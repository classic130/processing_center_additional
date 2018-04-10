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

import java.security.Key;
import java.security.SecureRandom;
import java.security.AlgorithmParameters;
import java.security.InvalidKeyException;
import java.security.NoSuchAlgorithmException;
import java.security.InvalidAlgorithmParameterException;
import java.security.spec.AlgorithmParameterSpec;
import javax.crypto.Cipher;
import javax.crypto.CipherSpi;
import javax.crypto.NoSuchPaddingException;
import javax.crypto.ShortBufferException;
import javax.crypto.BadPaddingException;
import javax.crypto.IllegalBlockSizeException;

/**
 * <p>Implements the RC4 stream cipher algorithm from RSA.
 *
 * @see javax.crypto.Cipher
 *
 * @version 0.98, 98/07/01
 * @author Ming Yung
 */
public final class RC4 extends CipherSpi
{
  private final byte[] S = new byte[256];
  private int x, y;

  public RC4() 
  {
  }

  public void engineSetPadding(String padding) throws NoSuchPaddingException 
  {
    throw new NoSuchPaddingException("No padding needed for RC4");
  }

  public void engineSetMode(String mode) throws NoSuchAlgorithmException 
  {
    throw new NoSuchAlgorithmException("mode " + mode + " unsupported for RC4");
  }

  protected int engineGetBlockSize() 
  {
    //Not a block cipher
    return 0;
  }

  protected int engineGetOutputSize(int inputLen)
  {
    return inputLen;
  }

  protected byte[] engineGetIV() 
  {
    return null;
  }

  protected AlgorithmParameters engineGetParameters()
  {
    return null;
  }

  protected void engineInit(int opmode, Key key, SecureRandom random) 
    throws InvalidKeyException 
  {
    final byte[] S = this.S;
    final int sLength = S.length;  // (256)

    if (!(key.getAlgorithm().equals("RC4"))) 
    {
      throw new InvalidKeyException ("Not an RC4 Key");
    }

    final byte[] keyBytes = key.getEncoded();
    // Just in case someone gives us a key > 256 bytes:
    int keyLength = Math.min(keyBytes.length, sLength);

    for (int i = 0; i < sLength; i++) 
    {
      S[i] = (byte)i;
    }

    int i = 0;
    int j = 0;

    // Maximum x such that S[x .. (x+keyLength-1)] is in bounds
    final int limit = sLength - keyLength;
    while (i <= limit)
    {
      for (int k = 0;  k < keyLength;  k++, i++)
      {
        byte s_i = S[i];
        j = (j + s_i + keyBytes[k]) & 0xff;
        S[i] = S[j];
        S[j] = s_i;
      }
    }

    // Mop up any bytes at the end (if S.length % keyLength != 0)
    for (int k = 0;  i < sLength;  k++, i++)
    {
      byte s_i = S[i];
      j = (j + s_i + keyBytes[k]) & 0xff;
      S[i] = S[j];
      S[j] = s_i;
    }

    this.x = 0;
    this.y = 0;
  } 

  protected void engineInit(int opmode, Key key, AlgorithmParameterSpec params,
                            SecureRandom random) 
    throws InvalidKeyException, InvalidAlgorithmParameterException 
  {
    engineInit(opmode, key, random);
  }

  protected void engineInit(int opmode, Key key, AlgorithmParameters params,
                            SecureRandom random) 
    throws InvalidKeyException, InvalidAlgorithmParameterException 
  {
    engineInit(opmode, key, random);
  }

  protected byte[] engineUpdate(byte input[], int inputOffset, int inputLen) 
  {  
    byte[] result = new byte[inputLen];
    encrypt(input, inputOffset, inputLen, result, 0);
    return result;
  }

  protected int engineUpdate(byte input[], int inputOffset, int inputLen,
                             byte output[], int outputOffset) 
    throws ShortBufferException 
  {
    if (outputOffset + inputLen > output.length) {
      throw new ShortBufferException();
    }
    encrypt(input, inputOffset, inputLen, output, outputOffset);
    return inputLen;
  }

  protected byte[] engineDoFinal(byte input[], int inputOffset, int inputLen) 
    throws IllegalBlockSizeException, BadPaddingException 
  {
    return engineUpdate(input, inputOffset, inputLen);
  }

  protected int engineDoFinal(byte input[], int inputOffset, int inputLen,
                              byte output[], int outputOffset) 
    throws ShortBufferException, 
           IllegalBlockSizeException, BadPaddingException 
  {
    return engineUpdate(input, inputOffset, inputLen, output, outputOffset);
  }

  /**
   * crypt input[ inputOffset ..  inputOffset + inputLen - 1]
   *   to output[outputOffset .. outputOffset + inputLen - 1]
   */
  private final void encrypt(byte input[], int inputOffset, int inputLen,
                             byte output[], int outputOffset)
  {
    final byte[] S = this.S;

    // Cache instance variables in locals, write back updated values at end
    int x = this.x;
    int y = this.y;

    for (int i=0; i < inputLen; i++) {
      //Oh for an unsigned byte type in java :-(

      x = (x + 1) & 0xff;
      byte s_x = S[x];

      y = (y + s_x) & 0xff;
      byte s_y = S[y];

      S[x] = s_y;
      S[y] = s_x;

      output[outputOffset + i] =
        (byte) (input[inputOffset + i] ^ S[(s_x + s_y) & 0xff]);
    }

    this.x = x;
    this.y = y;
  }

  private static final boolean DUMMY = Licensed.VALID;
}
