<!-- VSSKBEGINPOLICYVAL#yes#1#1.0.0.2 -->
<Script Language="VBScript">
<!--
  Dim ApplicationName
  Dim PreferenceName
  Dim PreferenceValue
  Dim IVSNZAppPref
  Dim NZIntermediateCA
  Dim vbNotarizationServer
  Dim vbHashAlgorithm
  Dim vbDisplayID
  Dim vbHostingServer
  Dim vbRevocationInformation
  Dim vbLogoUrl
  Dim vbWizardTitle
  Dim vbSelectFileTitle
  Dim vbSelectFileDescription
  Dim vbProgressTitle
  Dim vbProgressDescription
  Dim vbVerifyReceiptTitle
  Dim vbVerifyReceiptDesc
  Dim vbReceiptDesc
  Dim vbAppContext
  Dim vbSearchCriteria
  Dim vbClientInfo
  Dim vbClientInfoSig
  Dim vbCapi
  
  Dim vbProgressHelpUrl
  Dim vbVerifyReceiptHelpUrl
  Dim vbHelpUrl

  '-- VSSKBEGIN Global/Mode#35 --
  '-- VSSKEND Global/Mode#35 --

  NZIntermediateCA = "MIIDzjCCAzegAwIBAgIQAWvNF7MSr5Z+mIGLKKQVwTANBgkqhkiG9w0BAQUFADCBwTELMAkGA1UEBhMCVVMxFzAVBgNVBAoTDlZlcmlTaWduLCBJbmMuMTwwOgYDVQQLEzNDbGFzcyAzIFB1YmxpYyBQcmltYXJ5IENlcnRpZmljYXRpb24gQXV0aG9yaXR5IC0gRzIxOjA4BgNVBAsTMShjKSAxOTk4IFZlcmlTaWduLCBJbmMuIC0gRm9yIGF1dGhvcml6ZWQgdXNlIG9ubHkxHzAdBgNVBAsTFlZlcmlTaWduIFRydXN0IE5ldHdvcmswHhcNMDEwNTA4MDAwMDAwWhcNMTEwNTA3MjM1OTU5WjCBpTEXMBUGA1UEChMOVmVyaVNpZ24sIEluYy4xHzAdBgNVBAsTFlZlcmlTaWduIFRydXN0IE5ldHdvcmsxOzA5BgNVBAsTMlRlcm1zIG9mIHVzZSBhdCBodHRwczovL3d3dy52ZXJpc2lnbi5jb20vcnBhIChjKTAxMSwwKgYDVQQDEyNWZXJpU2lnbiBUaW1lIFN0YW1waW5nIEF1dGhvcml0eSBDQTCBnTANBgkqhkiG9w0BAQEFAAOBiwAwgYcCgYEA4RQ9CevWSRcoKRVkud/jScl65xUmG1Ey3JpnS+WSMMkQRtkNHO4FTatO4RdC2PGZa6B3Um7gmR3/gfXs2Pe3NudPOVRQUK4rgGUDj9un8VJk40K8oMu5Z4Qa1cyLA4nNqAZ4xD1uTptdgrZPmbljPgXaojBLDqZpmh27OP9UliUCAQOjgeIwgd8wQAYIKwYBBQUHAQEENDAyMDAGCCsGAQUFBzABhiRodHRwOi8vb2NzcC52ZXJpc2lnbi5jb20vb2NzcC9zdGF0dXMwEgYDVR0TAQH/BAgwBgEB/wIBADBEBgNVHSAEPTA7MDkGC2CGSAGG+EUBBxcDMCowKAYIKwYBBQUHAgEWHGh0dHBzOi8vd3d3LnZlcmlzaWduLmNvbS9ycGEwMQYDVR0fBCowKDAmoCSgIoYgaHR0cDovL2NybC52ZXJpc2lnbi5jb20vcGNhMy5jcmwwDgYDVR0PAQH/BAQDAgEGMA0GCSqGSIb3DQEBBQUAA4GBACE0Fj8u0nbjDYVx6+i8Oxb0fdHaOCLY7LsG4w6ZJ2ef9TuV34Glpt4xDuYCVU+MXPj4LOBZOFYrFceR4uG7T1fkq8u9ab1CtEiETdJOMF2TSDKhy/96KFj2HExVlB2vFCp5r369z7jPD2+SxrnKKQz0LiTiR4xBlhYQfTlQd1Om"
  ApplicationName = "Notarization"
  vbNotarizationServer = "%%nzNotarizationServer%%"
  vbHashAlgorithm = "MD5"
  vbDisplayID = 1
  'vbValidationFlag = 8
  If ( "%%nzNotarizationSystem%%" = "pilot" ) then
        vbValidationFlag = 0
  Else 
        vbValidationFlag = 8
  End If
  vbRevocationInformation = ""
  vbLogoUrl = "%%Apps/PTAv2::ptaAppLogoUrl%%"
  vbWizardTitle = "%%nzWizardTitle%%"
  vbSelectFileTitle =   "%%nzSelectFileTitle%%"
  vbSelectFileDescription = "%%nzSelectFileDescription%%"
  vbProgressTitle = "%%nzProgressTitle%%"
  vbProgressDescription = ""
  vbVerifyReceiptTitle = "%%nzVerifyReceiptTitle%%"
  vbVerifyReceiptDesc = ""
  vbReceiptDesc = ""
  vbAppContext = "%%Apps/PTAv2::ptaAppName%%"
  vbSearchCriteria = "%%::ptaIssuerDN%%"
  vbClientInfo = "%%Apps/PTAv2/Roaming::clientInfo%%"
  vbClientInfoSig = "%%Apps/PTAv2/Roaming::clientInfoSig%%"
  If ( "%%Enrollment/CertStore::policyValue%%" = "verisign" ) then
	vbCapi = 0
  Else
	vbCapi = 1
  End If
 
  vbHostingServer = helpHostName & "/VSApps/"
  vbProgressHelpUrl = helpHostName & "/VSApps/client/help/tasks/nzprogress.htm"
  vbVerifyReceiptHelpUrl = helpHostName & "/VSApps/client/help/tasks/nzreceipt.htm"
  vbHelpUrl = ""
