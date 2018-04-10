<!-- VSSKBEGINPOLICYVAL#Java#1 -->

<SCRIPT language=javascript>
//functions to handle error coded returned by javapta
function handleError(error) {
  //-- VSSKBEGIN Global/Mode#121 --
  //-- VSSKEND Global/Mode#121 --
      enrollUrl = hostName + "VSApps/client/userEnrollJava.htm"
      ERR_USER_CANCEL_OP = 24583
      ERR_NO_DIGITAL_ID_FOUND =	28687
      ERROR_ACCOUNT_LOCKED_OUT = 16670
      ERR_NO_RENEWABLE_IDS = 28674
      if(error == ERR_USER_CANCEL_OP) {
         alert( "You have cancelled the operation. Please select appropriate action to continue.")
      } else if (error == ERR_NO_DIGITAL_ID_FOUND) {
            toEnroll = confirm("You do not have a valid Digital ID. Would you like to enroll for a Digital ID at this time?")
            if( toEnroll == true) {
			    window.location.href= enrollUrl
            }
      } else if (error == ERROR_ACCOUNT_LOCKED_OUT) {
            alert("You have exceeded the maximum number of login attempts.\n Your profile has been locked. Please try again later.")
      } else if (error == ERR_NO_RENEWABLE_IDS) {
           alert("No Renewable Digital IDs could be found!")
           window.location.href = "../digitalidCenter.htm"
      } else {
              <!--  23 July 2004: Begin Changes -->
              <!-- As we are checking errors in above condition there is no need to give alert for no error. -->
	      //alert("Unknown Error, Code : " + error)
	      <!--  23 July 2004: End Changes -->
      }
}
</SCRIPT>
<!-- VSSKENDPOLICYVAL#Java#1 -->

// for java pta transaction signing
<!-- VSSKBEGINPOLICYVAL#Java#2 -->
<SCRIPT language=javascript>
function pressedSignItNew() {
   setMessage ()
   document.theform.dataToSign.value = Msgg
   appletRef = waitUntilAppletIsReady()
   SetPreferences(document.signTransPrefForm)
   signedmsg = appletRef.signTransaction(Msgg, "true")
   if(signedmsg == "" || signedmsg == null) {
       handleError(appletRef.getLastError())
   }   else if(signedmsg.indexOf("pkcsInformation") == -1){
        document.theform.dataSignature.value =  signedmsg
        <!--  23 July 2004: Begin Changes HTML submit is not needed-->
        <!-- As JPTA architecture is changed from applet dialog box to applet HTML -->
        <!-- there is no need to submit the HTML, applet will forward control to next page -->
	//document.theform.submit()
        <!--  23 July 2004: End Changes -->
   }  else {
      <!--  23 July 2004: Begin Changes Removed the function call-->
        <!-- As JPTA architecture is changed from applet dialog box to applet HTML -->
        <!-- there is no need to submit the HTML, applet will forward control to next page -->
      //postRenewal(signedmsg);
      <!--  23 July 2004: End Changes -->
   }
}
</SCRIPT>
<!-- VSSKENDPOLICYVAL#Java#2 -->

// section used in digital ID center to use javapta for enrollment
<!-- VSSKBEGINPOLICYVAL#Java#3 -->
<TR>
	<TD WIDTH=50 ALIGN=left VALIGN=top>
        <A HREF="client/userEnrollJava.htm">
	  <IMG SRC="graphics/action_checkyellow.gif" WIDTH="40" HEIGHT="40" BORDER="0"></A>
	</TD>
	<TD WIDTH=538 ALIGN=left VALIGN=top>
        <A HREF="client/userEnrollJava.htm">
   	  <FONT FACE="verdana, arial, helvetica" SIZE=5><B>ENROLL</B></FONT></A><BR>
	  <FONT FACE="arial, helvetica" SIZE=2>Choose this option to enroll for a Digital ID.</FONT>
	   <P>
	</TD>
</TR>
<!-- VSSKENDPOLICYVAL#Java#3 -->

// section used in digital ID center to use javapta to pickup cert
<!-- VSSKBEGINPOLICYVAL#Java#4 -->
<TR>
	<TD WIDTH=50 ALIGN=left VALIGN=top>
        <A HREF="client/javaPtapickup.htm">
  	  <IMG SRC="graphics/action_arrowyellow.gif" WIDTH=40 HEIGHT=40 BORDER=0 ALT=""></A>
	</TD>
	<TD WIDTH=538 ALIGN=left VALIGN=top>
        <A HREF="client/javaPtapickup.htm">
	  <FONT FACE="verdana, arial, helvetica" SIZE=5><B>PICK-UP ID</B></FONT></A><BR>
	  <FONT FACE="arial, helvetica" SIZE=2>Choose this option if you have enrolled for a Digital ID but have not picked it up.</FONT>
	  <P>
	</TD>
</TR>
<!-- VSSKENDPOLICYVAL#Java#4 -->

//section used in digital ID center for link to javapta preference page
<!-- VSSKBEGINPOLICYVAL#Java#5 -->
<TR>
	<TD WIDTH=50 ALIGN=left VALIGN=top>  <A HREF=ptaprefCenter.htm>
	<IMG SRC="graphics/action_arrowyellow.gif" border=0 WIDTH=40 HEIGHT=40 ALIGN=LEFT></A>
	</TD>
	<TD WIDTH=538 ALIGN=left VALIGN=top>   <A HREF=ptaprefCenter.htm>
	<FONT FACE="verdana, arial, helvetica" SIZE=4><B>PTA PREFERENCE MANAGEMENT</B></FONT></A><BR>
	<FONT FACE="arial, helvetica" SIZE=2>Choose this option to change the preferences for your VeriSign Profile.
	</FONT>
	<P>
	</TD>
