
// for the enrollment fdf files
<!-- VSSKBEGINPOLICYVAL#dual#1 --> 
  CONST           version            %%KMVersion%%
<!-- VSSKENDPOLICYVAL#dual#1 -->


<!-- VSSKBEGINPOLICYVAL#dual#2#1.0.0.2 --> 
<TR>
	<TD WIDTH=50 ALIGN=left VALIGN=top>
	<IMG SRC="graphics/action_checkyellow.gif" WIDTH="40" HEIGHT="40" BORDER="0">
	</TD>
	<TD WIDTH=538 ALIGN=left VALIGN=top>
	 <FONT COLOR="#cc0000" FACE="verdana, arial, helvetica" SIZE=5><B>ENROLL...</B><BR>
	 <FONT FACE="verdana, arial, helvetica" SIZE=2>
	 <!--BEGIN BROWSER CHECK TO TAKE USER TO THE APPRPRIATE PAGE-->
	  	&#149;<NOSCRIPT><A HREF="client/enroll.htm"></NOSCRIPT>
               <script Language="JavaScript">
               if ((navigator.appName == "Netscape"))
                 {document.write("<A HREF='client/userEnrollDualNS.htm'>")}
                       else
                    if ( "%%Enrollment/CertStore::policyValue%%" == "verisign" )
                      {document.write("<A HREF='client/userEnrollDualMS.htm'>")}
                    else
			{CheckIESupportedVersion1("<A HREF='client/userEnrollDualMS.htm'>");}
               </script>
               for Encryption and Signing Digital ID</A><BR>
		<!--END BROWSER CHECK TO TAKE USER TO THE APPRPRIATE PAGE-->
		
		<!--userEnrollEncrption.htm IS USED FOR FIREFOX AND MICROSOFT-->
		&#149; <NOSCRIPT><A HREF="client/enroll.htm"></NOSCRIPT>
			  <script Language="JavaScript">
        		if ((navigator.appName == "Netscape"))
              		   {document.write("<A HREF='client/userEnrollEncNS.htm'>")}
               		else 
                            if ( "%%Enrollment/CertStore::policyValue%%" == "verisign" )
                              {document.write("<A HREF='client/userEnrollEncMS.htm'>")}
                          else
                              { CheckIESupportedVersion1("<A HREF='client/userEnrollEncMS.htm'>");}
			</script>
                        for Encryption Digital ID only</A><BR>
		
		<!--BEGIN BROWSER CHECK TO TAKE USER TO THE APPRPRIATE PAGE-->
		&#149;<NOSCRIPT><A HREF="client/enroll.htm"></NOSCRIPT>
			  <script Language="JavaScript">
        		  if ((navigator.appName == "Netscape"))
              		    {document.write("<A HREF='client/userEnrollNS.htm'>")}
               		  else
                            if ( "%%Enrollment/CertStore::policyValue%%" == "verisign" )
                              {document.write("<A HREF='client/userEnrollMS.htm'>")}
                          else
                              { CheckIESupportedVersion1("<A HREF='client/userEnrollMS.htm'>");}
			  </script>
			for Signing Digital ID only</A><BR>
		<!--END BROWSER CHECK TO TAKE USER TO THE APPRPRIATE PAGE-->
	</FONT>

	</TD>
</TR>
<!-- VSSKENDPOLICYVAL#dual#2 -->



