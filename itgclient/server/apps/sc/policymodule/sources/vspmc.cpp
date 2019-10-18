/*
 * $Revision: 1.1.2.1 $
 * $Header: /cvs/itgclient/server/apps/sc/policymodule/sources/Attic/vspmc.cpp,v 1.1.2.1 2001/09/06 22:32:33 ajayaram Exp $
 */

/*-----------------------------------------------------------------------\
| Copyright (C) VeriSign, Inc. created 1999. All rights reserved.        |
| This is an unpublished work protected as such under copyright law.     |
| This work contains proprietary, confidential, and trade secret         |
| information of VeriSign, Inc.  Use, disclosure or reproduction without |
| the expressed written authorization of VeriSign, Inc.  is prohibited.  |
\-----------------------------------------------------------------------*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>

#include "vspmcP.h"
#include "vspmctype.h"
#include "base64.h"

typedef int Boolean;
#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif


//!!!! Should try not to use this global buffer, it's not MT-safe !!!!
static char lastError[1024];


/* This function returns the major and minor numbers of the enrollment
 * specification implemented by the interface
 *
 *   pmd      - IN  - the descriptor of the policy description file
 *   prodType - IN  - the product type of the enrollment policy
 *   maj      - OUT - the major version of the enrollment spec for the product type
 *   min      - OUT - the minor version of the enrollment spec for the product type
 *   status   - OUT - status code
 *   
 */

VSPM_EXPORT void
        VSPM_GetSpecVersion (
                VSPM_Descriptor pmd,
				VSPM_PRODUCT_TAG prodType,
				unsigned short *maj,
				unsigned short *min,
                VSPM_STATUS *status) {

	/* Only supports end-user for now */
	if (prodType == VSPM_END_USER) {
		*maj = END_USER_SPEC_MAJ;
		*min = END_USER_SPEC_MIN;
		if (status != NULL)
		*status = VSPM_STATUS_NO_ERROR;
	}
	else {
		if (status != NULL)
		*status = VSPM_NOT_SUPPORTED_FEATURE;
	}

}


/* This function returns the number of enrollment parameters associated with the
 * enrollment policy of a given product type
 *
 *   pmd      - IN  - the descriptor of the policy description file
 *   prodType - IN  - the product type of the enrollment policy
 *   status   - OUT - if the function fails, the return status indicates the failure reason
 *   RETURNS  - an positive integer or 
 *              0 if no item is found or an error is encountered
 */

VSPM_EXPORT unsigned int
        VSPM_GetParameterCount (
                VSPM_Descriptor pmd,
				VSPM_PRODUCT_TAG prodType,
                VSPM_STATUS *status) {

	VSPM_STATUS rc = VSPM_STATUS_NO_ERROR;
	unsigned int count = 0;
	VSPM_Container enrollCnt = NULL;
	VSPM_Container tmpCnt = NULL;
	VSPM_Item tmpItem = NULL;
	const char * value = NULL;

	/* Only supports end-user for now */
	if (prodType != VSPM_END_USER) {
		if (status != NULL)
		*status = VSPM_NOT_SUPPORTED_FEATURE;
		return 0;
	}

	do {

		enrollCnt = VSPM_GetContainerByNameFromDescriptor(pmd, VSPM_USER_ENROLLMENT_CONTAINER, &rc);
		if (rc != VSPM_STATUS_NO_ERROR)
			break;

		unsigned int tmpCount = VSPM_ContainerCount(enrollCnt, &rc);
		if (rc != VSPM_STATUS_NO_ERROR)
			break;

		int i = 0;
		for (i = 0; i < tmpCount; i++) {

			tmpCnt = VSPM_GetContainer(enrollCnt, i, &rc);
			if (rc != VSPM_STATUS_NO_ERROR)
				break;
			
			tmpItem = VSPM_GetItemByName(tmpCnt, VSPM_IS_ENROLL_PARAM, &rc);
			if (rc != VSPM_STATUS_NO_ERROR) {
				if (rc == VSPM_NOT_FOUND) {
					rc = VSPM_STATUS_NO_ERROR;
					continue;
				}
				else
					break;
			}

			value = (const char *) VSPM_GetValue(tmpItem, &rc);
			if (rc != VSPM_STATUS_NO_ERROR)
				break;
			
			if (strstr(value, TRUE_VAL) != NULL) {

				if (tmpItem) {
					VSPM_FreeItem(tmpItem, &rc);
					tmpItem = NULL;
				}

				if (value) {
					VSPM_FreeString((char *)value, &rc);
					value = NULL;
				}

				tmpItem = VSPM_GetItemByName(tmpCnt, VSPM_POLICY_VALUE, &rc);
				if (rc != VSPM_STATUS_NO_ERROR) {
					if (rc == VSPM_NOT_FOUND) {
						rc = VSPM_STATUS_NO_ERROR;
						continue;
					}
					else
						break;
				}

				value = (const char *) VSPM_GetValue(tmpItem, &rc);
				if (rc != VSPM_STATUS_NO_ERROR)
					break;
			
				if (( ! strcmp(value, SHOW) ) ||
					(strstr(value, EXISTS) != NULL))
					count++;
			}

			/* Remember to free up the memory */
			if (tmpCnt)
				VSPM_FreeContainer(tmpCnt, &rc);
			tmpCnt = NULL;
			if (tmpItem)
				VSPM_FreeItem(tmpItem, &rc);
			tmpItem = NULL;
			if (value)
				VSPM_FreeString((char *)value, &rc);
			value = NULL;

		}

		if (rc != VSPM_STATUS_NO_ERROR)
			break;
			
		count += MIN_PARAM_COUNT;

	} while (0);

	if (status != NULL)
	*status = rc;

	if (enrollCnt)
		VSPM_FreeContainer(enrollCnt, &rc);

	if (tmpCnt)
		VSPM_FreeContainer(tmpCnt, &rc);

	if (tmpItem)
		VSPM_FreeItem(tmpItem, &rc);

	if (value)
		VSPM_FreeString((char *)value, &rc);

	return count;

}


/* This function returns the enrollment parameter based on the product type
 *
 *   pmd      - IN  - the descriptor of the policy description file
 *   prodType - IN  - the product type of the enrollment policy
 *   index    - IN  - between 0 and the value returned by VSPM_GetParamterCount()
 *   status   - OUT - if the function returns NULL, the return status indicates the failure reason
 *   RETURNS  - a VSPM_PARAMETER or
 *              NULL if an error is encountered
 */

