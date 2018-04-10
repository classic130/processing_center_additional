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

import java.util.Iterator;
import java.util.NoSuchElementException;

import com.dstc.security.asn1.Asn1;
import com.dstc.security.asn1.Asn1Exception;
import com.dstc.security.asn1.OctetString;
import com.dstc.security.asn1.Sequence;
import com.dstc.security.keymanage.debug.Debug;
import com.dstc.security.keymanage.pkcs7.DigestInfo;
import com.dstc.security.keymanage.pkcs12.InvalidFlagException;

/**
 * A class representing the PKCS#12 ASN.1 structure PFX's MacData Syntax. <p>
 *
 * <pre>
 *    MacData ::= SEQUENCE {
 *      mac  DigestInfo,
 *      macSalt OCTET STRING,
 *      iterations INTEGER DEFAULT 1
 *      --Note.  In the PKCS#12 2nd Draft, it said that certain Micro$oft
 *      --product must have the value of 1. ie. they are busted.
 *      --Also for netscape generated pkcs12 files, they don't have iteration
 *    }
 *
 *    DigestInfo ::= SEQUENCE {
 *      digestAlgorithm DigestAlgorithmIdentifier,
 *      digest Digest
 *    }
 *
 *    DigestAlgorithmIdentifier ::= AlgorithmIdentifier
 *    Digest ::= OCTET STRING
 * </pre>
 *
 * @see com.dstc.security.pkcs12.PFX
 * @see com.dstc.security.pkcs7.DigestInfo
 *
 * @version 0.1, 2000/03/01
 * @author Daniel Bradley (based on class by Eddie Cheung).
 */
public class MacData
{
  private Asn1 asn1;

  private DigestInfo mac;
  private byte[] macSalt;
  private int iterations = 1;
  private boolean explicit;

  /**
   *  Creates a MacData object using the passed parameters. <p>
   *
   *  @param mac A DigestInfo object.
   *  @param macSalt A byte[] representing the salt used to produce this MAC.
   *  @param iterations The number of iterations during creation of MAC.
   */
  public MacData( DigestInfo mac, byte[] macSalt, int iterations )
  {
    this( mac, macSalt, iterations, true );
  }

  /**
   *  Creates a MacData object using the passed parameters. <p>
   *
   *  @param mac A DigestInfo object.
   *  @param macSalt A byte[] representing the salt used to produce this MAC.
   *  @param iterations The number of iterations during creation of MAC.
   *  @param explicit Whether to explicity encode "1" or not.
   */
  public
  MacData( DigestInfo mac, byte[] macSalt, int iterations, boolean explicit )
  {
    this.mac = mac;
    this.macSalt = macSalt;
    this.iterations = iterations;
    this.explicit = explicit;
  }
  
  /**
   *  Creates a MacData object from the DER encoding. <p>
   *
   *  @param asn1 An Asn1 object that represents a MacData object.
   *  @throws Asn1Exception If asn1 is invalid.
   */
  public MacData( Asn1 asn1 ) throws Asn1Exception
  {
    Debug.log( Debug.DEBUG, "MacData( Asn1 )", "" );
    Debug.dumpAsn1To( asn1, Debug.MACDATA );
  
    try
    {
      Iterator it = asn1.components();
      Sequence di = (Sequence) it.next(); // throws NoSuchElementException
      this.mac = new DigestInfo( di );

      OctetString salt = (OctetString) it.next(); // throws NSEE
      this.macSalt = salt.getBytes();
      
      if ( it.hasNext() )
      {
        com.dstc.security.asn1.Integer number =
            (com.dstc.security.asn1.Integer) it.next();
        this.iterations = number.getInt();
        this.explicit = true;
      }
    }
    catch ( ClassCastException ex )
    {
      throw new Asn1Exception( "Incomplete MacData ASN.1" );
    }
    catch ( NoSuchElementException ex ) {
      throw new Asn1Exception( "Incomplete MacData ASN.1" );
    }
  }   

  public Asn1 getAsn1()
  {
    if ( null == this.asn1 )
    {
      this.asn1 = new Sequence();
      this.asn1.add( this.mac.getAsn1() );
      this.asn1.add( new OctetString( macSalt ) );
      if ( this.explicit || ( iterations != 1 ) )
      {
        this.asn1.add( new com.dstc.security.asn1.Integer( iterations ) );
      }
    }
    return this.asn1;
  }
  
  public DigestInfo getMac()
  {
    return this.mac;
  }
  
  public byte[] getMacSalt()
  {
    return this.macSalt;
  }
  
  public int getIterations()
  {
    return this.iterations;
  }
}
