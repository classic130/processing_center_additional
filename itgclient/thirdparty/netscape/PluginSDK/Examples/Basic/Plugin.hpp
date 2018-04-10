#ifndef __PLUGIN_HPP__
#define __PLUGIN_HPP__

#include "npapi.h"

class CPlugin
{
private:
  NPP m_pNPInstance;
  NPStream * m_pNPStream;
  HINSTANCE m_hInst;
  HWND m_hWnd;
  HWND m_hWndParent;
  BOOL m_bInitialized;
  char m_szTitle[128];

public:
  CPlugin(HINSTANCE hInst, NPP pNPInstance);
  ~CPlugin();

  BOOL init(HWND hWndParent, LPSTR szTitle);
  void shut();
  
  BOOL inited_p();

  LPSTR getTitle();
  const HINSTANCE getInstance();

  BOOL initStream(NPStream * pNPStream);
  void shutStream();
  
  long dataReady(NPStream * pNPStream);
  long data(NPStream * pNPStream, DWORD dwOffset, DWORD dwSize, LPVOID pData);
};

#define PLUGIN_WINDOW_CLASS_NAME        "TestPluginWindowClassName"

#endif // __PLUGIN_HPP__
