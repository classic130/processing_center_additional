<!-- #BeginEditable "EditTumbleweedFileName" --> <!-- File name: TW_AccDeliveryPageButtons.tpl -->
<SCRIPT language="Javascript">
<!--

function TidySel(selObj) {
  var selVal = selObj.options[selObj.selectedIndex].value;
  if (!selVal) {
    selObj.selectedIndex = 0;
  }
}
//-->
</SCRIPT>

<%
// Missing vars
//var imagepathurl = tw.httpGateway.getImgPathUrl();
//var current_delivery = tw.session.currentDelivery;
//var current_package = TW_Package.getPackageById( current_delivery.packageId);
//var is_logged_in = tw.session.isLoggedIn;

/* Get Current Folder Id , first check the HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_DESTINATION_FOLDER_ID  */
//var current_folder_id = tw.request.getQueryString( "dfi", "0" );
//if ( current_folder_id == "0" ) {
//    current_folder_id = tw.request.getQueryString( tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_FOLDER_ID, "0" );
//}

//var field_type = tw.request.getQueryString(  tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_SORT_FIELD_TYPE,
//                                            "-1" );
//var is_ascend = tw.request.getQueryString(  tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_SORT_FIELD_ORDER,
//                                            default_sort_order ); /* false; */

/* get the index of the package in the folder */
//var index = tw.request.getQueryString(  tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_TABLE_START_INDEX, "0");

// convert index to number
//var index_number = new Number( index );

