// BaseDERHierarchy.cpp: implementation of the CBaseDERHierarchy class.
//
//////////////////////////////////////////////////////////////////////

#include "BaseDERHierarchy.h"
#include "DataTypes.h"
#include <stdlib.h>
#include <memory.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

_BOOL	CBaseDERHierarchy::GetLengthInfo(CDERBlob *i_DERBlob, _DWORD *insideDERBlobLength, _DWORD *ContentLengthBytes)
{
	if (i_DERBlob->pbData[1] & 0x80)
	{
		if ( (i_DERBlob->pbData[1] & 0x7F) == 0 )
		{
			// You come here if it's Indefinite Length encoding.
			// You can't determine where the 0x00 0x00 termination sequence is.
			// Therefore, we will just assume that it is there somewhere and accordingly
			// reduce the number of length by 2.

			*insideDERBlobLength = i_DERBlob->cbData - 2 ;	// 2 corresponds to the Identifier octect and 0x80  
															// that represents indefinite length encoding.
			*ContentLengthBytes = 1 ;
			return _TRUE ;
		}
		else
		// There are multiple octets specifying the "Content length"
		if ( (i_DERBlob->pbData[1] & 0x7F) == 1 )
		{
			*insideDERBlobLength = (_DWORD)i_DERBlob->pbData[2] ;
			*ContentLengthBytes = 2 ;
		}
		else if ( (i_DERBlob->pbData[1] & 0x7F) == 2 )
		{
			*insideDERBlobLength = (_DWORD)(i_DERBlob->pbData[2] << 8) |
								(_DWORD)(i_DERBlob->pbData[3]) ;
			*ContentLengthBytes = 3 ;
		}
		else if ( (i_DERBlob->pbData[1] & 0x7F) == 3 )
		{
			*insideDERBlobLength = (_DWORD)(i_DERBlob->pbData[2] << 16) |
								(_DWORD)(i_DERBlob->pbData[3] << 8) |
								(_DWORD)(i_DERBlob->pbData[4]) ;
			*ContentLengthBytes = 4 ;
		}
		else if ( (i_DERBlob->pbData[1] & 0x7F) == 4 )
		{
			*insideDERBlobLength = (_DWORD)(i_DERBlob->pbData[2] << 24) |
								(_DWORD)(i_DERBlob->pbData[3] << 16) |
								(_DWORD)(i_DERBlob->pbData[4] << 8) |
								(_DWORD)(i_DERBlob->pbData[5]) ;
			*ContentLengthBytes = 5 ;
		}
		else
		{
			// This means there are more than 4 octets specifying
			// the "Content Length". Presently, I don't handle this
			// case.

			return _FALSE ;
		}

		// Check if the total length of the der blob is just
		// two octets more than the length mentioned in the
		// "Content length" octets
		if ( (*insideDERBlobLength + 2) != i_DERBlob->cbData )
		{
			return _FALSE ;
		}
	}
	else
	{
		// Check if the total length of the der blob is just
		// two octets more than the length mentioned in the
		// "Content length" octet
		if ( ((_DWORD)(i_DERBlob->pbData[1]) + 2) != i_DERBlob->cbData )
		{
			*insideDERBlobLength = i_DERBlob->pbData[1] ;
			*ContentLengthBytes = 1 ;
			return _FALSE ;
		}

		// Only one octet specifying the "Content length"
		*insideDERBlobLength = i_DERBlob->pbData[1] ;
		*ContentLengthBytes = 1 ;
	}

	return _TRUE ;
}

CDERBlob	*CBaseDERHierarchy::getInside(CDERBlob *i_DERBlob)
{
	if ( i_DERBlob->pbData[0] >= 0x30 && (i_DERBlob->pbData[0] != 0x80) )
	{
		_DWORD	insideDERBlobLength = 0, ContentLengthBytes = 0 ;

		GetLengthInfo(i_DERBlob, &insideDERBlobLength, &ContentLengthBytes) ;

		if ( (insideDERBlobLength+1+ContentLengthBytes) > i_DERBlob->cbData )
		{
			dwErrorCode = 0xFFFFFFFF ;
			return _NULL ;
		}

		if ( insideDERBlobLength )
		{
			CDERBlob	*retcderblob = new CDERBlob(
												insideDERBlobLength,
												i_DERBlob->pbData + 1 + ContentLengthBytes) ;
			return retcderblob ;
		}
		else
			return _NULL ;
	}
	else if ( (i_DERBlob->pbData[0] < 0x30) && (i_DERBlob->pbData[0] & 0x1F) && (i_DERBlob->pbData[1] == 0x80) )
	{
		// Handle the case where INDEFINITE encoding has been used to encode a CONSTRUCTED base primitive.

		_DWORD	insideDERBlobLength = 0, ContentLengthBytes = 0 ;

		GetLengthInfo(i_DERBlob, &insideDERBlobLength, &ContentLengthBytes) ;

		if ( (insideDERBlobLength+1+ContentLengthBytes) > i_DERBlob->cbData )
		{
			dwErrorCode = 0xFFFFFFFF ;
			return _NULL ;
		}

		if ( insideDERBlobLength )
		{
			CDERBlob	*retcderblob = new CDERBlob(
												insideDERBlobLength-2, // To remove 0x00 0x00 at the end
												i_DERBlob->pbData + 1 + ContentLengthBytes) ;
			return retcderblob ;
		}
		else
			return _NULL ;
	}
	else
		return _NULL ;
}

