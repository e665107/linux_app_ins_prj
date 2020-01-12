#ifndef STACK_ARRAY_F_H
#define STACK_ARRAY_F_H

struct Stack
{
    int capability;
    int sp;
    int *data;
};

typedef struct Stack *slink;

void stack_array_t(void);
int pop_stack(slink stack);
void push_stack(slink stack, int item);
int full(slink stack);
int empty(slink stack);
slink create_stack(int capability);

#endif /* STACK_ARRAY_F_H */
