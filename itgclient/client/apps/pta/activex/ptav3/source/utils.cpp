#include "stdafx.h"
#include "..\Include\utils.h"
#include "..\Include\ptadefines.h"
#include "..\Include\ptaerrs.h"
#include "..\Include\vscsp_macros.h"
#include "..\Include\cspglobals.h"

#include <wininet.h>
#include <wincrypt.h>
#include <userenv.h>

typedef BOOL (WINAPI * LPFNGetProfilesDirectory) (LPTSTR lpProfilesDir, LPDWORD lpcchSize);

//typedef BOOL (WINAPI * LPFNGetUserName) (IN PCCERT_CONTEXT i_pCertContext);

typedef LONG (WINAPI * LPFNRegOpenCurrentUser) (REGSAM samDesired, PHKEY phkResult);

int BytesToAscHex(unsigned char* byteHashVal, int nHashValSize, _bstr_t& tbstrAscHexMD5)
{
	tbstrAscHexMD5 = "";
	char szDigitAscVal[] = "0123456789ABCDEF";
	char szDigit[2];

	szDigit[1] = '\0';
	for(int i=0;i<nHashValSize;++i)
	{
		szDigit[0] = szDigitAscVal[((byteHashVal[i] & 0xF0)>>4)];
		tbstrAscHexMD5 = tbstrAscHexMD5 + szDigit;
		szDigit[0] = szDigitAscVal[(byteHashVal[i] & 0x0F)];
		tbstrAscHexMD5 = tbstrAscHexMD5 + szDigit;
	}

	return 1;
}

WCHAR* TCharToWChar(TCHAR* in_lptstrStrToConvert)
{
	_bstr_t tbstrStrToConvert = "";
	WCHAR* lpwstrOutStr;

	tbstrStrToConvert = in_lptstrStrToConvert;
	lpwstrOutStr = (WCHAR*)malloc(sizeof(WCHAR)*(tbstrStrToConvert.length()+1));

	//NOTE - Right now we use wcscpy - but we may want to implement this using
	//memcpy to reduce dependency on msvcrt.
	wcscpy(lpwstrOutStr, tbstrStrToConvert);
	return lpwstrOutStr;
}

PUICTXT _CreateUIContext()
{
	PUICTXT pNewUICtxt;

	pNewUICtxt = (PUICTXT)new(UICTXT);
	pNewUICtxt->pbtnElems = NULL;
	pNewUICtxt->pbtnFns = NULL;
	pNewUICtxt->pfontInfoCustomFonts = NULL;
	pNewUICtxt->pfontInfoDefaultFonts = NULL;
	pNewUICtxt->pvUIElements = NULL;
	pNewUICtxt->pvWizardElems = NULL;
	pNewUICtxt->pvReserved = NULL;
	pNewUICtxt->bShowTopMost = FALSE;
	return pNewUICtxt;
}

HRESULT _CopyUIContext(PUICTXT o_pUICtxtDest, PUICTXT i_pUICtxtSrc)
{
	HRESULT retVal = S_OK;

	o_pUICtxtDest->nWhichWizardAndUI = i_pUICtxtSrc->nWhichWizardAndUI;
	
	if(i_pUICtxtSrc->pbtnElems)
	{
		o_pUICtxtDest->pbtnElems = new(BTNELEMS);
		if(!(o_pUICtxtDest->pbtnElems))
			retVal = E_FAIL;
		else
			*(o_pUICtxtDest->pbtnElems) = *(i_pUICtxtSrc->pbtnElems);
	}

	if(i_pUICtxtSrc->pbtnFns && retVal == S_OK)
	{
		o_pUICtxtDest->pbtnFns = new(BTNFNS);
		if(!(o_pUICtxtDest->pbtnFns))
			retVal = E_FAIL;
		else
			*(o_pUICtxtDest->pbtnFns) = *(i_pUICtxtSrc->pbtnFns);
	}

	if(i_pUICtxtSrc->pfontInfoCustomFonts && retVal == S_OK)
	{
		o_pUICtxtDest->pfontInfoCustomFonts = new(FONTSINFO);
		if(!(o_pUICtxtDest->pfontInfoCustomFonts))
			retVal = E_FAIL;
		else
			*(o_pUICtxtDest->pfontInfoCustomFonts) = *(i_pUICtxtSrc->pfontInfoCustomFonts);
	}

	if(i_pUICtxtSrc->pfontInfoDefaultFonts && retVal == S_OK)	
	{
		o_pUICtxtDest->pfontInfoDefaultFonts  = new(FONTSINFO);
		if(!(o_pUICtxtDest->pfontInfoDefaultFonts))
			retVal = E_FAIL;
		else
			*(o_pUICtxtDest->pfontInfoDefaultFonts) = *(i_pUICtxtSrc->pfontInfoDefaultFonts);
	}

	o_pUICtxtDest->tbstrDefLogoUrl = i_pUICtxtSrc->tbstrDefLogoUrl;
	o_pUICtxtDest->tbstrCustLogoUrl = i_pUICtxtSrc->tbstrCustLogoUrl;
	o_pUICtxtDest->tbstrDefAffLogoUrl = i_pUICtxtSrc->tbstrDefAffLogoUrl;
	o_pUICtxtDest->tbstrCustAffLogoUrl = i_pUICtxtSrc->tbstrCustAffLogoUrl;
	

	if(i_pUICtxtSrc->pvUIElements && retVal == S_OK)		
	{
		// Sasi 05/05/03
		// Added new case statements to copy UI structures for new operations: GetSecretQuestion, ResetPassword and CreateSecret
		switch(i_pUICtxtSrc->nWhichWizardAndUI & (~WIZARD_BITS))
		{
		case OPENPROF_OPEN_BASE :
		case OPENPROF_CREATE_BASE :
			o_pUICtxtDest->pvUIElements = (void*)new(ALL_OPENPROF_UIELEMENTS);
			if(!(o_pUICtxtDest->pvUIElements))
				retVal = E_FAIL;
			else
				(*(PALL_OPENPROF_UIELEMENTS)(o_pUICtxtDest->pvUIElements)) = (*(PALL_OPENPROF_UIELEMENTS)(i_pUICtxtSrc->pvUIElements));
			break;

	
		case SELID_BASE :
			o_pUICtxtDest->pvUIElements  = (void*)new(ALL_SELID_UIELEMENTS);
			if(!(o_pUICtxtDest->pvUIElements))
				retVal = E_FAIL;
			else
				(*(PALL_SELID_UIELEMENTS)(o_pUICtxtDest->pvUIElements)) = (*(PALL_SELID_UIELEMENTS)(i_pUICtxtSrc->pvUIElements));
			break;

		case SIGNMSG_BASE :
			o_pUICtxtDest->pvUIElements  = (void*)new(ALL_REVWMSG_UIELEMENTS);
			if(!(o_pUICtxtDest->pvUIElements))
				retVal = E_FAIL;
			else
				(*(PALL_REVWMSG_UIELEMENTS)(o_pUICtxtDest->pvUIElements)) = (*(PALL_REVWMSG_UIELEMENTS)(i_pUICtxtSrc->pvUIElements));
			break;

		case INTRO_BASE :
			o_pUICtxtDest->pvUIElements  = (void*)new(ALL_INTRODLG_UIELEMENTS);
			if(!(o_pUICtxtDest->pvUIElements))
				retVal = E_FAIL;
			else
				(*(PALL_INTRODLG_UIELEMENTS)(o_pUICtxtDest->pvUIElements)) = (*(PALL_INTRODLG_UIELEMENTS)(i_pUICtxtSrc->pvUIElements));
			break;

		case CREATEPASSWD_BASE : 
			o_pUICtxtDest->pvUIElements  = (void*)new(ALL_CREATEPASSWD_UIELEMENTS);
			if(!(o_pUICtxtDest->pvUIElements))
				retVal = E_FAIL;
			else
				(*(PALL_CREATEPASSWD_UIELEMENTS)(o_pUICtxtDest->pvUIElements)) = (*(PALL_CREATEPASSWD_UIELEMENTS)(i_pUICtxtSrc->pvUIElements));
			break;

		case ENTERPASSWD_BASE : 
			o_pUICtxtDest->pvUIElements  = (void*)new(ALL_ENTERPASSWD_UIELEMENTS);
			if(!(o_pUICtxtDest->pvUIElements))
				retVal = E_FAIL;
			else
				(*(PALL_ENTERPASSWD_UIELEMENTS)(o_pUICtxtDest->pvUIElements)) = (*(PALL_ENTERPASSWD_UIELEMENTS)(i_pUICtxtSrc->pvUIElements));
			break;

		case CHANGEPASSWD_BASE :
			o_pUICtxtDest->pvUIElements  = (void*)new(ALL_CHANGEPASSWD_UIELEMENTS);
			if(!(o_pUICtxtDest->pvUIElements))
				retVal = E_FAIL;
			else
				(*(PALL_CHANGEPASSWD_UIELEMENTS)(o_pUICtxtDest->pvUIElements)) = (*(PALL_CHANGEPASSWD_UIELEMENTS)(i_pUICtxtSrc->pvUIElements));
			break;

		case IMPORTP12_BASE :
			o_pUICtxtDest->pvUIElements  = (void*)new(ALL_IMPORTP12_UIELEMENTS);
			if(!(o_pUICtxtDest->pvUIElements))
				retVal = E_FAIL;
			else
				(*(PALL_IMPORTP12_UIELEMENTS)(o_pUICtxtDest->pvUIElements)) = (*(PALL_IMPORTP12_UIELEMENTS)(i_pUICtxtSrc->pvUIElements));
			break;

		case EXPORTP12_BASE :
			o_pUICtxtDest->pvUIElements  = (void*)new(ALL_EXPORTP12_UIELEMENTS);
			if(!(o_pUICtxtDest->pvUIElements))
				retVal = E_FAIL;
			else
				(*(PALL_EXPORTP12_UIELEMENTS)(o_pUICtxtDest->pvUIElements)) = (*(PALL_EXPORTP12_UIELEMENTS)(i_pUICtxtSrc->pvUIElements));
			break;

		case GETSECRETQUESTION_BASE :
			o_pUICtxtDest->pvUIElements = (void*)new(ALL_GETSECRETQUESTION_UIELEMENTS);
			if(!(o_pUICtxtDest->pvUIElements))
				retVal = E_FAIL;
			else
				(*(PALL_GETSECRETQUESTION_UIELEMENTS)(o_pUICtxtDest->pvUIElements)) = (*(PALL_GETSECRETQUESTION_UIELEMENTS)(i_pUICtxtSrc->pvUIElements));
			break;

		case RESETPASSWD_BASE :
			o_pUICtxtDest->pvUIElements  = (void*)new(ALL_RESETPASSWD_UIELEMENTS);
			if(!(o_pUICtxtDest->pvUIElements))
				retVal = E_FAIL;
			else
				(*(PALL_RESETPASSWD_UIELEMENTS)(o_pUICtxtDest->pvUIElements)) = (*(PALL_RESETPASSWD_UIELEMENTS)(i_pUICtxtSrc->pvUIElements));
			break;

		case CREATESECRET_BASE :
			o_pUICtxtDest->pvUIElements  = (void*)new(ALL_CREATESECRET_UIELEMENTS);
			if(!(o_pUICtxtDest->pvUIElements))
				retVal = E_FAIL;
			else
				(*(PALL_CREATESECRET_UIELEMENTS)(o_pUICtxtDest->pvUIElements)) = (*(PALL_CREATESECRET_UIELEMENTS)(i_pUICtxtSrc->pvUIElements));
			break;

		default :
			retVal = E_INVALIDUIFLAG;
			break;
		}
	}
	
	if(i_pUICtxtSrc->pvWizardElems && retVal == S_OK)
	{
		o_pUICtxtDest->pvWizardElems = (void*)new (ALLWIZARDELEMENTS);
		if(!(o_pUICtxtDest->pvWizardElems))
				retVal = E_FAIL;
		else	
			(*(PALLWIZARDELEMENTS)(o_pUICtxtDest->pvWizardElems)) = (*(PALLWIZARDELEMENTS)(i_pUICtxtSrc->pvWizardElems));		
	}
	
	o_pUICtxtDest->nDefLangId = i_pUICtxtSrc->nDefLangId;
	o_pUICtxtDest->bShowTopMost = i_pUICtxtSrc->bShowTopMost;
	return retVal;
}

