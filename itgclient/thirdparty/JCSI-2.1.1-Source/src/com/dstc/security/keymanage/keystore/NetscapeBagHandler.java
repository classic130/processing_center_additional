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

import java.io.PrintStream;
import java.io.IOException;
import java.security.PrivateKey;
import java.security.cert.X509Certificate;
import java.security.cert.CertificateException;
import java.security.SecureRandom;
import java.util.Collection;
import java.util.Enumeration;
import java.util.Hashtable;
import java.util.Iterator;
import java.util.TreeSet;
import java.util.Vector;
import javax.crypto.SecretKey;

import com.dstc.security.asn1.Asn1;
import com.dstc.security.asn1.Asn1DecodingException;
import com.dstc.security.asn1.Asn1Exception;
import com.dstc.security.asn1.OctetString;
import com.dstc.security.keymanage.pkcs7.ContentInfo;
import com.dstc.security.common.OID;
import com.dstc.security.common.X500Name;
import com.dstc.security.keymanage.pkcs7.ContentInfoFactory;
import com.dstc.security.keymanage.pkcs12.AuthenticatedSafe;
import com.dstc.security.keymanage.pkcs12.SafeBag;
import com.dstc.security.keymanage.pkcs12.SafeContents;
import com.dstc.security.keymanage.pkcs12.bags.CertBag;
import com.dstc.security.keymanage.keystore.BagHandler;
import com.dstc.security.keymanage.util.PKCS12KeyFactory;
import com.dstc.security.keymanage.debug.Debug;
import com.dstc.security.certpath.CertPathBuilder;
import com.dstc.security.certpath.CertPath;
import com.dstc.security.certpath.CertPathException;
import com.dstc.security.certpath.X509CertSelector;

/**
 *  This class implements the BagHandler class which provides a Bag
 *  oriented user interface to the AuthenticatedSafe class. <p>
 *
 *  This class handles bags appropriately for import into Netscape
 *  from a PKCS#12 file. <p>
 *
 *  WARNING: This class does not handle FriendlyName collisions. <p>
 *
 *  @see com.dstc.security.pkcs12.AuthenticatedSafe
 *
 *  @author Daniel Bradley
 */
public class NetscapeBagHandler implements BagHandler
{
  /**
   *  This Hashtable holds (unencrypted) KeyBags. <p>
   */
  private Hashtable keys = new Hashtable();

  /**
   *  This Hashtable holds ShroudedKeyBags. <p>
   */
  private Hashtable shroudedKeys = new Hashtable();

  /**
   *  This Hashtable holds CertBags. <p>
   */
  private Hashtable certificates = new Hashtable();

  // XXX:Hack
  //
  // certsByKeyId is a temporary Hashtable, containing certs
  // which have a localKeyId attribute in their SafeBag.
  private Hashtable certsByKeyId = new Hashtable();

  // store cert-chains are SafeBag[] where the Hashtable "key" is
  // the FN of the corresponding ShroudedKeyBag
  //
  private Hashtable certChainByKeyId = new Hashtable();

  private SecureRandom rnd = new SecureRandom(new byte[]{0,0,1,2});

  /**
   *  This key is used to decrypt EncryptedData ContentInfo objects. <p>
   */
  private char[] password = null;

  /**
   *  This Vector contains Encrypted/Enveloped Data ContentInfo objects
   *  that we cannot handle at this moment. <p>
   */
  private Vector cloaked = new Vector();

  //---------------------------------------------------------------------------
  //  Constructors
  //---------------------------------------------------------------------------
  
  /**
   *  Creates a new empty BagHandler that can be exported as an empty
   *  AuthenticatedSafe object. <p>
   */
  public NetscapeBagHandler() { ; }

  /**
   *  Creates a BagHandler and initializes it with the passed
   *  AuthenticatedSafe. <p>
   *
   *  This is the same as:
   *  <pre>
   *     BagHandler bagHand = new BagHandler();
   *     bagHand.importBags( authSafe );
   *  </pre>
   *
   *  @param authSafe
   *  @throws Asn1Exception If authSafe contains invalid ContentInfo objects.
   */
  public NetscapeBagHandler( AuthenticatedSafe authSafe )
  throws Asn1DecodingException, Asn1Exception
  {
    this.importBags( authSafe );
  }

