//alert("made it to the install.js script!");

// Conditional alert.
function cAlert (message) {
   if (!this.silent)
      alert(message);
}

// Conditional confirm.
function cConfirm (message) {
   if (this.silent)
      return true;
   else
      return confirm(message);
}

// Variable indicating whether or not installation should proceed.
bInstall = true;

// Make sure Java is enabled before doing anything else.
if ( !navigator.javaEnabled() ) {
   bInstall = false;
   cAlert ("Java must be enabled to install.");
}

// Make sure installation is attempted on correct machine architecture.
else if ( navigator.platform != "Win32" ) {
   bInstall = false;
   cAlert ("This plug-in only runs on Win32 platforms.");
}

// Check user-interface language, if appropriate.
else if ( navigator.language != "en" ) {
   bInstall = cConfirm("This plug-in uses the English language. You do not appear to be using English on this machine. Install anyway?");
}


// If all conditions look good, proceed with the installation.
if (bInstall) {
   // Create a version object and a software update object
   vi = new netscape.softupdate.VersionInfo(1, 0, 0, 3);
   su = new netscape.softupdate.SoftwareUpdate(this,
       "VeriSign Personal Trust Agent Plug-in");

   // Start the install process
   err = su.StartInstall("plugins/verisign/vsnp", vi,
       netscape.softupdate.SoftwareUpdate.FULL_INSTALL);

   if (err != 0)      cAlert ("Installation error. Aborting.");

   else {
      bAbort = false;

      // Find the plug-ins directory on the user's machine
     PIFolder = su.GetFolder("Plugins");


      // Install the files. Unpack them and list where they go
	// npexport.dll
	// NPPref32.dll
	// VSCnfChk.dll
	// VSExport.class
	// VSExports.dll
	// VSImport.dll
	// VSPref.class
	// VSPref.dll

      err = su.AddSubcomponent("npexport DLL", vi, "npexport.dll",
         PIFolder, "", this.force);
	  if (err != 0)
		cAlert ("Failed to install component npexport.dll. Error " + err);

      bAbort = bAbort || (err !=0);


      if (!bAbort) {
         err = su.AddSubcomponent("NPPref32 DLL", vi, "NPPref32.dll",
            PIFolder, "", this.force);
		 if (err != 0)
			cAlert ("Failed to install component NPPref32.dll. Error " + err);

         bAbort = bAbort || (err !=0);
      }

      if (!bAbort) {
         err = su.AddSubcomponent("VSCnfChk DLL", vi, "VSCnfChk.dll",
             PIFolder, "", this.force);
		 if (err != 0)
			cAlert ("Failed to install component VSCnfChk.dll. Error " + err);

         bAbort = bAbort || (err !=0);
      }

      if (!bAbort) {
         err = su.AddSubcomponent("VSExport CLASS", vi, "VSExport.class",
             PIFolder, "", this.force);
		 if (err != 0)
			cAlert ("Failed to install component VSExport.class. Error " + err);

         bAbort = bAbort || (err !=0);
      }

      if (!bAbort) {
         err = su.AddSubcomponent("VSExport DLL", vi, "VSExports.dll",
             PIFolder, "", this.force);
		 if (err != 0)
			cAlert ("Failed to install component VSExports.dll. Error " + err);

         bAbort = bAbort || (err !=0);
      }

      if (!bAbort) {
         err = su.AddSubcomponent("VSImport DLL", vi, "VSImport.dll",
             PIFolder, "", this.force);
		 if (err != 0)
			cAlert ("Failed to install component VSImport.dll. Error " + err);

         bAbort = bAbort || (err !=0);
      }

      if (!bAbort) {
         err = su.AddSubcomponent("VSPref CLASS", vi, "VSPref.class",
             PIFolder, "", this.force);
		 if (err != 0)
			cAlert ("Failed to install component VSPref.class. Error " + err);

         bAbort = bAbort || (err !=0);
      }

      if (!bAbort) {
         err = su.AddSubcomponent("VSPref DLL", vi, "VSPref.dll",
             PIFolder, "", this.force);
		 if (err != 0)
			cAlert ("Failed to install component VSPref.dll. Error " + err);

         bAbort = bAbort || (err !=0);
      }

	  if (!bAbort) {
		 err = su.Execute("vsnpsetup.exe");
		 if (err != 0)
			cAlert ("Failed to execute component vsnpsetup.exe. Error " + err);

		 bAbort = bAbort || (err != 0);
	  }

   }


   // Unless there was a problem, move files to final location
   // and update the Client Version Registry
   if (bAbort) {
      cAlert ("Installation error. Aborting.");
      su.AbortInstall();
   }
   else {
      err = su.FinalizeInstall();

      // Refresh list of available plug-ins
      if (err == 0)
         navigator.plugins.refresh(true);
      else if (err == 999) {
         cAlert("You must reboot to finish this installation.");
         err = 0;
      }
   }

   if ( bAbort || err != 0 )
      cAlert("Install encountered errors. Please contact your Administrator for assistance.");
}
