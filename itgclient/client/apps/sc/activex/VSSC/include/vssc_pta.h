///////////////////vssc_pta.h/////////////////////////////
#ifndef _VSSC_PTA_
#define _VSSC_PTA_

BOOL SelectCertForSigning(IVSPTA *pVSPTA,char *szCertIssuerDN,char *szCertSerialNum);

BOOL SelectCertForDecryption(IVSPTA *pVSPTA,VS_PKCS7_INFO *vsspiPKCS7Info,
							 VSSC_CERT_RDN_INFO *CertRDNInfo,DWORD *pdwSelectedCert);

BOOL SetCertSelectionCriteria(char *szCertIssuerDN, char *szCertSerialNum,
																IVSPTA *pVSPTA) ;
 

#endif
