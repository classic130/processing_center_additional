<!-- Copyright (c) 1993-2000 Tumbleweed Communications Corp. All Rights Reserved. -->
<!-- #BeginEditable "EditTumbleweedFileName" --> <!-- File name: SGMS_AccValidate.tpl -->
<%@include file="TW_HelperHttpHosts.tpl" %>
<%@include file="TW_HandleError.tpl" %>
<%
/*	var delivery_id = tw.request.getQueryString( tw.constant.HTTP_GATEWAY_URL_VARIABLE_SHORT_ID );

	try {
		var account_name = TW_Account.checkValidationKeyInDeliveryId( delivery_id );
	} catch (e) {
		// check the exception code for already validated accounts
		if ( tw.getObjectType( e ) == "Error"  ) {
			if ( e.id == "TW_E_ACCOUNT_ALREADY_VALIDATED" ) {
				// if the account is validated, you should
				// redirect to an "already" validated page
				tw.redirect( "TW_AccValidateAlready.tpl" );
			} else {
				TW_HandleError( e );
			}
		} else {
			throw (e );
		}
	}
*/
	var table_border_SGMS_AccValidate = 0; //table debugging
	var imagepathurl = tw.httpGateway.getImgPathUrl();

	var http_host = getRealHostname();
	var secure_host = getRealSecureHostname();

	var has_ssl = tw.server.getConfigParameter( "TW_HTTP_SSL", tw.request.locale);

	//var account_escaped = escapeHTML(account_name);
	// formurl should be /ime?s=ac&t=50
	var formurl = tw.server.getConfigParameter( "TW_VIRTUAL_URL" );
	formurl = formurl.concat("?");
	formurl = tw.httpGateway.appendUrlQueryVariable(
		formurl,
		tw.constant.HTTP_GATEWAY_URL_VARIABLE_SESSION_TYPE,
		tw.request.getQueryString( "s", "ac" ) );
	formurl	= tw.httpGateway.appendUrlQueryVariable(
		formurl,
		tw.constant.HTTP_GATEWAY_URL_VARIABLE_TRANSACTION_TYPE,
		"SGMS_TxnAccValidate.tpl");

	//var validate_key	= tw.request.getQueryString(tw.constant.HTTP_GATEWAY_URL_VARIABLE_ACCOUNT_SESSION_VALIDATE_KEY, "0");

%>
<!-- #EndEditable --> <!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 3.2 Final//EN">
<HTML>
<HEAD>
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

function GoService()
{
	//Create a new window
	var newWin = window.open("legaldocs/service.htm", "popup_1", 'toolbar=1,location=0,directories=0,status=0,menubar=0,scrollbars=1,resizable=0,width=620,height=375'); 		
}

function submitForm() {
	if (document.validate.firstName.value == "") {
		alert("You must enter your first name!");
	} else
	if (document.validate.lastName.value == "") {
		alert("You must enter your last name!");
	} else
	if (document.validate.challenge_phrase.value != document.validate.challenge_phrase2.value) {
		alert("Answers to Challenge Question do not match");
	} else {
		document.validate.submit();
	}
}

//-->
</SCRIPT>
<!-- #BeginEditable "EditHtmlTitle" -->
<title>VeriSign PrivatePath service</title>
<!-- #EndEditable -->
<link rel="stylesheet" href="<%=tw.httpGateway.getStylesheetPathUrl();%>/verisign.css">
</HEAD>
<body bgcolor="#ffffff" background="<%=imagepathurl;%>/background.gif" leftmargin="0" topmargin="0"  marginwidth="0" marginheight="0" name="main">

