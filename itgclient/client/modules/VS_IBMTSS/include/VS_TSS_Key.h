#ifndef _VS_TSS_KEY_H_
#define _VS_TSS_KEY_H_



class VS_TSS_Key {
   private:
	   TSS_HCONTEXT m_hContext;
	   TSS_HKEY     m_hKey;
	   DWORD        m_dwKeyUsage;
	   DWORD        m_dwModulusLength;
	   BYTE*        m_pbModulusData;

   public:
	   /*
	    * Create and register a user storage root key
		* The parent is always SRK
		*/
	   VS_TSS_Key(const VS_TSS_Context* i_chContext, 
                  const UUID            i_cMyUUID,
				  const DWORD           i_cdwMyPasswordLength,
                  const BYTE*           i_cMyPasssword, 
				  DWORD*                o_pdwError);
 
	   // Create and register a user leaf key
	   VS_TSS_Key(const VS_TSS_Context* i_chContext, 
		          const DWORD           i_cdwKeyLength, 
				  const DWORD           i_cdwKeyUsage,
                  const UUID            i_cMyUUID,
				  const DWORD           i_cdwMyPasswordLength,
				  const BYTE*           i_cMyPassword,
				  const UUID            i_cParentUUID,
				  const DWORD           i_cdwParentPasswordLength,
                  const BYTE*           i_cParentPasssword, 
				  DWORD*                o_pdwError);

	   // Load a user leaf key which is created in the past
       VS_TSS_Key(const VS_TSS_Context* i_chContext, 
                  const UUID            i_cMyUUID, 
				  const DWORD           i_cdwMyPasswordLength,
				  const BYTE*           i_cMyPassword,
				  const UUID            i_cParentUUID,
				  const DWORD           i_cdwParentPasswordLength,
                  const BYTE*           i_cParentPassword, 
				  DWORD*                o_pdwError);
       
       /*
	    * Create a key object with the public key only
		* The key is not to be stored in TPM
		* XXX A dummy parameter is added to silence a compiler error
		*/
       VS_TSS_Key(const VS_TSS_Context* i_chContext,
		   		  const DWORD           i_cdwKeyUsage,
		          const DWORD           i_cdwModulusLength,
				  const BYTE*           i_pbModulusData,
				  DWORD*                o_pdwError,
				  const BYTE            i_cbDummy);

       virtual ~VS_TSS_Key();

       
	   virtual HRESULT GetKeyUsage(DWORD* o_pdwKeyUsage);
       virtual HRESULT GetKeyLength(DWORD* o_pdwKeyLength);

	   virtual HRESULT GetModulusLength(DWORD* o_pdwModulusLength);
	   virtual HRESULT GetModulus(DWORD* o_pdwModulusLength, 
		                  BYTE** o_pbModulusData);

	   /* 
	    * Get the TSS key handle
	    * Used within VS_TSS layer
		*/
	   virtual HRESULT GetKey(TSS_HKEY* o_phKey);
};

#endif // _VS_TSS_KEY_H_