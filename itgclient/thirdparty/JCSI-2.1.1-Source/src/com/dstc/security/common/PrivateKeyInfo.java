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

package com.dstc.security.common;

import java.io.IOException;
import java.io.InputStream;
import java.util.Iterator;

import com.dstc.security.asn1.Asn1;
import com.dstc.security.asn1.Asn1Exception;
import com.dstc.security.asn1.Sequence;
import com.dstc.security.asn1.OctetString;
import com.dstc.security.common.AlgorithmId;

/**
 * <p>A class representing the PKCS#8 ASN.1 structure PrivateKeyInfo.
 *
 * <pre>
 * PrivateKeyInfo ::= SEQUENCE {
 *                        version             Version,
 *                        privateKeyAlgorithm PrivateKeyAlgorithmIdentifier,
 *                        privateKey          PrivateKey,
 *                        attributes [0] IMPLICIT Attributes OPTIONAL }
 *
 * Version ::= INTEGER -- equals to 0
 *
 * PrivateKeyAlgorithmIdentifier ::= AlgorithmIdentifier
 *
 * PrivateKey ::= OCTET STRING
 *
 * Attributes ::= SET OF Attribute
 * </pre>
 *
 * @see com.dstc.security.common.AlgorithmId
 *
 * @version 0.98, 98/07/01
 * @author Ming Yung
 */
public class PrivateKeyInfo
{
  private Asn1 asn1 = null;
  private int version = 0;
  private byte encodedKey[];
  private AlgorithmId privAlgo;

  /**
   * Constructs a PrivateKeyInfo from an AlgorithmId and encoded key
   */
  public PrivateKeyInfo(AlgorithmId algo, byte encodedKey[])
  {
    this.asn1 = new Sequence();

    this.asn1.add(new com.dstc.security.asn1.Integer(version));

    this.privAlgo = algo;
    this.asn1.add(algo.getAsn1());

    this.encodedKey = encodedKey;
    this.asn1.add(new OctetString(encodedKey));
  }

  /**
   * Constructs a PrivateKeyInfo from a DER encoding
   */
  public PrivateKeyInfo(byte[] encoded) throws Asn1Exception
  {
    this(Asn1.getAsn1(encoded));
  }

  /**
   * Constructs a PrivateKeyInfo from a DER encoding
   */
  public PrivateKeyInfo(InputStream is) 
    throws Asn1Exception, IOException
  {
    this(Asn1.getAsn1(is));
  }

  /**
   * Constructs a PrivateKeyInfo from a DER encoding
   */
  public PrivateKeyInfo(Asn1 asn1) throws Asn1Exception
  {
    if (asn1 == null)
      throw new Asn1Exception("null asn1");

    this.asn1 = asn1;
    Iterator it = asn1.components();

    this.version = ((com.dstc.security.asn1.Integer)it.next()).getInt();
    this.privAlgo = new AlgorithmId((Asn1)it.next());
    this.encodedKey = ((OctetString)it.next()).getBytes();
  }

  public Asn1 getAsn1()
  {
    return this.asn1;
  }

  /**
   * Returns the AlgorithmId
   */
  public AlgorithmId getAlgorithmId()
  {
    return this.privAlgo;
  }

  /**
   * Returns the encoded key
   */
  public byte[] getEncodedKey()
  {
    return this.encodedKey;
  }
}
