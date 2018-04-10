'
' Script to register a Web Filter into ISA Server
'
On Error Resume Next

Set FPC = WScript.CreateObject("FPC.Root")
FPC.Arrays.GetContainingArray
if Err.Number = 0 Then
   ' must be ISA2000
   Set filters = FPC.Arrays.GetContainingArray.Extensions.WebFilters
Else
   ' must be ISA2004 or ISA2006
   Set filters = FPC.GetContainingArray.Extensions.WebFilters
End If

On Error Goto 0

' Syntax ==> filters.Add(GUID, Name, Relative Path, Priority, Direction)
' GUID ==> {05D91054-2343-4c17-BD7C-13B748578170}
' Priority ==>
'	0 == fpcFilterPriority_Low
'	1 == fpcFilterPriority_Medium
'	2 == fpcFilterPriority_High
' Direction ==>
'	0 == fpcFilterDirectionForward (Outgoing)
'	1 == fpcFilterDirectionReverse (Incomming)
'	2 == fpcFilterDirectionBoth

Set mfilter = filters.Add("{05D91054-2343-4c17-BD7C-13B748578170}", "CVM Filter", "libvsvalm.dll", 1, 1)

mfilter.Description = "CVM ISA Plugin"
mfilter.Vendor = "VeriSign Inc."
mfilter.Version = "7.2"
mfilter.Enabled = True
filters.Save

WScript.Echo "done"
