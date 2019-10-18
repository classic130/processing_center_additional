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

import java.io.*;
import java.util.Set;
import java.util.HashSet;
import java.util.Iterator;
import java.util.Vector;

import com.dstc.security.asn1.*;

/**
 * <p>A class representing the x.509 ASN.1 structure Extensions
 *
 * @version 0.98, 98/07/01
 * @author Ming Yung
 */
public class Extensions
{
  private Asn1 asn1 = null;

  private Vector extns = null;

  public Extensions(InputStream is) throws IOException, Asn1Exception
  {
    this(Asn1.getAsn1(is));
  }

  /**
   * Default Constructor
   */

  public Extensions() {}

  /**
   * Constructs an Extensions object from given Set of extensions
   */
  public Extensions(Vector extns)
  {
    this.asn1 = new Sequence();
    this.extns = extns;

    Iterator it = extns.iterator();
    while (it.hasNext())
    {
      this.asn1.add(((Extension)it.next()).getAsn1());
    }
  }

  /**
   * Constructs an Extensions from a DER encoding
   */
  public Extensions(Asn1 asn1) throws Asn1Exception
  {
    if (asn1 == null)
      throw new Asn1Exception("null asn1");

    this.asn1 = asn1;

    Iterator it = asn1.components();

    this.extns = new Vector();
    while (it.hasNext())
    {
      Asn1 next = (Asn1)it.next();
      if (next == null) break;

      //extns.add(ExtensionFactory.getExtension(next));
      extns.add(new Extension(next));
    }
  }

  public Asn1 getAsn1()
  {
    return this.asn1;
  }

  public Vector getExtensions()
  {
      return this.extns;
  }

  public void addExtension(Extension ex) 
  {
      if (this.extns == null) {
          this.extns = new Vector();
      }
      this.extns.add(ex);
  }

  public Set getCriticalOIDs()
  {
    HashSet retval = new HashSet();
    Iterator it = extns.iterator();
    while (it.hasNext())
    {
      Extension extn = (Extension)it.next();
      if (extn.isCritical())
      {
        retval.add(extn.getExtnID());
      }
    }
    return retval;
  }

  public Set getNonCriticalOIDs()
  {
    HashSet retval = new HashSet();
    Iterator it = extns.iterator();
    while (it.hasNext())
    {
      Extension extn = (Extension)it.next();
      if (!extn.isCritical())
      {
        retval.add(extn.getExtnID());
      }
    }
    return retval;
  }

  public byte[] getValue(String oid)
  {
    try
    {
      Iterator it = extns.iterator();
      while (it.hasNext())
      {
        Extension extn = (Extension)it.next();
        if(extn.getExtnID().equals(oid))
          return extn.getExtnValue().getEncoded();
      }

      return null;
    }
    catch (Asn1Exception e)
    {
        throw new RuntimeException("bad encoding");
    }
  }

  public String toString()
  {
    StringBuffer retval = new StringBuffer();

    Iterator it = extns.iterator();
    while (it.hasNext())
    {
      retval.append(((Extension)it.next()).toString());
    }
    return retval.toString();
  }
}
