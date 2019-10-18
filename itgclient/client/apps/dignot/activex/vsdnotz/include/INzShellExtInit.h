#include <AtlCom.h>
#include <ShlObj.h>

class ATL_NO_VTABLE INzShellExtInit : public IShellExtInit
{
public:

	// IUnknown
	STDMETHOD(QueryInterface)(REFIID riid, void** ppvObject) = 0;
	_ATL_DEBUG_ADDREF_RELEASE_IMPL(INzShellExtInit)

	// IShellExtInit
	STDMETHOD(Initialize)(LPCITEMIDLIST, LPDATAOBJECT, HKEY)
	{
		return S_FALSE;
	}
};