#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int main()
{
	long long *ptr = calloc(MAX, sizeof(long long));
	
	for (int i = 0; i < MAX; i++)
		*ptr++ = 0;
	for (int i = 0; i < MAX; i++)
		--ptr;
	
	++ptr;
	++*ptr;
	++*ptr;
	++*ptr;
	++*ptr;
	++*ptr;
	++*ptr;
	++*ptr;
	++*ptr;
	++*ptr;
	++*ptr;
	
	while (*ptr) {
		--ptr;
		++*ptr;
		++*ptr;
		++*ptr;
		++*ptr;
		++*ptr;
		++*ptr;
		++*ptr;
		++*ptr;
		++*ptr;
		++*ptr;
		++ptr;
		--*ptr;
	}
	
	++*ptr;
	++ptr;
	++*ptr;
	--ptr;
	--ptr;
	
	while (*ptr) {
		++ptr;
		printf("%lld\n", *ptr);
		++ptr;
		
		while (*ptr) {
			++ptr;
			++*ptr;
			--ptr;
			--*ptr;
		}
		
		--ptr;
		
		while (*ptr) {
			++ptr;
			++*ptr;
			--ptr;
			--*ptr;
		}
		
		++ptr;
		++ptr;
		
		while (*ptr) {
			--ptr;
			++*ptr;
			--ptr;
			++*ptr;
			++ptr;
			++ptr;
			--*ptr;
		}
		
		--ptr;
		--ptr;
		--ptr;
		--*ptr;
	}
	
}