<%@include file="TW_HelperHttpHosts.tpl" %>
<%@include file="TW_HelperSession.tpl" %>
<% 
	// Generate the URL to the Get plugin page here!
	var get_plugin_url = tw.httpGateway.getUrl('SGMS_VSSCPluginDownload.tpl');
	var get_plugin_urlNS6 = tw.httpGateway.getUrl('SGMS_GetPluginNS6.tpl');
	var secure_host_url = "https://" + getRealSecureHostname();

if(isClientPTACompatible() && isCertAuthenticated())
	if ( tw.request.userAgentVendor == "microsoft" ) { %>
	<!-- VSSC BEGIN Global/Mode#101#autoauth#1.0.0.8#54892 -->
	<object
		classid="clsid:C5E8B9E2-D217-11D4-A21E-001083023D07"
		CODEBASE="<%=secure_host_url;%>/cabs/VSSMPTA.cab#VERSION=1,0,0,9"
		id="VSSC"
		style="LEFT: Opx; TOP: Opx; VISIBILITY: hidden">
	</object>
	<!-- VSSC END Global/Mode#101 -->

	<!-- VSSC BEGIN Apps/PTAv2#8#yes#1.0.2.2#1025 -->
	<!--
	<object
		classid="clsid:6F7864F9-DB33-11D3-8166-0060B0F885E6"
		CODEBASE="<%=secure_host_url;%>/cabs/VSSMPTA.cab#VERSION=1,0,2,5"
		id="IVSPTA"
		style="LEFT: Opx; TOP: Opx; VISIBILITY: hidden">
	</object>
	-->
	<!-- VSSC END Apps/PTAv2#8 -->
<% } else {%>
	<!-- Netscape plug-in: VSSC -->
	<script language="javascript">
		var len;
		var name;
		var description;
		var found = 0;
		var i = 0;
		var browserNum = parseInt(navigator.appVersion);

		navigator.plugins.refresh(true);
		
		len = navigator.plugins.length;
		for(i=0;i<len;++i)
		{
			name = navigator.plugins[i].name;
			description = navigator.plugins[i].description;
			if(name.search("Verisign Secure Collaboration") != -1)
			{
			  if (browserNum < 5) {
				if ( description >= 1004 )
				{ 
					found = 1;
					i = len;
				}
			  } else {
				if ( description >= 3501 )
				{

					alert("Netscape 6 is not supported");
					// Ajay - Netscape 6 not supported
					//found = 1;
					//i = len;
				}
			  }
			}
		}

		if(found != 1)
		
			if(browserNum < 5){
			self.location = "<%=get_plugin_url;%>";
			
		} else {
					//Ajay - Netscape6 not supported - who checks the browser version
					//self.location = "https://schu-sun.verisign.com:417/VSApps/client/getpluginNS6.htm";
					alert("Netscape 6 is not supported");
		}

	//if(found == 1)
	//{
	//	self.location=document.referrer; 
	//}
	//else
	//{
//		 alert("It appears that you haven't successfully installed the plug-in. \nPlease close the browser and try the operation again.");
//	}


	</script>

	<EMBED type=application/x-vssc-plugin name="VSSC" hidden="true" align="right">
	<script>
		var VSSC = document.VSSC;
	</script>
<!--
	<script>
		var VSSC_loaded = false;
		function raiseflag() {
			VSSC_loaded = true;
		}
	</script>
	<embed type="application/x-vssc-plugin" name="VSSC_A" hidden>
	<ilayer id="mylayer" onload="raiseflag()" VISIBILITY="hide">
		<embed type="application/x-vssc-plugin" name="VSSC_X" hidden>
	</ilayer>
	<script>
		var proba = "start";
		if (!document.layers["mylayer"].document.VSSC_X.isActive()) proba+="not_active";
		proba+=" "+document.embeds.length+"_embeds";
		//while (!window ["VSSC_A"]) proba=proba+" kkk";
		while (!VSSC_loaded) proba=proba+" wait";
		//while (!document.layers["mylayer"].document.VSSC_X) proba=proba+" eee";
		var VSSC = document.layers["mylayer"].document.VSSC_X;
		//var VSSC = document.VSSC;
	</script>
-->
<% } %>

