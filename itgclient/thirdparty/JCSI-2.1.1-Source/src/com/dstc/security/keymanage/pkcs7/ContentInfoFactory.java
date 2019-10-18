//////////////////////////////////////////////////////////////////////////
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

package com.dstc.security.keymanage.pkcs7;

import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.security.InvalidKeyException;
import java.security.InvalidAlgorithmParameterException;
import java.security.NoSuchAlgorithmException;
import java.security.PrivateKey;
import java.security.spec.AlgorithmParameterSpec;
import java.security.spec.InvalidParameterSpecException;
import java.util.Iterator;

import javax.crypto.BadPaddingException;
import javax.crypto.Cipher;
import javax.crypto.IllegalBlockSizeException;
import javax.crypto.NoSuchPaddingException;
import javax.crypto.SecretKey;
import javax.crypto.spec.PBEParameterSpec;

import com.dstc.security.asn1.Asn1;
import com.dstc.security.asn1.Asn1Exception;
import com.dstc.security.asn1.OctetString;
import com.dstc.security.common.OID;
import com.dstc.security.keymanage.debug.Debug;
import com.dstc.security.keymanage.pkcs7.AlgorithmId;
import com.dstc.security.keymanage.pkcs7.ContentInfo;
import com.dstc.security.keymanage.pkcs7.Data;
import com.dstc.security.keymanage.pkcs7.EncryptedContentInfo;
import com.dstc.security.keymanage.pkcs7.EncryptedData;

// IN PROGRESS import com.dstc.security.keymanage.pkcs7.EnvelopedData;

import com.dstc.security.keymanage.util.PKCS12KeyFactory;

/**
 *  This class converts ContentInfo objects to/from ContentInfo objects that
 *  contain EncryptedData, EnvelopedData, or SignedData content. <p>
 */
public class ContentInfoFactory
{
  public static final String DEFAULT_ALGORITHM = "PBEwithMD5andDES-CBC";
  public static final String DEFAULT_ALGORITHM_OID = OID.pbeWithMD5AndDES_CBC;

  // Hashcodes

  private static final int DATA = OID.id_data.hashCode();
  private static final int ENCRYPTED_DATA = OID.id_encryptedData.hashCode();
  private static final int ENVELOPED_DATA = OID.id_envelopedData.hashCode();
  private static final int SIGNED_DATA = OID.id_signedData.hashCode();

  //---------------------------------------------------------------------------
  //  ContentInfo Methods
  //---------------------------------------------------------------------------

  /**
   *  Creates a ContentInfo object containing the ASN.1 encoding of the passed
   *  Asn1 object. <p>
   */
  public static ContentInfo createContentInfo( Asn1 asn1 )
  {
    ContentInfo ci = null;

    try
    {
      byte[] encoded = asn1.getEncoded(); // throws IOException.
      Data data = new Data( encoded );
      ci = new ContentInfo( OID.id_data, (Content) data );
    }
    catch ( Asn1Exception ex ) {
      // Should never occur.
      throw new RuntimeException( "Unexpected exception: " + ex.toString() );
    }
    return ci;
  }

  /**
   *  Attempts to create a new Data Content implemenation of
   *  <code>contentType</code> using <code>asn1</code>. <p>
   */
  public static Content
  resolve( String contentType, Asn1 asn1 )
  throws Asn1Exception
  {
    if ( null == asn1 )
    {
      throw new NullPointerException( "Asn1 is null" );
    }
    int type = contentType.hashCode();

    Content retval = null;

    if ( DATA == type )
    {
      try
      {
        ByteArrayOutputStream baos;
        OctetString oct = (OctetString) asn1;

        //  Call wrapper method which handles constructed OctetStrings
        byte[] bytes = getBytes( oct );

        if ( null == bytes )
        {
          throw new Asn1Exception( "Empty/Invalid OctetString" );
        }
        retval = new Data( bytes );
      }
      catch ( ClassCastException ex )
      {
      }
    }
    else if ( ENCRYPTED_DATA == type )
    {
      retval = new EncryptedData( asn1 );
    }
    else if ( ENVELOPED_DATA == type )
    {
      throw new UnsupportedOperationException(
          "EnvelopedData support in progress" );
      // retval = new EnvelopedData( asn1 );
    }
    else if ( SIGNED_DATA == type )
    {
      throw new UnsupportedOperationException(
          "SignedData support in progress" );
      // retval = new SignedData( asn1 );
    }
    else
    {
      throw new Asn1Exception( "Unknown Type" );
    }
    return retval;
  }






