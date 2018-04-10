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

package com.dstc.security.asn1;

import java.util.Vector;
import java.util.Iterator;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.InputStream;
import java.io.OutputStream;
import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.IOException;

public class Asn1
{
  private static final boolean debug = true;

  //Tag classes -- bits 8 and 7
  public static final int TAG_CLASS_UNIVERSAL = 0x00;
  public static final int TAG_CLASS_APPLICATION = 0x40;
  public static final int TAG_CLASS_CONTEXT = 0x80;
  public static final int TAG_CLASS_PRIVATE = 0xC0;
  public static final int MASK_CLASS = 0xC0;

  //Primitive or Constructed -- bit 6
  public static final int TAG_PRIMITIVE = 0x00;
  public static final int TAG_CONSTRUCTED = 0x20;
  public static final int MASK_CONSTRUCTED = 0x20;

  //Universal Tag numbers
  public static final byte TAG_BOOLEAN = 0x01;
  public static final byte TAG_INTEGER = 0x02;
  public static final byte TAG_BITSTRING = 0x03;
  public static final byte TAG_OCTETSTRING = 0x04;
  public static final byte TAG_NULL = 0x05;
  public static final byte TAG_OID = 0x06;
  public static final byte TAG_ENUMERATED = 0x0A;
  public static final byte TAG_SEQUENCE = 0x10;
  public static final byte TAG_SET = 0x11;
  public static final byte TAG_UTF8STRING = 0xC;               //0x12
  public static final byte TAG_PRINTABLESTRING = 0x13;
  public static final byte TAG_T61STRING = 0x14;
  public static final byte TAG_IA5STRING = 0x16;
  public static final byte TAG_UTCTIME = 0x17;
  public static final byte TAG_GENERALIZEDTIME = 0x18;
  public static final byte TAG_VISIBLESTRING = 0x1A;
  public static final byte TAG_GENERALSTRING = 0x1B;
  public static final byte TAG_UNIVERSALSTRING = 0x1C;
  public static final byte TAG_BMPSTRING = 0x1E;
  public static final byte MASK_NUMBER = 0x1F;

  private static final int DECODING = 1;
  private static int BER_BUF_LEN = 512;
  private int state;
  protected int depth = 0;
  protected int tag;
  protected int length;
  protected byte[] value = null;
  protected InputStream contentsIn = null;
  protected Vector components = null;
  protected boolean isStructured = false;
  protected int encodingLength = 0;
  protected boolean lengthKnown = true;
  protected Asn1ComponentIterator it;

  //used in writeValue() (during decoding) & berEncode() (during encoding)
  private boolean done = false;
  private boolean headerDone = false;
  private Iterator encIt = null;
  private Asn1 encComp = null;

  /**
   * <p>Constructs and returns an Asn1 object from a byte array
   * containing a BER encoding.
   *
   * <p>If the encoding is definite-length, full decoding is performed
   * with the results kept in memory. If the encoding is indefinite-
   * length, actual decoding is postponed until necessary; ie. when
   * calls to components().next() are made.
   *
   * <p>If the class tag is UNIVERSAL, the returned object is cast to
   * the appropriate Asn1 subclass.
   *
   * <p>NB: The returned object is not immutable
   *
   *  Added getAsAsnTagged. DRB. <p>
   */
  public static Asn1 getAsn1(byte[] encoded) 
    throws Asn1Exception
  {
    try
    {
      return getAsn1(new ByteArrayInputStream(encoded));
    }
    catch (IOException e)
    {
      throw new Asn1DecodingException(e.getMessage());
    }
  }

  /**
   * <p>Constructs and returns an Asn1 object from an InputStream 
   * containing a BER encoding.
   *
   * <p>If the encoding is definite-length, full decoding is performed
   * with the results kept in memory. If the encoding is indefinite-
   * length, actual decoding is postponed until necessary; ie. when
   * calls to components().next() are made.
   *
   * <p>If the class tag is UNIVERSAL, the returned object is cast to
   * the appropriate Asn1 subclass.
   *
   * <p>NB: The returned object is not immutable
   */
  public static Asn1 getAsn1(InputStream is) throws IOException
  {
    int tag = readTag(is);
    Asn1 retval = getAsn1ForTag( tag );

    retval.decode(tag, is);
    return retval;
  }

