# Microsoft Developer Studio Project File - Name="ckdemo_pkcs201" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=ckdemo_pkcs201 - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ckdemo_pkcs201.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ckdemo_pkcs201.mak" CFG="ckdemo_pkcs201 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ckdemo_pkcs201 - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "ckdemo_pkcs201 - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName "ckdemo_pkcs201"
# PROP Scc_LocalPath "."
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ckdemo_pkcs201 - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release_201"
# PROP Intermediate_Dir "Release_201"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /I "source" /D "NDEBUG" /D "_WINDOWS" /D "WIN32" /D "OS_WIN32" /D "_CONSOLE" /D "_MBCS" /D "PKCS11_2_0" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386 /out:"Release/ckdemo.exe"

!ELSEIF  "$(CFG)" == "ckdemo_pkcs201 - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug_201"
# PROP Intermediate_Dir "Debug_201"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /I "source" /D "_DEBUG" /D "WINDOWS" /D "_WINDOWS" /D "WIN32" /D "OS_WIN32" /D "_CONSOLE" /D "_MBCS" /D "PKCS11_2_0" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /out:"Debug/ckdemo.exe" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "ckdemo_pkcs201 - Win32 Release"
# Name "ckdemo_pkcs201 - Win32 Debug"
# Begin Source File

SOURCE=.\source\c_bridge.cpp
# End Source File
# Begin Source File

SOURCE=.\source\ChrystokiConfiguration.cpp
# End Source File
# Begin Source File

SOURCE=.\source\ckbridge.cpp
# End Source File
# Begin Source File

SOURCE=.\Ckdemo.cpp
# End Source File
# Begin Source File

SOURCE=.\source\Ckodesc.cpp
# End Source File
# Begin Source File

SOURCE=.\source\console.cpp
# End Source File
# Begin Source File

SOURCE=.\source\DynamicLibrary.cpp
# End Source File
# Begin Source File

SOURCE=.\source\editor.cpp
# End Source File
# Begin Source File

SOURCE=.\source\template.cpp
# End Source File
# Begin Source File

SOURCE=.\source\Utils.cpp
# End Source File
# End Target
# End Project
