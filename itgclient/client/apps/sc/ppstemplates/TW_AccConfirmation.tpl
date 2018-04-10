<!-- Copyright (c) 1993-2001 Tumbleweed Communications Corp. All Rights Reserved. -->
<!-- #BeginEditable "EditTumbleweedFileName" --> <!-- File name: TW_AccConfirmation.tpl -->
<%@include file="TW_GlobalHeaderMenu.tpl" %>
<%@include file="TW_HTMLUtil.tpl" %> 
<!-- #EndEditable --> <!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 3.2 Final//EN"> <%
var imagepathurl = tw.httpGateway.getImgPathUrl();
var table_border_TW_AccConfirmation = 0; //debugging layout

var aValues = new Array ( "Day(s)",
		                  "Week(s)",
                          "Month(s)");
var iIds = new Array (0,1,2);
var outobj = new Object();
//       outobj.extend_recipients_unit		= FormatIdList(aValues,iIds,extend_recipients_unit);
var expire_in_days; 
function ApiToUiExpirationDelay(delay_in_days,units){
    if (units == tw.constant.TW_SESSION_EXPIRE_UNIT_MONTHS ) {
        return delay_in_days / 31;
    } else if (units == tw.constant.TW_SESSION_EXPIRE_UNIT_WEEKS ) {
        return delay_in_days / 7;
    } else {
        return delay_in_days;
    }
}
function toDays(time){
    return time / (24*3600);
}
var accPreferences = tw.session;
var current_time = new Date();
function time_display(end_time){
            var user_timezone_delta = 0;
            if ( tw.session.isLoggedIn ) {
                user_timezone_delta = tw.session.account.userTimeZoneDelta;
            }
            var date_difference, future;
        	var days_display = new String();
        	var t_display = new String();
        	var ex_t_display = new String();
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
			t_display =  end_time.format( "%m/%d/%Y %X, %Z", user_timezone_delta );
			ex_t_display = ex_t_display.formatPositional( "%1$s, %2$s", days_display, t_display );
            return ex_t_display;
}
function GetAbsoluteDayDifference(start,end){
            var span, future;
            var number_of_days;
            
            future = end.getTime() > start.getTime();
            if ( future ) {
                span = (end.getTime()-start.getTime())/(1000*60*60);
                number_of_days = (span + start.getHours())/24;
            } else {
                span = (start.getTime() - end.getTime())/(1000*60*60);
                number_of_days = (span + end.getHours())/24;
            } 
            return number_of_days;
}
var submit_action=tw.request.getFormFieldValue( "submit_action" );
var trans_id = tw.request.transactionId;
var is_list_view = ( 
                     submit_action   == tw.constant.HTTP_GATEWAY_ACCOUNT_SESSION_COMMAND_DELETE_SELECTED  ||
                     (submit_action  == tw.constant.HTTP_GATEWAY_ACCOUNT_SESSION_COMMAND_EXTEND_EXPIRATION && trans_id == "TW_TxnAccDeliveryFolderViewAction.tpl") ||
                     trans_id == "TW_TxnAccDeliveryFolderViewSavePackage.tpl" 
					);
var is_delete_package = ( 
                     submit_action   == tw.constant.HTTP_GATEWAY_ACCOUNT_SESSION_COMMAND_DELETE_SELECTED  ||
                     submit_action   == tw.constant.HTTP_GATEWAY_ACCOUNT_SESSION_COMMAND_DELETE ||
                     tw.request.getQueryString( tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_ACTION_ID, "0" ) == 11
                     );

var folders = TW_Folder.queryFolders(tw.session.account, "; TW_FOLDER_TYPE asc , TW_NAME asc locale 'en_US.8859-1' ; 0INT; 1INT");
var base_folder_url = tw.httpGateway.getUrl("TW_TxnAccDeliveryFolderView.tpl"); 
var folder_length = folders.length;
var i = 0;
var folder_url;
/* Get Current Folder Id , first check the HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_DESTINATION_FOLDER_ID  */
var current_folder_id = tw.request.getQueryString( tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_DESTINATION_FOLDER_ID, "0" );
if ( current_folder_id == "0" ) {
	/* check against HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_FOLDER_ID */;
	current_folder_id = tw.request.getQueryString( tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_FOLDER_ID, "0" );
}
var custom_folders = "";
for (i=0 ; i < folder_length; ++i )
{
	custom_folders = custom_folders.concat( "<option value=",
										folders[i].id,
										">",
										escapeHTML(folders[i].name),
										"</option> \n" );
}

// Set the page specific data.
// set the active menu
if ( current_folder_id == "0" ) {
    TW_SetActiveMenuItem( tw.constant.TW_MENU_GROUP_SEARCH, "Find Message" );
}

// set the help url
var helpUrl = "javascript:GoHelp('Folders','COutbox')";
TW_SetHelpMenuUrl( "Help", helpUrl );

var folder_obj;
var folder_name;
var columns_displayed;
var default_sort_field;
if ( current_folder_id !="0" ) {
	folder_obj = TW_Folder.getFolderById( current_folder_id );
	folder_name = escapeHTML( folder_obj.name );
	if ( folder_obj.folderType == tw.constant.TW_FOLDER_TYPE_OUTBOX ) {
		/* outbox type; */
		default_sort_field = tw.constant.TW_SESSION_FIELD_SEND_DATE;
		columns_displayed = tw.session.TW_SESSION_PREF_OUTBOX_COLUMN_DISPLAY;
    } else {
		default_sort_field = tw.constant.TW_SESSION_FIELD_SUBJECT;
		columns_displayed = tw.session.TW_SESSION_PREF_INBOX_COLUMN_DISPLAY;
	}
} else {
	folder_name = "Found Messages";
	default_sort_field = tw.constant.TW_SESSION_FIELD_SUBJECT;
    columns_displayed = tw.session.TW_SESSION_PREF_INBOX_COLUMN_DISPLAY;
	// make sure that folder column is set,
	if ( !(columns_displayed & tw.constant.TW_SESSION_FIELD_FOLDER) ) {
	columns_displayed = columns_displayed |	tw.constant.TW_SESSION_FIELD_FOLDER;
    }
}
// Determine table headers
var delivery_table_header = "<tr bgcolor= '#d8d7b8'>";
// first column check box.
//delivery_table_header = delivery_table_header.concat ( "<th width=1>&nbsp;</th> \n" );
var default_sort_order = default_sort_order = "0"; //false
var field_type, is_ascend;
field_type = tw.request.getQueryString( tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_SORT_FIELD_TYPE,
				default_sort_field );
is_ascend = tw.request.getQueryString( tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_SORT_FIELD_ORDER,
				default_sort_order ); /* true; */
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
var send_time_sorting_url, subject_sorting_url, expire_time_sorting_url,sender_sorting_url;
var sort_image;
var helppathurl = tw.httpGateway.getHelpUrl();
if ( columns_displayed & tw.constant.TW_SESSION_FIELD_FOLDER) { //TW_SESSION_FIELD_FOLDER
	delivery_table_header = delivery_table_header.concat( "<th nowrap align=left>",
														  "Folder",
														  "</font></th> \n"
														  );
}
if ( (tw.request.transaction_id == "TW_TxnAccDeliveryFolderViewAction.tpl") || (current_folder_id =="0") || (folder_obj.folderType != 1 ) ) {
	// not outbox
	if ( columns_displayed & tw.constant.TW_SESSION_FIELD_STATUS ) { //TW_SESSION_FIELD_STATUS
		delivery_table_header = delivery_table_header.concat( "<th nowrap align=left>",
															  "<font size='-1' face='Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular' color='#000066'>",
															  "Status",
															  "</font></th> \n"
															  );
	}
}
if ( columns_displayed & tw.constant.TW_SESSION_FIELD_PRIORITY ) { //TW_SESSION_FIELD_PRIORITY
	delivery_table_header = delivery_table_header.concat( "<th nowrap align=left>",
														  "<font size='-1' face='Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular' color='#000066'>",
														  "Priority",
														  "</font></th> \n"
														  );
}
if ( columns_displayed & tw.constant.TW_SESSION_FIELD_SENDER ) { //TW_SESSION_FIELD_SENDER
	// need to get the sorting_image
	sender_sorting_url = base_folder_url;
	sender_sorting_url = tw.httpGateway.appendUrlQueryVariable( sender_sorting_url,
																tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_FOLDER_ID,
																current_folder_id );
	sender_sorting_url = tw.httpGateway.appendUrlQueryVariable( sender_sorting_url,
																tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_TABLE_START_INDEX,
																index );
	sender_sorting_url = tw.httpGateway.appendUrlQueryVariable( sender_sorting_url,
																tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_SORT_FIELD_TYPE,
																tw.constant.TW_SESSION_FIELD_SENDER );
	if ( field_type != tw.constant.TW_SESSION_FIELD_SENDER ) {
		sort_image = imagepathurl + "/sortedNot.gif";
		sender_sorting_url = tw.httpGateway.appendUrlQueryVariable( sender_sorting_url,
																	tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_SORT_FIELD_ORDER,
																	"0" );	//False
	} else if ( is_ascend == "1" ) {
		sort_image = imagepathurl + "/sortedUp.gif";
		sender_sorting_url = tw.httpGateway.appendUrlQueryVariable( sender_sorting_url,
																	tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_SORT_FIELD_ORDER,
																	"0" );	//True
	} else {
		sort_image = imagepathurl + "/sortedDown.gif";
		sender_sorting_url = tw.httpGateway.appendUrlQueryVariable( sender_sorting_url,
																	tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_SORT_FIELD_ORDER,
																	"1" );	//True
	}
	delivery_table_header = delivery_table_header.concat( "<th nowrap align=left>",
														  "<font size='-1' face='Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular' color='#000066'>",
														  "From",
														  "</font></th> \n"
														  );
}
if ( columns_displayed & tw.constant.TW_SESSION_FIELD_SUBJECT ) { //TW_SESSION_FIELD_SUBJECT
	subject_sorting_url = base_folder_url;
	subject_sorting_url = tw.httpGateway.appendUrlQueryVariable( subject_sorting_url,
																tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_FOLDER_ID,
																current_folder_id );
	subject_sorting_url = tw.httpGateway.appendUrlQueryVariable( subject_sorting_url,
																tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_TABLE_START_INDEX,
																index );
	subject_sorting_url = tw.httpGateway.appendUrlQueryVariable( subject_sorting_url,
																 tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_SORT_FIELD_TYPE,
																 tw.constant.TW_SESSION_FIELD_SUBJECT );
	// need to get the sorting_image
	if ( field_type != tw.constant.TW_SESSION_FIELD_SUBJECT ) {
		sort_image = imagepathurl + "/sortedNot.gif";
		subject_sorting_url = tw.httpGateway.appendUrlQueryVariable( subject_sorting_url,
																	tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_SORT_FIELD_ORDER,
																	"0" );	//False
	} else if ( is_ascend == "1" ) {
		sort_image = imagepathurl + "/sortedUp.gif";
		subject_sorting_url = tw.httpGateway.appendUrlQueryVariable( subject_sorting_url,
																	tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_SORT_FIELD_ORDER,
																	"0" );	//False
	} else {
		sort_image = imagepathurl + "/sortedDown.gif";
		subject_sorting_url = tw.httpGateway.appendUrlQueryVariable( subject_sorting_url,
																	 tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_SORT_FIELD_ORDER,
																	"1" );	//True
	}
	delivery_table_header = delivery_table_header.concat( "<th nowrap align=left>",
														  "<font size='-1' face='Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular' color='#000066'>",
														  "Message",
														  "</font></th> \n"
														  );														
}
if ( columns_displayed & tw.constant.TW_SESSION_FIELD_RECIPIENTS ) { //TW_SESSION_FIELD_RECIPIENTS
	delivery_table_header = delivery_table_header.concat( "<th nowrap align=left>",
														  "<font size='-1' face='Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular' color='#000066'>",
														  "To",
														  "</font></th> \n"
														  );
}
if ( (tw.request.transaction_id != "TW_TxnAccDeliveryFolderViewAction.tpl" ) && (current_folder_id != "0" ) && (folder_obj.TW_FOLDER_TYPE==1) ) {
	// outbox case
	if ( columns_displayed & tw.constant.TW_SESSION_FIELD_STATUS ) { //TW_SESSION_FIELD_STATUS
		delivery_table_header = delivery_table_header.concat( "<th nowrap align=left>",
															  "<font size='-1' face='Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular' color='#000066'>",
															  "Tracking",
															  "</font></th> \n"
															  );
	}
}
if ( columns_displayed & tw.constant.TW_SESSION_FIELD_BILLCODE ) { //TW_SESSION_FIELD_BILLCODE
	delivery_table_header = delivery_table_header.concat( "<th nowrap align=left>",
														  "<font size='-1' face='Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular' color='#000066'>",
														  "Billing Code",
														  "</font></th> \n"
														  );
}
if ( columns_displayed & tw.constant.TW_SESSION_FIELD_RECEIVED ) { //TW_SESSION_FIELD_RECEIVED
	delivery_table_header = delivery_table_header.concat( "<th nowrap align=right>",
														  "<font size='-1' face='Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular' color='#000066'>",
														  "Received",
														  "</font></th> \n"
														  );
}
if ( columns_displayed & tw.constant.TW_SESSION_FIELD_EXPIRATION ) { //TW_SESSION_FIELD_EXPIRATION
	expire_time_sorting_url = base_folder_url;
	expire_time_sorting_url = tw.httpGateway.appendUrlQueryVariable( expire_time_sorting_url,
																tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_FOLDER_ID,
																current_folder_id );
	expire_time_sorting_url = tw.httpGateway.appendUrlQueryVariable( expire_time_sorting_url,
																tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_TABLE_START_INDEX,
																index );
	expire_time_sorting_url = tw.httpGateway.appendUrlQueryVariable( expire_time_sorting_url,
																	tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_SORT_FIELD_TYPE,
																	tw.constant.TW_SESSION_FIELD_EXPIRATION );
	// need to get the sorting_image
	if ( field_type != tw.constant.TW_SESSION_FIELD_EXPIRATION ) {
		sort_image = imagepathurl + "/sortedNot.gif";
		expire_time_sorting_url = tw.httpGateway.appendUrlQueryVariable( expire_time_sorting_url,
																	tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_SORT_FIELD_ORDER,
																	"0" );	//False
	} else if ( is_ascend == "1" ) {
		sort_image = imagepathurl + "/sortedUp.gif";
		expire_time_sorting_url = tw.httpGateway.appendUrlQueryVariable( expire_time_sorting_url,
																	tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_SORT_FIELD_ORDER,
																	"0" );	//True
	} else {
		sort_image = imagepathurl + "/sortedDown.gif";
		expire_time_sorting_url = tw.httpGateway.appendUrlQueryVariable( expire_time_sorting_url,
																	tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_SORT_FIELD_ORDER,
																	"1" );	//True
	}
	delivery_table_header = delivery_table_header.concat( "<th nowrap align=right>",
														  "<font size='-1' face='Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular' color='#000066'>",
														  "Expires",
														  "</font></th> \n"
														  );
}
if ( columns_displayed & tw.constant.TW_SESSION_FIELD_FILES ) { //TW_SESSION_FIELD_FILES
	delivery_table_header = delivery_table_header.concat( "<th nowrap align=right>",
														  "<font size='-1' face='Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular' color='#000066'>",
														  "Files",
														  "</font></th> \n"
														  );
}
if ( columns_displayed & tw.constant.TW_SESSION_FIELD_KBYTE ) { //TW_SESSION_FIELD_KBYTE
	delivery_table_header = delivery_table_header.concat( "<th nowrap align=right>",
														  "<font size='-1' face='Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular' color='#000066'>",
														  "Size"," \n",
                                                          "(","KB",")",
                                                          "</font></th> \n"
														  );
}
delivery_table_header = delivery_table_header.concat( "</tr>" );
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
<%
    var row_per_page;
    if ( (current_folder_id == "0") || (folder_obj.folderType != 1) ) {
        // not outbox folder, retrieve based inbox preference.
        row_per_page = tw.session.TW_SESSION_PREF_INBOX_ROW_COUNT;
    } else {
        row_per_page = tw.session.TW_SESSION_PREF_DELIVERY_ROW_COUNT;
    }
    var package_ids = new String;
    if (is_list_view && trans_id != "TW_TxnAccDeliveryFolderViewSavePackage.tpl") {
      for ( i = 0;  i < row_per_page ; ++i ) {
		var name = tw.constant.HTTPGATEWAY_CHECKBOX_NAME_FOR_SELECT_ALL + i.toString();
		var id_str;
        id_str = tw.request.getFormFieldValue(name);
        if (id_str != "")
        {   if (package_ids == "")
            {package_ids = id_str;
            } else {
            package_ids = package_ids + "," + id_str;
            }
        }
      }
    } else {
    package_ids = tw.request.getQueryString( tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_STOREITEM_ID, "0");
    }
