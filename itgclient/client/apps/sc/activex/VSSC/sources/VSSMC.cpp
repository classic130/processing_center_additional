// VSSMC.cpp : Implementation of CVSSC

#include "stdafx.h"
#include "VSSC.h"
#include "VSSMC.h"
#include "vssc_smime.h"


using namespace std ;
#include <list>
typedef list<char *> LISTSTR;

extern g_GlobalMemoryManagement		*gp_GMemMgmt;
extern CListUserInfo				*g_pEncryptCertInGM;
extern CListUserInfo				*g_pSignerCertInGM;
extern DWORD                        g_dwCertTimeOut;
extern DWORD						g_dwAppErr;
 

extern CAppContext                  *gp_AppContext;

IVSPTA *pVSPTA=NULL;

CVSSC::CVSSC()
	{
		//Agg
		m_pUnkObj=NULL;

		
		m_bInitialized=FALSE;
		m_bFoundPTAVer=FALSE;
		m_bResolveFirst=FALSE;
		bComposeCalled=FALSE;
		bUseInternetData=FALSE;


		pbURLContent=NULL;

		/////
		g_dwAppErr=0;
		
		dwRetBufferSize=0;
		g_AttachedFiles=NULL;
		
		if(g_AttachedFiles==NULL)
			g_AttachedFiles=new ATTACH_FILE_INFO;

		m_pMsg=new CMsg;
		pDecCertInfo=new DECCERT_INFO;

		///////initialize
		m_pMsg->m_bstrAttachFileNameList=_bstr_t("");
		m_pMsg->m_FILEINFO_AttachFileInfoList=NULL;
		
}

CVSSC::~CVSSC()
{
		DELETE_MEMORY(m_pMsg)

        ////delete Attachinfo class
		if(g_AttachedFiles!=NULL)
				freeAttachInfo(g_AttachedFiles);

        DELETE_MEMORY(g_AttachedFiles)

		FREE_MEMORY(pbURLContent)
		
		m_pUnkObj=NULL;
		m_bInitialized=FALSE;
		m_bFoundPTAVer=FALSE;
		m_bResolveFirst=FALSE;
		g_dwAppErr=0;

		DELETE_MEMORY(pDecCertInfo)

		
}


//Agg
HRESULT CVSSC::FinalConstruct()
{
	IUnknown* pUnkOuter = GetControllingUnknown();
	HRESULT hRes = CoCreateInstance(CLSID_VSPTA, pUnkOuter, CLSCTX_INPROC_SERVER, IID_IUnknown, (void**)&m_pUnkObj);
	if(hRes != S_OK)
		return hRes;

	return S_OK;	
}
void CVSSC::FinalRelease()
{
	
	if(m_pUnkObj)
	{
		m_pUnkObj.Release();
		m_pUnkObj = NULL;
	}
	
}
//Agg
IDispatch* CVSSC::_GetInterface(REFIID i_refIId)
{
	void* pvInterface = NULL;
	QueryInterface(i_refIId, &pvInterface);
	return (IDispatch*)pvInterface;
}

STDMETHODIMP CVSSC::get_IVSSCPTA(IDispatch **pVal)
{
	hr = S_OK;
	IVSPTADllApi *pPTADllApi = NULL;
	
	VARIANT varClientSite;
	VARIANT varGetClientSite;
	
	do
	{

		VariantInit(&varClientSite);
		VariantInit(&varGetClientSite);

		hr=CheckEnv(CHECK_INIT|CHECK_PTAVER);
		CHECK_HRESULT_BREAK

		*pVal = NULL;
		*pVal = (IDispatch*)_GetInterface(IID_IVSPTA);
		if(!*pVal)
		{
			hr = E_NOINTERFACE;
			break;
		}
		
	
	
		(*pVal)->QueryInterface(IID_IVSPTADllApi, (void **)&(pPTADllApi));
		if(!pPTADllApi)
		{
			hr = E_NOINTERFACE;
			break;
		}

		hr = pPTADllApi->get_OleClientSite(&varGetClientSite);
		if(hr==S_OK)
			break;

		if(m_spClientSite==NULL)
		{
			hr=S_OK;
			break;
		}

		varClientSite.vt = VT_UNKNOWN;
		varClientSite.punkVal = m_spClientSite;
	
		hr = pPTADllApi->put_OleClientSite(varClientSite);
		if(hr!=S_OK)
			break;
	
		


	}while(0);
		
    if(pPTADllApi)
	{
		pPTADllApi->Release();
		pPTADllApi = NULL;
	}

	VariantClear(&varClientSite);
	VariantClear(&varGetClientSite);
	
	return hr;

}

void CVSSC::_SetErrorInfo(HRESULT hresultErr)
{
	TCHAR tstrErrStringBuff[MAX_ERR_DESC_SIZE]; 
	_bstr_t tbstrErrStringBuff("");
	int nErrStringId=0;

	//Get the error string id for the hresult
	switch(hresultErr)
	{
	case E_INITIALIZED :
		//nErrStringId = IDS_ERR_INITIALIZED;
		break;
	
	case E_VSSC_EMPTYARGS :
		//nErrStringId = IDS_ERR_EMPTYARGS;
		break;

	case E_INVALIDFLAGS :
		//nErrStringId = IDS_ERR_INVALIDFLAGS;
		break;

	//case E_VSSC_INVALIDARGS :
		//nErrStringId = IDS_ERR_INVALIDARGS;
	//	break;
	
	default :
		nErrStringId = 0;
		break;
	}

	if(nErrStringId)
	{
		//Get the error string from the string table
		//Fixed Size
		LoadString(_Module.m_hInst, nErrStringId, tstrErrStringBuff, 1024);

		//Convert it from ascii to unicode
		tbstrErrStringBuff = tstrErrStringBuff;

		ICreateErrorInfo* pCreateErrInfo;
		CreateErrorInfo(&pCreateErrInfo);
		pCreateErrInfo->SetDescription(tbstrErrStringBuff);
		SetErrorInfo(0,(IErrorInfo*)pCreateErrInfo);
		pCreateErrInfo->Release();
	}
	

	return;

}

STDMETHODIMP CVSSC::Initialize(VARIANT *i_pMsgObjID, VARIANT *i_pMode,VARIANT* i_pvarAppStatus)
{
     hr=S_OK;

	_bstr_t		bstrProtocolName;
	_bstr_t		bstrHostName;


	try
	{

		do
		{
			
			g_dwAppErr=0;

			if(m_bInitialized)
			{
				hr=E_VSSC_INITIALIZED;
				break;
			}

			///////////Allocate the global memory
			if(g_pEncryptCertInGM==NULL)
					g_pEncryptCertInGM=new CListUserInfo;

			if(NULL==gp_GMemMgmt)
					gp_GMemMgmt=new g_GlobalMemoryManagement;

			if(NULL==g_pSignerCertInGM)
					g_pSignerCertInGM=new CListUserInfo;

			if(NULL==gp_AppContext)
					gp_AppContext=new CAppContext;


			/////////////////////////////////////////////////



			/*Get the hostname and the protocol.*/
			bstrHostName = "";
			bstrProtocolName = "";
			if((hr=_GetHostAndProtocol(bstrHostName, bstrProtocolName)) != S_OK)
			{
				return hr; //Note we dont set the err info because the only erro return values 
						   //is the standard E_FAIL
			}

			
			if(gp_AppContext->bstrHostName.length()==0 && gp_AppContext->bstrProtocolName.length()==0)
			{
				gp_AppContext->bstrHostName=bstrHostName;
				gp_AppContext->bstrProtocolName=bstrProtocolName;
			}
			else
			{

				if(!(gp_AppContext->bstrHostName==bstrHostName)&&
					(gp_AppContext->bstrProtocolName==bstrProtocolName))
				{
					hr=E_HOST_NOT_MATCH;
					break;
				}

			}
			

			
			if ( 0 == i_pMsgObjID -> iVal )
			{
				if ( 0 > i_pMode->iVal || 1 < i_pMode->iVal )
				{
					hr =	E_VSSC_INVALID_MODE;
					break;
				}

					//	since msg id is 0, it means that its a new 
					//	message context. there is NOTHING in the
					//	global memory

					//	seed the random number with time
				::srand( (unsigned)time( NULL ) );
				m_pMsg->m_iMsgObjID =	::rand();

				m_pMsg->m_dwMessageMode = i_pMode->iVal;
			}
			else
			{
					//	since msg id is NOT 0, it means that the
					//	msg context is already set in the global
					//	memory

				m_pMsg->m_iMsgObjID =	i_pMsgObjID -> iVal;

					//	read everything from the object
					//
					//	all these functions will check ifthe required 
					//	information exists in the global memory. 
					//	if NOT they will return S_OK
					//	copying anything in the class
				hr=GM_GetMsgHeader(m_pMsg);
				CHECK_HRESULT_BREAK;
				hr=GM_GetMsgBody(m_pMsg);
				CHECK_HRESULT_BREAK;
				hr=GM_GetMsgAttFileNames(m_pMsg,g_AttachedFiles);
				CHECK_HRESULT_BREAK;
				hr=GM_GetMsgEntity(m_pMsg);
				CHECK_HRESULT_BREAK;
	//			hr=GM_GetAttachments(m_pMsg);
	//			CHECK_HRESULT_BREAK;
	//			hr=GM_GetSMIME(m_pMsg);
	//			CHECK_HRESULT_BREAK;


				/************

				/////Delete From Memory
				hr=gp_GMemMgmt->DeleteObjectNode(
							(BYTE*)&m_pMsg->m_iMsgObjID,
							sizeof(int)
							);
				CHECK_HRESULT_BREAK

				
				::srand( (unsigned)time( NULL ) );
				m_pMsg->m_iMsgObjID =	::rand();

				*************/

				//Do Initialization

				bComposeCalled=TRUE;
				SetComposeMode ();
			}
			
			m_bInitialized = TRUE;
		
		} while (0);
	}
	catch(...)
	{
		hr=E_UNEXPECTED;
	}

	i_pvarAppStatus->vt=VT_I4;
	i_pvarAppStatus->lVal=g_dwAppErr;

	return hr;
}

HRESULT CVSSC::CheckEnv(short nCheck)
{

	hr=S_OK;
	
	/////Addtion Error info
	g_dwAppErr=0;

	do
	{
		if(nCheck & CHECK_INIT)
		{
			if(!m_bInitialized)
			{
				hr=E_VSSC_INITIALIZED;
				g_dwAppErr=E_UNABLE_TO_INIT;
				break;
			}

			if(!gp_AppContext->bstrHostName.length())
			{
				hr=E_VSSC_INITIALIZED;
				g_dwAppErr=E_UNABLE_TO_INIT;
				break;
			}
			if(!gp_AppContext->bstrProtocolName.length())
			{
				hr=E_VSSC_INITIALIZED;
				g_dwAppErr=E_UNABLE_TO_INIT;
				break;
			}
			

		}

		if(nCheck & CHECK_PTAVER)
		{
			if(!m_bFoundPTAVer)
			{
				hr=E_NOSUPPORTED_PTAVER;
				g_dwAppErr=E_UNABLE_TO_INIT;
				break;
			}
		}

		if(nCheck & CHECK_CERTURL)
		{
			if(!m_pMsg->m_bstrCertResolutionURL.length())
			{
				hr=E_CERTRESOLVEURL_NOTFOUND;
				g_dwAppErr=E_UNABLE_TO_INIT;
				break;
			}
			
		}

		if(nCheck & CHECK_SCTYPE)
		{
			if(!m_pMsg->m_SCType.length())
			{
				hr=E_SCTYPE_NOTFOUND;
				g_dwAppErr=E_UNABLE_TO_INIT;
				break;
			}
			
		}

		if(nCheck & CHECK_RESFIRST)
		{
			if(!m_bResolveFirst)
			{
				hr=E_FIRSTNOT_CALLED;
				g_dwAppErr=E_UNABLE_TO_INIT;
				break;
			}
			
		}


	

	}
	while(0);
	return hr;

}

HRESULT CVSSC::_GetHostAndProtocol(_bstr_t& tbstrHostName, _bstr_t& tbstrProtocolName)
{
	HRESULT retVal = S_OK;

	BSTR bstrHostName;
	BSTR bstrProtocolName;
	CComPtr <IOleContainer>		spContainer;
	CComPtr <IOleClientSite>	spCurrClientSite = NULL;

	if(m_spClientSite)
	{
		spCurrClientSite = m_spClientSite;
	}
	else if(m_spOuterClientSite)
	{
		spCurrClientSite = m_spOuterClientSite;
	}

	if(spCurrClientSite)
	{
		spCurrClientSite->GetContainer (&spContainer);

		CComQIPtr<IHTMLDocument2, &IID_IHTMLDocument2> spDoc (spContainer);
		CComPtr <IHTMLLocation> spHtmlLocation;

		if (spDoc)
		{
			spDoc->get_location (&spHtmlLocation);

			spHtmlLocation->get_hostname (&bstrHostName);
			spHtmlLocation->get_protocol (&bstrProtocolName);

			tbstrHostName		=	bstrHostName;
			tbstrProtocolName	=	bstrProtocolName;
		}
		else
			retVal = E_FAIL;
	}


	return retVal;
}




