// this function verifies disk space in kilobytes
function verifyDiskSpace(dirPath, spaceRequired)
{
  var spaceAvailable;

  // Get the available disk space on the given path
  spaceAvailable = fileGetDiskSpaceAvailable(dirPath);

  // Convert the available disk space into kilobytes
  spaceAvailable = parseInt(spaceAvailable / 1024);

  // do the verification
  if(spaceAvailable < spaceRequired)
  {
    logComment("Insufficient disk space: " + dirPath);
    logComment("  required : " + spaceRequired + " K");
    logComment("  available: " + spaceAvailable + " K");
    return(false);
  }

  return(true);
}

function updateWinReg4Ren8dot3() 
{
  var fProgram      = getFolder("Program");
  var fTemp         = getFolder("Temporary");

  //Notes:
  // can't use a double backslash before subkey - Windows already puts it in.			
  // subkeys have to exist before values can be put in.
  var subkey;  // the name of the subkey you are poking around in
  var valname; // the name of the value you want to look at
  var value;   // the data in the value you want to look at.
  var winreg = getWinRegistry() ;

  if(winreg != null) 
  {
    // Here, we get the current version.
    winreg.setRootKey(winreg.HKEY_CURRENT_USER) ;  // CURRENT_USER
    subkey  = "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\RunOnce" ;

    winreg.createKey(subkey,"");
    valname = "ren8dot3";
    value   = fProgram + "ren8dot3.exe " + fTemp + "ren8dot3.ini";
    err     = winreg.setValueString(subkey, valname, value);
  }
}

function prepareRen8dot3(listLongFilePaths)
{
  var fTemp                 = getFolder("Temporary");
  var fProgram              = getFolder("Program");
  var fRen8dot3Ini          = getWinProfile(fTemp, "ren8dot3.ini");
  var bIniCreated           = false;
  var fLongFilePath;
  var sShortFilePath;

  if(fRen8dot3Ini != null)
  {
    for(i = 0; i < listLongFilePaths.length; i++)
    {
      fLongFilePath   = getFolder(fProgram, listLongFilePaths[i]);
      sShortFilePath  = File.windowsGetShortName(fLongFilePath);
      if(sShortFilePath)
      {
        fRen8dot3Ini.writeString("rename", sShortFilePath, fLongFilePath);
        bIniCreated = true;
      }
    }

    if(bIniCreated)
      updateWinReg4Ren8dot3() ;
  }

  return(0);
}

// main
var srDest;
var err;
var communicatorFolder;
var FileRegxpcom;
var err2;

// This list contains filenames that are long filenames ( > 8.3) critical during installation time.
// Unfortunately, it is statically created.  If there are new files that are suspected to be
// locked in memory during installation of this .xpi file, then they should be listed here.
// The filenames should include paths relative to the Netscape 6 folder.
// '/' must be used as path delimiters regardless of platform.
var listLongFilePaths = ["components/vscspsign", "components/vsnpsetup.exe", "components/ptav3.dll"];

srDest = 801;
err    = initInstall("VeriSign Personal Trust Agent", "VeriSign Personal Trust Agent", "3.5.0.5"); 
logComment("initInstall: " + err);

communicatorFolder = getFolder("Program");
logComment("communicatorFolder: " + communicatorFolder);

if(verifyDiskSpace(communicatorFolder, srDest))
{
  setPackageFolder(communicatorFolder);

  // Ren8dot3 process needs to be done before any files have been installed
  // (this includes the temp files during the prepare phase)
  prepareRen8dot3(listLongFilePaths);

  err = addDirectory("",
                     "3.5.0.5",
                     "components",              // dir name in jar to extract 
                     communicatorFolder, // Where to put this file (Returned from getFolder) 
                     "components",                 // subdir name to create relative to communicatorFolder
                     true );             // Force Flag 
  logComment("addDirectory() returned: " + err);

	
  execute("components/vsnpsetup.exe", "NS6");
	
//alert("before execute");
	FileRegxpcom = getFolder("file:///", communicatorFolder + "regxpcom.exe");
//	alert (FileRegxpcom);
	err2 = File.execute(FileRegxpcom);
//	alert (err2);
//alert("after execute");

  // check return value
  if(!err)
  {
    err = performInstall(); 
    logComment("performInstall() returned: " + err);
  }
  else
    cancelInstall(err);

}
else
  cancelInstall(INSUFFICIENT_DISK_SPACE);

// end main
