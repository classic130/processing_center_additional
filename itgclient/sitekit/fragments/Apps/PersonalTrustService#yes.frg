
<!-- VSSKBEGINPOLICYVAL#yes#1#1.0.0.3 -->
<HEAD>
<TITLE>Logout</TITLE>
<META HTTP-EQUIV="Pragma" CONTENT="no-cache">
<META HTTP-EQUIV="Expires" CONTENT="-1">

<!-- VSSKBEGIN Enrollment/CharEncoding#3 -->
<!-- VSSKEND Enrollment/CharEncoding#3 -->

</HEAD>
<BODY BGCOLOR="#FFFFFF" LINK="#333333" TEXT="#333333" VLINK="#333333" ALINK="#CCCCCC">

<CENTER>
<FONT SIZE="3" COLOR="#0033CC" FACE="arial,helvetica,verdana,sans-serif"><B>Logging Out...</B></FONT>

<form name="LogoutForm" action="%%ptsServerUrl%%/vspts/pts" method="post">
  <input type="hidden" name="Action"               value="Logout">
  <input type="hidden" name="AppContextName"       value="%%Apps/PTAv2::ptaAppName%%">
  <input type="hidden" name="ReturnURL"            value="%%Apps/PTAv2::ptaAppHomeUrl%%">

  <!-- VSSKBEGIN Apps/PersonalTrustService#9 -->
  <!-- VSSKEND Apps/PersonalTrustService#9 -->

<!-- VSSKBEGIN Apps/PersonalTrustService#28 -->
<!-- VSSKEND Apps/PersonalTrustService#28 -->

  <p>
  <input type="submit" name="Submit" value="Submit">
  
  <br>
</form>
</CENTER>

<Script Language="JavaScript">
<!--
function DoLogout()
{
  document.LogoutForm.submit();    
}
window.setTimeout("DoLogout()",1000);
//-->
</Script>
</BODY>
<!-- VSSKENDPOLICYVAL#yes#1 -->

<!-- VSSKBEGINPOLICYVAL#yes#2#1.0.0.3 -->
<FORM name=theform action="%%ptsServerUrl%%/vspts/pts" method=post>
<INPUT type="hidden" name="AppContextName"  value="%%Apps/PTAv2::ptaAppName%%">
<INPUT type="hidden" name="RoamingClientInfo" value="%%Apps/PTAv2/Roaming::clientInfo%%">
<INPUT type="hidden" name="RoamingClientInfoSig" value="%%Apps/PTAv2/Roaming::clientInfoSig%%">
<INPUT type="hidden" name="SrchCritIssuerDN" value="%%::ptaIssuerDN%%">

<!-- VSSKBEGIN Apps/PersonalTrustService#28 -->
<!-- VSSKEND Apps/PersonalTrustService#28 -->

<!-- VSSKENDPOLICYVAL#yes#2 -->


<!-- VSSKBEGINPOLICYVAL#yes#3#1.0.0.4 -->
<FORM name=proform action="%%ptsServerUrl%%/vspts/pts" ENCTYPE=x-www-form-encoded METHOD="POST">
<INPUT type="hidden" name="AppContextName"  value="%%Apps/PTAv2::ptaAppName%%">
<INPUT type="hidden" name="RoamingClientInfo" value="%%Apps/PTAv2/Roaming::clientInfo%%">
<INPUT type="hidden" name="RoamingClientInfoSig" value="%%Apps/PTAv2/Roaming::clientInfoSig%%">
<!-- VSSKBEGIN Global/Mode#110 -->
<!-- VSSKEND Global/Mode#110 -->

<!-- profile settings -->
<INPUT TYPE="hidden" name="ProfileTimeout" value="%%Apps/PTAv2::ptaPasswordTimeout%%">
<INPUT TYPE="hidden" name="PasswordLockOutTries" value="%%Apps/PTAv2::ptaPasswordLockout%%">
<INPUT TYPE="hidden" name="ProfileUnlockPeriod" value="%%Apps/PTAv2::ptaPasswordUnlock%%">
<INPUT TYPE="hidden" name="PasswordLenDefMin" value="%%Apps/PTAv2::ptaPasswordLength%%">
<INPUT TYPE="hidden" name="PasswordQualityCode" value="%%Apps/PTAv2::ptaPasswordQuality%%">
<INPUT TYPE="hidden" name="RequiredPasswordQuality">
<INPUT TYPE="hidden" name="PasswordQualReqNoNum">

