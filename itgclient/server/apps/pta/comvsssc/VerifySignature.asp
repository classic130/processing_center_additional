
<html>
<head>
<title>ASP Signature Verification Sample</title>
</head>
<body>
<FONT FACE="verdana, arial, helvetica" SIZE=4>
<h3>ASP Signature Verification Sample</h3>
</FONT>

<TABLE WIDTH=588 BORDER=0 CELLPADDING=0 CELLSPACING=0>
<TR>
<TD VALIGN=TOP>
<FONT COLOR="0000cc" FACE="verdana, arial, helvetica" SIZE=4><B>Transfer of Funds</B></FONT></TD>
</TR>
</TABLE>

<TABLE WIDTH=588 BGCOLOR="ffffcc" CELLPADDING=7 CELLSPACING=0 BORDER=0>
<TR>
      <TD WIDTH=588>
<FONT SIZE=2 FACE="verdana, arial, helvetica"><B>Transaction Details</B></FONT><BR><P>
<CENTER>
        
<TABLE WIDTH=574 CELLPADDING=3 CELLSPACING=2 BORDER=0>

<TR>
<TD WIDTH=50% BGCOLOR="ffcc00"><FONT FACE="verdana, arial, helvetica" SIZE=2><B>Transaction </B></FONT></TD>
<TD WIDTH=50% COLSPAN=2 BGCOLOR="ffcc00">
<%@ Language=VBScript %>
<%
    Dim dataToSign
    Dim dataSignature
    dataToSign = Request.Form("dataToSign")
    dataSignature = Request.Form("dataSignature")
    Response.Write dataToSign
%>
</TD>               
</TR>
<!--
<TR>
<TD WIDTH=50% BGCOLOR="ffcc00"><FONT FACE="verdana, arial, helvetica" SIZE=2><B>Signature </B></FONT></TD>
<TD WIDTH=50% BGCOLOR="ffcc00"><%Response.Write dataSignature%>
</td>
</tr>
-->
<%
        Dim ptaObj
		Set ptaObj = Server.CreateObject("COMVSSSC.vsVerify.1")       
        Dim result, hash, hashLen
		Dim b64Cert, certStatus, outAlg       			
'****************************************************************************************
'*	vPKIB64VerifyPKCS7        
		On Error Resume Next
		result = ptaObj.vPKIVerifyB64PKCS7(dataSignature, dataToSign, Len(dataToSign), hash, hashLen, outAlg,  b64Cert, certStatus)		
%>		
<TR>
<TD WIDTH=50% BGCOLOR="ffcc00"><FONT FACE="verdana, arial, helvetica" SIZE=2><B>Transaction Status </B></FONT></TD>
<TD COLSPAN=2 WIDTH=50% BGCOLOR="ffcc00">
<%
if (err.number <> 0) Then 
	Response.Write "There was an error in verifying the signature. Error Code : 0x" & Hex(err.number) & "<br>"
	Response.Write "err.Description:" & err.Description
else
	Response.Write "Signature Successfully Verified"	
End if 
%>
</td>
</tr>

</TABLE>

<BR><P>

</TD>
</TR>
</TABLE>

