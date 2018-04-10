<!-- Copyright (c) 1993-2000 Tumbleweed Communications Corp. All Rights Reserved. -->
<!-- #BeginEditable "EditTumbleweedFileName" -->
<!-- File name: SGMS_AccPackageCertResolutionFailed.tpl -->
<!-- #EndEditable -->


<%
	var imagepathurl = tw.httpGateway.getImgPathUrl();
%>

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 3.2 Final//EN">

<HTML>
<!-- #BeginTemplate "/Templates/TW_AccCentralSimplePage.dwt" -->
<HEAD>

<SCRIPT language="Javascript">
function GoHelp(h_dir, h_topic) {
	if (h_topic.charAt(0) == "A") {
		h_url="/help/Admin/"+h_dir+"/"+h_topic+".htm";
	} else if (h_topic.charAt(0) == "C") {
		h_url="/help/Central/"+h_dir+"/"+h_topic+".htm";
	}
	HWin=window.open(h_url,"HelpWin","toolbar=yes,width=670,height=450,resizable=yes,scrollbars=yes")
	if (HWin.focus) HWin.focus()
}
</SCRIPT>

<!-- #BeginEditable "EditJavaScripts" -->
<!-- put here all page specific the global variables, TW script or JavaScript. See AccDeliveryFolderView.tpl for example -->

<script language="JavaScript">
<!--
js_version=0
js_version=Math.round(parseFloat(navigator.appVersion)*1000)

window.returnValue = 0; //initialize the return value in case someone stabs us with the X button

function DisplayStatusMsg( msg )
{
	status = msg;
	document.MM_returnValue = true;
}

function SubmitAction( submit_obj, action_obj, folder_action )
{
	action_obj.value = folder_action;
	submit_obj.submit();
}

function AboutThisField(file)
{
	help_win=window.open(file,"AboutThisWin","toolbar=no,width=400,height=250,resizable=yes");
}

var browser_ns = window.Event ? true : false;

function SubmitOnEnter(e, form, action, result)
{
	if (browser_ns) {
		var which_char = e.which;
	} else {
		var which_char = window.event.keyCode;
	}
	if (which_char == 13) {
		SubmitAction(form, action, result)
	}
	return false;
}
//-->
</script>

<script>
<!--
function getRadioByValue (radioButtonOrGroup, value)
{
	if (!radioButtonOrGroup.length) { // single button
		if (radioButtonOrGroup.value == value)
			return radioButtonOrGroup;
		else
			return null;
	} else {
		for (var b = 0; b < radioButtonOrGroup.length; b++)
			if (radioButtonOrGroup[b].value == value)
				return radioButtonOrGroup[b];
	}
	return null;
}

function isRecipientInList(address,list)
{
	var high = list.length;
	var i;
	for(i=0;i<high;i++)
		if (address == list[i]) return true;
	return false;
}

function filterLine(Line,list)
{
	var recipients = Line.split(",");
	var newLine = "";
	var high = recipients.length;
	var i;
	var address;
	for(i=0;i<high;i++){
		address = recipients[i];
		if(!isRecipientInList(address,list)) 
		   newLine = newLine.concat(",",address);
	}
	return newLine.slice(1); //Remove the first comma
}

function removeRecipients(list)
{
	window.opener.document.form1.to.value = filterLine(window.opener.document.form1.to.value, list);
	window.opener.document.form1.cc.value = filterLine(window.opener.document.form1.cc.value, list);
	window.opener.document.form1.bcc.value = filterLine(window.opener.document.form1.bcc.value, list);
}

function processForm()
{
	// check to see if we have both secure and unsecure recepients then: RK
	if ( resolved.length > 0 )
	{
		var radiogroup = document.form1.R1;
		if (getRadioByValue(radiogroup,"medium").checked) {
			window.opener.submitWithPRC( true );
		} else if (getRadioByValue(radiogroup,"high").checked) {
			removeRecipients(window.opener.prcRecipients);
			//window.opener.promptForInvitation(window);
			window.opener.document.form1.prc_invite.value = "ON";
			window.opener.submitWithPRC( false );
			window.close();
			return;
	/*
	    } else if (getRadioByValue(radiogroup,"high_and_invite").checked) {
	        removeRecipients(window.opener.prcRecipients);
	        //TODO: Set a flag to invite guys without certs e.g. current prc to be guys
	        window.opener.submitWithPRC( false );
	*/
		} 
	}
	else
	{
		// we have only unsecured recepients so send the message : Rk
		window.opener.submitWithPRC( true );
	}

	// else Cancel
	window.close();
}


  var resolved = window.opener.resolvedRecipients;
  var prc = window.opener.prcRecipients;

//-->
</script>
<!-- #EndEditable -->


