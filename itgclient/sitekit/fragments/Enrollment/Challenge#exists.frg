<!-- VSSKBEGINPOLICYVAL#exists#1 -->
<TABLE WIDTH=588 BGCOLOR="ffffcc" CELLPADDING=7 CELLSPACING=0 BORDER=0>
<TR>       
<TD WIDTH=588>
<FONT SIZE=2 FACE="verdana, arial, helvetica"><B>Challenge Phrase</B></FONT><BR>
<FONT FACE="arial, helvetica" SIZE=2>This unique phrase protects you against unauthorized action 
  on your Digital ID and should not be
 shared with anyone. Do not lose it! It is required to revoke and renew your Digital ID.<BR></FONT>
<P>
<CENTER>
        
    <!--BEGIN INPUT FIELD TABLE-->
    <TABLE WIDTH=574 CELLPADDING=3 CELLSPACING=2 BORDER=0>                
    <TR>
    <TD WIDTH=50% BGCOLOR="ffcc00">
    <FONT FACE="verdana, arial, helvetica" SIZE=2><B>Enter Challenge Phrase:</B></FONT>
    <script Language="JavaScript">
    <!-->
    if ("%%bRequired%%"=="MANDATORY"){
        document.write("<FONT FACE=\"verdana, arial, helvetica\" SIZE=1  COLOR=\"cc0000\"> &nbsp;&nbsp; (required)</FONT>");
    }
    //-->
    </script>
    <BR><FONT SIZE=2 FACE="arial, helvetica">Do not use any punctuation.<BR></FONT>
    </TD>
    <TD COLSPAN=2 WIDTH=50% BGCOLOR="ffcc00"><IMG SRC="../graphics/blank2.gif" WIDTH=27 HEIGHT=27" NAME="imgchallenge">&nbsp;&nbsp;&nbsp;
    <script Language="JavaScript">
    <!--
        if (browserNum < 4) 
            {document.write("<INPUT NAME='challenge' VALUE='' TYPE='PASSWORD' SIZE='20' MAXLENGTH='32'>")}
        else
            {document.write("<INPUT NAME=\"challenge\" VALUE=\"\" TYPE=\"PASSWORD\" SIZE=\"20\" MAXLENGTH=\"32\" onBlur=\"clearImage(\'imgchallenge\')\">")}
    //-->
    </script>
    </TD>             
    </TR>
    </TABLE>
</TD>
</TR>
</TABLE>
<P><BR><P>
<!-- VSSKENDPOLICYVAL#exists#1 -->



<!-- VSSKBEGINPOLICYVAL#exists#2 -->
     if ("%%bRequired%%"=="MANDATORY")     
	checkFieldAndDisplay('imgchallenge', 'challenge', document.proform.challenge.value);
<!-- VSSKENDPOLICYVAL#exists#2 -->

<!-- VSSKBEGINPOLICYVAL#exists#3 -->
<TABLE WIDTH=588 BGCOLOR="ffffcc" CELLPADDING=7 CELLSPACING=0 BORDER=0>
<TR>
<TD WIDTH=588>
<FONT SIZE=2 FACE="verdana, arial, helvetica"><B>Challenge Phrase</B></FONT><BR>
<FONT FACE="arial, helvetica" SIZE=2>This unique phrase protects you against unauthorized action 
on your Digital ID and should not be
shared with anyone. Do not lose it! It is required to revoke and renew your Digital ID.<BR></FONT>
<P>
<CENTER>
    <!--BEGIN INPUT FIELD TABLE-->
    <TABLE WIDTH=574 CELLPADDING=3 CELLSPACING=2 BORDER=0>	
    <TR>
    <TD WIDTH=50% BGCOLOR="ffcc00"><FONT FACE="verdana, arial, helvetica" SIZE=2><B>Enter Challenge Phrase:</B></FONT>
    <script Language="JavaScript">
    <!--
    if ("%%bRequired%%"=="MANDATORY"){
        document.write("<FONT FACE=\"verdana, arial, helvetica\" SIZE=1  COLOR=\"cc0000\"> &nbsp;&nbsp; (required)</FONT>");
    }
    //-->
    </script>
    <BR><FONT SIZE=2 FACE="arial, helvetica">Do not use any punctuation.<BR></FONT></TD>
    <TD COLSPAN=2 WIDTH=50% BGCOLOR="ffcc00"><IMG SRC="../graphics/blank2.gif" WIDTH=27 HEIGHT=27"  NAME="imgchallenge">&nbsp;&nbsp;&nbsp;
       <INPUT NAME="challenge" VALUE="" TYPE="PASSWORD" SIZE="20" MAXLENGTH="32" onBlur="clearImage(imgchallenge)">
    </TD>
    </TR>
    </TABLE>
