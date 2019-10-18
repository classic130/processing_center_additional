// CClassFactory definitions.


#ifndef CLASSFACTORY_H
#define CLASSFACTORY_H

class CClassFactory : public IClassFactory
{
private:
   DWORD m_ObjRefCount;

public:
   CClassFactory();
   ~CClassFactory();

   //IUnknown methods
   STDMETHODIMP QueryInterface(REFIID, LPVOID*);
   STDMETHODIMP_(DWORD) AddRef();
   STDMETHODIMP_(DWORD) Release();

   //IClassFactory methods
   STDMETHODIMP CreateInstance(LPUNKNOWN, REFIID, LPVOID*);
   STDMETHODIMP LockServer(BOOL);
};

#endif   //CLASSFACTORY_H
