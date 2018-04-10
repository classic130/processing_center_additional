#include "..\include\gMemMgmt.h"
#include "..\include\VSGMM_Macros.h"
#include "..\include\VSGMM_Errors.h"


g_GlobalMemoryManagement::g_GlobalMemoryManagement ()
{
	m_hNamedMutex					=	NULL;

	m_dwPID							=	0;
	m_dwLoadedCount					=	0;

	m_dwObjectTimeoutInSec			=	VSSC_DEFAULT_OBJECT_TIMEOUT;
	time (&m_lLastObjectAccessTime);

	m_dwElementTimeoutInSec			=	VSSC_DEFAULT_ELEMENT_TIMEOUT;
	time (&m_lElementTime);

	m_dwNumberOfObjectNodes			=	0;
	m_pHeadObjectNode				=	NULL;

	m_dwNumberOfElements			=	0;
	m_pHeadElement					=	NULL;
}

g_GlobalMemoryManagement::~g_GlobalMemoryManagement ()
{
	if ( NULL != m_pHeadObjectNode )
	{
		DeleteObjectNode
		(
			m_pHeadObjectNode -> pbyteObjectID,
			m_pHeadObjectNode -> dwObjectIDLen
		);
	}

	if ( NULL != m_pHeadElement )
	{
		m_VS_DeleteElementList (m_pHeadElement);
	}
}

HRESULT		g_GlobalMemoryManagement::AddObjectNode
(
	const BYTE*						i_cpbyteObjectID,
	const DWORD						i_cdwObjectIDLen
//	const DWORD						i_cdwObjectTimeoutInMin
)
{
	HRESULT						hResult				=	E_FAIL;
	g_ObjectNode*				pstructObjectNode	=	NULL;

	long						longCurrentTime		=	0;

	do
	{
//		VSGMM_CHECK_OBJECT_TIMEOUT

			//	check input parameters
		VSGMM_CHECK_INPUT_POINTER_FOR_NULL (i_cpbyteObjectID)
		VSGMM_CHECK_LENGTH_FOR_ZERO (i_cdwObjectIDLen)

		if ( NULL != m_pHeadObjectNode )
		{
			hResult =	E_OBJECT_NODE_EXISTS;
			break;
		}

			//	allocate an object (message node)
		pstructObjectNode =	new	g_ObjectNode;
		VSGMM_CHECK_ALLOCATED_MEMORY (pstructObjectNode)

			//	copy the object ID into the node
		VSGMM_ALLOC_AND_BYTEBLOB_COPY ( (pstructObjectNode -> pbyteObjectID ), i_cpbyteObjectID, i_cdwObjectIDLen )
		pstructObjectNode -> dwObjectIDLen =	i_cdwObjectIDLen;

			//	copy timeout in sec and set the last access time to current time
//		pstructObjectNode -> dwAccessTimeOutInSec	=	i_cdwObjectTimeoutInMin * 60;
//		time ( &(pstructObjectNode -> lLastAccessTime) );

			//	init other members
		pstructObjectNode -> dwNumberOfMemoryBlobs	=	0;
		pstructObjectNode -> pHeadMemoryBlob		=	NULL;

			//	add this new node in the class. at the moment only one node
			//	is required. if in future a list of nodes is required then
			//	use the m_pHeadObjectNode to go to the end of the list and
			//	append the list
		m_pHeadObjectNode =	pstructObjectNode;

			//	increment the loaded count. this count if > 0 will prevent
			//	unloading of the dll
		m_dwLoadedCount ++;

		hResult =	S_OK;

	}	while (0);

	return		hResult;
}	//	end		HRESULT		g_GlobalMemoryManagement::AddObjectNode


