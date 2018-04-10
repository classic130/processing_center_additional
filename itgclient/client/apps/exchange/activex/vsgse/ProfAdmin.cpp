// ProfAdmin.cpp: implementation of the CProfAdmin class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ProfAdmin.h"
#include <winsock2.h>
#include "vsgseutil.h"

/*
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
*/

#define TraceFnResult(f, hr)
#define PR_REPLICA_VERSION PROP_TAG(PT_I8, 0x664b)

#define  ID_BARNAME  "EncryptSign"
#define  ID_EXTNAME  "VSGSEEXT.dll"

/*--------------------Exchnage Version Information ------------------*/
#define DEFAULT_PORT		  143
#define DEFAULT_PROTO		  SOCK_STREAM   // TCP

#define EX_VERSION            "version"
#define  LEGACY_EXCHANGE      "legacyExchangeDN"
/*-----------------------------------------------------------------*/
// Start Change : Infosys : CR29538 
#define MDB_ONLINE ((ULONG) 0x00000100)
//End Change : Infosys : CR29538

// Start Change : Infosys : CR21346
// Added user first name and last name to the array list.
//WCHAR    *attrs[6]={L"cn",L"distinguishedName",L"Home-MTA",L"rfc822Mailbox",L"uid",NULL};
//WCHAR    *exch2k_attrs[7]={L"cn",L"distinguishedName",L"Home-MTA",L"proxyAddresses",L"mailNickname",L"userPrincipalName",NULL};
WCHAR    *attrs[8]={L"cn",L"distinguishedName",L"Home-MTA",L"rfc822Mailbox",L"uid",L"givenName",L"sn",NULL};
WCHAR    *exch2k_attrs[9]={L"cn",L"distinguishedName",L"Home-MTA",L"proxyAddresses",L"mailNickname",L"userPrincipalName",L"givenName",L"sn",NULL};
// End Change : Infosys : CR21346

WCHAR    *exch2k_updateattrs[3]={L"objectSid",L"userCertificate",NULL};


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CProfAdmin::CProfAdmin()
{

	 #ifdef	_VS_LOG_MSG_
		VSGSE_Log(FALSE, L"INFO: Start Logging");
//		::MessageBox(NULL,"Start Logging","VSGSE",MB_OK);
     #endif


	 gbDefOutLookClient=TRUE;
	 hr = MAPIInitialize(NULL);
	 if(FAILED(hr))
	 {
		#ifdef	_VS_LOG_MSG_
			VSGSE_Log(FALSE,L"MAPIInitialize:Error Code : 0x%08X",hr);
	    #endif

		gbDefOutLookClient=FALSE;
		
	 }
	 else
	 {
		 #ifdef	_VS_LOG_MSG_
			VSGSE_Log(FALSE,L"MAPIInitialize:Successful" );
	     #endif
	 }




	 
	 ghbstrUserCertificate="";
	 ghbstrSMIMECertificate="";
	 ghbstrADServerInfoList="";
	 pdispItem=NULL;

	 gh_CAInfo=0;
	 ghExch_UpdateVer=EXCH_55;
	 ghExchVer=-1;
	 ghADServerInfo=0;


	 gLDAPAccess=FALSE;
	 ghVer=FALSE;
	 bRenewCert=FALSE;
	 bSetEFSCert=FALSE;

	 gMailBoxInfo.bstrcn="";
	 gMailBoxInfo.bstrdistinguishedName="";
	 gMailBoxInfo.bstrHome_MTA="";
	 gMailBoxInfo.bstrrfc822Mailbox="";
	 gMailBoxInfo.bstruid="";
	 gMailBoxInfo.bstrUserDN="";
	 gMailBoxInfo.bstrupn="";

	 ghbstrExchVerStr="";

	 ptbstrDNAttrs=NULL;
     ptbstrDNVals=NULL;

	 pProfAdmin=NULL;
     pSvcAdmin =NULL;
     pMsgSvcTable=NULL;
	 pProfileTable=NULL;

	 // Start Add : Infosys : CR27993
 	 // This flag specifies whether the certificate issued is to be set as a default certificate 
	 // for Signing, Encryption or Both. Default is set to both which can be altered using the exposed
	 // method put_SetDefaultCertFlag.
	 nSetDefaultCertFlag = SET_DEFAULT_FOR_BOTH;
	 // End Add : Infosys : CR27993
	 
}

CProfAdmin::~CProfAdmin()
{
	MAPIUninitialize();

	if(pdispItem!=NULL)
		pdispItem->Release();

	
}

HRESULT CProfAdmin::GetDefaultProfile(_bstr_t  *i_bstrDefProfile)
{
	  
	  
	  SRestriction   sres;
      SPropValue     spvDefaultProfile;
      LPSRowSet      pRow = NULL;

	  LPMAPIERROR   lpMapiError=NULL;
	  ULONG          mFlag=0;//MAPI_UNICODE ;
      LPSTR          lpDisplayName = NULL;

	  _bstr_t        bstrProfile="";

	  #ifdef	_VS_LOG_MSG_
			VSGSE_Log(FALSE,L"GetDefaultProfile start");
	  #endif

	  
      // Get a IProfAdmin Interface.
      hr = MAPIAdminProfiles(0, &pProfAdmin);
	  if(FAILED(hr))
	  {
		  #ifdef	_VS_LOG_MSG_
			VSGSE_Log(FALSE,L"GetDefaultProfile:MAPIAdminProfiles:Error Code : 0x%08X",hr);
		  #endif
	 	
		  goto Quit;
	  }
	 
      
      // Get the Table of Profiles
      hr = pProfAdmin->GetProfileTable(0, &pProfileTable);
	  if(FAILED(hr))
	  {
		  #ifdef	_VS_LOG_MSG_
			VSGSE_Log(FALSE,L"GetDefaultProfile:pProfAdmin->GetProfileTable:Error Code : 0x%08X",hr);
	      #endif

		  goto Quit;
	  }

      // build a restriction where PR_DEFAULT_PROFILE = TRUE
      spvDefaultProfile.ulPropTag = PR_DEFAULT_PROFILE;
      spvDefaultProfile.Value.b = TRUE;

      sres.rt = RES_PROPERTY;
      sres.res.resProperty.relop = RELOP_EQ;
      sres.res.resProperty.ulPropTag = PR_DEFAULT_PROFILE;
      sres.res.resProperty.lpProp = &spvDefaultProfile;

      hr = pProfileTable->Restrict(&sres, TBL_BATCH);
	  if(FAILED(hr))
	  {
		  #ifdef	_VS_LOG_MSG_
			VSGSE_Log(FALSE,L"GetDefaultProfile:pProfileTable->Restrict:Error Code : 0x%08X",hr);
	      #endif
		  goto Quit;
	  }


      hr = pProfileTable->FindRow(&sres, BOOKMARK_BEGINNING, 0);
	  if(FAILED(hr))
	  {
		  #ifdef	_VS_LOG_MSG_
			VSGSE_Log(FALSE,L"GetDefaultProfile:pProfileTable->FindRow:Error Code : 0x%08X",hr);
	      #endif

		  if(hr==MAPI_E_NOT_FOUND)
					hr=S_OK;
    	   goto Quit;
	  }
      // we have a match
      hr = pProfileTable->QueryRows(1,0,&pRow);
      if (SUCCEEDED(hr))
      {
		 if(pRow->cRows==0)
		 {
			 hr=S_OK;
			 goto Quit;
		 }
         
		 bstrProfile=pRow->aRow[0].lpProps[0].Value.lpszA;
		 *i_bstrDefProfile=bstrProfile;

		 #ifdef	_VS_LOG_MSG_
			VSGSE_Log(FALSE,L"GetDefaultProfile Profile Name:=%s",
				_MultiToWideString(pRow->aRow[0].lpProps[0].Value.lpszA));
			VSGSE_Log(FALSE,L"GetDefaultProfile:done");
    	 #endif


      }
	  else {
		if(hr==MAPI_E_NOT_FOUND)
					hr=S_OK;
	  }




	  Quit:
	   if(pProfileTable)
	   {
		   if(pRow)
		   {
				FreeProws(pRow);
				pRow=NULL;
		   }

		   pProfileTable -> Release();
           pProfileTable = NULL;

	   }

	   if ( pProfAdmin )
         {
            pProfAdmin -> Release ( );
            pProfAdmin = NULL;
         }


	  return hr;
}

HRESULT CProfAdmin::IsExchProfile(_bstr_t& i_bstrProfileName)
{
      LPMAPITABLE     pTable = NULL;
      LPSRowSet       pRow = NULL;
      
	  SRestriction    sres;
      SPropValue      spv;

	  ULONG ul=0,ulFlags = 0L,ulObjType = 0L;

	  
	  // Get the row from the message service table that represents the
      // Microsoft Exchange Server service provider.
       static SizedSPropTagArray(1, Columns) =   {1, {PR_DISPLAY_NAME}};

	   #ifdef	_VS_LOG_MSG_
			VSGSE_Log(FALSE,L"IsExchProfile:start");
	   #endif

      	  
	   //  Get IProfAdmin interface pointer.
       if ( FAILED ( hr = MAPIAdminProfiles ( 0L, &pProfAdmin ) ) )
	   {
		  #ifdef	_VS_LOG_MSG_
			VSGSE_Log(FALSE,L"IsExchProfile:MAPIAdminProfiles:Error Code : 0x%08X",hr);
	      #endif
          goto Quit;
	   }

	   // Get IMsgServiceAdmin interface pointer.
        hr = pProfAdmin -> AdminServices(i_bstrProfileName, "", 0L, 0L,
							&pSvcAdmin );
		if(FAILED(hr))
		{
			#ifdef	_VS_LOG_MSG_
			VSGSE_Log(FALSE,L"IsExchProfile:pProfAdmin -> AdminServices:Error Code : 0x%08X",hr);
			#endif
			goto Quit;
		}
	
        // Get the message service table of the Message service.
        if ( FAILED ( hr = pSvcAdmin->GetMsgServiceTable(0L,
                                       &pMsgSvcTable) ) )
		{
           #ifdef	_VS_LOG_MSG_
			VSGSE_Log(FALSE,L"IsExchProfile:pSvcAdmin->GetMsgServiceTable:Error Code : 0x%08X",hr);
		   #endif 
           goto Quit;
		}
		

         // Restrict the columns to just PR_DISPLAY_NAME 
         hr = pMsgSvcTable->SetColumns((LPSPropTagArray)&Columns, 0);

         if (FAILED(hr))
         {
			 #ifdef	_VS_LOG_MSG_
				VSGSE_Log(FALSE,L"IsExchProfile:pMsgSvcTable->SetColumns:Error Code : 0x%08X",hr);
			 #endif
              goto Quit;
         }

         // Set up a restriction for the Exchange Server Service.
         sres.rt = RES_PROPERTY;
         sres.res.resProperty.relop = RELOP_EQ;
         sres.res.resProperty.ulPropTag = PR_SERVICE_NAME;
         sres.res.resProperty.lpProp = &spv;

         spv.ulPropTag = PR_SERVICE_NAME;
         spv.Value.lpszA = "MSEMS";

         // Call FindRow with that restriction
         hr = pMsgSvcTable->FindRow(&sres, BOOKMARK_BEGINNING, 0);

         if (SUCCEEDED(hr))
         {
            // We have found the Service. 
            LPSPropValue   lpProp  =   NULL;
            hr = pMsgSvcTable->QueryRows(1, 0, &pRow);
            if (FAILED(hr))
            {
				#ifdef	_VS_LOG_MSG_
					VSGSE_Log(FALSE,L"IsExchProfile:pMsgSvcTable->QueryRows:Error Code : 0x%08X",hr);
				#endif
               goto Quit;
            }

            // It would not make sense to have more than one row returned in
            // this case.
            if (pRow->cRows != 1)
            {
               hr = (E_FAIL);
               goto Quit;
            }
			//return TRUE;
			#ifdef	_VS_LOG_MSG_
			VSGSE_Log(FALSE,L"IsExchProfile:Yes");
			VSGSE_Log(FALSE,L"IsExchProfile:done");
	        #endif
   

			hr=1;
         }
		 else
			 if(hr==MAPI_E_NOT_FOUND)
			 {
				 #ifdef	_VS_LOG_MSG_
					VSGSE_Log(FALSE,L"IsExchProfile:pMsgSvcTable->FindRow:Error Code : 0x%08X",hr);
				 #endif
				 return hr;
			 }
    
     Quit:
		 if (pMsgSvcTable )
         {
            if(pRow)
			{
				FreeProws( pRow );
				pRow = NULL;
			}

            pMsgSvcTable -> Release ( );
            pMsgSvcTable = NULL;
         }


         if ( pSvcAdmin )
         {
            pSvcAdmin -> Release ( );
            pSvcAdmin = NULL;
         }

         if ( pProfAdmin )
         {
            pProfAdmin -> Release ( );
            pProfAdmin = NULL;
         } 
	     return hr;

}

HRESULT CProfAdmin::GetProfileInfo(_bstr_t& i_bstrProfile, ProfileInfo *pProfileInfo)
{
	LPPROFSECT    pGlobalProfSect = NULL; 
    LPSPropValue  pProps = NULL; 

	#ifdef	_VS_LOG_MSG_
		VSGSE_Log(FALSE,L"GetProfileInfo:start");
	#endif


	
     // Get a Profile admin object
     if ( FAILED ( hr = MAPIAdminProfiles ( 0L, &pProfAdmin ) ) )
	 {
		#ifdef	_VS_LOG_MSG_
			VSGSE_Log(FALSE,L"GetProfileInfo:MAPIAdminProfiles:Error Code : 0x%08X",hr);
	    #endif
        goto Quit;
	 }
	 
     // Get a ServiceAdmin object
     if ( FAILED ( hr = pProfAdmin -> AdminServices (
                                           i_bstrProfile,
                                           NULL,
                                           0L,  
                                           0L,
                                           &pSvcAdmin ) ) )
	 {
		#ifdef	_VS_LOG_MSG_
			VSGSE_Log(FALSE,L"GetProfileInfo:pProfAdmin -> AdminServices:Error Code : 0x%08X",hr);
	    #endif
       goto Quit;
	 }

      // Get the Global Profile Section by calling
      // IServiceAdmin::OpenProfileSection use pbGlobalProfileSectionGuid
      // defined in EDKMDB.H as the entry ID to request
      // The default return is an IProfSect interface.
      if ( FAILED ( hr = pSvcAdmin -> OpenProfileSection (
                                  (LPMAPIUID)pbGlobalProfileSectionGuid,
                                  NULL,
                                  0L,
                                  &pGlobalProfSect ) ) )
	  {
		  #ifdef	_VS_LOG_MSG_
			VSGSE_Log(FALSE,L"GetProfileInfo:pSvcAdmin -> OpenProfileSection:Error Code : 0x%08X",hr);
		#endif
         goto Quit;
	  }

	  #ifdef	_VS_LOG_MSG_
		VSGSE_Log(FALSE,L"GetProfileInfo:OpenProfileSection");
      #endif


      // Call HrGetOneProp to get PR_PROFILE_HOME_SERVER
      if ( FAILED ( hr = HrGetOneProp ( pGlobalProfSect,
                                          PR_PROFILE_HOME_SERVER,
                                          &pProps ) ) )
	  {
		 #ifdef	_VS_LOG_MSG_
			VSGSE_Log(FALSE,L"GetProfileInfo:PR_PROFILE_HOME_SERVER:Error Code : 0x%08X",hr);
	     #endif
         goto Quit;
	  }

      // HrGetOneProp
      
        pProfileInfo->bstrHomeServer=pProps -> Value.lpszA;
		pProfileInfo->bstrExchServer=pProps -> Value.lpszA;
	  	ghbstrHomeServer=pProps -> Value.lpszA;

		#ifdef	_VS_LOG_MSG_
			VSGSE_Log(FALSE,L"GetProfileInfo:HOME_SERVER:%s",
				_MultiToWideString(pProps -> Value.lpszA));
        #endif

  
  	  //////////
	  if ( FAILED ( hr = HrGetOneProp ( pGlobalProfSect,
                                          PR_PROFILE_USER ,
                                          &pProps ) ) )
	  {
		  #ifdef	_VS_LOG_MSG_
			VSGSE_Log(FALSE,L"GetProfileInfo:PR_PROFILE_USER:Error Code : 0x%08X",hr);
	      #endif
         goto Quit;
	  }

      
	  pProfileInfo->bstrProfileUser=pProps -> Value.lpszA;

	  #ifdef	_VS_LOG_MSG_
			VSGSE_Log(FALSE,L"GetProfileInfo:PR_PROFILE_USER:%s",
				_MultiToWideString(pProps -> Value.lpszA));
      #endif


	  // fill in the legacyExchangeDN for exchage 2000
	  pProfileInfo->bstrLegacyExchangeDN="(";
	  pProfileInfo->bstrLegacyExchangeDN+=LEGACY_EXCHANGE;
	  pProfileInfo->bstrLegacyExchangeDN+="=";
	  pProfileInfo->bstrLegacyExchangeDN+=pProps -> Value.lpszA;
	  pProfileInfo->bstrLegacyExchangeDN+=")"; 
	  ///////	


	  if ( FAILED ( hr = HrGetOneProp ( pGlobalProfSect,
                                          PR_PROFILE_HOME_SERVER_DN  ,
                                          &pProps ) ) )
	  {
		  #ifdef	_VS_LOG_MSG_
			VSGSE_Log(FALSE,L"GetProfileInfo:PR_PROFILE_HOME_SERVER_DN:Error Code : 0x%08X",hr);
	      #endif
         goto Quit;
	  }

	  pProfileInfo->bstrHomeServerDN=pProps -> Value.lpszA;

	  #ifdef	_VS_LOG_MSG_
		VSGSE_Log(FALSE,L"GetProfileInfo:done");
      #endif

   
     Quit:
      // Free all memory allocated by any MAPI calls
	     if ( pSvcAdmin )
         {
            pSvcAdmin -> Release ( );
            pSvcAdmin = NULL;
         }

         if ( pProfAdmin )
         {
            pProfAdmin -> Release ( );
            pProfAdmin = NULL;
         } 

	return hr;
}

HRESULT CProfAdmin::EnumExchProfile()
{

      LPSRowSet      pRow = NULL;
	  int            bExch=0;

	  SizedSPropTagArray (1, spta ) =
         {1, PR_DISPLAY_NAME};

	  gNumOfExchProfile=0;

	  #ifdef	_VS_LOG_MSG_
			VSGSE_Log(FALSE,L"EnumExchProfile:start");
	  #endif

      // Get a IProfAdmin Interface.
      hr = MAPIAdminProfiles(0, &pProfAdmin);
	  if(FAILED(hr))
	  {
		  #ifdef	_VS_LOG_MSG_
			VSGSE_Log(FALSE,L"EnumExchProfile:MAPIAdminProfiles:Error Code : 0x%08X",hr);
	      #endif
		  goto Quit;
	  }
      
      // Get the Table of Profiles
      hr = pProfAdmin->GetProfileTable(0, &pProfileTable);
      hr=HrQueryAllRows(pProfileTable,(LPSPropTagArray)&spta,NULL,NULL,0,&pRow);
      if (SUCCEEDED(hr))
      {
		  for( ULONG  i=0;i<pRow->cRows;i++)
		  {
				if (PR_DISPLAY_NAME ==pRow->aRow[i].lpProps[0].ulPropTag )
				{
					    _bstr_t bstrExchProfile=pRow->aRow[i].lpProps[0].Value.lpszA;
			    	    bExch=IsExchProfile(bstrExchProfile);
						if(bExch==1)
						{
							gNumOfExchProfile++;
						}
				
				}		  
		  
		  }

		  gTotalProfile=pRow->cRows;
		  hr=gNumOfExchProfile;

		  #ifdef	_VS_LOG_MSG_
			VSGSE_Log(FALSE,L"EnumExchProfile:done");
		  #endif

	  }
Quit:
	  return hr;

}

