
<!-- VSSKBEGINPOLICYVAL#verisign#1 -->
<!-- VSSKBEGIN Global/Mode#101 -->
<!-- VSSKEND Global/Mode#101 -->
<!-- VSSKENDPOLICYVAL#verisign#1 -->

<!-- VSSKBEGINPOLICYVAL#verisign#2 -->
<!-- VSSKENDPOLICYVAL#verisign#2 -->

<!-- VSSKBEGINPOLICYVAL#verisign#3 -->
<BODY BGCOLOR="ffffff" LINK="cc0000" VLINK="666666">
<!-- VSSKENDPOLICYVAL#verisign#3 -->


<!-- VSSKBEGINPOLICYVAL#verisign#4#1.2.5.6 -->
<SCRIPT LANGUAGE="VBScript">
<!--
  '-- VSSKBEGIN Apps/PTAv2#5 --
  '-- VSSKEND Apps/PTAv2#5 --
  
  Dim IVSProfMgmt
  Dim IVSUIPrefs
  Dim IVSCertPrefs
  Dim IVSSrchCrit
  Dim IVSSelectedID
  Dim IVSRoamPrefs

  On Error Resume Next
  Set IVSProfMgmt = IVSPTA.IVSProfMgmt
  Set IVSUIPrefs = IVSPTA.IVSUIPrefs
  Set IVSCertPrefs = IVSPTA.IVSCertPrefs
  Set IVSSrchCrit = IVSPTA.IVSSrchCrit
  Set IVSSelectedID = IVSPTA.IVSSelectedDigID
  Set IVSRoamPrefs = IVSPTA.IVSRoamPrefs
  
  'This sub will call the close methods of both the objects  
   Function CloseObjects (ErrorCode, Operation, WinErrorCode)
    On Error Resume Next
    IVSPTA.Close
    if ( ErrorCode <> 0 ) then
       Call SetErrorInfo ("../fdf/VSApps/client/PTAv2Errors.fdf", CheckErrorCodeMS(ErrorCode), WinErrorCode, Operation)
       Exit Function
    end if 
    If ( err.number <> 0 ) then
        Call SetErrorInfo("../fdf/VSApps/client/PTAv2Errors.fdf", 00000001, Hex(err.number), "IVSPTA.Close")
        Exit Function
    End If
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
    
    set theForm = document.proform
    theForm.Accept.disabled = true
	if(TPMEnabled = "CHECKED" And boolTPMAvailable = "True") then
		' Initialize the PTA Object
		On Error Resume Next

		IVSPTA.Initialize strAppCtxtName,2
		If ( err.number <> 0 ) then
		  Call CloseObjects(Hex(err.number), "Enroll::IVSPTA.Initialize", Hex(err.number))
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
			Call CloseObjects(Hex(err.number), "Enroll::IVSProfMgmt.CreatePKCS10", Hex(err.number))
			Exit Sub
		End If
	else
		' open profile etc.
		' Initialize the PTA Object
		On Error Resume Next
    
		if (strCertStore = "1") then 
		   IVSPTA.Initialize strAppCtxtName,0
		else
		   MsgBox "This is an error in setting policies, the cert store should be Symantec"
		   Exit Sub
		End If
		
		If ( err.number <> 0 ) then
		  Call CloseObjects(Hex(err.number), "Enroll::IVSPTA.Initialize", Hex(err.number))
		  Exit Sub
		End If

		'MsgBox "PTA Initialized"
    
		On Error Resume Next
		If (Len(strNewPasswordTitle) <> 0) then 
			IVSUIPrefs.NewPasswd_Title = strNewPasswordTitle
			If ( err.number <> 0 ) then
							Call CloseObjects(Hex(err.number), "Enroll::IVSUIPrefs.NewPasswd_Title", Hex(err.number))
				Exit Sub
			End If
		End If
		
		On Error Resume Next
		If (Len(strNewPasswordText) <> 0) then 
			IVSUIPrefs.NewPasswd_Text = strNewPasswordText
			If ( err.number <> 0 ) then
							Call CloseObjects(Hex(err.number), "Enroll::IVSUIPrefs.NewPasswd_Text", Hex(err.number))
				Exit Sub
			End If
		End If
		
		On Error Resume Next
		If (Len(strAppLogoUrl) <> 0) then
		IVSUIPrefs.UILogoUrl = strAppLogoUrl
		   If ( err.number <> 0 ) then
					  Call CloseObjects(Hex(err.number), "Enroll::IVSUIPrefs.LogoUrl", Hex(err.number))
			  Exit Sub
		   End If
		End If
			

		On Error Resume Next
		If (Len(strAffiliateLogoUrl) <> 0 And strAffiliateLogoUrl <> "VeriSign") then
      		 IVSPTA.AffLogoUrl = strAffiliateLogoUrl
			 If ( err.number <> 0 And err.number <> &h800010c4 ) then
				   Call CloseObjects(Hex(err.number), "Enroll::IVSPTA.AffLogoUrl", Hex(err.number))
				   Exit Sub
			 End If
		End If

		On Error Resume Next
		If (Len(strNewProfileHelpUrl) <> 0) then 
			IVSUIPrefs.NewPasswd_HelpUrl = strNewProfileHelpUrl
			If ( err.number <> 0 ) then
							Call CloseObjects(Hex(err.number), "Enroll::IVSUIPrefs.NewPasswd_HelpUrl", Hex(err.number))
	         		Exit Sub
			End If
		End If
		
		
		' set the password preferences.
		On Error Resume Next
		if ( passwordQuality <> "") then
		   IVSProfMgmt.PasswdQuality = CInt (passwordQuality)
		   If ((err.number <> 0) And (Hex(err.number) <> "8000102F") ) Then
					  Call CloseObjects(Hex(err.number), "Enroll::IVSProfMgmt.PasswdQuality", Hex(err.number))
			  Exit Sub 
		   End If
		End If 

		On Error Resume Next
		if ( passwordLength <> "") then
		   IVSProfMgmt.PasswdLength = CInt (passwordLength)
		   If ((err.number <> 0) And (Hex(err.number) <> "8000102F") ) Then
					  Call CloseObjects(Hex(err.number), "Enroll::IVSProfMgmt.PasswdLength", Hex(err.number))
			  Exit Sub 
		   End If
		End If     
    
		On Error Resume Next
		if ( passwordTimeOut <> "") then
		   IVSProfMgmt.PasswdTimeOut = CInt (passwordTimeOut)
		   If ((err.number <> 0) And (Hex(err.number) <> "8000102F") ) Then
					  Call CloseObjects(Hex(err.number), "Enroll::IVSProfMgmt.PasswdTimeOut", Hex(err.number))
			  Exit Sub 
		   End If
		End If
    
		On Error Resume Next
		if ( passwordTries <> "") then
		   IVSProfMgmt.PasswdLockOutTries = CInt (passwordTries)
		   If ((err.number <> 0) And (Hex(err.number) <> "8000102F") ) Then
					  Call CloseObjects(Hex(err.number), "Enroll::IVSProfMgmt.PasswdLockOutTries", Hex(err.number))
			  Exit Sub 
		   End If
		End If          
    
		On Error Resume Next
		if ( passwordUnlockPeriod <> "") then
		   IVSProfMgmt.PasswdUnLockPeriod = CInt (passwordUnlockPeriod)
		   If ((err.number <> 0) And (Hex(err.number) <> "8000102F") ) Then
					  Call CloseObjects(Hex(err.number), "Enroll::IVSProfMgmt.PasswdUnLockPeriod", Hex(err.number))
			  Exit Sub 
		   End If
		End If      

		' set roaming preferences
		'-- VSSKBEGIN Apps/PTAv2/Roaming#2 -- 
		'-- VSSKEND Apps/PTAv2/Roaming#2 -- 
    
		'if exchange is enabled then first name and last name are not valid.
		On Error Resume Next
		if ( (ExchangeIntegration <> 1) And ("%%Enrollment/FirstName::policyValue%%" = "exists") And ("%%Enrollment/FirstName::policyValue%%" = "exists")) then
		  profileName = Left(theForm.mail_firstName.value,1) + theForm.mail_lastName.value

    		   On Error Resume Next
    		   if ( theForm.mail_firstName.value <> "") then
	 	      IVSProfMgmt.FirstName = theForm.mail_firstName.value
       		      If (err.number <> 0)  Then
           	          Call CloseObjects(Hex(err.number), "Enroll::IVSProfMgmt.FirstName", Hex(err.number))
		          Exit Sub 
       		      End If
   		   End If       

   		   On Error Resume Next
   		   if ( theForm.mail_lastName.value <> "") then
   		      IVSProfMgmt.LastName = theForm.mail_lastName.value
     		      If (err.number <> 0)  Then
          	           Call CloseObjects(Hex(err.number), "Enroll::IVSProfMgmt.LastName", Hex(err.number))
			   Exit Sub 
      		      End If
   		   End If       

		End If

		'Start Add : Infosys : CR21346
		if (ExchangeIntegration = 1) then

		  theForm.mail_firstName.value = IGSE.FirstName
		  theForm.mail_lastName.value = IGSE.LastName

		  profileName = Left(theForm.mail_firstName.value,1) + theForm.mail_lastName.value

    		   On Error Resume Next
    		   if ( theForm.mail_firstName.value <> "") then
	 	      IVSProfMgmt.FirstName = theForm.mail_firstName.value
       		      If (err.number <> 0)  Then
           	          Call CloseObjects(Hex(err.number), "Enroll::IVSProfMgmt.FirstName", Hex(err.number))
		          Exit Sub 
       		      End If
   		   End If       

   		   On Error Resume Next
   		   if ( theForm.mail_lastName.value <> "") then
   		      IVSProfMgmt.LastName = theForm.mail_lastName.value
     		      If (err.number <> 0)  Then
          	           Call CloseObjects(Hex(err.number), "Enroll::IVSProfMgmt.LastName", Hex(err.number))
			   Exit Sub 
      		      End If
   		   End If       

		End If
		'End Add : Infosys : CR21346
    
		On Error Resume Next
		if ( profileName <> "") then
		   IVSProfMgmt.ProfileName = profileName
		   If ((err.number <> 0) And (Hex(err.number) <> "8000102F") ) Then
					  Call CloseObjects(Hex(err.number), "Enroll::IVSProfMgmt.ProfileName", Hex(err.number))
			  Exit Sub 
		   End If
		End If       
        
  		On Error Resume Next
  		if ( theForm.mail_email.value <> "") then
  		   IVSProfMgmt.Email = theForm.mail_email.value
  		   If (err.number <> 0)  Then
  		        Call CloseObjects(Hex(err.number), "Enroll::IVSProfMgmt.Email", Hex(err.number))
		        Exit Sub 
		   End If
	        End If       

		' Create the PKCS 10
		theForm.public_key.value = CreatePKCS10()

		if (Hex(err.number) = "80001067" ) Then 
			Call CloseObjects(0, "", 0)
			MsgBox "You have cancelled the operation at this time. Click Accept again if you want to continue with the enrollment."
			Exit Sub
		End if 
		If (err.number <> 0) Then
			Call CloseObjects(Hex(err.number), "Enroll::IVSProfMgmt.CreatePKCS10", Hex(err.number))
			Exit Sub
		End If       

		'On Error Resume Next
		'IVSProfMgmt.SaveProfile
		'If (err.number <> 0) Then
		'       Call CloseObjects(Hex(err.number), "Enroll::IVSProfMgmt.SaveProfile", Hex(err.number))
		'       Exit Sub 
		'End If
    End If
	Call CloseObjects(0, "", 0)
    ' set the public key and submit the form.
    if Len(theForm.public_key.value) = 0 then
      Call SetErrorInfo("../fdf/VSApps/client/PTAv2Errors.fdf", CheckErrorCodeMS(Hex(err.number)), Hex(err.number), "Enroll::Key Generation")
    else
      theForm.submit
    end If
  End Sub
