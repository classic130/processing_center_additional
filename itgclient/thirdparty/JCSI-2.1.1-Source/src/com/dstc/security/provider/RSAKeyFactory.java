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
import java.security.spec.KeySpec;
import java.security.spec.X509EncodedKeySpec;
import java.security.spec.PKCS8EncodedKeySpec;
import java.security.spec.InvalidKeySpecException;
import java.security.spec.RSAPublicKeySpec;
import java.security.spec.RSAPrivateCrtKeySpec;
import java.security.spec.RSAPrivateKeySpec;

import javax.crypto.Cipher;
import javax.crypto.BadPaddingException;
import javax.crypto.spec.PBEParameterSpec;

import com.dstc.security.common.AlgorithmId;
import com.dstc.security.common.SubjectPublicKeyInfo;
import com.dstc.security.common.PrivateKeyInfo;

/**
 * <p>Implements a Factory class for public or private keys to use with 
 * the RSA signature algorithm.
 *
 * @see java.security.KeyFactory
 * @see com.dstc.security.provider.RSAPublicKey
 * @see com.dstc.security.provider.RSAPrivateKey
 * @see com.dstc.security.provider.RSA
 *
 * @version 0.98, 98/07/01
 * @author Ming Yung
 */
public class RSAKeyFactory extends KeyFactorySpi
{
  protected PublicKey engineGeneratePublic(KeySpec keySpec) 
    throws InvalidKeySpecException
  {
    if(keySpec instanceof RSAPublicKeySpec)
    {
      RSAPublicKeySpec spec = (RSAPublicKeySpec)keySpec;

      return new RSAPublicKey(
                   spec.getModulus(), spec.getPublicExponent());
    }
    else if(keySpec instanceof X509EncodedKeySpec)
    {
      try
      {
        SubjectPublicKeyInfo info = new SubjectPublicKeyInfo(
          ((X509EncodedKeySpec)keySpec).getEncoded());
        return new RSAPublicKey(info.getEncodedKey());
      }
      catch (Exception e)
      {
        throw new InvalidKeySpecException("Bad key spec: " + e.getMessage());
      }
    }
    else
      throw new InvalidKeySpecException("Cannot convert to RSA Public Key");
  }

  protected PrivateKey engineGeneratePrivate(KeySpec keySpec)
    throws InvalidKeySpecException
  {
    if(keySpec instanceof RSAPrivateCrtKeySpec)
    {
      RSAPrivateCrtKeySpec spec = (RSAPrivateCrtKeySpec)keySpec;

      return new RSAPrivateCrtKey(spec.getModulus(), spec.getPublicExponent(),
                                  spec.getPrivateExponent(), spec.getPrimeP(),
                                  spec.getPrimeQ());
    }
    else if(keySpec instanceof RSAPrivateKeySpec)
    {
      RSAPrivateKeySpec spec = (RSAPrivateKeySpec)keySpec;

      return new RSAPrivateKey(spec.getModulus(), spec.getPrivateExponent());
    }
    else if(keySpec instanceof PKCS8EncodedKeySpec)
    {
      try
      {
        PrivateKeyInfo pki 
          = new PrivateKeyInfo(((PKCS8EncodedKeySpec)keySpec).getEncoded());

        return new RSAPrivateCrtKey(pki.getEncodedKey());
      }
      catch (Exception e)
      {
        throw new InvalidKeySpecException("Bad key spec: " + e.getMessage());
      }
    }
    else
      throw new InvalidKeySpecException("Cannot convert to RSA Private Key");
  }

  protected KeySpec engineGetKeySpec(Key key, Class keySpec) 
    throws InvalidKeySpecException
  {
    if (!key.getAlgorithm().equals("RSA"))
      throw new InvalidKeySpecException("Not an RSA Key");

    if (key instanceof PublicKey)
    {
      if (keySpec.equals(X509EncodedKeySpec.class))
      {
        return new X509EncodedKeySpec(key.getEncoded());
      }
      else if (keySpec.equals(RSAPublicKeySpec.class))
      {
        java.security.interfaces.RSAPublicKey pub = 
                        (java.security.interfaces.RSAPublicKey) key; 
        return new RSAPublicKeySpec(pub.getModulus(), 
                                    pub.getPublicExponent());
      }
      else
        throw new InvalidKeySpecException("Key and keyspec mismatch");
    }
    else 
    {
      if (keySpec.equals(PKCS8EncodedKeySpec.class))
      {
        return new PKCS8EncodedKeySpec(key.getEncoded());
      }
      else if (keySpec.equals(RSAPrivateKeySpec.class))
      {
        java.security.interfaces.RSAPrivateKey priv = 
            (java.security.interfaces.RSAPrivateKey)key;
        
        return new RSAPrivateKeySpec(priv.getModulus(), 
                                     priv.getPrivateExponent());
      }
      else if (keySpec.equals(RSAPrivateCrtKeySpec.class))
      {
        java.security.interfaces.RSAPrivateCrtKey priv;
        if (key instanceof java.security.interfaces.RSAPrivateCrtKey)
          priv = (java.security.interfaces.RSAPrivateCrtKey)key;
        else
          throw new InvalidKeySpecException("Key and keyspec mismatch");

        return new RSAPrivateCrtKeySpec(priv.getModulus(), 
                                    priv.getPublicExponent(),
                                    priv.getPrivateExponent(),
                                    priv.getPrimeP(),
                                    priv.getPrimeQ(),
                                    priv.getPrimeExponentP(),
                                    priv.getPrimeExponentQ(),
                                    priv.getCrtCoefficient());
      }
      else
        throw new InvalidKeySpecException("Key and keyspec mismatch");
    }
  }

  protected Key engineTranslateKey(Key key) throws InvalidKeyException
  {
    if (key == null) return null;

    if (key instanceof java.security.interfaces.RSAPublicKey)
    {
      java.security.interfaces.RSAPublicKey rsaPublic
        = (java.security.interfaces.RSAPublicKey)key;
      return new RSAPublicKey(rsaPublic.getModulus(), 
                              rsaPublic.getPublicExponent());
    }
    else if (key instanceof java.security.interfaces.RSAPrivateKey)
    {
      java.security.interfaces.RSAPrivateKey rsaPrivate
        = (java.security.interfaces.RSAPrivateKey)key;
      return new RSAPrivateKey( rsaPrivate.getModulus(), 
                      rsaPrivate.getPrivateExponent());
    }
    else if (key instanceof java.security.interfaces.RSAPrivateCrtKey)
    {
      java.security.interfaces.RSAPrivateCrtKey rsaPrivate
        = (java.security.interfaces.RSAPrivateCrtKey)key;
      return new RSAPrivateCrtKey(rsaPrivate.getModulus(), 
                               rsaPrivate.getPublicExponent(),
                               rsaPrivate.getPrivateExponent(),
                               rsaPrivate.getPrimeP(),
                               rsaPrivate.getPrimeQ(),
                               rsaPrivate.getPrimeExponentP(),
                               rsaPrivate.getPrimeExponentQ(),
                               rsaPrivate.getCrtCoefficient());
    }
    else
      throw new InvalidKeyException("Cannot translate this key");
  }

  private static final boolean DUMMY = Licensed.VALID;
}
