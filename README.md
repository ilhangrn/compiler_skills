# This is a demo project to learn more about compilers and their effective usage. 
> It is not for education purposes. It may be ugly for people trying to read. You can follow commits and changes to see what i am trying but it is not a rocket science.

> No need to check this basic repo and its funny progress.

> Build call was 

    cc my_app.c multi_file.c -o tell_me

But this will not work with our new file structure. We run compiler with including files:
    
    cc src/my_app.c src/lib/multi_file.c -o tell_me_time -I include/

Buy the way we call our outputs from ubuntu console like : (supposed we are on top directory)

    ./tell_me_time

Lets learn more flags.
### Debug Flags

> We can instruct the compiler to include extra debug information in our binary. This enables a better experience when debugging our program with lldb or gdb.

> The g flag is for debug. When we use GDB -ggdb is going to be the most expressive output avaliable.

> glevel is for debugging level. It is between [0-3] default it 2.

    Level 0
        is -g0, gives no debug information. negates the -g.
    
    Level 1
        gives minimal. gives some backtrace up to functions we don't plan to debug. But no information for local variables.
    
    Level 3
        is for extra info. All macro definitions present. Some debuggers supports macro expansion with -g3.
    
    If there is multiple -g options, last one will be effective.

### Warning flags
> -W flags are used for them.

    -Wall
        is not turn all warnings but turns on large set of warnings
    -Wextra
        turns additionals not in -Wall
    -Wpedantic or -pedantic
        turns on all warnings demanded by strict ISO C and C++, rejects the extensions.
    -Werror
        turns all warnings into errors
    -Werror=<id>
        which turns specific warning into error.
        e.g -Werror=switch turns -Wswitch into an error
    -Wno-error=<id>
        stops error generation if specific warning is on.
        e.g -Wno-error=switch stops -Wswitch from causing and error when it is in effect
    -Wno-<id>
        turns off a specific error
        e.g -Wno-switch turns off the -Wswitch warning.

### Optimization levels
    -O0, default
        reduce compile time, make debugging produce expected results.
    -O or -O1
        reducing code size and execution time, without some optimization which take time
    -O2
        perform all optimization, no space-speed tradeoff. increses time and performance
    -O3
        more optimization
    -Os
        optimize for size, enables all -O2 except ones increasing code size
    -Ofast
        not recommanded, enables all -O3, disregards standart compliance
    -Og
        optimize for debugging experience. This is our standart level for development.
        It is better than -O0 for producing debuggable code. Because in -O0 debugger passes are disabled.

### Lang specific flags
> We use usually need to control the dialect. Like C99 or C11 for C, C++17 for C++ solutions. Flag for this is:

    -std=c99
    -std=c11
    -std=gnu99
    -std=c++17
    -std=c++21

> it can also be -ansi to enable strict ANSI C mode. -ffreestanding indicate a freestanding env, -fno-builtin to disable builtin funcs from compiler. There are some more for env, you can for C dialect flags, C++ dialect flags.

### Output flags
    -c
        tells to compile and assemble source files but stop before linking. We use this heavily. Gives us object files for all sources.
    -s
        tells to compile but stop before assembling them. It gives us assembly files(.s) for each source.
    -E
        tells to stop after preprocessing stage. It gives input source code to compiler. You can check it for preprocessing problems.
    -v
        reminds me verbose. tells to show full command execution during compile.

### Lets see embedded flags
    -mcpu
        We use a lot. To tell what kind of processor we are coding for. 
        e.g -mcpu=name[+extenstion]
        For exentions, some are 
        +nosimd (without advanced simd floating point)
        +nofp (version without floating point)
    -march
        determines which instructions can be generated for assembly. it can replace -mcpu or placed together with it.
    -mabi
        it is for application binary interface. Tells compiler how to use registers and call functions. by default it is aapc for 32-bit arm systems.

### Instruction set flag
> You can use -mthumb or -marm. Arm has these two different instruction sets.

### Endianness
> Compiler has assumption but you can set it as -mlittle-endian or -mbig-endian.

### Floating point options
    -To specify float ABI, you can use mfloat-abi=soft or -mfloat-abi-hard. Soft tells to use software for operatiosn, hard tells to use hardware to handle floatong point operations. Flag has to be same for all compilation. If a file compiled for a different version, it will be problem.

    -To specify FPU version, -mfpu=vfpv4 or -mfpu=fpv5-sp-d16. They are for version of VFP and supported type like 16bit FPU, 32bit FPU or 64bit FPU.

### SDK flags
To use SDKs properly we need to check their flags and use them. Like STM32L4, It can support all device family or like -DSTM32F103xB for specific group.

In the end we have something like this for an Cortex m7 with hardware floating point:
    -mcpu=cortex-m7 -mfloat-abi=hard -mfpu=fpv5-sp-d16 -mthumb

