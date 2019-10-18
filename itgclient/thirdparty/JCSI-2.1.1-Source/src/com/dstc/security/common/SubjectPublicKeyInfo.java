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

import java.io.InputStream;
import java.io.IOException;
import java.util.Iterator;

import com.dstc.security.asn1.Asn1;
import com.dstc.security.asn1.Asn1Exception;
import com.dstc.security.asn1.Sequence;
import com.dstc.security.asn1.BitString;
import com.dstc.security.common.AlgorithmId;

/**
 * <p>A class representing the x.509 ASN.1 structure SubjectPublicKeyInfo.
 *
 * <pre>
 *    SubjectPublicKeyInfo  ::= SEQUENCE  {
 *       algorithm            AlgorithmIdentifier,
 *       subjectPublicKey     BIT STRING  }
 *
 * </pre>
 * @see com.dstc.security.common.AlgorithmId
 *
 * @version 0.98, 98/07/01
 * @author Ming Yung
 */
public class SubjectPublicKeyInfo
{
  private Asn1 asn1 = null;

  private AlgorithmId algoId;
  private byte[] encodedKey;

  /**
   * Constructs a SubjectPublicKeyInfo from an AlgorithmId and Public Key
   */
  public SubjectPublicKeyInfo(AlgorithmId algoId, byte encodedKey[]) 
  {
    this.asn1 = new Sequence();

    this.algoId = algoId;
    this.asn1.add(algoId.getAsn1());

    this.encodedKey = encodedKey;
    this.asn1.add(new BitString(encodedKey));
  }

  /**
   * Constructs a SubjectPublicKeyInfo from a DER encoding
   */
  public SubjectPublicKeyInfo(InputStream is) 
    throws Asn1Exception, IOException
  {
    this(Asn1.getAsn1(is));
  }

  /**
   * Constructs a SubjectPublicKeyInfo from a DER encoding
   */
  public SubjectPublicKeyInfo(byte[] encoded) throws Asn1Exception
  {
    this(Asn1.getAsn1(encoded));
  }

  public SubjectPublicKeyInfo(Asn1 asn1) throws Asn1Exception
  {
    if (asn1 == null)
      throw new Asn1Exception("null asn1");

    this.asn1 = asn1;

    Iterator it = asn1.components();

    this.algoId = new AlgorithmId((Asn1)it.next());
    this.encodedKey = ((BitString)it.next()).getBytes();
  }

  public Asn1 getAsn1()
  {
    return this.asn1;
  }

  /**
   * Returns the encoded Public key
   */
  public byte[] getEncodedKey()
  {
    return this.encodedKey;
  }

  /**
   * Returns the AlgorithmId
   */
  public AlgorithmId getAlgorithmId()
  {
    return this.algoId;
  }

 /**
  * Returns the DER encoding for this <code>SubjectPublicKeyInfo</code>
  *
  */
 
  public byte[] getEncoded()
  {
    try
    {
      return this.asn1.getEncoded();
    }
    catch (Asn1Exception e)
    {
      return null;
    }
  }

}