  /**
   *  Pulled straight from <code>getAsn1</code> to allow sharing between
   *  it and <code>getAsAsn1Tagged</code>. DRB. <p>
   *
   *  @param tag The tag of the class to be returned.
   *  @return An Asn1, or subclass, object for tag.
   */
  private static Asn1 getAsn1ForTag( int tag )
  {
    Asn1 retval = null;
    if (TAG_CLASS_UNIVERSAL == (tag & MASK_CLASS))
    {
      switch (tag & MASK_NUMBER)
      {
        case (TAG_SEQUENCE):
          retval = new Sequence();
          break;

        case (TAG_SET):
          retval = new Set();
          break;

        case (TAG_OID):
          retval = new Oid();
          break;

        case (TAG_INTEGER):
          retval = new Integer();
          break;

        case (TAG_ENUMERATED):
          retval = new Enumerated();
          break;

        case (TAG_OCTETSTRING):
          retval = new OctetString();
          break;

        case (TAG_BITSTRING):
          retval = new BitString();
          break;

        case (TAG_BOOLEAN):
          retval = new Boolean();
          break;

        case (TAG_GENERALIZEDTIME):
          retval = new GeneralizedTime();
          break;

        case (TAG_UTCTIME):
          retval = new UTCTime();
          break;

        case (TAG_NULL):
          retval = new Null();
          break;

        case (TAG_PRINTABLESTRING):
          retval = new PrintableString();
          break;

        case (TAG_IA5STRING):
          retval = new IA5String();
          break;

        case (TAG_T61STRING):
          retval = new T61String();
          break;

        case (TAG_UTF8STRING):
          retval = new UTF8String();
          break;

        case (TAG_BMPSTRING):
          retval = new BMPString();
          break;

        case (TAG_UNIVERSALSTRING):
          retval = new UniversalString();
          break;

        case (TAG_VISIBLESTRING):
          retval = new VisibleString();
          break;

        case (TAG_GENERALSTRING):
          retval = new GeneralString();
          break;

        default:
          retval = new Asn1();    //unknown tag
      }
    }
    else // non-universal
    {
      retval = new Asn1();
      retval.components = new Vector();
    }
    return retval;
  }

  /**
   *  Changes the type of an Asn1 object to that of another Universal Asn1
   *  object (a subclass of Asn1). <p>
   *
   *  Only use Universal tag vales for <code>tag</code>.
   *
   *  This method just copies the state of the instance it is called
   *  upon into the new object, hence the original instance should be
   *  treated as no longer valid - any methods on it may affect the
   *  new Asn1 object. <p>
   *
   *  This method is useful for conversion of Asn1 objects to other Asn1
   *  objects -
   *  useful when an implicitly tagged asn1 component is instantiated as
   *  an Asn1 object, but you really want the subclass the implicit type
   *  is based upon. DRB. <p>
   *
   *  @param tag The tag of the Universal Asn1 type you want returned.
   *  @return An Asn1, or subclass, object.
   */
  public Asn1 getAsAsn1Tagged( int tagValue )
  {
    int newTag = tagValue;

    //  Check if this tag is Universal as expected.
    //  Type is univeral if Bits 8 & 7 are zero.
    //  ie. if 0x00 == tag & 0xC0
    if ( TAG_CLASS_UNIVERSAL != ( tagValue & MASK_CLASS ) ) // not Universal
    {
      throw new IllegalArgumentException( "Universal tag type expected" );
    }

    //  If original object is constructed, change the tag to reflect this.
    //  ie. if 0x20 == tag & 0x20
    if ( TAG_CONSTRUCTED == ( this.tag & MASK_CONSTRUCTED ) )
    {
      newTag = tagValue | TAG_CONSTRUCTED;
    }
    //  Create new object.
    Asn1 implicit = getAsn1ForTag( newTag );

    //  Set modified tag.
    implicit.tag = newTag;

    //  Copy rest of state.
    //  XXX This will need to be changed if more members are added to Asn1.
    implicit.state = this.state;
    implicit.depth = this.depth;
    implicit.length = this.length;
    implicit.value = this.value;
    implicit.contentsIn = this.contentsIn;
    implicit.components = this.components;
    implicit.isStructured = this.isStructured;
    implicit.encodingLength = this.encodingLength;
    implicit.lengthKnown = this.lengthKnown;
    implicit.it = this.it;
    return implicit;
  }

