#ifndef __VS_UTIL_
#define __VS_UTIL_

// Language identifiers
#define LANG_ENGLISH_US			0x0409

#define	MAX_SEL_FILES			4*1024
#define	MAX_FILE_SIZE			MAX_PATH*2

#define	ERR_STRING_LEN			12*1024
#define	MAX_STRING_LEN			1024

#define	LOGFILE					"c:\\vsscode.log"


enum OpStatus
{
	SIGN_SUCCEEDED,
	IMPORT_SUCCEEDED,
	EXPORT_SUCCEEDED,
	INSTALL_SUCCEEDED,
	CHANGE_PASSWD_SUCCEEDED
};


enum ErrType
{
	ERR_FATAL,
	ERR_QUES
};


VOID _LogErrorMsg(LPCTSTR i_pErrLocation, LPCTSTR i_pErrDesc, LPCTSTR i_pErrParam, DWORD i_dwErrCode);
BOOL ShowErrorMessage(HRESULT hr, LPCTSTR i_pErrParam = NULL, ErrType i_eErrType = ERR_FATAL);
VOID ShowSuccessMessage(OpStatus i_eStat);
HRESULT GetOpenFileNames(UINT i_idOFTitle, UINT i_idOFFilter, BOOL i_bMultipleSel, _bstr_t** o_pptbstrSelFiles, DWORD* o_pdwNumFiles);
HRESULT LoadStringW(HINSTANCE i_hInst, DWORD i_dwLangId, INT i_nStringID, WCHAR** o_wstrOutBuff);
DWORD _GetDefaultLangID(VOID);
BOOL _IsLangSupported(DWORD i_dwLangID);
HRESULT ParseServerPath(const _bstr_t& i_bstrServerPath, _bstr_t* o_pbstrServerName, _bstr_t* o_pbstrServerObject, LPDWORD o_pdwPortNum);
VOID _Base64Decode(PCHAR pInput, DWORD dwInputSize, PCHAR pOutput, LPDWORD dwOutputSize);
BOOL _decode(short input, DWORD *output);
unsigned int EraseMemory(unsigned int dwMemoryBlockSize, PBYTE pbyteMemoryBlock);
HRESULT GetUTCTime(LPTimeSettings i_lpTimeSettings, LPSYSTEMTIME o_lpUTCSysTime);

#endif // __VS_UTIL_