<!-- VSSKBEGINPOLICYVAL#yes#1 -->
<P><BR><P>
<TABLE WIDTH=588 BGCOLOR="ffffcc" CELLPADDING=7 CELLSPACING=0 BORDER=0>
<TR>
<TD WIDTH=588>
<FONT SIZE=2 FACE="verdana, arial, helvetica"><B>Information detected from Microsoft Exchange</B></FONT><BR><P>
<CENTER>
<TABLE WIDTH=574 CELLPADDING=3 CELLSPACING=2 BORDER=0>
<TR>
  <TD WIDTH=50% BGCOLOR="FFCC00">
    <FONT FACE="verdana, arial, helvetica" SIZE=2>
    <B>Full Name: </B>
    </FONT>
  </TD>
  <TD COLSPAN=2 WIDTH=50% BGCOLOR="FFCC00">
    <IMG SRC="../graphics/blank2.gif" WIDTH=27 HEIGHT=27>&nbsp;&nbsp;&nbsp;
    <FONT FACE="verdana, arial, helvetica" SIZE=2>
    <SCRIPT LANGUAGE="VBScript">
      document.write "<b>"
      document.write directoryFullName
      document.write "</b>"
    </SCRIPT>
    </FONT>
  </TD>
</TR>
<TR>
  <TD WIDTH=50% BGCOLOR="FFCC00">
    <FONT FACE="verdana, arial, helvetica" SIZE=2>
    <B>Email Address: </B>
  </TD>
  <TD COLSPAN=2 WIDTH=50% BGCOLOR="FFCC00">
    <IMG SRC="../graphics/blank2.gif" WIDTH=27 HEIGHT=27>&nbsp;&nbsp;&nbsp;
    <FONT FACE="verdana, arial, helvetica" SIZE=2>
    <SCRIPT LANGUAGE="VBScript">
      document.write "<b>"
      document.write directoryRfc822Mailbox
      document.write "</b>"
    </SCRIPT>
    </FONT>
  </TD>
</TR>
</TABLE>
<!--END INPUT FIELD TABLE-->
</TD>
</TR>
</TABLE>
<!-- VSSKENDPOLICYVAL#yes#1 -->

<!-- VSSKBEGINPOLICYVAL#yes#2 -->
<Script Language="VBScript">
<!--
  Dim rfc822Mailbox, Alias, firstName, lastName, Trunc, companyName, certDN
  rfc822Mailbox = ""
  Alias = ""

  Sub SetVars

    fullName = directoryFullName

    if fullName = "" Then
      window.location = "../../cgi-bin/softbounce.exe?form_file=../fdf/VSApps/client/ExchangeErrors.fdf&errorCode=00000001&operation=Enrollment Status&showError="
    end if

    distinguishedName = directoryDN

    if distinguishedName = "" Then
      window.location = "../../cgi-bin/softbounce.exe?form_file=../fdf/VSApps/client/ExchangeErrors.fdf&errorCode=00000002&operation=Enrollment Status&showError="
    end if

    countStartOfAlias = InStr(distinguishedName, "=")
    stringAliasStart = Mid(distinguishedName, countStartOfAlias+1)
    sizeOfAlias = InStr(stringAliasStart, ",")
    sizeOfAlias = sizeOfAlias - 1
    Alias = Left(stringAliasStart, sizeOfAlias)

    rfc822Mailbox = directoryRfc822Mailbox

    if rfc822Mailbox= "" Then
      window.location = "../../cgi-bin/softbounce.exe?form_file=../fdf/VSApps/client/ExchangeErrors.fdf&errorCode=00000003&operation=Enrollment Status&showError="
    end if

    companyName = ", %%::corpName%%"
    Trunc = Mid(Alias & " (" & directoryFullName & companyName, 1, 63)
    Trunc = Trunc & ")"

    document.proform.mail_email.value = rfc822Mailbox
    document.proform.common_name.value = Trunc
    document.proform.exchange_alias.value = Alias
    document.proform.exchange_userName.value = directoryFullName
    document.proform.exchange_DN.value = directoryDN 
    
    certDN=Mid(directoryDN, InStr(directoryDN, ",")+1)
    'certDN= "cn=" & Chr(34) & Trunc & Chr(34) & "," & certDN
    '-- VSSKBEGIN Global/Mode#32 --
    '-- VSSKEND Global/Mode#32 --
    document.proform.cert_DN.value = certDN
  End Sub
'-->
</Script>
<!-- VSSKENDPOLICYVAL#yes#2 -->

<!-- VSSKBEGINPOLICYVAL#yes#3 -->
  <SCRIPT LANGUAGE="VBScript">
    Call ShowMBI
  </SCRIPT>
<!-- VSSKENDPOLICYVAL#yes#3 -->


<!-- VSSKBEGINPOLICYVAL#yes#4 -->
<!-- these are exchange integration specific variables -->
<input type=hidden name=exchange_alias value="">
<input type=hidden name=exchange_userName value="">
<input type=hidden name=common_name value="">
<input type=hidden name=san_common_name value="">
<input type=hidden name=exchange_DN value="">
<input type=hidden name=ldap_DN value="">
<input type=hidden name=exchange_ServerName value="">
<input type=hidden name=exch_Srvr value="">
<input type=hidden name=exchange_ProfileName value="">
<input type=hidden name=exchange_Version value="">
<input type=hidden name=exchange_VerString value="">
<input type=hidden name=cert_DN value="">
<input type=hidden name=win2k_upn value="">
<input type=hidden name=win2k_efs_eku value="">
<!-- VSSKENDPOLICYVAL#yes#4 -->


<!-- VSSKBEGINPOLICYVAL#yes#5 -->
<Script Language="VBScript">
<!--
Dim directoryDN, directoryFullName, directoryRfc822Mailbox
directoryDN="cn=SBajaj,cn=Recipients,ou=HQ,o=VERISIGN"
directoryFullName="Siddharth Bajaj"
directoryRfc822Mailbox="SBajaj@verisign.com"
'-->
</script>
<!-- VSSKENDPOLICYVAL#yes#5 -->

<-- The SignAtrb (vssgnatb) control -->
<!-- VSSKBEGINPOLICYVAL#yes#6 -->
  <!-- VSSKBEGIN Global/Mode#106 -->
  <!-- VSSKEND Global/Mode#106 -->
<!-- VSSKENDPOLICYVAL#yes#6 -->

<!-- VSSKBEGINPOLICYVAL#yes#7#2.0.0.1 -->
<Script Language="VBScript">
<!--
   Dim exchangeDN, encUserCertificate, encUserSMIMECertificate
   Dim exchangeServerName,exchangeProfileName,ExchangeVer
   Dim DirUpdate,UseAuthUpdate,UseCRLDP
   Dim Outlook2002Flag
   Outlook2002Flag = FALSE

Sub SignExchange

  '-- VSSKBEGIN Global/System#17 --
  '-- VSSKEND Global/System#17 --

   'exchangeDN = "$$exchange_DN$$"
   exchangeDN = "$#exchange_DN#$" 	
   exchangeServerName = "$$exchange_ServerName$$"
   exchangeProfileName=	"$$exchange_ProfileName$$"	

   ExchangeVer ="$$exchange_Version$$"	

   if ExchangeVer = "" then
	Call SetErrorInfo2("../fdf/VSApps/client/ExchangeErrors.fdf", "00000020", CStr(Hex(err.number)), "Certificate Publish Status")
     exit sub
   end if

   DirUpdate=%%directory_Update%%
   UseAuthUpdate=%%use_AuthUpdate%%
   UseCRLDP=%%use_CRLDP%% 
	
   	 
     On Error Resume Next	
     IGSE.ProfileName=exchangeProfileName 
     If err.number <> 0 Then
	Select Case CStr(Hex(err.number))
		Case "1B6"
			Call SetErrorInfo2("../fdf/VSApps/client/ExchangeErrors.fdf", "00000024", CStr(Hex(err.number)),"Certificate Installation")  
		Exit Sub
		Case else
			Call SetErrorInfo2("../fdf/VSApps/client/ExchangeErrors.fdf", "00000019", CStr(Hex(err.number)),"Certificate Installation")  
		Exit Sub	
	End Select
     End If

     On Error Resume Next	
     IGSE.AddEncryptSignButton
     If err.number <> 0 Then	
		Select Case 	CStr(Hex(err.number))
			Case "1AD"
				MsgBox "Error in customizing Outlook toolbar  " 
	     	   	Case "80008101"
				'MsgBox "Outlook 2002 Word default editor error..."	
				Outlook2002Flag = TRUE
				document.cookie = "VSGSEOutlook2002Cookie=1"
			Case else
				MsgBox "Unable to add encrypt/sign toolbar buttons in the Outlook toolbar." & chr(13) &_
				"Windows Error Code  : 0x" & CStr(Hex(err.number))& chr(13)&_
				"Please press the Ok button to publish your certificate to your mailbox"	
					
		End Select

     End If

     On Error Resume Next	
     if UseCRLDP=1 Then
		IGSE.EnableCRLDistPoint=1	
     else
		IGSE.EnableCRLDistPoint=0
     End IF	

     If err.number <> 0 Then	
	Call SetErrorInfo2("../fdf/VSApps/client/ExchangeErrors.fdf", "0000001A", CStr(Hex(err.number)),"Certificate Installation")  
	Exit Sub	
     End IF	
	
     If DirUpdate=0 Then
	ClientUpdate
     Else
	GetChallengePhrase
     End If		
  '-- VSSKBEGIN Global/System#17 --
  '-- VSSKEND Global/System#17 --



End Sub

Sub ClientUpdate

  '-- VSSKBEGIN Global/System#17 --
  '-- VSSKEND Global/System#17 --
   On Error Resume Next
   IGSE.ExchangeVer = ExchangeVer
   If err.number <> 0 Then
		Select Case CStr(Hex(err.number))
		Case "1B6"
			Call SetErrorInfo2("../fdf/VSApps/client/ExchangeErrors.fdf", "00000024", CStr(Hex(err.number)),"Certificate Status")  
		Exit Sub
		Case else
		     Call SetErrorInfo2("../fdf/VSApps/client/ExchangeErrors.fdf", "00000020", CStr(Hex(err.number)), "Certificate Publish      Status")
     		exit sub
		End Select
   End If
   
   On Error Resume Next
   IGSE.ServerName=exchangeServerName
   If err.number <> 0 Then
     Call SetErrorInfo2("../fdf/VSApps/client/ExchangeErrors.fdf", "0000001B", CStr(Hex(err.number)), "Certificate Publish       Status")
     exit sub
   End If
   
   On Error Resume Next
   IGSE.UserDN = exchangeDN
   If err.number <> 0 Then
     Call SetErrorInfo2("../fdf/VSApps/client/ExchangeErrors.fdf", "0000001C", CStr(Hex(err.number)), "Certificate Publish      Status")
     exit sub
   End If
   

   On Error Resume Next
   IGSE.PKCS7=CertChain
   '----------------Error Handing----------------------------
   If err.number <> 0 Then
	Select Case 	CStr(Hex(err.number))
 		   Case "8007003A"
			Call SetErrorInfo2("../fdf/VSApps/client/ExchangeErrors.fdf", "0000000d",                        CStr(Hex(err.number)),"Certificate Publish Status")  
	     	   	exit Sub	
		   Case "80070020"
			Call SetErrorInfo2("../fdf/VSApps/client/ExchangeErrors.fdf", "0000000A", CStr(Hex(err.number)), 			"Certificate Publish Status")  
	     	   	exit Sub
		   case "80070032"
			Call SetErrorInfo2("../fdf/VSApps/client/ExchangeErrors.fdf", "0000000F", CStr(Hex(err.number)), 			"Certificate Publish Status")  
 			exit Sub	
		   case "80093004"
			Call SetErrorInfo2("../fdf/VSApps/client/ExchangeErrors.fdf", 00000005, CStr(Hex(err.number)), 									"Certificate Publish Status")  
 			exit Sub	
		   case "80090009"
			Call SetErrorInfo2("../fdf/VSApps/client/ExchangeErrors.fdf", "0000001E", CStr(Hex(err.number)), 									"Certificate Publish Status")  
 			exit Sub		
		   case "1AD"
			Call SetErrorInfo2("../fdf/VSApps/client/ExchangeErrors.fdf", "00000035", CStr(Hex(err.number)), 									"Certificate Publish Status")  
 			exit Sub		
		   Case else
				MsgBox "An unknown error occured while updating your certificate to your mailbox." & chr(13) 								&_
				 "The error number is : 0x" & CStr(Hex(err.number))			
				Call StopIt()
     				window.navigate("../VSApps/digitalIdCenter.htm")		
				Exit Sub
		   End Select

     End If
     '---------------------End Here-------------------------------



     Call StopIt()
     
     <!-- VSSKBEGIN Apps/GSE#49 -->
     <!-- VSSKEND Apps/GSE#49 -->	