STDMETHODIMP CVSSC::Compose(VARIANT* i_pvarAppStatus)
{
	
	_bstr_t                     bstrSep(_T(","));


	hr=CheckEnv(CHECK_INIT|CHECK_PTAVER);
	if(hr!=S_OK)
		return hr;

	pVSPTA = (IVSPTA*)_GetInterface(IID_IVSPTA);
	if(!pVSPTA)
	{
		return E_NOINTERFACE;
			
	}

//	hr=E_VSSC_EMPTYARGS;
//	g_dwAppErr=E_PTA_ERR;
//	i_pvarAppStatus->vt=VT_I4;
//	i_pvarAppStatus->lVal=g_dwAppErr;
//	return hr;

	
	try
	{

		

		bComposeCalled=TRUE;

		CAttachInfo *pAttachInfo;
		ATTACH_FILE_INFO::iterator i;

		if (!g_AttachedFiles->empty())
		{

			m_pMsg->m_bstrAttachFileNameList="";
		
			for (i =  g_AttachedFiles->begin(); i != g_AttachedFiles->end(); ++i)
			{
				pAttachInfo=(*i);

				m_pMsg->m_bstrAttachFileNameList+=pAttachInfo->m_bstrPathName;
				m_pMsg->m_bstrAttachFileNameList+=bstrSep;
      
			}
		}
		else
		{
			m_pMsg->m_bstrAttachFileNameList=_bstr_t("");
		}

		
		switch(dwMsgType)
		{
			case VSSC_MSG_PLAINTEXT:  //plain text
				::MessageBox(NULL,"Not Implemented yet","VSSC",MB_OK);
				return E_FAIL;
				
			break;

			case VSSC_MSG_SIGNED:  //sign 
				//m_pMsg->m_nSignAlgId=SCRIPT_HASH_MD5;
				m_pMsg->m_bstrSMIMECapabilities=_bstr_t(L"RC2CBC,SHA1,MD5");
										
				hr=VSSC_CreateSignedMessage(pVSPTA,m_pMsg);
				if(hr!=S_OK)
				{
					break;

				}
				break;
				case VSSC_MSG_ENCRYPT:  //encrypt
						
					hr=VSSC_CreateEncryptedMessage(m_pMsg);
					if(hr!=S_OK)
					{
						break;
					}
					break;

				case VSSC_MSG_SIGN_ENCRYPT:  //signed encrypt
				
				
				m_pMsg->m_bstrSMIMECapabilities=_bstr_t(L"RC2CBC,SHA1,MD5");
							
				hr=VSSC_CreateSignedMessage(pVSPTA,m_pMsg);
				if(hr!=S_OK)
				{
					break;
				}
				hr=VSSC_CreateEncryptedMessage(m_pMsg);
				if(hr!=S_OK)
				{
					break;
				}
				break;
		}
	}
	catch(...)
	{
		hr=E_UNEXPECTED;
	}

		
	if(pVSPTA)
	{
		//pProfMgmt->CloseProfile();
		//pVSPTA->Close();
		pVSPTA->Release();
		pVSPTA = NULL;
	}

	/*
	/////Attachmentment info
	if(m_pMsg->m_FILEINFO_AttachFileInfoList!=NULL)
	{
		freeFileInfo(m_pMsg->m_FILEINFO_AttachFileInfoList);
		m_pMsg->m_FILEINFO_AttachFileInfoList=NULL;
	}
	*/

	/////To the List of file Name
	if(g_AttachedFiles!=NULL)
				freeAttachInfo(g_AttachedFiles);

	DELETE_MEMORY(g_AttachedFiles)

	FreeCertList(&m_pMsg->m_SignerCertList);
	FreeCertList(&m_pMsg->m_EncryptCertList);

	/////Deleting object from memory

	gp_GMemMgmt->DeleteObjectNode(
						(BYTE*)&m_pMsg->m_iMsgObjID,
						sizeof(int)
						);
	//CHECK_HRESULT_BREAK

	i_pvarAppStatus->vt=VT_I4;
	i_pvarAppStatus->lVal=g_dwAppErr;

	return hr;
}



STDMETHODIMP CVSSC::get_ToRecipientsInfo(VARIANT *pVal)
{

	hr = S_OK;

	do
	{
		hr=CheckEnv(CHECK_INIT|CHECK_PTAVER);
		CHECK_HRESULT_BREAK


		if(!bComposeCalled)
		{
			 pVal->bstrVal=NULL;
			 return hr;
		}

		pVal->vt = VT_BSTR;

		if(m_pMsg->m_bstrTo.length()>0)
					pVal->bstrVal=m_pMsg->m_bstrTo.copy();
		else
					pVal->bstrVal=NULL;
	}
	while(0);
	

	return hr;
}

STDMETHODIMP CVSSC::put_ToRecipientsInfo(VARIANT newVal)
{
	
	hr = S_OK;

	do
	{
		hr=CheckEnv(CHECK_INIT|CHECK_PTAVER);
		CHECK_HRESULT_BREAK

		///Check for BSTR//////
		if(newVal.vt != VT_BSTR)
		{
			//return Invalid argument;
			hr=E_VSSC_INVALIDARGS;
			return hr;
		}

		m_pMsg->m_bstrTo=newVal.bstrVal;
	}
	while(0);

	return hr;

}

STDMETHODIMP CVSSC::get_CcRecipientsInfo(VARIANT *pVal)
{
	hr = S_OK;

	do
	{
		hr=CheckEnv(CHECK_INIT|CHECK_PTAVER);
		CHECK_HRESULT_BREAK

		if(!bComposeCalled)
		{
			 pVal->bstrVal=NULL;
			 return hr;
		}

		pVal->vt = VT_BSTR;
		if(m_pMsg->m_bstrCc.length()>0)
				pVal->bstrVal=m_pMsg->m_bstrCc.copy();
		else
				pVal->bstrVal=NULL;
	}
	while(0);
	
	return hr;

	
}

STDMETHODIMP CVSSC::put_CcRecipientsInfo(VARIANT newVal)
{

	hr = S_OK;
	
	do
	{
		hr=CheckEnv(CHECK_INIT|CHECK_PTAVER);
		CHECK_HRESULT_BREAK

		///Check for BSTR//////
		if(newVal.vt != VT_BSTR)
		{
			//return Invalid argument;
		}
		m_pMsg->m_bstrCc=newVal.bstrVal;
	}
	while(0);

	
	return hr;
	
}

STDMETHODIMP CVSSC::get_BccRecipientsInfo(VARIANT *pVal)
{
	hr = S_OK;
	do
	{
		hr=CheckEnv(CHECK_INIT|CHECK_PTAVER);
		CHECK_HRESULT_BREAK


		if(!bComposeCalled)
		{
			 pVal->bstrVal=NULL;
			 return hr;
		}

		pVal->vt = VT_BSTR;
		if(m_pMsg->m_bstrBcc.length()>0)
					pVal->bstrVal=m_pMsg->m_bstrBcc.copy();
		else
					pVal->bstrVal=NULL;
	}
	while(0);

	return hr;
}

STDMETHODIMP CVSSC::put_BccRecipientsInfo(VARIANT newVal)
{
	
	hr = S_OK;
	do
	{
		hr=CheckEnv(CHECK_INIT|CHECK_PTAVER);
		CHECK_HRESULT_BREAK

		///Check for BSTR//////
		if(newVal.vt != VT_BSTR)
		{
			//return Invalid argument;
		}

		m_pMsg->m_bstrBcc=newVal.bstrVal;
	}
	while(0);
		return hr;
	
}

STDMETHODIMP CVSSC::get_FromInfo(VARIANT *pVal)
{
	hr = S_OK;
	
	do
	{
		hr=CheckEnv(CHECK_INIT|CHECK_PTAVER);
		CHECK_HRESULT_BREAK

		if(!bComposeCalled)
		{
			 pVal->bstrVal=NULL;
			 return hr;
		}

		pVal->vt = VT_BSTR;
		if(m_pMsg->m_bstrFrom.length()>0)
				pVal->bstrVal=m_pMsg->m_bstrFrom.copy();
		else
				pVal->bstrVal=NULL;
	}
	while(0);

	return hr;
	
}

STDMETHODIMP CVSSC::put_FromInfo(VARIANT newVal)
{
	
	hr = S_OK;

	do
	{
		hr=CheckEnv(CHECK_INIT|CHECK_PTAVER);
		CHECK_HRESULT_BREAK

		///Check for BSTR//////
		if(newVal.vt != VT_BSTR)
		{
			//return Invalid argument;
			hr=E_VSSC_INVALIDARGS;
			break;
		}

		m_pMsg->m_bstrFrom=newVal.bstrVal;

		
	}
	while(0);

	
	return hr;
}

STDMETHODIMP CVSSC::get_Subject(VARIANT *pVal)
{
	hr = S_OK;

	do
	{
		hr=CheckEnv(CHECK_INIT|CHECK_PTAVER);
		CHECK_HRESULT_BREAK


		if(!bComposeCalled)
		{
			 pVal->bstrVal=NULL;
			return hr;
		}

		pVal->vt = VT_BSTR;
		if(m_pMsg->m_bstrSubject.length()>0)
					pVal->bstrVal=m_pMsg->m_bstrSubject.copy();
		else
					pVal->bstrVal=NULL;
	}
	while(0);

	return hr;
	
}

STDMETHODIMP CVSSC::put_Subject(VARIANT newVal)
{

	hr = S_OK;

	do
	{
		

		///Check for BSTR//////
		if(newVal.vt != VT_BSTR)
		{
			//return Invalid argument;
			hr=E_VSSC_INVALIDARGS;
			break;
		}

		hr=CheckEnv(CHECK_INIT|CHECK_PTAVER);
		CHECK_HRESULT_BREAK

		m_pMsg->m_bstrSubject=newVal.bstrVal;
		
		
	}
	while(0);

	return hr;

}

STDMETHODIMP CVSSC::get_MsgType(VARIANT *pVal)
{
	hr=S_OK;
	do
	{
		hr=CheckEnv(CHECK_INIT|CHECK_PTAVER);
		CHECK_HRESULT_BREAK

		pVal->vt=VT_I2;

		if(m_pMsg->m_dwMsgType==VSSC_MSG_SIGNED)
			pVal->iVal=1;

		if(m_pMsg->m_dwMsgType==VSSC_MSG_ENCRYPT)
			pVal->iVal=2;

		if(m_pMsg->m_dwMsgType==VSSC_MSG_SIGN_ENCRYPT)
			pVal->iVal=3;
	}
	while(0);

	


	return S_OK;
}

STDMETHODIMP CVSSC::put_MsgType(VARIANT newVal)
{

   hr=S_OK;
   do
   {
	   hr=CheckEnv(CHECK_INIT|CHECK_PTAVER);
	   CHECK_HRESULT_BREAK
	
		if(newVal.vt == VT_I2)
		{
			dwMsgType=newVal.iVal;
			m_pMsg->m_dwMsgType=newVal.iVal;	
		}
		
   }
   while(0);

   return hr;	

}



STDMETHODIMP CVSSC::get_Body(VARIANT *pVal)
{
	hr = S_OK;

	do
	{
		hr=CheckEnv(CHECK_INIT|CHECK_PTAVER);
		CHECK_HRESULT_BREAK


		if(!bComposeCalled)
		{
			 pVal->bstrVal=NULL;
			 return hr;
		}

		pVal->vt = VT_BSTR;
		if(m_pMsg->m_bstrBody.length()>0)
				pVal->bstrVal=m_pMsg->m_bstrBody.copy();
		else
				pVal->bstrVal=NULL;
		

	}
	while(0);

	return hr;
}

STDMETHODIMP CVSSC::put_Body(VARIANT newVal)
{

	hr = S_OK;
	do
	{
		hr=CheckEnv(CHECK_INIT|CHECK_PTAVER);
		CHECK_HRESULT_BREAK

		///Check for BSTR//////
		if(newVal.vt != VT_BSTR)
		{
			//return Invalid argument;
			hr=E_VSSC_INVALIDARGS;
			break;
		}

		m_pMsg->m_bstrBody=newVal.bstrVal;
		
	}
	while(0);



	return hr;
}

STDMETHODIMP CVSSC::get_GetMsg(VARIANT *pVal)
{
	hr = S_OK;
	do
	{
		hr=CheckEnv(CHECK_INIT);
		CHECK_HRESULT_BREAK

		pVal->vt = VT_BSTR;
		if(m_pMsg->m_bstrSMIMEMsg.length()>0)
			pVal->bstrVal=m_pMsg->m_bstrSMIMEMsg.copy();
		else
			pVal->bstrVal=NULL;
	}
	while(0);

	return hr;
}

STDMETHODIMP CVSSC::get_Date(VARIANT *pVal)
{
	hr = S_OK;
	do
	{
		hr=CheckEnv(CHECK_INIT|CHECK_PTAVER);
		CHECK_HRESULT_BREAK

		if(!bComposeCalled)
		{
			 pVal->bstrVal=NULL;
			 return hr;
		}

		pVal->vt = VT_BSTR;
		if(m_pMsg->m_bstrDate.length()>0)
				pVal->bstrVal=m_pMsg->m_bstrDate.copy();
		else
				pVal->bstrVal=NULL;
	}
	while(0);

	return hr;
}

STDMETHODIMP CVSSC::put_Date(VARIANT newVal)
{
	hr = S_OK;

	do
	{
		hr=CheckEnv(CHECK_INIT|CHECK_PTAVER);
		CHECK_HRESULT_BREAK

		///Check for BSTR//////
		if(newVal.vt != VT_BSTR)
		{
			//return Invalid argument;
			hr=E_VSSC_INVALIDARGS;
			break;
		}

		m_pMsg->m_bstrDate=newVal.bstrVal;
		
		
	}
	while(0);

	return hr;

	
}

STDMETHODIMP CVSSC::get_CryptStatus(VARIANT *pVal)
{
	pVal->vt=VT_I4;
	pVal->lVal=m_pMsg->m_dwCryptStatus;
	return S_OK;
}

