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
import java.security.PublicKey;
import java.security.AlgorithmParameters;
import java.security.interfaces.DSAParams;
import java.security.spec.DSAParameterSpec;

import com.dstc.security.asn1.Asn1;
import com.dstc.security.asn1.Asn1Exception;
import com.dstc.security.common.OID;
import com.dstc.security.common.AlgorithmId;
import com.dstc.security.common.SubjectPublicKeyInfo;

/**
 * <p>Implements a public key for use with the DSA signature algorithm.
 * 
 * @see java.security.PublicKey
 * @see java.security.Signature
 * @see com.dstc.security.provider.DSAParameters
 * @see com.dstc.security.provider.DSAPrivateKey
 *
 * @version 0.98, 98/07/01
 * @author Ming Yung
 */
public class DSAPublicKey
  implements PublicKey, java.security.interfaces.DSAPublicKey
{
  private Asn1 asn1 = null;
  private BigInteger y;
  private DSAParameterSpec dsaParamsSpec;

  private void decode(Asn1 asn1) throws IOException
  {
    this.asn1 = asn1;
    this.y = ((com.dstc.security.asn1.Integer)asn1).getBigInteger();
  }

  //Constructs a DSA public key from a value y and DSAParams
  protected DSAPublicKey(BigInteger y, DSAParams params)
  {
    this.y = y;
    this.asn1 = new com.dstc.security.asn1.Integer(y);

    this.dsaParamsSpec 
      = new DSAParameterSpec(params.getP(), params.getQ(), params.getG());
  }

  /**
   * Returns algorithm "DSA"
   */
  public String getAlgorithm () 
  {
    return "DSA";
  }

  /**
   * Returns format "X.509"
   */
  public String getFormat () 
  {
    return "X.509";
  }

  /**
   * Returns value y
   */
  public BigInteger getY () 
  {
    return y;
  }

  /**
   * Returns DSAParams for this key
   */
  public DSAParams getParams() 
  {
    return dsaParamsSpec;
  }

  /**
   * Returns DER encoding of SubjectPublicKeyInfo for this key
   */
  public byte[] getEncoded()
  {
    try
    {
      AlgorithmParameters algParams = 
        AlgorithmParameters.getInstance("DSA");
      algParams.init(dsaParamsSpec);

      return new SubjectPublicKeyInfo(new AlgorithmId(OID.dsa, algParams),
        this.asn1.getEncoded()).getAsn1().getEncoded();
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
        sb.append("\nPublic Y: \n" + "            " );
        b = this.getY().toByteArray();
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


  //Constructs a DSA public key from a DER INTEGER encoding and DSAParams
  protected DSAPublicKey(byte encoded[], DSAParameterSpec dsaParamsSpec) 
    throws Asn1Exception, IOException
  {
    this.decode(Asn1.getAsn1(encoded));
    this.dsaParamsSpec = dsaParamsSpec;
  } 

  private static final boolean DUMMY = Licensed.VALID;
}
