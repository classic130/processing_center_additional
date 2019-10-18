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
import java.security.AlgorithmParameters;
import java.security.Key;
import java.security.InvalidKeyException;
import java.security.spec.AlgorithmParameterSpec;
import javax.crypto.spec.RC2ParameterSpec;
import javax.crypto.Cipher;

/**
 * <p>Implements the RC2 block cipher algorithm from RSA.
 *
 * @see com.dstc.security.provider.BlockCipher
 * @see javax.crypto.Cipher
 *
 * @version 0.98, 98/07/01
 * @author Ming Yung
 */
public final class RC2 extends BlockCipher 
{
  private short K[]; //64 16-bit words
  private int effectiveKeyBits = 128; //can be overridden by RC2ParamSpec

  public RC2() 
  {
    blockSize = 8;
  }

  protected void initialize(Key key, AlgorithmParameterSpec params)
    throws IllegalStateException, InvalidKeyException 
  {
    if (!key.getAlgorithm().equals("RC2")) 
    {
      throw new InvalidKeyException ("Not an RC2 Key");
    }

    if (params instanceof RC2ParameterSpec)
    {
      this.effectiveKeyBits = 
        ((RC2ParameterSpec)params).getEffectiveKeyBits();

      byte iv[] = ((RC2ParameterSpec)params).getIV();
      
      if (iv != null) IV = iv;
    }

    try
    {
      this.algParams = AlgorithmParameters.getInstance("RC2/CBC");
      this.algParams.init(new RC2ParameterSpec(this.effectiveKeyBits, IV));
    }
    catch (Exception e)
    {
      //ignore
    }

    //Key Expansion
    byte keyBytes[] = key.getEncoded();
    int keyLength = keyBytes.length;
    byte L[] = new byte[128];
    System.arraycopy (keyBytes, 0, L, 0, keyLength);

    int T8 = (effectiveKeyBits + 7)/8;
    int Tm = 255 % (1 << (8 + effectiveKeyBits - 8*T8));

    for (int i=keyLength; i< 128; i++) 
    {
      L[i] = Pi[(L[i-1] + L[i-keyLength] & 0xff)];
    }

    L[128-T8] = Pi[(L[128-T8] & Tm)];

    for (int i=127 - T8; i >= 0; i--) 
    {
      L[i] = Pi[(L[i+1] ^ L[i+T8]) & 0xff];
    }

    K = bytesToShorts (L, 0, 128);
  }

  protected void encryptBlock(byte in[], byte out[]) 
  {
    //short R[] = bytesToShorts(in, 0, blockSize);
    short R0 = (short) (((in[1] & 0xff) << 8) | (in[0] & 0xff)) ;
    short R1 = (short) (((in[3] & 0xff) << 8) | (in[2] & 0xff)) ;
    short R2 = (short) (((in[5] & 0xff) << 8) | (in[4] & 0xff)) ;
    short R3 = (short) (((in[7] & 0xff) << 8) | (in[6] & 0xff)) ;
    int next = 0;

    for (int i=0; i<16; i++) 
    {
      //mixE (R,next);
      int tmp;
      tmp = R0 + K[next] + (R3 & R2) + ((~R3) & R1);
      R0 = (short) ((tmp << 1) | (tmp >>> 15 & 1));
      tmp = R1 + K[next+1] + (R0 & R3) + ((~R0) & R2);
      R1 = (short) ((tmp << 2) | (tmp >>> 14 & 3));
      tmp = R2 + K[next+2] + (R1 & R0) + ((~R1) & R3);
      R2 = (short) ((tmp << 3) | (tmp >>> 13 & 7));
      tmp = R3 + K[next+3] + (R2 & R1) + ((~R2) & R0);
      R3 = (short) ((tmp << 5) | (tmp >>> 11 & 31));
      //if (i==4 || i==10) mashE (R);
      if (i==4 || i==10) 
      {
        R0 += K[R3 & 63];
        R1 += K[R0 & 63];
        R2 += K[R1 & 63];
        R3 += K[R2 & 63];
      }
      next += 4;
    }
    //shortsToBytes(R, out);
    out[1] = (byte) (R0 >>> 8);
    out[0] = (byte) R0;
    out[3] = (byte) (R1 >>> 8);
    out[2] = (byte) R1;
    out[5] = (byte) (R2 >>> 8);
    out[4] = (byte) R2;
    out[7] = (byte) (R3 >>> 8);
    out[6] = (byte) R3;
  }

