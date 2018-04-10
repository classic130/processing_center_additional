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
import java.util.Collection;
import java.util.Iterator;
import java.util.Vector;

//JCSI
import com.dstc.security.asn1.Asn1;
import com.dstc.security.asn1.Asn1Exception;
import com.dstc.security.asn1.Sequence;
import com.dstc.security.asn1.BMPString;
import com.dstc.security.asn1.VisibleString;
import com.dstc.security.asn1.UTF8String;

/**
 * This is a Class representing of the policyQualifier - UserNotice
 *
 * <pre>
 *    NoticeReference ::= SEQUENCE {
 *      organization     DisplayText,
 *      noticeNumbers    SEQUENCE OF INTEGER 
 *    }
 * </pre> 
 *
 * @see com.dstc.security.x509.extns.UserNotice
 *
 * @author Eddy Cheung
 */
public class NoticeReference
{
  private Asn1 asn1;
  private DisplayText organisation;
  private Collection noticeNumber;

  /**
   * Construct a NoticeReference using DisplayText and Collection of Integer
   **/
  public NoticeReference(DisplayText text, Collection numbers)
  {
    this.asn1 = new Sequence();
    
    //organisation
    organisation = text;

    ((Sequence)asn1).add(organisation.getAsn1());

    //noticeNumber
    Sequence seq = new Sequence();
    Iterator i = numbers.iterator();
    while (i.hasNext()) {
      seq.add(new com.dstc.security.asn1.Integer
        (((java.lang.Integer)i.next()).intValue()));
    }
    ((Sequence)asn1).add(seq);
  }

  /**
   * Construct a NoticeReference from DER encoded message
   **/
  public NoticeReference(Asn1 asn1) throws Asn1Exception
  {
    this.asn1 = asn1;
    
    Iterator i = asn1.components();

    //Organisation
    this.organisation = new DisplayText((Asn1)i.next());
    
    //NoticeNumber
    Iterator iseq = ((Sequence)i.next()).components();
    this.noticeNumber = new Vector();
    while (iseq.hasNext()) {
      noticeNumber.add(new java.lang.Integer(
        ((com.dstc.security.asn1.Integer)iseq.next()).getInt()
        ));
    }
  }

  /**
   * Return Asn1 for this object
   **/
  public Asn1 getAsn1()
  {
    return this.asn1;
  }
   
  /** 
   * Return the Text
   **/
  public String getText()
  {
    return this.organisation.getText();
  } 

  /**
   * Return the Notice Number in form of collection of integer
   * 
   **/
  public Collection getNoticeNumber()
  {
    return this.noticeNumber;
  }

  /**
   * toString
   **/
  public String toString() 
  {
    StringBuffer sb = new StringBuffer();
    //Organisation
    sb.append("   Organisation: " + organisation.toString() + "\n");
    //Notice Number
    sb.append("   Notice Number: ");
    Iterator i = this.noticeNumber.iterator();
    while (i.hasNext()) {
      sb.append(i.next() + " ");
    }
    sb.append("\n");
    return sb.toString();
  }
}
