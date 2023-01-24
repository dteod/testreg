## testreg

### A small unit testing library for C with automatic test registration

`testreg` is a(nother) unit testing library for C projects. It implements the
bare minimum features you could expect from a testing framework, such as:

- automatic test registration: you can add tests to your compilation units
simply by including the headers and declaring test cases using the `TEST_CASE`
macro, and they will be collected directly by linking the various compilation units
- macros to `ASSERT` test results and `CHECK`s to skip them if particular
conditions are not met
- the possibility to embed a runner program in a compilation unit by declaring
`TESTREG_RUNNER` before including the library.

The library aims at the same level of usability of [Catch2](https://github.com/catchorg/Catch2),
with of course a (very) limited set of features restricted to the C programming
language. With it you can add your tests to each compilation unit, they will be
linked all together and statically registered before main is called.

## Purpose

The library can be used for two purposes:
1. Declare black-box tests in external compilation units that
include a library from a client's point of view:
```c
#include <mylib.h>
#include <testreg.h>

/*
Notice that both "label" and "[tag]" are entirely optional.
They are not used in v0.1.0 of the runner.
*/
TEST_CASE("mylib black box test 1", "[mylib][black-box]")
{
    // mylib black box test body 1
}

TEST_CASE("mylib black box test 2", "[mylib][black-box]")
{
    // mylib black box test body 2
}
```

2. Declare white-box tests in a library's compilation units conditionally with a macro, in order to access statically linked functions that wouldn't otherwise be accessible from external compilation units
```c
#include "mylib/inner_header.h"

static int mylib_private() { /*...*/ }

void mylib_api() {
    int result = mylib_private();
    /* use result */
}

#ifdef MYLIB_BUILD_TESTS
#include <testreg.h>

TEST_CASE("mylib white box test", "[mylib][white-box]") {
    ASSERT(mylib_private() == 1);
}

#endif
``` 

## Build

You can use both CMake and Meson to build the library, both the static and shared library are enabled.

### CMake

Run the following:

```bash
mkdir build
cd build
cmake ..
make
```

The example demo runner will not be built with the default target, build it explicitly if you want to see it in action:

```bash
make testreg_demo_runner
```

You can then run it, it should be present in your build folder.

### Meson

Run the following:

```bash
meson setup builddir
cd builddir
meson compile
```

You should find the `testreg_demo_runner` executable in your path ready to run a simple example.

## Package and install 

TODO