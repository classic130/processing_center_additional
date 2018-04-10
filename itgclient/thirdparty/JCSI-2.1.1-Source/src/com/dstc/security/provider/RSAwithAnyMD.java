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

package com.dstc.security.provider;

import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.util.Arrays;
import java.util.Iterator;
import java.security.SignatureSpi;
import java.security.PublicKey;
import java.security.PrivateKey;
import java.security.MessageDigest;
import java.security.InvalidParameterException;
import java.security.InvalidAlgorithmParameterException;
import java.security.NoSuchAlgorithmException;
import java.security.InvalidKeyException;
import java.security.SignatureException;
import java.security.spec.AlgorithmParameterSpec;

import javax.crypto.Cipher;
import javax.crypto.NoSuchPaddingException;
import javax.crypto.BadPaddingException;
import javax.crypto.IllegalBlockSizeException;

import com.dstc.security.asn1.Sequence;
import com.dstc.security.asn1.OctetString;
import com.dstc.security.asn1.Asn1;
import com.dstc.security.asn1.Asn1Exception;
import com.dstc.security.common.AlgorithmId;

/**
 * <p>An abstract class representing a signature algorithm with RSA
 * any any message Digest algorithm.
 *
 * @see java.security.Signature
 * @see com.dstc.security.provider.RSAwithMD2
 * @see com.dstc.security.provider.RSAwithMD5
 * @see com.dstc.security.provider.RSAwithSHA1
 * @see com.dstc.security.provider.RSAwithRIPEMD160
 *
 * @version 0.98, 98/07/01
 * @author Ming Yung
 */
public abstract class RSAwithAnyMD extends SignatureSpi
{
  protected RSAPublicKey pubKey;
  protected RSAPrivateCrtKey privKey;
  protected MessageDigest md;
  protected String mdOid;
  protected Cipher rsa;
  protected byte[] buf = new byte[1];

  protected void engineSetParameter(String param, Object value)
    throws InvalidParameterException
  {
    //Deprecated. Does nothing
  }

  protected Object engineGetParameter(String param)
    throws InvalidParameterException
  {
    //Deprecated.
    return null;
  }

  protected void engineSetParameter(AlgorithmParameterSpec params) 
    throws InvalidAlgorithmParameterException
  {
    throw new InvalidAlgorithmParameterException(
      "No parameter to set for this algorithm");
  }

  protected void engineInitVerify(PublicKey publicKey) 
    throws InvalidKeyException 
  {
    try
    {
      rsa = Cipher.getInstance("RSA");
      rsa.init(Cipher.DECRYPT_MODE, publicKey);
      reset();
    }
    catch (NoSuchPaddingException e)
    {
      throw new RuntimeException("Internal error: " + e.getMessage());
    }
    catch (NoSuchAlgorithmException e)
    {
      throw new RuntimeException("Internal error: " + e.getMessage());
    }
  }

  protected void engineInitSign(PrivateKey privateKey) 
    throws InvalidKeyException 
  {
    try
    {
      rsa = Cipher.getInstance("RSA");
      rsa.init(Cipher.ENCRYPT_MODE, privateKey);
      reset();
    }
    catch (NoSuchPaddingException e)
    {
      throw new RuntimeException("Internal error: " + e.getMessage());
    }
    catch (NoSuchAlgorithmException e)
    {
      throw new RuntimeException("Internal error: " + e.getMessage());
    }
  }

  protected void engineUpdate(byte b) throws SignatureException 
  {
    buf[0] = b;
    this.engineUpdate(buf, 0, 1);
  }

  protected void engineUpdate(byte b[], int off, int len) 
    throws SignatureException 
  {
    md.update(b, off, len);
  }

  byte[] finalizeSignDigest() throws SignatureException, 
           Asn1Exception, IOException
  {
    byte[] data = finalizeVerifyDigest();
    return wrapDigInfo(data);
  }

  byte[] finalizeVerifyDigest() throws SignatureException
  {
    byte[] data = md.digest();
    if (data.length == 0)
      throw new SignatureException("Nothing to sign");
    md.reset();
    return data;
  }

  void reset()
  {
    md.reset();
  }

  private byte[] wrapDigInfo(byte[] data) throws Asn1Exception, IOException
  {
      Asn1 digestInfo = new Sequence();
      digestInfo.add((new AlgorithmId(mdOid, null)).getAsn1());
      digestInfo.add(new OctetString(data));
      return digestInfo.getEncoded();
  }

  byte[] getComputed(byte[] decrypted) throws Asn1Exception
  {
      byte[] computed = null;
      Asn1 digestInfo = Asn1.getAsn1(decrypted);
      Iterator it = digestInfo.components();
      AlgorithmId mdId = new AlgorithmId((Asn1)it.next());
      computed = ((OctetString)it.next()).getBytes();
      return computed;
  }

  protected byte[] engineSign() throws SignatureException 
  {

    byte[] toBeEncrypted = null;
    try {
        toBeEncrypted = finalizeSignDigest();
    }
    catch(Asn1Exception e) {
        throw new SignatureException(e.getMessage());
    }
    catch(IOException e) {
        throw new SignatureException(e.getMessage());
    }

    try
    {
      return rsa.doFinal(toBeEncrypted);
    }
    catch (BadPaddingException e)
    {
      throw new RuntimeException("Internal error: " + e.getMessage());
    }
    catch (IllegalBlockSizeException e)
    {
      throw new RuntimeException("Internal error: " + e.getMessage());
    }
  }

  protected boolean engineVerify(byte sigBytes[]) throws SignatureException 
  {
    byte[] orig, computed;
    byte[] decrypted = null;

    try
    {
      decrypted = rsa.doFinal(sigBytes);
    }
    catch (BadPaddingException e)
    {
      return false;
    }
    catch (IllegalBlockSizeException e)
    {
      return false;
    }

    orig = finalizeVerifyDigest();
  
    try {
        computed  = getComputed(decrypted);
    }
    catch(Asn1Exception e) {
        throw new SignatureException(e.getMessage());
    }

    if(!Arrays.equals(orig, computed))
      return false;
    else
      return true;
  }

  private static final boolean DUMMY = Licensed.VALID;
}
