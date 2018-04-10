//////////////////////////////////////////////////////////////////////////// 
// 
// Copyright (C) DSTC Pty Ltd (ACN 052 372 577) 1993, 1994, 1995.
// Unpublished work.  All Rights Reserved.
// 
// The software contained on this media is the property of the
// DSTC Pty Ltd.  Use of this software is strictly in accordance
// with the license agreement in the accompanying LICENSE.DOC 
// file. If your distribution of this software does not contain 
// a LICENSE.DOC file then you have no rights to use this 
// software in any manner and should contact DSTC at the address 
// below to determine an appropriate licensing arrangement.
// 
//      DSTC Pty Ltd
//      Level 7, GP South
//      University of Queensland
//      St Lucia, 4072
//      Australia
//      Tel: +61 7 3365 4310
//      Fax: +61 7 3365 4311
//      Email: jcsi@dstc.qut.edu.au
// 
// This software is being provided "AS IS" without warranty of
// any kind.  In no event shall DSTC Pty Ltd be liable for
// damage of any kind arising out of or in connection with
// the use or performance of this software.
// 
//////////////////////////////////////////////////////////////////////////// 

package com.dstc.security.x509;

import java.security.Provider;
import java.security.AccessController;

import com.dstc.security.util.Dependencies;

public final class DSTC extends Provider 
{
  private static String name;
  private static String info;
  private static double version;

  static
  {
    name    = "DSTC_X509";
    version = -1.0;

    // Check that we have the required JAR files and versions;
    // incidentally get our version number
    String versionString = Dependencies.check(DSTC.class, false);
    if (versionString != null) {
      int firstDot = versionString.indexOf('.');
      if (firstDot >= 0) {
        int secondDot = versionString.indexOf('.', firstDot + 1);
        if (secondDot > 0) {
          // a.b.c or more;  use "a.b", ignore the rest
          versionString = versionString.substring(0, secondDot);
        }
      }
      try {
        version = Double.parseDouble(versionString);
      }
      catch (NumberFormatException ex) {
        // Don't abort;  use the dummy version (-1.0) and keep going
      }
    }

    StringBuffer sb = new StringBuffer();
    sb.append("DSTC Security Provider ");
    sb.append("(" + name + ") v" );
    sb.append((versionString == null) ? "?.?" : versionString);
    sb.append(" : \n");
    sb.append("  CertificateFactory for X.509 v3 Certificates and CRLs");
    info = sb.toString();
  }
  
  public DSTC() 
  {
    super(name, version, info);

    AccessController.doPrivileged(
      new java.security.PrivilegedAction() {
        public Object run() {

          // Certificate factories

          put("CertificateFactory.X509", 
            "com.dstc.security.x509.X509CertificateFactory");

          put("Alg.Alias.CertificateFactory.X.509", "X509"); 

          return null;
        }
      }
    );
  }
}
