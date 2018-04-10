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

import java.security.InvalidKeyException;
import java.security.spec.KeySpec;
import java.security.spec.InvalidKeySpecException;

import javax.crypto.SecretKey;
import javax.crypto.spec.SecretKeySpec;
import javax.crypto.SecretKeyFactory;
import javax.crypto.SecretKeyFactorySpi;

/**
 * <p>Implements a Factory class for secret keys to use with the IDEA cipher.
 *
 * @see javax.crypto.SecretKeyFactory
 * @see com.dstc.security.provider.IDEA
 *
 * @version 0.98, 98/07/01
 * @author Ming Yung
 */
abstract class SymmetricKeyFactory extends SecretKeyFactorySpi
{
  protected final String alg;

  SymmetricKeyFactory(String alg)
  {
    this.alg = alg;
  }

  protected SecretKey engineGenerateSecret(KeySpec keySpec) 
    throws InvalidKeySpecException
  {
    if (keySpec instanceof SecretKeySpec)
    {
      if (!((SecretKeySpec)keySpec).getAlgorithm().equals(alg))
        throw new InvalidKeySpecException("Not an " + alg + " key spec");

      return new SymmetricKey(alg, ((SecretKeySpec)keySpec).getEncoded());
    }

    throw new InvalidKeySpecException("Not an " + alg + " key spec");
  }

  protected KeySpec engineGetKeySpec(SecretKey key, Class keySpec) 
    throws InvalidKeySpecException
  {
    if (!keySpec.equals(SecretKeySpec.class))
      throw new InvalidKeySpecException("Not a valid key spec for this key");

    return new SecretKeySpec(key.getEncoded(), alg);
  }

  protected SecretKey engineTranslateKey(SecretKey key) 
    throws InvalidKeyException
  {
    if (key.getAlgorithm().equals(alg))
      return new SymmetricKey(alg, key.getEncoded());

    throw new InvalidKeyException("Cannot translate this key");
  }

  private static final boolean DUMMY = Licensed.VALID;
}
