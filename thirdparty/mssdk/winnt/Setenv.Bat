@Echo OFF
:: -------------------------------------------------------------------
:: File    : setenv.exe
::
:: Usage   : <Path to Platform SDK>
::
:: Abstract: This batch file sets the appropriate environmental
::           variables for the Platform SDK build envionment with
::           respect to OS and platform type.
::
:: Imports : None
::
:: -------------------------------------------------------------------

:: Set MSSDK variable and verify that the directory exists
:: while working around " issue on Windows 9x
if "%1" == "" goto checkenv
set MSSDK=%1
if "%2" == "" goto checkmssdk
set MSSDK=%MSSDK% %2
if "%3" == "" goto checkmssdk
set MSSDK=%MSSDK% %3
if "%4" == "" goto checkmssdk
set MSSDK=%MSSDK% %4
if "%5" == "" goto checkmssdk
set MSSDK=%MSSDK% %5
if NOT "%6" == "" goto ErrorPath
goto checkmssdk

:checkenv
if "%MSSDK%" == "" goto ErrorUsage

:checkmssdk
If not exist "%MSSDK%\SetEnv.Bat" goto :ErrorBadPath


:: Set common variables
set Lib=%MSSDK%\Lib;%lib%
set Include=%MSSDK%\Include;%include%
set Bkoffice=%MSSDK%\
set Basemake=%MSSDK%\Include\BKOffice.Mak
set DXSDKROOT=%MSSDK%
set INETSDK=%MSSDK%
set Mssdk=%MSSDK%
set Mstools=%MSSDK%
set LOG=NO


:: Set OS specific variables
if "%OS%" == "Windows_NT" goto winnt
goto win9x

:: Set Windows 9x specific variables
:win9x
Echo Setting SDK environment relative to %MSSDK%. Targeting Windows 9x
set Path="%MSSDK%\bin;%MSSDK%\bin\win95;%path%"
set CPU=i386
doskey > NUL
goto checkmsdevdir

:: Set Windows NT specific variables
:winnt
set Path=%MSSDK%\bin;%MSSDK%\bin\winnt;%path%
if /i "%PROCESSOR_ARCHITECTURE%" == "ALPHA" (set CPU=ALPHA) else (set CPU=i386)
Echo.
Echo Setting SDK environment relative to %MSSDK%. Targeting Windows NT (%Cpu%)
Echo.
goto checkmsdevdir


:checkmsdevdir
if "%MSDevDir%" == "" goto ErrorMSDevDir
goto end


:ErrorUsage
Echo.
Echo To set the SDK environment paths, run SETENV from your Platform SDK
Echo installation directory.
Echo.
Echo Usage:   SETENV MSSDK
Echo Where:   MSSDK specifies where the Platform SDK was installed 
Echo.
Echo Example: C:\MSSDK\SETENV C:\MSSDK sets the environment relative to C:\MSSDK
Echo.
goto end


:ErrorMSDevDir
Echo.
Echo Warning: check your LIB, INCLUDE and PATH to verify that the 
Echo  SDK Lib, Include, and Bin directories precede the compiler 
Echo  directories in the environment.
Echo.
Echo Microsoft Visual Studio provides VCVARS32.BAT to set them. 
Echo You must run VCVARS32.BAT first and then run SETENV.BAT.
Echo.
Echo Current settings:
Echo.
Echo LIB=%LIB%
Echo.
Echo INCLUDE=%INCLUDE%
Echo.
Echo PATH=%PATH%
Echo.
goto end


:ErrorPath
Echo.
Echo Error: Too many spaces in path. Cannot set MSSDK environment variable
Echo
Echo.
goto end


:ErrorBadPath
Echo.
Echo Error: The path "%MSSDK%" does not exist
Echo.
goto ErrorUsage


:end
