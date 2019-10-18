<!-- Copyright (c) 1993-2000 Tumbleweed Communications Corp. All Rights Reserved. -->
<%@include file="TW_GlobalHeaderMenu.tpl" %>
<!-- #BeginEditable "EditTumbleweedFileName" --> <!-- File name: TW_AccDeliveryTracking.tpl -->
<!-- #EndEditable --> <!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 3.2 Final//EN"> <%
var imagepathurl = tw.httpGateway.getImgPathUrl();
var pageTitle = "Tracking";
var table_border_TW_AccDeliveryTracking = 0; //debugging layout
var base_folder_url = tw.httpGateway.getUrl('TW_TxnAccDeliveryFolderView.tpl'); /*AccDeliveryFolderView*/
var i = 0;
var folder_url;
/* Get Current Folder Id , first check the HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_DESTINATION_FOLDER_ID  */
var current_folder_id = tw.request.getQueryString( tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_DESTINATION_FOLDER_ID, "0" );
if ( current_folder_id == "0" ) {
	/* check against tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_FOLDER_ID */;
	current_folder_id = tw.request.getQueryString(tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_FOLDER_ID, "0" );
}

// Set the page specific data.
// set the active menu
if ( current_folder_id == "0" ) {
    // set the active menu to ACC_DELIVERY_SEARCH
    TW_SetActiveMenuItem( tw.constant.TW_MENU_GROUP_SEARCH, "Find Message" );
}

// set the help url
TW_SetHelpMenuUrl(  "Help", "javascript:GoHelp('Tracking','CTracking')" );

var folder_obj;
var folder_name;

var default_sort_field;
var default_sort_order;
if ( current_folder_id !="0" ) {
	folder_obj = TW_Folder.getFolderById( current_folder_id );
	folder_name = escapeHTML( folder_obj.name );
	if ( folder_obj.folderType == tw.constant.TW_FOLDER_TYPE_OUTBOX ) {
		/* outbox type; */
		default_sort_field = tw.constant.TW_SESSION_FIELD_SEND_DATE;
	} else {
		default_sort_field = tw.constant.TW_SESSION_FIELD_SUBJECT;
	}
} else {
	folder_name = "Find Message";
	default_sort_field = tw.constant.TW_SESSION_FIELD_SUBJECT;
}

default_sort_order = "0"; //false

var field_type;
var is_ascend;
field_type = tw.request.getQueryString( tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_SORT_FIELD_TYPE, 
										default_sort_field );
is_ascend = tw.request.getQueryString( tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_SORT_FIELD_ORDER, 
										default_sort_order ); /* true; */
field_type = tw.request.getQueryString( tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_SORT_FIELD_TYPE,
										"-1" );
is_ascend = tw.request.getQueryString( tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_SORT_FIELD_ORDER,
										default_sort_order ); // false;
// compose the sorting order
var sort_data = "";

if ( field_type == -1 ) {
	// field_type is not in the url, we are trying to get from the folder first, if not use the default.
	if (current_folder_id == "0" ) {
		// find package case, or we don't know the current folder id.
		// always start with the default field.
		field_type = default_sort_field;
	} else {
		var folder_sort_string = folder_obj.sortAttributes;

		if ( (folder_sort_string == null) || (folder_sort_string.length ==0 )) {
			//  no sort field in the folder.
			field_type = default_sort_field;
		} else {
			// use the sort data from the folder_obj
			sort_data = folder_sort_string;

			// now we parse the sort attributes to determine the field_type;
			var sort_pos = folder_sort_string.indexOf( ",", 0 );

			// field_type is determined by first sort attribute, we don't care about others.
			var first_sort_attribute;
			if ( sort_pos > 0 ) {
				first_sort_attribute = folder_sort_string.substr( 0, sort_pos );
			} else {
				first_sort_attribute = folder_sort_string;
			}

			// space is the separator for sorting field and sorting order.
			sort_pos = first_sort_attribute.indexOf( " ", 0 );
			if ( sort_pos > 0 ) {
				var sort_field_string = first_sort_attribute.substr( 0, sort_pos );
				if ( sort_field_string == "TW_SCHEDULE_TIME" ) {
					field_type = tw.constant.TW_SESSION_FIELD_SEND_DATE;
				} else {
					if ( sort_field_string == "TW_SUBJECT" ) {
						field_type = tw.constant.TW_SESSION_FIELD_SUBJECT;
					} else {
						if ( (sort_field_string == "TW_IS_SAVED") || (sort_field_string == "TW_EXPIRE_TIME") ) {
							field_type = tw.constant.TW_SESSION_FIELD_EXPIRATION;
						} else {
							if ( (sort_field_string == "TW_SENDER_LASTNAME") ||
								 (sort_field_string == "TW_SENDER_FIRSTNAME") ||
								 (sort_field_string == "TW_SENDER_ADDRESS") ) {
								field_type = tw.constant.TW_SESSION_FIELD_SENDER;
							} else {
								if ( sort_field_string == "TW_USER_CONTENT_SIZE" ) {
									field_type = tw.constant.TW_SESSION_FIELD_KBYTE;
								} else {
									field_type = default_sort_field;
								}
							}
						}
					}
				}

				// now we need to recover the sorting order
				var sort_order_string = first_sort_attribute.substr( sort_pos + 1, first_sort_attribute.length - sort_pos -1 );
				if ( sort_order_string.indexOf( "asc", 0 ) < 0 ) {
					is_ascend = "0";
				} else {
					is_ascend = "1";
				}
			} else {
				field_type = default_sort_field;
			}
		}
	}
}