HRESULT CProfAdmin::GetAttributes()
{

	
	_bstr_t         bstrDefaultProfile="";

	if(!gbDefOutLookClient)
	{
		hr=E_NOTDEF_OUTLOOK_CLINET;
		goto Quit;
	}

	hr=GetDefaultProfile(&bstrDefaultProfile);
	if(hr!=0)
	 	goto Quit;

	if(bstrDefaultProfile.length()==0)
		goto Quit;

	hr=IsExchProfile(bstrDefaultProfile);
	if(hr==1)  //default is exchange profile
	{
		hr=GetProfileInfo(bstrDefaultProfile,&m_pInfo);
		if(FAILED(hr))
			goto Quit;

		ghbstrCurrentProfile=bstrDefaultProfile;
        
	    ///////////////
		if(!ghVer)
		{
			hr=FindExchVer(ghbstrCurrentProfile);
			if(hr!=S_OK)
			return hr;
		}
        

		switch(gh_CAInfo)
		{ //Start of case
			case 0:
						/////////////////
						if(ghExchVer==EXCH_55) //valid Exchange 5.5 version
						{
							hr=Exchange55();
							if(hr!=S_OK)
								return hr;
						}

						if(ghExchVer==EXCH_2000) //Exchange 2000
						{
							hr=Exchange2000();
							if(hr!=S_OK)
								return hr;
						}
						////////////////////////////////
			break;

			case 1:
						if(ghExchVer==EXCH_55) //valid Exchange 5.5 version
						{
							hr=Exchange55();
							if(hr!=S_OK)
							return hr;
						}
            break;

			case 2:
				        if(ghExchVer==EXCH_2000) //Exchange 2000
						{
							hr=Exchange2000();
							if(hr!=S_OK)
								return hr;
						}
				 
            break;

			case 3:
						if(ghExchVer==EXCH_55) //valid Exchange 5.5 version
						{
							hr=Exchange55();
							if(hr!=S_OK)
							return hr;
						}

						if(ghExchVer==EXCH_2000) //Exchange 2000
						{
							hr=Exchange2000();
							if(hr!=S_OK)
								return hr;
						}
						////////////////////////////////

			break;

		}// End of case
		
	}
	else
	{
	}

Quit:

	
        return hr;
}



BOOL CProfAdmin::PrepareLDAPDN(_bstr_t& i_bstrExchangeDN,
							   _bstr_t* o_ptbstrldapDN)
{

	#ifdef	_VS_LOG_MSG_
			VSGSE_Log(FALSE,L"PrepareLDAPDN:start");
	#endif

    if(ptbstrDNAttrs!= NULL)
	{
		delete[] ptbstrDNAttrs;
		ptbstrDNAttrs=NULL;
	}

	if(ptbstrDNVals != NULL)
	{
		delete[] ptbstrDNVals;
		ptbstrDNVals=NULL;
	}

	nNumOfDNAttrs=0;
	hr=_ParseDNIntoComponents(i_bstrExchangeDN,&nNumOfDNAttrs,&ptbstrDNAttrs,&ptbstrDNVals);
	if(hr==S_OK)
	{
        for(int i=0; i<nNumOfDNAttrs;i++)
		{
	
			*o_ptbstrldapDN+=ptbstrDNAttrs[nNumOfDNAttrs-i-1];
			*o_ptbstrldapDN+=L"=";
			*o_ptbstrldapDN+=L"\"";
			*o_ptbstrldapDN+=ptbstrDNVals[nNumOfDNAttrs-i-1];
			*o_ptbstrldapDN+=L"\"";
			if(i!=nNumOfDNAttrs-1)
				*o_ptbstrldapDN+=L",";
		}

		#ifdef	_VS_LOG_MSG_
			VSGSE_Log(FALSE,L"PrepareLDAPDN:%s",_MultiToWideString(*o_ptbstrldapDN));
			VSGSE_Log(FALSE,L"PrepareLDAPDN:done");

		#endif

			
	}
	else
	{
		#ifdef	_VS_LOG_MSG_
			VSGSE_Log(FALSE,L"PrepareLDAPDN:_ParseDNIntoComponents:Error Code : 0x%08X",hr);
		#endif

		return FALSE;
	}


	return TRUE;
	
}

HRESULT CProfAdmin::GetMailBoxInfo(_bstr_t& i_bstrServerName,_bstr_t&i_bstrMailDN,
								   MailBoxInfo *pMailBoxInfo)
{

	DWORD			err=0;
	int             i=0,Index=0;
	ULONG version = LDAP_VERSION3,count;

	WCHAR           *a=NULL, *dn=NULL;
	WCHAR			buffer_value[8024];  //To get the value
	WCHAR			**vals,*buffer=NULL; 
	
	LDAP			*ldapConnection =NULL;
	LDAPMessage     *results = NULL,*e=NULL;
	BerElement      *ber;

	hr=S_OK;

	#ifdef	_VS_LOG_MSG_
				
		VSGSE_Log(FALSE,L"INFO:GetMailBoxInfo LDAP Server=%s",_MultiToWideString(i_bstrServerName));
		VSGSE_Log(FALSE,L"INFO: GetMailBoxInfo DN: %s",_MultiToWideString(i_bstrMailDN));

	#endif

	do
	{
			ldapConnection = ldap_init(i_bstrServerName, LDAP_PORT );
			if ( ldapConnection == NULL ) {
				err=LdapGetLastError();
				hr= HRESULT_FROM_WIN32(err) ;
				#ifdef	_VS_LOG_MSG_
					buffer=ldap_err2string(err); 
					VSGSE_Log(FALSE,L"ERROR:ldap_init FAILED :Error Code : 0x%08X",
						HRESULT_FROM_WIN32(err));
					VSGSE_Log(FALSE,L"ERROR: ldap_init FAILED : Error Desc: %s", buffer);

				#endif
				break;

			}

			// Set the version to 3.0 (default is 2.0).
			err = ldap_set_option(ldapConnection,LDAP_OPT_VERSION,&version);
			if (err != LDAP_SUCCESS) {
				hr= HRESULT_FROM_WIN32(err);

				#ifdef	_VS_LOG_MSG_
					buffer=ldap_err2string(err); 
					VSGSE_Log(FALSE,L"ERROR:ldap_set_option FAILED :Error Code : 0x%08X",hr);
					VSGSE_Log(FALSE,L"ERROR: ldap_set_option FAILED : Error Desc: %s", buffer);

				#endif

				break;
			}
			
			err=ldap_connect(ldapConnection, NULL);
			if (err != LDAP_SUCCESS) {
				hr = HRESULT_FROM_WIN32(err);

				#ifdef	_VS_LOG_MSG_
					buffer=ldap_err2string(err); 
					VSGSE_Log(FALSE,L"ERROR:ldap_connect FAILED :Error Code : 0x%08X",hr);
					VSGSE_Log(FALSE,L"ERROR: ldap_connect FAILED : Error Desc: %s", buffer);
				#endif

				break;
			}
			
			// Bind with the caller's credentials.
			err = ldap_bind_s( ldapConnection, NULL, NULL,LDAP_AUTH_NEGOTIATE);
			if (err != LDAP_SUCCESS) {
				hr= HRESULT_FROM_WIN32(err);
				#ifdef	_VS_LOG_MSG_
					buffer=ldap_err2string(err); 
					VSGSE_Log(FALSE,L"ERROR:ldap_bind_s FAILED :Error Code : 0x%08X",hr);
					VSGSE_Log(FALSE,L"ERROR: ldap_bind_s FAILED : Error Desc: %s", buffer);

				#endif
				break;
			}
			// search for entries for mailbox  
			err=ldap_search_s(ldapConnection,i_bstrMailDN, LDAP_SCOPE_SUBTREE     ,
					  L"(Objectclass=*)", attrs, 0, &results );
			if(err!=LDAP_SUCCESS){
					
		  			hr= HRESULT_FROM_WIN32(err);

					#ifdef	_VS_LOG_MSG_
						buffer=ldap_err2string(err); 
						VSGSE_Log(FALSE,L"ERROR:ldap_search_s FAILED :Error Code : 0x%08X",hr);
						VSGSE_Log(FALSE,L"ERROR: ldap_search_s FAILED : Error Desc: %s", buffer);
					#endif
					break;
			}

			gLDAPAccess=TRUE;  //////Get All necessary attributes

			//for each entry print out name + all attrs and values 
			  for ( e = ldap_first_entry( ldapConnection, results ); e != NULL;
				e = ldap_next_entry( ldapConnection, e ) ) {
				  if ( (dn = ldap_get_dn( ldapConnection, e )) != NULL ) {
						ldap_memfree( dn );
				  }
				  for ( a = ldap_first_attribute( ldapConnection, e, &ber );
				   a != NULL; a = ldap_next_attribute( ldapConnection, e, ber ) ) {

					 Index=IsAttributeInclude(a);
					 if(Index!=-1)
					 {
							 ///////
							 if ((vals = ldap_get_values( ldapConnection, e, a)) != NULL ) {
								 count=ldap_count_values(vals);			
								for ( i = 0; vals[i] != NULL; i++ ) {
									swprintf(buffer_value, L"%s",  vals[i] );
								}
								ldap_value_free( vals );
								///////////
								switch(Index)
								{
								case 0:
									 pMailBoxInfo->bstrcn=buffer_value;
								break;

								case 1:
									pMailBoxInfo->bstrdistinguishedName=buffer_value;
									pMailBoxInfo->bstrUserDN=buffer_value;

								break;

								case 2:
									pMailBoxInfo->bstrHome_MTA=buffer_value;
								break;
								case 3:
									
									pMailBoxInfo->bstrrfc822Mailbox=buffer_value;
								break;
								case 4:
									
									pMailBoxInfo->bstruid=buffer_value;
								break;
								// Start Add : Infosys : CR21346
								// Populate the user first name and the last name values.
								case 5:
									pMailBoxInfo->bstrFirstName=buffer_value;
								break;
								case 6:
									pMailBoxInfo->bstrLastName=buffer_value;
								break;
								// End Add : Infosys : CR21346


								}
								//////////
							 }
							 /////////
					 }

					 ldap_memfree( a );
				  }
				
			      //if ( ber != NULL ) 
			      //   ber_free( ber, 0 );
			      
				
			   }
				
			   if(pMailBoxInfo->bstrdistinguishedName.length()==0)
			   {
					pMailBoxInfo->bstrdistinguishedName=i_bstrMailDN;
					pMailBoxInfo->bstrUserDN=i_bstrMailDN;
			
			   }
		
       }
	   while(0);

	   if(results!=NULL)
		   	   ldap_msgfree( results );
	   if(ldapConnection!=NULL)
				ldap_unbind( ldapConnection );

	   return hr;
}

int CProfAdmin::IsAttributeInclude(WCHAR *a)
{
	int nSize=0;

	// Start Change : Infosys : CR21346
	if(ghExchVer==EXCH_55)   //Valid Exchage 5.5
	{
		// Modify the size parameter to include the two additional properties for 
		// first name and last name.
		// nSize=5;
		nSize = EXCH55_NO_OF_ATTR ;
	}

	if(ghExchVer==EXCH_2000) //Exchnage 2000
	{
		// Modify the size parameter to include the two additional properties for 
		// first name and last name.
		// nSize=6;
		nSize = EXCH2K_NO_OF_ATTR ;
	}
	// End Change : Infosys : CR21346

	for (int i=0;i<nSize;i++)
	{
		if(ghExchVer==EXCH_55)
		{
			if(!_wcsicmp(attrs[i],a))
				return i;
		}

		if(ghExchVer==EXCH_2000)
		{
			if(!_wcsicmp(exch2k_attrs[i],a))
				return i;
		}

	}
	return -1;
}

HRESULT CProfAdmin::GetFullName(_bstr_t* o_pbstrName)
{
	if(!gLDAPAccess)
	{
		hr=GetAttributes();
		if(hr!=0)
			return hr;
	}

	if(gMailBoxInfo.bstrcn.length()>0)
	{
		*o_pbstrName=(wchar_t*)gMailBoxInfo.bstrcn;
	}
	return hr;
}

HRESULT CProfAdmin::GetRFC822MailBox(_bstr_t*o_bstrRFC822Name)
{
	if(!gLDAPAccess)
	{
		hr=GetAttributes();
		if(hr!=0)
			return hr;
	}

	if(gMailBoxInfo.bstrrfc822Mailbox.length()>0)
	{
		*o_bstrRFC822Name=(wchar_t*)gMailBoxInfo.bstrrfc822Mailbox;
	}
	return hr;
}

HRESULT CProfAdmin::GetHomeMTA(_bstr_t*o_bstrHomeMTA)
{
	if(!gLDAPAccess)
	{
    		hr=GetAttributes();
			if(hr!=0)
				return hr;
	}

	if(gMailBoxInfo.bstrHome_MTA.length()>0)
	{
		*o_bstrHomeMTA=(wchar_t*)gMailBoxInfo.bstrHome_MTA;
	}



	return hr;

}

HRESULT CProfAdmin::GetDN(_bstr_t* o_bstrMailDN)
{
	if(!gLDAPAccess)
	{
    		hr=GetAttributes();
			if(hr!=0)
				return hr;
	}

	if(gMailBoxInfo.bstrdistinguishedName.length()>0)
	{
		*o_bstrMailDN=(wchar_t*)gMailBoxInfo.bstrdistinguishedName;
	}
	return hr;

}

HRESULT CProfAdmin::GetUserDN(_bstr_t* o_bstrUserDN)
{
	if(!gLDAPAccess)
	{
    		hr=GetAttributes();
			if(hr!=0)
				return hr;
	}

	if(gMailBoxInfo.bstrUserDN.length()>0)
	{
		*o_bstrUserDN=(wchar_t*)gMailBoxInfo.bstrUserDN;
	}
	return hr;

}



HRESULT CProfAdmin::GetAlias(_bstr_t*o_bstrAlias)
{
	if(!gLDAPAccess)
	{
    		hr=GetAttributes();
			if(hr!=0)
				return hr;
	}

	if(gMailBoxInfo.bstruid.length()>0)
	{
		*o_bstrAlias=(wchar_t*)gMailBoxInfo.bstruid;
	}

    return hr;

}

HRESULT CProfAdmin::GetUserPrincipalName(_bstr_t* o_bstrUPN)
{
	if(!gLDAPAccess)
	{
		hr=GetAttributes();
		if(hr!=0)
			return hr;
	}

	if(gMailBoxInfo.bstrupn.length()>0)
	{
		*o_bstrUPN=(wchar_t*)gMailBoxInfo.bstrupn;
	}
	
	return hr;
}

HRESULT CProfAdmin::PromptProfileSelection()
{
	   HRESULT			hRes = S_OK;
	   ULONG			ulFlags = 0L;
	   
       LPMAPISESSION	pSession = NULL;
	   LPMAPITABLE      lpStatusTable = NULL;

	   SRestriction     sres;
	   SPropValue       spvResType;
	   LPSRowSet        pRows = NULL;
	   LPTSTR           lpszProfileName = NULL;


	   _bstr_t         bstrProfileName="";

	  // hr = MAPIInitialize(NULL);

	   SizedSPropTagArray(2, Columns) =
	   {
		  2, PR_DISPLAY_NAME, PR_RESOURCE_TYPE
	   };


       //if ( FAILED ( hRes = MAPIInitialize ( NULL ) ) )
       //   goto Quit;

	    #ifdef	_VS_LOG_MSG_
			VSGSE_Log(FALSE,L"PromptProfileSelection:start");
		#endif


       ulFlags = MAPI_EXTENDED | MAPI_LOGON_UI |
                 MAPI_EXPLICIT_PROFILE |MAPI_NEW_SESSION  ;

       if ( FAILED ( hr = MAPILogonEx (0l,NULL,NULL,
                                          ulFlags,&pSession ) ) )
	   {
		   #ifdef	_VS_LOG_MSG_
			VSGSE_Log(FALSE,L"PromptProfileSelection:MAPILogonEx:Error Code : 0x%08X",hr);
			#endif
          goto Quit;
	   }

	   hr = pSession->GetStatusTable(NULL, &lpStatusTable);
	   hr = lpStatusTable->SetColumns((LPSPropTagArray)&Columns, NULL);

	   spvResType.ulPropTag = PR_RESOURCE_TYPE;
	   spvResType.Value.ul = MAPI_SUBSYSTEM;

	   sres.rt = RES_PROPERTY;
	   sres.res.resProperty.relop = RELOP_EQ;
	   sres.res.resProperty.ulPropTag = PR_RESOURCE_TYPE;
	   sres.res.resProperty.lpProp = &spvResType;

	   hr = lpStatusTable->Restrict(&sres, TBL_ASYNC);
	   if(FAILED(hr))
	   {
		   #ifdef	_VS_LOG_MSG_
			VSGSE_Log(FALSE,L"PromptProfileSelection:lpStatusTable->Restrict:Error Code : 0x%08X",hr);
			#endif
		   goto Quit;
	   }

	   hr = lpStatusTable->FindRow(&sres, BOOKMARK_BEGINNING, 0);
	   if(FAILED(hr))
	   {
		   #ifdef	_VS_LOG_MSG_
			VSGSE_Log(FALSE,L"PromptProfileSelection:lpStatusTable->FindRow:Error Code : 0x%08X",hr);
		   #endif
		   goto Quit;
	   }

	   // We have a match.
	   hr = lpStatusTable->QueryRows(1,0,&pRows);
	   if (SUCCEEDED(hr))
	   {
		  bstrProfileName = pRows->aRow[0].lpProps[0].Value.lpszA;

		  hr=IsExchProfile(bstrProfileName);
	      if(hr==1)   ////Yes Exch profile
		  {
				hr=GetProfileInfo(bstrProfileName,&m_pInfo);
				if(FAILED(hr))
		    		goto Quit;
				
				ghbstrCurrentProfile=bstrProfileName;

				///////////////
				hr=ExchVerByMapi(pSession);
				if(hr!=S_OK)
				return hr;
				/////////////////
				switch(gh_CAInfo)
				{ //Start of case
					case 0:
								/////////////////
								if(ghExchVer==EXCH_55) //valid Exchange 5.5 version
								{
									hr=Exchange55();
									if(hr!=S_OK)
									return hr;
								}

								if(ghExchVer==EXCH_2000) //Exchange 2000
								{
									hr=Exchange2000();
									if(hr!=S_OK)
										return hr;
								}
								////////////////////////////////
					break;

					case 1:
								if(ghExchVer==EXCH_55) //valid Exchange 5.5 version
								{
									hr=Exchange55();
									if(hr!=S_OK)
									return hr;
								}
					break;

					case 2:
								if(ghExchVer==EXCH_2000) //Exchange 2000
								{
									hr=Exchange55();
									if(hr!=S_OK)
										return hr;
								}
						 
					break;

					case 3:
								if(ghExchVer==EXCH_55) //valid Exchange 5.5 version
								{
									hr=Exchange55();
									if(hr!=S_OK)
									return hr;
								}
								if(ghExchVer==EXCH_2000) //Exchange 2000
								{
									hr=Exchange2000();
									if(hr!=S_OK)
										return hr;
								}


					break;

			}// End of case
		
			////////////////////////
			
		  }
	   }
   

    Quit:
	   if(pSession!=NULL)
			pSession->Logoff(0,0,0);

	   //MAPIUninitialize();
	   return hr;

    // Add code to release and free all memory allocated by MAPI.
      

}