<table border="<%=table_border_SGMS_AccValidate;%>" cellpadding="0" cellspacing="0" align="top" width="100%">

  <!-- VeriSign logo --><!-- top image -->
  <tr>
    <td rowspan="1" valign="top" width="150" height="84"><img name="logo" src="<%=imagepathurl;%>/verisign.gif" width="150" height="84" border="0"></td>
    <td colspan="3"  height="84" valign="top" background="<%=imagepathurl;%>/hd_home.gif"  bgcolor="#d8d7b8"><BR><BR>&nbsp;&nbsp;<br>&nbsp;&nbsp;
      <span class="bigblue">Enroll for PrivatePath Digital ID - step 1 of 3</span>
  </tr>

  <tr valign="top">
    <!-- left nav bar -->
    <td rowspan="2" height="360">
	<table cellspacing="0" cellpadding="0" border="<%=table_border_SGMS_AccValidate;%>" width="100%">
	  <tr valign="top">
	    <td valign="top" background="<%=imagepathurl;%>/nav_background.gif" height="360">
						<br>
						<br>
						<br>
						&nbsp;&nbsp;&nbsp;<img src="<%=imagepathurl;%>/arrow.gif">
						<SPAN class="navNoLink">Enroll for Digital ID</SPAN><br>
	    </td>
	  </tr>
	</table>
    </td>
    <!-- left vertical spacer -->
    <TD rowspan="2" width="20"><IMG src="<%=imagepathurl;%>/spacer.gif" width="20"></TD>
    <TD height="400" width="100%">
	<TABLE height="100%" width="1" cellspacing="0" cellpadding="0" border="<%=table_border_SGMS_AccValidate;%>">
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
					<table width="600" border="<%=table_border_SGMS_AccValidate;%>" cellspacing="0" cellpadding="0" valign="TOP">
						<TR>
						  <TD colspan="3" nowrap>
							<TABLE border="<%=table_border_SGMS_AccValidate;%>" cellspacing="1" cellpadding="2" bgcolor="#d8d7b8" width="100%">
							  <TR>
							    <TD>
							      &nbsp;<IMG src="<%=imagepathurl;%>/arrow_red.gif">&nbsp;
							      <FONT color="#000066"><B>Step 1: Complete the enrollment form</B></FONT>
							    </TD>
							  </TR>
							  <TR>
							    <TD>
							      &nbsp;<IMG src="<%=imagepathurl;%>/arrow_red_blank.gif">&nbsp;
							      <FONT color="#000066"><B>Step 2: Create your PTA profile</B></FONT>
							    </TD>
							  </TR>
							  <TR>
							    <TD>
							      &nbsp;<IMG src="<%=imagepathurl;%>/arrow_red_blank.gif">&nbsp;
							      <FONT color="#000066"><B>Step 3: Receive your Digital ID</B></FONT>
							    </TD>
							  </TR>
							</TABLE>
						  </TD>
						</TR>
						<TR>
						  <TD>
						    <br><b>To view high-security messages through the PrivatePath service, enroll for a PrivatePath service Digital ID. Enter the required information and click Accept.</b><br><br>
						  </TD>
						</TR>

					<form name="validate" action="<%=formurl;%>" method="POST"> 
					<!-- Tunnel Data for SGMS is first name last name and e-mail address -->
					<input type=hidden size=16 maxlength=256 name="address" value="<%=arguments.address;%>">
						<tr>
							<td align="left">
								<table cellpadding=0 cellspacing=1 border="<%=table_border_SGMS_AccValidate;%>" align=left width="100%">
								<tr><td><img height=5 src="<%=imagepathurl;%>/spacer.gif"></td></tr>
								<tr><td align=left>
									<table border="<%=table_border_SGMS_AccValidate;%>" cellspacing="1" cellpadding="2" width="100%" align="left" valign="TOP" bgcolor="#d8d7b8">
										<tr bgcolor="#d8d7b8">
										<td colspan="3" nowrap>
											<font color="#000066" face="Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular" size="-1">
											<b>PrivatePath service Digital ID Information</b></font>
										</td>
										</tr>
									</table>
								</td></tr>
								<tr>
									<td colspan="3"><img src="<%=imagepathurl;%>/dot.gif"  width="1" height="5" border="<%=table_border_SGMS_AccValidate;%>" alt=""></td>
								</tr>
								</table>
							</td>
						</tr>

						<tr>
							<td align="center" valign="top"><img src="<%=imagepathurl;%>/dot.gif" width="10" height="15"></td>
						</tr>

						<tr>
							<td align="left">
								<TABLE border="<%=table_border_SGMS_AccValidate;%>" align=left>
								<tr>
									<td align="right" nowrap height=25><font size="-1">
										<b>Email Address:&nbsp;</b></font>
									</td>
									<td align="left">&nbsp;<%=arguments.address;%></td>
								<tr>
									<td align="right" nowrap height=25><font size="-1">
										<b>First Name:&nbsp;</b></font>
									</td>
							<% if ( arguments.firstName != "" ) { %>
									<td align="left">&nbsp;<%=arguments.firstName;%></td>
									<input type="hidden" size=16 maxlength=256 name="firstName" value="<%=arguments.firstName;%>">
							<% } else { %>
									<td align="left">
									&nbsp;<input type="text" size="30" maxlength="256" name="firstName">
									</td>
							<% } %>
								</tr>

								<tr>
									<td align="right" nowrap height=25><font size="-1">
									<b>Last Name:&nbsp;</b></font>
									</td>
							<% if ( arguments.lastName != "" ) { %>
									<td align="left">&nbsp;<%=arguments.lastName;%></td>
									<input type="hidden" size=16 maxlength=256 name="lastName" value="<%=arguments.lastName;%>">
							<% } else { %>
									<td align="left">
									&nbsp;<input type="text" size="30" maxlength="256" name="lastName">
									</td>
							<% } %>
								</tr>

								<tr>
									<td align="right" nowrap width="150" height=25><font size="-1">
									<b>Challenge question:&nbsp;</b></font><br>
									<font size="-2" color="red">Example: What is your<BR> dogs name?</font>
									</td>
									<td align="left">
									&nbsp;<input type="text" size="30" maxlength="1023" name="challenge_question">
									</td>
								</tr>

								<tr>
									<td align="right" nowrap height=25><font size="-1">
									<b>Answer:&nbsp;</b></font><br>
									<font size="-2" color="red">Example: Rover</font>
									</td>
									<td align="left">
									&nbsp;<input type="password" size="30" maxlength="1023" name="challenge_phrase">
									</td>
								</tr>

								<tr>
									<td align="right" nowrap height=25><font size="-1">
									<b>Re-enter answer:&nbsp;</b></font>
									</td>
									<td align="left">
									&nbsp;<input type="password" size="30" maxlength="1023" name="challenge_phrase2">
									</td>
								</tr>


								</TABLE>
							</TD>
						</TR>
						<TR>
						    <td>
						      <font size="-2">The Challenge Question and Answer are used to maintain your PrivatePath service ID, such as for ID renewal or replacement. Remember your challenge question and answer and keep them secret.</font><BR><BR>
						    </td>
						</TR>

						<tr><td><img src="<%=imagepathurl;%>/spacer.gif"></td></tr>
	
						<tr>
						  <TD>
							<TABLE cellspacing="0" cellpadding="0" border="<%= table_border_SGMS_AccValidate; %>">
							  <TR>
							    <td>
							      <b>You agree that you are not a citizen of nor located in the following countries  Cuba, Iran, Iraq, Libya, North Korea, Sudan, Syria, and Taliban Controlled Afghanistan.</b>
							    </td>
							    <td valign="middle" nowrap>
							      <b>Yes</b><input type="radio" name="country" value="yes" checked>&nbsp;
							      <b>No</b><input type="radio" name="country" value="no">
							    </td>
							  </TR>
							</TABLE>
						  </TD>
						</tr>
	
						<tr><td height="20"><img src="<%=imagepathurl;%>/spacer.gif" height="20"></td></tr>

						<TR align="left">
						    <TD colspan="3"><FONT face="arial, helvetica" size="1"><B>
							<TABLE cellpadding="0" cellspacing="0" border="<%=table_border_SGMS_AccValidate;%>">
							  <TR>
							    <TD><FONT face="arial, helvetica" size="1"><B>
							      PLEASE READ THIS SUBSCRIBER AGREEMENT BEFORE APPLYING FOR, ACCEPTING, OR USING A DIGITAL ID/CERTIFICATE. IF YOU DO NOT AGREE TO THE TERMS OF THIS SUBSCRIBER AGREEMENT, DO NOT APPLY FOR, ACCEPT, OR USE THE DIGITAL ID/CERTIFICATE.
							      </B></FONT><br>
							      <TEXTAREA name="name" rows="6" cols="90" readonly wrap="physical">PrivatePathSM Service Agreement
