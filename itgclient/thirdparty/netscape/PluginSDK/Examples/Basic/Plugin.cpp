#include <windows.h>
#include <windowsx.h>
#include <assert.h>

#ifdef WIN16
#include <memory.h>
#endif

#include "resource.h"

#include "Plugin.hpp"

static char szPluginWindowClassName[] = PLUGIN_WINDOW_CLASS_NAME;

/***********************************************/
/*                                             */
/*       CPlugin class implementation          */
/*                                             */
/***********************************************/

CPlugin::CPlugin(HINSTANCE hInst, NPP pNPInstance) :
  m_pNPInstance(pNPInstance),
  m_pNPStream(NULL),
  m_hInst(hInst),
  m_hWnd(NULL),
  m_bInitialized(FALSE),
  m_hWndParent(NULL)
{
  assert(m_hInst != NULL);
  assert(m_pNPInstance != NULL);
  m_szTitle[0] = '\0';
}

CPlugin::~CPlugin()
{
}

BOOL CPlugin::init(HWND hWndParent, LPSTR szTitle)
{
  
  m_hWndParent = hWndParent;
  assert(IsWindow(m_hWndParent));
  lstrcpy(m_szTitle, szTitle);

  m_hWnd = CreateWindow(szPluginWindowClassName, 
                        m_szTitle, 
                        WS_CHILD|WS_VISIBLE|WS_BORDER,
                        10, 10, 300, 200,
                        m_hWndParent,
                        (HMENU)-1,
                        m_hInst,
                        (LPVOID)this);

  if(m_hWnd != NULL)
  {
    m_bInitialized = TRUE;
    return TRUE;
  }
  else
    return FALSE;
}

void CPlugin::shut()
{
  if(m_hWnd != NULL)
  {
    DestroyWindow(m_hWnd);
    m_hWnd = NULL;
  }
  
  m_bInitialized = FALSE;
}

BOOL CPlugin::inited_p()
{
  return m_bInitialized;
}

BOOL CPlugin::initStream(NPStream * pNPStream)
{
  m_pNPStream = pNPStream;

  return TRUE;
}

void CPlugin::shutStream()
{
  m_pNPStream = NULL;
}

LPSTR CPlugin::getTitle()
{
  return &m_szTitle[0];
}

const HINSTANCE CPlugin::getInstance()
{
  return m_hInst;
}

long CPlugin::dataReady(NPStream * pNPStream)
{
  assert(pNPStream != NULL);
  assert(pNPStream == m_pNPStream);

  return 0x0FFFFFFF;
}

long CPlugin::data(NPStream * pNPStream, DWORD dwOffset, DWORD dwSize, LPVOID pData)
{
  assert(pNPStream != NULL);
  assert(pNPStream == m_pNPStream);

  return dwSize;
}

/***********************************************/
/*                                             */
/*        Window message handlers              */
/*                                             */
/***********************************************/

static BOOL onCreate(HWND hWnd, LPCREATESTRUCT lpCreateStruct)
{

  CPlugin * pPlugin = (CPlugin *)(lpCreateStruct->lpCreateParams);

  SetWindowLong(hWnd, 0, (long)pPlugin);

  SetWindowText(hWnd, pPlugin->getTitle());

  // custom stuff
  HWND hWndButton = CreateWindow("button", "Button", WS_CHILD|WS_VISIBLE, 20,20,100,30, 
                                 hWnd, (HMENU)1111, pPlugin->getInstance(), NULL);

  return TRUE;
}

static void onCommand(HWND hWnd, int id, HWND hWndCtl, UINT codeNotify)
{
  switch (id)
  {
    case 1111:
      break;
    default:
      break;
  }
}

static void onDestroy(HWND hWnd)
{
  CPlugin * pPlugin = (CPlugin *)GetWindowLong(hWnd, 0);
}

LRESULT CALLBACK NP_LOADDS PluginWinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
  switch(msg)
  {
    case WM_CREATE:
      HANDLE_WM_CREATE(hWnd, wParam, lParam, onCreate);
      break;
    case WM_COMMAND:
      HANDLE_WM_COMMAND(hWnd, wParam, lParam, onCommand);
      break;
    case WM_DESTROY:
      HANDLE_WM_DESTROY(hWnd, wParam, lParam, onDestroy);
      break;
    case WM_CLOSE:
      DestroyWindow(hWnd);
      break;

    default:
      return DefWindowProc(hWnd, msg, wParam, lParam);
  }
  return 0L;
}
