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
import java.security.PublicKey;
import java.math.BigInteger;
import java.util.Vector;
import java.util.Iterator;

import com.dstc.security.asn1.Asn1;
import com.dstc.security.asn1.Asn1Exception;
import com.dstc.security.asn1.Sequence;
import com.dstc.security.common.OID;
import com.dstc.security.common.AlgorithmId;
import com.dstc.security.common.SubjectPublicKeyInfo;

/**
 * <p>Implements a public key for use with the RSA-based signature algorithms.
 * 
 * Implements the ASN.1 structure
 * <pre>
 *     RSAPublicKey ::= SEQUENCE { 
 *       modulus        INTEGER, 
 *       publicExponent INTEGER } 
 * </pre>
 *
 * @see java.security.PublicKey
 * @see java.security.Signature
 * @see com.dstc.security.provider.RSAPrivateKey
 *
 * @version 0.98, 98/07/01
 * @author Ming Yung
 */
public class RSAPublicKey
  implements PublicKey, java.security.interfaces.RSAPublicKey
{
  private Asn1 asn1 = null;
  private BigInteger modulus, exponent;

  private void decode(Asn1 asn1) throws IOException
  {
    this.asn1 = asn1;
    Iterator it = asn1.components();

    this.modulus 
      = ((com.dstc.security.asn1.Integer)it.next()).getBigInteger();
    this.exponent 
      = ((com.dstc.security.asn1.Integer)it.next()).getBigInteger();
  }

  //Constructs a key from a modulus and exponent
  protected RSAPublicKey(BigInteger modulus, BigInteger exponent) 
  {
    this.asn1 = new Sequence();

    this.modulus = modulus;
    this.exponent = exponent;
    this.asn1.add(new com.dstc.security.asn1.Integer(modulus));
    this.asn1.add(new com.dstc.security.asn1.Integer(exponent));
  }

  /**
   * Returns the algorithm "RSA"
   */
  public String getAlgorithm () 
  {
    return "RSA";
  }

  /**
   * Returns the format "X.509"
   */
  public String getFormat () 
  {
    return "X.509";
  }

  /**
   * Returns the modulus for this key
   */
  public BigInteger getModulus () 
  {
    return modulus;
  }

  /**
   * Returns the exponent for this key
   */
  public BigInteger getPublicExponent () 
  {
    return exponent;
  }

  /**
   * Returns the DER encoding of SubjectPublickeyInfo for this key
   */
  public byte[] getEncoded () 
  {
    try
    {
      return (new SubjectPublicKeyInfo(new AlgorithmId(OID.rsaEncryption, 
       null), this.asn1.getEncoded())).getAsn1().getEncoded();
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
    for (int k=0; k<2; k++) {
      if (k==0) {
        sb.append("Modulus: \n" + "            " );
        b = this.getModulus().toByteArray();
      }
      else {
        sb.append("\nPublic Exponent: \n" + "            " );
        b = this.getPublicExponent().toByteArray();
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

  protected RSAPublicKey(byte encoded[]) 
    throws Asn1Exception, IOException
  {
    this.decode(Asn1.getAsn1(encoded));
  }

  private static final boolean DUMMY = Licensed.VALID;
}
