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

package com.dstc.security.common;

import java.security.Key;
import java.security.MessageDigest;
import java.security.spec.AlgorithmParameterSpec;
import java.security.DigestException;
import java.security.InvalidKeyException;
import java.security.InvalidAlgorithmParameterException;

import javax.crypto.spec.PBEParameterSpec;

import com.dstc.security.common.PBEKeyDerivation;

/**
 * <p>An Implementation of KeyDerivation using PKCS#12 described method
 *
 * @see com.dstc.security.provider.PBEKeyDerivation
 *
 * @version 0.98, 99/05/26
 * @author Eddy Cheung
 */
public class PKCS12KeyDerivation implements PBEKeyDerivation
{
  // Note that this class has no state.  We can't make the method static,
  // but we could create and export a singleton instance -- but the overhead
  // of creating a few instances of this is pretty low compared to the work
  // that it does, so it probably doesn't matter.

  public byte[] generateKey(int opmode, MessageDigest md, 
                            Key key, AlgorithmParameterSpec params, 
                            int keyLen)
    throws InvalidKeyException, InvalidAlgorithmParameterException
  {
    //Assertion
    if (opmode < GENERATE_KEY_MODE || opmode > GENERATE_INTEGRITY_KEY_MODE)
      throw new IllegalArgumentException("Unrecognised Mode");

    if (!key.getAlgorithm().startsWith("PBE")) 
    {
      throw new InvalidKeyException ("Not a PBE Key");
    }

    if (!(params instanceof PBEParameterSpec)) {
      throw new InvalidAlgorithmParameterException("Not PBE parameters");
    }

    byte password[] = key.getEncoded();
    byte salt[] = ((PBEParameterSpec)params).getSalt();
    int iteration = ((PBEParameterSpec)params).getIterationCount();

    //find out the block size in bytes
    int v = getMessageDigestBlockSize(md);
    //get the digest size in bytes
    int u = getMessageDigestOutputSize(md);

    //Step 1. Construct the string D
    byte[] D = new byte[v];
    for (int i = 0; i < D.length; i++)
      D[i] = (byte)opmode;

    //Steps 2 to 4.  Construct I, a concatenation of S and P
    int Slen = v * roundUp(salt.length, v);
    int Plen = v * roundUp(password.length, v);
    int Ilen = Slen + Plen;
    byte[] I = new byte[Ilen];

    fillConcat(salt, I, 0, Slen);
    fillConcat(password, I, Slen, Plen);

    //Step 5.  Unnecessary -- instead we use the for-loop below

    //Steps 6 to 8.
    //Computing A (step 7) and then returning the first n bits (step 8) would
    //be inefficient;  instead we allocate a result[] array of exactly the
    //right length and copy each Ai into it as we iterate through the loop.

    int resultLen = keyLen;
    byte[] result = new byte[resultLen];

    int AiLen = u;
    byte[] Ai = new byte[AiLen];

    int Blen = v;
    byte[] B = new byte[Blen];

    for (int resultOff = 0;  true;  resultOff += AiLen)
    {
      //Step 6a
      md.reset();
      md.update(D);
      md.update(I);

      for (int n = 1; n < iteration; n++) 
      {
        checkDigest(md, Ai);
        md.reset();  // unnecessary, right?
        md.update(Ai);
      }
      checkDigest(md, Ai);
  
      if (resultOff + AiLen >= resultLen)
      {
        // Last iteration, may do only a partial copy
        System.arraycopy(Ai, 0, result, resultOff, resultLen - resultOff);

        return result;
      }

      // Normal iteration, do full copy
      System.arraycopy(Ai, 0, result, resultOff, AiLen);

      //Step 6b. Concatenate copies of Ai to create B
      fillConcat(Ai, B, 0, Blen);

      //Step 6c.  Modify I
      for (int j = 0;  j < Ilen;  j += Blen) 
      {
        // I[j .. j+v-1] += B[..] + 1
        addBigEndianByteArrays(B, 0, I, j, Blen, true);
        // (this is safe because Ilen is an exact multiple of Blen, i.e. v)
      }
    }
  }