  //---------------------------------------------------------------------------
  //  Import Methods
  //---------------------------------------------------------------------------

  /**
   *  Adds all the SafeContents objects held in the authenticatedSafe
   *  object into appropriate Vector objects for convenience. <p>
   *
   *  @param authSafe
   *  @throws Asn1DecodingException If ContentInfo contents is invalid ASN.1.
   *  @throws Asn1Exception If authSafe contains invalid ContentInfo objects.
   */
  public void importBags( AuthenticatedSafe authenticatedSafe )
  throws Asn1DecodingException, Asn1Exception
  {
    ContentInfo[] contents = authenticatedSafe.getContents();
    SafeContents sc = null;

    SecretKey[] skeys = null;
    if ( null != this.password )
    {
      skeys = new SecretKey[1];
      skeys[0] = PKCS12KeyFactory.createPBEKey( this.password );
    }

    for( int i=0; i < contents.length; i++ )
    {
      try
      {
        //  Retrieve the embedded ContentInfo object that holds the
        //  Data object that holds an encoded SafeContents.
        byte[] data = ContentInfoFactory.recurse( contents[i], skeys, null );
        Asn1 asn1 = Asn1.getAsn1( data );
        sc = new SafeContents( asn1 );
      }
      // XXX Need to add more exceptions to "recurse" so we know what is
      //     happening.
      catch ( Exception ex )
      {
        //  Unable to resolve ContentInfo so put it into cloaked Vector
        //  so we don't lose it.
        Debug.log( Debug.INFO, "NetscapeBagHandler.importBags()",
            "Unable to decrypt ContentInfo" );
        Debug.log( Debug.DEBUG, "NetscapeBagHandler.importBags()",
            ex.toString() );
        cloaked.add( contents[i] );
      }

      //  Now we process the Data ContentInfo object if we
      //  managed to get it.
      //
      if ( null != sc )
      {
        SafeBag[] safeBags = sc.getAllSafeBags();
        this.storeBags( safeBags );

        // Need to make null so we can test
        // against it next time around.
        sc = null;
      }
    }
    // At this stage, all CertBag's are in the Hashtable certificates
    // and user certs are also in certsByKeyId. Now build cert-paths
    // from the usercerts and afterwards delete used entries from 
    // this.certificates
    //
    // First copy certs in Hashtable into Vector (needed by CertPathBuilder)
    Vector vec = new Vector();
    Hashtable copy = (Hashtable) certificates.clone();
    /*Enumeration en = certificates.elements();
    while (en.hasMoreElements())
    {
      CertBag cb = (CertBag) ((SafeBag)en.nextElement()).getBag();
      vec.add((X509Certificate) cb.getCertificate());
    }*/
    Enumeration en = certificates.keys(); 
    while (en.hasMoreElements())
    {
      String key = (String)en.nextElement();
      CertBag cb = (CertBag) ((SafeBag)certificates.get(key)).getBag();
      vec.add((X509Certificate) cb.getCertificate());
    }

    // Next, build certpaths
    en = certsByKeyId.elements();
    X509Certificate userCert=null;
    X509CertSelector sel= new X509CertSelector();
    CertPathBuilder cpb = new CertPathBuilder();
    Vector cp = null;
    cpb.setTrustedCerts(vec);
    while (en.hasMoreElements())
    {
      SafeBag sb = (SafeBag)en.nextElement();
      userCert = (X509Certificate) ((CertBag) sb.getBag()).getCertificate();
      String skb_alias = null;
      try {  
        skb_alias = getSKBAlias(sb.getLocalKeyId());
      }
      catch(IOException e) {
        continue;
      }
      if (skb_alias == null) {
          continue;
      }

      sel.setIssuerDN( (userCert.getIssuerDN()).getName() );
      sel.setSerialNumber(userCert.getSerialNumber());
      try {
        cp = cpb.doNameChaining(vec, sel);
        // now, build a chain of SafeBag's from CertPath
        int len = cp.size();
        SafeBag[] sbPath = new SafeBag[len];
        for (int j=0; j<len; j++) {
          X509Certificate crt = (X509Certificate)cp.elementAt(j);
          SafeBag tmp = null;
          String tmp_key = null;
          Enumeration en2 = certificates.keys();
          while (en2.hasMoreElements()) {
            String key = (String) en2.nextElement();
            SafeBag sb2 = (SafeBag) certificates.get(key);
            X509Certificate htcrt = (X509Certificate) ((CertBag) 
               sb2.getBag()).getCertificate();
            if (crt.getSerialNumber().equals(htcrt.getSerialNumber()) &&
                X500Name.equals(crt.getIssuerDN(), htcrt.getIssuerDN()))
            // All certs are stored internally, so can compare references
            // if (crt == htcrt)
            {
              if (sb2.getFNAttribute() == null) {
                  sbPath[j] = sb2;
                  copy.remove(key);
                  break;
              }
              else {
                  tmp = sb2;
                  tmp_key = key;
              }
            }
          }
          if (sbPath[j] == null)
          {
              sbPath[j] = tmp;
              copy.remove(tmp_key);
              sbPath[j].removeFN();
          }
        }
        certChainByKeyId.put(skb_alias, sbPath);
        certificates = copy;
      }
      catch(Exception e) {
        throw new RuntimeException("Certpath building error:" +e.getMessage());
      }
      
    }
  }

