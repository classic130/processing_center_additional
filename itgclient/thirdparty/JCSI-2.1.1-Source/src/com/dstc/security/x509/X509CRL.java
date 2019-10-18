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

import java.io.IOException;
import java.io.InputStream;
import java.math.BigInteger;
import java.util.Collections;
import java.util.Date;
import java.util.HashMap;
import java.util.Map;
import java.util.Set;
import java.util.Iterator;

import java.security.NoSuchAlgorithmException;
import java.security.NoSuchProviderException;
import java.security.InvalidKeyException;
import java.security.SignatureException;
import java.security.Principal;
import java.security.PublicKey;
import java.security.Signature;
import java.security.cert.Certificate;
import java.security.cert.CRLException;

import com.dstc.security.asn1.Asn1;
import com.dstc.security.asn1.Asn1Exception;
import com.dstc.security.asn1.Sequence;
import com.dstc.security.asn1.BitString;
import com.dstc.security.common.OID;
import com.dstc.security.common.X500Name;
import com.dstc.security.common.AlgorithmId;

/**
 * Implements X509 Certifcate Revocation Lists.
 *
 * <p>Defined by the ASN.1 structure CertificateList.
 * <pre>
 * CertificateList  ::=  SEQUENCE  {
 *     tbsCertList          TBSCertList,
 *     signatureAlgorithm   AlgorithmIdentifier,
 *     signature            BIT STRING  }
 * </pre>
 * @see CRL
 * @see CertificateFactory
 * @see X509Extension
 */
public class X509CRL extends java.security.cert.X509CRL
{
  protected Asn1 asn1 = null;
  protected TbsCertList tbsCertList;
  protected AlgorithmId sigAlg;
  protected byte[] signature;
  /**
   * X509CRLEntry values, indexed by serial number.
   * Depends on tbsCertList being immutable.
   */
  protected Map bySerialNumber;

  public X509CRL() 
  {
    // XXX - can we get rid of this constructor?
  }

  /**
   * Constructs an X509CRL from a DER encoding
   */
  public X509CRL(InputStream is) 
    throws Asn1Exception, IOException
  {
    this(Asn1.getAsn1(is));
  }

  /**
   * Constructs an X509CRL from a DER encoding
   */
  public X509CRL(Asn1 asn1) 
    throws Asn1Exception, IOException
  {
    this.asn1 = asn1;
    if (!(asn1 instanceof Sequence))
    {
      throw new Asn1Exception("Bad CRL encoding");
    }                                                
    Iterator it = asn1.components();

    this.tbsCertList = new TbsCertList((Asn1)it.next());

    this.sigAlg = new AlgorithmId((Asn1)it.next());

    this.signature = ((BitString)it.next()).getBytes();
  }

  public byte[] getEncoded() throws CRLException
  {
    try
    {
      return this.asn1.getEncoded();
    }
    catch (Asn1Exception e)
    {
      throw new CRLException(e.getMessage());
    }
  }

  public void verify(PublicKey key)
      throws CRLException, NoSuchAlgorithmException,
      InvalidKeyException, NoSuchProviderException,
      SignatureException
  {
    Signature sig = Signature.getInstance(getSigAlgName());
    sig.initVerify(key);
    sig.update(getTBSCertList());
    boolean verifies = sig.verify(getSignature());
  }

  public void verify(PublicKey key, String sigProvider)
      throws CRLException, NoSuchAlgorithmException,
      InvalidKeyException, NoSuchProviderException,
      SignatureException
  {
    Signature sig = Signature.getInstance(getSigAlgName(), sigProvider);
    sig.initVerify(key);
    sig.update(getTBSCertList());
    boolean verifies = sig.verify(getSignature());
  }

  public int getVersion()
  {
    return this.tbsCertList.getVersion();
  }

  public Principal getIssuerDN()
  {
    return this.tbsCertList.getIssuer();
  }

