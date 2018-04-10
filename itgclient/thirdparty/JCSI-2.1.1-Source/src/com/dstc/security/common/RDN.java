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
import java.util.StringTokenizer;
import java.util.Hashtable;
import java.util.Iterator;
import java.util.Vector;

import com.dstc.security.asn1.Asn1;
import com.dstc.security.asn1.Asn1Exception;
import com.dstc.security.asn1.Sequence;
import com.dstc.security.asn1.Set;
import com.dstc.security.asn1.PrintableString;
import com.dstc.security.asn1.T61String;
import com.dstc.security.asn1.IA5String;
import com.dstc.security.asn1.Oid;
import com.dstc.security.common.OID;

/**
 * <p>A class representing the x.500 ASN.1 structure RelativeDistinguishedName.
 *
 * <pre>
 *    RelativeDistinguishedName  ::=
 *                       SET SIZE (1 .. MAX) OF AttributeTypeAndValue
 *
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
 * @see com.dstc.security.common.X500Name
 *
 * @version 0.98, 98/07/01
 * @author Ming Yung
 */
public class RDN
{
  private Asn1 asn1 = null;
  private Vector rdnComponents = new Vector();

  /**
   * Constructs an RDN from its String representation as per RFC 1778
   */
  public RDN(String rdn) 
  {
    this.asn1 = new Set();

    StringTokenizer tknz0 = new StringTokenizer(rdn, "+", false);

    while (tknz0.hasMoreTokens())
    {
      String pair = tknz0.nextToken().trim();

      StringTokenizer tknz = new StringTokenizer(pair, "=", false);
      String type = tknz.nextToken().trim();
      String value = tknz.nextToken().trim();
      AttributeTypeAndValue attVal = new AttributeTypeAndValue(type, value);
      rdnComponents.addElement(attVal);
      this.asn1.add(attVal.getAsn1());
    }
  }

  /**
   * Constructs an RDN from a DER encoding
   */
  public RDN(Asn1 asn1) throws Asn1Exception
  {
    this.asn1 = asn1;

    Iterator it = asn1.components();

    while (it.hasNext())
    {
      Asn1 next = (Asn1)it.next();
      if (next == null) break;

      rdnComponents.add(new AttributeTypeAndValue(next));
    }  
  }

  public AttributeTypeAndValue[] getTypeAndValue()
  {
    AttributeTypeAndValue[] retval 
      = new AttributeTypeAndValue[rdnComponents.size()];

    rdnComponents.toArray(retval);
    return retval;
  }

  public Asn1 getAsn1()
  {
    return this.asn1;
  }

  public String getName()
  {
    StringBuffer st = new StringBuffer();
    for (Iterator it = rdnComponents.iterator(); it.hasNext(); )
    {
      st.append(((AttributeTypeAndValue)it.next()).getName());
      
      if (it.hasNext())
      {
        st.append(" + ");
      }
    }
    return st.toString();
  }
}
