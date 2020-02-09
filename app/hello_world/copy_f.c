/*************************************************************************\
*                  Copyright (C) Michael Kerrisk, 2017.                   *
*                                                                         *
* This program is free software. You may use, modify, and redistribute it *
* under the terms of the GNU General Public License as published by the   *
* Free Software Foundation, either version 3 or (at your option) any      *
* later version. This program is distributed without any warranty.  See   *
* the file COPYING.gpl-v3 for details.                                    *
\*************************************************************************/

/* Listing 4-1 */

#include <sys/stat.h>
#include <fcntl.h>
#include "lib/tlpi_hdr.h"
#include "copy_f.h"
#include "error_functions.h"

#ifndef BUF_SIZE        /* Allow "cc -D" to override definition */
#define BUF_SIZE 1024
#endif

int copy_f(int argc, const char*path0, const char*path1)
{
    int inputFd, outputFd, openFlags;
    mode_t filePerms;
    ssize_t numRead;
    char buf[BUF_SIZE];

    
    if (argc != 3 || strcmp(path0, "--help") == 0)
        usageErr("%s old-file new-file\n", path0);
 
    /* Open input and output files */
    inputFd = open(path0, O_RDONLY);
    if (inputFd == -1)
        errExit("opening file %s", path0);

    openFlags = O_CREAT | O_WRONLY | O_TRUNC;
    filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP |
                S_IROTH | S_IWOTH;      /* rw-rw-rw- */
    
    outputFd = open(path1, openFlags, filePerms);
    if (outputFd == -1)
        errExit("opening file %s", path1);
    /* Transfer data until we encounter end of input or an error */
    while ((numRead = read(inputFd, buf, BUF_SIZE)) > 0)
        if (write(outputFd, buf, numRead) != numRead)
            fatal("couldn't write whole buffer");
    if (numRead == -1)
        errExit("read");

    if (close(inputFd) == -1)
        errExit("close input");
    if (close(outputFd) == -1)
        errExit("close output");
    
    return 0;
}


void copy_f_test()
{
    copy_f(3, "/data/linux_system_programming/Linux_c_src/my_c_code/my_test_ins/app/hello_world/files_for_test/1.txt", "/data/linux_system_programming/Linux_c_src/my_c_code/my_test_ins/app/hello_world/files_for_test/2.txt");
}




