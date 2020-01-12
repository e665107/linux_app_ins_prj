#ifndef STACK_F_H
#define STACK_F_H

struct Stack{
    int size;
    struct List{
        int item;
        struct List *next;
    } *head;
};
typedef struct Stack *slink;

void stack_list_t(void);

int pop_stack(slink stack);

void push_stack(slink stack, int item);

int empty(slink stack);

slink create_stack(void);

#endif /* STACK_F_H */

