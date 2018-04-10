Const msiOpenDatabaseModeReadOnly     = 0
Const msiOpenDatabaseModeTransact     = 1
Const msiOpenDatabaseModeCreate       = 3
Const ForAppending = 8
Const ForReading = 1
Const ForWriting = 2
Const TristateTrue = -1

Dim strLstFile
Dim strSrcFolder

If Wscript.Arguments.Item(0) = "-help" Then
	Wscript.Echo "Usage Is : Wscript/Cscript removtags.vbs <lst file> <src folder>"
	Wscript.Quit(1)
End If

If WScript.Arguments.Count <> 2 Then
	WScript.Echo "Invalid Number of Parameters"
	WScript.Quit(1)
End If

On Error Resume Next

strLstFile = WScript.Arguments.Item(0) : CheckError
strSrcFolder = WScript.Arguments.Item(1) : CheckError

'Convert relative paths to absolute paths
Dim fso
Set fso = CreateObject("Scripting.FileSystemObject") : CheckError
strLstFile = fso.GetAbsolutePathName (strLstFile) : CheckError
strSrcFolder = fso.GetAbsolutePathName (strSrcFolder) : CheckError

'Open the lst file
Dim theLstFile

Set theLstFile = fso.OpenTextFile(strLstFile, ForReading, False) : CheckError

Dim strSrcFile
Dim strDestFile
Dim strMSIFolder
Dim strXFMFile

'Read the names of the msi files for which transforms are to be generated
Do While theLstFile.AtEndOfStream <> True
	strSrcFile = strSrcFolder + "\" + theLstFile.ReadLine
	
	'Create the destination file
	strDestFile = strSrcFile + ".tmp"
	fso.CopyFile strSrcFile, strDestFile
	
	'Add the idts to the destination file
	strMSIFolder = fso.GetParentFolderName(strDestFile)
	ImportIdt strDestFile, (strMSIFolder+"\idts")
	
	strXFMFile = Left(strSrcFile, InStrRev(strSrcFile,"."))
	strXFMFile = strXFMFile + "mst"

	'Generate the transform
	GenXFM strSrcFile, strDestFile, strXFMFile

	'Delete the tmp file
	fso.DeleteFile strDestFile
Loop

Function ImportIdt (inStrDatabase, inStrFolder)
	' Connect to Windows Installer object
	On Error Resume Next
	Dim installer : Set installer = Nothing
	Set installer = Wscript.CreateObject("WindowsInstaller.Installer") : CheckError

	Dim openMode:openMode = msiOpenDatabaseModeTransact
	Dim databasePath:databasePath = inStrDatabase
	Dim folder:folder = inStrFolder

	' Open database and process list of files
	Dim database, table
	Set database = installer.OpenDatabase(databasePath, openMode) : CheckError
	table = "*.idt"
	' Check file name for wildcard specification
	If (InStr(1,table,"*",vbTextCompare) <> 0) Or (InStr(1,table,"?",vbTextCompare) <> 0) Then
		' Obtain list of files matching wildcard specification
		Dim WshShell, fileSys, file, tempFilePath
		Set WshShell = Wscript.CreateObject("Wscript.Shell") : CheckError
		tempFilePath = WshShell.ExpandEnvironmentStrings("%TEMP%") & "\dir.tmp"
		WshShell.Run "cmd.exe /U /c dir /b " & folder & "\" & table & ">" & tempFilePath, 0, True : CheckError
		Set fileSys = CreateObject("Scripting.FileSystemObject") : CheckError
		Set file = fileSys.OpenTextFile(tempFilePath, ForReading, False, TristateTrue) : CheckError
		' Import each file in directory list
		Do While file.AtEndOfStream <> True
			table = file.ReadLine
			database.Import folder, table : CheckError
		Loop
	Else
		database.Import folder, table : CheckError
	End If
	database.Commit 'commit changes if no import errors
End Function


Function GenXFM (inStrDB1, inStrDB2, inStrXFM)
	On Error Resume Next
	Dim installer : Set installer = Nothing
	Set installer = Wscript.CreateObject("WindowsInstaller.Installer") : CheckError

	' Open databases and generate transform
	Dim database1 : Set database1 = installer.OpenDatabase(inStrDB1, msiOpenDatabaseModeReadOnly) : CheckError

	Dim database2 : Set database2 = installer.OpenDatabase(inStrDB2, msiOpenDatabaseModeReadOnly) : CheckError

	Dim transform: transform = inStrXFM
	Dim different: different = database2.GenerateTransform(database1, transform) : CheckError

	' Create and add Summary Information
	Dim transinfo : transinfo = database2.CreateTransformSummaryInfo(database1, transform,0,0) : CheckError

End Function

Sub CheckError
	Dim message, errRec
	If Err = 0 Then Exit Sub
	message = Err.Source & " " & Hex(Err) & ": " & Err.Description
	Wscript.Echo message
	Wscript.Quit 2
End Sub
