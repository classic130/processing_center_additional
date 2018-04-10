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

package javax.crypto;

import java.security.SecureRandom;
import java.security.spec.AlgorithmParameterSpec;
import java.security.InvalidAlgorithmParameterException;

/**
 * <p>This class defines the Service Provider Interface (SPI) for the 
 * KeyGenerator class. All the abstract methods in this class must 
 * be implemented by each cryptographic service provider who wishes 
 * to supply the implementation of a key generator for a particular
 * algorithm.
 *
 * @see javax.crypto.SecretKey
 * @see java.security.AlgorithmParameters
 * @see java.security.spec.AlgorithmParameterSpec
 *
 * @version 0.98, 98/07/01
 * @author Ming Yung
 *
 */
public abstract class KeyGeneratorSpi
{
  public KeyGeneratorSpi() {}

  /**
   * Initializes the key generator.
   *
   * @param random the source of randomness for this generator
   */
  protected abstract void engineInit(SecureRandom random);

  /**
   * Initializes the key generator with the specified parameter 
   * set and a user-provided source of randomness.
   *
   * @param params the key generation parameters
   * @param random the source of randomness for this key generator
   *
   * @exception java.security.InvalidAlgorithmParameterException if
   * params is inappropriate for this key generator
   */
  protected abstract void engineInit(AlgorithmParameterSpec params,
                                     SecureRandom random) 
    throws InvalidAlgorithmParameterException;

  /**
   * Initializes this key generator for a certain strength, using 
   * the given source of randomness.
   *
   * @param strength the strength of the key. This is an
   * algorithm-specific metric specified in number of bits.
   * @param random the source of randomness for this key generator
   */
  protected abstract void engineInit(int strength, SecureRandom random);

  /**
   * Generates a secret key.
   *
   * @return the new key
   */
  protected abstract SecretKey engineGenerateKey();
}
