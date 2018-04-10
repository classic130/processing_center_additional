////////////vssc_util.h//////////////////////////////
#ifndef VSSC_UTIL_H
#define VSSC_UTIL_H



HRESULT GetSignerCertificate(
							 _bstr_t bstrEmailAddr,
							 _bstr_t m_bstrCertResolutionURL,
							 PCERT_RESOLVE_INFO  pCertResolveInfo,
							 PCERT_REQ_CRIT_INFO pCertReqCritInfo[],
							 int  nCertReqCertInfo,
							 CListUserInfo *i_pUserList
							 );

HRESULT GetEncryptionCertificates(
								  _bstr_t bstrEmailAddr,
								  _bstr_t m_bstrCertResolutionURL,
								  PCERT_RESOLVE_INFO  pCertResolveInfo,
								  PCERT_REQ_CRIT_INFO pCertReqCritInfo[],
								  int  nCertReqCertInfo,
								  CListUserInfo *i_pUserList
								  );

HRESULT GetPRC(
			  _bstr_t bstrEmailAddr,
			  _bstr_t m_bstrCertResolutionURL,
			  PCERT_RESOLVE_INFO  pCertResolveInfo,
			   CListUserInfo *i_pUserList
			  );

HRESULT HowToUsePRC(
					CListUserInfo *i_pPRCList,
					DWORD         dwPRCUse,
					PCERT_INFO     *pPRCCertInfo
					);


HRESULT VSSC_HashData(
					  int i_nHashAlg,
					  BYTE  *pInputData,
					  DWORD InputDataLength,
					  BYTE	**pbyteHash,
					  DWORD   *dwHashLength
					  );
/*
HRESULT  GetRSAKeyFromKeyInfo(
							  CERT_PUBLIC_KEY_INFO& i_CertPublicKeyInfo,
							  A_RSA_KEY* o_pTheKey
							  );
*/

HRESULT	 UnPadDataForVerify(
							const BYTE*	i_cpbyteData,
							const DWORD i_cdwDataLen,
							BYTE**	o_ppbyteUnPaddedData,
							DWORD*	o_pdwUnPaddedDataLen
							);


HRESULT  GetDataFromSequence(
							 const BYTE*i_cpbyteDataInSequence,
							 const DWORD 	i_cdwDataLenInSequence,
							 const DWORD	i_cdwAlgID,	
							 BYTE**o_ppbyteData,
							 DWORD*o_pdwDataLen
							 );



HRESULT _GetDateFromFileTime(FILETIME& i_ftTheFileTime, DATE* o_pDate);
HRESULT _GetCertSerNum(CRYPT_INTEGER_BLOB& i_SerialNumber, _bstr_t* o_ptbstrSerNum);
HRESULT _GetNameFromBlob(CERT_NAME_BLOB& i_TheNameBlob, _bstr_t* o_ptbstrName);
DWORD	 MyCertNameToStr(DWORD dwCertEncodingType, PCERT_NAME_BLOB pName, DWORD dwStrType,
																	LPTSTR psz, DWORD csz);
HRESULT _DecodeCertInfo(PCERT_INFO i_pCertInfo, PDECCERT_INFO io_pDecCertInfo);
bool	GetEndEntityCert(VS_CERT_BLOB CertSet, PVS_CERT_BLOB EndEntityCert);

HRESULT GetVers(char *szFileName, char *szVer);

void	TimetToFileTime( time_t t, LPFILETIME pft );
BOOL	CheckCertExpDate(DATE  dateEffDate,DATE dateExpDate);

int		CheckCertStatus(DWORD dwStatus,CERT_STATUS_INFO *pstCertStatusInfo);
void    FreeCertList(CListUserInfo	*pCertList);
void	freeAttachInfo(ATTACH_FILE_INFO	*pAttachedFiles);


HRESULT  GetAttachments(char *szFileList,FILEINFO **o_pFileInfo);
HRESULT  AddRFC822Header(VSSCMessage *Msg,CMsg *pCMsg);

HRESULT  FormatMIMEEntityForSigning(CMsg *pCMsg,char **szMimeEntity);

HRESULT	 GetMsgHeader(MSGINFO *MsgInfo,CMsg *pCMsg);

HRESULT  GM_PutMsgHeader(CMsg *pCMsg);
HRESULT  GM_GetMsgHeader(CMsg *pCMsg);

HRESULT  GM_PutMsgBody(CMsg *pCMsg);
HRESULT  GM_GetMsgBody(CMsg *pCMsg);

HRESULT  GM_PutMsgAttFileNames(CMsg *pCMsg,ATTACH_FILE_INFO*pInsertAttInfo);
HRESULT  GM_GetMsgAttFileNames(CMsg *pCMsg,ATTACH_FILE_INFO*pInsertAttInfo);

HRESULT  GM_PutMsgEntity(CMsg *pCMsg);
HRESULT  GM_GetMsgEntity(CMsg *pCMsg);

void GetFileName(char *szPathName,char**szFileName);


void ParseFileList(
				   char *szFileTitle, 
				   char *szFileList, 
				   FILEINFO *pFileInfo,
				   ATTACH_FILE_INFO	*g_AttachedFiles,
				   char **szOutputFileList,
				   BOOL& bDuplicate
				   );
BOOL CheckForDuplicateFile(char *szFile,
						   FILEINFO *pFileInfo,
						   ATTACH_FILE_INFO	*pAttachedFiles
						   );


#endif