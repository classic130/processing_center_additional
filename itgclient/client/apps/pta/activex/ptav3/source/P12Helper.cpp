#include "stdafx.h"
#include "P12Helper.h"

#include "pkcs12defines.h"
#include "pkcs12errs.h"
#include "pkcs12macros.h"
#include "simder_all.h"
#include <wincrypt.h> //For OID definitions.
#include "..\..\BSafeLite\include\integrate.h"
#include "md5.h"
#include "md2.h"
#include "sha.h"
#include <math.h>
#include "P12Helper.h"
#include "ptaerrs.h"
#include "FindPrimes.h"
#include "MyUniversalInteger.h"


/*
Function Name : _GetHMACKey
Purpose : This function creates the key that will be used for the HMAC operation from the password, salt and iterations
		  value

Parameters :	i_tbstrPassword - The integrity password used for calculating the HMAC key.
				i_pbyteSalt - The salt blob used to compute the key for the HMAC operation. 
				i_dwSaltSize - The size of the salt blob
				i_dwIterations - The number of iterations used while computing the key for the HMAC 
								  operation.
				o_pbyteKey - The HMAC key. If this parameter is NULL, the size of the key will be returned in the next
							 parameter.
				o_pdwKeySize - The size of the Key blob

				
Return :		S_OK - Operation succeeded.
				

*/
HRESULT _GetHMACKey(_bstr_t& i_tbstrPassword, BYTE* i_pbyteSalt, DWORD i_dwSaltSize, DWORD i_dwIterations, 
								BYTE* o_pbyteKey, DWORD* o_pdwKeySize)
{
	HRESULT hResult = S_OK;
	
	do
	{
		//Set the HMAC Key Size
		*o_pdwKeySize = HMAC_KEY_SIZE;
		if(!o_pbyteKey)
		{
			break;
		}

		/*Use the P12 KeyGen Algorithm to obtain the required key of the required size*/
		hResult = _DoP12KeyGen(i_tbstrPassword,i_pbyteSalt,i_dwSaltSize, i_dwIterations, ID_HMAC, o_pbyteKey, *o_pdwKeySize);
		PKCS12_CHECK_HRESULT 


	}while(0);

	return hResult;
}



