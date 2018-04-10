#ifndef _VS_TSS_CONTEXT_H_
#define _VS_TSS_CONTEXT_H_

// #import in this way causes exceptions to be thrown below in case of a failure
// utilize #import with raw_interfaces_only if you do not want exceptions to be thrown
#import "tsp.tlb" 

// A namespace declaration identifies and assigns a name to a declarative region.
// This definition is the name of the namespace for the IFXTSP.dll.
using namespace TSPLib;

class VS_TSS_Context {
   private:
       ITCPAContextPtr	m_pContextObject;
	   ITCPAKeyPtr		m_pSRKKeyObject;

   public:
	   VS_TSS_Context(DWORD* o_dwError);
	   virtual ~VS_TSS_Context();

       virtual HRESULT GetContext(ITCPAContextPtr* o_pContext);   
	   virtual HRESULT GetSRK(ITCPAKeyPtr* o_pSRK);
};

#endif // _VS_TSS_CONTEXT_H_