CDERBlob	*CBaseDERHierarchy::getNext(CDERBlob *i_DERBlob)
{
	_DWORD	insideDERBlobLength = 0, ContentLengthBytes = 0 ;

	/// Obtain length info on the 1st input DER blob
	GetLengthInfo(i_DERBlob, &insideDERBlobLength, &ContentLengthBytes) ;

	// Check if there is only one blob inside the input DER Blob
	if ( (insideDERBlobLength + ContentLengthBytes + 1) == i_DERBlob->cbData )
	{
		// Only one DER blob
		return _NULL ;
	}

	// Return the 2nd DER Blob.
	CDERBlob	*cderblob = new CDERBlob((i_DERBlob->cbData - (insideDERBlobLength + ContentLengthBytes + 1)),
										 i_DERBlob->pbData + (insideDERBlobLength + ContentLengthBytes + 1)) ;
	return cderblob ;
}

void	CBaseDERHierarchy::fillit(DERTree *i_DERTree, CDERBlob *i_DERBlob)
{
	CDERBlob	*insideDERBlob = _NULL, *nextDERBlob = _NULL ;
	_DWORD		dwInsideDERBlobLength = 0, dwContentLengthBytes = 0 ;

	insideDERBlob = getInside(i_DERBlob) ;

	if ( insideDERBlob != _NULL)
	{
		// You come here if the first DER blob is a non-primitive DER Blob (like SEQ, SET etc.)
		//                                          OR
		// if the first DER blob is a constructed primitive DER Blob (like 0x24 <==> Contructed Octet String)

		i_DERTree->currentBaseDER = new CBaseDER(*i_DERBlob) ;
		i_DERTree->currentBaseDER->decode() ;
		{
			_DWORD		insideDERBlobLength, ContentLengthBytes ;
			insideDERBlobLength = 0 ;
			ContentLengthBytes = 0 ;
			GetLengthInfo(i_DERBlob, &insideDERBlobLength, &ContentLengthBytes) ;
			_RemainingLength -= 1+ContentLengthBytes ;
		}

		CDERBlob	*cdbOriginalDERBlob = new CDERBlob(*i_DERBlob) ;

		i_DERTree->rightDERTree = (DERTree *) malloc (sizeof(DERTree)) ;
		i_DERTree->rightDERTree->currentBaseDER = _NULL ;
		i_DERTree->rightDERTree->nextDERTree = _NULL ;
		i_DERTree->rightDERTree->rightDERTree = _NULL ;
		i_DERTree->nextDERTree = _NULL ;

		fillit(i_DERTree->rightDERTree, insideDERBlob) ;

		// Determine the correct length of the DER blob that is inside i_DERBlob.
		if ( i_DERTree->currentBaseDER->BaseDERBlob->pbData[1] == 0x80 )
		{
			// We assume that the number of bytes used to encoded the tag/identifier information is always 1.

			// Calculate number of bytes inside this indefinite encoded blob

			_DWORD dwInsideIDELength = 0 ;
			DERTree	*tmpDERTree = i_DERTree->rightDERTree ;
			while(tmpDERTree)
			{
				dwInsideIDELength += tmpDERTree->currentBaseDER->BaseDERBlob->cbData ;
				tmpDERTree = tmpDERTree->nextDERTree ;
			}

			i_DERTree->currentBaseDER->cbData = dwInsideIDELength ;
			if ( i_DERTree->currentBaseDER->pbData )
				free(i_DERTree->currentBaseDER->pbData) ;
			i_DERTree->currentBaseDER->pbData = (_PBYTE) malloc(dwInsideIDELength) ;
			memcpy(i_DERTree->currentBaseDER->pbData, cdbOriginalDERBlob->pbData+2, dwInsideIDELength) ;

			i_DERTree->currentBaseDER->BaseDERBlob->cbData = 2+dwInsideIDELength + 2 ; // for 0x00 0x00
			if (i_DERTree->currentBaseDER->BaseDERBlob->pbData)
				free(i_DERTree->currentBaseDER->BaseDERBlob->pbData) ;
			i_DERTree->currentBaseDER->BaseDERBlob->pbData = (_PBYTE) malloc(i_DERTree->currentBaseDER->BaseDERBlob->cbData) ;
			memcpy(i_DERTree->currentBaseDER->BaseDERBlob->pbData, cdbOriginalDERBlob->pbData, i_DERTree->currentBaseDER->BaseDERBlob->cbData) ;

			dwInsideDERBlobLength = dwInsideIDELength + 2 ; // 2 is for the 0x00 0x00 sequence at the end.
			dwContentLengthBytes = 0x01 ;	// Because it takes only one byte to store the 0x80 byte that is present 
											// in the Content length field that indicates Indefinite Length encoding.

			_RemainingLength -= 2 ; // For the 0x00 0x00 sequence used to terminate indefinite length encoded blobs.
		}
		else
		{
			// If i_DERBlob->currentBaseDER is NOT indefinite length encoded, then come here.

			GetLengthInfo(cdbOriginalDERBlob, &dwInsideDERBlobLength, &dwContentLengthBytes) ;

			// Calculate number of bytes inside this blob

			_DWORD dwInsideIDELength = 0 ;
			DERTree	*tmpDERTree = i_DERTree->rightDERTree ;
			while(tmpDERTree)
			{
				dwInsideIDELength += tmpDERTree->currentBaseDER->BaseDERBlob->cbData ;
				tmpDERTree = tmpDERTree->nextDERTree ;
			}

			if ( i_DERTree->currentBaseDER->cbData != dwInsideIDELength )
			{
				i_DERTree->currentBaseDER->cbData = dwInsideIDELength ;
				if ( i_DERTree->currentBaseDER->pbData )
					free(i_DERTree->currentBaseDER->pbData) ;
				i_DERTree->currentBaseDER->pbData = (_PBYTE) malloc(dwInsideIDELength) ;
				memcpy(i_DERTree->currentBaseDER->pbData, cdbOriginalDERBlob->pbData+1+dwContentLengthBytes, dwInsideIDELength) ;
			}

			if ( i_DERTree->currentBaseDER->BaseDERBlob->cbData != (1 + dwContentLengthBytes + dwInsideIDELength) )
			{
				i_DERTree->currentBaseDER->BaseDERBlob->cbData = 1 + dwContentLengthBytes + dwInsideIDELength ; 
				if (i_DERTree->currentBaseDER->BaseDERBlob->pbData)
					free(i_DERTree->currentBaseDER->BaseDERBlob->pbData) ;
				i_DERTree->currentBaseDER->BaseDERBlob->pbData = (_PBYTE) malloc(i_DERTree->currentBaseDER->BaseDERBlob->cbData) ;
				memcpy(i_DERTree->currentBaseDER->BaseDERBlob->pbData, cdbOriginalDERBlob->pbData, i_DERTree->currentBaseDER->BaseDERBlob->cbData) ;
			}

			dwInsideDERBlobLength = dwInsideIDELength ;
		}

		// Determine if there is a DER Blob after the one pointed by i_DERBlob.

		if ( (1+dwContentLengthBytes+dwInsideDERBlobLength) < cdbOriginalDERBlob->cbData )
		{
			// You come here if there is a DER Blob after the one pointed by i_DERBlob.
			// So determine if that is just a NULL

			if ( ((cdbOriginalDERBlob->pbData)+(1+dwContentLengthBytes+dwInsideDERBlobLength))[0] == 0x00 && 
				 ((cdbOriginalDERBlob->pbData)+(1+dwContentLengthBytes+dwInsideDERBlobLength))[1] == 0x00 )
			{
				i_DERTree->nextDERTree = (DERTree *) _NULL ;
			}
			else
			{
				CDERBlob *newDERBlob = new CDERBlob(cdbOriginalDERBlob->cbData - (1+dwContentLengthBytes+dwInsideDERBlobLength), cdbOriginalDERBlob->pbData+(1+dwContentLengthBytes+dwInsideDERBlobLength)) ;
				i_DERTree->nextDERTree = (DERTree *) malloc(sizeof(DERTree)) ;
				i_DERTree->nextDERTree->currentBaseDER = _NULL ;
				i_DERTree->nextDERTree->nextDERTree = _NULL ;
				i_DERTree->nextDERTree->rightDERTree = _NULL ;
				fillit(i_DERTree->nextDERTree, newDERBlob) ;

				delete newDERBlob ;
			}
		}
		else
			i_DERTree->nextDERTree = (DERTree *) _NULL ;

		delete cdbOriginalDERBlob ;
	}
	else
	{
		if ( dwErrorCode == 0xFFFFFFFF )
		{
			i_DERTree->nextDERTree = _NULL;
            i_DERTree->currentBaseDER = _NULL;
            i_DERTree->rightDERTree = _NULL;

			return ;
		}

		GetLengthInfo(i_DERBlob, &dwInsideDERBlobLength, &dwContentLengthBytes) ;

		if ( (1+dwContentLengthBytes+dwInsideDERBlobLength) < i_DERBlob->cbData )
		{
			// You come here if i_DERBlob has at least one primitive or non-primitive DER
			// blob following the one pointed to by i_DERBlob.
			CDERBlob	retDERBlob(1+dwContentLengthBytes+dwInsideDERBlobLength, (_PBYTE)i_DERBlob->pbData) ;

			i_DERTree->currentBaseDER = new CBaseDER(retDERBlob) ;
			i_DERTree->currentBaseDER->decode() ;
			
			_RemainingLength -= 1+dwContentLengthBytes+dwInsideDERBlobLength ;
			
			i_DERTree->rightDERTree = _NULL ;
			i_DERTree->nextDERTree = _NULL ;

			// Check for terminator of Indefinite length encoded blob !!
			// Basically check for 0x00 0x00 sequence after the current blob pointed by i_DERBlob->pbData
			if ( i_DERBlob->pbData[(1+dwContentLengthBytes+dwInsideDERBlobLength)] == 0x00 &&
				 i_DERBlob->pbData[(1+dwContentLengthBytes+dwInsideDERBlobLength) + 1] == 0x00 )
			{

			}
			else
			{
				i_DERTree->nextDERTree = (DERTree *) malloc (sizeof(DERTree)) ;
				i_DERTree->nextDERTree->currentBaseDER = _NULL ;
				i_DERTree->nextDERTree->nextDERTree = _NULL ;
				i_DERTree->nextDERTree->rightDERTree = _NULL ;

				nextDERBlob = new CDERBlob ( (i_DERBlob->cbData) - (1+dwContentLengthBytes+dwInsideDERBlobLength),
									i_DERBlob->pbData + (1+dwContentLengthBytes+dwInsideDERBlobLength) ) ;

				fillit(i_DERTree->nextDERTree, nextDERBlob) ;
			}
		}
		else
		{
			CDERBlob	retDERBlob(1+dwContentLengthBytes+dwInsideDERBlobLength, (_PBYTE)i_DERBlob->pbData) ;

			if (retDERBlob.pbData[0] == 0x00 && retDERBlob.pbData[1] == 0x00 )
			{
				i_DERTree->currentBaseDER = _NULL ;
			}
			else
			{
				i_DERTree->currentBaseDER = new CBaseDER(retDERBlob) ;
				i_DERTree->currentBaseDER->decode() ;

				if ( (1+dwContentLengthBytes+dwInsideDERBlobLength) != i_DERBlob->cbData )
				{
					// You reach here when the last dwInsideDERBlobLength is more than what it should be.
					// So Altough you may even manage to decode the DER Blob, as dwInsideDERBlobLength is wrong,
					// the decoded stuff is wrong. 
					// Convey this fact by setting the error code.
					i_DERTree->currentBaseDER->dwErrorCode = 0xFFFFFFFF ;
				}
				_RemainingLength -= 1+dwContentLengthBytes+dwInsideDERBlobLength ;
			}
			
			i_DERTree->rightDERTree = _NULL ;
			i_DERTree->nextDERTree = _NULL ;
		}
	}

	if (insideDERBlob)
		delete insideDERBlob ;
	if (nextDERBlob)
		delete nextDERBlob ;
}

