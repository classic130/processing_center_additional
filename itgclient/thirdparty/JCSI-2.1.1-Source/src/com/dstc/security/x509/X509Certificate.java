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

import java.io.*;
import java.util.Set;
import java.util.HashSet;
import java.util.Date;
import java.util.Iterator;
import java.util.Arrays;
import java.util.Vector;
import java.math.BigInteger;
import java.security.*;
import java.security.cert.CertificateExpiredException;
import java.security.cert.CertificateNotYetValidException;
import java.security.cert.CertificateEncodingException;
import java.security.cert.CertificateException;
import java.security.spec.X509EncodedKeySpec;

import com.dstc.security.asn1.*;
import com.dstc.security.common.OID;
import com.dstc.security.common.AlgorithmId;
import com.dstc.security.common.X500Name;
import com.dstc.security.common.SubjectPublicKeyInfo;
import com.dstc.security.x509.extns.*;

import com.dstc.security.util.Debug;

/**
 * <p>Implements the java.security.cert.X509Certificate class.
 *
 * The x.509 ASN.1 strcuture Certificate is
 *
 * <pre>
 *  <p>Certificate  ::=     SEQUENCE  {
 *       tbsCertificate       TBSCertificate,
 *       signatureAlgorithm   AlgorithmIdentifier,
 *       signature            BIT STRING  }
 *  
 *  <p>TBSCertificate  ::=  SEQUENCE  {
 *       version         [0]  EXPLICIT Version DEFAULT v1,
 *       serialNumber         CertificateSerialNumber,
 *       signature            AlgorithmIdentifier,
 *       issuer               Name,
 *       validity             Validity,
 *       subject              Name,
 *       subjectPublicKeyInfo SubjectPublicKeyInfo,
 *       issuerUniqueID  [1]  UniqueIdentifier OPTIONAL,
 *                            -- If present, version must be v2 or v3
 *       subjectUniqueID [2]  UniqueIdentifier OPTIONAL,
 *                            -- If present, version must be v2 or v3
 *       extensions      [3]  EXPLICIT Extensions OPTIONAL
 *                            -- If present, version must be v3
 *       }
 *  
 *  <p>Version  ::=  INTEGER  {  v1(0), v2(1), v3(2)  }
 *  
 *  <p>CertificateSerialNumber  ::=  INTEGER
 *  
 *  <p>UniqueIdentifier  ::=  BIT STRING
 *  
 *  <p>Extensions  ::=  SEQUENCE SIZE (1..MAX) OF Extension
 *  
 *  <p>Extension  ::=  SEQUENCE  {
 *       extnID      OBJECT IDENTIFIER,
 *       critical    BOOLEAN DEFAULT FALSE,
 *       extnValue   OCTET STRING  }
 * </pre>
 *
 * @version 0.98, 98/07/01
 * @author Ming Yung
 */
public class X509Certificate extends java.security.cert.X509Certificate 
{
  protected Asn1 asn1 = null;
  protected TBSCertificate tbs;
  protected AlgorithmId sigAlg;
  protected byte[] sigData;  

  public X509Certificate() {}

  public X509Certificate(InputStream is) 
    throws Asn1Exception, IOException 
  {
    this(Asn1.getAsn1(is));
  }

  /**
   * Constructs a Certificate from a DER encoding
   */
  public X509Certificate(Asn1 asn1) 
    throws Asn1Exception, IOException 
  {
    this.asn1 = asn1;

    if (!(asn1 instanceof Sequence))
    {
      throw new Asn1Exception("Bad certificate encoding");
    }

    Iterator it = asn1.components();

    this.tbs = new TBSCertificate((Asn1)it.next());

    this.sigAlg = new AlgorithmId((Asn1)it.next());

    this.sigData = ((BitString)it.next()).getBytes();
  }

////////////////////////////////////////////////////////////////////////////
// Implements methods defined abstract in java.security.cert.X509Certificate
////////////////////////////////////////////////////////////////////////////

  /**
   * Checks if this Certificate is valid
   */
  public void checkValidity()
    throws CertificateExpiredException, CertificateNotYetValidException
  {
    Date now = new Date();

    if (now.after(getNotAfter())) 
    {
      throw new CertificateExpiredException 
          ("Certficate Expired on: " + getNotAfter());
    }

    if (now.before(getNotBefore()))
    {
      throw new CertificateNotYetValidException 
          ("Certficate Not Valid until " + getNotBefore());
    }
  }