/*
Function Name : _DoP12KeyGen
Purpose : This function creates a key of a required size using the P12 key gen algorithm using the password, salt
		  and iterations.

Parameters :	i_tbstrPassword - The password used for calculating the key.
				i_pbyteSalt - The salt blob used to compute the key for the HMAC operation. 
				i_dwSaltSize - The size of the salt blob
				i_dwIterations - The number of iterations used while computing the key for the HMAC 
								  operation.
				i_byteID	- An ID determining the type of key to generate. As per the p12 specification this value can be
							  ID_ENCKEY = 1 - The key is being generated for encryption
							  ID_IV = 2 - The key is being generated for use as an IV
							  ID_HMAC =3 - The key is being generated for use in HMAC
				o_pbyteKey - The HMAC key. If this parameter is NULL, the size of the key will be returned in the next
							 parameter.
				i_dwKeySize - The size of the Key blob

				
Return :		S_OK - Operation succeeded.
				

*/
HRESULT _DoP12KeyGen(_bstr_t& i_tbstrPassword, BYTE* i_pbyteSalt, DWORD i_dwSaltSize, DWORD i_dwIterations, BYTE i_byteID,
								BYTE* o_pbyteKey, DWORD i_dwKeySize)
{
	HRESULT hResult = S_OK;
	BYTE* pbyteD = NULL;
	BYTE* pbyteS = NULL;
	BYTE* pbyteP = NULL;
	BYTE* pbyteI = NULL;
	BYTE* pbyteB = NULL;
	BYTE* pbyteA = NULL;
	BYTE* pbytePasswdBMPString = NULL;
	DWORD dwSSize =0;
	DWORD dwPSize = 0;
	DWORD dwISize = 0;
	DWORD dwASize = 0;
	int v = 0;
	int u = 0;
	int p = 0;
	int n = 0;
	int s = 0;
	int c = 0;
	int k = 0;

	do
	{
		/*
		The algorithm for key gen as specified in the p12 specs is as follows :
		1. Let u = 160 - Size of the SHA1 hash output in bits
		2. Let v = 512 - Size of the SHA1 block size in bits
		3. Let p = 8*password length - The size of the password in bits. The password is represented as a null terminated unicode string
		4. Let s = 8*i_dwSaltSize
		5. Let n = 8*i_dwKeySize - The number of bits required for the key
		6. Construct a string, D by concatenating v/8 copies of the ID
		7. Concatenate copies of the salt together to create a string S of length v.ceil(s/v) bits
		8. Concatenate copies of the password together to create a string P of length v.ceil(p/v) bits
		9. Set I=S||P
		10. Set c=ceil(n/u)
		11. For i = 1,2,...,c
				a) Set Ai = H^r(D||I) i.e. the rth hash of D||I
				b) Concatenate copies of Ai to create a string B of length v bits
				c) Treating I as a concatenation of I0,I1,...I(k-1) where k = ceil(s/v)+ceild(p/v)
					modify I by setting Ij=(Ij+B+1) mod 2^v for each j
		12. Concatenate A1,A2,...Ac together to form string A
		13. Use the first n bits of A as the key
		*/

		//Perform step 1
		u = SHA_SIZE_INBYTES * 8;

		//Perform step 2
		v = HASH_BLOCKSIZE_INBYTES * 8;

		//Peform step 3
		p = 8*((i_tbstrPassword.length()+1)* 2); //The +1 is done to account for the null terminator
		
		//Peform step 4
		s = 8*i_dwSaltSize;

		//Perform step 5
		n = 8*i_dwKeySize;

		//Perform step 6
		pbyteD = (BYTE*)new BYTE[v/8];
		PKCS12_CHECK_MEMALLOC(pbyteD)		
		memset(pbyteD,i_byteID,v/8);

		//Peform step 7
		dwSSize = (DWORD)(v* ceil((double)s/(double)v));
		pbyteS = (BYTE*) new BYTE[dwSSize/8];
		PKCS12_CHECK_MEMALLOC(pbyteS)		
		
		hResult = _CatToFillBuffer(pbyteS,dwSSize/8,i_pbyteSalt,i_dwSaltSize);
		PKCS12_CHECK_HRESULT 

		//Perform step 8
		dwPSize = (DWORD)(v * ceil((double)p/(double)v));
		pbyteP = (BYTE*) new BYTE[dwPSize/8];
		PKCS12_CHECK_MEMALLOC(pbyteS)		

		//Create the password string in the bmpstring format
		pbytePasswdBMPString = new BYTE[p/8];
		PKCS12_CHECK_MEMALLOC(pbytePasswdBMPString)		

		memcpy(pbytePasswdBMPString, (BYTE*)(WCHAR*)i_tbstrPassword, p/8);

		BYTE temp;
		for(int i=0;i<p/8;i+=2)
		{
			temp = pbytePasswdBMPString[i];
			pbytePasswdBMPString[i] = pbytePasswdBMPString[i+1];
			pbytePasswdBMPString[i+1] = temp;
		}

		hResult = _CatToFillBuffer(pbyteP,dwPSize/8,pbytePasswdBMPString,p/8);
		PKCS12_CHECK_HRESULT 

		//Perform step 9
		dwISize = dwSSize + dwPSize;
		pbyteI = (BYTE*) new BYTE[dwISize/8];
		PKCS12_CHECK_MEMALLOC(pbyteI)
		
		memcpy(pbyteI,pbyteS,dwSSize/8);
		memcpy(pbyteI+(dwSSize/8),pbyteP,dwPSize/8);

		//Perform step 10
		c = (DWORD)ceil((double)n / (double)u);

		/*Perform steps 11 and 12*/
		dwASize = c * u;
		pbyteA = (BYTE*) new BYTE[dwASize/8];
		PKCS12_CHECK_MEMALLOC(pbyteA)

		BOOL boolDone = FALSE;
		void* pvoidCtxt;

		c = 0;

		do
		{
			//Calculate the hash of (D||I)
			if(HashBegin(HASH_SHA1, &pvoidCtxt))
			{
				hResult = E_HASHBEGIN_FAILED;
				break;
			}

			if(HashData(HASH_SHA1, pvoidCtxt,pbyteD,v/8))
			{
				hResult = E_HASHDATA_FAILED;
				break;
			}

			if(HashData(HASH_SHA1, pvoidCtxt,pbyteI,dwISize/8))
			{
				hResult = E_HASHDATA_FAILED;
				break;
			}


			if(HashEnd(HASH_SHA1, pvoidCtxt,pbyteA+(c* u /8), u/8))
			{
				hResult = E_HASHEND_FAILED;
				break;
			}
			pvoidCtxt = NULL;

			//Now iteratively hash the above digest
			for(DWORD i=1; i<i_dwIterations;++i)  //Start with 1 because we have already done one hash
			{
				if(HashBegin(HASH_SHA1, &pvoidCtxt))
				{
					hResult = E_HASHBEGIN_FAILED;
					break;
				}

				if(HashData(HASH_SHA1, pvoidCtxt,pbyteA+(c* u /8),u/8))
				{
					hResult = E_HASHDATA_FAILED;
					break;
				}

				if(HashEnd(HASH_SHA1, pvoidCtxt,pbyteA+(c* u /8), u/8))
				{
					hResult = E_HASHEND_FAILED;
					break;
				}
				pvoidCtxt = NULL;
			}
			
			c++;

			//We now have Ai. Find out if we need to calculate B and modify I
			if((DWORD)c*u < dwASize)
			{
				//Create the string B
				pbyteB = (BYTE*)new BYTE[v/8];
				PKCS12_CHECK_MEMALLOC(pbyteA)

				hResult = _CatToFillBuffer(pbyteB,v/8,pbyteA+((c-1) * u/8),u/8);
				PKCS12_CHECK_HRESULT 

				CMPInt cmpintB;
				CMPInt cmpintIj;
				CMPInt cmpint2Powv;
				CMPInt cmpintSum;
				unsigned int nTemp;

				CMP_Constructor(&cmpintIj);
				CMP_Constructor(&cmpintSum);

				CMP_Constructor(&cmpintB);
				if(CMP_OctetStringToCMPInt(pbyteB, v/8, &cmpintB))
				{
					hResult = E_OCTET2CMPINT_FAILED;
					break;
				}

				CMP_Constructor(&cmpint2Powv);
				if(CMP_PowerOfTwo(v, &cmpint2Powv))
				{
					hResult = E_POWOF2_FAILED;
					break;
				}

				for(DWORD i=0;i<dwISize/v;++i)
				{
					if(CMP_OctetStringToCMPInt(pbyteI+(i* v/8), v/8, &cmpintIj))
					{
						hResult = E_OCTET2CMPINT_FAILED;
						break;
					}

					if(VS_CMP_Add(&cmpintIj, &cmpintB, &cmpintSum))
					{
						hResult = E_CMPINTADD_FAILED;
						break;
					}

					if(VS_CMP_AddCMPWord(1,&cmpintSum))
					{
						hResult = E_CMPINTADDWORD_FAILED;
						break;
					}

					if(CMP_ModularReduce(&cmpintSum,&cmpint2Powv,&cmpintIj))
					{
						hResult = E_CMPINTMODRED_FAILED;
						break;
					}

					if(CMP_CMPIntToOctetString(&cmpintIj, v/8,&nTemp,pbyteI+(i*v/8)))
					{
						hResult = E_CMPINT2OCTET_FAILED;
						break;
					}
					if(nTemp < v/8)
					{
						memset(pbyteI+(i*v/8), 0, v/8);
					
						if(CMP_CMPIntToOctetString(&cmpintIj, v/8,&nTemp,pbyteI+(i*v/8)+(v/8 - nTemp)))
						{
							hResult = E_CMPINT2OCTET_FAILED;
							break;
						}
					}


				}

				CMP_Destructor(&cmpintB);
				CMP_Destructor(&cmpint2Powv);
				CMP_Destructor(&cmpintIj);
				CMP_Destructor(&cmpintSum);
	
			}
			else
			{
				boolDone = TRUE;
			}

		}while(!boolDone);
		
		PKCS12_CHECK_HRESULT 

		//Perform step 13
		memcpy(o_pbyteKey, pbyteA, i_dwKeySize);

		
	}while(0);

	PKCS12_FREE_MEM(pbyteD)
	PKCS12_FREE_MEM(pbyteS)
	PKCS12_FREE_MEM(pbyteP)
	PKCS12_FREE_MEM(pbyteI)
	PKCS12_FREE_MEM(pbyteB)
	PKCS12_FREE_MEM(pbyteA)
	PKCS12_FREE_MEM(pbytePasswdBMPString)

	return hResult;
}


