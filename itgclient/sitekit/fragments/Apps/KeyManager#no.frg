
// for the enrollment fdf files
<!-- VSSKBEGINPOLICYVAL#no#1 -->
<!-- VSSKENDPOLICYVAL#no#1 -->


<!-- VSSKBEGINPOLICYVAL#no#2 -->
<TR>
	<TD WIDTH=50 ALIGN=left VALIGN=top>
        <NOSCRIPT><A HREF="client/enroll.htm"></NOSCRIPT>
        <script Language="JavaScript">
        if (navigator.appName == "Netscape") 
          {document.write("<A HREF='client/userEnrollNS.htm'>")}
	else
            if ( ("%%Enrollment/CertStore::policyValue%%" == "verisign") || (bIsWin2k == true) )
               {document.write("<A HREF='client/userEnrollMS.htm'>")}
            else
               { CheckIESupportedVersion1("<A HREF='client/userEnrollMS.htm'>");}
        </script>
	<IMG SRC="graphics/action_checkyellow.gif" WIDTH="40" HEIGHT="40" BORDER="0"></A>
	</TD>
	<TD WIDTH=538 ALIGN=left VALIGN=top>
        <NOSCRIPT><A HREF="client/enroll.htm"></NOSCRIPT>
        <script Language="JavaScript">
        if (navigator.appName == "Netscape") 
          {document.write("<A HREF='client/userEnrollNS.htm'>")}
	else
            if ( ("%%Enrollment/CertStore::policyValue%%" == "verisign") || (bIsWin2k == true) )
               {document.write("<A HREF='client/userEnrollMS.htm'>")}
            else
               { CheckIESupportedVersion1("<A HREF='client/userEnrollMS.htm'>");}
        </script>
	<FONT FACE="verdana, arial, helvetica" SIZE=5><B>ENROLL</B></FONT></A><BR>
	<FONT FACE="arial, helvetica" SIZE=2>Choose this option to enroll for a Digital ID for Microsoft or Firefox.</FONT>
	<P>
	</TD>
</TR>
<!-- VSSKENDPOLICYVAL#no#2 -->


<!-- VSSKBEGINPOLICYVAL#no#3 --> 
<TR>
	<TD WIDTH=50 ALIGN=left VALIGN=top>
        <NOSCRIPT><A HREF="client/retrieve_id.htm"></NOSCRIPT>
        <script Language="JavaScript">
        if (navigator.appName == "Netscape") 
          {document.write("<A HREF='client/nspickup.htm'>")}
	else
          {document.write("<A HREF='client/mspickup.htm'>")}
        </script>
	<IMG SRC="graphics/action_arrowyellow.gif" WIDTH=40 HEIGHT=40 BORDER=0 ALT=""></A>
	</TD>
	<TD WIDTH=538 ALIGN=left VALIGN=top>
        <NOSCRIPT><A HREF="client/retrieve_id.htm"></NOSCRIPT>
        <script Language="JavaScript">
        if (navigator.appName == "Netscape") 
          {document.write("<A HREF='client/nspickup.htm'>")}
	else
          {document.write("<A HREF='client/mspickup.htm'>")}
        </script>
	<FONT FACE="verdana, arial, helvetica" SIZE=5><B>PICK-UP ID</B></FONT></A><BR>
	<FONT FACE="arial, helvetica" SIZE=2>Choose this option if you have enrolled for a Digital ID but have not picked it up.</FONT>
	<P>
	</TD>
</TR>
<!-- VSSKENDPOLICYVAL#no#3 -->


<!-- VSSKBEGINPOLICYVAL#no#4 -->
<TABLE WIDTH=588 BGCOLOR="ffffcc" CELLPADDING=2 CELLSPACING=0 BORDER=0>
<TR>
	<TD COLSPAN=2><IMG SRC="../graphics/ie_logo2.gif" ALT="Microsoft" border=0>
        <a href="mspickup.htm">
	<FONT FACE="verdana, arial, helvetica" SIZE=4>For Microsoft Internet Explorer</A><BR><BR></TD> 
</TR>
<TR>
	<TD COLSPAN=2><IMG SRC="../graphics/ns_logo.gif" ALT="Firefox" border=0>
        <a href="nspickup.htm">
	<FONT FACE="verdana, arial, helvetica" SIZE=4>For Firefox<BR><BR></A></TD> 
</TR>
</TABLE>
<!-- VSSKENDPOLICYVAL#no#4 -->


<!-- VSSKBEGINPOLICYVAL#no#5 -->
<TABLE WIDTH=588 BGCOLOR="ffffcc" CELLPADDING=2 CELLSPACING=0 BORDER=0>
<TR>
	<TD COLSPAN=2><IMG SRC="../graphics/ie_logo2.gif" ALT="Microsoft" border=0><a href="userEnrollMS.htm">
	<FONT FACE="verdana, arial, helvetica" SIZE=4>For Microsoft Internet Explorer</A><BR><BR></TD> 
</TR>
<TR>
	<TD COLSPAN=2><IMG SRC="../graphics/ns_logo.gif" ALT="Firefox" border=0><a href="userEnrollNS.htm">
	<FONT FACE="verdana, arial, helvetica" SIZE=4>For Firefox<BR><BR></A></TD> 
</TR>
</TABLE>
<!-- VSSKENDPOLICYVAL#no#5 -->


// for userEnrollMS.fdf and userEnrollNS.fdf
<!-- VSSKBEGINPOLICYVAL#no#6 -->
CONST     originator           VeriSign OnSite
<!-- VSSKENDPOLICYVAL#no#6 -->