</TR>
<!-- end change password -->
<!-- VSSKENDPOLICYVAL#Java#5 -->

// change password section used in javapta preference page
<!-- VSSKBEGINPOLICYVAL#Java#6 -->
<TABLE WIDTH=588 BGCOLOR="#ccffff" CELLPADDING=2 CELLSPACING=0 BORDER=0>
<TR>
	<TD WIDTH=50 ALIGN=left VALIGN=top>
      <P>
       <A HREF='client/changePasswdJava.htm'>
       <IMG align=left border=0 height=40 src="graphics/action_arrowyellow.gif" width=40></A> </P>
      <P>&nbsp;</P>
      <P>&nbsp;</P>
	</TD>
	<TD WIDTH=538 ALIGN=left VALIGN=top>
        <A HREF='client/changePasswdJava.htm'>
	<FONT FACE="verdana, arial, helvetica" SIZE=4><B>Change Password</B></FONT></A><BR>
	<FONT FACE="arial, helvetica" SIZE=2>Choose this option to change the password for your profile.
	</FONT>
	<!--  23 July 2004: Begin Changes Added for reset password functionality -->
	<!-- VSSKBEGIN Apps/PTAv2/Roaming#11 -->
	<!-- VSSKEND Apps/PTAv2/Roaming#11 -->
	<!--  23 July 2004: End Changes -->
	<P></P>
	</TD>
</TR>
<p>
<!-- VSSKENDPOLICYVAL#Java#6 -->

//section used to refer to java pta renewal page
<!-- VSSKBEGINPOLICYVAL#Java#7 -->
document.write("<A HREF='client/userRenewalJava.htm'>")
<!-- VSSKENDPOLICYVAL#Java#7 -->

// function for calling javapta user enrollment function
<!-- VSSKBEGINPOLICYVAL#Java#8 -->
<SCRIPT language=javascript>
function DoKeyGen() {
   appletRef= waitUntilAppletIsReady()
   var firstNameStr = document.proform.mail_firstName.value;
   if ( ("%%Enrollment/FirstName::policyValue%%" == "exists") && ("%%Enrollment/FirstName::policyValue%%" == "exists") ) {
     document.enrollPrefForm.UserName.value = firstNameStr.substring(0,1) + document.proform.mail_lastName.value;
    }
   SetPreferences(document.enrollPrefForm)
   <!--  23 July 2004: Begin Changes function called to set variables of proform in preferences -->
   SetPreferences(document.proform)
   <!--  23 July 2004: End Changes -->
   pkcs10 = appletRef.userEnroll()
   if(pkcs10 == "" || pkcs10 == null) {
	<!--  23 July 2004: Begin Changes -->
	<!-- Removed the function call as after calling userEnroll method of applet, control goes to another page -->
       //handleError(appletRef.getLastError())
       <!--  23 July 2004: End Changes-->
   } else {
        document.proform.public_key.value =  pkcs10
        if(navigator.appName != "Microsoft Internet Explorer"){
            document.proform.enroll_track.value = "Netscape"
        }
	<!--  23 July 2004: Begin Changes Removed HTML Page submit-->
        <!-- As JPTA architecture is changed from applet dialog box to applet HTML -->
        <!-- there is no need to submit the HTML, applet will forward control to next page -->
	//document.proform.submit()
        <!--  23 July 2004: End Changes-->
   }
}
</SCRIPT>
<!-- VSSKENDPOLICYVAL#Java#8 -->

// function calls javapta install cert function
<!-- VSSKBEGINPOLICYVAL#Java#9 -->
<SCRIPT language=javascript>
function installCert()  {
   certProp =document.InstallForm.NewCertProperties.value
   CertChain=document.InstallForm.Base64CertInstallList.value
   appletRef = waitUntilAppletIsReady()
   SetPreferences(document.InstallIDPrefForm)
   res = appletRef.installCertificate(CertChain,certProp)
   if(res != 1) {
       handleError(appletRef.getLastError())
   } else {
      //maybe we should prompt user install cert ok?
   }
}
</SCRIPT>
<!-- VSSKENDPOLICYVAL#Java#9 -->

// data form holding new cert info
<!-- VSSKBEGINPOLICYVAL#Java#10 -->
<INPUT type="hidden" name="Base64CertInstallList" value="$$certOrCRL$$">
<INPUT type="hidden" name="NewCertProperties" value="Separator=|SerialNumber=$$cert_serial$$| IssuerDN=%%::ptaIssuerDN%%| FrndlyName=%%Apps/PTAv2::ptaCertFriendlyName%%| LogoUrl=%%Apps/PTAv2::ptaCertLogoURL%%| TextureUrl=%%Apps/PTAv2::ptaCertTextureURL%%">
<!-- VSSKENDPOLICYVAL#Java#10 -->

// calling install cert function
<!-- VSSKBEGINPOLICYVAL#Java#11 -->
<SCRIPT Language="JavaScript">
    window.setTimeout("installCert()",500);
</SCRIPT>
<!-- VSSKENDPOLICYVAL#Java#11 -->

// function calls javapta install renewal cert function
<!-- VSSKBEGINPOLICYVAL#Java#12 -->
<SCRIPT language=javascript>
function installCert()  {
   certProp =document.InstallForm.NewCertProperties.value
   CertChain=document.InstallForm.Base64CertInstallList.value
   oldCertProp=document.InstallForm.OldCertProperties.value
   appletRef = waitUntilAppletIsReady()
   SetPreferences(document.InstallIDPrefForm)
   res = appletRef.installRenewalCertificate(CertChain,certProp,oldCertProp)
   if(res != 1) {
       handleError(appletRef.getLastError())
   } else {
      //maybe we should prompt user install cert ok?
   }
}
</SCRIPT>
<!-- VSSKENDPOLICYVAL#Java#12 -->

