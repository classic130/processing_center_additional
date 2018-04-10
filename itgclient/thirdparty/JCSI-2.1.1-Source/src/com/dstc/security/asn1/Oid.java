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
import java.util.StringTokenizer;

/**
 * <p>A class representing the ASN.1 type Object Identifier.
 *
 * @see com.dstc.security.asn1.Asn1
 *
 * @version 0.98, 98/07/01
 * @author Ming Yung
 */
public class Oid extends Asn1
{
  public Oid() 
  {
    this.tag = TAG_OID;
  }

  public Oid(String oid)
  {
    this();
    this.value = toContents(oid);
  }

  public String getOid()
  {
    StringBuffer retval = new StringBuffer ();
    retval.append(value[0] / 40 );
    retval.append("." + value[0] % 40 );
    int next = 0;
    for (int i=1; i< value.length; i++)
    {
      if ((value[i] & 0x80) == 0)
      {
        //bit not set; therefore last
        next = (next << 7) | value[i];
        retval.append("." + next);
        next = 0;
      }
      else
      {
        next = (next << 7) | (value[i] & 0x7f);
      }
    }
    return retval.toString();
  }

  private static final byte[] toContents(String oid) 
  {
    StringTokenizer tknz = new StringTokenizer(oid, ".", false);
    int in[] = new int[tknz.countTokens ()];
    for (int i=0; i<in.length; i++) 
    {
      in[i] = java.lang.Integer.parseInt(tknz.nextToken ());
    }
    //Converts in to base 128
    byte bytes[] = new byte[50];
    int next, index = 0;
    boolean isFirst;
    for (int i=in.length - 1; i > 1; i--) 
    {
      next = in[i];
      isFirst = true;
      while (true) 
      {
        bytes[index] = (byte) ((next & 0x7f) | 0x80);
        if (isFirst) bytes[index] &= 0x7f;
        next = next >>> 7;
        index++;
        isFirst = false;
        if (next == 0) break;
      }
    }
    byte retval[] = new byte[index+1];
    for (int i=1; i<index+1; i++) 
    {
      retval[i] = bytes[index-i];
    }
    retval[0] = ((byte)(40*in[0] + in[1]));
    return retval;
  }
}
