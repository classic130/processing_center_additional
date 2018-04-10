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

import java.security.spec.AlgorithmParameterSpec;
import java.security.AlgorithmParameters;
import java.security.SecureRandom;
import java.security.Key;
import java.security.InvalidAlgorithmParameterException;
import java.security.NoSuchAlgorithmException;
import java.security.InvalidKeyException;

/**
 * <p>This class defines the Service Provider Interface (SPI) for the Cipher
 * class. All the abstract methods in this class must be implemented by
 * each cryptographic service provider who wishes to supply the
 * implementation of a particular cipher algorithm.
 *
 * <p>In order to create an instance of Cipher, which encapsulates an
 * instance of this CipherSpi class, an application calls the getInstance
 * method of Cipher and specifies the requested transformation.
 * Optionally, the application may also specify the name of a provider.
 *
 * <p>A transformation is a string that describes the operation (or set of
 * operations) to be performed on the given input, to produce some
 * output. A transformation always includes the name of a cryptographic
 * algorithm (e.g., DES), and may be followed by a feedback mode and
 * padding scheme. A transformation is of the form: algorithm or
 * algorithm/mode/padding (in the former case, defaults are used for mode
 * and padding). For example, DES/CBC/PKCS5Padding represents a valid
 * transformation.
 *
 * <p>A provider may supply a separate class for each combination of
 * algorithm/mode/padding, or may decide to provide more generic classes
 * representing sub-transformations corresponding to algorithm or
 * algorithm/mode, whose mode and/or padding schemes can be set using
 * engineSetMode and engineSetPadding, respectively.
 *
 * <p>For example, a provider may supply a subclass of CipherSpi that
 * implements DES/ECB/PKCS5Padding, one that implements
 * DES/CBC/PKCS5Padding, one that implements DES/CFB/PKCS5Padding, and
 * yet another one that implements DES/OFB/PKCS5Padding.
 *
 * <p>A different provider may implement a class for each of the above modes
 * (i.e., one class for ECB, one for CBC, one for CFB, and one for OFB),
 * one class for PKCS5Padding, and a generic DES class that subclasses
 * from CipherSpi.
 *
 * <p>The algorithm for instantiating a Cipher object (using one of the
 * getInstance methods) when a transformation of the form algorithm is
 * given is as follows:
 * <ul>
 * <li> Check if the provider has registered a subclass of Cipher for the
 *      specified algorithm. If the answer is YES, instantiate this class,
 *      for whose mode and padding scheme default values (as supplied by
 *      the provider) are used. If the answer is NO, throw a
 *      NoSuchAlgorithmException exception.
 * </ul>
 *
 * <p>The algorithm for instantiating a CipherSpi object when a transformation
 * of the form algorithm/mode/padding is given is as follows:
 * <ul>
 * <li> Check if the provider has registered a subclass of CipherSpi for the
 *      specified algorithm/mode/padding transformation. If the answer is
 *      YES, instantiate this class and return it to the user. If the
 *      answer is NO, go to the next step.
 * <li> Check if the provider has registered a subclass of CipherSpi for the
 *      sub-transformation algorithm/mode. If the answer is YES,
 *      instantiate this class, and call engineSetPadding(padding) on the
 *      new instance, before returning it to the user. If the answer is
 *      NO, go to the next step.
 * <li> Check if the provider has registered a subclass of CipherSpi for the
 *      sub-transformation algorithm. If the answer is YES, instantiate
 *      this class, and call engineSetMode(mode) and
 *      engineSetPadding(padding) on the new instance, before returning it
 *      to the user. If the answer is NO, throw a NoSuchAlgorithmException
 *      exception.
 * </ul>
 *
 * @see javax.crypto.KeyGenerator
 * @see javax.crypto.SecretKey
 * @see java.security.KeyPairGenerator
 * @see java.security.PublicKey
 * @see java.security.PrivateKey
 * @see java.security.AlgorithmParameters
 * @see java.security.spec.AlgorithmParameterSpec
 *
 * @version 0.98, 98/07/01
 * @author Ming Yung
 *
 */

public abstract class CipherSpi 
{
  protected int state;

  public CipherSpi() {}

