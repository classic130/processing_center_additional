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

package com.dstc.security.keymanage.keystore;

import java.io.FileOutputStream;
import java.io.InputStream;
import java.io.IOException;
import java.io.OutputStream;

import java.util.Date;
import java.util.Enumeration;
import java.util.HashSet;
import java.util.Vector;
import java.util.StringTokenizer;

import java.security.InvalidKeyException;
import java.security.PrivateKey;
import java.security.Principal;
import java.security.Key;
import java.security.KeyStoreException;
import java.security.KeyStoreSpi;
import java.security.NoSuchAlgorithmException;
import java.security.UnrecoverableKeyException;
import java.security.cert.Certificate;
import java.security.cert.CertificateException;
import java.security.cert.CertificateEncodingException;
import java.security.cert.X509Certificate;
import java.security.spec.InvalidKeySpecException;

import javax.crypto.SecretKey;
import javax.crypto.spec.PBEKeySpec;
import javax.crypto.spec.PBEParameterSpec;

import com.dstc.security.asn1.Asn1;
import com.dstc.security.asn1.Asn1DecodingException;
import com.dstc.security.asn1.Asn1EncodingException;
import com.dstc.security.asn1.Asn1Exception;
import com.dstc.security.common.Attribute;
import com.dstc.security.common.FriendlyName;
import com.dstc.security.common.OID;
import com.dstc.security.common.X500Name;
import com.dstc.security.certpath.CertPathBuilder;
import com.dstc.security.certpath.X509CertSelector;
import com.dstc.security.keymanage.debug.Debug;

import com.dstc.security.keymanage.PKCS8EncryptedPrivateKey;
import com.dstc.security.keymanage.PKCS8Exception;
import com.dstc.security.keymanage.pkcs12.AuthenticatedSafe;
import com.dstc.security.keymanage.pkcs12.InvalidFlagException;
import com.dstc.security.keymanage.pkcs12.PFX;
import com.dstc.security.keymanage.pkcs12.SafeBag;
import com.dstc.security.keymanage.pkcs12.bags.CertBag;
import com.dstc.security.keymanage.pkcs12.bags.KeyBag;
import com.dstc.security.keymanage.pkcs12.bags.ShroudedKeyBag;
import com.dstc.security.keymanage.keystore.BagHandler;
import com.dstc.security.keymanage.keystore.NetscapeBagHandler;
//import com.dstc.security.keymanage.spi.KeyStore;
import com.dstc.security.keymanage.util.PKCS12KeyFactory;


/**
 *  Key Store implememtation using com.dstc.security.PKCS12 classes. <p>
 *
 *  This class is intended to be used as a KeyStore when bypassing the
 *  JDK 1.2 provider architecture. <p>
 *
 *  Using provider architecture:
 *
 *  <pre>
 *    import java.security.KeyStore;
 *    ...
 *    KeyStore myStore = KeyStore.getIntstance( "DSTC" );
 *  </pre>
 *
 *  Without provider architecture: <p>
 *
 *  <pre>
 *    import com.dstc.security.pkcs12.util.KeyStore;
 *    import com.dstc.security.pkcs12.util.KeyStoreImpl;
 *    ...
 *    KeyStore myStore = new KeyStoreImpl();
 *  </pre>
 *
 *  Further usage is the same as the JDK class. <p>
 *
 *  @author Daniel Bradley.
 */
//public class P12KeyStore implements KeyStore
public class P12KeyStore extends KeyStoreSpi
{
  /**
   *  This specifies the encryption algorithm that is used to encrypt
   *  Private Keys. <p>
   */
  public static String DEFAULT_ENCRYPTION_ALGORITHM = 
      OID.pbeWithSHAAnd3_KeyTripleDES_CBC;

  /**
   *  The PFX object that is encoded/decoded to/from
   *  OutputStream/InputStream. <p>
   *
   *  pfx is only not null if the KeyStore does not require re-ecoding. If
   *  a KeyStore has not been loaded, if a new KeyStore has not been saved,
   *  or if a KeyStore has been modified, pfx will be null. <p>
   */
  private PFX pfx = null;
  
