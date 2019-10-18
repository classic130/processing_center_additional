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

import java.io.InputStream;
import java.io.IOException;
import java.util.Iterator;
import java.util.NoSuchElementException;
import java.security.AlgorithmParameters;
import java.security.NoSuchAlgorithmException;

import com.dstc.security.asn1.Asn1;
import com.dstc.security.asn1.Asn1Exception;
import com.dstc.security.asn1.Sequence;
import com.dstc.security.asn1.Null;
import com.dstc.security.asn1.Oid;
import com.dstc.security.common.OID;

/**
 * <p>A class representing the x.509 ASN.1 structure AlgorithmIdentifier.
 *
 * <pre>
 * AlgorithmIdentifier  ::=  SEQUENCE  {
 *       algorithm               OBJECT IDENTIFIER,
 *       parameters              ANY DEFINED BY algorithm OPTIONAL  }
 *                                  -- contains a value of the type
 *                                  -- registered for use with the
 *                                  -- algorithm object identifier value
 * </pre>
 *
 *  Supports indefinate length encodings. <p>
 */  
public class AlgorithmId
{
  private Asn1 asn1;

  private String algorithm;
  private AlgorithmParameters parameters;
  private Asn1 encodedParameters;

  //---------------------------------------------------------------------------
  //  Constructors
  //---------------------------------------------------------------------------

  public AlgorithmId( Asn1 asn1 )
    throws Asn1Exception //, NoSuchAlgorithmException
  {
    // XXX. Should this be here?
    if ( null == asn1 )
    {
      throw new Asn1Exception( "null AlgorithmId ASN.1" );
    }

    String algorithmName = null;
    try
    {
      Iterator it = asn1.components();
      Oid oid = (Oid) it.next();
      this.algorithm = oid.getOid();
      algorithmName = OID.getAlgName( this.algorithm );

      if ( it.hasNext() )
      {
        Asn1 comp = (Asn1) it.next();

        if ( comp instanceof Null )
        {
          this.parameters = null;
        }
        else
        {
          this.parameters =
              AlgorithmParameters.getInstance( algorithmName );

          //  A question here is that it is only necessary to reencode
          //  "comp" if it is indefinatelength. However (as the comment below
          //  states) if comp is indefinate the next part will fail.
          //  Therefore either we don't really need to reecode "comp" or this
          //  should be fixed so that it won't fail on an indefinate length
          //  encoding.

          //  This will throw an Asn1EncodingException
          //  if comp is indefinate length encoded.
          this.parameters.init( comp.getEncoded() );

          this.encodedParameters = comp;
          //  We eventually need this as an Asn1 for "getAsn1()" but we
          //  do it here so that if the exception is thrown it's thrown
          //  here and not in "getAsn1()".
          //
          //  Having it thrown in "getAsn1()" would change the method
          //  signature.
          this.encodedParameters =
              Asn1.getAsn1( this.parameters.getEncoded() );
        }
      }
    }
    catch ( ClassCastException ex )
    {
      throw new Asn1Exception(
          "Invalid AlgorithmId ASN.1: " + ex.toString() );
    }
    catch ( NoSuchElementException ex )
    {
      throw new Asn1Exception(
          "Incomplete Algorithm ASN.1: " + ex.toString() );
    }
    catch ( NoSuchAlgorithmException ex )
    {
     throw new Asn1Exception(
       ex.toString() + ": " + algorithmName + "(" + this.algorithm + ")" );
    }
    catch ( IOException ex )
    {
      throw new Asn1Exception( ex.toString() );
    }
  }

  public AlgorithmId( String oid )
  {
    this.algorithm = oid;
  }

  public AlgorithmId( String oid, boolean dummy )
  {
    this.algorithm = oid;
    // this.asn1 = new Sequence();
    // this.asn1.add(new Oid(oid));
  }

  /**
   * Constructs an AlgorithmID from its oid name and
   * supplied parameters
   */
  public AlgorithmId( String oid, AlgorithmParameters params )
  throws Asn1Exception, IOException
  {
    this.algorithm = oid;
    this.parameters = params;
    this.encodedParameters = Asn1.getAsn1( this.parameters.getEncoded() );
  }

  public AlgorithmId( InputStream is )
    throws IOException, Asn1Exception, NoSuchAlgorithmException
  {
    this( Asn1.getAsn1( is ) );
  }

  //---------------------------------------------------------------------------
  //  Accessors
  //---------------------------------------------------------------------------

  public Asn1 getAsn1()
  {
    if ( null == this.asn1 )
    {
      this.asn1 = new Sequence();
      this.asn1.add( new Oid( this.algorithm ) );

      if ( null == this.parameters )
      {
        this.asn1.add( new Null() );
      }
      else
      {
        this.asn1.add( this.encodedParameters );
      }
    }
    return this.asn1;
  }

  /**
   * Returns the string represntation of the Object Identifier
   */
  public String getOid()
  {
    return this.algorithm;
  }

  /**
   * Returns the parameters associated with this AlgorithmId.
   */
  public AlgorithmParameters getParams()
  {
    return this.parameters;
  }
}
