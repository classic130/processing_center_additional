#ifndef _PKCS12_MACROS_H
#define _PKCS12_MACROS_H

#define PKCS12_CHECK_HRESULT if(S_OK != hResult) \
								break;
#define PKCS12_CHECK_MEMALLOC(pbyteBlob) {\
		if(!pbyteBlob)	{\
			hResult = E_FAIL;\
			break;\
		} \
	}

#define PKCS12_CHECK_FOR_NULL(pPtr, valToSet) {\
		if(!pPtr) {\
			hResult = valToSet;\
			break;\
		}\
	}

#define PKCS12_FREE_MEM(pPtr) {\
	if(pPtr)\
	{\
		delete[] pPtr;\
		pPtr = NULL;\
	}\
}
#endif
