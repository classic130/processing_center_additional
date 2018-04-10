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

import java.security.*;
import java.security.spec.AlgorithmParameterSpec;
import javax.crypto.*;
import javax.crypto.spec.IvParameterSpec;

/**
 * <p>An abstract class representing a Block Cipher.
 *
 * <p>Three modes are defined: ECB, CBC and CFB
 *
 * <p>Three padding mechanisms are defined: No Padding, PKCS#5 and Padding
 * with zeros as described in FIPS81 for DES-MAC
 *
 * @see javax.crypto.Cipher
 *
 * @version 0.98, 98/07/01
 * @author Ming Yung
 */
abstract class BlockCipher extends CipherSpi
{
  private final static int MODE_ECB = 0x00;
  private final static int MODE_CBC = 0x01;
  private final static int MODE_CFB = 0x02;

  protected int blockSize;
  protected byte IV[] = null;
  protected byte inputBuffer[];
  protected byte chainBlock[];
  protected AlgorithmParameters algParams = null;
  protected int inputBufferOffset;
  protected int inputBufferLen;

  protected int state;
  private int mode = MODE_CBC; //Default
  private SecureRandom rand;
  private Padding pad = new PKCS5Padding(); //Default
  private int paddingType = 0;
  private boolean needIV = false;
  private byte[] tempBlock;

  protected void engineSetPadding(String padding) 
    throws NoSuchPaddingException 
  {
    if (padding.equals("PKCS5Padding"))
    {
      this.pad = new PKCS5Padding();
      this.paddingType = 1;
    }
    else if (padding.equals("NoPadding"))
    {
      this.pad = new Padding();
    }
    else if (padding.equals("Zeroes"))
    {
      this.pad = new Zeroes();
      this.paddingType = 1;
    }
    else
    {
      throw new NoSuchPaddingException(padding + " Not supported");
    }
  }

  protected void engineSetMode(String mode) 
    throws NoSuchAlgorithmException 
  {
    if (mode.equals("CBC"))
    {
      this.mode = MODE_CBC;
      this.needIV = true;
    }
    else if (mode.equals("ECB"))
    {
      this.mode = MODE_ECB;
    }
    else if (mode.equals("CFB"))
    {
      this.mode = MODE_CFB;
      this.needIV = true;
    }
    else
    {
      throw new NoSuchAlgorithmException(mode + " Not supported");
    }
  }

  protected int engineGetBlockSize() 
  {
    return blockSize;
  }

  protected int engineGetOutputSize(int inputLen) 
  {
    // Include buffered input
    int outSize = inputLen + inputBufferOffset;
    if (this.state == Cipher.ENCRYPT_MODE)
      // Include padding
      outSize += blockSize - (outSize % blockSize);
 
    return outSize;
  }

  protected byte[] engineGetIV() 
  {
    return IV;
  }

  protected AlgorithmParameters engineGetParameters()
  {
    return algParams;
  }

  ///////////////////////////////////////////////////////////////////////////
  // To be implemented in a subclass for each algorithm 
  ///////////////////////////////////////////////////////////////////////////
  
  protected abstract void initialize(Key key, AlgorithmParameterSpec params)
    throws IllegalStateException, InvalidKeyException;

  protected abstract void encryptBlock(byte in[], byte out[]); 

  protected abstract void decryptBlock(byte in[], byte out[]);

  protected void engineInit(int opmode, Key key, SecureRandom random) 
    throws InvalidKeyException 
  {
    this.state = opmode;
    this.rand = random;

    if (this.needIV)
    {
      this.IV = new byte[blockSize];
      this.rand.nextBytes(IV);
    }

    initialize(key, null);
    reset();
  }

  ///////////////////////////////////////////////////////////////////////////

  protected void engineInit(int opmode, Key key,
                            AlgorithmParameterSpec params,
                            SecureRandom random) 
    throws InvalidKeyException, InvalidAlgorithmParameterException 
  {
    this.state = opmode;
    this.rand = random;

    if (params instanceof IvParameterSpec)
    {
      this.IV = ((IvParameterSpec)params).getIV();

      initialize(key, null);
      reset();
      return;
    }
    else
    {
      initialize(key, params);
      reset();
    }
  }

  protected void engineInit(int opmode, Key key,
                            AlgorithmParameters params,
                            SecureRandom random) 
    throws InvalidKeyException, InvalidAlgorithmParameterException 
  {
    this.state = opmode;
    this.rand = random;

    initialize(key, null);
    reset();
  }