'-->
</Script>
<!-- VSSKENDPOLICYVAL#yes#1 -->

  

<!-- VSSKBEGINPOLICYVAL#yes#2#1.0.0.4 -->
<Script Language="VBScript">
<!--
  Dim strAppCtxtName
  Dim strCertStore
  Dim strClientInfo
  Dim strClientInfoSig
  Dim strNotarizationServer
  Dim strDisplayDigitalID
  Dim strHashAlg
  Dim strSrchCriteria
  Dim strLogoUrl
  Dim ValidationFlags
  Dim NZIntermediateCA
  Dim strWizardTitle
  Dim strSelectFileTitle
  Dim strSelectFileDescription
  Dim strProgressTitle
  Dim strVerifyReceiptTitle
  Dim strProgressHelpUrl
  Dim strVerifyReceiptHelpUrl

  '-- VSSKBEGIN Global/Mode#35 --
  '-- VSSKEND Global/Mode#35 --

  strAppCtxtName = "%%Apps/PTAv2::ptaAppName%%"
  strCertStore = %%Apps/PTAv2::ptaCertStore%%
  strSrchCriteria = "%%::ptaIssuerDN%%"
  strNotarizationServer = "%%nzNotarizationServer%%"
  strDisplayDigitalID = "1"
  strHashAlg = "MD5"
  strLogoUrl = "%%Apps/PTAv2::ptaAppLogoUrl%%"
  If ( "%%nzNotarizationSystem%%" = "pilot" ) then
        ValidationFlags = 0
  Else 
        ValidationFlags = 8
  End If
  'ValidationFlags = 8
  strClientInfo = "%%Apps/PTAv2/Roaming::clientInfo%%"
  strClientInfoSig = "%%Apps/PTAv2/Roaming::clientInfoSig%%"
  NZIntermediateCA = "MIIDzjCCAzegAwIBAgIQAWvNF7MSr5Z+mIGLKKQVwTANBgkqhkiG9w0BAQUFADCBwTELMAkGA1UEBhMCVVMxFzAVBgNVBAoTDlZlcmlTaWduLCBJbmMuMTwwOgYDVQQLEzNDbGFzcyAzIFB1YmxpYyBQcmltYXJ5IENlcnRpZmljYXRpb24gQXV0aG9yaXR5IC0gRzIxOjA4BgNVBAsTMShjKSAxOTk4IFZlcmlTaWduLCBJbmMuIC0gRm9yIGF1dGhvcml6ZWQgdXNlIG9ubHkxHzAdBgNVBAsTFlZlcmlTaWduIFRydXN0IE5ldHdvcmswHhcNMDEwNTA4MDAwMDAwWhcNMTEwNTA3MjM1OTU5WjCBpTEXMBUGA1UEChMOVmVyaVNpZ24sIEluYy4xHzAdBgNVBAsTFlZlcmlTaWduIFRydXN0IE5ldHdvcmsxOzA5BgNVBAsTMlRlcm1zIG9mIHVzZSBhdCBodHRwczovL3d3dy52ZXJpc2lnbi5jb20vcnBhIChjKTAxMSwwKgYDVQQDEyNWZXJpU2lnbiBUaW1lIFN0YW1waW5nIEF1dGhvcml0eSBDQTCBnTANBgkqhkiG9w0BAQEFAAOBiwAwgYcCgYEA4RQ9CevWSRcoKRVkud/jScl65xUmG1Ey3JpnS+WSMMkQRtkNHO4FTatO4RdC2PGZa6B3Um7gmR3/gfXs2Pe3NudPOVRQUK4rgGUDj9un8VJk40K8oMu5Z4Qa1cyLA4nNqAZ4xD1uTptdgrZPmbljPgXaojBLDqZpmh27OP9UliUCAQOjgeIwgd8wQAYIKwYBBQUHAQEENDAyMDAGCCsGAQUFBzABhiRodHRwOi8vb2NzcC52ZXJpc2lnbi5jb20vb2NzcC9zdGF0dXMwEgYDVR0TAQH/BAgwBgEB/wIBADBEBgNVHSAEPTA7MDkGC2CGSAGG+EUBBxcDMCowKAYIKwYBBQUHAgEWHGh0dHBzOi8vd3d3LnZlcmlzaWduLmNvbS9ycGEwMQYDVR0fBCowKDAmoCSgIoYgaHR0cDovL2NybC52ZXJpc2lnbi5jb20vcGNhMy5jcmwwDgYDVR0PAQH/BAQDAgEGMA0GCSqGSIb3DQEBBQUAA4GBACE0Fj8u0nbjDYVx6+i8Oxb0fdHaOCLY7LsG4w6ZJ2ef9TuV34Glpt4xDuYCVU+MXPj4LOBZOFYrFceR4uG7T1fkq8u9ab1CtEiETdJOMF2TSDKhy/96KFj2HExVlB2vFCp5r369z7jPD2+SxrnKKQz0LiTiR4xBlhYQfTlQd1Om"
  strWizardTitle = "%%nzWizardTitle%%"
  strSelectFileTitle =   "%%nzSelectFileTitle%%"
  strSelectFileDescription = "%%nzSelectFileDescription%%"
  strProgressTitle = "%%nzProgressTitle%%"
  strVerifyReceiptTitle = "%%nzVerifyReceiptTitle%%"
  strProgressHelpUrl = helpHostName & "/VSApps/client/help/tasks/nzprogress.htm"
  strVerifyReceiptHelpUrl = helpHostName & "/VSApps/client/help/tasks/nzreceipt.htm"
