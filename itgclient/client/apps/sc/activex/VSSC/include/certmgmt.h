/////////certmgmt.h/////////////////////////////////////

#ifndef VSSC_CERTMGMT_H
#define VSSC_CERTMGMT_H


LPTSTR	   GetCertIssuerDN(PCERT_INFO pCertInfo);
LPTSTR	   GetCertSerNum(PCERT_INFO pCertInfo);

LPTSTR	   Enc_GetCertSerNum(VS_RECIPIENT_INFO *pCertInfo);
LPTSTR     Enc_GetCertIssuerDN(VS_RECIPIENT_INFO *pCertInfo);



#endif	// CERTMGMT_H