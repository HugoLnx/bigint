/* Hugo Roque de Figueiredo 1311162 */
/* Robert Correa dos Santos 1210325 */

#include<stdio.h>
#include "bigint.h"

/*-------Protótipos das funções encapsuladas-------*/
int IsLessThan(BigInt a, BigInt b);
int IsLessThanForSigned(BigInt a, BigInt b);
void Reverse(BigInt a, BigInt res);
int IsNegative(BigInt a);
int IsEqual(BigInt a, BigInt b);
void big_copy(BigInt res, BigInt a);
void reset_bytes(BigInt res);
void reset_bytes_with(BigInt res, char byte);
unsigned char bit_pow(unsigned char n, unsigned char exp);
unsigned char byte_shift_esquerda(unsigned char bits, unsigned char qnt_bits);
unsigned char byte_shift_direita(unsigned char bits, unsigned char qnt_bits);

/*-------FIM dos protótipos das funções encapsuladas-------*/

/*-------Implementação das funções exportadas-------*/

/* Atribuicao */

/* res = val (extensao com sinal) */
void big_val (BigInt res, int val)
{
	int * n = (int *) res;
	char bit_do_sinal;

	bit_do_sinal = (val & 0x80000000) == 0x80000000;

	if ( bit_do_sinal == 0x01 )
	{
		reset_bytes_with(res, 0xff);
	}
	else
	{
		reset_bytes_with(res, 0x00);
	}
	
	*n = val;
}

/* res = uval (extensao sem sinal) */
void big_uval (BigInt res, unsigned int uval)
{
	unsigned int * n = (unsigned int *) res; 
	reset_bytes(res);
	*n = uval;
}

/* Operacoes aritmeticas */

