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

import java.io.IOException;
import java.util.Iterator;
import java.math.BigInteger;

import com.dstc.security.asn1.Asn1;
import com.dstc.security.asn1.Asn1Exception;
import com.dstc.security.asn1.Sequence;
import com.dstc.security.asn1.Integer;
import com.dstc.security.x509.ExtensionValue;

/**
 * <p>Class representing the ASN.1 structure Policy Constraints
 *
 * <pre>
 *     PolicyConstraints ::= SEQUENCE {
 *          requireExplicitPolicy   [0] SkipCerts OPTIONAL,
 *          inhibitPolicyMapping    [1] SkipCerts OPTIONAL
 *     }
 * </pre>
 *
 * @author Eddy Cheung
 */ 
public class PolicyConstraints implements ExtensionValue
{
  private Asn1 asn1 = null;

  //By default, they don't exist. 
  private int requireExplicitPolicy = -1;
  private int inhibitPolicyMapping = -1;


  /**
   * Constructs a PolicyConstraints extension
   * If rePolicy or inhibitMapping is less than zero (0), 
   * then it is assumed that they are not present
   * <B>Note</B>: that at least one of the requireExplicitPolicy or 
   *   inhibitPolicyMapping MUST be present
   */
  public PolicyConstraints(int reqPolicy, int inhibitMapping)
    throws IOException
  {

    //Assertion
    if ((reqPolicy < 0) && (inhibitMapping < 0)) {
      throw new IllegalArgumentException("At least one of the " +
          "requireExplicitPolicy or inhibitPolicyMapping MUST be present");
    }

    this.asn1 = new Sequence();

    //requireExplicitPolicy
    this.requireExplicitPolicy = reqPolicy;
    if (reqPolicy >= 0) {
      com.dstc.security.asn1.Integer i = 
        new com.dstc.security.asn1.Integer(reqPolicy);
      i.setTagClass(Asn1.TAG_CLASS_CONTEXT);
      i.setTagNumber(0);
      this.asn1.add(i);
    }

    //inhibitPolicyMapping
    this.inhibitPolicyMapping = inhibitMapping;
    if (inhibitMapping >= 0) {
      com.dstc.security.asn1.Integer i = 
        new com.dstc.security.asn1.Integer(inhibitMapping);
      i.setTagClass(Asn1.TAG_CLASS_CONTEXT);
      i.setTagNumber(1);
      this.asn1.add(i);
    }
  }

  /**
   * Constructs a PolicyConstraints extension from a DER encoding
   */
  public PolicyConstraints(Asn1 asn1) throws IOException
  {
    this.asn1 = asn1;

    Iterator it = asn1.components();

    //is there any constraint?
    if (!it.hasNext()) {
      //XXX TODO, Jan 1999 Draft did not address if encounter 
      //  a null policy constraints field

      //Right now we will issue a warning..
      //May be we should throw an exception?!
      System.out.println("PolicyConstraints is null sequence");
      
      return;     
    }

    Asn1 comp = (Asn1)it.next();

    //requireExplicitPolicy
    if (comp.getTagNumber() == 0) {
      this.requireExplicitPolicy = (new 
        BigInteger(comp.getValue())).intValue();
      //Anymore?
      if (!it.hasNext()) {
        return;
      }
      comp = (Asn1)it.next();
    } 

    //inhibitPolicyMapping
    if (comp.getTagNumber() == 1) {
        this.inhibitPolicyMapping = (new 
          BigInteger(comp.getValue())).intValue();
        //Anymore?
        if (!it.hasNext()) {
          return;
        }         
    } 

    //Should never reached here!
    throw new IOException("Unknown PolicyConstraints certificate extension");
  }


  /**
   * Return the require explicit mapping path length
   * In the case, where it is absent, it will return negative value
   **/
  public int getRequireExplicitPolicy() 
  {
    return this.requireExplicitPolicy;
  }

  /**
   * Return the inhibit policy mapping path length
   * In the case, where it is absent, it will return negative value
   **/
  public int getInhibitPolicyMapping()
  {
    return this.inhibitPolicyMapping;
  }

  
  /**
   * return a string representation of this object
   **/
  public String toString()
  {
    StringBuffer sb = new StringBuffer();
    sb.append("PolicyConstraints extension:\n");

    //Require Explicit Policy
    if (this.requireExplicitPolicy >= 0) {
      sb.append("  Require Explicit Policy path length = " 
                + this.requireExplicitPolicy + "\n");
    }

    //Inhibit Policy Mapping
    if (this.inhibitPolicyMapping >= 0) {
      sb.append("  Inhibit Policy Mapping path length = " 
                + this.inhibitPolicyMapping + "\n");
    }

    return sb.toString();
  }

  public byte[] getEncoded() throws Asn1Exception
  {
    return asn1.getEncoded();
  }
}
