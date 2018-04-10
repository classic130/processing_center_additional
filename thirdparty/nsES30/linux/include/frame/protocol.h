/*
    PROPRIETARY/CONFIDENTIAL.  Use of this product is subject to license terms.
    Copyright  1999 Sun Microsystems, Inc. Some preexisting portions Copyright
    1999 Netscape Communications Corp. All rights reserved.
*/

/*
 * protocol.h: Switch which protocol we're speaking. 
 * 
 * Currently only HTTP, but expected to include MTP in the future.
 * 
 * Rob McCool
 */


#if defined(MCC_HTTPD) || defined(MCC_PROXY) || defined(MCC_BATMAN) || defined(MCC_NEWS)
#include "http.h"
#endif
