
<!-- VSSKBEGINPOLICYVAL#yes#1#1.0.0.3 -->
' the VBSCript variables made available on PTA login and transaction pages
 Dim strCertStore
 Dim strAppCtxtName
 Dim strIssuerDN
 Dim strLoginWizardTitle
 Dim strLoginChooseTitle 
 Dim strLoginChooseText
 Dim strLoginTitle
 Dim strLoginText
 Dim strAppLogoUrl
 Dim strAffiliateLogoUrl
 Dim AbtToExpWindow
 Dim strSignWizardTitle
 Dim strSignChooseTitle
 Dim strSignChooseText
 Dim strSignTitle
 Dim strSignText
 Dim strReviewTitle
 Dim strReviewText
 Dim saveLocal 
 Dim strClientInfo
 Dim strClientInfoSig

 Dim strLoginChooseHelpUrl 
 Dim strLoginHelpUrl
 Dim strSignHelpUrl 
 Dim strReviewHelpUrl
 Dim strSignChooseHelpUrl
 Dim strUnLockHelpUrl

 strCertStore = "%%ptaCertStore%%"
 strAppCtxtName = "%%ptaAppName%%"
 strIssuerDN = "%%::ptaIssuerDN%%"
 strLoginWizardTitle = "%%ptaLoginWizardTitle%%"
 strLoginChooseTitle = "%%ptaLoginChooseTitle%%"
 strLoginChooseText = "%%ptaLoginChooseText%%"
 strLoginTitle = "%%ptaLoginTitle%%"
 strLoginText = "%%ptaLoginText%%"
 strAppLogoUrl = "%%ptaAppLogoUrl%%"
 strAffiliateLogoUrl = "%%affiliateLogoURL%%"
 strSignWizardTitle = "%%ptaSignWizardTitle%%"
 strSignChooseTitle = "%%ptaLoginChooseTitle%%"
 strSignChooseText = "%%ptaLoginChooseText%%"
 strSignTitle = "%%ptaSignTitle%%"
 strSignText = "%%ptaSignText%%"
 strReviewTitle = "%%ptaReviewTitle%%"
 strReviewText = "%%ptaReviewText%%" 
 saveLocal = "%%Apps/PTAv2/Roaming::saveLocal%%"
 strClientInfo = "%%Apps/PTAv2/Roaming::clientInfo%%"
 strClientInfoSig = "%%Apps/PTAv2/Roaming::clientInfoSig%%"
 Dim TPMEnabled
 Dim boolTPMAvailable

 boolTPMAvailable = CBool(0)
 TPMEnabled = "%%Apps/PTAv2::ptaTPMOption%%"

 AbtToExpWindow = %%::AbtToExpireWindow%%

 '-- VSSKBEGIN Global/Mode#35 --
 '-- VSSKEND Global/Mode#35 --

 strLoginChooseHelpUrl = helpHostName & "%%ptaLoginChooseHelpUrl%%"
 strLoginHelpUrl = helpHostName & "%%ptaLoginHelpUrl%%"
 strSignHelpUrl = helpHostName & "%%ptaSignHelpUrl%%"
 strReviewHelpUrl = helpHostName & "%%ptaReviewHelpUrl%%"
 strSignChooseHelpUrl = helpHostName & "%%ptaSignChooseHelpUrl%%"
 strUnLockHelpUrl = helpHostName & "/VSApps/client/help/tasks/ptaunlock.htm"
<!-- VSSKENDPOLICYVAL#yes#1 -->

<!-- VSSKBEGINPOLICYVAL#yes#2#1.2.0.4 -->
<EMBED type=application/x-vspta2-plugin name="ThePlugin" WIDTH=0 HEIGHT=0 HIDDEN>
<!-- VSSKENDPOLICYVAL#yes#2 -->

<!-- VSSKBEGINPOLICYVAL#yes#3#1.0.0.2 -->
 // the JavaScript variables made available on PTA login page
 var strCertStore = "%%ptaCertStore%%";
 var strAppCtxtName = "%%ptaAppName%%";
 var strCertIssuerDN = "%%::ptaIssuerDN%%";
 var strLoginWizardTitle = "%%ptaLoginWizardTitle%%";
 var strLoginChooseTitle = "%%ptaLoginChooseTitle%%";
 var strLoginChooseText = "%%ptaLoginChooseText%%";
 var strLoginTitle = "%%ptaLoginTitle%%";
 var strLoginText = "%%ptaLoginText%%";
 var strAppLogoUrl = "%%ptaAppLogoUrl%%";
 var strAffiliateLogoUrl = "%%affiliateLogoURL%%";
 var strSignWizardTitle = "%%ptaSignWizardTitle%%";
 var strSignChooseTitle = "%%ptaLoginChooseTitle%%";
 var strSignChooseText = "%%ptaLoginChooseText%%";
 var strSignTitle = "%%ptaSignTitle%%";
 var strSignText = "%%ptaSignText%%";
 var strReviewTitle = "%%ptaReviewTitle%%";
 var strReviewText = "%%ptaReviewText%%";
 var saveLocal = "%%Apps/PTAv2/Roaming::saveLocal%%";
 var strClientInfo = "%%Apps/PTAv2/Roaming::clientInfo%%";
 var strClientInfoSig = "%%Apps/PTAv2/Roaming::clientInfoSig%%";


 var AbtToExpWindow = %%::AbtToExpireWindow%%;

 //-- VSSKBEGIN Global/Mode#36 --
 //-- VSSKEND Global/Mode#36 --

 var strLoginChooseHelpUrl = helpHostName + "%%ptaLoginChooseHelpUrl%%";
 var strLoginHelpUrl = helpHostName + "%%ptaLoginHelpUrl%%";
 var strSignHelpUrl = helpHostName + "%%ptaSignHelpUrl%%";
 var strReviewHelpUrl = helpHostName + "%%ptaReviewHelpUrl%%";
 var strSignChooseHelpUrl = helpHostName + "%%ptaSignChooseHelpUrl%%";
 var strUnLockHelpUrl = helpHostName + "/VSApps/client/help/tasks/ptaunlock.htm";
<!-- VSSKENDPOLICYVAL#yes#3 -->

<!-- VSSKBEGINPOLICYVAL#yes#4 -->
	self.location = "%%ptaAppHomeUrl%%";
<!-- VSSKENDPOLICYVAL#yes#4 -->

<!-- VSSKBEGINPOLICYVAL#yes#5#1.0.0.3 -->
  ' the VBSCript variables made available on PTA enrollment pages
  Dim strCertStore
  Dim strAppCtxtName
  Dim strAppLogoUrl
  Dim strAffiliateLogoUrl
  Dim strNewPasswordTitle
  Dim strNewPasswordText
  Dim passwordQuality
  Dim passwordLength
  Dim passwordTimeOut
  Dim passwordTries
  Dim passwordUnlockPeriod
  Dim saveLocal 
  Dim strClientInfo
  Dim strClientInfoSig

  
  Dim strNewProfileHelpUrl
  Dim TPMEnabled


  TPMEnabled = "%%ptaTPMOption%%"

  strCertStore = "%%ptaCertStore%%"
  strAppCtxtName = "%%ptaAppName%%"
  strAppLogoUrl = "%%ptaAppLogoUrl%%"
  strAffiliateLogoUrl = "%%affiliateLogoURL%%"
  strNewPasswordTitle = "%%ptaNewProfileTitle%%"
  strNewPasswordText = "%%ptaNewProfileText%%"
  passwordQuality = "%%ptaPasswordQuality%%"
  passwordLength = "%%ptaPasswordLength%%"
  passwordTimeOut = "%%ptaPasswordTimeout%%"
  passwordTries = "%%ptaPasswordLockout%%"
  passwordUnlockPeriod = "%%ptaPasswordUnlock%%"
  saveLocal = "%%Apps/PTAv2/Roaming::saveLocal%%"
  strClientInfo = "%%Apps/PTAv2/Roaming::clientInfo%%"
  strClientInfoSig = "%%Apps/PTAv2/Roaming::clientInfoSig%%"
  
 '-- VSSKBEGIN Global/Mode#35 --
 '-- VSSKEND Global/Mode#35 --

  strNewProfileHelpUrl = helpHostName & "%%ptaNewProfileHelpUrl%%"
<!-- VSSKENDPOLICYVAL#yes#5 -->


<!-- VSSKBEGINPOLICYVAL#yes#6#1.0.0.2 -->
  // the JavaScript variables made available on PTA enrollment pages
  var strCertStore = "%%ptaCertStore%%";
  var strAppCtxtName = "%%ptaAppName%%";
  var strAppLogoUrl = "%%ptaAppLogoUrl%%";
  var strAffiliateLogoUrl = "%%affiliateLogoURL%%";
  var strNewPasswordTitle = "%%ptaNewProfileTitle%%";
  var strNewPasswordText = "%%ptaNewProfileText%%";
  var passwordQuality = "%%ptaPasswordQuality%%";
  var passwordLength = "%%ptaPasswordLength%%";
  var passwordTimeOut = "%%ptaPasswordTimeout%%";
  var passwordTries = "%%ptaPasswordLockout%%";
  var passwordUnlockPeriod = "%%ptaPasswordUnlock%%";
  var saveLocal = "%%Apps/PTAv2/Roaming::saveLocal%%";
  var strClientInfo = "%%Apps/PTAv2/Roaming::clientInfo%%";
  var strClientInfoSig = "%%Apps/PTAv2/Roaming::clientInfoSig%%";

 //-- VSSKBEGIN Global/Mode#36 --
 //-- VSSKEND Global/Mode#36 --

  var strNewProfileHelpUrl = helpHostName + "%%ptaNewProfileHelpUrl%%";
