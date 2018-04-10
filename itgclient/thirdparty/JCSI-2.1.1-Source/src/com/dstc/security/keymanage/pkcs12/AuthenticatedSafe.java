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

package com.dstc.security.keymanage.pkcs12;

import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.security.spec.InvalidKeySpecException;
import java.util.Vector;
import java.util.List;
import java.util.Set;
import java.util.Iterator;
import java.util.NoSuchElementException;

import com.dstc.security.asn1.Asn1;
import com.dstc.security.asn1.Asn1Exception;
import com.dstc.security.asn1.OctetString;
import com.dstc.security.asn1.Sequence;
import com.dstc.security.keymanage.pkcs7.AlgorithmId;
import com.dstc.security.keymanage.pkcs7.ContentInfo;
import com.dstc.security.common.OID;
import com.dstc.security.keymanage.debug.Debug;
import com.dstc.security.keymanage.pkcs7.ContentInfoFactory;
import com.dstc.security.keymanage.pkcs12.SafeContents;

/**
 * <p>A class representing the PKCS#12 ASN.1 structure AuthenticatedSafe
 *    Each Content is a SafeContent.
 *    When a SafeContent is not encrypted (ie. plain), the Oid is id_data
 *    When a SafeContent is encrypted, then the Oid is id_encrypteDdata
 *    Finally, when the SafeContent is enveloped, the Oid is id_envelopedData
 * <pre>
 *     AuthenticatedSafe ::= SEQUENCE OF ContentInfo
 * </pre>
 *
 * @see com.dstc.security.pkcs12.util.BagHandler
 * @see com.dstc.security.pkcs12.PFX
 * @see com.dstc.security.pkcs12.SafeContent
 * @see com.dstc.security.cms.ContentInfo
 *
 * @version 0.98, 99/05/26
 * @author Eddy Cheung
 */
public class AuthenticatedSafe
{
  private Asn1 asn1;

  /**
   *  Stores SafeContent objects. <p>
   */
  private Vector contents = new Vector();

  //---------------------------------------------------------------------------
  //  Constructors
  //---------------------------------------------------------------------------

  /**
   *  Constructs an empty AuthenticatedSafe object. <p>
   */
  public AuthenticatedSafe() {}

  public AuthenticatedSafe( SafeContents safeContents )
  {
    this.add( safeContents );
  }

  /**
   *  Constructs an AuthenticatedSafe object that encapsulates
   *  the passed ContentInfo objects. <p>
   *
   *  @param contentInfos An array of ContentInfo objects.
   */
  public AuthenticatedSafe( ContentInfo[] contentInfos )
  {
    for ( int i=0; i < contentInfos.length; i++ )
    {
      this.contents.add( contentInfos[i] );
    }
  }

  /**
   * Constructs AuthenticatedSafe from a DER encoding
   */
  public AuthenticatedSafe( Asn1 asn1 ) throws Asn1Exception
  {
    Debug.log( Debug.DEBUG, "AuthenticatedSafe( Asn1 )", "" );
    Debug.dumpAsn1To( asn1, Debug.AUTHENTICATEDSAFE );

    this.asn1 = asn1;
    
    Iterator it = asn1.components();
    Asn1 cia = null;
    ContentInfo ci = null;
    while( it.hasNext() )
    {
      cia = (Asn1) it.next();
      ci = new ContentInfo( cia );
      this.contents.add( ci );
    }
  }

  //---------------------------------------------------------------------------
  //  Accessors
  //---------------------------------------------------------------------------

  /**
   *  Returns a vector contain the ContentInfo objects held by this
   *  AuthenticatedSafe object. <p>
   *
   *  @return Vector Containing ContentInfo objects.
   */
  public ContentInfo[] getContents()
  {
    ContentInfo[] array = new ContentInfo[ this.contents.size() ];
    this.contents.toArray( array );
    return array;
  }

  /**
   *  Returns the ContentInfo object at the specified posn. <p>
   */
  public ContentInfo get( int posn )
  {
    return (ContentInfo) this.contents.get( posn );
  }

  //---------------------------------------------------------------------------
  //  Operations
  //---------------------------------------------------------------------------

  /**
   *  Encapsulates the SafeContents into a DATA ContentInfo object and adds
   *  it to the AuthenticatedSafe. <p>
   *
   *  @param safeContents The SafeContents to add.
   */
  public void add( SafeContents safeContents )
  {
    this.asn1 = null;

    Asn1 scAsn1 = safeContents.getAsn1();
    ContentInfo ci = ContentInfoFactory.createContentInfo( scAsn1 );
    this.add( ci );
  }

  /**
   *  Encapsulates the SafeContents into a DATA ContentInfo object and adds
   *  it to the AuthenticatedSafe at the specified position. <p>
   *
   *  @param posn The position to add the ContentInfo object.
   *  @param safeContents The SafeContents to add.
   */
  public void add( int posn, SafeContents safeContents )
  {
    this.asn1 = null;

    Asn1 scAsn1 = safeContents.getAsn1();
    ContentInfo ci = ContentInfoFactory.createContentInfo( scAsn1 );

    this.add( posn, ci );
  }

  /**
   *  Adds either a Data, EncryptedData, or EnvelopedData ContentInfo
   *  object. <p>
   *
   *  @param contentInfo A ContentInfo object (Data, Encrypted, or Enveloped).
   */
  public void add( ContentInfo contentInfo )
  {
    this.asn1 = null;
    this.contents.add( contentInfo );
  }

  /**
   *  Adds either a Data, EncryptedData, or EnvelopedData ContentInfo
   *  object into a specified position. <p>
   *
   *  @param posn The position to add the ContentInfo object.
   *  @param contentInfo A ContentInfo object (Data, Encrypted, or Enveloped).
   */
  public void add( int posn, ContentInfo contentInfo )
  {
    this.asn1 = null;
    this.contents.add( posn, contentInfo );
  }

  public ContentInfo remove( int posn )
  {
    this.asn1 = null;
    return (ContentInfo) this.contents.remove( posn );
  }

  /**
   *  Returns an Asn1 object that represents an AuthenticatedSafe object. <p>
   *
   *  @return An Asn1 object.
   */
  public Asn1 getAsn1()
  {
    if ( null == this.asn1 )
    {
      this.asn1 = new Sequence();

      int size = this.contents.size();
      for ( int i=0; i < size; i++ )
      {
        ContentInfo ci = (ContentInfo) this.contents.get( i );
        this.asn1.add( ci.getAsn1() );
      }
    }
    return this.asn1;
  }

  /**
   *  Removes the passed ContentInfo object from this AuthenticatedSafe. <p>
   *
   *  @param The ContentInfo object to remove.
   *  @return The ContentInfo object removed.
   *  @throws Exception If the ContentInfo object is not present.
   */
  public ContentInfo remove( ContentInfo contentInfo )
  throws NoSuchElementException
  {
    this.asn1 = null;

    if ( this.contents.remove( contentInfo ) == false )
    {
      throw new NoSuchElementException( "ContentInfo not present" );
    }
    return contentInfo;
  }
}