//var folder_obj
//if ( current_folder_id !="0" ) {
//    folder_obj = TW_Folder.getFolderById( new TW_ID( current_folder_id ));
//}

	// scripts about
	
	// get repaid reply info.
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
		form_url = tw.httpGateway.getUrl('TW_TxnAccDeliveryPage.tpl'); //AccDeliveryPage
		form_url = tw.httpGateway.appendUrlQueryVariable(    form_url,
								tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_FOLDER_ID,
								current_folder_id );
		form_url = tw.httpGateway.appendUrlQueryVariable(    form_url,
								tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_TABLE_START_INDEX,
								index );
		form_url = tw.httpGateway.appendUrlQueryVariable(    form_url,
								tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_SORT_FIELD_TYPE,
								field_type );
		form_url = tw.httpGateway.appendUrlQueryVariable(    form_url,
								tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_SORT_FIELD_ORDER,
								is_ascend );    //True
		form_url = tw.httpGateway.appendUrlQueryVariable(    form_url,
								tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_STOREITEM_ID,
								current_package.id );
	
	
		// build repaid_reply_url
		prepaid_reply_url = tw.httpGateway.getUrl('TW_TxnAccDeliveryPagePrepaidReply.tpl'); //AccDeliveryPagePrepaidReply
	
		prepaid_reply_url = tw.httpGateway.appendUrlQueryVariable(    prepaid_reply_url,
									tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_FOLDER_ID,
									current_folder_id );
		prepaid_reply_url = tw.httpGateway.appendUrlQueryVariable(    prepaid_reply_url,
									tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_TABLE_START_INDEX,
									index );
		prepaid_reply_url = tw.httpGateway.appendUrlQueryVariable(    prepaid_reply_url,
									tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_SORT_FIELD_TYPE,
									field_type );
		prepaid_reply_url = tw.httpGateway.appendUrlQueryVariable(    prepaid_reply_url,
									tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_SORT_FIELD_ORDER,
									is_ascend );    //True
		prepaid_reply_url = tw.httpGateway.appendUrlQueryVariable(    prepaid_reply_url,
									tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_STOREITEM_ID,
									current_package.id );
									
		// if the user logged in from ABP package. we don't know the package position and navigation.
		// if whether_to_show_package_position = "-1", we don't show the navigation information.
		var whether_to_show_package_position = tw.request.getQueryString( tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_TABLE_START_INDEX, "-1");
	
		// get package position info.
		var package_position = new String;
		var total_packages;
		if ( current_folder_id == "0" &&  whether_to_show_package_position != "-1") {
			total_packages = tw.session.account.countQueryPackages(tw.session.TW_SESSION_PACKAGE_QUERY, true);
		} else {
			total_packages = folder_obj.packageItemCount;
		}
		if( whether_to_show_package_position != "-1") {
			package_position = package_position.formatPositional( "%1$d of %2$d package(s)",
											index_number+1,
											total_packages);
		}
	
	
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
					package_query = package_query.concat(    "; ", sort_data,"; ", query_range,"; " );
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
			var prev_next_packages = tw.session.account.queryPackages ( package_query, base64encoded );
	
			// build prev and next navigation button
			if ( prev_next_packages.length == 3 ) {
	
				prev_package_url = tw.httpGateway.getUrl('TW_TxnAccDeliveryPageEntry.tpl'); //AccDeliveryPageEntry
				prev_package_url = tw.httpGateway.appendUrlQueryVariable( prev_package_url,
											tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_FOLDER_ID,
											current_folder_id );
				next_switch =true;
				next_package_url = tw.httpGateway.getUrl('TW_TxnAccDeliveryPageEntry.tpl'); //AccDeliveryPageEntry
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
						next_package_url = tw.httpGateway.getUrl('TW_TxnAccDeliveryPageEntry.tpl'); //AccDeliveryPageEntry
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
														is_ascend );    //True
						}
	
					} else {
						prev_switch = true;
	
						prev_package_url = tw.httpGateway.getUrl('TW_TxnAccDeliveryPageEntry.tpl'); //AccDeliveryPageEntry
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
														is_ascend );    //True
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
		prepaid_reply_url = tw.httpGateway.getUrl('TW_TxnAccDeliveryPagePrepaidReply.tpl'); //AccDeliveryPagePrepaidReply
		prepaid_reply_url = tw.httpGateway.appendUrlQueryVariable(    prepaid_reply_url,
										tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_STOREITEM_ID,
										current_package.id );
	}
	
	var package_message, save_message_url;
	var package_streams = current_package.streams;
	var has_pdf_files = false;
	for ( i = 0; i < package_streams.length; ++i )
	{
		if ( (!has_pdf_files) && (package_streams[i].mimeType =="application/pdf" ) ) {
			has_pdf_files = true;
			break;
		}
	}
	
	package_message = "";
	var number_of_files = 0;
	for ( i = 0; i < package_streams.length; ++i ) {
		if ( package_streams[i].usage == tw.constant.TW_STREAM_CONTENT_COVER ) {
			if ( tw.session.TW_HTTPGATEWAY_SESSION_DOCUMENT_BASED_PASSWORD == "undefined" ) {
				package_message = current_package.readStream( current_package.recipientId,
										package_streams[i].id,
										package_streams[i].usage, "" );
	
			} else {
				package_message = current_package.readStream( current_package.recipientId,
										package_streams[i].id,
										package_streams[i].usage,
										tw.session.TW_HTTPGATEWAY_SESSION_DOCUMENT_BASED_PASSWORD );
			}
		}
		if ( package_streams[i].usage == tw.constant.TW_STREAM_CONTENT ) {
			++number_of_files;
		}
	}    
	
	// escape the html
	package_message = escapeHTML( package_message, true );
	
	// build save_message_url;
	save_message_url = tw.httpGateway.getUrl('TW_TxnAccDeliveryPageSaveMessage.tpl'); // AccDeliveryPageSaveMessage
	
	var download_file_name = escapeHTML( "delivery_message" );
	
	// MassageFileNameForTextDownload
	if ( (tw.request.userAgentVendor != "microsoft" ) ||
		 (tw.request.userAgentMajorVersion < 4 ) ) {
		 // we don't want extension for MSIE 4.0 and above, because it will try to open it up in IE.
		 download_file_name = download_file_name.concat( ".txt" );
	}
	save_message_url = tw.httpGateway.appendUrlQueryVariable( save_message_url,
								tw.constant.HTTP_GATEWAY_URL_VARIABLE_DOWNLOAD_EXTENSION,
								  download_file_name );
	
	var save_selected_file_url, virtual_base_url;
	virtual_base_url = tw.server.getConfigParameter( "TW_VIRTUAL_URL" );
	
	save_message_url = virtual_base_url;
	save_selected_file_url = virtual_base_url;
	var len = virtual_base_url.length;
	
	var selected_file_name = escapeHTML( "selected_files.zip" );
	
	if ( (len >0 ) && (virtual_base_url.substr( len-1, 1 ) == "/") ) {
		save_message_url = save_message_url.concat( download_file_name, "?" );
		save_selected_file_url = save_selected_file_url.concat( selected_file_name , "?" );
	} else {
		save_message_url = save_message_url.concat("/", download_file_name, "?" );
		save_selected_file_url = save_selected_file_url.concat( "/", "selected_files.zip" , "?" );
	}
	
	save_message_url = tw.httpGateway.appendUrlQueryVariable(    save_message_url,
								tw.constant.HTTP_GATEWAY_URL_VARIABLE_SESSION_TYPE,
								tw.request.getQueryString( "s", "ac" )
								);
	save_message_url = tw.httpGateway.appendUrlQueryVariable(    save_message_url,
								tw.constant.HTTP_GATEWAY_URL_VARIABLE_TRANSACTION_TYPE,
								"TW_TxnAccDeliveryPageSaveMessage.tpl" //
								);
	save_message_url = tw.httpGateway.appendUrlQueryVariable(    save_message_url,
								tw.constant.HTTP_GATEWAY_URL_VARIABLE_SESSION_ID,
								tw.session.id
								);
	save_message_url = tw.httpGateway.appendUrlQueryVariable(    save_message_url,
								tw.constant.HTTP_GATEWAY_URL_VARIABLE_SESSION_KEY,
								tw.session.key
								);
	
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

			<form name="delivery_form" action="<%=form_url;%>" method="POST">
			<input type="hidden" name="vssc_message_id" value="0">
			<input type="hidden" name="submit_action" value="">
			<% if (is_logged_in) { %>
			<table border="0" cellpadding="0" cellspacing="0" width="100%" align=center>
			  <tr>
				<td width=20%></td>
				<td><img height=5 src="<%=imagepathurl;%>/dot.gif" width=20></td>
			  </tr>
			  <tr nowrap>
				<td></td>
				<td align=right colspan=2>
				  <table border="0" cellpadding="0" cellspacing="0">
				  <tr>
					<!-- Removing reply to, reply all and forward as we do not want to enable these
					buttons for the PRC 
					
					  <td><img height="19" width="9" src="<%=imagepathurl;%>/buttonGreyLeft.gif"></td>
					  <td bgcolor="#d8d7b8"  height="19" nowrap><a href="javascript:onReplyForward('reply')" class="buttonText">
					  <font face="Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular" size="2" color="#000066">
					  Reply</font></a></td>
					  <td><img height="19" width="9" src="<%=imagepathurl;%>/buttonGreyRight.gif"></td>
					  <td><img src="<%=imagepathurl;%>/dot.gif" height="10" width="20"></td>
					  
					  <td><img height="19" width="9" src="<%=imagepathurl;%>/buttonGreyLeft.gif"></td>
					  <td bgcolor="#d8d7b8"  height="19" nowrap><a href="javascript:onReplyForward('reply_all')" class="buttonText">
					  <font face="Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular" size="2" color="#000066">
					  Reply to All</font></a></td>
					  <td><img height="19" width="9" src="<%=imagepathurl;%>/buttonGreyRight.gif"></td>
					  <td><img src="<%=imagepathurl;%>/dot.gif" height="10" width="20"></td>
					  
					  <% if (has_prepaid_reply) { %>
					  <td><img height="19" width="9" src="<%=imagepathurl;%>/buttonGreyLeft.gif"></td>
					  <td bgcolor="#d8d7b8"  height="19" nowrap><a href="<%=prepaid_reply_url;%>" class="buttonText">
					  <font face="Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular" size="2" color="#000066">
					  Free Reply</font></a></td>
					  <td><img height="19" width="9" src="<%=imagepathurl;%>/buttonGreyRight.gif"></td>
					  <td><img src="<%=imagepathurl;%>/dot.gif" height="10" width="20"></td>
					  <% }  %>
					  <td><img height="19" width="9" src="<%=imagepathurl;%>/buttonGreyLeft.gif"></td>
					  <td bgcolor="#d8d7b8"  height="19" nowrap><a href="javascript:onReplyForward('forward')" class="buttonText">
					  <font face="Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular" size="2" color="#000066">
					  Forward</font></a></td>					  
					  <td><img height="19" width="9" src="<%=imagepathurl;%>/buttonGreyRight.gif"></td>
					  
					  -->
					  
					  
					  <td><img src="<%=imagepathurl;%>/dot.gif" height="10" width="20"></td>

					  <% if ( current_folder_id != "0" ) { %>

					  <td><img height="19" width="9" src="<%=imagepathurl;%>/buttonGreyLeft.gif"></td>
					  <td bgcolor="#d8d7b8"  height="19" nowrap><a href="javascript:SubmitAction(document.delivery_form, document.delivery_form.submit_action, 'delete')" class="buttonText">
					  <font face="Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular" size="2" color="#000066">
					  Delete</font></a></td>
					  <td><img height="19" width="9" src="<%=imagepathurl;%>/buttonGreyRight.gif"></td>

					  <% } %>

					</tr>
				  </table>
				</td>
				<% if ( whether_to_show_package_position != "-1" ) { %>
				<!--td><img height=19 src="<%=imagepathurl;%>/dot.gif" width="10"></td-->
				<td align=center>
				  <table border="0" cellpadding="0" cellspacing="0">
					<tr>
					  <% if (prev_switch) { %>
					  <td><a href="<%=prev_package_url;%>"><img src="<%=imagepathurl;%>/arrowLeft.gif" width="25" height="21" border="0"></a></td>
					  <td><img border=0 height=8 src="<%=imagepathurl;%>/dot.gif" width=10></td>
					  <% }  %>
					  <td nowrap><font size="-1"><%=package_position;%></font></td>
					  <% if (next_switch) { %>
					  <td><img border=0 height=8 src="<%=imagepathurl;%>/dot.gif" width=10></td>
					  <td><a href="<%=next_package_url;%>"><img src="<%=imagepathurl;%>/arrowRight.gif" width="25" height="21" border="0"></a></td>
					  <% }  %>
					</tr>
				  </table>
				</td>
				<% } %>
			  </tr>
			</table>
			
			<table border="0" cellpadding="0" cellspacing="0" width="100%" align=center>
			  <tr>
				<td width=20></td>
				<td colspan=3><img height=10 src="<%=imagepathurl;%>/dot.gif"></td>
			  </tr>
			  
			  <tr nowrap>
				<td></td>
				<td align=left width=15%>
				  <table border="0" cellpadding="0" cellspacing="0">
					<tr>
					  <td><img height="19" width="9" src="<%=imagepathurl;%>/buttonGreyLeft.gif"></td>
					  <td bgcolor="#d8d7b8"  height="19" nowrap><a href="javascript:SubmitAction(document.delivery_form, document.delivery_form.submit_action, 'move_to')" class="buttonText">
					  <font face="Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular" size="2" color="#000066">
					  Move To Folder</font></a>&nbsp;&nbsp;</td>
					  <td><img height="19" width="9" src="<%=imagepathurl;%>/buttonGreyRight.gif"></td>
					  <td><img src="<%=imagepathurl;%>/dot.gif" height="10" width="10"></td>
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
			<% } else if ( user_has_account ) { %>
			<!-- User is not logged in but does have an account: Do not use javascript; Use href for each button (to Login screen w/package id and action) -->
			<table border="0" cellpadding="0" cellspacing="0" width="100%" align=center>
			  <tr>
				<td width=20></td>
				<td><img height=5 src="<%=imagepathurl;%>/dot.gif" width=20></td>
			  </tr>
			  <tr nowrap>
				<td></td>
				<td align=left colspan=2>
				  <table border="0" cellpadding="0" cellspacing="0">
				  <tr>
					<% if (has_prepaid_reply) { %>
					<td><img height="19" width="9" src="<%=imagepathurl;%>/buttonGreyLeft.gif"></td>
					<td bgcolor="#d8d7b8"  height="19" nowrap><a href="<%=prepaid_reply_url;%>" class="buttonText">
					<font face="Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular" size="2" color="#000066">
					Free Reply</font></a></td>
					<td><img height="19" width="9" src="<%=imagepathurl;%>/buttonGreyRight.gif"></td>
					<td><img src="<%=imagepathurl;%>/dot.gif" height="10" width="10"></td>
					<% } %>
					<td><img height="19" width="9" src="<%=imagepathurl;%>/buttonGreyLeft.gif"></td>
					<td bgcolor="#d8d7b8"  height="19" nowrap><a href="<%=login_then_reply_url;%>" class="buttonText">
					<font face="Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular" size="2" color="#000066">[Reply]</font></a></td>
					<td><img height="19" width="9" src="<%=imagepathurl;%>/buttonGreyRight.gif"></td>
					<td><img src="<%=imagepathurl;%>/dot.gif" height="10" width="10"></td>
					
					<td><img height="19" width="9" src="<%=imagepathurl;%>/buttonGreyLeft.gif"></td>
					<td bgcolor="#d8d7b8"  height="19" nowrap><a href="<%=login_then_reply_all_url;%>" class="buttonText">
					<font face="Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular" size="2" color="#000066">[Reply to All]</font></a></td>
					<td><img height="19" width="9" src="<%=imagepathurl;%>/buttonGreyRight.gif"></td>
					<td><img src="<%=imagepathurl;%>/dot.gif" height="10" width="10"></td>
					
					<td><img height="19" width="9" src="<%=imagepathurl;%>/buttonGreyLeft.gif"></td>
					<td bgcolor="#d8d7b8"  height="19" nowrap><a href="<%=login_then_forward_url;%>" class="buttonText">
					<font face="Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular" size="2" color="#000066">[Forward]</font></a></td>
					<td><img height="19" width="9" src="<%=imagepathurl;%>/buttonGreyRight.gif"></td>
				  </tr>
				</table>
			
			   </td>
			  </tr>
			</table>

			<table border="0" cellpadding="0" cellspacing="0" width="100%" align=center>
			  <tr>
				<td width=20></td>
				<td><img height=5 src="<%=imagepathurl;%>/dot.gif" width=20></td>
			  </tr>
			  <tr nowrap>
				<td></td>
				<td align=left colspan=2>
				  <table border="0" cellpadding="0" cellspacing="0">
					<tr>
					  <td><img height="19" width="9" src="<%=imagepathurl;%>/buttonGreyLeft.gif"></td>
					  <td bgcolor="#d8d7b8"  height="19" nowrap><a href="<%=login_then_delete_url;%>" class="buttonText">
					  <font face="Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular" size="2" color="#000066">[Delete]</font></a></td>
					  <td><img height="19" width="9" src="<%=imagepathurl;%>/buttonGreyRight.gif"></td>
					</tr>
				</table>
			   </td>
			  </tr>
			</table>

			<% } else if (has_prepaid_reply) { %>
			<!-- User does not have an account: Do not use javascript; Use href for button -->
			<table border="0" cellpadding="0" cellspacing="0" width="100%" align=center>
			  <tr>
				<td width=20></td>
				<td><img height=5 src="<%=imagepathurl;%>/dot.gif" width=20></td>
			  </tr>
			  <tr nowrap>
				<td></td>
				<td align=left colspan=2>
				  <table border="0" cellpadding="0" cellspacing="0">
							<tr>
							  <td><img height="19" width="9" src="<%=imagepathurl;%>/buttonGreyLeft.gif"></td>
							  <td bgcolor="#d8d7b8"  height="19" nowrap><a href="<%=prepaid_reply_url;%>" class="buttonText">
							  <font face="Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular" size="2" color="#000066">Free Reply</font></a></td>
							  <td><img height="19" width="9" src="<%=imagepathurl;%>/buttonGreyRight.gif"></td>
							  <td><img src="<%=imagepathurl;%>/dot.gif" height="10" width="10"></td>
							</tr>
					</table>
				</td>
			  </tr>
			</table>
			<% } %>
			</form>
