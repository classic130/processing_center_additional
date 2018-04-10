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

import java.io.FilterInputStream;
import java.io.InputStream;
import java.io.IOException;

/**
 * <p>A CipherInputStream is composed of an InputStream and a Cipher so 
 * that read() methods return data that are read in from the underlying 
 * InputStream but have been additionally processed by the Cipher. The 
 * Cipher must be fully initialized before being used by a CipherInputStream. 
 *
 * <p>For example, if the Cipher is initialized for decryption, the 
 * CipherInputStream will attempt to read in data and decrypt them, 
 * before returning the decrypted data. 
 *
 * <p>This class adheres strictly to the semantics, especially the failure 
 * semantics, of its ancestor classes java.io.FilterInputStream and 
 * java.io.InputStream. This class has exactly those methods specified in 
 * its ancestor classes, and overrides them all. Moreover, this class
 * catches all exceptions that are not thrown by its ancestor classes. 
 * In particular, the skip(long) method skips only data that have been 
 * processed by the Cipher. 
 *
 * <p>It is crucial for a programmer using this class not to use methods that 
 * are not defined or overridden in this class (such as a new method or c
 * onstructor that is later added to one of the super classes), because 
 * the design and implementation of those methods are unlikely to have 
 * considered security impact with regard to CipherInputStream. 
 *
 * @see java.io.InputStream
 * @see java.io.FilterInputStream
 * @see javax.crypto.Cipher
 * @see javax.crypto.CipherOutputStream
 *
 * @version 0.98, 98/07/01
 * @author Ming Yung
 *
 */
public class CipherInputStream extends FilterInputStream
{ 
  private Cipher cipher;
  private byte[] buffer;
  private int blockSize;
  private int bufferStart = 0;
  private int bufferLen = 0;
  private boolean eof =false;
  private byte[] buf;
  private byte[] cipherText;
  private byte[] temp;

  /** 
   * Constructs a CipherInputStream from an InputStream and a Cipher.
   */
  public CipherInputStream(InputStream is, Cipher c)
  {
    super(is);
    this.cipher = c;
    this.blockSize = c.getBlockSize();
    this.buffer = new byte[blockSize];
    this.buf = new byte[blockSize];
  }

  /**
   * Constructs a CipherInputStream from an InputStream without 
   * specifying a Cipher.  This has the effect of constructing a 
   * CipherInputStream using a NullCipher
   */
  protected CipherInputStream(InputStream is)
  {
    super(is);
    this.cipher = new NullCipher();
    this.blockSize = this.cipher.getBlockSize();
    this.buffer = new byte[blockSize];
    this.buf = new byte[blockSize];
  }

  /**
   * Reads the next byte of data from this input stream. The value byte 
   * is returned as an int in the range 0 to 255. If no byte is available 
   * because the end of the stream has been reached, the value -1 is 
   * returned. This method blocks until input data is available, the end 
   * of the stream is detected, or an exception is thrown. 
   *
   * @return the next byte of data, or -1 if the end of the stream is
   * reached.
   *
   * @exception java.io.IOException if an I/O error occurs.
   */
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

  /**
   * Reads up to b.length bytes of data from this input stream into an 
   * array of bytes. 
   *
   * <p>The read method of InputStream calls the read method of three 
   * arguments with the arguments b, 0, and b.length.
   *
   * @params b the buffer into which the data is read.
   *
   * @return the total number of bytes read into the buffer, or -1 is
   * there is no more data because the end of the stream has
   * been reached.
   *
   * @exception java.io.IOException if an I/O error occurs.
   */
  public int read(byte[] b) throws IOException
  {
    return read(b, 0, b.length);
  }

