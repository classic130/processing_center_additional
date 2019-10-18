1.  \Mssdk\Samples\Multimedia directory
----------------------------------------

The \Mssdk\Samples\Multimedia directory contains samples, tools, 
and sample media files for the following Platform SDK components:

* Win32 Audio, Input, and Video
* Broadcast Architecture
* DirectX, including DirectDraw, DirectSound, DirectPlay, 
  DirectInput, Direct3D Immediate Mode, Direct3D Retained Mode, 
  DirectAnimation, and DirectShow
* GDI
* Image Color Management (ICM) 2.0
* OpenGL

The build environment (headers, libraries, and minimum build 
tools) for the Platform SDK must be installed in order to build 
any of the samples in the \Mssdk\Samples\Multimedia directory. The 
most recent version of the build environment is available at 
http://www.microsoft.com/msdn/sdk/platform.htm. 
Some components may also require you to install runtimes, depending 
on the platform on which you are trying to run the sample. 
Redistributables are available in the \Mssdk\Redist subdirectory 
on the Platform SDK compact disc. 

Documentation for the components listed above can be installed 
from the Platform SDK compact disc, or can be viewed online at 
http://premium.microsoft.com/msdn/library/. This is a FREE service; 
registration is necessary.

If you do not see any subdirectories in the \Mssdk\Samples\Multimedia 
node, you'll need to install the Graphics and Multimedia components 
from the Platform SDK compact disc or download and install them
from http://www.microsoft.com/msdn/sdk/platform.htm. 


2.  Release Notes for the DirectX Foundation components
-------------------------------------------------------
DirectX samples appear in the following \Mssdk\Samples\Multimedia 
subdirectories:
* D3DIM
* D3DRM
* DSound
* DPlay
* DInput
* DDraw
* Misc


2.1 Setting up your DirectX build environment
---------------------------------------------
To setup your DirectX build environment, edit the 
<sdkdir>\samples\multimedia\directx\dxsetenv.bat
file to point to the location of your compiler, assembler, 
and the location of the Windows Platform SDK. Run the 
dxsetenv.bat batch file.

Windows 95-specific libs (VC and Watcom) are installed 
to <sdkdir>\lib. 

If you have problems building the samples when running 
under a DOS Command box, try using a NT DOS CMD box 
instead. Start\Run, Type "CMD", hit enter".    


2.2 DirectX Samples
-------------------

To ensure compatability with all editors, all tabs in sample source code files
have been replaced with spaces.

All SDK samples are designed to be built in the directory they are in.  
Once your Win32 development environment is set up, you 
can go to any sample directory and do a make.

There is a main make file in each sample directory:
MAKEFILE        - for use with Microsoft VC++ 2.0 or higher (NMAKE)

There are 2 ways to build each sample, debug or retail.   To build a
sample as retail with VC++, just type:

nmake nodebug=1

To build a sample as debug with VC++, just type:

nmake

There is also a master make file in the SAMPLES directory that will compile
all the samples at once:
MAKEFILE        - for use with Microsoft VC++ 2.0 or higher (NMAKE)


2.3  Notes for users of Visual C++ 4.2
---------------------------------
Visual C++ 4.2 includes the DX2 header files and libraries.  If you are
getting errors compiling, make sure that the DX3 include
and lib paths come before the MSVC++ 4.2 include and lib paths.


2.4  Notes for users of Watcom C/C++
-------------------------------
Watcom C/C++ v10.6 is required to compile the DXSDK samples.
v10.0 is not sufficient. The Microsoft Windows Platform SDK is also required
and is expected to be in \MSSDK on the same drive as your DirectX
sample files. If the Platform SDK is elsewhere, you can set the MSSDK
environment variable to point to its root directory (e.g. set
MSSDK=\MSSDK).

Change the following lines in WIN32.MAK from:
        libc = libc.lib oldnames.lib
        libcmt = libcmt.lib oldnames.lib
        libcdll = msvcrt.lib oldnames.lib
to:
        libc =
        libcmt =
        libcdll =

The Watcom makefiles expect the WATCOM environment variable
to be set, as it should have been by the Watcom installation procedure.

Only a subset of the samples have Watcom makefiles.

Watcom and Watcom C/C++ are trademarks of Powersoft, Watcom Division.