/* res = a + b */
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
		if(soma > 0xff)
		{
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

/* res = a - b */
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
		if(subt < 0) 
		{
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

/* res = a * b (com sinal) */
void big_mul (BigInt res, BigInt a, BigInt b)
{
	big_umul(res,a,b);
}

/* res = a * b (sem sinal) */
void big_umul (BigInt res, BigInt a, BigInt b)
{
	BigInt um, zero, aux_a, aux_b, aux_res;
	big_uval(zero,0);
	big_uval(res,0);
	big_uval(um,1);

	while(big_ucmp(b,zero))
	{
		if(b[0]&1)
		{
			big_sum(aux_res,res,a);
			big_copy(res,aux_res);
		}

		big_shl(aux_a,a,1);
		big_copy(a,aux_a);

		big_shr(aux_b,b,1);
		big_copy(b,aux_b);
	}
}

/* Operacoes de deslocamento */

/* res = a << n */
void big_shl (BigInt res, BigInt a, int n)
{
	int byte;
	unsigned char * resBytes = (unsigned char*) res;
	unsigned char * aBytes = (unsigned char*) a;
	unsigned char bits_iniciais = 0;
	unsigned char qnt_bits;

	resBytes += n / 8;

	reset_bytes(res);

	qnt_bits = n % 8;

	for ( byte = 0 ; byte < NUM_BYTES - n / 8 ; byte++ )
	{
		*resBytes = byte_shift_esquerda(*aBytes, qnt_bits) + bits_iniciais;
		bits_iniciais = byte_shift_direita(*aBytes, 8 - qnt_bits);
		resBytes++;
		aBytes++;
	}
}

/* res = a >> n (logico) */
void big_shr (BigInt res, BigInt a, int n)
{
	int byte;
	unsigned char * resBytes = (unsigned char*) res;
	unsigned char * aBytes = (unsigned char*) a;
	unsigned char bits_finais = 0;
	unsigned char qnt_bits;

	resBytes += NUM_BYTES - n / 8 - 1;
	aBytes += NUM_BYTES - 1;

	reset_bytes(res);

	qnt_bits = n % 8;

	for ( byte = 0 ; byte < NUM_BYTES - n / 8 ; byte++ )
	{
		*resBytes = byte_shift_direita(*aBytes, qnt_bits) + bits_finais;
		bits_finais = byte_shift_esquerda(*aBytes, 8 - qnt_bits);
		resBytes--;
		aBytes--;
	}
}

/* Comparacao: retorna -1 (a < b), 0 (a == b), 1 (a > b) */

/* comparacao com sinal */
int big_cmp(BigInt a, BigInt b)
{
	if(IsEqual(a,b))
		return 0;
	else
	{
		if(IsLessThanForSigned(a,b))
			return -1;
		else
			return 1;
	}
}

/* comparacao sem sinal */
int big_ucmp(BigInt a, BigInt b)
{
	if(IsEqual(a,b))
		return 0;
	else
	{
		if(IsLessThan(a,b))
			return -1;
		else
			return 1;
	}
}

/*-------FIM da implementação das funções exportadas-------*/

/*-------Implementação das funções encapsuladas-------*/

void big_copy(BigInt res, BigInt a)
{
	int i = 0;
	for(i = 0; i < NUM_BYTES; i++)
		res[i] = a[i];
}

void reset_bytes_with(BigInt res, char byte)
{
	int i;
	char * bytes = (char *) res;

	for ( i = 0 ; i < NUM_BYTES ; i++ )
		*bytes++ = byte;
}

void reset_bytes(BigInt res)
{
	reset_bytes_with(res, 0);
}

unsigned char bit_pow(unsigned char n, unsigned char exp)
{
	unsigned char i;
	unsigned char res = 1;
	for(i = 0; i < exp; i++)
		res *= n;
	
	return res; 
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

/* Checa se o dois BigInts sao iguais */
int IsEqual(BigInt a, BigInt b)
{
	int i = 0;
	for(i = 0; i < NUM_BYTES; i++)
	{
		if(a[i] != b[i])
			return 0;
	}

	return 1;
}

/* Checa se o BigInt é negativo */
int IsNegative(BigInt a)
{
	char val = a[NUM_BYTES-1];
	char bit_do_sinal = (val & 0x80000000) == 0x80000000;

	if ( bit_do_sinal == 0x01 )
		return 1;
	else
		return 0;
}

/* Transforama número negativo em positivo e vice-versa */
void Reverse(BigInt a, BigInt res)
{
	BigInt um; // bigint contendo valor 1
	BigInt aux_a; // bigint que auxilia na conversao de 'a'
	int i;

	big_val(um,1);
	for(i = 0; i < NUM_BYTES; i++)
		/* inverte bytes bit a bit */
		aux_a[i] = ~a[i];

    /* soma + 1 para obter o valor correto */
	big_sum(res,aux_a,um);

}

int IsLessThanForSigned(BigInt a, BigInt b)
{
	int i;
	BigInt a_complementoA2;
	BigInt b_complementoA2;

	/* Se 'a' for negativo e 'b' não */
	if(IsNegative(a) && !(IsNegative(b)))
	{
		/* converte 'a' para positivo */
		Reverse(a, a_complementoA2);

		return IsLessThan(b,a_complementoA2);
	}
	/* Se 'a' for negativo e 'b' não  */
	else if(!IsNegative(a) && (IsNegative(b)))
	{
		/* converte 'b' para positivo */
		Reverse(b, b_complementoA2);

		return IsLessThan(b_complementoA2,a);
	}
	/* Se ambos forem negativos */
	else if(IsNegative(a) && (IsNegative(b)))
	{
		/* converte ambos para positivo */
		Reverse(a, a_complementoA2);
		Reverse(b, b_complementoA2);
		
		return IsLessThan(b_complementoA2,a_complementoA2);
	}

	/* Se ambos fore positivos */
	/* itera pelo BigInt partindo dos bits mais segnificativos */
	for(i = NUM_BYTES-1; i >= 0; i--)
	{
		// Se ambos forem 0xFF ou se forem iguais, continua a iteração
		if((a[i] == 0xFF) && (b[i] == 0xFF) || a[i] == b[i])
			continue;

		// Caso o byte corrente de 'a' for maior que o de 'b', então o Bigint 'a' é maior que o BigInt 'b'
		if(a[i] > b[i])
			return 0;

		return 1;
	}

	// error
	return -1;
}

int IsLessThan(BigInt a, BigInt b)
{
	int i;

	/* itera pelo BigInt partindo dos bits mais segnificativos */
	for(i = NUM_BYTES-1; i >= 0; i--)
	{
		// Se ambos forem 0x00 ou se forem iguais, continua a iteração
		if((a[i] == 0x00) && (b[i] == 0x00) || a[i] == b[i])
			continue;

		// Caso o byte corrente de 'a' for maior que o de 'b', então o Bigint 'a' é maior que o BigInt 'b'
		if(a[i] > b[i])
			return 0;

		return 1;
	}

	// error
	return -1;
}

/*------- FIM Implementação das funções encapsuladas-------*/