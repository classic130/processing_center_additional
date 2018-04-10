<SCRIPT language=JavaScript>
<!--

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
//-->
</SCRIPT>

<% if( tw.request.userAgentVendor == "microsoft" ) { %>
	<SCRIPT LANGUAGE="VBScript">
	Sub RemoveAttachedFile(file_name)

		On Error Resume Next
		VSSC.UnSelectAttachments=file_name
		If ( err.number <> 0 ) Then
			Call SetErrorInfoMS("Compose Operation","",CStr(hex(err.number)),"<%=ComposeAppStatus;%>",0)
			Exit Sub
		End If

	End Sub

	Function GetSelectedAttachmentSize(file_name)

		Dim AppStatus
		Dim size
		
		On Error Resume Next

		size = VSSC.SelectedAttachmentSize( file_name, AppStatus )
		If ( err.number <> 0 ) Then
			GetSelectedAttachmentSize = 0			
			Call SetErrorInfoMS("Compose Operation","",CStr(hex(err.number)),CStr(hex(AppStatus)),0)
			Exit Function
		End If

		GetSelectedAttachmentSize = size
	End Function

	</SCRIPT>

<% } else { %>
 
   <SCRIPT LANGUAGE="JavaScript">

	function ConvertToHexNS(error_code)
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
			} else if (error_code <= 0xFF) {
				javaErrorCode = "800000" + javaErrorCode.substring(javaErrorCode.length-2, javaErrorCode.length);
			} else if (error_code <= 0xFFF) {
				javaErrorCode = "80000" + javaErrorCode.substring(javaErrorCode.length-3, javaErrorCode.length);
			} else {
				javaErrorCode = "8000" + javaErrorCode.substring(javaErrorCode.length-4, javaErrorCode.length);
			}
		} else {
			ErrNumber = new Number(error_code);
			javaErrorCode = ErrNumber.toString(10);
		}

		return javaErrorCode;
	}


	function RemoveAttachedFile(file_name)
	{
		var ErrorCode;

		VSSC.set_VSSC_UnSelectAttachments( file_name );
		if ( ErrorCode = GetLastError() ) {
			SetErrorInfoNS("Compose Operation","",ConvertToHexNS(ErrorCode),"<%=ComposeAppStatus;%>",0);
			return ErrorCode;
		}

	}

	function GetSelectedAttachmentSize(file_name)
	{
		var size;
		var AppStatus = new java.lang.StringBuffer("");

		size = VSSC.VSSC_SelectedAttachmentSize( file_name, AppStatus );
		if ( ErrorCode = GetLastError() ) {
			SetErrorInfoNS("Compose Operation","",ConvertToHexNS(ErrorCode),ConvertToHexNS(AppStatus),0);
			return 0;
		}

		return size;
	}

   </SCRIPT>

<% } %>

<SCRIPT LANGUAGE="JavaScript">
<!--
var files = new Array();