<!-- VSSKENDPOLICYVAL#yes#6 -->

<!-- VSSKBEGINPOLICYVAL#yes#7#1.2.0.6 -->
<SCRIPT LANGUAGE="JavaScript">
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
<!-- VSSKENDPOLICYVAL#yes#7 -->


<!-- VSSKBEGINPOLICYVAL#yes#8 -->
<!-- VSSKBEGIN Global/Mode#101 -->
<!-- VSSKEND Global/Mode#101 -->
<!-- VSSKBEGIN Enrollment/KeyExportable#5 -->
<!-- VSSKEND Enrollment/KeyExportable#5 -->

<!-- VSSKENDPOLICYVAL#yes#8 -->


<!-- VSSKBEGINPOLICYVAL#yes#9 -->
<!-- the AddRootCerts control -->
  <!-- VSSKBEGIN Apps/AddRoots#5 -->
  <!-- VSSKEND Apps/AddRoots#5 -->
<!-- VSSKENDPOLICYVAL#yes#9 -->


<!-- VSSKBEGINPOLICYVAL#yes#10 -->
<BR>
<TABLE WIDTH=588 CELLPADDING=2 CELLSPACING=0 BORDER=0>
<TR>
    <TD><IMG SRC="../VSApps/graphics/space.gif" border="0" WIDTH=432 HEIGHT=1 HSPACE=0 VSPACE=0></TD>

    <TD><A HREF="%%ptaAppHomeUrl%%"><IMG SRC="../VSApps/graphics/button_continue.gif" border="0" WIDTH=121 HEIGHT=39 BORDER=0 ALT="Continue"></A></TD>
</TR>
</TABLE>
<!-- VSSKENDPOLICYVAL#yes#10 -->


// for userInstallMS.htm and userRenewalInstallMS.htm
<!-- VSSKBEGINPOLICYVAL#yes#11 -->
<SCRIPT LANGUAGE=VBScript>
<!--
  Call SetPreferences
'-->
</SCRIPT>

<!-- VSSKBEGIN Apps/AddRoots#2 -->
<!-- VSSKEND Apps/AddRoots#2 -->
<!-- VSSKENDPOLICYVAL#yes#11 -->

<!-- VSSKBEGINPOLICYVAL#yes#12#1.2.0.8 -->
<Script Language="VBScript">
<!--
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
  
  Dim strCertStore 
  Dim strAppCtxtName
  Dim strIssuerDN
  Dim strCertSerial 
  Dim strCertLogoUrl
  Dim strCertFriendlyName
  Dim strCertTextureUrl
  Dim strChooseProfileText 
  Dim strChooseProfileTitle 
  Dim saveLocal 
  Dim strClientInfo
  Dim strClientInfoSig
  Dim strChooseHelpUrl 
  Dim strAffiliateLogoUrl

 '-- VSSKBEGIN Global/Mode#35 --
 '-- VSSKEND Global/Mode#35 --

  strChooseHelpUrl = helpHostName & "%%ptaLoginChooseHelpUrl%%"  
  strCertStore = "%%ptaCertStore%%"
  strAppCtxtName = "%%ptaAppName%%"
  strIssuerDN = "%%::ptaIssuerDN%%"
  strCertSerial = "$$cert_serial$$"
  strCertLogoUrl = "%%ptaCertLogoURL%%"
  strCertFriendlyName = "%%ptaCertFriendlyName%%"
  strCertTextureUrl = "%%ptaCertTextureURL%%"
  strChooseProfileTitle = "Open Profile"
  strChooseProfileText = "Choose the profile in which you want to install the Digital ID."
  saveLocal = "%%Apps/PTAv2/Roaming::saveLocal%%"
  strClientInfo = "%%Apps/PTAv2/Roaming::clientInfo%%"
  strClientInfoSig = "%%Apps/PTAv2/Roaming::clientInfoSig%%"
    
  strAppLogoUrl = "%%ptaAppLogoUrl%%"
  strAffiliateLogoUrl = "%%affiliateLogoURL%%"
  
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
  
  
  Sub SetPreferences
  	Dim TPMEnabled
	Dim boolTPMAvailable

	boolTPMAvailable = CBool(0)
	TPMEnabled = "%%ptaTPMOption%%"
	
	On Error Resume Next
	if(TPMEnabled = "CHECKED") then
		boolTPMAvailable = IVSPTA.IsTPMAvailable 
	End If
	if(TPMEnabled = "CHECKED" And boolTPMAvailable = "True") then
		if ("%%Enrollment/CertStore::policyValue%%" = "verisign") then
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
		End If

		' the certificate is installed one way or the other so set the preferences. 
		On Error Resume Next
		if (Len (strIssuerDN) = 0) then 
			Call CloseObjects("00000103", "Empty Issuer DN", "00000000")
			Exit Sub 
		end if
		IVSCertPrefs.CertIssDN = strIssuerDN
		If ( err.number <> 0 ) then
		  Call CloseObjects("00000103", "IVSCertPrefs.CertIssDN", Hex(err.number))
		  Exit Sub
		End If

		On Error Resume Next
		if (Len (strCertSerial) = 0) then 
			Call CloseObjects("00000103", "Blank Serial Number", "00000000")
			Exit Sub 
		end if
		On Error Resume Next
		IVSCertPrefs.CertSerNum = strCertSerial
		If ( err.number <> 0 ) then
		  Call CloseObjects(Hex(err.number), "Digital ID Install::IVSCertPrefs.CertISerNum", Hex(err.number))
		  Exit Sub
		End If

		On Error Resume Next
		If (Len (strCertLogoUrl) <> 0) then 
		   IVSCertPrefs.CertLogoUrl = strCertLogoUrl
		   If ( err.number <> 0 ) then
			  Call CloseObjects(Hex(err.number), "Digital ID Install::IVSCertPrefs.CertLogoUrl", Hex(err.number))
			  Exit Sub
		   End If
		End If 

		On Error Resume Next
		If (Len (strCertFriendlyName) <> 0) then 
		   IVSCertPrefs.CertFrndlyName = strCertFriendlyName
		   If ( err.number <> 0 ) then
				Call CloseObjects(Hex(err.number), "Digital ID Install::IVSCertPrefs.CertFrndlyName", Hex(err.number))
				Exit Sub
		   End If   
		End If  

		On Error Resume Next
		If (Len (strCertTextureUrl) <> 0) then 
		   IVSCertPrefs.CertTextureUrl = strCertTextureUrl
		   If ( err.number <> 0 ) then
				Call CloseObjects(Hex(err.number), "Digital ID Install::IVSCertPrefs.CertTextureUrl", Hex(err.number))
				Exit Sub
		   End If   
		End If  

	else
		if ("%%Enrollment/CertStore::policyValue%%" = "verisign") then 
		   IVSPTA.Initialize strAppCtxtName,0
		else
		   IVSPTA.Initialize strAppCtxtName,1
		End If	
		If ( err.number <> 0 ) then
		  'MsgBox "Error in IVSPTA.PTA_Initialize." & vbCRLF & _
		  '			"Error Number : 0x" & CStr(Hex(err.number))
		  Call CloseObjects(Hex(err.number), "Digital ID Install::IVSPTA.Initialize", Hex(err.number))      
		  Exit Sub
		End If

		'MsgBox "PTA Initialized"
    
		if ( "%%Enrollment/CertStore::policyValue%%" = "verisign" ) then 
			' set the open profile preferences and install the certificate 
			On Error Resume Next
			If (Len(strChooseProfileTitle) <> 0) then
				IVSUIPrefs.OpenProf_Title = strChooseProfileTitle
				If ( err.number <> 0 ) then
					Call CloseObjects(Hex(err.number), "Digital ID Install::IVSUIPrefs.OpenProf_Title", Hex(err.number))
					Exit Sub
				End If
			End If

			On Error Resume Next
			If (Len(strChooseProfileText) <> 0) then
				IVSUIPrefs.OpenProf_Text = strChooseProfileText
				If ( err.number <> 0 ) then
					Call CloseObjects(Hex(err.number), "Digital ID Install::IVSUIPrefs.OpenProf_Text", Hex(err.number))
					Exit Sub
				End If
			End If

			On Error Resume Next
			If (Len(strChooseHelpUrl) <> 0) then
				IVSUIPrefs.OpenProf_HelpUrl = strChooseHelpUrl
				If ( err.number <> 0 ) then
					Call CloseObjects(Hex(err.number), "Digital ID Install::IVSUIPrefs.OpenProf_HelpUrl", Hex(err.number))
					Exit Sub
				End If
			End If

			
			'Flags
			OPENPROF_OPEN_ONLY = CInt(529)
			On Error Resume Next
			IVSProfMgmt.OpenProfFlags = OPENPROF_OPEN_ONLY
			If ((err.number <> 0) And (Hex(err.number) <> "8000102F") ) Then
				Call CloseObjects(Hex(err.number), "Digital ID Install::IVSProfMgmt.OpenProfFlags", Hex(err.number))
				Exit Sub
			End If

				   On Error Resume Next
				   If (Len(strAppLogoUrl) <> 0) then
      				  IVSUIPrefs.UILogoUrl = strAppLogoUrl
					  If ( err.number <> 0 ) then
						Call CloseObjects(Hex(err.number), "Digital ID Install::IVSUIPrefs.LogoUrl", Hex(err.number))
				Exit Sub
					  End If
			   End If

			On Error Resume Next
			If (Len(strAffiliateLogoUrl) <> 0 And strAffiliateLogoUrl <> "VeriSign") then
      			 IVSPTA.AffLogoUrl = strAffiliateLogoUrl
				 If ( err.number <> 0  And err.number <> &h800010c4 ) then
					   Call CloseObjects(Hex(err.number), "Digital ID Install::IVSPTA.AffLogoUrl", Hex(err.number))
					   Exit Sub
				 End If
			End If

					'-- VSSKBEGIN Apps/PTAv2/Roaming#3 --
					'-- VSSKEND Apps/PTAv2/Roaming#3 --
			
			'open the profile 
			'On Error Resume Next
			'IVSProfMgmt.OpenProfile
					'if (Hex(err.number) = "80001067") Then
					'    Call CloseObjects(Hex(err.number), "Digital ID Install::IVSProfMgmt.OpenProfile", Hex(err.number))
					'    Exit Sub
					'End if
			'if ( (err.number <> 0) And (Hex(err.number) <> "8000102F") ) then
					'    Call CloseObjects(Hex(err.number), "Digital ID Install::IVSProfMgmt.OpenProfile", Hex(err.number))
			'    Exit Sub
			'End If 
			
			' at this instance the profile is open one way or the other
			' so install the certificate
					On Error Resume Next
			IVSPTA.InstallCert CertChain
			if (err.number <> 0) then
						Call CloseObjects(Hex(err.number), "Digital ID Install::IVSPTA.InstallCert", Hex(err.number))
				Exit Sub
					end if 
		end if
    
		' the certificate is installed one way or the other so set the preferences. 
		On Error Resume Next
		if (Len (strIssuerDN) = 0) then 
			Call CloseObjects("00000103", "Empty Issuer DN", "00000000")
			Exit Sub 
		end if
		IVSCertPrefs.CertIssDN = strIssuerDN
		If ( err.number <> 0 ) then
		  Call CloseObjects("00000103", "IVSCertPrefs.CertIssDN", Hex(err.number))
		  Exit Sub
		End If

		On Error Resume Next
		if (Len (strCertSerial) = 0) then 
			Call CloseObjects("00000103", "Blank Serial Number", "00000000")
			Exit Sub 
		end if
		On Error Resume Next
		IVSCertPrefs.CertSerNum = strCertSerial
		If ( err.number <> 0 ) then
		  Call CloseObjects(Hex(err.number), "Digital ID Install::IVSCertPrefs.CertISerNum", Hex(err.number))
		  Exit Sub
		End If

		On Error Resume Next
		If (Len (strCertLogoUrl) <> 0) then 
		   IVSCertPrefs.CertLogoUrl = strCertLogoUrl
		   If ( err.number <> 0 ) then
			  Call CloseObjects(Hex(err.number), "Digital ID Install::IVSCertPrefs.CertLogoUrl", Hex(err.number))
			  Exit Sub
		   End If
		End If 

		On Error Resume Next
		If (Len (strCertFriendlyName) <> 0) then 
		   IVSCertPrefs.CertFrndlyName = strCertFriendlyName
		   If ( err.number <> 0 ) then
				Call CloseObjects(Hex(err.number), "Digital ID Install::IVSCertPrefs.CertFrndlyName", Hex(err.number))
				Exit Sub
		   End If   
		End If  
    
		On Error Resume Next
		If (Len (strCertTextureUrl) <> 0) then 
		   IVSCertPrefs.CertTextureUrl = strCertTextureUrl
		   If ( err.number <> 0 ) then
				Call CloseObjects(Hex(err.number), "Digital ID Install::IVSCertPrefs.CertTextureUrl", Hex(err.number))
				Exit Sub
		   End If   
		End If  
    
		if ( "%%Enrollment/CertStore::policyValue%%" = "verisign" ) then 
		   On Error Resume Next
		   IVSProfMgmt.SaveProfile
		   If ( err.number <> 0 ) then
				Call CloseObjects(Hex(err.number), "Digital ID Install::IVSProfMgmt.SaveProfile", Hex(err.number))
				Exit Sub
		   End If   

		   On Error Resume Next
		   IVSProfMgmt.CloseProfile
		   If ( err.number <> 0 ) then
				Call CloseObjects(Hex(err.number), "Digital ID Install::IVSProfMgmt.CloseProfile", Hex(err.number))
				Exit Sub
		   End If   

		End If
	End If
	
    Call CloseObjects(0, "", 0)    
  End Sub
