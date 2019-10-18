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
//      Email: enquiries@dstc.edu.au
//
// This software is being provided "AS IS" without warranty of
// any kind.  In no event shall DSTC Pty Ltd be liable for
// damage of any kind arising out of or in connection with
// the use or performance of this software.
//
////////////////////////////////////////////////////////////////////////////

package com.dstc.security.keymanage.pkcs12.bags;

import java.io.ByteArrayInputStream;
import java.io.IOException;
import java.security.cert.Certificate;
import java.security.cert.CertificateException;
import java.security.cert.CertificateFactory;
import java.security.cert.X509Certificate;
import java.util.Iterator;
import java.util.NoSuchElementException;

import com.dstc.security.asn1.Asn1;
import com.dstc.security.asn1.Asn1Exception;
import com.dstc.security.asn1.Explicit;
import com.dstc.security.asn1.IA5String;
import com.dstc.security.asn1.Oid;
import com.dstc.security.asn1.OctetString;
import com.dstc.security.asn1.Sequence;
import com.dstc.security.common.OID;
import com.dstc.security.keymanage.debug.Debug;
import com.dstc.security.keymanage.pkcs12.bags.Bag;

/**
 *  Implements the PKCS#12 ASN.1 structure CertBag. <p>
 *
 *  <pre>
 *       CertBag ::= SEQUENCE {
 *           certId BAG-TYPE.&id ({CertTypes}),
 *           certValue [0] EXPLICIT BAG-TYPE.&Type({CertTypes}{@certId})
 *       }
 *  </pre>
 */
public class CertBag implements Bag
{
  public static final String X509_CERTIFICATE = OID.x509Certificate;
  public static final String SDSI_CERTIFICATE = OID.sdsiCertificate;

  // Hash Codes for Oids
  private static final int X509 = OID.x509Certificate.hashCode();
  private static final int SDSI = OID.sdsiCertificate.hashCode();

  private static final String KEYBAG_OID = OID.certBag;

  private static final int TAG_EXPLICIT = 0;
  
  private Asn1 asn1;
  private String certId;
  private Certificate certificate;
  
  /**
   *  Creates a PKCS#12 CertBag from an ASN.1 encoding. <p>
   *
   *  @param encoding The Asn1 encoded form of the CertBag.
   *  @throws Asn1Exception If asn1 is not a valid CertBag.
   */
  public CertBag( Asn1 encoding ) throws Asn1Exception
  {
    Debug.dumpAsn1To( encoding, Debug.CERTBAG );

    this.asn1 = encoding;

    CertificateFactory certFact = null;

    try
    {
      certFact = CertificateFactory.getInstance("X.509");
    }
    catch (Exception e)
    {
      throw new RuntimeException("No certificate factory for X.509");
    }
    
    try
    {
      Iterator it = this.asn1.components();
      Oid oid = (Oid) it.next();
      this.certId = oid.getOid();

      Asn1 explicit = (Asn1) it.next();
      Iterator itEx = explicit.components();

      int hash = oid.getOid().hashCode();
      if ( X509 == hash )
      {
        OctetString oct = (OctetString) itEx.next();
        byte[] encoded = oct.getBytes();
        Asn1 cert = Asn1.getAsn1( encoded );

        Debug.dumpAsn1To( cert, Debug.CERT );
        
        this.certificate 
          = certFact.generateCertificate(
              new ByteArrayInputStream(encoded));
      }
      else if ( SDSI == hash )
      {
        IA5String ia5 = (IA5String) itEx.next();
        
        Debug.log( Debug.INFO, "CertBag( Asn1 )",
            "SDSI Certificates Unsupported" );
        throw new Asn1Exception(
            "SDSI Certificates Are Yet To Be Supported" );
      }
      else
      {
        throw new Asn1Exception( "Unknown Certificate Type" );
      }
    }
    catch ( NoSuchElementException ex ) {
      throw new Asn1Exception( "Invalid CertBag ASN.1" );
    }
    catch ( ClassCastException ex ) {
      throw new Asn1Exception( "Invalid CertBag ASN.1" );
    }
    catch ( CertificateException ex) {
      throw new Asn1Exception( "Invalid X509Certificate" );
    }
  }

  /** 
   *  Creates a CertBag of type <code>certId</code> that holds
   *  <code>certificate</code>.
   *
   *  @param certId The OID type of the Certificate being passed.
   *  @param certificate The Certificate to hold.
   *  @throws CertificateException If the certificate type is not supported,
   *                               or if an invalid Certificate.
   */
  public CertBag( String certId, Certificate certificate )
  throws CertificateException
  {
    this.certId = certId;
    this.certificate = certificate;
    this.initialize();
  }
  
  /**
   *  This method initializes the <code>asn1</code> member using the
   *  <code>certId</code> and <code>certificate</code> members.
   */
  private void initialize() throws CertificateException
  {    
    this.asn1 = new Sequence();

      Oid oid = new Oid( this.certId );
      this.asn1.add( oid );
    
      Explicit certValue = new Explicit( Asn1.TAG_CLASS_CONTEXT, TAG_EXPLICIT );
   
      // Add Certificate Asn1 to explicit.
      X509Certificate x509 = null;
      int hash = this.certId.hashCode();

      if ( X509 == hash )
      {
        try
        {
          x509 = (X509Certificate) this.certificate;
        }
        catch ( ClassCastException ex ) {
          Debug.log( Debug.INFO, "CertBag.initialize()",
              "X509Certificate expected; received: " + x509.getType() );
          throw new CertificateException(
              "X509Certificate expected; received: " + x509.getType() );
        }
        byte[] encoded = x509.getEncoded();
        OctetString x509Certificate = new OctetString( encoded );
        certValue.add( x509Certificate );
      }
      else if ( SDSI == hash )
      {
        throw new CertificateException(
            "SDSI Certificates Are Yet To Be Supported" );
      }
      else
      {
        throw new CertificateException( "Unknown Certificate Type" );
      }
    this.asn1.add( certValue );
  }
  
  /**
   *  Returns the Bag-type Oid that identifies the type of this Bag. <p>
   *
   *  @return a String representation of a Bag-type Oid.
   */
  public String getType()
  {
    return KEYBAG_OID;
  }
  
  /**
   *  Returns the Asn1 representation of this CertBag. <p>
   *
   *  @return an Asn1 object representing this CertBag.
   */
  public Asn1 getAsn1()
  {
    return this.asn1;
  }
  
  /**
   *  Returns the OID that identifies the type of certificate held by this
   *  CertBag. <p>
   *
   *  @return a String representation of an OID.
   */
  public String getCertId()
  {
    return this.certId;
  }
  
  /**
   *  Returns the certificate held by this CertBag. <p>
   *
   *  @see java.security.cert.Certificate.
   *  @see java.security.cert.X509Certificate.
   *
   *  @return A subclass of Certificate.
   */
  public Certificate getCertificate()
  {
    return this.certificate;
  }
}
