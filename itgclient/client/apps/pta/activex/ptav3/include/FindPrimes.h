#ifndef		__P12_FIND_PRIMES_H__
#define		__P12_FIND_PRIMES_H__

#include "integrate.h"

#define		P12_EXP_ALLOC_AND_BYTEBLOB_COPY(pbyteDest, pbyteSource, dwLength)	{\
		pbyteDest = new BYTE [dwLength];\
		if ( NULL == pbyteDest )\
		{\
			dwResult =	E_VS_OUT_OF_MEMORY;\
			break;\
		}\
		::memcpy ( pbyteDest, pbyteSource, dwLength);\
	}

#define		P12_EXP_CHECK_ALLOCATED_MEMORY(pPointer)	{\
		if ( NULL == pPointer )\
		{\
			hResult =	NTE_NO_MEMORY;\
			break;\
		}\
	}


int	FindPrimes(A_PKCS_RSA_PRIVATE_KEY* io_psRSAKey);
int find_s_t(CMPInt i_edm, CMPInt* o_ps, CMPInt* o_pt);
int is_div_2(CMPInt x);
int check_props(CMPInt s, CMPInt t, CMPInt a, CMPInt n, int* pniout);
int prop1(int ni, CMPInt t, CMPInt a, CMPInt n);
int prop2(CMPInt pos, int ni, CMPInt t, CMPInt a, CMPInt n);
int get_pq(CMPInt a, int ni, CMPInt t, CMPInt n, CMPInt* pout, CMPInt* qout);
int	FillPrivateKeyStructure(A_PKCS_RSA_PRIVATE_KEY* io_psRSAKey, CMPInt* pout, CMPInt* qout);

#endif