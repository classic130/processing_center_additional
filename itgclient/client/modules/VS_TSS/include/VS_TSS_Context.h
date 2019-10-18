#ifndef _VS_TSS_CONTEXT_H_
#define _VS_TSS_CONTEXT_H_

class VS_TSS_Context {
   private:
	   TSS_UUID  m_tssuuidSRK;
	   TSS_HCONTEXT     m_hContext;
	   TSS_HKEY         m_hSRK;

   public:
	   VS_TSS_Context(DWORD* o_dwError);
	   virtual ~VS_TSS_Context();

       HRESULT GetHContext(TSS_HCONTEXT* o_phContext);   
	   HRESULT GetSRK(TSS_HCONTEXT* o_phSRK);
	   HRESULT GetSRKUUID(TSS_UUID* o_puuidSRK);
};

#endif // _VS_TSS_CONTEXT_H_