// entry for install renewal cert
<!-- VSSKBEGINPOLICYVAL#Java#13 -->
<INPUT type="hidden" name="OldCertProperties" value="Separator=|SerialNumber=$$orig_cert_serial$$| IssuerDN=%%::ptaIssuerDN%%| Renewed=1">
<!-- VSSKENDPOLICYVAL#Java#13 -->

// function for change password
<!-- VSSKBEGINPOLICYVAL#Java#14 -->
<SCRIPT language=javascript>
function changePassword()  {
   appletRef = waitUntilAppletIsReady()
   SetPreferences(document.changepwdPrefForm)
   res = appletRef.changePassword()
   if(res != 1) {
       handleError(appletRef.getLastError())
   } else {
      alert("your password has been successfully changed");
   }
}
</SCRIPT>
<!-- VSSKENDPOLICYVAL#Java#14 -->

//function to ensure applet is ready
<!-- VSSKBEGINPOLICYVAL#Java#15 -->
<SCRIPT language=javascript>
function waitUntilAppletIsReady() {
    intervalHandle = setInterval("checkUntilAppletIsReady()",250);
    clearInterval(intervalHandle);
//<!-- VSSKBEGIN Apps/PTAv2/GSWAClientType#17 -->
//<!-- VSSKEND Apps/PTAv2/GSWAClientType#17 -->
    return appletRef;
}

function checkUntilAppletIsReady() {
//<!-- VSSKBEGIN Apps/PTAv2/GSWAClientType#17 -->
//<!-- VSSKEND Apps/PTAv2/GSWAClientType#17 -->
	try{
    if (appletRef != null && appletRef.isActive()) {
		ready = true;
    } else {
		ready = false;
    }
	} catch (ex){
		//ex.printStackTrace();
		ready = false;
	}
	return ready;
}
</SCRIPT>
<!-- VSSKENDPOLICYVAL#Java#15 -->

//preferences for enrollment pages
<!-- VSSKBEGINPOLICYVAL#Java#16 -->
<INPUT TYPE="hidden" NAME="IDS_CREATEDLG_TITLE" VALUE="%%Apps/PTAv2::ptaNewProfileTitle%%">
<INPUT TYPE="hidden" NAME="IDS_NEWPASSWD_TITLE" VALUE="%%Apps/PTAv2::ptaNewProfileText%%">
<INPUT TYPE="hidden" NAME="UserName" VALUE="">
<!-- VSSKENDPOLICYVAL#Java#16 -->

//fragment to differ different browser
<!-- VSSKBEGINPOLICYVAL#Java#17 -->

  <!--  23 July 2004: Begin Changes -->
   <!-- Action is taken depending on browswer and OS -->
   if(_ie)
   {
     appletRef = document.PtaApplet;
   }
   else
   {
     appletRef = document.embeds[0];
   }
  <!--  23 July 2004: End Changes -->

<!-- VSSKENDPOLICYVAL#Java#17 -->

<!-- VSSKBEGINPOLICYVAL#Java#21#1.0.0.1 -->
<HEAD>
<TITLE>Logout</TITLE>
<META HTTP-EQUIV="Pragma" CONTENT="no-cache">
<META HTTP-EQUIV="Expires" CONTENT="-1">
<!-- VSSKBEGIN Enrollment/CharEncoding#3 -->
<!-- VSSKEND Enrollment/CharEncoding#3 -->

<!-- VSSKBEGIN Global/Mode#123 -->
<!-- VSSKEND Global/Mode#123 -->

</HEAD>
<!-- VSSKBEGIN Apps/PTAv2/GSWAClientType#15 -->
<!-- VSSKEND Apps/PTAv2/GSWAClientType#15 -->
<script language="JavaScript">
function DoLogout() {
   appletRef = waitUntilAppletIsReady();
   appletRef.logout();
   GoToHome();
}

function GoToHome()
{
    //-- VSSKBEGIN Apps/PTAv2#4 --
    //-- VSSKEND Apps/PTAv2#4 --
}

</script>


<BODY BGCOLOR="#FFFFFF" LINK="#333333" TEXT="#333333" VLINK="#333333" ALINK="#CCCCCC" onLoad="DoLogout();">
<FONT SIZE="5" COLOR="#0033CC" FACE="arial,helvetica,verdana,sans-serif"><B>Logging Out...</B></FONT>
<!-- VSSKBEGIN Enrollment/CertStore#36 -->
<!-- VSSKEND Enrollment/CertStore#36 -->
</BODY>
<!-- VSSKENDPOLICYVAL#Java#21 -->

<!-- VSSKBEGINPOLICYVAL#Java#22 -->
<SCRIPT LANGUAGE=JavaScript>
function SetPreferences(form)
{
   appletRef = waitUntilAppletIsReady();
   for(var i = 0; i < form.elements.length; i++ )
   {
     try {
       appletRef.setPreferences(form.elements[i].name,form.elements[i].value);
     } catch (e) {
       continue;
     }
   }

}
</Script>
<!-- VSSKENDPOLICYVAL#Java#22 -->

<!-- VSSKBEGINPOLICYVAL#Java#23 -->
<FORM NAME=InitData >
</FORM>
<!-- VSSKENDPOLICYVAL#Java#23 -->


