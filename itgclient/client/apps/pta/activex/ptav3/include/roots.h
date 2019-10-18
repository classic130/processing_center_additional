#ifndef __ROOTS_UPDATE_H__
#define __ROOTS_UPDATE_H__

#include "resource.h"       // main symbols
#include "comdef.h"
#include "wincrypt.h"
//#include "CertBlobs.h"


typedef PCCERT_CONTEXT (WINAPI * VSROOTS_LPFNCertFindCertificateInStore)(HCERTSTORE hCertStore, DWORD dwCertEncodingType, DWORD dwFindFlags,DWORD dwFindType, const void *pvFindPara, PCCERT_CONTEXT pPrevCertContext);
typedef DWORD (WINAPI * VSROOTS_LPFNCertNameToStr)(DWORD dwCertEncodingType, PCERT_NAME_BLOB pName, DWORD dwStrType, LPTSTR psz, DWORD csz );
typedef BOOL (WINAPI * VSROOTS_LPFNCertGetCertificateContextProperty)(PCCERT_CONTEXT pCertContext, DWORD dwPropId, void *pvData,DWORD *pcbData);
typedef HCERTSTORE (WINAPI * VSROOTS_LPFNCertOpenStore)(LPCSTR lpszStoreProvider, DWORD dwEncodingType, HCRYPTPROV hCryptProv, DWORD dwFlags, const void *pvPara);
//typedef	HCERTSTORE (WINAPI * VSROOTS_LPFNCertOpenSystemStore)(HCRYPTPROV hProv, LPCTSTR szSubsystemProtocol);

/////////////////////////////////////////////////////////////////////////////
class ATL_NO_VTABLE CVSROOTS : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public IDispatchImpl<IVSRootsUpdate, &IID_IVSRootsUpdate, &LIBID_PTAV3Lib>,
	public CComCoClass<CVSROOTS, &CLSID_VSROOTS>
{
public:
	CVSROOTS()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_VSROOTS)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CVSROOTS)
	COM_INTERFACE_ENTRY(IVSRootsUpdate)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

// IVSRootsUpdate
public:
	STDMETHOD(Initialize)();
	STDMETHOD(CreateVerisignTrustProfile)();
	STDMETHOD(CreateStandardTrustProfile)();
};

#endif //__ROOTS_UPDATE_H__
