package com.dstc.security.keymanage.util;

import java.security.InvalidKeyException;
import java.security.spec.InvalidKeySpecException;
import java.security.InvalidAlgorithmParameterException;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

import javax.crypto.spec.PBEKeySpec;
import javax.crypto.spec.PBEParameterSpec;
import javax.crypto.SecretKeyFactory;
import javax.crypto.SecretKey;
import javax.crypto.spec.SecretKeySpec;

import com.dstc.security.common.OID;
import com.dstc.security.keymanage.debug.Debug;
import com.dstc.security.common.PKCS12KeyDerivation;
import com.dstc.security.common.PBEKeyDerivation;

/**
 *  This class is used by these classes to generate PKCS#12 PBEKeys.
 */
public class PKCS12KeyFactory
{
  public static final String MAC_ALGORITHM = "HMACwithSHA1";
  public static final String MD_ALGORITHM = "SHA";
  public static final String DIGEST_OID = OID.sha_1;

  private static final int HASH_LENGTH = 20;

  /**
   *  Instatiates a PBEKey from the String representation of a password. <p>
   *
   *  @param password A String the holds the password.
   *  @return a PBEKey.
   */
  /*public static SecretKey createPBEKey( String password )
  {
    Debug.log( Debug.DEBUG, "PKCS12KeyFactory.createPBEKey( String )",
        "String: " + password );
    return PKCS12KeyFactory.createPBEKey( password.toCharArray() );
  }*/
  
  /**
   *  Instantiates a PBEKey from an array of characters. <p>
   *
   *  @param password An array of characters that form a password.
   *  @return a PBEKey
   */
  public static SecretKey createPBEKey( char[] password )
  {
    Debug.log( Debug.DEBUG, "PKCS12KeyFactory.createPBEKey( char[] )",
        "CharArray: " + new String( password ) );
//    return PKCS12KeyFactory.createPBEKey( toPasswordBytes( password ) );
    //return new PBEKey( toPasswordBytes( password ) );

    try
    {
      SecretKeyFactory fact 
        = SecretKeyFactory.getInstance("PBEwithSHAand3-KeyTripleDES-CBC");
      return fact.generateSecret(new PBEKeySpec(password));
    }
    catch (NoSuchAlgorithmException e)
    {
      throw new RuntimeException("Internal error: " + e.toString());
    }
    catch (InvalidKeySpecException e)
    {
      throw new RuntimeException("Internal error: " + e.toString());
    }
  }

//   public static PBEKey createPBEKey( char[] password )
//   {
//     byte[] passwordBytes = new byte[password.length * 2 + 2];
//     for (int i = 0, j = 0; i < password.length; i++)
//     {
//       passwordBytes[j++] = (byte)((password[i] >> 8) & 0xff);
//       passwordBytes[j++] = (byte)(password[i] & 0xff);
//     }
//     passwordBytes[passwordBytes.length - 1] = 0x00;
//     passwordBytes[passwordBytes.length - 2] = 0x00;
//     return new PBEKey( passwordBytes );
//   }

//   /**
//    *  Instantiates a PBEKey using password bytes that have been represented
//    *  as specified in PKCS#12. <p>
//    *
//    *  @param password the PKCS#12 byte representation of a password.
//    *  @return a PBEKey.
//    */
//   public static PBEKey createPBEKey( byte[] password )
//   {
// System.out.println( "ByteArray: " + new String( password ) );
//     return new PBEKey( password );
//   }

//   /**
//    *  Wrapper function intended to allow user classes to not have to
//    *  include other packages. <p>
//    */
//   private static PBEKey createPBEKey( byte[] bytes )
//   {
//     return new PBEKey( bytes );
//   }

  /**
   *  Converts a character array representation of a password to the byte
   *  array representation as specified in PKCS#12. <p>
   *
   *  @param password An array of characters that form a password.
   *  @return the PKCS#12 specified byte array representation.
   */
  /*private static byte[] toPasswordBytes( char[] password )
  {
    byte[] passwordBytes = new byte[password.length * 2 + 2];
    for (int i = 0, j = 0; i < password.length; i++)
    {
      passwordBytes[j++] = (byte)((password[i] >> 8) & 0xff);
      passwordBytes[j++] = (byte)(password[i] & 0xff);
    }
    passwordBytes[passwordBytes.length - 1] = 0x00;
    passwordBytes[passwordBytes.length - 2] = 0x00;
    return passwordBytes;
  }*/

  //---------------------------------------------------------------------------
  //  MACKey Related Routines
  //---------------------------------------------------------------------------
  
  /**
   *  Generates PBEParameterSpecs that are used in the process of generating
   *  MACKeys. <p>
   *
   *  Basically retrieves salt by calling <code>generateSalt</code> and
   *  specifies a number of default iterations. <p>
   *
   *  @return a PBEParameterSpec.
   */
  public static PBEParameterSpec generatePBEParameterSpec()
  {
    byte[] salt = PKCS12KeyFactory.generateSalt();
    int iterations = 1;
    return new PBEParameterSpec( salt, iterations );
  }

  /**
   *  XXX. This needs to be written properly. <p>
   *
   *  Generates PKCS#12 salts as per specified in PKCS#5. <p>
   */
  public static byte[] generateSalt()
  {
    return "Hello".getBytes();
  }

  /**
   *  Produces a MAC <code>Key</code> by modifying key, according to PKCS#12,
   *  using the macSalt and interations parameters contained within
   *  <code>pbeSpec</code>. <p>
   *
   *  @param key The Secret Key used to produce the MAC Key.
   *  @param pbeSpec A PBEParametersSpec containing the parameters needed to
   *                 produce a MAC Key.
   *  @return A MAC Key as a Secret Key.
   */
  public static SecretKey generateMacKey( SecretKey key, PBEParameterSpec pbeSpec )
  throws InvalidKeyException
  {
    MessageDigest md = null;
    try
    {
      md = MessageDigest.getInstance( MD_ALGORITHM );
    } catch ( NoSuchAlgorithmException ex ) {
      Debug.log( Debug.DEBUG, "PKCS12KeyFactory.generateMacKey()",
          ex.toString() );
      throw new RuntimeException( ex.toString() );
    }
    PBEKeyDerivation keyDeriver = new PKCS12KeyDerivation();

    byte[] macKeyBytes = null;
    try
    {
      // XXX Why is there a constant here for the key length?
      macKeyBytes = keyDeriver.generateKey(
          PBEKeyDerivation.GENERATE_INTEGRITY_KEY_MODE,
              md, key, pbeSpec, HASH_LENGTH );
    } catch ( InvalidAlgorithmParameterException ex ) {
      Debug.log( Debug.ERROR, "PKCS12KeyFactory.generateMacKey()",
          ex.toString() );
    }

    return new SecretKeySpec( macKeyBytes, "HMAC" );
  }
}
