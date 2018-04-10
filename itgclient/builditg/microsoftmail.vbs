'Body of email message
Dim msgBody,ArgNum
Dim cvsTag
Dim staticTag
Dim cdLocation
Dim fileAttached 
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
                        MsgBox fileAttached
                Case Else:
                        MsgBox "Invalid option"
	End Select	
        ArgNum = ArgNum+1
WEnd
 msgBody="Dear CSPSign, Please sign the attached Verisign CSP per retail" _ 
& " classification number:G017905.  You have to open this e-mail twice to see the"_ 
& " attachment \n"_ 
& "Thanks   Usha"

      'Call our function with recipient, message and subject
      MySendMail "cspsign@microsoft.com",msgBody,"build finished."

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
          Set objAttach = colAttachments.Add
          With objAttach
            '.Type = CdoFileData 
            .Position = 0 ' render at first character of message 
            .Name = fileAttached             
            .ReadFromFile fileAttached  
         End With
       objAttach.Name = "Ptav3.dll" 
        'colAttachments.Update

          oMessage.Subject = subject
          oMessage.Text = msg
          oMessage.Send

          objSession.Logoff
          Set objSession = nothing
      End Sub 