<!-- VSSKBEGINPOLICYVAL#Java#24 -->
<INPUT type="hidden" name="AppContextName"  value="%%Apps/PTAv2::ptaAppName%%">
<INPUT type="hidden" name="RoamingClientInfo" value="%%Apps/PTAv2/Roaming::clientInfo%%">
<INPUT type="hidden" name="RoamingClientInfoSig" value="%%Apps/PTAv2/Roaming::clientInfoSig%%">
<INPUT type="hidden" name="SrchCritIssuerDN" value="%%::ptaIssuerDN%%">
<INPUT TYPE="hidden" NAME="InstallCertificate.OpenProfile.HelpUrl" VALUE="">
<INPUT TYPE="hidden" NAME="Challenge.OpenProfile.HelpUrl" VALUE="">
<INPUT TYPE="hidden" NAME="SignChallenge.SelectID.HelpUrl" VALUE="">
<INPUT TYPE="hidden" NAME="SignTransaction.OpenProfile.HelpUrl" VALUE="">
<INPUT TYPE="hidden" NAME="SignTransaction.SelectID.HelpUrl" VALUE="">
<INPUT TYPE="hidden" NAME="SignTransaction.RvwMsg.HelpUrl" VALUE="">
<INPUT TYPE="hidden" NAME="RequestCertificate.NewUser.HelpUrl" VALUE="">
<INPUT TYPE="hidden" NAME="RequestCertificate.OpenProfile.HelpUrl" VALUE="">
<INPUT TYPE="hidden" NAME="ChangePassword.OpenProfile.HelpUrl" VALUE="">
<INPUT TYPE="hidden" NAME="ChangePassword.NewPassword.HelpUrl" VALUE="">
<INPUT TYPE="hidden" NAME="RenewCertificate.OpenProfile.HelpUrl" VALUE="">
<INPUT TYPE="hidden" NAME="RenewCertificate.SelectID.HelpUrl" VALUE="">
<INPUT TYPE="hidden" NAME="RenewConfirmation.HelpUrl" VALUE="">
<INPUT TYPE="hidden" name="AppHeaderLogoURL" value="%%Apps/PTAv2::ptaAppLogoUrl%%">
<INPUT TYPE="hidden" NAME="DaysToRenew" VALUE="%%::AbtToExpireWindow%%">
<input type="hidden" name="IDS_OPENPROF_TITLE" VALUE="%%Apps/PTAv2::ptaLoginWizardTitle%%" >
<input type="hidden" name="IDS_OPENPROF_TEXT" value="%%Apps/PTAv2::ptaLoginChooseTitle%%" >
<INPUT TYPE="hidden" NAME="IDS_LGNDLG_TITLE" VALUE="%%Apps/PTAv2::ptaLoginTitle%%">
<INPUT TYPE="hidden" NAME="IDS_SELID_TITLE" VALUE="%%Apps/PTAv2::ptaSignWizardTitle%%">
<INPUT TYPE="hidden" NAME="IDS_SELID_TEXT" VALUE="%%Apps/PTAv2::ptaLoginChooseTitle%%">
<INPUT TYPE="hidden" NAME="ProfileTimeout" value="%%Apps/PTAv2::ptaPasswordTimeout%%">
<INPUT TYPE="hidden" NAME="PasswordLockOutTries" value="%%Apps/PTAv2::ptaPasswordLockout%%">
<INPUT TYPE="hidden" NAME="ProfileUnlockPeriod" value="%%Apps/PTAv2::ptaPasswordUnlock%%">
<INPUT TYPE="hidden" NAME="KeySize" value="%%Enrollment/KeyLength::policyValue%%">
<!-- Begin: Fix for artf14455-->
<INPUT TYPE="hidden" name="ProtectedURL">
<!-- End: Fix for artf14455-->
<!-- VSSKENDPOLICYVAL#Java#24 -->


// Commoon renual parameters used in userRenewal, login and signTransaction pages.
<!-- VSSKBEGINPOLICYVAL#Java#25 -->
<!-- VSSKBEGIN Global/Mode#118 -->
<!-- VSSKEND Global/Mode#118 -->
<input type="hidden" name="SignHashAlg" value="MD5">
<INPUT TYPE="hidden" NAME="form_file" VALUE="../fdf/VSApps/client/userRenewalJava.fdf">
<INPUT TYPE="hidden" NAME="getMethod" VALUE="pkcs7">
<INPUT TYPE="hidden" NAME="detachedMesg" VALUE="Renew Digital ID">
<INPUT TYPE="hidden" NAME="DaysToRenew" VALUE="%%::AbtToExpireWindow%%">
<!-- VSSKENDPOLICYVAL#Java#25 -->

//Not to be used. use other name value initialization fragments
<!-- VSSKBEGINPOLICYVAL#Java#26 -->
<!-- VSSKENDPOLICYVAL#Java#26 -->

<!-- VSSKBEGINPOLICYVAL#Java#27 -->
login-page-ms="c:/VeriSign/pta/config/jptaLogin.htm"
login-page-ns="c:/VeriSign/pta/config/jptaLogin.htm"
<!-- VSSKENDPOLICYVAL#Java#27 -->

// stuff for the login page
<!-- VSSKBEGINPOLICYVAL#Java#28 -->
<input type="hidden" name="IDS_OPENPROF_TITLE" VALUE="%%Apps/PTAv2::ptaLoginChooseTitle%%" >
<input type="hidden" name="IDS_OPENPROF_TEXT" value="%%Apps/PTAv2::ptaLoginChooseText%%" >
<INPUT TYPE="hidden" NAME="IDS_LGNDLG_TITLE" VALUE="%%Apps/PTAv2::ptaLoginWizardTitle%%">
<INPUT TYPE="hidden" NAME="IDS_SELID_TITLE" VALUE="%%Apps/PTAv2::ptaLoginTitle%%">
<INPUT TYPE="hidden" NAME="IDS_SELID_TEXT" VALUE="%%Apps/PTAv2::ptaLoginText%%">
<!-- VSSKENDPOLICYVAL#Java#28 -->


