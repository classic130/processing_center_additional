#!/bin/csh

# This shows how to parse the certificate status code
# and return a customized error page.

echo "Content-type: Text/html"
echo ""
echo "<html>"
echo "<title>Certificate Status</title>"
echo "<body>"
echo "<h1>"

if (! $?QUERY_STRING) then
    setenv QUERY_STRING "0"
endif

switch ($QUERY_STRING)
    case 2:
    echo "Certificate Pending"
    breaksw

    case 3:
    echo "Certificate Expired"
    breaksw

    case 4:
    echo "Server Error: CRL Expired"
    breaksw

    case 5:
    echo "Server Error: CRL Unavailable"
    breaksw

    case 6:
    echo "Certificate Revoked"
    breaksw

    default
    echo "Server Error: Certificate Failure"
    breaksw
endsw

echo "</h1>"

echo "Your client is not allowed to access the requested object."
echo "<HR>(c) 1998, VeriSign, Inc."
echo "</body>"
echo "</html>"







