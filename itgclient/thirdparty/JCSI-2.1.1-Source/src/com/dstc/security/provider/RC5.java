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
import java.security.InvalidKeyException;
import java.security.spec.AlgorithmParameterSpec;
import javax.crypto.spec.RC5ParameterSpec;

import com.dstc.security.util.Bytes;

/**
 * <p>Implements the RC5 block cipher algorithm from RSA.
 *
 * @see com.dstc.security.provider.BlockCipher
 * @see javax.crypto.Cipher
 *
 * @version 0.98, 98/07/01
 * @author Ming Yung
 */
public final class RC5 extends BlockCipher 
{
  private int S[];
  private int numRounds = 12;
  private int wordSize = 32; //in bits

  public RC5() 
  {
    blockSize = (wordSize)/4;
  }

  protected void initialize(Key key, AlgorithmParameterSpec params) 
    throws IllegalStateException, InvalidKeyException 
  {
    if (!key.getAlgorithm().equals("RC5")) 
    {
      throw new InvalidKeyException ("Not an RC5 Key");
    }

    if (params instanceof RC5ParameterSpec)
    {
      this.numRounds =
        ((RC5ParameterSpec)params).getRounds();

      this.wordSize =
        ((RC5ParameterSpec)params).getWordSize();
      blockSize = (wordSize)/4;

      byte iv[] = ((RC5ParameterSpec)params).getIV();

      if (iv != null) IV = iv;
    }

    //Construct array L
    byte keyBytes[] = key.getEncoded();
    int L[] = Bytes.bytesLSBToInts(keyBytes, 0, keyBytes.length);

    //Construct array S
    S = new int[2*numRounds + 2];
    S[0] = 0xb7e15163;
    for (int i=1; i<S.length; i++) 
    {
      S[i] = S[i-1] + 0x9e3779b9;
    }

    //Mix L into S
    int ii = 0, jj = 0, kk;
    int P = 0, Q = 0;
    if (L.length > S.length)
      kk = 3 * L.length; 
    else
      kk = 3 * S.length; 
    for ( ; kk > 0 ; kk--)  
    {
      P = (((S[ii] + P + Q) << 3) | ((S[ii] + P + Q) >>> 29));
      S[ii] = P;
      Q = ((L[jj] + P + Q << ((P+Q) & 0x1f)) | 
           (L[jj] + P + Q >>> 32 - ((P+Q) & 0x1f)));
      L[jj] = Q;
      ii = (ii + 1) % S.length;
      jj = (jj + 1) % L.length;
    }
  }

  protected void encryptBlock(byte inBytes[], byte outBytes[]) 
  {
    int in[] = Bytes.bytesLSBToInts(inBytes, 0, blockSize);
    int A = in[0] + S[0];
    int B = in[1] + S[1];

    for (int i=1; i <= numRounds; i++) 
    {
      A ^= B;
      A = ((A << (B & 0x1f)) | (A >>> (32 - (B & 0x1f)))) + S[2*i];
      B ^= A;
      B = ((B << (A & 0x1f)) | (B >>> (32 - (A & 0x1f)))) + S[2*i+1];
    }

    int out[] = {A, B};
    Bytes.intsToBytesLSB(out, outBytes);
  }

  protected void decryptBlock(byte inBytes[], byte outBytes[]) 
  {
    int in[] = Bytes.bytesLSBToInts(inBytes, 0, blockSize);
    int A = in[0];
    int B = in[1];

    for (int i=numRounds; i >= 1; i--) {
      B = B - S[2*i+1];
      B = (B >>> (A & 0x1f)) | (B << (32 - (A & 0x1f)));
      B ^= A;
      A = A - S[2*i];
      A = (A >>> (B & 0x1f)) | (A << (32 - (B & 0x1f)));
      A ^= B;
    }

    int out[] = {A - S[0], B - S[1]};
    Bytes.intsToBytesLSB(out, outBytes);
  }
}
