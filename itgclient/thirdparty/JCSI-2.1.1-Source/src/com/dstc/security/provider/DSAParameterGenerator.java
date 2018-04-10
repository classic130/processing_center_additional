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

import java.math.BigInteger;
import java.security.SecureRandom;
import java.security.MessageDigest;
import java.security.AlgorithmParameters;
import java.security.AlgorithmParameterGeneratorSpi;
import java.security.NoSuchAlgorithmException;
import java.security.ProviderException;
import java.security.InvalidAlgorithmParameterException;
import java.security.spec.DSAParameterSpec;
import java.security.spec.AlgorithmParameterSpec;
import java.security.spec.InvalidParameterSpecException;

/**
 * <p>Implements an Algorithm Parameter Generator for use with the
 * DSA signature algorithm following the DSS standard.
 *
 * @see java.security.AlgorithmParameterGenerator
 * @see com.dstc.security.provider.DSAParameters
 * @see com.dstc.security.provider.DSA
 *
 * @version 0.98, 98/07/01
 * @author Ming Yung
 */
public final class DSAParameterGenerator extends AlgorithmParameterGeneratorSpi
{
  private SecureRandom random;
  private int keyLength;
  private static BigInteger one = BigInteger.valueOf((long)1);
  private static int probab = 80;

  protected void engineInit(int strength, SecureRandom random)
  {
    this.keyLength = strength;
    this.random = random;
  }

  protected void engineInit(AlgorithmParameterSpec genParamSpec,
                            SecureRandom random) 
    throws InvalidAlgorithmParameterException
  {
    if (genParamSpec != null)
      throw new InvalidAlgorithmParameterException("Unsupported parameter spec");
  }

  protected AlgorithmParameters engineGenerateParameters()
  {
    //Generate new DSA parameters according to NIST standard
    try
    {
      BigInteger seedE, p, q, modulus, W;
      int seedLength;

      MessageDigest md = MessageDigest.getInstance("SHA-1");
      int n = (keyLength-1)/160;
      int b = keyLength - 1 -160*n;

      while (true)
      {
        seedE = new BigInteger(160, random);
        seedLength = seedE.bitLength();
        modulus = one.shiftLeft(seedLength);

        q = SHA(md, seedE).xor(SHA(md, seedE.add(one).mod(modulus)));
        q = q.setBit(0).setBit(159);
        if (q.isProbablePrime(probab)) break;
      }

      int N = 2;
      int C = 0;
      int index = keyLength - 1;

      while (true)
      {
        //First block
        W = SHA(md, seedE.add(BigInteger.valueOf(N)).mod(modulus));
        //Next (n-1) blocks
        for (int k=1; k<n; k++)
        {
          W = W.add(SHA(md, seedE.add(
            BigInteger.valueOf(N+k)).mod(modulus)).shiftLeft(k*160));
        }
        //Last block
        W = W.add(SHA(md, seedE.add(
          BigInteger.valueOf(N+n)).mod(modulus)).mod(
            one.shiftLeft(b)).shiftLeft(n*160));
        W = W.setBit(index);

        p = W.subtract(W.mod(q.multiply(one.shiftLeft(1)))).add(one);

        if (p.testBit(index))
        {
         if (p.isProbablePrime(probab)) break;
        }

        C += 1;
        N += n + 1;
      }

      BigInteger g, h;
      while (true)
      {
        h = new BigInteger(p.bitLength() - 1, random);
        g = h.modPow(p.subtract(one).divide(q), p);
        if (g.compareTo(one) == 1) break;
      }

      DSAParameterSpec dsaParamsSpec = new DSAParameterSpec(p, q, g);

      //Uncomment to verify
      //verifyDSAParams(dsaParamsSpec, seedE);

      AlgorithmParameters algParams = 
        AlgorithmParameters.getInstance("DSA");
      algParams.init(dsaParamsSpec);
      return algParams;
    }
    catch (NoSuchAlgorithmException e)
    {
      throw new ProviderException(e.getMessage());
    }
    catch (InvalidParameterSpecException e)
    {
      throw new RuntimeException("Internal error: " + e.getMessage());
    }
  }

  private static BigInteger SHA(MessageDigest md, BigInteger S)
  {
    byte bytes[] = S.toByteArray();

    int offset = 0;
    if (bytes[0] == 0x00) offset++;
    md.reset();
    md.update(bytes, offset, bytes.length - offset);
    return new BigInteger(1, md.digest());
  }

  public void verifyDSAParams(DSAParameterSpec params, BigInteger seedE)
  {
    try
    {
      System.out.println("Verifying DSA parameters...");
      BigInteger W;

      MessageDigest md = MessageDigest.getInstance("SHA-1");
      int keyL = params.getP().bitLength();
      int n = (keyL - 1)/160;
      int b = keyL - 1 -160*n;

      int g = seedE.bitLength();
      BigInteger modulus = one.shiftLeft(g);
 
      BigInteger U = SHA(md, seedE).xor(SHA(md, seedE.add(one).mod(modulus)));

      U = U.setBit(0).setBit(159);

      if (!(U.equals(params.getQ())))
      {
        System.out.println("Verification failed for parameter q");
        return;
      }

      int N = 2;
      int C = 0;
      int index = keyL - 1;

      while (true)
      {
        //First block
        W = SHA(md, seedE.add(BigInteger.valueOf(N)).mod(modulus));
        //Next (n-1) blocks
        for (int k=1; k<n; k++)
        {
          W = W.add(SHA(md, seedE.add(
            BigInteger.valueOf(N+k)).mod(modulus)).shiftLeft(k*160));
        }
        //Last block
        W = W.add(SHA(md, seedE.add(
          BigInteger.valueOf(N+n)).mod(modulus)).mod(
            one.shiftLeft(b)).shiftLeft(n*160));
        W = W.setBit(index);
 
        W = W.subtract(W.mod(U.multiply(one.shiftLeft(1)))).add(one);

        if (W.testBit(index))
        {
         if (W.isProbablePrime(probab))
         {
           if (!(W.equals(params.getP())))
           {
             System.out.println("Verification failed for parameter p");
             System.out.println("C, N = " + C + " " + N);
           }
           else
           {
             System.out.println("Verification succeded. Counter = " + C);
           }
           return;
          }
        }

        C += 1;
        N += n + 1;
      }

    }
    catch (NoSuchAlgorithmException e)
    {
      throw new ProviderException(e.getMessage());
    }
  }

  private static final boolean DUMMY = Licensed.VALID;
}