'-->
</Script>

<!-- VSSKBEGIN Apps/AddRoots#1 -->
<!-- VSSKEND Apps/AddRoots#1 -->
<!-- VSSKENDPOLICYVAL#yes#12 -->

<!-- VSSKBEGINPOLICYVAL#yes#13#1.2.0.6 -->
var strCertStore = "%%ptaCertStore%%";
var strAppCtxtName = "%%ptaAppName%%";
var strIssuserDN = "%%::ptaIssuerDN%%";
var strCertLogoUrl = "%%ptaCertLogoURL%%";
var strAppLogoUrl = "%%ptaAppLogoUrl%%";
var strAffiliateLogoUrl = "%%affiliateLogoURL%%";
var strCertFriendlyName = "%%ptaCertFriendlyName%%";
var strCertTextureUrl = "%%ptaCertTextureURL%%";
var PTAHome = "%%ptaAppHomeUrl%%";
var ptaEnabled = 1;
var enrollStore = "%%Enrollment/CertStore::policyValue%%";
var kmProvider = "%%Apps/KeyManager::provName%%";
var saveLocal = "%%Apps/PTAv2/Roaming::saveLocal%%";
var strClientInfo = "%%Apps/PTAv2/Roaming::clientInfo%%";
var strClientInfoSig = "%%Apps/PTAv2/Roaming::clientInfoSig%%";
 //-- VSSKBEGIN Global/Mode#36 --
 //-- VSSKEND Global/Mode#36 --

var strChooseHelpUrl = helpHostName + "%%ptaLoginChooseHelpUrl%%";
<!-- VSSKENDPOLICYVAL#yes#13 -->