HRESULT CProfAdmin::CertUpdate()
{
	DWORD			err=0;
	WCHAR			*CertData[2];
	WCHAR			*buffer=NULL;

	LDAP			*ldapConnection = NULL;
	LDAPMod			mod;
	LDAPMod			*mods[2];


	//  Connect to the default LDAP server.
	ldapConnection = ldap_open(ghbstrHomeServer , LDAP_PORT );
	if ( ldapConnection == NULL ) {
		err=GetLastError();

		#ifdef	_VS_LOG_MSG_
				buffer=ldap_err2string(err); 
				VSGSE_Log(FALSE,L"ERROR:ldap_open FAILED :Error Code : 0x%08X",HRESULT_FROM_WIN32(err));
				VSGSE_Log(FALSE,L"ERROR: ldap_open FAILED : Error Desc: %s", buffer);
		#endif

		return  HRESULT_FROM_WIN32(err);
	}
	 
	// Bind with the caller's credentials.
	err = ldap_bind_s( ldapConnection, NULL, NULL, LDAP_AUTH_NEGOTIATE );
	if (err != LDAP_SUCCESS) {
		#ifdef	_VS_LOG_MSG_
				buffer=ldap_err2string(err); 
				VSGSE_Log(FALSE,L"ERROR:ldap_bind_s FAILED :Error Code : 0x%08X",HRESULT_FROM_WIN32(err));
				VSGSE_Log(FALSE,L"ERROR: ldap_bind_s FAILED : Error Desc: %s", buffer);
		#endif

		return HRESULT_FROM_WIN32(err);
	}
	
	////Fill the Mod structure with proper data
	if(UserOrSMIME)
		CertData[0]=ghbstrUserCertificate;
	else
		CertData[0]=ghbstrSMIMECertificate;

	CertData[1]=NULL;
	/* Start Change : Infosys */
	/* Changed to fix the problem discovered while GSe testing with UAS */
	/* When user enrolls for GSE certificate SMIME certificate is overwritting */
	/* UAS certificate in active directory */
	/* mod.mod_op=LDAP_MOD_REPLACE; */
	mod.mod_op=LDAP_MOD_ADD; 
	/* End Change : Infosys */

	if(UserOrSMIME)
		mod.mod_type=L"userCertificate";   //user-cert
	else
		mod.mod_type=L"userSMIMECertificate";


	mod.mod_values=CertData;
	mods[0]=&mod;
	mods[1]=NULL;

	err=ldap_modify_s(ldapConnection,ghbstrMailDN,mods);
	if(err!=LDAP_SUCCESS)
	{
		buffer=ldap_err2string(err);

		#ifdef	_VS_LOG_MSG_
				buffer=ldap_err2string(err); 
				VSGSE_Log(FALSE,L"ERROR:ldap_modify_s FAILED :Error Code : 0x%08X",HRESULT_FROM_WIN32(err));
				VSGSE_Log(FALSE,L"ERROR: ldap_modify_s FAILED : Error Desc: %s", buffer);
		#endif

		return HRESULT_FROM_WIN32(err);
	}
	
	ldap_unbind(ldapConnection);

	ghbstrUserCertificate="";
    ghbstrSMIMECertificate="";
	return HRESULT_FROM_WIN32(err);
	
}

HRESULT CProfAdmin::GetHomeServer(_bstr_t* o_pbstrHomeServer)
{
	if(!gLDAPAccess)
	{
    		hr=GetAttributes();
			if(hr!=0)
				return hr;
	}

	if(m_pInfo.bstrHomeServer.length()>0)
	{
		*o_pbstrHomeServer=(wchar_t*)m_pInfo.bstrHomeServer;
	}
	
	return hr;

}

HRESULT CProfAdmin::GetExchServer(_bstr_t* o_pbstrExchServer)
{
	if(!gLDAPAccess)
	{
    		hr=GetAttributes();
			if(hr!=0)
				return hr;
	}

	if(m_pInfo.bstrExchServer.length()>0)
	{
		*o_pbstrExchServer=(wchar_t*)m_pInfo.bstrExchServer;
	}
	
	return hr;

}


HRESULT CProfAdmin::CheckUpdateRight(_bstr_t& i_bstrServerName,_bstr_t&i_bstrMailDN)
{
	
	DWORD			err=0;
	int             i=0;
	ULONG			version = LDAP_VERSION3,numValue=0;

	PSID			pMySID;
	char			*szmbMySID = NULL;
	WCHAR			*wszmbMySID=NULL;

	unsigned char	*pbMyUserCert = NULL;
	unsigned int	cbMyUserCert = 0;


	WCHAR           *a=NULL, *dn=NULL,*buffer=NULL;
	WCHAR			*attrs[2];
	
	LDAP			*ldapConnection =NULL;
	LDAPMessage     *results = NULL,*e=NULL;
	BerElement		*ber;
	
	attrs[0]=L"userCertificate";
	attrs[1]=NULL;

	hr=S_OK;

	#ifdef	_VS_LOG_MSG_
		VSGSE_Log(FALSE,L"CheckUpdateRight start :%s",
					_MultiToWideString((char*)i_bstrServerName));
	#endif

	do
	{

			ldapConnection = ldap_init(i_bstrServerName, LDAP_PORT );
			if ( ldapConnection == NULL ) {
				err=LdapGetLastError ();
				hr=HRESULT_FROM_WIN32(err) ;

				#ifdef	_VS_LOG_MSG_
					buffer=ldap_err2string(err); 
					VSGSE_Log(FALSE,L"ERROR:ldap_init FAILED :Error Code : 0x%08X",hr);
					VSGSE_Log(FALSE,L"ERROR: ldap_init FAILED : Error Desc: %s", buffer);

				#endif

				break;
			}

			// Set the version to 3.0 (default is 2.0).
			err = ldap_set_option(ldapConnection,LDAP_OPT_VERSION,&version);
			if (err != LDAP_SUCCESS) {
				hr=HRESULT_FROM_WIN32(err);
				#ifdef	_VS_LOG_MSG_
					buffer=ldap_err2string(err); 
					VSGSE_Log(FALSE,L"ERROR:ldap_set_option FAILED :Error Code : 0x%08X",hr);
					VSGSE_Log(FALSE,L"ERROR: ldap_set_option FAILED : Error Desc: %s", buffer);

				#endif
				break;
			}
			

			err=ldap_connect(ldapConnection, NULL);
			if (err != LDAP_SUCCESS) {
				hr= HRESULT_FROM_WIN32(err);
				#ifdef	_VS_LOG_MSG_
					buffer=ldap_err2string(err); 
					VSGSE_Log(FALSE,L"ERROR:ldap_connect FAILED :Error Code : 0x%08X",hr);
					VSGSE_Log(FALSE,L"ERROR: ldap_connect FAILED : Error Desc: %s", buffer);

				#endif
				break;
			}
			
			// Bind with the caller's credentials.
			err = ldap_bind_s( ldapConnection, NULL, NULL, LDAP_AUTH_NEGOTIATE);
			if (err != LDAP_SUCCESS) {
				buffer=ldap_err2string(err); 
				hr= HRESULT_FROM_WIN32(err);

				#ifdef	_VS_LOG_MSG_
					buffer=ldap_err2string(err); 
					VSGSE_Log(FALSE,L"ERROR:ldap_bind_s FAILED :Error Code : 0x%08X",hr);
					VSGSE_Log(FALSE,L"ERROR: ldap_bind_s FAILED : Error Desc: %s", buffer);

				#endif

				break;
			}

			//////Get the SID Information
			if ((pMySID = GetMySid()) == NULL)
			{
				  hr= E_UNABLE_TO_GET_SID;
				  #ifdef	_VS_LOG_MSG_
					
					VSGSE_Log(FALSE,L"ERROR:GetMySid FAILED :Error Code : 0x%08X",hr);
					VSGSE_Log(FALSE,L"ERROR: GetMySID FAILED");

				  #endif
				  break;
			}
    
			szmbMySID = EncodeSid(pMySID);
			wszmbMySID=_MultiToWideString(szmbMySID);
			WCHAR  wszAssocNTValue[1024];
			wcscpy(wszAssocNTValue, L"(Assoc-NT-Account=") ;
			wcscat(wszAssocNTValue, (WCHAR*)wszmbMySID);
			wcscat(wszAssocNTValue, L")");

			#ifdef	_VS_LOG_MSG_
			VSGSE_Log(FALSE,L"CheckUpdateRight:SID :%s",wszAssocNTValue);
			#endif


			err=ldap_compare_s(ldapConnection,i_bstrMailDN,L"Assoc-NT-Account",wszmbMySID);
			if(err!=LDAP_COMPARE_TRUE)
			{
				hr= E_SID_COMP_FAILED;
				#ifdef	_VS_LOG_MSG_
					buffer=ldap_err2string(err); 
					VSGSE_Log(FALSE,L"ERROR:ldap_compare_s FAILED :Error Code : 0x%08X",hr);
					VSGSE_Log(FALSE,L"ERROR: ldap_compare_s FAILED : Error Desc: %s", buffer);

				#endif

				break;
			}

			if(bRenewCert==1)
			{
				err=ldap_search_s(ldapConnection,i_bstrMailDN, LDAP_SCOPE_SUBTREE     ,
					  wszAssocNTValue,attrs,  0, &results );
				if(err!=LDAP_SUCCESS)
				{
						
						hr=  HRESULT_FROM_WIN32(err);

						#ifdef	_VS_LOG_MSG_
							buffer=ldap_err2string(err); 
							VSGSE_Log(FALSE,L"ERROR:ldap_init FAILED :Error Code : 0x%08X",hr);
							VSGSE_Log(FALSE,L"ERROR: ldap_init FAILED : Error Desc: %s", buffer);

						#endif
						break;
				}
   
				 for ( e = ldap_first_entry( ldapConnection, results ); e != NULL;
				  e = ldap_next_entry( ldapConnection, e ) ) 
					{
					  if ( (dn = ldap_get_dn( ldapConnection, e )) != NULL ) {
							  ldap_memfree( dn );
						}

						 for ( a = ldap_first_attribute( ldapConnection, e, &ber );
							a != NULL; a = ldap_next_attribute( ldapConnection, e, ber ))
						{
					
							PLDAP_BERVAL *pBer = ldap_get_values_len(ldapConnection, e, a);
							if(*pBer == NULL)
							{
								hr= E_FAILED_LDAP_GET_LEN;				
								break;
							}

							numValue=ldap_count_values_len(pBer);

            				pbMyUserCert = (unsigned char *)malloc(pBer[0]->bv_len + 1);
							memset(pbMyUserCert, 0 , pBer[0]->bv_len + 1);
							memcpy(pbMyUserCert, pBer[0]->bv_val, pBer[0]->bv_len);
							cbMyUserCert= pBer[0]->bv_len;

							ldap_memfree(a);
							ldap_value_free_len(pBer);

						}

					CHECK_HRESULT

					}
				
				CHECK_HRESULT

			
				hr=GetCertificateProperties(pbMyUserCert,cbMyUserCert);
				if(hr!=S_OK)
					break;
				
			}

	}
	while(0);

   
    if(szmbMySID!=NULL)
			free(szmbMySID);

	if(wszmbMySID!=NULL)
			SysFreeString(wszmbMySID);

	if(pbMyUserCert!=NULL)
			free(pbMyUserCert);

	if(results!=NULL)
		    ldap_msgfree( results );

	if(ldapConnection!=NULL)
		   ldap_unbind( ldapConnection );

    return hr;

}

HRESULT CProfAdmin::AddEncrypt_SignButton()
{
	

	BSTR                      szNs,szBarName,szStdBar;
	BSTR                      szProfileName;

//	_Application              *olApp;
//	Inspector                 *olIns;
//	NameSpace                 *olNs;
//	_MailItem                 *olMail;

//	IDispatch                 *pdispItem,*pdispCmdBar;
//	CLSID					   clsOlApp;

	CommandBars               *Ins_Bars;
	CommandBar                *pCmdBar,*pStdBar;
	CommandBarControl         *pBarControl,*pSignControl,*pEncryptControl;
    CommandBarControls		  *pCmdControls;	

	char*		pCharDot		=	NULL;
	double		dVersion		=	0;
	CHAR		szVersion [256];

	BOOL                      bOutlook2000=FALSE;

	CoInitialize(NULL);

	olIns=NULL;
	olNs=NULL;
	olMail=NULL;
	pdispCmdBar=NULL;

	VARIANT      varOptional;
	VariantInit(&varOptional); 
	varOptional.vt=VT_ERROR;
	varOptional.scode=DISP_E_PARAMNOTFOUND;


	hr=CLSIDFromProgID(L"OutLook.Application", &clsOlApp); 
	if(hr!=S_OK)
		return hr;

	
    hr=CoCreateInstance(clsOlApp, NULL, CLSCTX_LOCAL_SERVER,
										IID__Application, (void **)&olApp); 

	if(hr!=S_OK)
		return hr;


	/////////////////////////////
	BSTR                      bVer;
	char                      *pVer;
	hr=olApp->get_Version(&bVer);
	if(hr!=S_OK)
		goto Quit;

	pVer=_WideToMultiString(bVer);
    if(pVer==NULL)
		goto Quit;

	::strcpy(szVersion, pVer);

	//	find the first dot in the version string
	pCharDot =	::strchr(szVersion, '.');


	if ( NULL == pCharDot )
	{
		hr =	E_FAIL;
		goto Quit;
	}

		//	truncate the string at the dot. basically get only the major version as a string
	*pCharDot = '\0';

		//	convert it to number
	dVersion = ::atoi( (const char*) szVersion );

		//	compare if the number is >= OUTLOOK_2000_VERSION
	if ( dVersion >= OUTLOOK_2000_VERSION )
	{
		bOutlook2000 = TRUE;
	}
	else
	{
		bOutlook2000 = FALSE;
	}

	//////////////////////////////////


	szNs=_MultiToWideString("MAPI");
	hr=olApp->GetNamespace(szNs,&olNs);
	if(hr!=S_OK)
		goto Quit;

	VARIANT     varProfileName;
	VariantInit(&varProfileName);
    szProfileName=_MultiToWideString(bstrCurrentProfile);
	varProfileName.vt=VT_BSTR;
    varProfileName.bstrVal=szProfileName;
    
  
    
	VARIANT     varTrue;
	VariantInit(&varTrue);
   	varTrue.vt=VT_BOOL;
    varTrue.boolVal=1;

	VARIANT     varFalse;
	VariantInit(&varFalse);
   	varFalse.vt=VT_BOOL;
    varFalse.boolVal=0;


	hr=olNs->Logon(varProfileName,varOptional,varFalse,varTrue);
	if(hr!=S_OK)
		goto Quit;

	
	hr=olApp->CreateItem(olMailItem,&pdispItem);
	if(hr!=S_OK)
		goto Quit;

	hr=pdispItem->QueryInterface(IID__MailItem,(void **)&olMail);
    if(hr!=S_OK)
		goto Quit;

	VARIANT varDisplay;
	varDisplay.vt = VT_I2;
	varDisplay.iVal = 0;

	if(!bOutlook2000)
	{
			hr=olMail->Display(varDisplay);
			if(hr!=S_OK)
			goto Quit;
	}
	


	hr=olMail->get_GetInspector(&olIns);
	if(hr!=S_OK)
		goto Quit;

	hr=olIns->get_CommandBars(&pdispCmdBar);
    if(hr!=S_OK)
		goto Quit;

	hr=pdispCmdBar->QueryInterface(IID_CommandBars,(void **)&Ins_Bars);
	if(hr!=S_OK)
		goto Quit;

	int   count;
	hr=Ins_Bars->get_Count(&count);
    if(hr!=S_OK)
		goto Quit;
	//Add more processing here

	VARIANT varPos;
	VariantInit(&varPos);
	varPos.vt = VT_I2;
	varPos.iVal =msoBarTop;

	VARIANT varType;
	VariantInit(&varType);
	varType.vt = VT_I2;
	varType.iVal = msoControlButton;

	VARIANT varSignID;
	VariantInit(&varSignID);
	varSignID.vt = VT_I2;
	varSignID.iVal = 718;

	VARIANT varEncryptID;
	VariantInit(&varEncryptID);
	varEncryptID.vt = VT_I2;
	varEncryptID.iVal = 719;

	hr=Ins_Bars->FindControl(varType,varSignID,varOptional,varFalse,&pSignControl);
	if(pSignControl!=NULL)
	{
		hr=pSignControl->get_Parent(&pCmdBar);
		if(hr!=S_OK)
			goto Quit;
		hr=pCmdBar->put_Visible(TRUE);
	}

	hr=Ins_Bars->FindControl(varType,varEncryptID,varOptional,varFalse,&pEncryptControl);
	if(pEncryptControl!=NULL)
	{
		hr=pEncryptControl->get_Parent(&pCmdBar);
		if(hr!=S_OK)
			goto Quit;
		hr=pCmdBar->put_Visible(TRUE);
	}


	if(pSignControl==NULL || pEncryptControl==NULL)
	{
		VARIANT     varBarName;
		VariantInit(&varBarName);
		szBarName=_MultiToWideString(ID_BARNAME);
		varBarName.vt=VT_BSTR;
		varBarName.bstrVal=szBarName;

		VARIANT     varStdBar;
		VariantInit(&varStdBar);
		szStdBar=_MultiToWideString("Standard");
		varStdBar.vt=VT_BSTR;
		varStdBar.bstrVal=szStdBar;

		

        if(!bOutlook2000)
		{
			hr=Ins_Bars->Add(varBarName,varPos,varOptional,varOptional,&pCmdBar);
			if(hr!=S_OK)
					goto Quit;
			hr=Ins_Bars->get_Item(varStdBar,&pStdBar);
			if(hr!=S_OK)
					goto Quit;
			int  row_index;
			pStdBar->get_RowIndex(&row_index);
			pCmdBar->put_RowIndex(row_index);
			
			int   width;
			pStdBar->get_Width(&width);
			pCmdBar->put_Left(width);
			pCmdBar->put_Visible(TRUE);
				
			hr=pCmdBar->get_Controls(&pCmdControls);
			if(hr!=S_OK)
				goto Quit;
		}
		else
		{
			hr=Ins_Bars->get_Item(varStdBar,&pStdBar);
			if(hr!=S_OK)
					goto Quit;

			hr=pStdBar->get_Controls(&pCmdControls);
			if(hr!=S_OK)
				goto Quit;

		}


		if(pSignControl==NULL)
		{
			hr=pCmdControls->Add(varType,varSignID,varOptional,varOptional,varFalse,&pBarControl);
			if(hr!=S_OK)
			{
				//	if its outlook 2002 or later then if word is the email editor
				//	then adding buttons fail. so return appropriate error
				if ( dVersion > OUTLOOK_2000_VERSION )
				{
					hr = E_VS_OUTLOOK2002_NO_BUTTONS;
				}
				goto Quit;
			}
		}

		if(pEncryptControl==NULL)
		{
			hr=pCmdControls->Add(varType,varEncryptID,varOptional,varOptional,varFalse,&pBarControl);
			if(hr!=S_OK)
				goto Quit;
		}

	}


Quit:
	//CoUninitialize();

	if(pVer!=NULL)
		 free(pVer);


	if(olIns!=NULL)
		olIns->Close(olSave);
	if(olNs!=NULL)
		olNs->Logoff();

	//if(olApp!=NULL)
	//	  olApp->Quit();

	if(olMail!=NULL)
		olMail->Release();

//	if(pdispItem!=NULL)
//		pdispItem->Release();


	if(olIns!=NULL)
		olIns->Release();
	 
	if(olNs!=NULL)
			olNs->Release();

	if(olApp!=NULL)
		olApp->Release();

	return hr;


}

