<!-- Copyright (c) 1993-2000 Tumbleweed Communications Corp. All Rights Reserved. -->
<!-- File name: TW_AccEnd.tpl -->
<%@include file="SGMS_OnSiteHostConfig.tpl" %>
<%@include file="TW_HelperHttpHosts.tpl" %>

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 3.2 Final//EN"> 
<%
var pageTitle = "PrivatePath Logout";
var imagepathurl = tw.httpGateway.getImgPathUrl();
var strErrorCode = "";
%>

<HTML>
<HEAD>
<!-- put here all page specific the global variables, TW script or JavaScript. See AccDeliveryFolderView.tpl for example -->
<script language="javascript">
<!--

/* Tumbleweed help. We don't use this. Use GoHelp(h_topic)
 *function GoHelp(h_dir, h_topic)
 *{
 *   if (h_topic.charAt(0) == "A"){
 *	h_url="/help/Admin/"+h_dir+"/"+h_topic+".htm";
 *   } else if (h_topic.charAt(0) == "C"){
 *	h_url="/help/Central/"+h_dir+"/"+h_topic+".htm";
 *   }
 *			HWin=window.open(h_url,"HelpWin","toolbar=yes,width=670,height=450,resizable=yes,scrollbars=yes")
 *   if (HWin.focus) HWin.focus()
 *}
 */

function GoHelp(h_topic, h_bookmark)
{
	h_url="/help/" + h_topic + ".htm";
	if (h_bookmark)
	{
		var char0, char1;
		char0 = h_bookmark.charAt(0);
		char1 = h_bookmark.charAt(1);
		// if first 2 letters are CAPS, then switch to Admin help
		if ( (char0 == 'A') && (char1 >= 'A' && char1 <= 'Z') )
		{
			var h_admin_topic = h_bookmark;
			var h_admin_dir = h_topic;
			h_url = "/help/Admin/"+h_admin_dir+"/"+h_admin_topic+".htm";
		} else {
			h_url = h_url + "#" + h_bookmark;
		}
	}
	HWin=window.open(h_url,"HelpWin","toolbar=yes,width=670,height=450,resizable=yes,scrollbars=yes")
	if (HWin.focus) HWin.focus()
}

//-->
</script>
<!-- #BeginEditable "EditHtmlTitle" -->
<title>VeriSign PrivatePath service</title>
<!-- #EndEditable -->
<link rel="stylesheet" href="<%=tw.httpGateway.getStylesheetPathUrl();%>/verisign.css">

<%@include file="SGMS_VSSCDownloadInclude.tpl" %>

<% if(arguments.usesCertificate) //Only broswers supporting certificate should see and use the scripts below
   if( tw.request.userAgentVendor == "microsoft" ) { %>

	<!-- VSSC Log out script: IE compatible functions -->
	<SCRIPT LANGUAGE="VBScript">
	Sub VSSCLogOut
		Dim IVSPTA
		Dim IVSProfMgmt
		Dim AppStatus

		VSSC_INITIALIZED = &h80003001

		On Error Resume Next
		VSSC.Initialize 0,0, AppStatus

		If (err.number <> 0 and err.number <> VSSC_INITIALIZED) Then
			strErrorCode = CStr(Hex(err.number))
			Exit Sub
		End if


		szAppContextName="<%=AppContextName; %>"
		INITIALIZED = &h80001001
		
		'Set the list of PTA versions supported by VSSC		
		DIFFERENT_PTAVER = &h8000300F
		Dim SupportedVer 
		Dim SupportedText
		Dim InstalledVer
				
		SupportedVer = "<%=PTASupportedVer;%>"
		SupportedText = "  Supported Version = "

		On Error Resume Next
		VSSC.SupportedPTAVer = SupportedVer
		If (err.number <> 0) then
			strErrorCode = CStr(Hex(err.number))
			Exit Sub
		End If


		On Error Resume Next
		Set IVSPTA=VSSC.IVSSCPTA
		If (err.number <> 0) then
			strErrorCode = CStr(Hex(err.number))
			Exit Sub
		End If

		On Error Resume Next
		IVSPTA.Initialize szAppContextName,0
		If ( err.number <> INITIALIZED And err.number <> 0) then
			strErrorCode = CStr(Hex(err.number))
			Exit Sub
		End If


		On Error Resume Next
		Set IVSProfMgmt = IVSPTA.IVSProfMgmt
		If (err.number <> 0) then
			strErrorCode = CStr(Hex(err.number))
			Exit Sub
		End If

		On Error Resume Next
		IVSProfMgmt.CloseProfile()
		If (err.number <> 0) then
			strErrorCode = CStr(Hex(err.number))
			Exit Sub
		End If

		OBJECT_NODE_NOT_FOUND =	&h80005002
		On Error Resume Next
		VSSC.ClearAll 0, AppStatus
		If (err.number <> 0 And err.number <> OBJECT_NODE_NOT_FOUND) then
			strErrorCode = CStr(Hex(err.number))
			Exit Sub
		End If
	End Sub
	</SCRIPT>
<% } else { %>
	<!-- VSSC Log out script: NS compatible functions -->
	<SCRIPT language="JavaScript">
	<!--
function VSSCLogOut()
{
		var AppStatus = new java.lang.StringBuffer("");
		//VSSC.VSSC_Initialize(0,0, AppStatus);

		VSSC_PLUGIN_NOT_INITIALIZED = 0x80003555;
		var count = 1;
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

		VSSC_INITIALIZED = 0x80003001;
		ErrorCode=VSSC.GetLastError();
		if(ErrorCode != 0 && ErrorCode != VSSC_INITIALIZED)
		{
			strErrorCode = ConvertToHexNS(ErrorCode);
			return;
		}

		//Set the list of PTA versions supported by VSSC
		DIFFERENT_PTAVER = 0x8000300F;
		var InstalledVer;
		var SupportedVer = "<%=PTASupportedVer;%>";
		var SupportedText = "  Supported Version = ";
		VSSC.set_VSSC_SupportedPTAVer(SupportedVer);
		ErrorCode=VSSC.GetLastError();
		
		if(ErrorCode != 0)
		{
			strErrorCode = ConvertToHexNS(ErrorCode);
			return;
		}


		szAppContextName="<%=AppContextName; %>";
		INITIALIZED = 0x80001001;
		CARDNOTOPEN = 0x80001008;

		VSSC.PTA_Initialize(szAppContextName,0);
		ErrorCode = VSSC.GetLastError();
		if ( ErrorCode != INITIALIZED && ErrorCode != 0) {
			strErrorCode = ConvertToHexNS(ErrorCode);
			return ErrorCode;
		}
		
		VSSC.ProfMgmt_CloseProfile();
		ErrorCode = VSSC.GetLastError();
		if ( ErrorCode != CARDNOTOPEN && ErrorCode != 0 ) {
			strErrorCode = ConvertToHexNS(ErrorCode);
			return ErrorCode;
		}

		OBJECT_NODE_NOT_FOUND =	0x80005002;		
		VSSC.VSSC_ClearAll(0, AppStatus);
		ErrorCode = VSSC.GetLastError();
		if ( ErrorCode  && ErrorCode != OBJECT_NODE_NOT_FOUND) {
			strErrorCode = ConvertToHexNS(ErrorCode);
			return ErrorCode;
		}
	}



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
	// -->
	</SCRIPT>
<% } %>

