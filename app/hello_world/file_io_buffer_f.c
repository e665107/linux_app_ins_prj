#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "file_io_buffer_f.h"

int fopen_f(int argc, const char*path0)
{
    /* FILE* fps; */
     


    return 0;
}

int get_line_f(int argc, const char*path0)
{
    FILE* fp;
    char* linebuf = NULL;
    size_t line_size = 0;
    
    if(argc < 2)
    {
        fprintf(stderr, "usage...\n");
        exit(1);

    }
    
    fp = fopen(path0, "r");
    
    if(fp == NULL)
    {
        perror("fopen");
        exit(1);
    }

    while (1) {

        if(getline(&linebuf, &line_size, fp) < 0)
        {
            perror("getline()");
            exit(1);
        }
        
        printf("%ld\n", strlen(linebuf));
        printf("%ld\n", line_size);

    }
    
    fclose(fp);
}


void get_line_f_test()
{
    get_line_f(2, "/data/linux_system_programming/Linux_c_src/my_c_code/my_test_ins/app/hello_world/files_for_test/1.txt");
}










