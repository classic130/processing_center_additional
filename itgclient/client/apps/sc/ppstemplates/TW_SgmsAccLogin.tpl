<!-- Copyright (c) 1993-2000 Tumbleweed Communications Corp. All Rights Reserved. -->
<!-- #BeginEditable "EditTumbleweedFileName" -->
<!-- File name: TW_SgmsAccLogin.tpl -->
<!-- #EndEditable -->
<%@include file="TW_HelperHttpHosts.tpl" %>
<%@include file="TW_HandleReadCookie.tpl" %>

<%
	// redirect to "TW_TxnPickupEntry.tpl" if no delivery ID present
	pushDeliveryIdToQueryString();
%>

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 3.2 Final//EN">

<HTML>
<!-- #BeginTemplate "/Templates/TW_AccCentralSimplePage.dwt" -->

<SCRIPT language="Javascript">

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

</SCRIPT><HEAD>

<!-- #BeginEditable "EditJavaScripts" --> <!-- put here all page specific the global variables, TW script or JavaScript. See AccDeliveryFolderView.tpl for example -->
<%
/* optimization: let's put here all the standard variables we may use. */

var imagepathurl         = tw.httpGateway.getImgPathUrl();
var helppathurl            = tw.httpGateway.getHelpUrl();
var table_border_TW_SgmsAccLogin = 0; //for debugging

// generate form_url
var form_url = tw.server.getConfigParameter( "TW_VIRTUAL_URL") + "?";
form_url = tw.httpGateway.appendUrlQueryVariable( form_url,
                                                  tw.constant.HTTP_GATEWAY_URL_VARIABLE_SESSION_TYPE,
                                                  tw.request.getQueryString( tw.constant.HTTP_GATEWAY_URL_VARIABLE_SESSION_TYPE, "ac" )
                                                 );
form_url = tw.httpGateway.appendUrlQueryVariable( form_url,
                                                  tw.constant.HTTP_GATEWAY_URL_VARIABLE_TRANSACTION_TYPE,
                                                  "TW_SgmsTxnAccLogin.tpl"); /*AccLogin*/

form_url = tw.httpGateway.appendUrlQueryVariable( form_url,
                                                    tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_DONOT_RECOVER_FROM_COOKIE_AT_ALL,

                                                    tw.constant.HTTP_GATEWAY_DONOT_RECOVER_FROM_COOKIE );
var package_id = tw.request.getQueryString(
                                            tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_STOREITEM_ID,
                                            "0"
                                            );
if ( package_id != "0" ) {
    form_url = tw.httpGateway.appendUrlQueryVariable(
                                            form_url,
                                            tw.constant.HTTP_GATEWAY_URL_VARIABLE_SESSION_ID,
                                            tw.session.id
                                          );

    form_url = tw.httpGateway.appendUrlQueryVariable(
                                            form_url,
                                            tw.constant.HTTP_GATEWAY_URL_VARIABLE_SESSION_KEY,
                                            tw.session.key
                                          );

    form_url = tw.httpGateway.appendUrlQueryVariable(
                                            form_url,
                                            tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_STOREITEM_ID,
                                            package_id
                                          );

    var action = tw.request.getQueryString(
                                    tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_ACTION_ID,
                                    "-1"
                                    );

    if ( action != "-1" ) {
        form_url = tw.httpGateway.appendUrlQueryVariable(
                                            form_url,
                                            tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_ACTION_ID,
                                            action
                                          );

    }
}

// get account email
var enable_account_or_password_cookie = tw.server.getConfigParameter("TW_ENABLE_ACCOUNT_OR_PASSWORD_COOKIE");
var account = tw.request.getQueryString(
                                    tw.constant.HTTP_GATEWAY_URL_VARIABLE_PICKUP_SESSION_RECIPIENT_EMAIL,
                                    ""
                                    );
account = account.decodeBase64();

if ( account == "" ) {
    if ( enable_account_or_password_cookie ) {
        var account_cookie = tw.request.getCookie(tw.constant.COOKIE_ACCOUNT_LOGIN_ENCODED);
        account = account_cookie.decodeBase64();
    }
}

var is_ssl                = tw.request.isSSL;
var has_ssl            = tw.server.getConfigParameter("TW_HTTP_SSL");
var has_non_ssl            = tw.server.getConfigParameter("TW_HTTP_NON_SSL");

