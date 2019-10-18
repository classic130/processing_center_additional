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

import com.dstc.security.asn1.Asn1;
import com.dstc.security.asn1.Asn1Exception;
import com.dstc.security.asn1.Sequence;
import com.dstc.security.asn1.Oid;
import com.dstc.security.asn1.Boolean;
import com.dstc.security.asn1.OctetString;
import com.dstc.security.common.OID;
import com.dstc.security.x509.ExtensionValue;

/**
 * <p>Class representing the ASN.1 structure Name Constraints
 *
 * <pre>
 *     NameConstraints ::= SEQUENCE {
 *       permittedSubtrees     [0]    GeneralSubtrees OPTIONAL,
 *       excludedSubtrees      [1]    GeneralSubtrees OPTIONAL 
 *     }
 * 
 * </pre>
 *
 * @author Eddy Cheung
 */
 
public class NameConstraints implements ExtensionValue
{
  private Asn1 asn1 = null;

  //By default, they don't exist. 
  private GeneralSubtrees permittedSubtrees = null;
  private GeneralSubtrees excludedSubtrees = null;

  //constant
  private final int PERMITTED_ASN1_TAG = 0;
  private final int EXCLUDED_ASN1_TAG = 1;

  /**
   * Construct a name constraint using permitted an excludedSubtrees
   **/
  /*public NameConstraints(GeneralSubtrees permitted, 
                         GeneralSubtrees excluded) throws IOException
  {
    this(true, permitted, excluded);
  }*/

  /**
   * Construct a Name Constraints using permitted and excludedSubtrees
   * If they are null, then it is assumed that they are not present
   * Note: This extension MUST be critical
   */
  /*protected NameConstraints(boolean isCritical, GeneralSubtrees permitted, 
                            GeneralSubtrees excluded)
    throws IOException
  {

    this.asn1 = new Sequence();

    this.extnID = OID.nameConstraints;
    this.asn1.add(new Oid(OID.nameConstraints));
 
    if (isCritical) {
      this.critical = isCritical;
      this.asn1.add(new Boolean(true));
    }

    Sequence seq = new Sequence();

    //permittedSubtrees
    this.permittedSubtrees = permitted;
    if (permitted != null) {
      //add it into seq
      Asn1 comp = permitted.getAsn1();
      comp.setTagClass(Asn1.TAG_CLASS_CONTEXT);
      comp.setTagNumber(PERMITTED_ASN1_TAG);
      seq.add(comp);
    }

    //excludedSubtrees
    this.excludedSubtrees = excluded;
    if (excluded != null) {
      //add it into seq
      Asn1 comp = excluded.getAsn1();
      comp.setTagClass(Asn1.TAG_CLASS_CONTEXT);
      comp.setTagNumber(EXCLUDED_ASN1_TAG);
      seq.add(comp);
    }

    this.extnValue = new OctetString(seq.encode());
    this.asn1.add(this.extnValue);
  }*/

  /**
   * Construct a Name Constraints using permitted and excludedSubtrees
   * If they are null, then it is assumed that they are not present
   * Note: This extension MUST be critical
   */
  public NameConstraints(GeneralSubtrees permitted, GeneralSubtrees excluded)
    throws IOException
  {
    this.asn1 = new Sequence();
 
    //permittedSubtrees
    this.permittedSubtrees = permitted;
    if (permitted != null) {
      //add it into seq
      Asn1 comp = permitted.getAsn1();
      comp.setTagClass(Asn1.TAG_CLASS_CONTEXT);
      comp.setTagNumber(PERMITTED_ASN1_TAG);
      this.asn1.add(comp);
    }                                                                            
    //excludedSubtrees
    this.excludedSubtrees = excluded;
    if (excluded != null) {
      //add it into seq
      Asn1 comp = excluded.getAsn1();
      comp.setTagClass(Asn1.TAG_CLASS_CONTEXT);
      comp.setTagNumber(EXCLUDED_ASN1_TAG);
      this.asn1.add(comp);
    }
  }                                                                             


  /**
   * Constructs a name constraints using DER encoding
   */
  public NameConstraints(Asn1 asn1) throws Asn1Exception
  {
    this.asn1 = asn1;

    Iterator it = asn1.components();

    //is there any constraint?
    if (!it.hasNext()) {
      //draft 1999, Jan - X.509 profile
      //if no name of the type is in the certifiate, 
      //the certificate is acceptable.
      return;     
    }

    Asn1 comp = (Asn1)it.next();

    //PermittedSubtrees
    if (comp.getTagNumber() == PERMITTED_ASN1_TAG) {
      this.permittedSubtrees = new GeneralSubtrees(comp);
      if (!it.hasNext()) {
        return;
      } else {
        comp = (Asn1)it.next();
      }
    }
        
    //ExcludedSubtrees
    if (comp.getTagNumber() == EXCLUDED_ASN1_TAG) {
      this.excludedSubtrees = new GeneralSubtrees(comp);      
      //Anymore?
      if (!it.hasNext()) {
        return;
      }
    }

    //Should never reached here!
    throw new Asn1Exception("Unknown NameConstraints certificate " 
                          + "extension structure");
  }


  /**
   * Return the permitted subtrees
   * Null will be returned, if permittedSubtrees is not presented
   **/
  public GeneralSubtrees getPermittedSubtrees() 
  {
    return this.permittedSubtrees;
  }

  /**
   * Return the excludedSubtrees
   * Null will be returned, if excludedSubtrees is not presented
   **/
  public GeneralSubtrees getExcludedSubtrees()
  {
    return this.excludedSubtrees;
  }
  
  /**
   * return a string representation of this object
   **/
  public String toString()
  {
    StringBuffer sb = new StringBuffer();
    sb.append("Name Constraints extension:\n");

    //PermittedSubtrees
    if (this.permittedSubtrees != null) {
      sb.append("  Permitted:  " 
                + this.permittedSubtrees.toString() + "\n");
    }

    //ExcludedSubtrees
    if (this.excludedSubtrees != null) {
      sb.append("  Excluded:  " 
                + this.excludedSubtrees.toString() + "\n");
    }

    return sb.toString();
  }

  public byte[] getEncoded() throws Asn1Exception
  {
    return this.asn1.getEncoded();
  }
}
