#ifndef		__VSSC_GMM_MACROS_H__
#define		__VSSC_GMM_MACROS_H__

#define		VSGMM_CHECK_HRESULT	{\
		if ( S_OK != hResult )\
		{\
			break;\
		}\
	}

#define		VSGMM_CHECK_INPUT_STRING(i_szInputString)	{\
		if ( NULL == i_szInputString )\
		{\
			hResult =	E_INVALIDARG;\
			break;\
		}\
	}

#define		VSGMM_CHECK_INPUT_STRING_LEN(i_szInputString)	{\
		if ( 0 == _VS_strlenW ( i_szInputString ) )\
		{\
			hResult =	E_INVALIDARG;\
			break;\
		}\
	}

#define		VSGMM_CHECK_INPUT_POINTER_FOR_NULL(i_pPointer)	{\
		if ( NULL == i_pPointer )\
		{\
			hResult =	E_INVALIDARG;\
			break;\
		}\
	}

#define		VSGMM_CHECK_LENGTH_FOR_ZERO(i_nLength)	{\
		if ( 0 >= i_nLength )\
		{\
			hResult =	E_INVALIDARG;\
			break;\
		}\
	}

#define		VSGMM_CHECK_ALLOCATED_MEMORY(pPointer)	{\
		if ( NULL == pPointer )\
		{\
			hResult =	E_OUTOFMEMORY;\
			break;\
		}\
	}

#define		VSGMM_ALLOC_AND_BYTEBLOB_COPY(pbyteDest, pbyteSource, dwLength)	{\
		pbyteDest = new BYTE [dwLength];\
		if ( NULL == pbyteDest )\
		{\
			hResult =	E_OUTOFMEMORY;\
			break;\
		}\
		::memcpy( pbyteDest, pbyteSource, dwLength);\
	}

#define		VSGMM_CHECK_OBJECT_TIMEOUT	{\
		time ( &longCurrentTime );\
		if ( (longCurrentTime - m_lLastObjectAccessTime) > (long) m_dwObjectTimeoutInSec )\
		{\
			DeleteObjectNode ( i_cpbyteObjectID, i_cdwObjectIDLen );\
			hResult =	E_GLOBAL_MEMORY_TIME_OUT;\
			break;\
		}\
		else\
		{\
			m_lLastObjectAccessTime =	longCurrentTime;\
		}\
	}


#define		VSGMM_CHECK_ELEMENT_TIMEOUT	{\
		time ( &longCurrentTime );\
		if ( (longCurrentTime - m_lElementTime) > (long) m_dwElementTimeoutInSec )\
		{\
			m_VS_DeleteElementList ( m_pHeadElement );\
			hResult =	E_ELEMENT_TIME_OUT;\
			break;\
		}\
	}		

#endif