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
import java.security.KeyFactorySpi;
import java.security.Key;
import java.security.InvalidKeyException;
import java.security.PrivateKey;
import java.security.PublicKey;
import java.security.AlgorithmParameters;
import java.security.spec.KeySpec;
import java.security.spec.X509EncodedKeySpec;
import java.security.spec.PKCS8EncodedKeySpec;
import java.security.spec.InvalidKeySpecException;

import javax.crypto.Cipher;
import javax.crypto.spec.DHPublicKeySpec;
import javax.crypto.spec.DHPrivateKeySpec;
import javax.crypto.spec.DHParameterSpec;
import javax.crypto.spec.PBEParameterSpec;

import com.dstc.security.common.AlgorithmId;
import com.dstc.security.common.SubjectPublicKeyInfo;
import com.dstc.security.common.PrivateKeyInfo;

/**
 * <p>Implements a Factory class for public or private keys to use with 
 * the Diffie-Hellman key agreement algorithm.
 *
 * @see java.security.KeyFactory
 * @see com.dstc.security.provider.DHPublicKey
 * @see com.dstc.security.provider.DHPrivateKey
 * @see com.dstc.security.provider.DHKeyAgreement
 *
 * @version 0.98, 98/07/01
 * @author Ming Yung
 */
public class DHKeyFactory extends KeyFactorySpi
{
  protected PublicKey engineGeneratePublic(KeySpec keySpec) 
    throws InvalidKeySpecException
  {
    if(keySpec instanceof DHPublicKeySpec)
    {
      DHPublicKeySpec spec = (DHPublicKeySpec)keySpec;
      return new com.dstc.security.provider.DHPublicKey(
        spec.getY(), spec.getP(), spec.getG());
    }
    else if (keySpec instanceof X509EncodedKeySpec)
    {
      try
      {
        SubjectPublicKeyInfo info = new SubjectPublicKeyInfo(
          ((X509EncodedKeySpec)keySpec).getEncoded());
        AlgorithmId algo = info.getAlgorithmId();
        DHParameterSpec dhParams = (DHParameterSpec)
          algo.getParams().getParameterSpec(DHParameterSpec.class);

        return new DHPublicKey(info.getEncodedKey(), dhParams);
      }
      catch (Exception e)
      {
        throw new InvalidKeySpecException("Bad key spec: " + e.getMessage());
      }
    }
    else
      throw new InvalidKeySpecException("Not a DH public key spec");
  }

  protected PrivateKey engineGeneratePrivate(KeySpec keySpec)
    throws InvalidKeySpecException
  {
    if(keySpec instanceof DHPrivateKeySpec)
    {
      DHPrivateKeySpec spec = (DHPrivateKeySpec)keySpec;
      return new com.dstc.security.provider.DHPrivateKey(
        spec.getX(), spec.getP(), spec.getG());
    }
    else if(keySpec instanceof PKCS8EncodedKeySpec)
    {
      try
      {
        PrivateKeyInfo pki 
          = new PrivateKeyInfo(((PKCS8EncodedKeySpec)keySpec).getEncoded());

        AlgorithmId algo = pki.getAlgorithmId();
        DHParameterSpec dhParams = (DHParameterSpec)
          algo.getParams().getParameterSpec(DHParameterSpec.class);
 
        return new DHPrivateKey(pki.getEncodedKey(), dhParams);
      }
      catch (Exception e)
      {
        throw new InvalidKeySpecException("Bad key spec: " + e.getMessage());
      }
    }
    else
      throw new InvalidKeySpecException("Not a DH private key spec");
  }

  protected KeySpec engineGetKeySpec(Key key, Class keySpec) 
    throws InvalidKeySpecException
  {
    if (!key.getAlgorithm().equals("DH"))
      throw new InvalidKeySpecException("Not a DH key");

    if (key instanceof PublicKey)
    {
      if (keySpec.equals(X509EncodedKeySpec.class))
      {
        return new X509EncodedKeySpec(key.getEncoded());
      }
      else if (keySpec.equals(DHPublicKeySpec.class))
      {
        javax.crypto.interfaces.DHPublicKey pub =
          (javax.crypto.interfaces.DHPublicKey)key;
           
        return new DHPublicKeySpec(pub.getY(), pub.getParams().getP(), 
         pub.getParams().getG());
      }
      else
        throw new InvalidKeySpecException("Key and keySpec mismatch");
    }
    else
    {
      if (keySpec.equals(PKCS8EncodedKeySpec.class))
      {
        return new PKCS8EncodedKeySpec(key.getEncoded());
      }
      else if (keySpec.equals(DHPrivateKeySpec.class))
      {
        javax.crypto.interfaces.DHPrivateKey priv =
          (javax.crypto.interfaces.DHPrivateKey)key;

        return new DHPrivateKeySpec(priv.getX(), priv.getParams().getP(), 
          priv.getParams().getG());
      }
      else
        throw new InvalidKeySpecException("Key and keySpec mismatch");
    }
  }

  protected Key engineTranslateKey(Key key) throws InvalidKeyException
  {
    if (key == null) return null;

    if (!key.getAlgorithm().equals("DH"))
      throw new InvalidKeyException("Not a DH key");

    if (key instanceof javax.crypto.interfaces.DHPublicKey)
    {
      javax.crypto.interfaces.DHPublicKey dhPublic
        = (javax.crypto.interfaces.DHPublicKey)key;
      return new DHPublicKey(dhPublic.getY(), 
        dhPublic.getParams().getP(), dhPublic.getParams().getG());
    }
    else if (key instanceof javax.crypto.interfaces.DHPrivateKey)
    {
      javax.crypto.interfaces.DHPrivateKey dhPriv
        = (javax.crypto.interfaces.DHPrivateKey)key;
      return new DHPrivateKey(dhPriv.getX(), 
        dhPriv.getParams().getP(), dhPriv.getParams().getG());
    }
    else
      throw new InvalidKeyException("Cannot translate key");
  }

  private static final boolean DUMMY = Licensed.VALID;
}