  /**
   * Writes the BER encoding for this Asn1 into the
   * supplied OutputStream.
   *
   * <p>NB: All encodings are DER where possible (in
   * particular if the length of the encoding is known
   * in advance)
   *
   * <p> Warning!!! This is not an idempotent operation.
   * In particular, repeated calls may not make sense
   * (in the case where the encoding is indefinite-length
   * and the contents are supplied through an InputStream)
   */
  public void encode(OutputStream os) 
    throws IOException, Asn1Exception
  {
    berEncode(os);
  }

  /**
   * Returns the DER encoding for this Asn1 object.
   *
   * <p> NB. Use the stream-based method for BER encoding
   */
  public byte[] getEncoded() throws Asn1Exception
  {
    try
    {
      ByteArrayOutputStream baos = new ByteArrayOutputStream();
      derEncode(baos);
      baos.flush();
      return baos.toByteArray();
    }
    catch (IOException e)
    {
      throw new Asn1EncodingException(e.getMessage());
    }
  }

  /**
   * Writes the DER encoding into the supplied OutputStream.
   *
   * <p> The encoding is cached for better performance with 
   * repeated calls.
   */
  public void derEncode(OutputStream os) 
    throws IOException, Asn1Exception
  {
    if (!lengthKnown())
       throw new Asn1EncodingException("Length unknown: cannot DER encode"); 

    os.write((byte)(0xff & this.tag));

    if (isConstructed())
    {
      Iterator it = components();
      ByteArrayOutputStream baos = new ByteArrayOutputStream();
      while (it.hasNext())
      {
        ((Asn1)it.next()).derEncode(baos);
      }
      
      this.value = baos.toByteArray();
    }

    this.length = this.value.length;
    writeLengthOctets(this.length, os);
    os.write(this.value);
  }

  /**
   * Writes the BER encoding for this Asn1 into the 
   * supplied OutputStream.
   *
   * <p>NB: All encodings are DER where possible (in
   * particular if the length of the encoding is known
   * in advance)
   */
  public void berEncode(OutputStream os) 
    throws IOException, Asn1Exception
  {
    byte[] buf = null;
    while (true)
    {
      if (null == (buf = berEncode()))
        break;

      os.write(buf);
    }
  }

  /**
   * Returns an iterator for the components of this
   * Asn1 object. 
   *
   * <p>For the encoding process, "components" here mean the 
   * usual, and is only valid if the "container" is for a structured
   * ASN.1 type.
   * 
   * <p>For the decoding process, the meaning of "components" is
   * extended for the case of a non-DER encoding. If particular,
   * if a simple string type (or type derived from it by implicit
   * tagging) is encoded with a constructed method (either definite
   * or indefinite length) the "components" are the substrings in
   * the encoding. In this case, the onus is on the programmer to
   * re-construct the original string from these "components".
   * Eg. use the writeValue(OutputStream) method.
   */
  public Iterator components()
  {
    if (!lengthKnown() && state == DECODING)
      return this.it;

    if (this.components == null)
      return null;

    return this.components.iterator();
  }

  /**
   * Adds an Asn1 object as a component to this
   * Asn1 object. 
   *
   * <p>NB: Valid only if this Asn1 object
   * is structured (ie. is Set, Sequence or tagged
   * versions of these).
   */
  public void add(Asn1 asn1) //throws Asn1Exception
  {
    //if (this.components == null)
    //  throw new Asn1Exception("Cannot add to simple type");

    this.components.add(asn1);

    if (lengthKnown())
    {
      this.lengthKnown &= asn1.lengthKnown;
      this.length += asn1.encodingLength;
    }
  }

  public final void setTagNumber(int num)
  {
    this.tag = (this.tag & MASK_CLASS) | (this.tag & MASK_CONSTRUCTED) | num;
  }

  /**
   * Returns the TAG NUMBER for this Asn1 object
   */
  public final int getTagNumber()
  {
    return (tag & MASK_NUMBER);
  }

  public final void setTagClass(int cl)
  {
    this.tag = (this.tag & MASK_NUMBER) | (this.tag & MASK_CONSTRUCTED) | cl;
  }

  /**
   * Returns the TAG CLASS for this Asn1 object
   */
  public final int getTagClass()
  {
    return (tag & MASK_CLASS);
  }

