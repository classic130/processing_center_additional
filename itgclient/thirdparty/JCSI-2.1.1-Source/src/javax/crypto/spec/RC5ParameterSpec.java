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
import java.security.InvalidAlgorithmParameterException;

/**
 * <p>This class specifies the parameters used with the RC5 algorithm. 
 *
 * <p>The parameters consist of a version number, a rounds count, 
 * a word size, and optionally an initialization vector (IV) (only in 
 * feedback mode). 
 *
 * <p>This class can be used to initialize a Cipher object that implements 
 * the RC5 algorithm as supplied by RSA Data Security, Inc., or parties 
 * authorized by RSA Data Security. 
 *
 * @see java.security.spec.AlgorithmParameterSpec
 *
 * @version 0.98, 98/08/05
 * @author Ming Yung 
 */
public class RC5ParameterSpec implements AlgorithmParameterSpec
{
  private int version;
  private int rounds;
  private int wordSize;
  private byte[] iv = null;

  /**
   * Constructs a parameter set for RC5 from the given version, number 
   * of rounds and word size (in bits). 
   *
   * @param version  the version.
   * @param rounds  the number of rounds.
   * @param wordSize the word size in bits.
   */
  public RC5ParameterSpec(int version, int rounds, int wordSize)
  {
    this.version = version;
    this.rounds = rounds;
    this.wordSize = wordSize;
  }

  /**
   * Constructs a parameter set for RC5 from the given version, number 
   * of rounds, word size (in bits), and IV. Note that the size of 
   * the IV (block size) must be twice the word size.
   * 
   * @param version  the version.
   * @param rounds  the number of rounds.
   * @param wordSize the word size in bits.
   * @param iv the buffer with the IV.
   */
  public RC5ParameterSpec(int version, int rounds, int wordSize, byte[] iv)
  {
    this(version, rounds, wordSize, iv, 0);
  }

  /**
   * Constructs a parameter set for RC5 from the given version, number 
   * of rounds, word size (in bits), and IV. The IV is taken from iv, 
   * starting at offset. Note that the size of the IV (block size), 
   * starting at offset, must be twice the word size. 
   *
   * @param version  the version.
   * @param rounds  the number of rounds.
   * @param wordSize the word size in bits.
   * @param iv the buffer with the IV.
   * @param offset the offset in iv where the IV starts.
   */
  public RC5ParameterSpec(int version, int rounds, int wordSize,
                          byte[] iv, int offset) 
                               
  {
    if (iv == null)
      throw new IllegalArgumentException("IV is null");

    if (4*(iv.length - offset) != wordSize)
      throw new IllegalArgumentException(
                   "IV length not equal to twice wordsize");

    this.version = version;
    this.rounds = rounds;
    this.wordSize = wordSize;
    this.iv = new byte[wordSize/4];
    System.arraycopy(iv, offset, this.iv, 0, wordSize/4);
  }

  /**
   * Returns the version
   *
   * @return the version.
   */
  public int getVersion()
  {
    return this.version;
  }

  /**
   * Returns the number of rounds
   *
   * @return the number of rounds.
   */
  public int getRounds()
  {
    return this.rounds;
  }

  /**
   * Returns the word size in bits.
   *
   * @return the word size in bits.
   */
  public int getWordSize()
  {
    return this.wordSize;
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