<!-- key settings -->
<INPUT TYPE="hidden" name="KeySize" value="%%Enrollment/KeyLength::policyValue%%">

<!-- VSSKBEGIN Apps/PersonalTrustService#28 -->
<!-- VSSKEND Apps/PersonalTrustService#28 -->

<!-- VSSKENDPOLICYVAL#yes#3 -->

<!-- VSSKBEGINPOLICYVAL#yes#4 -->
<TABLE WIDTH=588 BGCOLOR="#ccffff" CELLPADDING=2 CELLSPACING=0 BORDER=0>
<TR>
	<TD WIDTH=50 ALIGN=left VALIGN=top>
      <P>
       <A HREF='client/changePasswdPTS.htm'>
       <IMG align=left border=0 height=40 src="graphics/action_arrowyellow.gif" width=40></A> </P>
      <P>&nbsp;</P>
      <P>&nbsp;</P>
	</TD>
	<TD WIDTH=538 ALIGN=left VALIGN=top>
        <A HREF='client/changePasswdPTS.htm'>
	<FONT FACE="verdana, arial, helvetica" SIZE=4><B>Change Password</B></FONT></A><BR>
	<FONT FACE="arial, helvetica" SIZE=2>Change the password for your PTS profile. 
	</FONT>
	<P></P>
	</TD>
</TR>
<p>
<!-- VSSKENDPOLICYVAL#yes#4 -->

<!-- VSSKBEGINPOLICYVAL#yes#5 -->
</HEAD>
<BODY BGCOLOR="ffffff" LINK="cc0000" VLINK="666666">
<!-- VSSKENDPOLICYVAL#yes#5 -->

// information for userInstallPTS.htm
<!-- VSSKBEGINPOLICYVAL#yes#6#1.0.0.6 -->
<FORM NAME="InstallForm" ACTION="%%ptsServerUrl%%/vspts/pts" ENCTYPE=x-www-form-encoded METHOD="POST">
<input type="hidden" name="Action" value="InstallCertificate,SetCertificateProperties,SaveProfile,Logout">
<INPUT type="hidden" name="AppContextName"  value="%%Apps/PTAv2::ptaAppName%%">
<INPUT type="hidden" name="RoamingClientInfo" value="%%Apps/PTAv2/Roaming::clientInfo%%">
<INPUT type="hidden" name="RoamingClientInfoSig" value="%%Apps/PTAv2/Roaming::clientInfoSig%%">
<INPUT type="hidden" name="CertProperties" value="NewCertProperties">
<INPUT type="hidden" name="NewCertProperties" value="Separator=|SerialNumber=$$cert_serial$$| IssuerDN=%%::ptaIssuerDN%%| FrndlyName=%%Apps/PTAv2::ptaCertFriendlyName%%| LogoUrl=%%Apps/PTAv2::ptaCertLogoURL%%| TextureUrl=%%Apps/PTAv2::ptaCertTextureURL%%">
<!-- VSSKBEGIN Global/Mode#111 -->
<!-- VSSKEND Global/Mode#111 -->

<INPUT TYPE="hidden" NAME="InstallCertificate.WizardTitle" VALUE="">
<INPUT TYPE="hidden" NAME="InstallCertificate.OpenProfile.Title" VALUE="">
<INPUT TYPE="hidden" NAME="InstallCertificate.OpenProfile.Text" VALUE="">
<INPUT TYPE="hidden" NAME="InstallCertificate.OpenProfile.HelpUrl" VALUE="">

<!-- VSSKBEGIN Apps/PersonalTrustService#28 -->
<!-- VSSKEND Apps/PersonalTrustService#28 -->

<!-- VSSKENDPOLICYVAL#yes#6 -->

<!-- VSSKBEGINPOLICYVAL#yes#7 -->
<TR>
	<TD WIDTH=50 ALIGN=left VALIGN=top>
        <A HREF="client/userEnrollPTS.htm">
	  <IMG SRC="graphics/action_checkyellow.gif" WIDTH="40" HEIGHT="40" BORDER="0"></A>
	</TD>
	<TD WIDTH=538 ALIGN=left VALIGN=top>
        <A HREF="client/userEnrollPTS.htm">
   	  <FONT FACE="verdana, arial, helvetica" SIZE=5><B>ENROLL</B></FONT></A><BR>
	  <FONT FACE="arial, helvetica" SIZE=2>Choose this option to enroll for a Digital ID for Microsoft or Firefox.</FONT>
	   <P>
	</TD>
