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

import javax.crypto.Mac;
import javax.crypto.MacSpi;
import java.security.Key;
import java.security.MessageDigest;
import java.security.spec.AlgorithmParameterSpec;
import java.security.InvalidKeyException;
import java.security.InvalidAlgorithmParameterException;

/**
 * <p>An abstract class implementing the HMAC Message Authentication Code
 * algorithm to be used with any Message Digest algorithm.
 *
 * @see javax.crypto.Mac
 *
 * @version 0.98, 98/07/01
 * @author Ming Yung
 */
class HMACwithAnyMD extends MacSpi
{
  protected int L;
  protected MessageDigest md;

  private byte ipadByte = 0x36;
  private byte opadByte = 0x5c;
  private int B = 64;
  private byte keyXORIpad[];
  private byte keyXOROpad[];
  private MessageDigest md2;

  protected int engineGetMacLength()
  {
    return L;
  }

  protected void engineInit(Key key, AlgorithmParameterSpec params)
    throws InvalidKeyException, InvalidAlgorithmParameterException
  {
    if (params != null)
      throw new InvalidAlgorithmParameterException(
        "No params needed for this Mac");

    keyXORIpad = new byte[B];
    keyXOROpad = new byte[B];
    byte keyBytes[] = key.getEncoded();

    // Check that length of keyBytes <= 64. If not, Hash keyBytes
    // to get new keyBytes (see RFC 2104).
    //
    if (keyBytes.length > 64) {
        try {
            md2 = (MessageDigest) md.clone();
        }
        catch (CloneNotSupportedException e) {
            throw new RuntimeException("Clone not supported for this MD");
        }
        byte[] tmp = new byte[L];
        tmp = md2.digest(keyBytes);
        keyBytes = tmp;
    }

    System.arraycopy(keyBytes, 0, keyXORIpad, 0, keyBytes.length);
    System.arraycopy(keyBytes, 0, keyXOROpad, 0, keyBytes.length);

    for (int i=0; i<B; i++)
    {
      keyXORIpad[i] ^= ipadByte;
      keyXOROpad[i] ^= opadByte;
    }

    md.reset();
    md.update(keyXORIpad); 
  }

  protected void engineUpdate(byte input)
  {
    md.update(input);
  }

  protected void engineUpdate(byte[] input, int offset, int len)
  {
    md.update(input, offset, len);
  }

  protected byte[] engineDoFinal()
  {
    byte temp[] = md.digest();
    md.update(keyXOROpad);
    byte[] retval = md.digest(temp);

    md.update(keyXORIpad);
    return retval;
  }

  protected void engineReset()
  {
    md.reset();
    md.update(keyXORIpad);
  }

  public Object clone() throws CloneNotSupportedException
  {
    HMACwithAnyMD retval = new HMACwithAnyMD();
    retval.L = this.L;
    retval.keyXORIpad = (byte[])this.keyXORIpad.clone();
    retval.keyXOROpad = (byte[])this.keyXOROpad.clone();
    retval.md = (MessageDigest)this.md.clone();
    return retval;
  }

  private static final boolean DUMMY = Licensed.VALID;
}
