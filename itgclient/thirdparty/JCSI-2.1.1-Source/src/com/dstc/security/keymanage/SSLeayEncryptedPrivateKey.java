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

import java.util.*;
import java.io.*;
import java.security.*;
import java.security.interfaces.*;
import java.security.spec.*;
import javax.crypto.*;
import javax.crypto.spec.*;

import com.dstc.security.asn1.Asn1;
import com.dstc.security.asn1.Sequence;
import com.dstc.security.asn1.Asn1Exception;
import com.dstc.security.common.PrivateKeyInfo;
import com.dstc.security.util.Base64InputStream;
import com.dstc.security.util.Base64OutputStream;

/**
 * <p>
 * This class encrypts/decrypts a PrivateKey to/from the the 
 * proprietary encryption format used in SSLeay. The encrypted keys
 * are stored in the ASCII format
 * <pre>
 * -----BEGIN RSA PRIVATE KEY-----
 * Proc-Type: 4,ENCRYPTED
 * DEK-Info: DES-EDE3-CBC,ivBytes
 * 
 * Base 64 encoding goes here
 * -----END RSA PRIVATE KEY-----
 * </pre>
 * Here, ivBytes is the hexadecimal representation of the Initialization
 * Vector used in the encryption process.
 * <p>
 * Typical usage of this class would be the following:
 * <p>
 * To encrypt the <code> PrivateKey </code> object privateKey using 
 * the password "myPassword" and store it in a file with the above format,
 * <pre>
 * SSLeayEncryptedPrivateKey encKey = 
 *              new SSLeayEncryptedPrivateKey(privateKey);
 * FileOutputStream fos = new FileOutputStream(fileName);
 * encKey.encrypt("myPassword".toCharArray());
 * fos.write(encKey.getEncoded());
 * </pre>
 * Conversely, to decrypt the encrypted private key stored in the file
 * "fileName",
 * <pre>
 * FileInputStream fis = new FileInputStream("fileName");
 * SSLeayEncryptedPrivateKey encKey = new SSLeayEncryptedPrivateKey(fis);
 * encKey.decrypt("myPassword".toCharArray());
 * PrivateKey privateKey = encKey.getPrivateKey();
 * </pre>
 *
 *
 * @author Ming Yung
 */

public class SSLeayEncryptedPrivateKey
{
  private static final byte[] HEADER = 
    ("-----BEGIN RSA PRIVATE KEY-----\n" +
    "Proc-Type: 4,ENCRYPTED\n" +
    "DEK-Info: DES-EDE3-CBC,").getBytes();
  private static final byte[] FOOTER = 
    "\n-----END RSA PRIVATE KEY-----".getBytes();
  private String keyAlg;
  private IvParameterSpec iv; 
  private Cipher ciph;
  private String encAlg = "DESede";
  private byte[] encodedKey;
  private PrivateKey priv;
  private SecureRandom rand = null;

/**
 * <p> Construct an <code> SSLeayEncryptedPrivateKey </code> object from
 * a byte array containing the (base-64 encoded) encrypted private key.
 *
 * @param encoding the  byte array containing the (base-64 encoded) 
 * encrypted private key.
 * @exception SSLeayException if the data is corrupt.
 */

  public SSLeayEncryptedPrivateKey(byte[] encoding) 
    throws SSLeayException
  {
    try
    {
      decode(new ByteArrayInputStream(encoding));
    }
    catch (IOException e)
    {
      throw new SSLeayException("Unexpected error");
    }
  }

/**
 * <p> Construct an <code> SSLeayEncryptedPrivateKey </code> object from
 * an <code> InputStream </code>  containing the (base-64 encoded) 
 * encrypted private key.
 *
 * @param is the <code> InputStream </code> containing the (base-64 encoded) 
 * encrypted private key.
 * @exception SSLeayException if the data is corrupt.
 * @exception IOException
 */

  public SSLeayEncryptedPrivateKey(InputStream is) 
    throws SSLeayException, IOException
  {
    decode(is);
  }

/**
 * <p> Construct an <code> SSLeayEncryptedPrivateKey </code> object from
 * a <code> PrivateKey </code>
 *
 * @param rand source of randomness (can be <code> null </code>).
 * @param priv the <code> PrivateKey </code> to be encrypted.
 * @exception SSLeayException if <code> PrivateKey </code> is not an instance 
 * of <code> java.security.interfaces.RSAPrivateCrtKey </code>. 
 */

  public SSLeayEncryptedPrivateKey(SecureRandom rand, PrivateKey priv) 
    throws SSLeayException
  {
    if (!(priv instanceof RSAPrivateCrtKey))
      throw new SSLeayException("Only RSA CRT Private Key supported");

    this.rand = rand;
    this.priv = priv;
  }

/**
 * <p> Encrypts the <code> SSLeayEncryptedPrivateKey </code> object using
 * the given password.
 *
 * @param  password the character array containing the password used to
 * encrypt the key.
 * @exception SSLeayException if the encryption process fails.
 */

