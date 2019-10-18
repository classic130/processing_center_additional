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

package com.dstc.security.x509.extns;

import java.io.*;
import java.util.Vector;
import java.util.Iterator;
import java.math.BigInteger;

import com.dstc.security.asn1.Asn1;
import com.dstc.security.asn1.Asn1Exception;
import com.dstc.security.asn1.Sequence;
import com.dstc.security.asn1.OctetString;
import com.dstc.security.asn1.Oid;
import com.dstc.security.common.OID;
import com.dstc.security.x509.ExtensionValue;
import com.dstc.security.x509.GeneralNames;

/**
 * Class representing the ASN.1 structure AuthorityKeyIdentifier.
 *
 * <pre>
 *  AuthorityKeyIdentifier ::= SEQUENCE {
 *        keyIdentifier             [0] KeyIdentifier            OPTIONAL,
 *        authorityCertIssuer       [1] GeneralNames             OPTIONAL,
 *        authorityCertSerialNumber [2] CertificateSerialNumber  OPTIONAL }
 *      -- authorityCertIssuer and authorityCertSerialNumber shall both
 *      -- be present or both be absent
 *  
 *  KeyIdentifier ::= OCTET STRING
 * </pre>  
 * @author Ming Yung
 */
public class AuthorityKeyIdentifier implements ExtensionValue
{
  private Asn1 asn1;
  private byte[] keyId;
  private GeneralNames issuer;
  private BigInteger serialNumber;

  /**
   * Constructs an AuthorityKeyIdentifier extension from a key identifier
   * (Non-critical).
   */
    public AuthorityKeyIdentifier(boolean dummy, byte[] keyId)
    throws Asn1Exception, IOException
  {
    this.asn1 = new Sequence();

    this.keyId = keyId;

    OctetString oct = new OctetString(keyId);
    oct.setTagClass(Asn1.TAG_CLASS_CONTEXT);
    oct.setTagNumber(0);
    this.asn1.add(oct);
  }

  /**
   * Constructs an AuthorityKeyIdentifier extension from a cert issuer
   * and serial number (Non-critical).
   */
    public AuthorityKeyIdentifier(GeneralNames issuer, BigInteger serial)
    throws Asn1Exception, IOException
  {
    this.asn1 = new Sequence();

    this.issuer = issuer;
    this.serialNumber = serial;

    Asn1 orig = issuer.getAsn1();
    orig.setTagClass(Asn1.TAG_CLASS_CONTEXT);
    orig.setTagNumber(1);
    this.asn1.add(orig);

    com.dstc.security.asn1.Integer intgr= 
      new com.dstc.security.asn1.Integer(serial);
    intgr.setTagClass(Asn1.TAG_CLASS_CONTEXT);
    intgr.setTagNumber(2);

    this.asn1.add(intgr);
  }

  /**
   * Constructs an AuthorityKeyIdentifier extension from a DER encoding
   */
  public AuthorityKeyIdentifier(Asn1 asn1) 
    throws Asn1Exception, IOException
  {
    this.asn1 = asn1;
 
    Iterator it = asn1.components();

    Asn1 comp = null;
    if (it.hasNext())
      comp = (Asn1)it.next();
      
    if (comp.getTagNumber() == 0)
    {
      this.keyId = comp.getValue();
    }
    else if (comp.getTagNumber() == 1)
    {
      this.issuer = new GeneralNames(comp);
      this.serialNumber 
        = new BigInteger( ((Asn1)it.next()).getValue() );
    }
  }

  public byte[] getEncoded() throws Asn1Exception
  {
    return this.asn1.getEncoded();
  }

  public String toString()
  {
    StringBuffer sb = new StringBuffer();

    sb.append("AuthorityKeyIdentifier extension:\n");
    if (this.issuer != null) {
        sb.append("    Issuer: " + this.issuer.getNames().toString() +"\n");
        sb.append("    Serial Number: " + this.serialNumber.toString() + "\n");
    }
    if (this.keyId != null) {
        sb.append("    " + 
               com.dstc.security.x509.Extension.printHex(this.keyId));
    }

    return sb.toString();
  }
}
