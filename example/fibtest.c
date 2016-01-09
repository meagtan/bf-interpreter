#include <stdio.h>

int main()
{
    unsigned long long a, b;
    
    a = b = 1;
    for (int i = 0; i < 100; i++) {
        printf("%llu\n", a);
        b += a;
        a = b - a;
    }
}