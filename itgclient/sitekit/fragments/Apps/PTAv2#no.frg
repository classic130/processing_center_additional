
<!-- VSSKBEGINPOLICYVAL#no#1 -->
<!-- VSSKENDPOLICYVAL#no#1 -->

<!-- VSSKBEGINPOLICYVAL#no#2 -->
<!-- VSSKENDPOLICYVAL#no#2 -->

<!-- VSSKBEGINPOLICYVAL#no#3 -->
<!-- VSSKENDPOLICYVAL#no#3 -->

<!-- VSSKBEGINPOLICYVAL#no#4 -->
	self.location = "%%ptaAppHomeUrl%%";
<!-- VSSKENDPOLICYVAL#no#4 -->

<!-- VSSKBEGINPOLICYVAL#no#5 -->
<!-- VSSKENDPOLICYVAL#no#5 -->

<!-- VSSKBEGINPOLICYVAL#no#6 -->
<!-- VSSKENDPOLICYVAL#no#6 -->

<!-- VSSKBEGINPOLICYVAL#no#7 -->
<!-- VSSKENDPOLICYVAL#no#7 -->

<!-- VSSKBEGINPOLICYVAL#no#8 -->
<!-- VSSKENDPOLICYVAL#no#8 -->

<!-- VSSKBEGINPOLICYVAL#no#9 -->
<!-- VSSKENDPOLICYVAL#no#9 -->

<!-- VSSKBEGINPOLICYVAL#no#10 -->
<!-- VSSKENDPOLICYVAL#no#10 -->


<!-- VSSKBEGINPOLICYVAL#no#11 -->
<!-- VSSKENDPOLICYVAL#no#11 -->

<!-- VSSKBEGINPOLICYVAL#no#12 -->
<!-- VSSKENDPOLICYVAL#no#12 -->

<!-- VSSKBEGINPOLICYVAL#no#13 -->
var strCertStore = "%%ptaCertStore%%";
var strAppCtxtName = "%%ptaAppName%%";
var strIssuserDN = "%%::ptaIssuerDN%%";
var strCertLogoUrl = "%%ptaCertLogoURL%%";
var strCertFriendlyName = "%%ptaCertFriendlyName%%";
var strCertTextureUrl = "%%ptaCertTextureURL%%";
var PTAHome = "%%ptaAppHomeUrl%%";
var ptaEnabled = 0;
var enrollStore = "%%Enrollment/CertStore::policyValue%%";
var kmProvider = "%%Apps/KeyManager::provName%%";
<!-- VSSKENDPOLICYVAL#no#13 -->

<!-- VSSKBEGINPOLICYVAL#no#14 -->
<!-- VSSKENDPOLICYVAL#no#14 -->

<!-- VSSKBEGINPOLICYVAL#no#15 -->
<!-- VSSKENDPOLICYVAL#no#15 -->

<!-- VSSKBEGINPOLICYVAL#no#16 -->
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
  Dim strRoaming
  Dim strPtaHomeUrl
  Dim strRenewChooseHelpUrl 
  Dim strRenewHelpUrl
  Dim  AbtToExpWindow

  strCertStore = "%%Renewal/CertStore::policyValue%%"
  strAppCtxtName = ""
  strAppLogoUrl = ""
  strAffiliateLogoUrl = "%%affiliateLogoURL%%"
  strRenewWizardTitle = "Digital ID Renewal"
  strRenewChooseTitle = "Choose Profile"
  strRenewChooseText = ""
  strRenewTitle = "Choose Digital ID"
  strRenewText = "Choose the Digital ID that you wish to Renew and click the Renew button"
  strIssuerDN = "%%::ptaIssuerDN%%"
  strIssuerDN2 = "%%::ptaIssuerDN%%"
  strRoaming="disabled"
  strPtaHomeUrl = "../digitalidCenter.htm"
  AbtToExpWindow = %%::AbtToExpireWindow%%

 '-- VSSKBEGIN Global/Mode#35 --
 '-- VSSKEND Global/Mode#35 --

  strRenewChooseHelpUrl = helpHostName & "%%ptaRenewChooseHelpUrl%%"
  strRenewHelpUrl = helpHostName & "%%ptaRenewHelpUrl%%"
<!-- VSSKENDPOLICYVAL#no#16 -->

