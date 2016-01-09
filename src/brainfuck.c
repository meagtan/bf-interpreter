#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX         1000
#define LOOP_DEPTH  10
#define STACK_TYPE  long long
// #define inc(x,y) (x) = (x) < loopbounds[(y)] + LOOP_DEPTH - 1 ? (x) + 1 : NULL
// #define dec(x,y) (x) = (x) > loopbounds[(y)] ? (x) - 1 : NULL
#define CURRENTPOS  ftell(inputf)
#define jumpto(x)   fseek(inputf, x, SEEK_SET)
#define inloop(x)   inptr(loopsts, (x)) // *loopstarts == (x)

void inits(STACK_TYPE *);
void initl(long *);
int  inptr(long *, long);

int main(int argc, char *argv[])
{
    char  c;
    FILE  *inputf;
    int   skiptoend, opencount, closecount, i, usech;
    long  *loopstarts, *loopsts = calloc(LOOP_DEPTH, sizeof(long));
    STACK_TYPE *stack, *stackstart = calloc(MAX, sizeof(STACK_TYPE));
    
    if (argc == 2) {
        i = 1;
    } else if (argc == 3 && !strcmp(argv[1], "-c")) {
        usech = 1;
        i = 2;
    } else if (argc == 3 && !strcmp(argv[1], "-n")) {
        usech = 0;
        i = 2;
    } else {
        fprintf(stderr, "Invalid command\nThe valid command format is ./brainfuck [-c | -n] <filename>\n");
        exit(1);
    }
    inputf = fopen(argv[i], "r");
    if (!inputf) {
        fprintf(stderr, "Cannot open file %s\n", argv[i]);
        exit(1);
    }
    
    // give error if no memory
    if (!stackstart || !loopsts) {
        fprintf(stderr, "Memory allocation error\n");
        exit(1);
    }
    
    inits(stackstart);
    initl(loopsts);
    stack      = stackstart;
    loopstarts = loopsts;
    skiptoend  = opencount = closecount = 0;
    
    // go through each character
    while ((c = fgetc(inputf)) != EOF) {
        
        // skip to first ] that isn't enclosed by an [
        if (skiptoend) {
            if (c == '[')
                opencount++;
            if (c == ']')
                closecount++;
            if (c != ']' || (opencount - closecount))
                continue;
        }
        
        switch (c) {
        case '+':
            ++*stack;
            break;
        case '-':
            --*stack;
            break;
        case '>':
            if (stack < stackstart + MAX - 1) // keep stack position within range
                ++stack;
            break;
        case '<':
            if (stack > stackstart) // keep stack position within range
                --stack;
            break;
        case ',':
            if (usech)
                *stack = getchar();
            else
                scanf("%lld", stack);
            break;
        case '.':
            if (usech)
                putchar((char) *stack);
            else
                printf("%lld\n", (unsigned long long) *stack); 
            break;
        case '[':
            if (!*stack) {
                skiptoend = opencount = 1;
                closecount = 0;
            } else if (!inloop(CURRENTPOS - 1)) { // check if I've already come here
                ++loopstarts; // inc(loopstart, 0);
                *loopstarts = CURRENTPOS - 1; // loopstart is located at the [
            }
            break;
        case ']':
            if (!skiptoend) { // if the loop is continuing
                jumpto(*loopstarts); // go back to the [
            } else {
                *loopstarts = 0;
                --loopstarts; // continue after the ]
                skiptoend = opencount = closecount = 0;
            }
            break;
        }
    }
    
    if (usech)
        putchar('\n');

    fclose(inputf);
    free(loopsts);
    free(stackstart);
    // free(stack);
    
}

/* initialize every position on the stack to 0 */
void inits(STACK_TYPE *s)
{
    for (int i = 0; i < MAX; i++)
        *s++ = 0;
}

/* initialize every loop starting position to 0 */
void initl(long *poslist)
{
    for (int i = 0; i < LOOP_DEPTH; i++)
        *poslist++ = 0;
}

/* whether val is a loop starting position in l */
int inptr(long *l, long val)
{
    int res = 0;
    for (int i = 0; i < LOOP_DEPTH; i++)
        res = res || (*l++ == val);
    return res;
}