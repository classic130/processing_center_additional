
<!-- VSSKBEGINPOLICYVAL#enabled#1 -->
<script language="JavaScript">;
if ("%%saveLocal%%" == "user")
{
document.write("<TABLE WIDTH=588 BGCOLOR=\"ffffcc\" CELLPADDING=7 CELLSPACING=0 BORDER=0>");
document.writeln("<TR>");
document.writeln("<TD WIDTH=588>");
document.writeln("<font size=2 face=\"verdana, arial, helvetica\"><B> Is This Your Computer?</B></FONT><BR>");
document.writeln("<P>");
document.writeln("<CENTER>");
document.writeln("       <TABLE WIDTH=574 CELLPADDING=3 CELLSPACING=2 BORDER=0>");
document.writeln("        <TR>");
document.writeln("                <TD WIDTH=50% BGCOLOR=\"ffcc00\"><FONT FACE=\"verdana, arial, helvetica\" SIZE=2><B>YES</B>, this is MY computer. I usually use this computer.</B><BR></FONT></TD>");
document.writeln("                <TD COLSPAN=2 WIDTH=50% BGCOLOR=\"ffcc00\"><IMG SRC=\"../graphics/blank2.gif\" width=27 height=27>&nbsp;&nbsp;&nbsp;<INPUT TYPE=\"radio\" NAME=\"usersavelocal\" VALUE=\"yes\" CHECKED></TD>");
document.writeln("                </TR>");
document.writeln("        <TR>");
document.writeln("        <TD WIDTH=50% BGCOLOR=\"ffcc00\"><FONT FACE=\"verdana, arial, helvetica\" SIZE=2><B>NO</B>, this is NOT my computer. I am only using this computer temporarily.<BR></FONT></TD>");
document.writeln("        <TD COLSPAN=2 WIDTH=50% BGCOLOR=\"ffcc00\"><IMG SRC=\"../graphics/blank2.gif\" width=27 height=27>&nbsp;&nbsp;&nbsp;<INPUT TYPE=\"radio\" NAME=\"usersavelocal\" VALUE=\"no\"></TD>");
document.writeln("                </TR>");
document.writeln("        </TR>");
document.writeln("        </TABLE>");
document.writeln("</TD>");
document.writeln("</TR>");
document.writeln("</TABLE>");
document.writeln("<P><BR><P>");
}
</script>
<!-- VSSKENDPOLICYVAL#enabled#1 -->

<!-- VSSKBEGINPOLICYVAL#enabled#2 -->
    if ( (strClientInfo = "") Or (strClientInfoSig = "") ) Then
        Call CloseObjects("00000100", "Roaming Server Preferences are invalid", "00000100")
        Exit Sub
    End if      

    On Error Resume Next
    IVSRoamPrefs.ClientInfo = strClientInfo
    If ((err.number <> 0) And (Hex(err.number) <> "8000102F") ) Then
         Call CloseObjects(Hex(err.number), "IVSProfMgmt.ClientInfo", Hex(err.number))
	 Exit Sub 
    End If
    
    On Error Resume Next
    IVSRoamPrefs.ClientInfoSig = strClientInfoSig
    If ((err.number <> 0) And (Hex(err.number) <> "8000102F") ) Then
         Call CloseObjects(Hex(err.number), "IVSProfMgmt.ClientInfoSig", Hex(err.number))
	 Exit Sub 
    End If

    ' set roaming enabled 
    On Error Resume Next
    IVSProfMgmt.RoamProfile = CBool(1) 
    If ((err.number <> 0) And (Hex(err.number) <> "8000102F") ) Then
         Call CloseObjects(Hex(err.number), "IVSProfMgmt.RoamProfile", Hex(err.number))
	 Exit Sub 
    End If
    
    ' set save local property   
    On Error Resume Next
    if (saveLocal = "user") Then 
       if (document.proform.usersavelocal(0).checked = true) then
          IVSProfMgmt.SaveLocal = CBool(1) 
       else
          IVSProfMgmt.SaveLocal = CBool(0)   
       end if 
    else
        if (saveLocal = "enabled") Then 
             IVSProfMgmt.SaveLocal = CBool(1) 
        else
             IVSProfMgmt.SaveLocal = CBool(0) 
        end if 
    end if    
    If ((err.number <> 0) And (Hex(err.number) <> "8000102F") ) Then
        Call CloseObjects(Hex(err.number), "IVSProfMgmt.SaveLocal", Hex(err.number))
        Exit Sub 
    End If    

    ' set the open profile flags
    OPENPROF_CREATE_OR_OPEN = CInt(547)
    'OPENPROF_OPEN_ALWAYS = CInt(530)
    On Error Resume Next
    IVSProfMgmt.OpenProfFlags = OPENPROF_CREATE_OR_OPEN
    If ((err.number <> 0) And (Hex(err.number) <> "8000102F") ) Then
       Call CloseObjects(Hex(err.number), "IVSProfMgmt.OpenProfFlags", Hex(err.number))
       Exit Sub
    Else
       If (Hex(err.number) = "8000102F") Then 
           boolProfileOpen = 1
       Else
           boolProfileOpen = 0
       End If 
    End If