  /**
   * Returns the contents for this Asn1 object
   */
  public byte[] getValue()
  {
    return this.value;
  }

  /**
   * Writes the contents for this Asn1 object into an OutputStream.
   *
   * <p>NB: Not valid if this Asn1 object is a structured type or a
   * a type constructed from one by implicit or explicit tagging
   * ??? How do we check this ???
   */
  public void writeValue(OutputStream os) throws IOException
  {
    byte[] buf = null;
    while (true)
    {
      if (null == (buf = writeValue()))
      {
        break;
      }
      else
      {
        os.write(buf);
      }
    }
  }

  /**
   * Returns true if the encoding is CONSTRUCTED
   */
  public boolean isConstructed()
  {
    return (TAG_CONSTRUCTED == (tag & MASK_CONSTRUCTED));
  }

  /**
   * Returns true if the TAG CLASS is UNIVERSAL
   */
  public boolean isClassUniversal()
  {
    return (TAG_CLASS_UNIVERSAL == (tag & MASK_CLASS));
  }

  public final void info() throws IOException
  {
    StringBuffer sb = new StringBuffer();
    info(sb, 0);
    System.out.println(sb.toString());
  }

  ////////////////////////////////////////////////////////////////
  // encoding routines
  ////////////////////////////////////////////////////////////////

  private boolean lengthKnown()
  {
    return this.lengthKnown;
  }

  private void writeLengthOctets(int in, OutputStream os)
    throws IOException
  {
    if (in < 128) 
    {
      //Short form of Length Octets
      os.write(in);
    }
    else
    {
      //Long form of Length Octets
      byte[] buf = new byte[16];
      int i = 0;
      do
      {
        buf[i++] = (byte)in;
        in >>>= 8;
      }
      while (in != 0);

      os.write((byte)(i | 0x80));
      for (int j=0; j<i; j++)
        os.write(buf[i-1-j]);
    }
  }

  ////////////////////////////////////////////////////////////////
  // decoding routines
  ////////////////////////////////////////////////////////////////

  /**
   * Helper method to decode the ASN.1 encoding in the
   * supplied InputStream. The InputStream is expected
   * to be positioned at the start of the length octets
   * before this call.
   *
   * <p>If the encoding is definite-length we fully decode
   * into memory and if successful the stream will be positioned
   * after the end of the encoding. 
   *
   * <p>If the encoding is indefinite-length, decoding will be
   * postponed until calls to components().next().
   */
  private void decode(int tag, InputStream is) throws IOException
  {
    this.state = DECODING;
    this.tag = tag;
    this.encodingLength++;

    readLength(is);

    //Constructed encoding
    if (isConstructed())
    {
      Asn1 comp;

      //Indefinite-length encoding
      if (!lengthKnown())
      {
        this.it = new Asn1ComponentIterator(is);
      }
      //Definite-length encoding
      else
      {
        // Decode all components
        int compLength = 0;
        this.components = new Vector(); //?
    
        while (true)
        {
          if (compLength == this.length)
            break;

          comp = getAsn1(is);
          this.components.add(comp);                          //////
    
          compLength += comp.encodingLength;
          this.encodingLength += comp.encodingLength;
        }
      }
    }
    //Primitive encoding
    else
    {
      readValue(is);
    }
  }

  /**
   * Reads and returns the tag from the supplied InputStream
   */
  private static int readTag(InputStream is) throws IOException
  {
    int retval = is.read();

    if (retval == -1)
      throw new IOException("Unexpected end of stream encountered");

    return retval;
  }

  /**
   * Reads the length octets from the supplied InputStream
   * into the length variable. The encoding length is
   * incremented. 
   * 
   * <p> If the encoding uses an indefinite-length method, 
   * the lengthUnknown variable is set to true.
   */
  private void readLength(InputStream is) throws IOException
  {
    byte firstOct = (byte)(is.read() & 0xff);
    this.encodingLength++;

    //Check if it is an indefinite-length encoding
    if (firstOct == (byte)0x80)
    {
      this.lengthKnown = false;
      this.length = -1;
      return;
    }

    if ((firstOct & 0x80) == 0) 
    {
      this.lengthKnown = true;
      this.length = firstOct;
    } 
    else 
    {
      //Long. Additional length octets present
      int len = firstOct & 0x7f;
      byte[] additional = new byte[len];

      this.encodingLength += len;

      int rd = 0;
      while (true)
      {
        if (rd == len) break;
        try {      // in case, it terminate premature
          rd += is.read(additional, rd, len - rd);
        } catch (IndexOutOfBoundsException err) {
          throw new IOException(err.toString());
        }
      }
      this.length = 0;
      for (int j=0; j < len; j++)
      {
        this.length |= ((additional[j] & 0xff) << 8*(len - 1 -j));
      }
    }
  } 

