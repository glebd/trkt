#include <fmt/format.h>
#include <cli/cli.h>
#include <cli/clifilesession.h>
#include <cli/filehistorystorage.h>
#include <iostream>
#include <memory>

int main(int /*argc*/, char** /*argv*/)
{
    try {
        cli::SetColor();
        auto rootMenu = std::make_unique<cli::Menu>("trkt");
        cli::Cli cli( std::move(rootMenu) );
        cli.ExitAction( [](auto& out){ out << "Bye.\n"; } );
        cli.StdExceptionHandler(
                [](std::ostream& os, const std::string& cmd, const std::exception& e)
                {
                    os << fmt::format("Exception '{}' caught handling command '{}'\n", e.what(), cmd);
                }
        );
        cli::CliFileSession input(cli);
        input.Start();
    }
    catch(const std::exception& e) {
        std::cerr << fmt::format("Exception: {}\n", e.what());
        return -1;
    }
    catch(...) {
        std::cerr << "Unknown exception\n";
        return -1;
    }
    return 0;
}
