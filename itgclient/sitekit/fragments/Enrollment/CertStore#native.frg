
<!-- VSSKBEGINPOLICYVAL#native#1 -->
<!-- VSSKBEGIN Global/Mode#19 -->
<!-- VSSKEND Global/Mode#19 -->
<!-- VSSKENDPOLICYVAL#native#1 -->

<!-- VSSKBEGINPOLICYVAL#native#2 -->
<!--BEGIN IN TABLE THREE-->
<!-- VSSKBEGIN Enrollment/CSP#1 -->
<!--VSSKEND Enrollment/CSP#1 -->
<!--END TABLE THREE-->
<P><BR><P>

<!-- BUG NOTE: The Base crypto provider is added twice and appears twice in the options -->

<!--BEGIN  TABLE FOUR-->

<!-- VSSKBEGIN Enrollment/KeyProtect#1 -->
<!-- VSSKEND Enrollment/KeyProtect -->

<!--END TABLE FOUR-->
<!-- VSSKENDPOLICYVAL#native#2 -->


<!-- VSSKBEGINPOLICYVAL#native#3 -->
<BODY onLoad="CheckIfVista(),FindProviders()" BGCOLOR="ffffff" LINK="cc0000" VLINK="666666">
<!-- VSSKENDPOLICYVAL#native#3 -->


<!-- VSSKBEGINPOLICYVAL#native#4 -->
<SCRIPT LANGUAGE="VBScript">
<!--
  '-- VSSKBEGIN Enrollment/CSP#3 --
  '-- VSSKEND Enrollment/CSP#3 --

Function CreateP10( keyflags )
 On Error Resume Next
 CreateP10 = ""

 spnCertEnroll.innerHTML="<OBJECT id='g_objClassFactory' CLASSID='clsid:884e2049-217d-11da-b2a4-000e7bbb2b09'></OBJECT>"

'-- VSSKBEGIN Enrollment/KeyLength#1 --
'-- VSSKEND Enrollment/KeyLength#1 --
End Function

  Sub DoKeyGen
    dim theForm 
    dim options
    dim keyflags
    dim cryptoProvName
    dim cryptoProvType

    keyflags=0
    set theForm = document.proform
    'theForm.submit.disabled = true
    ' VSSKTEST - commented out for testing purposes...the document is not submitted 
    ' to the server.

    '-- VSSKBEGIN Enrollment/CSP#2 --
    '-- VSSKEND Enrollment/CSP#2 --

   If isRunningOnVista = 0 Then
    cenroll.HashAlgorithm = "MD5"
    cenroll.KeySpec = 1
   End If

    '-- VSSKBEGIN Enrollment/KeyProtect#2 --
    '-- VSSKEND Enrollment/KeyProtect#2 --

    '-- VSSKBEGIN Enrollment/KeyExportable#1 --
    '-- VSSKEND Enrollment/KeyExportable#1 --

    theForm.public_key.value = CreateP10(keyflags)
    if Len(theForm.public_key.value) = 0 then
      MsgBox("The error: " + hex(err.number) + " occured in generating certificate request")
        window.navigate("../error/MSkeygenerr.htm")
    else
      theForm.submit
    end if
  End Sub
'-->
</SCRIPT>
<!-- VSSKENDPOLICYVAL#native#4 -->

<!-- VSSKBEGINPOLICYVAL#native#5 -->
<!-- VSSKENDPOLICYVAL#native#5 -->

<!-- VSSKBEGINPOLICYVAL#native#6 -->
<!-- VSSKENDPOLICYVAL#native#6 -->

<!-- VSSKBEGINPOLICYVAL#native#7 -->
<!--BEGIN IN TABLE THREE-->
<TABLE WIDTH=588 BGCOLOR="ffffcc" CELLPADDING=7 CELLSPACING=0 BORDER=0>
<TR>
<TD WIDTH=588>
<FONT SIZE=2 FACE="verdana, arial, helvetica"><B>Optional: Choose Your Encryption Strength</B></FONT><BR>
<FONT FACE="arial, helvetica" SIZE=2>The encryption strength indicated below is the maximum allowed by your browser software.  We recommend that you leave this as it is.
<BR></FONT>
<P>
<CENTER>
    <!--BEGIN INPUT FIELD TABLE-->
    <TABLE WIDTH=574 CELLPADDING=3 CELLSPACING=2 BORDER=0>
    <TR>
    <TD WIDTH=50% BGCOLOR="ffcc00">&nbsp;</TD>
    <TD COLSPAN=2 WIDTH=50% BGCOLOR="ffcc00"><IMG SRC="../graphics/blank2.gif" WIDTH=27 HEIGHT=27">&nbsp;&nbsp;&nbsp;
    <KEYGEN TYPE="hidden" NAME="public_key" VALUE=""></TD>
    </TR>
    </TABLE>
