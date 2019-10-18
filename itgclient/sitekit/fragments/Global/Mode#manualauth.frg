// for MS IE manual auth enrollment - end-userMS.htm
<!-- VSSKBEGINPOLICYVAL#manualauth#1 -->
<FORM NAME="proform" ACTION="https://%%::vsHost%%/cgi-bin/sophia.exe" ENCTYPE=x-www-form-encoded METHOD=POST >
<INPUT TYPE=hidden NAME=remote_host VALUE="%%::remoteHost%%/cgi-bin/haydn.exe">
<input TYPE=hidden NAME=operation VALUE="C1LRAUserSubmit">
<!-- VSSKENDPOLICYVAL#manualauth#1 -->


//for firefox manual auth enrollment - end-userNS.htm
<!-- VSSKBEGINPOLICYVAL#manualauth#2 -->
<FORM NAME="proform" ACTION="https://%%::vsHost%%/cgi-bin/sophia.exe" ENCTYPE=x-www-form-encoded METHOD=POST>
<INPUT TYPE=hidden NAME=remote_host VALUE="%%::remoteHost%%/cgi-bin/haydn.exe">
<input TYPE=hidden NAME=operation VALUE="C1LRAUserSubmit">
<!-- VSSKENDPOLICYVAL#manualauth#2 -->


// fragment from revoke_start.htm 
<!-- VSSKBEGINPOLICYVAL#manualauth#3#1.0.0.2 -->
<FORM METHOD=POST ACTION=https://%%::vsHost%%/cgi-bin/rvoke.exe>
<INPUT TYPE=HIDDEN NAME=form_file VALUE="../fdf/VSApps/client/userRevoke.fdf">
<INPUT TYPE=HIDDEN NAME=remote_host VALUE="%%::remoteHost%%/cgi-bin/haydn.exe">
<INPUT TYPE=HIDDEN NAME=issuerSerial VALUE="$$vs_issuer_digest$$">
<INPUT TYPE=HIDDEN NAME=subject VALUE="$$subject$$">

<!--BEGIN CONTENT TABLE ONE-->
<TABLE WIDTH=588 BGCOLOR="cccccc" CELLPADDING=7 CELLSPACING=0 BORDER=0>
<TR>
    <TD WIDTH=588><FONT FACE="VERDANA, ARIAL, HELVETICA" SIZE=2>By applying for, submitting, or using a Digital ID, you are agreeing to the terms of the Symantec Relying Party Agreement. 
   </FONT>  
   <P>
   <CENTER>
       <!--BEGIN CONTENT IN TABLE ONE-->
       <TABLE WIDTH=574 CELLPADDING=3 CELLSPACING=2 BORDER=0>
       <TR>
         <TD WIDTH=50% VALIGN=top BGCOLOR="ffffcc"><FONT FACE="verdana, arial, helvetica" SIZE=2><B>Challenge Phrase:</B><BR></FONT></TD>
         <TD WIDTH=50% BGCOLOR="ffffcc"><INPUT NAME=challenge TYPE=PASSWORD size=32></TD>
       </TR>
       <TR>
    	 <TD WIDTH=50% BGCOLOR="ffffcc"><FONT FACE="verdana, arial, helvetica" SIZE=2><B>Reason For Revoking:</B><BR></FONT></TD>
         <TD WIDTH=50% BGCOLOR="ffffcc">
         <SELECT Name=reason>
	    <OPTION VALUE="Key compromise">Key compromise
	    <OPTION VALUE="CA compromise">CA compromise
	    <OPTION VALUE="Affiliation changed">Affiliation changed
	    <OPTION VALUE="Superseded">Superseded
	    <OPTION VALUE="Cessation of operation">Cessation of operation
	    <OPTION VALUE="Certificate hold">Certificate hold
	    <OPTION VALUE="Privilege withdrawn">Privilege withdrawn
	    <OPTION VALUE="AA compromise">AA compromise
	    <OPTION VALUE="Unspecified">Unspecified
          </SELECT>
          </TD>
       </TR>
       </TABLE>
    </CENTER>
<!--END CONTENT IN TABLE ONE-->
</TR>
</TABLE>
<!--END CONTENT TABLE ONE-->
<P>
<TABLE WIDTH=588 CELLPADDING=0 CELLSPACING=0 BORDER=0>
<TR>
    <TD WIDTH=50><IMG SRC="../graphics/action_39x39.gif" WIDTH="40" HEIGHT="39" BORDER="0"></TD> 
    <TD WIDTH=388><FONT COLOR="009933" FACE="arial, helvetica" SIZE=2><B>Click the Submit button to Revoke<BR> 
    the Digital ID.</B><BR></FONT></TD>
    <TD WIDTH=150><INPUT TYPE="image" VALUE="submit" IMG SRC="../graphics/button_submit.gif" border=0 alt="retrieve button"></TD>
