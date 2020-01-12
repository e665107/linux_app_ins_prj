#include <signal.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <tlpi_hdr.h>

#include "misc_f1.h"

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

void misc1_fun_test()
{
    sigwinch_f();
}