HRESULT		g_GlobalMemoryManagement::DeleteObjectNode
(
	const BYTE*						i_cpbyteObjectID,
	const DWORD						i_cdwObjectIDLen
)
{
	HRESULT						hResult				=	E_FAIL;

	int							nCompare			=	999;

	g_MemoryNode*				pMemoryNode			=	NULL;
	g_MemoryNode*				pNextMemoryNode		=	NULL;

	do
	{
			//	check input parameters
		VSGMM_CHECK_INPUT_POINTER_FOR_NULL (i_cpbyteObjectID)
		VSGMM_CHECK_LENGTH_FOR_ZERO (i_cdwObjectIDLen)

				//	make sure that the object exists
		hResult =	m_CheckForObject
					(
						i_cpbyteObjectID,
						i_cdwObjectIDLen
					);
		VSGMM_CHECK_HRESULT

/*
				//	make sure that the object exists
		if ( i_cdwObjectIDLen != (m_pHeadObjectNode ->dwObjectIDLen) )
		{
			hResult	=	E_OBJECT_NODE_NOT_FOUND;
			break;
		}

		nCompare =	::memcmp
					(
						(const void*) i_cpbyteObjectID,
						(const void*) (m_pHeadObjectNode -> pbyteObjectID),
						i_cdwObjectIDLen
					);
		if ( 0 != nCompare )
		{
			hResult	=	E_OBJECT_NODE_NOT_FOUND;
			break;
		}
*/

				//	the Object Node contains a list of memory blobs
				//	delete all the memory blobs
		pMemoryNode =	(m_pHeadObjectNode -> pHeadMemoryBlob);

		while ( NULL != pMemoryNode )
		{
			pNextMemoryNode =	pMemoryNode -> pNext;

			hResult =	m_VS_DeleteMemoryNode ( pMemoryNode );

			pMemoryNode =	pNextMemoryNode;
		}

		delete [] (m_pHeadObjectNode -> pbyteObjectID);
		m_pHeadObjectNode -> dwObjectIDLen = 0;

		delete	m_pHeadObjectNode;

		m_pHeadObjectNode =	NULL;

			//	decrement the loaded count. this count if > 0 will prevent
			//	unloading of the dll
		m_dwLoadedCount --;

		hResult =	S_OK;
	}	while (0);

	return	hResult;
}	//	end		HRESULT		g_GlobalMemoryManagement::DeleteObjectNode

HRESULT	g_GlobalMemoryManagement::DeleteObjectNodeWithOutID()
{
	HRESULT						hResult				=	E_FAIL;

	if ( NULL != m_pHeadObjectNode )
	{
	  return hResult=DeleteObjectNode(
								m_pHeadObjectNode -> pbyteObjectID,
								m_pHeadObjectNode -> dwObjectIDLen
								);

		
	}

	hResult=S_OK;
	return hResult;

}