YOU MUST READ THIS PRIVATEPATHSM SERVICE OR ("THE SERVICE") SUBSCRIBER AGREEMENT ("SUBSCRIBER AGREEMENT") BEFORE APPLYING FOR, ACCEPTING, OR USING THE PRIVATEPATHSM SERVICE.  IF YOU DO NOT AGREE TO THE TERMS OF THIS AGREEMENT, DO NOT APPLY FOR, ACCEPT, OR USE THE PRIVATEPATHSM SERVICE.
				
THIS SUBSCRIBER AGREEMENT will become effective on the date you submit the application to VeriSign.  By submitting this Subscriber Agreement (and certificate application) you are requesting that VeriSign establish an online Webmail service that requires the issuance of a Digital ID (certificate) to you and you are expressing your agreement to the terms of this Subscriber Agreement.  VeriSign's Public Certification Services are governed by VeriSign's Certification Practice Statement (the "CPS") as amended from time to time, which is incorporated by reference into this Subscriber Agreement. The CPS is published on the Internet in VeriSign's repository at https://www.verisign.com/repository and is available via E-mail from:  CPS-requests@verisign.com. Amendments to the CPS are also posted in VeriSign's repository at https://www.verisign.com/repository/updates.
You agree to use the Digital ID (certificate) and any related VeriSign services only in accordance with the CPS.  

