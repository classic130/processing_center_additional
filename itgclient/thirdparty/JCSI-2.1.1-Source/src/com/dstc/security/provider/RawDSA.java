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
import java.math.BigInteger;
import java.util.Iterator;
import java.security.SignatureSpi;
import java.security.PublicKey;
import java.security.PrivateKey;
import java.security.MessageDigest;
import java.security.KeyFactory;
import java.security.InvalidParameterException;
import java.security.InvalidAlgorithmParameterException;
import java.security.InvalidKeyException;
import java.security.NoSuchAlgorithmException;
import java.security.NoSuchProviderException;
import java.security.ProviderException;
import java.security.SignatureException;
import java.security.SecureRandom;
import java.security.spec.AlgorithmParameterSpec;
import java.security.spec.X509EncodedKeySpec;
import java.security.spec.PKCS8EncodedKeySpec;
import java.security.spec.InvalidKeySpecException;

import com.dstc.security.asn1.Asn1;
import com.dstc.security.asn1.Sequence;

/**
 * <p>Implements the DSA signature algorithm following the DSS standard.
 *
 * @see java.security.Signature
 * @see com.dstc.security.provider.DSAParameters
 * @see com.dstc.security.provider.DSAPublicKey
 * @see com.dstc.security.provider.DSAPrivateKey
 *
 * @version 0.98, 98/07/01
 * @author Ming Yung
 */
public class RawDSA extends SignatureSpi
{
  protected java.security.interfaces.DSAPublicKey pubKey;
  protected java.security.interfaces.DSAPrivateKey privKey;
  protected ByteArrayOutputStream bos = new ByteArrayOutputStream();
  //protected MessageDigest md = null;
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
    if (params != null)
      throw new InvalidAlgorithmParameterException("Parameter not supported");
  }

  protected void engineInitVerify(PublicKey publicKey) 
     throws InvalidKeyException 
  {
    if (publicKey.getAlgorithm().equals("DSA")) 
    {
      if (publicKey instanceof java.security.interfaces.DSAPublicKey)
        this.pubKey = (java.security.interfaces.DSAPublicKey)publicKey;

      reset();
    }
    else
      throw new InvalidKeyException("Not a DSA Public Key");
  }

  protected void engineInitSign(PrivateKey privateKey) 
     throws InvalidKeyException 
  {
    if (privateKey.getAlgorithm().equals("DSA")) 
    {
      if (privateKey instanceof java.security.interfaces.DSAPrivateKey)
        this.privKey = (java.security.interfaces.DSAPrivateKey)privateKey;

      reset();
    } 
    else 
      throw new InvalidKeyException ("Not a DSA Private Key");
  }

  protected void engineUpdate(byte b) throws SignatureException 
  {
    buf[0] = b;
    engineUpdate(buf, 0, 1);
  }

  protected void engineUpdate(byte b[], int off, int len) 
      throws SignatureException 
  {
    bos.write(b, off, len);
  }

  void reset()
  {
    bos.reset();
  }

  BigInteger generateH() throws SignatureException
  {
    byte[] data = bos.toByteArray();
    if (data.length == 0)
      throw new SignatureException("Nothing to sign");
    bos.reset();

    return new BigInteger(1, data);
  }

  protected byte[] engineSign() throws SignatureException 
  {
    java.security.interfaces.DSAParams dsaParams = privKey.getParams();
    BigInteger k = new BigInteger(dsaParams.getQ().bitLength()-1,
                                   new SecureRandom());
    BigInteger h = generateH();
    
    BigInteger r = dsaParams.getG().modPow(k, dsaParams.getP()).mod(
        dsaParams.getQ());

    BigInteger xrPlusH = r.multiply(privKey.getX()).add(h);
    BigInteger kinv = k.modInverse(dsaParams.getQ());
    BigInteger s = kinv.multiply(xrPlusH).mod(dsaParams.getQ());
    
    try 
    {
      Asn1 dssSig = new Sequence();
      dssSig.add(new com.dstc.security.asn1.Integer(r));
      dssSig.add(new com.dstc.security.asn1.Integer(s));
      return dssSig.getEncoded();
    } 
    catch (Exception e) 
    {
      throw new SignatureException(e.getMessage());
    }
  }

  protected boolean engineVerify(byte sigBytes[]) 
     throws SignatureException 
  {
    BigInteger r, s;

    try 
    {
      Asn1 dssSig = Asn1.getAsn1(sigBytes);
      Iterator it = dssSig.components();
      r = ((com.dstc.security.asn1.Integer)it.next()).getBigInteger();
      s = ((com.dstc.security.asn1.Integer)it.next()).getBigInteger();
    }
    catch (Exception e) 
    {
      throw new SignatureException("Badly formed signature");
    }

    java.security.interfaces.DSAParams dsaParams = pubKey.getParams();
  
    BigInteger w = s.modInverse(dsaParams.getQ());

    BigInteger h = generateH();

    BigInteger u1 = h.multiply(w).mod(dsaParams.getQ());

    BigInteger u2 = r.multiply(w).mod(dsaParams.getQ());
    BigInteger v1 = dsaParams.getG().modPow(u1, dsaParams.getP());
    BigInteger v2 = pubKey.getY().modPow(u2, dsaParams.getP());
    BigInteger v = v1.multiply(v2).mod(dsaParams.getP()).mod(
                   dsaParams.getQ());
    return (v.equals(r));
  }

  protected String getAlgorithm()
  {
    return "RawDSA";
  }

  private static final boolean DUMMY = Licensed.VALID;
}
