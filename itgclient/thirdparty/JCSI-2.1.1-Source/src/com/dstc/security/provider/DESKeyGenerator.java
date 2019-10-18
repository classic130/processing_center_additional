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
import java.security.spec.AlgorithmParameterSpec;
import java.security.InvalidAlgorithmParameterException;
import java.security.InvalidParameterException;

import javax.crypto.KeyGeneratorSpi;
import javax.crypto.SecretKey;

/**
 * <p>Implements a Key Generator for Secret keys to use with the DES cipher
 *
 * @see javax.crypto.KeyGenerator
 * @see com.dstc.security.provider.DES
 *
 * @version 0.98, 98/07/01
 * @author Ming Yung
 */
public class DESKeyGenerator extends SymmKeyGenerator
{
  public DESKeyGenerator()
  {
    this.keyLength = 64;
    this.alg = "DES";
  }

  protected void engineInit(int strength, SecureRandom random)
  {
    if (strength != 56)
      throw new InvalidParameterException("Only 56-bit DES keys supported");

    this.random = random;
  }

  protected SecretKey engineGenerateKey()
  {
    byte bytes[] = new byte[keyLength/8];

    if (this.random == null)
    {
      this.random = new SecureRandom();
    }

    this.random.nextBytes(bytes);
    forceOddParity(bytes);
    return new SymmetricKey(this.alg, bytes);
  }

  private static void forceOddParity (byte in[])
  {
    int score;
    for (int j=0; j < in.length; j++)
    {
      score = 0;
      for (int i=7; i>=0; i--)
      {
        score += (in[j] >>> i) & 0x1;
      }
      if (0 == score % 2) in[j] ^= 0x1;
    }
  }
}
