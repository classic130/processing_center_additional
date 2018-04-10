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

import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.util.Vector;
import java.util.Set;
import java.util.HashSet;
import java.util.Iterator;

import com.dstc.security.asn1.Asn1;
import com.dstc.security.asn1.Asn1Exception;
import com.dstc.security.asn1.Sequence;
import com.dstc.security.keymanage.PKCS8Exception;
import com.dstc.security.keymanage.pkcs7.ContentInfo;
import com.dstc.security.common.OID;
import com.dstc.security.keymanage.debug.Debug;
import com.dstc.security.keymanage.pkcs12.SafeBag;

/**
 * <p>A class representing the PKCS#12 ASN.1 SafeContents
 *
 * <pre>
 *     SafeContents ::= SEQUENCE OF SafeBag
 * </pre>
 *
 * @see com.dstc.security.pkcs12.PFX
 * @see com.dstc.security.cms.ContentInfo
 *
 * @author Daniel Bradley
 */
public class SafeContents
{
  private Asn1 asn1 = null;

  //  Sequence of ContentInfo
  private Vector safeBags = new Vector();

  //---------------------------------------------------------------------------
  //  Construtors
  //---------------------------------------------------------------------------

  public SafeContents() {}

  /**
   *  Constructs SafeContents from a DER encoding
   */
  public SafeContents( Asn1 asn1 ) 
    throws PKCS8Exception, Asn1Exception
  {
    Debug.dumpAsn1To( asn1, Debug.SAFECONTENTS );
    
    this.asn1 = asn1;
    Iterator it = asn1.components();

    while ( it.hasNext() )
    {
      try
      {
        Asn1 bagAsn1 = (Sequence) it.next();
        safeBags.add( new SafeBag( bagAsn1 ) );
      }
      catch(Asn1Exception e) {   // Bad certificate encoding
         // ignore
      }
      catch ( ClassCastException ex ) {
        throw new Asn1Exception( "Invalid SafeBag ASN.1" );
      }
    }
  }

  /**
   *  Instantiates a new SafeContents object that contains all of the bags
   *  passed.
   */  
  public SafeContents( SafeBag[] bags )
  {
    for ( int i=0; i < bags.length; i++ )
    {
      this.safeBags.add( bags[i] );
    }
  }

  //---------------------------------------------------------------------------
  //  Accessor Operations
  //---------------------------------------------------------------------------

  /**
   *  Returns an Asn1 object representing the ASN.1 encoding of this
   *  SafeContents. <p>
   *
   *  @return an Asn1 object representing a SafeContents.
   */ 
  public Asn1 getAsn1()
  {
    if ( null == this.asn1 )
    {
      this.asn1 = new Sequence();
      Iterator it = this.safeBags.iterator();
      while( it.hasNext() )
      {
        SafeBag bag = (SafeBag) it.next();
        this.asn1.add( bag.getAsn1() );
      }
    }
    return this.asn1;
  }

  /**
   *  Return the OIDs of the SafeBags contained in this SafeContents. <p>
   *
   *  @return A Set of Strings.
   */
  public String[] getSafeBagIds()
  {
    HashSet set = new HashSet();
    Iterator it = safeBags.iterator();
    while (it.hasNext())
    {
      SafeBag safebag = (SafeBag) it.next();
      set.add( safebag.getBagId() );
    }

    String[] ids = new String[ set.size() ];
    ids = (String[]) set.toArray( ids );

    return ids;
  }

  /**
   *  Returns an array of Strings containing the friendly-name of every
   *  Safe Bag contained within this SafeContents. <p>
   *
   *  @return A String[], possibly empty.
   */
  public String[] getFriendlyNames()
  {
    int size = safeBags.size();
    String[] names = new String[ size ];

    SafeBag bag = null;
    for ( int i=0; i < size; i++ )
    {
      bag = (SafeBag) safeBags.get( i );
      names[ i ] = bag.getFriendlyName();
    }
    return names;
 }

  /**
   *  Return all the SafeBags contained in this SafeContents. <p>
   *
   *  @return A Vector of SafeBags.
   */
  public SafeBag[] getAllSafeBags()
  {
    SafeBag[] bags = new SafeBag[ this.safeBags.size() ];
    this.safeBags.copyInto( bags );
    return bags;
  }

  /**
   *  Returns the Number of SafeBags contained in this SafeContents. <p>
   *
   *  @return Number of Bags.
   */
  public int size()
  {
    return this.safeBags.size();
  }

  /**
   *  Returns all the bags contained by this SafeContents that have a
   *  matching friendly-name attribute. <p>
   *
   *  @friendlyName the friendlyName that is looked for.
   *  @return A possibly empty Vector of SafeBags.
   */

  public SafeBag[] getSafeBags( String friendlyName )
  {
    Vector bags = new Vector();
  
    Iterator it = safeBags.iterator();
    while ( it.hasNext() )
    {
      SafeBag bag = (SafeBag) it.next();
      if ( bag.getFriendlyName().equals( friendlyName ) )
      {
        bags.add( bag );
      }
    }

    SafeBag[] array = new SafeBag[ bags.size() ];
    bags.copyInto( array );
    return array;
  }

  //---------------------------------------------------------------------------
  //  Operations
  //---------------------------------------------------------------------------

  /**
   *  Adds a SafeBag to the end of this SafeContents. <p>
   *
   *  @param The SafeBag to add.
   */
  public void add( SafeBag safeBag )
  {
    this.asn1 = null;
    this.safeBags.add( safeBag );
  }

  /**
   *  Adds a SafeBag to this SafeContenst as the specified posn. <p>
   *
   *  @param posn The posn to add the SafeBag.
   *  @param safeBag The SafeBag to add.
   */
  public void add( int posn, SafeBag safeBag ) throws IndexOutOfBoundsException
  {
    this.asn1 = null;
    this.safeBags.add( posn, safeBag );
  }

  /**
   *  Removes the SafeBag located at the specified posn. <p>
   *
   *  @param posn The posn to remove the SafeBag from.
   *  @return A SafeBag.
   */
  public SafeBag remove( int posn ) throws IndexOutOfBoundsException
  {
    this.asn1 = null;
    return (SafeBag) this.safeBags.remove( posn );
  }

  /**
   *  Removes all SafeBag objects from this SafeContents that have a
   *  matching FriendlyName. <p>
   *
   *  @param friendlyName Representing the friendlyName of the SafeBag
   *                      objects to remove.
   *  @return An arrya of SafeBag objects, possibly empty.
   */
  public SafeBag[] removeSafeBags( String friendlyName )
  {
    // Get reference to the SafeBag to remove, then remove from safeBags.
    //
    SafeBag[] bags = getSafeBags( friendlyName );

    if ( bags.length > 0 )
    {
      this.asn1 = null;
      for ( int i=0; i < bags.length; i++ )
      {
        this.safeBags.remove( bags[i] );
      }
    }
    return bags;
  }
}