End Sub

Sub GetChallengePhrase
   exchangeDN = "$$exchange_DN$$"
   exchangeServerName = "$$exchange_ServerName$$"
   exchangeProfileName=	"$$exchange_ProfileName$$"	
   ExchangeVer ="$$exchange_Version$$"
   CertChainBlob=CertChain
   
   document.Stuff.userDN.value = exchangeDN
   document.Stuff.Use_AuthUpdate.value =UseAuthUpdate 	
   document.Stuff.ExchangeServerName_BOTH.value =exchangeServerName
   document.Stuff.ExchangeVersion.value =ExchangeVer
   document.Stuff.CertChainblob.value =CertChainBlob
     
   Call StopIt()

   document.Stuff.submit
   document.close

End Sub


'-->
</Script>
<!-- VSSKENDPOLICYVAL#yes#7 -->
<!-- VSSKBEGINPOLICYVAL#yes#8 -->
<FORM NAME="Stuff" ACTION="../cgi-bin/VSApps/srchexce.exe?Type=Challenge" ENCTYPE=x-www-form-encoded METHOD=POST>
         <INPUT TYPE="HIDDEN" NAME="userDN" VALUE="">
	<INPUT TYPE="HIDDEN" NAME="Use_AuthUpdate" VALUE="">
	<INPUT TYPE="HIDDEN" NAME="ExchangeServerName_BOTH" VALUE="">
	<INPUT TYPE="HIDDEN" NAME="ExchangeVersion" VALUE="">
	<INPUT TYPE="HIDDEN" NAME="CertChainblob" VALUE="">
</FORM>

<Script Language="VBScript">
<!--
        Call SignExchange
'-->
</Script>
<!-- VSSKENDPOLICYVAL#yes#8 -->


<!-- VSSKBEGINPOLICYVAL#yes#9#1.0.0.2 -->
<TABLE WIDTH=588 CELLPADDING=6 CELLSPACING=0 BORDER=0>
<TR>
	<TD BGCOLOR="cccccc"><FONT FACE="verdana, arial, helvetica" SIZE=2><B>Microsoft Exchange Integration:</B></FONT><P>
	 <CENTER>
	<TABLE WIDTH=574 CELLPADDING=2 CELLSPACING=0 BORDER=0 BGCOLOR="ffffcc">
	<TR>
	<TD>
        Your Digital ID has also been  also been added to the <B>Microsoft Exchange <BR>
        Global Address List (GAL)</B>,enabling other users within your organization <BR>
        the ability to easily send encrypted messages to you!
        <P>
        Visit our tutorial on <A HREF="../VSApps/client/help/apps/tutorial/outlook98.htm">Securing your
        E-mail with Microsoft Outlook '98 and your new VeriSign Managed PKI Digital ID</A>.
	</TD>
        </TR>
	</TABLE>
	</TD>
</TR>
</TABLE>
<p>
<!-- VSSKENDPOLICYVAL#yes#9 -->




<!-- VSSKBEGINPOLICYVAL#yes#10#1.0.0.2 -->
<TR>
	<TD WIDTH=50 ALIGN=left VALIGN=top>
	<A HREF="OSEXSETP.exe"><IMG SRC="graphics/action_arrowyellow.gif" border=0 WIDTH=40 HEIGHT=40 ALIGN=LEFT></A>
	</TD>
	<TD WIDTH=538 ALIGN=left VALIGN=top>
	<A HREF="OSEXSETP.exe"><FONT FACE="verdana, arial, helvetica" SIZE=5><B>Install Managed PKI/Exchange 
        Integration Desktop</B></FONT></A><BR>
	<P>
	</TD>
</TR>
<!-- VSSKENDPOLICYVAL#yes#10 -->


<!-- VSSKBEGINPOLICYVAL#yes#11 -->
     window.navigate("../client/userEnrollMS.htm")	
<!-- VSSKENDPOLICYVAL#yes#11 -->


<!-- VSSKBEGINPOLICYVAL#yes#12 -->
  	  {
	      document.write("<A HREF='client/userEnrollEncMS.htm'>")
          }  
<!-- VSSKENDPOLICYVAL#yes#12 -->


<!-- VSSKBEGINPOLICYVAL#yes#13 -->
      window.navigate("../client/userEnrollDualMS.htm")
<!-- VSSKENDPOLICYVAL#yes#13 -->


<!-- VSSKBEGINPOLICYVAL#yes#14 -->
       <NOSCRIPT><A HREF="../cgi-bin/srchexce.exe?fileName=/client/userEnrollEncMS.htm&ExchangeServerName=%%ExchangeServerName%%&ExchangeServerDomain=%%ExchangeOrgName%%&Type="></NOSCRIPT>
       <SCRIPT>
         document.write("<A HREF='../cgi-bin/srchexce.exe?fileName=/client/userEnrollEncMS.htm&ExchangeServerName=%%ExchangeServerName%%&ExchangeServerDomain=%%ExchangeOrgName%%&Type='>")
       </SCRIPT>
<!-- VSSKENDPOLICYVAL#yes#14 -->


<!-- VSSKBEGINPOLICYVAL#yes#15 -->
exchange_alias        CLEAR     MANDATORY                NONE    NONE
exchange_userName     CLEAR    MANDATORY                NONE    NONE
common_name           CLEAR    MANDATORY                NONE    NONE
san_common_name       CLEAR    MANDATORY                NONE    NONE
exchange_DN           CLEAR    MANDATORY                NONE    NONE
ldap_DN				  CLEAR    MANDATORY                NONE    NONE	
cert_DN               CLEAR    MANDATORY                NONE    NONE
exchange_ServerName   CLEAR	   MANDATORY                NONE    NONE
exch_Srvr			  CLEAR    MANDATORY                NONE    NONE
exchange_Version      CLEAR    MANDATORY                NONE    NONE
exchange_VerString    CLEAR  MANDATORY                  NONE    NONE
exchange_ProfileName  CLEAR    MANDATORY                NONE    NONE
win2k_upn             CLEAR  OPTIONAL                   NONE    NONE
win2k_efs_eku         CLEAR  OPTIONAL                   NONE    NONE
<!-- VSSKENDPOLICYVAL#yes#15 -->


<!-- VSSKBEGINPOLICYVAL#yes#16 -->
<input type=hidden NAME=exchange_alias VALUE="$$exchange_alias$$">
<input type=hidden NAME=exchange_userName VALUE="$$exchange_userName$$">
<input type=hidden NAME=common_name VALUE="$$common_name$$">
<input type=hidden NAME=san_common_name VALUE="$$san_common_name$$">
<input type=hidden NAME=exchange_DN VALUE="$$exchange_DN$$">
<input type=hidden NAME=ldap_DN VALUE="$$ldap_DN$$">
<input type=hidden NAME=exchange_ServerName VALUE="$$exchange_ServerName$$">
<input type=hidden NAME=exch_Srvr VALUE="$$exch_Srvr$$">
<input type=hidden NAME=exchange_Version VALUE="$$exchange_Version$$">
<input type=hidden NAME=exchange_VerString VALUE="$$exchange_VerString$$">
<input type=hidden NAME=exchange_ProfileName VALUE="$$exchange_ProfileName$$">
<input type=hidden NAME=cert_DN VALUE="$$cert_DN$$">
<input type=hidden name=win2k_upn value="$$win2k_upn$$">
<input type=hidden name=win2k_efs_eku value="$$win2k_efs_eku$$">
<!-- VSSKENDPOLICYVAL#yes#16 -->

<!-- VSSKBEGINPOLICYVAL#yes#17 -->
  <!-- VSSKBEGIN Enrollment/EMAIL#8 -->
  <!-- VSSKEND Enrollment/EMAIL#8 -->
<!-- VSSKENDPOLICYVAL#yes#17 -->


<!-- VSSKBEGINPOLICYVAL#yes#18 -->
  <!-- VSSKBEGIN Enrollment/EMAIL#9 -->
  <!-- VSSKEND Enrollment/EMAIL#9 -->
<!-- VSSKENDPOLICYVAL#yes#18 -->

<!-- VSSKBEGINPOLICYVAL#yes#19 -->
  <!-- VSSKBEGIN Enrollment/EMAIL#7 -->
  <!-- VSSKEND Enrollment/EMAIL#7 -->
<!-- VSSKENDPOLICYVAL#yes#19 -->

<!-- VSSKBEGINPOLICYVAL#yes#20 -->
       <NOSCRIPT><A HREF="../cgi-bin/srchexce.exe?fileName=/client/mspickup.htm&ExchangeServerName=%%ExchangeServerName%%&ExchangeServerDomain=%%ExchangeOrgName%%&Type="></NOSCRIPT>
       <SCRIPT>
         document.write("<A HREF='../cgi-bin/srchexce.exe?fileName=/client/mspickup.htm&ExchangeServerName=%%ExchangeServerName%%&ExchangeServerDomain=%%ExchangeOrgName%%&Type='>")
       </SCRIPT>
<!-- VSSKENDPOLICYVAL#yes#20 -->

<!-- VSSKBEGINPOLICYVAL#yes#21 -->
          document.write("<A HREF='client/mspickup.htm'>")
<!-- VSSKENDPOLICYVAL#yes#21 -->


<!-- VSSKBEGINPOLICYVAL#yes#22 -->
       <NOSCRIPT><A HREF="../cgi-bin/srchexce.exe?fileName=/client/userGetEncMS.htm&ExchangeServerName=%%ExchangeServerName%%&ExchangeServerDomain=%%ExchangeOrgName%%&Type="></NOSCRIPT>
       <SCRIPT>
         document.write("<A HREF='../cgi-bin/srchexce.exe?fileName=/client/userGetEncMS.htm&ExchangeServerName=%%ExchangeServerName%%&ExchangeServerDomain=%%ExchangeOrgName%%&Type='>")
       </SCRIPT>
<!-- VSSKENDPOLICYVAL#yes#22 -->

<!-- VSSKBEGINPOLICYVAL#yes#23 -->
          document.write("<A HREF='/client/userGetEncMS.htm'>")
<!-- VSSKENDPOLICYVAL#yes#23 -->

<!-- VSSKBEGINPOLICYVAL#yes#24 -->
<!-- these are exchange integration specific variables -->
<input type=hidden name=exchange_DN value="">
<input type=hidden name=ldap_DN value="">
<input type=hidden name=exchange_ServerName value="">
<input type=hidden name=exch_Srvr value="">
<input type=hidden name=exchange_Version value="">
<input type=hidden name=exchange_VerString value="">
<input type=hidden name=exchange_ProfileName value="">

<Script Language="JavaScript">
<!--
  
-->
</Script>
<!-- VSSKENDPOLICYVAL#yes#24 -->


<!-- VSSKBEGINPOLICYVAL#yes#25 -->
exchange_DN        	CLEAR     MANDATORY                NONE    NONE
ldap_DN        		CLEAR     MANDATORY                NONE    NONE
exchange_ServerName CLEAR     MANDATORY                NONE    NONE
exch_Srvr		  	CLEAR     MANDATORY                NONE    NONE
exchange_Version  	CLEAR     MANDATORY                NONE    NONE
exchange_VerString  CLEAR     MANDATORY                NONE    NONE
exchange_ProfileName  	CLEAR     MANDATORY                NONE    NONE

<!-- VSSKENDPOLICYVAL#yes#25 -->

<!-- VSSKBEGINPOLICYVAL#yes#26 -->
<Script Language="JavaScript">
<!--
  function SetDN()
  {
    var inputDN, outputDN ;
    var re = /"/g ;

    inputDN = tMailBoxInfo[0].DN ;
    outputDN = inputDN.replace(re, "\"\"") ;
    document.proform.exchange_DN.value = outputDN ;

    if ( tMailBoxInfo[0].DN == "" )
    {
      window.navigate("../../cgi-bin/softbounce.exe?form_file=../fdf/VSApps/client/ExchangeErrors.fdf&errorCode=00000002&operation=Enrollment Status&showError=") ;
    }
  }
-->
</Script>
<!-- VSSKENDPOLICYVAL#yes#26 -->

