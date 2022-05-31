#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include "http_client.h"

int http_client_ins(void)
{
    int sockfd;
    int len;
    struct sockaddr_in address;
    int result;
    char *req = "GET\r\n";
    char ack[512];
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("127.0.0.1");
    address.sin_port = htons(4000);
    len = sizeof(address);
    result = connect(sockfd, (struct sockaddr *)&address, len);

    if (result == -1)
    {
        perror("oops: client1");
        exit(1);
    }

    if(write(sockfd, req, strlen(req)) == 0)
        goto close;
    read(sockfd, ack, 10);
    printf("char from server = %s\n", ack);
close:
    close(sockfd);
    exit(0);
}
