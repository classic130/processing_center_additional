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
import java.security.spec.InvalidKeySpecException;
import java.security.spec.KeySpec;

import javax.crypto.SecretKey;
import javax.crypto.spec.DESedeKeySpec;
import javax.crypto.spec.SecretKeySpec;

/**
 * <p>Implements a Factory class for secret keys to use with the DESede cipher.
 *
 * @see javax.crypto.SecretKeyFactory
 * @see com.dstc.security.provider.DESede
 *
 * @version 0.98, 98/07/01
 * @author Ming Yung
 */
public final class DESedeSecretKeyFactory extends SymmetricKeyFactory
{
  public DESedeSecretKeyFactory()
  {
    super("DESede");
  }

  protected SecretKey engineGenerateSecret(KeySpec keySpec) 
    throws InvalidKeySpecException
  {
    if (keySpec instanceof DESedeKeySpec)
      return new SymmetricKey(alg, ((DESedeKeySpec)keySpec).getKey()); 

    return super.engineGenerateSecret(keySpec);
  }

  protected KeySpec engineGetKeySpec(SecretKey key, Class keySpec) 
    throws InvalidKeySpecException
  {
    try
    {
      if ((keySpec.equals(DESedeKeySpec.class)))
        return new DESedeKeySpec(key.getEncoded());
    }
    catch (InvalidKeyException e)
    {
      throw new InvalidKeySpecException(e.getMessage());
    }

    return super.engineGetKeySpec(key, keySpec);
  }
}