  /* Search through the keys and shroudedKeys Hashtables to find
   * a (Shrouded)KeyBag with matching local key id.
   *
   */
  private String getSKBAlias(byte[] lkid)
  {
    String retval = null;
    byte[] b = null;
    // First search the Shrouded KeyBag's
    Enumeration en = shroudedKeys.keys();
    while (en.hasMoreElements())
    {
      retval = (String) en.nextElement();
      try {
        b = ((SafeBag) shroudedKeys.get(retval)).getLocalKeyId();
      }
      catch(IOException e) {
        return null;
      }
      if (java.util.Arrays.equals(lkid, b))
      {
        return retval;
      }
    }
    // Didn't find it, so search the KeyBags
    Enumeration en2 = keys.keys();
    while (en2.hasMoreElements())
    {
      retval = (String) en2.nextElement();
      try {
        b = ((SafeBag) keys.get(retval)).getLocalKeyId();
      }
      catch(IOException e) {
        return null;
      }
      if (java.util.Arrays.equals(lkid, b))
      {
        return retval;
      }
    }
    return null;
  }

/*private boolean isInPath(String s)
  {
    X509Certificate cert = (X509Certificate) ((CertBag) 
                 ((SafeBag) certificates.get(s)).getBag()).getCertificate();
    Enumeration e1 = certChainByKeyId.keys();
    while(e1.hasMoreElements())
    { 
      SafeBag[] sbp = (SafeBag[]) certChainByKeyId.get(
                                        (String)e1.nextElement());
      for (int i=0; i < sbp.length; i++)
      {
        if (cert == (X509Certificate) ((CertBag) 
                              sbp[i].getBag()).getCertificate() )
          return true;
      }
    }
    return false;
  }*/

  //---------------------------------------------------------------------------
  //  Get Methods
  //---------------------------------------------------------------------------
 
  /**
   *  Returns a SafeBag object. <p>
   *
   *  If available returns the first SafeBag found that contains a
   *  friendly-name attribute equal to <code>friendlyName</code>; if such
   *  SafeBag cannot be found null is returned.
   *
   *  Note that an alias is often associated with more than one SafeBag.
   *  This searches in the order ShroudedKeys, Certificates ... <p>
   *
   *  @see getBags( String friendlyName )
   *
   *  @param friendlyName The alias given to the bag.  
   *  @return The first SafeBag found that matches that alias, else null.
   */
  public SafeBag getBag( String friendlyName )
  {
    SafeBag safeBag = (SafeBag) this.shroudedKeys.get( friendlyName );
    if ( safeBag == null )
    {
      safeBag = (SafeBag) this.certificates.get( friendlyName );
    }
    if ( safeBag == null )
    {
      safeBag = (SafeBag) this.keys.get( friendlyName );
    }
    return safeBag;
  }
  
