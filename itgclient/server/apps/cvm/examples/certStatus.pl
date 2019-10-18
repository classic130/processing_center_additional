#!/usr/local/bin/perl

# This shows how to parse the certificate status code
# and return a customized error page.

sub certStatusString {
 
    my ($statusString);
    
    if ($_[0]=="2") {
        $statusString = "Certificate Pending";
    }
    elsif ($_[0]=="3") {
        $statusString = "Certificate Expired";
    }
    elsif ($_[0]=="4") {
        $statusString = "Server Error: CRL Expired";
    }
    elsif ($_[0]=="5") {
        $statusString = "Server Error: CRL Unavailable";
    }
    elsif ($_[0]=="6") {
        $statusString = "Certificate Revoked";
    }
    else {
        # includes undefined values.
        $statusString = "Server Error: Certificate Failure";
    }
    
    return $statusString;
}

print "Content-type: Text/html\n";
print "\n";
print "<html>\n";
print "<title>Certificate Status</title>\n";
print "<body>\n";
print "<h1>\n";

print certStatusString($ENV{"QUERY_STRING"});
print "\n";

print "</h1>\n";

print "Your client is not allowed to access the requested object.\n";
print "<HR>(c) 1998, VeriSign, Inc.\n";
print "</body>\n";
print "</html>\n";

