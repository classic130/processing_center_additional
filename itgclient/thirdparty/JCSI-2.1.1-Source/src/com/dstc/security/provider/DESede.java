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

/**
 * <p>Implements the Triple-DES or DESede cipher algorithm.
 *
 * @see com.dstc.security.provider.BlockCipher
 * @see javax.crypto.Cipher
 *
 * @version 0.98, 98/07/01
 * @author Ming Yung
 */
public final class DESede extends DES 
{
  private int[] encryptKeys1 = new int[32];
  private int[] decryptKeys1 = new int[32];
  private int[] encryptKeys2 = new int[32];
  private int[] decryptKeys2 = new int[32];
  private int[] encryptKeys3 = new int[32];
  private int[] decryptKeys3 = new int[32];

  public DESede() 
  {
    blockSize = 8;
  }

  protected void initialize(Key key, AlgorithmParameterSpec params)
    throws IllegalStateException, InvalidKeyException 
  {
    if (!key.getAlgorithm().equals("DESede") &&
         !key.getAlgorithm().equals("TripleDES") ) 
    {
      throw new InvalidKeyException ("Not a DESede Key");
    }

    // Set the key.
    byte keyBytes[] = key.getEncoded();

    // Have to tweak the parity bits so that each byte has odd parity.
    // This imposition of odd parity is required by the standard.
    forceOddParity (keyBytes);
      
    byte keyBlock[] = new byte[8];

    System.arraycopy(keyBytes, 0, keyBlock, 0, 8);
    deskey(keyBlock, true, encryptKeys1);
    deskey(keyBlock, false, decryptKeys1);

    System.arraycopy(keyBytes, 8, keyBlock, 0, 8);
    deskey(keyBlock, true, encryptKeys2);
    deskey(keyBlock, false, decryptKeys2);

    System.arraycopy(keyBytes, 16, keyBlock, 0, 8);
    deskey(keyBlock, true, encryptKeys3);
    deskey(keyBlock, false, decryptKeys3);
  }

  protected void encryptBlock(byte inBytes[], byte outBytes[]) 
  {
    des(inBytes, outBytes, encryptKeys1);
    des(outBytes, outBytes, decryptKeys2);
    des(outBytes, outBytes, encryptKeys3);
  }

  protected void decryptBlock(byte inBytes[], byte outBytes[]) 
  {
    des(inBytes, outBytes, decryptKeys3);
    des(outBytes, outBytes, encryptKeys2);
    des(outBytes, outBytes, decryptKeys1);
  }
}