STDMETHODIMP CVSSC::SelectAttachments(VARIANT* i_pvarAppStatus)
{
   hr=S_OK;
   
   long	lErrMsg = 0;
  
   OPENFILENAME ofn;
   /////Fix size
   
   FILEINFO	  *pTmpFileInfo=NULL;

   /////100 files
   TCHAR sfile[MAX_PATH*10];
   TCHAR sfileTitle[MAX_PATH*10];

   

   DWORD  dwFilePathNameSize=MAX_PATH*10;

   FILE *stream = NULL;

   try
   {

	   hr=CheckEnv(CHECK_INIT|CHECK_PTAVER);
	   if(hr!=S_OK)
		   return hr;

	   CAttachInfo *pInsAttachInfo,*pAttachInfo;
	   ATTACH_FILE_INFO::iterator i;

	   ZeroMemory(&ofn, sizeof(ofn));
   
	   ZeroMemory(sfile, sizeof(TCHAR)*dwFilePathNameSize);
	   ZeroMemory(sfileTitle,sizeof(TCHAR)*dwFilePathNameSize);
  
	   sfile[0] = '\0';
	   sfileTitle[0]='\0';
  



	   // Initialize OPENFILENAME structure.
	   ofn.lStructSize = sizeof(ofn);
	   ofn.hwndOwner = GetFocus(); 
	   ofn.lpstrFile = sfile; 
	   ofn.nMaxFile = dwFilePathNameSize;
	   ofn.lpstrFilter = NULL;
	   ofn.nFilterIndex = 1;
	   ofn.lpstrTitle = TEXT("Please Select The Attachment");
	   ofn.lpstrInitialDir = NULL;
	   ofn.lpstrCustomFilter = NULL;
	   ofn.nMaxCustFilter = 0;
	   ofn.lpstrFileTitle = sfileTitle;
	   ofn.nMaxFileTitle = sizeof(TCHAR)*dwFilePathNameSize;
	   ofn.nFileOffset = 0;
	   ofn.nFileExtension = 0;
	   ofn.lpstrDefExt = NULL;
	   ofn.lCustData = 0;
	   ofn.lpfnHook =0;// DialogHookProc;
	   ofn.lpTemplateName = 0;
	   ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST |
				   OFN_HIDEREADONLY | OFN_NOCHANGEDIR | OFN_ALLOWMULTISELECT | OFN_EXPLORER;

   
	   if (!GetOpenFileName(&ofn))
	   {
		  lErrMsg = CommDlgExtendedError();
		  hr=HRESULT_FROM_WIN32(lErrMsg);
		  return hr;
		  
	   }

	   /*
	   /////////////////
	   for (i =  g_AttachedFiles->begin(); i != g_AttachedFiles->end(); ++i)
			{



				if (g_AttachedFiles->empty())
					break;
				
				pInsAttachInfo=(*i);
				
				if(pInsAttachInfo->m_bstrFileName==_bstr_t(ofn.lpstrFileTitle))
				{
					hr=E_FILE_EXIST;
					goto Quit;

				}

       
	   }

	   */

/*	   
	   pTmpFileInfo=	m_pMsg->m_FILEINFO_AttachFileInfoList;
	   if(pTmpFileInfo)
	   {
			while(pTmpFileInfo)
			{
			
					if(_bstr_t(ofn.lpstrFileTitle)==_bstr_t(pTmpFileInfo->szFileName))
					{
						hr=E_FILE_EXIST;
						goto Quit;
						
					}

					pTmpFileInfo = pTmpFileInfo->next;
			}
	   }
*/

	   char *szFileList = NULL;
	   BOOL bDuplicate;

	   ParseFileList(
					(char*)ofn.lpstrFileTitle,
					(char*)ofn.lpstrFile,
					m_pMsg->m_FILEINFO_AttachFileInfoList,
					g_AttachedFiles,
					&szFileList,
					bDuplicate
					);
	   /*
	   hr=GetAttachments(
						 szFileList,
						 &m_pMsg->m_FILEINFO_AttachFileInfoList
						 );

	   FREE_MEMORY(szFileList);

	   

	   if(hr!=S_OK)
	   {
				g_dwAppErr=E_UNABLE_TO_ATTACH;
				goto Quit;
	   }
	   */

	   if(bDuplicate == TRUE) 
			hr=E_FILE_EXIST;

	   if(szFileList==NULL)
		   goto Quit;

	   char * lpTok=NULL;	
	   lpTok=strtok(szFileList,",");

	   while(lpTok!=NULL)
	   {
		  
		   pAttachInfo=new CAttachInfo;

		   stream = fopen((TCHAR*)lpTok, "rb");
		   if(stream==NULL)
		   {
			   hr=HRESULT_FROM_WIN32(GetLastError());
			   goto Quit;
		   }

		   fseek(stream, 0, SEEK_END);
		   pAttachInfo->m_dwFileSize = ftell(stream);
		   rewind(stream);
		   fclose(stream);
			
		   ////Fix Size
		   char  *szFileName;
		   GetFileName(lpTok,&szFileName);

		      
		   pAttachInfo->m_bstrPathName=lpTok;
		   pAttachInfo->m_bstrFileName= szFileName;
		   g_AttachedFiles->insert(g_AttachedFiles->begin(),pAttachInfo);

		   FREE_MEMORY(szFileName);

		   lpTok=strtok(NULL,",");
	   }
      	   

   }
   catch(...)
   {
	   hr=E_UNEXPECTED;
   }

     
 
	//////////
Quit:
	i_pvarAppStatus->vt=VT_I4;
	i_pvarAppStatus->lVal=g_dwAppErr;
	
	return hr;
}


STDMETHODIMP CVSSC::get_SelectedAttachments(VARIANT *pVal)
{
   
   hr=S_OK;
   ///////

    _bstr_t       bstrFileList;
	_bstr_t       bstrSep(L",");
	FILEINFO	  *pTmpFileInfo=NULL;
      
   CAttachInfo *pInsAttachInfo;
   ATTACH_FILE_INFO::iterator i;

   _bstr_t      bstrFileTitle;

   bstrFileList="";
   bstrFileTitle="";

   do
   {
	   hr=CheckEnv(CHECK_INIT|CHECK_PTAVER);
	   CHECK_HRESULT_BREAK
	  
	   m_pMsg->m_bstrAttachFileNameList="";

	   if(g_AttachedFiles!=NULL)
	   {   
		   for (i =  g_AttachedFiles->begin(); i != g_AttachedFiles->end(); ++i)
			{
				pInsAttachInfo=(*i);
			
				m_pMsg->m_bstrAttachFileNameList+=pInsAttachInfo->m_bstrPathName;
				m_pMsg->m_bstrAttachFileNameList+=_bstr_t(L",");

				bstrFileTitle+=pInsAttachInfo->m_bstrFileName;
				bstrFileTitle+=_bstr_t(L",");
			}
	   }

		pTmpFileInfo=	m_pMsg->m_FILEINFO_AttachFileInfoList;
		if(pTmpFileInfo)
		{
			while(pTmpFileInfo)
			{
		
				bstrFileList+=pTmpFileInfo->szFileName;
				bstrFileList+=bstrSep;

				pTmpFileInfo = pTmpFileInfo->next;
			}
		}

	   bstrFileTitle+=bstrFileList;

	   pVal->vt = VT_BSTR;
	   pVal->bstrVal =bstrFileTitle.copy();
   
		

   }

   while(0);
   return hr;
}

STDMETHODIMP CVSSC::put_UnSelectAttachments(VARIANT newVal)
{
	
   CAttachInfo *pInsAttachInfo;
   ATTACH_FILE_INFO::iterator i;

   FILEINFO		*pTmpFileInfo=NULL;
   FILEINFO		*pStartFileInfo=NULL;
   FILEINFO		*pPrevFileInfo=NULL;

   BOOL         bDelFile=FALSE;

    hr = S_OK;

	do
	{
		///Check for BSTR//////
		if(newVal.vt != VT_BSTR)
		{
				//return Invalid argument;
			hr=E_VSSC_INVALIDARGS;
			return hr;

		}

		hr=CheckEnv(CHECK_INIT|CHECK_PTAVER);
		CHECK_HRESULT_BREAK

		//if (g_AttachedFiles->empty())
		//				return E_FAIL;
			
   		for (i =  g_AttachedFiles->begin(); i != g_AttachedFiles->end(); ++i)
			{

				if (g_AttachedFiles->empty())
					break;

				pInsAttachInfo=(*i);
				
				if(pInsAttachInfo->m_bstrFileName==_bstr_t(newVal.bstrVal))			
				{
						g_AttachedFiles->erase(i);
						bDelFile=TRUE;
						break;
				}
			
       
			}

		//if(bDelFile)
		//	break;

		pTmpFileInfo=	m_pMsg->m_FILEINFO_AttachFileInfoList;
		pStartFileInfo = m_pMsg->m_FILEINFO_AttachFileInfoList;

		if(pTmpFileInfo)
		{
			while(pTmpFileInfo)
			{
					
				if(_bstr_t(newVal.bstrVal)==_bstr_t(pTmpFileInfo->szFileName))
				{
					break;
				}
				pPrevFileInfo = pTmpFileInfo;
				pTmpFileInfo = pTmpFileInfo->next;
			}

			if(pTmpFileInfo != NULL)
			{
				if(pTmpFileInfo == pStartFileInfo)
				{
					m_pMsg->m_FILEINFO_AttachFileInfoList = pTmpFileInfo->next;
				}
				else
				{
					pPrevFileInfo->next = pTmpFileInfo->next;
				}

				FREE_MEMORY(pTmpFileInfo->pbFileData);
				delete pTmpFileInfo;

			}
			else
			{
				//not found
			}
			


		}
			

			
	}
	while(0);
	return hr;
	
}


STDMETHODIMP CVSSC::get_AttachedFileList(VARIANT *pVal)
{

	  hr=S_OK;
   ///////

    _bstr_t       bstrFileList;
	_bstr_t       bstrSep(L",");
	FILEINFO	  *pTmpFileInfo=NULL;
      
   CAttachInfo *pInsAttachInfo;
   ATTACH_FILE_INFO::iterator i;

   _bstr_t      bstrFileTitle;

   bstrFileList="";
   bstrFileTitle="";

   do
   {
	   hr=CheckEnv(CHECK_INIT|CHECK_PTAVER);
	   CHECK_HRESULT_BREAK

	   
	   m_pMsg->m_bstrAttachFileNameList="";

	   if(g_AttachedFiles!=NULL)
	   {
 
		   for (i =  g_AttachedFiles->begin(); i != g_AttachedFiles->end(); ++i)
			{

				pInsAttachInfo=(*i);
				
				m_pMsg->m_bstrAttachFileNameList+=pInsAttachInfo->m_bstrPathName;
				m_pMsg->m_bstrAttachFileNameList+=_bstr_t(L",");

				bstrFileTitle+=pInsAttachInfo->m_bstrFileName;
				bstrFileTitle+=_bstr_t(L",");

				
			}
	   }

		pTmpFileInfo=	m_pMsg->m_FILEINFO_AttachFileInfoList;
		if(pTmpFileInfo)
		{
			while(pTmpFileInfo)
			{
		
				bstrFileList+=pTmpFileInfo->szFileName;
				bstrFileList+=bstrSep;

				pTmpFileInfo = pTmpFileInfo->next;
			}
		}

	   bstrFileTitle+=bstrFileList;

	   pVal->vt = VT_BSTR;
	   pVal->bstrVal =bstrFileTitle.copy();
   

   }

   while(0);
   return hr;
		   
}

STDMETHODIMP CVSSC::SaveAttachment(VARIANT *pFileName, VARIANT* i_pvarAppStatus)
{

   hr=S_OK;

   long	lErrMsg = 0;
   OPENFILENAME ofn;
  
   char      *pszInput=NULL,*pszDisplayFileName=NULL;
   
   BYTE		 *pbDecodeData=NULL;
   DWORD     dwDecodedData=0;	

   try
   {

	   do
	   {

		   if(pFileName->vt != VT_BSTR)
		   {
					//return Invalid argument;
					hr=E_VSSC_INVALIDARGS;
					break;
		   }

		   hr=CheckEnv(CHECK_INIT|CHECK_PTAVER);
		   CHECK_HRESULT_BREAK
			
		   ZeroMemory(&ofn, sizeof(ofn));

		   
		   /////FileName
		   pszInput= _WideToMultiString(pFileName->bstrVal);
		   CHECK_MEM_BREAK(pszInput)
			
		   DWORD   dwDislayBufferSize=lstrlen(pszInput)+1+(4*MAX_PATH);
		   
		   pszDisplayFileName=(char*)malloc(dwDislayBufferSize);
		   CHECK_MEM_BREAK(pszDisplayFileName)	
	   		   
		   strcpy(pszDisplayFileName,pszInput);

		   /////File Extension
		   char  szFileExt[256];
		   char *last=strrchr(pszInput,'.');
		   int offset;

		   offset=last-pszInput+1;
		   lstrcpy(szFileExt,pszInput+offset);
 
 
		   // Initialize OPENFILENAME structure.
		   ofn.lStructSize = sizeof(ofn);
		   ofn.hwndOwner = NULL; 
		   ofn.lpstrFile = pszDisplayFileName; 
		   ofn.nMaxFile = dwDislayBufferSize;
		   ofn.lpstrFilter = TEXT("All Files\0*.*\0\0");
		   ofn.nFilterIndex = 1;
		   ofn.lpstrTitle = TEXT("Save Attachment");
		   ofn.lpstrInitialDir = NULL;
		   ofn.lpstrCustomFilter = NULL;
		   ofn.nMaxCustFilter = 0;
		   ofn.lpstrFileTitle = NULL;
		   ofn.nMaxFileTitle = 0;
		   ofn.nFileOffset = 0;
		   ofn.nFileExtension = 0;
		   ofn.lpstrDefExt = szFileExt;
		   ofn.lCustData = 0;
		   ofn.lpfnHook = 0;
		   ofn.lpTemplateName = 0;
		   ofn.Flags = OFN_PATHMUSTEXIST|OFN_HIDEREADONLY|
							OFN_OVERWRITEPROMPT|OFN_CREATEPROMPT |OFN_NOCHANGEDIR;
		   
		   if (!GetSaveFileName(&ofn))
		   {
			  
			  lErrMsg = CommDlgExtendedError();
			  hr=HRESULT_FROM_WIN32(lErrMsg);
			  break;

			  
		   }
   
		   
		   FILEINFO		*pTmpFileInfo=NULL;
		   pTmpFileInfo= m_pMsg->m_FILEINFO_AttachFileInfoList;

		   if(pTmpFileInfo)
			{
			
				while(pTmpFileInfo)
				{
					
						if(strnicmp(pszInput,pTmpFileInfo->szFileName,strlen(pTmpFileInfo->szFileName))==0)
						{	
							
							
							if(pTmpFileInfo->pbFileData!=NULL &&
											pTmpFileInfo->cbFileSize!=NULL)
							{
								_Base64Decode((char*)pTmpFileInfo->pbFileData,pTmpFileInfo->cbFileSize,
													NULL,&dwDecodedData) ;
								if(!dwDecodedData)break;
								
								pbDecodeData = (BYTE*)malloc(dwDecodedData); 
								CHECK_MEM_BREAK(pbDecodeData)

								_Base64Decode((char*)pTmpFileInfo->pbFileData,pTmpFileInfo->cbFileSize,
												(char *)pbDecodeData,&dwDecodedData) ;
								if (!pbDecodeData) break;
							}

							FILE *stream = NULL;
							stream = fopen(ofn.lpstrFile, "wb+");
							if(stream==NULL)
							{
								hr=HRESULT_FROM_WIN32(GetLastError());
								break;
							}
							if(pbDecodeData!=NULL && dwDecodedData!=0)
								fwrite(pbDecodeData, 1,	dwDecodedData, stream);

							fclose(stream);
							break;

						}
					
						pTmpFileInfo = pTmpFileInfo->next;
				}
			}

		   
	   }
	   while(0);
	}
	catch(...)
	{
		hr=E_UNEXPECTED;
	}

   FREE_MEMORY(pszInput)
   FREE_MEMORY(pszDisplayFileName)
   FREE_MEMORY(pbDecodeData)
  
   i_pvarAppStatus->vt=VT_I4;
   i_pvarAppStatus->lVal=g_dwAppErr;

	return hr;
}


