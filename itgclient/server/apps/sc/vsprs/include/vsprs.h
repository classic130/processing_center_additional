// vsprs.h: interface for the CProxyRecipient class
//
// Change Log
//			- Ramakant 11/01/2001											 //
//			  Changed functions to incorporate new VSSC parameter
//			   pvarAppStatus
//			 - Added new member variable to VSPRSInfo for VSSC parameters
//			   SC type string VSString SCType
//			   Supported PTA Verison Info VSString SupportedPTAVersions

//////////////////////////////////////////////////////////////////////
///////////VSPRS.h/////////////////
#ifndef VSPRS_H
#define VSPRS_H

#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <wincrypt.h>
#include <comdef.h>
/////bsafelite related headers files
#include "integrate.h"

#include "vsprserrors.h"
#include "vsstring.h"
//#include "charutils.h"
#include "vsmimelib.h"
#include "sgmsCommon.h"


#include "vsprsattachments.h"

#define		VSSC_MSG_SIGNED	1
#define		VSSC_MSG_SIGN_ENCRYPT 2

#define		YES		"1"

enum VSPRS_CryptoStatus { CS_None = 0, CS_Ver = 1, CS_Dec = 2,
				    CS_DecVer = 3, CS_ReEnc = 4, CS_VerReEnc = 5, CS_DecReEnc = 6, CS_DecVerReEnc = 7 };

enum VSPRS_MsgType { MSG_None = 0, MSG_Sign = 1, MSG_Enc = 2, MSG_SignEnc = 3 };

enum VSPRS_BodyType { BD_CONTENT_TYPE, BD_CONTENT_XSFER_ENCODING, BD_CONTENT_DISP };
struct VSPRSInfo
{
	VSString  PTAProfile;             // input: required to open PTA profile
	VSString  PTAPassword;             // input: required to open PTA profile
	VSString  PTAApplication;         // input: required to open PTA profile
	VSString  PassWordTimeOut;        // input: required to open PTA profile
	VSString  EncryptedMIMEMessage;   // input: encrypted MIME message in EML format.
	VSString  AuthDLL;				  // input: Auth DLL for PTA to bypass the UI.
	VSString  ReEncryptEmail;		  // input: this is the end-user email addr used to do cert resolution and re-encrypt
	VSString  UseEncCert;			  // input: flag to use EncCert
	VSString  Base64Attachment;	  // input: base64-encode all attachments

	// For Roaming.
	VSString  ClientInfo;			
	VSString  ClientInfoSig;
	VSString  Roaming;
	
	// Cert Resolution URL.  For Re-Encrypt.
	VSString  CertResolutionURL;
	
	// Server-Side Crypto Email Addr.  Used for Re-Encryption, the
	// 'From' field will contain this email address.
	VSString  SSCEmail;

	// Server-Side Crypto Subject.  Used in the 'Subject' field to
	// inform recipient using his/her certificate to encrypt the
	// email.
	VSString SSCSubject;

	// Certificate Resolution Source.
	// This is to control whether or not the certifciate resolution
	// should use the recipient certificate embedded in the PKCS7
	// or via a dedicated certificate resolution service.
	//
	// The following values are meaningful:
	// 0 - from the certificate resolution service ONLY, 'certResolutionURL' will be used.
	// 1 - from PKCS7 ONLY.
	// 2 - first try the certificate resolution service, if not found, get certificate from PKCS7.
	// 3 - first try PKCS7, if not found, get the certificate from certificate resolution service.
	VSString CertResSource;

	// SC type string
	VSString SCType;

	// Supported PTA Verison Info
	VSString SupportedPTAVersions;

	// The path of the profile
	VSString PTAProfilePath;
};

typedef struct _VSPRS_MSGINFO {
	VSString	To;
	
	VSString	Cc;
	
	VSString	Bcc; 
	
	VSString	From;
	VSString	Date;
	VSString	Subject; 
	VSString	Body;			// this is the body with attachments.
	
	VSString	MsgType;
	VSString	AttachmentInfo;
	
	VSString	ReEncryptedContent;  // this contains the re-encrypted
									 // content, complete with headers.

	

	

	VSPRS_MsgType  SmimeType;
	
}VSPRS_MSGINFO ;




class CProxyRecipients  
{
public:

	// Getter functions
	VSPRS_MsgType		VSPRS_GetMsgType () { return mMsgInfo.SmimeType; }
	VSPRS_CryptoStatus	VSPRS_GetStatus  () { return mCStatus; }
	
	
	
	// MIME Getters
	const char *	VSPRS_GetFrom() { return (const char *)mMsgInfo.From; }
	const char *	VSPRS_GetTo() { return (const char *)mMsgInfo.To; }
	const char *	VSPRS_GetCC() { return (const char *)mMsgInfo.Cc; }
	const char *	VSPRS_GetBCC() { return (const char *)mMsgInfo.Bcc; }
	const char *	VSPRS_GetDate() { return (const char *)mMsgInfo.Date; }
	const char *	VSPRS_GetSubject() { return (const char *)mMsgInfo.Subject; }
	const char *    VSPRS_GetBody() { return (const char *)mMsgInfo.Body; }
	const char *    VSPRS_GeReEncryptedContent() { return (const char *)mMsgInfo.ReEncryptedContent; }
	// To be implemented in next version. 
	// const char *    VSPRS_GetBodyContent(VSPRS_BodyType bType);
	const char *    VSPRS_GetMimeBody () { return (const char *)mMsgInfo.Body; }

	VSPRSAttachment * VSPRS_GetAttachmentObj(VARIANT* i_pvarAppStatus);

	HRESULT VSPRS_Initialize(VSPRSInfo *proxyInfo,VARIANT* i_pvarAppStatus);
	HRESULT VSPRS_DecryptVerifySMIMEMessage(VARIANT* i_pvarAppStatus);
	
	
	
	void    VSPRS_SetMIMEMessage(const char * mimeStr) { mpVSPRSInfo->EncryptedMIMEMessage = mimeStr; }

	void    VSPRS_SetReEncrypted(bool flag) { mReEncrypted = flag; }
	void    VSPRS_SetRoaming(bool flag) { mRoaming = flag; }

	

	CProxyRecipients(VSPRSInfo *info = NULL);
	virtual ~CProxyRecipients();

private:

	HRESULT ValidateProxyInfo();
	
	void	SetMsgInfo();

	HRESULT	Release();
	HRESULT	InitPTA(VARIANT* i_pvarAppStatus);

	HRESULT HandleReEncryption(VARIANT* i_pvarAppStatus);

	

	void    CopyProxyInfo(VSPRSInfo *proxyInfo);


	VSPRSInfo		*mpVSPRSInfo;
	VSPRS_MSGINFO   mMsgInfo;
	VSString		mResultStr, mClearText;
	bool	mReEncrypted, mRoaming;

	VSPRS_CryptoStatus	mCStatus;

	VSPRSAttachment *mAttachment;
	
};

#endif


