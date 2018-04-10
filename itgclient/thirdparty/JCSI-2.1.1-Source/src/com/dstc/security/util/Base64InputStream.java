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

package com.dstc.security.util;

import java.io.*;

public class Base64InputStream extends FilterInputStream
{
  public static final int ENCODE = 0;
  public static final int DECODE = 1;
  private static final char PAD = '=';

  private Base64 b64;
  private int mode;
  private int BLOCKSIZE;
  private byte[] buffer;  /* processed data, offset 
                          = bufferOff, length = bufferLen */
  private byte[] temp;      /* unprocessed data, 2 blocks*/
  private byte[] buf = new byte[1];
  private int bufferOff;
  private int bufferLen;
  private int tempLen;  
  private boolean firstRun = true;
  private boolean eof;
  private int ind1,ind2, dummy; /* ind1 & ind2 are indices 
                                   into the 2 temp blocks */

  public Base64InputStream(InputStream is)
  {
    this(DECODE, is);
  }

  public Base64InputStream(int mode, InputStream is)
  {
    super(is);
    this.mode = mode;

    if (mode == DECODE)
    {
      b64 = new Base64Decoder();
      BLOCKSIZE = 4;
      temp = new byte[2*BLOCKSIZE];
      buffer = new byte[3];
    }
    else
    {
      b64 = new Base64Encoder();
      BLOCKSIZE = 3;
      temp = new byte[2*BLOCKSIZE];
      buffer = new byte[4];
    }
  }

  public int available() throws IOException
  {
    return 0;
  }

  public int read() throws IOException
  {
    while (true)
    {
      int bytesRead = read(buf, 0, 1);

      if (bytesRead == -1)
        return -1;

      if (bytesRead == 1)
        return (buf[0] & 0xff);
    }
  }

  public int read(byte[] b) throws IOException
  {
    return read(b, 0, b.length);
  }

  public int read(byte[] b, int offset, int length) throws IOException
  {
    if (firstRun)
    {
      readBlock(temp, 0, BLOCKSIZE);
      firstRun = false;
      ind1 = BLOCKSIZE;
      ind2 = 0;
      tempLen = BLOCKSIZE;
    }

    if (eof && (bufferLen == 0))
      return -1;

    //enough buffered data to satisfy request
    if (length <= bufferLen)
    {
      System.arraycopy(buffer, bufferOff, b, offset, length);
      bufferOff += length;
      bufferLen -= length;
      return length;
    }

    //flush buffer
    System.arraycopy(buffer, bufferOff, b, offset, bufferLen);

    int rem = length - bufferLen;
    int off = offset + bufferLen;
    bufferOff = 0;
    bufferLen = 0;

    if (eof)
      return (length - rem);

    try
    {
      while (true)
      {
        int rd = readBlock(temp, ind1, BLOCKSIZE);
  
        if (rd == BLOCKSIZE)
        {
          tempLen = rd;
  
          if (rem < BLOCKSIZE)
          {
            //buffer data
            b64.doBlock(temp, ind2, buffer, bufferOff);
            bufferLen = b64.produced();
            dummy = ind1;
            ind1 = ind2;
            ind2 = dummy;
            return (length - rem);
          }
  
          b64.doBlock(temp, ind2, b, off);
          rem -= b64.produced();
          off += b64.produced();
          dummy = ind1;
          ind1 = ind2;
          ind2 = dummy;
        }
        else if (rd == -1)
        {
          eof = true;
  
          if (mode == DECODE)
          {
            b64.doFinal(temp, ind2, tempLen, buffer, bufferOff);
            bufferLen = b64.produced();
          }
          else
          {
            b64.doBlock(temp, ind2, b, off);
            rem -= b64.produced();
            off += b64.produced();
            b64.doFinal(temp, ind1, tempLen, buffer, bufferOff);
            bufferLen = b64.produced();
          }
          if (bufferLen <= rem)
          {
            System.arraycopy(buffer, bufferOff, b, off, bufferLen);
            rem -= bufferLen;
            bufferLen = 0;
            return (length - rem);
          }
          else
            return (length - rem);
        }
        else
        {
          tempLen = rd;
        }
      }
    }
    catch (Base64Exception e)
    {
      throw new IOException(e.toString());
    }
  }

  /** 
   * Tries to read blocksize bytes fully. Blocks if block is not filled and
   * eof is not reached. If eof is reached and the block is partially filled
   * the number of bytes filled is returned. If eof is reached and the block
   * is empty, -1 is returned.
   */ 
  private int readBlock(byte[] b, int offset, int blockSize) throws IOException
  {
    int rd;
    int off = offset;
    while (true)
    {
      rd = in.read();
      if (rd != -1)
      {
        if (mode == DECODE)
        {
          if (rd != '\n' && rd != '\r' && rd != ' ' && rd != '\t')
            b[off++] = (byte)(rd & 0xff);
        }
        else
          b[off++] = (byte)(rd & 0xff);
      }
      else
      {
        if (off == offset)
          return -1;
        else
          return (off - offset);
      }
      if (off - offset == blockSize)
        return blockSize;
    }
  }
}
