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

import java.security.spec.KeySpec;

/**
 * <p>A user-chosen password that can be used with password-based
 * encryption.
 *
 * <p>The password can be viewed as some kind of raw key material, from
 * which the encryption mechanism to which it is passed derives a
 * cryptographic key.
 *
 * <p>Different PBE mechanisms may consume different bits of each password 
 * character. For example, the PBE mechanism defined in PKCS #5 looks 
 * at only the low order 8 bits of each character, whereas PKCS #12 looks 
 * at all 16 bits of each character. 
 *
 * <p>You convert the password characters to a PBE key by creating an 
 * instance of the appropriate secret-key factory. For example, a secret-key 
 * factory for PKCS #5 will construct a PBE key from only the low order 8 bits 
 * of each password character, whereas a secret-key factory for PKCS #12 will 
 * take all 16 bits of each character. 
 *
 * <p>Also note that this class stores passwords as char arrays instead of 
 * String objects (which would seem more logical), because the String class 
 * is immutable and there is no way to overwrite its internal value when the 
 * password stored in it is no longer needed. Hence, this class requests the 
 * password as a char array, so it can be overwritten when done. 
 *
 * <p>See PKCS#5: Password-Based Encryption Standard for more details on
 * password-based encryption.
 *
 * @see javax.crypto.SecretKeyFactory
 * @see javax.crypto.spec.PBEParameterSpec
 *
 * @version 0.98, 98/07/01
 * @author Ming Yung
 *
 */
public class PBEKeySpec implements KeySpec 
{
  private char[] password;

  /**
   * Constructor that takes a password.
   * 
   * @param password the password used for password-based encryption
   */
  public PBEKeySpec(char[] password) 
  {
    this.password = (char[])password.clone();
  }

  /**
   * Retrieves the password.
   *
   * @return the password
   */
  public char[] getPassword()
  {
    return password;
  }
}
