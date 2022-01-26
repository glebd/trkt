#include <fmt/format.h>
#include <iostream>

int main(int /*argc*/, char** /*argv*/)
{
    std::cout << fmt::format("Hello world!\n");
#if __cplusplus >= 202002L
    // C++20 (and later) code
    std::cout << "C++20\n";
#endif
    return 0;
}