// for userEnrollEncMS.fdf and userEnrollEncNS.fdf
<!-- VSSKBEGINPOLICYVAL#no#7 -->
CONST     originator           VeriSign OnSite
<!-- VSSKENDPOLICYVAL#no#7 -->


<!-- VSSKBEGINPOLICYVAL#no#8 -->
<!-- VSSKENDPOLICYVAL#no#8 -->

<!-- VSSKBEGINPOLICYVAL#no#9 -->
   CONST        vsenroll_url    %%::crsUrl%%
<!-- VSSKENDPOLICYVAL#no#9 -->

// for the renewal page, login page for WAC.
<!-- VSSKBEGINPOLICYVAL#no#10 -->
            Dim EnrollPage
            EnrollPage= "userEnrollMS.htm"
<!-- VSSKENDPOLICYVAL#no#10 -->

// for the renewal page, login page for WAC.
<!-- VSSKBEGINPOLICYVAL#no#11 -->
            var EnrollPage = "userEnrollNS.htm";
<!-- VSSKENDPOLICYVAL#no#11 -->


// for the NS login page for WAC.
<!-- VSSKBEGINPOLICYVAL#no#12 -->
<A HREF="../vsprefinst.exe">
<!-- VSSKENDPOLICYVAL#no#12 -->

//-- no remote_host field when key manager is enabled
<!-- VSSKBEGINPOLICYVAL#no#13 -->
<INPUT TYPE="hidden" NAME="remote_host" VALUE="%%::remoteHost%%/cgi-bin/haydn.exe">
<!-- VSSKENDPOLICYVAL#no#13 -->

//-- CSP to be used while importing a PKCS#12
<!-- VSSKBEGINPOLICYVAL#no#14 -->
<!-- VSSKENDPOLICYVAL#no#14 -->

//-- CSP to be used while importing a PKCS#12 for Firefox,PTA, KM install pages 
<!-- VSSKBEGINPOLICYVAL#no#15 -->
<!-- VSSKENDPOLICYVAL#no#15 -->


<!-- VSSKBEGINPOLICYVAL#no#16 -->
var KeyManagerIntegration = 0;
<!-- VSSKENDPOLICYVAL#no#16 -->

<!-- VSSKBEGINPOLICYVAL#no#17 -->
  <!-- VSSKBEGIN Apps/GSE#6 -->
  <!-- VSSKEND Apps/GSE#6 -->
<!-- VSSKENDPOLICYVAL#no#17 -->

<!-- VSSKBEGINPOLICYVAL#no#18 -->
  <!-- VSSKBEGIN Apps/GSE#7 -->
  <!-- VSSKEND Apps/GSE#7 -->
<!-- VSSKENDPOLICYVAL#no#18 -->

<!-- VSSKBEGINPOLICYVAL#no#19 -->
  <!-- VSSKBEGIN Apps/GSE#8 -->
  <!-- VSSKEND Apps/GSE#8 -->
<!-- VSSKENDPOLICYVAL#no#19 -->

<!-- VSSKBEGINPOLICYVAL#no#20 -->
CONST       originator                  VeriSign OnSite
<!-- VSSKENDPOLICYVAL#no#20 -->

// for the NS login page for WAC.
<!-- VSSKBEGINPOLICYVAL#no#101 -->
  <A HREF="../vsptainst.exe">
<!-- VSSKENDPOLICYVAL#no#101 -->

<!-- VSSKBEGINPOLICYVAL#no#21 -->
  <!-- VSSKBEGIN Apps/GSE#50 -->
  <!-- VSSKEND Apps/GSE#50 -->
<!-- VSSKENDPOLICYVAL#no#21 -->

<!-- VSSKBEGINPOLICYVAL#no#22 -->
<!-- VSSKENDPOLICYVAL#no#22 -->

<!-- VSSKBEGINPOLICYVAL#no#23 -->

<Script Language="JavaScript">
<!--



    document.write("<TR>");
    document.write("<TD WIDTH=50 ALIGN=left VALIGN=top>");

//-- VSSKBEGIN Apps/PersonalTrustService#18 --
//-- VSSKEND Apps/PersonalTrustService#18 --

    document.write("<IMG SRC=\"graphics/icon_renew.gif\" border=0 WIDTH=40 HEIGHT=40 ALIGN=LEFT></A>"); 
    document.write("</TD>");
    document.write("<TD WIDTH=538 ALIGN=left VALIGN=top>");

//-- VSSKBEGIN Apps/PersonalTrustService#18 --
//-- VSSKEND Apps/PersonalTrustService#18 --

    document.write("<FONT FACE=\"verdana, arial, helvetica\" SIZE=5><B>RENEW</B></FONT></A><BR>");
    document.write("<FONT FACE=\"arial, helvetica\" SIZE=2>Choose this option to renew a Digital ID which is expiring or which has already expired. You should generally start renewing your Digital ID at least one month before your Digital ID is due to expire.</FONT>");
    document.write("<P>");
    document.write("</TD>");
    document.write("</TR>");

//-->
</script>

<!-- VSSKENDPOLICYVAL#no#23 -->

<!-- VSSKBEGINPOLICYVAL#no#24 -->
<!-- VSSKENDPOLICYVAL#no#24 -->

// for userRenewalEncNS.htm
<!-- VSSKBEGINPOLICYVAL#no#25 -->
<!-- VSSKENDPOLICYVAL#no#25 -->