Additional Terms and Conditions.

1.  Description of Service (This Section applies to messages sent between Members.)

The PrivatePathSM Service uses the S/MIME standard and VeriSign's Public Key Infrastructure ("PKI") technology to provide end-to-end secure messaging and document delivery.  There are two types of messaging enabled by PrivatePathSM, depending on the computer capabilities of the message recipient.  VeriSign does not guarantee or warrant that the message has been retrieved by the recipient.
1.1 PrivatePathSM Member Messaging.  Messages sent to registered members ("Members") are encrypted using VeriSign's PKI technology on the sender's computer.  The encrypted message is sent to the PrivatePathSM Messaging Server ("PrivatePathSM Server") through an Internet connection secured by SSL.  Once the recipient is notified that a message exists on the PrivatePathSM Server, the recipient downloads the encrypted message over an SSL connection and decrypts the message on his/her personal computer using his/her private key.  
1.2 Non-Member Service.  (This Section applies to messages sent from a Member to a non-member).  The PrivatePathSM Service can send secure messages to non-members (those who have not registered and signed up for the service) and users of a Macintosh or UNIX computer.  Messages sent to non-members are encrypted with the Proxy Recipient Certificate ("PRC"), a digital ID held by the PrivatePathSM Server.  

2.  Revocation.  The PrivatePathSM Service uses the VeriSign Personal Trust Agent.  The Personal Trust Agent provides you a password to recover your private key securely on multiple workstations using a passphrase.  You must maintain the security of your passphrase and prevent any Compromise of the passphrase's security. 

If you know or suspect that a compromise occurred relating to your private key's security or the security of any data (such as a passphrase or PIN) protecting your private key, you must promptly notify VeriSign or the organization that approved your PrivatePathSM Service application and request that such organization revoke the Service. After your revocation request has been authenticated, VeriSign will revoke your Service (and Certificate).  You agree that VeriSign is entitled to investigate all actual or suspected Compromises of your private key or data protecting your private key, or breach in the security of the VTN, as permitted by law, and you must reasonably cooperate with VeriSign in any such investigation.  You agree that VeriSign is entitled to revoke your PrivatePathSM Service upon an actual or suspected Compromise of your private key, if your Certificate involves an actual or suspected Compromise of the security of the VTN, if you materially breach this Agreement, or if VeriSign determines that it or another organization approved your Certificate application or issued your Certificate in a way that materially differed from what is required under the CPS.  VeriSign also retains the right to revoke your PrivatePathSM Service if, within forty-five (45) days of receiving an invoice from VeriSign, you do not pay the invoice.

3.  Restrictions on Use.  You agree not to use the PrivatePathSM Service to; upload, post, email, transmit or otherwise make available Content that is unlawful, harmful, threatening, abusive, harassing, tortious, defamatory, vulgar, obscene, libelous. You also agree that such content shall not be harmful to minors in any way invasive of another's privacy, racially, ethnically or otherwise objectionable.  You agree not to email, transmit or otherwise make available any material that contains viruses or any other computer codes, files, programs designed to interrupt, destroy or limit the functionality of any computer software or hardware or telecommunications equipment.  You agree not to intentionally or unintentionally violate any applicable local, state, national or international law including but not limited to regulations promulgated by the U.S Securities and Exchange Commission, any rules of any national or other securities exchange, including without limitation, the New York Stock Exchange, the American Stock Exchange or the NASDAQ, and any regulations having the force of law.  Additionally, you shall not monitor, interfere with, or reverse engineer the technical implementation of the VeriSign Trust Network ("VTN"), except upon prior written approval from VeriSign, and shall not otherwise intentionally compromise the security of the VTN.  You agree not to use the PrivatePathSM Service as proof of identity.

