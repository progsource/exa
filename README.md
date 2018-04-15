# exa

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![Version: 0.1.0](https://img.shields.io/badge/Version-0.1.0-brightgreen.svg)](https://semver.org/)

**exa** is a short name for **extended assert**.

It is using the [{fmt} library](https://github.com/fmtlib/fmt) for formatting
output messages.

## supported OS

It actually should work on any OS, that supports the C++14 standard library.

It is tested to work on:

* Linux (without exceptions and without RTTI)

## dependencies

* C++14
* [{fmt} library](https://github.com/fmtlib/fmt)

## assert levels

Currently there is `DEBUG`, `WARNING`, `DEFAULT`, `ERROR` and `FATAL`.

`DEBUG` will only output something, if exa was compiled with `NDEBUG` defined.

`DEBUG` and `WARNING` should run into a breakpoint, while `DEFAULT`, `ERROR` and
`FATAL` are going to abort the program.

At the moment there is then no other difference with the levels, only the output
message, which is written to `std::cerr`, differs based on the level.

## how to use

Clone the repository and run `git submodule update --init --recursive` to get
the dependencies.

Add `libs/fmt`, `include/exa/exa.h` and `src/exa/exa.cpp` to your files to
compile.

Then you can use it for example like:

```c++
#include "exa/exa.h"

// some code would surround the following lines ;)
// so this example code is not directly compile-able

EXA_DEBUG(2 == myVar, "myVar should be 2 and not {}", myVar);
EXA_WARNING(a < b);
EXA(1 == 0, "There {} something wrong.", "went");
EXA_ERROR(!myVector.empty(), "the vector is empty");
EXA_FATAL(a / 0, "really bad zero-devision");
```

## how to run tests

Tested on linux:

```bash
git clone https://github.com/progsource/exa.git
cd exa
git submodule update --init --recursive
mkdir tmp
cd tmp
cmake ..
make
make test # or run the tests directly with: ../build/ExaTests
```

If you want to see the output of the asserts during the test runs, you need to
set `EXA_DEBUG_TESTS` in the CMakeLists.txt to true, so it will still write
everything to cerr.

```cmake
set(EXA_DEBUG_TESTS true)
```

## how to contribute

There are different possibilities:

* [Create a GitHub issue](https://github.com/progsource/exa/issues/new)
* Create a pull request with an own branch (don't forget to put yourself in the
  AUTHORS file)

## thanks to

in no particular order

* [Sam Hocevar - PPK_ASSERT](https://github.com/gpakosz/PPK_ASSERT)
* [Victor Zverovich - {fmt} library](https://github.com/fmtlib/fmt)
* [Zacharias Pasternack - stdout and stderr: Adventures in Redirection, Part 1](http://zpasternack.org/stdout-and-stderr-adventures-in-redirection-part-1/)