  /**
   * Sets the mode of this cipher.
   * 
   * @param mode the cipher mode
   *
   * @exception java.security.NoSuchAlgorithmException if the requested
   * cipher mode does not exist
   */
  protected abstract void engineSetMode(String mode) 
    throws NoSuchAlgorithmException;

  /**
   * Sets the padding mechanism of this cipher.
   * 
   * @param padding the padding mechanism
   *
   * @exception NoSuchPaddingException if the requested padding
   * mechanism does not exist
   */
  protected abstract void engineSetPadding(String padding) 
    throws NoSuchPaddingException;

  /**
   * <p>Returns the block size (in bytes).
   *
   * @return the block size (in bytes),
   * or 0 if the underlying algorithm is not a block cipher
   */
  protected abstract int engineGetBlockSize(); 

  /**
   * <p>Returns the length in bytes that an output buffer would
   * need to be in order to hold the result of the next update or
   * doFinal operation, given the input length inputLen (in bytes).
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
   */
  protected abstract int engineGetOutputSize(int inputLen); 

  /**
   * <p>Returns the initialization vector (IV) in a new buffer.
   *
   * <p>This is useful in the context of password-based encryption or
   * decryption, where the IV is derived from a user-provided
   * passphrase.
   * 
   * @return the initialization vector in a new buffer, or null if the
   * underlying algorithm does not use an IV, or if the IV has
   * not yet been set.
   */
  protected abstract byte[] engineGetIV();

  /**
   * <p>Initializes this cipher with a key and a source of
   * randomness. 
   *
   * <p>The cipher is initialized for encryption or
   * decryption, depending on the value of opmode.
   *
   * <p>If this cipher requires an initialization vector (IV), it will
   * get it from random. The random IV can be retrieved using getIV.
   * This behaviour should only be used in encryption mode, however.
   * When initializing a cipher that requires an IV for decryption,
   * the IV (same IV that was used for encryption) must be provided
   * explicitly as a parameter, in order to get the correct result.
   *
   * Note that when a Cipher object is initialized, it loses all
   * previously-acquired state. In other words, initializing a
   * Cipher is equivalent to creating a new instance of that Cipher,
   * and initializing it.
   * 
   * @param opmode the operation mode of this cipher (this is
   * either ENCRYPT_MODE or DECRYPT_MODE)
   * @param key the encryption key
   * @param random the source of randomness
   *
   * @exception java.security.InvalidKeyException if the given key is
   * inappropriate for initializing this cipher
   */
  protected abstract void engineInit(int opmode, Key key, 
                                     SecureRandom random) 
    throws InvalidKeyException;

  /**
   * <p>Initializes this cipher with a key, a set of algorithm
   * parameters and a source of randomness. 
   *
   * <p>The cipher is initialized for encryption or
   * decryption, depending on the value of opmode.
   *
   * If this cipher (including its underlying feedback or padding
   * scheme) requires any random bytes, it will get them from random.
   *
   * Note that when a Cipher object is initialized, it loses all
   * previously-acquired state. In other words, initializing a
   * Cipher is equivalent to creating a new instance of that Cipher,
   * and initializing it.
   * 
   * @param opmode the operation mode of this cipher (this is
   * either ENCRYPT_MODE or DECRYPT_MODE)
   * @param key the encryption key
   * @param params the algorithm parameters
   * @param random the source of randomness
   *
   * @exception java.security.InvalidKeyException if the given key is
   * inappropriate for initializing this cipher
   * @exception java.security.InvalidAlgorithmParameterException if the
   * given algorithm parameters are inappropriate for this cipher
   */
  protected abstract void engineInit(int opmode, Key key,
                                     AlgorithmParameterSpec params,
                                     SecureRandom random) 
    throws InvalidKeyException, InvalidAlgorithmParameterException;

