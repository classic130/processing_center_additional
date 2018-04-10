<!-- File name: SGMS_EnrollCertificate.htm -->
<%@include file = "TW_DefinedVars.tpl" %>
<%@include file="SGMS_OnSiteHostConfig.tpl" %>

<!-- VSSC ErrorForm -->
<%@include file="SGMS_VSSCErrorFormInclude.tpl" %>

<%
var host = OnSiteHost;
var VSApps = host + "/VSApps";
var imagepathurl = tw.httpGateway.getImgPathUrl();
var table_border_SGMS_EnrollCertificate = 0; //debugging layout

var firstname = (arguments.firstName == "undefined")?tw.session.account.firstname:arguments.firstName;
var lastname = arguments.lastName == "undefined"?tw.session.account.lastname:arguments.lastName;
var address = arguments.address == "undefined"?tw.session.account.address:arguments.address;
var challenge_phrase = arguments.challenge_phrase;

// Set up the name of the form processing file used.
// FIXME!!! - when the new onsite kit arrives, change the filenames to userEnrollMSPPS.fdf and userEnrollNSPPS.fdf
if ( tw.request.userAgentVendor == "microsoft" ) {
	var userEnroll_fileName = "../fdf/VSApps/client/userEnrollMSPPS.fdf";
} else {
	var userEnroll_fileName = "../fdf/VSApps/client/userEnrollNSPPS.fdf";
}

%>

<HTML>
<HEAD>
<META HTTP-EQUIV="PRAGMA" CONTENT="NO-CACHE">
<title>VeriSign PrivatePath service</title>

<%='';%>
<%@include file="SGMS_VSSCDownloadInclude.tpl"%>