  // XXX: Hack - get (unique) CertBag corresponding to KeyId
  //
  public SafeBag getBag(byte[] keyId )
  {
    return (SafeBag) this.certsByKeyId.get( bytesToString(keyId) );
  }
  
  /**
   *  Unlike <code>getBag( String )</code> this method will search for all
   *  bags that have the same friendlyName. <p>
   *
   *  ie It will return Bags containing all the Keys and Certificates that
   *  match this friendlyName.
   *
   */
  public SafeBag[] getBags( String friendlyName )
  {
    SafeBag shroudedKeyBag = (SafeBag) this.shroudedKeys.get( friendlyName );
    SafeBag keyBag = (SafeBag) this.keys.get( friendlyName );
    SafeBag certBag = (SafeBag) this.certificates.get( friendlyName );

    int size = 0;

    if ( shroudedKeyBag != null )
    {
      size++;
    }

    if ( keyBag != null )
    {
      size++;
    }

    if ( certBag != null )
    {
      size++;
    }

    SafeBag[] safeBags = new SafeBag[size];

    int posn = 0;
    if ( shroudedKeyBag != null )
    {
      safeBags[posn] = shroudedKeyBag;
      posn++;
    }

    if ( keyBag != null )
    {
      safeBags[posn] = keyBag;
      posn++;
    }

    if ( certBag != null )
    {
      safeBags[posn] = certBag;
      posn++;
    }

    return safeBags;
  }

  /**
   *  Returns all the Bags managed by this BagHandler. <p>
   *
   *  @return An array of SafeBag objects.
   */
  public SafeBag[] getAllBags()
  {
    int size = this.shroudedKeys.size() + this.certificates.size()
                       + this.keys.size();
    SafeBag[] safebags = new SafeBag[size];

    int posn = 0;
    Enumeration enum = this.shroudedKeys.elements();
    while ( enum.hasMoreElements() )
    {
      safebags[ posn++ ] = (SafeBag) enum.nextElement();
    }

    enum = this.keys.elements();
    while ( enum.hasMoreElements() )
    {
      safebags[ posn++ ] = (SafeBag) enum.nextElement();
    }

    enum = this.certificates.elements();
    while ( enum.hasMoreElements() )
    {
      safebags[ posn++ ] = (SafeBag) enum.nextElement();
    }

    return safebags;
  }

  public X509Certificate[] getChain(String alias)
  {
    SafeBag[] sbp = (SafeBag[]) certChainByKeyId.get(alias);
    if (sbp == null) {
        return null;
    }
  /*try {
        SafeBag safeBag = (SafeBag) shroudedKeys.get(alias);
        byte[] b = safeBag.getLocalKeyId(); 
 
        sbp = (SafeBag[]) certChainByKeyId.get(bytesToString(b));
    }
    catch(IOException e) {
        return null;
    }*/
    X509Certificate[] chain = new X509Certificate[sbp.length];
    for (int i=0; i<chain.length; i++) {
/*
try {
System.out.println("****** FN :" + sbp[i].getFNAttribute());
System.out.println("****** FriendlyName :" + sbp[i].getFriendlyName());
System.out.println("****** Local KeyID :" + bytesToString(sbp[i].getLocalKeyId()));
} catch(Exception e){System.out.println(e.getMessage());}
*/
        chain[i] = (X509Certificate) ((CertBag) 
                                  sbp[i].getBag()).getCertificate() ;
    }
    return chain;
  }
  
  //---------------------------------------------------------------------------
  //  Set Methods
  //---------------------------------------------------------------------------

  public void setPassword( char[] passwd )
  {
    this.password = passwd;
  }

  //---------------------------------------------------------------------------
  //  Store Methods
  //---------------------------------------------------------------------------

