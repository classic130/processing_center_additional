/*
 * $Revision: 1.1.2.1 $
 * $Header: /cvs/itgclient/client/apps/fet/vsfe/h/Attic/vspmsmp.h,v 1.1.2.1 2000/02/25 01:38:13 aranade Exp $
 */

/*-----------------------------------------------------------------------\
| Copyright (C) VeriSign, Inc. created 1999. All rights reserved.        |
| This is an unpublished work protected as such under copyright law.     |
| This work contains proprietary, confidential, and trade secret         |
| information of VeriSign, Inc.  Use, disclosure or reproduction without |
| the expressed written authorization of VeriSign, Inc.  is prohibited.  |
\-----------------------------------------------------------------------*/


#ifndef _VSPMSMP_H_
#define _VSPMSMP_H_

#include "vspmutil.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef WIN32
#define VSPM_EXPORT extern __declspec( dllexport )
#else
#define VSPM_EXPORT extern
#endif

#define VSPM_NVP_CONTAINER		"NVP"

typedef struct _VSPMSP_Module {
	unsigned char * moduleName;
	unsigned int moduleNameLen;
	void ( * GeneratePolicyFuncPtr )( VSPM_Container pmd, VSPM_STATUS * status);
} VSPMSP_Module;


/* This function returns the container's name
 *
 *   cnt      - IN  - the reference to the container
 *   status   - OUT - if the function returns NULL, the return status indicates the failure reason
 *   RETURNS  - an ASCII, null-terminated string 
 *              NULL if an error is encountered
 */

VSPM_EXPORT unsigned char *
        VSPMSP_GetContainerName (
                VSPM_Container cnt,
                VSPM_STATUS *status);


/* This function returns the container's name length
 *
 *   cnt      - IN  - the reference to the container
 *   status   - OUT - if the function returns NULL, the return status indicates the failure reason
 *   RETURNS  - Number of bytes in the name, not including the terminating '\0' byte
 */

VSPM_EXPORT unsigned int
        VSPMSP_GetContainerNameLength (
                VSPM_Container cnt,
                VSPM_STATUS *status);


/* This function sets the container's name
 *
 *   cnt      - IN  - the reference to the container
 *   name     - IN  - a pointer to the container name
 *   nameLen  - IN  - Number of bytes in the name, not including the terminating '\0' byte
 *   status   - OUT - if the function returns NULL, the return status indicates the failure reason
 */

VSPM_EXPORT void
        VSPMSP_SetContainerName (
                VSPM_Container cnt,
                const unsigned char * name,
                unsigned int * nameLen,
                VSPM_STATUS *status);


/* This function returns the version of the container
 *
 *   cnt      - IN  - the reference to the container
 *   status   - OUT - if the function returns NULL, the return status indicates the failure reason
 *   RETURNS  - a VSPM_Version or
 *              NULL if an error is encountered
 */

VSPM_EXPORT VSPM_Version
        VSPMSP_GetVersion (
                VSPM_Container cnt,
                VSPM_STATUS *status);


/* This function sets the version of the container
 *
 *   cnt      - IN  - the reference to the container
 *   maj      - IN  - the major version of the container
 *   min      - IN  - the minor version of the container
 *   status   - OUT - if the function returns NULL, the return status indicates the failure reason
 */

VSPM_EXPORT void
        VSPMSP_SetVersion (
                VSPM_Container cnt,
                unsigned int maj,
                unsigned int min,
                VSPM_STATUS *status);


/* This function returns the number of immediate subordinate containers in the container
 *
 *   cnt      - IN  - the reference to the container
 *   status   - OUT - if the function fails, the return status indicates the failure reason
 *   RETURNS  - an positive integer or 
 *              0 if no container is found or an error is encountered
 */

VSPM_EXPORT unsigned int
        VSPMSP_ContainerCount (
                VSPM_Container cnt,
                VSPM_STATUS *status);