  /**
   * More efficient (we hope) version of
   * (int) Math.ceil( (double)value / (double)divisor );
   * assumes that both arguments are positive.
   */
  private static int roundUp(int value, int divisor)
  {
    return (value + divisor - 1) / divisor;
  }

  /**
   * Fill an output array with concatenated copies of an input array.
   * The final copy may be truncated (if the output length is not an
   * integer multiple of the input length).
   */
  private static void fillConcat(byte[] in,
                                 byte[] out, int outOffset, int outLength)
  {
    final int inLength = in.length;
    final int outLimit = outOffset + outLength;

    if (inLength == 0 && outLength != 0)
    {
      throw new IllegalArgumentException("Cannot fill with empty input!");
    }

    while (outOffset + inLength < outLimit)
    {
      System.arraycopy(in, 0, out, outOffset, inLength);
      outOffset += inLength;
    }
    // Final copy -- may be whole, partial, or zero (only if inLength == 0)
    System.arraycopy(in, 0, out, outOffset, outLimit - outOffset);
  }
  
  /**
   * Get a message digest result and check that its length is what we assumed,
   * i.e. it exactly fills the output array.
   */
  private static void checkDigest(MessageDigest md, byte[] out)
  {
    final int outLength = out.length;
    try {
      int mdLen = md.digest(out, 0, outLength);
      if (mdLen != outLength)
      {
        throw new RuntimeException(
          "Internal botch -- assumed " + md.getAlgorithm() + 
          " digest length = " + outLength + 
          ", actual = " + mdLen);
      }
    }
    catch (DigestException ex)
    {
      throw new RuntimeException("Internal botch -- " + ex);
    }
  }

  /**
   * Add two multiprecision integers stored in byte arrays.  One of the
   * arrays is strictly an input value, whereas the other is both an 
   * input and an output.  We operate on slices of the arrays:  the 
   * slices are the same length in both arrays, but may start at different
   * offsets in each array.  The bytes in the slices are in big-endian order,
   * i.e. the most significant byte comes first.  Each byte is treated as an
   * unsigned value (0 to 255).  We allow an optional carry in to the least
   * significant byte;  if there is a carry out of the most significant byte
   * we do <em>not</em> store it in the output array, but instead pass it as
   * the return value of this method.
   * 
   * @param in the input byte array
   * @param inOffset the offset to the start of the slice in the input array
   * @param out the input/output byte array
   * @param outOffset the offset to the start of the slice in the input/output
   *        array
   * @param length the length (number of bytes) of the slices
   * @param carry the boolean carry-in:  true means carry in, false means none
   * @return the boolean carry-out:  true means a carry, false means none
   */
  private static boolean addBigEndianByteArrays(byte[] in, int inOffset,
                                                byte[] out, int outOffset,
                                                int length, boolean carry)
  {
    final int BYTE = 0xFF;

    int accum = (carry) ? 1 : 0;

    while (--length >= 0)
    {
      accum += 
        (in[inOffset + length] & BYTE) + (out[outOffset + length] & BYTE);

      out[outOffset + length] = (byte) accum;
      accum >>>= 8;
    }
    return accum != 0;
  }

  // Return the MessageDigest Block Size
  private static int getMessageDigestBlockSize(MessageDigest md) 
  {
    if (md.getAlgorithm().equals("SHA"))
      return 64;   //512 bit block size
    else if (md.getAlgorithm().equals("MD5"))
      return 64;
    else if (md.getAlgorithm().equals("MD2"))
      return 64;
    else if (md.getAlgorithm().equals("RIPEMD160"))
      return 64;
    else 
      return 0;
  }
  
  // Return the MessageDigest Block Size
  private static int getMessageDigestOutputSize(MessageDigest md) 
  {
    return md.getDigestLength();
  }
}

