/**************************************************************************
*
*		Microsoft Site Server v3.00
*		Copyright (C) 1997-1998 Microsoft Corporation.  All rights reserved
*
*		Microsoft Site Server 3.0 Search Status Codes
*
*		The values defined below associate a string with the 
*   	various hex HRESULT return values generated by the Site Server 3.0
*   	Search COM objects as documented in the SDK.
*
* 		Include this file if you desire to check against these values
* 		in your C/C++ code.
*
*	 	In each case below,
* 
*		The Severity bit is either "on" (0x80000000) or "off" (0x00000000)
*			indicating the code type
*       All HRESULT values have the FACILITY_ITF bits set
*			(0x7fff0000)
*		The last two bytes distinguish the area the code corresponds to and
*		the identity of the code. 
*
*		Consult the Site Server 3.0 SDK for more information.
*
****************************************************************************
*/


#ifndef _SEARCHSTATUS_H_
#define _SEARCHSTATUS_H_


#define NET_E_GENERAL 0x80040300
#define NET_E_UNEXPECTED 0x80040301
#define NET_E_RESOURCES 0x80040302
#define NET_E_DISCONNECTED 0x80040303
#define NET_E_BADSEQUENCE 0x80040304
#define NET_E_NETDOWN 0x80040305
#define NET_E_WINSOCKNOTINITIALIZED 0x80040306
#define NET_E_ADDRINUSE 0x80040307
#define NET_E_INVALIDPARAMS 0x80040308
#define NET_E_OPERATIONINPROGRESS 0x80040309
#define NET_E_HOSTNOTFOUND 0x8004030A
#define NET_E_HOSTLOOKUPFAILED 0x8004030B
#define NET_E_CONNABORTED 0x8004030C
#define NET_S_MOREDATA 0x0004030D
#define NET_E_CONNREFUSED 0x8004030E
#define NET_E_TIMEOUT 0x8004030F

#define SEC_E_INVALIDCONTEXT 0x80041403
#define SEC_E_INITFAILED 0x80041401
#define SEC_E_NOTINITIALIZED 0x80041402
#define SEC_E_ACCESSDENIED 0x800414FF

#define DS_E_NOMOREDATA 0x80040400
#define DS_E_INVALIDDATASOURCE 0x80040401
#define DS_E_DATASOURCENOTAVAILABLE 0x80040402
#define DS_E_QUERYCANCELED 0x80040403
#define DS_E_UNKNOWNREQUEST 0x80040404
#define DS_E_BADREQUEST 0x80040405
#define DS_E_SERVERCAPACITY 0x80040406
#define DS_E_BADSEQUENCE 0x80040407
#define DS_E_MESSAGETOOLONG 0x80040408
#define DS_E_SERVERERROR 0x80040409
#define DS_E_CONFIGBAD 0x8004040A
#define DS_E_CANNOTBACKUP 0x8004040B
#define DS_E_MOVEFAILED 0x8004040C
#define DS_E_DATANOTPRESENT 0x80040410
#define DS_E_SETSTATUSINPROGRESS 0x80040411
#define DS_E_DUPLICATEID 0x80040412
#define DS_E_TOOMANYDATASOURCES 0x80040413
#define DS_E_REGISTRY 0x80040414
#define DS_E_DATASOURCENOTDISABLED 0x80040415
#define DS_E_INVALIDTAGDB 0x80040416
#define DS_E_INVALIDCATALOGNAME 0x80040417
#define DS_E_CONFIGNOTRIGHTTYPE 0x80040418
#define DS_E_PROTOCOLVERSION 0x80040419
#define DS_E_ALREADYENABLED 0x8004041a
#define DS_E_DROPSHARE 0x8004041b
#define DS_E_INDEXDIRECTORY 0x8004041c
#define DS_E_VALUETOOLARGE 0x8004041d
#define DS_E_UNKNOWNPARAM 0x8004041e
#define DS_E_BUFFERTOOSMALL 0x8004041f
#define DS_E_PARAMOUTOFRANGE 0x80040420
#define DS_E_ALREADYDISABLED 0x80040421
#define DS_E_QUERYHUNG 0x80040422
#define DS_E_BADRESULT 0x80040423
#define DS_E_CANNOTWRITEREGISTRY 0x80040424

