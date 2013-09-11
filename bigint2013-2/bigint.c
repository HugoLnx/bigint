#include<stdio.h>

#define NUM_BYTES 16
typedef unsigned char BigInt[NUM_BYTES];

void zerarBytes(BigInt res);

void big_val (BigInt res, int val)
{
	int * n = (int *) res;
	zerarBytes(res);
	*n = val;
}

void big_uval (BigInt res, unsigned int uval)
{
	unsigned int * n = (unsigned int *) res; 
	zerarBytes(res);
	*n = uval;
}

unsigned int big_cast_uint(BigInt res)
{
	return *((unsigned int *) res);
}

int big_cast_int(BigInt res)
{
	return *((int *) res);
}

void zerarBytes(BigInt res)
{
	int i;
	char * bytes = (char *) res;

	for ( i = 0 ; i < NUM_BYTES ; i++ )
	{
		*bytes++ = 0;
	}
}