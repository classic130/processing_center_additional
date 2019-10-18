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
 * <p>This class specifies the parameters used with the RC2 algorithm. 
 * 
 * <p>The parameters consist of an effective key size and optionally an 
 * 8-byte initialization vector (IV) (only in feedback mode). 
 * 
 * <p>This class can be used to initialize a Cipher object that 
 * implements the RC2 algorithm. 
 *
 * @see java.security.spec.AlgorithmParameterSpec
 *
 * @version 0.98, 98/08/05
 * @author Ming Yung 
 */
public class RC2ParameterSpec implements AlgorithmParameterSpec
{
  private byte iv[] = null;
  private int eKB;

  /**
   * Constructs a parameter set for RC2 from the given effective key 
   * size (in bits).
   * 
   * @param effectiveKeyBits the effective key size in bits 
   */
  public RC2ParameterSpec(int effectiveKeyBits)
  {
    this.eKB = effectiveKeyBits;
  }

  /**
   * Constructs a parameter set for RC2 from the given effective key 
   * size (in bits) and an 8-byte IV.
   * 
   * @param effectiveKeyBits the effective key size in bits 
   * @param iv  the buffer with the 8-byte IV.
   */
  public RC2ParameterSpec(int effectiveKeyBits, byte[] iv)
  {
    this(effectiveKeyBits, iv, 0);
  }

  /**
   * Constructs a parameter set for RC2 from the given effective key 
   * size (in bits) and IV. The IV is taken from iv, starting at offset.
   * 
   * @param  effectiveKeyBits the effective key size in bits 
   * @param iv  the buffer with IV.
   * @param offset  the offset in iv where the 8-byte IV starts.
   */
  public RC2ParameterSpec(int effectiveKeyBits, byte[] iv, int offset)
  {
    this.eKB = effectiveKeyBits;
    this.iv = new byte[8];
    System.arraycopy(iv, offset, this.iv, 0, 8);
  }

  /**
   * Returns the effective key size in bits.
   *
   * @return the effective key size in bits.
   */
  public int getEffectiveKeyBits()
  {
    return eKB;
  }

  /**
   * Returns the IV or null if this parameter set does not contain an IV.
   * 
   * @return the IV or null if this parameter set does not contain an IV.
   */
  public byte[] getIV()
  {
    return iv;
  }
}