/*
Function Name : _CatToFillBuffer
Purpose : Fill the buffer with the given filler. The filler is repeated till all the bytes in the buffer are filled.

Parameters :	i_pbyteBuffer - The buffer to be filled.
				i_dwBufferSize - The size of the buffer in bytes. 
				i_pbyteFiller - The filler to be used to fill the buffer
				i_dwFillerSize - The size of the filler in bytes
				
Return :		S_OK - Operation succeeded.
				

*/
HRESULT _CatToFillBuffer(BYTE* i_pbyteBuffer,DWORD i_dwBufferSize,BYTE* i_pbyteFiller,DWORD i_dwFillerSize)
{
	HRESULT hResult = S_OK;
	
	do
	{
		for(DWORD i=0;i<i_dwBufferSize;++i)
		{
			i_pbyteBuffer[i] = i_pbyteFiller[(i%i_dwFillerSize)];
		}
	}while(0);

	return hResult;
}


/*
Function Name : _GetHMACDigest
Purpose : This function calls into BSafeLite to perform the HMAC digest.

Parameters :	i_pbyteAuthSafe - The buffer to be HMACed.
				i_dwAuthSafeSize - The size of the buffer in bytes. 
				i_dwDigestAlg - The digest alg to be used for doing the HMAC
				i_pbyteHMACKey - The HMAC key
				i_dwHMACKeySize = The HMAC key size
				o_pbyteHMACDigest - The HMAC digest
				
Return :		S_OK - Operation succeeded.
				

*/
HRESULT _GetHMACDigest(BYTE* i_pbyteAuthSafe,DWORD i_dwAuthSafeSize, DWORD i_dwDigestAlg, BYTE* i_pbyteHMACKey,DWORD i_dwHMACKeySize, BYTE* o_pbyteHMACDigest)
{
	HRESULT hResult = S_OK;
	void* pvoidCtxt = NULL;

	do
	{
		if(HMACBegin(i_dwDigestAlg,i_pbyteHMACKey,i_dwHMACKeySize,&pvoidCtxt))
		{
			hResult = E_HMACBEGIN_FAILED;
			break;
		}

		if(HMACData(pvoidCtxt, i_pbyteAuthSafe, i_dwAuthSafeSize))
		{
			hResult = E_HMACDATA_FAILED;
			break;
		}

		if(HMACFinal(pvoidCtxt, o_pbyteHMACDigest))
		{
			hResult = E_HMACFINAL_FAILED;
			break;
		}

	}while(0);

	return hResult;
}


