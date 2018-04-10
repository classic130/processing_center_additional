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

package com.dstc.security.x509.extns;

//JCSI
import com.dstc.security.asn1.Asn1;
import com.dstc.security.asn1.Asn1Exception;
import com.dstc.security.asn1.Asn1String;
import com.dstc.security.asn1.VisibleString;
import com.dstc.security.asn1.BMPString;
import com.dstc.security.asn1.UTF8String;
import com.dstc.security.asn1.IA5String;

/**
 * This is a Class representing -  DisplayText
 *
 * <pre>
 *    DisplayText   ::= Choice {
 *       visibleString    VisibleString (Size (1..200)),
 *       bmpString        BMPString     (Size (1..200)),
 *       utf8String       UTF8String    (Size (1..200))   
 *    }
 * </pre> 
 *
 * @see com.dstc.security.x509.extns.NoticeReference
 * @see com.dstc.security.x509.extns.UserNotice
 *
 * @author Eddy Cheung
 */
public class DisplayText
{
  private Asn1String text;
  private final static int MAX_TEXT_LENGTH = 200;

  /**
   * Construct DisplayText with either visibleString, 
   * BMPString or UTF8String
   **/
  public DisplayText(Asn1String text)
  {
    //Check if it is one of the allowed type
    if (text instanceof VisibleString ||
        text instanceof BMPString ||
        text instanceof UTF8String) {
      //Check for its length
      if (text.getString().length() <= MAX_TEXT_LENGTH) {
        this.text = text;
      } else {
        throw new IllegalArgumentException("Text exceed allowed length (200)");
      }
    } else {
      throw 
        new IllegalArgumentException("Only VisibleString, BMPString or UTF8String allowed");
    }
  }
        
  /**
   * Construct DisplayText using DER encoded Asn1
   **/
  public DisplayText(Asn1 asn1) throws Asn1Exception
  {
    if (asn1 instanceof VisibleString || 
        asn1 instanceof BMPString ||
        asn1 instanceof UTF8String) {      
      this.text = (Asn1String)asn1;
    } else if (asn1 instanceof IA5String) {
      //XXX, Verisign certificate uses non-standard IA5String
//    System.out.println("Warning: IA5String found in DisplayText " 
//                       + "(CertificatePolicies. Continued...");
      this.text = (Asn1String)asn1;
    } else {
      throw new Asn1Exception("Expecting VisibleString, BMPString, " +
                            "UTF8String in DisplayText " + asn1);
    }
    //XXX TODO, check for the length
  }

  /**
   * Return the Asn1 encoding of this object
   **/
  public Asn1 getAsn1() 
  {
    return this.text;
  }
   
  /** 
   * Return the Text
   **/
  public String getText()
  {
    return this.text.getString();
  } 

  /**
   * toString
   **/
  public String toString() 
  {
    return getText();
  }
}
