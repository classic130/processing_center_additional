<!-- VSSKBEGINPOLICYVAL#exists#1 -->
<TR>
<TD WIDTH=50% BGCOLOR="ffcc00"><FONT FACE="verdana, arial, helvetica" SIZE=2><B>First Name: </B>
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
<FONT SIZE=2 FACE="arial, helvetica">Nickname or middle initial allowed<BR>(example -- Jack B.)<BR></FONT></TD>
<TD COLSPAN=2 WIDTH=50% BGCOLOR="ffcc00">
<img SRC="../graphics/blank2.gif" WIDTH=27 HEIGHT=27" NAME="imgmail_firstName">&nbsp;&nbsp;&nbsp;
<script Language="JavaScript">
     if (browserNum < 4) 
          {document.write("<INPUT NAME='mail_firstName' VALUE='' TYPE='text' SIZE='20' MAXLENGTH='30'>")}
     else
          {document.write("<INPUT NAME=\'mail_firstName\' VALUE=\"\" TYPE=\"text\" SIZE=\"20\" MAXLENGTH=\"30\" onBlur=\"clearImage(\'imgmail_firstName\')\">")}
</script>
</TD>               
</TR>
<!-- VSSKENDPOLICYVAL#exists#1 -->


<!-- VSSKBEGINPOLICYVAL#exists#2 -->
    if("%%bRequired%%"=="MANDATORY")
	checkFieldAndDisplay('imgmail_firstName', 'mail_firstName', document.proform.mail_firstName.value);
<!-- VSSKENDPOLICYVAL#exists#2 -->


<!-- VSSKBEGINPOLICYVAL#exists#3 -->
<TR>
<TD WIDTH=50% BGCOLOR="ffcc00"><FONT FACE="verdana, arial, helvetica" SIZE=2><B>First Name:	</B>
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
<FONT SIZE=2 FACE="arial, helvetica">Nickname or middle initial allowed<BR>(example -- Jack B.)<BR></FONT></TD>
<TD COLSPAN=2 WIDTH=50% BGCOLOR="ffcc00"><img SRC="../graphics/blank2.gif" WIDTH=27 HEIGHT=27 NAME="imgmail_firstName">&nbsp;&nbsp;&nbsp;<INPUT NAME="mail_firstName" VALUE="" TYPE="text" SIZE="20" MAXLENGTH="30" onBlur="clearImage(imgmail_firstName)"></TD>
</TR>	
<!-- VSSKENDPOLICYVAL#exists#3 -->


<!-- VSSKBEGINPOLICYVAL#exists#4 -->
mail_firstName		%%type%%   %%bRequired%%	NONE	      NONE
<!-- VSSKENDPOLICYVAL#exists#4 -->


<!-- VSSKBEGINPOLICYVAL#exists#5 -->
<INPUT TYPE=hidden NAME=mail_firstName VALUE="$$mail_firstName$$">
<!-- VSSKENDPOLICYVAL#exists#5 -->

<!-- VSSKBEGINPOLICYVAL#exists#6 -->
    if("%%bRequired%%"=="MANDATORY")
	checkFieldAndDisplay('imgmail_firstName', 'Enroll_mail_firstName', document.proform.Enroll_mail_firstName.value);
<!-- VSSKENDPOLICYVAL#exists#6 -->

<!-- VSSKBEGINPOLICYVAL#exists#7 -->
<TR>
<TD WIDTH=50% BGCOLOR="ffcc00"><FONT FACE="verdana, arial, helvetica" SIZE=2><B>First Name:	</B>
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
<FONT SIZE=2 FACE="arial, helvetica">Nickname or middle initial allowed<BR>(example -- Jack B.)<BR></FONT></TD>
<TD COLSPAN=2 WIDTH=50% BGCOLOR="ffcc00"><img SRC="../graphics/blank2.gif" WIDTH=27 HEIGHT=27 NAME="imgmail_firstName">&nbsp;&nbsp;&nbsp;<INPUT NAME="Enroll_mail_firstName" VALUE="" TYPE="text" SIZE="20" MAXLENGTH="30" onBlur="clearImage(imgmail_firstName)"></TD>
</TR>	
<!-- VSSKENDPOLICYVAL#exists#7 -->
