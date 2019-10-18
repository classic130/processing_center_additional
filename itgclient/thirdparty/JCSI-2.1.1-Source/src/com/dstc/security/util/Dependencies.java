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

package com.dstc.security.util;

import java.net.URL;
import java.net.URLConnection;
import java.net.JarURLConnection;
import java.util.jar.Manifest;
import java.util.jar.Attributes;
import java.util.jar.Attributes.Name;
import java.util.StringTokenizer;

public class Dependencies
{
  // Exists in JDK 1.3 but not in 1.2, so duplicate them here
  public static final Name EXTENSION_LIST        = new Name("Extension-List");
  public static final Name EXTENSION_NAME        = new Name("Extension-Name");
  public static final Name IMPLEMENTATION_VENDOR_ID
    = new Name("Implementation-Vendor-Id");

  public static final Name SPECIFICATION_VERSION = Name.SPECIFICATION_VERSION;
  public static final Name IMPLEMENTATION_VERSION= Name.IMPLEMENTATION_VERSION;
  public static final Name IMPLEMENTATION_VENDOR = Name.IMPLEMENTATION_VENDOR;

  /**
   * Given a Class, determine where the class was loaded from (e.g a JAR file)
   * and return the relevant Manifest, or <code>null</code> otherwise.
   */
  public static Manifest getManifest(Class classInJar)
  {
    // Approaches that don't cut it:
    //
    //   (1) classInJar.getResource("/META-INF/MANIFEST.MF") returns the first
    //       resource (manifest) that it finds on the class path, rather than
    //       the relevant one for this class
    //
    //   (2) classInJar.getProtectionDomain().getCodeSource().getLocation()
    //       *might* give us a URL on which we could then do openConnection()
    //       and cast the connection to JarURLConnection -- but (a) it is
    //       roundabout, (b) it triggers permissions checks and privileged
    //       actions, and (c) CodeSource abuses URLs even more blatantly than
    //       the rest of Java does, so openConnection() looks dubious.
    //
    // So... we construct a URL to the class itself and do openConnection(),
    // hoping piously that it's a "jar:" URL and thus a JarURLConnection,
    // which lets us get at the Manifest.

    try {
      String className = classInJar.getName();
      // That's the fully qualified name, we just want the last component
      int lastDot = className.lastIndexOf('.');
      if (lastDot >= 0) {
        className = className.substring(lastDot + 1);
      }

      URL classURL = classInJar.getResource(className + ".class");

      return ((JarURLConnection)classURL.openConnection()).getManifest();
    }
    catch (ClassCastException ex) {
      // Not what we expected, so give up
      return null;
    }
    catch (java.io.IOException ex) {
      // XXX Hmmm...
      return null;
    }

    // No cache at present, assume/hope that we don't get invoked unnecessarily
  }    

  /**
   * @param classInJar any Class whose package is in the JAR file that we
   *        want to check
   * @param checkLicence <code>true</code> if we should also check that the
   *        caller has a valid JCSI licence, <code>false</code> if not
   * @return a String that is the version of the package that classInJar
   *         belongs to, or null if the package/version info is unavailable
   * @exception UnsatisfiedJarDependency if there was a missing JAR file or
   *         a version mismatch
   * @exception InvalidLicense if we checked the license and found it wanting
   */
  public static String check(Class classInJar, boolean checkLicence)
  {
    if (checkLicence)
    {
      License.check();
    }

    Manifest manifest = getManifest(classInJar);
    if (manifest != null) {
      Attributes mainAttrs = manifest.getMainAttributes();
      String extensionList = mainAttrs.getValue(EXTENSION_LIST);
      if (extensionList != null) {
        StringTokenizer st = new StringTokenizer(extensionList);
        while (st.hasMoreTokens()) {
          check(mainAttrs, st.nextToken(), classInJar);
        }
      }
    }

    // All dependencies satisfied;  return own version number
    Package pkg = classInJar.getPackage();
    return (pkg == null) ? null : pkg.getSpecificationVersion();
  }