<!-- #BeginEditable "EditHtmlTitle" -->
<title>VeriSign PrivatePath service</title>
<!-- #EndEditable -->

<link rel="stylesheet" href="<%=tw.httpGateway.getStylesheetPathUrl();%>/verisign.css">
</head>

<body bgcolor="#ffffff" leftmargin="0" topmargin="0"  marginwidth="0" marginheight="0" name="main">

<form name='form1' method="POST" action="">
<table border="0" cellpadding="0" cellspacing="0" width="100%">

	<!-- top image -->
	<tr valign="top"> 
		<TD width="100%"  height="84" valign="top" background="<%=imagepathurl;%>/hd_home.gif"  bgcolor="#d8d7b8">
		  <BR><BR>&nbsp;&nbsp;<br>&nbsp;&nbsp;
		  <span class="bigblue">Recipient Information</span>
		</TD>
	</tr>
	<tr>
		<TD>
		<noscript>
			<br>
			<left>
				<font size='-1'>Many features on this page will not operate as this browser does not support Javascript.</font> 
			</left>
		</noscript> 
		</TD>
	</tr>
</table>

<table><tr><td>

	<table><tr><td>
		<b>One or more recipients cannot receive end-to-end secured PrivatePath messages.</b>
		<br><br>They may not be PrivatePath Members or are otherwise unable to receive end-to-end PrivatePath messages. 
		You can send this message using PrivatePath's <i>End-to-End Encryption</i> to those listed below as highest security 
		or send the message to all recipients using PrivatePath's <i>Service Encryption</i> at high security. <br><br>
		<script>
		if ( resolved.length > 0 ) { 
			document.write('        <font face="Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular" color="#000080">');
			document.write('        <b>Recipients with End-To-End Encryption, Highest Security:</b></font>');
			document.write('        <blockquote>');
			// FIXME !
			//to = window.opener.document.form1.to.value.split(",");
			//var resolved = window.dialogArguments.resolvedRecipients; //.opener.resolvedRecipients;
			for (i=0; i<resolved.length; i++)
			document.write('<font face="Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular" size="-1">'+resolved[i]+'</font><br>');

			document.write('</blockquote>');
		}

		if ( prc.length > 0) { 
			document.write('        <font face="Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular" color="#000080">');
			document.write('        <b>Recipients with Service Encryption, High Security:</b></font>');
			document.write('        <blockquote>');
			// FIXME !
			//to = window.opener.document.form1.to.value.split(",");
			//var prc = window.dialogArguments.prcRecipients; //.opener.resolvedRecipients;
			for (i=0; i<prc.length; i++)
				document.write('<font face="Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular" size="-1">'+prc[i]+'</font><br>');

			document.write('</blockquote>');
		}

		// Only if we have both then it makes sense to show this message. 
		if ( resolved.length > 0 ) { 
		
			document.write('        <input type="radio" value="high" name="R1">');
			document.write('        <font face="Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular" size="-1" color="#000080">');
			document.write('        Send this message to the high security recipients <u>only</u> </font><br>');
			document.write('        <input type="radio" value="medium" name="R1" checked>');
			document.write('        <font face="Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular" size="-1" color="#000080">');
			document.write('        Send this message to all recipients using high security  </font>');			
		}
		
		</script>

	</tr></td></table>
	<table width=100%>
    <tr>
      <td align="center" height="46"></td>
      <td align="center" height="46">
        <img height=10 src="<%=imagepathurl;%>/dot.gif" width=10>
      </td>
      <td align="center" height="46">
        <table border="0" cellspacing="0" cellpadding="0" align="center">
			  <tr>
			  <td><img src="<%=imagepathurl;%>/buttonGreyLeft.gif" width="9" height="19" border="0"></td>
			  <td bgcolor="#d8d7b8" height="19" nowrap>
			  <a href="javascript:processForm()" class="buttonText">
			  <font face="Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular" size="2" color="#000066">
			  Send</font></a></td>
			  <td><img  src="<%=imagepathurl;%>/buttonGreyRight.gif" height="19" width="9" border="0"></td>
			  <td>&nbsp;</td>
			  <td><img src="<%=imagepathurl;%>/buttonGreyLeft.gif" width="9" height="19" border="0"></td>
			  <td bgcolor="#d8d7b8" height="19" nowrap>
			  <a href="javascript:window.close()" class="buttonText">
			  <font face="Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular" size="2" color="#000066">
			  Cancel</font></a></td>
			  <td><img  src="<%=imagepathurl;%>/buttonGreyRight.gif" height="19" width="9" border="0"></td>
			  </tr>
        </table>
        <!-- #EndEditable -->
      </td>
    </tr>
    </table>
</tr></td></table>

</table>
</tr>
</table>
</form>


</body>
<!-- #EndTemplate -->
</html>
