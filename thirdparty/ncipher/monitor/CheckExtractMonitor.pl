#!/usr/local/bin/perl

$NVPFILE1 = "./checkextract.nvp";
$TMPFILE = "/var/tmp/CheckExtractMonitor.tmp";
$TIMEOUT = 20000;

# test url
$URL1 = "https://digitalid.verisign.com/cgi-bin/sophia.exe";
$RESP1 = "Invalid Token Number";
# error code range
$RetCodeStart = 0x10025020;
$RetCodeEnd = 0x100250FF;
$SSLWEB = "sslweb";

######################################################
# main procedure
$SIG{ALRM} = \&timeout;
$PID = fork;
if ($PID == 0) { # child, do the work
    if (check_service($URL1, $NVPFILE1, $RESP1) != 0) {
        exit 1;
    }
} else { # parent, set the timeout
    alarm($TIMEOUT);
    wait;
    alarm(0);
}

sub timeout {
    kill 9, $PID;
    printf("%x|critical|NC001 service enrollment timeout|NULL\n", $RetCodeStart+1);
    exit 9;
}

sub check_service {
    my ($url, $nvp, $resp) = @_;
    my $outfile = $TMPFILE;
    $cmd = "$SSLWEB -n $nvp -o $outfile \"$url\" > /dev/null 2>&1";
    system("$cmd");
    open(IN, "<$outfile");
    while(<IN>) {
        if (/$resp/) {
            print "0|normal|ping NC001 service($url) success|NULL\n";
            return 0;
        }
    }
    printf("%x|critical|NC001 service($url) response error|$outfile\n", $RetCodeStart+2);
    close(IN);
    return 1;
}
