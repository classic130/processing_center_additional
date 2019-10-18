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

package com.dstc.security.x509;

import java.util.Vector;
import java.util.Iterator;
import java.util.Collection;
import java.util.Arrays;
import java.io.InputStream;
import java.io.DataInputStream;
import java.io.FilterInputStream;
import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.PushbackInputStream;
import java.io.IOException;
import java.security.cert.CRL;
import java.security.cert.CRLException;
import java.security.cert.Certificate;
import java.security.cert.CertificateEncodingException;
import java.security.cert.CertificateException;
import java.security.cert.CertificateFactorySpi;

import com.dstc.security.util.Base64InputStream;
import com.dstc.security.util.Base64OutputStream;
import com.dstc.security.util.DegeneratePKCS7;
import com.dstc.security.common.OID;
import com.dstc.security.asn1.Asn1;
import com.dstc.security.asn1.Asn1Exception;

public class X509CertificateFactory extends CertificateFactorySpi
{
  private static final byte[] HEADER = "-----BEGIN CERTIFICATE-----".getBytes();
  private static final byte[] FOOTER = ("-----END CERTIFICATE-----" + 
         System.getProperty("line.separator")).getBytes();
  private static final byte[] HEADER7 = "-----BEGIN PKCS7-----".getBytes();
  private static final byte[] FOOTER7 = ("-----END PKCS7-----" +
         System.getProperty("line.separator")).getBytes();

  public Certificate engineGenerateCertificate(InputStream inStream)
    throws CertificateException
  {
    InputStream is = null;
    boolean notDER;

    is = isBase64(inStream, HEADER, FOOTER);

    try
    {
        return new X509Certificate(is);
    }
    catch (Exception e)
    {
      throw new CertificateEncodingException(e.getMessage());
    }
  }

  public Collection engineGenerateCertificates(InputStream inStream)
      throws CertificateException
  {
    try
    {
      PushbackInputStream pis = new PushbackInputStream(inStream, 129);
      byte[] buf = new byte[129];    
      boolean isBase64 = false;
      Vector vec = new Vector();

      buf[0] = (byte) (pis.read() & 0xff);    // read 1st byte

      if (buf[0] == HEADER[0]) {             // if Base64 encoded
          for (int j=0; j<11; j++) {
               buf[j+1] = (byte) pis.read();
          }
          if (buf[11]== ((int) 'P')) {         // PKCS7 format
              int len = getNonZero(buf); 
              pis.unread(buf, 0, len);
              InputStream iss = isBase64(pis, HEADER7, FOOTER7);

              DegeneratePKCS7 deg = new DegeneratePKCS7(iss);
              return deg.getCertificates(); 
          }
          else {                              // sequence of x509's
              int len = getNonZero(buf); 
              pis.unread(buf, 0, len);

              InputStream bais = makeAvailableStream(pis);
              while (bais.available() >0) {
                  vec.add(this.engineGenerateCertificate(bais));
              }
              return vec;
          }
      }
      else {                            // binary encoding
          pis.unread(buf[0]);
          boolean x509Bool = isX509orPKCS7(buf, pis);
          int len = getNonZero(buf);      // this should be correct since we
          pis.unread(buf, 0, len);        // assume DER encoding. i.e. all 
                                          // length octets != 0

          if ( x509Bool ) {                      // x.509 format
              InputStream bais = makeAvailableStream(pis);
              while (bais.available() >0) {
                  vec.add(new X509Certificate(bais));
              }
              return vec;

          }
          else {                                 // PKCS7 format
              DegeneratePKCS7 degen = new DegeneratePKCS7(pis);
              return degen.getCertificates();
          }
       }
    }
    catch (Asn1Exception e)
    {
      throw new CertificateException(e.toString());
    }
    catch (IOException e)
    {
      throw new CertificateException(e.toString());
    }
    catch (CRLException e)     
    {
      throw new CertificateException(e.toString());
    }
  }

  public CRL engineGenerateCRL(InputStream inStream)
      throws CRLException
  {
    try
    {
      return new X509CRL(inStream);
    }
    catch (Asn1Exception e)
    {
      throw new CRLException(e.toString()); 
    }
    catch (IOException e)
    {
      throw new CRLException(e.toString()); 
    }
  }

  public Collection engineGenerateCRLs(InputStream inStream)
      throws CRLException
  {
      PushbackInputStream pis = new PushbackInputStream(inStream, 129);
      byte[] buf = new byte[129];    
      Vector vec = new Vector();
    try
    {
        boolean bl = isX509orPKCS7(buf, pis);
        int len = getNonZero(buf);
        pis.unread(buf, 0, len);

        if (bl) {                                // x.509 sequence
            InputStream bais = makeAvailableStream(pis);
            while (bais.available() > 0 )  {
                vec.add(new X509CRL(bais));
            }
            return vec;
        }
        else {                                  // PKCS7 format
            DegeneratePKCS7 degen = new DegeneratePKCS7(pis);
            return degen.getCRLs();
        }
    }
    catch (Asn1Exception e)
    {
      throw new CRLException(e.toString());
    }
    catch (IOException e)
    {
      throw new CRLException(e.toString());
    }
    catch (CertificateException e)  
    {
      throw new CRLException(e.toString());
    }
  }