  /**
   * @exception UnsatisfiedJarDependency if there was a missing JAR file or
   *         a version mismatch
   */
  public static void check(Attributes main, String label, Class classInJar)
  {
    String prefix = label + "-";

    String extName      = main.getValue(prefix + EXTENSION_NAME).trim();

    if (extName == null || extName.length() == 0) {
      // Malformed dependency info -- should we complain?
      return;
    }

    // Similar to getManifest() above, except that we're starting with the
    // name of a package (we hope) rather than with a Class.
    String pkgPath = "/" + extName.replace('.', '/') + '/';
    URL pkgURL = classInJar.getResource(pkgPath);
    Attributes depend;
    try {
      depend = ((JarURLConnection)pkgURL.openConnection()).getMainAttributes();
    }
    catch (ClassCastException ex) {
      // Not what we expected;  give up
      throw new UnsatisfiedJarDependency("No package for Extension-Name: " +
                                         extName);
    }
    catch (java.io.IOException ex) {
      throw new UnsatisfiedJarDependency("Got " + ex + 
                                         " while fetching Manifest for " +
                                         extName);
    }

    checkVersion(prefix, SPECIFICATION_VERSION,    extName, main, depend);
    checkString (prefix, IMPLEMENTATION_VENDOR,    extName, main, depend);
    checkString (prefix, IMPLEMENTATION_VENDOR_ID, extName, main, depend);
    checkVersion(prefix, IMPLEMENTATION_VERSION,   extName, main, depend);

    // FIXME:  what about transitive dependency-checking?  (without loops...)

    return;
  }

  /**
   * @exception UnsatisfiedJarDependency if the string comparison was
   *         not satisfactory.
   */
  public static void checkString(String prefix, Attributes.Name attrName,
                                 String extName,
                                 Attributes main, Attributes depend)
  {
    String attrString = attrName.toString();

    String required = main.getValue(prefix + attrString);
    if (required == null) {
      // No constraints;  declare victory
      return;
    }
    String actual = depend.getValue(attrName);
    if (actual == null) {
      // They didn't tell us, so assume the worst
      throw new UnsatisfiedJarDependency("No " + attrString + " for " +
                                         extName);
    }
    if (! actual.equals(required) ) {
      throw new UnsatisfiedJarDependency("Needed " + attrString + "=" +
                                         required + " for package " +
                                         extName + " but got " + actual);
    }
    // success
    return;
  }

  /**
   * @exception UnsatisfiedJarDependency if the version comparison was
   *         not satisfactory.
   */
  public static void checkVersion(String prefix, Attributes.Name attrName,
                                  String extName,
                                  Attributes main, Attributes depend)
  {
    String attrString = attrName.toString();

    String required = main.getValue(prefix + attrString);
    if (required == null) {
      // No constraints;  declare victory
      return;
    }
    String actual = depend.getValue(attrName);
    if (actual == null) {
      // They didn't tell us, so assume the worst
      throw new UnsatisfiedJarDependency("No " + attrString + " for " +
                                         extName);
    }

    StringTokenizer reqTok = new StringTokenizer(required, ".");
    StringTokenizer actTok = new StringTokenizer(actual,   ".");

    try {
      while (reqTok.hasMoreTokens() && actTok.hasMoreTokens()) {
        int reqVer = Integer.parseInt(reqTok.nextToken());
        int actVer = Integer.parseInt(actTok.nextToken());
        if (actVer > reqVer) {
          // Version is more than good enough
          return;
        } else if (actVer < reqVer) {
          throw lowVersion(attrString, extName, required, actual);
        }
      }
    }
    catch (NumberFormatException ex) {
      throw new UnsatisfiedJarDependency("Malformed " + attrString + ": " +
                                         required + " or " + actual +
                                         " for package " + extName);
    }

    // Fail if 'required' still has unused version digits;  otherwise pass
    if (reqTok.hasMoreTokens()) {
      throw lowVersion(attrString, extName, required, actual);
    }

    // success
    return;
  }

  private static UnsatisfiedJarDependency lowVersion(String versionType,
                                                     String pkg,
                                                     String required,
                                                     String actual)
  { 
    return new UnsatisfiedJarDependency("Needed " + versionType + " >= " +
                                        required + " for package " + pkg +
                                        " but only got " + actual);
  }

  }
