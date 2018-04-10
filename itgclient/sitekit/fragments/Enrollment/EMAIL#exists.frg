<!-- VSSKBEGINPOLICYVAL#exists#1 -->
<TR>		
<TD WIDTH=50% BGCOLOR="ffcc00"><FONT FACE="verdana, arial, helvetica" SIZE=2><B>Your E-mail Address: </B></FONT>
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
<FONT SIZE=2 FACE="arial, helvetica">(example -- jbdoe@verisign.com)<BR></FONT></TD>		
<TD COLSPAN=2 WIDTH=50% BGCOLOR="ffcc00"><img SRC="../graphics/blank2.gif" WIDTH=27 HEIGHT=27" NAME="imgmail_email">&nbsp;&nbsp;&nbsp;
<script Language="JavaScript">
     if (browserNum < 4) 
         {document.write("<INPUT NAME='mail_email' VALUE='' TYPE='text' SIZE='20' MAXLENGTH='230'>")}
     else
         {document.write("<INPUT NAME=\"mail_email\" VALUE=\"\" TYPE=\"text\" SIZE=\"20\" MAXLENGTH=\"230\" onBlur=\"clearImage(\'imgmail_email\')\">")}
</script>
</TD>
</TR>
<!-- VSSKENDPOLICYVAL#exists#1 -->


<!-- VSSKBEGINPOLICYVAL#exists#2 -->
     if ("%%bRequired%%"=="MANDATORY")
  	  checkmail_email();
<!-- VSSKENDPOLICYVAL#exists#2 -->



<!-- VSSKBEGINPOLICYVAL#exists#3 -->
//function checkmail_email makes sure that there is an "@" in the string and that a "." 
//appears as the 3rd or 4th from last character.
function checkmail_email() 
  {             
      if (document.proform.mail_email.value == "")                    
          {
             forn++;
             document.images['imgmail_email'].src = "../graphics/bang2.gif"
          }
      else 
      if ((document.proform.mail_email.value.indexOf("@") != -1) && 
          (document.proform.mail_email.value.indexOf("@") < document.proform.mail_email.value.lastIndexOf(".")))
         {
            document.images['imgmail_email'].src = "../graphics/blank2.gif"; 
         }
      else
         {
            forn++;
            document.images['imgmail_email'].src = "../graphics/bang2.gif"; 
            //alert("Please include a proper email address.");
         }
   }
<!-- VSSKENDPOLICYVAL#exists#3 -->


<!-- VSSKBEGINPOLICYVAL#exists#4 -->
<TR>
<TD WIDTH=50% BGCOLOR="ffcc00"><FONT FACE="verdana, arial, helvetica" SIZE=2><B>E-mail Address: </B></FONT>
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
<FONT SIZE=2 FACE="arial, helvetica">(example -- jbdoe@verisign.com)<BR></FONT></TD>
<TD COLSPAN=2 WIDTH=50% BGCOLOR="ffcc00"><img SRC="../graphics/blank2.gif" WIDTH=27 HEIGHT=27 NAME="imgmail_email">&nbsp;&nbsp;&nbsp;<INPUT NAME="mail_email" VALUE="" TYPE="text" SIZE="20" MAXLENGTH="230" onBlur="clearImage(imgmail_email)"></TD>
</TR>
<!-- VSSKENDPOLICYVAL#exists#4 -->


<!-- VSSKBEGINPOLICYVAL#exists#5 -->
mail_email		%%type%%   %%bRequired%%	NONE	      NONE
<!-- VSSKENDPOLICYVAL#exists#5 -->


<!-- VSSKBEGINPOLICYVAL#exists#6 -->
<INPUT TYPE=hidden NAME=mail_email VALUE="$$mail_email$$">
<!-- VSSKENDPOLICYVAL#exists#6 -->


<!-- VSSKBEGINPOLICYVAL#exists#7 -->
<!-- VSSKENDPOLICYVAL#exists#7 -->

<!-- VSSKBEGINPOLICYVAL#exists#8 -->
<!-- VSSKENDPOLICYVAL#exists#8 -->


<!-- VSSKBEGINPOLICYVAL#exists#9 -->
<!-- VSSKENDPOLICYVAL#exists#9 -->

<!-- VSSKBEGINPOLICYVAL#exists#10 -->
            rval = confirm("Confirm your e-mail address:\n "+ document.proform.mail_email.value + 
                            "\n\nIf your e-mail address is correct click OK, if not click CANCEL " + 
                            "and \ncorrect it in the enrollment form.  \n\nIf the e-mail address is " +
                            "not correct you will not be able to use your Digital ID");
<!-- VSSKENDPOLICYVAL#exists#10 -->


<!-- VSSKBEGINPOLICYVAL#exists#11 -->
            else document.proform.mail_email.focus() ;
<!-- VSSKENDPOLICYVAL#exists#11 -->

<!-- VSSKBEGINPOLICYVAL#exists#12 -->
//function checkmail_email makes sure that there is an "@" in the string and that a "." 
//appears as the 3rd or 4th from last character.
function checkmail_email() 
  {             
      if (document.proform.Enroll_mail_email.value == "")                    
          {
             forn++;
             document.images['imgmail_email'].src = "../graphics/bang2.gif"
          }
      else 
      if ((document.proform.Enroll_mail_email.value.indexOf("@") != -1) && 
          (document.proform.Enroll_mail_email.value.indexOf("@") < document.proform.Enroll_mail_email.value.lastIndexOf(".")))
         {
            document.images['imgmail_email'].src = "../graphics/blank2.gif"; 
         }
      else
         {
            forn++;
            document.images['imgmail_email'].src = "../graphics/bang2.gif"; 
            //alert("Please include a proper email address.");
         }
   }
<!-- VSSKENDPOLICYVAL#exists#12 -->

<!-- VSSKBEGINPOLICYVAL#exists#13 -->
            rval = confirm("Confirm your e-mail address:\n "+ document.proform.Enroll_mail_email.value + 
                            "\n\nIf your e-mail address is correct click OK, if not click CANCEL " + 
                            "and \ncorrect it in the enrollment form.  \n\nIf the e-mail address is " +
                            "not correct you will not be able to use your Digital ID");
<!-- VSSKENDPOLICYVAL#exists#13 -->

<!-- VSSKBEGINPOLICYVAL#exists#14 -->
            else document.proform.Enroll_mail_email.focus() ;
<!-- VSSKENDPOLICYVAL#exists#14 -->

<!-- VSSKBEGINPOLICYVAL#exists#15 -->
<TR>
<TD WIDTH=50% BGCOLOR="ffcc00"><FONT FACE="verdana, arial, helvetica" SIZE=2><B>E-mail Address: </B></FONT>
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
<FONT SIZE=2 FACE="arial, helvetica">(example -- jbdoe@verisign.com)<BR></FONT></TD>
<TD COLSPAN=2 WIDTH=50% BGCOLOR="ffcc00"><img SRC="../graphics/blank2.gif" WIDTH=27 HEIGHT=27 NAME="imgmail_email">&nbsp;&nbsp;&nbsp;<INPUT NAME="Enroll_mail_email" VALUE="" TYPE="text" SIZE="20" MAXLENGTH="230" onBlur="clearImage(imgmail_email)"></TD>
</TR>
<!-- VSSKENDPOLICYVAL#exists#15 -->