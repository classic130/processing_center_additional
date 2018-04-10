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

package com.dstc.security.x509;

import java.util.Vector;
import java.util.Iterator;

import com.dstc.security.asn1.Asn1;
import com.dstc.security.asn1.Asn1Exception;
import com.dstc.security.asn1.Sequence;

/**
 * <p>A class representing x.509 ASN.1 structure GeneralNames.
 * 
 * <pre>
 *     GeneralNames ::= SEQUENCE SIZE (1..MAX) OF GeneralName
 * </pre>
 */
public class GeneralNames
{
  private Asn1 asn1 = null;
  private Vector names;

  /**
   * Constructs a GeneralNames from a Set of GeneralName
   */
  public GeneralNames(Vector names)
  {
    this.asn1 = new Sequence();
    this.names = names;

    Iterator it = names.iterator();
    while (it.hasNext())
    {
      this.asn1.add(((GeneralName)it.next()).getAsn1());
    }
  }

  /** 
   * Add a GeneralName to this GeneralNames
   */
  public void addGeneralName(GeneralName name)
  {
    this.names.add(name);
    this.asn1.add(name.getAsn1());
  }

  /**
   * Constructs a GeneralNames from a DER encoding
   */
  public GeneralNames(Asn1 asn1) throws Asn1Exception
  {
    if (asn1 == null)
      throw new Asn1Exception("null asn1");

    this.asn1 = asn1;

    this.names = new Vector();

    Iterator it = asn1.components();
    while (it.hasNext())
    {
      this.names.add(new GeneralName((Asn1)it.next()));
    }
  }

  /**
   * Returns the Set of GeneralName
   */
  public Vector getNames()
  {
    return this.names;
  }

  public Asn1 getAsn1()
  {
    return this.asn1;
  }
}
