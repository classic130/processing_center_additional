#ifndef _VS_TSS_DATA_H_
#define _VS_TSS_DATA_H_

// #import in this way causes exceptions to be thrown below in case of a failure
// utilize #import with raw_interfaces_only if you do not want exceptions to be thrown
#import "tsp.tlb" 

// A namespace declaration identifies and assigns a name to a declarative region.
// This definition is the name of the namespace for the IFXTSP.dll.
using namespace TSPLib;

class VS_TSS_Data {
   private: 
       ITCPAContextPtr	m_pContextObject;
	   ITCPAKeyPtr		m_pKeyObject;
	   ITCPAEncDataPtr	m_pEncDataObject;
   public:
       VS_TSS_Data(const VS_TSS_Context* i_cpContext, 
		           const VS_TSS_Key*     i_cpTSSKey, 
		           DWORD*                o_dwError);
       virtual ~VS_TSS_Data();

       virtual HRESULT Encrypt(const DWORD       i_cdwDataLength, 
					   const BYTE*       i_cpbData,
                       DWORD*            o_pdwEncryptedLength, 
					   BYTE**            o_ppbEncryptedData);
       virtual HRESULT Decrypt(const DWORD       i_cdwEncryptedLength, 
					   const BYTE*       i_cpbEncryptedData,
                       DWORD*            o_pdwDecryptedLength, 
					   BYTE**            o_ppbDecryptedData);

};

#endif // _VS_TSS_DATA_H_