HRESULT CProfAdmin::GetVers(char *szFileName, char *szVer)
{
	   DWORD dwArg;
	   DWORD err; 
       DWORD dwInfoSize = GetFileVersionInfoSize(szFileName, &dwArg);

       if(0 == dwInfoSize)
       {                 
           err= GetLastError();
		   return HRESULT_FROM_WIN32(err);
       }

      
	   BYTE* lpBuff= (BYTE *)malloc(dwInfoSize);

       if(!lpBuff)
       {
            err= GetLastError();
		   return HRESULT_FROM_WIN32(err);
       }

       if(0 == GetFileVersionInfo(szFileName, 0, dwInfoSize, lpBuff))
       {
          err= GetLastError();
		  return HRESULT_FROM_WIN32(err);
       }

       VS_FIXEDFILEINFO *vInfo;

       UINT uInfoSize;

       if(0 == VerQueryValue(lpBuff, TEXT("\\"),
               (LPVOID*)&vInfo,
               &uInfoSize))
       {
           
           free(lpBuff) ;
		   err= GetLastError();
		   return HRESULT_FROM_WIN32(err);
           
       }

       if(0 == uInfoSize)
       {
           
           free(lpBuff) ;
           err= GetLastError();
		   return HRESULT_FROM_WIN32(err);
       }

	   char buf[10];

	   lstrcpy(szVer,"Version:");

	   _itoa(HIWORD(vInfo->dwFileVersionMS),buf,10);
	   lstrcat(szVer, buf);

	   _itoa(LOWORD(vInfo->dwFileVersionMS),buf,10);
	   lstrcat(szVer, buf);

	   _itoa(HIWORD(vInfo->dwFileVersionLS),buf,10);
	   lstrcat(szVer, buf);

	   _itoa(LOWORD(vInfo->dwFileVersionLS),buf,10);
	   lstrcat(szVer, buf);
    
	   if (lpBuff)
			free(lpBuff) ;

	   return S_OK;

}

HRESULT CProfAdmin::UpdateClientExt()
{
	char    szDownLoadName[MAXLEN],szWinDir[MAXLEN];
    char    szInstallVer[MAXLEN],szDownLoadVer[MAXLEN];
	char    szInstallPath[MAXLEN];
	char    *lptoken=NULL;
	char	*envPtr;


	BOOL    bRet;
	DWORD   err,dwDisposition = 0;

	CHAR szKey[MAXLEN];
	HKEY hRegKey = NULL;
  

	hr=S_OK;


	DWORD   m_err=0;

	envPtr=getenv("ProgramFiles");
	strcpy(szInstallPath,envPtr);
	bRet=CreateDirectory(szInstallPath,NULL);
	m_err=GetLastError();

	lstrcat(szInstallPath,"\\VeriSign");
	bRet=CreateDirectory(szInstallPath,NULL);

	m_err=GetLastError();

	//lstrcat(szInstallPath,"\\Onsite");
	//bRet=CreateDirectory(szInstallPath,NULL);
	//m_err=GetLastError();

	
	lstrcat(szInstallPath,"\\GSE");
	bRet=CreateDirectory(szInstallPath,NULL);

	m_err=GetLastError();


	/*---------------Store the install path -----------------------*/

	_tcscpy(szKey, _T("SOFTWARE\\VeriSign\\GSE"));

	err = RegCreateKeyEx(
					HKEY_CURRENT_USER,
					szKey,
					0,
					NULL,
					REG_OPTION_NON_VOLATILE,
					KEY_ALL_ACCESS,
					NULL,
					&hRegKey,
					&dwDisposition) ;
	 
	if ( dwDisposition == NULL || err != ERROR_SUCCESS )
	{
		return err ;
	}


	err=RegSetValueEx(hRegKey, _T("ExtInstallPath"), 0, REG_SZ, 
												(CONST BYTE *)&szInstallPath, strlen(szInstallPath));
	if(err!=ERROR_SUCCESS)
	{
		return err;
	}
	RegCloseKey(hRegKey);

	/*------------------------------------------------------------*/
	
	lstrcat(szInstallPath,"\\");
	lstrcat(szInstallPath,ID_EXTNAME);

	memset(szInstallVer,0,MAXLEN);

	hr=GetVers(szInstallPath,szInstallVer);
	
    GetWindowsDirectory(szWinDir,MAXLEN);
	
	lstrcpy(szDownLoadName,szWinDir);
	lstrcat(szDownLoadName,"\\Downloaded Program Files");
	lstrcat(szDownLoadName,"\\");
	lstrcat(szDownLoadName,ID_EXTNAME);

	memset(szDownLoadVer,0,MAXLEN);
	hr=GetVers(szDownLoadName,szDownLoadVer);

	if(strlen(szDownLoadVer)>0)
	{
		if((lstrcmp(szInstallVer,szDownLoadVer)!=0))
		{
			bRet=CopyFile(szDownLoadName,szInstallPath,FALSE);
			if(!bRet)
			{
			   err= GetLastError();
			   return HRESULT_FROM_WIN32(err);
			}

		}
	}
		
	return S_OK;

}

void CProfAdmin::Base64Encode(PCHAR pInput, DWORD dwInputSize, PCHAR pOutput, DWORD *dwOutputSize)
{
	
	char _encode[64] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
					'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
				    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
				    'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/'} ;

	if ( pOutput == NULL )
	{
		*dwOutputSize = !(dwInputSize % 3) ? (dwInputSize/3)*4 : ((dwInputSize/3)*4) + 4 ;
		*dwOutputSize += (*dwOutputSize / 76)*2 ; // Includes '\n' '\r' after 76 chars in encoded output.
	}
	else
	{
		DWORD		remainingSize, seventySixCount ;
		PCHAR		inputPtr, outputPtr ;

		remainingSize = dwInputSize ;
		inputPtr = pInput ;
		outputPtr = pOutput ;
		*dwOutputSize = 0 ;
		seventySixCount = 0 ;

		while((int)remainingSize > 0)
		{
			if (remainingSize == 1)
			{
				DWORD tmp ;
				tmp = 0x000000FF & inputPtr[0] ;
				tmp = tmp << 16 ;

				outputPtr[0] = _encode[((tmp & 0x00FC0000) >> 18)] ;
				outputPtr[1] = _encode[((tmp & 0x0003F000) >> 12)] ;
				outputPtr[2] = '=' ;
				outputPtr[3] = '=' ;
			}

			else if(remainingSize == 2)
			{
				DWORD tmp ;
				tmp = 0x000000FF & inputPtr[0] ;
				tmp = tmp << 8 ;
				tmp |= 0x000000FF & inputPtr[1] ;
				tmp = tmp << 8 ;

				outputPtr[0] = _encode[((tmp & 0x00FC0000) >> 18)] ;
				outputPtr[1] = _encode[((tmp & 0x0003F000) >> 12)] ;
				outputPtr[2] = _encode[((tmp & 0x00000FC0) >> 6)] ;
				outputPtr[3] = '=' ;

			}
			else
			{
				DWORD tmp ;
				tmp = 0x000000FF & inputPtr[0] ;
				tmp = tmp << 8 ;

				tmp |= 0x000000FF & inputPtr[1] ;
				tmp = tmp << 8 ;
				tmp |= 0x000000FF & inputPtr[2] ;


				outputPtr[0] = _encode[((tmp & 0x00FC0000) >> 18)] ;
				outputPtr[1] = _encode[((tmp & 0x0003F000) >> 12)] ;
				outputPtr[2] = _encode[((tmp & 0x00000FC0) >> 6)] ;

				outputPtr[3] = _encode[(tmp & 0x0000003F)] ;

			}

			*dwOutputSize += 4 ;
			seventySixCount += 4 ;
			remainingSize -= 3 ;
			inputPtr += 3 ;
			outputPtr += 4 ;

			// Check if '\n' \r' sequence is necessary.
			if ( seventySixCount >= 76 )
			{
				seventySixCount = 0 ;
				*dwOutputSize += 2 ;
				outputPtr[0] = '\n' ;
				outputPtr[1] = '\r' ;
				outputPtr += 2 ;
			}

		}

	}


}

int CProfAdmin::Hascii2Bin(PCHAR hasc, PCHAR *OutBuf, int *OutLen)
{
	int status = 0;
	PCHAR data;
	unsigned int i = 0;
	int binNum;

	do {
		*OutLen = (unsigned int)(strlen(hasc)+1)/2;
		if (*OutLen > 0) {
			data = (char *) malloc (*OutLen);
			memset(data, 0, *OutLen);
			if (data != NULL) {
				while ((int)i < *OutLen) {
					status = sscanf (&hasc[2 * i], "%2x", &binNum);
					data[i] = (char)binNum;
					i++;
				}

			} else {
				*OutLen = 0;
			}
		} else {
				*OutBuf = NULL;
		}

	} while (0);
  *OutBuf = data;
  return(status);
}

HRESULT CProfAdmin::Exch2k_CheckUpdateRight(_bstr_t& i_bstrServerName,
											_bstr_t&i_bstrLegacyExchangeDN,
											BOOL  bAutoDC)
{

	DWORD           err=0;
	int             i=0;

	ULONG			version = LDAP_VERSION3;
	unsigned char   *pbMyUserCert = NULL;
	unsigned int    cbMyUserCert = 0;

	unsigned char   *pbsid=NULL;
	unsigned int    cbsid = 0;

	PSID			pMySID;
	WCHAR           *a=NULL, *dn=NULL,*buffer=NULL;
	WCHAR			szBaseDN[MAXLEN]; 
	

	LDAP			*ldapConnection =NULL;
	LDAPMessage     *results = NULL,*e=NULL;
	
	BerElement      *ber;

	hr=S_OK;

	

	do
	{
	
			if(!bAutoDC)
			{
					#ifdef	_VS_LOG_MSG_
							VSGSE_Log(FALSE,L"Exch2k_CheckUpdateRight Ldap Server :%s",
										_MultiToWideString((char*)i_bstrServerName));

							VSGSE_Log(FALSE,L"Exch2k_CheckUpdateRight DN :%s",
										_MultiToWideString((char*)i_bstrLegacyExchangeDN));
					 #endif
			
					ldapConnection = ldap_init(i_bstrServerName, LDAP_PORT );
					if ( ldapConnection == NULL ) {
						err=LdapGetLastError();
						hr= HRESULT_FROM_WIN32(err) ;

						#ifdef	_VS_LOG_MSG_
							buffer=ldap_err2string(err); 
							VSGSE_Log(FALSE,L"ERROR:ldap_init FAILED :Error Code : 0x%08X",hr);
							VSGSE_Log(FALSE,L"ERROR: ldap_init FAILED : Error Desc: %s", buffer);

						#endif
						break;

					}

					// Set the version to 3.0 (default is 2.0).
					err = ldap_set_option(ldapConnection,LDAP_OPT_VERSION,&version);
					if (err != LDAP_SUCCESS) {
						buffer=ldap_err2string(err); 
						hr= HRESULT_FROM_WIN32(err);

						#ifdef	_VS_LOG_MSG_
							buffer=ldap_err2string(err); 
							VSGSE_Log(FALSE,L"ERROR:ldap_set_option FAILED :Error Code : 0x%08X",hr);
							VSGSE_Log(FALSE,L"ERROR: ldap_set_option FAILED : Error Desc: %s", buffer);

						#endif

						break;
					}
					
					err=ldap_connect(ldapConnection, NULL);
					if (err != LDAP_SUCCESS) {
						buffer=ldap_err2string(err); 
						hr= HRESULT_FROM_WIN32(err);

						#ifdef	_VS_LOG_MSG_
							buffer=ldap_err2string(err); 
							VSGSE_Log(FALSE,L"ERROR:ldap_connect FAILED :Error Code : 0x%08X",hr);
							VSGSE_Log(FALSE,L"ERROR: ldap_connect FAILED : Error Desc: %s", buffer);

						#endif

						break;
					}
				
					// Bind with the caller's credentials.
					err = ldap_bind_s( ldapConnection, NULL, NULL, LDAP_AUTH_NEGOTIATE);
					if (err != LDAP_SUCCESS) {
						buffer=ldap_err2string(err); 
						hr= HRESULT_FROM_WIN32(err);

						#ifdef	_VS_LOG_MSG_
							buffer=ldap_err2string(err); 
							VSGSE_Log(FALSE,L"ERROR:ldap_bind_s FAILED :Error Code : 0x%08X",hr);
							VSGSE_Log(FALSE,L"ERROR: ldap_bind_s FAILED : Error Desc: %s", buffer);

						#endif

						break;
					}

					 WCHAR * szDefNamCnxt=NULL;
					 HRESULT hr=S_OK;
					 hr=Exch2k_GetDefNamCnxt_Domain(ldapConnection,&szDefNamCnxt);
					 if(hr!=S_OK)
					 {
						break;
					 }

					 if(szDefNamCnxt!=NULL)
					 {
						 wcscpy(szBaseDN,szDefNamCnxt);

					 }

					 #ifdef	_VS_LOG_MSG_
						VSGSE_Log(FALSE,L"Exch2k_CheckUpdateRight start :%s",szBaseDN);
					 #endif


					 
			}
			else
			{
					#ifdef	_VS_LOG_MSG_
						VSGSE_Log(FALSE,L"Exch2k_CheckUpdateRight DN :%s",
										_MultiToWideString((char*)i_bstrLegacyExchangeDN));
					 #endif

					ldapConnection = ldap_init(NULL, LDAP_PORT );
					if ( ldapConnection == NULL ) {
						err=LdapGetLastError();
						hr=HRESULT_FROM_WIN32(err) ;
						#ifdef	_VS_LOG_MSG_
							buffer=ldap_err2string(err); 
							VSGSE_Log(FALSE,L"ERROR:ldap_init FAILED :Error Code : 0x%08X",hr);
							VSGSE_Log(FALSE,L"ERROR: ldap_init FAILED : Error Desc: %s", buffer);

						#endif

						break;

					}
					// Set the version to 3.0 (default is 2.0).
					err = ldap_set_option(ldapConnection,LDAP_OPT_VERSION,&version);
					if (err != LDAP_SUCCESS) {
						buffer=ldap_err2string(err); 
						hr= HRESULT_FROM_WIN32(err);

						#ifdef	_VS_LOG_MSG_
							buffer=ldap_err2string(err); 
							VSGSE_Log(FALSE,L"ERROR:ldap_set_option FAILED :Error Code : 0x%08X",hr);
							VSGSE_Log(FALSE,L"ERROR: ldap_set_option FAILED : Error Desc: %s", buffer);

						#endif

						break;
					}

					err=ldap_connect(ldapConnection, NULL);
					if (err != LDAP_SUCCESS) {
						buffer=ldap_err2string(err); 
						hr= HRESULT_FROM_WIN32(err);

						#ifdef	_VS_LOG_MSG_
							buffer=ldap_err2string(err); 
							VSGSE_Log(FALSE,L"ERROR:ldap_connect FAILED :Error Code : 0x%08X",hr);
							VSGSE_Log(FALSE,L"ERROR: ldap_connect FAILED : Error Desc: %s", buffer);

						#endif

						break;
					}

					WCHAR    *serverName;
					serverName=(WCHAR*)malloc(MAXLEN);
					err=ldap_get_option(ldapConnection,LDAP_OPT_HOST_NAME ,(void*)&serverName);
					if (err != LDAP_SUCCESS) {
						buffer=ldap_err2string(err); 
						hr= HRESULT_FROM_WIN32(err);

						#ifdef	_VS_LOG_MSG_
							buffer=ldap_err2string(err); 
							VSGSE_Log(FALSE,L"ERROR:ldap_get_option FAILED :Error Code : 0x%08X",hr);
							VSGSE_Log(FALSE,L"ERROR: ldap_get_option FAILED : Error Desc: %s", buffer);

						#endif

						break;
					}
					m_pInfo.bstrHomeServer=serverName;

					#ifdef	_VS_LOG_MSG_
							VSGSE_Log(FALSE,L"Exch2k_CheckUpdateRight :%s",serverName);
					#endif

					// Bind with the caller's credentials.
					err = ldap_bind_s( ldapConnection, NULL, NULL,LDAP_AUTH_NEGOTIATE);
					if (err != LDAP_SUCCESS) {
						buffer=ldap_err2string(err); 
						hr= HRESULT_FROM_WIN32(err);

						#ifdef	_VS_LOG_MSG_
							buffer=ldap_err2string(err); 
							VSGSE_Log(FALSE,L"ERROR:ldap_bind_s FAILED :Error Code : 0x%08X",hr);
							VSGSE_Log(FALSE,L"ERROR: ldap_bind_s FAILED : Error Desc: %s", buffer);

						#endif

						break;
					}

					 WCHAR* szDefNamCnxt=NULL;
					 HRESULT hr=S_OK;
					 hr=Exch2k_GetDefNamCnxt_Domain(ldapConnection,&szDefNamCnxt);
					 if(hr!=S_OK)
					 {
						break;
					 }

					 if(szDefNamCnxt!=NULL)
					 {
						 wcscpy(szBaseDN,szDefNamCnxt);
					 }

					 #ifdef	_VS_LOG_MSG_
						VSGSE_Log(FALSE,L"Exch2k_CheckUpdateRight start :%s",szBaseDN);
					 #endif
				
			}

			//////check for HRESULT 
			CHECK_HRESULT

			///////////////////////////////////////////
			// search for all entries for mailbox  
			// use legacyExchangeDN

			err=ldap_search_s(ldapConnection,szBaseDN, LDAP_SCOPE_SUBTREE, 
					  i_bstrLegacyExchangeDN ,exch2k_updateattrs,  0, &results );
			if(err!=LDAP_SUCCESS){
						buffer=ldap_err2string(err); 
						hr= HRESULT_FROM_WIN32(err);

						#ifdef	_VS_LOG_MSG_
							buffer=ldap_err2string(err); 
							VSGSE_Log(FALSE,L"ERROR:ldap_search_s FAILED :Error Code : 0x%08X",hr);
							VSGSE_Log(FALSE,L"ERROR: ldap_search_s FAILED : Error Desc: %s", buffer);

						#endif

						break;
				
			}

			//for each entry print out name + all attrs and values 
			   for ( e = ldap_first_entry( ldapConnection, results ); e != NULL;
				e = ldap_next_entry( ldapConnection, e ) ) {
				  if ( (dn = ldap_get_dn( ldapConnection, e )) != NULL ) {
					 // save the Base DN to get other properties of user
					 m_pInfo.bstrBaseDN=dn;
					 ldap_memfree( dn );
				  }

		  				 for ( a = ldap_first_attribute( ldapConnection, e, &ber );
							a != NULL; a = ldap_next_attribute( ldapConnection, e, ber ))
					{
							PLDAP_BERVAL *pBer=NULL;
							
							if(wcscmp(a,exch2k_updateattrs[0])==0)
							{

								pBer = ldap_get_values_len(ldapConnection, e, a);
								if(*pBer == NULL)
								{
									hr=E_FAILED_LDAP_GET_LEN;				
									break;
								}
								
            					pbsid = (unsigned char *)malloc(pBer[0]->bv_len + 1);
								memset(pbsid, 0, pBer[0]->bv_len + 1);
								memcpy(pbsid, pBer[0]->bv_val, pBer[0]->bv_len);
								cbsid= pBer[0]->bv_len;

							
							}

							if(bRenewCert==1)
							{
								if(wcscmp(a,exch2k_updateattrs[1])==0)
								{

									pBer = ldap_get_values_len(ldapConnection, e, a);
									if(*pBer == NULL)
									{
										hr= E_FAILED_LDAP_GET_LEN;				
										break;
									}
								
            						pbMyUserCert = (unsigned char *)malloc(pBer[0]->bv_len + 1);
									memset(pbMyUserCert, 0, pBer[0]->bv_len + 1);
									memcpy(pbMyUserCert, pBer[0]->bv_val, pBer[0]->bv_len);
									cbMyUserCert= pBer[0]->bv_len;

								}
							}

							ldap_memfree(a);
							ldap_value_free_len(pBer);

					}
					 

				}
			
			CHECK_HRESULT

                        if(pbsid == NULL)
                        {
                        hr=E_SID_NOTFOUND;

				#ifdef	_VS_LOG_MSG_
						VSGSE_Log(FALSE,L"ERROR:ldap_search_s - Sid NOT FOUND:Error Code : 0x%08X",hr);
				#endif
				break;
			}

			//////Get the SID Information
			if ((pMySID = GetMySid()) == NULL)
			{
       			hr=E_UNABLE_TO_GET_SID;

				#ifdef	_VS_LOG_MSG_
						VSGSE_Log(FALSE,L"ERROR:GetMySid FAILED :Error Code : 0x%08X",hr);
				#endif
				break;
			}
    
			
			BOOL bSuccess=EqualSid(pbsid,pMySID);
			if(!bSuccess)
			{
				hr=E_SID_COMP_FAILED;

				#ifdef	_VS_LOG_MSG_
						VSGSE_Log(FALSE,L"ERROR:EqualSid FAILED :Error Code : 0x%08X",hr);
				#endif

				break;
			}
    
			
			if(bRenewCert==1)
			{
				hr=GetCertificateProperties(pbMyUserCert,cbMyUserCert);
				if(hr!=S_OK)
					break;
			
				
			}


	}while(0);



	if(results!=NULL)   
			ldap_msgfree( results );
	if(ldapConnection!=NULL)
		   ldap_unbind( ldapConnection );
	if(pbMyUserCert!=NULL)
		   free(pbMyUserCert);

   return hr;

}