HRESULT		g_GlobalMemoryManagement::VS_AllocateMemory
(
	const BYTE*						i_cpbyteObjectID,
	const DWORD						i_cdwObjectIDLen,
	const DWORD						i_cdwMemoryBlobType,
	const DWORD						i_cdwMemoryBlobLen,
	void**							o_ppvoidMemory
)
{
	HRESULT						hResult				=	E_FAIL;

	int							nCompare			=	999;

	BOOL						boolDuplicateType	=	FALSE;

	g_MemoryNode*				pMemoryNode			=	NULL;
	g_MemoryNode*				pPreviousMemoryNode	=	NULL;
	g_MemoryNode*				pNewMemoryNode		=	NULL;

	long						longCurrentTime		=	0;
		
	do
	{
		VSGMM_CHECK_OBJECT_TIMEOUT

			//	check input parameters
		VSGMM_CHECK_INPUT_POINTER_FOR_NULL (i_cpbyteObjectID)
		VSGMM_CHECK_LENGTH_FOR_ZERO (i_cdwObjectIDLen)
		VSGMM_CHECK_LENGTH_FOR_ZERO (i_cdwMemoryBlobLen)
		VSGMM_CHECK_INPUT_POINTER_FOR_NULL (o_ppvoidMemory)

				//	make sure that the object exists
		hResult =	m_CheckForObject
					(
						i_cpbyteObjectID,
						i_cdwObjectIDLen
					);
		VSGMM_CHECK_HRESULT
			
/*			//	make sure that the object exists
		if ( i_cdwObjectIDLen != (m_pHeadObjectNode ->dwObjectIDLen) )
		{
			hResult	=	E_OBJECT_NODE_NOT_FOUND;
			break;
		}

		nCompare =	::memcmp
					(
						(const void*) i_cpbyteObjectID,
						(const void*) (m_pHeadObjectNode -> pbyteObjectID),
						i_cdwObjectIDLen
					);
		if ( 0 != nCompare )
		{
			hResult	=	E_OBJECT_NODE_NOT_FOUND;
			break;
		}
*/
		pMemoryNode =	(m_pHeadObjectNode -> pHeadMemoryBlob);

				//	traverse the memory blob list to the end.
		while ( NULL != pMemoryNode )
		{
					//	if a memory blob of the specified type already
					//	exists then flag it
			if ( i_cdwMemoryBlobType ==  (pMemoryNode -> dwMemoryBlobType) )
			{
				boolDuplicateType =	TRUE;
				break;
			}

			pPreviousMemoryNode =	pMemoryNode;
			pMemoryNode =	(pMemoryNode -> pNext);
		}

				//	if the type is duplicate then return error
		if ( TRUE == boolDuplicateType )
		{
			hResult =	E_MEMORY_BLOB_TYPE_EXISTS;
			break;
		}

				//	allocate new memory node
		pNewMemoryNode =	new g_MemoryNode;
		VSGMM_CHECK_ALLOCATED_MEMORY (pNewMemoryNode)

				//	set the length and type of the memory blob
		pNewMemoryNode -> dwMemoryBlobType	=	i_cdwMemoryBlobType;
		pNewMemoryNode -> dwMemoryBlobLen	=	i_cdwMemoryBlobLen;

				//	allocate memory. initialize the pointer to NULL before allocating
				//	so that it can be checked for OUTOFMEMORY error
		pNewMemoryNode -> pvoidMemoryBlob	=	NULL;
		pNewMemoryNode -> pvoidMemoryBlob	=	(void*) new BYTE [i_cdwMemoryBlobLen];
		VSGMM_CHECK_ALLOCATED_MEMORY ( (pNewMemoryNode -> pvoidMemoryBlob) )

				//	adjust the next and previous pointers. since this is the last
				//	node in the list the next is NULL
		pNewMemoryNode -> pNext				=	NULL;
		pNewMemoryNode -> pPrevious			=	pPreviousMemoryNode;

				//	also adjust the next pointer of the previous node. this was the last
				//	node in the list, which has now become the second last.
		if ( NULL != pPreviousMemoryNode )
		{
			pPreviousMemoryNode -> pNext =	pNewMemoryNode;
		}
		else
		{
				//	if pPreviousMemoryNode is NULL then it means that the newly
				//	added node is the first one. so make it the head
			(m_pHeadObjectNode -> pHeadMemoryBlob) =	pNewMemoryNode;
		}

				//	increment the number of blobs
		(m_pHeadObjectNode -> dwNumberOfMemoryBlobs) ++;

				//	set the out void** to the appropriate memory blob in the memory
				//	node
		*o_ppvoidMemory =	pNewMemoryNode -> pvoidMemoryBlob;

		hResult =	S_OK;
	}	while (0);

	return	hResult;
}	//	end		HRESULT		g_GlobalMemoryManagement::VS_AllocateMemory