<!--END INPUT FIELD-->
</TD>
</TR>
</TABLE>
<!--END TABLE THREE-->
<P><BR><P>
<!-- VSSKENDPOLICYVAL#native#7 -->

<!-- VSSKBEGINPOLICYVAL#native#8 -->
<!-- VSSKENDPOLICYVAL#native#8 -->

<!-- VSSKBEGINPOLICYVAL#native#9 -->
       rval = true;
<!-- VSSKENDPOLICYVAL#native#9 -->

<!-- VSSKBEGINPOLICYVAL#native#10 -->
<!-- VSSKENDPOLICYVAL#native#10 -->

<!-- VSSKBEGINPOLICYVAL#native#11 -->
<SCRIPT LANGUAGE="VBScript">
<!--
  Sub InstallCert

  spnCertEnroll.innerHTML="<OBJECT id='g_objClassFactory' CLASSID='clsid:884e2049-217d-11da-b2a4-000e7bbb2b09'></OBJECT>"
  If isRunningOnVista = 0 Then
    Dim sz10
    sz10 = CertChain
    On Error Resume Next
    cenroll.DeleteRequestCert = FALSE
    err.clear
    cenroll.WriteCertToCSP = true
    cenroll.acceptPKCS7(sz10)
    if err.number <> 0 then
        cenroll.WriteCertToCSP = false
        err.clear
        cenroll.acceptPKCS7(sz10)
        if err.number <> 0 then
	     Call StopIt()
             window.navigate ("../VSApps/error/msinserr.htm")
             exit sub
        end if
    end if
  Else
      'MsgBox "Called InstallCert on Vista"
      const contextUser = 1
      const contextMachine = 2
      const CRYPT_STRING_BASE64 = 1
      const CRYPT_STRING_BASE64_ANY = 6
      dim objEnroll
      set objEnroll = g_objClassFactory.CreateObject("X509Enrollment.CX509Enrollment")
      objEnroll.Initialize(contextUser)
    
      call objEnroll.InstallResponse(0, CertChain, CRYPT_STRING_BASE64, "")
      If ( err.number <> 0 ) then
          window.navigate ( "../VSApps/error/msinsvistaerr.htm" )
      End If

  End If


    '-- VSSKBEGIN Apps/GSE#62 --
    '-- VSSKEND Apps/GSE#62 --
  End Sub
'-->
</SCRIPT>
<!-- VSSKENDPOLICYVAL#native#11 -->

// for userEnrollNS.fdf
<!-- VSSKBEGINPOLICYVAL#native#12 -->
STATUS		   0		VSApps/client/userInstallNS.htm
STATUS		6FFF		VSApps/client/userInstallNS.htm
<!-- VSSKENDPOLICYVAL#native#12 -->

// for userEnroll*.fdf
<!-- VSSKBEGINPOLICYVAL#native#13 -->
CONST     public_key_format       netscape
CONST     RAW_OUTPUT              yes
# VSSKBEGIN Apps/AuthBureau#2  
# VSSKEND Apps/AuthBureau#2 
<!-- VSSKENDPOLICYVAL#native#13 -->

// for userGetIDNS.fdf
<!-- VSSKBEGINPOLICYVAL#native#14 -->
CONST     RAW_OUTPUT              yes
<!-- VSSKENDPOLICYVAL#native#14 -->

// key manager should deliver files in pkcs12 format for firefox 
// enrollments if no WAC is used
<!-- VSSKBEGINPOLICYVAL#native#15 -->
CONST     key_format           pkcs12
<!-- VSSKENDPOLICYVAL#native#15 -->

// for userEnrollDualNS.fdf
<!-- VSSKBEGINPOLICYVAL#native#16 -->
STATUS		   0		VSApps/client/userInstallDualNS.htm
STATUS		6FFF		VSApps/client/userInstallDualNS.htm
<!-- VSSKENDPOLICYVAL#native#16 -->

// for userEnrollEncNS.fdf
<!-- VSSKBEGINPOLICYVAL#native#17 -->
STATUS		   0		VSApps/client/userInstallEncNS.htm
STATUS		6FFF		VSApps/client/userInstallEncNS.htm
<!-- VSSKENDPOLICYVAL#native#17 -->