HRESULT CProfAdmin::Exch2k_GetDefNamCnxt_Domain(LDAP *ldapConnection,
												WCHAR**szDefNamingContext)
{
	
	DWORD           err=0;
	int             i=0;
	ULONG			count;

	WCHAR           **vals,*buffer=NULL;
	WCHAR           buffer_value[8024]; 

	LDAPMessage     *results = NULL;

	WCHAR  *attr[2]= {L"DefaultNamingContext",NULL};

	memset(buffer_value, 0, 8024);

	LDAPMessage* pmsgResult = NULL;
    err = ldap_search_s(
						ldapConnection,        
						L"",				   // empty container name means RootDSE
						LDAP_SCOPE_BASE,       // search scope
						L"ObjectClass=*",      // search crtieria
						attr,                 // return all attributes
						(ULONG)false,          // not attrs only
						&pmsgResult
						);          

	if(err!=LDAP_SUCCESS){
			
			#ifdef	_VS_LOG_MSG_
							buffer=ldap_err2string(err); 
							VSGSE_Log(FALSE,L"ERROR:ldap_search_s FAILED :Error Code : 0x%08X",
								HRESULT_FROM_WIN32(err));
							VSGSE_Log(FALSE,L"ERROR: ldap_search_s FAILED : Error Desc: %s", buffer);

			#endif

		  	return  HRESULT_FROM_WIN32(err);

			
	}

	LDAPMessage* pmsgObject = ldap_first_entry(ldapConnection, pmsgResult);
	if(err == 0 && pmsgObject != NULL)
	{
		WCHAR* pszAttrName;
		BerElement *sberAttrValue;
		for(pszAttrName = ldap_first_attribute(ldapConnection, pmsgObject, &sberAttrValue);
			pszAttrName != NULL;
			pszAttrName = ldap_next_attribute(ldapConnection, pmsgObject, sberAttrValue))
		 {
			 // do something with pszAttrName and sberAttrValue here
			 if ((vals = ldap_get_values( ldapConnection, pmsgObject, pszAttrName)) != NULL ) {
						 count=ldap_count_values(vals);			
						for ( i = 0; vals[i] != NULL; i++ ) {
								swprintf(buffer_value, L" %s",  vals[i] );
						}
						ldap_value_free( vals );
			 }

		 }
	}

    *szDefNamingContext=(WCHAR*)malloc((wcslen(buffer_value) + 1) *sizeof(WCHAR));
	if(*szDefNamingContext!=NULL)
	{
		wcscpy(*szDefNamingContext,buffer_value);
	}
	return hr;
}

HRESULT CProfAdmin::Exch2k_GetMailBoxInfo(_bstr_t& i_bstrExchSrvr,
										  _bstr_t& i_bstrBaseDN,
										  BOOL  bAutoDC,
		  								  MailBoxInfo *pMailBoxInfo)
{

	DWORD           err=0;
	int             i=0,Index;
	ULONG			version = LDAP_VERSION3,count;

	WCHAR           *a=NULL, *dn=NULL,**vals,*buffer=NULL;
	WCHAR           buffer_value[8024]; 

	LDAP			*ldapConnection =NULL;
	LDAPMessage     *results = NULL,*e=NULL;
	BerElement      *ber;

	hr=S_OK;

	do
	{		/*
			//Connect to the default LDAP server.
			ldapConnection = ldap_open(i_bstrExchSrvr, LDAP_PORT );
			if ( ldapConnection == NULL ) {
				err=LdapGetLastError();
				hr= HRESULT_FROM_WIN32(err) ;

				#ifdef	_VS_LOG_MSG_
							buffer=ldap_err2string(err); 
							VSGSE_Log(FALSE,L"ERROR:ldap_open FAILED :Error Code : 0x%08X",hr);
							VSGSE_Log(FALSE,L"ERROR: ldap_open FAILED : Error Desc: %s", buffer);
				#endif

				break;
			}
			*/

				#ifdef	_VS_LOG_MSG_
						VSGSE_Log(FALSE,L"Exch2k_GetMailBoxInfo DN :%s",
									_MultiToWideString((char*)i_bstrBaseDN));
				#endif


				if(!bAutoDC)
				{

						#ifdef	_VS_LOG_MSG_
						VSGSE_Log(FALSE,L"Exch2k_GetMailBoxInfo Ldap Server :%s",
									_MultiToWideString((char*)i_bstrExchSrvr));
						 #endif

				
					ldapConnection = ldap_init(i_bstrExchSrvr, LDAP_PORT );
					if ( ldapConnection == NULL ) {
							err=LdapGetLastError();
							hr= HRESULT_FROM_WIN32(err) ;

							#ifdef	_VS_LOG_MSG_
								buffer=ldap_err2string(err); 
								VSGSE_Log(FALSE,L"ERROR:ldap_init FAILED :Error Code : 0x%08X",hr);
								VSGSE_Log(FALSE,L"ERROR: ldap_init FAILED : Error Desc: %s", buffer);

							#endif
							break;

						}
				}
				else
				{
					ldapConnection = ldap_init(NULL, LDAP_PORT );
					if ( ldapConnection == NULL ) {
							err=LdapGetLastError();
							hr= HRESULT_FROM_WIN32(err) ;

							#ifdef	_VS_LOG_MSG_
								buffer=ldap_err2string(err); 
								VSGSE_Log(FALSE,L"ERROR:ldap_init FAILED :Error Code : 0x%08X",hr);
								VSGSE_Log(FALSE,L"ERROR: ldap_init FAILED : Error Desc: %s", buffer);

							#endif
							break;

						}



				}


				CHECK_HRESULT
			
				// Set the version to 3.0 (default is 2.0).
				err = ldap_set_option(ldapConnection,LDAP_OPT_VERSION,&version);
				if (err != LDAP_SUCCESS) {
					buffer=ldap_err2string(err); 
					hr= HRESULT_FROM_WIN32(err);

					#ifdef	_VS_LOG_MSG_
						buffer=ldap_err2string(err); 
						VSGSE_Log(FALSE,L"ERROR:ldap_set_option FAILED :Error Code : 0x%08X",hr);
						VSGSE_Log(FALSE,L"ERROR: ldap_set_option FAILED : Error Desc: %s", buffer);

					#endif

					break;
				}
				
				err=ldap_connect(ldapConnection, NULL);
				if (err != LDAP_SUCCESS) {
					buffer=ldap_err2string(err); 
					hr= HRESULT_FROM_WIN32(err);

					#ifdef	_VS_LOG_MSG_
						buffer=ldap_err2string(err); 
						VSGSE_Log(FALSE,L"ERROR:ldap_connect FAILED :Error Code : 0x%08X",hr);
						VSGSE_Log(FALSE,L"ERROR: ldap_connect FAILED : Error Desc: %s", buffer);

					#endif

					break;
				}

             ////////////////////

			// Bind with the caller's credentials.
			err = ldap_bind_s( ldapConnection, NULL, NULL, LDAP_AUTH_NEGOTIATE);
			if (err != LDAP_SUCCESS) {
				buffer=ldap_err2string(err); 
				hr= HRESULT_FROM_WIN32(err);

				#ifdef	_VS_LOG_MSG_
							buffer=ldap_err2string(err); 
							VSGSE_Log(FALSE,L"ERROR:ldap_bind_s FAILED :Error Code : 0x%08X",hr);
							VSGSE_Log(FALSE,L"ERROR: ldap_bind_s FAILED : Error Desc: %s", buffer);

				#endif

				break;
			}

			// search for Attributes of mailbox
			err=ldap_search_s(ldapConnection, i_bstrBaseDN, LDAP_SCOPE_SUBTREE     ,
					  L"(Objectclass=*)", exch2k_attrs, 0, &results );
			if(err!=LDAP_SUCCESS){
					buffer=ldap_err2string(err); 
					hr= HRESULT_FROM_WIN32(err);

					#ifdef	_VS_LOG_MSG_
							buffer=ldap_err2string(err); 
							VSGSE_Log(FALSE,L"ERROR:ldap_search_s FAILED :Error Code : 0x%08X",hr);
							VSGSE_Log(FALSE,L"ERROR: ldap_search_s FAILED : Error Desc: %s", buffer);
					#endif

					break;
			}

			gLDAPAccess=TRUE;  //////Get  attributes

			//for each entry print out name + all attrs and values 
			  for ( e = ldap_first_entry( ldapConnection, results ); e != NULL;
				e = ldap_next_entry( ldapConnection, e ) ) {
				  if ( (dn = ldap_get_dn( ldapConnection, e )) != NULL ) {
						pMailBoxInfo->bstrUserDN=dn;
						ldap_memfree( dn );
				  }
				  for ( a = ldap_first_attribute( ldapConnection, e, &ber );
				   a != NULL; a = ldap_next_attribute( ldapConnection, e, ber ) ) {
					 Index=IsAttributeInclude(a);
					 if(Index!=-1)
					 {
						 ///////
							 if ((vals = ldap_get_values( ldapConnection, e, a)) != NULL ) {
								 count=ldap_count_values(vals);			
								for ( i = 0; vals[i] != NULL; i++ ) {
									// DEBUg -
									// The email address is now in an attribute called
									// proxyAddresses.  We need to parse it.
									if (Index == 3 && (wcsncmp(L"SMTP:", vals[i], 5) == 0)) {
										swprintf(buffer_value, L"%s",  &vals[i][5] );
										break;

									} // END DEBUG
									swprintf(buffer_value, L"%s",  vals[i] );
								}
								ldap_value_free( vals );
								///////////
								switch(Index)
								{
								case 0:
									 pMailBoxInfo->bstrcn=buffer_value;
								break;
							   case 1:
									pMailBoxInfo->bstrUserDN=buffer_value;
								break;
								case 2:
									pMailBoxInfo->bstrHome_MTA=buffer_value;
								break;
								case 3:
 									pMailBoxInfo->bstrrfc822Mailbox=buffer_value;
								break;

								case 4:
									pMailBoxInfo->bstruid=buffer_value;
								break;
								case 5:
									pMailBoxInfo->bstrupn=buffer_value;
								break;
								// Start Add : Infosys : CR21346
								// Populate the user first name and the last name values.
								case 6:
									pMailBoxInfo->bstrFirstName=buffer_value;
								break;
								case 7:
									pMailBoxInfo->bstrLastName=buffer_value;
								break;
								// End Add : Infosys : CR21346
								}
								//////////

							 }
							 /////////
					 }

					 ldap_memfree( a );
				  }
			   }

		}while(0);

	   if(results!=NULL)	
			ldap_msgfree( results );

	   if(ldapConnection!=NULL)
			ldap_unbind( ldapConnection );

	   return hr;

}

HRESULT CProfAdmin::Exch2k_CertUpdate()
{
	int			binLen = 0;
	DWORD		err=0, outB64Size=0;
	
	WCHAR		*buffer;
    PCHAR		binBuffer;
	
	LDAP		*ldapConnection = NULL;
    LDAPMod     mod,*mods[2];
	LDAP_BERVAL *BerVal[2];

	//  Connect to the default LDAP server.
	ldapConnection = ldap_open(ghbstrHomeServer, LDAP_PORT );
	if ( ldapConnection == NULL ) {
		err=GetLastError();
		#ifdef	_VS_LOG_MSG_
				buffer=ldap_err2string(err); 
				VSGSE_Log(FALSE,L"ERROR:ldap_open FAILED :Error Code : 0x%08X",HRESULT_FROM_WIN32(err));
				VSGSE_Log(FALSE,L"ERROR: ldap_open FAILED : Error Desc: %s", buffer);
		#endif

		return  HRESULT_FROM_WIN32(err);
	}

	// Bind with the caller's credentials.
	err = ldap_bind_s( ldapConnection, NULL, NULL, LDAP_AUTH_NEGOTIATE );
	if (err != LDAP_SUCCESS) {
		#ifdef	_VS_LOG_MSG_
				buffer=ldap_err2string(err); 
				VSGSE_Log(FALSE,L"ERROR:ldap_bind_s FAILED :Error Code : 0x%08X",HRESULT_FROM_WIN32(err));
				VSGSE_Log(FALSE,L"ERROR: ldap_bind_s FAILED : Error Desc: %s", buffer);
		#endif

		return HRESULT_FROM_WIN32(err);

	}

	// DEBUG: Change the format to Base64
	////Fill the Mod structure with proper data
	if(UserOrSMIME) {
		 Hascii2Bin(ghbstrUserCertificate, &binBuffer, &binLen);
		mod.mod_type = L"userCertificate";
	}
	else
	{
		
         Hascii2Bin(ghbstrSMIMECertificate, &binBuffer, &binLen);
		 mod.mod_type=L"userSMIMECertificate";
    }

	BerVal[0] = (struct berval *)malloc(sizeof(struct berval));
	BerVal[0]->bv_len = binLen;

    BerVal[0]->bv_val = binBuffer;
	BerVal[1] = NULL;

	
	mod.mod_values = NULL;
	mod.mod_vals.modv_bvals = BerVal;
	/* Start Change : Infosys */
	/* Changed to fix the problem discovered while GSe testing with UAS */
	/* When user enrolls for GSE certificate SMIME certificate is overwritting */
	/* UAS certificate in active directory */
	/* mod.mod_op=LDAP_MOD_REPLACE | LDAP_MOD_BVALUES; */
	mod.mod_op=LDAP_MOD_ADD | LDAP_MOD_BVALUES;
	/* End Change : Infosys */

    mods[0]=&mod;
	mods[1]=NULL;

	err=ldap_modify_s(ldapConnection,ghbstrMailDN,mods);
	if(err!=LDAP_SUCCESS)
	{
		buffer=ldap_err2string(err);
		ldap_unbind(ldapConnection);
		free(BerVal[0]); free(binBuffer);

		#ifdef	_VS_LOG_MSG_
				buffer=ldap_err2string(err); 
				VSGSE_Log(FALSE,L"ERROR:ldap_modify_s FAILED :Error Code : 0x%08X",HRESULT_FROM_WIN32(err));
				VSGSE_Log(FALSE,L"ERROR: ldap_modify_s FAILED : Error Desc: %s", buffer);
		#endif

		return HRESULT_FROM_WIN32(err);

	}
    ldap_unbind(ldapConnection);

    
	ghbstrUserCertificate="";
    ghbstrSMIMECertificate="";

	free(binBuffer);
	free(BerVal[0]);

	return HRESULT_FROM_WIN32(err);

}

HRESULT CProfAdmin::UpdateCertificateData()
{
	if(ghExch_UpdateVer==EXCH_55)
	{
		hr=CertUpdate();
	}
		
	if(ghExch_UpdateVer==EXCH_2000)
	{
		hr=Exch2k_CertUpdate();

	}
	return hr;
}

HRESULT CProfAdmin::Exchange55()
{

	 hr=S_OK;
 
	 _bstr_t   bstrLdapDN=""; 	
     
	 PrepareLDAPDN(m_pInfo.bstrProfileUser,&bstrLdapDN);
	 hr=CheckUpdateRight(m_pInfo.bstrHomeServer,bstrLdapDN);
	 if(hr!=0)
		goto Quit;
	 hr=GetMailBoxInfo(m_pInfo.bstrHomeServer,bstrLdapDN,&gMailBoxInfo);
	 if(hr!=0)
	    goto  Quit;


	 #ifdef	_VS_LOG_MSG_
		VSGSE_Log(FALSE,L"MailBox Info:CN=%s",	_MultiToWideString((char*)gMailBoxInfo.bstrcn));
		VSGSE_Log(FALSE,L"MailBox Info:DN=%s",	_MultiToWideString((char*)gMailBoxInfo.bstrdistinguishedName));
		VSGSE_Log(FALSE,L"MailBox Info:USERDN=%s",	_MultiToWideString((char*)gMailBoxInfo.bstrUserDN));
		VSGSE_Log(FALSE,L"MailBox Info:RFC822=%s",	_MultiToWideString((char*)gMailBoxInfo.bstrrfc822Mailbox));
	
     #endif


Quit:
	 return hr;
}

