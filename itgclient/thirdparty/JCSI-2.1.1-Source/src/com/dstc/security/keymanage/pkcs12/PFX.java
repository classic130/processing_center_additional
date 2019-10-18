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

import java.io.InputStream;
import java.io.IOException;
import java.io.OutputStream;
import java.security.InvalidKeyException;
import java.security.InvalidAlgorithmParameterException;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.Arrays;
import java.util.Iterator;
import java.util.NoSuchElementException;

import javax.crypto.Mac;
import javax.crypto.SecretKey;
import javax.crypto.spec.PBEParameterSpec;

import com.dstc.security.asn1.Asn1;
import com.dstc.security.asn1.Asn1DecodingException;
import com.dstc.security.asn1.Asn1EncodingException;
import com.dstc.security.asn1.Asn1Exception;
import com.dstc.security.asn1.Integer;
import com.dstc.security.asn1.OctetString;
import com.dstc.security.asn1.Sequence;
//import com.dstc.security.cms.CMSException;
import com.dstc.security.keymanage.pkcs7.AlgorithmId;
import com.dstc.security.keymanage.pkcs7.ContentInfo;
import com.dstc.security.common.OID;
import com.dstc.security.keymanage.debug.Debug;
import com.dstc.security.keymanage.pkcs7.ContentInfoFactory;
import com.dstc.security.keymanage.pkcs7.Data;
import com.dstc.security.keymanage.pkcs7.DigestInfo;
import com.dstc.security.keymanage.pkcs12.AuthenticatedSafe;
import com.dstc.security.keymanage.pkcs12.MacData;

import com.dstc.security.keymanage.util.PKCS12KeyFactory;

public class PFX
{
  private Asn1 asn1;

  private int version = DEFAULT_VERSION;
  private ContentInfo contentInfo;
  private MacData macData;
  
  private AuthenticatedSafe authSafe;
  private byte[] data;
  
  private byte[] test_data;

  private static final int DEFAULT_VERSION = 3;

  //---------------------------------------------------------------------------
  //  Static Final Members relating to MACing
  //---------------------------------------------------------------------------

//   Moved to PKCS12KeyFactory

//   private static final String MAC_ALGORITHM = "HMACwithSHA1";
//   private static final String MD_ALGORITHM = "SHA";
//   private static final String DIGEST_OID = OID.sha_1;
  
  public  static final int DEFAULT = 0;
  public  static final int NETSCAPE_COMPATIBLE = 1;
  public  static final int MICROSOFT_COMPATIBLE = 2;
  private static final int GREATEST_FLAG = 2;
  
  private static final int COM_ITERATIONS = 1;
  private static final int DEFAULT_ITERATIONS = COM_ITERATIONS;

  //---------------------------------------------------------------------------
  //  Static Methods
  //---------------------------------------------------------------------------

  /**
   *  Creates a PFX object decoded from a passed InputStream. <p>
   *
   *  @param stream The inputstream to decode.
   *  @throws Asn1DecodingException If cannot decode InputStream.
   *  @throws Asn1Exception If the stream does not contain a valid PFX.
   *  @throws IOException If a problem is encountered reading from istream.
   */
  public static PFX createPFX( InputStream istream )
  throws Asn1DecodingException, Asn1Exception, IOException
  {
    Debug.log( Debug.DEBUG, "PFX.createPFX( InputStream )", "" );

    Asn1 asn1 = Asn1.getAsn1(istream); // Throws Asn1DecodingException
    
    return new PFX( asn1 ); // Throws Asn1Exception
  }

  //---------------------------------------------------------------------------
  //  Constructors
  //---------------------------------------------------------------------------

