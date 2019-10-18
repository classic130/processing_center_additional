<!-- Copyright (c) 1993-2000 Tumbleweed Communications Corp. All Rights Reserved. --> 
<%@include file="TW_GlobalHeaderMenu.tpl" %>
<%@include file="TW_HelperPickup.tpl" %>
<%@include file="TW_HelperHttpHosts.tpl" %>
<%@include file="SGMS_OnSiteHostConfig.tpl" %>
<!-- #BeginEditable "EditTumbleweedFileName" --> <!-- File name: SGMS_PickupPRC.tpl --> 
<!-- #EndEditable -->
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 3.2 Final//EN">
<%
    //TODO: KIRIL: localize
	function ResolveCryptStatus( crypt_status, msg_type ){
		if( msg_type == 2 || msg_type == 0) {
			// Not signed
			return "<img src='" + imagepathurl + "/encrypt.gif'>&nbsp;Encrypted&nbsp;&nbsp;&nbsp;&nbsp;Not Digitally Signed";
			}
		else if ((crypt_status & 1) == 1 )
			// Valid
			return "<img src='" + imagepathurl + "/encrypt.gif'>&nbsp;Encrypted&nbsp;&nbsp;&nbsp;&nbsp;<img src='" + imagepathurl + "/sign.gif'> Digitally Signed - Valid";
		else {
			// Invalid
			return "<img src='" + imagepathurl + "/encrypt.gif'>&nbsp;Encrypted&nbsp;&nbsp;&nbsp;&nbsp;<img src='" + imagepathurl + "/sign.gif'> - Digitally Signed - Invalid";
		}
				
	}
%>  
<%

//SGMS Testing
//if (tw.session.sii != tw.request.getQueryString("sii", 0)) {
//	tw.session.sii = tw.request.getQueryString("sii", "");


	//Remember what package has been decrypted last
	//TO DO:This has to be invalidated on compose 
	tw.session.SGMSPackageId = tw.session.currentDelivery.packageId.toString();

	var decode_obj = new SGMSDecodePackage(tw.request.getQueryString(tw.constant.HTTP_GATEWAY_URL_VARIABLE_SESSION_ID, ""), tw.request.getQueryString(tw.constant.HTTP_GATEWAY_URL_VARIABLE_SESSION_KEY, ""), PRCServer);

	var attach_count = decode_obj.getHTTPData(tw.session.currentDelivery.packageId.toString());

	var cryptStat = decode_obj.getCryptStatus();
	var status = decode_obj.getStatus();
	
	if ( status == -1 )
	{
		// get the error codes back from PRC
		var errorCode = decode_obj.getErrorCode();
		var appErrorCode = decode_obj.getAppErrorCode();
		
		// Append these to the redirect url which will take us to the error
		// page
		var redirect_url = tw.request.addQueryString("errorCode",errorCode);
		var redirect_url = tw.request.addQueryString("appStatus",appErrorCode);
		
		// processing of this tpl will end here
		tw.redirect("SGMS_PRCErrorPages.tpl");
	}		

	if(attach_count<0){
		var err = new Error(attach_count);
		err.message = "PRC Decryption Failed. Code:" + attach_count;
		TW_HandleError(err);
	} 

//}


var imagepathurl = tw.httpGateway.getImgPathUrl();
var helppathurl = tw.httpGateway.getHelpUrl();

var current_delivery = tw.session.currentDelivery;
var current_package = TW_Package.getPackageById( current_delivery.packageId);

var	is_outbound_package = current_package.packageReferenceType == tw.constant.TW_PACKAGE_REFERENCE_TYPE_SENDER;

var current_recipient;
if ( !is_outbound_package ) {
	// if it is 
	current_recipient = current_package.getRecipientById(current_delivery.recipientId );
}

