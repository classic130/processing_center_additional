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

package com.dstc.security.common;

import java.util.Properties;
import java.util.StringTokenizer;

/**
 * <p>A class which centralizes the management of Algorithm Object
 * Identifiers.
 *
 * @version 0.98, 98/07/01
 * @author Ming Yung
 */
public class OID 
{
  // Message Digest Algorithms
  public static final String md2 = "1.2.840.113549.2.2";
  public static final String md4 = "1.2.840.113549.2.4";
  public static final String md5 = "1.2.840.113549.2.5";
  public static final String sha_1 = "1.3.14.3.2.26";
  public static final String ripemd_160 = "1.3.36.3.2.1";
  
  // Signature Algorithms
  public static final String dsaWithSHA_old = "1.3.14.3.2.13";
  public static final String dsaWithSHA = "1.2.840.10040.4.3";
  public static final String md2WithRSAEncryption = "1.2.840.113549.1.1.2";
  public static final String md5WithRSAEncryption = "1.2.840.113549.1.1.4";
  public static final String shaWithRSAEncryption = "1.2.840.113549.1.1.5";
  public static final String sha_1WithRSAEncryption_alt = "1.3.14.3.2.29";
  public static final String dhe = "1.0.1.0.1.0"; //unassigned
  
  //Password-Based Cipher - PKCS#5 
  public static final String pbeWithMD2AndDES_CBC = "1.2.840.113549.1.5.1";
  public static final String pbeWithMD5AndDES_CBC = "1.2.840.113549.1.5.3";    

  // Public Key Algorithms
  public static final String rsaEncryption = "1.2.840.113549.1.1.1";
  public static final String dsa_old = "1.3.14.3.2.12";
  public static final String dsa = "1.2.840.10040.4.1";
  public static final String dhpublicnumber = "1.2.840.10046.2.1";
  public static final String dhKeyAgreement = "1.2.840.113549.1.3.1";
  public static final String dhStatic = "1.2.840.10046.3.1";
  public static final String esdh = "1.2.840.113549.1.9.16.3.5";
  
  // Symmetric Key Algorithms
  public static final String rc2_cbc = "1.2.840.113549.3.2";
  public static final String des_ede3_cbc = "1.2.840.113549.3.7";
  public static final String idea_cbc = "1.3.6.1.4.1.188.7.1.1.2";

  // CMS Key wrap
  public static final String CMS3DESwrap = "1.2.840.113549.1.9.16.3.6";
  public static final String CMSRC2wrap = "1.2.840.113549.1.9.16.3.7";
  public static final String CMSIDEAwrap = "1.3.6.1.4.1.188.7.1.1.6";
  
  // From X.500
  public static final String country = "2.5.4.6";
  public static final String locality = "2.5.4.7";
  public static final String state = "2.5.4.8";
  public static final String organization = "2.5.4.10";
  public static final String organizationalUnit = "2.5.4.11";
  public static final String commonName = "2.5.4.3";
  public static final String emailAddress = "1.2.840.113549.1.9.1";
  public static final String rsa_500 = "2.5.8.1.1";
  
  // X.509 Extensions
  public static final String subjectKeyIdentifier = "2.5.29.14";
  public static final String keyUsage = "2.5.29.15";
  public static final String subjectAltName = "2.5.29.17";
  public static final String issuerAltName = "2.5.29.18";
  public static final String basicConstraints = "2.5.29.19";
  public static final String cRLNumber = "2.5.29.20";
  public static final String authorityKeyIdentifier = "2.5.29.35";
  public static final String netscapeCertType = "2.16.840.1.113730.1.1";
  public static final String extKeyUsage = "2.5.29.37";
  public static final String cRLDistributionPoints = "2.5.29.31";
  public static final String certificatePolicies = "2.5.29.32";
  public static final String policyConstraints = "2.5.29.36";
  public static final String nameConstraints = "2.5.29.30";
  
  // S/MIME
  public static final String id_data = "1.2.840.113549.1.7.1";
  public static final String id_signedData = "1.2.840.113549.1.7.2";
  public static final String id_envelopedData = "1.2.840.113549.1.7.3";
  public static final String id_digestedData = "1.2.840.113549.1.7.5";
  public static final String id_encryptedData = "1.2.840.113549.1.7.6";
  public static final String id_authData = "1.2.840.113549.1.9.16.1.2";
  
