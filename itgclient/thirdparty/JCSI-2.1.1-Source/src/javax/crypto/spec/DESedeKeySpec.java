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

import java.security.spec.KeySpec;
import java.security.InvalidKeyException;

/**
 * <p>This class specifies a DES-EDE ("triple-DES") key. 
 *
 * @see java.security.Key
 * @see java.security.KeyFactory
 * @see java.security.spec.KeySpec
 *
 * @version 0.98, 98/07/01
 * @author Ming Yung
 *
 */
public class DESedeKeySpec implements KeySpec
{
  public static final int DES_EDE_KEY_LEN = 24;
  private byte keyBytes[];

  /**
   * Uses the first 24 bytes in key as the DES-EDE key
   *
   * @param key the buffer with the DES-EDE key
   *
   * @exception java.security.InvalidKeyException if the given key
   * material is shorter than 24 bytes
   */
  public DESedeKeySpec(byte[] key) throws InvalidKeyException
  {
    this(key, 0);
  }

  /**
   * Uses the first 24 bytes in key, beginning at offset, as the DES-EDE key
   *
   * @param key the buffer with the DES-EDE key
   * @param offset the offset in key, where the DES-EDE key starts
   *
   * @exception java.security.InvalidKeyException if the given key
   * material, starting at offset, is shorter than 24 bytes
   */
  public DESedeKeySpec(byte[] key, int offset) throws InvalidKeyException
  {
    if(key.length - offset < DES_EDE_KEY_LEN) 
      throw new InvalidKeyException("Key too short");

    keyBytes = new byte[DES_EDE_KEY_LEN];
    System.arraycopy(key, offset, keyBytes, 0, DES_EDE_KEY_LEN);
  }

  /**
   * Returns the DES-EDE key.
   *
   * @return the DES-EDE key
   */
  public byte[] getKey()
  {
    return keyBytes;
  }

  /**
   * Checks if the given DES-EDE key, starting at offset, is parity-adjusted.
   *
   * @return true if the given DES-EDE key is parity-adjusted, false
   * otherwise
   *
   * @exception java.security.InvalidKeyException if the given key
   * material, starting at offset, is shorter than 24 bytes
   */
  public static boolean isParityAdjusted(byte[] key, int offset) 
    throws InvalidKeyException
  {
    for (int j=offset; j < key.length; j++)
    {
      int score = 0;
      for (int i=7; i>=0; i--)
      {
        score += (key[j] >>> i) & 0x1;
      }
      if (0 == score % 2) return false;
    }
    return true;
  }
}
