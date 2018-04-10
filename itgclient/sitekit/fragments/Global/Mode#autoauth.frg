// for MSIE autoauth enrollment
<!-- VSSKBEGINPOLICYVAL#autoauth#1 -->
<form NAME="proform" ACTION=../../cgi-bin/softbounce.exe ENCTYPE=x-www-form-encoded METHOD="POST">
<input TYPE=hidden NAME=operation VALUE="AutoAuthOSUserSubmit">
<input TYPE=hidden NAME=authenticate VALUE="NO">
<input TYPE=hidden NAME=VHTML_FILE VALUE="../htmldocs/VSApps/client/enroll_wait.htm">
<!--
<INPUT TYPE=hidden NAME=remote_host VALUE="%%::remoteHost%%/cgi-bin/haydn.exe">
-->
<!-- VSSKENDPOLICYVAL#autoauth#1 -->


// for firefox autoauth enrollment
<!-- VSSKBEGINPOLICYVAL#autoauth#2 -->
<form NAME="proform" ACTION=../../cgi-bin/softbounce.exe ENCTYPE=x-www-form-encoded METHOD=POST>
<input TYPE=hidden NAME=operation VALUE="AutoAuthOSUserSubmit">
<input TYPE=hidden NAME=authenticate VALUE="NO">
<input TYPE=hidden NAME=VHTML_FILE VALUE="../htmldocs/VSApps/client/enroll_wait.htm">
<!--
<INPUT TYPE=hidden NAME=remote_host VALUE="%%::remoteHost%%/cgi-bin/haydn.exe">
-->
<!-- VSSKENDPOLICYVAL#autoauth#2 -->


// from revoke_start.htm
<!-- VSSKBEGINPOLICYVAL#autoauth#3#1.2.5.2 -->
<FORM NAME=form3 METHOD=POST ACTION="../cgi-bin/sophialite.exe" onsubmit="assignIssuerDN2()">
<INPUT TYPE=hidden NAME=form_file VALUE="../fdf/VSApps/client/userRevokeAA.fdf">
<INPUT TYPE=hidden NAME=certSerial VALUE=$$vs_cert_serial$$>
<INPUT TYPE=hidden NAME=issuerDigest VALUE=$$vs_issuer_digest$$>
<INPUT TYPE=hidden NAME=issuerName2 value="">

<TABLE WIDTH=588 CELLPADDING=2 CELLSPACING=0 BORDER=0>
<TR>
<TD WIDTH=588 BGCOLOR="#cccccc">
<FONT SIZE=2 FACE="verdana, arial, helvetica"><B>Revoke your own digital certificate:</FONT><P>
<CENTER>
<TABLE WIDTH=574 CELLPADDING=3 CELLSPACING=2 BORDER=0> 
<TR>
<TD WIDTH=50% BGCOLOR="#ffffcc" VALIGN=TOP><FONT SIZE=2 FACE="verdana, arial, helvetica">
<B>Enter the challenge phrase:</B><BR></FONT></TD> 
<TD WIDTH=50% BGCOLOR="#ffffcc"><INPUT Name=challenge TYPE=PASSWORD value="" size=32 maxlength=32></TD> 
</TR>
<TR>
<TD WIDTH=50% BGCOLOR="#ffffcc" VALIGN=TOP><FONT SIZE=2 FACE="verdana, arial, helvetica">
<B>Select reason:</B><BR></FONT><font size=2 face="arial, helvetica"></FONT></TD> 
<TD WIDTH=50% BGCOLOR="#ffffcc"><SELECT NAME=reason><option selected> Key compromise
<option> CA compromise
<option> Affiliation changed
<option> Superseded
<option> Cessation of operation
<option> Certificate hold
<option> Privilege withdrawn
<option> AA compromise
<option> Unspecified</select>
</TD> 
</TR>  
</TABLE>
</TR>
<TR>
<TD ALIGN=RIGHT><INPUT type="image" IMG SRC="../VSApps/graphics/button_revoke_green.gif" border=0 ></TD>  
</TR>
</TABLE>
</FORM>
<!-- VSSKENDPOLICYVAL#autoauth#3 -->



