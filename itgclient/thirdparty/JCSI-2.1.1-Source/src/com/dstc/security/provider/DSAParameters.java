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

package com.dstc.security.provider;

import java.io.IOException;
import java.util.Iterator;
import java.math.BigInteger;
import java.security.AlgorithmParametersSpi;
import java.security.spec.AlgorithmParameterSpec;
import java.security.spec.DSAParameterSpec;
import java.security.spec.InvalidParameterSpecException;

import com.dstc.security.asn1.Sequence;
import com.dstc.security.asn1.Asn1;
import com.dstc.security.asn1.Asn1Exception;

/**
 * <p>Implements algorithm parameters for the DSA signature
 * algorithm following the DSS standard.
 *
 * <p>Inner class representing the ASN.1 structure DSAParameters.
 *
 * <pre>
 *    DSAParameters ::= SEQUENCE {
 *       p INTEGER,
 *       q INTEGER,
 *       g INTEGER
 *    }
 * </pre>
 * @see java.security.AlgorithmParameters
 * @see com.dstc.security.provider.DSA
 *
 * @version 0.98, 98/07/01
 * @author Ming Yung
 */
public final class DSAParameters extends AlgorithmParametersSpi
{
  private static final String ASN1 = "ASN.1";
  private Asn1 asn1 = null;
  private BigInteger g, p, q;

  /**
   * Constructs a DSAParams given parameters p, q, g
   */
  private void encode()
  {
    this.asn1 = new Sequence();

    this.asn1.add(new com.dstc.security.asn1.Integer(p));
    this.asn1.add(new com.dstc.security.asn1.Integer(q));
    this.asn1.add(new com.dstc.security.asn1.Integer(g));
  }

  /**
   * Constructs a DSAParams from a DER encoding
   */
  private void decode(Asn1 asn1) throws IOException
  {
    this.asn1 = asn1;
    Iterator it = asn1.components();

    this.p = ((com.dstc.security.asn1.Integer)it.next()).getBigInteger();
    this.q = ((com.dstc.security.asn1.Integer)it.next()).getBigInteger();
    this.g = ((com.dstc.security.asn1.Integer)it.next()).getBigInteger();
  }

  protected void engineInit(AlgorithmParameterSpec paramSpec) 
    throws InvalidParameterSpecException
  {
    if (!(paramSpec instanceof DSAParameterSpec))
      throw new InvalidParameterSpecException("Not a DSA param spec");

    this.p = ((DSAParameterSpec)paramSpec).getP();
    this.q = ((DSAParameterSpec)paramSpec).getQ();
    this.g = ((DSAParameterSpec)paramSpec).getG();
    this.encode();
  }

  protected void engineInit(byte[] params) throws IOException
  {
    try
    {
      this.decode(Asn1.getAsn1(params));
    }
    catch (Asn1Exception e)
    {
      throw new IOException(e.getMessage());
    }
  }

  protected void engineInit(byte[] params, String format) throws IOException
  {
    if (format != null && !format.equals(ASN1))
      throw new RuntimeException("Unsupported format " + format);

    engineInit(params);
  }

  protected AlgorithmParameterSpec engineGetParameterSpec(Class paramSpec) 
    throws InvalidParameterSpecException
  {
    if (!paramSpec.equals(DSAParameterSpec.class))
      throw new InvalidParameterSpecException("Bad parameter specification " +
        paramSpec.getName());

    return new DSAParameterSpec(this.p, this.q, this.g);
  }

  protected byte[] engineGetEncoded() 
    throws IOException
  {
    try
    {
      return this.asn1.getEncoded();
    }
    catch (Asn1Exception e)
    {
      throw new IOException(e.getMessage());
    }
  }

  protected byte[] engineGetEncoded(String format) throws IOException
  {
    if (format == null)
      return engineGetEncoded();

    if (format.equals(ASN1))
      return engineGetEncoded();

    throw new RuntimeException("Unrecognized format " +format);
  }

  protected String engineToString()
  {
    StringBuffer sb = new StringBuffer("DSA Parameters: \n");
    sb.append("  p: ").append(p.toString(16)).append("\n");
    sb.append("  q: ").append(q.toString(16)).append("\n");
    sb.append("  g: ").append(g.toString(16));
    return sb.toString();
  }

  private static final boolean DUMMY = Licensed.VALID;
}