void _FreeUIContext(PUICTXT i_pUICtxt)
{
	if(i_pUICtxt)
	{
		if(i_pUICtxt->pbtnElems)
		{
			delete(i_pUICtxt->pbtnElems);
			i_pUICtxt->pbtnElems = NULL;
		}
		
		if(i_pUICtxt->pbtnFns)
		{
			delete(i_pUICtxt->pbtnFns);
			i_pUICtxt->pbtnFns = NULL;
		}

		if(i_pUICtxt->pfontInfoCustomFonts)
		{
			delete(i_pUICtxt->pfontInfoCustomFonts);
			i_pUICtxt->pfontInfoCustomFonts = NULL;
		}

		if(i_pUICtxt->pfontInfoDefaultFonts)
		{
			delete(i_pUICtxt->pfontInfoDefaultFonts);
			i_pUICtxt->pfontInfoDefaultFonts = NULL;
		}

		if(i_pUICtxt->pvUIElements)
		{
			// Sasi 05/05/03
			// Added new case statements to destroy UI structures for new operations: GetSecretQuestion, ResetPassword and CreateSecret
			switch(i_pUICtxt->nWhichWizardAndUI & (~WIZARD_BITS))
			{
			case OPENPROF_OPEN_BASE :
			case OPENPROF_CREATE_BASE :
				delete((PALL_OPENPROF_UIELEMENTS)i_pUICtxt->pvUIElements);
				break;

		
			case SELID_BASE :
				delete((PALL_SELID_UIELEMENTS)i_pUICtxt->pvUIElements);
				break;

			case SIGNMSG_BASE :
				delete((PALL_REVWMSG_UIELEMENTS)i_pUICtxt->pvUIElements);
				break;

			case INTRO_BASE :
				delete((PALL_INTRODLG_UIELEMENTS)i_pUICtxt->pvUIElements);
				break;

			case CHANGEPASSWD_BASE :
				delete((PALL_CHANGEPASSWD_UIELEMENTS)i_pUICtxt->pvUIElements);
				break;

			case IMPORTP12_BASE :
				delete((PALL_IMPORTP12_UIELEMENTS)i_pUICtxt->pvUIElements);
				break;
			
			case EXPORTP12_BASE :
				delete((PALL_EXPORTP12_UIELEMENTS)i_pUICtxt->pvUIElements);
				break;

			case GETSECRETQUESTION_BASE :
				delete((PALL_GETSECRETQUESTION_UIELEMENTS)i_pUICtxt->pvUIElements);
				break;

			case RESETPASSWD_BASE :
				delete((PALL_RESETPASSWD_UIELEMENTS)i_pUICtxt->pvUIElements);
				break;

			case CREATESECRET_BASE :
				delete((PALL_CREATESECRET_UIELEMENTS)i_pUICtxt->pvUIElements);
				break;


			default :
				break;
			}
			i_pUICtxt->pvUIElements = NULL;
		}

		if(i_pUICtxt->pvWizardElems)
		{
			delete((PALLWIZARDELEMENTS)i_pUICtxt->pvWizardElems);
			i_pUICtxt->pvWizardElems = NULL;
		}


	}

	return;
}

HRESULT _GetBitmap(_bstr_t& tbstrBmpUrl, HBITMAP* o_phBitmap)
{
	HRESULT retVal = S_OK;
	
	BITMAP_THREAD_PARAM param;
	
	 // store the info for the bitmap in a structure, which will be passed to a thread
	param.tbstrBmpUrl =  tbstrBmpUrl;
	param.phBitmap = o_phBitmap;
	param.status = retVal;

	DWORD  dwThreadID = 0;
    HANDLE hThread = 0;

	   // Create a thread that downloads a bitmap from the web server. We need to run it on a separate thread
	   // since it uses WinINET API to get the bitmap and this some how doesn't support multiple
	   // connections on the same thread. This issue was encountered with native client auth (SSL).
    hThread = CreateThread(NULL, // no security attributes 
         0,                      // use default stack size 
         (LPTHREAD_START_ROUTINE) BitmapThreadFunc, // thread function 
         &param,                 // thread function argument 
         0,                       // use default creation flags 
         &dwThreadID);              // returns thread identifier 

    if (hThread == 0) {
			retVal = E_CREATETHREADFAILED;        
    } else {
			// wait until thread completes the task
        DWORD rc = WaitForSingleObject(hThread, INFINITE);

		if(rc == WAIT_FAILED)
			retVal = E_CREATETHREADFAILED;
		else 
			retVal = param.status;

	}

    return retVal;
}