  public Date getThisUpdate()
  {
    return this.tbsCertList.getThisUpdate().getDate();
  }

  public Date getNextUpdate()
  {
    if (this.tbsCertList.getNextUpdate() == null)
      return null;

    return this.tbsCertList.getNextUpdate().getDate();
  }

  protected Map getSerialNumberMap()
  {
    // XX - if anyone could modify the TbsCertList then this cache would get
    //      stale, but (unless someone subclasses us) the only reference to
    //      the TbsCertList is held by us.
    Map result = this.bySerialNumber;
    if (result == null)
    {
      result = new HashMap();
      Set revokedCerts = getRevokedCertificates();
      if (revokedCerts != null)
      {
        Iterator entries = revokedCerts.iterator();
        while (entries.hasNext())
        {
          X509CRLEntry entry = (X509CRLEntry)entries.next();
          result.put(entry.getSerialNumber(), entry);
        }
      }
      this.bySerialNumber = result;
    }
    return result;
  }

  public java.security.cert.X509CRLEntry 
    getRevokedCertificate(BigInteger serialNumber)
  {
    return (X509CRLEntry) getSerialNumberMap().get(serialNumber);
  }

  public Set getRevokedCertificates()
  {
    Set certs = this.tbsCertList.getRevokedCerts();
    if (certs != null)
    {
      certs = Collections.unmodifiableSet(this.tbsCertList.getRevokedCerts());
    }
    return certs;
  }

  public byte[] getTBSCertList() throws CRLException
  {
    try
    {
      return this.tbsCertList.getAsn1().getEncoded();
    }
    catch (Asn1Exception e)
    {
      throw new CRLException(e.getMessage());
    }
  }

  public byte[] getSignature()
  {
    return this.signature;
  }

  public String getSigAlgName()
  {
    return OID.getAlgName(this.sigAlg.getOid());
  }

  public String getSigAlgOID()
  {
    return this.sigAlg.getOid();
  }

  ///XXX
  public byte[] getSigAlgParams()
  {
    try
    {
      return this.sigAlg.getParams().getEncoded();
    }
    catch (IOException e)
    {
      throw new RuntimeException("bad encoding");
    }
  }

  public boolean isRevoked(Certificate cert)
  {
    try
    {
      BigInteger serialNumber =
        ((java.security.cert.X509Certificate)cert).getSerialNumber();

      return getRevokedCertificate(serialNumber) != null;
    }
    catch (ClassCastException e)
    {
      // Not an X509Certificate, so doesn't match this CRL
      return false;
    }
  }

  public String toString()
  {
    StringBuffer sb = new StringBuffer();
    sb.append("X509 CRL, version ").append(getVersion()+1).append("\n");
    sb.append("Issuer              : ").append(getIssuerDN().getName()).append("\n");
    sb.append("This Update         : ").append(getThisUpdate()).append("\n");
    if (getNextUpdate() != null)
      sb.append("Next Update         : ").append(getNextUpdate()).append("\n");

    if (this.tbsCertList.getExtensions() != null)
      sb.append(this.tbsCertList.getExtensions().toString());

    sb.append("\nRevoked certificates: ").append("\n");
 
    if (getRevokedCertificates() != null)
    {
      for (Iterator it = getRevokedCertificates().iterator(); it.hasNext(); )
      {
        sb.append(it.next());
      }
    }

    return sb.toString();
  }

  public Set getCriticalExtensionOIDs()
  {
    return this.tbsCertList.getExtensions().getCriticalOIDs();
  }

  public Set getNonCriticalExtensionOIDs()
  {
    return this.tbsCertList.getExtensions().getNonCriticalOIDs();
  }

  public byte[] getExtensionValue(String oid)
  {
    return this.tbsCertList.getExtensions().getValue(oid);
  }

  ///XXX
  public boolean hasUnsupportedCriticalExtension()
  {
    return false;
  }
}
