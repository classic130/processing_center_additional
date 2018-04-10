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
md %2\cgi-bin\VSApps
md %2\htmldocs\VSApps
md %2\fdf\VSApps

xcopy/E /C /R /Q %1\cgi-bin\VSApps\*.* %2\cgi-bin\VSApps
xcopy/E /C /R /Q %1\cgi-bin\vsexchange.dll %2\cgi-bin
xcopy/E /C /R /Q %1\htmldocs\VSApps\*.* %2\htmldocs\VSApps
xcopy/E /C /R /Q %1\fdf\VSApps\*.* %2\fdf\VSApps
xcopy/E /C /R /Q %1\htmldocs\VSApps\VSApps.htm %2\htmldocs

:do_not_copy
customizer.exe -f ..\fragments\VSApps -c ..\templates\vsapps_nt.lst -s %1 -d %2 -p %3 -l %2/log/VSApps/Customizer.log
goto end


:usage 
echo.
echo.
echo ***** Invalid parameters *****
echo "Usage:  vsainst-nt.bat <src_dir> <dest_dir> <policy_file>"
echo.
goto end 

:end
