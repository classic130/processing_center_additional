To generate the Zip file (OSEXSETP.exe) follow these instructions :
- ExSec32.dll does not get built - so include it as it is and is present in this directory

- OL98QFE.exe does not get built - so include it as it is and is present in this directory

- oesetupw.exe gets built and is present in this directory

- VSCnfChk.dll gets built and gets generated at itgclient/client/apps/pta/activex/vsvnfchk/ReleaseMinDependency OR
						itgclient/client/lib/dynamic/Release directory

	NOTE : As VSCnfChk has not been checked in, it should be picked from this directory itself.
               Once VSCnfChk is built properly, we should pick it from the itgclient/client/lib/dynamic/Release directory

- VSSgnAtb.dll gets built and is present in this directory

- VSImport.dll gets built and is present in this directory

- VSGSE.dll gets built and is present in this directory

- VSGSEExt.dll gets built and is present in this directory

- Add all these files in a zip file called OSEXSETP.zip

- Use this file to generate the self extracting executable.

To generate Self Extracting Executable follow these instructions :

- Open the GUI for WinZip Self-Extractor
- Select the "Standard self-extracting Zip file" Radio button and click Next
- Leave "Span multiple removable disks" checkbox unchecked
- Select the zip file whose self-extracting executable is to be created and 
  click Next. If you asked whether to replace the previously existing 
  executable, then select Yes.
- Do not enter anything in the "Enter message text" text box and click Next.
- Enter C:\Program Files\VeriSign\OnSite\GSE as the default folder
  where the files are unzipped. Press Next.
- Enter "oesetupw" in the "Command and parameter" text box. This program gets
  executed after the files are unzipped. Press Next.
- Keep the "About" box message empty and Press Next.
- Do not enter anything in the "Icon filename" text box and click Next.
- Check the checkbox against "Default to overwrite files without prompting".
- Also check the "Unzip Automatically" checkbox. If you are prompted to 
  with a warning dialog box at this point, just press the "Yes" button.
- Click Next on the Summary screen.
- This will generate a self-extrating executable with the same same as the 
  input zip file, except the file extension is .exe instead of .zip.

- run signit.bat (in this directory) which uses a private key (you
need to insert in floppy or cdrom) to generate a signed version of 
this file.
