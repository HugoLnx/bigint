#include<stdlib.h>
#include<stdio.h>
#include "bigint.h"

int testesPassaram = 0;
int testesFalharam = 0;

void assert(unsigned int esperado, unsigned int obtido)
{
	if (esperado == obtido)
	{
		testesPassaram++;
	}
	else
	{
		testesFalharam++;
		printf("esperado %d, mas foi obtido %d\n", esperado, obtido);
	}
}

void reportarTestes()
{
	printf("Passaram: %d    Falharam: %d\n", testesPassaram, testesFalharam);
}


int main() {
	BigInt big;
	unsigned int x;

	// big_uval e cast_uint
	big_uval(big, 10000);
	x = big_cast_uint(big);
	assert(10000, x);
	
	reportarTestes();

	return 0;
}