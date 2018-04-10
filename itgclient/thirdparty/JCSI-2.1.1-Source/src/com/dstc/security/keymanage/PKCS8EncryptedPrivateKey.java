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

package com.dstc.security.keymanage;

import java.io.IOException;
import java.io.InputStream;
import java.util.Iterator;
import java.util.NoSuchElementException;
import java.security.MessageDigest;
import java.security.KeyFactory;
import java.security.PrivateKey;
import java.security.AlgorithmParameters;
import java.security.NoSuchAlgorithmException;
import java.security.spec.PKCS8EncodedKeySpec;
import java.security.spec.InvalidKeySpecException;

import javax.crypto.Cipher;
import javax.crypto.SecretKey;
import javax.crypto.SecretKeyFactory;
import javax.crypto.BadPaddingException;
import javax.crypto.NoSuchPaddingException;
import javax.crypto.spec.PBEKeySpec;
import javax.crypto.spec.PBEParameterSpec;

import com.dstc.security.common.OID;
import com.dstc.security.common.AlgorithmId;
import com.dstc.security.common.PrivateKeyInfo;
import com.dstc.security.asn1.Sequence;
import com.dstc.security.asn1.OctetString;
import com.dstc.security.asn1.Asn1;
import com.dstc.security.asn1.Asn1Exception;

/**
 * <p>
 * This class encrypts/decrypts a PrivateKey to/from PKCS#8 format.
 * Password-based encryption based on PKCS#5 and PKCS#12 are supported.
 * <p> 
 * Instances of this class can be stored in PKCS#8 EncryptedPrivateKeyInfo
 * format using the encode() method, with the ASN.1 structure
 * <pre>
 * EncryptedPrivateKeyInfo ::= SEQUENCE {
 *   encryptionAlgorithm EncryptionAlgorithmIdentifier,
 *   encryptedData EncryptedData }
 *
 * EncryptionAlgorithmIdentifier ::= AlgorithmIdentifier
 *
 * EncryptedData ::= OCTET STRING
 * </pre>
 * <p>
 * Typical usage of this class would be the following:
 * <p>
 * To encrypt a private key using the password "myPassword" and store it 
 * in a file with the above format,
 * <pre>
 * PKCS8EncryptedPrivateKey encKey = new PKCS8EncryptedPrivateKey(privateKey);
 * FileOutputStream fos = new FileOutputStream(fileName);
 * encKey.encrypt("myPassword".toCharArray());
 * fos.write(encKey.getEncoded());
 * </pre>
 * Conversely, to decrypt the encrypted private key stored in the file 
 * "fileName",
 * <pre>
 * FileInputStream fis = new FileInputStream("fileName"); 
 * PKCS8EncryptedPrivateKey encKey = new PKCS8EncryptedPrivateKey(fis);
 * encKey.decrypt("myPassword".toCharArray());
 * PrivateKey privateKey = encKey.getPrivateKey();
 * </pre>
 *
 *
 * @author Ming Yung, Eddy Cheung
 */ 
public class PKCS8EncryptedPrivateKey
{
  private Asn1 asn1 = null;
  private String alg = OID.pbeWithMD5AndDES_CBC;
  private AlgorithmId algoId = null;
  private byte[] encKeyBytes = null;
  private PrivateKey priv = null;

  private void decode(Asn1 asn1) throws PKCS8Exception
  {
    try
    {
      this.asn1 = asn1;
      Iterator it = asn1.components();
  
      this.algoId = new AlgorithmId((Asn1)it.next());
  
      this.alg = this.algoId.getOid();
  
      this.encKeyBytes = ((OctetString)it.next()).getBytes();
    }
    catch (Asn1Exception e)
    {
      throw new PKCS8Exception("Bad pkcs8 encoding: " + e.getMessage());
    }
    catch (ClassCastException e)
    {
      throw new PKCS8Exception("Bad pkcs8 encoding: " + e.getMessage());
    }
    catch (NoSuchElementException e)
    {
      throw new PKCS8Exception("Bad pkcs8 encoding");
    }
  }
  
  private void encode() throws IOException
  {
    this.asn1 = new Sequence();

    this.asn1.add(algoId.getAsn1());

    this.asn1.add(new OctetString(encKeyBytes));
  }

/**
 * <p> Construct a <code> PKCS8EncryptedPrivateKey </code> object from
 * a <code> PrivateKey </code> object.
 * <p> The algorithm used to encrypt the private key is PBE with 
 * MD5 and DES/CBC.
 *
 * @param priv the private key to encrypt.
 */

