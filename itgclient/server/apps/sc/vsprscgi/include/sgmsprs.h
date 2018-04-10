#include "vsprs.h" // API that will decode the SMIME Message.
#include "vsstring.h"

#include "vspmutil.h"
#include "LogWrapper.h"



// Constants 
#define PTACONTAINER		"PTAv2"
#define PTAAPPNAME			"ptaAppName"
#define PTAPASSWORDTIMEOUT	"ptaPasswordTimeout"
#define	SGMSPRSCONTAINER	"SGMSPRS"
#define	PTAFILE				"ptaUserName"
#define	PTAPASSWORD			"ptaPassword"
#define DEBUGMODE			"debugMode"
#define	DEBUGSMIMEFILE		"debugSMIMEFile"
#define AUTHDLL				"authDLL"
#define POLICYFILE			"sgmsprs.policy"
#define DEBUGLINE			" -----> "
#define USEENCCERT			"useEncCert"
#define ENCCERT				"encCert"
#define SMIMEMESSAGE		"smimeMessage"
#define BASE64ATTACHMENT	"base64Attachment"
#define MIMEOUTPUT			"mimeOutputFormat"
#define ROAMING				"roaming"
#define CLIENTINFO			"clientInfo"
#define CLIENTINFOSIG		"clientInfoSig"
#define CERTRESOLUTEURL		"certResolutionURL"
#define REENCRYPTEMAIL		"reEncryptEmail"
#define SSCEMAIL            "sscEmail"
#define SSCSUBJECT			"sscSubject"
#define CERTRESSOURCE		"certResolutionSource"
#define LOGFILE				"logFile"
#define LOGLEVEL			"logLevel"
#define SCTYPE				"scType"
#define SUPPORTED_PTA_VERSIONS	"supportedPTAVersions"
#define PTAPATH		"profilePath" 


// proto types
HRESULT GetConfiguration(VSPRSInfo *pInfo, CLogWrapper& logWrapper);
HRESULT GetSMIMEMessage(VSPRSInfo *pInfo, CLogWrapper& logWrapper);
void PostError(HRESULT rc,HRESULT appErrorCode=S_OK);
void HandleOutput(CProxyRecipients &myCPR, VSPRSInfo *info,CLogWrapper& logWrapper);
void HandleAttachments(CProxyRecipients &myCPR, VSString &flag,CLogWrapper& logWrapper);

// global variables
extern bool		debugMode;
extern VSString	debugSMIMEFile;

// Error Codes
#define PRS_POLICY_FILE_NOT_FOUND		0xFC01
#define PRS_INVALID_POLICY_FORMAT		0xFC02
#define PRS_SMIME_FILE_NOT_FOUND		0xFC03


// App error codes that i will send upwards
#define PRS_CONFIGURATION_ERROR		0x80009001
#define PRS_GETSMIME_ERROR			0x80009002
#define PRS_INITVSSC_ERROR			0x80009003
#define PRS_DECRYPTVERIFY_ERROR		0x80009004
#define PRS_HANDLEOUTPUT_ERROR		0x80009005
#define PRS_DUPPROFILE_ERROR		0x80009006
#define PRS_EXCEPTION_ERROR			0x80009FFD

// system errors
#define PRS_PASSWORDFAILED_ERROR	0x80009101
