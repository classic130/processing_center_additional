<!-- Copyright (c) 1993-2001 Tumbleweed Communications Corp. All Rights Reserved. -->
<%@include file="TW_GlobalHeaderMenu.tpl" %>
<%@include file="TW_HandleError.tpl" %>
<%@include file="TW_HelperSession.tpl" %>
<%@include file="TW_HelperForm.tpl" %>

<%@include file="TW_HelperThrowErrors.tpl" %>
<%@include file="SGMS_HelperAccount.tpl" %>

<%@include file="TW_HelperHttpHosts.tpl" %>

<!-- File name: TW_AccPackage.tpl -->
<!-- NOTE:  This page has no associated DreamWeaver template -->
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 3.2 Final//EN">
<HTML>
<%
var imagepathurl = tw.httpGateway.getImgPathUrl();
var helppathurl = tw.httpGateway.getHelpUrl();

var microsoft_useragent = "microsoft";
var current_useragent = tw.request.userAgentVendor;

var secure_url = "https://" + getRealSecureHostname();

%>

<HEAD>
<META HTTP-EQUIV="pragma" CONTENT="no-cache">
<title>VeriSign PrivatePath service</title>
<link rel="stylesheet" href="<%=tw.httpGateway.getStylesheetPathUrl();%>/verisign.css">

<script language="javascript">


	function getPlugins()
	{
	   var Result;
	   //alert ("calling smart update script");
	   if ( navigator.javaEnabled() ) {
			trigger = netscape.softupdate.Trigger;
			if ( trigger.UpdateEnabled() ) {
				if (navigator.platform == "Win32") {
				   vi = new netscape.softupdate.VersionInfo(1, 0, 0, 4);
				   //-- VSSKBEGIN Enrollment/CertStore#30#verisign#1.0.0.0#1025 --
				//-- VSSKBEGIN Global/Mode#105#autoauth#1.0.0.0#24983 --
			 Result = trigger.ConditionalSoftwareUpdate(
				"<%=secure_url;%>/cabs/vsnpsmpta.jar",
				"plugins/verisign/vsmptanp",
				 vi, trigger.DEFAULT_MODE);
				//-- VSSKEND Global/Mode#105 --
				   //-- VSSKEND Enrollment/CertStore#30 --
				   if (Result == false) alert ("The plugin is installed.\nClick Continue to resume operation.");
		  }
		  else alert("This plug-in only runs on Windows NT/95.");
	   }
	   else
		  alert("Enable SmartUpdate before running this script.");
	}
	else 
	   alert("Enable Java before running this script.");
	}

	function checkPlugins()
	{
	  var len;
	  var name;
	  var description;
	  var found = 0;

	  navigator.plugins.refresh(true);
	  window.location.reload();

	  len = navigator.plugins.length;
	  for(i=0;i<len;++i)
	  {
			name = navigator.plugins[i].name;
			description = navigator.plugins[i].description;
			if(name.search("Verisign Secure Collaboration") != -1)
			{
				//if ( description >= 3022 )
				//{
					found = 1;
					i = len;
				//}
			}
	  }

	  if(found == 1)
		 self.location=document.referrer; 
	  else
		 alert("It appears that you haven't successfully installed the plug-in. \nPlease close the browser and try the operation again.");
	  }
	//-->

</script>



</HEAD>

<body bgcolor="#ffffff" background="<%=imagepathurl;%>/background.gif" leftmargin="0" topmargin="0"  marginwidth="0" marginheight="0" name="main">

<table border="0" cellpadding="0" cellspacing="0" width="100%" align="top">

  <!-- VeriSign logo -->
 <tr> 
    <td valign="top"><img name="logo" src="<%=imagepathurl;%>/verisign.gif" width="150" height="83" border="0"></td>
 	<td width="100%"  height="36"  valign="top"  background="<%=imagepathurl;%>/hd_home.gif"><br><br>&nbsp;&nbsp;<br>&nbsp;&nbsp;
	<span class="bigblue">PrivatePath service Login</span></td>
</tr>


  <tr valign="top">
  
   <!-- left nav bar -->
   <td width="150" height="360">
     <table width="100%" cellspacing="0" cellpadding="0" border="0">
	   <tr valign="top">
	     <td valign="top" background="<%=imagepathurl;%>/nav_background.gif" height="360" width="150">
		 
			 <!-- section links -->
		 <br>
		 <br>
		 <br>
     	&nbsp;&nbsp;&nbsp;<img src="<%=imagepathurl;%>/arrow.gif">
	    <font color="#ffffff" face="Arial,Verdana,Helvetica" size="-1"><b>
	    &nbsp;<a href="<%=secure_url;%>" class='nav'>Login</a><b></font><br>
	  <!-- End of section links -->
		 </td>
	   </tr>
	 </table>
	</td>
	
	<!-- start of content cell -->
    <td width="100%">
	  <table border="0" cellpadding="20" cellspacing="0" width="100%" align="top">
		<td width="100%" valign="top"> 
		<table>
		<!-- put content here -->
		<tr>
			<td>
			<font size="+1" color="#b32732"><b>Install the VeriSign PTA plugin</b></font><br><br>
			</td>
		</tr>
        <tr>
			<td>
			The latest VeriSign PTA plugin is required to access your VeriSign PrivatePath account.<BR>
			<br>
			Click on the Install button below to download the plugin. You will see a Netscape Java
       		Security dialog box. Click the Grant button (as shown below) to install the
       		plugin. 
			<br><br>
			<center>&nbsp;&nbsp;&nbsp;<img src="<%=imagepathurl;%>/ns_smart.gif"></center>
			<br><br>
			<form>
			<center><input type=button value="Install" Name="Install" onclick=getPlugins()>		</center>
			</form>
			<br><br>
			After the install is complete, <a href="<%=secure_url;%>">login to your account.</a>
			</td></tr>



		<!-- copyright row -->
		<tr>
			<td height="80" valign="bottom">
			<A HREF="https://www.verisign.com/about/copyright/index.html" target="new"><span class="copyrt">Copyright &#169; 2001,</span></A>
			<A HREF="https://www.verisign.com/about/copyright/index.html" target="new"><span class="copyrt">Privacy Policy,</span></A><span class="copyrtblack"> VeriSign, Inc. All Rights Reserved<BR></span>
			 			
			</td>
		</tr>
		
      	</table>
	  
	  	</td>
 	</tr>
    </table>
	<!-- end view message table -->

	<img height=5 src="<%=imagepathurl;%>/dot.gif" width=20>

		<br>
		<br>
	    <br>
		
			
		</td>
	   
     </table>	 
    </td>

  </tr>
</table>

</body>
</html>