// For  SignTransaction pages.
<!-- VSSKBEGINPOLICYVAL#Java#29 -->
<input type="hidden" name="IDS_OPENPROF_TITLE" VALUE="%%Apps/PTAv2::ptaLoginChooseTitle%%" >
<input type="hidden" name="IDS_OPENPROF_TEXT" value="%%Apps/PTAv2::ptaLoginChooseText%%" >
<INPUT TYPE="hidden" NAME="IDS_LGNDLG_TITLE" VALUE="%%Apps/PTAv2::ptaSignWizardTitle%%">
<INPUT TYPE="hidden" NAME="IDS_SELID_TITLE" VALUE="%%Apps/PTAv2::ptaSignTitle%%">
<INPUT TYPE="hidden" NAME="IDS_SELID_TEXT" VALUE="%%Apps/PTAv2::ptaSignText%%">
<INPUT TYPE="hidden" NAME="IDS_RVWMSG_TITLE" VALUE="%%Apps/PTAv2::ptaReviewTitle%%">
<INPUT TYPE="hidden" NAME="IDS_RVWMSG_TEXT" VALUE="%%Apps/PTAv2::ptaReviewText%%">
<!-- VSSKENDPOLICYVAL#Java#29 -->

//Figure out Storage Type
<!-- VSSKBEGINPOLICYVAL#Java#30 -->
<SCRIPT language=javascript>

if("%%Apps/PTAv2/Roaming::policyValue%%" == "disabled")
 {document.write("<INPUT TYPE='HIDDEN' NAME='StorageType' VALUE='Local'>")}
else
  {document.write("<INPUT TYPE='HIDDEN' NAME='StorageType' VALUE='Roaming'>")}

  document.write("<INPUT TYPE='HIDDEN' NAME='AppServerURL' VALUE='" + location.href + "'>")
</SCRIPT>
<!-- VSSKENDPOLICYVAL#Java#30 -->

//body of the page which checks if applet is ready
<!-- VSSKBEGINPOLICYVAL#Java#31 -->
<BODY text=#333333 vLink=#333333 aLink=#cccccc link=#333333 bgColor=#ffffff onLoad = appLoaded(); >
<!-- VSSKENDPOLICYVAL#Java#31 -->

<!-- VSSKBEGINPOLICYVAL#Java#32 -->
<!--  23 July 2004: Begin Changes changed the initApplet function-->
<SCRIPT LANGUAGE="JavaScript">
function initApplet()
{
	<!-- Interval is set depending on OS to load applet properly. -->
	 if(_info.indexOf("Linux")> 0)
	 waitHandle = setInterval("waitApplet()",23000);
	 else if(_info.indexOf("Sun")> 0)
	 waitHandle = setInterval("waitApplet()",42000);
	 else
	 waitHandle = setInterval("waitApplet()",2000);
  	 return true;
}
<!-- function sets state to initial state and error to 0 -->
function waitApplet()
{
	<!-- clear the interval set depending on OS -->
 	if(_info.indexOf("Linux")> 0 || _info.indexOf("Sun")> 0)
		clearInterval(waitHandle);
	appletRef = waitUntilAppletIsReady()
 	document.LoginForm.Loginbtn.disabled = false;
     	document.LoginForm.Signupbtn.disabled = false;
     	appletRef.setInitialState()
	handleError(appletRef.getLastError())
	appletRef.setLastError(0)
     	return true;
}
</SCRIPT>
<!--  23 July 2004: End Changes-->

<!-- VSSKENDPOLICYVAL#Java#32 -->

<!-- VSSKBEGINPOLICYVAL#Java#33 -->
no-cache-pages="0"
no-cache-login="1"
<!-- VSSKENDPOLICYVAL#Java#33 -->

<!-- VSSKBEGINPOLICYVAL#Java#34 -->
<!--  23 July 2004: Begin Changes changed the waitUntilRenewClick function-->

function waitUntilRenewClick() {
	
	<!-- Interval is set if OS is linux or solaris to load applet properly. -->
	 if(_info.indexOf("Linux")> 0)
	 waitHandle = setInterval("renewclick()",23000);
	 else if(_info.indexOf("Sun")> 0)
	 waitHandle = setInterval("renewclick()",42000);
	 else
	 {
	     waitUntilAppletIsReady()
	     renewclick();
	 }
}
function renewclick(){
      fromProtectedResource = 0;
      <!-- clear the interval set depending on OS -->
      if(_info.indexOf("Linux")> 0 || _info.indexOf("Sun")> 0)
      clearInterval(waitHandle);

      if (document.theform.public_key.value.indexOf("public_key") != -1) {
           SetPreferences(document.InitData);
           appletRef = waitUntilAppletIsReady();
           var stateVal = appletRef.getState();
           if(stateVal == "Initial") {
             appletRef.RenewCert();
           } else {
             renewalData = appletRef.Renewal();
             if (renewalData == "" || renewalData == null) {
               handleError(appletRef.getLastError())
               window.location.href = "../digitalidCenter.htm"
             } else {
               postRenewal()
             }
           }


      } else {
         fromProtectedResource = 1;

          // document.theform.Renewbtn.disabled = false;
          // document.theform.Cancelbtn.disabled = false;
          postRenewal()
      }
}

