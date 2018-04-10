/* DISABLE check_long_lines  */

/*
 * $Header: /cvs/thirdparty/oracle/sparc/oci816/include/Attic/nzerror.h,v 1.1.2.1 2003/10/29 19:42:18 simpson Exp $
 *
 * Copyright (c) Oracle Corporation 1995, 1996, 1997, 1998, 1999.  All Rights Reserved.
 */

/* ENABLE check_long_lines  */
/*
  NAME
     nzerror.h - error numbers for the Oracle Security Server
  DESCRIPTION
     None.
  PUBLIC FUNCTION(S)
     None.
  PRIVATE FUNCTION(S)
     None.
  NOTES
     A pragma is used to silence olint about the enum value names not being
     unique within 7 characters. This limit is being changed to 30.
  MODIFIED
     rwessman   07/07/99 - Deleted include of sslerrs.h. It caused the RDBMS bu
     rwessman   07/02/99 - fixed merge errors
     rwessman   07/01/99 - moved NZOS errors to nzerror to make them visible
     supriya    12/16/98 - add new error for cert chain.
     arswamin   12/04/98 - add NZERROR_NO_MATCHING_PRIVATE_KEY
     qdinh      11/12/98 - add NZERROR_VALIDITY_EXPIRED.
     arswamin   06/17/98 - add INIT_FAILED
     sdange     06/10/98 - change wrong password to bad password
     amthakur   06/09/98 - adding error messages
     wliau      03/10/97 - Add new error message for snzdfo.c.
     rwessman   03/14/97 - Consolidated PL/SQL toolkit errors into generic erro
     rwessman   02/26/97 - Added NZERROR_UNSUPPORTED. Corrected values of
                           errors outside the valid range.
     asriniva   03/02/97 - Fix olint warning
     rwessman   02/26/97 - Added NZERROR_UNSUPPORTED
     rwessman   01/02/97 - Changed PLSQL package errors to be TK_PLSQL to
                           separate them from the errors generated by the
                           Oracle interface.
     rwessman   12/30/96 - Merged in PL/SQL toolkit errors
     sdange     11/14/96 - (Added NZERROR_DECRYPT_FAILED to the enum list)
     rwessman   12/02/96 -
     rwessman   11/25/96 - Added error messages for PL/SQL functions.
     asriniva   10/31/96 - Include oratypes.h
     asriniva   10/29/96 - Fix numbering.
     asriniva   10/29/96 - Fix error numbers
     asriniva   10/29/96 - Correct type-o
     asriniva   10/28/96 - Add more TK errors
     asriniva   10/28/96 - Convert OKAPI errors to TK errors.
     rwessman   10/17/96 - still more OSS TK errors
     asriniva   10/16/96 - OKAPI errors
     asriniva   10/15/96 - OSSTK errors
     rwessman   10/15/96 - Added more OSS TK errors
     asriniva   10/09/96 - Add OSSTK errors.
     rwessman   09/05/96 - Added errors for PL/SQL functions.
     wliau      09/05/96 - correct error numbers.
     $Log: nzerror.h,v $
     Revision 1.1.2.1  2003/10/29 19:42:18  simpson
     - Oracle 8 header file

 * Revision 1.26  1996/07/15  23:07:23  wliau
 * Added NZERROR_AUTH_SHARED_MEMORY
 *
 * Revision 1.25  1996/07/01  20:40:15  asriniva
 * Finished RSA verify/sign.
 *
 * Revision 1.24  1996/06/27  20:39:41  rwessman
 * Added more errors.
 *
 * Revision 1.23  1996/05/31  17:33:40  rwessman
 * Updated nzerror.h to contain bug # for olint enum bug.
 *
 * Revision 1.22  1996/05/31  17:12:30  rwessman
 * Assigned values to the various errors.
 *
 * Revision 1.21  1996/05/13  20:46:58  ggilchri
 * Added more attribute related error conditions
 *
*/

#ifndef NZERROR_ORACLE
# define NZERROR_ORACLE

#ifndef ORATYPES
# include <oratypes.h>
#endif /* ORATYPES */

/*
** Errors - when an error is added here, a message corresponding to the
** error number must be added to the message file.
** New errors must be assigned numbers, otherwise the compiler can assign any
** value that it wants, which may lead to invalid error numbers being
** generated.
** The number range currently assigned to the OSS is 28750 - 29249
*/

