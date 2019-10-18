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

package com.dstc.security.keymanage.pkcs7;

import java.io.IOException;
import java.util.Iterator;

import com.dstc.security.asn1.Asn1;
import com.dstc.security.asn1.Asn1Exception;
import com.dstc.security.asn1.OctetString;
import com.dstc.security.asn1.Sequence;

import com.dstc.security.keymanage.pkcs7.AlgorithmId;

/**
 *  Represents the PKCS#7 ASN.1 type DigestInfo. <p>
 *
 *  <pre>
 *       DigestInfo ::= SEQUENCE {
 *         digestAlgorithm DigestAlgorithmIdentifier,
 *         digest Digest }
 *
 *       DigestAlgorithmIdentifier ::= AlgorithmIdentifier ::= SEQUENCE {
 *         algorithm  OBJECT IDENTIFIER,
 *         parameters ANY DEFINED BY algorithm OPTIONAL  }
 *                                 -- contains a value of the type
 *                                 -- registered for use with the
 *                                 -- algorithm object identifier value
 *
 *       Digest ::= OCTET STRING
 *
 *  </pre>
 *
 *  @author Daniel Bradley
 */
public class DigestInfo
{
  private Asn1 asn1 = null;
  
  private AlgorithmId digestAlgorithm = null;
  private byte[] digest = null;

  /**
   *  Creates a DigestInfo object from a Digest AlgorithmId and a digest. <p>
   *
   *  @param digestAlgorithm Identifiers algorithm used to produce digest.
   *  @param digest The digest.
   */
  public DigestInfo( AlgorithmId digestAlgorithm, byte[] digest )
  {
    this.digestAlgorithm = digestAlgorithm;
    this.digest = digest;
    
    this.asn1 = new Sequence();
    this.asn1.add( digestAlgorithm.getAsn1() );
    this.asn1.add( new OctetString( digest ) );
  }
  
  /**
   *  Creates a DigestInfo object from a DER encoding. <p>
   *
   *  @param asn1 An Asn1 object that represents a DigestInfo object. <p>
   */
  public DigestInfo( Asn1 asn1 ) throws Asn1Exception
  {
    this.asn1 = asn1;
    
    Iterator it = asn1.components();
    try
    {
      Asn1 digestId = (Asn1) it.next();
      this.digestAlgorithm = new AlgorithmId( digestId );
      OctetString os = (OctetString) it.next();
      this.digest = os.getBytes();
    }
    catch ( ClassCastException ex ) {
      throw new Asn1Exception( "Invalid AlgorithmId ASN.1" );
    }
    //catch ( IOException ioe ) {
    //  throw new Asn1Exception( "Invalid AlgorithmId ASN.1" );
    //}
  }
  
  public Asn1 getAsn1()
  {
    return this.asn1;
  }
  
  public AlgorithmId getDigestAlgorithm()
  {
    return this.digestAlgorithm;
  }
  
  public byte[] getDigest()
  {
    return this.digest;
  }
}
