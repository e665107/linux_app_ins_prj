#include <signal.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <sys/epoll.h>
#define _GNU_SOURCE     /* Obtain O_DIRECT definition from <fcntl.h> */
#define _BSD_SOURCE     /* Get getpass() declaration from <unistd.h> */
#define _XOPEN_SOURCE       /* See feature_test_macros(7) */       

#include <fcntl.h>
#include <time.h>
#include <utime.h>
#include <poll.h>
#include <sys/select.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include <stddef.h>
#include <dirent.h>
#include <libgen.h>
#include <malloc.h>
#include <sys/statvfs.h>
#include <sys/inotify.h>
#include <limits.h>
#include <sys/wait.h>
#include <sys/mman.h>
/* #define _GNU_SOURCE         /\* See feature_test_macros(7) *\/ */
#include <crypt.h>

#include <sys/utsname.h>

#define __USE_XOPEN_EXTENDED
#include <sys/xattr.h>
#include <shadow.h>
#include <pwd.h>

#include <ftw.h>
#include "tlpi_hdr.h"
#include "error_functions.h"

#include "misc_f1.h"



/* #define _XOPEN_SOURCE 600   /\* Get nftw() and S_IFSOCK declarations *\/ */
/* #define __USE_XOPEN_EXTENDED */

#define MAX_BUF     1000        /* Maximum bytes fetched by a single read() */

#define MAX_EVENTS     5        /* Maximum number of events to be returned from a single epoll_wait() call */

#define BUF_SIZE 200

#define MAX_MTEXT 400

#define CMD_SIZE 200

#define BUF_LEN (10 * (sizeof(struct inotify_event) + NAME_MAX + 1))


struct pbuf {
    int msqid;                  /* Origin of message */
    int len;                    /* Number of bytes used in mtext */
    long mtype;                 /* Message type */
    char mtext[MAX_MTEXT];      /* Message body */
};

static int pfd[2];                      /* File descriptors for pipe */

static int numReg = 0, numDir = 0, numSymLk = 0, numSocket = 0,
    numFifo = 0, numChar = 0, numBlock = 0,
    numNonstatable = 0;

static void sigwinchHandler(int sig)
{
    printf("sigwinch_handler\n");

    /* return ; */
}

/*
  terminal window size changed will produce the signal
  can't return from the pause
*/
static int sigwinch_f(void)
{
    struct winsize ws;
    struct sigaction sa;

    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sa.sa_handler = sigwinchHandler;
    if (sigaction(SIGWINCH, &sa, NULL) == -1)
        errExit("sigaction");
    
    for (;;) {
        pause();                        /* Wait for SIGWINCH signal */
        if (ioctl(STDIN_FILENO, TIOCGWINSZ, &ws) == -1)
            errExit("ioctl");
        printf("Caught SIGWINCH, new window size: "
               "%d rows * %d columns\n", ws.ws_row, ws.ws_col);
    }
}

static int epoll_input_f()
{
    int epfd, ready, fd, s, j, numOpenFds;
    struct epoll_event ev;
    struct epoll_event evlist[MAX_EVENTS];
    char buf[MAX_BUF];
    char argc = 3;
    char *argv[3] = {"build/temp.txt", "build/temp1.txt", "build/temp2.txt"};

    epfd = epoll_create(argc);
    if (epfd == -1)
        errExit("epoll_create");

    /* Open each file on command line, and add it to the "interest
       list" for the epoll instance */
    for (j = 0; j < argc; j++) {
        fd = open(argv[j], O_RDWR | O_CREAT);
        if (fd == -1)
            errExit("open");
        printf("Opened \"%s\" on fd %d\n", argv[j], fd);

        ev.events = EPOLLIN;            /* Only interested in input events */
        ev.data.fd = fd;
        if (epoll_ctl(epfd, EPOLL_CTL_ADD, fd, &ev) == -1)
            errExit("epoll_ctl");
    }

    numOpenFds = argc - 1;

    while (numOpenFds > 0) {
        /* Fetch up to MAX_EVENTS items from the ready list of the
           epoll instance */
        printf("About to epoll_wait()\n");
        ready = epoll_wait(epfd, evlist, MAX_EVENTS, -1);
        if (ready == -1) {
            if (errno == EINTR)
                continue;               /* Restart if interrupted by signal */
            else
                errExit("epoll_wait");
        }
        printf("Ready: %d\n", ready);

        /* Deal with returned list of events */
        for (j = 0; j < ready; j++) {
            printf("  fd=%d; events: %s%s%s\n", evlist[j].data.fd,
                   (evlist[j].events & EPOLLIN)  ? "EPOLLIN "  : "",
                   (evlist[j].events & EPOLLHUP) ? "EPOLLHUP " : "",
                   (evlist[j].events & EPOLLERR) ? "EPOLLERR " : "");
            if (evlist[j].events & EPOLLIN) {
                s = read(evlist[j].data.fd, buf, MAX_BUF);
                if (s == -1)
                    errExit("read");
                printf("    read %d bytes: %.*s\n", s, s, buf);

            } else if (evlist[j].events & (EPOLLHUP | EPOLLERR)) {

                /* After the epoll_wait(), EPOLLIN and EPOLLHUP may both have
                   been set. But we'll only get here, and thus close the file
                   descriptor, if EPOLLIN was not set. This ensures that all
                   outstanding input (possibly more than MAX_BUF bytes) is
                   consumed (by further loop iterations) before the file
                   descriptor is closed. */
                printf("    closing fd %d\n", evlist[j].data.fd);
                if (close(evlist[j].data.fd) == -1)
                    errExit("close");
                numOpenFds--;
            }
        }
    }

    printf("All file descriptors closed; bye\n");
    exit(EXIT_SUCCESS);
}

static int poll_f()
{
    int numPipes, j, ready, randPipe, numWrites;
    int (*pfds)[2];                     /* File descriptors for all pipes */
    int argc = 3;
    
    struct pollfd *pollFd;

    /* Allocate the arrays that we use. The arrays are sized according
       to the number of pipes specified on command line */
    numPipes = getInt("3", GN_GT_0, "num-pipes");

    pfds = calloc(numPipes, sizeof(int [2]));
    
    if (pfds == NULL)
        errExit("calloc");
    pollFd = calloc(numPipes, sizeof(struct pollfd));
    if (pollFd == NULL)
        errExit("calloc");

    /* Create the number of pipes specified on command line */
    for (j = 0; j < numPipes; j++)
        if (pipe(pfds[j]) == -1)
            errExit("pipe %d", j);

    /* Perform specified number of writes to random pipes */
    numWrites = (argc > 2) ? getInt("3", GN_GT_0, "num-writes") : 1;
    srandom((int) time(NULL));
    
    for (j = 0; j < numWrites; j++) {
        randPipe = random() % numPipes;
        printf("Writing to fd: %3d (read fd: %3d)\n",
               pfds[randPipe][1], pfds[randPipe][0]);
        if (write(pfds[randPipe][1], "a", 1) == -1)
            errExit("write %d", pfds[randPipe][1]);
    }
    
    /* Build the file descriptor list to be supplied to poll(). This list
       is set to contain the file descriptors for the read ends of all of
       the pipes. */
    for (j = 0; j < numPipes; j++) {
        pollFd[j].fd = pfds[j][0];
        pollFd[j].events = POLLIN;
    }

    ready = poll(pollFd, numPipes, 0);
    
    if (ready == -1)
        errExit("poll");

    printf("poll() returned: %d\n", ready);

    /* Check which pipes have data available for reading */
    for (j = 0; j < numPipes; j++)
        if (pollFd[j].revents & POLLIN)
            printf("Readable: %3d\n", pollFd[j].fd);

    exit(EXIT_SUCCESS);
}

static void childMon(int msqid, int fd)
{
    struct pbuf pmsg;
    ssize_t msgLen;
    size_t wlen;

    for (;;) {
        
        msgLen = msgrcv(msqid, &pmsg.mtype, MAX_MTEXT, 0, 0);
        
        if (msgLen == -1)
            errExit("msgrcv");
        /* We add some info to the message read by msgrcv() before
           writing to the pipe. */

        pmsg.msqid = msqid;
        pmsg.len = msgLen;      /* So parent knows how much to read from pipe */

        wlen = offsetof(struct pbuf, mtext) + msgLen;
        /* Or: wlen = &pmsg.mtext - &pmsg + msgLen */
        if (write(fd, &pmsg, wlen) != wlen)
            fatal("partial/failed write to pipe");
    }
}

