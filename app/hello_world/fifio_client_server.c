#include "fifio_client_server.h"
#include <signal.h>

static char clientFifo[CLIENT_FIFO_NAME_LEN];

static void             /* Invoked on exit to delete client FIFO */
removeFifo(void)
{
    unlink(clientFifo);
}

int fifo_client()
{
    int serverFd, clientFd;
    struct request req;
    struct response resp;

    char argc = 2;
    
    /* Create our FIFO (before sending request, to avoid a race) */
    umask(0);       /* So we get the permissions we want */
    snprintf(clientFifo, CLIENT_FIFO_NAME_LEN, CLIENT_FIFO_TEMPLATE,
             (long) getpid());
    
    if (mkfifo(clientFifo, S_IRUSR | S_IWUSR | S_IWGRP) == -1
        && errno != EEXIST)
        errExit("mkfifo %s", clientFifo);

    if (atexit(removeFifo) != 0)
        errExit("atexit");

    /* Construct request message, open server FIFO, and send message */
    req.pid = getpid();
    req.seqLen = (argc > 1) ? getInt("2", GN_GT_0, "seq-len") : 1;
    
    serverFd = open(SERVER_FIFO, O_WRONLY);
    
    if (serverFd == -1)
        errExit("open %s", SERVER_FIFO);

    if (write(serverFd, &req, sizeof(struct request)) !=
        sizeof(struct request))
        fatal("Can't write to server");

    /* Open our FIFO, read and display response */
    clientFd = open(clientFifo, O_RDONLY);
    
    if (clientFd == -1)
        errExit("open %s", clientFifo);

    if (read(clientFd, &resp, sizeof(struct response))
        != sizeof(struct response))
        fatal("Can't read response from server");

    printf("%d\n", resp.seqNum);
    /* exit(EXIT_SUCCESS); */
}

int fifo_server()
{
    int serverFd, dummyFd, clientFd;
    char clientFifo[CLIENT_FIFO_NAME_LEN];
    struct request req;
    struct response resp;
    int seqNum = 0;                     /* This is our "service" */

    /* Create well-known FIFO, and open it for reading */
    umask(0);                           /* So we get the permissions we want */
    
    if (mkfifo(SERVER_FIFO, S_IRUSR | S_IWUSR | S_IWGRP) == -1
        && errno != EEXIST)
        errExit("mkfifo %s", SERVER_FIFO);
    
    serverFd = open(SERVER_FIFO, O_RDONLY);
    
    if (serverFd == -1)
        errExit("open %s", SERVER_FIFO);
    
    /* Open an extra write descriptor, so that we never see EOF */
    dummyFd = open(SERVER_FIFO, O_WRONLY);
    
    if (dummyFd == -1)
        errExit("open %s", SERVER_FIFO);

    if (signal(SIGPIPE, SIG_IGN) == SIG_ERR)    errExit("signal");

    for (;;) {  /* Read requests and send responses */
        
        if (read(serverFd, &req, sizeof(struct request))
            != sizeof(struct request)) {
            fprintf(stderr, "Error reading request; discarding\n");
            continue;                   /* Either partial read or error */
        }

        /* Open client FIFO (previously created by client) */
        snprintf(clientFifo, CLIENT_FIFO_NAME_LEN, CLIENT_FIFO_TEMPLATE,
                 (long) req.pid);
        clientFd = open(clientFifo, O_WRONLY);
        if (clientFd == -1) {           /* Open failed, give up on client */
            errMsg("open %s", clientFifo);
            continue;
        }

        /* Send response and close FIFO */
        resp.seqNum = seqNum;
        if (write(clientFd, &resp, sizeof(struct response))
            != sizeof(struct response))
            fprintf(stderr, "Error writing to FIFO %s\n", clientFifo);
        if (close(clientFd) == -1)
            errMsg("close");

        seqNum += req.seqLen;           /* Update our sequence number */
    }
}














