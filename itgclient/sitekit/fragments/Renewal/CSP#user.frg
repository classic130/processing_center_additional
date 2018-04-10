<!-- VSSKBEGINPOLICYVAL#user#1 -->
<!-- FindProviders() routine is called on load to fill the list -->
<TABLE WIDTH=588 BGCOLOR="ffffcc" CELLPADDING=7 CELLSPACING=0 BORDER=0>
<TR>
<TD WIDTH=588>
<FONT SIZE=2 FACE="verdana, arial, helvetica"><B>Optional: Select The Cryptographic Service </B></FONT><BR>
<FONT FACE="arial, helvetica" SIZE=2>If you have a domestic version of this browser you are offered an Enhanced Cryptographic option which
	provides 1024-bit key encryption. The MS Base Cryptographic provider offers 512-bit key encryption which is adequate for most
	applications today, but you may select the Enhanced option if your browser offers this choice and you require the higher encryption
        strength. If you use a specialized mechanism such as a smartcard, please select the appropriate provider as directed by the manufacturer.
<BR></FONT>
<P>
<CENTER>
     <!--BEGIN INPUT FIELD TABLE-->
     <TABLE WIDTH=574 CELLPADDING=3 CELLSPACING=2 BORDER=0> 
     <TR>
     <TD WIDTH=50% BGCOLOR="ffcc00"><FONT FACE="verdana, arial, helvetica" SIZE=2><B>Cryptographic Service Provider Name</B><BR></FONT></TD>
     <TD COLSPAN=2 WIDTH=50% BGCOLOR="ffcc00">
         <SELECT NAME="cryptProv">
         <OPTION SELECTED VALUE="1">Microsoft Base Cryptographic Provider v1.0
	 </SELECT></TD>
     </TR>
     </TABLE>
     <!--END INPUT FIELD TABLE-->
</TD>
</TR>
</TABLE> 
<!-- VSSKENDPOLICYVAL#user#1 -->



<!-- VSSKBEGINPOLICYVAL#user#2#1.0.0.1 -->
      if isRunningOnVista = 0 Then
         if IsIE4orLater() Then
         On Error Resume Next
         set options = document.all.cryptProv.options
         index = options.selectedIndex
         cenroll.providerName = options(index).text
         cenroll.providerType = options(index).value
      else
         On Error resume next
         cenroll.providerType = 1
         cenroll.providerName = "Microsoft Base Cryptographic Provider v1.0"
       end if
    end if
<!-- VSSKENDPOLICYVAL#user#2 -->


