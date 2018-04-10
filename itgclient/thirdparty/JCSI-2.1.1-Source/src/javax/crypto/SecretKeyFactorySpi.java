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

import java.security.spec.KeySpec;
import java.security.spec.InvalidKeySpecException;
import java.security.InvalidKeyException;

/**
 * This class defines the Service Provider Interface (SPI) for the 
 * SecretKeyFactory class.  All the abstract methods in this class 
 * must be implemented by each cryptographic service provider who wishes 
 * to supply the implementation of a secret-key factory for a particular
 * algorithm. 
 *
 * A provider should document all the key specifications supported by its 
 * secret key factory.  For example, the Sun provider SecretKeyFactory 
 * for DES keys supports DESKeySpec as a transparent representation of 
 * DES keys, and the SecretKeyFactory for Triple DES keys supports 
 * DESedeKeySpec as a transparent representation of Triple DES keys. 
 *
 * @see javax.crypto.SecretKey
 * @see java.security.Key
 * @see java.security.KeyFactory
 * @see java.security.spec.KeySpec
 * @see javax.crypto.spec.DESKeySpec
 * @see javax.crypto.spec.DESedeKeySpec
 * @see javax.crypto.spec.PBEKeySpec
 *
 * @version 0.98, 98/07/01
 * @author Ming Yung
 *
 */
public abstract class SecretKeyFactorySpi
{
   public SecretKeyFactorySpi() {}

  /**
   * Generates a SecretKey object from the provided key specification 
   * (key material).
   *
   * @param keySpec the specification (key material) of the secret key 
   *
   * @return the secret key
   * 
   * @exception java.security.spec.InvalidKeySpecException if the given 
   * key specification is inappropriate for this key factory to produce 
   * a secret key.
   *
   */
  protected abstract SecretKey engineGenerateSecret(KeySpec keySpec) 
   throws InvalidKeySpecException;

  /**
   * Returns a specification (key material) of the given key object in 
   * the requested format.
   *
   * @param key the key 
   * @param keySpec the requested format in which the key material shall 
   * be returned 
   *
   * @return the underlying key specification (key material) in the 
   * requested format
   *
   * @exception java.security.spec.InvalidKeySpecException if the requested 
   * specification is inappropriate for the given key (e.g., the algorithms
   * associated with key and keySpec do not match, or key references a key on a
   * cryptographic hardware device whereas keySpec is the specification of a
   * software-based key), or the given key cannot be dealt with (e.g., the given
   * key has an algorithm or format not supported by this secret-key factory).
   */
  protected abstract KeySpec engineGetKeySpec(SecretKey key, Class keySpec) 
    throws InvalidKeySpecException;

  /**
   * Translates a key object, whose provider may be unknown or potentially 
   * untrusted, into a corresponding key object of this key factory.
   *
   * @param key the key whose provider is unknown or untrusted 
   *
   * @return the translated key
   *
   * @exception java.security.InvalidKeyException if the given key cannot 
   * be processed by this key factory.
   */
  protected abstract SecretKey engineTranslateKey(SecretKey key) 
    throws InvalidKeyException;
}