// Sasi - 04/14/2003
// Added a new function that can be executed on a separate thread. This function
// connects to web server and downloads bitmap. 
// Parameters:
//	bitmap structure containing input bitmap url, output bitmap and output status.
HRESULT BitmapThreadFunc(BITMAP_THREAD_PARAM *lpParam)
{
	HRESULT retVal = S_OK;

	_bstr_t temp = "VeriSign Web Access Control";

	_bstr_t tbstrBmpUrl = lpParam -> tbstrBmpUrl;
	HBITMAP* phBitmap = lpParam -> phBitmap;

	if(InternetAttemptConnect(0) == ERROR_SUCCESS)
	{
		HINTERNET hInternet;

		//Initialize
		if((hInternet =  InternetOpen((TCHAR*)temp, INTERNET_OPEN_TYPE_PRECONFIG,
			NULL,NULL,INTERNET_FLAG_FROM_CACHE )) == NULL) 
		{
			DWORD err;
			err = GetLastError();
			retVal = E_INTERNETOPENERR;
			
		}
		else
		{
			//Try to connect to szURL
			HINTERNET hInternetURL;
			temp = tbstrBmpUrl;
			if((hInternetURL = InternetOpenUrl(hInternet,(TCHAR*)temp,NULL, -1L,0,0)) == NULL)
			{
				DWORD err;
				err = GetLastError();
				if(err == ERROR_FILE_NOT_FOUND)
				{
					retVal = S_OK;

					//File is not in the cache, try to get it from the network
					InternetCloseHandle(hInternet);
					if((hInternet =  InternetOpen((TCHAR*)temp, INTERNET_OPEN_TYPE_PRECONFIG,
					NULL,NULL,0)) == NULL) 
					{
						DWORD err;
						err = GetLastError();
						retVal = E_INTERNETOPENERR;
					}
					else
					{
						if((hInternetURL = InternetOpenUrl(hInternet,(TCHAR*)temp,NULL, -1L,0,0)) == NULL)
						{
							retVal = E_INTERNETOPENURLERR;		
						}
					}
				}
				else
				{
					retVal = E_INTERNETOPENURLERR;
				}
			}

			if(retVal == S_OK)
			{
				//Write the data to a file
				DWORD dwbytesReadSize;
				BYTE buffer[128];
				DWORD dwSize;
				TCHAR* tstrTempPath;
				TCHAR* tstrLogoFile;

				//Get the temporary path name
				if((dwSize = GetTempPath(0,NULL)) == 0)
				{
					retVal = E_COULDNOTGETTEMPPATH;
				}
				else
				{
					tstrTempPath = (TCHAR*)malloc(dwSize + sizeof(TCHAR));
					if(!tstrTempPath)
					{
						retVal = -1;
					}
					else
					{
						if((dwSize = GetTempPath(dwSize,tstrTempPath)) == 0)
						{
							retVal = E_COULDNOTGETTEMPPATH;
						}
						else
						{
							tstrLogoFile = (TCHAR*)malloc(MAX_PATH);

							temp = _T("vspta");
							//Get the temporary file name
							if(GetTempFileName(tstrTempPath,(TCHAR*)temp,0,tstrLogoFile) == 0)
							{
								retVal = E_COULDNOTGETTEMPFILENAME;
							}
							else
							{
								//Create a file to store the data in
								HANDLE hFileHandle;
								hFileHandle = CreateFile(tstrLogoFile,GENERIC_READ|GENERIC_WRITE,0,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL, NULL);
								if(!hFileHandle)
									retVal = E_COULDNOTCREATETEMPFILE;

								//Store the data in this file
								do
								{
									if(!InternetReadFile(hInternetURL,(LPVOID)buffer,128,&dwbytesReadSize))
									{
										retVal = E_INTERNETREADERR;
										break;
									}
									else if(dwbytesReadSize)
									{
										if(!WriteFile(hFileHandle,buffer,dwbytesReadSize,&dwbytesReadSize,NULL))
										{
											retVal = E_FILEWRITEERR;
											break;
										}
									}

								}while(dwbytesReadSize != 0);

								CloseHandle(hFileHandle);

								//Now create a bitmap handle
								*phBitmap = (HBITMAP)LoadImage(NULL,tstrLogoFile,IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
								if(! *phBitmap)
									retVal = GetLastError();

								//Delete the file
								DeleteFile(tstrLogoFile);
							}

							free(tstrLogoFile);
						}

						free(tstrTempPath);
					}
				}
				
				InternetCloseHandle(hInternetURL);
			}

			InternetCloseHandle(hInternet);
		}

	}
	else
		retVal = E_INTERNETATTEMPTERR;

	lpParam -> status = retVal;

	return retVal;
}

/*
HRESULT _GetBitmap(_bstr_t& tbstrBmpUrl, HBITMAP* o_phBitmap)
{
	HRESULT retVal = S_OK;
	
	_bstr_t temp = "VeriSign Web Access Control";

	if(InternetAttemptConnect(0) == ERROR_SUCCESS)
	{
		HINTERNET hInternet;

		//Initialize
		if((hInternet =  InternetOpen((TCHAR*)temp, INTERNET_OPEN_TYPE_PRECONFIG,
			NULL,NULL,INTERNET_FLAG_FROM_CACHE )) == NULL) 
		{
			DWORD err;
			err = GetLastError();
			retVal = E_INTERNETOPENERR;
			
		}
		else
		{
			//Try to connect to szURL
			HINTERNET hInternetURL;
			temp = tbstrBmpUrl;
			if((hInternetURL = InternetOpenUrl(hInternet,(TCHAR*)temp,NULL, -1L,0,0)) == NULL)
			{
				DWORD err;
				err = GetLastError();
				if(err == ERROR_FILE_NOT_FOUND)
				{
					retVal = S_OK;

					//File is not in the cache, try to get it from the network
					InternetCloseHandle(hInternet);
					if((hInternet =  InternetOpen((TCHAR*)temp, INTERNET_OPEN_TYPE_PRECONFIG,
					NULL,NULL,0)) == NULL) 
					{
						DWORD err;
						err = GetLastError();
						retVal = E_INTERNETOPENERR;
					}
					else
					{
						if((hInternetURL = InternetOpenUrl(hInternet,(TCHAR*)temp,NULL, -1L,0,0)) == NULL)
						{
							retVal = E_INTERNETOPENURLERR;		
						}
					}
				}
				else
				{
					retVal = E_INTERNETOPENURLERR;
				}
			}

			if(retVal == S_OK)
			{
				//Write the data to a file
				DWORD dwbytesReadSize;
				BYTE buffer[128];
				DWORD dwSize;
				TCHAR* tstrTempPath;
				TCHAR* tstrLogoFile;

				//Get the temporary path name
				if((dwSize = GetTempPath(0,NULL)) == 0)
				{
					retVal = E_COULDNOTGETTEMPPATH;
				}
				else
				{
					tstrTempPath = (TCHAR*)malloc(dwSize + sizeof(TCHAR));
					if(!tstrTempPath)
					{
						retVal = -1;
					}
					else
					{
						if((dwSize = GetTempPath(dwSize,tstrTempPath)) == 0)
						{
							retVal = E_COULDNOTGETTEMPPATH;
						}
						else
						{
							tstrLogoFile = (TCHAR*)malloc(MAX_PATH);

							temp = _T("vspta");
							//Get the temporary file name
							if(GetTempFileName(tstrTempPath,(TCHAR*)temp,0,tstrLogoFile) == 0)
							{
								retVal = E_COULDNOTGETTEMPFILENAME;
							}
							else
							{
								//Create a file to store the data in
								HANDLE hFileHandle;
								hFileHandle = CreateFile(tstrLogoFile,GENERIC_READ|GENERIC_WRITE,0,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL, NULL);
								if(!hFileHandle)
									retVal = E_COULDNOTCREATETEMPFILE;

								//Store the data in this file
								do
								{
									if(!InternetReadFile(hInternetURL,(LPVOID)buffer,128,&dwbytesReadSize))
									{
										retVal = E_INTERNETREADERR;
										break;
									}
									else if(dwbytesReadSize)
									{
										if(!WriteFile(hFileHandle,buffer,dwbytesReadSize,&dwbytesReadSize,NULL))
										{
											retVal = E_FILEWRITEERR;
											break;
										}
									}

								}while(dwbytesReadSize != 0);

								CloseHandle(hFileHandle);

								//Now create a bitmap handle
								*o_phBitmap = (HBITMAP)LoadImage(NULL,tstrLogoFile,IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
								if(! *o_phBitmap)
									retVal = GetLastError();

								//Delete the file
								DeleteFile(tstrLogoFile);
							}

							free(tstrLogoFile);
						}

						free(tstrTempPath);
					}
				}
				
				InternetCloseHandle(hInternetURL);
			}

			InternetCloseHandle(hInternet);
		}

	}
	else
		retVal = E_INTERNETATTEMPTERR;
	return retVal;
}
*/
HRESULT _FreeBitmap(HBITMAP i_hBitmap)
{
	if(i_hBitmap)
		DeleteObject(i_hBitmap);
	return S_OK;
}

HRESULT _GetCertCN(_bstr_t& i_tbstrSubjectDN, _bstr_t* o_ptbstrSubjectCN)
{
	HRESULT retVal = S_OK;

	int nNumOfAttrs;
	_bstr_t* ptbstrAttrs = NULL;
	_bstr_t* ptbstrVals = NULL;
	retVal = _ParseDNIntoComponents(i_tbstrSubjectDN, &nNumOfAttrs, &ptbstrAttrs, &ptbstrVals);

	if(retVal == S_OK)
	{
		*o_ptbstrSubjectCN = "";
		for(int i=0;i<nNumOfAttrs;++i)
		{
			if(ptbstrAttrs[i] == _bstr_t("CN"))
			{
				*o_ptbstrSubjectCN = ptbstrVals[i];
			}
		}
	}

	delete[] ptbstrAttrs;
	delete[] ptbstrVals;

	return retVal;
}

HRESULT _FormatDate(DATE in_theDate, _bstr_t* o_ptbstrFormattedDate)
{
	HRESULT retVal = S_OK;

	//First obtain the date format for the current locale
	TCHAR tcharDateFormatType[2];
	if(!GetLocaleInfo(LOCALE_SYSTEM_DEFAULT,LOCALE_IDATE,tcharDateFormatType,2))
		retVal = E_GETLOCALEINFOFAILED;
	else
	{
		_bstr_t tbstrDateFormat = "";

		if(!lstrcmp(tcharDateFormatType,_T("0")))
		{
			tbstrDateFormat = _T("MM'\'dd'\'yyyy");
		}
		else if(!lstrcmp(tcharDateFormatType,_T("1")))
		{
			tbstrDateFormat = _T("dd'\'MM'\'yyyy");
		}
		else
		{
			tbstrDateFormat = _T("yyyy'\'MM'\'dd'");
		}

		SYSTEMTIME st;
		if(!VariantTimeToSystemTime(in_theDate,&st))
			retVal = E_VARTIMETOSYSTIMEFAILED;
		else
		{
			TCHAR* ptszFormattedDate;
			int nFormattedDateSize;
			if((nFormattedDateSize = GetDateFormat(LOCALE_SYSTEM_DEFAULT,0,&st,NULL,NULL,0)) == 0)
				retVal = E_GETDATEFORMATSIZEFAILED;
			else
			{
				ptszFormattedDate = (TCHAR*)new TCHAR[nFormattedDateSize];
				if(!ptszFormattedDate)
					retVal =  E_FAIL;
				else
				{
					if((nFormattedDateSize = GetDateFormat(LOCALE_SYSTEM_DEFAULT,0,&st,NULL,ptszFormattedDate,nFormattedDateSize)) == 0)
						retVal = E_GETDATEFORMATFAILED;
					else
					{
						*o_ptbstrFormattedDate = ptszFormattedDate;
					}
					delete[] ptszFormattedDate;
				}
			}
		}
	}

	return retVal;
}

HRESULT _ParseDNIntoComponents(_bstr_t& i_tbstrSubjectDN, int* o_pnNumOfDNAttrs,_bstr_t** o_pptbstrDNAttrs, _bstr_t** o_pptbstrDNVals)
{

	WCHAR* pwszTempStr;
	HRESULT retVal = S_OK;
	_bstr_t tbstrFirstDNAttr = "";
	_bstr_t tbstrFirstDNVal = "";
	UINT nFirstDNValLen = 0;

	if(i_tbstrSubjectDN.length() == 0)
	{
		*o_pnNumOfDNAttrs = 0;
		return S_OK;
	}

	//Copy the inputted dn into a temporary string
	pwszTempStr = (WCHAR*)new WCHAR[i_tbstrSubjectDN.length()+1];
	if(!pwszTempStr)
		retVal = E_FAIL;

	for(unsigned int i=0;i<i_tbstrSubjectDN.length();++i)
		pwszTempStr[i] = ((WCHAR*)(i_tbstrSubjectDN))[i];
	pwszTempStr[i] = L'\0';

	//Obtain the first component type
	WCHAR *pwszStartPtr, *pwszEndPtr, *pwszSpacePtr;
	BOOL boolDone = FALSE;
	int nState = 0;

	pwszStartPtr = pwszTempStr;
	
	do
	{
		switch(nState)
		{
		case 0:
			if(*pwszStartPtr == L' ')
				pwszStartPtr ++;
			else if(*pwszStartPtr == L'\0')
			{
				boolDone = TRUE;
				retVal = E_DNPARSEERR;
			}
			else
			{
				pwszEndPtr = pwszStartPtr+1;
				nState = 1;
			}

			break;

		case 1:
			if(*pwszEndPtr == L' ')
			{
				*pwszEndPtr = '\0';
				pwszEndPtr++;
			}
			else if(*pwszEndPtr == L'=')
			{
				*pwszEndPtr = '\0';
				boolDone = TRUE;
			}
			else if(*pwszEndPtr == L'\0')
			{
				boolDone = TRUE;
				retVal = E_DNPARSEERR;
			}
			else
			{
				pwszEndPtr++;
			}
			break;

		}
	}while(!boolDone);

	if(retVal == S_OK)
	{
		tbstrFirstDNAttr = pwszStartPtr;
		pwszStartPtr = ++pwszEndPtr;
		pwszSpacePtr = pwszEndPtr;
		boolDone = FALSE;
		nState = 0;

		do
		{
			//Now obtain the first component value
			switch(nState)
			{
			case 0:
				if(*pwszStartPtr == L' ')
					pwszStartPtr ++;
				else if(*pwszStartPtr == L'\0')
				{
					boolDone = TRUE;
					retVal = E_DNPARSEERR;
				}
				else if(*pwszStartPtr == L'\"')
				{
					pwszEndPtr = pwszStartPtr+1;
					nState = 2;
				}
				else if(*pwszStartPtr == L'<')		// Wasim : Oct, 2001, Parsing out "<>" if present
				{
					pwszStartPtr ++;
					nState = 3;
				}
				else if(*pwszStartPtr == L'#')		// Wasim : Oct, 2001, we do not support non-printable strings yet
				{
					boolDone = TRUE;
					retVal = E_DNPARSEERR;
				}
				else
				{
					pwszEndPtr = pwszStartPtr+1;
					pwszSpacePtr = pwszEndPtr;		// reset the pointer
					nState = 1;
				}
				break;

			case 1:
				if(*pwszEndPtr == L' ')
				{
					pwszEndPtr++;
				}
				else if( (*pwszEndPtr == L';') || (*pwszEndPtr == L',') )  // added comma as delimiter
				{
					*pwszSpacePtr = '\0';
					pwszEndPtr++;
					boolDone = TRUE;
				}
				else if(*pwszEndPtr == L'\0')
				{
					boolDone = TRUE;
					pwszSpacePtr = '\0';
				}
				else if(*pwszEndPtr == L'\"')
				{
					pwszEndPtr++;
					nState = 2;
				}
				else
				{
					pwszEndPtr++;
					pwszSpacePtr = pwszEndPtr;
				}
				break;

			case 2:
				if(*pwszEndPtr == L'\"')
				{
					pwszEndPtr++;
					pwszSpacePtr = pwszEndPtr;
					nState = 1;
				}
				else
				{
					pwszEndPtr++;
					pwszSpacePtr = pwszEndPtr;
				}
				break;

			case 3:
				if(*pwszStartPtr == L'>')
				{
					pwszStartPtr ++;
					nState = 0;
				}
				else if(*pwszStartPtr == L'\0')
				{
					boolDone = TRUE;
					retVal = E_DNPARSEERR;
				}
				else
					pwszStartPtr ++;
				break;

			}
		}while(!boolDone);
	}

	if(retVal == S_OK)
	{
		WCHAR wcTemp[2];
		wcTemp[0] = '\0';
		nFirstDNValLen = wcslen(pwszStartPtr);
		UINT i = 0;

		// Strip out the quotes from the beginning and end of the string if any. Also if two
		// consecutive quotes are present keep only one because that is the way 'MyCertNameTStr()'
		// has created it
		if(pwszStartPtr[i] == L'"')
		{
			i++;
			nFirstDNValLen--;
		}
		
		for(; i < nFirstDNValLen; i++)
		{
			if(wcTemp[0] == L'"' && pwszStartPtr[i] == L'"')
			{
				wcTemp[0] = '\0';
				continue;
			}

			wcTemp[0] = pwszStartPtr[i];
			wcTemp[1] = '\0';

			tbstrFirstDNVal += wcTemp;
		}

		//Obtain the remaining components
		_bstr_t tbstrRemainingDN = "";
		_bstr_t* ptbstrRemainingAttrs = NULL;
		_bstr_t* ptbstrRemainingVals = NULL;
		int nRemainingAttrs = 0;

		tbstrRemainingDN = pwszEndPtr;
		retVal = _ParseDNIntoComponents(tbstrRemainingDN, &nRemainingAttrs, &ptbstrRemainingAttrs,
			&ptbstrRemainingVals);
		if(retVal == S_OK)
		{
			//Allocate space for all the attributes and values
			*o_pnNumOfDNAttrs = nRemainingAttrs + 1;
			*o_pptbstrDNAttrs = (_bstr_t*) new _bstr_t[*o_pnNumOfDNAttrs];
			*o_pptbstrDNVals = (_bstr_t*) new _bstr_t[*o_pnNumOfDNAttrs];

			//Save all the attributes and values
			(*o_pptbstrDNAttrs)[0] = tbstrFirstDNAttr;
			(*o_pptbstrDNVals)[0] = tbstrFirstDNVal;

			for(int i=0;i<nRemainingAttrs;++i)
			{
				(*o_pptbstrDNAttrs)[i+1] = ptbstrRemainingAttrs[i];
				(*o_pptbstrDNVals)[i+1] = ptbstrRemainingVals[i];
			}
			delete[] ptbstrRemainingAttrs;
			delete[] ptbstrRemainingVals;
		}

	}

	delete[] pwszTempStr;
	return retVal;
	
}

int AscHexToBytes(_bstr_t& i_tbstrAscHex, unsigned char* o_pbyteBytes)
{
	char* pszAscHex = (char*)i_tbstrAscHex;
	unsigned char pbyteUpperNibble;
	unsigned char pbyteLowerNibble;
	WCHAR* pwszAscHex;
	pwszAscHex = (WCHAR*)i_tbstrAscHex;

	for(unsigned int i=0;i<(i_tbstrAscHex.length()/2); ++i)
	{
		if((pwszAscHex[i*2]) >= '0' && (pwszAscHex[i*2]) <= '9')
			pbyteUpperNibble = (pwszAscHex[i*2]) - '0';
		else if((pwszAscHex[i*2]) >= 'a' && (pwszAscHex[i*2]) <= 'f')
			pbyteUpperNibble = (pwszAscHex[i*2]) - 'a' + 0x000A;
		else 
			pbyteUpperNibble = (pwszAscHex[i*2]) - 'A' + 0x000A;

		pbyteUpperNibble = pbyteUpperNibble << 4;

		if((pwszAscHex[(i*2)+1]) >= '0' && (pwszAscHex[(i*2)+1]) <= '9')
			pbyteLowerNibble = (pwszAscHex[(i*2)+1]) - '0';
		else if((pwszAscHex[(i*2)+1]) >= 'a' && (pwszAscHex[(i*2)+1]) <= 'f')
			pbyteLowerNibble = (pwszAscHex[(i*2)+1]) - 'a' + 0x000A;
		else 
			pbyteLowerNibble = (pwszAscHex[(i*2)+1]) - 'A' + 0x000A;

		o_pbyteBytes[i] = pbyteUpperNibble | pbyteLowerNibble;
	}

	return 1;
}

HRESULT GetKeyFromBlob
(
	const BYTE*			i_cpbyteKeyBlob,
	const DWORD			i_cdwKeyBlobLen,
	A_RSA_KEY*			o_pKey
)
{
	HRESULT						hResult						=	E_FAIL;

	DWORD						dwOffset					=	0;

	while (1)
	{
				//	copy the modulus length
		memcpy
		(
			(void*) &((o_pKey -> modulus).len),
			(const void*) i_cpbyteKeyBlob,
			sizeof (unsigned int)
		);

		dwOffset += sizeof (unsigned int);

				//	allocate memory for modulus data
		(o_pKey -> modulus).data =	(unsigned char*) new BYTE [(o_pKey -> modulus).len * sizeof (unsigned char)];
		CHECK_ALLOCATED_MEMORY ( (o_pKey -> modulus).data )

				//	copy modulus data
		memcpy
		(
			(void*)	(o_pKey -> modulus).data ,
			(const void*) &(i_cpbyteKeyBlob [dwOffset]),
			(o_pKey -> modulus).len
		);

		dwOffset += (o_pKey -> modulus).len * sizeof (unsigned char);

				//	copy exponent len
		memcpy
		(
			(void*) &((o_pKey -> exponent).len),
			(const void*) &(i_cpbyteKeyBlob [dwOffset]),
			sizeof (unsigned int)
		);

		dwOffset += sizeof (unsigned int);

				//	allocate memory for exponent data
		(o_pKey -> exponent).data =	(unsigned char*) new BYTE [(o_pKey -> exponent).len * sizeof (unsigned char)];
		CHECK_ALLOCATED_MEMORY ( (o_pKey -> exponent).data )

				//	copy exponent data
		memcpy
		(
			(void*)	(o_pKey -> exponent).data ,
			(const void*) &(i_cpbyteKeyBlob [dwOffset]),
			(o_pKey -> exponent).len
		);
		
		hResult =	S_OK;
		break;
	}	//	end		while (1)

	return	hResult;
}	//	end		HRESULT	GetKeyFromBlob


///////////////////////////////////////////////////////////////////////////////
//
//	Function Name	:	GetBlobFromKey
//
//	Parameters
//		const A_RSA_KEY*	i_cpKey				-	the key
//		BYTE**				o_ppbyteKeyBlob		-	the key will be flattened and copied
//													to this blob. Memory will be allocated
//													by this function. the caller should free
//													the memory
//		DWORD*				o_pdwKeyBlobLen		-	the lenght of the blob will be
//													returned in this
//
//	Return Values	:
//		VS_SUCCESS		-	successful
//
//	Description		:	the function will accept a RSA key, flatten it and return it
//						as a byte blob
//
///////////////////////////////////////////////////////////////////////////////	
HRESULT		GetBlobFromKey
(
	const A_RSA_KEY*	i_cpKey,
	BYTE**				o_ppbyteKeyBlob,
	DWORD*				o_pdwKeyBlobLen
)
{
	HRESULT						hResult				=	E_FAIL;

	DWORD						dwOffset			=	0;

	while (1)
	{
			//	the A_RSA_KEY strucutre contains 2 ITEM
			//	each ITEM is a char* followed by len
			//
			//	so to flatten out this structure we will have to put the actual char arrays
			//	into the byte blob
		*o_pdwKeyBlobLen =		(i_cpKey -> modulus).len * sizeof (unsigned char)\
							+	sizeof (unsigned int)\
							+	(i_cpKey -> exponent).len * sizeof (unsigned char)\
							+	sizeof (unsigned int);

		*o_ppbyteKeyBlob =	new BYTE [*o_pdwKeyBlobLen];
		CHECK_ALLOCATED_MEMORY (*o_ppbyteKeyBlob)

		memcpy
		(
			(void*) &((*o_ppbyteKeyBlob) [dwOffset]),
			(const void*) &((i_cpKey -> modulus).len),
			sizeof (unsigned int)
		);

		dwOffset +=	sizeof (unsigned int);

		memcpy
		(
			(void*) &((*o_ppbyteKeyBlob) [dwOffset]),
			(const void*) (i_cpKey -> modulus).data,
			(i_cpKey -> modulus).len * sizeof (unsigned char)
		);

		dwOffset += (i_cpKey -> modulus).len * sizeof (unsigned char);

		memcpy
		(
			(void*) &((*o_ppbyteKeyBlob) [dwOffset]),
			(const void*) &((i_cpKey -> exponent).len),
			sizeof (unsigned int)
		);

		dwOffset +=	sizeof (unsigned int);

		memcpy
		(
			(void*) &((*o_ppbyteKeyBlob) [dwOffset]),
			(const void*) (i_cpKey -> exponent).data,
			(i_cpKey -> exponent).len * sizeof (unsigned char)
		);

		hResult =	VS_SUCCESS;
		break;
	}	//	end		while (1)

	return	hResult;
}	//	end		HRESULT		CVirtualSmartCard::GetBlobFromKey


///////////////////////////////////////////////////////////////////////////////
//
//	Function Name	:	HashPublicKey
//
//	Parameters
//		const A_RSA_KEY*	i_cpPublicKey	-	the public key
//		BYTE*				o_pbyteHash		-	the hash of the flattened public key
//												will be returned in this. the length
//												of this buffer MUST be VS_CSP_SHA1_LEN (=20) as the SHA1
//												algo will be used
//
//	Return Values	:
//		VS_SUCCESS		-	successful
//		NTE_FAIL		-	failure
//
//	Description		:	the function will accept a RSA public key, flatten it, hash it
//						 and return the hash.
//
///////////////////////////////////////////////////////////////////////////////	
HRESULT		HashPublicKey
(
	const A_RSA_KEY*	i_cpPublicKey,
	BYTE*				o_pbyteHash
)
{
	HRESULT						hResult				=	E_FAIL;
	int							nResult				=	999;

	BYTE*						pbyteKeyBlob		=	NULL;
	DWORD						dwKeyBlobLen		=	0;

	void*						pvoidContext		=	NULL;

	DWORD						dwBufferSize		=	VS_CSP_SHA1_LEN;	//	SHA len

	while (1)
	{
				//	flatten the public key
		hResult =	GetBlobFromKey
					(
						i_cpPublicKey,
						&pbyteKeyBlob,
						&dwKeyBlobLen
					);

		if ( VS_SUCCESS != hResult )
			break;

				//	hash the byte blob
		nResult =	HashBegin
					(
						VS_SHA_1,
						&pvoidContext
					);
		if ( 0 != nResult )
		{
			hResult =	NTE_FAIL;
			break;
		}

		nResult =	HashData
					(
						VS_SHA_1,
						pvoidContext,
						(unsigned char*) pbyteKeyBlob,
						(unsigned int) dwKeyBlobLen
					);
		if ( 0 != nResult )
		{
			hResult =	NTE_FAIL;
			break;
		}

		nResult =	HashEnd
					(
						VS_SHA_1,
						pvoidContext,
						o_pbyteHash,
						dwBufferSize
					);
		if ( 0 != nResult )
		{
			hResult =	NTE_FAIL;
			break;
		}

		hResult =	VS_SUCCESS;
		break;
	}	//	end		while (1)
	
	VSCSP_CHECK_FOR_NULL_AND_DELETE (pbyteKeyBlob)

	return	hResult;
}	//	end		HRESULT		CVirtualSmartCard::HashPublicKey

int mallocandcpy(BYTE*& pbDestBuff, BYTE* pbSrcBuff, unsigned int nBuffSize)
{
	if(!pbSrcBuff)
		return 0;
	pbDestBuff = (_BYTE*)malloc(sizeof(_BYTE)*nBuffSize);
	memcpy(pbDestBuff,pbSrcBuff,nBuffSize);
	return 1;
}

int freecertinfo(PCERT_INFO pCertInfo)
{
	if(pCertInfo)
	{
		if(pCertInfo->SerialNumber.pbData)
			free(pCertInfo->SerialNumber.pbData);

		if(pCertInfo->SignatureAlgorithm.pszObjId)
			free(pCertInfo->SignatureAlgorithm.pszObjId);

		if(pCertInfo->SignatureAlgorithm.Parameters.pbData)
			free(pCertInfo->SignatureAlgorithm.Parameters.pbData);

		if(pCertInfo->Issuer.pbData)
			free(pCertInfo->Issuer.pbData);

		if(pCertInfo->Subject.pbData)
			free(pCertInfo->Subject.pbData);

		if(pCertInfo->SubjectPublicKeyInfo.Algorithm.pszObjId)
			free(pCertInfo->SubjectPublicKeyInfo.Algorithm.pszObjId);

		if(pCertInfo->SubjectPublicKeyInfo.Algorithm.Parameters.pbData)
			free(pCertInfo->SubjectPublicKeyInfo.Algorithm.Parameters.pbData);
	
		if(pCertInfo->SubjectPublicKeyInfo.PublicKey.pbData)
			free(pCertInfo->SubjectPublicKeyInfo.PublicKey.pbData);
		
		if(pCertInfo->IssuerUniqueId.pbData)
			free(pCertInfo->IssuerUniqueId.pbData);

		if(pCertInfo->SubjectUniqueId.pbData)
			free(pCertInfo->SubjectUniqueId.pbData);

		for(unsigned int i=0; i<pCertInfo->cExtension; ++i)
		{
			if(pCertInfo->rgExtension[i].pszObjId)
				free(pCertInfo->rgExtension[i].pszObjId);
			if(pCertInfo->rgExtension[i].Value.pbData )
				free(pCertInfo->rgExtension[i].Value.pbData);
		}

		if(pCertInfo->rgExtension)
			free(pCertInfo->rgExtension);

	}

	memset(pCertInfo, 0 , sizeof(PCERT_INFO));

	return 1;
}

HRESULT _UTCToFiletime(unsigned char* pbUTCTime, FILETIME* ftFileTime)
{
	int nUTCTimeLen;
	LPSTR szUTCTime = (LPSTR)pbUTCTime;
	HRESULT retVal = S_OK;

	nUTCTimeLen = strlen(szUTCTime);

	//Make sure that the last character in the UTCTime string and if the length of the
	//string is greater than or equal to 13 (YYMMDDHHMMSSZ)
	if((szUTCTime[nUTCTimeLen - 1] != 'Z' && szUTCTime[nUTCTimeLen - 1] != 'z') || nUTCTimeLen < 13)
	{
		retVal = E_NOT_GMT;
	}
	else
	{
		//Set the environment variables for the local time - will be turned on when we do the portable
		//code
		//_tzset();

		/*Obtain the information from the UTCTime string*/

		//The first two characters represent the year - this will be true till year 2050
		char szYear[3];
		szYear[0] = szUTCTime[0];
		szYear[1] = szUTCTime[1];
		szYear[2] = '\0';

		int nYear;
		nYear = atoi(szYear);
		if(nYear < 50) //which century is it 2000 or 1900
			nYear += 2000;
		else
			nYear += 1900;

		//The next two characters represent the month.
		char szMonth[3];
		szMonth[0] = szUTCTime[2];
		szMonth[1] = szUTCTime[3];
		szMonth[2] = '\0';

		int nMonth;
		nMonth = atoi(szMonth);

		//The next two characters represent the day
		char szDay[3];
		szDay[0] = szUTCTime[4];
		szDay[1] = szUTCTime[5];
		szDay[2] = '\0';

		int nDay;
		nDay = atoi(szDay);
	
		//The next two characters represent the hours
		char szHour[3];
		szHour[0] = szUTCTime[6];
		szHour[1] = szUTCTime[7];
		szHour[2] = '\0';

		int nHour;
		nHour = atoi(szHour);
		
		//The next two characters represent the minutes
		char szMins[3];
		szMins[0] = szUTCTime[8];
		szMins[1] = szUTCTime[9];
		szMins[2] = '\0';

		int nMins = atoi(szMins);

		//The next two characters represent the seconds
		char szSecs[3];
		szSecs[0] = szUTCTime[10];
		szSecs[1] = szUTCTime[11];
		szSecs[2] = '\0';

		int nSecs = atoi(szSecs);


		//Convert to filetime for now - later we will turn on the usage of time_t instead of FILETIME
		//for portability - NOTE;
		SYSTEMTIME stGMT;
		stGMT.wYear = nYear;
		stGMT.wMonth = nMonth;
		stGMT.wDay = nDay;
		stGMT.wHour = nHour;
		stGMT.wMinute = nMins;
		stGMT.wSecond = nSecs;
		stGMT.wMilliseconds = 0;

		if(!SystemTimeToFileTime(&stGMT,ftFileTime))
		{
			int err = GetLastError();
			retVal = E_SYSTOFT_ERR;		
		}

			
	}
	return retVal;
}


HRESULT			ParseProfile_Path_Name
(
	const WCHAR*			i_cwszProfile_Path_Name,
	BSTR*					o_pbstrUserName,
	BSTR*					o_pbstrPath,
	BSTR*					o_pbstrApContext
)
{
	
	HRESULT					retVal = S_OK;
//	WCHAR*					wszProfilePathName [MAX_PATH];
//	WCHAR*					wszUserName [MAX_PATH];
//	WCHAR*					wszPath [MAX_PATH];
//	WCHAR*					wszApContext [MAX_PATH];

	DWORD					dwTotalLength			=	0;

	DWORD					dwUserNameLen			=	0;
	DWORD					dwPathLen				=	0;
	DWORD					dwApContextLen			=	0;

		//	check input parameters
	if	(\
			( NULL == i_cwszProfile_Path_Name )		||\
			( NULL == o_pbstrUserName )				||\
			( NULL == o_pbstrPath )					||\
			( NULL == o_pbstrApContext )				  \
		)
	{
		return	E_INVALIDARG;
	}

	_bstr_t tbstrAppCtxtName = "";
	_bstr_t tbstrProfName = "";
	_bstr_t tbstrPathName = "";

	_bstr_t tbstrInputString = i_cwszProfile_Path_Name;
	WCHAR* pwszTemp;
	
	if(tbstrInputString.length() > (_bstr_t(PROFILE_NAME_ENDING)).length())
	{
		_bstr_t	tbstrProfileSubStr = "";

		pwszTemp = (WCHAR*)tbstrInputString.copy();

		tbstrProfileSubStr = &pwszTemp[tbstrInputString.length()- (_bstr_t(PROFILE_NAME_ENDING)).length()];
		if(tbstrProfileSubStr == _bstr_t(PROFILE_NAME_ENDING))
		{
			pwszTemp[tbstrInputString.length()- (_bstr_t(PROFILE_NAME_ENDING)).length()] = L'\0';
			tbstrInputString = pwszTemp;
		}

		SysFreeString(pwszTemp);
	}

	pwszTemp = (WCHAR*)tbstrInputString.copy();

	for(int i = tbstrInputString.length()-1; i >= 0  ;--i)
	{
		if(pwszTemp[i] == L'\'') // We've found the 's
		{
			if(pwszTemp[i+1] != L's' &&  pwszTemp[i+2] != L' ')
			{
				retVal = E_PATHNAMEPARSEERR;
				i = -1;
			}
			else
			{
				tbstrAppCtxtName = pwszTemp+(i+3);
				pwszTemp[i] = L'\0';
				i = -1;
			}
		}
	}

	//Now get the username by looking for the first '\' from right
	
	if(retVal == S_OK)
	{
		tbstrInputString = pwszTemp;
		SysFreeString(pwszTemp);	
		pwszTemp = tbstrInputString.copy();
		
		for(int i = tbstrInputString.length()-1; i >= 0  ;--i)
		{
			if(pwszTemp[i] == L'\\') // We've found the '\'
			{
				tbstrProfName = pwszTemp+(i+1);
				pwszTemp[i] = L'\0';
				tbstrPathName = pwszTemp;
				i = -1;
			}
			else if(i==0) //we've reached the beginning of the string
			{
				tbstrProfName = pwszTemp;
				pwszTemp[i] = L'\0';
				tbstrPathName = pwszTemp;
			}

		}
		
	}

	SysFreeString(pwszTemp);

	if(retVal == S_OK)
	{
		*o_pbstrApContext = tbstrAppCtxtName.copy();
		*o_pbstrPath = tbstrPathName.copy();
		*o_pbstrUserName = tbstrProfName.copy();
	}

//	VSPTA_CLEAN_TBSTR(tbstrAppCtxtName)
//	VSPTA_CLEAN_TBSTR(tbstrProfName)
//	VSPTA_CLEAN_TBSTR(tbstrPathName)

	return	retVal;
}


HRESULT			GetProfileInfoFromRegistry
(
	const WCHAR*			i_cwszContainerName,
	BSTR*					o_pbstrProfile,
	BSTR*					o_pbstrClientInfo,
	BSTR*					o_pbstrClientInfoSig,
	BOOL*					o_pboolIsLocal
)
{
	HRESULT				hResult;

	_bstr_t				tbstrRegKeyName;
	_bstr_t				tbstrValueName;
	_bstr_t				tbstrProfileValue;

	BYTE				pbyteData [CLIENT_INFO_LEN];
	DWORD				dwData		=	CLIENT_INFO_LEN;
	DWORD				dwType		=	0;

	LONG				lResult;

	HKEY				hRegKey		=	NULL;
	HMODULE				hModAdvapiDll = NULL;
	HKEY				hCurrUserKey = HKEY_CURRENT_USER;

	LPFNRegOpenCurrentUser	My_RegOpenCurrentUser =	NULL;
	

	    // Need to use RegOpenCurrentUser to map HKEY_CURRENT_USER to
	    // proper HKEY_USERS\User's SID key. Otherwise, it is not mapped to 
	    // proper user's registry key when the user is impersonated in the service.

	    // RegOpenCurrentUser function is available only on Windows 2000 and later.
		// It is not present on Win95/98/NT and so if the function is called directly the 
		// registration fails. so we have to do a load library followed by the getprocaddress 
		// for the "RegOpenCurrentUser" function.
	    // This fix is specifically made for Windows 2000 and later.
	
	hModAdvapiDll = ::LoadLibrary("advapi32.dll");
	if(NULL == hModAdvapiDll)
	{
		return	E_ADVAPI32LOADFAILED;
	}

	My_RegOpenCurrentUser = (LPFNRegOpenCurrentUser) ::GetProcAddress
							(
								hModAdvapiDll, 
								"RegOpenCurrentUser"
							);

	if(NULL != My_RegOpenCurrentUser)
	{
		// It is windows 2000 or later
		lResult =	My_RegOpenCurrentUser
					(
						KEY_ALL_ACCESS,
						&hCurrUserKey
					);

		if ( ERROR_SUCCESS != lResult )
		{
			hCurrUserKey = HKEY_CURRENT_USER;
		}

	}


	tbstrRegKeyName	=	VS_CRYPTO_REG_KEY;
	tbstrRegKeyName += i_cwszContainerName;

	tbstrValueName	=	PROFILE_NAME;

	lResult =	RegOpenKeyEx
				(
					hCurrUserKey,
					tbstrRegKeyName,
					0,
					KEY_ALL_ACCESS,
					&hRegKey
				);
	if ( ERROR_SUCCESS != lResult )
	{
		hResult =	::GetLastError ();
		if ( NULL != hRegKey )
		{
			RegCloseKey (hRegKey);
		}
		if( HKEY_CURRENT_USER != hCurrUserKey)
		{
			RegCloseKey (hCurrUserKey);
		}
		return	hResult;
	}

	lResult =	RegQueryValueEx
				(
					hRegKey,
					tbstrValueName,
					NULL,
					&dwType,
					pbyteData,
					&dwData
				);
	if ( ERROR_SUCCESS != lResult )
	{
		hResult =	::GetLastError ();
		if ( NULL != hRegKey )
		{
			RegCloseKey (hRegKey);
		}
		if( HKEY_CURRENT_USER != hCurrUserKey)
		{
			RegCloseKey (hCurrUserKey);
		}
		return	hResult;
	}

	tbstrProfileValue =	(TCHAR*) pbyteData;

	*o_pbstrProfile =	tbstrProfileValue.copy();

	tbstrValueName	=	PROFILE_TYPE;
	dwData			=	CLIENT_INFO_LEN;

	lResult	=	RegQueryValueEx
				(
					hRegKey,
					tbstrValueName,
					NULL,
					&dwType,
					pbyteData,
					&dwData
				);
	if ( ERROR_SUCCESS != lResult )
	{
		*o_pboolIsLocal			=	TRUE;
		*o_pbstrClientInfo		=	_bstr_t("");
		*o_pbstrClientInfoSig	=	_bstr_t("");
	}
	else
	{
		*o_pboolIsLocal	=	(BOOL)pbyteData[0];

		tbstrValueName	=	CLIENT_INFO;
		dwData			=	CLIENT_INFO_LEN;

		lResult =	RegQueryValueEx
					(
						hRegKey,
						tbstrValueName,
						NULL,
						&dwType,
						pbyteData,
						&dwData
					);
		if ( ERROR_SUCCESS != lResult )
		{
			hResult =	::GetLastError ();
			if ( NULL != hRegKey )
			{
				RegCloseKey (hRegKey);
			}
			if( HKEY_CURRENT_USER != hCurrUserKey)
			{
				RegCloseKey (hCurrUserKey);
			}
			return	hResult;
		}
		else
		{
			tbstrProfileValue	=	(TCHAR*) pbyteData;
			*o_pbstrClientInfo	=	tbstrProfileValue.copy();

			tbstrValueName	=	CLIENT_INFO_SIG;
			dwData			=	CLIENT_INFO_LEN;

			lResult =	RegQueryValueEx
						(
							hRegKey,
							tbstrValueName,
							NULL,
							&dwType,
							pbyteData,
							&dwData
						);
			if ( ERROR_SUCCESS != lResult )
			{
				hResult =	::GetLastError ();
				if ( NULL != hRegKey )
				{
					RegCloseKey (hRegKey);
				}
				if( HKEY_CURRENT_USER != hCurrUserKey)
				{
					RegCloseKey (hCurrUserKey);
				}
				return	hResult;
			}
			else
			{
				tbstrProfileValue		=	(TCHAR*) pbyteData;
				*o_pbstrClientInfoSig	=	tbstrProfileValue.copy();
			}
		}
	}

	if ( NULL != hRegKey )
	{
		RegCloseKey (hRegKey);
	}

	if( HKEY_CURRENT_USER != hCurrUserKey)
	{
		RegCloseKey (hCurrUserKey);
	}

	if(NULL != hModAdvapiDll)
	{
		::FreeLibrary(hModAdvapiDll);
	}

	return	S_OK;
}

HRESULT CreateProfile_Path_Name(WCHAR* i_pwszProfileName, WCHAR* i_pwszAppCtxtName, BSTR* o_pbstrProfPathName)
{
	HRESULT retVal = S_OK;
	_bstr_t tbstrProfilePathName;

	/*First obtain the directory in which the profile is to be created*/
	BSTR bstrProfilePath = 0;
	retVal = GetProfilePath(&bstrProfilePath);
	
	/*Concatenate the profile name to this path*/
	if(retVal == S_OK)
	{
		tbstrProfilePathName = bstrProfilePath;
		tbstrProfilePathName += i_pwszProfileName;

		/*Add a 's(space) */
		tbstrProfilePathName += USER_NAME_ENDING;

		/*Add the appcontext name(space) Profile.pta*/
		tbstrProfilePathName += i_pwszAppCtxtName;
		tbstrProfilePathName += PROFILE_NAME_ENDING;

	}

	/*Free memory*/
	if(bstrProfilePath)
		SysFreeString(bstrProfilePath);

	*o_pbstrProfPathName = tbstrProfilePathName.copy();

	return retVal;
}

HRESULT GetProfilePath(BSTR* o_pbstrProfilePath)
{

	HRESULT retVal = S_OK;
	TCHAR tszEnvVariables[] = HOMEDRIVEATH_ENV;
	TCHAR tszProfilePath[MAX_PATH];
	_bstr_t tbstrProfilePath = "";
	UINT	unPathProfileLen	=	999;
	DWORD	dwWindows2000Check	=	0;
	_bstr_t	tbstrNewProfilePath = "";

	//
	//	Anand	May 04, 2000
	//
	//	The "%HOMEDRIVE%%HOMEPATH%" is sometimes not set (esp on Win 95/98)
	//	so the folder to store the profiles is changed to
	//	SYSTEMDRIVE\Program Files\VeriSign\PTA
	//
/*
	if(!ExpandEnvironmentStrings(tszEnvVariables,tszProfilePath, MAX_PATH))
		retVal = E_EXPENVSTRFAILED;
	else
	{
		tbstrProfilePath = tszProfilePath;
	}
*/

			//	get the path where windows is stored
	unPathProfileLen =	::GetWindowsDirectory
						(
							(LPTSTR) tszProfilePath,
							(UINT) MAX_PATH
						);
	if ( 0 == unPathProfileLen )
	{
		retVal =	::GetLastError ();
		return retVal;
	}


	retVal =	CheckIfWinNTorWin2000 (&dwWindows2000Check);
	if ( S_OK != retVal )
	{
		return	retVal;
	}

		//	we need only the drive 'c:\' or the 'd:\' so end the string after 3 chars
	tszProfilePath [3] = '\0';
	tbstrProfilePath =	tszProfilePath;
	tbstrProfilePath += VERISIGN_PTA_PROFILE_PATH;	//	append the "Program Files\\VeriSign\\PTA\\"

	if ( 1 == dwWindows2000Check )
	{
		tbstrNewProfilePath =	tbstrProfilePath;
		retVal =	UpdatePathIfNecessary (&tbstrNewProfilePath);
		if ( S_OK != retVal )
		{
			return	retVal;
		}

		tbstrProfilePath =	tbstrNewProfilePath;
//		tbstrProfilePath += WIN_2000_VERISIGN_PTA_PROFILE_PATH;
	}

	*o_pbstrProfilePath = tbstrProfilePath.copy();

	return retVal;
}


DWORD MyCertNameToStr(DWORD dwCertEncodingType, PCERT_NAME_BLOB pName, DWORD dwStrType,
					  LPTSTR psz, DWORD csz)
{
	if ( NULL == pName )
		return 0;

	// Only support for these for now
	if ( ( CERT_X500_NAME_STR | CERT_NAME_STR_SEMICOLON_FLAG ) != dwStrType )
		return 0;

	CBaseDERCollection cbdcCertName( pName->cbData, pName->pbData );
	CBaseDERHierarchy cbdhCertName( cbdcCertName );
	DERTree* dtCertNameInfo = &cbdhCertName.m_DERTree, *dtSet = NULL, *dtSequence = NULL;
	DERTree *dtObjID = NULL, *dtObjIDValue = NULL;
	BYTE *pbData = NULL, *pbValueData = NULL;
	DWORD cbData = 0, cbValueData = 0, dwTotalRdnLen = 0;
	TCHAR szLabel[MAX_PATH];
	_bstr_t bstrValueData = "";
	
	// Confirm we have a SEQUENCE
	if ( NULL == dtCertNameInfo || SEQUENCE != dtCertNameInfo->currentBaseDER->Type )
		return 0;

	if ( NULL != psz && 0 < csz)
		psz[0] = '\0';

	// Construct the o=;ou=...
	dtSet = dtCertNameInfo->rightDERTree;
	
	while ( NULL != dtSet )
	{
		// Make sure that it is a set
		if ( SET != dtSet->currentBaseDER->Type )
		{
			dwTotalRdnLen = 0;
			break;
		}

		// Make sure that it is a sequence
		dtSequence = dtSet->rightDERTree;
		if ( NULL == dtSequence || SEQUENCE != dtSequence->currentBaseDER->Type )
		{
			dwTotalRdnLen = 0;
			break;
		}

		// Make sure that it is a object ID.
		dtObjID = dtSequence->rightDERTree;
		if ( NULL == dtObjID || OBJECT_IDENTIFIER != dtObjID->currentBaseDER->Type )
		{
			dwTotalRdnLen = 0;
			break;
		}

		pbData = dtObjID->currentBaseDER->pbData;
		cbData = dtObjID->currentBaseDER->cbData;

		// Value of the Object ID
		dtObjIDValue = dtObjID->nextDERTree;

		if ( NULL == dtObjIDValue )
		{
			dwTotalRdnLen = 0;
			break;
		}

		pbValueData = dtObjIDValue->currentBaseDER->pbData;
		cbValueData = dtObjIDValue->currentBaseDER->cbData;

		if ( !strnicmp((const char*)pbData, szOID_COMMON_NAME, cbData) )
		{
			lstrcpy(szLabel, "CN=");
			dwTotalRdnLen += 3;
		}
		else
		  if ( !strnicmp((const char*)pbData, szOID_COUNTRY_NAME, cbData) )
		  {
		 	  lstrcpy(szLabel, "C=");
			  dwTotalRdnLen += 2;
		  }
		  else
			if ( !strnicmp((const char*)pbData, szOID_ORGANIZATION_NAME, cbData) )
			{
				lstrcpy(szLabel, "O=");
				dwTotalRdnLen += 2;
			}
			else
			  if ( !strnicmp((const char*)pbData, szOID_ORGANIZATIONAL_UNIT_NAME, cbData) )
			  {
				  lstrcpy(szLabel, "OU=");
				  dwTotalRdnLen += 3;
			  }
			  else
				if ( !strnicmp((const char*)pbData, szOID_TITLE, cbData) )
				{
					lstrcpy(szLabel, "T=");
					dwTotalRdnLen += 2;
				}
				else
				  if( !strnicmp((const char*)pbData, szOID_LOCALITY_NAME, cbData) )
				  {
					 lstrcpy(szLabel, "L=");
					 dwTotalRdnLen += 2;
				  }
				  else
				    if( !strnicmp((const char*)pbData, szOID_RSA_emailAddr, cbData) )
					{
						lstrcpy(szLabel, "E=");
						dwTotalRdnLen += 2;
					}
					else if( !strnicmp((const char*)pbData, szOID_STATE_OR_PROVINCE_NAME, cbData) )
					{
						  lstrcpy(szLabel, "ST=");
						  dwTotalRdnLen += 3;
					}
					else if( !strnicmp((const char*)pbData, szOID_STREET_ADDRESS, cbData) )
					{
						lstrcpy(szLabel, "STREET=");
						dwTotalRdnLen += 7;
					}
					else if( !strnicmp((const char*)pbData, szOID_GIVEN_NAME, cbData) )
					{
						lstrcpy(szLabel, "G=");
						dwTotalRdnLen += 2;
					}
					else if( !strnicmp((const char*)pbData, szOID_INITIALS, cbData) )
					{
						lstrcpy(szLabel, "I=");
						dwTotalRdnLen += 2;
					}
					else if( !strnicmp((const char*)pbData, szOID_SUR_NAME, cbData) )
					{
						lstrcpy(szLabel, "SN=");
						dwTotalRdnLen += 3;
					}
					else if( !strnicmp((const char*)pbData, szOID_DOMAIN_COMPONENT, cbData) )
					{
						lstrcpy(szLabel, "DC=");
						dwTotalRdnLen += 3;
					}
					else
					{
						// We don't support this RDN
						dtSet = dtSet->nextDERTree;
						continue;
					}
		
		// Instead of just using 'cbValueData' check if the 'pbValueData' has any 
		// special characters. If special characters are present then quote the string.
		// The length will then be a bit longer than 'cbValueData'
		bstrValueData = GetRDNData(pbValueData, cbValueData);
		dwTotalRdnLen += lstrlen((TCHAR*)bstrValueData);

		// Copy the value of this OID into the O/P string
		if ( NULL != psz && 0 < csz )
		{
			if ( psz[0] != '\0' )
				dwTotalRdnLen += 2;		// For ';' and 'space'

			
			// Check if enough space is left in the string to copy this OID value
			// 'dwSize' includes the NULL terminating character
			if ( csz - 1 >= dwTotalRdnLen )
			{
				if ( psz[0] != '\0' )
					lstrcat(psz, "; ");

				lstrcat(psz, szLabel);
				UINT len = lstrlen(psz);
				strncpy(&psz[len], (const char*)bstrValueData, lstrlen((TCHAR*)bstrValueData));
				psz[len + lstrlen((TCHAR*)bstrValueData)] = '\0';
			}
			else
			{
				psz[0] = '\0';
				dwTotalRdnLen = 0;
				break;
			}
		}
		else
		{
			if ( NULL != dtSet->nextDERTree )
				dwTotalRdnLen += 2;		// For ';' and 'space'
		}

		dtSet = dtSet->nextDERTree;
	}	// while ( NULL != dtSet )

	return dwTotalRdnLen + 1;
}


/*
	Formats the input RDN by checking for any special characters. If special characters are
	present then the output string is quotted. If any quotes are present in the input string
	then it is double quotted.
*/
#if 0
_bstr_t GetRDNData(PBYTE i_pbRDNData, DWORD i_cbRDNData)
{
	_bstr_t bstrRDN = "";
	BOOL bSpecialChar = FALSE;
	WCHAR wcTemp[2];

	for(UINT i = 0; i < i_cbRDNData; i++)
	{
		if(i_pbRDNData[i] == ',' || i_pbRDNData[i] == '+' || i_pbRDNData[i] == '=' ||
			i_pbRDNData[i] == '"' || i_pbRDNData[i] == '\n' || i_pbRDNData[i] == '<' ||
			i_pbRDNData[i] == '>' || i_pbRDNData[i] == '#' || i_pbRDNData[i] == ';')
				bSpecialChar = TRUE;

		wcTemp[0] = i_pbRDNData[i];
		wcTemp[1] = '\0';

		bstrRDN += wcTemp;

		if(i_pbRDNData[i] == '"')
			bstrRDN += "\"";
	}

	if(bSpecialChar)
		return (_bstr_t("\"") + bstrRDN + _bstr_t("\""));
	else
		return bstrRDN;
}
#else
/*
	In case of UTF-8 the conversion to wide char is incorrect, because we are taking each byte and making
	it a wide char by adding a NULL terminator. If we convert this back to a multibyte string it gives a 
	wrong string. The correct way to do it is take each byte as it is and then let the bstr convert it 
	appropriately to the wide char version using the correct code page.
*/
_bstr_t GetRDNData(PBYTE i_pbRDNData, DWORD i_cbRDNData)
{
	_bstr_t bstrRDN = "";
	BOOL bSpecialChar = FALSE;
	//WCHAR wcTemp[2];
	TCHAR szTemp[4*MAX_PATH];

	for(UINT i = 0, j = 0; i < i_cbRDNData; i++, j++)
	{
		if(i_pbRDNData[i] == ',' || i_pbRDNData[i] == '+' || i_pbRDNData[i] == '=' ||
			i_pbRDNData[i] == '"' || i_pbRDNData[i] == '\n' || i_pbRDNData[i] == '<' ||
			i_pbRDNData[i] == '>' || i_pbRDNData[i] == '#' || i_pbRDNData[i] == ';')
				bSpecialChar = TRUE;

		szTemp[j] = i_pbRDNData[i];
		
		if(i_pbRDNData[i] == '"')
		{
			j++;
			szTemp[j] = '"';
		}
	}

	szTemp[j] = 0;

	WCHAR wcTemp[2*MAX_PATH];

	if(MultiByteToWideChar(CP_UTF8, 0, szTemp, -1, wcTemp, 2*MAX_PATH) == 0)
		bstrRDN = szTemp;
	else
		bstrRDN = wcTemp;

	if(bSpecialChar)
		return (_bstr_t("\"") + bstrRDN + _bstr_t("\""));
	else
		return bstrRDN;
}
#endif


HRESULT	CheckIfWinNTorWin2000(DWORD* o_pdwWindowsVersion)
{
	OSVERSIONINFOEX osvi;
	BOOL bOsVersionInfoEx;

	*o_pdwWindowsVersion = 0;

	// Try calling GetVersionEx using the OSVERSIONINFOEX structure,
	// which is supported on Windows 2000.
	//
	// If that fails, try using the OSVERSIONINFO structure.

	ZeroMemory(&osvi, sizeof(OSVERSIONINFOEX));
	osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);

	if( !(bOsVersionInfoEx = GetVersionEx ((OSVERSIONINFO *) &osvi)) )
	{
		// If OSVERSIONINFOEX doesn't work, try OSVERSIONINFO.

		osvi.dwOSVersionInfoSize = sizeof (OSVERSIONINFO);
		if (! GetVersionEx ( (OSVERSIONINFO *) &osvi) ) 
			return	E_FAIL;;
	}

	if (VER_PLATFORM_WIN32_NT == osvi.dwPlatformId)
	{
		*o_pdwWindowsVersion =	1;
	}

	return S_OK; 
}


