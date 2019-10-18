<!-- Copyright (c) 1993-2001 Tumbleweed Communications Corp. All Rights Reserved. -->
<%@include file="TW_GlobalHeaderMenu.tpl" %>


<%@include file="TW_HandleError.tpl" %>
<%@include file="TW_HelperSession.tpl" %>
<%@include file="TW_HelperForm.tpl" %>

<%@include file="TW_HelperThrowErrors.tpl" %>
<%@include file="SGMS_HelperAccount.tpl" %>

<%@include file="SGMS_OnSiteHostConfig.tpl" %>

<!-- File name: SGMS_PRCErrorPages.tpl -->
<!-- NOTE:  This page has no associated DreamWeaver template -->
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 3.2 Final//EN">
<HTML>
<%
var imagepathurl = tw.httpGateway.getImgPathUrl();
var helppathurl = tw.httpGateway.getHelpUrl();

var microsoft_useragent = "microsoft";
var current_useragent = tw.request.userAgentVendor;
var errorCode = tw.request.getQueryString( "errorCode","0");
var appStatus = tw.request.getQueryString( "appStatus","0");var errordesc ="";
// Read from the form context for this transaction
function	ReadErrorFormInput()
{	if ( appStatus != "0" )	{		switch(appStatus)
		{			// put all configuration errors here					case "80009001":				 errordesc="<b>The server was unable to retrieve your message due to an internal configuration error. Please contact your Administrator and refer to error code.<b>";				 break;	 						case "80009002":				 errordesc="<b>The server was unable to retrieve your message due to an internal error. Please contact your Administrator and refer to the error code.<b>";				 break;	 						case "80009003":				 errordesc="<b>The server was unable to retrieve your message due to an internal configuration error. Please contact your Administrator and refer to the error code.<b>";				 break;	 						case "80009004":				 errordesc="<b>The server was unable to decrypt your message due to an internal system error. Please contact your Administrator and refer to the error code.<b>";				 break;	 						case "80009FFD":
				 errordesc="<b>The server was unable to decrypt your message due to an unexpected error. Please contact your Administrator and refer to the error code.<b>";				 break;								
			default:
				errordesc="<b>The server is unable to retrieve your message due to an internal error. Please contact your Administrator and refer to the error code.<b>";
				break;	 			
		}	}
	else	{	
		errordesc="<b>The server is unable to retrieve your message. Please contact your Administrator.<b>";	}
 }
ReadErrorFormInput();
%>

<HEAD>
<META HTTP-EQUIV="pragma" CONTENT="no-cache">

<title>Verisign - Error</title>
<link rel="stylesheet" href="<%=tw.httpGateway.getStylesheetPathUrl();%>/verisign.css">
</HEAD>

<body bgcolor="#ffffff" background="<%=imagepathurl;%>/background.gif" leftmargin="0" topmargin="0"  marginwidth="0" marginheight="0" name="main">

<table border="0" cellpadding="0" cellspacing="0" align="top">


  <!-- VeriSign logo --><!-- top image -->
  <tr> 
     <td colspan="1" rowspan="1" valign="top" height="84"><img name="logo" src="<%=imagepathurl;%>/verisign.gif" width="150" height="84" border="0"></td>
     <td colspan="3" width="100%"  height="84" valign="top" background="<%=imagepathurl;%>/hd_home.gif"  bgcolor="#d8d7b8"><BR><BR>&nbsp;&nbsp;<br>&nbsp;&nbsp;
      <span class="bigblue">
      Error</span>
      <noscript>
	<br>
	<left>
	  <font size='-1'>Many features on this page will not operate as this browser does not support Javascript.</font> 
	</left>
      </noscript> 
    </td>
  </tr>


  <tr valign="top">
  
   <!-- left nav bar -->
   <td width="150" height="360">
     <table width="100%" cellspacing="0" cellpadding="0" border="0">
	   <tr valign="top">
	     <td valign="top" background="<%=imagepathurl;%>/nav_background.gif" height="360" width="150">
		 
		 <br>
		 <br>
		 <br>
			 <% TW_MenuBuilder( imagepathurl ); %>			
		 </td>
	   </tr>
	 </table>
	</td>
	

<!-- start of content cell -->
    <td width="100%">
	  <table border="0" cellpadding="15" cellspacing="0" width="100%" align="top">
	   <tr>
		<td width="100%" valign="top"> 
		<table>
		<% if ( errorCode != "0" ) {%>
		<tr>
			<td>			System Error Code:  <%=errorCode;%>			
			</td>
		</tr>
		<% } %>		<tr>
			<td>
			<br>
			<%=errordesc;%>
			</td>
		</tr>


		<!-- copyright row -->
		<tr>
			<td height="80" valign="bottom">
			<A HREF="https://www.verisign.com/about/copyright/index.html" target="new"><span class="copyrt">Copyright &#169; 2001,</span></A>
			<A HREF="https://www.verisign.com/about/copyright/index.html" target="new"><span class="copyrt">Privacy Policy,</span></A><span class="copyrtblack"> VeriSign, Inc. All Rights Reserved<BR></span>
			 			
			</td>
		</tr>
		
      	</table>
	  
	  	</td>
	   </tr>
	  </table>
	 </td>
  </tr>
</table>

</BODY>
</HTML>