'-->
</SCRIPT>
<!-- VSSKENDPOLICYVAL#verisign#4 -->


# stuff for key gen information on NS enrollment page.
<!-- VSSKBEGINPOLICYVAL#verisign#5#1.2.0.6 -->
<Script Language="Javascript">
<!--
 //-- VSSKBEGIN Apps/PTAv2#6 -- 
 //-- VSSKEND Apps/PTAv2#6 --
 
 var PKCS10;
  
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
        return;
    }   
    if ( (ErrorCode = document.NSCP_IVSPTA.GetLastError()) != 0) {    
      SetErrorInfo ("../fdf/VSApps/client/PTAv2Errors.fdf", "00000001", ConvertToHexNS(ErrorCode), "NSCP_IVSPTA.PTA_Close");
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
   
   //-- VSSKBEGIN Enrollment/KeyExportable#4 --
   //-- VSSKEND Enrollment/KeyExportable#4 --
  
   // generate the public key
   //-- VSSKBEGIN Enrollment/KeyLength#5 --
   //-- VSSKEND Enrollment/KeyLength#5 --
   
   return (PKCS10) ;
 }
 
 
 function GenerateP10Java()
 {
   var boolProfileOpen;
   var profileName;
   //alert("Generating the key-pair");

   if(browserNum < 5) {
	PKCS10 = new java.lang.StringBuffer("");
   } else {
	PKCS10 = new String("");
   }
   
   if (document.NSCP_IVSPTA == null) {
       SetErrorInfo ("../fdf/VSApps/client/PTAv2Errors.fdf", "00000101", 0, "The plugin instance is NULL");
   }

   if (strCertStore == "1") {
	  document.NSCP_IVSPTA.PTA_Initialize(strAppCtxtName, 0) ;
   }
   else {
	  document.NSCP_IVSPTA.PTA_Initialize(strAppCtxtName, 1) ;
   }	
   if ( (ErrorCode = document.NSCP_IVSPTA.GetLastError()) != 0) {
      CloseObjects(ErrorCode, "Enroll::NSCP_IVSPTA.PTA_Initialize", ErrorCode);
      return false;
   }
   
   if (strNewPasswordTitle[0] != null){
      document.NSCP_IVSPTA.set_UIPrefs_NewPasswd_Title(strNewPasswordTitle) ;
      if ( (ErrorCode = document.NSCP_IVSPTA.GetLastError()) != 0) {
          CloseObjects(ErrorCode, "Enroll::NSCP_IVSPTA.set_UIPrefs_NewPasswd_Title", ErrorCode);
          return false;
      }
   }
    
   if (strNewPasswordText[0] != null){
      document.NSCP_IVSPTA.set_UIPrefs_NewPasswd_Text(strNewPasswordText) ;
      if ( (ErrorCode = document.NSCP_IVSPTA.GetLastError()) != 0) {
          CloseObjects(ErrorCode, "Enroll::NSCP_IVSPTA.set_UIPrefs_NewPasswd_Text", ErrorCode);
          return false;
      }
   }
    
   if (strAppLogoUrl[0] != null){
      document.NSCP_IVSPTA.set_UIPrefs_UILogoUrl(strAppLogoUrl) ;
      if ( (ErrorCode = document.NSCP_IVSPTA.GetLastError()) != 0) {
          CloseObjects(ErrorCode, "Enroll::NSCP_IVSPTA.set_UIPrefs_UILogoUrl", ErrorCode);
          return false;
      }
   }

   if ( (strAffiliateLogoUrl[0] != null) && (strAffiliateLogoUrl != "VeriSign") ){
      document.NSCP_IVSPTA.set_PTA_AffLogoUrl(strAffiliateLogoUrl) ;
      if ( ((ErrorCode = document.NSCP_IVSPTA.GetLastError()) != 0) && (ErrorCode != 0x800010c4)) {
          CloseObjects(ErrorCode, "Enroll::NSCP_IVSPTA.set_PTA_AffLogoUrl", ErrorCode);
          return false;
      }
   }
   
   if (strNewProfileHelpUrl[0] != null){
      document.NSCP_IVSPTA.set_UIPrefs_NewPasswd_HelpUrl(strNewProfileHelpUrl) ;
      if ( (ErrorCode = document.NSCP_IVSPTA.GetLastError()) != 0) {
          CloseObjects(ErrorCode, "Enroll::NSCP_IVSPTA.set_UIPrefs_NewPasswd_HelpUrl", ErrorCode);
          return false;
      }
   }

   E_CARDALREADYOPEN = 0x8000102F;
        
   if (!isNaN(parseInt(passwordQuality))){
      document.NSCP_IVSPTA.set_ProfMgmt_PasswdQuality(parseInt(passwordQuality)) ;
      if ( ((ErrorCode = document.NSCP_IVSPTA.GetLastError()) != 0) && (ErrorCode != E_CARDALREADYOPEN )) {
          CloseObjects(ErrorCode, "Enroll::NSCP_IVSPTA.set_ProfMgmt_PasswdQuality", ErrorCode);
          return false;
      }
   }  
     
   if (!isNaN(parseInt(passwordLength))){
      document.NSCP_IVSPTA.set_ProfMgmt_PasswdLength(parseInt(passwordLength)) ;
      if ( ((ErrorCode = document.NSCP_IVSPTA.GetLastError()) != 0 ) && (ErrorCode != E_CARDALREADYOPEN ) ) {
          CloseObjects(ErrorCode, "Enroll::NSCP_IVSPTA.set_ProfMgmt_PasswdLength", ErrorCode);
          return false;
      }
   }    
   
   if (!isNaN(parseInt(passwordTimeOut))){
      document.NSCP_IVSPTA.set_ProfMgmt_PasswdTimeOut(parseInt(passwordTimeOut)) ;
      if ( ((ErrorCode = document.NSCP_IVSPTA.GetLastError()) != 0 ) && (ErrorCode != E_CARDALREADYOPEN ) ) {
          CloseObjects(ErrorCode, "Enroll::NSCP_IVSPTA.set_ProfMgmt_PasswdTimeOut", ErrorCode);
          return false;
      }
   }    
   
   if (!isNaN(parseInt(passwordTries))){
      document.NSCP_IVSPTA.set_ProfMgmt_PasswdLockOutTries(parseInt(passwordTries)) ;
      if ( ((ErrorCode = document.NSCP_IVSPTA.GetLastError()) != 0 ) && (ErrorCode != E_CARDALREADYOPEN ) ) {
          CloseObjects(ErrorCode, "Enroll::NSCP_IVSPTA.set_ProfMgmt_PasswdLockOutTries", ErrorCode);
          return false;
      }
   }    
   
   if (!isNaN(parseInt(passwordUnlockPeriod))){
      document.NSCP_IVSPTA.set_ProfMgmt_PasswdUnLockPeriod(parseInt(passwordUnlockPeriod)) ;
      if ( ((ErrorCode = document.NSCP_IVSPTA.GetLastError()) != 0 ) && (ErrorCode != E_CARDALREADYOPEN ) ) {
          CloseObjects(ErrorCode, "Enroll::NSCP_IVSPTA.set_ProfMgmt_PasswdunLockPeriod", ErrorCode);
          return false;
      }
   }    
   
   //-- VSSKBEGIN Apps/PTAv2/Roaming#4 --
   //-- VSSKEND Apps/PTAv2/Roaming#4 --

   if ( ("%%Enrollment/FirstName::policyValue%%" == "exists") && ("%%Enrollment/FirstName::policyValue%%" == "exists") ) {
     profileName = document.proform.mail_firstName.value[0] + document.proform.mail_lastName.value;
   } else {
     profileName = "";
   } 
      
   if (profileName[0] != null) {
      //set the profile name
      document.NSCP_IVSPTA.set_ProfMgmt_ProfileName(profileName) ;
      if ( ((ErrorCode = document.NSCP_IVSPTA.GetLastError()) != 0  ) && (ErrorCode != E_CARDALREADYOPEN )) {
          CloseObjects(ErrorCode, "Enroll::NSCP_IVSPTA.set_ProfMgmt_ProfileName", ErrorCode);
          return false;
      }
   }
   
   document.proform.public_key.value = CreateP10Java() ;
   
   ErrorCode = document.NSCP_IVSPTA.GetLastError();
   if (ErrorCode == 0x80001067) {
         CloseObjects(0, "", 0);
         alert ("You have cancelled this operation at this time. Click Accept again if you want to enroll.");
         return false;
   } else 
   if (ErrorCode != 0) {
         CloseObjects(ErrorCode, "Enroll::NSCP_IVSPTA.PTA_CreateCertReq", ErrorCode);
         return false;
   }
   
   //document.NSCP_IVSPTA.ProfMgmt_SaveProfile() ;
   //if ( (ErrorCode = document.NSCP_IVSPTA.GetLastError()) != 0 ) {
   //    CloseObjects(ErrorCode, "Enroll::NSCP_IVSPTA.ProfMgmt_SaveProfile", ErrorCode);
   //    return false;
   //}

   CloseObjects(0, "", 0);
   if ( document.proform.public_key.length == 0 ){
       SetErrorInfo("../fdf/VSApps/client/PTAv2Errors.fdf", ReBaseErrorCodeNS(ErrorCode), ConvertToHexNS(ErrorCode), "Enroll::KeyGeneration");
       return false;
   }

   //alert("document.proform.public_key.value : \n" + document.proform.public_key.value) ;
   return true;
 }