  /**
   *  Recurses into a ContentInfo object and returns the Data Content. <p>
   *
   *  ContentInfo objects may contain many different types of payloads,
   *  EncryptedData, EnvelopedData, SignedData etc.
   *  Each of these holds a ContentInfo object which may in turn hold any
   *  of these types - a recursive structure. <p>
   *
   *  This method uses recursion to work its way down through a recursive
   *  ContentInfo structure using the keys supplied to decrypt or unenvelope
   *  the contained types along the way, eventually returning the
   *  bottommost DATA ContentInfo object. <p>
   *
   *  Note:
   *
   *  Original I had this function return a ContentInfo object until I found
   *  that EncryptedContentInfo objects do not necessarily contain payloads
   *  encoded as OctetStrings, hence I changed it. DRB. <p>
   *
   *  In the case of a DATA ContentInfo object the OctetString is decoded
   *  into bytes which are then returned. In the case of encrypted types
   *  the decrypted bytes are returned. <p> 
   *
   *  @param ci The ContentInfo object to be recursed into.
   *  @param skeys An array of SecretKeys used to attempt decryption.
   *  @param pkeys An array of PrivateKeys used to attempt unenveloping.
   *  @returns byte[] The eventual payload.
   *  @throw Asn1Exception If Asn1 is invalid.
   *  @throw InvalidKeyException If decryption/unenveloping fails due to
   *                             not having a key.
   */
  public static byte[]
  recurse( ContentInfo ci, SecretKey[] skeys, PrivateKey[] pkeys )
  throws Asn1Exception,
         BadPaddingException,
         ClassNotFoundException,
         IllegalBlockSizeException,
         InvalidAlgorithmParameterException,
         InvalidKeyException,
         InvalidParameterSpecException,
         IOException,
         NoSuchAlgorithmException,
         NoSuchPaddingException
  {
    byte[] data = null;
    int type = ci.getContentType().hashCode();

    if ( SIGNED_DATA == type )
    {
      throw new UnsupportedOperationException(
          "SigendData support in progress" );
//       try
//       {
//         SignedData signedData = (SignedData) ci.getAsContent();
//         ContentInfo contentInfo = signedData.getContentInfo();
//         data = recurse( contentInfo, null, null );
//       }
//       catch ( ClassCastException ex )
//       {
//         throw new Asn1Exception(
//             "Content Not SignedData As Expected" + ex.toString() );
//       }
    }
    else if( ENCRYPTED_DATA == type )
    {
      Debug.log( Debug.DEBUG, "ContentInfoFactory.recurse(...)",
              "trying keys to unencrypt EncryptedContentInfo" );

      //  Try each key to see if it decrypts.
      for ( int i=0; i < skeys.length; i++ )
      {
        try
        {
          Debug.log( Debug.DEBUG, "ContentInfoFactory.recurse(...)",
              "trying key" );
          data = decrypt( ci, skeys[i] );
          Debug.log( Debug.DEBUG, "ContentInfoFactory.recurse(...)",
              "valid key" );
          break;
        }
        catch ( InvalidKeyException ex )
        {
          Debug.log( Debug.DEBUG, "ContentInfoFactory.recurse(...)",
              "invalid key" );
        }
        catch ( Exception ex )
        {
          throw new RuntimeException("Unexpected error: " + ex.toString());
        }
      }
      if ( null == data )
      {
        throw new InvalidKeyException();
      }
    }
    else if ( ENVELOPED_DATA == type )
    {
      throw new RuntimeException( "EnvelopedData Support In Development" );
    }
    else if ( DATA == type )
    {
      Data dataContent = (Data) ci.getAsContent();
      data = dataContent.getBytes();
    }
    else
    {
      throw new Asn1Exception( "Unsupported ContentInfo Type" );
    }

    // Return the DATA ContentInfo
    return data;
  }

