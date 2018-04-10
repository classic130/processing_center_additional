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
 * Implements the ASN.1 structure RSAPrivateKey
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
 * @see java.security.Signature
 * @see com.dstc.security.provider.RSAPublicKey
 *
 * @version 0.98, 98/07/01
 * @author Ming Yung
 */
public class RSAPrivateCrtKey
  implements java.security.interfaces.RSAPrivateCrtKey
{
  private Asn1 asn1 = null;
  private int version = 0;
  private BigInteger modulus, publicExponent, privateExponent, p, q;
  private BigInteger primeExponentP, primeExponentQ, crtCoefficient;
  private static BigInteger one = BigInteger.valueOf(1);

  /**
   * Decodes from a DER encoding of RSAPrivateKey
   */
  void decode(Asn1 asn1) throws IOException
  {
    this.asn1 = asn1;
    Iterator it = asn1.components();

    this.version 
      = ((com.dstc.security.asn1.Integer)it.next()).getInt();
    this.modulus 
      = ((com.dstc.security.asn1.Integer)it.next()).getBigInteger();
    this.publicExponent 
      = ((com.dstc.security.asn1.Integer)it.next()).getBigInteger();
    this.privateExponent 
      = ((com.dstc.security.asn1.Integer)it.next()).getBigInteger();
    this.p = ((com.dstc.security.asn1.Integer)it.next()).getBigInteger();
    this.q = ((com.dstc.security.asn1.Integer)it.next()).getBigInteger();
    this.primeExponentP 
      = ((com.dstc.security.asn1.Integer)it.next()).getBigInteger();
    this.primeExponentQ 
      = ((com.dstc.security.asn1.Integer)it.next()).getBigInteger();
    this.crtCoefficient 
      = ((com.dstc.security.asn1.Integer)it.next()).getBigInteger();
  }

  //Constructs a key from key data
  protected RSAPrivateCrtKey(BigInteger modulus, BigInteger privateExponent) 
  {
    this.modulus = modulus;
    this.privateExponent = privateExponent;
  }

  //Constructs a key from key data
  protected RSAPrivateCrtKey(BigInteger modulus, BigInteger publicExponent,
                        BigInteger privateExponent, BigInteger p,
                        BigInteger q) 
  {
    this(modulus, publicExponent, privateExponent, p, q, 
         privateExponent.mod(p.subtract(one)),
         privateExponent.mod(q.subtract(one)),
         q.modInverse(p));
  }

  protected RSAPrivateCrtKey(BigInteger modulus, BigInteger publicExponent,
                        BigInteger privateExponent, BigInteger p,
                        BigInteger q, BigInteger primeP, BigInteger primeQ,
                        BigInteger crtCoeff) 
  {
    this.asn1 = new Sequence();

    this.asn1.add(
      new com.dstc.security.asn1.Integer(BigInteger.valueOf(version)));

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

    this.primeExponentP = primeP;
    this.asn1.add(new com.dstc.security.asn1.Integer(primeP));

    this.primeExponentQ = primeQ;
    this.asn1.add(new com.dstc.security.asn1.Integer(primeQ));

    this.crtCoefficient = crtCoeff;
    this.asn1.add(new com.dstc.security.asn1.Integer(crtCoeff));
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
   * Returns the public exponent for this key
   */
  public BigInteger getPublicExponent() 
  {
    return publicExponent;
  }

  /**
   * Returns the private exponent for this key
   */
  public BigInteger getPrivateExponent() 
  {
    return privateExponent;
  }

  /**
   * Returns the prime p for this key
   */
  public BigInteger getPrimeP()
  {
    return p;
  }

  /**
   * Returns the prime q for this key
   */
  public BigInteger getPrimeQ()
  {
    return q;
  }

  /**
   * Returns the exponent d mod (p-1) for this key
   */
  public BigInteger getPrimeExponentP()
  {
    return primeExponentP;
  }

  /**
   * Returns the exponent d mod (q-1) for this key
   */
  public BigInteger getPrimeExponentQ()
  {
    return primeExponentQ;
  }

  /**
   * Returns the crt coefficient for this key
   */
  public BigInteger getCrtCoefficient()
  {
    return crtCoefficient;
  }

  /**
   * Returns a PKCS8 encoding for this key
   */
  public byte[] getEncoded() 
  {
    try
    {
      byte priv[] = (new PrivateKeyInfo(new AlgorithmId(OID.rsaEncryption,
        null), this.asn1.getEncoded())).getAsn1().getEncoded();

      return priv;
    }
    catch (Exception e)
    {
      throw new RuntimeException(e.getMessage());
    }
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
    for (int k=0; k<7; k++) {
      switch(k) {
          case(0):
              sb.append("Modulus: \n" + "            " );
              b = this.getModulus().toByteArray();
              break;
          case(1):
              sb.append("\nPrivate Exponent: \n" + "            " );
              b = this.getPrivateExponent().toByteArray();
              break;
          case(2):
              sb.append("\nPrime P: \n" + "            " );
              b = this.getPrimeP().toByteArray();
              break;
          case(3):
              sb.append("\nPrime Q: \n" + "            " );
              b = this.getPrimeQ().toByteArray();
              break;
          case(4):
              sb.append("\nPrime Exponent P: \n" + "            " );
              b = this.getPrimeExponentP().toByteArray();
              break;
          case(5):
              sb.append("\nPrime Exponent Q: \n" + "            " );
              b = this.getPrimeExponentQ().toByteArray();
              break;
          case(6):
              sb.append("\nCrt Coefficient: \n" + "            " );
              b = this.getCrtCoefficient().toByteArray();
              break;
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


  public RSAPrivateCrtKey(byte[] encoded) 
    throws Asn1Exception, IOException
  {
    this.decode(Asn1.getAsn1(encoded));
  }

  private static final boolean DUMMY = Licensed.VALID;
}