<SCRIPT LANGUAGE=JavaScript>
<!--
	// don't call the function below on IE pages
	function ReBaseErrorCodeNS(error_code)
	{
		if (navigator.appName != "Netscape") {
			return error_code;
		}

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
		if (navigator.appName != "Netscape") {
			return error_code;
		}

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

	// don't call the function below on Netscape pages
	function CheckErrorCodeMS(error_code)
	{
		var strErrorCode;
		if (navigator.appName == "Netscape") {
			return error_code; 
		}

		if (error_code >= "80000000") {
			strErrorCode = "7000" + error_code.substring(error_code.length-4, error_code.length);
		} else {
			strErrorCode = error_code;
		}
		return strErrorCode;
	}

	// This is the browser type
	var browserName=navigator.appName;

	// These are the minimum versions supported.
	var requiredBrowserNumMS=3;
	var requiredBrowserNumNS=3;

	// The browser version.
	var browserNum = parseInt(navigator.appVersion);


	if ( browserName == "Netscape" ) {
		if (browserNum < requiredBrowserNumNS ) {
		    SetErrorInfoNS("Enrollment","","0","<%=BrowserStatus;%>",0);
		}
	} else {
		if (browserNum < requiredBrowserNumMS ) {
		    SetErrorInfoMS("Enrollment","","0","<%=BrowserStatus;%>",0);
		}
	}
	//-->
</SCRIPT>

<% if ( tw.request.userAgentVendor == "microsoft" ) { %>

<!-- Scripts for Microsoft IE -->
<SCRIPT LANGUAGE="VBScript">
	<!--
	Function IsIE4
		dim ua 
		dim pos
		dim msie
		dim tmp

		ua = window.navigator.userAgent
		pos = instr(ua, "MSIE 4")

		if pos > 0 then
			tmp = true
		else
			tmp = false
		end if

		IsIE4 = tmp
	End Function

	Function IsIE5
		dim ua
		dim pos
		dim tmp

		ua = Window.navigator.useragent
		pos = instr(ua, "MSIE 5")

		if pos > 0 then
			tmp = true
		else
			tmp = false
		end if

		IsIE5 = tmp
	End Function
	'-->
</SCRIPT>

<SCRIPT LANGUAGE="VBScript">
	<!--
	Dim IVSWin2KSelectedID

	On Error Resume Next
	Set IVSWin2KSelectedID = VSSC.IVSSCPTA.IVSSelectedDigID
	If ( err.number <> 0 ) then
		Call CloseObjects(Hex(err.number), "",0)
	End If
	'-->
</Script>

<SCRIPT LANGUAGE="VBScript">
	<!--
	' the VBSCript variables made available on PTA enrollment pages
	Dim strCertStore
	Dim strAppCtxtName
	Dim strAppLogoUrl
	Dim strNewPasswordTitle
	Dim strNewPasswordText
	Dim strIntroDlgText
	Dim passwordQuality
	Dim passwordLength
	Dim passwordTimeOut
	Dim passwordTries
	Dim passwordUnlockPeriod
	Dim saveLocal
	Dim strClientInfo
	Dim strClientInfoSig

	Dim strNewProfileHelpUrl

	strCertStore = "1"
	strAppCtxtName = "<%=AppContextName; %>"

	strAppLogoUrl = "<%=host;%>/SGMSAppLogo.BMP"

	strNewPasswordTitle = "<%=NewPasswordTitle;%>"
	strNewPasswordText = "<%=NewPasswordText;%>"
	strIntroDlgText="<%=IntroDlgText;%>"

	passwordQuality = "16384"
	passwordLength = "6"
	passwordTimeOut = "10"
	passwordTries = "3"
	passwordUnlockPeriod = "3"
	saveLocal = "disabled"
	strClientInfo =  "<%=strClientInfo;%>"
	strClientInfoSig =  "<%=strClientInfoSig;%>"

	'-- VSSKBEGIN Global/Mode#35#autoauth#1.0.0.0#54892 --
	Dim helpHostName
	helpHostName = "<%=host;%>"
	'-- VSSKEND Global/Mode#35 --

	strNewProfileHelpUrl = helpHostName & "<%=VSApps;%>/client/help/tasks/ptanewprofile.htm"
	'-- VSSKEND Apps/PTAv2#5 --

	'This sub will call the close methods of both the objects  
	Function CloseObjects (ErrorCode, Operation, WinErrorCode)
		On Error Resume Next
		VSSC.IVSSCPTA.Close
		if ( ErrorCode <> 0 ) then
		    Call SetErrorInfoMS("Enrollment","",ErrorCode,"<%=EnrollAppStatus;%>",0)
			Exit Function
		end if 
	End Function

	Function  CreatePKCS10
		On Error Resume Next
		CreatePKCS10 = ""

		If bErrorPresent = 1 Then
			Exit Function
		End If

		SubjectDN = "CN=vsc1enroll"
		HashAlg = CInt(4)

		' Need to handle key exportability and key strength policies
		KeyFlags = &h00000001 'KEY SPEC = AT_KEYEXCHANGE

		KeyFlags = KeyFlags OR 0

		Dim Attributes(2,2)
		Attributes(1,1) = "2.5.29.15"
		Attributes(1,2) = "03020138"
		Attributes(2,1) = "2.5.29.37"
		Attributes(2,2) = "300A06082B06010505070302"

		Dim KeyAttributes
		' for 1024 bit keys
		KeyAttributes = KeyFlags OR &h04000000

		On Error Resume Next
		CreatePKCS10 = VSSC.IVSSCPTA.CreateCertReq (SubjectDN, KeyAttributes, HashAlg, Attributes)
		If ( err.number <> 0 ) then
			Call CloseObjects(Hex(err.number), "",0)
			Exit Function
		End If

	End Function

	Sub DoKeyGen
		Dim boolProfileOpen
		Dim profileName
		Dim theForm 
		Dim AppStatus

		If bErrorPresent = 1 Then
			Exit Sub
		End If

		set theForm = document.proform
		' theForm.Accept.disabled = true
		' open profile etc.


		' Initialize the VSSC ActiveX
		On Error Resume Next
		VSSC.Initialize 0, 0, AppStatus
		
		If ( err.number <> 0 ) then
			Call CloseObjects(Hex(err.number), "",0)
			Exit Sub
		End If

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


		' Initialize the VSSC ActiveX again
		On Error Resume Next
		VSSC.Initialize 0, 0, AppStatus
		
		If ( err.number <> 0 ) then
			Call CloseObjects(Hex(err.number), "",0)
			Exit Sub
		End If
				
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

		' Initialize the PTA Object
		On Error Resume Next
		if (strCertStore = "1") then 
			VSSC.IVSSCPTA.Initialize strAppCtxtName,0
		else
			MsgBox "This is an error in setting policies, the cert store should be verisign"
			Exit Sub
		End If
		If ( err.number <> INITIALIZED And err.number <> 0) then
			Call CloseObjects(Hex(err.number), "",0)
			Exit Sub
		End If

		' Set the UI preferences for the PTA.
		
		On Error Resume Next
		If (Len(strNewPasswordTitle) <> 0) then 
			VSSC.IVSSCPTA.IVSUIPrefs.NewPasswd_Title = strNewPasswordTitle
			If ( err.number <> 0 ) then
				Call CloseObjects(Hex(err.number), "",0)
				Exit Sub
			End If
		End If

		On Error Resume Next
		If (Len(strNewPasswordText) <> 0) then 
			VSSC.IVSSCPTA.IVSUIPrefs.NewPasswd_Text = strNewPasswordText
			If ( err.number <> 0 ) then
				Call CloseObjects(Hex(err.number), "",0)
				Exit Sub
			End If
		End If

		
		On Error Resume Next
		If (Len(strIntroDlgText) <> 0) then 
			VSSC.IVSSCPTA.IVSUIPrefs.IntroDlg_Text = strIntroDlgText
			If ( err.number <> 0 ) then
				Call CloseObjects(Hex(err.number), "",0)
				Exit Sub
			End If
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
		If (Len(strNewProfileHelpUrl) <> 0) then 
			VSSC.IVSSCPTA.IVSUIPrefs.NewPasswd_HelpUrl = strNewProfileHelpUrl
			If ( err.number <> 0 ) then
					Call CloseObjects(Hex(err.number), "",0)
					Exit Sub
			End If
		End If

		'Set WriteOk Domain
		'Dim    strWriteOkDomains(2)
		'strWriteOkDomains(0)="<%=PTAWriteOkDomains;%>"
		'strWriteOkDomains(1)="<%=PTAWriteOkDomains;%>"
		'MsgBox strWriteOkDomains(0)

		'On Error Resume Next
		'VSSC.IVSSCPTA.IVSProfMgmt.WriteOkDomains = strWriteOkDomains
		'If ( err.number <> 0 ) then
		'	Call CloseObjects(Hex(err.number), "",0)
		'	Exit Sub
		'End If

		'-------------------
		
		' Set the password preferences for the profile password.
		On Error Resume Next
		if ( passwordQuality <> "") then
			VSSC.IVSSCPTA.IVSProfMgmt.PasswdQuality = CInt (passwordQuality)
			If ((err.number <> 0) And (Hex(err.number) <> "8000102F") ) Then
				Call CloseObjects(Hex(err.number), "",0)
				Exit Sub
			End If
		End If 

		On Error Resume Next
		if ( passwordLength <> "") then
			VSSC.IVSSCPTA.IVSProfMgmt.PasswdLength = CInt (passwordLength)
			If ((err.number <> 0) And (Hex(err.number) <> "8000102F") ) Then
				Call CloseObjects(Hex(err.number), "",0)
				Exit Sub
			End If
		End If

		On Error Resume Next
		if ( passwordTimeOut <> "") then
			VSSC.IVSSCPTA.IVSProfMgmt.PasswdTimeOut = CInt (passwordTimeOut)
			If ((err.number <> 0) And (Hex(err.number) <> "8000102F") ) Then
				Call CloseObjects(Hex(err.number), "",0)
				Exit Sub
			End If
		End If

		On Error Resume Next
		if ( passwordTries <> "") then
			VSSC.IVSSCPTA.IVSProfMgmt.PasswdLockOutTries = CInt (passwordTries)
			If ((err.number <> 0) And (Hex(err.number) <> "8000102F") ) Then
				Call CloseObjects(Hex(err.number), "",0)
				Exit Sub 
			End If
		End If

		On Error Resume Next
		if ( passwordUnlockPeriod <> "") then
			VSSC.IVSSCPTA.IVSProfMgmt.PasswdUnLockPeriod = CInt (passwordUnlockPeriod)
			If ((err.number <> 0) And (Hex(err.number) <> "8000102F") ) Then
				Call CloseObjects(Hex(err.number), "",0)
				Exit Sub
			End If
		End If

		' Set roaming preferences.
		if ( (strClientInfo = "") Or (strClientInfoSig = "") ) Then
			Call CloseObjects("00000100", "",0)
			Exit Sub
		End If

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

		' Enable roaming profile usage.
		On Error Resume Next
		VSSC.IVSSCPTA.IVSProfMgmt.RoamProfile = CBool(1) 
		If ((err.number <> 0) And (Hex(err.number) <> "8000102F") ) Then
			Call CloseObjects(Hex(err.number), "",0)
			Exit Sub
		End If

		' Set save local property
		On Error Resume Next
		if (saveLocal = "user") Then 
			if (document.proform.usersavelocal(0).checked = true) then
				VSSC.IVSSCPTA.IVSProfMgmt.SaveLocal = CBool(1)
			else
				VSSC.IVSSCPTA.IVSProfMgmt.SaveLocal = CBool(0)
			end if 
		else
			if (saveLocal = "enabled") Then
				VSSC.IVSSCPTA.IVSProfMgmt.SaveLocal = CBool(1)
			else
				VSSC.IVSSCPTA.IVSProfMgmt.SaveLocal = CBool(0)
			end if
		end if
		If ((err.number <> 0) And (Hex(err.number) <> "8000102F") ) Then
			Call CloseObjects(Hex(err.number), "",0)
			Exit Sub
		End If

		' Set the open profile flags
		OPENPROF_CREATE_OR_OPEN = CInt(547)
		OPENPROF_OPEN_ALWAYS = CInt(530)

		On Error Resume Next
		VSSC.IVSSCPTA.IVSProfMgmt.OpenProfFlags = OPENPROF_CREATE_OR_OPEN
		If ((err.number <> 0) And (Hex(err.number) <> "8000102F") ) Then
			Call CloseObjects(Hex(err.number), "",0)
			Exit Sub
		Else
			If (Hex(err.number) = "8000102F") Then 
				boolProfileOpen = 1
			Else
				boolProfileOpen = 0
			End If 
		End If

		' Use the email as the default profile name.
		profileName = theForm.mail_email.value

		On Error Resume Next
		if ( profileName <> "") then
			VSSC.IVSSCPTA.IVSProfMgmt.ProfileName = profileName
			If ((err.number <> 0) And (Hex(err.number) <> "8000102F") ) Then
				Call CloseObjects(Hex(err.number), "",0)
				Exit Sub
			End If
		End If

		On Error Resume Next
		VSSC.IVSSCPTA.IVSProfMgmt.IsUsernameEditable = CBool(0)
		If (err.number <> 0 ) Then
			Call CloseObjects(Hex(err.number), "",0)
			Exit Sub
		End If

			
		' Create the PKCS10 key and store it in the form.
		theForm.public_key.value = CreatePKCS10()

		if (Hex(err.number) = "80001067" ) Then 
			Call CloseObjects(Hex(err.number), "", 0)
			'MsgBox "You have cancelled the operation at this time. Click Accept again if you want to continue with the enrollment."
			Exit Sub
		End if 
		If (err.number <> 0) Then
			Call CloseObjects(Hex(err.number), "",0)
			Exit Sub
		End If

		' Close the PTA.
		Call CloseObjects(0, "", 0)

		' Set the public key and submit the form.
		if Len(theForm.public_key.value) = 0 then
			Call CloseObjects(Hex(err.number), "",0)
			Exit Sub
		else
			theForm.submit
		end If
	End Sub
	'-->
</SCRIPT>

<% } else { %>

<!-- Scripts for Netscape Navigator -->
<SCRIPT LANGUAGE="Javascript">
	<!--
	// The JavaScript variables made available on PTA enrollment pages
	var strCertStore = "1";
	var strAppCtxtName = "<%=AppContextName; %>";
	
	strAppLogoUrl = "<%=host;%>/SGMSAppLogo.BMP"
	
	var strNewPasswordTitle = "<%=NewPasswordTitle;%>";
	var strNewPasswordText = "<%=NewPasswordText;%>";
	var strIntroDlgText="<%=IntroDlgText;%>";

	var passwordQuality = "16384";
	var passwordLength = "6";
	var passwordTimeOut = "10";
	var passwordTries = "3";
	var passwordUnlockPeriod = "3";
	var saveLocal = "disabled";
	var strClientInfo = "<%=strClientInfo;%>";
	var strClientInfoSig = "<%=strClientInfoSig;%>";

	//-- VSSKBEGIN Global/Mode#36#autoauth#1.0.0.0#54892 --
	var helpHostName = "<%=host;%>";
	//-- VSSKEND Global/Mode#36 --

	var strNewProfileHelpUrl = helpHostName + "<%=VSApps;%>/client/help/tasks/ptanewprofile.htm";
	//-- VSSKEND Apps/PTAv2#6 --

	function CloseObjects(errCode, Operation, WinErrorCode) {
		RetVal = VSSC.PTA_Close();
		if (errCode != 0) {
		    SetErrorInfoNS("Enrollment","",ConvertToHexNS(errCode),"<%=EnrollAppStatus;%>",0);
			return;
		}
	}

	function CreatePKCS10() {
		var PKCS10;
		var KeyFlags = 0x00000001;  // to generate AK_KEYEXCHANGE  keys
		var SubjectDN = "CN=vsc1enroll";
		var HashAlg = 4;   // SHA1 as hash algorithm
		var theArray;

		if(browserNum < 5) {
			PKCS10 = new java.lang.StringBuffer("");
		} else {
			PKCS10 = new String("");
		}

		if(bErrorPresent == 1)
			return;

		if(browserNum < 5) {
			theClass = java.lang.Class.forName("java.lang.String")
			theArray = java.lang.reflect.Array.newInstance(theClass, 4);
			var temp = java.lang.String("2.5.29.15");
			java.lang.reflect.Array.set(theArray, 0, temp);
			temp = java.lang.String("03020138");
			java.lang.reflect.Array.set(theArray, 1, temp);
			temp = java.lang.String("2.5.29.37");
			java.lang.reflect.Array.set(theArray, 2, temp);
			temp = java.lang.String("300A06082B06010505070302");
			java.lang.reflect.Array.set(theArray, 3, temp);
		} else {
			theArray = new Array(4);
			theArray[0] = "2.5.29.15";
			theArray[1] = "03020138";
			theArray[2] = "2.5.29.37";
			theArray[3] = "300A06082B06010505070302";
		}

		KeyFlags = KeyFlags | 0;

		// generate the public key

		var KeyAttributes;
		KeyAttributes = 0x04000000 | KeyFlags;
		
		if(browserNum < 5) {
			PKCS10 = VSSC.PTA_CreateCertReq(SubjectDN, KeyAttributes, HashAlg, theArray) ;
		} else {
			PKCS10 = VSSC.PTA_CreateCertReq(SubjectDN, KeyAttributes, HashAlg, 4, theArray) ;
		}

		if ( (ErrorCode = VSSC.GetLastError()) != 0) {
			CloseObjects(ErrorCode, "", 0);
			return (PKCS10);
		}

		return (PKCS10);
	}


	function DoKeyGen() {
		var boolProfileOpen;
		var profileName;

		if(bErrorPresent == 1)
			return;

		if (VSSC == null) {
			CloseObjects("00000101", "", 0);
			return;
		}

		// Initialize the VSSC first.
		var AppStatus = new java.lang.StringBuffer("");
/*
		VSSC.VSSC_Initialize(0, 0, AppStatus) ;
		if ( (ErrorCode = VSSC.GetLastError()) != 0) {
			//CloseObjects(ErrorCode, "Enroll::VSSC.Initialize", ErrorCode);
			CloseObjects(ErrorCode, "", 0);
			return false;
		}
*/

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

		// Initialize VSSC again
		count = 1;
		VSSC.VSSC_Initialize(0,0, AppStatus);
		while(true)
		{
			ErrorCode=VSSC.GetLastError();
			if(ErrorCode == VSSC_PLUGIN_NOT_INITIALIZED)
			{
				
				VSSC.VSSC_Initialize(0,0, AppStatus);
				count ++;
			}
			else
			{
				
				break;
			}

		}
		// Only for Debug, remove this later
		//alert("Times VSSC_Initialize Called = " + count);

		ErrorCode=VSSC.GetLastError();
		if(ErrorCode != 0 && ErrorCode != VSSC_INITIALIZED)
		{
			CloseObjects(ErrorCode, "", 0);
			return;
		}

		//Set the list of PTA versions supported by VSSC
		VSSC.set_VSSC_SupportedPTAVer(SupportedVer);
		ErrorCode=VSSC.GetLastError();
		
		if(ErrorCode == DIFFERENT_PTAVER)
		{
			//InstalledVer = VSSC.get_VSSC_InstalledPTAVer();
			CloseObjects(ErrorCode, "", 0);
			return;	
		}
		else if(ErrorCode)
		{
			CloseObjects(ErrorCode, "", 0);
			return;
		}

		// Initialize the PTA component of the VSSC
		if (strCertStore == "1") {
			VSSC.PTA_Initialize(strAppCtxtName, 0) ;
		}
		else {
			VSSC.PTA_Initialize(strAppCtxtName, 1) ;
		}	
		if ( (ErrorCode = VSSC.GetLastError()) != 0) {
			CloseObjects(ErrorCode, "", 0);
			return false;
		}

		if (strNewPasswordTitle[0] != null){
			VSSC.set_UIPrefs_NewPasswd_Title(strNewPasswordTitle) ;
			if ( (ErrorCode = VSSC.GetLastError()) != 0) {
				CloseObjects(ErrorCode, "", 0);
				return false;
			}
		}

		if (strNewPasswordText[0] != null){
			VSSC.set_UIPrefs_NewPasswd_Text(strNewPasswordText) ;
			if ( (ErrorCode = VSSC.GetLastError()) != 0) {
				CloseObjects(ErrorCode, "", 0);
				return false;
			}
		}

		if (strIntroDlgText[0] != null){
			VSSC.set_UIPrefs_IntroDlg_Text(strIntroDlgText) ;
			if ( (ErrorCode = VSSC.GetLastError()) != 0) {
				CloseObjects(ErrorCode, "", 0);
				return false;
			}
		}


		if (strAppLogoUrl[0] != null){
			VSSC.set_UIPrefs_UILogoUrl(strAppLogoUrl) ;
			if ( (ErrorCode = VSSC.GetLastError()) != 0) {
				CloseObjects(ErrorCode, "", 0);
				return false;
			}
		}

		if (strNewProfileHelpUrl[0] != null){
			VSSC.set_UIPrefs_NewPasswd_HelpUrl(strNewProfileHelpUrl) ;
			if ( (ErrorCode = VSSC.GetLastError()) != 0) {
				CloseObjects(ErrorCode, "", 0);
				return false;
			}
		}

		E_CARDALREADYOPEN = 0x8000102F;

		if (!isNaN(parseInt(passwordQuality))){
			VSSC.set_ProfMgmt_PasswdQuality(parseInt(passwordQuality)) ;
			if ( ((ErrorCode = VSSC.GetLastError()) != 0) && (ErrorCode != E_CARDALREADYOPEN )) {
				CloseObjects(ErrorCode, "", 0);
				return false;
			}
		}

		if (!isNaN(parseInt(passwordLength))){
			VSSC.set_ProfMgmt_PasswdLength(parseInt(passwordLength)) ;
			if ( ((ErrorCode = VSSC.GetLastError()) != 0 ) && (ErrorCode != E_CARDALREADYOPEN ) ) {
				CloseObjects(ErrorCode, "", 0);
				return false;
			}
		}

		if (!isNaN(parseInt(passwordTimeOut))){
			VSSC.set_ProfMgmt_PasswdTimeOut(parseInt(passwordTimeOut)) ;
			if ( ((ErrorCode = VSSC.GetLastError()) != 0 ) && (ErrorCode != E_CARDALREADYOPEN ) ) {
				CloseObjects(ErrorCode, "", 0);
				return false;
			}
		}

		if (!isNaN(parseInt(passwordTries))){
			VSSC.set_ProfMgmt_PasswdLockOutTries(parseInt(passwordTries)) ;
			if ( ((ErrorCode = VSSC.GetLastError()) != 0 ) && (ErrorCode != E_CARDALREADYOPEN ) ) {
				CloseObjects(ErrorCode, "", 0);
				return false;
			}
		}

		if (!isNaN(parseInt(passwordUnlockPeriod))){
			VSSC.set_ProfMgmt_PasswdUnLockPeriod(parseInt(passwordUnlockPeriod)) ;
			if ( ((ErrorCode = VSSC.GetLastError()) != 0 ) && (ErrorCode != E_CARDALREADYOPEN ) ) {
				CloseObjects(ErrorCode, "", 0);
				return false;
			}
		}

		if ( (strClientInfo[0] == null) || (strClientInfoSig[0] == null)) {
			CloseObjects("100", "", 0);
			return false;
		}

		VSSC.set_RoamPrefs_ClientInfo(strClientInfo);
		if ( ((ErrorCode = VSSC.GetLastError()) != 0 ) && (ErrorCode != E_CARDALREADYOPEN ) ) {
			CloseObjects(ErrorCode, "", 0);
			return false;
		}

		VSSC.set_RoamPrefs_ClientInfoSig(strClientInfoSig);
		if ( ((ErrorCode = VSSC.GetLastError()) != 0 ) && (ErrorCode != E_CARDALREADYOPEN ) ) {
			CloseObjects(ErrorCode, "", 0);
			return false;
		}

		VSSC.set_ProfMgmt_RoamProfile(true);
		if ( ((ErrorCode = VSSC.GetLastError()) != 0 ) && (ErrorCode != E_CARDALREADYOPEN ) ) {
			CloseObjects(ErrorCode, "", 0);
			return false;
		}

		if (saveLocal == "user") {
			if (document.proform.usersavelocal[0].checked) {
				VSSC.set_ProfMgmt_SaveLocal(true);
			} else {
				VSSC.set_ProfMgmt_SaveLocal(false);
			}
		} else {
			if (saveLocal == "enabled") {
				VSSC.set_ProfMgmt_SaveLocal(true);
			} else {
				VSSC.set_ProfMgmt_SaveLocal(false);
			}
		}
		if ( ((ErrorCode = VSSC.GetLastError()) != 0 ) && (ErrorCode != E_CARDALREADYOPEN ) ) {
			CloseObjects(ErrorCode, "", 0);
			return false;
		}

		OPENPROF_CREATE_OR_OPEN = 547;
		OPENPROF_OPEN_ALWAYS = 530;
		VSSC.set_ProfMgmt_OpenProfFlags(OPENPROF_CREATE_OR_OPEN) ;
		if ( ((ErrorCode = VSSC.GetLastError()) != 0) && (ErrorCode != E_CARDALREADYOPEN )) {
			CloseObjects(ErrorCode, "", 0);
			return false;
		} else if ( ErrorCode == E_CARDALREADYOPEN ) {
			boolProfileOpen = 1;
		} else {
			boolProfileOpen = 0;
		}

		// Use the email as the default profile name.
		profileName = document.proform.mail_email.value

		if (profileName[0] != null) {
			//set the profile name
			VSSC.set_ProfMgmt_ProfileName(profileName) ;
			if ( ((ErrorCode = VSSC.GetLastError()) != 0  ) && (ErrorCode != E_CARDALREADYOPEN )) {
				CloseObjects(ErrorCode, "", 0);
				return false;
			}
		}

		VSSC.set_ProfMgmt_IsUsernameEditable(false);;
		if ( (ErrorCode = VSSC.GetLastError()) != 0 ) {
			CloseObjects(ErrorCode, "", 0);
			return false;
		}

		// Create the PKCS10 key and store it in the form.
		document.proform.public_key.value = CreatePKCS10();

		ErrorCode = VSSC.GetLastError();
		if (ErrorCode == 0x80001067) {
			CloseObjects(ErrorCode, "", 0);
			//alert ("You have cancelled this operation at this time. Click Accept again if you want to enroll.");
			return false;
		} else if (ErrorCode != 0) {
			CloseObjects(ErrorCode, "", 0);
			return false;
		}

		// Close the PTA.
		CloseObjects(0, "", 0);

		// Set the public key and submit the form.
		if ( document.proform.public_key.length == 0 ){
			CloseObjects(ErrorCode, "", 0);
			return false;
		} else {
			document.proform.submit();
		}

		return true;
	}
	//-->
</SCRIPT>
<% } %>

<SCRIPT LANGUAGE="JavaScript">
	<!--
	function submitForm() {
		DoKeyGen();
	}
	//-->
</script>

<LINK REL="stylesheet" HREF="<%=tw.httpGateway.getStylesheetPathUrl();%>/verisign.css">
</HEAD>

<BODY ONLOAD="javascript:submitForm();" BGCOLOR="#ffffff" BACKGROUND="<%=imagepathurl;%>/background.gif" LEFTMARGIN="0" TOPMARGIN="0"  MARGINWIDTH="0" MARGINHEIGHT="0" NAME="main">

	<FORM NAME=ErrorForm1 ACTION="<%=host;%>/cgi-bin/softbounce.exe" METHOD=POST>
		<INPUT type=hidden NAME=form_file VALUE="../fdf/VSApps/client/DefaultError.fdf">
		<INPUT type=hidden NAME=errorCode VALUE=0>
		<INPUT type=hidden NAME=winerrorcode VALUE=0>
		<INPUT type=hidden NAME=operation VALUE="">
		<INPUT type=hidden NAME=showError VALUE="">
	</FORM>

	<TABLE border="<%=table_border_SGMS_EnrollCertificate;%>" CELLPADDING="0" CELLSPACING="0" WIDTH="100%" ALIGN="TOP">
		<!-- VeriSign logo -->
		<tr>
			<td rowspan="1" valign="top" width="150" height="84"><img name="logo" src="<%=imagepathurl;%>/verisign.gif" width="150" height="84" border="0"></td>
			<td colspan="3" height="84" valign="top" nowrap background="<%=imagepathurl;%>/hd_home.gif" bgcolor="#d8d7b8"><BR><BR>&nbsp;&nbsp;<br>&nbsp;&nbsp;
			<span class="bigblue">Enroll for Digital ID - step 2 of 3</span>
			</td>
		</tr>
		<TR valign="top">
			<!-- left nav bar -->
			<td rowspan="1" height="360">
				<table width="100%" cellspacing="0" cellpadding="0" border="<%=table_border_SGMS_EnrollCertificate;%>">
				<tr valign="top">
					<td valign="top" background="<%=imagepathurl;%>/nav_background.gif" height="360">
						<br><br><br>
						&nbsp;&nbsp;&nbsp;<img src="<%=imagepathurl;%>/arrow.gif">
						<A href="" class="nav">Enroll for Digital ID</A><br>
					</td>
				</tr>
				</table>
			</td>
			<!-- left vertical spacer -->
			<TD rowspan="1" width="20"><IMG src="<%=imagepathurl;%>/spacer.gif" width="20"></TD>
			<TD height="400" width="100%">
				<TABLE height="100%" width="1" cellspacing="0" cellpadding="0" border="<%=table_border_SGMS_EnrollCertificate;%>">
				  <TR>
				    <!-- horizontal spacer -->
				    <TD colspan="1" height="20" valign="TOP" bgcolor="#ffffff">
				      <IMG src="<%=imagepathurl;%>/spacer.gif" height="20">
				      <noscript>
					<BR>
					<center>
					  <font color='#ff0000' face='Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular' size='-1'>
					    <b>Many features on this page will not operate as this browser does not support Javascript.</b>
					  </font>
					</center>
				      </noscript>
				    </TD>
				    <!-- right vertical spacer -->
				    <TD rowspan="3" width="20"><IMG src="<%=imagepathurl;%>/spacer.gif" width="20"></TD>
				  </TR>
				  <TR>
				    <TD valign="top">

					<TABLE width="600" border="<%=table_border_SGMS_EnrollCertificate;%>" cellspacing="1" cellpadding="2" bgcolor="#d8d7b8">
					  <TR>
					    <TD nowrap>
					      &nbsp;<IMG src="<%=imagepathurl;%>/arrow_red_blank.gif">&nbsp;
					      <FONT color="#000066"><B>Step 1: Complete the enrollment form</B></FONT>
					    </TD>
					  </TR>
					  <TR>
					    <TD>
					      &nbsp;<IMG src="<%=imagepathurl;%>/arrow_red.gif">&nbsp;
					      <FONT color="#000066"><B>Step 2: Create your PTA profile</B></FONT>
					    </TD>
					  </TR>
					  <TR>
					    <TD>
					      &nbsp;<IMG src="<%=imagepathurl;%>/arrow_red_blank.gif">&nbsp;
					      <FONT color="#000066"><B>Step 3: Receive your Digital ID</B></FONT>
					    </TD>
					  </TR>
					</TABLE>
					<BR><b>Create your PTA profile.</b><BR>


<!-- Navigation bar include -->
	    </td>
	  </tr>
	  <tr>
	    <td colspan="1" nowrap valign="bottom">
	      <script language="javascript">
		
		function copyright ()
		{
		//Create a new window
		var newWin = window.open("legaldocs/copyright.htm", "popup_1", 'toolbar=1,location=0,directories=0,status=0,menubar=0,scrollbars=1,resizable=0,width=620,height=375'); 		
		}
	
		function privacy ()
		{
		//Create a new window
		var newWin = window.open("legaldocs/privacy.htm", "popup_1", 'toolbar=1,location=0,directories=0,status=0,menubar=0,scrollbars=1,resizable=0,width=620,height=375'); 	
		}
	      </script>
	      <IMG src="<%=imagepathurl;%>/dot.gif" height="80"><BR>
	      <a href="javascript:copyright();"><span class="copyrt">Copyright &#169; 2001,</span></a>
	      &nbsp;<a href="javascript:privacy();"><span class="copyrt">Privacy Policy,</span></a><span class="copyrtblack"> VeriSign, Inc. All Rights Reserved<br></span>
	      <BR><BR>
	    </td>
	  <tr>
	</table>
    </td>
  </tr>
</table>
<!-- End Navigation Bar Include  -->

	<FORM NAME="proform" ACTION="<%=host;%>/cgi-bin/softbounce.exe" ENCTYPE=x-www-form-encoded METHOD="POST">
		<INPUT TYPE=hidden NAME=operation VALUE="AutoAuthOSUserSubmit">
		<INPUT TYPE=hidden NAME=authenticate VALUE="NO">
		<INPUT TYPE=hidden NAME=additional_field4 VALUE="VeriSignSGMS">
		<!-- BBI: this file path is relative to the cgi-bin on the file system, not to the HTTP server's root -->
		<!-- FIXME !!! when the new onsite kit arrives, change the filename to enroll_waitPPS.htm -->
		<INPUT TYPE=hidden NAME=VHTML_FILE VALUE="../htmldocs/VSApps/client/enroll_waitPPS.htm">

		<!--
		<INPUT TYPE=hidden NAME=remote_host VALUE="<%=host;%>/cgi-bin/haydn.exe">
		-->

		<INPUT TYPE=hidden NAME=form_file VALUE="<%=userEnroll_fileName;%>">
		<INPUT TYPE=hidden NAME=public_key VALUE="">

<SCRIPT LANGUAGE="JavaScript">
	if (browserNum < 4) {
		document.write("<INPUT NAME='mail_firstName' VALUE='<%=firstname;%>' TYPE='hidden' SIZE='20' MAXLENGTH='30'>")
		document.write("<INPUT NAME='mail_lastName' VALUE='<%=lastname;%>' TYPE='hidden' SIZE='20' MAXLENGTH='30'>")
		document.write("<INPUT NAME='mail_email' VALUE='<%=address;%>' TYPE='hidden' SIZE='20' MAXLENGTH='230'>")
		document.write("<INPUT NAME='challenge' VALUE='<%=challenge_phrase;%>' TYPE='hidden' SIZE='20' MAXLENGTH='32'>")
	} else {
		document.write("<INPUT NAME=\'mail_firstName\' VALUE=\"<%=firstname;%>\" TYPE=\"hidden\" SIZE=\"20\" MAXLENGTH=\"30\">")
		document.write("<INPUT NAME=\'mail_lastName\' VALUE=\"<%=lastname;%>\" TYPE=\"hidden\" SIZE=\"20\" MAXLENGTH=\"30\">")
		document.write("<INPUT NAME=\"mail_email\" VALUE=\"<%=address;%>\" TYPE=\"hidden\" SIZE=\"20\" MAXLENGTH=\"230\">")
		document.write("<INPUT NAME=\"challenge\" VALUE=\"<%=challenge_phrase;%>\" TYPE=\"hidden\" SIZE=\"20\" MAXLENGTH=\"32\">")
	}
</SCRIPT>

		<INPUT TYPE=HIDDEN NAME="additional_field3" VALUE="">
	</FORM>
</BODY>
</HTML>
