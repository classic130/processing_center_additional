/* SCCSID: inc/cssmcli.h, dss_cdsa_fwk, fwk_rel3, dss_980811 1.5 8/12/98 19:10:19 */
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

#ifndef _CSSMCLI_H
#define _CSSMCLI_H    

#include "cssmtype.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct cssm_spi_cl_funcs {
    CSSM_DATA_PTR (CSSMAPI *CertSign)  (CSSM_CL_HANDLE CLHandle, 
                                        CSSM_CC_HANDLE CCHandle, 
                                        const CSSM_DATA_PTR SubjectCert, 
                                        const CSSM_DATA_PTR SignerCert, 
                                        const CSSM_FIELD_PTR SignScope, 
                                        uint32 ScopeSize);
    CSSM_BOOL     (CSSMAPI *CertVerify)(CSSM_CL_HANDLE CLHandle, 
                                        CSSM_CC_HANDLE CCHandle, 
                                        const CSSM_DATA_PTR SubjectCert, 
                                        const CSSM_DATA_PTR SignerCert, 
                                        const CSSM_FIELD_PTR VerifyScope,
                                        uint32 ScopeSize);
    CSSM_DATA_PTR (CSSMAPI *CertCreateTemplate)
                                            (CSSM_CL_HANDLE CLHandle, 
                                             const CSSM_FIELD_PTR CertTemplate, 
                                             uint32 NumberOfFields);
    CSSM_DATA_PTR  (CSSMAPI *CertGetFirstFieldValue) 
                                       (CSSM_CL_HANDLE CLHandle, 
                                        const CSSM_DATA_PTR Cert, 
                                        const CSSM_OID_PTR CertField,
                                        CSSM_HANDLE_PTR ResultsHandle,
                                        uint32 *NumberOfMatchedFields);
    CSSM_DATA_PTR  (CSSMAPI *CertGetNextFieldValue) 
                                       (CSSM_CL_HANDLE CLHandle, 
                                        CSSM_HANDLE ResultsHandle);
    CSSM_RETURN    (CSSMAPI *CertAbortQuery) 
                                       (CSSM_CL_HANDLE CLHandle, 
                                        CSSM_HANDLE ResultsHandle);
    CSSM_KEY_PTR   (CSSMAPI *CertGetKeyInfo) 
                                       (CSSM_CL_HANDLE CLHandle, 
                                        const CSSM_DATA_PTR Cert);
    CSSM_FIELD_PTR (CSSMAPI *CertGetAllFields) 
                                       (CSSM_CL_HANDLE CLHandle,
                                        const CSSM_DATA_PTR Cert,
                                        uint32 *NumberOfFields);
    CSSM_DATA_PTR (CSSMAPI *CertImport)(CSSM_CL_HANDLE CLHandle, 
                                        CSSM_CERT_TYPE ForeignCertType, 
                                        const CSSM_DATA_PTR ForeignCert); 
    CSSM_DATA_PTR (CSSMAPI *CertExport)(CSSM_CL_HANDLE CLHandle, 
                                        CSSM_CERT_TYPE TargetCertType, 
                                        const CSSM_DATA_PTR NativeCert);
    CSSM_OID_PTR  (CSSMAPI *CertDescribeFormat) 
                                       (CSSM_CL_HANDLE CLHandle,
                                        uint32 *NumberOfFields);
    CSSM_DATA_PTR (CSSMAPI *CrlCreateTemplate) (CSSM_CL_HANDLE CLHandle, 
                                               const CSSM_FIELD_PTR CrlTemplate,
                                               uint32 NumberOfFields);
    CSSM_DATA_PTR (CSSMAPI *CrlSetFields)  (CSSM_CL_HANDLE CLHandle,
                                            const CSSM_FIELD_PTR CrlTemplate,
                                            uint32 NumberOfFields,
                                            const CSSM_DATA_PTR OldCrl);
    CSSM_DATA_PTR (CSSMAPI *CrlAddCert)(CSSM_CL_HANDLE CLHandle, 
                                        CSSM_CC_HANDLE CCHandle, 
                                        const CSSM_DATA_PTR Cert, 
                                        const CSSM_DATA_PTR RevokerCert, 
                                        CSSM_REVOKE_REASON RevokeReason, 
                                        const CSSM_DATA_PTR OldCrl);
    CSSM_DATA_PTR (CSSMAPI *CrlRemoveCert) 
                                       (CSSM_CL_HANDLE CLHandle, 
                                        const CSSM_DATA_PTR Cert, 
                                        const CSSM_DATA_PTR OldCrl);
    CSSM_DATA_PTR (CSSMAPI *CrlSign)   (CSSM_CL_HANDLE CLHandle, 
                                        CSSM_CC_HANDLE CCHandle, 
                                        const CSSM_DATA_PTR UnsignedCrl, 
                                        const CSSM_DATA_PTR SignerCert, 
                                        const CSSM_FIELD_PTR SignScope,
                                        uint32 ScopeSize);
    CSSM_BOOL     (CSSMAPI *CrlVerify) (CSSM_CL_HANDLE CLHandle, 
                                        CSSM_CC_HANDLE CCHandle, 
                                        const CSSM_DATA_PTR SubjectCrl, 
                                        const CSSM_DATA_PTR SignerCert,
                                        const CSSM_FIELD_PTR VerifyScope,
                                        uint32 ScopeSize);
    CSSM_BOOL     (CSSMAPI *IsCertInCrl)(CSSM_CL_HANDLE CLHandle, 
                                        const CSSM_DATA_PTR Cert, 
                                        const CSSM_DATA_PTR Crl);
    CSSM_DATA_PTR (CSSMAPI *CrlGetFirstFieldValue) 
                                       (CSSM_CL_HANDLE CLHandle, 
                                        const CSSM_DATA_PTR Crl,
                                        const CSSM_OID_PTR CrlField,
                                        CSSM_HANDLE_PTR ResultsHandle,
                                        uint32 *NumberOfMatchedFields);
    CSSM_DATA_PTR (CSSMAPI *CrlGetNextFieldValue) 
                                       (CSSM_CL_HANDLE CLHandle, 
                                        CSSM_HANDLE ResultsHandle);
    CSSM_RETURN   (CSSMAPI *CrlAbortQuery) 
                                       (CSSM_CL_HANDLE CLHandle, 
                                        CSSM_HANDLE ResultsHandle);
    CSSM_OID_PTR  (CSSMAPI *CrlDescribeFormat) 
                                       (CSSM_CL_HANDLE CLHandle,
                                        uint32 *NumberOfFields);
    void * (CSSMAPI *PassThrough)(CSSM_CL_HANDLE CLHandle, 
                                        CSSM_CC_HANDLE CCHandle, 
                                        uint32 PassThroughId, 
                                        const void * InputParams);
} CSSM_SPI_CL_FUNCS, *CSSM_SPI_CL_FUNCS_PTR;

#ifdef __cplusplus
}
#endif

#endif
