/*
This class takes in a der encoded x.509 cert and creates a cert info blob.
*/
#ifndef _CERTCONTEXTHEADER
#define _CERTCONTEXTHEADER

#include "simder_all.h"
#include "MyUniversalInteger.h"
#include "MyOctetString.h"
#include "MyBitString.h"
#include <wincrypt.h>

class CCertInfo {
private :
	CERT_INFO certInfo;
	BOOL boolInitOk;
public :
	//Constructor
	CCertInfo(BYTE* pbCertDerBlob, DWORD dwCertDerBlobLen);
	
	//Destructor
	~CCertInfo();

	//Public methods
	PCERT_INFO GetCertInfo();
};
#endif