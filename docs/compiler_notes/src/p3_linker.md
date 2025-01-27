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

> -u flag can be used to mark a function as undefined. This is used to unload a function definition so another library can use. e.g

    -u symbol_to_undefine

> After a regular embedded script becomes like this:

    -Larchitecture/arm/linker -Tgcc_arm_common.ld -specs=nosys.specs

If we dont need to use different standart libs we do not use -nodefault or -nolibc.

> Note that not all linker flags recognised by compiler. We need to pass them with an extra -Xlinker or -Wl flag. The flag following -Xlinker will be passed to linker.

> to pass command to linker to create a map file named test.map, command becomes:

    cc my_app.o multi_file.o -Xlinker -Map -Xlinker test.map

    or we can use flag=argument style
    cc my_app.o multi_file.o -Xlinker -Map=test.map

> if we use -Wl we use commo to seperate them

    cc my_app.o multi_file.o -Wl,-Map,test.map

In general we prefer -Wl version.

### Linking for a static library
> we do it some reasons:
- When we need to compile different parts with different flags, include paths and preprocessors.
- To leverage information hiding, encapsulation to decrease coupling.
- To keep source code hidden while releasing pre compiled libraries to customers
- To reduce compalation time for complex builds


    For embedded system engineers static libraries are almost always the choice.

To create our static library we don't use linker or compiler, instead we use archiver(ar). e.g

    ar rcs my_app.a my_app.o multi_file.o
    -ar
        archiver
    r: insert symbols, replace already existing
    c: create a new arc
    s: write an index

> lets say we want to create static library for parts. We need to archive them individualy like here:

    cc -c src/my_app.c src/lib/multi_file.c -I include
    ar rcs libmultifile.a multi_file.o

> Now it is time to link them for application. We need to compile other part too. We already did. We have two .a files.

> I failed at this point, will check it later.

### Linking for shared library
> Shared libraries are created using the compiler/linker. We need to use special compilation. We use -fPIC flag to create position-indepent code. It means it can be executed in any memory address without modification. We go to library directory and call

    cc -fPIC -c multi_file.c -o multi_pic.o -I ../../include/

    then we call:

    cc -shared multi_pic.o -o multi_dyn.dylib
    cc -shared multi_pic.o -o multi_dyn.so
    cc -shared multi_pic.o -o multi_dyn.dll

> Now we have shared library which is with 
    .dylib for OS X, 
    .so for linux 
    .dll for windows

> Now we know all, we could run directly from compiler with a single command below. Gives us shared library from c files.

    cc -shared multi_file.c -o libmulti_func.so -I ../../include

    It could be .dll or dylib. Just examples.

> Sumamry:

    If you are going to compile source files into object files that will be used in shared library, use:
    -fPIC -c
    -> output is .o object files

    If you are compiling sources or object files into a shared library using the compiler front-end use: 
    -shared.
    -> output is the shared library with .so, .dll, .dylib
    
    We usually create share libraries through library front-end.

> Remember we generated libmultifunc.so, i moved it to top folder to use as library and generate output. we call next command(-L. says our library is here) and lmulti_func says there is a shared library named "libmulti_func".[extention] 

    cc my_app.o -L. -lmulti_func -o multi_linked_lib

> Now we have application named multi_linked_lib. We call

    ./multi_linked_lib
    -> and we fail. Because program loader looks another path for shared libraries. So we tell it our shared is here.

    LD_LIBRARY_PATH=. ./multi_linked_lib
    -> it works. It was a long journey to run a c code. Life was never easy, we forget!