VSPM_EXPORT VSPM_PARAMETER
        VSPM_GetParameter (
                VSPM_Descriptor pmd,
				VSPM_PRODUCT_TAG prodType,
                unsigned int index,
                VSPM_STATUS *status) {

	VSPM_STATUS rc = VSPM_STATUS_NO_ERROR;
	_VSPM_PARAMETER *param = NULL;
	VSPM_Container enrollCnt = NULL;
	VSPM_Container tmpCnt = NULL;
	VSPM_Item tmpItem = NULL;
	const char * value = NULL;
	unsigned int paramIndex = -1;


	/* Only supports end-user for now */
	if (prodType != VSPM_END_USER) {
		if (status != NULL)
		*status = VSPM_NOT_SUPPORTED_FEATURE;
		return NULL;
	}

	do {

		if (index < MIN_PARAM_COUNT) {

			param = GetInternalParam(pmd, index, &rc);
			if (rc != VSPM_STATUS_NO_ERROR)
				break;

		}
		else {

			index -= MIN_PARAM_COUNT;

			enrollCnt = VSPM_GetContainerByNameFromDescriptor(pmd, VSPM_USER_ENROLLMENT_CONTAINER, &rc);
			if (rc != VSPM_STATUS_NO_ERROR)
				break;

			unsigned int count = VSPM_ContainerCount(enrollCnt, &rc);
			if (rc != VSPM_STATUS_NO_ERROR)
				break;

			int i = 0;
			for (i = 0; i < count; i++) {

				tmpCnt = VSPM_GetContainer(enrollCnt, i, &rc);
				if (rc != VSPM_STATUS_NO_ERROR)
					break;
			
				tmpItem = VSPM_GetItemByName(tmpCnt, VSPM_IS_ENROLL_PARAM, &rc);
				if (rc != VSPM_STATUS_NO_ERROR) {
					if (rc == VSPM_NOT_FOUND) {
						rc = VSPM_STATUS_NO_ERROR;
						continue;
					}
					else
						break;
				}

				value = (const char *) VSPM_GetValue(tmpItem, &rc);
				if (rc != VSPM_STATUS_NO_ERROR)
					break;
			
				if (strstr(value, TRUE_VAL) != NULL) {

					if (tmpItem) {
						VSPM_FreeItem(tmpItem, &rc);
						tmpItem = NULL;
					}

					if (value) {
						VSPM_FreeString((char *)value, &rc);
						value = NULL;
					}

					tmpItem = VSPM_GetItemByName(tmpCnt, VSPM_POLICY_VALUE, &rc);
					if (rc != VSPM_STATUS_NO_ERROR)
						break;

					value = (const char *) VSPM_GetValue(tmpItem, &rc);
					if (rc != VSPM_STATUS_NO_ERROR)
						break;

					if ((! strcmp(value, EXISTS)) || (! strcmp(value, SHOW))) {
						paramIndex++;

						if (paramIndex == index) {

							param = (_VSPM_PARAMETER *) malloc(sizeof(_VSPM_PARAMETER));
							if (param == NULL) {
								rc = VSPM_OUT_OF_MEMORY;
								break;
							}
							memset(param, 0, sizeof(_VSPM_PARAMETER));

							if (tmpItem) {
								VSPM_FreeItem(tmpItem, &rc);
								tmpItem = NULL;
							}

							if (value) {
								VSPM_FreeString((char *)value, &rc);
								value = NULL;
							}

							/* Populate the fieldType field in _VSPM_PARAMETER */
							tmpItem = VSPM_GetItemByName(tmpCnt, VSPM_PROCESS_TYPE, &rc);
							if (rc != VSPM_STATUS_NO_ERROR)
								break;

							value = (const char *) VSPM_GetValue(tmpItem, &rc);
							if (rc != VSPM_STATUS_NO_ERROR)
								break;
							
							if (strstr(value, VSPM_USER_INPUT) != NULL) {
								param->fieldType = VSPM_USER_INPUT_FIELD;
							}
							else if (strstr(value, VSPM_DISPLAY_ONLY) != NULL) {
								param->fieldType = VSPM_DISPLAY_ONLY_FIELD;
							}
							else if (strstr(value, VSPM_HARD_CODED) != NULL) {
								param->fieldType = VSPM_HARD_CODED_FIELD;
							}
							else if (strstr(value, VSPM_SOFTWARE_CONFIG) != NULL) {
								param->fieldType = VSPM_SOFTWARE_CONFIG_FIELD;
							}
							else if (strstr(value, VSPM_USER_SELECTABLE) != NULL) {
								param->fieldType = VSPM_USER_SELECTABLE_FIELD;
							}
							else {
								rc = VSPM_NOT_SUPPORTED_FEATURE;
								break;
							}

							if (tmpItem) {
								VSPM_FreeItem(tmpItem, &rc);
								tmpItem = NULL;
							}

							if (value) {
								VSPM_FreeString((char *)value, &rc);
								value = NULL;
							}

							/* Populate the displayName field in _VSPM_PARAMETER */
							tmpItem = VSPM_GetItemByName(tmpCnt, VSPM_DISPLAY_NAME, &rc);
							if (rc != VSPM_STATUS_NO_ERROR)
								break;

							value = (const char *) VSPM_GetValue(tmpItem, &rc);
							if (rc != VSPM_STATUS_NO_ERROR)
								break;

							param->displayName = (char *) strdup(value);
							if (param->displayName == NULL) {
								rc = VSPM_OUT_OF_MEMORY;
								break;
							}

							if (tmpItem) {
								VSPM_FreeItem(tmpItem, &rc);
								tmpItem = NULL;
							}

							if (value) {
								VSPM_FreeString((char *)value, &rc);
								value = NULL;
							}

							/* Populate the internalName field in _VSPM_PARAMETER */
							tmpItem = VSPM_GetItemByName(tmpCnt, VSPM_INTERNAL_NAME, &rc);
							if (rc != VSPM_STATUS_NO_ERROR)
								break;

							value = (const char *) VSPM_GetValue(tmpItem, &rc);
							if (rc != VSPM_STATUS_NO_ERROR)
								break;

							param->internalName = (char *) strdup(value);
							if (param->internalName == NULL) {
								rc = VSPM_OUT_OF_MEMORY;
								break;
							}

							if (tmpItem) {
								VSPM_FreeItem(tmpItem, &rc);
								tmpItem = NULL;
							}

							if (value) {
								VSPM_FreeString((char *)value, &rc);
								value = NULL;
							}

							/* Populate the tag field in _VSPM_PARAMETER */
							tmpItem = VSPM_GetItemByName(tmpCnt, VSPM_FDF_TYPE, &rc);
							if (rc != VSPM_STATUS_NO_ERROR)
								break;

							value = (const char *) VSPM_GetValue(tmpItem, &rc);
							if (rc != VSPM_STATUS_NO_ERROR)
								break;

							if (strstr(value, VSPM_FDF_TEXT) != NULL) {
								param->tag = VSPM_VALUE_TEXT;
							}
							else if (strstr(value, VSPM_FDF_EMAIL) != NULL) {
								param->tag = VSPM_VALUE_EMAIL;
							}
							else if (strstr(value, VSPM_FDF_CLEAR) != NULL) {
								param->tag = VSPM_VALUE_CLEAR;
							}
							else if (strstr(value, VSPM_FDF_T61) != NULL) {
								param->tag = VSPM_VALUE_T61;
							}
							else if (strstr(value, VSPM_FDF_BASE64) != NULL) {
								param->tag = VSPM_VALUE_BASE64;
							}
							else if (strstr(value, VSPM_FDF_DATE) != NULL) {
								param->tag = VSPM_VALUE_DATE;
							}
							else if (strstr(value, VSPM_FDF_NUMBER) != NULL) {
								param->tag = VSPM_VALUE_NUMBER;
							}
							else if (strstr(value, VSPM_FDF_PHONE) != NULL) {
								param->tag = VSPM_VALUE_PHONE;
							}
							else if (strstr(value, VSPM_FDF_PASSCODE) != NULL) {
								param->tag = VSPM_VALUE_PASSCODE;
							}
							else {
								rc = VSPM_NOT_SUPPORTED_FEATURE;
								break;
							}

							if (tmpItem) {
								VSPM_FreeItem(tmpItem, &rc);
								tmpItem = NULL;
							}

							if (value) {
								VSPM_FreeString((char *)value, &rc);
								value = NULL;
							}

							/* Populate the req field in _VSPM_PARAMETER */
							tmpItem = VSPM_GetItemByName(tmpCnt, VSPM_IS_REQUIRED, &rc);
							if (rc != VSPM_STATUS_NO_ERROR)
								break;

							value = (const char *) VSPM_GetValue(tmpItem, &rc);
							if (rc != VSPM_STATUS_NO_ERROR)
								break;

							if (strstr(value, MANDATORY) != NULL) {
								param->req = VSPM_REQ_MANDATORY;
							}
							else {
								param->req = VSPM_REQ_OPTIONAL;
							}

							if (tmpItem) {
								VSPM_FreeItem(tmpItem, &rc);
								tmpItem = NULL;
							}

							if (value) {
								VSPM_FreeString((char *)value, &rc);
								value = NULL;
							}

							/* Populate the minLen field in _VSPM_PARAMETER */
							tmpItem = VSPM_GetItemByName(tmpCnt, VSPM_MIN_LEN, &rc);
							if (rc != VSPM_STATUS_NO_ERROR)
								break;

							value = (const char *) VSPM_GetValue(tmpItem, &rc);
							if (rc != VSPM_STATUS_NO_ERROR)
								break;

							/* May need to check for the errno after the call */
							param->minLen = (unsigned short) atoi(value);

							if (tmpItem) {
								VSPM_FreeItem(tmpItem, &rc);
								tmpItem = NULL;
							}

							if (value) {
								VSPM_FreeString((char *)value, &rc);
								value = NULL;
							}

							/* Populate the maxLen field in _VSPM_PARAMETER */
							tmpItem = VSPM_GetItemByName(tmpCnt, VSPM_MAX_LEN, &rc);
							if (rc != VSPM_STATUS_NO_ERROR)
								break;

							value = (const char *) VSPM_GetValue(tmpItem, &rc);
							if (rc != VSPM_STATUS_NO_ERROR)
								break;

							/* May need to check for the errno after the call */
							param->maxLen = (unsigned short) atoi(value);


							if (tmpItem) {
								VSPM_FreeItem(tmpItem, &rc);
								tmpItem = NULL;
							}

							if (value) {
								VSPM_FreeString((char *)value, &rc);
								value = NULL;
							}

							/* If the param is hard-coded or display-only field 
							 * then grab the value */
							if ((param->fieldType == VSPM_HARD_CODED_FIELD) ||
								(param->fieldType == VSPM_DISPLAY_ONLY_FIELD)) {

								/* Populate the maxLen field in _VSPM_PARAMETER */
								tmpItem = VSPM_GetItemByName(tmpCnt, VSPM_VALUE, &rc);
								if (rc != VSPM_STATUS_NO_ERROR)
									break;

								value = (const char *) VSPM_GetValue(tmpItem, &rc);
								if (rc != VSPM_STATUS_NO_ERROR)
									break;

								param->value = strdup(value);
								if (param->value == NULL) {
									rc = VSPM_OUT_OF_MEMORY;
									break;
								}

							}

							/* found the right policy */
							break;

						} /* if paramIndex == index */

					} /* if policyValue*/

				} /* if isEnrollParam */

				/* Remember to free up the memory */
				if (tmpCnt)
					VSPM_FreeContainer(tmpCnt, &rc);
				tmpCnt = NULL;
				if (tmpItem)
					VSPM_FreeItem(tmpItem, &rc);
				tmpItem = NULL;
				if (value)
					VSPM_FreeString((char *)value, &rc);
				value = NULL;

			} /* for */

			if (rc != VSPM_STATUS_NO_ERROR)
				break;

		} /* if */

	} while (0);

	if (status != NULL)
	*status = rc;

	if ((rc == VSPM_STATUS_NO_ERROR) && (param == NULL))
		if (status != NULL)
		*status = VSPM_INDEX_OUT_OF_RANGE;

	if (rc != VSPM_STATUS_NO_ERROR) {
		if (param)
			VSPM_FreeParam(param, &rc);
	}

	/* Remember to free up the memory */
	if (enrollCnt)
		VSPM_FreeContainer(enrollCnt, &rc);

	if (tmpCnt)
		VSPM_FreeContainer(tmpCnt, &rc);

	if (tmpItem)
		VSPM_FreeItem(tmpItem, &rc);

	if (value)
		VSPM_FreeString((char *)value, &rc);

	return (VSPM_PARAMETER) param;

}


/* This function does the dirty work to extrapolate the information from policy entries that do 
 * not map well to the fdf entries to _VSPM_PARAMETER struct
 * Mapping:
 * 		0 : version
 *		1 : charEncoding
 *		2 : charSet
 *		3 : charFilter
 *		4 : charFilterParam
 * 
 * These param are all either hard-coded or software-config
 */