### GCC file parsings

    file.c
        C source code that must be preprocessed.
    file.i
        C source code that should not be preprocessed.

    file.ii
        C++ source code that should not be preprocessed.

    file.h
        C, C++, Objective-C or Objective-C++ header file to be turned into a precompiled header (default), or C, C++ header file to be turned into an Ada spec (via the -fdump-ada-spec switch).

    file.cc, file.cp, file.cxx, file.cpp, file.CPP ,file.c++, file.C
        C++ source code that must be preprocessed. Note that in ‘.cxx’, the last two letters must both be literally ‘x’. Likewise, ‘.C’ refers to a literal capital C.

    file.hh, file.H, file.hp, file.hxx, file.hpp, file.HPP, file.h++, file.tcc
        C++ header file to be turned into a precompiled header or Ada spec.

    file.s
        Assembler code.

    file.S, file.sx
        Assembler code that must be preprocessed.

    other
        An object file to be fed straight into linking. Any file name with no recognized suffix is treated this way.

### Object file
It is mostly compiled code. Near to machine code. It has no addresses for function calls and global variables which are in a different file. Compiler generates placeholder for them, linker replaces them in linking phase. Linker collects various object files and replaces stubs with the correct memory addresses.

> Lets try to see assemly code which is short and clean for now.

    cc src/my_app.c src/lib/multi_file.c -I include -S

<br>

---
## Linker
> Linker collects all of the provided objects and libraries into memory and resolves the placeholder stubs and symbols with the proper memory addresses or dynamic linking calls. Any functions or variables not found will result in a error. Functions and variables not in use typically discarded during optimization pass.

> For compiler path is clear, result is object file. In linker result can be an object, library or binary.

> Linker program in Clang and GCC called as ld.

### Libraries
> libraries are precompiled object files that typically performs a related set of functions. They are often incomplete and do not provide a main().

> There is two type: static, shared.

### Static libraries
> It is basically a set of object files that are copied into a single file. Tool for creating them is archiver. Called as ar in GCC and Clang. extension of output is ".a".

### Shared libraries = dynamic
> They are similar to static but can be used by other programs. If library is shared they are not combined into a binary. Instead a table is created in the executable, which refers to dynamic library. When program executed a program called as loader reads the library contents and places machine code for the needed function into memory.

> In this way binaries get smaller, since a single library can be used in different binaries by call. Shared libraries can also be updated without needing to rebuild the dependent binaries.

> Other name of shared library is dynamic library.

> their extentions are like 

    - .dll(dynamicall linked library) for windows
    - .dylib on OS X
    - .so (shared object) on Linux

> naming for them need to be lib[name].[extention] e.g:
    - libc.a
    - libSystem.dylib
    - libgcc.so

> If you don't use this naming linker will not be able locate.

> When we use compiler for linking it helps us for flags and libraries like libc for output. But when we use ld for linking project we fail. There is no support there. Better way is using compiler.

> If we are going to call linker ld by ourself we need to add -l flag and follow with the name of library without lib prefix, like "-ls" for our missed library libc. In apple systems it becomes "-lSystem".

> Now we go like this

    cc -c src/my_app.c src/lib/multi_file.c  -I include

    we get object files for compiler result, then we try to link them with:

    ld multi_file.o my_app.o -lc -o manu

    And we fail. Linker is not easy to handle, systems dependencies and organization is too high

    We go with compiler!!!

### Some common linker flags to get used to, but not using :)

    -L/home/lib
        to indicate a non-standart search directory to look for libraries during linktime
    -T my_script.lds
        to specify a linker script to be used by linker.
    -static
        forces to use static library for binary. Prevents linker to use shared libraries and disables the -pie flag, if used.
    -pthread
        can be used to link the POSIX threads library on platform support it.
    -Map
        will generate a linker map which is a txt file that describes all symbols and sections in binary.
        it is so useful for debugging 
        e.g: -Map filename.map
        GCC uses -Map while Clang and OS X use -map
    -specs
        passes a spec file to compiler. A text file to override GCC default behaviour. It can be used to set default include directories, library search path, linking args, selection of standart c lib, runtime implementation, startup libraries.
        A famous one is to use picolib which using nano.specs
        -specs=nano.specs

> In embedded systems we rely on compilers default values in most cases. Typically we use flags to compile against standart libraries like libc and libc++. e.g

    - nostdinc
    - nodefaultlibs

> -e flag can be used to control entry point for program. Normally linker assumes a default as _start. We may need to overwrite as reset for our embedded systems. There are two forms for it.

    -e entry_func
    --entry=entry_func

> -nostartfiles is used to give your own startup files instead of standart system files. It is common in embedded.

> -nodefaultlibs tells to not use standart system libraries. Useful to prevent automatic linking of c library and others. In embedded we want to give our own usually.

> -nolibc similar to -nodefaultlibs but reduced in scope. Startup files are still linked

> -nostdlib will not link standart system startup files or libraries. This is equivalent to -nodefaultlibs.

    *Before passing to another section lets we need to take care of docs. Lets add mdbook for this project.

### Uncommon flags we may need
