<!-- Copyright (c) 1993-2001 Tumbleweed Communications Corp. All Rights Reserved. -->
<%@include file="TW_GlobalHeaderMenu.tpl" %>

<%@include file="TW_HelperHttpHosts.tpl" %>

<%@include file="TW_HandleError.tpl" %>
<%@include file="TW_HelperSession.tpl" %>
<%@include file="TW_HelperForm.tpl" %>

<%@include file="TW_HelperThrowErrors.tpl" %>
<%@include file="SGMS_HelperAccount.tpl" %>

<%@include file="SGMS_OnSiteHostConfig.tpl" %>

<!-- File name: TW_AccPackage.tpl -->
<!-- NOTE:  This page has no associated DreamWeaver template -->
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 3.2 Final//EN">
<HTML>
<%
var imagepathurl = tw.httpGateway.getImgPathUrl();
var helppathurl = tw.httpGateway.getHelpUrl();

var microsoft_useragent = "microsoft";
var current_useragent = tw.request.userAgentVendor;

// Read from the form context for this transaction
function	ReadErrorFormInput(input)
 {
	
	input.operation=TW_GetFormStringInRange( "operation" );
	input.errortype=TW_GetFormStringInRange( "errortype" );
	input.errorcode=TW_GetFormStringInRange( "errorcode" );
	input.appstatus=TW_GetFormStringInRange( "appstatus" );
	input.msgobjid= TW_GetFormStringInRange( "msgobjid" );

	var appstatus = input.appstatus;
	appstatus = appstatus.toUpperCase();
	switch(appstatus)
	{
		case "80003049":
			 input.errordesc="<b>Unable to verify PTA Version. Contact your Administrator and refer to error code.<b>";
			 break;	
		case "8000304A":
			 input.errordesc="<b>Certificate is revoked or expired. Contact your Administrator and refer to error code.<b>";
			 break;	
		case "8000304B":
			 input.errordesc="<b>Unable to resolve certificate. Contact your Administrator and refer to error code.<b>";
			 break;	
		case "8000304C":
			 input.errordesc="<b>Unable to resolve proxy recipient certificate. Contact your Administrator and refer to error code.<b>";
			 break;	
		case "8000304D":
			 input.errordesc="<b>Unable to sign and encrypt message. Contact your Administrator and refer to error code.<b>";
			 break;	
		case "80006001":
			 input.errordesc="<b>Unable to compose message. Message not sent. Contact your Administrator and refer to error code.<b>";
			 break;	
		case "8000304F":
			 input.errordesc="<b>Unable to verify and decrypt message. Contact your Administrator and refer to error code.<b>";
			 break;	
		case "80006002":
			 input.errordesc="<b>Unable to decrypt message. Contact your Administrator and refer to error code.<b>";
			 break;	
		case "80003051":
			 input.errordesc="<b>Unable to decrypt message. Contact your Administrator and refer to error code.<b>";
			 break;	
		case "80003052":
			 input.errordesc="<b>Unable to view message. Contact your Administrator and refer to error code.<b>";
			 break;	
		case "80006003":
			 input.errordesc = LoginError(input.errorcode); 
			 break;	
		case "80006004":
			 input.errordesc = EnrollmentError(input.errorcode);
			 break;	
		case "80006005":
			 input.errordesc="<b>Your Digital ID has been revoked.<BR><BR>To Compose, Reply or Forward messages, please enroll for a new Digital ID.</b>";
			 break;
		case "80006006":
			 input.errordesc="<b>Your Digital ID has expired.<BR><BR>To Compose, Reply or Forward messages, please enroll for a new Digital ID.<b>";
			 break;
		case "80006008":
			 input.errordesc="<b>Unable to change password. Contact your Administrator and refer to error code.<b>";
			 break;
		case "80006009":
			 input.errordesc="<b>You may be using an older web browser that is not compatible with the latest digital certificate software. <br><br> Versions before Netscape Navigator 4 and Microsoft Internet Explorer 4 are not supported. Please download Netscape Navigator 4.5 or the latest version of Microsoft Internet Explorer.</b>";
			 break;
		case "80003055":
			 input.errordesc="<b>Unable to attach file. Message not sent. Re-attach file(s) and send message.</b>";
			 break;
		default:
			 input.errordesc="<b>Error occured. Contact your Administrator and refer to error code.<b>";
			 break;
			  
	}

	// show specific errors for these errors
	switch(input.errorcode)
	{
		case "80003026":
			 input.errordesc="<b>Unable to attach second file of identical name. To attach, change file name and try again.</b>";
			 break;

		case "80070002":
			 input.errordesc="<b>Unable to find attached file. Message not sent. Re-attach file and send message.</b>";
			 break;

	}

 }

