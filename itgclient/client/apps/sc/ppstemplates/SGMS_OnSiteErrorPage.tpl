<!-- Copyright (c) 1993-2001 Tumbleweed Communications Corp. All Rights Reserved. -->
<%@include file="TW_GlobalHeaderMenu.tpl" %>


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
		
	var error;

	//input.appstatus=TW_GetFormStringInRange( "appstatus" );
	error=TW_GetFormStringInRange( "error_status");

	input.error_status = error.toUpperCase();

	switch(input.error_status)
	{
		case "7000":
		case "1B58":
		case "1B59":
		case "A104":
		case "3062":
			 input.errordesc = "<b>Check your inbox at the e-mail address you entered in the enrollment form for an e-mail from your administrator. It will contain instructions for installing the Digital ID.</b>";
			 input.errorheader = "Check E-mail";
			 break;	
		case "A001":
			 input.errordesc="<b>The information provided with your request does not meet our authentication requirements. If you continue to get this error, contact the Administrator.</b>";
			 input.errorheader = "Digital ID cannot be Issued";
			 break;	
		case "A002":
			 input.errordesc="<b>The information provided with your request does not meet our authentication requirements. If you continue to get this error, contact the Administrator.</b>";
			 input.errorheader = "Digital ID cannot be Issued";
			 break;	
		case "A003":
			 input.errordesc="<b>If you continue to get this error, contact the Administrator.</b>";
			 input.errorheader = "Signing Error";
			 break;	
		case "A004":
			 input.errordesc="<b>If you continue to get this error, contact the Administrator.</b>";
			 input.errorheader = "Registration Error";
			 break;	
		case "A005":
			 input.errordesc="<b>If you continue to get this error, contact the Administrator.</b>";
			 input.errorheader = "Out of Memory";
			 break;	
		case "A006":
			 input.errordesc="<b>If you continue to get this error, contact the Administrator.</b>";
			 input.errorheader = "Invalid Digital ID";
			 break;	
		case "A007":
			 input.errordesc="<b>If you continue to get this error, contact the Administrator.</b>";
			 input.errorheader = "Hardware Error";
			 break;	
		case "A008":
			 input.errordesc="<b>If you continue to get this error, contact the Administrator.</b>";
			 input.errorheader = "Invalid Configuration File";
			 break;	
		case "A009":
			 input.errordesc="<b>Either the authentication server or the signer device could not be reached to process your request. If you continue to get this error, contact the Administrator.</b>";
			 input.errorheader = "Cannot Process Request";
			 break;
		case "A00A":
			 input.errordesc="<b>If you continue to get this error, contact the Administrator.</b>";
			 input.errorheader = "Signer could not Initialize";
			 break;
		case "A0CA":
			 input.errordesc="<b>The LDAP server could not be reached to process your request. If you continue to get this error, contact the administrator.</b>";
			 input.errorheader = "Server Error";
			 break;
		case "A0CB":
			 input.errordesc="<b>Your enrollment failed because an error occurred when trying to connect to the LDAP server.</b>";
			 input.errorheader = "Authentication Error";
			 break;
		case "A0CC":
			 input.errordesc="<b>Your enrollment failed because the verification attribute was not found in the LDAP directory.</b>";
			 input.errorheader = "Verification Error";
			 break;
		case "A0D3":
			 input.errordesc="<b>Your enrollment failed because the information in the enrollment form that you supplied to identify yourself is incorrect. For example, you may have supplied a password that is incorrect.</b>";
			 input.errorheader = "Authentication Error";
			 break;
		case "A0D4":
			 input.errordesc="<b>Your enrollment failed because the server that is used to verify the information you supplied in the enrollment form could not be accessed.</b>";
			 input.errorheader = "Authentication Error";
			 break;
		case "3061":
		case "D061":
			 input.errordesc="<b>The information provided with your request does not meet our authentication requirements. If you continue to get this error, contact the administrator.</b>";
			 input.errorheader = "Digital ID cannot be Issued";
			 break;
		case "1005":
		case "B005":
			 input.errordesc="<b>The information submitted already exists in another Digital ID.</b><br><br>If you have enrolled in the last 24 hours please check your email for a message from the Administrator. Follow the instructions included in that email.<br><br>To receive a new Digital ID, enroll with a different name.<br>If you have previously installed the Digital ID, you can view it at Digital ID Center. Digital IDs can be found by searching with the name or E-mail address in the Digital ID.";
			 input.errorheader = "Duplicate Digital ID";
			 break;
		case "30CA":
			 input.errordesc="<b>Your enrollment failed because you did not supply the correct passcode.</b>";
			 input.errorheader = "Passcode Mismatch";
			 break;
		case "30CB":
			 input.errordesc="<b>Your passcode has expired. Please contact your administrator for more details.</b>";
			 input.errorheader = "Passcode Expired";
			 break;
		case "3117":
			 input.errordesc="<b>Your enrollment failed because you did not supply the correct passcode.</b>";
			 input.errorheader = "Passcode Mismatch";
			 break;
		case "3118":
			 input.errordesc="<b>Your passcode has been locked because you have exceeded the permitted number of enrollment attempts. Please contact your administrator for more information.</b>";
			 input.errorheader = "Locked Passcode";
			 break;
		case "3119":
			 input.errordesc="<b>Your enrollment failed because the passcode you supplied has already been used for another enrollment. Please contact your administrator for more information.</b>";
			 input.errorheader = "Passcode Error";
			 break;
		default:
			 input.errordesc="<b>Please try again. If you continue to get this error, contact your Administrator.</b>";
			 input.errorheader = "Server Failure";
			 break;
			  
	}

 }




 var input	= new Object();
 //input.appstatus="";
 input.error_status="";
 input.errordesc="";
 input.errorheader="";
	
 ReadErrorFormInput(input);

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
        <tr>
			<td>
			<br>
				<font color="#cc0000" face="verdana, arial, helvetica" size=5><b><%=input.errorheader;%></b></font>	
			</td>
		</tr>
        <tr>
			<td>
			<font face="verdana, arial, helvetica" size=2><%=input.errordesc;%></font>			
			</td>

		</tr>
        <tr>
			<td>
			<br>
			<b>Status Code: <%=input.error_status;%> </b>
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
