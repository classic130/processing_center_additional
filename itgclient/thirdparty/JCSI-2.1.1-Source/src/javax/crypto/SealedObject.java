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

import java.io.Serializable;
import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.IOException;
import java.security.*;

/**
 * <p>This class enables a programmer to create an object and protect its 
 * confidentiality with a cryptographic algorithm. 
 *
 * <p>Given any Serializable object, one can create a SealedObject that 
 * encapsulates the original object, in serialized format (i.e., a 
 * "deep copy"), and seals (encrypts) its serialized contents, using a 
 * cryptographic algorithm such as DES, to protect its confidentiality. 
 * The encrypted content can later be decrypted (with the corresponding 
 * algorithm using the correct decryption key) and de-serialized, yielding 
 * the original object.
 *
 * <p>Note that the Cipher object must be fully initialized with the correct 
 * algorithm, key, padding scheme, etc., before being applied to a 
 * SealedObject.
 *
 * <p>The original object that was sealed can be recovered in two different ways:
 *
 *      by using the getObject method that takes a Cipher object.
 *       This method requires a fully initialized Cipher object, initialized with the exact
 *       same algorithm, key, padding scheme, etc., that were used to seal the object.
 *       This approach has the advantage that the party who unseals the sealed object does not
 *       require knowledge of the decryption key. For example, after one party has initialized
 *       the cipher object with the required decryption key, it could hand over the cipher
 *       object to another party who then unseals the sealed object.
 *      by using one of the getObject methods that take a Key object.
 *       In this approach, the getObject method creates a cipher object for the appropriate
 *       decryption algorithm and initializes it with the given decryption key and the
 *       algorithm parameters (if any) that were stored in the sealed object.
 *       This approach has the advantage that the party who unseals the object does not need to
 *       keep track of the parameters (e.g., an IV) that were used to seal the object.
 *
 * @see javax.crypto.Cipher
 *
 * @version 0.98, 98/07/01
 * @author Ming Yung
 *
 */
public class SealedObject implements Serializable
{
  private byte sealedContents[];
  private String alg;
  private AlgorithmParameters params = null;

  /**
   * Constructs a SealedObject from any Serializable object. 
   *
   * <p>The given object is serialized, and its serialized contents 
   * are encrypted using the given Cipher, which must be fully initialized.
   *
   * <p> Any algorithm parameters that may be used in the encryption 
   * operation are stored inside of the new SealedObject.
   *
   * @param object the object to be sealed. 
   * @param c the cipher used to seal the object
   *
   * @exception java.io.IOException if an error occurs during serialization
   * @exception javax.crypto.IllegalBlockSizeException if the given cipher 
   * is a block cipher, no padding has been requested, and the total input 
   * length is not a multiple of the cipher's block size
   */
  public SealedObject(Serializable object, Cipher c) 
    throws IOException, IllegalBlockSizeException, BadPaddingException
  {
    this.alg = c.getAlgorithm();
    this.params = c.getParameters();

    ByteArrayOutputStream ostream = new ByteArrayOutputStream();
    ObjectOutputStream os = new ObjectOutputStream(ostream);
    os.writeObject(object);
    os.flush();
    sealedContents = c.doFinal(ostream.toByteArray());
  }

  /**
   * Returns the algorithm that was used to seal this object.
   *
   * @return the algorithm that was used to seal this object.
   */
  public final java.lang.String getAlgorithm()
  {
    return alg;
  }

  /**
   * Retrieves the original (encapsulated) object. 
   *
   * <p>The encapsulated object is unsealed (using the given Cipher, 
   * assuming that the Cipher is already properly initialized) and 
   * de-serialized, before it is returned. 
   *
   * @param c the cipher used to unseal the object 
   *
   * @return the original object.
   *
   * @exception java.io.IOException if an error occurs during de-serialization
   * @exception java.lang.ClassNotFoundException if an error occurs during 
   * de-serialization
   * @exception javax.crypto.IllegalBlockSizeException if the given cipher is 
   * a block cipher, no padding has been requested, and the total input 
   * length is not a multiple of the cipher's block size 
   * @exception javax.crypto.BadPaddingException if the given cipher has 
   * been initialized for decryption, and padding has been specified, but 
   * the input data does not have proper expected padding bytes
   */
  public final Object getObject(Cipher c) 
   throws IOException, ClassNotFoundException, 
          IllegalBlockSizeException, BadPaddingException
  {
    ByteArrayInputStream istream 
      = new ByteArrayInputStream(c.doFinal(sealedContents));
    ObjectInputStream is = new ObjectInputStream(istream);
    return is.readObject();
  }

  public final Object getObject(Key key)
    throws IOException, ClassNotFoundException, 
           NoSuchAlgorithmException,
           InvalidKeyException
  {
    Cipher c = null;

    try
    {
      c = Cipher.getInstance(alg);
      c.init(Cipher.DECRYPT_MODE, key, params);
    }
    catch (NoSuchPaddingException e)
    {
      throw new NoSuchAlgorithmException("Padding algorithm unavailable");
    }
    catch (InvalidAlgorithmParameterException e)
    {
      throw new RuntimeException("Algorithm and parameter mismatch");
    }

    return getObj(c);
  }

  public final Object getObject(Key key, String provider)
    throws IOException, ClassNotFoundException, 
           NoSuchAlgorithmException, NoSuchProviderException,
           InvalidKeyException
  {
    Cipher c = null;

    try
    {
      c = Cipher.getInstance(alg, provider);
      c.init(Cipher.DECRYPT_MODE, key, params);
    }
    catch (NoSuchPaddingException e)
    {
      throw new NoSuchAlgorithmException("Padding algorithm unavailable");
    }
    catch (InvalidAlgorithmParameterException e)
    {
      throw new RuntimeException("Algorithm and parameter mismatch");
    }

    return getObj(c);
  }

  private Object getObj(Cipher c)
   throws IOException, ClassNotFoundException, 
          InvalidKeyException
  {
    try
    { 
      return getObject(c);
    }
    catch (BadPaddingException e)
    {
      throw new InvalidKeyException("Decryption failed");
    }
    catch (IllegalBlockSizeException e)
    {
      throw new InvalidKeyException("Decryption failed");
    }
  }
}