<!-- VSSKBEGINPOLICYVAL#yes#27 -->
<SCRIPT LANGUAGE=JavaScript>
<!--
var fullName, distinguishedName, Alias, rfc822Mailbox ;

  function SetGlobalVars(index)
  {
    distinguishedName = tMailBoxInfo[index].DN ;
    rfc822Mailbox = tMailBoxInfo[index].emailAddress ;
    fullName = tMailBoxInfo[index].fullName ;
    Alias = tMailBoxInfo[index].Alias ;

    if ( fullName == "" )
    {
      window.navigate("../../cgi-bin/softbounce.exe?form_file=../fdf/VSApps/client/ExchangeErrors.fdf&errorCode=00000001&operation=Enrollment Status&showError=") ;
    }
    else if ( distinguishedName == "" )
    {
      window.navigate("../../cgi-bin/softbounce.exe?form_file=../fdf/VSApps/client/ExchangeErrors.fdf&errorCode=00000002&operation=Enrollment Status&showError=") ;
    }
    else if ( rfc822Mailbox == "" )
    {
      window.navigate("../../cgi-bin/softbounce.exe?form_file=../fdf/VSApps/client/ExchangeErrors.fdf&errorCode=00000003&operation=Enrollment Status&showError=") ;
    }
    else if ( Alias == "" )
    {
      window.navigate("../../cgi-bin/softbounce.exe?form_file=../fdf/VSApps/client/ExchangeErrors.fdf&errorCode=00000004&operation=Enrollment Status&showError=") ;
    }

    var companyName, Trunc ;

    companyName = ", %%::corpName%%" ;
    Trunc = Alias + " (" + fullName + companyName ;
    Trunc = Trunc.substring(0, 62) ;
    Trunc = Trunc + ")" ;

    document.proform.mail_email.value = rfc822Mailbox ;
    document.proform.common_name.value = Trunc ;
    document.proform.exchange_alias.value = Alias ;
    document.proform.exchange_userName.value = fullName ;


    //-- VSSKBEGIN Global/Mode#37 --
    //-- VSSKEND Global/Mode#37 --

    certDN = distinguishedName.substring(distinguishedName.indexOf(",")+1) ;

    //-- VSSKBEGIN Global/Mode#34 --
    //-- VSSKEND Global/Mode#34 --

    //-- VSSKBEGIN Global/Mode#38 --
    //-- VSSKEND Global/Mode#38 --
  }

  function SetSelectedUserGlobalVars()
  {
    for ( i = 0 ; i < tMailBoxInfo.length ; i++ )
    {
      if ( document.proform.MailBoxIndex[i].checked )
      {
	distinguishedName = tMailBoxInfo[i].DN ;
	rfc822Mailbox = tMailBoxInfo[i].emailAddress ;
	fullName = tMailBoxInfo[i].fullName ;
	Alias = tMailBoxInfo[i].Alias ;

        if ( fullName == "" )
        {
          window.navigate("../../cgi-bin/softbounce.exe?form_file=../fdf/VSApps/client/ExchangeErrors.fdf&errorCode=00000001&operation=Enrollment Status&showError=")
        }
        else if ( distinguishedName == "" )
        {
          window.navigate("../../cgi-bin/softbounce.exe?form_file=../fdf/VSApps/client/ExchangeErrors.fdf&errorCode=00000002&operation=Enrollment Status&showError=")
        }
        else if ( rfc822Mailbox == "" )
        {
          window.navigate("../../cgi-bin/softbounce.exe?form_file=../fdf/VSApps/client/ExchangeErrors.fdf&errorCode=00000003&operation=Enrollment Status&showError=")
        }
        else if ( Alias == "" )
        {
          window.navigate("../../cgi-bin/softbounce.exe?form_file=../fdf/VSApps/client/ExchangeErrors.fdf&errorCode=00000004&operation=Enrollment Status&showError=")
        }

	break ;
      }
    }
  }

  function ShowFullNameEmailAddress(TheFullName)
  {
    document.write("<P><BR><P>") ;
    document.write("<TABLE WIDTH=588 BGCOLOR=\"ffffcc\" CELLPADDING=7 CELLSPACING=0 BORDER=0>") ;
    document.write("<TR>") ;
    document.write("<TD WIDTH=588>") ;
    document.write("<FONT SIZE=2 FACE=\"verdana, arial, helvetica\"><B>Information detected from Micro") ;
    document.write("soft Exchange</B></FONT><BR><P>") ;
    document.write("<CENTER>") ;
    document.write("<TABLE WIDTH=574 CELLPADDING=3 CELLSPACING=2 BORDER=0>") ;
    document.write("<TR>") ;
    document.write("  <TD WIDTH=50% BGCOLOR=\"FFCC00\">") ;
    document.write("    <FONT FACE=\"verdana, arial, helvetica\" SIZE=2>") ;
    document.write("    <B>Full Name: </B>") ;
    document.write("    </FONT>") ;
    document.write("  </TD>") ;
    document.write("  <TD COLSPAN=2 WIDTH=50% BGCOLOR=\"FFCC00\">") ;
    document.write("    <IMG SRC=\"../graphics/blank2.gif\" WIDTH=27 HEIGHT=27>&nbsp;&nbsp;&nbsp;") ;
    document.write("    <FONT FACE=\"verdana, arial, helvetica\" SIZE=2>") ;

    document.write("    <b>" + fullName + "</b>") ;

    document.write("    </FONT>") ;
    document.write("  </TD>") ;
    document.write("</TR>") ;
    document.write("<TR>") ;
    document.write("  <TD WIDTH=50% BGCOLOR=\"FFCC00\">") ;
    document.write("    <FONT FACE=\"verdana, arial, helvetica\" SIZE=2>") ;
    document.write("    <B>Email Address: </B>") ;
    document.write("  </TD>") ;
    document.write("  <TD COLSPAN=2 WIDTH=50% BGCOLOR=\"FFCC00\">") ;
    document.write("    <IMG SRC=\"../graphics/blank2.gif\" WIDTH=27 HEIGHT=27>&nbsp;&nbsp;&nbsp;") ;
    document.write("    <FONT FACE=\"verdana, arial, helvetica\" SIZE=2>") ;

    document.write("    <b>" + rfc822Mailbox + "</b>") ;

    document.write("    </FONT>") ;
    document.write("  </TD>") ;
    document.write("</TR>") ;
    document.write("</TABLE>") ;
    document.write("<!--END INPUT FIELD TABLE-->") ;
    document.write("</TD>") ;
    document.write("</TR>") ;
    document.write("</TABLE>") ;
  }


  function ShowMBITableHead()
  {
    document.write("<TABLE WIDTH=588 BGCOLOR=\"ffffcc\" CELLPADDING=7 CELLSPACING=0 BORDER=0>") ;
    document.write("<TR>") ;
    document.write("                <TD WIDTH=588>") ;
    document.write("                        <FONT FACE=\"arial, helvetica\" SIZE=2><b></b></FONT>") ;
    document.write("                        <FONT SIZE=2 FACE=\"verdana, arial, helvetica\">") ;
    document.write("                </TD>") ;
    document.write("                <TD WIDTH=588>") ;
    document.write("                        <FONT FACE=\"arial, helvetica\" SIZE=2><b>MailBox Name</b></FONT>") ;
    document.write("                        <FONT SIZE=2 FACE=\"verdana, arial, helvetica\">") ;
    document.write("                </TD>") ;
    document.write("                <TD WIDTH=588>") ;
    document.write("                        <FONT FACE=\"arial, helvetica\" SIZE=2><b>Full Name</b></FONT>") ;
    document.write("                        <FONT SIZE=2 FACE=\"verdana, arial, helvetica\">") ;
    document.write("                </TD>") ;
    document.write("                <TD WIDTH=588>") ;
    document.write("                        <FONT FACE=\"arial, helvetica\" SIZE=2><b>Email Address</b></FONT>") ;
    document.write("                        <FONT SIZE=2 FACE=\"verdana, arial, helvetica\">") ;
    document.write("                </TD>") ;
    document.write("</TR>") ;
  }


  function ShowMBITitle()
  {
    document.write("<TABLE WIDTH=588 BGCOLOR=\"ffffcc\" CELLPADDING=7 CELLSPACING=0 BORDER=0>") ;
    document.write("<TR>") ;
    document.write("                <TD WIDTH=588>") ;
    document.write("                        <FONT FACE=\"arial, helvetica\" SIZE=2><b>There are multiple mailboxes associated with your Windows Login. Please select the mailbox for Digital ID enrollment.</b></FONT>") ;
    document.write("                        <FONT SIZE=2 FACE=\"verdana, arial, helvetica\">") ;
    document.write("                </TD>") ;
    document.write("</TR>") ;
    document.write("</TABLE>") ;
  }


  function ShowMBIEnum(MailBoxInfo)
  {
    document.write("<TR>") ;

    document.write("                <TD WIDTH=588 ALIGN=RIGHT>") ;
    document.write("                <INPUT TYPE=\"RADIO\" ") ;
    if ( i == 0 )
    {
      document.write("CHECKED") ;
    }
    document.write("                NAME=MailBoxIndex VALUE=" + i + "> ") ;
    document.write("                </TD>") ;

    document.write("                <TD WIDTH=588>") ;
    document.write("                        <FONT FACE=\"arial, helvetica\" SIZE=2>" + MailBoxInfo.Alias + "</FONT>") ;
    document.write("                        <FONT SIZE=2 FACE=\"verdana, arial, helvetica\">") ;
    document.write("                </TD>") ;

    document.write("                <TD WIDTH=588>") ;
    document.write("                        <FONT FACE=\"arial, helvetica\" SIZE=2>" + MailBoxInfo.fullName + "</FONT>") ;
    document.write("                        <FONT SIZE=2 FACE=\"verdana, arial, helvetica\">") ;
    document.write("                </TD>") ;

    document.write("                <TD WIDTH=588>") ;
    document.write("                        <FONT FACE=\"arial, helvetica\" SIZE=2>" + MailBoxInfo.emailAddress + "</FONT>") ;
    document.write("                        <FONT SIZE=2 FACE=\"verdana, arial, helvetica\">") ;
    document.write("                </TD>") ;
  
    document.write("</TR>") ;
  }


  function ShowMBI()
  {
    if (tMailBoxInfo.length == 1 )
    {
      SetGlobalVars(0) ;
      ShowFullNameEmailAddress(fullName) ;
    }
    else
    {
      ShowMBITitle() ;

      ShowMBITableHead() ;

      for ( i = 0 ; i < tMailBoxInfo.length ; i++ )
        ShowMBIEnum(tMailBoxInfo[i]) ;
  
      document.write("</TABLE>") ;
    }
  }
-->
</SCRIPT>

<SCRIPT LANGUAGE="JavaScript">
<!--
  function SetFormVars()
  {
    var companyName, Trunc ;

    companyName = ", %%::corpName%%" ;
    Trunc = Alias + " (" + fullName + companyName ;
    Trunc = Trunc.substring(0, 62) ;
    Trunc = Trunc + ")" ;

    document.proform.mail_email.value = rfc822Mailbox
    document.proform.common_name.value = Trunc
    document.proform.exchange_alias.value = Alias
    document.proform.exchange_userName.value = fullName

    //-- VSSKBEGIN Global/Mode#37 --
    //-- VSSKEND Global/Mode#37 --

    certDN = distinguishedName.substring(distinguishedName.indexOf(",")+1) ;

    //-- VSSKBEGIN Global/Mode#34
    //-- VSSKEND Global/Mode#34

    //-- VSSKBEGIN Global/Mode#38 --
    //-- VSSKEND Global/Mode#38 --
  }

-->
</SCRIPT>
<!-- VSSKENDPOLICYVAL#yes#27 -->

<!-- VSSKBEGINPOLICYVAL#yes#28 -->
       If tMailBoxInfo.length <> 1 Then
         SetSelectedUserGlobalVars()

         SetFormVars()
       End If
<!-- VSSKENDPOLICYVAL#yes#28 -->

<!-- VSSKBEGINPOLICYVAL#yes#29 -->
       if ( tMailBoxInfo.length != 1 )
       {
         SetSelectedUserGlobalVars() ;

         SetFormVars() ;
       }
<!-- VSSKENDPOLICYVAL#yes#29 -->

<!-- VSSKBEGINPOLICYVAL#yes#30 -->
  Sub GoAhead
     window.navigate("../cgi-bin/VSApps/srchexce.exe?fileName=/VSApps/client/userEnrollMS.htm&ExchangeServerName=%%ExchangeServerName%%&ExchangeServerDomain=%%ExchangeOrgName%%&Type=")
  End Sub
<!-- VSSKENDPOLICYVAL#yes#30 -->