</TR>
</TABLE>
</FORM>
<!-- VSSKENDPOLICYVAL#manualauth#3 -->



// from revoke.htm
<!-- VSSKBEGINPOLICYVAL#manualauth#4 -->
<!-- VSSKENDPOLICYVAL#manualauth#4 -->


// form parameters for end-userCSR.htm
<!-- VSSKBEGINPOLICYVAL#manualauth#5 -->
<FORM ENCTYPE="multipart/form-data" ACTION = "https://%%::vsHost%%/cgi-bin/upload.exe" METHOD=POST>
<INPUT TYPE=hidden NAME=remote_host VALUE="%%::remoteHost%%/cgi-bin/haydn.exe">
<!-- VSSKENDPOLICYVAL#manualauth#5 -->

// form parameters for end-userCSRMain.htm
<!-- VSSKBEGINPOLICYVAL#manualauth#6 -->
<FORM NAME="proform" ACTION="https://%%::vsHost%%/cgi-bin/sophia.exe" ENCTYPE=x-www-form-encoded METHOD=POST onsubmit="return lastCheck()">
<input TYPE=hidden NAME=operation VALUE="C1LRAUserSubmit">
<INPUT TYPE=hidden NAME=remote_host VALUE="%%::remoteHost%%/cgi-bin/haydn.exe">
<!-- VSSKENDPOLICYVAL#manualauth#6 -->

// for the MS and NS pickup files: mspickup.htm and nspickup.htm
<!-- VSSKBEGINPOLICYVAL#manualauth#7 -->
<FORM NAME="proform" METHOD="POST" ACTION="https://%%::vsHost%%/cgi-bin/sophia.exe">
<INPUT TYPE="hidden" NAME="remote_host" VALUE="%%::remoteHost%%/cgi-bin/haydn.exe">
<!-- VSSKENDPOLICYVAL#manualauth#7 -->

// for the revoke files: revoke.htm
// and query files:noCertFound.htm, search.htm 
<!-- VSSKBEGINPOLICYVAL#manualauth#8 -->
<FORM NAME=form1 METHOD=POST ACTION="https://%%::vsHost%%/cgi-bin/Xquery.exe">
<INPUT TYPE=hidden NAME=remote_host VALUE="%%::remoteHost%%/cgi-bin/haydn.exe">
<!-- VSSKENDPOLICYVAL#manualauth#8 -->

// for the revoke files: revoke.htm
// and query files:noCertFound.htm, search.htm 
<!-- VSSKBEGINPOLICYVAL#manualauth#9 -->
<FORM NAME=form2 METHOD=POST ACTION="https://%%::vsHost%%/cgi-bin/Xquery.exe">
<INPUT TYPE=hidden NAME=remote_host VALUE="%%::remoteHost%%/cgi-bin/haydn.exe">
<!-- VSSKENDPOLICYVAL#manualauth#9 -->

// for the revoke files: revokeConfirm.htm
<!-- VSSKBEGINPOLICYVAL#manualauth#10 -->
<FORM METHOD=POST ACTION="https://%%::vsHost%%/cgi-bin/Xquery.exe">
<!-- VSSKENDPOLICYVAL#manualauth#10 -->


// for query files: userQueryResult.htm
<!-- VSSKBEGINPOLICYVAL#manualauth#11 -->
        <FORM NAME="prevpage" METHOD=POST ACTION=https://%%::vsHost%%/cgi-bin/Xquery.exe>
        <INPUT TYPE=hidden NAME=remote_host VALUE="%%::remoteHost%%/cgi-bin/haydn.exe">
<!-- VSSKENDPOLICYVAL#manualauth#11 -->

// for the query files: userQueryResult.htm
<!-- VSSKBEGINPOLICYVAL#manualauth#12 -->
        <FORM NAME="nextpage" METHOD=POST ACTION=https://%%::vsHost%%/cgi-bin/Xquery.exe>
        <INPUT TYPE=hidden NAME=remote_host VALUE="%%::remoteHost%%/cgi-bin/haydn.exe">
<!-- VSSKENDPOLICYVAL#manualauth#12 -->


