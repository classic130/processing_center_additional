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

import java.io.IOException;
import java.math.BigInteger;
import java.security.Key;
import java.security.SecureRandom;
import java.security.InvalidKeyException;
import java.security.spec.AlgorithmParameterSpec;
import java.security.InvalidAlgorithmParameterException;
import java.security.NoSuchAlgorithmException;
import java.security.NoSuchProviderException;
import javax.crypto.SecretKey;
import javax.crypto.SecretKeyFactory;
import javax.crypto.spec.SecretKeySpec;
import javax.crypto.KeyAgreement;
import javax.crypto.KeyAgreementSpi;
import javax.crypto.ShortBufferException;

import com.dstc.security.util.Bytes;
import com.dstc.security.asn1.Asn1;
import com.dstc.security.provider.ESDHParameterSpec;

/**
 * <p>Implements the Diffie-Hellman Key Agreement algorithm.
 *
 * @see javax.crypto.KeyAgreement
 * @see com.dstc.security.provider.DHParameters
 * @see com.dstc.security.provider.DHPublicKey
 * @see com.dstc.security.provider.DHPrivateKey
 *
 * @version 0.98, 98/07/01
 * @author Ming Yung
 */
public class ESDHKeyAgreement extends DHKeyAgreement
{

  private AlgorithmParameterSpec aps = null;

  protected void engineInit(Key key, AlgorithmParameterSpec params,
                            SecureRandom random)
    throws InvalidKeyException, InvalidAlgorithmParameterException
  {
    if (!(key instanceof DHPrivateKey))
      throw new InvalidKeyException("Not a DH Private Key");
 
    if (!(params instanceof ESDHParameterSpec))
      throw new InvalidAlgorithmParameterException("Wrong type of parameters");
 
    this.myPriv = (DHPrivateKey)key;
    this.modulus = myPriv.getParams().getP();
    this.base = myPriv.getParams().getG();
    this.aps = params;
  }                                                                             

  protected Key engineDoPhase(Key key, boolean lastPhase)
    throws InvalidKeyException, IllegalStateException                             {
      if (lastPhase == false) {
          throw new IllegalStateException("Only 2 parties supported for ESDH"); 
      }
  
      return super.engineDoPhase(key, lastPhase);
  }


  protected SecretKey engineGenerateSecret(String algorithm)
    throws IllegalStateException, NoSuchAlgorithmException,
           InvalidKeyException
  {
    if (!algorithm.equals("3DESwrap") && !algorithm.equals("RC2wrap")
         && !algorithm.equals("IDEAwrap"))
      throw new NoSuchAlgorithmException(algorithm + 
         " not suppported for Ephemeral-Static DH");


    byte ZZ[] = engineGenerateSecret();

    SecretKey retval = null;
    int kekLength;

    if (algorithm.equals("3DESwrap"))
      kekLength = 192;
    else
      kekLength = 128;

    KEKGenerator kek = new KEKGenerator(ZZ, algorithm, kekLength);

    if (this.aps != null) {
        kek.setPartyAInfo(((ESDHParameterSpec) aps).getPartyAInfo());
    }

    byte[] keyBytes = null;

    try
    {
      keyBytes = kek.generateKeyMaterial();
    }
    catch (IOException e)
    {
      throw new InvalidKeyException(e.getMessage());
    }

    if (algorithm.equals("3DESwrap"))
    {
      retval = new SymmetricKey("DESede", keyBytes, 0, 24);
    }
    else if (algorithm.equals("RC2wrap"))
    {
      retval = new SymmetricKey("RC2", keyBytes, 0, 16);
    }
    else if (algorithm.equals("IDEAwrap"))
    {
      retval = new SymmetricKey("IDEA", keyBytes, 0, 16);
    }

    return retval;
  }
}
