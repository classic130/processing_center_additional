<%@include file="TW_HelperAccFolders.tpl" %>
<%@include file="SGMS_OnSiteHostConfig.tpl" %>
<%@include file="SGMS_VSSCDownloadInclude.tpl"%>
<SCRIPT LANGUAGE="javascript">

function sg(a,a2,a3)
{
	var r='';
	while (a.indexOf(a2)!=-1) {
		var v1=a.indexOf(a2);
		r+=a.substring(0,v1)+a3;
		a=a.substring(v1+a2.length);
	}
	return r+a;
}

function escapeHTML(a)
{
	a=sg(a,'&','&amp;');
	a=sg(a,'<','&lt;');
	a=sg(a,'>','&gt;');
	a=sg(a,'"','&quot;');
	a = sg(a,'\n','<BR>');  // Convert newlines to HTML line breaks (Unix, Windows, DOS).
	return a;
}
</SCRIPT>

<%
	imagepathurl = tw.httpGateway.getImgPathUrl();
	var txt_valid = "<img src='" + imagepathurl + "/encrypt.gif'>&nbsp;" + "Encrypted" + "&nbsp;&nbsp;&nbsp;&nbsp;<img src='" + imagepathurl + "/sign.gif'> " + "Digitally Signed";
	var txt_invalid = "<img src='" + imagepathurl + "/encrypt.gif'>&nbsp;" + "Encrypted" + "&nbsp;&nbsp;&nbsp;&nbsp;<img src='" + imagepathurl + "/sign.gif'> " + "Digitally Signed";
	var txt_not_signed = "<img src='" + imagepathurl + "/encrypt.gif'>&nbsp;" + "Encrypted";

	
	var inbox_id = getInboxFolderId();

	var getinbox_url = tw.httpGateway.getUrl('TW_AccDeliveryFolderView.tpl');
	getinbox_url=tw.httpGateway.appendUrlQueryVariable( getinbox_url,
										   tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_FOLDER_ID,
										   inbox_id );
	


%>

