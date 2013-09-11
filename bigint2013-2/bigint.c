#include<stdio.h>

#define NUM_BYTES 16
typedef unsigned char BigInt[NUM_BYTES];

void zerarBytes(BigInt res);
void zerarBytesCom(BigInt res, char byte);

void big_val (BigInt res, int val)
{
	int * n = (int *) res;
	char bit_do_sinal;

	zerarBytes(res);

	bit_do_sinal = (val >> 31) * 0xff;
	if ( bit_do_sinal == 0x01 )
	{
		zerarBytesCom(res, 0xff);
	}
	else
	{
		zerarBytesCom(res, 0x00);
	}
	
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

void zerarBytesCom(BigInt res, char byte)
{
	int i;
	char * bytes = (char *) res;

	for ( i = 0 ; i < NUM_BYTES ; i++ )
	{
		*bytes++ = byte;
	}
}


void zerarBytes(BigInt res)
{
	zerarBytesCom(res, 0);
}