//-->
</Script>
<!-- VSSKENDPOLICYVAL#verisign#5 -->


<!-- VSSKBEGINPOLICYVAL#verisign#6 -->
<!-- VSSKENDPOLICYVAL#verisign#6 -->


<!-- VSSKBEGINPOLICYVAL#verisign#7 -->
<!-- VSSKENDPOLICYVAL#verisign#7 -->

#include the PTA plugin for Generating Symantec keys 
<!-- VSSKBEGINPOLICYVAL#verisign#8#1.2.0.4 -->
<EMBED type="application/x-vspta2-plugin" name="ThePlugin" WIDTH=0 HEIGHT=0 HIDDEN>
<!-- VSSKENDPOLICYVAL#verisign#8 -->

<!-- VSSKBEGINPOLICYVAL#verisign#9#1.2.0.4 -->
				InitPlugin();
                rval = GenerateP10Java();
<!-- VSSKENDPOLICYVAL#verisign#9 -->


<!-- VSSKBEGINPOLICYVAL#verisign#10#1.2.0.7 -->

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
<!-- VSSKENDPOLICYVAL#verisign#10 -->


<!-- VSSKBEGINPOLICYVAL#verisign#11 -->
<SCRIPT LANGUAGE="VBScript">
<!--
  ' the cert is available in the variable CertChain
  Sub InstallCert
 
  End Sub
