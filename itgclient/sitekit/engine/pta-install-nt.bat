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
md %2\log\VSApps
md %2\pta
md %2\pta\log

xcopy/E /C /R /Q ..\templates\pta\*.* %2\pta

:do_not_copy
customizer.exe -c ..\templates\sitekit_pta_nt.lst -s %1 -d %2 -f ..\fragments\VSApps -p %3 -l %2/log/VSApps/ptaCustomizer.log
goto end


:usage 
echo.
echo.
echo ***** Invalid parameters *****
echo "Usage:  pta-install-nt.bat <src_dir> <dest_dir> <policy_file>"
echo.
goto end 

:end
