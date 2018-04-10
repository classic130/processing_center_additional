#ifndef _VS_PTA_CERT_DATASTRUCTS_
#define _VS_PTA_CERT_DATASTRUCTS_

#include <wincrypt.h>
#include <comdef.h>

typedef struct AuxCert_Info
{
	_bstr_t tbstrFrndlyName;
	_bstr_t tbstrLogoUrl;
	_bstr_t tbstrDispString;
	_bstr_t	tbstrTextureUrl;
	_bstr_t tbstrContainerName;
	_bstr_t tbstrCertStore;
	BOOL	boolRenewed;
	BOOL	boolIsDef;
	short	nKeySpec;
}AUXCERT_INFO, *PAUXCERT_INFO;

typedef struct DecCert_Info
{
	_bstr_t tbstrIssuerDN;
	_bstr_t tbstrSubjectDN;
	_bstr_t tbstrSerNum;

	DATE dateExpDate;
	DATE dateEffDate;

	short nKeyUsage;
	short nKeySize;

}DECCERT_INFO, *PDECCERT_INFO;

typedef struct _IDLISTNODE
{
	PCERT_CONTEXT pCertContext;
	PDECCERT_INFO pDecCertInfo;
	PAUXCERT_INFO pAuxCertInfo;
	struct _IDLISTNODE* pidlistnodeNext;
}IDLISTNODE, *PIDLISTNODE;

#endif