<!-- VSSKBEGINPOLICYVAL#dual#3 --> 
<TR>
	<TD WIDTH=50 ALIGN=left VALIGN=top>
	<IMG SRC="graphics/action_arrowyellow.gif" WIDTH=40 HEIGHT=40 BORDER=0 ALT=""></A>
	</TD>
	<TD WIDTH=538 ALIGN=left VALIGN=top>
	 <FONT COLOR="#cc0000" FACE="verdana, arial, helvetica" SIZE=5><B>PICK-UP ID</B></A><BR>
		 <FONT FACE="verdana, arial, helvetica" SIZE=2>
                <!--
	  	&#149;<NOSCRIPT><A HREF="client/retrieve_id.htm"></NOSCRIPT>
			  <script Language="JavaScript">
        		if (navigator.appName == "Netscape")
              		  {document.write("<A HREF='client/userGetDualNS.htm'>")}
               		else
              		  {document.write("<A HREF='client/userGetDualMS.htm'>")}
			</script>
			for Encryption and Signing Digital ID</A><BR>
		-->
		&#149;<NOSCRIPT><A HREF="client/retrieve_id.htm"></NOSCRIPT>
			  <script Language="JavaScript">
        		if (navigator.appName == "Netscape")
              		   {document.write("<A HREF='client/userGetEncNS.htm'>")}
               		else 
              		   {
          			document.write("<A HREF='client/userGetEncMS.htm'>")
                           }
			</script>
			for Encryption Digital ID</A><BR>
		
		&#149;<NOSCRIPT><A HREF="client/retrieve_id.htm"></NOSCRIPT>
			  <script Language="JavaScript">
        		if (navigator.appName == "Netscape")
              		   {document.write("<A HREF='client/nspickup.htm'>")}
               		else
                           {
          			document.write("<A HREF='client/mspickup.htm'>")
                           }
			</script>
			for Signing Digital ID only</A><BR>
	</FONT>
	<P>
	</TD>
</TR>
<!-- VSSKENDPOLICYVAL#dual#3 -->


// for retrieve_id.htm
<!-- VSSKBEGINPOLICYVAL#dual#4 -->
<TABLE WIDTH=588 BGCOLOR="ffffcc" CELLPADDING=2 CELLSPACING=0 BORDER=0>
<TR>
   <TD COLSPAN=2><IMG SRC="../graphics/ie_logo2.gif" ALT="Microsoft" border=0></TD>
   <TD WIDTH=538 ALIGN=left VALIGN=top>
   <FONT FACE="verdana, arial, helvetica" SIZE=4>For Microsoft Internet Explorer</FONT><BR>
   <FONT FACE="verdana, arial, helvetica" SIZE=2>
    <A HREF="userGetEncMS.htm">for Encryption Digital ID</A><BR>
    <a href="mspickup.htm">for Signing Digital ID only</A>
   </FONT>
   </TD>
</TR>
<TR><TD>&nbsp;&nbsp;</TD></TR>
<TR>
   <TD COLSPAN=2><IMG SRC="../graphics/ns_logo.gif" ALT="Firefox" border=0></TD>
   <TD WIDTH=538 ALIGN=left VALIGN=top>
   <FONT FACE="verdana, arial, helvetica" SIZE=4>For Firefox</FONT><BR> 
   <FONT FACE="verdana, arial, helvetica" SIZE=2>
   <!--
   <A HREF=userGetDualNS.htm>for Encryption and Signing Digital ID</A><BR>
   -->
   <A HREF=userGetEncNS.htm>for Encryption Digital ID</A><BR>
   <A HREF=nspickup.htm>for Signing Digital ID only</A>
   </FONT>
   </TD>
</TR>
</TABLE>
<!-- VSSKENDPOLICYVAL#dual#4 -->


// enroll.htm
<!-- VSSKBEGINPOLICYVAL#dual#5 -->
<TABLE WIDTH=588 BGCOLOR="ffffcc" CELLPADDING=2 CELLSPACING=0 BORDER=0>
<TR>
   <TD COLSPAN=2><IMG SRC="../graphics/ie_logo2.gif" ALT="Microsoft" border=0></TD>
   <TD WIDTH=538 ALIGN=left VALIGN=top>
   <FONT FACE="verdana, arial, helvetica" SIZE=4>For Microsoft Internet Explorer</FONT><BR>
   <FONT FACE="verdana, arial, helvetica" SIZE=2>
    <A HREF=userEnrollDualMS.htm>for Encryption and Signing Digital ID</A><BR>
    <A HREF="userEnrollEncMS.htm">for Encryption Digital ID</A><BR>
    <A HREF="userEnrollMS.htm">for Signing Digital ID only</A>
   </FONT>
   </TD>
