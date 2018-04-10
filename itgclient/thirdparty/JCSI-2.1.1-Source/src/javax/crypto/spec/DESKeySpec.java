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

import java.security.InvalidKeyException;
import java.security.spec.KeySpec;

/**
 * <p>This class specifies a DES key. 
 *
 * @see java.security.Key
 * @see java.security.KeyFactory
 * @see java.security.spec.KeySpec
 *
 * @version 0.98, 98/07/01
 * @author Ming Yung
 *
 */
public class DESKeySpec implements KeySpec
{
  public static final int DES_KEY_LEN = 8;

  private static final byte[][] WEAK_KEYS
     = {{(byte)0x01, (byte)0x01, (byte)0x01, (byte)0x01,
         (byte)0x01, (byte)0x01, (byte)0x01, (byte)0x01},
        {(byte)0x1F, (byte)0x1F, (byte)0x1F, (byte)0x1F,
         (byte)0xE0, (byte)0xE0, (byte)0xE0, (byte)0xE0},
        {(byte)0xE0, (byte)0xE0, (byte)0xE0, (byte)0xE0,
         (byte)0x1F, (byte)0x1F, (byte)0x1F, (byte)0x1F},
        {(byte)0xFE, (byte)0xFE, (byte)0xFE, (byte)0xFE,
         (byte)0xFE, (byte)0xFE, (byte)0xFE, (byte)0xFE}};

  private static final byte[][] SEMI_WEAK_KEYS
    = {{(byte)0x01, (byte)0xFE, (byte)0x01, (byte)0xFE,
        (byte)0x01, (byte)0xFE, (byte)0x01, (byte)0xFE},
       {(byte)0x1F, (byte)0xE0, (byte)0x1F, (byte)0xE0,
        (byte)0x0E, (byte)0xF1, (byte)0x0E, (byte)0xF1},
       {(byte)0x01, (byte)0xE0, (byte)0x01, (byte)0xE0,
        (byte)0x01, (byte)0xF1, (byte)0x01, (byte)0xF1},
       {(byte)0x1F, (byte)0xFE, (byte)0x1F, (byte)0xFE,
        (byte)0x0E, (byte)0xFE, (byte)0x0E, (byte)0xFE},
       {(byte)0x01, (byte)0x1F, (byte)0x01, (byte)0x1F,
        (byte)0x01, (byte)0x0E, (byte)0x01, (byte)0x0E},
       {(byte)0xE0, (byte)0xFE, (byte)0xE0, (byte)0xFE,
        (byte)0xF1, (byte)0xFE, (byte)0xF1, (byte)0xFE}};

  private byte keyBytes[];

  /**
   * Uses the first 8 bytes in key as the key material for the DES key.
   *
   * @param key the buffer with the DES key material.
   *
   * @exception java.security.InvalidKeyException if the given key
   * material is shorter than 8 bytes.
   */
  public DESKeySpec(byte[] key) throws InvalidKeyException
  {
    this(key, 0);
  }

  /**
   * Uses the first 8 bytes in key, beginning at offset, as the key 
   * material for the DES key.
   *
   * @param key the buffer with the DES key material.
   * @param offset the offset in key, where the DES key material starts.
   *
   * @exception java.security.InvalidKeyException if the given key
   * material is shorter than 8 bytes.
   */
  public DESKeySpec(byte[] key, int offset) throws InvalidKeyException
  {
    if (key.length - offset < DES_KEY_LEN) 
      throw new InvalidKeyException("Key too short");

    keyBytes = new byte[DES_KEY_LEN];
    System.arraycopy(key, offset, keyBytes, 0, DES_KEY_LEN);
  }

  /**
   * Returns the DES key material.
   *
   * @return the DES key material.
   */
  public byte[] getKey()
  {
    return keyBytes;
  }

  /**
   * Checks if the given DES key material, starting at offset, 
   * is parity-adjusted.
   *
   * @return true if the given DES key material is parity-adjusted,
   * false otherwise.
   *
   * @exception java.security.InvalidKeyException if the given key
   * material, starting at offset, is shorter than 8 bytes.
   */
  public static boolean isParityAdjusted(byte[] key, int offset) 
    throws InvalidKeyException
  {
    int score;
    for (int j=offset; j < key.length; j++)
    {
      score = 0;
      for (int i=7; i>=0; i--)
      {
        score += (key[j] >>> i) & 0x1;
      }
      if (0 == score % 2) return false;
    }
    return true;
  }

  /**
   * Checks if the given DES key material is weak or semi-weak.
   *
   * @return true if the given DES key material is weak or semi-weak,
   * false otherwise.
   *
   * @exception java.security.InvalidKeyException if the given key
   * material, starting at offset, is shorter than 8 bytes.
   */
  public static boolean isWeak(byte[] key, int offset) 
    throws InvalidKeyException
  {
    if (key.length - offset < DES_KEY_LEN)
      throw new InvalidKeyException("Key too short");

    //simple check first
    for (int i=offset; i<offset+DES_KEY_LEN; i++)
    {
      switch (key[i])
      {
        case ((byte)0x01):
        case ((byte)0x1f):
        case ((byte)0xe0):
        case ((byte)0xfe):
        case ((byte)0xf1):
        case ((byte)0x0e):
          break;

        default: return false;
      }
    }

    //check each weak key
    for (int i=0; i<4; i++)
    {
      boolean equals = true; 
      for (int j=0; j<DES_KEY_LEN; j++)
      {
        if (WEAK_KEYS[i][j] != key[offset+j])
        {
          equals = false;
          break;
        };
      }      

      if (equals) return true;
    }

    //check each semi-weak key (pairwise)
    for (int i=0; i<6; i++)
    {
      boolean equals = true; 
      for (int j=0; j<DES_KEY_LEN; j++)
      {
        if (SEMI_WEAK_KEYS[i][j] != key[offset+j])
        {
          equals = false;
          break;
        };
      }

      for (int j=0; j<DES_KEY_LEN; j++)
      {
        int shift = (j % 2 == 0 ? 1: -1);
        if (SEMI_WEAK_KEYS[i][j+shift] != key[offset+j])
        {
          equals = false;
          break;
        };
      }      

      if (equals) return true;
    }

    return false;
  }
}
