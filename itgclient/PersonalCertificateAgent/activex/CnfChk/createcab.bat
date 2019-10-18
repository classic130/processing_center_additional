cabarc N "vscnfchk.cab" "..\..\lib\dynamic\release\vscnfchk.dll" "..\..\lib\dynamic\release\vscnfchk.inf"

signcode -spc a:\newcert.spc -v a:\newvs.pvk -n "VeriSign Configuration Checker" -i "http://www.verisign.com" -t "http://timestamp.verisign.com/scripts/timstamp.dll" vscnfchk.cab	