  /**
   *  Creates a PFX from a DER encoding. <p>
   *
   *  @param asn1 An Asn1 object representing a PFX object.
   *  @throws Asn1Exception If PFX or component is invalid.
   */
  public PFX( Asn1 asn1 ) throws Asn1Exception
  {
    Debug.log( Debug.DEBUG, "PFX( Asn1 )", "" );
    Debug.dumpAsn1To( asn1, Debug.PFX );
 
    //this.asn1 = new Sequence();
    
    Iterator it = asn1.components();
    try
    {
      com.dstc.security.asn1.Integer versionAsn1 =
          (com.dstc.security.asn1.Integer) it.next();
      this.version = versionAsn1.getInt();

      Asn1 contentInfoAsn1 = (Asn1) it.next();

      //  We now need to parse the Asn1 of the ContentInfo before calling
      //  it.hasNext() or it.next() else we will get NoSuchElementExceptions
      //  as the iterator will have gone past it.

      //  May throw Asn1Exception.
      this.contentInfo = new ContentInfo( contentInfoAsn1 );

      this.initDataAndAuthSafe();  // throws Asn1Exception

      if ( it.hasNext() )
      {
        Asn1 macDataAsn1 = (Asn1) it.next(); // throws NoSuchElementException
        Debug.log( Debug.DEBUG, "PFX( Asn1 )", "Returned MacData" );
        this.macData = new MacData( macDataAsn1 );
      }
    }
    catch ( ClassCastException ex )
    {
      throw new Asn1Exception( "Invalid PFX ASN.1: " + ex.toString() );
    }
    catch ( NoSuchElementException ex )
    {
      throw new Asn1Exception( "Incomplete PFX ASN.1: " + ex.toString() );
    }
  }

  /**
   *  Creates a PFX that holds the passed ContentInfo object. <p>
   *
   *  @param contentInfo A Data or SignedData ContentInfo object.
   */
  public PFX( ContentInfo contentInfo ) throws Asn1Exception
  {
    this( contentInfo, null );
    Debug.log( Debug.DEBUG, "PFX( ContentInfo )", "" );
  }

  /**
   *  Creates a PFX containing the optional MacData structure. <p>
   *
   *  @param contentInfo A Data or SignedData ContentInfo object whose content
   *                     is an AuthenticatedSafe object.
   *  @param macData A MacData object appropriate for the contentInfo.
   *  @throws Asn1DecodingException If contentInfo does not contain valid ASN.1
   *  @throws Asn1Exception If contentInfo does not hold an AuthenticatedSafe.
   */
  public PFX( ContentInfo contentInfo, MacData macData )
  throws Asn1DecodingException, Asn1Exception
  {
    Debug.log( Debug.DEBUG, "PFX( ContentInfo, MacData )", "" );

    this.version = DEFAULT_VERSION;
    this.contentInfo = contentInfo;
    this.macData = macData;

    this.initDataAndAuthSafe(); //throws Asn1DecodingException, Asn1Exception
  }

  /**
   *  Creates a PFX object that holds the passed AuthenticatedSafe object. <p>
   *
   *  @param authSafe The payload for this PFX object.
   */
  public PFX( AuthenticatedSafe authSafe )
  {
    this( authSafe, null );
    Debug.log( Debug.DEBUG, "PFX( AuthenticatedSafe )", "" );
  }
  
  /**
   *  Creates a PFX object that encapsulates the passed AuthenticatedSafe
   *  object, and sets the MacData information.
   *
   *  @param authSafe The payload for this PFX object.
   *  @param macData A MacData object that should be valid for the resulting
   *                 PFX object.
   */
  public PFX( AuthenticatedSafe authSafe, MacData macData )
  {
    this.version = DEFAULT_VERSION;

    // Create Content Info.
    this.authSafe = authSafe;
    Asn1 auth = authSafe.getAsn1();
    this.contentInfo = ContentInfoFactory.createContentInfo( auth );
    
    try
    {
      this.data = auth.getEncoded(); // throws Asn1Exception
    }
    catch ( Asn1Exception ex ) {
      // Swallow exception.
      // This should never occur.
      Debug.log( Debug.ERROR,
          "PFX( AuthenticatedSafe, MacData )",
              "Unexpected exception while encoding AuthenticatedSafe" );
      throw new RuntimeException(
          "Unexpected exception while encoding AuthenticatedSafe: " +
          ex.toString() );
    }
   
    if ( null != macData )
    {
      this.macData = macData;
    }
  }    

  //---------------------------------------------------------------------------
  //  Initialization
  //---------------------------------------------------------------------------

