#ifndef __VS_CERTMGMT_
#define __VS_CERTMGMT_

// Key generation key flags
#define	AT_EXCHANGE_KEY			1
#define	EXPORTABLE_KEY			0
#define KEY_SIZE_1024			0x04000000

enum CertificateOp
{
	CERT_ENROLL,
	CERT_INSTALL,
	CERT_IMPORT,
	CERT_EXPORT,
	CERT_COSIGN,
	CERT_SIGNONLY,
	PROF_CHANGE_PASSWD
};

HRESULT CreateCSR(VOID);
HRESULT InstallCert(VOID);
HRESULT ImportCert(VOID);
HRESULT ExportCert(VOID);

HRESULT ChangePassword(VOID);

#endif // __VS_CERTMGMT_