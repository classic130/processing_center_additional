<!-- VSSKBEGINPOLICYVAL#microsoft#1 -->
<!-- VSSKBEGIN Global/Mode#19 -->
<!-- VSSKEND Global/Mode#19 -->
<!-- VSSKENDPOLICYVAL#microsoft#1 -->


<!-- VSSKBEGINPOLICYVAL##microsoft#2#1.0.0.2 -->
<SCRIPT LANGUAGE="VBScript">
<!--
  '-- VSSKBEGIN Renewal/CSP#3 --
  '-- VSSKEND Renewal/CSP#3 --

Function CreateP10( keyflags )
 On Error Resume Next
 CreateP10 = ""

 spnCertEnroll.innerHTML="<OBJECT id='g_objClassFactory' CLASSID='clsid:884e2049-217d-11da-b2a4-000e7bbb2b09'></OBJECT>"

'-- VSSKBEGIN Renewal/KeyLength#1 --
'-- VSSKEND Renewal/KeyLength#1 --
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
    set theForm = document.theform
    'theForm.submit.disabled = true
    ' VSSKTEST - commented out for testing purposes...the document is not submitted 
    ' to the server.
    if(TPMEnabled = "CHECKED" And boolTPMAvailable = "True") then
		On Error Resume Next

		IVSPTA.Initialize strAppCtxtName,2
		' Create the PKCS 10
		theForm.public_key.value = CreatePKCS10()
    else

	        '-- VSSKBEGIN Renewal/CSP#2 --
	        '-- VSSKEND Renewal/CSP#2 --

    If isRunningOnVista = 0 Then
	        cenroll.HashAlgorithm = "MD5"
	        cenroll.KeySpec = 1
    End If

	        '-- VSSKBEGIN Renewal/KeyProtect#2 --
	        '-- VSSKEND Renewal/KeyProtect#2 --

	        '-- VSSKBEGIN Renewal/KeyExportable#1 --
	        '-- VSSKEND Renewal/KeyExportable#1 --

	        theForm.public_key.value = CreateP10(keyflags)
    End If
    
    if Len(theForm.public_key.value) = 0 then
      MsgBox("The error: " + hex(err.number) + " occured in generating certificate request")
        window.navigate("../error/MSkeygenerr.htm")
    end if
  End Sub
'-->
</SCRIPT>
<!-- VSSKENDPOLICYVAL#microsoft#2 -->


<!-- VSSKBEGINPOLICYVAL#microsoft#3 -->
<!-- VSSKBEGIN Renewal/CSP#1 -->
<!--VSSKEND Renewal/CSP#1 -->

<P><BR><P>

<!-- VSSKBEGIN Renewal/KeyProtect#1 -->
<!-- VSSKEND Renewal/KeyProtect#1 -->

<!-- VSSKBEGIN Renewal/CertPublish#1 -->
<!-- VSSKEND Renewal/CertPublish#1 -->
<!-- VSSKENDPOLICYVAL#microsoft#3 -->


<!-- VSSKBEGINPOLICYVAL#microsoft#4#1.0.0.1 -->
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
		Dim sz10
		sz10 = CertChain
        If isRunningOnVista = 0 Then
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
			 'Call StopIt()
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
<!-- VSSKENDPOLICYVAL#microsoft#4 -->

#include the PTA plugin for Generating Verisign keys 
<!-- VSSKBEGINPOLICYVAL#microsoft#5#1.2.0.4 -->
<EMBED type="application/x-vspta2-plugin" name="ThePlugin" WIDTH=0 HEIGHT=0 HIDDEN>
<!-- VSSKENDPOLICYVAL#microsoft#5 -->



