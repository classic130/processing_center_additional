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
import java.security.spec.InvalidParameterSpecException;

import javax.crypto.spec.PBEParameterSpec;

import com.dstc.security.asn1.Integer;
import com.dstc.security.asn1.OctetString;
import com.dstc.security.asn1.Sequence;
import com.dstc.security.asn1.Asn1;
import com.dstc.security.asn1.Asn1Exception;

/**
 * <p>Implements java.security.AlgorithmParameters for the password-based
 * encryption algorithm in PKCS#5.
 *
 * <p>Implements the ASN.1 structure PBEParameter
 * <pre>
 *  PBEParameter ::= SEQUENCE {
 *    salt OCTET STRING SIZE(8),
 *    iterationCount INTEGER }
 * </pre>
 *
 * @see java.security.AlgorithmParameters
 * @see com.dstc.security.provider.PBECipher
 * @see javax.crypto.Cipher
 *
 * @version 0.98, 98/07/01
 * @author Ming Yung
 */
public class PBEParameters extends AlgorithmParametersSpi
{
  private static final String ASN1 = "ASN.1";
  private Asn1 asn1 = null;
  private byte[] salt;
  private int ic; 

  /**
   * Encodes to a PBEParameter
   */
  private void encode() 
  {
    this.asn1 = new Sequence();

    this.asn1.add(new OctetString(salt));
    this.asn1.add(new com.dstc.security.asn1.Integer(ic));
  }

  /** 
   * Constructs a PBEParams from a DER encoding
   */ 
  private void decode(Asn1 asn1) throws IOException
  {
    this.asn1 = asn1;
    Iterator it = asn1.components();

    this.salt = ((OctetString)it.next()).getBytes();
    this.ic 
      = ((com.dstc.security.asn1.Integer)it.next()).getBigInteger().intValue();
  }

  protected void engineInit(AlgorithmParameterSpec paramSpec) 
    throws InvalidParameterSpecException
  {
    if (!(paramSpec instanceof PBEParameterSpec))
      throw new InvalidParameterSpecException("Not a PBE param spec");

    this.salt = ((PBEParameterSpec)paramSpec).getSalt();
    this.ic = ((PBEParameterSpec)paramSpec).getIterationCount();
    this.encode();
  }

  protected void engineInit(byte[] params) throws IOException
  {
    try
    {
      decode(Asn1.getAsn1(params));
    }
    catch (Asn1Exception e)
    {
      throw new IOException(e.toString());
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
    PBEParameterSpec pbespec;

    if (!paramSpec.equals(PBEParameterSpec.class))
      throw new InvalidParameterSpecException("Bad parameter specification "
        + paramSpec.getName());

    return new PBEParameterSpec(this.salt, this.ic);
  }

  protected byte[] engineGetEncoded() throws IOException
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

    throw new RuntimeException("Unsupported format " + format);
  }

  protected String engineToString()
  {
    StringBuffer sb = new StringBuffer("PBE Parameters");
    return sb.toString();
  }

  private static final boolean DUMMY = Licensed.VALID;
}