  /**
   * <p>Initializes this cipher with a key, a set of algorithm
   * parameters and a source of randomness. 
   *
   * <p>The cipher is initialized for encryption or
   * decryption, depending on the value of opmode.
   *
   * <p>f this cipher requires any algorithm parameters and params is null, 
   * the underlying cipher implementation is supposed to generate the 
   * required parameters itself (using provider-specific default or 
   * random values) if it is being initialized for encryption, and raise 
   * an InvalidAlgorithmParameterException if it is being initialized for
   * decryption. The generated parameters can be retrieved using 
   * engineGetParameters or engineGetIV (if the parameter is an IV). 
   *
   * <p>Note that when a Cipher object is initialized, it loses all
   * previously-acquired state. In other words, initializing a
   * Cipher is equivalent to creating a new instance of that Cipher,
   * and initializing it.
   * 
   * @param opmode the operation mode of this cipher (this is
   * either ENCRYPT_MODE or DECRYPT_MODE)
   * @param key the encryption key
   * @param params the algorithm parameters
   * @param random the source of randomness
   *
   * @exception java.security.InvalidKeyException if the given key is
   * inappropriate for initializing this cipher
   * @exception java.security.InvalidAlgorithmParameterException if the
   * given algorithm parameters are inappropriate for this cipher,
   * or if this cipher is being initialized for decryption and requires 
   * algorithm parameters and params is null
   */
  protected abstract void engineInit(int opmode, Key key,
                                     AlgorithmParameters params,
                                     SecureRandom random) 
    throws InvalidKeyException, InvalidAlgorithmParameterException;

  /**
   * <p>Continues a multiple-part encryption or decryption 
   * operation (depending on how this cipher was initialized), 
   * processing another data part.
   *
   * <p>The first inputLen bytes in the input buffer, starting at
   * inputOffset, are processed, and the result is stored in a
   * new buffer.
   *  
   * @param input the input buffer
   * @param inputOffset the offset in input where the input starts
   * @param inputLen the input length
   * 
   * @return the new buffer with the result, or null if the underlying
   * cipher is a block cipher and the input data is too short
   * to result in a new block
   *
   */
  protected abstract byte[] engineUpdate(byte input[], int inputOffset,
                                          int inputLen); 

  /**
   * <p>Continues a multiple-part encryption or decryption 
   * operation (depending on how this cipher was initialized), 
   * processing another data part.
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
   * @exception ShortBufferException if the given output buffer is too
   * small to hold the result
   */
   protected abstract int engineUpdate(byte input[], int inputOffset,
                                       int inputLen, byte output[],
                                       int outputOffset) 
        throws ShortBufferException;

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
   * @exception IllegalBlockSizeException if this cipher is a block
   * cipher, no padding has been requested (only in encryption
   * mode), and the total input length of the data processed
   * by this cipher is not a multiple of block size
   * @exception BadPaddingException if this cipher is in decryption
   * mode, and (un)padding has been requested, but the
   * decrypted data is not bounded by the appropriate padding bytes
   */
  protected abstract byte[] engineDoFinal(byte input[], int inputOffset,
                                          int inputLen) 
    throws IllegalBlockSizeException, BadPaddingException;

  /**
   * <p>Encrypts or decrypts data in a single-part operation, or
   * finishes a multiple-part operation. The data is encrypted or
   * decrypted, depending on how this cipher was initialized.
   *
   * <p>The first inputLen bytes in the input buffer, starting at
   * inputOffset, and any input bytes that may have been buffered
   * during a previous update operation, are processed, with padding
   * (if requested) being applied. The result is stored in the
   * output buffer, starting at outputOffset.
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
   * 
   * @return the number of bytes stored in output
   *
   * @exception IllegalBlockSizeException if this cipher is a block
   * cipher, no padding has been requested (only in encryption
   * mode), and the total input length of the data processed
   * by this cipher is not a multiple of block size
   * @exception ShortBufferException if the given output buffer is too
   * small to hold the result
   * @exception BadPaddingException if this cipher is in decryption
   * mode, and (un)padding has been requested, but the
   * decrypted data is not bounded by the appropriate padding bytes
   * 
   */
  protected abstract int engineDoFinal(byte input[], int inputOffset,
                                       int inputLen, byte output[],
                                       int outputOffset) 
    throws ShortBufferException,IllegalBlockSizeException, 
           BadPaddingException;

  /**
   * Returns the parameters used with this cipher.
   *
   * <p> The returned parameters may be the same that were used to
   *     initialize this cipher, or may contain the default set of
   *     parameters or a set of randomly generated parameters used by
   *     the underlying cipher implementation (provided that the
   *     underlying cipher implementation uses a default set of
   *     parameters or creates new parameters if it needs parameters but
   *     was not initialized with any).
   *
   * @return the parameters used with this cipher, or null if this
   *             cipher does not use any parameters.
   */
  protected abstract AlgorithmParameters engineGetParameters();
}
