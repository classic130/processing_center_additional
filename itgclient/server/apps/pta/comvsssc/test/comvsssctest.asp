<%@ Language=VBScript %>
<%
'On Error resume next
		Response.Write "<html>"
        Dim result, hash, hashLen,outAlg, cert, certLen, certStatus
        Dim pkcs7Len, pkcs7, newB64pkcs7, b64pkcs7
		Dim b64Cert 
        b64pkcs7 = "MIIFVQYJKoZIhvcNAQcCoIIFRjCCBUICAQExDjAMBggqhkiG9w0CBQUAMAsGCSqGSIb3DQEHAaCCA8IwggO+MIIDaKADAgECAhA2yqwVXnaEOJxgm28KPgPrMA0GCSqGSIb3DQEBBAUAMIGZMREwDwYDVQQKEwhWZXJpU2lnbjEuMCwGA1UECxMlVmVyaVNpZ24gQ2xhc3MgMiBPblNpdGUgSW5kaXZpZHVhbCBDQTEfMB0GA1UECxMWRm9yIFRlc3QgUHVycG9zZXMgT25seTEzMDEGA1UEAxMqVmVyaVNpZ24gQ2xhc3MgMiBPblNpdGUgSW5kaXZpZHVhbCBURVNUIENBMB4XDTAxMDQxNDAwMDAwMFoXDTAyMDQxNDIzNTk1OVowga8xETAPBgNVBAoUCFZlcmlTaWduMRkwFwYDVQQLFBBUZXN0IEVuZ2luZWVyaW5nMUYwRAYDVQQLEz13d3cudmVyaXNpZ24uY29tL3JlcG9zaXRvcnkvQ1BTIEluY29ycC4gYnkgUmVmLixMSUFCLkxURChjKTk2MRUwEwYDVQQDEwxwaWxvdEJpbiBab3UxIDAeBgkqhkiG9w0BCQEWEWJ6b3VAdmVyaXNpZ24uY29tMIGfMA0GCSqGSIb3DQEBAQUAA4GNADCBiQKBgQCxyH9HFeI25DqoXDpZBt/Uf3zuXXEsF6wdQ6R/Y+4ELVbo4+Mb6Z3j2hPScMIgr4sRMoYqFvz5k4ASzsy6zIbJOKFUMFxikm9t7qc0miLrYKnF3X5Ln3B87F+5FzwAtj6i2D5KMz54zeEB5oXkVWXXavINYqPSpeoHmp2cmkWm2QIDAQABo4IBLjCCASowCQYDVR0TBAIwADCBrAYDVR0gBIGkMIGhMIGeBgtghkgBhvhFAQcBATCBjjAoBggrBgEFBQcCARYcaHR0cHM6Ly93d3cudmVyaXNpZ24uY29tL0NQUzBiBggrBgEFBQcCAjBWMBUWDlZlcmlTaWduLCBJbmMuMAMCAQEaPVZlcmlTaWduJ3MgQ1BTIGluY29ycC4gYnkgcmVmZXJlbmNlIGxpYWIuIGx0ZC4gKGMpOTcgVmVyaVNpZ24wCwYDVR0PBAQDAgWgMBEGCWCGSAGG+EIBAQQEAwIHgDBOBgNVHR8ERzBFMEOgQaA/hj1odHRwOi8vcGlsb3RvbnNpdGVjcmwudmVyaXNpZ24uY29tL09uU2l0ZVB1YmxpYy9MYXRlc3RDUkwuY3JsMA0GCSqGSIb3DQEBBAUAA0EACs0Z9QDAjn2Ur4Tmm808yJpKTRN2oTlfCiIay9UGiMeyhXCjSlxmHjQfbjSfYA3o6mkysTDQQDraS83BWz0P/zGCAVgwggFUAgEBMIGuMIGZMREwDwYDVQQKEwhWZXJpU2lnbjEuMCwGA1UECxMlVmVyaVNpZ24gQ2xhc3MgMiBPblNpdGUgSW5kaXZpZHVhbCBDQTEfMB0GA1UECxMWRm9yIFRlc3QgUHVycG9zZXMgT25seTEzMDEGA1UEAxMqVmVyaVNpZ24gQ2xhc3MgMiBPblNpdGUgSW5kaXZpZHVhbCBURVNUIENBAhA2yqwVXnaEOJxgm28KPgPrMAwGCCqGSIb3DQIFBQAwDQYJKoZIhvcNAQEBBQAEgYBT317/Dc6gtWvqq2Ox92OLWPJ7RwENll9zb6EdchOVQFyZ6yBlBFRDB+C+xUnS6iludsp30GMHuJovZrlxMzxMspUZfrJai8z2M+RSvCHplWIvLGtg7gd0xrTbK6+4pArV427FLnfi0b0GG0zWyc3jpQ+FVpgWpAKI5AJQ/ARxpg=="