CBaseDERHierarchy::CBaseDERHierarchy(CBaseDERCollection &cbasedercollection)
{
	m_DERTree.currentBaseDER = _NULL ;
	m_DERTree.nextDERTree = _NULL ;
	m_DERTree.rightDERTree = _NULL ;
	dwErrorCode = 0x00000000 ;

	if ( cbasedercollection.BaseDERBlob )
	{
		CDERBlob	input_BaseDERBlob(cbasedercollection.BaseDERBlob->cbData, cbasedercollection.BaseDERBlob->pbData) ;

		_RemainingLength = cbasedercollection.BaseDERBlob->cbData ;

		fillit(&m_DERTree, &input_BaseDERBlob) ;

		if ( _RemainingLength != 0 )
		{
			dwErrorCode = 0xFFFFFFFF ;
		}
	}
}

CBaseDERHierarchy::~CBaseDERHierarchy()
{
	freeit(&m_DERTree) ;
}

void CBaseDERHierarchy::freeit(DERTree	*i_DERTree)
{
	if ( i_DERTree->rightDERTree )
	{
		freeit(i_DERTree->rightDERTree) ;
		free(i_DERTree->rightDERTree) ;
	}

	if ( i_DERTree->nextDERTree )
	{
		freeit(i_DERTree->nextDERTree) ;
		free(i_DERTree->nextDERTree) ;
	}

	delete i_DERTree->currentBaseDER ;
}


	