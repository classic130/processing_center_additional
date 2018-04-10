#ifndef __NZUSER_
#define __NZUSER_

// Registry settings used when notarizing a document from the context menu interface and 
// opening a receipt file by double clicking on it
#define	NZ_SERVER				(TEXT("NotarizationServer"))
#define NZ_HASHALG				(TEXT("HashAlg"))
#define NZ_RCPTDESC				(TEXT("ReceiptDesc"))
#define NZ_DISP_DIGID			(TEXT("DisplayID"))
#define NZ_VAL_FLAG				(TEXT("ValidationFlag"))
#define NZ_LOGOURL				(TEXT("LogoUrl"))
#define NZ_WIZTITLE				(TEXT("NzWizTitle"))
#define NZ_SELFILETITLE			(TEXT("SelFileTitle"))
#define NZ_SELFILEDESC			(TEXT("SelFileDesc"))
#define NZ_SELFILEHELPURL		(TEXT("SelFileHelpUrl"))
#define NZ_PROGRESSTITLE		(TEXT("ProgressTitle"))
#define NZ_PROGRESSDESC			(TEXT("ProgressDesc"))
#define NZ_PROGRESSHELPURL		(TEXT("ProgressHelpUrl"))
#define NZ_VERIFYRCPTITLE		(TEXT("VerifyReceiptTitle"))
#define NZ_VERIFYRCPTDESC		(TEXT("VerifyReceiptDesc"))
#define NZ_VERIFYRCPTHELPURL	(TEXT("VerifyReceiptHelpUrl"))
#define NZ_HELPURL				(TEXT("HelpUrl"))
#define NZ_CLINFO				(TEXT("ClientInfo"))
#define NZ_CLINFOSIG			(TEXT("ClientInfoSig"))
#define NZ_SRCHCRITERIA			(TEXT("SearchCriteria"))
#define NZ_CAPI					(TEXT("Capi"))
#define NZ_APPCONTEXT			(TEXT("AppContext"))
#define NZ_HOST_SERVER			(TEXT("HostingServer"))			// From where the client was downloaded
#define	NZ_ENROLL_HOMEPAGE		(TEXT("EnrollHomePage"))		// Digital ID enrollment page
#define NZ_RENEWAL_HOMEPAGE		(TEXT("RenewalHomePage"))		// Digital ID renewal page
#define NZ_CRL					(TEXT("Crl"))
#define NZ_TIMEOUT				(TEXT("TimeoutInterval"))
#define NZ_LAST_ACCESSED		(TEXT("LastAccessed"))
#define	NZ_CONTEXT_MENU			(TEXT("ContextMenu"))

class CUserSettings
{
public:
	CUserSettings();
	~CUserSettings();

public:
	// Notarization settings
	_bstr_t m_bstrNzServer;
	_bstr_t m_bstrHashAlg;
	_bstr_t m_bstrReceiptDescription;
	DWORD m_dwDisplayDigID;
	DWORD m_dwValidationFlags;

	// UI settings
	_bstr_t m_bstrLogoUrl;
	_bstr_t m_bstrDigNotWizTitle;
	_bstr_t m_bstrSelFileTitle;
	_bstr_t m_bstrSelFileDescription;
	_bstr_t m_bstrSelFileHelpUrl;
	_bstr_t m_bstrProgressTitle;
	_bstr_t m_bstrProgressDescription;
	_bstr_t m_bstrProgressHelpUrl;
	_bstr_t m_bstrVerifyRcptTitle;
	_bstr_t m_bstrVerifyRcptDescription;
	_bstr_t m_bstrVerifyRcptHelpUrl;


	// PTA settings
	_bstr_t m_bstrAppContext;
	_bstr_t m_bstrClientInfo;
	_bstr_t m_bstrClientInfoSig;
	_bstr_t m_bstrSrchCriteria;
	DWORD m_dwCapi;

	_bstr_t m_bstrHostingServer;		// Server from where control is downloaded
	_bstr_t m_bstrEnrollPage;			// Digital ID enrollment page
	_bstr_t m_bstrRenewalPage;			// Digital ID renewal page
	_bstr_t m_bstrCrl;					// Location from where CRL will be downloaded
										// if CDP is absent in certificate.

	// Timer settings for the Profile timeout
	DWORD m_dwTimeoutInterval;		// in minutes
	DWORD m_dwLastAccessed;			// obtained from GetTickCount() API call

public:
	HRESULT Read();
	VOID Dump(LPCTSTR i_pCaller);
};

#endif	// __NZUSER