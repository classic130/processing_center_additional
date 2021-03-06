
<!-- VSSKBEGINPOLICYVAL#default#1 -->
   CONST        vsenroll_url    %%::crsUrl%%
<!-- VSSKENDPOLICYVAL#default#1 -->

<!-- VSSKBEGINPOLICYVAL#default#2 -->
  CONST   corp_company              %%::corpName%%
  CONST   org_unit                  %%::orgUnitName%%
  CONST   cert_jurisdiction_hash    %%::jurisdictionHash%%
  CONST   private_label             %%::privateLabel%%
<!-- VSSKENDPOLICYVAL#default#2 -->

<!-- VSSKBEGINPOLICYVAL#default#3 -->
   CONST    cert_jurisdiction_hash     %%::jurisdictionHash%%
<!-- VSSKENDPOLICYVAL#default#3 -->


<!-- VSSKBEGINPOLICYVAL#default#4 -->
CONST		product_config_file	%%::productConfigFile%%
<!-- VSSKENDPOLICYVAL#default#4 -->


<!-- VSSKBEGINPOLICYVAL#default#5 -->
<TABLE WIDTH=588 CELLPADDING=0 CELLSPACING=0 BORDER=0>
<TR>
    <TD WIDTH=100%><FONT COLOR="0000cc" FACE="verdana, arial, helvetica" SIZE=5><B>
    %%::corpName%% %%::orgUnitName%% Digital ID Center
    </B></FONT></TD>
</TR>
</TABLE>
<!-- VSSKENDPOLICYVAL#default#5 -->


<!-- VSSKBEGINPOLICYVAL#default#6 -->
CONST       product_config_file  	%%::productConfigFile%%
CONST       embed_email                 yes
<!-- VSSKENDPOLICYVAL#default#6 -->

<!-- VSSKBEGINPOLICYVAL#default#7 -->
<FORM NAME=ErrorForm ACTION="../../cgi-bin/softbounce.exe" METHOD=POST>
  <INPUT type=hidden NAME=form_file VALUE="../fdf/VSApps/client/DefaultError.fdf">
  <INPUT type=hidden NAME=errorCode VALUE=0>
  <INPUT type=hidden NAME=winerrorcode VALUE=0>
  <INPUT type=hidden NAME=operation VALUE="">
  <INPUT type=hidden NAME=showError VALUE="">
</FORM>
<!-- VSSKENDPOLICYVAL#default#7 -->

<!-- VSSKBEGINPOLICYVAL#default#8#1.2.0.4 -->
<SCRIPT LANGUAGE=JavaScript>
<!--
  var firstSearch = 0
  function SetErrorInfo(form_file, error_code, winerrorcode, operation)
  {
    document.ErrorForm.form_file.value = form_file ;
    document.ErrorForm.errorCode.value = error_code ;
    document.ErrorForm.winerrorcode.value = winerrorcode ;
    document.ErrorForm.operation.value = operation ;

    document.ErrorForm.submit() ;
  }

  // don't call the function below on IE pages
  function ReBaseErrorCodeNS(error_code)
  {
    if (navigator.appName != "Netscape")
        { return error_code; }

    var javaErrorString, strErrorCode;
	var ErrNumber;
    
    ERROR_LIMIT = 0x80000000;       
    if (error_code >= ERROR_LIMIT) {
	  error_code = error_code - 0x80000000;
	  ErrNumber = new Number(error_code);
      javaErrorString = ErrNumber.toString(16);
      if(error_code <= 0xF) {
	strErrorCode = "7000000" + javaErrorString.substring(javaErrorString.length-1, javaErrorString.length);
      }
      else if (error_code <= 0xFF) {
	strErrorCode = "700000" + javaErrorString.substring(javaErrorString.length-2, javaErrorString.length);
      }
      else if (error_code <= 0xFFF) {
	strErrorCode = "70000" + javaErrorString.substring(javaErrorString.length-3, javaErrorString.length);
      } 
      else {
       strErrorCode = "7000" + javaErrorString.substring(javaErrorString.length-4, javaErrorString.length);
      }
    } else {
      ErrNumber = new Number(error_code);
      strErrorCode = ErrNumber.toString(10);
    }
    return strErrorCode;
  }
  
  // Don't call the function below on IE pages
  function ConvertToHexNS (error_code)
  {
    if (navigator.appName != "Netscape")
        { return error_code; }
   
    var javaErrorCode;
	var ErrNumber;
	 
    ERROR_LIMIT = 0x80000000;       
    if (error_code >= ERROR_LIMIT) {
	  error_code = error_code - 0x80000000;
	  ErrNumber = new Number(error_code);
      javaErrorCode = ErrNumber.toString(16);
      if(error_code <= 0xF) {
	javaErrorCode = "8000000" + javaErrorCode.substring(javaErrorCode.length-1, javaErrorCode.length);
      }
      else if (error_code <= 0xFF) {
	javaErrorCode = "800000" + javaErrorCode.substring(javaErrorCode.length-2, javaErrorCode.length);
      }
      else if (error_code <= 0xFFF) {
	javaErrorCode = "80000" + javaErrorCode.substring(javaErrorCode.length-3, javaErrorCode.length);
      } 
      else {
       javaErrorCode = "8000" + javaErrorCode.substring(javaErrorCode.length-4, javaErrorCode.length);
      }
      
    } else {
	  ErrNumber = new Number(error_code);
      javaErrorCode = ErrNumber.toString(10);
    }
    return javaErrorCode;
  }

  // don't call the function below on Firefox pages
  function CheckErrorCodeMS(error_code)
  {
    var strErrorCode;
    if (navigator.appName == "Netscape")
        { return error_code; }

    if (error_code >= "80000000")
    {
       strErrorCode = "7000" + error_code.substring(error_code.length-4, error_code.length);
    } else {
       strErrorCode = error_code;
    }
    return strErrorCode;
  }