</TR>
<TR><TD>&nbsp;&nbsp;</TD></TR>
<TR>
   <TD COLSPAN=2><IMG SRC="../graphics/ns_logo.gif" ALT="Firefox" border=0></TD>
   <TD WIDTH=538 ALIGN=left VALIGN=top>
   <FONT FACE="verdana, arial, helvetica" SIZE=4>For Firefox</FONT><BR> 
   <FONT FACE="verdana, arial, helvetica" SIZE=2>
   <A HREF=userEnrollDualNS.htm>for Encryption and Signing Digital ID</A><BR>
   <A HREF=userEnrollEncNS.htm>for Encryption Digital ID</A><BR>
   <A HREF=userEnrollNS.htm>for Signing Digital ID only</A>
   </FONT>
   </TD>
</TR>
</TABLE>
<!-- VSSKENDPOLICYVAL#dual#5 -->


// for userEnrollMS.fdf and userEnrollNS.fdf
<!-- VSSKBEGINPOLICYVAL#dual#6 -->
CONST     originator           VeriSign OnSite Signing
<!-- VSSKENDPOLICYVAL#dual#6 -->


// for userEnrollEnc.fdf 
<!-- VSSKBEGINPOLICYVAL#dual#7 -->
CONST     originator           VeriSign OnSite Encryption
<!-- VSSKENDPOLICYVAL#dual#7 -->

<!-- VSSKBEGINPOLICYVAL#dual#8 -->
<TABLE WIDTH=588 BGCOLOR="ffffcc" CELLPADDING=7 CELLSPACING=0 BORDER=0>
<TR>
<TD WIDTH=588><FONT SIZE=2 FACE="verdana, arial, helvetica">
When you submit this Digital ID application by clicking Accept, your browser
will generate the public and private keys for your Signing Digital ID.
The browser will also prompt you to set 
up a password to protect your private key if you have chosen additional 
protection for your private key in Step 5 above.  Your 
private key is a secret file that you will use to digitally sign e-mail. 
Your public key will become part of your Signing Digital ID&#151;your 
associates can use it to verify your digital signature.

<p>
When your Signing Digital ID is ready, you will receive
e-mail that includes instructions for retrieving and installing it.
<P>
</FONT>
</TD>	
</TR>
</TABLE>
<!-- VSSKENDPOLICYVAL#dual#8 -->

<!-- VSSKBEGINPOLICYVAL#dual#9#1.0.0.1 -->
   CONST        vsenroll_url    %%::crsUrl%%
<!-- VSSKENDPOLICYVAL#dual#9 -->


// for the renewal page, login page for WAC.
<!-- VSSKBEGINPOLICYVAL#dual#10 -->
           Dim EnrollPage
            EnrollPage = "enroll.htm"
<!-- VSSKENDPOLICYVAL#dual#10 -->

// for the renewal page, login page for WAC.
<!-- VSSKBEGINPOLICYVAL#dual#11 -->
           var EnrollPage = "enroll.htm";
<!-- VSSKENDPOLICYVAL#dual#11 -->


// for the NS login page for WAC.
<!-- VSSKBEGINPOLICYVAL#dual#12 -->
<A HREF="../vsprefinstkm.exe">
<!-- VSSKENDPOLICYVAL#dual#12 -->

//-- no remote_host field when key manager is enabled
<!-- VSSKBEGINPOLICYVAL#dual#13 -->
<!-- VSSKENDPOLICYVAL#dual#13 -->

//-- CSP to be used while importing a PKCS#12
<!-- VSSKBEGINPOLICYVAL#dual#14#2.0.0.0 -->
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
<!-- VSSKENDPOLICYVAL#dual#14 -->


