

Option Explicit

On Error Resume Next

Dim oWS : Set oWS = CreateObject("WScript.Shell")
Dim fileSys: Set fileSys = CreateObject("Scripting.FileSystemObject")

Dim dllFileName, permErr

permErr = 0

'Read the file location from registry

dllFileName = oWS.RegRead("HKCR\CLSID\{08F04139-8DFC-11D2-80E9-006008B066EE}\InprocServer32\")

'If entry is found in registry, error is 0

If Err.Number = 0 Then

'Check for file and delete it if present

    If fileSys.FileExists(dllFileName) Then
        'oWS.PopUp  dllFileName 
        fileSys.DeleteFile(dllFileName)
        If Err.Number <> 0 Then
            permErr = 99 
        End If  
    End If

    'Delete all the registry entry from Current User Root

    oWS.RegDelete("HKCR\CLSID\{08F04139-8DFC-11D2-80E9-006008B066EE}\Control\")
    If Err.Number <> 0 Then
        permErr = 99 
    End If  

    oWS.RegDelete("HKCR\CLSID\{08F04139-8DFC-11D2-80E9-006008B066EE}\Implemented Categories\{7DD95801-9882-11CF-9FA9-00AA006C42C4}\")
    If Err.Number <> 0 Then
        permErr = 99 
    End If  

    oWS.RegDelete("HKCR\CLSID\{08F04139-8DFC-11D2-80E9-006008B066EE}\Implemented Categories\{7DD95802-9882-11CF-9FA9-00AA006C42C4}\")
    If Err.Number <> 0 Then
        permErr = 99 
    End If  

    oWS.RegDelete("HKCR\CLSID\{08F04139-8DFC-11D2-80E9-006008B066EE}\Implemented Categories\")
    If Err.Number <> 0 Then
        permErr = 99 
    End If  

    oWS.RegDelete("HKCR\CLSID\{08F04139-8DFC-11D2-80E9-006008B066EE}\InprocServer32\")
    If Err.Number <> 0 Then
        permErr = 99 
    End If  

    oWS.RegDelete("HKCR\CLSID\{08F04139-8DFC-11D2-80E9-006008B066EE}\Insertable\")
    If Err.Number <> 0 Then
        permErr = 99 
    End If  

    oWS.RegDelete("HKCR\CLSID\{08F04139-8DFC-11D2-80E9-006008B066EE}\MiscStatus\1\")
    If Err.Number <> 0 Then
        permErr = 99 
    End If  

    oWS.RegDelete("HKCR\CLSID\{08F04139-8DFC-11D2-80E9-006008B066EE}\MiscStatus\")
    If Err.Number <> 0 Then
        permErr = 99 
    End If  

    oWS.RegDelete("HKCR\CLSID\{08F04139-8DFC-11D2-80E9-006008B066EE}\ProgID\")
    If Err.Number <> 0 Then
        permErr = 99 
    End If  

    oWS.RegDelete("HKCR\CLSID\{08F04139-8DFC-11D2-80E9-006008B066EE}\Programmable\")
    If Err.Number <> 0 Then
        permErr = 99 
    End If  

    oWS.RegDelete("HKCR\CLSID\{08F04139-8DFC-11D2-80E9-006008B066EE}\ToolboxBitmap32\")
    If Err.Number <> 0 Then
        permErr = 99 
    End If  

    oWS.RegDelete("HKCR\CLSID\{08F04139-8DFC-11D2-80E9-006008B066EE}\TypeLib\")
    If Err.Number <> 0 Then
        permErr = 99 
    End If  

    oWS.RegDelete("HKCR\CLSID\{08F04139-8DFC-11D2-80E9-006008B066EE}\VersionIndependentProgID\")
    If Err.Number <> 0 Then
        permErr = 99 
    End If  

    oWS.RegDelete("HKCR\CLSID\{08F04139-8DFC-11D2-80E9-006008B066EE}\Version\")
    If Err.Number <> 0 Then
        permErr = 99 
    End If  

    oWS.RegDelete("HKCR\CLSID\{08F04139-8DFC-11D2-80E9-006008B066EE}\")
    If Err.Number <> 0 Then
        permErr = 99 
    End If  

Else
'Nothing to do
'oWS.PopUp "No entry in the registry"
End If

If permErr <> 0 Then
    oWS.PopUp "Please run the program with admin privilege"
End If

Cleanup()

Sub Cleanup()
  Set oWS = Nothing
  Set fileSys = Nothing
  WScript.Quit(0)
End Sub