  /**
   *  Stores a bag into a newly created SafeContents object. <p>
   *
   *  @param safeBag The SafeBag to add.
   */
  public void storeBag( SafeBag safeBag )
  {
    String fn = safeBag.getFriendlyName();

    if ( safeBag.getBagId().equals( OID.pkcs_8ShroudedKeyBag ) )
    {
      this.shroudedKeys.put( safeBag.getFriendlyName(), safeBag );
    }
    else if ( safeBag.getBagId().equals( OID.keyBag ) )
    {
      this.keys.put( safeBag.getFriendlyName(), safeBag );

    }
    else if ( safeBag.getBagId().equals( OID.certBag ) )
    {
//    this.certificates.put( safeBag.getFriendlyName(), safeBag );
      // XXX:Hack
      try {
        byte[] b = safeBag.getLocalKeyId();
        if ( b != null) {                        // if CertBag has keyId
            this.certsByKeyId.put(bytesToString(b), safeBag );
        }
        if (!this.certificates.containsKey(fn)) {
            this.certificates.put( safeBag.getFriendlyName(), safeBag );
        }
        else {
            byte[] b2 = new byte[20];
            rnd.nextBytes(b2);
            this.certificates.put( fn + bytesToString(b2), safeBag );
        }
      }
      catch(IOException e) {}
      // XXX: end hack
    }
  }

// Hack method
private String bytesToString(byte[] bytes) {
    StringBuffer sb= new StringBuffer();
    for (int i=0; i<bytes.length; i++)
    {
      sb.append(java.lang.Integer.toHexString(bytes[i] & 0xff) + " ");
    }
    return sb.toString();
}

  /**
   *  Stores a group of Safe Bags into a new SafeContents object. <p>
   */
  public void storeBags( SafeBag[] safeBags )
  {
    for ( int i=0; i < safeBags.length; i++ )
    {
      this.storeBag( safeBags[i] );
    }
  }

  /*  Stores a SafeBag[] in the Hashtable this.certChainByKeyId
   *
   *  imput - path: Vector of SafeBag objects
   */

   public void storeChain(String alias, Vector path)
   {
     SafeBag[] sbp = new SafeBag[path.size()];
     for (int i=0; i< sbp.length; i++) {
         sbp[i] = (SafeBag) path.elementAt(i);
     }
     this.certChainByKeyId.put(alias, sbp);
   }

  //---------------------------------------------------------------------------
  //  Remove Methods
  //---------------------------------------------------------------------------

  public void removeBags( String alias )
  {
    this.shroudedKeys.remove( alias );
    this.keys.remove( alias );
    this.certificates.remove( alias );
    this.certChainByKeyId.remove( alias );
  }
  
  /**
   *  Removes all bags that match both <code>bagId</code> and
   *  <code>friendlyName</code>. <p>
   */
  public void removeBags( String bagId, String friendlyName )
  {
    // XXX
    ;
  }

  //---------------------------------------------------------------------------
  //  Queries
  //---------------------------------------------------------------------------
  
  /**
   *  Returns all of the friendly names of SafeBags that can be found within
   *  this BagHandler. <p>
   *
   *  @return An array of friendly-names as String objects.
   */
  public String[] getAllFriendlyNames()
  {
    Enumeration shroudedKeyNames = this.shroudedKeys.keys();
    Enumeration keyNames = this.keys.keys();
    Enumeration certNames = this.certificates.keys();

    //TreeSet set = new TreeSet();
    Vector set = new Vector();
    while ( shroudedKeyNames.hasMoreElements() )
    {
      set.add( shroudedKeyNames.nextElement() );
    }

    while ( keyNames.hasMoreElements() )
    {
      set.add( keyNames.nextElement() );
    }

    while ( certNames.hasMoreElements() )
    {
//    set.add( certNames.nextElement() );
      // XXX: begin hack (Only "trusted cert" entries to output)
      try {
        String s = (String)certNames.nextElement();
        if ( getBag(s).getLocalKeyId() == null ) {
            set.add(s);
        }
      }
      catch(IOException e) {}
      
      // XXX: end hack
    }

    int size = set.size();
    String[] names = new String[ size ];

    Iterator it = set.iterator();
    int posn = 0;
    while( it.hasNext() )
    {
      names[ posn ] = (String) it.next();
      posn++;
    }
    return names;
  }

  /**
   *  Returns the the number of bags. <p>
   *
   *  @return an <code>int</code> representing the number of bags.
   */  
  public int size()
  {
    return keys.size() + shroudedKeys.size() + certificates.size();
  }
  
