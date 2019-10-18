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
 * This class specifies a Diffie-Hellman public key with 
 * its associated parameters. 
 *
 * @see java.security.Key
 * @see java.security.KeyFactory
 * @see java.security.spec.KeySpec
 * @see java.security.spec.KeySpec
 * @see java.security.spec.X509EncodedKeySpec
 * @see javax.crypto.spec.DHPrivateKeySpec
 *
 * @version 0.1, 97/11/26
 * @author Ming Yung
 */
public class DHPublicKeySpec implements KeySpec
{
  private BigInteger p, g, y;

  /**
   * Constructor that takes a public value y, a prime modulus p, and a base generator g
   */
  public DHPublicKeySpec(BigInteger y, BigInteger p, BigInteger g)
  {
    this.y = y;
    this.p = p;
    this.g = g;
  }

  /**
   * Returns the public value y.
   *
   * @return the public value y.
   */
  public BigInteger getY()
  {
    return this.y;
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