  /**
   *  The bagHandler takes care of appropriately storing bags in an
   *  AuthenticatedSafe object. <p>
   *
   *  Bag Handler is also used to tracks whether or not the KeyStore is
   *  considered to be initialized. If null uninitialized. <p>
   */
  private BagHandler bagHandler = null;

  private Vector tmpChainStore = new Vector();

  //---------------------------------------------------------------------------
  //  Constructor(s)
  //---------------------------------------------------------------------------
  public P12KeyStore()
  {}

  //---------------------------------------------------------------------------
  //  Load/Store Methods
  //---------------------------------------------------------------------------

  /**
   *
   *  Produces a PBEKey by:
   *  <pre>
   *    String s = new String( passwd );
   *    byte[] passbytes = s.getBytes();
   *    PBEKey key = new PBEKey( passbytes );
   *  </pre>
   */
  public void engineLoad( InputStream stream, char[] passwd )
  throws IOException, NoSuchAlgorithmException, CertificateException
  {
    Debug.log( Debug.DEBUG, "P12KeyStore.load()", "" );
  
    if ( stream == null )
    {
      this.bagHandler = new NetscapeBagHandler();
    }
    else {
    
      try
      {
        this.pfx = PFX.createPFX( stream );
      }
      catch ( Asn1DecodingException ex ) {
        throw new IOException( ex.toString() );
      }
      catch ( Asn1Exception ex ) {
        throw new IOException( ex.toString() );
      }
      catch (Exception ex ) {
        throw new IOException( " bad pkcs12 data" );
      }

      SecretKey key = null;
      // Use passwd to verify integrity of PFX.
      if ( passwd != null )
      {
        try
        {
          key = PKCS12KeyFactory.createPBEKey( passwd );
          if (!this.pfx.verify( key ))
          {
              throw new InvalidKeyException();
          }
        }
        catch ( InvalidKeyException ex ) {
          throw new IOException(
              "KeyStore Integrity Compromised: " + ex.toString() );
        }
      }

      //  Create a NetscapeBagHandler, set the PBEKey (null if passwd == null),
      //  and import the AuthenticatedSafe.
      //
      this.bagHandler = new NetscapeBagHandler();
      this.bagHandler.setPassword( passwd );
    
      try
      {
        AuthenticatedSafe authSafe = this.pfx.getAuthSafe();
        this.bagHandler.importBags( authSafe );
      }
      catch ( Asn1Exception ex ) {
        throw new CertificateException( ex.toString() );
      }
    }
  }

  /**
   *  Encodes the KeyStore as a PKCS#12 file to the OutputStream. <p>
   */
  public void engineStore( OutputStream stream, char[] passwd )
  throws IOException, NoSuchAlgorithmException, CertificateException
  {
    Debug.log( Debug.DEBUG, "KeyStoreImpl.store()", "" );

    this.isInitialized();

    if ( this.pfx == null )
    {
      // Extracts all the SafeContents and Bags from AuthenticatedSafe and
      // creates a new one with only two SafeContents in it.
      // For compatibility with Netscape.
      //
      // XXX Algorithm Name Hardcoded. This should be defined somewhere
      // else.

      // AuthenticatedSafe authSafe = this.bagHandler.export( "RC4", passwd );
      // AuthenticatedSafe authSafe = this.bagHandler.export( null, null );
      AuthenticatedSafe authSafe = this.bagHandler.export();

      this.pfx = new PFX( authSafe );

      try
      {
        SecretKey key = PKCS12KeyFactory.createPBEKey( passwd );
        PBEParameterSpec paramSpec =
            PKCS12KeyFactory.generatePBEParameterSpec();
        this.pfx.mac( key, paramSpec, PFX.NETSCAPE_COMPATIBLE );
//      this.pfx.mac( key, paramSpec, PFX.MICROSOFT_COMPATIBLE );
      }
      catch ( InvalidFlagException ex ) {
        // Will never occur.
        //System.exit( -1 );
        throw new IOException(
            "Internal Error While Creating PBEKey: " + ex.toString() );
      }
      catch ( InvalidKeyException ex ) {
        throw new IOException(
            "Exception While Creating PBEKey: " + ex.toString() );
      }
    }
    try
    {
      this.pfx.encode( stream );
    }
    catch ( Asn1EncodingException ex )
    {
      throw new IOException(
          "Exception while encoding PFX to ASN.1: " + ex.toString() );
    }
  }

