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
import java.security.SecureRandom;
import java.security.spec.AlgorithmParameterSpec;
import java.security.InvalidParameterException;
import java.security.InvalidAlgorithmParameterException;
import java.security.NoSuchAlgorithmException;
import java.security.NoSuchProviderException;
import java.util.Enumeration;


/**
 * <p>This class provides the functionality of a (symmetric) key generator. 
 *
 * <p>Key generators are constructed using one of the getInstance class 
 * methods of this class.
 *
 * <p>KeyGenerator objects are reusable, i.e., after a key has been 
 * generated, the same KeyGenerator object can be re-used to generate 
 * further keys.
 *
 * <p>There are two ways to generate a key: in an algorithm-independent 
 * manner, and in an algorithm-specific manner. The only difference 
 * between the two is the initialization of the object:
 *
 * <p>  Algorithm-Independent Initialization 
 *     All key generators share the concepts of a "strength" and a 
 *     source of randomness.  The measure of strength is universally 
 *     shared by all algorithms, though it is interpreted differently 
 *     for different algorithms. There is an init method in this
 *     KeyGenerator class that takes these two universally shared types 
 *     of arguments. There is also one that takes just a strength argument, 
 *     and uses a system-provided source of randomness, and one that takes 
 *     just a source of randomness.  
 *
 *     Since no other parameters are specified when you call the above
 *     algorithm-independent init methods, it is up to the provider what 
 *     to do about the algorithm-specific parameters (if any) to be 
 *     associated with each of the keys. 
 *
 * <p>  Algorithm-Specific Initialization 
 *     For situations where a set of algorithm-specific parameters 
 *     already exists, there are two init methods that have an 
 *     AlgorithmParameterSpec argument. One also has a SecureRandom 
 *     argument, while the source of randomness is system-provided for
 *     the other. 
 *
 * <p>In case the client does not explicitly initialize the KeyGenerator 
 * (via a call to an init method), each provider must supply (and document) 
 * a default initialization. 
 *
 * @see javax.crypto.SecretKey
 * @see java.security.AlgorithmParameters
 * @see java.security.spec.AlgorithmParameterSpec
 *
 * @version 0.98, 98/07/01
 * @author Ming Yung
 *
 */
public class KeyGenerator
{
  private KeyGeneratorSpi delegate;
  private Provider provider;
  private String algorithm;

  /**
   * Creates a KeyGenerator object.
   *
   * @param keyGenSpi the delegate
   * @param provider the provider
   * @param algorithm the algorithm
   */
  protected KeyGenerator(KeyGeneratorSpi keyGenSpi, Provider provider, 
                         String algorithm)
  {
    this.delegate = keyGenSpi;
    this.provider = provider;
    this.algorithm = algorithm;
  }

  /**
   * Returns the standard name of the key algorithm. 
   * <p>This is the same name that was specified in one of the getInstance 
   * calls that created this KeyGenerator object.
   *
   * @return the standard algorithm name.
   */
  public final String getAlgorithm()
  {
    return this.algorithm;
  }

  /**
   * Generates a KeyGenerator object for the specified algorithm. If the 
   * default provider package provides an implementation of the requested 
   * key generator, an instance of KeyGenerator containing that 
   * implementation is returned. If the requested key generator is not 
   * available in the default provider package, other provider packages 
   * are searched.
   * 
   * @param algorithm the standard name of the requested key
   * algorithm. See Appendix A in the Java Cryptography
   * Extension API Specification & Reference for information
   * about standard algorithm names.
   *
   * @return the new KeyGenerator object
   *
   * @exception java.security.NoSuchAlgorithmException if a key
   * generator for the requested algorithm is not available
   * in the default provider package or any of the other provider packages 
   * that were searched.
   */
  public static final KeyGenerator getInstance(String algorithm)
    throws NoSuchAlgorithmException
  {
    Provider[] provs = Security.getProviders();
    KeyGenerator retval = null;

    for (int i=0; i<provs.length; i++)
    {
      try
      {
        retval = KeyGenerator.getInstance(algorithm, provs[i].getName());
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

    throw new NoSuchAlgorithmException("KeyGenerator algorithm " 
      + algorithm + " not supported");
  }

  /**
   * Generates a keyGenerator object for the specified key algorithm from
   * the specified provider.
   *
   * @param algorithm the standard name of the requested key
   * algorithm. See Appendix A in the Java Cryptography
   * Extension API Specification & Reference for information
   * about standard algorithm names.
   * @param provider the provider
   *
   * @return the new KeyGenerator object
   *
   * @exception java.security.NoSuchAlgorithmException if a key
   * generator for the requested algorithm is not available
   * @exception java.security.NoSuchProviderException if the requested
   * provider is not available
   */
  public static final KeyGenerator getInstance(String algorithm, 
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

      StringBuffer algName = new StringBuffer("KeyGenerator.");

      StringBuffer alt = new StringBuffer("Alg.Alias.KeyGenerator.");
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
      return new KeyGenerator((KeyGeneratorSpi)cl.newInstance(), 
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
   * Returns the provider of this KeyGenerator object.
   *
   * @return the provider of this KeyGenerator object
   */
  public final Provider getProvider()
  {
    return this.provider;
  }

  /**
   * Initializes the key generator.
   *
   * @param random the source of randomness for this generator
   */
  public final void init(SecureRandom random)
  {
    delegate.engineInit(random);
  }

  /**
   * Initializes the key generator with the specified parameter 
   * set and a system-provided source of randomness.
   *
   * @param params the key generation parameters
   *
   * @exception java.security.InvalidAlgorithmParameterException if the
   * given parameters are inappropriate for this key generator
   */ 
  public final void init(AlgorithmParameterSpec params) 
    throws InvalidAlgorithmParameterException
  {
    init(params, new SecureRandom());
  }

  /**
   * Initializes the key generator with the specified parameter 
   * set and a user-provided source of randomness.
   *
   * @param params the key generation parameters
   * @param random the source of randomness
   *
   * @exception java.security.InvalidAlgorithmParameterException if the
   * given parameters are inappropriate for this key generator
   */
  public final void init(AlgorithmParameterSpec params,
                               SecureRandom random) 
    throws InvalidAlgorithmParameterException
  {
    delegate.engineInit(params, random);
  }

  /**
   * Initializes this key generator for a certain strength, using 
   * a system-provided source of randomness.
   *
   * @param strength the strength of the key. This is an
   * algorithm-specific metric specified in number of bits.
   */
  public final void init(int strength)
  {
    init(strength, new SecureRandom());
  }

  /**
   * Initializes this key generator for a certain strength, using 
   * the given source of randomness.
   *
   * @param strength the strength of the key. This is an
   * algorithm-specific metric specified in number of bits.
   * @param random the source of randomness
   */
  public final void init(int strength, SecureRandom random)
  {
    delegate.engineInit(strength, random);
  }

  /**
   * Generates a secret key.
   *
   * @return the new key
   */
  public final SecretKey generateKey()
  {
    return delegate.engineGenerateKey();
  }
}