  /**
   * Reads up to len bytes of data from this input stream into an array 
   * of bytes. This method blocks until some input is available. If the 
   * first argument is null, up to len bytes are read and discarded.
   *
   * @param b the buffer into which the data is read.
   * @param off the start offset of the data.
   * @param len the maximum number of bytes read.
   *
   * @return the total number of bytes read into the buffer, or -1 if
   * there is no more data because the end of the stream has been reached.
   *
   * @exception java.io.IOException if an I/O error occurs.
   */
  public int read(byte[] b, int off, int len) throws IOException,
                  NullPointerException,IndexOutOfBoundsException
  {
    if (b == null) {
        throw new NullPointerException();
    }
    if (len == 0) {
        return 0;
    }
    if ((len < 0) || (off < 0) || ((off+len) > b.length)) {
        throw new IndexOutOfBoundsException();
    }

    if (eof && (bufferLen == 0)) {
        return -1;
    }

    int retval = 0;

    if (len <= bufferLen) 
    {
      System.arraycopy(buffer, bufferStart, b, off, len);
      retval += len;

      bufferStart += len;
      bufferLen -= len;
      return retval;
    }

    System.arraycopy(buffer, bufferStart, b, off, bufferLen);
    retval += bufferLen;

    off += bufferLen;
    len -= bufferLen;
    bufferStart = 0;
    bufferLen = 0;

    if (eof) 
    {
      return retval;
    }

    int more = 0;
    
    //block until eof or we have something to return
    while (more == 0 && !eof)
    {
      more += processMore(b, off, len);
    }

    if (eof && (retval + more == 0))
    {
      return -1;
    }
    else
    {
      return retval + more;
    }
  }

  private int processMore(byte[] b, int off, int len)
    throws IOException
  {
    int retval = 0;

    try
    {
      if (cipherText == null || cipherText.length < len)
      {
        cipherText = new byte[len];
      }

      int bytesRead = in.read(cipherText, 0, len);

      if (bytesRead == -1)
      {
        eof = true;
        int more = cipher.doFinal(buf, 0);

        if (len < more)
        {
          System.arraycopy(buf, 0, b, off, len);
          retval += len;

          //Put the rest into buffer
          bufferLen = more - len;
          System.arraycopy(buf, len, buffer, 0, bufferLen);
          return retval;
        }
        else
        {
          System.arraycopy(buf, 0, b, off, more);
          retval += more;

          return retval;
        }
      }

      int outSize = cipher.getOutputSize(bytesRead);
      if (temp == null || temp.length < outSize)
      {
        temp = new byte[outSize];
      }

      int bytesUpdated = cipher.update(cipherText, 0, bytesRead, temp, 0);

      if (len < bytesUpdated)
      {
        System.arraycopy(temp, 0, b, off, len);
        retval += len;

        //Put the rest into buffer
        bufferLen = bytesUpdated - len;
        System.arraycopy(temp, len, buffer, 0, bufferLen);

        return retval;
      }
      else
      {
        System.arraycopy(temp, 0, b, off, bytesUpdated);
        retval += bytesUpdated;

        bufferLen = 0;
        return retval;
      }
    }
    catch (java.lang.IllegalStateException e)
    {
      throw new IOException("Cipher in wrong state");
    }
    catch (ShortBufferException e)
    {
      throw new IOException(e.toString());
    }
    catch (IllegalBlockSizeException e)
    {
      throw new IOException(e.toString());
    }
    catch (BadPaddingException e)
    {
      throw new IOException(e.toString());
    }
  }

  /**
   * Skips over and discards n bytes of data from this input stream. 
   * The skip method may, for a variety of reasons, end up skipping over 
   * some smaller number of bytes, possibly 0. The actual number of 
   * bytes skipped is returned.
   *
   * @param n the number of bytes to be skipped.
   * 
   * @return the actual number of bytes skipped.
   *
   * @exception java.io.IOException if an I/O error occurs.
   */
  public long skip(long n) throws IOException
  {
    // XX - hypothetical bug if ((int)n) < 0, i.e. bit 31 == 1
    byte[] tmp = new byte[(int) n];     // garbage buffer
    return read(tmp, 0, (int) n);
  }

  /**
   * Returns the number of bytes that can be read from this input stream 
   * without blocking. The available method of InputStream returns 0. 
   * This method should be overridden by subclasses
   *
   * @return the number of bytes that can be read from this input
   * stream without blocking.
   *
   * @exception java.io.IOException if an I/O error occurs.
   */
  public int available() throws IOException
  {
    try
    {
      return (cipher.getOutputSize(in.available()) + bufferLen);
    }
    catch (java.lang.IllegalStateException e)
    {
      //cipher not yet initialized
      return 0;
    }
  }

  /**
   * Closes this input stream and releases any system resources associated 
   * with the stream. 
   *
   * @exception java.io.IOException if an I/O error occurs.
   */
  public void close() throws IOException
  {
    in.close();
  }

  /**
   * Tests if this input stream supports the mark and reset methods, 
   * which it does not.
   *
   * @return false, since this class does not support the mark and
   * reset methods.
   */
  public boolean markSupported()
  {
    return false;
  }
}