/*
Function Name : HMACBegin
Purpose : This function initializes the HMAC operation. It creates a new hmac context and 
		  stores the information provided to the function into the context.

Parameters :	i_nDigestAlg - The digest algorithm to be used to perform the HMAC
				i_pbyteHMACKey - The key to be used to calculate the HMAC
				i_dwHMACKeySize - The size of the HMAC keys
				o_ppvoidCtxt - The HMAC context. This context should be passed to other HMAC
				functions.
				
Return :		0 - Success
				-1 - Failure

*/
int HMACBegin(int i_nDigestAlg,BYTE* i_pbyteHMACKey,int i_dwHMACKeySize,void** o_ppvoidCtxt)
{
	HRESULT hResult = S_OK;

	do
	{
		*o_ppvoidCtxt = (void*)(HMACCtxt*)new HMACCtxt;
		PKCS12_CHECK_MEMALLOC(*o_ppvoidCtxt)	

		((HMACCtxt*)(*o_ppvoidCtxt))->nHashAlg = i_nDigestAlg;
		((HMACCtxt*)(*o_ppvoidCtxt))->dwKeySize = i_dwHMACKeySize;
		((HMACCtxt*)(*o_ppvoidCtxt))->pbyteKey = (BYTE*)new BYTE[i_dwHMACKeySize];
		PKCS12_CHECK_MEMALLOC(((HMACCtxt*)(*o_ppvoidCtxt))->pbyteKey)	

		memcpy(((HMACCtxt*)(*o_ppvoidCtxt))->pbyteKey, i_pbyteHMACKey,i_dwHMACKeySize);
		((HMACCtxt*)(*o_ppvoidCtxt))->pbyteDigest = NULL;
		((HMACCtxt*)(*o_ppvoidCtxt))->pvoidDigestCtxt = NULL;



	}while(0);

	if(hResult != S_OK)
		return -1;
	else
		return 0;
	
}