<%
'****************************************************************************************
'*	vPKIParseB64Cert        
	Dim emailAddress, commonName, title, uniqueID, address
	Dim organization, organizationUnits, orgUnitCount
	Dim issOrg, issLocality, issCountry, issCommonName
	Dim issOrgUnits, issOrgUnitCount, notBefore, notAfter
	Dim keyUsage, extendedKeyUsage, sanDirectoryNames, sanDirectoryNameCount, sanRFC822Names, sanRFC822NameCount, sanDNSNames, sanDNSNameCount, sanURIs, sanURICount, sanUPNs, sanUPNCount, sanGUIDs, sanGUIDCount, cdpDpnDirectoryNames, cdpDpnDirectoryNameCount, cdpDpnRFC822Names, cdpDpnRFC822NameCount, cdpDpnDNSNames, cdpDpnDNSNameCount, cdpDpnURIs, cdpDpnURICount, cdpDpnUPNs, cdpDpnUPNCount, cdpDpnGUIDs, cdpDpnGUIDCount, cdpCrlIssuerDirectoryNames, cdpCrlIssuerDirectoryNameCount, cdpCrlIssuerRFC822Names, cdpCrlIssuerRFC822NameCount, cdpCrlIssuerDNSNames, cdpCrlIssuerDNSNameCount, cdpCrlIssuerURIs, cdpCrlIssuerURICount, cdpCrlIssuerUPNs, cdpCrlIssuerUPNCount, cdpCrlIssuerGUIDs, cdpCrlIssuerGUIDCount
	Dim cn, index
	uniqueID = ""

	On Error Resume Next
	if (Len(b64Cert) <> 0) Then 
		'result = ptaObj.vPKIParseB64Cert(b64Cert, emailAddress, cn, title, uniqueID, address, organization, organizationUnits, orgUnitCount, issOrg, issLocality, issCountry, issCommonName, issOrgUnits, issOrgUnitCount, notBefore, notAfter)
		result = ptaObj.vPKIParseB64CertEx(b64Cert, emailAddress, cn, title, uniqueID, address, organization, organizationUnits, orgUnitCount, issOrg, issLocality, issCountry, issCommonName, issOrgUnits, issOrgUnitCount, notBefore, notAfter, keyUsage, extendedKeyUsage, sanDirectoryNames, sanDirectoryNameCount, sanRFC822Names, sanRFC822NameCount, sanDNSNames, sanDNSNameCount, sanURIs, sanURICount, sanUPNs, sanUPNCount, sanGUIDs, sanGUIDCount, cdpDpnDirectoryNames, cdpDpnDirectoryNameCount, cdpDpnRFC822Names, cdpDpnRFC822NameCount, cdpDpnDNSNames, cdpDpnDNSNameCount, cdpDpnURIs, cdpDpnURICount, cdpDpnUPNs, cdpDpnUPNCount, cdpDpnGUIDs, cdpDpnGUIDCount, cdpCrlIssuerDirectoryNames, cdpCrlIssuerDirectoryNameCount, cdpCrlIssuerRFC822Names, cdpCrlIssuerRFC822NameCount, cdpCrlIssuerDNSNames, cdpCrlIssuerDNSNameCount, cdpCrlIssuerURIs, cdpCrlIssuerURICount, cdpCrlIssuerUPNs, cdpCrlIssuerUPNCount, cdpCrlIssuerGUIDs, cdpCrlIssuerGUIDCount)


	End If 
    If (result <> 0) Then
		Response.Write "There was an error in parsing the certificate information"		
	End If
%>

<TABLE WIDTH=588 BGCOLOR="ffffcc" CELLPADDING=7 CELLSPACING=0 BORDER=0>
<TR>

<TD WIDTH=588>
<FONT SIZE=2 FACE="verdana, arial, helvetica"><B>Signing Certifictate Details</B></FONT><BR><P>
<CENTER>


<TABLE WIDTH=574 CELLPADDING=3 CELLSPACING=2 BORDER=0>
<TR>
<TD WIDTH=50% BGCOLOR="ffcc00"><FONT FACE="verdana, arial, helvetica" SIZE=2><B>Certificate Status</B></FONT></TD>
<TD WIDTH=50% BGCOLOR="ffcc00">
<%
   Select Case certStatus 
	Case "1"		Response.Write "Valid"
	Case "2"		Response.Write "Pending"
	Case "3"		Response.Write "Expired"
	Case "4"		Response.Write "CRL Expired"
	Case "6"		Response.Write "Revoked"
	Case Else	Response.Write "Status Unknown"
   End Select
%></TD>    
</TR>

<TR>
<TD WIDTH=50% BGCOLOR="ffcc00"><FONT FACE="verdana, arial, helvetica" SIZE=2><B>Serial No. </B></FONT></TD>
<TD WIDTH=50% BGCOLOR="ffcc00"><%Response.Write uniqueId%></TD>    
</TR>
<TR>
<TD WIDTH=50% BGCOLOR="ffcc00"><FONT FACE="verdana, arial, helvetica" SIZE=2><B>Email Address </B></FONT></TD>
<TD WIDTH=50% BGCOLOR="ffcc00">
<%
	Response.Write "E = "
	Response.Write emailAddress
%>
</TD>    
</TR>
<TR>
<TD WIDTH=50% BGCOLOR="ffcc00"><FONT FACE="verdana, arial, helvetica" SIZE=2><B>Common Name </B></FONT></TD>
<TD WIDTH=50% BGCOLOR="ffcc00">
<%
	Response.Write "CN = "
	Response.Write cn
%></TD>    
</TR>
<TR>
<TD WIDTH=50% BGCOLOR="ffcc00"><FONT FACE="verdana, arial, helvetica" SIZE=2><B>Title </B></FONT></TD>
<TD WIDTH=50% BGCOLOR="ffcc00">
<%
	Response.Write "T = "
	Response.Write title		
%>
	</TD>    
</TR>
<TR>
<TD WIDTH=50% BGCOLOR="ffcc00"><FONT FACE="verdana, arial, helvetica" SIZE=2><B>Address </B></FONT></TD>
<TD WIDTH=50% BGCOLOR="ffcc00">
<%
	Response.Write "A = "
	Response.Write address	
