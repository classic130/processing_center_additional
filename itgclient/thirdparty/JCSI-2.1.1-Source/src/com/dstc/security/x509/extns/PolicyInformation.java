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

import java.util.Iterator;
import java.util.Collection;
import java.util.Vector;

import com.dstc.security.asn1.Asn1;
import com.dstc.security.asn1.Asn1Exception;
import com.dstc.security.asn1.Sequence;
import com.dstc.security.asn1.Oid;
import com.dstc.security.common.OID;
import com.dstc.security.x509.Extension;

/**
 * Class representing PolicyInformation in Certificate Policies Extension
 *
 * <pre>
 *   PolicyInformation ::= SEQUENCE {
 *      policyIdentifier  CertPolicyId,
 *      policyQualifiers  SEQUENCE SIZE (1..MAX) OF
 *              PolicyQualifierInfo OPTIONAL }
 *
 *   CertPolicyId ::= OBJECT IDENTIFIER
 *     
 * </pre> 
 *
 * @see com.dstc.security.x509.extns.CertificatePolicies
 *
 * @author Eddy Cheung
 * @author Ming Yung
 */
public class PolicyInformation
{
  //Asn1
  private Asn1 asn1;
  //CertPolicyId
  private String policyIdentifier;
  //policyQualifiers
  private Collection policyQualifiers;
  
  /**
   * Construct a PolicyInformation from CertPolicyId
   */
  public PolicyInformation(String certPolicyId)
  {
    this(certPolicyId, null);
  }

  /**
   * Construct a PolicyInformation from oid and Qualifiers
   * if Qualifiers are NULL, it is assumed that it is no present
   */
  public PolicyInformation(String certPolicyId,
                             Collection policyInfos)
  {
    this.asn1 = new Sequence();
    
    //PolicyId
    this.policyIdentifier = certPolicyId;
    this.asn1.add(new Oid(certPolicyId));

    //policyQualifiers
    if (policyInfos != null) {
      this.policyQualifiers = policyInfos;
      Iterator i = policyInfos.iterator();
      Sequence seq = new Sequence();
      while (i.hasNext()) {
        seq.add(((PolicyQualifierInfo)i.next()).getAsn1());
      }
      this.asn1.add(seq);
    }
  }

  /**
   * Construct a PolicyInformation from Asn1
   */
  public PolicyInformation(Asn1 asn1) throws Asn1Exception
  {
    this.asn1 = asn1;

    Iterator i = asn1.components();

    //PolicyIdentifier
    this.policyIdentifier = ((Oid)i.next()).getOid();

    //PolicyQualifiers
    this.policyQualifiers = new Vector();
    if (i.hasNext()) {
      Iterator comp = ((Sequence)i.next()).components();
      while (comp.hasNext()) {
        this.policyQualifiers.add(new PolicyQualifierInfo((Asn1)comp.next()));
      }
    }
  }

  /**
   * Return the Asn1 encoding for this object
   **/
  public Asn1 getAsn1()
  {
    return this.asn1;
  }


  /**
   * Return the policyIdentifier (OID) as String
   **/
  public String getPolicyIdentifier()
  {
    return this.policyIdentifier;
  }

  /**
   * Return the collections of PolicyQualifiers
   * Note that it could be null
   **/
  public Collection getPolicyQualifiers()
  {
    return this.policyQualifiers;
  }

  public String toString()
  {
    StringBuffer sb = new StringBuffer();
    
    //PolicyId
    sb.append("  Policy Identifier: " + this.policyIdentifier + "\n");

    if (policyQualifiers != null && policyQualifiers.size() > 0) {
      sb.append(policyQualifiers.toString());
    }
    return sb.toString();
  }
}
