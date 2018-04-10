<!-- VSSKBEGINPOLICYVAL#user#1 -->
<TABLE WIDTH=588 BGCOLOR='ffffcc' CELLPADDING=7 CELLSPACING=0 BORDER=0>
<TR>
<TD WIDTH=588>
<FONT SIZE=2 FACE='verdana, arial, helvetica'><B>Publish your Digital ID</B> </FONT><Br>
<font face='arial, helvetica' size=2>You can choose whether you want your Digital ID to be published in a
public directory. Note that all the information contained in the Digital ID will be made publicly available.
<BR></FONT>
<P><CENTER>
<!--BEGIN INPUT FIELD TABLE-->
<TABLE WIDTH=574 CELLPADDING=3 CELLSPACING=2 BORDER=0>
<TR>
<TD WIDTH=50% BGCOLOR='ffcc00'><font face='verdana, arial, helvetica' size=2><B>Check this Box to Publish Your <BR>Certificate</B></FONT></TD>
<TD COLSPAN=2 WIDTH=50% BGCOLOR='ffcc00'><IMG SRC='../graphics/blank2.gif' WIDTH=27 HEIGHT=27'>
<Script Language="JavaScript">
<!--
if (%%bPublish%%)
   {
       document.writeln("<INPUT TYPE='checkbox' NAME='certPublishFlag' VALUE='Y' CHECKED></TD>");            
   }
else
   {
       document.writeln("<INPUT TYPE='checkbox' NAME='certPublishFlag VALUE='Y'></TD>");
   }
//-->
</Script>
</TR>
</TABLE>
<!--END INPUT FIELD TABLE-->
</TD>
</TR>
</TABLE>
<P><BR><P>
<!-- VSSKENDPOLICYVAL#user#1 -->



<!-- VSSKBEGINPOLICYVAL#user#2 -->
certPublishFlag        TEXT       OPTIONAL          NONE       NONE
<!-- VSSKENDPOLICYVAL#user#2 -->


<!-- VSSKBEGINPOLICYVAL#user#3 -->      
<INPUT TYPE=hidden NAME=certPublishFlag VALUE="$$certPublishFlag$$">
<!-- VSSKENDPOLICYVAL#user#3 -->

<!-- VSSKBEGINPOLICYVAL#user#4 -->
<TABLE WIDTH=588 BGCOLOR='ffffcc' CELLPADDING=7 CELLSPACING=0 BORDER=0>
<TR>
<TD WIDTH=588>
<FONT SIZE=2 FACE='verdana, arial, helvetica'><B>Publish your Digital ID</B> </FONT><Br>
<font face='arial, helvetica' size=2>You can choose whether you want your Digital ID to be published in a
public directory. Note that all the information contained in the Digital ID will be made publicly available.
<BR></FONT>
<P><CENTER>
<!--BEGIN INPUT FIELD TABLE-->
<TABLE WIDTH=574 CELLPADDING=3 CELLSPACING=2 BORDER=0>
<TR>
<TD WIDTH=50% BGCOLOR='ffcc00'><font face='verdana, arial, helvetica' size=2><B>Check this Box to Publish Your <BR>Certificate</B></FONT></TD>
<TD COLSPAN=2 WIDTH=50% BGCOLOR='ffcc00'><IMG SRC='../graphics/blank2.gif' WIDTH=27 HEIGHT=27'>
<Script Language="JavaScript">
<!--
if (%%bPublish%%)
   {
       document.writeln("<INPUT TYPE='checkbox' NAME='Enroll_certPublishFlag' VALUE='Y' CHECKED></TD>");            
   }
else
   {
       document.writeln("<INPUT TYPE='checkbox' NAME='Enroll_certPublishFlag VALUE='Y'></TD>");
   }
//-->
</Script>
</TR>
</TABLE>
<!--END INPUT FIELD TABLE-->
</TD>
</TR>
</TABLE>
<P><BR><P>
<!-- VSSKENDPOLICYVAL#user#4 -->

