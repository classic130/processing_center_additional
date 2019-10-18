/*
 * $Revision: 1.1.2.1 $
 * $Header: /cvs/itgclient/server/apps/sc/policymodule/include/Attic/vspmutil.h,v 1.1.2.1 2001/09/06 22:32:19 ajayaram Exp $
 */

/*-----------------------------------------------------------------------\
| Copyright (C) VeriSign, Inc. created 1999. All rights reserved.        |
| This is an unpublished work protected as such under copyright law.     |
| This work contains proprietary, confidential, and trade secret         |
| information of VeriSign, Inc.  Use, disclosure or reproduction without |
| the expressed written authorization of VeriSign, Inc.  is prohibited.  |
\-----------------------------------------------------------------------*/


#ifndef _VSPMUTIL_H_
#define _VSPMUTIL_H_

#ifdef __cplusplus
extern "C" {
#endif

#ifdef WIN32
#define VSPM_EXPORT extern __declspec( dllexport )
#else
#define VSPM_EXPORT extern
#endif

#define SCOPE_CHAR '//'

/* This enum holds all error codes that can be returned from
 * calls to VeriSign's DLL.
 */

typedef unsigned int VSPM_STATUS;

#define       VSPM_STATUS_NO_ERROR              0xC000          /* no error */
#define       VSPM_CANNOT_OPEN_FILE             0xC001          /* Cannot open the file */
#define       VSPM_INVALID_TOKEN                0xC002          /* Invalid token in the file */
#define       VSPM_NO_CLOSE_SESSION             0xC003          /* No closing bracket */
#define       VSPM_OUT_OF_MEMORY                0xC004          /* No more memory */
#define       VSPM_INVALID_DESCRIPTOR           0xC005          /* The specified VSPM_Descriptor is invalid */
#define       VSPM_NOT_FOUND                    0xC006
#define       VSPM_INVALID_TEXT                 0xC007
#define       VSPM_INVALID_T61                  0xC008
#define       VSPM_INVALID_EMAIL                0xC009
#define       VSPM_INVALID_NUMBER               0xC00A
#define       VSPM_INVALID_BASE64               0xC00B
#define       VSPM_INVALID_PHONE                0xC00C
#define       VSPM_INVALID_DATE                 0xC00D
#define       VSPM_INVALID_TYPE                 0xC00E
#define       VSPM_FIELD_REQUIRED               0xC00F
#define       VSPM_FIELD_TOO_SHORT              0xC010
#define       VSPM_FIELD_TOO_LONG               0xC011
#define       VSPM_INVALID_VERSION              0xC012
#define       VSPM_INDEX_OUT_OF_RANGE           0xC013
#define       VSPM_INVALID_FILE_FORMAT          0xC014
#define       VSPM_NOT_SUPPORTED_FILE_FORMAT    0xC015
#define       VSPM_INVALID_PASSCODE             0xC016
#define       VSPM_NOT_SUPPORTED_FEATURE        0xC017
#define       VSPM_INVALID_CRS_URL              0xC018
#define       VSPM_INVALID_ENROLLMENT_URL       0xC019



/*
typedef enum {
        VSPM_STATUS_NO_ERROR    =  0xC000,  
        VSPM_CANNOT_OPEN_FILE,              
        VSPM_INVALID_TOKEN,                 
        VSPM_NO_CLOSE_SESSION,              
        VSPM_OUT_OF_MEMORY,                 
        VSPM_INVALID_DESCRIPTOR,            
        VSPM_NOT_FOUND,
        VSPM_INVALID_TEXT,
        VSPM_INVALID_T61,
        VSPM_INVALID_EMAIL,
        VSPM_INVALID_NUMBER,
        VSPM_INVALID_BASE64,
        VSPM_INVALID_PHONE,
        VSPM_INVALID_DATE,
        VSPM_INVALID_TYPE,
        VSPM_FIELD_REQUIRED,
        VSPM_FIELD_TOO_SHORT,
        VSPM_FIELD_TOO_LONG,
	VSPM_INVALID_VERSION,
	VSPM_INDEX_OUT_OF_RANGE,
	VSPM_INVALID_FILE_FORMAT,
	VSPM_NOT_SUPPORTED_FILE_FORMAT
} VSPM_STATUS;
*/


struct _VSPM_Version {

    unsigned short major;       /* Major version number */
    unsigned short minor;       /* Minor version number */

};


typedef void *			VSPM_Descriptor;
typedef void *			VSPM_Container;
typedef void *			VSPM_Item;
typedef struct _VSPM_Version *	VSPM_Version;


/* This function opens a policy description file
 *
 *   pathname - IN  - the path name of the policy description file
 *   status   - OUT - if the function returns NULL, the return status indicates the failure reas
on
 *   RETURNS  - a VSPM_Descriptor or
 *              NULL if an error is encountered
 */

VSPM_EXPORT VSPM_Descriptor
        VSPM_Open (
                const char *pathname,
                VSPM_STATUS *status);


/* This function closes and cleans up the data associated with a previously opened VSPM_Descriptor
 *
 *   pmd - IN  - the descriptor of the policy description file
 *              
 */

VSPM_EXPORT void
        VSPM_Close (
                VSPM_Descriptor pmd);


/* This function returns the version of the policy description file
 *
 *   pmd      - IN  - the descriptor of the policy description file
 *   status   - OUT - if the function returns NULL, the return status indicates the failure reason
 *   RETURNS  - a VSPM_Version or
 *              NULL if an error is encountered
 */

VSPM_EXPORT VSPM_Version
        VSPM_GetVersionFromDescriptor (
                VSPM_Descriptor pmd,
                VSPM_STATUS *status);


/* This function returns the number of containers in the policy file referenced by
 * the policy descriptor
 *
 *   pmd      - IN  - the descriptor of the policy description file
 *   status   - OUT - if the function fails, the return status indicates the failure reason
 *   RETURNS  - an positive integer or 
 *              0 if no container is found or an error is encountered
 */

VSPM_EXPORT unsigned int
        VSPM_ContainerCountFromDescriptor (
                VSPM_Descriptor pmd,
                VSPM_STATUS *status);


/* This function returns the number of items in the policy file referenced by
 * the policy descriptor
 *
 *   pmd      - IN  - the descriptor of the policy description file
 *   status   - OUT - if the function fails, the return status indicates the failure reason
 *   RETURNS  - an positive integer or 
 *              0 if no item is found or an error is encountered
 */

VSPM_EXPORT unsigned int
        VSPM_ItemCountFromDescriptor (
                VSPM_Descriptor pmd,
                VSPM_STATUS *status);


/* This function returns the container with a given name in the policy description file
 *
 *   pmd      - IN  - the descriptor of the policy description file
 *   name     - IN  - an ASCII, null-terminated search string for the name of the container
 *   status   - OUT - if the function returns NULL, the return status indicates the failure reason
 *   RETURNS  - a VSPM_Container or
 *              NULL if an error is encountered
 */

VSPM_EXPORT VSPM_Container
        VSPM_GetContainerByNameFromDescriptor (
                VSPM_Descriptor pmd,
                const char* name, 
                VSPM_STATUS *status);


/* This function returns the container at a given index in the policy description file
 *
 *   pmd      - IN  - the descriptor of the policy description file
 *   index    - IN  - 0 based index. It should be a positive integer less than the value
 *                    returned by VSPM_ContainerCountFromDescriptor
 *   status   - OUT - if the function returns NULL, the return status indicates the
 *                    failure reason
 *   RETURNS  - a VSPM_Container or
 *              NULL if an error is encountered
 */

VSPM_EXPORT VSPM_Container
        VSPM_GetContainerFromDescriptor (
                VSPM_Descriptor pmd,
                unsigned int index, 
                VSPM_STATUS *status);


/* This function returns the item with a given name in the policy description file
 *
 *   pmd      - IN  - the descriptor of the policy description file
 *   name     - IN  - an ASCII, null-terminated search string for the name of the item
 *   status   - OUT - if the function returns NULL, the return status indicates the failure reason
 *   RETURNS  - a VSPM_Item or
 *              NULL if an error is encountered
 */

VSPM_EXPORT VSPM_Item
        VSPM_GetItemByNameFromDescriptor (
                VSPM_Descriptor pmd,
                const char* name, 
                VSPM_STATUS *status);


/* This function returns the item at a given index in the policy description file
 *
 *   pmd      - IN  - the descriptor of the policy description file
 *   index    - IN  - 0 based index. It should be a positive integer less than the value
 *                    returned by VSPM_ItemCountFromDescriptor
 *   status   - OUT - if the function returns NULL, the return status indicates the
 *                    failure reason
 *   RETURNS  - a VSPM_Item or
 *              NULL if an error is encountered
 */

VSPM_EXPORT VSPM_Item
        VSPM_GetItemFromDescriptor (
                VSPM_Descriptor pmd,
                unsigned int index, 
                VSPM_STATUS *status);


/* This function returns the version of the container
 *
 *   cnt      - IN  - the reference to the container
 *   status   - OUT - if the function returns NULL, the return status indicates the failure reason
 *   RETURNS  - a VSPM_Version or
 *              NULL if an error is encountered
 */

VSPM_EXPORT VSPM_Version
        VSPM_GetVersion (
                VSPM_Container cnt,
                VSPM_STATUS *status);


/* This function returns the number of immediate subordinate containers in the container
 *
 *   cnt      - IN  - the reference to the container
 *   status   - OUT - if the function fails, the return status indicates the failure reason
 *   RETURNS  - an positive integer or 
 *              0 if no container is found or an error is encountered
 */

VSPM_EXPORT unsigned int
        VSPM_ContainerCount (
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
        VSPM_ItemCount (
                VSPM_Container cnt,
                VSPM_STATUS *status);


/* This function returns the container's name
 *
 *   cnt      - IN  - the reference to the container
 *   status   - OUT - if the function returns NULL, the return status indicates the failure reason
 *   RETURNS  - an ASCII, null-terminated string 
 *              NULL if an error is encountered
 */

VSPM_EXPORT char *
        VSPM_GetContainerName (
                VSPM_Container cnt,
                VSPM_STATUS *status);


/* This function returns the container with a given name in the container
 *
 *   cnt      - IN  - the reference to the container
 *   name     - IN  - an ASCII, null-terminated search string for the name of the container
 *   status   - OUT - if the function returns NULL, the return status indicates the failure reason
 *   RETURNS  - a VSPM_Container or
 *              NULL if an error is encountered
 */

VSPM_EXPORT VSPM_Container
        VSPM_GetContainerByName (
                VSPM_Container cnt,
                const char* name, 
                VSPM_STATUS *status);


/* This function returns the container at a given index in the container
 *
 *   cnt      - IN  - the reference to the container
 *   index    - IN  - 0 based index. It should be a positive integer less than the value
 *                    returned by VSPM_ContainerCount
 *   status   - OUT - if the function returns NULL, the return status indicates the
 *                    failure reason
 *   RETURNS  - a VSPM_Container or
 *              NULL if an error is encountered
 */

VSPM_EXPORT VSPM_Container
        VSPM_GetContainer (
                VSPM_Container cnt,
                unsigned int index, 
                VSPM_STATUS *status);


/* This function returns the item with a given name in the container
 *
 *   cnt      - IN  - the reference to the container
 *   name     - IN  - an ASCII, null-terminated search string for the name of the item
 *   status   - OUT - if the function returns NULL, the return status indicates the failure reason
 *   RETURNS  - a VSPM_Item or
 *              NULL if an error is encountered
 */

VSPM_EXPORT VSPM_Item
        VSPM_GetItemByName (
                VSPM_Container cnt,
                const char* name, 
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
        VSPM_GetItem (
                VSPM_Container cnt,
                unsigned int index, 
                VSPM_STATUS *status);


/* This function returns the name of the item
 *
 *   itm      - IN  - the reference to the item
 *   status   - OUT - if the function fails, the return status indicates the failure reason
 *   RETURNS  - a null-terminated string
 *              NULL if an error is encountered
 */

VSPM_EXPORT char *
        VSPM_GetName (
                VSPM_Item itm,
                VSPM_STATUS *status);


/* This function returns the value of the item
 *
 *   itm      - IN  - the reference to the item
 *   status   - OUT - if the function fails, the return status indicates the failure reason
 *   RETURNS  - a null-terminated string
 *              NULL if an error is encountered
 */

VSPM_EXPORT char *
        VSPM_GetValue (
                VSPM_Item itm,
                VSPM_STATUS *status);


/* This function returns the a textual explanation associated with a VSPM_STATUS
 *
 *   pmd      - IN  - the descriptor to the policy file
 *   status   - IN  - status code to be explained
 *   RETURNS  - a null-terminated string. This string can contain multi-byte characters.
 *              NULL if an error is encountered
 */

VSPM_EXPORT char *
        VSPM_DescribeStatus (
                VSPM_Descriptor pmd,
                VSPM_STATUS status);


/* This function frees the memory occupied by a VSPM_Version
 *
 *   ver      - IN  - the reference to VSPM_Version
 *   status   - OUT - if the function fails, the return status indicates the failure reason
 */

VSPM_EXPORT void
        VSPM_FreeVersion (
                VSPM_Version ver,
                VSPM_STATUS *status);


/* This function frees the memory occupied by a VSPM_Container
 *
 *   itm      - IN  - the reference to VSPM_Container
 *   status   - OUT - if the function fails, the return status indicates the failure reason
 */

VSPM_EXPORT void
        VSPM_FreeContainer (
                VSPM_Container itm,
                VSPM_STATUS *status);


/* This function frees the memory occupied by a VSPM_Item
 *
 *   itm      - IN  - the reference to VSPM_Item
 *   status   - OUT - if the function fails, the return status indicates the failure reason
 */

VSPM_EXPORT void
        VSPM_FreeItem (
                VSPM_Item itm,
                VSPM_STATUS *status);


/* This function frees the memory occupied by a null-terminated string
 *
 *   str      - IN  - the null-terminated string
 *   status   - OUT - if the function fails, the return status indicates the failure reason
 */

VSPM_EXPORT void
        VSPM_FreeString (
                char * str,
                VSPM_STATUS *status);


#ifdef  __cplusplus
}
#endif

#endif  /* _VSPMUTIL_H_ */