<!-- VSSKBEGINPOLICYVAL#yes#14#1.2.0.8 -->
<Script Language="VBScript">
<!--
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
  
  Dim strCertStore 
  Dim strAppCtxtName
  Dim strIssuerDN
  Dim strCertSerial 
  Dim strCertLogoUrl
  Dim strCertFriendlyName
  Dim strCertTextureUrl
  Dim strChooseProfileText 
  Dim strChooseProfileTitle 
  Dim saveLocal
  Dim strClientInfo
  Dim strClientInfoSig
  Dim strChooseHelpUrl 
  Dim strAffiliateLogoUrl

 '-- VSSKBEGIN Global/Mode#35 --
 '-- VSSKEND Global/Mode#35 --

  strChooseHelpUrl = helpHostName & "%%ptaLoginChooseHelpUrl%%"    
  strCertStore = "%%ptaCertStore%%"
  strAppCtxtName = "%%ptaAppName%%"
  strIssuerDN = "%%::ptaIssuerDN%%"
  strCertSerial = "$$cert_serial$$"
  strCertLogoUrl = "%%ptaCertLogoURL%%"
  strCertFriendlyName = "%%ptaCertFriendlyName%%"
  strCertTextureUrl = "%%ptaCertTextureURL%%"
  strChooseProfileTitle = "Open Profile"
  strChooseProfileText = "Choose the profile in which you want to install the Digital ID."
  saveLocal = "%%Apps/PTAv2/Roaming::saveLocal%%"
  strClientInfo = "%%Apps/PTAv2/Roaming::clientInfo%%"
  strClientInfoSig = "%%Apps/PTAv2/Roaming::clientInfoSig%%"
  
  strAppLogoUrl = "%%ptaAppLogoUrl%%"
  strAffiliateLogoUrl = "%%affiliateLogoURL%%"
  
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
  
  
  Sub SetPreferences
    Dim KeyBlob
    Dim PKCS7Msg

    if ("%%Enrollment/CertStore::policyValue%%" = "verisign") then 
	   IVSPTA.Initialize strAppCtxtName,0
    else
	   IVSPTA.Initialize strAppCtxtName,1
    End If	
    If ( err.number <> 0 ) then
      Call CloseObjects(Hex(err.number), "Digital ID Install::IVSPTA.Initialize", Hex(err.number))      
      Exit Sub
    End If

    'MsgBox "PTA Initialized"
    
    if ( "%%Enrollment/CertStore::policyValue%%" = "verisign") then 
        ' set the open profile preferences and install the certificate 
        On Error Resume Next
		If (Len(strChooseProfileTitle) <> 0) then
			IVSUIPrefs.OpenProf_Title = strChooseProfileTitle
			If ( err.number <> 0 ) then
				Call CloseObjects(Hex(err.number), "Digital ID Install::IVSUIPrefs.OpenProf_Title", Hex(err.number))
				Exit Sub
			End If
		End If

		On Error Resume Next
		If (Len(strChooseProfileText) <> 0) then
			IVSUIPrefs.OpenProf_Text = strChooseProfileText
			If ( err.number <> 0 ) then
				Call CloseObjects(Hex(err.number), "Digital ID Install::IVSUIPrefs.OpenProf_Text", Hex(err.number))
				Exit Sub
			End If
		End If

		On Error Resume Next
		If (Len(strChooseHelpUrl) <> 0) then
			IVSUIPrefs.OpenProf_HelpUrl = strChooseHelpUrl
			If ( err.number <> 0 ) then
				Call CloseObjects(Hex(err.number), "Digital ID Install::IVSUIPrefs.OpenProf_HelpUrl", Hex(err.number))
				Exit Sub
			End If
		End If
		
		'Flags
		OPENPROF_OPEN_ONLY = CInt(529)
		On Error Resume Next
		IVSProfMgmt.OpenProfFlags = OPENPROF_OPEN_ONLY
		If ((err.number <> 0) And (Hex(err.number) <> "8000102F") ) Then
			Call CloseObjects(Hex(err.number), "Digital ID Install::IVSProfMgmt.OpenProfFlags", Hex(err.number))
			Exit Sub
		End If

               On Error Resume Next
               If (Len(strAppLogoUrl) <> 0) then
      	          IVSUIPrefs.UILogoUrl = strAppLogoUrl
                  If ( err.number <> 0 ) then
                    Call CloseObjects(Hex(err.number), "Digital ID Install::IVSUIPrefs.LogoUrl", Hex(err.number))
		    Exit Sub
                  End If
	       End If

        On Error Resume Next
        If (Len(strAffiliateLogoUrl) <> 0 And strAffiliateLogoUrl <> "VeriSign") then
      	     IVSPTA.AffLogoUrl = strAffiliateLogoUrl
             If ( err.number <> 0 And err.number <> &h800010c4 ) then
                   Call CloseObjects(Hex(err.number), "Digital ID Install::IVSPTA.AffLogoUrl", Hex(err.number))
		           Exit Sub
             End If
	    End If

                '-- VSSKBEGIN Apps/PTAv2/Roaming#3 --
                '-- VSSKEND Apps/PTAv2/Roaming#3 --
		
		'open the profile 
		'On Error Resume Next
		'IVSProfMgmt.OpenProfile
                'if (Hex(err.number) = "80001067") Then
                '    Call CloseObjects(Hex(err.number), "Digital ID Install::IVSProfMgmt.OpenProfile", Hex(err.number))
                '    Exit Sub
                'End if 
		'if ( (err.number <> 0) And (Hex(err.number) <> "8000102F") ) then
                '    Call CloseObjects(Hex(err.number), "Digital ID Install::IVSProfMgmt.OpenProfile", Hex(err.number))
		'    Exit Sub
		'End If 
		
                KeyBlob = "$$pkcs8_blob$$"
                PKCS7Msg = CertChain

		' at this instance the profile is open one way or the other
		' so install the certificate
                On Error Resume Next
                IVSPTA.InstallKeyPair KeyBlob, PKCS7Msg
		if (err.number <> 0) then
                    Call CloseObjects(Hex(err.number), "Digital ID Install::IVSPTA.InstallKeyPair", Hex(err.number))
		    Exit Sub
                end if 
    end if

    ' Mark old cert as renewed.
    if ( "true" = processOldCert ) then
        OrigIssDN = strIssuerDN

        ' the certificate is installed one way or the other so set the preferences. 
        On Error Resume Next
        if (Len (OrigIssDN) = 0) then 
            Call CloseObjects("00000103", "Digital ID Install::Empty Issuer DN", "00000000")
            Exit Sub 
        end if

        if (Len (OrigSerNum) = 0) then 
            Call CloseObjects("00000103", "Digital ID Install::Blank Original Serial Number", "00000000")
            Exit Sub 
        end if

        ' the certificate is installed one way or the other so set the preferences. 
        On Error Resume Next
        IVSCertPrefs.CertSerNum = OrigSerNum
        If ( err.number <> 0 ) then
          Call CloseObjects(Hex(err.number), "Digital ID Install::IVSCertPrefs.CertSerNum", Hex(err.number))
          Exit Sub
        End If

        On Error Resume Next
        IVSCertPrefs.MarkAsRenewed = TRUE
        If ( err.number <> 0 ) then
          Call CloseObjects(Hex(err.number), "Digital ID Install::IVSCertPrefs.MarkAsRenewed", Hex(err.number))
          Exit Sub
        End If

        On Error Resume Next
        IVSCertPrefs.CertIssDN = OrigIssDN
        If ( err.number <> 0 ) then
          Call CloseObjects(Hex(err.number), "Digital ID Install::IVSCertPrefs.CertIssDN", Hex(err.number))
          Exit Sub
        End If
    end if
    
    ' the certificate is installed one way or the other so set the preferences. 
    On Error Resume Next
    if (Len (strCertSerial) = 0) then 
        Call CloseObjects("00000103", "Blank Serial Number", "00000000")
        Exit Sub 
    end if
    On Error Resume Next
    IVSCertPrefs.CertSerNum = strCertSerial
    If ( err.number <> 0 ) then
      Call CloseObjects(Hex(err.number), "Digital ID Install::IVSCertPrefs.CertISerNum", Hex(err.number))
      Exit Sub
    End If

    On Error Resume Next
    If (Len (strCertLogoUrl) <> 0) then 
       IVSCertPrefs.CertLogoUrl = strCertLogoUrl
       If ( err.number <> 0 ) then
          Call CloseObjects(Hex(err.number), "Digital ID Install::IVSCertPrefs.CertLogoUrl", Hex(err.number))
          Exit Sub
       End If
    End If 

    On Error Resume Next
    If (Len (strCertFriendlyName) <> 0) then 
       IVSCertPrefs.CertFrndlyName = strCertFriendlyName
       If ( err.number <> 0 ) then
            Call CloseObjects(Hex(err.number), "Digital ID Install::IVSCertPrefs.CertFrndlyName", Hex(err.number))
            Exit Sub
       End If   
    End If  
    
    On Error Resume Next
    If (Len (strCertTextureUrl) <> 0) then 
       IVSCertPrefs.CertTextureUrl = strCertTextureUrl
       If ( err.number <> 0 ) then
            Call CloseObjects(Hex(err.number), "Digital ID Install::IVSCertPrefs.CertTextureUrl", Hex(err.number))
            Exit Sub
       End If   
    End If  

    On Error Resume Next
    if (Len (strIssuerDN) = 0) then 
        Call CloseObjects("00000103", "Empty Issuer DN", "00000000")
        Exit Sub 
    end if
    IVSCertPrefs.CertIssDN = strIssuerDN
    If ( err.number <> 0 ) then
      Call CloseObjects("00000103", "IVSCertPrefs.CertIssDN", Hex(err.number))
      Exit Sub
    End If

    if ( "%%Enrollment/CertStore::policyValue%%" = "verisign" ) then 
       On Error Resume Next
       IVSProfMgmt.SaveProfile
       If ( err.number <> 0 ) then
            Call CloseObjects(Hex(err.number), "Digital ID Install::IVSProfMgmt.SaveProfile", Hex(err.number))
            Exit Sub
       End If   

       On Error Resume Next
       IVSProfMgmt.CloseProfile
       If ( err.number <> 0 ) then
            Call CloseObjects(Hex(err.number), "Digital ID Install::IVSProfMgmt.CloseProfile", Hex(err.number))
            Exit Sub
       End If   
    End If
    
    Call CloseObjects(0, "", 0)    
  End Sub
'-->
</Script>

<!-- VSSKBEGIN Apps/AddRoots#1 -->
<!-- VSSKEND Apps/AddRoots#1 -->
<!-- VSSKENDPOLICYVAL#yes#14 -->


