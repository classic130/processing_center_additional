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

import java.security.KeyPair;
import java.security.SecureRandom;
import java.security.MessageDigest;
import java.security.AlgorithmParameters;
import java.security.AlgorithmParameterGenerator;
import java.security.KeyPairGeneratorSpi;
import java.security.spec.AlgorithmParameterSpec;
import java.security.spec.DSAParameterSpec;
import java.security.spec.InvalidParameterSpecException;
import java.security.InvalidAlgorithmParameterException;
import java.security.NoSuchAlgorithmException;
import java.math.BigInteger;
import java.util.Random;

/**
 * <p>Implements a Key Pair generator for the DSA signature algorithm.
 *
 * @see java.security.KeyPairGenerator
 * @see com.dstc.security.provider.DSAPublicKey
 * @see com.dstc.security.provider.DSAPrivateKey
 * @see com.dstc.security.provider.DSA
 *
 * @version 0.98, 98/07/01
 * @author Ming Yung
 */
public final class DSAKeyPairGenerator extends KeyPairGeneratorSpi
{
  private DSAPrivateKey priv;
  private DSAPublicKey pub;
  private DSAParameterSpec dsaParamsSpec;
  private SecureRandom random;
  private int keyLength = 1024;   // default key size
  private static final int MAX_KEY_LENGTH = 8192;

  public void initialize(int strength, SecureRandom random) 
  {
    if (strength > MAX_KEY_LENGTH) {
        throw new java.security.InvalidParameterException("key length" +
            " too long. Max = " + MAX_KEY_LENGTH + " bits");
    }
    this.random = random;
    this.keyLength = strength;

  }

  public KeyPair generateKeyPair() 
  {
    if (random == null) {
        random = new SecureRandom();
    }
    if (dsaParamsSpec == null) {

      if (keyLength == 1024)
      {
        this.dsaParamsSpec = new DSAParameterSpec
         (new BigInteger ("fd7f53811d75122952df4a9c2eece4e7f611b752" +
                          "3cef4400c31e3f80b6512669455d402251fb593d" +
                          "8d58fabfc5f5ba30f6cb9b556cd7813b801d346f" +
                          "f26660b76b9950a5a49f9fe8047b1022c24fbba9" +
                          "d7feb7c61bf83b57e7c6a8a6150f04fb83f6d3c5" +
                          "1ec3023554135a169132f675f3ae2b61d72aeff2" +
                          "2203199dd14801c7", 16),
          new BigInteger ("9760508f15230bccb292b982a2eb840bf0581cf5", 16),
          new BigInteger ("f7e1a085d69b3ddecbbcab5c36b857b97994afbb" +
                          "fa3aea82f9574c0b3d0782675159578ebad4594f" +
                          "e67107108180b449167123e84c281613b7cf0932" +
                          "8cc8a6e13c167a8b547c8d28e0a3ae1e2bb3a675" +
                          "916ea37f0bfa213562f1fb627a01243bcca4f1be" +
                          "a8519089a883dfe15ae59f06928b665e807b5525" +
                          "64014c3bfecf492a", 16));
      }
      else 
      {
        //Generate new DSA params
        try
        {
          AlgorithmParameterGenerator algGen =
            AlgorithmParameterGenerator.getInstance("DSA");
          algGen.init(keyLength, random);
          this.dsaParamsSpec = (DSAParameterSpec)algGen.generateParameters().
            getParameterSpec(DSAParameterSpec.class);
        }
        catch (NoSuchAlgorithmException e)
        {
          throw new RuntimeException("Internal error: " + e.getMessage());
        }
        catch (InvalidParameterSpecException e)
        {
          throw new RuntimeException("Internal error: " + e.getMessage());
        }
      }
    }

  BigInteger x = null;
    while (true)
    {
      x = new BigInteger(dsaParamsSpec.getQ().bitLength(), random);
      if (x.compareTo(dsaParamsSpec.getQ()) == -1) {
          break;
      }
    }

    priv = new DSAPrivateKey(x, dsaParamsSpec);

    BigInteger y = dsaParamsSpec.getG().modPow(x, dsaParamsSpec.getP());
    pub = new DSAPublicKey(y, dsaParamsSpec);

    return (new KeyPair(pub, priv));
  }

  public void initialize (AlgorithmParameterSpec spec, SecureRandom rnd) 
               throws InvalidAlgorithmParameterException 
  {
    if (!(spec instanceof DSAParameterSpec))
      throw new InvalidAlgorithmParameterException("Not a DSA parameter spec");

    int strength = ((DSAParameterSpec)spec).getP().bitLength();
    if (strength > MAX_KEY_LENGTH) {
        throw new java.security.InvalidParameterException("key length" +
            " too long. Max = " + MAX_KEY_LENGTH + " bits");
    }

    this.dsaParamsSpec = (DSAParameterSpec)spec;
    this.random = rnd;
  }

  private static final boolean DUMMY = Licensed.VALID;
}
