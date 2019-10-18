#ifndef __VSSCMACROS_
#define __VSSCMACROS_


#define CHECK_HRESULT_BREAK		if(hr != S_OK)\
	{\
		break;\
	}

#define CHECK_WININET_BOOL_BREAK if(!bRet)\
	{\
		hr=HRESULT_FROM_WIN32(GetLastError());\
		break;\
	}\

#define CHECK_MEM_BREAK(pPointer){\
	if(!pPointer)\
	{\
		hr = E_OUTOFMEMORY;\
		break;\
	}\
}


#define CHECK_NULL_PTR_BREAK(pPointer){\
	if(!pPointer)\
	{\
		hr = E_VSSCEMPTYARGS;\
		break;\
	}\
}\


#define FREE_MEMORY(pPointer){\
	if(pPointer)\
	{\
		free(pPointer);\
		pPointer = NULL;\
	}\
}


#define DELETE_MEMORY(pPointer){\
	if(pPointer)\
	{\
		delete (pPointer);\
		pPointer = NULL;\
	}\
}


#define RELEASE_INTERFACE_PTR(pPointer){\
	if(pPointer)\
	{\
		pPointer->Release();\
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

#define CHECK_TREE_NODE(pNode, NodeType){\
	if(pNode == NULL)\
	{\
		hr = E_VSSC_INVALIDNODE;\
		break;\
	}\
	if(pNode->currentBaseDER == NULL)\
	{\
		hr = E_VSSC_INVALIDNODE;\
		break;\
	}\
	if(pNode->currentBaseDER->Type != NodeType)\
	{\
		hr = E_VSSC_INVALIDNODE;\
		break;\
	}\
}

#define CHECK_BSTR_BREAK(i_pVal){\
	if(i_pVal->vt!=VT_BSTR)\
	{\
		hr=E_VSSC_INVALIDARGS;\
		break;\
	}\
}

#define CHECK_LONG_BREAK(i_pVal){\
	if(i_pVal->vt!=VT_I4)\
	{\
		hr=E_VSSC_INVALIDARGS;\
		break;\
	}\
}


#endif	// __VSSCMACROS