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
import java.util.Vector;
import java.util.Iterator;
//import java.util.ListIterator;
import java.util.StringTokenizer;
import java.security.Principal;

import com.dstc.security.asn1.Asn1;
import com.dstc.security.asn1.Asn1Exception;
import com.dstc.security.asn1.Sequence;
import com.dstc.security.asn1.Asn1Exception;

/**
 * <p>An implementation of Principal based on X.500 Names. Name is defined
 * in X.501 and has the ASN.1 structure
 *
 * <pre>
 *    Name            ::=   CHOICE {
 *                         -- only one possibility for now --
 *                            rdnSequence  RDNSequence }
 *
 *  RDNSequence     ::=   SEQUENCE OF RelativeDistinguishedName
 * </pre>
 *
 * @see com.dstc.security.common.RDN
 *
 * @version 0.98, 98/07/01
 * @author Ming Yung
 */
public class X500Name implements Principal
{
  private Asn1 asn1 = null;
  private Vector rdns = new Vector();

  /**
   * Constructor from a string representation of a distinguished name. 
   * The string representation follows a subset of RFC1779. Only
   * ASCII values are allowed. Only "," is allowed as a separator.
   * The representation is in little-endian order (most significant
   * component first). 
   *
   * Eg. "CN=Me, OU=\"My Dept, Inc.\", O=My Company, C=AU"
   */
  public X500Name(String dn)
  {
    this.asn1 = new Sequence();

    StringTokenizer tknz = new StringTokenizer(dn, ",", false);

    String current = tknz.nextToken();
    StringBuffer sb = new StringBuffer(current);
    RDN rdn;

    while (tknz.hasMoreTokens())
    {
      current = dequote(tknz.nextToken());
      if (current.indexOf('=') == -1)
      {
        sb.append(",").append(current);
      }
      else
      {
        rdn = new RDN(sb.toString());
        rdns.add(rdn);
        sb = new StringBuffer(current);
      }
    }
    rdn = new RDN(sb.toString());
    rdns.add(rdn);

    /*for (ListIterator i=rdns.listIterator(rdns.size()); i.hasPrevious(); )
    {
      this.asn1.add(((RDN)i.previous()).getAsn1());
    }*/
    int size = rdns.size();
    for (int i=size-1; i>=0; i--)
    {
      this.asn1.add(((RDN)rdns.elementAt(i)).getAsn1());
    }
  }

  // Get rid of 1st occurrence of \" in a string.
  //

  private String dequote(String s)
  {
    int pos = s.indexOf("\"");
    if (pos == -1)
    {
        return s;
    }
    return s.substring(0, pos) + s.substring(pos+1,s.length()); 
  }

  /**
   * Constructs an X500Name from an InputStream containing
   * a DER encoding of a Name 
   */
  public X500Name(InputStream is) 
    throws Asn1Exception, IOException
  {
    this(Asn1.getAsn1(is));
  }

  /**
   * Constructs an X500Name from a DER encoding of a Name
   */
  public X500Name(byte[] encoded) 
    throws Asn1Exception
  {
    this(Asn1.getAsn1(encoded));
  }

  /**
   * Constructs an X500Name from an Asn1 object representing
   * a Name
   */
  public X500Name(Asn1 asn1) throws Asn1Exception
  {
    if (asn1 == null)
      throw new Asn1Exception("null asn1");

    this.asn1 = asn1;
    
    Iterator it = asn1.components();

    while (it.hasNext())
    {
      Asn1 next = (Asn1)it.next();
      if (next == null) break;

      rdns.add(0, new RDN(next));
    }
  }

  public Asn1 getAsn1()
  {
    return this.asn1;
  }

  /**
   * Returns a Vector of RDNs
   */
  public Vector getRDNs()
  {
    return this.rdns;
  }

  //Methods defined abstract in Principal 

  public int hashCode() 
  {
    return getName().hashCode();
  }

  /**
   * Returns the string representation of the Name
   * per RFC1779
   */
  public String toString() 
  {
    return getName();
  }

  /**
   * Returns the string representation of the Name
   * per RFC1779
   */
  public String getName() 
  {
    StringBuffer st = new StringBuffer();
    for (Iterator i = rdns.iterator(); i.hasNext(); )
    {
      st.append(((RDN)i.next()).getName());
      if (i.hasNext())
        st.append(", ");
    }
    return st.toString();
  }

  public boolean equals(Object another)
  {
    try
    {
      return equals(this, (Principal)another);
    }
    catch (ClassCastException e)
    {
      return false;
    }
  }
 
  /**
   * Determine whether two X.500 names are "the same".  The names are
   * instances of {@link Principal};  they may be {@link X500Name}, but they
   * may also be from different JCE providers (for example, the Sun provider).
   *
   * @param dn1 a <code>Principal</code> representing an X.500
   *            Distinguished Name, or <code>null</code>
   * @param dn2 a <code>Principal</code> representing an X.500
   *            Distinguished Name, or <code>null</code>
   * @return true if the distinguished names are the same;  false otherwise
   */
  public static boolean equals(Principal dn1, Principal dn2)
  {
    if (dn1 == dn2)
    {
      return true;
    }
    else if (dn1 == null || dn2 == null)
    {
      return false;
    }
    else
    {
      // We want to say Yes if the X.500 names are the same, even if they are
      // in Principals from two different JCA providers.  We can't rely on
      // Principal.equals() to "do the right thing" -- we (JCSI X500Name) do
      // but Sun's provider doesn't -- so the best we can do is to get the
      // string representation from both.

      // assert(dn1.getName() != null)
      return dn1.getName().equals(dn2.getName());
    }
  }
}
