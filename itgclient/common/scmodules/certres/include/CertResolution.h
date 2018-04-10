#include "vssc_util.h"

#define CERTRES_CONFIGFILE	"CertRes.config"

typedef struct
{
	VS_PROTOCOL	eProtocol;				// Protocol used to connect ot the Cert Directory Server
	char		*szServerName;			// Server name of the Cert Directory Server
	char		*szEndUserBaseDN;		// BaseDN used to retrieve EndUser Cert
	char		*szCABaseDN;			// BaseDN used to retrieve CA cert
	char		*szEmailAttribute;		// Name of the attribute which stores Email Address in End-User Certificate Object
	char		*szUserCertAttribute;	// Name of the attribute which stores EndUser Cert in End-User Certificate Object
	char		*szIssuerDNAttribute;	// Name of the attribute which stores DN in CA Certificate Object
	char		*szCACertAttribute;		// Name of the attribute which stores CA Cert in CA Certificate Object
	char		*szMyCertAttribute;
}DIRINFO;

void InitiliazeCertConfigInfo(char *szName,
					  char *szValue);

bool CertResolutionInit();



unsigned long MyCertResolution(char *szEmailAddress,
							  unsigned int *cbUserCertificate, unsigned char **pbUserCertificate);

unsigned long UserCertResolution(char *szEmailAddress,
							  unsigned int *cbUserCertificate, unsigned char **pbUserCertificate);

int Hascii2Bin(char *hasc,
			   char  **OutBuf,
			   int *OutLen);