#include "io.h"
#include <stdio.h>

void a_read() 
{
    printf("hello\n");    
}

void a_write(char *buff, int size) {
    printf("aa");
}

io_access_t a_io_access = {
    &a_write,
    &a_read
};