// for the download files, download.htm
<!-- VSSKBEGINPOLICYVAL#manualauth#13 -->
<FORM Name=form0 METHOD=POST ACTION=https://%%::vsHost%%/cgi-bin/sophia.exe>
<INPUT TYPE=hidden NAME=remote_host VALUE="%%::remoteHost%%/cgi-bin/haydn.exe">
<!-- VSSKENDPOLICYVAL#manualauth#13 -->


//for the firefox renewal file userRenewalNS.htm
<!-- VSSKBEGINPOLICYVAL#manualauth#14 -->
<FORM METHOD="POST" NAME="Renewal" ACTION="https://%%::vsHost%%/cgi-bin/sophia.exe" enctype="x-www-form-encoded">
<INPUT TYPE=hidden NAME=remote_host VALUE="%%::remoteHost%%/cgi-bin/haydn.exe">
<!-- VSSKENDPOLICYVAL#manualauth#14 -->

//for the MSIE renewal file userRenewalMS.htm
<!-- VSSKBEGINPOLICYVAL#manualauth#15 -->
<FORM METHOD=POST NAME="theform" ACTION=https://%%::vsHost%%/cgi-bin/sophia.exe>
<INPUT TYPE=hidden NAME=remote_host VALUE="%%::remoteHost%%/cgi-bin/haydn.exe">
<!-- VSSKENDPOLICYVAL#manualauth#15 -->


// for userQueryResult.htm
<!-- VSSKBEGINPOLICYVAL#manualauth#16 -->
<a href="https://%%::vsHost%%/cgi-bin/Xquery.exe?vs_issuer_digest=$$VS_ISSUER_DIGEST$$&remote_host=%%::remoteHost%%/cgi-bin/haydn.exe&Template=certByIssuer&form_file=../fdf/VSApps/client/userQueryResult.fdf&cert_jurisdiction_hash=%%::jurisdictionHash%%">
<!-- VSSKENDPOLICYVAL#manualauth#16 -->


// for checkLibrary.htm
<!-- VSSKBEGINPOLICYVAL#manualauth#17 -->
<!-- VSSKENDPOLICYVAL#manualauth#17 -->

<!-- VSSKBEGINPOLICYVAL#manualauth#18 -->
       <A HREF="%%::remoteHost%%/VSApps/digitalidCenter.htm">
<!-- VSSKENDPOLICYVAL#manualauth#18 -->


// for userEnrollMS.htm
<!-- VSSKBEGINPOLICYVAL#manualauth#19#1.2.0.0 -->
  <object
   classid="clsid:127698e4-e730-4e5c-a2b1-21490a70c8a1"
   CODEBASE="%%::remoteHost%%/VSApps/xenroll.cab"
   id="cenroll"
  >
  </object>

  <Span ID=spnCertEnroll Style="display:none">
  </Span>
  
    <script language = "javascript">
  //
  // This script checks whether we're running under Windows Vista.
  // If this is Vista, isRunningOnVista is set to 1
  // If this is non-Vista, the value is set to 0
  //
  // This variable is used in other places to switch between XEnroll and Vista classes
  // for enrollment
  //
	var isRunningOnVista = 0
	var forceProviderName = ""
	var forceProviderType = 0
      var firstSearch = 0
	function CheckIfVista()
	{
		if (navigator.userAgent.indexOf("NT") >= 0 && navigator.userAgent.substr(navigator.userAgent.indexOf("NT")+3, 1) >=6)
		{
			//alert("Running on Vista.")
			isRunningOnVista = 1
		} 
		else
		{
			isRunningOnVista = 0
			//alert("Running on a non-Vista OS.")	
		}
	}
  </script>
<!-- VSSKENDPOLICYVAL#manualauth#19 -->

// for userRenewalMS.htm
<!-- VSSKBEGINPOLICYVAL#manualauth#20 -->
<object
   classid="clsid:86C4AF33-6171-11D2-80CD-006008B066EE"
   CODEBASE="%%::remoteHost%%/VSRenewSign.cab">
</object>
<!-- VSSKENDPOLICYVAL#manualauth#20 -->

// for userEnrollMS.fdf userEnrollNS.fdf
<!-- VSSKBEGINPOLICYVAL#manualauth#21 -->
<!-- VSSKENDPOLICYVAL#manualauth#21 -->

// for userInstallEncMS.htm
<!-- VSSKBEGINPOLICYVAL#manualauth#22#1.0.0.1 -->
<OBJECT
   classid="clsid:B1D475FE-75CD-11D2-8301-0060B0B32E16"
   CODEBASE="%%::remoteHost%%/VSApps/VSImport.cab#VERSION=2,0,0,5"
   id="Import">
