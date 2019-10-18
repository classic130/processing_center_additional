
<!-- VSSKBEGINPOLICYVAL#user#1 -->
<script language="JavaScript">
function checkSaveLocal()
{
    if (document.proform.usersavelocal[1].checked) {
       document.proform.userroam[0].checked = true;
    }
}

function checkRoam() {
    if ("%%saveLocal%%" == "user") {
       if (document.proform.userroam[1].checked) {
          document.proform.usersavelocal[0].checked = true;
       }
    }
}

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
document.writeln("                <TD WIDTH=50% BGCOLOR=\"ffcc00\"><FONT FACE=\"verdana, arial, helvetica\" SIZE=2><B>YES</B>, this is MY computer. I usually use this computer.<BR></FONT></TD>");
document.writeln("                <TD COLSPAN=2 WIDTH=50% BGCOLOR=\"ffcc00\"><IMG SRC=\"../graphics/blank2.gif\" width=27 height=27>&nbsp;&nbsp;&nbsp;<INPUT TYPE=\"radio\" NAME=\"usersavelocal\" VALUE=\"yes\" CHECKED></TD>");
document.writeln("                </TR>");
document.writeln("        <TR>");
document.writeln("        <TD WIDTH=50% BGCOLOR=\"ffcc00\"><FONT FACE=\"verdana, arial, helvetica\" SIZE=2><B>NO</B>, this is NOT my computer. I am only using this computer temporarily.<BR></FONT></TD>");
document.writeln("        <TD COLSPAN=2 WIDTH=50% BGCOLOR=\"ffcc00\"><IMG SRC=\"../graphics/blank2.gif\" width=27 height=27>&nbsp;&nbsp;&nbsp;<INPUT TYPE=\"radio\" NAME=\"usersavelocal\" VALUE=\"no\" onClick=\"checkSaveLocal()\"></TD>");
document.writeln("                </TR>");
document.writeln("        </TR>");
document.writeln("        </TABLE>");
document.writeln("</TD>");
document.writeln("</TR>");
document.writeln("</TABLE>");
document.writeln("<P><BR><P>");
}

document.write("<TABLE WIDTH=588 BGCOLOR=\"ffffcc\" CELLPADDING=7 CELLSPACING=0 BORDER=0>");
document.writeln("<TR>");
document.writeln("<TD WIDTH=588>");
document.writeln("<font size=2 face=\"verdana, arial, helvetica\"><B> Will you use other computers to access this application?</B></FONT><BR>");
document.writeln("<P>");
document.writeln("<CENTER>");
document.writeln("       <TABLE WIDTH=574 CELLPADDING=3 CELLSPACING=2 BORDER=0>");
document.writeln("        <TR>");
document.writeln("                <TD WIDTH=50% BGCOLOR=\"ffcc00\"><FONT FACE=\"verdana, arial, helvetica\" SIZE=2><B>YES</B>, I will use other computers to access this application.<BR></FONT></TD>");
if (%%default%%) {
   document.writeln("                <TD COLSPAN=2 WIDTH=50% BGCOLOR=\"ffcc00\"><IMG SRC=\"../graphics/blank2.gif\" width=27 height=27>&nbsp;&nbsp;&nbsp;<INPUT TYPE=\"radio\" NAME=\"userroam\" VALUE=\"yes\" CHECKED></TD>");
} else {
   document.writeln("                <TD COLSPAN=2 WIDTH=50% BGCOLOR=\"ffcc00\"><IMG SRC=\"../graphics/blank2.gif\" width=27 height=27>&nbsp;&nbsp;&nbsp;<INPUT TYPE=\"radio\" NAME=\"userroam\"      VALUE=\"yes\"></TD>");
}
document.writeln("                </TR>");
document.writeln("        <TR>");
document.writeln("        <TD WIDTH=50% BGCOLOR=\"ffcc00\"><FONT FACE=\"verdana, arial, helvetica\" SIZE=2><B>NO</B>, I will only use this computer to access this application.<BR></FONT></TD>");
if (%%default%%) {
   document.writeln("        <TD COLSPAN=2 WIDTH=50% BGCOLOR=\"ffcc00\"><IMG SRC=\"../graphics/blank2.gif\" width=27 height=27>&nbsp;&nbsp;&nbsp;<INPUT TYPE=\"radio\" NAME=\"userroam\" VALUE=\"no\" onClick=\"checkRoam()\"></TD>");
} else {
   document.writeln("        <TD COLSPAN=2 WIDTH=50% BGCOLOR=\"ffcc00\"><IMG SRC=\"../graphics/blank2.gif\" width=27 height=27>&nbsp;&nbsp;&nbsp;<INPUT TYPE=\"radio\" NAME=\"userroam\" VALUE=\"no\"  CHECKED onClick=\"checkRoam()\"></TD>");
}
document.writeln("                </TR>");
document.writeln("        </TR>");
document.writeln("        </TABLE>");
document.writeln("</TD>");
document.writeln("</TR>");
document.writeln("</TABLE>");
document.writeln("<P><BR><P>");
</script>
<!-- VSSKENDPOLICYVAL#user#1 -->



