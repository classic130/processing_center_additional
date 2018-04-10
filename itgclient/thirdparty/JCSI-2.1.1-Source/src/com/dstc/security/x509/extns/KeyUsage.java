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

/**
 * Class representing the ASN.1 structure KeyUsage.
 *
 * <pre>
 *      KeyUsage ::= BIT STRING {
 *             digitalSignature        (0),
 *             nonRepudiation          (1),
 *             keyEncipherment         (2),
 *             dataEncipherment        (3),
 *             keyAgreement            (4),
 *             keyCertSign             (5),
 *             cRLSign                 (6),
 *             encipherOnly            (7),
 *             decipherOnly            (8) 
 *                               }
 * </pre> 
 * @author Ming Yung
 */
public class KeyUsage implements ExtensionValue
{
  public static final short DIGITAL_SIGNATURE = (short)0x8000;
  public static final short NON_REPUDIATION = (short)0x4000;
  public static final short KEY_ENCIPHERMENT = (short)0x2000;
  public static final short DATA_ENCIPHERMENT = (short)0x1000;
  public static final short KEY_AGREEMENT = (short)0x0800;;
  public static final short KEY_CERT_SIGN = (short)0x0400;
  public static final short CRL_SIGN = (short)0x0200;
  public static final short ENCIPHER_ONLY = (short)0x0100;
  public static final short DECIPHER_ONLY = (short)0x0080;

  private short usage;
  private Asn1 asn1;

  /**
   * Constructs a KeyUsage from the usage
   */
    public KeyUsage(short usage) 
    throws Asn1Exception, IOException
  {
    this.usage = usage;
 
    byte[] val = new byte[2];
    val[0] = (byte)((usage >>> 8) & 0xff);
    val[1] = (byte)(usage & 0xff);
    this.asn1 = new BitString(val);
  }

  /**
   * Constructs a KeyUsage from a DER encoding
   */
  public KeyUsage(Asn1 asn1) 
    throws Asn1Exception, IOException
  {
    this.asn1 = asn1;

    byte[] val = ((BitString)asn1).getBytes();
    
    this.usage = (short)((val[0] << 8) & 0xffff);
    
    if (val.length == 2)
      this.usage |= (short)(val[1] & 0xff);
  }

  public byte[] getEncoded() throws Asn1Exception
  {
    return this.asn1.getEncoded();
  }

  public boolean[] getKeyUsage()
  {
    boolean retval[] = new boolean[9];

    if((usage & DIGITAL_SIGNATURE) != 0)
      retval[0] = true;

    if((usage & NON_REPUDIATION) != 0)
      retval[1] = true;

    if((usage &  KEY_ENCIPHERMENT) != 0)
      retval[2] = true;

    if((usage &  DATA_ENCIPHERMENT) != 0)
      retval[3] = true;

    if((usage &  KEY_AGREEMENT) != 0)
      retval[4] = true;

    if((usage &  KEY_CERT_SIGN) != 0)
      retval[5] = true;

    if((usage & CRL_SIGN) != 0)
      retval[6] = true;

    if((usage &  ENCIPHER_ONLY) != 0)
      retval[7] = true;

    if((usage &  DECIPHER_ONLY) != 0)
      retval[8] = true;

    return retval;
  }

  public String toString()
  {
    StringBuffer sb = new StringBuffer();
    sb.append("KeyUsage extension:\n");

    if((usage & DIGITAL_SIGNATURE) != 0)
      sb.append("  DIGITAL SIGNATURE\n");

    if((usage & NON_REPUDIATION) != 0)
      sb.append("  NON REPUDIATION\n");

    if((usage &  KEY_ENCIPHERMENT) != 0)
      sb.append("  KEY ENCIPHERMENT\n");

    if((usage &  DATA_ENCIPHERMENT) != 0)
      sb.append("  DATA ENCIPHERMENT\n");

    if((usage &  KEY_AGREEMENT) != 0)
      sb.append("  KEY AGREEMENT\n");

    if((usage &  KEY_CERT_SIGN) != 0)
      sb.append("  KEY CERT SIGN\n");

    if((usage & CRL_SIGN) != 0)
      sb.append("  CRL SIGN\n");

    if((usage &  ENCIPHER_ONLY) != 0)
      sb.append("  ENCIPHER ONLY\n");

    if((usage &  DECIPHER_ONLY) != 0)
      sb.append("  DECIPHER ONLY\n");

    return sb.toString();
  }
}