'-->
</SCRIPT>
<!-- VSSKENDPOLICYVAL#verisign#11 -->


// for userEnrollNS.fdf
<!-- VSSKBEGINPOLICYVAL#verisign#12 -->
STATUS		   0		VSApps/client/userInstallNSpta.htm
STATUS		6FFF		VSApps/client/userInstallNSpta.htm
<!-- VSSKENDPOLICYVAL#verisign#12 -->

// for userEnroll*.fdf
<!-- VSSKBEGINPOLICYVAL#verisign#13 -->
CONST     public_key_format       pkcs10
# VSSKBEGIN Apps/AuthBureau#1
# VSSKEND Apps/AuthBureau#1
<!-- VSSKENDPOLICYVAL#verisign#13 -->


// for userGetIDNS.fdf
<!-- VSSKBEGINPOLICYVAL#verisign#14 -->
<!-- VSSKENDPOLICYVAL#verisign#14 -->

// key manager should deliver files in pkcs8 format for firefox 
// enrollments if not a native NS cert store
<!-- VSSKBEGINPOLICYVAL#verisign#15 -->
CONST     key_format           pkcs8
<!-- VSSKENDPOLICYVAL#verisign#15 -->

// for userEnrollDualNS.fdf
<!-- VSSKBEGINPOLICYVAL#verisign#16 -->
STATUS		   0		VSApps/client/userInstallDualNSpta.htm
STATUS		6FFF		VSApps/client/userInstallDualNSpta.htm
<!-- VSSKENDPOLICYVAL#verisign#16 -->


// for userEnrollEncNS.fdf
<!-- VSSKBEGINPOLICYVAL#verisign#17 -->
STATUS		   0		VSApps/client/userInstallEncNSpta.htm
STATUS		6FFF		VSApps/client/userInstallEncNSpta.htm
<!-- VSSKENDPOLICYVAL#verisign#17 -->

// for userRenewalNS.fdf
<!-- VSSKBEGINPOLICYVAL#verisign#18 -->
STATUS		6FFF		VSApps/client/userRenewalInstallNSpta.htm
<!-- VSSKENDPOLICYVAL#verisign#18 -->


<!-- VSSKBEGINPOLICYVAL#verisign#19 -->
				InitPlugin();
                rval = CreateProfile();
<!-- VSSKENDPOLICYVAL#verisign#19 -->


