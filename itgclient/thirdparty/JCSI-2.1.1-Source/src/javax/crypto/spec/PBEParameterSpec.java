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

import java.security.spec.AlgorithmParameterSpec;
import java.security.InvalidAlgorithmParameterException;

/**
 * <p>This class specifies the set of parameters used with password-based
 * encryption (PBE), as defined in the PKCS #5 standard.
 *
 * @see java.security.spec.AlgorithmParameterSpec
 *
 * @version 0.98, 98/07/01
 * @author Ming Yung
 *
 */
public class PBEParameterSpec implements AlgorithmParameterSpec 
{
  private byte[] salt;
  private int ic;

  /**
   * Constructs a parameter set for password-based encryption as 
   * defined in the PKCS #5 standard
   *
   * @param salt the salt.
   * @param iterationCount the iteration count.
   */
  public PBEParameterSpec(byte[] salt, int ic) 
  {
    if (ic <=0 || salt == null)
      throw new IllegalArgumentException("Invalid PBE Parameters");
    this.salt = (byte[])salt.clone();
    this.ic = ic;
  }

  /**
   * Returns the salt.
   * @return the salt
   */
  public byte[] getSalt () 
  {
    return salt;
  }

  /**
   * Returns the iteration count.
   * @return the iteration count
   */
  public int getIterationCount () 
  {
    return ic;
  }
}