'****************************************************************************************
'*	vPKIInit
        Dim ptaObj
		Set ptaObj = Server.CreateObject("COMVSSSC.vsVerify.1")
'		result = ptaObj.vPKIInit(100,"C:\PTA\pta\config\VerifySignatureOptions.txt")
 '       Response.Write "PKIInit():" & result & "<br>"
'		Response.Write "**************************************************<br>"

'****************************************************************************************
'*	vPKIUnBase64Alloc
		result = ptaObj.vPKIUnBase64Alloc(pkcs7,pkcs7Len,b64pkcs7)
		Response.Write "vPKIUnBase64Alloc:" & result & "<br>"
		Response.Write "variable name:" & TypeName(pkcs7) & "<br>"
		Response.Write "UBound of pkcs7:" & UBound(pkcs7) & "<<<br>"
		Response.Write "LBound of pkcs7:" & LBound(pkcs7) & "<<<br>"
	    Response.Write "original b64pkcs7:<br>" & b64pkcs7 & "<<<br>"		
		Response.Write "pkcs7 (encoded by Encode64()): <br>" & Encode64(pkcs7,pkcs7Len) & "<<<br>"
		Response.Write "pkcs7Len:" & pkcs7Len & "<br>"
		Response.Write "**************************************************<br>"

'****************************************************************************************
'*	vPKIBase64Alloc
        result = ptaObj.vPKIBase64Alloc(newB64pkcs7,pkcs7,pkcs7Len)
		Response.Write "vPKIBase64Alloc:" & result & "<br>"
		Response.Write "typeName:" & TypeName(newB64pkcs7) & "<br>"
		Response.Write "newB64pkcs7 using vPKIBase64Alloc:<br>" & newB64pkcs7 & "<<<br>"
		Response.Write "**************************************************<br>"


'****************************************************************************************
'*	vPKIParseB64PKCS7
		result = ptaObj.vPKIParseB64PKCS7(b64pkcs7, hash, hashLen, outAlg,  b64Cert, certStatus)
        Response.Write "vPKIParseB64PKCS7:" & result & "<br>"
        Response.Write  "hash:" & Encode64(hash,hashLen) & "<br>"
        Response.Write  "hashLen:" & hashLen & "<br>"
        Response.Write  "outAlg:" & outAlg & "<br>"
		Response.Write  "cert:" & b64Cert & "<br>"
        Response.Write  "certStatus:" & certStatus & "<br>"
		Response.Write "**************************************************<br>"

'****************************************************************************************
'*	vPKIParseB64Cert        
		Dim emailAddress
		Dim commonName
		Dim title
		Dim uniqueID
		Dim address
		Dim organization
		Dim organizationUnits
		Dim orgUnitCount, issOrg, issLocality, issCountry, issCommonName, issOrgUnits, issOrgUnitCount
		Dim notBefore, notAfter
		Dim cn
		Dim index

        result = ptaObj.vPKIParseB64Cert(b64Cert, emailAddress, cn, title, uniqueID, address, organization, organizationUnits, orgUnitCount, issOrg, issLocality, issCountry, issCommonName, issOrgUnits, issOrgUnitCount, notBefore, notAfter)
        Response.Write  "vPKIParseB64Cert    :" & result & "<br>"       
        Response.Write  "email address      :" & emailAddress & "<br>"
		Response.Write  "cn                 :" & cn & "<br>"
		Response.Write  "title              :" & title & "<br>"
		Response.Write  "uniqueID           :" & uniqueID & "<br>"
		Response.Write  "address            :" & address & "<br>"
		Response.Write  "organization       :" & organization & "<br>"
		For index=0 To orgUnitCount-1
		    Response.Write  "organizationUnits " & index & ": " & organizationUnits(index) & "<br>"
		Next
		Response.Write  "orgUnitCount       :" & orgUnitCount & "<br>"
		Response.Write  "issOrg             :" & issOrg & "<br>"
		Response.Write  "issLocality        :" & issLocality & "<br>"
		Response.Write  "issCountry         :" & issCountry & "<br>"
		Response.Write  "issCommonName      :" & issCommonName & "<br>"
		Response.Write  "issOrgUnitCount    :" & issOrgUnitCount & "<br>"
		For index=0 To issOrgUnitCount-1
		    Response.Write  "issOrganizationUnits " & index & ": " & issOrgUnits(index) & "<br>"
		Next		
		Response.Write  "notBefore          :" & notBefore & "<br>"
		Response.Write  "notAfter           :" & notAfter & "<br>"
	    Response.Write "<br>"

		Response.Write "**************************************************<br>"
		'b64Cert = ""

		

