
<!-- VSSKBEGINPOLICYVAL#microsoft#1 -->
<!-- VSSKBEGIN Global/Mode#19 -->
<!-- VSSKEND Global/Mode#19 -->
<!-- VSSKENDPOLICYVAL#microsoft#1 -->

<!-- VSSKBEGINPOLICYVAL#microsoft#2 -->
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
<!-- VSSKENDPOLICYVAL#microsoft#2 -->

<!-- VSSKBEGINPOLICYVAL#microsoft#3 -->
<BODY onLoad="CheckIfVista(), FindProviders()" BGCOLOR="ffffff" LINK="cc0000" VLINK="666666">
<!-- VSSKENDPOLICYVAL#microsoft#3 -->

<!-- VSSKBEGINPOLICYVAL#microsoft#4#1.0.0.1 -->
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

Function  CreatePKCS10
	On Error Resume Next
	CreatePKCS10 = ""
	SubjectDN = "CN=vsc1enroll"
	HashAlg = CInt(4)

	'need to handle key exportability and key strength policies
	KeyFlags = &h00000001   'KEY SPEC = AT_KEYEXCHANGE

	'-- VSSKBEGIN Enrollment/KeyExportable#3 --
	'-- VSSKEND Enrollment/KeyExportable#3 --

	Dim Attributes(2,2)
	Attributes(1,1) = "2.5.29.15"
	Attributes(1,2) = "03020138"
	Attributes(2,1) = "2.5.29.37"	
	Attributes(2,2) = "300A06082B06010505070302"

	'-- VSSKBEGIN Enrollment/KeyLength#4 --
	'-- VSSKEND Enrollment/KeyLength#4 --
End Function

  Sub DoKeyGen
    dim theForm 
    dim options
    dim keyflags
    dim cryptoProvName
    dim cryptoProvType

	Dim TPMEnabled
	Dim boolTPMAvailable
	Dim strAppCtxtName

	boolTPMAvailable = CBool(0)
	TPMEnabled = "%%Apps/PTAv2::ptaTPMOption%%"

	strAppCtxtName = "%%Apps/PTAv2::ptaAppName%%"

	On Error Resume Next
	if(TPMEnabled = "CHECKED") then
		boolTPMAvailable = IVSPTA.IsTPMAvailable 
	End If

    keyflags=0
    set theForm = document.proform
    'theForm.submit.disabled = true
    ' VSSKTEST - commented out for testing purposes...the document is not submitted 
    ' to the server.
	if(TPMEnabled = "CHECKED" And boolTPMAvailable = "True") then
		On Error Resume Next

		IVSPTA.Initialize strAppCtxtName,2
		' Create the PKCS 10
		theForm.public_key.value = CreatePKCS10()
	else

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
	End If

	if Len(theForm.public_key.value) = 0 then
	  MsgBox("The error: " + hex(err.number) + " occured in generating certificate request")
		window.navigate("../error/MSkeygenerr.htm")
	else
	  theForm.submit
	end if
  End Sub
'-->
</SCRIPT>
<!-- VSSKENDPOLICYVAL#microsoft#4 -->



