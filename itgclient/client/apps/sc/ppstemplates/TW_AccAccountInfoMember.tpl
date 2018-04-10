<!-- Copyright (c) 1993-2001 Tumbleweed Communications Corp. All Rights Reserved. -->
<!-- Filename: TW_AccAccountInfoMember.tpl -->
<%@include file="TW_GlobalHeaderMenu.tpl" %>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 3.2 Final//EN"> 
<%
	var imagepathurl = tw.httpGateway.getImgPathUrl();
	// Set the page specific data.
	// set the active menu
	TW_SetActiveMenuItem( tw.constant.TW_MENU_GROUP_ACCOUNT_INFO, "Member Info" );

	// set the help url
	var helpUrl = "javascript:GoHelp('MemberInfo')" ;
	TW_SetHelpMenuUrl( "Help", helpUrl );
	var pageTitle = "Member Information";

	// Get the account object
	var account_obj = tw.session.account;
	// Get the effective capabilities for this account.
	var effective = account_obj.effectiveCapabilities;

	// Get the begining and the end of the month.
	var now_date = new Date();
	var from_date = new Date( now_date.getFullYear(), now_date.getMonth());
	var to_date;
	if (now_date.getMonth() == 11) {
		to_date = new Date( now_date.getFullYear()+1, 0);
	} else {
		to_date = new Date( now_date.getFullYear(), now_date.getMonth()+1);
	}
	// Substract one second in order to get the last second of the month.
	to_date = new Date( to_date.getTime() - 1000 );

	// Get the usage count.
	var query_package_str = "TW_USAGE = 'TW_DELIVERY' AND TW_CREATE_TIME >= " + (from_date.getTime()/1000) + "DATE " +
		" AND TW_CREATE_TIME < " + (to_date.getTime()/1000) + "DATE " +
		" AND TW_SENDER_ACCOUNT_ID = " + tw.session.account.id + "ID " +
		" AND TW_REFERENCE_TYPE = " + tw.constant.TW_PACKAGE_REFERENCE_TYPE_SENDER + "INT";
	var query_pkg = TW_Package.queryPackageUsage(tw.session.account, query_package_str + "; ; ; ; 1INT ; ;");
	var usage_count = query_pkg.packageCount;

	// Find the account credits
	var custArray = tw.session.account.queryCustomObjects("TW_NAME='SGMS_ACCOUNT_PROPERTY'; ; ;7INT", false);
	if (custArray.length > 0) {
		var unit_balance = new String(custArray[0].SGMS_message_unit_balance);
	} else {
		// the property is not found for some reason.
		var unit_balance = "none";
	}

	// Check if the account can create packages. This is used for package couter display.
	var effective = account_obj.effectiveCapabilities;
	var inherited = account_obj.inheritedCapabilities;
	var canCreatePackages;
	if ( effective.canCreatePackages == null ) {
		canCreatePackages = (inherited.canCreatePackages != null) ?
						  inherited.canCreatePackages : false;
	} else if ( inherited.canCreatePackages == null ) {
		canCreatePackages = (effective.canCreatePackages != null) ?
						  effective.canCreatePackages : false;
	} else {
		canCreatePackages = effective.canCreatePackages && inherited.canCreatePackages;
	}

	// Get the authentication method for this account.
	var authenticationMethod = "";
	if ( inherited.authenticationMethod == null || inherited.authenticationMethod == "" ) {
		authenticationMethod = effective.authenticationMethod;
	} else if ( effective.authenticationMethod == null || effective.authenticationMethod == "" ) {
		authenticationMethod = inherited.authenticationMethod;
	}
	if ( authenticationMethod == null ) {
		authenticationMethod = ""; 
	}

	// Prepare password restrictions text.
	var minAcctPasswordReqs = new String();
	var	minAccountPasswordLength =	new Number(( effective.minAccountPasswordLength != null ) ?
										effective.minAccountPasswordLength :
										0);
	var	minAccountPasswordDigits =	new Number(( effective.minAccountPasswordDigits != null ) ?
										effective.minAccountPasswordDigits :
										0);

	var	minAccountPasswordLetters =	new Number(( effective.minAccountPasswordLetters != null ) ?
										effective.minAccountPasswordLetters :
										0);

	minAcctPasswordReqs = minAcctPasswordReqs.formatPositional( "The account password requires a minimum of %1$d character(s) with at least %2$d digit(s) and at least %3$d alphabetical character(s).",
							  minAccountPasswordLength, 
							  minAccountPasswordDigits, 
							  minAccountPasswordLetters);

	// Get the locale of the account.
	var locales_supported = tw.server.getConfigParameter("TW_INTERNATIONAL_INSTALLED_LOCALES" );

	// Get the default.
	var default_index = tw.server.getConfigParameter("TW_DEFAULT_LOCALE");
	var locale_index = -1;
	for (i=0 ; i< locales_supported.length ; ++i) {
		if (locales_supported[i] == tw.session.account.locale) {
			locale_index = i;
		}
	}
	default_index = (locale_index == -1) ? default_index : locale_index;

	// Get the user time of this account.
	var now = new Date();
	var current_time = now.getTime();
	var gmt_lag = now.getTimezoneOffset();
	var user_time = account_obj.userTimeZoneDelta - -13 - ( gmt_lag / 60 );
