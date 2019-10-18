
iDefense found a buffer overflow vulnerability in vscnfchk.dll activex control. This activex control was used during Windows98 and WinNT time to check that strong crypto libraries are installed. It is not used anymore.

To fix the vulnerability following things have been decided

1> To make all the functions in activex control NOOP.
2> To release a patch that will uninstall defective activex control at the end user machine.
3> Patch is a msi file that invokes a vbscript mpki_vscnfchk_sp1.vbs.
4> Script file searches the registry using the class id of activex control.
5> If it finds entry in registry, it gets the path of activex control.
6> It deletes the activex control and deletes the registry entry of activex control.


