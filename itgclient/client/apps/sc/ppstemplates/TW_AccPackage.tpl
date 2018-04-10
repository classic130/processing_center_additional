<!-- File name: TW_AccPackage.tpl -->
<!-- Copyright (c) 1993-2001 Tumbleweed Communications Corp. All Rights Reserved. -->
<%@include file="TW_GlobalHeaderMenu.tpl" %>
<%@include file="TW_HelperAccBillingCode.tpl" %>
<%@include file="TW_HelperSession.tpl" %>
<%@include file="TW_HelperThrowErrors.tpl" %>
<%@include file="SGMS_HelperAccount.tpl" %>


<!-- NOTE:  This page has no associated DreamWeaver template -->
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 3.2 Final//EN">
<HTML>
<%

// expired accounts can not send packages (except COP & CSR)
if( (tw.session.isLoggedIn == false) || (tw.session.account.effectiveCapabilities.canCreatePackages != 1) || (isExpiredAllowedCreatePackage() == false) ){
	TW_ThrowError("TW_E_ACCOUNT_INSUFFICIENT_PRIVILEGE_CANNOT_CREATE_PACKAGE");
}

var table_border_TW_AccPackage = 0; //debugging layout
var pageTitle = "Compose";
var imagepathurl = tw.httpGateway.getImgPathUrl();
var helppathurl = tw.httpGateway.getHelpUrl();
var microsoft_useragent = "microsoft";
var current_useragent = tw.request.userAgentVendor;
var createable_options = tw.session.currentPackageCreateable;
var constraints_options = createable_options.getPackageConstraints;
var notification_options = createable_options.notificationOptions;
var confirmation_options = createable_options.confirmationOptions;
var caps = tw.session.account.effectiveCapabilities;
var is_logged_in = tw.session.isLoggedIn;
var is_reply = 	(createable_options.type == tw.constant.TW_PACKAGE_TYPE_PREPAID_REPLY) ||
				(createable_options.type == tw.constant.TW_PACKAGE_TYPE_REPLY);
var is_forward = (createable_options.type == tw.constant.TW_PACKAGE_TYPE_FORWARD);
var last_form_action	= tw.request.getFormFieldValue( "submit_action" );
var	is_reply_all 		= last_form_action == tw.constant.HTTP_GATEWAY_ACCOUNT_SESSION_COMMAND_REPLAY_ALL;
var user_has_account	= is_logged_in;
// Try to figure out if the recipient has a account and its email address
var recipient_email		= "";
// Note: calling tw.session.currentDelivery in a new package context will cause a Generic exception !!!
if ( is_reply ) {
	var current_delivery = tw.session.currentDelivery;
	var current_package = TW_Package.getPackageById( current_delivery.packageId );
	
	var current_recipient;
	// recipientId == 0 if the recipient is the sender.
	if ( current_delivery.recipientId != 0 ) {
		current_recipient = current_package.getRecipientById(current_delivery.recipientId );
		if ( current_recipient.description == tw.constant.SINGLE_RECIPIENT ) {
			recipient_email = current_recipient.singleRecipient.address;
			user_has_account = (current_recipient.singleRecipient.accountId != 0);
		}
	} else {
		// We reply and we are the sender therefore we are replying from the outbox
		user_has_account = true;
	}
}
if ( is_forward ) {
	var current_delivery = tw.session.currentDelivery;
	var current_package = TW_Package.getPackageById( current_delivery.packageId );
}
if ( is_logged_in ) {

    // set the active menu
    TW_SetActiveMenuItem( tw.constant.TW_MENU_GROUP_PRE_FOLDERS, "Compose" );

}

// set the help url
TW_SetHelpMenuUrl(  "Help", "javascript:GoHelp('Sending')" );

// true if we want to show the fallback page (Account-based send to non-account holders)
var show_fallback_page = (arguments.bad_to.length != 0) ||
						 (arguments.bad_cc.length != 0) ||
						 (arguments.bad_bcc.length != 0);

// get the message ID of the VSSC ActiveX/Plugin
// 0 if creating a new package, !0 if the ID is bounced when attaching a file
var messageID = arguments.messageID;

//Check if we are logged in to set an appropriate cancel button URL
if ( !is_logged_in ) {
	var cancel_url = tw.httpGateway.getUrl('TW_TxnAccPackageCancelToPackageDelivery.tpl');
} else if ( is_reply || is_forward ) {
	var cancel_url = tw.httpGateway.getUrl('TW_TxnAccDeliveryPageEntry.tpl');
	cancel_url = tw.httpGateway.appendUrlQueryVariable( cancel_url,
														 tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_STOREITEM_ID,
														 current_delivery.packageId );
	var cancel_folder_id = tw.request.getQueryString( tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_FOLDER_ID, "none" );
	if ( cancel_folder_id != "none" ) {
		cancel_url = tw.httpGateway.appendUrlQueryVariable( cancel_url,
															tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_FOLDER_ID,
															cancel_folder_id );
		var cancel_folder_index = tw.request.getQueryString( tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_TABLE_START_INDEX, "none");
		if ( cancel_folder_index != "none" ) {
			cancel_url = tw.httpGateway.appendUrlQueryVariable( cancel_url,
																tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_TABLE_START_INDEX,
																cancel_folder_index );
		}
	}
} else {
	var cancel_url = tw.httpGateway.getUrl('TW_TxnAccPackageStart.tpl');
}

var reply_initialize = "";
if ( is_reply && tw.request.getFormFieldValue("display_for_first_time") == "" ) {
	// This code is included for the first reply page only.
	var reply_initialize = "InitVSSC(0); ";
}

var input_fields_size = 70;
if (tw.request.userAgentVendor == "netscape" ) {
	input_fields_size = 42;
}
%>

<SCRIPT language=JavaScript>
<!-- -->Many features on this page will not operate as this browser does not support Javascript.
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

//-->
</SCRIPT>
<HEAD>
<META HTTP-EQUIV="pragma" CONTENT="no-cache">
<!-- put here all page specific the global variables, TW script or JavaScript. See AccDeliveryFolderView.tpl for example -->

<!-- VSSC ErrorForm -->
<%@include file="SGMS_VSSCErrorFormInclude.tpl" %>

<!-- VSSC ComposeInclude -->
<%@include file="SGMS_VSSCComposeInclude.tpl" %>

<!-- AttachmentsTable -->
<%@include file="SGMS_HandleAttachments.tpl" %>

<!-- Global Initialization -->
<SCRIPT language=JavaScript>
	InitVSSC( <%=messageID;%> );
	ConfigurePTA();
	<% // This code is included for the first reply or forward page only.
	if ( tw.request.getFormFieldValue("display_for_first_time") == "" ) { %>
		<% if(tw.request.userAgentVendor == "microsoft" ) {	%>
			<% if ( is_reply ) { %>
				files = new Array();
				var reply_body = escapeMessage( VSSC.Body, "reply" );
			<% }
			if ( is_forward ) {	%>
				var forward_body = escapeMessage ( VSSC.Body, "forward" );
			<% } 
		 } else { %>
			<%if ( is_reply ) { %>
				files = new Array();
				var reply_body = escapeMessage( VSSC.get_VSSC_Body(), "reply" );
			<% }
			if ( is_forward ) {	%>
				var forward_body = escapeMessage ( VSSC.get_VSSC_Body(), "forward" );
			<% } %>
		<% } %>
	<% } %>
	var attachments_table = buildAttachmentsTable();
</SCRIPT>

<SCRIPT language=JavaScript>
<!-- -->Many features on this page will not operate as this browser does not support Javascript.
<!--

function DisplayStatusMsg( msg )
{
	status = msg;
	document.MM_returnValue = true;
}
function AboutThisField(file) {
  help_win=window.open(file,"AboutThisWin","toolbar=no,width=400,height=250,resizable=yes");
}
var w=""
var js_version = Math.round(parseFloat(navigator.appVersion)*1000)
if (js_version > 2300) {
	X = new Image(65, 57)
	X.src = "<%=imagepathurl;%>/UploadWindowGraphic.gif"
}

function showNSBanner()
{
<% if ( current_useragent != microsoft_useragent) { %>
	var cmd = document.form1.submit_action.value;
	var win_top = (screen.height / 2) - 80;
	var win_left = (screen.width / 2) - 150;
	if (((cmd=='command_add_file')||(cmd=='command_add_file_sgms')||(cmd=='command_send'))&&(js_version>2300)) {
		w = window.open("", "UW", "scrollbars=1,width=300,height=160,top=" + win_top + ",left=" + win_left + ",resizable=1")
		if (cmd == 'command_add_file' ) {
			wstr="<html><head><title>VeriSign PrivatePath service</title> \n"
			wstr+="<body bgcolor=#ffffff> \n"
			wstr+="<center><font color='#003399' face='Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular' size='-1'><B>Your file is being uploaded to the PrivatePath<sup><font size='-2'>TM</font></sup>  server.</B></font><p> \n"
			wstr+="<img src='<%=imagepathurl;%>/UploadWindowGraphic.gif' WIDTH=65 HEIGHT=57 border=0>\n"
			wstr+="</center>"
		} else {
			wstr="<html><head><title>VeriSign PrivatePath service</title> \n"
			wstr+="<table width='100%' height='35' border='0'>"
			wstr+="<tr bgcolor='#d8d7b8'>"
			wstr+="<td width='100%'>"
			wstr+="<font color='#000066' face='Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular' size=2>"
			wstr+="<b>Uploading message<br></b></font>"
			wstr+="</td></tr>"
			wstr+="<tr><td>"
			wstr+="<font color='#000066' face='Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular' size=2>"
			wstr+="Your message is being uploaded to the PrivatePath service.<br>This window will close when uploading is complete.<br>"
			wstr+="</font>"
			wstr+="</td></tr>"
			wstr+="</table>"
		}
		w.document.write(wstr)
		w.document.write("</body></html> \n")
		w.document.close()
		setTimeout("document.form1.submit()", 2000)
	} else {
		<%=reply_initialize; %>
		document.form1.submit()
	}
<% } else { %>
	// Do nothing for IE
<% } %>
}


function showBanner()
{

	var win_top = (screen.height / 2) - 95;
	var win_left = (screen.width / 2) - 150;
	var imageurl = "<%=imagepathurl;%>";
	var imagestr = "<img src='";
	imagestr+=imageurl;
	imagestr+="/animated.gif' width='53' height='18' border='0' alt=''>";
	var cmd = document.form1.submit_action.value;
	if (((cmd=='command_add_file')||(cmd=='command_add_file_sgms')||(cmd=='command_send'))&&(js_version>2300)) {
		w = window.open("", "UW", "scrollbars=0,width=300,height=190,top=" + win_top + ",left=" + win_left + ",resizable=1")
		if (cmd == 'command_add_file' ) {
			wstr="<html><head><title>VeriSign PrivatePath service</title> \n"
			wstr+="<body bgcolor=#ffffff> \n"
			wstr+="<center><font color='#003399' face='Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular' size='-1'><B>Your file is being uploaded to the SGMS<sup><font size='-2'>TM</font></sup>  server.</B></font><p> \n"
			wstr+="<img src='<%=imagepathurl;%>/UploadWindowGraphic.gif' WIDTH=65 HEIGHT=57 border=0>\n"
			wstr+="</center>"
		} else {
			wstr="<html><head><title>VeriSign PrivatePath service</title> \n"
			wstr+="<table width='100%' height='35' border='0'>"
			wstr+="<tr bgcolor='#d8d7b8'>"
			wstr+="<td width='100%'>"
			wstr+="<font color='#000066' face='Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular' size=2>"
			wstr+="<b>Uploading message<br></b></font>"
			wstr+="</td></tr>"
			wstr+="<tr><td>"
			wstr+="<font color='#000066' face='Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular' size=2>"
			wstr+="<br>Your secure message is being sent to the PrivatePath service.<br><br>"
			wstr+="This window will close when uploading is complete.<br><br>"
			wstr+=imagestr
			wstr+="</font></td></tr>"
			wstr+="</table>"
		}
		w.document.write(wstr)
		w.document.write("</body></html> \n")
		w.document.close()
		setTimeout("document.form1.submit()", 2000)
	} else {
		<%=reply_initialize; %>
		document.form1.submit()
	}

}

