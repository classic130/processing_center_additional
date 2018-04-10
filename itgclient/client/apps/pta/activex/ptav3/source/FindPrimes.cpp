#include "stdafx.h"
#include "FindPrimes.h"
#include "ptaerrs.h"

#define	BUFFER_LEN		2000

int	FindPrimes(A_PKCS_RSA_PRIVATE_KEY* io_psRSAKey)
{
	CMPInt		e, d, n, ed,  edm1;
	CMPInt		rnd, s, t, one, pout, qout;
	CMPInt		swap;

	int			niout;
	
	int			i;
	int			good_is			= 0;

	int			nRandom			= 0;

	A_RSA_KEY		RSAPrivKey;
	A_RSA_KEY		RSAPubKey;

	DWORD		dwResult			=	999;
	int			nFound				=	0;

		//	construct all the CMPInts that are needed
	CMP_Constructor(&n);
	CMP_Constructor(&e);
	CMP_Constructor(&d);
	CMP_Constructor(&pout);
	CMP_Constructor(&qout);
	CMP_Constructor(&swap);
	CMP_Constructor(&ed);
	CMP_Constructor(&one);
	CMP_Constructor(&edm1);
	CMP_Constructor(&s);
	CMP_Constructor(&t);

	do
	{
				//	create CMPInts using the modulus, public key exponent and the private key exponent
		CMP_OctetStringToCMPInt( (unsigned char*) (io_psRSAKey->modulus).data, (io_psRSAKey->modulus).len, &n);
		CMP_OctetStringToCMPInt( (unsigned char*) (io_psRSAKey->publicExponent).data, (io_psRSAKey->publicExponent).len, &e);
		CMP_OctetStringToCMPInt( (unsigned char*) (io_psRSAKey->privateExponent).data, (io_psRSAKey->privateExponent).len, &d);

				//	ed = e * d
		CMP_Multiply(&e, &d, &ed);

				//	create a CMPInt with value 1
		CMP_CMPWordToCMPInt((CMPWord) 1, &one);

				//	edm1 = ed - 1
		VS_CMP_Subtract(&ed, &one, &edm1);

				//	find s and t such that ed-1 = (2^s)*t
		find_s_t(edm1, &s, &t);

		for (int j = 0; j<20; j++)
		{
				//	generate a random number and put it into a CMPInt
			GenerateRandomBlock((unsigned char*)&nRandom, 4);
			CMP_Constructor(&rnd);
			CMP_CMPWordToCMPInt((CMPWord) nRandom, &rnd);

				//	check if the required properties are satisfied by s and t
			if (check_props(s, t, rnd, n, &niout))
			{
					//	get the primes p and q
				get_pq(rnd, niout, t, n, &pout, &qout);

						//	make sure that the primes we found are not 1 and modulus
				if ( (VS_CMP_Compare(&pout, &n) != 0) && (VS_CMP_Compare(&qout, &n) != 0) )
				{
					nFound =	1;

						//	the larger of the primes should be P and the smaller should be Q
					if ( VS_CMP_Compare(&pout, &qout) < 0 )
					{
						VS_CMP_Move(&pout, &swap);
						VS_CMP_Move(&qout, &pout);
						VS_CMP_Move(&swap, &qout);
					}

					break;
				}
			}

			CMP_Destructor(&rnd);
		}	//	end		for (int j = 0; j<20; j++)

		if (0 == nFound)
		{
			dwResult =	E_P8_ERROR_FINDING_PRIMES;
			break;
		}

				//	this function will fill the private key structure will all the
				//	remaining data
		dwResult =	FillPrivateKeyStructure
					(
						io_psRSAKey,
						&pout,
						&qout
					);
		if (0 != dwResult)
		{
			break;
		}

		dwResult =	0;
	}	while (0);

	CMP_Destructor(&n);
	CMP_Destructor(&e);
	CMP_Destructor(&d);
	CMP_Destructor(&pout);
	CMP_Destructor(&qout);

	CMP_Destructor(&swap);

	CMP_Constructor(&ed);
	CMP_Constructor(&one);
	CMP_Constructor(&edm1);

	CMP_Constructor(&s);
	CMP_Constructor(&t);

	return	dwResult;
}

