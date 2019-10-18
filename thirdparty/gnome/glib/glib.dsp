# Microsoft Developer Studio Project File - Name="glib" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=glib - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "glib.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "glib.mak" CFG="glib - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "glib - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "glib - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "glib - Win32 Release"

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
# ADD CPP /nologo /MD /W3 /GX /O2 /I "../glib" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /D "HAVE_CONFIG_H" /D "GLIB_COMPILATION" /D G_LOG_DOMAIN=g_log_domain_glib /D "NATIVE_WIN32" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"lib\winnt\glib.lib"

!ELSEIF  "$(CFG)" == "glib - Win32 Debug"

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
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "../glib" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D "HAVE_CONFIG_H" /D "GLIB_COMPILATION" /D G_LOG_DOMAIN=g_log_domain_glib /D "NATIVE_WIN32" /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"lib\winnt\glib.lib"

!ENDIF 

# Begin Target

# Name "glib - Win32 Release"
# Name "glib - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\garray.c
# End Source File
# Begin Source File

SOURCE=.\gcache.c
# End Source File
# Begin Source File

SOURCE=.\gcompletion.c
# End Source File
# Begin Source File

SOURCE=.\gdataset.c
# End Source File
# Begin Source File

SOURCE=.\gdate.c
# End Source File
# Begin Source File

SOURCE=.\gerror.c
# End Source File
# Begin Source File

SOURCE=.\ghash.c
# End Source File
# Begin Source File

SOURCE=.\ghook.c
# End Source File
# Begin Source File

SOURCE=.\giochannel.c
# End Source File
# Begin Source File

SOURCE=.\giowin32.c
# End Source File
# Begin Source File

SOURCE=.\glist.c
# End Source File
# Begin Source File

SOURCE=.\gmain.c
# End Source File
# Begin Source File

SOURCE=.\gmem.c
# End Source File
# Begin Source File

SOURCE=.\gmessages.c
# End Source File
# Begin Source File

SOURCE=.\gmutex.c
# End Source File
# Begin Source File

SOURCE=.\gnode.c
# End Source File
# Begin Source File

SOURCE=.\gprimes.c
# End Source File
# Begin Source File

SOURCE=.\grel.c
# End Source File
# Begin Source File

SOURCE=.\gscanner.c
# End Source File
# Begin Source File

SOURCE=.\gslist.c
# End Source File
# Begin Source File

SOURCE=.\gstrfuncs.c
# End Source File
# Begin Source File

SOURCE=.\gstring.c
# End Source File
# Begin Source File

SOURCE=.\gtimer.c
# End Source File
# Begin Source File

SOURCE=.\gtree.c
# End Source File
# Begin Source File

SOURCE=.\gutils.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# End Group
# End Target
# End Project