//-->
</SCRIPT>
<!-- VSSKENDPOLICYVAL#default#8 -->


<!-- VSSKBEGINPOLICYVAL#default#9 -->
  CONST     issuerName   %%::certIssuerDN%%
<!-- VSSKENDPOLICYVAL#default#9 -->


<!-- VSSKBEGINPOLICYVAL#default#10 -->
<Script Language="JavaScript">
<!--
if ( "%%::privateLabel%%"=="Y" || "%%::privateLabel%%"=="y" )
{
   document.write("<TR>");
   document.write("<TD WIDTH=50 ALIGN=left VALIGN=top>");
   document.write("<A HREF=\"https://%%::vsHost%%/cgi-bin/privateCA/getcacert\">");
   document.write("<IMG SRC=\"graphics/action_arrowyellow.gif\" border=0 WIDTH=40 HEIGHT=40 ALIGN=LEFT></A>");
   document.write("</TD>");
   document.write("<TD WIDTH=538 ALIGN=left VALIGN=top>");
   document.write("<A HREF=\"https://%%::vsHost%%/cgi-bin/privateCA/getcacert\">");
   document.write("<FONT FACE=\"verdana, arial, helvetica\" SIZE=5><B>INSTALL CA</B></FONT></A><BR>");
   document.write("<P>");
   document.write("</TD>");
   document.write("</TR>");
}
//-->
</Script>
<!-- VSSKENDPOLICYVAL#default#10 -->

<!-- VSSKBEGINPOLICYVAL#default#11 -->
CONST       originator                  VeriSign OnSite
<!-- VSSKENDPOLICYVAL#default#11 -->

<!-- VSSKBEGINPOLICYVAL#default#12 -->
	Function GetCertAuthMethod()
	    Dim Method
	    Dim PasscodePolicyValue, ModePolicyValue

            PasscodePolicyValue = "%%Enrollment/PassCode::policyValue%%"
            ModePolicyValue = "%%Global/Mode::policyValue%%"

            if ( (PasscodePolicyValue = "exists" AND ModePolicyValue = "manualauth") OR (PasscodePolicyValue = "exists" AND ModePolicyValue = "remotehost") ) then
              ' Treat it as passcode auth only
	      Method = "passcode"
            elseif ( (PasscodePolicyValue = "absent" AND ModePolicyValue = "manualauth") OR (PasscodePolicyValue = "absent" AND ModePolicyValue = "remotehost") ) then
              ' Treat it as Manual auth only
	      Method = "manual"
            else
              ' Treat it as Auto Auth
	      Method = "auto"
	    end if

	    GetCertAuthMethod = Method
	End Function