  //---------------------------------------------------------------------------
  //  Retrieve Methods
  //---------------------------------------------------------------------------

  public Key engineGetKey( String alias, char[] password )
  throws NoSuchAlgorithmException, UnrecoverableKeyException
  {
    Debug.log( Debug.DEBUG, "KeyStoreImpl.getKey()", "" );
    this.isInitialized(); // Throws KeyStoreException.
    
    SafeBag[] safebags = this.bagHandler.getBags( alias );
    if ( 0 == safebags.length )
    {
      throw new UnrecoverableKeyException( "Key Not Present" );
    }
    // safebags.length should be = 1

    for ( int i=0; i < safebags.length; i++ )
    {
      if ( safebags[i].getBagId().equals( ShroudedKeyBag.SHROUDED_KEYBAG ) )
      {
        ShroudedKeyBag skb = (ShroudedKeyBag) safebags[i].getBag();
        PKCS8EncryptedPrivateKey encryptedKey 
                      = skb.getEncryptedPrivateKeyInfo();
        try
        {
          PBEKeySpec keySpec = new PBEKeySpec( password );
          encryptedKey.decrypt( keySpec );
          return encryptedKey.getPrivateKey();
        }
        catch ( PKCS8Exception ikse ) {
          // If PBEKeySpec cannot make a proper key then we 
          // cannot recover the key.
          throw new UnrecoverableKeyException( ikse.toString() );
        }
      }
      else    // it's a normal KeyBag
      {
        KeyBag kb = (KeyBag) safebags[i].getBag();
        try { 
            return kb.getPrivateKey();
        }
        catch(InvalidKeySpecException e) { 
          throw new UnrecoverableKeyException(e.getMessage());
        }
      }
    }
    return null;
   
  }
  
  public Certificate[] engineGetCertificateChain( String alias )
  {
    Debug.log(
        Debug.DEBUG, "KeyStore.getCertificateChain( " + alias + " )", "" );

    this.isInitialized();

    Vector chain = new Vector();
    
  /*SafeBag[] safeBags = this.bagHandler.getBags( alias );
    for ( int i=0; i < safeBags.length; i++ )
    {
      try
      {
        CertBag certBag = (CertBag) safeBags[i].getBag();
        chain.add( (X509Certificate) certBag.getCertificate() );
      }
      catch ( ClassCastException ex ) {
        // Happens if there is a PrivateKey stored with the same alias
        // as the Certificate chain that validates it. ie dont worry.
      }
    }*/



/*  // XXX: Begin hack
    //
    SafeBag[] safebags = this.bagHandler.getBags( alias );
    if ( 0 == safebags.length )
    {
      throw new KeyStoreException( "Key Not Present" );
    }
 
    SafeBag skSafeBag = null;
    for ( int i=0; i < safebags.length; i++ )
    {
      if ( safebags[i].getBagId().equals( ShroudedKeyBag.SHROUDED_KEYBAG ) )
      {
        skSafeBag = safebags[i];
        break;
      }
      throw new KeyStoreException( "Key Unprotected or Nonexistant" );
    } 
    CertBag cb=null;
    try {
      cb = (CertBag) ((NetscapeBagHandler)this.bagHandler).getBag(skSafeBag.getLocalKeyId()).getBag(); 
    }
    catch(IOException e) {}

    chain.add((X509Certificate) cb.getCertificate() );
    // XXX:end Hack
    //*/
    X509Certificate[] x509s = 
          ((NetscapeBagHandler)this.bagHandler).getChain(alias);
//  chain.copyInto( x509s );
    return x509s;
  }

  public Certificate engineGetCertificate( String alias )
  {
    Debug.log( Debug.DEBUG, "KeyStore.getCertificate()", "" );

    this.isInitialized();

    SafeBag[] safebags = this.bagHandler.getBags( alias );

    CertBag certbag = null;

    for ( int i=0; i < safebags.length; i++ )
    {
      try
      {
        certbag = (CertBag) safebags[i].getBag();
        break;
      }
      catch ( ClassCastException ex ) {
        // Ignore
      }
    }
    Certificate x509 = null;
    if ( certbag != null )
    {
      x509 = certbag.getCertificate();
    }
    else {
      X509Certificate[] certs = ((NetscapeBagHandler)this.bagHandler).getChain(alias);
      if (certs != null) {
          x509 = certs[0];
      }
    }
    return x509;
  }
  
