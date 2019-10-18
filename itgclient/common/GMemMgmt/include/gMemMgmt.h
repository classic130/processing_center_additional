///////////////////////////////////////////////////////////////////////////////
///	
///	This Memory Management scheme is designed to make all the allocations in 
///	the global memory.
///
///	The browsers destroy an instance of activeX control and creates another
///	instance when it goes from one page to another. Due to this, the memory
///	belonging to a particular instance is destroyed and cannot be accessed
///	on the next page.
///
///	If all the memory is allocated in the global memory then it can be accessed
///	accross multiple instances.
///
///	The dll containing the activeX control could get unloaded if the object
///	instance count is zero. The Memory Management scheme will prevent that
///	by making sure that the dll is not unloaded till all the memory is freed.
///
///////////////////////////////////////////////////////////////////////////////


#ifndef		__VS_GLOBAL_MEMORY_MANAGEMENT_H__
#define		__VS_GLOBAL_MEMORY_MANAGEMENT_H__

#ifndef	_WIN32_WINNT
#define	_WIN32_WINNT		0x0400
#endif


#include <atlbase.h>
#include <time.h>
#include <comdef.h>


//#include <stdio.h>
//#include <stdlib.h>
//#include <conio.h>

//#include <string.h>
//#include <wchar.h>
//#include <mbstring.h>
#include <time.h>
#include <winerror.h>
#include <winbase.h>

#include <tchar.h>


#define		VSSC_MESSAGE_SMIME							1
#define		VSSC_MESSAGE_HEADER							2
#define		VSSC_MESSAGE_BODY							3
#define		VSSC_MESSAGE_ATTACHMENTS					4
#define     VSSC_MESSAGE_ATT_FILE_NAMES                 5 
#define     VSSC_MESSAGE_ENTITY                         6 


#define		VSSC_DEFAULT_OBJECT_TIMEOUT					300
#define		VSSC_DEFAULT_ELEMENT_TIMEOUT				300


///
///	The g_Element structure will store the Element in the form
///	of a byte blob and its length
///
struct g_Element
{
	_bstr_t							tbstrElementID;
	DWORD							dwElementStatus;
	BYTE*							pbyteElement;
	DWORD							dwElementLen;
	g_Element*						pNext;
	g_Element*						pPrevious;
};

///
///	The g_MemoryNode structure will store the memory pointer, its type
///	and length.
///
struct	g_MemoryNode
{
	DWORD							dwMemoryBlobType;
	void*							pvoidMemoryBlob;
	DWORD							dwMemoryBlobLen;
	g_MemoryNode*					pNext;
	g_MemoryNode*					pPrevious;
};

///
///	The g_ObjectNode structure will store all the information for a particular
///	message. The message is uniquely identified by the ObjectID.
///	ObjectID is basically a byte blob of any length.
///
///	Corresponding to a ObjectID there is a list of MemoryBlobs. They are stored
///	in form of a linked list of the g_MemoryNode structure
///
struct	g_ObjectNode
{
	BYTE*							pbyteObjectID;
	DWORD							dwObjectIDLen;

	DWORD							dwNumberOfMemoryBlobs;

//	DWORD							dwAccessTimeOutInSec;	//	inactivity timeout limit.
//	long							lLastAccessTime;		//	last time any of the Memory
															//	node is accessed

	g_MemoryNode*					pHeadMemoryBlob;		//	list of the memory nodes
};


///
///	A global instance of this class will be created when the dll is loaded.
///	All the instances of the activeX controls will use this global instance
///	for all the memory requirements.
///
///	Typically an instance of activeX control will be assocaited with a single
/// message. This class will have a linked list of g_ObjectNodes corresponding
///	to each instance of the activeX control.
///
class	g_GlobalMemoryManagement
{
	private:	
		HANDLE							m_hNamedMutex;

		DWORD							m_dwPID;
		DWORD							m_dwLoadedCount;	//	this count will determine
															//	if the dll can be unloaded
															//	This count will depend on
															//	the m_dwNumberOfObjectNodes
															//	and the dwNumberOfObjects

		DWORD							m_dwObjectTimeoutInSec;	//	inactivity timeout limit.
		long							m_lLastObjectAccessTime;	//	last time any of the Object
																//	node is accessed

		DWORD							m_dwElementTimeoutInSec;
		long							m_lElementTime;

