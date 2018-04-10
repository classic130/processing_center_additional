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
import java.security.spec.AlgorithmParameterSpec;
import java.lang.IllegalStateException;

/**
 * The NullCipher class is a class that provides an "identity cipher" 
 * -- one that does not transform the plaintext. As a consequence, 
 * the ciphertext is identical to the plaintext. All initialization 
 * methods do nothing, while the blocksize is set to 1 byte. 
 *
 * @version 0.98, 98/07/01
 * @author Ming Yung
 *
 */
public class NullCipher extends Cipher
{
  private static final int UNINITIALIZED = 0;
  private int state = UNINITIALIZED;

  public NullCipher() 
  {
    super(null, null, null);
  }

  public void init(int opmode, Key key) 
    throws InvalidKeyException 
  {
    state = opmode;
    //Does nothing
  }

  public void init(int opmode, Key key, SecureRandom random) 
    throws InvalidKeyException 
  {
    state = opmode;
    //Does nothing
  }

  public void init(int opmode, Key key, AlgorithmParameterSpec params) 
    throws InvalidKeyException, InvalidAlgorithmParameterException 
  {
    state = opmode;
    //Does nothing
  }

  public void init(int opmode, Key key, AlgorithmParameterSpec params,
                   SecureRandom random) 
    throws InvalidKeyException, InvalidAlgorithmParameterException 
  {
    state = opmode;
    //Does nothing
  }

  public int getBlockSize() 
  {
    return 1;
  }

  public int getOutputSize(int inputLen) throws IllegalStateException
  {
    return inputLen;
  }

  public byte[] getIV() 
  {
    return new byte[0];
  }

  public byte[] update(byte input[]) throws IllegalStateException
  {
    if (state == UNINITIALIZED)
    {
      throw new IllegalStateException("Cipher not initialized");
    }

    return (byte[])input.clone();
  }

  public byte[] update(byte input[], int inputOffset, int inputLen) 
    throws IllegalStateException 
  {
    if (state == UNINITIALIZED)
    {
      throw new IllegalStateException("Cipher not initialized");
    }

    byte retval[] = new byte[inputLen];
    System.arraycopy(input, inputOffset, retval, 0, inputLen);
    return retval;
  }

  public int update(byte input[], int inputOffset,
                    int inputLen, byte output[]) 
    throws IllegalStateException, ShortBufferException 
  {
    return update(input, inputOffset, inputLen, output, 0);
  }

  public int update(byte input[], int inputOffset,
                    int inputLen, byte output[],
                    int outputOffset) 
    throws IllegalStateException, ShortBufferException 
  {
    if (state == UNINITIALIZED)
    {
      throw new IllegalStateException("Cipher not initialized");
    }

    if (output.length - outputOffset < inputLen)
    {
      throw new ShortBufferException("Buffer too short");
    }

    System.arraycopy(input, inputOffset, output, outputOffset, inputLen);
    return inputLen;
  }


  public byte[] doFinal() 
    throws IllegalStateException,
           IllegalBlockSizeException, BadPaddingException 
  {
    if (state == UNINITIALIZED)
    {
      throw new IllegalStateException("Cipher not initialized");
    }

    state = UNINITIALIZED;
    return new byte[0];
  }

  public byte[] doFinal(byte input[]) 
    throws IllegalStateException,
           IllegalBlockSizeException, BadPaddingException 
  {
    if (state == UNINITIALIZED)
    {
      throw new IllegalStateException("Cipher not initialized");
    }

    state = UNINITIALIZED;
    return (byte[])input.clone();
  }

  public int doFinal(byte output[], int outputOffset) 
     throws IllegalStateException,
            IllegalBlockSizeException, ShortBufferException,
            BadPaddingException 
  {
    if (state == UNINITIALIZED)
    {
      throw new IllegalStateException("Cipher not initialized");
    }

    state = UNINITIALIZED;
    return 0;
  }


  public byte[] doFinal(byte input[], int inputOffset,
                        int inputLen) 
    throws IllegalStateException,
           IllegalBlockSizeException, BadPaddingException 
  {
    if (state == UNINITIALIZED)
    {
      throw new IllegalStateException("Cipher not initialized");
    }

    byte retval[] = new byte[inputLen];
    System.arraycopy(input, inputOffset, retval, 0, inputLen);
    state = UNINITIALIZED;
    return retval;
  }


  public int doFinal(byte input[], int inputOffset,
                     int inputLen, byte output[]) 
    throws IllegalStateException,
           ShortBufferException, IllegalBlockSizeException,
           BadPaddingException 
  {
    return doFinal(input, inputOffset, inputLen, output, 0);
  }

  public int doFinal(byte input[], int inputOffset,
                     int inputLen, byte output[],
                     int outputOffset) 
    throws IllegalStateException,
           ShortBufferException, IllegalBlockSizeException,
           BadPaddingException 
  {
    if (state == UNINITIALIZED)
    {
      throw new IllegalStateException("Cipher not initialized");
    }

    if (output.length - outputOffset < inputLen)
    {
      throw new ShortBufferException("Buffer too short");
    }

    System.arraycopy(input, inputOffset, output, outputOffset, inputLen);
    state = UNINITIALIZED;
    return inputLen;
  }
}
