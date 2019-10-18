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
import java.util.Set;
import java.util.Iterator;
import java.math.BigInteger;
import java.util.Date;
import java.security.cert.CRLException;
import com.dstc.security.asn1.Asn1;
import com.dstc.security.asn1.Asn1Exception;
import com.dstc.security.asn1.Sequence;
import com.dstc.security.asn1.UTCTime;

/**
 * <p>Implemention of a revoked certificate in a CRL (Certificate
 * Revocation List).
 *
 * The ASN.1 definition for <em>revokedCertificates</em> is:
 * <pre>
 * revokedCertificates    SEQUENCE OF SEQUENCE  {
 *     userCertificate    CertificateSerialNumber,
 *     revocationDate     ChoiceOfTime,
 *     crlEntryExtensions Extensions OPTIONAL
 *                        -- if present, must be v2
 * }  OPTIONAL
 *<p>
 * CertificateSerialNumber  ::=  INTEGER
 *<p>
 * Extensions  ::=  SEQUENCE SIZE (1..MAX) OF Extension
 *<p>
 * Extension  ::=  SEQUENCE  {
 *     extnId        OBJECT IDENTIFIER,
 *     critical      BOOLEAN DEFAULT FALSE,
 *     extnValue     OCTET STRING
 *                   -- contains a Asn1 encoding of a value
 *                   -- of the type registered for use with
 *                   -- the extnId object identifier value
 * }
 * </pre>
 *
 */
public class X509CRLEntry extends java.security.cert.X509CRLEntry 
{
  protected Asn1 asn1 = null;
  protected BigInteger userCertificate;
  protected UTCTime revocationDate;
  protected Extensions crlExtns = null;

  public X509CRLEntry() 
  {}

  /**
   * Constructs an X509CRLEntryImpl from a DER encoding
   */
  public X509CRLEntry(Asn1 asn1) throws IOException, Asn1Exception
  {
    this.asn1 = asn1;
  
    Iterator it = asn1.components();
    Asn1 comp = (Asn1)it.next();

    this.userCertificate 
      = ((com.dstc.security.asn1.Integer)comp).getBigInteger();

    this.revocationDate 
      = (UTCTime)it.next();

    if (!it.hasNext()) return;
    this.crlExtns = new Extensions((Asn1)it.next());
  }

  public Asn1 getAsn1()
  {
    return this.asn1;
  }

  /**
   * Returns the ASN.1 DER-encoded form of this CRL Entry,
   * that is the inner SEQUENCE.
   *
   * @exception CRLException if an encoding error occurs.
   */
  public byte[] getEncoded() throws CRLException
  {
    try
    {
      return this.asn1.getEncoded();
    }
    catch (Asn1Exception e)
    {
      throw new CRLException(e.toString());
    }
  }

  /**
   * Gets the serial number from this X509CRLEntry,
   * the <em>userCertificate</em>.
   *
   * @return the serial number.
   */
  public BigInteger getSerialNumber()
  {
    return this.userCertificate;
  }

  /**
   * Gets the revocation date from this X509CRLEntry,
   * the <em>revocationDate</em>.
   *
   * @return the revocation date.
   */
  public Date getRevocationDate()
  {
    return this.revocationDate.getDate();
  }

  /**
   * Returns true if this CRL entry has extensions.
   *
   * @return true if this entry has extensions, false otherwise.
   */
  public boolean hasExtensions()
  {
    return (this.crlExtns == null ? false : true);
  }

  /**
   * Returns a string representation of this CRL entry.
   *
   * @return a string representation of this CRL entry.
   */
  public String toString()
  {
    StringBuffer sb = new StringBuffer();
    sb.append("  Serial number  : ").append(getSerialNumber());
    sb.append(",  Revocation time: ").append(getRevocationDate());
    sb.append("\n");
    return sb.toString();
  }

  public Set getCriticalExtensionOIDs()
  {
    return this.crlExtns.getCriticalOIDs();
  }

  public Set getNonCriticalExtensionOIDs()
  {
    return this.crlExtns.getNonCriticalOIDs();
  }

  public byte[] getExtensionValue(String oid)
  {
    return this.crlExtns.getValue(oid);
  }

  ///XXX
  public boolean hasUnsupportedCriticalExtension()
  {
    return false;
  }
}
