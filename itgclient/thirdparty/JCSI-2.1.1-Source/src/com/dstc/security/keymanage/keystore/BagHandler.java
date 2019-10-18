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

package com.dstc.security.keymanage.keystore;

import java.io.PrintStream;
import com.dstc.security.asn1.Asn1DecodingException;
import com.dstc.security.asn1.Asn1Exception;
import com.dstc.security.keymanage.pkcs12.AuthenticatedSafe;
import com.dstc.security.keymanage.pkcs12.SafeBag;

/**
 *  This class provides a more usable interface to the AuthenticatedSafe
 *  class. <p>
 *
 *  This class provides search for, add, and remove SafeBags from an
 *  AuthenticatedSafe object. This class also supports methods to decrypt
 *  encrypted SafeContents, or open enveloped SafeContents. <p>
 *
 *  This class is implemented (at the expense of efficiency) so as not to
 *  depend on any particular policy regarding how any particular SafeBag
 *  may be stored in an AuthenticatedSafe object. <p>
 *
 *  For more information see the comment for each operation. <p>
 *
 *  @see com.dstc.security.pkcs12.AuthenticatedSafe
 *
 *  @author Daniel Bradley
 */
public interface BagHandler
{
  //---------------------------------------------------------------------------
  //  Import Methods
  //---------------------------------------------------------------------------

  /**
   *  Adds all the SafeContents objects held in the authenticatedSafe
   *  object into appropriate Vector objects for convenience. <p>
   *
   *  @param authSafe
   *  @throws Asn1DecodingException If ContentInfo contents is invalid ASN.1.
   *  @throws Asn1Exception If authSafe contains invalid ContentInfo objects.
   */
  public void
  importBags( AuthenticatedSafe authenticatedSafe )
  throws Asn1DecodingException, Asn1Exception;

  //---------------------------------------------------------------------------
  //  Get Methods
  //---------------------------------------------------------------------------

  /**
   *  Returns a SafeBag object. <p>
   *
   *  If available returns the first SafeBag found that contains a
   *  friendly-name attribute equal to <code>friendlyName</code>; if such
   *  SafeBag cannot be found null is returned.
   *
   *  Note that an alias is often associated with more than one SafeBag. <p>
   *
   *  @see getBags( String friendlyName )
   *
   *  @param friendlyName The alias given to the bag.  
   *  @return The first SafeBag found that matches that alias, else null.
   */
  public SafeBag getBag( String friendlyName );
  
  /**
   *  Unlike <code>getBag( String )</code> this method will search for all
   *  bags that have the same friendlyName. <p>
   */
  public SafeBag[] getBags( String friendlyName );

  /**
   *  Returns all the unencrypted Bags managed by this BagHandler. <p>
   *
   *  @return An array of SafeBag objects.
   */
  public SafeBag[] getAllBags();
  
  /**
   *  Retrieves a SafeBag from an encrypted SafeContents. <p>
   *
   *  @param alias The alias given to the bag.
   *  @param pbekey The PBEKey used to decrypt the SafeContents. <p>
   */
  //  public SafeBag getBag( String alias, PBEKey pbeKey );
  
  /**
   *  Retrieves a SafeBag from an enveloped SafeContents. <p>
   *
   *  @param alias The alias given to the bag.
   *  @param privateKey The key to decrypt the SafeContents with.
   */
  //  public SafeBag getBag( String alias, PrivateKey privateKey );

  //---------------------------------------------------------------------------
  //  Set Methods
  //---------------------------------------------------------------------------

  public void setPassword( char[] passwd );

  //---------------------------------------------------------------------------
  //  Store Methods
  //---------------------------------------------------------------------------

  /**
   *  Stores a bag into a newly created SafeContents object. <p>
   *
   *  @param safeBag The SafeBag to add.
   */
  public void storeBag( SafeBag safeBag );

  /**
   *  Stores a group of Safe Bags into a new SafeContents object. <p>
   *
   */
  public void storeBags( SafeBag[] safeBags );

  //---------------------------------------------------------------------------
  //  Remove Methods
  //---------------------------------------------------------------------------

  public void removeBags( String friendlyName );
  
  /**
   *  Removes all bags that match both <code>bagId</code> and
   *  <code>friendlyName</code>. <p>
   */
  public void removeBags( String bagId, String friendlyName );

  //---------------------------------------------------------------------------
  //  Queries
  //---------------------------------------------------------------------------
  
  /**
   *  Returns all of the friendly names of SafeBags that can be found within
   *  this BagHandler. <p>
   *
   *  NOTE that this method has no way of determining the friendly-names
   *  of SafeBags that have been placed in an encrypted/enveloped
   *  SafeContents object. <p>
   *
   *  @return A Vector of friendly-names as String objects.
   */
  public String[] getAllFriendlyNames();

  /**
   *  Returns the the number of bags contained by unencrypted SafeContents
   *  objects. <p>
   *
   *  @return an <code>int</code> representing the number of bags.
   */  
  public int size();
  
  public void contents( PrintStream ps );
  
  /**
   *  Packages everything up into an AuthenticatedSafe object. <p>
   *
   *  XXX Does not support enveloping yet. <p>
   */
  public AuthenticatedSafe export();

  /**
   *  Packages everything up into an AuthenticatedSafe object. <p>
   *
   *  Gets all the bags and seperates them into two <b>Safe Contents</b>
   *  objects (depending on type), then encrypts them using 
   *  <code>passwd</code>. <p>
   *
   *  XXX Does not support enveloping yet. <p>
   */
  public AuthenticatedSafe export( String ALGORITHM, char[] passwd );
}