%></TD>    
</TR>
<TR>
<TD WIDTH=50% BGCOLOR="ffcc00"><FONT FACE="verdana, arial, helvetica" SIZE=2><B>Organization </B></FONT></TD>
<TD WIDTH=50% BGCOLOR="ffcc00">
<%
	Response.Write "O = "
	Response.Write organization
%>
</TD>    
</TR>
<TR>
<TD WIDTH=50% BGCOLOR="ffcc00"><FONT FACE="verdana, arial, helvetica" SIZE=2><B>OrganizationUnits </B></FONT></TD>
<TD WIDTH=50% BGCOLOR="ffcc00">
<%
		For index=0 To orgUnitCount-1
			Response.Write "OU = "
		    Response.Write organizationUnits(index)
		    Response.Write "<br>"
		Next				
%>
</TD>    
</TR>
<TR>
<TD WIDTH=50% BGCOLOR="ffcc00"><FONT FACE="verdana, arial, helvetica" SIZE=2><B>Issuer Organization </B></FONT></TD>
<TD WIDTH=50% BGCOLOR="ffcc00">
<%
	Response.Write "O = "
	Response.Write issOrg
%>
</TD>    
</TR>
<TR>
<TD WIDTH=50% BGCOLOR="ffcc00"><FONT FACE="verdana, arial, helvetica" SIZE=2><B>Issuer OrganizationUnits </B></FONT></TD>
<TD WIDTH=50% BGCOLOR="ffcc00">
<%
		For index=0 To issOrgUnitCount-1
			Response.Write "OU = "
		    Response.Write issOrgUnits(index)
		    Response.Write "<br>"
		Next				
%>
</TD>    
</TR>
<TR>
<TD WIDTH=50% BGCOLOR="ffcc00"><FONT FACE="verdana, arial, helvetica" SIZE=2><B>Issuer Locality </B></FONT></TD>
<TD WIDTH=50% BGCOLOR="ffcc00">
<%
	Response.Write "L = "
	Response.Write issLocality
%>
</TD>    
</TR>
<TR>
<TD WIDTH=50% BGCOLOR="ffcc00"><FONT FACE="verdana, arial, helvetica" SIZE=2><B>Issuer Country </B></FONT></TD>
<TD WIDTH=50% BGCOLOR="ffcc00">
<%
	Response.Write "C = "
	Response.Write issCountry
%>
</TD>    
</TR>
<TR>
<TD WIDTH=50% BGCOLOR="ffcc00"><FONT FACE="verdana, arial, helvetica" SIZE=2><B>Issuer Common Name </B></FONT></TD>
<TD WIDTH=50% BGCOLOR="ffcc00">
<%
	Response.Write "CN = "
	Response.Write issCommonName
%>
</TD>    
</TR>
<TR>
<TD WIDTH=50% BGCOLOR="ffcc00"><FONT FACE="verdana, arial, helvetica" SIZE=2><B>Certificate Validity </B></FONT></TD>
<TD WIDTH=50% BGCOLOR="ffcc00">
<%
	Response.Write notBefore
	Response.Write " To "
	Response.Write notAfter
%>
</TD>    
</TR>
<TR>
<TD WIDTH=50% BGCOLOR="ffcc00"><FONT FACE="verdana, arial, helvetica" SIZE=2><B>KeyUsage </B></FONT></TD>
<TD WIDTH=50% BGCOLOR="ffcc00">
<%
	Response.Write "KU = "
	Response.Write keyUsage
%>
</TD>    
</TR>
<TR>
<TD WIDTH=50% BGCOLOR="ffcc00"><FONT FACE="verdana, arial, helvetica" SIZE=2><B>Extended KeyUsage </B></FONT></TD>
<TD WIDTH=50% BGCOLOR="ffcc00">
<%
	Response.Write "EKU = "
	Response.Write extendedKeyUsage
%>
</TD>    
</TR>
<TR>
<TD WIDTH=50% BGCOLOR="ffcc00"><FONT FACE="verdana, arial, helvetica" SIZE=2><B>Subject Alternate Name - Directory Names </B></FONT></TD>
<TD WIDTH=50% BGCOLOR="ffcc00">
<%
		For index=0 To sanDirectoryNameCount-1
			Response.Write "SAN-DIRNAME = "
		    Response.Write sanDirectoryNames(index)
		    Response.Write "<br>"
		Next				
