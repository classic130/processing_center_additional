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

package com.dstc.security.keymanage.pkcs12.bags;

import java.io.IOException;
import java.security.PrivateKey;
import java.util.Iterator;

import com.dstc.security.asn1.Asn1;
import com.dstc.security.asn1.Asn1Exception;
import com.dstc.security.asn1.OctetString;
import com.dstc.security.common.AlgorithmId;
import com.dstc.security.common.OID;
import com.dstc.security.keymanage.debug.Debug;
import com.dstc.security.keymanage.PKCS8EncryptedPrivateKey;
import com.dstc.security.keymanage.PKCS8Exception;

/**
 *  A class representing the PKCS#12 ASN.1 ShroudedKeyBag <p>
 *
 *  <pre>
 *     ShroudedKeyBag ::= EncryptedPrivateKeyInfo ::= SEQUENCE {
 *       encryptionAlgorithm EncryptionAlgorithmIdentifier,
 *       encryptedData EncryptedData }
 *
 *     EncryptionAlgorithmIdentifier ::= AlgorithmIdentifier
 *
 *     EncryptedData ::= OCTET STRING
 *  </pre>
 *
 *  @see com.dstc.security.pkcs8.PKCS8EncryptedPrivateKeyInfo
 *  @see com.dstc.security.pkcs12.SafeBag
 *  @see com.dstc.security.x509.AlgorithmId
 *
 * @author Daniel Bradley
 */
public class ShroudedKeyBag implements Bag
{
  public static final String SHROUDED_KEYBAG = OID.pkcs_8ShroudedKeyBag;

  private Asn1 asn1;

  private PKCS8EncryptedPrivateKey encryptedPrivateKeyInfo;
  
  private String encryptionAlgorithm;
  
  private byte[] encryptedData;
  

  //---------------------------------------------------------------------------
  //  Constructors
  //---------------------------------------------------------------------------

  public ShroudedKeyBag( Asn1 encoding ) 
    throws PKCS8Exception, Asn1Exception
  {
    Debug.dumpAsn1To( encoding, Debug.SHROUDEDKEYBAG );

    this.initialize( encoding );
  }
  
  public ShroudedKeyBag( PKCS8EncryptedPrivateKey encryptedKey )
  {
    //Asn1 asn1 = encryptedKey.getAsn1();
    try
    {
      Asn1 asn1 = Asn1.getAsn1(encryptedKey.getEncoded());
      this.initialize( asn1 );
    }
    catch ( Exception ex ) {
      // Should never happen as we are effectively doing:
      // EncryptedPrivateKeyInfo --> ASN.1 --> EncryptedPrivateKeyInfo
      //
      // DB.
      throw new RuntimeException( "Unexpected exception: " + ex.toString() );
    }
  }

  //---------------------------------------------------------------------------
  //  Initializers
  //---------------------------------------------------------------------------

  private void initialize( Asn1 encoding ) 
    throws PKCS8Exception, Asn1Exception
  {
    this.asn1 = encoding;

    this.encryptedPrivateKeyInfo 
      = new PKCS8EncryptedPrivateKey( this.asn1.getEncoded() );

    try
    {
      Iterator it = this.asn1.components();
      
      Asn1 first = (Asn1) it.next();
      AlgorithmId algorithmId = new AlgorithmId( first );
      this.encryptionAlgorithm = algorithmId.getOid();
      
      OctetString oct = (OctetString) it.next();
      this.encryptedData = oct.getBytes();
    }
    catch ( ClassCastException ex ) {
      throw new PKCS8Exception( "Invalid EncryptedPrivateKeyInfo ASN.1" );
    }
    //catch ( IOException ex ) {
    //  throw new Asn1Exception( "Invalid EncryptedPrivateKeyInfo ASN.1" );
    //}
  }

  //---------------------------------------------------------------------------
  //  Interface Bag Methods
  //---------------------------------------------------------------------------

  public String getType()
  {
    return SHROUDED_KEYBAG;
  }
  
  //---------------------------------------------------------------------------
  //  Accessors
  //---------------------------------------------------------------------------

  public Asn1 getAsn1()
  {
    return this.asn1;
  }

  public PKCS8EncryptedPrivateKey getEncryptedPrivateKeyInfo()
  {
    return this.encryptedPrivateKeyInfo;
  }
  
  public String getEncryptionAlgorithm()
  {
    return this.encryptionAlgorithm;
  }
  
  public byte[] getEncryptedData()
  {
    return this.encryptedData;
  }
}
  
