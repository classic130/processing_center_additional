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
import java.security.AlgorithmParameters;

import javax.crypto.Cipher;
import javax.crypto.spec.PBEParameterSpec;
import javax.crypto.spec.DHParameterSpec;

import com.dstc.security.asn1.Asn1;
import com.dstc.security.asn1.Asn1Exception;
import com.dstc.security.common.OID;
import com.dstc.security.common.AlgorithmId;
import com.dstc.security.common.PrivateKeyInfo;

/**
 * <p>Implements a private key for use with the Diffie-Hellman key agreement
 * algorithm.
 * 
 * @see java.security.PublicKey
 * @see javax.crypto.KeyAgreement
 * @see com.dstc.security.provider.DHParameters
 * @see com.dstc.security.provider.DHPublicKey
 *
 * @version 0.98, 98/07/01
 * @author Ming Yung
 */
public class DHPrivateKey implements javax.crypto.interfaces.DHPrivateKey
{
  private Asn1 asn1 = null;
  private BigInteger x;
  private DHParameterSpec params;

  private void decode(Asn1 asn1) throws IOException
  {
    this.asn1 = asn1;

    this.x = ((com.dstc.security.asn1.Integer)asn1).getBigInteger();
  }

  private void encode()
  {
    this.asn1 = new com.dstc.security.asn1.Integer(this.x);
  }

  protected DHPrivateKey(BigInteger x, BigInteger p, BigInteger g)
  {
    this.x = x;
    this.params = new DHParameterSpec(p, g);
    this.encode();
  }

  public BigInteger getX()
  {
    return this.x;
  }

  public DHParameterSpec getParams()
  {
    return this.params;
  }

  public String getAlgorithm()
  {
    return "DH";
  }

  public String getFormat()
  {
    return "PKCS#8";
  }

  /**
   * Returns DER encoding of PrivateKeyInfo for this key
   */
  public byte[] getEncoded()
  {
    try
    {
      AlgorithmParameters algParams =
        AlgorithmParameters.getInstance("DH");
      algParams.init(params);

      //Get Encoded private key
      byte priv[] = (new PrivateKeyInfo(new AlgorithmId(OID.dhKeyAgreement,
        algParams), this.asn1.getEncoded())).getAsn1().getEncoded();

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
    for (int k=0; k<3; k++) {
      if (k==0) {
        sb.append("DH Modulus P: \n" + "            " );
        b = this.params.getP().toByteArray();
      }
      else if (k==1) {
        sb.append("\nDH base G: \n" + "            " );
        b = this.params.getG().toByteArray();
      }
      else {
        sb.append("\nPrivate X: \n" + "            " );
        b = this.getX().toByteArray();
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

  //Constructs a DH private key from a DER INTEGER encoding and DHParams
  public DHPrivateKey(byte encoded[], DHParameterSpec params)
    throws Asn1Exception, IOException
  {
    this.decode(Asn1.getAsn1(encoded));
    this.params = params;
  }

  private static final boolean DUMMY = Licensed.VALID;
}