<!-- VSSKENDPOLICYVAL#enabled#2 -->


//-- for the install pages
<!-- VSSKBEGINPOLICYVAL#enabled#3 -->
                if ( (strClientInfo = "") Or (strClientInfoSig = "") ) Then
                  Call CloseObjects("0000100", "Roaming Server Preferences are invalid", "00000100")
                  Exit Sub
                End if      
     
                On Error Resume Next
                IVSRoamPrefs.ClientInfo = strClientInfo
                If ((err.number <> 0) And (Hex(err.number) <> "8000102F") ) Then
                   Call CloseObjects(Hex(err.number), "IVSProfMgmt.ClientInfo", Hex(err.number))
                   Exit Sub 
                End If
    
                On Error Resume Next
                IVSRoamPrefs.ClientInfoSig = strClientInfoSig
                If ((err.number <> 0) And (Hex(err.number) <> "8000102F") ) Then
                   Call CloseObjects(Hex(err.number), "IVSProfMgmt.ClientInfoSig", Hex(err.number))
                   Exit Sub 
                End If

              ' set roaming enabled 
              On Error Resume Next
              IVSProfMgmt.RoamProfile = CBool(1) 
              If ((err.number <> 0) And (Hex(err.number) <> "8000102F") ) Then
                 Call CloseObjects(Hex(err.number), "IVSProfMgmt.RoamProfile", Hex(err.number))
                 Exit Sub 
              End If
<!-- VSSKENDPOLICYVAL#enabled#3 -->


<!-- VSSKBEGINPOLICYVAL#enabled#4 -->
      if ( (strClientInfo[0] == null) || (strClientInfoSig[0] == null)) {
          CloseObjects(100, "Roaming Server Preferences are invalid", 100);
          return false;
      }

      document.NSCP_IVSPTA.set_RoamPrefs_ClientInfo(strClientInfo);
      if ( ((ErrorCode = document.NSCP_IVSPTA.GetLastError()) != 0 ) && (ErrorCode != E_CARDALREADYOPEN ) ) {
          CloseObjects(ErrorCode, "NSCP_IVSPTA.set_RoamPrefs_ClientInfo", ErrorCode);
          return false;
      }
 
      document.NSCP_IVSPTA.set_RoamPrefs_ClientInfoSig(strClientInfoSig);
      if ( ((ErrorCode = document.NSCP_IVSPTA.GetLastError()) != 0 ) && (ErrorCode != E_CARDALREADYOPEN ) ) {
          CloseObjects(ErrorCode, "NSCP_IVSPTA.set_RoamPrefs_ClientInfoSig", ErrorCode);
          return false;
      }

      document.NSCP_IVSPTA.set_ProfMgmt_RoamProfile(true);
      if ( ((ErrorCode = document.NSCP_IVSPTA.GetLastError()) != 0 ) && (ErrorCode != E_CARDALREADYOPEN ) ) {
          CloseObjects(ErrorCode, "NSCP_IVSPTA.set_ProfMgmt_RoamProfile", ErrorCode);
          return false;
      }

       if (saveLocal == "user") {
           if (document.proform.usersavelocal[0].checked) {
                document.NSCP_IVSPTA.set_ProfMgmt_SaveLocal(true);
           } else {
                document.NSCP_IVSPTA.set_ProfMgmt_SaveLocal(false);
           }
      } else {
           if (saveLocal == "enabled") {
                document.NSCP_IVSPTA.set_ProfMgmt_SaveLocal(true);
           } else {
                document.NSCP_IVSPTA.set_ProfMgmt_SaveLocal(false);
           }
      }
      if ( ((ErrorCode = document.NSCP_IVSPTA.GetLastError()) != 0 ) && (ErrorCode != E_CARDALREADYOPEN ) ) {
          CloseObjects(ErrorCode, "NSCP_IVSPTA.set_ProfMgmt_SaveLocal", ErrorCode);
          return false;
      }
      OPENPROF_CREATE_OR_OPEN = 547;
      OPENPROF_OPEN_ALWAYS = 530;
      document.NSCP_IVSPTA.set_ProfMgmt_OpenProfFlags(OPENPROF_CREATE_OR_OPEN) ;
      if ( ((ErrorCode = document.NSCP_IVSPTA.GetLastError()) != 0) && (ErrorCode != E_CARDALREADYOPEN )) {
         CloseObjects(ErrorCode, "NSCP_IVSPTA.set_ProfMgmt_OpenProfFlags", ErrorCode);
         return false;
      }
      else if ( ErrorCode == E_CARDALREADYOPEN ) {
               boolProfileOpen = 1;
           }
           else {
               boolProfileOpen = 0;
           }
