# This is a demo project to learn more about compilers and their effective usage. 
> It is not for education purposes. It may be ugly for people trying to read. You can follow commits and changes to see what i am trying but it is not a rocket science.

> No need to check this basic repo and its funny progress.

> Build call was 

    cc my_app.c multi_file.c -o tell_me

But this will not work with our new file structure. We run compiler with including files:
    
    cc src/my_app.c src/lib/multi_file.c -o tell_me_time -I include/

Buy the way we call our outputs from ubuntu console like : (supposed we are on top directory)

    ./tell_me_time