HRESULT CProfAdmin::Exchange2000()
{
	hr=S_OK;
	char *lpToken=NULL;
    char *pADSInfo=NULL;

	BOOL  bAutoDC;
    
	if(ghADServerInfo==0)
	{
		
		if(ghbstrADServerInfoList.length()>0)
		{

				 #ifdef	_VS_LOG_MSG_
					VSGSE_Log(FALSE,L"ADServerInfoList:=%s",	_MultiToWideString((char*)ghbstrADServerInfoList));
				 #endif
		
			    bAutoDC=FALSE;
				pADSInfo=strdup(ghbstrADServerInfoList);
				lpToken=strtok(pADSInfo,ID_COMA_SEP);
				while(lpToken!=NULL)
				{
					_bstr_t  bstrServerName=lpToken;
					hr=Exch2k_CheckUpdateRight(bstrServerName,m_pInfo.bstrLegacyExchangeDN,bAutoDC);
					if(hr==S_OK)
					{
						 
						 _bstr_t  bstrLdapDN;
						 m_pInfo.bstrHomeServer=lpToken;
						 PrepareLDAPDN(m_pInfo.bstrProfileUser,&bstrLdapDN);
						 gMailBoxInfo.bstrdistinguishedName=bstrLdapDN;
						 break;
					}
					lpToken=strtok(NULL,ID_COMA_SEP);

				}
		}
	}
	else
	{
				 #ifdef	_VS_LOG_MSG_
					VSGSE_Log(FALSE,L"ADServer Automatic discovery");
				 #endif
			
				bAutoDC=TRUE;
				_bstr_t  bstrAdName="";
				hr=Exch2k_CheckUpdateRight(bstrAdName,m_pInfo.bstrLegacyExchangeDN,bAutoDC);
				if(hr==S_OK)
				{
				   _bstr_t   bstrldapDN;
				   PrepareLDAPDN(m_pInfo.bstrProfileUser,&bstrldapDN);
				   gMailBoxInfo.bstrdistinguishedName=bstrldapDN;	
				}
		
	}

	hr=Exch2k_GetMailBoxInfo(m_pInfo.bstrHomeServer,m_pInfo.bstrBaseDN,bAutoDC,&gMailBoxInfo);
	if(hr!=0)
			goto  Quit;

	 #ifdef	_VS_LOG_MSG_
		VSGSE_Log(FALSE,L"MailBox Info:CN=%s",	_MultiToWideString((char*)gMailBoxInfo.bstrcn));
		VSGSE_Log(FALSE,L"MailBox Info:DN=%s",	_MultiToWideString((char*)gMailBoxInfo.bstrdistinguishedName));
		VSGSE_Log(FALSE,L"MailBox Info:USERDN=%s",_MultiToWideString((char*)gMailBoxInfo.bstrUserDN));
		VSGSE_Log(FALSE,L"MailBox Info:RFC822=%s",	_MultiToWideString((char*)gMailBoxInfo.bstrrfc822Mailbox));
	
     #endif

Quit:
	return hr;

}

HRESULT CProfAdmin::CHECKREGForGC()
{

	long			err;
	HKEY hRegKey = NULL;
	_bstr_t     bstrkey="Software\\Microsoft\\Windows NT\\CurrentVersion\\Windows Messaging Subsystem\\Profiles\\";

	bstrkey+=ghbstrCurrentProfile;
	bstrkey+="\\dca740c8c042101ab4b908002b2fe182";

	err=RegOpenKeyEx(HKEY_CURRENT_USER, bstrkey,0,KEY_READ, &hRegKey);
	if(err== ERROR_SUCCESS) 
	{
		RegCloseKey(hRegKey);
		hr=S_OK;
	}
	else
	{
		hr=err;
	}
	return hr;

}

HRESULT CProfAdmin::ExchVerByMapi(LPMAPISESSION lpSession)
{

	WCHAR			wsBuf[MAXLEN];

	LPMDB           lpStore     = NULL;

	LPMAPIFOLDER    lpFolder    = NULL;
	LPSPropValue	pspvVersion = NULL;

	int				result=0;

	WORD			dwEX55MajorHI=5;
	WORD			dwEX55MajorLow=5;
    WORD			dwEX2000MajorHI=6;

	WORD			MajorHI=0,MajorLOW=0;
    WORD			MinorHI=0,MinorLOW=0;

	#ifdef	_VS_LOG_MSG_
			VSGSE_Log(FALSE,L"ExchVerByMapi:start");
    #endif


	// Check exchange version by Registry First Begin.

	hr=CHECKREGForGC(); /////GC Reg Exists assume Exch 2000+
	if(hr==S_OK)
	{
		ghExchVer=EXCH_2000; //For exchange 2000+
		ghVer=TRUE;
		ghbstrExchVerStr="6.0.0.0+";

		goto cleanup;
	}
	else
	{
		#ifdef	_VS_LOG_MSG_
			VSGSE_Log(FALSE,L"ExchVerByMapi:CHECKREGForGC:Error Code : 0x%08X",hr);
		#endif

		if (FAILED(hr = HrOpenDefaultStore(lpSession,&lpFolder)))
		{
			#ifdef	_VS_LOG_MSG_
				VSGSE_Log(FALSE,L"ExchVerByMapi:HrOpenDefaultStore:Error Code : 0x%08X",hr);
			#endif

			goto cleanup;
		}

		hr = HrGetOneProp (lpFolder, PR_REPLICA_VERSION,
		(LPSPropValue*)&pspvVersion);
		if (FAILED(hr))
		{
			#ifdef	_VS_LOG_MSG_
			VSGSE_Log(FALSE,L"ExchVerByMapi:PR_REPLICA_VERSION:Error Code : 0x%08X",hr);
			#endif
			goto cleanup;
		}
	}
	// Check Exchange Version by Registry First End.

	MajorHI=HIWORD(pspvVersion->Value.li.HighPart);
	MajorLOW=LOWORD(pspvVersion->Value.li.HighPart);
	MinorHI=HIWORD(pspvVersion->Value.li.LowPart);
	MinorLOW=LOWORD(pspvVersion->Value.li.LowPart);

	if( (MajorHI== dwEX55MajorHI)&&(MajorLOW==dwEX55MajorLow) )
	{
	   if((MinorHI<2232))
              ghExchVer=-1;
	   else
	   {
			ghExchVer=EXCH_55; //For Valid 5.5 version
			ghVer=TRUE;
	   }

	}

	if(MajorHI>= dwEX2000MajorHI)
	{
		ghExchVer=EXCH_2000; //For exchange 2000
		ghVer=TRUE;
	}

	

	_itow(MajorHI,wsBuf,10);
	ghbstrExchVerStr+=wsBuf;
	ghbstrExchVerStr+=L".";
	
	_itow(MajorLOW,wsBuf,10);
	ghbstrExchVerStr+=wsBuf;
	ghbstrExchVerStr+=L".";

	_itow(MinorHI,wsBuf,10);
	ghbstrExchVerStr+=wsBuf;
	ghbstrExchVerStr+=L".";

	_itow(MinorLOW,wsBuf,10);
	ghbstrExchVerStr+=wsBuf;

	#ifdef	_VS_LOG_MSG_
			VSGSE_Log(FALSE,L"ExchVerByMapi:Version String:%s",
				_MultiToWideString((char*)ghbstrExchVerStr));
    #endif

	

cleanup:
	if (pspvVersion)
		MAPIFreeBuffer(pspvVersion);

	if (lpFolder)
	{
		lpFolder->Release();
		lpFolder = NULL;
	}

	return hr;

}

//	
//	HrOpenDefaultStore function is inserted.
//
HRESULT CProfAdmin::HrOpenDefaultStore(LPMAPISESSION pses, LPMAPIFOLDER *pFolder)
{

    ULONG				i=0;
    LPMDB				lpmdb = NULL;
    LPMAPITABLE			ptable = NULL;
    LPSRowSet			prows = NULL;
    LPSPropValue		pvalProp = NULL;


	LPMAPIFOLDER		lpInbox		= NULL;
	ULONG				ulObjType	= 0;
	ULONG				cbeid		= 0;
	LPENTRYID			lpeid		= NULL;
	
	BOOL				bSuccess	=	FALSE;
	

    static SizedSPropTagArray(3, columns) =
	{ 3, {PR_DISPLAY_NAME, PR_ENTRYID, PR_MDB_PROVIDER} };

    SPropValue valDefStore;
    SRestriction restDefStore;
    
    valDefStore.ulPropTag = PR_DEFAULT_STORE;
    valDefStore.dwAlignPad = 0;
    valDefStore.Value.b = TRUE;
	
    restDefStore.rt = RES_PROPERTY;
    restDefStore.res.resProperty.relop = RELOP_EQ;
    restDefStore.res.resProperty.ulPropTag = PR_DEFAULT_STORE;
    restDefStore.res.resProperty.lpProp = &valDefStore;

	#ifdef	_VS_LOG_MSG_
			VSGSE_Log(FALSE,L"HrOpenDefaultStore:start");
	#endif

    
    hr = pses->GetMsgStoresTable(0, &ptable);
    if (HR_FAILED(hr))
    {
		#ifdef	_VS_LOG_MSG_
			VSGSE_Log(FALSE,L"HrOpenDefaultStore:pses->GetMsgStoresTable:Error Code : 0x%08X",hr);
	    #endif

        TraceFnResult(GetMsgStoresTable, hr);
        goto ret;
    }
	
	////No restriction get All rows
    hr = HrQueryAllRows(ptable, (LPSPropTagArray) &columns, NULL,	NULL, 0, &prows);
    if (HR_FAILED(hr))
    {
		#ifdef	_VS_LOG_MSG_
			VSGSE_Log(FALSE,L"HrOpenDefaultStore:HrQueryAllRows:Error Code : 0x%08X",hr);
	    #endif

        TraceFnResult(HrQyeryAllRows, hr);
        goto ret;
    }

	for (i = 0; i < prows -> cRows; i++)
    {
			
		///// lpProps[1]contain PR_ENTRYID
		if (prows == NULL || prows->cRows == 0
			|| prows->aRow[i].lpProps[1].ulPropTag != PR_ENTRYID)
		{
			goto ret;
		}

		if (prows == NULL || prows->cRows == 0
			|| prows->aRow[i].lpProps[2].ulPropTag != PR_MDB_PROVIDER)
		{
			goto ret;
		}


		MAPIUID msuid = *((MAPIUID*)prows->aRow[i].lpProps[2].Value.bin.lpb);
		MAPIUID msExchangeid;

		/////pbExchangeProviderPrimaryUserGuid  private information store defined in edkmdb.h
		memcpy(msExchangeid.ab,pbExchangeProviderPrimaryUserGuid,16);

		BOOL bExchangeid=IsEqualMAPIUID(&msuid,&msExchangeid); 
		if(bExchangeid)
		{
			#ifdef	_VS_LOG_MSG_
				VSGSE_Log(FALSE,L"IsEqualMAPIUID:TRUE:private information store");
			#endif

			break;
		}

	}

	/////Open the private information store
	hr = pses->OpenMsgStore(0,
					prows->aRow[i].lpProps[1].Value.bin.cb,
					(LPENTRYID)prows->aRow[i].lpProps[1].Value.bin.lpb,
					NULL, MDB_WRITE | MDB_ONLINE | MAPI_DEFERRED_ERRORS, &lpmdb);
				        // Added MDB_ONLINE by Infosys for CR29538
	if (!HR_FAILED(hr))
	{  
		#ifdef	_VS_LOG_MSG_
				VSGSE_Log(FALSE,L"OpenMsgStore:successful:private information store");
		#endif

	
		hr = lpmdb->GetReceiveFolder (
									NULL,		// get default receive folder
									0,			
									&cbeid,		
									&lpeid,		
									NULL		
									);
			 if (SUCCEEDED(hr))
			 {

				 #ifdef	_VS_LOG_MSG_
					VSGSE_Log(FALSE,L"GetReceiveFolder:successful:private information store");
				 #endif

					hr = lpmdb->OpenEntry (
									cbeid,
									lpeid,
									NULL,	// return thedefault interface
									MAPI_BEST_ACCESS,
									&ulObjType,
									(LPUNKNOWN FAR *) &lpInbox
									);
					if(SUCCEEDED(hr))
					{
						#ifdef	_VS_LOG_MSG_
							VSGSE_Log(FALSE,L"OpenEntry:successful:private information store");
								VSGSE_Log(FALSE,L"HrOpenDefaultStore:done");
						#endif
								
							*pFolder = lpInbox;
							bSuccess = TRUE;
							
					}
			}
			else
			{
				#ifdef	_VS_LOG_MSG_
					VSGSE_Log(FALSE,L"HrOpenDefaultStore:lpmdb->GetReceiveFolder:Error Code : 0x%08X",hr);
				#endif
			}
	}
	else
	{
		#ifdef	_VS_LOG_MSG_
			VSGSE_Log(FALSE,L"HrOpenDefaultStore:pses->OpenMsgStore:Error Code : 0x%08X",hr);
	    #endif
	}
	
	if ( bSuccess == TRUE )
	{
	
		hr = S_OK;
	}
	else
	{
		if (S_OK == hr)
		{
			hr = E_FAIL;
		}
		
	}

ret:
	if (lpmdb)
	{
		lpmdb->Release();
		lpmdb = NULL;
	}
	if (prows)
	{
		FreeProws(prows);
	}
	if (ptable)
	{
		UlRelease(ptable);
	}
    return hr;

}


HRESULT CProfAdmin::HrOpenInbox(LPMDB pmdb, LPMAPIFOLDER *lppF)
{

	LPMAPIFOLDER	lpInbox		= NULL;

    ULONG			ulObjType	= 0;
	ULONG			cbeid		= 0;
	LPENTRYID		lpeid		= NULL;
	
    *lppF = NULL;


	hr = pmdb->GetReceiveFolder (NULL,		// get default receive folder
					0,&cbeid,&lpeid,NULL);
	if (SUCCEEDED(hr))
	{
		hr = pmdb->OpenEntry (cbeid,lpeid,
						NULL,	// return thedefault interface
						MAPI_BEST_ACCESS,&ulObjType,(LPUNKNOWN FAR *) &lpInbox);
		if(SUCCEEDED(hr))
		{
			*lppF = lpInbox;
		}
		else
		{
			#ifdef	_VS_LOG_MSG_
			VSGSE_Log(FALSE,L"HrOpenInbox:pmdb->OpenEntry:Error Code : 0x%08X",hr);
			#endif
		}
	}
	else
	{
		#ifdef	_VS_LOG_MSG_
			VSGSE_Log(FALSE,L"HrOpenInbox:pmdb->GetReceiveFolder:Error Code : 0x%08X",hr);
	    #endif
	}
	
    return hr;

}

HRESULT CProfAdmin::FindExchVer(_bstr_t& i_bstrProfileName)
{

	LPMAPISESSION   lpSession   = NULL;
	_bstr_t       bstrDefaultProfile="";

	int  ver=0;
	
	if(!gbDefOutLookClient)
	{
		hr=E_NOTDEF_OUTLOOK_CLINET;
		goto Quit;
	}
	

	
	if(i_bstrProfileName.length()==0)
	{
		hr=GetDefaultProfile(&bstrDefaultProfile);
		if(hr!=0)
	 		goto Quit;

		if(bstrDefaultProfile.length()==0)
			goto Quit;

		hr=IsExchProfile(bstrDefaultProfile);
		if(hr==1)  //default is exchange profile
		{
			hr=GetProfileInfo(bstrDefaultProfile,&m_pInfo);
			if(FAILED(hr))
				goto Quit;
			ghbstrCurrentProfile=bstrDefaultProfile.copy();

		}
		else
			goto Quit;

	}
	else
	{
		   ghbstrCurrentProfile=i_bstrProfileName.copy();
	}

	hr = MAPILogonEx (0,ghbstrCurrentProfile,NULL,
				MAPI_NEW_SESSION |MAPI_EXPLICIT_PROFILE,&lpSession);
	if (FAILED(hr))
	{
		#ifdef	_VS_LOG_MSG_
			VSGSE_Log(FALSE,L"FindExchVer:MAPILogonEx:Error Code : 0x%08X",hr);
	    #endif
		goto Quit;
	}
	hr=ExchVerByMapi(lpSession);
	if (FAILED(hr))
	{
		goto Quit;
	}
	
Quit:
	
	if (lpSession)
	{
		lpSession->Logoff(0, 0, 0);
		lpSession->Release();
	}
	return hr;
}

HRESULT CProfAdmin::VerifyCertChain(BSTR newVal)
{

	//CLSID					   clsSgnAtr;
	ISignAttributes            *olSgnAtr;
	BSTR                       bUserCertificate,bSMIMECertificate;

    hr=CoCreateInstance(CLSID_SignAttributes, NULL, CLSCTX_ALL,
										IID_ISignAttributes, (void **)&olSgnAtr); 

	if(hr!=S_OK)
		return hr;

	hr=olSgnAtr->put_userCertificate(newVal);
	if(hr!=S_OK)
		return hr;

	hr=olSgnAtr->get_EncUserCertificate(&bUserCertificate);
	if(hr!=S_OK)
		return hr;

	ghbstrUserCertificate=bUserCertificate;
	if(ghbstrUserCertificate.length()==0)
	{
		goto Quit;
	}
	
	hr=olSgnAtr->get_EncUserSMIMECertificate(&bSMIMECertificate);
	if(hr!=S_OK)
	{
		goto Quit;
	}


	UserOrSMIME=TRUE;  //TRUE for user certificate
	hr=UpdateCertificateData();
	if(hr!=S_OK)
		goto Quit;


	ghbstrSMIMECertificate=bSMIMECertificate;
	if(ghbstrSMIMECertificate.length()==0)
	{
		goto Quit;
	}

	UserOrSMIME=FALSE;  //FALSE for smime certificate
	hr=UpdateCertificateData();
	if(hr!=S_OK)
		goto Quit;

Quit:

	return hr;

}

HRESULT CProfAdmin::IsUserMemberOfAdminGroup(BOOL *bResult)
{
	DWORD i, dwSize = 0, dwResult = 0;
	HANDLE hToken;
	PTOKEN_GROUPS pGroupInfo;
	SID_NAME_USE SidType;

	
	char lpName[MAX_NAME];
	char lpDomain[MAX_NAME];
	BYTE sidBuffer[100];
	PSID pSID = (PSID)&sidBuffer;
	SID_IDENTIFIER_AUTHORITY SIDAuth = SECURITY_NT_AUTHORITY;
   

	do {

	  *bResult = FALSE;

	  // Open a handle to the access token for the calling process.
	  if (!OpenProcessToken( GetCurrentProcess(), TOKEN_QUERY, &hToken )) {
		  dwResult = GetLastError();
		  _ShowErrorMessage(dwResult, "_MultiToWideString : OpenProcesToken Error.") ;
		  break;
	  }

	  // Call GetTokenInformation to get the buffer size.
	  if(!GetTokenInformation(hToken, TokenGroups, NULL, dwSize, &dwSize)) {
		  dwResult = GetLastError();
		if( dwResult != ERROR_INSUFFICIENT_BUFFER ) {
			_ShowErrorMessage(dwResult, "_MultiToWideString : GetTokenInformation Error") ;
			break;
		}
		else dwResult = S_OK;
	  }

	  // Allocate the buffer.
	  pGroupInfo = (PTOKEN_GROUPS) GlobalAlloc( GPTR, dwSize );

	  // Call GetTokenInformation again to get the group information.
	  if(! GetTokenInformation(hToken, TokenGroups, pGroupInfo, 
                        dwSize, &dwSize ) ) {
		  dwResult = GetLastError();
		  _ShowErrorMessage(dwResult, "_MultiToWideString : GetTokenInformation Error.") ;
		
		  break;
	  }

	  // Create a SID for the BUILTIN\Administrators group.
	  if(! AllocateAndInitializeSid( &SIDAuth, 2,SECURITY_BUILTIN_DOMAIN_RID,
                 DOMAIN_ALIAS_RID_ADMINS, 0, 0, 0, 0, 0, 0,&pSID) ) {
		  dwResult = GetLastError();
		  _ShowErrorMessage(dwResult, "_MultiToWideString : AllocateAndInitializeSid Error.") ;
		  break;
	  }
	  // Loop through the group SIDs looking for the administrator SID.
	  for(i=0; i<pGroupInfo->GroupCount; i++) {
	   	if ( EqualSid(pSID, pGroupInfo->Groups[i].Sid) ) {
			// Lookup the account name and print it.
			dwSize = MAX_NAME;
			if( !LookupAccountSid( NULL, pGroupInfo->Groups[i].Sid,
                              lpName, &dwSize, lpDomain, &dwSize, &SidType ) ) {
				dwResult = GetLastError();
				_ShowErrorMessage(dwResult, "_MultiToWideString :  LookupAccountSid Error.") ;
				break;
			}
			
			// Find out if the SID is enabled in the token
			if (!(pGroupInfo->Groups[i].Attributes & SE_GROUP_ENABLED)) {
				dwResult = -1;
				_ShowErrorMessage(dwResult, "_MultiToWideString :  Group SID is not enabled.") ;
				break;
			}

			*bResult = TRUE;
		}
	  } // end for loop
	} while (0);

	if (pSID)
		FreeSid(pSID);
	if ( pGroupInfo )
		GlobalFree( pGroupInfo );

	return HRESULT_FROM_WIN32(dwResult);
}