STDMETHODIMP CVSSC::put_MsgPostData(VARIANT newVal)
{
	hr = S_OK;
	do
	{
		hr=CheckEnv(CHECK_INIT|CHECK_PTAVER);
		CHECK_HRESULT_BREAK

		/////Check for BSTR Type
		if(newVal.vt != VT_BSTR)
		{
			return E_VSSC_INVALIDARGS;
		}

		/////Check for Empty Value
		if(newVal.bstrVal == NULL || newVal.bstrVal == _bstr_t(""))
			return E_VSSC_EMPTYARGS;

		m_pPost.m_bstrPostVar=newVal.bstrVal;

	}while(0);
		
	return hr;
}


STDMETHODIMP CVSSC::CertificateResolution(
										  VARIANT *in_pvarEmailInfo,
										  VARIANT* i_pvarAppStatus
										  )
{
	_bstr_t     bstrEmailAddr;

	hr=S_OK;

	try
	{

		do
		{

			if(!in_pvarEmailInfo)
			{
				hr = E_VSSC_EMPTYARGS;
				g_dwAppErr=E_UNABLE_TODO_CERTRESOLVE;
				break;
			}

			if(in_pvarEmailInfo->vt != VT_BSTR)
			{
				hr = E_VSSC_INVALIDARGS;
				g_dwAppErr=E_UNABLE_TODO_CERTRESOLVE;
				break;
			}

			bstrEmailAddr=in_pvarEmailInfo->bstrVal;
			if(bstrEmailAddr.length()==0)
			{
				hr = E_VSSC_EMPTYARGS;
				g_dwAppErr=E_UNABLE_TODO_CERTRESOLVE;
				break;
			}


			hr=CheckEnv(CHECK_INIT|CHECK_CERTURL|CHECK_SCTYPE|CHECK_PTAVER);
			CHECK_HRESULT_BREAK
		
			FreeCertList(&m_pMsg->m_SignerCertList);

			////0-userCertificate 1->SMIMECertificate
			m_pMsg->m_dwResolutionOpr=0;   

			CERT_RESOLVE_INFO   CertResolveInfo;

			CertResolveInfo.nVersion=m_pMsg->m_nReqVersion;
			CertResolveInfo.nOperation=m_pMsg->m_dwResolutionOpr; 
			//0-email 1->serialNum and issuerDN
			CertResolveInfo.ReqCrit=0;    
			CertResolveInfo.pszSCType=m_pMsg->m_SCType;


			
			hr=GetSignerCertificate(
									bstrEmailAddr,
									m_pMsg->m_bstrCertResolutionURL,
									&CertResolveInfo,	//CertResolveInfo
									NULL,				//REQ_CRIT_INFO
									0,					//Num OF REQ_CRIT_INFO
									&m_pMsg->m_SignerCertList
									);
			CHECK_HRESULT_BREAK;
			
		}
		while(0);
	}
	catch(...)
	{
		hr=E_UNEXPECTED;
	}

	i_pvarAppStatus->vt=VT_I4;
	i_pvarAppStatus->lVal=g_dwAppErr;

	return hr;
}

STDMETHODIMP CVSSC::SMIMECertificateResolution(VARIANT* i_pvarAppStatus)
{

	hr=S_OK;
	
	_bstr_t                     bstrSep(_T(","));
	_bstr_t                     bstrEmailAddr;

	CListUserInfo::iterator		it;

	try
	{

		do
		{

			hr=CheckEnv(CHECK_INIT|CHECK_CERTURL|CHECK_SCTYPE|CHECK_PTAVER);
			CHECK_HRESULT_BREAK
			
			if(m_pMsg->m_bstrTo.length()>0)
			{
						bstrEmailAddr+=m_pMsg->m_bstrTo;
						bstrEmailAddr+=bstrSep;
			}
			
			if(m_pMsg->m_bstrCc.length()>0)
			{
						bstrEmailAddr+=m_pMsg->m_bstrCc;
						bstrEmailAddr+=bstrSep;

			}
				
			if(m_pMsg->m_bstrBcc.length()>0)
			{
						bstrEmailAddr+=m_pMsg->m_bstrBcc;
						bstrEmailAddr+=bstrSep;

			}


			if(m_pMsg->m_AddSenderRecipientInfo)
			{
					if(m_pMsg->m_bstrFrom.length()>0)
					{
						bstrEmailAddr+=m_pMsg->m_bstrFrom;
						bstrEmailAddr+=bstrSep;
					}
					else
					{
						hr=E_SENDERINFO_NOTFOUND;
						g_dwAppErr=E_UNABLE_TODO_CERTRESOLVE;
						break;
					}
			}

			if(bstrEmailAddr.length()==0)
			{
				hr=E_VSSC_EMPTYARGS;
				g_dwAppErr=E_UNABLE_TODO_CERTRESOLVE;
				break;
			}

			FreeCertList(&m_pMsg->m_EncryptCertList);

			m_pMsg->m_dwResolutionOpr=1; /////1->SMIME Resolution

			
			CERT_RESOLVE_INFO   CertResolveInfo;

			CertResolveInfo.nVersion=m_pMsg->m_nReqVersion;
			CertResolveInfo.nOperation=m_pMsg->m_dwResolutionOpr;
			CertResolveInfo.ReqCrit=0;
			CertResolveInfo.pszSCType=m_pMsg->m_SCType;

			hr=GetEncryptionCertificates(
				bstrEmailAddr,
				m_pMsg->m_bstrCertResolutionURL,
				&CertResolveInfo,	//CertResolveInfo
				NULL,				//REQ_CRIT_INFO
				0,					//Num OF REQ_CRIT_INFO
				&m_pMsg->m_EncryptCertList);
			CHECK_HRESULT_BREAK;

			
		}
		while(0);
	}
	catch(...)
	{
		hr=E_UNEXPECTED;
	}

	i_pvarAppStatus->vt=VT_I4;
	i_pvarAppStatus->lVal=g_dwAppErr;

	return hr;
}

STDMETHODIMP CVSSC::put_CertResolveURL(VARIANT newVal)
{
	
	hr = S_OK;
	do
	{
		hr=CheckEnv(CHECK_INIT|CHECK_PTAVER);
		CHECK_HRESULT_BREAK

		///Check for BSTR//////
		if(newVal.vt != VT_BSTR)
		{
			//return Invalid argument;
			return E_VSSC_INVALIDARGS;
			g_dwAppErr=E_UNABLE_TODO_CERTRESOLVE;
		}

		if(newVal.bstrVal == NULL)
		{
			return E_VSSC_EMPTYARGS;
			g_dwAppErr=E_UNABLE_TODO_CERTRESOLVE;
		}
		
		m_pMsg->m_bstrCertResolutionURL=newVal.bstrVal;
	}
	while(0);
	return hr;

}


STDMETHODIMP CVSSC::Decompose(VARIANT *i_pvarSMIMEMsg, VARIANT *i_pvarAppStatus)
{
	
	hr =				S_OK;
	char                *szDecode=NULL,*szMsg=NULL;
	BOOL                bRet; 
	_bstr_t				bstrPKCS7;
	MSGINFO				MsgInfo;
	VS_PKCS7_INFO		vsspiPKCS7Info;

	

	try
	{
		hr=CheckEnv(CHECK_INIT|CHECK_PTAVER);
		if(hr!=S_OK)
		{
			g_dwAppErr=E_UNABLE_VIEW_ERR;
			i_pvarAppStatus->vt=VT_I4;
			i_pvarAppStatus->lVal=g_dwAppErr;
			return hr;
		}

		pVSPTA = (IVSPTA*)_GetInterface(IID_IVSPTA);
		if(!pVSPTA)
		{
			g_dwAppErr=E_UNABLE_VIEW_ERR;
			i_pvarAppStatus->vt=VT_I4;
			i_pvarAppStatus->lVal=g_dwAppErr;
			return E_NOINTERFACE;
		}

		do
		{
			
			

			m_pMsg->m_dwCryptStatus=0;
			bComposeCalled=TRUE;

			ZeroMemory(&MsgInfo,sizeof(MSGINFO));
			ZeroMemory(&vsspiPKCS7Info,sizeof(VS_PKCS7_INFO));
		

			if(!bUseInternetData)
			{
				
					/////Check for BSTR
					if(i_pvarSMIMEMsg->vt != VT_BSTR)
					{
						//return Invalid argument;
						hr=E_VSSC_INVALIDARGS;
						g_dwAppErr=E_UNABLE_VIEW_ERR;
				
						break;
					}
					
					szMsg=_WideToMultiString(i_pvarSMIMEMsg->bstrVal);
					
			}
			else
			{			
					
					szMsg=(char*)pbURLContent;
					
			}


			if(m_pMsg->m_bURLEncodeData)
			{	
				szDecode=URLDecode(szMsg);
				FREE_MEMORY(szMsg);

			}
			else
			{
				szDecode=szMsg;

			}
			
							
			if(szDecode)
			{
				/////passed the URL Encoded Data from VBSCRIPT
				if(!bUseInternetData)
				{
						bRet=ParseMessage(szDecode,&MsgInfo);
						if(!bRet)
						{
							hr=E_PARSEMIME_FAILED;
							g_dwAppErr=E_UNABLE_VIEW_ERR;
							break;
						}
					

						/////Plain Msg or Just PKCS7
						if(MsgInfo.eMimeType==VSSC_OTHER)
						{
							//freeMsgInfo(&MsgInfo);
							MsgInfo.szPKCS7=(char*)malloc(strlen(szDecode)+1);
							CHECK_MEM_BREAK(MsgInfo.szPKCS7)
							memcpy(MsgInfo.szPKCS7,(TCHAR*)szDecode,strlen(szDecode));
							MsgInfo.szPKCS7[strlen(szDecode)]='\0';

						}

						if(m_pMsg->m_bURLEncodeData)
								   FREE_MEMORY(szDecode);

						FREE_MEMORY(szMsg);
						

					

				}
				else
				{
					/////Out of bound Download(No URL decoding)
					bRet=ParseMessage(szDecode,&MsgInfo);
					if(!bRet)
					{
						hr=E_PARSEMIME_FAILED;
						g_dwAppErr=E_UNABLE_VIEW_ERR;
						break;
					}

					/////Plain Msg or Just PKCS7
					if(MsgInfo.eMimeType==VSSC_OTHER)
					{
						freeMsgInfo(&MsgInfo);

						MsgInfo.szPKCS7=(char*)malloc(strlen(szDecode)+1);
						CHECK_MEM_BREAK(MsgInfo.szPKCS7)
						memcpy(MsgInfo.szPKCS7,(TCHAR*)szDecode,strlen(szDecode));
						MsgInfo.szPKCS7[strlen(szDecode)]='\0';

					}

					if(m_pMsg->m_bURLEncodeData)
								FREE_MEMORY(szDecode);

				
				}
				
				#ifdef	_VSSC_MSG_BOX_
				::MessageBox ( NULL, (LPCTSTR) "PARSEPKCS7-Begin",
													(LPCTSTR) "VSSC", MB_OK );
				#endif

				if(MsgInfo.szPKCS7==NULL)
				{
					hr=E_INVALID_MIME;
					g_dwAppErr=E_UNABLE_VIEW_ERR;
				}

				hr=ParsePKCS7(MsgInfo,m_pMsg->m_bUseSimder,&vsspiPKCS7Info);
				CHECK_HRESULT_BREAK

				switch(vsspiPKCS7Info.ePKCS7Type)
				{
				case PKCS7_SIGNED:
								m_pMsg->m_dwMsgType=VSSC_MSG_SIGNED;
								hr=GetMsgHeader(&MsgInfo,m_pMsg);
								CHECK_HRESULT_BREAK;
								hr=VSSC_VerifyMessageSignature(
															 MsgInfo,
															 m_pMsg,
															 &vsspiPKCS7Info
															 );
				    				  				
								break;

				case PKCS7_ENVELOPED:
								m_pMsg->m_dwMsgType=VSSC_MSG_ENCRYPT;
								hr=GetMsgHeader(&MsgInfo,m_pMsg);
								CHECK_HRESULT_BREAK;
								hr=VSSC_DecryptMessage(
													  pVSPTA,
													  m_pMsg->m_dwMsgType,
													  m_pMsg,
													  &vsspiPKCS7Info
													  );
								break;
				}
				
	   			
			}
		}
		while(0);

		
	}//try end

	catch(...)
	{
		hr=E_UNEXPECTED;		
		
	}

	if(!bUseInternetData)
			FREE_MEMORY(szMsg)

	if(m_pMsg->m_bURLEncodeData)
			FREE_MEMORY(szDecode);


	
	FreePKCS7Info(&vsspiPKCS7Info);
	////#case
	FREE_MEMORY(vsspiPKCS7Info.EncryptedDataInfo.pRecipientInfo)
	freeMsgInfo(&MsgInfo);

	if(pVSPTA)
	{
		pVSPTA->Release();
		pVSPTA = NULL;
	}

	i_pvarAppStatus->vt=VT_I4;
	i_pvarAppStatus->lVal=g_dwAppErr;

	return hr;
}

