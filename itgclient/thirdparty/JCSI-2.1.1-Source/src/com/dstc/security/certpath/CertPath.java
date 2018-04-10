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

package com.dstc.security.certpath;

import java.util.Vector;
import java.security.PublicKey;
import java.security.cert.X509Certificate;

public class CertPath
{
  private X509Certificate[] path;

  CertPath(X509Certificate[] path)
  {
    this.path = (X509Certificate[])path.clone();
  }

  /**
   * Returns the X509Certificate Path for this CertPath,
   * starting with the signer cert
   */
  public X509Certificate[] getPath()
  {
    return this.path;
  }

  /**
   * Returns the signer cert for this CertPath
   */
  public PublicKey getValidatedPublicKey()
  {
    return path[0].getPublicKey();
  }
}
