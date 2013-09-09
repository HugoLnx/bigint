#include<stdlib.h>
#include<stdio.h>
#include "bigint.h"

int main() {
	BigInt big;
	unsigned int x;

	big_uval(big, 10000);
	
	x = big_cast_uint(big);

	printf("%d\n" , x);
	
	return 0;
}