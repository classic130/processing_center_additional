#ifndef		__VS_CSP_MACROS__
#define		__VS_CSP_MACROS__


#define		VSCSP_CHECK_INPUT_POINTER_FOR_NULL(i_pPointer)	{\
		if ( NULL == i_pPointer )\
		{\
			hResult =	ERROR_INVALID_PARAMETER;\
			::SetLastError ( (DWORD)hResult );\
			break;\
		}\
	}

#define		VSCSP_CHECK_INPUT_STRING(i_szInputString)	{\
		if ( NULL == i_szInputString )\
		{\
			hResult =	ERROR_INVALID_PARAMETER;\
			::SetLastError ( (DWORD)hResult );\
			break;\
		}\
	}

#define		VSCSP_CHECK_INPUT_STRING_LEN(i_szInputString)	{\
		if ( 0 == lstrlen ( i_szInputString ) )\
		{\
			hResult =	ERROR_INVALID_PARAMETER;\
			::SetLastError ( (DWORD)hResult );\
			break;\
		}\
	}

#define		VSCSP_CHECK_HRESULT	if ( VS_SUCCESS != hResult )\
	{\
		dwLastError =	hResult;\
		break;\
	}

#define		VSM_CHECK_HRESULT	if ( VS_SUCCESS != hResult )\
	{\
		::SetLastError ( (DWORD) hResult );\
		break;\
	}


#define		VSCSP_CHECK_HRESULT_AND_BREAK if (VS_SUCCESS != hResult )\
	{\
		break;\
	}

#define		VSCSP_CHECK_NRESULT	if ( VS_SUCCESS != nResult )\
	{\
		::SetLastError ( (DWORD) nResult );\
		break;\
	}

#define		VSCSP_CHECK_ALLOCATED_MEMORY(pPointer)	{\
		if ( NULL == pPointer )\
		{\
			dwLastError =	NTE_NO_MEMORY;\
			break;\
		}\
	}

#define		CHECK_ALLOCATED_MEMORY(pPointer)	{\
		if ( NULL == pPointer )\
		{\
			hResult =	NTE_NO_MEMORY;\
			::SetLastError ( (DWORD)hResult );\
			break;\
		}\
	}


#define		VSCSP_ALLOC_AND_STRING_COPY(szDestString, szSourceString)	{\
		szDestString =	(CHAR*) new CHAR [(lstrlen ( szSourceString ) + 1) * sizeof (CHAR)];\
		if ( NULL == szDestString )\
		{ \
			hResult =	E_VS_OUT_OF_MEMORY;\
			break;\
		}\
		lstrcpy(szDestString, szSourceString);\
	}

#define		VSCSP_CHECK_FOR_NULL_AND_DELETE(pBuffer)	{\
		if ( NULL != pBuffer )\
		{\
			delete []	pBuffer;\
			pBuffer =	NULL;\
		}\
	}

#define		VSCSP_CHECK_FOR_NULL_ERASE_AND_DELETE(pBuffer, nBufferLen)	{\
		if ( NULL != pBuffer )\
		{\
			EraseMemory ( (unsigned int) nBufferLen, (unsigned char*) pBuffer );\
			delete []	pBuffer;\
			pBuffer =	NULL;\
			nBufferLen = 0;\
		}\
	}

#define		VSCSP_CHECK_SIZE_OF_RSA_KEY(nSizeOfKey)	{\
		if ( 512 != nSizeOfKey && 1024 != nSizeOfKey && 2048 != nSizeOfKey )\
		{\
			hResult =	NTE_BAD_FLAGS;\
			break;\
		}\
	}

#define		VS_TPM_CSP_INIT_UUID_WITH_ZEROS(uuidTarget)	{\
		UuidFromString ( (unsigned char*) VS_TPM_UUID_ZEROS, &uuidTarget );\
	}

#endif