  /**
   *  Not supported. <p>
   *
   *  I do not think its possible to store a creation date in a keystore
   *  unless you embed it into a private bag. <p>
   */
  public Date engineGetCreationDate( String alias )
  {
    Debug.log( Debug.DEBUG, "KeyStore.getCreationDate()", "" );

    isInitialized();
    
//  throw new RuntimeException( "getCreationDate() not implemented" );
    return new Date();

    // I think that I made this return a new Date so that it would work
    // with Sun's Java keytool.
  }

  //---------------------------------------------------------------------------
  //  Modifier Methods
  //---------------------------------------------------------------------------

  /**
   *  NOTE. XXX Only supports X509Certificates.
   *
   *  @param alias The friendly-name to use to store these objects.
   *  @param key A PrivateKey to store.
   *  @param passwd A passwd which will be used to shroud the PrivateKey.
   *  @param chain A certificate chain related to this key.
   *  @throws KeyStoreException If KeyStore has not been loaded (initialized).
   */  
  public void
  engineSetKeyEntry( String alias, Key key, char[] passwd, Certificate[] chain )
  throws KeyStoreException
  {
    Debug.log( Debug.DEBUG, "KeyStore.setKeyEntry( Key )", "" );

    isInitialized();

    if ( (chain == null) || (chain.length == 0) )
    {
      throw new KeyStoreException(
          "Invalid Certificate Chain" );
    }
    //verifyChain(chain);

    this.pfx = null;

    //  Use the alias and cert chain to create FriendlyName and
    //  LocalKeyId attributes.
    //
    Vector attributes = createSafeBagAttributes( alias, chain );

    //  Create a ShroudedKeyBag that has the private key encrypted with
    //  the provided passwd.
    //
    ShroudedKeyBag skb = null;
    try
    {
      PrivateKey privatekey = (PrivateKey) key;
      PKCS8EncryptedPrivateKey p8 = new PKCS8EncryptedPrivateKey(
          privatekey, DEFAULT_ENCRYPTION_ALGORITHM );
      p8.encrypt( passwd );
      skb = new ShroudedKeyBag( p8 );
    }
    catch ( PKCS8Exception e ) {
      throw new KeyStoreException( "Encryption error: " + e.getMessage() );
    }
    catch ( ClassCastException cce ) {
      throw new KeyStoreException( "Not Private Key: " + cce.toString() );
    }

    // Create an array of SafeBags and pass them to BagHandler.
    //
    SafeBag[] bags = new SafeBag[ 1 ];
    bags[ 0 ] = new SafeBag( skb, attributes );
  /*byte[] lkid=null;
    try {
        lkid = bags[0].getLocalKeyId();
    }
    catch(IOException e) {
        throw new RuntimeException();
    }*/

    // Add them all to a SafeContents.
    this.bagHandler.storeBags( bags );

    int len = chain.length-1;

    // Store the Certificate as well.
    if (len == 0) {  // this is a self-signed cert
      this.addCertEntry( alias, chain[0], true , false, true);
    }
    else {
      this.addCertEntry( alias, chain[0], true , false, false);
    }

    for (int i=1; i<len; i++)
    {
//    this.addCertEntry( alias + String.valueOf(i), chain[i], false );
      this.addCertEntry( alias, chain[i], false, false, false);
    }
    // final one
    if (len > 0) 
    {
    this.addCertEntry( alias, chain[len], false, false, true);
    }
  }

