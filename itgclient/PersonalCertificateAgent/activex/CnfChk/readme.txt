README.TXT - For the VSCnfChk ActiveX control and the sample script that demonstrates how to use this control.

Introduction
------------

VSCnfChk is an ActiveX control that can be used to determine the versions of various files on the user's system and to determine if the Enhanced Cryptograhic Service Provider is installed correctly. This helps to determine a systems environment, which is useful while performing a diagnosis during troubleshooting. A scripting language such as VBScript or JavaScript can be used to invoke the methods of this ActiveX control.

This document contains the following
1. Requirements.
2. Contents information.
3. Installation instructions.
4. Information about the sample script. 


Required Software
-----------------
1. IIS or Netscape Web Server to host the sample html file
2. Internet Explorer
3. Windows NT/95


Contents
--------
This package contains the following directories and files -
1. Readme.txt - This file
2. VSCnfChk.dll - This is the VSCnfChk ActiveX control executable.
3. VSCnfChk.html - The sample html file which demonstrates how the VSCnfChk ActiveX
   control can be used to obtain file version information.


Installation Instructions
-------------------------

The VSCnfChk ActiveX control needs to be stored on the web server which hosts the web page that uses 
VSCnfChk. This web server can be either a Netscape web server or IIS. To install the VSCnfChk ActiveX
control simply copy the file VSCnfChk.dll, into any directory which is accessible to the web server. When the web page, that uses the ActiveX control 
is accessed, the web server will obtain the VSCnfChk.dll file and send it to the browser accessing the page. 
Thus the browser automatically downloads the ActiveX control form the server as and when required. In the remainder
 of the document the directory to which VSCnfChk.dll is copied will be referred to as the VSCnfChk directory.

Copy the sample html file into a directory that is accessible by the web server. Open this file
in a text editor and search for the line 
	CODEBASE="http://my.webserver.address/vscnfchk.dll.location/vscnfchk.dll"
and change my.webserver.address to the URL of your web server. Change vscnfchk.dll.location to the location of the VSCnfChk directory.


Sample Application Information
------------------------------
To obtain diagnostic information about a system, simply use the Internet Explorer on that system 
to visit the web page "vscnfchk.html" on the web server hosting this page. The sample page will display
the versions of the crypt32.dll and advapi32.dll located on the system. It will also display information
about the enhanced cryptographic provider located on the system.


