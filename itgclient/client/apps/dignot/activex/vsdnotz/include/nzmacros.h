#ifndef __NZMACROS_
#define __NZMACROS_


#define CHECK_HRESULT_BREAK		if(hr != S_OK)\
	{\
		break;\
	}


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
		hr = E_NZEMPTYARGS;\
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


#define SYS_FREE_MEMORY(pPointer){\
	if(pPointer)\
	{\
		SysFreeString(pPointer);\
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
		hr = E_NZINVALIDNODE;\
		break;\
	}\
	if(pNode->currentBaseDER == NULL)\
	{\
		hr = E_NZINVALIDNODE;\
		break;\
	}\
	if(pNode->currentBaseDER->Type != NodeType)\
	{\
		hr = E_NZINVALIDNODE;\
		break;\
	}\
}

#define CHECK_TREE_NODE_NO_HRESULT(pNode, NodeType){\
	if(pNode == NULL)\
		break;\
    if(pNode->currentBaseDER == NULL)\
		break;\
    if(pNode->currentBaseDER->Type != NodeType)\
		break;\
}

/*#define CHECK_TREE_NODE(pTree, Type){\
	if(!pTree)\
	{\
		hr = E_INVALIDNODE;\
		break;\
	}\
	if(pTree->currentBaseDER == NULL)\
	{\
		hr = E_INVALIDNODE;\
		break;\
	}\
	if(pTree->currentBaseDER->Type != Type)\
	{\
		hr = E_INVALIDNODE;\
		break;\
	}\
}*/
#endif	// __NZMACROS