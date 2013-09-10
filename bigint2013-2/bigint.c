#define NUM_BYTES 16
typedef unsigned char BigInt[NUM_BYTES];

void big_val (BigInt res, int val)
{
	int * n = (int *) (res + 16 - 4);
	*n = val;
}

void big_uval (BigInt res, unsigned int uval)
{
	unsigned int * n = (unsigned int *) (res + 16 - 4); 
	*n = uval;
}

unsigned int big_cast_uint(BigInt res)
{
	return *((unsigned int *) (res + 16 - 4));
}

int big_cast_int(BigInt res)
{
	return *((int *) (res + 16 - 4));
}