<!-- VSSKBEGINPOLICYVAL#verisign#20#1.2.5.6 -->
<SCRIPT Language="VBScript">
<!--
  '-- VSSKBEGIN Apps/PTAv2#5 --
  '-- VSSKEND Apps/PTAv2#5 --
  
  Dim IVSProfMgmt
  Dim IVSUIPrefs
  Dim IVSCertPrefs
  Dim IVSSrchCrit
  Dim IVSSelectedID
  Dim IVSRoamPrefs

  On Error Resume Next
  Set IVSProfMgmt = IVSPTA.IVSProfMgmt
  Set IVSUIPrefs = IVSPTA.IVSUIPrefs
  Set IVSCertPrefs = IVSPTA.IVSCertPrefs
  Set IVSSrchCrit = IVSPTA.IVSSrchCrit
  Set IVSSelectedID = IVSPTA.IVSSelectedDigID
  Set IVSRoamPrefs = IVSPTA.IVSRoamPrefs
  
  'This sub will call the close methods of both the objects  
   Function CloseObjects (ErrorCode, Operation, WinErrorCode)
    On Error Resume Next
    IVSPTA.Close
    if ( ErrorCode <> 0 ) then
       Call SetErrorInfo ("../fdf/VSApps/client/PTAv2Errors.fdf", CheckErrorCodeMS(ErrorCode), WinErrorCode, Operation)
       Exit Function
    end if 
    If ( err.number <> 0 ) then
        Call SetErrorInfo("../fdf/VSApps/client/PTAv2Errors.fdf", 00000001, Hex(err.number), "IVSPTA.Close")
        Exit Function
    End If
  End Function
    
  Sub CreateProfile
    Dim boolProfileOpen
    Dim profileName
    Dim theForm 
    
    set theForm = document.proform
    theForm.Accept.disabled = true
    ' open profile etc.
    ' Initialize the PTA Object
    On Error Resume Next    
    if (strCertStore = "1") then 
	   IVSPTA.Initialize strAppCtxtName,0
    else
	   MsgBox "This is an error in setting policies, the cert store should be symantec"
	   Exit Sub
    End If
	
    If ( err.number <> 0 ) then
      Call CloseObjects(Hex(err.number), "Enroll::IVSPTA.Initialize", Hex(err.number))
      Exit Sub
    End If

    'MsgBox "PTA Initialized"
    
    On Error Resume Next
    If (Len(strNewPasswordTitle) <> 0) then 
		IVSUIPrefs.NewPasswd_Title = strNewPasswordTitle
		If ( err.number <> 0 ) then
                        Call CloseObjects(Hex(err.number), "Enroll::IVSUIPrefs.NewPasswd_Title", Hex(err.number))
			Exit Sub
		End If
	End If
	
	On Error Resume Next
    If (Len(strNewPasswordText) <> 0) then 
		IVSUIPrefs.NewPasswd_Text = strNewPasswordText
		If ( err.number <> 0 ) then
                        Call CloseObjects(Hex(err.number), "Enroll::IVSUIPrefs.NewPasswd_Text", Hex(err.number))
			Exit Sub
		End If
	End If
	
	On Error Resume Next
    If (Len(strAppLogoUrl) <> 0) then
	IVSUIPrefs.UILogoUrl = strAppLogoUrl
	   If ( err.number <> 0 ) then
                  Call CloseObjects(Hex(err.number), "Enroll::IVSUIPrefs.LogoUrl", Hex(err.number))
		  Exit Sub
	   End If
	End If

	On Error Resume Next
    If (Len(strAffiliateLogoUrl) <> 0 And strAffiliateLogoUrl <> "VeriSign") then
      	 IVSPTA.AffLogoUrl = strAffiliateLogoUrl
         If ( err.number <> 0 And err.number <> &h800010c4 ) then
               Call CloseObjects(Hex(err.number), "Enroll::IVSPTA.AffLogoUrl", Hex(err.number))
		       Exit Sub
         End If
	End If
		
	On Error Resume Next
    If (Len(strNewProfileHelpUrl) <> 0) then 
		IVSUIPrefs.NewPasswd_HelpUrl = strNewProfileHelpUrl
		If ( err.number <> 0 ) then
                        Call CloseObjects(Hex(err.number), "Enroll::IVSUIPrefs.NewPasswd_HelpUrl", Hex(err.number))
	         	Exit Sub
		End If
	End If
		
	' set the password preferences.
	On Error Resume Next
	if ( passwordQuality <> "") then
       IVSProfMgmt.PasswdQuality = CInt (passwordQuality)
	   If ((err.number <> 0) And (Hex(err.number) <> "8000102F") ) Then
                  Call CloseObjects(Hex(err.number), "Enroll::IVSProfMgmt.PasswdQuality", Hex(err.number))
		  Exit Sub 
       End If
    End If 

    On Error Resume Next
	if ( passwordLength <> "") then
       IVSProfMgmt.PasswdLength = CInt (passwordLength)
	   If ((err.number <> 0) And (Hex(err.number) <> "8000102F") ) Then
                  Call CloseObjects(Hex(err.number), "Enroll::IVSProfMgmt.PasswdLength", Hex(err.number))
		  Exit Sub 
       End If
    End If     
    
    On Error Resume Next
	if ( passwordTimeOut <> "") then
       IVSProfMgmt.PasswdTimeOut = CInt (passwordTimeOut)
	   If ((err.number <> 0) And (Hex(err.number) <> "8000102F") ) Then
                  Call CloseObjects(Hex(err.number), "Enroll::IVSProfMgmt.PasswdTimeOut", Hex(err.number))
		  Exit Sub 
       End If
    End If
    
    On Error Resume Next
    if ( passwordTries <> "") then
       IVSProfMgmt.PasswdLockOutTries = CInt (passwordTries)
	   If ((err.number <> 0) And (Hex(err.number) <> "8000102F") ) Then
                  Call CloseObjects(Hex(err.number), "Enroll::IVSProfMgmt.PasswdLockOutTries", Hex(err.number))
		  Exit Sub 
       End If
    End If          
    
    On Error Resume Next
    if ( passwordUnlockPeriod <> "") then
       IVSProfMgmt.PasswdUnLockPeriod = CInt (passwordUnlockPeriod)
	   If ((err.number <> 0) And (Hex(err.number) <> "8000102F") ) Then
                  Call CloseObjects(Hex(err.number), "Enroll::IVSProfMgmt.PasswdUnLockPeriod", Hex(err.number))
		  Exit Sub 
       End If
    End If      

    ' set roaming preferences
    '-- VSSKBEGIN Apps/PTAv2/Roaming#2 -- 
    '-- VSSKEND Apps/PTAv2/Roaming#2 -- 
    
    'if exchange is enabled then first name and last name are not valid.
    On Error Resume Next
    if ( (ExchangeIntegration <> 1) And ("%%Enrollment/FirstName::policyValue%%" = "exists") And  ("%%Enrollment/FirstName::policyValue%%" = "exists")) then
      profileName = Left(theForm.mail_firstName.value,1) + theForm.mail_lastName.value
    End If
    
    ' Start Add : Infosys : CR21346
    If (ExchangeIntegration = 1)then
	theForm.mail_firstName.value = IGSE.FirstName
	theForm.mail_lastName.value = IGSE.LastName
        profileName = Left(theForm.mail_firstName.value,1) + theForm.mail_lastName.value
    End If
    ' End Add : Infosys : CR21346

    On Error Resume Next
    'MsgBox "Profile Name : " & profileName
    if ( profileName <> "") then
       IVSProfMgmt.ProfileName = profileName
	   If ((err.number <> 0) And (Hex(err.number) <> "8000102F") ) Then
                  Call CloseObjects(Hex(err.number), "Enroll::IVSProfMgmt.ProfileName", Hex(err.number))
		  Exit Sub 
       End If
    End If       
    
    On Error Resume Next
    if ( theForm.mail_firstName.value <> "") then
       IVSProfMgmt.FirstName = theForm.mail_firstName.value
       If (err.number <> 0)  Then
            Call CloseObjects(Hex(err.number), "Enroll::IVSProfMgmt.FirstName", Hex(err.number))
	    Exit Sub 
       End If
    End If       

    On Error Resume Next
    if ( theForm.mail_lastName.value <> "") then
       IVSProfMgmt.LastName = theForm.mail_lastName.value
       If (err.number <> 0)  Then
            Call CloseObjects(Hex(err.number), "Enroll::IVSProfMgmt.LastName", Hex(err.number))
	    Exit Sub 
       End If
    End If       

    On Error Resume Next
    if ( theForm.mail_email.value <> "") then
       IVSProfMgmt.Email = theForm.mail_email.value
       If (err.number <> 0)  Then
  	    Call CloseObjects(Hex(err.number), "Enroll::IVSProfMgmt.Email", Hex(err.number))
	    Exit Sub 
       End If
    End If       
    
    ' try to open profile, if error, reset profile and try again   
    On Error Resume Next
    If ( boolProfileOpen = 0 ) Then
        IVSProfMgmt.OpenProfile
        If (Hex(err.number) = "8000102D") Then
           ' the said profile already exists 
           'MsgBox "profile " & profileName & " already exists"
           profileName = ""
           On Error Resume Next
           IVSProfMgmt.ProfileName = profileName
           If (err.number <>0) Then 
               Call CloseObjects(Hex(err.number), "Enroll::IVSProfMgmt.ProfileName", Hex(err.number))
	       Exit Sub 
           End If
           On Error Resume Next
           IVSProfMgmt.OpenProfile
        End If 
        if (Hex(err.number) = "80001067" ) Then 
           Call CloseObjects(0, "", 0)
           MsgBox "You have cancelled the operation at this time. Click Accept again if you want to continue with the enrollment."
           Exit Sub
        End if 
        If (err.number <> 0) Then
               Call CloseObjects(Hex(err.number), "Enroll::IVSProfMgmt.OpenProfile", Hex(err.number))
   	       Exit Sub 
        End If       
    End If

    On Error Resume Next
    'IVSProfMgmt.SaveProfile    
    'If ((err.number <> 0) And (Hex(err.number) <> "8000102F") ) Then
    '     Call CloseObjects(Hex(err.number), "Enroll::IVSProfMgmt.SaveProfile", Hex(err.number))
    '     Exit Sub 
    'End If
    ' the profile should be open at this point        

   Call CloseObjects(0, "", 0)
   theForm.submit
  End Sub