STDMETHODIMP CVSSC::get_IVSSCResolveInfo(IDispatch **pVal)
{
	hr=S_OK;
	do
	{
		hr=CheckEnv(CHECK_INIT|CHECK_PTAVER);
		CHECK_HRESULT_BREAK

		*pVal = NULL;
		*pVal = (IDispatch*)_GetInterface(IID_IResolveRcpt);
		if(!*pVal)
		{
			hr = E_NOINTERFACE;
			g_dwAppErr=E_UNABLE_TODO_CERTRESOLVE;
		}
	}
	while(0);
	return hr;

}

STDMETHODIMP CVSSC::get_IVSSignerInfo(IDispatch **pVal)
{
	hr=S_OK;

	do
	{
		hr=CheckEnv(CHECK_INIT|CHECK_PTAVER);
		CHECK_HRESULT_BREAK

		*pVal = NULL;
		*pVal = (IDispatch*)_GetInterface(IID_IVSSignerInfo);
		if(!*pVal)
		{
			hr = E_NOINTERFACE;
		}

		bDecCert=FALSE;
	}
	while(0);

	return hr;
}


STDMETHODIMP CVSSC::get_EmailAddress(VARIANT *pVal)
{
	hr=S_OK;
	CUserInfo * pObj=NULL;
	do
	{
		hr=CheckEnv(CHECK_INIT|CHECK_RESFIRST|CHECK_PTAVER);
	    CHECK_HRESULT_BREAK
		pObj=(*ResolveIter);

		if(pObj==NULL)
		{
			break;
		}

		pVal->vt=VT_BSTR;

		//return Value
		if(pObj->stCertReqResponseInfo.bstrEmailAddr!=_bstr_t(_T("")))
		{
			pVal->bstrVal = pObj->stCertReqResponseInfo.bstrEmailAddr.copy();
		}
		else
			pVal->bstrVal=NULL;
	}
	while(0);

	return hr;
}

STDMETHODIMP CVSSC::get_Recipient_Count(VARIANT *pVal)
{
	int   iRecipient_count=0;

	hr=S_OK;
	do
	{
		hr=CheckEnv(CHECK_INIT|CHECK_PTAVER);
	    CHECK_HRESULT_BREAK
		
		if(m_pMsg->m_dwResolutionOpr==0)
			iRecipient_count=m_pMsg->m_SignerCertList.size();

        if(m_pMsg->m_dwResolutionOpr==1) 
				iRecipient_count=m_pMsg->m_EncryptCertList.size();


		pVal->vt=VT_I2;
		pVal->iVal=iRecipient_count;
	}
	while(0);

	return hr;

}


STDMETHODIMP CVSSC::First()
{
	hr=S_OK;
	do
	{
		hr=CheckEnv(CHECK_INIT|CHECK_PTAVER);
	    CHECK_HRESULT_BREAK

		if(m_pMsg->m_dwResolutionOpr==0)
		{
			if(!m_pMsg->m_SignerCertList.empty())
					ResolveIter=m_pMsg->m_SignerCertList.begin();
			else
			{
				hr=E_EMPTYEMAILLIST;
				break;
			}
		}

		if(m_pMsg->m_dwResolutionOpr==1)
		{
			if(!m_pMsg->m_EncryptCertList.empty())
						ResolveIter =  m_pMsg->m_EncryptCertList.begin();
			else
			{
				hr=E_EMPTYEMAILLIST;
				break;
			}
		}

		m_bResolveFirst=TRUE;

	}
	while(0);
	return hr;
}

STDMETHODIMP CVSSC::Next()
{
	hr=S_OK;
	do
	{
		hr=CheckEnv(CHECK_INIT|CHECK_RESFIRST|CHECK_PTAVER);
	    CHECK_HRESULT_BREAK

		ResolveIter++;
	}
	while(0);
	return hr;
}



STDMETHODIMP CVSSC::put_UseProxyRecipCert(VARIANT newVal)
{
	hr = S_OK;
	do
	{
		///Check for BSTR//////
		if(newVal.vt != VT_I2)
		{
			//return Invalid argument;
			hr=E_VSSC_INVALIDARGS;
			break;
		}
		hr=CheckEnv(CHECK_INIT|CHECK_PTAVER);
		CHECK_HRESULT_BREAK

		m_pMsg->m_dwUsePRC=newVal.iVal;
	
	}
	while(0);

	return hr;
}

STDMETHODIMP CVSSC::ResolveProxyRecipCert(
										  VARIANT *in_pvarEmailInfo,
										  VARIANT *o_pvarAppStatus,
										  VARIANT *in_pvarStatus)
{
	

	_bstr_t				bstrEmailAddr;
	PCERT_INFO			pPRCCertInfo=NULL;

	VSSC_ENCODED_CERT	EncodedCert;
	DECCERT_INFO		DecCertInfo;

	hr=S_OK;

	try
	{

		do
		{

			if(!in_pvarEmailInfo)
			{
				hr = E_VSSC_EMPTYARGS;
				g_dwAppErr=E_UNABLE_RESOLVE_PRC;
				break;
			}

			if(in_pvarEmailInfo->vt != VT_BSTR)
			{
				hr = E_VSSC_INVALIDARGS;
				g_dwAppErr=E_UNABLE_RESOLVE_PRC;
				break;
			}

			bstrEmailAddr=in_pvarEmailInfo->bstrVal;
			if(bstrEmailAddr.length()==0)
			{
				hr = E_VSSC_EMPTYARGS;
				g_dwAppErr=E_UNABLE_RESOLVE_PRC;
				break;
			}


			hr=CheckEnv(CHECK_INIT|CHECK_CERTURL|CHECK_SCTYPE|CHECK_PTAVER);
			CHECK_HRESULT_BREAK
		
			FreeCertList(&m_pMsg->m_PRCCertList);

			////0-userCertificate 1->SMIMECertificate
			//m_pMsg->m_dwResolutionOpr=1;   

			CERT_RESOLVE_INFO   CertResolveInfo;

			CertResolveInfo.nVersion=m_pMsg->m_nReqVersion;
			CertResolveInfo.nOperation=1; 
			//0-email 1->serialNum and issuerDN
			CertResolveInfo.ReqCrit=0;    
			CertResolveInfo.pszSCType=m_pMsg->m_SCType;


			
			hr=GetPRC(
					  bstrEmailAddr,
					  m_pMsg->m_bstrCertResolutionURL,
					  &CertResolveInfo,	//CertResolveInfo
					  &m_pMsg->m_PRCCertList
					);
			if(hr!=S_OK)
			{
				g_dwAppErr=E_UNABLE_RESOLVE_PRC;
				break;
			}

			it=m_pMsg->m_PRCCertList.begin();
			pObj=(*it);

			if(pObj==NULL)
			{
				hr=E_PRC_CERTNOTFOUND;
				g_dwAppErr= E_UNABLE_RESOLVE_PRC;
				break;

			}

			if(pObj->stCertStatusInfo.dwRevocationStatus!=0)
			{
					hr=E_PRC_REVOKED;
					g_dwAppErr=E_UNABLE_RESOLVE_PRC;
					break;
		
			}
					
			EncodedCert=pObj->GetEncryptionCert();
			if(EncodedCert.pbData==NULL && EncodedCert.cbData==0)
			{
				hr=E_PRC_CERTNOTFOUND;
				g_dwAppErr= E_UNABLE_RESOLVE_PRC;
				break;
			}

			
			
					
			CCertInfo  PRCCertInfo(EncodedCert.pbData,EncodedCert.cbData);
			pPRCCertInfo=PRCCertInfo.GetCertInfo();
			if(pPRCCertInfo==NULL)
			{
				hr=E_PRC_CERTNOTFOUND;
				g_dwAppErr= E_UNABLE_RESOLVE_PRC;
				break;
			}

			BOOL IsExpired=FALSE;
						
			hr=_DecodeCertInfo(pPRCCertInfo,&DecCertInfo);
			CHECK_HRESULT_BREAK
			
			
			/////Check Certificate is expired or not
			SYSTEMTIME      stSysTime;
			DATE			dtDate;

			GetSystemTime(&stSysTime);
			if(!SystemTimeToVariantTime(&stSysTime,&dtDate))
			{
				hr = E_SYSTIMETOVARTIMEFAILED;
				g_dwAppErr=E_UNABLE_RESOLVE_PRC;
			}
			
			if(!(DecCertInfo.dateEffDate<dtDate&&dtDate<DecCertInfo.dateExpDate))
			{
				hr=E_PRC_EXPIRED;
				g_dwAppErr=E_UNABLE_RESOLVE_PRC;
				break;
			}
			
			in_pvarStatus->vt=VT_I4;
			in_pvarStatus->lVal=pObj->stCertReqResponseInfo.dwStatus;

			
		}
		while(0);
	}
	catch(...)
	{
		hr=E_UNEXPECTED;
	}

	o_pvarAppStatus->vt=VT_I4;
	o_pvarAppStatus->lVal=g_dwAppErr;

	if(pPRCCertInfo)
	{
		freecertinfo(pPRCCertInfo);
		FREE_MEMORY(pPRCCertInfo)
	}

	return hr;
}

STDMETHODIMP CVSSC::get_Status(VARIANT *pVal)
{
	CUserInfo * pObj;
	hr=S_OK;

	do
	{
		hr=CheckEnv(CHECK_INIT|CHECK_RESFIRST|CHECK_PTAVER);
	    CHECK_HRESULT_BREAK

		pObj=(*ResolveIter);
		
		pVal->vt=VT_I4;
		pVal->lVal=pObj->stCertReqResponseInfo.dwStatus;
		
	}
	while(0);

	return hr;
}

STDMETHODIMP CVSSC::StoreAll(VARIANT *i_pModeType,VARIANT* i_pvarAppStatus)
{
	hr=S_OK;

	try
	{
		do
		{
			
			/*
			if ( i_pModeType->iVal >=0 || 1 < i_pModeType->iVal )
			{
				hr =	E_VSSC_INVALID_MODE;
				break;
			}
			*/

			hr=CheckEnv(CHECK_INIT|CHECK_PTAVER);
			CHECK_HRESULT_BREAK


			/////Delete From Memory
			hr=gp_GMemMgmt->DeleteObjectNode(
							(BYTE*)&m_pMsg->m_iMsgObjID,
							sizeof(int)
							);
				//CHECK_HRESULT_BREAK

			bComposeCalled=TRUE;
			::srand( (unsigned)time( NULL ) );
			m_pMsg->m_iMsgObjID =	::rand();

			//////////////////////////////
			if(i_pModeType->iVal==0)
					m_pMsg->m_ReplyAddAttachment=TRUE;
			else
					m_pMsg->m_ReplyAddAttachment=FALSE;

					//	create a new object by calling addobject
			hr=gp_GMemMgmt->AddObjectNode((BYTE *)&(m_pMsg->m_iMsgObjID),sizeof(int));
			CHECK_HRESULT_BREAK

        

			//	store everything in the object
			//
			//	all these functions will check ifthe required 
			//	information exists. if NOT they will return S_OK
			//	without storing it in the global memory

			hr=GM_PutMsgHeader(m_pMsg);
			CHECK_HRESULT_BREAK;
			hr=GM_PutMsgBody(m_pMsg);
			CHECK_HRESULT_BREAK;

			hr=GM_PutMsgAttFileNames(m_pMsg,g_AttachedFiles);
			CHECK_HRESULT_BREAK;
			

			hr=GM_PutMsgEntity(m_pMsg);
			CHECK_HRESULT_BREAK;
	//		hr=GM_PutAttachments(m_pMsg);
	//		CHECK_HRESULT_BREAK;
	//		hr=GM_PutSMIME(m_pMsg);
	//		CHECK_HRESULT_BREAK;

				//	change the mode
			m_pMsg->m_dwMessageMode =	i_pModeType->iVal;

			hr =	S_OK;
		}
		while(0);
	}
	catch(...)
	{
		hr=E_UNEXPECTED;
	}

	i_pvarAppStatus->vt=VT_I4;
	i_pvarAppStatus->lVal=g_dwAppErr;

	return hr;
}

