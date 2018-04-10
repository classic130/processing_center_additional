
// for the enrollment fdf files
<!-- VSSKBEGINPOLICYVAL#single#1 --> 
  CONST           version            %%KMVersion%%
<!-- VSSKENDPOLICYVAL#single#1 -->


<!-- VSSKBEGINPOLICYVAL#single#2 --> 
<TR>
	<TD WIDTH=50 ALIGN=left VALIGN=top>
        <NOSCRIPT><A HREF="client/enroll.htm"></NOSCRIPT>
        <script Language="JavaScript">
        if (navigator.appName == "Netscape") 
          {document.write("<A HREF='client/userEnrollEncNS.htm'>")}
	else
          if ( "%%Enrollment/CertStore::policyValue%%" == "verisign" )
             {document.write("<A HREF='client/userEnrollEncMS.htm'>")}
          else
             { CheckIESupportedVersion1("<A HREF='client/userEnrollEncMS.htm'>");}
        </script>
	<IMG SRC="graphics/action_checkyellow.gif" WIDTH="40" HEIGHT="40" BORDER="0"></A>
	</TD>
	<TD WIDTH=538 ALIGN=left VALIGN=top>
        <NOSCRIPT><A HREF="client/enroll.htm"></NOSCRIPT>
        <script Language="JavaScript">
        if (navigator.appName == "Netscape") 
          {document.write("<A HREF='client/userEnrollEncNS.htm'>")}
	else
          if ( "%%Enrollment/CertStore::policyValue%%" == "verisign" )
             {document.write("<A HREF='client/userEnrollEncMS.htm'>")}
          else
             { CheckIESupportedVersion1("<A HREF='client/userEnrollEncMS.htm'>");}
        </script>
	<FONT FACE="verdana, arial, helvetica" SIZE=5><B>ENROLL</B></FONT></A><BR>
	<FONT FACE="arial, helvetica" SIZE=2>Choose this option to enroll for a Digital ID.</FONT>
	<P>
	</TD>
</TR>
<!-- VSSKENDPOLICYVAL#single#2 -->



<!-- VSSKBEGINPOLICYVAL#single#3 --> 
<TR>
	<TD WIDTH=50 ALIGN=left VALIGN=top>
        <NOSCRIPT><A HREF="client/retrieve_id.htm"></NOSCRIPT>
        <script Language="JavaScript">
        if (navigator.appName == "Netscape") 
          {document.write("<A HREF='client/userGetEncNS.htm'>")}
	else
	  {document.write("<A HREF='client/userGetEncMS.htm'>")}
        </script>
	<IMG SRC="graphics/action_arrowyellow.gif" WIDTH=40 HEIGHT=40 BORDER=0 ALT=""></A>
	<P>
	</TD>
        <TD WIDTH=538 ALIGN=left VALIGN=top>
        <NOSCRIPT><A HREF="client/retrieve_id.htm"></NOSCRIPT>
        <script Language="JavaScript">
        if (navigator.appName == "Netscape") 
          {document.write("<A HREF='client/userGetEncNS.htm'>")}
	else
          {document.write("<A HREF='client/userGetEncMS.htm'>")}
        </script>
	<FONT FACE="verdana, arial, helvetica" SIZE=5><B>PICK-UP ID</B></FONT></A><BR>
	<FONT FACE="arial, helvetica" SIZE=2>Choose this option if you have enrolled for a Digital ID but have not picked it up.</FONT>
	<P>
	</TD>
</TR>
<!-- VSSKENDPOLICYVAL#single#3 -->


<!-- VSSKBEGINPOLICYVAL#single#4 -->
<TABLE WIDTH=588 BGCOLOR="ffffcc" CELLPADDING=2 CELLSPACING=0 BORDER=0>
<TR>
	<TD COLSPAN=2><IMG SRC="../graphics/ie_logo2.gif" ALT="Microsoft" border=0><A HREF="userGetEncMS.htm">
	<FONT FACE="verdana, arial, helvetica" SIZE=4>For Microsoft Internet Explorer</A><BR><BR></TD> 
</TR>
<TR>
	<TD COLSPAN=2><IMG SRC="../graphics/ns_logo.gif" ALT="Firefox" border=0><a href="userGetEncNS.htm">
	<FONT FACE="verdana, arial, helvetica" SIZE=4>For Firefox<BR><BR></A></TD> 
