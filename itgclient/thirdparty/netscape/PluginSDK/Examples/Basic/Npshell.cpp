//
// npshell.cpp - Plug-in methods called from Netscape.
//

#include <windows.h>
#include <string.h>

#include "npapi.h"

#include "Plugin.hpp"

HINSTANCE hInst;

char FAR szAppName[32] = {'T','e','s','t','\0'};

static char szPluginWindowClassName[] = PLUGIN_WINDOW_CLASS_NAME;

LRESULT CALLBACK NP_LOADDS PluginWinProc(HWND, UINT, WPARAM, LPARAM);


// DLL entry point, just to grab instance
int CALLBACK LibMain(HINSTANCE hinst, WORD wDataSeg, WORD cbHeap, LPSTR lpszCmdLine)
{
    hInst = hinst;
    return 1;
}

//
// NPP_Initialize
//
NPError NPP_Initialize(void)
{
  WNDCLASS wc;
  memset(&wc, 0, sizeof(wc));
  
  wc.lpfnWndProc    = (WNDPROC)PluginWinProc;
  wc.cbWndExtra     = sizeof(DWORD);
  wc.hInstance      = hInst;
  wc.hbrBackground  = (HBRUSH)(COLOR_HIGHLIGHT + 1);
  wc.lpszClassName  = szPluginWindowClassName;
  
  ATOM aRes = RegisterClass(&wc);
  if(aRes == NULL)
  {
    return NPERR_GENERIC_ERROR;
  }

  return NPERR_NO_ERROR;
}

//
// NPP_Shutdown
//
void NPP_Shutdown(void)
{
  UnregisterClass(szPluginWindowClassName, hInst);
}

//
//  NPP_GetJavaClass - This plug-in does not use the Java Runtime Interface (JRI)
//
jref NP_LOADDS NPP_GetJavaClass (void)
{
  // If no java is used return NULL.
  return NULL;
}

//
// NPP_New - Create a new plug-in instance.
//
NPError NP_LOADDS NPP_New(NPMIMEType pluginType,
                          NPP pInstance,
                          uint16 mode,
                          int16 argc,
                          char* argn[],
                          char* argv[],
                          NPSavedData* saved)
{   
  if(pInstance == NULL)
        return NPERR_INVALID_INSTANCE_ERROR;

  CPlugin * pPlugin = new CPlugin(hInst, pInstance);

  if(pPlugin == NULL)
    return NPERR_OUT_OF_MEMORY_ERROR;

  pInstance->pdata = (void *)pPlugin;

  return NPERR_NO_ERROR;
}

//
// NPP_Destroy - Destroy our plug-in instance.
//
NPError NP_LOADDS NPP_Destroy (NPP pInstance, NPSavedData** save)
{
  if(pInstance == NULL)
    return NPERR_INVALID_INSTANCE_ERROR;

  CPlugin * pPlugin = (CPlugin *)pInstance->pdata;
  if(pPlugin != NULL)
  {
    pPlugin->shut();
    delete pPlugin;
  }

  return NPERR_NO_ERROR;
}

//
// NPP_SetWindow - A window was created, resized, or destroyed.
//
NPError NP_LOADDS NPP_SetWindow (NPP pInstance, NPWindow* pNPWindow)
{    
  if(pInstance == NULL)
    return NPERR_INVALID_INSTANCE_ERROR;

  if(pNPWindow == NULL)
    return NPERR_GENERIC_ERROR;

  //HWND hWnd = DWORD2HWND((DWORD)pNPWindow->window);
  HWND hWnd = (HWND)(DWORD)pNPWindow->window;

  CPlugin * pPlugin = (CPlugin *)pInstance->pdata;

  if(pPlugin == NULL) 
    return NPERR_GENERIC_ERROR;

  if((hWnd == NULL) && !pPlugin->inited_p()) // spurious entry
    return NPERR_NO_ERROR;

  if((hWnd == NULL) && pPlugin->inited_p())
  { // window went away
    assert(0);
    return NPERR_NO_ERROR;
  }

  if(!pPlugin->inited_p() && (hWnd != NULL))
  { // First time in -- no window created by plugin yet
    if(!pPlugin->init(hWnd, szAppName))
    {
      delete pPlugin;
      pPlugin = NULL;
      return NPERR_MODULE_LOAD_FAILED_ERROR;
    }
  }

  if(pPlugin->inited_p() && (hWnd != NULL))
  { // Netscape window has been resized
  }

  return NPERR_NO_ERROR;
}

//
// NPP_NewStream - A new stream was created.
//
NPError NP_LOADDS NPP_NewStream(NPP pInstance,
                                NPMIMEType type,
                                NPStream* stream, 
                                NPBool seekable,
                                uint16* stype)
{
  if(pInstance == NULL)
    return NPERR_INVALID_INSTANCE_ERROR;

  CPlugin * pPlugin = (CPlugin *)pInstance->pdata;
  if(!pPlugin->initStream(stream))
    return NPERR_GENERIC_ERROR;

  return NPERR_NO_ERROR;
}


//
// NPP_WriteReady - Returns amount of data we can handle for the next NPP_Write
//                             
int32 NP_LOADDS NPP_WriteReady (NPP pInstance, NPStream *stream)
{
  if(pInstance == NULL)
    return NPERR_INVALID_INSTANCE_ERROR;

  CPlugin * pPlugin = (CPlugin *)pInstance->pdata;
  return (int32)pPlugin->dataReady(stream);
}


//
// NPP_Write - Here is some data. Return -1 to abort stream.
// 
int32 NP_LOADDS NPP_Write (NPP pInstance, NPStream *stream, int32 offset, int32 len, void *buffer)
{   
  if(pInstance == NULL)
    return NPERR_INVALID_INSTANCE_ERROR;

  CPlugin * pPlugin = (CPlugin *)pInstance->pdata;
  return (int32)pPlugin->data(stream, (DWORD)offset, (DWORD)len, buffer);
}

//
// NPP_DestroyStream - Stream is done, but audio may still be playing.
// 
NPError NP_LOADDS NPP_DestroyStream (NPP pInstance, NPStream *stream, NPError reason)
{
  if(pInstance == NULL)
    return NPERR_INVALID_INSTANCE_ERROR;

  CPlugin * pPlugin = (CPlugin *)pInstance->pdata;
  pPlugin->shutStream();

  return NPERR_NO_ERROR;
}


//
// NPP_StreamAsFile - For file based plug-ins, not streaming.
// 
void NP_LOADDS NPP_StreamAsFile (NPP pInstance, NPStream* stream, const char* fname)
{
}


//
// NPP_Print - This plug-in does not print.
//
void NP_LOADDS NPP_Print (NPP pInstance, NPPrint* printInfo)
{
}

void NP_LOADDS
NPP_URLNotify(NPP instance, const char* url, NPReason reason, void* notifyData)
{
  /* Not used in the Basic plugin. */
}
