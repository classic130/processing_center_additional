<!-- VSSKBEGINPOLICYVAL#policy#1 -->
<!-- VSSKENDPOLICYVAL#policy#1 -->


<!-- VSSKBEGINPOLICYVAL#policy#2 -->
      cryptoProvName = "%%provName%%"
      cryptoProvType = 1
 
      If isRunningOnVista = 0 Then
      if VerifyProvider(cryptoProvName, cryptoProvType) = 1 then
         On Error resume next
         cenroll.providerType = cryptoProvType
         cenroll.providerName = cryptoProvName
      else
         On Error resume next
         cenroll.providerType = 1
         cenroll.providerName = "Microsoft Base Cryptographic Provider v1.0"
       end if
      Else
            If VerifyProviderOnVista(cryptoProvName, cryptoProvType) = 1 Then
                forceProviderName = cryptoProvName
                forceProviderType = cryptoProvType
            Else
                forceProviderName = "Microsoft Base Cryptographic Provider v1.0"
                forceProviderType = 1
            End If
       End If
<!-- VSSKENDPOLICYVAL#policy#2 -->



<!-- VSSKBEGINPOLICYVAL#policy#3 -->
 Sub FindProviders

 End Sub

Function VerifyProvider (provName, provType)   'return 1 if provider exists
                                           '       0 otherwise
   Dim i,j
   Dim temp
   i=0

   On Error Resume Next

   VerifyProvider = 0
 
   Do While True
      temp = ""
      cenroll.providerType = provType    
      temp = cenroll.enumProviders(i,0)
      If Len(temp) = 0 Then
         Exit Function
      Else
         If temp = provName Then
            VerifyProvider = 1
            Exit Function
         End If
         i=i+1
      End If
   Loop
 End Function

 
 Function VerifyProviderOnVista (provName, provType)   'return 1 if provider exists
                                                       '0 otherwise
      Dim cspInfos
      Dim cspCount


      spnCertEnroll.innerHTML="<OBJECT id='g_objClassFactory' CLASSID='clsid:884e2049-217d-11da-b2a4-000e7bbb2b09'></OBJECT>"

      VerifyProviderOnVista = 0

      On Error Resume Next
      Set cspInfos = g_objClassFactory.CreateObject("X509Enrollment.CCspInformations")

      If ( err.number <> 0 ) then 
          MsgBox Err.Number & " " & Err.Description
          window.navigate("../error/MSEnrollError.htm")
      End If

      On Error Resume Next
      cspInfos.AddAvailableCsps()

      If ( err.number <> 0 ) then 
          MsgBox Err.Number & " " & Err.Description
          Exit Function
      End If

      cspCount = cspInfos.Count

      Dim cspInfo
      Dim i

      i = 1
      Do While True
        If i > cspCount Then
  	      Exit Do
        End If

        set cspInfo = cspInfos.ItemByIndex(i)

        If cspInfo.Type = 1 Then
	        If Len( cspInfo.Name) = 0 Then
	          Exit Function
	        Else
            If  cspInfo.Name = provName Then
	            VerifyProviderOnVista = 1
              Exit Function
            End If
          End If
        End If
        
        i = i + 1
      Loop
End Function


<!-- VSSKENDPOLICYVAL#policy#3 -->


<!-- VSSKBEGINPOLICYVAL#policy#4 -->
<!-- VSSKENDPOLICYVAL#policy#4 -->


<!-- VSSKBEGINPOLICYVAL#policy#5#1.2.0.4 -->
  var selectedProv;
  
  if(browserNum < 5)
  {
	selectedProv = new java.lang.StringBuffer("%%provName%%");
  }
  else
  {
	selectedProv = new String("%%provName%%");
  }
  
  function VerifyProvider(policyProviderName)
  {
    var ProviderType ;
    var ErrorCode ;
    var ProviderName;
    var found = false;

    ProviderIndex = 0 ;
    ProviderType = 1 ;		// Support PROV_RSA_FULL only

    //document.NSCP_IVSPTA.PTA_Initialize("", 1) ;
    //if ( (ErrorCode = document.NSCP_IVSPTA.GetLastError()) != 0)
    //{
    //  alert ("Error in NSCP_IVSPTA.PTA_Initialize : " + ErrorCode) ;
    //  return false;
   // }

    // Set the Provider Type
    document.NSCP_IVSPTA.set_XEnroll_ProviderType(ProviderType) ;
    if ( (ErrorCode = document.NSCP_IVSPTA.GetLastError()) != 0)
    {
      alert ("Error in NSCP_IVSPTA.set_XEnroll_ProviderType : " + ErrorCode) ;
      return false;
    }

    while(true)
    {
      ProviderName = document.NSCP_IVSPTA.XEnroll_enumProviders(ProviderIndex, 0) ;
      if ( (ErrorCode = document.NSCP_IVSPTA.GetLastError()) != 0)
      {
        if ( ErrorCode != 0x80070103 )
        {
          alert ("Error in NSCP_IVSPTA.set_XEnroll_ProviderType : " + ErrorCode) ;
          return false;
        }
        else
          break ;
      }
      if(browserNum < 5) {

	  	if(!ProviderName.compareTo(policyProviderName))
		{
			found = true;	
		}
     } else {
		if(ProviderName == policyProviderName)
		{
			found = true;
		}
     }

      // alert ("ProviderNAme : " + CryptProvArray[ProviderIndex+1] + "\nProviderIndex : " + ProviderIndex) ;

      ProviderIndex = ProviderIndex + 1 ;
    }

    //document.NSCP_IVSPTA.PTA_Close() ;
    //if ( (ErrorCode = document.NSCP_IVSPTA.GetLastError()) != 0)
    //{
    //  alert ("Error in NSCP_IVSPTA.PTA_Close : " + ErrorCode) ;
    //  return false;
    //}
    
    return found;
  }


  function setSelectedProvider()
  {
    return;
  }

  function DetectCryptProv()
  {
    return ;
  }

  function InsertCryptProv()
  {
     return;
  }
<!-- VSSKENDPOLICYVAL#policy#5 -->


<!-- VSSKBEGINPOLICYVAL#policy#6 -->
Dim CryptProvider
CryptProvider="%%provName%%"
'-- VSSKBEGIN Enrollment/KeyLength#3 --
'-- VSSKEND Enrollment/KeyLength#3 --
<!-- VSSKENDPOLICYVAL#policy#6 -->