</TR>
</TABLE>
<!-- VSSKENDPOLICYVAL#single#4 -->


<!-- VSSKBEGINPOLICYVAL#single#5 -->
<TABLE WIDTH=588 BGCOLOR="ffffcc" CELLPADDING=2 CELLSPACING=0 BORDER=0>
<TR>
	<TD COLSPAN=2><IMG SRC="../graphics/ie_logo2.gif" ALT="Microsoft" border=0><A HREF="userEnrollEncMS.htm">
	<FONT FACE="verdana, arial, helvetica" SIZE=4>For Microsoft Internet Explorer</A><BR><BR></TD> 
</TR>
<TR>
	<TD COLSPAN=2><IMG SRC="../graphics/ns_logo.gif" ALT="Firefox" border=0><a href="userEnrollEncNS.htm">
	<FONT FACE="verdana, arial, helvetica" SIZE=4>For Firefox<BR><BR></A></TD> 
</TR>
</TABLE>
<!-- VSSKENDPOLICYVAL#single#5 -->


// for userEnrollMS.fdf and userEnrollNS.fdf
<!-- VSSKBEGINPOLICYVAL#single#6 -->
CONST     originator           VeriSign OnSite
<!-- VSSKENDPOLICYVAL#single#6 -->


// for userEnrollEnc.fdf 
<!-- VSSKBEGINPOLICYVAL#single#7 -->
CONST     originator           VeriSign OnSite OneKey
<!-- VSSKENDPOLICYVAL#single#7 -->



<!-- VSSKBEGINPOLICYVAL#single#8 --> 
<!-- VSSKENDPOLICYVAL#single#8 -->


<!-- VSSKBEGINPOLICYVAL#single#9#1.0.0.1 -->
   CONST        vsenroll_url    %%::crsUrl%%
<!-- VSSKENDPOLICYVAL#single#9 -->

// for the renewal page, login page for WAC.
<!-- VSSKBEGINPOLICYVAL#single#10 -->
            Dim EnrollPage
            EnrollPage= "userEnrollEncMS.htm"
<!-- VSSKENDPOLICYVAL#single#10 -->


// for the renewal page, login page for WAC.
<!-- VSSKBEGINPOLICYVAL#single#11 -->
      var EnrollPage = "userEnrollEncNS.htm";
<!-- VSSKENDPOLICYVAL#single#11 -->


// for the NS login page for WAC.
<!-- VSSKBEGINPOLICYVAL#single#12 -->
<A HREF="../vsprefinstkm.exe">
<!-- VSSKENDPOLICYVAL#single#12 -->

//-- no remote_host field when key manager is enabled
<!-- VSSKBEGINPOLICYVAL#single#13 -->
<!-- VSSKENDPOLICYVAL#single#13 -->

//-- CSP to be used while importing a PKCS#12
<!-- VSSKBEGINPOLICYVAL#single#14#2.0.0.0 -->
	On Error Resume Next
	Import.ProviderName = "%%provName%%"
	If err.number <> 0 Then
	  Select Case CStr(Hex(err.number))
	  Case "1B6"
		Call SetErrorInfo2("../fdf/VSApps/client/ExchangeErrors.fdf", "00000036", CStr(Hex(err.number)),"Certificate Import Status")  
	       	exit Sub	
          Case else
	          Call SetErrorInfo2("../fdf/VSApps/client/KeyMngrErrors.fdf", 00000001, CStr(Hex(err.number)), "Certificate Import Status")
               Exit Sub
	  End Select
	End If
<!-- VSSKENDPOLICYVAL#single#14 -->


//-- CSP to be used while importing a PKCS#12 for Firefox,PTA, KM install pages 
<!-- VSSKBEGINPOLICYVAL#single#15 -->
     document.NSCP_IVSPTA.VSImport_set_ProviderName("%%provName%%") ;
     if ( (ErrorCode = document.NSCP_IVSPTA.GetLastError()) != 0)
     {
       SetErrorInfo2("../fdf/VSApps/client/KeyMngrErrors.fdf", "00000002", "Digital ID Install::NSCP_IVSPTA.VSImport_set_ProviderName", ErrorCode);
       return ;
     }
