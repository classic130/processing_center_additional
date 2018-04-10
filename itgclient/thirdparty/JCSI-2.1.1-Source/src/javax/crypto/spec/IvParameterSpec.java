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

package javax.crypto.spec;

import java.security.spec.AlgorithmParameterSpec;

/**
 * This class specifies an initialization vector (IV). 
 * IVs are used by ciphers in feedback mode, e.g., DES in CBC mode. 
 *
 * @see java.security.spec.AlgorithmParameterSpec
 *
 * @version 0.1, 97/11/26
 * @author Ming Yung 
 */
public class IvParameterSpec implements AlgorithmParameterSpec
{
  private byte iv[];

  /**
   * Uses the bytes in iv as the IV.
   * 
   * @param iv the buffer with the IV  
   */
  public IvParameterSpec(byte iv[])
  {
    this(iv, 0, iv.length);
  }

  /**
   * Uses the first len bytes in iv, beginning at offset, as the IV.
   * 
   * @param iv the buffer with the IV
   * @param offset the offset in iv, where the IV starts
   * @param len the number of IV bytes
   */
  public IvParameterSpec(byte iv[], int offset, int len)
  {
    this.iv = new byte[len];
    System.arraycopy(iv, offset, this.iv, 0, len);
  }

  /**
   * Returns the initialization vector (IV).
   * 
   * @return the initialization vector (IV)
   */
  public byte[] getIV()
  {
    return iv;
  }
}
