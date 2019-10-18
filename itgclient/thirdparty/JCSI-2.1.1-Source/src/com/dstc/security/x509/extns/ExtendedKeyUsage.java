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
import java.util.Set;
import java.util.HashSet;

import com.dstc.security.asn1.Asn1;
import com.dstc.security.asn1.Asn1Exception;
import com.dstc.security.asn1.Sequence;
import com.dstc.security.asn1.Oid;
import com.dstc.security.asn1.Boolean;
import com.dstc.security.asn1.OctetString;
import com.dstc.security.asn1.BitString;
import com.dstc.security.common.OID;
import com.dstc.security.x509.ExtensionValue;

/**
 * Class representing Extended Key usage extension of X.509 certificate
 *
 * <pre>
 *      ExtKeyUsageSyntax ::= SEQUENCE SIZE (1..MAX) OF KeyPurposeId
 *     
 *      KeyPurposeId ::= OBJECT IDENTIFIER
 *
 * </pre> 
 * @author Eddy Cheung
 * @author Ming Yung
 */
public class ExtendedKeyUsage implements ExtensionValue
{
  private Asn1 asn1 = null;
  private Set extKeyUsages;

  /**
   * Constructs a KeyUsage from the usage
   * usage should contains a set of OID string
   */
  /*public ExtendedKeyUsage(boolean isCritical, Set extUsage) throws IOException
  {
    this.asn1 = new Sequence();
    
    //OID of this extension
    this.extnID = OID.extKeyUsage;
    this.extKeyUsages = extUsage;
    this.asn1.add(new Oid(OID.extKeyUsage));
    //Critical?
    this.critical = isCritical;
    this.asn1.add(new Boolean(isCritical));
    //Extension Values
    Sequence seq = new Sequence();
    Iterator i = extUsage.iterator();
    while (i.hasNext()) {
      seq.add(new Oid((String)i.next()));
    }
    this.extnValue = new OctetString(seq.encode());
    this.asn1.add(this.extnValue);
  }*/

  /**
   * Constructs a KeyUsage from the usage
   * usage should contains a set of OID string
   */
  public ExtendedKeyUsage(Set extUsage) throws IOException
  {
    this.asn1 = new Sequence();
 
    this.extKeyUsages = extUsage;
 
    Iterator i = extUsage.iterator();
    while (i.hasNext()) {
      this.asn1.add(new Oid((String)i.next()));
    }
  }                                                                             

  /**
   * Constructs a ExtendedKeyUsage from a DER encoding
   */
  public ExtendedKeyUsage(Asn1 asn1) throws IOException
  {
    this.asn1 = asn1;

    Sequence seq  = (Sequence)asn1;
    Iterator it = seq.components();
    extKeyUsages = new HashSet();
    while (it.hasNext()) {
      Asn1 oid = (Asn1)it.next();
      if (oid instanceof com.dstc.security.asn1.Oid) {
        extKeyUsages.add(((Oid)oid).getOid());
      } else {
        throw new 
          IOException("Expecting OID within ExtendedKeyUsage cert Extension");
      }
    }
  }

  public String toString()
  {
    StringBuffer sb = new StringBuffer();
    sb.append("Extended KeyUsage extension:\n");

    Iterator i = extKeyUsages.iterator();
    
    while (i.hasNext()) {
      String oid = (String)i.next();
      if (oid.equals(OID.kp_serverAuth)) {
        sb.append("  TLS Web server authentication\n");
      } else if (oid.equals(OID.kp_clientAuth)) {
        sb.append("  TLS Web client Autnentication\n");
      } else if (oid.equals(OID.kp_codeSigning)) {
        sb.append("  Signing of downloadable executable code\n");
      } else if (oid.equals(OID.kp_emailProtection)) {
        sb.append("  E-mail protection\n");
      } else if (oid.equals(OID.kp_timeStamping)) {
        sb.append("  TimeStamping\n");
      } else if (oid.equals(OID.kp_dvcs)) {
        sb.append("  Data Validation and Certification Service\n");
      } else {
        sb.append("  " + oid + "\n");
      }
    }
    sb.append("\n");
    return sb.toString();
  }

  public byte[] getEncoded() throws Asn1Exception
  {
    return this.asn1.getEncoded();
  }
}