// for userRenewalNS.fdf
<!-- VSSKBEGINPOLICYVAL#native#18 -->
STATUS		6FFF		VSApps/client/userRenewalInstallNS.htm
<!-- VSSKENDPOLICYVAL#native#18 -->

<!-- VSSKBEGINPOLICYVAL#native#19 -->
                rval = true;
<!-- VSSKENDPOLICYVAL#native#19 -->

<!-- VSSKBEGINPOLICYVAL#native#20 -->
<!-- VSSKENDPOLICYVAL#native#20 -->

<!-- VSSKBEGINPOLICYVAL#native#21 -->
<!-- VSSKENDPOLICYVAL#native#21 -->


<!-- VSSKBEGINPOLICYVAL#native#22 -->
<!-- VSSKBEGIN Global/Mode#19 -->
<!-- VSSKEND Global/Mode#19 -->
<!-- VSSKENDPOLICYVAL#native#22 -->

// key manager import control
<!-- VSSKBEGINPOLICYVAL#native#23 -->
<!-- VSSKBEGIN Global/Mode#22 -->
<!-- VSSKEND Global/Mode#22 -->
<!-- VSSKENDPOLICYVAL#native#23 -->

<!-- VSSKBEGINPOLICYVAL#native#24#2.0.0.1 -->
<Script Language = "VBScript">
<!--
  Sub ImportPKCS12
    Dim fSuccess
    Dim Tmp
    Dim bExportable, bReturnedExportable
    Dim KeyBlob, PKCS7Msg, MyErrorCode, MyErrorCodeMessage

    bExportable = TRUE
  On Error Resume Next
    Import.KeyExportable = bExportable


    If err.number <> 0 Then
	Select Case CStr(Hex(err.number))
	Case "1B6"
		Call SetErrorInfo2("../fdf/VSApps/client/ExchangeErrors.fdf", "00000036", CStr(Hex(err.number)),"Certificate Import Status")  
	   	exit Sub	
	End Select
    End If

    '-- VSSKBEGIN Enrollment/KeyProtect#4 --
    '-- VSSKEND Enrollment/KeyProtect#4 --

    '-- VSSKBEGIN Apps/KeyManager#14 --
    '-- VSSKEND Apps/KeyManager#14 --

    KeyBlob = "$$pkcs8_blob$$"
    PKCS7Msg = CertChain

    Import.Import KeyBlob, PKCS7Msg, fSuccess, MyErrorCode, MyErrorCodeMessage
    If fSuccess = FALSE then
       Call SetErrorInfo2("../fdf/VSApps/client/KeyMngrErrors.fdf", 00000002, CStr(Hex(MyErrorCode)), "Certificate Import Status")
       exit sub
    end if
   '-- VSSKBEGIN Apps/GSE#63 --
   '-- VSSKEND Apps/GSE#63 --
  End Sub
'-->
</SCRIPT>
<!-- VSSKENDPOLICYVAL#native#24 -->

