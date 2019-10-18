Dim strLstFile
Dim strSrcFolder

If Wscript.Arguments.Item(0) = "-help" Then
	Wscript.Echo "Usage Is : Wscript/Cscript removeempty.vbs <lst file> <src folder>"
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
Const ForReading = 1

Set theLstFile = fso.OpenTextFile(strLstFile, ForReading, False) : CheckError

Dim strSrcFile
Dim theSrcFile
Dim strDestFile
Dim theDestFile
Dim strTemp

'Read the names of the files from which empty valued rows are to be removed
Do While theLstFile.AtEndOfStream <> True
    strSrcFile = strSrcFolder + "\" + theLstFile.ReadLine
		
	'Create the destination file
	strDestFile = strSrcFile + ".tmp"
	Set theDestFile = fso.CreateTextFile(strDestFile, True) : CheckError
	
	'Open the src file
	Set theSrcFile = fso.OpenTextFile(strSrcFile,ForReading,False) : CheckError

	'Read from the source file and write into the destination file filtering out the tags
	Do While theSrcFile.AtEndOfStream <> True
		strTemp = theSrcFile.ReadLine
		If RegExpTest(".*\t$", strTemp) = False Then
		   If RegExpTest(".*\t-$", strTemp) = False Then
			theDestFile.WriteLine strTemp
		   End If
		End If			
	Loop
	
	theSrcFile.Close
	theDestFile.Close	
	fso.DeleteFile strSrcFile,True : CheckError
	fso.MoveFile strDestFile, strSrcFile : CheckError
Loop

strLstFile.Close

Function RegExpTest(patrn, strng)
   Dim regEx, Match, Matches   ' Create variable.
   Set regEx = New RegExp   ' Create a regular expression.
   regEx.Pattern = patrn   ' Set pattern.
   regEx.IgnoreCase = True   ' Set case insensitivity.
   regEx.Global = True   ' Set global applicability.
   Set Matches = regEx.Execute(strng)   ' Execute search.
   If Matches.Count > 0 Then
  	 RegExpTest = True
   Else
	RegExpTest = False
   End If
End Function

Sub CheckError
	Dim message, errRec
	If Err = 0 Then Exit Sub
	message = Err.Source & " " & Hex(Err) & ": " & Err.Description
	Wscript.Echo message
	Wscript.Quit 2
End Sub

