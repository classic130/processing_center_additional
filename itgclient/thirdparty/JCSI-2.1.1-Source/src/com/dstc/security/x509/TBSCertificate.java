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

import java.io.IOException;
import java.util.Vector;
import java.util.Iterator;
import java.math.BigInteger;

import com.dstc.security.asn1.*;
import com.dstc.security.common.AlgorithmId;
import com.dstc.security.common.X500Name;
import com.dstc.security.common.SubjectPublicKeyInfo;

/**
 * <p>Implements the X.509 ASN.1 structure TBSCertificate.
 *
 * <pre>
 *  <p>TBSCertificate  ::=  SEQUENCE  {
 *       version         [0]  EXPLICIT Version DEFAULT v1,
 *       serialNumber         CertificateSerialNumber,
 *       signature            AlgorithmIdentifier,
 *       issuer               Name,
 *       validity             Validity,
 *       subject              Name,
 *       subjectPublicKeyInfo SubjectPublicKeyInfo,
 *       issuerUniqueID  [1]  UniqueIdentifier OPTIONAL,
 *                            -- If present, version must be v2 or v3
 *       subjectUniqueID [2]  UniqueIdentifier OPTIONAL,
 *                            -- If present, version must be v2 or v3
 *       extensions      [3]  EXPLICIT Extensions OPTIONAL
 *                            -- If present, version must be v3
 *       }
 *
 *  <p>Version  ::=  INTEGER  {  v1(0), v2(1), v3(2)  }
 *
 *  <p>CertificateSerialNumber  ::=  INTEGER
 *
 *  <p>UniqueIdentifier  ::=  BIT STRING
 *
 *  <p>Extensions  ::=  SEQUENCE SIZE (1..MAX) OF Extension
 *
 *  <p>Extension  ::=  SEQUENCE  {
 *       extnID      OBJECT IDENTIFIER,
 *       critical    BOOLEAN DEFAULT FALSE,
 *       extnValue   OCTET STRING  }
 * </pre>
 *
 * @version 0.98, 98/07/01
 * @author Ming Yung
 */
public class TBSCertificate
{
  protected Asn1 asn1 = null;

  protected int version = 0;
  protected BigInteger serialNumber;
  protected X500Name issuer;
  protected X500Name subject;
  protected Validity validity;
  protected AlgorithmId algo;
  protected SubjectPublicKeyInfo spki;
  protected byte[] issuerUniqueId;
  protected byte[] subjectUniqueId;
  public Extensions extns = null;
  
  /**
   * Constructs a TBSCertificate from a DER encoding
   */

  public TBSCertificate() 
  {}

  public TBSCertificate(Asn1 asn1) throws Asn1Exception, IOException
  {
    this.asn1 = asn1;

    if (!(asn1 instanceof Sequence))
    {
      throw new Asn1Exception("Bad certificate encoding");
    }    

    Iterator it = asn1.components();
    Asn1 comp = (Asn1)it.next();
  
    if (comp.getTagNumber() == 0)
    {
      this.version = 
        ((com.dstc.security.asn1.Integer)comp.components().next()).getInt();
      comp = (Asn1)it.next();
    }
  
    this.serialNumber = 
      ((com.dstc.security.asn1.Integer)comp).getBigInteger();
  
    this.algo = new AlgorithmId((Asn1)it.next()); 
    this.issuer = new X500Name((Asn1)it.next());
  
    this.validity = new Validity((Asn1)it.next());
  
    this.subject = new X500Name((Asn1)it.next());
  
    this.spki = new SubjectPublicKeyInfo((Asn1)it.next());

    // See if there is any more
    if (!it.hasNext()) return;

    comp = (Asn1)it.next();

    if (comp.getTagNumber() == 1)
    {
//    this.issuerUniqueId = ((BitString)comp.components().next()).getBytes();
      byte[] b2 = comp.getValue();
      this.issuerUniqueId = new byte[b2.length-1];
      System.arraycopy(b2,1,this.issuerUniqueId,0,b2.length - 1);
      if (!it.hasNext()) 
        return;
      else
        comp = (Asn1)it.next();
    }

    if (comp.getTagNumber() == 2)
    {
//    this.subjectUniqueId = ((BitString)comp.components().next()).getBytes();
      byte[] b2 = comp.getValue();
      this.subjectUniqueId = new byte[b2.length-1];
      System.arraycopy(b2,1,this.subjectUniqueId,0,b2.length - 1);
      if (!it.hasNext()) 
        return;
      else
        comp = (Asn1)it.next();
    }

    if (comp.getTagNumber() == 3)
    {
      this.extns = new Extensions((Asn1)comp.components().next());
    }
  }

  public Asn1 getAsn1()
  {
    return this.asn1;
  }

  /**
   * Returns the version for this TBSCertificate
   */
  public int getVersion()
  {
    return this.version;
  }

  /**
   * Returns the serial number for this TBSCertificate
   */
  public BigInteger getSerialNumber()
  {
    return this.serialNumber;
  }

  /**
   * Returns the Validity for this TBSCertificate
   */
  public Validity getValidity()
  {
    return this.validity;
  }

  /**
   * Returns the SubjectPublicKeyInfo for this TBSCertificate
   */
  public SubjectPublicKeyInfo getSubjectPubKeyInfo()
  {
    return this.spki;
  }

  /**
   * Returns the Subject for this TBSCertificate
   */
  public X500Name getSubject()
  {
    return this.subject;
  }

  /**
   * Returns the Isuuer for this TBSCertificate
   */
  public X500Name getIssuer()
  {
    return this.issuer;
  }

  /**
   * Returns the Extensions for this TBSCertificate
   */
  public Extensions getExtensions()
  {
    return this.extns;
  }

  public byte[] getIssuerUniqueId()
  {
    return this.issuerUniqueId;
  }

  public byte[] getSubjectUniqueId()
  {
    return this.subjectUniqueId;
  }
}
