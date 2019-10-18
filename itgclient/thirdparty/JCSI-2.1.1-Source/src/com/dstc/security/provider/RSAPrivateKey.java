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
import java.security.PrivateKey;
import java.security.AlgorithmParameters;

import javax.crypto.Cipher;
import javax.crypto.spec.PBEParameterSpec;

import com.dstc.security.asn1.Asn1;
import com.dstc.security.asn1.Asn1Exception;
import com.dstc.security.asn1.Sequence;
import com.dstc.security.common.OID;
import com.dstc.security.common.AlgorithmId;
import com.dstc.security.common.PrivateKeyInfo;

/**
 * <p>Implements a private key for use with the RSA-based signature algorithms.
 * 
 * <p>Implements the ASN.1 structure RSAPrivateKey
 * <pre>
 *       RSAPrivateKey ::= SEQUENCE {
 *         version Version,
 *         modulus INTEGER, -- n
 *         publicExponent INTEGER, -- e
 *         privateExponent INTEGER, -- d
 *         prime1 INTEGER, -- p
 *         prime2 INTEGER, -- q
 *         exponent1 INTEGER, -- d mod (p-1)
 *         exponent2 INTEGER, -- d mod (q-1)
 *         coefficient INTEGER -- (inverse of q) mod p }
 * </pre>
 *
 * @see java.security.PublicKey
 * @see com.dstc.security.provider.RSAwithAnyMD
 * @see com.dstc.security.provider.RSAPublicKey
 *
 * @version 0.98, 98/07/01
 * @author Ming Yung
 */
public class RSAPrivateKey
  implements PrivateKey, java.security.interfaces.RSAPrivateKey
{
  private Asn1 asn1 = null;
  private BigInteger modulus, publicExponent, privateExponent, p, q;
  private static BigInteger one = BigInteger.valueOf(1);

  //Constructs a key from key data
  protected RSAPrivateKey(BigInteger modulus, BigInteger privateExponent) 
  {
    this.modulus = modulus;
    this.privateExponent = privateExponent;
  }

  //Constructs a key from key data
  protected RSAPrivateKey(BigInteger modulus, BigInteger publicExponent,
                        BigInteger privateExponent, BigInteger p,
                        BigInteger q) 
  {
    this.asn1 = new Sequence();

    this.asn1.add(new com.dstc.security.asn1.Integer(BigInteger.valueOf(0)));

    this.modulus = modulus;
    this.asn1.add(new com.dstc.security.asn1.Integer(modulus));

    this.publicExponent = publicExponent;
    this.asn1.add(new com.dstc.security.asn1.Integer(publicExponent));

    this.privateExponent = privateExponent;
    this.asn1.add(new com.dstc.security.asn1.Integer(privateExponent));

    this.p = p;
    this.asn1.add(new com.dstc.security.asn1.Integer(p));

    this.q = q;
    this.asn1.add(new com.dstc.security.asn1.Integer(q));

    this.asn1.add(new com.dstc.security.asn1.Integer(privateExponent.mod
                                          (p.subtract(one))));

    this.asn1.add(new com.dstc.security.asn1.Integer(privateExponent.mod
                                          (q.subtract(one))));

    this.asn1.add(new com.dstc.security.asn1.Integer(q.modInverse(p)));
  }

  /**
   * Returns the algorithm "RSA"
   */
  public String getAlgorithm() 
  {
    return "RSA";
  }

  /**
   * Returns the format "PKCS#8"
   */
  public String getFormat() 
  {
    return "PKCS#8";
  }

  /**
   * Returns the modulus for this key
   */
  public BigInteger getModulus() 
  {
    return modulus;
  }

  /**
   * Returns the private exponent for this key
   */
  public BigInteger getPrivateExponent() 
  {
    return privateExponent;
  }

  /**
   * Returns a PKCS8 encoding for this key
   */
  public byte[] getEncoded() 
  {
    try
    {
      //Get Encoded private key
      byte priv[] = (new PrivateKeyInfo(new AlgorithmId(OID.rsaEncryption,
        null), this.asn1.getEncoded())).getAsn1().getEncoded();

      return priv;
    }
    catch (Exception e)
    {
      throw new RuntimeException(e.getMessage());
    }
  }

  protected RSAPrivateKey(byte encoded[]) 
    throws Asn1Exception, IOException
  {
    decode(Asn1.getAsn1(encoded));
  }

  public boolean equals(Object key) {
    if (this == key) {
        return true;
    }
    if (key instanceof java.security.Key) {
      return java.util.Arrays.equals(this.getEncoded(),
              ((java.security.Key)key).getEncoded());
    }
    return false;
  }

  public String toString()
  {
    byte[] b = null;
    StringBuffer sb = new StringBuffer();
    for (int k=0; k<2; k++) {
      if (k==0) {
        sb.append("Modulus: \n" + "            " );
        b = this.getModulus().toByteArray();
      }
      else {
        sb.append("\nPrivate Exponent: \n" + "            " );
        b = this.getPrivateExponent().toByteArray();
      }

      for (int i=0; i<b.length; i++)
      {
        if ((i>0) && (i % 20 == 0)) {
            sb.append("\n            ");
        }
        if (b[i] <16 && b[i] >=0) {
          sb.append("0"+java.lang.Integer.toHexString(
                            b[i] & 0xff) + " ");
        }
        else {
          sb.append(java.lang.Integer.toHexString(b[i] & 0xff) + " ");
        }
      }
    }
    return sb.toString();
  }


  private void decode(Asn1 asn1) throws IOException
  {
    this.asn1 = asn1;
    Iterator it = asn1.components();

    this.modulus = ((com.dstc.security.asn1.Integer)it.next()).getBigInteger();
    this.publicExponent 
      = ((com.dstc.security.asn1.Integer)it.next()).getBigInteger();
    this.privateExponent 
      = ((com.dstc.security.asn1.Integer)it.next()).getBigInteger();
    this.p = ((com.dstc.security.asn1.Integer)it.next()).getBigInteger();
    this.q = ((com.dstc.security.asn1.Integer)it.next()).getBigInteger();
  }

  private static final boolean DUMMY = Licensed.VALID;
}