%>

<html>
<script language=javascript>
<!-- Many features on this page will not operate as this browser does not support Javascript. -->
<!--

/* Tumbleweed help. We don't use this. Use GoHelp(h_topic)
 *function GoHelp(h_dir, h_topic)
 *{
 *   if (h_topic.charAt(0) == "A"){
 *	h_url="/help/Admin/"+h_dir+"/"+h_topic+".htm";
 *   } else if (h_topic.charAt(0) == "C"){
 *	h_url="/help/Central/"+h_dir+"/"+h_topic+".htm";
 *   }
 *			HWin=window.open(h_url,"HelpWin","toolbar=yes,width=670,height=450,resizable=yes,scrollbars=yes")
 *   if (HWin.focus) HWin.focus()
 *}
 */

function GoHelp(h_topic, h_bookmark)
{
	h_url="/help/" + h_topic + ".htm";
	if (h_bookmark)
	{
		var char0, char1;
		char0 = h_bookmark.charAt(0);
		char1 = h_bookmark.charAt(1);
		// if first 2 letters are CAPS, then switch to Admin help
		if ( (char0 == 'A') && (char1 >= 'A' && char1 <= 'Z') )
		{
			var h_admin_topic = h_bookmark;
			var h_admin_dir = h_topic;
			h_url = "/help/Admin/"+h_admin_dir+"/"+h_admin_topic+".htm";
		} else {
			h_url = h_url + "#" + h_bookmark;
		}
	}
	HWin=window.open(h_url,"HelpWin","toolbar=yes,width=670,height=450,resizable=yes,scrollbars=yes")
	if (HWin.focus) HWin.focus()
}


function DoClick( cmd )
{
	changePassword();
}
//-->
</script>
<head>
<%@include file="SGMS_VSSCChangePasswdInclude.tpl" %>
<title>VeriSign PrivatePath service</title>
<link rel="stylesheet" type="text/css" href="<%=tw.httpGateway.getStylesheetPathUrl();%>/verisign.css"> 
</head>

<body bgcolor="#ffffff" background="<%=imagepathurl;%>/background.gif" leftmargin="0" topmargin="0"  marginwidth="0" marginheight="0" name="main">


<%
tw.write("<!-- Navigation bar include -->"); // Don't remove this line.
/*
The include files NavigationBarsTop.tpl and NavigationBarsBottom.tpl 
contain the top part of the left and top navigation bars in the 
IME Messenger UI. To use it, you need to do the following in your 
main file:
    1. (at)include "TW_GlobalHeaderMenu.tpl"
    2. (pound)include NavigationBarsTop.tpl before the main table
    3. (pound)include NavigationBarsBottom.tpl after the main table
    4. define the variable pageTitle
    5. For the  help links in the left and top nav bar to be visible, 
       define helpUrl and call TW_SetHelpUrl in the main page.
    See TW_AccEnd.tpl for a simple file which does this.
    6. Make sure the variable imagepathurl is set to tw.httpGateway.getImgPathUrl();

	7. Certain files, such as TW_AccLogin.tpl, have unique menus.
	   They set tw.appRegistry.outputTemplate, so that MenuBuilder 
	   can look out for them.

note: the trial account code down by MenuBuilder( imagepathurl ) will result in an
      error if no session is active -- i.e., keep the header file inside, unless
      an inactive session is detected. PK
*/ %>

