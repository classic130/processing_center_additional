/*--------------------------------------------------------------------\
| Copyright (C) VeriSign, Inc. created 1998. All rights reserved.     |
| This is an unpublished work protected as such under copyright law.  |  
| This work contains proprietary, confidential, and trade secret      |
| information of VeriSign, Inc.  Use, disclosure or reproduction      |
| without the expressed written authorization of VeriSign, Inc.       |
| is prohibited.                                                      |
\--------------------------------------------------------------------*/

/*
 * $Revision: 1.1.2.1 $
 * $Header: /cvs/itgclient/server/apps/sc/policymodule/sources/Attic/vsnvp_file.cpp,v 1.1.2.1 2001/09/06 22:32:32 ajayaram Exp $
 */

static char *_VSNVP_FILE_C= "$Id: vsnvp_file.cpp,v 1.1.2.1 2001/09/06 22:32:32 ajayaram Exp $";

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include "vsnvp_file.h"


////////////////////////////////////////////////////////////////////
VSNvpFile::VSNvpFile(const char *fileName, char *lastError)
////////////////////////////////////////////////////////////////////
{
	_vsstatus = 0;
	_fp = fopen(fileName, "r");
	if (_fp == NULL)
	{
		sprintf(lastError, "Cannot open file %s", fileName);
		_vsstatus = errno;
	}
	_lineNum = 0;
	_bufferSize = 2048;
	_buffer = (char *)malloc(_bufferSize);
	if (_buffer == NULL)
	{
		sprintf(lastError, "Cannot allocate %d bytes", _bufferSize);
		_vsstatus = errno;
	}
	else
		_buffer[0] = '\0';
}


////////////////////////////////////////////////////////////////////
VSNvpFile::~VSNvpFile(void)
////////////////////////////////////////////////////////////////////
{
	if (_fp)
		fclose(_fp);
	if (_buffer)
		free(_buffer);
}


////////////////////////////////////////////////////////////////////
int VSNvpFile::getNext(char **name, int *nameLen, char *op,
    char **value, int *valueLen)
// return TRUE if data is found
// return FALSE if no more data
////////////////////////////////////////////////////////////////////
{
	int i;

	*name = *value = NULL;
	*nameLen = *valueLen = 0;
	*op = '\0';

	if (!readLine())
		return 0; // no more data

	// scan for the beginning of the name
	for (i=0; _buffer[i]; i++)
	{
		if (isspace(_buffer[i]))
			continue;
		if (isalnum(_buffer[i]) || (_buffer[i] == '_'))
		{
			*name = &_buffer[i];
			*nameLen = 0;
			break;
		}
		else // found a non-alpha character at the beginning of the line
		{
			*op = _buffer[i];
			return 1; // ignore the rest ?
		}
	}

	// scan for the entire name
	for (;_buffer[i]; i++)
	{
		if (isalnum(_buffer[i]) || (_buffer[i] == '_'))
		{
			(*nameLen)++;
			continue;
		}
		else
			break;
	}

	// scan for the operator
	for (; _buffer[i]; i++)
	{
		if (isspace(_buffer[i]))
			continue;
		*op = _buffer[i++];
		break;
	}

	// scan for the beginning of the value
	for (; _buffer[i]; i++)
	{
		if (isspace(_buffer[i]))
			continue;
		*value = &_buffer[i];
		*valueLen = strlen(*value);
		break;
	}
	return 1;
}


////////////////////////////////////////////////////////////////////
int VSNvpFile::readLine(void)
////////////////////////////////////////////////////////////////////
{
	char line[2048];
	int i;

	*_buffer='\0';
	while (fgets(line, sizeof(line), _fp))
	{
		_lineNum++;

		// remove the trailing CR
		if (line[strlen(line)-1] == '\n')
			line[strlen(line)-1] = '\0';

		// remove all data starting at the first pound sign
		for (i=0; line[i]; i++)
		{
			if (line[i] == '#')
			{
				line[i] = '\0';
				break;
			}
		}

		// delete all trailing blanks
		for (i=strlen(line)-1; i>=0; i--)
		{
			if (isspace(line[i]))
				continue;
			line[i+1] = '\0';
			break;
		}

		if (line[0] == '\0')
			continue;

		if ((int)(strlen(line) + strlen(_buffer) + 1) >= _bufferSize)
		{
			_bufferSize += 2048;
			_buffer = (char *)realloc(_buffer, _bufferSize);
			if (_buffer == NULL)
				return 0;
		}
		strcat(_buffer, line);

		if (line[strlen(line)- 1] == '\\')
			_buffer[strlen(_buffer) - 1] = '\0';
		else // no more data
			break;
	}
	return _buffer[0];
}


////////////////////////////////////////////////////////////////////
static int addSection(VSNvpFile &fp, VSSection *session, char *lastError)
////////////////////////////////////////////////////////////////////
{
	int status = 0;
	VSSection *subSession;
	VSNvp *nvp;
	char *name;
	int nameLen;
	char *value;
	int valueLen;
	char op;

	while (fp.getNext(&name, &nameLen, &op, &value, &valueLen))
	{
		switch (op)
		{
		case '{':
			subSession = new VSSection(session, name, nameLen);
			if (subSession)
			{
				session->add(subSession);
				status = addSection(fp, subSession, lastError);
			}
			else
			{
				sprintf(lastError, "Out of memory at line %d", fp.lineNum());
				status = ENOMEM;
			}
			break;
		case '}':
			return 0;
			break;
		case ':':
			nvp = new VSNvp(session, name, nameLen, (unsigned char *)value, valueLen);
			if (nvp == NULL)
			{
				sprintf(lastError, "Out of memory at line %d", fp.lineNum());
				status = ENOMEM;
			}
			else
				session->add(nvp);
			break;
		default:
			status = EINVAL;
			sprintf(lastError, "Invalid token [%c] found at line %d", op, fp.lineNum());
			break;
		}
		if (status)
			break;
	}
	if (status)
	{
		sprintf(lastError, "No closing bracket for section %s", session->name());
		status = EINVAL;
	}
	return status;
}


////////////////////////////////////////////////////////////////////
int VSNvpFile::createRoot(VSSection *root, const char *pathname, 
	char *lastError)
////////////////////////////////////////////////////////////////////
{
	VSSection *subSession;
	VSNvp *nvp;
	VSNvpFile fp(pathname, lastError);
	char *name;
	int nameLen;
	char *value;
	int valueLen;
	char op;
	int status;

	status = fp.status();
	if (status)
		return status;

	while (fp.getNext(&name, &nameLen, &op, &value, &valueLen))
	{
		switch (op)
		{
		case '{':
			subSession = new VSSection(root, name, nameLen);
			if (subSession)
			{
				root->add(subSession);
				status = addSection(fp, subSession, lastError);
			}
			else
			{
				sprintf(lastError, "Out of memory at line %d", fp.lineNum());
				status = ENOMEM;
			}
			break;
		case ':':
			nvp = new VSNvp(root, name, nameLen, (unsigned char *)value, valueLen);
			if (nvp == NULL)
			{
				sprintf(lastError, "Out of memory at line %d", fp.lineNum());
				status = ENOMEM;
			}
			else
				root->add(nvp);
			break;
		default:
			status = EINVAL;
			sprintf(lastError, "Invalid token [%c] found at line %d", op, fp.lineNum());
			break;
		}
		if (status)
			break;
	}

	return status;
}
