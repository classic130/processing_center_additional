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
 * <p>Implements the SHA-1 Message Digest algorithm.
 *
 * @see java.security.MessageDigest
 *
 * @version 0.98, 98/07/01
 * @author Shelina Gorain
 * @author Ming Yung
 */
public final class SHA1 extends MessageDigestSpi implements Cloneable, Licensed
{
  private static final int DIGEST_LENGTH = 20;
  private static final int BLOCKSIZE = 64; //in bytes

  private byte[] inputBuffer = new byte[BLOCKSIZE];
  private int inputBufferOffset;
  private int mdBuffer0;
  private int mdBuffer1;
  private int mdBuffer2;
  private int mdBuffer3;
  private int mdBuffer4;
  private int plainTextLength;
  private int[] seq = new int[80];

  public SHA1() 
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
      inputBuffer[inputBufferOffset+i] = (byte)((lb >>> 8*(7-i)) & 0xff);
    }

    //Last block to doDecode
    doDecodeBlock();

    byte retval[] = Bytes.intsToBytesMSB(new int[]{mdBuffer0,
                    mdBuffer1, mdBuffer2, mdBuffer3, mdBuffer4});
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
    mdBuffer0 =  0x67452301;
    mdBuffer1 =  0xefcdab89;
    mdBuffer2 =  0x98badcfe;
    mdBuffer3 =  0x10325476;
    mdBuffer4 =  0xc3d2e1f0;
    plainTextLength = 0;
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
    SHA1 retval = new SHA1();
    retval.inputBufferOffset = this.inputBufferOffset;
    retval.plainTextLength = this.plainTextLength;
    retval.mdBuffer0 = this.mdBuffer0;
    retval.mdBuffer1 = this.mdBuffer1;
    retval.mdBuffer2 = this.mdBuffer2;
    retval.mdBuffer3 = this.mdBuffer3;
    retval.mdBuffer4 = this.mdBuffer4;
    System.arraycopy(this.inputBuffer, 0, retval.inputBuffer, 0, BLOCKSIZE);
    return retval;
  }

  private void doDecodeBlock() 
  {
    expandBlock(inputBuffer);
    int a = mdBuffer0;
    int b = mdBuffer1;
    int c = mdBuffer2;
    int d = mdBuffer3;
    int e = mdBuffer4;

    for(int i=0; i<20; i++)
    {
     int temp = ((a << 5) | (a >>> 27)) + ( (b & c) | ((~b) & d) ) + e 
              + seq[i] + 0x5A827999;
     e = d;
     d = c;
     c = (b << 30) | (b >>> 2);
     b = a;
     a = temp;
    }

    for(int i=20; i<40; i++)
    {
     int temp = ((a << 5) | (a >>> 27)) + 
             ((b ^ c ^ d)) + e + seq[i] + 0x6ED9EBA1;
     e = d;
     d = c;
     c = (b << 30) | (b >>> 2);
     b = a;
     a = temp;
    }
    
    for(int i=40; i<60; i++)
    {
     int temp = ((a << 5) | (a >>> 27)) + ((b & c) | (b & d) | (c & d)) + 
                       e + seq[i] + 0x8F1BBCDC;
     e = d;
     d = c;
     c = (b << 30) | (b >>> 2);
     b = a;
     a = temp;
    }
    
    for(int i=60; i<80; i++)
    {
     int temp = ((a << 5) | (a >>> 27)) + 
             ((b ^ c ^ d)) + e + seq[i] + 0xCA62C1D6;
     e = d;
     d = c;
     c = (b << 30) | (b >>> 2);
     b = a;
     a = temp;
    }

      mdBuffer0 += a;
      mdBuffer1 += b;
      mdBuffer2 += c;
      mdBuffer3 += d;
      mdBuffer4 += e;
  }
  
  private void expandBlock(byte b[]) 
  {
    //int[] block = Bytes.bytesMSBToInts(b, 0, BLOCKSIZE);
    //System.arraycopy(block, 0, seq, 0, 16);

    int off = 0;
    int s_off = 0;
    while (off < BLOCKSIZE)
    {
        seq[s_off++] = ((b[off] & 0xff) << 24) | ((b[off + 1] & 0xff)<< 16) |
          ((b[off +2] & 0xff) << 8) | (b[off +3] & 0xff) ;
        off += 4;
    }


    for (int t=16; t<80; t++) 
    {
      int s = seq[t-3] ^ seq[t-8] ^ seq[t-14] ^ seq[t-16];
      seq[t] = (s << 1) | (s >>> 31) ;
    }
  }

  private static final boolean DUMMY = Licensed.VALID;
}
