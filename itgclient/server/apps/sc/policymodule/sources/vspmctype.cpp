/*
$Revision: 1.1.2.1 $
$Header: /cvs/itgclient/server/apps/sc/policymodule/sources/Attic/vspmctype.cpp,v 1.1.2.1 2001/09/06 22:32:34 ajayaram Exp $
*/

/*--------------------------------------------------------------------\
| Copyright (C) VeriSign, Inc. created 1998. All rights reserved.     |
| This is an unpublished work protected as such under copyright law.  |  
| This work contains proprietary, confidential, and trade secret      |
| information of VeriSign, Inc.  Use, disclosure or reproduction      |
| without the expressed written authorization of VeriSign, Inc.       |
| is prohibited.                                                      |
\--------------------------------------------------------------------*/

static char *_VSPMCTYPE_C= "$Id: vspmctype.cpp,v 1.1.2.1 2001/09/06 22:32:34 ajayaram Exp $";

#include <string.h>
#include "vspmctype.h"

////////////////////////////////////////////////////////////////////
int isPrintableString(const char* value)
////////////////////////////////////////////////////////////////////
{
	char valueChar;
	
	for (; *value; value++)
	{
		valueChar = *value;
		
		if (! ((valueChar >= 0x41 && valueChar <= 0x5a) ||
			   (valueChar >= 0x61 && valueChar <= 0x7a) ||
			    valueChar == 0x20 || valueChar == 0x0D || valueChar == 0x0A ||
			   (valueChar >= 0x27 && valueChar <= 0x3a && valueChar != 0x2a &&
			    valueChar != 0x3d && valueChar != 0x3f)))
			return 0;
	}
	return 1;
}


////////////////////////////////////////////////////////////////////
int isT61String(const char* value)
////////////////////////////////////////////////////////////////////
{
	char valueChar;

	for (; *value; value++)
	{
		valueChar = *value;
		
		if (valueChar >= 0x7F)
			continue;
		else if (! ((valueChar >= 0x41 && valueChar <= 0x5A) ||
           (valueChar >= 0x5F && valueChar <= 0x7A) ||
           (valueChar >= 0x21 && valueChar <= 0x40  &&
            valueChar != 0x2A && valueChar != 0x3F  &&
            valueChar != 0x25 && valueChar != 0x3D) ||
           (valueChar == 0x20 || valueChar == 0x0D  ||
            valueChar == 0x5F || valueChar == 0x26)
          ))
		  return 0;
	}
	return 1;
}


////////////////////////////////////////////////////////////////////
int isValidEmailAddress(const char* value)
////////////////////////////////////////////////////////////////////
{
	char valueChar;
	int hasValidatingSymbol = 0;

	for (; *value; value++)
	{
		valueChar = *value;
		
		if (! ((valueChar >= 0x41 && valueChar <= 0x5a) ||
			(valueChar >= 0x61 && valueChar <= 0x7a) ||
			(valueChar >= 0x27 && valueChar <= 0x3a &&
            valueChar != 0x2a && valueChar != 0x2c) ||
			valueChar == 0x5f))
		{
			if ((valueChar == '!') || (valueChar == '%') ||	(valueChar == '@'))
			{
				hasValidatingSymbol = 1;
				continue;
			}
			else
				return 0;
		}
	}
	
	if (strstr((const char *)value,"@"))
	{
		if(!strstr((const char *)value,"."))
			return 0;
	}
	if (hasValidatingSymbol)
		return 1;
	else
		return 0;
}


////////////////////////////////////////////////////////////////////
int isBase64String(const char* value)
////////////////////////////////////////////////////////////////////
{
	for (; value[0]; value++)
	{
		if (! ((value[0] >= 0x41 && value[0] <= 0x5a) ||
			   (value[0] >= 0x61 && value[0] <= 0x7a) ||
			   (value[0] >= 0x30 && value[0] <= 0x39) || 
				value[0] == 0x0d || value[0] == 0x3d  || 
				value[0] == 0x2b || value[0] == 0x2f  || 
				value[0] == 0x0a)
			)
			return 0;
	}
	return 1;
}


////////////////////////////////////////////////////////////////////
int isValidNumber(const char* value)
////////////////////////////////////////////////////////////////////
{
	for (; value[0]; value++)
	{
		if (!(value[0] >= 0x30  && value[0] <= 0x39 ))
			return 0;
	}
	return 1;
}


////////////////////////////////////////////////////////////////////
int isValidPhoneNumber(const char* value)
////////////////////////////////////////////////////////////////////
{
	for (; value[0]; value++)
	{
		if(!((value[0] >= 0x30  && value[0] <= 0x39 ) ||
			 (value[0] == 0x20) || (value[0] == 0x2d) ||
			 (value[0] == 0x28) || (value[0] == 0x29) ))
		 return 0;
	}
	return 1;
}


////////////////////////////////////////////////////////////////////
int isValidDate(const char* value)
////////////////////////////////////////////////////////////////////
{
	if (strlen((const char *)value) > 8)
		return 0;
	return isValidNumber(value);
}
