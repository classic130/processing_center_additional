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

import java.io.FilterOutputStream;
import java.io.OutputStream;
import java.io.IOException;

/**
 * <p>A CipherOutputStream is composed of an OutputStream and a Cipher so 
 * that write() methods first process the data before writing them out 
 * to the underlying OutputStream.  The Cipher must be fully initialized 
 * before being used by a CipherOutputStream. 
 *
 * <p>For example, if the Cipher is initialized for encryption, the 
 * CipherOutputStream will attempt to encrypt data before writing out 
 * the encrypted data. 
 *
 * <p>This class adheres strictly to the semantics, especially the failure 
 * semantics, of its ancestor classes java.io.OutputStream and 
 * java.io.FilterOutputStream. This class has exactly those methods 
 * specified in its ancestor classes, and overrides them all. Moreover, 
 * this class catches all exceptions that are not thrown by its 
 * ancestor classes. 
 * 
 * <p>It is crucial for a programmer using this class not to use methods 
 * that are not defined or overridden in this class (such as a new method 
 * or constructor that is later added to one of the super classes), 
 * because the design and implementation of those methods are unlikely 
 * to have considered security impact with regard to CipherOutputStream. 
 *
 * @see java.io.OutputStream
 * @see java.io.FilterOutputStream
 * @see javax.crypto.Cipher
 * @see javax.crypto.CipherInputStream
 *
 * @version 0.98, 98/07/01
 * @author Ming Yung
 *
 */
public class CipherOutputStream extends FilterOutputStream
{
  private Cipher cipher;
  private byte[] buf = new byte[1];
  private byte[] buffer = new byte[0];

  /**
   * Constructs a CipherOutputStream from an OutputStream and a Cipher.
   */
  public CipherOutputStream(OutputStream os, Cipher c)
  {
    super(os);
    this.cipher = c;
  }

  /**
   * Constructs a CipherOutputStream from an OutputStream without specifying a
   * Cipher. This has the effect of constructing a CipherOutputStream using a
   * NullCipher.
   */
  protected CipherOutputStream(OutputStream os)
  {
    super(os);
    this.cipher = new NullCipher();
  }

  /**
   * Writes the specified byte to this output stream.
   *
   * @param b the byte.
   *
   * @exception java.io.IOException if an I/O error occurs.
   */
  public void write(int b) throws IOException
  {
     buf[0] = (byte)(b & 0xff);
     write(buf, 0, 1);
  }

  /**
   * Writes b.length bytes from the specified byte array to this output stream. 
   *
   * <p>The write method of CipherOutputStream calls the write method of three
   * arguments with the three arguments b, 0, and b.length.
   *
   * @param b the data.
   *
   * @exception java.io.IOException if an I/O error occurs.
   */
  public void write(byte[] b) throws IOException
  {
    write(b, 0, b.length);
  }

  /**
   * Writes len bytes from the specified byte array starting at offset off 
   * to this output stream.
   *
   * @param b the data.
   * @param off the start offset in the data.
   * @param len the number of bytes to write.
   *
   * @exception java.io.IOException if an I/O error occurs.
   */
  public void write(byte[] b, int off, int len) throws IOException
  {
    if (len <= 0) return;

    int bufLen = cipher.getOutputSize(len);
    if (buffer.length < bufLen)
      buffer = new byte[bufLen];

    try
    {
      int bytesUpdated = cipher.update(b, off, len, buffer, 0);
      out.write(buffer, 0, bytesUpdated); 
    }
    catch (ShortBufferException e)
    {
      throw new RuntimeException("Internal error: " + e.getMessage());
    }
  }

  /**
   * Flushes this output stream by forcing any buffered output bytes 
   * that have already been processed by the encapsulated Cipher object 
   * to be written out
   *
   * <p> Any bytes buffered by the encapsulated cipher and waiting to be
   *  processed by it will not be written out. For example, if the
   * encapsulated cipher is a block cipher, and the total number of
   * bytes written using one of the write methods is less than the
   * cipher's block size, no bytes will be written out.
   *
   * @exception java.io.IOException if an I/O error occurs.
   */
  public void flush() throws IOException
  {
    out.flush();
  }

  /**
   * Closes this output stream and releases any system resources associated 
   * with this stream. 
   *
   * <p> This method invokes the doFinal method of the encapsulated
   *  cipher object, which causes any bytes buffered by the
   *  encapsulated cipher to be processed. The result is written out
   *  by calling the flush method of this output stream.
   *
   * <p> This method resets the encapsulated cipher object to its
   * initial state and calls the close method of the underlying
   * output stream.
   *
   * @exception java.io.IOException if an I/O error occurs.
   */
  public void close() throws IOException
  {
    try
    {
      byte[] outBytes = this.cipher.doFinal();
      out.write(outBytes, 0, outBytes.length); 
      out.flush();
      out.close();
    }
    catch (BadPaddingException e)
    {
      throw new IOException("Bad padding encountered: " + e.getMessage());
    }
    catch (IllegalBlockSizeException e)
    {
      throw new IOException("Illegal block size: " + e.getMessage());
    }
  }
}
