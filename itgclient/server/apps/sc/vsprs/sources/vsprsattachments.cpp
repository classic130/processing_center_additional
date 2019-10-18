
#include "vsprsattachments.h"

void VSPRSAttachment::VSPRSAT_Base64Attachments()
{

	
	FILEINFO *ptr = NULL;
	DWORD cbNames;
	PBYTE pbNames = NULL;

	if (!VSPRSAT_IsAttachmentBase64()) {
		mbase64Attachments = TRUE;
		for(ptr = mHead; ptr != NULL; ptr = ptr->next) {
		
			_Base64Encode((char *)ptr->pbFileData,
							ptr->cbFileSize,
							NULL,
							(unsigned int *)&cbNames);

			pbNames = (BYTE *) malloc(cbNames+1);


			_Base64Encode((char *)ptr->pbFileData,
						    ptr->cbFileSize,
							(char *)pbNames,
							(unsigned int *)&cbNames) ;

			// Free the original memory and point to the new storage.
			//free(ptr->pbFileData);

			// null-terminate it.
			pbNames[cbNames] = '\0';
			ptr->cbFileSize = cbNames;
			ptr->pbFileData = pbNames;
		} // end for loop

	} // end if 

	return;
}

