#ifndef CERTMGMT_H
#define CERTMGMT_H

#define	DIGID_CENTER		"digitalidCenter.htm"
#define DIGID_CENTER_URL	"https://digitalid.verisign.com/client/index.html"

VOID GetCertificate(VOID);
LPTSTR GetCertIssuerDN(PCERT_INFO);
LPTSTR GetCertSerNum(PCERT_INFO);

#endif	// CERTMGMT_H