'-->
</SCRIPT>
<!-- VSSKENDPOLICYVAL#verisign#20 -->


# stuff for key gen information on NS enrollment page.
<!-- VSSKBEGINPOLICYVAL#verisign#21#1.2.0.6 -->
<Script Language="Javascript">
<!--
 //-- VSSKBEGIN Apps/PTAv2#6 -- 
 //-- VSSKEND Apps/PTAv2#6 --
  

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
        SetErrorInfo ("../fdf/VSApps/client/PTAv2Errors.fdf", ReBaseErrorCodeNS(errCode), ConvertToHexNS (WinErrorCode), Operation);
        return;
    }   
    if ( (ErrorCode = document.NSCP_IVSPTA.GetLastError()) != 0) {    
      SetErrorInfo ("../fdf/VSApps/client/PTAv2Errors.fdf", "00000001", ConvertToHexNS (ErrorCode), "NSCP_IVSPTA.PTA_Close");
    }
    return;
 }
  
 function CreateProfile()
 {
 
   var boolProfileOpen;
   var profileName;
   
   //alert("Generating the key-pair");
   if (document.NSCP_IVSPTA == null) {
       SetErrorInfo ("../fdf/VSApps/client/PTAv2Errors.fdf", "00000101", 0, "The plugin instance is NULL");
       return false;
   }


   if (strCertStore == "1") {
	  document.NSCP_IVSPTA.PTA_Initialize(strAppCtxtName, 0) ;
   }
   else {
	  document.NSCP_IVSPTA.PTA_Initialize(strAppCtxtName, 1) ;
   }	
   if ( (ErrorCode = document.NSCP_IVSPTA.GetLastError()) != 0) {
      CloseObjects(ErrorCode, "Enroll::NSCP_IVSPTA.PTA_Initialize", ErrorCode);
      return false;
   }
   
   if (strNewPasswordTitle[0] != null){
      document.NSCP_IVSPTA.set_UIPrefs_NewPasswd_Title(strNewPasswordTitle) ;
      if ( (ErrorCode = document.NSCP_IVSPTA.GetLastError()) != 0) {
          CloseObjects(ErrorCode, "Enroll::NSCP_IVSPTA.set_UIPrefs_NewPasswd_Title", ErrorCode);
          return false;
      }
   }
    
   if (strNewPasswordText[0] != null){
      document.NSCP_IVSPTA.set_UIPrefs_NewPasswd_Text(strNewPasswordText) ;
      if ( (ErrorCode = document.NSCP_IVSPTA.GetLastError()) != 0) {
          CloseObjects(ErrorCode, "Enroll::NSCP_IVSPTA.set_UIPrefs_NewPasswd_Text", ErrorCode);
          return false;
      }
   }
    
   if (strAppLogoUrl[0] != null){
      document.NSCP_IVSPTA.set_UIPrefs_UILogoUrl(strAppLogoUrl) ;
      if ( (ErrorCode = document.NSCP_IVSPTA.GetLastError()) != 0) {
          CloseObjects(ErrorCode, "Enroll::NSCP_IVSPTA.set_UIPrefs_UILogoUrl", ErrorCode);
          return false;
      }
   }
   
   if ( (strAffiliateLogoUrl[0] != null) && (strAffiliateLogoUrl != "VeriSign") ){
      document.NSCP_IVSPTA.set_PTA_AffLogoUrl(strAffiliateLogoUrl) ;
      if ( ((ErrorCode = document.NSCP_IVSPTA.GetLastError()) != 0) && (ErrorCode != 0x800010c4)) {
          CloseObjects(ErrorCode, "Enroll::NSCP_IVSPTA.set_PTA_AffLogoUrl", ErrorCode);
          return false;
      }
   }

   if (strNewProfileHelpUrl[0] != null){
      document.NSCP_IVSPTA.set_UIPrefs_NewPasswd_HelpUrl(strNewProfileHelpUrl) ;
      if ( (ErrorCode = document.NSCP_IVSPTA.GetLastError()) != 0) {
          CloseObjects(ErrorCode, "Enroll::NSCP_IVSPTA.set_UIPrefs_NewPasswd_HelpUrl", ErrorCode);
          return false;
      }
   }
   E_CARDALREADYOPEN = 0x8000102F;
        
   if (!isNaN(parseInt(passwordQuality))){
      document.NSCP_IVSPTA.set_ProfMgmt_PasswdQuality(parseInt(passwordQuality)) ;
      if ( ((ErrorCode = document.NSCP_IVSPTA.GetLastError()) != 0) && (ErrorCode != E_CARDALREADYOPEN )) {
          CloseObjects(ErrorCode, "Enroll::NSCP_IVSPTA.set_ProfMgmt_PasswdQuality", ErrorCode);
          return false;
      }
   }  
     
   if (!isNaN(parseInt(passwordLength))){
      document.NSCP_IVSPTA.set_ProfMgmt_PasswdLength(parseInt(passwordLength)) ;
      if ( ((ErrorCode = document.NSCP_IVSPTA.GetLastError()) != 0 ) && (ErrorCode != E_CARDALREADYOPEN ) ) {
          CloseObjects(ErrorCode, "Enroll::NSCP_IVSPTA.set_ProfMgmt_PasswdLength", ErrorCode);
          return false;
      }
   }    
   
   if (!isNaN(parseInt(passwordTimeOut))){
      document.NSCP_IVSPTA.set_ProfMgmt_PasswdTimeOut(parseInt(passwordTimeOut)) ;
      if ( ((ErrorCode = document.NSCP_IVSPTA.GetLastError()) != 0 ) && (ErrorCode != E_CARDALREADYOPEN ) ) {
          CloseObjects(ErrorCode, "Enroll::NSCP_IVSPTA.set_ProfMgmt_PasswdTimeOut", ErrorCode);
          return false;
      }
   }    
   
   if (!isNaN(parseInt(passwordTries))){
      document.NSCP_IVSPTA.set_ProfMgmt_PasswdLockOutTries(parseInt(passwordTries)) ;
      if ( ((ErrorCode = document.NSCP_IVSPTA.GetLastError()) != 0 ) && (ErrorCode != E_CARDALREADYOPEN ) ) {
          CloseObjects(ErrorCode, "Enroll::NSCP_IVSPTA.set_ProfMgmt_PasswdLockOutTries", ErrorCode);
          return false;
      }
   }    
   
   if (!isNaN(parseInt(passwordUnlockPeriod))){
      document.NSCP_IVSPTA.set_ProfMgmt_PasswdUnLockPeriod(parseInt(passwordUnlockPeriod)) ;
      if ( ((ErrorCode = document.NSCP_IVSPTA.GetLastError()) != 0 ) && (ErrorCode != E_CARDALREADYOPEN ) ) {
          CloseObjects(ErrorCode, "Enroll::NSCP_IVSPTA.set_ProfMgmt_PasswdunLockPeriod", ErrorCode);
          return false;
      }
   }    
   
   //-- VSSKBEGIN Apps/PTAv2/Roaming#4 --
   //-- VSSKEND Apps/PTAv2/Roaming#4 --

   if ( ("%%Enrollment/FirstName::policyValue%%" == "exists") && ("%%Enrollment/FirstName::policyValue%%" == "exists") ) {
     profileName = document.proform.mail_firstName.value[0] + document.proform.mail_lastName.value;
   } else {
     profileName = "";
   }
   
   //alert (profileName);
   
   if (profileName[0] != null) {
      //set the profile name
      document.NSCP_IVSPTA.set_ProfMgmt_ProfileName(profileName) ;
      if ( ((ErrorCode = document.NSCP_IVSPTA.GetLastError()) != 0  ) && (ErrorCode != E_CARDALREADYOPEN )) {
          CloseObjects(ErrorCode, "Enroll::NSCP_IVSPTA.set_ProfMgmt_ProfileName", ErrorCode);
          return false;
      }
   }
   if ( boolProfileOpen == 0 ) {
       //alert ("trying to open the profile");
       document.NSCP_IVSPTA.ProfMgmt_OpenProfile();
       ErrorCode = document.NSCP_IVSPTA.GetLastError();
       if ( ErrorCode == 0x8000102D ) {
          //alert ("Profile : " + profileName + " already exists") ;
          profileName = "";
          document.NSCP_IVSPTA.set_ProfMgmt_ProfileName(profileName) ;
          if ( (ErrorCode = document.NSCP_IVSPTA.GetLastError()) != 0 ) {
             CloseObjects(ErrorCode, "Enroll::NSCP_IVSPTA.set_ProfMgmt_ProfileName", ErrorCode);
             return false;
           }
           document.NSCP_IVSPTA.ProfMgmt_OpenProfile();
       }
       ErrorCode = document.NSCP_IVSPTA.GetLastError();
       if (ErrorCode == 0x80001067) {
                CloseObjects(0, "", 0);
                alert ("You have cancelled this operation at this time. Click Accept again if you want to enroll.");
                return false;
       } else 
       if (ErrorCode != 0) {
          CloseObjects(ErrorCode, "Enroll::NSCP_IVSPTA.set_ProfMgmt_OpenProfile", ErrorCode);
          return false;
       }
   }
   
   //document.NSCP_IVSPTA.ProfMgmt_SaveProfile() ;
   //if ( ((ErrorCode = document.NSCP_IVSPTA.GetLastError()) != 0  ) && (ErrorCode != E_CARDALREADYOPEN )) {
   //    CloseObjects(ErrorCode, "Enroll::NSCP_IVSPTA.ProfMgmt_SaveProfile", ErrorCode);
   //    return false;
   //}


   CloseObjects(0, "", 0);
   return true;
 }

