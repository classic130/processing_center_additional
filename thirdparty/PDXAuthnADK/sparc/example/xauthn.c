/*
 * FILE: xauthn.c
 *
 * PD cross domain authentication (CDAS) demo.  This file implements
 *
 *     xauthn_initialize()
 *     xauthn_shutdown()
 *     xauthn_authenticate()
 *     xauthn_change_password()
 *
 * functions used by the PD WebSEAL to authenticate
 * users based on the specified authentication 
 * mechanism.
 *
 * To configure, modify the iv.conf file, under the 
 * [authentication-mechanisms] stanza, select the desired 
 * authentication mechanism that you want this library to
 * be used, and assign this library to it.
 *
 * For example, if you wish this library to process all the
 * HTTP SSL username/password LDAP authentication, specifies 
 * the following:
 *
 *    passwd-ldap = libxauthn.so
 *
 * or
 *
 *    passwd-ldap = libxauthn.so&<args>
 *
 * if you have any particular arguments that you want to pass
 * to this library for initialization and shutdown.
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#if !defined(WIN32) && !defined(_WIN32)
#include <strings.h>
#endif 

#include "pdxauthn.h"
#include "xattr.h"
#include "xnvlist.h"

/* Uncomment to build a DCE identity */
#define BUILD_LDAP_USER


/*
 * FUNCTION NAME
 * 	xauthn_initialize
 *
 * DESCRIPTION
 * 	init the authentication service
 *
 * ARGUMENTS
 * 	[in] argc The count of arguments to the service.
 * 	[in] argv The array of argument strings.
 *
 * RETURN VALUE
 * 	XAUTHN_S_COMPLETE on success, error code on failure
 */
xauthn_status_t
xauthn_initialize(
    int        argc,     /* in */
    const char **argv    /* in */
)
{
    return XAUTHN_S_COMPLETE;
}


/*
 * FUNCTION NAME
 * 	xauthn_shutdown
 *
 * DESCRIPTION
 * 	Shutdown the authentication service.
 * 	The initialization parameters are passed in
 * 	again.
 *
 * ARGUMENTS
 * 	[in] argc     The count of arguments to the service.
 * 	[in] argv     The array of argument strings.
 *
 * RETURN VALUE
 * 	XAUTHN_S_COMPLETE
 */
xauthn_status_t
xauthn_shutdown(
    int        argc,     /* in */
    const char **argv    /* in */
)
{
    return XAUTHN_S_COMPLETE;
}


/*
 * FUNCTION NAME
 *      xauthn_authenticate
 *
 * DESCRIPTION
 *      Examine the received user authentication information, and generate a 
 *      client identity. The received information will vary depending on the
 *      specified authentication mechanism. 
 *
 * ARGUMENTS - IN
 *      authInfo      List of names and set of values containing the user
 *                    authentication data. The pdxauthn.h contains all the
 *                    possible names that could be in this list. The actual
 *                    list of names received will depend on the specified    
 *                    authentication mechanism. 
 *
 * ARGUMENTS - OUT
 *      identity      Pointer to the resulted client identity.
 *
 *      st            Set to XAUTHN_S_COMPLETE, or to an error status indicating
 *                    the nature of the failure.
 */
xauthn_status_t 
xauthn_authenticate(
    xnvlist_t         *authnInfo,
    xauthn_identity_t *ident
)
{
    int               i;
    char              *username;
    char              **name;
    int               prin_type;
    xauthn_status_t   st;

    if ( authnInfo != NULL ) {
        printf("===============================\n");
        printf("User Authentication Information:\n");
        printf("===============================\n");

        for(i=0; i<authnInfo->length; i++) {
            if( ((authnInfo->items) + i)->name != NULL) {
                printf("%s:\t%s (%d)\n", authnInfo->items[i].name,
                                         authnInfo->items[i].value,
                                         authnInfo->items[i].vlen);
            }
        }
    }
    else {
        printf("There is NO user authenication information available.\n\n");
    }


    /*
     * We only want to get a user name if one has not already been added.
     */

    /* Undefine BUILD_LDAP_USER if you want to use DCE instead of LDAP */
#ifdef BUILD_LDAP_USER
    name = &ident->prin.data.dn;
    prin_type = XAUTHN_PRIN_TYPE_DN;
#else
    name = &ident->prin.data.name;
    prin_type = XAUTHN_PRIN_TYPE_NAME;
#endif

    if (*name == NULL) {
        username = (char *)malloc(1024);

        printf("Enter the user identity: ");
        scanf("%s", username);

        if ( strlen(username) == 0 ) {
            printf("Invalid user identity inputted. Authentication failure.\n");

            st = XAUTHN_S_INVALID_USERNAME;
            return st;
        }

        ident->prin.prin_type = prin_type;
        *name = (char*)username;
    } 
    else {
        char *tag = (char *) malloc(1024);
        char *tag_data = (char *) malloc(1024); 

        /*
         * A name is already specified so we just want to add some test tag
         * value data.
         */

        printf("using existing name: %s\n\n", *name);

        sprintf(tag, "%s", XAUTHN_TAG_VALUE_KEY_PREFIX);
        printf("Enter the test tag: ");
        fflush(stdout);
        scanf("%s", tag + strlen(XAUTHN_TAG_VALUE_KEY_PREFIX));

        printf("Enter the test tag data: ");
        fflush(stdout);
        scanf("%s", tag_data);

        xattr_set(&ident->xattrs, tag, tag_data);
    }

    return XAUTHN_S_COMPLETE;
}


xauthn_status_t 
xauthn_change_password(
    xnvlist_t         *authnInfo
)
{
    int               i;
    char              passwdChanged[2];
    xauthn_status_t   st;

    printf("====================\n");
    printf("User Password Change:\n");
    printf("====================\n");

    for(i=0; i<authnInfo->length; i++) {
        if( ((authnInfo->items) + i)->name != NULL) {
            printf("%s:\t%s (%d)\n", authnInfo->items[i].name,
                                     authnInfo->items[i].value,
                                     authnInfo->items[i].vlen);
        }
    }

    printf("Does the password change succeed [y/n]? ");
    scanf("%s", passwdChanged);

    if ( *passwdChanged != 'y' &&
         *passwdChanged != 'Y') {
        printf("User password changed failed.\n");

        st = XAUTHN_S_BAD_AUTHENTICATION_INFO;
        return st;
    }

    return XAUTHN_S_COMPLETE;
}
