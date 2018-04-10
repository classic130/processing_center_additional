/*
$Revision: 1.1.2.1 $
$Header: /cvs/itgclient/server/apps/sc/policymodule/include/Attic/vspolicyfile.h,v 1.1.2.1 2001/09/06 22:32:21 ajayaram Exp $
*/

/*--------------------------------------------------------------------\
| Copyright (C) VeriSign, Inc. created 1999. All rights reserved.     |
| This is an unpublished work protected as such under copyright law.  |
| This work contains proprietary, confidential, and trade secret      |
| information of VeriSign, Inc.  Use, disclosure or reproduction      |
| without the expressed written authorization of VeriSign, Inc.       |
| is prohibited.                                                      |
\--------------------------------------------------------------------*/

#ifndef _VSPOLICYFILE_H_
#define _VSPOLICYFILE_H_
#include <vsnvp_file.h>
#include "vspmutil.h"

#define SPEC_COOKIE	"VSPM"
#define MAJOR_VERSION	1
#define MINOR_VERSION	0


//////////////////////////////////////////////////////////////////////////////////
class VSPolicyFile : public VSNvpFile
//////////////////////////////////////////////////////////////////////////////////
{
public:
        VSPolicyFile(const char *fileName, char *lastError) : VSNvpFile(fileName, lastError) {}

	static int createRootContainer(VSContainer *root, const char *pathname, char *lastError);

protected:
	int checkFileFormat(VSContainer *root);

};

#endif