/* get the index of the package in the folder, HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_TABLE_START_INDEX = "tsi" */
var table_start_index = tw.request.getQueryString( tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_TABLE_START_INDEX, "0");

/* get the index of the package in the folder, HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_TRACKING_INDEX = "tri" */
var tracking_index = tw.request.getQueryString( tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_TRACKING_INDEX, "0");

var current_package_id = tw.request.getQueryString( tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_STOREITEM_ID, "0" );
var current_package = TW_Package.getPackageById(current_package_id);

%>

<HTML>
<!-- #BeginTemplate "/Templates/TW_AccCentralOnlyMenu.dwt" -->
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
<!-- #BeginEditable "EditJavaScripts" --> 
<SCRIPT language=JavaScript>
<!--

function SubmitAction( submit_obj, action_obj, folder_action )
{
	action_obj.value = folder_action;
	submit_obj.submit();
}

function TidySel(selObj) {
  var selVal = selObj.options[selObj.selectedIndex].value;
  if (!selVal) {
    selObj.selectedIndex = 0;
  }
}

function ToggleSelCheck(form, checkbox_base_name, count, exclude_check ) {
	var exclude = false;
    var checkbox_obj;
    if (arguments.length == 4)
	{
	    exclude = true;
    }

    //alert("My message");
	if ( count > 0 ) {
		var firstobject = checkbox_base_name + 0;
        var firstSelCheck ; 
        firstSelCheck = form["CheckAll"].checked;
		for( var i=0; i < count; ++i ) {
			if (!exclude )
			{
                checkbox_obj=checkbox_base_name + i;
			    form[checkbox_obj].checked = firstSelCheck;
            } else {
                if (i != exclude_check)
                {
                    checkbox_obj=checkbox_base_name + i;
			        form[checkbox_obj].checked = firstSelCheck;
                }
           }
       }
    }
}

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


function DisplayStatusMsg( msg )
{
	status = msg;
	document.MM_returnValue = true;
}
function AboutThisField(file) {
  help_win=window.open(file,"AboutThisWin","toolbar=no,width=400,height=250,resizable=yes");
}

var kid_win=null;

function TrackingError(url)
{
        DWin = window.open(url, "TrackingDetail", "resizable=1,scrollable=1,width=300,height=300");

        if (DWin.focus) DWin.focus()

}

function CloseTrackingError()
{
        if ( (kid_win) && (!kid_win.closed) ) {
                kid_win.close();
                kid_win=null;
        }
}

