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

package javax.crypto.spec;

import java.security.spec.AlgorithmParameterSpec;

/**
 * <p>This class specifies the set of parameters used for generating 
 * Diffie-Hellman (system) parameters for use in Diffie-Hellman key 
 * agreement. This is typically done by a central authority. 
 *
 * <p>The central authority, after computing the parameters, must send 
 * this information to the parties looking to agree on a secret key. 
 *
 * @see java.security.spec.AlgorithmParameterSpec
 * @see java.security.AlgorithmParameterGenerator
 * @see javax.crypto.spec.DHParameterSpec
 *
 * @version 0.98, 98/07/01
 * @author Ming Yung
 *
 */
public class DHGenParameterSpec implements AlgorithmParameterSpec
{
  private int primeSize, exponentSize;

  /**
   * Constructs a parameter set for the generation of Diffie-Hellman (system)
   * parameters.
   * <p> The constructed parameter set can be used to initialize an
   * AlgorithmParameterGenerator object for the generation of Diffie-Hellman parameters.
   *
   * @param primeSize the size (in bits) of the prime modulus.
   * @param exponentSize the size (in bits) of the random exponent.
   */
  public DHGenParameterSpec(int primeSize, int exponentSize)
  {
    this.primeSize = primeSize;
    this.exponentSize = exponentSize;
  }

  /**
   * Returns the size in bits of the prime modulus.
   *
   * @return the size in bits of the prime modulus
   */
  public int getPrimeSize()
  {
    return primeSize;
  }

  /**
   * Returns the size in bits of the random exponent (private value).
   *
   * @return the size in bits of the random exponent (private value)
   */
  public int getExponentSize()
  {
    return exponentSize;
  }
}