  /**
   *  Extracts an AuthSafe object from a ContentInfo. <p>
   *
   *  The ContentInfo may contain SignedData or Data.
   *  This method attempts to retrieve the encoded AuthSafe from either the
   *  ContentInfo or in the case of SignedData the content of the ContentInfo
   *  component of the SignedData object. <p>
   *
   *  Thought: Does PKCS#12 force SignedData objects to only hold Data
   *  ContentInfo objects. <p>
   */
  private void initDataAndAuthSafe()
  throws Asn1DecodingException, Asn1Exception
  {
    Debug.log( Debug.DEBUG, "PFX.initDataAndAuthSafe()", "" );

    //  Extract the raw payload from the possibly recursive ContentInfo
    //  structure.
    //
    //  ci should either be of type Data or SignedData so decryption keys
    //  should be unnecessary.
    try
    {
      this.data = ContentInfoFactory.recurse( this.contentInfo, null, null );
    }
    catch ( Asn1Exception ex )
    {
      throw ex;
    }
    catch ( Exception ex )
    {
      //  This catches a variety of exceptions related to encrypted ContentInfo
      //  objects, as this should only contain a SignedData or Data object
      //  these should never be thrown. However if they are this indicates
      //  that a malformed ContentInfo has been passed.
      throw new Asn1Exception(
          "Content does not contain Data or SignedData as expected" );
    }

    // Decode AuthSafe into an Asn1 object.
    Asn1 asn1 = Asn1.getAsn1( this.data ); // throws Asn1Exception

    // Create a new AuthenticatedSafe object.
    this.authSafe = new AuthenticatedSafe( asn1 ); // throws Asn1Exception
  }

  //---------------------------------------------------------------------------
  //  Accessors
  //---------------------------------------------------------------------------
  
  public Asn1 getAsn1()
  {
    if ( null == this.asn1 )
    {
      this.asn1 = new Sequence();
      this.asn1.add( new com.dstc.security.asn1.Integer( this.version ) );
      this.asn1.add( contentInfo.getAsn1() );
      if ( null != macData )
      {
        this.asn1.add( macData.getAsn1() );
      }
    }
    return this.asn1;
  }

  public int getVersion()
  {
    return this.version;
  }
  
  public ContentInfo getContentInfo()
  {
    return this.contentInfo;
  }
  
  public AuthenticatedSafe getAuthSafe()
  {
    return this.authSafe;
  }
  
  public MacData getMacData() throws NoSuchElementException
  {
    if ( this.macData == null )
    {
      throw new NoSuchElementException( "Optional MacData Not Present" );
    }
    return this.macData;
  }
  
  public boolean hasMacData()
  {
    if ( this.macData != null ) {
      return true;
    } else {
      return false;
    }
  }

  //---------------------------------------------------------------------------
  //  Operations
  //---------------------------------------------------------------------------
  
  /**
   *  Encodes this PFX object out to the OutputStream. <p>
   *
   *  @param pfx The PFX object to encode.
   *  @param ostream The OutputStream to encode to.
   *  @throws Asn1EncodingException If unable to encode PFX object to ASN.1.
   *  @throws IOException If unable to write to OutputStream.
   */
  public void encode( OutputStream ostream )
  throws Asn1EncodingException, IOException
  {
    try
    {
      Asn1 pfx = this.getAsn1();
      pfx.derEncode( ostream ); // throws Asn1Exception, IOException
    }
    catch ( Asn1Exception ex ) {
      throw new Asn1EncodingException();
    }
  }
  
  //---------------------------------------------------------------------------
  //  MAC Methods
  //---------------------------------------------------------------------------

/**
 *  The PFXFactory class converts to/from MACed PFX objects. <p>
 *  Although the returned PFX objects are not exactly the same as those
 *  passed in. The produced PFX objects retain references to the objects
 *  referenced by the passed in PFX objects. The should be taken into
 *  consideration when using this factory. <p>
 *
 *  Note by Eddie Cheung from MacData class
 *  -- In the PKCS#12 2nd Draft, it said that certain Micro$oft
 *  -- product must have the value of 1. ie. they are busted.
 *  -- Also for netscape generated pkcs12 files, they don't have iteration.
 *
 *  To allow for this a compatibility modes have been provided. To select a
 *  certain compatibility mode use either of the flags:
 *  <ul>
 *  <li><code>NETSCAPE_COMPATIBLE</code> -- enforces that the iteration
 *                                          count is "1" and that it is NOT
 *                                          encoded into the MacData.
 *  <li><code>MICROSOFT_COMPATIBLE</code> -- enforces that the iteration count
 *                                          is "1" and that it IS encoded into
 *                                          MacData.
 *  </ul>
 *
 *  In the PKCS#12 Specification iterations is specified default to "1". I
 *  am under the impression that a value should not be encoded into
 *  the ASN.1 if it matches the default. Hence, if neither of these
 *  compatibility modes is selected, a iterations value of 1 will not be
 *  encoded but any higher value will be. <p>
 *
 *  Usage:
 *  <pre>
 *       PFX pfx = new PFX( contentInfo );
 *       PFX MACedPFX = PFXFactory.macPFX( pfx, key, pbeSpec );
 *       ...
 *       boolean verified = PFXFactory.verify( MACedPFX, key );
 *  </pre>
 *  Or:
 *  <pre>
 *       PFX pfx = new PFX( contentInfo );
 *       PFX MACedPFX =
 *           PFXFactory.macPFX( pfx, key, pbeSpec, NETSCAPE_COMPATIBLE );
 *  </pre>
 *
 *  @author Daniel Bradley.
 *  @version 0.1, 2000/3/1
 */