<!--  23 July 2004: End Changes -->
function postRenewal(){
      if (!fromProtectedResource){

        var publicKeyValue = getValue(renewalData, "encodedp10");
        var pkcsInfoValue = getValue(renewalData, "pkcsInformation");
        var orig_cert_serial_Value = getValue(renewalData, "orig_cert_serial");
        var orig_ser_num_Value = getValue(renewalData, "orig_cert_issuerdn");

        document.theform.public_key.value = publicKeyValue;
        document.theform.pkcsInformation.value = pkcsInfoValue;
        document.theform.orig_cert_serial.value = orig_cert_serial_Value;
        document.theform.orig_cert_issuerdn.value = orig_ser_num_Value;
      }

       document.theform.submit() ;
}

function getValue(renewalData, name) {

      var start_name = renewalData.indexOf(name);
      var startValue = start_name + name.length + 9; <!-- quote + " value=" + quote-->
      var tmp;
      if(navigator.appName == "Netscape"){ 
        tmp = renewalData.substring(startValue, renewalData.length());
      } else
      {
        tmp = renewalData.substring(startValue, renewalData.length);
      }
      var endValue = tmp.indexOf(">")
      var value = tmp.substring(0,endValue-2);    //to account for close quotes and space

      return value;

}

function checkIfAppletIsReady() {
//<!-- VSSKBEGIN Apps/PTAv2/GSWAClientType#17 -->
//<!-- VSSKEND Apps/PTAv2/GSWAClientType#17 -->
    if (appletRef != null && appletRef.isActive()) {
       clearInterval(intervalHandle);
       renewclick();
       return true;
    } else {
       return false;
    }
}


<!-- VSSKENDPOLICYVAL#Java#34 -->

<!-- VSSKBEGINPOLICYVAL#Java#35 -->
<!-- VSSKENDPOLICYVAL#Java#35 -->

<!-- VSSKBEGINPOLICYVAL#Java#36 -->
<INPUT type="hidden" name="Action" value="RenewCertificate">
<INPUT type="hidden" name="CheckForRenew" value="false">
<INPUT type="hidden" name="OldActionList" value="">
<!-- VSSKENDPOLICYVAL#Java#36 -->

//for renewal
<!-- VSSKBEGINPOLICYVAL#Java#37 -->
<input type="hidden" name="IDS_OPENPROF_TITLE" VALUE="%%Apps/PTAv2::ptaRenewChooseTitle%%" >
<input type="hidden" name="IDS_OPENPROF_TEXT" value="%%Apps/PTAv2::ptaRenewChooseText%%" >
<INPUT TYPE="hidden" NAME="IDS_LGNDLG_TITLE" VALUE="%%Apps/PTAv2::ptaRenewWizardTitle%%">
<INPUT TYPE="hidden" NAME="IDS_SELID_TITLE" VALUE="%%Apps/PTAv2::ptaRenewTitle%%">
<INPUT TYPE="hidden" NAME="IDS_SELID_TEXT" VALUE="%%Apps/PTAv2::ptaRenewText%%">
<!-- VSSKENDPOLICYVAL#Java#37 -->

// include cert store info in checkmail
<!-- VSSKBEGINPOLICYVAL#Java#38 -->
</HEAD>
<BODY BGCOLOR="ffffff" LINK="cc0000" VLINK="666666">
<!-- VSSKENDPOLICYVAL#Java#38 -->

//sign challenge functions
<!-- VSSKBEGINPOLICYVAL#Java#39 -->

<SCRIPT LANGUAGE="JavaScript">
function SignIt() {
   if (digestAlg == "MD5")
         document.InitData.SignHashAlg.value="MD5";
    else
         document.InitData.SignHashAlg.value="SHA";
   SetPreferences(document.InitData);
   appletRef = waitUntilAppletIsReady();
   signature = appletRef.signChallenge(toSign);
   if(signature == "" || signature == null) {
 	  handleError(appletRef.getLastError())
   }
    else if(signature.indexOf("pkcsInformation") == -1){
      postChallenge(signature);
   }
   else {
      postRenewal(signature);
   }
}

function postChallenge(signature) {
   document.LoginForm.dataToSign.value = toSign;
   document.LoginForm.dataSignature.value = signature;
   document.LoginForm.submit();
}

function SignUpJava()
  {
    var EnrollUrl;
    var EnrollPage = "userEnrollJava.htm";

    EnrollUrl = hostName + "/VSApps/client/" + EnrollPage;
    self.location = EnrollUrl;
  }

onError = errHandler;
  // Without he parentheses, because we don't want IE
  // to do this. Like this, only NS does.

function appLoaded() {
     waitUntilAppletIsReady()
}

function errHandler() {
 alert("NS: Applet could not be loaded");
 consume();
 // stops further processing of the error
 }

</SCRIPT>
<!-- VSSKENDPOLICYVAL#Java#39 -->

// for break to renew
<!-- VSSKBEGINPOLICYVAL#Java#40 -->
<SCRIPT LANGUAGE="JavaScript">
function postRenewal(signature) {
    var publicKeyValue = getValue(signature, "encodedp10");
    var pkcsInfoValue = getValue(signature, "pkcsInformation");
    var orig_cert_serial_Value = getValue(signature, "orig_cert_serial");
    var orig_ser_num_Value = getValue(signature, "orig_cert_issuerdn");
    document.RenewalForm.public_key.value = publicKeyValue;
    document.RenewalForm.pkcsInformation.value = pkcsInfoValue;
    document.RenewalForm.orig_cert_serial.value = orig_cert_serial_Value;
    document.RenewalForm.orig_cert_issuerdn.value = orig_ser_num_Value;
    document.RenewalForm.submit() ;
}
function getValue(signature, name){
    var start_name = signature.indexOf(name);
    var startValue = start_name + name.length + 9; // quote + " value=" + quote
    var tmp = signature.substring(startValue, signature.length);
    var endValue = tmp.indexOf(">");
    var value = tmp.substring(0,endValue-2); //to account for close quotes and space
    return value;

}

