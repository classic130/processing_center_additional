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
//      Email: enquiries@dstc.edu.au
//
// This software is being provided "AS IS" without warranty of
// any kind.  In no event shall DSTC Pty Ltd be liable for
// damage of any kind arising out of or in connection with
// the use or performance of this software.
//
////////////////////////////////////////////////////////////////////////////

package com.dstc.security.asn1;

import java.io.*;

/**
 * <p>A class representing the ASN.1 type BitString.
 *
 * @see com.dstc.security.asn1.Asn1
 *
 * @version 0.98, 98/07/01
 * @author Ming Yung
 */
public class BitString extends Asn1
{
  public BitString()
  {
    this.tag = TAG_BITSTRING;
  }

  public BitString(byte in[])
  {
    this(in, (byte)0);
  }

  //unusedNumBit must be between 0 and 8 
  public BitString(byte in[], byte unusedNumBit)
  {
    this();
    //Assertion
    if (unusedNumBit < 0 || unusedNumBit > 8) {
      throw new IllegalArgumentException("The number of unused bits must has a value between 0 and 8");
    }
 
    this.value = new byte[in.length+1];
    System.arraycopy(in, 0, this.value, 1, in.length);
    this.value[0] = (byte)unusedNumBit;
  }

  public boolean testBit(int bit)
  {
    byte testMask = (byte)(0x80 >>> (bit % 8));
    return ((this.value[(bit >> 3)+1] & testMask) != 0);
  }

  public byte[] getBytes()
  {
    //zero out of the padding first, in case people use 1's for padding
    int padding = 0xff;
    padding = padding >>> value[0];
    padding = padding << value[0];
    value[value.length-1] &= padding;
    //The first octet is skipped as it contains the number of unusedBits
    byte retval[] = new byte[this.value.length - 1];
    System.arraycopy(this.value, 1, retval, 0, retval.length);
    return retval;
  }

  public int getUnusedBitNum()
  {
    return this.value[0];
  }

  public int getNumOfBits()
  {
    return (((value.length - 1) << 3) - getUnusedBitNum());
  }
}
