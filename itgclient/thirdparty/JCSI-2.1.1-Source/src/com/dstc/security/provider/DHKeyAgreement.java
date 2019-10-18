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

import java.math.BigInteger;
import java.security.Key;
import java.security.SecureRandom;
import java.security.InvalidKeyException;
import java.security.spec.AlgorithmParameterSpec;
import java.security.InvalidAlgorithmParameterException;
import java.security.NoSuchAlgorithmException;
import java.security.NoSuchProviderException;
import java.security.spec.InvalidKeySpecException;
import javax.crypto.SecretKey;
import javax.crypto.SecretKeyFactory;
import javax.crypto.spec.SecretKeySpec;
import javax.crypto.KeyAgreement;
import javax.crypto.KeyAgreementSpi;
import javax.crypto.ShortBufferException;

import com.dstc.security.util.Bytes;

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
public class DHKeyAgreement extends KeyAgreementSpi
{
  private SecureRandom random;
  protected DHPrivateKey myPriv;
  protected DHPublicKey yourPub;
  protected BigInteger modulus;
  protected BigInteger base;
  protected DHPublicKey nextKey;        

  protected void engineInit(Key key, SecureRandom random) 
    throws InvalidKeyException
  {
    if (!(key instanceof DHPrivateKey))
      throw new InvalidKeyException("Not a DH Private Key");

    this.random = random;
    this.myPriv = (DHPrivateKey)key;
    this.modulus = myPriv.getParams().getP();
    this.base = myPriv.getParams().getG();
  }

  protected void engineInit(Key key, AlgorithmParameterSpec params, 
                            SecureRandom random) 
    throws InvalidKeyException, InvalidAlgorithmParameterException
  {
    if (!(key instanceof DHPrivateKey))
      throw new InvalidKeyException("Not a DH Private Key");

    this.random = random;
    this.myPriv = (DHPrivateKey)key;
    this.modulus = myPriv.getParams().getP();
    this.base = myPriv.getParams().getG();
  }

  protected Key engineDoPhase(Key key, boolean lastPhase) 
    throws InvalidKeyException, IllegalStateException
  {
    BigInteger tmp;

    if (!(key instanceof DHPublicKey))
      throw new InvalidKeyException("Not a DH Public Key");

    this.yourPub = (DHPublicKey)key;     // intermediate key

    if (!(yourPub.getParams().getG().equals(this.base) &&
        yourPub.getParams().getP().equals(this.modulus)))
      throw new InvalidKeyException("modulus, base are mismatched");

    tmp = (yourPub.getY()).modPow(myPriv.getX(), this.modulus);

    this.nextKey = new DHPublicKey(tmp, this.modulus, this.base);

    if (lastPhase) {
        return null;
    }
    else {
        return this.nextKey;
    }
  }

  protected byte[] engineGenerateSecret() throws IllegalStateException
  {
    byte[] b = this.nextKey.getY().toByteArray();
    int bitLength = (this.modulus.bitLength() + 7) >>> 3;   

    if (b.length == bitLength)
    {
      return b;
    }
    else if (b.length == bitLength + 1)
    {
      byte[] retval = new byte[bitLength];
      System.arraycopy(b, 1, retval, 0, bitLength);
      return retval;
    }
    else if (b.length < bitLength)
    {
      byte[] retval = new byte[bitLength];
      System.arraycopy(b, 0, retval, bitLength - b.length, b.length);
      return retval;
    }
    else
    {
      throw new RuntimeException("Internal error: DH secret size");
    }
  }

  protected int engineGenerateSecret(byte[] sharedSecret, int offset) 
    throws IllegalStateException, ShortBufferException
  {
    byte val[] = engineGenerateSecret();

    if (sharedSecret.length - offset < val.length)
      throw new ShortBufferException("Buffer too short");

    System.arraycopy(val, 0, sharedSecret, offset, val.length);
    return val.length;
  }

  protected SecretKey engineGenerateSecret(String algorithm) 
    throws IllegalStateException, NoSuchAlgorithmException, 
           InvalidKeyException
  {
    byte val[] = engineGenerateSecret();

    try
    {
      SecretKeyFactory fact = SecretKeyFactory.getInstance(algorithm);
      SecretKeySpec spec = new SecretKeySpec(val, algorithm);

      return fact.generateSecret(spec);
    }
    catch (InvalidKeySpecException e)
    {
      throw new RuntimeException("Internal error: " + e.getMessage());
    }
  }

  private static final boolean DUMMY = Licensed.VALID;
}
