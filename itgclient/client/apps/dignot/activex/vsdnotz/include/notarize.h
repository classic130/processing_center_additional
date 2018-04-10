#ifndef __NOTARIZE_H_
#define __NOTARIZE_H_


// UI flags which determine what UI will be shown during(after) notarization and verification
#define		UIFLAG_NONE			0x00
#define		UIFLAG_PROGRESS		0x01
#define		UIFLAG_COMPLETE		0x02
#define		UIFLAG_VERIFICATION	0x04
#define		UIFLAG_WEB_LINK		0x08
#define		UIFLAG_SAVE_DOC		0x10
#define		UIFLAG_VIEW_DOC		0x20

// Type of data which is passed to us during a verification operation, is it a URL or
// is it a base64 encoded record
#define		NZRECORD_URL		0x00
#define		NZRECORD_RAW		0x01


// Version of the Notarization server we support
#define		NZ_VERSION			0x01


// Content type 
#define		NZ_CONTENT_TYPE		"Content-Type:application/timestamp\n\r"
//#define		NZ_CONTENT_TYPE		"Content-Type:application/x-verisign-authdoc-request\n\r"

// Oid that defines the extension for the 'signed response' returned in the notarization response
// This 'signed response' is the same as the 'signed timestamp request'
#define		SIGNATURE_EXT_OID		"2.16.840.1.113733.1.6.16"

// Oid that defines the extension for the 'description' that goes in the timestamp request
#define		DOC_EXT_OID				"2.16.840.1.113733.1.6.20"


// Oid for the authentic document policy information, encoded in the request
//#define		AUTHDOC_POLICY_OID		"2.16.840.1.113733.1.7.23.5.2"
#define		AUTHDOC_POLICY_OID		"2.16.840.1.113733.1.7.23.5.1"


// Header info sent to the web server while doing a GET, should be similar to what IE/NS send
#define		NZ_HEADER_INFO			""


// Random data used as a nonce
#define		NONCE_DATA_SIZE		8


enum ResponseType
{
	RT_NZRESPONSE,	// the response from the notarization server
	RT_NZRECORD		// includes the response from the notarization server + some
					// data which we stuff in for creating a notarization record
};


// Status returned by the Notarization authority
enum NZRespStatus
{
	GRANTED,
	GRANTEDWITHMODS,
	REJECTION,
	WAITING,
	REVOCATIONWARNING
};


// This structure is used to hold the unsigned, signed notarization requests and also nonce
// generated during a notarization request
typedef struct
{
	PBYTE pbNzRequest;	// is the ASN.1 encoded notarization request
	DWORD dwNzRequest;

	PBYTE pbNzNonce;	// is the nonce which is sent in the notarization request
	DWORD dwNzNonce;

	PBYTE pbSignedNzRequest;	// is the signed ASN.1 encoded notarization request
	DWORD dwSignedNzRequest;

public:
	VOID Initialize();
	VOID Clear();

}NzRequest, *LPNzRequest;


// This structure hold the decoded ASN.1 response sent by the notarization server
typedef struct
{
	NZRespStatus NzResponseStatus;

	_bstr_t bstrStatusMsg;			// String to hold error string if server returns error

	DWORD dwFailInfo;

	DWORD dwNzVersion;

	PBYTE pbSerialNum;
	DWORD dwSerialNum;

	SYSTEMTIME NzFormattedSysTime;

	PBYTE pbNonce;
	DWORD dwNonce;

	_bstr_t bstrNzAuthorityName;
	_bstr_t bstrNzDocumentName;
	_bstr_t bstrDescription;
	_bstr_t bstrNzRequestor;

	_bstr_t tbstrUserAgent;

	BOOL bDocumentModified;

	PBYTE pbRawRecordData;
	DWORD dwRawRecordDataLen;

	PBYTE pbTimeStampToken;		// Is the signed time stamp response, used to create a temporary
	DWORD dwTimeStampToken;		// html file to be posted to the notarization server

	PBYTE pbAuthDocPolicy;		// Policy information returned by the notarization server
	DWORD dwAuthDocPolicy;		// Compare it with the policy that was requested

public:
	VOID Initialize();
	VOID Clear();
}NzDetails, *LPNzDetails;



// This structure holds the response sent by the notarization server. The response is ASN.1
// encoded
typedef struct
{
	PBYTE pbNzResponse;		// is the response sent by the notarization server
	DWORD dwNzResponse;

public:
	VOID Initialize();
	VOID Clear();
}NzResponse, *LPNzResponse;



class CNotarization
{
public:
	CNotarization(IVSPTA* i_pVSPta/*, BOOL i_bShowDigID*/);
	~CNotarization();

public:
	// Fns for notarizing a document
	HRESULT CreateNotarizationRequest(const _bstr_t& i_bstrDocument, PBYTE i_pbHashVal, const _bstr_t& i_bstrDescription, const _bstr_t& i_bstrHashAlg, const _bstr_t& i_bstrUserAgent, LPNzRequest o_pNotzRequest);
	HRESULT SignNotarizationRequest(const _bstr_t& i_bstrHashAlg, LPNzRequest io_pNotzRequest);
	HRESULT SendNotarizationRequest(const _bstr_t& i_bstrServer, const LPNzRequest i_pNotzRequest, LPNzResponse o_pNotzResponse);

	// Fns for verifying a notarization response
	HRESULT VerifyNotarizationResponse(const _bstr_t& i_bstrDocument, PBYTE i_pbHashVal, const LPNzResponse i_pNotzResponse, const DWORD i_dwValidateFlag, const _bstr_t& i_bstrRevocationInfo, const _bstr_t& i_bstrUserAgent, LPNzDetails o_pNzDetails);

	// Fns for opening a notarization request
	HRESULT OpenNotarizationRequest(const PBYTE i_pbNzRequest, const DWORD i_dwNzRequest, _bstr_t* o_pbstrDescription);
	
private:
	IVSPTA* m_pVSPta;	// pointer passed during object creation, used for crypto operations
	//BOOL	m_bShowDigID;	// whether the digital ID used for signing a notarization request 
							// will be displayed? if multiple ID's are present then the ID's 
							// will be displayed irrespective of this flag, unless a default
							// ID has been selected
				 
private:
	
};


_bstr_t _HandleError(const HRESULT i_hResult, NzDetails *i_pNotzDetails);

#endif // __NOTARIZE_H_