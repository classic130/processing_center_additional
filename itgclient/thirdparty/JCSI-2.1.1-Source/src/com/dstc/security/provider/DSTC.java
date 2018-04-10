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

package com.dstc.security.provider;

import java.security.Provider;
import java.security.AccessController;

import com.dstc.security.util.Dependencies;
import com.dstc.security.common.OID;

/**
 * <p>The DSTC provider master class.
 *
 * @see java.security.Provider
 *
 * @version 0.98, 98/07/01
 * @author Ming Yung
 */
public final class DSTC extends Provider 
{
  private static final String PACKAGE = "com.dstc.security.provider.";

  private static final String PBE_PARAM = "AlgorithmParameters.PBEwithSHAand";
  private static final String PBE_CIPHER = "Cipher.PBEwithSHAand";
  private static final String PBE_KEYFACT = "SecretKeyFactory.PBEwithSHAand";
  
  private static String name;
  private static String info;
  private static double version;

  static
  {
    name    = "DSTC";
    version = -1.0;

    // Check that we have the required JAR files and versions;
    // incidentally get our version number
    String versionString = Dependencies.check(DSTC.class, false);
    if (versionString != null) {
      int firstDot = versionString.indexOf('.');
      if (firstDot >= 0) {
        int secondDot = versionString.indexOf('.', firstDot + 1);
        if (secondDot > 0) {
          // a.b.c or more;  use "a.b", ignore the rest
          versionString = versionString.substring(0, secondDot);
        }
      }
      try {
        version = Double.parseDouble(versionString);
      }
      catch (NumberFormatException ex) {
        // Don't abort;  use the dummy version (-1.0) and keep going
      }
    }

    StringBuffer sb = new StringBuffer();
    sb.append("DSTC Security Provider ");
    sb.append("(" + name + ") v" );
    sb.append((versionString == null) ? "?.?" : versionString);
    sb.append(" : \n");

    sb.append("  MD2, MD4, MD5, SHA-1 and RIPEMD-160 message digests,\n");
    sb.append("  DSA key generation and signatures,\n");
    sb.append("  RSA key generation and signing with ");
    sb.append("MD2, MD5, SHA-1 and RIPEMD-160\n");
    sb.append("  RSA encryption,\n");
    sb.append("  DES, DESede, Blowfish, IDEA, RC2 & RC5 block ciphers,\n");
    sb.append("  RC4 stream cipher,\n"); 
    sb.append("  Diffie-Hellman key agreement\n");
    sb.append("  Diffie-Hellman ephemeral signatures\n");
    sb.append("  DES-MAC, and HMAC with MD5, SHA1 and ");
    sb.append("RIPEMD-160 Message Authentication\n");
    sb.append("  PKCS#5 password-based encryption\n");
    sb.append("  PKCS#8 encryption of private keys\n");
    info = sb.toString();
  }
  
