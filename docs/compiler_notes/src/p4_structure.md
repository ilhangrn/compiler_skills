## Structure
> Up to this point, we implemented a two stage software construction process

    1. Create a static library
    2. Compile the main source and link it with the static lib.

> For most projects we will encounter in the field structure is similar.

> For almost every project we need to specify directories for this process.

    -I flag is used to specify a new search directory for the files
    -L flag is used to specify a new search directory for shared libraries
    - And source files and object files can be specified using absolute or relative paths

> In computer most of the programs uses dynamic libraries. But in embedded systems we don't use. Especially those written for mcu without a complex operating system and dynamic program loader.

> Instead we can force linker and compiler to produce statically linked binary with -static flag. It says combine all files and generate a single monolithic binary with no external dependencies. Typically unused library routines will be discarded by linker.

> We don't force and there are both static and dynamic libraries in env, compiler picks dynamic one.

> Linker has a table and places symbols and undefined symbols in order. We have give them in order. During linking if it already has symbol throws error of "multiple definition" 

> Seems familiar :) ?

> Linker checks library files to match with undefined symbols in table with them. After checking libraries and still has no definition for symbol it throws error "undefined reference"

> Order is matter, first place objects then place libraries at the end.

> GCC and Clang supplies linker script for us. Others force you to do command line invocation.

> Linker script has:

    - The memory layout with storage locations and adr ranges
    - Program sections
    - Symbols should be added by linker
    - Options like entry point and output binary format
        e.g, our hero : ELF

> We call it with -T flag. e.g:

    ld -T linker_script.lds object.o -o my_app