  /**
   * Reads the content octets from the supplied InputStream
   * into the value variable. The encoding length is
   * incremented.
   */
  private void readValue(InputStream is) throws IOException
  {
    if (length == 0) 
    {
      this.value = new byte[0];
      return;
    }

    this.value = new byte[length];
    int rd = 0;
    while (true)
    {
      if (rd == length) break;
      try {
        rd += is.read(this.value, rd, length - rd);
      } catch (IndexOutOfBoundsException err) {
        throw new IOException(err.toString());
      }
    }
    this.encodingLength += this.length;
  }

  //////////////////////////////////////////////////////////////////////
  // info
  //////////////////////////////////////////////////////////////////////

  private void info(StringBuffer infoSb, int dep) throws IOException
  {
if (debug)
{
    depth = dep+1;
    spit(infoSb);

    switch(getTagClass())
    {
      case (TAG_CLASS_APPLICATION):
        infoSb.append("[APPLICATION " + getTagNumber() + "]");
        break;

      case (TAG_CLASS_CONTEXT):
        infoSb.append("[CONTEXT-SPECIFIC " + getTagNumber() + "]");
        break;

      case (TAG_CLASS_PRIVATE):
        infoSb.append("[PRIVATE " + getTagNumber() + "]");
        break;

      case (TAG_CLASS_UNIVERSAL):
        switch(getTagNumber())
        {
          case (TAG_OCTETSTRING):
            infoSb.append("OCTET STRING");
            break;
    
          case (TAG_INTEGER):
            infoSb.append("INTEGER");
            break;
    
          case (TAG_OID):
            infoSb.append("OBJECT IDENTIFIER ");
            infoSb.append(((Oid)this).getOid()).append("\n");
            return;
    
          case (TAG_BOOLEAN):
            infoSb.append("BOOLEAN ");
            if (((Boolean)this).isTrue())
              infoSb.append("TRUE\n");
            else
              infoSb.append("FALSE\n");
            return;
    
          case (TAG_BITSTRING):
            infoSb.append("BIT STRING");
            printHex(infoSb, ((BitString)this).getBytes());
            return;
    
          case (TAG_UTCTIME):
            infoSb.append("UTC TIME ");
            infoSb.append(((UTCTime)this).getTime()).append("\n");
            return;
    
          case (TAG_GENERALIZEDTIME):
            infoSb.append("GENERALIZED TIME ");
            infoSb.append(new String(this.value)).append("\n");
            return;
    
          case (TAG_NULL):
            infoSb.append("NULL").append("\n");
            return;
    
          case (TAG_SEQUENCE):
            infoSb.append("SEQUENCE");
            break;

          case (TAG_SET):
            infoSb.append("SET");
            break;

          case (TAG_PRINTABLESTRING):
          case (TAG_T61STRING):
          case (TAG_IA5STRING):
          case (TAG_VISIBLESTRING):
          case (TAG_GENERALSTRING):
          case (TAG_UTF8STRING):
          case (TAG_UNIVERSALSTRING):
          case (TAG_BMPSTRING):
            infoSb.append(((Asn1String)this).stringType).append(" STRING ");
            infoSb.append("'").append(((Asn1String)this).getString()).append("'\n");
            return;

          default:
            break;
        }
    }

    if (isConstructed())
    {
      infoSb.append(" {\n");
      Iterator it = components();
      while (it.hasNext())
      {
        Asn1 next = (Asn1)it.next();

        if (next == null)
          break;

        next.info(infoSb, depth);
      }
      spit(infoSb); infoSb.append("}\n");
    }
    else
      printHex(infoSb, value);
}
  }

  private final void spit(StringBuffer infoSb)
  {
    for (int i=0; i<this.depth; i++)
      infoSb.append("  ");
  }