<!-- VSSKBEGINPOLICYVAL#user#2 -->
   'if (document.proform.userroam.checked = true) then
   if (document.proform.userroam(0).checked) then
      'MsgBox "Roaming enabled"
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
         'if (document.proform.usersavelocal.checked = true) then
         if (document.proform.usersavelocal(0).checked) then
            'MsgBox "SaveLocal enabled"
            IVSProfMgmt.SaveLocal = CBool(1) 
         else
            'MsgBox "Save Local Disabled"
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
   Else 
      'MsgBox "Roaming is disabled"
      ' set roaming disabled 
      On Error Resume Next
      IVSProfMgmt.RoamProfile = CBool(0) 
      If ((err.number <> 0) And (Hex(err.number) <> "8000102F") ) Then
           Call CloseObjects(Hex(err.number), "IVSProfMgmt.RoamProfile", Hex(err.number))
	   Exit Sub 
      End If
    
      ' set save local property   
      On Error Resume Next
      IVSProfMgmt.SaveLocal = CBool(1) 
      If ((err.number <> 0) And (Hex(err.number) <> "8000102F") ) Then
          Call CloseObjects(Hex(err.number), "IVSProfMgmt.SaveLocal", Hex(err.number))
          Exit Sub 
      End If       
   End If 
   ' set the open profile flags
   OPENPROF_CREATE_OR_OPEN = CInt(547)
   OPENPROF_OPEN_ALWAYS = CInt(530)
   On Error Resume Next
   if (document.proform.userroam(0).checked) then
      IVSProfMgmt.OpenProfFlags = OPENPROF_CREATE_OR_OPEN
   else
      IVSProfMgmt.OpenProfFlags = OPENPROF_OPEN_ALWAYS
   end if
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
<!-- VSSKENDPOLICYVAL#user#2 -->


//-- for the install pages
<!-- VSSKBEGINPOLICYVAL#user#3 -->
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
<!-- VSSKENDPOLICYVAL#user#3 -->


<!-- VSSKBEGINPOLICYVAL#user#4 -->
   if (document.proform.userroam[0].checked) 
   {
      //alert("Roaming enabled");
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
                //alert("Save Local enabled");
                document.NSCP_IVSPTA.set_ProfMgmt_SaveLocal(true);
           } else {
                //alert ("SaveLocal Disabled");
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
   } else {
      //alert ("Roaming is disabled");

      document.NSCP_IVSPTA.set_ProfMgmt_RoamProfile(false);
      if ( ((ErrorCode = document.NSCP_IVSPTA.GetLastError()) != 0 ) && (ErrorCode != E_CARDALREADYOPEN ) ) {
          CloseObjects(ErrorCode, "NSCP_IVSPTA.set_ProfMgmt_RoamProfile", ErrorCode);
          return false;
      }
      
      document.NSCP_IVSPTA.set_ProfMgmt_SaveLocal(true);
      if ( ((ErrorCode = document.NSCP_IVSPTA.GetLastError()) != 0 ) && (ErrorCode != E_CARDALREADYOPEN ) ) {
          CloseObjects(ErrorCode, "NSCP_IVSPTA.set_ProfMgmt_SaveLocal", ErrorCode);
          return false;
      }
   } 
   OPENPROF_CREATE_OR_OPEN = 547;
   OPENPROF_OPEN_ALWAYS = 530;
   if (document.proform.userroam[0].checked) {
      document.NSCP_IVSPTA.set_ProfMgmt_OpenProfFlags(OPENPROF_CREATE_OR_OPEN) ;
   } else {
      document.NSCP_IVSPTA.set_ProfMgmt_OpenProfFlags(OPENPROF_OPEN_ALWAYS) ;
   }
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
<!-- VSSKENDPOLICYVAL#user#4 -->


