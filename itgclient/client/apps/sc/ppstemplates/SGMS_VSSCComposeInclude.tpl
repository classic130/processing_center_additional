<%@include file="SGMS_OnSiteHostConfig.tpl" %>
<%@include file="SGMS_VSSCDownloadInclude.tpl" %>

<SCRIPT language="JavaScript">
<!--

function copyright ()
{
//Create a new window
var newWin = window.open("copyright.htm", "popup_1", 'toolbar=1,location=0,directories=0,status=0,menubar=0,scrollbars=1,resizable=0,width=620,height=375'); 

}

function privacy ()
{
//Create a new window
var newWin = window.open("privacy.htm", "popup_1", 'toolbar=1,location=0,directories=0,status=0,menubar=0,scrollbars=1,resizable=0,width=620,height=375'); 

}

function MergeFields(strTo, strCc, strBcc)
{
	var temp = "";
	if (strTo != "") {
		temp = strTo;
	}

	if (strCc != "") {
		if (temp != "") {
			temp = temp + ",";
		}
		temp = temp + strCc;
	}

	if (strBcc != "") {
		if (temp != "") {
			temp = temp + ",";
		}
		temp = temp + strBcc;
	}

	return temp;
}

function calculatePrice(msgSize)
{
	// TODO: BBI: BUG: resolve maillists?
	var strTo = document.form1.to.value;
	var strCc = document.form1.cc.value;
	var strBcc = document.form1.bcc.value;

	var temp = MergeFields( strTo, strCc, strBcc );

	var recipientArray = temp.split(",");
	var recipientsCount = recipientArray.length;

	var mbSize = 1024*1024;
	var unitsPerUser = 0;

	if (msgSize < mbSize) {
		unitsPerUser = 1;
	} else if (msgSize < 5*mbSize) {
		unitsPerUser = 2;
	} else if (msgSize < 10*mbSize) {
		unitsPerUser = 3;
	} else {
		unitsPerUser = 4;
	}
	
	return unitsPerUser*recipientsCount;
}

function escapeMessage(input, action) {
	// The customization variables are defined here:
	if ( action == "reply" ) {
		var msg_header = "--- Original Message ---";
		var msg_footer = "--- End of Original Message ---";
		var msg_prefix = "> ";
		var msg_suffix = "\n";
		var msg_row_length = 73;
	} else if ( action == "forward" ) {
		var msg_header = "--- Forwarded Message ---";
		var msg_footer = "--- End of Message ---";
		var msg_prefix = "| ";
		var msg_suffix = "\n";
		var msg_row_length = 73;
	} else {
		return "";
	}

	// Local instance variables are defined here:
	var lstr = new String( input );
	var output = "";

	// Initialize the output
	output = msg_header + msg_suffix;

	while ( lstr.length > 0) {
		var ind = lstr.indexOf("\n");
		if ( ind == -1 ) ind = lstr.length;
		if ( ind > msg_row_length ) {
			ind = msg_row_length;
			while ( ind > 0 && lstr.charAt(ind) != " " && lstr.charAt(ind) != "\t" ) ind--;
			if ( ind == 0 ) {
				// The whole row is one word, find the end of the word.
				while ( ind < lstr.length && lstr.charAt(ind) != " " && lstr.charAt(ind) != "\t" && 
						lstr.charAt(ind) != "\n" ) ind++;
			}
		}
		// Split the body at ind position
		output = output + msg_prefix + lstr.substring(0, ind) + msg_suffix;
		// Remove this part from the input string.
		lstr = lstr.substring(ind + 1, lstr.length);
	}
	// Add the footer and return
	output = output + msg_footer + msg_suffix;
	return output;
}

//-->
</SCRIPT>