<!-- VSSKBEGINPOLICYVAL#microsoft#5#1.2.0.4 -->
<SCRIPT LANGUAGE="JavaScript">
<!--
  var PKCS10;

 function InitPlugin()
 {
   if(browserNum < 5) {
	document.NSCP_IVSPTA = document.ThePlugin;
   } else {
	document.NSCP_IVSPTA = document.ThePlugin.ns6IPTA;
   }
 }
   
  //-- VSSKBEGIN Enrollment/CSP#5 --  
  //-- VSSKEND Enrollment/CSP#5 --

  //-- VSSKBEGIN Enrollment/KeyLength#2 --
  //-- VSSKEND Enrollment/KeyLength#2 --

  function GenerateP10Java()
  {
    var KeyFlags;
    KeyFlags = 0;

	if(browserNum < 5) {
		PKCS10 = new java.lang.StringBuffer("");
	}
	else {
		PKCS10 = new String("");
	}
	
    //alert("Generating the key-pair");
    // alert("Inside GenerateP10Java ...") ;
    if (document.NSCP_IVSPTA == null) {
       SetErrorInfo ("../fdf/VSApps/client/PTAv2Errors.fdf", "00000101", 0, "The plugin instance is NULL");
    }
 
    
    setSelectedProvider();
    // alert ("selectedProv = " + selectedProv) ;

    var selectedProvString;
    if(VerifyProvider(selectedProv) == true)
    {
		if(browserNum < 5)
		{
			selectedProvString = new java.lang.String(selectedProv) ;
		}
		else
		{
			selectedProvString = new String(selectedProv) ;
		}
    }
    else
    {
		if(browserNum < 5)
		{
			selectedProvString = new java.lang.String("Microsoft Base Cryptographic Provider v1.0") ;
		}
		else
		{
			selectedProvString = new String("Microsoft Base Cryptographic Provider v1.0") ;
		}
    }
 
    // Set the Cryptographic Provider
    document.NSCP_IVSPTA.set_XEnroll_ProviderName(selectedProvString) ;
    if ( (ErrorCode = document.NSCP_IVSPTA.GetLastError()) != 0)
    {
      alert ("Error in NSCP_IVSPTA.set_XEnroll_ProviderName : " + ErrorCode) ;
      return false;
    }

    // Set the Cryptographic Provider Type
    document.NSCP_IVSPTA.set_XEnroll_ProviderType(1) ;
    if ( (ErrorCode = document.NSCP_IVSPTA.GetLastError()) != 0)
    {
      alert ("Error in NSCP_IVSPTA.set_XEnroll_ProviderType : " + ErrorCode) ;
      return false;
    }

    // Set the Hash Algorithm
    document.NSCP_IVSPTA.set_XEnroll_HashAlgorithm("MD5") ;
    if ( (ErrorCode = document.NSCP_IVSPTA.GetLastError()) != 0)
    {
      alert ("Error in NSCP_IVSPTA.set_XEnroll_HashAlgorithm : " + ErrorCode) ;
      return false;
    }

    // Set the Key Spec
    document.NSCP_IVSPTA.set_XEnroll_KeySpec(1) ;
    if ( (ErrorCode = document.NSCP_IVSPTA.GetLastError()) != 0)
    {
      alert ("Error in NSCP_IVSPTA.set_XEnroll_KeySpec : " + ErrorCode) ;
      return false;
    }

    //-- VSSKBEGIN Enrollment/KeyProtect#3 --    
    //--VSSKEND Enrollment/KeyProtect#3 --

    //-- VSSKBEGIN Enrollment/KeyExportable#2 --
    //--VSSKEND Enrollment/KeyExportable#2 --

    document.proform.public_key.value = CreateP10Java(KeyFlags) ;
    if ( document.proform.public_key.length == 0 )
       self.location="../error/nsbrwerr.htm";

    // alert("document.proform.public_key.value : \n" + document.proform.public_key.value) ;
    return true;
  }
//-->
</script>
<!-- VSSKENDPOLICYVAL#microsoft#5 -->


// for userEnroll*.htm
<!-- VSSKBEGINPOLICYVAL#microsoft#6 -->
  <Script Language="JavaScript">
  <!-- 
     DetectCryptProv();
  //-->
  </script>
<!-- VSSKENDPOLICYVAL#microsoft#6 -->

# show the CSP and Key protection selection UI on NS enroll pages.
<!-- VSSKBEGINPOLICYVAL#microsoft#7 -->
  <!-- VSSKBEGIN Enrollment/CSP#4 -->
  <!-- VSSKEND Enrollment/CSP#4 -->

  <!-- VSSKBEGIN Enrollment/KeyProtect#1 -->
  <!-- VSSKEND Enrollment/KeyProtect#1 -->
<!-- VSSKENDPOLICYVAL#microsoft#7 -->

#include the PTA plugin for Generating MS keys 
<!-- VSSKBEGINPOLICYVAL#microsoft#8#1.2.0.4 -->
<EMBED type="application/x-vspta2-plugin" name="ThePlugin" WIDTH=0 HEIGHT=0 HIDDEN>
<!-- VSSKENDPOLICYVAL#microsoft#8 -->

<!-- VSSKBEGINPOLICYVAL#microsoft#9#1.2.0.4 -->
				InitPlugin();
                rval = GenerateP10Java();
<!-- VSSKENDPOLICYVAL#microsoft#9 -->

<!-- VSSKBEGINPOLICYVAL#microsoft#10#1.2.0.7 -->
<!-- Check for PTA plugin version -->
<SCRIPT LANGUAGE="JavaScript">
  var len;
  var name;
  var description;
  var found = 0;