// for userRenewalNS.htm
<!-- VSSKBEGINPOLICYVAL#microsoft#6#1.2.0.7 -->
<SCRIPT LANGUAGE="JavaScript">
<!--
  var PKCS10;

  //-- VSSKBEGIN Apps/PTAv2#21 --
  //-- VSSKEND Apps/PTAv2#21 --
 
 function InitPlugin()
 {
	if(browserNum < 5) {
		document.NSCP_IVSPTA = document.ThePlugin;
	} else {
		document.NSCP_IVSPTA = document.ThePlugin.ns6IPTA;
	}
 }
 
 function CloseObjects(errCode, Operation, WinErrorCode)
 {
    RetVal = document.NSCP_IVSPTA.PTA_Close ();
    if (errCode != 0) {
        SetErrorInfo ("../fdf/VSApps/client/PTAv2Errors.fdf", ReBaseErrorCodeNS(errCode), ConvertToHexNS(WinErrorCode), Operation);
    }   
    if ( (ErrorCode = document.NSCP_IVSPTA.GetLastError()) != 0) {    
      SetErrorInfo ("../fdf/VSApps/client/PTAv2Errors.fdf", "00000001", ConvertToHexNS(ErrorCode), "NSCP_IVSPTA.PTA_Close");
    }
     return;
 }
   
  //-- VSSKBEGIN Renewal/CSP#6 --  
  //-- VSSKEND Renewal/CSP#6 --

 //-- VSSKBEGIN Renewal/KeyLength#2 --
 //-- VSSKEND Renewal/KeyLength#2 --

  function GenerateP10Java()
  {
    var KeyFlags;
    KeyFlags = 0;

    //alert("Generating the key-pair");

    //document.NSCP_IVSPTA.PTA_Initialize("",1) ;
    //if ( (ErrorCode = document.NSCP_IVSPTA.GetLastError()) != 0)
    //{
    //  alert ("Error in NSCP_IVSPTA.PTA_Initialize : " + ErrorCode) ;
    //  return ;
    //}

    // alert("Inside GenerateP10Java ...") ;
    // alert ("selectedProv = " + selectedProv) ;
    
    if(browserNum < 5) {
		PKCS10 = new java.lang.StringBuffer("");
	}
	else {
		PKCS10 = new String("");
	}
	
    setSelectedProvider();

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
      CloseObjects(ErrorCode, "Renewal::NSCP_IVSPTA.set_XEnroll_ProviderName", ErrorCode);
      return -1;
    }

    // Set the Cryptographic Provider Type
    document.NSCP_IVSPTA.set_XEnroll_ProviderType(1) ;
    if ( (ErrorCode = document.NSCP_IVSPTA.GetLastError()) != 0)
    {
      CloseObjects(ErrorCode, "Renewal::NSCP_IVSPTA.set_XEnroll_ProviderType", ErrorCode);
      return -1;
    }

    // Set the Hash Algorithm
    document.NSCP_IVSPTA.set_XEnroll_HashAlgorithm("MD5") ;
    if ( (ErrorCode = document.NSCP_IVSPTA.GetLastError()) != 0)
    {
      CloseObjects(ErrorCode, "Renewal::NSCP_IVSPTA.set_XEnroll_HashAlgorithm", ErrorCode);
      return -1;
    }

    // Set the Key Spec
    document.NSCP_IVSPTA.set_XEnroll_KeySpec(1) ;
    if ( (ErrorCode = document.NSCP_IVSPTA.GetLastError()) != 0)
    {
      CloseObjects(ErrorCode, "Renewal::NSCP_IVSPTA.set_XEnroll_KeySpec", ErrorCode);
      return -1;
    }

    //-- VSSKBEGIN Renewal/KeyProtect#4 --    
    //--VSSKEND Renewal/KeyProtect#4 --

    //-- VSSKBEGIN Renewal/KeyExportable#2 --
    //--VSSKEND Renewal/KeyExportable#2 --

    document.Renewal.public_key.value = CreateP10Java(KeyFlags) ;
    if ( document.Renewal.public_key.length == 0 )
       self.location="../error/nsbrwerr.htm";

    //alert("document.Renewal.public_key.value : \n" + document.Renewal.public_key.value) ;

    //document.NSCP_IVSPTA.PTA_Close() ;
    //if ( (ErrorCode = document.NSCP_IVSPTA.GetLastError()) != 0)
    //{
      //alert ("Error in NSCP_IVSPTA.Initialize : " + ErrorCode) ;
    //  return -1;
    //}

    return 1;
  }

  // function to select the certificates
  function SelectAndSignJava()
  {
  
	if(browserNum < 5) {
		PKCS10 = new java.lang.StringBuffer("");
	}
	else {
		PKCS10 = new String("");
	}
	
    // Initialize the VSPTA Object
    document.NSCP_IVSPTA.PTA_Initialize(strAppCtxtName,1) ;
    if ( (ErrorCode = document.NSCP_IVSPTA.GetLastError()) != 0)
    {
      CloseObjects(ErrorCode, "Renewal::NSCP_IVSPTA.PTA_Initialize", ErrorCode);
      return -1 ;
    }

    // Initialize the IssuerDN
    document.NSCP_IVSPTA.set_SrchCrit_IssuerDN(strIssuerDN) ;
    if ( (ErrorCode = document.NSCP_IVSPTA.GetLastError()) != 0)
    {
      CloseObjects(ErrorCode, "Renewal::NSCP_IVSPTA.set_SrchCrit_IssuerDN", ErrorCode);
      return -1 ;
    }

    EXP_DATE_GREATER_THAN = 0x20 ;
    EXP_DATE_EQUALTO      = 0x10 ;
    EXP_DATE_LESS_THAN    = 0x08 ;
    EFF_DATE_GREATER_THAN = 0x04 ;
    EFF_DATE_EQUALTO      = 0x02 ;
    EFF_DATE_LESS_THAN    = 0x01 ;

    // Initialize the Certificate Search Criterion "Date Equality"
    document.NSCP_IVSPTA.set_SrchCrit_DateEquality(EXP_DATE_LESS_THAN) ;
    if ( (ErrorCode = document.NSCP_IVSPTA.GetLastError()) != 0)
    {
      CloseObjects(ErrorCode, "Renewal::NSCP_IVSPTA.set_SrchCrit_DateEquality", ErrorCode);
      return -1 ;
    }

    // Initialize the Certificate Search Criterion "Expiry Date"
    // to the CURRENT DATE.
    var StartDate;
    
    if(browserNum < 5)
    {
        StartDate = new java.util.Date();
    }
    else
    {
	StartDate = new Date();
    }
    var ShortStartDate = StartDate.getDate();
    ShortStartDate = ShortStartDate + AbtToExpWindow;
    StartDate.setDate ( ShortStartDate);
     
    if (browserNum >= 5) {
        StartDate = StartDate.getTime();
    }
   
    document.NSCP_IVSPTA.set_SrchCrit_ExpDate(StartDate) ;
    if ( (ErrorCode = document.NSCP_IVSPTA.GetLastError()) != 0)
    {
      CloseObjects(ErrorCode, "Renewal::NSCP_IVSPTA.set_SrchCrit_ExpDate", ErrorCode);
      return -1 ;
    }

    // set key usage criteria if necessary.
    if ( setKeyUsage == "true" ) {
       document.NSCP_IVSPTA.set_SrchCrit_KeyUsage(keyUsageFlag) ;
       if ( (ErrorCode = document.NSCP_IVSPTA.GetLastError()) != 0)
       {
          CloseObjects(ErrorCode, "Renewal::NSCP_IVSPTA.set_SrchCrit_KeyUsage", ErrorCode);
          return ;
       }
    }

    // Set the LogoURL associated with the Application Context
    if (strAppLogoUrl[0] != null){ 
        document.NSCP_IVSPTA.set_UIPrefs_UILogoUrl(strAppLogoUrl);
        if ( (ErrorCode = document.NSCP_IVSPTA.GetLastError()) != 0)
        {
          CloseObjects(ErrorCode, "Renewal::NSCP_IVSPTA.set_UIPref_LogoUrl", ErrorCode);
          return -1 ;
       }
    }
 
    if ( (strAffiliateLogoUrl[0] != null) && (strAffiliateLogoUrl != "VeriSign") ){
      document.NSCP_IVSPTA.set_PTA_AffLogoUrl(strAffiliateLogoUrl) ;
      if ( ((ErrorCode = document.NSCP_IVSPTA.GetLastError()) != 0) && (ErrorCode != 0x800010c4)) {
          CloseObjects(ErrorCode, "Renewal::NSCP_IVSPTA.set_PTA_AffLogoUrl", ErrorCode);
          return -1;
      }
    }

    // set the UI preferences
    if (strRenewTitle[0] != null){
        document.NSCP_IVSPTA.set_UIPrefs_SelID_Title(strRenewTitle) ;
        if ( (ErrorCode = document.NSCP_IVSPTA.GetLastError()) != 0) {
           CloseObjects(ErrorCode, "Renewal::NSCP_IVSPTA.set_UIPrefs_SelID_Title", ErrorCode);
           return -1;
        }
    }


    // set the UI preferences
    if (strRenewText[0] != null){
        document.NSCP_IVSPTA.set_UIPrefs_SelID_Text(strRenewText) ;
        if ( (ErrorCode = document.NSCP_IVSPTA.GetLastError()) != 0) {
           CloseObjects(ErrorCode, "Renewal::NSCP_IVSPTA.set_UIPrefs_SelID_Text", ErrorCode);
           return -1;
        }
    }

    // set the UI preferences
    if (strRenewHelpUrl[0] != null){
        document.NSCP_IVSPTA.set_UIPrefs_SelID_HelpUrl(strRenewHelpUrl) ;
        if ( (ErrorCode = document.NSCP_IVSPTA.GetLastError()) != 0) {
           CloseObjects(ErrorCode, "Renewal::NSCP_IVSPTA.set_UIPrefs_SelID_HelpUrl", ErrorCode);
           return -1;
        }
    }

    document.NSCP_IVSPTA.set_UIPrefs_SelID_OKBtnText(127) ;
    if ( (ErrorCode = document.NSCP_IVSPTA.GetLastError()) != 0) {
      CloseObjects(ErrorCode, "Renewal::NSCP_IVSPTA.set_UIPrefs_SelID_OKBtnText", ErrorCode);
      return -1;
    }

    document.NSCP_IVSPTA.set_UIPrefs_SelID_ShowDefChkBox(false) ;
    if ( (ErrorCode = document.NSCP_IVSPTA.GetLastError()) != 0) {
      CloseObjects(ErrorCode, "Renewal::NSCP_IVSPTA.set_UIPrefs_SelID_ShowDefChkBox", ErrorCode);
      return -1;
    }

    MD5 = 3 ;
    SHA1 = 4 ;
    
    // Select the Digital ID now
    var Signature = document.NSCP_IVSPTA.PTA_SignRenewal(MD5) ;

    VS_CERTNOMATCHCRIT = 0x80001095;
    VS_CERTMATCHBUTEXP = 0x80001096;
    VS_SUCCESS = 0x00000000;
    VS_PROFDOESNOTEXIST = 0x8000102B;
    VS_USER_CANCELLED = 0x80001067;
    VS_CERTNOTFOUND = 0x80001091;

    //alert("Signature is : " + Signature);
    var RetVal =  document.NSCP_IVSPTA.GetLastError();
    
    if (RetVal != VS_SUCCESS) {
       CloseObjects(0, "", 0);
       if ( document.referrer.indexOf('digitalidCenter.htm') != -1 ) {
          if ( (RetVal == VS_CERTNOMATCHCRIT) || (RetVal == VS_PROFDOESNOTEXIST) || (RetVal == VS_CERTNOTFOUND) || (RetVal == VS_CERTMATCHBUTEXP)) {
              alert("No Renewable Digital IDs could be found!");
              self.location="../digitalidCenter.htm";              
          } else if ( RetVal == VS_USER_CANCELLED ) {
              self.location="../digitalidCenter.htm";
          } else {
              alert ("Error in selecting a Digital ID");
          }
       }
       else {  
          // if the referrer page is not digitalidCenter.htm
          if ( (RetVal == VS_CERTNOMATCHCRIT) || (RetVal == VS_PROFDOESNOTEXIST) || (RetVal == VS_CERTNOTFOUND)) {
             RenewState = confirm ("No Digital IDs were found that could be used with this application.\nWould you like to Get a Digital ID ?") ;
             if ( RenewState == true )
             {
                //-- VSSKBEGIN Apps/KeyManager#11 --
                //-- VSSKEND Apps/KeyManager#11 --
                self.location = EnrollPage;
             } else {
                alert("No Renewable Digital IDs could be found!");
                self.location = strPtaHomeUrl;
             }
           } else if (RetVal == VS_USER_CANCELLED) {
                self.location = strPtaHomeUrl;  
           } else {
                alert("Error in selecting a Digital ID");
           }
       }
       return -1;
    } else {
      // This sets the signature which has the certificate that needs renewal
      document.Renewal.pkcsInformation.value = Signature ;
      // Get Serial Number of Certificate that needs renewal
      CertSerialNumber = document.NSCP_IVSPTA.get_SelectedDigID_SerNum() ;
      if ( (ErrorCode = document.NSCP_IVSPTA.GetLastError()) != 0)
      {
        CloseObjects(ErrorCode, "Renewal::NSCP_IVSPTA.get_SelectedDigId_SerNum", ErrorCode);
        return -1;
      }
      document.Renewal.orig_cert_serial.value = CertSerialNumber ;
  
      // Get Issuer DN of Certificate that needs renewal
      IssuerDN = document.NSCP_IVSPTA.get_SelectedDigID_IssuerDN() ;
      if ( (ErrorCode = document.NSCP_IVSPTA.GetLastError()) != 0)
      {
        CloseObjects(ErrorCode, "Renewal::NSCP_IVSPTA.get_SelectedDigId_IssuerDN", ErrorCode);
        return -1;
      }
      document.Renewal.orig_cert_issuerdn.value = IssuerDN ;
      CloseObjects(0, "", 0);
      //document.NSCP_IVSPTA.PTA_Close();

      //alert ( "Signature : " + Signature + "\nSerial no :" + CertSerialNumber + "\nMsgg :" + Msgg + "\nIssuer DN :" + IssuerDN );
      return 1;
    }
  } // end function SelectRenewal...