  public DSTC() 
  {
    super(name, version, info);

    AccessController.doPrivileged(
      new java.security.PrivilegedAction() {
        public Object run() {

          //Key pair generators

          put("KeyPairGenerator.DH", PACKAGE + "DHKeyPairGenerator");
          put("Alg.Alias.KeyPairGenerator.Diffie-Hellman", "DH");
          put("Alg.Alias.KeyPairGenerator.OID." + OID.dhKeyAgreement, "DH");
          put("Alg.Alias.KeyPairGenerator." + OID.dhKeyAgreement, "DH");
          put("Alg.Alias.KeyPairGenerator." + OID.dhpublicnumber, "DH");
          put("Alg.Alias.KeyPairGenerator." + OID.esdh, "DH");

          put("KeyPairGenerator.DSA", PACKAGE + "DSAKeyPairGenerator");
          put("Alg.Alias.KeyPairGenerator.OID." + OID.dsa, "DSA");
          put("Alg.Alias.KeyPairGenerator." + OID.dsa, "DSA");
          put("Alg.Alias.KeyPairGenerator." + OID.dsa_old, "DSA");

          put("KeyPairGenerator.RSA", PACKAGE + "RSAKeyPairGenerator");
          put("Alg.Alias.KeyPairGenerator.OID." + OID.rsaEncryption, "RSA");
          put("Alg.Alias.KeyPairGenerator." + OID.rsaEncryption, "RSA");
      
          //Key factories
      
          put("KeyFactory.DSA", PACKAGE + "DSAKeyFactory");
          put("Alg.Alias.KeyFactory.OID." + OID.dsa, "DSA");
          put("Alg.Alias.KeyFactory." + OID.dsa, "DSA");
          put("Alg.Alias.KeyFactory." + OID.dsa_old, "DSA");

          put("KeyFactory.RSA", PACKAGE + "RSAKeyFactory");
          put("Alg.Alias.KeyFactory.OID." + OID.rsaEncryption, "RSA");
          put("Alg.Alias.KeyFactory." + OID.rsaEncryption, "RSA");

          put("KeyFactory.DH", PACKAGE + "DHKeyFactory");
          put("Alg.Alias.KeyFactory.Diffie-Hellman", "DH");
          put("Alg.Alias.KeyFactory.OID." + OID.dhKeyAgreement, "DH");
          put("Alg.Alias.KeyFactory." + OID.dhKeyAgreement, "DH");
          put("Alg.Alias.KeyFactory." + OID.dhpublicnumber, "DH");
          put("Alg.Alias.KeyFactory." + OID.esdh, "DH");
      
          //Signature algorithms
      
          put("Signature.SHA1withDSA", PACKAGE + "DSA");
          put("Alg.Alias.Signature.SHA-1withDSA", "SHA1withDSA");
          put("Alg.Alias.Signature.SHA-1/DSA", "SHA1withDSA");
          put("Alg.Alias.Signature.SHA/DSA", "SHA1withDSA");
          put("Alg.Alias.Signature.DSA", "SHA1withDSA");
          put("Alg.Alias.Signature.DSS", "SHA1withDSA");
          put("Alg.Alias.Signature.OID." + OID.dsaWithSHA, "SHA1withDSA");
          put("Alg.Alias.Signature." + OID.dsaWithSHA, "SHA1withDSA");
          put("Alg.Alias.Signature." + OID.dsaWithSHA_old, "SHA1withDSA");

          put("Signature.MD2withRSA", PACKAGE + "RSAwithMD2");
          put("Alg.Alias.Signature.MD2/RSA", "MD2withRSA");
          put("Alg.Alias.Signature.OID." + OID.md2WithRSAEncryption, 
              "MD2withRSA");
          put("Alg.Alias.Signature." + OID.md2WithRSAEncryption, "MD2withRSA");

          put("Signature.MD5withRSA", PACKAGE + "RSAwithMD5");
          put("Alg.Alias.Signature.MD5/RSA", "MD5withRSA");
          put("Alg.Alias.Signature.OID." + OID.md5WithRSAEncryption, 
              "MD5withRSA");
          put("Alg.Alias.Signature." + OID.md5WithRSAEncryption, "MD5withRSA");

          put("Signature.SHA1withRSA", PACKAGE + "RSAwithSHA1");
          put("Alg.Alias.Signature.SHA-1withRSA", "SHA1withRSA");
          put("Alg.Alias.Signature.SHA-1/RSA", "SHA1withRSA");
          put("Alg.Alias.Signature.SHA1/RSA", "SHA1withRSA");
          put("Alg.Alias.Signature.SHA/RSA", "SHA1withRSA");
          put("Alg.Alias.Signature.OID." + OID.shaWithRSAEncryption, 
              "SHA1withRSA");
          put("Alg.Alias.Signature." + OID.shaWithRSAEncryption, 
              "SHA1withRSA");
          put("Alg.Alias.Signature." + OID.sha_1WithRSAEncryption_alt, 
              "SHA1withRSA");

          put("Signature.RIPEMD-160withRSA", PACKAGE + "RSAwithRIPEMD160"); 
          put("Alg.Alias.Signature.RIPEMD-160/RSA", "RIPEMD-160withRSA");
          put("Alg.Alias.Signature.RIPEMD160withRSA", "RIPEMD-160withRSA");
          //put("Alg.Alias.Signature.OID." + OID., "RIPEMD-160withRSA");
          //put("Alg.Alias.Signature." + OID., "RIPEMD-160withRSA");

          put("Signature.RawDSA", PACKAGE + "RawDSA");

          put("Signature.RawRSA", PACKAGE + "RawRSA");
      
          //Key agreement algorithms
      
          put("KeyAgreement.DH", PACKAGE + "DHKeyAgreement");
          put("Alg.Alias.KeyAgreement.Diffie-Hellman", "DH");
          put("Alg.Alias.KeyAgreement.OID." + OID.dhKeyAgreement, "DH");
          put("Alg.Alias.KeyAgreement." + OID.dhKeyAgreement, "DH");
          put("Alg.Alias.KeyAgreement." + OID.dhpublicnumber, "DH");

          put("KeyAgreement.ESDH", PACKAGE + "ESDHKeyAgreement");
          put("Alg.Alias.KeyAgreement.OID." + OID.esdh, "ESDH");
          put("Alg.Alias.KeyAgreement." + OID.esdh, "ESDH");
      
          //MessageDigest algorithms
      
          put("MessageDigest.MD2", PACKAGE + "MD2");
          put("Alg.Alias.MessageDigest.OID." + OID.md2, "MD2");
          put("Alg.Alias.MessageDigest." + OID.md2, "MD2");

          put("MessageDigest.MD4", PACKAGE + "MD4");
          put("Alg.Alias.MessageDigest.OID." + OID.md4, "MD4");
          put("Alg.Alias.MessageDigest." + OID.md4, "MD4");

          put("MessageDigest.MD5", PACKAGE + "MD5");
          put("Alg.Alias.MessageDigest.OID." + OID.md5, "MD5");
          put("Alg.Alias.MessageDigest." + OID.md5, "MD5");

          put("MessageDigest.RIPEMD-160", PACKAGE + "RIPEMD160");
          put("Alg.Alias.MessageDigest.OID." + OID.ripemd_160, "RIPEMD-160");
          put("Alg.Alias.MessageDigest." + OID.ripemd_160, "RIPEMD-160");

          put("MessageDigest.SHA", PACKAGE + "SHA1");
          put("Alg.Alias.MessageDigest.SHA-1", "SHA");
          put("Alg.Alias.MessageDigest.SHA1", "SHA");
          put("Alg.Alias.MessageDigest.OID." + OID.sha_1, "SHA");
          put("Alg.Alias.MessageDigest." + OID.sha_1, "SHA");
      
          //put("MessageDigest.SHA256", PACKAGE + "SHA256");
          //put("MessageDigest.SHA384", PACKAGE + "SHA384");
          //put("MessageDigest.SHA512", PACKAGE + "SHA512");

          //Key generators
      
          put("KeyGenerator.DES", PACKAGE + "DESKeyGenerator");

          put("KeyGenerator.AES", PACKAGE + "AESKeyGenerator");

          put("KeyGenerator.DESede", PACKAGE + "DESedeKeyGenerator");

          put("KeyGenerator.RC2", PACKAGE + "RC2KeyGenerator");

          put("KeyGenerator.RC4", PACKAGE + "RC4KeyGenerator");

          put("KeyGenerator.RC5", PACKAGE + "RC5KeyGenerator");

          put("KeyGenerator.IDEA", PACKAGE + "IDEAKeyGenerator");

          put("KeyGenerator.Blowfish", PACKAGE + "BlowfishKeyGenerator");
      
          //Secret key factories
      
          put("SecretKeyFactory.DES", PACKAGE + "DESSecretKeyFactory");

          put("SecretKeyFactory.AES", PACKAGE + "AESSecretKeyFactory");

          put("SecretKeyFactory.DESede", PACKAGE + "DESedeSecretKeyFactory");

          put("SecretKeyFactory.RC5", PACKAGE + "RC5SecretKeyFactory");

          put("SecretKeyFactory.RC2", PACKAGE + "RC2SecretKeyFactory");

          put("SecretKeyFactory.RC4", PACKAGE + "RC4SecretKeyFactory");

          put("SecretKeyFactory.IDEA", PACKAGE + "IDEASecretKeyFactory");

          put("SecretKeyFactory.Blowfish",
              PACKAGE + "BlowfishSecretKeyFactory");

          put("SecretKeyFactory.PBEwithMD5andDES",
              PACKAGE + "PBEwithMD5KeyFactory");
          put("Alg.Alias.SecretKeyFactory.PBEwithMD5AndDES-CBC", 
              "PBEwithMD5AndDES");

          put(PBE_KEYFACT + "3-KeyTripleDES-CBC",
              PACKAGE + "PBEwithSHAAnd3_KeyTripleDES_CBCKeyFactory");

          put(PBE_KEYFACT + "128BitRC2-CBC",
              PACKAGE + "PBEwithSHAAnd128BitRC2_CBCKeyFactory");       

          put(PBE_KEYFACT + "128BitRC4",
              PACKAGE + "PBEwithSHAAnd128BitRC4KeyFactory");       

          put(PBE_KEYFACT + "40BitRC2-CBC",
              PACKAGE + "PBEwithSHAAnd40BitRC2_CBCKeyFactory");       

          put(PBE_KEYFACT + "40BitRC4",
              PACKAGE + "PBEwithSHAAnd40BitRC4KeyFactory");       

          //Cipher algorithms
      
          put("Cipher.RC5", PACKAGE + "RC5");

          put("Cipher.RC4", PACKAGE + "RC4");

          put("Cipher.RC2", PACKAGE + "RC2");

          put("Cipher.DES", PACKAGE + "DES");

          put("Cipher.Blowfish", PACKAGE + "Blowfish");

          put("Cipher.DESede", PACKAGE + "DESede");

          put("Cipher.IDEA", PACKAGE + "IDEA");

          put("Cipher.PBEwithMD5andDES", PACKAGE + "PBEwithMD5AndDES_CBC");
          put("Alg.Alias.Cipher.PBEwithMD5AndDES-CBC", "PBEwithMD5AndDES");

          put(PBE_CIPHER + "3-KeyTripleDES-CBC", 
              PACKAGE + "PBEwithSHAAnd3_KeyTripleDES_CBC");

          put(PBE_CIPHER + "40BitRC2-CBC", 
              PACKAGE + "PBEwithSHAAnd40BitRC2_CBC");       

          put(PBE_CIPHER + "40BitRC4", PACKAGE + "PBEwithSHAAnd40BitRC4");       

          put(PBE_CIPHER + "128BitRC2-CBC", 
              PACKAGE + "PBEwithSHAAnd128BitRC2_CBC");       

          put(PBE_CIPHER + "128BitRC4", PACKAGE + "PBEwithSHAAnd128BitRC4");       

          put("Cipher.RSA", PACKAGE + "RSA");

          //put("Cipher.AES", PACKAGE + "AES");
      
          //Algorithm parameters
      
          put("AlgorithmParameters.DSA", PACKAGE + "DSAParameters");

          put("Alg.Alias.AlgorithmParameters.Diffie-Hellman", "DH");
          put("AlgorithmParameters.DH", PACKAGE + "DHParameters");

          put("AlgorithmParameters.PBEwithMD5andDES",
              PACKAGE + "PBEParameters");
          put("Alg.Alias.AlgorithmParameters.PBEwithMD5AndDES-CBC", 
              "PBEwithMD5AndDES");

          put(PBE_PARAM + "3-KeyTripleDES-CBC", PACKAGE + "PBEParameters");

          put(PBE_PARAM + "40BitRC2-CBC", PACKAGE + "PBEParameters");

          put(PBE_PARAM + "40BitRC4", PACKAGE + "PBEParameters");

          put(PBE_PARAM + "128BitRC2-CBC", PACKAGE + "PBEParameters");

          put(PBE_PARAM + "128BitRC4", PACKAGE + "PBEParameters");

          put("AlgorithmParameters.DESede/CBC", PACKAGE + "DESedeParameters");

          put("AlgorithmParameters.RC2/CBC", PACKAGE + "RC2Parameters");

          put("AlgorithmParameters.IDEA/CBC", PACKAGE + "IDEAParameters");
      
          //Algorithm parameter generators
      
          put("AlgorithmParameterGenerator.DSA",
              PACKAGE + "DSAParameterGenerator");

          put("AlgorithmParameterGenerator.DH",
              PACKAGE + "DHParameterGenerator");
          put("Alg.Alias.AlgorithmParameterGenerator.Diffie-Hellman", "DH");
          put("Alg.Alias.AlgorithmParameterGenerator.OID." + OID.dhKeyAgreement,
              "DH");
          put("Alg.Alias.AlgorithmParameterGenerator." + OID.dhKeyAgreement,
              "DH");
          put("Alg.Alias.AlgorithmParameterGenerator." + OID.dhpublicnumber,
              "DH");
          put("Alg.Alias.AlgorithmParameterGenerator." + OID.esdh, "DH");
      
          //MAC algorithms
      
          put("Mac.HMACwithMD5", PACKAGE + "HMACwithMD5");
          //put("Alg.Alias.Mac." + OID., "HMACwithMD5");

          put("Mac.HMACwithRIPEMD160", PACKAGE + "HMACwithRIPEMD160");
          //put("Alg.Alias.Mac." + OID., "HMACwithRIPEMD160");

          put("Mac.HMACwithSHA1", PACKAGE + "HMACwithSHA1");
          //put("Alg.Alias.Mac." + OID., "HMACwithSHA1");

          put("Mac.DES-MAC", PACKAGE + "DESMAC");
          //put("Alg.Alias.Mac." + OID., "HMACwithMD5");
      
          return null;
        }
      }
    );
  }
}