<!-- VSSKBEGINPOLICYVAL#yes#31 -->
  Sub GoAhead
     window.navigate("../cgi-bin/VSApps/srchexce.exe?fileName=/VSApps/client/userEnrollEncMS.htm&ExchangeServerName=%%ExchangeServerName%%&ExchangeServerDomain=%%ExchangeOrgName%%&Type=")
  End Sub
<!-- VSSKENDPOLICYVAL#yes#31 -->


<!-- VSSKBEGINPOLICYVAL#yes#32 -->
  Sub GoAhead
     window.navigate("../cgi-bin/VSApps/srchexce.exe?fileName=/VSApps/client/userEnrollDualMS.htm&ExchangeServerName=%%ExchangeServerName%%&ExchangeServerDomain=%%ExchangeOrgName%%&Type=")
  End Sub
<!-- VSSKENDPOLICYVAL#yes#32 -->


<!-- VSSKBEGINPOLICYVAL#yes#33 -->
  Sub GoAhead
     window.navigate("../cgi-bin/VSApps/srchexce.exe?fileName=/VSApps/client/mspickup.htm&ExchangeServerName=%%ExchangeServerName%%&ExchangeServerDomain=%%ExchangeOrgName%%&Type=")
  End Sub
<!-- VSSKENDPOLICYVAL#yes#33 -->


<!-- VSSKBEGINPOLICYVAL#yes#34 -->
  Sub GoAhead
     window.navigate("../cgi-bin/VSApps/srchexce.exe?fileName=/VSApps/client/userGetEncMS.htm&ExchangeServerName=%%ExchangeServerName%%&ExchangeServerDomain=%%ExchangeOrgName%%&Type=")
  End Sub
<!-- VSSKENDPOLICYVAL#yes#34 -->

<!-- VSSKBEGINPOLICYVAL#yes#35 -->
<FORM METHOD=POST NAME="proform" ACTION="../cgi-bin/authsophialite.exe" ENCTYPE=x-www-form-encoded>
<!-- VSSKENDPOLICYVAL#yes#35 -->

<!-- VSSKBEGINPOLICYVAL#yes#36 -->
var ExchangeIntegration = 1;
<!-- VSSKENDPOLICYVAL#yes#36 -->

<!-- VSSKBEGINPOLICYVAL#yes#37 -->
           Dim EnrollPage
           EnrollPage="enroll.htm"
<!-- VSSKENDPOLICYVAL#yes#37 -->

<!-- VSSKBEGINPOLICYVAL#yes#38 -->
          var EnrollPage = "enroll.htm";
<!-- VSSKENDPOLICYVAL#yes#38 -->

<!-- VSSKBEGINPOLICYVAL#yes#39 -->
           Dim EnrollPage
           EnrollPage= "enroll.htm"
<!-- VSSKENDPOLICYVAL#yes#39 -->

<!-- VSSKBEGINPOLICYVAL#yes#40 -->
          var EnrollPage = "enroll.htm";
<!-- VSSKENDPOLICYVAL#yes#40 -->

<!-- VSSKBEGINPOLICYVAL#yes#41#1.2.0.0 -->
<SCRIPT LANGUAGE=VBSCRIPT>
<!--
Dim fullName ,distinguishedName,ServerName,ProfileName,Alias,rfc822Mailbox,ExchangeVer,UserDN,SanName
Dim win2kUPN, useUPN, Policy_useUPN, useEFS, Policy_useEFS, isAdmin
Dim Cert_DN_Format,certDN,companyName,Trunc,distName
Dim ExplodeDN,x, gCharEncoding	

Cert_DN_Format=0	
gcharEncoding="%%Enrollment/CharEncoding::policyValue%%"

Function  ExchangeDNFormat()

		companyName = ", %%::corpName%%"
    	Trunc = Alias + " (" + fullName + companyName
    	Trunc = Left(Trunc, 62)
    	Trunc = Trunc + ")"

	    SanName="CN = "+fullName	
   	    Document.proform.common_name.value = Trunc 
		
		if(gCharEncoding="exists")then
			IGSE.CharEncodingInfo=1
        else
			IGSE.CharEncodingInfo=0
        End if  

		ExchRDN=IGSE.explode_DN
    
	    for x= LBound(ExchRDN) to UBound(ExchRDN)
			distName=distName+ExchRDN(x)
			if(x < UBound(ExchRDN)) then
				distName=distName+","
			end if
	    
    	next
	   
		Pos = Instr(distName, ",")
        certDN =Right(distName,len(distName)-Pos)	
	    	if(gCharEncoding="exists")then
				certDN="cn=" +"<0C>"+ """" + Trunc + """" + "," + certDN
		else
				certDN="cn=" + """" + Trunc + """" + "," + certDN
		End if
	    
		
		return certDN

End Function

Function MPKIDNFormat()

		companyName ="%%::corpName%%"
		orgUnitName = "%%::orgUnitName%%"

		SanName="CN = "+fullName	
           
	   	Document.proform.common_name.value = fullName 			

	    if(gCharEncoding="exists")then
			CertDN="cn=" + "<0C>"+"""" + fullName + """" + "," + "ou=" + "<0C>" + """" +orgUnitName +""""+"," + "o="+"<0C>" + """" +companyName + """"
        else
			CertDN="cn=" +"""" + fullName + """" + "," + "ou=" +"""" +orgUnitName +""""+"," + "o=" + """" +companyName + """"
        End if  
		
		return certDN

End Function

Function CustomMPKIDNFormat()
		Dim CertDN
		CertDN=""          
	   	Document.proform.common_name.value = fullName 			
		return certDN

End Function

