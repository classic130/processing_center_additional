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
import java.util.Iterator;
import java.math.BigInteger;
//JCSI
import com.dstc.security.asn1.Asn1;
import com.dstc.security.asn1.Asn1Exception;
import com.dstc.security.asn1.Integer;
import com.dstc.security.asn1.Sequence;
import com.dstc.security.x509.GeneralName;

/**
 * This is a Class representing -  GeneralSubTree
 *
 * <pre>
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
public class GeneralSubtree
{
  private Asn1 asn1 = null;
  private GeneralName base = null;
  private int minBaseDistance = 0;
  //by default this is absent
  private int maxBaseDistance = -1;

  //constant 
  private final int MIN_BASEDISTANCE_ASN1_TAG = 0;
  private final int MAX_BASEDISTANCE_ASN1_TAG = 1;

  /**
   * Construct a GeneralSubtree using base name,
   * the min base distance is defaul to zero (0)
   **/
  public GeneralSubtree(GeneralName base) throws IOException
  {
    this(base, 0);
  }

  /**
   * Construct a GeneralSubtree using base name, and the min base distance
   **/
  public GeneralSubtree(GeneralName base, int minBaseDistance)
    throws IOException
  {
    this(base, minBaseDistance, -1);
  }

  /**
   * Construct a GeneralSubtree using base name, min and max Base distances
   * If max is negative number, then it is assumed that it is not present
   **/
  public GeneralSubtree(GeneralName base, int minBaseDistance, 
                        int maxBaseDistance) throws IOException
  {
    this.asn1 = new Sequence();

    //Base
    this.base = base;
    asn1.add(base.getAsn1());

    //Assertion on minimum base distance
    if (minBaseDistance < 0) {
      minBaseDistance = 0;
    } 

    Asn1 comp;

    //minBaseDistance
    if (minBaseDistance > 0) {
      this.minBaseDistance = minBaseDistance;
      comp = new com.dstc.security.asn1.Integer(this.minBaseDistance);
      comp.setTagClass(Asn1.TAG_CLASS_CONTEXT);
      comp.setTagNumber(MIN_BASEDISTANCE_ASN1_TAG);
      asn1.add(comp);
    }

    //maxBaseDistance
    if (maxBaseDistance > 0) {
      this.maxBaseDistance = maxBaseDistance;
      comp = new com.dstc.security.asn1.Integer(this.maxBaseDistance);
      comp.setTagClass(Asn1.TAG_CLASS_CONTEXT);
      comp.setTagNumber(MAX_BASEDISTANCE_ASN1_TAG);
      asn1.add(comp);
    }    
  }
    
  /**
   * Construct a GeneralSubtree from a DER encoded
   **/
  public GeneralSubtree(Asn1 asn1) throws Asn1Exception
  {
    this.asn1 = asn1;

    Iterator it = asn1.components();

    //name
    this.base = new GeneralName((Asn1)it.next());

    //anymore?
    if (!it.hasNext()) {
      return;
    } 

    Asn1 comp = (Asn1)it.next();
            
    //minBaseDistance
    if (comp.getTagNumber() == MIN_BASEDISTANCE_ASN1_TAG) {
      this.minBaseDistance = (new 
        BigInteger(comp.getValue())).intValue();
      //Anymore?
      if (!it.hasNext()) {
        return;
      } else {
        comp = (Asn1)it.next();
      }
    }    

    //maxBaseDistance
    if (comp.getTagNumber() == MAX_BASEDISTANCE_ASN1_TAG) {
      this.maxBaseDistance = (new
        BigInteger(comp.getValue())).intValue();
      //Anymore?
      if (!it.hasNext()) {
        return;
      }
    }
      
    //Never should reach here
    throw new Asn1Exception("Unknown GeneralSubtree data structure");
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
  public GeneralName getBaseName()
  {
    return this.base;
  } 

  /**
   * toString
   **/
  public String toString() 
  {
    StringBuffer sb = new StringBuffer();
    sb.append("\n    Name: " + this.base.getName() + "\n");
    sb.append("    Min Base Distance: " + this.minBaseDistance + "\n");
    if (maxBaseDistance > 0) {
      sb.append("    Max Base Distance: " + this.maxBaseDistance + "\n");
    }
    return sb.toString();
  }
}