typedef enum nzerror
{
  NZERROR_OK = 0,
  NZERROR_GENERIC = 28750,                          /* A catchall for errors */
  NZERROR_NO_MEMORY = 28751,                               /* No more memory */
  NZERROR_DATA_SOURCE_INIT_FAILED = 28752,     /* Failed to init data source */
  NZERROR_DATA_SOURCE_TERM_FAILED = 28753,/* Failed to terminate data source */
  NZERROR_OBJECT_STORE_FAILED = 28754, /* Store object in data source failed */
  NZERROR_OBJECT_GET_FAILED = 28755,
                                 /* Failed to obtain object from data source */
  NZERROR_MEMORY_ALLOC_FAILED = 28756,
                                       /* Callback failed to allocate memory */
  NZERROR_MEMORY_ALLOC_0_BYTES = 28757,
                                   /* Attempted to ask for 0 bytes of memory */
  NZERROR_MEMORY_FREE_FAILED = 28758,
                                           /* Callback failed to free memory */
  NZERROR_FILE_OPEN_FAILED = 28759,
                                                      /* Open of file failed */
  NZERROR_LIST_CREATION_FAILED = 28760,
                                                  /* Creation of list failed */
  NZERROR_NO_ELEMENT = 28761,
                                                    /* No list element found */
  NZERROR_ELEMENT_ADD_FAILED = 28762,
                                          /* Addition of list element failed */
  NZERROR_PARAMETER_BAD_TYPE = 28763,
                                   /* Retrieval of an unknown parameter type */
  NZERROR_PARAMETER_RETRIEVAL = 28764,      /* Retrieval of parameter failed */
                             
  NZERROR_NO_LIST = 28765,                /* Data method list does not exist */
  NZERROR_TERMINATE_FAIL = 28766,                     /* Failed to terminate */
  NZERROR_BAD_VERSION_NUMBER = 28767,                  /* Bad version number */
  NZERROR_BAD_MAGIC_NUMBER = 28768,                      /* Bad magic number */
  NZERROR_METHOD_NOT_FOUND = 28769,
                           /* Data retrieval method specified does not exist */
  NZERROR_ALREADY_INITIALIZED = 28770,
                                    /*The data source is already initialized */
  NZERROR_NOT_INITIALIZED = 28771,     /* The data source is not initialized */
  NZERROR_BAD_FILE_ID = 28772,                             /* File ID is bad */
  NZERROR_WRITE_MAGIC_VERSION = 28773,  /* Failed to write magic and version */
  NZERROR_FILE_WRITE_FAILED = 28774,              /* Failed to write to file */
  NZERROR_FILE_CLOSE_FAILED = 28775,                 /* Failed to close file */
  NZERROR_OUTPUT_BUFFER_TOO_SMALL = 28776,
                           /* The buffer supplied by the caller is too small */
  NZERROR_BINDING_CREATION_FAILED = 28777,/* NL failed in creating a binding */
  NZERROR_PARAMETER_MALFORMED = 28778,    /* A parameter was in a bad format */
  NZERROR_PARAMETER_NO_METHOD = 28779,
                                  /* No method was specified for a data type */
  NZERROR_BAD_PARAMETER_METHOD = 28780,      /* Illegal method for data type */
  NZERROR_PARAMETER_NO_DATA = 28781,    /* No method specified when required */
  NZERROR_NOT_ALLOCATED = 28782,             /* Data source is not allocated */
  NZERROR_INVALID_PARAMETER = 28783,               /* Invalid parameter name */
  NZERROR_FILE_NAME_TRANSLATION = 28784,/* Could not translate OSD file name */
  NZERROR_NO_SUCH_PARAMETER = 28785,   /* Selected parameter is non-existent */

  NZERROR_DECRYPT_FAILED = 28786,     /* Encrypted private key decryption failure */ 
  NZERROR_ENCRYPT_FAILED = 28787,     /* Private key encryption failed */
 
  NZERROR_INVALID_INPUT = 28788,     /* Incorrect input or unknown error */ 

  NZERROR_NAME_TYPE_NOT_FOUND = 28789,
                                  /* Type of name requested is not available */
  NZERROR_NLS_STRING_OPEN_FAILED = 28790,
                                        /* Failure to generate an NLS string */
  NZERROR_CERTIFICATE_VERIFY = 28791,      /* Failed to verify a certificate */
  NZERROR_OCI_PLSQL_FAILED = 28792,
                                 /* an OCI call to process some plsql failed */
  NZERROR_OCI_BIND_FAILED = 28793,
                              /* an OCI call to bind an internal var. failed */
  NZERROR_ATTRIBUTE_INIT = 28794,           /* failed to init role retrieval */
  NZERROR_ATTRIBUTE_FINISH_FAILED = 28795,/* Did not complete role retrieval */
  NZERROR_UNSUPPORTED_METHOD = 28796, /* Data method specified not supported */
  NZERROR_INVALID_KEY_DATA_TYPE = 28797,
                                      /* Invalid data type specified for key */
  NZEROR_BIND_SUBKEY_COUNT = 28798,
       /* Number of sub-keys to bind does not match count in initialized key */
  NZERROR_AUTH_SHARED_MEMORY = 28799,
    /* Failed to retreieve authentication information from the shared memory */
  NZERROR_RIO_OPEN = 28800,                               /* RIO Open Failed */
  NZERROR_RIO_OBJECT_TYPE = 28801,                /* RIO object type invalid */
  NZERROR_RIO_MODE = 28802,                              /* RIO mode invalid */
  NZERROR_RIO_IO = 28803,                     /* RIO io set or numberinvalid */
  NZERROR_RIO_CLOSE = 28804,                             /* RIO close failed */
  NZERROR_RIO_RETRIEVE = 28805,                       /* RIO retrieve failed */
  NZERROR_RIO_STORE = 28806,                             /* RIO store failed */
  NZERROR_RIO_UPDATE = 28807,                           /* RIO update failed */
  NZERROR_RIO_INFO = 28808,                               /* RIO info failed */
  NZERROR_RIO_DELETE = 28809,                           /* RIO delete failed */
  NZERROR_KD_CREATE = 28810,                 /* Key descriptor create failed */
  NZERROR_RIO_ACCESS_DESCRIPTOR = 28811,        /* access descriptor invalid */
  NZERROR_RIO_RECORD = 28812,                              /* record invalid */
  NZERROR_RIO_RECORD_TYPE = 28813,    /* record type and AD type not matched */
  NZERROR_PLSQL_ORACLE_TO_REAL = 28814,
          /* A number passed to PL/SQL could not be converted to real format */
  NZERROR_PLSQL_REAL_TO_ORACLE = 28815,
       /* A number in machine format could not be converted to Oracle format */
  NZERROR_TK_PLSQL_NO_PASSWORD = 28816,
                         /* A password was not provided to a PL/SQL function */
  NZERROR_TK_PLSQL_GENERIC = 28817,
                                      /* A PL/SQL function returned an error */
  NZERROR_TK_PLSQL_NO_CONTEXT = 28818,
               /* The package context was not specified to a PL/SQL function */
  NZERROR_TK_PLSQL_NO_DIST_NAME = 28819,
      /* The user's distinguished name was not provided to a PL/SQL function */
  NZERROR_TK_PLSQL_NO_STATE = 28820,
/* The state of either a signature or decryption/encryption was not provided */
  NZERROR_TK_PLSQL_NO_INPUT = 28821,
                       /* An input buffer was specified to a PL/SQL function */
  NZERROR_TK_PLSQL_NO_SEED = 28822,
         /* No seed was specified to the PL/SQL seed initialization function */
  NZERROR_TK_PLSQL_NO_BYTES = 28823,
  /* Number of bytes was not specified to the PL/SQL random number generator */
  NZERROR_TK_INVALID_STATE = 28824,
                     /* Invalid encryption/decryption/signature state passed */
  NZERROR_TK_PLSQL_NO_ENG_FUNC = 28825,
                                  /* No crypto engine function was passed in */
  NZERROR_TK_INV_ENG_FUNC = 28826,
                          /* An invalid crypto engine function was passed in */
  NZERROR_TK_INV_CIPHR_TYPE = 28827,
                                     /* An invalid cipher type was passed in */
  NZERROR_TK_INV_IDENT_TYPE = 28828,
                                   /* An invalid identity type was specified */
  NZERROR_TK_PLSQL_NO_CIPHER_TYPE = 28829,
                                             /* No cipher type was specified */
  NZERROR_TK_PLSQL_NO_IDENT_TYPE = 28830,
                                           /* No identity type was specified */
  NZERROR_TK_PLSQL_NO_DATA_FMT = 28831,
                                        /* No data unit format was specified */
  NZERROR_TK_INV_DATA_FMT = 28832,
                        /* Invalid data unit format was provided to function */
  NZERROR_TK_PLSQL_INSUFF_INFO = 28833,
       /* Not enough info (usually parameters) provided to a PL/SQL function */
  NZERROR_TK_PLSQL_BUF_TOO_SMALL = 28834,
           /* Buffer provided by PL/SQL is too small for data to be returned */
  NZERROR_TK_PLSQL_INV_IDENT_DESC = 28835,
                             /* Identity descriptor not present or too small */
  NZERROR_TK_PLSQL_WALLET_NOTOPEN = 28836,
                                           /* Wallet has not been opened yet */
  NZERROR_TK_PLSQL_NO_WALLET = 28837,
                        /* No wallet descriptor specified to PL/SQL function */
  NZERROR_TK_PLSQL_NO_IDENTITY = 28838,
                      /* No identity descriptor specified to PL/SQL function */
  NZERROR_TK_PLSQL_NO_PERSONA = 28839,
                   /* No persona descriptor was specified to PL/SQL function */
  NZERROR_TK_PLSQL_WALLET_OPEN = 28840,
                                                /* Wallet was already opened */
  NZERROR_UNSUPPORTED = 28841,                 /* Operation is not supported */
  NZERROR_FILE_BAD_PERMISSION = 28842,      /* Bad file permission specified */
  NZERROR_FILE_OSD_ERROR = 28843,             /* OSD error when opening file */
  NZERROR_NO_WALLET  = 28844,  /* cert + privkey + tp files do not exist */
  NZERROR_NO_CERTIFICATE_ALERT    = 28845,  /* no certificate */
  NZERROR_NO_PRIVATE_KEY          = 28846,  /* no private-key */
  NZERROR_NO_CLEAR_PRIVATE_KEY_FILE   = 28847,   /* no clear key-file */
  NZERROR_NO_ENCRYPTED_PRIVATE_KEY_FILE = 28848,  /* no encrypted priv key */
  NZERROR_NO_TRUSTPOINTS     = 28849,       /* no trustpoints */
  NZERROR_NO_CLEAR_TRUSTPOINT_FILE    = 28850,   /* no clear trustpoints */
  NZERROR_NO_ENCRYPTED_TRUSTPOINT_FILE = 28851,   /* no encrypted trustpoints */
  NZERROR_BAD_PASSWORD    = 28852,   /* bad password */
  NZERROR_INITIALIZATION_FAILED   =  28853, /* init failed or 
					       module loading failed */
  /******************************* SSL ERRORS ********************************/
  /*
   * In order to allow SSL errors to be mapped to Oracle errors, space is
   * provided here. One Oracle error is provided for each SSL error to make
   * error handling easier. A macro is provided to do the conversion.
   * NOTE: ANY CHANGE IN SSL ERRORS MUST BE REFLECTED HERE.
   * To add an SSL error, use the following formula to calculate the Oracle
   * error:
   * new_oracle_error = (new_ssl_error - SSLMemoryError) + NZERROR_SSLMemoryErr
   * or numerically:
   * new_oracle_error = (new_ssl_error - -7000) + 28854
   */
  NZERROR_SSLMemoryErr = 28854,
  NZERROR_SSLUnsupportedErr = 28855,
  NZERROR_SSLOverflowErr = 28856,
  NZERROR_SSLUnknownErr = 28857,
  NZERROR_SSLProtocolErr = 28858,
  NZERROR_SSLNegotiationErr = 28859,
  NZERROR_SSLFatalAlert = 28860,
  NZERROR_SSLWouldBlockErr = 28861,
  NZERROR_SSLIOErr = 28862,
  NZERROR_SSLSessionNotFoundErr = 28863,
  NZERROR_SSLConnectionClosedGraceful = 28864,
  NZERROR_SSLConnectionClosedError = 28865,
  NZERROR_ASNBadEncodingErr = 28866,
  NZERROR_ASNIntegerTooBigErr = 28867,
  NZERROR_X509CertChainInvalidErr = 28868,
  NZERROR_X509CertExpiredErr = 28869,
  NZERROR_X509NamesNotEqualErr = 28870,
  NZERROR_X509CertChainIncompleteErr = 28871,
  NZERROR_X509DataNotFoundErr = 28872,
  NZERROR_SSLBadParameterErr = 28873,
  NZERROR_SSLIOClosedOverrideGoodbyeKiss = 28874,
  NZERROR_X509MozillaSGCErr  =  28875,
  NZERROR_X509IESGCErr       =  28876,
  NZERROR_ImproperServerCredentials = 28877,
  NZERROR_ImproperClientCredentials = 28878,
  NZERROR_NoProtocolSideSet = 28879,
  NZERROR_setPersonaFailed = 28880,
  NZERROR_setCertFailed = 28881,
  NZERROR_setVKeyFailed = 28882,
  NZERROR_setTPFailed = 28883,
  NZERROR_BadCipherSuite = 28884,


/* ============>>>  ADD ERRORS HERE -- NOTE DECREASING numbers */
  NZERROR_DN_MATCH  =            29222,  /* for nztCompareDN */
  NZERROR_CERT_CHAIN_CREATION  = 29223,  /* unable to create a cert chain
					  * with the existing TPs for the 
					  * cert to be installed. 
					  */
  NZERROR_NO_MATCHING_CERT_REQ = 29224,  /* No matching cert_req was 
					  * found the corresponding to
					  * the privatekey which
					  * matches the cert to be
					  * installed */
  NZERROR_CERT_ALREADY_INSTALLED = 29225, /* we are attempting to
					   * install a cert again into
					   * a persona which already 
					   * has it installed.
					   */
  NZERROR_NO_MATCHING_PRIVATE_KEY = 29226, /* could not find a matching 
					    * persona-private(privatekey) in
					    * the Persona, for the given
					    * cert(public key). 
					    */
  NZERROR_VALIDITY_EXPIRED = 29227, /* certificate validity date expired */
  NZERROR_TK_BYTES_NEEDED = 29228,   /* Couldn't determine # of bytes needed */
  NZERROR_TK_BAD_MAGIC_NUMBER = 29229,
                     /* Magic number found in header does not match expected */
  NZERROR_TK_BAD_HEADER_LENGTH = 29230,
                /* Header length passed in not sufficient for message header */
  NZERROR_TK_CE_INIT = 29231,          /* Crypto engine failed to initialize */
  NZERROR_TK_CE_KEYINIT = 29232,  /* Crypto engine key initialization failed */
  NZERROR_TK_CE_ENCODE_KEY = 29233,           /* Count not encode key object */
  NZERROR_TK_CE_DECODE_KEY = 29234,      /* Could not decode key into object */
  NZERROR_TK_CE_GEYKEYINFO = 29235,  /* Crypto engine failed to get key info */
  NZERROR_TK_SEED_RANDOM = 29236,   /* Couldn't seed random number generator */
  NZERROR_TK_CE_ALGFINISH = 29237,              /* Couldn't finish algorithm */
  NZERROR_TK_CE_ALGAPPLY = 29238,        /* Couldn't apply algorithm to data */
  NZERROR_TK_CE_ALGINIT = 29239,           /* Couldn't init CE for algorithm */
  NZERROR_TK_ALGORITHM = 29240,      /* Have no idea what algorithm you want */
  NZERROR_TK_CANNOT_GROW = 29241,         /* Cannot grow output buffer block */
  NZERROR_TK_KEYSIZE = 29242,               /* Key not large enough for data */
  NZERROR_TK_KEYTYPE = 29243,                           /* Unknown key type. */

  NZERROR_TK_PLSQL_NO_WRL = 29244,
                 /* Wallet resource locator not specified to PL/SQL function */

  NZERROR_TK_CE_FUNC = 29245,              /* Unknown crypto engine function */
  NZERROR_TK_TDU_FORMAT = 29246,                       /* Unknown TDU format */
  NZERROR_TK_NOTOPEN = 29247,                         /* Object must be open */
  NZERROR_TK_WRLTYPE = 29248,                                /* Bad WRL type */
  NZERROR_TK_CE_STATE = 29249,  /* Bad state specified for the crypto engine */

  NZERROR_LAST_ERROR = 29249,                        /* Last available error */
                                            /* MAXIMUM ERROR NUMBER IS 29249 */

  /*
   * DO NOT JUST INSERT NEW ERRORS IN ANY OLD PLACE.  New errors should be
   * added such the current error retains their integer values. Duplicate
   * values will cause compiler errors.
   */
  NZERROR_THIS_MUST_BE_LAST

} nzerror;

/*
 * Macro to convert SSL errors to Oracle errors. As SSL errors are negative
 * and Oracle numbers are positive, the following needs to be done.
 * 1. The base error number, which is the highest, is added to the
 *    SSL error to get the index into the number range.
 * 2. The result is added to the base Oracle number to get the Oracle error.
 */
#define NZERROR_SSL_TO_ORACLE(ssl_error_) \
  ((ssl_error_ == SSLNoErr) \
   ? NZERROR_OK \
   : (nzerror) ((ssl_error_ - SSLMemoryErr) + (uword) NZERROR_SSLMemoryErr))
#endif /* NZERROR_ORACLE */ 