function ConvertEmailToLowerCase()
{
	var strEmail;

	strEmail = document.form1.to.value;
	if(strEmail != "") 
		document.form1.to.value = strEmail.toLowerCase();

	strEmail = document.form1.cc.value;
	if(strEmail != "") 
		document.form1.cc.value = strEmail.toLowerCase();

	strEmail = document.form1.bcc.value;
	if(strEmail != "") 
		document.form1.bcc.value = strEmail.toLowerCase();


}



// Popup upload window and submit form.
function DoClick( cmd )
{
	document.form1.submit_action.value = cmd;
	document.form1.vssc_attached_files.value = getAttachmentsCount();

	if (cmd == 'command_send') {
		if(!validateTORecipients())
			return;
		if(!validateCCRecipients())
			return;
		if(!validateBCCRecipients())
			return;

		<%=reply_initialize; %>
		errCode = ResolveRecipients();
		if (errCode != 0) {
			//alert("Error while resolving recipients");
			return;
		}

		ConvertEmailToLowerCase();

		// alert("Checking PRC");
		if (prcRecipients.length>0) {
			openDialog();
		} else {
			submitWithPRC( false );
		}
	}

	// TODO: dead code here?
}


// AddressBook:
<%
	var acc_addr_book_url = tw.httpGateway.getUrl('TW_TxnAccPackageAddressBookFrame.tpl');
	acc_addr_book_url = tw.httpGateway.appendUrlQueryVariable(acc_addr_book_url,"addrbooktype","account");
%>
// AB:
var kid_win=null;
function AddressBookAccount()
{
	if (kid_win==null) {
		kid_win = window.open("<%=acc_addr_book_url;%>", "kid_win",
		"resizable=1,scrollable=1,width=300,height=400");
	} else {
		if (kid_win.focus) kid_win.focus();
	}
}



var child_win=null;

function AddressBook()
{
	if (child_win==null) {
		child_win = window.open("<%=tw.httpGateway.getUrl('TW_TxnAccPackageAddressBookFrame.tpl');%>", "child_win",
		"resizable=1,scrollable=1,width=300,height=400");
	} else {
		if (child_win.focus) child_win.focus();
	}
}
function CloseAddressBook()
{
	if ( (child_win) && (!child_win.closed) ) {
		child_win.close();
		child_win=null;
	}
}
function InitFocus()
{
	if ((document.form1)&&(js_version>2300)) {
		<% if ( createable_options.type == tw.constant.TW_PACKAGE_TYPE_FORWARD ) { %>
			document.form1.to.focus();
		<% } else if ( is_reply ) { %>
			document.form1.message.focus();
		<% } else if ( constraints_options.isAddingRecipientsAllowed ) { %>
			document.form1.to.focus();
		<% } else { %>
			document.form1.subject.focus();
		<% } %>
	}
}
function checkCredit()
{
	<%
	if (tw.session.isLoggedIn) {
		var custArray = tw.session.account.queryCustomObjects("TW_NAME='SGMS_ACCOUNT_PROPERTY'; ; ;7INT", false);
		if (custArray.length > 0) {
			var unit_balance = custArray[0].SGMS_message_unit_balance;
		} else {
			// the property is not found for some reason.
			var unit_balance = "";
		}
		if ( unit_balance != "" ) {
			// This function will check the balance
			%>
	var MsgSize = GetMessageSize();
	if(bErrorPresent == 1)
		return false;
	MsgSize = MsgSize/1.76;
	if ( calculatePrice(MsgSize) > <%=unit_balance; %> ) {
		alert("You don't have enough credits to send this message.\nPlease remove some recipients or attachments.");
		return false;
	}
		<%
		}
	} else {
		// not logged in, so no balance
		var unit_balance = "";
	}
	%>
	return true;
}


function calculateCredits()
{
	var file_list, file_size, total_size;

	total_size = 0;
		// get attached file list
	file_list = GetAttachedFileList();

	if(bErrorPresent == 1)
		return;

	if(file_list != "") {
		file_list = "" + file_list;
		var file_array = file_list.split(",");
		for(var i = 0; i < file_array.length; i++) {

			if(file_array[i] != "") {
				file_size = GetSelectedAttachmentSize(file_array[i]);

				if(bErrorPresent == 1)
					return;

				total_size += file_size;
			}
		}
	
	} 
/*
	   // calculate size of encoded data
	if(total_size % 3 == 0)
		total_size = (total_size/3)*4;
	else
		total_size = parseInt((total_size/3), 10) * 4 + 4;

	total_size += parseInt((total_size / 76), 10) * 2 ; 

	   // add overhead (around 4K)
	total_size += 4096;

	// calculate encoded size again
	if(total_size % 3 == 0)
		total_size = (total_size/3)*4;
	else
		total_size = parseInt((total_size/3), 10) * 4 + 4;

	total_size += parseInt((total_size / 76), 10) * 2 ; 
*/
	return calculatePrice(total_size);
}


//-->
</SCRIPT>

<!-------------------------------->

<title>VeriSign PrivatePath service</title>
<link rel="stylesheet" href="<%=tw.httpGateway.getStylesheetPathUrl();%>/verisign.css">
</HEAD>
<body bgcolor="#ffffff" background="<%=imagepathurl;%>/background.gif" leftmargin="0" topmargin="0"  marginwidth="0" marginheight="0" name="main"
onUnload="if ((w) && (!w.closed)) w.close(); CloseAddressBook();  if ((recip_win) && (!recip_win.closed)) recip_win.close(); "
<% if ( is_reply && tw.request.getFormFieldValue("display_for_first_time") == "" ) { %>
onLoad="InitFocus(); document.form1.message.value = reply_body;">
<% } else if ( is_forward && tw.request.getFormFieldValue("display_for_first_time") == "" ) { %>
onLoad="InitFocus(); document.form1.message.value = forward_body;">
<% } else { %>
onLoad="InitFocus(); UpdateHTMLFromVSSC();">
<% } %>

<SCRIPT LANGUAGE=JavaScript>
<!--
   CheckIfIDValid();
//-->
</SCRIPT>


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

<!-- Main content starts here -->		<table width="600" cellpadding=0 cellspacing=0 border="<%=table_border_TW_AccPackage;%>">
				<tr>
					<td colspan=2>
						<%	var package_form_url = tw.httpGateway.getUrl('TW_TxnAccPackage.tpl'); %>
						<form name="form1" action="<%=package_form_url;%>" method="POST" enctype="multipart/form-data">
						<%	var display_for_first_time = tw.request.getFormFieldValue("display_for_first_time") == "" ? 1 : 0;%>
						<input type="hidden" name="display_for_first_time" value="1">
						<input type="hidden" name="submit_action" value="none">
						<input type="hidden" name="vssc_message_id" value="<%=messageID; %>">
						<input type="hidden" name="vssc_attached_files" value="0">
						<table valign="TOP" cellpadding=0 cellspacing="3" border="<%=table_border_TW_AccPackage;%>" width="100%">
							<% if (arguments.show_error) { %>
								<tr>
									<td align="center" colspan="6">
										<font size="-1" color="#FF0000">
										<b>There was a problem with your message.</b></font><br>
										<font size="-1">
										<%=arguments.error;%><br>
										(Error code <%=arguments.error_code;%>)</font>
									</td>
								</tr>
								<tr><td colspan=6><img height=10 src="<%=imagepathurl;%>/dot.gif" width=20></td></tr>
								<tr><td colspan=6><hr width=100%></td></tr>
								<tr><td colspan=6><img height=10 src="<%=imagepathurl;%>/dot.gif" width=20></td></tr>
							<% } %>
<!-- In the case where some recipients don't have accounts -->
							<% if (show_fallback_page) { %>
								<tr>
									<td colspan=6><font size="-1" color="#FF0000">
										<b>Unable to send the message to some recipients</b></font>
									</td>
								</tr>
								<tr>
									<td colSpan=6><img height=10 src="<%=imagepathurl;%>/dot.gif" width=20></td>
								</tr>
								<tr>
									<td colspan=6><font size="-1">The following recipients have chosen not to receive PrivatePath messages:</td>
								</tr>
								<tr>
									<td align="center" colspan="6">
										<table>
											<% if (arguments.bad_to.length != 0) { %>
												<tr>
													<td valign="baseline" align="right">
														<font face="Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular" size="-1">
														<b>To:</b></font></td>
														<td valign="baseline" colspan="2"><%=arguments.bad_to;%></td>
												</tr>
											<% }  %>
											<% if (arguments.bad_cc.length != 0) { %>
												<tr>
													<td valign="baseline" align="right">
														<font face="Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular" size="-1">
														<b>CC:</b></font></td>
														<td valign="baseline" colspan="2"><%=arguments.bad_cc;%></td>
												</tr>
											<% }  %>
											<% if (arguments.bad_bcc.length != 0) { %>
												<tr>
													<td valign="baseline" align="right">
														<font face="Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular" size="-1">
														<b>BCC:</b></font></td>
														<td valign="baseline" colspan="2"><%=arguments.bad_bcc;%></td>
												</tr>
											<% }  %>
										</table>
									</td>
								</tr>
								<tr>
									<td colSpan=6><img height=10 src="<%=imagepathurl;%>/dot.gif" width=200></td>
								</tr>
								<tr>
									<td colSpan=6>
										<% if ( !constraints_options.isSecurityModifiable && show_fallback_page ) { %>
											Remove these addresses and send the message to the remaining recipients. Contact the removed recipients by other means.
										<% } else { %>
											You may handle this one of the following ways:
											<ul>
												<li>Do not change security options. Remove the recipients who do not have the PrivatePath account from the To, CC, and BCC lists, and send again.</li><p>
												<% if (constraints_options.canEnrollRecipients) { %>
													<li>Continue to use Account security, but choose the option to create an account for those recipients without accounts, and send again.</li><p>
												<% } %>
												<% if (constraints_options.isSecurityModifiable) { %>
													<li>Select a different security option for all recipients and send again. You can select Low, Standard, or Package.</li><p>
												<% } %>
											</ul>
										<% } %>
										<hr width=100%>
									</td>
								</tr>
							<% } %>
<!-- Building the SGMS message units display -->
							<%
								if ( unit_balance != "" ) {
							%><tr>
								<td valign="top" align="right">
									<!--a href="javascript:AboutThisField('<%=helppathurl;%>/Central/AboutThisFieldBcc.htm')"
									onMouseOut="DisplayStatusMsg(' ');return document.MM_returnValue"
									onMouseOver="DisplayStatusMsg('About this field...');return document.MM_returnValue" class="formlabel"-->
									<font face="Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular" size="-1">
									<b>Postage</b><!--/a--><b>:</b></font></td>
								<td valign="top" colspan="5"><font size="-1">
								Your account has<b> <%=unit_balance; %> </b>Message Credits remaining. 
								</font></td>
							</tr>
							<tr>
								<td><img height=5 src="<%=imagepathurl;%>/spacer.gif"></td>
							</tr>
							<% 
							}
							%>
