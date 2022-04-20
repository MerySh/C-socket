#include <stdio.h>
#include <string.h>
#include "io.h"

io_access_t a_io_access;

int main() 
{
    io_access_t *io_access;

    char filename[20];
    printf("Please enter the filename where you want to read-write: ");
    scanf("%s", filename);

    if (!memcmp(filename, "a", 1)) {
        io_access = &a_io_access;
    }
    /*
    else if (!strcmp(filename, "b")) {
        io_access = &b_io_access;
    } else if (!strcmp(filename, "c")) {
        io_access = &c_io_access;
    }
    */

    io_access->read();
}  
