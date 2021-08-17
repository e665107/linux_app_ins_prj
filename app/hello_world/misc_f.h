#ifndef MISC_F_H
#define MISC_F_H

void misc_fun_test(void);

int rindex_f(void);

char* basename(char*  full_name);

int putenv_f(void);

int malloc_f(void);

void f2(int *p);

void f1(int **p);

unsigned int my_sleep(unsigned int nsec);

void sigusr1_handler(int signo);

void sigalrm_handler(int signo);

void timer_handler(int signo);

void err_quit(char * msg);
void cleanup(void *arg);

#endif /* MISC_F_H */