'****************************************************************************************
'*	vPKIB64VerifyPKCS7
        theMsg = "123,Money Market,Cash"
		result = ptaObj.vPKIVerifyB64PKCS7(b64pkcs7, theMsg,21, hash, hashLen, outAlg,  b64Cert, certStatus)
        Response.Write "vPKIVerifyPKCS7:" & result & "<br>"
        Response.Write  "hash:" & Encode64(hash,hashLen) & "<br>"
        Response.Write  "hashLen:" & hashLen & "<br>"
        Response.Write  "outAlg:" & outAlg & "<br>"
        Response.Write  "cert:" & b64Cert & "<br>"
        Response.Write  "certStatus:" & certStatus & "<br>"
		Response.Write "**************************************************<br>"

'****************************************************************************************
'*	vPKIGetRevocationStatus
        theHashLen = hashLen
		Dim userName		
		result = ptaObj.vPKIGetB64RevocationStatus(b64Cert, certStatus, userName)
        Response.Write "vPKIGetB64RevocationStatus:" & result & "<br>"
        Response.Write  "certStatus:" & certStatus & "<br>"
        Response.Write  "userName:" & userName & "<br>"
		Response.Write "**************************************************<br>"


'****************************************************************************************
'*	vPKICompareMsgHash
        theHashLen = hashLen
		theMsg = "123,Money Market,Cash"
        'result = ptaObj.vPKICompareMsgHash(theMsg,21, outAlg, hash, hashLen)
        Response.Write "vPKICompareMsgHash:" & result & "<br>"
		Response.Write "**************************************************<br>"


