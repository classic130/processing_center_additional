<!-- VSSKBEGINPOLICYVAL#exists#1 -->
<TR>
<TD WIDTH=50% BGCOLOR="ffcc00"><FONT FACE="verdana, arial, helvetica" SIZE=2><B>Dept/Div/Proj: </B></FONT>
<Script Language="JavaScript">
<!--
if (%%bCertField%%) {
document.write("<FONT FACE=\"verdana, arial, helvetica\" SIZE=2 COLOR=\"0000cc\"><B>*</B></FONT>");
}
if ("%%bRequired%%"=="MANDATORY"){
document.write("<FONT FACE=\"verdana, arial, helvetica\" SIZE=1 COLOR=\"cc0000\"> &nbsp;&nbsp; (required)</FONT>");
}
//-->
</script>
<BR>
<FONT SIZE=2 FACE="arial, helvetica">(example -- Administration)<BR></FONT></TD>
<TD COLSPAN=2 WIDTH=50% BGCOLOR="ffcc00"><img SRC="../graphics/blank2.gif" WIDTH=27 HEIGHT=27" NAME="imgcert_org_unit">&nbsp;&nbsp;&nbsp;
<script Language="JavaScript">
    if (browserNum < 4)
        {document.write("<INPUT NAME='cert_org_unit' VALUE='' TYPE='text' SIZE='%%MinLength%%' MAXLENGTH='%%MaxLength%%'>")}
    else
        {document.write("<INPUT NAME=\"cert_org_unit\" VALUE=\"\" TYPE=\"text\" SIZE=\"%%MinLength%%\" MAXLENGTH=\"%%MaxLength%%\">")}
</script>
</TD>
</TR>
<!-- VSSKENDPOLICYVAL#exists#1 -->

<!-- VSSKBEGINPOLICYVAL#exists#2 -->
    if("%%bRequired%%"=="MANDATORY")
        checkFieldAndDisplay('imgcert_org_unit', 'cert_org_unit', document.proform.cert_org_unit.value);
<!-- VSSKENDPOLICYVAL#exists#2 -->

<!-- VSSKBEGINPOLICYVAL#exists#3 -->
<TR>
<TD WIDTH=50% BGCOLOR="ffcc00"><FONT FACE="verdana, arial, helvetica" SIZE=2><B>Dept/Div/Proj: </B></FONT>
<Script Language="JavaScript">
<!--
if (%%bCertField%%) {
document.write("<FONT FACE=\"verdana, arial, helvetica\" SIZE=2 COLOR=\"0000cc\"><B>*</B></FONT>");
}
if ("%%bRequired%%"=="MANDATORY"){
document.write("<FONT FACE=\"verdana, arial, helvetica\" SIZE=1 COLOR=\"cc0000\"> &nbsp;&nbsp; (required)</FONT>");
}
//-->
</script>
<BR>
<FONT SIZE=2 FACE="arial, helvetica">(example -- Administration)<BR></FONT></TD>
<TD COLSPAN=2 WIDTH=50% BGCOLOR="ffcc00"><img SRC="../graphics/blank2.gif" WIDTH=27 HEIGHT=27" NAME="imgcert_org_unit">&nbsp;&nbsp;&nbsp;<INPUT NAME="cert_org_unit" VALUE="" TYPE="text" SIZE="20" MAXLENGTH="64" onBlur="clearImage(imgcert_org_unit)">
</TD>
</TR>
<!-- VSSKENDPOLICYVAL#exists#3 -->


<!-- VSSKBEGINPOLICYVAL#exists#4 -->
cert_org_unit               %%type%%   %%bRequired%%        NONE          NONE
<!-- VSSKENDPOLICYVAL#exists#4 -->

<!-- VSSKBEGINPOLICYVAL#exists#5 -->
<INPUT TYPE=hidden NAME=cert_org_unit VALUE="$$cert_org_unit$$">
<!-- VSSKENDPOLICYVAL#exists#5 -->

<!-- VSSKBEGINPOLICYVAL#exists#6 -->
    if("%%bRequired%%"=="MANDATORY")
        checkFieldAndDisplay('imgcert_org_unit', 'Enroll_cert_org_unit', document.proform.Enroll_cert_org_unit.value);
<!-- VSSKENDPOLICYVAL#exists#6 -->

<!-- VSSKBEGINPOLICYVAL#exists#7 -->
<TR>
<TD WIDTH=50% BGCOLOR="ffcc00"><FONT FACE="verdana, arial, helvetica" SIZE=2><B>Dept/Div/Proj: </B></FONT>
<Script Language="JavaScript">
<!--
if (%%bCertField%%) {
document.write("<FONT FACE=\"verdana, arial, helvetica\" SIZE=2 COLOR=\"0000cc\"><B>*</B></FONT>");
}
if ("%%bRequired%%"=="MANDATORY"){
document.write("<FONT FACE=\"verdana, arial, helvetica\" SIZE=1 COLOR=\"cc0000\"> &nbsp;&nbsp; (required)</FONT>");
}
//-->
</script>
<BR>
<FONT SIZE=2 FACE="arial, helvetica">(example -- Administration)<BR></FONT></TD>
<TD COLSPAN=2 WIDTH=50% BGCOLOR="ffcc00"><img SRC="../graphics/blank2.gif" WIDTH=27 HEIGHT=27" NAME="imgcert_org_unit">&nbsp;&nbsp;&nbsp;<INPUT NAME="Enroll_cert_org_unit" VALUE="" TYPE="text" SIZE="20" MAXLENGTH="64" onBlur="clearImage(imgcert_org_unit)">
</TD>
</TR>
<!-- VSSKENDPOLICYVAL#exists#7 -->
