/* SCCSID: inc/cssmapi.h, dss_cdsa_fwk, fwk_rel3, dss_980811 1.29 8/12/98 19:10:18 */
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

#ifndef _CSSMAPI_H
#define _CSSMAPI_H    

#include "cssmdefs.h"

/* API Functions */
#ifdef __cplusplus
extern "C" {
#endif

/* CSSM functions */
CSSM_RETURN CSSMAPI CSSM_Init (const CSSM_VERSION_PTR Version,
                               const CSSM_API_MEMORY_FUNCS_PTR MemoryFuncs,
                               const void * Reserved);

CSSM_CSSMINFO_PTR CSSMAPI CSSM_GetInfo (void);

CSSM_RETURN CSSMAPI CSSM_FreeInfo (CSSM_CSSMINFO_PTR CssmInfo);

CSSM_RETURN CSSMAPI CSSM_RequestCssmExemption (	CSSM_EXEMPTION_MASK ExemptionRequests,
												const char * AppFileName,
												const char * AppPathName,
												const void * Reserved);

CSSM_RETURN CSSMAPI CSSM_CheckCssmExemption (	CSSM_EXEMPTION_MASK *Exemptions);

CSSM_RETURN CSSMAPI CSSM_QueryModulePrivilege(const char *AppFileName, 
											  const char *AppPathName,
											  CSSM_EXEMPTION_MASK *Exemptions);

/* Multi service module functions */
CSSM_RETURN CSSMAPI CSSM_ModuleInstall (
                                 const char *ModuleName,
                                 const char *ModuleFileNames,
                                 const char *ModulePathName,
                                 const CSSM_GUID_PTR GUID,
                                 const CSSM_MODULE_INFO_PTR ModuleDescription,
                                 const void * Reserved1,
                                 const CSSM_DATA_PTR Reserved2);
CSSM_RETURN CSSMAPI CSSM_ModuleUninstall (const CSSM_GUID_PTR GUID);
CSSM_MODULE_HANDLE CSSMAPI CSSM_ModuleAttach (
                                    const CSSM_GUID_PTR GUID,
                                    const CSSM_VERSION_PTR Version,
                                    const CSSM_API_MEMORY_FUNCS_PTR MemoryFuncs,
                                    uint32 SubserviceID,
                                    uint32 SubserviceFlags,
                                    uint32 Application,
                                    const CSSM_NOTIFY_CALLBACK Notification, 
                                    const void * Reserved);
CSSM_RETURN CSSMAPI CSSM_ModuleDetach (CSSM_MODULE_HANDLE ModuleHandle);
CSSM_LIST_PTR CSSMAPI CSSM_ListModules (CSSM_SERVICE_MASK ServiceMask,
                                        CSSM_BOOL MatchAll);
CSSM_SERVICE_MASK CSSMAPI CSSM_GetGUIDUsage (const CSSM_GUID_PTR ModuleGUID);
CSSM_SERVICE_MASK CSSMAPI CSSM_GetHandleUsage (CSSM_HANDLE ModuleHandle);
CSSM_GUID_PTR CSSMAPI CSSM_GetModuleGUIDFromHandle (CSSM_HANDLE ModuleHandle);
CSSM_RETURN CSSMAPI CSSM_SetModuleInfo (const CSSM_GUID_PTR ModuleGUID,
                                        const CSSM_MODULE_INFO_PTR ModuleInfo);
CSSM_MODULE_INFO_PTR CSSMAPI CSSM_GetModuleInfo (const CSSM_GUID_PTR ModuleGUID,
                                                 CSSM_SERVICE_MASK ServiceMask,
                                                 uint32 SubserviceID,
                                                 CSSM_INFO_LEVEL InfoLevel);
CSSM_RETURN CSSMAPI CSSM_FreeModuleInfo (CSSM_MODULE_INFO_PTR ModuleInfo);
CSSM_DATA_PTR CSSMAPI CSSM_GetCSSMRegistryPath (void);
CSSM_DATA_PTR CSSMAPI CSSM_GetModuleLocation (const CSSM_GUID_PTR GUID);

/* Context API */
CSSM_CC_HANDLE CSSMAPI CSSM_CSP_CreateSignatureContext (
                                          CSSM_CSP_HANDLE CSPHandle,
                                          uint32 AlgorithmID,
                                          const CSSM_CRYPTO_DATA_PTR PassPhrase,
                                          const CSSM_KEY_PTR Key);

CSSM_CC_HANDLE CSSMAPI CSSM_CSP_CreateSymmetricContext (
                                            CSSM_CSP_HANDLE CSPHandle,
                                            uint32 AlgorithmID,
                                            uint32 Mode,
                                            const CSSM_KEY_PTR Key,
                                            const CSSM_DATA_PTR InitVector, 
                                            uint32 Padding,
                                            uint32 Params);

CSSM_CC_HANDLE CSSMAPI CSSM_CSP_CreateDigestContext (CSSM_CSP_HANDLE CSPHandle,
                                                     uint32 AlgorithmID);

CSSM_CC_HANDLE CSSMAPI CSSM_CSP_CreateMacContext (CSSM_CSP_HANDLE CSPHandle,
                                                  uint32 AlgorithmID,
                                                  const CSSM_KEY_PTR Key);

CSSM_CC_HANDLE CSSMAPI CSSM_CSP_CreateRandomGenContext (
                                            CSSM_CSP_HANDLE CSPHandle,
                                            uint32 AlgorithmID,
                                            const CSSM_CRYPTO_DATA_PTR Seed,
                                            uint32 Length);

CSSM_CC_HANDLE CSSMAPI CSSM_CSP_CreateAsymmetricContext (
                                          CSSM_CSP_HANDLE CSPHandle,
                                          uint32 AlgorithmID,
                                          const CSSM_CRYPTO_DATA_PTR PassPhrase,
                                          const CSSM_KEY_PTR Key,
                                          uint32 Padding);

CSSM_CC_HANDLE CSSMAPI CSSM_CSP_CreateKeyGenContext (
                                          CSSM_CSP_HANDLE CSPHandle,
                                          uint32 AlgorithmID,
                                          const CSSM_CRYPTO_DATA_PTR PassPhrase,
                                          uint32 KeySizeInBits,
                                          const CSSM_CRYPTO_DATA_PTR Seed,
                                          const CSSM_DATA_PTR Salt,
                                          const CSSM_DATE_PTR StartDate,
                                          const CSSM_DATE_PTR EndDate,
                                          const CSSM_DATA_PTR Params);

CSSM_CC_HANDLE CSSMAPI CSSM_CSP_CreateDeriveKeyContext (
                                        CSSM_CSP_HANDLE CSPHandle,
                                        uint32 AlgorithmID,
                                        CSSM_KEY_TYPE DeriveKeyType,
                                        uint32 DeriveKeyLength,
                                        uint32 IterationCount,
                                        const CSSM_DATA_PTR Salt,
                                        const CSSM_CRYPTO_DATA_PTR Seed,
                                        const CSSM_CRYPTO_DATA_PTR PassPhrase);

CSSM_CC_HANDLE CSSMAPI CSSM_CSP_CreatePassThroughContext (
                                                  CSSM_CSP_HANDLE CSPHandle,
                                                  const CSSM_KEY_PTR Key,
                                                  const CSSM_DATA_PTR ParamBufs,
                                                  uint32 ParamBufCount);

CSSM_CONTEXT_PTR CSSMAPI CSSM_GetContext (CSSM_CC_HANDLE CCHandle);

CSSM_RETURN CSSMAPI CSSM_SetContext (CSSM_CC_HANDLE CCHandle,
                                     const CSSM_CONTEXT_PTR Context);

CSSM_RETURN CSSMAPI CSSM_DeleteContext (CSSM_CC_HANDLE CCHandle);

CSSM_CONTEXT_ATTRIBUTE_PTR CSSMAPI CSSM_GetContextAttribute (
                                            const CSSM_CONTEXT_PTR Context,
                                            uint32 AttributeType);

CSSM_RETURN CSSMAPI CSSM_FreeContext (CSSM_CONTEXT_PTR Context);
CSSM_RETURN CSSMAPI CSSM_UpdateContextAttributes (
                           CSSM_CC_HANDLE CCHandle,
                           uint32 NumberAttributes,
                           const CSSM_CONTEXT_ATTRIBUTE_PTR ContextAttributes);

CSSM_RETURN CSSMAPI CSSM_DeleteContextAttributes (
                           CSSM_CC_HANDLE CCHandle,
                           uint32 NumberAttributes,
                           const CSSM_CONTEXT_ATTRIBUTE_PTR ContextAttributes);


/* Cryptography API */
/* Cryptography Operations */

CSSM_RETURN CSSMAPI CSSM_QuerySize (CSSM_CC_HANDLE CCHandle,
                                    CSSM_BOOL Encrypt,
                                    uint32 QuerySizeCount,
                                    CSSM_QUERY_SIZE_DATA_PTR DataBlock);

/*Returns a signature item */
CSSM_RETURN CSSMAPI CSSM_SignData (CSSM_CC_HANDLE CCHandle,
                                   const CSSM_DATA_PTR DataBufs,
                                   uint32 DataBufCount,
                                   CSSM_DATA_PTR Signature);

CSSM_RETURN CSSMAPI CSSM_SignDataInit (CSSM_CC_HANDLE CCHandle);

CSSM_RETURN CSSMAPI CSSM_SignDataUpdate (CSSM_CC_HANDLE CCHandle,
                                         const CSSM_DATA_PTR DataBufs,
                                         uint32 DataBufCount);

/* Returns a signature item */
CSSM_RETURN CSSMAPI CSSM_SignDataFinal (CSSM_CC_HANDLE CCHandle,
                                        CSSM_DATA_PTR Signature);

CSSM_BOOL CSSMAPI CSSM_VerifyData (CSSM_CC_HANDLE CCHandle,
                                   const CSSM_DATA_PTR DataBufs,
                                   uint32 DataBufCount,
                                   const CSSM_DATA_PTR Signature);

CSSM_RETURN CSSMAPI CSSM_VerifyDataInit (CSSM_CC_HANDLE CCHandle);

CSSM_RETURN CSSMAPI CSSM_VerifyDataUpdate (CSSM_CC_HANDLE CCHandle,
                                           const CSSM_DATA_PTR DataBufs,
                                           uint32 DataBufCount);

CSSM_BOOL CSSMAPI CSSM_VerifyDataFinal (CSSM_CC_HANDLE CCHandle,
                                        const CSSM_DATA_PTR Signature);

/* Returns a digest item */
CSSM_RETURN CSSMAPI CSSM_DigestData (CSSM_CC_HANDLE CCHandle,
                                     const CSSM_DATA_PTR DataBufs,
                                     uint32 DataBufCount,
                                     CSSM_DATA_PTR Digest);

CSSM_RETURN CSSMAPI CSSM_DigestDataInit (CSSM_CC_HANDLE CCHandle);

CSSM_RETURN CSSMAPI CSSM_DigestDataUpdate (CSSM_CC_HANDLE CCHandle,
                                           const CSSM_DATA_PTR DataBufs,
                                           uint32 DataBufCount);

CSSM_CC_HANDLE CSSMAPI CSSM_DigestDataClone (CSSM_CC_HANDLE CCHandle);

/* Returns a digest item */
CSSM_RETURN CSSMAPI CSSM_DigestDataFinal (CSSM_CC_HANDLE CCHandle,
                                          CSSM_DATA_PTR Digest);

/* Returns a mac data */
CSSM_RETURN CSSMAPI CSSM_GenerateMac (CSSM_CC_HANDLE CCHandle,
                                      const CSSM_DATA_PTR DataBufs,
                                      uint32 DataBufCount,
                                      CSSM_DATA_PTR Mac);

CSSM_RETURN CSSMAPI CSSM_GenerateMacInit (CSSM_CC_HANDLE CCHandle);

CSSM_RETURN CSSMAPI CSSM_GenerateMacUpdate (CSSM_CC_HANDLE CCHandle,
                                            const CSSM_DATA_PTR DataBufs,
                                            uint32 DataBufCount);

/* Returns a mac data */
CSSM_RETURN CSSMAPI CSSM_GenerateMacFinal (CSSM_CC_HANDLE CCHandle,
                                           CSSM_DATA_PTR Mac);

CSSM_RETURN CSSMAPI CSSM_VerifyMac (CSSM_CC_HANDLE CCHandle,
                                      const CSSM_DATA_PTR DataBufs,
                                      uint32 DataBufCount,
                                      CSSM_DATA_PTR Mac);

CSSM_RETURN CSSMAPI CSSM_VerifyMacInit (CSSM_CC_HANDLE CCHandle);

CSSM_RETURN CSSMAPI CSSM_VerifyMacUpdate (CSSM_CC_HANDLE CCHandle,
                                          const CSSM_DATA_PTR DataBufs,
                                          uint32 DataBufCount);

CSSM_RETURN CSSMAPI CSSM_VerifyMacFinal (CSSM_CC_HANDLE CCHandle,
                                         CSSM_DATA_PTR Mac);

/* Returns the encrypted data */
CSSM_RETURN CSSMAPI CSSM_EncryptData (CSSM_CC_HANDLE CCHandle,
                                      const CSSM_DATA_PTR ClearBufs,
                                      uint32 ClearBufCount,
                                      CSSM_DATA_PTR CipherBufs,
                                      uint32 CipherBufCount,
                                      uint32 *bytesEncrypted,
                                      CSSM_DATA_PTR RemData);

CSSM_RETURN CSSMAPI CSSM_EncryptDataInit (CSSM_CC_HANDLE CCHandle);

CSSM_RETURN CSSMAPI CSSM_EncryptDataUpdate (CSSM_CC_HANDLE CCHandle,
                                            const CSSM_DATA_PTR ClearBufs,
                                            uint32 ClearBufCount,
                                            CSSM_DATA_PTR CipherBufs,
                                            uint32 CipherBufCount,
                                            uint32 *bytesEncrypted);

/* Returns the encrypted data */
CSSM_RETURN CSSMAPI CSSM_EncryptDataFinal (CSSM_CC_HANDLE CCHandle,
                                           CSSM_DATA_PTR RemData);

/* Returns the decrypted data */
CSSM_RETURN CSSMAPI CSSM_DecryptData (const CSSM_CC_HANDLE CCHandle,
                                      const CSSM_DATA_PTR CipherBufs,
                                      uint32 CipherBufCount,
                                      CSSM_DATA_PTR ClearBufs,
                                      uint32 ClearBufCount,
                                      uint32 *bytesDecrypted,
                                      CSSM_DATA_PTR RemData);

CSSM_RETURN CSSMAPI CSSM_DecryptDataInit (CSSM_CC_HANDLE CCHandle);

CSSM_RETURN CSSMAPI CSSM_DecryptDataUpdate (CSSM_CC_HANDLE CCHandle,
                                            const CSSM_DATA_PTR CipherBufs,
                                            uint32 CipherBufCount,
                                            CSSM_DATA_PTR ClearBufs,
                                            uint32 ClearBufCount,
                                            uint32 *bytesDecrypted);
/* Returns the decrypted data */
CSSM_RETURN CSSMAPI CSSM_DecryptDataFinal (CSSM_CC_HANDLE CCHandle,
                                           CSSM_DATA_PTR RemData);

/* Query to get the key size */
CSSM_RETURN CSSMAPI CSSM_QueryKeySizeInBits (CSSM_CSP_HANDLE CSPHandle,
											 CSSM_CC_HANDLE CCHandle,
                                             CSSM_KEY_SIZE_PTR KeySize);

/* Returns the symmetric key */
CSSM_RETURN CSSMAPI CSSM_GenerateKey (CSSM_CC_HANDLE CCHandle,
                                      uint32 KeyUsage,
                                      uint32 KeyAttr,
                                      const CSSM_DATA_PTR KeyLabel,
                                      CSSM_KEY_PTR Key);

/* Returns the asymmetric key pair */
CSSM_RETURN CSSMAPI CSSM_GenerateKeyPair (CSSM_CC_HANDLE CCHandle,
                                          uint32 PublicKeyUsage,
                                          uint32 PublicKeyAttr,
                                          const CSSM_DATA_PTR PublicKeyLabel,
                                          CSSM_KEY_PTR PublicKey,
                                          uint32 PrivateKeyUsage,
                                          uint32 PrivateKeyAttr,
                                          const CSSM_DATA_PTR PrivateKeyLabel,
                                          CSSM_KEY_PTR PrivateKey);

/* Returns the random data */
CSSM_RETURN CSSMAPI CSSM_GenerateRandom (CSSM_CC_HANDLE CCHandle,
                                         CSSM_DATA_PTR RandomNumber);

CSSM_RETURN CSSMAPI CSSM_GenerateAlgorithmParams (CSSM_CC_HANDLE CCHandle,
                                                  uint32 ParamBits,
                                                  CSSM_DATA_PTR Param);


CSSM_RETURN CSSMAPI CSSM_WrapKey (CSSM_CC_HANDLE CCHandle,
                                  const CSSM_CRYPTO_DATA_PTR PassPhrase, 
                                  const CSSM_KEY_PTR Key,
                                  CSSM_WRAP_KEY_PTR WrappedKey);

CSSM_RETURN CSSMAPI CSSM_UnwrapKey (CSSM_CC_HANDLE CCHandle,
                                    const CSSM_CRYPTO_DATA_PTR NewPassPhrase,
                                    const CSSM_WRAP_KEY_PTR WrappedKey,
                                    uint32 KeyAttr,
                                    const CSSM_DATA_PTR KeyLabel,
                                    CSSM_KEY_PTR UnwrappedKey);

CSSM_RETURN CSSMAPI CSSM_DeriveKey (CSSM_CC_HANDLE CCHandle,
                                    const CSSM_KEY_PTR BaseKey,
                                    void *Param,
                                    uint32 KeyUsage,
                                    uint32 KeyAttr,
                                    const CSSM_DATA_PTR KeyLabel,
                                    CSSM_KEY_PTR DerivedKey);

void * CSSMAPI CSSM_CSP_PassThrough (CSSM_CC_HANDLE CCHandle, 
                                     uint32 PassThroughId,
                                     const void *InData);

/* CSP Loging Functions */
CSSM_RETURN CSSMAPI CSSM_CSP_Login (CSSM_CSP_HANDLE CSPHandle,
                                    const CSSM_CRYPTO_DATA_PTR Password,
                                    const CSSM_DATA_PTR pReserved);

CSSM_RETURN CSSMAPI CSSM_CSP_Logout (CSSM_CSP_HANDLE CSPHandle);

CSSM_RETURN CSSMAPI CSSM_CSP_ChangeLoginPassword (
                                    CSSM_CSP_HANDLE CSPHandle,
                                    const CSSM_CRYPTO_DATA_PTR OldPassword,
                                    const CSSM_CRYPTO_DATA_PTR NewPassword);

/* Trust Policy API */
/* Trust Policy Operations */
/* Returns the signed certificate */
CSSM_DATA_PTR CSSMAPI CSSM_TP_CertSign (
                                    CSSM_TP_HANDLE TPHandle,
                                    CSSM_CL_HANDLE CLHandle,
                                    CSSM_CC_HANDLE CCHandle,
                                    const CSSM_DL_DB_LIST_PTR DBList,
                                    const CSSM_DATA_PTR CertToBeSigned,
                                    const CSSM_CERTGROUP_PTR SignerCertGroup,
                                    const CSSM_FIELD_PTR SignScope,
                                    uint32 ScopeSize);
/*
CSSM_BOOL CSSMAPI CSSM_TP_CertVerify (CSSM_TP_HANDLE TPHandle,
                                      CSSM_CL_HANDLE CLHandle,
                                      CSSM_DL_DB_LIST_PTR	DBList,
									  CSSM_CC_HANDLE CCHandle,
                                      const CSSM_FIELD_PTR  PolicyIdentifiers,
                                      uint32 NumberofPolicyIdentifiers,
                                      CSSM_TP_STOP_ON VerificationAbortOn,
                                      const CSSM_DATA_PTR CertToBeVerified,
                                      const CSSM_DATA_PTR AnchorCerts,
                                      uint32 NumberofAnchorCerts,
                                      const CSSM_FIELD_PTR VerifyScope,
                                      uint32 ScopeSize,
                                      CSSM_TP_ACTION Action,
                                      const CSSM_DATA_PTR Data,
                                      CSSM_DATA_PTR *Evidence,
                                      uint32 *EvidenceSize);
*/
/* Returns the new CRL */
CSSM_DATA_PTR CSSMAPI CSSM_TP_CertRevoke (
                                 CSSM_TP_HANDLE TPHandle,
                                 CSSM_CL_HANDLE CLHandle,
                                 CSSM_CC_HANDLE CCHandle,
                                 const CSSM_DL_DB_LIST_PTR DBList,
                                 const CSSM_DATA_PTR OldCrl,
                                 const CSSM_CERTGROUP_PTR CertGroupToBeRevoked,
                                 const CSSM_CERTGROUP_PTR RevokerCertGroup,
                                 CSSM_REVOKE_REASON Reason);

/* Returns the signed CRL */
CSSM_DATA_PTR CSSMAPI CSSM_TP_CrlSign (
                                  CSSM_TP_HANDLE TPHandle,
                                  CSSM_CL_HANDLE CLHandle,
                                  CSSM_CC_HANDLE CCHandle,
                                  const CSSM_DL_DB_LIST_PTR DBList,
                                  const CSSM_DATA_PTR CrlToBeSigned,
                                  const CSSM_CERTGROUP_PTR SignerCertGroup,
                                  const CSSM_FIELD_PTR SignScope,
                                  uint32 ScopeSize);

CSSM_BOOL CSSMAPI CSSM_TP_CrlVerify (
                                CSSM_TP_HANDLE TPHandle,
                                CSSM_CL_HANDLE CLHandle,
                                CSSM_CSP_HANDLE CSPHandle,
                                const CSSM_DL_DB_LIST_PTR DBList,
                                const CSSM_DATA_PTR CrlToBeVerified,
                                const CSSM_CERTGROUP_PTR SignerCertGroup,
                                const CSSM_FIELD_PTR VerifyScope,
                                uint32 ScopeSize);

CSSM_RETURN CSSMAPI CSSM_TP_ApplyCrlToDb (CSSM_TP_HANDLE TPHandle,
                                          CSSM_CL_HANDLE CLHandle,
                                          CSSM_CSP_HANDLE CSPHandle,
                                          const CSSM_DL_DB_LIST_PTR DBList,
                                          const CSSM_DATA_PTR Crl);

/* Cert Group Functions */
/* Returns the constructed cert group */
CSSM_CERTGROUP_PTR CSSMAPI CSSM_TP_CertGroupConstruct (
                                               CSSM_TP_HANDLE TPHandle,
                                               CSSM_CL_HANDLE CLHandle,
                                               CSSM_CSP_HANDLE CSPHandle,
											   CSSM_CERTGROUP_PTR CertGroupFrag,
                                               CSSM_DL_DB_LIST_PTR DBList);

/* Returns the pruned cert group */
CSSM_CERTGROUP_PTR CSSMAPI CSSM_TP_CertGroupPrune (
                                           CSSM_TP_HANDLE TPHandle,
                                           CSSM_CL_HANDLE CLHandle,
                                           CSSM_CERTGROUP_PTR OrderedCertGroup,
                                           CSSM_DL_DB_LIST_PTR DBList);

CSSM_BOOL CSSMAPI CSSM_TP_CertGroupVerify (	  CSSM_TP_HANDLE TPHandle,
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

void * CSSMAPI CSSM_TP_PassThrough (CSSM_TP_HANDLE TPHandle, 
                                    CSSM_CL_HANDLE CLHandle, 
                                    CSSM_DL_HANDLE DLHandle, 
                                    CSSM_DB_HANDLE DBHandle, 
                                    CSSM_CC_HANDLE CCHandle, 
                                    uint32 PassThroughId,
                                    const void * InputParams);

/* Certificate Library Operations */

/* Returns the signed certificate */
CSSM_DATA_PTR CSSMAPI CSSM_CL_CertSign (CSSM_CL_HANDLE CLHandle, 
                                        CSSM_CC_HANDLE CCHandle, 
                                        const CSSM_DATA_PTR CertToBeSigned, 
                                        const CSSM_DATA_PTR SignerCert, 
                                        const CSSM_FIELD_PTR SignScope, 
                                        uint32 ScopeSize);

CSSM_BOOL CSSMAPI CSSM_CL_CertVerify (CSSM_CL_HANDLE CLHandle, 
                                      CSSM_CC_HANDLE CCHandle, 
                                      const CSSM_DATA_PTR CertToBeVerified, 
                                      const CSSM_DATA_PTR SignerCert, 
                                      const CSSM_FIELD_PTR VerifyScope,
                                      uint32 ScopeSize);

/* Returns the new certificate */
CSSM_DATA_PTR CSSMAPI CSSM_CL_CertCreateTemplate (CSSM_CL_HANDLE CLHandle, 
                                          const CSSM_FIELD_PTR CertTemplate, 
                                          uint32 NumberOfFields);

/* Returns the field value */
CSSM_DATA_PTR CSSMAPI CSSM_CL_CertGetFirstFieldValue (
                                                 CSSM_CL_HANDLE CLHandle, 
                                                 const CSSM_DATA_PTR Cert, 
                                                 const CSSM_OID_PTR CertField,
                                                 CSSM_HANDLE_PTR ResultsHandle,
                                                 uint32 *NumberOfMatchedFields);

/* Returns the field value */
CSSM_DATA_PTR CSSMAPI CSSM_CL_CertGetNextFieldValue (CSSM_CL_HANDLE CLHandle, 
                                                     CSSM_HANDLE ResultsHandle);

CSSM_RETURN CSSMAPI CSSM_CL_CertAbortQuery (CSSM_CL_HANDLE CLHandle, 
                                            CSSM_HANDLE ResultsHandle);

CSSM_KEY_PTR CSSMAPI CSSM_CL_CertGetKeyInfo (CSSM_CL_HANDLE CLHandle, 
                                             const CSSM_DATA_PTR Cert);

CSSM_FIELD_PTR CSSMAPI CSSM_CL_CertGetAllFields (CSSM_CL_HANDLE CLHandle,
                                                 const CSSM_DATA_PTR Cert,
                                                 uint32 *NumberOfFields);

/* Returns the certificate in the native cert format */
CSSM_DATA_PTR CSSMAPI CSSM_CL_CertImport (CSSM_CL_HANDLE CLHandle, 
                                          CSSM_CERT_TYPE ForeignCertType, 
                                          const CSSM_DATA_PTR ForeignCert); 

/* Returns the certificate in the foreign format */
CSSM_DATA_PTR CSSMAPI CSSM_CL_CertExport (CSSM_CL_HANDLE CLHandle, 
                                          CSSM_CERT_TYPE TargetCertType, 
                                          const CSSM_DATA_PTR NativeCert);

CSSM_OID_PTR CSSMAPI CSSM_CL_CertDescribeFormat (CSSM_CL_HANDLE CLHandle,
                                                 uint32 *NumberOfFields);

/* Returns the new CRL */
CSSM_DATA_PTR CSSMAPI CSSM_CL_CrlCreateTemplate (CSSM_CL_HANDLE CLHandle,
                                         const CSSM_FIELD_PTR CrlTemplate, 
                                         uint32 NumberOfFields);

/* Set general attribute fields in an unsigned CRL */
CSSM_DATA_PTR CSSMAPI CSSM_CL_CrlSetFields (CSSM_CL_HANDLE CLHandle,
                                            const CSSM_FIELD_PTR CrlTemplate,
                                            uint32 NumberOfFields,
                                            const CSSM_DATA_PTR OldCrl);

/* Returns the updated CRL */
CSSM_DATA_PTR CSSMAPI CSSM_CL_CrlAddCert (CSSM_CL_HANDLE CLHandle, 
                                          CSSM_CC_HANDLE CCHandle, 
                                          const CSSM_DATA_PTR Cert, 
                                          const CSSM_DATA_PTR RevokerCert, 
                                          const CSSM_FIELD_PTR CrlEntryFields,
                                          uint32 NumberOfFields,
                                          const CSSM_DATA_PTR OldCrl);

/* Returns the updated CRL */
CSSM_DATA_PTR CSSMAPI CSSM_CL_CrlRemoveCert (CSSM_CL_HANDLE CLHandle, 
                                             const CSSM_DATA_PTR Cert, 
                                             const CSSM_DATA_PTR OldCrl);

/* Returns the signed CRL */
CSSM_DATA_PTR CSSMAPI CSSM_CL_CrlSign (CSSM_CL_HANDLE CLHandle, 
                                       CSSM_CC_HANDLE CCHandle, 
                                       const CSSM_DATA_PTR UnsignedCrl, 
                                       const CSSM_DATA_PTR SignerCert, 
                                       const CSSM_FIELD_PTR SignScope,
                                       uint32 ScopeSize);

CSSM_BOOL CSSMAPI CSSM_CL_CrlVerify (CSSM_CL_HANDLE CLHandle, 
                                     CSSM_CC_HANDLE CCHandle, 
                                     const CSSM_DATA_PTR CrlToBeVerified, 
                                     const CSSM_DATA_PTR SignerCert,
                                     const CSSM_FIELD_PTR VerifyScope,
                                     uint32 ScopeSize);

CSSM_BOOL CSSMAPI CSSM_CL_IsCertInCrl (CSSM_CL_HANDLE CLHandle, 
                                       const CSSM_DATA_PTR Cert, 
                                       const CSSM_DATA_PTR Crl);

/* Returns the first item in the CRL */
CSSM_DATA_PTR CSSMAPI CSSM_CL_CrlGetFirstFieldValue (
                                               CSSM_CL_HANDLE CLHandle, 
                                               const CSSM_DATA_PTR Crl,
                                               const CSSM_OID_PTR CrlField,
                                               CSSM_HANDLE_PTR ResultsHandle,
                                               uint32 *NumberOfMatchedFields);

/* Returns the next item in the CRL */
CSSM_DATA_PTR CSSMAPI CSSM_CL_CrlGetNextFieldValue (CSSM_CL_HANDLE CLHandle, 
                                                    CSSM_HANDLE ResultsHandle);

CSSM_RETURN CSSMAPI CSSM_CL_CrlAbortQuery (CSSM_CL_HANDLE CLHandle, 
                                           CSSM_HANDLE ResultsHandle);

CSSM_OID_PTR CSSMAPI CSSM_CL_CrlDescribeFormat (CSSM_CL_HANDLE CLHandle,
                                                uint32 *NumberOfFields);

void * CSSMAPI CSSM_CL_PassThrough (CSSM_CL_HANDLE CLHandle, 
                                    CSSM_CC_HANDLE CCHandle, 
                                    uint32 PassThroughId, 
                                    const void * InputParams);


/* Database Library Operations */

CSSM_RETURN CSSMAPI CSSM_DL_Authenticate (
                      CSSM_DL_DB_HANDLE DLDBHandle,
                      const CSSM_DB_ACCESS_TYPE_PTR AccessRequest,
                      const CSSM_USER_AUTHENTICATION_PTR UserAuthentication);

CSSM_DB_HANDLE CSSMAPI CSSM_DL_DbOpen (
                       CSSM_DL_HANDLE DLHandle,
                       const char *DbName,
                       const CSSM_DB_ACCESS_TYPE_PTR AccessRequest,
                       const CSSM_USER_AUTHENTICATION_PTR UserAuthentication,
                       const void *OpenParameters);

CSSM_RETURN CSSMAPI CSSM_DL_DbClose (CSSM_DL_DB_HANDLE DLDBHandle);

CSSM_DB_HANDLE CSSMAPI CSSM_DL_DbCreate (
                      CSSM_DL_HANDLE DLHandle,
                      const char *DbName,
                      const CSSM_DBINFO_PTR DBInfo,
                      const CSSM_DB_ACCESS_TYPE_PTR AccessRequest,
                      const CSSM_USER_AUTHENTICATION_PTR UserAuthentication,
                      const void *OpenParameters);

CSSM_RETURN CSSMAPI CSSM_DL_DbDelete (
                     CSSM_DL_HANDLE DLHandle,
                     const char *DbName,
                     const CSSM_USER_AUTHENTICATION_PTR UserAuthentication);

CSSM_RETURN CSSMAPI CSSM_DL_DbImport (
                     CSSM_DL_HANDLE DLHandle,
                     const char *DbDestinationName,
                     const char *DbSourceName,
                     const CSSM_DBINFO_PTR DBInfo,
                     CSSM_BOOL InfoOnly,
                     const CSSM_USER_AUTHENTICATION_PTR UserAuthentication);

CSSM_RETURN CSSMAPI CSSM_DL_DbExport (
                     CSSM_DL_HANDLE DLHandle,
                     const char *DbDestinationName,
                     const char *DbSourceName,
                     CSSM_BOOL InfoOnly,
                     const CSSM_USER_AUTHENTICATION_PTR UserAuthentication);

CSSM_RETURN CSSMAPI CSSM_DL_DbSetRecordParsingFunctions (
                        CSSM_DL_HANDLE DLHandle,
                        const char* DbName,
                        CSSM_DB_RECORDTYPE RecordType,
                        const CSSM_DB_RECORD_PARSING_FNTABLE_PTR FunctionTable);

CSSM_DB_RECORD_PARSING_FNTABLE_PTR CSSMAPI CSSM_DL_DbGetRecordParsingFunctions (
                                          CSSM_DL_HANDLE DLHandle,
                                          const char* DbName,
                                          CSSM_DB_RECORDTYPE RecordType);


char * CSSMAPI CSSM_DL_GetDbNameFromHandle (
                                              CSSM_DL_DB_HANDLE DLDBHandle);


CSSM_DB_UNIQUE_RECORD_PTR CSSMAPI CSSM_DL_DataInsert (
                           CSSM_DL_DB_HANDLE DLDBHandle,
                           CSSM_DB_RECORDTYPE RecordType,
                           const CSSM_DB_RECORD_ATTRIBUTE_DATA_PTR Attributes, 
                           const CSSM_DATA_PTR Data);

CSSM_RETURN CSSMAPI CSSM_DL_DataDelete (
                       CSSM_DL_DB_HANDLE DLDBHandle,
                       CSSM_DB_RECORDTYPE RecordType,
                       const CSSM_DB_UNIQUE_RECORD_PTR UniqueRecordIdentifier);

CSSM_DB_UNIQUE_RECORD_PTR CSSMAPI CSSM_DL_DataGetFirst (
                       CSSM_DL_DB_HANDLE DLDBHandle,
                       const CSSM_QUERY_PTR Query,
                       CSSM_HANDLE_PTR  ResultsHandle,
                       CSSM_BOOL  *EndOfDataStore,
                       CSSM_DB_RECORD_ATTRIBUTE_DATA_PTR Attributes,
                       CSSM_DATA_PTR Data);

CSSM_DB_UNIQUE_RECORD_PTR CSSMAPI CSSM_DL_DataGetNext (
                                  CSSM_DL_DB_HANDLE DLDBHandle,
                                  CSSM_HANDLE ResultsHandle,
                                  CSSM_BOOL *EndOfDataStore,
                                  CSSM_DB_RECORD_ATTRIBUTE_DATA_PTR Attributes, 
                                  CSSM_DATA_PTR Data);

CSSM_RETURN CSSMAPI CSSM_DL_FreeUniqueRecord (
                                       CSSM_DL_DB_HANDLE DLDBHandle,
                                       CSSM_DB_UNIQUE_RECORD_PTR UniqueRecord);

CSSM_RETURN CSSMAPI CSSM_DL_AbortQuery (CSSM_DL_DB_HANDLE DLDBHandle,
                                      CSSM_HANDLE ResultsHandle);

void * CSSMAPI CSSM_DL_PassThrough (CSSM_DL_DB_HANDLE DLDBHandle, 
                                    uint32 PassThroughId,
                                    const void * InputParams); 

/* Utility Functions */
CSSM_RETURN CSSMAPI CSSM_VerifyComponents (void);

CSSM_RETURN CSSMAPI CSSM_FreeList (CSSM_LIST_PTR List);

void CSSMAPI CSSM_Free (void *MemPtr, CSSM_HANDLE AddInHandle);

CSSM_API_MEMORY_FUNCS_PTR CSSMAPI CSSM_GetAPIMemoryFunctions (
                                                   CSSM_HANDLE AddInHandle);

/* Error Handling */

#define CSSM_CompareGuids(guid1, guid2)    \
    ( ( (guid1.Data1 == guid2.Data1) &&    \
        (guid1.Data2 == guid2.Data2) &&    \
        (guid1.Data3 == guid2.Data3) &&    \
        (guid1.Data4[0] == guid2.Data4[0]) && \
        (guid1.Data4[1] == guid2.Data4[1]) && \
        (guid1.Data4[2] == guid2.Data4[2]) && \
        (guid1.Data4[3] == guid2.Data4[3]) && \
        (guid1.Data4[4] == guid2.Data4[4]) && \
        (guid1.Data4[5] == guid2.Data4[5]) && \
        (guid1.Data4[6] == guid2.Data4[6]) && \
        (guid1.Data4[7] == guid2.Data4[7]) ) ? CSSM_TRUE : CSSM_FALSE) 

CSSM_ERROR_PTR CSSMAPI CSSM_GetError (void);    /* gets the last error */
CSSM_RETURN CSSMAPI CSSM_SetError (CSSM_GUID_PTR guid, uint32  error);/* sets the error var to error */ 
void CSSMAPI CSSM_ClearError(void);        /* clear the value in the error var, 
                i.e., someone returned an error to 
                you, you have handled it and it is 
                no longer a valid error */



#ifdef KEY_RECOVERY

// Get the KR policy for a particular context
CSSM_RETURN CSSMAPI CSSM_KR_GetPolicyInfo (CSSM_CC_HANDLE CCHandle,
                                    uint32 *EncryptionProhibited,
                                    uint32 *WorkFactor);

CSSM_RETURN CSSMAPI CSSM_KR_QueryPolicyInfo(const uint32	AlgorithmID, 
									const uint32	Mode,
									const uint32	AlgClass,
									CSSM_POLICY_INFO_PTR *PolicyInfoData);

// Get strings describing the overall policy
// ManPolicyString = Jurisdiction of manufacture
// UsePolicyString = Jurisdiction of usage
CSSM_RETURN CSSMAPI CSSM_KR_GetPolicyStrings (
			char *ManPolicyString,
			int ManPolicyStrlen,
			char *UsePolicyString,
			int UsePolicyStrlen);

/* Key Recovery Context Operations */
CSSM_CC_HANDLE CSSMAPI CSSM_KR_CreateRecoveryEnablementContext(
            CSSM_KRSP_HANDLE KRSPHandle,
            CSSM_KR_PROFILE_PTR LocalProfile,
            CSSM_KR_PROFILE_PTR RemoteProfile);

CSSM_CC_HANDLE CSSMAPI CSSM_KR_CreateRecoveryRegistrationContext(
            CSSM_KRSP_HANDLE KRSPHandle);

CSSM_CC_HANDLE CSSMAPI CSSM_KR_CreateRecoveryRequestContext(
            CSSM_KRSP_HANDLE KRSPHandle,
            const CSSM_KR_PROFILE_PTR LocalProfile);

/* Key Recovery API */
/* Key Recovery Operations */
CSSM_RETURN CSSMAPI CSSM_KR_SetEnterpriseRecoveryPolicy(
            char *RecoveryPolicyFileName,
			const CSSM_CRYPTO_DATA_PTR OldPassPhrase, 
			const CSSM_CRYPTO_DATA_PTR NewPassPhrase);

CSSM_RETURN CSSMAPI CSSM_KR_RegistrationRequest(
			CSSM_CC_HANDLE RecoveryRegistrationContext,
			CSSM_DATA_PTR KRInData,
			CSSM_CRYPTO_DATA_PTR UserCallback,
			uint8 KRFlags,
			uint32 *EstimatedTime,
			CSSM_HANDLE_PTR ReferenceHandle);

CSSM_RETURN CSSMAPI CSSM_KR_RegistrationRetrieve(
			CSSM_KRSP_HANDLE hKRSP,
			CSSM_HANDLE ReferenceHandle,
			uint32 *EstimatedTime,
			CSSM_KR_PROFILE_PTR KRProfile);

CSSM_RETURN CSSMAPI CSSM_KR_RecoveryRequest(
            CSSM_CC_HANDLE RecoveryRequestContext,
            const CSSM_DATA_PTR KRInData,
            const CSSM_CRYPTO_DATA_PTR UserCallback,
            uint32 *EstimatedTime,
            const CSSM_HANDLE_PTR ReferenceHandle);

CSSM_RETURN CSSMAPI CSSM_KR_RecoveryRetrieve(
            CSSM_KRSP_HANDLE KRSPHandle,                                                                                                                             
            CSSM_HANDLE_PTR ReferenceHandle,
            uint32 *EstimatedTime,
            CSSM_HANDLE_PTR CacheHandle,
            uint32 *NumberOfRecoveredKeys);

CSSM_RETURN CSSMAPI CSSM_KR_GetRecoveredObject(
            CSSM_KRSP_HANDLE KRSPHandle,
            CSSM_HANDLE_PTR CacheHandle,
            uint32 IndexInResults,
            CSSM_CSP_HANDLE CSPHandle,
            const CSSM_CRYPTO_DATA_PTR PassPhrase,
            CSSM_KEY_PTR RecoveredKey,
            uint32 Flags,
            CSSM_DATA_PTR OtherInfo);

CSSM_RETURN CSSMAPI CSSM_KR_RecoveryRequestAbort(
            CSSM_KRSP_HANDLE KRSPHandle,
            CSSM_HANDLE CacheHandle);

CSSM_RETURN CSSMAPI CSSM_KR_GenerateRecoveryFields (
            CSSM_CC_HANDLE KRSPHandle,
            CSSM_CC_HANDLE CryptoContext,
            CSSM_DATA_PTR KRSPOptions,
            uint32 KRFlags,
            CSSM_DATA_PTR KRFields);

CSSM_RETURN CSSMAPI CSSM_KR_ProcessRecoveryFields (
            CSSM_CC_HANDLE KeyRecoveryContext,
            CSSM_CC_HANDLE CryptoContext,
            CSSM_DATA_PTR KRSPOptions,
            uint32 KRFlags,
            CSSM_DATA_PTR KRFields);

CSSM_RETURN CSSMAPI CSSM_KR_FreeKRProfile (CSSM_KR_PROFILE_PTR Profile);

CSSM_DATA_PTR CSSMAPI CSSM_KR_PassThrough(
            CSSM_KRSP_HANDLE KRSPHandle,
            CSSM_CC_HANDLE KeyRecoveryContext, 
            CSSM_CC_HANDLE CryptoContext,
            uint32 PassThroughId,
            const CSSM_DATA_PTR InputParams);
#endif

#ifdef __cplusplus
}
#endif

#endif