static int select_mq_f()
{
    fd_set readfds;
    int ready, nfds, j;
    int pfd[2];                 /* Pipe used to transfer messages from
                                   children to parent */
    int argc = 2;
    
    ssize_t numRead;
    char buf[BUF_SIZE];
    struct pbuf pmsg;

    if (pipe(pfd) == -1)
        errExit("pipe");

    /* Create one child for each message queue being monitored */
    for (j = 1; j < argc; j++) {
        switch (fork()) {
            case -1:
                errMsg("fork");
                killpg(0, SIGTERM);
                _exit(EXIT_FAILURE);        /* NOTREACHED */

            case 0:
                childMon(getInt("3", 0, "msqid"), pfd[1]);
                _exit(EXIT_FAILURE);        /* NOTREACHED */

            default:
                break;
        }
    }

    /* Parent falls through to here */
    for (;;) {
        FD_ZERO(&readfds);
        FD_SET(STDIN_FILENO, &readfds);
        FD_SET(pfd[0], &readfds);
        nfds = max(STDIN_FILENO, pfd[0]) + 1;

        ready = select(nfds, &readfds, NULL, NULL, NULL);
        
        if (ready == -1)
            errExit("select");

        /* Check if terminal fd is ready */
        if (FD_ISSET(STDIN_FILENO, &readfds)) {
            numRead = read(STDIN_FILENO, buf, BUF_SIZE - 1);
            if (numRead == -1)
                errExit("read stdin");
            buf[numRead] = '\0';
            printf("Read from terminal: %s", buf);
            if (numRead > 0 && buf[numRead - 1] != '\n')
                printf("\n");
        }

        /* Check if pipe fd is ready */
        if (FD_ISSET(pfd[0], &readfds)) {
            numRead = read(pfd[0], &pmsg, offsetof(struct pbuf, mtext));
            if (numRead == -1)
                errExit("read pipe");
            
            if (numRead == 0)
                fatal("EOF on pipe");

            numRead = read(pfd[0], &pmsg.mtext, pmsg.len);
            
            if (numRead == -1)
                errExit("read pipe");
            if (numRead == 0)
                fatal("EOF on pipe");

            printf("MQ %d: type=%ld length=%d <%.*s>\n", pmsg.msqid,
                   pmsg.mtype, pmsg.len, pmsg.len, pmsg.mtext);
        }
    }
}

static void handler(int sig)
{
    int savedErrno;                     /* In case we change 'errno' */
    savedErrno = errno;
    if (write(pfd[1], "x", 1) == -1 && errno != EAGAIN)
        errExit("write");
    errno = savedErrno;
}

static int self_pipe_f()
{
    fd_set readfds;
    int ready, nfds, flags;
    struct timeval timeout;
    struct timeval *pto;
    struct sigaction sa;
    char ch;
    int fd, j;
    int argc = 3;
    char *argv[] = {"", "10", "3"};
    
    /* Initialize 'timeout', 'readfds', and 'nfds' for select() */
    if (strcmp(argv[1], "-") == 0) {
        pto = NULL;                     /* Infinite timeout */
    } else {
        pto = &timeout;
        timeout.tv_sec = getLong(argv[1], 0, "timeout");
        timeout.tv_usec = 0;            /* No microseconds */
    }

    nfds = 0;
    /* Build the 'readfds' from the fd numbers given in command line */
    FD_ZERO(&readfds);
    
    for (j = 2; j < argc; j++) {
        fd = getInt(argv[j], 0, "fd");
        
        if (fd >= FD_SETSIZE)
            cmdLineErr("file descriptor exceeds limit (%d)\n", FD_SETSIZE);
        if (fd >= nfds)
            nfds = fd + 1;              /* Record maximum fd + 1 */
        FD_SET(fd, &readfds);
    }

    if (pipe(pfd) == -1)
        errExit("pipe");

    FD_SET(pfd[0], &readfds);           /* Add read end of pipe to 'readfds' */
    nfds = max(nfds, pfd[0] + 1);       /* And adjust 'nfds' if required */
    flags = fcntl(pfd[0], F_GETFL);
    
    if (flags == -1)
        errExit("fcntl-F_GETFL");
    flags |= O_NONBLOCK;                /* Make read end nonblocking */
    if (fcntl(pfd[0], F_SETFL, flags) == -1)
        errExit("fcntl-F_SETFL");

    flags = fcntl(pfd[1], F_GETFL);
    
    if (flags == -1)
        errExit("fcntl-F_GETFL");
    flags |= O_NONBLOCK;                /* Make write end nonblocking */
    if (fcntl(pfd[1], F_SETFL, flags) == -1)
        errExit("fcntl-F_SETFL");

    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;           /* Restart interrupted reads()s */
    sa.sa_handler = handler;
    
    if (sigaction(SIGINT, &sa, NULL) == -1)
        errExit("sigaction");

    while ((ready = select(nfds, &readfds, NULL, NULL, pto)) == -1 &&
           errno == EINTR)
        continue;                       /* Restart if interrupted by signal */
    if (ready == -1)                    /* Unexpected error */
        errExit("select");

    if (FD_ISSET(pfd[0], &readfds)) {   /* Handler was called */
        printf("A signal was caught\n");

        for (;;) {                      /* Consume bytes from pipe */
            
            if (read(pfd[0], &ch, 1) == -1) {
                if (errno == EAGAIN)
                    break;              /* No more bytes */
                else
                    errExit("read");    /* Some other error */
            }
            /* Perform any actions that should be taken in response to signal */
            printf("ch = %c\n", ch);

        }
    }

    /* Examine file descriptor sets returned by select() to see
       which other file descriptors are ready */
    printf("ready = %d\n", ready);
    
    for (j = 2; j < argc; j++) {
        fd = getInt(argv[j], 0, "fd");
        printf("%d: %s\n", fd, FD_ISSET(fd, &readfds) ? "r" : "");
    }

    /* And check if read end of pipe is ready */
    printf("%d: %s   (read end of pipe)\n", pfd[0],
           FD_ISSET(pfd[0], &readfds) ? "r" : "");

    if (pto != NULL)
        printf("timeout after select(): %ld.%03ld\n",
               (long) timeout.tv_sec, (long) timeout.tv_usec / 1000);

    exit(EXIT_SUCCESS);
}