function LoginError(ErrorCode)
{
	var strErrorDesc = "";

	switch(ErrorCode.toUpperCase()) 
	{
		case "1B6":
				strErrorDesc = "<b>Unable to install ActiveX component. PrivatePath service requires installation of this component. Make sure your browser security allows the installation of ActiveX applications.  If not, change security settings and try to login again. If this does not solve the problem, contact your Administrator.</b>";
					// reset error code, it does not need to be shown on error page
				input.errorcode = "0"; 
				break;
		case "8000109A":
				strErrorDesc = "<b>Password is blank. Please click on Login link to log in to the PrivatePath Service.</b>";
					// reset error code, it does not need to be shown on error page
				input.errorcode = "0"; 
				break;

		case "80001091":
		case "80001095":
		case "80001096":
		case "8000102B":
				strErrorDesc = "<b>No valid Digital ID available for this e-mail address.  Make sure that:<br><br>&nbsp;1. You have entered the correct e-mail address.<br>&nbsp;2. You are enrolled for PrivatePath service.<br><br>Please click on Login link to log in to the PrivatePath Service.</b>";
				break;

		default:
				strErrorDesc = "<b>Unable to login. Contact your Administrator and refer to error code.</b>";
				break;

	}

	return strErrorDesc;
}

function EnrollmentError(ErrorCode)
{
	var strErrorDesc = "";

	switch(ErrorCode.toUpperCase()) 
	{
		case "1B6":
				strErrorDesc = "<b>Unable to install ActiveX component. PrivatePath service requires installation of this component. Make sure your browser security allows the installation of ActiveX applications.  If not, change security settings and try to login again. If this does not solve the problem, contact your Administrator.</b>";
					// reset error code, it does not need to be shown on error page
				input.errorcode = "0"; 
				break;
		case "8000109A":
				strErrorDesc = "<b>Password is blank. Please click on Login link to log in to the PrivatePath Service.</b>";
					// reset error code, it does not need to be shown on error page
				input.errorcode = "0"; 
				break;
		case "80001067":
				strErrorDesc="<b>You have cancelled the enrollment at this time. You need to enroll for a DigitialID to view the message.</b>";
				input.errorcode = "0";

		default:
				strErrorDesc = "<b>Unable to Enroll for a DigitialID . Contact your Administrator and refer to error code.</b>";
				break;

	}

	return strErrorDesc;
}


 var input	= new Object();
 input.operation="";
 input.errortype="";
 input.errorcode="";
 input.appstatus="";
 input.msgobjid=0;
 input.ErrorDesc="";
	
 ReadErrorFormInput(input);

%>



<HEAD>
<META HTTP-EQUIV="pragma" CONTENT="no-cache">

<title>VeriSign PrivatePath service</title>
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
			<% if (input.appstatus==LoginAppStatus){%>
				&nbsp;&nbsp;&nbsp;<img src="<%=imagepathurl;%>/arrow.gif">
	            <font color="#ffffff" face="Arial,Verdana,Helvetica" size="-1"><b>
	            &nbsp;<a href="https://<%=getRealSecureHostname();%>" class='nav'>Login</a><b></font><br>
			<% } else if (input.appstatus != BrowserStatus) { %>
				<% 
					TW_MenuBuilder( imagepathurl );
				%>
			<% } %>
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
		<% if (input.errorcode != "0") {%>
		<tr>
			<td>
			<b>System Error Code:  <%=input.errorcode;%></b>
			</td>
		</tr>
		<% } %>
        <tr>
			<td>
			<br>
			<%=input.errordesc;%>
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