_VSPM_PARAMETER * GetInternalParam(VSPM_Descriptor pmd, unsigned int index, VSPM_STATUS *status) {

	VSPM_STATUS rc = VSPM_STATUS_NO_ERROR;
	_VSPM_PARAMETER *param = NULL;
	VSPM_Container enrollCnt = NULL;
	VSPM_Container charCnt = NULL;
	VSPM_Item tmpItem = NULL;
	unsigned isSpecified = 0;
	const char * value = NULL;

	if (index >= MIN_PARAM_COUNT) {
		if (status != NULL)
		*status = VSPM_INDEX_OUT_OF_RANGE;
		return NULL;
	}

	do {

		enrollCnt = VSPM_GetContainerByNameFromDescriptor(pmd, VSPM_USER_ENROLLMENT_CONTAINER, &rc);
		if (rc != VSPM_STATUS_NO_ERROR)
			break;


		param = (_VSPM_PARAMETER *) malloc (sizeof(_VSPM_PARAMETER));
		if (param == NULL) {
			rc = VSPM_OUT_OF_MEMORY;
			break;
		}
		memset(param, 0, sizeof(_VSPM_PARAMETER));
		param->minLen = 1;
		param->maxLen = 255;

		if (index > 0) {

			charCnt = VSPM_GetContainerByName(enrollCnt, VSPM_CHAR_ENCODING_CONTAINER, &rc);
			if (rc != VSPM_STATUS_NO_ERROR)
				break;
			
			tmpItem = VSPM_GetItemByName(charCnt, VSPM_POLICY_VALUE, &rc);
			if (rc != VSPM_STATUS_NO_ERROR)
				break;
			
			value = (const char *) VSPM_GetValue(tmpItem, &rc);
			if (rc != VSPM_STATUS_NO_ERROR)
				break;
			
			if (strstr(value, ABSENT) == NULL) {
				isSpecified = 1;
				param->fieldType = VSPM_HARD_CODED_FIELD;
			}
			else {
				isSpecified = 0;
				param->fieldType = VSPM_SOFTWARE_CONFIG_FIELD;
			}

			param->tag = VSPM_VALUE_CLEAR;
			param->req = VSPM_REQ_OPTIONAL;


			VSPM_FreeItem(tmpItem, &rc);
			tmpItem = NULL;
			VSPM_FreeString((char *)value, &rc);
			value = NULL;

		}

		switch (index) {
		case 0:
			param->fieldType = VSPM_HARD_CODED_FIELD;
			param->displayName = strdup(VERSION);
			param->internalName = strdup(VERSION);
			param->tag = VSPM_VALUE_TEXT;
			param->req = VSPM_REQ_MANDATORY;
			tmpItem = VSPM_GetItemByName(enrollCnt, VSPM_VERSION_NAME, &rc);
			if (rc != VSPM_STATUS_NO_ERROR)
				break;

			value = (const char *) VSPM_GetValue(tmpItem, &rc);
			if (rc != VSPM_STATUS_NO_ERROR)
				break;
			
			param->value = strdup(value);

			VSPM_FreeItem(tmpItem, &rc);
			tmpItem = NULL;
			VSPM_FreeString((char *)value, &rc);
			value = NULL;

			break;
		case 1:
			param->displayName = strdup(CHAR_ENCODING);
			param->internalName = strdup(CHAR_ENCODING);
			if (isSpecified) {

				tmpItem = VSPM_GetItemByName(charCnt, CHAR_ENCODING, &rc);
				if (rc != VSPM_STATUS_NO_ERROR)
					break;

				value = (const char *) VSPM_GetValue(tmpItem, &rc);
				if (rc != VSPM_STATUS_NO_ERROR)
					break;
				
				param->value = strdup(value);

				VSPM_FreeItem(tmpItem, &rc);
				tmpItem = NULL;
				VSPM_FreeString((char *)value, &rc);
				value = NULL;

			}
			break;
		case 2:
			param->displayName = strdup(CHAR_SET);
			param->internalName = strdup(CHAR_SET);
			if (isSpecified) {

				tmpItem = VSPM_GetItemByName(charCnt, CHAR_SET, &rc);
				if (rc != VSPM_STATUS_NO_ERROR)
					break;

				value = (const char *) VSPM_GetValue(tmpItem, &rc);
				if (rc != VSPM_STATUS_NO_ERROR)
					break;
				
				param->value = strdup(value);

				VSPM_FreeItem(tmpItem, &rc);
				tmpItem = NULL;
				VSPM_FreeString((char *)value, &rc);
				value = NULL;

			}
			break;
		case 3:
			param->displayName = strdup(CHAR_FILTER);
			param->internalName = strdup(CHAR_FILTER);
			if (isSpecified) {

				tmpItem = VSPM_GetItemByName(charCnt, CHAR_FILTER, &rc);
				if (rc != VSPM_STATUS_NO_ERROR)
					break;

				value = (const char *) VSPM_GetValue(tmpItem, &rc);
				if (rc != VSPM_STATUS_NO_ERROR)
					break;
				
				param->value = strdup(value);

				VSPM_FreeItem(tmpItem, &rc);
				tmpItem = NULL;
				VSPM_FreeString((char *)value, &rc);
				value = NULL;

			}
			break;
		case 4:
			param->displayName = strdup(CHAR_FILTER_PARAM);
			param->internalName = strdup(CHAR_FILTER_PARAM);
			if (isSpecified) {

				tmpItem = VSPM_GetItemByName(charCnt, CHAR_FILTER_PARAM, &rc);
				if (rc != VSPM_STATUS_NO_ERROR)
					break;

				value = (const char *) VSPM_GetValue(tmpItem, &rc);
				if (rc != VSPM_STATUS_NO_ERROR)
					break;
				
				param->value = strdup(value);

				VSPM_FreeItem(tmpItem, &rc);
				tmpItem = NULL;
				VSPM_FreeString((char *)value, &rc);
				value = NULL;

			}
			break;
		default:
			rc = VSPM_INDEX_OUT_OF_RANGE;
			break;
		}

	} while (0);

	if (status != NULL)
	*status = rc;

	if (param && (rc != VSPM_STATUS_NO_ERROR)) {
		VSPM_FreeParam((VSPM_PARAMETER) param, &rc);
		param = NULL;
	}

	if (enrollCnt)
		VSPM_FreeContainer(enrollCnt, &rc);

	if (charCnt)
		VSPM_FreeContainer(charCnt, &rc);

	if (tmpItem)
		VSPM_FreeItem(tmpItem, &rc);

	if (value)
		VSPM_FreeString((char *)value, &rc);

	return param;
}


/* This function verifies the enrollment data associated with a parameter
 *
 *   param    - IN  - parameter returned by the VSPM_GetParameter() function
 *   value    - IN  - data to be verified
 *   RETURNS  - status  
 *
 */

VSPM_EXPORT VSPM_STATUS
        VSPM_VerifyParameter (
				const VSPM_PARAMETER param,
                const char *value) {

    unsigned len = strlen((const char *)value);
	_VSPM_PARAMETER *entry = (_VSPM_PARAMETER *)param;

    if ((len == 0) && (entry->req == VSPM_REQ_MANDATORY))
        return VSPM_FIELD_REQUIRED;
    if ((len == 0) && (entry->req == VSPM_REQ_OPTIONAL))
        return VSPM_STATUS_NO_ERROR;
    if (len < entry->minLen)
        return VSPM_FIELD_TOO_SHORT;
    if (len > entry->maxLen)
        return VSPM_FIELD_TOO_LONG;

    switch (entry->tag)
    {
    case VSPM_VALUE_TEXT:        /* alphanumeric plus space '()+,-./:=? */
        if (isPrintableString(value))
            return VSPM_STATUS_NO_ERROR;
        else
            return VSPM_INVALID_TEXT;
        break;
    case VSPM_VALUE_T61:         /* T61 string */
        if (isT61String(value))
            return VSPM_STATUS_NO_ERROR;
        else
            return VSPM_INVALID_T61;
        break;
    case VSPM_VALUE_PASSCODE:         /* Passcode string */
        if (isT61String(value))
            return VSPM_STATUS_NO_ERROR;
        else
            return VSPM_INVALID_PASSCODE;
        break;
    case VSPM_VALUE_NUMBER:      /* decimal numeric only [0-9] */
        if (isValidNumber(value))
            return VSPM_STATUS_NO_ERROR;
        else
            return VSPM_INVALID_NUMBER;
        break;
    case VSPM_VALUE_BASE64:      /* Certificate in Base64 [0-9,a-f, CR, LF] */
        if (isBase64String(value))
            return VSPM_STATUS_NO_ERROR;
        else
            return VSPM_INVALID_BASE64;
        break;
    case VSPM_VALUE_EMAIL:       /* alphanumeric plus 1 @@ and at least one dot  */
        if (isValidEmailAddress(value))
            return VSPM_STATUS_NO_ERROR;
        else
            return VSPM_INVALID_EMAIL;
        break;
    case VSPM_VALUE_PHONE:       /* telephone number */
        if (isValidPhoneNumber(value))
            return VSPM_STATUS_NO_ERROR;
        else
            return VSPM_INVALID_PHONE;
        break;
    case VSPM_VALUE_DATE:        /* 8-digit numeric date in mmddyyyy */
        if (isValidDate(value))
            return VSPM_STATUS_NO_ERROR;
        else
            return VSPM_INVALID_EMAIL;
        break;
    case VSPM_VALUE_CLEAR:       /* anything goes */
        return VSPM_STATUS_NO_ERROR;
    }
    return VSPM_INVALID_TYPE;

}


/* This function returns the cryptographic configuration policy for CAPI
 *
 *   pmd      - IN  - the descriptor of the policy description file
 *   prodType - IN  - the product type of the enrollment policy
 *                    returned by VSPM_ContainerCountFromDescriptor
 *   status   - OUT - if the function returns NULL, the return status indicates the
 *                    failure reason
 *   RETURNS  - a VSPM_CRYPT_CONFIG or
 *              NULL if an error is encountered
 */

