#include "vssc.h"

#define ERROR_STRING_LEN 20

EXTERN_C IVSSC* VSSC_CreateInstance();

EXTERN_C wchar_t* get_VSSC_ToRecipientsInfo(IVSSC *pVSSC);
EXTERN_C unsigned int set_VSSC_ToRecipientsInfo(IVSSC *pVSSC, wchar_t* pwstrnewVal, int nLen);

EXTERN_C wchar_t* get_VSSC_CcRecipientsInfo(IVSSC *pVSSC);
EXTERN_C unsigned int set_VSSC_CcRecipientsInfo(IVSSC *pVSSC, wchar_t* pwstrnewVal, int nLen);

EXTERN_C wchar_t* get_VSSC_BccRecipientsInfo(IVSSC *pVSSC);
EXTERN_C unsigned int set_VSSC_BccRecipientsInfo(IVSSC *pVSSC, wchar_t* pwstrnewVal, int nLen);

EXTERN_C wchar_t* get_VSSC_FromInfo(IVSSC *pVSSC);
EXTERN_C unsigned int set_VSSC_FromInfo(IVSSC *pVSSC, wchar_t* pwstrnewVal, int nLen);

EXTERN_C wchar_t* get_VSSC_Subject(IVSSC *pVSSC);
EXTERN_C unsigned int set_VSSC_Subject(IVSSC *pVSSC, wchar_t* pwstrnewVal, int nLen);

EXTERN_C wchar_t* get_VSSC_Body(IVSSC *pVSSC);
EXTERN_C unsigned int set_VSSC_Body(IVSSC *pVSSC, wchar_t* pwstrnewVal, int nLen);

EXTERN_C wchar_t* get_VSSC_Date(IVSSC *pVSSC);
EXTERN_C unsigned int set_VSSC_Date(IVSSC *pVSSC, wchar_t* pwstrnewVal, int nLen);

EXTERN_C wchar_t* get_VSSC_SelectedAttachments(IVSSC *pVSSC);
EXTERN_C unsigned int set_VSSC_UnSelectAttachments(IVSSC *pVSSC, wchar_t* pwstrnewVal, int nLen);

EXTERN_C wchar_t* get_VSSC_GetMsg(IVSSC *pVSSC);

//EXTERN_C wchar_t* get_VSSC_DecryptMsg(IVSSC *pVSSC);

EXTERN_C wchar_t* get_VSSC_AttachedFileList(IVSSC *pVSSC);

EXTERN_C unsigned int set_VSSC_MsgPostData(IVSSC *pVSSC, wchar_t* pwstrnewVal, int nLen);

EXTERN_C unsigned int set_VSSC_CertResolveURL(IVSSC *pVSSC, wchar_t* pwstrnewVal, int nLen);

EXTERN_C short get_VSSC_MsgType(IVSSC *pVSSC);
EXTERN_C unsigned int set_VSSC_MsgType(IVSSC *pVSSC, short newVal);

EXTERN_C unsigned int get_VSSC_CryptStatus(IVSSC *pVSSC);


/******************** Methods **********************/

EXTERN_C unsigned int VSSC_Compose(IVSSC *pVSSC, wchar_t** ppwstrErrString);

EXTERN_C unsigned int VSSC_SelectAttachments(IVSSC *pVSSC, wchar_t** ppwstrErrString);

EXTERN_C short VSSC_SaveAttachment(IVSSC *pVSSC, wchar_t* pFileName, int nLen, wchar_t** ppwstrErrString);

//EXTERN_C wchar_t* VSSC_CertificateResolution(IVSSC *pVSSC, wchar_t* in_pvarEmailInfo, int nLen);
EXTERN_C unsigned int VSSC_CertificateResolution(IVSSC *pVSSC, wchar_t* in_pvarEmailInfo, int nLen, wchar_t** ppwstrErrString);

//EXTERN_C wchar_t* VSSC_SMIMECertificateResolution(IVSSC *pVSSC, wchar_t* in_pvarEmailInfo, int nLen);
EXTERN_C unsigned int VSSC_SMIMECertificateResolution(IVSSC *pVSSC, wchar_t** ppwstrErrString);

EXTERN_C short VSSC_Decompose(IVSSC *pVSSC, wchar_t* i_pvarSMIMEMsg, int nLen, wchar_t** ppwstrErrString);


