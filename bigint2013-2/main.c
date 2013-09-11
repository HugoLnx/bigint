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
		printf("[%s]: esperado %02x, mas foi obtido %02x\n", testName, esperado, obtido);
	}
}

void assertBytes(char * esperado, void * obtido)
{
	int i;
	int erro = 0;
	char * bytesObt = (char *) obtido;
	char * bytesEsp = esperado;

	for ( i = 0 ; i < 16 ; i++ )
	{
		erro = (*bytesEsp++ != *bytesObt++);
		if(erro) break;
	}

	if(erro)
	{
		bytesObt = (char *) obtido;
		bytesEsp = esperado;

		
		printf("[%s]: erro bytes errados:\nesperado > obtido\n", testName);
		for ( i = 0 ; i < 16 ; i++ )
		{
			printf("%02x > %02x\n", *bytesEsp++, *bytesObt++);
		}
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

char * bytesFrom(char b1, char b2, char b3, char b4,
	char b5, char b6, char b7, char b8,
	char b9, char b10, char b11, char b12,
	char b13, char b14, char b15, char b16)
{
	char * bytes = (char *) malloc(sizeof(char)*16);
	char * bytesBegin = bytes;

	*(bytes++) = b1; *(bytes++) = b2; *(bytes++) = b3; *(bytes++) = b4;
	*(bytes++) = b5; *(bytes++) = b6; *(bytes++) = b7; *(bytes++) = b8;
	*(bytes++) = b9; *(bytes++) = b10; *(bytes++) = b11; *(bytes++) = b12;
	*(bytes++) = b13; *(bytes++) = b14; *(bytes++) = b15; *(bytes++) = b16;

	return bytesBegin;
}

int main() {
	BigInt big, a, b;
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

	test("big_uval => 1 como: 0x00(15x) 0x01");
	big_uval(big, 1);
	assertBytes(bytesFrom(
		0x01, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00
	), big);
	
	test("big_val => 1 como: 0x00(15x) 0x01");
	big_val(big, 1);
	assertBytes(bytesFrom(
		0x01, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00
	), big);
	
	test("big_val => -1 como: 0xff(16x)");
	big_val(big, -1);
	assertBytes(bytesFrom(
		0xff, 0xff, 0xff, 0xff,
		0xff, 0xff, 0xff, 0xff,
		0xff, 0xff, 0xff, 0xff,
		0xff, 0xff, 0xff, 0xff
	), big);

	reportarTestes();

	return 0;
}