// from revoke.htm
<!-- VSSKBEGINPOLICYVAL#autoauth#4#1.0.0.2 -->
<P><BR><P>
<FORM NAME=form3 METHOD=POST ACTION="../../cgi-bin/sophialite.exe">
<INPUT TYPE=hidden NAME=form_file VALUE="../fdf/VSApps/client/userRevokeAA.fdf">

<TABLE WIDTH=588 CELLPADDING=2 CELLSPACING=0 BORDER=0>
<TR>
    <TD WIDTH=588 BGCOLOR="#cccccc">
    <FONT SIZE=2 FACE="verdana, arial, helvetica"><B>Revoke your own digital certificate:</FONT><P>
    <CENTER>

     <TABLE WIDTH=574 CELLPADDING=3 CELLSPACING=2 BORDER=0> 
     <TR>
         <TD WIDTH=50% BGCOLOR="#ffffcc" VALIGN=TOP><FONT SIZE=2 FACE="verdana, arial, helvetica">
         <B>Enter the ID&#146;s serial number:</B><BR></FONT></TD> 

         <TD WIDTH=50% BGCOLOR="#ffffcc"><INPUT Name=certSerial value="" size=32 maxlength=32></TD> 
     </TR>

     <TR>
         <TD WIDTH=50% BGCOLOR="#ffffcc" VALIGN=TOP><FONT SIZE=2 FACE="verdana, arial, helvetica">
         <B>Enter the challenge phrase:</B><BR></FONT></TD> 

         <TD WIDTH=50% BGCOLOR="#ffffcc"><INPUT Name=challenge TYPE=PASSWORD value="" size=32 maxlength=32></TD> 
     </TR>

     <TR>
         <TD WIDTH=50% BGCOLOR="#ffffcc" VALIGN=TOP><FONT SIZE=2 FACE="verdana, arial, helvetica">
         <B>Select reason:</B><BR></FONT><font size=2 face="arial, helvetica"></FONT></TD> 

         <TD WIDTH=50% BGCOLOR="#ffffcc"><SELECT NAME=reason><option selected> Key compromise
                                                             <option> CA compromise
                                                             <option> Affiliation changed
                                                             <option> Superseded
                                                             <option> Cessation of operation
                                                             <option> Certificate hold
                                                             <option> Privilege withdrawn
                                                             <option> AA compromise
                                                             <option> Unspecified</select>
        </TD> 
    </TR>  
    </TABLE>
</TR>

<TR>
    <TD ALIGN=RIGHT><INPUT type="image" IMG SRC="../graphics/button_revoke_green.gif" border=0 ></TD>  
</TR>
</TABLE>
</FORM>
<!-- VSSKENDPOLICYVAL#autoauth#4 -->


// form parameters for userEnrollCSR.htm
<!-- VSSKBEGINPOLICYVAL#autoauth#5 -->
<FORM ENCTYPE="multipart/form-data" ACTION = "https://%%::vsHost%%/cgi-bin/upload.exe" METHOD=POST>
<INPUT TYPE=hidden NAME=remote_host VALUE="%%::remoteHost%%/cgi-bin/haydn.exe">
<!-- VSSKENDPOLICYVAL#autoauth#5 -->

// form parameters for userEnrollCSRMain.htm
<!-- VSSKBEGINPOLICYVAL#autoauth#6 -->
<form NAME="proform" ACTION="https://%%::vsHost%%/cgi-bin/sophia.exe" ENCTYPE=x-www-form-encoded METHOD=POST onsubmit="return lastCheck()">
<input TYPE=hidden NAME=operation VALUE="C1LRAUserSubmit">
<!--
<input TYPE=hidden NAME=operation VALUE="AutoAuthOSUserSubmit">
<input TYPE=hidden NAME=authenticate VALUE="NO">
<input TYPE=hidden NAME=VHTML_FILE VALUE="../htmldocs/VSApps/client/enroll_wait.htm">
-->
<INPUT TYPE=hidden NAME=remote_host VALUE="%%::remoteHost%%/cgi-bin/haydn.exe">
<!-- VSSKENDPOLICYVAL#autoauth#6 -->

// for the MS and NS pickup files: mspickup.htm and nspickup.htm
<!-- VSSKBEGINPOLICYVAL#autoauth#7 -->
<FORM NAME="proform" METHOD="POST" ACTION="../../cgi-bin/sophialite.exe">
<!-- VSSKENDPOLICYVAL#autoauth#7 -->