  public static final String id_contentType = "1.2.840.113549.1.9.3";
  public static final String id_messageDigest = "1.2.840.113549.1.9.4";
  public static final String id_signingTime = "1.2.840.113549.1.9.5";
  public static final String id_counterSignature= "1.2.840.113549.1.9.6";
  public static final String id_macValue = "1.2.840.113549.1.9.16.2.8";
  public static final String smimeCapabilities = "1.2.840.113549.1.9.15";
  public static final String encrypKeyPref = "1.2.840.113549.1.9.16.2.11";

  //CMP 
  public static final String PasswordBasedMac = "1.2.840.113533.7.66.13";
  public static final String DHBasedMac = "1.2.840.113533.7.66.30";

  // PKCS#10
  public static final String challengePassword = "1.2.840.113549.1.9.7";

  // PKCS#12
  public static final String pbeWithSHAAnd128BitRC4 
    = "1.2.840.113549.1.12.1.1";
  public static final String pbeWithSHAAnd40BitRC4 
    = "1.2.840.113549.1.12.1.2";
  public static final String pbeWithSHAAnd3_KeyTripleDES_CBC 
    = "1.2.840.113549.1.12.1.3";
  public static final String pbeWithSHAAnd2_KeyTripleDES_CBC 
    = "1.2.840.113549.1.12.1.4";
  public static final String pbeWithSHAAnd128BitRC2_CBC 
    = "1.2.840.113549.1.12.1.5";
  public static final String pbeWithSHAAnd40BitRC2_CBC 
    = "1.2.840.113549.1.12.1.6";

  // pkcs-12BagIds
  public static final String id_bagTypes = "1.2.840.113549.1.12.10.1";
  public static final String keyBag = "1.2.840.113549.1.12.10.1.1";
  public static final String pkcs_8ShroudedKeyBag 
    = "1.2.840.113549.1.12.10.1.2";
  public static final String certBag = "1.2.840.113549.1.12.10.1.3";
  public static final String crlBag = "1.2.840.113549.1.12.10.1.4";
  public static final String secretBag = "1.2.840.113549.1.12.10.1.5";
  public static final String safeContentBag = "1.2.840.113549.1.12.10.1.6";
  
  //PKCS#12 induced OID to be included in PKCS#9
  public static final String friendlyName = "1.2.840.113549.1.9.20";
  public static final String localKeyId = "1.2.840.113549.1.9.21";
  public static final String id_certTypes = "1.2.840.113549.1.9.22";
  public static final String x509Certificate = "1.2.840.113549.1.9.22.1";
  public static final String sdsiCertificate = "1.2.840.113549.1.9.22.2";
  public static final String id_crlTypes = "1.2.840.113549.1.9.23";
  public static final String x509crl = "1.2.840.113549.1.0.23.1";

  //PKCS#9 OIDs for use with PKCS#10 certificate requests
  public static final String pkcs_9ChallengePassword = "1.2.840.113549.1.9.7";
  public static final String pkcs_9ExtensionRequest = "1.2.840.113549.1.9.14";
  public static final String 
                pkcs_9ExtendedCertificateAttributes = "1.2.840.113549.1.9.9";

  //X.509 Certificate Extension - Extended Key Usage related OID
  public static final String kp_serverAuth = "1.3.6.1.5.5.7.3.1";
  public static final String kp_clientAuth = "1.3.6.1.5.5.7.3.2";
  public static final String kp_codeSigning = "1.3.6.1.5.5.7.3.3";
  public static final String kp_emailProtection = "1.3.6.1.5.5.7.3.4";
  public static final String kp_timeStamping = "1.3.6.1.5.5.7.3.8";
  // The following is defined in draft PKIX 
  // DataValidationCertificationService spec
  public static final String kp_dvcs = "1.3.6.1.5.5.7.3.10";

  //X.509 Certificate Extension - CertificatePolicies related OID
  public static final String qt_cps = "1.3.6.1.5.5.7.2.1";
  public static final String qt_unotice = "1.3.6.1.5.5.7.2.2";

  //Attribute Certificate related OIDs
  //Attributes
  public static final String id_at_role = "2.5.4.72"; //Role

  private static Properties names;
  private static Properties oids;
  
  public OID () {}
  
