<!-- VSSKBEGINPOLICYVAL#exists#1 -->
<TR>
<TD WIDTH=50% BGCOLOR="ffcc00"><FONT FACE="verdana, arial, helvetica" SIZE=2><B>%%DisplayName%%: </B></FONT>
<Script Language="JavaScript">
<!--
if (%%bCertField%%) {
document.write("<FONT FACE=\"verdana, arial, helvetica\" SIZE=2 COLOR=\"0000cc\"><B>*</B></FONT>");
}
if ("%%bRequired%%"=="MANDATORY"){
document.write("<FONT FACE=\"verdana, arial, helvetica\" SIZE=1  COLOR=\"cc0000\"> &nbsp;&nbsp; (required)</FONT>");
}
//-->
</script>
</TD>
<TD COLSPAN=2 WIDTH=50% BGCOLOR="ffcc00"><img SRC="../graphics/blank2.gif" WIDTH=27 HEIGHT=27" NAME="imgadditional_field6">&nbsp;&nbsp;&nbsp;
<script Language="JavaScript">
    if (browserNum < 4) 
         {document.write("<INPUT NAME='additional_field6' VALUE='' TYPE='text' SIZE='%%MinLength%%' MAXLENGTH='%%MaxLength%%'>")}
    else
         {document.write("<INPUT NAME=\"additional_field6\" VALUE=\"\" TYPE=\"text\" SIZE=\"%%MinLength%%\" MAXLENGTH=\"%%MaxLength%%\">")}
</script>
</TD>
</TR>
<!-- VSSKENDPOLICYVAL#exists#1 -->


<!-- VSSKBEGINPOLICYVAL#exists#2 -->
    if("%%bRequired%%"=="MANDATORY")
	checkFieldAndDisplay('imgadditional_field6', 'additional_field6', document.proform.additional_field6.value);
<!-- VSSKENDPOLICYVAL#exists#2 -->


<!-- VSSKBEGINPOLICYVAL#exists#3 -->
<TR>
<TD WIDTH=50% BGCOLOR="ffcc00"><FONT FACE="verdana, arial, helvetica" SIZE=2><B>%%DisplayName%%: </B></FONT>
<Script Language="JavaScript">
<!--
if (%%bCertField%%) {
document.write("<FONT FACE=\"verdana, arial, helvetica\" SIZE=2 COLOR=\"0000cc\"><B>*</B></FONT>");
}
if ("%%bRequired%%"=="MANDATORY"){
document.write("<FONT FACE=\"verdana, arial, helvetica\" SIZE=1  COLOR=\"cc0000\"> &nbsp;&nbsp; (required)</FONT>");
}
//-->
</script>
</TD>
<TD COLSPAN=2 WIDTH=50% BGCOLOR="ffcc00"><img SRC="../graphics/blank2.gif" WIDTH=27 HEIGHT=27" NAME="imgadditional_field6">&nbsp;&nbsp;&nbsp;<INPUT NAME="additional_field6" VALUE="" TYPE="text" SIZE="%%MinLength%%" MAXLENGTH="%%MaxLength%%"></TD>
</TR>
<!-- VSSKENDPOLICYVAL#exists#3 -->


<!-- VSSKBEGINPOLICYVAL#exists#4 -->
additional_field6	%%type%%   %%bRequired%%	NONE	      NONE
<!-- VSSKENDPOLICYVAL#exists#4 -->

<!-- VSSKBEGINPOLICYVAL#exists#5 -->
<INPUT TYPE=hidden NAME=additional_field6 VALUE="$$additional_field6$$">
<!-- VSSKENDPOLICYVAL#exists#5 -->

<!-- VSSKBEGINPOLICYVAL#exists#6 -->
    if("%%bRequired%%"=="MANDATORY")
	checkFieldAndDisplay('imgadditional_field6', 'Enroll_additional_field6', document.proform.Enroll_additional_field6.value);
<!-- VSSKENDPOLICYVAL#exists#6 -->


<!-- VSSKBEGINPOLICYVAL#exists#7 -->
<TR>
<TD WIDTH=50% BGCOLOR="ffcc00"><FONT FACE="verdana, arial, helvetica" SIZE=2><B>%%DisplayName%%: </B></FONT>
<Script Language="JavaScript">
<!--
if (%%bCertField%%) {
document.write("<FONT FACE=\"verdana, arial, helvetica\" SIZE=2 COLOR=\"0000cc\"><B>*</B></FONT>");
}
if ("%%bRequired%%"=="MANDATORY"){
document.write("<FONT FACE=\"verdana, arial, helvetica\" SIZE=1  COLOR=\"cc0000\"> &nbsp;&nbsp; (required)</FONT>");
}
//-->
</script>
</TD>
<TD COLSPAN=2 WIDTH=50% BGCOLOR="ffcc00"><img SRC="../graphics/blank2.gif" WIDTH=27 HEIGHT=27" NAME="imgadditional_field6">&nbsp;&nbsp;&nbsp;<INPUT NAME="Enroll_additional_field6" VALUE="" TYPE="text" SIZE="%%MinLength%%" MAXLENGTH="%%MaxLength%%"></TD>
</TR>
<!-- VSSKENDPOLICYVAL#exists#7 -->

<!-- VSSKBEGINPOLICYVAL#exists#8 -->
if ("%%bRequired%%"=="MANDATORY")
<!--  23 July 2004: Begin Changes Added for JPTA RE-Arch-->
document.proform.additional_field6.value = appletRef.getKey("additional_field6")
<!--  23 July 2004: End Changes -->
<!-- VSSKENDPOLICYVAL#exists#8 -->