'-- VSSKBEGIN Global/System#12 --
'-- VSSKEND Global/System#12 --	

	SUB SetVars
        Dim szTemp,Pos,Check
	    Dim RetVal ,AccessRight,ExchProfile,str
	    Dim inputDN,outputDN,tmpDN,ExchVerStr,ADSInfo,LdapDN
	    Dim AuthMethod,tmpfullName 

            '-- VSSKBEGIN Global/System#17 --
            '-- VSSKEND Global/System#17 --	
	    
	    On Error Resume Next	
	    IGSE.UpdateClientExt	
	    If err.number <> 0 Then
	    		Select Case CStr(Hex(err.number))
			Case "80070020"
				MsgBox "Unable to update Go Secure! for Exchange Outlook Client Extension. Please close all Outlook windows and start the certificate enrollment again. "
				Call StopIt()
				window.navigate("../digitalidCenter.htm")	 
			  exit Sub
			Case "1B6"
				Call SetErrorInfo2("../fdf/VSApps/client/ExchangeErrors.fdf", "00000024", CStr(Hex(err.number)),"Certificate Enrollment")  
	     	   	exit Sub	
				
			End Select	
	    End If

	     'These three function must be needed before you call any function related to the mailbox properties
	     'such as FullName,mailDN,HomeServer...etc.
             
		
	     IGSE.CAInfo=%%ConnectionAgreementType%%	
	     On Error Resume Next		
 	     ADSInfo=%%ADSInfo%% 
	 
	     On Error Resume Next			
	     IGSE.ADServerInfo=ADSInfo 
	     IGSE.ADServerInfoList="%%ADSInfoList%%"

				
		 
	    fullName=Empty

	    AccessRight=1        	
            On Error Resume Next
	    fullName = IGSE.FullName
            If err.number <> 0 Then
                   Select Case 	CStr(Hex(err.number))
 		   Case "8007003A"
			Call SetErrorInfo2("../fdf/VSApps/client/ExchangeErrors.fdf", "0000000d", CStr(Hex(err.number)),"Certificate Enrollment")  
	     	   	exit Sub	
		   Case "80070020"
			Call SetErrorInfo2("../fdf/VSApps/client/ExchangeErrors.fdf", "0000000A", CStr(Hex(err.number)),"Certificate Enrollment")  
	     	   	exit Sub
		   Case "80070031"
			Call SetErrorInfo2("../fdf/VSApps/client/ExchangeErrors.fdf", "00000011", CStr(Hex(err.number)), "Certificate Enrollment") 
			exit Sub	
         	   Case "80070032"
			Call SetErrorInfo2("../fdf/VSApps/client/ExchangeErrors.fdf", "0000000F", CStr(Hex(err.number)), "Certificate Enrollment") 
			exit Sub	
		   Case "8007274d"
			Call SetErrorInfo2("../fdf/VSApps/client/ExchangeErrors.fdf", "00000022", CStr(Hex(err.number)), "Certificate Enrollment") 
			exit Sub		
		   Case "80008004"
			Call SetErrorInfo2("../fdf/VSApps/client/ExchangeErrors.fdf", "00000038", CStr(Hex(err.number)), "Certificate Enrollment") 
			 exit Sub
		   
		   End Select
            End If
		
 	    If Len(fullName)=0  Then
		 	str=	"You are viewing this message for one of the following reasons:" & chr(13)& chr(13) &_
				"Your default outlook profile is not Exchange enabled." & chr(13)&_
				"You do not have any Outlook Exchange profile."& chr(13)&_
				"You do not have the rights to view properties of the mailbox associated with the default Outlook Exchange profile" & chr(13) & chr(13)&_
				"Press OK to Select/Create Outlook Exchange enabled profile or Press CANCEL" & chr(13)&_ 
				"to abort certificate enrollment."

		RetVal=MsgBox (str,1)	
                 
		If RetVal=1 Then	
			ExchProfile=0	
			while ExchProfile=0	
	 			On Error Resume Next 
			  	IGSE.PromptForSelection
                           	' ---------------------------------	
			   	If err.number <> 0 Then
                   			Select Case 	CStr(Hex(err.number))
		 			Case "80070031"
						Call SetErrorInfo2("../fdf/VSApps/client/ExchangeErrors.fdf", "00000011", CStr(Hex(err.number)), "Certificate Enrollment") 
						exit Sub	
		 			Case "80070032"
						Call SetErrorInfo2("../fdf/VSApps/client/ExchangeErrors.fdf", "0000000F", CStr(Hex(err.number)), "Certificate Enrollment") 
						exit Sub	
		 			Case "8007003A"
						Call SetErrorInfo2("../fdf/VSApps/client/ExchangeErrors.fdf", "0000000d", CStr(Hex(err.number)), "Certificate Enrollment") 
						exit Sub	
		   			Case "80070020"
						Call SetErrorInfo2("../fdf/VSApps/client/ExchangeErrors.fdf", "0000000A", CStr(Hex(err.number)), "Certificate Enrollment")  
	     	   				exit Sub	
					case "80040111"
						window.navigate("../digitalidCenter.htm")
						exit Sub
		   			case "80040113"
						Call SetErrorInfo2("../fdf/VSApps/client/ExchangeErrors.fdf", "0000000E", CStr(Hex(err.number)),"Certificate Enrollment")
 						exit Sub
					Case "8007274d"
						Call SetErrorInfo2("../fdf/VSApps/client/ExchangeErrors.fdf", "00000022", CStr(Hex(err.number)), "Certificate Enrollment") 
					exit Sub
	
					case  "80070032"
						MsgBox "You don't have the rights to modify the properties of the mailbox associated with this Outlook profile."
					case Else
						MsgBox "An unknown error occured while obtaining your information from the mailbox identified by the selected Outlook profile." & chr(13) &_
					"The error number is : 0x" & CStr(Hex(err.number))			
						ExchProfile=1
						Call StopIt()
						window.navigate("../digitalidCenter.htm")
						exit Sub
		   			End Select
			   	Else
	 		 		On Error Resume Next 
			   		fullName = IGSE.FullName
			   		if Len(fullName)=0 Then
	     					MsgBox "Select exchange enabled profile."
		    	   		else
						ExchProfile=1
			   		End If
            		   	End If
			wend
		   Else
			Call StopIt()
			window.navigate("../digitalidCenter.htm")	
			exit Sub	
		   End IF		
	    End If

 	
            
         On Error Resume Next
          ExchangeVer=IGSE.ExchangeVer
	     if err.number<> 0 then
			Call SetErrorInfo2("../fdf/VSApps/client/ExchangeErrors.fdf", "00000022", CStr(Hex(err.number)), "Certificate 												Enrollment")
     			exit sub
             end if
	     if ExchangeVer=-1 then	
			ExchVerStr=IGSE.ExchangeVerString	
			Call SetErrorInfo2("../fdf/VSApps/client/ExchangeErrors.fdf", "00000021", ExchVerStr, "Certificate 															Enrollment")
			exit sub
	     end if
		   	            	
	    
	    fullName = IGSE.FullName

	    tmpfullName = fullName
        fullName = ""
        For i = 1 to Len(tmpfullName)
          If Mid(tmpfullName,i,1) <> "," then
            fullName = fullName & Mid(tmpfullName,i,1)
          End If
        Next


        distinguishedName = IGSE.DN
	    UserDN=IGSE.UserDN
		rfc822Mailbox = IGSE.RFC822Name
    	Alias = IGSE.Alias
        ServerName=IGSE.ProfileServer
		exch_srvr= IGSE.ExchServer
	    ProfileName=IGSE.ProfileName

		LdapDN=UserDN
		ExchVerStr=IGSE.ExchangeVerString

		

        '----- Windows 2000 UPN
        Policy_useUPN="%%use_UPN%%"
        if Policy_useUPN = "" or Policy_useUPN = "0" then
          useUPN = 0
        else
          useUPN = 1
        end if

        if useUPN=1 then	
          win2kUPN=IGSE.UserPrincipalName
        else  
          win2kUPN = ""
        end if

       '----- Windows 2000 EFS

        Policy_useEFS="%%use_EFS%%"
        if Policy_useEFS = "" OR Policy_useEFS = "0" then
          useEFS = 0
        else
          useEFS = 1
        end if

        if useEFS=1 then	
          isAdmin=IGSE.IsUserMemberOfAdminGroup
          if (isAdmin=1) then
			Document.proform.win2k_efs_eku.value="ra"
		  else
			Document.proform.win2k_efs_eku.value="user"
		  end if
        end if

	
		If ( fullName = "" OR distinguishedName = "" OR rfc822Mailbox = "" OR  UserDN="" OR Alias = "" OR ServerName = "" OR ProfileName = "" ) Then
				Call SetErrorInfo2("../fdf/VSApps/client/ExchangeErrors.fdf", "0000001F", CStr(Hex(err.number)),"Certificate Enrollment")
				exit Sub
		End If  
	    	                
		
	    AuthMethod = GetCertAuthMethod

	    if ( AuthMethod = "passcode" ) then
	      ' Treat it as passcode auth only
              tmpDN = ""
              For i = 1 to Len(UserDN)
                If Mid(UserDN,i,1) = """" then
		  tmpDN = tmpDN & """" &""""		
                Else
                  tmpDN = tmpDN & Mid(UserDN,i,1)
                End If
              Next
              Document.proform.exchange_DN.value = tmpDN
	    elseif ( AuthMethod = "manual" ) then
	      ' Treat it as Manual auth only
	      Document.proform.exchange_DN.value = UserDN
	    else
	      ' Treat it as Auto Auth
              tmpDN = ""
              For i = 1 to Len(UserDN)
                If Mid(UserDN,i,1) = """" then
                  tmpDN = tmpDN & "&#34;&#34;"
                Else
                  tmpDN = tmpDN & Mid(UserDN,i,1)
                End If
              Next
              Document.proform.exchange_DN.value = tmpDN
	    end if


		if(Cert_DN_Format=0) then
			certDN=ExchangeDNFormat
        End if

		if(Cert_DN_Format=1) then
			certDN=MPKIDNFormat
        End if

		if(Cert_DN_Format=2) then
			certDN=CustomMPKIDNFormat
        End if


	    if ( AuthMethod = "passcode" ) then
	      ' Treat it as passcode auth only
              tmpDN = ""
              For i = 1 to Len(certDN)
                If Mid(certDN,i,1) = """" then
		   tmpDN = tmpDN & """"	
                Else
                  tmpDN = tmpDN & Mid(certDN,i,1)
                End If
              Next
              Document.proform.cert_DN.value = tmpDN
	    elseif ( AuthMethod = "manual" )then
	      ' Treat it as Manual auth only
	      Document.proform.cert_DN.value = certDN
	    else
	      ' Treat it as Auto Auth
              tmpDN = ""
              For i = 1 to Len(certDN)
                If Mid(certDN,i,1) = """" then
                  tmpDN = tmpDN & "&#34;"
                Else
                  tmpDN = tmpDN & Mid(certDN,i,1)
                End If
              Next
              Document.proform.cert_DN.value = tmpDN
	    end if

		Document.proform.mail_email.value = rfc822Mailbox
    	Document.proform.san_common_name.value = SanName	
        Document.proform.exchange_alias.value = Alias 
		Document.proform.ldap_DN.value = LdapDN 
        Document.proform.exchange_userName.value = fullName 
        Document.proform.win2k_upn.value = win2kUPN


	    Document.proform.exchange_ServerName.value = ServerName	
		Document.proform.exch_Srvr.value = exch_srvr	
	    Document.proform.exchange_Version.value=ExchangeVer					
		Document.proform.exchange_VerString.value=ExchVerStr							
	    Document.proform.exchange_ProfileName.value = ProfileName	
    End SUB

    Sub ShowFullNameEmailAddress
	 Document.Write "<P><BR><P>" 
    	 Document.Write "<TABLE WIDTH=588 BGCOLOR=""ffffcc"" CELLPADDING=7 CELLSPACING=0 BORDER=0>"
         Document.Write "<TR>" 
         Document.Write "<TD WIDTH=588>"
	 Document.Write "<FONT SIZE=2 FACE=""verdana, arial, helvetica""><B>Information retrieved from Micro"
	 Document.Write "soft Exchange Server</B></FONT><BR><P>" 


    	 Document.Write "<CENTER>" 
	 Document.Write "<TABLE WIDTH=574 CELLPADDING=3 CELLSPACING=2 BORDER=0>"



	 '-----------Fill the Table Row ------------
	 Document.Write "<TR>"
    	 Document.Write "  <TD WIDTH=50% BGCOLOR=""FFCC00"">"
    	 Document.Write "    <FONT FACE=""verdana, arial, helvetica"" SIZE=2>"
    	 Document.Write "    <B>Outlook Profile: </B>"
    	 Document.Write "    </FONT>"

	 Document.Write  "<BR><FONT SIZE=2 FACE=""arial, helvetica"">Outlook Profile used for  certificate enrollment<BR></FONT>"

	 Document.Write "  </TD>"
	 Document.Write "  <TD COLSPAN=2 WIDTH=50% BGCOLOR=""FFCC00"">" 
    	 Document.Write "    <IMG SRC=""../graphics/blank2.gif"" WIDTH=27 HEIGHT=27>&nbsp;&nbsp;&nbsp;" 

	 Document.Write "    <FONT FACE=""verdana, arial, helvetica"" SIZE=2>" 
	 Document.Write "    <b>" + ProfileName+ "</b>"
	 Document.Write "    </FONT>"
	 	
	 Document.Write "  </TD>"
    	 Document.Write "</TR>"
         '-----------Row End Here---------------------

	 '-----------Fill the Table Row ------------
	 Document.Write "<TR>"
    	 Document.Write "  <TD WIDTH=50% BGCOLOR=""FFCC00"">"
    	 Document.Write "    <FONT FACE=""verdana, arial, helvetica"" SIZE=2>"
    	 Document.Write "    <B>Full Name: </B>"
    	 Document.Write "    </FONT>"

	 Document.Write  "<BR><FONT SIZE=2 FACE=""arial, helvetica"">Full Name associated with the Outlook Profile<BR></FONT>"

	 Document.Write "  </TD>"
	 Document.Write "  <TD COLSPAN=2 WIDTH=50% BGCOLOR=""FFCC00"">" 
    	 Document.Write "    <IMG SRC=""../graphics/blank2.gif"" WIDTH=27 HEIGHT=27>&nbsp;&nbsp;&nbsp;" 

	 Document.Write "    <FONT FACE=""verdana, arial, helvetica"" SIZE=2>" 
	 Document.Write "    <b>" + fullName + "</b>"
	 Document.Write "    </FONT>"

	 Document.Write "  </TD>"
    	 Document.Write "</TR>"
         '-----------Row End Here---------------------

	 '-----------Fill the Table Row ------------
	 Document.Write "<TR>"
    	 Document.Write "  <TD WIDTH=50% BGCOLOR=""FFCC00"">"
    	 Document.Write "    <FONT FACE=""verdana, arial, helvetica"" SIZE=2>"
    	 Document.Write "    <B>Email Address: </B>"
    	 Document.Write "    </FONT>"
	 Document.Write  "<BR><FONT SIZE=2 FACE=""arial, helvetica"">Email Address associated with the Outlook Profile<BR></FONT>"
	 Document.Write "  </TD>"

	

	 Document.Write "  <TD COLSPAN=2 WIDTH=50% BGCOLOR=""FFCC00"">" 
    	 Document.Write "    <IMG SRC=""../graphics/blank2.gif"" WIDTH=27 HEIGHT=27>&nbsp;&nbsp;&nbsp;" 

	 Document.Write "    <FONT FACE=""verdana, arial, helvetica"" SIZE=2>" 
	 Document.Write "    <b>" + rfc822Mailbox+ "</b>"
	 Document.Write "    </FONT>"

	 Document.Write "  </TD>"
    	 Document.Write "</TR>"    	   
        
         '-----------Row End Here---------------------

         '-----------Row End Here---------------------
    	 Document.Write "</TABLE>"

    	 'Document.Write "<!--END INPUT FIELD TABLE"

    	 Document.Write "</TD>"
    	 Document.Write "</TR>"
    	 Document.Write "</TABLE>"

         '----------- windows 2000 Features ---------------------
		 if ( win2kUPN <> "" OR useEFS = 1) then
			Document.Write "<P><BR><P>" 
    		Document.Write "<TABLE WIDTH=588 BGCOLOR=""ffffcc"" CELLPADDING=7 CELLSPACING=0 BORDER=0>"
			Document.Write "<TR>" 
			Document.Write "<TD WIDTH=588>"
			Document.Write "<FONT SIZE=2 FACE=""verdana, arial, helvetica""><B>Windows 2000 Additional"
			Document.Write " Features</B></FONT><BR><P>" 


    		Document.Write "<CENTER>" 
			Document.Write "<TABLE WIDTH=574 CELLPADDING=3 CELLSPACING=2 BORDER=0>"

			'-----------Fill the Table Row - UPN ------------
         

			if ( win2kUPN <> "" ) Then
          
				Document.Write "<TR>"
    			Document.Write "  <TD WIDTH=50% BGCOLOR=""FFCC00"">"
    			Document.Write "    <FONT FACE=""verdana, arial, helvetica"" SIZE=2>"
    			Document.Write "    <B>User Princial Name (UPN): </B>"
    			Document.Write "    </FONT>"
				Document.Write "<BR><FONT SIZE=2 FACE=""arial, helvetica"">You will be able to log on to a Windows 2000 based network via Client-Authentication.<BR></FONT>"
				Document.Write "  </TD>"

	

				Document.Write "  <TD COLSPAN=2 WIDTH=50% BGCOLOR=""FFCC00"">" 
    			Document.Write "    <IMG SRC=""../graphics/blank2.gif"" WIDTH=27 HEIGHT=27>&nbsp;&nbsp;&nbsp;" 

				Document.Write "    <FONT FACE=""verdana, arial, helvetica"" SIZE=2>" 
				Document.Write "    <b>" + win2kUPN+ "</b>"
				Document.Write "    </FONT>"

				Document.Write "  </TD>"
    			Document.Write "</TR>"    	   
       
			End If
		'-----------Row End Here---------------------
	     
    	
	  '-----------Fill the Row - EFS ------------
         

			if (  useEFS=1 ) Then
			
    			Document.Write "<TR>"
    			Document.Write "  <TD WIDTH=50% BGCOLOR=""FFCC00"">"
    			Document.Write "    <FONT FACE=""verdana, arial, helvetica"" SIZE=2>"
    			Document.Write "    <B>Encrypting File System (EFS): </B>"
    			Document.Write "    </FONT>"
				Document.Write "<BR><FONT SIZE=2 FACE=""arial, helvetica"">Windows 2000 security feature to secure file on disks.<BR></FONT>"
				Document.Write "  </TD>"

				Document.Write "  <TD COLSPAN=2 WIDTH=50% BGCOLOR=""FFCC00"">" 
    			Document.Write "    <IMG SRC=""../graphics/blank2.gif"" WIDTH=27 HEIGHT=27>&nbsp" 

				Document.Write "    <FONT FACE=""verdana, arial, helvetica"" SIZE=2>" 
				
				if ( isAdmin=1 ) Then
					Document.Write "<FONT SIZE=2 FACE=""arial, helvetica"">You can <B>encrypt</B>, <B>decrypt</B> files"
					Document.Write " and &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<B>recover</B> encrypted files on disks.<BR></Font>"
				else
					Document.Write "<FONT SIZE=2 FACE=""arial, helvetica"">You can <B>encrypt</B>, "
					Document.Write "and <B>decrypt</B> files on &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;disks.<BR></Font>"
				End if
                Document.Write "  </TD>"
    			Document.Write "</TR>"    	   
			End if
        Document.Write "</TABLE>"
		Document.Write "</TD>"
    	Document.Write "</TR>"
    	Document.Write "</TABLE>"
		'----------- Table End Here ---------------
        End if

	End Sub
	
        Sub GetDisplayMBI
	    SetVars
        End Sub
-->
</SCRIPT>
<!-- VSSKENDPOLICYVAL#yes#41 -->

<!-- VSSKBEGINPOLICYVAL#yes#42 -->
<SCRIPT LANGUAGE="VBScript">
       Call GetDisplayMBI
</SCRIPT>
<!-- VSSKENDPOLICYVAL#yes#42 -->

<!-- VSSKBEGINPOLICYVAL#yes#43 -->
<SCRIPT LANGUAGE="VBScript">
       Call ShowFullNameEmailAddress
 </SCRIPT>
<!-- VSSKENDPOLICYVAL#yes#43 -->

<!-- VSSKBEGINPOLICYVAL#yes#44 -->
<SCRIPT LANGUAGE=VBSCRIPT>
 
  Sub SetServerInfo
	
	Dim  str,OrgName,rdn,Pos,Quote,DN,ProfileName,ProfileServer,distinguishedName,ExchangeVer,UserDN
	Dim  AccessRight,ExchProfile,MsgStr,tmpDN,ExchVerStr,ADSInfo,LdapDN

        '-- VSSKBEGIN Global/System#17 --
        '-- VSSKEND Global/System#17 --	

	On Error Resume Next	
	    IGSE.UpdateClientExt	
	    If err.number <> 0 Then
	    		Select Case CStr(Hex(err.number))
			Case "80070020"
				MsgBox "Unable to update Go Secure! for Exchange Outlook Client Extension. Please close all Outlook windows and start the certificate enrollment again. "
				Call StopIt()
				window.navigate("../digitalidCenter.htm")	 
			  exit Sub
			Case "1B6"
				Call SetErrorInfo2("../fdf/VSApps/client/ExchangeErrors.fdf", "00000024", CStr(Hex(err.number)),"Certificate Pickup")  
	     	   	exit Sub	
	
			End Select	
	    End If	
	
	 'These three function must be needed before you call any function related to the mailbox properties
	 'such as FullName,mailDN,HomeServer...etc.
             
		
	IGSE.CAInfo=%%ConnectionAgreementType%%	 
	On Error Resume Next	
	ADSInfo=%%ADSInfo%% 
			
	On Error Resume Next	
	IGSE.ADServerInfo=ADSInfo
 	IGSE.ADServerInfoList="%%ADSInfoList%%"
     
        


	AccessRight=1        
        On Error Resume Next
 	str=IGSE.UserDN
	
	'-----------error checking----------------------
            If err.number <> 0 Then
                   Select Case 	CStr(Hex(err.number))
 		   Case "8007003A"
			Call SetErrorInfo2("../fdf/VSApps/client/ExchangeErrors.fdf", "0000000d", CStr(Hex(err.number)),"Certificate Pickup")  
	     	   	exit Sub	
		   Case "80070020"
			Call SetErrorInfo2("../fdf/VSApps/client/ExchangeErrors.fdf", "0000000A", CStr(Hex(err.number)),"Certificate Pickup")  
	     	   	exit Sub
		   Case "80070031"
			Call SetErrorInfo2("../fdf/VSApps/client/ExchangeErrors.fdf", "00000011", CStr(Hex(err.number)), "Certificate Pickup") 
			exit Sub	
         	   Case "80070032"
			Call SetErrorInfo2("../fdf/VSApps/client/ExchangeErrors.fdf", "0000000F", CStr(Hex(err.number)), "Certificate Pickup") 
			exit Sub	
		   Case "8007274d"
			Call SetErrorInfo2("../fdf/VSApps/client/ExchangeErrors.fdf", "00000022", CStr(Hex(err.number)), "Certificate Pickup") 
			exit Sub
			
			Case "80008004"
			Call SetErrorInfo2("../fdf/VSApps/client/ExchangeErrors.fdf", "00000038", CStr(Hex(err.number)), "Certificate Pickup") 
			exit Sub	
		   
		   End Select
            End If
	   
 	    If Len(str)=0  Then
		 Msgstr="You have to select same Outlook Exchange profile which you have selected during Certificate Enrollment." & chr(13)&_
			"Press OK to select Outlook Exchange profile or Press CANCEL to abort certificate pick up process."  
		RetVal=MsgBox (MsgStr,1)	  
		
		If RetVal=1 Then	
			ExchProfile=0	
			while ExchProfile=0	
	 			On Error Resume Next 
			  	IGSE.PromptForSelection
                           	' ---------------------------------	
			   	If err.number <> 0 Then
                   			Select Case 	CStr(Hex(err.number))
		 			Case "80070031"
						Call SetErrorInfo2("../fdf/VSApps/client/ExchangeErrors.fdf", "00000011", CStr(Hex(err.number)), "Certificate Pickup") 
						exit Sub	
		 			Case "80070032"
						Call SetErrorInfo2("../fdf/VSApps/client/ExchangeErrors.fdf", "0000000F", CStr(Hex(err.number)), "Certificate Pickup") 
						exit Sub	
		 			Case "8007003A"
						Call SetErrorInfo2("../fdf/VSApps/client/ExchangeErrors.fdf", "0000000d", CStr(Hex(err.number)), "Certificate Pickup") 
						exit Sub	
		   			Case "80070020"
						Call SetErrorInfo2("../fdf/VSApps/client/ExchangeErrors.fdf", "0000000A", CStr(Hex(err.number)), "Certificate Pickup")  
	     	   				exit Sub	
					case "80040111"
						window.navigate("../digitalidCenter.htm")
						exit Sub
		   			case "80040113"
						Call SetErrorInfo2("../fdf/VSApps/client/ExchangeErrors.fdf", "0000000E", CStr(Hex(err.number)),"Certificate Pickup")
 						exit Sub
					Case "8007274d"
						Call SetErrorInfo2("../fdf/VSApps/client/ExchangeErrors.fdf", "00000022", CStr(Hex(err.number)), "Certificate Pickup") 
					exit Sub	
					case  "80070032"
						MsgBox "You don't have the rights to modify the properties of the mailbox associated with this Outlook profile."
					case Else
						MsgBox "An unknown error occured while obtaining your information from the mailbox identified by the selected Outlook profile." & chr(13) &_
					"The error number is : 0x" & CStr(Hex(err.number))			
						ExchProfile=1
						Call StopIt()
						window.navigate("../digitalidCenter.htm")
						exit Sub
		   			End Select
			   	Else
	 		 		On Error Resume Next 
			   		fullName = IGSE.FullName
			   		if Len(fullName)=0 Then
	     					MsgBox "Select exchange enabled profile."
		    	   		else
						ExchProfile=1
			   		End If
            		   	End If
			wend
		   Else
			Call StopIt()
			window.navigate("../digitalidCenter.htm")	
			exit Sub	
		   End IF		
	    End If		   	            	

	'-------------End here------------------------- 


	On Error Resume Next
        ExchangeVer=IGSE.ExchangeVer
	if err.number<> 0 then
		Call SetErrorInfo2("../fdf/VSApps/client/ExchangeErrors.fdf", "00000022", CStr(Hex(err.number)), "Certificate 											Enrollment")
     		exit sub
        end if
	if ExchangeVer=-1 then	
		ExchVerStr=IGSE.ExchangeVerString	
		Call SetErrorInfo2("../fdf/VSApps/client/ExchangeErrors.fdf", "00000021", ExchVerStr, "Certificate 														Enrollment")
		exit sub
	 end if





	distinguishedName=IGSE.UserDN
	ProfileServer=IGSE.ProfileServer
	exch_srvr=IGSE.ExchServer
	ProfileName=IGSE.ProfileName

	LdapDN=distinguishedName
	ExchVerStr=IGSE.ExchangeVerString
	
	If ( ProfileServer = "" OR ProfileName = "" OR distinguishedName = "" ) Then
	      Call SetErrorInfo2("../fdf/VSApps/client/ExchangeErrors.fdf", "0000001F", CStr(Hex(err.number)),"Certificate Pickup")
	      exit Sub
	End If                  

	tmpDN = ""
        For i = 1 to Len(distinguishedName)
        If Mid(distinguishedName,i,1) = """" then
	  tmpDN = tmpDN & """" &""""		
        Else
          tmpDN = tmpDN & Mid(distinguishedName,i,1)
        End If
        Next
        Document.proform.exchange_DN.value = tmpDN

	Document.proform.exchange_ServerName.value=ProfileServer
	Document.proform.exch_Srvr.value=exch_srvr
	Document.proform.exchange_Version.value=ExchangeVer					
	Document.proform.ldap_DN.value = LdapDN
	Document.proform.exchange_VerString.value=ExchVerStr					
	Document.proform.exchange_ProfileName.value=ProfileName	
  End Sub

