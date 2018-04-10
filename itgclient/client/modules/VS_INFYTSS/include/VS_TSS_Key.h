#ifndef _VS_TSS_KEY_H_
#define _VS_TSS_KEY_H_

// #import in this way causes exceptions to be thrown below in case of a failure
// utilize #import with raw_interfaces_only if you do not want exceptions to be thrown
#import "tsp.tlb" 

// A namespace declaration identifies and assigns a name to a declarative region.
// This definition is the name of the namespace for the IFXTSP.dll.
using namespace TSPLib;


class VS_TSS_Key {
   private:
	   DWORD        m_dwKeyUsage;
	   DWORD        m_dwModulusLength;
	   BYTE*        m_pbModulusData;
       ITCPAContextPtr	m_pContextObject;
	   ITCPAKeyPtr		m_pKeyObject;

   public:
	   /*
	    * Create and register a user storage root key
		* The parent is always SRK
		*/
	   VS_TSS_Key(const VS_TSS_Context* i_cpContext, 
                  const UUID            i_cMyUUID,
				  const DWORD           i_cdwMyPasswordLength,
                  const BYTE*           i_cMyPasssword, 
				  DWORD*                o_pdwError);
 
	   // Create and register a user leaf key
	   VS_TSS_Key(const VS_TSS_Context* i_cpContext, 
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
       VS_TSS_Key(const VS_TSS_Context* i_cpContext, 
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
       VS_TSS_Key(const VS_TSS_Context* i_cpContext,
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
	    * Get the TSS key pointer
	    * Used within VS_TSS layer
		*/
	   virtual HRESULT GetKey(ITCPAKeyPtr* o_pKey);

	   virtual HRESULT GetPublicKey(DWORD* o_pdwKeyLength, 
		                  BYTE** o_pbPublicKey);

	   virtual HRESULT GetExponent(DWORD* o_pdwExponentLength, 
		                  BYTE** o_pbExponent);

};

#endif // _VS_TSS_KEY_H_