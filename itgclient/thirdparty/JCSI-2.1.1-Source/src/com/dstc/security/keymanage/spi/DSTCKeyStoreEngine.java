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

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.Date;
import java.util.Enumeration;
import java.security.Key;
import java.security.KeyStoreSpi;
import java.security.KeyStoreException;
import java.security.NoSuchAlgorithmException;
import java.security.UnrecoverableKeyException;
import java.security.cert.Certificate;
import java.security.cert.CertificateException;

import com.dstc.security.keymanage.spi.KeyStore;

/**
 *  This class acts as a container class so that the KeyStoreImpl(ementation)
 *  class does not need to know about SPI classes. The aim of this is to
 *  seperate the Java provider architecture from the actual implementation. <p>
 *
 *  @see java.security.KeyStore
 *  @see java.security.KeyStoreSPI
 *
 *  @author Daniel Bradley.
 *  @date 11/2/2000
 */
public abstract class DSTCKeyStoreEngine extends KeyStoreSpi
{
  /**
   *  Extending classes should set this to the appropriate implementation. <p>
   */
  protected KeyStore keyStore = null;
  
  public Key engineGetKey( String alias, char[] password )
  throws NoSuchAlgorithmException, UnrecoverableKeyException
  {
    try
    {
      return this.keyStore.getKey( alias, password );
    } catch ( KeyStoreException kse ) {
      ; // When using provider it is unnecessary to throw this.
    }
    return null;
  }
  
  public Certificate[] engineGetCertificateChain( String alias )
  {
    try
    {
      return this.keyStore.getCertificateChain( alias );
    } catch ( KeyStoreException kse ) {
      ; // When using provider it is unnecessary to throw this.
    }
    return null;
  }
  
  public Certificate engineGetCertificate( String alias )
  {
    try
    {
      return this.keyStore.getCertificate( alias );
    } catch ( KeyStoreException kse ) {
      ; // When using provider it is unnecessary to throw this.
    }
    return null;
  }
  
  public Date engineGetCreationDate( String alias )
  {
    try
    {  
      return this.keyStore.getCreationDate( alias );
    } catch ( KeyStoreException kse ) {
      ; // When using provider it is unnecessary to throw this.
    }
    return null;
  }
  
  public void
  engineSetKeyEntry( String alias, Key key, char[] passwd, Certificate[] chain )
  throws KeyStoreException
  {
    try
    {
      this.keyStore.setKeyEntry( alias, key, passwd, chain );
    } catch ( KeyStoreException kse ) {
      ; // When using provider it is unnecessary to throw this.
    }

  }

  public void engineSetKeyEntry( String alias, byte[] key, Certificate[] chain )
  throws KeyStoreException
  {
    try
    {
      this.keyStore.setKeyEntry( alias, key, chain );
    } catch ( KeyStoreException kse ) {
      ; // When using provider it is unnecessary to throw this.
    }
  }

  public void engineSetCertificateEntry( String alias, Certificate cert )
  throws KeyStoreException
  {
    try
    {
      this.keyStore.setCertificateEntry( alias, cert );
    } catch ( KeyStoreException kse ) {
      ; // When using provider it is unnecessary to throw this.
    }
  }
  
  public void engineDeleteEntry( String alias ) throws KeyStoreException
  {
    try
    {
      this.keyStore.deleteEntry( alias );
    } catch ( KeyStoreException kse ) {
      ; // When using provider it is unnecessary to throw this.
    }
  }
  
  public Enumeration engineAliases()
  {
    try
    {
      return this.keyStore.aliases();
    } catch ( KeyStoreException kse ) {
      ; // When using provider it is unnecessary to throw this.
    }
    return null;
  }
  
  public boolean engineContainsAlias( String alias )
  {
    try
    {
      return this.keyStore.containsAlias( alias );
    } catch ( KeyStoreException kse ) {
      ; // When using provider it is unnecessary to throw this.
    }
    return false;
  }
  
  public int engineSize()
  {
    try
    {
      return this.keyStore.size();
    } catch ( KeyStoreException kse ) {
      ; // When using provider it is unnecessary to throw this.
    }
    return 0;
  }
  
  public boolean engineIsKeyEntry( String alias )
  {
    try
    {
      return this.keyStore.isKeyEntry( alias );
    } catch ( KeyStoreException kse ) {
      ; // When using provider it is unnecessary to throw this.
    }
    return false;
  }
  
  public boolean engineIsCertificateEntry( String alias )
  {
    try
    {
      return this.keyStore.isCertificateEntry( alias );
    } catch ( KeyStoreException kse ) {
      ; // When using provider it is unnecessary to throw this.
    }
    return false;
  }
  
  public String engineGetCertificateAlias( Certificate cert )
  {
    try
    {
      return this.keyStore.getCertificateAlias( cert );
    } catch ( KeyStoreException kse ) {
      ; // When using provider it is unnecessary to throw this.
    }
    return null;
  }
  
  public void engineStore( OutputStream stream, char[] passwd )
  throws IOException, NoSuchAlgorithmException, CertificateException
  {
    try
    {
      this.keyStore.store( stream, passwd );
    } catch ( KeyStoreException kse ) {
      ; // When using provider it is unnecessary to throw this.
    }
  }
  
  public void engineLoad( InputStream stream, char[] passwd )
  throws IOException, NoSuchAlgorithmException, CertificateException
  {
    try
    {
      this.keyStore.load( stream, passwd );
    } catch ( KeyStoreException kse ) {
      ; // When using provider it is unnecessary to throw this.
    }
  }
}
