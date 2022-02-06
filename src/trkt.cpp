#include <fmt/format.h>
#include <cli/cli.h>
#include <cli/clifilesession.h>
#include <cli/filehistorystorage.h>
#include <iostream>
#include <memory>

int main(int /*argc*/, char** /*argv*/)
{
    try {
        cli::CmdHandler colorCmd;
        auto rootMenu = std::make_unique<cli::Menu>("trkt");
        cli::Cli cli( std::move(rootMenu) );
        cli.ExitAction( [](auto& out){ out << "Bye.\n"; } );
        cli::CliFileSession input(cli);
        input.Start();
        return 0;
    }
    catch(...) {
        std::cerr << "Unknown exception\n";
    }
    return -1;
}
