<!-- VSSKBEGINPOLICYVAL#2048#1 -->
  If isRunningOnVista = 0 Then
      cenroll.GenKeyFlags = &h08000000 OR keyflags
      CreateP10 = cenroll.CreatePKCS10("CN=vsc1enroll", "1.3.6.1.5.5.7.3.2")    
      if Len(CreateP10) <> 0 Then Exit Function
    
      if %%bDegrade%% Then 
         cenroll.GenKeyFlags = &h04000000 OR keyflags
         CreateP10 = cenroll.CreatePKCS10("CN=vsc1enroll", "1.3.6.1.5.5.7.3.2")    
         if Len(CreateP10) <> 0 Then Exit Function
         cenroll.GenKeyFlags = &h02000000 OR keyflags                   
         CreateP10 = cenroll.CreatePKCS10("CN=vsc1enroll", "1.3.6.1.5.5.7.3.2")
         if Len(CreateP10) <> 0 Then Exit Function
         cenroll.GenKeyFlags = &h00000000 OR keyflags                   
         CreateP10 = cenroll.CreatePKCS10("CN=vsc1enroll", "1.3.6.1.5.5.7.3.2")
      End If
  Else
    Dim selectedCSP
    const CRYPT_STRING_BASE64 = 1
    const contextUser = 1
    
    set selectedCSP = g_objClassFactory.CreateObject("X509Enrollment.CCspInformation")
    
    If forceProviderName <> "" Then
        selectedCSP.InitializeFromName(forceProviderName)
    Else
        if browserVer > requiredBrowserNumMS Then
            On Error Resume Next
            set options = document.all.cryptProv.options
            index = options.selectedIndex
            selectedCSP.InitializeFromName(options(index).text)
        else
            On Error resume next
            selectedCSP.InitializeFromName("Microsoft Base Cryptographic Provider v1.0")
        end if
    End If
    
    ' Private key related settings
    dim objPrivateKey
    set objPrivateKey = g_objClassFactory.CreateObject("X509Enrollment.CX509PrivateKey")
   
    objPrivateKey.CspInformations = g_objClassFactory.CreateObject("X509Enrollment.CCspInformations")
    objPrivateKey.CspInformations.Add(selectedCSP)
    
    If (keyflags AND 2) = 2 Then
        objPrivateKey.KeyProtection = 1
    Else
        objPrivateKey.KeyProtection = 0
    End If
    
    If (keyflags AND 1) = 1 Then
        objPrivateKey.ExportPolicy = 1
    Else
        objPrivateKey.ExportPolicy = 0
    End If
        
    objPrivateKey.Length = 2048
    objPrivateKey.keySpec = 2
    
    ' Initialize P10 based on private key
    dim objRequest
    set objRequest = g_objClassFactory.CreateObject("X509Enrollment.CX509CertificateRequestPkcs10")
    If ( err.number <> 0 ) then
               MsgBox("The error: " + err.description + " " + err.number + " occurred in generating the certificate request")              
               window.navigate("../error/MSEnrollError.htm")
    End If
    call objRequest.InitializeFromPrivateKey(contextUser, objPrivateKey, "")
    
    ' 1.3.6.1.5.5.7.3.2 Oid - Extension
    Dim extensionTemplate1
    set extensionTemplate1 = g_objClassFactory.CreateObject("X509Enrollment.CX509ExtensionTemplateName")
    'MsgBox "Create Extn Object - Error # " & CStr(Err.Number) & " " & Err.Description
    extensionTemplate1.InitializeEncode("1.3.6.1.5.5.7.3.2")
    'MsgBox "InitializeEncode Extn - Error # " & CStr(Err.Number) & " " & Err.Description

    objRequest.X509Extensions.Add(extensionTemplate1)
    
    ' DN related stuff
    Dim objDn
    set objDn = g_objClassFactory.CreateObject("X509Enrollment.CX500DistinguishedName")
    call objDn.Encode(strDN, XCN_CERT_NAME_STR_NONE)
    'MsgBox "Encode for Dn - Error # " & CStr(Err.Number) & " " & Err.Description

    objRequest.subject = objDn
    'MsgBox "set subject Dn - Error # " & CStr(Err.Number) & " " & Err.Description

    dim objEnroll
    set objEnroll = g_objClassFactory.CreateObject("X509Enrollment.CX509Enrollment")
    objEnroll.InitializeFromRequest(objRequest)
    'MsgBox "InitializeFromRequest - Error # " & CStr(Err.Number) & " " & Err.Description

    dim pkcs10
    pkcs10 = objEnroll.CreateRequest(CRYPT_STRING_BASE64)
    If ( err.number <> 0 ) then
                   MsgBox("The error: " + err.description + " " + err.number + " occurred in generating the certificate request")              
                   window.navigate("../error/MSEnrollError.htm")
    End If

    CreateP10 = pkcs10
  
  End If
<!-- VSSKENDPOLICYVAL#2048#1 -->

