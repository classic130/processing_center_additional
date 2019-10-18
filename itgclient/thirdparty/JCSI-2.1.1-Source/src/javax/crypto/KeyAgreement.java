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

import java.security.Security;
import java.security.Provider;
import java.security.Key;
import java.security.PrivateKey;
import java.security.PublicKey;
import java.security.SecureRandom;
import java.security.InvalidKeyException;
import java.security.InvalidParameterException;
import java.security.InvalidAlgorithmParameterException;
import java.security.NoSuchProviderException;
import java.security.NoSuchAlgorithmException;
import java.security.spec.AlgorithmParameterSpec;
import java.util.Enumeration;

/**
 * This class provides the functionality of a key agreement (or key
 * exchange) protocol. The keys involved in establishing a shared secret
 * are created by one of the key generators (KeyPairGenerator or
 * KeyGenerator), a KeyFactory, or as a result from an intermediate phase
 * of the key agreement protocol (see doPhase). For each of the
 * correspondents in the key exchange, doPhase needs to be called. For
 * example, if this key exchange is with one other party, doPhase needs
 * to be called once, with the lastPhase flag set to true. If this key
 * exchange is with two other parties, doPhase needs to be called twice,
 * the first time setting the lastPhase flag to false, and the second
 * time setting it to true. There may be any number of parties involved
 * in a key exchange.
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
public class KeyAgreement
{
  private static final int UNINITIALIZED = 0;
  private static final int INITIALIZED = 1;
  private static final int COMPLETED = 2;

  private int state;
  private Provider provider;
  private String algorithm;
  private KeyAgreementSpi delegate;

  /**
   * Creates a KeyAgreement object.
   *
   * @param keyAgreeSpi the delegate
   * @param provider the provider
   * @param algorithm the algorithm
   */
  protected KeyAgreement(KeyAgreementSpi keyAgreeSpi,
                       Provider provider, String algorithm)
  {
    this.delegate = keyAgreeSpi;
    this.provider = provider;
    this.algorithm = algorithm;
  }

  /**
   * Returns the standard name of the key agreement algorithm. 
   * See Appendix A in the Java Cryptography Extension API Specification &
   * Reference for information about standard algorithm names.
   *
   * @return the standard algorithm name.
   */
  public final java.lang.String getAlgorithm()
  {
    return algorithm;
  }

  /**
   * Generates a KeyAgreement object that implements the specified key 
   * agreement algorithm. If the default provider package provides an
   * implementation of the requested key agreement algorithm, an instance 
   * of KeyAgreement containing that implementation is returned.
   * If the algorithm is not available in the default provider package, 
   * other provider packages are searched.
   *
   * @param algorithm the standard name of the requested key
   * agreement algorithm. See Appendix A in the Java
   * Cryptography Extension API Specification & Reference for
   * information about standard algorithm names.
   *
   * @return the new KeyAgreement object
   *
   * @exception java.security.NoSuchAlgorithmException if the requested
   * key agreement algorithm is not available
   */
  public static final KeyAgreement getInstance(String algorithm) 
    throws NoSuchAlgorithmException
  {
    Provider[] provs = Security.getProviders();

    KeyAgreement retval = null;

    for (int i=0; i<provs.length; i++)
    {
      try
      {
        retval = KeyAgreement.getInstance(algorithm, provs[i].getName());
      }
      catch (NoSuchProviderException e)
      {
        throw new RuntimeException("Internal error: " + e.getMessage());
      }
      catch (NoSuchAlgorithmException e)
      {
        //ignore
      }

      if (retval != null)
        return retval;
    }

    throw new NoSuchAlgorithmException("KeyAgreement algorithm " +
      algorithm + " not supported");
  }

  /**
   * Generates a KeyAgreement object for the specified key agreement 
   * algorithm from the specified provider.
   *
   * @param algorithm the standard name of the requested key
   * agreement algorithm. See Appendix A in the Java
   * Cryptography Extension API Specification & Reference for
   * information about standard algorithm names.
   * @param provider the provider
   *
   * @return the new KeyAgreement object
   *
   * @exception java.security.NoSuchAlgorithmException if the requested
   * key agreement algorithm is not available
   * @exception java.security.NoSuchProviderException if the requested
   * provider is not available
   */
  public static final KeyAgreement getInstance(String algorithm, 
                                               String provider) 
    throws NoSuchAlgorithmException, NoSuchProviderException
  {
    if (provider == null)
      throw new InvalidParameterException("Null provider supplied");

    try
    {
      Provider prov = Security.getProvider(provider);
      if (prov == null)
        throw new NoSuchProviderException("Provider " + provider + " not found");

      StringBuffer algName = new StringBuffer("KeyAgreement.");

      StringBuffer alt = new StringBuffer("Alg.Alias.KeyAgreement.");
      alt.append(algorithm);
//    String alg = prov.getProperty(alt.toString());
      String alg = getProviderProperty(alt.toString(), prov);

      if (alg != null)
        algName.append(alg);
      else
        algName.append(algorithm);
 
//    String className = prov.getProperty(algName.toString());
      String className = getProviderProperty(algName.toString(), prov);

      Class cl = Class.forName(className, true,
        Thread.currentThread().getContextClassLoader());
      return new KeyAgreement((KeyAgreementSpi)cl.newInstance(), 
                              prov, algorithm);
    }
    catch (Exception e)
    {
      throw new NoSuchAlgorithmException("Algorithm " + algorithm +
                                         " not found in provider " +
                                         provider);
    }
  }

  // Check for case-insensitive matches
  //
  private static String getProviderProperty(String name, Provider prov)
  {
      String retval = null;
      for (Enumeration en = prov.keys(); en.hasMoreElements() ; ) {
        String matchKey = (String)en.nextElement();
        if (name.equalsIgnoreCase(matchKey)) {
          retval = prov.getProperty(matchKey);
          break;
        }
      }
      return retval;
  }

  /**
   * Returns the provider of this KeyAgreement object.
   *
   * @return the provider of this KeyAgreement object
   */
  public final Provider getProvider()
  {
    return provider;
  }

  /**
   * Initializes this key agreement with the given key, which is 
   * required to contain all the algorithm parameters required for 
   * this key agreement. 
   *
   * @param key the party's private information. For example, in
   * the case of the Diffie-Hellman key agreement, this would
   * be the party's own Diffie-Hellman private key.
   *
   * @exception java.security.InvalidKeyException if the given key is
   * inappropriate for this key agreement, e.g., is of the
   * wrong type or has an incompatible algorithm type.
   */
  public final void init(Key key) throws InvalidKeyException
  {
    init(key, new SecureRandom());
  }

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
  public final void init(Key key, SecureRandom random) 
    throws InvalidKeyException
  {
    this.state = INITIALIZED;
    delegate.engineInit(key, random);
  }

  /**
   * Initializes this key agreement with the given key and set of 
   * algorithm parameters. 
   *
   * <p>If this key agreement requires any random bytes, a system-provided 
   * source of randomness is used.
   *
   * @param key the party's private information. For example, in
   * the case of the Diffie-Hellman key agreement, this would
   * be the party's own Diffie-Hellman private key.
   * @param params the key agreement parameters
   *
   * @exception java.security.InvalidKeyException if the given key is
   * inappropriate for this key agreement, e.g., is of the
   * @exception java.security.InvalidAlgorithmParameterException if the
   * given parameters are inappropriate for this key agreement.
   */
  public final void init(Key key, AlgorithmParameterSpec params) 
    throws InvalidKeyException, InvalidAlgorithmParameterException
  {
    init(key, params, new SecureRandom());
  }

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
  public final void init(Key key, AlgorithmParameterSpec params,
                                     SecureRandom random) 
    throws InvalidKeyException, InvalidAlgorithmParameterException
  {
    this.state = INITIALIZED;
    delegate.engineInit(key, params, random);
  }

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
   *
   * @exception java.security.InvalidKeyException if the given key is
   * inappropriate for this phase.
   * @exception java.lang.IllegalStateException if this key agreement
   * has not been initialized.
   */
  public final Key doPhase(Key key, boolean lastPhase) 
    throws InvalidKeyException, IllegalStateException
  {
    if (state != INITIALIZED)
      throw new IllegalStateException("Agreement not yet initialized");

    Key retval = delegate.engineDoPhase(key, lastPhase);

    if (lastPhase)
      state = COMPLETED;

    return retval;
  }

  /**
   * Generates the shared secret and returns it in a new buffer. 
   *
   * <p>This method resets this KeyAgreement object, so that it can 
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
  public final byte[] generateSecret() throws IllegalStateException
  {
    if (state != COMPLETED)
      throw new IllegalStateException("Agreement not yet completed");

    return delegate.engineGenerateSecret();
  }

  /**
   * Generates the shared secret, and places it into the buffer 
   * sharedSecret, beginning at offset. 
   *
   * <p>If the sharedSecret buffer is too small to hold the result, 
   * a ShortBufferException is thrown. In this case, this call should be
   * repeated with a larger output buffer. 
   *
   * <p>This method resets this KeyAgreement object, so that it can 
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
   * @exception ShortBufferException if the given output buffer is too
   * small to hold the secret
   */
  public final int generateSecret(byte[] sharedSecret, int offset) 
    throws IllegalStateException, ShortBufferException
  {
    if (state != COMPLETED)
      throw new IllegalStateException("Agreement not yet completed");

    return delegate.engineGenerateSecret(sharedSecret, offset);
  }

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
   *
   */
  public final SecretKey generateSecret(String algorithm) 
    throws IllegalStateException, NoSuchAlgorithmException, 
           InvalidKeyException
  {
    if (state != COMPLETED)
      throw new IllegalStateException("Agreement not yet completed");

    return delegate.engineGenerateSecret(algorithm);
  }
}
