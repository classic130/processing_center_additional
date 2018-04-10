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
import java.security.PrivateKey;
import java.security.PublicKey;
import java.security.KeyPair;
import java.math.BigInteger;
import java.util.Random;
import java.security.interfaces.*;

/**
 * <p>Implements a Key Pair generator for the RSA signature algorithm.
 *
 * @see java.security.KeyPairGenerator
 * @see com.dstc.security.provider.RSAPublicKey
 * @see com.dstc.security.provider.RSAPrivateKey
 * @see com.dstc.security.provider.RSAwithAnyMD
 *
 * @version 0.98, 98/07/01
 * @author Ming Yung
 */
public class RSAKeyPairGenerator extends java.security.KeyPairGenerator
{
  private static BigInteger one = BigInteger.ONE;
  private static BigInteger two = BigInteger.valueOf(2);

  private int modlen = 1024; //default
  private SecureRandom random;
  private static final int PROB = 80;
  private static final String EXPONENT = "10001";
  private static final int MAX_KEY_LENGTH = 8192;

  public RSAKeyPairGenerator() 
  {
    super ("RSA");
  }

  /// Initializes this KeyPairGenerator for given modulus and random source
  public void initialize(int strength, SecureRandom random) 
  {
    this.initialize(strength);
    this.random = random;
  }

  /// Initializes this KeyPairGenerator for given modulus
  public void initialize(int strength) 
  {
    if (strength > MAX_KEY_LENGTH) {
        throw new java.security.InvalidParameterException("key length" +
            " too long. Max = " + MAX_KEY_LENGTH + " bits");
    }
    this.modlen = strength;
  }

  /// Generates a Key Pair
  public KeyPair generateKeyPair() 
  {
    if (this.random == null)
      this.random = new SecureRandom();

    BigInteger e = new BigInteger(EXPONENT, 16);
    BigInteger p, q, n;

    while (true)
    {
      p = new BigInteger(modlen/2, PROB, random);
      q = new BigInteger(modlen - modlen/2, PROB, random);
      n = p.multiply(q);

      if (n.bitLength() == modlen) break;
    }

    BigInteger phi = (p.subtract(one)).multiply(q.subtract(one));

    while (true) 
    {
      if (phi.gcd(e).equals(one)) break;
      p = p.subtract(two);
      q = q.subtract(two);
      n = p.multiply(q);
      phi = (p.subtract(one)).multiply(q.subtract(one));
    }

    BigInteger d = e.modInverse(phi);
    RSAPublicKey pub = new RSAPublicKey(n, e);

    // modulus, private exponent, public exponent, p, q
    RSAPrivateCrtKey priv = new RSAPrivateCrtKey(n, e, d, p, q);
    return (new KeyPair(pub, priv));
  }

  private static final boolean DUMMY = Licensed.VALID;
}
