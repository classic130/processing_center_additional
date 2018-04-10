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

import java.security.SecureRandom;
import java.security.Key;
import java.security.InvalidKeyException;
import java.security.spec.AlgorithmParameterSpec;
import javax.crypto.Cipher;

/**
 * <p>Implements the IDEA block cipher algorithm.
 *
 * @see com.dstc.security.provider.BlockCipher
 * @see javax.crypto.Cipher
 *
 * @version 0.98, 98/07/01
 * @author Dean Povey
 * @author Ming Yung
 */
public final class IDEA extends BlockCipher 
{
  private int[] encKeys;
  private int[] decKeys;

  public IDEA() 
  {
    blockSize = 8;
  }
  
  protected void initialize(Key key, AlgorithmParameterSpec params)
    throws IllegalStateException, InvalidKeyException 
  {
    if (!key.getAlgorithm().equals("IDEA")) 
    {
      throw new InvalidKeyException ("Not an IDEA Key");
    }

    // Set the keys
    encKeys = generateEncKeys(key.getEncoded());
    decKeys = generateDecKeys();
  }

  protected void encryptBlock(byte inBytes[], byte outBytes[]) 
  {
    idea(inBytes, 0, outBytes, 0, encKeys);
  }

  protected void decryptBlock(byte inBytes[], byte outBytes[]) 
  {
    idea(inBytes, 0, outBytes, 0, decKeys);
  }

  private void idea(byte[] in, int inOff, byte[] out, 
                    int outOff, int subKeys[]) 
  {
    int x1 = ((in[inOff++] & 0xff) << 8) | (in[inOff++] & 0xff);
    int x2 = ((in[inOff++] & 0xff) << 8) | (in[inOff++] & 0xff);
    int x3 = ((in[inOff++] & 0xff) << 8) | (in[inOff++] & 0xff);
    int x4 = ((in[inOff++] & 0xff) << 8) | (in[inOff] & 0xff);

    int i = 0;
    int round = 8;
    int s2, s3;

    while (round-- > 0) 
    {
      x1 = mulmod(x1, subKeys[i++]);
      x2 += subKeys[i++];
      x3 += subKeys[i++];
      x4 = mulmod(x4, subKeys[i++]);

      s3 = x3;
      x3 = mulmod(x1 ^ x3, subKeys[i++]);
      s2 = x2;
      x2 = mulmod(x3 + (x2 ^ x4), subKeys[i++]);
      x3 += x2;

      x1 ^= x2;
      x4 ^= x3;
      x2 ^= s3;
      x3 ^= s2;
    }

    s2 = mulmod(x1, subKeys[i++]);
    out[outOff++] = (byte)(s2 >>> 8);
    out[outOff++] = (byte) s2;
    s2 = x3 + subKeys[i++];
    out[outOff++] = (byte)(s2 >>> 8);
    out[outOff++] = (byte) s2;
    s2 = x2 + subKeys[i++];
    out[outOff++] = (byte)(s2 >>> 8);
    out[outOff++] = (byte) s2;
    s2 = mulmod(x4, subKeys[i]);
    out[outOff++] = (byte)(s2 >>> 8);
    out[outOff] = (byte) s2;
  }

  private static int mulmod(int a, int b) 
  {
    a &= 0xffff;
    b &= 0xffff;

    int p;
    if (a != 0) 
    {
      if (b != 0) 
      {
        p = a * b;
        b = p & 0xffff;
        a = p >>> 16;
        return (b - a + (b < a ? 1 : 0));
      } 
      else
        return (1 - a);
    } 
    else
      return (1 - b);
  }

  private int[] generateEncKeys(byte[] keyBytes)
  {
    int[] retval = new int[52];

    retval[0] = (keyBytes[0] & 0xff) << 8 | (keyBytes[1] & 0xff);
    retval[1] = (keyBytes[2] & 0xff) << 8 | (keyBytes[3] & 0xff);
    retval[2] = (keyBytes[4] & 0xff) << 8 | (keyBytes[5] & 0xff);
    retval[3] = (keyBytes[6] & 0xff) << 8 | (keyBytes[7] & 0xff);
    retval[4] = (keyBytes[8] & 0xff) << 8 | (keyBytes[9] & 0xff);
    retval[5] = (keyBytes[10] & 0xff) << 8 | (keyBytes[11] & 0xff);
    retval[6] = (keyBytes[12] & 0xff) << 8 | (keyBytes[13] & 0xff);
    retval[7] = (keyBytes[14] & 0xff) << 8 | (keyBytes[15] & 0xff);

    for (int i = 0, off = 0, j = 8; j < 52; i &= 7, j++) 
    {
      i++;
      retval[i + 7 + off] = (retval[(i & 7) + off] << 9) |
          ((retval[((i + 1) & 7) + off] >>> 7) & 0x1ff);
      off += i & 8;
    }
    return retval;
  }

  private int[] generateDecKeys() 
  {
    int[] retval = new int[52];
    int i, j = 4, k = 51;
    retval[k--] = mulInv(encKeys[3]);
    retval[k--] =  -encKeys[2];
    retval[k--] =  -encKeys[1];
    retval[k--] = mulInv(encKeys[0]);
    for (i = 1; i < 8; i++, j += 6) 
    {
      retval[k--] = encKeys[j + 1];
      retval[k--] = encKeys[j];
      retval[k--] = mulInv(encKeys[j + 5]);
      retval[k--] =  -encKeys[j + 3];
      retval[k--] =  -encKeys[j + 4];
      retval[k--] = mulInv(encKeys[j + 2]);
    }
    retval[k--] = encKeys[j + 1];
    retval[k--] = encKeys[j];
    retval[k--] = mulInv(encKeys[j + 5]);
    retval[k--] =  -encKeys[j + 4];
    retval[k--] =  -encKeys[j + 3];
    retval[k--] = mulInv(encKeys[j + 2]);
    return retval;
  }

  private static int mulInv(int xx) 
  {
    int x = xx & 0xffff;
    if (x <= 1)
      return x; 

    int t1 = 0x10001 / x;        
    int y = 0x10001 % x;
    if (y == 1)
      return (1 - t1);

    int t0 = 1;
    int q;
    do 
    {
      q = x / y;
      x = x % y;
      t0 += q * t1;
      if (x == 1)
        return t0;
      q = y / x;
      y %= x;
      t1 += q * t0;
    } 
    while (y != 1);
    return (1 - t1);
  }
}