  /**
   *  Decrypts the content of the passed EncryptedData ContentInfo
   *  object and returns a new ContentInfo object. <p>
   *
   *  @param contentInfo The EncryptedData ContentInfo object to be decrypted.
   *  @param password The password that will be used to decrypt the content.
   *  @throws IOException If ContentInfo does not contain an
   *                      EncryptedContentInfo.
   *
   */
  public static ContentInfo
  decrypt( ContentInfo contentInfo, char[] password )
  throws
         Asn1Exception,
         BadPaddingException,
         ClassNotFoundException,
         IllegalBlockSizeException,
         InvalidAlgorithmParameterException,
         InvalidKeyException,
         InvalidParameterSpecException,
         IOException,
         NoSuchAlgorithmException,
         NoSuchPaddingException
  {
    // This directly uses a provider class.
    //
    SecretKey sKey = PKCS12KeyFactory.createPBEKey( password );
    byte[] encoded = decrypt( contentInfo, sKey );

    // Create a new ContentInfo object containing the now decrypted
    // content from the EncryptedContentInfo.
    Asn1 asn1 = Asn1.getAsn1( encoded );

    // This assumes that it was a Content subclass that was actually
    // encrypted.
    Content content = resolve( contentInfo.getContentType(), asn1 );
    return new ContentInfo( content );
  }

  /**
   *  Decrypts the content of the passed EncryptedData ContentInfo
   *  object and returns a new ContentInfo object. <p>
   *
   *  @param contentInfo The EncryptedData ContentInfo object to be decrypted.
   *  @param password The password that will be used to decrypt the content.
   *  @throws IOException If ContentInfo does not contain an
   *                      EncryptedContentInfo.
   *
   */
  public static byte[]
  decrypt( ContentInfo contentInfo, SecretKey skey )
  throws
         Asn1Exception,
         BadPaddingException,
         ClassNotFoundException,
         IllegalBlockSizeException,
         InvalidAlgorithmParameterException,
         InvalidKeyException,
         InvalidParameterSpecException,
         IOException,
         NoSuchAlgorithmException,
         NoSuchPaddingException
  {
    if ( ! contentInfo.getContentType().equals( OID.id_encryptedData ) )
    {
      throw new Asn1Exception( "ContentType not EncryptedData as expected" );
    }

    EncryptedData encData = null;
    try
    {
      encData = (EncryptedData) contentInfo.getAsContent();
    }
    catch ( ClassCastException ex )
    {
      throw new Asn1Exception( "Content Not EncryptedData As Expected" );
    }

    EncryptedContentInfo eci = encData.getEncryptedContentInfo();
    return decrypt( eci, skey );
  }

  /**
   *  Takes the encryptedContent and returns the decrypted form. <p>
   *
   *  @param eci  An EncryptedContentInfo object.
   *  @param skey The secret key to decrypt with.
   *  @return byte[] containing decrypted contents.
   */ 
  public static byte[]
  decrypt( EncryptedContentInfo eci, SecretKey skey )
  throws
         BadPaddingException,
         ClassNotFoundException,
         IllegalBlockSizeException,
         InvalidAlgorithmParameterException,
         InvalidKeyException,
         InvalidParameterSpecException,
         IOException,
         NoSuchAlgorithmException,
         NoSuchPaddingException
  {
    String contentType = eci.getContentType().getOid();
    byte[] encrypted = eci.getEncryptedContent();
    AlgorithmId algorithmId = eci.getContentEncryptionAlgorithm();
    String algorithm = OID.getAlgName( algorithmId.getOid() );

    // May throw NoSuchPaddingException
    // May throw InvalidParameterSpecException
    Cipher cipher = Cipher.getInstance( algorithm );
      
    // May throw InvalidAlgorithmParameterException
    AlgorithmParameterSpec paramsSpec = 
        algorithmId.getParams().getParameterSpec( PBEParameterSpec.class );
      
    // May throw InvalidAlgorithmParameterException
    // May throw InvalidKeyException
    cipher.init( Cipher.DECRYPT_MODE, skey, paramsSpec, null);
    return cipher.doFinal( encrypted );
  }


  //---------------------------------------------------------------------------
  //  Synchronous Encryption Methods
  //---------------------------------------------------------------------------