</OBJECT>
<!-- VSSKENDPOLICYVAL#manualauth#22 -->


// for enrollment and renewal fdfs for MSIE
<!-- VSSKBEGINPOLICYVAL#manualauth#23 -->
CONST    application                  VeriSignOnSiteMSIE
<!-- VSSKENDPOLICYVAL#manualauth#23 -->

// for enrollment and renewal fdfs for Firefox
<!-- VSSKBEGINPOLICYVAL#manualauth#24 -->
CONST    application                  VeriSignOnSiteNetscape
<!-- VSSKENDPOLICYVAL#manualauth#24 -->


// for the ms and nspickup.fdf files
<!-- VSSKBEGINPOLICYVAL#manualauth#25 -->
<!-- VSSKENDPOLICYVAL#manualauth#25 -->


// for the WAC pages...VsPref...
<!-- VSSKBEGINPOLICYVAL#manualauth#26 -->
<OBJECT
  classid="clsid:70D86F3C-BA4D-11D2-80F5-006008B066EE"
  CODEBASE="%%::remoteHost%%/vspcakm.cab#VERSION=2,0,0,4"
  id="IVSPrefMgmt"
  style="LEFT: Opx; TOP: Opx; VISIBILITY: hidden"
>
</OBJECT>
<!-- VSSKENDPOLICYVAL#manualauth#26 -->


// for the WAC pages...VSPvkOps
<!-- VSSKBEGINPOLICYVAL#manualauth#27 -->
<OBJECT
classid="clsid:BFDA6775-C868-11D2-8100-006008B066EE"
CODEBASE="%%::remoteHost%%/vspcakm.cab#VERSION=2,0,0,4"
id="IVSPvkOps"
style="LEFT: Opx; TOP: Opx; VISIBILITY: hidden"
>
</OBJECT>
<!-- VSSKENDPOLICYVAL#manualauth#27 -->


<!-- VSSKBEGINPOLICYVAL#manualauth#28 -->
<FORM METHOD="post" NAME="RenewalForm" ENCTYPE="x-www-form-encoded" ACTION=%%::remoteHost%%/cgi-bin/softbounce.exe>
<!-- VSSKENDPOLICYVAL#manualauth#28 -->


// for the PCA Login pages...
<!-- VSSKBEGINPOLICYVAL#manualauth#29 -->
   Dim hostName
   hostName = "%%::remoteHost%%"
<!-- VSSKENDPOLICYVAL#manualauth#29 -->


// for the PCA Login pages...
<!-- VSSKBEGINPOLICYVAL#manualauth#30 -->
   var hostName = "%%::remoteHost%%";
<!-- VSSKENDPOLICYVAL#manualauth#30 -->

// got the PCA NS Login page...
<!-- VSSKBEGINPOLICYVAL#manualauth#31 -->
        self.location = "%%::remoteHost%%/VSApps/client/getplugin.htm";
<!-- VSSKENDPOLICYVAL#manualauth#31 -->

// temporary fragment to solve the certDN bug in exchange integration
<!-- VSSKBEGINPOLICYVAL#manualauth#32 -->
    certDN="cn=" & Chr(34) & Trunc & Chr(34) & "," & certDN
<!-- VSSKENDPOLICYVAL#manualauth#32 -->

//-- fragment for AddRootCerts Interface...
<!-- VSSKBEGINPOLICYVAL#manualauth#33#1.0.0.8 -->
<OBJECT
   classid="clsid:50E71FEB-2234-11d4-8D73-0060B0FC0637"
   CODEBASE="%%::remoteHost%%/VSApps/vspta3.cab#VERSION=2,1,0,9"
   id="ObjectIAddRootCerts"
   style="LEFT: Opx; TOP: Opx; VISIBILITY: hidden"
>
</OBJECT>
<!-- VSSKENDPOLICYVAL#manualauth#33 -->


// temporary fragment to solve the certDN bug in exchange integration
<!-- VSSKBEGINPOLICYVAL#manualauth#34 -->
    certDN="cn=" + "\"" + Trunc + "\"" + "," + certDN ;
<!-- VSSKENDPOLICYVAL#manualauth#34 -->

// for the PCA Login pages...
<!-- VSSKBEGINPOLICYVAL#manualauth#35 -->
   Dim helpHostName
   helpHostName = "%%::remoteHost%%"
