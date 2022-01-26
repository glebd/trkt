# TRKTCLI

A [trakt.tv](https://trakt.tv) command-line interface written in C++20.

## Installing prerequisites

### Mac

* Install Xcode 13+ from the Mac App Store.
* Install [Homebrew](https://brew.sh).
* Install [Meson Build](https://mesonbuild.com).

```bash
brew install conan
conan remote add -i 0 conancenter https://center.conan.io
brew install meson
brew install ninja
brew install python3
pip3 install rich
```

## Installing dependencies

```bash
meson wrap install fmt
```

## Building TRKTCLI

```bash
meson configure build
cd build
meson compile
```