<!-- VSSKENDPOLICYVAL#default#12 -->

<!-- VSSKBEGINPOLICYVAL#default#13 -->
<!-- VSSKBEGIN Global/Mode#103 -->
<!-- VSSKEND Global/Mode#103 -->
  <INPUT type=hidden NAME=form_file VALUE="../fdf/VSApps/client/DefaultError.fdf">
  <INPUT type=hidden NAME=errorCode VALUE=0>
  <INPUT type=hidden NAME=winerrorcode VALUE=0>
  <INPUT type=hidden NAME=operation VALUE="">
  <INPUT type=hidden NAME=showError VALUE="">
</FORM>
<!-- VSSKENDPOLICYVAL#default#13 -->


<!-- VSSKBEGINPOLICYVAL#default#14 -->
<SCRIPT LANGUAGE=VBScript>
<!--
  Dim authvarpresent
  
  Dim authvar_FirstName,authvar_LastName,authvar_Email,authvar_Passcode,authvar_JobTitle
  Dim authvar_EmpID,authvar_MailStop,authvar_AddField4,authvar_AddField5,authvar_AddField6
  Dim authvar_Locality,authvar_State,authvar_Country

  authvar_FirstName = "%%Enrollment/FirstName::policyValue%%"	
  authvar_LastName = "%%Enrollment/LastName::policyValue%%"	
  authvar_Email="%%Enrollment/EMAIL::policyValue%%"

  authvar_Passcode="%%Enrollment/PassCode::policyValue%%"
  authvar_JobTitle= "%%Enrollment/JobTitle::policyValue%%"	
  authvar_EmpID="%%Enrollment/EmpID::policyValue%%"	

  authvar_MailStop="%%Enrollment/MailStop::policyValue%%"
  authvar_AddField4="%%Enrollment/AddField4::policyValue%%"
  authvar_AddField5="%%Enrollment/AddField5::policyValue%%"
  authvar_AddField6="%%Enrollment/AddField6::policyValue%%"

  authvar_Locality="%%Enrollment/Locality::policyValue%%"
  authvar_State="%%Enrollment/State::policyValue%%"
  authvar_Country="%%Enrollment/Country::policyValue%%"	

  authvarpresent = 1

  if ( authvar_FirstName = "absent" AND authvar_LastName = "absent" AND authvar_Email="absent" AND authvar_Passcode="absent" AND authvar_JobTitle="absent" AND authvar_EmpID="absent" AND authvar_MailStop="absent" AND authvar_AddField4="absent" AND authvar_AddField5="absent" AND authvar_AddField6="absent" AND authvar_Locality="absent" AND authvar_State="absent" AND authvar_Country="absent" ) Then	

		  authvarpresent = 0
  end if


  if ( authvarpresent = 1 ) then
    document.write("<P><BR><P>")
    document.write("<TABLE WIDTH=588 BGCOLOR=""ffffcc"" CELLPADDING=7 CELLSPACING=0 BORDER=0>")
    document.write("  <TR>")
    document.write("        <TD WIDTH=588>")
    document.write("  <FONT SIZE=2 FACE=""verdana, arial, helvetica""><B>Enter your Digital ID information</B></FONT><BR>")
    document.write("  <FONT FACE=""arial, helvetica"" SIZE=2>Fill in all required fields. Fields marked with an asterisk <FONT COLOR=""0000cc"" FACE=""verdana, arial, helvetica"" SIZE=2><B>(*)</B></FONT> are included with your Digital ID and are viewable in the certificate's details.<BR></FONT><P>")
    document.write("  <CENTER>")
    end if 
-->
</SCRIPT>
<!-- VSSKENDPOLICYVAL#default#14 -->

<!-- VSSKBEGINPOLICYVAL#default#15 -->
<SCRIPT LANGUAGE=VBScript>
<!--
  if ( authvarpresent = 1 ) then
	document.write("</TD>")
	document.write("</TR>")
    	document.write("</TABLE>")
  end if

  document.write("<P><BR><P>")
-->
</SCRIPT>

<!-- VSSKENDPOLICYVAL#default#15 -->