<%
// Variables here
var table_border_NavigationBarsTop = 0;  //for debugging purposes
%>

<TABLE border="<%=table_border_NavigationBarsTop;%>" cellpadding="0" cellspacing="0" width="100%">

  <!-- VeriSign logo --><!-- top image -->
  <TR> 
    <TD colspan="1" rowspan="1" width="150" valign="top" height="84"><img name="logo" src="<%=imagepathurl;%>/verisign.gif" width="150" height="84" border="0"></TD>
    <TD colspan="3" height="84" valign="top" nowrap background="<%=imagepathurl;%>/hd_home.gif"  bgcolor="#d8d7b8"><BR><BR>&nbsp;&nbsp;<br>&nbsp;&nbsp;
      <span class="bigblue">
      <%=pageTitle;%></span>
    </TD>
  </TR>

  <TR valign="top">
    <!-- left nav bar -->
    <TD rowspan="1" height="360">
	<TABLE width="100%" cellspacing="0" cellpadding="0" border="<%=table_border_NavigationBarsTop;%>">
	  <TR valign="top">
	    <TD colspan="2" valign="top" background="<%=imagepathurl;%>/nav_background.gif" height="360" width="150">
	      <br>
	      <br>
	      <br>
		<% TW_MenuBuilder( imagepathurl );%>

			
			<% if ( tw.session.isLoggedIn ) { /* Added the if clause to check if the account logged in is trial account */ %>
				<% if((tw.session.account.effectiveCapabilities.canCreatePackages == 0) && isExpiredAllowedCreatePackage()) { %>
					<BR>&nbsp;<a href="<%=tw.httpGateway.getUrl('SGMS_ErrorReceiveOnly.tpl');%>"><img src="<%=imagepathurl;%>/enroll.gif" width="140" height="54" border="0" alt=""></a>
				<% } %>
			<% } %>

	    </TD>
	  </TR>
	</TABLE>
    </TD>
    <!-- left vertical spacer -->
    <TD rowspan="1" width="20"><IMG src="<%=imagepathurl;%>/spacer.gif" width="20" border="0"></TD>

    <TD height="400" width="100%">
	<TABLE height="100%" width="100%" cellspacing="0" cellpadding="0" border="<%=table_border_NavigationBarsTop;%>">
	  <TR>
	    <!-- horizontal spacer -->
	    <TD height="20" colspan="1">
	      <IMG src="<%=imagepathurl;%>/spacer.gif" height="20">
	      <noscript>
		<BR>
		<center>
		  <font color='#ff0000' face='Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular' size='-1'><B>Many features on this page will not operate as this browser does not support Javascript.</B></font> 
		</center>
	      </noscript> 
	    </TD>
	    <!-- right vertical spacer -->
	    <TD rowspan="3"><IMG src="<%=imagepathurl;%>/spacer.gif" width="20" border="0"></TD>
	  </TR>
	  <TR>
	    <td valign="top">
<!-- End Navigation Bar Include  -->