HRESULT	UpdatePathIfNecessary (_bstr_t* io_ptbstrPath)
{
	HRESULT				hResult				=	E_FAIL;
	BOOL				bResult				=	FALSE;
	CHAR				szProfilesDirectory [1000];
	DWORD				dwLenOfBuffer =	1000;

	CHAR				szUserName [1000];
	DWORD				dwUserNameLen = 1000;

	HMODULE				hModUserEnv			=	NULL;

	LPFNGetProfilesDirectory	My_GetProfilesDirectory =	NULL;

	_bstr_t				tbstrNewPath;
	_bstr_t				tbstrOldPath;

	_bstr_t				tbstrNewFileName;
	_bstr_t				tbstrOldFileName;

	_bstr_t				tbstrFindFile;

	LONG				lResult				=	0;
	HKEY				hPathKey			=	NULL;

	HANDLE				hFile				=	NULL;
	WIN32_FIND_DATA		win32FindData;

	BOOL				boolSuccessFlag		=	1;


	do
	{
				//	make a copy of the old path
		tbstrOldPath =	*io_ptbstrPath;

				//	load the dll in order to call the funciton
				//
				//	this userenv.dll is not present on win 95/98 and so if the function is 
				//	used directly then the registration fails. so we have to do a load library
				//	followed by teh get proc address for the "GetProfilesDirectory" function
		hModUserEnv =	::LoadLibrary ("userenv.dll");

		if ( NULL == hModUserEnv )
		{
			hResult =	E_USERENV_DLL_MISSING;
			break;
		}

		My_GetProfilesDirectory =	(LPFNGetProfilesDirectory) ::GetProcAddress
									(
										hModUserEnv,
										"GetProfilesDirectoryA"
									);

		if ( NULL == My_GetProfilesDirectory )
		{
			hResult =	E_GETPROC;
			break;
		}

				//	get the profiles directory
		bResult =	My_GetProfilesDirectory
					(
						(LPTSTR) szProfilesDirectory,
						&dwLenOfBuffer
					);
		if ( 0 == bResult )
		{
			hResult =	E_GETPROC;
			break;
		}

				//	get the logged on users name
		bResult =	::GetUserName
					(
						szUserName,
						&dwUserNameLen
					);
		if ( 0 == bResult )
		{
			hResult =	E_GETUSERNAME;
			break;
		}

				//	the new path = UsersProfileDirectory\VeriSign\PTA
		tbstrNewPath =	szProfilesDirectory;
		tbstrNewPath +=	"\\";
		tbstrNewPath +=	szUserName;
		tbstrNewPath +=	"\\";
		tbstrNewPath +=	WIN_NT_OR_WIN_2000_VERISIGN_PTA_PROFILE_PATH;

				//	make sure that the folder exists
		bResult =	CreateRecursiveDirectory (tbstrNewPath);

				//	open the registry key. 
		lResult =	::RegOpenKey
					(
						HKEY_CURRENT_USER,
						PATH_UPGRADE,
						&hPathKey
					);
		if ( ERROR_SUCCESS == lResult )
		{
				//	if open succeeds then it means that the upgrade
				//	(moving of the profiles) is already done.

				//	so just copy the new path to the out variable and quit
			*io_ptbstrPath =	tbstrNewPath;
			hResult =	S_OK;
			break;
		}

				//	the reg open failed. this means that we have to copy all the profiles
				//	from the old path to the new path

				
				//	find *.pta files in the old folder
		tbstrFindFile =	tbstrOldPath;
		tbstrFindFile += "*.pta";

		hFile = ::FindFirstFile
				(
					tbstrFindFile,
					&win32FindData
				);
		if (INVALID_HANDLE_VALUE != hFile)
		{
			while (1)
			{
						//	create the complete file names
						//	oldfolder\filename and newfolder\filename
				tbstrNewFileName =	tbstrNewPath;
				tbstrOldFileName =	tbstrOldPath;
				tbstrNewFileName +=	win32FindData.cFileName;
				tbstrOldFileName +=	win32FindData.cFileName;

						//	move the file
				bResult =	::MoveFile
							(
								tbstrOldFileName,
								tbstrNewFileName
							);
				if ( 0 == bResult )
				{
					boolSuccessFlag =	0;
					break;
				}
				
						//	find the next file
				bResult =	::FindNextFile
							(
								hFile,
								&win32FindData
							);
				if ( 0 == bResult ) 
				{
					if ( ERROR_NO_MORE_FILES == ::GetLastError () )
					{
						break;
					}
					else
					{
						boolSuccessFlag =	0;
						break;
					}
				}
			}
		}

				//	check if the move of all the files was successful
		if ( 0 == boolSuccessFlag )
		{
			hResult =	E_UPGRADE;
			break;
		}

				//	create the registry key indicating that the files are moved
				//	to the new location (basically indicate DON'T DO IT AGAIN)
		lResult =	::RegCreateKey
					(
						HKEY_CURRENT_USER,
						PATH_UPGRADE,
						&hPathKey
					);
		if ( ERROR_SUCCESS != lResult )
		{
			hResult =	E_UPGRADE;
			break;
		}

				//	copy the new path in the out variable
		*io_ptbstrPath =	tbstrNewPath;

		hResult =	S_OK;
	}	while (0);

			//	close the registry key
	if ( NULL != hPathKey )
	{
		::RegCloseKey (hPathKey);
	}

	if ( NULL != hFile )
	{
		::FindClose (hFile);
	}

	return	hResult;
}