<!-- VSSKENDPOLICYVAL#manualauth#35 -->


// for the PCA Login pages...
<!-- VSSKBEGINPOLICYVAL#manualauth#36 -->
   var helpHostName = "%%::remoteHost%%";
<!-- VSSKENDPOLICYVAL#manualauth#36 -->

<!-- VSSKBEGINPOLICYVAL#manualauth#37 -->
    document.proform.exchange_DN.value = distinguishedName ;
<!-- VSSKENDPOLICYVAL#manualauth#37 -->

<!-- VSSKBEGINPOLICYVAL#manualauth#38 -->
    document.proform.cert_DN.value = certDN ;
<!-- VSSKENDPOLICYVAL#manualauth#38 -->

<!-- VSSKBEGINPOLICYVAL#manualauth#39 -->
<OBJECT
   classid="clsid:5CBAA8E0-234B-11D3-AE02-0060B0C4A3BC"
   CODEBASE="%%::remoteHost%%/vsexports.cab#VERSION=2,1,0,3"
   id="Exports"
   style="LEFT: Opx; TOP: Opx; VISIBILITY: hidden"
>
</OBJECT>
<!-- VSSKENDPOLICYVAL#manualauth#39 -->

<!-- VSSKBEGINPOLICYVAL#manualauth#40 -->
<SCRIPT Language="JavaScript">

if ( navigator.javaEnabled() ) {

   trigger = netscape.softupdate.Trigger;
   if ( trigger.UpdateEnabled() ) {

      if (navigator.platform == "Win32") {
         vi = new netscape.softupdate.VersionInfo(1, 0, 0, 3);
         trigger.ConditionalSoftwareUpdate(
            "%%::remoteHost%%/vsnp.jar",
             "plugins/verisign/vsnp",
             vi, trigger.DEFAULT_MODE);
      }
      else alert("This plug-in only runs on Windows NT/95.")
   }
   else
      alert("Enable SmartUpdate before running this script.");

}
else
   alert("Enable Java before running this script.");


</SCRIPT>
<!-- VSSKENDPOLICYVAL#manualauth#40 -->

<!-- VSSKBEGINPOLICYVAL#manualauth#41#1.2.0.9 -->
  <object
   classid="clsid:5685505C-DA94-11D3-A1C3-001083023D07"
   CODEBASE="%%::remoteHost%%/VSApps/VSGSE.cab#VERSION=2,6,0,3"
   id="IGSE"
  >
  </object>
<!-- VSSKENDPOLICYVAL#manualauth#41 -->

<!-- VSSKBEGINPOLICYVAL#manualauth#42 -->
            Document.proform.exchange_DN.value = distinguishedName
<!-- VSSKENDPOLICYVAL#manualauth#42 -->

<!-- VSSKBEGINPOLICYVAL#manualauth#43 -->
            Document.proform.cert_DN.value = certDN
<!-- VSSKENDPOLICYVAL#manualauth#43 -->

<!-- VSSKBEGINPOLICYVAL#manualauth#44 -->
<!-- VSSKBEGIN Enrollment/CharEncoding#3 -->
<!-- VSSKEND Enrollment/CharEncoding#3 -->
<!-- VSSKENDPOLICYVAL#manualauth#44 -->

<!-- VSSKBEGINPOLICYVAL#manualauth#101#1.0.0.8 -->
<OBJECT
  classid="clsid:6F7864F9-DB33-11D3-8166-0060B0F885E6"
  CODEBASE="%%::remoteHost%%/VSApps/vspta3.cab#VERSION=2,1,0,9"
  id="IVSPTA"
  style="LEFT: Opx; TOP: Opx; VISIBILITY: hidden"
>
</OBJECT>
<!-- VSSKENDPOLICYVAL#manualauth#101 -->

// got the PCA NS Login page...
<!-- VSSKBEGINPOLICYVAL#manualauth#102#1.2.0.5 -->
	if(browserNum < 5){
        self.location = "%%::remoteHost%%/VSApps/client/getplugin.htm";
    } else {
		self.location = "%%::remoteHost%%/VSApps/error/PTAUnsupportedBrowser.htm";
    }
<!-- VSSKENDPOLICYVAL#manualauth#102 -->

// error reporting for login and transaction pages
<!-- VSSKBEGINPOLICYVAL#manualauth#103 -->
<FORM NAME=ErrorForm ACTION="%%::remoteHost%%/cgi-bin/softbounce.exe" METHOD=POST>
<!-- VSSKENDPOLICYVAL#manualauth#103 -->

