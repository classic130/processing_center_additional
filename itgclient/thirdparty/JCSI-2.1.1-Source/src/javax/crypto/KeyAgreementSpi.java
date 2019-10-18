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
import java.security.SecureRandom;
import java.security.InvalidKeyException;
import java.security.InvalidAlgorithmParameterException;
import java.security.NoSuchAlgorithmException;
import java.security.spec.AlgorithmParameterSpec;
import java.security.AlgorithmParameterGenerator;

/**
 * <p>This class defines the Service Provider Interface (SPI) for the
 * KeyAgreement class. All the abstract methods in this class must be
 * implemented by each cryptographic service provider who wishes to
 * supply the implementation of a particular key agreement algorithm.
 *
 * <p>The keys involved in establishing a shared secret are created by one
 * of the key generators (KeyPairGenerator or KeyGenerator), a
 * KeyFactory, or as a result from an intermediate phase of the key
 * agreement protocol (see engineDoPhase).
 *
 * <p>For each of the correspondents in the key exchange, engineDoPhase
 * needs to be called. For example, if the key exchange is with one other
 * party, engineDoPhase needs to be called once, with the lastPhase flag
 * set to true. If the key exchange is with two other parties,
 * engineDoPhase needs to be called twice, the first time setting the
 * lastPhase flag to false, and the second time setting it to true. There
 * may be any number of parties involved in a key exchange.
 *
 * @see java.security.AlgorithmParameterGenerator
 * @see java.security.AlgorithmParameters
 * @see java.security.KeyPairGenerator
 * @see java.security.Key
 * @see java.security.KeyFactory
 * @see javax.crypto.KeyGenerator
 * @see javax.crypto.SecretKey
 *
 * @version 0.98, 98/07/01
 * @author Ming Yung
 *
 */
public abstract class KeyAgreementSpi
{
  /**
   * Initializes this key agreement with the given key and 
   * source of randomness. The given key is required to 
   * contain all the algorithm parameters required for this key agreement. 
   *
   * <p>If the key agreement algorithm requires random bytes, it gets 
   * them from the given source of randomness, random. However, if 
   * the underlying algorithm implementation does not require any random 
   * bytes, random is ignored.
   *
   * @param key the party's private information. For example, in
   * the case of the Diffie-Hellman key agreement, this would
   * be the party's own Diffie-Hellman private key.
   * @param random the source of randomness
   *
   * @exception java.security.InvalidKeyException if the given key is
   * inappropriate for this key agreement, e.g., is of the
   * wrong type or has an incompatible algorithm type.
   */
  protected abstract void engineInit(Key key, SecureRandom random) 
    throws InvalidKeyException;

  /**
   * Initializes this key agreement with the given key, set of 
   * algorithm parameters, and source of randomness.
   *
   * @param key the party's private information. For example, in
   * the case of the Diffie-Hellman key agreement, this would
   * be the party's own Diffie-Hellman private key.
   * @param params the key agreement parameters
   * @param random the source of randomness
   *
   * @exception java.security.InvalidKeyException if the given key is
   * inappropriate for this key agreement, e.g., is of the
   * @exception java.security.InvalidAlgorithmParameterException if the
   * given parameters are inappropriate for this key agreement.
   */
  protected abstract void engineInit(Key key, AlgorithmParameterSpec params,
                                     SecureRandom random) 
    throws InvalidKeyException, InvalidAlgorithmParameterException;

  /**
   * Executes the next phase of this key agreement with the given 
   * key that was received from one of the other parties involved 
   * in this key agreement.
   *
   * @param key the key for this phase. For example, in the case of
   * Diffie-Hellman between 2 parties, this would be the other
   * party's Diffie-Hellman public key.
   * @param lastPhase flag which indicates whether or not this is
   * the last phase of this key agreement.
   *
   * @return the (intermediate) key resulting from this phase, or null
   * if this phase does not yield a key
   * @exception java.security.InvalidKeyException if the given key is
   * inappropriate for this phase.
   * @exception java.lang.IllegalStateException if this key agreement
   * has not been initialized.
   */
  protected abstract Key engineDoPhase(Key key, boolean lastPhase) 
    throws InvalidKeyException, IllegalStateException;

  /**
   * Generates the shared secret and returns it in a new buffer. 
   *
   * <p>This method resets this KeyAgreementSpi object, so that it can 
   * be reused for further key agreements. Unless this key agreement 
   * is reinitialized with one of the engineInit methods, the same 
   * private information and algorithm parameters will be used for 
   * subsequent key agreements.
   *
   * @return the new buffer with the shared secret
   *
   * @exception java.lang.IllegalStateException if this key agreement
   * has not been completed yet
   */
  protected abstract byte[] engineGenerateSecret() 
    throws IllegalStateException;

  /**
   * Generates the shared secret, and places it into the buffer 
   * sharedSecret, beginning at offset. 
   *
   * <p>If the sharedSecret buffer is too small to hold the result, 
   * a ShortBufferException is thrown. In this case, this call should be
   * repeated with a larger output buffer. 
   *
   * <p>This method resets this KeyAgreementSpi object, so that it can 
   * be reused for further key agreements. Unless this key agreement is
   * reinitialized with one of the engineInit methods, the same private 
   * information and algorithm parameters will be used for subsequent
   * key agreements.
   *
   * @param sharedSecret the buffer for the shared secret
   * @param offset the offset in sharedSecret where the shared
   * secret will be stored
   *
   * @return the number of bytes placed into sharedSecret
   *
   * @exception java.lang.IllegalStateException if this key agreement
   * has not been completed yet
   * @exception  ShortBufferException if the given output buffer is too
   * small to hold the secret
   */
  protected abstract int engineGenerateSecret(byte[] sharedSecret, int offset) 
    throws IllegalStateException, ShortBufferException;

  /**
   * Creates the shared secret and returns it as a secret key object 
   * of the requested algorithm type. 
   *
   * <p>This method resets this KeyAgreementSpi object, so that it can be 
   * reused for further key agreements. Unless this key agreement is
   * reinitialized with one of the engineInit methods, the same private 
   * information and algorithm parameters will be used for subsequent
   * key agreements.
   *
   * @param algorithm the requested secret key algorithm
   *
   * @return the shared secret key
   *
   * @exception java.lang.IllegalStateException if this key agreement
   * has not been completed yet
   * @exception java.security.NoSuchAlgorithmException if the requested
   * secret key algorithm is not available
   * @exception java.security.InvalidKeyException if the shared secret
   * key material cannot be used to generate a secret key of
   * the requested algorithm type (e.g., the key material is too short)
   */
  protected abstract SecretKey engineGenerateSecret(String algorithm) 
    throws IllegalStateException, NoSuchAlgorithmException, 
           InvalidKeyException;

}
