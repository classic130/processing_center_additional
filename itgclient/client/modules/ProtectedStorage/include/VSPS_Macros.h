///////////////////////////////////////////////////////////////////////////////
//																			 //
//	File Name		:	VSPS_Macros.h										 //
//																			 //
//	Description		:	The file contains the macros used in the project.	 //
//																			 //
//	Date			:	Sept 13, 1999										 //
//																			 //
//	Author			:	Anand Abhyankar										 //
//																			 //
///////////////////////////////////////////////////////////////////////////////
#ifndef		__PROTECTED_STORAGE_MACROS_H__
#define		__PROTECTED_STORAGE_MACROS_H__

//#include "ptaimpl.h"

#define		VS_CHECK_INPUT_STRING(i_szInputString)	{\
		if ( NULL == i_szInputString )\
		{\
			hResult =	E_VS_INVALIDARG;\
			break;\
		}\
	}

#define		VS_CHECK_INPUT_STRING_LEN(i_szInputString)	{\
		if ( 0 == _VS_strlenW ( i_szInputString ) )\
		{\
			hResult =	E_VS_INVALIDARG;\
			break;\
		}\
	}

#define		VS_CHECK_INPUT_POINTER_FOR_NULL(i_pPointer)	{\
		if ( NULL == i_pPointer )\
		{\
			hResult =	E_VS_INVALIDARG;\
			break;\
		}\
	}

#define		VS_CHECK_LENGTH_FOR_ZERO(i_nLength)	{\
		if ( 0 >= i_nLength )\
		{\
			hResult =	E_VS_INVALIDARG;\
			break;\
		}\
	}

#define		VS_ALLOC_AND_STRING_COPY(szDestString, szSourceString)	{\
		szDestString =	(_VS_CHAR*) m_VS_HeapAlloc ( (_VS_strlenW ( szSourceString ) + 1) * sizeof (_VS_CHAR) );\
		if ( NULL == szDestString )\
		{ \
			hResult =	E_VS_OUT_OF_MEMORY;\
			break;\
		}\
		m_VS_strcpyW(szDestString, szSourceString);\
	}

#define		VS_ALLOC_AND_BYTEBLOB_COPY(pbyteDest, pbyteSource, dwLength)	{\
		pbyteDest = (_BYTE*) m_VS_HeapAlloc ( dwLength * sizeof (_BYTE) );\
		if ( NULL == pbyteDest )\
		{\
			hResult =	E_VS_OUT_OF_MEMORY;\
			break;\
		}\
		_VS_memcpy ( pbyteDest, pbyteSource, dwLength * sizeof (_BYTE) );\
	}

/*
#define		VS_ALLOC_AND_COPY_PRINTABLE_STRING(szDestString, szSourceString)	{\
		szDestString =	(_CHAR*) m_VS_HeapAlloc ( (strlen ( (_VS_CHAR*) szSourceString ) + 1) * sizeof (_CHAR) );\
		if ( NULL == szDestString )\
		{ \
			hResult =	E_VS_OUT_OF_MEMORY;\
			break;\
		}\
		::strcpy ( (_VS_CHAR*)szDestString, (_VS_CHAR*)szSourceString);\
	}
*/

#define		VS_CHECK_HRESULT	if ( VS_SUCCESS != hResult )\
	{\
		break;\
	}

#define		VS_CHECK_BRESULT	if ( TRUE != bResult )\
	{\
		hResult =	::GetLastError ();\
		break;\
	}

#define		VS_CHECK_NRESULT	if ( 0 != nResult )\
	{\
		hResult =	E_VS_FAIL;\
		break;\
	}

			//	The (pFreeBlock != NULL) check is done in the m_VS_HeapFree function
			//	so its not done in the macro
#define		VS_FREE_MEMORY(pFreeBlock)	{\
		m_VS_HeapFree ( (void*) pFreeBlock );\
		pFreeBlock = NULL;\
	}

