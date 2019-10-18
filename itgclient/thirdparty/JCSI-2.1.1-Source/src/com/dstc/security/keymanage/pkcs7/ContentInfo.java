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

package com.dstc.security.keymanage.pkcs7;

import java.io.IOException;
import java.util.Iterator;
import java.util.NoSuchElementException;

import com.dstc.security.asn1.*;

//  To support indefinate length encodings ContentInfo needs to
//  have some way of parsing Content types such as SignedData or
//  EncryptedData.
import com.dstc.security.keymanage.pkcs7.Content;
import com.dstc.security.keymanage.pkcs7.ContentInfoFactory;

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
 * @author Daniel Bradley
 */
public class ContentInfo
{
  private Asn1 asn1 = null;

  /**
   *  Identifies the content type - Data, SignedData, EncryptedData, etc. <p>
   */
  private String contentType;

  /**
   *  The content of this ContentInfo, may be any implementation of the
   *  Content interface. <p>
   */
  private Content content;

  //---------------------------------------------------------------------------
  //  Constructors
  //---------------------------------------------------------------------------

  /**
   *  Constructs a ContentInfo from a DER encoding.
   *
   *  Changed this contructor to appropriately parse all subelements from
   *  the Asn1 object - which in turn parses them from the Input Stream.
   *  DRB. <p>
   */
  public ContentInfo(Asn1 asn1) throws Asn1Exception
  {
    if ( asn1 == null )
    {
      throw new Asn1Exception( "Null ASN.1 Data");
    }

    Iterator it = asn1.components();
    try
    {
      //  Parse the Oid out.
      Oid oid = (Oid) it.next();
      this.contentType = oid.getOid();

      //  Parse the Content
      Asn1 exp = (Asn1) it.next();
      Iterator it2 = exp.components();
      if ( null == it2 )
      {
        throw new Asn1Exception( "Invalid ContentInfo ASN.1" );
      }
      else
      {
        //  May throw Asn1Exception.
        Asn1 payload = (Asn1) it2.next();

        this.content =
            ContentInfoFactory.resolve( this.contentType, (Asn1) payload );
      }
      //  By here the part of the Asn1 object's inputstream that is
      //  relevant to this ContentInfo should have been parsed.
    }
    catch ( ClassCastException ex )
    {
      throw new Asn1Exception( "Invalid ContentInfo ASN.1" );
    }
    catch ( NoSuchElementException ex )
    {
      throw new Asn1Exception( "Incomplete ContentInfo ASN.1" );
    }
  }

  /**
   *  Create a ContentInfo object that encapsulates an implementation of the
   *  Content interface. <p>
   */
  public ContentInfo( Content content )
  {
    if ( null == content )
    {
      throw new NullPointerException();
    }
    this.contentType = content.getContentType();
    this.content = content;
  }

  /**
   * Constructs a ContentInfo from a content type oid and an Asn1
   */
  public ContentInfo(String oid, Content content)
  {
    this.contentType = oid;

    if (content != null)
    {
      this.content = content;
    }
  }

  /**
   * Constructs a ContentInfo from a content type oid and an Asn1
   *
   * Asn1 may be either OctetString, EncryptedData,
   */
  public ContentInfo(String oid, Asn1 content)
  throws Asn1Exception
  {
    this.contentType = oid;

    if (content != null)
    {
      this.content = ContentInfoFactory.resolve( oid, content );
    }
  }

  /**
   *  Creates and returns an Asn1 object representing this ContentInfo. <p>
   */
  public Asn1 getAsn1()
  {
    if ( null == this.asn1 )
    {
      this.asn1 = new Sequence();
      this.asn1.add( new Oid( this.contentType ) );
      if ( this.content != null )
      {
        Explicit exp = new Explicit( Asn1.TAG_CLASS_CONTEXT, 0 );
        exp.add( this.content.getAsn1() );
        this.asn1.add( exp );
      }
    }
    return this.asn1;
  }

  /**
   * Returns the Content type for this ContentInfo. <p>
   */
  public String getContentType()
  {
    return this.contentType;
  }

  /**
   * Returns the Content for this ContentInfo as an Asn1. <p>
   */
  public Asn1 getContent()
  {
    return this.content.getAsn1();
  }

  /**
   *  Returns the implementation of the Content interface that is
   *  held by this ContentInfo object. <p>
   *
   *  Note: <p>
   *
   *  It probably makes more sence to call this method
   *  <code>getContent()</code>, but that method name is already used
   *  and is probably needed for backwards compatibility. <p>
   */
  public Content getAsContent()
  {
    return this.content;
  }
}
