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
import java.util.Collection;
import java.util.Iterator;
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
 * <p>Class representing the ASN.1 structure CRLDistributionPoints
 *
 * <pre>
 *     cRLDistributionPoints ::= {
 *         CRLDistPointsSyntax
 *     }
 *
 *     CRLDistPointsSyntax ::= SEQUENCE SIZE( 1..MAX) OF DistributionPoint
 *
 * </pre>
 *
 * @author Eddy Cheung
 */
 
public class CRLDistributionPoints implements ExtensionValue
{
  private Asn1 asn1 = null;

  private Collection distributionPts = null;

  /**
   * Construct CRLDistributionPoints using a collection of DistributionPoints
   **/
/*public CRLDistributionPoints(Collection distPts) throws IOException
  {
    this(false, distPts);
  }*/

  /**
   * Construct CRLDistributionPoints using a collection of DistributionPoints
   *   and specify if this extension is critical
   */
  /*protected CRLDistributionPoints(boolean isCritical, Collection distPts)
    throws IOException
  {

    this.asn1 = new Sequence();

    this.extnID = OID.cRLDistributionPoints;
    this.asn1.add(new Oid(OID.cRLDistributionPoints));
 
    if (isCritical) {
      this.critical = isCritical;
      this.asn1.add(new Boolean(true));
    }

    Sequence seq = new Sequence();
    this.distributionPts = distPts;
    //CRLDistribution Points
    
    Iterator it = distPts.iterator();
    while (it.hasNext()) {
      seq.add(((DistributionPoint)it.next()).getAsn1());
    }

    this.extnValue = new OctetString(seq.encode());
    this.asn1.add(this.extnValue);
  }*/


  /**
   * Constructs a CRLDistributionPoints using DER encoding
   */
  public CRLDistributionPoints(Asn1 asn1) throws Asn1Exception
  {
    this.asn1 = asn1;

    Iterator it = asn1.components();

    //CRLDistributionPoints
    distributionPts = new Vector();
    while (it.hasNext()) {
      distributionPts.add(new DistributionPoint((Asn1)it.next()));
    }
  }

  /**
   * Construct CRLDistributionPoints using a collection of DistributionPoints
   *   and specify if this extension is critical
   */
  public CRLDistributionPoints(Collection distPts)
    throws IOException
  {
    this.asn1 = new Sequence();
 
    this.distributionPts = distPts;
 
    Iterator it = distPts.iterator();
    while (it.hasNext()) {
      this.asn1.add(((DistributionPoint)it.next()).getAsn1());
    }
  }
                                                                                

  /**
   * Return the collection of the DistributionPoints
   **/
  public Collection getDistributionPoints()
  {
    return this.distributionPts;
  }

  /**
   * return a string representation of this object
   **/
  public String toString()
  {
    StringBuffer sb = new StringBuffer();
    sb.append("CRL Distribution Points extension:\n");
    sb.append(this.distributionPts + "\n");
    return sb.toString();
  }

  public byte[] getEncoded() throws Asn1Exception
  {
    return this.asn1.getEncoded();
  }
}