// for the revoke files: revoke.htm, 
// and query files:noCertFound.htm, search.htm 
<!-- VSSKBEGINPOLICYVAL#autoauth#8 -->
<FORM NAME=form1 METHOD=POST ACTION="https://%%::vsHost%%/cgi-bin/Xquery.exe">
<INPUT TYPE=hidden NAME=remote_host VALUE="%%::remoteHost%%/cgi-bin/haydn.exe">
<!-- VSSKENDPOLICYVAL#autoauth#8 -->

// for the revoke files: revoke.htm, 
// and query files: noCertFound.htm, search.htm
<!-- VSSKBEGINPOLICYVAL#autoauth#9 -->
<FORM NAME=form2 METHOD=POST ACTION="https://%%::vsHost%%/cgi-bin/Xquery.exe">
<INPUT TYPE=hidden NAME=remote_host VALUE="%%::remoteHost%%/cgi-bin/haydn.exe">
<!-- VSSKENDPOLICYVAL#autoauth#9 -->

// for the revoke files: revokeConfirm.htm
<!-- VSSKBEGINPOLICYVAL#autoauth#10 -->
<FORM METHOD=POST ACTION="https://%%::vsHost%%/cgi-bin/Xquery.exe">
<!-- VSSKENDPOLICYVAL#autoauth#10 -->

// for query files: userQueryResult.htm
<!-- VSSKBEGINPOLICYVAL#autoauth#11 -->
        <FORM NAME="prevpage" METHOD=POST ACTION=https://%%::vsHost%%/cgi-bin/Xquery.exe>
        <INPUT TYPE=hidden NAME=remote_host VALUE="%%::remoteHost%%/cgi-bin/haydn.exe">
<!-- VSSKENDPOLICYVAL#autoauth#11 -->

// for the query files: userQueryResult.htm
<!-- VSSKBEGINPOLICYVAL#autoauth#12 -->
        <FORM NAME="nextpage" METHOD=POST ACTION=https://%%::vsHost%%/cgi-bin/Xquery.exe>
        <INPUT TYPE=hidden NAME=remote_host VALUE="%%::remoteHost%%/cgi-bin/haydn.exe">
<!-- VSSKENDPOLICYVAL#autoauth#12 -->

// for the download files, download.htm
<!-- VSSKBEGINPOLICYVAL#autoauth#13 -->
<FORM Name=form0 METHOD=POST ACTION=https://%%::vsHost%%/cgi-bin/sophia.exe>
<INPUT TYPE=hidden NAME=remote_host VALUE="%%::remoteHost%%/cgi-bin/haydn.exe">
<!-- VSSKENDPOLICYVAL#autoauth#13 -->

//for the firefox renewal file userRenewalNS.htm
<!-- VSSKBEGINPOLICYVAL#autoauth#14 -->
<FORM METHOD="POST" NAME="Renewal" ACTION="%%::remoteHost%%/cgi-bin/sophialite.exe" enctype="x-www-form-encoded">
<!-- VSSKENDPOLICYVAL#autoauth#14 -->


//for the MSIE renewal file userRenewalMS.htm
<!-- VSSKBEGINPOLICYVAL#autoauth#15 -->
<FORM METHOD=POST NAME="theform" ACTION="%%::remoteHost%%/cgi-bin/sophialite.exe">
<!-- VSSKENDPOLICYVAL#autoauth#15 -->

// for userQueryResult.htm
<!-- VSSKBEGINPOLICYVAL#autoauth#16 -->
<a href="https://%%::vsHost%%/cgi-bin/Xquery.exe?vs_issuer_digest=$$VS_ISSUER_DIGEST$$&remote_host=%%::remoteHost%%/cgi-bin/haydn.exe&Template=certByIssuer&form_file=../fdf/VSApps/client/userQueryResult.fdf&cert_jurisdiction_hash=%%::jurisdictionHash%%">
<!-- VSSKENDPOLICYVAL#autoauth#16 -->

// for checkLibrary.htm
<!-- VSSKBEGINPOLICYVAL#autoauth#17 -->
<!-- VSSKENDPOLICYVAL#autoauth#17 -->

// for the navigation buttons in the various files 
<!-- VSSKBEGINPOLICYVAL#autoauth#18 -->
       <A HREF="%%::remoteHost%%/VSApps/digitalidCenter.htm">