<!-- Building the To, CC, BCC fields -->
							<%
								var package_recipients = createable_options.recipients;
								var all_to_recipients = "";
								var all_cc_recipients = "";
								var all_bcc_recipients = "";
								var i = 0;
								for ( ; i< package_recipients.length; ++i ) {
									if ( package_recipients[i].description == tw.constant.SINGLE_RECIPIENT ) {
										if ( package_recipients[i].category == tw.constant.RECIPIENT_CATEGORY_TO ) {
											if ( all_to_recipients != "" ) all_to_recipients = all_to_recipients.concat(", ");
											all_to_recipients = all_to_recipients.concat( package_recipients[i].singleRecipient.address);
										} else if ( package_recipients[i].category == tw.constant.RECIPIENT_CATEGORY_CC ) {
											if ( all_cc_recipients != "" ) all_cc_recipients = all_cc_recipients.concat(", ");
											all_cc_recipients = all_cc_recipients.concat( package_recipients[i].singleRecipient.address);
										} else if ( package_recipients[i].category == tw.constant.RECIPIENT_CATEGORY_BCC ) {
											if ( all_bcc_recipients != "" ) all_bcc_recipients = all_bcc_recipients.concat(", ");
											all_bcc_recipients = all_bcc_recipients.concat( package_recipients[i].singleRecipient.address);
										}
									} else {
										if ( package_recipients[i].category == tw.constant.RECIPIENT_CATEGORY_TO ) {
											if ( all_to_recipients != "" ) all_to_recipients = all_to_recipients.concat(", ");
											all_to_recipients = all_to_recipients.concat( package_recipients[i].recipientList.mailList);
										} else if ( package_recipients[i].category == tw.constant.RECIPIENT_CATEGORY_CC ) {
											if ( all_cc_recipients != "" ) all_cc_recipients = all_cc_recipients.concat(", ");
											all_cc_recipients = all_cc_recipients.concat( package_recipients[i].recipientList.mailList);
										} else if ( package_recipients[i].category == tw.constant.RECIPIENT_CATEGORY_BCC ) {
											if ( all_bcc_recipients != "" ) all_bcc_recipients = all_bcc_recipients.concat(", ");
											all_bcc_recipients = all_bcc_recipients.concat( package_recipients[i].recipientList.mailList);
										}
									}
								}
								var to_escaped = escapeHTML(all_to_recipients);
								var cc_escaped = escapeHTML(all_cc_recipients);
								var bcc_escaped = escapeHTML(all_bcc_recipients);
								if ( is_reply && display_for_first_time ) {

									// Don't build the BCC clause
									bcc_escaped = "";

								} else {
									to_escaped = tw.request.getFormFieldValue("to");
									cc_escaped = tw.request.getFormFieldValue("cc");
									bcc_escaped = tw.request.getFormFieldValue("bcc");
								}
								// Fix IE weirdosity
								var fields_cols = "64";
								if ( current_useragent == microsoft_useragent ) {
									fields_cols = "74";
								}
							%>
<!-- Displaying To field -->
							<tr>
								<td valign="top" align="right" nowrap>
									<!--a href="javascript:AboutThisField('<%=helppathurl;%>/Central/AboutThisFieldTo.htm')"
									onMouseOut="DisplayStatusMsg(' ');return document.MM_returnValue"
									onMouseOver="DisplayStatusMsg('About this field...');return document.MM_returnValue" class="formlabel"-->
									<font face="Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular" size="-1">
									<b>To</b></font><!--/a--><b>:</b></td>
									<td valign="top" colspan="5">
									<% if (constraints_options.isAddingRecipientsAllowed) { %>
										<input type="text" name="to" tabindex=1 cols="<%=fields_cols;%>" size="<%=input_fields_size;%>" value="<%=to_escaped;%>" onblur="return toOnBlur()">
									<% } else { %>
										<%=to_escaped;%>
										<input type=hidden name="to" value="<%=to_escaped;%>">
									<% } %>
								</td>
							</tr>
<!-- Displaying CC field -->
							<tr>
								<td valign="top" align="right">
									<!--a href="javascript:AboutThisField('<%=helppathurl;%>/Central/AboutThisFieldCc.htm')"
									onMouseOut="DisplayStatusMsg(' ');return document.MM_returnValue"
									onMouseOver="DisplayStatusMsg('About this field...');return document.MM_returnValue" class="formlabel"-->
									<font face="Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular" size="-1">
									<b>CC</b></font><!--/a--><b>:</b></td>
									<td valign="top" colspan="5">
									<% if (constraints_options.isAddingRecipientsAllowed) { %>
										<input type="text" name="cc" tabindex=1 cols="<%=fields_cols;%>" size="<%=input_fields_size;%>" value="<%=cc_escaped;%>" onblur="return ccOnBlur()">
									<% } else { %>
										<%=cc_escaped;%>
										<input type=hidden name="cc" value="<%=cc_escaped;%>">
									<% } %>
								</td>
							</tr>
<!-- Displaying BCC field -->
							<tr>
								<td valign="top" align="right">
									<!--a href="javascript:AboutThisField('<%=helppathurl;%>/Central/AboutThisFieldBcc.htm')"
									onMouseOut="DisplayStatusMsg(' ');return document.MM_returnValue"
									onMouseOver="DisplayStatusMsg('About this field...');return document.MM_returnValue" class="formlabel"-->
									<font face="Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular" size="-1">
									<b>BCC</b></font><!--/a--><b>:</b></td>
									<td valign="top" colspan="5">
									<% if (constraints_options.isAddingRecipientsAllowed) { %>
										<input type="text" name="bcc" tabindex=1 cols="<%=fields_cols;%>" size="<%=input_fields_size;%>" value="<%=bcc_escaped;%>" onblur="return bccOnBlur()">
									<% } else { %>
										<%=bcc_escaped;%>
										<input type=hidden name="bcc" value="<%=bcc_escaped;%>">
									<% } %>
								</td>
							</tr>
<!-- Address Book Line -->
							<% if (constraints_options.isAddingRecipientsAllowed) { %>
								<tr>
									<td></td>
									<td></td>
                                    <%
                                        var adminType = tw.session.account.SGMS_account_type == "SGMS_CSR" ||
                                            tw.session.account.SGMS_account_type == "SGMS_CHANNEL_OPERATOR" ||
                                            tw.session.account.category == tw.constant.TW_ADMINISTRATOR;
                                    %>
                                    <% if (adminType) { %>
                                        <td nowrap colspan="1"><font size="-1">Add addresses from:&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br><A HREF="javascript:AddressBook()" tabindex=1>Personal Address Book</A></font></td>
                                    <% } else { %>
                                        <td nowrap colspan="1"><font size="-1">Add addresses from:&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br><A HREF="javascript:AddressBook()" tabindex=1>Personal Address Book</A> or <A HREF="javascript:AddressBookAccount()" tabindex=1>Account Address Book</A></font></td>
                                    <% } %>
								</tr>
							<% } %>
							<tr>
								<td colspan=6><img height="8" width="20" src="<%=imagepathurl;%>/dot.gif"></td>
							</tr>
<!-- Building Subject & Message fields -->
							<%
								var package_message = "";
								var subject_escaped = "";
								var package_streams;
								// Compute right away the number of files present
								var number_of_files = 0;
								var message_index = -1;
								// Get the subject from the package descriptor
								subject_escaped = escapeHTML(createable_options.subject);
								package_streams = createable_options.packageStreamCreateableDescriptors;
								if ( package_streams.length == 0 ) {
									// No streams have been created yet: do not try to fetch subject & message from non-existent streams!
									// Example: password validation takes place within gateway, before request to create streams is ever 
									// made. Hence, if password validation fails, we cannot access streams to get subject & message (#8953).
									package_message = tw.request.getFormFieldValue( "message" );
								}
								else
								{
									// We have got to the stage where streams have already been created.
									// These can be used here.
									for ( i = 0; i < package_streams.length; i++ ) {
										if ( package_streams[i].usage == tw.constant.TW_STREAM_CONTENT_COVER ) {
											message_index = i;
										}
										if ( package_streams[i].usage == tw.constant.TW_STREAM_CONTENT ) {
											++number_of_files;
										}
									}
									if ( message_index != -1 ){
										// escape the html
										package_message = createable_options.readStream(message_index);
									}
								}
							%>
<!-- Displaying Subject field -->
							<tr>
								<td valign="top" align="right">
									<!--a href="javascript:AboutThisField('<%=helppathurl;%>/Central/AboutThisFieldSubject.htm')"
									onMouseOut="DisplayStatusMsg(' ');return document.MM_returnValue"
									onMouseOver="DisplayStatusMsg('About this field...');return document.MM_returnValue" class="formlabel"-->
									<font face="Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular" size="-1">
									<b>Subject</b></font><!--/a--><b>:</b>
								</td>
								<td valign="top" colspan="5">
									<input maxlength="127" name="subject" tabindex=1 size="<%=input_fields_size;%>" type=text value="<%=subject_escaped;%>">
								</td>
							</tr>
							<tr>
							<%
							// Preserve the Sign Message checkbox value on bounce
							var cb_vssc_sign = "";
							if (tw.request.getFormFieldValue( "vssc_sign" ) == "ON" ) cb_vssc_sign = "CHECKED";
							%>
									<td></td>
									<td colspan="5">
										<input type="checkbox" name="vssc_sign" tabindex=1 value="ON" <%=cb_vssc_sign;%>>
										<img src="<%=imagepathurl;%>/sign.gif" width="16" height="14" border="0" alt="" align="bottom">&nbsp;
										Digitally Sign
										&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
										<img src="<%=imagepathurl;%>/encrypt.gif" width="16" height="14" border="0" alt="">&nbsp;
										Encrypted&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
									
								
							<% if (constraints_options.isPriorityModifiable) { %>
<!-- Send priority -->
									<%
										var priority_list = "";
										if (createable_options.priority == tw.constant.PACKAGE_PRIORITY_BULK ) {
											priority_list = priority_list.concat(
												//"<OPTION VALUE=0 SELECTED>",
												//"Low",
												//"</OPTION>
												"<OPTION VALUE=1 SELECTED>",
												"Normal",
												"</OPTION><OPTION VALUE=2>",
												"Urgent",
												"</OPTION>"
											);
										} else if (createable_options.priority == tw.constant.PACKAGE_PRIORITY_NORMAL ) {
											priority_list = priority_list.concat(
												//"<OPTION VALUE=0>",
												//"Low",
												//"</OPTION><OPTION VALUE=1 SELECTED>",
												"<OPTION VALUE=1 SELECTED>",
												"Normal",
												"</OPTION><OPTION VALUE=2>",
												"Urgent",
												"</OPTION>"
											);
										} else if (createable_options.priority == tw.constant.PACKAGE_PRIORITY_EXPRESS ) {
											priority_list = priority_list.concat(
												//"<OPTION VALUE=0>",
												//"Low",
												//"</OPTION><OPTION VALUE=1>",
												"<OPTION VALUE=1>",
												"Normal",
												"</OPTION><OPTION VALUE=2 SELECTED>",
												"Urgent",
												"</OPTION>"
											);
										}
									%>
						
										&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
										<!--a href="javascript:AboutThisField('<%=helppathurl;%>/Central/AboutThisFieldPriority.htm')"
										onMouseOut="DisplayStatusMsg(' ');return document.MM_returnValue"
										onMouseOver="DisplayStatusMsg('About this field...');return document.MM_returnValue" class="formlabel"-->
										<font face="Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular" size="-1">
										Priority</font><!--/a-->&nbsp;&nbsp;
										<select name="send_priority" tabindex=1><%=priority_list;%></select>
									</td>
								</tr>
								<tr>
									<td colspan=6><img height="5" src="<%=imagepathurl;%>/dot.gif" width=20></td>
								</tr>
							<% } else { %>
								<tr><td>
									<input type=hidden name="send_priority" value="<%=createable_options.priority - 1;%>">
									<% tw.trace(tw.constant.TW_TRACE_DEBUG, "priority: " + createable_options.priority); %>
								</td></tr>
							<% } %>



