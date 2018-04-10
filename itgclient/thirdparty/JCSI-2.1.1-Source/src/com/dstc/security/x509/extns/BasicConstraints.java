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
import java.util.Iterator;

import com.dstc.security.asn1.Asn1;
import com.dstc.security.asn1.Asn1Exception;
import com.dstc.security.asn1.Sequence;
import com.dstc.security.asn1.Oid;
import com.dstc.security.asn1.Boolean;
import com.dstc.security.asn1.OctetString;
import com.dstc.security.asn1.BitString;
import com.dstc.security.common.OID;
import com.dstc.security.x509.ExtensionValue;

/**
 * <p>Class representing the ASN.1 structure BasicConstraints.
 *
 * <pre>
 *     BasicConstraints ::= SEQUENCE {
 *          cA                      BOOLEAN DEFAULT FALSE,
 *          pathLenConstraint       INTEGER (0..MAX) OPTIONAL }
 * </pre>
 *
 * @author Ming Yung
 */ 
public class BasicConstraints implements ExtensionValue
{
  private int len = -1;
  private boolean isCA;
  private Asn1 asn1;

  /**
   * Constructs a BasicConstraints extension from a DER encoding
   */
  public BasicConstraints(Asn1 asn1) 
    throws Asn1Exception, IOException
  {
    this.asn1 = asn1;

    if (!(asn1 instanceof Sequence))
      throw new Asn1Exception("Bad encoding for basic constraint");

    Iterator it = asn1.components();

    if (!it.hasNext()) 
      return;

    this.isCA = ((Boolean)it.next()).isTrue();

    if (!it.hasNext())
      return;

    this.len = ((com.dstc.security.asn1.Integer)it.next()).getInt();
  }

  /**
   * Constructs a BasicConstraints extension
   */
  public BasicConstraints(boolean isCA, int len)
  {
    this.asn1 = new Sequence();
 
    this.isCA = isCA;
    if (isCA)
    {
      this.asn1.add(new Boolean(true));
 
      this.len = len;
      if (len > -1)
        this.asn1.add(new com.dstc.security.asn1.Integer(len));
    }
  }
                                                                                
  public int getBasicConstraints()
  {
    return (this.isCA ? this.len : -1);
  }

  public byte[] getEncoded() throws Asn1Exception
  {
    return this.asn1.getEncoded();
  }

  public String toString()
  {
    StringBuffer sb = new StringBuffer();
    sb.append("BasicConstraints extension:\n");

    sb.append("  CA: ");
    if (isCA)
      sb.append(" true, ");
    else
      sb.append(" false, ");

    sb.append("path length constraint = ");
    if (len > 0)
      sb.append(len + "\n");
    else
      sb.append("unspecified\n");
    
    return sb.toString();
  }
}
