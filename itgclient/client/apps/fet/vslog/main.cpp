#include <windows.h>

// Local function prototypes.
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int);
BOOL InitApplication (HINSTANCE);
BOOL InitInstance (HINSTANCE, int);
LRESULT CALLBACK MainWndProc(HWND, UINT, WPARAM, LPARAM);
BOOL NameSpaceExists();
UINT g_Msg;

//extern "C" BOOL WINAPI DoOpenLink(HWND, LPCTSTR);

typedef BOOL (*LPFNDoOpenLink)(HWND, LPCTSTR);
typedef BOOL (*LPFNEncryptAtLogoff)(VOID);
typedef BOOL (*LPFNDecryptAtLogon)(VOID);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, 
				   LPSTR lpCmdLine, int nCmdShow)
{
	MSG msg;

	// lpCmdLine valid when a shortcut is clicked
	if(*lpCmdLine)
	{
		CoInitialize(NULL);

		//MessageBox(GetFocus(), lpCmdLine, "VSSafe", MB_OK | MB_SYSTEMMODAL);
	//	DoOpenLink(GetForegroundWindow(), lpCmdLine);
		HINSTANCE hInst = NULL;
		hInst = LoadLibrary("vsfectl.dll");
		if(!hInst)
		{
			MessageBox(GetFocus(), "LoadLibrary for vsfectl failed", "VSSafe", MB_OK);
			return TRUE;
		}

		LPFNDoOpenLink lpfnDoOpenLink = (LPFNDoOpenLink)GetProcAddress(hInst, "DoOpenLink");

		if(!lpfnDoOpenLink)
		{
			MessageBox(GetFocus(), "GetProcAddress() failed", "VSSafe", MB_OK);
			return TRUE;
		}

		(*lpfnDoOpenLink)(GetForegroundWindow(), lpCmdLine);

		CoUninitialize();

		return FALSE;
	}

#if 0	
	// Only one instance
	CreateMutex(NULL, TRUE, "VSLOG");

	if(GetLastError() == ERROR_ALREADY_EXISTS)
		return FALSE;

	if(!InitApplication(hInstance))
		return (FALSE);

	if (!InitInstance(hInstance, nCmdShow))
		return (FALSE);

	while (GetMessage(&msg, NULL, NULL, NULL))
	{
		//if(msg.message == g_Msg)
		//	MessageBox(GetFocus(), "Received", (LPCTSTR)msg.lParam, MB_OK);

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (msg.wParam); // Returns the value from PostQuitMessage
#else
	return FALSE;
#endif
}


BOOL InitApplication (HINSTANCE hInstance)
{
   WNDCLASS wc;

   wc.style = CS_HREDRAW | CS_VREDRAW;
   wc.lpfnWndProc = MainWndProc;
   wc.cbClsExtra = 0;
   wc.cbWndExtra = 0;
   wc.hInstance = hInstance;
   wc.hIcon = NULL;
   wc.hCursor = LoadCursor(NULL, IDC_ARROW);
   wc.hbrBackground = (	HBRUSH)COLOR_WINDOW + 1;
   wc.lpszMenuName = NULL;
   wc.lpszClassName = "VSLogWClass";

   if(!RegisterClass(&wc))
	   return FALSE;

   return TRUE;
}


BOOL InitInstance (HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;

	// Create Frame Window
	hWnd = CreateWindow("VSLogWClass", "VSLOG", 0, 0, 0, 5, 5, NULL, NULL, hInstance, NULL);

   if (!hWnd)
      return FALSE;

   //g_Msg = RegisterWindowMessage("vslogmsg");

   HINSTANCE hInst = NULL;
	hInst = LoadLibrary("vsfectl.dll");
	if(!hInst)
	{
		MessageBox(GetFocus(), "LoadLibrary for vsfectl failed", "VSSafe", MB_OK);
		return TRUE;
	}

	LPFNDecryptAtLogon lpfnDecryptAtLogon = (LPFNDecryptAtLogon)GetProcAddress(hInst, "DecryptAtLogon");

	if(!lpfnDecryptAtLogon)
	{
		MessageBox(GetFocus(), "GetProcAddress() failed", "VSSafe", MB_OK);
		return TRUE;
	}

	(*lpfnDecryptAtLogon)();
   

   return TRUE;
}


LRESULT CALLBACK MainWndProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam)
{
	switch (uMessage)
	{
		case WM_QUERYENDSESSION:
		{
			HINSTANCE hInst = NULL;

			//CoInitialize(NULL);

			hInst = LoadLibrary("vsfectl.dll");
			if(!hInst)
			{
				MessageBox(GetFocus(), "LoadLibrary for vsfectl failed", "VSSafe", MB_OK);
				return TRUE;
			}

			LPFNEncryptAtLogoff lpfnEncryptAtLogoff = (LPFNEncryptAtLogoff)GetProcAddress(hInst, "EncryptAtLogoff");

			if(!lpfnEncryptAtLogoff)
			{
				MessageBox(GetFocus(), "GetProcAddress() failed", "VSSafe", MB_OK);
				return TRUE;
			}

			(*lpfnEncryptAtLogoff)();

			return TRUE;

			//CoUninitialize();
		}
	}
	return DefWindowProc(hWnd, uMessage, wParam, lParam);
}


