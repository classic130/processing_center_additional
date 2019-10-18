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

package com.dstc.security.certpath;

import java.util.Arrays;
import java.math.BigInteger;
import java.security.cert.X509Certificate;

import com.dstc.security.common.OID;

public class X509CertSelector
{
  private String issuer = null;
  private BigInteger serialNumber = null;
  private byte[] ski = null;

  public X509CertSelector() {}

  public void setIssuerDN(String issuer)
  {
    this.issuer = issuer;
  }

  public void setSerialNumber(BigInteger ser)
  {
    this.serialNumber = ser;
  }

  public void setSubjectKeyIdentifier(byte[] ski)
  {
    this.ski = ski;
  }

  public boolean match(X509Certificate cert)
  {
    if (issuer != null)
    {
      if (!checkIssuerDN(cert))
        return false;
    }

    if (serialNumber != null)
    {
      if (!checkSerialNumber(cert))
        return false;
    }

    if (ski != null)
    {
System.out.println("Sel:ski");
      if (!checkSubjectKeyIdentifier(cert))
        return false;
    }

    return true;
  }

  private boolean checkIssuerDN(X509Certificate cert)
  {
    return (cert.getIssuerDN().getName().equals(this.issuer));
  }

  private boolean checkSerialNumber(X509Certificate cert)
  {
    return (cert.getSerialNumber().equals(this.serialNumber));
  }

  private boolean checkSubjectKeyIdentifier(X509Certificate cert)
  {
    byte[] val = cert.getExtensionValue(OID.subjectKeyIdentifier);
    if (val == null)
      return false;
 
    byte[] certSki = new byte[val.length - 4];
    System.arraycopy(val, 4, certSki, 0, certSki.length);
    return Arrays.equals(this.ski, certSki);
  }
}