<!-- Displaying Message field -->
							<tr>
			  					<td valign="top" align="right">
									<!--a href="javascript:AboutThisField('<%=helppathurl;%>/Central/AboutThisFieldMessage.htm')"
									onMouseOut="DisplayStatusMsg(' ');return document.MM_returnValue"
									onMouseOver="DisplayStatusMsg('About this field...');return document.MM_returnValue" class="formlabel"-->
									<font face="Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular" size="-1">
									<b>Message</b></font><!--/a--><b>:</b>
								</td>
								<td valign="top" colspan="5">
									<textarea name="message" tabindex=1 cols="<%=input_fields_size;%>" rows="8" wrap="soft"><%=package_message;%></textarea>
								</td>
							</tr>
							
							<tr>
							 <td colspan=6>	
							  <table border="<%=table_border_TW_AccPackage;%>" cellpadding="0" valign="TOP" width="100%">
								<tr>
  		     					  <td width=10></td>
								  <td><img height=5 src="<%=imagepathurl;%>/spacer.gif"></td>
   		     					  <td width=10></td>
								</tr>
								<tr>
								 <td>
 									<table cellpadding=0 cellspacing=1 border="<%=table_border_TW_AccPackage;%>" width="100%" align=left>
								         <tr>
  								            <td><img height=5 src="<%=imagepathurl;%>/spacer.gif"></td>
								          </tr>
								        <tr>
								             <td align=left width=100%>
										      <table width="100%" border="<%=table_border_TW_AccPackage;%>" cellspacing="1" cellpadding="2" align="left" valign="TOP" bgcolor="#d8d7b8">
								                <tr bgcolor="#d8d7b8">
													<td width="100%" nowrap> 
													<font color="#000066" face="Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular" size="-1">
													<b>Attachments</b></font></td>
												</tr>
											  </table>
											</td>
								      </tr>
								      <tr>
								        <td colspan="2"><img src="<%=imagepathurl;%>/dot.gif"  width="1" height="5" border="0" alt=""></td>
								      </tr>
               
								    </table>
								  </td>
  		     					  <td></td>
								</tr>
								</table>
							  </td>
							</tr>
<!-- FIXME !!! Displaying hidden fields for testing purposes -->
							<input type="hidden" name="prc_recipients" value="">
                            <input type="hidden" name="prc_invite" value="OFF">
                                                        <input type="hidden" name="vssc_blob">
                                                        <input type="hidden" name="vssc_security" value="ON" >

<!-- SGMS - certificate resolution failure popup window -->
<script language="javascript">
// arrays containing the recipients with and without certificates
var resolvedRecipients;
var prcRecipients ;
var dialog = null;

initCertResolution();

function initCertResolution()
{
	resolvedRecipients = new Array();
	prcRecipients = new Array();
}

function addResolvedRecipient(email)
{
	//alert("Good:" + email);
	resolvedRecipients[resolvedRecipients.length] = email;
}

function addPRCRecipient(email)
{
	//alert("Bad:" + email);
	if (document.form1.prc_recipients.value == "")
		document.form1.prc_recipients.value = email;
	else
		document.form1.prc_recipients.value = document.form1.prc_recipients.value + "," + email;
	prcRecipients[prcRecipients.length] = email;
}

function completeCertResolution()
{
	if (prcRecipients.length>0) {
		return openDialog();
	}
	return 0;
}

function openDialog()
{
	//Netscape does not have this perhaps
	dialog = window.open('<%=tw.httpGateway.getUrl("SGMS_AccPackageCertResolutionFailed.tpl");%>',"Recipients", "width=600,height=500,resizable=yes,scrollbars=1,dependent=yes,toolbars=no,status=no");
}


function checkDialog()
{
	if (!dialog.closed() ) {
		dialog.focus();
	}

}

function promptForInvitation(opener)
{
	opener.close();
	dialog = window.open('<%=tw.httpGateway.getUrl("SGMS_AccPackageInvitePrompt.tpl");%>','Invite', "width=600,height=500,resizable=yes,scrollbars=1,dependent=yes,toolbars=no,status=no");
}

function submitWithPRC( usePRC )
{
	if( usePRC == false ){
		UpdateRecipients();
	}

	var res = VSSC_ONSEND(usePRC);
	if (res == 0) {
		if ( checkCredit() ) {
			
			showBanner();
			//document.sent_image.src = "img/sent.gif";
			//alert(document.form1.prc_recipients.value);
			document.form1.message.value='';
			document.form1.submit();
		}
	} //else
		 //alert("Could not create S/MIME" + res);
}

function stripSpaces(inputStr) 
{
    x = inputStr;
    while (x.substring(0,1) == ' ') x = x.substring(1);
    while (x.substring(x.length-1,x.length) == ' ') x = x.substring(0,x.length-1);
    return x;
}

function emailCheck (emailStr) 
{

	/* The following variable tells the rest of the function whether or not
	to verify that the address ends in a two-letter country or well-known
	TLD.  1 means check it, 0 means don't. */
	var checkTLD=0;

	/* The following is the list of known TLDs that an e-mail address must end with. */
	var knownDomsPat=/^(com|net|org|edu|int|mil|gov|arpa|biz|aero|name|coop|info|pro|museum)$/;

	/* The following pattern is used to check if the entered e-mail address
	fits the user@domain format.  It also is used to separate the username
	from the domain. */
	var emailPat=/^(.+)@(.+)$/;

	/* The following string represents the pattern for matching all special
	characters.  We don't want to allow special characters in the address. 
	These characters include ( ) < > @ , ; : \ " . [ ] */
	var specialChars="\\(\\)><@,;:\\\\\\\"\\.\\[\\]";

	/* The following string represents the range of characters allowed in a 
	username or domainname.  It really states which chars aren't allowed.*/
	var validChars="\[^\\s" + specialChars + "\]";

	/* The following pattern applies if the "user" is a quoted string (in
	which case, there are no rules about which characters are allowed
	and which aren't; anything goes).  E.g. "jiminy cricket"@disney.com
	is a legal e-mail address. */
	var quotedUser="(\"[^\"]*\")";

	/* The following pattern applies for domains that are IP addresses,
	rather than symbolic names.  E.g. joe@[123.124.233.4] is a legal
	e-mail address. NOTE: The square brackets are required. */
	var ipDomainPat=/^\[(\d{1,3})\.(\d{1,3})\.(\d{1,3})\.(\d{1,3})\]$/;

	/* The following string represents an atom (basically a series of non-special characters.) */
	var atom=validChars + '+';

	/* The following string represents one word in the typical username.
	For example, in john.doe@somewhere.com, john and doe are words.
	Basically, a word is either an atom or quoted string. */
	var word="(" + atom + "|" + quotedUser + ")";

	// The following pattern describes the structure of the user
	var userPat=new RegExp("^" + word + "(\\." + word + ")*$");

	/* The following pattern describes the structure of a normal symbolic
	domain, as opposed to ipDomainPat, shown above. */
	var domainPat=new RegExp("^" + atom + "(\\." + atom +")*$");

	/* Finally, let's start trying to figure out if the supplied address is valid. */
	
	/* Begin with the coarse pattern to simply break up user@domain into
	different pieces that are easy to analyze. */
	var matchArray=emailStr.match(emailPat);

	if (matchArray==null) {

	/* Too many/few @'s or something; basically, this address doesn't
	even fit the general mould of a valid e-mail address. */

	//alert("Email address seems incorrect (check @ and .'s)");
	return false;
	}
	var user=matchArray[1];
	var domain=matchArray[2];

	// Start by checking that only basic ASCII characters are in the strings (0-127).

	for (i=0; i<user.length; i++) {
		if (user.charCodeAt(i)>127) {
			//alert("Ths username contains invalid characters.");
			return false;
	    }
	}
	for (i=0; i<domain.length; i++) {
		if (domain.charCodeAt(i)>127) {
			//alert("Ths domain name contains invalid characters.");
			return false;
		}
	}

	// See if "user" is valid 

	if (user.match(userPat)==null) {

		// user is not valid

		//alert("The username doesn't seem to be valid.");
		return false;
	}

	/* if the e-mail address is at an IP address (as opposed to a symbolic
	host name) make sure the IP address is valid. */

	var IPArray=domain.match(ipDomainPat);
	if (IPArray!=null) {
		// this is an IP address
		for (var i=1;i<=4;i++) {
			if (IPArray[i]>255) {
				//alert("Destination IP address is invalid!");
				return false;
			}
		}
		return true;
	}

	// Domain is symbolic name.  Check if it's valid.
	 
	var atomPat=new RegExp("^" + atom + "$");
	var domArr=domain.split(".");
	var len=domArr.length;
	for (i=0;i<len;i++) {
		if (domArr[i].search(atomPat)==-1) {
			//alert("The domain name does not seem to be valid.");
			return false;
		}
	}

	/* domain name seems valid, but now make sure that it ends in a
	known top-level domain (like com, edu, gov) or a two-letter word,
	representing country (uk, nl), and that there's a hostname preceding 
	the domain or country. */

	if (checkTLD && domArr[domArr.length-1].length!=2 && 
		domArr[domArr.length-1].search(knownDomsPat)==-1) {
			//alert("The address must end in a well-known domain or two letter " + "country.");
			return false;
	}

	// Make sure there's a host name preceding the domain.
	if (len<2) {
		//alert("This address is missing a hostname!");
		return false;
	}

	// If we've gotten this far, everything's valid!
	return true;
}

function validateEMailList(inputText)
{
	var arrayOfStrings;
	var validList, invalidList;
	
	var inputList = inputText.value; // get value from text box
	
		// split e-mail list into array of e-mail addresses
		// using comma as delimiter
	arrayOfStrings = inputList.split(","); 
	validList = "";
	invalidList = "";
	for (var i=0; i < arrayOfStrings.length; i++) 
	{	
			// strip spaces before and after the e-mail addr
		arrayOfStrings[i] = stripSpaces(arrayOfStrings[i]);
		
			//split again using semicolon as delimiter this time
		arrayOfStrings1 = arrayOfStrings[i].split(";");
		for (var j=0; j < arrayOfStrings1.length; j++) 
		{	
			arrayOfStrings1[j] = stripSpaces(arrayOfStrings1[j]);
		
			if(arrayOfStrings1[j] != "") 
			{
					// validate e-mail address
				if(emailCheck(arrayOfStrings1[j]) == true) 
					validList = validList + arrayOfStrings1[j] + ",";
				else
					invalidList = invalidList + arrayOfStrings1[j] + "<br>";
			}
		}
	}
	
	if(validList != "")  // remove trailing comma
		validList = validList.substring(0,validList.length-1);

		// if there is no invalid e-mail addr, replace the text box value
		// with new formatted string
	if(invalidList != "") 
		invalidList = invalidList.substring(0,invalidList.length-4);
	else {	
		if(inputList != validList)
			inputText.value = validList;
	}
	
	return invalidList;
}

var recip_win = null;

function toOnBlur() {

/*
	var invalidList;
	
	// validate To List
	invalidList = validateEMailList(document.form1.to);
	
	if(invalidList != "")
		alert("Invalid e-mail addresses in To List: \n" + invalidList);
*/
	document.form1.credit_cost.value =  calculateCredits();

	validateTORecipients();

	//alert("credits:" + calculateCredits());

}

function ccOnBlur() {
/*
	var invalidList;
	
	// validate Cc List
	invalidList = validateEMailList(document.form1.cc);
	
	if(invalidList != "")
		alert("Invalid e-mail addresses in Cc List: \n" + invalidList);
*/
	document.form1.credit_cost.value =  calculateCredits();

	validateCCRecipients();

	//alert("credits:" + calculateCredits());

}

function bccOnBlur() {
/*
	var invalidList;
	
	// validate Bcc List
	invalidList = validateEMailList(document.form1.bcc);
	
	if(invalidList != "")
		alert("Invalid e-mail addresses in Bcc List: \n" + invalidList);
*/
	document.form1.credit_cost.value =  calculateCredits();

	validateBCCRecipients();

	//alert("credits:" + calculateCredits());
}