<!-- VSSKENDPOLICYVAL#autoauth#18 -->


// for userEnrollMS.htm
<!-- VSSKBEGINPOLICYVAL#autoauth#19#1.2.0.0 -->
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

<!-- VSSKENDPOLICYVAL#autoauth#19 -->

 
// for userRenewalMS.htm
<!-- VSSKBEGINPOLICYVAL#autoauth#20 -->
<object
   classid="clsid:86C4AF33-6171-11D2-80CD-006008B066EE"
   CODEBASE="%%::remoteHost%%/VSRenewSign.cab">
</object>
<!-- VSSKENDPOLICYVAL#autoauth#20 -->


// for userEnrollMS.fdf and userEnrollNS.fdf
<!-- VSSKBEGINPOLICYVAL#autoauth#21 -->
#
# AA section
#
# if key manager is used vsenroll_url should not be passed
# VSSKBEGIN Apps/KeyManager#9 
# VSSKEND Apps/KeyManager#9
#
#  NAME         CODE    VALUE     
#------------------------------------------------------------------------------
#

authenticate	TEXT	OPTIONAL	NONE	NONE
user_data_1	CLEAR	OPTIONAL	NONE	NONE
user_data_2	CLEAR	OPTIONAL	NONE	NONE
user_data_3	CLEAR	OPTIONAL	NONE	NONE
user_data_4	CLEAR	OPTIONAL	NONE	NONE
user_data_5	CLEAR	OPTIONAL	NONE	NONE
#
<!-- VSSKENDPOLICYVAL#autoauth#21 -->


// for userInstallEncMS.htm
<!-- VSSKBEGINPOLICYVAL#autoauth#22#1.0.0.1 -->
<OBJECT
   classid="clsid:B1D475FE-75CD-11D2-8301-0060B0B32E16"
   CODEBASE="%%::remoteHost%%/VSApps/VSImport.cab#VERSION=2,0,0,5"
   id="Import">
</OBJECT>
<!-- VSSKENDPOLICYVAL#autoauth#22 -->


// for enrollment and renewal fdfs for MSIE
<!-- VSSKBEGINPOLICYVAL#autoauth#23 -->
CONST    application                  VeriSignOnSiteCRS
<!-- VSSKENDPOLICYVAL#autoauth#23 -->

// for enrollment and renewal fdfs for Firefox 
<!-- VSSKBEGINPOLICYVAL#autoauth#24 -->
CONST    application                  VeriSignOnSiteCRS
<!-- VSSKENDPOLICYVAL#autoauth#24 -->

// for the ms and nspickup.fdf files
<!-- VSSKBEGINPOLICYVAL#autoauth#25 -->
CONST vsenroll_url   %%::crsUrl%%
CONST issuerName     OU=GetCert,O=VSAA
CONST padding        YES
<!-- VSSKENDPOLICYVAL#autoauth#25 -->


// for the WAC pages...for VSPref
<!-- VSSKBEGINPOLICYVAL#autoauth#26 -->
<OBJECT
  classid="clsid:70D86F3C-BA4D-11D2-80F5-006008B066EE"
  CODEBASE="%%::remoteHost%%/vspcakm.cab#VERSION=2,0,0,4"
  id="IVSPrefMgmt"
  style="LEFT: Opx; TOP: Opx; VISIBILITY: hidden"
>
</OBJECT>
<!-- VSSKENDPOLICYVAL#autoauth#26 -->


// for the WAC pages...for VsPvkOps
<!-- VSSKBEGINPOLICYVAL#autoauth#27 -->
<OBJECT
classid="clsid:BFDA6775-C868-11D2-8100-006008B066EE"
CODEBASE="%%::remoteHost%%/vspcakm.cab#VERSION=2,0,0,4"
id="IVSPvkOps"
style="LEFT: Opx; TOP: Opx; VISIBILITY: hidden"
>
</OBJECT>
<!-- VSSKENDPOLICYVAL#autoauth#27 -->


<!-- VSSKBEGINPOLICYVAL#autoauth#28 -->
<FORM METHOD="post" NAME="RenewalForm" ENCTYPE="x-www-form-encoded" ACTION=%%::remoteHost%%/cgi-bin/softbounce.exe>
<!-- VSSKENDPOLICYVAL#autoauth#28 -->