STDMETHODIMP CVSSC::get_MsgObjID(VARIANT *pVal)
{

	hr=S_OK;

	do
	{
		hr=CheckEnv(CHECK_INIT|CHECK_PTAVER);
		CHECK_HRESULT_BREAK

		pVal->vt=VT_I4;
		pVal->lVal=m_pMsg->m_iMsgObjID;
	}
	while(0);
	return hr;
}

void CVSSC::SetComposeMode ()
{
	m_pMsg->m_dwMessageMode =	VSSC_COMPOSE;
	return;
}

STDMETHODIMP CVSSC::get_MsgBlobSize(VARIANT *pVal)
{
	hr=S_OK;
	do
	{
		

		hr=CheckEnv(CHECK_INIT|CHECK_PTAVER);
		CHECK_HRESULT_BREAK

		pVal->vt=VT_I4;
		pVal->lVal=m_pMsg->m_bstrSMIMEMsg.length();
	}
	while(0);
	
	return hr;
}

STDMETHODIMP CVSSC::InternetInitialize(VARIANT *in_pvarURL, 
									   VARIANT *in_pvarMethod, VARIANT *in_pvarPostData,VARIANT* i_pvarAppStatus)
{

	hr=S_OK;

	try
	{

		do
		{
			
			if(!in_pvarURL)
			{
					hr = E_VSSC_EMPTYARGS;
					break;
			}

			if(in_pvarURL->vt != VT_BSTR)
			{
					hr = E_VSSC_INVALIDARGS;
					break;
			}


			if(!in_pvarMethod)
			{
					hr = E_VSSC_EMPTYARGS;
					break;
			}

			if(in_pvarMethod->vt != VT_BSTR)
			{
					hr = E_VSSC_INVALIDARGS;
					break;
			}

			hr=CheckEnv(CHECK_INIT|CHECK_PTAVER);
			CHECK_HRESULT_BREAK


			m_bstrURL=in_pvarURL->bstrVal;
			m_bstrMethod=in_pvarMethod->bstrVal;
			m_bstrPostData=in_pvarPostData->bstrVal;
			
		}while(0);
	}
	catch(...)
	{
		hr=E_UNEXPECTED;
	}

	i_pvarAppStatus->vt=VT_I4;
	i_pvarAppStatus->lVal=g_dwAppErr;

  return hr;
	
}

STDMETHODIMP CVSSC::InternetSendRequest(VARIANT* i_pvarAppStatus)
{
	
	hr=S_OK;
	dwSizeSum=0;
	pbURLContent=NULL;	
	_bstr_t bstrPostData;

	try
	{

		do
		{
			hr=CheckEnv(CHECK_INIT|CHECK_PTAVER);
			CHECK_HRESULT_BREAK

			if(m_bstrPostData.length()>0)
			{
				//////Fix size
				DWORD   dwEncodedLen=m_bstrPostData.length()*3+1;
				TCHAR  *szEncodedVars=(TCHAR*)malloc(dwEncodedLen);
				CHECK_MEM_BREAK(szEncodedVars)
				URLEncode((TCHAR*)m_bstrPostData,szEncodedVars);
				bstrPostData=szEncodedVars;
				FREE_MEMORY(szEncodedVars);
			}

				hr=m_pPost.URLDownloadToBuffer(m_bstrURL,bstrPostData,&pbURLContent,&dwSizeSum);
				CHECK_HRESULT_BREAK

		}

		while(0);
	}
	catch(...)
	{
		hr=E_UNEXPECTED;
	}

	i_pvarAppStatus->vt=VT_I4;
	i_pvarAppStatus->lVal=g_dwAppErr;

	return hr;
}

STDMETHODIMP CVSSC::put_UseInternetData(VARIANT newVal)
{
	hr = S_OK;
	do
	{
		///Check for BSTR//////
		if(newVal.vt != VT_BOOL)
		{
			//return Invalid argument;
			hr=E_VSSC_INVALIDARGS;
			break;
		}

		hr=CheckEnv(CHECK_INIT|CHECK_PTAVER);
		CHECK_HRESULT_BREAK

		bUseInternetData=newVal.boolVal;
	
	}
	while(0);

	return hr;
}

STDMETHODIMP CVSSC::get_InternetDataSize(VARIANT *pVal)
{
	do
	{
		hr=CheckEnv(CHECK_INIT|CHECK_PTAVER);
		CHECK_HRESULT_BREAK

		pVal->vt=VT_I4;
		pVal->lVal=dwSizeSum;
	}
	while(0);

	return S_OK;
}

STDMETHODIMP CVSSC::get_InternetData(VARIANT *pVal)
{
	hr=S_OK;

	
	
	do
	{
		 hr=CheckEnv(CHECK_INIT|CHECK_PTAVER);
		 CHECK_HRESULT_BREAK
	
		 VARIANT var;
		 VariantInit(&var);  //Initialize our variant

		 //Set the type to an array of unsigned chars (OLE SAFEARRAY)
		 var.vt = VT_ARRAY | VT_UI1;

		 //Set up the bounds structure
		 SAFEARRAYBOUND  rgsabound[1];

		 rgsabound[0].cElements = dwSizeSum;
		 rgsabound[0].lLbound = 0;

		 //Create an OLE SAFEARRAY
		 var.parray = SafeArrayCreate(VT_UI1,1,rgsabound);

		 if(var.parray != NULL)
		 {
		   void * pArrayData = NULL;

		   //Get a safe pointer to the array
		   SafeArrayAccessData(var.parray,&pArrayData);

		   //Copy data to it
		   memcpy(pArrayData, pbURLContent,dwSizeSum);

		   //Unlock the variant data
		   SafeArrayUnaccessData(var.parray);

		   *pVal = var; 
		   //VariantClear(&var);
		   
		 }

	}
	while(0);
	return hr;
}



STDMETHODIMP CVSSC::ChangeVarType(VARIANT *in_pvarByteArray, VARIANT *in_pvarType, VARIANT *o_pvarOutputType)
{
	hr=S_OK;
	do
	{
	 //Binary data is stored in the variant as an array of unsigned char
     if(in_pvarByteArray->vt == (VT_ARRAY|VT_UI1))  // (OLE SAFEARRAY)
     {
       
         void * pArrayData;
         //Obtain safe pointer to the array
         SafeArrayAccessData(in_pvarByteArray->parray,&pArrayData);

         //Copy the bitmap into our buffer
         if(in_pvarType->iVal==8)//vbString Type
		 {
			o_pvarOutputType->vt=VT_BSTR;
			o_pvarOutputType->bstrVal=_MultiToWideString((char*)pArrayData);
		 }

		 //Unlock the variant data
         SafeArrayUnaccessData(in_pvarByteArray->parray);
       }

	}
	while(0);

	return hr;
}

STDMETHODIMP CVSSC::SelectedAttachmentSize(
										   VARIANT *in_pvarFileName, 
										   VARIANT *i_pvarAppStatus,
										   VARIANT *o_pvarFileSize
										   )
{

   CAttachInfo *pInsAttachInfo;
   ATTACH_FILE_INFO::iterator i;

   BYTE		   *pbFileData=NULL;
   DWORD       dwDecodedData=0;

   FILEINFO	  *pTmpFileInfo=NULL;

   hr = S_OK;

   try
   {
	   do
		{

			///Check for BSTR//////
			if(in_pvarFileName->vt != VT_BSTR)
			{
					//return Invalid argument;
				hr=E_VSSC_INVALIDARGS;
				return hr;

			}
			
			hr=CheckEnv(CHECK_INIT|CHECK_PTAVER);
			CHECK_HRESULT_BREAK
					
			if(g_AttachedFiles!=NULL)
			{
				
   				for (i =  g_AttachedFiles->begin(); i != g_AttachedFiles->end(); ++i)
					{

						if (g_AttachedFiles->empty())
							break;

						pInsAttachInfo=(*i);
						
						if(pInsAttachInfo->m_bstrFileName==_bstr_t(in_pvarFileName->bstrVal))			
						{
								o_pvarFileSize->vt=VT_I4;
								o_pvarFileSize->lVal=pInsAttachInfo->m_dwFileSize;
								break;
						}
					
       
					}
			}

			 pTmpFileInfo=	m_pMsg->m_FILEINFO_AttachFileInfoList;
			 if(pTmpFileInfo)
			 {
					while(pTmpFileInfo)
					{
					
							if(_bstr_t(in_pvarFileName->bstrVal)==_bstr_t(pTmpFileInfo->szFileName))
							{

								if(pTmpFileInfo->pbFileData!=NULL &&
												pTmpFileInfo->cbFileSize!=0) 
								{

									_Base64Decode(
												 (char*)pTmpFileInfo->pbFileData,
												 pTmpFileInfo->cbFileSize,
												 NULL,
												 &dwDecodedData
												 ) ;
									if(!dwDecodedData)break;
									pbFileData=(BYTE*)malloc(dwDecodedData);
									CHECK_MEM_BREAK(pbFileData)

									_Base64Decode(
												 (char*)pTmpFileInfo->pbFileData,
												 pTmpFileInfo->cbFileSize,
												 (char*)pbFileData,
												 &dwDecodedData
												 ) ;

									FREE_MEMORY(pbFileData)
								}

					

								o_pvarFileSize->vt=VT_I4;
								o_pvarFileSize->lVal=dwDecodedData;
								break;
							}

							pTmpFileInfo = pTmpFileInfo->next;
					}
			 }




		}
		while(0);
   }
   catch(...)
   {
	   hr=E_UNEXPECTED;
   }

	i_pvarAppStatus->vt=VT_I4;
	i_pvarAppStatus->lVal=g_dwAppErr;

	return hr;

}



STDMETHODIMP CVSSC::get_SubjectCN(VARIANT *pVal)
{	
	char *pszSubjectDN=NULL;

	hr=S_OK;
	do
	{
		hr=CheckEnv(CHECK_INIT|CHECK_PTAVER);
	    CHECK_HRESULT_BREAK

		if(!bDecCert)
		{
			hr=GetSignerCertProps();
    		CHECK_HRESULT_BREAK

		}


		/*
		_bstr_t   bstrTmp=pDecCertInfo->bstrSubjectDN.copy();
		wchar_t   *pwcRDN=NULL;
		////Fix
		wchar_t   *pwcFind=L" CN=" ;////Space before E=
		int        nwcFind=wcslen(pwcFind);

		pwcRDN=wcstok(bstrTmp,L";");
		
		while(pwcRDN!=NULL)
		{
			if(wcsncmp(pwcRDN,pwcFind,nwcFind)==0)
			{
				int nwcRDN=wcslen(pwcRDN);
				wchar_t *pwcCN=(wchar_t *)malloc(nwcRDN+nwcFind);
				CHECK_MEM_BREAK(pwcCN)

				wcscpy(pwcCN,pwcRDN+nwcFind);
				pDecCertInfo->bstrSubjectDN_CN=pwcCN;
				//FREE_MEMORY(pwcCN);
				break;
			}

			pwcRDN=wcstok(NULL,L";");
		}
		*/

		pszSubjectDN=_WideToMultiString(pDecCertInfo->bstrSubjectDN);
		CHECK_MEM_BREAK(pszSubjectDN)
		char *pszToken=NULL;
		char *pszFind=" CN=";
		char *pszEmail=NULL;

		pszToken=strtok(pszSubjectDN,";");
		while(pszToken!=NULL)
		{
			if(strncmp(pszToken,pszFind,strlen(pszFind))==0)
			{
				int   nszFind=strlen(pszFind);
				int nszToken=strlen(pszToken);

				pszEmail=(char*)malloc(nszToken+nszFind+1);
				strcpy(pszEmail,pszToken+nszFind);
				_bstr_t  bstrEmailTmp(pszEmail);
				pDecCertInfo->bstrSubjectDN_CN=bstrEmailTmp;
				break;

			}
			pszToken=strtok(NULL,";");
		}
		FREE_MEMORY(pszEmail);

		pVal->vt = VT_BSTR;
		pVal->bstrVal=pDecCertInfo->bstrSubjectDN_CN.copy();

	}
	while(0);
	
	FREE_MEMORY(pszSubjectDN)
	return hr;
}

STDMETHODIMP CVSSC::get_SubjectDN(VARIANT *pVal)
{
	hr=S_OK;
	do
	{
		hr=CheckEnv(CHECK_INIT|CHECK_PTAVER);
	    CHECK_HRESULT_BREAK

		if(!bDecCert)
		{
			hr=GetSignerCertProps();
			CHECK_HRESULT_BREAK
		}

		pVal->vt = VT_BSTR;
		pVal->bstrVal = pDecCertInfo->bstrSubjectDN.copy();
	}
	while(0);
	return hr;

}

STDMETHODIMP CVSSC::get_IssuerDN(VARIANT *pVal)
{
	hr=S_OK;
	do
	{
		hr=CheckEnv(CHECK_INIT|CHECK_PTAVER);
	    CHECK_HRESULT_BREAK

		if(!bDecCert)
		{
			hr=GetSignerCertProps();
			CHECK_HRESULT_BREAK
		}

		pVal->vt = VT_BSTR;
		pVal->bstrVal = pDecCertInfo->bstrIssuerDN.copy();
	}
	while(0);
	return hr;

}

STDMETHODIMP CVSSC::get_SubjectSerialNumber(VARIANT *pVal)
{
	hr=S_OK;
	do
	{
		hr=CheckEnv(CHECK_INIT|CHECK_PTAVER);
	    CHECK_HRESULT_BREAK

		if(!bDecCert)
		{
			hr=GetSignerCertProps();
			CHECK_HRESULT_BREAK
		}

		pVal->vt = VT_BSTR;
		pVal->bstrVal = pDecCertInfo->bstrSerNum.copy();
	}
	while(0);
	return hr;

}