</HEAD>
<body bgcolor="#ffffff" background="<%=imagepathurl;%>/background.gif" leftmargin="0" topmargin="0"  marginwidth="0" marginheight="0" name="main" <% if(arguments.usesCertificate) { %> onload="VSSCLogOut()" <% } %>>

<%
// Variables here
var table_border_TW_AccEnd = 0;  //for debugging purposes
%>

<TABLE border="<%=table_border_TW_AccEnd;%>" cellpadding="0" cellspacing="0" width="100%">

  <!-- VeriSign logo --><!-- top image -->
  <TR> 
    <TD colspan="1" rowspan="1" width="150" valign="top" height="84"><img name="logo" src="<%=imagepathurl;%>/verisign.gif" width="150" height="84" border="0"></TD>
    <TD colspan="3" height="84" valign="top" nowrap background="<%=imagepathurl;%>/hd_home.gif"  bgcolor="#d8d7b8"><BR><BR>&nbsp;&nbsp;<br>&nbsp;&nbsp;
      <span class="bigblue">
      <%=pageTitle;%></span>
    </TD>
  </TR>

  <TR valign="top">
    <!-- left nav bar -->
    <TD rowspan="1" height="360">
	<TABLE width="100%" cellspacing="0" cellpadding="0" border="<%=table_border_TW_AccEnd;%>">
	  <TR valign="top">
	    <TD colspan="2" valign="top" background="<%=imagepathurl;%>/nav_background.gif" height="360" width="150">
	      <br>
	      <br>
	      <br>
		&nbsp;&nbsp;&nbsp;<IMG src="<%=imagepathurl;%>/arrow.gif">&nbsp;<SPAN class="navNoLink">Logout</SPAN>
	    </TD>
	  </TR>
	</TABLE>
    </TD>
    <!-- left vertical spacer -->
    <TD rowspan="1" width="20"><IMG src="<%=imagepathurl;%>/spacer.gif" width="20" border="0"></TD>

    <TD height="400" width="100%">
	<TABLE height="100%" width="100%" cellspacing="0" cellpadding="0" border="<%=table_border_TW_AccEnd;%>">
	  <TR>
	    <!-- horizontal spacer -->
	    <TD height="20" colspan="1">
	      <IMG src="<%=imagepathurl;%>/spacer.gif" height="20">
	      <noscript>
		<BR>
		<center>
		  <font color='#ff0000' face='Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular' size='-1'><B>Many features on this page will not operate as this browser does not support Javascript.</B></font> 
		</center>
	      </noscript> 
	    </TD>
	    <!-- right vertical spacer -->
	    <TD rowspan="3"><IMG src="<%=imagepathurl;%>/spacer.gif" width="20" border="0"></TD>
	  </TR>
	  <TR>
	    <td valign="top">

	<table cellpadding=0 cellspacing=0 border="0" width="100%">           
	  <tr>
	    <td width=100%> <!-- #BeginEditable "EditMainTableContent" -->
		<table border="0" cellpadding="0" valign="TOP" width="100%">

		  <% if (strErrorCode == "") { %>
				  <tr>
				    <td><b>You are now logged out of the PrivatePath service.</b></td>
				  </tr>
				  <tr>
				    <td><img height=15 src="<%=imagepathurl;%>/spacer.gif"></td>
				  </tr>
				  <tr>
				    <td><a href="<%=getCurrentRealURL();%>">Log in</a> to PrivatePath</td>
				  </tr>
		  <% } else { %>
				  <tr>
				    <td>System Error Code: <%= strErrorCode; %></td>
				  </tr>
				  <tr>
				    <td><img height=15 src="<%=imagepathurl;%>/spacer.gif"></td>
				  </tr>
				  <tr>
				    <td>Error occured while closing the profile. Please restart your browser and log in to PrivatePath Service again.</td>
				  </tr>
		  <% } %>
		</table>
	    </td>
	  </tr>
	</table>

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
<!-- #EndTemplate -->
</HTML>