<!-- VSSKBEGINPOLICYVAL#user#3 -->
  Sub FindProviders

    spnCertEnroll.innerHTML="<OBJECT id='g_objClassFactory' CLASSID='clsid:884e2049-217d-11da-b2a4-000e7bbb2b09'></OBJECT>"

    If isRunningOnVista = 0 Then
		  FindProvidersOnNonVista()
	  Else
		  FindProvidersOnVista()
	  End If
  End Sub
  
  Sub FindProvidersOnVista
		'MsgBox "Called FindProvidersOnVista"
		Dim cspInfos
		Dim cspCount
		On Error Resume Next
		
		Set cspInfos = g_objClassFactory.CreateObject("X509Enrollment.CCspInformations")
		
		
		If ( err.number <> 0 ) then 
                        MsgBox("The error: " + err.description + " " + err.number + " occurred in generating the certificate request")              
	                window.navigate("../error/MSEnrollError.htm")

          	End If
		
		On Error Resume Next
		'MsgBox "Adding"
		cspInfos.AddAvailableCsps()
		'MsgBox "Added"
		
		If ( err.number <> 0 ) then 
          MsgBox Err.Number & " " & Err.Description
          Exit Sub
		End If
		
		cspCount = cspInfos.Count
		'MsgBox "Count: " & cspCount
      
		Dim i
		Dim j
		Dim el
		Dim first
		
		i = 1
		j = 1
		first = 0
		
		Do While True
			If i = cspCount Then
			  Exit Do
			End If
			
			set cspInfo = cspInfos.ItemByIndex(i)
			'MsgBox "Name[" & i & "]: " & cspInfo.Name & ", Type: " & cspInfo.Type

			If cspInfo.Type = j Then
			  
				If Len( cspInfo.Name) = 0 Then
					If j < 1 Then          'Look for RSA_FULL only.
					  j = j + 1
					  i = 0 
					  'MsgBox j
					Else
					  Exit Sub
					End If
				Else
			  
					If cspInfo.Name <> "Microsoft Base Cryptographic Provider v1.0" Then
						set el = document.createElement("OPTION")
						el.text = cspInfo.Name
						el.value = j 
						document.all.cryptprov.add(el)
						count = count + 1
						If el.text = "%%preferredProv%%" Then
						  document.all.cryptprov.selectedIndex = count
						End If 
						If first = 0  Then
						  first = 1
						  document.all.cryptprov.selectedIndex = 0
						End If
					End If
					
				End If
			  
			  
			  
			End If
			i = i + 1
		  Loop

	
  End Sub
  
  Sub FindProvidersOnNonVista
  
	  'MsgBox "Called FindProvidersOnNonVista"
    Dim i, j, count
    Dim providers()
    i = 0
    j = 1
    count=0
    Dim el
    Dim temp
    Dim first 
    On Error Resume Next
    first =  0
    
    Do While True
      temp = ""
      cenroll.providerType = j
      temp = cenroll.enumProviders(i,0)
      If Len(Temp) = 0 Then
        If j < 1 Then          'Look for RSA_FULL only.
          j = j + 1
          i = 0 
        Else
          Exit Do
        End If
      Else
        set el = document.createElement("OPTION")
        el.text = temp
        el.value = j 
        document.all.cryptprov.add(el)
        count = count + 1
        If el.text = "%%preferredProv%%" Then
          document.all.cryptprov.selectedIndex = count
        End If 
        If first = 0  Then
          first = 1
          document.all.cryptprov.selectedIndex = 0
        End If
        i = i + 1
      End If
    Loop
  End Sub
<!-- VSSKENDPOLICYVAL#user#3 -->


<!-- VSSKBEGINPOLICYVAL#user#4 -->
<!-- VSSKENDPOLICYVAL#user#4 -->

// display the CSP...
<!-- VSSKBEGINPOLICYVAL#user#5 -->
<!--BEGIN IN TABLE THREE-->
<TABLE WIDTH=588 BGCOLOR="ffffcc" CELLPADDING=7 CELLSPACING=0 BORDER=0>
<TR>
<TD WIDTH=588>
<FONT SIZE=2 FACE="verdana, arial, helvetica"><B>Optional: Select The Cryptographic Service </B></FONT><BR>
<FONT FACE="arial, helvetica" SIZE=2>If you have a domestic version of this browser you are offered an Enhanced Cryptographic option which
	provides 1024-bit key encryption. The MS Base Cryptographic provider offers 512-bit key encryption which is adequate for most
	applications today, but you may select the Enhanced option if your browser offers this choice and you require the higher encryption
        strength. If you use a specialized mechanism such as a smartcard, please select the appropriate provider as directed by the manufacturer.
<BR></FONT>
<P>
<CENTER>
     <!--BEGIN INPUT FIELD TABLE-->
     <TABLE WIDTH=574 CELLPADDING=3 CELLSPACING=2 BORDER=0> 
     <TR>
     <TD WIDTH=50% BGCOLOR="ffcc00"><FONT FACE="verdana, arial, helvetica" SIZE=2><B>Cryptographic Service Provider Name</B><BR></FONT></TD>
     <TD COLSPAN=2 WIDTH=50% BGCOLOR="ffcc00">
         <SELECT NAME="cryptoProviders" onChange="setSelectedProvider();">
	  <SCRIPT LANGUAGE="JavaScript">
    		InsertCryptProv() ;
	  </SCRIPT>
	 </SELECT>
     </TD>
     </TR>
     </TABLE>
     <!--END INPUT FIELD TABLE-->
</TD>
</TR>
</TABLE> 
<BR><P><BR>
<!--END TABLE THREE-->
<!-- VSSKENDPOLICYVAL#user#5 -->