</TR>
<!-- VSSKENDPOLICYVAL#yes#7 -->

<!-- VSSKBEGINPOLICYVAL#yes#8 -->
<TR>
	<TD WIDTH=50 ALIGN=left VALIGN=top>
        <A HREF="client/ptspickup.htm">
  	  <IMG SRC="graphics/action_arrowyellow.gif" WIDTH=40 HEIGHT=40 BORDER=0 ALT=""></A>
	</TD>
	<TD WIDTH=538 ALIGN=left VALIGN=top>
        <A HREF="client/ptspickup.htm">
	  <FONT FACE="verdana, arial, helvetica" SIZE=5><B>PICK-UP ID</B></FONT></A><BR>
	  <FONT FACE="arial, helvetica" SIZE=2>Choose this option if you have enrolled for a Digital ID but have not picked it up.</FONT>
	  <P>
	</TD>
</TR>
<!-- VSSKENDPOLICYVAL#yes#8 -->


//-- global variables for PTS pages 
<!-- VSSKBEGINPOLICYVAL#yes#9 -->
  <!-- PTS UI settings -->
  <INPUT TYPE="hidden" name="AppHeaderLogoURL" value="%%Apps/PersonalTrustService::ptsHeaderLogo%%">
  <INPUT TYPE="hidden" name="AppFooterLogoURL" value="%%Apps/PersonalTrustService::ptsFooterLogo%%">

  <!-- PTS Language/style settings -->
  <INPUT TYPE="hidden" name="Language" value="%%Apps/PersonalTrustService::ptsLanguage%%">
  <INPUT TYPE="hidden" name="deviceLanguage" value="html">

  <INPUT TYPE="hidden" NAME="CertJurHash" VALUE="%%::jurisdictionHash%%">

  <!-- PTS Cancel URL -->
  <!-- VSSKBEGIN Global/Mode#113 -->
  <!-- VSSKEND Global/Mode#113 -->
<!-- VSSKENDPOLICYVAL#yes#9 -->


// stuff for the login page
<!-- VSSKBEGINPOLICYVAL#yes#10 -->
<INPUT TYPE="hidden" NAME="SignChallenge.WizardTitle" VALUE="%%Apps/PTAv2::ptaLoginWizardTitle%%">

<INPUT TYPE="hidden" NAME="SignChallenge.OpenProfile.Title" VALUE="%%Apps/PTAv2::ptaLoginChooseTitle%%">
<INPUT TYPE="hidden" NAME="SignChallenge.OpenProfile.Text" VALUE="%%Apps/PTAv2::ptaLoginChooseText%%">
<INPUT TYPE="hidden" NAME="SignChallenge.OpenProfile.HelpUrl" VALUE="">

<INPUT TYPE="hidden" NAME="SignChallenge.SelectID.Title" VALUE="%%Apps/PTAv2::ptaLoginTitle%%">
<INPUT TYPE="hidden" NAME="SignChallenge.SelectID.Text" VALUE="%%Apps/PTAv2::ptaLoginText%%">
<INPUT TYPE="hidden" NAME="SignChallenge.SelectID.HelpUrl" VALUE="">

<INPUT TYPE="hidden" NAME="SignChallenge.PostMessage" VALUE="Please wait while we submit your authentication information to the web-site...">

<!-- VSSKENDPOLICYVAL#yes#10 -->


// stuff for the Transaction signing page
<!-- VSSKBEGINPOLICYVAL#yes#11 -->
<INPUT TYPE="hidden" NAME="SignTransaction.WizardTitle" VALUE="%%Apps/PTAv2::ptaSignWizardTitle%%">

<INPUT TYPE="hidden" NAME="SignTransaction.OpenProfile.Title" VALUE="%%Apps/PTAv2::ptaLoginChooseTitle%%">
<INPUT TYPE="hidden" NAME="SignTransaction.OpenProfile.Text" VALUE="%%Apps/PTAv2::ptaLoginChooseText%%">
<INPUT TYPE="hidden" NAME="SignTransaction.OpenProfile.HelpUrl" VALUE="">