#define		VS_FREE_MEMORY_2D(ppFreeBlock, nCount)	{\
		for ( int z = 0; z < (int) nCount; z ++ )\
		{\
			m_VS_HeapFree ( (void*) ppFreeBlock [z] );\
			ppFreeBlock[z] = NULL;\
		}\
		m_VS_HeapFree ( (void*) ppFreeBlock );\
		ppFreeBlock = NULL;\
	}

#define		VS_CHECK_TYPE(byteType, pstructDERTreeCurrent)	{\
		if ( NULL != pstructDERTreeCurrent )\
		{\
			if ( byteType != ( (pstructDERTreeCurrent -> currentBaseDER) -> Type ) )\
			{\
				hResult =	E_VS_STORAGE_CORRUPT;\
				break;\
			}\
		}\
	}

/*
#define		VS_CREATE_STRING_FROM_STRUCT(szString, pStruct, dwStringLength)	{\
		szString =	(_CHAR*) m_VS_HeapAlloc ( ( (pStruct -> currentBaseDER) -> cbData ) + sizeof (_CHAR) );\
		if ( NULL == szString )\
		{\
			hResult =	E_VS_OUT_OF_MEMORY;\
			break;\
		}\
		_VS_memcpy ( (void*) szString, (const void*) (pStruct -> currentBaseDER) -> pbData, (pStruct -> currentBaseDER) -> cbData );\
		szString [(pStruct -> currentBaseDER) -> cbData] = '\0';\
		dwStringLength =	(pStruct -> currentBaseDER) -> cbData;\
	}
*/

#define		VS_CREATE_INTEGER_FROM_STRUCT(pnInt, pStruct)	{\
		*pnInt = 0;\
		_VS_memcpy ( (void*) pnInt, (void*) (pStruct -> currentBaseDER) -> pbData, (pStruct -> currentBaseDER) -> cbData );\
	}

/*
#define		VS_CREATE_BYTEBLOB_FROM_STRUCT(pbyteBlob, pStruct, dwBlobLength)	{\
		pbyteBlob =	(_BYTE*) m_VS_HeapAlloc ( (pStruct -> currentBaseDER) -> cbData );\
		if ( NULL == pbyteBlob )\
		{\
			hResult =	E_VS_OUT_OF_MEMORY;\
			break;\
		}\
		_VS_memcpy ( (void*) pbyteBlob, (const void*) (pStruct -> currentBaseDER) -> pbData, (pStruct -> currentBaseDER) -> cbData );\
		dwBlobLength =	(pStruct -> currentBaseDER) -> cbData;\
	}
*/


#define		VS_CREATE_BYTEBLOB_FROM_STRUCT(pbyteBlob, pStruct, dwBlobLength)	{\
		pbyteBlob =	(_BYTE*) m_VS_HeapAlloc ( (pStruct -> currentBaseDER) -> cbData );\
		if ( NULL == pbyteBlob )\
		{\
			hResult =	E_VS_OUT_OF_MEMORY;\
			break;\
		}\
		dwBlobLength =	(pStruct -> currentBaseDER) -> cbData;\
			/*	make sure that if m_dwPSSecondVersionNumber is 0 then reverse and copy */ \
			/*	if its 1 (or more) then just copy */ \
		if ( VSPS_VERSION_SECOND_NUMBER_1 < m_dwPSSecondVersionNumber )\
		{\
			_VS_memcpy ( (void*) pbyteBlob, (const void*) (pStruct -> currentBaseDER) -> pbData, (pStruct -> currentBaseDER) -> cbData );\
		}\
		else\
		{\
			for ( m_dwReverseOS = 0; m_dwReverseOS < dwBlobLength; m_dwReverseOS ++ )\
			{\
				pbyteBlob [m_dwReverseOS] = (((pStruct -> currentBaseDER) -> pbData) [(dwBlobLength - m_dwReverseOS) - 1]);\
			}\
		}\
	}


