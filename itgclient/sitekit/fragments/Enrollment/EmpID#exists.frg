<!-- VSSKBEGINPOLICYVAL#exists#1 -->
<TR>
<TD WIDTH=50% BGCOLOR="ffcc00"><FONT FACE="verdana, arial, helvetica" SIZE=2><B>Employee ID Number: </B></FONT>
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
<BR><FONT SIZE=2 FACE="arial, helvetica">(example -- 12345)<BR></FONT></TD>
<TD COLSPAN=2 WIDTH=50% BGCOLOR="ffcc00"><img SRC="../graphics/blank2.gif" WIDTH=27 HEIGHT=27" NAME="imgemployeeID">&nbsp;&nbsp;&nbsp;
<script Language="JavaScript">
    if (browserNum < 4) 
        {document.write("<INPUT NAME='employeeID' VALUE='' TYPE='text' SIZE='20' MAXLENGTH='64'>")}
    else
        {document.write("<INPUT NAME=\"employeeID\" VALUE=\"\" TYPE=\"text\" SIZE=\"20\" MAXLENGTH=\"64\">")}
</script>
</TD>
</TR>
<!-- VSSKENDPOLICYVAL#exists#1 -->


<!-- VSSKBEGINPOLICYVAL#exists#2 -->
    if("%%bRequired%%"=="MANDATORY")
	checkFieldAndDisplay('imgemployeeID', 'employeeID', document.proform.employeeID.value);
<!-- VSSKENDPOLICYVAL#exists#2 -->


<!-- VSSKBEGINPOLICYVAL#exists#3 -->
<TR>
<TD WIDTH=50% BGCOLOR="ffcc00"><FONT FACE="verdana, arial, helvetica" SIZE=2><B>Employee ID Number: </B></FONT>
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
<BR>
<FONT SIZE=2 FACE="arial, helvetica">(example -- 12345)<BR></FONT></TD>
<TD COLSPAN=2 WIDTH=50% BGCOLOR="ffcc00"><img SRC="../graphics/blank2.gif" WIDTH=27 HEIGHT=27" NAME="imgemployeeID">&nbsp;&nbsp;&nbsp;<INPUT NAME="employeeID" VALUE="" TYPE="text" SIZE="20" MAXLENGTH="64"></TD>
</TR>
<!-- VSSKENDPOLICYVAL#exists#3 -->


<!-- VSSKBEGINPOLICYVAL#exists#4 -->
employeeID		%%type%%   %%bRequired%%	NONE	      NONE
<!-- VSSKENDPOLICYVAL#exists#4 -->


<!-- VSSKBEGINPOLICYVAL#exists#5 -->
<INPUT TYPE=hidden NAME=employeeID VALUE="$$employeeID$$">
<!-- VSSKENDPOLICYVAL#exists#5 -->

<!-- VSSKBEGINPOLICYVAL#exists#6 -->
    if("%%bRequired%%"=="MANDATORY")
	checkFieldAndDisplay('imgemployeeID', 'Enroll_employeeID', document.proform.Enroll_employeeID.value);
<!-- VSSKENDPOLICYVAL#exists#6 -->


<!-- VSSKBEGINPOLICYVAL#exists#7 -->
<TR>
<TD WIDTH=50% BGCOLOR="ffcc00"><FONT FACE="verdana, arial, helvetica" SIZE=2><B>Employee ID Number: </B></FONT>
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
<BR>
<FONT SIZE=2 FACE="arial, helvetica">(example -- 12345)<BR></FONT></TD>
<TD COLSPAN=2 WIDTH=50% BGCOLOR="ffcc00"><img SRC="../graphics/blank2.gif" WIDTH=27 HEIGHT=27" NAME="imgemployeeID">&nbsp;&nbsp;&nbsp;<INPUT NAME="Enroll_employeeID" VALUE="" TYPE="text" SIZE="20" MAXLENGTH="64"></TD>
</TR>
<!-- VSSKENDPOLICYVAL#exists#7 -->

<!-- VSSKBEGINPOLICYVAL#exists#8 -->
<!--  23 July 2004: Begin Changes Added for JPTA Re-Arch. -->
if ("%%bRequired%%"=="MANDATORY")
	document.proform.employeeID.value = appletRef.getKey("employeeID")
<!--  23 July 2004: End Changes -->
<!-- VSSKENDPOLICYVAL#exists#8 -->