		DWORD							m_dwNumberOfObjectNodes;
		g_ObjectNode*					m_pHeadObjectNode;	//	list of Object node
//		g_ObjectNode					m_HeadObjectNode;	//	Object node

		DWORD							m_dwNumberOfElements;
		g_Element*						m_pHeadElement;	//	list of Elements
	
	public:
		g_GlobalMemoryManagement ();
		
		~g_GlobalMemoryManagement ();


		HRESULT		AddObjectNode
		(
			const BYTE*						i_cpbyteObjectID,
			const DWORD						i_cdwObjectIDLen
		//	const DWORD						i_cdwObjectTimeoutInMin
		);

		HRESULT		DeleteObjectNode
		(
			const BYTE*						i_cpbyteObjectID,
			const DWORD						i_cdwObjectIDLen
		);

		////Narinder: To delete node with Object ID There is only One node
		HRESULT		DeleteObjectNodeWithOutID
		(
			
		);


		HRESULT		VS_AllocateMemory
		(
			const BYTE*						i_cpbyteObjectID,
			const DWORD						i_cdwObjectIDLen,
			const DWORD						i_cdwMemoryBlobType,
			const DWORD						i_cdwMemoryBlobLen,
			void**							o_ppvoidMemory
		);

		HRESULT		VS_GetMemoryBlob
		(
			const BYTE*						i_cpbyteObjectID,
			const DWORD						i_cdwObjectIDLen,
			const DWORD						i_cdwMemoryBlobType,
			DWORD*							o_pdwMemoryBlobLen,
			void**							o_ppvoidMemory
		);

		HRESULT		VS_DeleteMemoryBlob
		(
			const BYTE*						i_cpbyteObjectID,
			const DWORD						i_cdwObjectIDLen,
			const DWORD						i_cdwMemoryBlobType
		);

		HRESULT		VS_SetObjectTimeoutInterval
		(
			const DWORD						i_cdwObjectTimeoutInMin
		);

		HRESULT		VS_SetElementTimeoutInterval
		(
			const DWORD						i_cdwElementTimeoutInMin
		);

		HRESULT		VS_AddElement
		(
			const _bstr_t					i_ctbstrElementID,
			const DWORD						i_cdwElementStatus,
			const BYTE*						i_cpbyteElement,
			const DWORD						i_cdwElementLen
		);

		HRESULT		VS_GetElement
		(
			const _bstr_t					i_ctbstrElementID,
			DWORD*							o_pdwElementStatus,
			BYTE**							o_ppbyteElement,
			DWORD*							o_pdwElementLen
		);

		HRESULT		VS_GetLoadedCount
		(
			DWORD*							o_pdwLoadedCount
		);


	private:
		HRESULT		m_VS_DeleteMemoryNode
		(
			g_MemoryNode*					i_pMemoryNode
		);

		HRESULT		m_VS_DeleteElementList
		(
			g_Element*						i_pElement
		);

		inline HRESULT		m_CheckForObject
		(
			const BYTE*						i_cpbyteObjectID,
			const DWORD						i_cdwObjectIDLen
		);


};	//	end		class	g_GlobalMemoryManagement



///////////////////////////////////////////////////////////////////////////////
/*
	There are 6 cases:
		1.	Compose
		2.	Compose and Attach
		3.	Reply
		4.	Reply and Attach
		5.	Forward
		6.	Forward and Attach

	
	Compose:
		No complications

	Compose and Attach:
		i.	MIME formatted Message header and message body is stored
		ii.	If any attachments are already selected then even the attachments
			are stored.
		iii.Control moves to a new page where the user can select more attachment(s).
		iv.	On the original page, read the Message header, body and already selected
			attachments
		v.	Also add the newly selected attachments
		vi. Display the message to the user.
		
	Reply:
		i.	As soon as the SMIME blob is downloaded, store it
		ii.	When the user clicks reply, store the message header, body and attachements
		iii.On the new page, read the message header, body and attachments and display
			it to the user.

	Reply and Attach:
		i - iii.	Same as Reply
		iv.	The user changes the body/header
		v.	If the user wants to select more attachments store the message header,
			body and any existing attachments
				iii.Control moves to a new page where the user can select more attachment(s).
		vi.	On the original page, read the Message header, body and already selected
			attachments
		vii.	Also add the newly selected attachments
		viiii. Display the message to the user.

	Forward and Froward and Attach are similar to the Reply and Reply and Attach cases.
*/

#endif