  static
  {
    names = new Properties ();

    names.put(md2, "MD2");
    names.put(md5, "MD5");
    names.put(sha_1, "SHA");
    names.put(ripemd_160, "RIPEMD-160");

    names.put(dsaWithSHA, "SHA1withDSA");
    names.put(md2WithRSAEncryption, "MD2withRSA");
    names.put(md5WithRSAEncryption, "MD5withRSA");
    names.put(sha_1WithRSAEncryption_alt, "SHA1withRSA");
    names.put(shaWithRSAEncryption, "SHA1withRSA");
    names.put(dhe, "DH");

    names.put(dsa, "DSA");
    names.put(dsa_old, "DSA");
    names.put(dsaWithSHA_old, "DSA");
    names.put(rsaEncryption, "RSA");
    names.put(rsa_500, "RSA");

    names.put(rc2_cbc, "RC2/CBC");
    names.put(des_ede3_cbc, "DESede/CBC");
    names.put(idea_cbc, "IDEA/CBC");

    names.put(pbeWithMD5AndDES_CBC, "PBEwithMD5andDES");
    names.put(pbeWithMD2AndDES_CBC, "PBEwithMD2andDES");
    names.put(pbeWithSHAAnd3_KeyTripleDES_CBC, 
              "PBEwithSHAand3-KeyTripleDES-CBC");
    names.put(pbeWithSHAAnd40BitRC2_CBC, "PBEwithSHAand40BitRC2-CBC");
    names.put(pbeWithSHAAnd40BitRC4, "PBEwithSHAand40BitRC4");
    names.put(pbeWithSHAAnd128BitRC4, "PBEwithSHAand128BitRC4");
    names.put(pbeWithSHAAnd128BitRC2_CBC, "PBEwithSHAand128BitRC2-CBC");
     
    names.put(dhKeyAgreement, "DH");
    names.put(dhpublicnumber, "DH");
    names.put(dhStatic, "DH");

    names.put(country, "C");
    names.put(state, "ST");
    names.put(locality, "L");
    names.put(organization, "O");
    names.put(organizationalUnit, "OU");
    names.put(commonName, "CN");
    names.put(emailAddress, "EmailAddress");

    names.put(id_data, "id-data");
    names.put(id_signedData, "id-signedData");
    names.put(id_envelopedData, "id-envelopedData");
    names.put(id_contentType, "id-contentType");
    names.put(id_messageDigest, "id-messageDigest");
    names.put(id_signingTime, "id-signingTime");

    //CMP stuff
    names.put(PasswordBasedMac, "PasswordBasedMac");
    names.put(DHBasedMac, "DHBasedMac");

    names.put(CMSRC2wrap, "RC2wrap");
    names.put(CMS3DESwrap, "3DESwrap");
    names.put(CMSIDEAwrap, "IDEAwrap");

    ////////////////////////////////////////////////////////// 

    oids = new Properties();

    oids.put("sha/dsa", dsaWithSHA);
    oids.put("sha1withdsa", dsaWithSHA);
    oids.put("sha-1/dsa", dsaWithSHA);
    oids.put("sha1withrsa", shaWithRSAEncryption);
    oids.put("sha-1/rsa", shaWithRSAEncryption);
    oids.put("md5withrsa", md5WithRSAEncryption);
    oids.put("md5/rsa", md5WithRSAEncryption);
    oids.put("md2/rsa", md2WithRSAEncryption);

    oids.put("dsa", dsa);
    oids.put("rsa", rsaEncryption);

    oids.put("sha", sha_1);
    oids.put("sha-1", sha_1);
    oids.put("md5", md5);

    oids.put("c", country);
    oids.put("st", state);
    oids.put("s", state);
    oids.put("l", locality);
    oids.put("o", organization);
    oids.put("ou", organizationalUnit);
    oids.put("cn", commonName);
    oids.put("emailaddress", emailAddress);
    oids.put("email", emailAddress);
    oids.put("e", emailAddress);

    oids.put("id-data", id_data);
    oids.put("id-signeddata", id_signedData);
    oids.put("id-envelopeddata", id_envelopedData);
    oids.put("id-contenttype", id_contentType);
    oids.put("id-messagedigest", id_messageDigest);
    oids.put("id-signingtime", id_signingTime);

    oids.put("3deswrap", CMS3DESwrap);
    oids.put("rc2wrap", CMSRC2wrap);
    oids.put("ideawrap", CMSIDEAwrap);
  }
  
  public static final String getAlgName(String oid)
  {
    String retval = (String)names.get(oid);
    return (retval == null ? oid : retval);
  }
  
  public static final String getAlgOid(String name)
  {
    String retval = (String)oids.get(name.toLowerCase());
    if (retval == null)
    {
      return (isDottedString(name) ? name : null);
    }
    else
    {
      return retval;
    }
  }

  private static boolean isDottedString(String str)
  {
    if (str.indexOf(".") == -1)
    {
      return false;
    }
    else
    {
      StringTokenizer tknz = new StringTokenizer(str, ".", false);

      try
      {
        while (tknz.hasMoreTokens())
        {
          Integer.parseInt(tknz.nextToken());
        }

        return true;
      }
      catch (Exception e)
      {
        return false;
      }
    }
  }
}