4.  Export Requirements:

4.1.  VeriSign Export Licenses.  VeriSign is licensed to issue the PrivatePathSM Service  (which uses VeriSign's Personal Trust Agent), subject to the terms of VeriSign's export license agreements with the U.S. Department of Commerce, Bureau of Export Administration ("License").  VeriSign shall retain the right, at its sole discretion, to approve your Application, subject to the terms of a License.

4.2.  Personal Trust Agent.  The Export Commodity Control Number for the Personal Trust Agent component of your PrivatePathSM Service is 5D002.

4.3.  Geographic Restrictions.  You shall not be located in or use the PRIVATEPATH(SM) Service in Afghanistan (Taliban-controlled areas), Cuba, Iran, Iraq, Libya, North Korea, Sudan, Syria and any other country where such use is prohibited under U.S. export regulations, or under the terms of this Agreement.  You represent that you are not one of the individuals nor affiliated with entities on the  Bureau of Export's Denied Persons and Denied Entities Lists.  If at anytime you are added to these lists you agree to notify VeriSign and revoke the PrivatePathSM Service immediately. 

5.  DISCLAIMER OF WARRANTIES:

YOU EXPRESSLY UNDERSTAND AND AGREE THAT YOUR USE OF THIS SERVICE IS SOLELY AT YOUR OWN RISK.  YOU AGREE THE SERVICE IS PROVIDED ON AN "AS IS" AND "AS AVAILABLE" BASIS.  VERISIGN EXPRESSLY DISCLAIMS ALL WARRANTIES OF ANY KIND, WHETHER EXPRESS OR IMPLIED INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT.  VERISIGN MAKES NO WARRANTY AS THAT THE SERVICES PROVIDED HEREUNDER WILL MEET YOUR REQUIREMENTS, OR THAT THE SERVICES WILL BE UNINTERRUPTED, TIMELY,  OR ERROR FREE; NOR THE RESULTS THAT MAY BE OBTAINED FROM THE USE OF THE SERVICE WILL BE ACCURATE OR RELIABLE.  YOU UNDERSTAND AND AGREE THAT ANY MATERIAL AND/OR DATA DOWNLOADED OR OBTAINED THROUGH THE USE OF THIS SERVICE IS DONE AT YOUR OWN DISCRETION AND RISK AND THAT YOU ARE SOLEY RESPONSIBLE FOR ANY DAMAGE TO YOUR COMPUTER SYSTEM OR LOSS OF DATA THAT RESULTS FROM THE DOWNLOAD OF SUCH MATERIAL.   NO ADVICE OR INFORMATION OBTAINED ORALLY OR WRITTEN FROM VERISIGN OR THROUGH THE SERVICE SHALL CREATE ANY WARRANTY NOT EXPRESSLY STATED IN THIS SUBSCRIBER AGREEMENT.  OTHER THAN AS EXPRESSLY SET FORTH HEREIN, VERISIGN IS NOT RESPONSIBLE FOR AND SHALL HAVE NO LIABILITY WITH RESPECT TO ANY PRODUCTS AND/OR SERVICES PURCHASED BY YOU FROM THE SERVICES PROVIDED UNDER THIS AGREEMENT, WHETHER SUCH SERVICES ARE PROVIDED BY VERISIGN  OR OTHER PARTIES, WHETHER BY OR THROUGH THE VERISIGN  WEBSITE OR OTHERWISE, AND THE PROVISION OF ANY SUCH OTHER PRODUCTS AND/OR SERVICES SHALL BE SUBJECT TO THE TERMS OF YOUR AGREEMENT, IF ANY, WITH THE PARTY (WHETHER VERISIGN  OR A THIRD-PARTY) PROVIDING THE OTHER PRODUCTS AND/OR SERVICES.

6.  LIMITATION OF LIABILITY.

YOU EXPRESSLY UNDERSTAND AND AGREE THAT VERISIGN SHALL NOT BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, CONSEQUENTIAL OR EXEMPLARY DAMAGES, INCLUDING BUT NOT LIMITED TO, DAMAGES FOR LOSS OF PROFITS, GOODWILL, USE, DATA OR OTHER INTANGIBLE LOSSES (EVEN IF VERISIGN HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES), RESULTING FROM THE USE OR INABILTY TO USE THE SERVICE; THE COST OF ACQUIRING REPLACEMENT GOODS AND SERVICES RESULTING FROM ANY GOODS; DATA INFORMATION OR SERVICES PURCHASED OR OBTAINED OR MESSAGES RECEIVED OR TRANSACTIONS ENTERTED INTO, THROUGH, OR FROM THE SERVICE; UNAUTHORIZED ACCES TO OR ALTERATION OF YOUR TRANSMISSION OR DATA; STATEMENTS OR CONDUCT OF ANY THIRD PARTY ON THE SERVICE; OR ANY OTHER MATTER RELATING TO THE SERVICE.

7.  Privacy Information about your Digital ID.

THE FOLLOWING PARAGRAPHS EXPLAIN WHAT VERISIGN DOES WITH THE INFORMATION WE COLLECT FROM YOU WHEN YOU ENROLL FOR A DIGITAL ID.  PLEASE NOTE THAT OTHER PRODUCTS AND SERVICES MAY INVOLVE ADDITIONAL PRIVACY CONSIDERATIONS.  THESE PARAGRAPHS ARE EXTRACTED FROM OUR PRIVACY STATEMENT WHICH WE ENCOURAGE YOU TO READ IN FULL (http://www.verisign.com/truste).  

7.1. The CPS.  With respect to VeriSign's Public Certification Services, this Privacy Statement is intended to supplement the VeriSign Certification Practice Statement ("CPS"), not replace it.
7.2. Information We Gather from You.  VeriSign is asking for the personal information in this Digital ID enrollment screen for the limited purposes of creating your Digital ID, providing the services that may be part of your Digital ID, and authenticating your identity in order to issue you a Digital ID. You should also be assured that we do not provide or sell information about our customers or site visitors to vendors that are not involved in the provision of VeriSign's public certification and other services.  When you visit our site, our computers may automatically collect statistics about your visit. This information does not identify you personally, but rather about a visit to our site. We may monitor statistics such as how many people visit our site, the user's IP address, which pages people visit, from which domains our visitors come and which browsers people use. We use these statistics about your visit for aggregation purposes only. These statistics are used to help us improve the performance of our Web site.
7.3. How We Use and With Whom We Share the Information We Gather.    We may request information from customers via surveys.  Participation in these surveys is voluntary and will be used for purposes of monitoring or improving the use of and satisfaction with our Web site.  
We use the information you submit to contact you to discuss the support, renewal, and purchase of our products and services. We may also provide the information you have submitted to us to a VeriSign subsidiary, business partner, or representative so that the subsidiary, business partner, or representative can contact you on behalf of VeriSign to facilitate the support, renewal, and purchase of VeriSign products and services.  Please be assured that any subsidiary, business partner, or representative who contacts you for one of these purposes has agreed to use the information we supply only in accordance with a confidentiality agreement or, with respect to Digital IDs, our CPS. To find out the names and locations of the subsidiaries, business partners, and/or representatives to whom we have provided your information, please contact us at the address listed at the end of this document.  We will also use the information you supply to form the contents of a Digital ID.  The exact information that appears in our different types of Digital IDs is set forth in the relevant enrollment page, our CPS, and this Privacy Statement. Please note that all information that you provide us that forms the content of a Digital ID will be "published." Publication of Digital IDs in an accessible location (a repository) is an integral part of enabling the widespread use of Digital IDs. Your Digital ID will be published in our repository so that a third party may access, review, and rely upon your Digital ID. You should have no expectation of privacy regarding the content of your Digital ID.
If we are required by law to disclose certain information to local, state, federal, national or international government or law enforcement authorities, we will do so.
7.4. Your Ability to Opt-Out of Further Notifications.  From time-to-time, we notify our subscribers of new products, announcements, upgrades and updates. If you would like to opt-out of being notified, please contact us at the address listed at the end of this document.
If you would like to change your preferences online, please visit http://www.verisign.com/compref/ Please be aware that we reserve the right to notify our subscribers of any information that affects the security of our products or services.
7.5. How You Can Update or Correct Your Information.  We cannot update or correct information contained in a Digital ID without destroying the integrity of the Digital ID because we digitally sign each subscriber's Digital ID as a part of the Digital ID issuance process. If we were to subsequently modify or remove any information listed in a Digital ID, our digital signature would not verify the Digital ID's new content. Furthermore, if a subscriber (sender) then digitally signed a message with his or her private key, a third party would not be able to properly verify the sender's signature (created using the sender's private key) because the sender's Digital ID would have been altered after the key pair's creation. For more information and tutorials on digital signatures, Digital IDs, keys, and related subjects, click here http://www.verisign.com/repository
If you would like to update or correct any information in our records that is not contained in your Digital ID, please contact us via e-mail at id-support@verisign.com or at the address listed at the end of this document.
7.6. How You Can Revoke (Deactivate) Your Digital ID.  When a third party wants to rely on a Digital ID, it is important for the third party to know its status (for example, whether it is valid, suspended (where available) or revoked). The third party may do this by accessing our repository and querying for the status of the Digital ID. We do not generally delete Digital IDs (and their content) from our on-line repository because a third party might not then be able to check its status. You may, however, revoke (deactivate) your Digital ID. A revoked Digital ID will still appear in our repository with an indication that it has been revoked. If you are a Digital ID subscriber and would like to have your Digital ID revoked (deactivated) from our database, please visit our site at https://digitalid.verisign.com/revoke.htm and follow the listed instructions or contact us via e-mail at id-support@verisign.com or at the address listed at the end of this document.
7.7. Changes to VeriSign's Privacy Statement.  If a material change is made to the VeriSign Privacy Statement (http://www.verisign.com/truste) and/or the way we use our customers' personally identifiable information then, with the prior written approval from TRUSTe, we will post prominent notice of the nature of such change on the first page of the Privacy Statement.
Our address is: 	VeriSign, Inc.
		Attention:  Support
		487 E. Middlefield Road
		Mountain View, California  94043

YOU DEMONSTRATE YOUR KNOWLEDGE AND ACCEPTANCE OF THE TERMS OF THIS AGREEMENT BY EITHER (1) SUBMITTING AN APPLICATION OR USING THE PRIVATEPATHSM SERVICE, WHICHEVER OCCURS FIRST.


</TEXTAREA>
							    </TD>
							  </TR>
							  <tr>
							    <td valign="center" align="center"><FONT FACE="arial, helvetica" SIZE=1>
								<BR>
								<A HREF="javascript:GoService();">Click here</A> to open a printable copy of this agreement.</FONT><BR>
								<BR>
							    </td>
							  </TR>
							  <TR align="center">
							    <TD>
								<TABLE cellpadding="0" cellspacing="0" border="<%=table_border_SGMS_AccValidate;%>">
								  <TR>
									<td><img height="19" width="9" src="<%=imagepathurl;%>/buttonGreyLeft.gif"></td>
									<td bgcolor="#d8d7b8"  height="19" nowrap><a href="javascript:submitForm()" class="buttonText">
										<font face="Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular" size="2" color="#000066">
										Accept</font></a>
									</td>
									<td><img height="19" width="9" src="<%=imagepathurl;%>/buttonGreyRight.gif"></td>
									<td>&nbsp;&nbsp;&nbsp;</td>
									<td><img height="19" width="9" src="<%=imagepathurl;%>/buttonGreyLeft.gif"></td>
									<td bgcolor="#d8d7b8"  height="19" nowrap><a href="#">
										<font face="Arial, Helvetica, Geneva, Swiss, Sans-Serif, SunSans-Regular" size="2" color="#000066">
										Decline</font></a></td>
									<td><img height="19" width="9" src="<%=imagepathurl;%>/buttonGreyRight.gif"></td>
								  </TR>
								</TABLE>
							   </TD>
							  </TR>
							</TABLE>
						    </TD>
						</TR>
					</form>
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
<!-- #EndTemplate -->
</HTML>
