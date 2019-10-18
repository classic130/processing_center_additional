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
import java.security.Key;
import java.security.Provider;
import java.security.InvalidKeyException;
import java.security.InvalidParameterException;
import java.security.InvalidAlgorithmParameterException;
import java.security.spec.AlgorithmParameterSpec;
import java.security.NoSuchAlgorithmException;
import java.security.NoSuchProviderException;
import java.lang.IllegalStateException;
import java.util.Enumeration;


/**
 * <p>This class provides the functionality of a "message authentication code" 
 * (MAC). 
 *
 * <p>A MAC provides a way to check the integrity of information 
 * transmitted over or stored in an unreliable medium, based on a secret key.
 * Typically, message authentication codes are used between two parties 
 * that share a secret key in order to validate information transmitted
 * between these parties. 
 *
 * <p>A MAC mechanism that is based on cryptographic hash functions is 
 * referred to as HMAC. HMAC can be used with any cryptographic hash
 * function, e.g., MD5 or SHA-1, in combination with a secret shared key. 
 * HMAC is specified in RFC 2104.
 *
 * @version 0.98, 98/07/01
 * @author Ming Yung
 *
 */
public class Mac
{
  private MacSpi delegate;
  private Provider provider;
  private String algorithm;
  private int state;
  private static final int UNINITIALIZED = 0;
  private static final int INITIALIZED = 1;

  /**
   * Creates a MAC object.
   *
   * @param macSpi the delegate
   * @param provider the provider
   * @param algorithm the algorithm
   */
  protected Mac(MacSpi macSpi, Provider provider, String algorithm)
  {
    this.delegate = macSpi;
    this.provider = provider;
    this.algorithm = algorithm;
  }

  /**
   * Returns the standard name of the MAC algorithm. See Appendix A 
   * in the Java Cryptography Extension API Specification & Reference 
   * for information about standard algorithm names.
   *
   * <p>This is the same name that was specified in one of the 
   * getInstance calls that created this Mac object.
   *
   * @return the standard algorithm name.
   */
  public final String getAlgorithm()
  {
    return this.algorithm;
  }