%>
</TD>    
</TR>
<TR>
<TD WIDTH=50% BGCOLOR="ffcc00"><FONT FACE="verdana, arial, helvetica" SIZE=2><B>Subject Alternate Name - RFC822 Names </B></FONT></TD>
<TD WIDTH=50% BGCOLOR="ffcc00">
<%
		For index=0 To sanRFC822NameCount-1
			Response.Write "SAN-RFC822 = "
		    Response.Write sanRFC822Names(index)
		    Response.Write "<br>"
		Next				
%>
</TD>    
</TR>
<TR>
<TD WIDTH=50% BGCOLOR="ffcc00"><FONT FACE="verdana, arial, helvetica" SIZE=2><B>Subject Alternate Name - DNS Names </B></FONT></TD>
<TD WIDTH=50% BGCOLOR="ffcc00">
<%
		For index=0 To sanDNSNameCount-1
			Response.Write "SAN-DNSNAME = "
		    Response.Write sanDNSNames(index)
		    Response.Write "<br>"
		Next				
%>
</TD>    
</TR>
<TR>
<TD WIDTH=50% BGCOLOR="ffcc00"><FONT FACE="verdana, arial, helvetica" SIZE=2><B>Subject Alternate Name - Uniform Resource Identifiers </B></FONT></TD>
<TD WIDTH=50% BGCOLOR="ffcc00">
<%
		For index=0 To sanURICount-1
			Response.Write "SAN-URI = "
		    Response.Write sanURIs(index)
		    Response.Write "<br>"
		Next				
%>
</TD>    
</TR>
<TR>
<TD WIDTH=50% BGCOLOR="ffcc00"><FONT FACE="verdana, arial, helvetica" SIZE=2><B>Subject Alternate Name - OtherName UPNs </B></FONT></TD>
<TD WIDTH=50% BGCOLOR="ffcc00">
<%
		For index=0 To sanUPNCount-1
			Response.Write "SAN-UPN = "
		    Response.Write sanUPNs(index)
		    Response.Write "<br>"
		Next				
%>
</TD>    
</TR>
<TR>
<TD WIDTH=50% BGCOLOR="ffcc00"><FONT FACE="verdana, arial, helvetica" SIZE=2><B>Subject Alternate Name - OtherName GUIDs </B></FONT></TD>
<TD WIDTH=50% BGCOLOR="ffcc00">
<%
		For index=0 To sanGUIDCount-1
			Response.Write "SAN-GUID = "
		    Response.Write sanGUIDs(index)
		    Response.Write "<br>"
		Next				
%>
</TD>    
</TR>
<TR>
<TD WIDTH=50% BGCOLOR="ffcc00"><FONT FACE="verdana, arial, helvetica" SIZE=2><B>CDP Full Name - Directory Names </B></FONT></TD>
<TD WIDTH=50% BGCOLOR="ffcc00">
<%
		For index=0 To cdpDpnDirectoryNameCount-1
			Response.Write "CDP-DPN-DIRNAME = "
		    Response.Write cdpDpnDirectoryNames(index)
		    Response.Write "<br>"
		Next				
%>
</TD>    
</TR>
<TR>
<TD WIDTH=50% BGCOLOR="ffcc00"><FONT FACE="verdana, arial, helvetica" SIZE=2><B>CDP Full Name - RFC822 Names </B></FONT></TD>
<TD WIDTH=50% BGCOLOR="ffcc00">
<%
		For index=0 To cdpDpnRFC822NameCount-1
			Response.Write "CDP-DPN-RFC822 = "
		    Response.Write cdpDpnRFC822Names(index)
		    Response.Write "<br>"
		Next				
%>
</TD>    
</TR>
<TR>
<TD WIDTH=50% BGCOLOR="ffcc00"><FONT FACE="verdana, arial, helvetica" SIZE=2><B>CDP Full Name - DNS Names </B></FONT></TD>
<TD WIDTH=50% BGCOLOR="ffcc00">
<%
		For index=0 To cdpDpnDNSNameCount-1
			Response.Write "CDP-DPN-DNSNAME = "
		    Response.Write cdpDpnDNSNames(index)
		    Response.Write "<br>"
		Next				
%>
</TD>    
</TR>
<TR>
<TD WIDTH=50% BGCOLOR="ffcc00"><FONT FACE="verdana, arial, helvetica" SIZE=2><B>CDP Full Name - Uniform Resource Identifiers </B></FONT></TD>
<TD WIDTH=50% BGCOLOR="ffcc00">
<%
		For index=0 To cdpDpnURICount-1
			Response.Write "CDP-DPN-URI = "
		    Response.Write cdpDpnURIs(index)
		    Response.Write "<br>"
		Next				
