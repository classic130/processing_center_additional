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

import java.math.BigInteger;
import java.security.spec.KeySpec;

/**
 * <p>This class specifies a Diffie-Hellman private key with 
 * its associated parameters. 
 *
 * @see java.security.Key
 * @see java.security.KeyFactory
 * @see java.security.spec.KeySpec
 * @see java.security.spec.PKCS8EncodedKeySpec
 * @see javax.crypto.spec.DHPublicKeySpec
 *
 * @version 0.1, 97/11/26
 * @author Ming Yung
 */
public class DHPrivateKeySpec implements KeySpec
{
  private BigInteger p, g, x;

  /**
   * Constructor that takes a private value x, a prime modulus p, and 
   * a base generator g
   */
  public DHPrivateKeySpec(BigInteger x, BigInteger p, BigInteger g)
  {
    this.x = x;
    this.p = p;
    this.g = g;
  }

  /**
   * Returns the private value x.
   *
   * @return the private value x.
   */
  public BigInteger getX()
  {
    return this.x;
  }

  /**
   * Returns the prime modulus p.
   *
   * @return the prime modulus p.
   */
  public BigInteger getP()
  {
    return this.p;
  }

  /**
   * Returns the base generator g.
   *
   * @return the base generator g.
   */
  public BigInteger getG()
  {
    return this.g;
  }
}
