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

package com.dstc.security.common;

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
 * @version 0.98, 98/07/01
 * @author Ming Yung
 */  
public class AlgorithmId
{
  private Asn1 asn1;
  private String oid = null;
  private AlgorithmParameters params = null;

  public AlgorithmId(String oid)
  {
    this.asn1 = new Sequence();
    this.oid = oid;
    this.asn1.add(new Oid(oid));
    this.asn1.add(new Null());
  }

  public AlgorithmId(String oid, boolean dummy)
  {
    this.asn1 = new Sequence();
    this.oid = oid;
    this.asn1.add(new Oid(oid));
  }

  /**
   * Constructs an AlgorithmID from its oid name and
   * supplied parameters
   */
  public AlgorithmId(String oid, AlgorithmParameters params)
    throws Asn1Exception, IOException
  {
    this.asn1 = new Sequence();

    this.oid = oid;
    this.asn1.add(new Oid(oid));

    this.params = params;

    if (params == null)
      this.asn1.add(new Null());
    else
      this.asn1.add(Asn1.getAsn1(params.getEncoded()));
  }

  public AlgorithmId(InputStream is) 
    throws Asn1Exception, IOException
  {
    this(Asn1.getAsn1(is));
  }

  public AlgorithmId(Asn1 asn1) throws Asn1Exception
  {
    try
    {
      this.asn1 = asn1;
      Iterator it = asn1.components();
  
      this.oid = ((Oid)it.next()).getOid();
     
      if (it.hasNext())
      {
        Asn1 comp = (Asn1)it.next();
  
        if (comp instanceof Null)
        {
          params = null;
          return;
        }
  
        try
        {
          String algoName = OID.getAlgName(oid);
          params = AlgorithmParameters.getInstance(algoName);
          params.init(comp.getEncoded());
        }
        catch (NoSuchAlgorithmException e) 
        {
            params =  null;
            return;
        }
        catch (Exception e)
        {
          throw new Asn1Exception(e.getMessage());
        }
      }
    }
    catch (NoSuchElementException e)
    {
      throw new Asn1Exception("Bad encoding: " + e.getMessage());
    }
    catch (ClassCastException e)
    {
      throw new Asn1Exception("Bad encoding: " + e.getMessage());
    }
    catch (NullPointerException e)
    {  //The Asn1 may not have components, hence could throw a
       // null pointer Exception
      throw new Asn1Exception("Bad encoding: " + e.getMessage());
    }
  }

  public Asn1 getAsn1()
  {
    return this.asn1;
  }

  /**
   * Returns the string represntation of the Object Identifier
   */
  public String getOid()
  {
    return oid;
  }

  /**
   * Returns the parameters associated with this AlgorithmId.
   */
  public AlgorithmParameters getParams()
  {
    return params;
  }
}
