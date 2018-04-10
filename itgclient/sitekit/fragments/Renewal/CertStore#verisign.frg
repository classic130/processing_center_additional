<!-- VSSKBEGINPOLICYVAL#verisign#1 -->
<!-- the PTA control not be required for key gen -->
<!-- VSSKBEGIN Global/Mode#19 -->
<!-- VSSKEND Global/Mode#19 -->
<!-- VSSKENDPOLICYVAL#verisign#1 -->

<!-- VSSKBEGINPOLICYVAL#verisign#2#1.0.0.1 -->
<SCRIPT LANGUAGE="VBScript">
<!--  

  Sub FindProviders

  End Sub

  Function  CreatePKCS10
    On Error Resume Next
    CreatePKCS10 = ""
    SubjectDN = "CN=vsc1enroll"
    HashAlg = CInt(4)
    
    'need to handle key exportability and key strength policies
    KeyFlags = &h00000001   'KEY SPEC = AT_KEYEXCHANGE
    
    '-- VSSKBEGIN Renewal/KeyExportable#3 --
    '-- VSSKEND Renewal/KeyExportable#3 --

    Dim Attributes(2,2)
    Attributes(1,1) = "2.5.29.15"
    Attributes(1,2) = "03020138"
    Attributes(2,1) = "2.5.29.37"	
    Attributes(2,2) = "300A06082B06010505070302"

    '-- VSSKBEGIN Renewal/KeyLength#4 --
    '-- VSSKEND Renewal/KeyLength#4 --
  End Function
  
  Sub DoKeyGen
    Dim boolProfileOpen
    Dim profileName
    Dim theForm 


	Dim TPMEnabled
	Dim boolTPMAvailable

	boolTPMAvailable = CBool(0)
	TPMEnabled = "%%Apps/PTAv2::ptaTPMOption%%"
	
	On Error Resume Next
	if(TPMEnabled = "CHECKED") then
		boolTPMAvailable = IVSPTA.IsTPMAvailable 
	End If  
	
	set theForm = document.theform
    'theForm.Accept.disabled = true

	if(TPMEnabled = "CHECKED" And boolTPMAvailable = "True") then
		' Initialize the PTA Object
		On Error Resume Next

		IVSPTA.Initialize strAppCtxtName,2
		If ( err.number <> 0 ) then
		  Call CloseObjects(Hex(err.number), "Renewal::IVSPTA.Initialize", Hex(err.number))
		  Exit Sub
		End If

		' Create the PKCS 10
		theForm.public_key.value = CreatePKCS10()
		if (Hex(err.number) = "80001067" ) Then 
			Call CloseObjects(0, "", 0)
			MsgBox "You have cancelled the operation at this time. Click Accept again if you want to continue with the enrollment."
			Exit Sub
		End if 
		If (err.number <> 0) Then
			Call CloseObjects(Hex(err.number), "Renewal::IVSProfMgmt.CreatePKCS10", Hex(err.number))
			Exit Sub
		End If
	else        
		' the profile should be open at this point opened during select Digital ID. there is a probability that the profile is 
		' not open, so ask the user to open it. 
		' open profile etc.
		' Initialize the PTA Object
		On Error Resume Next
		IVSPTA.Initialize strAppCtxtName,0
		If ( err.number <> 0 ) then
			Call CloseObjects(Hex(err.number), "Renewal::IVSPTA.Initialize", Hex(err.number))
			Exit Sub
		End If

		'MsgBox "PTA Initialized"
    
			
		'Flags
		 OPENPROF_OPEN_ONLY = CInt(529)
		 On Error Resume Next
		 IVSProfMgmt.OpenProfFlags = OPENPROF_OPEN_ONLY
		 If ((err.number <> 0) And (Hex(err.number) <> "8000102F") ) Then
		   Call CloseObjects(Hex(err.number), "Renewal::IVSProfMgmt.OpenProfFlags", Hex(err.number))
		   Exit Sub
		 End If

		 '-- VSSKBEGIN Apps/PTAv2/Roaming#3 --
		 '-- VSSKEND Apps/PTAv2/Roaming#3 --
			
		 'open the profile 
		 On Error Resume Next
		 IVSProfMgmt.OpenProfile
		 if (Hex(err.number) = "80001067") Then
			   Call CloseObjects(Hex(err.number), "Renewal::IVSProfMgmt.OpenProfile", Hex(err.number))
			   Exit Sub
		 end if 
		 if ( (err.number <> 0) And (Hex(err.number) <> "8000102F") ) then
			   Call CloseObjects(Hex(err.number), "Renewal::IVSProfMgmt.OpenProfile", Hex(err.number))
		   Exit Sub
		 End If 
    
    
		' Create the PKCS 10
		theForm.public_key.value = CreatePKCS10()

		On Error Resume Next
		IVSProfMgmt.SaveProfile
		If (err.number <> 0) Then
			   Call CloseObjects(Hex(err.number), "Renewal::IVSProfMgmt.SaveProfile", Hex(err.number))
			   Exit Sub 
		End If
	End If
    Call CloseObjects(0, "", "")
    
    ' set the public key and submit the form.
    if Len(theForm.public_key.value) = 0 then
      Call SetErrorInfo("../fdf/VSApps/client/PTAv2Errors.fdf", CheckErrorCodeMS(Hex(err.number)), "Renewal::Key Generation", Hex(err.number))
    end If
  End Sub
