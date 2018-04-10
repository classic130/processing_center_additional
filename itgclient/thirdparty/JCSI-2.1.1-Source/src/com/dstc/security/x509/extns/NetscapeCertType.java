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

package com.dstc.security.x509.extns;

import java.io.*;

import com.dstc.security.asn1.Asn1;
import com.dstc.security.asn1.Asn1Exception;
import com.dstc.security.asn1.BitString;
import com.dstc.security.x509.ExtensionValue;

public class NetscapeCertType implements ExtensionValue
{
  public static final byte SSL_CLIENT = (byte)0x80;
  public static final byte SSL_SERVER = (byte)0x40;
  public static final byte SMIME = (byte)0x20;
  public static final byte OBJECT_SIGNING = (byte)0x10;
  public static final byte SSL_CA = (byte)0x04;
  public static final byte SMIME_CA = (byte)0x02;
  public static final byte OBJECT_SIGNING_CA = (byte)0x01;

  private byte type;
  private Asn1 asn1;

  /*public NetscapeCertType(boolean isCritical, byte value)
    throws Asn1Exception, IOException
  {
    this.type = value;
    byte bytes[] = {value};
    this.asn1 = new BitString(bytes);
  }*/

  public NetscapeCertType(byte value)
  {
    this.type = value;
    byte bytes[] = {value};
    this.asn1 = new BitString(bytes);
  }                                                                             

  public NetscapeCertType(Asn1 asn1) 
    throws Asn1Exception, IOException
  {
    this.asn1 = asn1;

    this.type = ((BitString)asn1).getBytes()[0];
  }

  public byte[] getEncoded() throws Asn1Exception
  {
    return this.asn1.getEncoded();
  }

  public String toString()
  {
    StringBuffer sb = new StringBuffer();
    sb.append("NetscapeCertType extension:\n");

    if ((type & SSL_CA) != 0)
      sb.append("  SSL CA\n");

    if ((type & SSL_CLIENT) != 0)
      sb.append("  SSL CLIENT\n");

    if ((type & OBJECT_SIGNING) != 0)
      sb.append("  OBJECT SIGNING\n");

    if ((type & SSL_SERVER) != 0)
      sb.append("  SSL SERVER\n");

    if ((type & SMIME) != 0)
      sb.append("  SMIME\n");

    if ((type & SMIME_CA) != 0)
      sb.append("  SMIME CA\n");
  
    if ((type & OBJECT_SIGNING_CA) != 0)
      sb.append("  OBJECT SIGNING CA\n");

    return sb.toString();
  }
}
