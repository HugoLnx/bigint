#define NUM_BYTES 4
typedef unsigned char BigInt[NUM_BYTES];


void big_uval (BigInt res, unsigned int uval)
{
	unsigned int * n = (unsigned int *) res; 
	*n = uval;
}

unsigned int big_cast_uint(BigInt res)
{
	return *((unsigned int *) res);
}