<!-- VSSKBEGINPOLICYVAL#exists#1 -->
<TR>
<TD WIDTH=50% BGCOLOR="ffcc00"><FONT FACE="verdana, arial, helvetica" SIZE=2><B>Last Name: </B>
<Script Language="JavaScript">
<!--
if (%%bCertField%%) {
document.write("<FONT COLOR=\"0000cc\"><B>*</B></FONT>");
}
if ("%%bRequired%%"=="MANDATORY"){
document.write("<FONT FACE=\"verdana, arial, helvetica\" SIZE=1  COLOR=\"cc0000\"> &nbsp;&nbsp; (required)</FONT>");
}
//-->
</script>
<BR>
<FONT SIZE=2 FACE="arial, helvetica">(example -- Doe)<BR></FONT></TD>
<TD COLSPAN=2 WIDTH=50% BGCOLOR="ffcc00"><img SRC="../graphics/blank2.gif" WIDTH=27 HEIGHT=27" NAME="imgmail_lastName">&nbsp;&nbsp;&nbsp;
<script Language="JavaScript">
     if (browserNum < 4) 
          {document.write("<INPUT NAME='mail_lastName' VALUE='' TYPE='text' SIZE='20' MAXLENGTH='30'>")}
     else
          {document.write("<INPUT NAME=\'mail_lastName\' VALUE=\"\" TYPE=\"text\" SIZE=\"20\" MAXLENGTH=\"30\" onBlur=\"clearImage(\'imgmail_lastName\')\">")}
</script>
</TD>
</TR>
<!-- VSSKENDPOLICYVAL#exists#1 -->


<!-- VSSKBEGINPOLICYVAL#exists#2 -->
    if("%%bRequired%%"=="MANDATORY")
	checkFieldAndDisplay('imgmail_lastName', 'mail_lastName', document.proform.mail_lastName.value);
<!-- VSSKENDPOLICYVAL#exists#2 -->


<!-- VSSKBEGINPOLICYVAL#exists#3 -->
<TR>
<TD WIDTH=50% BGCOLOR="ffcc00"><FONT FACE="verdana, arial, helvetica" SIZE=2><B>Last Name: </B>
<Script Language="JavaScript">
<!--
if (%%bCertField%%) {
document.write("<FONT COLOR=\"0000cc\"><B>*</B></FONT>");
}
if ("%%bRequired%%"=="MANDATORY"){
document.write("<FONT FACE=\"verdana, arial, helvetica\" SIZE=1 COLOR=\"cc0000\"> &nbsp;&nbsp; (required)</FONT>");
}
//-->
</script>
<BR>
<FONT SIZE=2 FACE="arial, helvetica">(example -- Doe)<BR></FONT></TD>
<TD COLSPAN=2 WIDTH=50% BGCOLOR="ffcc00"><img SRC="../graphics/blank2.gif" WIDTH=27 HEIGHT=27 NAME="imgmail_lastName">&nbsp;&nbsp;&nbsp;<INPUT NAME="mail_lastName" VALUE="" TYPE="text" SIZE="20" MAXLENGTH="30" onBlur="clearImage(imgmail_lastName)"></TD>
</TR>
<!-- VSSKENDPOLICYVAL#exists#3 -->


<!-- VSSKBEGINPOLICYVAL#exists#4 -->
mail_lastName		%%type%%   %%bRequired%%	NONE	      NONE
<!-- VSSKENDPOLICYVAL#exists#4 -->

<!-- VSSKBEGINPOLICYVAL#exists#5 -->
<INPUT TYPE=hidden NAME=mail_lastName VALUE="$$mail_lastName$$">
<!-- VSSKENDPOLICYVAL#exists#5 -->

<!-- VSSKBEGINPOLICYVAL#exists#6 -->
    if("%%bRequired%%"=="MANDATORY")
	checkFieldAndDisplay('imgmail_lastName', 'Enroll_mail_lastName', document.proform.Enroll_mail_lastName.value);
<!-- VSSKENDPOLICYVAL#exists#6 -->


<!-- VSSKBEGINPOLICYVAL#exists#7 -->
<TR>
<TD WIDTH=50% BGCOLOR="ffcc00"><FONT FACE="verdana, arial, helvetica" SIZE=2><B>Last Name: </B>
<Script Language="JavaScript">
<!--
if (%%bCertField%%) {
document.write("<FONT COLOR=\"0000cc\"><B>*</B></FONT>");
}
if ("%%bRequired%%"=="MANDATORY"){
document.write("<FONT FACE=\"verdana, arial, helvetica\" SIZE=1 COLOR=\"cc0000\"> &nbsp;&nbsp; (required)</FONT>");
}
//-->
</script>
<BR>
<FONT SIZE=2 FACE="arial, helvetica">(example -- Doe)<BR></FONT></TD>
<TD COLSPAN=2 WIDTH=50% BGCOLOR="ffcc00"><img SRC="../graphics/blank2.gif" WIDTH=27 HEIGHT=27 NAME="imgmail_lastName">&nbsp;&nbsp;&nbsp;<INPUT NAME="Enroll_mail_lastName" VALUE="" TYPE="text" SIZE="20" MAXLENGTH="30" onBlur="clearImage(imgmail_lastName)"></TD>
</TR>
<!-- VSSKENDPOLICYVAL#exists#7 -->
