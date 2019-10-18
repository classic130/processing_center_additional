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

import java.util.Date;
import java.text.FieldPosition;
import java.text.ParseException;
import java.text.SimpleDateFormat;


/**
 * Checks imbedded date against system date for use
 * in time restricted instances.
 */
public class License
{
    private final static String MSG_EXP = "JCSI Evaluation licence expired.";
    private final static String MSG_CON = "jcsi@dstc.com";
    private final static String MSG_TTL = "JCSI Evaluation licence will expire ";
    private final static String EXPIRATION_DATE = "2001/12/21";
    private final static boolean ISEVAL = true;
    private final static boolean isValidLicense;

    /* initialise isValidLicense after checking validity */
    static {
        if (ISEVAL) {
	    isValidLicense = License.isValid(EXPIRATION_DATE);
	} else {
	    isValidLicense = true;
	}
    }

    /**
     * Checks whether licence is valid, throws an Error (!) if not.
     *
     * @exception InvalidLicense if the licence is not valid (probably expired)
     */
    public static boolean check ()
    {
        if (isValid()) {
            return true;
        } else {
            throw new InvalidLicense();
        }
    }

    /**
     * Checks license is valid.
     *<p>
     * @returns True is instance is valid
     */
    public static boolean isValid ()
    {
	return isValidLicense;
    }

    /**
     * Checks timebomb date for the license.
     *<p>
     * @returns True if instance is still "current"; false otherwise.
     */
    public static boolean isValid (String checkDate)
    {
        boolean ok;
        Date bombDate = null;

	    try {
            SimpleDateFormat df = new SimpleDateFormat("yyyy/MM/dd");
            bombDate = df.parse(checkDate);
            ok =  bombDate.after(new Date());
    	}
        catch (ParseException ex) {
            // treat parse errors as expired license
            ok = false;
    	}

        if (!ok) {
            System.err.println(MSG_EXP);
            System.err.println(MSG_CON);
        }
        else {
            System.err.println(MSG_TTL +
               (new SimpleDateFormat("dd MMMM yyyy")).format(
                bombDate, new StringBuffer(), new FieldPosition(0)));
        }
        return ok;
    }

}

// End of License

