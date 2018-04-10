Dim strRegFile
Dim strProjFile
Dim pProj
Dim pComp

If Wscript.Arguments.Item(0) = "help" Then
	Wscript.Echo "Usage Is : Wscript/Cscript InsertSig.vbs <registry file> <InstallShield Project File>"
	Wscript.Echo "Make sure you specify the absolute path of the registry and install shield project files"
	Wscript.Quit(1)
End If

If WScript.Arguments.Count <> 2 Then
	WScript.Echo "Invalid Number of Parameters"
	WScript.Quit(1)
End If

strRegFile = WScript.Arguments.Item(0)
strProjFile = WScript.Arguments.Item(1)    

'Convert relative paths to absolute paths
Dim fso
Set fso = CreateObject("Scripting.FileSystemObject")
strRegFile = fso.GetAbsolutePathName (strRegFile)
strProjFile = fso.GetAbsolutePathName (strProjFile)

Set pProj = CreateObject("ISWiAutomation.ISWiProject")

pProj.OpenProject strProjFile

For Each pComp In pProj.ISWiComponents
      If pComp.Name = "C_PTA_Control" Then
		pComp.ImportRegFile strRegFile,TRUE
      End If
Next

pProj.SaveProject    
pProj.CloseProject
WScript.Echo "Signature inserted"