/* This function returns the number of immediate items in the container
 *
 *   cnt      - IN  - the reference to the container
 *   status   - OUT - if the function fails, the return status indicates the failure reason
 *   RETURNS  - an positive integer or 
 *              0 if no item is found or an error is encountered
 */

VSPM_EXPORT unsigned int
        VSPMSP_ItemCount (
                VSPM_Container cnt,
                VSPM_STATUS *status);


/* This function returns the container with a given name in the container
 *
 *   cnt      - IN  - the reference to the container
 *   name     - IN  - a pointer to the name of the container
 *   nameLen  - IN  - Number of bytes in the name, not including the terminating '\0' byte
 *   status   - OUT - if the function returns NULL, the return status indicates the failure reason
 *   RETURNS  - a VSPM_Container or
 *              NULL if an error is encountered
 */

VSPM_EXPORT VSPM_Container
        VSPMSP_GetContainerByName (
                VSPM_Container cnt,
                const char * name, 
                unsigned int nameLen, 
                VSPM_STATUS *status);


/* This function sets the container with a given name in the container
 *
 *   cnt      - IN  - the reference to the container
 *   name     - IN  - a pointer to the name of the container
 *   nameLen  - IN  - Number of bytes in the name, not including the terminating '\0' byte
 *   newCnt   - IN  - Reference to the container that is to be set
 *   status   - OUT - if the function returns NULL, the return status indicates the failure reason
 */

VSPM_EXPORT void
        VSPMSP_SetContainerByName (
                VSPM_Container cnt,
                const char * name, 
                unsigned int nameLen, 
                VSPM_Container newCnt, 
                VSPM_STATUS *status);


/* This function returns the container at a given index in the container
 *
 *   cnt      - IN  - the reference to the container
 *   index    - IN  - 0 based index. It should be a positive integer less than the value
 *                    returned by VSPMSP_ContainerCount
 *   status   - OUT - if the function returns NULL, the return status indicates the
 *                    failure reason
 *   RETURNS  - a VSPM_Container or
 *              NULL if an error is encountered
 */

VSPM_EXPORT VSPM_Container
        VSPMSP_GetContainer (
                VSPM_Container cnt,
                unsigned int index, 
                VSPM_STATUS *status);


/* This function sets the container at a given index in the container
 *
 *   cnt      - IN  - the reference to the container
 *   index    - IN  - 0 based index. It should be a positive integer less than the value
 *                    returned by VSPMSP_ContainerCount
 *   newCnt   - IN  - Reference to the container that is to be set
 *   status   - OUT - if the function returns NULL, the return status indicates the
 *                    failure reason
 *   RETURNS  - a VSPM_Container or
 *              NULL if an error is encountered
 */

VSPM_EXPORT void
        VSPMSP_SetContainer (
                VSPM_Container cnt,
                unsigned int index, 
                VSPM_Container newCnt, 
                VSPM_STATUS *status);


/* This function returns the item at a given index in the container
 *
 *   cnt      - IN  - the reference to the container
 *   index    - IN  - 0 based index. It should be a positive integer less than the value
 *                    returned by VSPM_ItemCount
 *   status   - OUT - if the function returns NULL, the return status indicates the
 *                    failure reason
 *   RETURNS  - a VSPM_Item or
 *              NULL if an error is encountered
 */

VSPM_EXPORT VSPM_Item
        VSPMSP_GetItem (
                VSPM_Container cnt,
                unsigned int index, 
                VSPM_STATUS *status);


/* This function sets the item at a given index in the container
 *
 *   cnt      - IN  - the reference to the container
 *   index    - IN  - 0 based index. It should be a positive integer less than the value
 *                    returned by VSPM_ItemCount
 *   item     - IN  - an item to be set
 *   status   - OUT - if the function returns NULL, the return status indicates the
 *                    failure reason
 */

VSPM_EXPORT void
        VSPMSP_SetItem (
                VSPM_Container cnt,
                unsigned int index, 
                VSPM_Item item, 
                VSPM_STATUS *status);