<!-- VSSKBEGINPOLICYVAL#2048#2 -->
function CreateP10Java(KeyFlags)
{
    PKCS10 = "";

    // Set the Key Gen Flags
    document.NSCP_IVSPTA.set_XEnroll_GenKeyFlags(0x08000000 | KeyFlags) ;
    if ( (ErrorCode = document.NSCP_IVSPTA.GetLastError()) != 0)
    {
      return(PKCS10) ;
    }

    // Create the PKCS10
    PKCS10 = document.NSCP_IVSPTA.XEnroll_createPKCS10("CN=vsc1enroll", "1.3.6.1.5.5.7.3.2") ;
    if ( (ErrorCode = document.NSCP_IVSPTA.GetLastError()) != 0)
    {
	if(%%bDegrade%%)
	{

	        // Set the Key Gen Flags
		document.NSCP_IVSPTA.set_XEnroll_GenKeyFlags(0x04000000 | KeyFlags) ;
		if ( (ErrorCode = document.NSCP_IVSPTA.GetLastError()) != 0)
		{
		  PKCS10 = "";
		  return(PKCS10) ;
		}

	        // Create the PKCS10
        	PKCS10 = document.NSCP_IVSPTA.XEnroll_createPKCS10("CN=vsc1enroll", "1.3.6.1.5.5.7.3.2") ;
                if ( (ErrorCode = document.NSCP_IVSPTA.GetLastError()) != 0)
                {

	            // Set the Key Gen Flags
        	    document.NSCP_IVSPTA.set_XEnroll_GenKeyFlags(0x02000000 | KeyFlags) ;
	            if ( (ErrorCode = document.NSCP_IVSPTA.GetLastError()) != 0)
        	    {
		      PKCS10 = "";
        	      return(PKCS10) ;
	            }

	            // Create the PKCS10
        	    PKCS10 = document.NSCP_IVSPTA.XEnroll_createPKCS10("CN=vsc1enroll", "1.3.6.1.5.5.7.3.2") ;
                    if ( (ErrorCode = document.NSCP_IVSPTA.GetLastError()) != 0)
                    {
                        // Set the Key Gen Flags
        	        document.NSCP_IVSPTA.set_XEnroll_GenKeyFlags(0x00000000 | KeyFlags) ;
	                if ( (ErrorCode = document.NSCP_IVSPTA.GetLastError()) != 0)
           	        {
		           PKCS10 = "";
        	           return(PKCS10) ;
	                }
                        // Create the PKCS10
            	        PKCS10 = document.NSCP_IVSPTA.XEnroll_createPKCS10("CN=vsc1enroll", "1.3.6.1.5.5.7.3.2") ;
                        if ( (ErrorCode = document.NSCP_IVSPTA.GetLastError()) != 0)
                        {
                           PKCS10 = "";
                           return(PKCS10);
                        }
                        return (PKCS10);
                    }
   	            return(PKCS10) ;
		}
   	        return(PKCS10) ;

	}
	else
	{
		PKCS10 = "";
		return PKCS10;
	}
    }
    return (PKCS10) ;
  }
<!-- VSSKENDPOLICYVAL#2048#2 -->


<!-- VSSKBEGINPOLICYVAL#2048#3 -->
Dim bKeyGenSuccess
Dim bKeyGen
Dim keyflags
Dim keygenflags
keyflags=0

'-- VSSKBEGIN Enrollment/KeyExportable#1 --
'-- VSSKEND Enrollment/KeyExportable#1 --

keygenflags = keyflags OR &h08000000
bKeyGenSuccess=ConfChk.CheckKeyGen(CryptProvider, keygenflags)
if bKeyGenSuccess <> 0 then
   if %%bDegrade%% Then
      keygenflags = keyflags OR &h04000000
      bKeyGenSuccess=ConfChk.CheckKeyGen(CryptProvider, keygenflags)
      if bKeyGenSuccess <> 0 then
        keygenflags = keyflags OR &h02000000
        bKeyGenSuccess=ConfChk.CheckKeyGen(CryptProvider, keygenflags)
        if bKeyGenSuccess <> 0 then
          keygenflags = keyflags OR &h00000000
          bKeyGenSuccess=ConfChk.CheckKeyGen(CryptProvider, keygenflags)
          if bKeyGenSuccess <> 0 then
             bKeyGen = FALSE
          else
             bKeyGen = TRUE
          end if
        else
	  bKeyGen = TRUE
        end if 
      else
	bKeyGen = TRUE
      end if 
   else
     bKeyGen = FALSE
   end if
else
    bKeyGen = TRUE
end if
<!-- VSSKENDPOLICYVAL#2048#3 -->

<!-- VSSKBEGINPOLICYVAL#2048#4 -->
    Dim KeyAttributes
    ' for 2048 bit keys
    KeyAttributes = KeyFlags OR &h08000000
    On Error Resume Next
    CreatePKCS10 = IVSPTA.CreateCertReq (SubjectDN, KeyAttributes, HashAlg, Attributes)
<!-- VSSKENDPOLICYVAL#2048#4 -->

<!-- VSSKBEGINPOLICYVAL#2048#5 -->
   var KeyAttributes;
   KeyAttributes = 0x08000000 | KeyFlags;
   if(browserNum < 5)
   {
	PKCS10 = document.NSCP_IVSPTA.PTA_CreateCertReq(SubjectDN, KeyAttributes, HashAlg, theArray) ;
   } 
   else
   {
	PKCS10 = document.NSCP_IVSPTA.PTA_CreateCertReq(SubjectDN, KeyAttributes, HashAlg, 4, theArray) ;
   }
<!-- VSSKENDPOLICYVAL#2048#5 -->

<!-- VSSKBEGINPOLICYVAL#2048#6 -->
CONST keySize  2048
<!-- VSSKENDPOLICYVAL#2048#6 -->
