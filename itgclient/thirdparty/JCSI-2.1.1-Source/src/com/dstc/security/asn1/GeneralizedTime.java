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

import java.io.*;
import java.util.Calendar;
import java.util.TimeZone;
import java.util.Date;
import java.util.StringTokenizer;

/**
 * <p>A class representing the ASN.1 type GeneralizedTime.
 *
 * @see com.dstc.security.asn1.Asn1
 *
 * @version 0.98, 98/07/01
 * @author Ming Yung
 */
public class GeneralizedTime extends Asn1
{
  protected boolean includeSeconds = true;
  protected boolean fourDigitYear = true;
  protected Calendar cal = Calendar.getInstance(TimeZone.getTimeZone("GMT"));

  public GeneralizedTime() 
  {
    init();
  }

  public GeneralizedTime(Date date)
  {
    this();

    cal.setTime(date);
    setTime();
  }

  protected void init()
  {
    this.tag = TAG_GENERALIZEDTIME;
  }

  /**
   * Constructs a GeneralizedTime from an hour offset (0 for current time)
   */
  public GeneralizedTime(int offset)
  {
    this();

    cal.add(Calendar.HOUR_OF_DAY, offset);
    setTime();
  }

  public GeneralizedTime(String time)
  {
    this();

    this.value = time.getBytes();
  }

  void setTime()
  {
    StringBuffer now = new StringBuffer();

    if (fourDigitYear)
      now.append(cal.get(Calendar.YEAR));
    else
      now.append(String.valueOf(cal.get(Calendar.YEAR)).substring(2, 4));

    append(now, cal.get(Calendar.MONTH) + 1);
    append(now, cal.get(Calendar.DATE));
    append(now, cal.get(Calendar.HOUR_OF_DAY));
    append(now, cal.get(Calendar.MINUTE));

    if (includeSeconds)
      append(now, cal.get(Calendar.SECOND));

    now.append("Z");
    this.value = now.toString().getBytes();
  }

  public String getTime()
  {
    return new String(this.value);
  }

  public Date getDate()
  {
    String utc = new String(this.value);

    if (utc.endsWith ("Z"))
    {
      int year, month, date, hour, minute;
      int second = 0;

      int ind = 0;

      if (fourDigitYear) {
        year = java.lang.Integer.parseInt(utc.substring(ind, ind + 4));
        ind += 2;
      }
      else {
        year = java.lang.Integer.parseInt(utc.substring(ind, ind + 2));
        year += (year >= 50) ? 1900 : 2000;
      }

      month = java.lang.Integer.parseInt(utc.substring(ind + 2, ind + 4)) - 1;
      date = java.lang.Integer.parseInt(utc.substring(ind + 4, ind + 6));
      hour = java.lang.Integer.parseInt(utc.substring(ind + 6, ind + 8));
      minute = java.lang.Integer.parseInt(utc.substring(ind + 8, ind + 10));

      if (includeSeconds && utc.length() > ind + 12) {
        second = java.lang.Integer.parseInt(utc.substring(ind + 10, ind + 12));
      }

      cal.set(year, month, date, hour, minute, second);
      cal.set(Calendar.MILLISECOND, 0);
    }
    Date retval = cal.getTime();
    return retval;
  }

  private void append(StringBuffer sb, int number)
  {
    if (number < 10)
      sb.append("0" + number);
    else
      sb.append(number);
  }
}