<INPUT TYPE="hidden" NAME="SignTransaction.SelectID.Title" VALUE="%%Apps/PTAv2::ptaSignTitle%%">
<INPUT TYPE="hidden" NAME="SignTransaction.SelectID.Text" VALUE="%%Apps/PTAv2::ptaSignText%%">
<INPUT TYPE="hidden" NAME="SignTransaction.SelectID.HelpUrl" VALUE="">

<INPUT TYPE="hidden" NAME="SignTransaction.RvwMsg.Title" VALUE="%%Apps/PTAv2::ptaReviewTitle%%">
<INPUT TYPE="hidden" NAME="SignTransaction.RvwMsg.Text" VALUE="%%Apps/PTAv2::ptaReviewText%%">
<INPUT TYPE="hidden" NAME="SignTransaction.RvwMsg.HelpUrl" VALUE="">

<INPUT TYPE="hidden" NAME="SignTransaction.PostMessage" VALUE="Please wait while we submit your signed transaction to the web-site...">

<!-- VSSKENDPOLICYVAL#yes#11 -->

// for the userEnrollPTS page
<!-- VSSKBEGINPOLICYVAL#yes#12 -->
<INPUT TYPE="hidden" NAME="RequestCertificate.WizardTitle" VALUE="Create New Profile">

<INPUT TYPE="hidden" NAME="RequestCertificate.NewUser.Title" VALUE="%%Apps/PTAv2::ptaNewProfileTitle%%">
<INPUT TYPE="hidden" NAME="RequestCertificate.NewUser.Text" VALUE="%%Apps/PTAv2::ptaNewProfileText%%">
<INPUT TYPE="hidden" NAME="RequestCertificate.NewUser.HelpUrl" VALUE="">

<INPUT TYPE="hidden" NAME="RequestCertificate.OpenProfile.Title" VALUE="%%Apps/PTAv2::ptaLoginChooseTitle%%">
<INPUT TYPE="hidden" NAME="RequestCertificate.OpenProfile.Text" VALUE="%%Apps/PTAv2::ptaLoginChooseText%%">
<INPUT TYPE="hidden" NAME="RequestCertificate.OpenProfile.HelpUrl" VALUE="">

<INPUT TYPE="hidden" NAME="RequestCertificate.PostMessage" VALUE="Please wait while your request for enrollment is being processed...">
<!-- VSSKENDPOLICYVAL#yes#12 -->

<!-- VSSKBEGINPOLICYVAL#yes#13#1.0.0.2 -->
<FORM name=proform action="%%ptsServerUrl%%/vspts/pts" ENCTYPE=x-www-form-encoded METHOD="POST">
<INPUT type="hidden" name="AppContextName"  value="%%Apps/PTAv2::ptaAppName%%">
<INPUT type="hidden" name="RoamingClientInfo" value="%%Apps/PTAv2/Roaming::clientInfo%%">
<INPUT type="hidden" name="RoamingClientInfoSig" value="%%Apps/PTAv2/Roaming::clientInfoSig%%">

<!-- profile settings -->
<INPUT TYPE="hidden" name="ProfileTimeout" value="%%Apps/PTAv2::ptaPasswordTimeout%%">
<INPUT TYPE="hidden" name="PasswordLockOutTries" value="%%Apps/PTAv2::ptaPasswordLockout%%">
<INPUT TYPE="hidden" name="ProfileUnlockPeriod" value="%%Apps/PTAv2::ptaPasswordUnlock%%">
<INPUT TYPE="hidden" name="PasswordLenDefMin" value="%%Apps/PTAv2::ptaPasswordLength%%">
<INPUT TYPE="hidden" name="PasswordQualityCode" value="%%Apps/PTAv2::ptaPasswordQuality%%">
<INPUT TYPE="hidden" name="RequiredPasswordQuality">
<INPUT TYPE="hidden" name="PasswordQualReqNoNum">

<INPUT TYPE="hidden" NAME="ChangePassword.WizardTitle" VALUE="Change Password">