</SCRIPT>

<!-- VSSKENDPOLICYVAL#yes#44 -->

<!-- VSSKBEGINPOLICYVAL#yes#45 -->
<SCRIPT LANGUAGE=VBSCRIPT>
     Call SetServerInfo
</SCRIPT>
<!-- VSSKENDPOLICYVAL#yes#45 -->

<!-- VSSKBEGINPOLICYVAL#yes#46 -->
###############################################################
# Exchange Server configuration
#
# EXCHANGE_SERVER	%%Apps/GSE::ExchangeServerName%%
# EXCHANGE_DOMAIN	%%Apps/GSE::ExchangeOrgName%%
#
###############################################################
<!-- VSSKENDPOLICYVAL#yes#46 -->

<!-- VSSKBEGINPOLICYVAL#yes#47 -->
<SCRIPT LANGUAGE=VBSCRIPT>
  Dim ExchangeIntegration
  ExchangeIntegration = 1
</SCRIPT>
<!-- VSSKENDPOLICYVAL#yes#47 -->

<!-- VSSKBEGINPOLICYVAL#yes#48 -->
  <!-- VSSKBEGIN Global/Mode#41 -->
  <!-- VSSKEND Global/Mode#41 -->
<!-- VSSKENDPOLICYVAL#yes#48 -->

<!-- VSSKBEGINPOLICYVAL#yes#49 -->
  <!-- VSSKBEGIN Global/Mode#109 -->
  <!-- VSSKEND Global/Mode#109 -->
<!-- VSSKENDPOLICYVAL#yes#49 -->

<!-- VSSKBEGINPOLICYVAL#yes#50 -->
<P><BR><P><P><BR><P>
<CENTER>
<TABLE WIDTH=588 BGCOLOR="ffffff" CELLPADDING=0 CELLSPACING=0 BORDER=0>
<TR>
	<TD WIDTH=588 COLSPAN=7><FONT COLOR="0000cc" FACE="verdana, arial, helvetica" SIZE=5><B>Please wait while  ...</FONT> <P><BR><P></TD>
</TR>

<TR>
	<TD WIDTH=588 COLSPAN=7><FONT COLOR="0000cc" FACE="verdana, arial, helvetica" SIZE=4><B>The Digital ID is being   Installed.</B></FONT> <P><BR><P></TD>
</TR>

<TR>
	<TD WIDTH=588 COLSPAN=7><FONT COLOR="0000cc" FACE="verdana, arial, helvetica" SIZE=4><B>The Digital ID is being published to GAL.</B></FONT><P><BR><P></TD>
</TR>

<TR>
	<TD WIDTH=588 COLSPAN=7><FONT COLOR="0000cc" FACE="verdana, arial, helvetica" SIZE=4><B>Outlook is being configured. </B></FONT><P><BR><P></TD>
</TR>
</TABLE>
<!-- VSSKENDPOLICYVAL#yes#50 -->

<!-- VSSKBEGINPOLICYVAL#yes#60#2.0.0.0 -->
<Script Language="VBScript">
<!--
   Dim userDN, encUserCertificate, encUserSMIMECertificate
   Dim exchangeServerName, SessionId, ChallengePh, ExchangeVer
   Dim UseAuthUpdate,CertChainBlob

