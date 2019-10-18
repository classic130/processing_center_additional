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
import javax.crypto.spec.PBEKeySpec;
import javax.crypto.SecretKeyFactory;
import javax.crypto.SecretKeyFactorySpi;

abstract class PBEKeyFactory extends SecretKeyFactorySpi
{
  protected final String alg;

  PBEKeyFactory(String alg)
  {
    this.alg = alg;
  }

  protected SecretKey engineGenerateSecret(KeySpec keySpec) 
    throws InvalidKeySpecException
  {
    if (keySpec instanceof PBEKeySpec)
    {
      return new SecretKeySpec(
        toPasswordBytes(((PBEKeySpec)keySpec).getPassword()), alg);
    }

    throw new InvalidKeySpecException("Not a PBE key spec");
  }

  protected KeySpec engineGetKeySpec(SecretKey key, Class keySpec) 
    throws InvalidKeySpecException
  {
    throw new UnsupportedOperationException("Not implemented");
  }

  protected SecretKey engineTranslateKey(SecretKey key) 
    throws InvalidKeyException
  {
    if (key.getAlgorithm().equals(alg))
      return new SecretKeySpec(key.getEncoded(), alg);

    throw new InvalidKeyException("Cannot translate this key");
  }

  protected abstract byte[] toPasswordBytes(char[] pass);

  private static final boolean DUMMY = Licensed.VALID;
}