/* This function returns the item with a given name in the container
 *
 *   cnt      - IN  - the reference to the container
 *   name     - IN  - an ASCII, null-terminated search string for the name of the item
 *   nameLen  - IN  - number of bytes, not including the terminating '\0' of the length of name
 *   status   - OUT - if the function returns NULL, the return status indicates the failure reason
 *   RETURNS  - a VSPM_Item or
 *              NULL if an error is encountered
 */

VSPM_EXPORT VSPM_Item
        VSPMSP_GetItemByName (
                VSPM_Container cnt,
                const char* name, 
                unsigned int nameLen, 
                VSPM_STATUS *status);


/* This function sets the item with a given name in the container
 *
 *   cnt      - IN  - the reference to the container
 *   name     - IN  - a pointer to the name
 *   nameLen  - IN  - number of bytes, not including the terminating '\0' of the length of name
 *   item     - IN  - an item to be set
 *   status   - OUT - if the function returns NULL, the return status indicates the failure reason
 */

VSPM_EXPORT void
        VSPMSP_SetItemByName (
                VSPM_Container cnt,
                const char* name, 
                unsigned int nameLen, 
                VSPM_Item item, 
                VSPM_STATUS *status);


/* This function appends a new container at the end of the container
 *
 *   cnt      - IN  - the reference to the container
 *   newCnt   - IN  - Reference to the container that is to be added
 *   status   - OUT - if the function returns NULL, the return status indicates the
 *                    failure reason
 */

VSPM_EXPORT void
        VSPMSP_AddContainer (
                VSPM_Container cnt,
                VSPM_Container newCnt, 
                VSPM_STATUS *status);


/* This function appends a new item at the end of the container
 *
 *   cnt      - IN  - the reference to the container
 *   item     - IN  - Reference to the item that is to be added
 *   status   - OUT - if the function returns NULL, the return status indicates the
 *                    failure reason
 */

VSPM_EXPORT void
        VSPMSP_AddItem (
                VSPM_Container cnt,
                VSPM_Item item, 
                VSPM_STATUS *status);


/* This function deletes a container at the given index from the parent container
 *
 *   cnt      - IN  - the reference to the container
 *   index    - IN  - 0 based index. It should be a positive integer less than the value
 *                    returned by VSPM_CountainerCount
 *   status   - OUT - if the function returns NULL, the return status indicates the
 *                    failure reason
 */

VSPM_EXPORT void
        VSPMSP_DeleteContainer (
                VSPM_Container cnt,
		unsigned int index,
                VSPM_STATUS *status);


/* This function deletes the container with a given name in the container
 *
 *   cnt      - IN  - the reference to the container
 *   name     - IN  - a pointer to the name of the container
 *   nameLen  - IN  - Number of bytes in the name, not including the terminating '\0' byte
 *   status   - OUT - if the function returns NULL, the return status indicates the failure reason
 */

VSPM_EXPORT void
        VSPMSP_DeleteContainerByName (
                VSPM_Container cnt,
                const char * name, 
                unsigned int nameLen, 
                VSPM_STATUS *status);


/* This function deletes a item at the given index from the parent container
 *
 *   cnt      - IN  - the reference to the container
 *   index    - IN  - 0 based index. It should be a positive integer less than the value
 *                    returned by VSPM_ItemCount
 *   status   - OUT - if the function returns NULL, the return status indicates the
 *                    failure reason
 */

VSPM_EXPORT void
        VSPMSP_DeleteItem (
                VSPM_Container cnt,
		unsigned int index,
                VSPM_STATUS *status);


/* This function deletes the item with a given name in the container
 *
 *   cnt      - IN  - the reference to the container
 *   name     - IN  - a pointer to the name of the item
 *   nameLen  - IN  - Number of bytes in the name, not including the terminating '\0' byte
 *   status   - OUT - if the function returns NULL, the return status indicates the failure reason
 */