'****************************************************************************************
'*	vPKIParseB64CertEx
		Dim keyUsage, extendedKeyUsage, sanDirectoryNames, sanDirectoryNameCount, sanRFC822Names, sanRFC822NameCount, sanDNSNames, sanDNSNameCount, sanURIs, sanURICount, sanUPNs, sanUPNCount, sanGUIDs, sanGUIDCount, cdpDpnDirectoryNames, cdpDpnDirectoryNameCount, cdpDpnRFC822Names, cdpDpnRFC822NameCount, cdpDpnDNSNames, cdpDpnDNSNameCount, cdpDpnURIs, cdpDpnURICount, cdpDpnUPNs, cdpDpnUPNCount, cdpDpnGUIDs, cdpDpnGUIDCount, cdpCrlIssuerDirectoryNames, cdpCrlIssuerDirectoryNameCount, cdpCrlIssuerRFC822Names, cdpCrlIssuerRFC822NameCount, cdpCrlIssuerDNSNames, cdpCrlIssuerDNSNameCount, cdpCrlIssuerURIs, cdpCrlIssuerURICount, cdpCrlIssuerUPNs, cdpCrlIssuerUPNCount, cdpCrlIssuerGUIDs, cdpCrlIssuerGUIDCount

		b64Cert = "MIIErjCCBFigAwIBAgIQGHEY5oDftsIV0py4fTS4DTANBgkqhkiG9w0BAQUFADBDMREwDwYDVQQKEwhWZXJpU2lnbjEuMCwGA1UECxMlVmVyaVNpZ24gQ2xhc3MgMiBPblNpdGUgSW5kaXZpZHVhbCBDQTAeFw0wMzA3MjQwMDAwMDBaFw0wNDA3MjMyMzU5NTlaMDYxDTALBgNVBAoTBHRlc3QxFjAUBgNVBAsTDXRlc3QgcHVycG9zZXMxDTALBgNVBAMTBG5vZG4wgZ8wDQYJKoZIhvcNAQEBBQADgY0AMIGJAoGBAMPzcuRlLfKJ222tESbbDg4uw1mPgQI/jNVliTNCUhl5X4j6UqWaFoMq76D4nLvbBHwF0EoCAr7ZLCQ9p5qIAj1gWc1dEQbgLDLqdXvsvhDZOHrvKm0AdoGtmx+INO5sWpopemdyZTjaoCA/JmMgULMh53iwu4KOal51a0NE7vFTAgMBAAGjggLvMIIC6zALBgNVHQ8EBAMCAf4wEQYJYIZIAYb4QgEBBAQDAgeAMFkGA1UdJQRSMFAGCCsGAQUFBwMBBggrBgEFBQcDAgYIKwYBBQUHAwMGCCsGAQUFBwMEBggrBgEFBQcDBQYIKwYBBQUHAwYGCCsGAQUFBwMHBggrBgEFBQcDCDCCASwGA1UdEQSCASMwggEfgRVhamF5YXJhbUB2ZXJpc2lnbi5jb22CEHd3dy52ZXJpc2lnbi5jb22GgbdsZGFwOi8vL0NOPUFQUkclMjBNQUlOLENOPWFwcmctc3ZyLTIwMDMsQ049Q0RQLENOPVB1YmxpYyUyMEtleSUyMFNlcnZpY2VzLENOPVNlcnZpY2VzLENOPUNvbmZpZ3VyYXRpb24sREM9QVBSRyxEQz1sb2NhbD9jZXJ0aWZpY2F0ZVJldm9jYXRpb25MaXN0P2Jhc2U/b2JqZWN0Q2xhc3M9Y1JMRGlzdHJpYnV0aW9uUG9pbnSGOmh0dHA6Ly9hcHJnLXN2ci0yMDAzLmFwcmcubG9jYWwvQ2VydEVucm9sbC9BUFJHJTIwTUFJTi5jcmwwggE8BgNVHR8EggEzMIIBLzCCASugggEjoIIBH4EVYWpheWFyYW1AdmVyaXNpZ24uY29tghB3d3cudmVyaXNpZ24uY29thoG3bGRhcDovLy9DTj1BUFJHJTIwTUFJTixDTj1hcHJnLXN2ci0yMDAzLENOPUNEUCxDTj1QdWJsaWMlMjBLZXklMjBTZXJ2aWNlcyxDTj1TZXJ2aWNlcyxDTj1Db25maWd1cmF0aW9uLERDPUFQUkcsREM9bG9jYWw/Y2VydGlmaWNhdGVSZXZvY2F0aW9uTGlzdD9iYXNlP29iamVjdENsYXNzPWNSTERpc3RyaWJ1dGlvblBvaW50hjpodHRwOi8vYXByZy1zdnItMjAwMy5hcHJnLmxvY2FsL0NlcnRFbnJvbGwvQVBSRyUyME1BSU4uY3JsgQIB/jANBgkqhkiG9w0BAQUFAANBAJwcfBDxO9V58RJcgZJPY/y5F6mxtZ/Wtk4dvhPcEtWuEh9iKuhhNDaTT961BviBKf0tR/Abyt/F51YmvqBsRWM="

		Response.Write  "Sample Cert with v3 Extensions:" & b64Cert & "<br>"

        result = ptaObj.vPKIParseB64CertEx(b64Cert, emailAddress, cn, title, uniqueID, address, organization, organizationUnits, orgUnitCount, issOrg, issLocality, issCountry, issCommonName, issOrgUnits, issOrgUnitCount, notBefore, notAfter, keyUsage, extendedKeyUsage, sanDirectoryNames, sanDirectoryNameCount, sanRFC822Names, sanRFC822NameCount, sanDNSNames, sanDNSNameCount, sanURIs, sanURICount, sanUPNs, sanUPNCount, sanGUIDs, sanGUIDCount, cdpDpnDirectoryNames, cdpDpnDirectoryNameCount, cdpDpnRFC822Names, cdpDpnRFC822NameCount, cdpDpnDNSNames, cdpDpnDNSNameCount, cdpDpnURIs, cdpDpnURICount, cdpDpnUPNs, cdpDpnUPNCount, cdpDpnGUIDs, cdpDpnGUIDCount, cdpCrlIssuerDirectoryNames, cdpCrlIssuerDirectoryNameCount, cdpCrlIssuerRFC822Names, cdpCrlIssuerRFC822NameCount, cdpCrlIssuerDNSNames, cdpCrlIssuerDNSNameCount, cdpCrlIssuerURIs, cdpCrlIssuerURICount, cdpCrlIssuerUPNs, cdpCrlIssuerUPNCount, cdpCrlIssuerGUIDs, cdpCrlIssuerGUIDCount)
        Response.Write  "vPKIParseB64CertEx    :" & result & "<br>"       
        Response.Write  "email address      :" & emailAddress & "<br>"
		Response.Write  "cn                 :" & cn & "<br>"
		Response.Write  "title              :" & title & "<br>"
		Response.Write  "uniqueID           :" & uniqueID & "<br>"
		Response.Write  "address            :" & address & "<br>"
		Response.Write  "organization       :" & organization & "<br>"
		For index=0 To orgUnitCount-1
		    Response.Write  "organizationUnits " & index & ": " & organizationUnits(index) & "<br>"
		Next
		Response.Write  "orgUnitCount       :" & orgUnitCount & "<br>"
		Response.Write  "issOrg             :" & issOrg & "<br>"
		Response.Write  "issLocality        :" & issLocality & "<br>"
		Response.Write  "issCountry         :" & issCountry & "<br>"
		Response.Write  "issCommonName      :" & issCommonName & "<br>"
		Response.Write  "issOrgUnitCount    :" & issOrgUnitCount & "<br>"
		For index=0 To issOrgUnitCount-1
		    Response.Write  "issOrganizationUnits " & index & ": " & issOrgUnits(index) & "<br>"
		Next		
		Response.Write  "notBefore          :" & notBefore & "<br>"
		Response.Write  "notAfter           :" & notAfter & "<br>"


		Response.Write "keyUsage 			:" & keyUsage & "<br>"
		Response.Write "extendedKeyUsage	:" & extendedKeyUsage & "<br>"
		Response.Write "sanDirectoryNameCount: " & sanDirectoryNameCount & "<br>"
		For index=0 To sanDirectoryNameCount-1
			Response.Write "sanDirectoryNames " & index & ": " & sanDirectoryNames(index) & "<br>"
		Next				
		Response.Write "sanRFC822NameCount: " & sanRFC822NameCount & "<br>"
		For index=0 To sanRFC822NameCount-1
			Response.Write "sanRFC822Names " & index & ": " & sanRFC822Names(index) & "<br>"
		Next				
		Response.Write "sanDNSNameCount: " & sanDNSNameCount & "<br>"
		For index=0 To sanDNSNameCount-1
			Response.Write "sanDNSNames " & index & ": " & sanDNSNames(index) & "<br>"
		Next				
		Response.Write "sanURICount: " & sanURICount & "<br>"
		For index=0 To sanURICount-1
			Response.Write "sanURIs " & index & ": " & sanURIs(index) & "<br>"
		Next				
		Response.Write "sanUPNCount: " & sanUPNCount & "<br>"
		For index=0 To sanUPNCount-1
			Response.Write "sanUPNs " & index & ": " & sanUPNs(index) & "<br>"
		Next				
		Response.Write "sanGUIDCount: " & sanGUIDCount & "<br>"
		For index=0 To sanGUIDCount-1
			Response.Write "sanGUIDs " & index & ": " & sanGUIDs(index) & "<br>"
		Next				
		Response.Write "cdpDpnDirectoryNameCount: " & cdpDpnDirectoryNameCount & "<br>"
		For index=0 To cdpDpnDirectoryNameCount-1
			Response.Write "cdpDpnDirectoryNames " & index & ": " & cdpDpnDirectoryNames(index) & "<br>"
		Next				
		Response.Write "cdpDpnRFC822NameCount: " & cdpDpnRFC822NameCount & "<br>"
		For index=0 To cdpDpnRFC822NameCount-1
			Response.Write "cdpDpnRFC822Names " & index & ": " & cdpDpnRFC822Names(index) & "<br>"
		Next				
		Response.Write "cdpDpnDNSNameCount: " & cdpDpnDNSNameCount & "<br>"
		For index=0 To cdpDpnDNSNameCount-1
			Response.Write "cdpDpnDNSNames " & index & ": " & cdpDpnDNSNames(index) & "<br>"
		Next				
		Response.Write "cdpDpnURICount: " & cdpDpnURICount & "<br>"
		For index=0 To cdpDpnURICount-1
			Response.Write "cdpDpnURIs " & index & ": " & cdpDpnURIs(index) & "<br>"
		Next				
		Response.Write "cdpDpnUPNCount: " & cdpDpnUPNCount & "<br>"
		For index=0 To cdpDpnUPNCount-1
			Response.Write "cdpDpnUPNs " & index & ": " & cdpDpnUPNs(index) & "<br>"
		Next				
		Response.Write "cdpDpnGUIDCount: " & cdpDpnGUIDCount & "<br>"
		For index=0 To cdpDpnGUIDCount-1
			Response.Write "cdpDpnGUIDs " & index & ": " & cdpDpnGUIDs(index) & "<br>"
		Next				
		Response.Write "cdpCrlIssuerDirectoryNameCount: " & cdpCrlIssuerDirectoryNameCount & "<br>"
		For index=0 To cdpCrlIssuerDirectoryNameCount-1
			Response.Write "cdpCrlIssuerDirectoryNames " & index & ": " & cdpCrlIssuerDirectoryNames(index) & "<br>"
		Next				
		Response.Write "cdpCrlIssuerRFC822NameCount: " & cdpCrlIssuerRFC822NameCount & "<br>"
		For index=0 To cdpCrlIssuerRFC822NameCount-1
			Response.Write "cdpCrlIssuerRFC822Names " & index & ": " & cdpCrlIssuerRFC822Names(index) & "<br>"
		Next				
		Response.Write "cdpCrlIssuerDNSNameCount: " & cdpCrlIssuerDNSNameCount & "<br>"
		For index=0 To cdpCrlIssuerDNSNameCount-1
			Response.Write "cdpCrlIssuerDNSNames " & index & ": " & cdpCrlIssuerDNSNames(index) & "<br>"
		Next				
		Response.Write "cdpCrlIssuerURICount: " & cdpCrlIssuerURICount & "<br>"
		For index=0 To cdpCrlIssuerURICount-1
			Response.Write "cdpCrlIssuerURIs " & index & ": " & cdpCrlIssuerURIs(index) & "<br>"
		Next				
		Response.Write "cdpCrlIssuerUPNCount: " & cdpCrlIssuerUPNCount & "<br>"
		For index=0 To cdpCrlIssuerUPNCount-1
			Response.Write "cdpCrlIssuerUPNs " & index & ": " & cdpCrlIssuerUPNs(index) & "<br>"
		Next
		Response.Write "cdpCrlIssuerGUIDCount: " & cdpCrlIssuerGUIDCount & "<br>"						
		For index=0 To cdpCrlIssuerGUIDCount-1
			Response.Write "cdpCrlIssuerGUIDs " & index & ": " & cdpCrlIssuerGUIDs(index) & "<br>"
		Next				
	    Response.Write "<br>"

        Set ptaObj = nothing
		Response.Write "**************************************************<br>"
		
		Response.Write "**************************************************<br>"
		Response.Write "</html>"