VSPM_EXPORT VSPM_CRYPT_CONFIG
        VSPM_GetCryptConfig (
                VSPM_Descriptor pmd,
				VSPM_PRODUCT_TAG prodType,
                VSPM_STATUS *status) {
	
	VSPM_STATUS rc = VSPM_STATUS_NO_ERROR;
	_VSPM_CRYPT_CONFIG *cryptConf = NULL;
	VSPM_Container enrollCnt = NULL;
	VSPM_Container tmpCnt = NULL;
	VSPM_Item tmpItem = NULL;
	const char * value = NULL;

	if (prodType != VSPM_END_USER) {
		if (status != NULL)
		*status = VSPM_NOT_SUPPORTED_FEATURE;
		return NULL;
	}

	do {

		enrollCnt = VSPM_GetContainerByNameFromDescriptor(pmd, VSPM_USER_ENROLLMENT_CONTAINER, &rc);
		if (rc != VSPM_STATUS_NO_ERROR)
			break;

		cryptConf = (_VSPM_CRYPT_CONFIG *)malloc(sizeof(_VSPM_CRYPT_CONFIG));
		if (cryptConf == NULL) {
			rc = VSPM_OUT_OF_MEMORY;
			break;
		}
		memset(cryptConf, 0, sizeof(_VSPM_CRYPT_CONFIG));

		tmpCnt = VSPM_GetContainerByName(enrollCnt, VSPM_CSP_CONTAINER, &rc);
		if (rc != VSPM_STATUS_NO_ERROR)
			break;

		/* Determine the value for _VSPM_CRYPT_CONFIG.isCSPUserSelectable field */
		tmpItem = VSPM_GetItemByName(tmpCnt, VSPM_POLICY_VALUE, &rc);
		if (rc != VSPM_STATUS_NO_ERROR)
			break;

		value = (const char *) VSPM_GetValue(tmpItem, &rc);
		if (rc != VSPM_STATUS_NO_ERROR)
			break;

		if (strstr(value, USER) != NULL) {
			cryptConf->isCSPUserSelectable = VSPM_TRUE;
		}
		else {
			cryptConf->isCSPUserSelectable = VSPM_FALSE;
		}

		VSPM_FreeItem(tmpItem, &rc);
		tmpItem = NULL;
		VSPM_FreeString((char *)value, &rc);
		value = NULL;

		/* Determine the value for _VSPM_CRYPT_CONFIG.prefCSP field */
		if (cryptConf->isCSPUserSelectable) {
			tmpItem = VSPM_GetItemByName(tmpCnt, VSPM_PREFERRED_PROV, &rc);
		}
		else {
			tmpItem = VSPM_GetItemByName(tmpCnt, VSPM_PROV_NAME, &rc);
		}
		if (rc != VSPM_STATUS_NO_ERROR)
			break;

		value = (const char *) VSPM_GetValue(tmpItem, &rc);
		if (rc != VSPM_STATUS_NO_ERROR)
			break;

		cryptConf->prefCSP = strdup(value);

		VSPM_FreeContainer(tmpCnt, &rc);
		tmpCnt = NULL;
		VSPM_FreeItem(tmpItem, &rc);
		tmpItem = NULL;
		VSPM_FreeString((char *)value, &rc);
		value = NULL;

		/* Determine the _VSPM_CRYPT_CONFIG.isKeyExportable field */
		tmpCnt = VSPM_GetContainerByName(enrollCnt, VSPM_KEY_EXPORT_CONTAINER, &rc);
		if (rc != VSPM_STATUS_NO_ERROR)
			break;

		tmpItem = VSPM_GetItemByName(tmpCnt, VSPM_POLICY_VALUE, &rc);
		if (rc != VSPM_STATUS_NO_ERROR)
			break;

		value = (const char *) VSPM_GetValue(tmpItem, &rc);
		if (rc != VSPM_STATUS_NO_ERROR)
			break;

		if (strstr(value, YES) != NULL) {
			cryptConf->isKeyExportable = VSPM_TRUE;
		}
		else {
			cryptConf->isKeyExportable = VSPM_FALSE;
		}

		VSPM_FreeContainer(tmpCnt, &rc);
		tmpCnt = NULL;
		VSPM_FreeItem(tmpItem, &rc);
		tmpItem = NULL;
		VSPM_FreeString((char *)value, &rc);
		value = NULL;

		/* Determine the _VSPM_CRYPT_CONFIG.isKeyProtectionUserSelectable field */
		tmpCnt = VSPM_GetContainerByName(enrollCnt, VSPM_KEY_PROTECT_CONTAINER, &rc);
		if (rc != VSPM_STATUS_NO_ERROR)
			break;

		tmpItem = VSPM_GetItemByName(tmpCnt, VSPM_POLICY_VALUE, &rc);
		if (rc != VSPM_STATUS_NO_ERROR)
			break;

		value = (const char *) VSPM_GetValue(tmpItem, &rc);
		if (rc != VSPM_STATUS_NO_ERROR)
			break;

		if (strstr(value, USER) != NULL) {
			cryptConf->isKeyProtectionUserSelectable = VSPM_TRUE;
		}
		else {
			cryptConf->isKeyProtectionUserSelectable = VSPM_FALSE;
		}

		VSPM_FreeItem(tmpItem, &rc);
		tmpItem = NULL;
		VSPM_FreeString((char *)value, &rc);
		value = NULL;

		/* Determine the _VSPM_CRYPT_CONFIG.isKeyProtected field */
		tmpItem = VSPM_GetItemByName(tmpCnt, VSPM_IS_PROTECTED, &rc);
		if (rc != VSPM_STATUS_NO_ERROR)
			break;

		value = (const char *) VSPM_GetValue(tmpItem, &rc);
		if (rc != VSPM_STATUS_NO_ERROR)
			break;

		if (strstr(value, TRUE_VAL) != NULL) {
			cryptConf->isKeyProtected = VSPM_TRUE;
		}
		else {
			cryptConf->isKeyProtected = VSPM_FALSE;
		}

		VSPM_FreeContainer(tmpCnt, &rc);
		tmpCnt = NULL;
		VSPM_FreeItem(tmpItem, &rc);
		tmpItem = NULL;
		VSPM_FreeString((char *)value, &rc);
		value = NULL;

		/* Determine the _VSPM_CRYPT_CONFIG.keyLength field */
		tmpCnt = VSPM_GetContainerByName(enrollCnt, VSPM_KEY_LENGTH_CONTAINER, &rc);
		if (rc != VSPM_STATUS_NO_ERROR)
			break;

		tmpItem = VSPM_GetItemByName(tmpCnt, VSPM_POLICY_VALUE, &rc);
		if (rc != VSPM_STATUS_NO_ERROR)
			break;

		value = (const char *) VSPM_GetValue(tmpItem, &rc);
		if (rc != VSPM_STATUS_NO_ERROR)
			break;

		cryptConf->keyLength = (unsigned short) atoi(value);

		VSPM_FreeItem(tmpItem, &rc);
		tmpItem = NULL;
		VSPM_FreeString((char *)value, &rc);
		value = NULL;

		/* Determine the _VSPM_CRYPT_CONFIG.isKeyLengthDegradable field */
		tmpItem = VSPM_GetItemByName(tmpCnt, VSPM_CAN_DEGRADE, &rc);
		if (rc != VSPM_STATUS_NO_ERROR)
			break;

		value = (const char *) VSPM_GetValue(tmpItem, &rc);
		if (rc != VSPM_STATUS_NO_ERROR)
			break;

		if (strstr(value, TRUE_VAL) != NULL) {
			cryptConf->isKeyLengthDegradable = VSPM_TRUE;
		}
		else {
			cryptConf->isKeyLengthDegradable = VSPM_FALSE;
		}

		VSPM_FreeContainer(tmpCnt, &rc);
		tmpCnt = NULL;
		VSPM_FreeItem(tmpItem, &rc);
		tmpItem = NULL;
		VSPM_FreeString((char *)value, &rc);
		value = NULL;

		/* Determine the _VSPM_CRYPT_CONFIG.minAdvapi32Ver field */
		tmpCnt = VSPM_GetContainerByNameFromDescriptor(pmd, VSPM_CRYPTVER_CONTAINER, &rc);
		if (rc != VSPM_STATUS_NO_ERROR)
			break;

		tmpItem = VSPM_GetItemByName(tmpCnt, VSPM_ADVAPI, &rc);
		if (rc != VSPM_STATUS_NO_ERROR)
			break;

		value = (const char *) VSPM_GetValue(tmpItem, &rc);
		if (rc != VSPM_STATUS_NO_ERROR)
			break;

		cryptConf->minAdvapi32Ver = strdup(value);

		VSPM_FreeItem(tmpItem, &rc);
		tmpItem = NULL;
		VSPM_FreeString((char *)value, &rc);
		value = NULL;

		/* Determine the _VSPM_CRYPT_CONFIG.minCrypt32Ver field */
		tmpItem = VSPM_GetItemByName(tmpCnt, VSPM_CRYPTVER, &rc);
		if (rc != VSPM_STATUS_NO_ERROR)
			break;

		value = (const char *) VSPM_GetValue(tmpItem, &rc);
		if (rc != VSPM_STATUS_NO_ERROR)
			break;

		cryptConf->minCrypt32Ver = strdup(value);

		VSPM_FreeItem(tmpItem, &rc);
		tmpItem = NULL;
		VSPM_FreeString((char *)value, &rc);
		value = NULL;

		/* Determine the _VSPM_CRYPT_CONFIG.checkEnhanced field */
		tmpItem = VSPM_GetItemByName(tmpCnt, VSPM_CHECK_ENHANCED, &rc);
		if (rc != VSPM_STATUS_NO_ERROR)
			break;

		value = (const char *) VSPM_GetValue(tmpItem, &rc);
		if (rc != VSPM_STATUS_NO_ERROR)
			break;

		if (strstr(value, TRUE_VAL) != NULL) {
			cryptConf->checkEnhanced = VSPM_TRUE;
		}
		else {
			cryptConf->checkEnhanced = VSPM_FALSE;
		}

		VSPM_FreeContainer(tmpCnt, &rc);
		tmpCnt = NULL;
		VSPM_FreeItem(tmpItem, &rc);
		tmpItem = NULL;
		VSPM_FreeString((char *)value, &rc);
		value = NULL;

	} while (0);

	if (status != NULL)
	*status = rc;

	if (cryptConf && (rc != VSPM_STATUS_NO_ERROR)) {
		VSPM_FreeCryptConfig((VSPM_CRYPT_CONFIG) cryptConf, &rc);
		cryptConf = NULL;
	}

	if (enrollCnt)
		VSPM_FreeContainer(enrollCnt, &rc);

	if (tmpCnt)
		VSPM_FreeContainer(tmpCnt, &rc);

	if (tmpItem)
		VSPM_FreeItem(tmpItem, &rc);

	if (value)
		VSPM_FreeString((char *)value, &rc);

	return (VSPM_CRYPT_CONFIG) cryptConf;

}


/* This function returns the email address for support issue during
 * the enrollment process
 *
 *   pmd      - IN  - the descriptor of the policy description file
 *   status   - OUT - status code
 *   RETURNS  - an rfc822 email address or
 *              NULL if an error is encountered
 *
 */

VSPM_EXPORT const char *
        VSPM_GetHelpEmail (
                VSPM_Descriptor pmd,
                VSPM_STATUS *status) {

	VSPM_STATUS rc = VSPM_STATUS_NO_ERROR;
	VSPM_Container tmpCnt = NULL;
	VSPM_Item tmpItem = NULL;
	const char * helpEmail = NULL;

	do {

		tmpCnt = VSPM_GetContainerByNameFromDescriptor(pmd, VSPM_GLOBALVAR_CONTAINER, &rc);
		if (rc != VSPM_STATUS_NO_ERROR)
			break;

		tmpItem = VSPM_GetItemByName(tmpCnt, VSPM_HELP_EMAIL, &rc);
		if (rc != VSPM_STATUS_NO_ERROR)
			break;

		helpEmail = (const char *) VSPM_GetValue(tmpItem, &rc);
		if (rc != VSPM_STATUS_NO_ERROR)
			break;

	} while (0);

	if (status != NULL)
	*status = rc;

	if (tmpCnt)
		VSPM_FreeContainer(tmpCnt, &rc);

	if (tmpItem)
		VSPM_FreeItem(tmpItem, &rc);

	return helpEmail; 
}