// for the PCA Login MS pages...
<!-- VSSKBEGINPOLICYVAL#autoauth#29 -->
   Dim hostName
   hostName = "%%::remoteHost%%"
<!-- VSSKENDPOLICYVAL#autoauth#29 -->

// for the PCA Login NS pages...
<!-- VSSKBEGINPOLICYVAL#autoauth#30 -->
   var hostName = "%%::remoteHost%%";
<!-- VSSKENDPOLICYVAL#autoauth#30 -->

// got the PCA NS Login page...
<!-- VSSKBEGINPOLICYVAL#autoauth#31 -->
        self.location = "%%::remoteHost%%/VSApps/client/getplugin.htm";
<!-- VSSKENDPOLICYVAL#autoauth#31 -->

// temporary fragment to solve the certDN bug in exchange integration
<!-- VSSKBEGINPOLICYVAL#autoauth#32 -->
    certDN="cn=" & "&#34; " & Trunc & "&#34;" & "," & certDN
<!-- VSSKENDPOLICYVAL#autoauth#32 -->

<!-- VSSKBEGINPOLICYVAL#autoauth#33#1.0.0.6 -->
<OBJECT
   classid="clsid:50E71FEB-2234-11d4-8D73-0060B0FC0637"
   CODEBASE="%%::remoteHost%%/VSApps/vspta3.cab#VERSION=2,1,0,9"
   id="ObjectIAddRootCerts"
   style="LEFT: Opx; TOP: Opx; VISIBILITY: hidden"
>
</OBJECT>
<!-- VSSKENDPOLICYVAL#autoauth#33 -->

// temporary fragment to solve the certDN bug in exchange integration
<!-- VSSKBEGINPOLICYVAL#autoauth#34 -->
    certDN="cn=" + "&#34;" + Trunc + "&#34;" + "," + certDN ;
<!-- VSSKENDPOLICYVAL#autoauth#34 -->


// for the PCA MS pages...
<!-- VSSKBEGINPOLICYVAL#autoauth#35 -->
   Dim helpHostName
   helpHostName = "%%::remoteHost%%"
<!-- VSSKENDPOLICYVAL#autoauth#35 -->

// for the PCA NS pages...
<!-- VSSKBEGINPOLICYVAL#autoauth#36 -->
   var helpHostName = "%%::remoteHost%%";
<!-- VSSKENDPOLICYVAL#autoauth#36 -->

<!-- VSSKBEGINPOLICYVAL#autoauth#37 -->
    var outputDN ;
    var re = /"/g ;
    inputDN = distinguishedName ;
    outputDN = inputDN.replace(re, "&#34;&#34;") ;

    document.proform.exchange_DN.value = outputDN ;
<!-- VSSKENDPOLICYVAL#autoauth#37 -->

<!-- VSSKBEGINPOLICYVAL#autoauth#38 -->
    inputDN = certDN ;
    outputDN = inputDN.replace(re, "&#34;") ;

    document.proform.cert_DN.value = outputDN ;
<!-- VSSKENDPOLICYVAL#autoauth#38 -->

<!-- VSSKBEGINPOLICYVAL#autoauth#39 -->
<OBJECT
   classid="clsid:5CBAA8E0-234B-11D3-AE02-0060B0C4A3BC"
   CODEBASE="%%::remoteHost%%/vsexports.cab#VERSION=2,1,0,3"
   id="Exports"
   style="LEFT: Opx; TOP: Opx; VISIBILITY: hidden"
>
</OBJECT>
<!-- VSSKENDPOLICYVAL#autoauth#39 -->

<!-- VSSKBEGINPOLICYVAL#autoauth#40 -->
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
<!-- VSSKENDPOLICYVAL#autoauth#40 -->

<!-- VSSKBEGINPOLICYVAL#autoauth#41#1.2.0.9 -->
  <object
   classid="clsid:5685505C-DA94-11D3-A1C3-001083023D07"
   CODEBASE="%%::remoteHost%%/VSApps/VSGSE.cab#VERSION=2,6,0,3"
   id="IGSE"
  >
  </object>
<!-- VSSKENDPOLICYVAL#autoauth#41 -->