<!-- VSSKBEGINPOLICYVAL#yes#15#1.2.0.7 -->
<Script Language="VBScript">
<!--
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
  
  Dim strCertStore 
  Dim strAppCtxtName
  Dim strIssuerDN
  Dim strCertSerial 
  Dim strCertLogoUrl
  Dim strCertFriendlyName
  Dim strCertTextureUrl
  Dim strChooseProfileText 
  Dim strChooseProfileTitle 
  Dim saveLocal
  Dim strClientInfo
  Dim strClientInfoSig
  Dim strChooseHelpUrl 
  Dim strAffiliateLogoUrl

 '-- VSSKBEGIN Global/Mode#35 --
 '-- VSSKEND Global/Mode#35 --

  strChooseHelpUrl = helpHostName & "%%ptaLoginChooseHelpUrl%%"    
  strCertStore = "%%ptaCertStore%%"
  strAppCtxtName = "%%ptaAppName%%"
  strIssuerDN = "%%::ptaIssuerDN%%"
  strCertSerial = "$$cert_serial$$"
  strCertLogoUrl = "%%ptaCertLogoURL%%"
  strCertFriendlyName = "%%ptaCertFriendlyName%%"
  strCertTextureUrl = "%%ptaCertTextureURL%%"
  strChooseProfileTitle = "Open Profile"
  strChooseProfileText = "Choose the profile in which you want to install the Digital ID."
  saveLocal = "%%Apps/PTAv2/Roaming::saveLocal%%"
  strClientInfo = "%%Apps/PTAv2/Roaming::clientInfo%%"
  strClientInfoSig = "%%Apps/PTAv2/Roaming::clientInfoSig%%"

  
  strAppLogoUrl = "%%ptaAppLogoUrl%%"
  strAffiliateLogoUrl = "%%affiliateLogoURL%%"
  
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
  
  
  Sub SetPreferences
    Dim KeyBlob
    Dim PKCS7Msg
    Dim sz10

    if ("%%Enrollment/CertStore::policyValue%%" = "verisign") then 
	   IVSPTA.Initialize strAppCtxtName,0
    else
	   IVSPTA.Initialize strAppCtxtName,1
    End If	
    If ( err.number <> 0 ) then
      Call CloseObjects(Hex(err.number), "Digital ID Install::IVSPTA.Initialize", Hex(err.number))
      Exit Sub
    End If
    
    if ( "%%Enrollment/CertStore::policyValue%%" = "verisign") then 
        ' set the open profile preferences and install the certificate 
        On Error Resume Next
		If (Len(strChooseProfileTitle) <> 0) then
			IVSUIPrefs.OpenProf_Title = strChooseProfileTitle
			If ( err.number <> 0 ) then
				Call CloseObjects(Hex(err.number), "Digital ID Install::IVSUIPrefs.OpenProf_Title", Hex(err.number))
				Exit Sub
			End If
		End If

		On Error Resume Next
		If (Len(strChooseProfileText) <> 0) then
			IVSUIPrefs.OpenProf_Text = strChooseProfileText
			If ( err.number <> 0 ) then
				Call CloseObjects(Hex(err.number), "Digital ID Install::IVSUIPrefs.OpenProf_Text", Hex(err.number))
				Exit Sub
			End If
		End If

		On Error Resume Next
		If (Len(strChooseHelpUrl) <> 0) then
			IVSUIPrefs.OpenProf_HelpUrl = strChooseHelpUrl
			If ( err.number <> 0 ) then
				Call CloseObjects(Hex(err.number), "Digital ID Install::IVSUIPrefs.OpenProf_HelpUrl", Hex(err.number))
				Exit Sub
			End If
		End If
		
		'Flags
		OPENPROF_OPEN_ONLY = CInt(529)
		On Error Resume Next
		IVSProfMgmt.OpenProfFlags = OPENPROF_OPEN_ONLY
		If ((err.number <> 0) And (Hex(err.number) <> "8000102F") ) Then
			Call CloseObjects(Hex(err.number), "Digital ID Install::IVSProfMgmt.OpenProfFlags", Hex(err.number))
			Exit Sub
		End If

               On Error Resume Next
               If (Len(strAppLogoUrl) <> 0) then
      	          IVSUIPrefs.UILogoUrl = strAppLogoUrl
                  If ( err.number <> 0 ) then
                    Call CloseObjects(Hex(err.number), "Digital ID Install::IVSUIPrefs.LogoUrl", Hex(err.number))
		    Exit Sub
                  End If
	       End If

        On Error Resume Next
        If (Len(strAffiliateLogoUrl) <> 0 And strAffiliateLogoUrl <> "VeriSign") then
      	     IVSPTA.AffLogoUrl = strAffiliateLogoUrl
             If ( err.number <> 0 And err.number <> &h800010c4 ) then
                   Call CloseObjects(Hex(err.number), "Digital ID Install::IVSPTA.AffLogoUrl", Hex(err.number))
		           Exit Sub
             End If
	    End If

                '-- VSSKBEGIN Apps/PTAv2/Roaming#3 --
                '-- VSSKEND Apps/PTAv2/Roaming#3 --
		
		'open the profile 
		'On Error Resume Next
		'IVSProfMgmt.OpenProfile
                'if (Hex(err.number) = "80001067") Then
                '    Call CloseObjects(Hex(err.number), "Digital ID Install::IVSProfMgmt.OpenProfile", Hex(err.number))
                '    Exit Sub
                'end if 
		'if ( (err.number <> 0) And (Hex(err.number) <> "8000102F") ) then
                '    Call CloseObjects(Hex(err.number), "Digital ID Install::IVSProfMgmt.OpenProfile", Hex(err.number))
		'    Exit Sub
		'End If 

                'MsgBox "Installing the signing cert"

    
                sz10 = "$$cert_base64_for_VBScript$$"
                On Error Resume Next
		IVSPTA.InstallCert sz10
		if (err.number <> 0) then
                    Call CloseObjects(Hex(err.number), "Digital ID Install::IVSPTA.InstallCert", Hex(err.number))
		    Exit Sub
                end if 

                'MsgBox "Installed signing cert now installing encryption cert"
		
                KeyBlob = "$$pkcs8_blob$$"
                PKCS7Msg = CertChain

		' at this instance the profile is open one way or the other
		' so install the certificate
                On Error Resume Next
                IVSPTA.InstallKeyPair KeyBlob, PKCS7Msg
		if (err.number <> 0) then
                    Call CloseObjects(Hex(err.number), "Digital ID Install::IVSPTA.InstallKeyPair", Hex(err.number))
		    Exit Sub
                end if 
    end if
    
    ' the certificate is installed one way or the other so set the preferences. 
    On Error Resume Next
    if (Len (strIssuerDN) = 0) then 
        Call CloseObjects("00000103", "Empty Issuer DN", "00000000")
        Exit Sub 
    end if
    IVSCertPrefs.CertIssDN = strIssuerDN
    If ( err.number <> 0 ) then
      Call CloseObjects("00000103", "IVSCertPrefs.CertIssDN", Hex(err.number))
      Exit Sub
    End If

    On Error Resume Next
    if (Len (strCertSerial) = 0) then 
        Call CloseObjects("00000103", "Blank Serial Number", "00000000")
        Exit Sub 
    end if
    On Error Resume Next
    IVSCertPrefs.CertSerNum = strCertSerial
    If ( err.number <> 0 ) then
      Call CloseObjects(Hex(err.number), "Digital ID Install::IVSCertPrefs.CertISerNum", Hex(err.number))
      Exit Sub
    End If

    On Error Resume Next
    If (Len (strCertLogoUrl) <> 0) then 
       IVSCertPrefs.CertLogoUrl = strCertLogoUrl
       If ( err.number <> 0 ) then
          Call CloseObjects(Hex(err.number), "Digital ID Install::IVSCertPrefs.CertLogoUrl", Hex(err.number))
          Exit Sub
       End If
    End If 

    On Error Resume Next
    If (Len (strCertFriendlyName) <> 0) then 
       IVSCertPrefs.CertFrndlyName = strCertFriendlyName
       If ( err.number <> 0 ) then
            Call CloseObjects(Hex(err.number), "Digital ID Install::IVSCertPrefs.CertFrndlyName", Hex(err.number))
            Exit Sub
       End If   
    End If  
    
    On Error Resume Next
    If (Len (strCertTextureUrl) <> 0) then 
       IVSCertPrefs.CertTextureUrl = strCertTextureUrl
       If ( err.number <> 0 ) then
            Call CloseObjects(Hex(err.number), "Digital ID Install::IVSCertPrefs.CertTextureUrl", Hex(err.number))
            Exit Sub
       End If   
    End If  

    if ( "%%Enrollment/CertStore::policyValue%%" = "verisign" ) then 
       On Error Resume Next
       IVSProfMgmt.SaveProfile
       If ( err.number <> 0 ) then
            Call CloseObjects(Hex(err.number), "Digital ID Install::IVSProfMgmt.SaveProfile", Hex(err.number))
            Exit Sub
       End If   

       On Error Resume Next
       IVSProfMgmt.CloseProfile
       If ( err.number <> 0 ) then
            Call CloseObjects(Hex(err.number), "Digital ID Install::IVSProfMgmt.CloseProfile", Hex(err.number))
            Exit Sub
       End If   
    End If
    
    Call CloseObjects(0, "", 0)    
  End Sub
'-->
</Script>

<!-- VSSKBEGIN Apps/AddRoots#1 -->
<!-- VSSKEND Apps/AddRoots#1 -->
<!-- VSSKENDPOLICYVAL#yes#15 -->