<!-- VSSKBEGINPOLICYVAL#user#5 -->
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
<!-- VSSKENDPOLICYVAL#user#5 -->


<!-- VSSKBEGINPOLICYVAL#user#6 -->
<SCript Language="JavaScript">
<!--
    var bRoamingEnabled = 1;
    var strAppCtxt = "%%Apps/PTAv2::ptaAppName%%";
    var strClientInfo = "%%clientInfo%%";
    var strClientInfoSig = "%%clientInfoSig%%";
//-->
</Script>
<!-- VSSKENDPOLICYVAL#user#6 -->


<!-- VSSKBEGINPOLICYVAL#user#7 -->
   'if (document.proform.userroam.checked = true) then
   if (document.proform.userroam(0).checked) then
      'MsgBox "Roaming enabled"
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
         'if (document.proform.usersavelocal.checked = true) then
         if (document.proform.usersavelocal(0).checked) then
            'MsgBox "SaveLocal enabled"
            IVSProfMgmt.SaveLocal = CBool(1) 
         else
            'MsgBox "Save Local Disabled"
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
   Else 
      'MsgBox "Roaming is disabled"
      ' set roaming disabled 
      On Error Resume Next
      IVSProfMgmt.RoamProfile = CBool(0) 
      If ((err.number <> 0) And (Hex(err.number) <> "8000102F") ) Then
           Call CloseObjects(Hex(err.number), "IVSProfMgmt.RoamProfile", Hex(err.number))
	   Exit Sub 
      End If
    
      ' set save local property   
      On Error Resume Next
      IVSProfMgmt.SaveLocal = CBool(1) 
      If ((err.number <> 0) And (Hex(err.number) <> "8000102F") ) Then
          Call CloseObjects(Hex(err.number), "IVSProfMgmt.SaveLocal", Hex(err.number))
          Exit Sub 
      End If       
   End If 
<!-- VSSKENDPOLICYVAL#user#7 -->


<!-- VSSKBEGINPOLICYVAL#user#8 -->
   if (document.proform.userroam[0].checked) 
   {
      //alert("Roaming enabled");
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
                //alert("Save Local enabled");
                document.NSCP_IVSPTA.set_ProfMgmt_SaveLocal(true);
           } else {
                //alert ("SaveLocal Disabled");
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
   } else {
      //alert ("Roaming is disabled");

      document.NSCP_IVSPTA.set_ProfMgmt_RoamProfile(false);
      if ( ((ErrorCode = document.NSCP_IVSPTA.GetLastError()) != 0 ) && (ErrorCode != E_CARDALREADYOPEN ) ) {
          CloseObjects(ErrorCode, "NSCP_IVSPTA.set_ProfMgmt_RoamProfile", ErrorCode);
          return false;
      }
      
      document.NSCP_IVSPTA.set_ProfMgmt_SaveLocal(true);
      if ( ((ErrorCode = document.NSCP_IVSPTA.GetLastError()) != 0 ) && (ErrorCode != E_CARDALREADYOPEN ) ) {
          CloseObjects(ErrorCode, "NSCP_IVSPTA.set_ProfMgmt_SaveLocal", ErrorCode);
          return false;
      }
   } 
<!-- VSSKENDPOLICYVAL#user#8 -->


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

