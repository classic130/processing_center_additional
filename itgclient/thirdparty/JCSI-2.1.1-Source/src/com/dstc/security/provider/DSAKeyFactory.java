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
import java.security.spec.PKCS8EncodedKeySpec;
import java.security.spec.X509EncodedKeySpec;
import java.security.spec.InvalidKeySpecException;
import java.security.spec.DSAPublicKeySpec;
import java.security.spec.DSAPrivateKeySpec;
import java.security.spec.DSAParameterSpec;

import com.dstc.security.common.AlgorithmId;
import com.dstc.security.common.SubjectPublicKeyInfo;
import com.dstc.security.common.PrivateKeyInfo;

/**
 * <p>Implements a Factory class for public or private keys to use with 
 * the DSA signature algorithm.
 *
 * @see java.security.KeyFactory
 * @see com.dstc.security.provider.DSAPublicKey
 * @see com.dstc.security.provider.DSAPrivateKey
 * @see com.dstc.security.provider.DSA
 *
 * @version 0.98, 98/07/01
 * @author Ming Yung
 */
public class DSAKeyFactory extends KeyFactorySpi
{
  protected PublicKey engineGeneratePublic(KeySpec keySpec) 
    throws InvalidKeySpecException
  {
    if(keySpec instanceof DSAPublicKeySpec)
    {
      DSAPublicKeySpec spec = (DSAPublicKeySpec)keySpec;

      return new DSAPublicKey(spec.getY(), 
        new DSAParameterSpec(spec.getP(), spec.getQ(), spec.getG()));
    }
    else if (keySpec instanceof X509EncodedKeySpec)
    { 
      try
      {
        SubjectPublicKeyInfo info = new SubjectPublicKeyInfo(
          ((X509EncodedKeySpec)keySpec).getEncoded());
        AlgorithmId algo = info.getAlgorithmId();
        DSAParameterSpec dsaParams = null;
  
        if (algo.getParams() != null)
        {
          dsaParams = (DSAParameterSpec)
            algo.getParams().getParameterSpec(DSAParameterSpec.class);
        }
  
        return new DSAPublicKey(info.getEncodedKey(), dsaParams);
      }
      catch (Exception e)
      {
        throw new InvalidKeySpecException("Bad key spec: " + e.getMessage());
      }
    }
    else
      throw new InvalidKeySpecException("Not a DSA public key spec");
  }

  protected PrivateKey engineGeneratePrivate(KeySpec keySpec)
    throws InvalidKeySpecException
  {
    if(keySpec instanceof DSAPrivateKeySpec)
    {
      DSAPrivateKeySpec spec = (DSAPrivateKeySpec)keySpec;

      return new DSAPrivateKey(spec.getX(), 
        new DSAParameterSpec(spec.getP(), spec.getQ(), spec.getG()));
    }
    else if(keySpec instanceof PKCS8EncodedKeySpec)
    {
      try
      {
        PrivateKeyInfo pki 
          = new PrivateKeyInfo(((PKCS8EncodedKeySpec)keySpec).getEncoded());
  
        AlgorithmId algo = pki.getAlgorithmId();
        DSAParameterSpec dsaParams = null;
        if (algo.getParams() != null)
        {
          dsaParams = (DSAParameterSpec)
            algo.getParams().getParameterSpec(DSAParameterSpec.class);
        }
  
        return new DSAPrivateKey(pki.getEncodedKey(), dsaParams);
      }
      catch(Exception e)
      {
        throw new InvalidKeySpecException("Bad key spec: " + e.getMessage());
      }
    }
    else
      throw new InvalidKeySpecException("Not a DSA private key spec");
  }

  protected KeySpec engineGetKeySpec(Key key, Class keySpec) 
    throws InvalidKeySpecException
  {
    if (!key.getAlgorithm().equals("DSA"))
      throw new InvalidKeySpecException("Not a DSA key");

    if (key instanceof PublicKey)
    {
      if (keySpec.equals(X509EncodedKeySpec.class))
      {
        return new X509EncodedKeySpec(key.getEncoded());
      }
      else if (keySpec.equals(DSAPublicKeySpec.class))
      {
        java.security.interfaces.DSAPublicKey pub
          = (java.security.interfaces.DSAPublicKey)key;

        return new DSAPublicKeySpec(pub.getY(), pub.getParams().getP(),
          pub.getParams().getQ(), pub.getParams().getG());
      }
      else
        throw new InvalidKeySpecException("key and keyspec mismatch");
    }
    else
    {
      if (keySpec.equals(PKCS8EncodedKeySpec.class))
      {
        return new PKCS8EncodedKeySpec(key.getEncoded());
      }
      else if (keySpec.equals(DSAPrivateKeySpec.class))
      {
        java.security.interfaces.DSAPrivateKey priv
          = (java.security.interfaces.DSAPrivateKey)key;

        return new DSAPrivateKeySpec(priv.getX(), priv.getParams().getP(),
          priv.getParams().getQ(), priv.getParams().getG());
      }
      else
        throw new InvalidKeySpecException("key and keyspec mismatch");
    }
  }

  protected Key engineTranslateKey(Key key) throws InvalidKeyException
  {
    if (key == null) return null;

    if (!key.getAlgorithm().equals("DSA"))
      throw new InvalidKeyException("Not a DSA key");

    if (key instanceof java.security.interfaces.DSAPublicKey)
    {
      java.security.interfaces.DSAPublicKey dsaPublic
        = (java.security.interfaces.DSAPublicKey)key;
      return new DSAPublicKey(dsaPublic.getY(), dsaPublic.getParams());
    }
    else if (key instanceof java.security.interfaces.DSAPrivateKey)
    {
      java.security.interfaces.DSAPrivateKey dsaPriv
        = (java.security.interfaces.DSAPrivateKey)key;
      return new DSAPrivateKey(dsaPriv.getX(), dsaPriv.getParams());
    }
    else
      throw new InvalidKeyException("Cannot translate key");
  }

  private static final boolean DUMMY = Licensed.VALID;
}