function buildAttachmentsTable()
{
	// TABLE HEADER
	var tab =
		'<table border="0" valign="TOP" width="100%" cellspacing="1" cellpadding="2" bgcolor="#cccccc">\
			<tr bgcolor="#d8d7b8">\
				<td align="center" valign="TOP" nowrap width="5%">\
					<input type="checkbox" name="CheckAll" onclick="javascript:checkAll(' + files.length + ')">\
				</td>\
				<td nowrap align="left">\
					<font size="-1" face="Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular" color="#000066"><b>\
					Filename</b></font></a></td>\
				<td nowrap align="left">\
					<font size="-1" face="Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular" color="#000066"><b>\
					Size</font></b></a></td>\
				<td nowrap align="center">\
					<font size="-1" face="Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular" color="#000066"><b>\
					Action</font></b></a></td>\
			</tr>';


	// adding the lines for each file
	for (i = 0; i < files.length; i++) {
		var file_basename = basename(files[i]);
		var file_size = getFileSize( file_basename );

		tab = tab + 
			'<tr bgcolor="#FFFFFF" height=23>\
				<td align="center">\
					<input type="checkbox" name="file_checkbox' + i + '" value="'+i+'">\
				</td>\
				<td>\
					<img src="<%=tw.httpGateway.getUrl('SGMS_TxnFileTypeIcon.tpl');%>&filename='+file_basename+'" width="14" height="16" border="0">&nbsp;' + file_basename +
				'</td>';
		// FIXME !!! - file size not correct				
		tab = tab + 
				'<td align="left">' + file_size + '</td>\
				<td nowrap align="center" width="*" >\
					<table border="0" cellpadding="0" cellspacing="0">\
						<tr>\
							<td><img height="19" width="9" src="<%=imagepathurl;%>/buttonGreyLeft.gif"></td>\
							<td bgcolor="#d8d7b8" height="19" nowrap valing="middle">\
								<a href="javascript:removeAttachment('+i+')" class="buttonText" tabindex="1">\
								<font face="Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular" size="2" color="#000066">\
								Remove</font></a>\
							</td>\
							<td><img height="19" width="9" src="<%=imagepathurl;%>/buttonGreyRight.gif"></td>\
						</tr>\
					</table>\
				</td>\
			</tr>';
	}
	tab = tab +
		'</table>';

	if (files.length>0) {
		tab = tab + 
				'<table border="0" valign="TOP" width="100%">\
					<tr><td width=100%>\
						<img src="<%=imagepathurl;%>/dot.gif"  width="1" height="5" border="0" alt="">\
					</td></tr>\
					<tr><td width=100% align="left">\
						<table border="0" cellpadding="0" cellspacing="0">\
						<tr>\
							<td width="9" height="19"><img height="19" width="9" src="<%=imagepathurl;%>/buttonPurpleLeft.gif"></td>\
							<td bgcolor="#d8d7b8" height="19" nowrap><a href="javascript:removeCheckedAttachments()" class="buttonText">\
								<font face="Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular" size="2" color="#000066">\
								Remove the Checked Files...</font></a></td>\
							<td width="10" height="19"><img height="19" width="9" src="<%=imagepathurl;%>/buttonPurpleRight.gif"></td>\
						</tr>\
						</table>\
					</td></tr>\
				</table>';
	} else {
		tab = tab + '&nbsp;';
	}

	// TABLE FOOTER
	tab = tab + 
			'<table border="0" valign="TOP" width="100%">\
				<tr BGCOLOR="#ffffff">\
					<td>&nbsp;</td>\
					<td colspan="3" align="right"><font size="-1">'+files.length+'&nbsp;File(s)</font></td>\
				</tr>\
			</table>';

	return tab;
}

function basename(str)
{
	var separator = "\\";
	var index = str.lastIndexOf(separator);
	if( index > 0 ){
		return str.substr(index+1);
	} else {
		return str;
	}
}

function check(str)
{
	for (name in files)
		if (str == files[name]) return true;
	return false;
}

function addAtachment(strFileName)
{
	if (check(strFileName)) return;
	files = files.concat(strFileName);
}


function removeAttachment(n)
{
	RemoveAttachedFile(files[n]);

	if(bErrorPresent == 1)
		return;

	for (i=n; i<files.length; i++) {
		files[i] = files[i+1];
	}
	files.length=files.length-1;

	onClickAttach();
}

function removeCheckedAttachments()
{
	var checked = false;

	for (var i=0; i<files.length; i++) {
		var checkboxName = "file_checkbox" + i;
		var e = document.form1.elements[checkboxName];
		if (e.checked) {
			checked = true;
			RemoveAttachedFile(files[parseInt(e.value)]);
			if(bErrorPresent == 1)
				return;

			files[parseInt(e.value)] = null;
		}
	}

	if( checked ){
		for (var i=0,j=0; i<files.length; i++) {
			if (files[i]!=null) {
				files[j] = files[i];
				j++;
			}
		}
		files.length = j;

		onClickAttach();
	} else {
		// TODO: change the message
		alert( "No files selected" );
	}
}


function checkAll(numOfFiles)
{
	ToggleSelCheck(document.form1, "file_checkbox", numOfFiles);
}


function getFileSize( filename )
{
	var size = GetSelectedAttachmentSize(filename);

	if(bErrorPresent == 1)
		return;

	var suffix;
	if( size < 1024 ){
		// Bytes
		suffix = "Bytes";
	} else if( size < 1024*1024 ){
		// KB
		suffix = "KB";
		size /= 1024;
	} else if( size < (1024*1024*1024) ){
		// MB
		suffix = "MB";
		size /= (1024*1024);
	} else {
		// GB
		suffix = "GB";
		alert( size );
		size /= 1024*1024*1024;
	}
	if (size < 10)
	{
		size = String(size + 0.05).substr(0,3);
	} else {
		size = Math.ceil( size );
	}


	return (size + '&nbsp;' + suffix);
}

function getAttachmentsCount()
{
	return files.length;
}

//-->
</SCRIPT>
<!-- End File table -->