//-->
</script>
<!-- VSSKENDPOLICYVAL#microsoft#6 -->


// for userEnroll*.htm
<!-- VSSKBEGINPOLICYVAL#microsoft#7 -->
  <Script Language="JavaScript">
  <!-- 
     DetectCryptProv();
  //-->
  </script>
<!-- VSSKENDPOLICYVAL#microsoft#7 -->

// for userRenewalNS.htm
<!-- VSSKBEGINPOLICYVAL#microsoft#8 -->
<INPUT TYPE=hidden NAME=getMethod VALUE="pkcs7">
<INPUT TYPE=hidden NAME=orig_cert_serial VALUE="$$orig_cert_serial$$">  
<INPUT TYPE=hidden NAME=orig_cert_issuerdn VALUE="$$orig_cert_issuerdn$$">
<INPUT TYPE=hidden NAME=pkcsInformation VALUE="$$pkcsInformation$$">
<INPUT TYPE=hidden NAME=detachedMesg VALUE="$$detachedMesg$$">
<INPUT TYPE=hidden NAME=public_key VALUE="">
<!-- VSSKENDPOLICYVAL#microsoft#8 -->

 
<!-- VSSKBEGINPOLICYVAL#microsoft#9#1.2.0.5 -->
     var RetVal = true;
     var serNum = document.Renewal.orig_cert_serial.value;
     
     InitPlugin();
     
     if( serNum.indexOf ('$orig_cert_serial$') != -1)
     {
         document.Renewal.pkcsInformation.value = "";
         SelectAndSignJava();
         document.Renewal.detachedMesg.value = "Renew Digital ID";
     }
     var Sig = document.Renewal.pkcsInformation.value;
     RetVal = true;
     if( Sig.length == 0) {
        RetVal = false;
     } else {
          if( Sig.indexOf ('$pkcsInformation$') == -1) {
              RetVal=GenerateP10Java();
          }
    } 
    if (RetVal==true) {
      document.Renewal.submit();
      document.Renewal.Accept.disabled = true;
      isRenewInProcess = true;
    } else {
      return false;
    } 
