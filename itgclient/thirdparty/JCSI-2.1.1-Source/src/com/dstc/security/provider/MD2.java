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
import java.security.*;

/**
 * <p>Implements the MD2 Message Digest algorithm from RSA.
 *
 * @see java.security.MessageDigest
 *
 * @version 0.98, 98/07/01
 * @author Ming Yung
 */
public final class MD2 extends MessageDigestSpi
{
  private static final int DIGEST_LENGTH = 16;
  private static final int BLOCKSIZE = 16; //in bytes
  private byte inputBuffer[];
  private int inputBufferOffset;
  private byte mdBuffer[];
  private int plainTextLength;
  private byte checksum[];
  private byte dummy[];

  public MD2 () 
  {
    //Initialize
    inputBuffer = new byte[BLOCKSIZE];
    inputBufferOffset = 0;
    plainTextLength = 0;
    mdBuffer = new byte[48];
    checksum = new byte[16];
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


  protected byte[] engineDigest () 
  {
    int extra = 16 - ( plainTextLength & 0xf );

    //NB: There are always two blocks to encrypt

    //First block: Add padding
    for (int i=0; i<extra; i++) 
    {
      inputBuffer[inputBufferOffset + i] = (byte) extra ;
    }
    copyIntoMDBuffer (inputBuffer, mdBuffer, checksum);
    doDecodeBlock (mdBuffer);
      
    //Last block to doDecode
    copyIntoMDBuffer (checksum, mdBuffer, checksum);
    doDecodeBlock (mdBuffer);
   
    byte retval[] = new byte[16];
    for (int i=0; i<16; i++) 
    {
      retval[i] = mdBuffer[i];
    }

    doReset ();
    return retval;
  }

  protected void engineReset () 
  {
    doReset ();
  }

  private final void doReset () 
  {
    inputBufferOffset = 0;
    plainTextLength = 0;
    mdBuffer = new byte[48];
    checksum = new byte[16];
  }

  protected int engineGetDigestLength()
  {
    return DIGEST_LENGTH;
  }

  protected void engineUpdate (byte input)
  {
    byte in[] = new byte[1];
    in[0] = input;
    engineUpdate(in, 0, 1);
  }

  protected void engineUpdate (byte input[], int inputOffset, 
                               int length) 
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
        copyIntoMDBuffer (inputBuffer, mdBuffer, checksum);
        doDecodeBlock (mdBuffer);
        left -= len;
        inputBufferOffset = 0;
        inputUsed += len;
      } 
      else 
      {
        //Buffer the remaining input
        System.arraycopy (input, inputUsed + inputOffset, inputBuffer,
                          inputBufferOffset, left);
        inputBufferOffset += left;
        break;
      }
    }
    plainTextLength += length;
  }

  private static void copyIntoMDBuffer(byte next[], byte buf[],
                                       byte checksum[]) 
  {
    int t = checksum[15];

    for (int j=0; j<16; j++) 
    {
      buf[j+16] = next[j];
      buf[j+32] = (byte)(buf[j] ^ buf[j+16]);
    }
    //Update checksum

    for (int j=0; j < 16; j++) 
    {
      t = checksum[j] ^= permutation [(next[j] ^ t) & 0xff];
    }

  }

  private static void doDecodeBlock (byte inout[]) 
  {
    int t = 0;
    for (int j=0; j<18; j++) 
    {
      for (int k=0; k < 48; k++) 
      {
        t = inout[k] ^= permutation[t & 0xff];
      }
      t = ((t + j) & 0xff);
    }
  }

  private static byte permutation [] = {
    41, 46, 67, -55, -94, -40, 124, 1, 61, 54, 84, -95, -20, -16, 6,
    19, 98, -89, 5, -13, -64, -57, 115, -116, -104, -109, 43, -39, -68, 76,
    -126, -54, 30, -101, 87, 60, -3, -44, -32, 22, 103, 66, 111, 24, -118,
    23, -27, 18, -66, 78, -60, -42, -38, -98, -34, 73, -96, -5, -11, -114,
    -69, 47, -18, 122, -87, 104, 121, -111, 21, -78, 7, 63, -108, -62, 16,
    -119, 11, 34, 95, 33, -128, 127, 93, -102, 90, -112, 50, 39, 53, 62,
    -52, -25, -65, -9, -105, 3, -1, 25, 48, -77, 72, -91, -75, -47, -41,
    94, -110, 42, -84, 86, -86, -58, 79, -72, 56, -46, -106, -92, 125, -74,
    118, -4, 107, -30, -100, 116, 4, -15, 69, -99, 112, 89, 100, 113, -121,
    32, -122, 91, -49, 101, -26, 45, -88, 2, 27, 96, 37, -83, -82, -80,
    -71, -10, 28, 70, 97, 105, 52, 64, 126, 15, 85, 71, -93, 35, -35,
    81, -81, 58, -61, 92, -7, -50, -70, -59, -22, 38, 44, 83, 13, 110,
    -123, 40, -124, 9, -45, -33, -51, -12, 65, -127, 77, 82, 106, -36, 55,
    -56, 108, -63, -85, -6, 36, -31, 123, 8, 12, -67, -79, 74, 120, -120,
    -107, -117, -29, 99, -24, 109, -23, -53, -43, -2, 59, 0, 29, 57, -14,
    -17, -73, 14, 102, 88, -48, -28, -90, 119, 114, -8, -21, 117, 75, 10,
    49, 68, 80, -76, -113, -19, 31, 26, -37, -103, -115, 51, -97, 17, -125,
    20
  };

  private static final boolean DUMMY = Licensed.VALID;
}