<!-- VSSKBEGINPOLICYVAL#native#25#2.0.0.1 -->
<SCRIPT LANGUAGE="VBSCRIPT">
<!--
  Sub InstallSigningCert

    spnCertEnroll.innerHTML="<OBJECT id='g_objClassFactory' CLASSID='clsid:884e2049-217d-11da-b2a4-000e7bbb2b09'></OBJECT>"
    if IsIE4() Then
      window.onerror = ErrorFunc
    else
      On Error Resume Next
    end if
   If isRunningOnVista = 0 Then
    Dim sz10
    sz10 = "$$cert_base64_for_VBScript$$"
    cenroll.acceptPKCS7(sz10)
        if err.number <> 0 then
	     Call StopIt()
             window.navigate ("../VSApps/error/msinserr.htm")
             exit sub
        end if
   Else
    'MsgBox "Called InstallCert on Vista
     const contextUser = 1
     const contextMachine = 2
     const CRYPT_STRING_BASE64 = 1
     const CRYPT_STRING_BASE64_ANY = 6
    
     CertChain = "$$cert_base64_for_VBScript$$"
     dim objEnroll
     set objEnroll = g_objClassFactory.CreateObject("X509Enrollment.CX509Enrollment")
     objEnroll.Initialize(contextUser)
    
      call objEnroll.InstallResponse(0, CertChain, CRYPT_STRING_BASE64, "")
      If ( err.number <> 0 ) then
          window.navigate ( "../VSApps/error/msinsvistaerr.htm" )
       End If

   End If
  '-- VSSKBEGIN Apps/GSE#62 --
  '-- VSSKEND Apps/GSE#62 --
  End Sub

  Sub ImportPKCS12
    Dim fSuccess 
    Dim Tmp
    Dim KeyBlob, PKCS7Msg, MyErrorCode, MyErrorCodeMessage

    'First install the Encryption cert
    bExportable = TRUE 
  On Error Resume Next
    Import.KeyExportable = bExportable
    If err.number <> 0 Then
	Select Case CStr(Hex(err.number))
	Case "1B6"
		Call SetErrorInfo2("../fdf/VSApps/client/ExchangeErrors.fdf", "00000036", CStr(Hex(err.number)),"Certificate Import Status")  
	   	exit Sub	
	End Select
    End If

    '-- VSSKBEGIN Enrollment/KeyProtect#4 --
    '-- VSSKEND Enrollment/KeyProtect#4 --

    '-- VSSKBEGIN Apps/KeyManager#14 --
    '-- VSSKEND Apps/KeyManager#14 --

    KeyBlob = "$$pkcs8_blob$$"
    PKCS7Msg = CertChain

    Import.Import KeyBlob, PKCS7Msg, fSuccess, MyErrorCode, MyErrorCodeMessage
    If fSuccess = FALSE then
       Call SetErrorInfo2("../fdf/VSApps/client/KeyMngrErrors.fdf", 00000002, CStr(Hex(MyErrorCode)), "Certificate Import Status")
       exit sub
    end if
    '-- VSSKBEGIN Apps/GSE#63 --
    '-- VSSKEND Apps/GSE#63 --

    document.close

    End Sub
'-->
</SCRIPT>
<!-- VSSKENDPOLICYVAL#native#25 -->

<!-- VSSKBEGINPOLICYVAL#native#26 -->
                document.proform.submit();
<!-- VSSKENDPOLICYVAL#native#26 -->

<!-- VSSKBEGINPOLICYVAL#native#27 -->
<!-- VSSKENDPOLICYVAL#native#27 -->

<!-- VSSKBEGINPOLICYVAL#native#28 -->
<!-- VSSKENDPOLICYVAL#native#28 -->

<!-- VSSKBEGINPOLICYVAL#native#29 -->
<!-- VSSKENDPOLICYVAL#native#29 -->

<!-- VSSKBEGINPOLICYVAL#native#30 -->
<!-- VSSKENDPOLICYVAL#native#30 -->

<!-- VSSKBEGINPOLICYVAL#native#31 -->
<!-- VSSKENDPOLICYVAL#native#31 -->

<!-- VSSKBEGINPOLICYVAL#native#32 -->
<!-- VSSKENDPOLICYVAL#native#32 -->

<!-- VSSKBEGINPOLICYVAL#native#33#1.2.0.4 -->
<script language = "JavaScript">
<!--
	GoToHome();
//-->
</script>
<!-- VSSKENDPOLICYVAL#native#33 -->

<!-- VSSKBEGINPOLICYVAL#native#34 -->
<!-- VSSKENDPOLICYVAL#native#34 -->

<!-- VSSKBEGINPOLICYVAL#native#35#1.2.0.4 -->
<!-- VSSKENDPOLICYVAL#native#35 -->

<!-- VSSKBEGINPOLICYVAL#native#36 -->
<!-- VSSKENDPOLICYVAL#native#36 -->

<!-- VSSKBEGINPOLICYVAL#native#37 -->
<SCRIPT Language="VBScript">
<!--
    On Error Resume Next
    Set bExportable = Import.KeyExportable
	If ( (Hex(err.number) = "1B6") AND (InStr(1,navigator.appMinorVersion,";SP2;") > 0)  ) Then
         window.location = "./client/installComponentForSP2.htm"
    End If
-->
</SCRIPT>
<!-- VSSKENDPOLICYVAL#native#37 -->
<!-- VSSKBEGINPOLICYVAL#native#38 -->
try{
	dummy=Import.getName();
	temp = 1;
}catch(er){
	temp=0;
	window.open("../vsapps/error/win2k.htm","_self");
}
<!-- VSSKENDPOLICYVAL#native#38 -->

<!-- VSSKBEGINPOLICYVAL#native#39 -->
<!-- VSSKBEGIN Global/Mode#128 -->
<!-- VSSKEND Global/Mode#128 -->
<!-- VSSKENDPOLICYVAL#native#39 -->
