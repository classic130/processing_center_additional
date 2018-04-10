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
print "</table></center>\n";
print "</body>\n";
print "</html>\n";