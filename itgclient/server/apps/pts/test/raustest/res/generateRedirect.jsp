<%@page import="javax.servlet.jsp.*, java.net.URLEncoder, com.verisign.raus.test.*"%>
<%
String serviceURL = request.getParameter("PTSbase");
String contextURL = request.getScheme() + "://" + request.getServerName() + ":" + request.getServerPort() + request.getContextPath();
String handlerURL = contextURL + "/handleRedirect";
session.setAttribute("PTSbase", serviceURL);
String service = request.getParameter("service");
session.setAttribute("service", service);
session.setAttribute("alias", request.getParameter("alias"));
%>
<html>
<head><title>RAuS Artifact Test Harness</title></head>
<body onLoad="document.forms[0].submit()">
<form name="AUTHFORM" method="GET" action="<%=HTMLEncoder.encode(response.encodeURL(serviceURL + "/raus"))%>">
  <input type="hidden" name="TARGET" value="<%=HTMLEncoder.encode(response.encodeURL(handlerURL))%>">
  <input type="hidden" name="VS_SAML_CONSUMER_URL" value="<%=HTMLEncoder.encode(response.encodeURL(handlerURL))%>">
  <INPUT TYPE="hidden" NAME="VS_SERVICE_ID" VALUE="<%=HTMLEncoder.encode(service)%>">
  <INPUT TYPE="hidden" NAME="VS_REQUEST_TYPE" VALUE="Artifact">
  <INPUT TYPE="hidden" NAME="VS_AZ_AGENT" VALUE="WebSeal">
  <INPUT TYPE="hidden" NAME="VS_APP_tokenuser" VALUE="dummy">
  <INPUT TYPE="hidden" NAME="VS_LOGOUT_URL" VALUE="dummy">
  <noscript>
  <INPUT TYPE="submit">Connect to PTS</INPUT>
  </noscript>
</FORM>
</BODY>
</HTML>
