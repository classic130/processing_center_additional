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

import com.dstc.security.asn1.Asn1;
import com.dstc.security.asn1.Asn1Exception;
import com.dstc.security.asn1.Oid;
import com.dstc.security.asn1.Sequence;
import com.dstc.security.asn1.OctetString;
import com.dstc.security.common.OID;
import com.dstc.security.x509.ExtensionValue;

/**
 * Class representing the ASN.1 structure structure SubjectKeyIdentifier.
 *
 * <pre>
 *  SubjectKeyIdentifier ::= KeyIdentifier
 *
 *  KeyIdentifier ::= OCTET STRING
 * </pre>
 * @author Ming Yung
 */
public class SubjectKeyIdentifier implements ExtensionValue
{
  private byte[] keyId;
  private Asn1 asn1;

  /**
   * Constructs a SubjectKeyIdentifier extension (non-critical).
   */
  public SubjectKeyIdentifier(boolean dummy, byte[] keyId)
    throws Asn1Exception, IOException
  {
    this.keyId = keyId;
    this.asn1 = new OctetString(keyId);
  }

  /**
   * Constructs a SubjectKeyIdentifier extension from a DER encoding
   */
  public SubjectKeyIdentifier(Asn1 asn1) 
    throws Asn1Exception, IOException
  {
    this.asn1 = asn1;

    this.keyId = ((OctetString)asn1).getBytes();
  }

    public SubjectKeyIdentifier(byte[] keyId) 
    throws Asn1Exception, IOException
  {
    this.keyId = keyId;
    this.asn1 = new OctetString(keyId);
  }

/*private void decodeFromValue(byte[] val) 
    throws Asn1Exception, IOException
  {
    this.extnValue = (OctetString)Asn1.getAsn1(val);
    this.keyId 
      = ((OctetString)
         OctetString.getAsn1(this.extnValue.getBytes())).getBytes();
  }*/

  public byte[] getEncoded() throws Asn1Exception
  {
    return this.asn1.getEncoded();
  }

  /**
   * Returns the keyID for this SubjectKeyIdentifier extension
   */
  public byte[] getKeyID()
  {
    return this.keyId;
  }

  public String toString()
  {
    StringBuffer sb = new StringBuffer();

    sb.append("SubjectKeyIdentifier extension:\n");
    sb.append("  " + com.dstc.security.x509.Extension.printHex(this.keyId));
    return sb.toString();
  }
}