<!-- VSSKBEGINPOLICYVAL#yes#16#1.0.0.4 -->
  ' the VBSCript variables made available on PTA renewal pages
  Dim strCertStore
  Dim strAppCtxtName
  Dim strAppLogoUrl
  Dim strAffiliateLogoUrl
  Dim strRenewWizardTitle
  Dim strRenewChooseTitle
  Dim strRenewChooseText
  Dim strRenewTitle
  Dim strRenewText
  Dim strIssuerDN
  Dim strIssuerDN2
  Dim saveLocal
  Dim strClientInfo
  Dim strClientInfoSig
  Dim strPtaHomeUrl
  Dim strRenewChooseHelpUrl
  Dim strRenewHelpUrl
  Dim AbtToExpWindow


  strCertStore = "%%Renewal/CertStore::policyValue%%"
  strAppCtxtName = "%%ptaAppName%%"
  strAppLogoUrl = "%%ptaAppLogoUrl%%"
  strAffiliateLogoUrl = "%%affiliateLogoURL%%"
  strRenewWizardTitle = "%%ptaRenewWizardTitle%%"
  strRenewChooseTitle = "%%ptaRenewChooseTitle%%"
  strRenewChooseText = "%%ptaRenewChooseText%%"
  strRenewTitle = "%%ptaRenewTitle%%"
  strRenewText = "%%ptaRenewText%%"
  strIssuerDN = "%%::ptaIssuerDN%%"
  strIssuerDN2 = "%%::ptaIssuerDN%%"
  saveLocal = "%%Apps/PTAv2/Roaming::saveLocal%%"
  strClientInfo = "%%Apps/PTAv2/Roaming::clientInfo%%"
  strClientInfoSig = "%%Apps/PTAv2/Roaming::clientInfoSig%%"
  strPtaHomeUrl = "%%ptaAppHomeUrl%%"
  AbtToExpWindow = %%::AbtToExpireWindow%%

  Dim TPMEnabled
  Dim boolTPMAvailable

  boolTPMAvailable = CBool(0)
  TPMEnabled = "%%ptaTPMOption%%"

 '-- VSSKBEGIN Global/Mode#35 --
 '-- VSSKEND Global/Mode#35 --

  strRenewChooseHelpUrl = helpHostName & "%%ptaRenewChooseHelpUrl%%"
  strRenewHelpUrl = helpHostName & "%%ptaRenewHelpUrl%%"
<!-- VSSKENDPOLICYVAL#yes#16 -->

<!-- VSSKBEGINPOLICYVAL#yes#17#1.0.0.3 -->

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
<!-- VSSKENDPOLICYVAL#yes#17 -->


<!-- VSSKBEGINPOLICYVAL#yes#18 -->
<Script Language="JavaScript">
<!--
   var PTAv2Enabled = 1;
//-->
</Script>
<!-- VSSKENDPOLICYVAL#yes#18 -->


// if both CSP and KeyProtect are policy auto-submit...
<!-- VSSKBEGINPOLICYVAL#yes#19 -->
  <!-- VSSKBEGIN Renewal/CSP#4 -->
  <!-- VSSKEND Renewal/CSP#4 -->
<!-- VSSKENDPOLICYVAL#yes#19 -->


<!-- VSSKBEGINPOLICYVAL#yes#20#1.2.0.8 -->
<Script Language="VBScript">
<!--
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
  
  Dim strCertStore 
  Dim strAppCtxtName
  Dim strIssuerDN
  Dim strCertSerial 
  Dim strCertLogoUrl
  Dim strCertFriendlyName
  Dim strCertTextureUrl
  Dim strChooseProfileText 
  Dim strChooseProfileTitle 
  Dim saveLocal 
  Dim strClientInfo
  Dim strClientInfoSig
  Dim strChooseHelpUrl 
  Dim strAffiliateLogoUrl

 '-- VSSKBEGIN Global/Mode#35 --
 '-- VSSKEND Global/Mode#35 --

  strChooseHelpUrl = helpHostName & "%%ptaLoginChooseHelpUrl%%"    
  strCertStore = "%%ptaCertStore%%"
  strAppCtxtName = "%%ptaAppName%%"
  strIssuerDN = "%%::ptaIssuerDN%%"
  strCertSerial = "$$cert_serial$$"
  strCertLogoUrl = "%%ptaCertLogoURL%%"
  strCertFriendlyName = "%%ptaCertFriendlyName%%"
  strCertTextureUrl = "%%ptaCertTextureURL%%"
  strChooseProfileTitle = "Open Profile"
  strChooseProfileText = "Choose the profile in which you want to install the Digital ID."
  saveLocal = "%%Apps/PTAv2/Roaming::saveLocal%%"
  strClientInfo = "%%Apps/PTAv2/Roaming::clientInfo%%"
  strClientInfoSig = "%%Apps/PTAv2/Roaming::clientInfoSig%%"
    
  strAppLogoUrl = "%%ptaAppLogoUrl%%"
  strAffiliateLogoUrl = "%%affiliateLogoURL%%"
  
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
  
  
  Sub SetPreferences
 	Dim TPMEnabled
	Dim boolTPMAvailable

	boolTPMAvailable = CBool(0)
	TPMEnabled = "%%ptaTPMOption%%"
	
	On Error Resume Next
	if(TPMEnabled = "CHECKED") then
		boolTPMAvailable = IVSPTA.IsTPMAvailable 
	End If
	if(TPMEnabled = "CHECKED" And boolTPMAvailable = "True") then
		if ("%%Enrollment/CertStore::policyValue%%" = "verisign") then
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
		End If

		' the certificate is installed one way or the other so set the preferences. 
		On Error Resume Next
		if (Len (strIssuerDN) = 0) then 
			Call CloseObjects("00000103", "Empty Issuer DN", "00000000")
			Exit Sub 
		end if
		IVSCertPrefs.CertIssDN = strIssuerDN
		If ( err.number <> 0 ) then
		  Call CloseObjects("00000103", "IVSCertPrefs.CertIssDN", Hex(err.number))
		  Exit Sub
		End If

		On Error Resume Next
		if (Len (strCertSerial) = 0) then 
			Call CloseObjects("00000103", "Blank Serial Number", "00000000")
			Exit Sub 
		end if
		On Error Resume Next
		IVSCertPrefs.CertSerNum = strCertSerial
		If ( err.number <> 0 ) then
		  Call CloseObjects(Hex(err.number), "Digital ID Install::IVSCertPrefs.CertISerNum", Hex(err.number))
		  Exit Sub
		End If

		On Error Resume Next
		If (Len (strCertLogoUrl) <> 0) then 
		   IVSCertPrefs.CertLogoUrl = strCertLogoUrl
		   If ( err.number <> 0 ) then
			  Call CloseObjects(Hex(err.number), "Digital ID Install::IVSCertPrefs.CertLogoUrl", Hex(err.number))
			  Exit Sub
		   End If
		End If 

		On Error Resume Next
		If (Len (strCertFriendlyName) <> 0) then 
		   IVSCertPrefs.CertFrndlyName = strCertFriendlyName
		   If ( err.number <> 0 ) then
				Call CloseObjects(Hex(err.number), "Digital ID Install::IVSCertPrefs.CertFrndlyName", Hex(err.number))
				Exit Sub
		   End If   
		End If  

		On Error Resume Next
		If (Len (strCertTextureUrl) <> 0) then 
		   IVSCertPrefs.CertTextureUrl = strCertTextureUrl
		   If ( err.number <> 0 ) then
				Call CloseObjects(Hex(err.number), "Digital ID Install::IVSCertPrefs.CertTextureUrl", Hex(err.number))
				Exit Sub
		   End If   
		End If  
	else
		if ("%%Renewal/CertStore::policyValue%%" = "verisign") then 
		   IVSPTA.Initialize strAppCtxtName,0
		else
		   IVSPTA.Initialize strAppCtxtName,1
		End If	
		If ( err.number <> 0 ) then
		  Call CloseObjects(Hex(err.number), "Digital ID Install::IVSPTA.Initialize", Hex(err.number))      
		  Exit Sub
		End If

		'MsgBox "PTA Initialized"
    
		if ( "%%Renewal/CertStore::policyValue%%" = "verisign" ) then 
			' set the open profile preferences and install the certificate 
			On Error Resume Next
			If (Len(strChooseProfileTitle) <> 0) then
			   IVSUIPrefs.OpenProf_Title = strChooseProfileTitle
			   If ( err.number <> 0 ) then
				  Call CloseObjects(Hex(err.number), "Digital ID Install::IVSUIPrefs.OpenProf_Title", Hex(err.number))
				  Exit Sub
			   End If
			End If

			On Error Resume Next
			If (Len(strChooseProfileText) <> 0) then
			   IVSUIPrefs.OpenProf_Text = strChooseProfileText
			   If ( err.number <> 0 ) then
				  Call CloseObjects(Hex(err.number), "Digital ID Install::IVSUIPrefs.OpenProf_Text", Hex(err.number))
				  Exit Sub
			   End If
			End If

		On Error Resume Next
		If (Len(strChooseHelpUrl) <> 0) then
			IVSUIPrefs.OpenProf_HelpUrl = strChooseHelpUrl
			If ( err.number <> 0 ) then
				Call CloseObjects(Hex(err.number), "Digital ID Install::IVSUIPrefs.OpenProf_HelpUrl", Hex(err.number))
				Exit Sub
			End If
		End If
			
			'Flags
			OPENPROF_OPEN_ONLY = CInt(529)
			On Error Resume Next
			IVSProfMgmt.OpenProfFlags = OPENPROF_OPEN_ONLY
			If ((err.number <> 0) And (Hex(err.number) <> "8000102F") ) Then
			   Call CloseObjects(Hex(err.number), "Digital ID Install::IVSProfMgmt.OpenProfFlags", Hex(err.number))
			   Exit Sub
			End If

				   On Error Resume Next
				   If (Len(strAppLogoUrl) <> 0) then
      				  IVSUIPrefs.UILogoUrl = strAppLogoUrl
					  If ( err.number <> 0 ) then
						Call CloseObjects(Hex(err.number), "Digital ID Install::IVSUIPrefs.LogoUrl", Hex(err.number))
				Exit Sub
					  End If
			   End If

			On Error Resume Next
			If (Len(strAffiliateLogoUrl) <> 0 And strAffiliateLogoUrl <> "VeriSign") then
      			 IVSPTA.AffLogoUrl = strAffiliateLogoUrl
				 If ( err.number <> 0 And err.number <> &h800010c4 ) then
					   Call CloseObjects(Hex(err.number), "Digital ID Install::IVSPTA.AffLogoUrl", Hex(err.number))
					   Exit Sub
				 End If
			End If

			'-- VSSKBEGIN Apps/PTAv2/Roaming#3 --
			'-- VSSKEND Apps/PTAv2/Roaming#3 --
			
			'open the profile 
			'On Error Resume Next
			'IVSProfMgmt.OpenProfile
			'if (Hex(err.number) = "80001067") Then
			'    Call CloseObjects(Hex(err.number), "Digital ID Install::IVSProfMgmt.OpenProfile", Hex(err.number))
			'    Exit Sub
			'End if
		'if ( (err.number <> 0) And (Hex(err.number) <> "8000102F") ) then
			'      Call CloseObjects(Hex(err.number), "Digital ID Install::IVSProfMgmt.OpenProfile", Hex(err.number))
			'      Exit Sub
			'End If 
			
		   ' at this instance the profile is open one way or the other
		   ' so install the certificate
		   On Error Resume Next
		   IVSPTA.InstallCert CertChain
		   if (err.number <> 0) then
				Call CloseObjects(Hex(err.number), "Digital ID Install::IVSPTA.InstallCert", Hex(err.number))
				Exit Sub
		   end if 
		end if
    End If


    Dim OrigIssDN
    Dim OrigSerNum
    Dim NewSerNum

    'OrigIssDN = "$$orig_cert_issuerdn$$"
    OrigIssDN = strIssuerDN
    OrigSerNum = "$$orig_cert_serial$$"
    NewSerNum = "$$cert_serial$$"

    ' the certificate is installed one way or the other so set the preferences. 
    On Error Resume Next
    if (Len (OrigIssDN) = 0) then 
        Call CloseObjects("00000103", "Digital ID Install::Empty Issuer DN", "00000000")
        Exit Sub 
    end if

    if (Len (NewSerNum) = 0) then 
        Call CloseObjects("00000103", "Digital ID Install::Blank Serial Number", "00000000")
        Exit Sub 
    end if

    if (Len (OrigSerNum) = 0) then 
        Call CloseObjects("00000103", "Digital ID Install::Blank Original Serial Number", "00000000")
        Exit Sub 
    end if

    ' the certificate is installed one way or the other so set the preferences. 
    On Error Resume Next
    IVSCertPrefs.CertIssDN = OrigIssDN
    If ( err.number <> 0 ) then
      Call CloseObjects(Hex(err.number), "Digital ID Install::IVSCertPrefs.CertIssDN", Hex(err.number))
      Exit Sub
    End If

    On Error Resume Next
    IVSCertPrefs.CertSerNum = OrigSerNum
    If ( err.number <> 0 ) then
      Call CloseObjects(Hex(err.number), "Digital ID Install::IVSCertPrefs.CertSerNum", Hex(err.number))
      Exit Sub
    End If

    On Error Resume Next
    IVSCertPrefs.MarkAsRenewed = TRUE
    If ( err.number <> 0 ) then
      Call CloseObjects(Hex(err.number), "Digital ID Install::IVSCertPrefs.MarkAsRenewed", Hex(err.number))
      Exit Sub
    End If

    On Error Resume Next
    IVSCertPrefs.CertSerNum = NewSerNum
    If ( err.number <> 0 ) then
      Call CloseObjects(Hex(err.number), "Digital ID Install::IVSCertPrefs.CertISerNum", Hex(err.number))
      Exit Sub
    End If


    On Error Resume Next
    If (Len (strCertLogoUrl) <> 0) then 
       IVSCertPrefs.CertLogoUrl = strCertLogoUrl
       If ( err.number <> 0 ) then
          Call CloseObjects(Hex(err.number), "Digital ID Install::IVSCertPrefs.CertLogoUrl", Hex(err.number))
          Exit Sub
       End If
    End If 

    On Error Resume Next
    If (Len (strCertFriendlyName) <> 0) then 
       IVSCertPrefs.CertFrndlyName = strCertFriendlyName
       If ( err.number <> 0 ) then
            Call CloseObjects(Hex(err.number), "Digital ID Install::IVSCertPrefs.CertFrndlyName", Hex(err.number))
            Exit Sub
       End If   
    End If  
    
    On Error Resume Next
    If (Len (strCertTextureUrl) <> 0) then 
       IVSCertPrefs.CertTextureUrl = strCertTextureUrl
       If ( err.number <> 0 ) then
            Call CloseObjects(Hex(err.number), "Digital ID Install::IVSCertPrefs.CertTextureUrl", Hex(err.number))
            Exit Sub
       End If   
    End If  

    if ( "%%Enrollment/CertStore::policyValue%%" = "verisign" And boolTPMAvailable <> "True" ) then 
       On Error Resume Next
       IVSProfMgmt.SaveProfile
       If ( err.number <> 0 ) then
            Call CloseObjects(Hex(err.number), "Digital ID Install::IVSProfMgmt.SaveProfile", Hex(err.number))
            Exit Sub
       End If   

       On Error Resume Next
       IVSProfMgmt.CloseProfile
       If ( err.number <> 0 ) then
            Call CloseObjects(Hex(err.number), "Digital ID Install::IVSProfMgmt.CloseProfile", Hex(err.number))
            Exit Sub
       End If   
    End If
    
    Call CloseObjects(0, "", 0)    
  End Sub