HRESULT		g_GlobalMemoryManagement::VS_GetMemoryBlob
(
	const BYTE*						i_cpbyteObjectID,
	const DWORD						i_cdwObjectIDLen,
	const DWORD						i_cdwMemoryBlobType,
	DWORD*							o_pdwMemoryBlobLen,
	void**							o_ppvoidMemory
)
{
	HRESULT						hResult				=	E_FAIL;

	int							nCompare			=	999;

	BOOL						boolTypeFound		=	FALSE;

	g_MemoryNode*				pMemoryNode			=	NULL;

	long						longCurrentTime		=	0;

	do
	{
		VSGMM_CHECK_OBJECT_TIMEOUT

			//	check input parameters
		VSGMM_CHECK_INPUT_POINTER_FOR_NULL (i_cpbyteObjectID)
		VSGMM_CHECK_LENGTH_FOR_ZERO (i_cdwObjectIDLen)
		VSGMM_CHECK_LENGTH_FOR_ZERO (o_pdwMemoryBlobLen)
		VSGMM_CHECK_INPUT_POINTER_FOR_NULL (o_ppvoidMemory)

				//	make sure that the object exists
		hResult =	m_CheckForObject
					(
						i_cpbyteObjectID,
						i_cdwObjectIDLen
					);
		VSGMM_CHECK_HRESULT
			
/*			//	make sure that the object exists
		if ( i_cdwObjectIDLen != (m_pHeadObjectNode ->dwObjectIDLen) )
		{
			hResult	=	E_OBJECT_NODE_NOT_FOUND;
			break;
		}

		nCompare =	::memcmp
					(
						(const void*) i_cpbyteObjectID,
						(const void*) (m_pHeadObjectNode -> pbyteObjectID),
						i_cdwObjectIDLen
					);
		if ( 0 != nCompare )
		{
			hResult	=	E_OBJECT_NODE_NOT_FOUND;
			break;
		}
*/
		pMemoryNode =	(m_pHeadObjectNode -> pHeadMemoryBlob);

				//	traverse the memory blob list to the end.
		while ( NULL != pMemoryNode )
		{
					//	if a memory blob of the specified type is found
					//	then copy the contents in the output variables
			if ( i_cdwMemoryBlobType ==  (pMemoryNode -> dwMemoryBlobType) )
			{
				*o_pdwMemoryBlobLen	=	pMemoryNode -> dwMemoryBlobLen;
				*o_ppvoidMemory		=	pMemoryNode -> pvoidMemoryBlob;

					//	turn the found flag true and break out of the loop
				boolTypeFound =	TRUE;
				break;
			}

			pMemoryNode =	(pMemoryNode -> pNext);
		}

				//	if found is false then return error
		if ( FALSE == boolTypeFound )
		{
			hResult =	E_MEMORY_BLOB_TYPE_NOT_FOUND;
			break;
		}

		hResult =	S_OK;
	}	while (0);

	return	hResult;
}	//	end		HRESULT		g_GlobalMemoryManagement::VS_GetMemoryBlob


