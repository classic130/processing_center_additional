
<!-- VSSKBEGINPOLICYVAL#standard#1 -->
<SCRIPT LANGUAGE="VBScript">
<!--
  Sub CreateStandardTrustProfile
      ObjectIAddRootCerts.Initialize
      ObjectIAddRootCerts.CreateStandardTrustProfile
  End Sub
'-->
</SCRIPT>
<!-- VSSKENDPOLICYVAL#standard#1 -->

<!-- VSSKBEGINPOLICYVAL#standard#2 -->
<SCRIPT LANGUAGE="VBScript">
<!--
  Call CreateStandardTrustProfile
'-->
</SCRIPT>
<!-- VSSKENDPOLICYVAL#standard#2 -->


<!-- VSSKBEGINPOLICYVAL#standard#3 -->
<Script Language="JavaScript">
<!--
  function CreateStandardTrustProfileJava()
  {
       document.NSCP_IVSPTA.AddRootCerts_Initialize();
       document.NSCP_IVSPTA.AddRootCerts_CreateStandardTrustProfile();
       return;
  }
//-->
</Script>
<!-- VSSKENDPOLICYVAL#standard#3 -->


<!-- VSSKBEGINPOLICYVAL#standard#4#1.2.0.4 -->
  CreateStandardTrustProfileJava();
<!-- VSSKENDPOLICYVAL#standard#4 -->


<!-- VSSKBEGINPOLICYVAL#standard#5 -->
<!-- VSSKBEGIN Global/Mode#33 -->
<!-- VSSKEND Global/Mode#33 -->
<!-- VSSKENDPOLICYVAL#standard#5 -->
