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

//JDK1.2
import java.util.Iterator;
//JCSI
import com.dstc.security.asn1.Asn1;
import com.dstc.security.asn1.Sequence;
import com.dstc.security.asn1.BMPString;
import com.dstc.security.asn1.VisibleString;
import com.dstc.security.asn1.UTF8String;
import com.dstc.security.asn1.IA5String;
import com.dstc.security.asn1.Asn1Exception;

/**
 * This is a Class representing of the policyQualifier - UserNotice
 *
 * <pre>
 *    UserNotice ::= SEQUENCE {
 *       noticeRef      NoticeReference OPTIONAL
 *       explicitText   DisplayText OPTIONAL
 *    }
 * </pre> 
 *
 * @see com.dstc.security.x509.extns.PolicyQualifier
 * @see com.dstc.security.x509.extns.CPSuri
 *
 * @author Eddy Cheung
 */
public class UserNotice extends Qualifier
{
  private NoticeReference ref;
  private DisplayText text;

  /**
   * Construct a user notice using NoticeReference and DisplayText
   **/
  public UserNotice(NoticeReference noticeRef, DisplayText displayText)
  {
    this.asn1 = new Sequence();
    
    //NoticeReference
    ref = noticeRef;
    ((Sequence)asn1).add(noticeRef.getAsn1());

    //Display Text
    text = displayText;
    ((Sequence)asn1).add(displayText.getAsn1());
  }

  /**
   * Construct a UserNotice from DER encoded message
   **/
  public UserNotice(Asn1 asn1) throws Asn1Exception
  {
    this.asn1 = asn1;

    Iterator i = asn1.components();

    if (i.hasNext()) {
      Asn1 comp = (Asn1)i.next();

      //NoticeReference?
      if (comp instanceof Sequence) {
        ref = new NoticeReference(comp);
      } 

      //DisplayText
      if (i.hasNext()) {
        comp = (Asn1)i.next();
        if (comp instanceof VisibleString ||
            comp instanceof BMPString ||
            comp instanceof UTF8String ||
            //XXX, Versign Certificate uses non-standard IA5String!
            comp instanceof IA5String) {
          text = new DisplayText(comp);
        } else {
          throw new Asn1Exception("Expecting DisplayText ASN.1 structure");
        }
      }
    }
  }
   
  /** 
   * Return NoticeReference 
   * Note: It can be null
   **/
  public NoticeReference getNoticeReference()
  {
    return this.ref;
  } 

  /**
   * Return the Explicit Text
   * If it is not present, null will be returned
   **/
  public String getExplicitText()
  {
    if (this.text == null) {
      return null;
    } else {
      return this.text.getText();
    }
  }

  /**
   * toString
   **/
  public String toString() 
  {
    StringBuffer sb = new StringBuffer();
    if (this.ref != null) {
      sb.append(this.ref.toString());
    } 
    if (this.text != null) {
      sb.append("   Explicit Text: " + this.text.toString() + "\n");
    }
    return sb.toString();
  }
}
