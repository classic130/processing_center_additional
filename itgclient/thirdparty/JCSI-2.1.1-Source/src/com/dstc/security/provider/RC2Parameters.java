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
import java.security.AlgorithmParametersSpi;
import java.security.spec.AlgorithmParameterSpec;
import java.security.spec.InvalidParameterSpecException;

import javax.crypto.spec.RC2ParameterSpec;

import com.dstc.security.asn1.Integer;
import com.dstc.security.asn1.OctetString;
import com.dstc.security.asn1.Sequence;
import com.dstc.security.asn1.Asn1;
import com.dstc.security.asn1.Asn1Exception;

/**
 * <p>Implements java.security.AlgorithmParameters for the RC2-CBC
 * encryption algorithm
 *
 * <p>An Inner class representing the ASN.1 structure RC2CBCParameter.
 * <pre>
 *    RC2CBCParameter ::= SEQUENCE {
 *        rc2ParameterVersion      INTEGER,
 *        iv                       OCTET STRING
 *    }
 * </pre>
 * 
 * parameterVersions of 160, 120, 58 corresponds to
 * effective key bits of 40, 64 and 128 respectively
 *
 * @see java.security.AlgorithmParameters
 * @see com.dstc.security.provider.RC2
 * @see javax.crypto.Cipher
 *
 * @version 0.98, 98/07/01
 * @author Ming Yung
 */
public final class RC2Parameters extends AlgorithmParametersSpi
{
  private static final String ASN1 = "ASN.1";
  private Asn1 asn1 = null;
  private int eKB; 
  private int parameterVersion;
  private byte[] iv;

  /**
   * Encoded to an RC2CBCParameter from the effective key bits and iv
   */
  private void encode()
  {
    this.asn1 = new Sequence();
    this.asn1.add(new com.dstc.security.asn1.Integer(parameterVersion));

    this.asn1.add(new OctetString(iv));
  }

  /**
   * Decodes from a DER encoding of RC2CBCParameter
   */
  private void decode(Asn1 asn1) throws IOException
  {
    this.asn1 = asn1;
    Iterator it = asn1.components();

    this.parameterVersion 
      = ((com.dstc.security.asn1.Integer)it.next()).getInt();

    if (parameterVersion == 160)
      this.eKB = 40;
    else if (parameterVersion == 120)
      this.eKB = 64;
    else if (parameterVersion == 58)
      this.eKB = 128;

    this.iv = ((OctetString)it.next()).getBytes();
  }

  protected void engineInit(AlgorithmParameterSpec paramSpec) 
    throws InvalidParameterSpecException
  {
    if (!(paramSpec instanceof RC2ParameterSpec))
      throw new InvalidParameterSpecException("Not an RC2 param spec");

    this.eKB = ((RC2ParameterSpec)paramSpec).getEffectiveKeyBits();
    if (eKB == 40)
      this.parameterVersion = 160;
    else if (eKB == 64)
      this.parameterVersion = 120;
    else if (eKB == 128)
      this.parameterVersion = 58;
    else
      throw new InvalidParameterSpecException("Bad parameter version");

    this.iv = ((RC2ParameterSpec)paramSpec).getIV();
    this.encode();
  }

  protected void engineInit(byte[] encoded) throws IOException
  {
    try
    {
      this.decode(Asn1.getAsn1(encoded));
    }
    catch (Asn1Exception e)
    {
      throw new IOException(e.getMessage());
    }
  }

  protected void engineInit(byte[] params, String format) throws IOException
  {
    if (format != null && !format.equals(ASN1))
      throw new RuntimeException("Format " + format + " unsupported");

    engineInit(params);
  }

  protected AlgorithmParameterSpec engineGetParameterSpec(Class paramSpec) 
    throws InvalidParameterSpecException
  {
    if (!paramSpec.equals(RC2ParameterSpec.class))
      throw new InvalidParameterSpecException("Bad parameter specification "
        + paramSpec.getName());

    return new RC2ParameterSpec(this.eKB, this.iv);
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

    throw new RuntimeException("Unrecognized format " + format);
  }

  protected String engineToString()
  {
    StringBuffer sb = new StringBuffer("RC2 Parameters");
    return sb.toString();
  }

  private static final boolean DUMMY = Licensed.VALID;
}