HRESULT CProfAdmin::CertFriendlyName(BSTR newVal)
{
	hr = S_OK;
	DWORD			dwResult = 0;
	LPSTR			szBase64PKCS7 ;
	DWORD			cbPKCS7 ;
	PBYTE			pbPKCS7 ;
	HCERTSTORE		hCertStore;
	PBYTE			pbUserCertificate;
	DWORD			cbUserCertificate;

	szBase64PKCS7 = _WideToMultiString(newVal) ;

	_Base64Decode(szBase64PKCS7,strlen(szBase64PKCS7),
				NULL,&cbPKCS7) ;

	pbPKCS7 = (BYTE *) malloc(cbPKCS7+1);

	_Base64Decode(szBase64PKCS7,
					strlen(szBase64PKCS7),
					(char *)pbPKCS7,
					&cbPKCS7) ;

	////////////////////////////////////////////////////////////////////////////
	// Open a Message Handle that will hold the decoded PKCS#7 message
	////////////////////////////////////////////////////////////////////////////

	HCRYPTMSG			hCryptMsg = NULL ;
	if ( (hCryptMsg = CryptMsgOpenToDecode(	MY_ENCODING_TYPE,
					0,0,0,
					NULL,NULL)) == NULL ) 
	{
		dwResult = GetLastError();
		_ShowErrorMessage(dwResult, "put_CertFriendlyName : CryptMsgOpenToDecode for falied") ;
		return hr;
	}

	////////////////////////////////////////////////////////////////////////////
	// Update the handle with the DER of the PKCS#7
	////////////////////////////////////////////////////////////////////////////
	if ( !CryptMsgUpdate(hCryptMsg,	pbPKCS7,cbPKCS7,TRUE) )
	{
		DWORD temp ;
		temp = GetLastError() ;
		_ShowErrorMessage(temp, "put_CertFriendlyName : CryptMsgUpdate for PKCS#7 falied") ;
		return hr;
	}

	
	DWORD		dwNumberOfCerts = 0 ;
	DWORD		dwNumberOfBytes_For_NumberOfCerts = 4 ;

	////////////////////////////////////////////////////////////////////////////
	// Find the number of Certificates in the PKCS#7 message
	////////////////////////////////////////////////////////////////////////////
	if ( !CryptMsgGetParam(hCryptMsg,CMSG_CERT_COUNT_PARAM,
					0,&dwNumberOfCerts,	&dwNumberOfBytes_For_NumberOfCerts) )
	{
		DWORD temp ;
		temp = GetLastError() ;
		_ShowErrorMessage(temp, "put_CertFriendlyName : CryptMsgGetParam for PKCS#7 falied") ;
		return hr ;
	}
	
	// Extract individual certificates (which are in X.509 format) into a 
	// Linked List of Certificate Contexts.

	DWORD					certIndex ;
	BOOL					fFirstCert = TRUE ;
	PCCERT_CONTEXT			pCertContext = NULL ;
	PCCERT_CONTEXT_LIST		pCertContextList = NULL, pTmpCertContextList = NULL ;

	for ( certIndex = 0 ; certIndex < dwNumberOfCerts ; certIndex++ )
	{

		
		BYTE		EncodedCertInPKCS7[10000] ;
		DWORD		dwEncodedCertInPKCS7 = 10000 ;

		if ( !CryptMsgGetParam(hCryptMsg,CMSG_CERT_PARAM ,
						certIndex,EncodedCertInPKCS7,&dwEncodedCertInPKCS7) )
		{
			DWORD temp ;
			temp = GetLastError() ;
			_ShowErrorMessage(temp, "put_CertFriendlyName : CryptMsgGetParam for Certificate in PKCS#7 falied") ;
			return hr ;
		}
		if ( (pCertContext = CertCreateCertificateContext(
						X509_ASN_ENCODING, 
						EncodedCertInPKCS7, 
						dwEncodedCertInPKCS7)) == NULL )
		{
			DWORD temp ;
			temp = GetLastError() ;
			_ShowErrorMessage(temp, "put_SigningCertFriendlyName : CertCreateCertificateContext falied") ;
			return hr ;
		}

		if ( fFirstCert )
		{
			pCertContextList = (PCCERT_CONTEXT_LIST) malloc(sizeof(CCERT_CONTEXT_LIST)) ;
			pTmpCertContextList = pCertContextList ;
			pCertContextList->pCertContext = pCertContext ; 
			pCertContextList->nextCertContext = NULL ;
			fFirstCert = FALSE ;
		}
		else
		{
			pTmpCertContextList->nextCertContext = (PCCERT_CONTEXT_LIST) malloc(sizeof(CCERT_CONTEXT_LIST)) ;
			pTmpCertContextList = pTmpCertContextList->nextCertContext ;
			pTmpCertContextList->pCertContext = pCertContext ;
			pTmpCertContextList->nextCertContext = NULL ;
		}
	}

	PCCERT_CONTEXT_LIST		pSaveCertContextList ;
	DWORD			dwNumberOfCACerts ;
	

	pSaveCertContextList = pCertContextList ;
	dwNumberOfCACerts = dwNumberOfCerts - 1 ; // subtract one for end-entity cert.

	// Determine if the FIRST or the LAST certificate is end-entity certificate.

	// Let us assume that the LAST certificate is indeed the end-entity certificate.
	// If it indeed is, then you should be able to find it in the MY cert store.
	// If you can't find it in MY cert store then just BLINDLY assume that the
	// FIRST cert is the end-entity cert.

	if ( !(hCertStore = CertOpenSystemStore(NULL, "MY")) )
	{
		_ShowErrorMessage(GetLastError(), "put_SigningCertFriendlyName : CertOpenSystemStore falied") ;
		return hr ;
	}

	PCCERT_CONTEXT	pSearchCert = NULL ;
	
	if ( (pSearchCert = CertCreateCertificateContext(
							X509_ASN_ENCODING, 
							pCertContext->pbCertEncoded,			// This points to the LAST cert
																	// in the linked list.
							pCertContext->cbCertEncoded)) == NULL )
	{
		_ShowErrorMessage(GetLastError(), "put_SigningCertFriendlyName : CertCreateCertificateContext falied") ;
		return hr ;
	}

	PCCERT_CONTEXT  pCert ;
	BOOL			bEndUserCert_LAST = TRUE ; // By default, assume that the LAST cert in the
											   // PKCS#7/Linked list is the end-user cert.	
	if ( (pCert = CertFindCertificateInStore(
              hCertStore,				     // Store handle
              MY_ENCODING_TYPE,              // Encoding type
              0,                             // Not used
              CERT_FIND_PUBLIC_KEY,            // Find type
              &pSearchCert->pCertInfo->SubjectPublicKeyInfo,					 // Name string
              NULL)) == NULL )               // Previous context
	{
		// If you can't find the last cert in the linked list IN the MY cert store,
		// then assume that it's the FIRST cert in the linked List that is the end-user
		// cert and that it is also in the MY cert store.
		bEndUserCert_LAST = FALSE ;
	}

	if (pSearchCert)
		CertFreeCertificateContext(pSearchCert) ;

	if (hr)
		return hr ;

	if (pCert)
		CertFreeCertificateContext(pCert) ;

	if ( bEndUserCert_LAST )
	{
		//LAST certificate in the PKCS7 is assumed to be the end-entity certificate.
		cbUserCertificate = pCertContext->cbCertEncoded ;
		pbUserCertificate = pCertContext->pbCertEncoded ;
	}
	else
	{
		//FIRST certificate in the PKCS7 is assumed to be the end-entity certificate.
		cbUserCertificate = pSaveCertContextList->pCertContext->cbCertEncoded ;
		pbUserCertificate = pSaveCertContextList->pCertContext->pbCertEncoded ;
	}


	///Set the EFS certificate
	if(bSetEFSCert)
	{
		if(_SetEFSCertificate(hCertStore,pbUserCertificate,cbUserCertificate))
		return hr;
	}
	
	// Set Friendly Name based on the Key Usage
    if(_SetFriendlyName(hCertStore,	pbUserCertificate, cbUserCertificate ))
		return hr;

	// Start Add : Infosys : CR27993
	// Set the certificate as default certificate for MAPI profile.
	if (nSetDefaultCertFlag != SET_DEFAULT_FOR_NONE)
	{
		// Assign the certificate to the profile default settings.
		// Currently the return value is not checked, in case of error it is just logged 
		AssignCertToProfile(newVal, hCertStore, pbUserCertificate, cbUserCertificate);
	}
	// End Add : Infosys : CR27993

	if(hCertStore)
		CertCloseStore(hCertStore,0);

	return hr;


}

HRESULT CProfAdmin::GetCertificateProperties(unsigned char *pbMyUserCert,
											 unsigned int cbMyUserCert)
{
	hr = S_OK;
	DWORD			dwResult = 0;
	char*			pbBytes =NULL;
	int			    cbByte =0;
	HCERTSTORE		hCertStore;
	PCCERT_CONTEXT	pSearchCert = NULL ;
	PCCERT_CONTEXT  pCert =NULL;


	if(pbMyUserCert==NULL)
		return E_ENC_CERT_NOTFOUND;
	if(cbMyUserCert==0)
		return E_ENC_CERT_NOTFOUND;


	do
	{

			if(ghExchVer==EXCH_55)
				Hascii2Bin((char*)pbMyUserCert, &pbBytes, &cbByte);
			else
			{
				pbBytes=(char*)malloc(cbMyUserCert);
				if(pbBytes==NULL)
				{
					hr=E_FAIL;
					break;
				}
				memcpy(pbBytes,pbMyUserCert,cbMyUserCert);
				cbByte=cbMyUserCert;
			}
			
			if ( !(hCertStore = CertOpenSystemStore(NULL, "MY")) )
			{
				dwResult=GetLastError();
				_ShowErrorMessage(dwResult, " CertOpenSystemStore falied") ;
				 hr=HRESULT_FROM_WIN32(dwResult);
				 break;
			}




			if ( (pSearchCert = CertCreateCertificateContext(
									X509_ASN_ENCODING | PKCS_7_ASN_ENCODING, 
									(PBYTE)pbBytes,		
									cbByte)) == NULL )
			{
				dwResult=GetLastError();
				_ShowErrorMessage(dwResult, " CertCreateCertificateContext") ;
				 hr=HRESULT_FROM_WIN32(dwResult);
				 break;
			}

						
			if ( (pCert = CertFindCertificateInStore(
					  hCertStore,				     // Store handle
					  X509_ASN_ENCODING | PKCS_7_ASN_ENCODING,              // Encoding type
					  0,                             // Not used
					  CERT_FIND_PUBLIC_KEY,            // Find type
					  &pSearchCert->pCertInfo->SubjectPublicKeyInfo, // Name string
					  NULL)) == NULL )               // Previous context
			{
				
				dwResult=GetLastError();
				_ShowErrorMessage(dwResult, " CertFindCertificateInStore falied") ;
				 hr=HRESULT_FROM_WIN32(dwResult);
				 break;
			}

			
			hr = _GetCertSerNum(pSearchCert->pCertInfo->SerialNumber, m_bstrSerialNum);
			if(hr!=S_OK)
				break;
	}
	while(0);


	if (pSearchCert)
		CertFreeCertificateContext(pSearchCert) ;

	if (pCert)
		CertFreeCertificateContext(pCert) ;
	
	if(hCertStore)
		CertCloseStore(hCertStore,0);

	return hr;


}

// Start Add : Infosys : CR27993
/*****************************************************************************/
// AssignCertToProfile() : Assigns the given certificate to the selected profile's
//					       security property according to the certificate type and value
//						   of flag that specifies whether the certificate issued is 
//						   to be made default for Signing, Encryption or Both.
//						   -- Get the MAPI IprofAdmin interface.
//						   -- Get the profile name and open the Service Admin interface.
//						   -- Open the GUID_Dilkie profile section, 
//						   -- Get the existing security property if any, create the security 
//							  property blob and set the profile section's security property using the same.						
// Invoked by : CertFriendlyName()
//
//  Input :
//	  newVal : BSTR
//			BYTE string containing the PKCS7 certificate chain blob.
//	  hCertStore : HCERTSTORE
//			Handle to the "MY" certificate store
//	  pbUserCertificate : PBYTE
//			User certificate Blob
//	  cbUserCertificate : DWORD
//			Size of user certificate blob passed
//  Returns :
//    S_OK, MAPI Error Codes
/*****************************************************************************/

HRESULT CProfAdmin::AssignCertToProfile(BSTR newVal, HCERTSTORE hCertStore, PBYTE pbUserCertificate, DWORD cbUserCertificate)
{
	// Initialise the return value
	HRESULT hr = S_OK;

	// From the newVal passed get the userCertificate details
	BYTE			pbSecBlob[MAX_BUF_SIZE]; // Buffer to hold Security Property Blob
	ULONG			cbSecBlob = 0;	// Size of Security Property Blob

	// MAPI Variables
	LPPROFADMIN			lpProfAdmin = NULL;
	LPSERVICEADMIN		lpServiceAdmin = NULL;
	LPPROFSECT			lpProfSectDilkie = NULL; 

	// Variable to store the current profile selected
	char *cstrProfileName;

	// Variables required to get the existing security property
	SPropValue     *pvalPropArray      = NULL;
	ULONG           ul;
    SPropTagArray   propTagArray      = { 1,{ PR_SECURITY_PROFILES } };
	ULONG ulFlags = 0;

	//Variables required to set the security property
	SPropValue SecProp;
	LPSPropValue lpSecProp = &SecProp;
	SBinary sbCert;

	LPSPropProblemArray lppProblems ; 

	// Open MAPI profile using IProfAdmin interface.
	// Get IProfAdmin interface pointer.
	
    if ( FAILED ( hr = MAPIAdminProfiles ( 0L, &lpProfAdmin ) ) )
    {
	    #ifdef	_VS_LOG_MSG_
	 	    VSGSE_Log(FALSE,L"AssignCertToProfile:MAPIAdminProfiles:Error Code : 0x%08X",hr);
	    #endif

		goto Quit;
    }

	// Check if the global variable to contain profile name is populated
	if(ghbstrCurrentProfile.length() <= 0)
	{
		// No its not, get the value from the exchange directory.
		GetAttributes();
		if(ghbstrCurrentProfile.length() <= 0)
		{
			goto Quit;
		}
	}

	// Get IMsgServiceAdmin interface pointer.
	cstrProfileName = (char *)malloc((ghbstrCurrentProfile.length())*2);

	wcstombs((char *)cstrProfileName, (wchar_t *)ghbstrCurrentProfile, (ghbstrCurrentProfile.length())*2);

	hr = lpProfAdmin -> AdminServices(cstrProfileName, NULL, NULL, 0, &lpServiceAdmin);
	if(FAILED(hr))
	{
		#ifdef	_VS_LOG_MSG_
		VSGSE_Log(FALSE,L"AssignCertToProfile:pProfAdmin -> AdminServices:Error Code : 0x%08X",hr);
		#endif

		goto Quit;
	}

	// Open GUID_Dilkie profile section, security settings are stored here.
	if ( FAILED ( hr = lpServiceAdmin -> OpenProfileSection (
                              (LPMAPIUID)DILKIE_MAPIUID,
                              NULL,
                              MAPI_MODIFY,
                              &lpProfSectDilkie ) ) )
	{
	    #ifdef	_VS_LOG_MSG_
			VSGSE_Log(FALSE,L"AssignCertToProfile:pSvcAdmin -> OpenProfileSection:Error Code : 0x%08X",hr);
		#endif
        
		goto Quit;
	}

	// Get the security setting if already present.
	// This is important to preserve the current Signing certificate setting if only Encryption 
	// certificate is requested and vice-versa.
	if (FAILED(hr = lpProfSectDilkie->GetProps(&propTagArray, ulFlags, &ul, &pvalPropArray)))
	{
	    #ifdef	_VS_LOG_MSG_
			VSGSE_Log(FALSE,L"AssignCertToProfile:pDilkieProfSect->GetProps:Error Code : 0x%08X",hr);
		#endif

		goto Quit;
	}

	memset(pbSecBlob, 0x00, MAX_BUF_SIZE);

	// Check if cValues is valid
	if (pvalPropArray->Value.MVbin.cValues == 1)
	{
		// There is some value already bieng set, Get that value to update.
		memcpy(pbSecBlob, pvalPropArray->Value.MVbin.lpbin[0].lpb, pvalPropArray->Value.MVbin.lpbin[0].cb);
		cbSecBlob = pvalPropArray->Value.MVbin.lpbin[0].cb;
	}
	
	// Create Blob to hold security settings.
	// Get certificate Hashes, ASN1 encoded SMIME capabilities BLOB and certificate usage.
	hr = CreateSecurityBlob (newVal, hCertStore, pbSecBlob, &cbSecBlob, pbUserCertificate, cbUserCertificate);
	if (hr != S_OK)
	{
		#ifdef	_VS_LOG_MSG_
			VSGSE_Log(FALSE,L"AssignCertToProfile:CreateSecurityBlob:Error Code : 0x%08X",hr);
		#endif

		goto Quit;
	}

	// If there is no property to be set exit
	if (cbSecBlob == 0)
	{
		goto Quit;

	}

	// Create the security property structure using the Security Blob.
	SecProp.ulPropTag = PR_SECURITY_PROFILES;
	SecProp.Value.MVbin.cValues = 1;
	SecProp.Value.MVbin.lpbin = &sbCert;
	SecProp.Value.MVbin.lpbin[0].cb = cbSecBlob;
	SecProp.Value.MVbin.lpbin[0].lpb = (unsigned char *)pbSecBlob;
	
	// Set the property
	if (FAILED(hr = lpProfSectDilkie->SetProps(1, lpSecProp, &lppProblems)))
	{
		#ifdef	_VS_LOG_MSG_
			VSGSE_Log(FALSE,L"AssignCertToProfile:lpProfSectDilkie->SetProps:Error Code : 0x%08X",hr);
		#endif

		goto Quit;
	}

	// Free before returning. No memory leaks please!

Quit:
	if(lpProfSectDilkie)
	{
        lpProfSectDilkie -> Release ( );
        lpProfSectDilkie = NULL;
	}

    if ( lpServiceAdmin )
    {
        lpServiceAdmin -> Release ( );
        lpServiceAdmin = NULL;
    }

    if ( lpProfAdmin )
    {
        lpProfAdmin -> Release ( );
        lpProfAdmin = NULL;
    } 
	
	return S_OK;
}

