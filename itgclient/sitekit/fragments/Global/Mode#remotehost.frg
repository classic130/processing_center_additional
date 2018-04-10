// for MS IE manual auth enrollment - end-userMS.htm
<!-- VSSKBEGINPOLICYVAL#remotehost#1 -->
<FORM NAME="proform" ACTION="https://%%::vsHost%%/cgi-bin/sophia.exe" ENCTYPE=x-www-form-encoded METHOD=POST >
<input TYPE=hidden NAME=operation VALUE="C1LRAUserSubmit">
<!-- VSSKENDPOLICYVAL#remotehost#1 -->


//for firefox manual auth enrollment - end-userNS.htm
<!-- VSSKBEGINPOLICYVAL#remotehost#2 -->
<FORM NAME="proform" ACTION="https://%%::vsHost%%/cgi-bin/sophia.exe" ENCTYPE=x-www-form-encoded METHOD=POST>
<input TYPE=hidden NAME=operation VALUE="C1LRAUserSubmit">
<!-- VSSKENDPOLICYVAL#remotehost#2 -->


// fragment from revoke_start.htm 
<!-- VSSKBEGINPOLICYVAL#remotehost#3#1.0.0.2 -->
<FORM METHOD=POST ACTION=https://%%::vsHost%%/cgi-bin/rvoke.exe>
<INPUT TYPE=HIDDEN NAME=form_file VALUE="../fdf/VSApps/client/userRevoke.fdf">
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
<!-- VSSKENDPOLICYVAL#remotehost#3 -->


// from revoke.htm
<!-- VSSKBEGINPOLICYVAL#remotehost#4 -->
<!-- VSSKENDPOLICYVAL#remotehost#4 -->



// form parameters for end-userCSR.htm
<!-- VSSKBEGINPOLICYVAL#remotehost#5 -->
<FORM ENCTYPE="multipart/form-data" ACTION = "https://%%::vsHost%%/cgi-bin/upload.exe" METHOD=POST>
<!-- VSSKENDPOLICYVAL#remotehost#5 -->

// form parameters for end-userCSRMain.htm
<!-- VSSKBEGINPOLICYVAL#remotehost#6 -->
<FORM NAME="proform" ACTION="https://%%::vsHost%%/cgi-bin/sophia.exe" ENCTYPE=x-www-form-encoded METHOD=POST onsubmit="return lastCheck()">
<input TYPE=hidden NAME=operation VALUE="C1LRAUserSubmit">
<!-- VSSKENDPOLICYVAL#remotehost#6 -->

// for the MS and NS pickup files: mspickup.htm and nspickup.htm
<!-- VSSKBEGINPOLICYVAL#remotehost#7 -->
<FORM NAME="proform" METHOD="POST" ACTION="https://%%::vsHost%%/cgi-bin/sophia.exe">
<!-- VSSKENDPOLICYVAL#remotehost#7 -->

// for the revoke files: revoke.htm
// and query files:noCertFound.htm, search.htm 
<!-- VSSKBEGINPOLICYVAL#remotehost#8 -->
<FORM NAME=form1 METHOD=POST ACTION="https://%%::vsHost%%/cgi-bin/Xquery.exe">
<!-- VSSKENDPOLICYVAL#remotehost#8 -->

// for the revoke files: revoke.htm
// and query files:noCertFound.htm, search.htm 
<!-- VSSKBEGINPOLICYVAL#remotehost#9 -->
<FORM NAME=form2 METHOD=POST ACTION="https://%%::vsHost%%/cgi-bin/Xquery.exe">
<!-- VSSKENDPOLICYVAL#remotehost#9 -->

// for the revoke files: revokeConfirm.htm
<!-- VSSKBEGINPOLICYVAL#remotehost#10 -->
<FORM METHOD=POST ACTION="https://%%::vsHost%%/cgi-bin/Xquery.exe">
<!-- VSSKENDPOLICYVAL#remotehost#10 -->


