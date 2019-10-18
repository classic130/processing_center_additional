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

import java.io.IOException;
import java.io.ByteArrayOutputStream;
import java.math.BigInteger;
import java.security.SecureRandom;
import java.security.AlgorithmParameters;
import java.security.Key;
import java.security.PublicKey;
import java.security.PrivateKey;
import java.security.KeyFactory;
import java.security.InvalidParameterException;
import java.security.InvalidAlgorithmParameterException;
import java.security.InvalidKeyException;
import java.security.NoSuchAlgorithmException;
import java.security.SignatureException;
import java.security.spec.AlgorithmParameterSpec;
import java.security.spec.PKCS8EncodedKeySpec;
import java.security.spec.X509EncodedKeySpec;

import javax.crypto.Cipher;
import javax.crypto.CipherSpi;
import javax.crypto.NoSuchPaddingException;
import javax.crypto.ShortBufferException;
import javax.crypto.BadPaddingException;
import javax.crypto.IllegalBlockSizeException;

import com.dstc.security.util.Bytes;

/**
 * Implements RSA Cipher according to PKCS#1
 */
public class RSA extends CipherSpi
{
  private static final byte PRIVATE_KEY_ENCRYPT_MODE = (byte)0x01;
  private static final byte PUBLIC_KEY_ENCRYPT_MODE = (byte)0x02;

  private java.security.interfaces.RSAPublicKey rsaPubKey;
  private java.security.interfaces.RSAPrivateKey rsaPrivKey;
  private java.security.interfaces.RSAPrivateCrtKey rsaPrivCrtKey;
  private byte data[];
  private SecureRandom random;
  private byte[] empty = new byte[0];

  private int state;
  private ByteArrayOutputStream bos = new ByteArrayOutputStream();
  private PKCS1Padding pad;
  private int k;
  private byte pkcs1Mode = PUBLIC_KEY_ENCRYPT_MODE;

  public void engineSetPadding(String padding) throws NoSuchPaddingException 
  {
    if (!padding.equals("PKCS1Padding"))
      throw new NoSuchPaddingException(padding + " Not supported");
  }

  public void engineSetMode(String mode) throws NoSuchAlgorithmException 
  {
    throw new NoSuchAlgorithmException(mode + " Not supported");
  }

  protected int engineGetBlockSize() 
  {
    //Not a block cipher
    return 0;
  }

  protected int engineGetOutputSize(int inputLen)
  {
    if (this.state == Cipher.DECRYPT_MODE)
    {
      return k;   //over-estimate. Can we do better?
    }
    else if (this.state == Cipher.ENCRYPT_MODE)
    {
      return k;
    }
    else
    {
      throw new IllegalStateException("RSA Cipher not yet initialized");
    }
  }

  protected byte[] engineGetIV() 
  {
    return null;
  }

  protected AlgorithmParameters engineGetParameters()
  {
    return null;
  }

  protected void engineInit(int opmode, Key key, SecureRandom random) 
    throws InvalidKeyException 
  {
    this.state = opmode;
    this.random = random;

    if (!key.getAlgorithm().equals("RSA"))
    {
      throw new InvalidKeyException("Not an RSA Key");
    }

    if (key instanceof java.security.interfaces.RSAPublicKey)
    {
      this.rsaPubKey = (java.security.interfaces.RSAPublicKey)key;
      k = (this.rsaPubKey.getModulus().bitLength() + 7) >>> 3;

      if (opmode == Cipher.DECRYPT_MODE)
        pkcs1Mode = PRIVATE_KEY_ENCRYPT_MODE;
      else
        pkcs1Mode = PUBLIC_KEY_ENCRYPT_MODE;
    }
    else if (key instanceof PrivateKey)
    {
      if (opmode == Cipher.DECRYPT_MODE)
        pkcs1Mode = PUBLIC_KEY_ENCRYPT_MODE;
      else
        pkcs1Mode = PRIVATE_KEY_ENCRYPT_MODE;

      if (key instanceof java.security.interfaces.RSAPrivateCrtKey)
      {
        this.rsaPrivCrtKey = (java.security.interfaces.RSAPrivateCrtKey)key;
        k = (this.rsaPrivCrtKey.getModulus().bitLength() + 7) >>> 3;
      }
      else if (key instanceof java.security.interfaces.RSAPrivateKey)
      {
        this.rsaPrivKey = (java.security.interfaces.RSAPrivateKey)key;
        k = (this.rsaPrivKey.getModulus().bitLength() + 7) >>> 3;
      }
    }
    else
      throw new InvalidKeyException("Cannot handle this key");

    this.bos.reset();
    this.pad = new PKCS1Padding(this.pkcs1Mode);
  }

