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

package com.dstc.security.util;

public class Bytes
{
  public static byte[] removeLeadingZero(byte[] in)
  {
    if (in[0] == 0)
    {
      byte retval[] = new byte[in.length-1];
      System.arraycopy(in, 1, retval, 0, retval.length);
      return retval;
    }
    else
      return in;
  }

  //MD5, ~SHA1, RIPEMD-160, MD4, RC5, ~Blowfish
  public static final byte[] intsToBytesLSB(int ints[])
  {
    //Converts every int to 4 bytes
    byte bytes[] = new byte[4*ints.length];
    for (int j=0; j < bytes.length; j++)
    {
      bytes[j] = (byte)((ints[j/4] >>> 8*(j%4)) & 0xff);
    }
    return bytes;
  }

  public static final void intsToBytesLSB(int ints[], byte bytes[])
  {
    //Converts every int to 4 bytes
    for (int j=0; j < bytes.length; j++)
    {
      bytes[j] = (byte)((ints[j/4] >>> 8*(j%4)) & 0xff);
    }
  }

  public static final int[] bytesLSBToInts(byte bytes[], int offset, int length)
  {
    //Convert every 4 bytes to an int
    int retval[] = new int[(length + 3)/4];
    for (int j=0; j < length; j++)
    {
      retval[j/4] += (int) (bytes[j + offset] & 0xff) << 8*(j%4);
    }
    return retval;
  }

  public static final byte[] intsToBytesMSB(int ints[])
  {
    //Converts every int to 4 bytes
    byte bytes[] = new byte[4*ints.length];
    for (int j=0; j < bytes.length; j++)
    {
      bytes[j] = (byte)((ints[j/4] >>> 8*((3-j)%4)) & 0xff);
    }
    return bytes;
  }

  public static final void intsToBytesMSB(int ints[], byte bytes[])
  {
    //Converts every int to 4 bytes
    for (int j=0; j < bytes.length; j++)
    {
      bytes[j] = (byte)((ints[j/4] >>> 8*((3-j)%4)) & 0xff);
    }
  }

  public static final int[] bytesMSBToInts(byte bytes[], int offset, int length)
  {
    //Convert every 4 bytes to an int
    int retval[] = new int[(length + 3) >> 2];
    for (int j=0; j < length; j++)
    {
      retval[j >> 2] += (int) (bytes[j + offset] & 0xff) << 8*((3-j)%4);
    }
    return retval;
  }

  public static final long[] bytesMSBToLongs(byte bytes[], 
                                 int offset, int length)
  {
    //Convert every 8 bytes to a long
    long[] retval = new long[(length + 7)/8];
    for (int j=0; j < length; j++)
    {
      retval[j/8] += (long) (bytes[j + offset] & 0xff) << 8*((7-j)%8);
    }
    return retval;
  }

  public static final byte[] longsToBytesMSB(long[] longs)
  {
    //Converts every long to 8 bytes
    byte bytes[] = new byte[8*longs.length];
    for (int j=0; j < bytes.length; j++)
    {
      bytes[j] = (byte)((longs[j/8] >>> 8*((7-j)%8)) & 0xff);
    }
    return bytes;
  }

}