<!-- VSSKBEGINPOLICYVAL#autoauth#42 -->
            tmpDN = ""
            For i = 1 to Len(distinguishedName)
              If Mid(distinguishedName,i,1) = """" then
                tmpDN = tmpDN & "&#34;&#34;"
              Else
                tmpDN = tmpDN & Mid(distinguishedName,i,1)
              End If 
            Next
            Document.proform.exchange_DN.value = tmpDN
<!-- VSSKENDPOLICYVAL#autoauth#42 -->

<!-- VSSKBEGINPOLICYVAL#autoauth#43 -->
            tmpDN = ""
            For i = 1 to Len(certDN)
              If Mid(certDN,i,1) = """" then
                tmpDN = tmpDN & "&#34;"
              Else
                tmpDN = tmpDN & Mid(certDN,i,1)
              End If 
            Next
            Document.proform.cert_DN.value = tmpDN
<!-- VSSKENDPOLICYVAL#autoauth#43 -->

<!-- VSSKBEGINPOLICYVAL#autoauth#44 -->
<META HTTP-EQUIV="Content-Type" CONTENT="text/html; charset=UTF-8">
<!-- VSSKENDPOLICYVAL#autoauth#44 -->

<!-- VSSKBEGINPOLICYVAL#autoauth#101#1.0.0.8 -->
<OBJECT
  classid="clsid:6F7864F9-DB33-11D3-8166-0060B0F885E6"
  CODEBASE="%%::remoteHost%%/VSApps/vspta3.cab#VERSION=2,1,0,9"
  id="IVSPTA"
  style="LEFT: Opx; TOP: Opx; VISIBILITY: hidden"
>
</OBJECT>
<!-- VSSKENDPOLICYVAL#autoauth#101 -->

// got the PCA NS Login page...
<!-- VSSKBEGINPOLICYVAL#autoauth#102#1.2.0.5 -->
	if(browserNum < 5){
        self.location = "%%::remoteHost%%/VSApps/client/getplugin.htm";
    } else {
		self.location = "%%::remoteHost%%/VSApps/error/PTAUnsupportedBrowser.htm";
    }
<!-- VSSKENDPOLICYVAL#autoauth#102 -->

// error reporting for login and transaction pages
<!-- VSSKBEGINPOLICYVAL#autoauth#103 -->
  <FORM NAME=ErrorForm ACTION="%%::remoteHost%%/cgi-bin/softbounce.exe" METHOD=POST>
<!-- VSSKENDPOLICYVAL#autoauth#103 -->

<!-- VSSKBEGINPOLICYVAL#autoauth#104 -->
         Result = trigger.ConditionalSoftwareUpdate(
            "%%::remoteHost%%/VSApps/vspta3km.jar",
             "plugins/verisign/vspta",
             vi, trigger.DEFAULT_MODE);
<!-- VSSKENDPOLICYVAL#autoauth#104 -->

<!-- VSSKBEGINPOLICYVAL#autoauth#105 -->
         Result = trigger.ConditionalSoftwareUpdate(
            "%%::remoteHost%%/VSApps/vspta3.jar",
            "plugins/verisign/vspta",
             vi, trigger.DEFAULT_MODE);
<!-- VSSKENDPOLICYVAL#autoauth#105 -->

<!-- VSSKBEGINPOLICYVAL#autoauth#106 -->
<OBJECT
   classid="clsid:71C6919E-F9C0-11D2-8344-0060B0B32E16"
   codeBase="%%::remoteHost%%/VSApps/VSSgnAtb.cab#VERSION=2,0,0,8"
   id="ISignAtrb">
</OBJECT>
<!-- VSSKENDPOLICYVAL#autoauth#106 -->


<!-- VSSKBEGINPOLICYVAL#autoauth#107#1.0.0.2 -->

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
<!-- VSSKENDPOLICYVAL#autoauth#107 -->

//-- include the PTA control/plugin on the PTA logout page 
<!-- VSSKBEGINPOLICYVAL#autoauth#108#1.2.1.1 -->
<script Language="JavaScript">
<!--
if (navigator.appName == "Netscape")
{ document.write("<EMBED type='application/x-vspta2-plugin' name='ThePlugin' WIDTH=0 HEIGHT=0 HIDDEN>"); }
else
{ document.write("<OBJECT classid='clsid:6F7864F9-DB33-11D3-8166-0060B0F885E6' CODEBASE='%%::remoteHost%%/VSApps/vspta3.cab#VERSION=2,1,0,9' id='IVSPTA' style='LEFT: Opx; TOP: Opx; VISIBILITY: hidden'></OBJECT>");}
//-->
</script>
<!-- VSSKENDPOLICYVAL#autoauth#108 -->

