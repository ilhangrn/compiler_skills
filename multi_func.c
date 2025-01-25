#include <stdio.h>
#include <time.h>
#include "multi_file.h"

void print_time(void){
    time_t current_time;
    time(&current_time);
    
    printf("time is %s \n", ctime(&current_time));
}