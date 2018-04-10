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

package com.dstc.security.x509;

import java.io.*;
import java.util.Iterator;
import java.util.Vector;
import java.util.Set;
import java.util.HashSet;

import com.dstc.security.asn1.Boolean;
import com.dstc.security.asn1.Asn1;
import com.dstc.security.asn1.Asn1Exception;
import com.dstc.security.asn1.Oid;
import com.dstc.security.asn1.Sequence;
import com.dstc.security.asn1.OctetString;


/**
 * <p>A class representing the x.509 ASN.1 structure Extension.
 * 
 * <pre>
 *   Extension  ::=  SEQUENCE  {
 *       extnID      OBJECT IDENTIFIER,
 *       critical    BOOLEAN DEFAULT FALSE,
 *       extnValue   OCTET STRING  }
 * </pre>
 */
public class Extension
{
  protected Asn1 asn1 = null;

  private String extnID;
  private boolean critical = false;
  private ExtensionValue extnValue; 

  /**
   * Default constructor
   */
  public Extension() {}

  public Extension(String extnID, boolean critical, ExtensionValue extnValue)
                    throws Asn1Exception
  {
    this.extnID = extnID;
    this.critical = critical;
    this.extnValue = extnValue;
 
    encode();
  }                                                                             

  /**
   * Constructs an Extension from a DER encoding
   */
  public Extension(InputStream is) throws IOException, Asn1Exception
  {
    this(Asn1.getAsn1(is));
  }

  public Extension(Asn1 asn1) throws Asn1Exception
  {
    if (asn1 == null)
      throw new Asn1Exception("null asn1");

    this.asn1 = asn1;

    Iterator it = asn1.components();
    this.extnID = ((Oid)it.next()).getOid();
    Asn1 comp = (Asn1)it.next();

    try
    {
      this.critical = ((Boolean)comp).isTrue();
      comp = (Asn1)it.next();
    }
    catch (ClassCastException e)
    {
      //Ignore
    }

    this.extnValue = ExtensionFactory.getExtension(this.extnID, comp);

    if (this.extnValue == null) {
        this.extnValue = new UnknownExtensionVal(this.extnID, comp);
    }

  }

  public Asn1 getAsn1()
  {
    return this.asn1;
  }

  public boolean isCritical()
  {
    return this.critical;
  }

  public String getExtnID()
  {
    return this.extnID;
  }

  public ExtensionValue getExtnValue()
  {
    return this.extnValue;
  }

  void encode() throws Asn1Exception
  {
    this.asn1 = new Sequence();
    this.asn1.add(new Oid(this.extnID));
 
    if (critical)
      this.asn1.add(new Boolean(true));
 
    this.asn1.add(new OctetString(extnValue.getEncoded()));
  }                                                                             

  public String toString()
  {
  /*if (this.extnValue != null)
      return this.extnValue.toString();
    else
    {
      StringBuffer sb = new StringBuffer("Unknown Extension:\n");
      sb.append("  OID:" + extnID + "\n");
      return sb.toString();
    }*/
    return this.extnValue.toString();
  }

  public static String printHex(byte bytes[]) 
  {
    StringBuffer sb = new StringBuffer();
    for (int i=0; i<bytes.length; i++) 
    {
      sb.append(toHexDigit(bytes[i]));
    }
    sb.append("\n");
    return sb.toString();
  }

  private static String toHexDigit(byte x)
  {
    char ret[] = new char[2];
    char c = (char) ((x >> 4) & 0xf);
    if (c > 9)
    {
      c = (char) ((c - 10) + 'a');
    }
    else
    {
      c = (char) (c + '0');
    }
    ret[0] = c;

    c = (char) (x & 0xf);
    if (c > 9)
    {
      c = (char)((c - 10) + 'a');
    }
    else
    {
      c = (char)(c + '0');
    }
    ret[1] = c;
    return new String(ret);
  }

  private class UnknownExtensionVal implements ExtensionValue
  {
    private String extnId;
    private Asn1 asn1;
 
    UnknownExtensionVal(String id, Asn1 asn1) {
        this.extnId = id;
        this.asn1 = asn1;
    }
 
    public byte[] getEncoded() throws Asn1Exception {

      return this.asn1.getEncoded();

    }

    public String toString() {
 
      byte[] b=null;
      StringBuffer sb = new StringBuffer();
      sb.append("Unknown extension:" + "\n");
      sb.append("  OID:" + this.extnId + "\n");
      try {
          b = this.asn1.getEncoded();
      }
      catch(Asn1Exception e) {
          throw new RuntimeException("Bad DER encoding");
      }
      sb.append("    DER encoding:\n            ");
      for (int i=0; i<b.length; i++)
      {
        if ((i>0) && (i % 20 == 0)) {
            sb.append("\n            ");
        }
        if (b[i] <16 && b[i] >=0) {
          sb.append("0"+java.lang.Integer.toHexString(
                            b[i] & 0xff) + " ");
        }
        else {
          sb.append(java.lang.Integer.toHexString(b[i] & 0xff) + " ");
        }
      }
      sb.append("\n");
      return sb.toString();
    }
 
  } 

}
