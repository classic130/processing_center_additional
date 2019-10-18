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
 * $Header: /cvs/itgclient/server/apps/sc/policymodule/include/Attic/vsnvp_file.h,v 1.1.2.1 2001/09/06 22:32:11 ajayaram Exp $
 */

#ifndef _VSNVP_FILE_H_
#define _VSNVP_FILE_H_
#include <stdio.h>
#include <vsnvp.h>


////////////////////////////////////////////////////////////////////
class VSNvpFile
////////////////////////////////////////////////////////////////////
{
public:
	VSNvpFile(const char *fileName, char *lastError);
	~VSNvpFile(void);

	unsigned int lineNum(void) const { return _lineNum; }
	int status(void) const { return _vsstatus; }
	int getNext(char **name, int *nameLen, char *op, char **value, int *valueLen);

	static int createRoot(VSSection *root, const char *pathname, char *lastError);

protected:
	FILE        *_fp;
	char        *_buffer;
	int          _bufferSize;

private:
	int readLine(void);

	int          _vsstatus;
	unsigned int _lineNum;
};
#endif
