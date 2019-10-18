#!/usr/local/bin/perl
print "Content-type: text/html\n\n\n";
print "<html>\n";
print "<head>\n";
print "<title>$ENV{'HTTP_VSCERT_CN'}</title>\n";
print "</head>\n";
print "<body background='binary.gif'>\n";
print "<center><h2>Welcome $ENV{'HTTP_VSCERT_CN'}</h2>\n";
print "<b>Here's the certificate you presented:</b></center><br>\n";
print "<center><table border=5 cellpadding=5>\n";
print "  <th colspan=2>\n";
print "     $ENV{'HTTP_VSCERT_OU1'}";
print "  </th>\n";
print "  <tr>\n";
print "    <td align=right><b>\n";
print "      cn= \n";
print "    </b></td>\n";
print "    <td><b>\n";
print "      $ENV{'HTTP_VSCERT_CN'}";
print "    </b></td>\n";
print "  </tr>\n";
print "  <tr>\n";
print "    <td align=right><b>\n";
print "      KeyUsage= \n";
print "    </b></td>\n";
print "    <td><b>\n";
print "    $ENV{'HTTP_VSCERT_EX_KEYUSAGE'}";
print "    </b></td>\n";
print "  </tr>\n";
print "  <tr>\n";
print "    <td align=right><b>\n";
print "      Extended KeyUsage= \n";
print "    </b></td>\n";
print "    <td><b>\n";
print "    $ENV{'HTTP_VSCERT_EX_EKU'}";
print "    </b></td>\n";
print "  </tr>\n";
print "  <tr>\n";
print "    <td align=right><b>\n";
print "      email= \n";
print "    </b></td>\n";
print "    <td><b>\n";
print "      $ENV{'HTTP_VSCERT_EMAIL'}";
print "    </b></td>\n";
print "  </tr>\n";
# Create a row for each OU element and display it.
$i=1;
 while ($i <= $ENV{'HTTP_VSCERT_OUCOUNT'}) {
  $OU = "HTTP_VSCERT_OU".$i;
  print "  <tr>\n";
  print "    <td align=right><b>\n";
  print "      ou$i= \n";
  print "    </b></td>\n";
  print "    <td><b>\n";
  print       $ENV{"$OU"};
  print "    </b></td>\n";
  print "  </tr>\n";
  $i++;
 }
print "  <tr>\n";
print "    <td align=right><b>\n";
print "      uniqueIdentifier= \n";
print "    </b></td>\n";
print "    <td><b>\n";
print "      $ENV{'HTTP_VSCERT_UNIQUE'}";
print "    </b></td>\n";
print "  </tr>\n";
print "  <tr>\n";
print "    <td align=right><b>\n";
print "      not before= \n";
print "    </b></td>\n";
print "    <td><b>\n";
print "      $ENV{'HTTP_VSCERT_NOTBEFORE'}";
print "    </b></td>\n";
print "  </tr>\n";
print "  <tr>\n";
print "    <td align=right><b>\n";
print "      not after= \n";
print "    </b></td>\n";
print "    <td><b>\n";
print "      $ENV{'HTTP_VSCERT_NOTAFTER'}";
print "    </b></td>\n";
print "  </tr>\n";
# Create a row for each HTTP_VSCERT_EX_SAN_DIRNAME element and display it.
$i=1;
 while ($i <= $ENV{'HTTP_VSCERT_EX_SAN_DIRNAMECOUNT'}) {
  $OU = "HTTP_VSCERT_EX_SAN_DIRNAME".$i;
  print "  <tr>\n";
  print "    <td align=right><b>\n";
  print "      san_dirname$i= \n";
  print "    </b></td>\n";
  print "    <td><b>\n";
  print       $ENV{"$OU"};
  print "    </b></td>\n";
  print "  </tr>\n";
  $i++;
 }
# Create a row for each HTTP_ VSCERT_EX_SAN_RFC822 element and display it.
$i=1;
 while ($i <= $ENV{'HTTP_VSCERT_EX_SAN_RFC822COUNT'}) {
  $OU = "HTTP_VSCERT_EX_SAN_RFC822".$i;
  print "  <tr>\n";
  print "    <td align=right><b>\n";
  print "      san_rfc822$i= \n";
  print "    </b></td>\n";
  print "    <td><b>\n";
  print       $ENV{"$OU"};
  print "    </b></td>\n";
  print "  </tr>\n";
  $i++;
 }
# Create a row for each HTTP_VSCERT_EX_SAN_DNSNAME element and display it.
$i=1;
 while ($i <= $ENV{'HTTP_VSCERT_EX_SAN_DNSNAMECOUNT'}) {
  $OU = "HTTP_VSCERT_EX_SAN_DNSNAME".$i;
  print "  <tr>\n";
  print "    <td align=right><b>\n";
  print "      san_dnsname$i= \n";
  print "    </b></td>\n";
  print "    <td><b>\n";
  print       $ENV{"$OU"};
  print "    </b></td>\n";
  print "  </tr>\n";
  $i++;
 }
