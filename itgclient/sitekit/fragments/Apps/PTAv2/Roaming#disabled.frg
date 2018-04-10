<!-- VSSKBEGINPOLICYVAL#disabled#1 -->
<!-- VSSKENDPOLICYVAL#disabled#1 -->

<!-- VSSKBEGINPOLICYVAL#disabled#2 -->
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

    ' set the open profile flags
    OPENPROF_CREATE_OR_OPEN = CInt(547)
    OPENPROF_OPEN_ALWAYS = CInt(530)
    On Error Resume Next
    IVSProfMgmt.OpenProfFlags = OPENPROF_OPEN_ALWAYS
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
<!-- VSSKENDPOLICYVAL#disabled#2 -->


<!-- VSSKBEGINPOLICYVAL#disabled#3 -->
                ' set roaming disabled 
                On Error Resume Next
                IVSProfMgmt.RoamProfile = CBool(0) 
                If ((err.number <> 0) And (Hex(err.number) <> "8000102F") ) Then
                   Call CloseObjects(Hex(err.number), "IVSProfMgmt.RoamProfile", Hex(err.number))
                   Exit Sub 
                End If
<!-- VSSKENDPOLICYVAL#disabled#3 -->


<!-- VSSKBEGINPOLICYVAL#disabled#4 -->
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
      OPENPROF_CREATE_OR_OPEN = 547;
      OPENPROF_OPEN_ALWAYS = 530;
      document.NSCP_IVSPTA.set_ProfMgmt_OpenProfFlags(OPENPROF_OPEN_ALWAYS) ;
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
<!-- VSSKENDPOLICYVAL#disabled#4 -->


<!-- VSSKBEGINPOLICYVAL#disabled#5 -->
      document.NSCP_IVSPTA.set_ProfMgmt_RoamProfile(false);
      if ( ((ErrorCode = document.NSCP_IVSPTA.GetLastError()) != 0 ) && (ErrorCode != E_CARDALREADYOPEN ) ) {
          CloseObjects(ErrorCode, "NSCP_IVSPTA.set_ProfMgmt_RoamProfile", ErrorCode);
          return false;
      }
<!-- VSSKENDPOLICYVAL#disabled#5 -->


<!-- VSSKBEGINPOLICYVAL#disabled#6 -->
     var bRoamingEnabled = 0;
<!-- VSSKENDPOLICYVAL#disabled#6 -->


<!-- VSSKBEGINPOLICYVAL#disabled#7 -->
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
<!-- VSSKENDPOLICYVAL#disabled#7 -->

<!-- VSSKBEGINPOLICYVAL#disabled#8 -->
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
<!-- VSSKENDPOLICYVAL#disabled#8 -->

<!-- VSSKBEGINPOLICYVAL#disabled#9 -->
<!-- VSSKENDPOLICYVAL#disabled#9 -->

<!-- VSSKBEGINPOLICYVAL#disabled#10 -->
<!-- VSSKENDPOLICYVAL#disabled#10 -->

<!--  23 July 2004: Begin Changes Added empty fragment as same fragment no. is present in Roaming#enabled.frg file. -->
<!-- VSSKBEGINPOLICYVAL#disabled#11 -->
<!-- VSSKENDPOLICYVAL#disabled#11 -->
<!--  23 July 2004: End Changes -->