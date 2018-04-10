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

package com.dstc.security.certpath;

import java.io.InputStreamReader;
import java.io.BufferedReader;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.Vector;
import java.security.*;
import java.security.cert.*;

import com.dstc.security.util.Base64OutputStream;

/**
 * A class for making trust decisions when presented with a certificate
 * chain by a peer.
 *
 * Given a set of trust anchors (trusted certs) the TrustEngine
 * validates or otherwise a certificate chain. In the case where
 * validation fails, a callback mechanism is supplied whereby user 
 * intervention can over-ride the failure. Currently this is available
 * only for the case where a NoTrustAnchorException is thrown.
 *
 * @author Ming Yung
 */
public class TrustEngine
{
  private static final boolean OFFER = false;
  private CertPathBuilder cpb;

  public TrustEngine()
  {
    this.cpb = new CertPathBuilder();
  }

  public TrustEngine(X509Certificate[] certs)
  {
    // XXX - should get rid of vectors and use arrays as the normal format
    this(arrayToVec(certs));
  }

  public TrustEngine(Vector certs)
  {
    this.cpb = new CertPathBuilder(certs);
  }

  public void setTrustedCerts(Vector certs)
  {
    this.cpb.setTrustedCerts(certs);
  }

  public Vector getTrustedCerts()
  {
    return this.cpb.getTrustedCerts();
  }

  /**
   * Verifies the supplied cert chain against the set of
   * trust anchors. The chain is expected to be name-chained,
   * starting with the end-entity cert.
   *
   * @parameter chain the X509Certificate chain with the 
   *                  end-entity cert first
   */
  public void verifyCertChain(X509Certificate[] chain) 
    throws CertPathException, CertificateException, IOException
  {
    verifyCertChain(chain, null);
  }

  public void verifyCertChain(X509Certificate[] chain, X509CertChecker checker) 
    throws CertPathException, CertificateException, IOException
  {
    try
    {
      this.cpb.verify(chain, checker);
    }
    catch (NoTrustAnchorException e)
    {
      if (OFFER)
      {
        offer(chain[chain.length - 1]);
      }
      else
        throw e;
    }
  }

  static Vector arrayToVec(Object[] objs)
  {
    Vector vec = new Vector(objs.length);
    for (int i = 0;  i < objs.length;  i++)
    {
      vec.addElement(objs[i]);
    }
    return vec;
  }

  private void offer(X509Certificate cert) 
    throws IOException, CertificateException
  {
    System.out.print("You don't trust your peer's root cert\n");
    System.out.println("  Issuer: " + cert.getIssuerDN().getName());
    System.out.println("  Subject: " + cert.getSubjectDN().getName());
    System.out.print("Either quit the session now or save the\n");
    System.out.println("root cert to add to your trusted certs store\n");
    System.out.print("Enter filename to save root cert: ");
    InputStreamReader isr = new InputStreamReader(System.in);
    BufferedReader in = new BufferedReader(isr);
    FileOutputStream fos = new FileOutputStream(in.readLine());
    fos.write("-----BEGIN CERTIFICATE-----".getBytes());
    Base64OutputStream os = new Base64OutputStream(fos);
    os.write(cert.getEncoded());
    os.flush();
    fos.write("-----END CERTIFICATE-----".getBytes());
    fos.close();
  }
}
