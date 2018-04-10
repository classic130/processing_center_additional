// CDropSource class defintions


class CDropSource : public IDropSource
{
private: 
   DWORD m_ObjRefCount;

public: 
   // Contstructor and Destructor
   CDropSource();
   ~CDropSource();

   // IUnknown Interface members
   STDMETHODIMP QueryInterface(REFIID, LPVOID*);
   STDMETHODIMP_(ULONG) AddRef(void);
   STDMETHODIMP_(ULONG) Release(void);

   // IDropSource Interface members
   STDMETHODIMP QueryContinueDrag(BOOL, DWORD);
   STDMETHODIMP GiveFeedback(DWORD);
};