<!-- VSSKBEGINPOLICYVAL#manualauth#104 -->
         Result = trigger.ConditionalSoftwareUpdate(
            "%%::remoteHost%%/VSApps/vspta3km.jar",
             "plugins/verisign/vspta",
             vi, trigger.DEFAULT_MODE);
<!-- VSSKENDPOLICYVAL#manualauth#104 -->

<!-- VSSKBEGINPOLICYVAL#manualauth#105 -->
         Result = trigger.ConditionalSoftwareUpdate(
            "%%::remoteHost%%/VSApps/vspta3.jar",
            "plugins/verisign/vspta",
             vi, trigger.DEFAULT_MODE);
<!-- VSSKENDPOLICYVAL#manualauth#105 -->

<!-- VSSKBEGINPOLICYVAL#manualauth#106 -->
<OBJECT
   classid="clsid:71C6919E-F9C0-11D2-8344-0060B0B32E16"
   codeBase="%%::remoteHost%%/VSApps/VSSgnAtb.cab#VERSION=2,0,0,8"
   id="ISignAtrb">
</OBJECT>
<!-- VSSKENDPOLICYVAL#manualauth#106 -->

<!-- VSSKBEGINPOLICYVAL#manualauth#107#1.0.0.2 -->

<OBJECT
   classid="clsid:6C67604E-91A2-11D3-8C1B-0010830169AF"
   codeBase="%%::remoteHost%%/VSApps/vsfe.cab#VERSION=1,0,1,1"
   id="vsctl">
</OBJECT>

<!-- include the PTA control -->
<OBJECT
  classid="clsid:6F7864F9-DB33-11D3-8166-0060B0F885E6"
  CODEBASE="%%::remoteHost%%/VSApps/vsfe.cab#VERSION=1,0,2,7">
</OBJECT>

<SCript Language="JavaScript">
<!--
    var policyFileLocation = "%%::remoteHost%%/VSApps";
//-->
</Script>
<!-- VSSKENDPOLICYVAL#manualauth#107 -->

//-- include the PTA control/plugin on the PTA logout page 
<!-- VSSKBEGINPOLICYVAL#manualauth#108#1.2.1.1 -->
<script Language="JavaScript">
<!--
if (navigator.appName == "Netscape")
{ document.write("<EMBED type='application/x-vspta2-plugin' name='ThePlugin' WIDTH=0 HEIGHT=0 HIDDEN>"); }
else
{ document.write("<OBJECT classid='clsid:6F7864F9-DB33-11D3-8166-0060B0F885E6' CODEBASE='%%::remoteHost%%/VSApps/vspta3.cab#VERSION=2,1,0,9' id='IVSPTA' style='LEFT: Opx; TOP: Opx; VISIBILITY: hidden'></OBJECT>");}
//-->
</script>
<!-- VSSKENDPOLICYVAL#manualauth#108 -->

<!-- VSSKBEGINPOLICYVAL#manualauth#109 -->
window.navigate("%%::remoteHost%%/cgi-bin/softbounce.exe?form_file=../fdf/VSApps/client/ExchangeErrors.fdf&errorCode=10000000&operation=Enrollment Status&showError=")
<!-- VSSKENDPOLICYVAL#manualauth#109 -->

<!-- VSSKBEGINPOLICYVAL#manualauth#110 -->
<input TYPE=hidden NAME=Enroll_operation VALUE="C1LRAUserSubmit">
<input TYPE=hidden NAME=CertRqstPostURL VALUE="https://%%::vsHost%%/cgi-bin/sophia.exe">
<INPUT TYPE=hidden NAME=Enroll_remote_host VALUE="%%::remoteHost%%/cgi-bin/haydn.exe">
<!-- VSSKENDPOLICYVAL#manualauth#110 -->

<!-- VSSKBEGINPOLICYVAL#manualauth#111 -->
<input type="hidden" name="ReturnURL" value="%%::remoteHost%%/VSApps/client/userInstallSuccess.htm">
<!-- VSSKENDPOLICYVAL#manualauth#111 -->

<!-- VSSKBEGINPOLICYVAL#manualauth#112#1.0.0.2 -->
<input type="hidden" name="ReturnURL" value="%%::remoteHost%%/VSApps/client/changePasswdSuccess.htm">
<!-- VSSKENDPOLICYVAL#manualauth#112 -->