#define COLL_E_BADSEQUENCE 0x80040501
#define COLL_E_NOMOREDATA 0x80040502
#define COLL_E_INCOMPATIBLECOLUMNS 0x80040503
#define COLL_E_BUFFERTOOSMALL 0x80040504
#define COLL_E_BADRESULT 0x80040506
#define COLL_E_NOSORTCOLUMN 0x80040507
#define COLL_E_DUPLICATEDBID 0x80040508
#define COLL_E_TOOMANYMERGECOLUMNS 0x80040509
#define COLL_E_NODEFAULTCATALOG 0x8004050A

#define CM_E_TOOMANYDATASERVERS 0x80040601
#define CM_E_TOOMANYDATASOURCES 0x80040602
#define CM_E_NOQUERYCONNECTIONS 0x80040603
#define CM_E_DATASOURCENOTAVAILABLE 0x80040604
#define CM_E_CONNECTIONTIMEOUT 0x80040605
#define CM_E_SERVERNOTFOUND 0x80040606
#define CM_S_NODATASERVERS 0x00040607
#define CM_E_REGISTRY 0x80040608
#define CM_E_INVALIDDATASOURCE 0x80040609
#define CM_E_TIMEOUT 0x8004060A
#define CM_E_INSUFFICIENTBUFFER 0x8004060B

#define QRY_E_QUERYSYNTAX 0x80040701
#define QRY_E_TYPEMISMATCH 0x80040702
#define QRY_E_UNHANDLEDTYPE 0x80040703
#define QRY_E_NOROWSFOUND 0x80040704
#define QRY_E_TOOMANYCOLUMNS 0x80040705
#define QRY_E_TOOMANYDATABASES 0x80040706
#define QRY_E_STARTHITTOBIG 0x80040707
#define QRY_E_TOOMANYQUERYTERMS 0x80040708
#define QRY_E_NODATASOURCES 0x80040709
#define QRY_E_TIMEOUT 0x8004070a
#define QRY_E_COLUMNNOTSORTABLE 0x8004070b
#define QRY_E_COLUMNNOTSEARCHABLE 0x8004070c
#define QRY_E_INVALIDCOLUMN 0x8004070d
#define QRY_E_QUERYCORRUPT 0x8004070e
#define QRY_E_PREFIXWILDCARD 0x8004070f
#define QRY_E_INFIXWILDCARD 0x80040710
#define QRY_E_WILDCARDPREFIXLENGTH 0x80040711
#define QRY_S_TERMIGNORED 0x00040712
#define QRY_E_ENGINEFAILED 0x80040713
#define QRY_E_SEARCHTOOBIG 0x80040714
#define QRY_E_NULLQUERY 0x80040715
#define QRY_S_INEXACTRESULTS 0x00040716
#define QRY_E_NOCOLUMNS 0x80040717
#define QRY_E_INVALIDSCOPES 0x80040718
#define QRY_E_INVALIDCATALOG 0x80040719
#define QRY_E_SCOPECARDINALIDY 0x8004071A