'-->
</SCRIPT>
<!-- VSSKENDPOLICYVAL#verisign#2 -->

<!-- VSSKBEGINPOLICYVAL#verisign#3 -->
<!-- VSSKENDPOLICYVAL#verisign#3 -->

<!-- VSSKBEGINPOLICYVAL#verisign#4 -->
<SCRIPT LANGUAGE="VBScript">
<!--
  ' the cert is available in the variable CertChain
  Sub InstallCert
 
  End Sub
'-->
</SCRIPT>
<!-- VSSKENDPOLICYVAL#verisign#4 -->

#include the PTA plugin for Generating Verisign keys 
<!-- VSSKBEGINPOLICYVAL#verisign#5#1.2.0.4 -->
<EMBED type="application/x-vspta2-plugin" name="ThePlugin" WIDTH=0 HEIGHT=0 HIDDEN>
<!-- VSSKENDPOLICYVAL#verisign#5 -->


// for userRenewalNS.htm
<!-- VSSKBEGINPOLICYVAL#verisign#6#1.2.0.7 -->
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
      SetErrorInfo ("../fdf/VSApps/client/PTAv2Errors.fdf", ConvertToHexNS(ErrorCode), ConvertToHexNS(ErrorCode), "Renewal::NSCP_IVSPTA.PTA_Close");
    }
     return;
 }
   

 function CreateP10Java()
 {
   var KeyFlags=0x00000001;  // to generate AK_KEYEXCHANGE  keys
   var SubjectDN="CN=vsc1enroll";
   var HashAlg = 4;   // SHA1 as hash algorithm
   var theArray;
   
   if(browserNum < 5) {
	theClass = java.lang.Class.forName("java.lang.String")
	theArray = java.lang.reflect.Array.newInstance(theClass, 4);
	var temp = java.lang.String("2.5.29.15");
	java.lang.reflect.Array.set(theArray, 0, temp);
	temp = java.lang.String("03020138");
	java.lang.reflect.Array.set(theArray, 1, temp);
	temp = java.lang.String("2.5.29.37");
	java.lang.reflect.Array.set(theArray, 2, temp);
	temp = java.lang.String("300A06082B06010505070302");
	java.lang.reflect.Array.set(theArray, 3, temp);
   }
   else {
	theArray = new Array(4);
	theArray[0] = "2.5.29.15";
	theArray[1] = "03020138";
	theArray[2] = "2.5.29.37";
	theArray[3] = "300A06082B06010505070302";
   }
   
   //alert (theArray.toString());
   
   //-- VSSKBEGIN Renewal/KeyExportable#4 --
   //-- VSSKEND Renewal/KeyExportable#4 --
  
   // generate the public key
   //-- VSSKBEGIN Renewal/KeyLength#5 --
   //-- VSSKEND Renewal/KeyLength#5 --
   
   return (PKCS10) ;
 }


  function GenerateP10Java()
  {
    var KeyFlags;
    KeyFlags = 0;

    //alert("Generating the key-pair");
	if(browserNum < 5) {
		PKCS10 = new java.lang.StringBuffer("");
    } else {
		PKCS10 = new String("");
	}
   
    if (document.NSCP_IVSPTA == null) {
       SetErrorInfo ("../fdf/VSApps/client/PTAv2Errors.fdf", "00000101", 0, "The plugin instance is NULL");
    }

    if (strCertStore == "verisign") {
	  document.NSCP_IVSPTA.PTA_Initialize(strAppCtxtName, 0) ;
    }
    else {
	  document.NSCP_IVSPTA.PTA_Initialize(strAppCtxtName, 1) ;
    }	
    if ((ErrorCode = document.NSCP_IVSPTA.GetLastError()) != 0) {
        CloseObjects(ErrorCode, "Renewal::NSCP_IVSPTA.PTA_Initialize", ErrorCode);
        return false;
    }
   
    if (strCertStore == "verisign") {
        OPENPROF_OPEN_ONLY = 0x00000211;
        E_CARDALREADYOPEN = 0x8000102F;
        document.NSCP_IVSPTA.set_ProfMgmt_OpenProfFlags(OPENPROF_OPEN_ONLY) ;
        if ( ((ErrorCode = document.NSCP_IVSPTA.GetLastError()) != 0) && (ErrorCode != E_CARDALREADYOPEN )) {
           CloseObjects(ErrorCode, "Renewal::NSCP_IVSPTA.set_ProfMgmt_OpenProfFlags", ErrorCode);
           return false;
        }
  
        //-- VSSKBEGIN Apps/PTAv2/Roaming#5 -- 
        //-- VSSKEND Apps/PTAv2/Roaming#5 --
    }

    document.Renewal.public_key.value = CreateP10Java() ;
    ErrorCode = document.NSCP_IVSPTA.GetLastError();
    if (ErrorCode == 0x80001067) {
        CloseObjects(0, "", 0);
        alert ("You have cancelled this operation at this time. Click Accept again if you want to enroll.");
        return false;
    } else 
    if (ErrorCode != 0) {
        CloseObjects(ErrorCode, "Renewal::NSCP_IVSPTA.PTA_CreateCertReq", ErrorCode);
        return false;
    }
   
   document.NSCP_IVSPTA.ProfMgmt_SaveProfile() ;
   if ( (ErrorCode = document.NSCP_IVSPTA.GetLastError()) != 0 ) {
       CloseObjects(ErrorCode, "Renewal::NSCP_IVSPTA.ProfMgmt_SaveProfile", ErrorCode);
       return false;
   }

    CloseObjects(0, "", 0);
    if ( document.Renewal.public_key.length == 0 ){
        SetErrorInfo("../fdf/VSApps/client/PTAv2Errors.fdf", ReBaseErrorCodeNS(ErrorCode), "Renewal::KeyGeneration", ConvertToHexNS(ErrorCode));
        return false;
    }

    //alert("document.theform.public_key.value : \n" + document.theform.public_key.value) ;
    return true;
}