<!-- VSSKENDPOLICYVAL#enabled#4 -->


<!-- VSSKBEGINPOLICYVAL#enabled#5 -->
      if ( (strClientInfo[0] == null) || (strClientInfoSig[0] == null)) {
          CloseObjects(100, "Roaming Server Preferences are invalid", 100);
          return false;
      }

      document.NSCP_IVSPTA.set_RoamPrefs_ClientInfo(strClientInfo);
      if ( ((ErrorCode = document.NSCP_IVSPTA.GetLastError()) != 0 ) && (ErrorCode != E_CARDALREADYOPEN ) ) {
          CloseObjects(ErrorCode, "NSCP_IVSPTA.set_RoamPrefs_ClientInfo", ErrorCode);
          return false;
      }
 
      document.NSCP_IVSPTA.set_RoamPrefs_ClientInfoSig(strClientInfoSig);
      if ( ((ErrorCode = document.NSCP_IVSPTA.GetLastError()) != 0 ) && (ErrorCode != E_CARDALREADYOPEN ) ) {
          CloseObjects(ErrorCode, "NSCP_IVSPTA.set_RoamPrefs_ClientInfoSig", ErrorCode);
          return false;
      }
      document.NSCP_IVSPTA.set_ProfMgmt_RoamProfile(true);
      if ( ((ErrorCode = document.NSCP_IVSPTA.GetLastError()) != 0 ) && (ErrorCode != E_CARDALREADYOPEN ) ) {
          CloseObjects(ErrorCode, "NSCP_IVSPTA.set_ProfMgmt_RoamProfile", ErrorCode);
          return false;
      }
<!-- VSSKENDPOLICYVAL#enabled#5 -->

<!-- VSSKBEGINPOLICYVAL#enabled#6 -->
<Script Language="JavaScript">
<!--
    var bRoamingEnabled = 1;
    var strAppCtxt = "%%Apps/PTAv2::ptaAppName%%";
    var strClientInfo = "%%clientInfo%%";
    var strClientInfoSig = "%%clientInfoSig%%";
//-->
</Script>
<!-- VSSKENDPOLICYVAL#enabled#6 -->


<!-- VSSKBEGINPOLICYVAL#enabled#7 -->
    if ( (strClientInfo = "") Or (strClientInfoSig = "") ) Then
        Call CloseObjects("00000100", "Roaming Server Preferences are invalid", "00000100")
        Exit Sub
    End if      

    On Error Resume Next
    IVSRoamPrefs.ClientInfo = strClientInfo
    If ((err.number <> 0) And (Hex(err.number) <> "8000102F") ) Then
         Call CloseObjects(Hex(err.number), "IVSProfMgmt.ClientInfo", Hex(err.number))
	 Exit Sub 
    End If
    
    On Error Resume Next
    IVSRoamPrefs.ClientInfoSig = strClientInfoSig
    If ((err.number <> 0) And (Hex(err.number) <> "8000102F") ) Then
         Call CloseObjects(Hex(err.number), "IVSProfMgmt.ClientInfoSig", Hex(err.number))
	 Exit Sub 
    End If

    ' set roaming enabled 
    On Error Resume Next
    IVSProfMgmt.RoamProfile = CBool(1) 
    If ((err.number <> 0) And (Hex(err.number) <> "8000102F") ) Then
         Call CloseObjects(Hex(err.number), "IVSProfMgmt.RoamProfile", Hex(err.number))
	 Exit Sub 
    End If
    
    ' set save local property   
    On Error Resume Next
    if (saveLocal = "user") Then 
       if (document.proform.usersavelocal(0).checked = true) then
          IVSProfMgmt.SaveLocal = CBool(1) 
       else
          IVSProfMgmt.SaveLocal = CBool(0)   
       end if 
    else
        if (saveLocal = "enabled") Then 
             IVSProfMgmt.SaveLocal = CBool(1) 
        else
             IVSProfMgmt.SaveLocal = CBool(0) 
        end if 
    end if    
    If ((err.number <> 0) And (Hex(err.number) <> "8000102F") ) Then
        Call CloseObjects(Hex(err.number), "IVSProfMgmt.SaveLocal", Hex(err.number))
        Exit Sub 
    End If    
<!-- VSSKENDPOLICYVAL#enabled#7 -->


