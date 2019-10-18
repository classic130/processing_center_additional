<!-- Copyright (c) 1993-2001 Tumbleweed Communications Corp. All Rights Reserved. -->
<!-- File name: SGMS_VSSCChangePasswdInclude.tpl -->

<%@include file="SGMS_VSSCErrorFormInclude.tpl" %>
<%@include file="SGMS_OnSiteHostConfig.tpl" %>
<%@include file="SGMS_VSSCDownloadInclude.tpl" %>
<%@include file="TW_HelperSession.tpl" %>
	  
<SCRIPT LANGUAGE="JavaScript">

function RedirectToLogin()
{
	self.location = "<%=HostNameSSL;%>";
}

</script>

	 <% if( tw.request.userAgentVendor == "microsoft" ) { %>
		<SCRIPT Language="VBScript">

		  'This function will call the close methods of both the objects
		  Function CloseObjects (ErrorCode, Operation, WinErrorCode)
			On Error Resume Next
			VSSC.IVSSCPTA.Close
			if ( ErrorCode <> 0 ) then
			   Call SetErrorInfoMS("PTA Change Password","00000001",ErrorCode,"<%=ChangePasswordStatus;%>",0)
			   Exit Function
			end if
		  End Function
	
		 Sub VSSCInitialize
			On Error Resume Next

			VSSC_INITIALIZED = &h80003001

			VSSC.Initialize 0, 0, AppStatus
			If (err.number <> 0 and err.number <> VSSC_INITIALIZED) Then
				Call CloseObjects(Hex(err.number), "",0)
				Exit Sub	
			End if


			'Set the list of PTA versions supported by VSSC		
			DIFFERENT_PTAVER = &h8000300F
			Dim SupportedVer 
			Dim SupportedText
			Dim InstalledVer
				
			SupportedVer = "<%=PTASupportedVer;%>"
			SupportedText = "  Supported Version = "

			On Error Resume Next
			VSSC.SupportedPTAVer = SupportedVer
			If( err.number = DIFFERENT_PTAVER) then
				'InstalledVer = VSSC.InstalledPTAVer
				Call CloseObjects(Hex(err.number), "",0)
				Exit Sub	
			Else If (err.number) then
				Call CloseObjects(Hex(err.number), "",0)
				Exit Sub
			End If
			End If
		  End Sub


		Sub changePassword()
			  Dim strCertStore 
			  Dim strAppCtxtName
			  Dim strIssuerDN
			  Dim strChooseProfileText 
			  Dim strChooseProfileTitle 
			  Dim strChangepwdWizardTitle
			  Dim strChangepwdTitle
			  Dim strChangepwdText
			  Dim strChangepwdHelpUrl
			  Dim passwordQuality
			  Dim passwordLength
			  Dim saveLocal
			  Dim strClientInfo
			  Dim strClientInfoSig
			  Dim strAppLogoUrl

			  Dim IVSProfMgmt
    		  Dim IVSUIPrefs
			  Dim IVSCertPrefs
			  Dim IVSSrchCrit
			  Dim IVSSelectedID
			  Dim IVSRoamPrefs

			  strCertStore = "verisign"
			  strAppCtxtName = "<%=AppContextName; %>"
			  strIssuerDN = "O=VeriSign; OU=VeriSign Class 2 OnSite Individual CA"
			  
			  
	          strLoginWizardTitle = "SGMS Authentication"

			  strChooseProfileTitle = "Open Profile"
			  strChooseProfileText = "Choose the profile whose password is to be changed."
			  strChangepwdWizardTitle = "Change Password"
			  strChangepwdTitle = "Change profile password"
			  strChangepwdText = "Enter your new password to change your profile password."  
			  passwordQuality = "16384"
			  passwordLength = "6"
			  saveLocal = "disabled"
			 
			  strClientInfo = "<%=strClientInfo;%>"
	          strClientInfoSig = "<%=strClientInfoSig;%>"

			  strAppLogoUrl = "<%=OnSiteHost;%>/SGMSAppLogo.BMP"

			 
			   Dim helpHostName
			   helpHostName = "<%=OnSiteHost;%>"
			 

			   strChangepwdHelpUrl = helpHostName & "/VSApps/client/help/tasks/ptachangepwd.htm"
			

				 Call VSSCInitialize

				 if bErrorPresent = 1 then
					exit sub
				 end if


				 On Error Resume Next
				 Set IVSPTA=VSSC.IVSSCPTA
				 If ( err.number <> 0 ) then
					Call CloseObjects(Hex(err.number), "", 0)
					Exit Sub
				 End If

				 On Error Resume Next
				 Set IVSProfMgmt = IVSPTA.IVSProfMgmt
				 If (err.number <> 0 ) Then
					 Call CloseObjects(Hex(err.number), "", 0)
				 End if

				 On Error Resume Next
				 Set IVSUIPrefs = IVSPTA.IVSUIPrefs
				 If ( err.number <> 0 ) then
					Call CloseObjects(Hex(err.number), "", 0)
					Exit Sub
				 End If

				 On Error Resume Next
				 Set IVSCertPrefs = IVSPTA.IVSCertPrefs
				 If ( err.number <> 0 ) then
					Call CloseObjects(Hex(err.number), "", 0)
					Exit Sub
				 End If

				 On Error Resume Next
				 Set IVSSrchCrit = IVSPTA.IVSSrchCrit
				 If ( err.number <> 0 ) then
					Call CloseObjects(Hex(err.number), "", 0)
					Exit Sub
				 End If

				 On Error Resume Next
				 Set IVSSelectedID = IVSPTA.IVSSelectedDigID
				 If ( err.number <> 0 ) then
					Call CloseObjects(Hex(err.number), "", 0)
					Exit Sub
				 End If

				 On Error Resume Next
				 Set IVSRoamPrefs = IVSPTA.IVSRoamPrefs
				 If ( err.number <> 0 ) then
					Call CloseObjects(Hex(err.number), "", 0)
					Exit Sub
				 End If
 
				 
				 On Error Resume Next
				 IVSPTA.Initialize strAppCtxtName,0
				 If ( err.number <> 0 ) then
					 Call CloseObjects(Hex(err.number), "", 0)      
					 Exit Sub
				 End If

				 On Error Resume Next
				 If (Len(strChooseProfileTitle) <> 0) then
					 IVSUIPrefs.OpenProf_Title = strChooseProfileTitle
					 If ( err.number <> 0 ) then
						Call CloseObjects(Hex(err.number), "", 0)
						Exit Sub
					End If
				 End If

				 On Error Resume Next
				 If (Len(strChooseProfileText) <> 0) then
					IVSUIPrefs.OpenProf_Text = strChooseProfileText
					If ( err.number <> 0 ) then
						Call CloseObjects(Hex(err.number), "", 0)
						Exit Sub
					End If
				 End If
				 
				 On Error Resume Next
				 If (Len(strChangepwdWizardTitle) <> 0) then
					 IVSUIPrefs.LgnDlg_Title = strChangepwdWizardTitle
					 If ( err.number <> 0 ) then
						Call CloseObjects(Hex(err.number), "", 0)
						Exit Sub
					End If
				 End If
				 
				 On Error Resume Next
				 If (Len(strChangepwdTitle) <> 0) then
					 IVSUIPrefs.ChangePasswd_Title = strChangepwdTitle
					 If ( err.number <> 0 ) then
						Call CloseObjects(Hex(err.number), "", 0)
						Exit Sub
					End If
				 End If
					
				 On Error Resume Next
				 If (Len(strChangepwdText) <> 0) then
					 IVSUIPrefs.ChangePasswd_Text = strChangepwdText
					 If ( err.number <> 0 ) then
						Call CloseObjects(Hex(err.number), "", 0)
						Exit Sub
					End If
				 End If		     
					
				 On Error Resume Next
				 If (Len(strChangepwdHelpUrl) <> 0) then
					 IVSUIPrefs.ChangePasswd_HelpUrl = strChangepwdHelpUrl
					 If ( err.number <> 0 ) then
						Call CloseObjects(Hex(err.number), "", 0)
						Exit Sub
					End If
				 End If		     		
  
		  		 E_CARDALREADYOPEN = &h8000102F

				 'Flags
				 OPENPROF_OPEN_ONLY = CInt(529)
				 On Error Resume Next
				 IVSProfMgmt.OpenProfFlags = OPENPROF_OPEN_ONLY
				 If ((err.number <> 0) And (err.number <> E_CARDALREADYOPEN) ) Then
					Call CloseObjects(Hex(err.number), "", 0)
					Exit Sub
				 End If


  				 ' set the password preferences.
				 On Error Resume Next
				 if ( passwordQuality <> "") then
				   IVSProfMgmt.PasswdQuality = CInt (passwordQuality)
				   If ((err.number <> 0) And (err.number <> E_CARDALREADYOPEN) ) Then
							  Call CloseObjects(Hex(err.number), "", 0)
					  Exit Sub 
				   End If
				 End If 

				 On Error Resume Next
				 if ( passwordLength <> "") then
				   IVSProfMgmt.PasswdLength = CInt (passwordLength)
				   If ((err.number <> 0) And (err.number <> E_CARDALREADYOPEN) ) Then
							  Call CloseObjects(Hex(err.number), "", 0)
					  Exit Sub 
				   End If
				 End If     
 

				 On Error Resume Next
				 IVSProfMgmt.IsUsernameEditable = CBool(0)
				 If (err.number <> 0 ) Then
					Call CloseObjects(Hex(err.number), "",0)
					Exit Sub
				 End If

				 On Error Resume Next
				 If (Len(strAppLogoUrl) <> 0) then
				   IVSUIPrefs.UILogoUrl = strAppLogoUrl
				   If ( err.number <> 0 ) then
					  Call CloseObjects(Hex(err.number), "", 0)
					  Exit Sub
				   End If
				 End If

				
				On Error Resume Next
				IVSRoamPrefs.ClientInfo = strClientInfo
				If ((err.number <> 0) And (err.number <> E_CARDALREADYOPEN) ) Then
				   Call CloseObjects(Hex(err.number), "", 0)
				   Exit Sub 
				End If

				On Error Resume Next
				IVSRoamPrefs.ClientInfoSig = strClientInfoSig
				If ((err.number <> 0) And (err.number <> E_CARDALREADYOPEN) ) Then
				   Call CloseObjects(Hex(err.number), "", 0)
				   Exit Sub 
				End If

			 ' set roaming enabled 
			 On Error Resume Next
			 IVSProfMgmt.RoamProfile = CBool(1) 
			 If ((err.number <> 0) And (err.number <> E_CARDALREADYOPEN) ) Then
				 Call CloseObjects(Hex(err.number), "", 0)
				 Exit Sub 
			 End If


		     VSSC_PTA_CANCEL = &h80001067

						
			 ' call change password
			 On Error Resume Next 
			 IVSProfMgmt.ChangePassword
			 If ( (err.number <> 0) And (err.number <> VSSC_PTA_CANCEL)) then 
				 Call CloseObjects(Hex(err.number), "", 0)
				 Exit Sub
			 End If 
			 If (err.number = VSSC_PTA_CANCEL) then 
				 Call CloseObjects(0, "", 0)
				 Exit Sub
			 End If

			 On Error Resume Next
			 IVSProfMgmt.SaveProfile
			 If ( err.number <> 0 ) then
				 Call CloseObjects(Hex(err.number), "", 0)
				 Exit Sub
			 End If   

			 'On Error Resume Next
			 'IVSProfMgmt.CloseProfile
			 'If ( err.number <> 0 ) then
			 '	 Call CloseObjects(Hex(err.number), "", 0)
			 '	 Exit Sub
			 'End If   

			 If (err.number = 0) Then
				 MsgBox "Your password has been changed successfully."
			 End If 

			 Call CloseObjects(0, "", 0) 

			 End Sub

		</SCRIPT>

	 <% } else { %>
		<SCRIPT LANGUAGE=JavaScript>
		 
		  function ConvertToHexNS (error_code)
		  {
			if (navigator.appName != "Netscape")
				{ return error_code; }

			var javaErrorCode;
			var ErrNumber;

			ERROR_LIMIT = 0x80000000;
			if (error_code >= ERROR_LIMIT) {
			  error_code = error_code - 0x80000000;
			  ErrNumber = new Number(error_code);
			  javaErrorCode = ErrNumber.toString(16);
			  if(error_code <= 0xF) {
			javaErrorCode = "8000000" + javaErrorCode.substring(javaErrorCode.length-1, javaErrorCode.length);
			  }
			  else if (error_code <= 0xFF) {
			javaErrorCode = "800000" + javaErrorCode.substring(javaErrorCode.length-2, javaErrorCode.length);
			  }
			  else if (error_code <= 0xFFF) {
			javaErrorCode = "80000" + javaErrorCode.substring(javaErrorCode.length-3, javaErrorCode.length);
			  }
			  else {
			   javaErrorCode = "8000" + javaErrorCode.substring(javaErrorCode.length-4, javaErrorCode.length);
			  }

			} else {
			  ErrNumber = new Number(error_code);
			  javaErrorCode = ErrNumber.toString(10);
			}
			return javaErrorCode;
		  }


		 function CloseObjects(errCode, Operation, WinErrorCode)
		 {
			RetVal = document.VSSC.PTA_Close ();

			if (errCode != 0) {
			   SetErrorInfoNS("PTA Change Password","00000001",ConvertToHexNS(errCode),"<%=ChangePasswordStatus;%>",0);
			}
			return;
		 }

		 function changePassword()
		 {
			 // the JavaScript variables made available on PTA change password page
			var strCertStore = "verisign";
			var strAppCtxtName = "<%=AppContextName; %>";
			var strCertIssuerDN = "O=VeriSign; OU=VeriSign Class 2 OnSite Individual CA";
			var strLoginWizardTitle = "SGMS Authentication";

			var strChooseProfileTitle = "Open Profile";
			var strChooseProfileText = "Choose the profile whose password is to be changed.";
			var strChangepwdWizardTitle = "Change Password";
			var strChangepwdTitle = "Change profile password";
			var strChangepwdText = "Enter your new password to change your profile password.";
			var passwordQuality = 16384;
			var passwordLength = 6;
			var saveLocal = "disabled";

			var strAppLogoUrl = "<%=OnSiteHost;%>/SGMSAppLogo.BMP";

			var strClientInfo = "<%=strClientInfo;%>";
			var strClientInfoSig = "<%=strClientInfoSig;%>";


 		    var helpHostName = "<%=OnSiteHost;%>";

			var strChangepwdHelpUrl = helpHostName + "/VSApps/client/help/tasks/ptachangepwd.htm"

			var AppStatus = new java.lang.StringBuffer("");

			VSSC_PLUGIN_NOT_INITIALIZED = 0x80003555;
			var count = 1;
			document.VSSC.VSSC_Initialize(0,0, AppStatus);
			while(true)
			{
				ErrorCode=document.VSSC.GetLastError();
				if(ErrorCode == VSSC_PLUGIN_NOT_INITIALIZED)
				{
					document.VSSC.VSSC_Initialize(0,0, AppStatus);
					count ++;
				}
				else
				{
					
					break;
				}

			}
			// Only for Debug, remove this later
			//alert("Times VSSC_Initialize Called = " + count);
			
			VSSC_INITIALIZED = 0x80003001;
			ErrorCode=document.VSSC.GetLastError();
			if(ErrorCode !=0 && ErrorCode != VSSC_INITIALIZED)
			{
				CloseObjects(ErrorCode, "", 0);	
				return ErrorCode;		
			}		

			//Set the list of PTA versions supported by VSSC
			DIFFERENT_PTAVER = 0x8000300F;
			var InstalledVer;
			var SupportedVer = "<%=PTASupportedVer;%>";
			var SupportedText = "  Supported Version = ";
			document.VSSC.set_VSSC_SupportedPTAVer(SupportedVer);
			ErrorCode=document.VSSC.GetLastError();
			
			if(ErrorCode == DIFFERENT_PTAVER)
			{
				//InstalledVer = document.VSSC.get_VSSC_InstalledPTAVer();
				CloseObjects(ErrorCode, "", 0);
				return ErrorCode;	
			}
			else if(ErrorCode)
			{
				CloseObjects(ErrorCode, "", 0);
				return ErrorCode;
			}

			document.VSSC.PTA_Initialize(strAppCtxtName, 0) ;

			if ( (ErrorCode = document.VSSC.GetLastError()) != 0) {
				CloseObjects(ErrorCode, "", 0);
				return ErrorCode;
			}

			// set the UI preferences
			if (strChooseProfileTitle[0] != null){
				document.VSSC.set_UIPrefs_OpenProf_Title(strChooseProfileTitle) ;
				if ( (ErrorCode = document.VSSC.GetLastError()) != 0) {
				   CloseObjects(ErrorCode, "", 0);
				   return ErrorCode;
				}
			}

		   if (strChooseProfileText[0] != null){
			  document.VSSC.set_UIPrefs_OpenProf_Text(strChooseProfileText) ;
			  if ( (ErrorCode = document.VSSC.GetLastError()) != 0) {
				 CloseObjects(ErrorCode, "", 0);
				 return ErrorCode;
			  }
		   }

		   if (strChangepwdWizardTitle[0] != null){
			  document.VSSC.set_UIPrefs_LgnDlg_Title(strChangepwdWizardTitle) ;
			  if ( (ErrorCode = document.VSSC.GetLastError()) != 0) {
				 CloseObjects(ErrorCode, "", 0);
				 return ErrorCode;
			  }
		   }

		   if (strChangepwdTitle[0] != null){
			  document.VSSC.set_UIPrefs_ChangePasswd_Title(strChangepwdTitle) ;
			  if ( (ErrorCode = document.VSSC.GetLastError()) != 0) {
				 CloseObjects(ErrorCode, "", 0);
				 return ErrorCode;
			  }
		   }

		   if (strChangepwdText[0] != null){
			  document.VSSC.set_UIPrefs_ChangePasswd_Text(strChangepwdText) ;
			  if ( (ErrorCode = document.VSSC.GetLastError()) != 0) {
				 CloseObjects(ErrorCode, "", 0);
				 return ErrorCode;
			  }
		   }

		   if (strChangepwdHelpUrl[0] != null){
			  document.VSSC.set_UIPrefs_ChangePasswd_HelpUrl(strChangepwdHelpUrl) ;
			  if ( (ErrorCode = document.VSSC.GetLastError()) != 0) {
				 CloseObjects(ErrorCode, "", 0);
				 return ErrorCode;
			  }
		   }

		   if (strAppLogoUrl[0] != null){
			  document.VSSC.set_UIPrefs_UILogoUrl(strAppLogoUrl) ;
			  if ( (ErrorCode = document.VSSC.GetLastError()) != 0) {
				 CloseObjects(ErrorCode, "", 0);
				 return ErrorCode;
			  }
		   }

		   E_CARDALREADYOPEN = 0x8000102F;

		   // flags
		   OPENPROF_OPEN_ONLY = 529;
		   document.VSSC.set_ProfMgmt_OpenProfFlags(OPENPROF_OPEN_ONLY) ;
		   ErrorCode = document.VSSC.GetLastError();
		   if ( ErrorCode  != 0 && ErrorCode  != E_CARDALREADYOPEN ) {
			  CloseObjects(ErrorCode, "", 0);
			  return ErrorCode;
		   }

  			// set the password preferences.
		   document.VSSC.set_ProfMgmt_PasswdQuality(passwordQuality) ;
		   ErrorCode = document.VSSC.GetLastError();
		   if ( ErrorCode  != 0 && ErrorCode  != E_CARDALREADYOPEN ) {
			  CloseObjects(ErrorCode, "", 0);
			  return ErrorCode;
		   }

		   document.VSSC.set_ProfMgmt_PasswdLength(passwordLength) ;
		   ErrorCode = document.VSSC.GetLastError();
		   if ( ErrorCode  != 0 && ErrorCode  != E_CARDALREADYOPEN ) {
			  CloseObjects(ErrorCode, "", 0);
			  return ErrorCode;
		   }

		   document.VSSC.set_ProfMgmt_IsUsernameEditable(false);;
		   if ( (ErrorCode = document.VSSC.GetLastError()) != 0 ) {
				CloseObjects(ErrorCode, "", 0);
				return ErrorCode;
		   }

		   
		   document.VSSC.set_RoamPrefs_ClientInfo(strClientInfo);
		   if ( ((ErrorCode = document.VSSC.GetLastError()) != 0 ) && (ErrorCode != E_CARDALREADYOPEN ) ) {
			  CloseObjects(ErrorCode, "", 0);
			  return ErrorCode;
		   }

		   document.VSSC.set_RoamPrefs_ClientInfoSig(strClientInfoSig);
		   if ( ((ErrorCode = document.VSSC.GetLastError()) != 0 ) && (ErrorCode != E_CARDALREADYOPEN ) ) {
			  CloseObjects(ErrorCode, "", 0);
			  return ErrorCode;
		   }

		   document.VSSC.set_ProfMgmt_RoamProfile(true);
		   if ( ((ErrorCode = document.VSSC.GetLastError()) != 0 ) && (ErrorCode != E_CARDALREADYOPEN ) ) {
			  CloseObjects(ErrorCode, "", 0);
			  return ErrorCode;
		   }

		   VSSC_PTA_CANCEL = 0x80001067;

		   document.VSSC.ProfMgmt_ChangePassword() ;
		   if ( ((ErrorCode = document.VSSC.GetLastError()) != 0 ) && (ErrorCode != VSSC_PTA_CANCEL ) ) {
			  CloseObjects(ErrorCode, "", 0);
			  return ErrorCode;
		   }

		   if ( ErrorCode  == VSSC_PTA_CANCEL) {
			  CloseObjects(0, "", 0);
			  return ErrorCode;
		   }

		   document.VSSC.ProfMgmt_SaveProfile() ;
		   if ( (ErrorCode = document.VSSC.GetLastError()) != 0) {
			  CloseObjects(ErrorCode, "", 0);
			  return ErrorCode;
		   }
/*
		   document.VSSC.ProfMgmt_CloseProfile();
		   if ( (ErrorCode = document.VSSC.GetLastError()) != 0) {
				CloseObjects(ErrorCode, "", 0);
				return ErrorCode;
		   }
*/
		   if ( ErrorCode == 0 )
				alert("Your password has been changed successfully.");

		   CloseObjects(0, "", 0);

		   return true;
		 }
		
		</SCRIPT>

	 <% } %>