  public void contents( PrintStream ps )
  {
    Enumeration shroudedKeyNames = this.shroudedKeys.keys();
    ps.println( "ShroudedKeyBags:" );
    while( shroudedKeyNames.hasMoreElements() )
    {
      ps.println( "\t" + (String) shroudedKeyNames.nextElement() );
    }

    Enumeration certNames = this.certificates.keys();
    ps.println( "CertBags:" );
    while( certNames.hasMoreElements() )
    {
      ps.println( "\t" + (String) certNames.nextElement() );
    }
    ps.flush();
  }

  /**
   *  XXX Doesn't export unencrypted KeyBags. <p>
   */
  public AuthenticatedSafe export()
  {
    return this.export( null, null );
  }
  
  /**
   *  Packages everything up into an AuthenticatedSafe object. <p>
   *
   *  Gets all the bags and seperates them into two <b>Safe Contents</b>
   *  objects (depending on type), then encrypts them using 
   *  <code>passwd</code>. <p>
   *
   *  XXX Does not support enveloping yet. <p>
   */
  public AuthenticatedSafe export( String ALGORITHM, char[] passwd )
  {
    Collection col = null;
    SafeBag[] bags = null;

    col = this.shroudedKeys.values();
    bags = new SafeBag[ col.size() ];
    SafeContents shkeysSC = null;
    if (bags.length > 0) 
    {
        bags = (SafeBag[]) col.toArray( bags );
        shkeysSC = new SafeContents( bags );
    }

    col = this.certificates.values();
    bags = new SafeBag[ col.size() ];
    SafeContents certsSC = null;
    if (bags.length > 0) 
    {
        bags = (SafeBag[]) col.toArray( bags );
        certsSC = new SafeContents( bags );
    }

    // Deal with chains of CertBag's
    Enumeration en  = certChainByKeyId.elements();
    Vector bagVec = new Vector();
    while (en.hasMoreElements()) {
        SafeBag[] sbp = (SafeBag[]) en.nextElement();
        for (int i=0; i < sbp.length; i++) {
            bagVec.add(sbp[i]);
        }
    }
    bags = new SafeBag[bagVec.size()];
    bags = (SafeBag[]) bagVec.toArray(bags);
    SafeContents certchainSC = null;
    if (bags.length > 0) 
    {
        certchainSC = new SafeContents( bags );
    }

    AuthenticatedSafe authSafe = new AuthenticatedSafe();

    if ( ( passwd == null ) || ( ALGORITHM == null ) )
    {
      if (shkeysSC != null)
          authSafe.add( shkeysSC );
      if (certsSC != null)
          authSafe.add( certsSC );
      if (certchainSC != null)
          authSafe.add( certchainSC );
    }
    else
    {
      // If a password is passed encrypt the two SafeContents objects using
      // the algorithm specified, before adding them to the
      // AuthenticatedSafe object.

      try
      {
        Asn1 shroudedKeysAsn1 = shkeysSC.getAsn1();
        ContentInfo keysInfo =
            ContentInfoFactory.createContentInfo( shroudedKeysAsn1 );
        ContentInfo keysEncrypted =
            ContentInfoFactory.encrypt( keysInfo, ALGORITHM, passwd );
        authSafe.add( keysEncrypted );

        Asn1 certsAsn1 = certsSC.getAsn1();
        ContentInfo certsInfo =
            ContentInfoFactory.createContentInfo( certsAsn1 );
        ContentInfo certsEncrypted = 
            ContentInfoFactory.encrypt( certsInfo, ALGORITHM, passwd );
        authSafe.add( certsEncrypted );
      }
      catch ( Exception ex )
      {
          throw new RuntimeException("encryption error");
      }
    }

    Iterator others = this.cloaked.iterator();
    while ( others.hasNext() )
    {
      ContentInfo ci = (ContentInfo) others.next();
      authSafe.add( ci );
    }

    return authSafe;
  }

  //  EnvelopedData ed = (EnvelopedData) enveloped.next();
  //  Asn1 asn1 = null; //ed.getAsn1();
  //  ContentInfo ci = new ContentInfo( OID.id_envelopedData, asn1 );
  //  authSafe.add( ci );
}
  
