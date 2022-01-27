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

## Links

### API

* [Trakt.tv API](https://trakt.docs.apiary.io/#introduction/create-an-app)

### Project layout

* [Pitchfork](https://api.csswg.org/bikeshed/?force=1&url=https://raw.githubusercontent.com/vector-of-bool/pitchfork/develop/data/spec.bs)
* [ModernCppStarter](https://github.com/TheLartians/ModernCppStarter)
* [cpp-starter-project by Jason Turner](https://github.com/cpp-best-practices/cpp_starter_project)
* [C++ Reference: libraries](https://en.cppreference.com/w/cpp/links/libs)

### Examples

* [Revisited: Full-fledged client-server example with C++ REST SDK 2.10](https://mariusbancila.ro/blog/2017/11/19/revisited-full-fledged-client-server-example-with-c-rest-sdk-2-10/)