  protected byte[] engineUpdate(byte input[], int inputOffset, int inputLen) 
  {
    try
    {
      byte output[] = new byte[engineGetOutputSize(inputLen)];
      int done = engineUpdate(input, inputOffset, inputLen, output, 0);
      byte retval[] = new byte[done];
      System.arraycopy(output, 0, retval, 0, done);
      return retval;
    }
    catch (ShortBufferException e)
    {
      throw new RuntimeException("Internal error: " + e.getMessage());
    }
  }
 
  protected int engineUpdate(byte input[], int inputOffset, int inputLen, 
                             byte output[], int outputOffset) 
    throws ShortBufferException 
  {
    if (input == null)
    {
      return 0;
    }

    int bufferFillRequired;
    int remaining;
    int consumed = 0;
    int retval = 0;

    if (state == Cipher.ENCRYPT_MODE) 
    {
      while (true) 
      {
        bufferFillRequired = blockSize - inputBufferOffset;
        remaining = inputLen - consumed;

        if (bufferFillRequired <= remaining) 
        {
          //Enough input for a block
          System.arraycopy(input, consumed + inputOffset, inputBuffer, 
                           inputBufferOffset, bufferFillRequired);

          if (mode == MODE_CBC)
          {
            for (int i=0; i< blockSize; i++) 
            {
              inputBuffer[i] ^= chainBlock[i];
            }
            encryptBlock(inputBuffer, chainBlock);
            System.arraycopy(chainBlock, 0, output, 
                             retval + outputOffset, blockSize);
          }
          else if (mode == MODE_ECB)
          {
            encryptBlock(inputBuffer, chainBlock);
            System.arraycopy(chainBlock, 0, output, 
                             retval + outputOffset, blockSize);
          }
          else if (mode == MODE_CFB)
          {
            encryptBlock(chainBlock, tempBlock);
            for (int i=0; i< blockSize; i++) 
            {
              chainBlock[i] = (byte)(inputBuffer[i] ^ tempBlock[i]);
            }
            System.arraycopy(chainBlock, 0, output, 
                             retval + outputOffset, blockSize);
          }

          inputBufferOffset = 0;
          consumed += bufferFillRequired;
          retval += blockSize;
        } 
        else 
        {
          //Buffer the remaining input
          System.arraycopy(input, consumed + inputOffset, inputBuffer, 
                            inputBufferOffset, remaining);
          inputBufferOffset += remaining;
          break;
        }
      }
      return retval;
    } 
    else if (state == Cipher.DECRYPT_MODE) 
    {
      while (true) 
      {
        bufferFillRequired = blockSize - inputBufferOffset ;
        remaining =  inputLen - consumed;

        if (remaining - bufferFillRequired >= paddingType)  //for NoPadding
        {
          //Enough input for block
          //Always leave something for the buffer
          System.arraycopy(input, consumed + inputOffset, inputBuffer, 
                           inputBufferOffset, bufferFillRequired);

          if (mode == MODE_CBC)
          {
            decryptBlock(inputBuffer, tempBlock);

            for (int i=0; i< blockSize; i++) 
            {
              output[i + retval + outputOffset] = (byte)(chainBlock[i] ^ 
                                                     tempBlock[i]);
            }
            System.arraycopy(inputBuffer, 0, chainBlock, 0, blockSize);
          }
          else if (mode == MODE_ECB)
          {
            decryptBlock(inputBuffer, tempBlock);

            System.arraycopy(tempBlock, 0, output, retval + outputOffset,
                             blockSize);
          }
          else if (mode == MODE_CFB)
          {
            encryptBlock(chainBlock, tempBlock);

            for (int i=0; i< blockSize; i++) 
            {
              output[i + retval + outputOffset] = (byte)(inputBuffer[i] ^ 
                                                    tempBlock[i]);
            }
            System.arraycopy(inputBuffer, 0, chainBlock, 0, blockSize);
          }

          inputBufferOffset = 0;
          consumed += bufferFillRequired;
          retval += blockSize;
        } 
        else 
        {
          //Buffer the remaining input
          System.arraycopy(input, consumed + inputOffset, inputBuffer, 
                           inputBufferOffset, remaining);
          inputBufferOffset += remaining;
          break;
        }
      }
      //returns number of bytes stored in output
      return retval;
    }
    else return 0;
  }

  protected byte[] engineDoFinal(byte input[], int inputOffset, int inputLen) 
    throws IllegalBlockSizeException, BadPaddingException 
  {
    try
    {
      byte output[] = new byte[engineGetOutputSize(inputLen)];
      int done = engineDoFinal(input, inputOffset, inputLen, output, 0);
      byte retval[] = new byte[done];
      System.arraycopy(output, 0, retval, 0, done);
      return retval;
    }
    catch (ShortBufferException e)
    {
      throw new RuntimeException("Internal error: " + e.getMessage());
    }
  }

