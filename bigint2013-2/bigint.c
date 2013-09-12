#include<stdio.h>
#include<math.h>

#define NUM_BYTES 16
typedef unsigned char BigInt[NUM_BYTES];

void zerar_bytes(BigInt res);
void zerar_bytes_com(BigInt res, char byte);
unsigned char bit_pow(unsigned char n, unsigned char exp);
unsigned char byte_shift_esquerda(unsigned char bits, unsigned char qnt_bits);
unsigned char byte_shift_direita(unsigned char bits, unsigned char qnt_bits);

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

	zerar_bytes(res);

	qnt_bits = n % 8;

	for ( byte = 0 ; byte < NUM_BYTES - n / 8 ; byte++ )
	{
		*resBytes = byte_shift_esquerda(*aBytes, qnt_bits) + bits_iniciais;
		bits_iniciais = byte_shift_direita(*aBytes, 8 - qnt_bits);
		resBytes++;
		aBytes++;
	}
}


void big_shr (BigInt res, BigInt a, int n)
{
	int byte;
	unsigned char * resBytes = (unsigned char*) res;
	unsigned char * aBytes = (unsigned char*) a;
	unsigned char bits_finais = 0;
	unsigned char qnt_bits;

	resBytes += NUM_BYTES - n / 8 - 1;
	aBytes += NUM_BYTES - 1;

	qnt_bits = n % 8;

	for ( byte = 0 ; byte < NUM_BYTES - n / 8 ; byte++ )
	{
		*resBytes = byte_shift_direita(*aBytes, qnt_bits) + bits_finais;
		bits_finais = byte_shift_esquerda(*aBytes, 8 - qnt_bits);
		resBytes--;
		aBytes--;
	}
}

void big_val (BigInt res, int val)
{
	int * n = (int *) res;
	char bit_do_sinal;

	bit_do_sinal = (val & 0x80000000) == 0x80000000;

	if ( bit_do_sinal == 0x01 )
	{
		zerar_bytes_com(res, 0xff);
	}
	else
	{
		zerar_bytes_com(res, 0x00);
	}
	
	*n = val;
}

void big_uval (BigInt res, unsigned int uval)
{
	unsigned int * n = (unsigned int *) res; 
	zerar_bytes(res);
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

void zerar_bytes_com(BigInt res, char byte)
{
	int i;
	char * bytes = (char *) res;

	for ( i = 0 ; i < NUM_BYTES ; i++ )
	{
		*bytes++ = byte;
	}
}


void zerar_bytes(BigInt res)
{
	zerar_bytes_com(res, 0);
}

unsigned char bit_pow(unsigned char n, unsigned char exp)
{
	return (unsigned char) pow((double) n, (double) exp); 
}


unsigned char byte_shift_esquerda(unsigned char bits, unsigned char qnt_bits)
{
	 return bits * bit_pow(2, qnt_bits);
}


unsigned char byte_shift_direita(unsigned char bits, unsigned char qnt_bits)
{
	unsigned char pow_result = bit_pow(2, qnt_bits);
	return (pow_result == 0 ? 0 : bits / pow_result);
}