%>
</TD>    
</TR>
<TR>
<TD WIDTH=50% BGCOLOR="ffcc00"><FONT FACE="verdana, arial, helvetica" SIZE=2><B>CDP Full Name - OtherName UPNs </B></FONT></TD>
<TD WIDTH=50% BGCOLOR="ffcc00">
<%
		For index=0 To cdpDpnUPNCount-1
			Response.Write "CDP-DPN-UPN = "
		    Response.Write cdpDpnUPNs(index)
		    Response.Write "<br>"
		Next				
%>
</TD>    
</TR>
<TR>
<TD WIDTH=50% BGCOLOR="ffcc00"><FONT FACE="verdana, arial, helvetica" SIZE=2><B>CDP Full Name - OtherName GUIDs </B></FONT></TD>
<TD WIDTH=50% BGCOLOR="ffcc00">
<%
		For index=0 To cdpDpnGUIDCount-1
			Response.Write "CDP-DPN-GUID = "
		    Response.Write cdpDpnGUIDs(index)
		    Response.Write "<br>"
		Next				
%>
</TD>    
</TR>
<TR>
<TD WIDTH=50% BGCOLOR="ffcc00"><FONT FACE="verdana, arial, helvetica" SIZE=2><B>CDP CRL Issuer - Directory Names </B></FONT></TD>
<TD WIDTH=50% BGCOLOR="ffcc00">
<%
		For index=0 To cdpCrlIssuerDirectoryNameCount-1
			Response.Write "CDP-CRLISSUER-DIRNAME = "
		    Response.Write cdpCrlIssuerDirectoryNames(index)
		    Response.Write "<br>"
		Next				
%>
</TD>    
</TR>
<TR>
<TD WIDTH=50% BGCOLOR="ffcc00"><FONT FACE="verdana, arial, helvetica" SIZE=2><B>CDP CRL Issuer - RFC822 Names </B></FONT></TD>
<TD WIDTH=50% BGCOLOR="ffcc00">
<%
		For index=0 To cdpCrlIssuerRFC822NameCount-1
			Response.Write "CDP-CRLISSUER-RFC822 = "
		    Response.Write cdpCrlIssuerRFC822Names(index)
		    Response.Write "<br>"
		Next				
%>
</TD>    
</TR>
<TR>
<TD WIDTH=50% BGCOLOR="ffcc00"><FONT FACE="verdana, arial, helvetica" SIZE=2><B>CDP CRL Issuer - DNS Names </B></FONT></TD>
<TD WIDTH=50% BGCOLOR="ffcc00">
<%
		For index=0 To cdpCrlIssuerDNSNameCount-1
			Response.Write "CDP-CRLISSUER-DNSNAME = "
		    Response.Write cdpCrlIssuerDNSNames(index)
		    Response.Write "<br>"
		Next				
%>
</TD>    
</TR>
<TR>
<TD WIDTH=50% BGCOLOR="ffcc00"><FONT FACE="verdana, arial, helvetica" SIZE=2><B>CDP CRL Issuer - Uniform Resource Identifiers </B></FONT></TD>
<TD WIDTH=50% BGCOLOR="ffcc00">
<%
		For index=0 To cdpCrlIssuerURICount-1
			Response.Write "CDP-CRLISSUER-URI = "
		    Response.Write cdpCrlIssuerURIs(index)
		    Response.Write "<br>"
		Next				
%>
</TD>    
</TR>
<TR>
<TD WIDTH=50% BGCOLOR="ffcc00"><FONT FACE="verdana, arial, helvetica" SIZE=2><B>CDP CRL Issuer - OtherName UPNs </B></FONT></TD>
<TD WIDTH=50% BGCOLOR="ffcc00">
<%
		For index=0 To cdpCrlIssuerUPNCount-1
			Response.Write "CDP-CRLISSUER-UPN = "
		    Response.Write cdpCrlIssuerUPNs(index)
		    Response.Write "<br>"
		Next				
%>
</TD>    
</TR>
<TR>
<TD WIDTH=50% BGCOLOR="ffcc00"><FONT FACE="verdana, arial, helvetica" SIZE=2><B>CDP CRL Issuer - OtherName GUIDs </B></FONT></TD>
<TD WIDTH=50% BGCOLOR="ffcc00">
<%
		For index=0 To cdpCrlIssuerGUIDCount-1
			Response.Write "CDP-CRLISSUER-GUID = "
		    Response.Write cdpCrlIssuerGUIDs(index)
		    Response.Write "<br>"
		Next				
%>
</TD>    
</TR>
</TABLE>

</TD>
</TR>
</TABLE>
<P><BR><P>
</body>
</html>

