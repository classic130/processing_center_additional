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
//      Email: enquiries@dstc.edu.au
// 
// This software is being provided "AS IS" without warranty of
// any kind.  In no event shall DSTC Pty Ltd be liable for
// damage of any kind arising out of or in connection with
// the use or performance of this software.
// 
//////////////////////////////////////////////////////////////////////////// 

package com.dstc.security.asn1;

import java.io.*;

/**
 * <p>A class representing the ASN.1 type UTF8String.
 *
 * @see com.dstc.security.asn1.Asn1
 *
 * @version 0.98, 98/07/01
 * @author Ming Yung
 */
public class UTF8String extends Asn1String
{
  public UTF8String() 
  {
    super();
    this.tag = TAG_UTF8STRING;
    this.stringType = "UTF8";
  }

  public UTF8String(String str)
  {
    super(str);
    this.tag = TAG_UTF8STRING;
    this.stringType = "UTF8";
  }
}
