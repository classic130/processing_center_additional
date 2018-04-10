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

import java.security.Key;
import java.security.InvalidKeyException;
import java.security.InvalidAlgorithmParameterException;
import java.security.spec.AlgorithmParameterSpec;

/**
 * <p>This class defines the Service Provider Interface (SPI) for the 
 * Mac class. All the abstract methods in this class must be implemented 
 * by each cryptographic service provider who wishes to supply the 
 * implementation of a particular MAC algorithm. 
 *
 * <p>Implementations are free to implement the Cloneable interface. 
 *
 * @version 0.98, 98/07/01
 * @author Ming Yung
 *
 */
public abstract class MacSpi
{
  public MacSpi() {}

  /**
   * Returns the length of the MAC in bytes.
   *
   * @return the MAC length in bytes.
   */
  protected abstract int engineGetMacLength();

  /**
   * Initializes the MAC with the given (secret) key and algorithm parameters.
   *
   * @param key the (secret) key.
   * @param params the algorithm parameters.
   *
   * @exception java.security.InvalidKeyException if the given key is
   * inappropriate for initializing this MAC.
   * @exception java.security.InvalidAlgorithmParameterException if the
   * given algorithm parameters are inappropriate for this MAC.
   */
  protected abstract void engineInit(Key key, AlgorithmParameterSpec params) 
    throws InvalidKeyException, InvalidAlgorithmParameterException;

  /**
   * Processes the given byte.
   *
   * @param input the input byte to be processed.
   */
  protected abstract void engineUpdate(byte input);

  /**
   * Processes the first len bytes in input, starting at offset.
   *
   * @param input the input buffer.
   * @param offset the offset in input where the input starts.
   * @param len the number of bytes to process.
   */
  protected abstract void engineUpdate(byte[] input, int offset, int len);

  /**
   * Completes the MAC computation and resets the MAC for further use, 
   * maintaining the secret key that the MAC was initialized with.
   *
   * @return the MAC result.
   */
  protected abstract byte[] engineDoFinal();

  /**
   * Resets the MAC for further use, maintaining the secret key that 
   * the MAC was initialized with.
   */
  protected abstract void engineReset();

  /**
   * Returns a clone if the implementation is cloneable.
   *
   * @return a clone if the implementation is cloneable.
   *
   * @exception java.lang.CloneNotSupportedException if this is called
   * on an implementation that does not support Cloneable.
   */
  public Object clone() throws CloneNotSupportedException {
    if (this instanceof Cloneable) 
    {
      return super.clone();
    } 
    else 
    {
      throw new CloneNotSupportedException();
    }
  }
}