  /**
   * Generates an Mac object that implements the specified MAC 
   * algorithm. If the default provider package provides an implementation 
   * of the requested MAC algorithm, an instance of Mac containing that 
   * implementation is returned. If the algorithm is not available in the 
   * default provider package, other provider packages are searched.
   *
   * @param algorithm the standard name of the requested MAC
   * algorithm. See Appendix A in the Java Cryptography
   * Extension API Specification & Reference for information
   * about standard algorithm names.
   *
   * @return the new Mac object.
   *
   * @exception java.security.NoSuchAlgorithmException if the requested
   * MAC algorithm is not available.
   */
  public static final Mac getInstance(String algorithm) 
    throws NoSuchAlgorithmException
  {
    Provider[] provs = Security.getProviders();

    Mac retval = null;
    for (int i=0; i<provs.length; i++)
    {
      try
      {
        retval = Mac.getInstance(algorithm, provs[i].getName());
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

    throw new NoSuchAlgorithmException("Mac algorithm " + 
      algorithm + " not supported");
  }

  /**
   * Generates an Mac object for the specified MAC algorithm from 
   * the specified provider.
   *
   * @param algorithm the standard name of the requested MAC
   * algorithm. See Appendix A in the Java Cryptography
   * Extension API Specification & Reference for information
   * about standard algorithm names.
   * @param provider the provider
   *
   * @return the new Mac object.
   *
   * @exception java.security.NoSuchAlgorithmException if the requested
   * MAC algorithm is not available.
   * @exception java.security.NoSuchProviderException if the requested
   * provider is not available.
   */
  public static final Mac getInstance(String algorithm, String provider) 
    throws NoSuchAlgorithmException, NoSuchProviderException
  {
    if (provider == null)
        throw new InvalidParameterException("Null provider is supplied");

    try
    {
      Provider prov = Security.getProvider(provider);

      if (prov == null)
        throw new NoSuchProviderException("Provider " + provider + " not found");

      StringBuffer algName = new StringBuffer("Mac.");

      StringBuffer alt = new StringBuffer("Alg.Alias.Mac.");
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
      return new Mac((MacSpi)cl.newInstance(), prov, algorithm);
    }
    catch (Exception e)
    {
      throw new NoSuchAlgorithmException("Mac algorithm " + algorithm +
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
   * Returns the provider of this Mac object.
   *
   * @return the provider of this Mac object.
   */
  public final Provider getProvider()
  {
    return this.provider;
  }

  /**
   * Returns the length of the MAC in bytes.
   *
   * @return the MAC length in bytes.
   */
  public final int getMacLength()
  {
    return delegate.engineGetMacLength();
  }

  /**
   * Initializes the MAC with the given (secret) key.
   *
   * @param key the (secret) key.
   *
   * @exception java.security.InvalidKeyException if the given key is
   * inappropriate for initializing this MAC.
   */
  public final void init(Key key) 
    throws InvalidKeyException
  {
    try
    {
      this.init(key, null);
    }
    catch (InvalidAlgorithmParameterException e)
    {
      throw new RuntimeException("Need algorithm parameters to initialize");
    }
  }

  /**
   * Initializes the MAC with the given (secret) key and algorithm parameters.
   *
   * @param key the (secret) key.
   * @param params the algorithm parameters.
   *
   * @exception java.security.InvalidKeyException if the given key is
   * inappropriate for initializing this MAC.
   * @exception InvalidAlgorithmParameterException if the given algorithm
   * parameters are inappropriate for this MAC.
   */
  public final void init(Key key, AlgorithmParameterSpec params) 
    throws InvalidKeyException, InvalidAlgorithmParameterException
  {
    state = INITIALIZED;
    delegate.engineInit(key, params);
  }

  /**
   * Processes the given byte.
   *
   * @param input the input byte to be processed.
   *
   * @exception java.lang.IllegalStateException if this Mac has not
   * been initialized.
   */
  public final void update(byte input)
    throws IllegalStateException
  {
    if (state != INITIALIZED) 
      throw new IllegalStateException("Not yet initialized");

    delegate.engineUpdate(input);
  }

  /**
   * Processes the given array of bytes.
   *
   * @param input the array of bytes to be processed.
   *
   * @exception java.lang.IllegalStateException if this Mac has not
   * been initialized.
   */
  public final void update(byte[] input)
    throws IllegalStateException
  {
    update(input, 0, input.length);
  }

  /**
   * Processes the first len bytes in input, starting at offset.
   *
   * @param input the input buffer.
   * @param offset the offset in input where the input starts.
   * @param len the number of bytes to process.
   *
   * @exception java.lang.IllegalStateException if this Mac has not
   * been initialized.
   */
  public final void update(byte[] input, int offset, int len)
    throws IllegalStateException
  {
    if (state != INITIALIZED) 
      throw new IllegalStateException("Not yet initialized");

    delegate.engineUpdate(input, offset, len);
  }


  /**
   * <p>Finishes the MAC operation. 
   *
   * <p>A call to this method resets this Mac object to the state it was 
   * in when previously initialized via a call to init(Key) or 
   * init(Key, AlgorithmParameterSpec). That is, the object is reset 
   * and available to generate another MAC from the same key, if desired, 
   * via new calls to update and doFinal. (In order to reuse this Mac 
   * object with a different key, it must be reinitialized via a call to 
   * init(Key) or init(Key, AlgorithmParameterSpec).
   *
   * @return the MAC result.
   *
   * @exception java.lang.IllegalStateException if this Mac has not
   * been initialized.
   */
  public final byte[] doFinal() throws IllegalStateException
  {
    if (state != INITIALIZED) 
      throw new IllegalStateException("Not yet initialized");

    return delegate.engineDoFinal();
  }

  /**
   * <p>Finishes the MAC operation. 
   *
   * <p>A call to this method resets this Mac object to the state it was 
   * in when previously initialized via a call to init(Key) or 
   * init(Key, AlgorithmParameterSpec). That is, the object is reset 
   * and available to generate another MAC from the same key, if desired, 
   * via new calls to update and doFinal. (In order to reuse this Mac 
   * object with a different key, it must be reinitialized via a call 
   * to init(Key) or init(Key, AlgorithmParameterSpec). 

   * <p>The MAC result is stored in output, starting at outOffset inclusive.
   *
   * @param output the buffer where the MAC result is stored
   * @param outOffset the offset in output where the MAC is stored
   *
   * @exception ShortBufferException if the given output buffer is too
   * small to hold the result
   * @exception java.lang.IllegalStateException if this Mac has not
   * been initialized.
   */
  public final void doFinal(byte[] output, int outOffset) throws 
    ShortBufferException, IllegalStateException
  {
    if (output.length - outOffset < getMacLength())
      throw new ShortBufferException("Buffer too short");

    byte mac[] = doFinal();
    System.arraycopy(mac, 0, output, outOffset, mac.length);
  }

  /**
   * <p>Processes the given array of bytes and finishes the MAC operation. 
   *
   * <p>A call to this method resets this Mac object to the state it was 
   * in when previously initialized via a call to init(Key) or 
   * init(Key, AlgorithmParameterSpec). That is, the object is reset and 
   * available to generate another MAC from the same key, if desired, via 
   * new calls to update and doFinal. (In order to reuse this Mac object 
   * with a different key, it must be reinitialized via a call to init(Key) 
   * or init(Key, AlgorithmParameterSpec).
   *
   * @return the MAC result.
   *
   * @exception java.lang.IllegalStateException if this Mac has not
   * been initialized.
   */
  public final byte[] doFinal(byte[] input) throws IllegalStateException
  {
    if (state != INITIALIZED) 
      throw new IllegalStateException("Not yet initialized");

    update(input);

    return delegate.engineDoFinal();
  }

  /**
   * <p>Resets this Mac object. 
   *
   * <p>A call to this method resets this Mac object to the state it was 
   * in when previously initialized via a call to init(Key) or 
   * init(Key, AlgorithmParameterSpec). That is, the object is reset and 
   * available to generate another MAC from the same key, if desired, via 
   * new calls to update and doFinal. (In order to reuse this Mac object 
   * with a different key, it must be reinitialized via a call to 
   * init(Key) or init(Key, AlgorithmParameterSpec).
   */
  public final void reset()
  {
    delegate.engineReset();
  }

  /**
   * Returns a clone if the implementation is cloneable.
   *
   * @return a clone if the implementation is cloneable.
   *
   * @exception java.lang.CloneNotSupportedException if this is called
   * on an implementation that does not support Cloneable.
   */
  public Object clone() throws CloneNotSupportedException 
  {
    if (this instanceof Cloneable) 
    {
      return delegate.clone();
    } 
    else 
    {
      throw new CloneNotSupportedException();
    }
  }
}
  
