<!-- VSSKBEGINPOLICYVAL#user#1 -->
<script language="JavaScript">;
if (browserNum >= 4) 
{ 
document.writeln("<!--BEGIN TABLE FIVE-->");
document.writeln("<TABLE WIDTH=588 BGCOLOR='ffffcc' CELLPADDING=7 CELLSPACING=0 BORDER=0>");
document.writeln("<TR>");
document.writeln("<TD WIDTH=588>");
document.writeln("<FONT SIZE=2 FACE='verdana, arial, helvetica'><B>Additional Security for Your Private Key</B> </FONT><Br>");
document.writeln(" <font face='arial, helvetica' size=2>We recommend that you protect the private key associated with your digital ID.");
document.writeln(" Checking the box below will provide you with security options for your private key.");
document.writeln("<label id=try onClick=dumbfunc()><FONT COLOR=#FF0000> Click Here</FONT></LABEL>");
document.writeln(" for additional information.<BR></FONT>");
document.writeln(" <P><CENTER>");
document.writeln("<!--BEGIN INPUT FIELD TABLE-->");
document.writeln("<TABLE WIDTH=574 CELLPADDING=3 CELLSPACING=2 BORDER=0>");
document.writeln("<TR>");
document.writeln("<TD WIDTH=50% BGCOLOR='ffcc00'><font face='verdana, arial, helvetica' size=2><B>Check this Box to Protect Your <BR>Private Key</B></FONT></TD>");
document.writeln("<TD COLSPAN=2 WIDTH=50% BGCOLOR='ffcc00'><IMG SRC='../graphics/blank2.gif' WIDTH=27 HEIGHT=27'>");
if (%%bProtect%%)
   {
       document.writeln("<INPUT TYPE='checkbox' NAME='userprotect' CHECKED></TD>");            
   }
else
   {
       document.writeln("<INPUT TYPE='checkbox' NAME='userprotect'></TD>");      
   }
document.writeln("</TR>");
document.writeln("</TABLE>");
document.writeln("<!--END INPUT FIELD TABLE-->");
document.writeln("</TD>");
document.writeln("</TR>");
document.writeln("</TABLE>");
document.writeln("<!--END TABLE FIVE-->");
document.writeln("<P><BR><P>");
} 
</script>
<!-- VSSKENDPOLICYVAL#user#1 -->



<!-- VSSKBEGINPOLICYVAL#user#2 -->
       if theForm.userprotect.checked = true then
          keyflags = keyflags OR 2
       end if
<!-- VSSKENDPOLICYVAL#user#2 -->


<!-- VSSKBEGINPOLICYVAL#user#3 -->       
if (document.proform.userprotect.checked) 
{ 
  KeyFlags = KeyFlags | 2;
} 
<!-- VSSKENDPOLICYVAL#user#3 -->



<!-- VSSKBEGINPOLICYVAL#user#4 -->
    if "$$userprotect$$" = "on" then
       	Import.KeyUserProtected = true
    else
	Import.KeyUserProtected = false
    end if
<!-- VSSKENDPOLICYVAL#user#4 -->


// for enroll_wait.htm
<!-- VSSKBEGINPOLICYVAL#user#5 -->
<input TYPE=hidden NAME=userprotect VALUE="$$userprotect$$">
<!-- VSSKENDPOLICYVAL#user#5 -->


// for userEnrollDualMS.fdf
<!-- VSSKBEGINPOLICYVAL#user#6 -->
userprotect	TEXT	OPTIONAL	NONE	NONE
<!-- VSSKENDPOLICYVAL#user#6 -->

// for userGetEncMS.htm
<!-- VSSKBEGINPOLICYVAL#user#7 -->
<script language="JavaScript">;
if (browserNum >= 4) 
{ 
document.writeln("<!--BEGIN TABLE FIVE-->");
document.writeln("<TABLE WIDTH=556 BGCOLOR='ffffcc' CELLPADDING=7 CELLSPACING=0 BORDER=0>");
document.writeln("<TR>");
document.writeln("<TD WIDTH=556>");
document.writeln("<FONT SIZE=2 FACE='verdana, arial, helvetica'><B>Additional Security for Your Private Key</B> </FONT><Br>");
document.writeln(" <font face='arial, helvetica' size=2>We recommend that you protect the private key associated with your digital ID.");
document.writeln(" Checking the box below will provide you with security options for your private key.");
document.writeln("<label id=try onClick=dumbfunc()><FONT COLOR=#FF0000> Click Here</FONT></LABEL>");
document.writeln(" for additional information.<BR></FONT>");
document.writeln(" <CENTER>");
document.writeln("<!--BEGIN INPUT FIELD TABLE-->");
document.writeln("<br><TABLE WIDTH=556 CELLPADDING=0 CELLSPACING=0 BORDER=0>");
document.writeln("<TR>");
document.writeln("<TD WIDTH=50% BGCOLOR='ffffcc'><font face='verdana, arial, helvetica' COLOR=#FF0000 size=2><B>Check this Box to Protect Your <BR>Private Key</B></FONT></TD>");
document.writeln("<TD COLSPAN=2 WIDTH=50% BGCOLOR='ffffcc'><IMG SRC='../graphics/blank2.gif' WIDTH=27 HEIGHT=27'>");
if (0)
   {
       document.writeln("<INPUT TYPE='checkbox' NAME='userprotect' CHECKED></TD>");            
   }
else
   {
       document.writeln("<INPUT TYPE='checkbox' NAME='userprotect'></TD>");      
   }
document.writeln("</TR>");
document.writeln("</TABLE>");
document.writeln("<!--END INPUT FIELD TABLE-->");
document.writeln("</TD>");
document.writeln("</TR>");
document.writeln("</TABLE>");
document.writeln("<!--END TABLE FIVE-->");
} 
</script>
<!-- VSSKENDPOLICYVAL#user#7 -->
