Where do header files come from?
================================
Both user and system header files are included using the preprocessing
directive `#include`. It has two variants:

- `#include <file>` This variant is used for system header files. It searches
for a file named file in a standard list of system directories. You can prepend
directories to this list with the `-I` option (see Invocation).
- `#include "file"` This variant is used for header files of your own program.
It searches for a file named file first in the directory containing the current
file, then in the quote directories and then the same directories used for
`<file>`. You can prepend directories to the list of quote directories with the
`-iquote` option.

[Source: gcc.gnu.org](https://gcc.gnu.org/onlinedocs/cpp/Include-Syntax.html#Include-Syntax)

But where is the include path set?
----------------------------------
1. "Like most GNU software, GCC must be configured before it can be built." [Source](https://gcc.gnu.org/install/configure.html)
2. The `./configure` script is called in the [gcc.rb](https://github.com/Homebrew/homebrew-core/blob/a2f529d375868fe8d907e08aa892d37c1b4d3350/Formula/gcc.rb) Homebrew formula.
3. That configure script lives in the GCC repository in [configure](https://gcc.gnu.org/git/?p=gcc.git;a=blob;f=configure;hb=af8bbdf198a7cd619efd7c9a7aef2f86d5590aae).
4. Seems like the configure script is taking the `--prefix` option and somehow appending the `--enable-languages` and the gcc version to construct a list of subdirectories to look for header files in.

g++-8 -v
--------

> `g++-8 -v $1 -o ${OUTPUT_DIR}/${OUTPUT_FILE} && ./${OUTPUT_DIR}/${OUTPUT_FILE}`

    Using built-in specs.
    COLLECT_GCC=g++-8
    COLLECT_LTO_WRAPPER=/usr/local/Cellar/gcc@8/8.3.0_1/libexec/gcc/x86_64-apple-darwin18/8.3.0/lto-wrapper
    Target: x86_64-apple-darwin18
    Configured with: ../configure --build=x86_64-apple-darwin18 --prefix=/usr/local/Cellar/gcc@8/8.3.0_1 --libdir=/usr/local/Cellar/gcc@8/8.3.0_1/lib/gcc/8 --disable-nls --enable-checking=release --enable-languages=c,c++,objc,obj-c++,fortran --program-suffix=-8 --with-gmp=/usr/local/opt/gmp --with-mpfr=/usr/local/opt/mpfr --with-mpc=/usr/local/opt/libmpc --with-isl=/usr/local/opt/isl --with-system-zlib --with-pkgversion='Homebrew GCC 8.3.0_1' --with-bugurl=https://github.com/Homebrew/homebrew-core/issues --disable-multilib --with-native-system-header-dir=/usr/include --with-sysroot=/Library/Developer/CommandLineTools/SDKs/MacOSX10.14.sdk
    Thread model: posix
    gcc version 8.3.0 (Homebrew GCC 8.3.0_1) 
    COLLECT_GCC_OPTIONS='-v' '-o' './dist/hello-world/hello' '-mmacosx-version-min=10.15.0' '-asm_macosx_version_min=10.15' '-shared-libgcc' '-mtune=core2'
     /usr/local/Cellar/gcc@8/8.3.0_1/libexec/gcc/x86_64-apple-darwin18/8.3.0/cc1plus -quiet -v -D__DYNAMIC__ hello-world/hello.cpp -fPIC -quiet -dumpbase hello.cpp -mmacosx-version-min=10.15.0 -mtune=core2 -auxbase hello -version -o /var/folders/g2/9my9yx490tz_3z78zyg68njr0000gn/T//ccB74zh4.s
    GNU C++14 (Homebrew GCC 8.3.0_1) version 8.3.0 (x86_64-apple-darwin18)
        compiled by GNU C version 8.3.0, GMP version 6.1.2, MPFR version 4.0.2, MPC version 1.1.0, isl version isl-0.21-GMP

    GGC heuristics: --param ggc-min-expand=100 --param ggc-min-heapsize=131072
    ignoring nonexistent directory "/Library/Developer/CommandLineTools/SDKs/MacOSX10.14.sdk/usr/local/include"
    ignoring nonexistent directory "/usr/local/Cellar/gcc@8/8.3.0_1/lib/gcc/8/gcc/x86_64-apple-darwin18/8.3.0/../../../../../../x86_64-apple-darwin18/include"
    ignoring nonexistent directory "/Library/Developer/CommandLineTools/SDKs/MacOSX10.14.sdk/Library/Frameworks"
    #include "..." search starts here:
    #include <...> search starts here:
     /usr/local/Cellar/gcc@8/8.3.0_1/lib/gcc/8/gcc/x86_64-apple-darwin18/8.3.0/../../../../../../include/c++/8.3.0
     /usr/local/Cellar/gcc@8/8.3.0_1/lib/gcc/8/gcc/x86_64-apple-darwin18/8.3.0/../../../../../../include/c++/8.3.0/x86_64-apple-darwin18
     /usr/local/Cellar/gcc@8/8.3.0_1/lib/gcc/8/gcc/x86_64-apple-darwin18/8.3.0/../../../../../../include/c++/8.3.0/backward
     /usr/local/Cellar/gcc@8/8.3.0_1/lib/gcc/8/gcc/x86_64-apple-darwin18/8.3.0/include
     /usr/local/Cellar/gcc@8/8.3.0_1/lib/gcc/8/gcc/x86_64-apple-darwin18/8.3.0/include-fixed
     /Library/Developer/CommandLineTools/SDKs/MacOSX10.14.sdk/usr/include
     /Library/Developer/CommandLineTools/SDKs/MacOSX10.14.sdk/System/Library/Frameworks
    End of search list.
    GNU C++14 (Homebrew GCC 8.3.0_1) version 8.3.0 (x86_64-apple-darwin18)
        compiled by GNU C version 8.3.0, GMP version 6.1.2, MPFR version 4.0.2, MPC version 1.1.0, isl version isl-0.21-GMP

Linking
=======

_Following copied from [linking.txt](https://homepages.inf.ed.ac.uk/imurray2/compnotes/library_linking.txt)_

Notes on linking with C/C++ libraries with gcc/g++ when building an
existing project.
                                                -- Iain Murray, 2015.


There are at least three things that can go wrong when trying to link
with a library that is in a non-standard location on your machine:

1. The compiler can't find the .h header files.
2. The linker can't find the library's binary .a or .so files.
3. At run time, your binary can't find the library's .so file.

Usually the build script for a project should sort out at least 1 and 2.
If it has a configure script, try looking at:
    ./configure --help
which may have options to point the build system to any libraries in
non-standard locations.

Unfortunately many projects have broken build systems that don't work if
libaries are in non-standard locations. So here's some notes on brute
force fixes to the three issues above.



1. Pointing the compiler to .h header files for #include lines to work
----------------------------------------------------------------------

If you are calling gcc or g++, pass the path to the .h file like this:
    gcc -I/location/of/headers ...
or
    g++ -I/location/of/headers ...

If you have a complicated build system, you may not be able to easily
specify the compilation command-line directly. Instead you can export
the CPATH environment variable, with a colon-separated list of paths.
Then call your build system.

In bash set the environment variable like this:
    export CPATH="/location/one:/location/two"
or in (t)csh like this:
    setenv CPATH "/location/one:/location/two"

Environment variables that gcc looks at are documented here:
    https://gcc.gnu.org/onlinedocs/gcc/Environment-Variables.html

If you're really unlucky, the build system might reset environment
variables like CPATH. As a last resort hack, you could create a shell
script called "gcc" with the following contents (specifying the paths
you need):
    #!/bin/sh
    exec /usr/bin/gcc -I/location/one -I/location/two "$@"
make it executable with
    chmod +x gcc
and put it at the front of your path. E.g., put it in ~/bin/override
and do:
    export PATH="$HOME/bin/override:$PATH"
Then do the same for g++.


2. Pointing the linker to the library's binaries
------------------------------------------------

With access to library headers, gcc can compile object code (.o files
created when using the -c command-line option) without needing access to
the library routines themselves.

An executable will need the library routines though. These are either
included with the executable (statically linking the library's .a files
into the binary) or accessed from a .so "shared object" file.

An executable is created with a linker (usually /usr/bin/ld), but the
linker is usually called for us by gcc. We tell gcc where the .a or .so
files are by using:
    -L/path/to/library/code
We also have to tell it which libraries to link with, either by
explicitly linking in the .a file or specifying a library by name, for
example:
    -lfftw3
to link with libfftw3. However, if we're building an existing project,
its build system should already specify the library names. It's only
the locations of the libraries we'll have to fix.

If you can't easily specify paths with -L, we can again set a
colon-separated list in an environment variable:
    export LIBRARY_PATH=/location/one:/location/two
These locations are often different from the ones we previously put in
CPATH. They're directories containing library binaries (.a or .so files)
rather than the header files (.h).

If setting the environment variable doesn't work, as a last resort you
could override the gcc binary as in the previous section. This time
forcing the use of -L command-line arguments.


3. Making sure your executable can find the library's .so file
--------------------------------------------------------------

Even if the compiler knew where a shared object (.so file) was at
compile time, your resulting program can still have difficulty finding
it at run time. Even if it hasn't moved!

You can tell an executable where to look by setting LD_LIBRARY_PATH:
    export LD_LIBRARY_PATH="/location/one:/location/two"
before running your program.

Alternatively, you can make the linker bake the location into the
executable by passing:
    -Wl,-rpath,"/location/one"
to gcc (that's a letter 'l' not a one after the W). OR by setting an
environment variable:
    export LD_RUN_PATH="/location/one:/location/two"
before compiling. You then don't need to set LD_LIBRARY_PATH every time
you run the program.

You can see what shared libraries your program is trying to use with:
    ldd ./my_program


ProtoBuf
========

Install via instructions at https://github.com/protocolbuffers/protobuf/blob/master/src/README.md:

    git clone https://github.com/protocolbuffers/protobuf.git
    cd protobuf
    git submodule update --init --recursive
    ./autogen.sh

     CXX=g++-8 ./configure
     CXX=g++-8 make
     make check
     sudo make install
     sudo ldconfig # refresh shared library cache.
