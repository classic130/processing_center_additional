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

class Base64Encoder extends Base64
{
  Base64Encoder() {};

  private static final char table[]
    = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
       'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
       'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
       'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
       '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/'};

  void doBlock(byte[] in, int offset, byte[] out, int outOffset)
    throws Base64Exception
  {
    try
    {
      out[outOffset    ] = (byte)table[(in[offset] & 0xfc) >> 2];
      out[outOffset + 1] = (byte)table[((in[offset] & 0x03) << 4) | 
                                       ((in[offset + 1] & 0xf0) >> 4)];
      out[outOffset + 2] = (byte)table[((in[offset + 1] & 0x0f) << 2) | 
                                       ((in[offset + 2] & 0xc0) >> 6)];
      out[outOffset + 3] = (byte)table[in[offset + 2] & 0x3f];
    }
    // XX - probably better off without this (just let the exception propagate,
    //      since it indicates an internal botch) but leave it alone for now
    catch (ArrayIndexOutOfBoundsException e)
    {
      throw new Base64Exception("Bad input");
    }

    consumed = 3;
    produced = 4;
  }

  void doFinal(byte[] in, int inOffset, int length, byte[] out, 
              int outOffset) 
    throws Base64Exception
  {
    switch (length)
    {
      case (0):
        produced = 0;
        consumed = 0;
        return;

      case (1):
        out[outOffset    ] = (byte)table[(in[inOffset] & 0xfc) >> 2];
        out[outOffset + 1] = (byte)table[(in[inOffset] & 0x03) << 4];
        out[outOffset + 2] = (byte)'=';
        out[outOffset + 3] = (byte)'=';
        produced = 4;
        consumed = 1;
        return;

      case (2):
        out[outOffset    ] = (byte)table[(in[inOffset] & 0xfc) >> 2];
        out[outOffset + 1] = (byte)table[((in[inOffset] & 0x03) << 4) | 
                                         ((in[inOffset + 1] & 0xf0) >> 4)];
        out[outOffset + 2] = (byte)table[(in[inOffset + 1] & 0x0f) << 2];
        out[outOffset + 3] = (byte)'=';
        produced = 4;
        consumed = 2;
        return;

      case (3):
        doBlock(in, inOffset, out, outOffset);
        return;

      default:
        throw new Base64Exception("length must be 0 .. 3");
    }
  }
}