Sub ServerUpdate
  '-- VSSKBEGIN Global/System#17 --
  '-- VSSKEND Global/System#17 --

   userDN = "$$userDN$$"
   exchangeServerName = "$$exchange_ServerName$$"
   ExchangeVer ="$$exchange_Version$$"
   SessionId="$$SessionID$$"
   ChallengePh="$$ChallengePhrase$$"
   CertChainBlob="$$CertChainblob$$"
   UseAuthUpdate="$$Use_AuthUpdate$$"
  
   On Error Resume Next
   
   ISignAtrb.ChallengePhrase = ChallengePh
   If err.number <> 0 Then
     Select Case CStr(Hex(err.number))
     Case "1B6"
		Call SetErrorInfo2("../fdf/VSApps/client/ExchangeErrors.fdf", "00000035", CStr(Hex(err.number)),"Certificate Publish Status")  
	       	exit Sub	
     Case else
	     Call SetErrorInfo2("../../fdf/VSApps/client/ExchangeErrors.fdf", 00000005, CStr(Hex(err.number)), "Certificate Publish Status")
    	     exit sub
     End Select
   End If
     
   
   On Error Resume Next
   
   ISignAtrb.UserCertificate = CertChainBlob

   If err.number <> 0 Then
     
     Call SetErrorInfo2("../fdf/VSApps/client/ExchangeErrors.fdf", 00000005, CStr(Hex(err.number)), "Certificate Publish Status")
     exit sub
   End If

   On Error Resume Next
      encUserCertificate = ISignAtrb.EncUserCertificate
   If err.number <> 0 Then
  
     Call SetErrorInfo2("../fdf/VSApps/client/ExchangeErrors.fdf", 00000006, CStr(Hex(err.number)), "Certificate Publish Status")
     exit sub
   End If

   On Error Resume Next

   encUserSMIMECertificate = ISignAtrb.AuthEncUserSMIMECertificate
   If err.number <> 0 Then
        Call SetErrorInfo2("../fdf/VSApps/client/ExchangeErrors.fdf", 00000007, CStr(Hex(err.number)), "Certificate Publish Status")
     exit sub
   End If

   document.Stuff.userCertificate.value = encUserCertificate
   document.Stuff.userSMIMECertificate.value = encUserSMIMECertificate
   document.Stuff.userDN.value = userDN
   document.Stuff.Use_AuthUpdate.value =UseAuthUpdate 	
   document.Stuff.ExchangeServerName_BOTH.value =exchangeServerName
   document.Stuff.ExchangeVersion.value =ExchangeVer
   document.Stuff.SessionID.value =SessionId
   document.Stuff.ChallengePhrase.value =ChallengePh
   Call StopIt()
   document.Stuff.submit
   document.close

End Sub


'-->
</Script>
<!-- VSSKENDPOLICYVAL#yes#60 -->

<!-- VSSKBEGINPOLICYVAL#yes#61 -->
<FORM NAME="Stuff" ACTION="../cgi-bin/VSApps/srchexce.exe?Type=Stuff" ENCTYPE=x-www-form-encoded METHOD=POST>
        <INPUT TYPE="HIDDEN" NAME="userDN" VALUE="">
	<INPUT TYPE="HIDDEN" NAME="Use_AuthUpdate" VALUE="">
	<INPUT TYPE="HIDDEN" NAME="ExchangeServerName_BOTH" VALUE="">
	<INPUT TYPE="HIDDEN" NAME="ExchangeVersion" VALUE="">
	<INPUT TYPE="HIDDEN" NAME="SessionID" VALUE="">
	<INPUT TYPE="HIDDEN" NAME="ChallengePhrase" VALUE="">
	<INPUT TYPE="HIDDEN" NAME="userCertificate" VALUE="">
	<INPUT TYPE="HIDDEN" NAME="userSMIMECertificate" VALUE="">
	
</FORM>

<Script Language="VBScript">
<!--
        Call ServerUpdate
'-->
</Script>
<!-- VSSKENDPOLICYVAL#yes#61 -->

<!-- VSSKBEGINPOLICYVAL#yes#62#2.0.0.0 -->

    On Error Resume Next
    IGSE.CertFriendlyName=sz10
	If err.number <> 0 Then
		Select Case CStr(Hex(err.number))
		Case "1B6"
			Call SetErrorInfo2("../fdf/VSApps/client/ExchangeErrors.fdf", "00000024", CStr(Hex(err.number)),"Certificate Installation")  
	     	   	exit Sub	
		End Select
	End If
<!-- VSSKENDPOLICYVAL#yes#62# -->

<!-- VSSKBEGINPOLICYVAL#yes#63#2.0.0.0 -->

	On Error Resume Next
	Policy_useEFS="%%use_EFS%%"
    if Policy_useEFS = "" OR Policy_useEFS = "0" then
          IGSE.SetEFSCertificate=0
    else
          IGSE.SetEFSCertificate=1
    end if

    On Error Resume Next
    IGSE.CertFriendlyName=CertChain
	If err.number <> 0 Then
		Select Case CStr(Hex(err.number))
		Case "1B6"
			Call SetErrorInfo2("../fdf/VSApps/client/ExchangeErrors.fdf", "00000024", CStr(Hex(err.number)),"Certificate Installation")  
	     	   	exit Sub	
		End Select
	End If
<!-- VSSKENDPOLICYVAL#yes#63 -->

<!-- VSSKBEGINPOLICYVAL#yes#64 -->
exchange_alias        CLEAR     MANDATORY                NONE    NONE
exchange_userName     T61    MANDATORY                NONE    NONE
common_name           T61    MANDATORY                NONE    NONE
san_common_name       T61    MANDATORY                NONE    NONE
exchange_DN           T61    MANDATORY                NONE    NONE
ldap_DN				  T61    MANDATORY                NONE    NONE
cert_DN               T61    MANDATORY                NONE    NONE
exchange_ServerName   CLEAR  MANDATORY                NONE    NONE
exch_Srvr			  CLEAR  MANDATORY                NONE    NONE
exchange_Version      CLEAR  MANDATORY                NONE    NONE
exchange_VerString    CLEAR  MANDATORY                NONE    NONE
exchange_ProfileName  T61    MANDATORY                NONE    NONE
win2k_upn             CLEAR  OPTIONAL                 NONE    NONE
win2k_efs_eku         CLEAR  OPTIONAL                 NONE    NONE
<!-- VSSKENDPOLICYVAL#yes#64 -->

<!-- VSSKBEGINPOLICYVAL#yes#65 -->
<SCRIPT LANGUAGE=VBSCRIPT>
 
 Dim  CertSerialNumber
