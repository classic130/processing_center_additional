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
import java.util.Iterator;

//JCSI
import com.dstc.security.asn1.Asn1;
import com.dstc.security.asn1.Asn1Exception;
import com.dstc.security.asn1.Sequence;
import com.dstc.security.asn1.Oid;
import com.dstc.security.common.OID;

/**
 * Class representing PolicyQualifierInfo in Certificate Policies Extension
 *
 * <pre>
 *   PolicyQualifierInfo ::= SEQUENCE {
 *      policyQualifierId  PolicyQualifierId,
 *      qualifier          ANY DEFINED BY policyQualifierId
 *   }
 *
 *   PolicyQualifierId ::= OBJECT IDENTIFIER ( id-qt-cps | id-qt-unotice )
 *
 *   Qualifier ::= CHOICE {
 *      cPSuri       CPSuri,
 *      userNotice   UserNotice }
 *     
 * </pre> 
 *
 * @see com.dstc.security.x509.extns.CPSuri
 * @see com.dstc.security.x509.extns.UserNotice
 *
 * @author Eddy Cheung
 * @author Ming Yung
 */
public class PolicyQualifierInfo
{
  //Asn1
  private Asn1 asn1;
  //Cert Policy Qualifier Id
  private String qualifierIdentifier;
  //policyQualifier
  private Qualifier policyQualifier;
  
  /**
   * Construct PolicyQualifierInfo using Oid and a Qualifier
   */
  public PolicyQualifierInfo(String qualifierId,
                           Qualifier qualifier)
  {
    this.asn1 = new Sequence();
    
    //qualifierId
    this.qualifierIdentifier = qualifierId;
    this.asn1.add(new Oid(qualifierId));

    //Qualifier
    this.policyQualifier = qualifier;
    this.asn1.add(qualifier.getAsn1());
  }

  /**
   * Construct a PolicyQualifierInfo from Asn1
   */
  public PolicyQualifierInfo(Asn1 asn1) throws Asn1Exception
  {
    this.asn1 = asn1;

    Iterator i = asn1.components();

    //QualifierIdentifier
    this.qualifierIdentifier = ((Oid)i.next()).getOid();

    //PolicyQualifiers
    if (this.qualifierIdentifier.equals(OID.qt_cps)) {
      this.policyQualifier = new CPSuri((Asn1)i.next());
    } else if (this.qualifierIdentifier.equals(OID.qt_unotice)) {
      this.policyQualifier = new UserNotice((Asn1)i.next());
    } else {
      // All other unknown qualifierIdentifier's will be treated as
      //
      this.policyQualifier = new UnknownPQ((Asn1)i.next());
    }
  }

  /**
   * Return Asn1 Object for this object
   **/
  public Asn1 getAsn1()
  {
    return this.asn1;
  }


  /**
   * Return the Policy Qualifier Identifier (OID) as String
   **/
  public String getQualifierIdentifier()
  {
    return this.qualifierIdentifier;
  }

  /**
   * Return the qualifier
   **/
  public Qualifier getQualifier()
  {
    return this.policyQualifier;
  }

  public String toString()
  {
    StringBuffer sb = new StringBuffer();
    
    //Policy Qualifier Id
    sb.append("  Policy Qualifier Identifier: " 
              + this.qualifierIdentifier + "\n");
    //Qualifier Id
    sb.append("    " +
                 this.policyQualifier.toString());
    return sb.toString();
  }

  private class UnknownPQ extends Qualifier
  {

    UnknownPQ(Asn1 asn1) {
        this.asn1 = asn1;
    }
  
    public String toString() {

      byte[] b=null;
      StringBuffer sb = new StringBuffer();
      try {
          b = this.asn1.getEncoded();
      }
      catch(Asn1Exception e) {
          throw new RuntimeException("Bad DER encoding");
      }
      sb.append("  DER encoding:\n            ");
      for (int i=0; i<b.length; i++)
      {
        if ((i>0) && (i % 20 == 0)) {
            sb.append("\n            ");
        }
        if (b[i] <16 && b[i] >=0) {
          sb.append("0"+java.lang.Integer.toHexString(
                            b[i] & 0xff) + " ");
        }
        else {
          sb.append(java.lang.Integer.toHexString(b[i] & 0xff) + " ");
        }
      }
      return sb.toString();
    } 

  }

}