'-->
</Script>

<!-- VSSKBEGIN Apps/AddRoots#1 -->
<!-- VSSKEND Apps/AddRoots#1 -->
<!-- VSSKENDPOLICYVAL#yes#20 -->


<!-- VSSKBEGINPOLICYVAL#yes#21#1.0.0.2 -->
  var strCertStore = "%%Renewal/CertStore::policyValue%%";
  var strAppCtxtName = "%%ptaAppName%%";
  var strAppLogoUrl = "%%ptaAppLogoUrl%%";
  var strAffiliateLogoUrl = "%%affiliateLogoURL%%";
  var strRenewWizardTitle = "%%ptaRenewWizardTitle%%";
  var strRenewChooseTitle = "%%ptaRenewChooseTitle%%";
  var strRenewChooseText = "%%ptaRenewChooseText%%";
  var strRenewTitle = "%%ptaRenewTitle%%";
  var strRenewText = "%%ptaRenewText%%";
  var strIssuerDN = "%%::ptaIssuerDN%%";
  var saveLocal = "%%Apps/PTAv2/Roaming::saveLocal%%";
  var strClientInfo = "%%Apps/PTAv2/Roaming::clientInfo%%";
  var strClientInfoSig = "%%Apps/PTAv2/Roaming::clientInfoSig%%";
  var strPtaHomeUrl = "%%ptaAppHomeUrl%%";

  var AbtToExpWindow = %%::AbtToExpireWindow%%;
 //-- VSSKBEGIN Global/Mode#36 --
 //-- VSSKEND Global/Mode#36 --

  var strRenewChooseHelpUrl = helpHostName + "%%ptaRenewChooseHelpUrl%%";
  var strRenewHelpUrl = helpHostName + "%%ptaRenewHelpUrl%%";
<!-- VSSKENDPOLICYVAL#yes#21 -->

<!-- VSSKBEGINPOLICYVAL#yes#22#1.0.0.3 -->
  Dim strCertStore 
  Dim strAppCtxtName
  Dim strIssuerDN
  Dim strChooseProfileText 
  Dim strChooseProfileTitle 
  Dim strChangepwdWizardTitle
  Dim strChangepwdTitle
  Dim strChangepwdText
  Dim strChangepwdHelpUrl
  Dim passwordQuality
  Dim passwordLength
  Dim saveLocal
  Dim strClientInfo
  Dim strClientInfoSig
  Dim strAppLogoUrl
  Dim strAffiliateLogoUrl
  Dim TPMEnabled


  TPMEnabled = "%%ptaTPMOption%%"
  strCertStore = "%%Enrollment/CertStore::policyValue%%"
  strAppCtxtName = "%%ptaAppName%%"
  strIssuerDN = "%%::ptaIssuerDN%%"
  strChooseProfileTitle = "Open Profile"
  strChooseProfileText = "Choose the profile whose password is to be changed."
  strChangepwdWizardTitle = "Change Password"
  strChangepwdTitle = "Change your profile password"
  strChangepwdText = "Enter your new password to change your profile password."  
  passwordQuality = "%%ptaPasswordQuality%%"
  passwordLength = "%%ptaPasswordLength%%"
  saveLocal = "%%Apps/PTAv2/Roaming::saveLocal%%"
  strClientInfo = "%%Apps/PTAv2/Roaming::clientInfo%%"
  strClientInfoSig = "%%Apps/PTAv2/Roaming::clientInfoSig%%"
  strAppLogoUrl = "%%ptaAppLogoUrl%%"
  strAffiliateLogoUrl = "%%affiliateLogoURL%%"

  '-- VSSKBEGIN Global/Mode#35 --
  '-- VSSKEND Global/Mode#35 --

  strChangepwdHelpUrl = helpHostName & "/VSApps/client/help/tasks/ptachangepwd.htm"