#define SCHEMA_E_LOAD_SPECIAL 0x80040C01
#define SCHEMA_E_FILENOTFOUND 0x80040C02
#define SCHEMA_E_NESTEDTAG 0x80040C03
#define SCHEMA_E_UNEXPECTEDTAG 0x80040C04
#define SCHEMA_E_VERSIONMISMATCH 0x80040C05
#define SCHEMA_E_CANNOTCREATEFILE 0x80040C06
#define SCHEMA_E_CANNOTWRITEFILE 0x80040C07
#define SCHEMA_E_EMPTYFILE 0x80040C08
#define SCHEMA_E_INVALIDFILETYPE 0x80040C09
#define SCHEMA_E_INVALIDDATATYPE 0x80040C0A
#define SCHEMA_E_CANNOTCREATENOISEWORDFILE 0x80040C0B
#define SCHEMA_E_ADDSTOPWORDS 0x80040C0C
#define SCHEMA_E_NAMEEXISTS 0x80040C0D
#define SCHEMA_E_INVALIDVALUE 0x80040C0E
#define SCHEMA_E_BADPROPSPEC 0x80040C0F
#define SCHEMA_E_NOMORECOLUMNS 0x80040C10
#define SCHEMA_E_FILECHANGED 0x80040C11
#define SCHEMA_E_BADCOLUMNNAME 0x80040C12
#define SCHEMA_E_BADPROPPID 0x80040C13
#define SCHEMA_E_BADATTRIBUTE 0x80040C14
#define SCHEMA_E_BADFILENAME 0x80040C15
#define SCHEMA_E_PROPEXISTS 0x80040C16
#define SCHEMA_E_DUPLICATENOISE 0x80040C17