' Start Add : Infosys : CR21582 -->
'-- VSSKBEGIN Apps/GSE#71 --
'-- VSSKEND Apps/GSE#71 --	
' End Add : Infosys : CR21582 -->
   

  Sub SetServerInfo
	
	Dim  str,OrgName,rdn,Pos,Quote,DN,ProfileName,ProfileServer,distinguishedName,ExchangeVer,UserDN
	Dim  AccessRight,ExchProfile,MsgStr,tmpDN,ExchVerStr,ADSInfo,LdapDN

        '-- VSSKBEGIN Global/System#17 --
        '-- VSSKEND Global/System#17 --	

	
	 'These three function must be needed before you call any function related to the mailbox properties
	 'such as FullName,mailDN,HomeServer...etc.
             
		
	  IGSE.CAInfo=%%ConnectionAgreementType%%	 
	 On Error Resume Next	
	 ADSInfo=%%ADSInfo%% 
			
	 On Error Resume Next	
	 IGSE.ADServerInfo=ADSInfo
 	 IGSE.ADServerInfoList="%%ADSInfoList%%"
	 IGSE.RenewCert=1
           


	AccessRight=1        
    On Error Resume Next
 	str=IGSE.UserDN
	
	'-----------error checking----------------------
            If err.number <> 0 Then
                   Select Case 	CStr(Hex(err.number))
 		   Case "8007003A"
			Call SetErrorInfo2("../fdf/VSApps/client/ExchangeErrors.fdf", "0000000d", CStr(Hex(err.number)),"Certificate Renewal")  
	     	   	exit Sub	
		   Case "80070020"
			Call SetErrorInfo2("../fdf/VSApps/client/ExchangeErrors.fdf", "0000000A", CStr(Hex(err.number)),"Certificate Renewal")  
	     	   	exit Sub
		   Case "80070031"
			Call SetErrorInfo2("../fdf/VSApps/client/ExchangeErrors.fdf", "00000011", CStr(Hex(err.number)), "Certificate Renewal") 
			exit Sub	
         	   Case "80070032"
			Call SetErrorInfo2("../fdf/VSApps/client/ExchangeErrors.fdf", "0000000F", CStr(Hex(err.number)), "Certificate Renewal") 
			exit Sub	
		   Case "8007274d"
			Call SetErrorInfo2("../fdf/VSApps/client/ExchangeErrors.fdf", "00000022", CStr(Hex(err.number)), "Certificate Renewal") 
			exit Sub

			Case "80008004"
			Call SetErrorInfo2("../fdf/VSApps/client/ExchangeErrors.fdf", "00000038", CStr(Hex(err.number)), "Certificate Renewal") 
			exit Sub	
			
				
		   
		   End Select
            End If
	   
 	    If Len(str)=0  Then
		 Msgstr="You have to select same Outlook Exchange profile which you have selected during Certificate Enrollment." & chr(13)&_
			"Press OK to select Outlook Exchange profile or Press CANCEL to abort certificate pick up process."  
		RetVal=MsgBox (MsgStr,1)	  
		
		If RetVal=1 Then	
			ExchProfile=0	
			while ExchProfile=0	
	 			On Error Resume Next 
			  	IGSE.PromptForSelection
                           	' ---------------------------------	
			   	If err.number <> 0 Then
                   			Select Case 	CStr(Hex(err.number))
		 			Case "80070031"
						Call SetErrorInfo2("../fdf/VSApps/client/ExchangeErrors.fdf", "00000011", CStr(Hex(err.number)), "Certificate Renewal") 
						exit Sub	
		 			Case "80070032"
						Call SetErrorInfo2("../fdf/VSApps/client/ExchangeErrors.fdf", "0000000F", CStr(Hex(err.number)), "Certificate Renewal") 
						exit Sub	
		 			Case "8007003A"
						Call SetErrorInfo2("../fdf/VSApps/client/ExchangeErrors.fdf", "0000000d", CStr(Hex(err.number)), "Certificate Renewal") 
						exit Sub	
		   			Case "80070020"
						Call SetErrorInfo2("../fdf/VSApps/client/ExchangeErrors.fdf", "0000000A", CStr(Hex(err.number)), "Certificate Renewal")  
	     	   				exit Sub	
					case "80040111"
						window.navigate("../digitalidCenter.htm")
						exit Sub
		   			case "80040113"
						Call SetErrorInfo2("../fdf/VSApps/client/ExchangeErrors.fdf", "0000000E", CStr(Hex(err.number)),"Certificate Renewal")
 						exit Sub
					Case "8007274d"
						Call SetErrorInfo2("../fdf/VSApps/client/ExchangeErrors.fdf", "00000022", CStr(Hex(err.number)), "Certificate Renewal") 
					exit Sub	
					case  "80070032"
						MsgBox "You don't have the rights to modify the properties of the mailbox associated with this Outlook profile."
					case Else
						MsgBox "An unknown error occured while obtaining your information from the mailbox identified by the selected Outlook profile." & chr(13) &_
					"The error number is : 0x" & CStr(Hex(err.number))			
						ExchProfile=1
						Call StopIt()
						window.navigate("../digitalidCenter.htm")
						exit Sub
		   			End Select
			   	Else
	 		 		On Error Resume Next 
			   		fullName = IGSE.FullName
			   		if Len(fullName)=0 Then
	     					MsgBox "Select exchange enabled profile."
		    	   		else
						ExchProfile=1
			   		End If
            		   	End If
			wend
		   Else
			Call StopIt()
			window.navigate("../digitalidCenter.htm")	
			exit Sub	
		   End IF		
	    End If		   	            	

	'-------------End here------------------------- 


	On Error Resume Next
        ExchangeVer=IGSE.ExchangeVer
	if err.number<> 0 then
		Call SetErrorInfo2("../fdf/VSApps/client/ExchangeErrors.fdf", "00000022", CStr(Hex(err.number)), "Certificate Renewal")
     		exit sub
        end if
	if ExchangeVer=-1 then	
		ExchVerStr=IGSE.ExchangeVerString	
		Call SetErrorInfo2("../fdf/VSApps/client/ExchangeErrors.fdf", "00000021", ExchVerStr, "Certificate 	Renewal")
		exit sub
	 end if





	distinguishedName=IGSE.UserDN   
	ProfileServer=IGSE.ProfileServer
	ProfileName=IGSE.ProfileName
	exch_srvr=IGSE.ExchServer
	CertSerialNumber=IGSE.CertSerialNum

	LdapDN=distinguishedName
	ExchVerStr=IGSE.ExchangeVerString
	
	If ( ProfileServer = "" OR ProfileName = "" OR distinguishedName = "" ) Then
	      Call SetErrorInfo2("../fdf/VSApps/client/ExchangeErrors.fdf", "0000001F", CStr(Hex(err.number)),"Certificate Renewal")
	      exit Sub
	End If                  

	tmpDN = ""
        For i = 1 to Len(distinguishedName)
        If Mid(distinguishedName,i,1) = """" then
	  tmpDN = tmpDN & """" &""""		
        Else
          tmpDN = tmpDN & Mid(distinguishedName,i,1)
        End If
        Next
        Document.theform.exchange_DN.value = tmpDN

	Document.theform.exchange_ServerName.value=ProfileServer
	Document.theform.exch_Srvr.value=exch_srvr
	Document.theform.exchange_Version.value=ExchangeVer	
	Document.theform.ldap_DN.value = LdapDN
	Document.theform.exchange_VerString.value=ExchVerStr				
	Document.theform.exchange_ProfileName.value=ProfileName	


	' Start Add : Infosys: CR21582 -->
	'-- VSSKBEGIN Apps/GSE#70 --
	'-- VSSKEND Apps/GSE#70 --	
	' End Add : Infosys: CR21582 -->

  End Sub

</SCRIPT>

<!-- VSSKENDPOLICYVAL#yes#65 -->

<!-- VSSKBEGINPOLICYVAL#yes#66 -->
  On Error Resume Next
  If (Len(CertSerialNumber) <> 0) then
      IVSSrchCrit.SerNum = CertSerialNumber
      If ( err.number <> 0 ) then
        Call CloseObjects(Hex(err.number), "Renewal::IVSSrchCrit.CertSerialNumber", Hex(err.number))
        Exit Sub
      End If
  End If
<!-- VSSKENDPOLICYVAL#yes#66 -->

<!-- VSSKBEGINPOLICYVAL#yes#67 -->
exchange_DN        		T61     MANDATORY                NONE    NONE
ldap_DN        			T61     MANDATORY                NONE    NONE
exchange_ServerName		CLEAR     MANDATORY              NONE    NONE
exch_Srvr		  		CLEAR     MANDATORY              NONE    NONE
exchange_Version  		CLEAR     MANDATORY              NONE    NONE
exchange_VerString		CLEAR     MANDATORY              NONE    NONE
exchange_ProfileName  	T61     MANDATORY                NONE    NONE

<!-- VSSKENDPOLICYVAL#yes#67 -->

<!-- VSSKBEGINPOLICYVAL#yes#68 -->
<input type=hidden name=common_name value="">
<input type=hidden name=cert_DN value="">
<input type=hidden name=win2k_upn value="">
<input type=hidden name=win2k_efs_eku value="">
<!-- VSSKENDPOLICYVAL#yes#68 -->

<!-- VSSKBEGINPOLICYVAL#yes#69 -->
common_name  	  CLEAR     MANDATORY         NONE    NONE
cert_DN		      CLEAR     MANDATORY         NONE    NONE
win2k_upn         CLEAR     OPTIONAL          NONE    NONE
win2k_efs_eku     CLEAR     OPTIONAL          NONE    NONE
<!-- VSSKENDPOLICYVAL#yes#69 -->

<!-- VSSKBEGINPOLICYVAL#yes#70 -->
	call ExchangeDNFormat
	call SetEfsUpnFlag
<!-- VSSKENDPOLICYVAL#yes#70 -->

<!-- VSSKBEGINPOLICYVAL#yes#71 -->

' Below gets (GetCertAuthMethod) the authentication configuration whether its manual, passcode or autoauth.

'-- VSSKBEGIN Global/System#12 --
'-- VSSKEND Global/System#12 --	

 ' In case of renewal user common name is not being passed to backend because of this the search
 ' result shows "Recipients" as common name for all the renewed certificates.
 ' Code below sets the user common_name and cert_DN parameters to be sent to the backend to fix above.
 
 Dim Alias, fullName, companyName, Trunc, SanName, ExchRDN, distName, Pos, certDN, x, gcharEncoding
 Dim AuthMethod, tempDN
 gcharEncoding="%%Enrollment/CharEncoding::policyValue%%"

 Sub  ExchangeDNFormat

 	Alias=IGSE.Alias
	fullName = IGSE.FullName

	companyName = ", %%::corpName%%"
    	Trunc = Alias + " (" + fullName + companyName
    	Trunc = Left(Trunc, 62)
    	Trunc = Trunc + ")"

	    SanName="CN = "+fullName	
   	    Document.theform.common_name.value = Trunc 
		
		if(gCharEncoding="exists")then
			IGSE.CharEncodingInfo=1
        else
			IGSE.CharEncodingInfo=0
        End if  

		ExchRDN=IGSE.explode_DN
    
	    for x= LBound(ExchRDN) to UBound(ExchRDN)
			distName=distName+ExchRDN(x)
			if(x < UBound(ExchRDN)) then
				distName=distName+","
			end if
	    
    	next
	   
		Pos = Instr(distName, ",")
        certDN =Right(distName,len(distName)-Pos)	
	    	if(gCharEncoding="exists")then
				certDN="cn=" +"<0C>"+ """" + Trunc + """" + "," + certDN
		else
				certDN="cn=" + """" + Trunc + """" + "," + certDN
		End if
	    
		AuthMethod = GetCertAuthMethod

		if ( AuthMethod = "passcode" ) then
		' Treat it as passcode auth only
		      tmpDN = ""
		      For i = 1 to Len(certDN)
			If Mid(certDN,i,1) = """" then
			   tmpDN = tmpDN & """"	
			Else
			  tmpDN = tmpDN & Mid(certDN,i,1)
			End If
		      Next
		      Document.theform.cert_DN.value = tmpDN
		elseif ( AuthMethod = "manual" )then
		      ' Treat it as Manual auth only
		      Document.theform.cert_DN.value = certDN
		else
		      ' Treat it as Auto Auth
		      tmpDN = ""
		      For i = 1 to Len(certDN)
			If Mid(certDN,i,1) = """" then
			  tmpDN = tmpDN & "&#34;"
			Else
			  tmpDN = tmpDN & Mid(certDN,i,1)
			End If
		      Next
		      Document.theform.cert_DN.value = tmpDN
	        end if
		
 End Sub

 ' Start Add : Infosys : CR28330
 Dim win2kUPN, useUPN, Policy_useUPN, useEFS, Policy_useEFS, isAdmin

 Sub SetEfsUpnFlag

	 '----- Windows 2000 UPN
        Policy_useUPN="%%use_UPN%%"
        if Policy_useUPN = "" or Policy_useUPN = "0" then
          useUPN = 0
        else
          useUPN = 1
        end if

        if useUPN=1 then	
          win2kUPN=IGSE.UserPrincipalName
        else  
          win2kUPN = ""
        end if

	Document.theform.win2k_upn.value = win2kUPN

       '----- Windows 2000 EFS

        Policy_useEFS="%%use_EFS%%"
        if Policy_useEFS = "" OR Policy_useEFS = "0" then
          useEFS = 0
        else
          useEFS = 1
        end if

        if useEFS=1 then	
          isAdmin=IGSE.IsUserMemberOfAdminGroup
          if (isAdmin=1) then
			Document.theform.win2k_efs_eku.value="ra"
		  else
			Document.theform.win2k_efs_eku.value="user"
		  end if
        end if

 End Sub

 ' End Add : Infosys : CR28330

<!-- VSSKENDPOLICYVAL#yes#71 -->

<!-- VSSKBEGINPOLICYVAL#yes#72 -->

     Dim  ADSInfo

     IGSE.CAInfo=%%ConnectionAgreementType%%	
     On Error Resume Next		
     ADSInfo=%%ADSInfo%% 
 
     On Error Resume Next			
     IGSE.ADServerInfo=ADSInfo 
     IGSE.ADServerInfoList="%%ADSInfoList%%"

<!-- VSSKENDPOLICYVAL#yes#72 -->

<!-- VSSKBEGINPOLICYVAL#yes#73 -->
<!-- Infosys :CR21346 :these are exchange integration specific variables for Roaming -->
<input type=hidden name=mail_firstName value="">
<input type=hidden name=mail_lastName value="">
<!-- VSSKENDPOLICYVAL#yes#73 -->

<!-- VSSKBEGINPOLICYVAL#yes#74 -->
<SCRIPT Language="VBScript">
<!--

     Dim dummyObj
	 On Error Resume Next
	 Set dummyObj=IGSE.ExchangeVer
	 If ( (Hex(err.number) = "1B6") AND (InStr(1,navigator.appMinorVersion,";SP2;") > 0)  ) Then
         window.location = "./client/installComponentForSP2.htm"
     End if
-->
</SCRIPT>
<!-- VSSKENDPOLICYVAL#yes#74 -->

<!-- VSSKBEGINPOLICYVAL#yes#75 -->
<SCRIPT Language="VBScript">
<!--
	Dim phrase 
	On Error Resume Next
	 Set phrase = ISignAtrb.ChallengePhrase
     If ( (Hex(err.number) = "1B6") AND (InStr(1,navigator.appMinorVersion,";SP2;") > 0)  ) Then
         window.location = "./client/installComponentForSP2.htm"
     End if
-->
</SCRIPT>
<!-- VSSKENDPOLICYVAL#yes#75 -->

<!-- VSSKBEGINPOLICYVAL#yes#76 -->
try{
	dummy=IGSE.getName();
	temp = 1;
}catch(er){
	temp=0;
	window.open("../vsapps/error/win2k.htm","_self");
}
<!-- VSSKENDPOLICYVAL#yes#76 -->

<!-- VSSKBEGINPOLICYVAL#yes#77 -->
try{
	dummy=ISignAtrb.getName();
	temp = 1;
}catch(er){
	temp=0;
	window.open("../vsapps/error/win2k.htm","_self");
}
<!-- VSSKENDPOLICYVAL#yes#77 -->

<!-- VSSKBEGINPOLICYVAL#yes#78 -->
  <!-- VSSKBEGIN Global/Mode#127 -->
  <!-- VSSKEND Global/Mode#127 -->
<!-- VSSKENDPOLICYVAL#yes#78 -->

<!-- VSSKBEGINPOLICYVAL#yes#79 -->
  <!-- VSSKBEGIN Global/Mode#129 -->
  <!-- VSSKEND Global/Mode#129 -->
<!-- VSSKENDPOLICYVAL#yes#79 -->

<!-- VSSKBEGINPOLICYVAL#yes#80 -->
<!-- VSSKBEGIN Global/Mode#17 -->
<!-- VSSKEND Global/Mode#17 -->
<!-- VSSKENDPOLICYVAL#yes#80 -->

<!-- VSSKBEGINPOLICYVAL#yes#81 -->
<!-- VSSKBEGIN Global/Mode#123 -->
<!-- VSSKEND Global/Mode#123 -->
<!-- VSSKENDPOLICYVAL#yes#81 -->

<!-- VSSKBEGINPOLICYVAL#yes#82 -->
<!-- VSSKBEGIN Enrollment/CertStore#37 -->
<!-- VSSKEND Enrollment/CertStore#37 -->
<!-- VSSKENDPOLICYVAL#yes#82 -->

<!-- VSSKBEGINPOLICYVAL#yes#82 -->
<!-- VSSKBEGIN Enrollment/CertStore#38 -->
<!-- VSSKEND Enrollment/CertStore#38 -->
<!-- VSSKENDPOLICYVAL#yes#82 -->

<!-- VSSKBEGINPOLICYVAL#yes#83 -->
<!-- VSSKBEGIN Global/Mode#123 -->
<!-- VSSKEND Global/Mode#123 -->
<!-- VSSKENDPOLICYVAL#yes#83 -->

<!-- VSSKBEGINPOLICYVAL#yes#84 -->
<!-- VSSKBEGIN Global/Mode#126 -->
<!-- VSSKEND Global/Mode#126 -->
<!-- VSSKENDPOLICYVAL#yes#84 -->

<!-- VSSKBEGINPOLICYVAL#yes#85 -->
<!-- VSSKBEGIN Enrollment/CertStore#39 -->
<!-- VSSKEND Enrollment/CertStore#39 -->
<!-- VSSKENDPOLICYVAL#yes#85 -->

<!-- VSSKBEGINPOLICYVAL#yes#86 -->
<!-- VSSKBEGIN Global/Mode#101 -->
<!-- VSSKEND Global/Mode#101 -->
<!-- VSSKENDPOLICYVAL#yes#86 -->

<!-- VSSKBEGINPOLICYVAL#yes#87 -->
<!-- VSSKBEGIN Global/Mode#125 -->
<!-- VSSKEND Global/Mode#125 -->
<!-- VSSKENDPOLICYVAL#yes#87 -->