function validateTORecipients()
{
	var invalidList;
	var outputMsg = "";
	
	// validate To List
	invalidList = validateEMailList(document.form1.to);

	if(invalidList != "") {
		//alert("Invalid e-mail addresses in To List: \n" + invalidList);
		outputMsg = "<br>" + invalidList;
	}

	if(outputMsg != ""){

		if(recip_win == null || recip_win.closed)
			recip_win = window.open("", "InvalidRecipients", "scrollbars=1,width=300,height=160,resizable=1");
		else
			recip_win.document.close();
/*
		var html_str = "<html><head><title>VeriSign PrivatePath service</title> <body bgcolor=#ffffff>";
		html_str += "<center><font color='#003399' face='Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular' size='-1'><B>" + outputMsg +"</B></font><p> ";
		html_str += "<a href='javascript:close()' class='buttonText' tabindex=1>";
		html_str += "<font face='Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular' size='2' color='#000066'>"
		html_str += "Close</font></a>";
		html_str += "</center></body></html>";
*/

		var html_str = "<html><head><title>VeriSign PrivatePath service</title></head><body>";
		html_str += "<table width='100%' height=35 border=0>";
		html_str += "<tr bgcolor='#d8d7b8'><td width='100%'> ";
		html_str += "<font color='#000066' face='Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular' size=2>";
		html_str += "<b>The following e-mail addresses in the To: field are invalid.<br></b></font>";
		html_str += "</td></tr><tr><td><font color='#000066' face='Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular' size=2>";
		html_str += outputMsg;
		html_str += "<br><br><br><center><a href='javascript:close()'>Close</a><center></font></td></tr></table></body></html>";

		recip_win.document.write(html_str);

		recip_win.focus();

		return false;

	} else {
<% if ( current_useragent == microsoft_useragent) { %>
		if ((recip_win) && (!recip_win.closed)) 
			recip_win.close();	
<% } %>
	}

	return true;
}

function validateCCRecipients()
{
	var invalidList;
	var outputMsg = "";
	
	// validate Cc List
	invalidList = validateEMailList(document.form1.cc);
	
	if(invalidList != "") {
		//alert("Invalid e-mail addresses in Cc List: \n" + invalidList);
		outputMsg = outputMsg + "<br>" + invalidList;
	}
	
	if(outputMsg != ""){

		if(recip_win == null || recip_win.closed)
			recip_win = window.open("", "InvalidRecipients", "scrollbars=1,width=300,height=160,resizable=1");
		else
			recip_win.document.close();
/*
		var html_str = "<html><head><title>VeriSign PrivatePath service</title> <body bgcolor=#ffffff>";
		html_str += "<center><font color='#003399' face='Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular' size='-1'><B>" + outputMsg +"</B></font><p> ";
		html_str += "<a href='javascript:close()' class='buttonText' tabindex=1>";
		html_str += "<font face='Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular' size='2' color='#000066'>"
		html_str += "Close</font></a>";
		html_str += "</center></body></html>";
*/

		var html_str = "<html><head><title>VeriSign PrivatePath service</title></head><body>";
		html_str += "<table width='100%' height=35 border=0>";
		html_str += "<tr bgcolor='#d8d7b8'><td width='100%'> ";
		html_str += "<font color='#000066' face='Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular' size=2>";
		html_str += "<b>The following e-mail addresses in the CC: field are invalid.<br></b></font>";
		html_str += "</td></tr><tr><td><font color='#000066' face='Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular' size=2>";
		html_str += outputMsg;
		html_str += "<br><br><br><center><a href='javascript:close()'>Close</a><center></font></td></tr></table></body></html>";

		recip_win.document.write(html_str);

		recip_win.focus();

		return false;

	} else {

<% if ( current_useragent == microsoft_useragent) { %>
		if ((recip_win) && (!recip_win.closed)) 
			recip_win.close();	
<% } %>
	}

	return true;
}

function validateBCCRecipients()
{
	var invalidList;
	var outputMsg = "";
	
	// validate Bcc List
	invalidList = validateEMailList(document.form1.bcc);
	
	if(invalidList != "") {
		//alert("Invalid e-mail addresses in Bcc List: \n" + invalidList);
		outputMsg = outputMsg + "<br>" + invalidList;
	}

	if(outputMsg != ""){

		if(recip_win == null || recip_win.closed)
			recip_win = window.open("", "InvalidRecipients", "scrollbars=1,width=300,height=160,resizable=1");
		else
			recip_win.document.close();
/*
		var html_str = "<html><head><title>VeriSign PrivatePath service</title> <body bgcolor=#ffffff>";
		html_str += "<center><font color='#003399' face='Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular' size='-1'><B>" + outputMsg +"</B></font><p> ";
		html_str += "<a href='javascript:close()' class='buttonText' tabindex=1>";
		html_str += "<font face='Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular' size='2' color='#000066'>"
		html_str += "Close</font></a>";
		html_str += "</center></body></html>";
*/

		var html_str = "<html><head><title>VeriSign PrivatePath service</title></head><body>";
		html_str += "<table width='100%' height=35 border=0>";
		html_str += "<tr bgcolor='#d8d7b8'><td width='100%'> ";
		html_str += "<font color='#000066' face='Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular' size=2>";
		html_str += "<b>The following e-mail addresses in the BCC: field are invalid.<br></b></font>";
		html_str += "</td></tr><tr><td><font color='#000066' face='Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular' size=2>";
		html_str += outputMsg;
		html_str += "<br><br><br><center><a href='javascript:close()'>Close</a><center></font></td></tr></table></body></html>";

		recip_win.document.write(html_str);

		recip_win.focus();

		return false;

	} else {
<% if ( current_useragent == microsoft_useragent) { %>
		if ((recip_win) && (!recip_win.closed)) 
			recip_win.close();	
<% } %>
	}

	return true;
}

</script>
<!-- Files table Title line -->
							<tr>
							  <td colspan=6>
							  <table border="<%=table_border_TW_AccPackage;%>" cellpadding="0" valign="TOP" width="100%">
							  <tr>
								<td>
									<table border="<%=table_border_TW_AccPackage;%>" cellpadding="0" cellspacing="0">
										<tr>
											<td><img height="19" width="9" src="<%=imagepathurl;%>/buttonGreyLeft.gif"></td>
											<td bgcolor="#d8d7b8" height="19" nowrap>
												<a href="javascript:<%=reply_initialize; %>VSSelectAttachment()" class="buttonText" tabindex=1>
												<font face="Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular" size="2" color="#000066">
												Add Attachment</font></a></td>
											<td><img height="19" width="9" src="<%=imagepathurl;%>/buttonGreyRight.gif"></td>
										</tr>
									</table>
								 </td>
								</tr>
							    <tr>
								      <td colspan="3"><img src="<%=imagepathurl;%>/dot.gif"  width="1" height="5" border="0" alt=""></td>
								</tr>
									

								<tr>
								 <td>
									<!-- BBI -->
									<SCRIPT LANGUAGE="JavaScript">
										document.write( attachments_table );
									</SCRIPT>

								 </td>
								</tr>
							  </table>
							  </td>
							</tr>
<!-- 'Option for package' Title line -->
							<%
								var standard_security = tw.constant.TW_PACKAGE_SECURITY_ENCRYPTED_BY_SERVER;
								var package_security = standard_security;
								package_security |= tw.constant.TW_PACKAGE_SECURITY_PASSWORDED_BY_SERVER;
								package_security &= ~tw.constant.TW_PACKAGE_SECURITY_PASSWORD_USE_RECIPIENT_ACCOUNT;
								var account_security = standard_security;
								account_security |= tw.constant.TW_PACKAGE_SECURITY_PASSWORDED_BY_SERVER;
								account_security |= tw.constant.TW_PACKAGE_SECURITY_PASSWORD_USE_RECIPIENT_ACCOUNT;
								
								var no_security_check = "CHECKED";
								var standard_security_check = "";
								var package_security_check = "";
								var account_security_check = "";
								var security_options = createable_options.securityOptions;
								var security_option_type_index = 0; // default to no security
								if ( (account_security & security_options) == account_security) {
									security_option_type_index = 3;
									account_security_check = "CHECKED";
								} else if ( (package_security & security_options) == package_security) {
									security_option_type_index = 2;
									package_security_check = "CHECKED";
								} else if ( (standard_security & security_options) == standard_security ) {
									security_option_type_index = 1;
									standard_security_check = "CHECKED";
								}
								if ( security_option_type_index != 0 ) {
									no_security_check = "";
								}
								// SGMS BEGIN
								// Default to enrollment
								var abp_option_type_check_index = 2;
								/*
								if ( (is_logged_in && display_for_first_time) || security_option_type_index != 3 ) {
									// The first time we display the page we use the pref
									abp_option_type_check_index = (tw.session.TW_SESSION_PREF_PACKAGE_ABP_OPTIONS != "") ? tw.session.TW_SESSION_PREF_PACKAGE_ABP_OPTIONS : 0;
								} else 
								*/
								// SGMS END

								if ( !display_for_first_time ) {
									// But if we come from the same page then we use the value previously chosen
									abp_option_type_check_index = tw.request.getFormFieldValue("abp_option_type");
								}
								var abp_option_type_check_0 = (abp_option_type_check_index == 0) ? "CHECKED" : "";
								var abp_option_type_check_1 = (abp_option_type_check_index == 1) ? "CHECKED" : "";
								var abp_option_type_check_2 = (abp_option_type_check_index == 2) ? "CHECKED" : "";
								var password_escaped = escapeHTML(createable_options.password);
								var password2_escaped = escapeHTML(tw.request.getFormFieldValue("password2"));
								var abp_package_password_escaped = escapeHTML(tw.request.getFormFieldValue("abp_package_password"));
								var abp_package_password2_escaped = escapeHTML(tw.request.getFormFieldValue("abp_package_password2"));
								var enrollment_password_escaped = escapeHTML(tw.request.getFormFieldValue("enrollment_password"));
								var enrollment_password2_escaped = escapeHTML(tw.request.getFormFieldValue("enrollment_password2"));
								var hint_phrase_escaped = escapeHTML(tw.request.getFormFieldValue("hint_phrase"));
								var minimum_package_password_requirements = "";
								minimum_package_password_requirements = 
									minimum_package_password_requirements.formatPositional( 
									"The package password requires a minimum of %1$d character(s) with at least %2$d digit(s) and at least %3$d alphabetical character(s).",
									tw.server.getConfigParameter("TW_PASSWORD_MINIMUM_LENGTH"),
									tw.server.getConfigParameter("TW_PASSWORD_MINIMUM_DIGITS"),
									tw.server.getConfigParameter("TW_PASSWORD_MINIMUM_CHARACTERS") );
								
								var minEnrollPasswordReqs = "";
								var auto_enroll_with_password = true; // default is with_password
								// We don't bother doing all the work necessary to build the constraitns string
								// if we can't change the security or if we can't enroll recipients
								if ( 	is_logged_in && 
										constraints_options.isSecurityModifiable &&
										constraints_options.canEnrollRecipients
									) {
									// WATCHOUT!!! 
									// When we do a free reply the constraints come from the
									// sponsor not from the account currently logged in
									// determine the recipient manager id
									// directly by recipientManagerId
									var account = tw.session.account;
									if ( createable_options.type == tw.constant.TW_PACKAGE_TYPE_PREPAID_REPLY ) {
										// get sponsor account
										account = current_package.getSponsorAccount();
									}
									if (caps.TW_AUTO_ENROLL_VALIDATION_METHOD == tw.constant.TW_SENDER_ENROLLMENT_NO_PASSWORD ) {
										auto_enroll_with_password = false;
									}
									if ( auto_enroll_with_password ) {
										var managerId = caps.recipientManagerId;
										if ( managerId == 0 ) {
											if ( caps.TW_RECIPIENT_MANAGER_PEER == true ) {
												// recipient manager is user's manager
												managerId = tw.session.account.managerId;	
											} else if ( caps.TW_RECIPIENT_MANAGER_CHILD == true ) {
												// recipient manager is user
												managerId = tw.session.account.id;
											}
										}
										// managerId should not be 0.
										var manager = TW_Account.getAccountById( managerId );
										var managerInheritedCap = manager.inheritedCapabilities;
										var	minEnrollPasswordLength = 
											( managerInheritedCap.TW_MIN_INITIAL_PASSWORD_LENGTH != "undefined" &&
											managerInheritedCap.TW_MIN_INITIAL_PASSWORD_LENGTH != null ) ?
											managerInheritedCap.TW_MIN_INITIAL_PASSWORD_LENGTH :
											managerInheritedCap.minAccountPasswordLength;
										var	minEnrollPasswordDigits = 
											( managerInheritedCap.TW_MIN_INITIAL_PASSWORD_DIGITS != "undefined" &&
											managerInheritedCap.TW_MIN_INITIAL_PASSWORD_DIGITS != null ) ?
											managerInheritedCap.TW_MIN_INITIAL_PASSWORD_DIGITS :
											managerInheritedCap.minAccountPasswordDigits;
										var	minEnrollPasswordLetters = 
											( managerInheritedCap.TW_MIN_INITIAL_PASSWORD_LETTERS != "undefined" &&
											managerInheritedCap.TW_MIN_INITIAL_PASSWORD_LETTERS != null ) ?
											managerInheritedCap.TW_MIN_INITIAL_PASSWORD_LETTERS :
											managerInheritedCap.minAccountPasswordLetters;
										minEnrollPasswordReqs = 
											minEnrollPasswordReqs.formatPositional( 
												"The enrollment password requires a minimum of %1$d character(s) with at least %2$d digit(s) and at least %3$d alphabetical character(s).",
												minEnrollPasswordLength, 
												minEnrollPasswordDigits, 
												minEnrollPasswordLetters
											);
									}
								}
							%>
