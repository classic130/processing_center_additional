
#include "vssc_util.h"

unsigned long GetAttributeValueBin(
					LDAP *ld,
					char *base,
					unsigned long scope,
					char *filter,
					char *attrs[],
					unsigned long attrsonly,
					unsigned char **pbAttribValue,
					unsigned int *cbAttribValue
					)
{

	unsigned long dwError = 0;
	LDAPMessage *pMsg = NULL;
	LDAPMessage *pMsgEntry = NULL;
	char *attribute;
//	char **attrib_value;
	BerElement *ber;


	dwError = ldap_search_s(ld, base, scope, filter, attrs, attrsonly, &pMsg);
	if(dwError != LDAP_SUCCESS)
	{
		//printf("Call to ldap_search_s failed: error = 0x%x\n ", dwError);
		return dwError;
	}

	pMsgEntry = ldap_first_entry(ld,pMsg);

	if(pMsgEntry == NULL)
	{
		
		return -1;
	}

	attribute = ldap_first_attribute(ld, pMsgEntry, &ber);
	if(attribute == NULL)
	{
		dwError = GetLastError();
		//printf("Mail attribute not found: error = 0x%x\n", dwError);
		return dwError;
	}

	//attrib_value = ldap_get_values(ld, pMsgEntry, attribute);
	PLDAP_BERVAL *pBer = ldap_get_values_len(ld, pMsgEntry, attribute);

	
	if(*pBer == NULL)
	//if(attrib_value == NULL)
	{
		dwError = GetLastError();
		//printf("Mail attribute value not found: error = 0x%x\n", dwError);
		return dwError;
	}
	
	//*szAttributeValue = (char *)malloc(strlen(*attrib_value) + 1);
	
	//strcpy(*szAttributeValue, *attrib_value);
	*pbAttribValue = (unsigned char *)malloc((*pBer)->bv_len);

	memcpy(*pbAttribValue, (*pBer)->bv_val, (*pBer)->bv_len);
	*cbAttribValue = (*pBer)->bv_len;

	return dwError;

}

unsigned long GetAttributeValue(
					LDAP *ld,
					char *base,
					unsigned long scope,
					char *filter,
					char *attrs[],
					unsigned long attrsonly,
					char **szAttributeValue
					)
{

	unsigned long dwError = 0;
	LDAPMessage *pMsg = NULL;
	LDAPMessage *pMsgEntry = NULL;
	char *attribute;
	char **attrib_value;
	BerElement *ber;


	dwError = ldap_search_s(ld, base, scope, filter, attrs, attrsonly, &pMsg);
	if(dwError != LDAP_SUCCESS)
	{
		//printf("Call to ldap_search_s failed: error = 0x%x\n ", dwError);
		return dwError;
	}

	pMsgEntry = ldap_first_entry(ld,pMsg);

	if(pMsgEntry == NULL)
	{
		
		return -1;
	}

	attribute = ldap_first_attribute(ld, pMsgEntry, &ber);
	if(attribute == NULL)
	{
		dwError = GetLastError();
		//printf("Mail attribute not found: error = 0x%x\n", dwError);
		return dwError;
	}

	attrib_value = ldap_get_values(ld, pMsgEntry, attribute);

	if(attrib_value == NULL)
	{
		dwError = GetLastError();
		//printf("Mail attribute value not found: error = 0x%x\n", dwError);
		return dwError;
	}
	
	*szAttributeValue = (char *)malloc(strlen(*attrib_value) + 1);
	
	strcpy(*szAttributeValue, *attrib_value);
	return dwError;

}

