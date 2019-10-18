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
 * <p>A class for representing the ASN.1 type OctetString.
 * 
 * <p> On the encoding side:
 * <br>
 *
 * <p>If the constructor takes a bytearray parameter, the
 * resulting encoding will be DER. If the constructor takes
 * an InputStream paramater, the resulting encoding will be
 * BER using the constructed indefinite-length method.
 *
 * @see com.dstc.security.asn1.Asn1
 *
 * @version 0.98, 98/07/01
 * @author Ming Yung
 */
public class OctetString extends Asn1
{
  public OctetString() 
  {
    this.tag = TAG_OCTETSTRING;
  }

  /**
   * Constructs an OctetString whose contents are taken
   * from a byte array. The encoding will be DER.
   */
  public OctetString(byte in[])
  {
    this(in, 0, in.length);
  }

  /**
   * Constructs an OctetString whose contents are taken
   * from a byte array starting from an offset and of a
   * given length. The encoding will be DER.
   */
  public OctetString(byte in[], int offset, int length)
  {
    this();
    this.value = new byte[length];
    System.arraycopy(in, offset, this.value, 0, length);
  }

  /**
   * Constructs an OctetString whose contents are taken from 
   * the supplied InputStream. The encoding will be BER.
   */
  public OctetString(InputStream is)
  {
    this();
    this.tag |= TAG_CONSTRUCTED;

    this.lengthKnown = false;
    this.contentsIn = is;
  }

  /**
   *  Returns the contents encapsulated by this OctetString. <p>
   *
   *  Note: <p>
   *
   *  If this OctetString is constructed (indefinate-length), null will be
   *  returned.
   *  To avoid this it is potentially possible to use writeValue()
   *  to get a result.
   *  Alternatively look at
   *  <code>ContentInfoFactory.getBytes( OctetString )</code>. <p>
   */
  public byte[] getBytes()
  {
    return this.value;
  }
}