//-->
</SCRIPT>
<!-- #EndEditable -->
<HEAD>
<!-- #BeginEditable "EditHtmlTitle" -->
<title>VeriSign PrivatePath service</title>
<!-- #EndEditable -->
<link rel="stylesheet" href="<%=tw.httpGateway.getStylesheetPathUrl();%>/verisign.css">
</HEAD>
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
	<table border="<%=table_border_TW_AccDeliveryTracking;%>" cellpadding="0" cellspacing="0" width="100%">

	<!-- first section -->	
	  <tr>
		   <td>
			<table width="100%" border="<%=table_border_TW_AccDeliveryTracking;%>" cellspacing="1" cellpadding="2" align="center" valign="TOP">
				<tr bgcolor="#d8d7b8">
					<td width="100%" nowrap> 
					<font color="#000066" face="Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular" size="-1">
					&nbsp<b>Message Brief</b></font></td>
				</tr>
			 </table>
				</td>
	  </tr>
	  <tr>
	    <td colspan="1"><img border=0 height=10 src="<%=imagepathurl;%>/dot.gif"></td>
	  </tr>

	  <tr>
	    <td colspan=1> <!-- #BeginEditable "EditMainTableContent" -->
		<table cellpadding="0" cellspacing="0" border="<%=table_border_TW_AccDeliveryTracking;%>" width="100%">
		<!-- IME Delivery Header --> <!-- Delivery Information -->
		  <tr>
		    <td colspan="1">
			<table border="<%=table_border_TW_AccDeliveryTracking;%>" cellpadding=1 cellspacing=2 align="left" valign="TOP">

			  <tr>
			<%
				var account_obj = tw.session.account;

				var custom_switch = true;
				var imgStream = TW_AccountStream.getStreamByName( account_obj, tw.constant.TW_STREAM_IMAGE_BANNER );
				//was: var imgStream = account_obj.getStreamByName( tw.constant.TW_STREAM_IMAGE_BANNER ); sto010108
				if( imgStream == null ) {
				    custom_switch = false;
				}
			%>

			    <td align="right">
				<table border="<%=table_border_TW_AccDeliveryTracking;%>" cellpadding=1 cellspacing=2 valign="TOP">

				  <tr>
				    <td align="right"><font color="#000000" SIZE=-1 face='Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular'>
					  <B>Message:&nbsp;</B></font></td>
					<td bgcolor='#ffffff' nowrap><font size=-1>
					  <% if (current_package.subject == "") { %>
						(no subject)
					  <% } else { %>
						<%=current_package.subject;%>
					  <% } %>
					  </font>
					</td>
				  </tr>
				  <tr>
				    <td align="right"><font color = "#000000" SIZE=-1 face='Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular'>
					  <B>From:&nbsp;</B></font></td>
					<td bgcolor='#ffffff' nowrap><font size=-1>
						<%
						var sender_name = new String;
						if (!((current_package.senderFirstname ==null) ||(current_package.senderFirstname == ""))
						   || !((current_package.senderLastname == null) ||(current_package.senderLastname == "") ) ) {
							sender_name = sender_name.formatPositional( "%1$s %2$s",
								  escapeHTML(current_package.senderFirstname),
								  escapeHTML(current_package.senderLastname ) );
						} else {
							sender_name = escapeHTML(current_package.senderAddress);
						}
						%>
						<%=sender_name;%>&nbsp(<%=current_package.senderAddress;%>)
					  </font></td>
				  </tr>
				  <tr>
					<td align="right"><font color="#000000" SIZE=-1 face='Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular'>
					  <B>Sent:&nbsp;</B></font></td>
					<td bgcolor='#ffffff'><font size=-1>
					<%
					/*********************************
						define sent and expire time
					*/
					// Get the display for sent and expire time.
					var current_time = new Date();
					var date_difference, future;
					var days_display = new String();
					var time_display = new String();
					var user_timezone_delta = tw.session.account.userTimeZoneDelta;
					
					var sent_time = new Date( current_package.scheduleTime *1000); // date object takes milliseconds
					var end_time = sent_time;

					// this portion might be duplicated at several places. We need functions !!!!
					future = end_time.getTime() >= current_time.getTime();
					if ( future ) {
						date_difference = ((end_time.getTime() - current_time.getTime())/(1000*60*60) + current_time.getHours())/24;
					} else {
						date_difference = ((current_time.getTime() - end_time.getTime() )/(1000*60*60) + end_time.getHours())/24;
					}

					// we need switch statement here
					if ( date_difference == 0 ) {
						days_display= "Today";
					} else {
						if ( date_difference == 1 ) {
							if ( future ) {
								days_display = "Tomorrow";
							} else {
								days_display = "Yesterday";
							}
						} else {
							if ( future ) {
								days_display=days_display.formatPositional( "%1$d days later", date_difference );
							} else {
								days_display=days_display.formatPositional( "%1$d days ago", date_difference );
							}
						}
					}
					time_display =  end_time.format( "%m/%d/%Y %X, %Z", user_timezone_delta );
					
					var sent_time_display = new String;
					%>
					<%=sent_time_display.formatPositional( "%1$s, %2$s", days_display, time_display );%>
				     </font></td>
				  </tr>
				  <tr>
				    <td align="right"><font color="#000000" SIZE=-1 face='Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular'>
					  <B>Expires:&nbsp;</B></font></td>
					<td bgcolor='#ffffff'><font size=-1>


					<%

					var expire_time_display = new String;
					var expire_time = new Date( current_package.expireTime *1000 );
					if ( current_package.saved ) {
						expire_time_display = "Never (Extended)";
					} else {
						var is_package_expired = !current_package.saved && (
												(current_package.state == tw.constant.PACKAGE_STATE_EXPIRED ) ||
												(current_package.state == tw.constant.PACKAGE_STATE_EXPIRED_AND_STREAMS_DELETED ) ||
												!( current_time.getTime() < expire_time.getTime() ));
						if ( is_package_expired ) {
							expire_time_display = "Expired";
						} else {
							end_time = expire_time;

							// this portion might be duplicated at several places. We need functions !!!!
							future = end_time.getTime() >= current_time.getTime();
							if ( future ) {
								date_difference = ((end_time.getTime() - current_time.getTime())/(1000*60*60) + current_time.getHours())/24;
							} else {
								date_difference = ((current_time.getTime() - end_time.getTime() )/(1000*60*60) + end_time.getHours())/24;
							}

							// we need switch statement here
							if ( date_difference == 0 ) {
								days_display= "Today";
							} else {
								if ( date_difference == 1 ) {
									if ( future ) {
										days_display = "Tomorrow";
									} else {
										days_display = "Yesterday";
									}
								} else {
									if ( future ) {
										days_display=days_display.formatPositional( "%1$d days later", date_difference );
									} else {
										days_display=days_display.formatPositional( "%1$d days ago", date_difference );
									}
								}
							}
							time_display =  end_time.format( "%m/%d/%Y %X, %Z", user_timezone_delta );
							expire_time_display = expire_time_display.formatPositional( "%1$s, %2$s", days_display, time_display );
						}
					}  
					%>

					  <%=expire_time_display;%></font></td>
				  </tr>
				  <tr>
				    <td align="right"><font color="#000000" SIZE=-1 face='Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular'>
					  <B>Tracking:&nbsp;</B></font></td>
					<% if ((current_package.notifyBadDomainCount == 0 ) && (current_package.notifyBadAccountCount == 0 ) &&
						(current_package.notifyGiveUpCount == 0 ) && (current_package.allMediumFailCount == 0)) { %>
					<td bgcolor='#ffffff'><font size=-1>
					<% } else { %>
					<td bgcolor='#ffcccc'><font size=-1>
					<% }  %>
					<%
						/**************************
							define tracking status
						*/
					var send_count = Math.min( current_package.allMediumRecipientCount, 2 );
					var notified_count = Math.min( current_package.notifyDoneCount, 2 );
					var delivered_count = Math.min( current_package.receiveCount, 2 );

					if ( (notified_count ==2) && ( current_package.allMediumRecipientCount > current_package.notifyDoneCount ) ) {
						notified_count = 1;
					} /* endif */

					if ( (delivered_count ==2) && (notified_count ==2)
					   && ( current_package.allMediumRecipientCount > current_package.receiveCount) ) {
						delivered_count = 1;
					} /* endif */	
					%>
					<% if ( send_count == 1 ) {
						if ( notified_count == 0 ) {	/* 1, 0, 0 */ %>
							Not Notified
						<% } else { 
							if ( delivered_count == 0 ) { /* 1, 1, 0 */ %>
								Notified
							<% } else {	/* 1, 1, 1 */ %>
								Received
							<% }
						 } 
					   } else { 
						if ( send_count == 2 ) { 
							if ( notified_count == 2 ) { 
								if ( delivered_count == 2 ) { /* 2, 2, 2 */ %>
									All Received
								<% } else {
									if ( delivered_count == 1 ) { /* 2, 2, 1 */ %>
										Some Received
									<% } else { /* 2, 2, 0 */ %>
										All Notified
									<% } 
								 } 
							 } else { 
								 if ( notified_count == 1 ) { /* 2, 1,0 or 2, 1, 1 */ %>
									Some Notified
								<% } else { /* 2, 0 , 0 */ %>
									None Notified
								<% } 
							}
						}
					}
					%>
					<% if (current_package.state == tw.constant.PACKAGE_STATE_CANCELLED) { %>
						<FONT COLOR=#CC0033 SIZE=-1> (cancelled)</FONT>
					<% } %>

				  	</font></td>
				  </tr>
				</table>
			    </td>
			  </tr>
			</table>
		    </td>
		  </tr>
		  <%
			var package_form_url = tw.httpGateway.getUrl('TW_TxnAccDeliveryTrackingAction.tpl'); /*AccDeliveryTrackingAction*/
			package_form_url = package_form_url.concat("&",tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_FOLDER_ID, "=", current_folder_id );
			package_form_url = package_form_url.concat("&",tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_STOREITEM_ID, "=", current_package_id );
		  %>
		  <tr>
		    <td colspan="1"><img border=0 height=10 src="<%=imagepathurl;%>/dot.gif"></td>
		  </tr>
		  <tr> 
		    <td colspan="1" align="left"><font color="#000000" SIZE=-1 face='Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular'> 
			  <B>&nbsp;<%=current_package.allMediumRecipientCount;%> Recipient(s)</B></font> &nbsp;<font size=-1> 


			<%
			/***********************************
				Summarize Delivery Status
			*/
			var enable_to_notify_count = new Number (current_package.notifyBadDomainCount + current_package.notifyBadAccountCount);

			var failure_count = Math.min( enable_to_notify_count, 1 );
			var success_count = Math.min( current_package.notifyDoneCount, 1 );
			var view_count = Math.min( current_package.receiveCount, 1 );

			var notification_status = new String;

			if ( failure_count == 0 ) {
				if ( success_count == 0 ) { // 0, 0, 1
					notification_status =  notification_status.formatPositional("package viewed by: %1$d",	
										current_package.receiveCount);	
				} else {
					if ( view_count == 0) { // 0, 1, 0
						notification_status = notification_status.formatPositional("successfully notified: %1d",
										current_package.notifyDoneCount);
					} else {	// 0, 1, 1
						notification_status =  notification_status.formatPositional("successfully notified: %1$d, package viewed by: %2$d",
										current_package.notifyDoneCount,
										current_package.receiveCount);							
					}
				}
			} else {
				if ( success_count == 0 ) { 
					if ( view_count == 0 ) { //  1, 0, 0
						notification_status =  notification_status.formatPositional("unable to notify: %1$d",
									enable_to_notify_count);	
					} else { // 1, 0, 1
						notification_status = notification_status.formatPositional("unable to notify: %1$d, package viewed by: %2$d",
									enable_to_notify_count,
									current_package.receiveCount);
					}
				} else {
					if ( view_count == 0 ) { // 1, 1, 0
						notification_status = notification_status.formatPositional("unable to notify: %1$d, successfully notified: %2$d",
									enable_to_notify_count,
									current_package.notifyDoneCount);
					} else { // 1, 1, 1
						notification_status  = notification_status.formatPositional("unable to notify: %1$d, successfully notified: %2$d, package viewed by: %3$d",	
									enable_to_notify_count,
									current_package.notifyDoneCount,
									current_package.receiveCount);	

					}
				}
			}
			%>
			<%=notification_status;%>

			  </font></td>
		  </tr>
		</table>
	    </td>
		  <!-- End of first section-->
	  </tr>
		  
		  
		  <!-- second section-->
	  <tr>
	    <td>
		<table border="<%=table_border_TW_AccDeliveryTracking;%>" cellpadding="0" cellspacing="0" width="100%">

		  <tr>
		    <td align=right>
			<table width="100%" border="<%=table_border_TW_AccDeliveryTracking;%>" cellspacing="1" cellpadding="2" align="center" valign="TOP">
			  <tr bgcolor="#d8d7b8">
				<td width="100%" nowrap> 
				<font color="#000066" face="Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular" size="-1">
				&nbsp<b>Tracking Details</b></font></td>
			  </tr>
			</table>
		    </td>
		  </tr>
            
		</table>
	    </td>
	  </tr>
			  
	  <tr>
	    <td align=center valign=top colspan="1"> <img border=0 height=14 src="<%=imagepathurl;%>/dot.gif" width=201></td>
	  </tr>
	  
	  <!--Third section -->
	  <tr>
	    <td>
		<table border="<%=table_border_TW_AccDeliveryTracking;%>" cellpadding="0" cellspacing="0" valign="TOP" width="100%">
		  <tr>
		    <TD>
			<!-- Tracking Details table header -->
			<TABLE border="<%=table_border_TW_AccDeliveryTracking;%>" cellpadding="0" cellspacing="0" align="right">
			  <TR>
					<%

					/***********************************************************************
						compose the query to search for a list of recipients from the package
					*/

					var session_tracking_index = new Number(tracking_index);

					var query_range = tracking_index;
					var row_per_page =  tw.session.TW_SESSION_PREF_TRACKING_ROW_COUNT;

					query_range = query_range.concat("INT ,",
									session_tracking_index + row_per_page * 2 + 1,
									"INT" );

					var recipient_query = " ; ; ";
					recipient_query = recipient_query.concat(query_range);
					var recipients = current_package.queryRecipients(recipient_query);

					var row_per_page_on_next_page = 0;
					if (recipients.length > row_per_page) {
						row_per_page_on_next_page = Math.min(row_per_page, (recipients.length - row_per_page));
					}


					/****************************************
						Build the next/prev button
					*/

					var next_prev_url = tw.httpGateway.getUrl('TW_TxnAccDeliveryTracking.tpl'); /*AccDeliveryTracking*/	
					next_prev_url = next_prev_url.concat("&",tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_FOLDER_ID, "=", current_folder_id );
					next_prev_url = next_prev_url.concat("&",tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_STOREITEM_ID, "=", current_package_id );
					next_prev_url = next_prev_url.concat("&", tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_TABLE_START_INDEX, "=", table_start_index );

					var next_url = next_prev_url;
					var prev_url = next_prev_url;

					session_tracking_index += row_per_page;
					next_url = next_url.concat("&", tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_TRACKING_INDEX, "=", session_tracking_index);

					var next_button = new String;
					next_button = next_button.formatPositional("Next",
										 row_per_page_on_next_page
										 );				

					var prev_tracking_index = 0;
					var row_per_page_on_prev_page = new Number(0);

					if ((tracking_index - row_per_page) > 0) {
						prev_tracking_index = (tracking_index - row_per_page);
						row_per_page_on_prev_page = row_per_page;
					} else {
						row_per_page_on_prev_page = tracking_index;
					}

					var prev_url = next_prev_url;
					prev_url = prev_url.concat("&", tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_TRACKING_INDEX, "=", (prev_tracking_index));

					var prev_button = new String;
					var number_rows = new Number(row_per_page_on_prev_page);
					prev_button = prev_button.formatPositional("Previous",
										 number_rows
										 );	
					%>

					<% if (row_per_page_on_prev_page > 0) { %>
					    <td><font size="-1"> <A HREF="<%=prev_url;%>"><%=prev_button;%></A>&nbsp;|&nbsp;</font></td>
					<% }  %>
			    <td><font size="-1"><%=current_package.allMediumRecipientCount;%> Recipient(s)&nbsp;</td>

					<%
 
						var range_start = new Number( tracking_index);
						if (recipients.length > 0 ) {
						     ++range_start;
						}
						var range_end = new Number(tracking_index);;
						if (recipients.length > row_per_page) {
						     range_end += row_per_page;
						} else {
						     range_end += recipients.length;
						}

						var recipient_range = new String;
						recipient_range = recipient_range.formatPositional("%1$d-%2$d",
													range_start,
													range_end);
					%>
			    <td align="right"><font SIZE=-1> <%=recipient_range;%></font></td>

				<% if (row_per_page_on_next_page > 0) { %>
					    <td><font size="-1">&nbsp;|&nbsp;<A HREF="<%=next_url;%>"><%=next_button;%></A></font></td>
				<% }  %>

				<%
					
					//Check how many file (aka TW_STREAM_CONTENT) are in the package. At the same time, create the header of the table.
					var package_streams = current_package.streams;	

					var i;
					var number_files = 0;
					var tracking_table_header = "";
					if (current_package.securityOptions &
						(tw.constant.TW_PACKAGE_SECURITY_SIGNED_CLEARTEXT |
						 tw.constant.TW_PACKAGE_SECURITY_SIGNED_CYPHER |
						 tw.constant.TW_PACKAGE_SECURITY_ENCRYPTED_BY_CLIENT) == 0 )
					for (i=0; i < package_streams.length; ++i) { 
						if (package_streams[i].usage == tw.constant.TW_STREAM_CONTENT) { 
							// build the file type image
							var filename = package_streams[i].filename;
							// make file name url compiliant.	
							var escaped_filename = "";
							var cur_char;
							var j;
							for ( j=0; j < filename.length; ++j ) {
								cur_char = filename.charAt(j);
								if( (cur_char == " ") || (cur_char == "/" ) || (cur_char == "&") ||(cur_char == "#") ) {
									escaped_filename = escaped_filename.concat( "_" );
								} else {
									escaped_filename = escaped_filename.concat( cur_char );
								}
							}
							var mime_type = package_streams[i].mimeType;

							// find the file extension;
							var index = filename.lastIndexOf( "." );
							var extension;
							if ( index != -1 ) {
								extension = filename.substr( 0, index );
								extension = extension.toLowerCase();
							}
							var map_result;
							if ( (mime_type.length==0 ) && (extension.length != 0) ) {
								map_result = tw.request.mimesMapper.extensionToMime( extension );
								mime_type = map_result[0];
							}	

							if ( mime_type.length == 0 ) {
								mime_type = "application/octet-stream";
							}
					
							map_result = tw.request.mimesMapper.extensionToName ( mime_type, extension );
							var mime_name = map_result[0];
							if ( mime_name.length == 0 ) {
								mime_name = mime_type;
							}
					
							var gif_name = "";
							map_result = tw.request.mimesMapper.extensionToGifName( mime_type, extension );
							gif_name = map_result[0];
							if (gif_name.length == 0) {
								gif_name = "Type_Unknown.gif";
							}
						
							var image_path = "";
							if (gif_name.length != 0) {
								image_path = image_path.formatPositional ( "<img src=%1$s/%2$s width=14 height=16 border=0>&nbsp;",
														tw.server.getConfigParameter( "TW_IMAGE_ROOT_URL" ),
														gif_name );
							}
							tracking_table_header = tracking_table_header.concat("<TH BGCOLOR='#d8d7b8' nowrap>",
														image_path,
													     escapeHTML(package_streams[i].filename),
													     "</TH>");
							 ++number_files; 
						} 
					}
				%>
					<% if (number_files > 0) { %>

					    <TD nowrap colspan="<%=number_files;%>">
						<font color="#003399" SIZE=-1 face='Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular'><B>File status</B></font>
					    </TD>
					<% }  %>
			  </TR>
			</TABLE>
		    </TD>
		  </tr>
		  <TR>
		    <TD>
			<!-- Tracking Details table content -->
			<TABLE border="<%=table_border_TW_AccDeliveryTracking;%>" bgcolor="#cccccc" cellpadding="3" cellspacing="1" valign="TOP" width="100%">

			  <TR BGCOLOR='#d8d7b8'>
			    <TH BGCOLOR='#d8d7b8' nowrap> &nbsp </TH>
			    <TH BGCOLOR='#d8d7b8' nowrap>Recipients</TH>
			    <TH BGCOLOR='#d8d7b8' nowrap>Notification status</TH>
			    <TH BGCOLOR='#d8d7b8' nowrap>Message status	</TH>

			    <%=tracking_table_header;%>
			  </TR>

					<%
					  var recipient_counter = 0;
					  for (i = 0; i < recipients.length && (recipient_counter < row_per_page); ++i, ++recipient_counter) {
						%>
					  <TR>
						<%
						var state_time = new Date( recipients[i].stateTime *1000);
						var state_time_string = state_time.format( "%m/%d/%Y at %X", user_timezone_delta );


						var delivery_tracking_error_url = tw.httpGateway.getUrl('TW_TxnAccDeliveryTrackingError.tpl'); /*AccDeliveryTrackingError*/
						var encoded_recipient_email;
						var recipient_email = recipients[i].singleRecipient.address;
						encoded_recipient_email = recipient_email.encodeBase64();
						delivery_tracking_error_url=delivery_tracking_error_url.concat( "&",tw.constant.HTTP_GATEWAY_URL_VARIABLE_PICKUP_SESSION_RECIPIENT_EMAIL, "=", encoded_recipient_email );	
						delivery_tracking_error_url=delivery_tracking_error_url.concat( "&",tw.constant.HTTP_GATEWAY_URL_VARIABLE_SESSION_RECIPIENT_STATUS, "=", recipients[i].state );

						/***********************************/
					  	// nature of the delivery To, CC, BCC
						var delivery;
						if (recipients[i].category == tw.constant.RECIPIENT_CATEGORY_TO) {
							delivery = "To";
						 } else if (recipients[i].category == tw.constant.RECIPIENT_CATEGORY_CC) {
							delivery = "Cc";
						 } else if (recipients[i].category == tw.constant.RECIPIENT_CATEGORY_BCC) {
							delivery = "Bcc";
						 } else {
							delivery = "";
						 }
						%>
					    <TD bgcolor="#ffffff" ALIGN="center"><FONT SIZE=-1><%=delivery;%></TD>
						<%

						/******************/
						// recipient address
						if (recipients[i].description == tw.constant.SINGLE_RECIPIENT ) {
						%>
					    <TD bgcolor="#ffffff" ALIGN=LEFT><FONT SIZE=-1><%=escapeHTML(recipients[i].singleRecipient.address);%></TD>
						<%
						}

						/*********************/
						// Notification status
						
						var notification_status_output = "";
						if ( ( ( ( recipients[i].state & tw.constant.TW_RECIPIENT_STATE_GROUP_MASK) == tw.constant.TW_RECIPIENT_STATE_GROUP_START) ||
						       ( recipients[i].state == tw.constant.TW_RECIPIENT_STATE_STANDARD_PROCESSING_NOTIFICATION) )  &&
						     ( current_package.state != tw.constant.PACKAGE_STATE_CANCELLED ) ) {
								var time_schedule_string = sent_time.format( "%m/%d/%Y at %X", user_timezone_delta );
								var schedule_time_html = new String;
								schedule_time_html=schedule_time_html.formatPositional("<BR><FONT SIZE=-2 COLOR=#999999> %1$s </FONT>", time_schedule_string);
								notification_status_output = notification_status_output.concat("Scheduled",
																schedule_time_html);
						} else if ( ( recipients[i].state & tw.constant.TW_RECIPIENT_STATE_GROUP_MASK) == tw.constant.TW_RECIPIENT_STATE_GROUP_RETRY ){
							notification_status_output = "Retrying";
						} else if ( ( ( ( recipients[i].state & tw.constant.TW_RECIPIENT_STATE_GROUP_MASK) == tw.constant.TW_RECIPIENT_STATE_GROUP_FAILURE ) &&
							      ( recipients[i].state != tw.constant.TW_RECIPIENT_STATE_STANDARD_OR_GENERIC_SECURITY_FAILURE ) ) ||
							    ( ( ( ( recipients[i].state & tw.constant.TW_RECIPIENT_STATE_GROUP_MASK) == tw.constant.TW_RECIPIENT_STATE_GROUP_SUCCESS ) ||
							        ( ( recipients[i].state & tw.constant.TW_RECIPIENT_STATE_GROUP_MASK) == tw.constant.TW_RECIPIENT_STATE_GROUP_PROGRESS ) ) &&
							      ( recipients[i].singleRecipient.notifyTime == 0 ) ) ) {
						

							var url_error = new String;
							url_error = url_error.formatPositional("<a href=\"javascript:TrackingError('%1$s')\" onMouseOut=\"DisplayStatusMsg(' ');return document.MM_returnValue\" onMouseOver=\"DisplayStatusMsg('%2$s');return document.MM_returnValue\" class=\"formlabel\"> <u>%3$s</u> <a>",
									delivery_tracking_error_url,
									"About this error...",	
									"<FONT COLOR=#CC0033>Unable to send</FONT>");

							if ( ( recipients[i].state & tw.constant.TW_RECIPIENT_STATE_GROUP_MASK) == tw.constant.TW_RECIPIENT_STATE_GROUP_FAILURE ) {

								var state_time_html = new String;
								state_time_html=state_time_html.formatPositional("<BR><FONT SIZE=-2 COLOR=#FF6666> %1$s </FONT>", state_time_string);
								notification_status_output = notification_status_output.concat(url_error,
																state_time_html);
							} else {
								notification_status_output = url_error;
							}
						} else if ( ( ( recipients[i].state & tw.constant.TW_RECIPIENT_STATE_GROUP_MASK) == tw.constant.TW_RECIPIENT_STATE_GROUP_PROGRESS ) ||
							    ( ( recipients[i].state & tw.constant.TW_RECIPIENT_STATE_GROUP_MASK) == tw.constant.TW_RECIPIENT_STATE_GROUP_SUCCESS ) || 
							    ( recipients[i].state == tw.constant.TW_RECIPIENT_STATE_STANDARD_OR_GENERIC_SECURITY_FAILURE ) ) {
								var sent_notification_time = new Date( recipients[i].singleRecipient.notifyTime *1000);
								var time_sent_string = sent_notification_time.format( "%m/%d/%Y at %X", user_timezone_delta );
								var sent_time_html = new String;
								sent_time_html=sent_time_html.formatPositional("<BR><FONT SIZE=-2 COLOR=#999999> %1$s </FONT>", time_sent_string);
								if ((recipients[i].deliveryMethod != null) && (recipients[i].deliveryMethod == tw.constant.TW_DELIVERY_METHOD_NULL) ) {
									notification_status_output = "Sent";
								} else {
									notification_status_output = notification_status_output.concat("Sent",
																	sent_time_html);
								}
						} else if ( recipients[i].state == tw.constant.TW_RECIPIENT_STATE_STANDARD_OR_GENERIC_SKIPPED) {
							notification_status_output = "Skipped";
						} else {
							notification_status_output = "&nbsp";
						} 
						%>
					    <TD bgcolor="#ffffff" ALIGN=LEFT nowrap><FONT SIZE=-1><%=notification_status_output;%></TD>
						<%

						/***************/
						// Message status
						var package_status_output = "";
						if ( recipients[i].state == tw.constant.TW_RECIPIENT_STATE_STANDARD_OR_GENERIC_SKIPPED) {
							var skipped_time_html = new String;
							skipped_time_html=sent_time_html.formatPositional("<BR><FONT SIZE=-2 COLOR=#999999> %1$s </FONT>", state_time_string);
							package_status_output = package_status_output.concat("Skipped",
													     skipped_time_html);
						 } else if ( ( recipients[i].state & tw.constant.TW_RECIPIENT_STATE_GROUP_MASK) == tw.constant.TW_RECIPIENT_STATE_GROUP_SUCCESS ) {
							var receive_time = new Date( recipients[i].singleRecipient.receiveTime *1000);
							var receive_time_string = receive_time.format( "%m/%d/%Y at %X", user_timezone_delta );
							var receive_time_html = new String;
							receive_time_html=receive_time_html.formatPositional("<BR><FONT SIZE=-2 COLOR=#999999> %1$s </FONT>", receive_time_string);
							package_status_output = package_status_output.concat("Retrieved",
														receive_time_html);
						} else if ( ( recipients[i].state == tw.constant.TW_RECIPIENT_STATE_STANDARD_PICKUP_LOGIN_FAIL) ||
							    ( recipients[i].state == tw.constant.TW_RECIPIENT_STATE_STANDARD_PUBLIC_KEY_DELIVERY_STRONG_CRYPTO_ERROR) ||
							    ( recipients[i].state == tw.constant.TW_RECIPIENT_STATE_STANDARD_PUBLIC_KEY_DELIVERY_PRIVATE_KEY_ERROR) ||
							    ( recipients[i].state == tw.constant.TW_RECIPIENT_STATE_STANDARD_PUBLIC_KEY_DELIVERY_SECURITY_UNSUPPORTED_MIME_ERROR) ||
							    ( recipients[i].state == tw.constant.TW_RECIPIENT_STATE_STANDARD_PUBLIC_KEY_DELIVERY_PROCESSING_ERROR) ||
							    ( recipients[i].state == tw.constant.TW_RECIPIENT_STATE_STANDARD_PUBLIC_KEY_DELIVERY_UNKNOWN_ERROR) ||
							    ( recipients[i].state == tw.constant.TW_RECIPIENT_STATE_STANDARD_OR_GENERIC_SECURITY_FAILURE) ) {
							var url_error = new String;
							url_error = url_error.formatPositional("<a href=\"javascript:TrackingError('%1$s')\" onMouseOut=\"DisplayStatusMsg(' ');return document.MM_returnValue\" onMouseOver=\"DisplayStatusMsg('%2$s');return document.MM_returnValue\" class=\"formlabel\"> <u>%3$s</u> <a>",
									delivery_tracking_error_url,
									"About this error...",	
									"<FONT COLOR=#CC0033>Try to view</FONT>");

							var state_time_html = new String;
							state_time_html=state_time_html.formatPositional("<BR><FONT SIZE=-2 COLOR=#FF6666> %1$s </FONT>", state_time_string);
							package_status_output = package_status_output.concat(url_error,
													     state_time_html);
						} else { 
							package_status_output = "&nbsp;";
						}
						%>
					    <TD bgcolor="#ffffff" ALIGN=LEFT><FONT SIZE=-1><%=package_status_output;%></TD>
						<%
						var stream_index;
						if (current_package.securityOptions &
							(tw.constant.TW_PACKAGE_SECURITY_SIGNED_CLEARTEXT |
							 tw.constant.TW_PACKAGE_SECURITY_SIGNED_CYPHER |
							 tw.constant.TW_PACKAGE_SECURITY_ENCRYPTED_BY_CLIENT) == 0 )
						for ( stream_index = 0; stream_index < package_streams.length ; ++stream_index ) {
							if (package_streams[stream_index].usage == tw.constant.TW_STREAM_CONTENT) {
								if ( ( recipients[i].description == tw.constant.SINGLE_RECIPIENT) &&
								     (recipients[i].singleRecipient.streamStateArray.length > stream_index) ) {
									var stream_state;
									if ( recipients[i].singleRecipient.streamStateArray[stream_index] == tw.constant.TW_RECIPIENT_STREAM_NONE ) {
										stream_state = "&nbsp;";
									} else if ( recipients[i].singleRecipient.streamStateArray[stream_index] == tw.constant.TW_RECIPIENT_STREAM_ATTEMPTED_DOWNLOAD ) {
										stream_state = " Download failed";
									} else if ( recipients[i].singleRecipient.streamStateArray[stream_index] == tw.constant.TW_RECIPIENT_STREAM_SERVER_SUCCEEDED ) {
										stream_state = "Delivered";
									} else if ( recipients[i].singleRecipient.streamStateArray[stream_index] == tw.constant.TW_RECIPIENT_STREAM_CLIENT_CONFIRMED ) {
										stream_state = "Confirmed";
									} else {
										stream_state = "Unknown";
									}
						%>
								    <TD bgcolor="#ffffff" ALIGN=LEFT><FONT SIZE=-1><%=stream_state;%></TD>
						<%		}
							}
						}
						%>
					  </TR>
						
					<% } %>
			</TABLE>
		    </TD>
		  </TR>
		  <TR>
		    <TD>
			<!-- Tracking Details table footer -->
			<TABLE border="<%=table_border_TW_AccDeliveryTracking;%>" cellpadding="0" cellspacing="0" align="right"%>
			  <tr>
				<td  colspan="3" nowrap align="right">
				  <table border="<%=table_border_TW_AccDeliveryTracking;%>" cellpadding="0" cellspacing="0">
				  <tr>
					<% if (row_per_page_on_prev_page > 0) { %>
					  <td><font size="-1"> <A HREF="<%=prev_url;%>"><%=prev_button;%></A>&nbsp;|&nbsp;</font></td>
					<% }  %>

				    <td><font size="-1"><%=current_package.allMediumRecipientCount;%> Recipient(s)&nbsp;
				    <td><font SIZE=-1> <%=recipient_range;%></font></td>

				<% if (row_per_page_on_next_page > 0) { %>
					    <td><font size="-1">&nbsp;|&nbsp;<A HREF="<%=next_url;%>"><%=next_button;%></A></font></td>
				<% }  %>

				  </tr>
				  </table>
				</td>
			  </tr>
			  <!--tr>
			    <td>
				  <form name="tracking_form" action="<%=package_form_url;%>" method="POST">
				  <input type="hidden" name="submit_action" value="command_cancel">
				  <table border="<%=table_border_TW_AccDeliveryTracking;%>" cellpadding="0" cellspacing="0">
				    <tr>
					  
				<td>
				<img height="19" src="<%=imagepathurl;%>/buttonPurpleLeft.gif"></td>
					  <td bgcolor="#d8d7b8" height="19" nowrap><a href="javascript:SubmitAction(document.tracking_form,document.tracking_form.submit_action, '<%=tw.constant.HTTP_GATEWAY_ACCOUNT_SESSION_COMMAND_CANCEL;%>')" class="buttonText">
					  <font face="Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular" size="2" color="#000066">Cancel delivery to All Recipients</font></a></td>
					  <td><img height="19"  src="<%=imagepathurl;%>/buttonPurpleRight.gif"></td>
					</tr>
					>

				  </table>
				  </form>
				</td>
			  </tr-->
		</table>
	    </td>
	    <td width=20></td>
	  </tr>
	</table>

</BODY>
<!-- #EndTemplate -->
</HTML>