#define GTHR_E_INTERNAL 0x80040D01
#define GTHR_E_DUPLICATE_OBJECT 0x80040D02
#define GTHR_E_UNABLE_TO_READ_REGISTRY 0x80040D03
#define GTHR_E_ERROR_WRITING_REGISTRY 0x80040D04
#define GTHR_E_ERROR_INITIALIZING_PERFMON 0x80040D05
#define GTHR_E_ERROR_OBJECT_NOT_FOUND 0x80040D06
#define GTHR_E_URL_EXCLUDED 0x80040D07
#define GTHR_E_CONFIG_DUP_CRAWL_ENTRY 0x80040D08
#define GTHR_E_CONFIG_DUP_NNTP_SERVER 0x80040D09
#define GTHR_E_CONFIG_DUP_PROJECT 0x80040D0A
#define GTHR_E_CONFIG_DUP_EXTENSION 0x80040D0B
#define GTHR_E_CRAWL_TOO_DEEP 0x80040D0C
#define GTHR_E_DUPLICATE_URL 0x80040D0D
#define GTHR_E_TOO_MANY_PLUGINS 0x80040D0E
#define GTHR_E_INVALIDFUNCTION 0x80040D0F
#define GTHR_E_NOFILTERSINK 0x80040D10
#define GTHR_E_FILTER_PROCESS_TERMINATED 0x80040D11
#define GTHR_E_FILTER_INVALID_MESSAGE 0x80040D12
#define GTHR_E_UNSUPPORTED_PROPERTY_TYPE 0x80040D13
#define GTHR_E_NAME_TOO_LONG 0x80040D14
#define GTHR_E_NO_IDENTITY 0x80040D15
#define GTHR_E_FILTER_NOT_FOUND 0x80040D16
#define GTHR_E_FILTER_NO_MORE_THREADS 0x80040D17
#define GTHR_E_PRT_HNDLR_PROGID_MISSING 0x80040D18
#define GTHR_E_NO_LOGICAL_PATH 0x80040D19
#define GTHR_E_UNKNOWN_PROTOCOL 0x80040D1A
#define GTHR_E_PROJECT_NOT_INITIALIZED 0x80040D1B
#define GTHR_S_STATUS_CHANGE_IGNORED 0x00040D1C
#define GTHR_S_STATUS_END_CRAWL 0x00040D1D
#define GTHR_S_STATUS_RESET 0x00040D1E
#define GTHR_S_STATUS_THROTTLE 0x00040D1F
#define GTHR_S_STATUS_RESUME 0x00040D20
#define GTHR_S_STATUS_PAUSE 0x00040D21
#define GTHR_E_INVALID_PROJECT_NAME 0x80040D22
#define GTHR_E_SHUTTING_DOWN 0x80040D23
#define GTHR_S_END_STD_CHUNKS 0x00040D24
#define GTHR_E_VALUE_NOT_AVAILABLE 0x80040D25
#define GTHR_E_OUT_OF_DOC_ID 0x80040D26
#define GTHR_E_NOTIFICATION_PROJECT 0x80040D27
#define GTHR_E_CRAWL_PROJECT 0x80040D28
#define GTHR_E_CONFIG_DUP_NOTIFICATION_SOURCE 0x80040D29
#define GTHR_E_DUP_PROPERTY_MAPPING 0x80040D2A
#define GTHR_E_NO_CRAWL_SEEDS 0x80040D2B
#define GTHR_E_INVALID_ACCOUNT 0x80040D2C
#define GTHR_E_FILTER_MISMATCH 0x80040D2D
#define GTHR_E_FILTER_INIT 0x80040D2E
#define GTHR_E_FILTER_LOAD 0x80040D2F
#define GTHR_S_CANNOT_FILTER 0x00040D30
#define GTHR_E_PROXY_NAME 0x80040D31
#define GTHR_E_SERVER_UNAVAILABLE 0x80040D32
#define GTHR_S_STATUS_STOP 0x00040D33
#define GTHR_E_INVALID_PATH 0x80040D34
#define GTHR_E_FILTER_NO_CODEPAGE 0x80040D35
#define GTHR_S_STATUS_START 0x00040D36
#define GTHR_E_NO_PRTCLHNLR 0x80040D37
#define GTHR_E_IE_OFFLINE 0x80040D38
#define GTHR_E_BAD_FILTER_DAEMON 0x80040D39
#define GTHR_E_INVALID_MAPPING 0x80040D40
#define GTHR_E_USER_AGENT_NOT_SPECIFIED 0x80040D41
#define GTHR_E_NOTIFICATION_SOURCE_NOT_SPECIFIED 0x80040D42
#define GTHR_E_FROM_NOT_SPECIFIED 0x80040D43
#define GTHR_E_INVALID_STREAM_LOGS_COUNT 0x80040D44
#define GTHR_E_INVALID_EXTENSION 0x80040D45
#define GTHR_E_INVALID_GROW_FACTOR 0x80040D46
#define GTHR_E_INVALID_TIME_OUT 0x80040D47
#define GTHR_E_INVALID_RETRIES 0x80040D48
#define GTHR_E_INVALID_LOG_FILE_NAME 0x80040D49
#define GTHR_E_INVALID_HOST_NAME 0x80040D50
#define GTHR_E_INVALID_START_PAGE 0x80040D51
#define GTHR_E_DUPLICATE_PROJECT 0x80040D52
#define GTHR_E_INVALID_DIRECTORY 0x80040D53
#define GTHR_E_FILTER_INTERRUPTED 0x80040D54
#define GTHR_E_INVALID_PROXY_PORT 0x80040D55
#define GTHR_S_CONFIG_HAS_ACCOUNTS 0x00040D56
#define GTHR_E_SECRET_NOT_FOUND 0x80040D57
#define GTHR_E_INVALID_PATH_EXPRESSION 0x80040D58
#define GTHR_E_INVALID_START_PAGE_HOST 0x80040D59
#define GTHR_E_INVALID_START_PAGE_PATH 0x80040D60

#define PRTH_E_COMM_ERROR 0x80041200
#define PRTH_E_OBJ_NOT_FOUND 0x80041201
#define PRTH_E_REQUEST_ERROR 0x80041202
#define PRTH_S_NOT_MODIFIED 0x00041203
#define PRTH_E_INTERNAL_ERROR 0x80041204
#define PRTH_E_ACCESS_DENIED 0x80041205
#define PRTH_E_SERVER_ERROR 0x80041206
#define PRTH_E_NOT_REDIRECTED 0x80041207
#define PRTH_E_BAD_REQUEST 0x80041208
#define PRTH_S_MAX_GROWTH 0x00041209
#define PRTH_E_WININET 0x8004120A
#define PRTH_E_RETRY 0x8004120B
#define PRTH_E_MAX_DOWNLOAD 0x8004120C
#define PRTH_E_MIME_EXCLUDED 0x8004120D

