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

import java.io.IOException;
import java.util.Set;
import java.util.HashSet;
import java.util.Iterator;

import com.dstc.security.asn1.Asn1;
import com.dstc.security.asn1.Asn1Exception;
import com.dstc.security.asn1.Sequence;
import com.dstc.security.asn1.UTCTime;
import com.dstc.security.common.AlgorithmId;
import com.dstc.security.common.X500Name;

/**
 * <p>Inner class representing the ASN.1 structure tbsCertList.
 * <pre>
 * TBSCertList  ::=  SEQUENCE  {
 *     version                 Version OPTIONAL,
 *                             -- if present, must be v2
 *     signature               AlgorithmIdentifier,
 *     issuer                  Name,
 *     thisUpdate              ChoiceOfTime,
 *     nextUpdate              ChoiceOfTime OPTIONAL,
 *     revokedCertificates     SEQUENCE OF SEQUENCE  {
 *         userCertificate         CertificateSerialNumber,
 *         revocationDate          ChoiceOfTime,
 *         crlEntryExtensions      Extensions OPTIONAL
 *                                 -- if present, must be v2
 *         }  OPTIONAL,
 *     crlExtensions           [0]  EXPLICIT Extensions OPTIONAL
 *                                  -- if present, must be v2
 *     }
 * </pre>
 */
public class TbsCertList
{
  protected Asn1 asn1 = null;
  protected int version = 1;
  protected AlgorithmId sigAlgo;
  protected X500Name issuer;
  protected UTCTime thisUpdate;
  protected UTCTime nextUpdate;
  protected Set revCerts;
  protected Extensions extns;

  public TbsCertList()
  {}

  /**
   * Constructs a TbsCertList from a DER encoding
   */
  public TbsCertList(Asn1 asn1) throws Asn1Exception, IOException
  {
    this.asn1 = asn1;
    if (!(asn1 instanceof Sequence))
    {
      throw new Asn1Exception("Bad CRL encoding");
    }

    Iterator it = asn1.components();
    Asn1 comp = (Asn1)it.next();

    try
    {
      this.version 
        = ((com.dstc.security.asn1.Integer)comp).getInt(); 
      comp = (Asn1)it.next();
    }
    catch (ClassCastException e)
    {
      //Ignore
    }
  
    this.sigAlgo = new AlgorithmId(comp);
  
    this.issuer = new X500Name((Asn1)it.next());
  
    this.thisUpdate = (UTCTime)it.next();
  
    if (!it.hasNext()) return;

    comp = (Asn1)it.next();

    try
    {
      this.nextUpdate = (UTCTime)comp;

      if (!it.hasNext()) return;

      comp = (Asn1)it.next();
    }
    catch (ClassCastException e)
    {
      //Ignore
    }
  
    Sequence seq = (Sequence)comp;
    this.revCerts = new HashSet();
    Iterator its = seq.components();
    while (its.hasNext())
    {
      this.revCerts.add(new X509CRLEntry((Asn1)its.next()));
    }
  
    if (!it.hasNext()) return;
    comp = (Asn1)it.next(); 
    
    if (comp.getTagNumber() == 0)
    {
      this.extns = new Extensions((Asn1)comp.components().next());
    }
  }

  public Asn1 getAsn1()
  {
    return this.asn1;
  }

  protected int getVersion()
  {
    return this.version;
  }

  protected AlgorithmId getAlgorithmId()
  {
    return this.sigAlgo;
  }

  protected X500Name getIssuer()
  {
    return this.issuer;
  }

  protected UTCTime getThisUpdate()
  {
    return this.thisUpdate;
  }

  protected UTCTime getNextUpdate()
  {
    return this.nextUpdate;
  }

  protected Set getRevokedCerts()
  {
    return this.revCerts;
  }

  protected Extensions getExtensions()
  {
    return this.extns;
  }
}