  /**
   *  Generates an integrity protection Mac Data structure using the
   *  passed PBEKey, then adds it to this object. <p>
   *
   *  @param key The PBEKey to use to generate a MACKey to MAC this PFX.
   *  @throws InvalidKeyException If PBEKey is an invalid key.
   */
  public void mac( SecretKey key ) throws InvalidKeyException
  {
    try
    {
      this.mac( key, PFX.DEFAULT );
    }
    catch ( InvalidFlagException ex ) {
      // Should not happen as DEFAULT is valid.
      throw new RuntimeException( ex.toString() );
    }
  }

  /**
   *  Generates an integrity protection Mac Data structure using the
   *  passed PBEKey, then adds it to this object. <p>
   *
   *  The flag specifies which compatibility mode should be used to ensure
   *  compatibility with commercial browsers, options are:
   *
   *  <ul>
   *  <li>  DEFAULT
   *  <li>  NETSCAPE
   *  <li>  MICROSOFT
   *  </ul>
   *
   *  @param key The PBEKey to use to generate a MACKey to MAC this PFX.
   *  @param flag The compatibility mode to use.
   *  @throws InvalidKeyException If PBEKey is an invalid key.
   */
  public void mac( SecretKey key, int flag )
  throws InvalidFlagException, InvalidKeyException
  {
    PBEParameterSpec paramSpec = null;
    if ( DEFAULT == flag )
    {
      paramSpec = PKCS12KeyFactory.generatePBEParameterSpec();
    } else {
      byte[] salt = PKCS12KeyFactory.generateSalt();
      paramSpec = new PBEParameterSpec( salt, DEFAULT_ITERATIONS );
    }
    this.mac( key, paramSpec, flag );
  }

  /**
   *  Reinitializes the MacData structure of this PFX object. <p>
   *
   *  @param key The PBEKey used to produce the MAC digest.
   *  @param paramSpec The parameters used to produce the MACKey.
   *  @throws InvalidKeyException If key is not a valid Key.
   */
  public void mac( SecretKey key, PBEParameterSpec paramSpec )
  throws InvalidKeyException
  {
    try
    {
      this.mac( key, paramSpec, DEFAULT );
    }
    catch ( InvalidFlagException ex ) {
      // Should NOT be ever thrown as DEFAULT is a valid flag.
      throw new RuntimeException( ex.toString() );
    }
  }

  /**
   *  Reinitializes the MacData structure of this PFX object. <p>
   *
   *  A lot of this should actually be abstracted out into a general purpose
   *  MACing class. <p>
   *
   *  Note: If a compatibility mode is selected, only the <code>Salt</code>
   *  member of the <code>PBEParameterSpec</code> object will be used. <p>
   *
   *  @param pfx The PFX object to MAC.
   *  @param key The PBEKey used to produce the MAC digest.
   *  @param paramSpec The parameters used to produce the MACKey.
   *  @param flag Flag to specify if a compatibility mode is desired.
   *  @return PFX A MACed PFX object.
   *  @throws InvalidKeyException If key is not a valid Key.
   *  @throws InvalidFlagException If flag is invalid.
   */
  public void mac( SecretKey key, PBEParameterSpec paramSpec, int flag )
  throws InvalidKeyException, InvalidFlagException
  {
    // If either NETSCAPE_COMBATIBLE or MICROSOFT_COMPATIBLE mode is selected
    // then iterations must be set as "1" (COM_ITERATIONS).
    PBEParameterSpec pbeSpec = null;
    if ( (flag < DEFAULT) || (flag > GREATEST_FLAG) )
    {
      String value = java.lang.Integer.toString( flag );
      throw new InvalidFlagException( "Invalid Flag Value: " + value );
    }
    else if ( (flag == NETSCAPE_COMPATIBLE) || (flag == MICROSOFT_COMPATIBLE) )
    {
      pbeSpec = new PBEParameterSpec( paramSpec.getSalt(), COM_ITERATIONS );
    } else {
      pbeSpec = paramSpec;
    }

    SecretKey macKey = PKCS12KeyFactory.generateMacKey( key, pbeSpec );
    byte[] value = this.getData();
    byte[] macDigest = null;

    try
    {
      macDigest = PFX.computeMac( value, macKey );
    } catch ( NoSuchAlgorithmException ex ) {
      // This will only happen if JCSI isn't setup properly.
      // It would probably be better to instantiate the class directly.
      // ie bypass provider architecture.
      Debug.log( Debug.CRITICAL, "PFXFactory.macPFX()", ex.toString() );
      Debug.log( Debug.CRITICAL, "PFXFactory.macPFX()",
          "Check that JCE is installed correctly" );
      throw new RuntimeException( ex.toString() );
    }

    // Construct DigestInfo
    AlgorithmId algId = new AlgorithmId( PKCS12KeyFactory.DIGEST_OID );
    DigestInfo di = new DigestInfo( algId, macDigest );

    // Construct MacData.
    // If MICROSOFT_COMPATIBLE mode is selected iterations must be explicity
    // encoded in MacData.
    byte[] salt = pbeSpec.getSalt();
    int iterations = pbeSpec.getIterationCount();
    
    if ( flag == MICROSOFT_COMPATIBLE )
    {
      // Make MacData with explicit encoding of iterations.
      this.macData = new MacData( di, salt, iterations, true );
    } else {
      this.macData = new MacData( di, salt, iterations );
    }
  }