  // Helper method
  //
 private static boolean isX509orPKCS7(byte[] buf,
                       PushbackInputStream pis2) 
         throws CertificateException {
    boolean b = false;
    int len = 0;
    try {
      buf[0] = (byte) (pis2.read() & 0xff);   
      buf[1] = (byte) (pis2.read() & 0xff);  // 1st length octet
      if ((buf[1] & 0x80) != 0) {           // if long-form
          len = buf[1] & 0x7f;        // no. of additional length octets  
          int r = 2;
          while (true)
          {
            if (r == len+2) break;
            buf[r++] = (byte) (pis2.read() & 0xff);
          }
      }
      buf[len+2] = (byte) (pis2.read() & 0xff);  // crucial byte

      if (buf[len+2] == 0x30) {
          b = true;                  // x.509
      }
      else if (buf[len+2] == 0x06) {
          b = false;                  // pkcs7
      }
      else {
          throw new CertificateException("Unrecognized Format");
      }
    }
    catch (IOException e) {
        throw new CertificateException("Encoding error");
    }

      return b;

 }  // end helper

  // get the number of non-zero elements of an array
  //
  private static int getNonZero(byte[] b) {
      int retval;
      int i;
      for (i= b.length-1; i >=0 ; i--) {
          if (b[i] != 0) break;
      }
      return i+1;
  }
          
  // Returns input stream wrapped in Base64InputStream if Base-64 encoded
  // (after stripping headers) otherwise returns input stream wrapped in BAOS
  //
  private static InputStream isBase64(InputStream inStream,
          byte[] header, byte[] footer) throws CertificateException {

    boolean notDER2;
    InputStream is;
  
    if (inStream.markSupported())
    {
      inStream.mark(10);
    }

    try
    {
      ByteArrayOutputStream baos = new ByteArrayOutputStream();

      //test first byte to see if base64 encoded
      int b;
      if ((b = inStream.read()) == -1)
        throw new CertificateEncodingException("Unexpected end of stream");    

      if (b == header[0])
      {
        notDER2 = true;
        for (int j=1; j<header.length; j++)
        {
          if ((b = inStream.read()) == -1)
            throw new CertificateEncodingException("Unexpected end of stream");    
          if (b != header[j])
            throw new CertificateEncodingException("Bad header");    
        }

        while (true)
        {
          if ((b = inStream.read()) == -1)
            throw new CertificateEncodingException("Unexpected end of stream");    
          if (b == footer[0])
          {
            for (int j=1; j<footer.length; j++)
            {
              if ((b = inStream.read()) == -1)
                throw new CertificateEncodingException(
                    "Unexpected end of stream");    
              if (b != footer[j])
                throw new CertificateEncodingException("Bad footer");    
            }

//
            break;
          }
          baos.write((byte)(b & 0xff));
        }
        is = new ByteArrayInputStream(baos.toByteArray());
      }
      else
      {
        notDER2 = false;
        if (inStream.markSupported())
        {
          inStream.reset();
          is = inStream;
        }
        else
        {
          baos.write((byte)(b & 0xff));

          while (true)
          {
            if ((b = inStream.read()) == -1)
              break;
            baos.write((byte)(b & 0xff));
          }
          is = new ByteArrayInputStream(baos.toByteArray());
        }
      }
    }
    catch (IOException e)
    {
      throw new CertificateException("IO error: " + e.getMessage());
    }
    if (!notDER2) {
         return is;
    }
    else {
        return new Base64InputStream(is);
    }
  }

  /**
   * Convert an InputStream into one where available() does what we
   * incorrectly expect.
   */
  //
  // XXX - it would be much better to redesign the code so that it doesn't
  //       have bogus expectations of InputStream.available(), i.e. we should
  //       use com.dstc.security.ssl.BasicTrustEngine.isEOF() or something
  //       of its ilk to check for end-of-input, but this will do for now.
  //
  static InputStream makeAvailableStream(InputStream instream)
    throws IOException
  {
    if (instream instanceof ByteArrayInputStream)
    {
      // It's already a ByteArrayInputStream, so no need to convert it
      return instream;
    }

    byte[] buffer = new byte[128];
    ByteArrayOutputStream bufOs = new ByteArrayOutputStream();

    int rd;
    while ((rd = instream.read(buffer)) > -1)
    {
      bufOs.write(buffer, 0, rd);
    }
    return new ByteArrayInputStream(bufOs.toByteArray());  // ugh
  }

  private static final boolean DUMMY = Licensed.VALID;
}