<!-- VSSKBEGINPOLICYVAL#no#17 -->
<!-- VSSKENDPOLICYVAL#no#17 -->

<!-- VSSKBEGINPOLICYVAL#no#18 -->
<Script Language="JavaScript">
<!--
   var PTAv2Enabled = 0;
//-->
</Script>
<!-- VSSKENDPOLICYVAL#no#18 -->

<!-- VSSKBEGINPOLICYVAL#no#19 -->
<!-- VSSKENDPOLICYVAL#no#19 -->

<!-- VSSKBEGINPOLICYVAL#no#20 -->
<!-- VSSKENDPOLICYVAL#no#20 -->


<!-- VSSKBEGINPOLICYVAL#no#21 -->
  var strCertStore = "%%Renewal/CertStore::policyValue%%";
  var strAppCtxtName = "";
  var strAppLogoUrl = "";
  var strAffiliateLogoUrl = "%%affiliateLogoURL%%";
  var strRenewWizardTitle = "Digital ID Renewal";
  var strRenewChooseTitle = "Choose Profile";
  var strRenewChooseText = "";
  var strRenewTitle = "Choose Digital ID";
  var strRenewText = "Choose the Digital ID that you wish to Renew and click the Renew button";
  var strIssuerDN = "%%::ptaIssuerDN%%";
  var strRoaming="disabled";
  var strPtaHomeUrl = "../digitalidCenter.htm";
  var AbtToExpWindow = %%::AbtToExpireWindow%%;
 //-- VSSKBEGIN Global/Mode#36 --
 //-- VSSKEND Global/Mode#36 --

  var strRenewChooseHelpUrl = helpHostName + "%%ptaRenewChooseHelpUrl%%";
  var strRenewHelpUrl = helpHostName + "%%ptaRenewHelpUrl%%";
<!-- VSSKENDPOLICYVAL#no#21 -->


<!-- VSSKBEGINPOLICYVAL#no#22 -->
 Dim strCertStore 
 
 strCertStore = "%%Enrollment/CertStore::policyValue%%"
<!-- VSSKENDPOLICYVAL#no#22 -->

<!-- VSSKBEGINPOLICYVAL#no#23 -->
 var strCertStore = "%%Enrollment/CertStore::policyValue%%";
<!-- VSSKENDPOLICYVAL#no#23 -->

<!-- VSSKBEGINPOLICYVAL#no#24 -->
<!-- VSSKENDPOLICYVAL#no#24 -->


<!-- VSSKBEGINPOLICYVAL#yes#25 -->
  Dim strCertLogoUrl
  Dim strCertFriendlyName
  Dim strCertTextureUrl
  
  strCertLogoUrl = ""
  strCertFriendlyName = ""
  strCertTextureUrl = ""
<!-- VSSKENDPOLICYVAL#yes#25 -->

<!-- VSSKBEGINPOLICYVAL#yes#26 -->
  var strCertLogoUrl = "";
  var strCertFriendlyName = "";
  var strCertTextureUrl = "";
<!-- VSSKENDPOLICYVAL#yes#26 -->

<!-- VSSKBEGINPOLICYVAL#no#27 -->
<!-- VSSKENDPOLICYVAL#no#27 -->

<!-- VSSKBEGINPOLICYVAL#no#28 -->
<!-- VSSKENDPOLICYVAL#no#28 -->

<!-- VSSKBEGINPOLICYVAL#no#29 -->
<!-- VSSKENDPOLICYVAL#no#29 -->

<!-- VSSKBEGINPOLICYVAL#no#30 -->
<!-- VSSKENDPOLICYVAL#no#30 -->

<!-- VSSKBEGINPOLICYVAL#no#31 -->
 Dim strCertStore 
 
 strCertStore = "%%Enrollment/CertStore::policyValue%%"
<!-- VSSKENDPOLICYVAL#no#31 -->

<!-- VSSKBEGINPOLICYVAL#no#32 -->
 var strCertStore = "%%Enrollment/CertStore::policyValue%%";
<!-- VSSKENDPOLICYVAL#no#32 -->

<!-- VSSKBEGINPOLICYVAL#no#33 -->
      document.theform.Accept.disabled = true
<!-- VSSKENDPOLICYVAL#no#33 -->

<!-- VSSKBEGINPOLICYVAL#no#34 -->
<!-- VSSKENDPOLICYVAL#no#34 -->
