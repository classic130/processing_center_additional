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

package com.dstc.security.x509;

import java.io.*;

import java.util.Iterator;
import java.util.Vector;
import java.util.Date;
import java.util.Calendar;
import java.util.TimeZone;

import com.dstc.security.asn1.*;

/**
 * <p>A class representing the x.509 ASN.1 structure Validity.
 *
 * <pre>
 *    Validity ::= SEQUENCE {
 *       notBefore      CertificateValidityDate,
 *       notAfter       CertificateValidityDate }
 *  
 *    CertificateValidityDate ::= CHOICE {
 *       utcTime        UTCTime,
 *       generalTime    GeneralizedTime }
 * </pre>
 *
 * <p>Currently only handles GMT
 *
 * @version 0.98, 98/07/01
 * @author Ming Yung
 */
public class Validity
{
  private Asn1 asn1 = null;
  private Date notBefore;
  private Date notAfter;

  public Validity(InputStream is) throws IOException
  {
    this(Asn1.getAsn1(is));
  }

  public Validity(Asn1 asn1) 
  {
    this.asn1 = asn1;

    Iterator it = asn1.components();

    this.notBefore = ((UTCTime)it.next()).getDate();
    this.notAfter = ((UTCTime)it.next()).getDate();
  }

  /**
   * Constructs a Validity from a period in days
   */
  public Validity(int days)
  {
    Calendar cal = Calendar.getInstance(TimeZone.getTimeZone("GMT"));
    Date now = cal.getTime();
    cal.add(Calendar.DATE, days);
    encode(now, cal.getTime());
  }

  /**
   * Constructs a Validity given now and notAfter
   */
  public Validity(Date notBefore, Date notAfter)
  {
    encode(notBefore, notAfter);
  }
 
  void encode(Date notBefore, Date notAfter)
  {
    this.asn1 = new Sequence();
 
    this.notBefore = notBefore;
    this.asn1.add(new UTCTime(notBefore));
 
    this.notAfter = notAfter;
    this.asn1.add(new UTCTime(notAfter));
  }

  public Asn1 getAsn1()
  {
    return this.asn1;
  }

  /**
   * Returns a string representation of this Validity
   */
  public String toString() 
  {
    StringBuffer sb = new StringBuffer("Not Before: ");
    sb.append(notBefore.toString());
    sb.append("\nNot After: ");
    sb.append(notAfter.toString());
    return sb.toString();
  }

  /**
   * Returns notBefore as a Java Date
   */
  public Date getNotBefore() 
  {
    return notBefore;
  }

  /**
   * Returns notAfter as a Java Date
   */
  public Date getNotAfter() 
  {
    return notAfter;
  }
}
