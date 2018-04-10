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

public class Base64OutputStream extends FilterOutputStream
{
  public static final int ENCODE = 0;
  public static final int DECODE = 1;
  private static final int DEFAULT_WIDTH = 16; /* measured as number of blocks */
  private static final char PAD = '=';

  private int width;
  private int mode;
  private int BLOCKSIZE;
  private byte[] buffer;  /* unprocessed data */
  private byte[] temp;    /* processed data */
  private int bufferLen;
  private byte[] buf = new byte[1];
  private int count = 0;
  private Base64 b64;
  
  public Base64OutputStream(OutputStream os)
  {
    this(ENCODE, DEFAULT_WIDTH, os);
  }

  public Base64OutputStream(int mode, OutputStream os)
  {
    this(mode, DEFAULT_WIDTH, os);
  }

  public Base64OutputStream(int mode, int width, OutputStream os)
  {
    super(os);
    this.mode = mode;
    this.width = width;

    if (mode == ENCODE)
    {
      b64 = new Base64Encoder();
      BLOCKSIZE = 3;
      buffer = new byte[BLOCKSIZE];
      temp = new byte[4];
    }
    else
    {
      b64 = new Base64Decoder();
      BLOCKSIZE = 4;
      buffer = new byte[BLOCKSIZE];
      temp = new byte[3];
    }
  }

  public void write(int b) throws IOException
  {
    buf[0] = (byte)(b & 0xff);
    write(buf);
  }

  public void write(byte[] data) throws IOException
  {
    write(data, 0, data.length);
  }

  public void write(byte[] data, int offset, int length) throws IOException
  {
    try
    {
      int off = offset;
      int rem = length;

      if (mode == DECODE)
      {
        while (true)
        {
          int b = data[off++];
          rem--;
          if (b != '\n' && b != '\r' && b != '\t' && b != ' ')
          {
            buffer[bufferLen++] = (byte)b;
          }  
  
          if (bufferLen == BLOCKSIZE)
          {
            if (buffer[BLOCKSIZE-1] == PAD)
              flush();
            else
            {
              b64.doBlock(buffer, 0, temp, 0); 
              out.write(temp, 0, b64.produced());
            }
  
            bufferLen = 0;
          }
          if (rem == 0) break;
        }
      }
      else
      {
        if (bufferLen + length >= BLOCKSIZE)
        {
          for (int i=0; i<(BLOCKSIZE-bufferLen); i++)
            buffer[bufferLen + i] = data[offset + i];
          b64.doBlock(buffer, 0, temp, 0); 
          writeBlock(temp);
        }
    
        off += (BLOCKSIZE - bufferLen);
        rem -= (BLOCKSIZE - bufferLen);
    
        while (true)
        {
          if (rem <= BLOCKSIZE)
            break;
  
          b64.doBlock(data, off, temp, 0);
  
          off += b64.consumed();
          rem -= b64.consumed();
          writeBlock(temp);
        }

        //buffer
        bufferLen = rem;
        if (bufferLen > 0)
          System.arraycopy(data, off, buffer, 0, rem);
      }
    }
    catch (Base64Exception e)
    {
      throw new IOException(e.toString());
    }
  }

  public void flush() throws IOException
  {
    try
    {
      if (bufferLen > 0)
      {
        b64.doFinal(buffer, 0, bufferLen, temp, 0);
        out.write(temp, 0, b64.produced());
        bufferLen -= b64.consumed(); 
      }

      super.flush();
    }
    catch (Base64Exception e)
    {
      throw new IOException(e.toString());
    }
  }

  private void writeBlock(byte[] b) throws IOException
  {
    out.write(b);
    if (mode == ENCODE)
    {
      if (count == width)
      {
        out.write('\n');
        count = 0;
      }
      else
        count++;
    }
  }
}
