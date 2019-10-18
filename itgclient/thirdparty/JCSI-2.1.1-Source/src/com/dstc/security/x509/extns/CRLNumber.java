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
import java.math.BigInteger;

import com.dstc.security.asn1.Asn1;
import com.dstc.security.asn1.Asn1Exception;
import com.dstc.security.asn1.Oid;
import com.dstc.security.asn1.Integer;
import com.dstc.security.common.OID;
import com.dstc.security.x509.ExtensionValue;

/**
 * Class representing the ASN.1 structure structure SubjectKeyIdentifier.
 *
 * <pre>
 *  cRLNumber  ::= INTEGER (0..MAX)
 *
 * </pre>
 * @author Ming Yung
 */
public class CRLNumber implements ExtensionValue
{
  private BigInteger num;
  private Asn1 asn1;

  /**
   * Constructs a CRLNumber extension (non-critical).
   */
  public CRLNumber(BigInteger i)
  {
    this.num = i;
    this.asn1 = new com.dstc.security.asn1.Integer(i);
  }

  /**
   * Constructs a CRLNumber extension from a DER encoding
   */
  public CRLNumber(Asn1 asn1) 
  {
    this.asn1 = asn1;

    this.num = ((com.dstc.security.asn1.Integer)asn1).getBigInteger();
  }

  public byte[] getEncoded() throws Asn1Exception
  {
    return this.asn1.getEncoded();
  }

  /**
   * Returns the integer for this CRLNumber extension
   */
  public BigInteger getBigInteger()
  {
    return this.num;
  }

  public String toString()
  {
    StringBuffer sb = new StringBuffer();

    sb.append("CRLNumber extension:\n");
    sb.append("  " + this.num.toString() + "\n");
    return sb.toString();
  }
}
