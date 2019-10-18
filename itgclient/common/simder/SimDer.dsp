# Microsoft Developer Studio Project File - Name="SimDer" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=SimDer - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "SimDer.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "SimDer.mak" CFG="SimDer - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "SimDer - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "SimDer - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "SimDer - Win32 Release"

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
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O1 /I ".\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=if not exist "..\lib\release" md "..\lib\release"	copy release\simder.lib "..\lib\release\simder.lib"
# End Special Build Tool

!ELSEIF  "$(CFG)" == "SimDer - Win32 Debug"

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
# ADD BASE CPP /nologo /W3 /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /Z7 /Od /I ".\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /YX /FD /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=if not exist "..\lib\debug" md "..\lib\debug"	copy debug\simder.lib "..\lib\debug\simder.lib"
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "SimDer - Win32 Release"
# Name "SimDer - Win32 Debug"
# Begin Source File

SOURCE=.\sources\BaseDER.cpp
# End Source File
# Begin Source File

SOURCE=.\include\BaseDER.h
# End Source File
# Begin Source File

SOURCE=.\sources\BaseDERCollection.cpp
# End Source File
# Begin Source File

SOURCE=.\include\BaseDERCollection.h
# End Source File
# Begin Source File

SOURCE=.\sources\BaseDERHierarchy.cpp
# End Source File
# Begin Source File

SOURCE=.\include\BaseDERHierarchy.h
# End Source File
# Begin Source File

SOURCE=.\sources\BitString.cpp
# End Source File
# Begin Source File

SOURCE=.\include\BitString.h
# End Source File
# Begin Source File

SOURCE=.\sources\BMPString.cpp
# End Source File
# Begin Source File

SOURCE=.\include\BMPString.h
# End Source File
# Begin Source File

SOURCE=.\sources\Boolean.cpp
# End Source File
# Begin Source File

SOURCE=.\include\Boolean.h
# End Source File
# Begin Source File

SOURCE=.\include\DataTypes.h
# End Source File
# Begin Source File

SOURCE=.\sources\DERBlob.cpp
# End Source File
# Begin Source File

SOURCE=.\include\DERBlob.h
# End Source File
# Begin Source File

SOURCE=.\sources\GeneralizedTime.cpp
# End Source File
# Begin Source File

SOURCE=.\include\GeneralizedTime.h
# End Source File
# Begin Source File

SOURCE=.\sources\IA5String.cpp
# End Source File
# Begin Source File

SOURCE=.\include\IA5String.h
# End Source File
# Begin Source File

SOURCE=.\sources\MemFuncs.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Null.cpp
# End Source File
# Begin Source File

SOURCE=.\include\Null.h
# End Source File
# Begin Source File

SOURCE=.\sources\ObjectIdentifier.cpp
# End Source File
# Begin Source File

SOURCE=.\include\ObjectIdentifier.h
# End Source File
# Begin Source File

SOURCE=.\sources\OctetString.cpp
# End Source File
# Begin Source File

SOURCE=.\include\OctetString.h
# End Source File
# Begin Source File

SOURCE=.\sources\PrintableString.cpp
# End Source File
# Begin Source File

SOURCE=.\include\PrintableString.h
# End Source File
# Begin Source File

SOURCE=.\sources\Sequence.cpp
# End Source File
# Begin Source File

SOURCE=.\include\Sequence.h
# End Source File
# Begin Source File

SOURCE=.\sources\Set.cpp
# End Source File
# Begin Source File

SOURCE=.\include\Set.h
# End Source File
# Begin Source File

SOURCE=.\sources\TaggedValue.cpp
# End Source File
# Begin Source File

SOURCE=.\include\TaggedValue.h
# End Source File
# Begin Source File

SOURCE=.\sources\TeletexString.cpp
# End Source File
# Begin Source File

SOURCE=.\include\TeletexString.h
# End Source File
# Begin Source File

SOURCE=.\sources\UniversalInteger.cpp
# End Source File
# Begin Source File

SOURCE=.\include\UniversalInteger.h
# End Source File
# Begin Source File

SOURCE=.\sources\UTCTime.cpp
# End Source File
# Begin Source File

SOURCE=.\include\UTCTime.h
# End Source File
# Begin Source File

SOURCE=.\sources\UTF8String.cpp
# End Source File
# Begin Source File

SOURCE=.\include\UTF8String.h
# End Source File
# Begin Source File

SOURCE=.\sources\VisibleString.cpp
# End Source File
# Begin Source File

SOURCE=.\include\VisibleString.h
# End Source File
# End Target
# End Project
