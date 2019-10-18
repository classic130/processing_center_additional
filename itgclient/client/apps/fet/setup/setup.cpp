// setup.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include <process.h>
#include "vsctl.h"

const IID IID_Ivsctrl = {0x6C67604D,0x91A2,0x11D3,{0x8C,0x1B,0x00,0x10,0x83,0x01,0x69,0xAF}};
const CLSID CLSID_Ivsctrl = {0x6C67604E,0x91A2,0x11D3,{0x8C,0x1B,0x00,0x10,0x83,0x01,0x69,0xAF}};

Ivsctrl *g_pVSfeCtl	= NULL;

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                     LPSTR lpCmdLine, int nCmdShow)
{
 	TCHAR szTemp[MAX_PATH], szExtractedFile[MAX_PATH], szErr[MAX_PATH];
	TCHAR szInstallDir[MAX_PATH], szDestination[MAX_PATH], *pBSlash;
	TCHAR szCmd[MAX_PATH];

	// Install directory
	GetWindowsDirectory(szInstallDir, sizeof(szInstallDir));
	lstrcat(szInstallDir, "\\downlo~1");

	// 'regsvr32.exe path'
	GetSystemDirectory(szTemp,MAX_PATH);
	GetShortPathName(szTemp, szCmd, MAX_PATH);
	strcat(szCmd, "\\regsvr32");

	// Copy files to 'downlo~1' directory and register dlls 
	GetModuleFileName(hInstance, szTemp, MAX_PATH);
	pBSlash = strrchr(szTemp, '\\');
	*pBSlash = '\0';

	// PTA
	lstrcpy(szExtractedFile, szTemp);
	lstrcat(szExtractedFile, "\\vspref.dll");

	lstrcpy(szDestination, szInstallDir);
	lstrcat(szDestination, "\\vspref.dll");

	if(!CopyFile(szExtractedFile, szDestination, FALSE))
	{
		wsprintf(szErr, "Error %x copying 'vspref.dll'", GetLastError());
		MessageBox(GetFocus(), szErr, "Setup", MB_ICONERROR | MB_OK);
	}

	_spawnl(_P_WAIT, szCmd, "regsvr32","/s", szDestination, NULL);


	// FET
	lstrcpy(szExtractedFile, szTemp);
	lstrcat(szExtractedFile, "\\vsfe.dll");

	lstrcpy(szDestination, szInstallDir);
	lstrcat(szDestination, "\\vsfe.dll");

	if(!CopyFile(szExtractedFile, szDestination, FALSE))
	{
		wsprintf(szErr, "Error %x copying 'vsfe.dll'", GetLastError());
		MessageBox(GetFocus(), szErr, "Setup", MB_ICONERROR | MB_OK);
	}

	_spawnl(_P_WAIT, szCmd, "regsvr32","/s", szDestination, NULL);


	// Simulate what happens during a Web install, i.e. execute script
	// which makes some registry entries and downloads the policy file
	CoInitialize(NULL);	

	HRESULT hr;
	hr = CoCreateInstance(CLSID_Ivsctrl, NULL, CLSCTX_INPROC_SERVER, 
						  IID_Ivsctrl,(void**)&g_pVSfeCtl);
	if(hr != S_OK)
	{
		wsprintf(szErr, "CoCreateInstance() failed, error %x", hr);
		MessageBox(GetFocus(), szErr, "Setup", MB_OK | MB_ICONERROR);
		return FALSE;
	}

	BSTR bstrString;
	TCHAR szUrl[MAX_PATH] = {"file://"};
	WCHAR wcUrl[MAX_PATH];
	lstrcat(szUrl, szTemp);
	MultiByteToWideChar(CP_ACP, 0, szUrl, lstrlen(szUrl) + 1, 
						 wcUrl, sizeof(wcUrl));

	bstrString = SysAllocString(wcUrl);
	g_pVSfeCtl->SetEnterpriseServer(bstrString);
	SysFreeString(bstrString);

	g_pVSfeCtl->Release();
	CoUninitialize();

	::MessageBox(GetFocus(), "Install complete", "Setup", MB_OK);

	return 0;
}