<!-- VSSKENDPOLICYVAL#microsoft#9 -->


// for userRenewalNS.htm
<!-- VSSKBEGINPOLICYVAL#microsoft#10 -->
  <!-- VSSKBEGIN Renewal/CSP#5 -->
  <!-- VSSKEND Renewal/CSP#5 -->

  <!-- VSSKBEGIN Renewal/KeyProtect#1 -->
  <!-- VSSKEND Renewal/KeyProtect#1 -->

  <!-- VSSKBEGIN Renewal/CSP#7 -->
  <!-- VSSKEND Renewal/CSP#7 --> 
<!-- VSSKENDPOLICYVAL#microsoft#10 -->


<!-- VSSKBEGINPOLICYVAL#microsoft#11#1.2.0.7 -->
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
<!-- VSSKENDPOLICYVAL#microsoft#11 -->

<!-- VSSKBEGINPOLICYVAL#microsoft#12#1.2.0.4 -->
if(browserNum < 5) {
   if (document.ThePlugin == null) {
       SetErrorInfo ("../fdf/VSApps/client/PTAv2Errors.fdf", "00000101", 0, "The plugin instance is NULL");
   }
}
<!-- VSSKENDPOLICYVAL#microsoft#12 -->

<!-- VSSKBEGINPOLICYVAL#microsoft#13 -->
<!-- VSSKBEGIN Apps/PTAv2#19 -->
<!-- VSSKEND Apps/PTAv2#19 -->
<!-- VSSKENDPOLICYVAL#microsoft#13 -->

// for userRenewalSignNS.fdf
<!-- VSSKBEGINPOLICYVAL#microsoft#14 -->
STATUS		0		VSApps/client/userRenewalInstallNSpta.htm
STATUS		6FFF		VSApps/client/userRenewalInstallNSpta.htm
<!-- VSSKENDPOLICYVAL#microsoft#14 -->

// for userRenewalEncNS.fdf
<!-- VSSKBEGINPOLICYVAL#microsoft#15 -->
STATUS		   0		VSApps/client/userRenewalInstallEncNSpta.htm
STATUS		6FFF		VSApps/client/userRenewalInstallEncNSpta.htm
<!-- VSSKENDPOLICYVAL#microsoft#15 -->

<!-- VSSKBEGINPOLICYVAL#microsoft#16 -->
<!-- VSSKBEGIN Apps/PTAv2#33 -->
<!-- VSSKEND Apps/PTAv2#33 -->
<!-- VSSKENDPOLICYVAL#microsoft#16 -->