void	GetPathFromFileName
(
	_bstr_t				i_tbstrFileName,
	_bstr_t*			o_tbstrPath
)
{
	DWORD				dwFileNameLen			=	0;

	WCHAR			wszFile [MAX_PATH];

	::wcscpy (wszFile, i_tbstrFileName);

	dwFileNameLen =	::wcslen (wszFile);

	for ( int i = dwFileNameLen - 1; i >= 0; i -- )
	{
		if ( wszFile [i] == L'\\' || wszFile [i] == L'/' )
		{
			wszFile [i] = L'\0';
			break;
		}
	}

	// Replace any forward slash by back slash
	for ( int j = i - 1; j >= 0; j--)
	{
		if ( wszFile [j] == L'/' )
			wszFile [j] = L'\\';
	}

	*o_tbstrPath =	wszFile;

	return;
}


BOOL	CreateRecursiveDirectory
(
	_bstr_t			i_tbstrDirToCreate
)
{
	WIN32_FIND_DATA wfd;
	_bstr_t			tbstrDirectory;
	_VS_DWORD		dwDirectoryLen;

	tbstrDirectory =	i_tbstrDirToCreate;
	dwDirectoryLen = wcslen ( tbstrDirectory );	

	if(dwDirectoryLen == 2)       // root dirs "a:"
		return TRUE;

	HANDLE hDir = FindFirstFile(tbstrDirectory, &wfd);
	if(hDir != INVALID_HANDLE_VALUE)
	{
			FindClose(hDir);
			return TRUE;
	}

	WCHAR wszDirParent[MAX_PATH];

	::wcscpy(wszDirParent, tbstrDirectory);

	for ( int i = dwDirectoryLen - 1; i >= 0; i -- )
	{
		if ( wszDirParent [i] == L'\\' )
		{
			wszDirParent [i] = L'\0';
			break;
		}
	}

	if(CreateRecursiveDirectory(wszDirParent))
			if(CreateDirectory(tbstrDirectory, NULL))
			{
					return TRUE;
			}
			else
					return FALSE;

	return FALSE;
}