/*
Function Name : HMACData
Purpose : This function performs HMAC on the inputted data. (as specified in RFC 2104

Parameters :	i_pvoidCtxt - The HMAC context returned by HMACBegin
				i_pbyteData - The data to be HMACed
				i_dwDataSize - The size of the data to be HMACed
				
Return :		0 - Success
				-1 - Failure

*/

int HMACData(void* i_pvoidCtxt, BYTE* i_pbyteData, DWORD i_dwDataSize)
{
	HRESULT hResult = S_OK;
	BYTE bytek_ipad[HASH_BLOCKSIZE_INBYTES];
	BYTE bytek_opad[HASH_BLOCKSIZE_INBYTES];
	DWORD dwDigestSize = 0;
	HMACCtxt* theHMACCtxt = NULL;

	theHMACCtxt = (HMACCtxt*)i_pvoidCtxt;

	do
	{	
		switch(theHMACCtxt->nHashAlg)
		{
		case IMPP12_MD2 :
		case IMPP12_MD5 :
			dwDigestSize = MD_SIZE_INBYTES;
			break;

		case IMPP12_SHA :
			dwDigestSize = SHA_SIZE_INBYTES;
			break;

		}
		theHMACCtxt->pbyteDigest = (BYTE*)new BYTE[dwDigestSize];
		PKCS12_CHECK_MEMALLOC(theHMACCtxt->pbyteDigest)	

		/*Note we are omitting the key folding step because it will not be required in this
		implentation.*/
		/*Create the (k XOR ipad) and (k XOR opad)*/
		memset(bytek_ipad, 0, HASH_BLOCKSIZE_INBYTES);
		memset(bytek_opad, 0, HASH_BLOCKSIZE_INBYTES);

		memcpy(bytek_ipad, theHMACCtxt->pbyteKey, theHMACCtxt->dwKeySize);
		memcpy(bytek_opad, theHMACCtxt->pbyteKey, theHMACCtxt->dwKeySize);

		for(int i=0;i<HASH_BLOCKSIZE_INBYTES;++i)
		{
			bytek_ipad[i] ^= 0x36;
			bytek_opad[i] ^= 0x5c;
		}
		

		/*Now create digest = H(K XOR ipad, data)
		  Then create H(K XOR opad, digest)*/
		switch(theHMACCtxt->nHashAlg)
		{
		case IMPP12_MD2 :
			theHMACCtxt->pvoidDigestCtxt = (void*)new A_MD2_CTX;
			PKCS12_CHECK_MEMALLOC(theHMACCtxt->pvoidDigestCtxt)	

			A_MD2Init((A_MD2_CTX*)(theHMACCtxt->pvoidDigestCtxt));
			
			A_MD2Update((A_MD2_CTX*)(theHMACCtxt->pvoidDigestCtxt), bytek_ipad, HASH_BLOCKSIZE_INBYTES);
			
			A_MD2Update((A_MD2_CTX*)(theHMACCtxt->pvoidDigestCtxt), i_pbyteData, i_dwDataSize);
			
			A_MD2Final((A_MD2_CTX*)(theHMACCtxt->pvoidDigestCtxt), theHMACCtxt->pbyteDigest);
			
			A_MD2Init((A_MD2_CTX*)(theHMACCtxt->pvoidDigestCtxt));
			
			A_MD2Update((A_MD2_CTX*)(theHMACCtxt->pvoidDigestCtxt), bytek_opad, HASH_BLOCKSIZE_INBYTES);
			
			A_MD2Update((A_MD2_CTX*)(theHMACCtxt->pvoidDigestCtxt), theHMACCtxt->pbyteDigest, dwDigestSize);
			
			break;

		case IMPP12_MD5 :
			theHMACCtxt->pvoidDigestCtxt = (void*)new A_MD5_CTX;
			PKCS12_CHECK_MEMALLOC((theHMACCtxt->pvoidDigestCtxt))	

			A_MD5Init((A_MD5_CTX*)(theHMACCtxt->pvoidDigestCtxt));
			
			A_MD5Update((A_MD5_CTX*)(theHMACCtxt->pvoidDigestCtxt), bytek_ipad, HASH_BLOCKSIZE_INBYTES);
			
			A_MD5Update((A_MD5_CTX*)(theHMACCtxt->pvoidDigestCtxt), i_pbyteData, i_dwDataSize);
			
			A_MD5Final((A_MD5_CTX*)(theHMACCtxt->pvoidDigestCtxt), theHMACCtxt->pbyteDigest);
			
			A_MD5Init((A_MD5_CTX*)(theHMACCtxt->pvoidDigestCtxt));
			
			A_MD5Update((A_MD5_CTX*)(theHMACCtxt->pvoidDigestCtxt), bytek_opad, HASH_BLOCKSIZE_INBYTES);
			
			A_MD5Update((A_MD5_CTX*)(theHMACCtxt->pvoidDigestCtxt), theHMACCtxt->pbyteDigest, dwDigestSize);
			
			break;

		case IMPP12_SHA :
			theHMACCtxt->pvoidDigestCtxt= (void*)new A_SHA_CTX;
			PKCS12_CHECK_MEMALLOC((theHMACCtxt->pvoidDigestCtxt))	

			A_SHAInit((A_SHA_CTX*)(theHMACCtxt->pvoidDigestCtxt));
			
			A_SHAUpdate((A_SHA_CTX*)(theHMACCtxt->pvoidDigestCtxt), bytek_ipad, HASH_BLOCKSIZE_INBYTES);
			
			A_SHAUpdate((A_SHA_CTX*)(theHMACCtxt->pvoidDigestCtxt), i_pbyteData, i_dwDataSize);
			
			A_SHAFinal((A_SHA_CTX*)(theHMACCtxt->pvoidDigestCtxt), theHMACCtxt->pbyteDigest);
			
			A_SHAInit((A_SHA_CTX*)(theHMACCtxt->pvoidDigestCtxt));
			
			A_SHAUpdate((A_SHA_CTX*)(theHMACCtxt->pvoidDigestCtxt), bytek_opad, HASH_BLOCKSIZE_INBYTES);
			
			A_SHAUpdate((A_SHA_CTX*)(theHMACCtxt->pvoidDigestCtxt), theHMACCtxt->pbyteDigest, dwDigestSize);
			
			break;

		}
		PKCS12_CHECK_HRESULT 



	}while(0);

	if(hResult != S_OK)
		return -1;
	else
		return 0;

}


