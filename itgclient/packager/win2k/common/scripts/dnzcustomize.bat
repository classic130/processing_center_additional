@echo off
REM echo "destination directory  : %1"
REM echo "policy file            : %2"

if (%2) == () goto usage
if (%1) == () goto usage

md %1
md %1\log\
md %1\dnzpackages

xcopy/E /C /R /Q ..\templates\dnzpackages\*.* %1\dnzpackages\
customizer.exe -f ..\fragments -c ..\templates\customizednz.lst -s ..\templates -d %1 -p %2 -l %1/log/dnzcustomize.log
cscript removetags.vbs ..\templates\customizednz.lst %1
cscript removeempty.vbs ..\templates\customizednz.lst %1
cscript createmst.vbs ..\templates\gendnzmst.lst %1
goto end


:usage 
echo.
echo.
echo ***** Invalid parameters *****
echo "Usage:  dnzcustomize.bat <dest_dir> <policy_file>"
echo.
goto end 

:end
