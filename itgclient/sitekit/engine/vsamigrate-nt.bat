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

REM Clean up before run.
if exist %2\log\VSApps\migrate.log (
   del %2\log\VSApps\migrate.log
)
if exist %2\log\VSApps\temp.log (
   del %2\log\VSApps\temp.log
)

customizer.exe -f ..\fragments\VSApps -c ..\templates\vsapps_nt.lst -s %1 -d %2 -p %3 -l %2/log/VSApps/migrate.log -u check

REM Reformat migrate.log file.
if exist %2\log\VSApps\migrate.log. (
   REM Search for "INFO-UPDATE"
   move %2\log\VSApps\migrate.log %2\log\VSApps\temp.log
   findstr "INFO-UPDATE" %2\log\VSApps\temp.log > %2\log\VSApps\migrate.log   

   REM Search for not "Fragment"
   if exist %2\log\VSApps\migrate.log (
      del %2\log\VSApps\temp.log
      move %2\log\VSApps\migrate.log %2\log\VSApps\temp.log
      findstr /v "Fragment" %2\log\VSApps\temp.log > %2\log\VSApps\migrate.log
   )

   REM Search for not ".fdf"
   if exist %2\log\VSApps\migrate.log (
      del %2\log\VSApps\temp.log
      move %2\log\VSApps\migrate.log %2\log\VSApps\temp.log
      findstr /v ".fdf" %2\log\VSApps\temp.log > %2\log\VSApps\migrate.log
   )
)

del %2\log\VSApps\temp.log

echo Because of template changes in the new site kit, some of your locally > %2\log\VSApps\temp.log
echo hosted HTML files might be overwritten with standard VeriSign files >> %2\log\VSApps\temp.log
echo during the upgrade procedures.  >> %2\log\VSApps\temp.log
echo. >> %2\log\VSApps\temp.log
echo If there are any files listed below, save copies of the files before >> %2\log\VSApps\temp.log
echo continuing with the upgrade. After you run the install command, you >> %2\log\VSApps\temp.log
echo must re-apply the modifications to only these files. Use the copies >> %2\log\VSApps\temp.log
echo for reference only; the structure of the new HTML files has changed >> %2\log\VSApps\temp.log
echo and requires new editing. If no files appear below, you may continue >> %2\log\VSApps\temp.log
echo with the upgrade and your HTML pages will be preserved. >> %2\log\VSApps\temp.log
echo. >> %2\log\VSApps\temp.log
echo ********************************************************************************** >> %2\log\VSApps\temp.log
echo. >> %2\log\VSApps\temp.log

if exist %2\log\VSApps\migrate.log. ( 
   type %2\log\VSApps\migrate.log >> %2\log\VSApps\temp.log
)

echo. >> %2\log\VSApps\temp.log

del %2\log\VSApps\migrate.log
move %2\log\VSApps\temp.log %2\log\VSApps\migrate.log

goto end


:usage 
echo.
echo.
echo ***** Invalid parameters *****
echo "Usage:  vsamigrate-nt.bat <src_dir> <dest_dir> <policy_file>"
echo.
goto end 

:end
