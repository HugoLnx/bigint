#include<stdio.h>
#include<math.h>

#define NUM_BYTES 16
typedef unsigned char BigInt[NUM_BYTES];

void zerarBytes(BigInt res);
void zerarBytesCom(BigInt res, char byte);
unsigned char bit_pow(unsigned char n, unsigned char exp);

void big_sum (BigInt res, BigInt a, BigInt b)
{
	int i;
	unsigned char * resBytes = (unsigned char *) res;
	unsigned char * aBytes = (unsigned char *) a;
	unsigned char * bBytes = (unsigned char *) b;
	int soma;
	char sobra = 0;

	for(i = 0 ; i < NUM_BYTES ; i++)
	{
		soma = *aBytes++ + *bBytes++ + sobra;
		if(soma > 0xff) {
			sobra = 1;
			soma -= 0xff + 1;
		}
		else
		{
			sobra = 0;
		}
		*resBytes++ = soma;
	}
}

void big_sub (BigInt res, BigInt a, BigInt b)
{
	int i;
	unsigned char * resBytes = (unsigned char *) res;
	unsigned char * aBytes = (unsigned char *) a;
	unsigned char * bBytes = (unsigned char *) b;
	int subt;
	char sobra = 0;

	for(i = 0 ; i < NUM_BYTES ; i++)
	{
		subt = *aBytes++ - *bBytes++ - sobra;
		if(subt < 0) {
			sobra = 1;
			subt += 0xff + 1;
		}
		else
		{
			sobra = 0;
		}
		*resBytes++ = subt;
	}
}

void big_shl (BigInt res, BigInt a, int n)
{
	int byte;
	unsigned char * resBytes = (unsigned char*) res;
	unsigned char * aBytes = (unsigned char*) a;
	unsigned char bits_iniciais = 0;
	unsigned char qnt_bits;

	resBytes += n / 8;

	qnt_bits = n % 8;

	for ( byte = 0 ; byte < NUM_BYTES - n / 8 ; byte++ )
	{
		*resBytes = *aBytes * bit_pow(2, qnt_bits) + bits_iniciais;
		bits_iniciais = *aBytes / bit_pow(2, 8 - qnt_bits);
		resBytes++;
		aBytes++;
	}
}

void big_val (BigInt res, int val)
{
	int * n = (int *) res;
	char bit_do_sinal;

	bit_do_sinal = (val & 0x80000000) == 0x80000000;

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

unsigned char bit_pow(unsigned char n, unsigned char exp)
{
	return (unsigned char) pow((double) n, (double) exp); 
}