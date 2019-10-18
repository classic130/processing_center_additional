# Microsoft Developer Studio Project File - Name="BSafeLite" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=BSafeLite - Win32 DebugASM
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "BSafeLite.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "BSafeLite.mak" CFG="BSafeLite - Win32 DebugASM"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "BSafeLite - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "BSafeLite - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "BSafeLite - Win32 DebugASM" (based on "Win32 (x86) Static Library")
!MESSAGE "BSafeLite - Win32 ReleaseASM" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "BSafeLite - Win32 Release"

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
# ADD CPP /nologo /MD /W3 /GX /O2 /I "include" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /D "INTELx86i32" /FR /YX /FD /c
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
PostBuild_Cmds=if not exist "..\lib\static\release" md "..\lib\static\release"	copy release\BSafeLite.lib "..\lib\static\release"
# End Special Build Tool

!ELSEIF  "$(CFG)" == "BSafeLite - Win32 Debug"

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
# ADD CPP /MD /W3 /Gm /GX /ZI /Od /I "include" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D "INTELx86i32" /FR /YX /FD /GZ /c
# SUBTRACT CPP /nologo
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
PostBuild_Cmds=if not exist "..\lib\static\debug" md "..\lib\static\debug"	copy debug\BSafeLite.lib "..\lib\static\debug"
# End Special Build Tool

!ELSEIF  "$(CFG)" == "BSafeLite - Win32 DebugASM"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "BSafeLite___Win32_DebugASM"
# PROP BASE Intermediate_Dir "BSafeLite___Win32_DebugASM"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "DebugASM"
# PROP Intermediate_Dir "DebugASM"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /Gm /GX /ZI /Od /I "include" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D "INTELx86i32" /FR /YX /FD /GZ /c
# ADD CPP /nologo /MD /W3 /Gm /GX /ZI /Od /I "include" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D "INTELx86i32" /FR /YX /FD /GZ /c
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
PostBuild_Cmds=if not exist "..\lib\static\debug" md "..\lib\static\debug"	copy debugASM\BSafeLite.lib "..\lib\static\debug"
# End Special Build Tool

!ELSEIF  "$(CFG)" == "BSafeLite - Win32 ReleaseASM"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "BSafeLite___Win32_ReleaseASM"
# PROP BASE Intermediate_Dir "BSafeLite___Win32_ReleaseASM"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ReleaseASM"
# PROP Intermediate_Dir "ReleaseASM"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /I "include" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /D "INTELx86i32" /FR /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "include" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /D "INTELx86i32" /FR /YX /FD /c
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
PostBuild_Cmds=if not exist "..\lib\static\release" md "..\lib\static\release"	copy releaseASM\BSafeLite.lib "..\lib\static\release"
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "BSafeLite - Win32 Release"
# Name "BSafeLite - Win32 Debug"
# Name "BSafeLite - Win32 DebugASM"
# Name "BSafeLite - Win32 ReleaseASM"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "BSafe"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\cmparith.c
# End Source File
# Begin Source File

SOURCE=.\src\cmpati32.asm

!IF  "$(CFG)" == "BSafeLite - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BSafeLite - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BSafeLite - Win32 DebugASM"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=.\DebugASM
InputPath=.\src\cmpati32.asm

"$(IntDir)\cmpati32.obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	I:\MASM611\BIN\ml /c /Cx /coff /Fo $(IntDir)\cmpati32.obj $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "BSafeLite - Win32 ReleaseASM"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=.\ReleaseASM
InputPath=.\src\cmpati32.asm

"$(IntDir)\cmpati32.obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	I:\MASM611\BIN\ml /c /Cx /coff /Fo $(IntDir)\cmpati32.obj $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\cmpbits.c
# End Source File
# Begin Source File

SOURCE=.\src\cmpcnv.c
# End Source File
# Begin Source File

SOURCE=.\src\cmpmdexp.c

!IF  "$(CFG)" == "BSafeLite - Win32 Release"