// for choosing the CSP 
<!-- VSSKBEGINPOLICYVAL#user#6#1.2.0.4 -->
  var ProviderName;
  var selectedProv;
  var CryptProvArray = new Array(10) ;
  var ProviderIndex ;

  if(browserNum < 5)
  {
	ProviderName = new java.lang.StringBuffer("") ;
	selectedProv = new java.lang.StringBuffer("Microsoft Enhanced Cryptographic Provider v1.0") ;
  }
  else
  {
	ProviderName = new String("") ;
	selectedProv = new String("Microsoft Enhanced Cryptographic Provider v1.0") ;
  }
  
  function setSelectedProvider()
  {
    selectedProv = document.Renewal.cryptoProviders[document.Renewal.cryptoProviders.selectedIndex].value ;
  }

  function VerifyProvider(policyProviderName)
  {
	return true;    
  }

  function DetectCryptProv()
  {
    // alert ("From InitCryptProv ...") ;

    var ProviderType ;
    var first ;
    var ErrorCode ;

    first =  0 ;
    ProviderIndex = 0 ;
    ProviderType = 1 ;		// Support PROV_RSA_FULL only

    InitPlugin();
    
    //document.NSCP_IVSPTA.PTA_Initialize("", 1) ;
    //if ( (ErrorCode = document.NSCP_IVSPTA.GetLastError()) != 0)
    //{
    //  alert ("Error in NSCP_IVSPTA.PTA_Initialize : " + ErrorCode) ;
    //  return ;
    //}

    // Set the Provider Type
    document.NSCP_IVSPTA.set_XEnroll_ProviderType(ProviderType) ;
    if ( (ErrorCode = document.NSCP_IVSPTA.GetLastError()) != 0)
    {
      alert ("Error in NSCP_IVSPTA.set_XEnroll_ProviderType : " + ErrorCode) ;
      return ;
    }

    while(true)
    {
      CryptProvArray[ProviderIndex+1] = document.NSCP_IVSPTA.XEnroll_enumProviders(ProviderIndex, 0) ;
      if ( (ErrorCode = document.NSCP_IVSPTA.GetLastError()) != 0)
      {
        if ( ErrorCode != 0x80070103 )
        {
          alert ("Error in NSCP_IVSPTA.set_XEnroll_ProviderType : " + ErrorCode) ;
          return ;
        }
        else
          break ;
      }

      // alert ("ProviderNAme : " + CryptProvArray[ProviderIndex+1] + "\nProviderIndex : " + ProviderIndex) ;

      ProviderIndex = ProviderIndex + 1 ;
    }

    //document.NSCP_IVSPTA.PTA_Close() ;
    //if ( (ErrorCode = document.NSCP_IVSPTA.GetLastError()) != 0)
    //{
    //  alert ("Error in NSCP_IVSPTA.PTA_Close : " + ErrorCode) ;
    //  return ;
    //}
  }

  function InsertCryptProv()
  {
    var length, i ;
    var tmpStr ;
    var re = /Netscape/i ;
    var DefProvString;

    if(browserNum < 5)
    {
     DefProvString = new java.lang.String("%%preferredProv%%") ;
    }
    else
    {
	 DefProvString = new String("%%preferredProv%%") ;
    }
    
    for ( i = 0 ; i < ProviderIndex ; i++ )
    {
      tmpStr = CryptProvArray[i+1] ;

      // Set the default if detected
      if (browserNum < 5) {
	if (DefProvString.equals(CryptProvArray[i+1]) != true )
           document.write ("<OPTION VALUE=\"" + tmpStr + "\">" + tmpStr + "\n") ;
        else
          document.write ("<OPTION SELECTED VALUE=\"" + tmpStr + "\">" + tmpStr + "\n") ;
      } else {
	if (DefProvString != CryptProvArray[i+1])
           document.write ("<OPTION VALUE=\"" + tmpStr + "\">" + tmpStr + "\n") ;
        else
          document.write ("<OPTION SELECTED VALUE=\"" + tmpStr + "\">" + tmpStr + "\n") ;
      }
    }
  }
<!-- VSSKENDPOLICYVAL#user#6 -->


<!-- VSSKBEGINPOLICYVAL#user#7 -->
<!-- VSSKENDPOLICYVAL#user#7 -->

<!-- VSSKBEGINPOLICYVAL#user#8 -->
      document.theform.Accept.disabled = true
<!-- VSSKENDPOLICYVAL#user#8 -->