  public void encrypt(char[] pass) throws SSLeayException
  {
    try
    {
      PrivateKeyInfo info = new PrivateKeyInfo(priv.getEncoded());
      byte[] encoding = info.getEncodedKey();

      ciph = Cipher.getInstance(encAlg + "/CBC/PKCS5Padding");
      byte[] ivBytes = new byte[8];
      
      if (rand == null)
      {
        rand = new SecureRandom();
      }
      rand.nextBytes(ivBytes);
      iv = new IvParameterSpec(ivBytes);

      ciph.init(Cipher.ENCRYPT_MODE, passToKey(pass), iv);

      byte[] encrypted = ciph.doFinal(encoding);
      ByteArrayOutputStream baos = new ByteArrayOutputStream();
      Base64OutputStream b64 
        = new Base64OutputStream(Base64OutputStream.ENCODE, 15, baos);
      b64.write(encrypted);
      b64.flush();
      b64.close();
      this.encodedKey = baos.toByteArray();
    }
    catch (Asn1Exception e)
    {
      throw new SSLeayException("Unexpected error: " + e.getMessage());
    }
    catch (IOException e)
    {
      throw new SSLeayException("Unexpected error: " + e.getMessage());
    }
    catch (NoSuchAlgorithmException e)
    {
      throw new SSLeayException("Provider error: " + e.getMessage());
    }
    catch (Exception e)
    {
      throw new SSLeayException("Unexpected error: " + e.getMessage());
    }
  }

/**
 * <p> Returns the Base64-encoding of the <code>SSLeayEncryptedPrivateKey
 * </code>.
 *
 * @exception SSLeayException if <code> encrypt() </code> has not yet
 * been called.
 */

  public byte[] getEncoded() throws SSLeayException
  {
    if (this.encodedKey == null) {
        throw new SSLeayException("Private key not yet encrypted");
    }
    byte[] ivString = ivToString().getBytes();

    byte[] retval 
      = new byte[HEADER.length + ivString.length + 
                 FOOTER.length + encodedKey.length]; 
    System.arraycopy(HEADER, 0, retval, 0, HEADER.length);
    System.arraycopy(ivString, 0, retval, HEADER.length, ivString.length);
    System.arraycopy(encodedKey, 0, retval, HEADER.length + ivString.length, 
                     encodedKey.length);
    System.arraycopy(FOOTER, 0, retval, HEADER.length + encodedKey.length +
                     ivString.length, FOOTER.length);

    return retval;
  }

  private void decode(InputStream is) 
    throws IOException, SSLeayException
  {
    InputStreamReader isr = new InputStreamReader(is);
    BufferedReader in = new BufferedReader(isr);

    StringBuffer sb = new StringBuffer();

    String next = in.readLine();
    checkAlg(next);

    next = in.readLine();
    if (next.startsWith("Proc-Type: 4,ENCRYPTED"))
    {
      checkEncrypted(in.readLine());
      in.readLine();
    }
    else
      throw new SSLeayException("Not an encrypted private key");
    
    while (true)
    {
      next = in.readLine();
      if (next.startsWith("-----END"))
      {
        ByteArrayOutputStream baos = new ByteArrayOutputStream();
        while (true)
        {
          next = in.readLine();
          if (next == null)
            break;
          baos.write((next + "\n").getBytes());
        }
        is = new ByteArrayInputStream(baos.toByteArray());
        break;
      }

      sb.append(next).append("\n");
    }
    encodedKey = sb.toString().getBytes();
  }

/**
 * <p> Returns the <code> PrivateKey </code> associated with this object.
 *
 * @exception SSLeayException if <code> decrypt() </code> has not yet
 * been called.
 */

  public PrivateKey getPrivateKey() throws SSLeayException
  {
    if (this.priv == null)
      throw new SSLeayException("Private key not yet decrypted");

    return this.priv;
  }

/**
 * <p> Decrypts the <code> SSLeayEncryptedPrivateKey </code> object using
 * the given password.
 *
 * @param  password the character array containing the password used to
 * decrypt the key.
 * @exception SSLeayException if the decryption process fails.
 */

  public void decrypt(char[] pass) throws SSLeayException
  {
    try
    {
      ByteArrayInputStream bais 
        = new ByteArrayInputStream(encodedKey);
      Base64InputStream b64 = new Base64InputStream(bais); 
  
      byte[] buf = new byte[128];
      ByteArrayOutputStream baos = new ByteArrayOutputStream();
      while (true)
      {
        int rd = b64.read(buf);
        if (rd == -1) break;
 
        baos.write(buf, 0, rd);
      }
      byte[] enc = baos.toByteArray();
  
      ciph.init(Cipher.DECRYPT_MODE, passToKey(pass), iv);
      byte[] dec = ciph.doFinal(enc);
  
      KeyFactory keyFact = KeyFactory.getInstance("RSA");
        
      this.priv = keyFact.generatePrivate(asn1ToPriv(dec));
    }
    catch (BadPaddingException e)
    {
      throw new SSLeayException("Bad password");
    }
    catch (NoSuchAlgorithmException e)
    {
      throw new SSLeayException("Provider error: " + e.getMessage());
    }
    catch (Exception e)
    {
      throw new SSLeayException("Unexpected error: " + e.getMessage());
    }
  }