  public void
  engineSetKeyEntry( String alias, byte[] key, Certificate[] chain )
  throws KeyStoreException
  {
    Debug.log( Debug.DEBUG, "KeyStore.setKeyEntry( byte[] )", "" );

    this.pfx = null;

    if ( (chain == null) || (chain.length == 0) )
    {
      throw new KeyStoreException( "Invalid Certificate Chain" );
    }
    //verifyChain(chain);

    PKCS8EncryptedPrivateKey p8 = null;
    try
    {
      p8 = new PKCS8EncryptedPrivateKey( key );
    }
    catch ( PKCS8Exception ex )
    {
      throw new KeyStoreException(
          "Invalid Encrypted Private Key: " + ex.toString() );
    }
    ShroudedKeyBag skb = new ShroudedKeyBag( p8 );

    Vector attributes = createSafeBagAttributes( alias, chain );
    SafeBag bag = new SafeBag( skb, attributes );
  /*byte[] lkid=null;
    try {
        lkid = bag.getLocalKeyId();
    }
    catch(IOException e) {
        throw new RuntimeException();
    }*/

    this.bagHandler.storeBag( bag );
    int len = chain.length-1;

    if (len == 0) {  // this is a self-signed cert
      this.addCertEntry( alias, chain[0], true , false, true);
    }
    else {
      this.addCertEntry( alias, chain[0], true , false, false);
    }


    for (int i=1; i< len; i++)
    {
//    this.addCertEntry( alias + String.valueOf(i), chain[i], false );
      this.addCertEntry( alias, chain[i], false, false, false);
    }
    // final one
    if (len > 0)
    {
        this.addCertEntry( alias, chain[len], false, false, true );
    }
  }

  /**
   *  Only supports X509Certificates. <p>
   *
   *  @param cert An X509Certificate.
   *  @throws KeyStoreException.
   */
  public void engineSetCertificateEntry( String alias, Certificate cert )
  throws KeyStoreException
  {
    if (engineIsCertificateEntry(alias)) {
        this.bagHandler.removeBags( alias );
    }
    else if (engineIsKeyEntry(alias)) {
        throw new KeyStoreException("Alias " + alias + " is a key entry" +
               " in this KeyStore");
    }
    addCertEntry(alias, cert, false, true, false);
  }

  private void addCertEntry(String alias, Certificate cert, boolean 
         includeLocalKeyId, boolean isTrusted, boolean isFinal)
  throws KeyStoreException
  {
    Debug.log( Debug.DEBUG, "KeyStore.setCertificateEntry()", "" );

    isInitialized();
    this.pfx = null;

    // Check if this alias is already assigned to a trusted certificate.
    //if ( !isKeyEntry( alias ) )
    if ( true )
    {
      // Create a friendly-name attribute using alias that will identify
      // these bags.
      Vector attributes = new Vector();
      if (isTrusted) {
          attributes.add( SafeBag.createFriendlyName( alias ) );
      }

      if (includeLocalKeyId)
      {
        try
        {
          byte[] thumb = cert.getEncoded();
          attributes.add( SafeBag.createLocalKeyId( thumb ) );
        }
        catch ( CertificateEncodingException ex )
        {
          throw new KeyStoreException( ex.toString() );
        }
      }
  
      SafeBag safebag = null;
      CertBag certbag = null;
      try
      {
        certbag = new CertBag( CertBag.X509_CERTIFICATE, cert );
        safebag = new SafeBag( certbag, attributes );
      }
      catch ( CertificateEncodingException ex ) {
        // This should not happen as cert should be good!
        Debug.log( Debug.ERROR, "P12KeyStore.setCertificateEntry()",
            "Unexpected exception while creating CertBag: " + ex.toString() );
        throw new KeyStoreException( ex.toString() );
      }
      catch ( CertificateException ex ) {
        // XXX Only supports X509Certificates at the moment.
        throw new KeyStoreException( ex.toString() );
      }

      if (isTrusted) {
          this.bagHandler.storeBag( safebag );
      }
      else {
          tmpChainStore.add(safebag);
          if (isFinal){
              ((NetscapeBagHandler)this.bagHandler).storeChain(
                                    alias, tmpChainStore);
              tmpChainStore = new Vector();     // get ready for next one
          }
      }

      Debug.dumpAsn1To( safebag.getAsn1(), Debug.SAFEBAG_W_CERTBAG );

      //if ( true )
      //{
      //  try
      //  {
      //    Asn1 asn1 = safebag.getAsn1();
      //    byte[] bytes = asn1.getEncoded();
      //    OutputStream fos = new FileOutputStream( "Cert.SafeBag.bytes.2" );
      //    fos.write( bytes );
      //    fos.close();
      //  } catch ( Exception ex ) {
      //    System.exit(1);
      //  }
      //}
    }
  }
  
