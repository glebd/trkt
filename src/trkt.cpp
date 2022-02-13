#include <cli/cli.h>
#include <cli/clifilesession.h>
#include <cpprest/http_client.h>
#include <cpprest/http_listener.h>
#include <fmt/format.h>

#include <cstdlib> // getenv
#include <iostream>
#include <memory>
#include <mutex>
#include <string>
#include <utility>

//
// A simple listener class to capture OAuth 2.0 HTTP redirect to localhost.
// The listener captures redirected URI and obtains the token.
// This type of listener can be implemented in the back-end to capture and store tokens.
// https://github.com/Microsoft/cpprestsdk/blob/master/Release/samples/Oauth2Client/Oauth2Client.cpp
//
class oauth2_code_listener
{
private:
  std::unique_ptr<web::http::experimental::listener::http_listener> m_listener;
  pplx::task_completion_event<bool> m_tce;
  web::http::oauth2::experimental::oauth2_config& m_config;
  std::mutex m_resplock;

public:
  oauth2_code_listener(web::uri listen_uri, web::http::oauth2::experimental::oauth2_config& config)
    : m_listener(new web::http::experimental::listener::http_listener(std::move(listen_uri)))
    , m_config(config)
  {
    m_listener->support([this](const web::http::http_request& request) -> void {
      if (request.request_uri().path() == U("/") && !request.request_uri().query().empty()) {
        m_resplock.lock();

        m_config.token_from_redirected_uri(request.request_uri())
          .then([this, request](const pplx::task<void>& token_task) -> void {
            try {
              token_task.wait();
              m_tce.set(true);
            } catch (const web::http::oauth2::experimental::oauth2_exception& e) {
              ucout << "Error: " << e.what() << "\n";
              m_tce.set(false);
            }
          });

        request.reply(web::http::status_codes::OK, U("Ok."));

        m_resplock.unlock();
      } else {
        request.reply(web::http::status_codes::NotFound, U("Not found."));
      }
    });

    m_listener->open().wait();
  }

  ~oauth2_code_listener() { m_listener->close().wait(); }

  pplx::task<bool> listen_for_code() { return pplx::create_task(m_tce); }
};

//
// Utility method to open browser on Windows, OS X and Linux systems.
// https://github.com/Microsoft/cpprestsdk/blob/master/Release/samples/Oauth2Client/Oauth2Client.cpp
//
static void open_browser(const std::string& auth_uri)
{
#if defined(_WIN32) && !defined(__cplusplus_winrt)
  // NOTE: Windows desktop only.
  auto r = ShellExecuteA(NULL, "open", auth_uri.c_str(), NULL, NULL, SW_SHOWNORMAL);
#elif defined(__APPLE__)
  // NOTE: OS X only.
  std::string browser_cmd(fmt::format("open \"{}\"", auth_uri));
  (void)system(browser_cmd.c_str());
#else
  // NOTE: Linux/X11 only.
  std::string browser_cmd(fmt::format("xdg-open \"{}\"", auth_uri));
  (void)system(browser_cmd.c_str());
#endif
}

//
// Base class for OAuth 2.0 sessions of this sample.
// https://github.com/Microsoft/cpprestsdk/blob/master/Release/samples/Oauth2Client/Oauth2Client.cpp
//
class oauth2_session_sample
{
private:
  utility::string_t m_name;
  std::unique_ptr<oauth2_code_listener> m_listener;

public:
  oauth2_session_sample(utility::string_t name, utility::string_t client_key, utility::string_t client_secret,
                        utility::string_t auth_endpoint, utility::string_t token_endpoint,
                        utility::string_t redirect_uri)
    : m_oauth2_config(std::move(client_key), std::move(client_secret), std::move(auth_endpoint),
                      std::move(token_endpoint), std::move(redirect_uri))
    , m_name(std::move(name))
    , m_listener(new oauth2_code_listener(redirect_uri, m_oauth2_config))
  {}

  void run()
  {
    if (is_enabled()) {
      ucout << "Running " << m_name.c_str() << " session...\n";

      if (!m_oauth2_config.token().is_valid_access_token()) {
        if (authorization_code_flow().get()) {
          m_http_config.set_oauth2(m_oauth2_config);
        } else {
          ucout << "Authorization failed for " << m_name.c_str() << ".\n";
        }
      }

      run_internal();
    } else {
      ucout << "Skipped " << m_name.c_str()
            << " session sample because app key or secret is empty. Please see instructions.\n";
    }
  }

protected:
  virtual void run_internal() = 0;

  pplx::task<bool> authorization_code_flow()
  {
    open_browser_auth();
    return m_listener->listen_for_code();
  }

  web::http::client::http_client_config m_http_config;
  web::http::oauth2::experimental::oauth2_config m_oauth2_config;

private:
  [[nodiscard]] bool is_enabled() const
  {
    return !m_oauth2_config.client_key().empty() && !m_oauth2_config.client_secret().empty();
  }

  void open_browser_auth()
  {
    auto auth_uri(m_oauth2_config.build_authorization_uri(true));
    ucout << "Opening browser in URI:\n";
    ucout << auth_uri << "\n";
    open_browser(auth_uri);
  }
};

//
// Specialized class for Trakt.tv OAuth 2.0 session.
// Based on https://github.com/Microsoft/cpprestsdk/blob/master/Release/samples/Oauth2Client/Oauth2Client.cpp
//
class trakt_session_sample : public oauth2_session_sample
{
private:
  inline static char const* m_api_url = "https://api-staging.trakt.tv";
  constexpr static int api_version = 2;

public:
  trakt_session_sample(const std::string& key, const std::string& secret)
    : oauth2_session_sample(U("Trakt"), key, secret, U(fmt::format("{}/oauth/authorize", m_api_url)),
                            U(fmt::format("{}/oauth/token", m_api_url)), U("http://localhost:8889/"))
  {}

protected:
  void run_internal() override
  {
    web::http::client::http_client api(U(m_api_url), m_http_config);
    ucout << "Requesting account information:\n";
    ucout << "Information: " << api.request(web::http::methods::GET, U("account/info")).get().extract_json().get()
          << "\n";
  }
};

int main(int /*argc*/, char** /*argv*/)
{
  char const* trakt_key_ptr = std::getenv("TRAKT_KEY");
  std::string const trakt_key = trakt_key_ptr ? trakt_key_ptr : "";
  char const* trakt_secret_ptr = std::getenv("TRAKT_SECRET");
  std::string const trakt_secret = trakt_secret_ptr ? trakt_secret_ptr : "";

  if (trakt_key.empty() || trakt_secret.empty()) {
    std::cerr << "[ERROR] Both TRAKT_KEY and TRAKT_SECRET environment variables must be defined\n";
    return -1;
  }

  try {
    cli::SetColor();
    auto rootMenu = std::make_unique<cli::Menu>("trkt");
    cli::Cli cli(std::move(rootMenu));
    cli.ExitAction([](auto& os) { os << "Bye.\n"; });
    cli.StdExceptionHandler([](std::ostream& os, const std::string& cmd, const std::exception& e) {
      os << fmt::format("Exception '{}' caught handling command '{}'\n", e.what(), cmd);
    });
    cli::CliFileSession input(cli);
    input.Start();
  } catch (const std::exception& e) {
    std::cerr << fmt::format("Exception: {}\n", e.what());
    return -1;
  } catch (...) {
    std::cerr << "Unknown exception\n";
    return -1;
  }
  return 0;
}