VSPM_EXPORT void
        VSPMSP_DeleteItemByName (
                VSPM_Container cnt,
                const char * name, 
                unsigned int nameLen, 
                VSPM_STATUS *status);


/* This function returns the name of the item
 *
 *   itm      - IN  - the reference to the item
 *   status   - OUT - if the function fails, the return status indicates the failure reason
 *   RETURNS  - a null-terminated string
 *              NULL if an error is encountered
 */

VSPM_EXPORT unsigned char *
        VSPMSP_GetName (
                VSPM_Item itm,
                VSPM_STATUS *status);


/* This function returns the length of the name of the item
 *
 *   itm      - IN  - the reference to the item
 *   status   - OUT - if the function fails, the return status indicates the failure reason
 *   RETURNS  - Number of bytes in the name, not including the terminating '\0' byte
 */

VSPM_EXPORT unsigned int
        VSPMSP_GetNameLength (
                VSPM_Item itm,
                VSPM_STATUS *status);


/* This function sets the name of the item
 *
 *   itm      - IN  - the reference to the item
 *   name     - IN  - a pointer to the name
 *   nameLen  - IN  - number of bytes in the name, not including the terminating '\0' byte
 *   status   - OUT - if the function fails, the return status indicates the failure reason
 */

VSPM_EXPORT void
        VSPMSP_SetName (
                VSPM_Item itm,
                const unsigned char * name,
                unsigned int nameLen,
                VSPM_STATUS *status);


/* This function returns the value of the item
 *
 *   itm      - IN  - the reference to the item
 *   status   - OUT - if the function fails, the return status indicates the failure reason
 *   RETURNS  - a null-terminated string
 *              NULL if an error is encountered
 */

VSPM_EXPORT unsigned char *
        VSPMSP_GetValue (
                VSPM_Item itm,
                VSPM_STATUS *status);


/* This function returns the length of the value of the item
 *
 *   itm      - IN  - the reference to the item
 *   status   - OUT - if the function fails, the return status indicates the failure reason
 *   RETURNS  - Number of bytes in the value, not including the terminating '\0' byte
 */

VSPM_EXPORT unsigned int
        VSPMSP_GetValueLength (
                VSPM_Item itm,
                VSPM_STATUS *status);


/* This function sets the value of the item
 *
 *   itm      - IN  - the reference to the item
 *   value    - IN  - a pointer to the value
 *   valueLen - IN  - number of bytes in the value, not including the terminating '\0' byte
 *   status   - OUT - if the function fails, the return status indicates the failure reason
 */

VSPM_EXPORT void
        VSPMSP_SetValue (
                VSPM_Item itm,
                const unsigned char * value,
                unsigned int valueLen,
                VSPM_STATUS *status);


/* This function returns the a textual explanation associated with a VSPM_STATUS
 *
 *   pmd      - IN  - the descriptor to the policy file
 *   status   - IN  - status code to be explained
 *   RETURNS  - a null-terminated string. This string can contain multi-byte characters.
 *              NULL if an error is encountered
 */

VSPM_EXPORT unsigned char *
        VSPMSP_DescribeStatus (
                VSPM_Descriptor pmd,
                VSPM_STATUS status);


/* This function allocates the memory needed by a VSPM_Container
 *
 *   status   - OUT - if the function fails, the return status indicates the failure reason
 *   RETURNS  - a reference to VSPM_Container
 */

VSPM_EXPORT VSPM_Container
        VSPM_AllocContainer (
				VSPM_Container parentCnt,
                VSPM_STATUS *status);


/* This function allocates the memory needed by a VSPM_Item
 *
 *   status   - OUT - if the function fails, the return status indicates the failure reason
 *   RETURNS  - a reference to VSPM_Item
 */

VSPM_EXPORT VSPM_Item
        VSPM_AllocItem (
				VSPM_Container parentCnt,
                VSPM_STATUS *status);



#ifdef  __cplusplus
}
#endif

#endif  /* _VSPMSMP_H_ */