HRESULT		g_GlobalMemoryManagement::VS_DeleteMemoryBlob
(
	const BYTE*						i_cpbyteObjectID,
	const DWORD						i_cdwObjectIDLen,
	const DWORD						i_cdwMemoryBlobType
)
{
	HRESULT						hResult				=	E_FAIL;

	int							nCompare			=	999;

	BOOL						boolTypeFound		=	FALSE;

	g_MemoryNode*				pMemoryNode			=	NULL;
	g_MemoryNode*				pNextMemoryNode		=	NULL;
	g_MemoryNode*				pPreviousMemoryNode	=	NULL;

	long						longCurrentTime		=	0;

	do
	{
		VSGMM_CHECK_OBJECT_TIMEOUT

			//	check input parameters
		VSGMM_CHECK_INPUT_POINTER_FOR_NULL (i_cpbyteObjectID)
		VSGMM_CHECK_LENGTH_FOR_ZERO (i_cdwObjectIDLen)

				//	make sure that the object exists
		hResult =	m_CheckForObject
					(
						i_cpbyteObjectID,
						i_cdwObjectIDLen
					);
		VSGMM_CHECK_HRESULT
			
/*			//	make sure that the object exists
		if ( i_cdwObjectIDLen != (m_pHeadObjectNode ->dwObjectIDLen) )
		{
			hResult	=	E_OBJECT_NODE_NOT_FOUND;
			break;
		}

		nCompare =	::memcmp
					(
						(const void*) i_cpbyteObjectID,
						(const void*) (m_pHeadObjectNode -> pbyteObjectID),
						i_cdwObjectIDLen
					);
		if ( 0 != nCompare )
		{
			hResult	=	E_OBJECT_NODE_NOT_FOUND;
			break;
		}
*/
		pMemoryNode =	(m_pHeadObjectNode -> pHeadMemoryBlob);

				//	traverse the memory blob list to the end.
		while ( NULL != pMemoryNode )
		{
					//	if a memory blob of the specified type is found
					//	then we have to delete it
			if ( i_cdwMemoryBlobType ==  (pMemoryNode -> dwMemoryBlobType) )
			{
					//	preserve the next and previous pointer in the list
				pPreviousMemoryNode	=	pMemoryNode -> pPrevious;
				pNextMemoryNode		=	pMemoryNode -> pNext;

					//	delete the node
				hResult =	m_VS_DeleteMemoryNode ( pMemoryNode );

					//	if previous is NOT null then previous -> next = next
				if ( NULL != pPreviousMemoryNode )
				{
					pPreviousMemoryNode -> pNext	=	pNextMemoryNode;
				}
				else
				{
						//	if previous is NULL then it means that it was the first node
						//	so point the head (m_pHeadObjectNode -> pHeadMemoryBlob)
						//	to the next node
					m_pHeadObjectNode -> pHeadMemoryBlob =	pNextMemoryNode;
				}

					//	if next is NOT null then next -> previous = previous
				if ( NULL != pNextMemoryNode )
				{
					pNextMemoryNode -> pPrevious	=	pPreviousMemoryNode;
				}

					//	turn the found flag true and break out of the loop
				boolTypeFound =	TRUE;
				break;
			}

			pMemoryNode =	(pMemoryNode -> pNext);
		}

				//	if found is false then return error
		if ( FALSE == boolTypeFound )
		{
			hResult =	E_MEMORY_BLOB_TYPE_NOT_FOUND;
			break;
		}

				//	decrement the number of blobs
		(m_pHeadObjectNode -> dwNumberOfMemoryBlobs) --;

		hResult =	S_OK;
	}	while (0);

	return	hResult;
}	//	end		HRESULT		g_GlobalMemoryManagement::VS_DeleteMemoryBlob


HRESULT		g_GlobalMemoryManagement::VS_SetObjectTimeoutInterval
(
	const DWORD						i_cdwObjectTimeoutInMin
)
{
	HRESULT						hResult				=	E_FAIL;

	do
	{
		m_dwObjectTimeoutInSec	=	i_cdwObjectTimeoutInMin * 60;

		time ( &m_lLastObjectAccessTime );

		hResult =	S_OK;
	}	while (0);

	return	hResult;
}	//	end		HRESULT		g_GlobalMemoryManagement::VS_SetObjectTimeoutInterval


HRESULT		g_GlobalMemoryManagement::VS_SetElementTimeoutInterval
(
	const DWORD						i_cdwElementTimeoutInMin
)
{
	HRESULT						hResult				=	E_FAIL;

	do
	{
		m_dwElementTimeoutInSec	=	i_cdwElementTimeoutInMin * 60;

		time ( &m_lElementTime );

		hResult =	S_OK;
	}	while (0);

	return	hResult;
}	//	HRESULT		g_GlobalMemoryManagement::VS_SetElementTimeoutInterval



