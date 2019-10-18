#ifndef POLICYSUP_H
#define POLICYSUP_H

#define		MAX_INVALID_TRIES		3
#define		PASSWD_RETRY_TIMEOUT	15	// minutes

// structure to store the policy file variables.
typedef struct
{
	EncryptMethod EncryptMethod;
	BOOL bEncrMethodForced; 

	BOOL bSignatureReqd;
	BOOL bSigReqdForced;

	BOOL bSecureDelete;
	BOOL bSecDelForced;

	TCHAR EncryptionAlg[32];
	BOOL bEncrAlgForced;

	TCHAR HashAlg[32];
	BOOL bHashAlgForced;

	UINT LockOutPeriod;
	BOOL bLockPeriodForced;

	UINT PolicyTimeout;
	BOOL bPolicyTimeoutForced;

	TCHAR szFilter[2*MAX_PATH];
	BOOL bFilterForced;

	PasswordMethod PasswdMethod;
	BOOL bPasswdMethodForced;

	UINT PasswordPromptTimeout;
	BOOL bPasswdTimeoutForced;

	TCHAR szRemoteHost[MAX_PATH];
	TCHAR szIssuerDN[MAX_PATH];
	TCHAR szAppLogoUrl[MAX_PATH];
	TCHAR szLoginHelpUrl[MAX_PATH];
	TCHAR szRenewalHelpUrl[MAX_PATH];
	BOOL EnterpriseMode;
	TCHAR szInstallDir[MAX_PATH];
	BYTE AdminCert[4096];
	DWORD dwCertLen;
}PolicyVars, *LPPolicyVars;


// Linklist holding the Issuer DN and Serial number of the current and past
// certificates. If the Encryption/Signing certificate is modified then all
// the existing files in Safe are not re-encrypted/re-signed. So it is 
// necessary to maintain a list. This will be used while verifying the 
// authenticity of the user while decryption and signing files.
typedef struct tagCertDetails
{
	TCHAR szSerialNum[1024];
	TCHAR szIssuerDN[1024];
	FILETIME ftExpiryDate;
	BYTE Signature[5120];
	DWORD dwSigLen;
	struct tagCertDetails *pNext;
}CertDetails, *LPCertDetails;


// structure to store the Safe Settings which would usually go in the 
// registry. 
typedef struct
{
	DWORD bDecryptPane;			// Decrypt pane visible
	DWORD lDisplaySizes[10];	// ListView column headers
	DWORD lPolicyTimeout;		// Days after which remote policy file will
								// be downloaded, valid for Enterprise Mode
	DWORD bCheckExpiry;			// Set if a day is over. Needed to do expiry
								// checks on the certificate and also for
								// downloading the policyfile after 'lPolicyTimeout'
	FILETIME ftDay;			
	LPCertDetails pCurrEncrCert;
	LPCertDetails pOldEncrCerts;
}SafeSettings, *LPSafeSettings;


enum LoginStat
{
	LOGIN_OK,		// successfully logged into safe
	LOGIN_CANCEL,	// user pressed cancelled 
	LOGIN_INVALID	// invalid password or other failure
};



LoginStat AuthenticateUser(VOID);

BOOL InitSafe(VOID);
BOOL UpdateSafe(VOID);

//BOOL SetDefaultSafeValues(VOID);
BOOL IsOldPolicyFile(LPCTSTR);

BOOL GetSafeProps(VOID);
BOOL SetSafeProps(VOID);

BOOL ReadPolicyFile(VOID);
BOOL WritePolicyFile(VOID);
void UpdatePolicies(VSContainer, VSPM_STATUS);
BOOL DownloadRemotePolicyFile(LPCTSTR, DWORD*);
BOOL InitFilters();
BOOL ReadPolicyFileVar(LPCTSTR, LPCTSTR, UINT*, BOOL, LPCTSTR lpszPolyFilePath = NULL);
BOOL GetFETProfileInfo(BOOL*, BOOL*, LPTSTR, DWORD, LPTSTR, DWORD, LPTSTR, DWORD);

#endif  // POLICYSUP_H