</SCRIPT>
<!-- VSSKENDPOLICYVAL#Java#40 -->

//break to renewalform
<!-- VSSKBEGINPOLICYVAL#Java#41 -->
<!-- VSSKBEGIN Global/Mode#28 -->
<!-- VSSKEND Global/Mode#28 -->
<INPUT TYPE=hidden NAME=orig_cert_serial>
<INPUT TYPE=hidden NAME=orig_cert_issuerdn>
<INPUT TYPE=hidden NAME=pkcsInformation>
<INPUT TYPE=hidden NAME=public_key>
<INPUT TYPE=hidden NAME=detachedMesg VALUE="Renew Digital ID">
<INPUT TYPE=hidden NAME=VHTML_FILE VALUE="../htmldocs/VSApps/client/userRenewalJava.htm">
</FORM>
<!-- VSSKENDPOLICYVAL#Java#41 -->

//password quality
<!-- VSSKBEGINPOLICYVAL#Java#42 -->
<INPUT TYPE="hidden" NAME="RequiredPasswordQuality" value="%%Apps/PTAv2::ptaPasswordQuality%%">
<INPUT TYPE="hidden" NAME="PasswordLenDefMin" value="%%Apps/PTAv2::ptaPasswordLength%%">
<!-- VSSKENDPOLICYVAL#Java#42 -->

<!-- VSSKBEGINPOLICYVAL#Java#43 -->
<SCRIPT language=javascript>
<!--  23 July 2004: Begin Changes Added the reset password function for JPTA-->
function resetPassword()  {
   appletRef = waitUntilAppletIsReady()
   SetPreferences(document.resetpwdPrefForm)
   res = appletRef.resetPassword()
}
</SCRIPT>
<!--  23 July 2004: End Changes Added the reset password function for JPTA-->
<!-- VSSKENDPOLICYVAL#Java#43 -->

<!-- VSSKBEGINPOLICYVAL#Java#44 -->
<!--  23 July 2004: Begin Changes Added the  function for JPTA-->
<SCRIPT language=javascript>
//functions to handle error coded returned by javapta
// this is used to show alert when password is reset.
function handleError() {
  //-- VSSKBEGIN Global/Mode#121 --
  //-- VSSKEND Global/Mode#121 --
      
      if(_info.indexOf("Linux")> 0 || _info.indexOf("Sun")> 0)
      clearInterval(waitHandle);
      
      appletRef = waitUntilAppletIsReady()
      error = appletRef.getLastError()
      enrollUrl = hostName + "VSApps/client/userEnrollJava.htm"
      ERR_USER_CANCEL_OP = 24583
      ERR_NO_DIGITAL_ID_FOUND =	28687
      ERROR_ACCOUNT_LOCKED_OUT = 16670
      ERR_NO_RENEWABLE_IDS = 28674
      ERR_RESET_PWD = 16924
      if(error == ERR_USER_CANCEL_OP) {
         alert( "You have cancelled the operation. Please select appropriate action to continue.")
      } else if (error == ERR_NO_DIGITAL_ID_FOUND) {
            toEnroll = confirm("You do not have a valid Digital ID. Would you like to enroll for a Digital ID at this time?")
            if( toEnroll == true) {
			    window.location.href= enrollUrl
            }
      } else if (error == ERROR_ACCOUNT_LOCKED_OUT) {
            alert("You have exceeded the maximum number of login attempts.\n Your profile has been locked. Please try again later.")
      } else if (error == ERR_NO_RENEWABLE_IDS) {
           alert("No Renewable Digital IDs could be found!")
           window.location.href = "../digitalidCenter.htm"
      } 
      else if (error == ERR_RESET_PWD) {
            alert("You have exceeded the maximum number of login attempts.\n Your profile has been locked. Please contact the administrator.")
      }
      else if (appletRef.getKey("PASSWORD_RESET") == "true"){
	   alert("your password has been successfully reset");
	   appletRef.setPreferences("PASSWORD_RESET","false");      
      }
}
</SCRIPT>
<!--  23 July 2004: End Changes -->
<!-- VSSKENDPOLICYVAL#Java#44 -->