  protected void decryptBlock(byte in[], byte out[]) 
  {
    //short R[] = bytesToShorts(in, 0, blockSize);
    short R0 = (short) (((in[1] & 0xff) << 8) | (in[0] & 0xff)) ;
    short R1 = (short) (((in[3] & 0xff) << 8) | (in[2] & 0xff)) ;
    short R2 = (short) (((in[5] & 0xff) << 8) | (in[4] & 0xff)) ;
    short R3 = (short) (((in[7] & 0xff) << 8) | (in[6] & 0xff)) ;
    int next = 63;

    for (int i=15; i>=0; i--) 
    {
      //mixD (R,next);
      int tmp;
      tmp = (R3 >>> 5 & 0x7ff) + (R3 << 11);
      R3 = (short) (tmp - K[next] - (R2 & R1) - ((~R2) & R0) );
      tmp = (R2 >>> 3 & 0x1fff) + (R2 << 13);
      R2 = (short) (tmp - K[next-1] - (R1 & R0) - ((~R1) & R3) );
      tmp = (R1 >>> 2 & 0x3fff) + (R1 << 14);
      R1 = (short) (tmp - K[next-2] - (R0 & R3) - ((~R0) & R2) );
      tmp = (R0 >>> 1 & 0x7fff) + (R0 << 15);
      R0 = (short) (tmp - K[next-3] - (R3 & R2) - ((~R3) & R1) );

      //if (i==5 || i==11) mashD (R);
      if (i==5 || i==11) 
      {
        R3 -= K[R2 & 63];
        R2 -= K[R1 & 63];
        R1 -= K[R0 & 63];
        R0 -= K[R3 & 63];
      }
      next -= 4;
    }
    //shortsToBytes(R, out);
    out[1] = (byte) (R0 >>> 8);
    out[0] = (byte) R0;
    out[3] = (byte) (R1 >>> 8);
    out[2] = (byte) R1;
    out[5] = (byte) (R2 >>> 8);
    out[4] = (byte) R2;
    out[7] = (byte) (R3 >>> 8);
    out[6] = (byte) R3;
  }

  private static final short[] bytesToShorts (byte bytes[], int offset, 
                                              int length) 
  {
    //Convert every 2 bytes to a short
    short retval[] = new short[(length + 1)/2];
    int r = retval.length;
    for (int j=0; j < r; j++) 
    {
      retval[j] = (short) ( ((bytes[2*j+1 + offset] & 0xff) << 8)
                  +  (bytes[2*j + offset] & 0xff) );
    }

    return retval;
  }

