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
import java.util.Iterator;

import com.dstc.security.asn1.*;

/**
 * <p> Implements the ASN.1 structure ContentInfo.
 *
 * <pre>
 *     ContentInfo ::= SEQUENCE {
 *        contentType ContentType,
 *        content [0] EXPLICIT ANY DEFINED BY contentType }
 *   
 *     ContentType ::= OBJECT IDENTIFIER
 * </pre>
 *
 * @version 0.98, 98/07/01
 * @author Ming Yung
 */
public class ContentInfo
{
  private Asn1 asn1 = null;
  private Oid contentType;
  private Asn1 content = null;

  /**
   * Constructs a ContentInfo from a content type oid and a Asn1
   */
  public ContentInfo(String oid, Asn1 content)
  {
    this.asn1 = new Sequence();
    this.contentType = new Oid(oid);
    this.asn1.add(contentType);

    if (content != null)
    {
      this.content = content;
      Explicit exp = new Explicit(Asn1.TAG_CLASS_CONTEXT, 0);
      exp.add(content);
      this.asn1.add(exp);
    }
  }

  /**
   * Constructs a ContentInfo from a DER encoding
   */
  public ContentInfo(Asn1 asn1) throws Asn1Exception
  {
    if (asn1 == null)
      throw new Asn1Exception("null data");

    this.asn1 = asn1;
    Iterator it = asn1.components();

    this.contentType = (Oid)it.next();
    
    if (!it.hasNext()) return;

    Asn1 exp = (Asn1)it.next();
    if (exp.components() == null)
    {
      this.content = exp;
    }
    else
      this.content = (Asn1)exp.components().next();
  }

  public Asn1 getAsn1()
  {
    return this.asn1;
  }

  /**
   * Returns the Content type for this ContentInfo
   */
  public String getContentType()
  {
    return this.contentType.getOid();
  }

  /**
   * Returns the Content for this ContentInfo as a Asn1
   */
  public Asn1 getContent()
  {
    return content;
  }
}