!ELSEIF  "$(CFG)" == "BSafeLite - Win32 Debug"

!ELSEIF  "$(CFG)" == "BSafeLite - Win32 DebugASM"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BSafeLite - Win32 ReleaseASM"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\cmpmdi32.c

!IF  "$(CFG)" == "BSafeLite - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BSafeLite - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BSafeLite - Win32 DebugASM"

!ELSEIF  "$(CFG)" == "BSafeLite - Win32 ReleaseASM"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\cmpmem.c
# End Source File
# Begin Source File

SOURCE=.\src\cmpmgi32.c

!IF  "$(CFG)" == "BSafeLite - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BSafeLite - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BSafeLite - Win32 DebugASM"

!ELSEIF  "$(CFG)" == "BSafeLite - Win32 ReleaseASM"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\cmpmod.c
# End Source File
# Begin Source File

SOURCE=.\src\cmpmontg.c

!IF  "$(CFG)" == "BSafeLite - Win32 Release"

!ELSEIF  "$(CFG)" == "BSafeLite - Win32 Debug"

!ELSEIF  "$(CFG)" == "BSafeLite - Win32 DebugASM"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BSafeLite - Win32 ReleaseASM"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\cmpmpi32.asm

!IF  "$(CFG)" == "BSafeLite - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BSafeLite - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BSafeLite - Win32 DebugASM"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=.\DebugASM
InputPath=.\src\cmpmpi32.asm

"$(IntDir)\cmpmpi32.obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	I:\MASM611\BIN\ml /c /Cx /coff /Fo $(IntDir)\cmpmpi32.obj $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "BSafeLite - Win32 ReleaseASM"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=.\ReleaseASM
InputPath=.\src\cmpmpi32.asm

"$(IntDir)\cmpmpi32.obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	I:\MASM611\BIN\ml /c /Cx /coff /Fo $(IntDir)\cmpmpi32.obj $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\cmpmsi32.asm

!IF  "$(CFG)" == "BSafeLite - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BSafeLite - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BSafeLite - Win32 DebugASM"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=.\DebugASM
InputPath=.\src\cmpmsi32.asm

"$(IntDir)\cmpmsi32.obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	I:\MASM611\BIN\ml /c /Cx /coff /Fo $(IntDir)\cmpmsi32.obj $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "BSafeLite - Win32 ReleaseASM"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=.\ReleaseASM
InputPath=.\src\cmpmsi32.asm

"$(IntDir)\cmpmsi32.obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	I:\MASM611\BIN\ml /c /Cx /coff /Fo $(IntDir)\cmpmsi32.obj $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\cmpmuldv.c

!IF  "$(CFG)" == "BSafeLite - Win32 Release"

!ELSEIF  "$(CFG)" == "BSafeLite - Win32 Debug"

!ELSEIF  "$(CFG)" == "BSafeLite - Win32 DebugASM"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BSafeLite - Win32 ReleaseASM"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\cmpmxi32.c

!IF  "$(CFG)" == "BSafeLite - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BSafeLite - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BSafeLite - Win32 DebugASM"

!ELSEIF  "$(CFG)" == "BSafeLite - Win32 ReleaseASM"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\cmpspprt.c
# End Source File
# Begin Source File

SOURCE=.\src\cmpvectr.c
# End Source File
# Begin Source File

SOURCE=.\src\cmpvmi32.asm

!IF  "$(CFG)" == "BSafeLite - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BSafeLite - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BSafeLite - Win32 DebugASM"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=.\DebugASM
InputPath=.\src\cmpvmi32.asm

"$(IntDir)\cmpvmi32.obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	I:\MASM611\BIN\ml /c /Cx /coff /Fo $(IntDir)\cmpvmi32.obj $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "BSafeLite - Win32 ReleaseASM"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=.\ReleaseASM
InputPath=.\src\cmpvmi32.asm