<!-- VSSKENDPOLICYVAL#single#15 -->

<!-- VSSKBEGINPOLICYVAL#single#16 -->
var KeyManagerIntegration = 1;
<!-- VSSKENDPOLICYVAL#single#16 -->

<!-- VSSKBEGINPOLICYVAL#single#17 -->
<!-- VSSKENDPOLICYVAL#single#17 -->

<!-- VSSKBEGINPOLICYVAL#single#18 -->
<!-- VSSKENDPOLICYVAL#single#18 -->

<!-- VSSKBEGINPOLICYVAL#single#19 -->
<!-- VSSKENDPOLICYVAL#single#19 -->

<!-- VSSKBEGINPOLICYVAL#single#20 -->
originator      TEXT    MANDATORY       NONE            NONE
kr_refnum	TEXT	OPTIONAL	NONE		NONE
<!-- VSSKENDPOLICYVAL#single#20 -->

// for the NS login page for WAC.
<!-- VSSKBEGINPOLICYVAL#single#101 -->
  <A HREF="../vsptainstkm.exe">
<!-- VSSKENDPOLICYVAL#single#101 -->
 
<!-- VSSKBEGINPOLICYVAL#single#21 -->
<!-- VSSKENDPOLICYVAL#single#21 -->


<!-- VSSKBEGINPOLICYVAL#single#22 -->
<TR>
	<TD WIDTH=50 ALIGN=left VALIGN=top>
        <Script Language="JavaScript">
        <!-- 
        if (navigator.appName == "Netscape")
           {document.write("<A HREF='client/importP12NS.htm'>")}
        else
           {document.write("<A HREF='client/importP12MS.htm'>")}
        //-->
        </Script>
	<IMG SRC="graphics/action_arrowyellow.gif" border=0 WIDTH=40 HEIGHT=40 ALIGN=LEFT></A>
	</TD>
	<TD WIDTH=538 ALIGN=left VALIGN=top>
        <Script Language="JavaScript">
        <!-- 
        if (navigator.appName == "Netscape")
           {document.write("<A HREF='client/importP12NS.htm'>")}
        else
           {document.write("<A HREF='client/importP12MS.htm'>")}
        //-->
        </Script>
	<FONT FACE="verdana, arial, helvetica" SIZE=4><B>PTA KEY RECOVERY</B></FONT></A><BR>
	<FONT FACE="arial, helvetica" SIZE=2>Choose this option to recover your keys. Before doing this operation you need to get a Recovered Key File from your administrator.
	</FONT>
	<P>
	</TD>
</TR>
<!-- VSSKENDPOLICYVAL#single#22 -->

<!-- VSSKBEGINPOLICYVAL#single#23 --> 

<Script Language="JavaScript">




    document.write("<TR>");
    document.write("<TD WIDTH=50 ALIGN=left VALIGN=top>");

//-- VSSKBEGIN Apps/PersonalTrustService#25 --
//-- VSSKEND Apps/PersonalTrustService#25 --

    document.write("<IMG SRC=\"graphics/icon_renew.gif\" border=0 WIDTH=40 HEIGHT=40 ALIGN=LEFT></A>");
    document.write("</TD>");
    document.write("<TD WIDTH=538 ALIGN=left VALIGN=top>");

//-- VSSKBEGIN Apps/PersonalTrustService#25 --
//-- VSSKEND Apps/PersonalTrustService#25 --

    document.write("<FONT FACE=\"verdana, arial, helvetica\" SIZE=5><B>RENEW</B></FONT></A><BR>");
    document.write("<FONT FACE=\"arial, helvetica\" SIZE=2>Choose this option to renew a Digital ID which is expiring or which has already expired. You should generally start renewing your Digital ID at least one month before your Digital ID is due to expire.</FONT>");

    document.write("<P>");
    document.write("</TD>");
    document.write("</TR>");

</script>

<!-- VSSKENDPOLICYVAL#single#23 -->

<!-- VSSKBEGINPOLICYVAL#single#24 -->
  KeyUsage = "single"
<!-- VSSKENDPOLICYVAL#single#24 -->

// for userRenewalEncNS.htm
<!-- VSSKBEGINPOLICYVAL#single#25 -->
  KeyUsage = "single";
<!-- VSSKENDPOLICYVAL#single#25 -->