HRESULT		g_GlobalMemoryManagement::VS_AddElement
(
	const _bstr_t					i_ctbstrElementID,
	const DWORD						i_cdwElementStatus,
	const BYTE*						i_cpbyteElement,
	const DWORD						i_cdwElementLen
)
{
	HRESULT						hResult				=	E_FAIL;

	g_Element*					pElement			=	NULL;
	g_Element*					pPreviousElement	=	NULL;
	g_Element*					pNewElement			=	NULL;

	BOOL						boolDuplicate		=	FALSE;

	long						longCurrentTime		=	0;

	do
	{
		VSGMM_CHECK_ELEMENT_TIMEOUT

		VSGMM_CHECK_LENGTH_FOR_ZERO ( strlen(i_ctbstrElementID) )
		VSGMM_CHECK_INPUT_POINTER_FOR_NULL (i_cpbyteElement)
		VSGMM_CHECK_LENGTH_FOR_ZERO (i_cdwElementLen)

		pElement =	m_pHeadElement;

				//	traverse the elementlist to the end.
		while ( NULL != pElement )
		{
					//	if a element already exists then flag it
			if ( i_ctbstrElementID ==  (pElement -> tbstrElementID) )
			{
				boolDuplicate =	TRUE;
				break;
			}

			pPreviousElement =	pElement;
			pElement =	(pElement -> pNext);
		}

				//	if the element is duplicate then return error
		if ( TRUE == boolDuplicate )
		{
			hResult =	E_ELEMENT_EXISTS;
			break;
		}

				//	allocate a new element
		pNewElement =	new g_Element;
		VSGMM_CHECK_ALLOCATED_MEMORY (pNewElement)

				//	set the element ID and the status
		pNewElement -> tbstrElementID	=	i_ctbstrElementID;
		pNewElement -> dwElementStatus	=	i_cdwElementStatus;

				//	copy the element byte data and the length
		VSGMM_ALLOC_AND_BYTEBLOB_COPY( (pNewElement -> pbyteElement), i_cpbyteElement, i_cdwElementLen )
		pNewElement -> dwElementLen		=	i_cdwElementLen;

				//	set the next and previous pointers
				//	since this is the last element in the list, the next is NULL
				//	the previous is the current last node in the list
		pNewElement -> pNext			=	NULL;
		pNewElement -> pPrevious		=	pPreviousElement;

				//	if previous is NULL then this is the
		if ( NULL != pPreviousElement )
		{
			pPreviousElement -> pNext = pNewElement;
		}
		else
		{
				//	if pPreviousElement is NULL then it means that the newly added
				//	element is the first in the list. so make it the head of the list
			m_pHeadElement =	pNewElement;
		}
		
				//	increment the number of elements in the list
		m_dwNumberOfElements ++;

		hResult =	S_OK;
	}	while (0);

	return	hResult;
}	//	end		HRESULT		g_GlobalMemoryManagement::VS_AddElement


HRESULT		g_GlobalMemoryManagement::VS_GetElement
(
	const _bstr_t					i_ctbstrElementID,
	DWORD*							o_pdwElementStatus,
	BYTE**							o_ppbyteElement,
	DWORD*							o_pdwElementLen
)
{
	HRESULT						hResult				=	E_FAIL;

	BOOL						boolFound			=	FALSE;

	g_Element*					pElement			=	NULL;

	long						longCurrentTime		=	0;

	do
	{
/*
			//	check if the list of elements is timed out.
		time ( &longCurrentTime );
		if ( (longCurrentTime - m_lElementTime) > m_dwElementTimeoutInSec )
		{
				//	if timed out then delete the list and return an error
			m_VS_DeleteElementList ( m_pHeadElement );
		}
*/

		VSGMM_CHECK_ELEMENT_TIMEOUT

		VSGMM_CHECK_LENGTH_FOR_ZERO ( strlen(i_ctbstrElementID) )
		VSGMM_CHECK_INPUT_POINTER_FOR_NULL (o_pdwElementStatus)
		VSGMM_CHECK_INPUT_POINTER_FOR_NULL (o_ppbyteElement)
		VSGMM_CHECK_INPUT_POINTER_FOR_NULL (o_pdwElementLen)

		pElement =	m_pHeadElement;

				//	traverse the elementlist to the end.
		while ( NULL != pElement )
		{
					//	see if the element ID matches
			if ( i_ctbstrElementID ==  (pElement -> tbstrElementID) )
			{
				*o_pdwElementStatus =	pElement -> dwElementStatus;
				*o_ppbyteElement	=	pElement -> pbyteElement;
				*o_pdwElementLen	=	pElement -> dwElementLen;

				boolFound =	TRUE;
				break;
			}

			pElement =	(pElement -> pNext);
		}

		if ( FALSE == boolFound )
		{
			hResult =	E_ELEMENT_NOT_FOUND;
		}
		
		hResult =	S_OK;
	}	while (0);

	return	hResult;
}	//	end		HRESULT		g_GlobalMemoryManagement::VS_GetElement


