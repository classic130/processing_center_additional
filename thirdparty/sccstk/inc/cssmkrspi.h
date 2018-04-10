/* SCCSID: inc/cssmkrspi.h, dss_cdsa_fwk, fwk_rel3, dss_980811 1.8 8/12/98 19:10:20 */
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

#ifndef _CSSMKRSPI_H
#define _CSSMKRSPI_H    

#include "cssmtype.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef CSSM_RETURN (*CSSM_PRIV_FUNC_PTR)(CSSM_CC_HANDLE hContext, CSSM_BOOL Priv);

#ifdef KEY_RECOVERY

typedef struct cssm_spi_krsp_funcs {
	CSSM_RETURN (CSSMAPI *RegistrationRequest) (
			CSSM_KRSP_HANDLE KRSPHandle,
			CSSM_CC_HANDLE KRRegistrationContextHandle,
			const CSSM_CONTEXT_PTR KRRegistrationContext,
			CSSM_DATA_PTR KRInData,
			CSSM_CRYPTO_DATA_PTR UserCallback,
			uint32 *EstimatedTime,
			CSSM_HANDLE_PTR ReferenceHandle);
	CSSM_RETURN (CSSMAPI *RegistrationRetrieve) (
			CSSM_KRSP_HANDLE KRSPHandle,
			CSSM_HANDLE ReferenceHandle,
			uint32 *EstimatedTime,
			CSSM_KR_PROFILE_PTR KRProfile);
	CSSM_RETURN (CSSMAPI *RecoveryRequest) (
			CSSM_KRSP_HANDLE KRSPHandle,
			CSSM_CC_HANDLE KRRequestContextHandle,
			const CSSM_CONTEXT_PTR KRRequestContext,
			CSSM_DATA_PTR KRInData,
			CSSM_CRYPTO_DATA_PTR UserCallback,
			uint32 *EstimatedTime,
			CSSM_HANDLE_PTR ReferenceHandle);
	CSSM_RETURN (CSSMAPI *RecoveryRetrieve) (
			CSSM_KRSP_HANDLE KRSPHandle,
			CSSM_HANDLE_PTR ReferenceHandle,
			uint32 *EstimatedTime,
			uint32 *NumberOfResults);
	CSSM_RETURN (CSSMAPI *GetRecoveredObject) (
			CSSM_KRSP_HANDLE KRSPHandle,
			CSSM_HANDLE_PTR ResultsHandle,
			uint32 IndexInResults,
			const CSSM_CRYPTO_DATA_PTR PassPhrase,
			CSSM_KEY_PTR RecoveredKey,
			uint32 Flags,
			CSSM_DATA_PTR OtherInfo);
	CSSM_RETURN (CSSMAPI *RecoveryRequestAbort) (
			CSSM_KRSP_HANDLE KRSPHandle,
			CSSM_HANDLE ResultsHandle);
	CSSM_RETURN (CSSMAPI *GenerateKRFields) (
			CSSM_KRSP_HANDLE KRSPHandle,
			CSSM_KRC_HANDLE KRContextHandle,
			const CSSM_CONTEXT_PTR KRContext,
			CSSM_CC_HANDLE CryptoContextHandle,
			const CSSM_CONTEXT_PTR CryptoContext,
			CSSM_DATA_PTR KRAlgAttributes,
			uint32 KRFlags,
			CSSM_DATA_PTR KRFields);
	CSSM_RETURN (CSSMAPI *ProcessKRFields) (
			CSSM_KRSP_HANDLE KRSPHandle,
			CSSM_KRC_HANDLE KRContextHandle,
			const CSSM_CONTEXT_PTR KRContext,
			CSSM_CC_HANDLE CryptoContextHandle,
			const CSSM_CONTEXT_PTR CryptoContext,
			CSSM_DATA_PTR KRAlgAttributes,
			uint32 KRFlags,
			CSSM_DATA_PTR KRFields); 
} CSSM_SPI_KRSP_FUNCS, *CSSM_SPI_KRSP_FUNCS_PTR;

#endif //KEY_RECOVERY

#ifdef __cplusplus
}
#endif

#endif