/* This function returns the URL for CRS enrollment
 *
 *   pmd      - IN  - the descriptor of the policy description file
 *   protocol - OUT - The OnSite CRS enrollment transport protocol
 *   hostName - OUT - The OnSite CRS enrollment host name
 *   portNumber - OUT - The OnSite CRS enrollment port number
 *   crsURI - OUT - The OnSite CRS enrollment responder path name
 *   status   - OUT - status code
 *
 */

VSPM_EXPORT void
        VSPM_GetCRSEnrollmentURL (
                VSPM_Descriptor pmd,
                const char** protocol, 
                const char** hostName, 
                const char** portNumber, 
                const char** crsURI, 
                VSPM_STATUS *status) {

	VSPM_STATUS rc = VSPM_STATUS_NO_ERROR;
	VSPM_Container tmpCnt = NULL;
	VSPM_Item tmpItem = NULL;
	const char * crsUrl = NULL;
	char * value = NULL;
	char * ptr = NULL;
	char * ptr1 = NULL;
	int len = 0;

	do {

		tmpCnt = VSPM_GetContainerByNameFromDescriptor(pmd, VSPM_GLOBALVAR_CONTAINER, &rc);
		if (rc != VSPM_STATUS_NO_ERROR)
			break;

		tmpItem = VSPM_GetItemByName(tmpCnt, VSPM_CRS_URL, &rc);
		if (rc != VSPM_STATUS_NO_ERROR)
			break;

		crsUrl = (const char *) VSPM_GetValue(tmpItem, &rc);
		if (rc != VSPM_STATUS_NO_ERROR)
			break;

		/* protocol */
		ptr = (char *)strstr(crsUrl, "://");
		if (!ptr) {
			rc = VSPM_INVALID_CRS_URL;
			break;
		}

		len = strlen(crsUrl) - strlen(ptr);
		value = (char *)malloc(len + 1);
		if (!value) {
			rc = VSPM_OUT_OF_MEMORY;
			break;
		}
		memset(value, 0, len + 1);
		strncpy(value, crsUrl, len);

		*protocol = (const char *) value;

		/* hostname and port number */
		ptr += 3;
		ptr1 = strchr(ptr, ':');
		if (!ptr1) {
			ptr1 = strchr(ptr, '/');
			len = strlen(ptr) - strlen(ptr1);
			value = (char *) malloc(len + 1);
			if (!value) {
				rc = VSPM_OUT_OF_MEMORY;
				break;
			}
			memset(value, 0, len + 1);
			strncpy(value, ptr, len);

			*hostName = (const char *)value;

			value = (char *) malloc(4);
			if (!value) {
				rc = VSPM_OUT_OF_MEMORY;
				break;
			}
			memset(value, 0, 4);

			/* a bit cheating here: use strlen test to see if it is https or http */

			if (strlen(*protocol) > 4) {
				strcpy(value, "443");
			}
			else {
				strcpy(value, "80");
			}

			*portNumber = (const char *)value;

			ptr = ptr1;

		}
		else {
			len = strlen(ptr) - strlen(ptr1);
			value = (char *) malloc(len + 1);
			if (!value) {
				rc = VSPM_OUT_OF_MEMORY;
				break;
			}
			memset(value, 0, len + 1);
			strncpy(value, ptr, len);

			*hostName = (const char *)value;

			ptr = ptr1 + 1;
			ptr1 = strchr(ptr, '/');
			len = strlen(ptr) - strlen(ptr1);
			value = (char *) malloc(len + 1);
			if (!value) {
				rc = VSPM_OUT_OF_MEMORY;
				break;
			}
			memset(value, 0, len + 1);

			strncpy(value, ptr, len);

			*portNumber = (const char *) value;

			ptr = ptr1;

		}

		/* finally, the crs uri */
		len = strlen(ptr);
		value = (char *) malloc(len + 1);
		if (!value) {
			rc = VSPM_OUT_OF_MEMORY;
			break;
		}
		memset(value, 0, len + 1);

		strcpy(value, ptr);

		*crsURI = value;

	} while (0);

	if (status != NULL)
	*status = rc;

	if (crsUrl)
		VSPM_FreeString((char *)crsUrl, &rc);

	if (tmpCnt)
		VSPM_FreeContainer(tmpCnt, &rc);

	if (tmpItem)
		VSPM_FreeItem(tmpItem, &rc);

}


/* This function returns the URL for enrollment
 *
 *   pmd      - IN  - the descriptor of the policy description file
 *   protocol - OUT - The OnSite enrollment transport protocol
 *   hostName - OUT - The OnSite enrollment host name
 *   portNumber - OUT - The OnSite enrollment port number
 *   cgiURI - OUT - The OnSite enrollment responder path name
 *   status   - OUT - status code
 *
 */

VSPM_EXPORT void
        VSPM_GetEnrollmentURL (
                VSPM_Descriptor pmd,
                const char** protocol, 
                const char** hostName, 
                const char** portNumber, 
                const char** cgiURI, 
                VSPM_STATUS *status) {

	VSPM_STATUS rc = VSPM_STATUS_NO_ERROR;
	VSPM_Container tmpCnt = NULL;
	VSPM_Item vsHostItem = NULL;
	VSPM_Item remoteHostItem = NULL;
	VSPM_Item lhItem = NULL;
	VSPM_BOOL isLocalHost = VSPM_FALSE;
	const char * remoteHostUrl = NULL;
	const char * vsHostUrl = NULL;
	char * value = NULL;
	char * ptr = NULL;
	char * ptr1 = NULL;
	int len = 0;

	do {

		tmpCnt = VSPM_GetContainerByNameFromDescriptor(pmd, VSPM_GLOBALVAR_CONTAINER, &rc);
		if (rc != VSPM_STATUS_NO_ERROR)
			break;

		remoteHostItem = VSPM_GetItemByName(tmpCnt, VSPM_REMOTE_HOST, &rc);
		if (rc != VSPM_STATUS_NO_ERROR)
			break;

		remoteHostUrl = (const char *) VSPM_GetValue(remoteHostItem, &rc);
		if (rc != VSPM_STATUS_NO_ERROR)
			break;

		vsHostItem = VSPM_GetItemByName(tmpCnt, VSPM_VS_HOST, &rc);
		if (rc != VSPM_STATUS_NO_ERROR)
			break;

		vsHostUrl = (const char *) VSPM_GetValue(vsHostItem, &rc);
		if (rc != VSPM_STATUS_NO_ERROR)
			break;

		/* protocol */
		ptr = (char *)strstr(remoteHostUrl, "://");
		if (!ptr) {
			rc = VSPM_INVALID_ENROLLMENT_URL;
			break;
		}

		len = strlen(remoteHostUrl) - strlen(ptr);
		value = (char *)malloc(len + 1);
		if (!value) {
			rc = VSPM_OUT_OF_MEMORY;
			break;
		}
		memset(value, 0, len + 1);
		strncpy(value, remoteHostUrl, len);

		*protocol = (const char *) value;

		/* hostname and port number */
		ptr += 3;
		ptr1 = strchr(ptr, ':');
		if (!ptr1) {
			ptr1 = strchr(ptr, '/');
			if (ptr1 != NULL)
				len = strlen(ptr) - strlen(ptr1);
			else {
				len = strlen(ptr);
				ptr1 = ptr + len;
			}

			value = (char *) malloc(len + 1);
			if (!value) {
				rc = VSPM_OUT_OF_MEMORY;
				break;
			}
			memset(value, 0, len + 1);
			strncpy(value, ptr, len);

			*hostName = (const char *)value;

			/* if the remoteHost hostname is not the same as */
			/* the one in vsHost, it is locally hosted */
			if (strstr(vsHostUrl, value) == NULL) {
				isLocalHost = VSPM_TRUE;
			}

			value = (char *) malloc(4);
			if (!value) {
				rc = VSPM_OUT_OF_MEMORY;
				break;
			}
			memset(value, 0, 4);

			/* a bit cheating here: use strlen test to see if it is https or http */

			if (strlen(*protocol) > 4) {
				strcpy(value, "443");
			}
			else {
				strcpy(value, "80");
			}

			*portNumber = (const char *)value;

			ptr = ptr1;

		}
		else {
			len = strlen(ptr) - strlen(ptr1);
			value = (char *) malloc(len + 1);
			if (!value) {
				rc = VSPM_OUT_OF_MEMORY;
				break;
			}
			memset(value, 0, len + 1);
			strncpy(value, ptr, len);

			*hostName = (const char *)value;

			if (strstr(vsHostUrl, value) == NULL) {
				isLocalHost = VSPM_TRUE;
			}

			ptr = ptr1 + 1;
			ptr1 = strchr(ptr, '/');
			if (ptr1 != NULL)
				len = strlen(ptr) - strlen(ptr1);
			else {
				len = strlen(ptr);
				ptr1 = ptr + len;
			}

			value = (char *) malloc(len + 1);
			if (!value) {
				rc = VSPM_OUT_OF_MEMORY;
				break;
			}
			memset(value, 0, len + 1);

			strncpy(value, ptr, len);

			*portNumber = (const char *) value;

			ptr = ptr1;

		}

		/* finally, the cgi uri */
		if (isLocalHost == VSPM_TRUE) {
			len = strlen(ptr) + strlen(SOPHIALITE_PATH);
		}
		else {
			len = strlen(ptr) + strlen(vsHostUrl) + strlen(SOPHIA_PATH);
		}

		value = (char *) malloc(len + 1);
		if (!value) {
			rc = VSPM_OUT_OF_MEMORY;
			break;
		}
		memset(value, 0, len + 1);

		if (isLocalHost == VSPM_TRUE) {
			if (strlen(ptr) > 0)
				strcpy(value, ptr);
		} else {
			ptr = ((char *) vsHostUrl) + strlen(*hostName);
			if (*ptr == ':')
			  ptr = strstr(ptr, "/");
			if (ptr != NULL)
			  strcat (value, ptr);
		}

		if (isLocalHost == VSPM_TRUE)
			strcat(value, SOPHIALITE_PATH);
		else
			strcat(value, SOPHIA_PATH);

		*cgiURI = value;

	} while (0);

	if (status != NULL)
	*status = rc;

	if (remoteHostUrl)
		VSPM_FreeString((char *)remoteHostUrl, &rc);

	if (vsHostUrl)
		VSPM_FreeString((char *)vsHostUrl, &rc);

	if (tmpCnt)
		VSPM_FreeContainer(tmpCnt, &rc);

	if (remoteHostItem)
		VSPM_FreeItem(remoteHostItem, &rc);

	if (vsHostItem)
		VSPM_FreeItem(vsHostItem, &rc);

}