<INPUT TYPE="hidden" NAME="ChangePassword.OpenProfile.Title" VALUE="%%Apps/PTAv2::ptaLoginChooseTitle%%">
<INPUT TYPE="hidden" NAME="ChangePassword.OpenProfile.Text" VALUE="%%Apps/PTAv2::ptaLoginChooseText%%">
<INPUT TYPE="hidden" NAME="ChangePassword.OpenProfile.HelpUrl" VALUE="">

<INPUT TYPE="hidden" NAME="ChangePassword.NewPassword.Title" VALUE="Change your profile password">
<INPUT TYPE="hidden" NAME="ChangePassword.NewPassword.Text" VALUE="Enter your new password to change your profile password.">
<INPUT TYPE="hidden" NAME="ChangePassword.NewPassword.HelpUrl" VALUE="">

<!-- VSSKBEGIN Apps/PersonalTrustService#28 -->
<!-- VSSKEND Apps/PersonalTrustService#28 -->

<!-- VSSKENDPOLICYVAL#yes#13 -->

<!-- VSSKBEGINPOLICYVAL#yes#14 -->
<Script Language="JavaScript">
<!--
    function setPasswordQuality(form) {
        if (form.PasswordLenDefMin == "0") {
            form.RequiredPasswordQuality.value = "AnyPasswordOK";
            form.PasswordQualReqNoNum.value = "0";
            return;
        }

        if (form.PasswordQualityCode.value == "16640") {
            form.RequiredPasswordQuality.value = "AlphaNumeric_NoPosReq";
            form.PasswordQualReqNoNum.value = "1";
        } 
        else if (form.PasswordQualityCode.value == "16688") {
            form.RequiredPasswordQuality.value = "AlphaNumeric_NumNotAtBeginEnd";
            form.PasswordQualReqNoNum.value = "1";
        }
        else if (form.PasswordQualityCode.value == "16896") {
            form.RequiredPasswordQuality.value = "AlphaNumeric_NoPosReq";
            form.PasswordQualReqNoNum.value = "2";
        }
        else if (form.PasswordQualityCode.value == "16944") {
            form.RequiredPasswordQuality.value = "AlphaNumeric_NumNotAtBeginEnd";
            form.PasswordQualReqNoNum.value = "2";
        }
        else if (form.PasswordQualityCode.value == "12288") {
            form.RequiredPasswordQuality.value = "NumericOnly";
            form.PasswordQualReqNoNum.value = "0";
        }
        else if (form.PasswordQualityCode.value == "16384") {
            form.RequiredPasswordQuality.value = "AnyPasswordOK";
            form.PasswordQualReqNoNum.value = "0";
        }

        //alert ("Password Quality Code : " + form.PasswordQualityCode.value);
        //alert ("Password Quality : " + form.RequiredPasswordQuality.value);
        //alert ("PassQualReqNoNum : " + form.PasswordQualReqNoNum.value);
    }
//-->
</Script>
<!-- VSSKENDPOLICYVAL#yes#14 -->

<!-- VSSKBEGINPOLICYVAL#yes#15 -->
<Script Language="JavaScript">
<!--
var HomeURL="%%Apps/PTAv2::ptaAppHomeUrl%%";
//-->
</Script>
<!-- VSSKENDPOLICYVAL#yes#15 -->

<!-- VSSKBEGINPOLICYVAL#yes#16 -->
<!-- begin PTS preference -->
<TR>
	<TD WIDTH=50 ALIGN=left VALIGN=top>
        <Script Language="JavaScript">
        <!-- 
        if (navigator.appName == "Netscape")
           {document.write("<A HREF='ptaprefCenter.htm'>")}
        else
           {document.write("<A HREF='ptaprefCenter.htm'>")}
        //-->
        </Script>
	<IMG SRC="graphics/action_arrowyellow.gif" border=0 WIDTH=40 HEIGHT=40 ALIGN=LEFT></A>
	</TD>
	<TD WIDTH=538 ALIGN=left VALIGN=top>
        <Script Language="JavaScript">
        <!-- 
        if (navigator.appName == "Netscape")
           {document.write("<A HREF='ptaprefCenter.htm'>")}
        else
           {document.write("<A HREF='ptaprefCenter.htm'>")}
        //-->
        </Script>
	<FONT FACE="verdana, arial, helvetica" SIZE=4><B>PTS PREFERENCE MANAGEMENT</B></FONT></A><BR>
	<FONT FACE="arial, helvetica" SIZE=2>Choose this option to change the preferences for your PTS profile. 
	</FONT>
	<P>
	</TD>
