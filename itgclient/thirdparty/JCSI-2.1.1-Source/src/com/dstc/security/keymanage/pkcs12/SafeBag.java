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

package com.dstc.security.keymanage.pkcs12;

import java.io.IOException;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.security.cert.X509Certificate;
import java.util.Vector;
import java.util.NoSuchElementException;
import java.util.Iterator;

import com.dstc.security.asn1.Asn1;
import com.dstc.security.asn1.Asn1Exception;
import com.dstc.security.asn1.BMPString;
import com.dstc.security.asn1.Explicit;
import com.dstc.security.asn1.Oid;
import com.dstc.security.asn1.Sequence;
import com.dstc.security.asn1.Set;
import com.dstc.security.common.Attribute;
import com.dstc.security.common.FriendlyName;
import com.dstc.security.common.LocalKeyId;
import com.dstc.security.common.OID;
import com.dstc.security.keymanage.PKCS8Exception;
import com.dstc.security.keymanage.debug.Debug;
import com.dstc.security.keymanage.pkcs12.bags.Bag;
import com.dstc.security.keymanage.pkcs12.bags.CertBag;
import com.dstc.security.keymanage.pkcs12.bags.KeyBag;
import com.dstc.security.keymanage.pkcs12.bags.ShroudedKeyBag;
import com.dstc.security.keymanage.pkcs12.bags.UnknownBag;
import com.dstc.security.util.UnicodeBig;

/**
 * <p>A class representing the PKCS#12 ASN.1 SafeBag
 *
 * <pre>
 *     SafeBag ::= SEQUENCE {
 *        bagType OBJECT IDENTIFIER,
 *        bagContent [0] EXPLICIT ANY DEFINED BY bagType
 *        bagAttributes Attributes OPTIONAL
 *     }
 *     -- Note: There are already two defined attributes for bagAttributes
 *     -- They are friendlyName, and localKeyID
 *     --
 * </pre>
 *
 * A SafeBag is an immutable object once initialized.
 *
 * @author Daniel Bradley
 */
public class SafeBag
{
  public static final int KEYBAG = OID.keyBag.hashCode();
  public static final int SHROUDED_KEYBAG =
      OID.pkcs_8ShroudedKeyBag.hashCode();
  public static final int CERTBAG = OID.certBag.hashCode();
  public static final int CRLBAG = OID.crlBag.hashCode();
  public static final int SECRETBAG = OID.secretBag.hashCode();
  public static final int SAFECONTENTBAG = OID.safeContentBag.hashCode();
  
  protected static final int TAG_EXPLICIT = 0;

  /**
   *  The Bag represented using Asn1 objects. <p>
   */
  private Asn1 asn1;

  /**
   *  The Bag Type Oid. <p>
   */
  private String bagId;

  /**
   *  The Bag contained by this SafeBag. <p>
   */
  private Bag bag;

  /**
   *  The Bag Attributes of this Safe bag as Attribute objects. <p>
   */
  private Vector bagAttributes;
  
  //---------------------------------------------------------------------------
  //  Constructors
  //---------------------------------------------------------------------------

  public SafeBag( Asn1 asn1 ) 
    throws PKCS8Exception, Asn1Exception
  {
    Debug.dumpAsn1To( asn1, Debug.SAFEBAG );
    
    this.asn1 = asn1;

    Iterator it = asn1.components();
    try
    {
      Oid oid = (Oid) it.next();
      this.bagId = oid.getOid();
    
      // Extract the content of the Explicit object.
      // The current Asn1 library instantiates Explicit objects as Asn1
      // objects during decoding.
      Asn1 explicit = (Asn1) it.next();
      Asn1 content = (Asn1) explicit.components().next();
            
      int hash = this.bagId.hashCode();
      if ( CERTBAG == hash )
      {
        this.bag = new CertBag( content );
      }
      else if ( SHROUDED_KEYBAG == hash )
      {
        this.bag = new ShroudedKeyBag( content );
      }
      else if ( KEYBAG == hash )
      {
        this.bag = new KeyBag( content );
      }
      else
      {
        this.bag = new UnknownBag( asn1 );
      }
    } catch ( ClassCastException cce ) {
      //  A class cast exception is thrown if the passed asn1 object
      //  does not contain the ASN1 subcomponents that should exist
      //  in a SafeBag object.
      //
      throw new Asn1Exception( "Invalid SafeBag ASN.1" );
    } catch ( NoSuchElementException nsee ) {
      //  A NoSuchElementException is thrown if there are not the number
      //  of ASN1 subcomponents that should exist in an ASN.1 object.
      //
      throw new Asn1Exception( "Incomplete SafeBag ASN.1" );
    }
    
      // Extract any optional attributes
      if ( it.hasNext() )
      {
        this.bagAttributes = new Vector();
        Set set = (Set) it.next();
        Iterator attributes = set.components();
        while ( attributes.hasNext() )
        {
          //try
          //{
            Asn1 attAsn1 =
                (Asn1) attributes.next(); // throws ClassCastException
            Attribute at = new Attribute( attAsn1 ); // throws IOException
            this.bagAttributes.add( at );
          //}
          //catch ( IOException ex ) {
          //  throw new Asn1Exception( "Invalid Attribute Asn1" );
          //}
        }
      }
  }  

