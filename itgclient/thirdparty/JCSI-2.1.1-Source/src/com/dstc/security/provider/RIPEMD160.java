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

import java.security.DigestException;
import java.security.MessageDigestSpi;

import com.dstc.security.util.Bytes;

/**
 * <p>Implements the RIPE MD-160 Message Digest algorithm.
 *
 * @see java.security.MessageDigest
 *
 * @version 0.98, 98/07/01
 * @author Ming Yung
 */
public final class RIPEMD160 extends MessageDigestSpi 
  implements Cloneable, Licensed
{
  private static final int DIGEST_LENGTH = 20;
  private static final int BLOCKSIZE = 64; //in bytes
  private byte[] inputBuffer = new byte[BLOCKSIZE];
  private int inputBufferOffset;
  private int[] mdBuffer = new int[5];
  private int plainTextLength;
  private int[] x = new int[BLOCKSIZE >> 2];
  private int first[] = new int[5];
  private int second[] = new int[5];

  public RIPEMD160() 
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
        inputBuffer[inputBufferOffset + i] = 0x00 ;
      }
      doDecodeBlock ();
      inputBufferOffset = -start;
    }
      
    for (int i=start; i<extra; i++) 
    {
      inputBuffer[inputBufferOffset + i] = 0x00 ;
    }
    inputBufferOffset += extra;

    //Step 2: Append length in bits
    long lb = (long) (plainTextLength*8);
    for (int i=0; i<8; i++) 
    {
      inputBuffer[inputBufferOffset+i] = (byte)((lb >>> 8*i) & 0xff);
    }

   //Last block to doDecode
   doDecodeBlock ();
   
   byte retval[] = Bytes.intsToBytesLSB(mdBuffer);
   doReset ();
   return retval;
  }

  protected void engineReset() 
  {
    doReset();
  }

  protected int engineGetDigestLength()
  {
    return DIGEST_LENGTH;
  }

  private void doReset() 
  {
    inputBufferOffset = 0;
    plainTextLength = 0;
    mdBuffer[0] = 0x67452301;
    mdBuffer[1] = 0xefcdab89;
    mdBuffer[2] = 0x98badcfe;
    mdBuffer[3] = 0x10325476;
    mdBuffer[4] = 0xc3d2e1f0;
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
        System.arraycopy (input, inputUsed + inputOffset, inputBuffer,
                          inputBufferOffset, len);
        doDecodeBlock ();
        left -= len;
        inputBufferOffset = 0;
        inputUsed += len;
      } 
      else 
      {
        //Buffer the remaining input
        System.arraycopy (input, inputUsed + inputOffset, inputBuffer,
                          0, left);
        inputBufferOffset += left;
        break;
      }
    }
    plainTextLength += length;
  }

  public Object clone() throws CloneNotSupportedException
  {
    RIPEMD160 retval = new RIPEMD160();
    retval.inputBufferOffset = this.inputBufferOffset;
    retval.plainTextLength = this.plainTextLength;
    System.arraycopy(this.mdBuffer, 0, retval.mdBuffer, 0, 5);
    System.arraycopy(this.inputBuffer, 0, retval.inputBuffer, 0, BLOCKSIZE);
    return retval;
  }

  private void FF (int buf[], int a, int b, int c, 
                          int d, int e, int i, int s) 
  {
    int t = buf[a] + (buf[b] ^ buf[c] ^ buf[d]) + x[i];
    buf[a] = (t << s | t >>> (32 -s)) + buf[e];
    buf[c] = (buf[c] << 10 | buf[c] >>> 22);
  }

  private void GG (int mag, int buf[], int a, int b, int c, 
                          int d, int e, int i, int s) 
  {
    int t = buf[a] + ((buf[b] & buf[c] ) | (~buf[b] & buf[d])) + x[i] + mag;
    buf[a] = (t << s | t >>> (32 -s)) + buf[e];
    buf[c] = (buf[c] << 10 | buf[c] >>> 22);
  }

  private void HH (int mag, int buf[], int a, int b, int c, 
                          int d, int e, int i, int s) 
  {
    int t = buf[a] + ((buf[b] | ~buf[c]) ^ buf[d]) + x[i] + mag;
    buf[a] = (t << s | t >>> (32 -s)) + buf[e];
    buf[c] = (buf[c] << 10 | buf[c] >>> 22);
  }

  private void II (int mag, int buf[], int a, int b, int c, 
                          int d, int e, int i, int s) 
  {
    int t = buf[a] + ((buf[b] & buf[d]) | (buf[c] & ~buf[d])) + x[i] + mag;
    buf[a] = (t << s | t >>> (32 -s)) + buf[e];
    buf[c] = (buf[c] << 10 | buf[c] >>> 22);
  }

  private void JJ (int mag, int buf[], int a, int b, int c, 
                          int d, int e, int i, int s) 
  {
    int t = buf[a] + (buf[b] ^ (buf[c] | ~buf[d])) + x[i] + mag;
    buf[a] = (t << s | t >>> (32 -s)) + buf[e];
    buf[c] = (buf[c] << 10 | buf[c] >>> 22);
  }

  private void doDecodeBlock () 
  {
    int off = 0;
    int s_off = 0;
    while (off < BLOCKSIZE)
    {
        x[s_off++] = ((inputBuffer[off+3] & 0xff) << 24) |
           ((inputBuffer[off + 2] & 0xff)<< 16) |
          ((inputBuffer[off +1] & 0xff) << 8) | (inputBuffer[off] & 0xff) ;
        off += 4;
    }

    System.arraycopy (mdBuffer, 0, first, 0, 5);
    System.arraycopy (mdBuffer, 0, second, 0, 5);

    /* round 1 */
    FF (first, 0, 1, 2, 3, 4,  0, 11);
    FF (first, 4, 0, 1, 2, 3,  1, 14);
    FF (first, 3, 4, 0, 1, 2,  2, 15);
    FF (first, 2, 3, 4, 0, 1,  3, 12);
    FF (first, 1, 2, 3, 4, 0,  4,  5);
    FF (first, 0, 1, 2, 3, 4,  5,  8);
    FF (first, 4, 0, 1, 2, 3,  6,  7);
    FF (first, 3, 4, 0, 1, 2,  7,  9);
    FF (first, 2, 3, 4, 0, 1,  8, 11);
    FF (first, 1, 2, 3, 4, 0,  9, 13);
    FF (first, 0, 1, 2, 3, 4, 10, 14);
    FF (first, 4, 0, 1, 2, 3, 11, 15);
    FF (first, 3, 4, 0, 1, 2, 12,  6);
    FF (first, 2, 3, 4, 0, 1, 13,  7);
    FF (first, 1, 2, 3, 4, 0, 14,  9);
    FF (first, 0, 1, 2, 3, 4, 15,  8);
 
    /* round 2 */
    GG (0x5a827999, first, 4, 0, 1, 2, 3,  7,  7);
    GG (0x5a827999, first, 3, 4, 0, 1, 2,  4,  6);
    GG (0x5a827999, first, 2, 3, 4, 0, 1, 13,  8);
    GG (0x5a827999, first, 1, 2, 3, 4, 0,  1, 13);
    GG (0x5a827999, first, 0, 1, 2, 3, 4, 10, 11);
    GG (0x5a827999, first, 4, 0, 1, 2, 3,  6,  9);
    GG (0x5a827999, first, 3, 4, 0, 1, 2, 15,  7);
    GG (0x5a827999, first, 2, 3, 4, 0, 1,  3, 15);
    GG (0x5a827999, first, 1, 2, 3, 4, 0, 12,  7);
    GG (0x5a827999, first, 0, 1, 2, 3, 4,  0, 12);
    GG (0x5a827999, first, 4, 0, 1, 2, 3,  9, 15);
    GG (0x5a827999, first, 3, 4, 0, 1, 2,  5,  9);
    GG (0x5a827999, first, 2, 3, 4, 0, 1,  2, 11);
    GG (0x5a827999, first, 1, 2, 3, 4, 0, 14,  7);
    GG (0x5a827999, first, 0, 1, 2, 3, 4, 11, 13);
    GG (0x5a827999, first, 4, 0, 1, 2, 3,  8, 12);
 
    /* round 3 */
    HH (0x6ed9eba1, first, 3, 4, 0, 1, 2,  3, 11);
    HH (0x6ed9eba1, first, 2, 3, 4, 0, 1, 10, 13);
    HH (0x6ed9eba1, first, 1, 2, 3, 4, 0, 14,  6);
    HH (0x6ed9eba1, first, 0, 1, 2, 3, 4,  4,  7);
    HH (0x6ed9eba1, first, 4, 0, 1, 2, 3,  9, 14);
    HH (0x6ed9eba1, first, 3, 4, 0, 1, 2, 15,  9);
    HH (0x6ed9eba1, first, 2, 3, 4, 0, 1,  8, 13);
    HH (0x6ed9eba1, first, 1, 2, 3, 4, 0,  1, 15);
    HH (0x6ed9eba1, first, 0, 1, 2, 3, 4,  2, 14);
    HH (0x6ed9eba1, first, 4, 0, 1, 2, 3,  7,  8);
    HH (0x6ed9eba1, first, 3, 4, 0, 1, 2,  0, 13);
    HH (0x6ed9eba1, first, 2, 3, 4, 0, 1,  6,  6);
    HH (0x6ed9eba1, first, 1, 2, 3, 4, 0, 13,  5);
    HH (0x6ed9eba1, first, 0, 1, 2, 3, 4, 11, 12);
    HH (0x6ed9eba1, first, 4, 0, 1, 2, 3,  5,  7);
    HH (0x6ed9eba1, first, 3, 4, 0, 1, 2, 12,  5);
 
    /* round 4 */
    II (0x8f1bbcdc, first, 2, 3, 4, 0, 1,  1, 11);
    II (0x8f1bbcdc, first, 1, 2, 3, 4, 0,  9, 12);
    II (0x8f1bbcdc, first, 0, 1, 2, 3, 4, 11, 14);
    II (0x8f1bbcdc, first, 4, 0, 1, 2, 3, 10, 15);
    II (0x8f1bbcdc, first, 3, 4, 0, 1, 2,  0, 14);
    II (0x8f1bbcdc, first, 2, 3, 4, 0, 1,  8, 15);
    II (0x8f1bbcdc, first, 1, 2, 3, 4, 0, 12,  9);
    II (0x8f1bbcdc, first, 0, 1, 2, 3, 4,  4,  8);
    II (0x8f1bbcdc, first, 4, 0, 1, 2, 3, 13,  9);
    II (0x8f1bbcdc, first, 3, 4, 0, 1, 2,  3, 14);
    II (0x8f1bbcdc, first, 2, 3, 4, 0, 1,  7,  5);
    II (0x8f1bbcdc, first, 1, 2, 3, 4, 0, 15,  6);
    II (0x8f1bbcdc, first, 0, 1, 2, 3, 4, 14,  8);
    II (0x8f1bbcdc, first, 4, 0, 1, 2, 3,  5,  6);
    II (0x8f1bbcdc, first, 3, 4, 0, 1, 2,  6,  5);
    II (0x8f1bbcdc, first, 2, 3, 4, 0, 1,  2, 12);
 
    /* round 5 */
    JJ (0xa953fd4e, first, 1, 2, 3, 4, 0,  4,  9);
    JJ (0xa953fd4e, first, 0, 1, 2, 3, 4,  0, 15);
    JJ (0xa953fd4e, first, 4, 0, 1, 2, 3,  5,  5);
    JJ (0xa953fd4e, first, 3, 4, 0, 1, 2,  9, 11);
    JJ (0xa953fd4e, first, 2, 3, 4, 0, 1,  7,  6);
    JJ (0xa953fd4e, first, 1, 2, 3, 4, 0, 12,  8);
    JJ (0xa953fd4e, first, 0, 1, 2, 3, 4,  2, 13);
    JJ (0xa953fd4e, first, 4, 0, 1, 2, 3, 10, 12);
    JJ (0xa953fd4e, first, 3, 4, 0, 1, 2, 14,  5);
    JJ (0xa953fd4e, first, 2, 3, 4, 0, 1,  1, 12);
    JJ (0xa953fd4e, first, 1, 2, 3, 4, 0,  3, 13);
    JJ (0xa953fd4e, first, 0, 1, 2, 3, 4,  8, 14);
    JJ (0xa953fd4e, first, 4, 0, 1, 2, 3, 11, 11);
    JJ (0xa953fd4e, first, 3, 4, 0, 1, 2,  6,  8);
    JJ (0xa953fd4e, first, 2, 3, 4, 0, 1, 15,  5);
    JJ (0xa953fd4e, first, 1, 2, 3, 4, 0, 13,  6);
 
    /* parallel round 1 */
    JJ (0x50a28be6, second, 0, 1, 2, 3, 4,  5,  8);
    JJ (0x50a28be6, second, 4, 0, 1, 2, 3, 14,  9);
    JJ (0x50a28be6, second, 3, 4, 0, 1, 2,  7,  9);
    JJ (0x50a28be6, second, 2, 3, 4, 0, 1,  0, 11);
    JJ (0x50a28be6, second, 1, 2, 3, 4, 0,  9, 13);
    JJ (0x50a28be6, second, 0, 1, 2, 3, 4,  2, 15);
    JJ (0x50a28be6, second, 4, 0, 1, 2, 3, 11, 15);
    JJ (0x50a28be6, second, 3, 4, 0, 1, 2,  4,  5);
    JJ (0x50a28be6, second, 2, 3, 4, 0, 1, 13,  7);
    JJ (0x50a28be6, second, 1, 2, 3, 4, 0,  6,  7);
    JJ (0x50a28be6, second, 0, 1, 2, 3, 4, 15,  8);
    JJ (0x50a28be6, second, 4, 0, 1, 2, 3,  8, 11);
    JJ (0x50a28be6, second, 3, 4, 0, 1, 2,  1, 14);
    JJ (0x50a28be6, second, 2, 3, 4, 0, 1, 10, 14);
    JJ (0x50a28be6, second, 1, 2, 3, 4, 0,  3, 12);
    JJ (0x50a28be6, second, 0, 1, 2, 3, 4, 12,  6);
 
    /* parallel round 2 */
    II (0x5c4dd124, second, 4, 0, 1, 2, 3,  6,  9);
    II (0x5c4dd124, second, 3, 4, 0, 1, 2, 11, 13);
    II (0x5c4dd124, second, 2, 3, 4, 0, 1,  3, 15);
    II (0x5c4dd124, second, 1, 2, 3, 4, 0,  7,  7);
    II (0x5c4dd124, second, 0, 1, 2, 3, 4,  0, 12);
    II (0x5c4dd124, second, 4, 0, 1, 2, 3, 13,  8);
    II (0x5c4dd124, second, 3, 4, 0, 1, 2,  5,  9);
    II (0x5c4dd124, second, 2, 3, 4, 0, 1, 10, 11);
    II (0x5c4dd124, second, 1, 2, 3, 4, 0, 14,  7);
    II (0x5c4dd124, second, 0, 1, 2, 3, 4, 15,  7);
    II (0x5c4dd124, second, 4, 0, 1, 2, 3,  8, 12);
    II (0x5c4dd124, second, 3, 4, 0, 1, 2, 12,  7);
    II (0x5c4dd124, second, 2, 3, 4, 0, 1,  4,  6);
    II (0x5c4dd124, second, 1, 2, 3, 4, 0,  9, 15);
    II (0x5c4dd124, second, 0, 1, 2, 3, 4,  1, 13);
    II (0x5c4dd124, second, 4, 0, 1, 2, 3,  2, 11);

    /* parallel round 3 */
    HH (0x6d703ef3, second, 3, 4, 0, 1, 2, 15,  9);
    HH (0x6d703ef3, second, 2, 3, 4, 0, 1,  5,  7);
    HH (0x6d703ef3, second, 1, 2, 3, 4, 0,  1, 15);
    HH (0x6d703ef3, second, 0, 1, 2, 3, 4,  3, 11);
    HH (0x6d703ef3, second, 4, 0, 1, 2, 3,  7,  8);
    HH (0x6d703ef3, second, 3, 4, 0, 1, 2, 14,  6);
    HH (0x6d703ef3, second, 2, 3, 4, 0, 1,  6,  6);
    HH (0x6d703ef3, second, 1, 2, 3, 4, 0,  9, 14);
    HH (0x6d703ef3, second, 0, 1, 2, 3, 4, 11, 12);
    HH (0x6d703ef3, second, 4, 0, 1, 2, 3,  8, 13);
    HH (0x6d703ef3, second, 3, 4, 0, 1, 2, 12,  5);
    HH (0x6d703ef3, second, 2, 3, 4, 0, 1,  2, 14);
    HH (0x6d703ef3, second, 1, 2, 3, 4, 0, 10, 13);
    HH (0x6d703ef3, second, 0, 1, 2, 3, 4,  0, 13);
    HH (0x6d703ef3, second, 4, 0, 1, 2, 3,  4,  7);
    HH (0x6d703ef3, second, 3, 4, 0, 1, 2, 13,  5);
 
    /* parallel round 4 */
    GG (0x7a6d76e9, second, 2, 3, 4, 0, 1,  8, 15);
    GG (0x7a6d76e9, second, 1, 2, 3, 4, 0,  6,  5);
    GG (0x7a6d76e9, second, 0, 1, 2, 3, 4,  4,  8);
    GG (0x7a6d76e9, second, 4, 0, 1, 2, 3,  1, 11);
    GG (0x7a6d76e9, second, 3, 4, 0, 1, 2,  3, 14);
    GG (0x7a6d76e9, second, 2, 3, 4, 0, 1, 11, 14);
    GG (0x7a6d76e9, second, 1, 2, 3, 4, 0, 15,  6);
    GG (0x7a6d76e9, second, 0, 1, 2, 3, 4,  0, 14);
    GG (0x7a6d76e9, second, 4, 0, 1, 2, 3,  5,  6);
    GG (0x7a6d76e9, second, 3, 4, 0, 1, 2, 12,  9);
    GG (0x7a6d76e9, second, 2, 3, 4, 0, 1,  2, 12);
    GG (0x7a6d76e9, second, 1, 2, 3, 4, 0, 13,  9);
    GG (0x7a6d76e9, second, 0, 1, 2, 3, 4,  9, 12);
    GG (0x7a6d76e9, second, 4, 0, 1, 2, 3,  7,  5);
    GG (0x7a6d76e9, second, 3, 4, 0, 1, 2, 10, 15);
    GG (0x7a6d76e9, second, 2, 3, 4, 0, 1, 14,  8);
 
    /* parallel round 5 */
    FF (second, 1, 2, 3, 4, 0, 12 ,  8);
    FF (second, 0, 1, 2, 3, 4, 15 ,  5);
    FF (second, 4, 0, 1, 2, 3, 10 , 12);
    FF (second, 3, 4, 0, 1, 2,  4 ,  9);
    FF (second, 2, 3, 4, 0, 1,  1 , 12);
    FF (second, 1, 2, 3, 4, 0,  5 ,  5);
    FF (second, 0, 1, 2, 3, 4,  8 , 14);
    FF (second, 4, 0, 1, 2, 3,  7 ,  6);
    FF (second, 3, 4, 0, 1, 2,  6 ,  8);
    FF (second, 2, 3, 4, 0, 1,  2 , 13);
    FF (second, 1, 2, 3, 4, 0, 13 ,  6);
    FF (second, 0, 1, 2, 3, 4, 14 ,  5);
    FF (second, 4, 0, 1, 2, 3,  0 , 15);
    FF (second, 3, 4, 0, 1, 2,  3 , 13);
    FF (second, 2, 3, 4, 0, 1,  9 , 11);
    FF (second, 1, 2, 3, 4, 0, 11 , 11);

    second[3] += first[2] + mdBuffer[1];
    mdBuffer[1] = mdBuffer[2] + first[3] + second[4];
    mdBuffer[2] = mdBuffer[3] + first[4] + second[0];
    mdBuffer[3] = mdBuffer[4] + first[0] + second[1];
    mdBuffer[4] = mdBuffer[0] + first[1] + second[2];
    mdBuffer[0] = second[3];
  }

  private static final boolean DUMMY = Licensed.VALID;
}
