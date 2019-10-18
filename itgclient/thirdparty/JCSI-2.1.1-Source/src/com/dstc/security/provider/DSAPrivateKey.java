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
import java.security.interfaces.DSAParams;
import java.security.spec.DSAParameterSpec;

import javax.crypto.Cipher;
import javax.crypto.spec.PBEParameterSpec;

import com.dstc.security.asn1.Asn1;
import com.dstc.security.asn1.Asn1Exception;
import com.dstc.security.asn1.Sequence;
import com.dstc.security.asn1.BitString;
import com.dstc.security.common.OID;
import com.dstc.security.common.AlgorithmId;
import com.dstc.security.common.PrivateKeyInfo;

/**
 * <p>Implements a private key for use with the DSA signature algorithm.
 * 
 * @see java.security.PublicKey
 * @see java.security.Signature
 * @see com.dstc.security.provider.DSAParameters
 * @see com.dstc.security.provider.DSAPublicKey
 *
 * @version 0.98, 98/07/01
 * @author Ming Yung
 */
public class DSAPrivateKey 
  implements PrivateKey, java.security.interfaces.DSAPrivateKey
{
  private Asn1 asn1 = null;
  private BigInteger x;
  private DSAParameterSpec dsaParamsSpec;

  private void encode()
  {
    this.asn1 = new com.dstc.security.asn1.Integer(this.x);
  }

  private void decode(Asn1 asn1) throws IOException
  {
    this.asn1 = asn1;
    this.x = ((com.dstc.security.asn1.Integer)asn1).getBigInteger();
  }

  /**
   * Constructs a DSAPrivateKey given value x and DSAParams
   */
  protected DSAPrivateKey(BigInteger x, DSAParams dsaParams) 
  {
    this.x = x;
    this.dsaParamsSpec 
      = new DSAParameterSpec(dsaParams.getP(), 
          dsaParams.getQ(), dsaParams.getG());
    this.encode();
  }

  /**
   * Returns algorithm "DSA"
   */
  public String getAlgorithm() 
  {
    return "DSA";
  }

  /**
   * Returns format "PKCS#8"
   */
  public String getFormat() 
  {
    return "PKCS#8";
  }

  /**
   * Returns value x
   */
  public BigInteger getX() 
  {
    return x;
  }

  /**
   * Returns DSAParams for this key
   */
  public DSAParams getParams() 
  {
    return dsaParamsSpec;
  }

  /**
   * Returns DER encoding of PrivateKeyInfo for this key
   */
  public byte[] getEncoded()
  {
    try
    {
      AlgorithmParameters algParams =
        AlgorithmParameters.getInstance("DSA");
      algParams.init(dsaParamsSpec);

      //Get Encoded private key
      byte priv[] = (new PrivateKeyInfo(new AlgorithmId(OID.dsa,
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
    for (int k=0; k<4; k++) {
      if (k==0) {
        sb.append("DSA Param P: \n" + "            " );
        b = this.dsaParamsSpec.getP().toByteArray();
      }
      else if (k==1) {
        sb.append("\nDSA Param Q: \n" + "            " );
        b = this.dsaParamsSpec.getQ().toByteArray();
      }
      else if (k==2) {
        sb.append("\nDSA Param G: \n" + "            " );
        b = this.dsaParamsSpec.getG().toByteArray();
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

  //Constructs a DSA private key from a DER INTEGER encoding and DSAParams
  public DSAPrivateKey(byte encoded[], DSAParameterSpec dsaParamsSpec)
    throws Asn1Exception, IOException
  {
    this.decode(Asn1.getAsn1(encoded));
    this.dsaParamsSpec = dsaParamsSpec;
  }

  private static final boolean DUMMY = Licensed.VALID;
}
