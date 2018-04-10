#ifndef __VS_MACROS_
#define __VS_MACROS_


#define CHECK_HRESULT_BREAK		if(hr != S_OK)\
	{\
		break;\
	}

#define FREE_MEMORY(pPointer){\
	if(pPointer)\
	{\
		free(pPointer);\
		pPointer = NULL;\
	}\
}


#define SYS_FREE_MEMORY(pPointer){\
	if(pPointer)\
	{\
		SysFreeString(pPointer);\
		pPointer = NULL;\
	}\
}

#define CHECK_MEM_BREAK(pPointer){\
	if(!pPointer)\
	{\
		hr = E_VSSCODE_OUTOFMEMORY;\
		break;\
	}\
}

#define REG_CLOSE_KEY(hKey){\
	if(hKey)\
	{\
		RegCloseKey(hKey);\
		hKey = NULL;\
	}\
}

#define CHECK_NULL_PTR_BREAK(pPointer){\
	if(!pPointer)\
	{\
		hr = E_VSSCODE_EMPTYARGS;\
		break;\
	}\
}

#define RELEASE_INTERFACE_PTR(pPointer){\
	if(pPointer)\
	{\
		(pPointer)->Release();\
		pPointer = NULL;\
	}\
}

#define CLOSE_INET_HANDLE(hHandle){\
	if(hHandle)\
	{\
		InternetCloseHandle(hHandle);\
		hHandle = NULL;\
	}\
}

#define FREE_CERT_INFO(pCertInfo){\
	if(pCertInfo)\
	{\
		FREE_MEMORY(pCertInfo->pbIssuerDN)\
		FREE_MEMORY(pCertInfo->pbSerialNumber)\
		FREE_MEMORY(pCertInfo)\
	}\
}

#endif	// __VS_MACROS_