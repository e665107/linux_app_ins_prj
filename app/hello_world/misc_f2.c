#include "unp.h"  
#include "misc_f2.h"  

static int get_daytime_f()
{
    int                 sockfd, n, counter = 0;
    char                recvline[MAXLINE + 1];
    struct sockaddr_in  servaddr;

    if ( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        perror("socket error");

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port   = htons(123);    /* daytime server */
    /* 192.43.244.18   210.72.145.44 */
    if (inet_pton(AF_INET, "210.72.145.44", &servaddr.sin_addr) <= 0)
        err_quit("inet_pton error for %s", "210.72.145.44");

    if (connect(sockfd, (SA *) &servaddr, sizeof(servaddr)) < 0)
        err_sys("connect error");

    while ( (n = read(sockfd, recvline, MAXLINE)) > 0) {
        counter++;
        recvline[n] = 0;    /* null terminate */
        if (fputs(recvline, stdout) == EOF)
            err_sys("fputs error");
    }
    if (n < 0)
        err_sys("read error");

    printf("counter = %d\n", counter);
    exit(0);
}

void misc2_fun_test()
{
    get_daytime_f();
}


