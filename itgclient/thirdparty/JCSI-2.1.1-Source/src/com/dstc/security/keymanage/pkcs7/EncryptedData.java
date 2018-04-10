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

import com.dstc.security.asn1.Asn1;
import com.dstc.security.asn1.Asn1Exception;
import com.dstc.security.asn1.Sequence;

import com.dstc.security.keymanage.pkcs7.EncryptedContentInfo;
import com.dstc.security.common.OID;
import com.dstc.security.keymanage.debug.Debug;

/**
 *  Implements the PKCS7 ASN.1 structure EncryptedData.
 *
 *  <pre>
 *  EncryptedData ::= SEQUENCE {
 *    version Version,
 *    encryptedContentInfo EncryptedContentInfo
 *  }
 *  </pre>
 *
 *  @author Daniel Bradley (Based upon version by Ming Yung).
 */
public class EncryptedData implements Content
{
  private static final int DEFAULT_VERSION = 0;
  private Asn1 asn1 = null;

  private int version = DEFAULT_VERSION;  
  private EncryptedContentInfo info = null;
  
  public EncryptedData( EncryptedContentInfo encryptedContentInfo )
  {
    this( DEFAULT_VERSION, encryptedContentInfo );
  }

  public EncryptedData( int ver, EncryptedContentInfo encryptedContentInfo )
  {
    this.version = version;
    this.info = encryptedContentInfo;
    
    this.asn1 = new Sequence();
    this.asn1.add( new com.dstc.security.asn1.Integer(this.version) );
    this.asn1.add( this.info.getAsn1() );
  }

  /**
   *  @param asn1 An Asn1 object that represents an EncryptedData object.
   */
  public EncryptedData( Asn1 asn1 ) throws Asn1Exception
  {
    Debug.log( Debug.DEBUG, "EncryptedData( Asn1 )", "" );

    this.asn1 = asn1;
    
    Iterator it = asn1.components();
    try
    {
      Debug.log( Debug.DEBUG, "EncryptedData( Asn1 )", "Version" );
      com.dstc.security.asn1.Integer ver =
          (com.dstc.security.asn1.Integer) it.next();
      this.version = ver.getInt();

      Debug.log( Debug.DEBUG, "EncryptedData( Asn1 )", "Content" );
      Asn1 content = (Asn1) it.next();
      Debug.log( Debug.DEBUG, "EncryptedData( Asn1 )", "Retrieved Asn1" );
      this.info = new EncryptedContentInfo( content );
      Debug.log( Debug.DEBUG, "EncryptedData( Asn1 )", "Info" );
    }
    // Thrown if asn1 does not contain necessary number of components.
    //
    catch ( NoSuchElementException ie ) {
      throw new Asn1Exception( "Incomplete EncryptedData ASN.1" );
    }
    // Thrown if asn1 does not contain appropriate asn1 sub-objects.
    //
    catch ( ClassCastException cce ) {
      throw new Asn1Exception( "Invalid EncryptedData ASN.1" );
    }  
  }
  
  // Content interface implementation.
  public Asn1 getAsn1()
  {
    return this.asn1;
  }
  
  public String getContentType()
  {
    return OID.id_encryptedData;
  }

  public int getVersion()
  {
    return this.version;
  }
  
  public EncryptedContentInfo getEncryptedContentInfo()
  {
    return this.info;
  }
}
