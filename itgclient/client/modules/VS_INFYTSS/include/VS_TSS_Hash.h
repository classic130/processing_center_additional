#ifndef _VS_TSS_HASH_H_
#define _VS_TSS_HASH_H_

// #import in this way causes exceptions to be thrown below in case of a failure
// utilize #import with raw_interfaces_only if you do not want exceptions to be thrown
#import "tsp.tlb" 

// A namespace declaration identifies and assigns a name to a declarative region.
// This definition is the name of the namespace for the IFXTSP.dll.
using namespace TSPLib;

class VS_TSS_Hash {
   private:
       ITCPAContextPtr	m_pContextObject;
       ITCPAHashPtr		m_pHashObject;

   public:
	   VS_TSS_Hash(const VS_TSS_Context* i_cpContext, 
		           const DWORD           i_cdwAlgorithmId, 
				   DWORD*                o_dwError);
       virtual ~VS_TSS_Hash();
    
	   virtual HRESULT UpdateHashValue(const DWORD i_cdwDataLength, 
		                       const BYTE* i_cpbData);
       virtual HRESULT GetHashValue(DWORD* o_pdwHashLength, 
		                    BYTE** o_ppbHashData);
       virtual HRESULT SetHashValue(const DWORD i_cdwHashLength, 
		                    const BYTE* i_cpbHashData);

       virtual HRESULT Sign(const VS_TSS_Key* i_cpTSSKey, 
		            DWORD*            o_pdwSignatureLength, 
					BYTE**            o_ppbSignatureData);
       virtual HRESULT VerifySignature(const VS_TSS_Key* i_cpTSSKey, 
		                       const DWORD       i_cdwSignatureLength, 
							   const BYTE*       i_cpbSignatureData);
};

#endif // _VS_TSS_HASH_H_