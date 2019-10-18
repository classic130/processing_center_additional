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

package com.dstc.security.common;

import java.security.Key;
import java.security.MessageDigest;
import java.security.spec.AlgorithmParameterSpec;
import java.security.InvalidKeyException;
import java.security.InvalidAlgorithmParameterException;


/**
 * <p>An interface define the method for deriving keys
 *
 * @see com.dstc.security.provider.PKCS12KeyDerivation
 * @see com.dstc.security.provider.PKCS5KeyDerivation
 *
 * @version 0.98, 99/06/26
 * @author Eddy Cheung
 */
public interface PBEKeyDerivation
{
  public final static int GENERATE_KEY_MODE = 1;
  public final static int GENERATE_IV_MODE = 2;
  public final static int GENERATE_INTEGRITY_KEY_MODE = 3;

  public byte[] generateKey(int opmode, MessageDigest md, Key key, 
                            AlgorithmParameterSpec params, int keyLen)
    throws InvalidKeyException, InvalidAlgorithmParameterException;
}
