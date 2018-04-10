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

import java.security.*;
import java.security.Provider;
import java.security.spec.AlgorithmParameterSpec;
import java.util.*;
import java.lang.*;
import java.io.*;

/**
 *  <p>This class provides the functionality of a cryptographic cipher for
 *  encryption and decryption. It forms the core of the Java Cryptographic
 *  Extension (JCE) framework.
 *
 *  <p>In order to create a Cipher object, the application calls the Cipher's
 *  getInstance method, and passes the name of the requested
 *  transformation to it. Optionally, the name of a provider may be
 *  specified.
 *
 *  <p>A transformation is a string that describes the operation (or set of
 *  operations) to be performed on the given input, to produce some
 *  output. A transformation always includes the name of a cryptographic
 *  algorithm (e.g., DES), and may be followed by a feedback mode and
 *  padding scheme. A transformation is of the form: algorithm or
 *  algorithm/mode/padding (in the former case, defaults are used for mode
 *  and padding). For example, DES/CBC/PKCS5Padding represents a valid
 *  transformation.
 *
 *  @see javax.crypto.KeyGenerator
 *  @see javax.crypto.SecretKey
 *  @see java.security.KeyPairGenerator
 *  @see java.security.PublicKey
 *  @see java.security.PrivateKey
 *  @see java.security.AlgorithmParameters
 *  @see java.security.spec.AlgorithmParameterSpec
 *
 * @version 0.98, 98/07/01
 * @author Ming Yung
 *
 */
public class Cipher
{
  public static final int ENCRYPT_MODE = 0x01;
  public static final int DECRYPT_MODE = 0x02;
  private static final int UNINITIALIZED = 0x00;

  private int state;
  private String transformation;
  private static final byte[] EMPTY = new byte[0];
 
  private Provider provider;

  /* The delegate */
  private CipherSpi cipherSpi;

  /**
   * Creates a Cipher object.
   *
   * @param cipherSpi the delegate
   * @param provider the provider
   * @param transformation the transformation
   */
  protected Cipher(CipherSpi cipherSpi, Provider provider, 
                   String transformation) 
  {
    this.cipherSpi = cipherSpi;
    this.provider = provider;
    this.transformation = transformation;
    this.state = UNINITIALIZED;
  }

