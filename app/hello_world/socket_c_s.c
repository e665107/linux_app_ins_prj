#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>

#define MAX_LINE 100

/*

 */
int client_f(void)
{
    struct sockaddr_in sin;
    char buf[MAX_LINE];
    int sfd;
    int port = 8000;
    char *str = "socket communication"; 
    socklen_t addr_len;
    int n; 
   
    bzero(&sin, sizeof(sin));
    sin.sin_family = AF_INET;
    /*convert IPv4 and IPv6 addresses from text to
      binary form  */
    inet_pton(AF_INET, "127.0.0.1", &sin.sin_addr); 
    sin.sin_port = htons(port);  /* convert values to network byte order */
    sfd = socket(AF_INET, SOCK_STREAM, 0);  /* create a socket */
    
    connect(sfd, (struct sockaddr_in *)&sin, sizeof(sin)); 

    /* n = sendto(sfd, str, strlen(str) + 1, 0, (struct sockaddr *) &sin, sizeof(sin)); */
    write(sfd, str, strlen(str) + 1);
    /* read(sfd, buf, MAX_LINE); */
    /* if(n == -1){ */
    /*     perror("fail to send\n"); */
    /*     exit(1); */
    /* } */

    sleep(5);
    addr_len = sizeof(sin);
    
    n = recvfrom(sfd, buf, MAX_LINE, 0, (struct sockaddr *) &sin, &addr_len);
    if(n == -1){
        perror("fail to receive\n");
        exit(1);
    }else
        printf("recive from server: %s\n", buf); 

    close(sfd); 
    
    return 0;
}

void my_fun(char * p)
{
    if(p == NULL) 
        return;
    
    for (; *p != '\0'; p++)
        if(*p >= 'A' && *p <= 'Z') 
            *p = *p -'A'+ 'a';
}

/*

 */
int server_f(void)
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
    
    while(1){
        c_fd = accept(l_fd, (struct sockaddr *) &cin, &len); 
        
        n = read(c_fd, buf, MAX_LINE); 
        
        inet_ntop(AF_INET, &cin.sin_addr, addr_p, sizeof(addr_p)); 
        printf("client IP is %s, port is %d\n", addr_p, ntohs(sin.sin_port)); 
        printf("content is : %s\n", buf); 
        
        my_fun(buf); 
        
        /* write(c_fd, buf, n);  */
        n = sendto(c_fd, buf, n, 0, (struct sockaddr *) &cin, len);
        if (n == -1){
            perror("fail to send\n");
            exit(1);
        }
    
        close(c_fd); 
    }
    
    if(close(l_fd) == -1){
        perror("fail to close");
        exit(1);
    }
    
    return 0; 
}