  public SafeBag( Bag bag )
  {
    this( bag, null );
  }

  public SafeBag( Bag bag, Vector attributes )
  {
    this( bag.getType(), bag, attributes );
  }

  public SafeBag( String bagId, Bag bag )
  {
    this( bagId, bag, null );
  }

  public SafeBag( String bagId, Bag bag, Vector attributes )
  {
    this.bagId = bagId;
    this.bag = bag;
    this.bagAttributes = attributes;
    this.initialize();
  }

  //---------------------------------------------------------------------------
  //  Initializers
  //---------------------------------------------------------------------------
  
  /**
   *  This method initializes the <code>asn1</code>  member using the
   *  <code>bagId</code>, <code>bag</code>, and <code>bagAttributes</code>
   *  members. <p>
   */
  private void initialize()
  {
    this.asn1 = new Sequence();
    
    Oid oid = new Oid( this.bagId );
    this.asn1.add( oid );
    
    Explicit bagValue = new Explicit( Asn1.TAG_CLASS_CONTEXT, TAG_EXPLICIT );
    Asn1 content = this.bag.getAsn1();
    bagValue.add( content );
    this.asn1.add( bagValue );

    if ( this.bagAttributes != null )
    {
      Asn1 bagAttributesAsn1 = new Set();
      Iterator it = this.bagAttributes.iterator();
      while ( it.hasNext() )
      {
        Attribute at = (Attribute) it.next();
        bagAttributesAsn1.add( at.getAsn1() );
      }
      this.asn1.add( bagAttributesAsn1 );
    }
  }

  //---------------------------------------------------------------------------
  //  Accessors
  //---------------------------------------------------------------------------

  /**
   *  Return an Asn1 object that represents a SafeBag object. <p>
   *
   *  @return an Asn1 object that represents a SafeBag.
   */
  public Asn1 getAsn1()
  {
    return this.asn1;
  }

  /**
   *  Returns the bagId of the Bag. <p>
   *
   *  @return a String representation of this bags Bag-type Oid.
   */
  public String getBagId()
  {
    return this.bagId;
  }
  
  /**
   *  Returns the encapsulated bag. <p>
   *
   *  @return a Bag subclass.
   */
  public Bag getBag()
  {
    return this.bag;
  } 
  
  /**
   *  Returns the Attributes of this Bag. <p>
   *
   *  @return a Vector containing zero or more Attribute objects.
   */
  public Vector getBagAttributes()
  {
    if ( bagAttributes == null )
    {
      return new Vector();
    } else {
      return this.bagAttributes;
    }
  }

  /**
   *  Return the number of Attributes of this SafeBag. <p>
   *
   *  @return <code>int</code> that shows the number of attributes
   *  in this bag.
   */
  public int getBagAttributeSize()
  {
    if ( bagAttributes == null )
    {
      return 0;
    } else {
      return this.bagAttributes.size();
    }
  }

  /**
   *  Returns the Friendly-Name of the SafeBag. <p>
   *
   *  If this SafeBag does not contain a Friendly-name, or if the attribute
   *  is invalid (eg. more than one value), an empty string ("") is
   *  returned. <p>
   *
   *  @return The friendly-name, or empty string ("").
   */
  public String getFriendlyName()
  {
    try
    {
      byte[] value = this.getAttributeValue( OID.friendlyName );
      // Should be big-endian UTF-16 (2 bytes per character)

      if ( value == null || (value.length & 1) != 0 )
      {
//      value = new byte[0];
     /*
      *  If value == null, create an "internal" friendlyName for use
      *  in Hashtables.
      */
        return ((X509Certificate) ((CertBag) this.bag).getCertificate()
                ).getSubjectDN().getName();
      }
      return UnicodeBig.bytesToString( value );
    }
    catch ( IOException ioe )
    {
      return "";
    }
  }