  protected void engineInit(int opmode, Key key, AlgorithmParameterSpec params,
                            SecureRandom random) 
    throws InvalidKeyException, InvalidAlgorithmParameterException 
  {
    if (params != null)
      throw new InvalidAlgorithmParameterException("No params needed for RSA"); 

    engineInit(opmode, key, random);
  }

  protected void engineInit(int opmode, Key key, AlgorithmParameters params,
                            SecureRandom random) 
    throws InvalidKeyException, InvalidAlgorithmParameterException 
  {
    if (params != null)
      throw new InvalidAlgorithmParameterException("No params needed for RSA"); 

    engineInit(opmode, key, random);
  }

  protected int engineDoFinal(byte input[], int inputOffset, int inputLen,
                              byte output[], int outputOffset) 
    throws ShortBufferException, IllegalBlockSizeException, BadPaddingException 
  {
    if (output.length - outputOffset < engineGetOutputSize(inputLen))
      throw new ShortBufferException("Output Buffer too short");

    byte out[] = engineDoFinal(input, inputOffset, inputLen);
    System.arraycopy(out, 0, output, outputOffset, out.length);
    return out.length;
  }

  protected byte[] engineDoFinal(byte input[], int inputOffset, int inputLen) 
    throws IllegalBlockSizeException, BadPaddingException 
  {
    byte retval[] = null;

    engineUpdate(input, inputOffset, inputLen);

    this.data = this.bos.toByteArray();
    this.bos.reset();

    if (state == Cipher.ENCRYPT_MODE)
    {
      if (pkcs1Mode == PUBLIC_KEY_ENCRYPT_MODE)
      {
        //pkcs1 padding string must be at least 8 bytes long
        if (this.data.length > k - 11)
          throw new IllegalBlockSizeException("Data too long for " +
            "PKCS1 padding");

        retval = publicKeyOp(pad.doPadding(k, this.data));
      }
      else
      {
        retval = privateCRTKeyOp(pad.doPadding(k, this.data));
      }
    }
    else if (state == Cipher.DECRYPT_MODE)
    {
      try
      {
        if (pkcs1Mode == PUBLIC_KEY_ENCRYPT_MODE)
        {
          retval = pad.doUnPadding(k, privateCRTKeyOp(this.data));
        }
        else
          retval = pad.doUnPadding(k, publicKeyOp(this.data));
      }
      catch (BadPaddingException e)
      {
        throw new BadPaddingException("Decryption error :" + e.getMessage());
      }
    }

    return retval;
  }

  protected int engineUpdate(byte input[], int inputOffset, int inputLen,
                             byte output[], int outputOffset) 
    throws ShortBufferException 
  {
    if (input != null)
    {
      this.bos.write(input, inputOffset, inputLen);
    }
    return 0;
  }

  protected byte[] engineUpdate(byte input[], int inputOffset, int inputLen)
  {
    if (input != null)
    {
      this.bos.write(input, inputOffset, inputLen);
    }
    return empty;
  }

  private byte[] publicKeyOp(byte input[]) 
  {
    BigInteger modulus = rsaPubKey.getModulus();
    BigInteger exponent = rsaPubKey.getPublicExponent();

    BigInteger x = new BigInteger(1, input);
    BigInteger y = x.modPow(exponent, modulus);
 
    return getBytes(y, k, this.state);
  }