// for query files: userQueryResult.htm
<!-- VSSKBEGINPOLICYVAL#remotehost#11 -->
        <FORM NAME="prevpage" METHOD=POST ACTION=https://%%::vsHost%%/cgi-bin/Xquery.exe>
<!-- VSSKENDPOLICYVAL#remotehost#11 -->

// for the query files: userQueryResult.htm
<!-- VSSKBEGINPOLICYVAL#remotehost#12 -->
        <FORM NAME="nextpage" METHOD=POST ACTION=https://%%::vsHost%%/cgi-bin/Xquery.exe>
<!-- VSSKENDPOLICYVAL#remotehost#12 -->

// for the download files, download.htm
<!-- VSSKBEGINPOLICYVAL#remotehost#13 -->
<FORM Name=form0 METHOD=POST ACTION=https://%%::vsHost%%/cgi-bin/sophia.exe>
<!-- VSSKENDPOLICYVAL#remotehost#13 -->

//for the firefox renewal file userRenewalNS.htm
<!-- VSSKBEGINPOLICYVAL#remotehost#14 -->
<FORM METHOD="POST" NAME="Renewal" ACTION="https://%%::vsHost%%/cgi-bin/sophia.exe" enctype="x-www-form-encoded">
<!-- VSSKENDPOLICYVAL#remotehost#14 -->


//for the MSIE renewal file userRenewalMS.htm
<!-- VSSKBEGINPOLICYVAL#remotehost#15 -->
<FORM METHOD=POST NAME="theform" ACTION=https://%%::vsHost%%/cgi-bin/sophia.exe>
<!-- VSSKENDPOLICYVAL#remotehost#15 -->

// for userQueryResult.htm
<!-- VSSKBEGINPOLICYVAL#remotehost#16 -->
<a href="https://%%::vsHost%%/cgi-bin/Xquery.exe?vs_issuer_digest=$$VS_ISSUER_DIGEST$$&Template=certByIssuer&form_file=../fdf/VSApps/client/userQueryResult.fdf&cert_jurisdiction_hash=%%::jurisdictionHash%%">
<!-- VSSKENDPOLICYVAL#remotehost#16 -->


// for checkLibrary.htm
<!-- VSSKBEGINPOLICYVAL#remotehost#17 -->
<!-- VSSKENDPOLICYVAL#remotehost#17 -->


<!-- VSSKBEGINPOLICYVAL#remotehost#18 -->
       <A HREF="https://%%::vsHost%%/VSApps/digitalidCenter.htm">
<!-- VSSKENDPOLICYVAL#remotehost#18 -->


// for userEnrollMS.htm
<!-- VSSKBEGINPOLICYVAL#remotehost#19#1.2.0.0 -->
  <object
   classid="clsid:127698e4-e730-4e5c-a2b1-21490a70c8a1"
   CODEBASE="https://%%::vsHost%%/VSApps/xenroll.cab"
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
<!-- VSSKENDPOLICYVAL#remotehost#19 -->

// for userRenewalMS.htm
<!-- VSSKBEGINPOLICYVAL#remotehost#20 -->
<object
   classid="clsid:86C4AF33-6171-11D2-80CD-006008B066EE"
   CODEBASE="https://%%::vsHost%%/VSRenewSign.cab">
</object>
<!-- VSSKENDPOLICYVAL#remotehost#20 -->

// for userEnrollMS.fdf and userEnrollNS.fdf
<!-- VSSKBEGINPOLICYVAL#remotehost#21 -->
<!-- VSSKENDPOLICYVAL#remotehost#21 -->


// for userInstallEncMS.htm
<!-- VSSKBEGINPOLICYVAL#remotehost#22#1.0.0.2 -->
<OBJECT
   classid="clsid:B1D475FE-75CD-11D2-8301-0060B0B32E16"
   CODEBASE="https://%%::vsHost%%/VSApps/VSImport.cab#VERSION=2,0,0,5"
   id="Import">
</OBJECT>
<!-- VSSKENDPOLICYVAL#remotehost#22 -->