/*
Function Name : HMACFinal
Purpose : This function returns the HMAC Digest and frees the context

Parameters :	i_pvoidCtxt - The HMAC context returned by HMACBegin
				o_pbyteHMACDigest - The HMAC Digest

Return :		0 - Success
				-1 - Failure

*/

int HMACFinal(void* i_pvoidCtxt, BYTE* o_pbyteHMACDigest)
{
	HRESULT hResult = S_OK;
	HMACCtxt* theHMACCtxt = NULL;

	theHMACCtxt = (HMACCtxt*)i_pvoidCtxt;

	do
	{
		/*Do the final hash*/
		switch(theHMACCtxt->nHashAlg)
		{
		case IMPP12_MD2 :
		
			A_MD2Final((A_MD2_CTX*)(theHMACCtxt->pvoidDigestCtxt), o_pbyteHMACDigest);
			
			break;

		case IMPP12_MD5 :

			A_MD5Final((A_MD5_CTX*)(theHMACCtxt->pvoidDigestCtxt), o_pbyteHMACDigest);
			
			break;

		case IMPP12_SHA :
			
			A_SHAFinal((A_SHA_CTX*)(theHMACCtxt->pvoidDigestCtxt), o_pbyteHMACDigest);
			
			break;

		}
		PKCS12_CHECK_HRESULT 

		/*Free the context*/
		PKCS12_FREE_MEM(theHMACCtxt->pbyteDigest)
		PKCS12_FREE_MEM(theHMACCtxt->pbyteKey)
		PKCS12_FREE_MEM(theHMACCtxt->pvoidDigestCtxt)
		PKCS12_FREE_MEM(theHMACCtxt)

	}while(0);

	if(hResult != S_OK)
		return -1;
	else
		return 0;
}



