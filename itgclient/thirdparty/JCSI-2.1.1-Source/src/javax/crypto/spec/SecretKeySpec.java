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

package javax.crypto.spec;

import java.util.Arrays;
import java.security.spec.KeySpec;

import javax.crypto.SecretKey;

/**
 * <p>This class specifies a secret key in a provider-independent fashion. 
 *
 * <p>It can be used to construct a SecretKey from a byte array, without 
 * having to go through a (provider-based) SecretKeyFactory. 
 *
 * <p> This class is only useful for raw secret keys that can be represented 
 * as a byte array and have no key parameters associated with them, e.g., 
 * DES or Triple DES keys.
 *
 * @see java.security.Key
 * @see java.security.KeyFactory
 *
 * @version 0.98, 98/07/01
 * @author Ming Yung
 *
 */
public class SecretKeySpec implements KeySpec, SecretKey
{
  private String algorithm;
  private byte keyMaterial[];

  /**
   * Constructs a secret key from the given byte array. 
   *
   * <p>This constructor does not check if the given bytes indeed specify 
   * a secret key of the specified algorithm. For example, if the algorithm 
   * is DES, this constructor does not check if key is 8 bytes long, and 
   * also does not check for weak or semi-weak keys. In order for those 
   * checks to be performed, an algorithm-specific key specification class
   * (in this case: DESKeySpec) must be used.
   *
   * @param key the key material of the secret key.
   * @param algorithm the name of the associated algorithm.
   */
  public SecretKeySpec(byte[] key, String algorithm)
  {
    this(key, 0, key.length, algorithm);
  }

  /**
   * Constructs a secret key from the given byte array, using the first 
   * len bytes of key, starting at offset. 
   *
   * <p>This constructor does not check if the given bytes indeed specify a 
   * secret key of the specified algorithm. For example, if the algorithm 
   * is DES, this constructor does not check if key is 8 bytes long, and 
   * also does not check for weak or semi-weak keys. In order for those 
   * checks to be performed, an algorithm-specific key specification class
   * (in this case: DESKeySpec) must be used.
   *
   * @param key the key material of the secret key.
   * @param offset the offset in key where the key material starts.
   * @param len the length of the key material.
   * @param algorithm the standard name of the associated key
   * algorithm. See Appendix A in the Java Cryptography
   * Extension API Specification & Reference for information
   * about standard algorithm names.
   */
  public SecretKeySpec(byte[] key, int offset, int len, String algorithm)
  {
    if (key.length - offset < len)
      throw new RuntimeException("Key too short");

    this.algorithm = algorithm;
    this.keyMaterial = new byte[len];
    System.arraycopy(key, offset, keyMaterial, 0, len);
  }

  /**
   * Returns the name of the algorithm associated with this secret key.
   *
   * @return the secret key algorithm.
   */
  public java.lang.String getAlgorithm()
  {
    return algorithm;
  }

  /**
   * Returns the name of the encoding format for this secret key.
   *
   * @return the string "RAW".
   */
  public String getFormat()
  {
    return "RAW";
  }

  /**
   * Returns the key material of this secret key.
   *
   * @return the key material
   */
  public byte[] getEncoded()
  {
    return keyMaterial;
  }

  /**
   * Calculates a hash code value for the object. 
   * Objects that are equal will also have the same hashcode.
   */
  public int hashCode()
  {
    int retval = 0;
    int shift = 0;
    for (int i=0; i<this.keyMaterial.length; i++)
    {
      retval ^= (int)(this.keyMaterial[i] << 8*shift);
      shift++;
      if (shift == 4)
        shift = 0;
    }
    return retval;
  }

  /**
   * Overides equals() in Object superclass
   */
  public boolean equals(Object obj)
  {
    if (!(obj instanceof SecretKeySpec))
      return false;

    if (!this.algorithm.equals(((SecretKeySpec)obj).algorithm))
      return false;

    return Arrays.equals(keyMaterial, ((SecretKeySpec)obj).keyMaterial);
  }
}