  public PKCS8EncryptedPrivateKey(PrivateKey priv)
  {
    this.priv = priv;
  }

/**
 * <p> Construct a <code> PKCS8EncryptedPrivateKey </code> object from
 * a <code> PrivateKey </code> object and an algorithm. The following 
 * algorithms are supported:
 * <pre>
 * PBEwithMD5AndDES_CBC
 * PBEwithSHAAnd3_KeyTripleDES_CBC
 * PBEwithSHAAnd40BitRC2_CBC
 * PBEwithSHAAnd40BitRC4
 * PBEwithSHAAnd128BitRC2_CBC
 * PBEwithSHAAnd128BitRC4
 * </pre>
 *
 * @param priv the private key to encrypt.
 * @param alg the algorithm used to encrypt the key.
 */

  public PKCS8EncryptedPrivateKey(PrivateKey priv, String alg)
  {
    this.priv = priv;
    this.alg = alg;
  }

/**
 * <p> Construct a <code> PKCS8EncryptedPrivateKey </code> object from
 * an<code> InputStream </code> .
 *
 * @param is the InputStream containing the PKCS#8 encrypted key.
 * @exception PKCS8Exception if the data in the InputStream is not in
 * the correct format.
 * @exception IOException
 */

  public PKCS8EncryptedPrivateKey(InputStream is) 
    throws PKCS8Exception, IOException
  {
    decode(Asn1.getAsn1(is));
  }

/**
 * <p> Construct a <code> PKCS8EncryptedPrivateKey </code> object from
 * a byte array.
 *
 * @param encoded the byte array containing the PKCS#8 encrypted key.
 * @exception PKCS8Exception if the data in the byte array is not in
 * the correct format.
 */

  public PKCS8EncryptedPrivateKey(byte[] encoded) 
    throws PKCS8Exception
  {
    try
    {
      decode(Asn1.getAsn1(encoded));
    }
    catch (Asn1Exception e)
    {
      throw new PKCS8Exception("Bad pkcs8 encoding: " + e.getMessage());
    }
  }

/**
 * <p> Encrypt the <code> PKCS8EncryptedPrivateKey </code> object using
 * the given password.
 *
 * @param password the character array containing the password used to
 * encrypt the key.
 * @exception PKCS8Exception if the encryption process fails.
 */

  public void encrypt(char[] password) throws PKCS8Exception
  {
    encrypt(new PBEKeySpec(password));
  }

/**
 * <p> Encrypt the <code> PKCS8EncryptedPrivateKey </code> object using
 * the <code> PBEKeySpec </code> object.
 *
 * @param keySpec the <code> PBEKeySpec </code> containing the password 
 * used to encrypt the key.
 * @exception PKCS8Exception if the encryption process fails.
 */

  public void encrypt(PBEKeySpec keySpec) throws PKCS8Exception
  {
    AlgorithmParameters algParams = null;
    String jcaName = null;
    SecretKeyFactory fact = null;
    Cipher cipher = null;
    PBEParameterSpec paramsSpec = null;

    try
    {
      jcaName = OID.getAlgName(alg);
      if (jcaName == null)
        throw new PKCS8Exception("PBE algorithm " + alg + " unsupported");

      fact = SecretKeyFactory.getInstance(jcaName);
      SecretKey pbeKey = fact.generateSecret(keySpec);

      MessageDigest md5 = MessageDigest.getInstance("MD5");
      md5.update(pbeKey.getEncoded());
      byte preSalt[] = md5.digest(priv.getEncoded());
      
      byte salt[] = new byte[8];
      System.arraycopy(preSalt, 0, salt, 0, 8);
      paramsSpec = new PBEParameterSpec(salt, 5);

      algParams = AlgorithmParameters.getInstance(jcaName);
      algParams.init(paramsSpec);

      cipher = Cipher.getInstance(jcaName);

      cipher.init(Cipher.ENCRYPT_MODE, pbeKey, paramsSpec);
    }
    catch (NoSuchAlgorithmException e)
    {
      throw new PKCS8Exception("Provider error: "+ e.getMessage());
    }
    catch (Exception e)
    {
      throw new RuntimeException("Internal error: " + e.getMessage());
    }

    try
    {
      byte pkiBytes[] = priv.getEncoded();

      encKeyBytes = cipher.doFinal(pkiBytes);

      algoId = new AlgorithmId(alg, algParams);

      this.encode();
    }
    catch (Exception e)
    {
      throw new RuntimeException("Internal error: " + e.getMessage());
    }
  }

/**
 * <p> Decrypt the <code> PKCS8EncryptedPrivateKey </code> object using
 * the given password.
 *
 * @param password the character array containing the password used to
 * decrypt the PKCS#8 encrypted key.
 * @exception PKCS8Exception if the decryption process fails.
 */

