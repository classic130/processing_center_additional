<!-- VSSKBEGINPOLICYVAL#native#1 -->
<!-- VSSKBEGIN Global/Mode#19 -->
<!-- VSSKEND Global/Mode#19 -->
<!-- VSSKENDPOLICYVAL#native#1 -->


<!-- VSSKBEGINPOLICYVAL#native#2 -->
<SCRIPT LANGUAGE="VBScript">
<!--
  '-- VSSKBEGIN Renewal/CSP#3 --
  '-- VSSKEND Renewal/CSP#3 --

Function CreateP10( keyflags )
 On Error Resume Next
 CreateP10 = ""

 spnCertEnroll.innerHTML="<OBJECT id='g_objClassFactory' CLASSID='clsid:884e2049-217d-11da-b2a4-000e7bbb2b09'></OBJECT>"

'-- VSSKBEGIN Renewal/KeyLength#1 --
'-- VSSKEND Renewal/KeyLength#1 --
End Function

  Sub DoKeyGen
    dim theForm 
    dim options
    dim keyflags
    dim cryptoProvName
    dim cryptoProvType

    keyflags=0
    set theForm = document.theform
    'theForm.submit.disabled = true
    ' VSSKTEST - commented out for testing purposes...the document is not submitted 
    ' to the server.

    '-- VSSKBEGIN Renewal/CSP#2 --
    '-- VSSKEND Renewal/CSP#2 --

    If isRunningOnVista = 0 Then
    cenroll.HashAlgorithm = "MD5"
    cenroll.KeySpec = 1
    End If

    '-- VSSKBEGIN Renewal/KeyProtect#2 --
    '-- VSSKEND Renewal/KeyProtect#2 --

    '-- VSSKBEGIN Renewal/KeyExportable#1 --
    '-- VSSKEND Renewal/KeyExportable#1 --

    theForm.public_key.value = CreateP10(keyflags)
    if Len(theForm.public_key.value) = 0 then
      MsgBox("The error: " + hex(err.number) + " occured in generating certificate request")
        window.navigate("../error/MSkeygenerr.htm")
    end if
  End Sub
'-->
</SCRIPT>
<!-- VSSKENDPOLICYVAL#native#2 -->



<!-- VSSKBEGINPOLICYVAL#native#3 -->
<!-- VSSKBEGIN Renewal/CSP#1 -->
<!--VSSKEND Renewal/CSP#1 -->

<P><BR><P>

<!-- VSSKBEGIN Renewal/KeyProtect#1 -->
<!-- VSSKEND Renewal/KeyProtect#1 -->

<!-- VSSKBEGIN Renewal/CertPublish#1 -->
<!-- VSSKEND Renewal/CertPublish#1 -->
<!-- VSSKENDPOLICYVAL#native#3 -->


<!-- VSSKBEGINPOLICYVAL#native#4#1.0.0.2 -->
<SCRIPT LANGUAGE="VBScript">
<!--
  Sub InstallCert

    spnCertEnroll.innerHTML="<OBJECT id='g_objClassFactory' CLASSID='clsid:884e2049-217d-11da-b2a4-000e7bbb2b09'></OBJECT>"

    Dim sz10
    sz10 = CertChain
    If isRunningOnVista = 0 Then
    On Error Resume Next
    cenroll.DeleteRequestCert = FALSE
    err.clear
    cenroll.WriteCertToCSP = true
    cenroll.acceptPKCS7(sz10)
    if err.number <> 0 then
        cenroll.WriteCertToCSP = false
        err.clear
        cenroll.acceptPKCS7(sz10)
        if err.number <> 0 then
	     Call StopIt()
             window.navigate ("../VSApps/error/msinserr.htm")
             exit sub
        end if
    end if
    Else
        'MsgBox "Called InstallCert on Vista"
        const contextUser = 1
        const contextMachine = 2
        const CRYPT_STRING_BASE64 = 1
        const CRYPT_STRING_BASE64_ANY = 6
    
        dim objEnroll
        set objEnroll = g_objClassFactory.CreateObject("X509Enrollment.CX509Enrollment")
        objEnroll.Initialize(contextUser)
    
        call objEnroll.InstallResponse(0, CertChain, CRYPT_STRING_BASE64, "")
        If ( err.number <> 0 ) then
            window.navigate ( "../VSApps/error/msinsvistaerr.htm" )
        End If
    End If
  '-- VSSKBEGIN Apps/GSE#62 --
  '-- VSSKEND Apps/GSE#62 --

  End Sub
'-->
</SCRIPT>
<!-- VSSKENDPOLICYVAL#native#4 -->

<!-- VSSKBEGINPOLICYVAL#native#5 -->
<!-- VSSKENDPOLICYVAL#native#5 -->

<!-- VSSKBEGINPOLICYVAL#native#6 -->
<!-- VSSKENDPOLICYVAL#native#6 -->

<!-- VSSKBEGINPOLICYVAL#native#7 -->
<!-- VSSKENDPOLICYVAL#native#7 -->

<!-- VSSKBEGINPOLICYVAL#native#8 -->
<INPUT TYPE=hidden NAME=getMethod VALUE="renewalID">
<!-- VSSKENDPOLICYVAL#native#8 -->

<!-- VSSKBEGINPOLICYVAL#native#9 -->
      document.Renewal.submit();
<!-- VSSKENDPOLICYVAL#native#9 -->


<!-- VSSKBEGINPOLICYVAL#native#10 -->
<TABLE WIDTH=588 BGCOLOR="ffffcc" CELLPADDING=7 CELLSPACING=0 BORDER=0>
<TR>
    <TD WIDTH=588>