var confirmation_title;
var confirmation_header;
var confirmation_message;
var about_to_delete_or_extend;
var delete_or_extend_button;
var package_id_array = package_ids.split(","); /* package_ids is a comma seperated list of ids */ 
var num_packages = 1;
if ( package_id_array.length > 1 ) {
    num_packages = package_id_array.length;
}
var packages = new Array;
for ( i= 0; i < num_packages; ++i )
{   
    packages[i] = TW_Package.getPackageById(package_id_array[i]);
}
if ( is_delete_package ) {
    if ( num_packages == 1 ) {
        confirmation_title = "Delete Message?";
        confirmation_header = "Delete Message?";
    } else {
        confirmation_title = "Delete Messages?";
        confirmation_header = "Delete Messages?";
    }
    about_to_delete_or_extend = "About to Delete:";
    delete_or_extend_button = "Delete";
} else {
    if ( num_packages == 1 ) {
        confirmation_header = "Extend the Expiration of this Message";
    } else {
        confirmation_header = "Extend Expiration?";
    }
    confirmation_title = "Extend Expiration?";
    about_to_delete_or_extend = "About to Extend Expiration:";
    delete_or_extend_button = "Extend";
}
var extend_personal;
var extend_recipients;
var is_sender = false;
var all_saved = true;
var same_expire_time = true;
var same_expiration_dates = true;
var last_expire_time = new Date();
var extend_personal_date = new String;
var cancel_button_url;
var current_package_url; // only for non-list view
if (  is_list_view ) {
     cancel_button_url = folder_url;
} else { // detailed package
      // construct the page url
      // first get the query variables
     var current_folder_id = tw.request.getQueryString( tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_FOLDER_ID, "0" );
     var index = tw.request.getQueryString( tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_TABLE_START_INDEX, "0");
     var sort_field_type = tw.request.getQueryString( tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_SORT_FIELD_TYPE,
	     		                        tw.constant.TW_SESSION_FIELD_SEND_DATE /* default sort field */ );
     var sort_is_ascend = tw.request.getQueryString( tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_SORT_FIELD_ORDER,
	    			   "0" /* default_sort_order = false */ );
     var current_package_id = tw.request.getQueryString( tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_STOREITEM_ID, "0");
	  // then, add them to the url
      current_package_url = tw.httpGateway.getUrl("TW_TxnAccDeliveryPageEntry.tpl"); 
      current_package_url = tw.httpGateway.appendUrlQueryVariable( current_package_url,
						                      tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_FOLDER_ID,
						                      current_folder_id );
      current_package_url = tw.httpGateway.appendUrlQueryVariable( current_package_url,
						                      tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_TABLE_START_INDEX,
						                      index );
      current_package_url = tw.httpGateway.appendUrlQueryVariable( current_package_url,
						                      tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_SORT_FIELD_TYPE,
						                      sort_field_type );
      current_package_url = tw.httpGateway.appendUrlQueryVariable( current_package_url,
						                      tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_SORT_FIELD_ORDER,
						                      sort_is_ascend );
      current_package_url = tw.httpGateway.appendUrlQueryVariable( current_package_url,
						                      tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_STOREITEM_ID,
						                      current_package_id );
     cancel_button_url = current_package_url;
	 var current_package = TW_Package.getPackageById(current_package_id);
     var package_subject = escapeHTML( current_package.subject );  
     if ( (package_subject =="") || (package_subject == null)) {
	     package_subject = "(no subject)";
     }
	
   	 var expire_time = new Date( current_package.expireTime *1000 );
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
     
	 var current_delivery = tw.session.currentDelivery;
	 var is_outbound_package = current_package.packageReferenceType == tw.constant.TW_PACKAGE_REFERENCE_TYPE_SENDER;
	 var current_recipient;
	 if ( !is_outbound_package ) {
	 	// if it is
	 	current_recipient = current_package.getRecipientById(current_delivery.recipientId );
	 }
	var is_logged_in = tw.session.isLoggedIn;
    is_sender = is_logged_in && is_outbound_package;
    if ( is_outbound_package ) {
		// we need to get the tracking status.
		
		// This portion of code is duplicated from TW_AccDeliveryFolderView.tpl. To be factored!
		var	good_status;	// boolean, indicate whether the tracking status
		var tracking_status;	// tracking status summary string.
		var send_count, notified_count, delivered_count;
		// summarize delivery status. will be reused in other pages also.
		good_status = (current_package.notifyBadDomainCount == 0 ) &&
					  (current_package.notifyBadAccountCount == 0 ) &&
					  (current_package.notifyGiveUpCount == 0 );
		send_count = Math.min( current_package.allMediumRecipientCount, 2 );
		delivered_count = Math.min( current_package.receiveCount, 2 );
		notified_count = Math.min( current_package.notifyDoneCount, 2 );
		if ( (notified_count ==2) && ( current_package.allMediumRecipientCount >current_package.notifyDoneCount ) ) {
			notified_count = 1;
		} /* endif */
		if ( (delivered_count ==2) && (notified_count ==2)
			 && ( current_package.allMediumRecipientCount > current_package.allMediumSuccessCount ) ) {
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
		var tracking_summary_url = tw.httpGateway.getUrl( "TW_TxnAccDeliveryTracking.tpl" );// AccDeliveryTracking
		tracking_summary_url = tw.httpGateway.appendUrlQueryVariable( tracking_summary_url,
									tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_STOREITEM_ID,
									current_package.id );
		tracking_summary_url = tw.httpGateway.appendUrlQueryVariable( tracking_summary_url,
									tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_FOLDER_ID,
									current_folder_id );
	} /* end of is_outbound_package */
    var user_timezone_delta;
	if ( is_logged_in ) {
		user_timezone_delta = tw.session.account.userTimeZoneDelta;
	} else {
		user_timezone_delta= 0;
	}
    extend_personal = 0;
	var sent_time = new Date( current_package.scheduleTime *1000); // date object takes milliseconds
	var sent_time_display = new String;
    sent_time_display = time_display(sent_time);
	var expire_time_display = new String;
    var package_expiration_date;
    package_expiration_date = time_display(expire_time);
    var is_package_expired = false;
	if ( current_package.saved ) {
		expire_time_display = "Never (Extended)";
	} else {
		is_package_expired = !current_package.saved && (
									(current_package.state == tw.constant.PACKAGE_STATE_EXPIRED ) ||
									(current_package.state == tw.constant.PACKAGE_STATE_EXPIRED_AND_STREAMS_DELETED ) ||
									!( current_time.getTime() < expire_time.getTime() )
									);
		if ( is_package_expired ) {
			expire_time_display = "Expired";
		} else {
            expire_time_display = time_display(expire_time);
		}
	}  
// Build the To:, CC:, BCC: fields from the Dynamic Attributes - Begin
    if ( current_package.saved ) {
         extend_personal_date = "Never (Extended)";
         } else {
         extend_personal_date = expire_time_display;
         }
	var to_recipients	= "";
	var to_count		= 0;
	var attribute_prefix= tw.constant.TW_PACKAGE_RECIPIENT_RFC822_TO_;
	var attribute_index = 0;
	while ( (current_package[attribute_prefix + attribute_index] != null) && (to_count < 2) ) {
		if ( to_count > 0 ) {
			to_recipients = to_recipients.concat( ", " );
		}
		to_recipients = to_recipients.concat( current_package[attribute_prefix + attribute_index] );
		++attribute_index;
		++to_count;
	}
	var cc_recipients	= "";
	var cc_count		= 0;
	attribute_prefix 	= tw.constant.TW_PACKAGE_RECIPIENT_RFC822_CC_;
	attribute_index 	= 0;
	while ( (current_package[attribute_prefix + attribute_index] != null) && (cc_count < 2) ) {
		if ( cc_count > 0 ) {
			cc_recipients = cc_recipients.concat( ", " );
		}
		cc_recipients = cc_recipients.concat( current_package[attribute_prefix + attribute_index] );
		++attribute_index;
		++cc_count;
	}
	var bcc_recipients	= "";
	var bcc_count		= 0;
	attribute_prefix 	= tw.constant.TW_PACKAGE_RECIPIENT_RFC822_BCC_;
	attribute_index 	= 0;
	while ( (current_package[attribute_prefix + attribute_index] != null) && (bcc_count < 2) ) {
		if ( bcc_count > 0 ) {
			bcc_recipients = bcc_recipients.concat( ", " );
		}
		bcc_recipients = bcc_recipients.concat( current_package[attribute_prefix + attribute_index] );
		++attribute_index;
		++bcc_count;
	}
	var to_clause_already_build = (to_count > 0) ? true : false;
	var cc_clause_already_build = (cc_count > 0) ? true : false;
	var bcc_clause_already_build = (bcc_count > 0) ? true : false;
	//  get all recipients from the package and format them respectively
	var recipient_query= " TW_IS_RECIPIENT_LIST =0; TW_ADDRESS asc; 0INT,";
	recipient_query = recipient_query.concat( Number.MAX_UINT32, "INT" );
	var package_recipients = current_package.queryRecipients( recipient_query );
	// we only show two recipients in each category, the rest we show as More...
	var i;
	for ( i = 0; ( (i < package_recipients.length) && ( (to_count <= 2) || (cc_count <=2) ||(bcc_count<=2) )); ++i )
	{
		var individual = "";
		if ( package_recipients[i].description == tw.constant.SINGLE_RECIPIENT ) {
			individual = individual.concat( package_recipients[i].singleRecipient.address );
		} else {
			individual = individual.concat( "List ", package_recipients[i].recipientList.mailList );
		}
		if ( package_recipients[i].category == tw.constant.RECIPIENT_CATEGORY_TO && !to_clause_already_build) {
			if ( to_count < 2 ) {
				if ( to_count > 0 ) {
					to_recipients = to_recipients.concat( ", " );
				}
				to_recipients = to_recipients.concat( individual );
			}
			to_count++;
		} else if ( package_recipients[i].category == tw.constant.RECIPIENT_CATEGORY_CC && !cc_clause_already_build ) {
			if ( cc_count < 2 ) {
				if ( cc_count > 0 ) {
					cc_recipients = cc_recipients.concat( ", " );
				}
				cc_recipients = cc_recipients.concat( individual );
			}
			cc_count++;
		} else if ( package_recipients[i].category == tw.constant.RECIPIENT_CATEGORY_BCC && !bcc_clause_already_build ) {
			if ( bcc_count < 2 ) {
				if ( bcc_count > 0 ) {
					bcc_recipients = bcc_recipients.concat( ", " );
				}
				bcc_recipients = bcc_recipients.concat( individual );
			}
			bcc_count++;
		}
	}
	var more_recipient_url = tw.httpGateway.getUrl( "TW_TxnAccDeliveryPageAllRecipients.tpl" );
	more_recipient_url = tw.httpGateway.appendUrlQueryVariable( more_recipient_url,
																tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_STOREITEM_ID,
																current_package.id );
	var show_more_recipient="";
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
       var extend_recipients_date = new Date();
       extend_recipients_date = expire_time; 
       var extend_recipients_unit = accPreferences.TW_SESSION_PREF_PACKAGE_EXPIRATION_DELAY_UNIT;
       outobj.extend_recipients_unit		= FormatIdList(aValues,iIds,extend_recipients_unit);
       expire_in_days = GetAbsoluteDayDifference(current_time, expire_time);
       var extend_recipients_delay = ApiToUiExpirationDelay(expire_in_days, accPreferences.TW_SESSION_PREF_PACKAGE_EXPIRATION_DELAY_UNIT);
       var extend_recipients_unit_index = extend_recipients_unit.toString();
}
%>
<SCRIPT language=JavaScript>
<!-- -->Many features on this page will not operate as this browser does not support Javascript.
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
//-->
</SCRIPT>
 <!-- #EndEditable -->
<HEAD>
<!-- #BeginEditable "EditHtmlTitle" -->
<TITLE> VeriSign PrivatePath service</TITLE>
<% // building the page title for the confirmation page 
// 1. pageTitle starts with folder name
var pageTitle = '';
pageTitle = pageTitle.concat('&nbsp; <a href="', folder_url, '">', 
                             '<font face="Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular" color="#000066">',
							 folder_name, 
							 '</font>',
							 '</a> ');

// 2. if it is a single package view, include a link to the package
if ( ! is_list_view ) { 
    pageTitle = pageTitle.concat('&gt; <a href="', current_package_url, '">',
                                 '<font face="Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular" color="#000066">',
								 'Message',
							     '</font>',
								 '</a> ');
} 
// 3. add the action you are performing
pageTitle = pageTitle.concat('&gt; ', confirmation_title);
%>
<!-- #EndEditable -->
<link rel="stylesheet" href="<%=tw.httpGateway.getStylesheetPathUrl();%>/verisign.css">
</HEAD>
<BODY aLink=#660033 bgColor="#ffffff" background="<%=imagepathurl;%>/background.gif" leftMargin=0 link=black topMargin=0 vLink=black marginwidth="0" marginheight="0">

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

<!-- Main content starts here -->	<%	 
			// build confirm form url
		var confirm_form_url = "";
        if (  is_list_view ) { 
			if ( is_delete_package ) {
				confirm_form_url = tw.httpGateway.getUrl( "TW_TxnAccDeliveryDeletePackagesConfirm.tpl" ); //AccDeliveryDeletePackagesConfirm
			} else {
				confirm_form_url = tw.httpGateway.getUrl( "TW_TxnAccDeliveryExtendPackagesConfirm.tpl" ); //AccDeliveryExtendPackagesConfirm
			}
				confirm_form_url = tw.httpGateway.appendUrlQueryVariable(	confirm_form_url,
										tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_FOLDER_ID,
										current_folder_id );
				confirm_form_url = tw.httpGateway.appendUrlQueryVariable(	confirm_form_url,
										tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_TABLE_START_INDEX,
										index );
				confirm_form_url = tw.httpGateway.appendUrlQueryVariable(	confirm_form_url,
										tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_SORT_FIELD_TYPE,
										field_type );
				confirm_form_url = tw.httpGateway.appendUrlQueryVariable(	confirm_form_url,
										tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_SORT_FIELD_ORDER,
										is_ascend );	//True
	
		} else {
			if ( is_delete_package ) {
				confirm_form_url = tw.httpGateway.getUrl( "TW_TxnAccDeliveryDeletePackagesConfirm.tpl" ); //AccDeliveryDeletePackagesConfirm
			} else {
				// extend package expiration
				if ( !is_logged_in ) {
					confirm_form_url = tw.httpGateway.getUrl( "TW_TxnAccDeliveryExtendPackageOnPasswordPageConfirm.tpl" ); //AccDeliveryExtendPackageOnPasswordPageConfirm
				} else {
					confirm_form_url = tw.httpGateway.getUrl( "TW_TxnAccDeliveryExtendPackageConfirm.tpl" ); //AccDeliveryExtendPackageConfirm
				}
			}
				confirm_form_url = tw.httpGateway.appendUrlQueryVariable(	confirm_form_url,
										tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_FOLDER_ID,
										current_folder_id );
				confirm_form_url = tw.httpGateway.appendUrlQueryVariable(	confirm_form_url,
										tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_TABLE_START_INDEX,
										index );
				confirm_form_url = tw.httpGateway.appendUrlQueryVariable(	confirm_form_url,
										tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_SORT_FIELD_TYPE,
										field_type );
				confirm_form_url = tw.httpGateway.appendUrlQueryVariable(	confirm_form_url,
										tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_SORT_FIELD_ORDER,
										is_ascend );	//True
				confirm_form_url = tw.httpGateway.appendUrlQueryVariable(	confirm_form_url,
										tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_STOREITEM_ID,
										current_package.id );
		}
      %>
<!-- Delete Confimation content -->
<% if (is_delete_package) { %>


		<FORM name="account_confirm" action="<%=confirm_form_url;%>" method="POST">
		<input type="hidden" name="package_ids" value="<%=package_ids; %>">
		<input type="hidden" name="extend_personal" value="1">
		<input type="hidden" name="extend_recipients" value="2">
		<input type="hidden" name="extend_recipients_unit" value="0">
		<input type="hidden" name="extend_recipients_delay" value="0">

		<input type="hidden" name="no_warning_delete_package" value="OFF">
		<SCRIPT> alert(document.account_confirm.no_warning_delete_package.value);</SCRIPT>

		<TABLE border="<%=table_border_TW_AccConfirmation;%>" cellpadding="0" cellspacing="0">
		  <TR>
		    <TD>
			<b>Delete message(s)?</b><br><br>
				<% if ( num_packages == 1 ) { %>
					You are about to delete 1 message.
				<% } else { %>
					You are about to delete <%=num_packages.toString(); %> messages.
				<% } %>
			<BR>Click Delete to continue.
		    </td>
		  </tr>

		  <tr><td><img src="<%=imagepathurl;%>/dot.gif" height="10"></td></tr>

		  <tr nowrap>
		    <td colspan=3 align="left" height="19">
			<table cellpadding=0 cellspacing=0 border="<%=table_border_TW_AccConfirmation;%>">
			  <tr>
			    <td><img height="19" width="9" src="<%=imagepathurl;%>/buttonPurpleLeft.gif"></td>
				<td bgcolor="#d8d7b8" nowrap><a href="javascript:document.account_confirm.submit()" class="buttonText">
				  <font face="Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular" size="2" color="#000066"><%=delete_or_extend_button;%></font></a></td>
				<td><img height="19" width="9" src="<%=imagepathurl;%>/buttonPurpleRight.gif"></td>
				<td>&nbsp;</td>
				<td><img height="19" width="9" src="<%=imagepathurl;%>/buttonPurpleLeft.gif"></td>
				<td bgcolor="#d8d7b8" nowrap><a href="<%=cancel_button_url;%>" class="buttonText">
				<font face="Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular" size="2" color="#000066">Cancel</font></a></td>
				<td><img height="19" width="9" src="<%=imagepathurl;%>/buttonPurpleRight.gif"></td>
			  </tr>
			</table>
		    </td>
		  </tr>
		</TABLE>
		</FORM>
<% } else { /* All non-Delete Confirmations*/%>



      <table border="<%=table_border_TW_AccConfirmation;%>" cellpadding="0" cellspacing="0" width="600">
        <tr>
          <td colspan=2> <!-- #BeginEditable "EditMainTableContent" -->
		    <table valign="TOP" cellpadding=0 cellspacing=0 border="<%=table_border_TW_AccConfirmation;%>" width="100%">
			  <!-- IME Delivery Header -->  <!-- Delivery Information -->
			  <tr>
			    <td align=center valign=top colspan=3><img border=0 height=5 src="<%=imagepathurl;%>/dot.gif" width=200></td>
			  </tr>
			  <% if ( is_list_view ) { %>
			  <!-- Package List View -->
			  <tr>
			    <td align=left valign=top colspan=3>
				  <table cellpadding=2 cellspacing=1 border="<%=table_border_TW_AccConfirmation;%>" width="100%" bgcolor="#cccccc">
<!-- compose delivery_table_content row by row - Begin --> 				   
     			
                <%=delivery_table_header;%>
                <%
                // determine table data
                var delivery_table_content = "";
                var change_to_storage = 0;
                // output the package table, one row at a time.
				for ( i= 0; i < num_packages; ++i )
				{
					delivery_table_content = "";
					var is_new_package;
					var current_package;
					var current_recipient;	// only for inbound package, should only be used after check it is an inbound package.
					// start the table row.
					delivery_table_content = delivery_table_content.concat( "<tr bgcolor='#ffffff'>" );
					current_package = TW_Package.getPackageById( packages[i].id );
					// check if the inbound package is new.
					if ( packages[i].packageReferenceType == tw.constant.TW_PACKAGE_REFERENCE_TYPE_RECIPIENT ) {
						// inbound package;
						current_recipient = current_package.getRecipientById( packages[i].recipientId );
						// TW_RECIPIENT_STATE_STANDARD_NOTIFICATION_OK || TW_RECIPIENT_STATE_STANDARD_NOTIFICATION_CONFIRMED
						is_new_package = ( current_recipient.state != tw.constant.TW_RECIPIENT_STATE_STANDARD_PICKUP_DOWNLOADED)
										 && (current_recipient.state != tw.constant.TW_RECIPIENT_STATE_STANDARD_PICKUP_CONFIRMED )
										 && (current_recipient.state != tw.constant.TW_RECIPIENT_STATE_STANDARD_PICKUP_LOGIN_OK );
					} else {
						is_new_package = false;
					}
					// THE ORDER HERE MUST MATCH THE ORDER HEADER IS DEFINED
					// output checkbox.
					//delivery_table_content = delivery_table_content.concat ( "<td align='center' bgcolor='#9999CC' >",
					//														 "<input type='checkbox' name='SelCheck",
					//														 i, "' value='",
					//														 packages[i].id, "'>",
					//														 "</td> \n");
					// folder name column
					if ( columns_displayed & tw.constant.TW_SESSION_FIELD_FOLDER ) { // TW_SESSION_FIELD_FOLDER
						var package_folder_obj;
						package_folder_obj = TW_Folder.getFolderById( packages[i].folderId);
						if ( is_new_package ) {
							delivery_table_content = delivery_table_content.concat( "<td align='left'> <b>",
																					"<font size='-1' face = 'Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular' >",
																					escapeHTML(package_folder_obj.name),
																					"</font>",
																					"</b></td>\n" );
						} else {
							delivery_table_content = delivery_table_content.concat( "<td align='left'> ",
																					"<font size='-1' face = 'Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular' >",
																					escapeHTML(package_folder_obj.name),
																					"</font></td>\n" );
						}
					}
					if ( (columns_displayed & tw.constant.TW_SESSION_FIELD_STATUS) && ((current_folder_id == "0" ) || (folder_obj.folderType != tw.constant.TW_FOLDER_TYPE_OUTBOX)) ) {	// TW_SESSION_FIELD_STATUS
						// inbox/personal/findpackage
						if ( packages[i].packageReferenceType == tw.constant.TW_PACKAGE_REFERENCE_TYPE_RECIPIENT ) {
							// inbound package;
							if ( is_new_package ) {
								delivery_table_content = delivery_table_content.concat( "<td align='left' > <b>",
																						"<font size='-1' face = 'Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular' >",
																						"New",
																						"</font></b></td> \n" );
							} else {
								delivery_table_content = delivery_table_content.concat( "<td align='left' >",
																						"<font size='-1' face = 'Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular' >",
																						"Viewed",	
																						"</font></td>\n" );
							}
						} else {
							delivery_table_content = delivery_table_content.concat( "<td align='left' >",
																					"<font size='-1' face = 'Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular' >",
																					"&nbsp;", "</font></td> \n" );
						}
					}
					if ( columns_displayed & tw.constant.TW_SESSION_FIELD_PRIORITY  ) {	// TW_SESSION_FIELD_PRIORITY
						if ( is_new_package ) {
							delivery_table_content = delivery_table_content.concat ( "<td align='left'><b>",
																					 "<font size='-1' face = 'Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular' >" );
						} else {
							delivery_table_content = delivery_table_content.concat ( "<td align='left'>",
																					 "<font size='-1' face = 'Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular' >");
						}
						if ( packages[i].priority == tw.constant.PACKAGE_PRIORITY_BULK ) {
							delivery_table_content = delivery_table_content.concat( "Low" );
						} else {
							if ( packages[i].priority == tw.constant.PACKAGE_PRIORITY_NORMAL ) { // PACKAGE_PRIORITY_NORMAL
								delivery_table_content = delivery_table_content.concat( "Normal" );
							} else {
								if ( packages[i].priority == tw.constant.PACKAGE_PRIORITY_EXPRESS ) { // PACKAGE_PRIORITY_EXPRESS
									delivery_table_content = delivery_table_content.concat( "Urgent" );
								} else {
									delivery_table_content = delivery_table_content.concat( "&nbsp;" );
								}
							}
						}
						if ( is_new_package ) {
							delivery_table_content = delivery_table_content.concat( "</font></b></td>" );
						} else {
							delivery_table_content = delivery_table_content.concat( "</font></td>" );
						}
					}
					if ( columns_displayed & tw.constant.TW_SESSION_FIELD_SENDER ) { //TW_SESSION_FIELD_SENDER
						if ( is_new_package ) {
							delivery_table_content = delivery_table_content.concat ( "<td align='left'><b>",
																					 "<font size='-1' face = 'Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular' >" );
						} else {
							delivery_table_content = delivery_table_content.concat ( "<td align='left'>",
																					 "<font size='-1' face = 'Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular' >"
																					  );
						}
						// show sender name
						if (!((packages[i].senderFirstname ==null) ||(packages[i].senderFirstname == ""))
								|| !((packages[i].senderLastname == null) ||(packages[i].senderLastname == "") ) ) {
							var sender_name = new String;
							sender_name = sender_name.formatPositional( "%1$s %2$s",
														  escapeHTML(packages[i].senderFirstname),
														  escapeHTML(packages[i].senderLastname ) );
							delivery_table_content = delivery_table_content.concat( sender_name );
						} else {
							delivery_table_content = delivery_table_content.concat( escapeHTML(packages[i].senderAddress) );
						}
						if ( is_new_package ) {
							delivery_table_content = delivery_table_content.concat( "</font></b></td>" );
						} else {
							delivery_table_content = delivery_table_content.concat( "</font></td>" );
						}	
					}
					if ( columns_displayed & tw.constant.TW_SESSION_FIELD_SUBJECT ) {
						// build the package_url
						var package_url = tw.httpGateway.getUrl( "TW_TxnAccDeliveryPageEntry.tpl" ); //AccDeliveryPageEntry
						package_url = tw.httpGateway.appendUrlQueryVariable( package_url,
																			tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_FOLDER_ID,
																			current_folder_id );
						package_url = tw.httpGateway.appendUrlQueryVariable( package_url,
																			 tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_STOREITEM_ID,
																			 packages[i].id );
						package_url = tw.httpGateway.appendUrlQueryVariable( package_url,
																			 tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_TABLE_START_INDEX,
																			 index_number+i );	
						if ( current_folder_id == "0" ) {
							// for find package result, we need to code the sort field in url, because it is not saved in any folder.
							package_url = tw.httpGateway.appendUrlQueryVariable( package_url,
																				tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_SORT_FIELD_TYPE,
																				field_type );
							package_url = tw.httpGateway.appendUrlQueryVariable( package_url,
																				tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_SORT_FIELD_ORDER,
																				 is_ascend );    //True
						}
						if ( is_new_package ) {
							delivery_table_content = delivery_table_content.concat( "<td align= 'left'><b>" );
						} else {
							delivery_table_content = delivery_table_content.concat( "<td align= 'left'>" );
						}
						if ( (packages[i].subject == null) || (packages[i].subject.length == 0 )) {
							delivery_table_content = delivery_table_content.concat( "<font size='-1' face = 'Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular' >",
																					"<a href='", package_url, "'>",
																					"(no subject)",
																					"</a></font>" );
						} else {
							delivery_table_content = delivery_table_content.concat( "<font size='-1' face = 'Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular' >",
																					"<a href='", package_url, "'>",
																					escapeHTML(packages[i].subject),
																					"</a></font>" );
						}	
						if ( packages[i].state == tw.constant.PACKAGE_STATE_CANCELLED ) {
							delivery_table_content = delivery_table_content.concat( "<font color='#CC0033' size='-1' face = 'Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular'> (Cancelled)</font>" );
						}
						if ( is_new_package ) {
							delivery_table_content = delivery_table_content.concat( "</b></td> " );
						} else {
							delivery_table_content = delivery_table_content.concat( "</td>" );
						}
					}
					if ( columns_displayed & tw.constant.TW_SESSION_FIELD_RECIPIENTS ) {
						// prepare recipient query strings;	
						var recipient_query="";
						// sort the recipient by category and then by address.
						recipient_query = recipient_query.concat( " TW_IS_RECIPIENT_LIST =0; TW_CATEGORY asc, TW_ADDRESS asc; 0INT, 15INT" );
						var package_recipients = current_package.queryRecipients( recipient_query );
						if ( is_new_package ) {	
							delivery_table_content = delivery_table_content.concat( "<td align = 'left'> <b> <font size='-1' face = 'Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular' > " );
						} else {
							delivery_table_content = delivery_table_content.concat( "<td align = 'left'> <font size='-1' face = 'Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular' >" );
						}
						if ( package_recipients.length > 0 ) {
							if ( packages[i].packageReferenceType == tw.constant.TW_PACKAGE_REFERENCE_TYPE_RECIPIENT ) {
								// inbound package; show the current recipient
								if ( current_recipient.description == tw.constant.SINGLE_RECIPIENT) {
									delivery_table_content = delivery_table_content.concat( escapeHTML(current_recipient.singleRecipient.address));
								} else {
									// for maillist we just show the list name
									delivery_table_content = delivery_table_content.concat( escapeHTML(current_recipient.recipientList.mailList));
								}
							} else {
								if ( package_recipients[0].description == tw.constant.SINGLE_RECIPIENT ) {
									delivery_table_content = delivery_table_content.concat( escapeHTML(package_recipients[0].singleRecipient.address));
								} else {
									// for maillist we just show the list name
									delivery_table_content = delivery_table_content.concat( escapeHTML(package_recipients[0].recipientList.mailList) );
								}
							}
							if (package_recipients.length > 1 ) {
								delivery_table_content = delivery_table_content.concat("..." );
							}
						} else {
							delivery_table_content = delivery_table_content.concat ( "&nbsp;" );
						}
						if ( is_new_package ) {
							delivery_table_content = delivery_table_content.concat( "</font></b></td>" );
						} else {
							delivery_table_content = delivery_table_content.concat( "</font></td>" );
						}
					}
					// show tracking column for outbox
					if ( (columns_displayed & tw.constant.TW_SESSION_FIELD_STATUS ) && (current_folder_id != "0" ) && (folder_obj.folderType == tw.constant.TW_FOLDER_TYPE_OUTBOX)  ) { //
						if ( packages[i].packageReferenceType == tw.constant.TW_PACKAGE_REFERENCE_TYPE_SENDER ) {
							// out bound package;
                            // This portion of code is duplicated from TW_AccDeliveryFolderView.tpl. To be factored!
							var	good_status;	// boolean, indicate whether the tracking status
							var tracking_status;	// tracking status summary string.
							var send_count, notified_count, delivered_count;
							// summarize delivery status. will be reused in other pages also.
							good_status = (packages[i].notifyBadDomainCount == 0 ) &&
										  (packages[i].notifyBadAccountCount == 0 ) &&
										  (packages[i].notifyGiveUpCount == 0 );
							var send_count = Math.min( packages[i].allMediumRecipientCount, 2 );
							delivered_count = Math.min( packages[i].receiveCount, 2 );
							notified_count = Math.min( packages[i].notifyDoneCount, 2 );
							if ( (notified_count ==2) && ( packages[i].allMediumRecipientCount > packages[i].notifyDoneCount ) ) {
								notified_count = 1;
							} /* endif */
							if ( (delivered_count ==2) && (notified_count ==2)
								 && ( packages[i].allMediumRecipientCount > packages[i].allMediumSuccessCount ) ) {
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
							// build tracking url
							var tracking_url = tw.httpGateway.getUrl( "TW_TxnAccDeliveryTracking.tpl" ); //AccDeliveryTracking
							tracking_url = tw.httpGateway.appendUrlQueryVariable(	tracking_url,
																					tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_FOLDER_ID,
																					current_folder_id );
							tracking_url = tw.httpGateway.appendUrlQueryVariable(	tracking_url,	
																					tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_STOREITEM_ID,
																					packages[i].id );
							tracking_url = tw.httpGateway.appendUrlQueryVariable(	tracking_url,
																					tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_TABLE_START_INDEX,
																					index );
							if ( good_status == true ) {
								if ( is_new_package ) {
									delivery_table_content = delivery_table_content.concat ( "<td align='left'><b><font size='-1' face = 'Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular' > ",
																							"<a href='", tracking_url, "'>",
																							tracking_status,
																							"</a></font></b></td>" );
								} else {
									delivery_table_content = delivery_table_content.concat( "<td align='left'> <font size='-1' face = 'Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular' > ",
																							"<a href='", tracking_url, "'>",
																							tracking_status,
																							"</a></font></td>" );
								}
							} else {
								// bad notification status.
								if ( is_new_package ) {
									delivery_table_content = delivery_table_content.concat( "<td align='left' bgcolor='#ffcccc'><b>",
																							"<font size='-1' face = 'Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular' > ",
																							"<a href='", tracking_url, "'>",
																							tracking_status,
																							"</a></font></b></td>" );
								} else {
									delivery_table_content = delivery_table_content.concat( "<td align='left' bgcolor='#ffcccc'>",
																							"<font size='-1' face = 'Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular' > ",
																							"<a href='", tracking_url, "'>",
																							tracking_status,
																							"</a></font></td>" );
								}
							}
						} else {
							// inbound package is the outbox folder. the tracking info should be left empty.
							delivery_table_content = delivery_table_content.concat( "<td align='left' > <font size='-1' face = 'Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular' > ",
																					"&nbsp;", "</font></td>" );
						}
					}
					if ( columns_displayed & tw.constant.TW_SESSION_FIELD_BILLCODE ) {
						if ( (packages[i].billingCode == null) || (packages[i].billingCode =="" ) ) {	
							delivery_table_content = delivery_table_content.concat ( "<td align='left'> &nbsp; </td> " );
						} else {
							if ( is_new_package ) {
								delivery_table_content = delivery_table_content.concat( "<td align='left'> <b>",
																						"<font size='-1' face = 'Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular' > ",
																						escapeHTML(packages[i].billingCode),
																						"</font></b></td>" );
							} else {
								delivery_table_content = delivery_table_content.concat( "<td align='left'>",
																						"<font size='-1' face = 'Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular' > ",
																						escapeHTML(packages[i].billingCode),
																						"</font></td>" );
							}
						}
					}
					if ( columns_displayed & tw.constant.TW_SESSION_FIELD_RECEIVED ) {
						if ( is_new_package ) {	
							delivery_table_content = delivery_table_content.concat( "<td align = 'left'> <b> <font size='-1' face = 'Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular' > " );
						} else {
							delivery_table_content = delivery_table_content.concat( "<td align = 'left'> <font size='-1' face = 'Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular' > " );
						}
						if ( packages[i].packageReferenceType == tw.constant.TW_PACKAGE_REFERENCE_TYPE_RECIPIENT ) {
							// inbound package;
							var receive_time = new Date( current_recipient.stateTime *1000 );
							delivery_table_content = delivery_table_content.concat( receive_time.format( "%m/%d/%Y", tw.session.account.userTimeZoneDelta ) );
						} else {
							delivery_table_content = delivery_table_content.concat( "&nbsp;" );
						}
						if ( is_new_package ) {
							delivery_table_content = delivery_table_content.concat( "</font></b></td>" );
						} else {
							delivery_table_content = delivery_table_content.concat( "</font></td>" );
						}
					}
					// show Sent column
					//if ( columns_displayed & tw.constant.TW_SESSION_FIELD_SEND_DATE ) {
					//	delivery_table_content = delivery_table_content.concat( "<td align='right'><font size='-1' face='Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular'>" );
					//	var sent_time = new Date( packages[i].scheduleTime *1000 );
					//	if ( is_new_package ) {
					//		delivery_table_content = delivery_table_content.concat( "<b>",
					//																escapeHTML(sent_time.format( "%m/%d/%Y", tw.session.account.userTimeZoneDelta )),
					//																"</b>" );
					//	} else {
					//		delivery_table_content = delivery_table_content.concat( escapeHTML(sent_time.format( "%m/%d/%Y", tw.session.account.userTimeZoneDelta ) ));
					//	}
					//	delivery_table_content = delivery_table_content.concat( "</font></td>" );
					//}
					// show Expire column
					if ( columns_displayed & tw.constant.TW_SESSION_FIELD_EXPIRATION ) {
						if ( is_new_package ) {	
							delivery_table_content = delivery_table_content.concat( "<td align='right'><b><font size='-1' face='Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular'>" );
						} else {
							delivery_table_content = delivery_table_content.concat( "<td align='right'><font size='-1' face='Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular'>" );
						}
						if (packages[i].saved == true ) {
							delivery_table_content = delivery_table_content.concat( "Never (Extended)" );
						}  else {
							var current_time = new Date();
							var expire_time = new Date( packages[i].expireTime *1000 );
							if ( ( packages[i].state ==  tw.constant.PACKAGE_STATE_EXPIRED ) || (packages[i].state == tw.constant.PACKAGE_STATE_EXPIRED_AND_STREAMS_DELETED ) || (current_time.getTime() > expire_time.getTime()) ) {
								delivery_table_content = delivery_table_content.concat( "Expired" );
							} else {
								var expiration_url = tw.httpGateway.getUrl( "TW_TxnAccDeliveryFolderViewSavePackage.tpl" ); //AccDeliveryFolderViewSavePackage
								expiration_url = tw.httpGateway.appendUrlQueryVariable( expiration_url,
																					tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_FOLDER_ID,
																					current_folder_id );
								expiration_url = tw.httpGateway.appendUrlQueryVariable( expiration_url,	
																					tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_STOREITEM_ID,
																					packages[i].id );
								expiration_url = tw.httpGateway.appendUrlQueryVariable(	expiration_url,
																					tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_TABLE_START_INDEX,
																					index );
								var timespan_milliseconds;
								timespan_milliseconds = expire_time.getTime() - current_time.getTime();
								var expire_in_days = (timespan_milliseconds/(1000*60*60)+ current_time.getHours())/24;
                                if (tw.session.account.effectiveCapabilities.canChangePackageExpirationDays) {
									delivery_table_content = delivery_table_content.concat ( "<a href='",expiration_url,
																						 "'>",
																						 expire_in_days, " ",
																						 "day(s)", "</a>" );
                                } else {
                                    delivery_table_content = delivery_table_content.concat (
                                        expire_in_days, " ", "day(s)");
								}

							}
						}
						if ( is_new_package ) {
							delivery_table_content = delivery_table_content.concat( "</font></b></td>" );
						} else {
							delivery_table_content = delivery_table_content.concat( "</font></td>" );
						}
					}
					if ( columns_displayed & tw.constant.TW_SESSION_FIELD_FILES ) { 
						var package_file_count = 0;
						var j;
						for ( j= 0; j < current_package.streams.length; ++j ) {
							if ( current_package.streams[j].usage == tw.constant.TW_STREAM_CONTENT ) { 
								package_file_count++;
							}
						}
						if ( is_new_package ) {
							delivery_table_content = delivery_table_content.concat( "<td align='right'><b><font size='-1' face='Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular'> ",
																					package_file_count,
																					"</font></b></td>" );
						} else {
							delivery_table_content = delivery_table_content.concat( "<td align='right'><font size='-1' face='Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular'> ",
																					package_file_count,
																					"</font></td>" );
						}
					}
					if ( columns_displayed & tw.constant.TW_SESSION_FIELD_KBYTE ) { 
						var current_package_size;
						// Should use Math.max()
						if ( packages[i].userContentSize/1024 > 1 ) {
							current_package_size = packages[i].userContentSize/1024;
						} else {
							current_package_size = 1;
						}
						if ( is_new_package ) {
							delivery_table_content = delivery_table_content.concat( "<td align='right'><b><font size='-1' face='Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular'> ",
																					current_package_size,
																					//"&nbsp;KB",
																					"</font></b></td>" );
						} else {
							delivery_table_content = delivery_table_content.concat( "<td align='right'><font size='-1' face='Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular'> ",
																					current_package_size,
																					//"&nbsp;KB",
																					"</font></td>" );
						}
					}
					// close the table row.
					delivery_table_content = delivery_table_content.concat ( "</tr>" );
					tw.write( delivery_table_content );
                    if ( i > 0 && last_expire_time != packages[i].expireTime*1000 ) {
                        same_expire_time = false;
                        if (  last_expire_time < packages[i].expireTime*1000 ) {
                            last_expire_time = packages[i].expireTime*1000;
                        }
                    } else {
                        last_expire_time = packages[i].expireTime*1000;
                    }
                    
                    if (!packages[i].saved) {
                        all_saved = false;
                    }
                    if (!is_sender) {
                        is_sender = packages[i].packageReferenceType == tw.constant.TW_PACKAGE_REFERENCE_TYPE_SENDER;
                    } 
                    change_to_storage += packages[i].userContentSize;
				    if ( change_to_storage > 0 ) {
					    if ( (change_to_storage% 1024) == 0 ) {
                            change_to_storage = change_to_storage/1024;
				    	} else {
                            change_to_storage = change_to_storage/1024 + 1;
					    }
    				} 
                }
              %>
<!-- compose delivery_table_content row by row - End --> 				   
        <%

        var is_package_expired = false;
        if ( !is_delete_package ) {
            // Set values for extend:
            same_expiration_dates = same_expire_time;
        	var current_time = new Date();
            if ( same_expire_time || all_saved ) {
                if ( last_expire_time < current_time.getTime() ) {
                    is_package_expired  = true;
                }
                var user_timezone_delta = tw.session.account.userTimeZoneDelta;
            	var package_expiration_date = new String();
            	var last_expire_date = new Date(last_expire_time);
                package_expiration_date = time_display(last_expire_date);


                if ( all_saved ) {
                    extend_personal_date = "Never (Extended)";
                } else {
                    extend_personal_date = package_expiration_date;
                }
                  var extend_recipients_date = last_expire_date;
                  var extend_recipients_unit = accPreferences.TW_SESSION_PREF_PACKAGE_EXPIRATION_DELAY_UNIT;
                  outobj.extend_recipients_unit		= FormatIdList(aValues,iIds,extend_recipients_unit);
                  expire_in_days = GetAbsoluteDayDifference(current_time, last_expire_date);
                  var extend_recipients_delay = ApiToUiExpirationDelay(expire_in_days, accPreferences.TW_SESSION_PREF_PACKAGE_EXPIRATION_DELAY_UNIT);
                  var extend_recipients_unit_index = extend_recipients_unit.toString();
            } else {
                // different expiration dates
                  var extend_recipients_delay = ApiToUiExpirationDelay(toDays(accPreferences.TW_SESSION_PREF_PACKAGE_DEFAULT_EXPIRE_DELAY), accPreferences.TW_SESSION_PREF_PACKAGE_EXPIRATION_DELAY_UNIT);
                  var extend_recipients_unit = accPreferences.TW_SESSION_PREF_PACKAGE_EXPIRATION_DELAY_UNIT;
                  var extend_recipients_unit_index = extend_recipients_unit.toString();
                  var extend_recipients_date = new Date();
                  extend_recipients_date = new Date (extend_recipients_date.valueOf() + accPreferences.TW_SESSION_PREF_PACKAGE_DEFAULT_EXPIRE_DELAY * 1000);
                  outobj.extend_recipients_unit		= FormatIdList(aValues,iIds,extend_recipients_unit);
            }
            // set default selections
            extend_personal = 0;    // never expire
            extend_recipients = 2; // no change
        } /* end of extend packages */
         %>
                  </table>
				</td>
			  </tr>
			  <tr>
			    <td align=center valign=top colspan=3><img border=0 height=7 src="<%=imagepathurl;%>/dot.gif" width=200></td>
			  </tr>
			  <tr>
			  <%
				// calculate the total storage space and available storage space in KB.
				var max_allocation_space, available_storage_space, used_storage_space ;
				used_storage_space = 0;
				var capabilities = tw.session.account.effectiveCapabilities;
				if ( capabilities.maxDiskAllotment == null ) {
					// the absence means no limitation, use the value for max long
					max_allocation_space =  Number.MAX_INT32;
				} else {
					// the unit is in megabyte for capabilities.TW_MAX_DISK_ALLOTMENT, convert to KB
					max_allocation_space = capabilities.maxDiskAllotment * 1024;
				}
				// we search for all the saved packages.
				var total_package_query = "TW_IS_SAVED = true; ;0INT, ";
				total_package_query = total_package_query.concat(	Number.MAX_UINT32, "INT;",
																	tw.session.account.id,
																	"ID; 1INT; ; ");
				var total_package_usage = TW_Package.queryPackageUsage(tw.session.account, total_package_query);
				used_storage_space = total_package_usage.userContentSize;
				// we need to convert it to KB.
				if ( used_storage_space > 0 ) {
					if ( (used_storage_space% 1024) == 0 ) {
						used_storage_space = used_storage_space/1024;
					} else {
						used_storage_space = used_storage_space/1024 + 1;
					}
				}
				if ( used_storage_space < max_allocation_space ) {
					available_storage_space = max_allocation_space - used_storage_space;
				}
			  %>
			    <td colspan="9" align="right"><font size="-1">Total Storage Allocation: <%=max_allocation_space;%>
				  <img border=0 height=15 src="<%=imagepathurl;%>/dot.gif"  width=20>Available Storage: <%=available_storage_space;%>
				  <%=about_to_delete_or_extend;%> <%=change_to_storage;%> KBytes
				  </font></td>
			  </tr>
			  <% } else { %>
			  <!-- Package Detail View -->
			  <tr>
			    <td colSpan=3>
				  <table border=0 cellpadding=0 cellspacing=0 valign="TOP" align=center>
				    <tr>
					  <td ALIGN="CENTER" width=90>
  				        <% if (!current_package.hasBannerStream( current_package.recipientId )) { %>
						<!--a href="http://www.tumbleweed.com/"><img src="<%=imagepathurl;%>/MDHFinal.gif" border=0></a-->
						<% } else { %>
 				        <img src="<%=tw.httpGateway.getUrl("TW_TxnAccDeliveryBannerUrl.tpl");%>">						<% }  %>
					  </td>
					  <td><img border=0 height=80 src="<%=imagepathurl;%>/dot.gif" width=10></td>
					  <td align=right>
					    <table border=0 cellpadding=1 cellspacing=2 valign="TOP">
						  <tr>
						    <td align=right><font color="#000000" face='Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular' size=-1>
							  <B>Message&nbsp;</B></font></td>
							<td bgcolor='#ffffff' nowrap><font size=-1><a href="<%=current_package_url;%>"><%=package_subject;%></a></font></td>
						  </tr>
						  <tr>
						    <td align=right><font color="#000000" face='Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular' size=-1>
							  <B>From&nbsp;</B></font></td>
							<td bgcolor='#ffffff' nowrap><font size=-1><%=sender;%></font></td>
						  </tr>
						  <% if ((replyto != null ) && (replyto != "")) { %>
						  <tr>
						    <td align=right><font color="#000000" face='Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular' size=-1>
							  <B>Reply To&nbsp;</B></font></td>
							<td bgcolor='#ffffff' nowrap><font size=-1><%=replyto;%></font></td>
						  </tr>
						  <% }  %>
						  <% if (to_recipients != "" ) { %>
						  <tr>
						    <td align=right><font color="#000000" face='Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular' size=-1>
							  <B>To&nbsp;</B></font></td>
							<td bgcolor='#ffffff'><font size=-1><%=to_recipients;%></font></td>
						  </tr>
						  <% }  %> 
						  <% if (cc_recipients != "") { %>
						  <tr>
						    <td align=right><font color="#000000" face='Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular' size=-1>
							  <B>CC&nbsp;</B></font></td>
							<td bgcolor='#ffffff'><font size=-1><%=cc_recipients;%></font></td>
						  </tr>
						  <% }  %> 
						  <% if ((bcc_recipients != "") && is_outbound_package ) { %>
						  <tr>
						    <td align=right><font color="#000000" face='Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular' size=-1>
							  <B>BCC&nbsp;</B></font></td>
							<td bgcolor='#ffffff'><font size=-1><%=bcc_recipients;%></font></td>
						  </tr>
						  <% }  %>
						  <tr>
						    <td align=right><font color="#000000" face='Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular' size=-1>
							  <B>Sent&nbsp;</B></font></td>
							<td bgcolor='#ffffff'><font size=-1><%=sent_time_display;%></font></td>
						  </tr>
						  <tr>
						    <td align=right><font color="#000000" face='Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular' size=-1>
							  <B>Expires&nbsp;</B></font></td>
							<td bgcolor='#ffffff'><font size=-1><%=expire_time_display;%></font></td>
						  </tr>
						  <% if ( is_sender ) { %>
						  <tr>
						    <td align=right><font color="#000000" face='Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular' size=-1>
							  <B>Tracking&nbsp;</B></font></td>
							<% if (good_status) { %>
							<td bgcolor='#ffffff'><a href="<%=tracking_summary_url; %>">
							<font size=-1><%=tracking_status; %>
							  </font></a></td>
							<% } else { %>
							<td bgcolor = '#ffcccc'>
							  <a href="<%=tracking_summary_url; %>">
							  <%=tracking_status; %></a></td>
							<% }  %>
						  </tr>
						  <% }  %>
						</table>
					  </td>
					</tr>
				  </table>
				</td>
			  </tr>
			  <tr>
			    <td align=center  valign=top colspan="2"> <img border=0 height=5 src="<%=imagepathurl;%>/dot.gif" width=200></td>
			  </tr>
          <%	//define delivery_form variables - Begin
				// scripts about
				// get prepaid reply info.
				var  has_prepaid_reply, prepaid_reply_url;
				if ( current_package.recipientId == 0 || current_package.sponsorAccountId == 0 ) {
				  has_prepaid_reply = false;
				} else {
				  has_prepaid_reply = (current_recipient.prepaidReply.howManyGranted > 0) &&
									 (current_recipient.prepaidReply.howManyGranted > current_recipient.prepaidReply.howManyUsed);
				}
				var prev_switch, prev_package_url, next_switch, next_package_url;
				var form_url = "";
				if ( is_logged_in ) {
					// build form url
					form_url = tw.httpGateway.getUrl( "TW_TxnAccDeliveryPage.tpl" ); //AccDeliveryPage
					form_url = tw.httpGateway.appendUrlQueryVariable(	form_url,
											tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_FOLDER_ID,
											current_folder_id );
					form_url = tw.httpGateway.appendUrlQueryVariable(	form_url,
											tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_TABLE_START_INDEX,
											index );
					form_url = tw.httpGateway.appendUrlQueryVariable(	form_url,
											tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_SORT_FIELD_TYPE,
											field_type );
					form_url = tw.httpGateway.appendUrlQueryVariable(	form_url,
											tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_SORT_FIELD_ORDER,
											is_ascend );	//True
					form_url = tw.httpGateway.appendUrlQueryVariable(	form_url,
											tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_STOREITEM_ID,
											current_package.id );
					// build repaid_reply_url
					prepaid_reply_url = tw.httpGateway.getUrl( "TW_TxnAccDeliveryPagePrepaidReply.tpl"); //AccDeliveryPagePrepaidReply
					prepaid_reply_url = tw.httpGateway.appendUrlQueryVariable(	prepaid_reply_url,
												tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_FOLDER_ID,
												current_folder_id );
					prepaid_reply_url = tw.httpGateway.appendUrlQueryVariable(	prepaid_reply_url,
												tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_TABLE_START_INDEX,
												index );
					prepaid_reply_url = tw.httpGateway.appendUrlQueryVariable(	prepaid_reply_url,
												tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_SORT_FIELD_TYPE,
												field_type );
					prepaid_reply_url = tw.httpGateway.appendUrlQueryVariable(	prepaid_reply_url,
												tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_SORT_FIELD_ORDER,
												is_ascend );	//True
					prepaid_reply_url = tw.httpGateway.appendUrlQueryVariable(	prepaid_reply_url,
												tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_STOREITEM_ID,
												current_package.id );
														// if the user logged in from ABP package. we don't know the package position and navigation.
					// if whether_to_show_package_position = "-1", we don't show the navigation information.
					var whether_to_show_package_position = 	tw.request.getQueryString( tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_TABLE_START_INDEX, "-1");
					
					// get package position info.
					var package_position = new String;
					var total_packages = 0;
					if ( current_folder_id == "0" ) {
						if(tw.session.TW_SESSION_PACKAGE_QUERY=="undefined") {
						    whether_to_show_package_position = -1;
                                                } else {
						    total_packages = TW_Package.countQueryPackages(tw.session.account, tw.session.TW_SESSION_PACKAGE_QUERY, true);
						}
					} else {
						total_packages = folder_obj.packageItemCount;
					}
					package_position = package_position.formatPositional( "%1$d of %2$d package(s)",
														index_number+1,
														total_packages);
													
					// build the query, so that we can get the prev/next info.
					var sort_order;
					if ( is_ascend == "1" ) {
						sort_order = ( " asc" );
					} else {
						sort_order = ( " desc" );
					}
					// compose the sort_data;
					var sort_data = "";
					if ( current_folder_id == "0" ) {
						// it is the find package case, we depends on the sort data from
						// the url.
						if ( field_type == tw.constant.TW_SESSION_FIELD_SEND_DATE ) {
							sort_data = sort_data.concat( "TW_SCHEDULE_TIME ", sort_order );
						} else if ( field_type == tw.constant.TW_SESSION_FIELD_SUBJECT ) {
							sort_data = sort_data.concat( "TW_SUBJECT ", sort_order );
						} else if ( field_type == tw.constant.TW_SESSION_FIELD_EXPIRATION ) {
							sort_data = sort_data.concat( "TW_IS_SAVED ", sort_order, ", ",
														  "TW_EXPIRE_TIME", sort_order);
						} else if ( field_type == tw.constant.TW_SESSION_FIELD_SENDER ) {
							sort_data = sort_data.concat( "TW_SENDER_LASTNAME", sort_order, ", ",
														  "TW_SENDER_FIRSTNAME", sort_order, ",",
														  "TW_SENDER_ADDRESS", sort_order );
						} else if ( field_type == tw.constant.TW_SESSION_FIELD_KBYTE ) {
							sort_data = sort_data.concat( "TW_USER_CONTENT_SIZE ", sort_order );
						}
					} else {
						// we retrieve the sort data from the folder.
						sort_data = folder_obj.sortAttributes;
					}
					// compose the query output range
					var query_range;
					if ( index_number > 0 ) {
						query_range = new String( index_number-1) ;
						query_range = query_range.concat("INT ,",
													 index_number+ 2,
													 "INT" );
					} else {
						query_range = index;
						query_range = query_range.concat("INT ,",
														 index_number+ 3,
														 "INT" );
					}
					// compose package query.
					var package_query, temp_package_query;
					var pos;
					package_query ="";
					var base64encoded= false;
					if ( current_folder_id == "0" ) {
						// find package result: get the query string from the session.
						temp_package_query = tw.session.TW_SESSION_PACKAGE_QUERY;
						if ( (temp_package_query != null) && (temp_package_query !="" ) ) {
							// replace the sort data and range.
							pos = temp_package_query.indexOf( ";", 0 );
							if ( pos > 0 ) {
								package_query = temp_package_query.substr( 0, pos );
								package_query = package_query.concat(	"; ", sort_data,"; ", query_range,"; " );
							}
							// append the reset of the query to package_query
							// skip the old sort data.
							pos = temp_package_query.indexOf(";", pos+1 );
							if ( pos > 0 ) {
								// skip the package range
								pos = temp_package_query.indexOf(";", pos+1 );
								if ( pos > 0 ) {
									package_query = package_query.concat( temp_package_query.substr( pos+1, (temp_package_query.length-pos-1)));
								}
							}
							base64encoded=true;
						}
					} else {
						package_query = "(TW_USAGE = 'TW_DELIVERY' AND TW_STATE != 0INT AND TW_FOLDER_ID = ";
						package_query = package_query.concat( folder_obj.id,
															  "ID) ;",
															  sort_data, "; ",
															  query_range, "; ",
															  tw.session.account.id,
															  "ID ; 1INT ; ; " );
					}
					if ( package_query !="" ) {
						var prev_next_packages = TW_Package.queryPackages(tw.session.account, package_query, base64encoded);
						// build prev and next navigation button
						if ( prev_next_packages.length == 3 ) {
							prev_package_url = tw.httpGateway.getUrl( "TW_TxnAccDeliveryPageEntry.tpl" ); //AccDeliveryPageEntry
							prev_package_url = tw.httpGateway.appendUrlQueryVariable( prev_package_url,
														tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_FOLDER_ID,
														current_folder_id );
							next_switch =true;
							next_package_url = tw.httpGateway.getUrl( "TW_TxnAccDeliveryPageEntry.tpl" ); //AccDeliveryPageEntry
							next_package_url = tw.httpGateway.appendUrlQueryVariable( next_package_url,
														tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_FOLDER_ID,
														current_folder_id );
							if ( index_number == 0 ) {
								prev_switch = false;
								next_package_url = tw.httpGateway.appendUrlQueryVariable( next_package_url,
															tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_STOREITEM_ID,
															 prev_next_packages[1].id );
							} else {
								prev_switch = true;
								prev_package_url = tw.httpGateway.appendUrlQueryVariable( prev_package_url,
															tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_STOREITEM_ID,
															 prev_next_packages[0].id );
								prev_package_url = tw.httpGateway.appendUrlQueryVariable( prev_package_url,
															tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_TABLE_START_INDEX,
															 index_number-1 );
								next_package_url = tw.httpGateway.appendUrlQueryVariable( next_package_url,
															tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_STOREITEM_ID,
															 prev_next_packages[2].id );
							}
							next_package_url = tw.httpGateway.appendUrlQueryVariable( next_package_url,
														tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_TABLE_START_INDEX,
														 index_number+1 );
							if ( current_folder_id == "0" ) {
								prev_package_url = tw.httpGateway.appendUrlQueryVariable( prev_package_url,
															tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_SORT_FIELD_TYPE,
															field_type );
								prev_package_url = tw.httpGateway.appendUrlQueryVariable( prev_package_url,
															tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_SORT_FIELD_ORDER,
															is_ascend );	
								next_package_url = tw.httpGateway.appendUrlQueryVariable( next_package_url,
															tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_SORT_FIELD_TYPE,
															field_type );
								next_package_url = tw.httpGateway.appendUrlQueryVariable( next_package_url,
															tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_SORT_FIELD_ORDER,
															is_ascend );
							}
						} else {
							if ( prev_next_packages.length == 2 ) {
								if ( index_number == 0 ) {
									prev_switch = false;
									next_switch = true;
									next_package_url = tw.httpGateway.getUrl( "TW_TxnAccDeliveryPageEntry.tpl" ); //AccDeliveryPageEntry
									next_package_url = tw.httpGateway.appendUrlQueryVariable( next_package_url,
																tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_FOLDER_ID,
																current_folder_id );
									next_package_url = tw.httpGateway.appendUrlQueryVariable( next_package_url,
																tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_STOREITEM_ID,
																 prev_next_packages[1].id );
									next_package_url = tw.httpGateway.appendUrlQueryVariable( next_package_url,
																tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_TABLE_START_INDEX,
																 index_number+1 );
									if ( current_folder_id =="0" ) {
										next_package_url = tw.httpGateway.appendUrlQueryVariable( next_package_url,
																	tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_SORT_FIELD_TYPE,
																	field_type );
										next_package_url = tw.httpGateway.appendUrlQueryVariable( next_package_url,
																	tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_SORT_FIELD_ORDER,
																	is_ascend );	//True
									}
								} else {
									prev_switch = true;
									prev_package_url = tw.httpGateway.getUrl( "TW_TxnAccDeliveryPageEntry.tpl" ); //AccDeliveryPageEntry
									prev_package_url = tw.httpGateway.appendUrlQueryVariable( prev_package_url,
																tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_FOLDER_ID,
																current_folder_id );
									prev_package_url = tw.httpGateway.appendUrlQueryVariable( prev_package_url,
																tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_STOREITEM_ID,
																 prev_next_packages[0].id );
									prev_package_url = tw.httpGateway.appendUrlQueryVariable( prev_package_url,
																tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_TABLE_START_INDEX,
																 index_number-1 );
									if ( current_folder_id =="0" ) {
										prev_package_url = tw.httpGateway.appendUrlQueryVariable( prev_package_url,
																	tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_SORT_FIELD_TYPE,
																	field_type );
										prev_package_url = tw.httpGateway.appendUrlQueryVariable( prev_package_url,
																	tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_SORT_FIELD_ORDER,
																	is_ascend );	//True
									}
									next_switch = false;
								}
							} else {
								prev_switch= false;
								next_switch = false;
							}
						}
					}
				} else {
					// not logged in case.
					prepaid_reply_url = tw.httpGateway.getUrl( "TW_TxnAccDeliveryPagePrepaidReply.tpl"); //AccDeliveryPagePrepaidReply
					prepaid_reply_url = tw.httpGateway.appendUrlQueryVariable(	prepaid_reply_url,
													tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_STOREITEM_ID,
													current_package.id );
				}
				
				%>
			  
			  <!-- Buttons for next, prev, reply, etc -->
			  <form name= "delivery_form" action="<%=form_url;%>" method="POST">
			  <input type="hidden" name="submit_action" value="">
			  <tr nowrap>
			    <td align=center>
				  <table border="<%=table_border_TW_AccConfirmation;%>" cellpadding="0" cellspacing="0">
				    <tr>
					  <% if ( is_logged_in ) { %>
					  <!-- Were logged in; show the reply & forward buttons -->
					  <!-- <td><img height="19" width="9" src="<%=imagepathurl;%>/buttonGreyLeft.gif"></td>
					  <td bgcolor="#d8d7b8" nowrap><a href="javascript:SubmitAction(document.delivery_form, document.delivery_form.submit_action, 'reply')" class="buttonText">
					    <font face="Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular" size="2" color="#000066">Reply</font></a></td>
					  <td><img height="19" width="9" src="<%=imagepathurl;%>/buttonGreyRight.gif"></td>
					  <td><img src="<%=imagepathurl;%>/dot.gif" height="10" width="10"></td>
					
					  <td><img height="19" width="9" src="<%=imagepathurl;%>/buttonGreyLeft.gif"></td>
					  <td bgcolor="#d8d7b8" nowrap><a href="javascript:SubmitAction(document.delivery_form, document.delivery_form.submit_action, 'reply_all')" class="buttonText"> 
					    <font face="Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular" size="2" color="#000066">Reply to All</font></a></td>
					  <td><img height="19" width="9" src="<%=imagepathurl;%>/buttonGreyRight.gif"></td>
					
					  <% if ( has_prepaid_reply ) { %>
					  <td><img src="<%=imagepathurl;%>/dot.gif" height="10" width="10"></td>
					  <td><img height="19" width="9" src="<%=imagepathurl;%>/buttonGreyLeft.gif"></td>
					  <td bgcolor="#d8d7b8" nowrap><a href="<%=prepaid_reply_url;%>" class="buttonText">
					    <font face="Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular" size="2" color="#000066">Free Reply</font></a></td>
					  <td><img height="19" width="9" src="<%=imagepathurl;%>/buttonGreyRight.gif"></td>
					  <% }  %>
					
					  <td><img src="<%=imagepathurl;%>/dot.gif" height="10" width="10"></td>
					  <td><img height="19" width="9" src="<%=imagepathurl;%>/buttonGreyLeft.gif"></td>
					  <td bgcolor="#d8d7b8" nowrap><a href="javascript:SubmitAction(document.delivery_form, document.delivery_form.submit_action, 'forward')" class="buttonText">
					  <font face="Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular" size="2" color="#000066">Forward</font></a></td>
					  <td><img height="19" width="9" src="<%=imagepathurl;%>/buttonGreyRight.gif"></td>
					  --> <% } %> <!-- end  of ! is_before_password i.e. is_logged_in -->
					</tr>
				  </table>
				</td>
				<% if ( whether_to_show_package_position != "-1" ) { %>
				<td><img border=0 height=10 src="<%=imagepathurl;%>/dot.gif" width=20></td>
				<td>
				  <table border="<%=table_border_TW_AccConfirmation;%>" cellpadding="0" cellspacing="0">
				    <tr>
					  <% if ( prev_switch ) { %>
					  <td><a href="<%=prev_package_url;%>" class="buttonText">
					    <img src="<%=imagepathurl;%>/arrowLeft.gif" width="25" height="21" border="0"></a></td>
					  <% }  %>
					  <td><span><font size=-1><%=package_position;%></font></span></td>
					  <% if ( next_switch ) { %>
					  <td><a href="<%=next_package_url;%>" class="buttonText">
					    <img src="<%=imagepathurl;%>/arrowRight.gif" width="25" height="21" border="0"></a></td>
					  <% }  %>
					</tr>
				  </table>
				</td>
				<% }  %>
			  </tr>
			  <tr>
				<td colspan=3><img src="<%=imagepathurl;%>/dot.gif" height="4" width="100"></td>
			  </tr>
<!--
			  <tr>
				<td colspan=3>
				  <table border="<%=table_border_TW_AccConfirmation;%>" cellpadding="0" cellspacing="0" align=center>
				    <tr>
					  <td>
					    <table border="<%=table_border_TW_AccConfirmation;%>" cellpadding="0" cellspacing="0">
						  <tr>
						    <td><img height="19" width="9" src="<%=imagepathurl;%>/buttonGreyLeft.gif"></td>
							<td bgcolor="#d8d7b8" nowrap><a href="javascript:SubmitAction(document.delivery_form, document.delivery_form.submit_action, 'delete')" class="buttonText">
							  <font face="Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular" size="2" color="#000066">Delete</font></a></td>
							<td><img height="19" width="9" src="<%=imagepathurl;%>/buttonGreyRight.gif"></td>
							<td><img src="<%=imagepathurl;%>/dot.gif" height="10" width="10"></td>
							<td><img height="19" width="9" src="<%=imagepathurl;%>/buttonGreyLeft.gif"></td>
							<td bgcolor="#d8d7b8" nowrap><a href="javascript:SubmitAction(document.delivery_form, document.delivery_form.submit_action, 'extend_expiration')" class="buttonText">
							  <font face="Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular" size="2" color="#000066">Extend Expiration</font></a></td>
							<td><img height="19" width="9" src="<%=imagepathurl;%>/buttonGreyRight.gif"></td>
							<td><img src="<%=imagepathurl;%>/dot.gif" height="10" width="10"></td>
							<td><img height="19" width="9" src="<%=imagepathurl;%>/buttonGreyLeft.gif"></td>
							<td bgcolor="#d8d7b8" nowrap><a href="javascript:SubmitAction(document.delivery_form, document.delivery_form.submit_action, 'move_to')" class="buttonText">
							  <font face="Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular" size="2" color="#000066">Move to</font></a>&nbsp;&nbsp;</td>
						  </tr>
						</table>
					  </td>
					  <td>
					    <select name="folder_selection" onChange="TidySel(document.delivery_form.folder_selection)">
						  <option value="" selected>(Select a Folder)</option>
						  <option value="" >-</option>
						  <%=custom_folders;%>
						  <option value="" >-</option>
						  <option value="0">New Folder...</option>
						</select>
					  </td>
					</tr>
				  </table>
				</td>
			  </tr>
-->
			  </form>
			  <% 
              } /* end of if ( is list ) else */ %>
			  <tr>
			    <td colspan=3><img border=0 height=10 src="<%=imagepathurl;%>/dot.gif" width=200></td>
			  </tr>
			  <tr><!-- Thin line spacer -->
			    <td colspan=3 bgcolor="#999999"><img border=0 height=2 src="<%=imagepathurl;%>/dot.gif" width=200></td>
			  </tr>	
			  <tr>
			    <td colspan=3><img border=0 height=10 src="<%=imagepathurl;%>/dot.gif" width=200></td>
			  </tr>
			  <!-- Message Section -->

 			  <form name="account_confirm" action="<%=confirm_form_url;%>" method="POST">
			  <input type="hidden" name="package_ids" value="<%=package_ids; %>">

			  <tr>
			    <td colspan=3>
				  <font color='#000000' face='Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular'>
				  <b><%=confirmation_header;%></b></font></td>
			  </tr>
			  <tr>
			    <td colspan=3><img border=0 height=15 src="<%=imagepathurl;%>/dot.gif" width=200></td>
			  </tr>
			  <% if ( is_delete_package ) { %>
			  <tr>
			    <td colspan=3>
				<% if ( num_packages == 1 ) { %>
				You are about to delete 1 message.
				<% } else { %>
				You are about to delete <%=num_packages.toString(); %> messages.
				<% } %>
				</td>
			  </tr>
			  <tr>
			    <td colspan=3><img border=0 height=15  src="<%=imagepathurl;%>/dot.gif" width=200></td>
			  </tr>
			  <tr>
			    <td colspan=3>You will no longer have access to them, but other people's access will not be affected.</td>
			  </tr>
			  <% } else { /* extend package */ %>
			  <tr>
			    <td colspan=3>
				  <% if ( num_packages == 1 ) { %>
				  You are about to extend the expiration of  1 message.
				  <% } else { %>
				  You are about to extend the expiration of  <%=num_packages.toString(); %> messages.
				  <% } %>
				</td>
			  </tr>	
			  <% if ( is_sender ) { %>
			  <tr>
			    <td colspan=3><img border=0 height=15 src="<%=imagepathurl;%>/dot.gif" width=200></td>
			  </tr>
			  <tr>
			    <td colspan=3>
				  <% if ( num_packages == 1 ) { %>
				  Because you sent this message, you may extend the expiration of your personal copy and for each of the recipients.
				  <% } else { %>
				  Because you sent these messages, you may extend the expiration of your personal copies and for each of the recipients.
				  <% } %>
				</td>
			  </tr>
			  <% } %>
			  <% } /* end of extend package */ %>
			  <tr>
			    <td colspan=3><img border=0 height=15 src="<%=imagepathurl;%>/dot.gif" width=200></td>
			  </tr>
			  <tr>
			    <td colspan=3 class="aside">
				  <table border=0 cellpadding=1 cellspacing=2 valign="TOP" width="100%">
				    <% if ( ! is_delete_package ) { %>
					<!-- Extend Expiration of Personal Copy -->
					<tr>
					  <td align="right" valign="top" nowrap>
					    <font color="#000000" face="Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular" size="-1">
						<b>Your Personal Copy</b></font></td>
					</tr>
					<tr>
					  <td colspan=3><img border=0 height=5 src="<%=imagepathurl;%>/dot.gif" width=200></td>
					</tr>
					<tr>
					  <td align="right" valign="top" nowrap>
					    <font size=-1 color='#000000' face='Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular'>
						<b>Current Expiration:</b></font></td>
					  <td align="left" nowrap>
                        <% if ( extend_personal_date.length == 0 ) { %>
						<% if (!same_expiration_dates) { %>	
							Multiple dates.
						<% } else { %>
							<%=expire_time_display; %>
						<% } %>
					    <% } else { %>
						<%=extend_personal_date; %>
					    <% }  %>
					  </td>
					</tr>
					<tr>
					  <td colspan=3><img border=0 height=5 src="<%=imagepathurl;%>/dot.gif" width=200></td>
					</tr>
					<tr>
					  <td align="right" valign="top" nowrap>
					    <font size=-1 color='#000000' face='Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular'>
						<b>New Expiration:</b> </font></td>
					  <td align="left" valign="top" nowrap>
                        <%
                        var extend_personal_check_0 = "";
                        var extend_personal_check_1 = "";
                        var extend_personal_check_2 = "";
                        if ( extend_personal == 0 )
                        {
                        extend_personal_check_0 = "CHECKED";
                        } else if (extend_personal == 1)
                        {
                        extend_personal_check_1 = "CHECKED";
                        } else if (extend_personal == 2)
                        {
                        extend_personal_check_2 = "CHECKED";
                        }
                        %>
					    
                        <input type="radio" name="extend_personal" value="0" <%=extend_personal_check_0;%>>
							Never<br>
						<input type="radio" name="extend_personal" value="1" <%=extend_personal_check_1;%>>
						No Change<br>
						<input type="radio" name="extend_personal" value="2" <%=extend_personal_check_2;%>>
						Use expiration set by sender (free):<br>
						<% if ( same_expiration_dates) { %>
						<%=package_expiration_date; %><br>
						<% } else { %>
						Multiple dates.
						<% } %>
						<% if ( is_package_expired )  { %>
						<% if ( num_packages == 1 ) { %>
						Warning: Message is past expiration and will be deleted.
						<% } else { %>
						Warning: Messages past expiration set by the sender will be deleted.
						<% } %>
						<% } %>
					  </td>
					</tr>
					<% if ( is_sender ) { %>
					<tr>
					  <td colspan=3><img border=0 height=15 src="<%=imagepathurl;%>/dot.gif" width=200></td>
					</tr>
					<tr>
					  <td align=right valign="top" nowrap>
						<font color="#000000" face="Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular" size="-1">
						<b>For Each Recipient</b></font></td>
					</tr>
					<tr>
					  <td colspan=3><img border=0 height=5 src="<%=imagepathurl;%>/dot.gif" width=200></td>
					</tr>
					<tr>
					  <td align="right" valign="top" nowrap>
					    <font size=-1 color='#000000' face='Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular'>
						<b>Current Expiration:</b></font></td>
					  <td align="left" nowrap>
						<% if (!same_expiration_dates) { %>	
							Multiple dates.
						<% } else { %>
							<%=package_expiration_date; %>
						<% } %>
					   </td>
					</tr>
					<tr>
					  <td align="right" valign="top" nowrap>
					    <font size=-1 color='#000000' face='Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular'>
						<b>Max Expiration:</b></font></td>
					  <td align="left" nowrap>
					  <%
                        var max_expire_time;
                        var max_expire_time_display;
                        var cur_time = new Date();
                        if (current_package.scheduleTime == null || typeof(current_package.scheduleTime) == "undefined") {
                            max_expire_time = cur_time;
                        } else {
                            max_expire_time = current_package.scheduleTime;
                        }

                        var max_expire_days = tw.session.account.effectiveCapabilities.maxPackageExpireDays;
                        if (max_expire_days != null) {
                            max_expire_time = new Date(max_expire_time.getTime() + max_expire_days*3600*24*1000);
                            if (max_expire_time_display == null || max_expire_time_display == "") {
                                max_expire_time_display = time_display(max_expire_time);
                            }
                        } else {
                            max_expire_time_display = "Never (Extended)";
                        }
					  %>
						<%=max_expire_time_display; %>
					   </td>
					</tr>
					<tr>
					  <td align="right" valign="top" nowrap>
					    <font size=-1 color='#000000' face='Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular'>
						<b>New Expiration:</b></font></td>
					  <td align="left" valign="top" nowrap>
                        <%
                        var extend_recipients_check_0 = "";
                        var extend_recipients_check_1 = "";
                        var extend_recipients_check_2 = "";
                        if ( extend_recipients == 0 )
                        {
                        extend_recipients_check_0 = "CHECKED";
                        } else if (extend_recipients == 1)
                        {
                        extend_recipients_check_1 = "CHECKED";
                        } else if (extend_recipients == 2)
                        {
                        extend_recipients_check_2 = "CHECKED";
                        }
                        %>
                        <input type="radio" name="extend_recipients" value="0" <%=extend_recipients_check_0;%>>
						In 
						<input type="text" maxlength=256 name="extend_recipients_delay" size=2 value="<%=extend_recipients_delay;%>">
						<select name="extend_recipients_unit" size="1"><%=outobj.extend_recipients_unit;%></select><br>
						<input type="radio" name="extend_recipients" value="1" <%=extend_recipients_check_1;%>>
						On <input type="text" maxlength=256 name="extend_recipients_date_month" size="2" value="<%=extend_recipients_date.format('%m', tw.session.account.userTimeZoneDelta);%>"> / <input type="text" maxlength=256 name="extend_recipients_date_day" size="2" value="<%=extend_recipients_date.format('%d', tw.session.account.userTimeZoneDelta);%>"> / <input type="text" maxlength=256 name="extend_recipients_date_year" size="5" value="<%=extend_recipients_date.format('%Y', tw.session.account.userTimeZoneDelta);%>">	<br>
						<input type="radio" name="extend_recipients" value="2" <%=extend_recipients_check_2;%>>
						No Change<br>
					  </td>
					</tr>
					<% } %>
					<% } else {  /* delete package */ %>
					<!-- Delete Package Warning Checkbox -->
					<tr>
					  <td colspan=3 nowrap><input type="checkbox" name="no_warning_delete_package" value="ON">
					    Do not warn me when deleting messages.</td>
					</tr>
					<% } %>
					
					<!-- Set hidden input varibles that were not used in various areas above -->
					<% if ( !is_sender || is_delete_package ) { %>
					<!-- User is not sender of package; add hidden inputs for extend_recipients; set extend to "no change" -->
					<input type="hidden" name="extend_recipients" value="2">
					<input type="hidden" name="extend_recipients_unit" value="0">
					<input type="hidden" name="extend_recipients_delay" value="0">
					<% } %>
					<% if ( is_delete_package ) { %>
					<!-- add hidden inputs for extending personal packages -->
					<input type="hidden" name="extend_personal" value="1">
					<% } %>
					<tr>
					  <td colspan=3><img border=0 height=15 src="<%=imagepathurl;%>/dot.gif" width=200></td>
					</tr>
					<tr>
					  <td colspan=3 align="center" height="19">
					    <table cellpadding=0 cellspacing=0 border="<%=table_border_TW_AccConfirmation;%>">
						  <tr>
						    <td><img height="19" width="9" src="<%=imagepathurl;%>/buttonPurpleLeft.gif"></td>
							<td bgcolor="#d8d7b8" nowrap><a href="javascript:document.account_confirm.submit()" class="buttonText">
							  <font face="Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular" size="2" color="#000066"><%=delete_or_extend_button;%></font></a></td>
							<td><img height="19" width="9" src="<%=imagepathurl;%>/buttonPurpleRight.gif"></td>
							<td>&nbsp;</td>
							<td><img height="19" width="9" src="<%=imagepathurl;%>/buttonPurpleLeft.gif"></td>
							<td bgcolor="#d8d7b8" nowrap><a href="<%=cancel_button_url;%>" class="buttonText">
							<font face="Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular" size="2" color="#000066">Cancel</font></a></td>
							<td><img height="19" width="9" src="<%=imagepathurl;%>/buttonPurpleRight.gif"></td>
						  </tr>
						</table>
					  </td>
					</tr>
				  </table>
				</td>
			  </tr>
			  </form>
			</table>
            <!-- #EndEditable --> </td>
        </tr>
      </table>
<% } %> 

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
<!-- #EndTemplate -->
</HTML>
