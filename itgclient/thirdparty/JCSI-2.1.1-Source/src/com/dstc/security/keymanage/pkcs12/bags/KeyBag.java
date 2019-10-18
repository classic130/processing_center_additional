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
import java.util.NoSuchElementException;
import java.util.Iterator;

import java.security.KeyFactory;
import java.security.NoSuchAlgorithmException;
import java.security.PrivateKey;
import java.security.spec.InvalidKeySpecException;
import java.security.spec.PKCS8EncodedKeySpec;

import com.dstc.security.asn1.Asn1;
import com.dstc.security.asn1.Asn1Exception;
import com.dstc.security.asn1.OctetString;
import com.dstc.security.asn1.Sequence;
import com.dstc.security.common.AlgorithmId;
import com.dstc.security.common.OID;
import com.dstc.security.common.PrivateKeyInfo;
import com.dstc.security.keymanage.debug.Debug;
import com.dstc.security.keymanage.pkcs12.bags.Bag;

/**
 *  A class representing the PKCS#12 ASN.1 KeyBag <p>
 *
 *  <pre>
 *    KeyBag ::= PrivateKeyInfo ::= SEQUENCE {
 *      version             Version,
 *      privateKeyAlgorithm PrivateKeyAlgorithmIdentifier,
 *      privateKey          PrivateKey,
 *      attributes          [0] IMPLICIT Attributes OPTIONAL
 *   }
 *
 *   PrivateKey ::= OCTET STRING
 *   Attributes ::= SET OF Attributes
 *  </pre>
 *
 *  <b>NOTE</b><p>
 *
 *  To avoid confusion with the <code>java.security.PrivateKey</code>
 *  type the <code><i>privateKey</i></code> component is referenced by
 *  the member variable <code>key</code>, and accessed using the
 *  <code>getKey</code> method. <p>
 *
 *  The <code>getPrivateKey</code> method attempts to instantiate a
 *  <code>java.security.PrivateKey</code> object using the algorithm
 *  identified by <code><i>privateKeyAlgorithm</i></code> and the raw
 *  private key bytes. <p>
 */
public class KeyBag implements Bag
{
  private Asn1 asn1;
  private int version = 0;
  private AlgorithmId privateKeyAlgorithm;
  private byte[] key;

  /**
   * Constructs a PrivateKeyInfo from a DER encoding.
   *
   *  @param asn1 An ASN.1 encoding of a KeyBag/PrivateKeyInfo object.
   *  @throws Asn1Exception If asn1 is not a valid representation of a KeyBag.
   */
  public KeyBag( Asn1 asn1 ) throws Asn1Exception
  {
    Debug.dumpAsn1To( asn1, Debug.KEYBAG );
  
    this.asn1 = asn1;

    Iterator it = asn1.components();
    try
    {
      this.version = ((com.dstc.security.asn1.Integer)it.next()).getInt();
      this.privateKeyAlgorithm = new AlgorithmId((Asn1)it.next());
      // throws IOException

      OctetString oct = (OctetString) it.next();
      this.key = oct.getBytes();
    }
    catch ( NoSuchElementException ex ) {
      throw new Asn1Exception( "Invalid KeyBag ASN.1" );
    }
    catch ( ClassCastException ex ) {
      throw new Asn1Exception( "Invalid KeyBag ASN.1" );
    }
    //catch ( IOException ex ) {
    //  throw new Asn1Exception( "Invalid KeyBag ASN.1 (OID)" );
    //}
  }
  
  /*
   *  Constructs a PrivateKeyInfo from an AlgorithmId and encoded key. <p>
   *
   *  @param algorithmId OID of the algorithm used to make
   *                     <code>privatekey</code>.
   *  @param privatekey The PKCS#8 encoded form of a private key.
   */
  public KeyBag( AlgorithmId algorithmId, byte[] privatekey )
  {
    this.privateKeyAlgorithm = algorithmId;
    this.key = privatekey;

    this.asn1 = new Sequence();
    this.asn1.add( new com.dstc.security.asn1.Integer( this.version ) );
    this.asn1.add( this.privateKeyAlgorithm.getAsn1() );
    
    OctetString oct = new OctetString( this.key );
    this.asn1.add( oct );
  }

  /**
   *  Returns the Bag Type of this Bag. <p>
   */
  public String getType()
  {
    return OID.keyBag;
  }

  /**
   *  Get the ASN.1 representation of this KeyBag. <p>
   *
   *  @return an Asn1 object that represents this KeyBag.
   */
  public Asn1 getAsn1()
  {
    return this.asn1;
  }

  /**
   *  Returns the AlgorithmId of the algorithm used to make
   *  the private key. <p>
   *
   *  @return an AlgorithmId object.
   */
  public AlgorithmId getPrivateKeyAlgorithm()
  {
    return this.privateKeyAlgorithm;
  }

  /**
   *  this just returns the raw key bytes
   *  (as defined in pkcs1 etc). You probably would never use this
   */
  public byte[] getKey()
  {
    return this.key;
  }

  /**
   *  Attempts to instantiate a PrivateKey from using the AlgorithmId and
   *  raw key bytes. <p>
   *
   *  @return an abstract PrivateKey.
   *  @throws InvalidKeySpecException If this KeyBag does not contain a valid
   *                                  Key.
   *  @throws NoSuchAlgorithmException If the algorithm of this private key
   *                                   is not supported.
   */
  public PrivateKey getPrivateKey()
  throws InvalidKeySpecException, NoSuchAlgorithmException
  {
    // This class is already a PrivateKeyInfo
    byte[] b = null; 
    try {
        b = asn1.getEncoded();
    }
    catch(Asn1Exception e) {
        throw new InvalidKeySpecException(e.getMessage());
    }
    PKCS8EncodedKeySpec keySpec = new PKCS8EncodedKeySpec(b);
    String name = OID.getAlgName( this.privateKeyAlgorithm.getOid() );
    KeyFactory factory = KeyFactory.getInstance( name );
    // throws NoSuchAlgorithmException.
      
    return factory.generatePrivate( keySpec );
    // throws InvalidKeySpecException.
  }
}