/*
	Checks if the spedified path is valid. The checks performed are whether the drive is valid and
	whether the path is well formed

	eg. the path is expected to be "drive:\path[...]"
*/
BOOL IsValidPath(const WCHAR* i_lpszPath)
{
	BOOL bRetVal = FALSE;

	do
	{
		if(!i_lpszPath)
			break;

		// Check if i_lpszPath[0] is a logical drive
		if(!IsLogicalDrive(i_lpszPath[0]))
			break;

		if(i_lpszPath[1] != L':')
			break;

		if(i_lpszPath[2] != L'\\')
			break;

		if(i_lpszPath[3] == L'\0')
			break;

		bRetVal = TRUE;

	}while(0);

	return bRetVal;
}


BOOL IsLogicalDrive(WCHAR i_wcDrive)
{
	BOOL bRetVal = FALSE;
	DWORD dwDrives = 0;
	INT nShift = 0;

	do
	{
		dwDrives = GetLogicalDrives();
		if(dwDrives == 0)
			break;

		nShift = towupper(i_wcDrive) - L'A';

		dwDrives = dwDrives >> nShift;

		if((dwDrives & 1) == TRUE)
			bRetVal = TRUE;

	}while(0);

	return bRetVal;
}


HRESULT _CreateKeyFromPasswdAndSalt(PBYTE i_pbPassword, DWORD i_dwPassword, PBYTE i_pbSalt, DWORD i_dwSalt, PBYTE *o_pbKey, PDWORD o_pdwKey)
{
	HRESULT hr = S_OK;
	void* pvoidContext = NULL;
	int	nResult = 999;
	BYTE pbPasswdHash[VS_CSP_SHA1_LEN], *pbPasswdHashAndSalt = NULL, pbFinalHash[VS_CSP_SHA1_LEN];
	
	do
	{
		// Create the SHA1 hash of the password
		nResult = HashBegin(VS_SHA_1, &pvoidContext);
		if(nResult != 0)
		{
			hr = NTE_FAIL;
			break;
		}

		nResult = HashData(VS_SHA_1, pvoidContext, i_pbPassword, i_dwPassword);
		if(nResult != 0)
		{
			hr = NTE_FAIL;
			break;
		}

		nResult = HashEnd(VS_SHA_1, pvoidContext, pbPasswdHash, VS_CSP_SHA1_LEN);
		if(nResult != 0)
		{
			hr = NTE_FAIL;
			break;
		}

		pbPasswdHashAndSalt = new BYTE[VS_CSP_SHA1_LEN + i_dwSalt];
		if(pbPasswdHashAndSalt == NULL)
		{
			hr = NTE_FAIL;
			break;
		}

		memcpy(pbPasswdHashAndSalt, pbPasswdHash, VS_CSP_SHA1_LEN);
		memcpy(pbPasswdHashAndSalt + VS_CSP_SHA1_LEN, i_pbSalt, i_dwSalt);

		// Create the SHA1 hash of the password and salt
		nResult = HashBegin(VS_SHA_1, &pvoidContext);
		if(nResult != 0)
		{
			hr = NTE_FAIL;
			break;
		}

		nResult = HashData(VS_SHA_1, pvoidContext, (unsigned char*)pbPasswdHashAndSalt, (unsigned int)(VS_CSP_SHA1_LEN + i_dwSalt));
		if(nResult != 0)
		{
			hr = NTE_FAIL;
			break;
		}

		nResult = HashEnd(VS_SHA_1, pvoidContext, pbFinalHash, VS_CSP_SHA1_LEN);
		if(nResult != 0)
		{
			hr = NTE_FAIL;
			break;
		}

		// Return first 16 bytes of the hash as the key
		*o_pbKey = new BYTE[16];
		if(!*o_pbKey)
		{
			hr = NTE_FAIL;
			break;
		}

		memcpy(*o_pbKey, pbFinalHash, 16);
		*o_pdwKey = 16;

	}while(0);

	if(pbPasswdHashAndSalt)
	{
		delete pbPasswdHashAndSalt;
		pbPasswdHashAndSalt = NULL;
	}

	return hr;
}



