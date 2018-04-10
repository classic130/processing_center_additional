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

package com.dstc.security.keymanage.spi;

import com.dstc.security.keymanage.spi.DSTCKeyStoreEngine;
import com.dstc.security.keymanage.spi.KeyStore;
import com.dstc.security.keymanage.keystore.P12KeyStore;

/**
 *  This class acts as a contain class so that the KeyStoreImpl(ementation)
 *  class does not need to know about SPI classes. The aim of this is to
 *  seperate the Java provider architecture from the actual implementation. <p>
 *
 *  @see java.security.KeyStore
 *  @see java.security.KeyStoreSPI
 *
 *  @author Daniel Bradley.
 *  @date 11/2/2000
 */
public class P12KeyStoreEngine extends DSTCKeyStoreEngine
{
  public P12KeyStoreEngine()
  {
    this.keyStore = (KeyStore) new P12KeyStore();
  }
}