var offer_ssl;

if ((!is_ssl) && (has_ssl == true)) {
    offer_ssl = true;
} else {
    offer_ssl = false;
}

var enable_cache_password = has_ssl && is_ssl && enable_account_or_password_cookie;

// get non_secure and secure host
var non_secure_httphost = getRealHostname();
var secure_httphost = getRealSecureHostname();

var desktop_url = "";
// Uncomment the next line to add a desktop download link to the login page.
// var desktop_url = tw.server.getConfigParameter( "TW_GENERIC_CLIENT_DOWNLOAD_URL", tw.request.locale );

var has_sent_free_reply = tw.request.getQueryString(tw.constant.HTTP_GATEWAY_URL_VARIABLE_TRANSACTION_TYPE, "0") == "TW_TxnAccPackage.tpl"; // transaction id 751 is new package

%>
<script language="JavaScript">
<!--
js_version=0
js_version=Math.round(parseFloat(navigator.appVersion)*1000)


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
function AboutThisField(file) {
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
<!-- #EndEditable -->


<!-- #BeginEditable "EditHtmlTitle" -->
<title>VeriSign PrivatePath service</title>
<!-- #EndEditable -->

<link rel="stylesheet" href="<%=tw.httpGateway.getStylesheetPathUrl();%>/verisign.css">
</head>

<body bgcolor="#000000" background="<%=imagepathurl;%>/background.gif" leftmargin="0" topmargin="0"  marginwidth="0" marginheight="0" name="main"
onLoad="if ((document.login_securely_form)&&(js_version>2300)) document.login_securely_form.account_or_email.focus()">

<table border="<%= table_border_TW_SgmsAccLogin; %>"  cellpadding="0" cellspacing="0" width="100%">
  <!-- VeriSign logo --><!-- top image -->
  <TR> 
    <TD colspan="1" rowspan="1" width="150" valign="top" height="84"><img name="logo" src="<%=imagepathurl;%>/verisign.gif" width="150" height="84" border="0"></TD>
    <TD colspan="3" height="84" valign="top" nowrap background="<%=imagepathurl;%>/hd_home.gif"  bgcolor="#d8d7b8"><BR><BR>&nbsp;&nbsp;<br>&nbsp;&nbsp;
      <span class="bigblue">
      Login</span>
    </TD>
  </TR>

  <TR valign="top">
    <!-- left nav bar -->
    <TD rowspan="2" height="360">
	<TABLE width="100%" cellspacing="0" cellpadding="0" border="<%=table_border_TW_SgmsAccLogin;%>">
	  <TR valign="top">
	    <TD colspan="2" valign="top" background="<%=imagepathurl;%>/nav_background.gif" height="360" width="150">
	      <!-- section links -->
	      <br>
	      <br>
	      <br>
		<% if (0) {TW_MenuBuilder( imagepathurl );}  /* TODO: PK - implement this */%>

	      &nbsp;&nbsp;&nbsp;<img src="<%=imagepathurl;%>/arrow.gif" height="13" width="6">&nbsp;<SPAN class="navNoLink">Login</SPAN><br><br>
	      &nbsp;&nbsp;&nbsp;<img src="<%=imagepathurl;%>/blank.gif" height="13" width="6">&nbsp;<a href="https://www.netsol.com/en_US/enhance-it/privatepath.jhtml" class="nav">Enroll Now</a><br><br>
	      &nbsp;&nbsp;&nbsp;<img src="<%=imagepathurl;%>/blank.gif" height="13" width="6">&nbsp;<a href="javascript:GoHelp('FAQ_member', '');" class="nav">FAQ</a><br><br>
	      &nbsp;&nbsp;&nbsp;<img src="<%=imagepathurl;%>/blank.gif" height="13" width="6">&nbsp;<a href="javascript:GoHelp('Accessing', '');" class="nav">Help</a><br><br>
	      &nbsp;&nbsp;&nbsp;<img src="<%=imagepathurl;%>/blank.gif" height="13" width="6">&nbsp;<a href="https://www.netsol.com/en_US/enhance-it/privatepath.jhtml" class="nav">Contact Us</a><br><br>
	       <!-- End of section links -->
	    </TD>
	  </TR>
	</TABLE>
    </TD>
    <!-- left vertical spacer -->
    <TD rowspan="2" width="20"><IMG src="<%=imagepathurl;%>/spacer.gif" width="20" border="0"></TD>

    <TD height="400" width="100%">
	<TABLE height="100%" width="1" cellspacing="0" cellpadding="0" border="<%=table_border_TW_SgmsAccLogin;%>">
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

		<table width="600" cellspacing="1" cellpadding="2" border="<%=table_border_TW_SgmsAccLogin;%>">

		  <form name="login_form" action="<%=form_url;%>" method="POST" onSubmit="login_form.account_or_email.value=login_securely_form.account_or_email.value">
		    <input type=hidden    name="submit_action" value="login">
		    <input type=hidden    name="account_or_email" value="">
		  </form>

		  <form name="login_securely_form"
				<% if(!is_ssl && has_ssl) { %>
					action="https://<%=secure_httphost;%><%=form_url;%>"
				<% } else { %>
					action="<%=form_url;%>"
				<% } %>
		  method="POST">
				<% if ( has_sent_free_reply ) { %>
					  <tr>
					    <td width=10></td>
					    <td colspan=3 nowrap>Your free reply was sent successfully</td>
					  </tr>
				<% } %>
		  <tr bgcolor="#d8d7b8">
		    <td colspan="2" align="left">
		      <font color="#000066" face="Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular" size="-1">
		      <b>&nbsp;PrivatePath Login</b></font>
		    </td>
		  </tr>
		  <tr>
		    <td>
			<table>
			  <tr>
			    <td>
			      <% var account_escaped = escapeHTML(account); %>
			      <b>Email Address:</b> 
			    </td>
			    <td>
			      <input type="text" size="30" maxlength="256" name="account_or_email" value="<%=account_escaped;%>" tabindex=1 onkeypress="javascript:SubmitOnEnter(event, document.login_securely_form, document.login_securely_form.submit_action, 'login');">
			    </td>
			  </tr>
			  <input type=hidden name="submit_action" value="login">
			  <tr>
			    <td>&nbsp;</td>
			    <td>
			      <input type="submit" value="Login" onClick="document.login_form.account_or_email.value=document.login_securely_form.account_or_email.value; SubmitAction( document.login_form, document.login_form.submit_action, 'login')">
			    </td>
			  </tr>
			</table>
		    </td>
		  </tr>
		  </form>

		  <tr>
		    <td><img  height="20" src="<%= imagepathurl; %>/spacer.gif"></td>
		  </tr>
		  <tr bgcolor="#d8d7b8">
		    <td width="100%" nowrap> 
		      <font color="#000066" face="Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular" size="-1">
		      <b>&nbsp;Sign Up for PrivatePath</b></font>
		      </td>
		  </tr>
		  <tr>
		    <td height="10"><img src="<%= imagepathurl; %>/spacer.gif"></td>
		  </tr>
		  <tr>
		    <td>
		      If you are <b>new to the service</b> and would like to obtain a free, receive only membership, <a href="https://www.netsol.com/en_US/enhance-it/privatepath.jhtml">click here.</a>	<br>
		      If you are a <b>receive-only member of PrivatePath</b> and would like to upgrade your membership, <a href="https://www.netsol.com/en_US/enhance-it/privatepath.jhtml">click here. </a>
		    </td>
		  </tr>
		  <tr>
		    <td>
		      <br>
			PrivatePath Service, delivered to you from VeriSign, the most trusted name in Internet security, gives you end to end secure 
			delivery capability for your most critical and confidential information.  Utilizing the speed of the Internet, 
			coupled with the privacy of a hand-delivered courier service, PrivatePath ensures that your most private communications 
			are kept between you and the person with whom you are communicating.  Save yourself the inconvenience and high cost 
			of express delivery services and start enjoying these benefits today:<br>
			<br>
			<ul>
			  <li><b>End to End Security</b></li>
			  <li><b>Ease of Use</b></li>
			  <li><b>Time/Cost Savings</b></li>
			  <li><b>Real Time Tracking</b></li>
			</ul>
				<a href="https://www.netsol.com/en_US/enhance-it/privatepath.jhtml">Learn more</a> about these and some of the other benefits of membership that our current members have come to rely on.
			<a href="https://www.netsol.com/en_US/enhance-it/privatepath.jhtml">Start today!</a><br><br><br><br>
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
<!-- #EndTemplate --></html>
