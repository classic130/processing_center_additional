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

import java.security.MessageDigestSpi;
import java.security.DigestException;

import com.dstc.security.util.Bytes;

/**
 * <p>Implements the MD5 Message Digest algorithm from RSA.
 *
 * @see java.security.MessageDigest
 *
 * @version 0.98, 98/07/01
 * @author Ming Yung, Chunxiao Li
 */
public final class MD4 extends MessageDigestSpi implements Cloneable
{
  private static final int DIGEST_LENGTH = 16;
  private static final int BLOCKSIZE = 64; //in bytes
  private byte[] inputBuffer = new byte[BLOCKSIZE];
  private int inputBufferOffset;
  private int mdbuf0;
  private int mdbuf1;
  private int mdbuf2;
  private int mdbuf3;
  private int plainTextLength;
  private int[] temp = new int[BLOCKSIZE >> 2];
  private static int iGG = 0x5a827999;
  private static int iHH = 0x6ed9eba1;

  public MD4() 
  {
    //Initialize
    doReset();
  }

  protected int engineDigest(byte[] buf, int offset, int length)
    throws DigestException
  {
    if (length < DIGEST_LENGTH)
      throw new DigestException("Specified length too short for digest");

    if (buf.length - offset < DIGEST_LENGTH)
      throw new DigestException("Buffer too short for digest");

    byte[] temp = engineDigest();
    System.arraycopy(temp, 0, buf, offset, DIGEST_LENGTH);
  
    return DIGEST_LENGTH;
  }

  protected byte[] engineDigest() 
  {
    int temp =  56 - (plainTextLength & 0x3f);
    int extra = temp > 0 ? temp : 64 + temp;

    //NB: There are either one or two blocks to encrypt

    //Step 1: Add padding
    inputBuffer[inputBufferOffset] = (byte)0x80;
    int start = 1;

    if (inputBufferOffset + extra > BLOCKSIZE) 
    {
      //Two blocks to encrypt: Do first block
      start = BLOCKSIZE - inputBufferOffset;
      for (int i=1; i<start; i++) 
      {
        inputBuffer[inputBufferOffset + i] = 0x00;
      }
      doDecodeBlock();
      inputBufferOffset = -start;
    }
      
    for (int i=start; i<extra; i++) 
    {
      inputBuffer[inputBufferOffset + i] = 0x00;
    }
    inputBufferOffset += extra;

    //Step 2: Append length in bits
    long lb = (long)(plainTextLength*8);
    for (int i=0; i<8; i++) 
    {
      inputBuffer[inputBufferOffset+i] = (byte)((lb >>> 8*i) & 0xff);
    }

    //Last block to doDecode
    doDecodeBlock();
    
    byte retval[] = Bytes.intsToBytesLSB(new int[]{mdbuf0, mdbuf1,
                                mdbuf2, mdbuf3});
    doReset();
    return retval;
  }

  protected int engineGetDigestLength()
  {
    return DIGEST_LENGTH;
  }

  protected void engineReset() 
  {
    doReset();
  }

  private final void doReset() 
  {
    inputBufferOffset = 0;
    plainTextLength = 0;
    mdbuf0 = 0x67452301;
    mdbuf1 = 0xefcdab89;
    mdbuf2 = 0x98badcfe;
    mdbuf3 = 0x10325476;
  }

  protected void engineUpdate(byte input)
  {
    byte in[] = new byte[1];
    in[0] = input;
    engineUpdate(in, 0, 1);
  }

  protected void engineUpdate(byte input[], int inputOffset, int length) 
  {
    int len;
    int left = length;
    int inputUsed = 0;
    while (true) 
    {
      len = BLOCKSIZE - inputBufferOffset;
      if (len <= left) 
      {
        //Enough input for block
        System.arraycopy(input, inputUsed + inputOffset, inputBuffer,
                          inputBufferOffset, len);
        doDecodeBlock();
        left -= len;
        inputBufferOffset = 0;
        inputUsed += len;
      } 
      else 
      {
        //Buffer the remaining input
        System.arraycopy(input, inputUsed + inputOffset, inputBuffer,
                         inputBufferOffset, left);
        inputBufferOffset += left;
        break;
      }
    }
    plainTextLength += length;
  }

