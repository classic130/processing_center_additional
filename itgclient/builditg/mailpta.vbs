'Body of email message
Dim msgBody,ArgNum
Dim cvsTag
Dim staticTag
Dim cdLocation
Dim filelocation
Dim fileAttached 
Dim errorFlag

fileAttached = ""
errorFlag = "pass" 
Set oArgs = WScript.Arguments
ArgNum = 0
While ArgNum < oArgs.Count
	Select Case LCase(oArgs(ArgNum))
		Case "--tagname","-t":
			ArgNum = ArgNum + 1
                        cvsTag = oArgs(ArgNum) 
                Case "--statictag","-s":
                        ArgNum = ArgNum + 1
                        staticTag = oArgs(ArgNum)
                Case "--location","-l":
                        ArgNum = ArgNum + 1
                        cdLocation = oArgs(ArgNum)
                Case "--attach","-a":
                        ArgNum = ArgNum + 1
                        fileAttached = oArgs(ArgNum)
                        'MsgBox fileAttached
                Case "--error","-e":
                        ArgNum = ArgNum + 1
                        errorFlag = oArgs(ArgNum)
             
                Case Else:
                        MsgBox "Invalid option"
	End Select	
        ArgNum = ArgNum+1
WEnd

if (errorFlag = "fail") then
	 msgBody=" Pta Build failed please read the attachment log file for details"
else
 msgBody="There is a new baseline for Pta from " & cvsTag & ". The build is sucessfully completed. The statictag is " & staticTag & " and location is " & cdLocation & " Use this sitekit for further testing"
End If


	If (errorFlag = "fail") then
		MySendMail "itg-client-eng@verisign.com", msgBody, "build failed"
	else
	      'Call our function with recipient, message and subject
	      MySendMail "itg-client-eng@verisign.com",msgBody,"build finished."
	End If 

      Sub MySendMail(recipient,msg,subject)
          'on Error goto ErrHandler
          Dim objSession, oInbox, colMessages, oMessage, colRecipients

          Set objSession = CreateObject("MAPI.Session")
          objSession.Logon "Usha"

          Set oInbox = objSession.Inbox
          Set colMessages = oInbox.Messages
          Set oMessage = colMessages.Add()
          Set colRecipients = oMessage.Recipients
          Set colAttachments = oMessage.Attachments

          colRecipients.Add recipient
          colRecipients.Resolve

          'colAttachments.Add " & fileAttached & "
	  If (fileAttached <> "") then
	     Set objAttach = colAttachments.Add
         	  With objAttach
	            '.Type = CdoFileData 
        	    .Position = 0 ' render at first character of message 
	            .Name = fileAttached             
	            .ReadFromFile fileAttached  
	          End With
	          objAttach.Name = fileAttached  
   	         'colAttachments.Update
   	  End If


          oMessage.Subject = subject
          oMessage.Text = msg
          oMessage.Send

          objSession.Logoff
          Set objSession = nothing
      End Sub 
