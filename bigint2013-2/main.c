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
	unsigned int uint;
	int vint;

	// big_uval e cast_uint
	big_uval(big, 33);
	uint = big_cast_uint(big);
	assert(33, uint);

	// big_val e cast_int
	big_val(big, 33);
	vint = big_cast_int(big);
	assert(33, vint);

	// big_val e cast_int com negativo
	big_val(big, -33);
	vint = big_cast_int(big);
	assert(-33, vint);

	reportarTestes();

	return 0;
}