  /**
   * Creates a Cipher object that implements the specified
   *          algorithm, as supplied by the default provider.
   *
   * @param transformation the string representation of the requested
   * transformation, e.g., DES/CBC/PKCS5Padding
   *
   * @return a cipher that implements the requested transformation
   *
   * @exception NoSuchAlgorithmException if the transformation is
   * not available in the caller's environment.  
   * 
   * @exception NoSuchPaddingException if the requested padding 
   * is not available
   */
  public static final Cipher getInstance(String transformation)
    throws NoSuchAlgorithmException, NoSuchPaddingException 
  {
    Provider[] provs = Security.getProviders();

    Cipher retval = null;
    for (int i=0; i<provs.length; i++)
    {
      try
      {
        retval = Cipher.getInstance(transformation, provs[i].getName());
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

    throw new NoSuchAlgorithmException("Cipher transformation " +
      transformation + " not found");
  }

  /**
   * Creates a Cipher object that implements the specified
   *         transformation, as supplied by the specified provider.
   *
   * @param transformation the string representation of the requested
   * transformation, e.g., DES/CBC/PKCS5Padding
   * @param provider the name of the cipher provider
   *
   * @return a cipher that implements the requested transformation
   *
   * @exception NoSuchAlgorithmException if the transformation is
   * not available in the package supplied by the requested
   * provider.
   *
   * @exception NoSuchProviderException if the provider is not
   * available in the environment. 
   * 
   * @exception NoSuchPaddingException if the requested padding 
   * is not available
   * 
   * @see java.security.Provider 
   */
  public static final Cipher getInstance(String transformation, String provider)
    throws NoSuchAlgorithmException, NoSuchProviderException,
           NoSuchPaddingException 
  {
    if (provider == null)
      throw new InvalidParameterException("Null provider supplied");

    CipherSpi cipherSpi = null;
    Class cl = null;
    String className = null;

    try
    {
      Provider prov = Security.getProvider(provider);

      if (prov == null)
        throw new NoSuchProviderException("Provider " + provider + " not found");
      
      StringTokenizer tknz = new StringTokenizer(transformation, "/", false);
      int count = tknz.countTokens();
      if (count != 1 && count != 3)
        throw new NoSuchAlgorithmException("Cipher " + transformation + 
          " not found in provider " + provider);

      StringBuffer name = new StringBuffer("Cipher.");

      StringBuffer alt = new StringBuffer("Alg.Alias.Cipher.");
      alt.append(transformation);
//    String alg = prov.getProperty(alt.toString());
      String alg = getProviderProperty(alt.toString(), prov);

      if (alg != null)
        name.append(alg);
      else
        name.append(transformation);

//    className = prov.getProperty(name.toString());
      className = getProviderProperty(name.toString(), prov);
      if (className != null)
      {
        cipherSpi = (CipherSpi)Class.forName(className, true, 
           Thread.currentThread().getContextClassLoader()).newInstance();
        return new Cipher(cipherSpi, prov, transformation);
      }

      if (count != 3)
        throw new NoSuchAlgorithmException("Cipher " + transformation + 
          " not found in provider " + provider);

      String algName = tknz.nextToken();
      String mode = tknz.nextToken();
      String padding = tknz.nextToken();

      name = new StringBuffer("Cipher.");
      alt = new StringBuffer("Alg.Alias.Cipher.");
      alt.append(algName).append("/").append(mode);
//    alg = prov.getProperty(alt.toString());
      alg = getProviderProperty(alt.toString(), prov);

      if (alg != null)
        name.append(alg);
      else
        name.append(algName).append("/").append(mode);
      
//    className = prov.getProperty(name.toString());
      className = getProviderProperty(name.toString(), prov);

      if (className != null)
      {
        cl = Class.forName(className, true, 
           Thread.currentThread().getContextClassLoader());
        cipherSpi = (CipherSpi)cl.newInstance();
        cipherSpi.engineSetPadding(padding);
        return new Cipher(cipherSpi, prov, transformation);
      }

      name = new StringBuffer("Cipher.");
      alt = new StringBuffer("Alg.Alias.Cipher.");
      alt.append(algName).append("//").append(padding);
//    alg = prov.getProperty(alt.toString());
      alg = getProviderProperty(alt.toString(), prov);

      if (alg != null)
        name.append(alg);
      else
        name.append(algName).append("//").append(padding);

//    className = prov.getProperty(name.toString());
      className = getProviderProperty(name.toString(), prov);

      if (className != null)
      {
        cl = Class.forName(className, true,
           Thread.currentThread().getContextClassLoader());
        cipherSpi = (CipherSpi)cl.newInstance();
        cipherSpi.engineSetMode(mode);
        return new Cipher(cipherSpi, prov, transformation);
      }

      name = new StringBuffer("Cipher.");
      alt = new StringBuffer("Alg.Alias.Cipher.");
      alt.append(algName);
//    alg = prov.getProperty(alt.toString());
      alg = getProviderProperty(alt.toString(), prov);

      if (alg != null)
        name.append(alg);
      else
        name.append(algName);

//    className = prov.getProperty(name.toString());
      className = getProviderProperty(name.toString(), prov);

      if (className != null)
      {
        cl = Class.forName(className, true, 
           Thread.currentThread().getContextClassLoader());
        cipherSpi = (CipherSpi)cl.newInstance();
        cipherSpi.engineSetPadding(padding);
        cipherSpi.engineSetMode(mode);
        return new Cipher(cipherSpi, prov, transformation);
      }
      else
        throw new NoSuchAlgorithmException("Cipher " + transformation + 
          " not found in provider " + provider);
    }
    catch (ClassNotFoundException e)
    {
      throw new NoSuchAlgorithmException("Class " + className + 
        " not found during Cipher instantiation");
    }
    catch (IllegalAccessException e)
    {
      throw new NoSuchAlgorithmException("Transformation " + transformation +
                                         " not found in provider " +
                                         provider);
    }
    catch (InstantiationException e)
    {
      throw new NoSuchAlgorithmException("Transformation " + transformation +
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
   * <p>Returns the algorithm name of this Cipher object. 
   *
   * <p> This is the same name that was specified in one of the 
   * getInstance calls that created this Cipher object.
   *
   * @return  the algorithm name of this Cipher object.
   */
  public final String getAlgorithm()
  {
    return this.transformation;
  }

  /**
   * Returns the provider of this Cipher object.
   *
   * @return the provider of this Cipher object
   */
  public final Provider getProvider()
  {
    return this.provider;
  }

  /**
   * <p>Initializes this cipher with a key. The cipher is initialized
   * for encryption or decryption, depending on the value of opmode.
   * 
   * <p>If this cipher requires an initialization vector (IV), it will
   * get it from a system-provided source of randomness. The random
   * IV can be retrieved using getIV. This behaviour should only be
   * used in encryption mode, however. When initializing a cipher
   * that requires an IV for decryption, the IV (same IV that was
   * used for encryption) must be provided explicitly as a
   * parameter, in order to get the correct result.
   *
   * <p>Note that when a Cipher object is initialized, it loses all
   * previously-acquired state. In other words, initializing a
   * Cipher is equivalent to creating a new instance of that Cipher,
   * and initializing it.
   *
   * @param opmode the operation mode of this cipher (this is
   * either ENCRYPT_MODE or DECRYPT_MODE)
   * @param key the key
   *
   * @exception java.security.InvalidKeyException if the given key is
   * inappropriate for initializing this cipher
   */
  public void init(int opmode, Key key) 
    throws InvalidKeyException 
  {
    init(opmode, key, new SecureRandom());
  }

  /**
   * <p>Initializes this cipher with a key and a source of randomness. 
   *
   * <p>The cipher is initialized for encryption or decryption,
   * depending on the value of opmode.
   *
   * <p>If this cipher requires an initialization vector (IV), it will
   * get it from random. The random IV can be retrieved using getIV.
   * This behaviour should only be used in encryption mode, however.
   * When initializing a cipher that requires an IV for decryption,
   * the IV (same IV that was used for encryption) must be provided
   * explicitly as a parameter, in order to get the correct result.
   *  
   * <p>Note that when a Cipher object is initialized, it loses all
   * previously-acquired state. In other words, initializing a
   * Cipher is equivalent to creating a new instance of that Cipher,
   * and initializing it.
   *
   * @param opmode the operation mode of this cipher (this is
   * either ENCRYPT_MODE or DECRYPT_MODE)
   * @param key the key
   * @param random the source of randomness
   *
   * @exception java.security.InvalidKeyException if the given key is
   * inappropriate for initializing this cipher
   */
  public void init(int opmode, Key key, SecureRandom random) 
    throws InvalidKeyException 
  {
    this.state = opmode;
    cipherSpi.engineInit(opmode, key, random);
  }

  /**
   * <p>Initializes this cipher with a key and a set of algorithm
   * parameters. 
   *
   * <p>The cipher is initialized
   * for encryption or decryption, depending on the value of opmode.
   * 
   * <p>Note that when a Cipher object is initialized, it loses all
   * previously-acquired state. In other words, initializing a
   * Cipher is equivalent to creating a new instance of that Cipher,
   * and initializing it.
   *
   * @param opmode the operation mode of this cipher (this is
   * either ENCRYPT_MODE or DECRYPT_MODE)
   * @param key the key
   * @param params the algorithm parameters
   *
   * @exception java.security.InvalidKeyException if the given key is
   * inappropriate for initializing this cipher
   * @exception java.security.InvalidAlgorithmParameterException if the
   * given algorithm parameters are inappropriate for this cipher
   */
  public void init(int opmode, Key key, AlgorithmParameterSpec params) 
    throws InvalidKeyException, InvalidAlgorithmParameterException 
  {
    init(opmode, key, params, new SecureRandom());
  }

  /**
   * <p>Initializes this cipher with a key, a set of algorithm
   * parameters, and a source of randomness. 
   *
   * <p>The cipher is initialized
   * for encryption or decryption, depending on the value of opmode.
   *
   * <p>If this cipher (including its underlying feedback or padding
   * scheme) requires any random bytes, it will get them from
   * random.
   *
   * <p>Note that when a Cipher object is initialized, it loses all
   * previously-acquired state. In other words, initializing a
   * Cipher is equivalent to creating a new instance of that Cipher,
   * and initializing it.
   * 
   * @param opmode the operation mode of this cipher (this is
   * either ENCRYPT_MODE or DECRYPT_MODE)
   * @param key the key
   * @param params the algorithm parameters
   * @param random the source of randomness
   *
   * @exception java.security.InvalidKeyException if the given key is
   * inappropriate for initializing this cipher
   * @exception java.security.InvalidAlgorithmParameterException if the
   * given algorithm parameters are inappropriate for this cipher
   */
  public void init(int opmode, Key key, AlgorithmParameterSpec params,
                   SecureRandom random) 
    throws InvalidKeyException, InvalidAlgorithmParameterException 
  {
    this.state = opmode;
    cipherSpi.engineInit(opmode, key, params, random);
  }

  /**
   * <p>Initializes this cipher with a key, a set of algorithm
   * parameters, and a source of randomness. 
   *
   * <p>The cipher is initialized
   * for encryption or decryption, depending on the value of opmode.
   *
   * <p>If this cipher requires any algorithm parameters and params is null, 
   * the underlying cipher implementation is supposed to generate the 
   * required parameters itself (using provider-specific default or random 
   * values) if it is being initialized for encryption, and raise an 
   * InvalidAlgorithmParameterException if it is being initialized for 
   * decryption. The generated parameters can be retrieved using 
   * getParameters or getIV (if the parameter is an IV). 
   *
   * <p>If this cipher (including its underlying feedback or padding
   * scheme) requires any random bytes (eg. for parameter generation), it 
   * will get them from  random.
   *
   * <p>Note that when a Cipher object is initialized, it loses all
   * previously-acquired state. In other words, initializing a
   * Cipher is equivalent to creating a new instance of that Cipher,
   * and initializing it.
   * 
   * @param opmode the operation mode of this cipher (this is
   * either ENCRYPT_MODE or DECRYPT_MODE)
   * @param key the key
   * @param params the algorithm parameters
   * @param random the source of randomness
   *
   * @exception java.security.InvalidKeyException if the given key is
   * inappropriate for initializing this cipher
   * @exception java.security.InvalidAlgorithmParameterException if the
   * given algorithm parameters are inappropriate for this cipher,
   * or if this cipher is being initialized for decryption and requires 
   * algorithm parameters and params is null.
   */
  public void init(int opmode, Key key, AlgorithmParameters params,
                   SecureRandom random) 
    throws InvalidKeyException, InvalidAlgorithmParameterException 
  {
    this.state = opmode;
    cipherSpi.engineInit(opmode, key, params, random);
  }

  /**
   * <p>Initializes this cipher with a key and  a set of algorithm
   * parameters.
   *
   * <p>The cipher is initialized
   * for encryption or decryption, depending on the value of opmode.
   *
   * <p>If this cipher requires any algorithm parameters and params is null, 
   * the underlying cipher implementation is supposed to generate the 
   * required parameters itself (using provider-specific default or random 
   * values) if it is being initialized for encryption, and raise an 
   * InvalidAlgorithmParameterException if it is being initialized for 
   * decryption. The generated parameters can be retrieved using 
   * getParameters or getIV (if the parameter is an IV). 
   *
   * <p>If this cipher (including its underlying feedback or padding scheme) 
   * requires any random bytes (e.g., for parameter generation), it will 
   * get them using the SecureRandom implementation of the highest-priority 
   * installed provider as the source of randomness. (If none of the 
   * installed providers supply an implementation of SecureRandom, a
   * system-provided source of randomness will be used.) 
   *
   * <p>Note that when a Cipher object is initialized, it loses all
   * previously-acquired state. In other words, initializing a
   * Cipher is equivalent to creating a new instance of that Cipher,
   * and initializing it.
   * 
   * @param opmode the operation mode of this cipher (this is
   * either ENCRYPT_MODE or DECRYPT_MODE)
   * @param key the key
   * @param params the algorithm parameters
   *
   * @exception java.security.InvalidKeyException if the given key is
   * inappropriate for initializing this cipher
   * @exception java.security.InvalidAlgorithmParameterException if the
   * given algorithm parameters are inappropriate for this cipher,
   * or if this cipher is being initialized for decryption and requires 
   * algorithm parameters and params is null.
   */
  public void init(int opmode, Key key, AlgorithmParameters params)
    throws InvalidKeyException, InvalidAlgorithmParameterException 
  {
    init(opmode, key, params, new SecureRandom());
  }

  /**
   * Returns the block size (in bytes).
   *
   * @return the block size (in bytes)
   */
  public int getBlockSize() 
  {
    return cipherSpi.engineGetBlockSize();
  }

  /**
   * <p>Returns the length in bytes that an output buffer would need to
   * be in order to hold the result of the next update or doFinal
   * operation, given the input length inputLen (in bytes).
   *
   * <p>This call takes into account any unprocessed (buffered) data
   * from a previous update call, and padding.
   *
   * <p>The actual output length of the next update or doFinal call may
   * be smaller than the length returned by this method.
   *
   * @param inputLen - the input length (in bytes)
   *
   * @return the required output buffer size (in bytes)
   *
   * @exception java.lang.IllegalStateException if this cipher is in a
   * wrong state (e.g., has not yet been initialized)
   */
  public int getOutputSize(int inputLen) throws IllegalStateException
  {
    if (state == UNINITIALIZED)
    {
      throw new IllegalStateException("Cipher not yet initialized");
    }

    return cipherSpi.engineGetOutputSize(inputLen);
  }

  /**
   * <p>Returns the initialization vector (IV) in a new buffer.
   *
   * <p>This is useful in the case where a random IV has been created
   * (see init), or in the context of password-based encryption or
   * decryption, where the IV is derived from a user-provided
   * passphrase.
   *
   * @return the initialization vector in a new buffer, or null if the
   * underlying algorithm does not use an IV, or if the IV has
   * not yet been set.
   */
  public byte[] getIV() 
  {
    return cipherSpi.engineGetIV();
  }

  /**
   * <p>Continues a multiple-part encryption or decryption operation
   * (depending on how this cipher was initialized), processing
   * another data part.
   *
   * <p>The bytes in the input buffer are processed, and the result is
   * stored in a new buffer.
   *
   * @param input - the input buffer
   *
   * @return the new buffer with the result
   *
   * @exception java.lang.IllegalStateException if this cipher is in a
   * wrong state (e.g., has not been initialized)
   */
  public byte[] update(byte input[]) throws IllegalStateException
  {
    return update(input, 0, input.length);
  }

  /**
   * <p>Continues a multiple-part encryption or decryption operation
   * (depending on how this cipher was initialized), processing
   * another data part.
   *
   * <p>The first inputLen bytes in the input buffer, starting at
   * inputOffset, are processed, and the result is stored in a new
   * buffer.
   *
   * @param input the input buffer
   * @param inputOffset the offset in input where the input starts
   * @param inputLen the input length
   *
   * @return the new buffer with the result
   *
   * @exception java.lang.IllegalStateException if this cipher is in a
   * wrong state (e.g., has not been initialized)
   */
  public byte[] update(byte input[], int inputOffset, int inputLen) 
    throws IllegalStateException 
  {
    if (state == UNINITIALIZED)
    {
      throw new IllegalStateException("Cipher not yet initialized");
    }

    return cipherSpi.engineUpdate(input, inputOffset, inputLen);
  }

  /**
   * <p>Continues a multiple-part encryption or decryption operation
   * (depending on how this cipher was initialized), processing
   * another data part.
   *
   * <p>The first inputLen bytes in the input buffer, starting at
   * inputOffset, are processed, and the result is stored in the
   * output buffer.
   *
   * <p>If the output buffer is too small to hold the result, a
   * ShortBufferException is thrown. In this case, repeat this call
   * with a larger output buffer. Use getOutputSize to determine how
   * big the output buffer should be.
   *
   * @param input the input buffer
   * @param inputOffset the offset in input where the input starts
   * @param inputLen the input length
   * @param output the buffer for the result
   *
   * @return the number of bytes stored in output
   *
   * @exception java.lang.IllegalStateException if this cipher is in a
   * wrong state (e.g., has not been initialized)
   * @exception javax.crypto.ShortBufferException if the given output buffer 
   * is too small to hold the result
   */
  public int update(byte input[], int inputOffset,
                    int inputLen, byte output[]) 
    throws IllegalStateException, ShortBufferException 
  {
    return update(input, inputOffset, inputLen, output, 0);
  }

  /**
   * <p>Continues a multiple-part encryption or decryption operation
   * (depending on how this cipher was initialized), processing
   * another data part.
   *
   * <p>The first inputLen bytes in the input buffer, starting at
   * inputOffset, are processed, and the result is stored in the
   * output buffer, starting at outputOffset.
   *
   * <p>If the output buffer is too small to hold the result, a
   * ShortBufferException is thrown. In this case, repeat this call
   * with a larger output buffer. Use getOutputSize to determine how
   * big the output buffer should be.
   *
   * @param input the input buffer
   * @param inputOffset the offset in input where the input starts
   * @param inputLen the input length
   * @param output the buffer for the result
   * @param outputOffset the offset in output where the result is stored 
   *
   * @return the number of bytes stored in output
   *
   * @exception java.lang.IllegalStateException if this cipher is in a
   * wrong state (e.g., has not been initialized)
   * @exception javax.crypto.ShortBufferException if the given output buffer 
   * is too small to hold the result
   */
  public int update(byte input[], int inputOffset,
                    int inputLen, byte output[],
                    int outputOffset) 
    throws IllegalStateException, ShortBufferException 
  {
    if (state == UNINITIALIZED)
    {
      throw new IllegalStateException("Cipher not yet initialized");
    }

    return cipherSpi.engineUpdate(input, inputOffset, inputLen, output, 
              outputOffset);
  }

  /**
   * <p>Finishes a multiple-part encryption or decryption operation,
   * depending on how this cipher was initialized.
   *
   * <p>Input data that may have been buffered during a previous update
   * operation is processed, with padding (if requested) being
   * applied. The result is stored in a new buffer.
   *
   * <p>A call to this method resets this cipher object to the state it
   *  was in when previously initialized via a call to init. That is,
   *  the object is reset and available to encrypt or decrypt
   *  (depending on the operation mode that was specified in the call
   *  to init) more data.
   *
   * @return the new buffer with the result
   *
   * @exception java.lang.IllegalStateException if this cipher is in a
   * wrong state (e.g., has not been initialized)
   * @exception IllegalBlockSizeException if this cipher is a block
   * cipher, no padding has been requested (only in encryption
   * mode), and the total input length of the data processed
   * by this cipher is not a multiple of block size
   * @exception BadPaddingException if this cipher is in decryption
   * mode, and (un)padding has been requested, but the
   * decrypted data is not bounded by the appropriate padding bytes
   */
  public byte[] doFinal() 
    throws IllegalStateException,
           IllegalBlockSizeException, BadPaddingException 
  {
    return doFinal(EMPTY, 0, 0);
  }

  /**
   * <p>Encrypts or decrypts data in a single-part operation, or finishes a
   * multiple-part operation. The data is encrypted or decrypted,
   * depending on how this cipher was initialized.
   *
   * <p>The bytes in the input buffer, and any input bytes that may
   * have been buffered during a previous update operation, are
   * processed, with padding (if requested) being applied. The
   * result is stored in a new buffer.
   *
   * <p>A call to this method resets this cipher object to the state it
   *  was in when previously initialized via a call to init. That is,
   *  the object is reset and available to encrypt or decrypt
   *  (depending on the operation mode that was specified in the call
   *  to init) more data.
   *
   * @param input the input buffer
   *
   * @return the new buffer with the result
   *
   * @exception java.lang.IllegalStateException if this cipher is in a
   * wrong state (e.g., has not been initialized)
   * @exception IllegalBlockSizeException if this cipher is a block
   * cipher, no padding has been requested (only in encryption
   * mode), and the total input length of the data processed
   * by this cipher is not a multiple of block size
   * @exception BadPaddingException if this cipher is in decryption
   * mode, and (un)padding has been requested, but the
   * decrypted data is not bounded by the appropriate padding bytes
   *
   */
  public byte[] doFinal(byte input[]) 
    throws IllegalStateException,
           IllegalBlockSizeException, BadPaddingException 
  {
    return doFinal(input, 0, input.length);
  }

  /**
   * <p>Finishes a multiple-part encryption or decryption operation, depending
   * on how this cipher was initialized.
   *
   * <p>Input data that may have been buffered during a previous update
   * operation is processed, with padding (if requested) being
   * applied. The result is stored in a new buffer.
   *
   * <p>If the output buffer is too small to hold the result, a
   * ShortBufferException is thrown. In this case, repeat this call
   * with a larger output buffer. Use getOutputSize to determine how
   * big the output buffer should be.
   *
   * <p>A call to this method resets this cipher object to the state it
   *  was in when previously initialized via a call to init. That is,
   *  the object is reset and available to encrypt or decrypt
   *  (depending on the operation mode that was specified in the call
   *  to init) more data.
   *
   * @param input the input buffer
   * @param outputOffset the offset in output where the result is stored
   *
   * @return the new buffer with the result
   *
   * @exception java.lang.IllegalStateException if this cipher is in a
   * wrong state (e.g., has not been initialized)
   * @exception IllegalBlockSizeException if this cipher is a block
   * cipher, no padding has been requested (only in encryption
   * mode), and the total input length of the data processed
   * by this cipher is not a multiple of block size
   * @exception ShortBufferException if the given output buffer is too
   * small to hold the result
   * @exception BadPaddingException if this cipher is in decryption
   * mode, and (un)padding has been requested, but the
   * decrypted data is not bounded by the appropriate padding bytes
   */
  public int doFinal(byte output[], int outputOffset) 
     throws IllegalStateException,
            IllegalBlockSizeException, ShortBufferException,
            BadPaddingException 
  {
    return doFinal(EMPTY, 0, 0, output, outputOffset);
  }


  /**
   * <p>Encrypts or decrypts data in a single-part operation, or
   * finishes a multiple-part operation. The data is encrypted or
   * decrypted, depending on how this cipher was initialized.
   *
   * <p>The first inputLen bytes in the input buffer, starting at
   * inputOffset, and any input bytes that may have been buffered
   * during a previous update operation, are processed, with padding
   * (if requested) being applied. The result is stored in a new
   * buffer.
   *
   * <p>A call to this method resets this cipher object to the state it
   *  was in when previously initialized via a call to init. That is,
   *  the object is reset and available to encrypt or decrypt
   *  (depending on the operation mode that was specified in the call
   *  to init) more data.
   *
   * @param input the input buffer
   * @param inputOffset the offset in input where the input starts
   * @param inputLen the input length
   *
   * @return the new buffer with the result
   *
   * @exception java.lang.IllegalStateException if this cipher is in a
   * wrong state (e.g., has not been initialized)
   * @exception IllegalBlockSizeException if this cipher is a block
   * cipher, no padding has been requested (only in encryption
   * mode), and the total input length of the data processed
   * by this cipher is not a multiple of block size
   * @exception BadPaddingException if this cipher is in decryption
   * mode, and (un)padding has been requested, but the
   * decrypted data is not bounded by the appropriate padding bytes
   */
  public byte[] doFinal(byte input[], int inputOffset,
                        int inputLen) 
    throws IllegalStateException,
           IllegalBlockSizeException, BadPaddingException 
  {
    if (state == UNINITIALIZED)
    {
      throw new IllegalStateException("Cipher not yet initialized");
    }

    return cipherSpi.engineDoFinal(input, inputOffset, inputLen);
  }


  /**
   * <p>Encrypts or decrypts data in a single-part operation, or
   * finishes a multiple-part operation. The data is encrypted or
   * decrypted, depending on how this cipher was initialized.
   *
   * <p>The first inputLen bytes in the input buffer, starting at
   * inputOffset, and any input bytes that may have been buffered
   * during a previous update operation, are processed, with padding
   * (if requested) being applied. The result is stored in the output
   * buffer.
   *
   * <p>If the output buffer is too small to hold the result, a
   * ShortBufferException is thrown. In this case, repeat this call
   * with a larger output buffer. Use getOutputSize to determine how
   * big the output buffer should be.
   *
   * <p>A call to this method resets this cipher object to the state it
   *  was in when previously initialized via a call to init. That is,
   *  the object is reset and available to encrypt or decrypt
   *  (depending on the operation mode that was specified in the call
   *  to init) more data.
   *
   * @param input the input buffer
   * @param inputOffset the offset in input where the input starts
   * @param inputLen the input length
   * @param output the buffer for the result
   *
   * @return the number of bytes stored in output
   *
   * @exception java.lang.IllegalStateException if this cipher is in a
   * wrong state (e.g., has not been initialized)
   * @exception IllegalBlockSizeException if this cipher is a block
   * cipher, no padding has been requested (only in encryption
   * mode), and the total input length of the data processed
   * by this cipher is not a multiple of block size
   * @exception ShortBufferException if the given output buffer is too
   * small to hold the result
   * @exception BadPaddingException if this cipher is in decryption
   * mode, and (un)padding has been requested, but the
   * decrypted data is not bounded by the appropriate padding bytes
   */
  public int doFinal(byte input[], int inputOffset,
                     int inputLen, byte output[]) 
    throws IllegalStateException,
           ShortBufferException, IllegalBlockSizeException,
           BadPaddingException 
  {
    return doFinal(input, inputOffset, inputLen, output, 0);
  }

  /**
   * <p>Encrypts or decrypts data in a single-part operation, or
   * finishes a multiple-part operation. The data is encrypted or
   * decrypted, depending on how this cipher was initialized.
   *
   * <p>The first inputLen bytes in the input buffer, starting at
   * inputOffset, and any input bytes that may have been buffered
   * during a previous update operation, are processed, with padding
   * (if requested) being applied. The result is stored in the output
   * buffer, starting at outputOffset.
   *
   * <p>If the output buffer is too small to hold the result, a
   * ShortBufferException is thrown. In this case, repeat this call
   * with a larger output buffer. Use getOutputSize to determine how
   * big the output buffer should be.
   *
   * <p>A call to this method resets this cipher object to the state it
   *  was in when previously initialized via a call to init. That is,
   *  the object is reset and available to encrypt or decrypt
   *  (depending on the operation mode that was specified in the call
   *  to init) more data.
   *
   * @param input the input buffer
   * @param inputOffset the offset in input where the input starts
   * @param inputLen the input length
   * @param output the buffer for the result
   * @param outputOffset the offset in output where the result is
   * stored
   *
   * @return the number of bytes stored in output
   *
   * @exception java.lang.IllegalStateException if this cipher is in a
   * wrong state (e.g., has not been initialized)
   * @exception IllegalBlockSizeException if this cipher is a block
   * cipher, no padding has been requested (only in encryption
   * mode), and the total input length of the data processed
   * by this cipher is not a multiple of block size
   * @exception ShortBufferException if the given output buffer is too
   * small to hold the result
   * @exception BadPaddingException if this cipher is in decryption
   * mode, and (un)padding has been requested, but the
   * decrypted data is not bounded by the appropriate padding bytes
   */
  public int doFinal(byte input[], int inputOffset,
                     int inputLen, byte output[],
                     int outputOffset) 
    throws IllegalStateException,
           ShortBufferException, IllegalBlockSizeException,
           BadPaddingException 
  {
    if (state == UNINITIALIZED)
    {
      throw new IllegalStateException("Cipher not yet initialized");
    }

    return cipherSpi.engineDoFinal(input, inputOffset, inputLen, output,
                outputOffset);
  }

  /**
   *  Returns the parameters used with this cipher.
   *
   * <p>The returned parameters may be the same that were used to
   *    initialize this cipher, or may contain the default set of
   *    parameters or a set of randomly generated parameters used by
   *    the underlying cipher implementation (provided that the
   *    underlying cipher implementation uses a default set of
   *    parameters or creates new parameters if it needs parameters but
   *    was not initialized with any).
   *
   * @return  the parameters used with this cipher, or null if this
   *           cipher does not use any parameters.
   */
  public final AlgorithmParameters getParameters()
  {
    return cipherSpi.engineGetParameters();
  }
}
