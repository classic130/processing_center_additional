<!-- Copyright (c) 1993-2001 Tumbleweed Communications Corp. All Rights Reserved. -->
<!-- File name: TW_PtaFormShared.tpl -->
<%@include file="SGMS_OnSiteHostConfig.tpl" %>

	<SCRIPT LANGUAGE="JavaScript">
	<!--
	  CheckReasonCode() ;
	//-->
	</SCRIPT>

	<!-- VSSKBEGIN Global/Mode#28#autoauth#1.0.0.0#54892 -->
	<FORM METHOD="post" NAME="RenewalForm" ENCTYPE="x-www-form-encoded" ACTION=<%=OnSiteHost;%>/cgi-bin/softbounce.exe>
	<!-- VSSKEND Global/Mode#28 -->

	<INPUT TYPE=hidden NAME=orig_cert_serial>
	<INPUT TYPE=hidden NAME=orig_cert_issuerdn>
	<INPUT TYPE=hidden NAME=pkcsInformation>
	<INPUT TYPE=hidden NAME=detachedMesg VALUE="Renew Digital ID">
	<INPUT TYPE=hidden NAME=VHTML_FILE VALUE="../htmldocs/VSApps/client/userRenewalMS.htm">
	</FORM>