/*****************************************************************************/
// CreateSecurityBlob() : Creates a BLOB holding the security property to be set.
//						  If only Signing certificate is to be set then the existing 
//						  encryption certificate property is preserved and vice versa
//					      -- Gets the certificate context and checks that certificate 
//							 is present in the certificate store.
//						  -- Gets the certificate usage whether Signing, Encryption or both.
//					      -- Create Blob to hold security settings. Preserve the certificate
//							 hashes for signing and encryption certificate from the already 
//						     present values according to the certificate usage and value of 
//						     nSetDefaultCertFlag.
//						     
//
// Invoked by : AssignCertToProfile()
//
//  Input :
//	  newVal : BSTR
//			BYTE string containing the PKCS7 certificate chain blob.
//	  hCertStore : HCERTSTORE
//			Handle to the "MY" certificate store
//	  pbUserCertificate : PBYTE
//			User certificate Blob
//	  cbUserCertificate : DWORD
//			Size of user certificate blob passed
//
//	Input/Output :
//	  lpbSecBlob : BYTE *
//			While input contains the current value of property retrieved from the property
//			section if any. On output it contains the value of new/updated security property.
//	  cbSecBlob : ULONG *
//			Contains the size of input/output lpbSecBlob. If there is no security profile set
//			then this value will be zero.
//
//  Returns :
//    S_OK, MAPI Error Codes
/*****************************************************************************/

HRESULT CProfAdmin::CreateSecurityBlob(BSTR newVal, HCERTSTORE hCertStore, BYTE *lpbSecBlob, ULONG *cbSecBlob, PBYTE pbUserCertificate, DWORD cbUserCertificate)
{
	HRESULT hr = S_OK;   // stores return value from various function calls
	void*	lpbHash = NULL; // stores the hash value of the certificate.
	DWORD   cbHash;	// length of the hash value above
	PCCERT_CONTEXT  pSecBlobCert = NULL;
	PCCERT_CONTEXT	pSearchCert = NULL ;

	// Variables used for loop counter
	int iCount;		
	ULONG iarrCounter = -1;

	// Variable to retrieve the SMIME Capability Blob
	USHORT cbSMIMECapabilityBlobSize = MAX_BUF_SIZE;		// Specify the maximum buffer size available to store the data

	// Variables to retrieve the Intended Certificate usage
	BOOL bUsage;
	BYTE pbUsage;
	DWORD dwBytes = 1;
	FRDLYNAMETYPE eType;

	// Get the certificate context
	if ((pSearchCert = CertCreateCertificateContext(
								X509_ASN_ENCODING, 
								pbUserCertificate,			
								cbUserCertificate)) == NULL )
	{
		_ShowErrorMessage(GetLastError(), "CreateSecurityBlob : CertCreateCertificateContext falied") ;
		goto Quit;
	}
		
	// Check if the certificate is present in the certificate store. 
	// Search by public key to find the certificate.
	if ( (pSecBlobCert = CertFindCertificateInStore(
				  hCertStore,				     // Store handle
				  MY_ENCODING_TYPE,              // Encoding type
				  0,                             // Not used
				  CERT_FIND_PUBLIC_KEY,            // Find type
				  &pSearchCert->pCertInfo->SubjectPublicKeyInfo,					 // Name string
				  NULL)) == NULL )               // Previous context
	{
		_ShowErrorMessage(GetLastError(), "CreateSecurityBlob : CertFindCertificateInStore for certificate data passed falied");
		goto Quit;
	}

	// Free the certificate context created for searching
	if (pSearchCert)
	{
		CertFreeCertificateContext(pSearchCert) ;
		pSearchCert = NULL;
	}

	// Get the intended certificate usage - Signing, Encryption or Both.

	bUsage = CertGetIntendedKeyUsage(
		X509_ASN_ENCODING | PKCS_7_ASN_ENCODING,
		pSecBlobCert->pCertInfo,
		&pbUsage,
		dwBytes);

	if(bUsage)
	{
		//CERT_DATA_ENCIPHERMENT_KEY_USAGE for EFS
		if(pbUsage == (CERT_DIGITAL_SIGNATURE_KEY_USAGE | CERT_KEY_ENCIPHERMENT_KEY_USAGE) || pbUsage == (CERT_DIGITAL_SIGNATURE_KEY_USAGE | CERT_KEY_ENCIPHERMENT_KEY_USAGE | CERT_DATA_ENCIPHERMENT_KEY_USAGE) )
		{
			eType = BOTH;
		}
		else if(pbUsage == CERT_DIGITAL_SIGNATURE_KEY_USAGE || pbUsage == (CERT_DIGITAL_SIGNATURE_KEY_USAGE | CERT_DATA_ENCIPHERMENT_KEY_USAGE))
		{
			eType = SIGN;
			// Certificate is for signing only while flag specifies 
			// only encryption certificate to be set as default. Nothing to be done
			if (nSetDefaultCertFlag == SET_DEFAULT_FOR_ENCRYPT)
			{
				*cbSecBlob = 0; // No data written in the Security property blob
				goto Quit;
			}
		}
		else if(pbUsage == CERT_KEY_ENCIPHERMENT_KEY_USAGE || pbUsage == (CERT_KEY_ENCIPHERMENT_KEY_USAGE | CERT_DATA_ENCIPHERMENT_KEY_USAGE))
		{
			eType = ENCRYPT;
			// Certificate is for encryption only while flag specifies 
			// only Signing certificate to be set as default. Nothing to be done
			if (nSetDefaultCertFlag == SET_DEFAULT_FOR_SIGN)
			{
				*cbSecBlob = 0; // No data written in the Security property blob
				goto Quit;
			}
		}
	}

	// Create Sec Blob to hold security settings. A blob is made up of number of properties
	// each property has three fields tag, length and data. The property are all stored in 
	// one continuous stream. Refer "http://support.microsoft.com/?kbid=312900" for details.
	
	// ------ Create Security Property structures.
	BYTE pbData[MAX_BUF_SIZE];			// Temporary buffer used for creating the properties
	memset(pbData, 0x00, MAX_BUF_SIZE); // Initialize the buffer

	SEC_PROP_BLOB arrSecProp[PROP_ARRAY_SIZE];	// Array to store the properties.

	//------------ PR_CERT_PROP_VERSION property -----------------------
	// Reserved property, always 1
	arrSecProp[0].tag = PR_CERT_PROP_VERSION;
	arrSecProp[0].length = 0x0008;	// Length is 8 bytes including tag and len fields.
	
	pbData[0] = 0x1;				// This is a reserved property value is always 1.
	
	memset(arrSecProp[0].pbdata, 0x00, MAX_BUF_SIZE);
	memcpy(arrSecProp[0].pbdata, pbData, arrSecProp[0].length - 4);


	//------------ PR_CERT_MESSAGE_ENCODING ----------------------------
	// Specifies the type of encoding S/MIME or other. S/MIME = 1.
	arrSecProp[1].tag = PR_CERT_MESSAGE_ENCODING;
	arrSecProp[1].length = 0x0008;

	pbData[0] = 0x1;				// Type of encoding SMIME = 1

	memset(arrSecProp[1].pbdata, 0x00, MAX_BUF_SIZE);
	memcpy(arrSecProp[1].pbdata, pbData, arrSecProp[1].length - 4);


	//------------ PR_CERT_DEFAULTS ------------------------------------
	// Specifies if the certificate is 
	// 0x1	Default certificate for S/MIME
	// 0x2	Default certificate for all formats
	// 0x4	Send certificate with message.
	// 0x7  Set certificate as default and send it along with message as 
	//      well.

	arrSecProp[2].tag = PR_CERT_DEFAULTS;
	arrSecProp[2].length = 0x0008;

	pbData[0] = 0x7; // Default certificate for all format.
	
	memset(arrSecProp[2].pbdata, 0x00, MAX_BUF_SIZE);
	memcpy(arrSecProp[2].pbdata, pbData, arrSecProp[2].length - 4);


	//------------ PR_CERT_DISPLAY_NAME_A ------------------------------
	// Display name for the created security profile.
	arrSecProp[3].tag = PR_CERT_DISPLAY_NAME_A;
	arrSecProp[3].length = sizeof(SETTING_DISPLAY_NAME) + 4;

	memset(pbData, 0x00, MAX_BUF_SIZE);
	memcpy(pbData, (BYTE*)SETTING_DISPLAY_NAME, arrSecProp[3].length - 4);
		
	memset(arrSecProp[3].pbdata, 0x00, MAX_BUF_SIZE);
	memcpy(arrSecProp[3].pbdata, pbData, arrSecProp[3].length - 4);

	//----------- Get the Certificate Hash Data ------------------------

	// Get certificate hash data using two calls to CertGetCertificateContextProperty

	// First get the size of buffer to be allocated
	if(!CertGetCertificateContextProperty(
		   pSecBlobCert,
		   CERT_HASH_PROP_ID,
		   NULL,
		   &cbHash))
	{
		_ShowErrorMessage(GetLastError(), "CreateSecurityBlob : CertGetCertificateContextProperty falied") ;
		goto Quit;
	}

	// Allocate the buffer to hold hash blob
	if (!(lpbHash = (void*)malloc(cbHash)))
	{
		_ShowErrorMessage(GetLastError(), "CreateSecurityBlob : malloc for Hash Blob falied") ;
		goto Quit;
	}

	// Now get actual value in the buffer
	if(!CertGetCertificateContextProperty(
		   pSecBlobCert,
		   CERT_HASH_PROP_ID,
		   lpbHash,
		   &cbHash))
	{
		_ShowErrorMessage(GetLastError(), "CreateSecurityBlob : CertGetCertificateContextProperty falied") ;
		goto Quit;
	}

	//----------- PR_CERT_KEYEX_SHA1_HASH -----------------------------------------
	// Binary Hash for Ecryption certificate.
	arrSecProp[4].tag = PR_CERT_KEYEX_SHA1_HASH;
	arrSecProp[4].length = cbHash + 4;
	
	memset(pbData, 0x00, MAX_BUF_SIZE);
	memcpy(pbData, (BYTE*)lpbHash, cbHash);
	
	memset(arrSecProp[4].pbdata, 0x00, MAX_BUF_SIZE);
	memcpy(arrSecProp[4].pbdata, pbData, arrSecProp[4].length - 4);

	//------------ PR_CERT_SIGN_SHA1_HASH -----------------------------------------
	// Binary Hash for Signing Certificate
	arrSecProp[5].tag = PR_CERT_SIGN_SHA1_HASH;
	arrSecProp[5].length = cbHash + 4;
	
	memset(pbData, 0x00, MAX_BUF_SIZE);
	memcpy(pbData, (BYTE*)lpbHash, cbHash);
		
	memset(arrSecProp[5].pbdata, 0x00, MAX_BUF_SIZE);
	memcpy(arrSecProp[5].pbdata, pbData, arrSecProp[5].length - 4);

	//------------ PR_CERT_ASYMETRIC_CAPS -----------------------------------------
	// ASN1 encoded S/MIME capabilities blob. This contains a list of all the 
	// algorithm supported by the Cryptographic service provider to which this 
	// certificate belong.
	arrSecProp[6].tag = PR_CERT_ASYMETRIC_CAPS;

	// Get the Sign Attribute method to get the SMIME capability blob.
	ISignAttributes            *olSgnAtr;
	
	// Create instance of SignAttributes class.
	hr = CoCreateInstance(CLSID_SignAttributes, NULL, CLSCTX_ALL,
										IID_ISignAttributes, (void **)&olSgnAtr); 
	if(hr!=S_OK)
	{
		goto Quit;
	}

	// Initialise the component with certificate details
	hr = olSgnAtr->put_userCertificate(newVal);
	if(hr!=S_OK)
	{		
		goto Quit;
	}

	// First call to get the buffer size
	memset(pbData, 0x00, MAX_BUF_SIZE);		// Initialise the buffer

	hr=olSgnAtr->get_SMIMECapabilityBlob(&cbSMIMECapabilityBlobSize, pbData);
	if(hr != S_OK)
	{
		goto Quit;
	}

	if (cbSMIMECapabilityBlobSize == 0)
	{
		goto Quit;
	}

	arrSecProp[6].length = cbSMIMECapabilityBlobSize + 4;
	memset(arrSecProp[6].pbdata, 0x00, MAX_BUF_SIZE );
	memcpy(arrSecProp[6].pbdata, pbData, arrSecProp[6].length -4);

	// All the properties are stored in one continuous byte stream.
	// so now serialize the data. 
	
	// Allocate a byte string to store the buffer.
	memset(pbData, 0x00, MAX_BUF_SIZE);
	

	for (iCount = 0;iCount < PROP_ARRAY_SIZE; iCount++)
	{
		// If certificate is encryption only then dont include the current signing property and vise versa
		// Get the Signing property from old Property blob if present.
		if ((iCount == SIGN_HASH_PROPERY) && (eType == ENCRYPT))
		{
			// If there was some old property value present
			if (*cbSecBlob == 0)
			{
				continue;
			}
			else
			{
				// Get the signing certificate hash from the current security property.
				hr = GetCertHash(SIGN, lpbSecBlob, *cbSecBlob, &arrSecProp[iCount]);
				// If error or no hash value found
				if ((hr != S_OK) || (arrSecProp[iCount].length == 0))
				{
					// The certificate hash for Signing certificate not found in the current security property.
					hr = S_OK;
					continue;
				}
			}
		}

		// Same as above but retrieves the existing encryption certificate hash, if any.
		if ((iCount == KEYEX_HASH_PROPERY) && (eType == SIGN)) 
		{
			// check if there was some old property value present
			if (*cbSecBlob == 0)
			{
				continue;
			}
			else
			{
				// Get the encryption certificate hash from the current security property.
				hr = GetCertHash(ENCRYPT, lpbSecBlob, *cbSecBlob, &arrSecProp[iCount]);
				// If error or no hash value found
				if ((hr != S_OK) || (arrSecProp[iCount].length == 0))
				{
					// The certificate hash for Encryption certificate not found in the current security property.
					hr = S_OK;
					continue;			
				}
			}
		}

		// Data has most significant byte first while the format we 
		// want has least significant byte first so reverse byte order first.

		pbData[++iarrCounter] = (arrSecProp[iCount].tag & 0x00FF);
		pbData[++iarrCounter] = (arrSecProp[iCount].tag & 0xFF00) >> 8;

		pbData[++iarrCounter] = (arrSecProp[iCount].length & 0x00FF);
		pbData[++iarrCounter] = (arrSecProp[iCount].length & 0xFF00) >> 8;
		
		memcpy(pbData + (iarrCounter +1), arrSecProp[iCount].pbdata, arrSecProp[iCount].length - 4);
		iarrCounter+= (arrSecProp[iCount].length - 4);
	}

	// Update the Sec property blob values
	memcpy (lpbSecBlob, pbData, iarrCounter);
	*cbSecBlob = iarrCounter;

Quit : 

	if (pSecBlobCert)
	{
		CertFreeCertificateContext(pSecBlobCert) ;
		pSecBlobCert = NULL;

	}

	if (pSearchCert)
	{
		CertFreeCertificateContext(pSearchCert) ;
		pSearchCert = NULL;
	}

	return hr;
}

/*****************************************************************************/
// GetCertHash() : It takes the currently available Security property blob and extracts
//				   signing or encryption certificate hash property on demand.
//
// Invoked by : CreateSecurityBlob()
//
//  Input :
//	  pType : FRDLYNAMETYPE
//			Specifies whether signing or encryption certificate hash value is required.
//	  lpbSecBlob : BYTE *
//			Blob containing the security property
//	  cbSecBlob : ULONG
//			Length of lpbSecBlob
//
//	Output :
//	  SecPropBlob : SEC_PROP_BLOB *
//			Security property array to store the output security property
//
//  Returns :
//    S_OK, MAPI Error Codes
/*****************************************************************************/

HRESULT CProfAdmin::GetCertHash(FRDLYNAMETYPE pType, BYTE *lpbSecBlob, ULONG cbSecBlob, SEC_PROP_BLOB *SecPropBlob)
{
	// Parse the lpbSecBlob to retrieve the hash for certificate indicated by pType.
	USHORT ntag;
	USHORT nlen;

	// Initialize the length buffer.
	SecPropBlob->length = 0;
	
	for (int iCount = 0; iCount < cbSecBlob; iCount++)
	{
		ntag = lpbSecBlob[iCount + 1];
		ntag = ntag << 8;
		ntag = ntag + lpbSecBlob[iCount];

		nlen = lpbSecBlob[iCount + 3];
		nlen = nlen << 8;
		nlen = nlen + lpbSecBlob[iCount + 2];

		// If Signing hash is asked for and this is Signing hash
		// or encryption hash is asked for and this is encryption hash
		if (((pType == SIGN) && (ntag == PR_CERT_SIGN_SHA1_HASH))
			|| ((pType == ENCRYPT) && (ntag == PR_CERT_KEYEX_SHA1_HASH)))
		{
			// This is the hash property we are asked for.
			// Populate the SEC_PROP_BLOB structure.
			SecPropBlob->tag = ntag;
			SecPropBlob->length = nlen;
			memcpy (SecPropBlob->pbdata, lpbSecBlob + iCount + 4, nlen - 4);
			return S_OK;
		}
		// this is not the hash property, skip len bytes in the buffer.
		iCount = iCount + nlen - 1;  
	}

	return S_FALSE;
}
// End Add : Infosys : CR27993


// Start Add : Infosys : CR21346
/*****************************************************************************/
// GetUserFirstName() : Gets the value of user first name "givenName" from 
//						the LDAP directory.
//
// Invoked by : CVSGSE::get_FirstName()
//
//	Output :
//	  o_pbstrFirstName : _bstr_t *
//			User first name as retrieved from LDAP directory
//
//  Returns :
//    S_OK, Error Code
/*****************************************************************************/

HRESULT CProfAdmin::GetUserFirstName(_bstr_t *o_pbstrFirstName)
{
	// If the data from LDAP is already retrieved then no need to make the call again
	if(!gLDAPAccess)
	{
		// Retrieve the data from LDAP directory and populate mailbox property variables
		hr=GetAttributes();
		if(hr!=0)
		{
			return hr;
		}
	}
	
	// Value found then update the output structure
	if (gMailBoxInfo.bstrFirstName.length() > 0)
	{
		*o_pbstrFirstName = (wchar_t*)gMailBoxInfo.bstrFirstName;
	}

	return hr;
}

/*****************************************************************************/
// GetUserLastName() : Gets the value of user Last name "sn" from 
//						the LDAP directory.
//
// Invoked by : CVSGSE::get_LastName()
//
//	Output :
//	  o_pbstrLastName : _bstr_t *
//			User Last name as retrieved from LDAP directory
//
//  Returns :
//    S_OK, Error Code
/*****************************************************************************/

HRESULT CProfAdmin::GetUserLastName(_bstr_t *o_pbstrLastName)
{
	// If the data from LDAP is already retrieved then no need to make the call again
	if(!gLDAPAccess)
	{
		// Retrieve the data from LDAP directory and populate mailbox property variables
		hr=GetAttributes();
		if(hr!=0)
		{
			return hr;
		}
	}
	
	// Value found then update the output structure
	if (gMailBoxInfo.bstrLastName.length() > 0)
	{
		*o_pbstrLastName = (wchar_t*)gMailBoxInfo.bstrLastName;
	}

	return hr;
}
// End Add : Infosys : CR21346

