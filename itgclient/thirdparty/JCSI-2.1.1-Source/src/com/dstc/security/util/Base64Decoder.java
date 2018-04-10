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

class Base64Decoder extends Base64
{
  private static final char PAD = '=';

  Base64Decoder() {};

  void doBlock(byte[] in, int offset, byte[] out, int outOffset)
    throws Base64Exception
  {
    int a = getValue(in[offset    ]);
    int b = getValue(in[offset + 1]);
    int c = getValue(in[offset + 2]);
    int d = getValue(in[offset + 3]);
    out[outOffset    ] = (byte)((a & 0xff) << 2 | (b & 0xff) >> 4); 
    out[outOffset + 1] = (byte)((b & 0xff) << 4 | (c & 0xff) >> 2);
    out[outOffset + 2] = (byte)((c & 0xff) << 6 | (d & 0xff));
    produced = 3;
    consumed = 4;
  }

  void doFinal(byte[] in, int offset, int length, byte[] out, int outOffset)
    throws Base64Exception
  {
    if (length == 0)
    {
      produced = 0;
      consumed = 0;
      return;
    }

    if (length != 4)
      throw new Base64Exception("Not padded correctly");

    doBlock(in, offset, out, outOffset);

    if (in[offset + 3] == PAD)
      produced -= 1;
    if (in[offset + 2] == PAD)
      produced -=1;
    consumed = 4;
  }

  private static final int getValue(int current) throws Base64Exception 
  {
    int retval = 0;

    if (current > 0x60)
      retval = current - 71;
    else if (current > 0x40)
      retval = current - 65;
    else if (current > 0x2f)
      retval = current  + 4;
    else if (current == 0x2b)
      retval = 62;
    else if (current == 0x2f)
      retval = 63;
    else
      throw new Base64Exception("Bad input character: " + (char)current);

    return retval;
  }
}