# Create a row for each HTTP_VSCERT_EX_SAN_URI element and display it.
$i=1;
 while ($i <= $ENV{'HTTP_VSCERT_EX_SAN_URICOUNT'}) {
  $OU = "HTTP_VSCERT_EX_SAN_URI".$i;
  print "  <tr>\n";
  print "    <td align=right><b>\n";
  print "      san_uri$i= \n";
  print "    </b></td>\n";
  print "    <td><b>\n";
  print       $ENV{"$OU"};
  print "    </b></td>\n";
  print "  </tr>\n";
  $i++;
 }
# Create a row for each HTTP_VSCERT_EX_SAN_UPN element and display it.
$i=1;
 while ($i <= $ENV{'HTTP_VSCERT_EX_SAN_UPNCOUNT'}) {
  $OU = "HTTP_VSCERT_EX_SAN_UPN".$i;
  print "  <tr>\n";
  print "    <td align=right><b>\n";
  print "      san_upn$i= \n";
  print "    </b></td>\n";
  print "    <td><b>\n";
  print       $ENV{"$OU"};
  print "    </b></td>\n";
  print "  </tr>\n";
  $i++;
 }
# Create a row for each HTTP_VSCERT_EX_SAN_GUID element and display it.
$i=1;
 while ($i <= $ENV{'HTTP_VSCERT_EX_SAN_GUIDCOUNT'}) {
  $OU = "HTTP_VSCERT_EX_SAN_GUID".$i;
  print "  <tr>\n";
  print "    <td align=right><b>\n";
  print "      san_guid$i= \n";
  print "    </b></td>\n";
  print "    <td><b>\n";
  print       $ENV{"$OU"};
  print "    </b></td>\n";
  print "  </tr>\n";
  $i++;
 }
# Create a row for each HTTP_VSCERT_EX_CDP_DPN_DIRNAME element and display it.
$i=1;
 while ($i <= $ENV{'HTTP_VSCERT_EX_CDP_DPN_DIRNAMECOUNT'}) {
  $OU = "HTTP_VSCERT_EX_CDP_DPN_DIRNAME".$i;
  print "  <tr>\n";
  print "    <td align=right><b>\n";
  print "      cdp_dirname$i= \n";
  print "    </b></td>\n";
  print "    <td><b>\n";
  print       $ENV{"$OU"};
  print "    </b></td>\n";
  print "  </tr>\n";
  $i++;
 }
# Create a row for each HTTP_VSCERT_EX_CDP_DPN_RFC822 element and display it.
$i=1;
 while ($i <= $ENV{'HTTP_VSCERT_EX_CDP_DPN_RFC822COUNT'}) {
  $OU = "HTTP_VSCERT_EX_CDP_DPN_RFC822".$i;
  print "  <tr>\n";
  print "    <td align=right><b>\n";
  print "      cdp_rfc822$i= \n";
  print "    </b></td>\n";
  print "    <td><b>\n";
  print       $ENV{"$OU"};
  print "    </b></td>\n";
  print "  </tr>\n";
  $i++;
 }
# Create a row for each HTTP_VSCERT_EX_CDP_DPN_DNSNAME element and display it.
$i=1;
 while ($i <= $ENV{'HTTP_VSCERT_EX_CDP_DPN_DNSNAMECOUNT'}) {
  $OU = "HTTP_VSCERT_EX_CDP_DPN_DNSNAME".$i;
  print "  <tr>\n";
  print "    <td align=right><b>\n";
  print "      cdp_dnsname$i= \n";
  print "    </b></td>\n";
  print "    <td><b>\n";
  print       $ENV{"$OU"};
  print "    </b></td>\n";
  print "  </tr>\n";
  $i++;
 }
# Create a row for each HTTP_VSCERT_EX_CDP_DPN_URI element and display it.
$i=1;
 while ($i <= $ENV{'HTTP_VSCERT_EX_CDP_DPN_URICOUNT'}) {
  $OU = "HTTP_VSCERT_EX_CDP_DPN_URI".$i;
  print "  <tr>\n";
  print "    <td align=right><b>\n";
  print "      cdp_uri$i= \n";
  print "    </b></td>\n";
  print "    <td><b>\n";
  print       $ENV{"$OU"};
  print "    </b></td>\n";
  print "  </tr>\n";
  $i++;
 }
# Create a row for each HTTP_VSCERT_EX_CDP_DPN_UPN element and display it.
$i=1;
 while ($i <= $ENV{'HTTP_VSCERT_EX_CDP_DPN_UPNCOUNT'}) {
  $OU = "HTTP_VSCERT_EX_CDP_DPN_UPN".$i;
  print "  <tr>\n";
  print "    <td align=right><b>\n";
  print "      cdp_upn$i= \n";
  print "    </b></td>\n";
  print "    <td><b>\n";
  print       $ENV{"$OU"};
  print "    </b></td>\n";
  print "  </tr>\n";
  $i++;
 }