static int symlink_f()
{
    int fd;
    
    umask(0);
    if (mkdir("build/tst", S_IRUSR | S_IWUSR | S_IXUSR) == -1)
        errExit("mkdir");
    if (chdir("build/tst") == -1)
        errExit("chdir");
    
    fd = open("myfile", O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
    
    if (fd == -1)
        errExit("open");
    if (close(fd) == -1)
        errExit("close");
    if (symlink("myfile", "../mylink") == -1)
        errExit("symlink");
    
    /* if (chmod("../mylink", S_IRUSR) == -1) */
    /*     errExit("chmod"); */
    
    exit(EXIT_SUCCESS);
}

static int countFile(const char *path, const struct stat *sb, int flag, struct FTW *ftwb)

{
    if (flag == FTW_NS) {
        numNonstatable++;
        return 0;
    }

    switch (sb->st_mode & S_IFMT) {
        case S_IFREG:  numReg++;    break;
        case S_IFDIR:  numDir++;    break;
        case S_IFCHR:  numChar++;   break;
        case S_IFBLK:  numBlock++;  break;
        case S_IFLNK:  numSymLk++;  break;
        case S_IFIFO:  numFifo++;   break;
        case S_IFSOCK: numSocket++; break;
    }
    return 0;           /* Always tell nftw() to continue */
}

static void printStats(const char *msg, int num, int numFiles)
{
    printf("%-15s   %6d %6.1f%%\n", msg, num, num * 100.0 / numFiles);
}

#if 0
static int file_type_stats_f()
{
    int numFiles;       /* Total number of files */

    /* Traverse directory tree counting files; don't follow symbolic links */
    if (nftw("build/", &countFile, 20, FTW_PHYS) == -1) {
        perror("nftw");
        exit(EXIT_FAILURE);
    }

    numFiles = numReg + numDir + numSymLk + numSocket +
               numFifo + numChar + numBlock + numNonstatable;

    if (numFiles == 0) {
        printf("No files found\n");
    } else {
        printf("Total files:      %6d\n", numFiles);
        printStats("Regular:", numReg, numFiles);
        printStats("Directory:", numDir, numFiles);
        printStats("Char device:", numChar, numFiles);
        printStats("Block device:", numBlock, numFiles);
        printStats("Symbolic link:", numSymLk, numFiles);
        printStats("FIFO:", numFifo, numFiles);
        printStats("Socket:", numSocket, numFiles);
        printStats("Non-statable:", numNonstatable, numFiles);
    }
    exit(EXIT_SUCCESS);
}
#endif

static void listFiles(const char *dirpath)/* List all files in directory 'dirpath' */
{
    DIR *dirp;
    struct dirent *dp;
    Boolean isCurrent;          /* True if 'dirpath' is "." */

    isCurrent = strcmp(dirpath, ".") == 0;

    dirp = opendir(dirpath);
    
    if (dirp  == NULL) {
        errMsg("opendir failed on '%s'", dirpath);
        return;
    }

    /* For each entry in this directory, print directory + filename */
    for (;;) {
        errno = 0;              /* To distinguish error from end-of-directory */
        dp = readdir(dirp);
        if (dp == NULL)
            break;

        if (strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0)
            continue;           /* Skip . and .. */

        if (!isCurrent)
            printf("%s/", dirpath);
        printf("%s\n", dp->d_name);
    }

    if (errno != 0)
        errExit("readdir");

    if (closedir(dirp) == -1)
        errMsg("closedir");
}


static int list_files_f()
{
    char argc = 3;
    char *argv[] = {" ", "build"};
    
    if (argc == 1)              /* No arguments - use current directory */
         listFiles(".");
    else
        listFiles(argv[1]);

#if 0
        for (argv++; *argv; argv++)
        {
            printf("*argv=%s", argv);
            listFiles(*argv);
        }
#endif
    exit(EXIT_SUCCESS);
}


static void usageError(const char *progName, const char *msg)
{
    if (msg != NULL)
        fprintf(stderr, "%s\n", msg);
    fprintf(stderr, "Usage: %s [-d] [-m] [-p] [directory-path]\n", progName);
    fprintf(stderr, "\t-d Use FTW_DEPTH flag\n");
    fprintf(stderr, "\t-m Use FTW_MOUNT flag\n");
    fprintf(stderr, "\t-p Use FTW_PHYS flag\n");
    
    exit(EXIT_FAILURE);
}

static int dirTree(const char *pathname, const struct stat *sbuf, int type,
                   struct FTW *ftwb)   /* Function called by nftw() */
{
    if (type == FTW_NS) {                  /* Could not stat() file */
        printf("?");
    } else {
        switch (sbuf->st_mode & S_IFMT) {  /* Print file type */
            case S_IFREG:  printf("-"); break;
            case S_IFDIR:  printf("d"); break;
            case S_IFCHR:  printf("c"); break;
            case S_IFBLK:  printf("b"); break;
            case S_IFLNK:  printf("l"); break;
            case S_IFIFO:  printf("p"); break;
            case S_IFSOCK: printf("s"); break;
            default:       printf("?"); break; /* Should never happen (on Linux) */
        }
    }

    printf(" %s  ", (type == FTW_D)  ? "D  " : (type == FTW_DNR) ? "DNR" :
           (type == FTW_DP) ? "DP " : (type == FTW_F)   ? "F  " :
           (type == FTW_SL) ? "SL " : (type == FTW_SLN) ? "SLN" :
           (type == FTW_NS) ? "NS " : "  ");
    if (type != FTW_NS)
        printf("%7ld ", (long) sbuf->st_ino);
    else
        printf("        ");
    
    printf(" %*s", 4 * ftwb->level, "");        /* Indent suitably */
    printf("%s\n",  &pathname[ftwb->base]);     /* Print basename */
    return 0;                                   /* Tell nftw() to continue */
}

#if 0  /* undo */
static int nftw_dir_tree_f()
{
    int flags, opt;
    int argc = 3;
    
    flags = 0;
    
    while ((opt = getopt(2, "-d", "dmp")) != -1) {
        switch (opt) {
            case 'd': flags |= FTW_DEPTH;   break;
            case 'm': flags |= FTW_MOUNT;   break;
            case 'p': flags |= FTW_PHYS;    break;
            default:  usageError("nftw_dir_tree_f", NULL);
        }
    }

    if (argc > optind + 1)
        usageError("nftw_dir_tree_f", NULL);

    if (nftw((argc > optind) ? "-d" : ".", dirTree, 10, flags) == -1) {
        perror("nftw");
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}
#endif

/* strdup---use malloc*/
static int t_dirbasename_f()
{
    char *t1, *t2;
    int j;
    char argc = 3;
    char *argv[] = {"--", "hello", "world"};
    
    for (j = 1; j < argc; j++)  {
        t1 = strdup(argv[j]);
        if (t1 == NULL)
            errExit("strdup");
        t2 = strdup(argv[j]);
        if (t2 == NULL)
            errExit("strdup");

        printf("%s ==> %s + %s\n", argv[j], dirname(t1), basename(t2));

        free(t1);
        free(t2);
    }

    exit(EXIT_SUCCESS);
}

#if 0
static int t_unlink_f()
{
    int fd, j, numBlocks;
    char shellCmd[CMD_SIZE];            /* Command to be passed to system() */
    char buf[BUF_SIZE];                 /* Random bytes to write to file */
    char argc = 3;
    char *argv[] = {"--", "build/test", "100"};
#if 0
    if (argc < 2 || strcmp(argv[1], "--help") == 0)
        usageErr("%s temp-file [num-1kB-blocks] \n", argv[0]);
#endif
    
    numBlocks = (argc > 2) ? getInt(argv[2], GN_GT_0, "num-1kB-blocks")
                : 100000;

    fd = open(argv[1], O_WRONLY | O_CREAT | O_EXCL, S_IRUSR | S_IWUSR);
    if (fd == -1)
        errExit("open");

    if (unlink(argv[1]) == -1)          /* Remove filename */
        errExit("unlink");

    for (j = 0; j < numBlocks; j++)     /* Write lots of junk to file */
        if (write(fd, buf, BUF_SIZE) != BUF_SIZE)
            fatal("partial/failed write");

    snprintf(shellCmd, CMD_SIZE, "df -k `dirname %s`", argv[1]);
    system(shellCmd);                   /* View space used in file system */

    if (close(fd) == -1)                /* File is now destroyed */
        errExit("close");
    printf("********** Closed file descriptor\n");

    system(shellCmd);                   /* Review space used in file system */
    exit(EXIT_SUCCESS);
}
#endif

#if 0
static int view_symlink_f()
{
    struct stat statbuf;
    char buf[BUF_SIZE];
    ssize_t numBytes;
    char argc = 3;
    char* argv[] = {"--", " ", " "};
    
    if (argc != 2 || strcmp(argv[1], "--help") == 0)
        usageErr("%s pathname\n", argv[0]);

    if (lstat(argv[1], &statbuf) == -1)
        errExit("lstat");

    if (!S_ISLNK(statbuf.st_mode))
        fatal("%s is not a symbolic link", argv[1]);

    numBytes = readlink(argv[1], buf, BUF_SIZE - 1);
    if (numBytes == -1)
        errExit("readlink");
    buf[numBytes] = '\0';                       /* Add terminating null byte */
    printf("readlink: %s --> %s\n", argv[1], buf);

    if (realpath(argv[1], buf) == NULL)
        errExit("realpath");
    printf("realpath: %s --> %s\n", argv[1], buf);

    exit(EXIT_SUCCESS);
}
#endif

#if 0
static int direct_read_f()
{
    int fd;
    ssize_t numRead;
    size_t length, alignment;
    off_t offset;
    char *buf;
    char argc = 5;
    length = getLong("10", GN_ANY_BASE, "length");
    offset = (argc > 3) ? getLong("10", GN_ANY_BASE, "offset") : 0;
    alignment = (argc > 4) ? getLong("4", GN_ANY_BASE, "alignment") : 4096;

    fd = open("build/test3.txt", O_RDONLY | O_DIRECT);
    
    if (fd == -1)
        errExit("open");

    /* memalign() allocates a block of memory aligned on an address that
       is a multiple of its first argument. By specifying this argument as
       2 * 'alignment' and then adding 'alignment' to the returned pointer,
       we ensure that 'buf' is aligned on a non-power-of-two multiple of
       'alignment'. We do this to ensure that if, for example, we ask
       for a 256-byte aligned buffer, we don't accidentally get
       a buffer that is also aligned on a 512-byte boundary. */

    buf = memalign(alignment * 2, length + alignment);
    
    if (buf == NULL)
        errExit("memalign");

    buf += alignment;

    if (lseek(fd, offset, SEEK_SET) == -1)
        errExit("lseek");

    numRead = read(fd, buf, length);
    if (numRead == -1)
        errExit("read");
    printf("Read %ld bytes\n", (long) numRead);

    exit(EXIT_SUCCESS);
}
#endif


static int mix23io_f()
{
    char argc = 3;
    printf("To man the world is twofold, ");
    if (argc > 1)
        printf("\n");
    write(STDOUT_FILENO, "in accordance with his twofold attitude.\n", 41);

    exit(EXIT_SUCCESS);
}

#if 0
static int write_bytes_f()
{
    size_t bufSize, numBytes, thisWrite, totWritten;
    char *buf;
    int fd, openFlags;

     numBytes = getLong(argv[2], GN_GT_0, "num-bytes");
     bufSize = getLong(argv[3], GN_GT_0, "buf-size");

     buf = malloc(bufSize);
     if (buf == NULL)
        errExit("malloc");

    openFlags = O_CREAT | O_WRONLY;

#if defined(USE_O_SYNC) && defined(O_SYNC)
    openFlags |= O_SYNC;
#endif

    fd = open(argv[1], openFlags, S_IRUSR | S_IWUSR);
    if (fd == -1)
        errExit("open");

    for (totWritten = 0; totWritten < numBytes;
         totWritten += thisWrite) {
        thisWrite = min(bufSize, numBytes - totWritten);

        if (write(fd, buf, thisWrite) != thisWrite)
            fatal("partial/failed write");

#ifdef USE_FSYNC
        if (fsync(fd))
            errExit("fsync");
#endif
#ifdef USE_FDATASYNC
        if (fdatasync(fd))
            errExit("fdatasync");
#endif
    }

    if (close(fd) == -1)
        errExit("close");
    exit(EXIT_SUCCESS);
}
#endif

#if 0
static int multi_descriptors_f()
{
    int fd1, fd2, fd3;
#define file "a"
    char cmd[] = "cat " file "; echo";

    fd1 = open(file, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (fd1 == -1)
        errExit("open fd1");
    fd2 = dup(fd1);
    if (fd2 == -1)
        errExit("dup");
    fd3 = open(file, O_RDWR);
    if (fd3 == -1)
        errExit("open fd3");

    /* 'fd1' and 'fd2' share same open file table entry (and thus file
       offset). 'fd3' has its own open file table entry, and thus a
       separate file offset. */

    if (write(fd1, "Hello,", 6) == -1)
        errExit("write1");
    system(cmd);
    if (write(fd2, " world", 6) == -1)
        errExit("write2");
    system(cmd);
    if (lseek(fd2, 0, SEEK_SET) == -1)
        errExit("lseek");
    if (write(fd1, "HELLO,", 6) == -1)
        errExit("write3");
    system(cmd);
    if (write(fd3, "Gidday", 6) == -1)
        errExit("write4");
    system(cmd);
    if (close(fd1) == -1)
        errExit("close output");
    if (close(fd2) == -1)
        errExit("close output");
    if (close(fd3) == -1)
        errExit("close output");
    exit(EXIT_SUCCESS);
}
#endif

#if 0
static int readv_f()
{
    int fd;
    struct iovec iov[3];
    struct stat myStruct;       /* First buffer */
    int x;                      /* Second buffer */
#define STR_SIZE 100
    char str[STR_SIZE];         /* Third buffer */
    ssize_t numRead, totRequired;

    if (argc != 2 || strcmp(argv[1], "--help") == 0)
        usageErr("%s file\n", argv[0]);

    fd = open(argv[1], O_RDONLY);
    if (fd == -1)
        errExit("open");

    totRequired = 0;

    iov[0].iov_base = &myStruct;
    iov[0].iov_len = sizeof(struct stat);
    totRequired += iov[0].iov_len;

    iov[1].iov_base = &x;
    iov[1].iov_len = sizeof(x);
    totRequired += iov[1].iov_len;

    iov[2].iov_base = str;
    iov[2].iov_len = STR_SIZE;
    totRequired += iov[2].iov_len;

    numRead = readv(fd, iov, 3);
    if (numRead == -1)
        errExit("readv");

    if (numRead < totRequired)
        printf("Read fewer bytes than requested\n");

    printf("total bytes requested: %ld; bytes read: %ld\n",
           (long) totRequired, (long) numRead);
    exit(EXIT_SUCCESS);
}
#endif

#if 0
static int utime_f()
{
    char *pathname;
    struct stat sb;
    struct utimbuf utb;

     pathname = argv[1];

     if (stat(pathname, &sb) == -1)    /* Retrieve current file times */
        errExit("stat");

    utb.actime = sb.st_atime;         /* Leave access time unchanged */
    utb.modtime = sb.st_atime;        /* Make modify time same as access time */
    if (utime(pathname, &utb) == -1)  /* Update file times */
        errExit("utime");

    exit(EXIT_SUCCESS);
}
#endif


static int utimes_f()
{
    struct stat sb;
    struct timeval tv[2];

    if (stat("build/test3.txt", &sb) == -1)       /* Retrieve current file times */
        errExit("stat");

    tv[0].tv_sec = sb.st_atime;         /* Leave atime seconds unchanged */
    tv[0].tv_usec = 223344;             /* Change microseconds for atime */
    tv[1].tv_sec = sb.st_atime;         /* mtime seconds == atime seconds */
    tv[1].tv_usec = 667788;             /* mtime microseconds */

    if (utimes("build/test3.txt", tv) == -1)
        errExit("utimes");

    exit(EXIT_SUCCESS);
}


#if 0
static int mount_f(int argc, char *argv[])
{
    unsigned long flags;
    char *data, *fstype;
    int j, opt;

    flags = 0;
    data = NULL;
    fstype = NULL;

    while ((opt = getopt(argc, argv, "o:t:f:")) != -1) {
        switch (opt) {
            case 'o':
                data = optarg;
                break;

            case 't':
                fstype = optarg;
                break;

            case 'f':
                for (j = 0; j < strlen(optarg); j++) {
                    switch (optarg[j]) {
                        case 'b': flags |= MS_BIND;             break;
                        case 'd': flags |= MS_DIRSYNC;          break;
                        case 'l': flags |= MS_MANDLOCK;         break;
                        case 'm': flags |= MS_MOVE;             break;
                        case 'A': flags |= MS_NOATIME;          break;
                        case 'V': flags |= MS_NODEV;            break;
                        case 'D': flags |= MS_NODIRATIME;       break;
                        case 'E': flags |= MS_NOEXEC;           break;
                        case 'S': flags |= MS_NOSUID;           break;
                        case 'r': flags |= MS_RDONLY;           break;
                        case 'c': flags |= MS_REC;              break;
                        case 'R': flags |= MS_REMOUNT;          break;
                        case 's': flags |= MS_SYNCHRONOUS;      break;
                        default:  usageError(argv[0], NULL);
                    }
                }
                break;

            default:
                usageError(argv[0], NULL);
        }
    }

    if (argc != optind + 2)
        usageError(argv[0], "Wrong number of arguments\n");

    if (mount(argv[optind], argv[optind + 1], fstype, flags, data) == -1)
        errExit("mount");

    exit(EXIT_SUCCESS);
}
#endif

#if 0
static int statfs_f()
{
    struct statfs sfs;

    if (argc != 2 || strcmp(argv[1], "--help") == 0)
        usageErr("%s path\n", argv[0]);

    if (statfs(argv[1], &sfs) == -1)
        errExit("statfs");

    printf("File system type:              %#lx\n",
           (unsigned long) sfs.f_type);
    printf("Optimal I/O block size:        %lu\n",
           (unsigned long) sfs.f_bsize);
    printf("Total data blocks:             %lu\n",
           (unsigned long) sfs.f_blocks);
    printf("Free data blocks:              %lu\n",
           (unsigned long) sfs.f_bfree);
    printf("Free blocks for nonsuperuser:  %lu\n",
           (unsigned long) sfs.f_bavail);
    printf("Total i-nodes:                 %lu\n",
           (unsigned long) sfs.f_files);
    printf("File system ID:                %#x, %#x\n",
           (unsigned) sfs.f_fsid.__val[0], (unsigned) sfs.f_fsid.__val[1]);
    printf("Free i-nodes:                  %lu\n",
           (unsigned long) sfs.f_ffree);
    printf("Maximum file name length:      %lu\n",
           (unsigned long) sfs.f_namelen);

    exit(EXIT_SUCCESS);
}
#endif

#if 0
static int statvfs_f()
{
    struct statvfs sb;


    if (statvfs(argv[1], &sb) == -1)
        errExit("statvfs");

    printf("Block size                       %lu\n", sb.f_bsize);
    printf("Fundamental block size           %lu\n", sb.f_frsize);
    printf("Total blocks (in above units)    %lu\n",
           (unsigned long) sb.f_blocks);
    printf("Free blocks for priv. proc.      %lu\n",
           (unsigned long) sb.f_bfree);
    printf("Free blocks for unpriv. proc.    %lu\n",
           (unsigned long) sb.f_bavail);
    printf("Total number of i-nodes          %lu\n",
           (unsigned long) sb.f_files);
    printf("Free i-nodes for priv. proc.     %lu\n",
           (unsigned long) sb.f_ffree);
    printf("Free i-nodes for nonpriv. proc.  %lu\n",
           (unsigned long) sb.f_favail);
    printf("File system ID                   %#lx\n", sb.f_fsid);
    printf("Flags                            %#lx\n", sb.f_flag);
    printf("Maximum filename length          %lu\n", sb.f_namemax);

    exit(EXIT_SUCCESS);
}
#endif

#if 0
static int umount_f()
{
    if (argc != 2 || strcmp(argv[1], "--help") == 0)
        usageErr("%s mount-point\n", argv[0]);

    if (umount(argv[1]) == -1)
        errExit("umount");

    exit(EXIT_SUCCESS);
}
#endif

#if 0
static int getopt_f()
{
    int opt, xfnd;
    char *pstr;

    xfnd = 0;
    pstr = NULL;

    while ((opt = getopt(argc, argv, ":p:x")) != -1) {
        printf("opt =%3d (%c); optind = %d", opt, printable(opt), optind);
        if (opt == '?' || opt == ':')
            printf("; optopt =%3d (%c)", optopt, printable(optopt));
        printf("\n");

        switch (opt) {
            case 'p': pstr = optarg;        break;
            case 'x': xfnd++;               break;
            case ':': usageError(argv[0], "Missing argument", optopt);
            case '?': usageError(argv[0], "Unrecognized option", optopt);
            default:  fatal("Unexpected case in switch()");
        }
    }

    if (xfnd != 0)
        printf("-x was specified (count=%d)\n", xfnd);
    if (pstr != NULL)
        printf("-p was specified with the value \"%s\"\n", pstr);
    if (optind < argc)
        printf("First nonoption argument is \"%s\" at argv[%d]\n",
               argv[optind], optind);
    exit(EXIT_SUCCESS);
}
#endif

static void displayInotifyEvent(struct inotify_event *i) /* Display information from inotify_event structure */
{
    printf("    wd =%2d; ", i->wd);
    if (i->cookie > 0)
        printf("cookie =%4d; ", i->cookie);

    printf("mask = ");
    if (i->mask & IN_ACCESS)        printf("IN_ACCESS ");
    if (i->mask & IN_ATTRIB)        printf("IN_ATTRIB ");
    if (i->mask & IN_CLOSE_NOWRITE) printf("IN_CLOSE_NOWRITE ");
    if (i->mask & IN_CLOSE_WRITE)   printf("IN_CLOSE_WRITE ");
    if (i->mask & IN_CREATE)        printf("IN_CREATE ");
    if (i->mask & IN_DELETE)        printf("IN_DELETE ");
    if (i->mask & IN_DELETE_SELF)   printf("IN_DELETE_SELF ");
    if (i->mask & IN_IGNORED)       printf("IN_IGNORED ");
    if (i->mask & IN_ISDIR)         printf("IN_ISDIR ");
    if (i->mask & IN_MODIFY)        printf("IN_MODIFY ");
    if (i->mask & IN_MOVE_SELF)     printf("IN_MOVE_SELF ");
    if (i->mask & IN_MOVED_FROM)    printf("IN_MOVED_FROM ");
    if (i->mask & IN_MOVED_TO)      printf("IN_MOVED_TO ");
    if (i->mask & IN_OPEN)          printf("IN_OPEN ");
    if (i->mask & IN_Q_OVERFLOW)    printf("IN_Q_OVERFLOW ");
    if (i->mask & IN_UNMOUNT)       printf("IN_UNMOUNT ");
    printf("\n");

    if (i->len > 0)
        printf("        name = %s\n", i->name);
}

#if 0
static int inotify_f()
{
    int inotifyFd, wd, j;
    char buf[BUF_LEN] __attribute__ ((aligned(8)));
    ssize_t numRead;
    char *p;
    struct inotify_event *event;

     inotifyFd = inotify_init();                 /* Create inotify instance */
     if (inotifyFd == -1)
        errExit("inotify_init");

    for (j = 1; j < argc; j++) {
        wd = inotify_add_watch(inotifyFd, argv[j], IN_ALL_EVENTS);
        if (wd == -1)
            errExit("inotify_add_watch");

        printf("Watching %s using wd %d\n", argv[j], wd);
    }

    for (;;) {                                  /* Read events forever */
        numRead = read(inotifyFd, buf, BUF_LEN);
        if (numRead == 0)
            fatal("read() from inotify fd returned 0!");

        if (numRead == -1)
            errExit("read");

        printf("Read %ld bytes from inotify fd\n", (long) numRead);

        /* Process all of the events in buffer returned by read() */
        for (p = buf; p < buf + numRead; ) {
            event = (struct inotify_event *) p;
            displayInotifyEvent(event);

            p += sizeof(struct inotify_event) + event->len;
        }
    }

    exit(EXIT_SUCCESS);
}
#endif

#if 0
static void notify_handler(int sig, siginfo_t *si, void *ucontext)
{
    printf("Got event on descriptor %d\n", si->si_fd);
    /* UNSAFE (see Section 21.1.2) */
}

static int denotify_f()
{
    struct sigaction sa;
    int fd, events, fnum;
    const int NOTIFY_SIG = SIGRTMIN;
    char *p;

    /* if (argc < 2 || strcmp(argv[1], "--help") == 0) */
    /*     usageError(argv[0], NULL); */

    /* Establish handler for notification signal */
    sa.sa_sigaction = notify_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_SIGINFO;           /* So handler gets siginfo_t arg. */
    if (sigaction(NOTIFY_SIG, &sa, NULL) == -1)
        errExit("sigaction");

    for (fnum = 1; fnum < argc; fnum++) {
        p = strchr(argv[fnum], ':');    /* Look for optional ':' */

        if (p == NULL) {                /* Default is all events + multishot */
            events = DN_ACCESS | DN_ATTRIB | DN_CREATE | DN_DELETE |
                     DN_MODIFY | DN_RENAME | DN_MULTISHOT;
        } else {                        /* ':' present, parse event chars */
            *p = '\0';                  /* Terminates directory component */
            events = 0;
            for (p++; *p != '\0'; p++) {
                switch (*p) {
                    case 'a': events |= DN_ACCESS;          break;
                    case 'A': events |= DN_ATTRIB;          break;
                    case 'c': events |= DN_CREATE;          break;
                    case 'd': events |= DN_DELETE;          break;
                    case 'm': events |= DN_MODIFY;          break;
                    case 'r': events |= DN_RENAME;          break;
                    case 'M': events |= DN_MULTISHOT;       break;
                    default:  usageError(argv[0], "Bad event character\n");
                }
            }
        }

        /* Obtain a file descriptor for the directory to be monitored */

        fd = open(argv[fnum], O_RDONLY);
        if (fd == -1)
            errExit("open");
        printf("opened '%s' as file descriptor %d\n", argv[fnum], fd);

        /* Use alternate signal instead of SIGIO for dnotify events */

        if (fcntl(fd, F_SETSIG, NOTIFY_SIG) == -1)
            errExit("fcntl - F_SETSIG");

        /* Enable directory change notifications */

        if (fcntl(fd, F_NOTIFY, events) == -1)
            errExit("fcntl-F_NOTIFY");
        printf("events: %o\n", (unsigned int) events);
    }

    for (;;)
        pause();                        /* Wait for events */
}
#endif


#if 0
static int anon_mmap()
{
    int *addr;                  /* Pointer to shared memory region */

#ifdef USE_MAP_ANON             /* Use MAP_ANONYMOUS */
    addr = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE,
                MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if (addr == MAP_FAILED)
        errExit("mmap");

#else                           /* Map /dev/zero */
    int fd;

    fd = open("/dev/zero", O_RDWR);
    if (fd == -1)
        errExit("open");

    addr = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (addr == MAP_FAILED)
        errExit("mmap");

    if (close(fd) == -1)        /* No longer needed */
        errExit("close");
#endif

    *addr = 1;                  /* Initialize integer in mapped region */

    switch (fork()) {           /* Parent and child share mapping */
        case -1:
            errExit("fork");

        case 0:                     /* Child: increment shared integer and exit */
            printf("Child started, value = %d\n", *addr);
            (*addr)++;
            if (munmap(addr, sizeof(int)) == -1)
                errExit("munmap");
            exit(EXIT_SUCCESS);

        default:                    /* Parent: wait for child to terminate */
            if (wait(NULL) == -1)
                errExit("wait");
            printf("In parent, value = %d\n", *addr);
            if (munmap(addr, sizeof(int)) == -1)
                errExit("munmap");
            exit(EXIT_SUCCESS);
    }
}
#endif

#if 0
static int mmcat_f()
{
    char *addr;
    int fd;
    struct stat sb;

    fd = open("build/test3.txt", O_RDONLY);
    if (fd == -1)
        errExit("open");

    /* Obtain the size of the file and use it to specify the size of
       the mapping and the size of the buffer to be written */
    if (fstat(fd, &sb) == -1)
        errExit("fstat");

    addr = mmap(NULL, sb.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    
    if (addr == MAP_FAILED)
        errExit("mmap");

    if (write(STDOUT_FILENO, addr, sb.st_size) != sb.st_size)
        fatal("partial/failed write");
    
    exit(EXIT_SUCCESS);
}
#endif

static int mmcopy_f()
{
    char *src, *dst;
    int fdSrc, fdDst;
    struct stat sb;

    fdSrc = open("build/test3.txt", O_RDONLY);
    if (fdSrc == -1)
        errExit("open");

    /* Use fstat() to obtain size of file: we use this to specify the size of the two mappings */
    if (fstat(fdSrc, &sb) == -1)
        errExit("fstat");

    /* Handle zero-length file specially, since specifying a size of
       zero to mmap() will fail with the error EINVAL */

    if (sb.st_size == 0)
        exit(EXIT_SUCCESS);

    src = mmap(NULL, sb.st_size, PROT_READ, MAP_PRIVATE, fdSrc, 0);
    if (src == MAP_FAILED)
        errExit("mmap");

    fdDst = open("build/test4.txt", O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (fdDst == -1)
        errExit("open");

    if (ftruncate(fdDst, sb.st_size) == -1)
        errExit("ftruncate");

    dst = mmap(NULL, sb.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fdDst, 0);
    if (dst == MAP_FAILED)
        errExit("mmap");

    memcpy(dst, src, sb.st_size);       /* Copy bytes between mappings */
    if (msync(dst, sb.st_size, MS_SYNC) == -1)
        errExit("msync");

    exit(EXIT_SUCCESS);
}

static int remap_file_pages_f()
{
    int fd, j;
    char ch;
    long pageSize;
    char *addr;

    fd = open("build/test.txt", O_CREAT | O_TRUNC | O_RDWR, S_IRUSR | S_IWUSR);
    if (fd == -1)
        errExit("open");

    pageSize = sysconf(_SC_PAGESIZE);
    printf("pagesize= %d\n", pageSize);
    if (pageSize == -1)
        fatal("Couldn't determine page size");

    for (ch = 'a'; ch < 'd'; ch++)
        for (j = 0; j < pageSize; j++)
            write(fd, &ch, 1);

    system("od -a build/test.txt");

    addr = mmap(0, 3 * pageSize, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (addr == MAP_FAILED)
        errExit("mmap");

    printf("Mapped at address %p\n", addr);

    /* The three pages of the file -- 0 1 2 -- are currently mapped
       linearly. Now we rearrange the mapping to 2 1 0. */

    if (remap_file_pages(addr, pageSize, 0, 2, 0) == -1)
        errExit("remap_file_pages");
    if (remap_file_pages(addr + 2 * pageSize, pageSize, 0, 0, 0) == -1)
        errExit("remap_file_pages");

    /* Now we modify the contents of the mapping */

    for (j = 0; j < 0x100; j++)         /* Modifies page 2 of file */
        *(addr + j) = '0';
    for (j = 0; j < 0x100; j++)         /* Modifies page 0 of file */
        *(addr + 2 * pageSize + j) = '2';

    system("od -a build/test.txt");

    exit(EXIT_SUCCESS);
}

#if 0
static int pipe_f()
{
    char buf[BUF_SIZE];
    int outbound[2];            /* Pipe to send data from parent to child */
    int inbound[2];             /* Pipe to send data from child to parent */
    int j;
    ssize_t cnt;

    if (pipe(outbound) == -1)
        errExit("pipe");
    if (pipe(inbound) == -1)
        errExit("pipe");

    switch (fork()) {
        case -1:
            errExit("fork");

        case 0: /* Child */

            /* Close unused pipe descriptors */

            if (close(outbound[1]) == -1)
                errExit("close");
            if (close(inbound[0]) == -1)
                errExit("close");

            /* Read data from outbound pipe, convert to uppercase,
               and send back to parent on inbound pipe */

            while ((cnt = read(outbound[0], buf, BUF_SIZE)) > 0) {
                for (j = 0; j < cnt; j++)
                    buf[j] = toupper((unsigned char) buf[j]);
                if (write(inbound[1], buf, cnt) != cnt)
                    fatal("failed/partial write(): inbound pipe");
            }

            if (cnt == -1)
                errExit("read");
            _exit(EXIT_SUCCESS);

        default:

            /* Close unused pipe descriptors */

            if (close(outbound[0]) == -1)
                errExit("close");
            if (close(inbound[1]) == -1)
                errExit("close");

            /* Read data from stdin, send to the child via the
               outbound pipe, read the results back from the child
               on the inbound pipe, and print them on stdout */

            while ((cnt = read(STDIN_FILENO, buf, BUF_SIZE)) > 0) {
                if (write(outbound[1], buf, cnt) != cnt)
                    fatal("failed/partial write(): outbound pipe");

                cnt = read(inbound[0], buf, BUF_SIZE);
                if (cnt == -1)
                    errExit("read");
                if (cnt > 0)
                    if (write(STDOUT_FILENO, buf, cnt) != cnt)
                        fatal("failed/partial write(): STDOUT_FILENO");
            }

            if (cnt == -1)
                errExit("read");

            /* Exiting will close write end of outbound pipe, so that
               child see EOF */

            exit(EXIT_SUCCESS);
    }
}
#endif

static int uname_f()
{
    struct utsname uts;

    if (uname(&uts) == -1)
        errExit("uname");

    printf("Node name:   %s\n", uts.nodename);
    printf("System name: %s\n", uts.sysname);
    printf("Release:     %s\n", uts.release);
    printf("Version:     %s\n", uts.version);
    printf("Machine:     %s\n", uts.machine);
#ifdef _GNU_SOURCE
    printf("Domain name: %s\n", uts.__domainname);
#endif
    exit(EXIT_SUCCESS);
}

#define MAX_LINE 100
/*EACCES Permission denied] open */
static int procfs_pidmax_f()
{
    int fd;
    char line[MAX_LINE];
    ssize_t n;
    char argc = 2;
    
    fd = open("/proc/sys/kernel/pid_max", (argc > 1) ? O_RDWR : O_RDONLY);
    
    if (fd == -1)
        errExit("open");

    n = read(fd, line, MAX_LINE);
    if (n == -1)
        errExit("read");

    if (argc > 1)
        printf("Old value: ");
    printf("%.*s", (int) n, line);

    if (argc > 1) {
        if (lseek(fd, 0, SEEK_SET) == -1)
            errExit("lseek");

        /* if (write(fd, argv[1], strlen(argv[1])) != strlen(argv[1])) */
        /*     fatal("write() failed"); */

        system("echo /proc/sys/kernel/pid_max now contains "
               "`cat /proc/sys/kernel/pid_max`");
    }

    exit(EXIT_SUCCESS);
}

static void sysconfPrint(const char *msg, int name)  /* Print 'msg' plus sysconf() value for 'name' */
{
    long lim;

    errno = 0;
    lim = sysconf(name);
    if (lim != -1) {        /* Call succeeded, limit determinate */
        printf("%s %ld\n", msg, lim);
    } else {
        if (errno == 0)     /* Call succeeded, limit indeterminate */
            printf("%s (indeterminate)\n", msg);
        else                /* Call failed */
            errExit("sysconf %s", msg);
    }
}

static int sysconf_f()
{
    sysconfPrint("_SC_ARG_MAX:        ", _SC_ARG_MAX);
    sysconfPrint("_SC_LOGIN_NAME_MAX: ", _SC_LOGIN_NAME_MAX);
    sysconfPrint("_SC_OPEN_MAX:       ", _SC_OPEN_MAX);
    sysconfPrint("_SC_NGROUPS_MAX:    ", _SC_NGROUPS_MAX);
    sysconfPrint("_SC_PAGESIZE:       ", _SC_PAGESIZE);
    sysconfPrint("_SC_RTSIG_MAX:      ", _SC_RTSIG_MAX);
    exit(EXIT_SUCCESS);
}

static void fpathconfPrint(const char *msg, int fd, int name)             /* Print 'msg' plus value of fpathconf(fd, name) */
{
    long lim;

    errno = 0;
    lim = fpathconf(fd, name);
    if (lim != -1) {        /* Call succeeded, limit determinate */
        printf("%s %ld\n", msg, lim);
    } else {
        if (errno == 0)     /* Call succeeded, limit indeterminate */
            printf("%s (indeterminate)\n", msg);
        else                /* Call failed */
            errExit("fpathconf %s", msg);
    }
}

static int fpathconf_f()
{
    fpathconfPrint("_PC_NAME_MAX: ", STDIN_FILENO, _PC_NAME_MAX);
    fpathconfPrint("_PC_PATH_MAX: ", STDIN_FILENO, _PC_PATH_MAX);
    fpathconfPrint("_PC_PIPE_BUF: ", STDIN_FILENO, _PC_PIPE_BUF);
    exit(EXIT_SUCCESS);
}

/* Display residency of pages in range [addr .. (addr + length - 1)] */
static void displayMincore(char *addr, size_t length)
{
    unsigned char *vec;
    long pageSize, numPages, j;

    pageSize = sysconf(_SC_PAGESIZE);

    numPages = (length + pageSize - 1) / pageSize;
    vec = malloc(numPages);
    
    if (vec == NULL)
        errExit("malloc");

    if (mincore(addr, length, vec) == -1)
        errExit("mincore");

    for (j = 0; j < numPages; j++) {
        if (j % 64 == 0)
            printf("%s%10p: ", (j == 0) ? "" : "\n", addr + (j * pageSize));
        printf("%c", (vec[j] & 1) ? '*' : '.');
    }
    printf("\n");

    free(vec);
}

static int memlock_f()
{
    char *addr;
    size_t len, lockLen;
    long pageSize, stepSize, j;

     pageSize = sysconf(_SC_PAGESIZE);
     if (pageSize == -1)
        errExit("sysconf(_SC_PAGESIZE)");

     len =      getInt("3", GN_GT_0, "num-pages") * pageSize;
     stepSize = getInt("3", GN_GT_0, "lock-page-step") * pageSize;
     lockLen =  getInt("3", GN_GT_0, "lock-page-len") * pageSize;

     addr = mmap(NULL, len, PROT_READ, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
     if (addr == MAP_FAILED)
        errExit("mmap");

    printf("Allocated %ld (%#lx) bytes starting at %p\n",
           (long) len, (unsigned long) len, addr);

    printf("Before mlock:\n");
    displayMincore(addr, len);

    /* Lock pages specified by command-line arguments into memory */
    for (j = 0; j + lockLen <= len; j += stepSize)
        if (mlock(addr + j, lockLen) == -1)
            errExit("mlock");

    printf("After mlock:\n");
    displayMincore(addr, len);

    exit(EXIT_SUCCESS);
}
#define LEN (1024 * 1024)
#define SHELL_FMT "cat /proc/%ld/maps | grep zero"
#define CMD_SIZE (sizeof(SHELL_FMT) + 20)

static int mprotect_f()
{
    char cmd[CMD_SIZE];
    char *addr;

    /* Create an anonymous mapping with all access denied */
    addr = mmap(NULL, LEN, PROT_NONE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if (addr == MAP_FAILED)
        errExit("mmap");

    /* Display line from /proc/self/maps corresponding to mapping */

    printf("Before mprotect()\n");
    snprintf(cmd, CMD_SIZE, SHELL_FMT, (long) getpid());
    system(cmd);

    /* Change protection on memory to allow read and write access */
    if (mprotect(addr, LEN, PROT_READ | PROT_WRITE) == -1)
        errExit("mprotect");

    printf("After mprotect()\n");
    system(cmd);                /* Review protection via /proc/self/maps */

    exit(EXIT_SUCCESS);
}

#if 0
static int setxattr_f()
{
    char *value;

    value = "The past is not dead.";
    if (setxattr(argv[1], "user.x", value, strlen(value), 0) == -1)
        errExit("setxattr");

    value = "In fact, it's not even past.";
    if (setxattr(argv[1], "user.y", value, strlen(value), 0) == -1)
        errExit("setxattr");

    exit(EXIT_SUCCESS);
}

#endif

#if 0
static int xattr_view_f()
{
    char list[XATTR_SIZE], value[XATTR_SIZE];
    ssize_t listLen, valueLen;
    int ns, j, k, opt;
    Boolean hexDisplay;

    hexDisplay = 0;
    while ((opt = getopt(argc, argv, "x")) != -1) {
        switch (opt) {
            case 'x': hexDisplay = 1;       break;
            case '?': usageError(argv[0]);
        }
    }

    if (optind >= argc)
        usageError(argv[0]);

    for (j = optind; j < argc; j++) {
        listLen = listxattr(argv[j], list, XATTR_SIZE);
        if (listLen == -1)
            errExit("listxattr");

        printf("%s:\n", argv[j]);

        /* Loop through all EA names, displaying name + value */

        for (ns = 0; ns < listLen; ns += strlen(&list[ns]) + 1) {
            printf("        name=%s; ", &list[ns]);

            valueLen = getxattr(argv[j], &list[ns], value, XATTR_SIZE);
            if (valueLen == -1) {
                printf("couldn't get value");
            } else if (!hexDisplay) {
                printf("value=%.*s", (int) valueLen, value);
            } else {
                printf("value=");
                for (k = 0; k < valueLen; k++)
                    printf("%02x ", (unsigned char) value[k]);
            }

            printf("\n");
        }

        printf("\n");
    }

    exit(EXIT_SUCCESS);
}
#endif

static int check_pwd_f()
{
    char *username, *password, *encrypted, *p;
    struct passwd *pwd;
    struct spwd *spwd;
    Boolean authOk;
    size_t len;
    long lnmax;

    lnmax = sysconf(_SC_LOGIN_NAME_MAX);
    if (lnmax == -1)                    /* If limit is indeterminate */
        lnmax = 256;                    /* make a guess */

    username = malloc(lnmax);
    if (username == NULL)
        errExit("malloc");

    printf("Username: ");
    fflush(stdout);
    if (fgets(username, lnmax, stdin) == NULL)
        exit(EXIT_FAILURE);             /* Exit on EOF */

    len = strlen(username);
    if (username[len - 1] == '\n')
        username[len - 1] = '\0';       /* Remove trailing '\n' */

    pwd = getpwnam(username);
    if (pwd == NULL)
        fatal("couldn't get password record");
    
    spwd = getspnam(username);
    if (spwd == NULL && errno == EACCES)
        fatal("no permission to read shadow password file");

    if (spwd != NULL)           /* If there is a shadow password record */
        pwd->pw_passwd = spwd->sp_pwdp;     /* Use the shadow password */

    password = getpass("Password: ");

    /* Encrypt password and erase cleartext version immediately */
    encrypted = crypt(password, pwd->pw_passwd);
    
    for (p = password; *p != '\0'; )
        *p++ = '\0';

    if (encrypted == NULL)
        errExit("crypt");

    authOk = strcmp(encrypted, pwd->pw_passwd) == 0;
    
    if (!authOk) {
        printf("Incorrect password\n");
        exit(EXIT_FAILURE);
    }

    printf("Successfully authenticated: UID=%ld\n", (long) pwd->pw_uid);

    /* Now do authenticated work... */

    exit(EXIT_SUCCESS);
}


static int getpwent_f()
{
    struct passwd *pwd;

    while ((pwd = getpwent()) != NULL)
        printf("%-8s %5ld\n", pwd->pw_name, (long) pwd->pw_uid);
    endpwent();
    exit(EXIT_SUCCESS);
}

#if 0
static int getpwnam_r_f()
{
    struct passwd pwd;
    struct passwd *result;
    char *buf;
    size_t bufSize;
    int s;

    if (argc != 2 || strcmp(argv[1], "--help") == 0)
        usageErr("%s username\n", argv[0]);

    bufSize = sysconf(_SC_GETPW_R_SIZE_MAX);
    buf = malloc(bufSize);
    if (buf == NULL)
        errExit("malloc %d", bufSize);

    s = getpwnam_r(argv[1], &pwd, buf, bufSize, &result);
    if (s != 0)
        errExitEN(s, "getpwnam_r");

    if (result != NULL)
        printf("Name: %s\n", pwd.pw_gecos);
    else
        printf("Not found\n");

    exit(EXIT_SUCCESS);
}
#endif

#if 0
static int new_intr_f()
{
    struct termios tp;
    int intrChar;
    char argc = 2;
    /* Determine new INTR setting from command line */
    if (argc == 1) {                                    /* Disable */
        intrChar = fpathconf(STDIN_FILENO, _PC_VDISABLE);
        if (intrChar == -1)
            errExit("Couldn't determine VDISABLE");
    } else if (isdigit((unsigned char) argv[1][0])) {
        intrChar = strtoul(argv[1], NULL, 0);           /* Allows hex, octal */
    } else {                                            /* Literal character */
        intrChar = argv[1][0];
    }
    /* Fetch current terminal settings, modify INTR character, and
       push changes back to the terminal driver */
    if (tcgetattr(STDIN_FILENO, &tp) == -1)
        errExit("tcgetattr");
    tp.c_cc[VINTR] = intrChar;
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &tp) == -1)
        errExit("tcsetattr");

    exit(EXIT_SUCCESS);
}
#endif

#if 0
static int no_echo_f()
{
    struct termios tp, save;
    char buf[BUF_SIZE];

    /* Retrieve current terminal settings, turn echoing off */
    if (tcgetattr(STDIN_FILENO, &tp) == -1)
        errExit("tcgetattr");
    save = tp;                          /* So we can restore settings later */
    tp.c_lflag &= ~ECHO;                /* ECHO off, other bits unchanged */
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &tp) == -1)
        errExit("tcsetattr");

    /* Read some input and then display it back to the user */
    printf("Enter text: ");
    fflush(stdout);
    if (fgets(buf, BUF_SIZE, stdin) == NULL)
        printf("Got end-of-file/error on fgets()\n");
    else
        printf("\nRead: %s", buf);

    /* Restore original terminal settings */
    if (tcsetattr(STDIN_FILENO, TCSANOW, &save) == -1)
        errExit("tcsetattr");

    exit(EXIT_SUCCESS);
}
#endif

static void sigintHandler(int sig)
{
    return;                     /* Just interrupt nanosleep() */
}

static int nanosleep_f()
{
    struct timeval start, finish;
    struct timespec request, remain;
    struct sigaction sa;
    int s;
    char *argv[] = {"0",  "30", "200"};
    
    request.tv_sec = getLong(argv[1], 0, "secs");
    request.tv_nsec = getLong(argv[2], 0, "nanosecs");

    /* Allow SIGINT handler to interrupt nanosleep() */
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sa.sa_handler = sigintHandler;
    if (sigaction(SIGINT, &sa, NULL) == -1)
        errExit("sigaction");

    if (gettimeofday(&start, NULL) == -1)
        errExit("gettimeofday");

    for (;;) {
        s = nanosleep(&request, &remain);
        if (s == -1 && errno != EINTR)
            errExit("nanosleep");

        if (gettimeofday(&finish, NULL) == -1)
            errExit("gettimeofday");
        printf("Slept for: %9.6f secs\n", finish.tv_sec - start.tv_sec +
               (finish.tv_usec - start.tv_usec) / 1000000.0);

        if (s == 0)
            break;                      /* nanosleep() completed */

        printf("Remaining: %2ld.%09ld\n", (long) remain.tv_sec, remain.tv_nsec);
        request = remain;               /* Next sleep is with remaining time */
    }

    printf("Sleep complete\n");
    exit(EXIT_SUCCESS);
}

static int cmdNum;      /* Our position in pipeline */

static void job_handler(int sig)            /* Handler for various signals */
{
    /* UNSAFE: This handler uses non-async-signal-safe functions
       (fprintf(), strsignal(); see Section 21.1.2) */
    if (getpid() == getpgrp())          /* If process group leader */
        fprintf(stderr, "Terminal FG process group: %ld\n",
                (long) tcgetpgrp(STDERR_FILENO));
    fprintf(stderr, "Process %ld (%d) received signal %d (%s)\n",
            (long) getpid(), cmdNum, sig, strsignal(sig));

    kill(getpid(), SIGSTOP);
    /* If we catch SIGTSTP, it won't actually stop us. Therefore we
       raise SIGSTOP so we actually get stopped. */

    if (sig == SIGTSTP)
        raise(SIGSTOP);
}


static int job_mon_f()
{
    struct sigaction sa;

    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    sa.sa_handler = job_handler;
    
    if (sigaction(SIGINT, &sa, NULL) == -1)
        errExit("sigaction");
    if (sigaction(SIGTSTP, &sa, NULL) == -1)
        errExit("sigaction");
    if (sigaction(SIGCONT, &sa, NULL) == -1)
        errExit("sigaction");

    /* If stdin is a terminal, this is the first process in pipeline:
       print a heading and initialize message to be sent down pipe */
    if (isatty(STDIN_FILENO)) {
        fprintf(stderr, "Terminal FG process group: %ld\n",
                (long) tcgetpgrp(STDIN_FILENO));
        fprintf(stderr, "Command   PID  PPID  PGRP   SID\n");
        cmdNum = 0;
    } else {            /* Not first in pipeline, so read message from pipe */
        if (read(STDIN_FILENO, &cmdNum, sizeof(cmdNum)) <= 0)
            fatal("read got EOF or error");
    }

    cmdNum++;
    fprintf(stderr, "%4d    %5ld %5ld %5ld %5ld\n", cmdNum,
            (long) getpid(), (long) getppid(),
            (long) getpgrp(), (long) getsid(0));

    /* If not the last process, pass a message to the next process */

    if (!isatty(STDOUT_FILENO))   /* If not tty, then should be pipe */
        if (write(STDOUT_FILENO, &cmdNum, sizeof(cmdNum)) == -1)
            errMsg("write");

    for (;;)            /* Wait for signals */
        pause();
}


void misc1_fun_test()
{
    /* sigwinch_f(); */
    /* epoll_input_f(); */
    /* poll_f(); */
    /* select_mq_f(); */
    /* self_pipe_f(); */
    /* file_type_stats_f(); */
    /* list_files_f(); */
    /* nftw_dir_tree_f(); */
    /* t_dirbasename_f(); */
    /* mix23io_f(); */
    /* utimes_f(); */
    /* mmcopy_f(); */
    /* remap_file_pages_f(); */
    /* uname_f(); */
    /* procfs_pidmax_f(); */
    /* sysconf_f(); */
    /* fpathconf_f(); */
    /* memlock_f(); */
    /* mprotect_f(); */
    /* check_pwd_f(); */
    /* getpwent_f(); */
    /* nanosleep_f(); */
    /* job_mon_f(); */
    
    exit(EXIT_SUCCESS);
}













