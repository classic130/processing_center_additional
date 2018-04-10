@echo off
REM echo "destination directory  : %1"
REM echo "policy file            : %2"

if (%2) == () goto usage
if (%1) == () goto usage

md %1
md %1\log\
md %1\fetpackages

xcopy/E /C /R /Q ..\templates\fetpackages\*.* %1\fetpackages\
customizer.exe -f ..\fragments -c ..\templates\customize.lst -s ..\templates -d %1 -p %2 -l %1/log/fetcustomize.log
cscript removetags.vbs ..\templates\customize.lst %1
cscript createmst.vbs ..\templates\genmst.lst %1
goto end


:usage 
echo.
echo.
echo ***** Invalid parameters *****
echo "Usage:  fetcustomize.bat <dest_dir> <policy_file>"
echo.
goto end 

:end