<!-- VSSKBEGINPOLICYVAL#manualauth#113 -->
<input type="hidden" name="CancelURL" value="%%::remoteHost%%/VSApps/client/ptsCancel.htm">
<!-- VSSKENDPOLICYVAL#manualauth#113 -->

<!-- VSSKBEGINPOLICYVAL#manualauth#114#1.0.0.2 -->
<!-- include the PTA control -->
<OBJECT
   classid="clsid:D66256E2-B99C-11D4-8C74-0010830169AF"
   codeBase="%%::remoteHost%%/VSApps/vsnzpta.cab#VERSION=1,0,0,3"
   id="IVSNZ"
>
</OBJECT>

<OBJECT
  classid="clsid:6F7864F9-DB33-11D3-8166-0060B0F885E6"
  CODEBASE="%%::remoteHost%%/VSApps/vsnzpta.cab#VERSION=1,0,2,7"
>
</OBJECT>
<!-- VSSKENDPOLICYVAL#manualauth#114 -->

<!-- VSSKBEGINPOLICYVAL#manualauth#115 -->
	if(browserNum < 5){
        self.location = "%%::remoteHost%%/VSApps/client/getnzptaplugin.htm";
    } else {
		self.location = "%%::remoteHost%%/VSApps/client/getnzptaplugin6.htm";
    }
<!-- VSSKENDPOLICYVAL#manualauth#115 -->

<!-- VSSKBEGINPOLICYVAL#manualauth#116 -->
   Result = trigger.ConditionalSoftwareUpdate(
            "%%::remoteHost%%/VSApps/vsnzpta.jar",
            "verisign/vspta", vi, trigger.DEFAULT_MODE);
<!-- VSSKENDPOLICYVAL#manualauth#116 -->


<!-- VSSKBEGINPOLICYVAL#manualauth#117 -->
   Result = trigger.ConditionalSoftwareUpdate(
            "%%::remoteHost%%/VSApps/vsdnotz.jar",
            "verisign/vsdnotz", vi, trigger.DEFAULT_MODE);
<!-- VSSKENDPOLICYVAL#manualauth#117 -->

<!-- VSSKBEGINPOLICYVAL#manualauth#118 -->
<input type="hidden" name="CertRenewPostURL" value="https://%%::vsHost%%/cgi-bin/sophia.exe">
<input type="hidden" name="Renew_remote_host" value="%%::remoteHost%%/cgi-bin/haydn.exe">
<!-- VSSKENDPOLICYVAL#manualauth#118 -->

<!-- VSSKBEGINPOLICYVAL#manualauth#119 -->
<INPUT type="hidden" name="ErrorPage.ReturnUrl" value="%%::remoteHost%%/VSApps/digitalidCenter.htm">
<!-- VSSKENDPOLICYVAL#manualauth#119 -->

<!-- VSSKBEGINPOLICYVAL#manualauth#120 -->

<OBJECT
    classid="clsid:8AD9C840-044E-11D1-B3E9-00805F499D93"
    WIDTH = 640 HEIGHT = 400 NAME = "PtaApplet"
    STANDBY="Please wait as the applet is being loaded..."
    codebase="http://java.sun.com/products/plugin/autodl/jinstall-1_4_1-windows-i586.cab#Version=1,4,1,mn">
    <PARAM NAME = CODE VALUE = "com.verisign.pta.applet.PtaApplet" >
	<PARAM NAME = CODEBASE VALUE = "%%::remoteHost%%/VSApps/" >
	<PARAM NAME = ARCHIVE VALUE = vsJavaPta.jar >
	<PARAM NAME = NAME VALUE = "PtaApplet" >
	<PARAM NAME = MAYSCRIPT VALUE = true >
        <PARAM NAME = browser VALUE = IE>
    	<PARAM NAME="type" VALUE="application/x-java-applet;version=1.4.1">
    	<PARAM NAME="scriptable" VALUE="true">

    <COMMENT>
	<EMBED
            type="application/x-java-applet;version=1.4.1"
            CODE = "com.verisign.pta.applet.PtaApplet"
            CODEBASE = "%%::remoteHost%%/VSApps/"
            ARCHIVE = vsJavaPta.jar
            NAME = "PtaApplet"
            WIDTH = 640
            HEIGHT = 400
	    MAYSCRIPT = true
	    scriptable = true
            browser = netscape
	    pluginspage="http://java.sun.com/j2se/1.4.1/download.html">
	        <noembed>
		No Java 2 SDK support available for applet
		</noembed>
	</EMBED>
    </COMMENT>
</OBJECT>



