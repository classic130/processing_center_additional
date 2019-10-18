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

package com.dstc.security.x509.extns;

//JDK1.2
import java.io.IOException;
import java.util.Collection;
import java.util.Iterator;
import java.util.Vector;

//JCSI
import com.dstc.security.asn1.Asn1;
import com.dstc.security.asn1.Asn1Exception;
import com.dstc.security.asn1.Sequence;

/**
 * This is a Class representing -  GeneralSubTrees
 *
 * <pre>
 *    GeneralSubTrees ::= SEQUENCE SIZE (1..MAX) OF GeneralSubTree
 *
 *    GeneralSubTree ::= SEQUENCE {
 *         base         GeneralName,
 *         minimum  [0] BaseDistance DEFAULT 0,
 *         maximum  [1] BaseDistance OPTIONAL
 *    }
 *
 *    BaseDistance ::= INTEGER (0..MAX)
 * </pre> 
 *
 * @author Eddy Cheung
 */
public class GeneralSubtrees
{
  private Asn1 asn1 = null;
  private Collection subtrees = null;

  /**
   * Construct a GeneralSubtrees from a set of GeneralSubtree
   **/
  public GeneralSubtrees(Collection subtrees)
    throws IOException
  {

    this.asn1 = new Sequence();
    this.subtrees = subtrees;
    
    Iterator i = subtrees.iterator();
    while (i.hasNext()) {
      asn1.add(((GeneralSubtree)i.next()).getAsn1());
    }
  }
        
  /**
   * Construct a GeneralSubtrees from a DER encoded GeneralSubtree
   **/
  public GeneralSubtrees(Asn1 asn1) throws Asn1Exception
  {
    this.asn1 = asn1;
    Iterator i = asn1.components();

    this.subtrees = new Vector();
    while (i.hasNext()) {
      this.subtrees.add(new GeneralSubtree((Asn1)i.next()));
    }
  }

  /**
   * Return the Asn1 encoding of this object
   **/
  public Asn1 getAsn1() 
  {
    return this.asn1;
  }
   
  /** 
   * Return the collection of the subtree
   **/
  public Collection getGeneralSubtree()
  {
    return this.subtrees;
  } 

  /**
   * toString
   **/
  public String toString() 
  {
    return this.subtrees.toString();
  }
}
