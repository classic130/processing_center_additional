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
import java.security.spec.KeySpec;
import java.security.spec.InvalidKeySpecException;
import java.security.InvalidKeyException;
import java.security.InvalidParameterException;
import java.security.NoSuchAlgorithmException;
import java.security.NoSuchProviderException;
import java.util.Enumeration;


/**
 * This class represents a factory for secret keys. 
 *
 * <p>Key factories are used to convert keys (opaque cryptographic keys 
 * of type Key) into key specifications (transparent representations of 
 * the underlying key material), and vice versa. Secret key factories 
 * operate only on secret (symmetric) keys
 *
 * <p>Key factories are bi-directional, i.e., they allow to build an opaque 
 * key object from a given key specification (key material), or to retrieve 
 * the underlying key material of a key object in a suitable format. 
 *
 * <p>Application developers should refer to their provider's documentation 
 * to find out which key specifications are supported by the generateSecret 
 * and getKeySpec methods. For example, the SecretKeyFactory for DES of 
 * the Sun provider supports DESKeySpec, and the SecretKeyFactory for 
 * Triple DES of the same provider supports DESedeKeySpec. 
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
public class SecretKeyFactory
{
  private SecretKeyFactorySpi delegate;
  private Provider provider;
  private String algorithm;

  /**
   * Creates a SecretKeyFactory object.
   *
   * @param keyFacSpi the delegate 
   * @param provider the provider
   */
  protected SecretKeyFactory(SecretKeyFactorySpi macSpi, Provider provider,
                             String algorithm)
  {
    this.delegate = macSpi;
    this.provider = provider;
    this.algorithm = algorithm;
  }

  /**
   * Returns the algorithm name of this SecretKeyFactory object.
   *
   * <p>This is the same name that was specified in one of the getInstance calls that
   * created this SecretKeyFactory object.
   *
   * @return the algorithm name of this SecretKeyFactory object.
   */
  public final String getAlgorithm()
  {
    return this.algorithm;
  }

  /**
   * Generates a SecretKeyFactory object for the specified algorithm. If the
   * default provider package provides an implementation of the requested
   * key generator, an instance of SecretKeyFactory containing that
   * implementation is returned. If the requested factory is not
   * available in the default provider package, other provider packages
   * are searched.
   *
   * @param algorithm the standard name of the requested secret key 
   * algorithm. See Appendix A in the Java Cryptography Extension API 
   * Specification & Reference for information about standard algorithm names. 
   *
   * @return a SecretKeyFactory object for the specified secret key algorithm.
   *
   * @exception java.security.NoSuchAlgorithmException if the requested 
   * algorithm is not available in the default provider package or any of 
   * the other provider packages that were searched.
   */
  public static final SecretKeyFactory getInstance(String algorithm)
    throws NoSuchAlgorithmException
  {
    Provider[] provs = Security.getProviders();
    SecretKeyFactory retval = null;

    for (int i=0; i<provs.length; i++)
    {
      try
      {
        retval = SecretKeyFactory.getInstance(algorithm, provs[i].getName());
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

    throw new NoSuchAlgorithmException("SecretKeyFactory algorithm " +
      algorithm + " not supported");
  }


  /**
   * Generates a SecretKeyFactory object for the specified key algorithm from
   * the specified provider.
   *
   * @param algorithm the standard name of the requested secret key 
   * algorithm. See Appendix A in the Java Cryptography Extension API 
   * Specification & Reference for information about standard algorithm names. 
   * @param provider the name of the provider
   *
   * @return a SecretKeyFactory object for the specified secret key algorithm.
   *
   * @exception NoSuchAlgorithmException if the requested 
   * algorithm is not available in the default provider package or any of 
   * the other provider packages that were searched.
   * @exception NoSuchProviderException if the provider has 
   * not been configured.
   */
  public static final SecretKeyFactory getInstance(String algorithm,
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

      StringBuffer algName = new StringBuffer("SecretKeyFactory.");
  
      StringBuffer alt = new StringBuffer("Alg.Alias.SecretKeyFactory.");
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
      return new SecretKeyFactory((SecretKeyFactorySpi)cl.newInstance(),
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
   * Returns the provider of this SecretKeyFactory object.
   *
   * @return the name of the algorithm associated with this key factory.
   */
  public final Provider getProvider()
  {
    return this.provider;
  }

  /**
   * Generates a SecretKey object from the provided key specification 
   * (key material).
   *
   * @param keySpec - the specification (key material) of the secret key 
   *
   * @return the secret key
   *
   * @exception java.security.spec.InvalidKeySpecException if the given 
   * key specification is inappropriate for this key factory to produce 
   * a secret key.
   */
  public final SecretKey generateSecret(KeySpec keySpec) 
   throws InvalidKeySpecException
  {
    return delegate.engineGenerateSecret(keySpec);
  }

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
   * key specification is inappropriate for the given key, or the given key 
   * cannot be processed (e.g., the given key has an unrecognized
   * algorithm or format).
   */
  public final KeySpec getKeySpec(SecretKey key, Class keySpec) 
    throws InvalidKeySpecException
  {
    return delegate.engineGetKeySpec(key, keySpec);
  }

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
  public final SecretKey translateKey(SecretKey key) 
    throws InvalidKeyException
  {
    return delegate.engineTranslateKey(key);
  }
}