STDMETHODIMP CVSSC::get_SubjectValidFrom(DATE *pVal)
{
	hr=S_OK;
	do
	{
		hr=CheckEnv(CHECK_INIT|CHECK_PTAVER);
	    CHECK_HRESULT_BREAK

		if(!bDecCert)
		{
			hr=GetSignerCertProps();
			CHECK_HRESULT_BREAK
		}
		
		*pVal = pDecCertInfo->dateEffDate;
	}
	while(0);
	return hr;

}

STDMETHODIMP CVSSC::get_SubjectValidTo(DATE *pVal)
{
	hr=S_OK;
	do
	{
		hr=CheckEnv(CHECK_INIT|CHECK_PTAVER);
	    CHECK_HRESULT_BREAK

		if(!bDecCert)
		{
			hr=GetSignerCertProps();
			CHECK_HRESULT_BREAK
		}
		
		*pVal=pDecCertInfo->dateExpDate;
	}
	while(0);
	return hr;

}

HRESULT CVSSC::GetSignerCertProps()
{
	hr=S_OK;
	
	PCERT_INFO			pResolveSignerInfo=NULL;    
	VSSC_ENCODED_CERT	EncodedCert;
	CUserInfo			*pObj=NULL;
	_bstr_t             bstrInit(_T(""));
	
	
	do
	{
		
		pDecCertInfo->bstrIssuerDN=bstrInit;
		pDecCertInfo->bstrSerNum=bstrInit;
		pDecCertInfo->bstrSubjectDN=bstrInit;
		pDecCertInfo->bstrSubjectDN_CN=bstrInit;
		pDecCertInfo->bstrSubjectDN_E=bstrInit;
		pDecCertInfo->bstrSubjectDN_O=bstrInit;
		pDecCertInfo->bstrSubjectDN_OU=bstrInit;
		

		

		pDecCertInfo->dateEffDate=0;
		pDecCertInfo->dateExpDate=0;

		pDecCertInfo->nKeySize=0;
		pDecCertInfo->nKeyUsage=0;
		
		if(m_pMsg->m_SignerCertList.empty())
		{
			hr=E_SIGNER_CERTNOTFOUND;
			break;
		}

		it=m_pMsg->m_SignerCertList.begin();
		pObj=(*it);

		if(pObj==NULL)
		{
			hr=E_SIGNER_CERTNOTFOUND;
			break;
		}

		if(pObj->stCertReqResponseInfo.dwStatus==0)
		{
		}

		EncodedCert=pObj->GetSignerCert();
		if(EncodedCert.pbData==NULL)
		{
			hr=E_SIGNER_CERTNOTFOUND;
			break;
		}
		
		CCertInfo  ResolveSignerInfo(EncodedCert.pbData,EncodedCert.cbData);
		pResolveSignerInfo=ResolveSignerInfo.GetCertInfo();

		/////Initialize Struct
		
		hr=_DecodeCertInfo(pResolveSignerInfo,pDecCertInfo);
		CHECK_HRESULT_BREAK
		        
		bDecCert=TRUE;
	}
	while(0);
	if(pResolveSignerInfo)
		freecertinfo(pResolveSignerInfo);

	FREE_MEMORY(pResolveSignerInfo)
    return hr;

}




STDMETHODIMP CVSSC::get_HostFQDN(VARIANT *pVal)
{
	hr = S_OK;
	do
	{
		hr=CheckEnv(CHECK_INIT|CHECK_PTAVER);
		CHECK_HRESULT_BREAK

		if(!bComposeCalled)
		{
			 pVal->bstrVal=NULL;
			 return hr;
		}

		pVal->vt = VT_BSTR;
		if((gp_AppContext->bstrHostName.length())>0)
			pVal->bstrVal=gp_AppContext->bstrHostName.copy();
		else
			pVal->bstrVal=NULL;
	}
	while(0);

	return hr;
}

STDMETHODIMP CVSSC::put_HostFQDN(VARIANT newVal)
{
	hr = S_OK;
	_bstr_t   bstrHostName;

	do
	{
		
		///Check for BSTR//////
		if(newVal.vt != VT_BSTR)
		{
			//return Invalid argument;
			hr=E_VSSC_INVALIDARGS;
			break;
		}

		if(!m_bInitialized)
		{
			hr = E_NOTINITIALIZED;
			_SetErrorInfo(hr);
			break;
		}

		bstrHostName=newVal.bstrVal;

		if(gp_AppContext->bstrHostName.length()==0)
		{
			gp_AppContext->bstrHostName=bstrHostName;
			
		}
		else
		{

			if(!(gp_AppContext->bstrHostName==bstrHostName))
			{
				hr=E_HOST_NOT_MATCH;
				break;
			}

		}
		
	}
	while(0);
	return hr;
	
	
}

STDMETHODIMP CVSSC::get_HostProtocol(VARIANT *pVal)
{
	hr = S_OK;
	do
	{
		hr=CheckEnv(CHECK_INIT|CHECK_PTAVER);
		CHECK_HRESULT_BREAK

		if(!bComposeCalled)
		{
			 pVal->bstrVal=NULL;
			 return hr;
		}

		pVal->vt = VT_BSTR;
		if((gp_AppContext->bstrProtocolName.length())>0)
			pVal->bstrVal=gp_AppContext->bstrProtocolName.copy();
		else
			pVal->bstrVal=NULL;
	}
	while(0);

	return hr;
}

STDMETHODIMP CVSSC::put_HostProtocol(VARIANT newVal)
{
	hr = S_OK;
	_bstr_t   bstrHostProtocol;

	do
	{
		
		///Check for BSTR//////
		if(newVal.vt != VT_BSTR)
		{
			//return Invalid argument;
			hr=E_VSSC_INVALIDARGS;
			break;
		}

		if(!m_bInitialized)
		{
			hr = E_NOTINITIALIZED;
			_SetErrorInfo(hr);
			break;
		}

		bstrHostProtocol=newVal.bstrVal;

		if(gp_AppContext->bstrProtocolName.length()==0)
		{
			gp_AppContext->bstrProtocolName=bstrHostProtocol;
			
		}
		else
		{

			if(!(gp_AppContext->bstrProtocolName==bstrHostProtocol))
			{
				hr=E_FAIL;
				break;
			}

		}
		
	}
	while(0);
	return hr;
}

STDMETHODIMP CVSSC::GetAttachFileContent(VARIANT *in_pvarFileName,VARIANT* i_pvarAppStatus,
											VARIANT *o_pvarFileContent)
{
   hr=S_OK;
   
   char      *pszInput=NULL;
   
   BYTE		 *pbDecodeData=NULL;
   DWORD	  dwDecodedData=0;	

   do
   {

	   if(in_pvarFileName->vt != VT_BSTR)
	   {
				//return Invalid argument;
				hr=E_VSSC_INVALIDARGS;
				break;
	   }

	   hr=CheckEnv(CHECK_INIT|CHECK_PTAVER);
	   CHECK_HRESULT_BREAK

	   VARIANT var;
	   VariantInit(&var);  	
		
		   
	   pszInput= _WideToMultiString(in_pvarFileName->bstrVal);
	   CHECK_MEM_BREAK(pszInput)
	   
	   
	   FILEINFO		*pTmpFileInfo=NULL;
	   pTmpFileInfo= m_pMsg->m_FILEINFO_AttachFileInfoList;

	   if(pTmpFileInfo)
		{
		
			while(pTmpFileInfo)
			{
				
					if(strnicmp(pszInput,pTmpFileInfo->szFileName,strlen(pTmpFileInfo->szFileName))==0)
					{	
						
						if(pTmpFileInfo->pbFileData!=NULL &&
														  pTmpFileInfo->cbFileSize!=0)
						{
								_Base64Decode(
									(char*)pTmpFileInfo->pbFileData,
									 pTmpFileInfo->cbFileSize,
									 NULL,
									 &dwDecodedData) ;
								if(!dwDecodedData)
								{	
									break;
								}
								
								pbDecodeData = (BYTE*)malloc(dwDecodedData); 
								CHECK_MEM_BREAK(pbDecodeData)

								_Base64Decode(
											 (char*)pTmpFileInfo->pbFileData,
											  pTmpFileInfo->cbFileSize,
											  (char *)pbDecodeData,
											  &dwDecodedData
											  ) ;
								if (!pbDecodeData)
								{
									break;
								}

						}
					

						//Set the type to an array of unsigned chars (OLE SAFEARRAY)
						var.vt = VT_ARRAY | VT_UI1;

						//Set up the bounds structure
						SAFEARRAYBOUND  rgsabound[1];

						rgsabound[0].cElements = dwDecodedData;
						rgsabound[0].lLbound = 0;

						//Create an OLE SAFEARRAY
						var.parray = SafeArrayCreate(VT_UI1,1,rgsabound);

						if(var.parray != NULL && pbDecodeData!=NULL)
						{
						   void * pArrayData = NULL;

						   //Get a safe pointer to the array
						   SafeArrayAccessData(var.parray,&pArrayData);

						   //Copy data to it
						   memcpy(pArrayData, pbDecodeData,dwDecodedData);

						   //Unlock the variant data
						   SafeArrayUnaccessData(var.parray);
				   

						}

						*o_pvarFileContent = var; 
						
				
						break;

					}
				
					pTmpFileInfo = pTmpFileInfo->next;
			}
		}

	   
   }
   while(0);

   FREE_MEMORY(pszInput)
   FREE_MEMORY(pbDecodeData)

   i_pvarAppStatus->vt=VT_I4;
   i_pvarAppStatus->lVal=g_dwAppErr;

   return hr;

}


STDMETHODIMP CVSSC::put_AddSignerCertificate(VARIANT newVal)
{
	hr = S_OK;
	do
	{
		///Check for Type//////
		if(newVal.vt != VT_BOOL)
		{
			//return Invalid argument;
			hr=E_VSSC_INVALIDARGS;
			break;
		}

		hr=CheckEnv(CHECK_INIT|CHECK_PTAVER);
		CHECK_HRESULT_BREAK

		m_pMsg->m_bAddSignerCert=newVal.boolVal;
	
	}
	while(0);
	return hr;



}



STDMETHODIMP CVSSC::put_AddRFC822Header(VARIANT newVal)
{
	hr = S_OK;
	do
	{
		///Check for BSTR//////
		if(newVal.vt != VT_BOOL)
		{
			//return Invalid argument;
			hr=E_VSSC_INVALIDARGS;
			break;
		}

		hr=CheckEnv(CHECK_INIT|CHECK_PTAVER);
		CHECK_HRESULT_BREAK

		m_pMsg->m_bAddRFC822Header=newVal.boolVal;
	
	}
	while(0);
	return hr;
}

STDMETHODIMP CVSSC::put_AddMIMEHeader(VARIANT newVal)
{
	hr = S_OK;
	do
	{
		///Check for BSTR//////
		if(newVal.vt != VT_BOOL)
		{
			//return Invalid argument;
			hr=E_VSSC_INVALIDARGS;
			break;
		}

		hr=CheckEnv(CHECK_INIT|CHECK_PTAVER);
		CHECK_HRESULT_BREAK

		m_pMsg->m_bAddMIMEHeader=newVal.boolVal;
	
	}
	while(0);
	return hr;
}

STDMETHODIMP CVSSC::put_OpaqueSign(VARIANT newVal)
{
	hr = S_OK;
	do
	{
		///Check for BSTR//////
		if(newVal.vt != VT_BOOL)
		{
			//return Invalid argument;
			hr=E_VSSC_INVALIDARGS;
			break;
		}

		hr=CheckEnv(CHECK_INIT|CHECK_PTAVER);
		CHECK_HRESULT_BREAK
		m_pMsg->m_bOpaqueSign=newVal.boolVal;
	
	}
	while(0);
	return hr;
}

STDMETHODIMP CVSSC::put_AddSenderRecipientInfo(VARIANT newVal)
{
	hr = S_OK;
	do
	{
		///Check for BSTR//////
		if(newVal.vt != VT_BOOL)
		{
			//return Invalid argument;
			hr=E_VSSC_INVALIDARGS;
			break;
		}

		hr=CheckEnv(CHECK_INIT|CHECK_PTAVER);
		CHECK_HRESULT_BREAK

		m_pMsg->m_AddSenderRecipientInfo=newVal.boolVal;
	
	}
	while(0);
	return hr;

}


STDMETHODIMP CVSSC::get_SCType(VARIANT *pVal)
{
	hr = S_OK;
	do
	{
		hr=CheckEnv(CHECK_INIT|CHECK_PTAVER);
		CHECK_HRESULT_BREAK
		
		pVal->vt = VT_BSTR;
		if(m_pMsg->m_SCType.length()>0)
					pVal->bstrVal=m_pMsg->m_SCType.copy();
		else
					pVal->bstrVal=NULL;
	}
	while(0);
	return hr;
}

STDMETHODIMP CVSSC::put_SCType(VARIANT newVal)
{
	hr = S_OK;
	do
	{
		hr=CheckEnv(CHECK_INIT|CHECK_PTAVER);
		CHECK_HRESULT_BREAK

		///Check for BSTR//////
		if(newVal.vt != VT_BSTR)
		{
			//return Invalid argument;
			hr=E_VSSC_INVALIDARGS;
			break;
		}
		m_pMsg->m_SCType=newVal.bstrVal;
	}
	while(0);
	return hr;
   
}

STDMETHODIMP CVSSC::get_CertificateTimeOut(VARIANT *pVal)
{
	return S_OK;
}