  protected int engineDoFinal(byte input[], int inputOffset,
                              int inputLen, byte output[],
                              int outputOffset) 
    throws ShortBufferException, 
           IllegalBlockSizeException, BadPaddingException 
  {
    int produced 
      = engineUpdate(input, inputOffset, inputLen, output, outputOffset);

    if (state == Cipher.ENCRYPT_MODE) 
    {
      if(!(pad.doPadding()))
      {
        reset();
        return produced;
      }

      if (mode == MODE_CBC)
      {
        for (int i=0; i< blockSize; i++) 
        {
          inputBuffer[i] ^= chainBlock[i];
        }
      }
      else if (mode == MODE_ECB)
      {
      }
      else if (mode == MODE_CFB)
      {
        //TODO
      }

      encryptBlock(inputBuffer, chainBlock);
      System.arraycopy(chainBlock, 0, output, 
                        produced + outputOffset, blockSize);

      reset();
      return (produced + blockSize);
    } 
    else if (state == Cipher.DECRYPT_MODE) 
    {
      if (inputBufferOffset == 0)
      {
        reset();
        return produced;
      }

      if (inputBufferOffset != blockSize) 
      {
        throw new IllegalBlockSizeException
          ("CipherText length not a multiple of blockSize");
      }

      decryptBlock(inputBuffer, tempBlock);

      if (mode == MODE_CBC)
      {
        for (int i=0; i< blockSize; i++) 
        {
          tempBlock[i] ^= chainBlock[i];
        }
      }
      else if (mode == MODE_ECB)
      {
      }
      else if (mode == MODE_CFB)
      {
        //TODO
      }

      int dataSize = pad.doUnPadding(tempBlock);
      System.arraycopy(tempBlock, 0, output, outputOffset + produced, 
                       dataSize);

      reset();

      //returns number of bytes stored in output
      return (produced + dataSize);
    }
    else 
      throw new RuntimeException("Unknown cipher state " + state);
  }

  private void reset () 
  {
    tempBlock = new byte[blockSize];
    inputBuffer = new byte[blockSize];
    inputBufferOffset = 0;
    inputBufferLen = 0;
    if (this.needIV)
      chainBlock = (byte[])(IV.clone());
    else
      chainBlock = new byte[blockSize];
  }

  /**
   * <p>An inner class for the padding mechanism in PKCS#5.
   *
   * <p>It pads with a common byte up to the block boundary. The value
   * of the padding byte is precisely the number of padding bytes.
   * Padding is always done, even if the plainText size is a multiple of
   * the block size. Un-padding is therefore unambiguous.
   */
  protected class PKCS5Padding extends Padding
  {
    protected boolean doPadding()
    {
      //Always pad with something
      int extra = (inputBufferOffset != 0) ?
        blockSize - inputBufferOffset : blockSize;

      for (int i=0; i<extra; i++)
      {
        inputBuffer[inputBufferOffset + i] = (byte)extra;
      }

      return true;
    }

    //Returns number of data bytes in buffer after unpadding
    protected int doUnPadding(byte buffer[])
      throws BadPaddingException
    {
      //Just peek at the last byte
      int numPad = buffer[buffer.length - 1];

      if ((numPad < 1) || (numPad > blockSize))
        throw new BadPaddingException
          ("Expected PKCS5 but not encountered");

      return (blockSize - numPad);
    }
  }

  /**
   * <p>An inner class which pads with zeros up to the block boundary.
   * 
   * <p>No un-padding is defined as it is ambiguous.
   */
  protected class Zeroes extends Padding
  {
    //Only pad if not at block boundary
    //Exit if buffer is empty 
    protected boolean doPadding()
      throws IllegalBlockSizeException
    {
      if (inputBufferOffset == 0) return false;

      int extra = (inputBufferOffset != 0) ?
        blockSize - inputBufferOffset : 0;

      for (int i=0; i<extra; i++)
      {
        inputBuffer[inputBufferOffset + i] = (byte)0x00;
      }
      return true;
    }
  }

  /**
   * <p>An inner class representing (absence of) padding mechanism.
   */
  protected class Padding
  {
    protected boolean doPadding()
      throws IllegalBlockSizeException
    {
      if(inputBufferOffset != 0)
        throw new IllegalBlockSizeException("Needs padding");

      //Don't pad
      return false;
    }

    protected int doUnPadding(byte buffer[])
      throws BadPaddingException
    {
      //Don't unpad
      return blockSize;
    }
  }

  private static final boolean DUMMY = Licensed.VALID;
}