//	test if the number is divisible by 2
int is_div_2(CMPInt x)
{
	CMPInt		r;
	CMPInt		two;
	CMPInt		zero;
	CMPInt		quotient;
	int			nReturn = 0;

	CMPInt		NumberOfTwo;


	CMP_Constructor(&r);
	CMP_Constructor(&two);
	CMP_Constructor(&zero);
	CMP_Constructor(&quotient);

	CMP_CMPWordToCMPInt((CMPWord) 2, &two);
	CMP_CMPWordToCMPInt((CMPWord) 0, &zero);
	
		//	divide by 2
	CMP_Divide (&x, &two, &quotient, &r);

		//	compare remainder with 0
	if (0 == VS_CMP_Compare(&r, &zero))
	{
		nReturn	=	1;
	}

	CMP_Destructor(&r);
	CMP_Destructor(&two);
	CMP_Destructor(&zero);
	CMP_Destructor(&quotient);
	
	return	nReturn;
}


//	find s and t, such that ed-1 = (2^s)*t where t is an odd int
int find_s_t(CMPInt i_edm1, CMPInt* o_ps, CMPInt* o_pt)
{
	CMPInt		one;
	CMPInt		two;
	CMPInt		NumberOfTwo;
	CMPInt		remainder;
	CMPInt		temp;

	CMP_Constructor(&one);
	CMP_Constructor(&two);
	CMP_Constructor(&NumberOfTwo);
	CMP_Constructor(&remainder);

	CMP_CMPWordToCMPInt((CMPWord) 1, &one);
	CMP_CMPWordToCMPInt((CMPWord) 2, &two);
	CMP_CMPWordToCMPInt((CMPWord) 0, &NumberOfTwo);

		//	to start with
		//	t = ed - 1
	CMP_Constructor(o_pt);
	VS_CMP_AddInPlace(&i_edm1, o_pt);
	CMP_Constructor(&temp);

		//	while t is divisible by 2
	while (is_div_2(*o_pt))
	{
			//	NumberOfTwo += 1
		VS_CMP_AddInPlace(&one, &NumberOfTwo);

			//	temp = t/2
		CMP_Divide(o_pt, &two, &temp, &remainder);

			//	t = temp
		CMP_Destructor(o_pt);
		CMP_Constructor(o_pt);
		VS_CMP_AddInPlace(&temp, o_pt);
		CMP_Destructor(&temp);
		CMP_Constructor(&temp);
	}

		//	s = NumberOfTwo
	CMP_Constructor(o_ps);
	VS_CMP_AddInPlace(&NumberOfTwo, o_ps);

	CMP_Destructor(&one);
	CMP_Destructor(&two);
	CMP_Destructor(&NumberOfTwo);
	CMP_Destructor(&remainder);

	return 1;
}


	//	check if t and s satisfy the required properties
int check_props(CMPInt s, CMPInt t, CMPInt a, CMPInt n, int* pniout)
{
	CMPInt		i, pos1, neg1;
	int			nReturn		=	0;
	int			ni			=	0;


	ni = 1;
	CMP_Constructor(&i);
	CMP_CMPWordToCMPInt((CMPWord) ni, &i);
	CMP_Constructor(&pos1);
	CMP_CMPWordToCMPInt((CMPWord) 1, &pos1);
	CMP_Constructor(&neg1);
	CMP_CMPWordToCMPInt((CMPWord) -1, &neg1);

	while ( (VS_CMP_Compare(&i, &s)) <= 0 )
	{
		if (prop1(ni,t,a,n) && prop2(pos1,ni,t,a,n) && prop2(neg1,ni,t,a,n) ) 
		{
			*pniout = ni;
			nReturn	=	1;
			break;
		}

		ni++;
		CMP_Constructor(&i);
		CMP_CMPWordToCMPInt((CMPWord) ni, &i);
	}

	CMP_Destructor(&i);
	CMP_Destructor(&pos1);
	CMP_Destructor(&neg1);

	return	nReturn;
}


