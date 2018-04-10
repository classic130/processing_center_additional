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
import javax.crypto.KeyGeneratorSpi;
import javax.crypto.SecretKey;
import java.security.spec.AlgorithmParameterSpec;
import java.security.InvalidAlgorithmParameterException;

/**
 * <p>Implements a Key Generator for Secret keys to use with the DES cipher
 *
 * @see javax.crypto.KeyGenerator
 * @see com.dstc.security.provider.DES
 *
 * @version 0.98, 98/07/01
 * @author Ming Yung
 */
abstract class SymmKeyGenerator extends KeyGeneratorSpi
{
  //Key length in bits
  protected int keyLength;
  protected SecureRandom random;
  protected String alg;

  protected void engineInit(SecureRandom random)
  {
    this.random = random;
  }

  protected void engineInit(AlgorithmParameterSpec params, SecureRandom random)
    throws InvalidAlgorithmParameterException
  {
    throw new InvalidAlgorithmParameterException("Params not supported");
  }

  protected void engineInit(int strength, SecureRandom random)
  {
    this.keyLength = strength;
    this.random = random;
  }

  protected SecretKey engineGenerateKey()
  {
    byte bytes[] = new byte[keyLength/8];

    if (this.random == null)
      this.random = new SecureRandom();

    this.random.nextBytes(bytes);
    return new SymmetricKey(alg, bytes);
  }

  private static final boolean DUMMY = Licensed.VALID;
}