/* This function returns the number of days before the certificate expiration date 
 * the subscriber should be reminded to renew the certificate
 *
 *   pmd      - IN  - the descriptor of the policy description file
 *   status   - OUT - status code
 *   RETURNS  - number of days before the certificate expiration date
 *
 */

VSPM_EXPORT unsigned short
        VSPM_GetCertExpireWindow (
                VSPM_Descriptor pmd,
                VSPM_STATUS *status) {

	VSPM_STATUS rc = VSPM_STATUS_NO_ERROR;
	VSPM_Container tmpCnt = NULL;
	VSPM_Item tmpItem = NULL;
	const char * value = NULL;
	unsigned short expWindow = 0;

	do {

		tmpCnt = VSPM_GetContainerByNameFromDescriptor(pmd, VSPM_GLOBALVAR_CONTAINER, &rc);
		if (rc != VSPM_STATUS_NO_ERROR)
			break;

		tmpItem = VSPM_GetItemByName(tmpCnt, VSPM_EXPIRATION_WINDOW, &rc);
		if (rc != VSPM_STATUS_NO_ERROR)
			break;

		value = (const char *) VSPM_GetValue(tmpItem, &rc);
		if (rc != VSPM_STATUS_NO_ERROR)
			break;

		expWindow = (unsigned short) atoi(value);

	} while (0);

	if (status != NULL)
	*status = rc;

	if (tmpCnt)
		VSPM_FreeContainer(tmpCnt, &rc);

	if (tmpItem)
		VSPM_FreeItem(tmpItem, &rc);
	
	if (value)
		VSPM_FreeString((char *)value, &rc);

	return expWindow;
}


/* This function returns the key manager configuration tag
 *
 *   pmd      - IN  - the descriptor of the policy description file
 *   status   - OUT - status code
 *   RETURNS  - VSPM_KEY_MANAGER_TAG
 *
 */

VSPM_EXPORT VSPM_KEY_MANAGER_TAG
        VSPM_GetKeyManagerTag (
                VSPM_Descriptor pmd,
                VSPM_STATUS *status) {

	VSPM_STATUS rc = VSPM_STATUS_NO_ERROR;
	VSPM_Container tmpCnt = NULL;
	VSPM_Item tmpItem = NULL;
	const char * value = NULL;
	VSPM_KEY_MANAGER_TAG kmTag = VSPM_NO_KEY_MANAGER;

	do {

		tmpCnt = VSPM_GetContainerByNameFromDescriptor(pmd, VSPM_APP_KEY_MANAGER_CONTAINER, &rc);
		if (rc != VSPM_STATUS_NO_ERROR)
			break;

		tmpItem = VSPM_GetItemByName(tmpCnt, VSPM_POLICY_VALUE, &rc);
		if (rc != VSPM_STATUS_NO_ERROR)
			break;

		value = (const char *) VSPM_GetValue(tmpItem, &rc);
		if (rc != VSPM_STATUS_NO_ERROR)
			break;

		if (strstr(value, SINGLE) != NULL) {
			kmTag = VSPM_SINGLE_KEY;
		}
		else if (strstr(value, DUAL) != NULL) {
			kmTag = VSPM_DUAL_KEY;
		}

	} while (0);

	if (status != NULL)
	*status = rc;

	if (tmpCnt)
		VSPM_FreeContainer(tmpCnt, &rc);

	if (tmpItem)
		VSPM_FreeItem(tmpItem, &rc);
	
	if (value)
		VSPM_FreeString((char *)value, &rc);

	return kmTag;

}

/* This function returns the authentication scheme configuration tag
 *
 *   pmd      - IN  - the descriptor of the policy description file
 *   status   - OUT - status code
 *   RETURNS  - VSPM_AUTH_SCHEME_TAG
 *
 */

VSPM_EXPORT VSPM_AUTH_SCHEME_TAG
        VSPM_GetAuthSchemeTag (
                VSPM_Descriptor pmd,
                VSPM_STATUS *status) {

	VSPM_STATUS rc = VSPM_STATUS_NO_ERROR;
	VSPM_Container tmpCnt = NULL;
	VSPM_Item tmpItem = NULL;
	const char * value = NULL;
	VSPM_AUTH_SCHEME_TAG authTag = VSPM_MANUAL_AUTH;

	do {

		tmpCnt = VSPM_GetContainerByNameFromDescriptor(pmd, VSPM_MODE_CONTAINER, &rc);
		if (rc != VSPM_STATUS_NO_ERROR)
			break;

		tmpItem = VSPM_GetItemByName(tmpCnt, VSPM_POLICY_VALUE, &rc);
		if (rc != VSPM_STATUS_NO_ERROR)
			break;

		value = (const char *) VSPM_GetValue(tmpItem, &rc);
		if (rc != VSPM_STATUS_NO_ERROR)
			break;

		if (strstr(value, AUTOAUTH_VAL) != NULL) {
			authTag = VSPM_AUTO_AUTH;
		}
		else {
			authTag = VSPM_MANUAL_AUTH;
		}

	} while (0);

	if (status != NULL)
	*status = rc;

	if (tmpCnt)
		VSPM_FreeContainer(tmpCnt, &rc);

	if (tmpItem)
		VSPM_FreeItem(tmpItem, &rc);
	
	if (value)
		VSPM_FreeString((char *)value, &rc);

	return authTag;

}

/* This function returns the field processing type of the certificate enrollment
 * parameter
 *
 *   param    - IN  - the reference to VSPM_PARAMETER
 *   RETURNS  - VSPM_FIELD_PROCESSING_TYPE
 *
 */

VSPM_EXPORT VSPM_FIELD_PROCESSING_TYPE
        VSPM_GetFieldProcessingType (
                VSPM_PARAMETER param,
				VSPM_STATUS *status ) {

	_VSPM_PARAMETER * _param = (_VSPM_PARAMETER *) param;
	VSPM_FIELD_PROCESSING_TYPE type = VSPM_USER_INPUT_FIELD;

	do {

		if (! _param) {
			if (status != NULL)
			*status = VSPM_INVALID_DESCRIPTOR;
			break;
		}

		type = _param->fieldType;
		if (status != NULL)
		*status = VSPM_STATUS_NO_ERROR;

	} while (0);

	return type;
}


/* This function returns the display name of the certificate enrollment
 * parameter
 *
 *   param    - IN  - the reference to VSPM_PARAMETER
 *   RETURNS  - null terminated string
 *
 */

VSPM_EXPORT const char *
        VSPM_GetDisplayName (
                VSPM_PARAMETER param,
				VSPM_STATUS *status ) {

	_VSPM_PARAMETER * _param = (_VSPM_PARAMETER *) param;
	const char * name = NULL;

	do {

		if (! _param) {
			if (status != NULL)
			*status = VSPM_INVALID_DESCRIPTOR;
			break;
		}

		name = strdup(_param->displayName);
		if (!name) {
			if (status != NULL)
			*status = VSPM_OUT_OF_MEMORY;
		}
		else {
			if (status != NULL)
			*status = VSPM_STATUS_NO_ERROR;
		}

	} while (0);

	return name;
}


/* This function returns the internal name of the certificate enrollment
 * parameter
 *
 *   param    - IN  - the reference to VSPM_PARAMETER
 *   RETURNS  - null terminated string
 *
 */

VSPM_EXPORT const char *
        VSPM_GetInternalName (
                VSPM_PARAMETER param,
				VSPM_STATUS *status ) {

	_VSPM_PARAMETER * _param = (_VSPM_PARAMETER *) param;
	const char * name = NULL;

	do {

		if (! _param) {
			if (status != NULL)
			*status = VSPM_INVALID_DESCRIPTOR;
			break;
		}

		name = strdup(_param->internalName);
		if (!name) {
			if (status != NULL)
			*status = VSPM_OUT_OF_MEMORY;
		}
		else {
			if (status != NULL)
			*status = VSPM_STATUS_NO_ERROR;
		}

	} while (0);

	return name;
}


/* This function returns the value of the certificate enrollment
 * parameter. Applicable only if the processing type is
 * VSPM_HARD_CODED_FIELD
 *
 *   param    - IN  - the reference to VSPM_PARAMETER
 *   RETURNS  - null terminated string
 *
 */

VSPM_EXPORT const char *
        VSPM_GetParamValue (
                VSPM_PARAMETER param,
				VSPM_STATUS *status ) {

	_VSPM_PARAMETER * _param = (_VSPM_PARAMETER *) param;
	const char * value = NULL;

	do {

		if (! _param) {
			if (status != NULL)
			*status = VSPM_INVALID_DESCRIPTOR;
			break;
		}

		if (status != NULL)
		*status = VSPM_STATUS_NO_ERROR;
		if (_param->fieldType == VSPM_HARD_CODED_FIELD) {
			value = strdup(_param->value);
			if (!value) {
				if (status != NULL)
				*status = VSPM_OUT_OF_MEMORY;
			}
		}

	} while (0);

	return value;
}


/* This function returns the value tag of the certificate enrollment
 * parameter.
 *
 *   param    - IN  - the reference to VSPM_PARAMETER
 *   RETURNS  - VSPM_VALUE_TAG
 *
 */

VSPM_EXPORT VSPM_VALUE_TAG
        VSPM_GetValueTag (
                VSPM_PARAMETER param,
				VSPM_STATUS *status ) {

	_VSPM_PARAMETER * _param = (_VSPM_PARAMETER *) param;
	VSPM_VALUE_TAG tag = VSPM_VALUE_TEXT;

	do {

		if (! _param) {
			if (status != NULL)
			*status = VSPM_INVALID_DESCRIPTOR;
			break;
		}

		tag = _param->tag;
		if (status != NULL)
		*status = VSPM_STATUS_NO_ERROR;

	} while (0);

	return tag;
}


