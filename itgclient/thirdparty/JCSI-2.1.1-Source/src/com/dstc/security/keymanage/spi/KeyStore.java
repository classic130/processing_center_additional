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

import java.io.InputStream;
import java.io.IOException;
import java.io.OutputStream;

import java.util.Date;
import java.util.Enumeration;

import java.security.Key;
import java.security.KeyStoreException;
import java.security.NoSuchAlgorithmException;
import java.security.UnrecoverableKeyException;
import java.security.cert.Certificate;
import java.security.cert.CertificateException;

/**
 *  This interface specifies those methods that are supported by the
 *  java.security.KeyStore interface. <p>
 *
 *  This interface allows other implementations to be easily used when
 *  bypassing the JDK 1.2 provider architecture. <p>
 *
 *  Usage:
 *
 *  <pre>
 *    import com.dstc.security.pkcs12.util.KeyStore;
 *    import any.KeyStoreImplementation;
 *    ...
 *    KeyStore myStore = new KeyStoreImplementation();
 *  </pre>
 *
 *  @author Daniel Bradley.
 */
public interface KeyStore
{
  public Key getKey( String alias, char[] password )
  throws KeyStoreException, NoSuchAlgorithmException, UnrecoverableKeyException;
  
  public Certificate[] getCertificateChain( String alias )
  throws KeyStoreException;
  
  public Certificate getCertificate( String alias )
  throws KeyStoreException;
  
  public Date getCreationDate( String alias )
  throws KeyStoreException;
  
  public void
  setKeyEntry( String alias, Key key, char[] passwd, Certificate[] chain )
  throws KeyStoreException;

  public void setKeyEntry( String alias, byte[] key, Certificate[] chain )
  throws KeyStoreException;
  
  public void setCertificateEntry( String alias, Certificate cert )
  throws KeyStoreException;
  
  public void deleteEntry( String alias ) throws KeyStoreException;
  
  public Enumeration aliases() throws KeyStoreException;
  
  public boolean containsAlias( String alias ) throws KeyStoreException;
    
  public int size() throws KeyStoreException;
  
  public boolean isKeyEntry( String alias ) throws KeyStoreException;
  
  public boolean isCertificateEntry( String alias ) throws KeyStoreException;
  
  public String getCertificateAlias( Certificate cert )
  throws KeyStoreException;
  
  public void store( OutputStream stream, char[] passwd )
  throws KeyStoreException, IOException,
         NoSuchAlgorithmException, CertificateException;
  
  public void load( InputStream stream, char[] passwd )
  throws KeyStoreException, IOException,
         NoSuchAlgorithmException, CertificateException;
}