<!-- Security settings -->
							<% if (constraints_options.isSecurityModifiable) { %>
<!-- No security -->
								<tr>
									<td align="right" valign="top" nowrap>
										<a href="javascript:AboutThisField('<%=helppathurl;%>/Central/AboutThisFieldSecurity.htm')"
										onMouseOut="DisplayStatusMsg(' ');return document.MM_returnValue"
										onMouseOver="DisplayStatusMsg('About this field...');return document.MM_returnValue" class="formlabel">
										<font color="#000000" face="Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular" size="-1">
										<b>Security</b></font></a><font color="#000000" face="Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular" size="-1"><b>:</b></font>
									</td>
									<td valign="top" colspan="2">
										<input type="radio" name="security_option_type" tabindex=1 value="0" <%=no_security_check;%>>
										Low
									</td>
									<td colspan="3" nowrap valign="baseline"><font size="-1">No encryption, unsecure Web connections allowed</font></td>
			  					</tr>
<!-- Standard security -->
								<tr>
									<td>&nbsp;</td>
									<td colspan="2">
										<input type="radio" name="security_option_type" tabindex=1 value="1" <%=standard_security_check;%>>
										Standard</td>
									<td colspan="3" nowrap valign="baseline"><font size="-1">Files encrypted, secure Web connections required</font></td>
								</tr>
<!-- Package Security -->
								<tr>
									<td>&nbsp;</td>
									<td colspan="2">
										<input type="radio" name="security_option_type" tabindex=1 value="2" <%=package_security_check;%>>
										Package</td>
									<td colspan="3" nowrap valign="baseline"><font size="-1">Standard, plus a package specific password</font></td>
								</tr>
								<tr>
									<td>&nbsp;</td>
									<td colspan="2">&nbsp;</td>
									<td nowrap align="right"><font size="-1">Set package password<b><i>!</i></b></font></td>
									<td nowrap colspan="2"><input type="password" name="password" tabindex=1 value="<%=password_escaped;%>" size="16" maxlength="31"></td>
								</tr>
								<tr>
									<td>&nbsp;</td>
									<td colspan="2">&nbsp;</td>
									<td nowrap align="right"><font size="-1">Reenter package password<b><i>!</i></b></font></td>
									<td nowrap colspan="2"><input type="password" name="password2" tabindex=1 value="<%=password2_escaped;%>" size="16" maxlength="31"></td>
								</tr>
								<tr>
									<td>&nbsp;</td>
									<td colspan="2">&nbsp;</td>
									<td colspan=3><font size="-2" face="Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular"><%=minimum_package_password_requirements;%></font></td>
								</tr>
<!-- Account Security -->
								<tr>
									<td>&nbsp;</td>
									<td colspan="2">
										<input type="radio" name="security_option_type" tabindex=1 value="3" <%=account_security_check;%>>
										Account</td>
									<td colspan="3" nowrap valign="baseline"><font size="-1">Standard, plus recipient must have a validated PrivatePath account</font></td>
								</tr>
								<tr>
									<td>&nbsp;</td>
									<td colspan="2">&nbsp;</td>
									<td colspan="3" nowrap><font size="-1">If any recipients do not have accounts, then:</font></td>
								</tr>
								<% if (show_fallback_page) { %>
									<tr>
										<td>&nbsp;</td>
										<td colspan="2">&nbsp;</td>
										<td colspan="3" nowrap><font size="-1">
											<!-- turn on if we previously choose the option to not send in case of errors -->
											<input type="radio" name="abp_option_type" tabindex=1 value="3" <%=abp_option_type_check_0;%>>
											Remove recipients without accounts</font></td>
										</tr>
								<% } else { %>	
									<%
										var abp_option_type_check=abp_option_type_check_0;
										if ( constraints_options.canEnrollRecipients && abp_option_type_check_2 ) {
											abp_option_type_check=abp_option_type_check_2;
										}
									%>
<!-- ABP option: Don't send -->
									<tr>
										<td>&nbsp;</td>
										<td colspan="2">&nbsp;</td>
										<td colspan="3" nowrap><font size="-1">
											<input type="radio" name="abp_option_type" tabindex=1 value="0" <%=abp_option_type_check_0;%>>
											Do not send this package at all</font></td>
									</tr>
								<% } %>
<!-- ABP option: Use given pssword -->
								<tr>
									<td>&nbsp;</td>
									<td colspan="2">&nbsp;</td>
									<td colspan="3" nowrap><font size="-1">
										<input type="radio" name="abp_option_type" tabindex=1 value="1" <%=abp_option_type_check_1;%>>
										Use package security for all recipients</font></td>
								</tr>
								<tr>
									<td>&nbsp;</td>
									<td colspan="2">&nbsp;</td>
									<td nowrap align="right"><font size="-1">Set package password<b><i>!</i></b></font></td>
									<td nowrap colspan="2">
										<input type="password" name="abp_package_password" tabindex=1 value="<%=abp_package_password_escaped;%>" size="16" maxlength="31">
									</td>
								</tr>
								<tr>
									<td>&nbsp;</td>
									<td colspan="2">&nbsp;</td>
									<td nowrap align="right"><font size="-1">Reenter package password<b><i>!</i></b></font></td>
									<td nowrap colspan="2">
										<input type="password" name="abp_package_password2" tabindex=1 value="<%=abp_package_password2_escaped;%>" size="16" maxlength="31">
									</td>
								</tr>
								<tr>
									<td>&nbsp;</td>
									<td colspan="2">&nbsp;</td>
									<td colspan=3><font size="-2" face="Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular"><%=minimum_package_password_requirements;%></font></td>
								</tr>
<!-- ABP option: Enroll recipient without account -->
								<% if ( constraints_options.canEnrollRecipients ) { %>
									<tr>
									    <td>&nbsp;</td>
										<td colspan="2">&nbsp;</td>
										<td colspan="3" nowrap><font size="-1">
											<input type="radio" name="abp_option_type" tabindex=1 value="2" <%=abp_option_type_check_2;%>>
											Create an account for those recipients</font></td>
									</tr>
									 <% if ( auto_enroll_with_password ) { %>
									  <tr>
										<td>&nbsp;</td>
										<td colspan="2">&nbsp;</td>
										<td nowrap align="right"><font size="-1">Set initial account password<b><i>!</i></b></font></td>
										<td nowrap colspan="2">
											<input type="password" name="enrollment_password" tabindex=1 value="<%=enrollment_password_escaped;%>" size="16">
										</td>
									  </tr>
									<tr>
										<td>&nbsp;</td>
										<td colspan="2">&nbsp;</td>
										<td nowrap align="right"><font size="-1">Reenter initial account password<b><i>!</i></b></font></td>
										<td nowrap colspan="2">
											<input type="password" name="enrollment_password2" tabindex=1 value="<%=enrollment_password2_escaped;%>" size="16">
										</td>
									</tr>
									<tr>
										<td>&nbsp;</td>
										<td colspan="2">&nbsp;</td>
										<td nowrap align="right"><font size="-1">Set password hint phrase:</font></td>
										<td nowrap colspan="2"><input type="text" name="hint_phrase" tabindex=1 value="<%=hint_phrase_escaped;%>" size="32" maxlength="63"></td>
									</tr>
									  <tr>
										<td>&nbsp;</td>
										<td colspan="2">&nbsp;</td>
										<td colspan=3><font size="-2" face="Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular"><%=minEnrollPasswordReqs;%></font></td>
									  </tr>
									<% } else { /* if auto_enroll_with_password */ %>     
									  <input type=hidden name="enrollment_password" value="<%=enrollment_password_escaped;%>">
                                                                          <input type=hidden name="enrollment_password2" value="<%=enrollment_password2_escaped;%>">
                                                                          <input type=hidden name="hint_phrase" value="<%=hint_phrase_escaped;%>">
									<% } %>
								<% } else { %>
									<input type=hidden name="enrollment_password" value="<%=enrollment_password_escaped;%>">
									<input type=hidden name="enrollment_password2" value="<%=enrollment_password2_escaped;%>">
									<input type=hidden name="hint_phrase" value="<%=hint_phrase_escaped;%>">
								<% } /* if can_enroll_recipients */ %>
								<tr>
									<td valign="top" colspan=6><img border=0 height=5 src="<%=imagepathurl;%>/dot.gif" width=20></td>
								</tr>
							<% } else { /* constraints_options.isSecurityModifiable() */ %>
								<tr>
									<td>
										<input type=hidden name="security_option_type" value="<%=security_option_type_index;%>">
										<input type=hidden name="password" value="<%=password_escaped;%>">
										<input type=hidden name="password2" value="<%=password_escaped;%>">
										<input type=hidden name="abp_option_type" value="<%=abp_option_type_check_index;%>">
										<input type=hidden name="abp_package_password" value="<%=abp_package_password_escaped;%>">
										<input type=hidden name="abp_package_password2" value="<%=abp_package_password2_escaped;%>">
										<input type=hidden name="enrollment_password" value="<%=enrollment_password_escaped;%>">
										<input type=hidden name="enrollment_password2" value="<%=enrollment_password2_escaped;%>">
										<input type=hidden name="hint_phrase" value="<%=hint_phrase_escaped;%>">
									</td>
								</tr>
							<% } %>
							<% if (TW_HasMultipleLanguages()) { %>
								<%
									var locales_supported = tw.server.getConfigParameter("TW_INTERNATIONAL_INSTALLED_LOCALES" );
									// Get the default.
									var default_index = 0;
									var locales_labels = new Array();
									var locales_values = new Array();
									for (i=0 ; i< locales_supported.length ; ++i) {
										if (locales_supported[i] == createable_options.locale) {
											default_index = i;
										}
										locales_labels[i] = tw.locale.localeToLanguageNameLocalized( locales_supported[i], tw.request.locale );
										locales_values[i] = i;
									}
									var select_locale = "";
									for (i=0; i < locales_labels.length ; ++i) {
										select_locale += " <OPTION VALUE=" + locales_values[i];
										if (i == default_index) {
											select_locale += " SELECTED> ";
										} else {
											select_locale += ">";
										}
										select_locale += locales_labels[i] +  "</OPTION>";
									}
								%>
								<% if (constraints_options.isLocaleModifiable) { %>
<!-- Multiple Language Settings -->
									<tr>
										<td align="right" valign="top" nowrap>
											<a href="javascript:AboutThisField('<%=helppathurl;%>/Central/AboutThisFieldLanguage.htm')"
											onMouseOut="DisplayStatusMsg(' ');return document.MM_returnValue"
											onMouseOver="DisplayStatusMsg('About this field...');return document.MM_returnValue" class="formlabel">
											<font color="#000000" face="Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular" size="-1">
											<B>Language</b></font></a><font color="#000000" face="Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular" size="-1"><b>:</B></font>
										</td>
										<td nowrap colspan=5>
											Language for notification and delivery:
											<select name="supported_language_list" tabindex=1 size=1><%=select_locale;%></select>
										</td>
									</tr>
									<tr>
										<td colspan=6><img border=0 height=5 src="<%=imagepathurl;%>/dot.gif" width=200></td>
									</tr>
								<% } else { %>
									<tr>
										<td>
											<input type=hidden name="supported_language_list" tabindex=1 size=1 value="<%=default_index;%>">
										</td>
									</tr>
								<% } %>
							<% } %>
							<%	
								// CLG: It seems that we are using the same HTML tag to display a checked checkbox
								var checkbox_on = "CHECKED";
								var checkbox_off= "";
							%>
