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

import java.util.HashSet;
import java.util.Vector;
import java.util.Iterator;
import java.security.cert.X509Certificate;

import com.dstc.security.x509.extns.*;
import com.dstc.security.common.X500Name;
import com.dstc.security.common.RDN;
import com.dstc.security.common.AttributeTypeAndValue;
import com.dstc.security.common.OID;
import com.dstc.security.asn1.Asn1;

public class X509ExtensionUtil
{
  public static final int DIGITAL_SIGNATURE = 0;
  public static final int NON_REPUDIATION   = 1;
  public static final int KEY_ENCIPHERMENT  = 2;
  public static final int DATA_ENCIPHERMENT = 3;
  public static final int KEY_AGREEMENT     = 4;
  public static final int KEY_CERT_SIGN     = 5;
  public static final int CRL_SIGN          = 6;
  public static final int ENCIPHER_ONLY     = 7;
  public static final int DECIPHER_ONLY     = 8;
        
  public static final int RFC822_NAME = 1;

  /**
   * Returns the e-mail address in this certificate, or null if absent.
   */
  public static String[] getEmailAddress(X509Certificate cert)
  {
    HashSet retval = new HashSet();

    try
    {
      byte[] val = cert.getExtensionValue(OID.subjectAltName);
      if (val != null)
      {
        byte[] enc = (Asn1.getAsn1(val)).getValue();
        if (enc != null)
        {
          SubjectAltName alt = new SubjectAltName(Asn1.getAsn1(enc));
          Vector names = alt.getNames();
          
          int i = 0;
          for (Iterator it=names.iterator(); it.hasNext(); i++)
          {
            GeneralName genName = (GeneralName)it.next();
            if (genName.getType() == RFC822_NAME)
            {
              retval.add(genName.getName());
            }
          }
        }
      }
 
      String dn = cert.getSubjectDN().getName();

      if (dn != null)
      {
        X500Name x500Name = new X500Name(dn);
        Vector rdns = x500Name.getRDNs();
        for (Iterator it=rdns.iterator(); it.hasNext(); )
        {
          AttributeTypeAndValue[] comp = ((RDN)it.next()).getTypeAndValue();
          for (int i=0; i<comp.length; i++)
          {
            if(comp[i].getType().equals(OID.emailAddress))
            {
              retval.add(comp[i].getValue());
            }
          }
        }
      }
      
      String[] ret = new String[retval.size()];
      retval.toArray(ret);
      return ret;
    }
    catch (Exception e)
    {
      throw new RuntimeException("Unexpected error in processing subAltName" +
       e.toString());
    }
  }
 
  /**
   * Returns true if this certificate is for signing.
   */
  public static boolean isKeyUsageSigning(X509Certificate cert)
  {
    if (cert.getKeyUsage() == null) return true;

    return (cert.getKeyUsage()[DIGITAL_SIGNATURE]);
  }
 
  /**
   * Returns true if this certificate is for encryption.
   */
  public static boolean isKeyUsageEncryption(X509Certificate cert)
  {
    boolean[] ku = cert.getKeyUsage();

    if (ku == null) return true;

    //defend against JDK 1.2.2 bug

    if (ku.length < KEY_ENCIPHERMENT + 1)
      return false;

    if (ku.length < DATA_ENCIPHERMENT + 1)
      return ku[KEY_ENCIPHERMENT];

    return (
      (ku.length < DECIPHER_ONLY + 1 ? true: !ku[DECIPHER_ONLY]) &&
      (ku[KEY_ENCIPHERMENT] || ku[DATA_ENCIPHERMENT]));
  }
 
  /**
   * Returns true if this certificate is for decryption.
   */
  public static boolean isKeyUsageDecryption(X509Certificate cert)
  {
    boolean[] ku = cert.getKeyUsage();

    if (ku == null) return true;

    //defend against JDK 1.2.2 bug

    if (ku.length < KEY_ENCIPHERMENT + 1)
      return false;

    if (ku.length < DATA_ENCIPHERMENT + 1)
      return ku[KEY_ENCIPHERMENT];

    return (
      (ku.length < ENCIPHER_ONLY + 1 ? true: !ku[ENCIPHER_ONLY]) &&
      (ku[KEY_ENCIPHERMENT] || ku[DATA_ENCIPHERMENT]));
  }
 
  /**
   * Returns true if this certificate is for keyagreement.
   */
  public static boolean isKeyUsageKeyAgreement(X509Certificate cert)
  {
    if (cert.getKeyUsage() == null) return true;

    return cert.getKeyUsage()[KEY_AGREEMENT];
  }                              

  /**
   * Returns true if issuer name is populated
   */
  public static boolean isIssuerNamePopulated(X509Certificate cert)
  {
    return (cert.getIssuerDN() != null);
  }
 
  /**
   * Returns true if subject name is populated
   */
  public static boolean isSubjectNamePopulated(X509Certificate cert)
  {
    return (cert.getSubjectDN() != null);
  }
 
  /**
   * Returns the subject alt names
   */
  public static String[] getSubjectAltNames(X509Certificate cert)
  {
    byte[] val = cert.getExtensionValue(OID.subjectAltName);
    if (val == null) return null;

    try
    {
      byte[] enc = (Asn1.getAsn1(val)).getValue();
      SubjectAltName alt = new SubjectAltName(Asn1.getAsn1(enc));
      Vector names = alt.getNames();
      
      String[] retval = new String[names.size()];
      int i = 0;
      for (Iterator it=names.iterator(); it.hasNext(); i++)
      {
        retval[i] = ((GeneralName)it.next()).getName();
      }

      return retval;
    }
    catch (Exception e)
    {
      throw new RuntimeException("Unexpected error in processing subAltName" +
       e.toString());
    }
  }                             

  /**
   * Returns true if the cert is a CA
   */
  public static boolean isCACert(X509Certificate cert)
  {
    if (cert.getVersion() == 3)
    {
      return (cert.getBasicConstraints() != -1 ? true : false);
    }
    else
    {
      return (cert.getIssuerDN().equals(cert.getSubjectDN()));
    }
  }                             

  /**
   * Returns true if the subject public key algorithm is Diffie Hellman
   */
  public static boolean isDiffieHellmanKeyXCert(X509Certificate cert)
  {
    String alg = cert.getPublicKey().getAlgorithm();
    return ((alg.equals("DH") || alg.equals("Diffie-Hellman")));
  }
}