  public void engineDeleteEntry( String alias ) throws KeyStoreException
  {
    Debug.log( Debug.DEBUG, "KeyStore.deleteEntry()", "" );

    this.isInitialized();
    this.pfx = null;
    
    this.bagHandler.removeBags( alias );
  }

  //---------------------------------------------------------------------------
  //  Queries
  //---------------------------------------------------------------------------
  
  public Enumeration engineAliases()
  {
    Debug.log( Debug.DEBUG, "KeyStore.aliases()", "" );

    this.isInitialized(); // throws KeyStoreException.
   
    //HashSet myset = new HashSet();
    Vector vect = new Vector();
    String[] names = this.bagHandler.getAllFriendlyNames();
    for ( int i=0; i < names.length; i++ )
    {
      //myset.add( names[i] );
      vect.add( names[i] );
    }

    //Vector vect = new Vector();
    //vect.addAll( myset );
    return vect.elements();
  }
  
  public boolean engineContainsAlias( String alias )
  {
    Debug.log(
        Debug.DEBUG, "KeyStore.containsAlias( " + alias + " )", "" );

    this.isInitialized();
    
    SafeBag bag = this.bagHandler.getBag( alias );
    if ( bag == null )
    {
      return false;
    }  else {
      return true;
    }
  }
  
  public int engineSize()
  {
    Debug.log( Debug.DEBUG, "KeyStore.size()", "" );

    this.isInitialized();
    
    return this.bagHandler.size();
  }
  
  /**
   *  A key entry is characterized by the fact that there is a key and
   *  a group of certificates all sharing the same alias. If we can
   *  find a key, there must be a key entry. <p>
   */
  public boolean engineIsKeyEntry( String alias )
  {
    Debug.log( Debug.DEBUG, "KeyStore.isKeyEntry( " + alias + " )", "" );

    this.isInitialized();
    
    SafeBag[] bags = this.bagHandler.getBags( alias );
    for ( int i=0; i < bags.length; i++ )
    {
      String id = bags[i].getBagId();
      int hash = id.hashCode();
      if ( hash == SafeBag.KEYBAG )
      {
        return true;
      }
      else if ( hash == SafeBag.SHROUDED_KEYBAG )
      {
        return true;
      }
    }
    // If no bags have triggered true return false.
    return false;
  }
  
  /**
   *  A certificate entry is characterized by the fact that there are
   *  certificates associated with the alias, but no keys. <p>
   *
   *  So an entry is a certificate entry if we can find a certificate but
   *  cannot find a key. Hence:
   *
   *  <pre>
   *  A bags, E certbag | certbag.fn == alias * !E keybag.fn == alias
   *  </pre>
   *
   *  True if: for all SafeBags, there exists a CertBag, such that its
   *  friendly-name equals alias, if there does not exist a key whose
   *  friendly_name equals alias. <p>
   *
   *  I'm not sure if this is different to a Trusted Certificate Entry. <p>
   */
  public boolean engineIsCertificateEntry( String alias )
  {
    Debug.log( Debug.DEBUG, "KeyStore.isCertificateEntry()", "" );

    this.isInitialized();
    
    boolean certEntry = false;
    
    SafeBag[] bags = this.bagHandler.getBags( alias );
    for ( int i=0; i < bags.length; i++ )
    {
      String id = bags[i].getBagId();
      int hash = id.hashCode();
      if ( hash == SafeBag.CERTBAG )
      {
        certEntry = true;
      }
      else if ( hash == SafeBag.KEYBAG )
      {
        return false;
      }
      else if ( hash == SafeBag.SHROUDED_KEYBAG )
      {
        return false;
      }
    }
    return certEntry;
  }
  
