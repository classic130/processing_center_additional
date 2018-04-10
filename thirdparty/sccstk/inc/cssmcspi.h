/* SCCSID: inc/cssmcspi.h, dss_cdsa_fwk, fwk_rel3, dss_980811 1.8 8/12/98 19:10:19 */
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

#ifndef _CSSMCSPI_H
#define _CSSMCSPI_H    

#include "cssmtype.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct cssm_spi_csp_funcs {
    /* Information Functions */
    CSSM_RETURN (CSSMAPI *QuerySize) (CSSM_CSP_HANDLE CSPHandle,
                                      CSSM_CC_HANDLE CCHandle,
                                      const CSSM_CONTEXT_PTR Context,
                                      CSSM_BOOL Encrypt,
                                      uint32 QuerySizeCount,
                                      CSSM_QUERY_SIZE_DATA_PTR DataBlock);
    /* Crypto Functions */
    CSSM_RETURN (CSSMAPI *SignData) (CSSM_CSP_HANDLE CSPHandle,
                                     CSSM_CC_HANDLE CCHandle,
                                     const CSSM_CONTEXT_PTR Context,
                                     const CSSM_DATA_PTR DataBufs,
                                     uint32 DataBufCount,
                                     CSSM_DATA_PTR Signature);
    CSSM_RETURN (CSSMAPI *SignDataInit) (CSSM_CSP_HANDLE CSPHandle,
                                         CSSM_CC_HANDLE CCHandle,
                                         const CSSM_CONTEXT_PTR Context);
    CSSM_RETURN (CSSMAPI *SignDataUpdate) (CSSM_CSP_HANDLE CSPHandle,
                                           CSSM_CC_HANDLE CCHandle,
                                           const CSSM_DATA_PTR DataBufs,
                                           uint32 DataBufCount);
    CSSM_RETURN (CSSMAPI *SignDataFinal) (CSSM_CSP_HANDLE CSPHandle,
                                          CSSM_CC_HANDLE CCHandle,
                                          CSSM_DATA_PTR Signature);
    CSSM_BOOL (CSSMAPI *VerifyData) (CSSM_CSP_HANDLE CSPHandle,
                                     CSSM_CC_HANDLE CCHandle,
                                     const CSSM_CONTEXT_PTR Context,
                                     const CSSM_DATA_PTR DataBufs,
                                     uint32 DataBufCount,
                                     const CSSM_DATA_PTR Signature);
    CSSM_RETURN (CSSMAPI *VerifyDataInit) (CSSM_CSP_HANDLE CSPHandle,
                                           CSSM_CC_HANDLE CCHandle,
                                           const CSSM_CONTEXT_PTR Context);
    CSSM_RETURN (CSSMAPI *VerifyDataUpdate) (CSSM_CSP_HANDLE CSPHandle,
                                             CSSM_CC_HANDLE CCHandle,
                                             const CSSM_DATA_PTR DataBufs,
                                             uint32 DataBufCount);
    CSSM_BOOL (CSSMAPI *VerifyDataFinal) (CSSM_CSP_HANDLE CSPHandle,
                                          CSSM_CC_HANDLE CCHandle,
                                          const CSSM_DATA_PTR Signature);
    CSSM_RETURN (CSSMAPI *DigestData) (CSSM_CSP_HANDLE CSPHandle,
                                       CSSM_CC_HANDLE CCHandle,
                                       const CSSM_CONTEXT_PTR Context,
                                       const CSSM_DATA_PTR DataBufs,
                                       uint32 DataBufCount,
                                       CSSM_DATA_PTR Digest);
    CSSM_RETURN (CSSMAPI *DigestDataInit) (CSSM_CSP_HANDLE CSPHandle,
                                           CSSM_CC_HANDLE CCHandle,
                                           const CSSM_CONTEXT_PTR Context);
    CSSM_RETURN (CSSMAPI *DigestDataUpdate) (CSSM_CSP_HANDLE CSPHandle,
                                             CSSM_CC_HANDLE CCHandle,
                                             const CSSM_DATA_PTR DataBufs,
                                             uint32 DataBufCount);
    CSSM_RETURN (CSSMAPI *DigestDataClone) (CSSM_CSP_HANDLE CSPHandle,
                                               CSSM_CC_HANDLE oldCCHandle,
                                               CSSM_CC_HANDLE newCCHandle);
    CSSM_RETURN (CSSMAPI *DigestDataFinal) (CSSM_CSP_HANDLE CSPHandle,
                                            CSSM_CC_HANDLE CCHandle,
                                            CSSM_DATA_PTR Digest);
    CSSM_RETURN (CSSMAPI *GenerateMac) (CSSM_CSP_HANDLE CSPHandle,
                                        CSSM_CC_HANDLE CCHandle,
                                        const CSSM_CONTEXT_PTR Context,
                                        const CSSM_DATA_PTR DataBufs,
                                        uint32 DataBufCount,
                                        CSSM_DATA_PTR Mac);
    CSSM_RETURN (CSSMAPI *GenerateMacInit) (CSSM_CSP_HANDLE CSPHandle,
                                            CSSM_CC_HANDLE CCHandle,
                                            const CSSM_CONTEXT_PTR Context);
    CSSM_RETURN (CSSMAPI *GenerateMacUpdate) (CSSM_CSP_HANDLE CSPHandle,
                                              CSSM_CC_HANDLE CCHandle,
                                              const CSSM_DATA_PTR DataBufs,
                                              uint32 DataBufCount);
    CSSM_RETURN (CSSMAPI *GenerateMacFinal) (CSSM_CSP_HANDLE CSPHandle,
                                             CSSM_CC_HANDLE CCHandle,
                                             CSSM_DATA_PTR Mac);
    CSSM_RETURN (CSSMAPI *VerifyMac) (CSSM_CSP_HANDLE CSPHandle,
                                        CSSM_CC_HANDLE CCHandle,
                                        const CSSM_CONTEXT_PTR Context,
                                        const CSSM_DATA_PTR DataBufs,
                                        uint32 DataBufCount,
                                        CSSM_DATA_PTR Mac);
    CSSM_RETURN (CSSMAPI *VerifyMacInit) (CSSM_CSP_HANDLE CSPHandle,
                                            CSSM_CC_HANDLE CCHandle,
                                            const CSSM_CONTEXT_PTR Context);
    CSSM_RETURN (CSSMAPI *VerifyMacUpdate) (CSSM_CSP_HANDLE CSPHandle,
                                              CSSM_CC_HANDLE CCHandle,
                                              const CSSM_DATA_PTR DataBufs,
                                              uint32 DataBufCount);
    CSSM_RETURN (CSSMAPI *VerifyMacFinal) (CSSM_CSP_HANDLE CSPHandle,
                                           CSSM_CC_HANDLE CCHandle,
                                           CSSM_DATA_PTR Mac);
    CSSM_RETURN (CSSMAPI *EncryptData) (CSSM_CSP_HANDLE CSPHandle,
                                        CSSM_CC_HANDLE CCHandle,
                                        const CSSM_CONTEXT_PTR Context,
                                        const CSSM_DATA_PTR ClearBufs,
                                        uint32 ClearBufCount,
                                        CSSM_DATA_PTR CipherBufs,
                                        uint32 CipherBufCount,
                                        uint32 *bytesEncrypted,
                                        CSSM_DATA_PTR RemData);
    CSSM_RETURN (CSSMAPI *EncryptDataInit) (CSSM_CSP_HANDLE CSPHandle,
                                            CSSM_CC_HANDLE CCHandle,
                                            const CSSM_CONTEXT_PTR Context);
    CSSM_RETURN (CSSMAPI *EncryptDataUpdate) (CSSM_CSP_HANDLE CSPHandle,
                                              CSSM_CC_HANDLE CCHandle,
                                              const CSSM_DATA_PTR ClearBufs,
                                              uint32 ClearBufCount,
                                              CSSM_DATA_PTR CipherBufs,
                                              uint32 CipherBufCount,
                                              uint32 *bytesEncrypted);
    CSSM_RETURN (CSSMAPI *EncryptDataFinal) (CSSM_CSP_HANDLE CSPHandle,
                                             CSSM_CC_HANDLE CCHandle,
                                             CSSM_DATA_PTR RemData);
    CSSM_RETURN (CSSMAPI *DecryptData) (CSSM_CSP_HANDLE CSPHandle,
                                        CSSM_CC_HANDLE CCHandle,
                                        const CSSM_CONTEXT_PTR Context,
                                        const CSSM_DATA_PTR CipherBufs,
                                        uint32 CipherBufCount,
                                        CSSM_DATA_PTR ClearBufs,
                                        uint32 ClearBufCount,
                                        uint32 *bytesDecrypted,
                                        CSSM_DATA_PTR RemData);
    CSSM_RETURN (CSSMAPI *DecryptDataInit) (CSSM_CSP_HANDLE CSPHandle,
                                            CSSM_CC_HANDLE CCHandle,
                                            const CSSM_CONTEXT_PTR Context);
    CSSM_RETURN (CSSMAPI *DecryptDataUpdate) (CSSM_CSP_HANDLE CSPHandle,
                                              CSSM_CC_HANDLE CCHandle,
                                              const CSSM_DATA_PTR CipherBufs,
                                              uint32 CipherBufCount,
                                              CSSM_DATA_PTR ClearBufs,
                                              uint32 ClearBufCount,
                                              uint32 *bytesDecrypted);
    CSSM_RETURN (CSSMAPI *DecryptDataFinal) (CSSM_CSP_HANDLE CSPHandle,
                                             CSSM_CC_HANDLE CCHandle,
                                             CSSM_DATA_PTR RemData);
    CSSM_RETURN (CSSMAPI *QueryKeySizeInBits) (CSSM_CSP_HANDLE CSPHandle,
											   CSSM_CC_HANDLE CCHandle,
                                               CSSM_KEY_SIZE_PTR KeySize);
    CSSM_RETURN (CSSMAPI *GenerateKey) (CSSM_CSP_HANDLE CSPHandle,
                                        CSSM_CC_HANDLE CCHandle,
                                        const CSSM_CONTEXT_PTR Context,
                                        uint32 KeyUsage,
                                        uint32 KeyAttr,
                                        const CSSM_DATA_PTR KeyLabel,
                                        CSSM_KEY_PTR Key);
    CSSM_RETURN (CSSMAPI *GenerateKeyPair) (CSSM_CSP_HANDLE CSPHandle,
                                            CSSM_CC_HANDLE CCHandle,
                                            const CSSM_CONTEXT_PTR Context,
                                            uint32 PublicKeyUsage,
                                            uint32 PublicKeyAttr,
                                            const CSSM_DATA_PTR PublicKeyLabel,
                                            CSSM_KEY_PTR PublicKey,
                                            uint32 PrivateKeyUsage,
                                            uint32 PrivateKeyAttr,
                                            const CSSM_DATA_PTR PrivateKeyLabel,
                                            CSSM_KEY_PTR PrivateKey);

    CSSM_RETURN (CSSMAPI *GenerateRandom) (CSSM_CSP_HANDLE CSPHandle,
                                           CSSM_CC_HANDLE CCHandle,
                                           const CSSM_CONTEXT_PTR Context,
                                           CSSM_DATA_PTR RandomNumber);
    CSSM_RETURN (CSSMAPI *GenerateAlgorithmParams) (CSSM_CSP_HANDLE CSPHandle,
                                                    CSSM_CC_HANDLE CCHandle,
                                                    const CSSM_CONTEXT_PTR Context,
                                                    uint32 ParamBits,
                                                    CSSM_DATA_PTR Param);
    CSSM_RETURN (CSSMAPI *WrapKey) (CSSM_CSP_HANDLE CSPHandle,
                                    CSSM_CC_HANDLE CCHandle,
                                    const CSSM_CONTEXT_PTR Context,
                                    const CSSM_CRYPTO_DATA_PTR PassPhrase, 
                                    const CSSM_KEY_PTR Key,
                                    CSSM_WRAP_KEY_PTR WrappedKey);
    CSSM_RETURN (CSSMAPI *UnwrapKey) (CSSM_CSP_HANDLE CSPHandle, 
                                      CSSM_CC_HANDLE CCHandle,
                                      const CSSM_CONTEXT_PTR Context,
                                      const CSSM_CRYPTO_DATA_PTR NewPassPhrase,
                                      const CSSM_WRAP_KEY_PTR WrappedKey,
                                      uint32 StorageMask,
                                      const CSSM_DATA_PTR KeyLabel,
                                      CSSM_KEY_PTR UnwrappedKey);
    CSSM_RETURN (CSSMAPI *DeriveKey) (CSSM_CSP_HANDLE CSPHandle,
                                      CSSM_CC_HANDLE CCHandle,
                                      const CSSM_CONTEXT_PTR Context,
                                      const CSSM_KEY_PTR BaseKey,
                                      void *Param,
                                      uint32 KeyUsage,
                                      uint32 KeyAttr,
                                      const CSSM_DATA_PTR KeyLabel,
                                      CSSM_KEY_PTR DerivedKey);

    /* Expandability Functions */
    void * (CSSMAPI *PassThrough) (CSSM_CSP_HANDLE CSPHandle, 
                                   CSSM_CC_HANDLE CCHandle,
                                   const CSSM_CONTEXT_PTR Context,
                                   uint32 PassThroughId,
                                   const void * InData);
    /* User Login Functions */
    CSSM_RETURN (CSSMAPI *Login) (CSSM_CSP_HANDLE CSPHandle,
                                  const CSSM_CRYPTO_DATA_PTR Password,
                                  const CSSM_DATA_PTR Reserved);
    CSSM_RETURN (CSSMAPI *Logout) (CSSM_CSP_HANDLE CSPHandle);
    CSSM_RETURN (CSSMAPI *ChangeLoginPassword) 
                                      (CSSM_CSP_HANDLE CSPHandle,
                                       const CSSM_CRYPTO_DATA_PTR OldPassword,
                                       const CSSM_CRYPTO_DATA_PTR NewPassword);

} CSSM_SPI_CSP_FUNCS, *CSSM_SPI_CSP_FUNCS_PTR;

#ifdef __cplusplus
}
#endif


#endif