HRESULT _SetParity(BYTE* i_pbyteKey, DWORD i_dwKeySize)
{
	HRESULT hResult = S_OK;

	for (unsigned int i=0; i<i_dwKeySize; i++)
		(i_pbyteKey)[i]=odd_parity[(i_pbyteKey)[i]];

	return hResult;

}


DWORD		CreateP8
(
	A_RSA_KEY			i_RSA_PrivateKey,
	A_RSA_KEY			i_RSA_PublicKey,
	CSequence*			o_pCSeqP8
)
{
	DWORD						dwResult		=	999;
	A_PKCS_RSA_PRIVATE_KEY		sRSA_PrivateKey;

	do
	{
			//	check input parameters
		if (\
				(0 == i_RSA_PrivateKey.modulus.len)		||\
				(0 == i_RSA_PrivateKey.exponent.len)	||\
				(0 == i_RSA_PublicKey.modulus.len)		||\
				(0 == i_RSA_PublicKey.exponent.len)		\
		   )
		{
			dwResult = E_P8_INVALID_PARAMS;
			break;
		}

				//	copy data from A_RSA_KEY structures to the A_PKCS_RSA_PRIVATE_KEY strucutre
		P12_EXP_ALLOC_AND_BYTEBLOB_COPY(	sRSA_PrivateKey.publicExponent.data, \
											i_RSA_PublicKey.exponent.data, \
											i_RSA_PublicKey.exponent.len )
		sRSA_PrivateKey.publicExponent.len = i_RSA_PublicKey.exponent.len;

		P12_EXP_ALLOC_AND_BYTEBLOB_COPY(	sRSA_PrivateKey.privateExponent.data, \
											i_RSA_PrivateKey.exponent.data, \
											i_RSA_PrivateKey.exponent.len )
		sRSA_PrivateKey.privateExponent.len = i_RSA_PrivateKey.exponent.len;
		
		P12_EXP_ALLOC_AND_BYTEBLOB_COPY(	sRSA_PrivateKey.modulus.data, \
											i_RSA_PrivateKey.modulus.data, \
											i_RSA_PrivateKey.modulus.len )
		sRSA_PrivateKey.modulus.len = i_RSA_PrivateKey.modulus.len;

				//	find the primes p and q
		dwResult =	FindPrimes ( &sRSA_PrivateKey );
		if ( 0 != dwResult )
		{
			break;
		}

				//	put the key in the sequence
		dwResult =	PutKeyInSequence
					(
						sRSA_PrivateKey,
						o_pCSeqP8
					);
		if ( 0 != dwResult )
		{
			dwResult =	E_P8_ERROR_ENCODING;
			break;
		}

		dwResult =	0;
	} while (0);


	return	dwResult;
}	//	end		DWORD		CreateP8


