#include <stdio.h>
#include <stdlib.h>

#define MAX 5

void init(long long *);

int main()
{
    long long *stack = calloc(MAX, sizeof(long long));
    init(stack);
    ++stack;
    *stack += 10;
    while (*stack)
    {
        --stack;
        *stack += 10;
        ++stack;
        --*stack;
    }
    ++*stack;
    ++stack;
    ++*stack;
    --stack;
    --stack;
    while (*stack)
    {
        ++stack;
        printf("%lld\n", *stack);
        ++stack;       // >
        while (*stack) // [>+<-]
        {
            ++stack;
            ++*stack;
            --stack;
            --*stack;
        }
        --stack;       // <
        while (*stack) // [>+<-]
        {
            ++stack;
            ++*stack;
            --stack;
            --*stack;
        }
        ++stack;       // >
        ++stack;       // >
        while (*stack) // [<+<+>>-]
        {
            --stack;
            ++*stack;
            --stack;
            ++*stack;
            ++stack;
            ++stack;
            --*stack;
        }
        --stack;       // <<<-
        --stack;
        --stack;
        --*stack;
    }
}

void init(long long *s)
{
    for (int i = 0; i < MAX; i++)
        *s++ = 0;
}