#define		VS_PROTECTED_CREATE_BYTEBLOB_FROM_STRUCT(pbyteBlob, pStruct, dwBlobLength)	{\
		pbyteBlob =	(_BYTE*) m_VS_HeapAlloc ( (pStruct -> currentBaseDER) -> cbData );\
		if ( NULL == pbyteBlob )\
		{\
			hResult =	E_VS_OUT_OF_MEMORY;\
			break;\
		}\
		dwBlobLength =	(pStruct -> currentBaseDER) -> cbData;\
			/*	make sure that if m_dwPSFirstVersionNumber is 1 or 2 then reverse and copy */ \
			/*	if its 3 (or more) then just copy */ \
		if ( VSPS_VERSION_FIRST_NUMBER_2 < m_dwPSFirstVersionNumber )\
		{\
			_VS_memcpy ( (void*) pbyteBlob, (const void*) (pStruct -> currentBaseDER) -> pbData, (pStruct -> currentBaseDER) -> cbData );\
		}\
		else\
		{\
			for ( m_dwReverseOS = 0; m_dwReverseOS < dwBlobLength; m_dwReverseOS ++ )\
			{\
				pbyteBlob [m_dwReverseOS] = (((pStruct -> currentBaseDER) -> pbData) [(dwBlobLength - m_dwReverseOS) - 1]);\
			}\
		}\
	}


/*
#define		VS_CHECK_INPUT_POINTER(pPointer)	{\
		if ( NULL == pPointer )\
		{\
			hResult =	E_VS_INVALIDARG;\
			break;\
		}\
	}
*/

#define		VS_CHECK_ALLOCATED_MEMORY(pPointer)	{\
		if ( NULL == pPointer )\
		{\
			hResult =	E_VS_OUT_OF_MEMORY;\
			break;\
		}\
	}

#define		VS_CHECK_IF_INITIALIZED {\
		if ( 1 != m_dwInitializeSuccessful )\
		{\
			hResult =	E_VS_NOT_INITIALIZED;\
			break;\
		}\
	}

#define		VS_CHECK_AND_UPDATE_PASSWORD_TIMEOUT {\
		if ( 1 != m_nPasswordProvided )\
		{\
			hResult =	E_VS_PASSWORD_NOT_PROVIDED;\
			break;\
		}\
		hResult =	m_CheckPasswordTimeOut ();\
		if ( VS_SUCCESS != hResult )\
		{\
			break;\
		}\
	}

#define		VS_UPDATE_PASSWORD_TIMEOUT {\
	}

/*		m_UpdatePasswordTimeOut ();\*/

#define		VS_GET_WAIT_FOR_SINGLE_OBJECT_TIMEOUT {\
		if ( NO_BLOCK_RETURN_ERROR == i_cnMode )\
		{\
			m_dwWaitForSingleObjectTimeOut = 0;\
		}\
		else\
		{\
			if ( BLOCK_WITHOUT_TIME_OUT == i_cnMode )\
			{\
				m_dwWaitForSingleObjectTimeOut = INFINITE;\
			}\
			else\
			{\
				if ( BLOCK_FOR_X_SECONDS == i_cnMode )\
				{\
					m_dwWaitForSingleObjectTimeOut = i_cnWaitTime;\
				}\
				else\
				{\
					hResult =	E_VS_INVALIDARG;\
					break;\
				}\
			}\
		}\
	}

#define		VS_CHECK_RETURN_WAIT_FOR_SINGLE_OBJECT {\
		if ( (WAIT_OBJECT_0 != hResult) && (WAIT_ABANDONED != hResult) )\
		{\
			if ( WAIT_FAILED == hResult )\
			{\
				hResult =	::GetLastError ();\
				break;\
			}\
			if ( WAIT_TIMEOUT == hResult )\
			{\
				break;\
			}\
		}\
	}

#define		VS_CHECK_IF_BEGIN_READ_OR_WRITE_CALLED	{\
		if ( (BEGIN_READ_CALLED != m_dwBeginReadCalled) && (BEGIN_WRITE_CALLED != m_dwBeginWriteCalled) )\
		{\
			hResult =	E_VS_BEGIN_NOT_CALLED;\
			break;\
		}\
	}

#define		VS_CHECK_IF_BEGIN_WRITE_CALLED	{\
		if ( BEGIN_WRITE_CALLED != m_dwBeginWriteCalled )\
		{\
			hResult =	E_VS_BEGIN_NOT_CALLED;\
			break;\
		}\
	}

#endif