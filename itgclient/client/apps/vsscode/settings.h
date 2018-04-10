#ifndef __VS_SETTINGS_
#define __VS_SETTINGS_

#define	MAIN_REG_KEY			(TEXT("Software\\VeriSign, Inc.\\CodeSigning"))
#define	CABLE_MODEM_REG_KEY		(TEXT("Software\\VeriSign, Inc.\\CodeSigning\\CableModem"))


// Registry keys used for initializing the PTA
#define APPCONTEXT			(TEXT("AppContext"))
#define CLINFO				(TEXT("ClientInfo"))
#define CLINFOSIG			(TEXT("ClientInfoSig"))
#define SRCHCRITERIA		(TEXT("SearchCriteria"))
#define CAPI				(TEXT("Capi"))


// Registry keys for performing signature
#define	HASHALG				(TEXT("HashAlg"))
#define DISP_DIGID			(TEXT("DisplayID"))


// Registry keys for password quality
#define	PASSWD_QUAL			(TEXT("PasswordQuality"))
#define	PASSWD_LEN			(TEXT("PasswordLen"))
#define PASSWD_TIMEOUT		(TEXT("PasswordTimeout"))
#define	PASSWD_TRIES		(TEXT("PasswordTries"))
#define PASSWD_UNLOCK		(TEXT("PasswordUnlockPeriod"))

// Registry key to determine if 'counter signature' is to be enabled for the 'SignOp' codetype
#define	COUNTER_SIGN		(TEXT("CounterSign"))


// Registry key storing the value of the current timer setting, system-time/user-time
#define	TIMER_SETTING		(TEXT("TimerSetting"))


#define	CODE_TYPE			(TEXT("CodeType"))


#define	LOG_ERROR			(TEXT("LogError"))



class CRegSettings
{
public:
	CRegSettings();
	~CRegSettings();

public:

	// Signature settings
	_bstr_t m_bstrHashAlg;
	DWORD m_dwDisplayDigID;

	// PTA settings
	_bstr_t m_bstrAppContext;
	_bstr_t m_bstrClientInfo;
	_bstr_t m_bstrClientInfoSig;
	_bstr_t m_bstrSrchCriteria;
	DWORD m_dwCapi;

	// Password settings used for cert enrollment
	DWORD m_dwPasswordQuality;
	DWORD m_dwPasswordLength;
	DWORD m_dwPasswordTimeout;
	DWORD m_dwPasswordTries;
	DWORD m_dwPasswordUnlockPeriod;

	// What file format are we stuffing the signature in
	_bstr_t m_bstrCodeType;

	// Determines the operation we are doing on the certificate
	CertificateOp m_CertOp;

	// If counter signature is required for the CodeType 'SigOp'
	DWORD m_dwCounterSign;

	// Determines whether to use system time or the user specified time in the authenticated signature attributes
	DWORD m_dwTimerSetting;
	
public:
	HRESULT Read(VOID);
	HRESULT Write(const _bstr_t i_tbstrValueName);
};

#endif	// __VS_SETTINGS_