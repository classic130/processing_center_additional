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

package com.dstc.security.common;

import java.io.*;
import java.util.StringTokenizer;
import java.util.Vector;
import java.util.Iterator;

import com.dstc.security.common.OID;
import com.dstc.security.asn1.*;

/**
 * <p>A class representing the x.500 ASN.1 structure AttributeTypeAndValue.
 *
 * <pre>
 *    AttributeTypeAndValue           ::=     SEQUENCE {
 *          type    AttributeType,
 *          value   AttributeValue }
 *  
 *    AttributeType           ::=   OBJECT IDENTIFIER
 *
 *    AttributeValue            ::=   CHOICE {
 *          DirectoryString,
 *          IA5String
 *          }
 * </pre>
 *
 * @see com.dstc.security.x509.X500Name
 *
 * @version 0.98, 98/07/01
 * @author Ming Yung
 */
public class AttributeTypeAndValue
{
  private Asn1 asn1 = null;
  private String type;
  private String friendly;
  private String value;

  /**
   * Constructs an AttributeTypeAndValue from a type and a value.
   *
   */
  public AttributeTypeAndValue(String type, String value)
  {
    if (type.startsWith("OID"))
    {
      this.type = type.substring(4);
      this.friendly = OID.getAlgName(type);
    }
    else
    {
      this.type = OID.getAlgOid(type);
      this.friendly = type;
    }
    
    this.asn1 = new Sequence();
    this.asn1.add(new Oid(this.type));

    this.value = value;
    if (!this.type.equals(OID.emailAddress))
      this.asn1.add(new PrintableString(value));
    else
      this.asn1.add(new IA5String(value));
  }

  public AttributeTypeAndValue(InputStream is) 
    throws Asn1Exception, IOException
  {
    this(Asn1.getAsn1(is));
  }

  /**
   * Constructs an AttributeTypeAndValue from a DER encoding
   */
  public AttributeTypeAndValue(Asn1 asn1) throws Asn1Exception
  {
    this.asn1 = asn1;

    Iterator it = asn1.components();

    this.type = ((Oid)it.next()).getOid();
    this.friendly = OID.getAlgName(this.type);

    Asn1 comp = (Asn1)it.next();
    try
    {
      this.value = ((DirectoryString)comp).getString();
      return;
    }
    catch (ClassCastException e)
    {
      //ignore
    }
    this.value = ((IA5String)comp).getString();
  }

  public String getName()
  {
    if (friendly.indexOf(".") == -1)
      return (friendly + "=" + quote(value));
    else
      return ("OID." + friendly + "=" + quote(value));
  }

  public String getType()
  {
    return type;
  }

  public String getValue()
  {
    return value;
  }

  public Asn1 getAsn1()
  {
    return this.asn1;
  }

  private String quote(String raw)
  {
    if ((raw.indexOf(",") == -1) ||
        (raw.indexOf("\"") != -1))
    {
      return raw;
    }
    else
    {
      return "\"" + raw + "\"";
    }
  }
}
