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


import java.io.*;
import java.util.Set;
import java.util.HashSet;
import java.security.cert.X509Certificate;

import com.dstc.security.asn1.Asn1;
import com.dstc.security.asn1.Asn1Exception;
import com.dstc.security.asn1.Sequence;
import com.dstc.security.asn1.OctetString;
import com.dstc.security.asn1.Oid;
import com.dstc.security.common.OID;
import com.dstc.security.x509.extns.*;

/**
 * A factory class for Extensions
 *
 * @author Ming Yung
 */
public class ExtensionFactory
{
  public static ExtensionValue getExtension(String extnID, Asn1 oct) 
  {
    try
    {
      ExtensionValue ext = null;

      Asn1 asn1 = Asn1.getAsn1(((OctetString)oct).getBytes());
      
      if (extnID.equals(OID.netscapeCertType))
        return new NetscapeCertType(asn1);

      if (extnID.equals(OID.basicConstraints))
        return new BasicConstraints(asn1);

      if (extnID.equals(OID.authorityKeyIdentifier))
        return new AuthorityKeyIdentifier(asn1);

      if (extnID.equals(OID.subjectKeyIdentifier))
        return new SubjectKeyIdentifier(asn1);

      if (extnID.equals(OID.keyUsage))
        return new KeyUsage(asn1);

      if (extnID.equals(OID.issuerAltName))
        return new IssuerAltName(asn1);

      if (extnID.equals(OID.subjectAltName))
        return new SubjectAltName(asn1);

      if (extnID.equals(OID.policyConstraints))
        return new PolicyConstraints(asn1);

      if (extnID.equals(OID.nameConstraints))
        return new NameConstraints(asn1);

      if (extnID.equals(OID.extKeyUsage))
        return new ExtendedKeyUsage(asn1);

      if (extnID.equals(OID.cRLDistributionPoints))
        return new CRLDistributionPoints(asn1);

      if (extnID.equals(OID.cRLNumber))
        return new CRLNumber(asn1);

      if (extnID.equals(OID.certificatePolicies))
        return new CertificatePolicies(asn1);

      return ext;
    }
    catch (Exception e)
    {
        throw new RuntimeException();
    }
  }

  public static ExtensionValue getExtension(String oid, X509Certificate cert)
    throws Asn1Exception
  {
    byte[] encoded = cert.getExtensionValue(oid);
    if (encoded == null)
      return null;

    /*Sequence seq = new Sequence();

    try
    {
      seq.add(new Oid(oid));
      seq.add(Asn1.getAsn1(encoded));
    }
    catch (Asn1Exception e)
    {
      return null;
    }*/

     return getExtension(oid, Asn1.getAsn1(encoded));
  }
}