<!--END INPUT FIELD TABLE-->
</TD>
</TR>
</TABLE>
<P><BR><P>
<!-- VSSKENDPOLICYVAL#exists#3 -->


<!-- VSSKBEGINPOLICYVAL#exists#4 -->
challenge		%%type%%   %%bRequired%%	NONE	      NONE
<!-- VSSKENDPOLICYVAL#exists#4 -->



<!-- VSSKBEGINPOLICYVAL#exists#5 -->
<INPUT TYPE=hidden NAME=challenge VALUE="$$challenge$$">
<!-- VSSKENDPOLICYVAL#exists#5 -->

<!-- VSSKBEGINPOLICYVAL#exists#6 -->
     if ("%%bRequired%%"=="MANDATORY")     
	checkFieldAndDisplay('imgchallenge', 'Enroll_challenge', document.proform.Enroll_challenge.value);
<!-- VSSKENDPOLICYVAL#exists#6 -->

<!-- VSSKBEGINPOLICYVAL#exists#7 -->
<TABLE WIDTH=588 BGCOLOR="ffffcc" CELLPADDING=7 CELLSPACING=0 BORDER=0>
<TR>
<TD WIDTH=588>
<FONT SIZE=2 FACE="verdana, arial, helvetica"><B>Challenge Phrase</B></FONT><BR>
<FONT FACE="arial, helvetica" SIZE=2>This unique phrase protects you against unauthorized action 
on your Digital ID and should not be
shared with anyone. Do not lose it! It is required to revoke and renew your Digital ID.<BR></FONT>
<P>
<CENTER>
    <!--BEGIN INPUT FIELD TABLE-->
    <TABLE WIDTH=574 CELLPADDING=3 CELLSPACING=2 BORDER=0>	
    <TR>
    <TD WIDTH=50% BGCOLOR="ffcc00"><FONT FACE="verdana, arial, helvetica" SIZE=2><B>Enter Challenge Phrase:</B></FONT>
    <script Language="JavaScript">
    <!--
    if ("%%bRequired%%"=="MANDATORY"){
        document.write("<FONT FACE=\"verdana, arial, helvetica\" SIZE=1  COLOR=\"cc0000\"> &nbsp;&nbsp; (required)</FONT>");
    }
    //-->
    </script>
    <BR><FONT SIZE=2 FACE="arial, helvetica">Do not use any punctuation.<BR></FONT></TD>
    <TD COLSPAN=2 WIDTH=50% BGCOLOR="ffcc00"><IMG SRC="../graphics/blank2.gif" WIDTH=27 HEIGHT=27"  NAME="imgchallenge">&nbsp;&nbsp;&nbsp;
       <INPUT NAME="Enroll_challenge" VALUE="" TYPE="PASSWORD" SIZE="20" MAXLENGTH="32" onBlur="clearImage(imgchallenge)">
    </TD>
    </TR>
    </TABLE>
<!--END INPUT FIELD TABLE-->
</TD>
</TR>
</TABLE>
<P><BR><P>
<!-- VSSKENDPOLICYVAL#exists#7 -->