Function Encode64(InputStr(), len) 
	Dim State 
	Dim i
	Dim current
	Dim old
	Dim first_new
	Dim second_new
	Dim Output
	Dim Base64
	Base64 = Array("A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K","L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y","Z", "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m","n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "0","1", "2", "3", "4", "5", "6", "7", "8", "9", "+", "/")
    State = 0
	Output = ""
	For i = 0 To len-1  
	State = State + 1  
	Select Case State  
	Case 1  current = InputStr(i) 'Asc(Mid(InputStr, i, 1))  
			first_new = Base64((Int(current /4) And &H3F)) 
			Output = Output & first_new  
			'Response.Write "first:"& first_new & "<<br>"
	Case 2  current =InputStr(i) 'Asc(Mid(InputStr, i, 1))  
			first_new = Base64((((old * 16) And &H30) Or ((Int(current / 16) And &HF))))  
			'Response.Write "first case2:"& first_new & "<<br>"
			Output = Output & first_new  
	Case 3: current = InputStr(i) 'Asc(Mid(InputStr, i, 1))  
			first_new = Base64((((old * 4) And&H3C) Or ((Int(current / 64) And &H3))))  
			second_new = Base64((current And &H3F))	
			Output = Output & first_new & second_new  
			'Response.Write "first case3 :"& first_new &"second:" & second_new & "<<br>"
			State = 0  
	End Select 
			old = current  
	Next  
	'Response.Write "output:" & Output & "<<br>"
	Select Case State	
	Case 1	first_new = Base64(((old*16) And &H30))  
			Output = Output & first_new & "=="  
	Case 2  first_new =Base64(((old * 4) And &H3C))  
			Output = Output & first_new & "="  
	End Select	
	Encode64 = Output 

End Function
%>