<!-- Main content starts here -->
	<table border="0" cellpadding="0" cellspacing="0" width="100%" align="top">
	<tr>
		<td width="100%" valign="top"> 
	
		<!-- put content here -->
		<table width="600" border="0" cellspacing="2" cellpadding="3" align="LEFT" valign="TOP">

		<tr  bgcolor="#d8d7b8">
			<td align="LEFT" valign="TOP">
				<font color="#000066" face="Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular" size="-1">
				<b> Member Information: </b></font>
			</td>
		</tr>

		<tr>
			<td>
			<!-- Member Information -->
			<table border=0 cellspacing="4" cellpadding="0" align="LEFT">
			<tr>
				<td align="RIGHT" valign=BASELINE nowrap>
					<font size="-1"><b> First Name: </b></font>
				</td>
				<td align="LEFT" valign=BASELINE>
					<font size="-1"><%=escapeHTML(account_obj.firstname);%></font>
				</td>
			</tr>
			<tr>
				<td align="RIGHT" valign=BASELINE nowrap>
					<font size="-1"><b> Last Name: </b></font>
				</td>
				<td align="LEFT" valign=BASELINE>
					<font size="-1"><%=escapeHTML(account_obj.lastname);%></font>
				</td>
			</tr>

			<tr>
				<td align="RIGHT" valign=BASELINE nowrap>
					<font size="-1"><b> Email Address: </b></font>
				</td>
				<td align="LEFT" valign=BASELINE>
					<font size="-1">
					<!-- <a href="mailto:<%=account_obj.address == null ? account_obj.name : account_obj.address;%>"> -->
					<%=account_obj.address == null ? account_obj.name : account_obj.address;%>
					<!-- </a> --></font>
				</td>
			</tr>

			<tr>
				<td align="RIGHT" valign=BASELINE nowrap>
					<font size="-1"><b> Created: </b></font>
				</td>
				<td align="LEFT" valign=BASELINE>
					<font size="-1"><%=account_obj.createTime.format( "%m/%d/%Y", tw.session.account.userTimeZoneDelta );%>
					</font>
				</td>
			</tr>

			<tr>
				<td align="RIGHT" valign=BASELINE nowrap> 
					<font size="-1"><b> Last Accessed: </b></font>
				</td>
				<td align="LEFT" valign=BASELINE> 
					<font size="-1"><%=account_obj.loginTime.format( "%m/%d/%Y", tw.session.account.userTimeZoneDelta );%>
					</font>
				</td>
			</tr>
			</table>
			</td>
		</tr>

		<!-- TODO: These statistics should be displayed only for paid members -->
		<% if ( canCreatePackages ) { %>
		<tr>
			<td>
			<!-- Delivery Statistics -->
			<table border=0 cellspacing=0 cellpadding=2 align=left>
			<tr>
				<td  align="right" valign="BASELINE" nowrap>
					<font size="-1"><b> Message Sent in Current Month: </b></font>
				</td>
				<td align=left valign=BASELINE>
					<font size="-1"><%=usage_count;%></font>
				</td>
			</tr>
			<% if ( unit_balance != "none" ) { %>
			<tr>
				<td align="right" valign=BASELINE nowrap>
					<font size="-1"><b> Message Units remaining in Account: </b></font> 
				</td>
				<td align=left valign=BASELINE>
					<font size="-1"><%=unit_balance;%></font>
				</td>
			</tr>
			<% } %>
			</table>
			</td>
		</tr>
		<% } %>

		<tr>
			<!-- Empty row -->
			<td height="10"><img src="<%=imagepathurl;%>/spacer.gif"></td>
		</tr>

		<tr bgcolor="#d8d7b8">
			<td align="LEFT" valign="TOP">
				<font color="#000066" face="Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular" size="-1">
				<b> Authentication: </b></font>
			</td>
		</tr>

		<tr>
			<td>
			<!-- Certificate management links -->
			<table>
			<% if ( authenticationMethod != certificateAuthenticationMethod ) { %>
			<!-- TODO: Show this only for TAP accounts -->
			<tr>
				<td width="10">&nbsp;</td>
				<td width="485">
					<b><a href="<%=tw.httpGateway.getUrl('SGMS_TxnConvertTAPtoTAC.tpl');%>" class="navmenu">
					<font size="-1">Convert to Digital-ID Based Login</font></a></b>
				</td>
			</tr>
			
			<% } else { %>

			<!-- TODO: Show this only for accounts with certificate -->
<!--
			<tr>
				<td width="10">&nbsp;</td>
				<td width="485">
					<b><a href="<%=tw.httpGateway.getUrl('SGMS_RevokeCert.tpl');%>"><font size="-1">Revoke My Digital-ID</font></a></b>
				</td>
			</tr>
-->
			<tr>
				<td width="10">&nbsp;</td>
				<td width="485">
					<b><a href="javascript:DoClick()"><font size="-1">Change Password</font></a></b>
				</td>
			</tr>
			<% } %>
			</table>
			</td>
		</tr>

	<% if ( authenticationMethod != certificateAuthenticationMethod ) { %>
		<!-- TODO: Show this only for TAP accounts -->
		<tr>
			<!-- Empty row -->
			<td height="10"><img src="<%=imagepathurl;%>/spacer.gif"></td>
		</tr>

		<tr bgcolor="#d8d7b8">
			<td  align="LEFT" valign="TOP">
				<font color="#000066" face="Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular" size="-1">
				<b>Change Password: </b></font>
			</td>
		</tr>

		<tr>
			<td>
			<!-- Change Member Password -->
				<form name="update_form" action="<%=tw.httpGateway.getUrl('TW_TxnAccAccountInfoMemberUpdate.tpl');%>" method="POST">
				<table border=0 cellspacing="4" cellpadding="0" align="LEFT" valign="TOP">
				<tr>
					<td align="RIGHT" valign="BASELINE" nowrap>
						<font size="-1"><b> Current Password: </b></font>
					</td>
					<td align="LEFT" valign="BASELINE">
						<input type=password size="25" maxlength=40 name="oldpassword" value="">
					</td>
				</tr>

				<tr>
					<td align="RIGHT" valign="BASELINE"	nowrap>
						<font size="-1"><b> New Password: </b></font>
					</td>
					<td align="LEFT" valign="BASELINE">
						<input type=password size="25" maxlength=40 name="newpassword" value="">
					</td>
				</tr>

				<tr>
					<td align="RIGHT" valign="BASELINE" nowrap>
						<font size="-1"><b> Confirm New Password: </b></font>
					</td>
					<td align="LEFT" valign="BASELINE">
						<input type=password size="25" maxlength=40 name="newpassword2" value="">
					</td>
				</tr>

				<tr>
					<td>&nbsp;</td>
					<td>
						<font face="Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular" size="-2">
						<%=minAcctPasswordReqs; %>
						</font>
					</td>
				</tr>

				<tr>
					<td height="10"><img src="<%=imagepathurl;%>/spacer.gif"></td>
				</tr>

				<tr>
					<td align="center" colspan="2">
						<table border="0" cellpadding="0" cellspacing="0">
						<tr>
							<td><img height="19" width="9" src="<%=imagepathurl;%>/buttonGreyLeft.gif"></td>
							<td bgcolor="#d8d7b8"  height="19" nowrap><a href="javascript:document.update_form.submit()" class="buttonText">
							<font face="Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular" size="2" color="#000066">Update</font></a></td>
							<td><img height="19" width="9" src="<%=imagepathurl;%>/buttonGreyRight.gif"></td>
						</tr>
						</table>
					</td>
				</tr>
				</table>
				<!-- These values are required for the transaction but are not user changeable -->
				<input type=hidden name="hint_phrase" value="">
				<input type=hidden name="locale" value="<%=default_index;%>">
				<input type=hidden name="usertime" value="<%=user_time;%>">
				</form>
			</td>
		</tr>
	<% } %>

		</table>
		</td>
	</tr>
	</table>

