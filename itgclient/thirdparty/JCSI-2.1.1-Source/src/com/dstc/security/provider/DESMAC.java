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

import java.security.Key;
import java.security.spec.AlgorithmParameterSpec;
import java.security.NoSuchAlgorithmException;
import java.security.InvalidKeyException;
import java.security.InvalidAlgorithmParameterException;

import javax.crypto.Mac;
import javax.crypto.MacSpi;
import javax.crypto.Cipher;
import javax.crypto.NoSuchPaddingException;
import javax.crypto.BadPaddingException;
import javax.crypto.IllegalBlockSizeException;

/**
 * <p>Implements the DES-MAC Message Authentication Code algorithm described
 * in FIPS81.
 *
 * @see javax.crypto.Mac
 *
 * @version 0.98, 98/07/01
 * @author Ming Yung
 */
public final class DESMAC extends MacSpi
{
  protected int macLength = 8;
  private Cipher cipher;
  private int count = 0;
  private byte outputBuffer[];

  //Given in number of bytes
  protected int engineGetMacLength()
  {
    return macLength;
  }

  protected void engineInit(Key key, AlgorithmParameterSpec params)
    throws InvalidKeyException, InvalidAlgorithmParameterException
  {
    try
    {
      cipher = Cipher.getInstance("DES/CBC/Zeroes");
      cipher.init(Cipher.ENCRYPT_MODE, key, params);
    }
    catch (NoSuchAlgorithmException e)
    {
      throw new RuntimeException("Internal error: " + e.getMessage());
    }
    catch (NoSuchPaddingException e)
    {
      throw new RuntimeException("Internal error: " + e.getMessage());
    }
  }

  protected void engineUpdate(byte input)
  {
    byte in[] = new byte[1];
    in[0] = input;
    engineUpdate(in, 0, 1);
  }

  protected void engineUpdate(byte[] input, int offset, int len)
  {
    outputBuffer = cipher.update(input, offset, len);
  }

  protected byte[] engineDoFinal()
  {
    try
    {
      //cipher.doFinal processes any buffered input + padding, if any
      //If there is no buffered input, padding is not needed &
      //cipher.doFinal does nothing. Otherwise, cipher.doFinal
      //processes precisely one block of data. Therefore extract
      //the mac from that processed block
      byte temp[] = cipher.doFinal();
      byte retval[] = new byte[macLength];
      if (temp.length == 0)
      {
        System.arraycopy(outputBuffer, outputBuffer.length - macLength, 
                         retval, 0, macLength);
        return retval;
      }
      else
      {
        System.arraycopy(temp, 0, retval, 0, macLength);
        return retval;
      }
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

  protected void engineDoFinal(byte output[], int outOffset)
  {
    try
    {
      byte mac[] = cipher.doFinal();
      System.arraycopy(mac, 0, output, outOffset, macLength);
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

  protected void engineReset()
  {
    outputBuffer = new byte[0];
  }

  public Object clone() throws CloneNotSupportedException
  {
    throw new CloneNotSupportedException("Cannot clone DESMAC");
  }

  private static final boolean DUMMY = Licensed.VALID;
}