  public void decrypt(char[] password) throws PKCS8Exception
  {
    decrypt(new PBEKeySpec(password));
  }

/**
 * <p> Decrypt the <code> PKCS8EncryptedPrivateKey </code> object using
 * the <code> PBEKeySpec </code> object.
 *
 * @param keySpec the <code> PBEKeySpec </code> containing the password 
 * used to decrypt the key.
 * @exception PKCS8Exception if the decryption process fails.
 */

  public void decrypt(PBEKeySpec keySpec) throws PKCS8Exception
  {
    Cipher cipher = null;
    SecretKeyFactory fact = null;
    byte[] encodedKey = null;

    try
    {
      cipher = Cipher.getInstance(OID.getAlgName(alg));
      fact = SecretKeyFactory.getInstance(OID.getAlgName(alg));
    }
    catch (NoSuchPaddingException e)
    {
      throw new RuntimeException(e.getMessage());
    }
    catch (NoSuchAlgorithmException e)
    {
      throw new RuntimeException(e.getMessage());
    }

    try
    {
      PBEParameterSpec paramsSpec = (PBEParameterSpec)
          algoId.getParams().getParameterSpec(
            javax.crypto.spec.PBEParameterSpec.class);

      SecretKey pbeKey = fact.generateSecret(keySpec);

      cipher.init(Cipher.DECRYPT_MODE, pbeKey, paramsSpec, null);
      encodedKey = cipher.doFinal(encKeyBytes);
    }
    catch (BadPaddingException e)
    {
      throw new PKCS8Exception("Invalid password");
    }
    catch (Exception e)
    {
      throw new RuntimeException("Internal error: " + e.toString());
    }

    try
    {
      PrivateKeyInfo pki = new PrivateKeyInfo(encodedKey);

      AlgorithmId algo = pki.getAlgorithmId();

      KeyFactory keyFact = null;

      String algOid = algo.getOid();
      if (algOid.equals(OID.rsaEncryption))
      {
        keyFact = KeyFactory.getInstance("RSA");
      }
      else if (algOid.equals(OID.dsa))
      {
        keyFact = KeyFactory.getInstance("DSA");
      }
      else if (algOid.equals(OID.dhKeyAgreement))
      {
        keyFact = KeyFactory.getInstance("DH");
      }
      else
      {
        keyFact = KeyFactory.getInstance(algOid);
      }

      priv 
        = keyFact.generatePrivate(new PKCS8EncodedKeySpec(encodedKey));
    }
    catch (InvalidKeySpecException e)
    {
      throw new RuntimeException("Internal error: " + e.getMessage());
    }
    catch (Asn1Exception e)
    {
      throw new PKCS8Exception("Bad encoding or bad password: " 
        + e.getMessage());
    }
    catch (NoSuchAlgorithmException e)
    {
      throw new PKCS8Exception("Algorithm not supported: " + e.getMessage());
    }
  }

/**
 * <p> Returns the DER encoding of this <code> PKCS8EncryptedPrivateKey
 * </code> object.
 *
 * @exception PKCS8Exception if <code> encrypt() </code> has not yet
 * been called.
 */

  public byte[] getEncoded() throws PKCS8Exception
  {
    if (this.asn1 == null)
      throw new PKCS8Exception("Private key not yet encrypted");

    try
    {
      return this.asn1.getEncoded();
    }
    catch (Asn1Exception e)
    {
      throw new RuntimeException("Internal error: " + e.getMessage());
    } 
  }

/**
 * <p> Returns the <code> PrivateKey </code> associated with this object.
 *
 * @exception PKCS8Exception if <code> decrypt() </code> has not yet
 * been called.
 */

  public PrivateKey getPrivateKey() throws PKCS8Exception
  {
    if (this.priv == null)
      throw new PKCS8Exception("Private key not yet decrypted");
 
    return this.priv;
  }
}
