<!-- VSSKBEGINPOLICYVAL#noshow#1 -->
&nbsp;
<TABLE WIDTH=588 BGCOLOR="ffffcc" CELLPADDING=7 CELLSPACING=0 BORDER=0>
<TR>
	<TD WIDTH=588>
<FONT SIZE=2 FACE="verdana, arial, helvetica"><B>Privacy Policy Acceptance</B><br>
[Insert text supplied by Affiliate's legal counsel and agreed to by VeriSign Pratices.]
</FONT>
</TD>	
</TR>
<TR><TD>
    <!--BEGIN INPUT FIELD TABLE-->
    <TABLE WIDTH=574 CELLPADDING=3 CELLSPACING=2 BORDER=0>                
    <TR>
    <TD WIDTH=50% BGCOLOR="ffcc00">
    <FONT FACE="verdana, arial, helvetica" SIZE=2><B>I agree:</B></FONT>
    </TD>
    <TD COLSPAN=2 WIDTH=50% BGCOLOR="ffcc00"><IMG SRC="../graphics/blank2.gif" WIDTH=27 HEIGHT=27" NAME="imgprivacy">&nbsp;&nbsp;&nbsp;
    <script Language="JavaScript">
    <!--
        document.write("<INPUT TYPE=\"CHECKBOX\" NAME=\"privacy_yes_no\" VALUE=\"CHECKED\">")
    //-->
    </script>
    </TD>             
    </TR>
    </TABLE>
</TD>
</TR>
</TABLE>
</TABLE>
<!-- VSSKENDPOLICYVAL#noshow#1 -->


<!-- VSSKBEGINPOLICYVAL#noshow#2 --> 
                     if (document.proform.privacy_yes_no.checked == true) {
		         document.proform.additional_field3.value = document.proform.additional_field3.value + 
			 " Agreement accepted : Yes"
		     }
		     else {
		         alert("Your enrollment can not be processed since you have not agreed to our privacy statement.");
			 return false;
		     }
<!-- VSSKENDPOLICYVAL#noshow#2 -->