//-->
</Script>
<!-- VSSKENDPOLICYVAL#verisign#21 -->

<!-- VSSKBEGINPOLICYVAL#verisign#22 -->
<!-- the PTA control will be include from the PTAv2#8 fragment -->
<!-- VSSKENDPOLICYVAL#verisign#22 -->

<!-- VSSKBEGINPOLICYVAL#verisign#23 -->
<!-- the PTA control will be include from the PTAv2#8 fragment -->
<!-- VSSKENDPOLICYVAL#verisign#23 -->

<!-- VSSKBEGINPOLICYVAL#verisign#24 -->
<!-- the p12 will be installed by SetPreference -->
<Script Language = "VBScript">
<!--
  Sub ImportPKCS12

  End Sub
'-->
</SCRIPT>
<!-- VSSKENDPOLICYVAL#verisign#24 -->


<!-- VSSKBEGINPOLICYVAL#microsoft#25 -->
<!-- the p12 and signing cert will be installed by SetPreference -->
<SCRIPT LANGUAGE="VBSCRIPT">
<!--
  Sub InstallSigningCert

  End Sub

  Sub ImportPKCS12

  End Sub
'-->
</SCRIPT>
<!-- VSSKENDPOLICYVAL#microsoft#25 -->

<!-- VSSKBEGINPOLICYVAL#verisign#26 -->
                rval = CreateProfile();
<!-- VSSKENDPOLICYVAL#verisign#26 -->

<!-- VSSKBEGINPOLICYVAL#verisign#27 -->
<!-- VSSKBEGIN Apps/PTAv2/Roaming#1 -->
<!-- VSSKEND Apps/PTAv2/Roaming#1 -->
<!-- VSSKENDPOLICYVAL#verisign#27 -->


<!-- VSSKBEGINPOLICYVAL#verisign#28#1.2.0.4 -->
   if(browserNum < 5){
	if (document.ThePlugin == null) {
		   SetErrorInfo ("../fdf/VSApps/client/PTAv2Errors.fdf", "00000101", 0, "The plugin instance is NULL");
	}
   }
<!-- VSSKENDPOLICYVAL#verisign#28 -->


<!-- VSSKBEGINPOLICYVAL#verisign#29#1.0.0.3 -->
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
<!-- VSSKENDPOLICYVAL#verisign#29 -->

<!-- VSSKBEGINPOLICYVAL#verisign#30 -->
            //-- VSSKBEGIN Global/Mode#105 --
            //-- VSSKEND Global/Mode#105 --
<!-- VSSKENDPOLICYVAL#verisign#30 -->


<!-- VSSKBEGINPOLICYVAL#verisign#31#1.0.0.2 -->
<!-- begin PTA preference -->
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
	<FONT FACE="verdana, arial, helvetica" SIZE=4><B>PTA PREFERENCE MANAGEMENT</B></FONT></A><BR>
	<FONT FACE="arial, helvetica" SIZE=2>Choose this option for advanced operations and to change the preferences for your PTA profile. 
	</FONT>
	<P>
	</TD>
</TR>
<!-- end change password -->
<!-- VSSKENDPOLICYVAL#verisign#31 -->


<!-- VSSKBEGINPOLICYVAL#verisign#32 -->
<!-- VSSKBEGIN Global/Mode#108 -->
<!-- VSSKEND Global/Mode#108 -->
<!-- VSSKENDPOLICYVAL#verisign#32 -->

<!-- VSSKBEGINPOLICYVAL#verisign#33#1.2.0.4 -->
<script Language="JavaScript">
var browserNum;
var NSCP_IVSPTA;

browserNum=parseInt(navigator.appVersion);

