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

import java.io.IOException;
import java.util.Vector;
import java.util.Iterator;

import com.dstc.security.asn1.Asn1;
import com.dstc.security.asn1.Asn1Exception;
import com.dstc.security.asn1.Sequence;
import com.dstc.security.asn1.Set;
import com.dstc.security.asn1.Oid;

/**
 * <p>A class representing the X.500 ASN.1 structure Attribute.
 *
 * <pre>
 *   Attribute       ::=     SEQUENCE {
 *          type    AttributeType,
 *          values  SET OF AttributeValue
 *                  -- at least one value is required -- }
 *
 *   AttributeType           ::=   OBJECT IDENTIFIER
 *
 *   AttributeValue            ::=   CHOICE {
 *          DirectoryString,
 *          IA5String
 *          }
 *
 *   DirectoryString ::= CHOICE {
 *       teletexString           TeletexString (SIZE (1..MAX)),
 *       printableString         PrintableString (SIZE (1..MAX)),
 *       universalString         UniversalString (SIZE (1..MAX))
 *                                            }
 * </pre>
 *
 * @version 0.98, 98/07/01
 * @author Ming Yung
 */
public class Attribute
{
  private Asn1 asn1 = null;

  //Object identifier as a string
  protected String type;

  //AttributeValues
  protected Vector values;

  /**
   * Constructs an Attribute from a DER encoding
   */
  public Attribute(Asn1 asn1) throws Asn1Exception
  {
    if (asn1 == null)
      throw new Asn1Exception("null asn1");

    this.asn1 = asn1;

    Iterator it = asn1.components();
 
    this.type = ((Oid)it.next()).getOid();
 
    Set set = (Set)it.next();
    Iterator it2 = set.components();
    this.values = new Vector();
    while (it2.hasNext())
    {
      this.values.add((Asn1)it2.next());
    }
  }

  /** 
   * Constructs an Attribute from type and Vector of Asn1 values
   */
  public Attribute(String type, Vector values)
  {
    this.asn1 = new Sequence();

    this.type = type;
    this.asn1.add(new Oid(type));

    this.values = values;
    Set set = new Set();
    Iterator it = values.iterator();
    while (it.hasNext())
    {
      set.add((Asn1)it.next());
    }
    this.asn1.add(set);
  }

  /**
   * Constructs an Attribute from type and a Asn1
   */
  public Attribute(String type, Asn1 value)
  {
    this.asn1 = new Sequence();

    this.values = new Vector();
    this.values.add(value);

    this.type = type;
    this.asn1.add(new Oid(type));

    Set set = new Set();
    set.add(value);
    this.asn1.add(set);
  }

  public Asn1 getAsn1()
  {
    return this.asn1;
  }

  /** 
   * Returns the AttributeType
   */
  public String getType()
  {
    return this.type;
  }

  /**
   * Returns the AttributeValues as a Vector of Asn1s
   */
  public Vector getValues()
  {
    return this.values;
  }
}