  private byte[] privateKeyOp(byte input[]) 
  {
    BigInteger modulus = rsaPrivKey.getModulus();
    BigInteger exponent = rsaPrivKey.getPrivateExponent();

    BigInteger y = new BigInteger(1, input);
    BigInteger x = y.modPow(exponent, modulus);

    return getBytes(x, k, this.state);
  }

  private byte[] privateCRTKeyOp(byte input[]) 
  {
    BigInteger modulus, exponent, p, q, primeExponentP, primeExponentQ, 
               crtCoefficient;

    modulus = rsaPrivCrtKey.getModulus();
    exponent = rsaPrivCrtKey.getPrivateExponent();

    p = rsaPrivCrtKey.getPrimeP();
    q = rsaPrivCrtKey.getPrimeQ();
    primeExponentP = rsaPrivCrtKey.getPrimeExponentP();
    primeExponentQ = rsaPrivCrtKey.getPrimeExponentQ();
    crtCoefficient = rsaPrivCrtKey.getCrtCoefficient();

    BigInteger y = new BigInteger(1, input);

    BigInteger j1 = y.modPow(primeExponentP, p);
    BigInteger j2 = y.modPow(primeExponentQ, q);
    BigInteger h = j1.subtract(j2).multiply(crtCoefficient).mod(p);
    BigInteger x = h.multiply(q).add(j2);

    return getBytes(x, k, this.state);
  }

  protected class PKCS1Padding
  {
    private byte blockType;

    protected PKCS1Padding(byte BT)
    {
      this.blockType = BT;
    }

    protected byte[] doPadding(int k, byte[] data)
    {
      // PKCS#1 specifies: EB = 00 || BT || PS || 00 || D
      byte retval[] = new byte[k];
      int padLen = k - 3 - data.length;
  
      // First byte 00
      retval[0] = (byte)0x00;
  
      // BT
      retval[1] = this.blockType;
  
      // PS
      if (this.blockType == 0x01)
      {
        for (int i=0; i < padLen; i++)
        {
          retval[2+i] = (byte)0xff;
        }
      }
      else if (this.blockType == 0x02)
      {
        byte[] randBytes = new byte[padLen];
        random.nextBytes(randBytes);
        for (int i=0; i<randBytes.length; i++)
        {
          randBytes[i] |= 0x01;
        }
        System.arraycopy(randBytes, 0, retval, 2, randBytes.length);
      }
      else
        throw new RuntimeException("Internal error: unsupported block type " +
          this.blockType);

      // 00 || D
      System.arraycopy(data, 0, retval, k - data.length, data.length);
  
      // EB
      return retval;
    }

    protected byte[] doUnPadding(int k, byte block[])
      throws BadPaddingException
    {
      if ((block[0] != this.blockType))
      {
        throw new BadPaddingException("Encountered block type: " + block[0] + 
          " while expecting " + this.blockType);
      }
  
      int index = 2 - k + block.length;
  
      // Compute beginning of data
      while (true) 
      {
        if (block[index] == (byte)0x00) break;
        index++;
      }
  
      byte retval[] = new byte[block.length - index - 1];
      System.arraycopy(block, index + 1, retval, 0, retval.length);
      return retval;
    }
  }

  private static byte[] getBytes(BigInteger num, int bitLength, int mode)
  {
    byte[] b = num.toByteArray();
    if (b.length == bitLength)
    {
      return b;
    }
    else if (b.length == bitLength + 1)
    {
      byte[] retval = new byte[bitLength];
      System.arraycopy(b, 1, retval, 0, bitLength);
      return retval;
    }
    else if (b.length < bitLength)
    {
      if (mode == Cipher.DECRYPT_MODE)
      {
        return b;
      }

      byte[] retval = new byte[bitLength];
      System.arraycopy(b, 0, retval, bitLength - b.length, b.length);
      return retval;
    }
    else
    {
      throw new RuntimeException("Internal error: PKCS#1 encoding size");
    }
  }

  private static final boolean DUMMY = Licensed.VALID;
}
