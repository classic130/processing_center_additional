<!-- VSSKBEGINPOLICYVAL#user#1 -->
<script language="JavaScript">
if (browserNum >= 4) 
{ 
document.write("<!--BEGIN TABLE FIVE-->");
document.write("<TABLE WIDTH=588 BGCOLOR='ffffcc' CELLPADDING=7 CELLSPACING=0 BORDER=0>");
document.write("<TR>");
document.write("<TD WIDTH=588>");
document.write("<FONT SIZE=2 FACE='verdana, arial, helvetica'><B>Additional Security for Your Private Key</B> </FONT><Br>");
document.write(" <font face='arial, helvetica' size=2>We recommend that you protect the private key associated with your digital ID.");
document.write(" Checking the box below will provide you with security options for your private key.");
document.write("<label id=try onClick=dumbfunc()><FONT COLOR=#FF0000> Click Here</FONT></LABEL>");
document.write(" for additional information.<BR></FONT>");
document.write(" <P><CENTER>");
document.write("<!--BEGIN INPUT FIELD TABLE-->");
document.write("<TABLE WIDTH=574 CELLPADDING=3 CELLSPACING=2 BORDER=0>");
document.write("<TR>");
document.write("<TD WIDTH=50% BGCOLOR='ffcc00'><font face='verdana, arial, helvetica' size=2><B>Check this Box to Protect Your <BR>Private Key</B></FONT></TD>");
document.write("<TD COLSPAN=2 WIDTH=50% BGCOLOR='ffcc00'><IMG SRC='../../VSApps/graphics/blank2.gif' WIDTH=27 HEIGHT=27'>");
if (%%bProtect%%)
   {
       document.write("<INPUT TYPE='checkbox' NAME='userprotect' CHECKED></TD>");            
   }
else
   {
       document.write("<INPUT TYPE='checkbox' NAME='userprotect'></TD>");      
   }
document.write("</TR>");
document.write("</TABLE>");
document.write("<!--END INPUT FIELD TABLE-->");
document.write("</TD>");
document.write("</TR>");
document.write("</TABLE>");
document.write("<!--END TABLE FIVE-->");
document.write("<P><BR><P>");
} 
</script>
<!-- VSSKENDPOLICYVAL#user#1 -->



<!-- VSSKBEGINPOLICYVAL#user#2 -->
       if theForm.userprotect.checked = true then
          keyflags = keyflags OR 2
       end if
<!-- VSSKENDPOLICYVAL#user#2 -->


<!-- VSSKBEGINPOLICYVAL#user#3 -->
<!-- VSSKENDPOLICYVAL#user#3 -->


<!-- VSSKBEGINPOLICYVAL#user#4 -->       
if (document.Renewal.userprotect.checked) 
{ 
  KeyFlags = KeyFlags | 2;
} 
<!-- VSSKENDPOLICYVAL#user#4 -->


<!-- VSSKBEGINPOLICYVAL#user#5 -->
<!-- VSSKENDPOLICYVAL#user#5 -->

<!-- VSSKBEGINPOLICYVAL#user#6 -->
      document.theform.Accept.disabled = true
<!-- VSSKENDPOLICYVAL#user#6 -->