# Create a row for each HTTP_VSCERT_EX_CDP_DPN_GUID element and display it.
$i=1;
 while ($i <= $ENV{'HTTP_VSCERT_EX_CDP_DPN_GUIDCOUNT'}) {
  $OU = "HTTP_VSCERT_EX_CDP_DPN_GUID".$i;
  print "  <tr>\n";
  print "    <td align=right><b>\n";
  print "      cdp_guid$i= \n";
  print "    </b></td>\n";
  print "    <td><b>\n";
  print       $ENV{"$OU"};
  print "    </b></td>\n";
  print "  </tr>\n";
  $i++;
 }
# Create a row for each HTTP_VSCERT_EX_CDP_CRL_DIRNAME element and display it.
$i=1;
 while ($i <= $ENV{'HTTP_VSCERT_EX_CDP_CRL_DIRNAMECOUNT'}) {
  $OU = "HTTP_VSCERT_EX_CDP_CRL_DIRNAME".$i;
  print "  <tr>\n";
  print "    <td align=right><b>\n";
  print "      cdp_crl_dirname$i= \n";
  print "    </b></td>\n";
  print "    <td><b>\n";
  print       $ENV{"$OU"};
  print "    </b></td>\n";
  print "  </tr>\n";
  $i++;
 }
# Create a row for each HTTP_VSCERT_EX_CDP_CRL_RFC822 element and display it.
$i=1;
 while ($i <= $ENV{'HTTP_VSCERT_EX_CDP_CRL_RFC822COUNT'}) {
  $OU = "HTTP_VSCERT_EX_CDP_CRL_RFC822".$i;
  print "  <tr>\n";
  print "    <td align=right><b>\n";
  print "      cdp_crl_rfc822$i= \n";
  print "    </b></td>\n";
  print "    <td><b>\n";
  print       $ENV{"$OU"};
  print "    </b></td>\n";
  print "  </tr>\n";
  $i++;
 }
# Create a row for each HTTP_VSCERT_EX_CDP_CRL_DNSNAME element and display it.
$i=1;
 while ($i <= $ENV{'HTTP_VSCERT_EX_CDP_CRL_DNSNAMECOUNT'}) {
  $OU = "HTTP_VSCERT_EX_CDP_CRL_DNSNAME".$i;
  print "  <tr>\n";
  print "    <td align=right><b>\n";
  print "      cdp_crl_dnsname$i= \n";
  print "    </b></td>\n";
  print "    <td><b>\n";
  print       $ENV{"$OU"};
  print "    </b></td>\n";
  print "  </tr>\n";
  $i++;
 }
# Create a row for each HTTP_VSCERT_EX_CDP_CRL_URI element and display it.
$i=1;
 while ($i <= $ENV{'HTTP_VSCERT_EX_CDP_CRL_URICOUNT'}) {
  $OU = "HTTP_VSCERT_EX_CDP_CRL_URI".$i;
  print "  <tr>\n";
  print "    <td align=right><b>\n";
  print "      cdp_crl_uri$i= \n";
  print "    </b></td>\n";
  print "    <td><b>\n";
  print       $ENV{"$OU"};
  print "    </b></td>\n";
  print "  </tr>\n";
  $i++;
 }
# Create a row for each HTTP_VSCERT_EX_CDP_CRL_UPN element and display it.
$i=1;
 while ($i <= $ENV{'HTTP_VSCERT_EX_CDP_CRL_UPNCOUNT'}) {
  $OU = "HTTP_VSCERT_EX_CDP_CRL_UPN".$i;
  print "  <tr>\n";
  print "    <td align=right><b>\n";
  print "      cdp_crl_upn$i= \n";
  print "    </b></td>\n";
  print "    <td><b>\n";
  print       $ENV{"$OU"};
  print "    </b></td>\n";
  print "  </tr>\n";
  $i++;
 }
# Create a row for each HTTP_VSCERT_EX_CDP_CRL_GUID element and display it.
$i=1;
 while ($i <= $ENV{'HTTP_VSCERT_EX_CDP_CRL_GUIDCOUNT'}) {
  $OU = "HTTP_VSCERT_EX_CDP_CRL_GUID".$i;
  print "  <tr>\n";
  print "    <td align=right><b>\n";
  print "      cdp_crl_guid$i= \n";
  print "    </b></td>\n";
  print "    <td><b>\n";
  print       $ENV{"$OU"};
  print "    </b></td>\n";
  print "  </tr>\n";
  $i++;
 }
print "</table></center>\n";
print "</body>\n";
print "</html>\n";