var is_logged_in = tw.session.isLoggedIn;
if ( is_logged_in ) {
	var folders = tw.session.account.queryFolders( "; TW_FOLDER_TYPE asc , TW_NAME asc locale 'en_US.8859-1'; 0INT; 1INT" );
	var base_folder_url = tw.httpGateway.getUrl('TW_TxnAccDeliveryFolderView.tpl'); /*AccDeliveryFolderView*/
	var folder_length = folders.length;
	var i = 0;
	var folder_url;
	/* Get Current Folder Id , first check the HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_DESTINATION_FOLDER_ID  */ 
	var current_folder_id = tw.request.getQueryString( "dfi", "0" );
	if ( current_folder_id == "0" ) {
		current_folder_id = tw.request.getQueryString( tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_FOLDER_ID, "0" );
	}
	var custom_folders = "";
	for (i=0 ; i < folder_length; ++i ) 
	{                
		folder_url = base_folder_url;
		folder_url = folder_url.concat( "&", tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_FOLDER_ID, "=", folders[i].id );

		custom_folders = custom_folders.concat( "<option value=",
											folders[i].id,
											">",
											escapeHTML(folders[i].name),
											"</option> \n" );
	}

    // Set the page specific data.
    // set the active menu
    if ( current_folder_id == "0" ) {
        // set the active menu to ACC_DELIVERY_SEARCH
        TW_SetActiveMenuItem( tw.constant.TW_MENU_GROUP_SEARCH, "Find Message" );
    }

	var folder_obj; 
    var folder_name; 

	var default_sort_field, default_sort_order;
	default_sort_field = tw.constant.TW_SESSION_FIELD_SEND_DATE;
	if ( current_folder_id !="0" ) {
		folder_obj = TW_Folder.getFolderById( current_folder_id );
		folder_name = escapeHTML( folder_obj.name );
	} else {
		if ( (tw.session.TW_SESSION_PACKAGE_QUERY == null) || (tw.session.TW_SESSION_PACKAGE_QUERY =="" ) ) {
			folder_name = "";
		} else {
			folder_name = "Found Messages";
		}
	}

	default_sort_order = "0"; //false

	var field_type, is_ascend;
	field_type = tw.request.getQueryString(  tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_SORT_FIELD_TYPE,
											"-1" );
	is_ascend = tw.request.getQueryString(  tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_SORT_FIELD_ORDER,
											default_sort_order ); /* false; */

	if ( field_type == "-1" ) {
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

	/* get the index of the package in the folder */
	var index = tw.request.getQueryString(  tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_TABLE_START_INDEX, "0");

	// convert index to number
	var index_number = new Number( index );

	/* build the link to jump back to the folder, */
	var folder_url = base_folder_url;
	folder_url = tw.httpGateway.appendUrlQueryVariable( folder_url,
						            tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_FOLDER_ID,
							current_folder_id );
	folder_url = tw.httpGateway.appendUrlQueryVariable( folder_url,
							tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_TABLE_START_INDEX,
							index );
	folder_url = tw.httpGateway.appendUrlQueryVariable( folder_url,
							tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_SORT_FIELD_TYPE,
							field_type );
	folder_url = tw.httpGateway.appendUrlQueryVariable( folder_url,
							tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_SORT_FIELD_ORDER,
							is_ascend );	//True
	
	if ( is_outbound_package ) {
		// we need to get the tracking status.
		
		// this portion of code, mirrors in AccDeliveryFolderView.tpl. Due to lack of functions.
		// If we fix a bug here, we also need to the equilvalent fix in AccDeliveryFolderView.tpl
		var	good_status;	// boolean, indicate whether the tracking status 
		var tracking_status;	// tracking status summary string.
		var send_count, notified_count, delivered_count;

		// summarize delivery status. will be reused in other pages also. 
		good_status = (current_package.notifyBadDomainCount == 0 ) && 
					  (current_package.notifyBadAccountCount == 0 ) &&
					  (current_package.notifyGiveUpCount == 0 ) &&
					  (current_package.allMediumFailCount == 0);

		send_count = Math.min( current_package.allMediumRecipientCount, 2 );
		delivered_count = Math.min( current_package.receiveCount, 2 );
		notified_count = Math.min( current_package.notifyDoneCount, 2 );

		if ( (notified_count ==2) && ( current_package.allMediumRecipientCount >current_package.notifyDoneCount ) ) {
			notified_count = 1;
		} /* endif */

		if ( (delivered_count ==2) && (notified_count ==2) 
			 && ( current_package.allMediumRecipientCount > current_package.receiveCount) ) {
			delivered_count = 1;
		} /* endif */

		tracking_status = "";
		if	( send_count == 1 ) {
			if ( notified_count == 0 ) {	// 1, 0, 0
				tracking_status = "Not Notified";
			} else {
				if ( delivered_count == 0 ) { // 1, 1, 0
					tracking_status = "Notified";
				} else {	// 1, 1, 1
					tracking_status = "Received";
				}
			}
		} else {
			if ( send_count == 2 ) {
				if ( notified_count == 2 ) {
					if ( delivered_count == 2 ) {	// 2, 2, 2
						tracking_status = "All Received" ;
					} else { 
						if ( delivered_count == 1 ) { // 2, 2, 1
							tracking_status = "Some Received";
						} else { // 2, 2, 0
							tracking_status = "All Notified";
						}
					} 
				}else {
					if ( notified_count == 1 ) { // 2, 1,0 or 2, 1, 1
						tracking_status = "Some Notified";
					} else { // 2, 0 , 0
						tracking_status = "None Notified";
					}
				}
			}
		}
		var tracking_summary_url = tw.httpGateway.getUrl('TW_TxnAccDeliveryTracking.tpl');// AccDeliveryTracking
		tracking_summary_url = tw.httpGateway.appendUrlQueryVariable( tracking_summary_url,
									tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_STOREITEM_ID,
									current_package.id );
		tracking_summary_url = tw.httpGateway.appendUrlQueryVariable( tracking_summary_url,
									tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_FOLDER_ID,
									current_folder_id );

	} /* end of is_outbound_package */

} else { // User is not logged in

	var user_has_account;
	if ( current_recipient.description == tw.constant.SINGLE_RECIPIENT ) {
		user_has_account= (current_recipient.singleRecipient.accountId != 0);
	} else {
		// it is a maillist
		user_has_account = false;
	}

	var recipient_email = current_recipient.singleRecipient.address;
	/* we want to scramble the recipient email a bit. */
	var encoded_recipient_email;
	encoded_recipient_email = recipient_email.encodeBase64();

	if ( user_has_account ) {
		var login_url = tw.httpGateway.getUrl('TW_TxnAccEntry.tpl'); /* AccEntry */
		login_url = tw.httpGateway.appendUrlQueryVariable( login_url, 
							          tw.constant.HTTP_GATEWAY_URL_VARIABLE_PICKUP_SESSION_RECIPIENT_EMAIL ,
							          encoded_recipient_email );
		// Append the package id to the url to enable going directly to the package after login
		login_url = tw.httpGateway.appendUrlQueryVariable( login_url, 
							          tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_STOREITEM_ID,
							          current_package.id );

		// Define the URLs for reply, forward, etc. buttons
		var login_then_reply_url = login_url;
		// Append the action to the url to enable going directly to the reply package after login
		login_then_reply_url = tw.httpGateway.appendUrlQueryVariable( login_then_reply_url, 
							          		tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_ACTION_ID,
							          		 "7");
		var login_then_reply_all_url = login_url;
		// Append the action to the url to enable going directly to the reply package after login
		login_then_reply_all_url = tw.httpGateway.appendUrlQueryVariable( login_then_reply_all_url, 
							          		tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_ACTION_ID,
							          		 "8");
		var login_then_forward_url = login_url;
		// Append the action to the url to enable going directly to the forward package after login
		login_then_forward_url = tw.httpGateway.appendUrlQueryVariable( login_then_forward_url, 
							          		tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_ACTION_ID,
							          		 "9");
		var login_then_extend_expiration_url = login_url;
		// Append the action to the url to enable going directly to the reply after login
		login_then_extend_expiration_url = tw.httpGateway.appendUrlQueryVariable( login_then_extend_expiration_url, 
							          		tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_ACTION_ID,
							          		 "10");
		var login_then_delete_url = login_url;
		// Append the action to the url to enable deleting the package after login
		login_then_delete_url = tw.httpGateway.appendUrlQueryVariable( login_then_delete_url, 
							          		tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_ACTION_ID,
							          		 "11");

	}
}
// set the help url
TW_SetHelpMenuUrl( "Help", GetReceiveHelpUrl());

// Get the display for sent and expire time.
var current_time = new Date();
var date_difference, future;
var days_display = new String();
var time_display = new String();
var user_timezone_delta;
if ( is_logged_in ) {
	user_timezone_delta = tw.session.account.userTimeZoneDelta;
} else {
	user_timezone_delta= 0;
}

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
sent_time_display = sent_time_display.formatPositional( "%1$s, %2$s", days_display, time_display );

var expire_time_display = new String;
var expire_time = new Date( current_package.expireTime *1000 );
if ( current_package.saved ) {
	expire_time_display = "Never (Extended)";
} else {
	var is_package_expired = !current_package.saved && (
								(current_package.state == tw.constant.PACKAGE_STATE_EXPIRED ) ||
								(current_package.state == tw.constant.PACKAGE_STATE_EXPIRED_AND_STREAMS_DELETED ) ||
								!( current_time.getTime() < expire_time.getTime() )
								);
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

var package_subject = escapeHTML( current_package.subject );
if ( (package_subject =="") || (package_subject == null)) {
	package_subject = "(no subject)";
}

var sender, replyto;
var sender_name = new String;
if (!((current_package.senderFirstname ==null) ||(current_package.senderFirstname == "")) 
		|| !((current_package.senderLastname == null) ||(current_package.senderLastname == "") ) ) {
	sender_name = sender_name.formatPositional( "%1$s %2$s",
							  escapeHTML(current_package.senderFirstname),
							  escapeHTML(current_package.senderLastname ) );
} else { 
	sender_name = escapeHTML(current_package.senderAddress); 
}
sender=new String;
sender = sender.concat( sender_name, "&nbsp;(", current_package.senderAddress, ")" ) ;

replyto = current_package.replytoAddr;

/*
 send time and expire time is still handled by C++. due to that the same algorithm is used several times.
 don't want to duplicate code. If someone want to customize the result, they can always do with the script.
 To access sent_time and expire_time, check out the scheduleTime and expireTime property in current_package.
*/

//  get all recipients from the package and format them respectively
var recipient_query= " TW_IS_RECIPIENT_LIST =0; TW_ADDRESS asc; 0INT,";
recipient_query = recipient_query.concat( Number.MAX_UINT32, "INT" );
var package_recipients = current_package.queryRecipients( recipient_query );

var to_recipients, cc_recipients, bcc_recipients;
var to_set, cc_set, bcc_set;
var to_count = 0;
var cc_count = 0;
var bcc_count = 0;
var i;
to_recipients="";
cc_recipients = "";
bcc_recipients = "";
// we only show two recipients in each category, the rest we show as More...
for ( i = 0; ( (i < package_recipients.length) && ( (to_count <= 2) || (cc_count <=2) ||(bcc_count<=2) )); ++i ) 
{
	var individual = "";
	if ( package_recipients[i].description == tw.constant.SINGLE_RECIPIENT ) {
		individual = individual.concat( package_recipients[i].singleRecipient.address );
	} else {
		individual = individual.concat( "List ", 
										package_recipients[i].recipientList.mailList );
	}

	if ( package_recipients[i].category == tw.constant.RECIPIENT_CATEGORY_TO ) {
		if ( to_count < 2 ) {
			if ( to_count > 0 ) {
				to_recipients = to_recipients.concat( ", " );
			} 
			to_recipients = to_recipients.concat( individual );
		}
		to_count++;
	} else {
		if ( package_recipients[i].category == tw.constant.RECIPIENT_CATEGORY_CC ) {
			if ( cc_count < 2 ) {
				if ( cc_count > 0 ) {
					cc_recipients = cc_recipients.concat( ", " );
				} 
				cc_recipients = cc_recipients.concat( individual );
			}
			cc_count++;
		} else {
			if ( package_recipients[i].category == tw.constant.RECIPIENT_CATEGORY_BCC ) {
				if ( bcc_count < 2 ) {
					if ( bcc_count > 0 ) {
						bcc_recipients = bcc_recipients.concat( ", " );
					} 
					bcc_recipients = bcc_recipients.concat( individual );
				}
				bcc_count++;
			}
		}
	}
}

var more_recipient_url = tw.httpGateway.getUrl('TW_TxnAccDeliveryPageAllRecipients.tpl'); 
more_recipient_url = tw.httpGateway.appendUrlQueryVariable( more_recipient_url,
															tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_STOREITEM_ID,
															current_package.id );
var show_more_recipient="";

// Please be carefull here when you want to change the logic of this more link.
// It is tricky about the matching quotes.
// We actually output the link in two different fashion, one is javascript enabled
// one is for javascript is not enabled. 
show_more_recipient = show_more_recipient.concat( "<script language=javascript>",
										  "document.write(\"",
										  "<a href = \\\"javascript:OpenBrWindow('",
										  more_recipient_url,
										  "', '', 'resizable=yes,scrollbars=yes,width=350,height=400') \\\"",
										  " onMouseOut=\\\"DisplayStatusMsg(' '); return document.MM_returnValue\\\" onMouseOver=\\\"DisplayStatusMsg('",
										  "Click to see all recipients...", "'); return document.MM_returnValue\\\">",
										  "More ...", "</a>" ,
										  "\"); </script>",
										  "<noscript>",
										  "<a href='",
										  more_recipient_url,
										  "' target='_blank'>","More ...", "</a>",
										  "</noscript>"
										  );

if ( to_count > 2 ) {
	to_recipients = to_recipients.concat( ", ", show_more_recipient );
}

if ( cc_count > 2 ) {
	cc_recipients = cc_recipients.concat( ", ", show_more_recipient );
}

if ( bcc_count > 2 ) {
	bcc_recipients = bcc_recipients.concat( ", ", show_more_recipient );
}

%> 
<HTML>
<!-- #BeginTemplate "/Templates/TW_AccCentralAndPickupMenu.dwt" --> 
<SCRIPT language=JavaScript>
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

function OpenBrWindow( url, win_name, features )
{
	window.open( url, win_name, features );
}


function DisplayStatusMsg( msg )
{
	status = msg;
	document.MM_returnValue = true;
}

//-->
</SCRIPT>
<HEAD>
<!-- #BeginEditable "EditJavaScripts" --> <!-- put here all page specific the global variables, TW script or JavaScript. See AccDeliveryFolderView.tpl for example --> 
<SCRIPT language=JavaScript>
<!--Many features on this page will not operate as this browser does not support Javascript.-->
<!--

function SubmitAction( submit_obj, action_obj, folder_action )
{
	action_obj.value = folder_action;
	submit_obj.submit();
}

w=null

<% 
	// initialize variables used in multiple places in the template.

	var show_initializing_popup = tw.request.getQueryString("ap", "1");
	show_initializing_popup = show_initializing_popup != "0";

	var host_with_port;
	var full_gateway_url;
	if(tw.request.isSSL){
		host_with_port = getRealSecureHostnamePort();
		full_gateway_url = "https://" + host_with_port;
	} else {
		host_with_port = getRealHostnamePort();
		full_gateway_url = "http://" + host_with_port;
	}

	var desktop_url = "/desktop"; // Configuration default
	var desktop_virtual_urls = tw.server.getConfigParameter("TW_DESKTOP_VIRTUAL_URLS");
	if( desktop_virtual_urls.length > 0 ) { // Should always be there under good config.
    	desktop_url = desktop_virtual_urls[0];
	} else {
    	// Ideally we should complain about bad config at this point, but there isn't a way.
  	}
	desktop_url = full_gateway_url + desktop_url;

	/*
		Get delivery id: we pass session id, session key and i=session_id&k=session_key
	*/
	var delivery_id = "";
	delivery_id = tw.httpGateway.appendUrlQueryVariable(
		delivery_id,
		tw.constant.HTTP_GATEWAY_URL_VARIABLE_SESSION_ID,
		tw.session.id
	);
	delivery_id = tw.httpGateway.appendUrlQueryVariable(
		delivery_id,
		tw.constant.HTTP_GATEWAY_URL_VARIABLE_SESSION_KEY,
		tw.session.key
	);

	var pickup_applet_initializing_transaction_id = "TW_TxnPickupAppletInitializing.tpl";
%>

// Returns a cookie value, given the name of the cookie
function getCookie(Name) {
	var search = Name+"="
	if (document.cookie.length > 0) { // if there are any cookies
		offset = document.cookie.indexOf(search)
		if (offset != -1) { // if cookie exists
			offset += search.length
			// set index of beginning of value
			end = document.cookie.indexOf(";", offset)
			// set index of end of cookie value
			if (end == -1) {
	    		end = document.cookie.length
			}
			var rval=document.cookie.substring(offset, end)
	  		return rval
		}
  	}
}

function showPopupWindow() {
	var exists = getCookie("TW_DONT_SHOW_POPUP_WINDOW")
	if (exists != null) {
    	// found it
		var rval=parseInt(exists)
		if (rval==1) {
	  	return false
	} else {
	  return true
	}
	} else {
    	return true
  	}
}

function handlePopup() {
	<% if (show_initializing_popup) { %>
		if ( showPopupWindow() ) {
			w=window.open(
				"<%=tw.httpGateway.getUrl(pickup_applet_initializing_transaction_id);%>",
				"",
				"scrollbars=1,width=420,height=250,resizable=1,dependent=1")
		} else {
			w=null
		}
	<% }  %>
}

<% if (tw.request.userAgentVendor == "netscape") { 

  var ns_applet_version = tw.server.getConfigParameter("TW_NS_RECEIVE_APPLET_VERSION");
  var ns_applet_jar_url = full_gateway_url + tw.httpGateway.getJavaUrl() + "/ReceiveAppletPackageNS.jar";

%>

function downloadNow() {
	if ( navigator.javaEnabled() ) {
		trigger = netscape.softupdate.Trigger;
    	if ( trigger.UpdateEnabled() ) {
			vi = new netscape.softupdate.VersionInfo(<%=ns_applet_version;%>);
			updateStarted = trigger.ConditionalSoftwareUpdate(
				"<%=ns_applet_jar_url;%>",
				"java/download/tumbleweed/PostaReceive/",
				vi,
				trigger.DEFAULT_MODE
	  		);
	  		if (updateStarted) {
	    		document.write(
					'<font face="Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular" size="-1">Downloading the latest version of the software... You will need to restart Navigator to make it available after the installation is complete.</font>'
				);
	  		} else {
	    		document.write('<APPLET CODE="tumbleweed.postareceive.posta.receive.app.ReceiveApplet" WIDTH=500 HEIGHT=400>');
				document.write('<PARAM NAME=serverURL VALUE="<%=desktop_url;%>">' );
				document.write('<PARAM NAME=deliveryID VALUE=<%=delivery_id;%>>' );
				document.write('</APPLET>');
	  		}
		} else {
			alert('"Please enable SmartUpdate and re-visit this page."');
		}
		handlePopup();
	} else {
    	alert('"Please enable Java and re-visit this page."');
	}
}

function forceAppletDownload() {
	trigger = netscape.softupdate.Trigger;
	trigger.StartSoftwareUpdate( "<%=ns_applet_jar_url;%>", trigger.FORCE_MODE );

	// set the correct version in the cookie
	document.cookie="TW_EN_APPLET_VERSION=<%=ns_applet_version;%>;expires=Friday, 01-Jan-2010 00:00:00 GMT;path=/;domain=<%=host_with_port;%>;"
}

<% }  %>

//-->
</SCRIPT>
<!-- #EndEditable --> <!-- #BeginEditable "EditHtmlTitle" --> <% if (is_logged_in && (folder_name!="")) { %> 
<title>VeriSign PrivatePath service</title>
<% } else { %> 
<title>VeriSign PrivatePath service</title>
<% } %> <!-- #EndEditable --> 
<link rel="stylesheet" href="<%=tw.httpGateway.getStylesheetPathUrl();%>/verisign.css">
</HEAD>
<body bgcolor="#ffffff" background="<%=imagepathurl;%>/background.gif" leftmargin="0" topmargin="0"  marginwidth="0" marginheight="0" name="main">

<table border="0" cellpadding="0" cellspacing="0" align="top">

  <!-- VeriSign logo -->
  <tr> 
    <td rowspan="3" valign="top" height="84"><img name="logo" src="<%=imagepathurl;%>/verisign.gif" width="150" height="84" border="0"></td>
    <td valign="top" height="13" width="520"><img src="<%=imagepathurl;%>/1ptrans.gif" height="13" width="1" border="0"></td>
  </tr>
  
  <tr> 
    <td width="100%"  height="25"  valign="top"  background="<%=imagepathurl;%>/hd_home_top.gif">&nbsp;</td>
  </tr>

  <!-- top image -->
  <tr valign="top"> 
    <td width="100%"  height="46" valign="top" background="<%=imagepathurl;%>/hd_home.gif"  bgcolor="#d8d7b8">&nbsp;&nbsp;<br>&nbsp;&nbsp;
	<span class="bigblue">
    <% if (is_logged_in && (folder_name!="")) { %>
            <a href="<%=folder_url;%>"><font color="#000066"><%=folder_name;%></font></a>
            &gt;&nbsp;Message 
    <% } else {  %>
            Message 
    <% }  %></span>
    <noscript>
    <br> 
		<left>
			<font size='-1'>Many features on this page will not operate as this browser does not support Javascript.</font> 
        </left>
    </noscript> 
  </tr>

<tr valign="top">
  
   <!-- left nav bar -->
   <td width="150" height="360">
     <table width="100%" cellspacing="0" cellpadding="0" border="0">
	   <tr valign="top">
	     <td valign="top" background="<%=imagepathurl;%>/nav_background.gif" height="360" width="150">
		 
		 <br>
		 <br>
		 <br>
			<% 
				TW_MenuBuilder( imagepathurl );
			%>
		 </td>
	   </tr>
	 </table>
	</td>

    <td valign=top width="*"> 

	<table cellpadding=0 cellspacing=0 border="0" width="100%">           
			<tr>
				<td colspan=2>
          
          <table valign="TOP" cellpadding=0 cellspacing=4 border="0" width="100%">
          	<tr>
  		      <td width=10></td>
              <td><img height=15 src="<%=imagepathurl;%>/spacer.gif"></td>
              <td></td>
              <td width=10></td>
            </tr>
			<tr>
   			<td></td>
			<td>
				<table border=0 cellspacing="4" cellpadding="0" align="left">
                   <tr>
                      <td align="RIGHT" valign=baseline NOWRAP><font size="-1" face="Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular">
                        <b>From:&nbsp;&nbsp;</b></font></td>
                      <td align="LEFT" valign=BASELINE><font size="-1"><%=sender;%></font></td>
                    </tr>
		
                    <% if (to_recipients != "" ) { %>
                   <tr>
                      <td align="RIGHT" valign=baseline NOWRAP><font size="-1" face="Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular">
                        <b>To:&nbsp;&nbsp;</b></font></td>
                      <td align="LEFT" valign=BASELINE><font size="-1"><%=to_recipients;%></font></td>
                    </tr>
                    <% }  %> 

                    <% if (cc_recipients != "") { %>
                   <tr>
                      <td align="RIGHT" valign=baseline NOWRAP><font size="-1" face="Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular">
                        <b>CC:&nbsp;&nbsp;</b></font></td>
                      <td align="LEFT" valign=BASELINE><font size="-1"><%=cc_recipients;%></font></td>
                    </tr>
                    <% }  %> 
                    
                    <% if ((bcc_recipients != "") && is_outbound_package ) { %>
                   <tr>
                      <td align="RIGHT" valign=baseline NOWRAP><font size="-1" face="Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular">
                        <b>BCC:&nbsp;&nbsp;</b></font></td>
                      <td align="LEFT" valign=BASELINE><font size="-1"><%=bcc_recipients;%></font></td>
                    </tr>
                    <% }  %>

		           <tr>
                      <td align="RIGHT" valign=baseline NOWRAP><font size="-1" face="Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular">
                        <b>Subject:&nbsp;&nbsp;</b></font></td>
                      <td align="LEFT" valign=BASELINE><font size="-1"><%=package_subject;%></font></td>
                    </tr>
         
                   <tr>
                      <td align="RIGHT" valign=baseline NOWRAP><font size="-1" face="Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular">
                        <b>Sent:&nbsp;&nbsp;</b></font></td>
                      <td align="LEFT" valign=BASELINE><font size="-1"><%=sent_time_display;%></font></td>
                    </tr>

                   <tr>
                      <td align="RIGHT" valign=baseline NOWRAP><font size="-1" face="Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular">
                        <b>Signature:&nbsp;&nbsp;</b></font></td>
                      <td align="LEFT" valign=BASELINE><font size="-1"><div id="signature_status"><%=ResolveCryptStatus(decode_obj.getCryptStatus(),decode_obj.getMsgType()); %></div></font></td>
                    </tr>

                   <tr>
                      <td align="RIGHT" valign=baseline NOWRAP><font size="-1" face="Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular">
                        <b>Expires:&nbsp;&nbsp;</b></font></td>
                      <td align="LEFT" valign=BASELINE><font size="-1"><%=expire_time_display;%></font></td>
                    </tr>

                    <% if ((replyto != null) && ( replyto != "" ) && (replyto != current_package.senderAddress) ) { %>
                   <tr>
                      <td align="RIGHT" valign=baseline NOWRAP><font size="-1" face="Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular">
                        <b>Reply To:&nbsp;&nbsp;</b></font></td>
                      <td align="LEFT" valign=BASELINE><font size="-1"><%=replyto;%></font></td>
                    </tr>
                    <% }  %> 
      
      
                    <% if ( is_logged_in ) {%> <% if (is_outbound_package) { %>
                    <tr>
                      <td align="RIGHT" valign=baseline NOWRAP><font size="-1" face="Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular">
                        <B>Tracking:&nbsp;&nbsp;</B></font></td>
                        <% if (good_status) { %>
							<td align="LEFT" valign=BASELINE><a href='<%=tracking_summary_url;%>'>
								<font size=-1><%=tracking_status;%> </font> </a> </td>
                        <% } else { %>
							<td align="LEFT" valign=BASELINE><a href='<%=tracking_summary_url;%>'> 
								<font size=-1><%=tracking_status;%></font></a> </td>
						<% }  %> </tr>
                    <% }  %> <% } %>
                  </table></td></tr>
            </table><!-- #EndLibraryItem --> </td>
        </tr>
        <tr> 
          <td colspan=2 align="center">
		  	<% var allow_reply_buttons = false; %>
            <%@include file="SGMS_AccDeliveryPageButtons.tpl" %>
          </td>
        </tr>

		<tr>
			<td colspan=6><img height="10" width="20" src="<%=imagepathurl;%>/dot.gif"></td>
		</tr>

		<tr>
			<td colspan=6><img height="10" width="20" src="<%=imagepathurl;%>/dot.gif"></td>
		</tr>

       <tr>
			<td colspan=6 align="left">
 				<table cellpadding=0 cellspacing=1 border="0" width="100%" align=left>
			        <tr>
					  <td width=10 height="1"></td>
  			          <td bgcolor="#333333"  height="1"><img src="<%=imagepathurl;%>/spacer.gif"  height="1"></td>
					  <td width=10 height="1"></td>	
			         </tr>
			    </table>
			 </td>
        </tr>
 
         <tr> 
			<td colspan=6 align="left">
 				<table cellpadding=0 cellspacing=1 border="0" width="100%" align=left>
			        <tr>
					  <td width=10>&nbsp;&nbsp;</td>
					  <td>
<%
                var package_message = "";
		package_message = escapeHTML( tw.session.readStream(decode_obj.getStreamID(0)), true );
		tw.write(package_message);
%>
				</td></tr>
			</table>
          </td>
        </tr>
       <tr>
			<td colspan=6 align="left">
 				<table cellpadding=0 cellspacing=1 border="0" width="100%" align=left>
			        <tr>
					  <td width=10 height="1"></td>
  			          <td bgcolor="#333333"  height="1"><img src="<%=imagepathurl;%>/spacer.gif"  height="1"></td>
					  <td width=10 height="1"></td>	
			         </tr>
			    </table>
			 </td>
        </tr>
 


        </tr>

							<tr>
								<td colspan=6><img height="10" width="20" src="<%=imagepathurl;%>/dot.gif"></td>
							</tr>

							<tr>
							    <td colspan=6 align="left">
 									<table cellpadding=0 cellspacing=1 border="0" width="100%" align=left>
							            <tr>
										  <td width=10>&nbsp;&nbsp;</td>
  							              <td><img height=5 src="<%=imagepathurl;%>/spacer.gif"></td>
										  <td width=10>&nbsp;&nbsp;</td>	
							             </tr>
										 <tr>
											<td width=10></td>
								             <td align=left width=100%>
										      <table width="100%" border="0" cellspacing="1" cellpadding="2" align="left" valign="TOP" bgcolor="#d8d7b8">
							                   <tr bgcolor="#d8d7b8">
													<td width="100%" nowrap> 
													<font color="#000066" face="Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular" size="-1">
													<b>Attachments</b></font></td>
												</tr>
											  </table>
											</td>
											<td width=10></td>
							         </tr>
							         <tr>
							           <td colspan="3"><img src="<%=imagepathurl;%>/dot.gif"  width="1" height="5" border="0" alt=""></td>
							         </tr>
							  
							       </table>
							     </td>
						  </tr>

							<tr>
								<td colspan=6><img height="5" width="20" src="<%=imagepathurl;%>/dot.gif"></td>
							</tr>

							<tr>
								<td colspan=6 align="left">
<% if (number_of_files > 0) { 

		var save_selected_file_url, virtual_base_url;
                virtual_base_url = tw.server.getConfigParameter( "TW_VIRTUAL_URL" );

                save_selected_file_url = virtual_base_url;
                var len = virtual_base_url.length;

                var selected_file_name = escapeHTML( "selected_files.zip" );

                if ( (len >0 ) && (virtual_base_url.substr( len-1, 1 ) == "/") ) {
                    save_selected_file_url = save_selected_file_url.concat( selected_file_name , "?" );
                } else {
                    save_selected_file_url = save_selected_file_url.concat( "/", "selected_files.zip" , "?" );
                }

                save_selected_file_url = tw.httpGateway.appendUrlQueryVariable( save_selected_file_url,
                                            tw.constant.HTTP_GATEWAY_URL_VARIABLE_SESSION_TYPE,
                                            tw.request.getQueryString( "s", "ac" )
                                            );
                save_selected_file_url = tw.httpGateway.appendUrlQueryVariable( save_selected_file_url,
                                            tw.constant.HTTP_GATEWAY_URL_VARIABLE_TRANSACTION_TYPE,
                                            "TW_TxnAccDeliveryPageSaveSelectedFile.tpl" //AccDeliveryPageSaveSelectedFile
                                            );
                save_selected_file_url = tw.httpGateway.appendUrlQueryVariable( save_selected_file_url,
                                            tw.constant.HTTP_GATEWAY_URL_VARIABLE_SESSION_ID,
                                            tw.session.id
                                            );
                save_selected_file_url = tw.httpGateway.appendUrlQueryVariable( save_selected_file_url,
                                            tw.constant.HTTP_GATEWAY_URL_VARIABLE_SESSION_KEY,
                                            tw.session.key
                                            );
                save_selected_file_url = tw.httpGateway.appendUrlQueryVariable( save_selected_file_url,
                                            tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_STOREITEM_ID,
                                            current_package.id );
                save_selected_file_url = tw.httpGateway.appendUrlQueryVariable( save_selected_file_url,
                                            tw.constant.HTTP_GATEWAY_URL_VARIABLE_PICKUP_SESSION_RECIPIENT_ID,
                                            current_package.recipientId );




%>
        <tr>
          <td colspan=2><img height=15 src="<%=imagepathurl;%>/dot.gif" width=20></td>
        </tr>
        <tr>
          <td colspan=2><img height=10 src="<%=imagepathurl;%>/dot.gif" width=20></td>
        </tr>
        <tr>
          <td colspan=2>
		<table border="0" valign="TOP" width="100%" cellspacing="1" cellpadding="2" bgcolor="#cccccc">
			<form name="save_selected_file_form" action="<%=save_selected_file_url;%>" method="POST">
                        <tr bgcolor="#d8d7b8">
                                <td nowrap align="left">
                                        <font size="-1" face="Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular" color="#000066"><b>
                                        File Name</b></font></a></td>
                                <td nowrap align="left">
                                        <font size="-1" face="Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular" color="#000066"><b>
                                        Size</font></b></a></td>
                                <td nowrap align="center">
                                        <font size="-1" face="Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular" color="#000066"><b>
                                        Action</font></b></a></td>
                        </tr>

                <% // output file table.
                    var cell = new String;
                    //var id = new Number;
                    var open_button = new String; var save_button = new String;
                    var transaction_id = new String;
                    var base_url = tw.server.getConfigParameter( "TW_VIRTUAL_URL");
                    var session_id = tw.session.id;
                    var session_key = tw.session.key;

                    var package_id = current_package.id; //TODO
                    var mime_type, extension, filename,escaped_filename, gif_name;
                    var file_url = new String;
                    var index, len;
                    var map_result;
                    var recipient_stream_state_summary = new Array(5);
                    var j = new Number; var k;
                    var all_have_same_state;
                    var image_path = new String;
                    var sz = new Number;
                    for ( i = 1; i <= attach_count; ++i ) {
                %>
			<tr bgcolor="#FFFFFF">
                        <!--column1: file name link-->
                        <%
                        if ( is_logged_in ) {
                            transaction_id = "SGMS_TxnAccDeliveryFileUrl.tpl"; //AccDeliveryFileUrl;
                        } else {
                            transaction_id = "TW_TxnPickupFileUrl.tpl"; // PickupFileUrl;
                        } /* endif */

			filename = decode_obj.getFileName(i);
                        tw.session[filename] = decode_obj.getStreamID(i);


                        // make file name url compiliant.
                        escaped_filename = "";
                        var cur_char;
                        for ( j=0; j < filename.length; ++j ) {
                            cur_char = filename.charAt(j);
                            if( (cur_char == " ") || (cur_char == "/" ) || (cur_char == "&") ||(cur_char == "#") ) {
                                escaped_filename = escaped_filename.concat( "_" );
                            } else {
                                escaped_filename = escaped_filename.concat( cur_char );
                            }
                        }

                        // find the file extension;
                        index = filename.lastIndexOf( "." );
                        if ( index != -1 ) {
                            extension = filename.substr( index+1, filename.length );
                            extension = extension.toLowerCase();
                        }
                        if ( extension.length != 0 ) {
                            map_result = tw.request.mimesMapper.extensionToMime( extension );
                            mime_type = map_result[0];
                        }

                        if ( mime_type.length == 0 ) {
                            mime_type = "application/octet-stream";
                        }

                        map_result = tw.request.mimesMapper.extensionToName ( mime_type, extension );
                        gif_name = "";
                        map_result = tw.request.mimesMapper.extensionToGifName( mime_type, extension );
                        gif_name = map_result[0];

                        if (gif_name.length == 0) {
                            gif_name = "Type_Unknown.gif";
                        } 

                        image_path = "";
                        if ( gif_name.length != 0 ) {
                            image_path=image_path.formatPositional ( "<img src=%1$s/%2$s width=14 height=16 border=0>&nbsp;",
                                                        tw.server.getConfigParameter( "TW_IMAGE_ROOT_URL" ),
                                                        gif_name );
                        }

                        // build the file url.
                        len = base_url.length;
                        file_url = base_url;
                        if (virtual_base_url.charAt(len-1) == "/" ) {
                            file_url = file_url.concat( escaped_filename, "?" );
                        } else {
                            file_url = file_url.concat( "/", escaped_filename, "?");
                        }
                        file_url = tw.httpGateway.appendUrlQueryVariable( file_url,
                                                                          tw.constant.HTTP_GATEWAY_URL_VARIABLE_SESSION_TYPE,
                                                                          "ac");
                        file_url = tw.httpGateway.appendUrlQueryVariable( file_url,
                                                                          tw.constant.HTTP_GATEWAY_URL_VARIABLE_TRANSACTION_TYPE,
                                                                          transaction_id);
                        file_url = tw.httpGateway.appendUrlQueryVariable( file_url,
                                                                          tw.constant.HTTP_GATEWAY_URL_VARIABLE_SESSION_ID,
                                                                          session_id);
                        file_url = tw.httpGateway.appendUrlQueryVariable( file_url,
                                                                          tw.constant.HTTP_GATEWAY_URL_VARIABLE_SESSION_KEY,
                                                                          session_key);
                        file_url = tw.httpGateway.appendUrlQueryVariable( file_url,
                                                                          tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_STOREITEM_ID,
                                                                          package_id.toString());
                        file_url = tw.httpGateway.appendUrlQueryVariable( file_url,
									   "filename",
                                                                          filename);

			file_url = tw.httpGateway.appendUrlQueryVariable( file_url, "index", i.toString());
										
			// massage url for file download.
                        if ( tw.request.userAgentVendor == "microsoft" ) {
                            // This is an ugly trick for MSIE
                            index = escaped_filename.lastIndexOf( "." );
                            if (  index != -1 ) {
                                file_url = tw.httpGateway.appendUrlQueryVariable( file_url,
                                                                          tw.constant.HTTP_GATEWAY_URL_VARIABLE_DOWNLOAD_EXTENSION,
                                                                          escaped_filename.substr( index, escaped_filename.length )
);
                            }

                        }
                        %>
                        <td> <%=image_path;%><a href="<%=file_url;%>"><%=escapeHTML(filename);%></a>
                        </td>

                        <!-- Column2: size -->
                        <%

                        sz = decode_obj.getSize(i);
			if (sz < 1024) {
				cell = cell.formatPositional( "%1$d Bytes", sz );
			}else{
                        	sz = sz / 1024;
				cell = cell.formatPositional( "%1$d KB", sz );
			}

                        %>
                        <td align=left>
                        <%=cell;%>
                        </td>

                        <!-- Column3: action -->
			<td nowrap align="center" width="*" >
                        <!-- in order to line up the action button, we introduce an other table here. -->
                        <table cellpadding=0 cellspacing=0 border='0'> <TR>
                          <td>
                            <table cellpadding=0 cellspacing=0 border='0'><TR>
                               <td><img height='19' width='9' src='<%=imagepathurl;%>/buttonGreyLeft.gif'></td>
                               <td bgcolor='#999999' nowrap><a href="<%=file_url;%>" class='buttonText'>
                                <font face="Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular" size='-1' color='white'>Save</fo
nt></a></td>
                                <td><img height='19' width='9' src="<%=imagepathurl;%>/buttonGreyRight.gif"></td>
                              </TR>
                            </table>
                          </td>

                        <%
                          if ( tw.request.userAgentVendor == "netscape" ) {
                            // we only show save button for the netscape
                            file_url = tw.httpGateway.appendUrlQueryVariable( file_url,
                                                                      tw.constant.HTTP_GATEWAY_URL_VARIABLE_FILE_ACTION,
                                                                      "save" );
                        %>
                          <td> &nbsp;</td>
                          <td>
                              <table cellpadding=0 cellspacing=0 border='0'><TR>
                              <td><img height='19' width='9' src="<%=imagepathurl;%>/buttonGreyLeft.gif"></td>
                              <td bgcolor='#999999' nowrap><a href="<%=file_url;%>" class='buttonText'><font face='Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular' size='-1' color='white' height='19'>Save</font></a></td>
                              <td><img height='19' width='9' src="<%=imagepathurl;%>/buttonGreyRight.gif"></td>
                            </TR> </table>
                          </td>
                        <% } %>

                        </tr> </table>
                        </td>
                      </tr>
                    <% } %>
                    </table>
                  </td>
                </tr>
              </form>
            </table>
          </td>
        </tr>
        <tr>
          <td colspan=2><img height=10 src="<%=imagepathurl;%>/dot.gif" width=20></td>
        </tr>
        <% if ( has_pdf_files ) { %>
        <tr align="center">
          <td colspan=2> <font size=-1>If necessary, <a href="http://www.adobe.com/prodindex/acrobat/readstep.html">get the Adobe Acrobat (PDF) viewer.</a></font></td>
        </tr>
        <% } %> <% } %> 

								</td>
							</tr>
							<tr nowrap>
								<td colspan=6><img border=0 height=10 src="<%=imagepathurl;%>/dot.gif" width=20></td>
							</tr>
							
      </table>
      <!-- #EndEditable --> </td>
    <td valign="top" width="7"> 
    </td>
  </tr>
</table>
</BODY>
<!-- #EndTemplate -->
</HTML>