#define IDX_E_INVALIDTAG 0x80041101
#define IDX_E_METAFILE_CORRUPT 0x80041102
#define IDX_E_TOO_MANY_SEARCH_SERVERS 0x80041103
#define IDX_E_SEARCH_SERVER_ALREADY_EXISTS 0x80041104
#define IDX_E_BUILD_IN_PROGRESS 0x80041105
#define IDX_E_IDXLSTFILE_CORRUPT 0x80041106
#define IDX_E_REGISTRY_ENTRY 0x80041107
#define IDX_E_OBJECT_NOT_FOUND 0x80041108
#define IDX_E_SEARCH_SERVER_NOT_FOUND 0x80041109
#define IDX_E_WB_NOTFOUND 0x8004110A
#define IDX_E_NOISELIST_NOTFOUND 0x8004110B
#define IDX_E_STEMMER_NOTFOUND 0x8004110C
#define IDX_E_PROP_STOPPED 0x8004110D
#define IDX_E_DISKFULL 0x8004110E
#define IDX_E_INVALID_INDEX 0x8004110F
#define IDX_E_CORRUPT_INDEX 0x80041110
#define IDX_E_NO_BACKUP 0x80041111
#define IDX_E_PROPSTORE_INIT_FAILED 0x80041112
#define IDX_E_PROP_STATE_CORRUPT 0x80041113
#define IDX_S_NO_BUILD_IN_PROGRESS 0x00041114
#define IDX_S_SEARCH_SERVER_ALREADY_EXISTS 0x00041115
#define IDX_S_SEARCH_SERVER_DOES_NOT_EXIST 0x00041116
#define IDX_E_NOT_LOADED 0x80041117
#define IDX_E_PROP_MAJOR_VERSION_MISMATCH 0x80041118
#define IDX_E_PROP_MINOR_VERSION_MISMATCH 0x80041119
#define IDX_E_DSS_NOT_CONNECTED 0x8004111A
#define IDX_E_DOCUMENT_ABORTED 0x8004111B
#define IDX_E_CATALOG_DISMOUNTED 0x8004111C
#define IDX_S_DSS_NOT_AVAILABLE 0x0004111D

#define EXCI_E_NO_CONFIG 0x800411A0
#define EXCI_E_INVALID_SERVER_CONFIG 0x800411A1
#define EXCI_E_ACCESS_DENIED 0x800411A2
#define EXCI_E_INVALID_EXCHANGE_SERVER 0x800411A3
#define EXCI_E_BADCONFIG_OR_ACCESSDENIED 0x800411A4
#define EXCI_E_WRONG_SERVER_OR_ACCT 0x800411A5
#define EXCI_E_NOT_ADMIN_OR_WRONG_SITE 0x800411A6

#define SETUP_E_EXCEPTION 0x80041301
#define SETUP_S_SERVICEUSERINFO 0x00041302

#define CMDLINE_E_UNEXPECTED 0x80041501
#define CMDLINE_E_PAREN 0x80041502
#define CMDLINE_E_PARAM_SIZE 0x80041503
#define CMDLINE_E_NOT_INIT 0x80041504
#define CMDLINE_E_ALREADY_INIT 0x80041505
#define CMDLINE_E_NUM_PARAMS 0x80041506

#define NLADMIN_E_DUPLICATE_CATALOG 0x80041901
#define NLADMIN_S_NOT_ALL_BUILD_CATALOGS_INITIALIZED 0x00041902
#define NLADMIN_E_FAILED_TO_GIVE_ACCOUNT_PRIVILEGE 0x80041903

#endif