  /**
   * Checks if this Certificate is valid on date
   */
  public void checkValidity(Date date)
      throws CertificateExpiredException, CertificateNotYetValidException 
  {
    if (date.after(getNotAfter())) 
    {
      throw new CertificateExpiredException 
          ("Certficate Expires on: " + getNotAfter());
    }

    if (date.before(getNotBefore()))
    {
      throw new CertificateNotYetValidException 
          ("Certficate Not Valid until " + getNotBefore());
    }
  }

  /**
   * Returns this Certificate's Version
   */
  public int getVersion() 
  {
    return tbs.getVersion() + 1;
  }

  /**
   * Returns this Certificate's Serial Number
   */
  public BigInteger getSerialNumber() 
  {
    return tbs.getSerialNumber();
  }

  /**
   * Returns the Issuer's Distinguished Name of this Certificate
   */
  public Principal getIssuerDN() 
  {
    return tbs.getIssuer();
  }

  /**
   * Returns the Subject's Distinguished Name of this Certificate
   */
  public Principal getSubjectDN() 
  {
    return tbs.getSubject();
  }

  /**
   * Returns the Not Before time of this Certificate
   */
  public Date getNotBefore() 
  {
    if (tbs.getValidity() == null)
    {
      return null;
    }
    else
    {
      return tbs.getValidity().getNotBefore();
    }
  }

  /**
   * Returns the Not After time of this Certificate
   */
  public Date getNotAfter() 
  {
    if (tbs.getValidity() == null)
    {
      return null;
    }
    else
    {
      return tbs.getValidity().getNotAfter();
    }
  }

  /**
   * Returns the DER encoding of the TBSCertificate
   */
  public byte[] getTBSCertificate() throws CertificateEncodingException 
  {
    try
    {
      return tbs.getAsn1().getEncoded();
    }
    catch (Asn1Exception e)
    {
      throw new CertificateEncodingException(e.toString());
    }
  }

  /**
   * Returns the Signature bytes in this Certifcate
   */
  public byte[] getSignature() 
  {
    return sigData;
  }

  /**
   * Returns the Signature Algorithm Name for this Certifcate
   */
  public String getSigAlgName() 
  {
    return OID.getAlgName(sigAlg.getOid());
  }

  /**
   * Returns the Signature Algorithm Object Identifier for this Certificate
   */
  public String getSigAlgOID() 
  {
    return sigAlg.getOid();
  }

  /**
   * Returns the DER encoded Signature Alg Parameters for this Certificate
   */
  ///XXX
  public byte[] getSigAlgParams() 
  {
    try
    {
      return sigAlg.getParams().getEncoded();
    }
    catch (IOException e)
    {
      return null;
    }
  }

  public boolean[] getIssuerUniqueID() 
  {
    byte val[] = tbs.getIssuerUniqueId();
    if (val == null) return null;

    boolean retval[] = new boolean[8*val.length];
    for (int j=0; j<val.length; j++)
    {
      for (int i=0; i<8; i++)
      {
        retval[j*8 + i] = ((val[j] >>> i) & 0x01) == 0 ? false : true;
      }
    }

    return retval;
  }

  public boolean[] getSubjectUniqueID() 
  {
    byte val[] = tbs.getSubjectUniqueId();
    if (val == null) return null;

    boolean retval[] = new boolean[8*val.length];
    for (int j=0; j<val.length; j++)
    {
      for (int i=0; i<8; i++)
      {
        retval[j*8 + i] = ((val[j] >>> i) & 0x01) == 0 ? false : true;
      }
    }

    return retval;
  }
 
  /**
   * Returns the KeyUsage values for this certificate as a boolean array
   */
  public boolean[] getKeyUsage() 
  {
    byte[] val = tbs.getExtensions().getValue(OID.keyUsage);
    if (val == null) return null;

    try
    {
      KeyUsage ku = new KeyUsage(Asn1.getAsn1(val));
      return ku.getKeyUsage();
    }
    catch (Exception e)
    {
      throw new RuntimeException("Internal error: " + e.toString());
    }
  }

  public int getBasicConstraints() 
  {
    byte[] val = tbs.getExtensions().getValue(OID.basicConstraints);
    if (val == null) return -1;

    try
    {
      BasicConstraints bc = new BasicConstraints(Asn1.getAsn1(val));
      return bc.getBasicConstraints();
    }
    catch (Exception e)
    {
      throw new RuntimeException("Internal error: " + e.toString());
    }
  }

  public boolean hasUnsupportedCriticalExtension()
  {
    throw new UnsupportedOperationException();
  }

////////////////////////////////////////////////////////////////////////////
// Implements the methods defined abstract in java.security.cert.Certificate
////////////////////////////////////////////////////////////////////////////