// for enrollment and renewal fdfs for MSIE
<!-- VSSKBEGINPOLICYVAL#remotehost#23 -->
CONST    application                  VeriSignOnSiteMSIE
<!-- VSSKENDPOLICYVAL#remotehost#23 -->

// for enrollment and renewal fdfs for Firefox
<!-- VSSKBEGINPOLICYVAL#remotehost#24 -->
CONST    application                  VeriSignOnSiteNetscape
<!-- VSSKENDPOLICYVAL#remotehost#24 -->


// for the ms and nspickup.fdf files
<!-- VSSKBEGINPOLICYVAL#remotehost#25 -->
<!-- VSSKENDPOLICYVAL#remotehost#25 -->

// for the WAC pages...VSPref
<!-- VSSKBEGINPOLICYVAL#remotehost#26 -->
<OBJECT
  classid="clsid:70D86F3C-BA4D-11D2-80F5-006008B066EE"
  CODEBASE="https://%%::vsHost%%/vspcakm.cab#VERSION=2,0,0,4"
  id="IVSPrefMgmt"
  style="LEFT: Opx; TOP: Opx; VISIBILITY: hidden"
>
</OBJECT>
<!-- VSSKENDPOLICYVAL#remotehost#26 -->


// for the WAC pages...VSPvkOps
<!-- VSSKBEGINPOLICYVAL#remotehost#27 -->
<OBJECT
classid="clsid:BFDA6775-C868-11D2-8100-006008B066EE"
CODEBASE="https://%%::vsHost%%/vspcakm.cab#VERSION=2,0,0,4"
id="IVSPvkOps"
style="LEFT: Opx; TOP: Opx; VISIBILITY: hidden"
>
</OBJECT>
<!-- VSSKENDPOLICYVAL#remotehost#27 -->


// for the PCA Login pages...
<!-- VSSKBEGINPOLICYVAL#remotehost#28 -->
<FORM METHOD="post" NAME="RenewalForm" ENCTYPE="x-www-form-encoded" ACTION=https://%%::vsHost%%/cgi-bin/softbounce.exe>
<!-- VSSKENDPOLICYVAL#remotehost#28 -->


// for the PCA Login pages...
<!-- VSSKBEGINPOLICYVAL#remotehost#29 -->
   Dim hostName
   hostName = "https://%%::vsHost%%"
<!-- VSSKENDPOLICYVAL#remotehost#29 -->


// for the PCA Login pages...
<!-- VSSKBEGINPOLICYVAL#remotehost#30 -->
   var hostName = "https://%%::vsHost%%";
<!-- VSSKENDPOLICYVAL#remotehost#30 -->


// got the PCA NS Login page...
<!-- VSSKBEGINPOLICYVAL#remotehost#31 -->
        self.location = "https://%%::vsHost%%/VSApps/client/getplugin.htm";
<!-- VSSKENDPOLICYVAL#remotehost#31 -->

// temporary fragment to solve the certDN bug in exchange integration
<!-- VSSKBEGINPOLICYVAL#remotehost#32 -->
    certDN="cn=" & Chr(34) & Trunc & Chr(34) & "," & certDN
<!-- VSSKENDPOLICYVAL#remotehost#32 -->


//-- fragment for AddRootCerts Interface...
<!-- VSSKBEGINPOLICYVAL#remotehost#33#1.0.0.8 -->
<OBJECT
   classid="clsid:50E71FEB-2234-11d4-8D73-0060B0FC0637"
   CODEBASE="https://%%::vsHost%%/VSApps/vspta3.cab#VERSION=2,1,0,9"
   id="ObjectIAddRootCerts"
   style="LEFT: Opx; TOP: Opx; VISIBILITY: hidden"
>
</OBJECT>
<!-- VSSKENDPOLICYVAL#remotehost#33 -->

// temporary fragment to solve the certDN bug in exchange integration
<!-- VSSKBEGINPOLICYVAL#remotehost#34 -->
    certDN="cn=" + "\"" + Trunc + "\"" + "," + certDN ;
<!-- VSSKENDPOLICYVAL#remotehost#34 -->