  public String engineGetCertificateAlias( Certificate cert )
  {
    Debug.log( Debug.DEBUG, "KeyStore.getCertificateAlias()", "" );

    isInitialized();

    String alias = null;
    SafeBag[] safebags = this.bagHandler.getAllBags();
    CertBag certbag = null;
    Certificate other = null;
    for ( int i=0; i < safebags.length; i++ )
    {
      String type = safebags[i].getBagId();
      int hash = type.hashCode();
      if ( hash == SafeBag.CERTBAG )
      {
        certbag = (CertBag) safebags[i].getBag();
        other = certbag.getCertificate();
        if ( certEquals( (X509Certificate)other, (X509Certificate)cert ) )
        {
          alias = safebags[i].getFriendlyName();
          break;
        }
      }
      else if ((hash == SafeBag.SHROUDED_KEYBAG) || (hash == SafeBag.KEYBAG))
      {
        String keyFN = safebags[i].getFriendlyName();
        X509Certificate[] chain = ((NetscapeBagHandler) 
                                    this.bagHandler).getChain(keyFN);
        // Only need to check the first cert in the chain
        if (certEquals((X509Certificate)chain[0],(X509Certificate) cert))
        {
          alias = keyFN;
          break;
        } 
      }
    }
    return alias;
  }

  //---------------------------------------------------------------------------
  //  Extra Methods
  //---------------------------------------------------------------------------

//  private void removeCertBags( String alias )
//  {
//    SafeBag[] bags = this.bagHandler.getBags( alias );
//    if (
    

  private void isInitialized()
  {
    if ( this.bagHandler == null )
    {
      throw new RuntimeException( "Operation On Uninitialized KeyStore" );
    }
  }

  private static Vector
  createSafeBagAttributes( String alias, Certificate[] chain )
  throws KeyStoreException
  {
    // Create a friendly-name attribute using alias that will identify
    // these bags.
    Vector attributes = new Vector();

    attributes.add( new FriendlyName( alias ) );

    try
    {
      byte[] thumb = chain[0].getEncoded();
      attributes.add( SafeBag.createLocalKeyId( thumb ) );
    }
    catch ( CertificateEncodingException ex )
    {
      throw new KeyStoreException( ex.toString() );
    }
    return attributes;
  }

  /*
   *   Extract the Attribute value CN from a cert's SubjectDN.
   *   If such an attribute is null, then return OU. If OU is
   *   also null, return the DN as a string.
   */

  private String getCN(X509Certificate cert)
  {
    Principal dn = cert.getSubjectDN();
    String s = dn.getName();
    StringTokenizer tknz = new StringTokenizer(s, ",", false);
    String CNString = null;
    String OUString = null;
    String current = null;
    while (tknz.hasMoreTokens())
    {
      current = tknz.nextToken();
      if (current.indexOf("CN") != -1)
      {
        CNString = current;
      }
      else if (current.indexOf("OU") != -1)
      {
        OUString = current;
      }
    }
    // Now remove CN= etc
    
    if (CNString !=null) {
      int i1 = CNString.indexOf("=");
      return CNString.substring(i1+1);
    }
    else if (OUString !=null) {
      int i2 = OUString.indexOf("=");
      return OUString.substring(i2+1);
    }
    else
      return s;
  }

  private boolean certEquals(X509Certificate crt1, X509Certificate crt2)
  {
    if ( X500Name.equals(crt1.getIssuerDN(), crt2.getIssuerDN()) &&
      crt1.getSerialNumber().equals(crt2.getSerialNumber()) )
    {
        return true;
    }
    else {
        return false;
    }
  }

  private void verifyChain(Certificate[] chain2) throws KeyStoreException
  {
    try {
    X509Certificate userCert = (X509Certificate) chain2[0];
    X509CertSelector sel= new X509CertSelector();
    CertPathBuilder cpb = new CertPathBuilder();
    Vector vec = new Vector();
    X509Certificate[] chain = new X509Certificate[chain2.length];
    for (int i=0; i < chain.length; i++) {
        chain[i] = (X509Certificate) chain2[i];
    }
    vec.add(chain[chain.length-1]);
    cpb.setTrustedCerts(vec);
    sel.setIssuerDN( (userCert.getIssuerDN()).getName() );
    sel.setSerialNumber(userCert.getSerialNumber()); 
        cpb.verify(chain);
    }
    catch(Exception e) {
        throw new KeyStoreException("Cert chain doesn't verify: " +
                            e.getMessage());
    }
  }

  private static final boolean DUMMY = Licensed.VALID;
}
