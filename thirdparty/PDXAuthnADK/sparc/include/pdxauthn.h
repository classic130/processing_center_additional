/*
 * FILENAME
 *      pdxauthn.h
 *
 * DESCRIPTION
 *      Used in cross domain authentication module (CDAS), where client
 * 	identity is generated base on the external authentication
 *	mechanism. PD converts this into PD's identity.
 *
 * COPYRIGHT NOTICE
 *      Copyright (c) 2001 Tivoli Systems.  All Rights Reserved.
 *
 */

#ifndef PDXAUTHN_H
#define PDXAUTHN_H

#if defined(__cplusplus)
extern "C" {
#endif

#include "xattr.h"
#include "xnvlist.h"

#ifndef PDXAUTHNREF
extern void* __pdxauthn_referee;
static void** __pdxauthn_reference = &__pdxauthn_referee;
#endif

/*
 * Defined Constants
 */
#define XAUTHN_PRIN_TYPE_NAME 0
#define XAUTHN_PRIN_TYPE_DN   1

#define XAUTHN_TAG_VALUE_KEY_PREFIX "tagvalue_"

/*
 * Possible identifier in the user authentication
 * name/value data list.
 */
#define XAUTHN_USERNAME       "xauthn_username"
#define XAUTHN_PASSWORD       "xauthn_password"
#define XAUTHN_NEW_PASSWORD   "xauthn_new_password"
#define XAUTHN_IPADDR         "xauthn_ipaddr"
#define XAUTHN_QOP            "xauthn_qop"
#define XAUTHN_BROWSER_INFO   "xauthn_browser_info"
#define XAUTHN_CERT           "xauthn_cert"
#define XAUTHN_CERT_DN        "xauthn_cert_dn"
#define XAUTHN_CERT_ISSUER_DN "xauthn_cert_issuer_dn"
#define XAUTHN_TOKEN          "xauthn_token"


typedef unsigned long unsigned32;
typedef unsigned long xauthn_status_t;
typedef unsigned long xauthn_boolean_t;


typedef struct {
    struct {
        unsigned32 prin_type;
        union {
            /* case(s): 0 */
            char *name;
            /* case(s): 1 */
            char *dn;
            /* case(s): 2 */
            char *uraf_name;
        } data;
    } prin;
    char         *user_info;
    char         *authnmech_info;
    xattr_list_t xattrs;
} xauthn_identity_t;


/*
 * External interfaces that custom implementation is required.
 */
xauthn_status_t xauthn_initialize(int argc, const char **argv);
xauthn_status_t xauthn_authenticate(xnvlist_t *xauthnInfo, xauthn_identity_t *xauthnIdent);
xauthn_status_t xauthn_change_password(xnvlist_t *xauthnInfo);
xauthn_status_t xauthn_shutdown(int argc, const char **argv);



/*
 * Error status code
 */
#define XAUTHN_S_COMPLETE                     0x0000
#define XAUTHN_S_FAILURE                      0x0001
#define XAUTHN_S_INTERNAL_ERROR               0x13212064
#define XAUTHN_S_UNKNOWN_ERROR                0x13212065
#define XAUTHN_S_MECHANISM_ERROR              0x1321206e
#define XAUTHN_S_OUT_OF_MEMORY                0x1321206f
#define XAUTHN_S_OPERATION_ABORTED            0x13212070
#define XAUTHN_S_UNKNOWN_IDENTITY_TYPE        0x13212073
#define XAUTHN_S_CANT_LOAD_XATTRS             0x13212074
#define XAUTHN_S_CANT_SELECT_MECHANISM        0x13212075
#define XAUTHN_S_UNSUPPORTED_AUTHN_METHOD     0x13212076
#define XAUTHN_S_MECHANISM_DOWN               0x13212077
#define XAUTHN_S_INVALID_OPERATION            0x13212079
#define XAUTHN_S_AUTHENTICATION_FAILURE       0x132120c8
#define XAUTHN_S_BAD_AUTHENTICATION_INFO      0x132120c9
#define XAUTHN_S_INVALID_USERNAME             0x132120ca
#define XAUTHN_S_RETRY_LIMIT_REACHED          0x132120cb
#define XAUTHN_S_PASSWORD_EXPIRED             0x132120cc 
#define XAUTHN_S_ACCOUNT_EXPIRED              0x132120cd
#define XAUTHN_S_LOGIN_POLICY_VIOLATION       0x132120ce
#define XAUTHN_S_NEW_PIN                      0x132120cf
#define XAUTHN_S_ACCOUNT_DISABLED             0x132120d0
#define XAUTHN_S_NEXT_TOKEN                   0x132120d1
#define XAUTHN_S_MAPPING_FAILED               0x132120d2
#define XAUTHN_S_CERTIFICATE_AUTH_FAILURE     0x132120d3
#define XAUTHN_S_HTTP_HEADER_AUTH_FAILURE     0x132120d4
#define XAUTHN_S_IP_ADDR_AUTH_FAILED          0x132120d6
#define XAUTHN_S_PASSWD_POLICY_VIOLATION      0x1321212c
#define XAUTHN_S_PASSWD_TOO_SHORT             0x1321212d
#define XAUTHN_S_PASSWD_HAS_SPACES            0x1321212e
#define XAUTHN_S_PASSWD_TOO_MANY_REPEATED     0x1321212f
#define XAUTHN_S_PASSWD_TOO_FEW_ALPHAS        0x13212130
#define XAUTHN_S_PASSWD_TOO_FEW_NONALPHAS     0x13212131
#define XAUTHN_S_PASSWD_ACCT_LOCKEDOUT        0x13212132

#if defined(__cplusplus)
}
#endif

#endif /* end PDXAUTHN_H */
