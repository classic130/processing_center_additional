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
import com.dstc.security.asn1.Asn1;
import com.dstc.security.asn1.IA5String;

/**
 * This is an abstract Class representing of the policyQualifier
 *
 * <pre>
 *    CPSuri ::= IA5String
 * </pre> 
 *
 * @see com.dstc.security.x509.extns.PolicyQualifier
 * @see com.dstc.security.x509.extns.UserNotice
 *
 * @author Eddy Cheung
 * @author Ming Yung
 */
public class CPSuri extends Qualifier
{
  private String uri;

  /**
   * Construct a CPSuri using a URI pointing to CPS
   **/
  public CPSuri(String uri)
  {
    this.uri = uri;
    this.asn1 = new IA5String(uri);
  }

  /**
   * Construct a CPSuri using a DER encoded Asn1
   **/
  public CPSuri(Asn1 asn1)
  {
    this.asn1 = asn1;

    this.uri = ((IA5String)asn1).getString();
  }
   
  /** 
   * Return the URI for the CPS
   **/
  public String getURI()
  {
    return this.uri;
  } 

  /**
   * Return String representation of the Object
   **/
  public String toString()
  {
    return "    CPS URI: " + this.uri + "\n";
  }

}
