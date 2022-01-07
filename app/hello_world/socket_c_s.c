#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>

#include "socket_c_s.h"

#define MAX_LINE 100
#define REQUEST 100
#define REPLY 100

static int tcp_client_f(void);
static int tcp_server_f(void);

static int udp_client_f(void);
static int udp_server_f(void);

void client_f(void)
{
#ifdef CLIENT_TCP_FUNC
        tcp_client_f();
#endif // CLIENT_TCP
#ifdef CLIENT_UDP_FUNC
        udp_client_f();
#endif // CLIENT_TCP
        
}

void server_f()
{
#ifdef SERVER_TCP_FUNC
        tcp_server_f();
#endif // SERVER_TCP
#ifdef SERVER_UDP_FUNC
        udp_server_f();
#endif // SERVER_TCP
}

static int tcp_client_f(void)
{
    struct sockaddr_in sin;
    char buf[MAX_LINE];
    int sfd;
    int port = 8000;
    char *str = "socket communication"; 
    socklen_t addr_len;
    int n; 
    int i;
    
    bzero(&sin, sizeof(sin));
    sin.sin_family = AF_INET;
    /*convert IPv4 and IPv6 addresses from text to
      binary form  */
    inet_pton(AF_INET, "192.168.100.141", &sin.sin_addr);  /*192.168.100.141--serverip*/
    sin.sin_port = htons(port);  /* convert values to network byte order */
    sfd = socket(AF_INET, SOCK_STREAM, 0);  /* create a socket */
    connect(sfd, (const struct sockaddr *)&sin, sizeof(sin)); 

    for (i = 0; i < 100; i++) {
            printf("%s:%d \n", __func__, __LINE__);

            n = sendto(sfd, "hello", 6, 0, (struct sockaddr *) &sin, sizeof(sin));
            printf("%s:%d \n", __func__, __LINE__);

            /* read(sfd, buf, MAX_LINE); */
            if(n == -1){
                    perror("fail to send\n");
                    exit(1);
            }

            printf("%s:%d \n", __func__, __LINE__);
            
            addr_len = sizeof(sin);
    
            n = recvfrom(sfd, buf, MAX_LINE, 0, (struct sockaddr *) &sin, &addr_len);
            if(n == -1){
                    perror("fail to receive\n");
                    exit(1);
            }else
                    printf("receive from server: %s\n", buf);
            sleep(1);
    }

    close(sfd); 
    printf("tcp_client closed\n");         
    
    return 0;
}

static int udp_client_f(void)
{
	int			sfd, i, n, addr_len;
	struct sockaddr_in	servaddr;
        int port = 8000;
        char buf[MAX_LINE];        
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(port);
        inet_pton(AF_INET, "192.168.100.141", &servaddr.sin_addr);  /*192.168.100.141--serverip*/
        sfd = socket(AF_INET, SOCK_DGRAM, 0);  /* create a socket */
        for (i = 0; i < 100; i++) {
                printf("%s:%d \n", __func__, __LINE__);

                n = sendto(sfd, "hello", 6, 0, (struct sockaddr *) &servaddr, sizeof(servaddr));
                if(n == -1){
                        perror("fail to send\n");
                        exit(1);
                }

            
                addr_len = sizeof(servaddr);
    
                n = recvfrom(sfd, buf, MAX_LINE, 0, (struct sockaddr *) &servaddr, &addr_len);
                if(n == -1){
                        perror("fail to receive\n");
                        exit(1);
                }else
                        printf("receive from server: %s\n", buf);
                sleep(1);
        }

        close(sfd); 
        printf("udp_client closed\n");         


}

void my_fun(char * p)
{
    if(p == NULL) 
        return;
    
    for (; *p != '\0'; p++)
        if(*p >= 'A' && *p <= 'Z') 
            *p = *p -'A'+ 'a';
}

static int tcp_server_f(void)
{
    struct sockaddr_in sin;
    struct sockaddr_in cin;
    int l_fd;
    int c_fd;
    socklen_t len;
    char buf[MAX_LINE]; 
    char addr_p[INET_ADDRSTRLEN]; 
    int port = 8000; 
    int n; 
    
    bzero(&sin, sizeof(sin)); 
    sin.sin_family = AF_INET; 
    sin.sin_addr.s_addr = INADDR_ANY;   /* Address to accept any incoming messages. */ 
    sin.sin_port = htons(port);
    
    l_fd = socket(AF_INET, SOCK_STREAM, 0); 
    
    bind(l_fd, (struct sockaddr *)&sin, sizeof(sin));
    listen(l_fd, 10); 
    
    printf("waiting ...\n");
    
    c_fd = accept(l_fd, (struct sockaddr *) &cin, &len); 
    
    while(1) {
            n = read(c_fd, buf, MAX_LINE); 
            inet_ntop(AF_INET, &cin.sin_addr, addr_p, sizeof(addr_p)); 
            printf("client IP is %s, port is %d\n", addr_p, ntohs(sin.sin_port)); 
            printf("content is : %s\n", buf); 
        
            my_fun(buf); 
        
            n = sendto(c_fd, buf, n, 0, (struct sockaddr *) &cin, len);
            if (n == -1){
                    perror("fail to send\n");
                    exit(1);
            }

    }
    close(c_fd);
    printf("tcp_server closed\n");

    if(close(l_fd) == -1){
        perror("fail to close");
        exit(1);
    }
    return 0; 
}

static int udp_server_f(void)
{
	int			sockfd, clilen, n;
	struct sockaddr_in	servaddr, cliaddr;
        char				request[REQUEST], reply[REPLY];
        char addr_p[INET_ADDRSTRLEN];
        
        sockfd = socket(AF_INET, SOCK_DGRAM, 0);
        if(sockfd < 0)
                perror("socket error\n");
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family      = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port        = htons(8000);
        bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

        while(1) {
                clilen = sizeof(cliaddr);
                if ( (n = recvfrom(sockfd, request, REQUEST, 0,
						   (struct sockaddr *) &cliaddr, &clilen)) < 0)
			perror("recvfrom error");

                inet_ntop(AF_INET, &cliaddr.sin_addr, addr_p, sizeof(addr_p)); 
                printf("client IP is %s, port is %d\n", addr_p, ntohs(servaddr.sin_port)); 
                printf("content is : %s\n", request); 
        
                my_fun(request); 
        
                n = sendto(sockfd, request, n, 0, (struct sockaddr *) &cliaddr, clilen);
                if (n == -1){
                        perror("fail to send\n");
                        exit(1);
                }

        }
        close(sockfd);
        printf("udp_server closed\n");

}



