/* SCCSID: inc/cssmdli.h, dss_cdsa_fwk, fwk_rel3, dss_980811 1.5 8/12/98 19:10:19 */
/*
 * (C) COPYRIGHT International Business Machines Corp. 1996, 1997
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * Copyright (c) 1995, 1996, 1997 Intel Corporation. All rights reserved.
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 *
 */

#ifndef _CSSMDLI_H
#define _CSSMDLI_H    

#include "cssmtype.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct cssm_spi_dl_funcs {
    CSSM_RETURN (CSSMAPI *Authenticate) (
                      CSSM_DL_DB_HANDLE DLDBHandle,
                      const CSSM_DB_ACCESS_TYPE_PTR AccessRequest,
                      const CSSM_USER_AUTHENTICATION_PTR UserAuthentication);

    CSSM_DB_HANDLE (CSSMAPI *DbOpen) (
                       CSSM_DL_HANDLE DLHandle,
                       const char *DbName,
                       const CSSM_DB_ACCESS_TYPE_PTR AccessRequest,
                       const CSSM_USER_AUTHENTICATION_PTR UserAuthentication,
                       const void *OpenParameters);


    CSSM_RETURN (CSSMAPI *DbClose) (CSSM_DL_DB_HANDLE DLDBHandle);

    CSSM_DB_HANDLE (CSSMAPI *DbCreate) (
                      CSSM_DL_HANDLE DLHandle,
                      const char *DbName,
                      const CSSM_DBINFO_PTR DBInfo,
                      const CSSM_DB_ACCESS_TYPE_PTR AccessRequest,
                      const CSSM_USER_AUTHENTICATION_PTR UserAuthentication,
                      const void *OpenParameters);

    CSSM_RETURN (CSSMAPI *DbDelete) (
                     CSSM_DL_HANDLE DLHandle,
                     const char *DbName,
                     const CSSM_USER_AUTHENTICATION_PTR UserAuthentication);

    CSSM_RETURN (CSSMAPI *DbImport) (
                     CSSM_DL_HANDLE DLHandle,
                     const char *DbDestinationName,
                     const char *DbSourceName,
                     const CSSM_DBINFO_PTR DBInfo,
                     CSSM_BOOL InfoOnly,
                     const CSSM_USER_AUTHENTICATION_PTR UserAuthentication);

    CSSM_RETURN (CSSMAPI *DbExport) (
                     CSSM_DL_HANDLE DLHandle,
                     const char *DbDestinationName,
                     const char *DbSourceName,
                     CSSM_BOOL InfoOnly,
                     const CSSM_USER_AUTHENTICATION_PTR UserAuthentication);

    CSSM_RETURN (CSSMAPI *DbSetRecordParsingFunctions) (
                        CSSM_DL_HANDLE DLHandle,
                        const char* DbName,
                        CSSM_DB_RECORDTYPE RecordType,
                        const CSSM_DB_RECORD_PARSING_FNTABLE_PTR FunctionTable);

    CSSM_DB_RECORD_PARSING_FNTABLE_PTR (CSSMAPI *DbGetRecordParsingFunctions) (
                                            CSSM_DL_HANDLE DLHandle,
                                            const char* DbName, 
                                            CSSM_DB_RECORDTYPE RecordType);

    char * (CSSMAPI *GetDbNameFromHandle) (CSSM_DL_DB_HANDLE DLHandle);

    CSSM_DB_UNIQUE_RECORD_PTR (CSSMAPI *DataInsert) (
                           CSSM_DL_DB_HANDLE DLDBHandle,
                           const CSSM_DB_RECORDTYPE RecordType,
                           const CSSM_DB_RECORD_ATTRIBUTE_DATA_PTR Attributes, 
                           const CSSM_DATA_PTR Data);

    CSSM_RETURN (CSSMAPI *DataDelete) (
                       CSSM_DL_DB_HANDLE DLDBHandle,
                       CSSM_DB_RECORDTYPE RecordType,
                       const CSSM_DB_UNIQUE_RECORD_PTR UniqueRecordIdentifier);

    CSSM_DB_UNIQUE_RECORD_PTR (CSSMAPI *DataGetFirst) (
                       CSSM_DL_DB_HANDLE DLDBHandle,
                       const CSSM_QUERY_PTR Query,
                       CSSM_HANDLE_PTR  ResultsHandle,
                       CSSM_BOOL  *EndOfDataStore,
                       CSSM_DB_RECORD_ATTRIBUTE_DATA_PTR Attributes,
                       CSSM_DATA_PTR  Data);

    CSSM_DB_UNIQUE_RECORD_PTR (CSSMAPI *DataGetNext) (
                                  CSSM_DL_DB_HANDLE DLDBHandle,
                                  CSSM_HANDLE ResultsHandle,
                                  CSSM_BOOL *EndOfDataStore,
                                  CSSM_DB_RECORD_ATTRIBUTE_DATA_PTR Attributes, 
                                  CSSM_DATA_PTR Data);

    CSSM_RETURN (CSSMAPI *DataAbortQuery) (CSSM_DL_DB_HANDLE DLDBHandle,
                                      CSSM_HANDLE ResultsHandle);

    CSSM_RETURN (CSSMAPI *FreeUniqueRecord) (
                                       CSSM_DL_DB_HANDLE DLDBHandle,
                                       CSSM_DB_UNIQUE_RECORD_PTR UniqueRecord);

    void * (CSSMAPI *PassThrough) (CSSM_DL_DB_HANDLE DLHandle, 
                                   uint32 PassThroughId,
                                   const void * InputParams); 
}CSSM_SPI_DL_FUNCS, *CSSM_SPI_DL_FUNCS_PTR;

#ifdef __cplusplus
}
#endif

#endif