<!-- VSSKBEGINPOLICYVAL#default#16 -->
<SCRIPT LANGUAGE=JavaScript>
<!--
  // This is a global variable that determines if 
  // an error occured while exeuting a Method or
  // property of an ActiveX control. It MUST be set
  // to a non-zero value when an error is to be reported
  // through a post/get to softbounce.exe.
  var bErrorPresent = 0 ;

  function deal() 
  {
    WebBrowser1.outerHTML = "";
    window.onerror = oldHandler;
    alert("Could not stop the browser using ExecWB method of the Web Browser object...\n") ;
    return true;
  }

  function StopIt() 
  {
    var OLECMDID_STOP = 23;
    var OLECMDEXECOPT_DONTPROMPTUSER = 2;
    var OLECMDEXECOPT_PROMPTUSER = 1;
    var WebBrowser = '<OBJECT ID="WebBrowser1" WIDTH=0 HEIGHT=0 CLASSID="CLSID:8856F961-340A-11D0-A96B-00C04FD705A2"></OBJECT>';
    document.body.insertAdjacentHTML('beforeEnd', WebBrowser);
    oldHandler = window.onerror;
    window.onerror = deal;

    WebBrowser1.ExecWB(OLECMDID_STOP, OLECMDEXECOPT_DONTPROMPTUSER);

    WebBrowser1.outerHTML = "";
    window.onerror = oldHandler;
  }

  function SetErrorInfo2(form_file, error_code, winerrorcode, operation)
  {
    document.ErrorForm.form_file.value = form_file ;
    document.ErrorForm.errorCode.value = error_code ;
    document.ErrorForm.winerrorcode.value = winerrorcode ;
    document.ErrorForm.operation.value = operation ;

    // Now stop the browser rendering.
    StopIt() ;

    document.ErrorForm.submit() ;
    bErrorPresent = 1 ;
  }
//-->
</SCRIPT>
<!-- VSSKENDPOLICYVAL#default#16 -->


<!-- VSSKBEGINPOLICYVAL#default#17 -->
   if ( bErrorPresent = 1 ) Then
       Exit Sub
   End if
<!-- VSSKENDPOLICYVAL#default#17 -->

<!-- VSSKBEGINPOLICYVAL#default#18#1.0.0.2 -->
<Script Language="JavaScript">
<!--
    var bIsWin2k = false;
    function checkWin2K() 
    {
       var uaOS = navigator.userAgent;
       bIsWin2k = (uaOS.indexOf("Windows NT 5.")>=1);
    }
    checkWin2K();
//-->
</Script>
<!-- VSSKENDPOLICYVAL#default#18 -->
<!-- VSSKBEGINPOLICYVAL#default#19#1.0.0.0 -->
<Script Language="JavaScript">
<!--
  if ("%%Apps/PTAv2::policyValue%%" != "no"  || "%%Apps/GSE::policyValue%%" != "no")
  {
	
  if ( "%%clientMode%%" != "pts" && "%%Apps/PTAv2/GSWAClientType::policyValue%%" != "Java")
  {
   document.write("<TR>");
   document.write("<TD WIDTH=50 ALIGN=left VALIGN=top>");
   document.write("<A HREF=\"win2kCenter.htm\"><IMG SRC=\"graphics/action_arrowyellow.gif\" border=0 WIDTH=40 HEIGHT=40 ALIGN=LEFT></A>");
   document.write("</TD>");
   document.write("<TD WIDTH=538 ALIGN=left VALIGN=top>");
   document.write("<A HREF=\"win2kCenter.htm\"><FONT FACE=\"verdana, arial, helvetica\" SIZE=4><B>Windows Resource Center</FONT><FONT SIZE=3> (For Administrators Only)</FONT></B></A><BR>");
   document.write("<FONT FACE=\"arial, helvetica\" SIZE=2>This page will give you information about how to enable your");
   document.write(" non-power users on Windows 7/8.1 machines.");
   document.write("</FONT>");
   document.write("<P>");
   document.write("</TD>");
   document.write("</TR>");
  }
}
//-->
</Script>
<!-- VSSKENDPOLICYVAL#default#19 -->

<!-- VSSKBEGINPOLICYVAL#default#20 -->
<SCRIPT Language="VBScript" src="%%::remoteHost%%/VSApps/client/vsissuerdn2.vbs"></SCRIPT>
<!-- VSSKENDPOLICYVAL#default#20 -->