HRESULT		g_GlobalMemoryManagement::VS_GetLoadedCount
(
	DWORD*							o_pdwLoadedCount
)
{
	HRESULT						hResult				=	E_FAIL;

	do
	{
		VSGMM_CHECK_INPUT_POINTER_FOR_NULL (o_pdwLoadedCount)

		*o_pdwLoadedCount =	m_dwLoadedCount;

		hResult =	S_OK;
	}	while (0);

	return	hResult;
}	//	end		HRESULT		g_GlobalMemoryManagement::VS_GetLoadedCount


HRESULT		g_GlobalMemoryManagement::m_VS_DeleteMemoryNode
(
	g_MemoryNode*					i_pMemoryNode
)
{
	HRESULT						hResult				=	E_FAIL;

	do
	{
			//	check input parameters
		VSGMM_CHECK_INPUT_POINTER_FOR_NULL (i_pMemoryNode)

			//	reset all the 
		i_pMemoryNode -> dwMemoryBlobType	=	0;
		i_pMemoryNode -> pNext				=	NULL;
		i_pMemoryNode -> pPrevious			=	NULL;

			//	delete the memory blob. this can be 'securely' deleted
			//	in future if required
		delete [] (i_pMemoryNode -> pvoidMemoryBlob);
		i_pMemoryNode -> dwMemoryBlobLen = 0;

			//	delete the node
		delete	i_pMemoryNode;

		hResult =	S_OK;
	}	while (0);

	return	hResult;
}	//	end		HRESULT		g_GlobalMemoryManagement::m_VS_DeleteMemoryNode


HRESULT		g_GlobalMemoryManagement::m_VS_DeleteElementList
(
	g_Element*						i_pElement
)
{
	HRESULT						hResult				=	E_FAIL;

	g_Element*					pNextElement		=	NULL;
	g_Element*					pCurrentElement		=	NULL;

	do
	{
		pCurrentElement =	i_pElement;

		while ( NULL != pCurrentElement )
		{
			pNextElement =	pCurrentElement -> pNext;

			pCurrentElement -> dwElementLen		=	0;
			pCurrentElement -> dwElementStatus	=	0;
			
			delete [] (pCurrentElement -> pbyteElement);

			delete pCurrentElement;

			pCurrentElement = pNextElement;
		}

		m_dwNumberOfElements =	0;

		hResult =	E_FAIL;
	}	while (0);

	return	hResult;
}	//	end		HRESULT		g_GlobalMemoryManagement::m_VS_DeleteElementList


inline HRESULT		g_GlobalMemoryManagement::m_CheckForObject
(
	const BYTE*						i_cpbyteObjectID,
	const DWORD						i_cdwObjectIDLen
)
{
	HRESULT						hResult				=	E_FAIL;

	int							nCompare			=	999;

	do
	{
		if ( NULL == m_pHeadObjectNode )
		{
			hResult	=	E_OBJECT_NODE_NOT_FOUND;
			break;
		}

				//	make sure that the object exists
		if ( i_cdwObjectIDLen != (m_pHeadObjectNode ->dwObjectIDLen) )
		{
			hResult	=	E_OBJECT_NODE_NOT_FOUND;
			break;
		}

		nCompare =	::memcmp
					(
						(const void*) i_cpbyteObjectID,
						(const void*) (m_pHeadObjectNode -> pbyteObjectID),
						i_cdwObjectIDLen
					);
		if ( 0 != nCompare )
		{
			hResult	=	E_OBJECT_NODE_NOT_FOUND;
			break;
		}

		hResult =	S_OK;
	} while (0);

	return	hResult;
}	//	end		HRESULT		g_GlobalMemoryManagement::m_CheckForObject ()