//-- VSSKBEGIN Global/Mode#122 --
//-- VSSKEND Global/Mode#122 --

  navigator.plugins.refresh(true);

  len = navigator.plugins.length;
  for(i=0;i<len;++i)
  {
        name = navigator.plugins[i].name;
        description = navigator.plugins[i].description;
        if(name.search("Symantec Personal Trust Agent") != -1)
        {
          if (browserNum < 5) {
            if ( description >= 3028 )
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
//-- VSSKBEGIN Global/Mode#102 --
//-- VSSKEND Global/Mode#102 --

</SCRIPT>
<!-- VSSKENDPOLICYVAL#microsoft#10 -->


<!-- VSSKBEGINPOLICYVAL#microsoft#11#1.0.0.1 -->
<SCRIPT LANGUAGE="VBScript">
<!--
  Sub InstallCert
  	Dim TPMEnabled
	Dim boolTPMAvailable
	Dim strAppCtxtName

        spnCertEnroll.innerHTML="<OBJECT id='g_objClassFactory' CLASSID='clsid:884e2049-217d-11da-b2a4-000e7bbb2b09'></OBJECT>"

	boolTPMAvailable = CBool(0)
	TPMEnabled = "%%Apps/PTAv2::ptaTPMOption%%"

	strAppCtxtName = "%%Apps/PTAv2::ptaAppName%%"
	
	On Error Resume Next
	if(TPMEnabled = "CHECKED") then
		boolTPMAvailable = IVSPTA.IsTPMAvailable 
	End If
	if(TPMEnabled = "CHECKED" And boolTPMAvailable = "True") then
		On Error Resume Next
		IVSPTA.Initialize strAppCtxtName,2
		If ( err.number <> 0 ) then
		  'MsgBox "Error in IVSPTA.PTA_Initialize." & vbCRLF & _
		  '			"Error Number : 0x" & CStr(Hex(err.number))
		  Call CloseObjects(Hex(err.number), "Digital ID Install::IVSPTA.Initialize", Hex(err.number))      
		  Exit Sub
		End If
		 On Error Resume Next
			IVSPTA.InstallCert CertChain
			if (err.number <> 0) then
						Call CloseObjects(Hex(err.number), "Digital ID Install::IVSPTA.InstallCert", Hex(err.number))
				Exit Sub
			end if
	else
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

	End If
  '-- VSSKBEGIN Apps/GSE#62 --
  '-- VSSKEND Apps/GSE#62 --
  End Sub
'-->
</SCRIPT>
<!-- VSSKENDPOLICYVAL#microsoft#11 -->


// for userEnrollNS.fdf
<!-- VSSKBEGINPOLICYVAL#microsoft#12 -->
STATUS		   0		VSApps/client/userInstallNSpta.htm
STATUS		6FFF		VSApps/client/userInstallNSpta.htm
<!-- VSSKENDPOLICYVAL#microsoft#12 -->

// for userEnroll*.fdf
<!-- VSSKBEGINPOLICYVAL#microsoft#13 -->
CONST     public_key_format       pkcs10
# VSSKBEGIN Apps/AuthBureau#1
# VSSKEND Apps/AuthBureau#1
<!-- VSSKENDPOLICYVAL#microsoft#13 -->

// for userGetIDNS.fdf
<!-- VSSKBEGINPOLICYVAL#microsoft#14 -->
<!-- VSSKENDPOLICYVAL#microsoft#14 -->

// key manager should deliver files in pkcs8 format for firefox 
// enrollments if not a native NS cert store
<!-- VSSKBEGINPOLICYVAL#microsoft#15 -->
CONST     key_format           pkcs8
<!-- VSSKENDPOLICYVAL#microsoft#15 -->

// for userEnrollDualNS.fdf
<!-- VSSKBEGINPOLICYVAL#microsoft#16 -->
STATUS		   0		VSApps/client/userInstallDualNSpta.htm
STATUS		6FFF		VSApps/client/userInstallDualNSpta.htm
<!-- VSSKENDPOLICYVAL#microsoft#16 -->

// for userEnrollEncNS.fdf
<!-- VSSKBEGINPOLICYVAL#microsoft#17 -->
STATUS		   0		VSApps/client/userInstallEncNSpta.htm
STATUS		6FFF		VSApps/client/userInstallEncNSpta.htm
<!-- VSSKENDPOLICYVAL#microsoft#17 -->


// for userRenewalNS.fdf
<!-- VSSKBEGINPOLICYVAL#microsoft#18 -->
STATUS		6FFF		VSApps/client/userRenewalInstallNSpta.htm
<!-- VSSKENDPOLICYVAL#microsoft#18 -->

//for userEnrollEncNS.htm and userEnrollDualNS.htm
<!-- VSSKBEGINPOLICYVAL#microsoft#19 -->
                rval = true;
<!-- VSSKENDPOLICYVAL#microsoft#19 -->


<!-- VSSKBEGINPOLICYVAL#microsoft#20 -->
<!-- VSSKENDPOLICYVAL#microsoft#20 -->

// for userEnrollEncNS.htm
<!-- VSSKBEGINPOLICYVAL#microsoft#21 -->
<!-- VSSKENDPOLICYVAL#microsoft#21 -->

<!-- VSSKBEGINPOLICYVAL#microsoft#22 -->
<!-- VSSKBEGIN Global/Mode#19 -->
<!-- VSSKEND Global/Mode#19 -->
<!-- VSSKENDPOLICYVAL#microsoft#22 -->

//-- the key manager import control
<!-- VSSKBEGINPOLICYVAL#microsoft#23 -->
<!-- VSSKBEGIN Global/Mode#22 -->
<!-- VSSKEND Global/Mode#22 -->
<!-- VSSKENDPOLICYVAL#microsoft#23 -->

<!-- VSSKBEGINPOLICYVAL#microsoft#24#2.0.0.2 -->
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
<!-- VSSKENDPOLICYVAL#microsoft#24 -->

<!-- VSSKBEGINPOLICYVAL#microsoft#25#2.0.0.2 -->
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
    'MsgBox "Called InstallSigningCert on Vista
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
<!-- VSSKENDPOLICYVAL#microsoft#25 -->

<!-- VSSKBEGINPOLICYVAL#microsoft#26 -->
                document.proform.submit();
<!-- VSSKENDPOLICYVAL#microsoft#26 -->

<!-- VSSKBEGINPOLICYVAL#microsoft#27 -->
<!-- VSSKENDPOLICYVAL#microsoft#27 -->

<!-- VSSKBEGINPOLICYVAL#microsoft#28#1.2.0.4 -->
   if(browserNum < 5){
	if (document.ThePlugin == null) {
		   SetErrorInfo ("../fdf/VSApps/client/PTAv2Errors.fdf", "00000101", 0, "The plugin instance is NULL");
	}
   }
<!-- VSSKENDPOLICYVAL#microsoft#28 -->


<!-- VSSKBEGINPOLICYVAL#microsoft#29#1.0.0.3 -->
<!-- Check for PTA plugin version -->
<SCRIPT Language="JavaScript">
<!--
var Result;
//alert ("calling smart update script");
if ( navigator.javaEnabled() ) {

   trigger = netscape.softupdate.Trigger;
   if ( trigger.UpdateEnabled() ) {

      if (navigator.platform == "Win32") {
         vi = new netscape.softupdate.VersionInfo(3, 0, 2, 8);
         //-- VSSKBEGIN Enrollment/CertStore#30 -- 
         //-- VSSKEND Enrollment/CertStore#30 -- 
      }
      else alert("This plug-in only runs on Windows NT/95.");
   }
   else
      alert("Enable SmartUpdate before running this script.");
}
else 
   alert("Enable Java before running this script.");
//-->
</SCRIPT>
<!-- VSSKENDPOLICYVAL#microsoft#29 -->


<!-- VSSKBEGINPOLICYVAL#microsoft#30 -->
            //-- VSSKBEGIN Global/Mode#104 --
            //-- VSSKEND Global/Mode#104 --
<!-- VSSKENDPOLICYVAL#microsoft#30 -->

<!-- VSSKBEGINPOLICYVAL#microsoft#31 -->
<!-- VSSKENDPOLICYVAL#microsoft#31 -->

<!-- VSSKBEGINPOLICYVAL#microsoft#32 -->
<!-- VSSKENDPOLICYVAL#microsoft#32 -->

<!-- VSSKBEGINPOLICYVAL#microsoft#33#1.2.0.4 -->
<script language = "JavaScript">
<!--
	GoToHome();
//-->
</script>
<!-- VSSKENDPOLICYVAL#microsoft#33 -->

<!-- VSSKBEGINPOLICYVAL#microsoft#34 -->
<!-- VSSKENDPOLICYVAL#microsoft#34 -->

<!-- VSSKBEGINPOLICYVAL#microsoft#35#1.2.0.4 -->
	xpi={'Symantec Personal Trust Agent':'../vspta3km.xpi'};
    InstallTrigger.install(xpi,xpinstallCallback);
<!-- VSSKENDPOLICYVAL#microsoft#35 -->

<!-- VSSKBEGINPOLICYVAL#microsoft#36 -->
<!-- VSSKENDPOLICYVAL#microsoft#36 -->


<!-- VSSKBEGINPOLICYVAL#microsoft#37 -->
<SCRIPT Language="VBScript">
<!--
    On Error Resume Next
    Set bExportable = Import.KeyExportable
	If ( (Hex(err.number) = "1B6") AND (InStr(1,navigator.appMinorVersion,";SP2;") > 0)  ) Then
         window.location = "./client/installComponentForSP2.htm"
    End If
-->
</SCRIPT>
<!-- VSSKENDPOLICYVAL#microsoft#37 -->
<!-- VSSKBEGINPOLICYVAL#microsoft#38 -->
try{
	dummy=Import.getName();
	temp = 1;
}catch(er){
	temp=0;
	window.open("../vsapps/error/win2k.htm","_self");
}
<!-- VSSKENDPOLICYVAL#microsoft#38 -->

<!-- VSSKBEGINPOLICYVAL#microsoft#39 -->
<!-- VSSKBEGIN Global/Mode#128 -->
<!-- VSSKEND Global/Mode#128 -->
<!-- VSSKENDPOLICYVAL#microsoft#39 -->