</TR>
<!-- end change password -->

<!-- VSSKENDPOLICYVAL#yes#16 -->


<!-- VSSKBEGINPOLICYVAL#yes#17 -->
login-page-ms="c:/VeriSign/pta/config/ptsLogin.htm"
login-page-ns="c:/VeriSign/pta/config/ptsLogin.htm"
<!-- VSSKENDPOLICYVAL#yes#17 -->

<!-- VSSKBEGINPOLICYVAL#yes#18 -->
    document.write("<A HREF='client/userRenewalPTS.htm'>");
<!-- VSSKENDPOLICYVAL#yes#18 -->


// information for userRenewalInstallPTS.htm
<!-- VSSKBEGINPOLICYVAL#yes#19#1.0.0.1 -->
<FORM NAME="InstallForm" ACTION="%%ptsServerUrl%%/vspts/pts" ENCTYPE=x-www-form-encoded METHOD="POST">
<input type="hidden" name="Action" value="$$RenewInstallAction$$">
<INPUT type="hidden" name="AppContextName"  value="%%Apps/PTAv2::ptaAppName%%">
<INPUT type="hidden" name="RoamingClientInfo" value="%%Apps/PTAv2/Roaming::clientInfo%%">
<INPUT type="hidden" name="RoamingClientInfoSig" value="%%Apps/PTAv2/Roaming::clientInfoSig%%">
<INPUT type="hidden" name="CertProperties" value="NewCertProperties; OldCertProperties">
<INPUT type="hidden" name="OldCertProperties" value="Separator=|SerialNumber=$$orig_cert_serial$$| IssuerDN=%%::ptaIssuerDN%%| Renewed=1">
<INPUT type="hidden" name="NewCertProperties" value="Separator=|SerialNumber=$$cert_serial$$| IssuerDN=%%::ptaIssuerDN%%| FrndlyName=%%Apps/PTAv2::ptaCertFriendlyName%%| LogoUrl=%%Apps/PTAv2::ptaCertLogoURL%%| TextureUrl=%%Apps/PTAv2::ptaCertTextureURL%%">
<INPUT TYPE="hidden" NAME="CheckForRenew" VALUE="false">
<!-- VSSKBEGIN Global/Mode#111 -->
<!-- VSSKEND Global/Mode#111 -->

<!-- VSSKBEGIN Apps/PersonalTrustService#28 -->
<!-- VSSKEND Apps/PersonalTrustService#28 -->

<!-- VSSKENDPOLICYVAL#yes#19 -->

// Info for userRenewalPTS.htm
<!-- VSSKBEGINPOLICYVAL#yes#20 -->
<INPUT type="hidden" name="Action" value="RenewCertificate">
<INPUT TYPE="hidden" NAME="OldActionList" VALUE="">
<INPUT TYPE="hidden" NAME="CheckForRenew" VALUE="false">
<input type="hidden" name="SignChallengeCertDisplayRequired" value="true">
<INPUT TYPE="hidden" NAME="RenewCertificate.WizardTitle" VALUE="%%Apps/PTAv2::ptaRenewWizardTitle%%">
<INPUT TYPE="hidden" NAME="RenewCertificate.OpenProfile.Title" VALUE="%%Apps/PTAv2::ptaRenewChooseTitle%%">
<INPUT TYPE="hidden" NAME="RenewCertificate.OpenProfile.Text" VALUE="%%Apps/PTAv2::ptaRenewChooseText%%">
<INPUT TYPE="hidden" NAME="RenewCertificate.OpenProfile.HelpUrl" VALUE="">
<INPUT TYPE="hidden" NAME="RenewCertificate.SelectID.Title" VALUE="%%Apps/PTAv2::ptaRenewTitle%%">
<INPUT TYPE="hidden" NAME="RenewCertificate.SelectID.Text" VALUE="%%Apps/PTAv2::ptaRenewText%%">
<INPUT TYPE="hidden" NAME="RenewCertificate.SelectID.HelpUrl" VALUE="">
<INPUT TYPE="hidden" NAME="RenewCertificate.PostMessage" VALUE="Please wait while we submit your renewal information to the web-site...">