'-->
</Script>
<!-- VSSKENDPOLICYVAL#yes#2 -->

<!-- VSSKBEGINPOLICYVAL#yes#3#1.0.0.3 -->
<SCRIPT LANGUAGE="JavaScript">
<!--
  var len;
  var name;
  var description;
  var found = 0;

  navigator.plugins.refresh(true);

  len = navigator.plugins.length;
  for(i=0;i<len;++i)
  {
        name = navigator.plugins[i].name;
        description = navigator.plugins[i].description;
        if(name.search("VeriSign Personal Trust Agent") != -1)
        {
          if (browserNum < 5) {
            if ( description >= 3027 )
            {
                found = 1;
                i = len;
            }
          } else {
            if ( description >= 3505 )
            { 
                found = 1;
                i = len;
            }
          }
        }
  }

  if(found != 1)
    //-- VSSKBEGIN Global/Mode#115 --
    //-- VSSKEND Global/Mode#115 --
//-->
</SCRIPT>
<!-- VSSKENDPOLICYVAL#yes#3 -->


<!-- VSSKBEGINPOLICYVAL#yes#4#1.0.0.4 -->
<Script Language="JavaScript">
<!--
  //-- VSSKBEGIN Global/Mode#36 --
  //-- VSSKEND Global/Mode#36 --

  var NZIntermediateCA = "MIIDzjCCAzegAwIBAgIQAWvNF7MSr5Z+mIGLKKQVwTANBgkqhkiG9w0BAQUFADCBwTELMAkGA1UEBhMCVVMxFzAVBgNVBAoTDlZlcmlTaWduLCBJbmMuMTwwOgYDVQQLEzNDbGFzcyAzIFB1YmxpYyBQcmltYXJ5IENlcnRpZmljYXRpb24gQXV0aG9yaXR5IC0gRzIxOjA4BgNVBAsTMShjKSAxOTk4IFZlcmlTaWduLCBJbmMuIC0gRm9yIGF1dGhvcml6ZWQgdXNlIG9ubHkxHzAdBgNVBAsTFlZlcmlTaWduIFRydXN0IE5ldHdvcmswHhcNMDEwNTA4MDAwMDAwWhcNMTEwNTA3MjM1OTU5WjCBpTEXMBUGA1UEChMOVmVyaVNpZ24sIEluYy4xHzAdBgNVBAsTFlZlcmlTaWduIFRydXN0IE5ldHdvcmsxOzA5BgNVBAsTMlRlcm1zIG9mIHVzZSBhdCBodHRwczovL3d3dy52ZXJpc2lnbi5jb20vcnBhIChjKTAxMSwwKgYDVQQDEyNWZXJpU2lnbiBUaW1lIFN0YW1waW5nIEF1dGhvcml0eSBDQTCBnTANBgkqhkiG9w0BAQEFAAOBiwAwgYcCgYEA4RQ9CevWSRcoKRVkud/jScl65xUmG1Ey3JpnS+WSMMkQRtkNHO4FTatO4RdC2PGZa6B3Um7gmR3/gfXs2Pe3NudPOVRQUK4rgGUDj9un8VJk40K8oMu5Z4Qa1cyLA4nNqAZ4xD1uTptdgrZPmbljPgXaojBLDqZpmh27OP9UliUCAQOjgeIwgd8wQAYIKwYBBQUHAQEENDAyMDAGCCsGAQUFBzABhiRodHRwOi8vb2NzcC52ZXJpc2lnbi5jb20vb2NzcC9zdGF0dXMwEgYDVR0TAQH/BAgwBgEB/wIBADBEBgNVHSAEPTA7MDkGC2CGSAGG+EUBBxcDMCowKAYIKwYBBQUHAgEWHGh0dHBzOi8vd3d3LnZlcmlzaWduLmNvbS9ycGEwMQYDVR0fBCowKDAmoCSgIoYgaHR0cDovL2NybC52ZXJpc2lnbi5jb20vcGNhMy5jcmwwDgYDVR0PAQH/BAQDAgEGMA0GCSqGSIb3DQEBBQUAA4GBACE0Fj8u0nbjDYVx6+i8Oxb0fdHaOCLY7LsG4w6ZJ2ef9TuV34Glpt4xDuYCVU+MXPj4LOBZOFYrFceR4uG7T1fkq8u9ab1CtEiETdJOMF2TSDKhy/96KFj2HExVlB2vFCp5r369z7jPD2+SxrnKKQz0LiTiR4xBlhYQfTlQd1Om";
  var ApplicationName = "Notarization";
  var jsNotarizationServer = "%%nzNotarizationServer%%";
  var jsHashAlgorithm = "MD5";
  var jsDisplayID = 1;
  var jsValidationFlag;
  if ( "%%nzNotarizationSystem%%" == "pilot" )
      jsValidationFlag = 0;
  else
      jsValidationFlag = 8;

  var jsRevocationInformation = "";
  var jsLogoUrl = "%%Apps/PTAv2::ptaAppLogoUrl%%";
  var jsWizardTitle = "%%nzWizardTitle%%";
  var jsSelectFileTitle =   "%%nzSelectFileTitle%%";
  var jsSelectFileDescription = "%%nzSelectFileDescription%%";
  var jsProgressTitle = "%%nzProgressTitle%%";
  var jsProgressDescription = "";
  var jsVerifyReceiptTitle = "%%nzVerifyReceiptTitle%%";
  var jsVerifyReceiptDesc = "";
  var jsReceiptDesc = "";
  var jsAppContext = "%%Apps/PTAv2::ptaAppName%%";
  var jsSearchCriteria = "%%::ptaIssuerDN%%";
  var jsClientInfo = "%%Apps/PTAv2/Roaming::clientInfo%%";
  var jsClientInfoSig = "%%Apps/PTAv2/Roaming::clientInfoSig%%";
  var jsCapi;
  if ( "%%Enrollment/CertStore::policyValue%%" == "verisign" ) 
	jsCapi = 0;
  else
	jsCapi = 1;
  
  var jsHostingServer = helpHostName + "/VSApps/";
  var jsProgressHelpUrl = helpHostName + "/VSApps/client/help/tasks/nzprogress.htm";
  var jsVerifyReceiptHelpUrl = helpHostName + "/VSApps/client/help/tasks/nzreceipt.htm";
  var jsHelpUrl = "";