  public Object clone() throws CloneNotSupportedException
  {
    MD4 retval = new MD4();
    retval.inputBufferOffset = this.inputBufferOffset;
    retval.plainTextLength = this.plainTextLength;
    retval.mdbuf0 = this.mdbuf0;
    retval.mdbuf1 = this.mdbuf1;
    retval.mdbuf2 = this.mdbuf2;
    retval.mdbuf3 = this.mdbuf3;
    System.arraycopy(this.inputBuffer, 0, retval.inputBuffer, 0, BLOCKSIZE);
    return retval;
  }

  private int FF(int a, int b, int c, int d, int k, int s) 
  {
     int t =  a + ((b & c) | ((~b) & d)) + temp[k];
     return  ((t << s) | (t >>> (32-s))) ;
  }

  private int GG(int a, int b, int c, int d, int k, int s) 
  {
     int t = a + ((b & c) | (b & d) | (d & c)) + temp[k] + iGG;
     return  ((t << s) | (t >>> (32-s))) ;
  }

  private int HH(int a, int b, int c, int d, int k, int s) 
  {
     int t = a + (b ^ c ^ d) + temp[k] + iHH;
     return  ((t << s) | (t >>> (32-s))) ;
  }

  private void doDecodeBlock() 
  {
    int off = 0;
    int s_off = 0;
    while (off < BLOCKSIZE)
    {
        temp[s_off++] = ((inputBuffer[off+3] & 0xff) << 24) |
           ((inputBuffer[off + 2] & 0xff)<< 16) |
          ((inputBuffer[off +1] & 0xff) << 8) | (inputBuffer[off] & 0xff) ;
        off += 4;
    }

    int a = mdbuf0;
    int b = mdbuf1;
    int c = mdbuf2;
    int d = mdbuf3;

    //Round 1
    a = FF(a, b, c, d, 0, 3);
    d = FF(d, a, b, c, 1, 7);
    c = FF(c, d, a, b, 2, 11);
    b = FF(b, c, d, a, 3, 19);

    a = FF(a, b, c, d, 4, 3);
    d = FF(d, a, b, c, 5, 7);
    c = FF(c, d, a, b, 6, 11);
    b = FF(b, c, d, a, 7, 19);

    a = FF(a, b, c, d, 8, 3);
    d = FF(d, a, b, c, 9, 7);
    c = FF(c, d, a, b, 10, 11);
    b = FF(b, c, d, a, 11, 19);

    a = FF(a, b, c, d, 12, 3);
    d = FF(d, a, b, c, 13, 7);
    c = FF(c, d, a, b, 14, 11);
    b = FF(b, c, d, a, 15, 19);

    //Round 2
    a = GG(a, b, c, d, 0, 3);
    d = GG(d, a, b, c, 4, 5);
    c = GG(c, d, a, b, 8, 9);
    b = GG(b, c, d, a, 12, 13);

    a = GG(a, b, c, d, 1, 3);
    d = GG(d, a, b, c, 5, 5);
    c = GG(c, d, a, b, 9, 9);
    b = GG(b, c, d, a, 13, 13);

    a = GG(a, b, c, d, 2, 3);
    d = GG(d, a, b, c, 6, 5);
    c = GG(c, d, a, b, 10, 9);
    b = GG(b, c, d, a, 14, 13);

    a = GG(a, b, c, d, 3, 3);
    d = GG(d, a, b, c, 7, 5);
    c = GG(c, d, a, b, 11, 9);
    b = GG(b, c, d, a, 15, 13);

    //Round 3
    a = HH(a, b, c, d, 0, 3);
    d = HH(d, a, b, c, 8, 9);
    c = HH(c, d, a, b, 4, 11);
    b = HH(b, c, d, a, 12, 15);

    a = HH(a, b, c, d, 2, 3);
    d = HH(d, a, b, c, 10, 9);
    c = HH(c, d, a, b, 6, 11);
    b = HH(b, c, d, a, 14, 15);

    a = HH(a, b, c, d, 1, 3);
    d = HH(d, a, b, c, 9, 9);
    c = HH(c, d, a, b, 5, 11);
    b = HH(b, c, d, a, 13, 15);

    a = HH(a, b, c, d, 3, 3);
    d = HH(d, a, b, c, 11, 9);
    c = HH(c, d, a, b, 7, 11);
    b = HH(b, c, d, a, 15, 15);

    mdbuf0 += a;
    mdbuf1 += b;
    mdbuf2 += c;
    mdbuf3 += d;
  }

  private static final boolean DUMMY = Licensed.VALID;
}