<!-- VSSKENDPOLICYVAL#manualauth#120 -->

// for javapta Login pages...
<!-- VSSKBEGINPOLICYVAL#manualauth#121 -->
   hostName = "%%::remoteHost%%"
<!-- VSSKENDPOLICYVAL#manualauth#121 -->

<!-- VSSKBEGINPOLICYVAL#manualauth#122 -->
  if(browserNum >= 5){
	  self.location = "%%::remoteHost%%/VSApps/error/PTAUnsupportedBrowser.htm";
  }
<!-- VSSKENDPOLICYVAL#manualauth#122 -->

<!-- VSSKBEGINPOLICYVAL#manualauth#123 -->
<SCRIPT Language="VBScript">
<!--
     Dim dummyObj
	 On Error Resume Next
	 Set dummyObj=ConfChk.GetVersion("crypt32.dll",szCryptVersion)
     If ( (Hex(err.number) = "1B6") AND (InStr(1,navigator.appMinorVersion,";SP2;") > 0)  ) Then
         window.location = "./client/installComponentForSP2.htm"
     End if
-->
</SCRIPT>
<!-- VSSKENDPOLICYVAL#manualauth#123 -->

<!-- VSSKBEGINPOLICYVAL#manualauth#124 -->
try{
	dummy=ConfChk.getName();
	temp = 1;
}catch(er){
	temp=0;
	window.open("../vsapps/error/win2k.htm","_self");
}
<!-- VSSKENDPOLICYVAL#manualauth#124 -->

<!-- VSSKBEGINPOLICYVAL#manualauth#125#1.0.0.6 -->
document.write('<OBJECT');
document.write('  classid="clsid:6F7864F9-DB33-11D3-8166-0060B0F885E6"');
document.write('  CODEBASE="%%::remoteHost%%/VSApps/vspta3.cab#VERSION=2,1,0,9"');
document.write('  id="IVSPTA"');
document.write('  style="LEFT: Opx; TOP: Opx; VISIBILITY: hidden"');
document.write('>');
document.write('</OBJECT>');
<!-- VSSKENDPOLICYVAL#manualauth#125 -->

<!-- VSSKBEGINPOLICYVAL#manualauth#126 -->
<!-- VSSKENDPOLICYVAL#manualauth#126 -->

<!-- VSSKBEGINPOLICYVAL#manualauth#127#1.2.0.7 -->
document.write('<OBJECT');
document.write('   classid="clsid:5685505C-DA94-11D3-A1C3-001083023D07"');
document.write('   CODEBASE="%%::remoteHost%%/VSApps/VSGSE.cab#VERSION=2,6,0,3"');
document.write('   id="IGSE"');
document.write('	style="VISIBILITY: hidden" >');
document.write('</OBJECT>');
<!-- VSSKENDPOLICYVAL#manualauth#127 -->

<!-- VSSKBEGINPOLICYVAL#manualauth#128#1.0.0.1 -->
document.write('<OBJECT');
document.write('   classid="clsid:B1D475FE-75CD-11D2-8301-0060B0B32E16"');
document.write('   CODEBASE="%%::remoteHost%%/VSApps/VSImport.cab#VERSION=2,0,0,5"');
document.write('   id="Import"');
document.write('   style="LEFT: Opx; TOP: Opx; VISIBILITY: hidden"');
document.write('>');
document.write('</OBJECT>');
<!-- VSSKENDPOLICYVAL#manualauth#128 -->

<!-- VSSKBEGINPOLICYVAL#manualauth#129 -->
document.write('<OBJECT');
document.write('   classid="clsid:71C6919E-F9C0-11D2-8344-0060B0B32E16"');
document.write('   codeBase="%%::remoteHost%%/VSApps/VSSgnAtb.cab#VERSION=2,0,0,8"');
document.write('   id="ISignAtrb"');
document.write('   style="VISIBILITY: hidden">');
document.write('</OBJECT>');
<!-- VSSKENDPOLICYVAL#manualauth#129 -->

//include script for OBJECT declaration
<!-- VSSKBEGINPOLICYVAL#manualauth#130#1.0.0.1 -->
<script src="%%::remoteHost%%/VSApps/client/createObject.js" language="JavaScript"></script>
<!-- VSSKENDPOLICYVAL#manualauth#130 -->

<!-- VSSKBEGINPOLICYVAL#manualauth#131 -->
<script language="JavaScript"> createJavaPluginObject();</script>
<!-- VSSKENDPOLICYVAL#manualauth#131 -->