<% if( tw.request.userAgentVendor == "microsoft" ) { %>

	<!-- VSSC Compose script: IE compatible functions -->

	<SCRIPT LANGUAGE="VBScript">
	
	Dim strFileName

	Function CheckIfIDValid
		Dim str,ResolveRcpt,strTo,strCc,strBcc
		Dim RecipCount,i
		Dim AppStatus

		On Error Resume Next
		VSSC.CertResolveURL = "<%=CertResolveURL;%>"
		If(err.number <> 0) then
			CheckIfIDValid=err.number
			Call SetErrorInfoMS("Compose Operation","",CStr(hex(err.number)),"<%=ComposeAppStatus;%>",0)
			Exit Function
		End If
				
		On Error Resume Next
		VSSC.SCType = "<%=SCType;%>"
		If(err.number <> 0) then
			CheckIfIDValid=err.number
			Call SetErrorInfoMS("Compose Operation","",CStr(hex(err.number)),"<%=ComposeAppStatus;%>",0)
			Exit Function
		End If

		' resolve the sender's email address
		On Error Resume Next
		str=VSSC.CertificateResolution("<%= tw.session.account.address; %>", AppStatus)
		If ((err.number <> 0) or (AppStatus <> 0)) Then
				CheckIfIDValid=err.number
				Call SetErrorInfoMS("Compose Operation","",CStr(hex(err.number)),CStr(hex(AppStatus)),0)
				Exit Function
		end if

		Dim Item_Count, szEmail, nStatus

		On Error Resume Next
		Set IResolveInfo = VSSC.IVSSCResolveInfo
		If(err.number <> 0) then
			CheckIfIDValid=err.number
			Call SetErrorInfoMS("Compose Operation","",CStr(hex(err.number)),"<%=ComposeAppStatus;%>",0)
			Exit Function
		End If


		On Error Resume Next
		Item_Count=IResolveInfo.Recipient_Count
		If(err.number <> 0) then
			CheckIfIDValid=err.number
			Call SetErrorInfoMS("Compose Operation","",CStr(hex(err.number)),"<%=ComposeAppStatus;%>",0)
			Exit Function
		End If

		On Error Resume Next
		IResolveInfo.First
		If(err.number <> 0) then
			CheckIfIDValid=err.number
			Call SetErrorInfoMS("Compose Operation","",CStr(hex(err.number)),"<%=ComposeAppStatus;%>",0)
			Exit Function
		End If

		On Error Resume Next
		szEmail=IResolveInfo.EmailAddress

		If(err.number <> 0) then
			CheckIfIDValid=err.number
			Call SetErrorInfoMS("Compose Operation","",CStr(hex(err.number)),"<%=ComposeAppStatus;%>",0)
			Exit Function
		End If

		CERT_RESOLUTION_FAILED = &h8000304B

		On Error Resume Next
		nStatus=IResolveInfo.RevocationStatus
		If(err.number <> 0) then
			CheckIfIDValid=err.number
			Call SetErrorInfoMS("Compose Operation","",CStr(hex(err.number)),"<%=ComposeAppStatus;%>",0)
			Exit Function
		End If

		'If Certificate is Revoked
		If(nStatus <> 0) then
			CheckIfIDValid=CERT_RESOLUTION_FAILED 
			Call SetErrorInfoMS("Compose Operation","",CStr(hex(CERT_RESOLUTION_FAILED )),"<%=RevocationStatus;%>",0)
			Exit Function
		End If

		On Error Resume Next
		nStatus=IResolveInfo.IsCertExpired
		If(err.number <> 0) then
			CheckIfIDValid=err.number
			Call SetErrorInfoMS("Compose Operation","",CStr(hex(err.number)),"<%=ComposeAppStatus;%>",0)
			Exit Function
		End If

		'If Certificate has Expired
		If(nStatus <> 0) then
			CheckIfIDValid=CERT_RESOLUTION_FAILED 
			Call SetErrorInfoMS("Compose Operation","",CStr(hex(CERT_RESOLUTION_FAILED )),"<%=ExpirationStatus;%>",0)
			Exit Function
		End If
    End Function

	Function GetBody()
		
		On Error Resume Next

		GetBody = VSSC.Body
		If ( err.number <> 0 ) Then
			Call SetErrorInfoMS("Compose Operation","",CStr(hex(err.number)),"<%=ComposeAppStatus;%>",0)
			Exit Function
		End If

	End Function

	Function GetMessageSize()
		Dim size

		On Error Resume Next

		size = VSSC.MsgBlobSize
		If ( err.number <> 0 ) Then
			GetMessageSize = 0			
			Call SetErrorInfoMS("Compose Operation","",CStr(hex(err.number)),"<%=ComposeAppStatus;%>",0)
			Exit Function
		End If

		GetMessageSize = size
	End Function

	Function GetAttachedFileList()
		Dim file_list

		On Error Resume Next

		file_list = VSSC.AttachedFileList
		If ( err.number <> 0 ) Then
			GetAttachedFileList = ""
			Call SetErrorInfoMS("Compose Operation","",CStr(hex(err.number)),"<%=ComposeAppStatus;%>",0)
			Exit Function
		End If

		GetAttachedFileList = file_list
	End Function

	Function GetSelectedAttachmentSize(file_name)

		Dim AppStatus
		Dim size
		
		On Error Resume Next

		size = VSSC.SelectedAttachmentSize( file_name, AppStatus )
		If ( err.number <> 0 ) Then
			GetSelectedAttachmentSize = 0			
			Call SetErrorInfoMS("Decompose Operation","",CStr(hex(err.number)),CStr(hex(AppStatus)),0)
			Exit Function
		End If

		GetSelectedAttachmentSize = size
	End Function

	Function VSSC_ONSEND(usePRC)
		Dim str,strFrom,strPRC
		Dim msgobjid
		Dim AppStatus, Status
		Dim Preferences
		Dim MsgBlobSize,MBUnit
		Dim MaxBlobSize,EstBlobSize
		Dim strMaxMsg

		if bErrorPresent = 1 then
			exit function
		end if
		
		' Setting PRC Related Properties
		' this is going with the recipient logic as we need to set the prc flag from here
		' FIXME - should be dynamically filled in by the server
	
		' Enable PRC
		' Preferences
		'0x0000 - Don't Use Proxy Certificate
		'0x0001 - Use Proxy Certificate when Cert not found
		'0x0002 - Use Proxy Certificate when Cert expired
		'0x0004 - Use Proxy Certificate when Cert revoked

		USE_PRC_FOR_NOT_FOUND = &h0001
		USE_PRC_FOR_EXPIRED = &h0002
		USE_PRC_FOR_REVOKED = &h0004
		VSSC_PTA_CANCEL = &h80001067


		Preferences = 7

		On Error Resume Next
		if usePRC <> 0 then
			VSSC.UseProxyRecipCert=CInt(7)
		else
			VSSC.UseProxyRecipCert=CInt(0)
		end if
		If ( err.number <> 0 ) then
			VSSC_ONSEND=err.number
			Call SetErrorInfoMS("Compose Operation","",CStr(hex(err.number)),"<%=ComposeAppStatus;%>",0)
			exit Function
		End If

		On Error Resume Next
		if usePRC <> 0 then
			  status = VSSC.ResolveProxyRecipCert ("<%=PRCEMailAddr;%>", AppStatus)
			  if (err.number <> 0 ) then
					VSSC_ONSEND=err.number
					Call SetErrorInfoMS("Compose Operation","",CStr(hex(err.number)),CStr(hex(AppStatus)),0)
					exit Function
			  End If
		end if

		str = document.form1.subject.value
		On Error Resume Next
		VSSC.Subject = str
		If ( err.number <> 0 ) then
			VSSC_ONSEND=err.number
			Call SetErrorInfoMS("Compose Operation","",CStr(hex(err.number)),"<%=ComposeAppStatus;%>",0)
			exit Function
		End If

		str = document.form1.message.value
		On Error Resume Next
		VSSC.Body = str
		If ( err.number <> 0 ) then
			VSSC_ONSEND=err.number
			Call SetErrorInfoMS("Compose Operation","",CStr(hex(err.number)),"<%=ComposeAppStatus;%>",0)
			exit Function
		End If

		On Error Resume Next
		if(document.form1.vssc_sign.Checked = "True")Then
			VSSC.MsgType = 3
		else
			VSSC.MsgType = 2
		end if
		If ( err.number <> 0 ) then
			VSSC_ONSEND=err.number
			Call SetErrorInfoMS("Compose Operation","",CStr(hex(err.number)),"<%=ComposeAppStatus;%>",0)
			exit Function
		End If

		

		On Error Resume Next
		VSSC.Compose AppStatus
		If ((err.number <> 0) or (AppStatus <> 0)) Then
				if(err.number = VSSC_PTA_CANCEL) Then
					VSSC_ONSEND=err.number
					exit Function
				else
					VSSC_ONSEND=err.number
					Call SetErrorInfoMS("Compose Operation","",CStr(hex(err.number)),CStr(hex(AppStatus)),0)
					exit Function
				end if
		end if

		On Error Resume Next
		BlobSize=VSSC.MsgBlobSize
		If (err.number <> 0) Then
			VSSC_ONSEND=err.number
			Call SetErrorInfoMS("Compose Operation","",CStr(hex(err.number)),"<%=ComposeAppStatus;%>",0)
			exit Function
		end if

		MBUnit=1024 *1024
		EstBlobSize=BlobSize/MBUnit
		MsgBlobSize=EstBlobSize/1.76
		MaxBlobSize=<%=MaxUploadBlobSize;%>
		
		
		if (MsgBlobSize>MaxBlobSize) Then
				strMaxMsg="<%=MaxLimitMsg;%>"
				MsgBox 	strMaxMsg
				exit Function	
		End if



		On Error Resume Next
		document.form1.vssc_blob.value = VSSC.GetMsg
		If (err.number <> 0) Then
				VSSC_ONSEND=err.number
				Call SetErrorInfoMS("Compose Operation","",CStr(hex(err.number)),"<%=ComposeAppStatus;%>",0)
				exit Function
		end if

		On Error Resume Next
		'post the message ID needed later for inline errors
		VSSC.StoreAll 0, AppStatus
		If ((err.number <> 0) or (AppStatus <> 0)) Then
				VSSC_ONSEND=err.number
				Call SetErrorInfoMS("Compose Operation","",CStr(hex(err.number)),CStr(hex(AppStatus)),0)
				exit Function
		end if

		On Error Resume Next
		document.form1.vssc_message_id.value = VSSC.MsgObjID
		If (err.number <> 0) Then
				VSSC_ONSEND=err.number
				Call SetErrorInfoMS("Compose Operation","",CStr(hex(err.number)),"<%=ComposeAppStatus;%>",0)
				exit Function
		end if

		VSSC_ONSEND = 0
	end Function

	Function SetRecipientInfo(strTo,strCc,strBcc)

		if bErrorPresent = 1 then
			exit function
		end if

		On Error Resume Next
		VSSC.ToRecipientsInfo = LCase(strTo)
		If ( err.number <> 0 ) then
				SetRecipientInfo=err.number
				Call SetErrorInfoMS("Compose Operation","",CStr(hex(err.number)),"<%=ComposeAppStatus;%>",0)
				Exit Function
		End If

		On Error Resume Next
		VSSC.CcRecipientsInfo = LCase(strCc)
		If ( err.number <> 0 ) then
			SetRecipientInfo=err.number
			Call SetErrorInfoMS("Compose Operation","",CStr(hex(err.number)),"<%=ComposeAppStatus;%>",0)
			Exit Function

		End If

		On Error Resume Next
		VSSC.BccRecipientsInfo = LCase(strBcc)
		If ( err.number <> 0 ) then
			SetRecipientInfo=err.number
			Call SetErrorInfoMS("Compose Operation","",CStr(hex(err.number)),"<%=ComposeAppStatus;%>",0)
			Exit Function
		End If

		SetRecipientInfo=0
		
	End Function


	Function BinaryToString(Binary)
	
		Dim cl1, cl2, cl3, pl1, pl2, pl3
		Dim L
		cl1 = 1
		cl2 = 1
		cl3 = 1
		L = LenB(Binary)
	
		Do While cl1<=L
			pl3 = pl3 & Chr(AscB(MidB(Binary,cl1,1)))
			cl1 = cl1 + 1
			cl3 = cl3 + 1
			If cl3>300 Then
				pl2 = pl2 & pl3
				pl3 = ""
				cl3 = 1
				cl2 = cl2 + 1
				If cl2>200 Then
					pl1 = pl1 & pl2
					pl2 = ""
					cl2 = 1
				End If
			End If
		Loop
		BinaryToString = pl1 & pl2 & pl3
	End Function


	Function ResolveRecipients()
		
		Dim str,ResolveRcpt,strTo,strCc,strBcc
		Dim RecipCount,i
		Dim AppStatus

		if bErrorPresent = 1 then
			exit function
		end if

		On Error Resume Next
		VSSC.CertResolveURL = "<%=CertResolveURL;%>"
		If(err.number <> 0) then
			ResolveRecipients=err.number
			Call SetErrorInfoMS("Compose Operation","",CStr(hex(err.number)),"<%=ComposeAppStatus;%>",0)
			Exit Function
		End If

				
		On Error Resume Next
		VSSC.SCType = "<%=SCType;%>"
		If(err.number <> 0) then
			ResolveRecipients=err.number
			Call SetErrorInfoMS("Compose Operation","",CStr(hex(err.number)),"<%=ComposeAppStatus;%>",0)
			Exit Function
		End If

		' resolve the sender's email address
		On Error Resume Next
		str=VSSC.CertificateResolution("<%= tw.session.account.address; %>", AppStatus)
		If ((err.number <> 0) or (AppStatus <> 0)) Then
				ResolveRecipients=err.number
				Call SetErrorInfoMS("Compose Operation","",CStr(hex(err.number)),CStr(hex(AppStatus)),0)
				Exit Function
		end if

		Dim Item_Count, szEmail, nStatus

		On Error Resume Next
		Set IResolveInfo = VSSC.IVSSCResolveInfo
		If(err.number <> 0) then
			ResolveRecipients=err.number
			Call SetErrorInfoMS("Compose Operation","",CStr(hex(err.number)),"<%=ComposeAppStatus;%>",0)
			Exit Function
		End If

		On Error Resume Next
		Item_Count=IResolveInfo.Recipient_Count
		If(err.number <> 0) then
			ResolveRecipients=err.number
			Call SetErrorInfoMS("Compose Operation","",CStr(hex(err.number)),"<%=ComposeAppStatus;%>",0)
			Exit Function
		End If

		On Error Resume Next
		IResolveInfo.First
		If(err.number <> 0) then
			ResolveRecipients=err.number
			Call SetErrorInfoMS("Compose Operation","",CStr(hex(err.number)),"<%=ComposeAppStatus;%>",0)
			Exit Function
		End If

		i=0
		For i=1 to Item_Count
			On Error Resume Next
			szEmail=IResolveInfo.EmailAddress
			If(err.number <> 0) then
				ResolveRecipients=err.number
				Call SetErrorInfoMS("Compose Operation","",CStr(hex(err.number)),"<%=ComposeAppStatus;%>",0)
				Exit Function
			End If

			On Error Resume Next
			nStatus=IResolveInfo.status
			If(err.number <> 0) then
				ResolveRecipients=err.number
				Call SetErrorInfoMS("Compose Operation","",CStr(hex(err.number)),"<%=ComposeAppStatus;%>",0)
				Exit Function
			End If

			'Check nStatus. If = 0, then email not resolved. No corresponding cert.
			On Error Resume Next
			IResolveInfo.Next
			If(err.number <> 0) then
				ResolveRecipients=err.number
				Call SetErrorInfoMS("Compose Operation","",CStr(hex(err.number)),"<%=ComposeAppStatus;%>",0)
				Exit Function
			End If
		Next


		On Error Resume Next
		VSSC.FromInfo=szEmail
		If(err.number <> 0) then
			ResolveRecipients=err.number
			Call SetErrorInfoMS("Compose Operation","",CStr(hex(err.number)),"<%=ComposeAppStatus;%>",0)
			Exit Function
		End If

		'VSSC.FromInfo=str

		'Perform certificate resolution  FIXME!!!
		strTo=document.form1.to.value
		strCc=document.form1.cc.value
		strBcc=document.form1.bcc.value

		'Resolve the alias name to email addresses from address book before passing onto VSSC. For TO, CC and BCC field values.
		<%
		// FIXME !!! - remove if no server side resolution will be done
		// FIXME !!!  - add the port
		var host_with_port = tw.httpGateway.hostName;      //AndPort;
		var full_gateway_url = (tw.request.isSSL ? "https" : "http") + "://" + host_with_port;
		full_gateway_url += tw.httpGateway.getUrl('SGMS_TxnAccPackageResolveRecipients.tpl');
		// FIXME !!! - use POST instead of GET method
		//full_gateway_url = tw.httpGateway.appendUrlQueryVariable(full_gateway_url,"to","kire");
		//full_gateway_url = tw.httpGateway.appendUrlQueryVariable(full_gateway_url,"cc","levski@wizcom.bg");
		//full_gateway_url = tw.httpGateway.appendUrlQueryVariable(full_gateway_url,"bcc","dgrigorov@hotmail.com");
		%>

'		' FIXME!!! - construction of URL not perfect
'		vbInternetURL = "<%= full_gateway_url; %>"
'		vbInternetURL = vbInternetURL & "&to=" & document.form1.to.value
'		vbInternetURL = vbInternetURL & "&cc=" & document.form1.cc.value
'		vbInternetURL = vbInternetURL & "&bcc=" & document.form1.bcc.value
'		vbInternetPostData = ""  'This should be set to "", if szMethod = "GET" 
'		vbInternetMethod = "GET"               'This can be "POST" or "GET" 
'		VSSC.InternetInitialize vbInternetURL, vbInternetMethod, vbInternetPostData'
'
'		VSSC.InternetSendRequest                'This is a blocking call 
'		'VSSC.UseInternetData = vbFalse          'This tells VSSC.Decompose to use the Internet data internally. 
'		'FIXME!!! - Error 80001003 ?   what is it ?
'
'		vbMessage = VSSC.InternetData 
'		vbMessageSize = VSSC.InternetDataSize
'
'		vbResolveArr = split( BinaryToString(vbMessage), ";" )
'		MsgBox "Resolved addresses: " & vbNewLine & _
'		       "To: " & vbResolveArr(0) & vbNewLine & _
'			   "Cc: " & vbResolveArr(1) & vbNewLine & _
'			   "Bcc: " & vbResolveArr(2)
'		' FIXME!!! [danail]  ... or here !!!

		'The call below does not make sense but otherwise the VSSC behaves oddly
'		errorCode = SetRecipientInfo( vbResolveArr(0), vbResolveArr(1), vbResolveArr(2) )    ' for server side resolution
		errorCode = SetRecipientInfo( strTo, strCc, strBcc )
		If ( errorCode <> 0 ) then
			ResolveRecipients=errorCode
			Exit Function
		End If


		On Error Resume Next
		str=VSSC.SMIMECertificateResolution(AppStatus)
		If ((err.number <> 0) or (AppStatus <> 0)) Then
				ResolveRecipients=err.number
				Call SetErrorInfoMS("Compose Operation","",CStr(hex(err.number)),CStr(hex(AppStatus)),0)
				exit Function
		end if

		On Error Resume Next
		Set ResolveRcpt=VSSC.IVSSCResolveInfo
		If(err.number <> 0) then
			ResolveRecipients=err.number
			Call SetErrorInfoMS("Compose Operation","",CStr(hex(err.number)),"<%=ComposeAppStatus;%>",0)
			exit Function
		End If

		On Error Resume Next
		RecipCount=ResolveRcpt.Recipient_Count
		If ( err.number <> 0 ) then
			ResolveRecipients=err.number
			Exit Function
		End If

		Dim flagSenderRemoved
		flagSenderRemoved = false
		
		'TODO: When VSSC starts working remove duplicate recipient check
		On Error Resume Next
		ResolveRcpt.First
		If(err.number <> 0) then
			ResolveRecipients=err.number
			Call SetErrorInfoMS("Compose Operation","",CStr(hex(err.number)),"<%=ComposeAppStatus;%>",0)
			Exit Function
		End If

		i=0
		initCertResolution
		CERTEXISTS = &h3002
		For i=1 to RecipCount

			On Error Resume Next
			szEmail = ResolveRcpt.EmailAddress
			If(err.number <> 0) then
				ResolveRecipients=err.number
				Call SetErrorInfoMS("Compose Operation","",CStr(hex(err.number)),"<%=ComposeAppStatus;%>",0)
				Exit Function
			End If

		    If (szEmail <> "<%= tw.session.account.address; %>") Or flagSenderRemoved Then

				' FIXME !!! - populate global arrays for certificate resolution
				On Error Resume Next
				nStatus = ResolveRcpt.Status
				If(err.number <> 0) then
					ResolveRecipients=err.number
					Call SetErrorInfoMS("Compose Operation","",CStr(hex(err.number)),"<%=ComposeAppStatus;%>",0)
					Exit Function
				End If

				If nStatus = CERTEXISTS Then		' 0 - failure, otherwise - success
					addResolvedRecipient szEmail
				Else
					addPRCRecipient szEmail
				End If

			Else
				flagSenderRemoved = true
			End If

			On Error Resume Next
			ResolveRcpt.Next
			If(err.number <> 0) then
				ResolveRecipients=err.number
				Call SetErrorInfoMS("Compose Operation","",CStr(hex(err.number)),"<%=ComposeAppStatus;%>",0)
				Exit Function
			End If

		Next
		
		ResolveRecipients = 0
	End Function


	Function UpdateRecipients()
		Dim AppStatus

		if bErrorPresent = 1 then
			exit function
		end if


		strTo=document.form1.to.value
		'TODO:  + "," + "<%= tw.session.account.address; %>"
		strCc=document.form1.cc.value
		strBcc=document.form1.bcc.value
		
		SetRecipientInfo strTo,strCc,strBcc

		On Error Resume Next				
		str=VSSC.SMIMECertificateResolution(AppStatus)
		If(err.number <> 0) then
			UpdateRecipients=err.number
			Call SetErrorInfoMS("Compose Operation","",CStr(hex(err.number)),"<%=ComposeAppStatus;%>",0)
			exit Function
		End If

	End Function


	' Initialize the VSSC with the correct message ID
	Function InitVSSC( messageID )

		if bErrorPresent = 1 then
			exit function
		end if

		OBJECT_NODE_NOT_FOUND =	&h80005002
		VSSC_INITIALIZED = &h80003001
		On Error Resume Next	
		If ( messageId = 0 ) Then
			VSSC.ClearAll 1, AppStatus
			If (err.number <> 0 And err.number <> OBJECT_NODE_NOT_FOUND) Then
				InitVSSC = err.number
				Call SetErrorInfoMS("Compose Operation","",CStr(hex(err.number)),CStr(hex(AppStatus)),0)
				Exit Function
			End If
		End IF
		
		On Error Resume Next
		messageID = CInt(messageID)
		VSSC.Initialize messageID, 0, AppStatus
		If (err.number <> 0 and err.number <> VSSC_INITIALIZED) Then
			InitVSSC = err.number
			Call SetErrorInfoMS("Compose Operation","",CStr(hex(err.number)),CStr(hex(AppStatus)),0)
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
			InitVSSC = err.number
			Call SetErrorInfoMS("Compose Operation","",CStr(hex(err.number)),"<%=ComposeAppStatus;%>",0)
			Exit Function	
		Else If (err.number) then
			InitVSSC = err.number
			Call SetErrorInfoMS("Compose Operation","",CStr(hex(err.number)),"<%=ComposeAppStatus;%>",0)
			Exit Function
		End If
		End If


		' TODO: This timeout is configurable. Time is in minutes.
		' TODO: should be >= session timeout !
		On Error Resume Next
		VSSC.CertificateTimeOut = <%=VSSCCertificateTimeout;%>
		If (err.number <> 0) Then
			InitVSSC = err.number
			Call SetErrorInfoMS("Compose Operation","",CStr(hex(err.number)),"<%=ComposeAppStatus;%>",0)
			Exit Function
		End if

		On Error Resume Next
		VSSC.MessageTimeOut = <%=VSSCMessageTimeout;%>
		If (err.number <> 0) Then
			InitVSSC = err.number
			Call SetErrorInfoMS("Compose Operation","",CStr(hex(err.number)),"<%=ComposeAppStatus;%>",0)
			Exit Function
		End if

		' build attachments table
		' TODO: move in external function
		Dim szFile, Pos, szFileNameList
		If ( messageId <> 0 ) Then
			On Error Resume Next
			szFileNameList = VSSC.SelectedAttachments
			If (err.number <> 0) Then
				InitVSSC = err.number
				Call SetErrorInfoMS("Compose Operation","",CStr(hex(err.number)),"<%=ComposeAppStatus;%>",0)
				Exit Function
			End if

			nLen=Len(szFileNameList)
			If nLen = 0 Then
				On Error Resume Next
				szFileNameList = VSSC.AttachedFileList
				If (err.number <> 0) Then
					InitVSSC = err.number
					Call SetErrorInfoMS("Compose Operation","",CStr(hex(err.number)),"<%=ComposeAppStatus;%>",0)
					Exit Function
				End if
				nLen=Len(szFileNameList)
			End if

			If nLen <> 0 Then
				Delimiter= ","
				szFileNameList =Delimiter & szFileNameList
				DelLen = Len(Delimiter)
				CurPos = 1
				NextPos = InStr(CurPos+DelLen, szFileNameList, Delimiter)
				Do Until NextPos = 0
					szFile=Mid(szFileNameList, CurPos + DelLen, NextPos - CurPos - DelLen)
					strFileName=szFile
					addAtachment(strFileName)
					CurPos = NextPos
					NextPos = InStr(CurPos + DelLen, szFileNameList, Delimiter)
				Loop
			End if
		End If

		InitVSSC = 0

	End Function


	Sub  ConfigurePTA
		Dim szClientInfo, szClientInfoSig
		Dim IVSPTA
		Dim IVSProfMgmt
		Dim IVSUIPrefs
		Dim IVSRoamPrefs
		Dim szAppContextName
		Dim szAppLogoUrl

		Dim AppStatus

		if bErrorPresent = 1 then
			exit sub
		end if

		szClientInfo = "<%=strClientInfo;%>"
		szClientInfoSig = "<%=strClientInfoSig;%>"

		szAppContextName="<%=AppContextName; %>" 
		szAppLogoUrl = "<%=OnSiteHost;%>/SGMSAppLogo.BMP"

	    On Error Resume Next
		Set IVSPTA=VSSC.IVSSCPTA
		If (err.number <> 0) Then
			Call SetErrorInfoMS("Compose Operation","00000005",CStr(hex(err.number)),"<%=ComposeAppStatus;%>",0)
			Exit Sub
		End if

	    On Error Resume Next
		Set IVSProfMgmt = IVSPTA.IVSProfMgmt
		If (err.number <> 0) Then
			Call SetErrorInfoMS("Compose Operation","00000005",CStr(hex(err.number)),"<%=ComposeAppStatus;%>",0)
			Exit Sub
		End if

	    On Error Resume Next
		Set IVSUIPrefs = IVSPTA.IVSUIPrefs
		If (err.number <> 0) Then
			Call SetErrorInfoMS("Compose Operation","00000005",CStr(hex(err.number)),"<%=ComposeAppStatus;%>",0)
			Exit Sub
		End if

	    On Error Resume Next
		Set IVSRoamPrefs=IVSPTA.IVSRoamPrefs
		If (err.number <> 0) Then
			Call SetErrorInfoMS("Compose Operation","00000005",CStr(hex(err.number)),"<%=ComposeAppStatus;%>",0)
			Exit Sub
		End if


		' Initialize PTA
		On Error Resume Next
		IVSPTA.Initialize szAppContextName,0
		If ( err.number <> 0 ) then
			Call SetErrorInfoMS("Compose Operation","00000005",CStr(hex(err.number)),"<%=ComposeAppStatus;%>",0)
			Exit Sub
		End If

		' Setting AppLogo
		On Error Resume Next
		IVSUIPrefs.UILogoUrl = szAppLogoUrl
		If ( err.number <> 0 ) then
			Call SetErrorInfoMS("Compose Operation","00000005",CStr(hex(err.number)),"<%=ComposeAppStatus;%>",0)
			Exit Sub
		End If

		' Setting Roaming Properties
		On Error Resume Next
		IVSRoamPrefs.ClientInfo=szClientInfo
		If (err.number <> 0) then
			Call SetErrorInfoMS("Compose Operation","00000005",CStr(hex(err.number)),"<%=ComposeAppStatus;%>",0)
			Exit Sub
		End If

		On Error Resume Next
		IVSRoamPrefs.ClientInfoSig=szClientinfoSig
		If(err.number <> 0) then
			Call SetErrorInfoMS("Compose Operation","00000005",CStr(hex(err.number)),"<%=ComposeAppStatus;%>",0)
			Exit Sub
		End If

		On Error Resume Next
		IVSProfMgmt.RoamProfile = CBool(1) 
		If(err.number <> 0) then
			Call SetErrorInfoMS("Compose Operation","00000005",CStr(hex(err.number)),"<%=ComposeAppStatus;%>",0)
			Exit Sub
		End If

		On Error Resume Next
		VSSC.IVSSCPTA.IVSProfMgmt.IsUsernameEditable = CBool(0)
		If (err.number <> 0 ) Then
			Call SetErrorInfoMS("Compose Operation","00000005",CStr(hex(err.number)),"<%=ComposeAppStatus;%>",0)
			Exit Sub
		End If

		' PTA
	End Sub


	Sub VSSelectAttachment

		' prompt for filename
		Dim AppStatus

		if bErrorPresent = 1 then
			exit sub
		end if
		
		On Error Resume Next
		VSSC.SelectAttachments AppStatus
		If err.number <> 0 or AppStatus <> 0 Then
			Call SetErrorInfoMS("Compose Operation","",CStr(hex(err.number)),CStr(hex(AppStatus)),0)
			Exit Sub

			'Select Case CStr(Hex(err.number))
			'	case 80003007
			'		MsgBox "File Already Selected"
			'		Exit Sub
			'End Select
			'Exit Sub
		End if

		
		onClickAttach
	End Sub


	Sub onClickAttach

		if bErrorPresent = 1 then
			exit sub
		end if

		' Init ActiveX
		UpdateVSSCFromHTML

		Dim AppStatus

		On Error Resume Next
		VSSC.StoreAll 0, AppStatus
		If(err.number <> 0 or AppStatus <> 0 ) then
			Call SetErrorInfoMS("Compose Operation","",CStr(hex(err.number)),CStr(hex(AppStatus)),0)
			Exit Sub
		End If

		' Clear the fields of the HTML FORM that we don't want to be transmitted
		document.form1.subject.value = ""
		document.form1.message.value = ""

		

		On Error Resume Next
		document.form1.vssc_message_id.value = VSSC.MsgObjID
		If (err.number <> 0 ) Then
			Call SetErrorInfoMS("Compose Operation","00000005",CStr(hex(err.number)),"<%=ComposeAppStatus;%>",0)
			Exit Sub
		End If

		document.form1.submit_action.value = "command_add_file_sgms"
		document.form1.submit()
		document.body.innerHTML = ""
	End Sub


	' Transfer the FORM data to the VSSC ActiveX
	Sub UpdateVSSCFromHTML
		if bErrorPresent = 1 then
			exit sub
		end if

		SetRecipientInfo document.form1.to.value, document.form1.cc.value, document.form1.bcc.value

		On Error Resume Next
		VSSC.Subject =document.form1.subject.value
		If(err.number <> 0) then
			Call SetErrorInfoMS("Compose Operation","",CStr(hex(err.number)),"<%=ComposeAppStatus;%>",0)
			Exit Sub
		End If

		On Error Resume Next
		VSSC.Body = document.form1.message.value
		If(err.number <> 0) then
			Call SetErrorInfoMS("Compose Operation","",CStr(hex(err.number)),"<%=ComposeAppStatus;%>",0)
			Exit Sub
		End If
	End Sub

	' Update the FORM data from the VSSC ActiveX
	Sub UpdateHTMLFromVSSC

		if bErrorPresent = 1 then
			exit sub
		end if

		'document.form1.to.value = VSSC.ToRecipientsInfo
		'document.form1.cc.value = VSSC.CcRecipientsInfo
		'document.form1.bcc.value = VSSC.BccRecipientsInfo
		On Error Resume Next
		document.form1.subject.value = VSSC.Subject
		If(err.number <> 0) then
			Call SetErrorInfoMS("Compose Operation","",CStr(hex(err.number)),"<%=ComposeAppStatus;%>",0)
			Exit Sub
		End If

		On Error Resume Next
		document.form1.message.value = VSSC.Body
		If(err.number <> 0) then
			Call SetErrorInfoMS("Compose Operation","",CStr(hex(err.number)),"<%=ComposeAppStatus;%>",0)
			Exit Sub
		End If

		

	End Sub

	</SCRIPT>

<% } else { %>
	<!-- VSSC Compose script: NS compatible functions -->
	<SCRIPT language="JavaScript">
	<!--

	var strFileName;

	// TODO: Remove DEBUG from final release
	var DEBUG = 1;
	// 1 -- Debug mode 0n
	// 0 -- Debug mode Off

// TODO: remove
// TODO: put in common include file
function ConvertToHexNS(error_code)
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

	function CheckIfIDValid()
	{
		var str, ResolveRcpt, strTo, strCc, strBcc;
		var RecipCount;
		var retValue = 0;

		var AppStatus = new java.lang.StringBuffer("");

		VSSC.set_VSSC_CertResolveURL("<%=CertResolveURL;%>");
		if ( ErrorCode = GetLastError() ) {
			SetErrorInfoNS("Compose Operation","",ConvertToHexNS(ErrorCode),"<%=ComposeAppStatus;%>",0);
			return ErrorCode;
		}

		document.VSSC.set_VSSC_SCType("<%=SCType;%>");
		if ( ErrorCode = GetLastError() ) {
			SetErrorInfoNS("Compose Operation","",ConvertToHexNS(ErrorCode),"<%=ComposeAppStatus;%>",0);
			return ErrorCode;
		}

		// BEGIN resolve the sender's email address
		str = VSSC.VSSC_CertificateResolution("<%= tw.session.account.address; %>", AppStatus);
		if ( ErrorCode = GetLastError() ) {
			SetErrorInfoNS("Compose Operation","",ConvertToHexNS(ErrorCode),ConvertToHexNS(AppStatus),0);
			return ErrorCode;
		}

		var item_count = VSSC.get_ResolveRcpt_Recipient_Count();
		if ( ErrorCode = GetLastError() ) {
			SetErrorInfoNS("Compose Operation","",ConvertToHexNS(ErrorCode),"<%=ComposeAppStatus;%>",0);
			return ErrorCode;
		}

		var szEmail, nStatus;

		// the sender is only one !?
		VSSC.ResolveRcpt_First();
		if ( ErrorCode = GetLastError() ) {
			SetErrorInfoNS("Compose Operation","",ConvertToHexNS(ErrorCode),"<%=ComposeAppStatus;%>",0);
			return ErrorCode;
		}

		szEmail = VSSC.get_ResolveRcpt_EmailAddress();
		if ( ErrorCode = GetLastError() ) {
			SetErrorInfoNS("Compose Operation","",ConvertToHexNS(ErrorCode),"<%=ComposeAppStatus;%>",0);
			return ErrorCode;
		}

		CERT_RESOLUTION_FAILED = 0x8000304B;

		nStatus = VSSC.get_ResolveRcpt_RevocationStatus();
		if ( ErrorCode = GetLastError() ) {
			SetErrorInfoNS("Compose Operation","",ConvertToHexNS(ErrorCode),"<%=ComposeAppStatus;%>",0);
			return ErrorCode;
		}


		if ( nStatus != 0 ) {
			SetErrorInfoNS("Compose Operation","",ConvertToHexNS(CERT_RESOLUTION_FAILED),"<%=RevocationStatus;%>",0);
			return CERT_RESOLUTION_FAILED;
		}

		nStatus = VSSC.get_ResolveRcpt_IsCertExpired();
		if ( ErrorCode = GetLastError() ) {
			SetErrorInfoNS("Compose Operation","",ConvertToHexNS(ErrorCode),"<%=ComposeAppStatus;%>",0);
			return ErrorCode;
		}

		if ( nStatus != 0 ) {
			SetErrorInfoNS("Compose Operation","",ConvertToHexNS(CERT_RESOLUTION_FAILED),"<%=ExpirationStatus;%>",0);
			return CERT_RESOLUTION_FAILED;
		}
	}

	function GetBody()
	{
		var body;

		body = VSSC.get_VSSC_Body();
		if ( ErrorCode = GetLastError() ) {
			SetErrorInfoNS("Compose Operation","",ConvertToHexNS(ErrorCode),"<%=ComposeAppStatus;%>",0);
			return;
		}

		return body;
	}

	function GetMessageSize()
	{
		var size;

		size = VSSC.get_VSSC_MsgBlobSize();
		if ( ErrorCode = GetLastError() ) {
			SetErrorInfoNS("Compose Operation","",ConvertToHexNS(ErrorCode),"<%=ComposeAppStatus;%>",0);
			return;
		}

		return size;
	}

	function GetAttachedFileList()
	{
		var file_list;

		file_list = VSSC.get_VSSC_AttachedFileList();
		if ( ErrorCode = GetLastError() ) {
			SetErrorInfoNS("Compose Operation","",ConvertToHexNS(ErrorCode),"<%=ComposeAppStatus;%>",0);
			return "";
		}

		return file_list;
	}

	function GetSelectedAttachmentSize(file_name)
	{
		var size;
		var AppStatus = new java.lang.StringBuffer("");

		size = VSSC.VSSC_SelectedAttachmentSize( file_name, AppStatus );
		if ( ErrorCode = GetLastError() ) {
			SetErrorInfoNS("Decompose Operation","",ConvertToHexNS(ErrorCode),ConvertToHexNS(AppStatus),0);
			return 0;
		}

		return size;
	}



	function VSSC_ONSEND(usePRC)
	{
		var str;
		var strFrom, strTo, strCc, strBcc;
		var strPRC;
		var msgID;

		var MBUnit;
		var MsgBlobSize,BlobSize;
		var MaxBlobSize,EstBlobSize;
		var strMaxMsg;

		var AppStatus = new java.lang.StringBuffer("");
		var ProxyCertStatus = new java.lang.StringBuffer("");
		

		if(bErrorPresent == 1)
			return;

		//*****Setting PRC Related Properties
		// this is going with the recipient logic as we need to set the prc falg from here
		// FIXME - should be dynamically filled in by the server

		// Enable PRC

		// Enable PRC
		// Preferences
		// 0x0000 - Don't Use Proxy Certificate
		// 0x0001 - Use Proxy Certificate when Cert not found
		// 0x0002 - Use Proxy Certificate when Cert expired
		// 0x0004 - Use Proxy Certificate when Cert revoked

		USE_PRC_FOR_NOT_FOUND = 0x0001;
		USE_PRC_FOR_EXPIRED = 0x0002;
		USE_PRC_FOR_REVOKED = 0x0004;
		VSSC_PTA_CANCEL = 0x80001067;

		var Preferences = USE_PRC_FOR_NOT_FOUND | USE_PRC_FOR_EXPIRED | USE_PRC_FOR_REVOKED;
		if (usePRC != 0) {
			VSSC.set_VSSC_UseProxyRecipCert(0x07);
			
		} else {
			VSSC.set_VSSC_UseProxyRecipCert(0x0);
		}
		if ( ErrorCode = GetLastError() ) {
			SetErrorInfoNS("Compose Operation","",ConvertToHexNS(ErrorCode),"<%=ComposeAppStatus;%>",0);
			return ErrorCode;
		}

		
		if (usePRC != 0) {
			  VSSC.VSSC_ResolveProxyRecipCert("<%=PRCEMailAddr;%>", AppStatus, ProxyCertStatus)
			  if ( ErrorCode = GetLastError() ) {
				  SetErrorInfoNS("Compose Operation","",ConvertToHexNS(ErrorCode),ConvertToHexNS(AppStatus),0);
				  return ErrorCode;
			  }
		}
		
		//ResolveRecipients();

		str = document.form1.subject.value;
		VSSC.set_VSSC_Subject(str);
		if ( ErrorCode = GetLastError() ) {
			SetErrorInfoNS("Compose Operation","",ConvertToHexNS(ErrorCode),"<%=ComposeAppStatus;%>",0);
			return ErrorCode;
		}

		str = document.form1.message.value;
		VSSC.set_VSSC_Body(str);
		if ( ErrorCode = GetLastError() ) {
			SetErrorInfoNS("Compose Operation","",ConvertToHexNS(ErrorCode),"<%=ComposeAppStatus;%>",0);
			return ErrorCode;
		}

		if (document.form1.vssc_sign.checked == true) {
			VSSC.set_VSSC_MsgType(3);
		} else {
			VSSC.set_VSSC_MsgType(2);
		}
		if ( ErrorCode = GetLastError() ) {
			SetErrorInfoNS("Compose Operation","",ConvertToHexNS(ErrorCode),"<%=ComposeAppStatus;%>",0);
			return ErrorCode;
		}

		VSSC.VSSC_Compose(AppStatus);
		if ( ErrorCode = GetLastError() ) {
			if(ErrorCode == VSSC_PTA_CANCEL) {
				return ErrorCode;
			} else {
				SetErrorInfoNS("Compose Operation","",ConvertToHexNS(ErrorCode),ConvertToHexNS(AppStatus),0);
				return ErrorCode;
			}
		}

		
		BlobSize=VSSC.get_VSSC_MsgBlobSize();
		if ( ErrorCode = GetLastError() ) {
			SetErrorInfoNS("Compose Operation","",ConvertToHexNS(ErrorCode),"<%=ComposeAppStatus;%>",0);
			return ErrorCode;
		}

		MBUnit=1024 *1024;
		EstBlobSize=BlobSize/MBUnit;
		MsgBlobSize=EstBlobSize/1.76;
		MaxBlobSize=<%=MaxUploadBlobSize;%>;

		if(MsgBlobSize>MaxBlobSize){
				strMaxMsg="<%=MaxLimitMsg;%>";
				alert(strMaxMsg);
				return 1;	
		}

		//Getting the Message out of the plugin is handled differently because of the JavaVM limitation of 8MB
		var Msg = "";
		var MsgTemp ;

		while(true)
		{
			MsgTemp = VSSC.get_VSSC_GetMsg();
			if ( ErrorCode = GetLastError() ) {
				SetErrorInfoNS("Compose Operation","",ConvertToHexNS(ErrorCode),"<%=ComposeAppStatus;%>",0);
				return ErrorCode;
			}

			if(MsgTemp == "")
				break;
			Msg = Msg + MsgTemp;
		}

		document.form1.vssc_blob.value = Msg;

		//document.form1.vssc_blob.value = VSSC.get_VSSC_GetMsg();

		// TODO: post the message ID needed later for inline errors
		VSSC.VSSC_StoreAll( 0, AppStatus );
		if ( ErrorCode = GetLastError() ) {
			SetErrorInfoNS("Compose Operation","",ConvertToHexNS(ErrorCode),ConvertToHexNS(AppStatus),0);
			return ErrorCode;
		}

		document.form1.vssc_message_id.value = VSSC.get_VSSC_MsgObjID();
		if ( ErrorCode = GetLastError() ) {
			SetErrorInfoNS("Compose Operation","",ConvertToHexNS(ErrorCode),"<%=ComposeAppStatus;%>",0);
			return ErrorCode;
		}

		return 0;

	}

	function SetRecipientInfo(strTo,strCc,strBcc)
	{

		if(bErrorPresent == 1)
			return;

		VSSC.set_VSSC_ToRecipientsInfo(strTo.toLowerCase());
		if ( ErrorCode = GetLastError() ) {
			SetErrorInfoNS("Compose Operation","",ConvertToHexNS(ErrorCode),"<%=ComposeAppStatus;%>",0);
			return ErrorCode;
		}
		
		VSSC.set_VSSC_CcRecipientsInfo(strCc.toLowerCase());
		if ( ErrorCode = GetLastError() ) {
			SetErrorInfoNS("Compose Operation","",ConvertToHexNS(ErrorCode),"<%=ComposeAppStatus;%>",0);
			return ErrorCode;
		}

		VSSC.set_VSSC_BccRecipientsInfo(strBcc.toLowerCase());
		if ( ErrorCode = GetLastError() ) {
			SetErrorInfoNS("Compose Operation","",ConvertToHexNS(ErrorCode),"<%=ComposeAppStatus;%>",0);
			return ErrorCode;
		}

		return 0;
	}

	function ResolveRecipients()
	{
		var str, ResolveRcpt, strTo, strCc, strBcc;
		var RecipCount;
		var retValue = 0;

		var AppStatus = new java.lang.StringBuffer("");

		if(bErrorPresent == 1)
			return;

		VSSC.set_VSSC_CertResolveURL("<%=CertResolveURL;%>");
		if ( ErrorCode = GetLastError() ) {
			SetErrorInfoNS("Compose Operation","",ConvertToHexNS(ErrorCode),"<%=ComposeAppStatus;%>",0);
			return ErrorCode;
		}

		document.VSSC.set_VSSC_SCType("<%=SCType;%>");
		if ( ErrorCode = GetLastError() ) {
			SetErrorInfoNS("Compose Operation","",ConvertToHexNS(ErrorCode),"<%=ComposeAppStatus;%>",0);
			return ErrorCode;
		}

		// BEGIN resolve the sender's email address
		str = VSSC.VSSC_CertificateResolution("<%= tw.session.account.address; %>", AppStatus);
		if ( ErrorCode = GetLastError() ) {
			SetErrorInfoNS("Compose Operation","",ConvertToHexNS(ErrorCode),ConvertToHexNS(AppStatus),0);
			return ErrorCode;
		}

		var item_count = VSSC.get_ResolveRcpt_Recipient_Count();
		if ( ErrorCode = GetLastError() ) {
			SetErrorInfoNS("Compose Operation","",ConvertToHexNS(ErrorCode),"<%=ComposeAppStatus;%>",0);
			return ErrorCode;
		}

		var szEmail, nStatus;

		// the sender is only one !?
		VSSC.ResolveRcpt_First();
		if ( ErrorCode = GetLastError() ) {
			SetErrorInfoNS("Compose Operation","",ConvertToHexNS(ErrorCode),"<%=ComposeAppStatus;%>",0);
			return ErrorCode;
		}

		for (var i=0; i<item_count; i++) {
			szEmail = VSSC.get_ResolveRcpt_EmailAddress();
			if ( ErrorCode = GetLastError() ) {
				SetErrorInfoNS("Compose Operation","",ConvertToHexNS(ErrorCode),"<%=ComposeAppStatus;%>",0);
				return ErrorCode;
			}

			nStatus = VSSC.get_ResolveRcpt_Status();
			if ( ErrorCode = GetLastError() ) {
				SetErrorInfoNS("Compose Operation","",ConvertToHexNS(ErrorCode),"<%=ComposeAppStatus;%>",0);
				return ErrorCode;
			}

			// Check nStatus. If = 0, then email not resolved. No corresponding cert.
			VSSC.ResolveRcpt_Next();
			if ( ErrorCode = GetLastError() ) {
				SetErrorInfoNS("Compose Operation","",ConvertToHexNS(ErrorCode),"<%=ComposeAppStatus;%>",0);
				return ErrorCode;
			}
		}

		VSSC.set_VSSC_FromInfo(szEmail);
		if ( ErrorCode = GetLastError() ) {
			SetErrorInfoNS("Compose Operation","",ConvertToHexNS(ErrorCode),"<%=ComposeAppStatus;%>",0);
			return ErrorCode;
		}
		// END resolve the sender's email address

		// Perform certificate resolution  FIXME!!!
		strTo = document.form1.to.value;
		// Resolve the alias name to email addresses from address book before passing onto VSSC. For TO, CC and BCC field values.
		strCc = document.form1.cc.value;
		strBcc = document.form1.bcc.value;

		// FIXME!!! [danail]  insert address book resolution here !!!

		<%
		// FIXME !!!  - add the port
		var host_with_port = tw.httpGateway.hostName;      //AndPort;
		var full_gateway_url = (tw.request.isSSL ? "https" : "http") + "://" + host_with_port;
		full_gateway_url += tw.httpGateway.getUrl('SGMS_TxnAccPackageResolveRecipients.tpl');
		// FIXME !!! - use POST instead of GET method
		//full_gateway_url = tw.httpGateway.appendUrlQueryVariable(full_gateway_url,"to","kire");
		//full_gateway_url = tw.httpGateway.appendUrlQueryVariable(full_gateway_url,"cc","levski@wizcom.bg");
		//full_gateway_url = tw.httpGateway.appendUrlQueryVariable(full_gateway_url,"bcc","dgrigorov@hotmail.com");
		%>

		// FIXME!!! - construction of URL not perfect
//		var InternetURL = "<%= full_gateway_url; %>"
//		InternetURL = InternetURL + "&to=" + document.form1.to.value;
//		InternetURL = InternetURL + "&cc=" + document.form1.cc.value;
//		InternetURL = InternetURL + "&bcc=" + document.form1.bcc.value;
		//This should be set to "", if szMethod = "GET"
//		var InternetPostData = "";
		// This can be "POST" or "GET"
//		var InternetMethod = "GET";
//		VSSC.VSSC_InternetInitialize(InternetURL, InternetMethod, InternetPostData);

//		VSSC.VSSC_InternetSendRequest();
//		if ( ErrorCode = GetLastError() ) {
//			alert("VSSC_InternetSendRequest error: " + ConvertToHexNS(ErrorCode));
//			return ErrorCode;
//		}

		//VSSC.UseInternetData = vbFalse          'This tells VSSC.Decompose to use the Internet data internally. 
		//FIXME!!! - Error 80001003 ?   what is it ?

//		var Message = VSSC.get_VSSC_InternetData();
//		var MessageSize = VSSC.get_VSSC_InternetDataSize();

//		alert("Resolved addresses1: " + Message);
		//var strMessage = BinaryToString(Message); // TODO: BinaryToString
		//var ResolveArr = Message.split(";");
		//alert( "Resolved addresses2: \n" + "To: " + ResolveArr[0] + "\n" + "Cc: " + ResolveArr[1] + "\n" + "Bcc: " + ResolveArr[2] );
		// FIXME!!! [danail]  ... or here !!!

		// The call below does not make sense but otherwise the VSSC behaves oddly
		// was strTo, strCc, strBcc
		//ErrorCode = SetRecipientInfo( Message, "", "");
		//ErrorCode = SetRecipientInfo( ResolveArr[0], ResolveArr[1], ResolveArr[2] );	// was strTo, strCc, strBcc
//		if ( ErrorCode != 0 ) {
//			alert("SetRecipientInfo error: " + ConvertToHexNS(ErrorCode));
//			return ErrorCode;
//		}
		ErrorCode = SetRecipientInfo( strTo, strCc, strBcc );

		if(ErrorCode != 0)
			return ErrorCode;

		str = VSSC.VSSC_SMIMECertificateResolution(AppStatus);
		if ( ErrorCode = GetLastError() ) {
			SetErrorInfoNS("Compose Operation","",ConvertToHexNS(ErrorCode),ConvertToHexNS(AppStatus),0);
			return ErrorCode;
		}

		//TODO: When VSSC starts working remove duplicate recipient check
		RecipCount = VSSC.get_ResolveRcpt_Recipient_Count();
		if ( ErrorCode = GetLastError() ) {
			SetErrorInfoNS("Compose Operation","",ConvertToHexNS(ErrorCode),"<%=ComposeAppStatus;%>",0);
			return ErrorCode;
		}

		//initCertResolution
		// FIXME !!! - populate global arrays for certificate resolution
		VSSC.ResolveRcpt_First();
		if ( ErrorCode = GetLastError() ) {
			SetErrorInfoNS("Compose Operation","",ConvertToHexNS(ErrorCode),"<%=ComposeAppStatus;%>",0);
			return ErrorCode;
		}

		var flagSenderRemoved = false;

		//reset the arrays
		resolvedRecipients.length = 0;
		prcRecipients.length = 0;
		CERTEXISTS = 0x3002;
		for(var i=0; i < RecipCount; i++) {
			szEmail = VSSC.get_ResolveRcpt_EmailAddress();
			if ( ErrorCode = GetLastError() ) {
				SetErrorInfoNS("Compose Operation","",ConvertToHexNS(ErrorCode),"<%=ComposeAppStatus;%>",0);
				return ErrorCode;
			}

			if ((szEmail != "<%= tw.session.account.address; %>") || flagSenderRemoved )
			{


				nStatus = VSSC.get_ResolveRcpt_Status();
				if ( ErrorCode = GetLastError() ) {
					SetErrorInfoNS("Compose Operation","",ConvertToHexNS(ErrorCode),"<%=ComposeAppStatus;%>",0);
					return ErrorCode;
				}

				if (nStatus == CERTEXISTS) {
					addResolvedRecipient(szEmail);
				} else {
					addPRCRecipient(szEmail);
				}
				
			}
			else
			{
				flagSenderRemoved = true;	
			}

			VSSC.ResolveRcpt_Next();
			if ( ErrorCode = GetLastError() ) {
				SetErrorInfoNS("Compose Operation","",ConvertToHexNS(ErrorCode),"<%=ComposeAppStatus;%>",0);
				return ErrorCode;
			}
		}
		
		return 0;
	}


	function UpdateRecipients()
	{
		var strTo = document.form1.to.value;
		// TODO: + "," + "<%= tw.session.account.address; %>";
		var strCc = document.form1.cc.value;
		var strBcc = document.form1.bcc.value;
		var AppStatus = new java.lang.StringBuffer("");

		if(bErrorPresent == 1)
			return;

		var ErrorCode = SetRecipientInfo(strTo, strCc, strBcc);
		if (ErrorCode != 0)
			return ErrorCode;

		var str = VSSC.VSSC_SMIMECertificateResolution(AppStatus);
		if ( ErrorCode = GetLastError() ) {
			SetErrorInfoNS("Compose Operation","",ConvertToHexNS(ErrorCode),ConvertToHexNS(AppStatus),0);
			return ErrorCode;
		}

		return 0;
	}


	function InitVSSC(messageID)
	{
		var AppStatus = new java.lang.StringBuffer("");

		OBJECT_NODE_NOT_FOUND =	0x80005002;
		VSSC_INITIALIZED = 0x80003001;

		if(bErrorPresent == 1)
			return;

		if (messageID == 0){
			VSSC.VSSC_ClearAll(1, AppStatus);
			ErrorCode = VSSC.GetLastError();
			if ( ErrorCode  && ErrorCode != OBJECT_NODE_NOT_FOUND) {
				SetErrorInfoNS("Compose Operation","",ConvertToHexNS(ErrorCode),ConvertToHexNS(AppStatus),0);
				return ErrorCode;
			}

		}

/*
		VSSC.VSSC_Initialize(messageID, 0, AppStatus);
		if ( ErrorCode = GetLastError() ) {
			alert("ERROR in VSSC_Initialize ( " + ConvertToHexNS(ErrorCode) + " )");
			return;
		}
*/		

		VSSC_PLUGIN_NOT_INITIALIZED = 0x80003555;
		var count = 1;
		VSSC.VSSC_Initialize(messageID,0, AppStatus);
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

		VSSC_INITIALIZED = 0x80003001;
		ErrorCode=VSSC.GetLastError();
		if(ErrorCode !=0 && ErrorCode != VSSC_INITIALIZED)
		{
			SetErrorInfoNS("Compose Operation","",ConvertToHexNS(ErrorCode),ConvertToHexNS(AppStatus),0);
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
			//InstalledVer = VSSC.get_VSSC_InstalledPTAVer();
			SetErrorInfoNS("Compose Operation","",ConvertToHexNS(ErrorCode),"<%=ComposeAppStatus;%>",0);
			return;	
		}
		else if(ErrorCode)
		{
			SetErrorInfoNS("Compose Operation","",ConvertToHexNS(ErrorCode),"<%=ComposeAppStatus;%>",0);
			return;
		}

		// TODO: This timeout is configurable. Time is in minutes.
		// TODO: should be >= session timeout !
		VSSC.set_VSSC_CertificateTimeOut(<%=VSSCCertificateTimeout;%>);
		if ( ErrorCode = GetLastError() ) {
			SetErrorInfoNS("Compose Operation","",ConvertToHexNS(ErrorCode),"<%=ComposeAppStatus;%>",0);
			return ErrorCode;
		}

		VSSC.set_VSSC_MessageTimeOut(<%=VSSCMessageTimeout;%>);
		if ( ErrorCode = GetLastError() ) {
			SetErrorInfoNS("Compose Operation","",ConvertToHexNS(ErrorCode),"<%=ComposeAppStatus;%>",0);
			return ErrorCode;
		}

		// build Aments table
		var attachments = VSSC.get_VSSC_SelectedAttachments();
		if ( ErrorCode = GetLastError() ) {
			SetErrorInfoNS("Compose Operation","",ConvertToHexNS(ErrorCode),"<%=ComposeAppStatus;%>",0);
			return ErrorCode;
		}
		if (attachments == null) {
			attachments = "";
		}

		// strange but 'attachments' is not a String object
		var str_att = "" + attachments;
		var files_array = str_att.split(",");
		for(var i=0; i<files_array.length; i++){
			if( (files_array[i] != null) && (files_array[i].length > 0) ){
				addAtachment(files_array[i]);
			}
		}

	}


	function ConfigurePTA()
	{
		var szClientInfo = "<%=strClientInfo;%>";
		var szClientInfoSig = "<%=strClientInfoSig;%>";
		var szAppContextName = "<%=AppContextName; %>";
		// TODO: remove hardcoded host
		//var szAppLogoUrl = "http://localhost/client/images/vhpta.bmp";
		var szAppLogoUrl = "<%=OnSiteHost;%>/SGMSAppLogo.BMP";

		if(bErrorPresent == 1)
			return;

		//**Initialize PTA
		VSSC.PTA_Initialize(szAppContextName,0);
		if ( ErrorCode = GetLastError() ) {
			SetErrorInfoNS("Compose Operation","",ConvertToHexNS(ErrorCode),"<%=ComposeAppStatus;%>",0);
			return ErrorCode;
		}

		//**Setting AppLogo
		VSSC.set_UIPrefs_UILogoUrl(szAppLogoUrl);
		if ( ErrorCode = GetLastError() ) {
			SetErrorInfoNS("Compose Operation","",ConvertToHexNS(ErrorCode),"<%=ComposeAppStatus;%>",0);
			return ErrorCode;
		}

		//**Setting Roaming Properties
		VSSC.set_RoamPrefs_ClientInfo(szClientInfo);
		if ( ErrorCode = GetLastError() ) {
			SetErrorInfoNS("Compose Operation","",ConvertToHexNS(ErrorCode),"<%=ComposeAppStatus;%>",0);
			return ErrorCode;
		}

		VSSC.set_RoamPrefs_ClientInfoSig(szClientInfoSig);
		if ( ErrorCode = GetLastError() ) {
			SetErrorInfoNS("Compose Operation","",ConvertToHexNS(ErrorCode),"<%=ComposeAppStatus;%>",0);
			return ErrorCode;
		}

		VSSC.set_ProfMgmt_RoamProfile(true);
		if ( ErrorCode = GetLastError() ) {
			SetErrorInfoNS("Compose Operation","",ConvertToHexNS(ErrorCode),"<%=ComposeAppStatus;%>",0);
			return ErrorCode;
		}


		VSSC.set_ProfMgmt_IsUsernameEditable(false);
		if ( ErrorCode = GetLastError() ) {
			SetErrorInfoNS("Compose Operation","",ConvertToHexNS(ErrorCode),"<%=ComposeAppStatus;%>",0);
			return ErrorCode;
		}

		//**************PTA
	}

	function VSSelectAttachment()
	{

		var szFile;
		var szFileNameList;
		var nPos;

		// prompts for filename

		var AppStatus = new java.lang.StringBuffer("");

		if(bErrorPresent == 1)
			return;

		VSSC.VSSC_SelectAttachments(AppStatus);
		if ( ErrorCode = GetLastError() ) {
			SetErrorInfoNS("Compose Operation","",ConvertToHexNS(ErrorCode),"<%=ComposeAppStatus;%>",0);
			return ErrorCode;
/*
			switch (ErrorCode) {
				case 80003007:
					alert("File Already Selected");
					break;

				default:
					alert("Unrecognizable Error ( " + ConvertToHexNS(ErrorCode) + " )");
			}
			return;
*/
		}

		onClickAttach();
	}

	function onClickAttach()
	{
		if(bErrorPresent == 1)
			return;

		// Init Plug-in
		UpdateVSSCFromHTML();

		var AppStatus = new java.lang.StringBuffer("");

		VSSC.VSSC_StoreAll(0, AppStatus);
		if ( ErrorCode = GetLastError() ) {
			SetErrorInfoNS("Compose Operation","",ConvertToHexNS(ErrorCode),ConvertToHexNS(AppStatus),0);
			return ErrorCode;
		}

		// clear fields we don't want to submit
		document.form1.subject.value = "";
		document.form1.message.value = "";

		document.form1.vssc_message_id.value = VSSC.get_VSSC_MsgObjID();
		if ( ErrorCode = GetLastError() ) {
			SetErrorInfoNS("Compose Operation","",ConvertToHexNS(ErrorCode),ConvertToHexNS(AppStatus),0);
			return ErrorCode;
		}

		document.form1.submit_action.value = "command_add_file_sgms";
		document.form1.submit();

	}

	function GetLastError()
	{
		return VSSC.GetLastError();
	}

	function UpdateHTMLFromVSSC()
	{
		if(bErrorPresent == 1)
			return;

		var subject = VSSC.get_VSSC_Subject();
		if ( ErrorCode = GetLastError() ) {
			SetErrorInfoNS("Compose Operation","",ConvertToHexNS(ErrorCode),"<%=ComposeAppStatus;%>",0);
			return ErrorCode;
		}
		if( subject == null )
			subject = "";
		document.form1.subject.value = subject;

		var message = VSSC.get_VSSC_Body();
		if ( ErrorCode = GetLastError() ) {
			SetErrorInfoNS("Compose Operation","",ConvertToHexNS(ErrorCode),"<%=ComposeAppStatus;%>",0);
			return ErrorCode;
		}
		if( message == null )
			message = "";
		document.form1.message.value = message;
	}

	function UpdateVSSCFromHTML()
	{
		SetRecipientInfo(document.form1.to.value, document.form1.cc.value, document.form1.bcc.value);
		VSSC.set_VSSC_Subject(document.form1.subject.value);
		if ( ErrorCode = GetLastError() ) {
			SetErrorInfoNS("Compose Operation","",ConvertToHexNS(ErrorCode),"<%=ComposeAppStatus;%>",0);
			return ErrorCode;
		}

		VSSC.set_VSSC_Body(document.form1.message.value);
		if ( ErrorCode = GetLastError() ) {
			SetErrorInfoNS("Compose Operation","",ConvertToHexNS(ErrorCode),"<%=ComposeAppStatus;%>",0);
			return ErrorCode;
		}
	}

	// -->
	</SCRIPT>
<% } %>