function DoLogoutNS()
{
  if (browserNum < 5) {
     document.NSCP_IVSPTA = document.ThePlugin;
  } else {
     document.NSCP_IVSPTA = document.ThePlugin.ns6IPTA;
  }
  var AppCtxtName = "%%Apps/PTAv2::ptaAppName%%";
  document.NSCP_IVSPTA.PTA_Initialize(AppCtxtName, 0);
  document.NSCP_IVSPTA.ProfMgmt_CloseProfile() ;
  document.NSCP_IVSPTA.PTA_Close();
  GoToHome();
}
if (navigator.appName == "Netscape")
{
	window.setTimeout("DoLogoutNS()",1000);
}
</script>
<script language=VBScript>
<!--
  if (navigator.appName <> "Netscape") then
    dim appctxt
    dim ivsprofmgmt
    On Error Resume Next
    set ivsprofmgmt = IVSPTA.IVSProfMgmt
    On Error Resume Next
    appctxt = "%%Apps/PTAv2::ptaAppName%%"
    On Error Resume Next
    IVSPTA.Initialize appctxt, 0
    On Error Resume Next
    ivsprofmgmt.CloseProfile
    On Error Resume Next
    IVSPTA.Close
    Call GoToHome
  end if
-->
</script>
<!-- VSSKENDPOLICYVAL#verisign#33 -->

<!-- VSSKBEGINPOLICYVAL#verisign#34#1.2.0.5 -->
<script Language="JavaScript">
var browserNum;
var NSCP_IVSPTA;

browserNum=parseInt(navigator.appVersion);

function DoSave()
{	
	  if(browserNum < 5) {
		document.NSCP_IVSPTA = document.ThePlugin;
	  }else {
		document.NSCP_IVSPTA = document.ThePlugin.ns6IPTA;
	  }
	  
	  var AppCtxtName = "%%Apps/PTAv2::ptaAppName%%";
	  document.NSCP_IVSPTA.PTA_Initialize(AppCtxtName, 0);
	  if ( (ErrorCode = document.NSCP_IVSPTA.GetLastError()) != 0  ) {
	       SetErrorInfo ("../fdf/VSApps/client/PTAv2Errors.fdf", ReBaseErrorCodeNS(ErrorCode), ConvertToHexNS(ErrorCode), "Enroll::NSCP_IVSPTA.PTA_Initialize");
	  }
	  E_CARDNOTOPEN = 0x80001008;
	  document.NSCP_IVSPTA.ProfMgmt_SaveProfile();
	  if ( ((ErrorCode = document.NSCP_IVSPTA.GetLastError()) != 0 ) && (ErrorCode != E_CARDNOTOPEN ) ) {
	       SetErrorInfo ("../fdf/VSApps/client/PTAv2Errors.fdf", ReBaseErrorCodeNS(ErrorCode), ConvertToHexNS(ErrorCode), "Enroll::NSCP_IVSPTA.ProfMgmt_SaveProfile");
	  }
	  //document.NSCP_IVSPTA.ProfMgmt_CloseProfile() ;
	  document.NSCP_IVSPTA.PTA_Close();	
}

if (navigator.appName == "Netscape"){
	window.setTimeout("DoSave()", 1000);
}
</script>

<script language=VBScript>
<!--
  if (navigator.appName <> "Netscape") then
    dim appctxt
    dim ivsprofmgmt

	Dim TPMEnabled
	Dim boolTPMAvailable

	boolTPMAvailable = CBool(0)
	TPMEnabled = "%%Apps/PTAv2::ptaTPMOption%%"
	
	On Error Resume Next
	if(TPMEnabled = "CHECKED") then
		boolTPMAvailable = IVSPTA.IsTPMAvailable 
	End If	 

	if(TPMEnabled = "CHECKED" And boolTPMAvailable = "True") then
		appctxt = "%%Apps/PTAv2::ptaAppName%%"
		On Error Resume Next
		IVSPTA.Initialize appctxt, 2
		If (err.number <> 0) Then
			Call SetErrorInfo ("../fdf/VSApps/client/PTAv2Errors.fdf", CheckErrorCodeMS(Hex(err.number)),Hex(err.number), "Enroll::IVSPTA.Initialize")
		End If
		IVSPTA.Close
	else
		On Error Resume Next
		set ivsprofmgmt = IVSPTA.IVSProfMgmt
		On Error Resume Next
		appctxt = "%%Apps/PTAv2::ptaAppName%%"
		On Error Resume Next
		IVSPTA.Initialize appctxt, 0
		If (err.number <> 0) Then
			Call SetErrorInfo ("../fdf/VSApps/client/PTAv2Errors.fdf", CheckErrorCodeMS(Hex(err.number)),Hex(err.number), "Enroll::IVSPTA.Initialize")
		End If
		On Error Resume Next
		ivsprofmgmt.SaveProfile
		If ((err.number <> 0) And (Hex(err.number) <> "80001008")) Then
			Call SetErrorInfo ("../fdf/VSApps/client/PTAv2Errors.fdf", CheckErrorCodeMS(Hex(err.number)),Hex(err.number), "Enroll::IVSProfMgmt.SaveProfile")
		End If
		'On Error Resume Next
		'ivsprofmgmt.CloseProfile
		On Error Resume Next
		IVSPTA.Close
	  end if
  End If
-->
</script>
<!-- VSSKENDPOLICYVAL#verisign#34 -->

<!-- VSSKBEGINPOLICYVAL#verisign#35#1.2.0.4 -->
	xpi={'Symantec Personal Trust Agent':'../vspta3.xpi'};
    InstallTrigger.install(xpi,xpinstallCallback);
<!-- VSSKENDPOLICYVAL#verisign#35 -->

<!-- VSSKBEGINPOLICYVAL#verisign#36#1.0.0.1 -->
<!-- VSSKBEGIN Global/Mode#124 -->
<!-- VSSKEND Global/Mode#124 -->
<!-- VSSKENDPOLICYVAL#verisign#36 -->

<!-- VSSKBEGINPOLICYVAL#verisign#37 -->
<SCRIPT Language="VBScript">
<!--
    On Error Resume Next
    Set bExportable = Import.KeyExportable
	If ( (Hex(err.number) = "1B6") AND (InStr(1,navigator.appMinorVersion,";SP2;") > 0)  ) Then
         window.location = "./client/installComponentForSP2.htm"
    End If
-->
</SCRIPT>
<!-- VSSKENDPOLICYVAL#verisign#37 -->
<!-- VSSKBEGINPOLICYVAL#verisign#38 -->
try{
	dummy=Import.getName();
	temp = 1;
}catch(er){
	temp=0;
	window.open("../vsapps/error/win2k.htm","_self");
}
<!-- VSSKENDPOLICYVAL#verisign#38 -->

<!-- VSSKBEGINPOLICYVAL#verisign#39 -->
<!-- VSSKBEGIN Global/Mode#128 -->
<!-- VSSKEND Global/Mode#128 -->
<!-- VSSKENDPOLICYVAL#verisign#39 -->