// for the PCA  pages...
<!-- VSSKBEGINPOLICYVAL#remotehost#35 -->
   Dim helpHostName
   helpHostName = "https://%%::vsHost%%"
<!-- VSSKENDPOLICYVAL#remotehost#35 -->


// for the PCA pages...
<!-- VSSKBEGINPOLICYVAL#remotehost#36 -->
   var helpHostName = "https://%%::vsHost%%";
<!-- VSSKENDPOLICYVAL#remotehost#36 -->

<!-- VSSKBEGINPOLICYVAL#remotehost#37 -->
    document.proform.exchange_DN.value = distinguishedName ;
<!-- VSSKENDPOLICYVAL#remotehost#37 -->

<!-- VSSKBEGINPOLICYVAL#remotehost#38 -->
    document.proform.cert_DN.value = certDN ;
<!-- VSSKENDPOLICYVAL#remotehost#38 -->

<!-- VSSKBEGINPOLICYVAL#remotehost#39 -->
<OBJECT
   classid="clsid:5CBAA8E0-234B-11D3-AE02-0060B0C4A3BC"
   CODEBASE="https://%%::vsHost%%/vsexports.cab#VERSION=2,1,0,3"
   id="Exports"
   style="LEFT: Opx; TOP: Opx; VISIBILITY: hidden"
>
</OBJECT>
<!-- VSSKENDPOLICYVAL#remotehost#39 -->

<!-- VSSKBEGINPOLICYVAL#remotehost#40 -->
<SCRIPT Language="JavaScript">