/* This function returns the field requirement of the certificate enrollment
 * parameter.
 *
 *   param    - IN  - the reference to VSPM_PARAMETER
 *   RETURNS  - VSPM_REQUIREMENT
 *
 */

VSPM_EXPORT VSPM_REQUIREMENT
        VSPM_GetRequirement (
                VSPM_PARAMETER param,
				VSPM_STATUS *status ) {

	_VSPM_PARAMETER * _param = (_VSPM_PARAMETER *) param;
	VSPM_REQUIREMENT req = VSPM_REQ_OPTIONAL;

	do {

		if (! _param) {
			if (status != NULL)
			*status = VSPM_INVALID_DESCRIPTOR;
			break;
		}

		req = _param->req;
		if (status != NULL)
		*status = VSPM_STATUS_NO_ERROR;

	} while (0);

	return req;
}


/* This function returns the minimum length in character
 * of the certificate enrollment parameter.
 *
 *   param    - IN  - the reference to VSPM_PARAMETER
 *   RETURNS  - minimum length in number of characters
 *
 */

VSPM_EXPORT unsigned short
        VSPM_GetMinLen (
                VSPM_PARAMETER param,
				VSPM_STATUS *status ) {

	_VSPM_PARAMETER * _param = (_VSPM_PARAMETER *) param;
	unsigned short len = 0;

	do {

		if (! _param) {
			if (status != NULL)
			*status = VSPM_INVALID_DESCRIPTOR;
			break;
		}

		len = _param->minLen;
		if (status != NULL)
		*status = VSPM_STATUS_NO_ERROR;

	} while (0);

	return len;
}


/* This function returns the maximum length in character
 * of the certificate enrollment parameter.
 *
 *   param    - IN  - the reference to VSPM_PARAMETER
 *   RETURNS  - maximum length in number of characters
 *
 */

VSPM_EXPORT unsigned short
        VSPM_GetMaxLen (
                VSPM_PARAMETER param,
				VSPM_STATUS *status ) {

	_VSPM_PARAMETER * _param = (_VSPM_PARAMETER *) param;
	unsigned short len = 0;

	do {

		if (! _param) {
			if (status != NULL)
			*status = VSPM_INVALID_DESCRIPTOR;
			break;
		}

		len = _param->maxLen;
		if (status != NULL)
		*status = VSPM_STATUS_NO_ERROR;

	} while (0);

	return len;
}


/* This function returns the default/preferred CSP from
 * cryptographic policy
 *
 *   cryptConf - IN  - the reference to VSPM_CRYPT_CONFIG
 *   RETURNS   - null terminated string
 *
 */

VSPM_EXPORT const char *
        VSPM_GetCSP (
                VSPM_CRYPT_CONFIG cryptConf,
				VSPM_STATUS *status ) {

	_VSPM_CRYPT_CONFIG * _cryptConf = (_VSPM_CRYPT_CONFIG *) cryptConf;
	const char *csp = NULL;

	do {

		if (! _cryptConf) {
			if (status != NULL)
			*status = VSPM_INVALID_DESCRIPTOR;
			break;
		}

		if (status != NULL)
		*status = VSPM_STATUS_NO_ERROR;

		csp = strdup(_cryptConf->prefCSP);
		if (!csp) {
			if (status != NULL)
			*status = VSPM_OUT_OF_MEMORY;
		}

	} while (0);

	return csp;
}


/* This function returns whether the CSP is user selectable 
 *
 *   cryptConf - IN  - the reference to VSPM_CRYPT_CONFIG
 *   RETURNS   - VSPM_FALSE or VSPM_TRUE
 *
 */

VSPM_EXPORT VSPM_BOOL
        VSPM_IsCSPUserSelectable (
                VSPM_CRYPT_CONFIG cryptConf,
				VSPM_STATUS *status ) {

	_VSPM_CRYPT_CONFIG * _cryptConf = (_VSPM_CRYPT_CONFIG *) cryptConf;
	VSPM_BOOL isUserSelectable = VSPM_FALSE;

	do {

		if (! _cryptConf) {
			if (status != NULL)
			*status = VSPM_INVALID_DESCRIPTOR;
			break;
		}

		if (status != NULL)
		*status = VSPM_STATUS_NO_ERROR;

		isUserSelectable = _cryptConf->isCSPUserSelectable;

	} while (0);

	return isUserSelectable;
}


/* This function returns whether an application should check for
 * the existence of enhanced cryptographic provider
 *
 *   cryptConf - IN  - the reference to VSPM_CRYPT_CONFIG
 *   RETURNS   - VSPM_FALSE or VSPM_TRUE
 *
 */

VSPM_EXPORT VSPM_BOOL
        VSPM_CheckEnhancedProvider (
                VSPM_CRYPT_CONFIG cryptConf,
				VSPM_STATUS *status ) {

	_VSPM_CRYPT_CONFIG * _cryptConf = (_VSPM_CRYPT_CONFIG *) cryptConf;
	VSPM_BOOL checkEnhanced = VSPM_FALSE;

	do {

		if (! _cryptConf) {
			if (status != NULL)
			*status = VSPM_INVALID_DESCRIPTOR;
			break;
		}

		if (status != NULL)
		*status = VSPM_STATUS_NO_ERROR;

		checkEnhanced = _cryptConf->checkEnhanced;

	} while (0);

	return checkEnhanced;
}


/* This function returns whether an application allow key
 * pairs to be exported
 *
 *   cryptConf - IN  - the reference to VSPM_CRYPT_CONFIG
 *   RETURNS   - VSPM_FALSE or VSPM_TRUE
 *
 */

VSPM_EXPORT VSPM_BOOL
        VSPM_IsKeyExportable (
                VSPM_CRYPT_CONFIG cryptConf,
				VSPM_STATUS *status ) {

	_VSPM_CRYPT_CONFIG * _cryptConf = (_VSPM_CRYPT_CONFIG *) cryptConf;
	VSPM_BOOL isKeyExportable = VSPM_FALSE;

	do {

		if (! _cryptConf) {
			if (status != NULL)
			*status = VSPM_INVALID_DESCRIPTOR;
			break;
		}

		if (status != NULL)
		*status = VSPM_STATUS_NO_ERROR;

		isKeyExportable = _cryptConf->isKeyExportable;

	} while (0);

	return isKeyExportable;
}


/* This function returns whether an application allows the subscriber to
 * decide whether or not to enable key protection
 *
 *   cryptConf - IN  - the reference to VSPM_CRYPT_CONFIG
 *   RETURNS   - VSPM_FALSE or VSPM_TRUE
 *
 */

VSPM_EXPORT VSPM_BOOL
        VSPM_IsKeyProtectionUserSelectable (
                VSPM_CRYPT_CONFIG cryptConf,
				VSPM_STATUS *status ) {

	_VSPM_CRYPT_CONFIG * _cryptConf = (_VSPM_CRYPT_CONFIG *) cryptConf;
	VSPM_BOOL isKeyProtectionUserSelectable = VSPM_FALSE;

	do {

		if (! _cryptConf) {
			if (status != NULL)
			*status = VSPM_INVALID_DESCRIPTOR;
			break;
		}

		if (status != NULL)
		*status = VSPM_STATUS_NO_ERROR;

		isKeyProtectionUserSelectable = _cryptConf->isKeyProtectionUserSelectable;

	} while (0);

	return isKeyProtectionUserSelectable;
}


/* This function returns whether the private key should be protected
 *
 *   cryptConf - IN  - the reference to VSPM_CRYPT_CONFIG
 *   RETURNS   - VSPM_FALSE or VSPM_TRUE
 *
 */

VSPM_EXPORT VSPM_BOOL
        VSPM_IsKeyProtected (
                VSPM_CRYPT_CONFIG cryptConf,
				VSPM_STATUS *status ) {

	_VSPM_CRYPT_CONFIG * _cryptConf = (_VSPM_CRYPT_CONFIG *) cryptConf;
	VSPM_BOOL isKeyProtected = VSPM_FALSE;

	do {

		if (! _cryptConf) {
			if (status != NULL)
			*status = VSPM_INVALID_DESCRIPTOR;
			break;
		}

		if (status != NULL)
		*status = VSPM_STATUS_NO_ERROR;

		isKeyProtected = _cryptConf->isKeyProtected;

	} while (0);

	return isKeyProtected;
}


/* This function returns the size of the key
 *
 *   cryptConf - IN  - the reference to VSPM_CRYPT_CONFIG
 *   RETURNS   - the number of bits for the key
 *
 */

VSPM_EXPORT unsigned short
        VSPM_GetKeyLength (
                VSPM_CRYPT_CONFIG cryptConf,
				VSPM_STATUS *status ) {

	_VSPM_CRYPT_CONFIG * _cryptConf = (_VSPM_CRYPT_CONFIG *) cryptConf;
	unsigned short keyLength = 0;

	do {

		if (! _cryptConf) {
			if (status != NULL)
			*status = VSPM_INVALID_DESCRIPTOR;
			break;
		}

		if (status != NULL)
		*status = VSPM_STATUS_NO_ERROR;

		keyLength = _cryptConf->keyLength;

	} while (0);

	return keyLength;
}


/* This function returns whether an application allows key size to be
 * degraded if the one returned by VSPM_GetKeyLength() is not available
 *
 *   cryptConf - IN  - the reference to VSPM_CRYPT_CONFIG
 *   RETURNS   - VSPM_FALSE or VSPM_TRUE
 *
 */

VSPM_EXPORT VSPM_BOOL
        VSPM_IsKeyLengthDegradable (
                VSPM_CRYPT_CONFIG cryptConf,
				VSPM_STATUS *status ) {

	_VSPM_CRYPT_CONFIG * _cryptConf = (_VSPM_CRYPT_CONFIG *) cryptConf;
	VSPM_BOOL isKeyLengthDegradable = VSPM_FALSE;

	do {

		if (! _cryptConf) {
			if (status != NULL)
			*status = VSPM_INVALID_DESCRIPTOR;
			break;
		}

		if (status != NULL)
		*status = VSPM_STATUS_NO_ERROR;

		isKeyLengthDegradable = _cryptConf->isKeyLengthDegradable;

	} while (0);

	return isKeyLengthDegradable;
}