int prop1(int ni, CMPInt t, CMPInt a, CMPInt n)
{
	int			nReturn		=	0;
	CMPInt		x, twoi, modmult;
	CMPInt		modsub;
	CMPInt		one, zero;

	CMP_Constructor(&one);
	CMP_Constructor(&zero);
	CMP_Constructor(&twoi);
	CMP_Constructor(&x);
	CMP_Constructor(&modmult);
	CMP_Constructor(&modsub);

	CMP_CMPWordToCMPInt((CMPWord) 1, &one);
	CMP_CMPWordToCMPInt((CMPWord) 0, &zero);

			//	x = t * 2 ^ i
	CMP_PowerOfTwo(ni, &twoi);
	CMP_Multiply(&twoi, &t, &x);

			//	modmult = a ^ x  mod n
	VS_CMP_ModExp(&a, &x, &n, &modmult, NULL);

			//	make sure that 
			//	modmult - 1 mod n == 0
	CMP_ModSubtract(&modmult, &one, &n, &modsub);
	if (VS_CMP_Compare(&zero, &modsub)==0)
	{
		nReturn = 1;
	}

	CMP_Destructor(&one);
	CMP_Destructor(&zero);
	CMP_Destructor(&twoi);
	CMP_Destructor(&x);
	CMP_Destructor(&modmult);
	CMP_Destructor(&modsub);

	return	nReturn;
}


int prop2(CMPInt pos, int ni, CMPInt t, CMPInt a, CMPInt n)
{
	int			nReturn		=	0;

	CMPInt		x, twoim1, modmult;
	CMPInt		modsub;
	CMPInt		zero;

	CMP_Constructor(&zero);
	CMP_Constructor(&twoim1);
	CMP_Constructor(&x);
	CMP_Constructor(&modmult);
	CMP_Constructor(&modsub);

			//	x = t * 2 ^ (i-1)
	CMP_PowerOfTwo(ni-1, &twoim1);
	CMP_Multiply(&twoim1, &t, &x);

			//	modmult = a ^ x  mod n
	VS_CMP_ModExp(&a, &x, &n, &modmult, NULL);

			//	make sure that
			//	modmult - pos mod n != 0
			//	pos is alternatively +/- 1
	CMP_ModSubtract(&modmult, &pos, &n, &modsub);
	if (VS_CMP_Compare(&zero, &modsub)!=0)
	{
		nReturn = 1;
	}

	CMP_Destructor(&zero);
	CMP_Destructor(&twoim1);
	CMP_Destructor(&x);
	CMP_Destructor(&modmult);
	CMP_Destructor(&modsub);

	return	nReturn;
}

		//	get primes
int get_pq(CMPInt a, int ni, CMPInt t, CMPInt n, CMPInt* pout, CMPInt* qout)
{
	int		nReturn		=	1;

	CMPInt	one, remainder, twoim1, x, modmult;

	CMP_Constructor(&twoim1);
	CMP_Constructor(&x);
	CMP_Constructor(&modmult);
	CMP_Constructor(&remainder);

	CMP_Constructor(&one);
	CMP_CMPWordToCMPInt((CMPWord) 1, &one);

		//	x = t * 2 ^ (i-1)
	CMP_PowerOfTwo(ni-1, &twoim1);
	CMP_Multiply(&twoim1, &t, &x);

		//	modmult = a ^ x mod n
	VS_CMP_ModExp(&a, &x, &n, &modmult, NULL);
		//	modmult -= 1
	VS_CMP_SubtractInPlace(&one, &modmult);

		//	p = gcd (modmult, n)
	CMP_ComputeGCD(&modmult, &n, pout);
		//	q = n / p
	CMP_Divide(&n, pout, qout, &remainder);

	CMP_Destructor(&twoim1);
	CMP_Destructor(&x);
	CMP_Destructor(&modmult);
	CMP_Destructor(&remainder);

	CMP_Destructor(&one);

	return	nReturn;
}

