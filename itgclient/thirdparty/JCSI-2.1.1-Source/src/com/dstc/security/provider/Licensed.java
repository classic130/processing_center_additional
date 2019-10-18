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

package com.dstc.security.provider;

import com.dstc.security.util.License;


/**
 * Dummy interface (hack) to perform static licence check.  
 * <p>
 * If a class wants to check, when the class is first used, that the user has 
 * a valid licence, the class should contrive to refer to the {@link #VALID}
 * field here.  When the class is first initialized, the classloader will
 * also initialize this interface (if it has not already been initialized),
 * which will initialize the {@link #VALID}
 * field, which will invoke the license-checking code.
 * <p>
 * Classes (such as the DSTC Provider class) that do <em>not</em> want to 
 * invoke the licence-checking code should not refer to this field.
 * (Otherwise, if the JAR file is installed in jre/lib/ext and the provider 
 * is listed in jre/lib/security/java.security, then java.security.Security
 * will load the provider and would trigger the licence check, even for Java
 * code that didn't use the provider at all).
 * <p>
 * We have a copy of this interface in each package where it is needed, 
 * rather than just one copy in com.dstc.security.util, so that if we decide 
 * to implement per-package licensing then we will only have to tweak one
 * place (i.e. this interface) in each package.
 */
interface Licensed
{
  /** Dummy, used only to trigger call to {@link License#check()} */
  boolean VALID = License.check();
}