<FONT SIZE=2 FACE="verdana, arial, helvetica"><B>Challenge Phrase</B></FONT><BR>
<FONT FACE="arial, helvetica" SIZE=2>This is a unique phrase you chose at the time of
 the original enrollment for the Digital ID.  It
    protects you against unauthorized action on your Digital ID and should not be shared with anyone. Do not lose it! It is required to
    revoke, replace, or renew  your Digital ID.<BR></FONT>
<P>
<CENTER>
    <!--BEGIN INPUT FIELD TABLE-->
    <TABLE WIDTH=574 CELLPADDING=3 CELLSPACING=2 BORDER=0>

    <TR>
        <TD WIDTH=50% BGCOLOR="ffcc00"><FONT FACE="verdana, arial, helvetica" SIZE=2>
<B>Enter Challenge Phrase:</B><BR>
            </FONT><FONT SIZE=2 FACE="arial, helvetica">Do not use any punctuation.<BR></FONT></TD>
        <TD COLSPAN=2 WIDTH=50% BGCOLOR="ffcc00"><IMG SRC="../graphics/blank2.gif" width=27 height=27"  NAME="imgchallenge">&nbsp;&nbsp;&nbsp;
        <INPUT NAME="challenge" VALUE=""  TYPE="PASSWORD" SIZE="20" MAXLENGTH="32"></TD>

    </TR>
    </TABLE>
<!--END INPUT FIELD TABLE-->
</TD>
</TR>
</TABLE>
<!--END TABLE ONE-->

<P><BR><P>


<!--BEGIN TABLE TWO-->

<TABLE WIDTH=588 BGCOLOR="ffffcc" CELLPADDING=7 CELLSPACING=0 BORDER=0>
<TR>
    <TD WIDTH=588>
<FONT SIZE=2 FACE="verdana, arial, helvetica"><B>Renewal PIN</B></FONT><BR>
<FONT FACE="arial, helvetica" SIZE=2>The Personal Identification Number (PIN) is needed to complete this step. It was contained in an
 e-mail message that notified you of the need to renew your Digital ID.  This was sent by the Digital ID Center. Copy (Ctrl + C) the PIN number from
 the e-mail, then paste (Ctrl + V) it into the box below.<BR></FONT>
<P>
<CENTER>
    <!--BEGIN INPUT FIELD TABLE-->
    <TABLE WIDTH=574 CELLPADDING=3 CELLSPACING=2 BORDER=0>

    <TR>
        <TD WIDTH=50% BGCOLOR="ffcc00"><FONT FACE="verdana, arial, helvetica" SIZE=2>
<B>Enter PIN:</B><BR></TD>
        <TD COLSPAN=2 WIDTH=50% BGCOLOR="ffcc00"><IMG SRC="../graphics/blank2.gif" width=27 height=27"  NAME="imgsecretCode">&nbsp;&nbsp;&nbsp;
        <INPUT NAME="secretCode" VALUE=""  TYPE="text" SIZE="20" MAXLENGTH="32"></TD>

    </TR>
    </TABLE>
<!--END INPUT FIELD TABLE-->
</TD>
</TR>
</TABLE>
<!--END TABLE TWO-->

<P><BR><P>

<!--BEGIN TABLE THREE-->
<TABLE WIDTH=588 BGCOLOR="ffffcc" CELLPADDING=7 CELLSPACING=0 BORDER=0>
<TR>
    <TD WIDTH=588>
<FONT SIZE=2 FACE="verdana, arial, helvetica"><B>Optional: Choose Your Encryption Strength</B></FONT><BR>
<FONT FACE="arial, helvetica" SIZE=2>The encryption strength indicated below is the maximum allowed by your browser software.
    We recommend that you leave this as it is.
                <BR></FONT>
<P>
<CENTER>
    <!--BEGIN INPUT FIELD TABLE-->
    <TABLE WIDTH=574 CELLPADDING=3 CELLSPACING=2 BORDER=0>

    <TR>
        <TD WIDTH=50% BGCOLOR="ffcc00">&nbsp;</TD>
        <TD COLSPAN=2 WIDTH=50% BGCOLOR="ffcc00"><IMG SRC="../graphics/blank2.gif" width=27 height=27">&nbsp;&nbsp;&nbsp;
        <KEYGEN TYPE="hidden" NAME="public_key" VALUE=""></TD>

    </TR>
    </TABLE>
<!--END INPUT FIELD TABLE-->
</TD>
</TR>
</TABLE>
<!--END TABLE THREE-->
<P>
<!-- VSSKENDPOLICYVAL#native#10 -->

<!-- VSSKBEGINPOLICYVAL#native#11 -->
<!-- VSSKENDPOLICYVAL#native#11 -->

<!-- VSSKBEGINPOLICYVAL#native#12 -->
<!-- VSSKENDPOLICYVAL#native#12 -->

<!-- VSSKBEGINPOLICYVAL#native#13 -->
<!-- VSSKENDPOLICYVAL#native#13 -->

// for userRenewalSignNS.fdf
<!-- VSSKBEGINPOLICYVAL#native#14 -->
STATUS		0		VSApps/client/userInstallNS.htm
STATUS		6FFF		VSApps/client/userInstallNS.htm
<!-- VSSKENDPOLICYVAL#native#14 -->

// for userRenewalEncNS.fdf
<!-- VSSKBEGINPOLICYVAL#native#15 -->
STATUS		   0		VSApps/client/userInstallEncNS.htm
STATUS		6FFF		VSApps/client/userInstallEncNS.htm
<!-- VSSKENDPOLICYVAL#native#15 -->

<!-- VSSKBEGINPOLICYVAL#native#16 -->
      document.theform.Accept.disabled = true
<!-- VSSKENDPOLICYVAL#native#16 -->
