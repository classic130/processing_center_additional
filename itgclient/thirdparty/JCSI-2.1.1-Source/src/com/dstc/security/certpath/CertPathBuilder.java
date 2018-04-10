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

import java.util.Arrays;
import java.util.Collection;
import java.util.Date;
import java.util.Vector;
import java.util.Iterator;

import java.security.Principal;
import java.security.InvalidKeyException;
import java.security.SignatureException;
import java.security.GeneralSecurityException;
import java.security.cert.X509Certificate;
import java.security.cert.CertificateException;

import com.dstc.security.common.X500Name;

/**
 * A class for building and validating certificate chains
 * against a supplied set of trust anchors
 *
 * NB: This is _not yet_ PKIX-compliant. Only name-chaining,
 * signature verification and certificate validity checks
 * are currently performed.
 */
public class CertPathBuilder
{
  private Vector trustedCerts = null;

  public CertPathBuilder() {}

  public CertPathBuilder(Vector trusted)
  {
    setTrustedCerts(trusted);
  }

  public void setTrustedCerts(Vector trusted)
  {
    this.trustedCerts = trusted;
  }

  public Vector getTrustedCerts()
  {
    return this.trustedCerts;
  }

  /** 
   * Builds a CertPath from a Collection of X509Certificates,
   * and an X509CertSelector for the end-entity certificate,
   * verifying the certpath in the process
   */
  public CertPath build(Collection certs, X509CertSelector selector) 
    throws CertPathException, CertificateException
  {
    Vector chain = doNameChaining(certs, selector);
    X509Certificate[] path = new X509Certificate[chain.size()];
    chain.toArray(path);
    verify(path);
    return new CertPath(path);
  }

  /** 
   * Constructs a CertPath from a Collection of X509Certificates,
   * and an X509CertSelector for the end-entity certificate
   */
  public Vector doNameChaining(Collection certColl, X509CertSelector selector)
    throws CertPathException
  {
    Vector retval = new Vector();
    Vector certs = new Vector(certColl);

    //Find first cert in chain
    Iterator iterator = certs.iterator();

    X509Certificate cert;

    while (true)
    {
      cert = (X509Certificate)iterator.next();

      if (selector.match(cert))
      {
        retval.add(cert);
        certs.removeElement(cert);
        break;
      }

      if (!iterator.hasNext())
        throw new CertPathException("End-entity cert not found");
    }

    //Iteratively find signer of previous cert until 
    //a self-signed cert is found or there are no more certs left

    while (true)
    {
      //no more certs left
      if (certs.isEmpty()) break;

      iterator = certs.iterator();

      //issuer -> subject
      Principal subject = cert.getIssuerDN();

      //self-signed
      if (cert.getSubjectDN().equals(subject)) break;

      while (true)
      {
        //no more certs
        if (!iterator.hasNext())
          return retval;

        cert = (X509Certificate)iterator.next();

        //got subject's cert
        if (cert.getSubjectDN().equals(subject))
        {
          retval.addElement(cert);
          certs.removeElement(cert);
          break;
        }
      }
    }

    return retval;
  }

  /**
   * Verifies the cert path against a Collection of trusted certs
   * The certs are expected to be in name-chained order.
   */
  public void verify(X509Certificate[] path) 
    throws NoTrustAnchorException, CertPathException, CertificateException
  {
    verify(path, null);
  }

  /**
   * @param checker a callback to check each certificate, or null
   */
  public void verify(X509Certificate[] path, X509CertChecker checker) 
    throws NoTrustAnchorException, CertPathException, CertificateException
  {
    if (trustedCerts == null)
      throw new CertPathException("No trusted certs set");

    if (path == null || path.length == 0)
      throw new CertPathException("Cert path must contain at least one cert");

    Date now = new Date();  // current time

    try
    {
      int ind = 0;

      //Verify the cert chain as far as we can go

      X509Certificate thisCert, nextCert;
      thisCert = path[ind];
  
      while (true)
      {
        if (ind == path.length - 1)
          break;

        checkCert(thisCert, checker, now);
        nextCert = path[++ind];
        thisCert.verify(nextCert.getPublicKey());
        thisCert = nextCert;
      }
  
      //thisCert is either self-signed or not

      Principal clientIssuerDN = thisCert.getIssuerDN();
      boolean selfSigned =
        X500Name.equals(clientIssuerDN, thisCert.getSubjectDN());

      //locate issuer cert amongst trusted certs

      Iterator iterator = trustedCerts.iterator();
      while (iterator.hasNext())
      {
        X509Certificate cert = (X509Certificate)iterator.next();

        if (X500Name.equals(clientIssuerDN, cert.getSubjectDN()))
        {
          //self-signed case, just test for cert equality
          if (selfSigned)
          {
            checkCert(thisCert, checker, now);
            boolean truth
              = Arrays.equals(thisCert.getEncoded(), cert.getEncoded());
            thisCert.verify(cert.getPublicKey());
            return;
          }            
          //otherwise verify thisCert against CA public key
          else
          {
            checkCert(thisCert, checker, now);
            thisCert.verify(cert.getPublicKey());
            return;
          }
        }
      }

      //out of certs, therefore no trust
      throw new NoTrustAnchorException("No trust anchor for this path");
    }
    catch (SignatureException e)
    {
      throw new CertPathException("Bad signature on cert");
    }
    catch (CertificateException e)
    {
      throw e;
    }
    catch (InvalidKeyException e)
    {
      throw new CertPathException(e.getMessage());
    }
    catch (GeneralSecurityException e)
    {
      throw new CertPathException(e.getMessage());
    }
  }

  private static void checkCert(X509Certificate cert, 
                                X509CertChecker checker, Date date)
    throws CertificateException
  {
    cert.checkValidity();
    if (checker != null)
    {
      checker.checkCert(cert, date);
    }
  }
}
