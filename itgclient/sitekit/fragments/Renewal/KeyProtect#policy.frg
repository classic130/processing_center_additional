<!-- VSSKBEGINPOLICYVAL#policy#1 -->
<!-- VSSKENDPOLICYVAL#policy#1 -->


<!-- VSSKBEGINPOLICYVAL#policy#2 -->
       if %%bProtect%% then
           keyflags = keyflags OR 2
       end if 
<!-- VSSKENDPOLICYVAL#policy#2 -->


<!-- VSSKBEGINPOLICYVAL#policy#3 -->
<Script Language="VBScript">
<!--
   Call CheckIfVista
   Call renewclick
'-->
</script>
<!-- VSSKENDPOLICYVAL#policy#3 -->


<!-- VSSKBEGINPOLICYVAL#policy#4 -->       
if (%%bProtect%%)
{
      KeyFlags = KeyFlags | 2;
}
<!-- VSSKENDPOLICYVAL#policy#4 -->


<!-- VSSKBEGINPOLICYVAL#policy#5#1.2.0.4 -->
<Script Language="JavaScript">
<!--
   window.setTimeout("renewclick()", 1000);
   //document.Renewal.submit();
//-->
</script>
<!-- VSSKENDPOLICYVAL#policy#5 -->

<!-- VSSKBEGINPOLICYVAL#policy#6 -->
<!-- VSSKENDPOLICYVAL#policy#6 -->