/* This function returns the minimum version required for ADVAPI32
 *
 *   cryptConf - IN  - the reference to VSPM_CRYPT_CONFIG
 *   RETURNS   - the version string
 *
 */

VSPM_EXPORT const char *
        VSPM_GetMinAdvapi32Ver (
                VSPM_CRYPT_CONFIG cryptConf,
				VSPM_STATUS *status ) {

	_VSPM_CRYPT_CONFIG * _cryptConf = (_VSPM_CRYPT_CONFIG *) cryptConf;
	const char *minAdvapi32Ver = NULL;

	do {

		if (! _cryptConf) {
			if (status != NULL)
			*status = VSPM_INVALID_DESCRIPTOR;
			break;
		}

		if (status != NULL)
		*status = VSPM_STATUS_NO_ERROR;

		minAdvapi32Ver = strdup(_cryptConf->minAdvapi32Ver);
		if (!minAdvapi32Ver) {
			if (status != NULL)
			*status = VSPM_OUT_OF_MEMORY;
		}

	} while (0);

	return minAdvapi32Ver;
}


/* This function returns the minimum version required for CRYPT32
 *
 *   cryptConf - IN  - the reference to VSPM_CRYPT_CONFIG
 *   RETURNS   - the version string
 *
 */

VSPM_EXPORT const char *
        VSPM_GetMinCrypt32Ver (
                VSPM_CRYPT_CONFIG cryptConf,
				VSPM_STATUS *status ) {

	_VSPM_CRYPT_CONFIG * _cryptConf = (_VSPM_CRYPT_CONFIG *) cryptConf;
	const char *minCrypt32Ver = NULL;

	do {

		if (! _cryptConf) {
			if (status != NULL)
			*status = VSPM_INVALID_DESCRIPTOR;
			break;
		}

		if (status != NULL)
		*status = VSPM_STATUS_NO_ERROR;

		minCrypt32Ver = strdup(_cryptConf->minCrypt32Ver);
		if (!minCrypt32Ver) {
			if (status != NULL)
			*status = VSPM_OUT_OF_MEMORY;
		}

	} while (0);

	return minCrypt32Ver;
}


/* This function returns the issuer's DN using the rfc 1779 format for a
 * given product type
 *
 *   pmd      - IN  - the descriptor of the policy description file
 *   prodType - IN  - the product type of the enrollment policy
 *   status   - OUT - if the function returns NULL, the return status indicates the
 *                    failure reason
 *   RETURNS  - issuer DN string
 *
 */

VSPM_EXPORT const char *
        VSPM_GetCertIssuerDN (
                VSPM_Descriptor pmd,
				VSPM_PRODUCT_TAG prodType,
                VSPM_STATUS *status) {
	
	VSPM_STATUS rc = VSPM_STATUS_NO_ERROR;
	VSPM_Container tmpCnt = NULL;
	VSPM_Item tmpItem = NULL;
	const char * value = NULL;

	if (prodType != VSPM_END_USER) {
		if (status != NULL)
		*status = VSPM_NOT_SUPPORTED_FEATURE;
		return NULL;
	}

	do {

		tmpCnt = VSPM_GetContainerByNameFromDescriptor(pmd, VSPM_GLOBALVAR_CONTAINER, &rc);
		if (rc != VSPM_STATUS_NO_ERROR)
			break;

		tmpItem = VSPM_GetItemByName(tmpCnt, VSPM_ISSUER_DN, &rc);
		if (rc != VSPM_STATUS_NO_ERROR)
			break;

		value = (const char *) VSPM_GetValue(tmpItem, &rc);
		if (rc != VSPM_STATUS_NO_ERROR)
			break;

	} while (0);

	if (status != NULL)
	*status = rc;

	if (tmpCnt)
		VSPM_FreeContainer(tmpCnt, &rc);

	if (tmpItem)
		VSPM_FreeItem(tmpItem, &rc);

	return value;

}


/* This function returns the template to format the subject DN
 * using the rfc 1779 format for a given product type
 *
 *   pmd      - IN  - the descriptor of the policy description file
 *   prodType - IN  - the product type of the enrollment policy
 *   status   - OUT - if the function returns NULL, the return status indicates the
 *                    failure reason
 *   RETURNS  - subject DN template string
 *
 */

VSPM_EXPORT const char *
        VSPM_GetCertSubjectDNTemplate (
                VSPM_Descriptor pmd,
				VSPM_PRODUCT_TAG prodType,
                VSPM_STATUS *status) {
	
	VSPM_STATUS rc = VSPM_STATUS_NO_ERROR;
	VSPM_Container tmpCnt = NULL;
	VSPM_Item tmpItem = NULL;
	const char * value = NULL;

	if (prodType != VSPM_END_USER) {
		if (status != NULL)
		*status = VSPM_NOT_SUPPORTED_FEATURE;
		return NULL;
	}

	do {

		tmpCnt = VSPM_GetContainerByNameFromDescriptor(pmd, VSPM_USER_ENROLLMENT_CONTAINER, &rc);
		if (rc != VSPM_STATUS_NO_ERROR)
			break;

		tmpItem = VSPM_GetItemByName(tmpCnt, VSPM_SUBJECT_DN_TEMPLATE, &rc);
		if (rc != VSPM_STATUS_NO_ERROR)
			break;

		value = (const char *) VSPM_GetValue(tmpItem, &rc);
		if (rc != VSPM_STATUS_NO_ERROR)
			break;

	} while (0);

	if (status != NULL)
	*status = rc;

	if (tmpCnt)
		VSPM_FreeContainer(tmpCnt, &rc);

	if (tmpItem)
		VSPM_FreeItem(tmpItem, &rc);

	return value;

}


/* This function returns the issuer's certificate in binary X.509 format
 *
 *   pmd      - IN  - the descriptor of the policy description file
 *   prodType - IN  - the product type of the enrollment policy
 *   issuerIndex - IN - issuer's index in the certificate chain.
 *                      (Note: It has to be 0 for this release)
 *   certBuf  - OUT - issuer's X.509 certificate in binary format
 *   certSize - OUT - the size of certBuf
 *   status   - OUT - if the function returns NULL, the return status indicates the
 *                    failure reason
 *
 */

VSPM_EXPORT void
        VSPM_GetCertIssuerChain (
                VSPM_Descriptor pmd,
				VSPM_PRODUCT_TAG prodType,
				unsigned int issuerIndex,
				char ** certBuf,
				unsigned int * certSize,
                VSPM_STATUS *status) {
	
	VSPM_STATUS rc = VSPM_STATUS_NO_ERROR;
	VSPM_Container tmpCnt = NULL;
	VSPM_Item tmpItem = NULL;
	const char * value = NULL;

	if (prodType != VSPM_END_USER) {
		if (status != NULL)
		*status = VSPM_NOT_SUPPORTED_FEATURE;
		*certBuf = NULL;
		*certSize = 0;
	}

	if (issuerIndex != 0) {
		if (status != NULL)
		*status = VSPM_NOT_SUPPORTED_FEATURE;
		*certBuf = NULL;
		*certSize = 0;
	}

	do {

		tmpCnt = VSPM_GetContainerByNameFromDescriptor(pmd, VSPM_GLOBALVAR_CONTAINER, &rc);
		if (rc != VSPM_STATUS_NO_ERROR)
			break;

		tmpItem = VSPM_GetItemByName(tmpCnt, VSPM_ISSUER_CERT, &rc);
		if (rc != VSPM_STATUS_NO_ERROR)
			break;

		value = (const char *) VSPM_GetValue(tmpItem, &rc);
		if (rc != VSPM_STATUS_NO_ERROR)
			break;

		*certBuf = (char *) Base64Decode(value, certSize);

	} while (0);

	if (status != NULL)
	*status = rc;

	if (tmpCnt)
		VSPM_FreeContainer(tmpCnt, &rc);

	if (tmpItem)
		VSPM_FreeItem(tmpItem, &rc);

	if (value)
		VSPM_FreeString((char *)value, &rc);

}


/* This function deallocates the memory occupied by a VSPM_PARAMETER structure
 *
 *   param    - IN  - the reference to VSPM_PARAMETER
 *   status   - OUT - status code
 *
 */

VSPM_EXPORT void
        VSPM_FreeParam (
                VSPM_PARAMETER param,
                VSPM_STATUS *status) {

	VSPM_STATUS rc = VSPM_STATUS_NO_ERROR;
	_VSPM_PARAMETER * _param = (_VSPM_PARAMETER *) param;

	do {

		if (! _param) {
			rc = VSPM_INVALID_DESCRIPTOR;
			break;
		}

		if (_param->displayName)
			free(_param->displayName);

		if (_param->internalName)
			free(_param->internalName);

		if (_param->value)
			free(_param->value);

		free(_param);

	} while (0);

	if (status != NULL)
	*status = rc;

}


/* This function deallocates the memory occupied by a VSPM_CRYPT_CONFIG structure
 *
 *   cryptConf - IN  - the reference to VSPM_CRYPT_CONFIG
 *   status    - OUT - status code
 *
 */

VSPM_EXPORT void
        VSPM_FreeCryptConfig (
                VSPM_CRYPT_CONFIG cryptConf,
                VSPM_STATUS *status) {

	VSPM_STATUS rc = VSPM_STATUS_NO_ERROR;
	_VSPM_CRYPT_CONFIG * _cryptConf = (_VSPM_CRYPT_CONFIG *) cryptConf;

	do {

		if (! _cryptConf) {
			rc = VSPM_INVALID_DESCRIPTOR;
			break;
		}

		if (_cryptConf->prefCSP)
			free(_cryptConf->prefCSP);

		if (_cryptConf->minAdvapi32Ver)
			free(_cryptConf->minAdvapi32Ver);

		if (_cryptConf->minCrypt32Ver)
			free(_cryptConf->minCrypt32Ver);

		free(_cryptConf);

	} while (0);

	if (status != NULL)
	*status = rc;

}


/* This function deallocates the buffer containing the binary X.509 certificate
 *
 *   certBuf - IN  - the pointer to the certificate buffer
 *   status  - OUT - status code
 *
 */

VSPM_EXPORT void
        VSPM_FreeCertBuf (
                char * certBuf,
                VSPM_STATUS *status) {

	if (certBuf) 
		free(certBuf);

	if (status != NULL)
	*status = VSPM_STATUS_NO_ERROR;
}