//-->
</Script>
<!-- VSSKENDPOLICYVAL#yes#4 -->

<!-- VSSKBEGINPOLICYVAL#yes#5#1.0.0.4 -->
<Script Language="JavaScript">
<!--
  //-- VSSKBEGIN Global/Mode#36 --
  //-- VSSKEND Global/Mode#36 --

  var strAppCtxtName = "%%Apps/PTAv2::ptaAppName%%";
  var strCertStore = %%Apps/PTAv2::ptaCertStore%%;
  var strSrchCriteria = "%%::ptaIssuerDN%%";
  var strNotarizationServer = "%%nzNotarizationServer%%";
  var strDisplayDigitalID = "1";
  var strHashAlg = "MD5";
  var strLogoUrl = "%%Apps/PTAv2::ptaAppLogoUrl%%";
  var ValidationFlags;
  if ( "%%nzNotarizationSystem%%" == "pilot" )
      ValidationFlags = 0;
  else
      ValidationFlags = 8;

  var strClientInfo = "%%Apps/PTAv2/Roaming::clientInfo%%";
  var strClientInfoSig = "%%Apps/PTAv2/Roaming::clientInfoSig%%";
  var NZIntermediateCA = "MIIDzjCCAzegAwIBAgIQAWvNF7MSr5Z+mIGLKKQVwTANBgkqhkiG9w0BAQUFADCBwTELMAkGA1UEBhMCVVMxFzAVBgNVBAoTDlZlcmlTaWduLCBJbmMuMTwwOgYDVQQLEzNDbGFzcyAzIFB1YmxpYyBQcmltYXJ5IENlcnRpZmljYXRpb24gQXV0aG9yaXR5IC0gRzIxOjA4BgNVBAsTMShjKSAxOTk4IFZlcmlTaWduLCBJbmMuIC0gRm9yIGF1dGhvcml6ZWQgdXNlIG9ubHkxHzAdBgNVBAsTFlZlcmlTaWduIFRydXN0IE5ldHdvcmswHhcNMDEwNTA4MDAwMDAwWhcNMTEwNTA3MjM1OTU5WjCBpTEXMBUGA1UEChMOVmVyaVNpZ24sIEluYy4xHzAdBgNVBAsTFlZlcmlTaWduIFRydXN0IE5ldHdvcmsxOzA5BgNVBAsTMlRlcm1zIG9mIHVzZSBhdCBodHRwczovL3d3dy52ZXJpc2lnbi5jb20vcnBhIChjKTAxMSwwKgYDVQQDEyNWZXJpU2lnbiBUaW1lIFN0YW1waW5nIEF1dGhvcml0eSBDQTCBnTANBgkqhkiG9w0BAQEFAAOBiwAwgYcCgYEA4RQ9CevWSRcoKRVkud/jScl65xUmG1Ey3JpnS+WSMMkQRtkNHO4FTatO4RdC2PGZa6B3Um7gmR3/gfXs2Pe3NudPOVRQUK4rgGUDj9un8VJk40K8oMu5Z4Qa1cyLA4nNqAZ4xD1uTptdgrZPmbljPgXaojBLDqZpmh27OP9UliUCAQOjgeIwgd8wQAYIKwYBBQUHAQEENDAyMDAGCCsGAQUFBzABhiRodHRwOi8vb2NzcC52ZXJpc2lnbi5jb20vb2NzcC9zdGF0dXMwEgYDVR0TAQH/BAgwBgEB/wIBADBEBgNVHSAEPTA7MDkGC2CGSAGG+EUBBxcDMCowKAYIKwYBBQUHAgEWHGh0dHBzOi8vd3d3LnZlcmlzaWduLmNvbS9ycGEwMQYDVR0fBCowKDAmoCSgIoYgaHR0cDovL2NybC52ZXJpc2lnbi5jb20vcGNhMy5jcmwwDgYDVR0PAQH/BAQDAgEGMA0GCSqGSIb3DQEBBQUAA4GBACE0Fj8u0nbjDYVx6+i8Oxb0fdHaOCLY7LsG4w6ZJ2ef9TuV34Glpt4xDuYCVU+MXPj4LOBZOFYrFceR4uG7T1fkq8u9ab1CtEiETdJOMF2TSDKhy/96KFj2HExVlB2vFCp5r369z7jPD2+SxrnKKQz0LiTiR4xBlhYQfTlQd1Om";
  var strWizardTitle = "%%nzWizardTitle%%";
  var strSelectFileTitle =   "%%nzSelectFileTitle%%";
  var strSelectFileDescription = "%%nzSelectFileDescription%%";
  var strProgressTitle = "%%nzProgressTitle%%";
  var strVerifyReceiptTitle = "%%nzVerifyReceiptTitle%%";
  var strProgressHelpUrl = helpHostName + "/VSApps/client/help/tasks/nzprogress.htm";
  var strVerifyReceiptHelpUrl = helpHostName + "/VSApps/client/help/tasks/nzreceipt.htm";
