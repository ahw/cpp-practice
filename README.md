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