<!-- VSSKBEGINPOLICYVAL#Java#45 -->
<!--  23 July 2004: Begin Changes Added the  function for JPTA-->
<SCRIPT language=javascript>
//functions to handle error coded returned by javapta
// this is used to show alert when password is changed.
function handleError() {
  //-- VSSKBEGIN Global/Mode#121 --
  //-- VSSKEND Global/Mode#121 --
      appletRef = waitUntilAppletIsReady()
      error = appletRef.getLastError()
      enrollUrl = hostName + "VSApps/client/userEnrollJava.htm"
      ERR_USER_CANCEL_OP = 24583
      ERR_NO_DIGITAL_ID_FOUND =	28687
      ERROR_ACCOUNT_LOCKED_OUT = 16670
      ERR_NO_RENEWABLE_IDS = 28674
      ERR_CHANGE_PWD = 16924
      if(error == ERR_USER_CANCEL_OP) {
         alert( "You have cancelled the operation. Please select appropriate action to continue.")
      } else if (error == ERR_NO_DIGITAL_ID_FOUND) {
            toEnroll = confirm("You do not have a valid Digital ID. Would you like to enroll for a Digital ID at this time?")
            if( toEnroll == true) {
			    window.location.href= enrollUrl
            }
      } else if (error == ERROR_ACCOUNT_LOCKED_OUT) {
            alert("You have exceeded the maximum number of login attempts.\n Your profile has been locked. Please try again later.")
      } else if (error == ERR_NO_RENEWABLE_IDS) {
           alert("No Renewable Digital IDs could be found!")
           window.location.href = "../digitalidCenter.htm"
      } else if (error == ERR_CHANGE_PWD) {
            alert("You have exceeded the maximum number of login attempts.\n Your profile has been locked. Please contact the administrator.")
      }
      else if (appletRef.getKey("PASSWORD_CHANGED") == "true"){
	   alert("your password has been successfully changed");
	   appletRef.setPreferences("PASSWORD_CHANGED","false");      
      }
}
</SCRIPT>
<!--  23 July 2004: End Changes -->
<!-- VSSKENDPOLICYVAL#Java#45 -->


<!-- VSSKBEGINPOLICYVAL#Java#46 -->
<TD WIDTH=120 ALIGN=center><IMG SRC="%%Apps/PTAv2::ptaAppLogoUrl%%" ALT=""></TD>
<!-- VSSKENDPOLICYVAL#Java#46 -->

<!-- VSSKBEGINPOLICYVAL#Java#47 -->
<!--  23 July 2004: Begin Changes -->
<!-- clear the interval depending on browser and OS. This is used in userEnrollJava.htm -->
function waitApplet()
{
	if(_info.indexOf("Linux")> 0 || _info.indexOf("Sun")> 0)
	clearInterval(waitHandle);
	document.proform.Accept.disabled = false;
}
<!--  23 July 2004: End Changes -->
<!-- VSSKENDPOLICYVAL#Java#47 -->



<!-- VSSKBEGINPOLICYVAL#Java#48 -->
<!--  23 July 2004: Begin Changes -->
<!-- This scriptlet sets the correct client browser -->
<SCRIPT LANGUAGE="JavaScript1.2"><!--
    var _info = navigator.userAgent;
    var _safari = false;
    var _ns = false;
    var _windows = (_info.indexOf("Win") > 0 );
    var _ie = (_info.indexOf("MSIE")> 0 && _info.indexOf("Win") > 0   && _info.indexOf("Windows 3.1") < 0);

    if(_ie == false){
    	_safari = (_info.indexOf("Safari") > 0 && _info.indexOf("Macintosh") > 0 );
    }

//--></SCRIPT>
<COMMENT>
	<SCRIPT LANGUAGE="JavaScript1.1"><!--
    	var _ns = (navigator.appName.indexOf("Netscape") > 0 || _info.indexOf("Netscape") > 0);	//-- Check if Netscape browser
	//--></SCRIPT>
</COMMENT>
<!--  23 July 2004: End Changes -->
<!-- VSSKENDPOLICYVAL#Java#48 -->



<!-- VSSKBEGINPOLICYVAL#Java#49 -->
<!--  23 July 2004: Begin Changes -->
<!-- clear the interval depending on browser and OS. This is used in changePasswordJava.htm -->
<SCRIPT language=javascript>
//functions to handle error coded returned by javapta
function waitApplet()
{
	 if(_info.indexOf("Linux")> 0)
	 waitHandle = setInterval("handleError()",23000);
	 else if(_info.indexOf("Sun")> 0)
	 waitHandle = setInterval("handleError()",43000);
	 else
	 handleError()
  	 return true;
}
</SCRIPT>
<!--  23 July 2004: End Changes -->
<!-- VSSKENDPOLICYVAL#Java#49 -->


<!-- VSSKBEGINPOLICYVAL#Java#50 -->
//  23 July 2004: Begin Changes
// set the interval depending on browser and OS
if(_info.indexOf("Linux")> 0)
 waitHandle = setInterval("waitApplet()",22000);
 else if(_info.indexOf("Sun")> 0)
 waitHandle = setInterval("waitApplet()",42000);
 else
 waitApplet()
//  23 July 2004: End Changes
<!-- VSSKENDPOLICYVAL#Java#50 -->



<!-- VSSKBEGINPOLICYVAL#Java#51 -->
<!--  23 July 2004: Begin Changes used in submitTransaction.html and trasient.html -->
<!-- This scriptlet sets the correct client browser -->
<SCRIPT LANGUAGE="JavaScript1.2"><!--
    var _info = navigator.userAgent;
    var _safari = false;
    var _ns = false;
    var _windows = (_info.indexOf("Win") > 0 );
    var _ie = (_info.indexOf("MSIE")> 0 && _info.indexOf("Win") > 0   && _info.indexOf("Windows 3.1") < 0);

    if(_ie == false){
    	_safari = (_info.indexOf("Safari") > 0 && _info.indexOf("Macintosh") > 0 );
    }

//--></SCRIPT>
<COMMENT>
	<SCRIPT LANGUAGE="JavaScript1.1"><!--
	var _moz = (navigator.appName.indexOf("Mozilla") > 0 || _info.indexOf("Mozilla") > -1);	//-- Check if Mozilla browser
    	var _ns = (navigator.appName.indexOf("Netscape") > 0 || _info.indexOf("Netscape") > 0);	//-- Check if Netscape browser
	//--></SCRIPT>
</COMMENT>
<!--  23 July 2004: End Changes -->
<!-- VSSKENDPOLICYVAL#Java#52 -->
