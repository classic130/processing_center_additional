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

import com.dstc.security.asn1.Asn1;
import com.dstc.security.keymanage.debug.Debug;
import com.dstc.security.keymanage.pkcs12.bags.Bag;

/**
 *  A class that represents an Unknown type of SafeBag. <p>
 *
 *  This class is used to hold a Bag that isn't explicitly supported by this
 *  implementation. <p>
 *
 *  While direct manipulation of these bags will be limited, their contents
 *  may be passed to another mechanism for interpretation. <p>
 *
 *  @see com.dstc.security.pkcs12.SafeBag
 *
 *  @author Daniel Bradley
 */
public class UnknownBag implements Bag
{
  private Asn1 asn1;
  private static String TYPE_ID = "";

  /**
   *  Constructs a KeyBag using a DER encoding. <p>
   *
   *  This constructor takes an ASN1 object that represents an encoded
   *  SafeBag with an unknown bag payload. <p>
   */
  public UnknownBag( Asn1 asn1 )
  {
    Debug.dumpAsn1To( asn1, Debug.UNKNOWNBAG );
    this.asn1 = asn1;
  }
  
  /**
   *  Returns the Asn1 representation of this Bag. <p>
   *
   *  @return an Asn1 object representing this Bag.
   */
  public Asn1 getAsn1()
  {
    return this.asn1;
  }
  
  /**
   *  Returns the Bag-type Oid that identifies the type of this Bag. <p>
   *
   *  @return an empty String.
   */
  public String getType()
  {
    return TYPE_ID;
  }
}
