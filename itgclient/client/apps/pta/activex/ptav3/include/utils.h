#ifndef _VS_PTA_UTILS_
#define _VS_PTA_UTILS_

#include <comdef.h>
#include <wincrypt.h>
#include "..\Include\ptauistructs.h"

#define CHECK_PROFILE(pNode, NodeType){\
	if(pNode == NULL)\
	{\
		hr = E_INVALIDPROFILE;\
		break;\
	}\
	if(pNode->currentBaseDER == NULL)\
	{\
		hr = E_INVALIDPROFILE;\
		break;\
	}\
	if(pNode->currentBaseDER->Type != NodeType)\
	{\
		hr = E_INVALIDPROFILE;\
		break;\
	}\
}

// Sasi - 04/14/2003
// This structure stores the info about bitmap. This info is passed to thread 
// that downloads bitmap from the web server.
typedef struct {
    _bstr_t  tbstrBmpUrl;     
    HBITMAP* phBitmap;
	HRESULT  status;
} BITMAP_THREAD_PARAM;

int BytesToAscHex(unsigned char* byteHashVal, int nHashValSize, _bstr_t& tbstrAscHexMD5);
int AscHexToBytes(_bstr_t& i_tbstrAscHex, unsigned char* o_pbyteBytes);
WCHAR* TCharToWChar(TCHAR* in_lptstrProfilesPath);
PUICTXT _CreateUIContext();
void _FreeUIContext(PUICTXT i_pUICtxt);
HRESULT _CopyUIContext(PUICTXT o_pUICtxtDest, PUICTXT i_pUICtxtSrc);
HRESULT _GetBitmap(_bstr_t& tbstrBmpUrl, HBITMAP* o_phBitmap);
HRESULT _FreeBitmap(HBITMAP i_hBitmap);
HRESULT _GetCertCN(_bstr_t& i_tbstrSubjectDN, _bstr_t* o_ptbstrSubjectCN);
HRESULT _FormatDate(DATE in_theDate, _bstr_t* o_ptbstrFormattedDate);
HRESULT _ParseDNIntoComponents(_bstr_t& i_tbstrSubjectDN, int* o_pnNumOfDNAttrs,_bstr_t** o_pptbstrDNAttrs, _bstr_t** o_pptbstrDNVals);
HRESULT GetKeyFromBlob(	const BYTE*	i_cpbyteKeyBlob,const DWORD	i_cdwKeyBlobLen,A_RSA_KEY* o_pKey);
HRESULT GetBlobFromKey(const A_RSA_KEY*	i_cpKey,BYTE**	o_ppbyteKeyBlob,DWORD*	o_pdwKeyBlobLen);
HRESULT	HashPublicKey(const A_RSA_KEY*	i_cpPublicKey,BYTE*	pbyteHash);
int mallocandcpy(BYTE*& pbDestBuff, BYTE* pbSrcBuff, unsigned int nBuffSize);
int freecertinfo(PCERT_INFO pCertInfo);
HRESULT _UTCToFiletime(unsigned char* pbUTCTime, FILETIME* ftFileTime);
HRESULT GetProfilePath(BSTR* o_pbstrProfilePath);
HRESULT CreateProfile_Path_Name(WCHAR* i_pwszProfileName, WCHAR* i_pwszAppCtxtName, BSTR* o_pbstrProfPathName);
DWORD MyCertNameToStr(DWORD dwCertEncodingType, PCERT_NAME_BLOB pName, DWORD dwStrType,
					  LPTSTR psz, DWORD csz);
_bstr_t GetRDNData(PBYTE i_pbRDNData, DWORD i_cbRDNData);
BOOL IsValidPath(const WCHAR* i_lpszPath);
BOOL IsLogicalDrive(WCHAR wcDrive);
HRESULT _CreateKeyFromPasswdAndSalt(PBYTE i_pbPassword, DWORD i_dwPassword, PBYTE i_pbSalt, DWORD i_dwSalt, PBYTE *o_pbKey, PDWORD o_pdwKey);

  // Sasi - 04/14/2003
  // Added new function that downloads a bitmap from the web server. 
  // This can be executed on a separate thread
HRESULT BitmapThreadFunc(BITMAP_THREAD_PARAM *lpParam);


HRESULT			ParseProfile_Path_Name
(
	const WCHAR*			i_cwszProfile_Path_Name,
	BSTR*					o_pbstrUserName,
	BSTR*					o_pbstrPath,
	BSTR*					o_pbstApContext
);

HRESULT			GetProfileInfoFromRegistry
(
	const WCHAR*			i_cwszContainerName,
	BSTR*					o_pbstrProfile,
	BSTR*					o_pbstrClientInfo,
	BSTR*					o_pbstrClientInfoSig,
	BOOL*					o_pboolIsLocal
);


HRESULT	CheckIfWinNTorWin2000(DWORD* o_pdwWindowsVersion);

HRESULT	UpdatePathIfNecessary (_bstr_t* io_ptbstrPath);


void	GetPathFromFileName
(
	_bstr_t				i_tbstrFileName,
	_bstr_t*			o_tbstrPath
);

BOOL	CreateRecursiveDirectory
(
	_bstr_t				i_tbstrDirToCreate
);

HRESULT PutDataInSequenceFunc
(
	const BYTE*			i_cpbyteData,
	const DWORD			i_cdwDataLen,
	const DWORD			i_cdwAlgID,
	BYTE**				o_ppbyteDataInSequence,
	DWORD*				o_pdwDataInSequenceLen
);

#endif