// function to select the certificates
function SelectAndSignJava()
{
    if (document.NSCP_IVSPTA == null) {
       SetErrorInfo ("../fdf/VSApps/client/PTAv2Errors.fdf", "00000101", 0, "The plugin instance is NULL");
    }

    // Initialize the VSPTA Object
    if (strCertStore == "verisign") {
	  document.NSCP_IVSPTA.PTA_Initialize(strAppCtxtName, 0) ;
    }
    else {
	  document.NSCP_IVSPTA.PTA_Initialize(strAppCtxtName, 1) ;
    }	
    if ((ErrorCode = document.NSCP_IVSPTA.GetLastError()) != 0) {
        CloseObjects(ErrorCode, "Renewal::NSCP_IVSPTA.PTA_Initialize", ErrorCode);
        return ;
    }

    // Initialize the IssuerDN
    document.NSCP_IVSPTA.set_SrchCrit_IssuerDN(strIssuerDN) ;
    if ( (ErrorCode = document.NSCP_IVSPTA.GetLastError()) != 0)
    {
      CloseObjects(ErrorCode, "Renewal::NSCP_IVSPTA.set_SrchCrit_IssuerDN", ErrorCode);
      return ;
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
      return ;
    }

    // Initialize the Certificate Search Criterion "Expiry Date"
    // to the CURRENT DATE.


    var StartDate;
    if(browserNum < 5) {
	StartDate = new java.util.Date(); 
    } else {
	StartDate = new Date(); 
    }
    var ShortStartDate = StartDate.getDate();
    ShortStartDate = ShortStartDate + AbtToExpWindow;
    StartDate.setDate ( ShortStartDate );

    if (browserNum >= 5) {
        StartDate = StartDate.getTime();
    }

    document.NSCP_IVSPTA.set_SrchCrit_ExpDate(StartDate) ;
    if ( (ErrorCode = document.NSCP_IVSPTA.GetLastError()) != 0)
    {
      CloseObjects(ErrorCode, "Renewal::NSCP_IVSPTA.set_SrchCrit_ExpDate", ErrorCode);
      return ;
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
          CloseObjects(ErrorCode, "Renewal::NSCP_IVSPTA.set_UIPrefs_UILogoUrl", ErrorCode);
          return ;
       }
    }

    if ( (strAffiliateLogoUrl[0] != null) && (strAffiliateLogoUrl != "VeriSign") ){
      document.NSCP_IVSPTA.set_PTA_AffLogoUrl(strAffiliateLogoUrl) ;
      if ( ((ErrorCode = document.NSCP_IVSPTA.GetLastError()) != 0) && (ErrorCode != 0x800010c4)) {
          CloseObjects(ErrorCode, "Renewal::NSCP_IVSPTA.set_PTA_AffLogoUrl", ErrorCode);
          return ;
      }
    }
 
    // set the UI preferences
    if (strRenewTitle[0] != null){
        document.NSCP_IVSPTA.set_UIPrefs_SelID_Title(strRenewTitle) ;
        if ( (ErrorCode = document.NSCP_IVSPTA.GetLastError()) != 0) {
           CloseObjects(ErrorCode, "Renewal::NSCP_IVSPTA.set_UIPrefs_SelID_Title", ErrorCode);
           return ;
        }
    }


    // set the UI preferences
    if (strRenewText[0] != null){
        document.NSCP_IVSPTA.set_UIPrefs_SelID_Text(strRenewText) ;
        if ( (ErrorCode = document.NSCP_IVSPTA.GetLastError()) != 0) {
           CloseObjects(ErrorCode, "Renewal::NSCP_IVSPTA.set_UIPrefs_SelID_Text", ErrorCode);
           return ;
        }
    }

    // set the UI preferences
    if (strRenewHelpUrl[0] != null){
        document.NSCP_IVSPTA.set_UIPrefs_SelID_HelpUrl(strRenewHelpUrl) ;
        if ( (ErrorCode = document.NSCP_IVSPTA.GetLastError()) != 0) {
           CloseObjects(ErrorCode, "Renewal::NSCP_IVSPTA.set_UIPrefs_SelID_HelpUrl", ErrorCode);
           return ;
        }
    }

    document.NSCP_IVSPTA.set_UIPrefs_SelID_OKBtnText(127) ;
    if ( (ErrorCode = document.NSCP_IVSPTA.GetLastError()) != 0) {
      CloseObjects(ErrorCode, "Renewal::NSCP_IVSPTA.set_UIPrefs_SelID_OKBtnText", ErrorCode);
      return ;
    }

    document.NSCP_IVSPTA.set_UIPrefs_SelID_ShowDefChkBox(false) ;
    if ( (ErrorCode = document.NSCP_IVSPTA.GetLastError()) != 0) {
      CloseObjects(ErrorCode, "Renewal::NSCP_IVSPTA.set_UIPrefs_SelID_ShowDefChkBox", ErrorCode);
      return ;
    }

    if ( strCertStore == "verisign" ) {
       if (strRenewChooseTitle[0] != null){
          document.NSCP_IVSPTA.set_UIPrefs_OpenProf_Title(strRenewChooseTitle) ;
          if ( (ErrorCode = document.NSCP_IVSPTA.GetLastError()) != 0) {
              CloseObjects(ErrorCode, "Renewal::NSCP_IVSPTA.set_UIPrefs_OpenProf_Title", ErrorCode);
              return -1;
          }
       }
       if (strRenewChooseText[0] != null){
          document.NSCP_IVSPTA.set_UIPrefs_OpenProf_Text(strRenewChooseText) ;
          if ( (ErrorCode = document.NSCP_IVSPTA.GetLastError()) != 0) {
              CloseObjects(ErrorCode, "Renewal::NSCP_IVSPTA.set_UIPrefs_OpenProf_Text", ErrorCode);
              return -1;
          }
       }
      OPENPROF_OPEN_ONLY = 0x00000211;
      E_CARDALREADYOPEN = 0x8000102F;
      document.NSCP_IVSPTA.set_ProfMgmt_OpenProfFlags(OPENPROF_OPEN_ONLY) ;
      if ( ((ErrorCode = document.NSCP_IVSPTA.GetLastError()) != 0) && (ErrorCode != E_CARDALREADYOPEN )) {
         CloseObjects(ErrorCode, "Renewal::NSCP_IVSPTA.set_ProfMgmt_OpenProfFlags", ErrorCode);
         return -1;
      }

      //-- VSSKBEGIN Apps/PTAv2/Roaming#5 -- 
      //-- VSSKEND Apps/PTAv2/Roaming#5 --
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
       else { // 
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
         CloseObjects(ErrorCode, "Renewal::NSCP_IVSPTA.get_SelectedDigID_SerNum", ErrorCode);
         return -1;
      }
      document.Renewal.orig_cert_serial.value = CertSerialNumber ;
  
      // Get Issuer DN of Certificate that needs renewal
      IssuerDN = document.NSCP_IVSPTA.get_SelectedDigID_IssuerDN() ;
      if ( (ErrorCode = document.NSCP_IVSPTA.GetLastError()) != 0)
      {
         CloseObjects(ErrorCode, "Renewal::NSCP_IVSPTA.get_SelectedDigID_SerNum", ErrorCode);
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
<!-- VSSKENDPOLICYVAL#verisign#6 -->



// for userEnroll*.htm
<!-- VSSKBEGINPOLICYVAL#verisign#7 -->
<!-- VSSKENDPOLICYVAL#verisign#7 -->

// for userRenewalNS.htm
<!-- VSSKBEGINPOLICYVAL#verisign#8 -->
<INPUT TYPE=hidden NAME=getMethod VALUE="pkcs7">
<INPUT TYPE=hidden NAME=orig_cert_serial VALUE="$$orig_cert_serial$$">  
<INPUT TYPE=hidden NAME=orig_cert_issuerdn VALUE="$$orig_cert_issuerdn$$">
<INPUT TYPE=hidden NAME=pkcsInformation VALUE="$$pkcsInformation$$">
<INPUT TYPE=hidden NAME=detachedMesg VALUE="$$detachedMesg$$">
<INPUT TYPE=hidden NAME=public_key VALUE="">
<!-- VSSKENDPOLICYVAL#verisign#8 -->

 
<!-- VSSKBEGINPOLICYVAL#verisign#9#1.2.0.5 -->
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
<!-- VSSKENDPOLICYVAL#verisign#9 -->


// for userRenewalNS.htm
<!-- VSSKBEGINPOLICYVAL#verisign#10#1.2.0.4 -->
<Script Language="JavaScript">
<!--
   window.setTimeout("renewclick()", 1000);

   //document.Renewal.submit();
//-->
</script>
<!-- VSSKENDPOLICYVAL#verisign#10 -->

<!-- VSSKBEGINPOLICYVAL#verisign#11#1.2.0.6 -->
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
        if(name.search("VeriSign Personal Trust Agent") != -1)
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
<!-- VSSKENDPOLICYVAL#verisign#11 -->

<!-- VSSKBEGINPOLICYVAL#verisign#12#1.2.0.4 -->
if(browserNum < 5)
{
   if (document.ThePlugin == null) {
       SetErrorInfo ("../fdf/VSApps/client/PTAv2Errors.fdf", "00000101", 0, "The plugin instance is NULL");
   }
}
<!-- VSSKENDPOLICYVAL#verisign#12 -->

<!-- VSSKBEGINPOLICYVAL#verisign#13 -->
<Script Language="VBScript">
<!--
   Call renewclick
'-->
</script>
<!-- VSSKENDPOLICYVAL#verisign#13 -->

// for userRenewalSignNS.fdf
<!-- VSSKBEGINPOLICYVAL#verisign#14 -->
STATUS		0		VSApps/client/userRenewalInstallNSpta.htm
STATUS		6FFF		VSApps/client/userRenewalInstallNSpta.htm
<!-- VSSKENDPOLICYVAL#verisign#14 -->

// for userRenewalEncNS.fdf
<!-- VSSKBEGINPOLICYVAL#verisign#15 -->
STATUS		   0		VSApps/client/userRenewalInstallEncNSpta.htm
STATUS		6FFF		VSApps/client/userRenewalInstallEncNSpta.htm
<!-- VSSKENDPOLICYVAL#verisign#15 -->

<!-- VSSKBEGINPOLICYVAL#verisign#16 -->
<!-- VSSKENDPOLICYVAL#verisign#16 -->
