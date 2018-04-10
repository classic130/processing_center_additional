// vsVerify.h : Declaration of the CvsVerify

#ifndef __VSVERIFY_H_
#define __VSVERIFY_H_

#include "resource.h"       // main symbols
#include <windows.h>
#include "pta.h"
#include "valsdk.h"


/////////////////////////////////////////////////////////////////////////////
// CvsVerify
class ATL_NO_VTABLE CvsVerify : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CvsVerify, &CLSID_vsVerify>,
	public IDispatchImpl<IvsVerify, &IID_IvsVerify, &LIBID_COMVSSSCLib>
{
public:
	CvsVerify();
	~CvsVerify();

DECLARE_REGISTRY_RESOURCEID(IDR_VSVERIFY)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CvsVerify)
	COM_INTERFACE_ENTRY(IvsVerify)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

// IvsVerify
public:
	STDMETHOD(vPKIParseB64CertEx)(/*[in]*/ BSTR b64Cert, 
							  /*[out]*/ VARIANT* emailAddress, 
							  /*[out]*/ VARIANT* commonName, 
							  /*[out]*/ VARIANT* title, 
							  /*[out]*/ VARIANT* uniqueID, 
							  /*[out]*/ VARIANT* address, 
							  /*[out]*/ VARIANT* organization, 
							  /*[out]*/ VARIANT* organizationUnits, 
							  /*[out]*/ VARIANT* orgUnitCount, 
							  /*[out]*/ VARIANT* issuerOrganization, 
							  /*[out]*/ VARIANT* issuerLocality, 
							  /*[out]*/ VARIANT* issuerCountry, 
							  /*[out]*/ VARIANT* issuerCommonName, 
							  /*[out]*/ VARIANT* issuerOrganizationUnits, 
							  /*[out]*/ VARIANT* issuerOrgUnitCount, 
							  /*[out]*/ VARIANT* notBefore, 
							  /*[out]*/ VARIANT* notAfter, 
							  /*[out]*/ VARIANT* keyUsage, 
							  /*[out]*/ VARIANT* extendedKeyUsage, 
							  /*[out]*/ VARIANT* sanDirectoryNames, 
							  /*[out]*/ VARIANT* sanDirectoryNameCount, 
							  /*[out]*/ VARIANT* sanRFC822Names, 
							  /*[out]*/ VARIANT* sanRFC822NameCount, 
							  /*[out]*/ VARIANT* sanDNSNames, 
							  /*[out]*/ VARIANT* sanDNSNameCount, 
							  /*[out]*/ VARIANT* sanURIs, 
							  /*[out]*/ VARIANT* sanURICount, 
							  /*[out]*/ VARIANT* sanUPNs, 
							  /*[out]*/ VARIANT* sanUPNCount, 
							  /*[out]*/ VARIANT* sanGUIDs, 
							  /*[out]*/ VARIANT* sanGUIDCount, 
							  /*[out]*/ VARIANT* cdpDpnDirectoryNames, 
							  /*[out]*/ VARIANT* cdpDpnDirectoryNameCount, 
							  /*[out]*/ VARIANT* cdpDpnRFC822Names, 
							  /*[out]*/ VARIANT* cdpDpnRFC822NameCount, 
							  /*[out]*/ VARIANT* cdpDpnDNSNames, 
							  /*[out]*/ VARIANT* cdpDpnDNSNameCount, 
							  /*[out]*/ VARIANT* cdpDpnURIs, 
							  /*[out]*/ VARIANT* cdpDpnURICount, 
							  /*[out]*/ VARIANT* cdpDpnUPNs, 
							  /*[out]*/ VARIANT* cdpDpnUPNCount, 
							  /*[out]*/ VARIANT* cdpDpnGUIDs, 
							  /*[out]*/ VARIANT* cdpDpnGUIDCount, 
							  /*[out]*/ VARIANT* cdpCrlDirectoryNames, 
							  /*[out]*/ VARIANT* cdpCrlDirectoryNameCount, 
							  /*[out]*/ VARIANT* cdpCrlRFC822Names, 
							  /*[out]*/ VARIANT* cdpCrlRFC822NameCount, 
							  /*[out]*/ VARIANT* cdpCrlDNSNames, 
							  /*[out]*/ VARIANT* cdpCrlDNSNameCount, 
							  /*[out]*/ VARIANT* cdpCrlURIs, 
							  /*[out]*/ VARIANT* cdpCrlURICount, 
							  /*[out]*/ VARIANT* cdpCrlUPNs, 
							  /*[out]*/ VARIANT* cdpCrlUPNCount, 
							  /*[out]*/ VARIANT* cdpCrlGUIDs, 
							  /*[out]*/ VARIANT* cdpCrlGUIDCount, 
							  /*[out,retval]*/ int* retCode);

	STDMETHOD(vPKIGetB64RevocationStatus)(/*[in]*/ BSTR b64Cert, 
		                                  /*[out]*/ VARIANT* certStatus ,  
										  /*[out]*/ VARIANT* userName , 
										  /*[out,retval]*/ int* retCode);

	STDMETHOD(vPKIUnBase64Alloc)(/*[out]*/ VARIANT* data, 
	                             /*[out]*/ VARIANT* len,  
								 /*[in]*/ BSTR b64String, 
								 /*[out,retval]*/ int* retCode);

	STDMETHOD(vPKIBase64Alloc)(/*[out]*/ VARIANT* b64String, 
	                           /*[in]*/ VARIANT* data, 
							   /*[in]*/ int len, 
							   /*[out,retval]*/ int* retCode);

	
    STDMETHOD(vPKIParseB64PKCS7)(/*[in]*/ BSTR b64Pkcs7, 
	                             /*[out]*/ VARIANT*  hash , 
								 /*[out]*/ VARIANT* hashLen, 
								 /*[out]*/ VARIANT* outAlgorithm, 
								 /*[out]*/ VARIANT* b64Cert, 
								 /*[out]*/ VARIANT* certStatus , 
								 /*[out,retval]*/ int* retCode);

	STDMETHOD(vPKIVerifyB64PKCS7)(/*[in]*/ BSTR b64Pkcs7, 
	                              /*[in]*/ BSTR msg,  
								  /*[in]*/ int msgLen,  
								  /*[out]*/ VARIANT* hash,  
								  /*[out]*/ VARIANT* hashLen,  
								  /*[out]*/ VARIANT* outAlgorithm, 
								  /*[out]*/ VARIANT* b64Cert, 
								  /*[out]*/ VARIANT* certStatus, 
								  /*[out,retval]*/ int* retCode);


	STDMETHOD(vPKICompareMsgHash)(/*[in]*/ BSTR msg, 
	                              /*[in]*/ int msgLen, 
								  /*[in]*/ int outAlgorithm, 
								  /*[in]*/ VARIANT* hash, 
								  /*[in]*/ int hashLen, 
								  /*[out,retval]*/  int* retCode);

	
	STDMETHOD(vPKIParseB64Cert)(/*[in]*/ BSTR b64Cert, 
							  /*[out]*/ VARIANT* emailAddress, 
							  /*[out]*/ VARIANT* commonName, 
							  /*[out]*/ VARIANT* title, 
							  /*[out]*/ VARIANT* uniqueID, 
							  /*[out]*/ VARIANT* address, 
							  /*[out]*/ VARIANT* organization, 
							  /*[out]*/ VARIANT* organizationUnits, 
							  /*[out]*/ VARIANT* orgUnitCount, 
							  /*[out]*/ VARIANT* issuerOrganization, 
							  /*[out]*/ VARIANT* issuerLocality, 
							  /*[out]*/ VARIANT* issuerCountry, 
							  /*[out]*/ VARIANT* issuerCommonName, 
							  /*[out]*/ VARIANT* issuerOrganizationUnits, 
							  /*[out]*/ VARIANT* issuerOrgUnitCount, 
							  /*[out]*/ VARIANT* notBefore, 
							  /*[out]*/ VARIANT* notAfter, 
							  /*[out,retval]*/ int* retCode);

private:
	int m_nCrlCheck;
	HRESULT m_nInitStatus;
	HRESULT GetErrDescription(int nErrCode);	
	VSVAL_SDK* m_valSdk;

};

#endif //__VSVERIFY_H_
