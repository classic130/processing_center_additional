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

package com.dstc.security.util;

import java.util.Vector;
import java.util.Iterator;
import java.io.ByteArrayInputStream;
import java.io.PushbackInputStream;
import java.io.InputStream;
import java.io.IOException;
import java.security.cert.X509CRL;
import java.security.cert.CRLException;
import java.security.cert.CertificateFactory;
import java.security.cert.X509Certificate;
import java.security.cert.X509CRL;
import java.security.cert.CertificateEncodingException;
import java.security.cert.CertificateException;

import com.dstc.security.common.OID;
import com.dstc.security.asn1.Set;
import com.dstc.security.asn1.Sequence;
import com.dstc.security.asn1.Explicit;
import com.dstc.security.asn1.Oid;
import com.dstc.security.asn1.Asn1;
import com.dstc.security.asn1.Asn1Exception;

/**
 * <pre>
 *     SignedData ::= SEQUENCE {
 *        version CMSVersion,
 *        digestAlgorithms DigestAlgorithmIdentifiers,
 *        encapContentInfo EncapsulatedContentInfo,
 *        certificates [0] IMPLICIT CertificateSet OPTIONAL,
 *        crls [1] IMPLICIT CertificateRevocationLists OPTIONAL,
 *        signerInfos SignerInfos }
 *
 *     DigestAlgorithmIdentifiers ::= SET OF DigestAlgorithmIdentifier
 *
 *     SignerInfos ::= SET OF SignerInfo
 * </pre>
 */
public class DegeneratePKCS7
{
  private Asn1 asn1 = null;
  private Vector certs;
  private Vector crls;

  public DegeneratePKCS7(Vector certs, Vector crls) 
    throws Asn1Exception, CertificateException,
           CRLException
  {
    this.certs = certs;
    this.crls = crls;

    encode();
  }

  public DegeneratePKCS7(InputStream in) 
    throws IOException, Asn1Exception, CertificateException,
           CRLException
  {
    this(in, null);
  }

  public DegeneratePKCS7(InputStream in, String provider) 
    throws IOException, Asn1Exception, CertificateException,
           CRLException
  {
    CertificateFactory fact;

    try
    {
      if (provider == null)
      {
        // XX - why the explicit DSTC_X509?
        fact = CertificateFactory.getInstance("X.509", "DSTC_X509");
      }
      else
      {
        fact = CertificateFactory.getInstance("X.509", provider);
      }
    }
    catch (Exception e)
    {
      throw new RuntimeException(e.getMessage());
    }

    this.asn1 = Asn1.getAsn1(in);

    Iterator it = this.asn1.components();
    it.next();

    Asn1 comp2 = (Asn1) ((Asn1) it.next()).components().next();
    Iterator it4 = comp2.components();
    it4.next();
    it4.next();
    it4.next();
    Asn1 comp = (Asn1) it4.next();

    ByteArrayInputStream bais = null;
    if (comp.getTagNumber() == 0)
    {
      this.certs = new Vector();
      Iterator it2 = comp.components();

      while (it2.hasNext())
      {
        Asn1 next = (Asn1)it2.next();
        if (next == null)
          break;
  
        bais = new ByteArrayInputStream(next.getEncoded());
        X509Certificate cert 
          = (X509Certificate)fact.generateCertificate(bais);
        certs.add(cert);
      }
      comp = (Asn1) it4.next();
    }
  
    if (comp.getTagNumber() == 1)
    {
      this.crls = new Vector();
      Iterator it2 = comp.components();

      while (it2.hasNext())
      {
        Asn1 next = (Asn1)it2.next();
        if (next == null)
          break;
  
        bais = new ByteArrayInputStream(next.getEncoded());
        X509CRL crl = (X509CRL)fact.generateCRL(bais);
        crls.add(crl);
      }
      comp = (Asn1)it4.next();
    }
  }

  private void encode()
    throws Asn1Exception, CertificateException,
           CRLException
  {
    Asn1 sd = new Sequence();
    sd.add(new com.dstc.security.asn1.Integer(1));
    sd.add(new Set());

    Asn1 eci = new Sequence();
    eci.add(new Oid(OID.id_data));
    sd.add(eci);
    
    if (this.certs != null)
    {
      Asn1 certSet = new Set();
      for (Iterator it = certs.iterator(); it.hasNext(); )
      {
        certSet.add(
          Asn1.getAsn1(((X509Certificate)it.next()).getEncoded()));
      }
      certSet.setTagClass(Asn1.TAG_CLASS_CONTEXT);
      certSet.setTagNumber(0);
      sd.add(certSet);
    }

    if (this.crls != null)
    {
      Asn1 crlSet = new Set();
      for (Iterator it = crls.iterator(); it.hasNext(); )
      {
        crlSet.add(
          Asn1.getAsn1(((X509CRL)it.next()).getEncoded()));
      }
      crlSet.setTagClass(Asn1.TAG_CLASS_CONTEXT);
      crlSet.setTagNumber(1);
      sd.add(crlSet);
    }

    sd.add(new Set());
  
    this.asn1 = new Sequence();
    this.asn1.add(new Oid(OID.id_signedData));
    Explicit exp = new Explicit(Asn1.TAG_CLASS_CONTEXT, 0);
    exp.add(sd);
    this.asn1.add(exp);
  }

  public byte[] getEncoded() throws Asn1Exception
  {
    return this.asn1.getEncoded();
  }

  public Vector getCertificates() 
  {
    return this.certs;
  }

  public Vector getCRLs() 
  {
    return crls;
  }
}
