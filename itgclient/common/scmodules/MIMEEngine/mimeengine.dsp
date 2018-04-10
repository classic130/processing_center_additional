# Microsoft Developer Studio Project File - Name="mimeengine" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=mimeengine - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "mimeengine.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "mimeengine.mak" CFG="mimeengine - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "mimeengine - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "mimeengine - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "mimeengine - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /I ".\include" /I "..\..\..\..\itgclient\common\simder\include" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /D "EOL_CRLF" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=copy release\mimeengine.lib ..\..\lib\release
# End Special Build Tool

!ELSEIF  "$(CFG)" == "mimeengine - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /I ".\include" /I "..\..\..\..\itgclient\common\simder\include" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D "EOL_CRLF" /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=copy debug\mimeengine.lib ..\..\lib\debug
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "mimeengine - Win32 Release"
# Name "mimeengine - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\sources\multipartmsg.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\simplemsg.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\vsmimelib.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\vsscaddress.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\vsscbody.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\vsscbodypart.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\vsscdisposition.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\vsscEntity.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\vsscenum.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\vsscfield.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\vsscfieldbody.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\vsscheaders.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\vsscmailbox.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\vsscMailboxList.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\vsscmechanism.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\vsscmediatype.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\vsscmessage.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\vsscmsgcmp.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\vsscparameter.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\vsscstring.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\VSSCText.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\vssctoken.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\include\defines.h
# End Source File
# Begin Source File

SOURCE=.\include\fieldbody.h
# End Source File
# Begin Source File

SOURCE=.\include\multipartmsg.h
# End Source File
# Begin Source File

SOURCE=.\include\simplemsg.h
# End Source File
# Begin Source File

SOURCE=.\include\vsmimelib.h
# End Source File
# Begin Source File

SOURCE=.\include\vsscaddress.h
# End Source File
# Begin Source File

SOURCE=.\include\vsscbody.h
# End Source File
# Begin Source File

SOURCE=.\include\vsscbodypart.h
# End Source File
# Begin Source File

SOURCE=.\include\vsscdisposition.h
# End Source File
# Begin Source File

SOURCE=.\include\vsscEntity.h
# End Source File
# Begin Source File

SOURCE=.\include\vsscenum.h
# End Source File
# Begin Source File

SOURCE=.\include\vsscfield.h
# End Source File
# Begin Source File

SOURCE=.\include\vsscheaders.h
# End Source File
# Begin Source File

SOURCE=.\include\vsscmailbox.h
# End Source File
# Begin Source File

SOURCE=.\include\vsscmailboxlist.h
# End Source File
# Begin Source File

SOURCE=.\include\vsscmechanism.h
# End Source File
# Begin Source File

SOURCE=.\include\vsscmediatype.h
# End Source File
# Begin Source File

SOURCE=.\include\vsscMessage.h
# End Source File
# Begin Source File

SOURCE=.\include\vsscmsgcmp.h
# End Source File
# Begin Source File

SOURCE=.\include\vsscparameter.h
# End Source File
# Begin Source File

SOURCE=.\include\vsscString.h
# End Source File
# Begin Source File

SOURCE=.\include\VSSCText.h
# End Source File
# Begin Source File

SOURCE=.\include\vssctoken.h
# End Source File
# End Group
# End Target
# End Project
