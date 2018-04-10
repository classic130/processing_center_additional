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

/**
 * Conversions between big-endian UTF-16 byte arrays and {@link String}.
 * <p>
 * Sun's JDK has a character convertor that does these, but we can't rely 
 * on it being on all Java platforms.
 */
public abstract class UnicodeBig
{
  /**
   * Unicode byte-order mark.  Optional at the start of a UTF-16 value,
   * used to distinguish between big-endian and little-endian byte order.
   */
  public static final char BOM         = '\uFEFF';
  /**
   * Byte-reversed version of {@link #BOM}, used to detect UTF-16 written
   * in the reverse endian-ness.  Should never occur in proper Unicode.
   */
  public static final char REVERSE_BOM = '\uFFFE';

  /**
   * All methods are static, so instantiating this doesn't make sense
   */
  private UnicodeBig() {}

  /**
   * Convert from a {@link String} to big-endian UTF-16.  This does
   * <strong>not</strong> prepend a {@link #BOM}.
   *
   * @param in a non-null String to be converted
   * @return an array of bytes containing the big-endian UTF-16
   *         representation of the string value
   */
  public static byte[] stringToBytes(String in)
  {
    int inLen = in.length();
    byte[] out = new byte[inLen << 1];
    for (int inIdx = 0;  inIdx < inLen;  inIdx++) {
      // String.toCharArray() would use less CPU but more heap
      char c = in.charAt(inIdx);
      int outIdx = inIdx << 1;
      out[outIdx    ] = (byte)(c >>> 8);  // ">>" would work fine too
      out[outIdx + 1] = (byte) c;
    }
    return out;
  }

  /**
   * Convert from big-endian UTF-16 to a {@link String}.  The initial 
   * {@link #BOM}, if present, will be skipped.
   *
   * @param in a non-null array containing big-endian UTF-16
   * @return a String containing the same Unicode characters (but without
   *         the leading byte-order mark, if there was one)
   * @exception IllegalArgumentException if the number of bytes is odd,
   *         or an initial {@link #REVERSE_BOM} was encountered
   */
  public static String bytesToString(byte[] in)
  {
    int inLen = in.length;
    if ((inLen & 1) != 0) {
      throw new IllegalArgumentException("Byte-count is odd");
    }
    int outLen = inLen >> 1;
    char[] out = new char[outLen];
    for (int outIdx = 0;  outIdx < outLen;  outIdx++) {
      int inIdx = outIdx << 1;
      out[outIdx] = (char) ((in[inIdx] << 8) + (in[inIdx + 1] & 0xFF));
    }
    int outOffset = 0;
    if (outLen > 0) {

      switch (out[0]) {

      case REVERSE_BOM:
        // Data is really little-endian UTF-16
        throw new IllegalArgumentException("Byte-order (mark) is reversed");

      case BOM:
        // Return everything except the byte-order mark
        ++outOffset;
        --outLen;
        break;
       
      default:
        // normal path
        break;

      }
    }
    return new String(out, outOffset, outLen);
  }
}