<!-- Navigation bar include -->
	    </td>
	  </tr>
	  <tr>
	    <td colspan="1" nowrap valign="bottom">
	      <script language="javascript">
		
		function copyright ()
		{
		//Create a new window
		var newWin = window.open("legaldocs/copyright.htm", "popup_1", 'toolbar=1,location=0,directories=0,status=0,menubar=0,scrollbars=1,resizable=0,width=620,height=375'); 		
		}
	
		function privacy ()
		{
		//Create a new window
		var newWin = window.open("legaldocs/privacy.htm", "popup_1", 'toolbar=1,location=0,directories=0,status=0,menubar=0,scrollbars=1,resizable=0,width=620,height=375'); 	
		}
	      </script>
	      <IMG src="<%=imagepathurl;%>/dot.gif" height="80"><BR>
	      <a href="javascript:copyright();"><span class="copyrt">Copyright &#169; 2001,</span></a>
	      &nbsp;<a href="javascript:privacy();"><span class="copyrt">Privacy Policy,</span></a><span class="copyrtblack"> VeriSign, Inc. All Rights Reserved<br></span>
	      <BR><BR>
	    </td>
	  <tr>
	</table>
    </td>
  </tr>
</table>
<!-- End Navigation Bar Include  -->
</body>
</html>

