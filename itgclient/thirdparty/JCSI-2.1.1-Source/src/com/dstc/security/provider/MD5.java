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
 * @author Ming Yung
 */
public final class MD5 extends MessageDigestSpi implements Cloneable
{
  private static final int DIGEST_LENGTH = 16;
  private static int BLOCKSIZE = 64; //in bytes
  private byte[] inputBuffer = new byte[BLOCKSIZE];
  private int inputBufferOffset;
  private int mdbuf0;
  private int mdbuf1;
  private int mdbuf2;
  private int mdbuf3;
  private int plainTextLength;
  private int[] temp = new int[BLOCKSIZE >> 2];

  public MD5() 
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
    MD5 retval = new MD5();
    retval.inputBufferOffset = this.inputBufferOffset;
    retval.plainTextLength = this.plainTextLength;
    retval.mdbuf0 = this.mdbuf0;
    retval.mdbuf1 = this.mdbuf1;
    retval.mdbuf2 = this.mdbuf2;
    retval.mdbuf3 = this.mdbuf3;
    System.arraycopy(this.inputBuffer, 0, retval.inputBuffer, 0, BLOCKSIZE);
    return retval;
  }

  private int FF(int a, int b, int c, int d, int k, int s, int i) 
  {
     int t =  a + ((b & c) | ((~b) & d)) + temp[k] + i;
     return  ((t << s) | (t >>> (32-s))) + b;
  }

  private int GG(int a, int b, int c, int d, int k, int s, int i) 
  {
     int t = a + ((b & d) | (c & (~d))) + temp[k] + i;
     return  ((t << s) | (t >>> (32-s))) + b;
  }

  private int HH(int a, int b, int c, int d, int k, int s, int i) 
  {
     int t = a + (b ^ c ^ d) + temp[k] + i;
     return  ((t << s) | (t >>> (32-s))) + b;
  }
    
  private int II(int a, int b, int c, int d, int k, int s, int i) 
  {
     int t = a + (c ^ (b | (~d))) + temp[k] + i;
     return  ((t << s) | (t >>> (32-s))) + b;
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
    a = FF(a, b, c, d, 0, 7, 0xd76aa478);
    d = FF(d, a, b, c, 1, 12, 0xe8c7b756);
    c = FF(c, d, a, b, 2, 17, 0x242070db);
    b = FF(b, c, d, a, 3, 22, 0xc1bdceee);

    a = FF(a, b, c, d, 4, 7, 0xf57c0faf);
    d = FF(d, a, b, c, 5, 12, 0x4787c62a);
    c = FF(c, d, a, b, 6, 17, 0xa8304613);
    b = FF(b, c, d, a, 7, 22, 0xfd469501);

    a = FF(a, b, c, d, 8, 7, 0x698098d8);
    d = FF(d, a, b, c, 9, 12, 0x8b44f7af);
    c = FF(c, d, a, b, 10, 17, 0xffff5bb1);
    b = FF(b, c, d, a, 11, 22, 0x895cd7be);

    a = FF(a, b, c, d, 12, 7, 0x6b901122);
    d = FF(d, a, b, c, 13, 12, 0xfd987193);
    c = FF(c, d, a, b, 14, 17, 0xa679438e);
    b = FF(b, c, d, a, 15, 22, 0x49b40821);

    //Round 2
    a = GG(a, b, c, d, 1, 5, 0xf61e2562);
    d = GG(d, a, b, c, 6, 9, 0xc040b340);
    c = GG(c, d, a, b, 11, 14, 0x265e5a51);
    b = GG(b, c, d, a, 0, 20, 0xe9b6c7aa);

    a = GG(a, b, c, d, 5, 5, 0xd62f105d);
    d = GG(d, a, b, c, 10, 9, 0x2441453);
    c = GG(c, d, a, b, 15, 14, 0xd8a1e681);
    b = GG(b, c, d, a, 4, 20, 0xe7d3fbc8);

    a = GG(a, b, c, d, 9, 5, 0x21e1cde6);
    d = GG(d, a, b, c, 14, 9, 0xc33707d6);
    c = GG(c, d, a, b, 3, 14, 0xf4d50d87);
    b = GG(b, c, d, a, 8, 20, 0x455a14ed);

    a = GG(a, b, c, d, 13, 5, 0xa9e3e905);
    d = GG(d, a, b, c, 2, 9, 0xfcefa3f8);
    c = GG(c, d, a, b, 7, 14, 0x676f02d9);
    b = GG(b, c, d, a, 12, 20, 0x8d2a4c8a);

    //Round 3
    a = HH(a, b, c, d, 5, 4, 0xfffa3942);
    d = HH(d, a, b, c, 8, 11, 0x8771f681);
    c = HH(c, d, a, b, 11, 16, 0x6d9d6122);
    b = HH(b, c, d, a, 14, 23, 0xfde5380c);

    a = HH(a, b, c, d, 1, 4, 0xa4beea44);
    d = HH(d, a, b, c, 4, 11, 0x4bdecfa9);
    c = HH(c, d, a, b, 7, 16, 0xf6bb4b60);
    b = HH(b, c, d, a, 10, 23, 0xbebfbc70);

    a = HH(a, b, c, d, 13, 4, 0x289b7ec6);
    d = HH(d, a, b, c, 0, 11, 0xeaa127fa);
    c = HH(c, d, a, b, 3, 16, 0xd4ef3085);
    b = HH(b, c, d, a, 6, 23, 0x4881d05);

    a = HH(a, b, c, d, 9, 4, 0xd9d4d039);
    d = HH(d, a, b, c, 12, 11, 0xe6db99e5);
    c = HH(c, d, a, b, 15, 16, 0x1fa27cf8);
    b = HH(b, c, d, a, 2, 23, 0xc4ac5665);

    //Round 4
    a = II(a, b, c, d, 0, 6, 0xf4292244);
    d = II(d, a, b, c, 7, 10, 0x432aff97);
    c = II(c, d, a, b, 14, 15, 0xab9423a7);
    b = II(b, c, d, a, 5, 21, 0xfc93a039);

    a = II(a, b, c, d, 12, 6, 0x655b59c3);
    d = II(d, a, b, c, 3, 10, 0x8f0ccc92);
    c = II(c, d, a, b, 10, 15, 0xffeff47d);
    b = II(b, c, d, a, 1, 21, 0x85845dd1);

    a = II(a, b, c, d, 8, 6, 0x6fa87e4f);
    d = II(d, a, b, c, 15, 10, 0xfe2ce6e0);
    c = II(c, d, a, b, 6, 15, 0xa3014314);
    b = II(b, c, d, a, 13, 21, 0x4e0811a1);

    a = II(a, b, c, d, 4, 6, 0xf7537e82);
    d = II(d, a, b, c, 11, 10, 0xbd3af235);
    c = II(c, d, a, b, 2, 15, 0x2ad7d2bb);
    b = II(b, c, d, a, 9, 21, 0xeb86d391);

    mdbuf0 += a;
    mdbuf1 += b;
    mdbuf2 += c;
    mdbuf3 += d;
  }

  private static final boolean DUMMY = Licensed.VALID;
}
