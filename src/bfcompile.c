#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OUT      "a.c"

#define print(s) indent(output, (s), ind)
// #define prf(s, ...) indent(output, sprintf((s), ##__VA_ARGS__), ind)

#define HEADERS  "#include <stdio.h>\n#include <stdlib.h>\n\n"
#define MACROS   "#define MAX 100\n\n"
#define FUNCS    "int main()\n{" // might include other function declarations
#define DECLARS  "\n%s *ptr = calloc(MAX, sizeof(%s));\n"
#define INIT     "\nfor (int i = 0; i < MAX; i++)\n\t*ptr++ = 0;\nfor (int i = 0; i < MAX; i++)\n\t--ptr;\n"
#define GETSTR   usech ? "\n*ptr = getchar();" : "\nscanf(\"%lld\", ptr);"
#define PUTSTR   usech ? "\nputchar(*ptr);"    : "\nprintf(\"%lld\n\", *ptr);"
#define FOOTER   usech ? "\n\n\tputchar('\\n');\n\n}" : "\n}" // might include other functions

void indent(FILE *, char *, int);

/* Brainfuck compiler - compiles to C code, then might call clang */
/* Possible avenues for optimization: simplifying arithmetic and numeric operations */
int main(int argc, char *argv[])
{
    FILE *input, *output;
    int  c, usech, ind = 0, typelen;
    char *ptrtype, *declars;
    
    if (argc == 2) {
        input  = fopen(argv[1], "r");
        output = fopen(OUT    , "w");
    } else if (argc == 4 && !strcmp(argv[1], "-o")) {
        input  = fopen(argv[3], "r");
        output = fopen(argv[2], "w");
    } else {
        fprintf(stderr, "Invalid command -- The valid format is ./bfcompile [-o <output>] <input>\n");
        exit(1);
    }
    
    if (!input) {
        fprintf(stderr, "Unable to open file\n");
        exit(1);
    }
    if (!output) {
        fprintf(stderr, "Unable to create compiled file\n");
        exit(1);
    }
    
    printf("Should the program output characters or numbers? (1/0) ");
    scanf("%d", &usech);
    if (usech)
        ptrtype = "char";
    else
        ptrtype = "long long";
    
    fprintf(output, "%s%s%s", HEADERS, MACROS, FUNCS);
    
    ++ind;
    sprintf(declars, DECLARS, ptrtype, ptrtype);
    print(declars);
    print(INIT);
    
    while ((c = fgetc(input)) != EOF) {
        switch (c) {
        case '+':
            print("\n++*ptr;");
            break;
        case '-':
            print("\n--*ptr;");
            break;
        case '>':
            print("\n++ptr;");
            break;
        case '<':
            print("\n--ptr;");
            break;
        case ',':
            print(GETSTR);
            break;
        case '.':
            print(PUTSTR);
            break;
        case '[':
            print("\n\nwhile (*ptr) {");
            ++ind;
            break;
        case ']':
            --ind;
            print("\n}\n");
            break;
        }
    }
    
    if (ind != 1) {
        fprintf(stderr, "File includes open loops");
        exit(1);
    }
    
    --ind;
    print(FOOTER);
    
    
    fclose(input);
    fclose(output);
}

/* prints text to stm, indenting every line ind times */
void indent(FILE *stm, char *text, int ind)
{
    char *mult(char, int);
    char *inds = mult('\t', ind);
    int insidestr = 0, insidechar = 0;
    
    for ( ; *text != '\0'; text++) {
        if (*text == '\"')
            insidestr = !insidestr;
        
        if (*text == '\'')
            insidechar = !insidechar;
        
        if (*text == '\n') {
            if (insidestr || insidechar)
                fprintf(stm, "\\n");
            else {
                fputc(*text, stm);
                fprintf(stm, "%s", inds);
            }
        } else {
            fputc(*text, stm);
        }
    }
}

/* return a string repeating c n times */
char *mult(char c, int n)
{
    char *res = calloc(n, sizeof(char));
    for (int i = 0; i < n; i++)
        *res++ = c;
    for (int i = n; i > 0; i--)
        res--;
    return res;
}