  /**
   * Returns the DER encoding of this Certificate
   */
  public byte[] getEncoded() throws CertificateEncodingException 
  {
    try
    {
      return this.asn1.getEncoded();
    }
    catch (Asn1Exception e)
    {
      throw new CertificateEncodingException(e.toString());
    }
  }

  /**
   * Returns the Public Key corresponding to this Certificate
   */
  public PublicKey getPublicKey()
  {
    try
    {
      String algName =
        OID.getAlgName(tbs.getSubjectPubKeyInfo().
          getAlgorithmId().getOid());
      KeyFactory keyFact = KeyFactory.getInstance(algName);
      return keyFact.generatePublic(
        new X509EncodedKeySpec(
               tbs.getSubjectPubKeyInfo().getAsn1().getEncoded()));
    } 
    catch (Exception e)
    {
        throw new RuntimeException("bad public key ");
    }
  }

  /**
   * Verifies this Certificate against the signerKey
   */
  public void verify(PublicKey signerKey) 
      throws CertificateException, NoSuchAlgorithmException,
      InvalidKeyException, NoSuchProviderException,
      SignatureException 
  {
      Signature sig = Signature.getInstance(getSigAlgName());
      verifyKey(sig, signerKey);
  }

  /**
   * Verifies this Certificate against the signerKey with sigProvider
   */
  public void verify(PublicKey key, String sigProvider)
      throws CertificateException, NoSuchAlgorithmException,
      InvalidKeyException, NoSuchProviderException,
      SignatureException 
  {
      Signature sig = Signature.getInstance(getSigAlgName(), sigProvider);
      verifyKey(sig, key);
  }

  private void verifyKey(Signature sig, PublicKey key)
      throws CertificateException, InvalidKeyException, SignatureException
  {
      sig.initVerify(key);
      sig.update(getTBSCertificate());
      boolean verifies = sig.verify(getSignature());
      if (!verifies)
        throw new CertificateException("Bad signature");
  }

  public String toString()
  {
    StringBuffer sb = new StringBuffer();
    sb.append("X509 Certificate, version " + getVersion() + "\n");
    sb.append("Serial Number: " + getSerialNumber().toString() + "\n");
    sb.append("Issuer: " + getIssuerDN().getName() + "\n");
    sb.append("Subject: " + getSubjectDN().getName() + "\n");
    sb.append("Key Algorithm: " + getPublicKey().getAlgorithm() + "\n");
    sb.append(getPublicKey().toString()+ "\n");
    sb.append("Signature Algorithm: " + getSigAlgName());
    sb.append(" (" + getSigAlgOID() + ")\n");
    sb.append("Valid Not Before: " + getNotBefore() + "\n");
    sb.append("Valid Not After: " + getNotAfter() + "\n");

    if (this.tbs.getExtensions() != null)
      sb.append(this.tbs.getExtensions().toString());

    return sb.toString();
  }

//////////////////////////////////////////////////////////////////////////
// Implements methods defined abstract in java.security.cert.X509Extension
//////////////////////////////////////////////////////////////////////////


  /**
   * Returns the critical extension oids.
   */
  public Set getCriticalExtensionOIDs() 
  {
    if (tbs.getExtensions() == null)
      return new HashSet();
    else
      return tbs.getExtensions().getCriticalOIDs();
  }

  /**
   * Returns the non-critical extension oids.
   */
  public Set getNonCriticalExtensionOIDs() 
  {
    if (tbs.getExtensions() == null)
      return new HashSet();
    else
      return tbs.getExtensions().getNonCriticalOIDs();
  }

  /**
   * Returns the extension value for the given oid
   */
  public byte[] getExtensionValue(String oid) 
  {
    byte[] val;

    if (tbs.getExtensions() == null)
    {
      return null;
    }
    else
    {
      try
      {
        val = tbs.getExtensions().getValue(oid);

        if (val == null)
        {
           return null;
        }
        else
        {
          return (new OctetString(val)).getEncoded();
        }
      }
      catch (Exception e)
      {
        throw new RuntimeException("Internal error: " + e.toString());
      }
    }
  }

  public boolean equals(Object obj)
  {
    try {
        if (obj instanceof java.security.cert.X509Certificate)
        {
          return Arrays.equals(getEncoded(),
            ((java.security.cert.X509Certificate)obj).getEncoded());
        }
        else
          return false;
    }
    catch(CertificateEncodingException e) {
        return false;
    }
  }

}
