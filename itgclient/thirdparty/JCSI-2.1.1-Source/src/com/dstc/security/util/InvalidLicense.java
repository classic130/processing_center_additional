/*
 * Copyright (C) DSTC Pty Ltd (ACN 052 372 577) 1998, 1999
 * Unpublished work.  All Rights Reserved.
 * 
 * The software contained on this media is the property of the
 * DSTC Pty Ltd.  Use of this software is strictly in accordance
 * with the license agreement in the accompanying LICENSE.DOC file.
 * If your distribution of this software does not contain a
 * LICENSE.DOC file then you have no rights to use this software
 * in any manner and should contact DSTC at the address below
 * to determine an appropriate licensing arrangement.
 * 
 *     DSTC Pty Ltd
 *     Australia
 *     Tel: +61 7 3365 4310
 *     Fax: +61 7 3365 4311
 *     Email: jcsi@dstc.com
 *
 * This software is being provided "AS IS" without warranty of
 * any kind.  In no event shall DSTC Pty Ltd be liable for
 * damage of any kind arising out of or in connection with
 * the use or performance of this software.
 * 
 */

package com.dstc.security.util;


/**
 * Indicates an invalid licence (probably expired).  We use an Error rather 
 * than an Exception so that it will propagate throw "catch (Exception ex)".
 */
public class InvalidLicense extends Error
{
  public InvalidLicense() {
    super();
  }

  public InvalidLicense(String message) {
    super(message);
  }
}
