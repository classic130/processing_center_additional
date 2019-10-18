<!-- Copyright (c) 1993-2001 Tumbleweed Communications Corp. All Rights Reserved. -->
<!-- File name: TW_PtaScriptShared.tpl -->
<%@include file="TW_HelperHttpHosts.tpl" %>
<%@include file="SGMS_OnSiteHostConfig.tpl" %>
<%@include file="SGMS_VSSCErrorFormInclude.tpl" %>

<%
	/**
		@function	dec2hex	"Conver decimal to hexadecimal(string)"
		@param		decVal	"value to convert"
		@result		result	"string in the hexa range..."
	*/
	var hexAlpha = "0123456789abcdef";

	function dec2hex( decVal )
	{
		if ( decVal > 255 || decVal < 0 )
		{	// error. we are converting only bytes
			return "";
		}
		return hexAlpha.charAt( decVal % 16 );
	}

	var pta						= new PTA();
	var challengeStringSize 	= pta.getConfigParameter("TW_CHALLENGE_STRING_SIZE");
	var hexaChallengeStringSize = 2 * challengeStringSize;
	var randomBytes				= TW_Crypto.generateRandomBytes(hexaChallengeStringSize);

	var hexaRandomBytes			= new String();
	var i;
	for( i = 0; i < hexaChallengeStringSize; ++i ) {
		hexaRandomBytes = hexaRandomBytes.concat( dec2hex( randomBytes[i] ) );
	}

	tw.session.TW_PTA_CHALLENGE_STRING=hexaRandomBytes;

	//var ptaDemo		= new PTADemo();
	//tw.session.TW_PTA_CHALLENGE_STRING=ptaDemo.generateCryptoRandom(40);

	if ( typeof(arguments) != "undefined" && typeof(arguments.email) != "undefined" && arguments.email.length > 0 ) {
		var account = arguments.email;
	} else {
		var account_cookie = tw.request.getCookie(tw.constant.COOKIE_ACCOUNT_LOGIN_ENCODED);
		var account = account_cookie.decodeBase64();
	}

	// Generate the URL to the Get plugin page here!
	var get_plugin_url = tw.httpGateway.getUrl('SGMS_GetPluginNS.tpl');
	var get_plugin_urlNS6 = tw.httpGateway.getUrl('SGMS_GetPluginNS6.tpl');
%>

<SCRIPT LANGUAGE="JavaScript">
<!--
toSign="<%=tw.session.TW_PTA_CHALLENGE_STRING;%>";
reasonCode="login";
digestAlg="MD5";
// -->

function RedirectToLogin()
{
	self.location = "https://<%=getRealSecureHostname();%>";
}

</script>

<%@include file="SGMS_VSSCDownloadInclude.tpl" %>