"$(IntDir)\cmpvmi32.obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	I:\MASM611\BIN\ml /c /Cx /coff /Fo $(IntDir)\cmpvmi32.obj $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\des.c
# End Source File
# Begin Source File

SOURCE=.\src\desedec.c
# End Source File
# Begin Source File

SOURCE=.\src\deseded.c
# End Source File
# Begin Source File

SOURCE=.\src\desedee.c
# End Source File
# Begin Source File

SOURCE=.\src\digrand.c
# End Source File
# Begin Source File

SOURCE=.\src\md2.c
# End Source File
# Begin Source File

SOURCE=.\src\md5.c
# End Source File
# Begin Source File

SOURCE=.\src\md5rand.c
# End Source File
# Begin Source File

SOURCE=.\src\prime.c
# End Source File
# Begin Source File

SOURCE=.\src\rc2.c
# End Source File
# Begin Source File

SOURCE=.\src\rc2cbd.c
# End Source File
# Begin Source File

SOURCE=.\src\rc2cbe.c
# End Source File
# Begin Source File

SOURCE=.\src\rc4.c
# End Source File
# Begin Source File

SOURCE=.\src\rsa.c
# End Source File
# Begin Source File

SOURCE=.\src\rsakeygn.c
# End Source File
# Begin Source File

SOURCE=.\src\seccbcd.c
# End Source File
# Begin Source File

SOURCE=.\src\seccbce.c
# End Source File
# Begin Source File

SOURCE=.\src\secrcbc.c
# End Source File
# Begin Source File

SOURCE=.\src\sha.c
# End Source File
# Begin Source File

SOURCE=.\src\shacomm.c
# End Source File
# Begin Source File

SOURCE=.\src\uint4.c
# End Source File
# End Group
# Begin Source File

SOURCE=.\src\integrate.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "bsafeInc"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\include\aglobal.h
# End Source File
# Begin Source File

SOURCE=.\include\algae.h
# End Source File
# Begin Source File

SOURCE=.\include\atypes.h
# End Source File
# Begin Source File

SOURCE=.\include\BASETSD.H
# End Source File
# Begin Source File

SOURCE=.\include\bsafe.h
# End Source File
# Begin Source File

SOURCE=.\include\bsafelite.h
# End Source File
# Begin Source File

SOURCE=.\include\cmp.h
# End Source File
# Begin Source File

SOURCE=.\include\cmppriv.h
# End Source File
# Begin Source File

SOURCE=.\include\cmpspprt.h
# End Source File
# Begin Source File

SOURCE=.\include\des.h
# End Source File
# Begin Source File

SOURCE=.\include\desedec.h
# End Source File
# Begin Source File

SOURCE=.\include\digrand.h
# End Source File
# Begin Source File

SOURCE=.\include\global.h
# End Source File
# Begin Source File

SOURCE=.\include\keysize.h
# End Source File
# Begin Source File

SOURCE=.\include\md2.h
# End Source File
# Begin Source File

SOURCE=.\include\md5.h
# End Source File
# Begin Source File

SOURCE=.\include\md5rand.h
# End Source File
# Begin Source File

SOURCE=.\include\prime.h
# End Source File
# Begin Source File

SOURCE=.\include\rc2.h
# End Source File
# Begin Source File

SOURCE=.\include\rc2cbc.h
# End Source File
# Begin Source File

SOURCE=.\include\rc4.h
# End Source File
# Begin Source File

SOURCE=.\include\rsa.h
# End Source File
# Begin Source File

SOURCE=.\include\rsakeygn.h
# End Source File
# Begin Source File

SOURCE=.\include\secrcbc.h
# End Source File
# Begin Source File

SOURCE=.\include\sha.h
# End Source File
# Begin Source File

SOURCE=.\include\shacomm.h
# End Source File
# Begin Source File

SOURCE=.\include\stdlibrf.h
# End Source File
# Begin Source File

SOURCE=.\include\uint4.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\include\integrate.h
# End Source File
# End Group
# End Target
# End Project
