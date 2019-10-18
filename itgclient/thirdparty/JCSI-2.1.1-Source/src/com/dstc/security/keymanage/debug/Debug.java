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

package com.dstc.security.keymanage.debug;

import java.io.File;
import java.io.FileOutputStream;
import java.io.PrintStream;

import com.dstc.security.asn1.Asn1;

/**
 *  Includes methods which aid debugging. <p>
 *
 *  @author Daniel Bradley.
 */
public class Debug
{
  //---------------------------------------------------------------------------
  // Public Static Final Members
  //---------------------------------------------------------------------------

  // Debug Message Priority Levels
  //
  public static final int NONE      = 1000;
  public static final int EMERGENCY = 8;
  public static final int ALERT     = 7;
  public static final int CRITICAL  = 6;
  public static final int ERROR     = 5;
  public static final int WARNING   = 4;
  public static final int NOTICE    = 3;
  public static final int INFO      = 2;
  public static final int DEBUG     = 1;
  public static final int ALL       = 0;

  // Debug Message Sources
  //
  // should I have these???

  // ASN.1 Types --> Filename Mappings
  //
  public static final String AUTHENTICATEDSAFE = "authenticatedsafe";
  public static final String MACDATA           = "macdata";
  public static final String PFX               = "pfx";
  public static final String SAFEBAG           = "safebag";
  public static final String SAFECONTENTS      = "safecontents";
  public static final String CERTBAG           = "certbag";
  public static final String KEYBAG            = "keybag";
  public static final String SHROUDEDKEYBAG    = "shroudedkeybag";
  public static final String UNKNOWNBAG        = "unknownbag";
  public static final String CERT              = "cert";

  public static final String SAFEBAG_W_CERTBAG = "safebagWcertbag";

  //---------------------------------------------------------------------------
  //  Private Static Members
  //---------------------------------------------------------------------------

  /**
   *  This member determines the output stream debug information
   *  is written to. <p>
   */
  private static PrintStream debug = System.err;

  /**
   *  All messages of this debug level and higher will be written to
   *  the debug output stream. <p>
   */
  private static int debugLevel = NONE;

  /**
   *  All dumps of this dump level and higher will be dumped to the dump
   *  directory. <p>
   */
  private static int dumpLevel = NONE;

  /**
   *  The standard directory for tempory files on a given platform. <p>
   */
  private static final String tmpdir = System.getProperty( "java.io.tmpdir" );

  /**
   *  The name of the directory under tmpdir that will be used for
   *  dump files.
   */
  private static String dumpDirName = "key_manage_dump";

  /**
   *  Dumped ASN.1 files are appended with this POSTFIX. <p>
   */
  private static final String POSTFIX = ".asn1";

  /**
   *  The directory dump files are saved to. <p>
   *
   *  This is initialized in the <code>dumpAsn1To</code> method. <p>
   */
  private static File dumpDir;

  //---------------------------------------------------------------------------
  //  Accessors
  //---------------------------------------------------------------------------

  public static String getDumpDirName()
  {
    return dumpDirName;
  }

  //---------------------------------------------------------------------------
  //  Mutators
  //---------------------------------------------------------------------------

  public static void setDebugStream( PrintStream ostream )
  {
    debug = ostream;
  }

  public static void setDebugLevel( int level )
  {
    debugLevel = level;
  }

  public static void setDumpLevel( int level )
  {
    dumpLevel = level;
  }

  public static void setDumpDirName( String name )
  {
    dumpDirName = name;
    dumpDir = null;
  }

  //---------------------------------------------------------------------------
  //  Operations
  //---------------------------------------------------------------------------

  /**
   *  Used to print debug messages to the debug output stream. <p>
   */
  public static void log( int level, String source, String message )
  {
    if ( shouldDebug( level ) )
    {
      debug.print( source + ": " );
      debug.println( message );
    }
  }

  /**
   *  Used to decide whether to do a debug action or not. <p>
   *
   *  @return true if <code>level >= debugLevel</code>.
   */
  public static boolean shouldDebug( int level )
  {
    if ( level >= debugLevel )
    {
      return true;
    }
    else
    {
      return false;
    }
  }

  public static boolean shouldDump( int level )
  {
    boolean ret = ( level >= dumpLevel );
    return ret;
//     if ( level >= dumpLevel )
//     {
//       return true;
//     }
//     else
//     {
//       return false;
//     }
  }

  /**
   *  Dumps the asn1 to a file. <p>
   */
  public static void dumpAsn1To( Asn1 asn1, String ASN1NAME )
  {
    if( shouldDump( Debug.DEBUG ) )
    {
      if( null == dumpDir )
      {
        try
        {
          dumpDir = new File( tmpdir + File.separator + getDumpDirName() );
          dumpDir.mkdirs();
        }
        catch( Exception ex )
        {
          Debug.log( Debug.ERROR, "Debug.dumpAsn1To", ex.toString() );
          return;
        }
      }

      log( INFO, "Debug.dumpAsn1To()",
          "Dumping ASN.1 encoded object to: " + ASN1NAME );
      try
      {
        File dump = File.createTempFile( ASN1NAME, POSTFIX, dumpDir );
        byte[] bytes = asn1.getEncoded();
        FileOutputStream fos
            = new FileOutputStream( dump );
        fos.write( bytes );
        fos.close();
      }
      catch ( Exception ex ) {
        Debug.log( Debug.ERROR, "Debug.dumpAsn1To", ex.toString() );
      }
    }
  }
}
