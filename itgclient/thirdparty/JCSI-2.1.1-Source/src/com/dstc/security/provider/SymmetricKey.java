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

import javax.crypto.SecretKey;

/**
 * <p>Implements a Secret Key to use with a symmetric cipher.
 *
 * @see javax.crypto.SecretKey
 *
 * @version 0.98, 98/07/01
 * @author Ming Yung
 */
public class SymmetricKey implements SecretKey
{
  private static final String RAW = "RAW";
  private byte[] keyBytes;
  private String alg;

  SymmetricKey(String alg, byte bytes[], int offset, int len) 
  {
    this.alg = alg;
    this.keyBytes = new byte[len];
    System.arraycopy(bytes, offset, this.keyBytes, 0, len);
  }

  SymmetricKey(String alg, byte bytes[]) 
  {
    this.alg = alg;
    this.keyBytes = bytes;
  }

  public String getAlgorithm() 
  {
    return this.alg;
  }

  public String getFormat() 
  {
    return RAW;
  }

  public byte[] getEncoded() 
  {
    return keyBytes;
  }

  public String toString() 
  {
    StringBuffer sb = new StringBuffer();
    sb.append("Key bytes: \n" + "            " );
    for (int i=0; i<keyBytes.length; i++)
    {
      if ((i>0) && (i % 20 == 0)) {
          sb.append("\n            ");
      }
      if (keyBytes[i] <16 && keyBytes[i] >=0) {
        sb.append("0"+java.lang.Integer.toHexString(keyBytes[i] & 0xff) + " ");
      }
      else {
        sb.append(java.lang.Integer.toHexString(keyBytes[i] & 0xff) + " ");
      }
    } 
    return sb.toString();
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

  private static final boolean DUMMY = Licensed.VALID;
}