HRESULT PutDataInSequenceFunc
(
	const BYTE*			i_cpbyteData,
	const DWORD			i_cdwDataLen,
	const DWORD			i_cdwAlgID,
	BYTE**				o_ppbyteDataInSequence,
	DWORD*				o_pdwDataInSequenceLen
)
{
	HRESULT						hResult						=	E_FAIL;

//	BYTE*						pbyteRevHash				=	NULL;
//	DWORD						dwRevHashLen				=	0;

	while (1)
	{
		CNull					CNULL;

				//	put the data in an octet string
		COctetString	CosHashData ( (_DWORD) i_cdwDataLen, (_BYTE*) i_cpbyteData );

				//	create ObjectIdentifiers for all the algos
		CObjectIdentifier	CoiSHA1
					(
						(_DWORD) ::lstrlen(VS_SHA1_OID),
						(_BYTE*) VS_SHA1_OID
					);

		CObjectIdentifier	CoiMD2
					( 
						(_DWORD) ::lstrlen(VS_MD2_OID),
						(_BYTE*) VS_MD2_OID
					);

		CObjectIdentifier	CoiMD5
					( 
						(_DWORD) ::lstrlen(VS_MD5_OID),
						(_BYTE*) VS_MD5_OID
					);

				//			AlgorithmIdentifier ::= SEQUENCE {
				//								  algorithm OBJECT IDENTIFIER,
				//								  parameters ANY DEFINED BY algorithm OPTIONAL }
		CSequence			CSeqAlgoId;

				//	DigestInfo ::= SEQUENCE {
				//						digestAlgorithm AlgorithmIdentifier,
				//						digest OCTET STRING
				//					}
		CSequence			CSeqDataInSequence;

				//	depending on the algo add the appropriate ObjectIdentifier in the algo id sequence
		switch ( i_cdwAlgID )
		{
			case	VS_SHA_1:
				CSeqAlgoId =	CoiSHA1;

				break;

			case	VS_MD2:
				CSeqAlgoId =	CoiMD2;

				break;

			case	VS_MD5:
				CSeqAlgoId =	CoiMD5;

				break;

			default:
				break;
		}	//	end		switch ( i_cdwAlgID )

		CSeqAlgoId += CNULL;

				//	the data in sequence is basically the DigestInfo
		CSeqDataInSequence += CSeqAlgoId;
		CSeqDataInSequence += CosHashData;

		*o_pdwDataInSequenceLen =	(CSeqDataInSequence.BaseDERBlob) -> cbData;
		*o_ppbyteDataInSequence =	new BYTE [*o_pdwDataInSequenceLen];
		CHECK_ALLOCATED_MEMORY ( *o_ppbyteDataInSequence )

		memcpy
		(
			(void*) *o_ppbyteDataInSequence,
			(const void*) (CSeqDataInSequence.BaseDERBlob) -> pbData,
			*o_pdwDataInSequenceLen
		);

		hResult =	VS_SUCCESS;
		break;
	}	//	end		while (1)

//	VSCSP_CHECK_FOR_NULL_ERASE_AND_DELETE (pbyteRevHash, dwRevHashLen)

	return	hResult;
}	