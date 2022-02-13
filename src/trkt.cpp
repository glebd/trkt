#include <cli/cli.h>
#include <cli/clifilesession.h>
#include <cpprest/http_client.h>
#include <cpprest/http_listener.h>
#include <fmt/format.h>

#include <iostream>
#include <memory>
#include <mutex>
#include <string>

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
    : m_listener(new web::http::experimental::listener::http_listener(listen_uri))
    , m_config(config)
  {
    m_listener->support([this](web::http::http_request request) -> void {
      if (request.request_uri().path() == U("/") && !request.request_uri().query().empty()) {
        m_resplock.lock();

        m_config.token_from_redirected_uri(request.request_uri())
          .then([this, request](pplx::task<void> token_task) -> void {
            try {
              token_task.wait();
              m_tce.set(true);
            } catch (const web::http::oauth2::experimental::oauth2_exception& e) {
              ucout << "Error: " << e.what() << std::endl;
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
    : m_oauth2_config(client_key, client_secret, auth_endpoint, token_endpoint, redirect_uri)
    , m_name(name)
    , m_listener(new oauth2_code_listener(redirect_uri, m_oauth2_config))
  {}

  void run()
  {
    if (is_enabled()) {
      ucout << "Running " << m_name.c_str() << " session..." << std::endl;

      if (!m_oauth2_config.token().is_valid_access_token()) {
        if (authorization_code_flow().get()) {
          m_http_config.set_oauth2(m_oauth2_config);
        } else {
          ucout << "Authorization failed for " << m_name.c_str() << "." << std::endl;
        }
      }

      run_internal();
    } else {
      ucout << "Skipped " << m_name.c_str()
            << " session sample because app key or secret is empty. Please see instructions." << std::endl;
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
  bool is_enabled() const { return !m_oauth2_config.client_key().empty() && !m_oauth2_config.client_secret().empty(); }

  void open_browser_auth()
  {
    auto auth_uri(m_oauth2_config.build_authorization_uri(true));
    ucout << "Opening browser in URI:" << std::endl;
    ucout << auth_uri << std::endl;
    open_browser(auth_uri);
  }
};

int main(int /*argc*/, char** /*argv*/)
{
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
