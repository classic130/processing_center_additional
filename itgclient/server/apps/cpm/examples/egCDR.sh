#!/bin/sh
echo "Content-type: text/html\n\n"
echo "<html>"
echo "<head>"
echo "<title>"$HTTP_VSCERT_CN"</title>"
echo "</head>"
echo "<body background='binary.gif'>"
echo "<center><h2>Welcome $HTTP_VSCERT_CN</h2>"
echo "<b>Here's the certificate you presented:</b></center><br>"
echo "<center><table border=5 cellpadding=5>"
echo "  <th colspan=2>"
echo      $HTTP_VSCERT_OU1
echo "  </th>"
echo "  <tr>"
echo "    <td align=right><b>"
echo "      cn= "
echo "    </b></td>"
echo "    <td><b>"
echo        $HTTP_VSCERT_CN
echo "    </b></td>"
echo "  </tr>"
echo "  <tr>"
echo "    <td align=right><b>"
echo "      email= "
echo "    </b></td>"
echo "    <td><b>"
echo        $HTTP_VSCERT_EMAIL
echo "    </b></td>"
echo "  </tr>"
# Create a row for each OU element and display it.
i=1
while [ "$i" -le "$HTTP_VSCERT_OUCOUNT" ]
do
  OU='HTTP_VSCERT_OU'$i
  echo "  <tr>"
  echo "    <td align=right><b>"
  echo "      ou$i= "
  echo "    </b></td>"
  echo "    <td><b>"
  /usr/ucb/printenv $OU
  echo "    </b></td>"
  echo "  </tr>"
  i=`expr $i + 1`
done
echo "  <tr>"
echo "    <td align=right><b>"
echo "      uniqueIdentifier= "
echo "    </b></td>"
echo "    <td><b>"
echo        $HTTP_VSCERT_UNIQUE
echo "    </b></td>"
echo "  </tr>"
echo "  <tr>"
echo "    <td align=right><b>"
echo "      not before= "
echo "    </b></td>"
echo "    <td><b>"
echo        $HTTP_VSCERT_NOTBEFORE
echo "    </b></td>"
echo "  </tr>"
echo "  <tr>"
echo "    <td align=right><b>"
echo "      not after= "
echo "    </b></td>"
echo "    <td><b>"
echo        $HTTP_VSCERT_NOTAFTER
echo "    </b></td>"
echo "  </tr>"
echo "</table></center>"
echo "</body>"
echo "</html>"