  public String getFNAttribute()
  {
    try
    {
      byte[] value = this.getAttributeValue( OID.friendlyName );
      if ( value != null && (value.length & 1) == 0 )
      {
        return UnicodeBig.bytesToString(value);
      }
      else 
      {
        return null;
      }
    }
    catch(IOException e)
    {
      return null;
    }
  }


  /**
    * Return Local-Key-Id of the SafeBag
    * Return null is not available
    **/
  public byte[] getLocalKeyId() throws IOException
  {
    return getAttributeValue(OID.localKeyId);
  }

  ////Helper function
  /**
   *  return bytes for the attribute with single value
   *
   *  @throws IOException If Attribute contains more than one value.
   */
  private byte[] getAttributeValue( String oid ) throws IOException
  {
    Iterator attsIt = getBagAttributes().iterator();
    while (attsIt.hasNext())
    {
      Attribute att = (Attribute) attsIt.next();
      if (att.getType().equals(oid))
      {
        Vector attsValues = att.getValues();
        //check if this is single value
        if (attsValues.size() != 1)
        {
          throw new IOException("Expecting Single Value Attribute");
        }
        else
        {
          if (oid.equals(OID.friendlyName)) {
            return ( ((BMPString) attsValues.elementAt(0)).getValue());
          }
          else {
            return ( ((com.dstc.security.asn1.OctetString) attsValues.elementAt(0)).getBytes());
          }
        }
      }
    }
    return null;
  }

  //---------------------------------------------------------------------------
  //  Public Static Methods
  //---------------------------------------------------------------------------

  /**
   *  Returns a FriendlyName attribute cast as an object. <p>
   *
   *  It is cast as an object so that users of the PKCS12 classes do not
   *  need to import <code>FriendlyName</code>. Is this worthwhile? <p>
   *
   *  @param name The name for the new FriendlyName object.
   *  @return A FriendlyName object cast to Object.
   */
  public static Object createFriendlyName( String name )
  {
    return new FriendlyName( name );
  }

  public static Object createLocalKeyId( byte[] thumb )
  {
    byte[] thumbprint = null;
    try
    {
      MessageDigest md = MessageDigest.getInstance( "SHA" );
      md.update( thumb );
      thumbprint = md.digest();
    }
    catch ( NoSuchAlgorithmException ex ) {
      Debug.log( Debug.CRITICAL, "SafeBag.createLocalKeyId()",
          "JCSI is not installed correctly: " + ex.toString() );
      throw new RuntimeException( ex.toString() );
    }
    return new LocalKeyId( thumbprint );
  }

  public void removeFN()
  {
    Iterator it = this.bagAttributes.iterator();
    Attribute att = null;
    while (it.hasNext()) {
      Attribute at = (Attribute) it.next();
      if (at.getType().equals(OID.friendlyName)) {
        att = at;
      }
    }
    if (att != null) {
       this.bagAttributes.remove(att);
       this.initialize();
    }
  }

  //---------------------------------------------------------------------------
  //  Unrelated Static Methods
  //---------------------------------------------------------------------------

  protected static String printHex(byte bytes[])
  {
    StringBuffer sb = new StringBuffer();
    for (int i = 0; i < bytes.length; i++)
    {
      sb.append(toHexDigit(bytes[i]));
    }
    sb.append("\n");
    return sb.toString();
  }

  private static String toHexDigit(byte x)
  {
    char ret[] = new char[2];
    char c = (char)((x >> 4) & 0xf);
    if (c > 9)
    {
      c = (char)((c - 10) + 'a');
    }
    else
    {
      c = (char)(c + '0');
    }
    ret[0] = c;

    c = (char)(x & 0xf);
    if (c > 9)
    {
      c = (char)((c - 10) + 'a');
    }
    else
    {
      c = (char)(c + '0');
    }
    ret[1] = c;
    return new String(ret);
  }
}