  private static final byte Pi[] = { //256 bytes
    (byte)0xd9, (byte)0x78, (byte)0xf9, (byte)0xc4,
    (byte)0x19, (byte)0xdd, (byte)0xb5, (byte)0xed,
    (byte)0x28, (byte)0xe9, (byte)0xfd, (byte)0x79,
    (byte)0x4a, (byte)0xa0, (byte)0xd8, (byte)0x9d,
    (byte)0xc6, (byte)0x7e, (byte)0x37, (byte)0x83,
    (byte)0x2b, (byte)0x76, (byte)0x53, (byte)0x8e,
    (byte)0x62, (byte)0x4c, (byte)0x64, (byte)0x88,
    (byte)0x44, (byte)0x8b, (byte)0xfb, (byte)0xa2,
    (byte)0x17, (byte)0x9a, (byte)0x59, (byte)0xf5,
    (byte)0x87, (byte)0xb3, (byte)0x4f, (byte)0x13,
    (byte)0x61, (byte)0x45, (byte)0x6d, (byte)0x8d,
    (byte)0x09, (byte)0x81, (byte)0x7d, (byte)0x32,
    (byte)0xbd, (byte)0x8f, (byte)0x40, (byte)0xeb,
    (byte)0x86, (byte)0xb7, (byte)0x7b, (byte)0x0b,
    (byte)0xf0, (byte)0x95, (byte)0x21, (byte)0x22,
    (byte)0x5c, (byte)0x6b, (byte)0x4e, (byte)0x82,
    (byte)0x54, (byte)0xd6, (byte)0x65, (byte)0x93,
    (byte)0xce, (byte)0x60, (byte)0xb2, (byte)0x1c,
    (byte)0x73, (byte)0x56, (byte)0xc0, (byte)0x14,
    (byte)0xa7, (byte)0x8c, (byte)0xf1, (byte)0xdc,
    (byte)0x12, (byte)0x75, (byte)0xca, (byte)0x1f,
    (byte)0x3b, (byte)0xbe, (byte)0xe4, (byte)0xd1,
    (byte)0x42, (byte)0x3d, (byte)0xd4, (byte)0x30,
    (byte)0xa3, (byte)0x3c, (byte)0xb6, (byte)0x26,
    (byte)0x6f, (byte)0xbf, (byte)0x0e, (byte)0xda,
    (byte)0x46, (byte)0x69, (byte)0x07, (byte)0x57,
    (byte)0x27, (byte)0xf2, (byte)0x1d, (byte)0x9b,
    (byte)0xbc, (byte)0x94, (byte)0x43, (byte)0x03,
    (byte)0xf8, (byte)0x11, (byte)0xc7, (byte)0xf6,
    (byte)0x90, (byte)0xef, (byte)0x3e, (byte)0xe7,
    (byte)0x06, (byte)0xc3, (byte)0xd5, (byte)0x2f,
    (byte)0xc8, (byte)0x66, (byte)0x1e, (byte)0xd7,
    (byte)0x08, (byte)0xe8, (byte)0xea, (byte)0xde,
    (byte)0x80, (byte)0x52, (byte)0xee, (byte)0xf7,
    (byte)0x84, (byte)0xaa, (byte)0x72, (byte)0xac,
    (byte)0x35, (byte)0x4d, (byte)0x6a, (byte)0x2a,
    (byte)0x96, (byte)0x1a, (byte)0xd2, (byte)0x71,
    (byte)0x5a, (byte)0x15, (byte)0x49, (byte)0x74,
    (byte)0x4b, (byte)0x9f, (byte)0xd0, (byte)0x5e,
    (byte)0x04, (byte)0x18, (byte)0xa4, (byte)0xec,
    (byte)0xc2, (byte)0xe0, (byte)0x41, (byte)0x6e,
    (byte)0x0f, (byte)0x51, (byte)0xcb, (byte)0xcc,
    (byte)0x24, (byte)0x91, (byte)0xaf, (byte)0x50,
    (byte)0xa1, (byte)0xf4, (byte)0x70, (byte)0x39,
    (byte)0x99, (byte)0x7c, (byte)0x3a, (byte)0x85,
    (byte)0x23, (byte)0xb8, (byte)0xb4, (byte)0x7a,
    (byte)0xfc, (byte)0x02, (byte)0x36, (byte)0x5b,
    (byte)0x25, (byte)0x55, (byte)0x97, (byte)0x31,
    (byte)0x2d, (byte)0x5d, (byte)0xfa, (byte)0x98,
    (byte)0xe3, (byte)0x8a, (byte)0x92, (byte)0xae,
    (byte)0x05, (byte)0xdf, (byte)0x29, (byte)0x10,
    (byte)0x67, (byte)0x6c, (byte)0xba, (byte)0xc9,
    (byte)0xd3, (byte)0x00, (byte)0xe6, (byte)0xcf,
    (byte)0xe1, (byte)0x9e, (byte)0xa8, (byte)0x2c,
    (byte)0x63, (byte)0x16, (byte)0x01, (byte)0x3f,
    (byte)0x58, (byte)0xe2, (byte)0x89, (byte)0xa9,
    (byte)0x0d, (byte)0x38, (byte)0x34, (byte)0x1b,
    (byte)0xab, (byte)0x33, (byte)0xff, (byte)0xb0,
    (byte)0xbb, (byte)0x48, (byte)0x0c, (byte)0x5f,
    (byte)0xb9, (byte)0xb1, (byte)0xcd, (byte)0x2e,
    (byte)0xc5, (byte)0xf3, (byte)0xdb, (byte)0x47,
    (byte)0xe5, (byte)0xa5, (byte)0x9c, (byte)0x77,
    (byte)0x0a, (byte)0xa6, (byte)0x20, (byte)0x68,
    (byte)0xfe, (byte)0x7f, (byte)0xc1, (byte)0xad
  };
}