STDMETHODIMP CVSSC::put_CertificateTimeOut(VARIANT newVal)
{
   hr=S_OK;

   do
   {
	   hr=CheckEnv(CHECK_INIT|CHECK_PTAVER);
	   CHECK_HRESULT_BREAK
	
	   if(newVal.vt == VT_I2)
	   {			
			g_dwCertTimeOut=newVal.iVal*60;	
	
	   }
		
   }
   while(0);


   return hr;
}

STDMETHODIMP CVSSC::get_MessageTimeOut(VARIANT *pVal)
{
	
	return S_OK;
}

STDMETHODIMP CVSSC::put_MessageTimeOut(VARIANT newVal)
{
   hr=S_OK;
   DWORD    dwMessageTimeOut=0;   /////in minute

   do
   {
	   hr=CheckEnv(CHECK_INIT|CHECK_PTAVER);
	   CHECK_HRESULT_BREAK
	
		if(newVal.vt == VT_I2)
		{			
			dwMessageTimeOut=newVal.iVal;	
			gp_GMemMgmt->VS_SetObjectTimeoutInterval(dwMessageTimeOut);
		}
		
   }
   while(0);

   return hr;

}

STDMETHODIMP CVSSC::ClearAll(VARIANT* i_pModeType,VARIANT* i_pvarAppStatus)
{

   hr=S_OK;

   try
   {
	   do
	   {
		   
		   if ( i_pModeType->iVal < 0 || i_pModeType->iVal>1)
		   {
			 hr =	E_VSSC_INVALID_MODE;
			 break;
		   }
			
		   /////
			g_dwAppErr=0;

		   //hr=CheckEnv(CHECK_INIT);
		   //CHECK_HRESULT_BREAK

			/////Delete From Memory
			
			hr=gp_GMemMgmt->DeleteObjectNodeWithOutID();
			//CHECK_HRESULT_BREAK
			

			if(i_pModeType->iVal==1)
			{
				
				break;
			}

			
			m_pMsg->Clear();

			g_dwCertTimeOut=0;
			bComposeCalled=FALSE;
			bUseInternetData=FALSE;
			m_bInitialized=FALSE;
			m_bFoundPTAVer=FALSE;

			
			
			/////Clear the global memory pointer
			if(g_pEncryptCertInGM!=NULL)
			{
					FreeCertList(g_pEncryptCertInGM);
					delete g_pEncryptCertInGM;
					g_pEncryptCertInGM=NULL;
			}

			if(NULL!=gp_GMemMgmt)
			{
					delete gp_GMemMgmt;
					gp_GMemMgmt=NULL;
			}

			if(NULL!=g_pSignerCertInGM)
			{
					FreeCertList(g_pSignerCertInGM);
					delete g_pSignerCertInGM;
					g_pSignerCertInGM=NULL;
			}

			if(gp_AppContext!=NULL)
			{
					delete gp_AppContext;
					gp_AppContext=NULL;
			}

			freeAttachInfo(g_AttachedFiles);
			DELETE_MEMORY(g_AttachedFiles)

	   }
	   while(0);
   }
   catch(...)
   {
	   hr=E_UNEXPECTED;
   }

   i_pvarAppStatus->vt=VT_I4;
   i_pvarAppStatus->lVal=g_dwAppErr;

   return hr;
}

STDMETHODIMP CVSSC::get_Issuer_DN(VARIANT *pVal)
{

	hr=S_OK;
	CUserInfo * pObj=NULL;
	
	do
	{
		hr=CheckEnv(CHECK_INIT|CHECK_RESFIRST|CHECK_PTAVER);
	    CHECK_HRESULT_BREAK
		pObj=(*ResolveIter);
		if(pObj==NULL)
		{
			break;
		}

		pVal->vt=VT_BSTR;
		if(pObj->DecCertInfo.bstrIssuerDN.length()>0)
				pVal->bstrVal=pObj->DecCertInfo.bstrIssuerDN.copy();
		else
			pVal->bstrVal=NULL;
	}
	while(0);
	
	return hr;

}

STDMETHODIMP CVSSC::get_SerialNumber(VARIANT *pVal)
{
	hr=S_OK;
	CUserInfo * pObj=NULL;

	do
	{
		hr=CheckEnv(CHECK_INIT|CHECK_RESFIRST|CHECK_PTAVER);
	    CHECK_HRESULT_BREAK

		pObj=(*ResolveIter);
		if(pObj==NULL)
			break;

		pVal->vt=VT_BSTR;
		if(pObj->DecCertInfo.bstrSerNum.length()>0)
				pVal->bstrVal=pObj->DecCertInfo.bstrSerNum.copy();
		else
			pVal->bstrVal=NULL;
	}
	while(0);
	
	return hr;
}

STDMETHODIMP CVSSC::put_UsePKCS7Certificate(VARIANT newVal)
{
	hr = S_OK;
	do
	{
		///Check for BSTR//////
		if(newVal.vt != VT_BOOL)
		{
			//return Invalid argument;
			hr=E_VSSC_INVALIDARGS;
			break;
		}

		hr=CheckEnv(CHECK_INIT|CHECK_PTAVER);
		CHECK_HRESULT_BREAK
		m_pMsg->m_bUsePKCS7Cert=newVal.boolVal;

	
	}
	while(0);

	return hr;
}

STDMETHODIMP CVSSC::put_AddSMIMECapabilities(VARIANT newVal)
{

	hr = S_OK;
	do
	{
		///Check for Type//////
		if(newVal.vt != VT_BOOL)
		{
			//return Invalid argument;
			hr=E_VSSC_INVALIDARGS;
			break;
		}

		hr=CheckEnv(CHECK_INIT|CHECK_PTAVER);
		CHECK_HRESULT_BREAK

		m_pMsg->m_bAddSMIMECap=newVal.boolVal;
	
	}
	while(0);
	return hr;
}

STDMETHODIMP CVSSC::put_AllowDecryption(VARIANT newVal)
{

   hr=S_OK;
   do
   {
	   hr=CheckEnv(CHECK_INIT|CHECK_PTAVER);
	   CHECK_HRESULT_BREAK
	
		if(newVal.vt == VT_I2)
		{			
			m_pMsg->m_dwAllowDecryption=newVal.iVal;	
		
		}
		
   }
   while(0);

   return hr;

}

STDMETHODIMP CVSSC::put_SupportedPTAVer(VARIANT newVal)
{
   hr=S_OK;
   int nSupportedPTAVer=0,nInstalledPTAVer=0;
   
   char szInstallPTAVer[VS_MAX_LEN]; 
   char *pszSupportedVers=NULL,*pszVer=NULL;


   do
   {
	   hr=CheckEnv(CHECK_INIT);
	   CHECK_HRESULT_BREAK
	
		if(newVal.vt == VT_BSTR)
		{	
			pszSupportedVers=_WideToMultiString(newVal.bstrVal);
			CHECK_MEM_BREAK(pszSupportedVers)
		
			hr=InstalledPTAVer(szInstallPTAVer);
			CHECK_HRESULT_BREAK
			nInstalledPTAVer=atoi(szInstallPTAVer);

			pszVer=strtok(pszSupportedVers,",");
			while(pszVer!=NULL)
			{
				nSupportedPTAVer=atoi(pszVer);
				if(nInstalledPTAVer==nSupportedPTAVer)
				{
					m_bFoundPTAVer=TRUE;
					break;
				}
				pszVer=strtok(NULL,",");
			}

			if(!m_bFoundPTAVer)
			{
				hr=E_DIFERENT_PTAVER;
			}


		}


		
   }
   while(0);

   FREE_MEMORY(pszSupportedVers)

   return hr;
	
	
}

STDMETHODIMP CVSSC::get_InstalledPTAVer(VARIANT *pVal)
{
	hr=S_OK;

	char   szInstallPTAVer[VS_MAX_LEN];
	
	do
	{
		hr=CheckEnv(CHECK_INIT);
		CHECK_HRESULT_BREAK

		hr=InstalledPTAVer(szInstallPTAVer);
		CHECK_HRESULT_BREAK

		pVal->vt = VT_I2;
		if(lstrlen(szInstallPTAVer)>0)
				pVal->iVal=atoi(szInstallPTAVer);
		else
				pVal->iVal=0;
		

	}
	while(0);
	
	return hr;
}



STDMETHODIMP CVSSC::get_RevocationStatus(VARIANT *pVal)
{
	CUserInfo * pObj=NULL;
	hr=S_OK;

	do
	{
		hr=CheckEnv(CHECK_INIT|CHECK_RESFIRST|CHECK_PTAVER);
	    CHECK_HRESULT_BREAK

		pObj=(*ResolveIter);
		if(pObj==NULL)
			break;
		
		pVal->vt=VT_I4;
		pVal->lVal=pObj->stCertStatusInfo.dwRevocationStatus;
		
	}
	while(0);

	return hr;
}

STDMETHODIMP CVSSC::get_ChainValidationStatus(VARIANT *pVal)
{
	CUserInfo * pObj=NULL;
	hr=S_OK;

	do
	{
		hr=CheckEnv(CHECK_INIT|CHECK_RESFIRST|CHECK_PTAVER);
	    CHECK_HRESULT_BREAK

		pObj=(*ResolveIter);
		if(pObj==NULL)
					break;
		
		pVal->vt=VT_I4;
		pVal->lVal=pObj->stCertStatusInfo.dwChainValidationStatus;
		
	}
	while(0);

	return hr;
}

STDMETHODIMP CVSSC::get_IsCertExpired(VARIANT *pVal)
{
	CUserInfo * objUserInfo=NULL;
	hr=S_OK;

	do
	{
		hr=CheckEnv(CHECK_INIT|CHECK_RESFIRST|CHECK_PTAVER);
	    CHECK_HRESULT_BREAK

		objUserInfo=(*ResolveIter);

		if(objUserInfo==NULL)
		{
			//fix
			//g_dwAppErr=
			break;
		}

		pVal->vt=VT_BOOL;

		SYSTEMTIME      stSysTime;
		DATE			dtDate;

		GetSystemTime(&stSysTime);
		if(!SystemTimeToVariantTime(&stSysTime,&dtDate))
		{
			hr = E_SYSTIMETOVARTIMEFAILED;
			
		}
		
		if(!(objUserInfo->DecCertInfo.dateEffDate<dtDate
			&&dtDate<objUserInfo->DecCertInfo.dateExpDate))
		{
			pVal->lVal=TRUE;
					
		}
		else
		{
			pVal->lVal=FALSE;

		}


		
		
	}
	while(0);

	return hr;
	
	
}

HRESULT CVSSC::InstalledPTAVer(char *szPTAver)
{
	hr=S_OK;
	long   err;
	
	DWORD dwType=REG_SZ;
	
	TCHAR szKey[VS_MAX_LEN];
	TCHAR szPathName[VS_MAX_LEN];

	
	HKEY hRegKey = NULL;
	ULONG lSize = VS_MAX_LEN;

	do
	{

			_tcscpy(szKey, _T("CLSID\\{6F7864F9-DB33-11D3-8166-0060B0F885E6}\\InprocServer32"));
			err=RegOpenKeyEx(HKEY_CLASSES_ROOT, szKey,0,KEY_READ, &hRegKey);
			
			if(err!= ERROR_SUCCESS) 
			{
				hr=E_REGOPEN_KEY;
				g_dwAppErr=E_UNABLE_TOFIND_PTAVER;
				break;
			}
				

			err=RegQueryValueEx(hRegKey, NULL, NULL, &dwType, 
														( BYTE *)szPathName, &lSize);
			if(err!=ERROR_SUCCESS)
			{
				hr=E_REGQUERY_KEY;
				g_dwAppErr=E_UNABLE_TOFIND_PTAVER;
				break;
			}
			
			RegCloseKey(hRegKey);

			GetVers(szPathName,szPTAver);
	}
	while(0);

	return hr;

}

STDMETHODIMP CVSSC::put_ShowSelIDUI(VARIANT newVal)
{

	IVSPTADllApi *pPTADllApi = NULL;

	hr = S_OK;
	do
	{
		///Check for BSTR//////
		if(newVal.vt != VT_BOOL)
		{
			//return Invalid argument;
			hr=E_VSSC_INVALIDARGS;
			break;
		}

		hr=CheckEnv(CHECK_INIT|CHECK_PTAVER);
		CHECK_HRESULT_BREAK
		
		
		pVSPTA = (IVSPTA*)_GetInterface(IID_IVSPTA);
		if(!pVSPTA)
		{
			return E_NOINTERFACE;
			
		}
		
		
		hr = pVSPTA->QueryInterface(IID_IVSPTADllApi, (void **) &(pPTADllApi));
		if(hr != S_OK)
		{
			
			break;
		}

		hr=pPTADllApi->put_ShowSelIDUI(newVal);
		CHECK_HRESULT_BREAK

	
	}
	while(0);

	return hr;
	
}

STDMETHODIMP CVSSC::put_URLEncodeData(VARIANT newVal)
{
	hr = S_OK;
	do
	{
		///Check for BSTR//////
		if(newVal.vt != VT_BOOL)
		{
			//return Invalid argument;
			hr=E_VSSC_INVALIDARGS;
			break;
		}

		hr=CheckEnv(CHECK_INIT|CHECK_PTAVER);
		CHECK_HRESULT_BREAK

		m_pMsg->m_bURLEncodeData=newVal.boolVal;
	
	}
	while(0);
	return hr;
}



STDMETHODIMP CVSSC::put_UseSimder(VARIANT newVal)
{
	
	hr = S_OK;
	do
	{
		///Check for BSTR//////
		if(newVal.vt != VT_BOOL)
		{
			//return Invalid argument;
			hr=E_VSSC_INVALIDARGS;
			break;
		}

		hr=CheckEnv(CHECK_INIT|CHECK_PTAVER);
		CHECK_HRESULT_BREAK
		m_pMsg->m_bUseSimder=newVal.boolVal;

	
	}
	while(0);

	return hr;

	
}
