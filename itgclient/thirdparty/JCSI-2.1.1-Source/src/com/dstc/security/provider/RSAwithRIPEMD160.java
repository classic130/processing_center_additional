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

package com.dstc.security.provider;

import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.security.ProviderException;

import com.dstc.security.common.OID;

/**
 * <p>Implements the RIPEMD-160_with_RSA signature algorithm.
 *
 * @see com.dstc.security.provider.RSAwithAnyMD
 * @see java.security.Signature
 *
 * @version 0.98, 98/07/01
 * @author Ming Yung
 */
public final class RSAwithRIPEMD160 extends RSAwithAnyMD 
{
  public RSAwithRIPEMD160() 
  {
    mdOid = OID.ripemd_160;
    try 
    {
      md = MessageDigest.getInstance("RIPEMD-160");
    } 
    catch(NoSuchAlgorithmException e)
    {
      throw new RuntimeException("Internal error: " + e.getMessage());
    }
  }

  protected String getAlgorithm()
  {
    return "RIPEMD-160withRSA";
  }
}


