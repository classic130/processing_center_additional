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
import java.util.Vector;
import java.net.InetAddress;
import java.net.UnknownHostException;

import com.dstc.security.asn1.Asn1;
import com.dstc.security.asn1.Asn1Exception;
import com.dstc.security.asn1.IA5String;
import com.dstc.security.asn1.OctetString;
import com.dstc.security.asn1.Oid;
import com.dstc.security.asn1.Sequence;
import com.dstc.security.asn1.Explicit;
import com.dstc.security.common.X500Name;

/**
 * <p>A class representing x.509 ASN.1 structure GeneralName.
 * 
 * <pre>
 *      GeneralName ::= CHOICE {
 *           otherName                       [0]     OtherName,
 *           rfc822Name                      [1]     IA5String,
 *           dNSName                         [2]     IA5String,
 *           x400Address                     [3]     ORAddress,
 *           directoryName                   [4]     EXPLICIT Name,
 *           ediPartyName                    [5]     EDIPartyName,
 *           uniformResourceIdentifier       [6]     IA5String,
 *           iPAddress                       [7]     OCTET STRING,
 *           registeredID                    [8]     OBJECT IDENTIFIER}
 *
 * </pre>
 */
public class GeneralName
{
  private Asn1 asn1 = null;

  public static final int RFC822NAME = 1;
  public static final int DNSNAME = 2;
  public static final int DIRECTORYNAME = 4;
  public static final int URL = 6;
  public static final int IPADDRESS = 7;
  private int type;
  private String name;
  
  public GeneralName(Asn1 asn1) throws Asn1Exception
  {
    if (asn1 == null)
      throw new Asn1Exception("null asn1");

    this.asn1 = asn1;

    this.type = asn1.getTagNumber();

    if (this.type == 1 || this.type == 2 || this.type == 6) { 
        this.name = new String(asn1.getValue());
    }
    else if (this.type == 4) {         // watch out - explicit tagging!
        Asn1 comp = (Asn1)asn1.components().next();
        this.name = (new X500Name(comp)).toString();
    }
    else if (this.type == 7 ) {              // deal with IP addresses
        byte[] b = asn1.getValue();
        StringBuffer sb = new StringBuffer();
        for (int i=0; i < b.length; i++) {
            sb.append(b[i] & 0xff);
            if (i != b.length-1) sb.append(".");
        }
        this.name = sb.toString();
    }
    else {
        this.name = new String(asn1.getEncoded());
    }
  }

  public GeneralName(int tagNum, String name)
  {
    this(tagNum, orig(tagNum, name));

    this.type = tagNum;
    this.name = name;
  }

  private GeneralName(int tagNum, Asn1 orig)
  {
    this.asn1 = orig;
    this.asn1.setTagClass(Asn1.TAG_CLASS_CONTEXT);
    this.asn1.setTagNumber(tagNum);
  }

  private static final Asn1 orig(int type, String name)
  {
    byte[] b = null;
    switch (type)
    {
      case (1):
      case (2):
      case (6):
        return new IA5String(name);

      case(4):
           Explicit exp = new Explicit(Asn1.TAG_CLASS_CONTEXT, 4);
           exp.add((new X500Name(name)).getAsn1());
           return exp;

      case(7):
        try {
            b = (InetAddress.getByName(name)).getAddress();
        }
        catch(UnknownHostException e) {
            throw new RuntimeException("Unknown Host");
        }
        return new OctetString(b);

      default:
        return null;
    }
  }

  /**
   * Returns the type of this GeneralName
   */
  public int getType()
  {
    return this.type;
  }
  
  /**
   * Return this GeneralName as a form of String
   */
  public String getName()
  {
    return this.name;
  }

  public String toString()
  {
    return this.getName();
  }
  public Asn1 getAsn1()
  {
    return this.asn1;
  }
} 
