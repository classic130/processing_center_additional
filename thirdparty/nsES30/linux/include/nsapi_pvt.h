/*
    PROPRIETARY/CONFIDENTIAL.  Use of this product is subject to license terms.
    Copyright  1999 Sun Microsystems, Inc. Some preexisting portions Copyright
    1999 Netscape Communications Corp. All rights reserved.
*/

#ifndef PUBLIC_NSAPI_PVT_H
#define PUBLIC_NSAPI_PVT_H

/*
 * IMPORTANT NOTE:
 *
 * The definitions in this file represent aspects of the NSAPI interface
 * that are in the process of being phased out of the supported API.
 * They are divided into two categories.  Definitions in the first part
 * of this file are intended to be binary compatible with the previous
 * release, but will not necessarily be binary compatible with the next
 * release.  Definitions in the latter part of this file are subject to
 * change without notice.  The structure definitions are provided to
 * assist with debugging, but direct access to members of these structures
 * is not supported.
 *
 * These changes are being made both to simplify the interface and to
 * enable implementation improvements to be made with less risk of
 * breaking existing plugins.
 */

#ifndef PUBLIC_NSAPI_H
#include "nsapi.h"
#endif /* PUBLIC_NSAPI_H */

/**************************************************************************
 * THE FOLLOWING STRUCTURES SHOULD BE BINARY COMPATIBLE WITH THE PREVIOUS *
 * RELEASE, BUT DIRECT ACCESS TO MEMBERS OF THESE STRUCTURES IS STRONGLY  *
 * DISCOURAGED.  IN THE NEXT RELEASE THESE STRUCTURES MAY NOT BE BINARY   *
 * COMPATIBLE WITH THIS RELEASE.                                          *
 **************************************************************************/

/*
 * Hierarchy of httpd_object
 *
 * An object contains dtables. 
 * 
 * Each dtable is a table of directives that were entered of a certain type.
 * There is one dtable for each unique type of directive.
 *
 * Each dtable contains an array of directives, each of which is equivalent
 * to one directive that occurred in a config. file.
 *
 * It is up to the caller to determine how many dtables will be allocated
 * and to keep track of which of their directive types maps to which dtable
 * number.
 */


/*
 * The httpd_object structure.
 *
 * The name pblock array contains the names for this object, such as its
 * virtual location, its physical location, or its identifier.
 *
 * Use the object_get_xxx functions to access this structure, if possible.
 */

struct httpd_object {
    pblock *name;

    int nd;
    dtable *dt;
};

/*
 * httpd_objset is a container for a bunch of objects. obj is a 
 * NULL-terminated array of objects. pos points to the entry after the last
 * one in the array. You should not mess with pos, but can read it to find
 * the last entry.
 *
 * The initfns array is a NULL-terminated array of the Init functions 
 * associated with this object set. If there are no Init functions associated
 * with this object set, initfns can be NULL. Each pblock specifies the
 * parameters which are passed to the function when it's executed.
 *
 * Use the objset_get_xxxxx functions to access this object if possible.
 */

struct httpd_objset {
    int pos;
    httpd_object **obj;

    pblock **initfns;
};

/**************************************************************************
 * THE FOLLOWING STRUCTURES ARE SUBJECT TO CHANGE WITHOUT NOTICE.  THEIR  *
 * DEFINITIONS ARE PROVIDED SOLELY TO ASSIST IN DEBUGGING.  THEY ARE NOT  *
 * NECESSARILY BINARY COMPATIBLE WITH THE DEFINITIONS IN THE PREVIOUS     *
 * RELEASE, AND FUTURE RELEASES WILL NOT NECESSARILY HAVE BINARY          *
 * COMPATIBILITY WITH THE DEFINITIONS IN THIS RELEASE.                    *
 **************************************************************************/

/*
 * NSAPIPhase defines the indices of the dt array in an httpd_object.
 * Each dtable corresponds to a particular phase of NSAPI processing.
 */
enum NSAPIPhase {
    NSAPIAuthTrans = 0,
    NSAPINameTrans,
    NSAPIPathCheck,
    NSAPIObjectType,
    NSAPIService,
    NSAPIError,
    NSAPIAddLog,
    NSAPIMaxPhase
};

typedef enum NSAPIPhase NSAPIPhase;

/*
 * directive is a structure containing the protection and parameters to an
 * instance of a directive within an httpd_object.
 *
 * param is the parameters, client is the protection.
 *
 * f is a pointer to the FuncStruct for the actual function identified by
 * name in the "fn" variable of the param pblock.  If a plugin changes "fn"
 * in the param pblock, it should also change the fn pointer, using
 * func_find_str() to get the FuncStruct pointer if necessary.
 *
 * Use the directive_get_xxxx functions to access this object, if
 * possible.
 */

struct directive {
    pblock *param;
    pblock *client;
    struct FuncStruct *f;
    PRInt32 bucket;   /* perf stats bucket index (0 catches unbucketed) */
};

/*
 * dtable is a structure for creating tables of directives
 *
 * Use the directive_table_get_xxxx functions to access this object, if
 * possible.
 */

struct dtable {
    int ni;
    directive *inst;
};

enum NSHttpHeader {
    NSHttpHeader_Unrecognized = 0,
    NSHttpHeader_Accept = 1,
    NSHttpHeader_Accept_Charset,
    NSHttpHeader_Accept_Encoding,
    NSHttpHeader_Accept_Language,
    NSHttpHeader_Accept_Ranges,
    NSHttpHeader_Age,
    NSHttpHeader_Allow,
    NSHttpHeader_Authorization,
    NSHttpHeader_Cache_Control,
    NSHttpHeader_Connection,
    NSHttpHeader_Content_Encoding,
    NSHttpHeader_Content_Language,
    NSHttpHeader_Content_Length,
    NSHttpHeader_Content_Location,
    NSHttpHeader_Content_MD5,
    NSHttpHeader_Content_Range,
    NSHttpHeader_Content_Type,
    NSHttpHeader_Cookie,
    NSHttpHeader_Date,
    NSHttpHeader_ETag,
    NSHttpHeader_Expect,
    NSHttpHeader_Expires,
    NSHttpHeader_From,
    NSHttpHeader_Host,
    NSHttpHeader_If_Match,
    NSHttpHeader_If_Modified_Since,
    NSHttpHeader_If_None_Match,
    NSHttpHeader_If_Range,
    NSHttpHeader_If_Unmodified_Since,
    NSHttpHeader_Last_Modified,
    NSHttpHeader_Location,
    NSHttpHeader_Max_Forwards,
    NSHttpHeader_Pragma,
    NSHttpHeader_Proxy_Authenticate,
    NSHttpHeader_Proxy_Authorization,
    NSHttpHeader_Range,
    NSHttpHeader_Referer,
    NSHttpHeader_Retry_After,
    NSHttpHeader_Server,
    NSHttpHeader_TE,
    NSHttpHeader_Trailer,
    NSHttpHeader_Transfer_Encoding,
    NSHttpHeader_Upgrade,
    NSHttpHeader_User_Agent,
    NSHttpHeader_Vary,
    NSHttpHeader_Via,
    NSHttpHeader_Warning,
    NSHttpHeader_WWW_Authenticate,
    /* Add new headers here */
    NSHttpHeaderMax
};


#endif /* PUBLIC_NSAPI_PVT_H */
