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

import java.security.Key;
import java.security.MessageDigest;
import java.security.spec.AlgorithmParameterSpec;
import java.security.InvalidKeyException;
import java.security.InvalidAlgorithmParameterException;

import javax.crypto.spec.PBEParameterSpec;

import com.dstc.security.common.PBEKeyDerivation;

/**
 * <p>An Implementation of KeyDerivation using PKCS#5 v1.5 described method
 *
 * @see com.dstc.security.provider.PBEKeyDerivation
 *
 * @version 0.98, 99/05/26
 * @author Eddy Cheung
 */

/* Log Message:
 * $Log: PKCS5KeyDerivation.java,v $
 * Revision 1.3  2000/12/19 04:11:05  ming
 * Modifications to use PBE SecretKeyFactorys
 *
 * Revision 1.2  2000/10/04 00:57:45  ming
 * PBEKey & PBEKeyDerivation moved to common
 *
 * Revision 1.1.1.1  2000/06/27 02:56:40  ming
 * Re-organized and re-packaged JCSI for commercial release
 *
 * Revision 1.1  1999/07/06 00:00:34  cheung
 * Ripped KeyDerivation Method specific to PKCS5 from PKCS8 class - EncryptedPrivateKeyInfo
 *
 */
public class PKCS5KeyDerivation implements PBEKeyDerivation
{
  /**
    * Generate Key / IV for PBECipher
    * Mode Supported: GENERATE_KEY_MODE, GENERATE_IV_MODE
    * Key Length expecting 8 bytes
    */
  public byte[] generateKey(int opmode, MessageDigest md, Key key,
                            AlgorithmParameterSpec params, int keyLen) 
    throws InvalidKeyException, InvalidAlgorithmParameterException
  {
    //Assertion
    if (opmode < GENERATE_KEY_MODE || opmode > GENERATE_IV_MODE)
      throw new IllegalArgumentException("Unrecognise or unsupported Mode");
    if (md == null)
      throw new NullPointerException("Message Digest not initialised");

    if (!(key.getAlgorithm().startsWith("PBE")))
    {
      throw new InvalidKeyException ("Not a PBE Key");
    }

    if (!(params instanceof PBEParameterSpec))
    {
      throw new InvalidAlgorithmParameterException("Not PBE parameters");
    }

    if (keyLen != 8)
      throw new IllegalArgumentException ("Expecting Key Length to be 8 bytes");

    byte KeyBytes[] = new byte[keyLen];
    byte pass[] = key.getEncoded ();
    byte salt[] = ((PBEParameterSpec) params).getSalt ();
    int ic = ((PBEParameterSpec) params).getIterationCount ();

    // P || S
    byte data[] = new byte[pass.length + salt.length];
    System.arraycopy (pass, 0, data, 0, pass.length);
    System.arraycopy (salt, 0, data, pass.length, salt.length);

    for (int i = 0; i < ic; i++)
    {
      md.update (data);
      data = md.digest ();
    }

    if (opmode == GENERATE_KEY_MODE)
    {
      System.arraycopy (data, 0, KeyBytes, 0, KeyBytes.length);
    }
    else if (opmode == GENERATE_IV_MODE)
    {
      System.arraycopy (data, data.length - 8, KeyBytes, 0, KeyBytes.length);
    }
    else
    {
      throw new IllegalArgumentException("Unrecogisned or unsupported mode");
    }

    return KeyBytes;
  }

} //...end class declaration