  /**
   *  Verifies the Mac digest within the MacData component of this PFX. <p>
   *
   *  If PFX does not contain a <b>Mac Data</b> structure, false is returned.
   *  This is somewhat intuitive, as the reproduced MAC definately won't be
   *  identical to nothing. <p>
   *
   *  @param pfx The PFX to verify.
   *  @param key The secret key used to produce the MAC digest.
   *  @return boolean True if MAC is reproduced, else false.
   */
  public boolean verify( SecretKey key )
  throws InvalidKeyException, NoSuchAlgorithmException
  {
    byte[] data = this.getData();

    // Retrieve the information necessary to calculate a new digest,
    // as well as the old digest.
    try
    {
      MacData macData = this.getMacData();
    }
    catch ( NoSuchElementException ex )
    {
      return false;
    }

    // Retrieve the existing digest.
    DigestInfo di = macData.getMac();
    byte[] existing = di.getDigest();

    // Retrieve PBE Parameters from MacData.
    byte[] salt = macData.getMacSalt();
    int iterations = macData.getIterations();
    PBEParameterSpec paramSpec = new PBEParameterSpec( salt, iterations );
    SecretKey macKey = PKCS12KeyFactory.generateMacKey( key, paramSpec );

    // Generate fresh MAC digest.
    byte[] macDigest = PFX.computeMac( data, macKey );

    // If both digests are equal returns true, else false.
    return Arrays.equals( macDigest, existing );
  }

  //---------------------------------------------------------------------------
  //  Private Static Methods
  //---------------------------------------------------------------------------

  /**
   *  Retrieves the Data component from the top level ContentInfo
   *  of this PFX. <p>
   *
   *  The intended purpose is for the data to be used as input for a digest
   *  algorithm. <p>
   */
  private byte[] getData()
  {
    return this.data;
  }

  /**
   *  Mostly taken from MacData class by Eddie Cheung.
   *
   *  @param  data The data to produce a MAC digest of.
   *  @param  macKey The SecretKey that has been combined with the salt as
   *                 defined by PKCS#12.
   *  @return The computed MAC digest.
   */
  private static
  byte[] computeMac( byte[] data, SecretKey macKey )
  throws InvalidKeyException, NoSuchAlgorithmException
  {
    // Generate MAC
    Mac mac = null;
    try
    {
      mac = Mac.getInstance( PKCS12KeyFactory.MAC_ALGORITHM );
    } catch ( NoSuchAlgorithmException ex ) {
      // This will only happen if JCSI isn't setup properly.
      // It would probably be better to instantiate the class directly.
      Debug.log( Debug.CRITICAL, "PFXFactory.macPFX()", ex.toString() );
      Debug.log( Debug.CRITICAL, "PFXFactory.macPFX()",
          "Check that JCE is installed correctly" );
      throw new RuntimeException( ex.toString() );
    }
    mac.init( macKey );
    return mac.doFinal( data );
  }
}