//-- CSP to be used while importing a PKCS#12 for Firefox,PTA, KM install pages
<!-- VSSKBEGINPOLICYVAL#dual#15 -->
     document.NSCP_IVSPTA.VSImport_set_ProviderName("%%provName%%") ;
     if ( (ErrorCode = document.NSCP_IVSPTA.GetLastError()) != 0)
     {
       SetErrorInfo2("../fdf/VSApps/client/KeyMngrErrors.fdf", "00000002", "NSCP_IVSPTA.VSImport_set_ProviderName", ErrorCode);
       return ;
     }
<!-- VSSKENDPOLICYVAL#dual#15 -->


<!-- VSSKBEGINPOLICYVAL#dual#16 -->
var KeyManagerIntegration = 1;
<!-- VSSKENDPOLICYVAL#dual#16 -->

<!-- VSSKBEGINPOLICYVAL#dual#17 -->
<!-- VSSKENDPOLICYVAL#dual#17 -->

<!-- VSSKBEGINPOLICYVAL#dual#18 -->
<!-- VSSKENDPOLICYVAL#dual#18 -->

<!-- VSSKBEGINPOLICYVAL#dual#19 -->
<!-- VSSKENDPOLICYVAL#dual#19 -->

<!-- VSSKBEGINPOLICYVAL#dual#20 -->
originator	TEXT	MANDATORY	NONE		NONE
kr_refnum	TEXT	OPTIONAL	NONE		NONE
<!-- VSSKENDPOLICYVAL#dual#20 -->  

<!-- VSSKBEGINPOLICYVAL#dual#21 -->
<!-- VSSKENDPOLICYVAL#dual#21 -->

// for the NS login page for WAC.
<!-- VSSKBEGINPOLICYVAL#dual#101 -->
<A HREF="../vsptainstkm.exe">
<!-- VSSKENDPOLICYVAL#dual#101 --> 

<!-- VSSKBEGINPOLICYVAL#dual#22 -->
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
<!-- VSSKENDPOLICYVAL#dual#22 -->

<!-- VSSKBEGINPOLICYVAL#dual#23 --> 

<Script Language="JavaScript">



    document.write("<TR>");
    document.write("<TD WIDTH=50 ALIGN=left VALIGN=top>");

    document.write("<IMG SRC=\"graphics/icon_renew.gif\" border=0 WIDTH=40 HEIGHT=40 ALIGN=LEFT><BR>");
    document.write("</TD>");
    document.write("<TD WIDTH=538 ALIGN=left VALIGN=top>");
    document.write("<FONT COLOR=\"#cc0000\" FACE=\"verdana, arial, helvetica\" SIZE=5><B>RENEW</B></A><BR>");
    document.write("<FONT COLOR=\"#000000\" FACE=\"arial, helvetica\" SIZE=2>Choose this option to renew a Digital ID which is expiring or which has already expired. You should generally start renewing your Digital ID at least one month before your Digital ID is due to expire.</FONT><BR>");

    document.write("<FONT FACE=\"verdana, arial, helvetica\" SIZE=2>&#149;");

//-- VSSKBEGIN Apps/PersonalTrustService#25 --
//-- VSSKEND Apps/PersonalTrustService#25 --

    document.write("for Encryption Digital ID</A><BR>&#149;");

//-- VSSKBEGIN Apps/PersonalTrustService#26 --
//-- VSSKEND Apps/PersonalTrustService#26 --

    document.write("for Signing Digital ID only</A><BR>");
    document.write("</FONT>");

    document.write("<P>");
    document.write("</TD>");
    document.write("</TR>");

</script>

<!-- VSSKENDPOLICYVAL#dual#23 -->

<!-- VSSKBEGINPOLICYVAL#dual#24 -->
  KeyUsage = "dual"
<!-- VSSKENDPOLICYVAL#dual#24 -->

// for userRenewalEncNS.htm
<!-- VSSKBEGINPOLICYVAL#dual#25 -->
  KeyUsage = "dual";
<!-- VSSKENDPOLICYVAL#dual#25 -->