<!-- VSSKBEGINPOLICYVAL#autoauth#109 -->
window.navigate("%%::remoteHost%%/cgi-bin/softbounce.exe?form_file=../fdf/VSApps/client/ExchangeErrors.fdf&errorCode=10000000&operation=Enrollment Status&showError=")
<!-- VSSKENDPOLICYVAL#autoauth#109 -->

<!-- VSSKBEGINPOLICYVAL#autoauth#110 -->
<input TYPE=hidden NAME=Enroll_operation VALUE="AutoAuthOSUserSubmit">
<input TYPE=hidden NAME=CertRqstPostURL VALUE="%%::remoteHost%%/cgi-bin/sophialite.exe">
<input TYPE=hidden NAME=Enroll_authenticate VALUE="NO">
<!--
<input TYPE=hidden NAME=Enroll_VHTML_FILE VALUE="../htmldocs/VSApps/client/enroll_wait.htm">
-->
<!-- VSSKENDPOLICYVAL#autoauth#110 -->

<!-- VSSKBEGINPOLICYVAL#autoauth#111 -->
<input type="hidden" name="ReturnURL" value="%%::remoteHost%%/VSApps/client/userInstallSuccess.htm">
<!-- VSSKENDPOLICYVAL#autoauth#111 -->

<!-- VSSKBEGINPOLICYVAL#autoauth#112#1.0.0.2 -->
<input type="hidden" name="ReturnURL" value="%%::remoteHost%%/VSApps/client/changePasswdSuccess.htm">
<!-- VSSKENDPOLICYVAL#autoauth#112 -->

<!-- VSSKBEGINPOLICYVAL#autoauth#113 -->
<input type="hidden" name="CancelURL" value="%%::remoteHost%%/VSApps/client/ptsCancel.htm">
<!-- VSSKENDPOLICYVAL#autoauth#113 -->

<!-- VSSKBEGINPOLICYVAL#autoauth#114#1.0.0.2 -->
<!-- include the PTA control -->
<OBJECT
   classid="clsid:D66256E2-B99C-11D4-8C74-0010830169AF"
   codeBase="%%::remoteHost%%/VSApps/vsnzpta.cab#VERSION=1,0,0,3"
   id='IVSNZ'
>
</OBJECT>

<OBJECT
  classid="clsid:6F7864F9-DB33-11D3-8166-0060B0F885E6"
  CODEBASE="%%::remoteHost%%/VSApps/vsnzpta.cab#VERSION=1,0,2,7"
>
</OBJECT>
<!-- VSSKENDPOLICYVAL#autoauth#114 -->


<!-- VSSKBEGINPOLICYVAL#autoauth#115 -->
	if(browserNum < 5){
        self.location = "%%::remoteHost%%/VSApps/client/getnzptaplugin.htm";
    } else {
		self.location = "%%::remoteHost%%/VSApps/client/getnzptaplugin6.htm";
    }
<!-- VSSKENDPOLICYVAL#autoauth#115 -->


<!-- VSSKBEGINPOLICYVAL#autoauth#116 -->
   Result = trigger.ConditionalSoftwareUpdate(
            "%%::remoteHost%%/VSApps/vsnzpta.jar",
            "verisign/vspta", vi, trigger.DEFAULT_MODE);
<!-- VSSKENDPOLICYVAL#autoauth#116 -->


<!-- VSSKBEGINPOLICYVAL#autoauth#117 -->
   Result = trigger.ConditionalSoftwareUpdate(
            "%%::remoteHost%%/VSApps/vsdnotz.jar",
            "verisign/vsdnotz", vi, trigger.DEFAULT_MODE);
<!-- VSSKENDPOLICYVAL#autoauth#117 -->

<!-- VSSKBEGINPOLICYVAL#autoauth#118 -->
<input type="hidden" name="CertRenewPostURL" value="%%::remoteHost%%/cgi-bin/sophialite.exe">
<!-- VSSKENDPOLICYVAL#autoauth#118 -->

<!-- VSSKBEGINPOLICYVAL#autoauth#119 -->
<INPUT type="hidden" name="ErrorPage.ReturnUrl" value="%%::remoteHost%%/VSApps/digitalidCenter.htm">
<!-- VSSKENDPOLICYVAL#autoauth#119 -->