<!-- VSSKBEGIN Apps/PersonalTrustService#28 -->
<!-- VSSKEND Apps/PersonalTrustService#28 -->

<!-- VSSKENDPOLICYVAL#yes#20 -->


// Commoon renual parameters used in userRenewal, login and signTransaction pages.
<!-- VSSKBEGINPOLICYVAL#yes#21 -->
   <!-- VSSKBEGIN Global/Mode#118 -->
   <!-- VSSKEND Global/Mode#118 -->
<input type="hidden" name="SignHashAlg" value="MD5">
<INPUT TYPE="hidden" NAME="Renew_form_file" VALUE="../fdf/VSApps/client/userRenewalPTS.fdf">
<INPUT TYPE="hidden" NAME="Renew_getMethod" VALUE="pkcs7">
<INPUT TYPE="hidden" NAME="Renew_detachedMesg" VALUE="Renew Digital ID">
<INPUT TYPE="hidden" NAME="DaysToRenew" VALUE="%%::AbtToExpireWindow%%">
<!-- VSSKENDPOLICYVAL#yes#21 -->

// For login and SignTransaction pages.
<!-- VSSKBEGINPOLICYVAL#yes#22 -->
<INPUT TYPE="hidden" NAME="RenewConfirmation.Title" VALUE="">
<INPUT TYPE="hidden" NAME="RenewConfirmation.HelpUrl" VALUE="">
<INPUT TYPE="hidden" NAME="RenewCertificate.PostMessage" VALUE="Please wait while we submit your renewal information to the web-site...">

<INPUT type="hidden" name="ErrorPage.ReturnTxt" value="Home">
<INPUT type="hidden" name="ErrorPage.ReturnUrl" value="%%Apps/PTAv2::ptaAppHomeUrl%%">
<!-- VSSKENDPOLICYVAL#yes#22 -->

<!-- VSSKBEGINPOLICYVAL#yes#23 -->
<Script Language="JavaScript">
<!--
var HomeURL="%%Apps/PTAv2::ptaAppHomeUrl%%";
//-->
</Script>
<!-- VSSKENDPOLICYVAL#yes#23 -->

<!-- VSSKBEGINPOLICYVAL#yes#24 -->
<SCRIPT LANGUAGE="JavaScript">
ptaloginurl = document.URL;

newUrl =  ptaloginurl.replace(/ptaSmLogin.fcc/, "ptsSmLogin.fcc");
window.location.href=newUrl;
</SCRIPT>
<!-- VSSKENDPOLICYVAL#yes#24 -->

<!-- VSSKBEGINPOLICYVAL#yes#25 -->
    document.write("<A HREF='client/userRenewalEncPTS.htm'>");
<!-- VSSKENDPOLICYVAL#yes#25 -->

<!-- VSSKBEGINPOLICYVAL#yes#26 -->
    document.write("<A HREF='client/userRenewalSignPTS.htm'>");
<!-- VSSKENDPOLICYVAL#yes#26 -->

// For Transaction Signing same as fragment 2 with onsubmit tag.
<!-- VSSKBEGINPOLICYVAL#yes#27 -->
<FORM name=theform action="%%ptsServerUrl%%/vspts/pts" onsubmit="pressedSignItNew()" method=post>
<INPUT type="hidden" name="AppContextName"  value="%%Apps/PTAv2::ptaAppName%%">
<INPUT type="hidden" name="RoamingClientInfo" value="%%Apps/PTAv2/Roaming::clientInfo%%">
<INPUT type="hidden" name="RoamingClientInfoSig" value="%%Apps/PTAv2/Roaming::clientInfoSig%%">
<INPUT type="hidden" name="SrchCritIssuerDN" value="%%::ptaIssuerDN%%">

<!-- VSSKBEGIN Apps/PersonalTrustService#28 -->
<!-- VSSKEND Apps/PersonalTrustService#28 -->

<!-- VSSKENDPOLICYVAL#yes#27 -->

// Name value pair for internationalization - character encoding and locale.
<!-- VSSKBEGINPOLICYVAL#yes#28 -->
<INPUT type="hidden" name="CharacterEncoding"  value="%%Enrollment/CharEncoding::charEncoding%%">
<INPUT type="hidden" name="CharacterSet" value="%%Enrollment/CharEncoding::charSet%%">
<!-- VSSKENDPOLICYVAL#yes#28 -->
