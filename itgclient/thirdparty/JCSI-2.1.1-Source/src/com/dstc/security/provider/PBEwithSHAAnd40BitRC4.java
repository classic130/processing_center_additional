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

import javax.crypto.Cipher;
import javax.crypto.NoSuchPaddingException;

import com.dstc.security.common.PKCS12KeyDerivation;

/** 
 * <p>An implementation javax.crypto.Cipher for the algorithm described in
 * the PKCS#5 Password-Based Encryption Standard.
 *
 * <p>The relevant Object Identifiers are
 *
 * <p>pkcs-5 OBJECT IDENTIFIER ::=
 *    { iso(1) member-body(2) US(840) rsadsi(113549)
 *        pkcs(1) 5 }
 *  
 * <p>pbeWithMD2AndDES-CBC OBJECT IDENTIFIER ::= { pkcs-5 1 }
 * <p>pbeWithMD5AndDES-CBC OBJECT IDENTIFIER ::= { pkcs-5 3 }
 *  
 * <p>These object identifiers are intended to be used in the
 * algorithm field of a value of type AlgorithmIdentifier. The
 * parameters field of that type, which has the algorithm-
 * specific syntax ANY DEFINED BY algorithm, would have ASN.1
 * type PBEParameter for these algorithms.
 *  
 * <p>This cipher is specified in PKCS#12
 * <p>pkcs-12PbeIds OBJECT IDENTIFIER ::=
 *     { iso(1) memeber-body(2) US(840) rsadsi(113549)
 *  pkcs(1) 12 1}
 * <p>pbeWithSHAAnd128BitRC4   OBJECT IDENTIFIER ::= { pkcs-12PbeIds 1 }
 * <p>pbeWithSHAAnd40BitRC4    OBJECT IDENTIFIER ::= { pkcs-12PbeIds 2 }
 * <p>pbeWithSHAAnd3-KeyTripleDES-CBC OBJECT IDENTIFIER ::= { pkcs-12PbeIds 3 }
 * <p>pbeWithSHAAnd2-KeyTripleDES-CBC OBJECT IDENTIFIER ::= { pkcs-12PbeIds 4 }
 * <p>pbeWithSHAAnd128BitRC2-CBC   OBJECT IDENTIFIER ::= { pkcs-12PbeIds 5 }
 * <p>pbeWithSHAAnd40BitRC2-CBC   OBJECT IDENTIFIER ::= { pkcs-12PbeIds 6 }
 * @see com.dstc.security.provider.PBEParameters
 * @see com.dstc.security.provider.PBEKey
 * @see javax.crypto.Cipher
 *
 * @version 0.98, 98/07/01
 * @author Ming Yung, Eddy Cheung
 */
public final class PBEwithSHAAnd40BitRC4 extends PBECipher
{
  public PBEwithSHAAnd40BitRC4() 
  {
    try 
    {
      cipher = Cipher.getInstance("RC4");
      md = MessageDigest.getInstance("SHA");
      algo = "RC4";
      pbeAlgo = "PBEwithSHAand40BitRC4";
      keyLength = 40; 
      deriveKey = new PKCS12KeyDerivation();
    } 
    catch (NoSuchPaddingException e)
    {
      throw new RuntimeException("Internal error: " + e.getMessage());
    }
    catch (NoSuchAlgorithmException e)
    {
      throw new RuntimeException("Internal error: " + e.getMessage());
    }
  }
}
