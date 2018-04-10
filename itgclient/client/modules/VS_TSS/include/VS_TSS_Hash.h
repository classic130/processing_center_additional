#ifndef _VS_TSS_HASH_H_
#define _VS_TSS_HASH_H_

class VS_TSS_Hash {
   private:
	   TSS_HCONTEXT m_hContext;
	   TSS_HHASH    m_hHash;

   public:
	   VS_TSS_Hash(const VS_TSS_Context* i_chContext, 
		           const DWORD           i_cdwAlgorithmId, 
				   DWORD*                o_dwError);
       virtual ~VS_TSS_Hash();
    
	   HRESULT UpdateHashValue(const DWORD i_cdwDataLength, 
		                       const BYTE* i_cpbData);
       HRESULT GetHashValue(DWORD* o_pdwHashLength, 
		                    BYTE** o_ppbHashData);
       HRESULT SetHashValue(const DWORD i_cdwHashLength, 
		                    const BYTE* i_cpbHashData);

       HRESULT Sign(const VS_TSS_Key* i_cTSSKey, 
		            DWORD*            o_pdwSignatureLength, 
					BYTE**            o_ppbSignatureData);
       HRESULT VerifySignature(const VS_TSS_Key* i_cTSSKey, 
		                       const DWORD       i_cdwSignatureLength, 
							   const BYTE*       i_cpbSignatureData);
};

#endif // _VS_TSS_HASH_H_