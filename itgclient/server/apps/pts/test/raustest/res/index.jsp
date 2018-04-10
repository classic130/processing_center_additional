<%@page import="com.verisign.raus.test.*"%>
<%
String contextURL = request.getScheme() + "://" + request.getServerName() + ":" + request.getServerPort() + request.getContextPath();
Config cfg = Config.getInstance(request);
%>
<html>
<head><title>RAuS Artifact Test Harness</title></head>
<body>
<form method="GET" action="<%=response.encodeURL(contextURL + "/generateRedirect.jsp")%>">
  <h2>Runtime Authentication Service Test Harness<hr noshade></h2>
  <table>
    <tr>
      <td>PTS Service Address</td>
      <td><input type="text" name="PTSbase" size="60" value="http://bzou-sun.verisign.com:9004/vspts"></td>
    </tr>
    <tr>
      <td>Service ID</td>
      <td><input type="text" name="service" value="//test.com/servicetpms"></td>
    <tr>
      <td>Signing Key</td>
      <td>
	<select name="alias">
<%
	String[] names = cfg.getKeyNames();
	for(int i = 0; i < names.length; i++) {
%>
		<option<%=(i == 1 ? " selected" : "")%>><%=names[i]%></option>
<%
	}
%>
	</select>
      </td>
    </tr>
  </table>
  <input type="submit"> <input type="reset">
</form>
</BODY>
</HTML>
