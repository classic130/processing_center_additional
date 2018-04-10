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

package com.dstc.security.keymanage.pkcs7;

import java.security.cert.Certificate;
import java.security.cert.CertificateEncodingException;

import com.dstc.security.asn1.Asn1;
import com.dstc.security.asn1.Asn1Exception;
import com.dstc.security.common.AlgorithmId;
import com.dstc.security.common.ContentInfo;
import com.dstc.security.keymanage.pkcs7.SignerInfo;

//import com.dstc.security.cms.CMSException;
//import com.dstc.security.cms.SignedMessage;

/**
 *  Stub object intended to eventually represent the ASN.1
 *  structure SignedData. <p>
 *
 *  <pre>
 *  SignedData ::= SEQUENCE {
 *    version Version,
 *    digestAlgorithms DigestAlgoritmIdentifiers,
 *    contentInfo ContentInfo,
 *    certificates [0] IMPLICIT ExtendedCertificatesAndCertificates OPTIONAL,
 *    signerInfos SignerInfos
 *  }
 *
 *  DigestAlgorithmIdentifiers ::= SET OF DigestAlgorithmIdentier
 *
 *  DigestAlgorithmIdentifier ::= AlgorithmIdentifier
 *
 *  ExtendedCertificatesAndCertificates ::=
 *      SET OF ExtendedCertificateORCertificate
 *
 *  ExtededCertificateOrCertificate ::= CHOICE {
 *    certificate Certificate, -- X509
 *    extendedCertificate [0] IMPLICIT ExtendedCertificate
 *  }
 *
 *  SignerInfos ::= SET OF SignerInfo
 *  </pre>
 */
public class SignedData
{
  private Asn1 asn1;

  private int version = 0;

  private AlgorithmId[] digestAlgorithms;

  private ContentInfo contentInfo;

  private Certificate[] certificates;

  private SignerInfo[] signerInfos;

  public SignedData( int version, AlgorithmId[] digestAlgorithms,
                     ContentInfo contentInfo, Certificate[] certificates,
                     SignerInfo[] signerInfos )
  throws Asn1Exception, CertificateEncodingException
  {
    throw new RuntimeException( "SignedData unimplemented" );
  }

  /**
   *  Creates a SignedData object from a DER encoding. <p>
   *
   *  @param asn1 An Asn1 object representing a SignedData object.
   *  @throws CMSException If ???
   *  @throws IOException If ContentInfo is invalid???
   */
  public SignedData( Asn1 asn1 ) throws Asn1Exception
  {
    throw new RuntimeException( "SignedData unimplemented" );
  }

  public byte[] getMessage(){
    return null;
  }
}
