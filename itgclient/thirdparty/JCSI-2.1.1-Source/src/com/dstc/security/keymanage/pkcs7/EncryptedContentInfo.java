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

import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.util.Iterator;
import java.util.NoSuchElementException;

import com.dstc.security.asn1.Asn1;
import com.dstc.security.asn1.Asn1Exception;
import com.dstc.security.asn1.Sequence;
import com.dstc.security.asn1.Asn1Exception;
import com.dstc.security.asn1.Oid;
import com.dstc.security.asn1.OctetString;
import com.dstc.security.keymanage.debug.Debug;
import com.dstc.security.keymanage.pkcs7.AlgorithmId;
import com.dstc.security.common.OID;

/**
 * <p> Implements the ASN.1 structure EncryptedContentInfo.
 *
 * <pre>
 *     EncryptedContentInfo ::= SEQUENCE {
 *        contentType ContentType,
 *        contentEncryptionAlgorithm ContentEncryptionAlgorithmIdentifier,
 *        encryptedContent [0] IMPLICIT EncryptedContent OPTIONAL }
 *
 *     ContentEncryptionAlgorithmIdentifier ::= AlgorithmIdentifier
 *
 *     EncryptedContent ::= OCTET STRING
 * </pre>
 *
 *  Modified to enable support for indefinate length encodings. DRB. <p>
 */
public final class EncryptedContentInfo
{
  private Asn1 asn1 = null;

  private String contentType;
  private AlgorithmId contentEncryptionAlgorithm;
  private byte[] encryptedContent;

  /**
   *  Constructs an EncryptedContentInfo from a BER encoding. <p>
   *
   *  Supports indefinate length encoding. <p>
   */
  public EncryptedContentInfo( Asn1 asn1 )
  throws Asn1Exception
  {
    //  XXX. Should this be here?
    Debug.log( Debug.DEBUG, "EncryptedContentInfo( Asn1 )", "" );
    if ( null == asn1 )
    {
      throw new Asn1Exception( "null ASN.1 data" );
    }

    try
    {
      Iterator it = asn1.components();
      Oid ct = (Oid) it.next();
      this.contentType = ct.getOid();
      this.contentEncryptionAlgorithm = new AlgorithmId( (Asn1) it.next() );

      if ( it.hasNext() )
      {
        /*Asn1 comp = (Asn1) it.next();
System.out.println("Class: " + comp.getAsAsn1Tagged( Asn1.TAG_OCTETSTRING ).getClass().getName());
        OctetString oct =
            (OctetString) comp.getAsAsn1Tagged( Asn1.TAG_OCTETSTRING );

        //  Call wrapper method to handle constructed OctetStrings.
        this.encryptedContent = getBytes( oct );
        //this.encryptedContent = oct.getBytes();*/
     
        ByteArrayOutputStream baos = new ByteArrayOutputStream();
        ((Asn1)it.next()).writeValue(baos);
        this.encryptedContent = baos.toByteArray();
      }
    }
    catch ( IOException ex )
    {
      throw new RuntimeException(
          "Internal error: " + ex.toString() );
    }
    catch ( ClassCastException ex )
    {
      throw new Asn1Exception(
          "Invalid EncryptedContentInfo ASN.1: " + ex.toString() );
    }
    catch ( NoSuchElementException ex )
    {
      throw new Asn1Exception(
          "Incomplete EncryptedContentInfo ASN.1: " + ex.toString() );
    }
  }

  private static byte[] getBytes( OctetString oct )
  {
    byte[] retval = oct.getBytes();

    if ( ( null == retval ) && oct.isConstructed() )
    {
      ByteArrayOutputStream baos = new ByteArrayOutputStream();

      Iterator itr = oct.components();
      while( itr.hasNext() )
      {
        OctetString str = (OctetString) itr.next();
        byte[] bytes = getBytes( str );
        baos.write( bytes, 0, bytes.length );
      }
      retval = baos.toByteArray();
    }
    return retval;
  }

  /**
   * Constructs an EncryptedContentInfo
   */
  public EncryptedContentInfo( String contentType,
                               AlgorithmId algoId,
                               byte[] content )
  {
    this.contentType = contentType;
    this.contentEncryptionAlgorithm = algoId;
    this.encryptedContent = content;
  }

  //---------------------------------------------------------------------------
  //  Accessors
  //---------------------------------------------------------------------------

  public Asn1 getAsn1()
  {
    if ( null == this.asn1 )
    {
      this.asn1 = new Sequence();
      this.asn1.add( new Oid( contentType ) );
      this.asn1.add( this.contentEncryptionAlgorithm.getAsn1() );

      //implicit tagging of constructed primitive type
      OctetString oct = new OctetString( this.encryptedContent );
      oct.setTagClass(Asn1.TAG_CLASS_CONTEXT);
      oct.setTagNumber(0);
      this.asn1.add( oct );
    }
    return this.asn1;
  }

  /**
   * Returns the content type for this EncryptedContentInfo
   */
  public Oid getContentType()
  {
    return new Oid( this.contentType );
  }

  /**
   * Returns the content encryption algorithm for this EncryptedContentInfo
   */
  public AlgorithmId getContentEncryptionAlgorithm()
  {
    return this.contentEncryptionAlgorithm;
  }

  /**
   * Returns the encrypted content for this EncryptedContentInfo
   */
  public byte[] getEncryptedContent()
  {
    return encryptedContent;
  }
}