<!-- VSSKENDPOLICYVAL#yes#22 -->


<!-- VSSKBEGINPOLICYVAL#yes#23#1.0.0.2 -->
      var strCertStore = "%%Enrollment/CertStore::policyValue%%";
      var strAppCtxtName = "%%ptaAppName%%";
      var strIssuerDN = "%%::ptaIssuerDN%%";
      var strChooseProfileTitle = "Open Profile";
      var strChooseProfileText = "Choose the profile whose password is to be changed.";
      var strChangepwdWizardTitle = "Change Password";
      var strChangepwdTitle = "Change your profile password";
      var strChangepwdText = "Enter your new password to change your profile password."  ;
      var passwordQuality = "%%ptaPasswordQuality%%";
      var passwordLength = "%%ptaPasswordLength%%";
      var saveLocal = "%%Apps/PTAv2/Roaming::saveLocal%%";
      var strClientInfo = "%%Apps/PTAv2/Roaming::clientInfo%%";
      var strClientInfoSig = "%%Apps/PTAv2/Roaming::clientInfoSig%%";
      var strAppLogoUrl = "%%ptaAppLogoUrl%%";
	  var strAffiliateLogoUrl = "%%affiliateLogoURL%%";

      //-- VSSKBEGIN Global/Mode#36 --
      //-- VSSKEND Global/Mode#36 --

      var strChangepwdHelpUrl = helpHostName + "/VSApps/client/help/tasks/ptachangepwd.htm";
<!-- VSSKENDPOLICYVAL#yes#23 -->

<!-- VSSKBEGINPOLICYVAL#yes#24 -->
<BR>
<TABLE WIDTH=588 CELLPADDING=2 CELLSPACING=0 BORDER=0>
<TR>
    <TD><IMG SRC="../../VSApps/graphics/space.gif" border="0" WIDTH=432 HEIGHT=1 HSPACE=0 VSPACE=0></TD>

    <TD><A HREF="%%ptaAppHomeUrl%%"><IMG SRC="../../VSApps/graphics/button_continue.gif" border="0" WIDTH=121 HEIGHT=39 BORDER=0 ALT="Continue"></A></TD>
</TR>
</TABLE>
<!-- VSSKENDPOLICYVAL#yes#24 -->

<!-- VSSKBEGINPOLICYVAL#yes#25 -->
  Dim strCertLogoUrl
  Dim strCertFriendlyName
  Dim strCertTextureUrl
  
  strCertLogoUrl = "%%ptaCertLogoURL%%"
  strCertFriendlyName = "%%ptaCertFriendlyName%%"
  strCertTextureUrl = "%%ptaCertTextureURL%%"
<!-- VSSKENDPOLICYVAL#yes#25 -->

<!-- VSSKBEGINPOLICYVAL#yes#26 -->
  var strCertLogoUrl = "%%ptaCertLogoURL%%";
  var strCertFriendlyName = "%%ptaCertFriendlyName%%";
  var strCertTextureUrl = "%%ptaCertTextureURL%%";
<!-- VSSKENDPOLICYVAL#yes#26 -->

<!-- VSSKBEGINPOLICYVAL#yes#27 -->
<Script Language="VBScript">
<!--
  Dim IVSWin2KSelectedID

  On Error Resume Next
  Set IVSWin2KSelectedID = IVSPTA.IVSSelectedDigID
  If (Hex(err.number) = "1B6") Then
      Call CloseObjects(Hex(err.number), "Renewal", Hex(err.number))
  End if
'-->
</Script>
<!-- VSSKENDPOLICYVAL#yes#27 -->

<!-- VSSKBEGINPOLICYVAL#yes#28 -->
<Script Language="VBScript">
<!--
  Dim IVSWin2KSelectedID

  On Error Resume Next
  Set IVSWin2KSelectedID = IVSPTA.IVSSelectedDigID
  If (Hex(err.number) = "1B6") Then
      window.location = "../error/win2k.htm"
  End if
'-->
</Script>
<!-- VSSKENDPOLICYVAL#yes#28 -->

<!-- VSSKBEGINPOLICYVAL#yes#29 -->
<Script Language="JavaScript">
<!--
  if ( "%%clientMode%%" != "pts" && "%%Apps/PTAv2/GSWAClientType::policyValue%%" != "Java")
  {
   document.write("<TR>");
   document.write("<TD WIDTH=50 ALIGN=left VALIGN=top>");
   document.write("<A HREF=\"win2kCenter.htm\"><IMG SRC=\"graphics/action_arrowyellow.gif\" border=0 WIDTH=40 HEIGHT=40 ALIGN=LEFT></A>");
   document.write("</TD>");
   document.write("<TD WIDTH=538 ALIGN=left VALIGN=top>");
   document.write("<A HREF=\"win2kCenter.htm\"><FONT FACE=\"verdana, arial, helvetica\" SIZE=4><B>Windows 2000  Resource Center</FONT><FONT SIZE=3> (For Administrators Only)</FONT></B></A><BR>");
   document.write("<FONT FACE=\"arial, helvetica\" SIZE=2>This page will give you information about how to enable your");
   document.write(" non-power users on Windows 2000 machines.");
   document.write("</FONT>");
   document.write("<P>");
   document.write("</TD>");
   document.write("</TR>");
  }
//-->
</Script>
<!-- VSSKENDPOLICYVAL#yes#29 -->

<!-- VSSKBEGINPOLICYVAL#yes#30 -->
<BR>
<TABLE WIDTH=588 CELLPADDING=2 CELLSPACING=0 BORDER=0>
<TR>
    <TD><IMG SRC="../graphics/space.gif" border="0" WIDTH=432 HEIGHT=1 HSPACE=0 VSPACE=0></TD>

    <TD><A HREF="%%ptaAppHomeUrl%%"><IMG SRC="../graphics/button_continue.gif" border="0" WIDTH=121 HEIGHT=39 BORDER=0 ALT="Continue"></A></TD>
</TR>
</TABLE>
<!-- VSSKENDPOLICYVAL#yes#30 -->

<!-- VSSKBEGINPOLICYVAL#yes#31#1.0.0.2 -->
  Dim strCertStore 
  Dim strAppCtxtName
  Dim strIssuerDN
  Dim strQuestion 
  Dim strResetpwdWizardTitle
  Dim passwordQuality
  Dim passwordLength
  Dim strClientInfo
  Dim strClientInfoSig
  Dim strAppLogoUrl
  Dim strAffiliateLogoUrl

  strCertStore = "%%Enrollment/CertStore::policyValue%%"
  strAppCtxtName = "%%ptaAppName%%"
  strIssuerDN = "%%::ptaIssuerDN%%"
  strClientInfo = "%%Apps/PTAv2/Roaming::clientInfo%%"
  strClientInfoSig = "%%Apps/PTAv2/Roaming::clientInfoSig%%"
  strResetpwdWizardTitle = "Reset Password"
  passwordQuality = "%%ptaPasswordQuality%%"
  passwordLength = "%%ptaPasswordLength%%"
  strAppLogoUrl = "%%ptaAppLogoUrl%%"
  strAffiliateLogoUrl = "%%affiliateLogoURL%%"

<!-- VSSKENDPOLICYVAL#yes#31 -->

<!-- VSSKBEGINPOLICYVAL#yes#32 -->
      var strCertStore = "%%Enrollment/CertStore::policyValue%%";
      var strAppCtxtName = "%%ptaAppName%%";
      var strIssuerDN = "%%::ptaIssuerDN%%";
      var strResetpwdWizardTitle = "Reset Password";
      var passwordQuality = "%%ptaPasswordQuality%%";
      var passwordLength = "%%ptaPasswordLength%%";
      var strClientInfo = "%%Apps/PTAv2/Roaming::clientInfo%%";
      var strClientInfoSig = "%%Apps/PTAv2/Roaming::clientInfoSig%%";
      var strAppLogoUrl = "%%ptaAppLogoUrl%%";
      var strAffiliateLogoUrl = "%%affiliateLogoURL%%";

      //-- VSSKBEGIN Global/Mode#36 --
      //-- VSSKEND Global/Mode#36 --

<!-- VSSKENDPOLICYVAL#yes#32 -->

// if both CSP and KeyProtect are policy then don't disable accept button as it gives script error...
<!-- VSSKBEGINPOLICYVAL#yes#33 -->
  <!-- VSSKBEGIN Renewal/CSP#8 -->
  <!-- VSSKEND Renewal/CSP#8 -->
<!-- VSSKENDPOLICYVAL#yes#33 -->

<!-- VSSKBEGINPOLICYVAL#yes#34 -->
On Error Resume Next
IVSPTA.UTF8EncodeMessage = CBool(1)
If ( err.number <> 0 ) then
    Call CloseObjects(Hex(err.number), "Transaction Signing::IVSPTA.UTF8EncodeMessage", Hex(err.number))
    Exit Sub
End If
<!-- VSSKENDPOLICYVAL#yes#34 -->