if ( navigator.javaEnabled() ) {

   trigger = netscape.softupdate.Trigger;
   if ( trigger.UpdateEnabled() ) {

      if (navigator.platform == "Win32") {
         vi = new netscape.softupdate.VersionInfo(1, 0, 0, 3);
         trigger.ConditionalSoftwareUpdate(
            "https://%%::vsHost%%/vsnp.jar",
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
<!-- VSSKENDPOLICYVAL#remotehost#40 -->

<!-- VSSKBEGINPOLICYVAL#remotehost#41#1.2.0.9 -->
  <object
   classid="clsid:5685505C-DA94-11D3-A1C3-001083023D07"
   CODEBASE="https://%%::vsHost%%/VSApps/VSGSE.cab#VERSION=2,6,0,3"
   id="IGSE"
  >
  </object>
<!-- VSSKENDPOLICYVAL#remotehost#41 -->

<!-- VSSKBEGINPOLICYVAL#remotehost#42 -->
            Document.proform.exchange_DN.value = distinguishedName
<!-- VSSKENDPOLICYVAL#remotehost#42 -->

<!-- VSSKBEGINPOLICYVAL#remotehost#43 -->
            Document.proform.cert_DN.value = certDN
<!-- VSSKENDPOLICYVAL#remotehost#43 -->

<!-- VSSKBEGINPOLICYVAL#remotehost#44 -->
<!-- VSSKBEGIN Enrollment/CharEncoding#3 -->
<!-- VSSKEND Enrollment/CharEncoding#3 -->
<!-- VSSKENDPOLICYVAL#remotehost#44 -->

<!-- VSSKBEGINPOLICYVAL#remotehost#101#1.0.0.8 -->
<OBJECT
  classid="clsid:6F7864F9-DB33-11D3-8166-0060B0F885E6"
  CODEBASE="https://%%::vsHost%%/VSApps/vspta3.cab#VERSION=2,1,0,9"
  id="IVSPTA"
  style="LEFT: Opx; TOP: Opx; VISIBILITY: hidden"
>
</OBJECT>
<!-- VSSKENDPOLICYVAL#remotehost#101 -->

// got the PCA NS Login page...
<!-- VSSKBEGINPOLICYVAL#remotehost#102#1.2.0.5 -->
	if(browserNum < 5){
        self.location = "https://%%::vsHost%%/VSApps/client/getplugin.htm";
    } else {
		self.location = "https://%%::vsHost%%/VSApps/error/PTAUnsupportedBrowser.htm";
    }
<!-- VSSKENDPOLICYVAL#remotehost#102 -->

// error reporting for login and transaction pages
<!-- VSSKBEGINPOLICYVAL#remotehost#103 -->
<FORM NAME=ErrorForm ACTION="https://%%::vsHost%%/cgi-bin/softbounce.exe" METHOD=POST>
<!-- VSSKENDPOLICYVAL#remotehost#103 -->

<!-- VSSKBEGINPOLICYVAL#remotehost#104 -->
         Result = trigger.ConditionalSoftwareUpdate(
            "https://%%::vsHost%%/VSApps/vspta3km.jar",
             "plugins/verisign/vspta",
             vi, trigger.DEFAULT_MODE);
<!-- VSSKENDPOLICYVAL#remotehost#104 -->

<!-- VSSKBEGINPOLICYVAL#remotehost#105 -->
        Result =  trigger.ConditionalSoftwareUpdate(
            "https://%%::vsHost%%/VSApps/vspta3.jar",
            "plugins/verisign/vspta",
             vi, trigger.DEFAULT_MODE);
<!-- VSSKENDPOLICYVAL#remotehost#105 -->

<!-- VSSKBEGINPOLICYVAL#remotehost#106 -->
<OBJECT
   classid="clsid:71C6919E-F9C0-11D2-8344-0060B0B32E16"
   codeBase="https://%%::vsHost%%/VSApps/VSSgnAtb.cab#VERSION=2,0,0,8"
   id="ISignAtrb">
</OBJECT>
<!-- VSSKENDPOLICYVAL#remotehost#106 -->

<!-- VSSKBEGINPOLICYVAL#remotehost#107#1.0.0.2 -->
<OBJECT
   classid="clsid:6C67604E-91A2-11D3-8C1B-0010830169AF"
   codeBase="https://%%::vsHost%%/VSApps/vsfe.cab#VERSION=1,0,1,1"
   id="vsctl">
</OBJECT>

<!-- include the PTA control -->
<OBJECT
  classid="clsid:6F7864F9-DB33-11D3-8166-0060B0F885E6"
  CODEBASE="https://%%::vsHost%%/VSApps/vsfe.cab#VERSION=1,0,2,7">
</OBJECT>

<SCript Language="JavaScript">
<!--
    self.location = "../error/fet_wrongmode.htm";
//-->
</Script>
<!-- VSSKENDPOLICYVAL#remotehost#107 -->

//-- include the PTA control/plugin on the PTA logout page 
<!-- VSSKBEGINPOLICYVAL#remotehost#108#1.2.1.1 -->
<script Language="JavaScript">
<!--
if (navigator.appName == "Netscape")
{ document.write("<EMBED type='application/x-vspta2-plugin' name='ThePlugin' WIDTH=0 HEIGHT=0 HIDDEN>"); }
else
{ document.write("<OBJECT classid='clsid:6F7864F9-DB33-11D3-8166-0060B0F885E6' CODEBASE='https://%%::vsHost%%/VSApps/vspta3.cab#VERSION=2,1,0,9' id='IVSPTA' style='LEFT: Opx; TOP: Opx; VISIBILITY: hidden'></OBJECT>");}
//-->
</script>
<!-- VSSKENDPOLICYVAL#remotehost#108 -->

<!-- VSSKBEGINPOLICYVAL#remotehost#109 -->
  
window.navigate("https://%%::vsHost%%/cgi-bin/softbounce.exe?form_file=../fdf/VSApps/client/ExchangeErrors.fdf&errorCode=10000000&operation=Enrollment Status&showError=")

<!-- VSSKENDPOLICYVAL#remotehost#109 -->

<!-- VSSKBEGINPOLICYVAL#remotehost#110 -->
<input TYPE=hidden NAME=Enroll_operation VALUE="C1LRAUserSubmit">
<input TYPE=hidden NAME=CertRqstPostURL VALUE="https://%%::vsHost%%/cgi-bin/sophia.exe">
<!-- VSSKENDPOLICYVAL#remotehost#110 -->

<!-- VSSKBEGINPOLICYVAL#remotehost#111 -->
<input type="hidden" name="ReturnURL" value="https://%%::vsHost%%/VSApps/client/userInstallSuccess.htm">
<!-- VSSKENDPOLICYVAL#remotehost#111 -->

<!-- VSSKBEGINPOLICYVAL#remotehost#112#1.0.0.2 -->
<input type="hidden" name="ReturnURL" value="https://%%::vsHost%%/VSApps/client/changePasswdSuccess.htm">
<!-- VSSKENDPOLICYVAL#remotehost#112 -->

<!-- VSSKBEGINPOLICYVAL#remotehost#113 -->
<input type="hidden" name="CancelURL" value="https://%%::vsHost%%/VSApps/client/ptsCancel.htm">
<!-- VSSKENDPOLICYVAL#remotehost#113 -->

<!-- VSSKBEGINPOLICYVAL#remotehost#114#1.0.0.2 -->
<!-- include the PTA control -->
<OBJECT
   classid="clsid:D66256E2-B99C-11D4-8C74-0010830169AF"
   codeBase="https://%%::vsHost%%/VSApps/vsnzpta.cab#VERSION=1,0,0,3"
   id="IVSNZ"
>
</OBJECT>

<OBJECT
  classid="clsid:6F7864F9-DB33-11D3-8166-0060B0F885E6"
  CODEBASE="https://%%::vsHost%%/VSApps/vsnzpta.cab#VERSION=1,0,2,7"
>
</OBJECT>
<!-- VSSKENDPOLICYVAL#remotehost#114 -->

<!-- VSSKBEGINPOLICYVAL#remotehost#115 -->
	if(browserNum < 5){
        self.location = "https://%%::vsHost%%/VSApps/client/getnzptaplugin.htm";
    } else {
		self.location = "https://%%::vsHost%%/VSApps/client/getnzptaplugin6.htm";
    }
<!-- VSSKENDPOLICYVAL#remotehost#115 -->

<!-- VSSKBEGINPOLICYVAL#remotehost#116 -->
   Result = trigger.ConditionalSoftwareUpdate(
            "https://%%::vsHost%%/VSApps/vsnzpta.jar",
            "verisign/vspta", vi, trigger.DEFAULT_MODE);
<!-- VSSKENDPOLICYVAL#remotehost#116 -->

<!-- VSSKBEGINPOLICYVAL#remotehost#117 -->
   Result = trigger.ConditionalSoftwareUpdate(
            "https://%%::vsHost%%/VSApps/vsdnotz.jar",
            "verisign/vsdnotz", vi, trigger.DEFAULT_MODE);
<!-- VSSKENDPOLICYVAL#remotehost#117 -->

<!-- VSSKBEGINPOLICYVAL#remotehost#118 -->
<input type="hidden" name="CertRenewPostURL" value="https://%%::vsHost%%/cgi-bin/sophia.exe">
<!-- VSSKENDPOLICYVAL#remotehost#118 -->

<!-- VSSKBEGINPOLICYVAL#remotehost#119 -->
<INPUT type="hidden" name="ErrorPage.ReturnUrl" value="https://%%::vsHost%%/VSApps/digitalidCenter.htm">
<!-- VSSKENDPOLICYVAL#remotehost#119 -->

<!-- VSSKBEGINPOLICYVAL#remotehost#120#1.0.0.0 -->

<OBJECT
    classid="clsid:8AD9C840-044E-11D1-B3E9-00805F499D93"
    WIDTH = 640 HEIGHT = 400 NAME = "PtaApplet"
    STANDBY="Please wait as the applet is being loaded..."
    codebase="http://java.sun.com/products/plugin/autodl/jinstall-1_4_1-windows-i586.cab#Version=1,4,1,mn">
    <PARAM NAME = CODE VALUE = "com.verisign.pta.applet.PtaApplet" >
	<PARAM NAME = CODEBASE VALUE = "https://%%::vsHost%%/VSApps" >
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
            CODEBASE = "https://%%::vsHost%%/VSApps"
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

<!-- VSSKENDPOLICYVAL#remotehost#120 -->

// for javapta Login pages...
<!-- VSSKBEGINPOLICYVAL#remotehost#121 -->
   hostName = "https://%%::vsHost%%"
<!-- VSSKENDPOLICYVAL#remotehost#121 -->

<!-- VSSKBEGINPOLICYVAL#remotehost#122 -->
  if(browserNum >= 5){
	self.location = "https://%%::vsHost%%/VSApps/error/PTAUnsupportedBrowser.htm";
  }
<!-- VSSKENDPOLICYVAL#remotehost#122 -->

<!-- VSSKBEGINPOLICYVAL#remotehost#123 -->
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
<!-- VSSKENDPOLICYVAL#remotehost#123 -->

<!-- VSSKBEGINPOLICYVAL#remotehost#124 -->
try{
	dummy=ConfChk.getName();
	temp = 1;
}catch(er){
	temp=0;
	window.open("../vsapps/error/win2k.htm","_self");
}
<!-- VSSKENDPOLICYVAL#remotehost#124 -->

<!-- VSSKBEGINPOLICYVAL#remotehost#125#1.0.0.6 -->
document.write('<OBJECT');
document.write('  classid="clsid:6F7864F9-DB33-11D3-8166-0060B0F885E6"');
document.write('  CODEBASE="%%::remoteHost%%/VSApps/vspta3.cab#VERSION=2,1,0,9"');
document.write('  id="IVSPTA"');
document.write('  style="LEFT: Opx; TOP: Opx; VISIBILITY: hidden"');
document.write('>');
document.write('</OBJECT>');
<!-- VSSKENDPOLICYVAL#remotehost#125 -->

<!-- VSSKBEGINPOLICYVAL#remotehost#126 -->
<!-- VSSKENDPOLICYVAL#remotehost#126 -->

<!-- VSSKBEGINPOLICYVAL#remotehost#127#1.2.0.7 -->
document.write('<OBJECT');
document.write('   classid="clsid:5685505C-DA94-11D3-A1C3-001083023D07"');
document.write('   CODEBASE="%%::remoteHost%%/VSApps/VSGSE.cab#VERSION=2,6,0,3"');
document.write('   id="IGSE"');
document.write('	style="VISIBILITY: hidden" >');
document.write('</OBJECT>');
<!-- VSSKENDPOLICYVAL#remotehost#127 -->

<!-- VSSKBEGINPOLICYVAL#remotehost#128#1.0.0.1 -->
document.write('<OBJECT');
document.write('   classid="clsid:B1D475FE-75CD-11D2-8301-0060B0B32E16"');
document.write('   CODEBASE="%%::remoteHost%%/VSApps/VSImport.cab#VERSION=2,0,0,5"');
document.write('   id="Import"');
document.write('   style="LEFT: Opx; TOP: Opx; VISIBILITY: hidden"');
document.write('>');
document.write('</OBJECT>');
<!-- VSSKENDPOLICYVAL#remotehost#128 -->

<!-- VSSKBEGINPOLICYVAL#remotehost#129 -->
document.write('<OBJECT');
document.write('   classid="clsid:71C6919E-F9C0-11D2-8344-0060B0B32E16"');
document.write('   codeBase="%%::remoteHost%%/VSApps/VSSgnAtb.cab#VERSION=2,0,0,8"');
document.write('   id="ISignAtrb"');
document.write('   style="VISIBILITY: hidden">');
document.write('</OBJECT>');
<!-- VSSKENDPOLICYVAL#remotehost#129 -->

<!-- VSSKBEGINPOLICYVAL#remotehost#130#1.0.0.1 -->
<script src="https://%%::vsHost%%/VSApps/client/createObject.js" language="JavaScript"></script>
<!-- VSSKENDPOLICYVAL#remotehost#130 -->

<!-- VSSKBEGINPOLICYVAL#remotehost#131 -->
<script language="JavaScript"> createJavaPluginObject();</script>
<!-- VSSKENDPOLICYVAL#remotehost#131 -->
