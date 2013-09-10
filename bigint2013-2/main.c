#include<stdlib.h>
#include<stdio.h>
#include "bigint.h"

int assertsPassaram = 0;
int assertsFalharam = 0;

char * testName;

void assert(unsigned int esperado, unsigned int obtido)
{
	if (esperado == obtido)
	{
		assertsPassaram++;
	}
	else
	{
		assertsFalharam++;
		printf("[%s]: esperado %d, mas foi obtido %d\n", testName, esperado, obtido);
	}
}

void test(char * name)
{
	testName = name;
}

void reportarTestes()
{
	printf("Passaram: %d    Falharam: %d\n", assertsPassaram, assertsFalharam);
}

int main() {
	BigInt big;
	unsigned int uint;
	int vint;

	test("cast_uint após big_uval tem que permanecer o mesmo valor");
	big_uval(big, 33);
	uint = big_cast_uint(big);
	assert(33, uint);

	test("cast_int após big_uval tem que permanecer o mesmo valor");
	big_val(big, 33);
	vint = big_cast_int(big);
	assert(33, vint);

	test("cast_int após big_val com negativo tem que permanecer o mesmo valor");
	big_val(big, -33);
	vint = big_cast_int(big);
	assert(-33, vint);

	reportarTestes();

	return 0;
}