  private final void printHex(StringBuffer infoSb, byte bytes[])
  {
    if (bytes != null)
    {
      for (int i=0; i<bytes.length; i++)
      {
        if (i%16 == 0)
        {
          infoSb.append("\n ");
          for (int j=0; j<this.depth; j++)
          {
            infoSb.append("  ");
          }
        }
        infoSb.append(hexDigit(bytes[i])).append(" ");
      }
    }
    infoSb.append("\n");
  }

  private static final String hexDigit(byte x)
  {
    char ret[] = new char[2];
    char c = (char) ((x >> 4) & 0xf);
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

  /**
   *  An iterator to return components of an indefinite-length encoding
   *  during the decoding process. <p>
   *
   *  Memory considerations mean that parsing is done only when
   *  necessary. <p>
   *
   *  Note:<p>
   *
   *  If you call the <code>hasNext()</code> method after <code>next()</code>
   *  the iterator of the previous component will no longer be able to
   *  access subcomponents. <p>
   *
   *  Example: This will work <p>
   *  <pre>
   *
   *    Vector two = new Vector();
   *    Vector three = new Vector();
   *
   *    Iterator it = sequence.components();
   *    if ( it.hasNext() )
   *    {
   *      Sequence seq2 = (Sequence) it.next();
   *      Iterator it2 = seq2.components();
   *      if( it2.hasNext( two.add( it2.next() ) );
   *    }
   *
   *    if ( it.hasNext() )
   *    {
   *      Sequence seq3 = (Sequence) it.next();
   *      Iterator it3 = seq3.components();
   *      if( it3.hasNext( three.add( it3.next() ) );
   *    }
   *
   *  </pre>
   *
   *  This will NOT work <p>
   *
   *  <pre>
   *
   *    Vector two = new Vector();
   *    Vector three = new Vector();
   *
   *    Sequence seq2, seq3 = null;
   *
   *    Iterator it = sequence.components();
   *    if ( it.hasNext() )
   *    {
   *      seq2 = (Sequence) it.next();
   *    }
   *    if ( it.hasNext() )               // This call will wipe
   *    {                                 // the iterator of seq2.
   *      seq3 = (Sequence) it.next();
   *    }
   *
   *    Iterator it2 = seq2.components();
   *    Iterator it3 = seq3.components();
   *
   *    if( it2.hasNext( two.add( it2.next() ) );
   *    if( it3.hasNext( three.add( it3.next() ) );
   *
   *  </pre>
   */
  class Asn1ComponentIterator implements Iterator
  {
    private InputStream is;
    private boolean hasNext = true;
    private Asn1 next = null;
    private Asn1 previous = null;

    Asn1ComponentIterator(InputStream is)
    {
      this.is = is;
    }

    /**
     *  This method reads the next ASN.1 type from the InputStream. <p>
     */
    public boolean hasNext()
    {
      if ( false == this.hasNext )
      {
        return this.hasNext;
      }

      // Assertion: true == this.hasNext

      //  Check if a read ahead has already been performed.
      //  If so return the value of hasNext.
      if ( null != this.next )
      {
        return this.hasNext; // true
      }

      // Assertion: null == this.next AND true == this.hasNext

      // As null == next attempt to get next component.

      // If this is constructed we need to parse all the subcomponents
      // from the Input Stream
      //
      // XXX. This isn't necessary for definate-length encoded objects
      //      so should probably have some sort of test to determine this.
      //      The main concern here is that definate-length encodings
      //      inside an indefinate length encoding may be a common
      //      occurance.
      if ( null != this.previous )
      {
        if ( this.previous.isConstructed() )
        {
          Iterator it = this.previous.components();
          while ( it.hasNext() )
          {
            Asn1 comp = (Asn1) it.next();
          }
        }
        this.previous = null;
      }

      this.next = this.read();
      // XXX Comment "need to clone!!" was originally put under
      //     the original read() line. WHY??

      // If there was not another component next will be null.
      if ( null == this.next )
      {
        this.hasNext = false;
      }

      return this.hasNext;
    }

    public Object next()
    {
      // If no next element throw exception.
      // hasNext() will set this.next if it returns true.
      if ( false == hasNext() )
      {
        throw new java.util.NoSuchElementException();
      }

      this.previous = this.next;
      this.next = null;

      return this.previous;
    }

    //Reads an Asn1 from the InputStream and returns it
    //unless it's an end-of-octets marker or if there is
    // is a decoding error, in which cases null is returned
    private Asn1 read()
    {
      try
      {
        Asn1 cp = getAsn1( this.is );

        //end-of-octets reached
        if ( cp.tag == 0 && cp.length == 0 )
        {
          return null;
        } else {
          return cp;
        }
      }
      catch (IOException e)
      {
        throw new RuntimeException( "Asn1DecodingException" + e.toString() );
        //XXX... shouldn't this return null??? ie. decoding error la
      }
    }

    /**
     *  XXX. This would be a little hard to implement seeing
     *       as we are reading from an InputStream. <p>
     */
    public void remove()
    {
      //throw new
      //    UnsupportedOperationException( "Asn1ComponentIterator.remove()" );
    }
  }

  /**
   * Successive calls to this method will return (upon concatenation)
   * the content octets of a constructed, indefinite-length BER encoding for 
   * an OctetString whose contents is obtained from contentsIn. When
   * there are no more content octets, null with be returned.
   *
   * <p>NB: Need to remove assumption on OctetString by
   * introducing an Asn1 TLV constructor. For now, we don't support
   * constructed, indefinite-length BER encoding of any other primitive type
   */
  private byte[] encodeFromStream() 
    throws IOException, Asn1Exception
  {
    byte[] buf = new byte[BER_BUF_LEN];

    int rd = contentsIn.read(buf);
    if (rd == -1)
    {
      return null;
    }
    else
    {
      return (new OctetString(buf, 0, rd)).getEncoded();
    }
  }

  /**
   * Successive calls to this method will return (upon concatenation)
   * the BER encoding for the current Asn1. When there are no more
   * encoding bytes to return, null will be returned.
   *
   * NB: The size of the arrays returned depends on the particular
   * encoding. Eg. for a DER encoding of the current Asn1. the whole
   * encoding will be returned in one go. For a constructed indefinite-
   * length BER encoding of an OctetString, the encoding will be returned
   * in BER_BUF_LEN chunks.
   *
   * NB: This method only makes sense during encoding.
   */
  public byte[] berEncode() 
    throws IOException, Asn1Exception
  {
    if (done)
    {
      return null;
    }

    if (lengthKnown())
    {
      done = true;
      return getEncoded();
    }
    else
    {
      if (!headerDone)
      {
        headerDone = true;
        return new byte[]{((byte)(0xff & this.tag)), (byte)0x80};
      }
      else
      {
        if (this.contentsIn != null)
        {
          byte[] retval = encodeFromStream();
          if (retval == null)
          {
            done = true;
          }
          else
          {
            return retval;
          }
        }
        else
        {
          byte[] buffer = null;
          while (true)
          {
            if (encIt == null)
            {
              encIt = components.iterator();
              if (encIt == null)
              {
                break;
              }
              encComp = (Asn1)encIt.next();
            }

            buffer = encComp.berEncode();

            if (buffer == null)
            {
              if (encIt.hasNext())
              {
                encComp = (Asn1)encIt.next();
              }
              else
              {
                done = true;
                break;
              }
            }
            else
            {
              return buffer;
            }
          }
        }
      }

      return new byte[2]; //end-of-contents octets
    }
  }

  /**
   * Successive calls to this method will return (upon concatenation)
   * the "value" of the current Asn1. When there are no more value bytes 
   * to return, null will be returned.
   *
   * NB: This method only makes sense during decoding.
   */
  public byte[] writeValue()
  {
    if (done)
    {
      return null;
    }

    //primitive encoding
    if (!isConstructed())
    {
      done = true;
      return this.getValue();
    }
    //constructed encoding
    else
    {
      if (encIt == null)
      {
        encIt = components();
        encComp = (Asn1)encIt.next();
      }
      else
      {
        if (encComp.done)
        {
          if (encIt.hasNext())
          {
            encComp = (Asn1)encIt.next();
          }
          else
          {
            done = true;
            return null;
          }
        }
      }           

      if (encComp == null)
      {
        done = true;
        return null;
      }
      else
      {
        byte[] retval = encComp.writeValue();
        if (retval == null)
        {
          done = true;
        }
        return retval;
      }
    }
  }
}