  /**
   *  Encrypts the content of the passed ContentInfo object and returns
   *  an EncryptedData ContentInfo object. <p>
   *
   *  @param contentInfo The ContentInfo object to encrypt.
   *  @param algorithm The name of the algorithm to use for encryption.
   *  @param password The password to use to encrypt the content.
   *  @throws IOException And others. XXX
   */
  public static ContentInfo
  encrypt( ContentInfo ci, String algorithmName, char[] password )
  throws NoSuchPaddingException,
         NoSuchAlgorithmException,
         InvalidParameterSpecException,
         ClassNotFoundException,
         BadPaddingException,
         IllegalBlockSizeException,
         InvalidAlgorithmParameterException,
         InvalidKeyException
  {
    // Extract the data bytes out of the Data OctetString.
    //
    OctetString content = (OctetString) ci.getAsContent();
    byte[] data = content.getBytes();
    
    // Encrypts the Data
    //
    byte[] encrypted = encrypt( data, algorithmName, password );

    // Package it up into an EncryptedData ContentInfo object.
    //    
    AlgorithmId algorithmId = new AlgorithmId( DEFAULT_ALGORITHM_OID );
    EncryptedContentInfo eci =
        new EncryptedContentInfo( OID.id_data, algorithmId, encrypted );
    EncryptedData encryptedData = new EncryptedData( eci );

    //    Asn1 edAsn1 = encryptedData.getAsn1();
    //    return new ContentInfo( OID.id_encryptedData, edAsn1 );

    return new ContentInfo( OID.id_encryptedData, encryptedData );
  }

  //---------------------------------------------------------------------------
  //  Private Synchronous Methods
  //---------------------------------------------------------------------------

  private static byte[]
  encrypt( byte[] data, String algorithmName, char[] password )
  throws NoSuchPaddingException,
         NoSuchAlgorithmException,
         InvalidParameterSpecException,
         ClassNotFoundException,
         BadPaddingException,
         IllegalBlockSizeException,
         InvalidAlgorithmParameterException,
         InvalidKeyException
  {
    SecretKey pbeKey = PKCS12KeyFactory.createPBEKey( password );

    // XXX Only supports one algorithm so far.
    //
    byte[] salt = "".getBytes();
    PBEParameterSpec paramsSpec = new PBEParameterSpec( salt, 5 );

    // May throw NoSuchPaddingException
    // May throw InvalidParameterSpecException
    Cipher cipher = Cipher.getInstance( algorithmName );

    // May throw InvalidAlgorithmParameterException
    // May throw InvalidKeyException
    cipher.init( Cipher.ENCRYPT_MODE, pbeKey, paramsSpec, null);
    return cipher.doFinal( data ); 
  }

  /**
   *  Encrypts ContentInfo producing EncryptedContentInfo using the key
   *  supplied. <p>
   *
   *  Note: This does not specify parameter specs. <p>
   */
  private static EncryptedContentInfo
  encrypt( ContentInfo ci, SecretKey key )
  throws NoSuchAlgorithmException, NoSuchPaddingException,
         InvalidKeyException, IllegalBlockSizeException
  {
    String algorithmName = key.getAlgorithm();
    AlgorithmId algorithmId = getAlgorithmId( algorithmName );

    byte[] encrypted = null;
    try
    {
      // NoSuchAlgorithmException
      // NoSuchPaddingException
      Cipher cipher = Cipher.getInstance( algorithmName );

      // InvalidKeyException
      cipher.init( Cipher.ENCRYPT_MODE, key );

      // Data to encrypt is the "value" part of ci's content.

      // XXX. Quick change by inserting "getAsn1()" when integrating
      // with ContentInfo - Should work I think. DRB.
      byte[] data = ci.getAsContent().getAsn1().getValue();

      // BadPaddingException
      // IllegalBlockSizeException
      encrypted = cipher.doFinal( data );
    }
    catch ( NoSuchAlgorithmException ex )
    {
      throw new NoSuchAlgorithmException(
          "No Cipher matches Key: " + ex.getMessage() );
    }
    catch ( BadPaddingException ex )
    {
      // Is only thrown during decryption.
    }

    return new
        EncryptedContentInfo( ci.getContentType(), algorithmId, encrypted );
  }

  private static AlgorithmId getAlgorithmId( String algorithmName )
  {
    String algOid = OID.getAlgOid( algorithmName );
    return new AlgorithmId( algOid );
  }

  //---------------------------------------------------------------------------
  //  Private Indefinate-support enabling Methods
  //---------------------------------------------------------------------------

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

  private static byte[] getBytes2( OctetString oct )
  {
    byte[] retval = oct.getBytes();

    if ( ( null == retval ) && oct.isConstructed() )
    {
      try
      {
        ByteArrayOutputStream baos = new ByteArrayOutputStream();
        oct.writeValue( baos );
        retval = baos.toByteArray();
      }
      catch ( IOException ex )
      {
        retval = null; // This isn't really necessary.
      }
    }
    return retval;
  }
}