<!-- Notify Recipient -->
							<%
								var cb_attach_html = checkbox_off;
								if ( notification_options & tw.constant.TW_PACKAGE_NOTIFICATION_INCLUDE_RECEIVE_PAGE ) {
									cb_attach_html = checkbox_on;
								}
								var cb_include_message = checkbox_off;
								if ( notification_options & tw.constant.TW_PACKAGE_NOTIFICATION_INCLUDE_MESSAGE ) {
									cb_include_message = checkbox_on;
								}
							%>
							<% if ( constraints_options.isIncludeMessageModifiable ||
									constraints_options.isIncludeReceivePageModifiable) { %>
								<tr>
									<td align="right" valign="top" nowrap>
										<a href="javascript:AboutThisField('<%=helppathurl;%>/Central/AboutThisFieldNotifyRecipient.htm')"
										onMouseOut="DisplayStatusMsg(' ');return document.MM_returnValue"
										onMouseOver="DisplayStatusMsg('About this field...');return document.MM_returnValue" class="formlabel">
										<font color="#000000" face="Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular" size="-1">
										<b>Notify Recipient</b></font></a><font color="#000000" face="Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular" size="-1"><b>:</b></font>
									</td>
									<td colspan=5 align="top">When sending each recipient an email to notify them of their package:</td>
								</tr>
							<% } %>
<!-- Include message in notification -->
							<% if ( constraints_options.isIncludeMessageModifiable ) { %>
								<tr>
									<td>&nbsp;</td>
									<td colspan="5">
										<input type="checkbox" tabindex=1 name="include_message" value="ON" <%=cb_include_message;%>>
										Include the message (message not secure)</td>
								</tr>
							<% } else { %>
								<% if ( notification_options & tw.constant.TW_PACKAGE_NOTIFICATION_INCLUDE_MESSAGE ) { %>
									<tr><td><input type=hidden name="include_message" value="ON"></td></tr>
								<% } %>
							<% } %>
<!-- Include receive page in notification -->
							<% if ( constraints_options.isIncludeReceivePageModifiable) { %>
								<tr>
									<td>&nbsp;</td>
									<td colspan="5">
										<input type="checkbox" name="include_receive_page" tabindex=1 value="ON" <%=cb_attach_html;%>>
										Attach Secure Envelope<br>
									</td>
								</tr>
							<% } else { %>
								<% if ( notification_options & tw.constant.TW_PACKAGE_NOTIFICATION_INCLUDE_RECEIVE_PAGE ) { %>
									<tr><td><input type=hidden name="include_receive_page" value="ON"></td></tr>
								<% } %>
							<% } %>
<!-- Prepaid Replies -->
							<%
								var prepaid_reply = tw.session.currentPrepaidReply;
								var prepaid_reply_on = (prepaid_reply.howManyGranted > 0);
							%>
							<% if (constraints_options.isPrepaidReplyModifiable) { %>
								<tr>
									<td align="right" valign="top" nowrap>
										<a href="javascript:AboutThisField('<%=helppathurl;%>/Central/AboutThisFieldPrepaidReplies.htm')"
										onMouseOut="DisplayStatusMsg(' ');return document.MM_returnValue"
										onMouseOver="DisplayStatusMsg('About this field...');return document.MM_returnValue" class="formlabel">
										<font color="#000000" face="Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular" size="-1">
										<b>Prepaid Replies</b></font></a><font color="#000000" face="Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular" size="-1"><b>:</b></font>
									</td>
									<td valign="top" colspan=5>
<!-- Number of replies -->
										<% if ( constraints_options.isPrepaidReplyNumberModifiable ) { %>
											<% if (prepaid_reply_on) { %>
												<input type="checkbox" name="prepaid_reply_on" tabindex=1 value="ON" <%=checkbox_on;%>>
											<% } else { %>
												<input type="checkbox" name="prepaid_reply_on" tabindex=1 value="ON" <%=checkbox_off;%>>
											<% } %>
										<% } else { %>
											<% if (prepaid_reply_on) { %>
												<input type=hidden name="prepaid_reply_on" value="ON">
											<% } %>
										<% } %>
										Pay for each recipient to reply
										<% if (constraints_options.isPrepaidReplyNumberModifiable) { %>
											<input type="text" name="num_replies_granted" tabindex=1 size="3" maxlength="5" value="<%=prepaid_reply.howManyGranted;%>">
										<% } else { %>
											<%=prepaid_reply.howManyGranted;%>
											<input type="hidden" name="num_replies_granted" value="<%=prepaid_reply.howManyGranted;%>">
										<% } %>
										times
									</td>
								</tr>
<!-- Recipients of replies -->
								<% if (constraints_options.isPrepaidReplyToAllModifiable) { %>
									<tr>
										<td>&nbsp;</td>
										<td colspan="2"><font size="-1">
											Address prepaid replies:</font></td>
										<td class="aside" nowrap valign="baseline" colspan=4><font size="-1">
											<% if (prepaid_reply.canReplyToAll) { %>
												<input type="radio" name="reply_only_to_sender_option_type" tabindex=1 value="0">
											<% } else { %>
												<input type="radio" name="reply_only_to_sender_option_type" tabindex=1 value="0" CHECKED>
											<% } %>
											to me<br>
											<% if (prepaid_reply.canReplyToAll) { %>
												<input type="radio" name="reply_only_to_sender_option_type" tabindex=1 value="1" CHECKED>
											<% } else { %>
												<input type="radio" name="reply_only_to_sender_option_type" tabindex=1 value="1">
											<% } %>
											to all original recipients</font></td>
									</tr>
								<% } else { %>
									<% if (prepaid_reply.canReplyToAll) { %>
										<tr>
											<td><input type=hidden name="reply_only_to_sender_option_type" value="1"></td>
										</tr>
									<% } else { %>
										<tr>
											<td><input type=hidden name="reply_only_to_sender_option_type" value="0"></td>
										</tr>
									<% } %>
								<% } %>
								<tr>
									<td>&nbsp;</td>
<!-- Size of replies -->
									<td colspan="5">
										<% if (constraints_options.isPrepaidReplyMaxSizeModifiable) { %>
											<font size="-1">
											<% if (prepaid_reply_on && prepaid_reply.maxKbytePerDelivery < caps.packagePrepaidReplyMaxSize ) { %>
												<input type="checkbox" name="limit_file_size" tabindex=1 value="ON" <%=checkbox_on;%>>
												Limit file size of prepaid replies to</font>
												<input type="text" name="file_size_limit" tabindex=1 size="6" maxlength="10" value="<%=prepaid_reply.maxKbytePerDelivery;%>">
											<% } else { %>
												<input type="checkbox" name="limit_file_size" tabindex=1 value="ON" <%=checkbox_off;%>>
												Limit file size of prepaid replies to</font>
												<input type="text" name="file_size_limit" tabindex=1 size="6" maxlength="10" value="<%=prepaid_reply.maxKbytePerDelivery;%>">
											<% } %>
											<font size="-1">KBytes</font>
										<% } else { %>
											<% if (prepaid_reply.maxKbytePerDelivery < caps.packagePrepaidReplyMaxSize ) { %>
												<input type=hidden name="limit_file_size" value="ON">
											<% } %>
											<input type=hidden name="file_size_limit" value="<%=prepaid_reply.maxKbytePerDelivery;%>">
										<% } %>
									</td>
								</tr>
								<tr>
									<td valign="top" colspan=6><img border=0 height=5 src="<%=imagepathurl;%>/dot.gif" width=20></td>
								</tr>
							<% } else /* no prepaid_replies_allowed */ { %>
								<tr>
									<td>
										<% if (prepaid_reply_on) { %>
											<input type=hidden name="prepaid_reply_on" value="ON">
										<% } %>
										<input type="hidden" name="num_replies_granted" value="<%=prepaid_reply.howManyGranted;%>">
										<% if (!prepaid_reply.canReplyToAll) { %>
											<input type=hidden name="reply_only_to_sender" value="ON">
										<% } %>
										<% if (prepaid_reply.maxKbytePerDelivery < Number.MAX_UINT32) { %>
											<input type=hidden name="limit_file_size" value="ON">
										<% } %>
										<input type=hidden name="file_size_limit" value="<%=prepaid_reply.maxKbytePerDelivery;%>">
									</td>
								</tr>
							<% } %>
<!-- Notify Me Settings -->
							<%
								var cb_notif_on_failure = checkbox_on;  // system default is on
								if (confirmation_options & tw.constant.TW_PACKAGE_CONFIRMATION_ON_DELIVERY_FAILURE) {
									cb_notif_on_failure = checkbox_on;
								}
								var cb_notif_on_success = checkbox_off;  // system default is off
								if (confirmation_options & tw.constant.TW_PACKAGE_CONFIRMATION_ON_DELIVERY_SUCCESS) {
									cb_notif_on_success = checkbox_on;
								}
							%>
							<% if (	(constraints_options.isNotifyOnSuccessModifiable) ||
									(constraints_options.isNotifyOnFailureModifiable)
								) { %>
								<tr>
									<td align="left" valign="top" nowrap colspan=6>
										<font face="Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular" size="-1">
										&nbsp;&nbsp;&nbsp;<b>Notify Me</b></font></a><font color="#000000" face="Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular" size="-1"><b>:</b></font>
									</td>
								</tr>
							<% } %>
<!-- Notify on failure -->
							<% if (constraints_options.isNotifyOnFailureModifiable) { %>
								<tr>
									<td>&nbsp;</td>
									<td></td>
									<td colspan="4">
										<input type="checkbox" name="failure_acked" tabindex=1 value="ON" <%=cb_notif_on_failure;%>>
										If message cannot be delivered
									</td>
								</tr>
							<% } else { %>
								<% if (confirmation_options & tw.constant.TW_PACKAGE_CONFIRMATION_ON_DELIVERY_FAILURE) { %>
									<tr><td><input type="hidden" name="failure_acked" value="ON"></td></tr>
								<% } %>
							<% } %>
<!-- Notify on success -->
							<% if (constraints_options.isNotifyOnSuccessModifiable) { %>
								<tr>
									<td>&nbsp;</td>
									<td></td>
									<td colspan="4">
										<input type="checkbox" name="success_acked" tabindex=1 value="ON" <%=cb_notif_on_success;%>>
										When message is viewed<br>
									</td>
								</tr>
								<tr>
									<td valign="top" colspan=6><img border=0 height=5 src="<%=imagepathurl;%>/dot.gif" width=200></td>
								</tr>
							<% } else { %>
								<% if (confirmation_options & tw.constant.TW_PACKAGE_CONFIRMATION_ON_DELIVERY_SUCCESS) { %>
									<tr><td><input type=hidden name="success_acked" value="ON"></td></tr>
								<% } %>
								<tr>
									<td valign="top" colspan=6><img border=0 height=5 src="<%=imagepathurl;%>/dot.gif" width=200></td>
								</tr>
							<% } %>