//-->
</Script>
<!-- VSSKENDPOLICYVAL#yes#5 -->

<!-- VSSKBEGINPOLICYVAL#yes#6#1.0.0.2 -->
<p>
<TR>
	<TD WIDTH=50 ALIGN=left VALIGN=top>
        <SCRIPT Language="JavaScript">
        <!-- 
        if (navigator.appName == "Netscape")
           {document.write("<A HREF='client/notarizationInstallNS.htm'>")}
        else
           {document.write("<A HREF='client/notarizationInstallMS.htm'>")}
        //-->
        </SCRIPT>
	<IMG align=left border=0 height=40 src="graphics/action_arrowyellow.gif" width=40></A>
	</TD>
	<TD WIDTH=538 ALIGN=left VALIGN=top>
        <SCRIPT Language="JavaScript">
        <!-- 
        if (navigator.appName == "Netscape")
           {document.write("<A HREF='client/notarizationInstallNS.htm'>")}
        else
           {document.write("<A HREF='client/notarizationInstallMS.htm'>")}
        //-->
        </SCRIPT>
	<FONT FACE="verdana, arial, helvetica" SIZE=4><B>Install Digital Notarization Client</B></FONT></A><BR>
	<FONT FACE="arial, helvetica" SIZE=2>This option will install the VeriSign Digital Notarization Client on your desktop.
	</FONT>
	<P></P>
	</TD>
</TR></p>
<p>
<TR>
	<TD WIDTH=50 ALIGN=left VALIGN=top>
        <SCRIPT Language="JavaScript">
        <!-- 
        if (navigator.appName == "Netscape")
           {document.write("<A HREF='client/notarizeNS.htm'>")}
        else
           {document.write("<A HREF='client/notarizeMS.htm'>")}
        //-->
        </SCRIPT>
	<IMG align=left border=0 height=40 src="graphics/action_arrowyellow.gif" width=40></A>
	</TD>
	<TD WIDTH=538 ALIGN=left VALIGN=top>
        <SCRIPT Language="JavaScript">
        <!-- 
        if (navigator.appName == "Netscape")
           {document.write("<A HREF='client/notarizeNS.htm'>")}
        else
           {document.write("<A HREF='client/notarizeMS.htm'>")}
        //-->
        </SCRIPT>
	<FONT FACE="verdana, arial, helvetica" SIZE=4><B>Notarize Documents</B></FONT></A><BR>
	<FONT FACE="arial, helvetica" SIZE=2>This page will enable you to Digitally Notarize documents.
	</FONT>
	<P></P>
	</TD>
</TR></p>
<!-- VSSKENDPOLICYVAL#yes#6 -->
