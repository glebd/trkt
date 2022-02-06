# TRKT

A [trakt.tv](https://trakt.tv) command-line interface written in C++20.

## Installing prerequisites

### Mac

* Install Xcode 13+ from the Mac App Store.
* Install [Homebrew](https://brew.sh).
* Install [Xmake](https://xmake.io).

```bash
brew install git
brew install xmake
brew install python3
pip3 install rich
```

## Dependencies

### vcpkg

```bash
git submodule init
git submodule update
```

### Libraries

* [{fmt}](https://fmt.dev)
* [C++ REST SDK](https://github.com/Microsoft/cpprestsdk)

## Building TRKT

```bash
xmake f -y --vcpkg=`pwd`/vcpkg
```

## API

* [Trakt.tv API](https://trakt.docs.apiary.io/#introduction/create-an-app)

## Project layout

* [Pitchfork](https://api.csswg.org/bikeshed/?force=1&url=https://raw.githubusercontent.com/vector-of-bool/pitchfork/develop/data/spec.bs)
* [ModernCppStarter](https://github.com/TheLartians/ModernCppStarter)
* [cpp-starter-project by Jason Turner](https://github.com/cpp-best-practices/cpp_starter_project)
* [C++ Reference: libraries](https://en.cppreference.com/w/cpp/links/libs)

## Libraries

### C++ next

* [cpp-coro](https://github.com/lewissbaker/cppcoro) - C++20 coroutine support library
* [range-v3](https://github.com/ericniebler/range-v3) - Range library for C++14/17/20, basis for C++20's `std::ranges`
* [expected](https://github.com/TartanLlama/expected) - C++11/14/17 `std::expected` with functional-style extensions
* [optional](https://github.com/TartanLlama/optional) - C++11/14/17 `std::optional` with functional-style extensions and reference support

### Tasks

* [taskflow](https://github.com/taskflow/taskflow)

### Console

* [xtd](https://github.com/gammasoft71/xtd) - Modern C++17/20 framework to create console (CLI), forms (GUI like WinForms) and tunit (unit tests like Microsoft Unit Testing Framework) applications on Windows, macOS, Linux, iOS and android.
* [cli](https://github.com/daniele77/cli) - A library for interactive command line interfaces in modern C++
* [indicators](https://github.com/p-ranav/indicators/) - Activity Indicators for Modern C++
* [ncurses](https://invisible-island.net/ncurses/)
* [cpp-terminal](https://github.com/jupyter-xeus/cpp-terminal) - Small header only C++ library for writing multiplatform terminal applications
* [FTXUI](https://github.com/ArthurSonzogni/FTXUI) - C++ Functional Terminal User Interface
* [imtui](https://github.com/ggerganov/imtui) - Immediate Mode Text-based User Interface C++ Library ([demo](https://imtui.ggerganov.com))

### Logging

* [spdlog](https://github.com/gabime/spdlog)

### Serialization

* [json](https://github.com/nlohmann/json) - [home](https://json.nlohmann.me)
* [toml++](https://github.com/marzer/tomlplusplus)

### Database

* [sqlpp11](https://github.com/rbock/sqlpp11)
* [sqlite-modern-cpp](https://github.com/SqliteModernCpp/sqlite_modern_cpp)

### Cryptography

[cryptopp](https://github.com/weidai11/cryptopp)

### Testing

* [Catch2](https://github.com/catchorg/Catch2)
* [googletest](https://github.com/google/googletest)
* [doctest](https://github.com/doctest/doctest)

### Benchmarks

* [nonius](https://github.com/libnonius/nonius) - [https://nonius.io](https://nonius.io)
* [hayai](https://github.com/nickbruun/hayai) - [blog](https://bruun.co/2012/02/07/easy-cpp-benchmarking)
* [google-benchmark](https://github.com/google/benchmark)
* [celero](https://github.com/DigitalInBlue/Celero)
* [nanobench](https://github.com/martinus/nanobench)

### Diagnostics

* [sanitizers](https://github.com/google/sanitizers)
* [clang-tidy](https://clang.llvm.org/extra/clang-tidy/)
* [cpp-dependencies](https://github.com/tomtom-international/cpp-dependencies)

## Examples

* [Revisited: Full-fledged client-server example with C++ REST SDK 2.10](https://mariusbancila.ro/blog/2017/11/19/revisited-full-fledged-client-server-example-with-c-rest-sdk-2-10/)
* [Client Server application with cpprest sdk Casablanca framework](https://github.com/kenhero/Cpp-REST-SDK-Client-Server-)
* [cpprestsdk OAuth2 client](https://github.com/Microsoft/cpprestsdk/blob/master/Release/samples/Oauth2Client/Oauth2Client.cpp)
* [`Poco::Net::OAuth20Credentials`](https://docs.pocoproject.org/current/Poco.Net.OAuth20Credentials.html)
* wlan-cloud-ucentralsec
  * [MicroService.h](https://github.com/Telecominfraproject/wlan-cloud-ucentralsec/blob/6d20c8408f30b945090681ddc6f752b721b086ac/src/framework/MicroService.h)
  * [AuthService.cpp](https://github.com/Telecominfraproject/wlan-cloud-ucentralsec/blob/c47e9bc98ddd61a814405afa77b3116eaeb627f7/src/AuthService.cpp)
* libmimiio (uses Poco)
  * [mimiioImpl.cpp](https://github.com/FairyDevicesRD/libmimiio/blob/c9b75db12ea81393d8577f9d2c9ceaa78ec27f10/src/mimiioImpl.cpp)
* [ofxHTTP](https://github.com/bakercp/ofxHTTP/blob/057212876235486aae25256a623edf38282f852e/src/ofxHTTP.h)
* [ofxCloudPlatform](https://github.com/bakercp/ofxCloudPlatform/blob/4a97b38cb9be1faf245b9421789e9b43b5645356/libs/ofxCloudPlatform/src/ServiceAccount.cpp)
* [Tethr.AudioBroker.CPP.SDK](https://github.com/CollabIP/Tethr.AudioBroker.CPP.SDK/blob/c809630018e1cf2ac81b4a6708a5b01ca786b810/Tethr.AudioBroker/Session.cpp)
* [toggldesktop](https://github.com/toggl-open-source/toggldesktop/blob/master/src/https_client.h)
* [InterprettableAddons/ofxHTTP/libs/ofxHTTP/src/OAuth20HTTPClient.cpp](https://github.com/martial/InterprettableAddons/blob/f95b7b19fb63a02f77ead378ca4be2ba59388a4a/ofxHTTP/libs/ofxHTTP/src/OAuth20HTTPClient.cpp)
* [InterprettableAddons/ofxHTTP/libs/ofxHTTP/src/OAuth20RequestFilter.cpp](https://github.com/martial/InterprettableAddons/blob/f95b7b19fb63a02f77ead378ca4be2ba59388a4a/ofxHTTP/libs/ofxHTTP/src/OAuth20RequestFilter.cpp)
* [InterprettableAddons/ofxHTTP/libs/ofxHTTP/include/ofx/HTTP/OAuth20HTTPClient.h](https://github.com/martial/InterprettableAddons/blob/f95b7b19fb63a02f77ead378ca4be2ba59388a4a/ofxHTTP/libs/ofxHTTP/include/ofx/HTTP/OAuth20HTTPClient.h)
* [Chilkat's Google OAuth2 example](https://www.example-code.com/cpp/github_oauth2_access_token.asp)

### Python Console Libraries

* [Rich](https://rich.readthedocs.io/en/latest/console.html), [code](https://github.com/Textualize/rich)
* [Python Prompt Toolkit](https://python-prompt-toolkit.readthedocs.io/en/stable/pages/asking_for_input.html)
* [Colorama](https://github.com/tartley/colorama) - Simple cross-platform colored terminal text in Python
* [Asciimatics](https://github.com/peterbrittain/asciimatics) - A cross platform package to do curses-like operations, plus higher level APIs and widgets to create text UIs and ASCII art animations
* [Cliff](https://docs.openstack.org/cliff/latest/install/index.html#)
* [Clint](https://github.com/kennethreitz-archive/clint)
* [Click](https://click.palletsprojects.com/en/8.0.x/parameters/)
* [PyInquirer](https://github.com/CITGuru/PyInquirer) - A Python module for common interactive command line user interfaces