<!-- VSSKBEGINPOLICYVAL#autoauth#120#1.0.0.0 -->

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


<!-- VSSKENDPOLICYVAL#autoauth#120 -->

// for the javapta Login MS pages...
<!-- VSSKBEGINPOLICYVAL#autoauth#121 -->
   hostName = "%%::remoteHost%%"
<!-- VSSKENDPOLICYVAL#autoauth#121 -->

<!-- VSSKBEGINPOLICYVAL#autoauth#122 -->
  if(browserNum >= 5){
	  self.location = "%%::remoteHost%%/VSApps/error/PTAUnsupportedBrowser.htm";
  }
<!-- VSSKENDPOLICYVAL#autoauth#122 -->

<!-- VSSKBEGINPOLICYVAL#autoauth#123 -->
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
<!-- VSSKENDPOLICYVAL#autoauth#123 -->

<!-- VSSKBEGINPOLICYVAL#autoauth#124 -->
try{
	dummy=ConfChk.getName();
	temp = 1;
}catch(er){
	temp=0;
	window.open("../vsapps/error/win2k.htm","_self");
}
<!-- VSSKENDPOLICYVAL#autoauth#124 -->

<!-- VSSKBEGINPOLICYVAL#autoauth#125#1.0.0.6 -->
document.write('<OBJECT');
document.write('  classid="clsid:6F7864F9-DB33-11D3-8166-0060B0F885E6"');
document.write('  CODEBASE="%%::remoteHost%%/VSApps/vspta3.cab#VERSION=2,1,0,9"');
document.write('  id="IVSPTA"');
document.write('  style="LEFT: Opx; TOP: Opx; VISIBILITY: hidden"');
document.write('>');
document.write('</OBJECT>');
<!-- VSSKENDPOLICYVAL#autoauth#125 -->

<!-- VSSKBEGINPOLICYVAL#autoauth#126 -->
<!-- VSSKENDPOLICYVAL#autoauth#126 -->

<!-- VSSKBEGINPOLICYVAL#autoauth#127#1.2.0.7 -->
document.write('<OBJECT');
document.write('   classid="clsid:5685505C-DA94-11D3-A1C3-001083023D07"');
document.write('   CODEBASE="%%::remoteHost%%/VSApps/VSGSE.cab#VERSION=2,6,0,3"');
document.write('   id="IGSE"');
document.write('	style="VISIBILITY: hidden" >');
document.write('</OBJECT>');
<!-- VSSKENDPOLICYVAL#autoauth#127 -->

<!-- VSSKBEGINPOLICYVAL#autoauth#128#1.0.0.1 -->
document.write('<OBJECT');
document.write('   classid="clsid:B1D475FE-75CD-11D2-8301-0060B0B32E16"');
document.write('   CODEBASE="%%::remoteHost%%/VSApps/VSImport.cab#VERSION=2,0,0,5"');
document.write('   id="Import"');
document.write('   style="LEFT: Opx; TOP: Opx; VISIBILITY: hidden"');
document.write('>');
document.write('</OBJECT>');
<!-- VSSKENDPOLICYVAL#autoauth#128 -->

<!-- VSSKBEGINPOLICYVAL#autoauth#129 -->
document.write('<OBJECT');
document.write('   classid="clsid:71C6919E-F9C0-11D2-8344-0060B0B32E16"');
document.write('   codeBase="%%::remoteHost%%/VSApps/VSSgnAtb.cab#VERSION=2,0,0,8"');
document.write('   id="ISignAtrb"');
document.write('   style="VISIBILITY: hidden">');
document.write('</OBJECT>');
<!-- VSSKENDPOLICYVAL#autoauth#129 -->


//include script for OBJECT declaration
<!-- VSSKBEGINPOLICYVAL#autoauth#130#1.0.0.1 -->
<script src="%%::remoteHost%%/VSApps/client/createObject.js" language="JavaScript"></script>
<!-- VSSKENDPOLICYVAL#autoauth#130 -->

<!-- VSSKBEGINPOLICYVAL#autoauth#131 -->
<script language="JavaScript"> createJavaPluginObject();</script>
<!-- VSSKENDPOLICYVAL#autoauth#131 -->
