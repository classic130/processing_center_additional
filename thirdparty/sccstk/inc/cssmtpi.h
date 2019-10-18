/* SCCSID: inc/cssmtpi.h, dss_cdsa_fwk, fwk_rel3, dss_980811 1.8 8/12/98 19:10:22 */
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

#ifndef _CSSMTPI_H
#define _CSSMTPI_H    

#include "cssmtype.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct cssm_spi_tp_funcs {
/*
    CSSM_BOOL (CSSMAPI *CertVerify) (CSSM_TP_HANDLE	TPHandle, 
									 CSSM_CL_HANDLE	CLHandle, 
									 CSSM_DL_HANDLE	DLHandle, 
									 CSSM_DB_HANDLE	DBHandle,
									 CSSM_CSP_HANDLE CSPHandle,
									 CSSM_CC_HANDLE	CCHandle,
									 const CSSM_FIELD_PTR	PolicyIdentifiers,
									 uint32		NumberofPolicyIdentifires,
									 CSSM_TP_STOP_ON	VerificationAbortOn,
									 const CSSM_CERTGROUP_PTR CertToBeVerified, 
									 const CSSM_DATA_PTR AnchorCerts,
									 uint32			NumberofAnchorCerts,
									 const CSSM_FIELD_PTR VerifyScope,
									 uint32			ScopeSize,
									 CSSM_TP_ACTION	Action,
									 const CSSM_DATA_PTR	Data,
									 const CSSM_DATA_PTR	Evidence,
									 uint32			EvidenceSize);
  */
	CSSM_DATA_PTR (CSSMAPI *CertSign) (	CSSM_TP_HANDLE TPHandle,
                                    CSSM_CL_HANDLE CLHandle,
                                    CSSM_CC_HANDLE CCHandle,
                                    const CSSM_DL_DB_LIST_PTR DBList,
                                    const CSSM_DATA_PTR CertToBeSigned,
                                    const CSSM_CERTGROUP_PTR SignerCertGroup,
                                    const CSSM_FIELD_PTR SignScope,
                                    uint32 ScopeSize);
    CSSM_DATA_PTR (CSSMAPI *CertRevoke) (	CSSM_TP_HANDLE TPHandle, 
											CSSM_CL_HANDLE CLHandle, 
											CSSM_CC_HANDLE	CCHandle,
											const CSSM_DL_DB_LIST_PTR	DBList,
											const CSSM_DATA_PTR OldCrl, 
											const CSSM_CERTGROUP_PTR CertGroupTpBeRevoked, 
											const CSSM_CERTGROUP_PTR RevokerCertGroup, 
											CSSM_REVOKE_REASON Reason);
    CSSM_BOOL (CSSMAPI *CrlVerify) (CSSM_TP_HANDLE TPHandle, 
                                    CSSM_CL_HANDLE CLHandle, 
                                    CSSM_CSP_HANDLE	CSPHandle,
									const CSSM_DL_DB_LIST_PTR	DBList,
									const CSSM_DATA_PTR CrlToBeVerified,
									const CSSM_CERTGROUP_PTR SignerCertGroup, 
									const CSSM_FIELD_PTR VerifyScope,
									uint32 ScopeSize);
    CSSM_DATA_PTR (CSSMAPI *CrlSign) (	CSSM_TP_HANDLE TPHandle, 
										CSSM_CL_HANDLE CLHandle, 
										CSSM_CC_HANDLE	CCHandle,
										const CSSM_DL_DB_LIST_PTR	DBList,
										const CSSM_DATA_PTR CrlToBeSigned, 
										const CSSM_CERTGROUP_PTR SignerCertGroup, 
										const CSSM_FIELD_PTR SignScope,
										uint32 ScopeSize);
    CSSM_RETURN (CSSMAPI *ApplyCrlToDb) (	CSSM_TP_HANDLE TPHandle, 
											CSSM_CL_HANDLE CLHandle, 
											CSSM_CSP_HANDLE CSPHandle,
											const CSSM_DL_DB_LIST_PTR DBList,
											const CSSM_DATA_PTR Crl);
     CSSM_CERTGROUP_PTR (CSSMAPI *CertGroupConstruct) 
                                       (CSSM_TP_HANDLE TPHandle,
										CSSM_CL_HANDLE CLHandle,
										CSSM_CSP_HANDLE	CSPHandle,
										CSSM_CERTGROUP_PTR CertGroupFrag,
                                        CSSM_DL_DB_LIST_PTR DBList);
    CSSM_CERTGROUP_PTR (CSSMAPI *CertGroupPrune) 
                                       (CSSM_TP_HANDLE TPHandle,
										CSSM_CL_HANDLE	CLHandle,
                                        CSSM_CERTGROUP_PTR OrderedCertGroup,
                                        CSSM_DL_DB_LIST_PTR DBList);
    CSSM_BOOL (CSSMAPI *CertGroupVerify)(	CSSM_TP_HANDLE TPHandle,
											  CSSM_CL_HANDLE CLHandle,
											  CSSM_DL_DB_LIST_PTR	DBList,
											  CSSM_CSP_HANDLE CSPHandle,
											  const CSSM_FIELD_PTR  PolicyIdentifiers,
											  uint32 NumberofPolicyIdentifiers,
											  CSSM_TP_STOP_ON VerificationAbortOn,
											  const CSSM_CERTGROUP_PTR CertToBeVerified,
											  const CSSM_DATA_PTR AnchorCerts,
											  uint32 NumberofAnchorCerts,
											  const CSSM_FIELD_PTR VerifyScope,
											  uint32 ScopeSize,
											  CSSM_TP_ACTION Action,
											  const CSSM_DATA_PTR Data,
											  CSSM_DATA_PTR *Evidence,
											  uint32 *EvidenceSize);


    CSSM_DATA_PTR (CSSMAPI *PassThrough) (CSSM_TP_HANDLE TPHandle, 
                                          CSSM_CL_HANDLE CLHandle, 
                                          CSSM_DL_HANDLE DLHandle, 
                                          CSSM_DB_HANDLE DBHandle, 
                                          CSSM_CC_HANDLE CCHandle, 
                                          uint32 PassThroughId,
                                          const void *InputParams);
} CSSM_SPI_TP_FUNCS, *CSSM_SPI_TP_FUNCS_PTR;

#ifdef __cplusplus
}
#endif

#endif
