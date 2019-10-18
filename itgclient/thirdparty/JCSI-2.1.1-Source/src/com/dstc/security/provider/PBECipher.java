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

import java.security.SecureRandom;
import java.security.Key;
import java.security.AlgorithmParameters;
import java.security.MessageDigest;
import java.security.InvalidKeyException;
import java.security.InvalidAlgorithmParameterException;
import java.security.NoSuchAlgorithmException;
import java.security.spec.AlgorithmParameterSpec;
import java.security.spec.InvalidParameterSpecException;

import javax.crypto.Cipher;
import javax.crypto.CipherSpi;
import javax.crypto.spec.PBEParameterSpec;
import javax.crypto.spec.IvParameterSpec;
import javax.crypto.spec.SecretKeySpec;
import javax.crypto.NoSuchPaddingException;
import javax.crypto.ShortBufferException;
import javax.crypto.BadPaddingException;
import javax.crypto.IllegalBlockSizeException;

import com.dstc.security.common.PBEKeyDerivation;
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
 * @see com.dstc.security.provider.PBEParameters
 * @see com.dstc.security.provider.PBEKey
 * @see javax.crypto.Cipher
 *
 * @version 0.98, 98/07/01
 * @author Ming Yung
 * modified & extended: Eddy Cheung 
 */
public abstract class PBECipher extends CipherSpi
{
  protected Cipher cipher = null;
  protected MessageDigest md = null;
  protected String pbeAlgo = null;
  protected String algo = null;
  protected int keyLength = 0;
  protected PBEKeyDerivation deriveKey = null;

  protected void engineSetPadding(String padding)
    throws NoSuchPaddingException 
  {
    //Nothing
  }

  protected void engineSetMode(String mode) throws NoSuchAlgorithmException 
  {
    //Nothing
  }

  protected int engineGetBlockSize()
  {
    //The underlying Cipher block size
    return cipher.getBlockSize();
  }

  protected int engineGetOutputSize(int inputLen)
  {
    return cipher.getOutputSize(inputLen);
  }

  protected byte[] engineGetIV()
  {
    return cipher.getIV();
  }

  protected AlgorithmParameters engineGetParameters()
  {
    return null;
  }

  protected void engineInit(int opmode, Key key, SecureRandom random)
    throws InvalidKeyException 
  {
    throw new InvalidKeyException("PBECipher needs PBE parameters");
  }

  protected void engineInit(int opmode, Key key, AlgorithmParameters params,   
                            SecureRandom random) 
    throws InvalidAlgorithmParameterException, InvalidKeyException
  {
    try
    {
      engineInit(opmode, key, params.getParameterSpec(PBEParameterSpec.class), 
                 random);
    }
    catch (InvalidParameterSpecException e)
    {
      throw new InvalidAlgorithmParameterException(e.getMessage());
    }
  }

  protected byte[] engineUpdate(byte input[], int inputOffset, int inputLen)
  {
    return cipher.update(input, inputOffset, inputLen);
  }

  protected int engineUpdate(byte[] input, int inputOffset,
                             int inputLen, byte[] output, int outputOffset) 
    throws ShortBufferException
  {
    return cipher.update(input, inputOffset, inputLen, output, outputOffset);
  }

  protected byte[] engineDoFinal(byte[] input, int inputOffset, int inputLen) 
    throws IllegalBlockSizeException, BadPaddingException
  {
    return cipher.doFinal(input, inputOffset, inputLen);
  }

  protected int engineDoFinal(byte[] input, int inputOffset, int inputLen,
                              byte[] output, int outputOffset) 
    throws ShortBufferException, IllegalBlockSizeException, BadPaddingException
  {
    return cipher.doFinal(input, inputOffset, inputLen, output, outputOffset);
  }

  protected void engineInit(int opmode, Key key, AlgorithmParameterSpec params, 
                            SecureRandom random)
    throws InvalidAlgorithmParameterException, InvalidKeyException 
  {
    /*if (!(key.getAlgorithm().equals(pbeAlgo))) 
    {
      throw new InvalidKeyException ("Key type " + key.getAlgorithm() +
        "unsuitable for this cipher");
    }*/

    if (!(params instanceof PBEParameterSpec)) 
    {
      throw new InvalidKeyException ("Not PBE parameters");
    }

    byte[] keyBytes 
      = deriveKey.generateKey(PBEKeyDerivation.GENERATE_KEY_MODE,
                              md, key, params, keyLength/8);

    byte[] ivBytes 
      = deriveKey.generateKey(PBEKeyDerivation.GENERATE_IV_MODE,
                              md, key, params, 8);

    try 
    {
      SecretKeySpec keySpec = new SecretKeySpec(keyBytes, algo);
      IvParameterSpec ivSpec = new IvParameterSpec(ivBytes);
      cipher.init(opmode, keySpec, ivSpec, random);
    } 
    catch (Exception e) 
    {
      throw new InvalidKeyException(e.getMessage());
    }
  }

  private static final boolean DUMMY = Licensed.VALID;
}