<!-- Scheduled delivery settings -->
							<%	var right_now = new Date();
								var scheduled = true; //(createable_options.scheduleTime.valueOf() > right_now.valueOf());
								var user_timezone_delta = is_logged_in ? tw.session.account.userTimeZoneDelta : 0;
							%>
							<% if (constraints_options.isScheduledDeliveryAllowed) { %>
								<tr>
									<td align="right" valign="top" nowrap>
										<a href="javascript:AboutThisField('<%=helppathurl;%>/Central/AboutThisFieldScheduleDelivery.htm')"
										onMouseOut="DisplayStatusMsg(' ');return document.MM_returnValue"
										onMouseOver="DisplayStatusMsg('About this field...');return document.MM_returnValue" class="formlabel">
										<font color="#000000" face="Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular" size="-1">
										<b>Schedule Delivery</b></font></a><font color="#000000" face="Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular" size="-1"><b>:</b></font>
									</td>
									<td valign="top" colspan="5">
										<p>
										<% if (scheduled) { %>
											<input type="radio" name="schedule_option_type" tabindex=1 value="0">
											Send immediately<br>
											<input type="radio" name="schedule_option_type" tabindex=1 value="1" CHECKED>
										<% } else { %>
											<input type="radio" name="schedule_option_type" tabindex=1 value="0" CHECKED>
											Send immediately<br>
											<input type="radio" name="schedule_option_type" tabindex=1 value="1">
										<% } %>
										Send on <input type="text" maxlength=256 name="schedule_date_month" tabindex=1 size="2" value="<%=createable_options.scheduleTime.format('%m', user_timezone_delta);%>"> / <input type="text" maxlength=256 name="schedule_date_day" size="2" value="<%=createable_options.scheduleTime.format('%d', user_timezone_delta);%>"> / <input type="text" maxlength=256 name="schedule_date_year" size="4" value="<%=createable_options.scheduleTime.format('%Y', user_timezone_delta);%>">
										at
										<input type="text" maxlength=256 name="schedule_date_hour" tabindex=1 size="2" value="<%=createable_options.scheduleTime.format('%H', user_timezone_delta);%>"> : <input type="text" maxlength=256 name="schedule_date_minute" size="2" value="<%=createable_options.scheduleTime.format('%M', user_timezone_delta);%>">
										<%	var user_date = new Date();
                                            var TimeZoneDelta = tw.session.account.userTimeZoneDelta != "undefined" ? tw.session.account.userTimeZoneDelta : 0 ;
											var scheduled_time_zone_string = user_date.format("%Z", TimeZoneDelta);
											%>
										<%=scheduled_time_zone_string;%>
									</td>
								</tr>
								<tr>
									<td valign="top" colspan=6><img border=0 height=5 src="<%=imagepathurl;%>/dot.gif" width=200></td>
								</tr>
							<% } else { %>
								<tr>
									<td>
										<% if (scheduled) { %>
											<input type=hidden name="schedule_option_type" value="0">
										<% } else { %>
											<input type=hidden name="schedule_option_type" value="1">
										<% } /*Fake SGMS inputs */ %>
									</td>
								</tr>
							<% } %>
<!-- Document expiration settings -->
							<%
								var expire_unit = tw.session.TW_SESSION_PREF_PACKAGE_EXPIRATION_DELAY_UNIT;
								var expire_unit_list = "";
								
								var expire_delay	= createable_options.expireTime - createable_options.scheduleTime;
								var delay_in_unit = 0;
								// Months
								if ( expire_unit == 2 ) {
									delay_in_unit = expire_delay / 2592000;
									expire_unit_list = expire_unit_list.concat(
										"<OPTION VALUE=0>",
										"<%=Days;%>",
										"</OPTION><OPTION VALUE=1>",
										"Weeks",
										"</OPTION><OPTION VALUE=2 SELECTED>",
										"Months",
										"</OPTION>"
									);
								// Weeks
								} else if ( expire_unit == 1 ) {
									delay_in_unit = expire_delay / 604800;
									expire_unit_list = expire_unit_list.concat(
										"<OPTION VALUE=0>",
										"Days",
										"</OPTION><OPTION VALUE=1 SELECTED>",
										"Weeks",
										"</OPTION><OPTION VALUE=2>",
										"Months",
										"</OPTION>"
									);
								// The rest		
								} else {
									delay_in_unit = expire_delay / 86400;
									expire_unit_list = expire_unit_list.concat(
										"<OPTION VALUE=0 SELECTED>",
										"Days",
										"</OPTION><OPTION VALUE=1>",
										"Weeks",
										"</OPTION><OPTION VALUE=2>",
										"Months",
										"</OPTION>"
									);
								}
								// The default policy for the expiration is to have expire_on_delay
								var expiration_type_index = tw.request.getFormFieldValue("expire_option_type");
								expiration_type_index = (expiration_type_index == 1) ? 1 : 0;
								var expiration_on_date = (expiration_type_index == 1) ? "CHECKED" : "";
								var expiration_on_delay = (expiration_type_index == 1) ? "" : "CHECKED";
								var sender_never_expire = createable_options.saved ? "CHECKED" : "";
								var sender_same_as_recipient = createable_options.saved ? "" : "CHECKED";
								var send_expiration_policy_index = createable_options.saved ? 1 : 0;
							%>
							<% if (constraints_options.isExpirationModifiable) { %>
								<tr>
									<td align="right" valign="top" nowrap>
										<a href="javascript:AboutThisField('<%=helppathurl;%>/Central/AboutThisFieldPackageExpires.htm')"
										onMouseOut="DisplayStatusMsg(' ');return document.MM_returnValue"
										onMouseOver="DisplayStatusMsg('About this field...');return document.MM_returnValue" class="formlabel">
										<font color="#000000" face="Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular" size="-1">
										<b>Package Expires</b></font></a><font color="#000000" face="Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular" size="-1"><b>:</b></font>
									</td>
									<td valign="top" colspan=5>
										For each recipient<br>
										<input type="radio" name="expire_option_type" tabindex=1 value="0" <%=expiration_on_delay;%>>
										In <input type="text" maxlength=256 name="expire_delay" tabindex=1 size="2" value="<%=delay_in_unit;%>"><select name="expire_unit" size="1" tabindex=1><%=expire_unit_list;%></select> after package is sent<br>
										<input type="radio" name="expire_option_type" tabindex=1 value="1" <%=expiration_on_date;%>>
										On <input type="text" maxlength=256 name="expire_date_month" tabindex=1 size="2" value="<%=createable_options.expireTime.format('%m', user_timezone_delta);%>"> / <input type="text" maxlength=256 name="expire_date_day" size="2" value="<%=createable_options.expireTime.format('%d', user_timezone_delta);%>"> / <input type="text" maxlength=256 name="expire_date_year" size="4" value="<%=createable_options.expireTime.format('%Y', user_timezone_delta);%>"><p>
										For your personal copy:<br>
										<input type="radio" name="expire_sender_copy_option_type" tabindex=1 value="0" <%=sender_same_as_recipient;%>>
										Same as recipient expiration<br>
										<input type="radio" name="expire_sender_copy_option_type" tabindex=1 value="1" <%=sender_never_expire;%>>
										Never<br>
									</td>
								</tr>
								<tr>
									<td colspan=6><img border=0 height=5 src="<%=imagepathurl;%>/dot.gif" width=20></td>
								</tr>
							<% } else { %>
								<tr>
									<td>
										<input type=hidden name="expire_option_type" value="0">
										<input type=hidden name="expire_delay" value="<%=delay_in_unit;%>">
										<input type=hidden name="expire_unit" value="<%=expire_unit;%>">
										<input type=hidden name="expire_date" value="<%=createable_options.expireTime;%>">
										<input type=hidden name="expire_sender_copy_option_type" value="<%=send_expiration_policy_index;%>">
									</td>
								</tr>
							<% } %>
<!-- Billing Code Settings -->
							<% if (constraints_options.isBillingCodeModifiable) { %>
                                <%
                                //
                                var html_string = GetAccBillingCodeHtmlInput( "None", createable_options.billingCode );
								%>
								<tr>
									<td align="right" nowrap>
										<a href="javascript:AboutThisField('<%=helppathurl;%>/Central/AboutThisFieldBillingCode.htm')"
										onMouseOut="DisplayStatusMsg(' ');return document.MM_returnValue"
										onMouseOver="DisplayStatusMsg('About this field...');return document.MM_returnValue" class="formlabel">
										<font color="#000000" face="Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular" size="-1">
										<B>Billing Code</b></font></a><font color="#000000" face="Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular" size="-1"><b>:</B></font></td>
									<td colspan="5">
										<%=html_string;%>
									</td>
								</tr>
								<tr>
									<td colspan=6><img border=0 height=5 src="<%=imagepathurl;%>/dot.gif" width=20></td>
								</tr>
							<% } else { %>
								<tr>
									<td>
										<input type=hidden name="billing_code_list" value="0">
									</td>
								</tr>
								<tr>
								<td align="center" colspan="6">
								<img src="<%=imagepathurl;%>/sent_blank.gif" name="sent_image" width="226" height="13" border="0" alt="">
								</td>
								</tr>
								<tr><td align="center" colspan="6">&nbsp;
								<font face="Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular" size="-2" color="#000066">Estimated Credit Cost:&nbsp;
								<font color="#bc2732"><b>
								
									<input type=text name=credit_cost readonly size=3 style="font-size:8pt; color:#bc2732; border-width:0px" onFocus="this.blur()">
									<script language=javascript>
										document.form1.credit_cost.value = calculateCredits();
										document.form1.credit_cost.size = new String(document.form1.credit_cost.value).length;
									</script>
								
								</b></font></font>
								</td>
								</tr>
							<% } %>
<!-- Save as Default -->
							<%	//BEGIN_SGMS_BLOCK
								if (false  && !is_reply) { 
								//END_SGMS_BLOCK
							%>
								<%	var save_option = tw.request.getFormFieldValue("update");
									var cb_update = save_option ? checkbox_on : checkbox_off;
								%>
								<tr>
									<td align="right" nowrap>
										<a href="javascript:AboutThisField('<%=helppathurl;%>/Central/AboutThisFieldDefaultSettings.htm')"
										onMouseOut="DisplayStatusMsg(' ');return document.MM_returnValue"
										onMouseOver="DisplayStatusMsg('About this field...');return document.MM_returnValue" class="formlabel">
										<font color="#000000" face="Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular" size="-1">
										<B>Default Settings</b></font></a><font color="#000000" face="Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular" size="-1"><b>:</B></font></td>
									<td colspan="5">
										<input type="checkbox" name="update" tabindex=1 value="ON" <%=cb_update;%>>
										Save these option settings as the default for next time</td>
								</tr>
							<% } %>
<!-- Footer -->
							<tr nowrap>
								<td align="center" colspan=6>
									<table border="<%=table_border_TW_AccPackage;%>" cellpadding="0" cellspacing="0">
										<tr>
											<td><img height="19" width="9" src="<%=imagepathurl;%>/buttonGreyLeft.gif"></td>
											<td bgcolor="#d8d7b8" height="19" nowrap>
												<a href="javascript:DoClick('command_send')" class="buttonText" tabindex=1>
												<font face="Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular" size="2" color="#000066">
												Send</font></a></td>
											<td><img height="19" width="9" src="<%=imagepathurl;%>/buttonGreyRight.gif"></td>
											<td height="19">&nbsp;</td>
											<td><img height="19" width="9" src="<%=imagepathurl;%>/buttonGreyLeft.gif"></td>
											<td bgcolor="#d8d7b8" height="19" nowrap>
												<a href="<%=cancel_url;%>" class="buttonText" tabindex=1>
												<font face="Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular" size="2" color="#000066">
												Cancel</font></a></td>
											<td><img height="19" width="9" src="<%=imagepathurl;%>/buttonGreyRight.gif"></td>
										</tr>
									</table>
								</td>
							</tr>
							<tr>
								<td colspan=6><img border=0 height=15 src="<%=imagepathurl;%>/dot.gif" width=20></td>
							</tr>
						</table>
						</form>
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

</BODY>
</HTML>
