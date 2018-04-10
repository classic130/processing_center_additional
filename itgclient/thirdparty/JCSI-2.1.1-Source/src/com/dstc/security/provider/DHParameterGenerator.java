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
import java.security.AlgorithmParameters;
import java.security.AlgorithmParameterGenerator;
import java.security.AlgorithmParameterGeneratorSpi;
import java.security.InvalidAlgorithmParameterException;
import java.security.ProviderException;
import java.security.NoSuchAlgorithmException;
import java.security.spec.AlgorithmParameterSpec;
import java.security.spec.DSAParameterSpec;
import java.security.spec.InvalidParameterSpecException;

import javax.crypto.spec.DHGenParameterSpec;
import javax.crypto.spec.DHParameterSpec;

/**
 * <p>Implements an Algorithm Parameter Generator for use with the
 * Diffie-Hellman key exchange algorithm.
 *
 * @see java.security.AlgorithmParameterGenerator
 * @see com.dstc.security.provider.DHParameters
 * @see com.dstc.security.provider.DHKeyAgreement
 *
 * @version 0.98, 98/08/08
 * @author Ming Yung
 */
public class DHParameterGenerator extends AlgorithmParameterGeneratorSpi
{
  private SecureRandom random;
  private int keyLength;
  private int expSize;

  protected void engineInit(int strength, SecureRandom random)
  {
    this.keyLength = strength;
    this.random = random;
  }

  protected void engineInit(AlgorithmParameterSpec genParamSpec,
                            SecureRandom random) 
    throws InvalidAlgorithmParameterException
  {
    if (!(genParamSpec instanceof DHGenParameterSpec))
      throw new InvalidAlgorithmParameterException("Unsupported param spec");

    this.random = random;
    this.expSize = ((DHGenParameterSpec)genParamSpec).getExponentSize();
    this.keyLength = ((DHGenParameterSpec)genParamSpec).getPrimeSize();
  }

  protected AlgorithmParameters engineGenerateParameters()
  {
    //Use the DSS parameter generation algorithm

    try
    {
      AlgorithmParameterGenerator gen = 
        AlgorithmParameterGenerator.getInstance("DSA");
      gen.init(this.keyLength, random);
  
      AlgorithmParameters dsaParams = gen.generateParameters();
      DSAParameterSpec dsaSpec = (DSAParameterSpec)
        dsaParams.getParameterSpec(DSAParameterSpec.class);
      DHParameterSpec dhSpec = 
        new DHParameterSpec(dsaSpec.getP(), dsaSpec.getG(), this.expSize);
  
      AlgorithmParameters algParams =
        AlgorithmParameters.getInstance("DH");
      algParams.init(dhSpec);
      return algParams;
    }
    catch (NoSuchAlgorithmException e)
    {
      throw new ProviderException(e.getMessage());
    }
    catch (InvalidParameterSpecException e)
    {
      throw new RuntimeException("Internal error: " +e.getMessage());
    }
  }

  private static final boolean DUMMY = Licensed.VALID;
}