EXTERN_C unsigned int VSSC_Initialize(IVSSC *pVSSC, int i_pMsgObjID, short i_pMode, wchar_t** ppwstrErrString);



EXTERN_C unsigned int VSSC_StoreAll(IVSSC *pVSSC, short i_pModeType, wchar_t** ppwstrErrString);

EXTERN_C unsigned int VSSC_InternetInitialize(IVSSC *pVSSC, wchar_t* in_pvarURL, int nLen1,
											  wchar_t* in_pvarMethod, int nLen2,
											  wchar_t* in_pvarPostData, int nLen3, wchar_t** ppwstrErrString);

EXTERN_C unsigned int VSSC_InternetSendRequest(IVSSC *pVSSC, wchar_t** ppwstrErrString);

EXTERN_C unsigned int VSSC_SelectedAttachmentSize(IVSSC *pVSSC, wchar_t* in_pvarFileName, int nLenString, wchar_t** ppwstrErrString);

EXTERN_C unsigned int get_VSSC_MsgObjID(IVSSC *pVSSC);

EXTERN_C unsigned int get_VSSC_MsgBlobSize(IVSSC *pVSSC);

EXTERN_C unsigned int get_VSSC_InternetDataSize(IVSSC *pVSSC);

EXTERN_C unsigned int set_VSSC_UseInternetData(IVSSC *pVSSC, BOOL newVal);

//EXTERN_C wchar_t* get_VSSC_InternetDataAsString(IVSSC *pVSSC);

EXTERN_C BYTE* get_VSSC_InternetData(IVSSC *pVSSC, int *nLen);

EXTERN_C unsigned int set_VSSC_UseProxyRecipCert(IVSSC *pVSSC, int newVal);





EXTERN_C unsigned int set_VSSC_AddSignerCertificate(IVSSC *pVSSC, BOOL newVal);

EXTERN_C unsigned int set_VSSC_AddAuthAttributes(IVSSC *pVSSC, BOOL newVal);

EXTERN_C unsigned int set_VSSC_AddRFC822Header(IVSSC *pVSSC, BOOL newVal);

EXTERN_C unsigned int set_VSSC_AddMIMEHeader(IVSSC *pVSSC, BOOL newVal);

EXTERN_C unsigned int set_VSSC_OpaqueSign(IVSSC *pVSSC, BOOL newVal);

EXTERN_C unsigned int set_VSSC_AddSenderRecipientInfo(IVSSC *pVSSC, BOOL newVal);


EXTERN_C unsigned int set_VSSC_SCType(IVSSC *pVSSC, wchar_t* pwstrnewVal, int nLen);
EXTERN_C wchar_t* get_VSSC_SCType(IVSSC *pVSSC);

EXTERN_C unsigned int set_VSSC_CertificateTimeOut(IVSSC *pVSSC, short newVal);
EXTERN_C short get_VSSC_CertificateTimeOut(IVSSC *pVSSC);

EXTERN_C unsigned int set_VSSC_MessageTimeOut(IVSSC *pVSSC, short newVal);
EXTERN_C short get_VSSC_MessageTimeOut(IVSSC *pVSSC);

EXTERN_C unsigned int VSSC_ClearAll(IVSSC *pVSSC, short newVal, wchar_t** ppwstrErrString);


EXTERN_C unsigned int set_VSSC_UsePKCS7Certificate(IVSSC *pVSSC, BOOL newVal);
EXTERN_C unsigned int set_VSSC_AddSMIMECapabilities(IVSSC *pVSSC, BOOL newVal);

EXTERN_C unsigned int set_VSSC_ShowSelIDUI(IVSSC *pVSSC, BOOL newVal);

EXTERN_C unsigned int set_VSSC_SupportedPTAVer(IVSSC *pVSSC, wchar_t* pwstrnewVal, int nLen);
EXTERN_C short get_VSSC_InstalledPTAVer(IVSSC *pVSSC);

EXTERN_C unsigned int set_VSSC_URLEncodeData(IVSSC *pVSSC, BOOL newVal);

EXTERN_C unsigned int VSSC_ResolveProxyRecipCert(IVSSC *pVSSC, wchar_t* pwstrnewVal, int nLen, wchar_t** ppwstrErrString, wchar_t** ppwstrStatusString);

EXTERN_C unsigned int set_VSSC_UseSimder(IVSSC *pVSSC, BOOL newVal);

EXTERN_C unsigned int set_VSSC_AllowDecryption(IVSSC *pVSSC, short newVal);