<% if( tw.request.userAgentVendor == "microsoft" ) { %>
	<!-- SGMS_VSSCDecomposeInclude: IE compatible functions -->

	<SCRIPT LANGUAGE="VBScript">

		' msg_type=2 (encrypted) or 3 (encrypted&signed)
		Function DecomposeSMIME(smime_url, msg_type)
			Dim AppStatus

			If bErrorPresent = 1 Then
				Exit Function
			End If

			VSSC_PTA_CANCEL = &h80001067

			On Error Resume Next
			VSSC.InternetInitialize smime_url, "GET", "", AppStatus
			If (err.number <> 0) Then
				Call SetErrorInfoMS("Decompose Operation","",CStr(hex(err.number)),CStr(hex(AppStatus)),0)
				exit Function
			End If

			On Error Resume Next
			VSSC.InternetSendRequest AppStatus
			If (err.number <> 0) Then
				Call SetErrorInfoMS("Decompose Operation","",CStr(hex(err.number)),CStr(hex(AppStatus)),0)
				exit Function
			End If

			On Error Resume Next
			VSSC.UseInternetData=CBool(1)
			If (err.number <> 0) Then
				Call SetErrorInfoMS("Decompose Operation","",CStr(hex(err.number)),"<%=DecomposeAppStatus;%>",0)
				exit Function
			End If

			Dim msg, bStatus
			msg = ""
			
			On Error Resume Next
			VSSC.MsgType = msg_type
			If (err.number <> 0) Then
				Call SetErrorInfoMS("Decompose Operation","",CStr(hex(err.number)),"<%=DecomposeAppStatus;%>",0)
				exit Function
			End If

			On Error Resume Next
			VSSC.CertResolveURL = "<%=CertResolveURL;%>"
			If (err.number <> 0) Then
				Call SetErrorInfoMS("Decompose Operation","",CStr(hex(err.number)),"<%=DecomposeAppStatus;%>",0)
				exit Function
			End If

		
			On Error Resume Next
			VSSC.SCType = "<%=SCType;%>"
			If (err.number <> 0) Then
				Call SetErrorInfoMS("Decompose Operation","",CStr(hex(err.number)),"<%=DecomposeAppStatus;%>",0)
				exit Function
			End If


			'Use the follwoing method to use the certificate either from the message (value 1) or get it from verisign directory (value 0). In case of SGMS, it should be always 1.
			On Error Resume Next
			VSSC.UsePKCS7Certificate=CBool(1)
			If (err.number <> 0) Then
				Call SetErrorInfoMS("Decompose Operation","",CStr(hex(err.number)),"<%=DecomposeAppStatus;%>",0)
				exit Function
			End If

			'The data downloaded is not URLEncoded.
			On Error Resume Next
			VSSC.URLEncodeData=CBool(0)
			If (err.number <> 0) Then
				Call SetErrorInfoMS("Decompose Operation","",CStr(hex(err.number)),"<%=DecomposeAppStatus;%>",0)
				exit Function
			End If

			On Error Resume Next
			VSSC.Decompose msg, AppStatus
			If (err.number <> 0) Then
				if(err.number = VSSC_PTA_CANCEL) Then
					self.location = "<%=getinbox_url;%>"
					exit Function
				else
					
					Call SetErrorInfoMS("Decompose Operation","",CStr(hex(err.number)),CStr(hex(AppStatus)),0)
					exit Function
				end if

				
				
			End If

			'true or false
			On Error Resume Next
			DecomposeSMIME = VSSC.CryptStatus
			If (err.number <> 0) Then
				Call SetErrorInfoMS("Decompose Operation","",CStr(hex(err.number)),"<%=DecomposeAppStatus;%>",0)
				exit Function
			End If

			' build attachments table
			' TODO: move in external function
			Dim szFile, Pos, szFileNameList
			On Error Resume Next
			szFileNameList = VSSC.AttachedFileList
			If (err.number <> 0) Then
				Call SetErrorInfoMS("Decompose Operation","",CStr(hex(err.number)),"<%=DecomposeAppStatus;%>",0)
				exit Function
			End If

			nLen=Len(szFileNameList)
			If nLen <> 0 Then
				Delimiter= ","
				szFileNameList =Delimiter & szFileNameList
				DelLen = Len(Delimiter)
				CurPos = 1
				NextPos = InStr(CurPos+DelLen, szFileNameList, Delimiter)
				Do Until NextPos = 0
					szFile=Mid(szFileNameList, CurPos + DelLen, NextPos - CurPos - DelLen)
					addAtachment(szFile)
					CurPos = NextPos
					NextPos = InStr(CurPos + DelLen, szFileNameList, Delimiter)
				Loop
			End if

		End Function

		' Initialize VSSC
		Function InitVSSC
			messageId = 0
			OBJECT_NODE_NOT_FOUND =	&h80005002

			If bErrorPresent = 1 Then
				Exit Function
			End If

			On Error Resume Next	
			If ( messageId = 0 ) Then
				VSSC.ClearAll 1, AppStatus
				If (err.number <> 0 And err.number <> OBJECT_NODE_NOT_FOUND) Then
					Call SetErrorInfoMS("Decompose Operation","",CStr(hex(err.number)),CStr(hex(AppStatus)),0)
					Exit Function
				End If
			End IF

			Dim AppStatus
			On Error Resume Next
			VSSC.Initialize messageID, 0, AppStatus
			If (err.number <> 0) Then
				Call SetErrorInfoMS("Decompose Operation","",CStr(hex(err.number)),CStr(hex(AppStatus)),0)
				Exit Function
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
				Call SetErrorInfoMS("Decompose Operation","",CStr(hex(err.number)),"<%=DecomposeAppStatus;%>",0)
				Exit Function	
			Else If (err.number) then
				Call SetErrorInfoMS("Decompose Operation","",CStr(hex(err.number)),"<%=DecomposeAppStatus;%>",0)
				Exit Function
			End If
			End If

			'Setting the time out to 35 minutes. Configurable.
			On Error Resume Next
			VSSC.CertificateTimeOut = <%=VSSCCertificateTimeout;%>
			If (err.number <> 0) Then
				Call SetErrorInfoMS("Decompose Operation","",CStr(hex(err.number)),"<%=DecomposeAppStatus;%>",0)
				Exit Function
			End if

			On Error Resume Next
			VSSC.MessageTimeOut = <%=VSSCMessageTimeout;%>
			If (err.number <> 0) Then
				Call SetErrorInfoMS("Decompose Operation","",CStr(hex(err.number)),"<%=DecomposeAppStatus;%>",0)
				Exit Function
			End if

			ConfigurePTA
		End Function


		Sub  ConfigurePTA
			Dim szClientInfo, szClientInfoSig
			Dim IVSPTA
			Dim IVSProfMgmt
			Dim IVSUIPrefs
			Dim IVSRoamPrefs
			Dim szAppContextName
			Dim szAppLogoUrl

			If bErrorPresent = 1 Then
				Exit Sub
			End If

			szClientInfo = "<%=strClientInfo;%>"
			szClientInfoSig = "<%=strClientInfoSig;%>"

			szAppContextName="<%=AppContextName; %>"
			szAppLogoUrl = "<%=OnSiteHost;%>/SGMSAppLogo.BMP"

			
			On Error Resume Next
			Set IVSPTA=VSSC.IVSSCPTA
			If (err.number <> 0) Then
				Call SetErrorInfoMS("Decompose Operation","",CStr(hex(err.number)),"<%=DecomposeAppStatus;%>",0)
				Exit Sub
			End if

			On Error Resume Next
			Set IVSProfMgmt = IVSPTA.IVSProfMgmt
			If (err.number <> 0) Then
				Call SetErrorInfoMS("Decompose Operation","",CStr(hex(err.number)),"<%=DecomposeAppStatus;%>",0)
				Exit Sub
			End if

			On Error Resume Next
			Set IVSUIPrefs = IVSPTA.IVSUIPrefs
			If (err.number <> 0) Then
				Call SetErrorInfoMS("Decompose Operation","",CStr(hex(err.number)),"<%=DecomposeAppStatus;%>",0)
				Exit Sub
			End if

			On Error Resume Next
			Set IVSRoamPrefs=IVSPTA.IVSRoamPrefs
			If (err.number <> 0) Then
				Call SetErrorInfoMS("Decompose Operation","",CStr(hex(err.number)),"<%=DecomposeAppStatus;%>",0)
				Exit Sub
			End if
			
			'**Initialize PTA
			On Error Resume Next
			IVSPTA.Initialize szAppContextName,0
			If (err.number <> 0) Then
				Call SetErrorInfoMS("Decompose Operation","",CStr(hex(err.number)),"<%=DecomposeAppStatus;%>",0)
				Exit Sub
			End if
			'**Setting AppLogo
			
			On Error Resume Next
			IVSUIPrefs.UILogoUrl = szAppLogoUrl
			If (err.number <> 0) Then
				Call SetErrorInfoMS("Decompose Operation","",CStr(hex(err.number)),"<%=DecomposeAppStatus;%>",0)
				Exit Sub
			End if
			
			'**Setting Roaming Properties
			On Error Resume Next
			IVSRoamPrefs.ClientInfo=szClientInfo
			If (err.number <> 0) Then
				Call SetErrorInfoMS("Decompose Operation","",CStr(hex(err.number)),"<%=DecomposeAppStatus;%>",0)
				Exit Sub
			End if

			On Error Resume Next
			IVSRoamPrefs.ClientInfoSig=szClientinfoSig
			If (err.number <> 0) Then
				Call SetErrorInfoMS("Decompose Operation","",CStr(hex(err.number)),"<%=DecomposeAppStatus;%>",0)
				Exit Sub
			End if
			
			On Error Resume Next
			IVSProfMgmt.RoamProfile = CBool(1) 
			If (err.number <> 0) Then
				Call SetErrorInfoMS("Decompose Operation","",CStr(hex(err.number)),"<%=DecomposeAppStatus;%>",0)
				Exit Sub
			End if

			On Error Resume Next
			VSSC.IVSSCPTA.IVSProfMgmt.IsUsernameEditable = CBool(0)
			If (err.number <> 0) Then
				Call SetErrorInfoMS("Decompose Operation","",CStr(hex(err.number)),"<%=DecomposeAppStatus;%>",0)
				Exit Sub
			End if

			'**************PTA	

		End Sub


	Function SaveAttachment(filename)
		Dim vs_Status
		On Error Resume Next
		VSSC.SaveAttachment filename,vs_Status
		If err.number <> 0 Then
			Call SetErrorInfoMS("Decompose Operation","",CStr(hex(err.number)),"<%=DecomposeAppStatus;%>",0)
			Exit Function
		End if
	End Function


	Function ResolveCryptStatus( crypt_status, msg_type )
		If( msg_type = 2 ) Then
			' Not signed
			ResolveCryptStatus = "<%=txt_not_signed;%>"
		ElseIf crypt_status = 0 Then
			' Valid
			ResolveCryptStatus = "<%=txt_valid;%>"
		Else 
			' Invalid
			ResolveCryptStatus = "<%=txt_invalid;%>"
		End If
				
	End Function


	Function ResolveSignatureStatus( crypt_status, msg_type )
		If( msg_type = 2 ) Then
			' Not signed
		ElseIf crypt_status = 0 Then
			' Valid
			ResolveSignatureStatus = "Valid"
		Else 
			' Invalid
			ResolveSignatureStatus = "Invalid"
		End If
				
	End Function


	' TODO: remove, only a wrapper
	Function GetMsgBody

		On Error Resume Next
		body = VSSC.Body
		If (err.number <> 0) Then
			Call SetErrorInfoMS("Decompose Operation","",CStr(hex(err.number)),"<%=DecomposeAppStatus;%>",0)
			Exit Function
		End if

		' replace \n with <br>

		GetMsgBody = escapeHTML(body)
	End Function



	Sub onReplyForward( action )
		' TODO: set correct mode based on action
		On Error Resume Next

		If action = "reply" or action = "reply_all" Then
			VSSC.StoreAll 1, AppStatus
		Else
			VSSC.StoreAll 0, AppStatus
		End If
		If (err.number <> 0) Then
			Call SetErrorInfoMS("Decompose Operation","",CStr(hex(err.number)),CStr(hex(AppStatus)),0)
			Exit Sub
		End if

		On Error Resume Next
		document.delivery_form.vssc_message_id.value = VSSC.MsgObjID
		If (err.number <> 0) Then
			Call SetErrorInfoMS("Decompose Operation","",CStr(hex(err.number)),"<%=DecomposeAppStatus;%>",0)
			Exit Sub
		End if

		SubmitAction document.delivery_form, document.delivery_form.submit_action, action
	End Sub


</SCRIPT>

<% } else { %>
<!-- SGMS_VSSCDecomposeInclude: NS compatible functions -->
<SCRIPT language="JavaScript">
<!--

	// TODO: put in common include file
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
			} else if (error_code <= 0xFF) {
				javaErrorCode = "800000" + javaErrorCode.substring(javaErrorCode.length-2, javaErrorCode.length);
			} else if (error_code <= 0xFFF) {
				javaErrorCode = "80000" + javaErrorCode.substring(javaErrorCode.length-3, javaErrorCode.length);
			} else {
				javaErrorCode = "8000" + javaErrorCode.substring(javaErrorCode.length-4, javaErrorCode.length);
			}
		} else {
			ErrNumber = new Number(error_code);
			javaErrorCode = ErrNumber.toString(10);
		}

		return javaErrorCode;
	}

	function GetLastError()
	{
		return VSSC.GetLastError();
	}

	function SaveAttachment(filename)
	{
		var AppStatus = new java.lang.StringBuffer("");
		VSSC.VSSC_SaveAttachment(filename, AppStatus);
		if ( ErrorCode = GetLastError() ) {
			SetErrorInfoNS("Decompose Operation","",ConvertToHexNS(ErrorCode),ConvertToHexNS(AppStatus),0);
			return;
		}
	}

	function InitVSSC()
	{
		if(bErrorPresent == 1)
			return;

		var msgobjid=0;
		OBJECT_NODE_NOT_FOUND =	0x80005002;

		var AppStatus = new java.lang.StringBuffer("");

		VSSC.VSSC_ClearAll(1, AppStatus);
		ErrorCode = VSSC.GetLastError();
		if ( ErrorCode  && ErrorCode != OBJECT_NODE_NOT_FOUND) {
			SetErrorInfoNS("Decompose Operation","",ConvertToHexNS(ErrorCode),ConvertToHexNS(AppStatus),0);
			return ErrorCode;
		}
/*
		VSSC.VSSC_Initialize( msgobjid, 0, AppStatus );
		if ( ErrorCode = GetLastError() ) {
			SetErrorInfoNS("Decompose Operation","",ConvertToHexNS(ErrorCode),ConvertToHexNS(AppStatus),0);
			return ErrorCode;
		}
*/
		VSSC_PLUGIN_NOT_INITIALIZED = 0x80003555;
		var count = 1;
		VSSC.VSSC_Initialize(0,0, AppStatus);
		ErrorCode = VSSC.GetLastError();
		//alert("Error = " + ConvertToHexNS(ErrorCode));
		while(true) {
			ErrorCode=VSSC.GetLastError();
			if(ErrorCode == VSSC_PLUGIN_NOT_INITIALIZED){
				VSSC.VSSC_Initialize(0,0, AppStatus);
				count ++;
			} else {
				break;
			}
		}
		// Only for Debug, remove this later
		//alert("Times VSSC_Initialize Called = " + count);

		VSSC_INITIALIZED = 0x80003001;
		ErrorCode=VSSC.GetLastError();
		if(ErrorCode != 0 && ErrorCode != VSSC_INITIALIZED )
		{
			SetErrorInfoNS("Decompose Operation","",ConvertToHexNS(ErrorCode),ConvertToHexNS(AppStatus),0);
			return;
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
			//InstalledVer = VSSC.get_VSSC_InstalledPTAVer();
			SetErrorInfoNS("Decompose Operation","",ConvertToHexNS(ErrorCode),"<%=DecomposeAppStatus;%>",0);
			return;	
		}
		else if(ErrorCode)
		{
			SetErrorInfoNS("Decompose Operation","",ConvertToHexNS(ErrorCode),"<%=DecomposeAppStatus;%>",0);
			return;
		}

		// Setting the time out to 35 minutes. Configurable.
		// TODO: set them equal to the session timeout
		VSSC.set_VSSC_CertificateTimeOut( <%=VSSCCertificateTimeout;%> );
		if ( ErrorCode = GetLastError() ) {
			SetErrorInfoNS("Decompose Operation","",ConvertToHexNS(ErrorCode),"<%=DecomposeAppStatus;%>",0);
			return;
		}

		VSSC.set_VSSC_MessageTimeOut( <%=VSSCMessageTimeout;%> );
		if ( ErrorCode = GetLastError() ) {
			SetErrorInfoNS("Decompose Operation","",ConvertToHexNS(ErrorCode),"<%=DecomposeAppStatus;%>",0);
			return;
		}

		ConfigurePTA();
	}

	function ConfigurePTA()
	{
		if(bErrorPresent == 1)
			return;

		var szClientInfo = "<%=strClientInfo;%>";
		var szClientInfoSig = "<%=strClientInfoSig;%>";
		var szAppContextName = "<%=AppContextName; %>";
		var szAppLogoUrl = "<%=OnSiteHost;%>/SGMSAppLogo.BMP";

		//**Initialize PTA
		VSSC.PTA_Initialize(szAppContextName,0);
		if ( ErrorCode = GetLastError() ) {
			SetErrorInfoNS("Decompose Operation","",ConvertToHexNS(ErrorCode),"<%=DecomposeAppStatus;%>",0);
			return;
		}
		
		//**Setting AppLogo
		VSSC.set_UIPrefs_UILogoUrl(szAppLogoUrl);
		if ( ErrorCode = GetLastError() ) {
			SetErrorInfoNS("Decompose Operation","",ConvertToHexNS(ErrorCode),"<%=DecomposeAppStatus;%>",0);
			return;
		}

		
		//**Setting Roaming Properties
		VSSC.set_RoamPrefs_ClientInfo(szClientInfo);
		if ( ErrorCode = GetLastError() ) {
			SetErrorInfoNS("Decompose Operation","",ConvertToHexNS(ErrorCode),"<%=DecomposeAppStatus;%>",0);
			return;
		}

		
		VSSC.set_RoamPrefs_ClientInfoSig(szClientInfoSig);
		if ( ErrorCode = GetLastError() ) {
			SetErrorInfoNS("Decompose Operation","",ConvertToHexNS(ErrorCode),"<%=DecomposeAppStatus;%>",0);
			return;
		}

		
		VSSC.set_ProfMgmt_RoamProfile(true);
		if ( ErrorCode = GetLastError() ) {
			SetErrorInfoNS("Decompose Operation","",ConvertToHexNS(ErrorCode),"<%=DecomposeAppStatus;%>",0);
			return;
		}

		VSSC.set_ProfMgmt_IsUsernameEditable(false);
		if ( ErrorCode = GetLastError() ) {
			SetErrorInfoNS("Decompose Operation","",ConvertToHexNS(ErrorCode),"<%=DecomposeAppStatus;%>",0);
			return;
		}
	}

	// msg_type=2 (encrypted) or 3 (encrypted&signed)
	function DecomposeSMIME(smime_url, msg_type)
	{
		if(bErrorPresent == 1)
			return;

		var AppStatus = new java.lang.StringBuffer("");

		VSSC_PTA_CANCEL = 0x80001067;

		VSSC.VSSC_InternetInitialize(smime_url, "GET", "", AppStatus);
		if ( ErrorCode = GetLastError() ) {
			SetErrorInfoNS("Decompose Operation","",ConvertToHexNS(ErrorCode),ConvertToHexNS(AppStatus),0);
			return ErrorCode;
		}

		
		VSSC.VSSC_InternetSendRequest(AppStatus);
		if ( ErrorCode = GetLastError() ) {
			SetErrorInfoNS("Decompose Operation","",ConvertToHexNS(ErrorCode),ConvertToHexNS(AppStatus),0);
			return ErrorCode;
		}

		
		VSSC.set_VSSC_UseInternetData( true );
		if ( ErrorCode = GetLastError() ) {
			SetErrorInfoNS("Decompose Operation","",ConvertToHexNS(ErrorCode),"<%=DecomposeAppStatus;%>",0);
			return ErrorCode;
		}

		
		var msg = "";
		var status;

		VSSC.set_VSSC_MsgType( msg_type );
		if ( ErrorCode = GetLastError() ) {
			SetErrorInfoNS("Decompose Operation","",ConvertToHexNS(ErrorCode),"<%=DecomposeAppStatus;%>",0);
			return ErrorCode;
		}

		VSSC.set_VSSC_CertResolveURL( "<%=CertResolveURL;%>" );
		if ( ErrorCode = GetLastError() ) {
			SetErrorInfoNS("Decompose Operation","",ConvertToHexNS(ErrorCode),"<%=DecomposeAppStatus;%>",0);
			return ErrorCode;
		}

		VSSC.set_VSSC_SCType("<%=SCType;%>");
		if ( ErrorCode = GetLastError() ) {
			SetErrorInfoNS("Decompose Operation","",ConvertToHexNS(ErrorCode),"<%=DecomposeAppStatus;%>",0);
			return ErrorCode;
		}

		// Use the follwoing method to use the certificate either from the message (value 1)
		// or get it from verisign directory (value 0).
		// In case of SGMS, it should be always 1.
		VSSC.set_VSSC_UsePKCS7Certificate( true );
		if ( ErrorCode = GetLastError() ) {
			SetErrorInfoNS("Decompose Operation","",ConvertToHexNS(ErrorCode),"<%=DecomposeAppStatus;%>",0);
			return ErrorCode;
		}

		//The data downloaded is not URLEncoded.
		VSSC.set_VSSC_URLEncodeData( false );
		if ( ErrorCode = GetLastError() ) {
			SetErrorInfoNS("Decompose Operation","",ConvertToHexNS(ErrorCode),"<%=DecomposeAppStatus;%>",0);
			return ErrorCode;
		}

		status = VSSC.VSSC_Decompose( msg, AppStatus );
		if ( ErrorCode = GetLastError() ) {

			if(ErrorCode  == VSSC_PTA_CANCEL) {
				self.location = "<%=getinbox_url;%>";
				return ErrorCode;
			} else {
				SetErrorInfoNS("Decompose Operation","",ConvertToHexNS(ErrorCode),ConvertToHexNS(AppStatus),0);
				return ErrorCode;
			}
		}

		// true or false
		var cryptStatus = VSSC.get_VSSC_CryptStatus();
		if ( ErrorCode = GetLastError() ) {
			SetErrorInfoNS("Decompose Operation","",ConvertToHexNS(ErrorCode),"<%=DecomposeAppStatus;%>",0);
			return ErrorCode;
		}

		// build attachments table
		var attachments = VSSC.get_VSSC_AttachedFileList();
		if ( ErrorCode = GetLastError() ) {
			SetErrorInfoNS("Decompose Operation","",ConvertToHexNS(ErrorCode),"<%=DecomposeAppStatus;%>",0);
			return ErrorCode;
		}

		var str_att = "" + attachments;
		if( str_att != null && str_att != ""){
			var files_array = str_att.split(",");

			var i;
			for(i=0; i<files_array.length; i++){
				if( (files_array[i] != null) && (files_array[i].length > 0) ){
					addAtachment(files_array[i]);
				}
			}
		}

		return cryptStatus;
	}

	function ResolveCryptStatus( crypt_status, msg_type )
	{
		var status = "";
		if ( msg_type == 2 ) {
			// Not signed
			status = "<%=txt_not_signed;%>";
		} else if ( crypt_status == 0 ) {
			// Valid
			status = "<%=txt_valid;%>";
		} else {
			// Invalid
			status = "<%=txt_invalid;%>";
		}

		return status;
	}

	function ResolveSignatureStatus( crypt_status, msg_type )
	{
		var status = "";
		if ( msg_type == 2 ) {
			// Not signed
		} else if ( crypt_status == 0 ) {
			// Valid
			status = "Valid";
		} else {
			// Invalid
			status = "Invalid";
		}

		return status;
	}


	function GetMsgBody(){
		var body = VSSC.get_VSSC_Body();

		if ( ErrorCode = GetLastError() ) {
			SetErrorInfoNS("Decompose Operation","",ConvertToHexNS(ErrorCode),"<%=DecomposeAppStatus;%>",0);
			return ErrorCode;
		}

		return escapeHTML(body);
	}

	function onReplyForward( action )
	{
		// TODO: set correct mode based on action

		var AppStatus = new java.lang.StringBuffer("");

		if(action == "reply" || action == "reply_all")
			VSSC.VSSC_StoreAll( 1, AppStatus );
		else
			VSSC.VSSC_StoreAll( 0, AppStatus );


		if ( ErrorCode = GetLastError() ) {
			SetErrorInfoNS("Decompose Operation","",ConvertToHexNS(ErrorCode),ConvertToHexNS(AppStatus),0);
			return ErrorCode;
		}

		document.delivery_form.vssc_message_id.value = VSSC.get_VSSC_MsgObjID();
		if ( ErrorCode = GetLastError() ) {
			SetErrorInfoNS("Decompose Operation","",ConvertToHexNS(ErrorCode),"<%=DecomposeAppStatus;%>",0);
			return ErrorCode;
		}

		SubmitAction (document.delivery_form, document.delivery_form.submit_action, action);

	}

// -->
</SCRIPT>
<% } %>
