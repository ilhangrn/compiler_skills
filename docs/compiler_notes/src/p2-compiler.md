## Compiler

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