<% if ( tw.request.userAgentVendor == "microsoft" ) { %>
	<!-- *********** INCLUDE BUG, remove when fixed *********** -->
	<!--
	/*--------------------------------------------------------------------
	| Copyright (C) VeriSign, Inc. created 1996. All rights reserved.     |
	| This is an unpublished work protected as such under copyright law.  |
	| This work contains proprietary, confidential, and trade secret      |
	| information of VeriSign, Inc.  Use, disclosure or reproduction      |
	| without the expressed written authorization of VeriSign, Inc.       |
	| is prohibited.                                                      |
	--------------------------------------------------------------------*/
	//-->

	<SCRIPT LANGUAGE=JavaScript>
	<!--
	  function SetErrorInfo(form_file, error_code, winerrorcode, operation)
	  {
		document.ErrorForm.form_file.value = form_file ;
		document.ErrorForm.errorCode.value = error_code ;
		document.ErrorForm.winerrorcode.value = winerrorcode ;
		document.ErrorForm.operation.value = operation ;

		document.ErrorForm.submit() ;
	  }

	  // don't call the function below on Netscape pages
	  function CheckErrorCodeMS(error_code)
	  {
		var strErrorCode;
		if (navigator.appName == "Netscape")
			{ return error_code; }

		if (error_code >= "80000000")
		{
		   strErrorCode = "7000" + error_code.substring(error_code.length-4, error_code.length);
		} else {
		   strErrorCode = error_code;
		}
		return strErrorCode;
	  }
	//-->
	</SCRIPT>

	<SCRIPT LANGUAGE="VBSCRIPT">
	<!--
	   Dim hostName
	   hostName = "<%=OnSiteHost;%>"

	  Sub VSSCInitialize
		VSSC_INITIALIZED = &h80003001

	    On Error Resume Next
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

	  Sub RenewDigitalID
		Dim RenewUrl

		RenewUrl = hostName & "/VSApps/client/userRenewalMS.htm"
		window.navigate RenewUrl
	  End Sub

	  Function SignUp
		Dim EnrollUrl
						
				Dim EnrollPage
				EnrollPage= "userEnrollMS.htm"
		
				EnrollUrl = hostName & "/VSApps/client/" & EnrollPage
				window.navigate EnrollUrl
	  End Function

	  'This sub will call the close methods of both the objects
	  Function CloseObjects (ErrorCode, Operation, WinErrorCode)
		On Error Resume Next
		VSSC.IVSSCPTA.Close
		if ( ErrorCode <> 0 ) then
		   Call SetErrorInfoMS("PTA Login","00000001",ErrorCode,"<%=LoginAppStatus;%>",0)
		   Exit Function
		end if
	  End Function


	  Sub SignIt
		Dim TheForm
		Dim Signature
		Dim retVal

	
	
		Dim strCertStore
		Dim strAppCtxtName
		Dim strCertIssuerDN
		Dim strLoginWizardTitle
		Dim strLoginChooseTitle
		Dim strLoginChooseText
		Dim strLoginTitle
		Dim strLoginText
		Dim strAppLogoUrl
		Dim AbtToExpWindow
		Dim strSignWizardTitle
		Dim strSignChooseTitle
		Dim strSignChooseText
		Dim strSignTitle
		Dim strSignText
		Dim strReviewTitle
		Dim strReviewText
		Dim saveLocal
		Dim strClientInfo
		Dim strClientInfoSig

		Dim strLoginChooseHelpUrl
		Dim strLoginHelpUrl
		Dim strSignHelpUrl
		Dim strReviewHelpUrl
		Dim strSignChooseHelpUrl
		Dim strunLockHelpUrl

		Dim AppStatus
		Dim Strg

		Dim strSerialNumber, strCertIDN
		Dim Item_Count, szEmail, nStatus, nResolveStatus

		strCertStore = "1"
		strAppCtxtName = "<%=AppContextName; %>"
		strCertIssuerDN = "O=VeriSign; OU=VeriSign Class 2 OnSite Individual CA"
		strLoginWizardTitle = "SGMS Authentication"

		strLoginChooseTitle = "<%=LoginChooseTitle; %>"
		strLoginChooseText = "<%=LoginChooseText; %>"
		
		strLoginTitle = "Select Digital ID"
		strLoginText = "Select the Digital ID that you would like to present to login to the website."
		
		strSignWizardTitle = "Sign Message"
		strSignChooseTitle = "Enter email address as your profile"
		strSignChooseText = "Enter email address as your profile and password"
		strSignTitle = "Select Digital Id"
		strSignText = "Select the Digital ID that you would like to present to the website."
		strReviewTitle = "Review Message"
		strReviewText = "Review the following message before signing it."
		saveLocal = "disabled"
		strClientInfo = "<%=strClientInfo;%>"
		strClientInfoSig = "<%=strClientInfoSig;%>"

		strAppLogoUrl = "<%=OnSiteHost;%>/SGMSAppLogo.BMP"
				
		AbtToExpWindow = 31

		
		Dim helpHostName
		helpHostName = "<%=OnSiteHost;%>"
		

		strLoginChooseHelpUrl = helpHostName & "/VSApps/client/help/tasks/ptaloginchoose.htm"
		strLoginHelpUrl = helpHostName & "/VSApps/client/help/tasks/ptalogin.htm"
		strSignHelpUrl = helpHostName & "/VSApps/client/help/tasks/sign.htm"
		strReviewHelpUrl = helpHostName & "/VSApps/client/help/tasks/review.htm"
		strSignChooseHelpUrl = helpHostName & "/VSApps/client/help/tasks/signchoose.htm"
		strUnLockHelpUrl = helpHostName & "/VSApps/client/help/tasks/ptaunlock.htm"
		
		On Error Resume Next
		Call VSSCInitialize

		if bErrorPresent = 1 then
			exit sub
		end if

		On Error Resume Next
		Set IVSPTA=VSSC.IVSSCPTA
		If ( err.number <> 0) then
		    Call CloseObjects(Hex(err.number), "",0)
			Exit Sub
		End If

		INITIALIZED = &h80001001

		' Initialize the PTA Object
		On Error Resume Next
		if (strCertStore = "1") then
			IVSPTA.Initialize strAppCtxtName,0
		else
			IVSPTA.Initialize strAppCtxtName,1
		End If

		If ( err.number <> INITIALIZED And err.number <> 0) then
		    Call CloseObjects(Hex(err.number), "",0)
			Exit Sub
		End If

		
		On Error Resume Next
		Set IVSProfMgmt = IVSPTA.IVSProfMgmt
		If ( err.number <> 0) then
		    Call CloseObjects(Hex(err.number), "",0)
			Exit Sub
		End If

		CARD_NOT_OPEN = &h80001008
		On Error Resume Next
		IVSProfMgmt.CloseProfile()
		If (err.number <> 0 And err.number <> CARD_NOT_OPEN) then
		    Call CloseObjects(Hex(err.number), "",0)
			Exit Sub
		End If

		OBJECT_NODE_NOT_FOUND =	&h80005002
		On Error Resume Next
		VSSC.ClearAll 0, AppStatus
		If (err.number <> 0 And err.number <> OBJECT_NODE_NOT_FOUND) then
		    Call CloseObjects(Hex(err.number), "",0)
			Exit Sub
		End If

		'Initialize VSSC And PTA Again
		Call VSSCInitialize
		
		if bErrorPresent = 1 then
			exit sub
		end if

		On Error Resume Next
		Set IVSPTA=VSSC.IVSSCPTA
		If ( err.number <> 0) then
		    Call CloseObjects(Hex(err.number), "",0)
			Exit Sub
		End If

		
		' Initialize the PTA Object
		On Error Resume Next
		if (strCertStore = "1") then
			IVSPTA.Initialize strAppCtxtName,0
		else
			IVSPTA.Initialize strAppCtxtName,1
		End If

		If ( err.number <> INITIALIZED And err.number <> 0) then
		    Call CloseObjects(Hex(err.number), "",0)
			Exit Sub
		End If


		'Remove SelectID Dialog
		'This VSSC Property to be called only after IVSPTA.Initialize is called
		On Error Resume Next
		VSSC.ShowSelIDUI = CBool(0)
		If ( err.number <> 0 ) then
		  Call CloseObjects(Hex(err.number), "",0)
		  Exit Sub
		End If


		On Error Resume Next
		VSSC.CertResolveURL = "<%=CertResolveURL;%>"
		If(err.number <> 0) then
			Call CloseObjects(Hex(err.number), "",0)
			Exit Sub
		
		End If

		
		On Error Resume Next
		VSSC.SCType = "<%=SCType;%>"		
		If(err.number <> 0) then
			Call CloseObjects(Hex(err.number), "",0)
			Exit Sub
		End If

		On Error Resume Next
		Strg=VSSC.CertificateResolution("<%= account; %>", AppStatus)
		If(err.number <> 0) then
			Call CloseObjects(Hex(err.number), "",0)
			Exit Sub
		End If


		On Error Resume Next
		Set IResolveInfo = VSSC.IVSSCResolveInfo
		If(err.number <> 0) then
			Call CloseObjects(Hex(err.number), "",0)
			Exit Sub
		End If

		On Error Resume Next
		Item_Count=IResolveInfo.Recipient_Count
		If(err.number <> 0) then
			Call CloseObjects(Hex(err.number), "",0)
			Exit Sub
		End If


		On Error Resume Next
		IResolveInfo.First
		If(err.number <> 0) then
			Call CloseObjects(Hex(err.number), "",0)
			Exit Sub
		End If

		On Error Resume Next
		szEmail=IResolveInfo.EmailAddress
		If(err.number <> 0) then
			Call CloseObjects(Hex(err.number), "",0)
			Exit Sub
		End If

		CERT_RESOLUTION_FAILED = &h8000304B
		RESOLVE_STATUS_BITS = &h000F
		On Error Resume Next
		nStatus=IResolveInfo.status
		If(err.number <> 0) then
			Call CloseObjects(Hex(err.number), "",0)
			Exit Sub
		End If


		nResolveStatus = nStatus and RESOLVE_STATUS_BITS

		If(nResolveStatus = 0) then
			'MsgBox "Unable to find your DigitalID. Please contact Administrator. "
			'Call RedirectToLogin()
			'Exit Sub
			errString = "You do not have a valid Digital ID." &vbCRLF & _
						"Would you like to enroll for a Digital ID at this time?"
			Choice = MsgBox (errString, 52, "Login Error")
			'MsgBox "Choice "&Choice
			if ( 6 = Choice ) then
				'MsgBox "About to call SignUp"
				Call CloseObjects(0, "", 0)
				' set the login form variables and submit
				document.LoginForm.dataToSign.value = ""
				document.LoginForm.dataSignature.value = ""
				document.LoginForm.submit
				'Call SignUp()
				Exit Sub
			else
				Call RedirectToLogin()
				Exit Sub
			end if
		End If

		On Error Resume Next
		strSerialNumber = IResolveInfo.SerialNumber
		If(err.number <> 0) then
			Call CloseObjects(Hex(err.number), "",0)
			Exit Sub
		End If
		If(Len(strSerialNumber) = 0) then
			Call CloseObjects(Hex(CERT_RESOLUTION_FAILED), "",0)
			Exit Sub
		End If

		On Error Resume Next
		strCertIDN = IResolveInfo.Issuer_DN
		If(err.number <> 0) then
			Call CloseObjects(Hex(err.number), "",0)
			Exit Sub
		End If
		If(Len(strCertIDN) = 0) then
			Call CloseObjects(Hex(CERT_RESOLUTION_FAILED), "",0)
			Exit Sub
		End If

		' Initialize the Search Criteria
		On Error Resume Next
		If (Len(strCertIDN) <> 0) then
			VSSC.IVSSCPTA.IVSSrchCrit.IssuerDN = strCertIDN
			If ( err.number <> 0 ) then
				Call CloseObjects(Hex(err.number), "",0)
				Exit Sub
			End If
		End If


		If(Len(strSerialNumber) <> 0) then
				VSSC.IVSSCPTA.IVSSrchCrit.SerNum = strSerialNumber
				If ( err.number <> 0 ) then
						Call CloseObjects(Hex(err.number), "",0)
						Exit Sub
				End If
		End If


		EXP_DATE_GREATER_THAN = &h20
		EXP_DATE_EQUALTO      = &h10
		EXP_DATE_LESS_THAN    = &h08
		EFF_DATE_GREATER_THAN = &h04
		EFF_DATE_EQUALTO      = &h02
		EFF_DATE_LESS_THAN    = &h01

		' Initialize the Certificate Search Criterion "Date Equality"
		On Error Resume Next
		VSSC.IVSSCPTA.IVSSrchCrit.DateEquality = EXP_DATE_GREATER_THAN
		If ( err.number <> 0 ) then
		  Call CloseObjects(Hex(err.number), "",0)
		  Exit Sub
		End If

		' Initialize the Certificate Search Criterion "Expiry Date"
		' to the CURRENT DATE.
		StartDate = CDate(Date)
		ShortStartDate = CDate(StartDate)

		On Error Resume Next
		VSSC.IVSSCPTA.IVSSrchCrit.ExpDate = ShortStartDate
		If ( err.number <> 0 ) then
		  Call CloseObjects(Hex(err.number), "",0)
		  Exit Sub
		End If

		Dim boolRenewed
		boolRenewed = CBool(0)
		' Set flag to show only certs that have NOT been marked as RENEWED
		On Error Resume Next
		VSSC.IVSSCPTA.IVSSrchCrit.Renewed = boolRenewed
		If ( err.number <> 0 ) then
		  Call CloseObjects(Hex(err.number), "",0)
		  Exit Sub
		End If

		' Initialize the login wizard title
		On Error Resume Next
		If (Len(strLoginWizardTitle) <> 0) then
			VSSC.IVSSCPTA.IVSUIPrefs.LgnDlg_Title = strLoginWizardTitle
			If ( err.number <> 0 ) then
				Call CloseObjects(Hex(err.number), "",0)
				Exit Sub
			End If
		End If

		' Initialize the open profile preferences
		if (strCertStore = "1") then
			On Error Resume Next
			If (Len(strLoginChooseTitle) <> 0) then
				VSSC.IVSSCPTA.IVSUIPrefs.OpenProf_Title = strLoginChooseTitle
				If ( err.number <> 0 ) then
					Call CloseObjects(Hex(err.number), "",0)
					Exit Sub
				End If
			End If

			On Error Resume Next
			If (Len(strLoginChooseText) <> 0) then
				VSSC.IVSSCPTA.IVSUIPrefs.OpenProf_Text = strLoginChooseText
				If ( err.number <> 0 ) then
					Call CloseObjects(Hex(err.number), "",0)
					Exit Sub
				End If
			End If

			On Error Resume Next
			If (Len(strLoginChooseHelpUrl) <> 0) then
				VSSC.IVSSCPTA.IVSUIPrefs.OpenProf_HelpUrl = strLoginChooseHelpUrl
				If ( err.number <> 0 ) then
					Call CloseObjects(Hex(err.number), "",0)
					Exit Sub
				End If
			End If

			On Error Resume Next
			If (Len(strUnLockHelpUrl) <> 0) then
				VSSC.IVSSCPTA.IVSUIPrefs.Timeout_HelpUrl = strUnLockHelpUrl
				If ( err.number <> 0 ) then
					Call CloseObjects(Hex(err.number), "",0)
					Exit Sub
				End If
			End If

			On Error Resume Next
			VSSC.IVSSCPTA.IVSProfMgmt.ProfileName = "<%=account; %>"
			If ((err.number <> 0) And (Hex(err.number) <> "8000102F") ) Then
				Call CloseObjects(Hex(err.number), "",0)
				Exit Sub
			End If

			On Error Resume Next
			VSSC.IVSSCPTA.IVSProfMgmt.IsUsernameEditable = CBool(0)
			If (err.number <> 0 ) Then
				Call CloseObjects(Hex(err.number), "",0)
				Exit Sub
			End If

			'Flags
			OPENPROF_OPEN_ONLY = CInt(529)
			On Error Resume Next
			VSSC.IVSSCPTA.IVSProfMgmt.OpenProfFlags = OPENPROF_OPEN_ONLY
			If ((err.number <> 0) And (Hex(err.number) <> "8000102F") ) Then
				Call CloseObjects(Hex(err.number), "",0)
				Exit Sub
			End If

			if ( (strClientInfo = "") Or (strClientInfoSig = "") ) Then
			  Call CloseObjects(Hex(err.number), "",0)
			  Exit Sub
			End if

			On Error Resume Next
			VSSC.IVSSCPTA.IVSRoamPrefs.ClientInfo = strClientInfo
			If ((err.number <> 0) And (Hex(err.number) <> "8000102F") ) Then
			   Call CloseObjects(Hex(err.number), "",0)
			   Exit Sub
			End If

			On Error Resume Next
			VSSC.IVSSCPTA.IVSRoamPrefs.ClientInfoSig = strClientInfoSig
			If ((err.number <> 0) And (Hex(err.number) <> "8000102F") ) Then
			   Call CloseObjects(Hex(err.number), "",0)
			   Exit Sub
			End If

		  ' set roaming enabled
		  On Error Resume Next
		  VSSC.IVSSCPTA.IVSProfMgmt.RoamProfile = CBool(1)
		  If ((err.number <> 0) And (Hex(err.number) <> "8000102F") ) Then
			 Call CloseObjects(Hex(err.number), "",0)
			 Exit Sub
		  End If
		End If

		' set open profile ok button text to login
		On Error Resume Next
		VSSC.IVSSCPTA.IVSUIPrefs.OpenProf_OKBtnText = CInt(125)
		If ( err.number <> 0 ) then
			Call CloseObjects(Hex(err.number), "",0)
			Exit Sub
		End If

		' set the select id preferences
		On Error Resume Next
		If (Len(strLoginTitle) <> 0) then
			VSSC.IVSSCPTA.IVSUIPrefs.SelID_Title = strLoginTitle
			If ( err.number <> 0 ) then
				Call CloseObjects(Hex(err.number), "",0)
				Exit Sub
			End If
		End If

		On Error Resume Next
		If (Len(strLoginText) <> 0) then
			VSSC.IVSSCPTA.IVSUIPrefs.SelID_Text = strLoginText
			If ( err.number <> 0 ) then
				Call CloseObjects(Hex(err.number), "",0)
				Exit Sub
			End If
		End If

		Dim boolShowDef
		boolShowDef = CBool(1)	
		On Error Resume Next
		VSSC.IVSSCPTA.IVSUIPrefs.SelID_ShowDefChkBox = boolShowDef
		If ( err.number <> 0 ) then
		   Call CloseObjects(Hex(err.number), "",0)
		   Exit Sub
		End If

		On Error Resume Next
		If (Len(strAppLogoUrl) <> 0) then
			VSSC.IVSSCPTA.IVSUIPrefs.UILogoUrl = strAppLogoUrl
			If ( err.number <> 0 ) then
				Call CloseObjects(Hex(err.number), "",0)
				Exit Sub
			End If
		End If

		On Error Resume Next
		If (Len(strLoginHelpUrl) <> 0) then
			VSSC.IVSSCPTA.IVSUIPrefs.SelID_HelpUrl = strLoginHelpUrl
			If ( err.number <> 0 ) then
				Call CloseObjects(Hex(err.number), "",0)
				Exit Sub
			End If
		End If


		On Error Resume Next
		VSSC.IVSSCPTA.IVSUIPrefs.SelID_OKBtnText = CInt(125)
		if (err.number <> 0) then
			Call CloseObjects(Hex(err.number), "",0)
			Exit Sub
		End If

		if document.LoginForm.ResetPref.checked = true then
			VSSC.IVSSCPTA.UseDefCertFlag = 0
		else
			VSSC.IVSSCPTA.UseDefCertFlag = 1
		end if
'		If ( err.number <> 0) then
'		    Call CloseObjects(Hex(err.number), "",0)
'			Exit Sub
'		End If

			' if the user did not choose to renew his Digital ID
		' or if the cert was not about to expire
		MD5 = 3
		SHA1 = 4

		On Error Resume Next
		' Get the "Signature"
		If (digestAlg = "MD5") Then
			Signature = VSSC.IVSSCPTA.SignChallenge (toSign, CInt(MD5))
		Else
		  If (digestAlg = "SHA") Then
			  Signature = VSSC.IVSSCPTA.SignChallenge (toSign, CInt(SHA1))
		  End If
		End If


		VS_CERTNOMATCHCRIT = &h80001095
		VS_CERTMATCHBUTEXP = &h80001096
		VS_SUCCESS = &h00000000
		VS_PROFDOESNOTEXIST = &h8000102B
		VS_USER_CANCELLED = &h80001067
		VS_CERTNOTFOUND = &h80001091


	   ' some special handling needs to be done.
	   If ( err.number <> 0 )then
		  If (err.number = VS_CERTMATCHBUTEXP) then
			  errString = "You do not have a valid Digital ID." &vbCRLF &_
						  "Now the PTA will try to renew your expired Digital IDs."
			  'Call MsgBox (errString, 48, "Login Error")
			  Call CloseObjects(Hex(err.number), "", 0)
			  'RenewDigitalID()
			  Exit Sub
		  Else
			 If ((err.number = VS_CERTNOMATCHCRIT) Or (err.number = VS_PROFDOESNOTEXIST) Or (err.number = VS_CERTNOTFOUND)) then
				 Call CloseObjects(Hex(err.number), "", 0)
				 errString = "You do not have a valid Digital ID." &vbCRLF & _
							 "Would you like to enroll for a Digital ID at this time?"
				 'Choice = MsgBox (errString, 52, "Login Error")
				 'if ( 6 = Choice ) then
				 '	 Call SignUp()
				 'end if
				 Exit Sub
			 Else
			   If (err.number = VS_USER_CANCELLED) then
				  errString = "You have cancelled the Login operation." & vbCRLF & _
							  "Please click login again to continue."
				  Call CloseObjects(0, "", 0)
				  Call RedirectToLogin()
				  Exit Sub
			   Else
				  Call CloseObjects(Hex(err.number), "",0)
				  Exit Sub
			   End If
			 End If
		  End If
	   End If


	   ' at this instance the user selected an ID and signed the challenge
	   ' check if the ID is about to expire and give the user an option to renew
	   ' his digital ID
	   '
	   ' If this point has been reached, the user selected a valid
	   ' certificate.

	   ' Detect here by looking at the Selected cert's Expriy Date if it
	   ' is about to expire in 10 days. If it is, then ask the user if
	   ' he wants to renew the cert which is about to expire OR
	   ' he just wants to continue with the login.

	   ADVANCE_DAYS = AbtToExpWindow

	   On Error Resume Next
	   SelExpDate = VSSC.IVSSCPTA.IVSSelectedDigID.ExpDate
	   If ( err.number <> 0) then
		    Call CloseObjects(Hex(err.number), "",0)
			Exit Sub
	   End If

	   ShortSelExpDate = CDate(SelExpDate)
	   If ( (Date + ADVANCE_DAYS) > ShortSelExpDate ) Then
		 'Msg = "The Digital ID that you selected will expire after " & CStr(CInt(ShortSelExpDate-Date)) & " Days." & vbCRLF & _
		 '	   "You can either choose to continue with this login " & vbCRLF & _
		 '	   "or you can renew your Digital ID." & vbCRLF & vbCRLF & _
		 '	   "Would you like to renew your Digital ID ?"
		 'retVal = MsgBox(Msg, 49, "Login Warning")

		 Msg = "The Digital ID that you selected will expire after " & CStr(CInt(ShortSelExpDate-Date)) & " Days." & vbCRLF & _
			   "You need to renew your Digital ID."

		 MsgBox Msg

		 retVal = 0

		 If ( retVal = 1 ) Then
			' If the user press OK, then take him to the renewal stuff
			' START Renewal Stuff
			MD5 = 3
			SHA1 = 4

			' Set the Message that needs to be signed.
			RenewMsgg = document.RenewalForm.detachedMesg.value
			'HexMsgg = "52656E6577204469676974616C204944"

			' Get the "Signature" that is to be used to renew a given certificate
			On Error Resume Next
			RenewSignature = VSSC.IVSSCPTA.SignRenewal (CInt(MD5))
			If ( err.number <> 0 ) then
			   Call CloseObjects(Hex(err.number), "",0)
			   Exit Sub
			End If

			' This sets the signature which has the certificate that needs renewal
			document.RenewalForm.pkcsInformation.value = RenewSignature

			' Get Serial Number of Certificate that needs renewal
			On Error Resume Next
			document.RenewalForm.orig_cert_serial.value = VSSC.IVSSCPTA.IVSSelectedDigID.SerNum
			If ( err.number <> 0 ) then
			  Call CloseObjects(Hex(err.number), "",0)
			  Exit Sub
			End If

			' Get Issuer DN of Certificate that needs renewal
			On Error Resume Next
			document.RenewalForm.orig_cert_issuerdn.value = VSSC.IVSSCPTA.IVSSelectedDigID.IssuerDN
			If ( err.number <> 0 ) then
			  Call CloseObjects(Hex(err.number), "",0)
			  Exit Sub
			End If

			Call CloseObjects(0, "", 0)
			document.RenewalForm.submit
			Exit Sub

		  End If ' end if user wants to renew
		End If ' end if cert is about to expire


		' Cleanup
		Call CloseObjects(0, "", 0)

		' set the login form variables and submit
		document.LoginForm.dataToSign.value = toSign
		document.LoginForm.dataSignature.value = Signature
		document.LoginForm.submit
	  End Sub
	'-->
	</SCRIPT>

	<SCRIPT LANGUAGE="JavaScript">
	  function CheckReasonCode()
	  {
		// The script variable "reasonCode" gets assigned a value through the
		// Java Script prepended by NSAPI Filter when the Login Page
		// is sent to the browser.

		if ( reasonCode.search(/expired/i) == 0 )
		{
		  document.write("<br><FONT SIZE=4 COLOR=RED><CENTER>Inactivity timeout ...</CENTER></FONT><br>") ;
		}
		else if ( reasonCode.search(/login/i) == -1 )
		{
		  document.write("<br><FONT SIZE=4 COLOR=RED><CENTER>Unknown Error Occured ...</CENTER></FONT><br>") ;
		}
	  }
	</SCRIPT>
<% } else { %>
<!-- The assumption is that JavaScript will be supported on a non-microsoft browser -->
	<!-- *********** INCLUDE BUG, remove when fixed *********** -->
	<!-- ptaLoginNS.htm
	/*--------------------------------------------------------------------
	| Copyright (C) VeriSign, Inc. created 1996. All rights reserved.     |
	| This is an unpublished work protected as such under copyright law.  |
	| This work contains proprietary, confidential, and trade secret      |
	| information of VeriSign, Inc.  Use, disclosure or reproduction      |
	| without the expressed written authorization of VeriSign, Inc.       |
	| is prohibited.                                                      |
	--------------------------------------------------------------------*/
	//-->

	<script language = "JavaScript">
	<!--
		var browserNum = parseInt(navigator.appVersion);
	//-->
	</script>

	<SCRIPT LANGUAGE="JavaScript">
		var len;
		var name;
		var description;
		var found = 0;

		navigator.plugins.refresh(true);

		len = navigator.plugins.length;
		for(i=0;i<len;++i) {
			name = navigator.plugins[i].name;
			description = navigator.plugins[i].description;
			if (name.search("Verisign Secure Collaboration") != -1) {
				if (browserNum < 5) {
					if ( description >= 1004 ) {
						found = 1;
						i = len;
					}
				} else {
					if ( description >= 1004 ) {
						found = 1;
						i = len;
					}
				}
			}
		}

		if(found != 1)
		//-- VSSKBEGIN Global/Mode#102#autoauth#1.2.0.4#2476 --
		if(browserNum < 5){
			self.location = "<%=get_plugin_url;%>";
		} else {
			self.location = "<%=get_plugin_urlNS6;%>";
		}

	</SCRIPT>

	<SCRIPT LANGUAGE=JavaScript>
	<!--
	  function SetErrorInfo(form_file, error_code, winerrorcode, operation)
	  {
		document.ErrorForm.form_file.value = form_file ;
		document.ErrorForm.errorCode.value = error_code ;
		document.ErrorForm.winerrorcode.value = winerrorcode ;
		document.ErrorForm.operation.value = operation ;

		document.ErrorForm.submit() ;
	  }

	  // don't call the function below on IE pages
	  function ReBaseErrorCodeNS(error_code)
	  {
		if (navigator.appName != "Netscape")
			{ return error_code; }

		var javaErrorString, strErrorCode;
		var ErrNumber;

		ERROR_LIMIT = 0x80000000;
		if (error_code >= ERROR_LIMIT) {
		  error_code = error_code - 0x80000000;
		  ErrNumber = new Number(error_code);
		  javaErrorString = ErrNumber.toString(16);
		  if(error_code <= 0xF) {
		strErrorCode = "7000000" + javaErrorString.substring(javaErrorString.length-1, javaErrorString.length);
		  }
		  else if (error_code <= 0xFF) {
		strErrorCode = "700000" + javaErrorString.substring(javaErrorString.length-2, javaErrorString.length);
		  }
		  else if (error_code <= 0xFFF) {
		strErrorCode = "70000" + javaErrorString.substring(javaErrorString.length-3, javaErrorString.length);
		  }
		  else {
		   strErrorCode = "7000" + javaErrorString.substring(javaErrorString.length-4, javaErrorString.length);
		  }
		} else {
		  ErrNumber = new Number(error_code);
		  strErrorCode = ErrNumber.toString(10);
		}
		return strErrorCode;
	  }

	  // Don't call the function below on IE pages
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

	//-->
	</SCRIPT>


	<SCRIPT LANGUAGE="JavaScript">
	  var StartDate;
	  var todaysDate;
	  var Signature;
	  var PKCS10;

	 function CheckReasonCode()
	  {
		// The script variable "reasonCode" gets assigned a value through the
		// Java Script prepended by NSAPI Filter when the Login Page
		// is sent to the browser.

		if ( reasonCode.search(/expired/i) == 0 )
		{
		  document.write("<br><FONT SIZE=4 COLOR=RED><CENTER>Inactivity timeout ...</CENTER></FONT><br>") ;
		}
		else if ( reasonCode.search(/login/i) == -1 )
		{
		  document.write("<br><FONT SIZE=4 COLOR=RED><CENTER>Unknown Error Occured ...</CENTER></FONT><br>") ;
		}
	  }
	</SCRIPT>

	<SCRIPT LANGUAGE="JavaScript">
	   var hostName = "<%=OnSiteHost;%>";

	  function GoToRenewDigitalIDJava()
	  {
		var RenewalUrl = hostName + "/VSApps/client/userRenewalNS.htm";
		self.location =  RenewalUrl;
	  }

	 function CloseObjects(errCode, Operation, WinErrorCode)
	 {
		RetVal = document.VSSC.PTA_Close ();

		if (errCode != 0) {
		   SetErrorInfoNS("PTA Login","00000001",ConvertToHexNS(errCode),"<%=LoginAppStatus;%>",0);
		}
		return;
	 }

	  function SignUpJava()
	  {
		var EnrollUrl;

		var EnrollPage = "userEnrollNS.htm";

		EnrollUrl = hostName + "/VSApps/client/" + EnrollPage;
		self.location = EnrollUrl;
	  }

	  function LoginJava()
	  {
		CloseObjects(0, "", 0);
		document.LoginForm.dataToSign.value = toSign ;
		document.LoginForm.dataSignature.value = Signature ;
		document.LoginForm.submit() ;
	  }


	  function RenewDigitalIDJava()
	  {
		MD5 = 3 ;
		SHA1 = 4 ;

		// Set the Message that needs to be signed.
		var RenewMsgg = "Renew Digital ID";
		MD5Renewal = 3 ;

		// Get the "Signature" that is to be used to renew a given certificate
		RenewSignature = document.VSSC.PTA_SignRenewal(MD5Renewal) ;
		if ( (ErrorCode = document.VSSC.GetLastError()) != 0)
		{
		  CloseObjects(ErrorCode, "", 0);
		  return ;
		}

		// This sets the signature which has the certificate that needs renewal
		document.RenewalForm.pkcsInformation.value = RenewSignature ;

		// This sets message that is being signed
		document.RenewalForm.detachedMesg.value = RenewMsgg ;

		// Get Serial Number of Certificate that needs renewal
		CertSerialNumber = document.VSSC.get_SelectedDigID_SerNum() ;
		if ( (ErrorCode = document.VSSC.GetLastError()) != 0)
		{
		  CloseObjects(ErrorCode, "", 0);
		  return ;
		}

		document.RenewalForm.orig_cert_serial.value = CertSerialNumber ;

		// Get Issuer DN of Certificate that needs renewal
		IssuerDN = document.VSSC.get_SelectedDigID_IssuerDN() ;
		if ( (ErrorCode = document.VSSC.GetLastError()) != 0)
		{
		  CloseObjects(ErrorCode, "", 0);
		  return ;
		}
		document.RenewalForm.orig_cert_issuerdn.value = IssuerDN ;

		CloseObjects(0, "", 0);
		document.RenewalForm.submit() ;
	  }


	  function SignItJava()
	  {

		// the JavaScript variables made available on PTA login page
		var strCertStore = "1";
		var strAppCtxtName = "<%=AppContextName; %>";
		var strCertIssuerDN = "O=VeriSign; OU=VeriSign Class 2 OnSite Individual CA";
		var strLoginWizardTitle = "SGMS Authentication";

		var strLoginChooseTitle = "<%=LoginChooseTitle; %>";
		var strLoginChooseText = "<%=LoginChooseText; %>";
		var strAppLogoUrl = "<%=OnSiteHost;%>/SGMSAppLogo.BMP";

		var strLoginTitle = "Select Digital ID";
		var strLoginText = "Select the Digital ID that you would like to present to login to the website.";

		var strSignWizardTitle = "Sign Message";
		var strSignChooseTitle = "Enter email address as your profile";
		var strSignChooseText = "Enter email address as your profile and password";
		var strSignTitle = "Select Digital Id";
		var strSignText = "Select the Digital ID that you would like to present to the website.";
		var strReviewTitle = "Review Message";
		var strReviewText = "Review the following message before signing it.";
		var saveLocal = "disabled";
		var strClientInfo = "<%=strClientInfo;%>";
		var strClientInfoSig = "<%=strClientInfoSig;%>";


		var AbtToExpWindow = 31;

		var helpHostName = "<%=OnSiteHost;%>";

		var strLoginChooseHelpUrl = helpHostName + "/VSApps/client/help/tasks/ptaloginchoose.htm";
		var strLoginHelpUrl = helpHostName + "/VSApps/client/help/tasks/ptalogin.htm";
		var strSignHelpUrl = helpHostName + "/VSApps/client/help/tasks/sign.htm";
		var strReviewHelpUrl = helpHostName + "/VSApps/client/help/tasks/review.htm";
		var strSignChooseHelpUrl = helpHostName + "/VSApps/client/help/tasks/signchoose.htm";
		var strUnLockHelpUrl = helpHostName + "/VSApps/client/help/tasks/ptaunlock.htm";

		if(bErrorPresent == 1)
			return;

		if(browserNum < 5) {
			StartDate = new java.util.Date();
			todaysDate = new java.util.Date() ;
			Signature = new java.lang.StringBuffer() ;
			PKCS10 = new java.lang.StringBuffer("") ;
		} else {
			StartDate = new Date();
			StartDate = StartDate.getTime();
			todaysDate = new Date() ;
			Signature = new String() ;
			PKCS10 = new String("") ;
			// ??? document.VSSC = document.VSSC.ns6IPTA;
		}

		
		// Code added as part of pop-up change  FIXME !!!!!
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
		VSSC.set_VSSC_SupportedPTAVer(SupportedVer);
		ErrorCode=VSSC.GetLastError();
		
		if(ErrorCode == DIFFERENT_PTAVER)
		{
			CloseObjects(ErrorCode, "", 0);
			return ErrorCode;	
		}
		else if(ErrorCode)
		{
			CloseObjects(ErrorCode, "", 0);
			return ErrorCode;
		}

		if (strCertStore == "1") {
			document.VSSC.PTA_Initialize(strAppCtxtName, 0) ;
		}
		else {
			document.VSSC.PTA_Initialize(strAppCtxtName, 1) ;
		}
		if ( (ErrorCode = document.VSSC.GetLastError()) != 0) {
			CloseObjects(ErrorCode, "", 0);
			return ErrorCode;
		}

		INITIALIZED = 0x80001001;
		CARDNOTOPEN = 0x80001008;

		document.VSSC.ProfMgmt_CloseProfile();
		ErrorCode = document.VSSC.GetLastError();
		if ( ErrorCode != 0 && ErrorCode != CARDNOTOPEN) {
			CloseObjects(ErrorCode, "", 0);
			return ErrorCode;
		}

		OBJECT_NODE_NOT_FOUND =	0x80005002;		
		document.VSSC.VSSC_ClearAll(0, AppStatus);
		ErrorCode = document.VSSC.GetLastError();
		if ( ErrorCode  && ErrorCode != OBJECT_NODE_NOT_FOUND) {
			CloseObjects(ErrorCode, "", 0);
			return ErrorCode;
		}

		count = 1;
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
		
		ErrorCode=document.VSSC.GetLastError();
		if(ErrorCode !=0 && ErrorCode != VSSC_INITIALIZED)
		{
			CloseObjects(ErrorCode, "", 0);	
			return ErrorCode;		
		}		

		//Set the list of PTA versions supported by VSSC
		VSSC.set_VSSC_SupportedPTAVer(SupportedVer);
		ErrorCode=VSSC.GetLastError();
		
		if(ErrorCode == DIFFERENT_PTAVER)
		{
			//InstalledVer = VSSC.get_VSSC_InstalledPTAVer();
			CloseObjects(ErrorCode, "", 0);
			return ErrorCode;	
		}
		else if(ErrorCode)
		{
			CloseObjects(ErrorCode, "", 0);
			return ErrorCode;
		}

		// Initialize PTA again
		if (strCertStore == "1") {
			document.VSSC.PTA_Initialize(strAppCtxtName, 0) ;
		}
		else {
			document.VSSC.PTA_Initialize(strAppCtxtName, 1) ;
		}
		if ( (ErrorCode = document.VSSC.GetLastError()) != 0) {
			CloseObjects(ErrorCode, "", 0);
			return ErrorCode;
		}

		document.VSSC.set_VSSC_ShowSelIDUI(false);
		if (ErrorCode = document.VSSC.GetLastError()) {
			CloseObjects(ErrorCode, "", 0);
			return ErrorCode;
		}

		document.VSSC.set_VSSC_CertResolveURL("<%=CertResolveURL;%>");
		if ( ErrorCode = document.VSSC.GetLastError() ) {
			CloseObjects(ErrorCode, "", 0);
			return ErrorCode;
		}

		document.VSSC.set_VSSC_SCType("<%=SCType;%>");
		if ( ErrorCode = document.VSSC.GetLastError() ) {
			CloseObjects(ErrorCode, "", 0);
			return ErrorCode;
		}

		Strg = document.VSSC.VSSC_CertificateResolution("<%= account; %>", AppStatus);
		if ( ErrorCode = document.VSSC.GetLastError() ) {
			CloseObjects(ErrorCode, "", 0);
			return ErrorCode;
		}

		var item_count = document.VSSC.get_ResolveRcpt_Recipient_Count();
		if ( ErrorCode = document.VSSC.GetLastError() ) {
			CloseObjects(ErrorCode, "", 0);
			return ErrorCode;
		}

		// the valid certificate is only one
		document.VSSC.ResolveRcpt_First();
		if ( ErrorCode = document.VSSC.GetLastError() ) {
			CloseObjects(ErrorCode, "", 0);
			return ErrorCode;
		}

		szEmail = document.VSSC.get_ResolveRcpt_EmailAddress();
		if ( ErrorCode = document.VSSC.GetLastError() ) {
			CloseObjects(ErrorCode, "", 0);
			return ErrorCode;
		}

		var nStatus = document.VSSC.get_ResolveRcpt_Status();
		if ( ErrorCode = document.VSSC.GetLastError() ) {
			CloseObjects(ErrorCode, "", 0);
			return ErrorCode;
		}

		CERT_RESOLUTION_FAILED = 0x8000304B;
		RESOLVE_STATUS_BITS = 0x000F;
		var nResolveStatus = nStatus & RESOLVE_STATUS_BITS;

		if(nResolveStatus  == 0) {
			//alert ("Unable to find your DigitialID.\nPlease contact Administrator.");
			//CloseObjects(0, "", 0);
			//RedirectToLogin();
			//return;
			EnrollState = confirm("You do not have a valid Digital ID.\nWould you like to enroll for a Digital ID at this time?") ;
			if ( EnrollState == true ) {
				//alert("About to call SignUp");
				CloseObjects(0, "", 0);
				document.LoginForm.dataToSign.value = "" ;
				document.LoginForm.dataSignature.value = "" ;
				document.LoginForm.submit() ;
				return;
			} else {
				RedirectToLogin();
				return ErrorCode;
			}
		}
	
		var strSerialNumber = document.VSSC.get_ResolveRcpt_SerialNumber();
		if ( ErrorCode = document.VSSC.GetLastError() ) {
			CloseObjects(ErrorCode, "", 0);
			return ErrorCode;
		}

		strCertIssuerDN = document.VSSC.get_ResolveRcpt_IssuerDN();
		if ( ErrorCode = document.VSSC.GetLastError() ) {
			CloseObjects(ErrorCode, "", 0);
			return ErrorCode;
		}
	
	    if(strSerialNumber == "" || strCertIssuerDN == "") {
			CloseObjects(CERT_RESOLUTION_FAILED, "", 0);
			return ErrorCode;
		}


		// Initialize the IssuerDN
		document.VSSC.set_SrchCrit_IssuerDN(strCertIssuerDN) ;
		if ( (ErrorCode = document.VSSC.GetLastError()) != 0)
		{
			CloseObjects(ErrorCode, "", 0);
			return ErrorCode;
		}

		// Initialize the certificate serial number
		document.VSSC.set_SrchCrit_SerNum(strSerialNumber);
		if ( (ErrorCode = document.VSSC.GetLastError()) != 0)
		{
			CloseObjects(ErrorCode, "", 0);
			return ErrorCode;
		}

		EXP_DATE_GREATER_THAN = 0x20 ;
		EXP_DATE_EQUALTO      = 0x10 ;
		EXP_DATE_LESS_THAN    = 0x08 ;
		EFF_DATE_GREATER_THAN = 0x04 ;
		EFF_DATE_EQUALTO      = 0x02 ;
		EFF_DATE_LESS_THAN    = 0x01 ;

		// Initialize the Certificate Search Criterion "Date Equality"
		document.VSSC.set_SrchCrit_DateEquality(EXP_DATE_GREATER_THAN) ;
		if ( (ErrorCode = document.VSSC.GetLastError()) != 0)
		{
		  CloseObjects(ErrorCode, "", 0);
		  return ;
		}

		// Initialize the Certificate Search Criterion "Expiry Date"
		// to the CURRENT DATE.
		document.VSSC.set_SrchCrit_ExpDate(StartDate) ;
		if ( (ErrorCode = document.VSSC.GetLastError()) != 0)
		{
		  CloseObjects(ErrorCode, "", 0);
		  return ;
		}


		document.VSSC.set_SrchCrit_Renewed(false) ;
		if ( (ErrorCode = document.VSSC.GetLastError()) != 0)
		{
		  CloseObjects(ErrorCode, "", 0);
		  return ;
		}

		// set the UI preferences
		if (strLoginWizardTitle[0] != null){
			document.VSSC.set_UIPrefs_LgnDlg_Title(strLoginWizardTitle) ;
			if ( (ErrorCode = document.VSSC.GetLastError()) != 0) {
			   CloseObjects(ErrorCode, "", 0);
			   return ;
			}
		}
		// Initialize the open profile preferences
		if (strCertStore == "1") {
		   if (strLoginChooseTitle[0] != null){
			  document.VSSC.set_UIPrefs_OpenProf_Title(strLoginChooseTitle) ;
			  if ( (ErrorCode = document.VSSC.GetLastError()) != 0) {
	 		     CloseObjects(ErrorCode, "", 0);
				 return ;
			  }
		   }
		   if (strLoginChooseText[0] != null){
			  document.VSSC.set_UIPrefs_OpenProf_Text(strLoginChooseText) ;
			  if ( (ErrorCode = document.VSSC.GetLastError()) != 0) {
			     CloseObjects(ErrorCode, "", 0);
				 return ;
			  }
		   }
		   if (strLoginChooseHelpUrl[0] != null){
			  document.VSSC.set_UIPrefs_OpenProf_HelpUrl(strLoginChooseHelpUrl) ;
			  if ( (ErrorCode = document.VSSC.GetLastError()) != 0) {
				 CloseObjects(ErrorCode, "", 0);
				 return ;
			  }
		   }
		   if (strUnLockHelpUrl[0] != null){
			  document.VSSC.set_UIPrefs_Timeout_HelpUrl(strUnLockHelpUrl) ;
			  if ( (ErrorCode = document.VSSC.GetLastError()) != 0) {
				 CloseObjects(ErrorCode, "", 0);
				 return ;
			  }
		   }
			
			E_CARDALREADYOPEN = 0x8000102F;

			document.VSSC.set_ProfMgmt_ProfileName("<%=account; %>");
			ErrorCode = document.VSSC.GetLastError();
			if ( (ErrorCode != 0) && (ErrorCode != E_CARDALREADYOPEN) ) {
			    CloseObjects(ErrorCode, "", 0);
				return ;
			}

			VSSC.set_ProfMgmt_IsUsernameEditable(false);;
			if ( (ErrorCode = VSSC.GetLastError()) != 0 ) {
				CloseObjects(ErrorCode, "", 0);
				return false;
			}

		   OPENPROF_OPEN_ONLY = 529;
		   document.VSSC.set_ProfMgmt_OpenProfFlags(OPENPROF_OPEN_ONLY) ;
		   if ( ((ErrorCode = document.VSSC.GetLastError()) != 0) && (ErrorCode != E_CARDALREADYOPEN )) {
			  CloseObjects(ErrorCode, "", 0);
			  return ;
		   }

		  if ( (strClientInfo[0] == null) || (strClientInfoSig[0] == null)) {
			  CloseObjects(ErrorCode, "", 0);
			  return false;
		  }

		  document.VSSC.set_RoamPrefs_ClientInfo(strClientInfo);
		  if ( ((ErrorCode = document.VSSC.GetLastError()) != 0 ) && (ErrorCode != E_CARDALREADYOPEN ) ) {
			  CloseObjects(ErrorCode, "", 0);
			  return false;
		  }

		  document.VSSC.set_RoamPrefs_ClientInfoSig(strClientInfoSig);
		  if ( ((ErrorCode = document.VSSC.GetLastError()) != 0 ) && (ErrorCode != E_CARDALREADYOPEN ) ) {
			  CloseObjects(ErrorCode, "", 0);
			  return false;
		  }
		  document.VSSC.set_ProfMgmt_RoamProfile(true);
		  if ( ((ErrorCode = document.VSSC.GetLastError()) != 0 ) && (ErrorCode != E_CARDALREADYOPEN ) ) {
			  CloseObjects(ErrorCode, "", 0);
			  return false;
		  }

		} // done setting open profile preferences


		// set open profile Ok button text to login
		document.VSSC.set_UIPrefs_OpenProf_OKBtnText(125) ;
		if ( (ErrorCode = document.VSSC.GetLastError()) != 0) {
			  CloseObjects(ErrorCode, "", 0);
			  return ;
		}

		// set the select id preferences
		if (strLoginTitle[0] != null){
		  document.VSSC.set_UIPrefs_SelID_Title(strLoginTitle) ;
		  if ( (ErrorCode = document.VSSC.GetLastError()) != 0) {
			  CloseObjects(ErrorCode, "", 0);
			  return ;
		  }
		}

		if (strLoginText[0] != null){
		  document.VSSC.set_UIPrefs_SelID_Text(strLoginText) ;
		  if ( (ErrorCode = document.VSSC.GetLastError()) != 0) {
			CloseObjects(ErrorCode, "", 0);
			return ;
		  }
		}

		document.VSSC.set_UIPrefs_SelID_ShowDefChkBox(true) ;
		if ( (ErrorCode = document.VSSC.GetLastError()) != 0) {
		  CloseObjects(ErrorCode, "", 0);
		  return ;
		}

		if (strAppLogoUrl[0] != null){
		  document.VSSC.set_UIPrefs_UILogoUrl(strAppLogoUrl) ;
		  if ( (ErrorCode = document.VSSC.GetLastError()) != 0) {
			CloseObjects(ErrorCode, "", 0);
			return ;
		  }
		}

		if (strLoginHelpUrl[0] != null){
		  document.VSSC.set_UIPrefs_SelID_HelpUrl(strLoginHelpUrl) ;
		  if ( (ErrorCode = document.VSSC.GetLastError()) != 0) {
			CloseObjects(ErrorCode, "", 0);
			return ;
		  }
		}

		document.VSSC.set_UIPrefs_SelID_OKBtnText(122) ;
		if ( (ErrorCode = document.VSSC.GetLastError()) != 0) {
		  CloseObjects(ErrorCode, "", 0);
		  return ;
		}

		// END suppress the SelectID Dialog box

		// Select the Digital ID now
		if (document.LoginForm.ResetPref && document.LoginForm.ResetPref.checked == true) {
		//   set the new property
			document.VSSC.set_PTA_UseDefCertFlag(0);
		}
		else {
		//   set the new property
			document.VSSC.set_PTA_UseDefCertFlag(1);
		}
		//if ( (ErrorCode = document.VSSC.GetLastError()) != 0) {
		//  CloseObjects(ErrorCode, "", 0);
		//  return ;
		//}

		// The script variable "toSign" gets assigned a value through the
		// Java Script prepended by the NSAPI Filter when the Login Page
		// is sent to the browser.

		MD5 = 3 ;
		SHA1 = 4 ;

		// Get the "Signature"
		// var Signature = new java.lang.StringBuffer() ;
		if (digestAlg == "MD5")
		{
		   Signature = document.VSSC.PTA_SignChallenge (toSign, MD5) ;
		}
		else
		  if (digestAlg == "SHA")
			{
			  Signature = document.VSSC.PTA_SignChallenge(toSign, SHA1) ;
			}
		RetVal = document.VSSC.GetLastError();

		VS_CERTNOMATCHCRIT = 0x80001095;
		VS_CERTMATCHBUTEXP = 0x80001096;
		VS_SUCCESS = 0x00000000;
		VS_PROFDOESNOTEXIST = 0x8000102B;
		VS_USER_CANCELLED = 0x80001067;
		VS_CERTNOTFOUND = 0x80001091;

		if (RetVal != 0) {
			if (RetVal == VS_CERTMATCHBUTEXP ) {
				//alert("You do not have a valid Digital ID. \nNow the PTA will try to renew your expired Digital IDs.");
				CloseObjects(RetVal, "", 0);
				//GoToRenewDigitalIDJava();
				return;
			} else
				if ( (RetVal == VS_CERTNOMATCHCRIT) || (RetVal == VS_PROFDOESNOTEXIST) || (RetVal == VS_CERTNOTFOUND)) {
				//EnrollState = confirm("You do not have a valid Digital ID.\nWould you like to enroll for a Digital ID at this time?") ;
				//if ( EnrollState == true ) {
				//	CloseObjects(0, "", 0);
				//	SignUpJava();
				//	return;
				//}
				CloseObjects(RetVal, "", 0);
				return;

		   } else
		   if (RetVal == VS_USER_CANCELLED) {
				CloseObjects(0, "", 0);
				RedirectToLogin();
				return;
		   } else {
			   CloseObjects(RetVal, "", 0);
			   return;
		   }
		}
		else
		{

		  // Detect here by looking at the Selected cert's Expriy Date if it
		  // is about to expire in ADVANCE_DAYS days.If it is, then ask the user if
		  // he wants to renew the cert which is about to expire OR
		  // he just wants to continue with the login.

		  ADVANCE_DAYS = AbtToExpWindow;

		  var SelExpDate = document.VSSC.get_SelectedDigID_ExpDate() ;
		  if ( (ErrorCode = document.VSSC.GetLastError()) != 0) {
			  CloseObjects(ErrorCode, "", 0);
			  return;
		  }

		  var AdvanceExpDate;

		  if(browserNum < 5) {
			AdvanceExpDate = SelExpDate;
		  } else {
			AdvanceExpDate = new Date();
			AdvanceExpDate.setTime(SelExpDate);
		  }

		  somedate = AdvanceExpDate.getDate() ;
		  somedate = somedate - ADVANCE_DAYS ;
		  AdvanceExpDate.setDate(somedate) ;

		  var isAbtToExp = false;
		  if(browserNum < 5) {
			if ( todaysDate.after(AdvanceExpDate) ) {
				isAbtToExp = true;
			}
		  } else {
			if(todaysDate.getTime() > AdvanceExpDate.getTime()) {
				isAbtToExp = true;
			}
		  }

		  if ( isAbtToExp)
		  {
			// You come here if today's date is after the Advance Exp Date.
			// Therefore, the cert is in the "ABOUT TO EXPIRE" period.
			// alert("Your cert is about to expire ...") ;

			//RenewState = confirm("The Digital ID that you selected is about to expire.\nYou can either choose to continue with this login or you can renew your Digital ID.\nWould you like to renew your Digital ID ?") ;

			alert("The Digital ID that you selected is about to expire.\nYou need to renew your Digital ID.") ;

			RenewState  = false;
			if ( RenewState == true ) {
			  // You come here if the user pressed OK and therefore wants to
			  // renew his Digital ID.
			  RenewDigitalIDJava() ;
			}
			else {
			  // You come here if the user pressed Cancel and therefore wants to
			  // continue with the login.
			  LoginJava() ;
			}
		  }
		  else
		  {
			LoginJava() ;
		  }
		}
	  }
	</SCRIPT>
<% } %>