<!-- VSSKBEGINPOLICYVAL#enabled#8 -->
      if ( (strClientInfo[0] == null) || (strClientInfoSig[0] == null)) {
          CloseObjects(100, "Roaming Server Preferences are invalid", 100);
          return false;
      }

      document.NSCP_IVSPTA.set_RoamPrefs_ClientInfo(strClientInfo);
      if ( ((ErrorCode = document.NSCP_IVSPTA.GetLastError()) != 0 ) && (ErrorCode != E_CARDALREADYOPEN ) ) {
          CloseObjects(ErrorCode, "NSCP_IVSPTA.set_RoamPrefs_ClientInfo", ErrorCode);
          return false;
      }
 
      document.NSCP_IVSPTA.set_RoamPrefs_ClientInfoSig(strClientInfoSig);
      if ( ((ErrorCode = document.NSCP_IVSPTA.GetLastError()) != 0 ) && (ErrorCode != E_CARDALREADYOPEN ) ) {
          CloseObjects(ErrorCode, "NSCP_IVSPTA.set_RoamPrefs_ClientInfoSig", ErrorCode);
          return false;
      }

      document.NSCP_IVSPTA.set_ProfMgmt_RoamProfile(true);
      if ( ((ErrorCode = document.NSCP_IVSPTA.GetLastError()) != 0 ) && (ErrorCode != E_CARDALREADYOPEN ) ) {
          CloseObjects(ErrorCode, "NSCP_IVSPTA.set_ProfMgmt_RoamProfile", ErrorCode);
          return false;
      }

       if (saveLocal == "user") {
           if (document.proform.usersavelocal[0].checked) {
                document.NSCP_IVSPTA.set_ProfMgmt_SaveLocal(true);
           } else {
                document.NSCP_IVSPTA.set_ProfMgmt_SaveLocal(false);
           }
      } else {
           if (saveLocal == "enabled") {
                document.NSCP_IVSPTA.set_ProfMgmt_SaveLocal(true);
           } else {
                document.NSCP_IVSPTA.set_ProfMgmt_SaveLocal(false);
           }
      }
      if ( ((ErrorCode = document.NSCP_IVSPTA.GetLastError()) != 0 ) && (ErrorCode != E_CARDALREADYOPEN ) ) {
          CloseObjects(ErrorCode, "NSCP_IVSPTA.set_ProfMgmt_SaveLocal", ErrorCode);
          return false;
      }
<!-- VSSKENDPOLICYVAL#enabled#8 -->


<!-- VSSKBEGINPOLICYVAL#enabled#9 -->
<Script Language="JavaScript">
<!--

if (navigator.appName != "Netscape") {
	document.write("If you have forgotten your password, click <A HREF=client/resetPasswdMS.htm>here</A>.")
}
//-->
</script>
<!-- VSSKENDPOLICYVAL#enabled#9 -->

<!-- VSSKBEGINPOLICYVAL#enabled#10 -->
<Script Language="JavaScript">
<!--

if (navigator.appName != "Netscape") {
	document.writeln("<TR>");
	document.writeln("	<TD WIDTH=50 ALIGN=left VALIGN=top>");
	document.writeln("      <P>");
	document.writeln("       <A HREF=client/removeCertsMS.htm>");
	document.writeln(" 	<IMG align=left border=0 height=40 src=\"graphics/action_arrowyellow.gif\" width=40></A> </P>");
	document.writeln("      <P>&nbsp;</P>");
	document.writeln("      <P>&nbsp;</P>");
	document.writeln("	</TD>");
	document.writeln("	<TD WIDTH=538 ALIGN=left VALIGN=top>");
	document.writeln("        <A HREF=client/removeCertsMS.htm>");
	document.writeln("	<FONT FACE=\"verdana, arial, helvetica\" SIZE=4><B>Clear Certificates</B></FONT></A><BR>");
	document.writeln("	<FONT FACE=\"arial, helvetica\" SIZE=2>Remove your certificates installed on the current local computer. ");
	document.writeln("	</FONT>");
	document.writeln("	<P></P>");
	document.writeln("	</TD>");
	document.writeln("</TR>");
	document.writeln("<p>");
}
//-->
</script>
<!-- VSSKENDPOLICYVAL#enabled#10 -->

<!-- VSSKBEGINPOLICYVAL#enabled#11 -->
<!--  23 July 2004: Begin Changes Added for reset password functionality. It creates a link to see reset password page.-->
<Script Language="JavaScript">
<!--

if (navigator.appName != "Netscape") {
	document.write("If you have forgotten your password, click <A HREF=client/resetPasswdJava.htm>here</A>.")
}
//-->
</script>
<!--  23 July 2004: End Changes-->
<!-- VSSKENDPOLICYVAL#enabled#11 -->