int	FillPrivateKeyStructure(A_PKCS_RSA_PRIVATE_KEY* io_psRSAKey, CMPInt* pout, CMPInt* qout)
{
	DWORD		dwResult			=	999;

	CMPInt		coefficient, ExponentP, ExponentQ, d;

	BYTE		pbyteBuffer[BUFFER_LEN];
	DWORD		dwBufferLen			=	BUFFER_LEN;

	CMP_Constructor(&coefficient);
	CMP_Constructor(&ExponentP);
	CMP_Constructor(&ExponentQ);
	CMP_Constructor(&d);

	do
	{
			//	copy the primes to the key structure
		dwResult =	CMP_CMPIntToOctetString
					(
						pout,
						BUFFER_LEN,
						(unsigned int*) &dwBufferLen,
						pbyteBuffer
					);
		if ( 0 != dwResult )
		{
			dwResult =	E_P8_ERROR_FINDING_PRIMES;
			break;
		}

		P12_EXP_ALLOC_AND_BYTEBLOB_COPY(	(io_psRSAKey->prime[0]).data,\
											pbyteBuffer,\
											dwBufferLen	)
		(io_psRSAKey->prime[0]).len = dwBufferLen;

		dwResult =	CMP_CMPIntToOctetString
					(
						qout,
						BUFFER_LEN,
						(unsigned int*) &dwBufferLen,
						pbyteBuffer
					);
		if ( 0 != dwResult )
		{
			dwResult =	E_P8_ERROR_FINDING_PRIMES;
			break;
		}

		P12_EXP_ALLOC_AND_BYTEBLOB_COPY(	(io_psRSAKey->prime[1]).data,\
											pbyteBuffer,\
											dwBufferLen	)
		(io_psRSAKey->prime[1]).len = dwBufferLen;

			//	calculate coefficient = (inv (Q) [modP])
		dwResult =	CMP_ModInvert
					(
						qout,
						pout,
						&coefficient
					);
		if ( 0 != dwResult )
		{
			dwResult =	E_P8_ERROR_FINDING_PRIMES;
			break;
		}

			//	Find p - 1 and q - 1
		dwResult = VS_CMP_SubtractCMPWord ((CMPWord)1, pout);
		if (0 != dwResult)
		{
			dwResult =	E_P8_ERROR_FINDING_PRIMES;
			break;
		}

		dwResult = VS_CMP_SubtractCMPWord ((CMPWord)1, qout);
		if (0 != dwResult)
		{
			dwResult =	E_P8_ERROR_FINDING_PRIMES;
			break;
		}

		CMP_OctetStringToCMPInt( (unsigned char*) (io_psRSAKey->privateExponent).data, (io_psRSAKey->privateExponent).len, &d);

			//	calc exponentP = inv (publicExponent) [mod (p - 1)]
			//	and exponentQ = inv (publicExponent) [mod (q - 1)]
		dwResult =	CMP_ModularReduce
					(
						&d, 
						pout,
						&ExponentP
					);
		if (0 != dwResult)
		{
			dwResult =	E_P8_ERROR_FINDING_PRIMES;
			break;
		}

		dwResult =	CMP_ModularReduce
					(
						&d,
						qout,
						&ExponentQ
					);
		if (0 != dwResult)
		{
			dwResult =	E_P8_ERROR_FINDING_PRIMES;
			break;
		}

			//	copy the prime exponents to the key structure
		dwResult =	CMP_CMPIntToOctetString
					(
						&ExponentP,
						BUFFER_LEN,
						(unsigned int*) &dwBufferLen,
						pbyteBuffer
					);
		if ( 0 != dwResult )
		{
			dwResult =	E_P8_ERROR_FINDING_PRIMES;
			break;
		}

		P12_EXP_ALLOC_AND_BYTEBLOB_COPY(	(io_psRSAKey->primeExponent[0]).data,\
											pbyteBuffer,\
											dwBufferLen	)
		(io_psRSAKey->primeExponent[0]).len = dwBufferLen;

		dwResult =	CMP_CMPIntToOctetString
					(
						&ExponentQ,
						BUFFER_LEN,
						(unsigned int*) &dwBufferLen,
						pbyteBuffer
					);
		if ( 0 != dwResult )
		{
			dwResult =	E_P8_ERROR_FINDING_PRIMES;
			break;
		}

		P12_EXP_ALLOC_AND_BYTEBLOB_COPY(	(io_psRSAKey->primeExponent[1]).data,\
											pbyteBuffer,\
											dwBufferLen	)
		(io_psRSAKey->primeExponent[1]).len = dwBufferLen;

			//	copy the coefficient to the key structure
		dwResult =	CMP_CMPIntToOctetString
					(
						&coefficient,
						BUFFER_LEN,
						(unsigned int*) &dwBufferLen,
						pbyteBuffer
					);
		if ( 0 != dwResult )
		{
			dwResult =	E_P8_ERROR_FINDING_PRIMES;
			break;
		}

		P12_EXP_ALLOC_AND_BYTEBLOB_COPY(	(io_psRSAKey->coefficient).data,\
											pbyteBuffer,\
											dwBufferLen	)
		(io_psRSAKey->coefficient).len = dwBufferLen;

		dwResult =	0;
	}	while (0);

	CMP_Destructor(&coefficient);
	CMP_Destructor(&ExponentP);
	CMP_Destructor(&ExponentQ);
	CMP_Destructor(&d);

	return	dwResult;
}