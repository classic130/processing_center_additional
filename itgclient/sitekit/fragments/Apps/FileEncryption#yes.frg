<!-- VSSKBEGINPOLICYVAL#yes#1 -->
<!-- VSSKBEGIN Global/Mode#107 -->
<!-- VSSKEND Global/Mode#107 -->
<!-- VSSKENDPOLICYVAL#yes#1 -->

<!-- VSSKBEGINPOLICYVAL#yes#2 -->
<!-- show link for FET download page -->
<TABLE WIDTH=588 CELLPADDING=7 CELLSPACING=0 BORDER=0>
<TR>
    <TD WIDTH=588 BGCOLOR="#cccccc"><FONT FACE="verdana, arial, helvetica" SIZE=2><B>
    <FONT FACE="arial, helvetica" SIZE=2>Install File Encryption Tool.</B></FONT><BR>
    <P>
    <CENTER>
      <TABLE WIDTH=574 CELLPADDING=3 CELLSPACING=2 BORDER=0 BGCOLOR="ffffcc">
      <TR>
         <TD WIDTH=100% ><FONT FACE="verdana, arial, helvetica" SIZE=2>The VeriSign File Encryption Tool is a desktop utility that allows you 
         to encrypt files on your machine using your Digital ID. Click <A HREF="../VSApps/client/fetIntroMS.htm" target="_blank">here</A> 
         to install this utility.
         </TD>
      </TR>
      </TABLE>	 
    </TD>
</TR>
</TABLE>
<P>
<!-- VSSKENDPOLICYVAL#yes#2 -->

<!-- VSSKBEGINPOLICYVAL#yes#3 -->
<!-- VSSKBEGIN Apps/PTAv2/Roaming#6 -->
<!-- VSSKEND Apps/PTAv2/Roaming#6 -->
<Script Language="JavaScript">
<!--
if (bRoamingEnabled == 1){
    if ( (strClientInfo[0] == null) || (strClientInfoSig[0] == null) || (strAppCtxt[0] == null) ) {
          alert ("The File Encryption Tool could not set your roaming access."); 
    } else {
         vsctl.SetFetContextInformation(strAppCtxt, strClientInfo, strClientInfoSign);
         if (err.number == 0) {
            alert ("The File Encryption Tool has successfully set your Roaming access.");
	 } else {
            alert ("The File Encryption Tool could not set your roaming access."); 
         }
    }
} 
//-->
</Script>
<!-- VSSKENDPOLICYVAL#yes#3 -->