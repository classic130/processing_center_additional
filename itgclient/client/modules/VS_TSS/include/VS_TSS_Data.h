#ifndef _VS_TSS_DATA_H_
#define _VS_TSS_DATA_H_

class VS_TSS_Data {
   private: 
	   TSS_HCONTEXT m_hContext;
	   TSS_HKEY     m_hKey;
       TSS_HENCDATA m_hEncData;

   public:
       VS_TSS_Data(const VS_TSS_Context* i_chContext, 
		           const VS_TSS_Key*     i_cTSSKey, 
		           DWORD*                o_dwError);
       virtual ~VS_TSS_Data();

       HRESULT Encrypt(const DWORD       i_cdwDataLength, 
					   const BYTE*       i_cpbData,
                       DWORD*            o_pdwEncryptedLength, 
					   BYTE**            o_ppbEncryptedData);
       HRESULT Decrypt(const DWORD       i_cdwEncryptedLength, 
					   const BYTE*       i_cpbEncryptedData,
                       DWORD*            o_pdwDecryptedLength, 
					   BYTE**            o_ppbDecryptedData);

};

#endif // _VS_TSS_DATA_H_