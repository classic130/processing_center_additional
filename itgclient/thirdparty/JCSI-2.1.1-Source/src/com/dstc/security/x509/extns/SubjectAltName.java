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

import java.io.*;
import java.util.Vector;
import java.util.Iterator;

import com.dstc.security.asn1.Asn1;
import com.dstc.security.asn1.Asn1Exception;
import com.dstc.security.asn1.Sequence;
import com.dstc.security.asn1.Oid;
import com.dstc.security.asn1.Boolean;
import com.dstc.security.asn1.OctetString;
import com.dstc.security.common.OID;
import com.dstc.security.x509.ExtensionValue;
import com.dstc.security.x509.GeneralNames;
import com.dstc.security.x509.GeneralName;

/**
 * A class representing the X.509 ASN.1 structure SubjectAltName.
 *
 * <pre>
 *     SubjectAltName ::= GeneralNames
 *
 *     GeneralNames ::= SEQUENCE SIZE (1..MAX) OF GeneralName
 * </pre>
 */
public class SubjectAltName implements ExtensionValue
{
//private String val;     // maybe contains Email
  private Asn1 asn1;
  private Vector altNames;   // Vector of GeneralName - maybe also Email

  /**
   * Constructs a SubjectAltName extension with a single email address
   * (critical).
   */
  /*public SubjectAltName(String email)
    throws Asn1Exception, IOException
  {
    this.asn1 = new Sequence();

    this.extnID = OID.subjectAltName;
    this.asn1.add(new Oid(OID.subjectAltName));

    this.critical = true;
    this.asn1.add(new Boolean(true));

    this.val = email;
    Vector names = new Vector();
    names.add(new GeneralName(GeneralName.RFC822NAME, email));

    this.extnValue 
      = new OctetString((new GeneralNames(names)).getAsn1().getEncoded());
    this.asn1.add(this.extnValue);
  }*/

  public SubjectAltName() {}

  /**
   * Constructs a SubjectAltName extension with a single email address
   * (critical).
   */
  public SubjectAltName(String email)
  {
    if (this.altNames == null) {
        altNames = new Vector();
    }
    altNames.add(new GeneralName(GeneralName.RFC822NAME, email));
 
    this.asn1 = (new GeneralNames(altNames)).getAsn1();
  }                                                                             

  /**
   *  Adds an alternative name to this SubjectAltName extension
   */
  public void addAltName(GeneralName name)
  {
    if (this.altNames ==null) {
        this.altNames = new Vector();
    }
    this.altNames.add(name);

    if (this.asn1 == null) {
        Vector v = new Vector();
        v.add(name);
        this.asn1 = (new GeneralNames(v)).getAsn1();
    }
    else {
//      this.asn1.add(name.getAsn1());
        this.asn1 = (new GeneralNames(altNames)).getAsn1();
    }
  }

  /**
   * Constructs a SubjectAltName from a DER encoding
   */
  public SubjectAltName(Asn1 asn1)
    throws Asn1Exception, IOException
  {
    this.asn1 = asn1;

  /*Iterator it 
      = (new GeneralNames(asn1)).getNames().iterator();
    GeneralName name = (GeneralName)it.next();
    this.val = name.getName(); */
    this.altNames = (new GeneralNames(asn1)).getNames();
  }

  public byte[] getEncoded() throws Asn1Exception
  {
    return this.asn1.getEncoded();
  }

  /**
   * Returns the name in this SubjectAltName
   */
/*public String getName()
  {
    if (this.val != null) {
        return this.val;
    }
    else {
        return null;
    }
  }*/

  public Vector getNames()
  {
    if (this.altNames != null) {
        return this.altNames;
    }
    else {
        return null;
    }
  }

  public String toString()
  {
    StringBuffer sb = new StringBuffer();

    sb.append("SubjectAltName extension:\n");
    if (altNames != null) {
        Iterator i = altNames.iterator();
        while (i.hasNext()) {
            sb.append("  " + ((GeneralName) i.next()).getName() + "\n");
        }
    }

    return sb.toString();
  }
}
