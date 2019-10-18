@echo off
REM echo "source directory       : %1"
REM echo "destination directory  : %2"
REM echo "policy file            : %3"

if (%3) == () goto usage
if (%2) == () goto usage
if (%1) == () goto usage

if (%1) == (%2) goto do_not_copy
echo "creating directory structure and copying files"
md %2
md %2\ptaSmLogin
md %2\ptaSmLogin\log

xcopy/E /C /R /Q ..\templates\ptaSmLogin\*.* %2\ptaSmLogin

:do_not_copy
customizer.exe -c ..\templates\sitekit_ptaSm_nt.lst -s %1 -d %2 -f ..\fragments\VSApps -p %3 -l %2/ptaSmLogin/log/ptaSmCustomizer.log
goto end


:usage 
echo.
echo.
echo ***** Invalid parameters *****
echo "Usage:  ptaSm-install-nt.bat <src_dir> <dest_dir> <policy_file>"
echo.
goto end 

:end
