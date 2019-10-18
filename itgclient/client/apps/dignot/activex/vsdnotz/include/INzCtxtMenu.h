#include <AtlCom.h>
#include <ShlObj.h>

class ATL_NO_VTABLE INzCtxtMenu : public IContextMenu
{
public:

	// IUnknown
	STDMETHOD(QueryInterface)(REFIID riid, void** ppvObject) = 0;
	_ATL_DEBUG_ADDREF_RELEASE_IMPL(INzCtxtMenu)

	// IContextMenu
	STDMETHOD(GetCommandString)(UINT, UINT, UINT*, LPSTR, UINT)
	{
		return S_FALSE;
	}

	STDMETHOD(InvokeCommand)(LPCMINVOKECOMMANDINFO)
	{
		return S_FALSE;
	}

	STDMETHOD(QueryContextMenu)(HMENU, UINT, UINT, UINT, UINT)
	{
		return S_FALSE;
	}
};