  ///////////// private methods ////////////////////

  private void checkAlg(String line) throws SSLeayException
  {
    if (!line.startsWith("-----BEGIN"))
      throw new SSLeayException("Not an SSLeay protected private key");

    if (line.indexOf("RSA") != -1)
      keyAlg = "RSA";
    else
      throw new SSLeayException("Only RSA keys supported");
  }

  private void checkEncrypted(String line) throws SSLeayException
  {
    try
    {
      String keyInfo = line.substring(10);
      StringTokenizer tknz = new StringTokenizer(keyInfo, ",", false);

      if (tknz.nextToken().equals("DES-EDE3-CBC"))
        encAlg = "DESede";
      else
        throw new SSLeayException("Only DESede encryption supported");

      ciph = Cipher.getInstance(encAlg + "/CBC/PKCS5Padding");

      retrieveIV(tknz.nextToken());
    }
    catch (Exception e)
    {
      throw new SSLeayException("Unexpected error: " + e.getMessage());
    }
  }

  private void retrieveIV(String s)
  {
    byte[] ivBytes = new byte[8];
    for (int j=0; j<8; j++)
    {
      ivBytes[j] 
        = (byte)java.lang.Integer.parseInt(s.substring(j*2, j*2 + 2), 16);
    }        
    iv = new IvParameterSpec(ivBytes);
  }

  private String ivToString()
  {
    byte[] ivBytes = iv.getIV();
    StringBuffer sb = new StringBuffer();
    for (int i=0; i<ivBytes.length; i++)
    {
      sb.append(hexDigit(ivBytes[i]));
    }
    sb.append("\n\n");
    return sb.toString();
  }

  private SecretKey passToKey(char[] pass) throws SSLeayException
  {
    try
    {
      byte[] keyMat = new byte[24];
  
      byte[] passBytes = (new String(pass)).getBytes();
      MessageDigest md = MessageDigest.getInstance("MD5");
      md.update(passBytes);
      md.update(iv.getIV());
      byte[] data = md.digest();
      System.arraycopy(data, 0, keyMat, 0, 16);
  
      md.update(data);
      md.update(passBytes);
      md.update(iv.getIV());
      data = md.digest();
      System.arraycopy(data, 0, keyMat, 16, 8);

      SecretKeySpec key = new SecretKeySpec(keyMat, encAlg);
      return key;
    }
    catch (NoSuchAlgorithmException e)
    {
      throw new SSLeayException("Provider error: " + e.getMessage());
    }
  }

  private static KeySpec asn1ToPriv(byte[] dec) throws Asn1Exception
  {
    try
    {
      Asn1 seq = Asn1.getAsn1(dec);
      Iterator it = seq.components();


      if (((com.dstc.security.asn1.Integer)it.next()).getInt() != 0)
        throw new Asn1Exception("Bad asn1 encoding");

      RSAPrivateCrtKeySpec keySpec = new RSAPrivateCrtKeySpec(
        ((com.dstc.security.asn1.Integer)it.next()).getBigInteger(),
        ((com.dstc.security.asn1.Integer)it.next()).getBigInteger(),
        ((com.dstc.security.asn1.Integer)it.next()).getBigInteger(),
        ((com.dstc.security.asn1.Integer)it.next()).getBigInteger(),
        ((com.dstc.security.asn1.Integer)it.next()).getBigInteger(),
        ((com.dstc.security.asn1.Integer)it.next()).getBigInteger(),
        ((com.dstc.security.asn1.Integer)it.next()).getBigInteger(),
        ((com.dstc.security.asn1.Integer)it.next()).getBigInteger()
      );

      return keySpec;
    }
    catch (ClassCastException e)
    {
      throw new Asn1Exception("Bad asn1 encoding: " + e.getMessage());
    }
  }

  private static final String hexDigit(byte x)
  {
    char ret[] = new char[2];
    char c = (char) ((x >> 4) & 0xf);
    if (c > 9)
    {
      c = (char)((c - 10) + 'a');
    }
    else
    {
      c = (char)(c + '0');
    }
    ret[0] = c;
 
    c = (char)(x & 0xf);
    if (c > 9)
    {
      c = (char)((c - 10) + 'a');
    }
    else
    {
      c = (char)(c + '0');
    }
    ret[1] = c;
    return new String(ret);
  }                   
}