DWORD		PutKeyInSequence
(
	A_PKCS_RSA_PRIVATE_KEY			i_sRSA_PrivateKey,
	CSequence*						io_pCSeqPrivateKey
)
{
	DWORD				dwResult				=	999;

	int					nVersion				=	0;

	do
	{
				//	create CUniversalInteger integers for all the required fields
		CMyUniversalInteger	CmuiModulus( i_sRSA_PrivateKey.modulus.len, (_BYTE*) i_sRSA_PrivateKey.modulus.data );
		CMyUniversalInteger	CmuiPublicExponent( i_sRSA_PrivateKey.publicExponent.len, (_BYTE*) i_sRSA_PrivateKey.publicExponent.data );
		CMyUniversalInteger	CmuiPrivateExponent( i_sRSA_PrivateKey.privateExponent.len, (_BYTE*) i_sRSA_PrivateKey.privateExponent.data );
		CMyUniversalInteger	CmuiPrimeP( i_sRSA_PrivateKey.prime[0].len, (_BYTE*) i_sRSA_PrivateKey.prime[0].data );
		CMyUniversalInteger	CmuiPrimeQ( i_sRSA_PrivateKey.prime[1].len, (_BYTE*) i_sRSA_PrivateKey.prime[1].data );
		CMyUniversalInteger	CmuiPrimeExponentP( i_sRSA_PrivateKey.primeExponent[0].len, (_BYTE*) i_sRSA_PrivateKey.primeExponent[0].data );
		CMyUniversalInteger	CmuiPrimeExponentQ( i_sRSA_PrivateKey.primeExponent[1].len, (_BYTE*) i_sRSA_PrivateKey.primeExponent[1].data );
		CMyUniversalInteger	CmuiCoefficient( i_sRSA_PrivateKey.coefficient.len, (_BYTE*) i_sRSA_PrivateKey.coefficient.data );

		CMyUniversalInteger	CmuiVersion( 1, (_BYTE*) &nVersion );

				//	add all the CUniversalInteger to the sequence
		*io_pCSeqPrivateKey +=	CmuiVersion;
		*io_pCSeqPrivateKey +=	CmuiModulus;
		*io_pCSeqPrivateKey +=	CmuiPublicExponent;
		*io_pCSeqPrivateKey +=	CmuiPrivateExponent;
		*io_pCSeqPrivateKey +=	CmuiPrimeP;
		*io_pCSeqPrivateKey +=	CmuiPrimeQ;
		*io_pCSeqPrivateKey +=	CmuiPrimeExponentP;
		*io_pCSeqPrivateKey +=	CmuiPrimeExponentQ;
		*io_pCSeqPrivateKey +=	CmuiCoefficient;

		dwResult =	0;
	}	while (0);

	return	dwResult;
}	//	end		PutKeyInSequence
