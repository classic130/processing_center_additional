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
import com.dstc.security.asn1.Boolean;
import com.dstc.security.asn1.OctetString;
import com.dstc.security.common.OID;
import com.dstc.security.x509.ExtensionValue;

/**
 * Class representing Extended Key usage extension of X.509 certificate
 *
 * <pre>
 *      certificatePolicies ::= SEQUENCE SIZE (1..MAX) OF PolicyInformation
 *     
 * @see com.dstc.security.x509.extns.PolicyInformation
 * </pre> 
 * @author Eddy Cheung
 * @author Ming Yung
 */
public class CertificatePolicies implements ExtensionValue
{
  private Asn1 asn1 = null;

  private Collection policyInfos;

  /**
   * Construct certificate policies from a collection of PolicyInformation
   * The collection should contains a list of PolicyInformation
   */
  /*public CertificatePolicies(boolean isCritical, Collection policyInfos)
    throws IOException
  {
    this.asn1 = new Sequence();
    
    //OID of this extension
    this.extnID = OID.certificatePolicies;
    this.policyInfos = policyInfos;
    this.asn1.add(new Oid(OID.certificatePolicies));
    //Critical?
    this.critical = isCritical;
    this.asn1.add(new Boolean(isCritical));
    //Extension Values
    Sequence seq = new Sequence();
    Iterator i = policyInfos.iterator();
    while (i.hasNext()) {
      seq.add(((PolicyInformation)i.next()).getAsn1());
    }
    this.extnValue = new OctetString(seq.encode());
    this.asn1.add(this.extnValue);
  }*/

  /**
   * Construct certificate policies from a collection of PolicyInformation
   * The collection should contains a list of PolicyInformation
   */
  public CertificatePolicies(Collection policyInfos)
  {
    this.asn1 = new Sequence();
 
    this.policyInfos = policyInfos;
 
    Iterator i = policyInfos.iterator();
    while (i.hasNext()) {
      this.asn1.add(((PolicyInformation)i.next()).getAsn1());
    }
  }                                                                             

  /**
   * Constructs a CertificatePolicies from a DER encoding
   */
  public CertificatePolicies(Asn1 asn1) throws Asn1Exception
  {
    this.asn1 = asn1;

    Iterator it = asn1.components();
    policyInfos = new Vector();
    while (it.hasNext()) {
      Asn1 pInfo = (Asn1)it.next();
      if (pInfo instanceof com.dstc.security.asn1.Sequence) {
        policyInfos.add(new PolicyInformation(pInfo));
      } else {
        throw new 
          Asn1Exception("Expecting Seq. within CertificatePolicies Extension");
      }
    }
  }

  /**
   * Return a collection of PolicyInformation
   **/
  public Collection getPolicyInformation()
  {
    return policyInfos;
  }

  public String toString()
  {
    StringBuffer sb = new StringBuffer();
    sb.append("Certificate Policies extension:\n");

    Iterator i = policyInfos.iterator();
    
    while (i.hasNext()) {
      sb.append(i.next().toString());
    }
    sb.append("\n");
    return sb.toString();
  }

  public byte[] getEncoded() throws Asn1Exception
  {
    return this.asn1.getEncoded();
  }
}
