#ifndef		__VS_CSP_GLOBALS__
#define		__VS_CSP_GLOBALS__


#include "cspstructures.h"


//CSP_State*		g_pCSP					=	NULL;
//DWORD			g_dwNumberOfCSPHandles	=	0;

#define		CSP_AP_CTXT_NAME					"VeriSign Personal Trust Agent (PTA)"
#define		CSP_VERSION_MAJOR					01
#define		CSP_VERSION_MINOR					00
#define		CSP_VERSION							0x00000100
#define		CSP_TYPE							PROV_RSA_FULL



#define		DONT_USE_CAPI						0
#define		DONT_ROAM							FALSE
#define		ROAM								TRUE

#define		SAVE_LOCAL							TRUE
#define		DONT_SAVE_LOCAL						FALSE


#define		VS_RC2								26114
#define		VS_RC4								26625
#define		VS_SHA_1							32772
#define		VS_MD2								32769
#define		VS_MD5								32771
#define		VS_RSA_SIGN							9216
#define		VS_RSA_KEYX							41984
#define		VS_3DES								26115
#define		VS_SSL3_SHAMD5						32776	// SSL hash algorithm 

/*
#define		VS_RC2								CALG_RC2
#define		VS_RC4								CALG_RC4
#define		VS_SHA_1							CALG_SHA
#define		VS_MD2								CALG_MD2
#define		VS_MD5								CALG_MD5
#define		VS_RSA_SIGN							CALG_RSA_SIGN
#define		VS_RSA_KEYX							CALG_RSA_KEYX
*/

#define		NUMBER_OF_ALGOS						8
#define		NUMBER_OF_TPM_ALGOS					5

#define		VS_CSP_DEFAULT_BLOCK_LENGTH			64
#define		VS_CSP_DEFAULT_CYPHER_MODES			CRYPT_MODE_CBC
#define		VS_CSP_DEFAULT_INIT_VECTOR			"00000000"	//	these are to be treated as bytes and not chars

#define		VS_CSP_SHA1_LEN						20

#define		RSA_MIN_PAD_LEN						11

#define		VS_MD2_OID							szOID_RSA_MD2
#define		VS_MD5_OID							szOID_RSA_MD5
#define		VS_SHA1_OID							szOID_OIWSEC_sha1

#define		SYMMETRIC_KEY_LENGTH				128
#define		VS_3DES_KEY_LENGTH					192

	//	these will be used in the VSM_ExportKey function
#define		VS_CSP_EXPORT_PUBLIC_KEY			0
#define		VS_CSP_EXPORT_PRIVATE_KEY			1

#define		VS_PTA_CSP							1000
#define		VS_TPM_CSP							2000

#define		VS_PTA_CSP_NAME					"VeriSign Personal Trust Agent (PTA)"
#define		VS_TPM_CSP_NAME					"VeriSign TPM CSP"	//	place holder till
																//	the final name is decided
#define		TPM_CSP_VERSION_MAJOR				01
#define		TPM_CSP_VERSION_MINOR				00
#define		TPM_CSP_VERSION						0x00000100
#define		TPM_CSP_TYPE						PROV_RSA_FULL

#define		VS_USER_ROOT_KEY_REG			"Software\\TSS\\RootKey0"
#define		VS_USER_ROOT_KEY_VALUE			"RootKeyUUID"
#define		VS_USER_ROOT_KEY_PASSWORD		"RootKeyPassword"

#define		VS_TSS_CONTAINERS				"SOFTWARE\\VeriSign, Inc.\\Pta3 TSS\\Keys\\"
#define		VS_CONTAINER_XKEY				"XKEY"
#define		VS_CONTAINER_SKEY				"SKEY"
#define		VS_CONTAINER_X_PUBKEY			"XPubKey"
#define		VS_CONTAINER_S_PUBKEY			"SPubKey"

#define		VS_TPM_CONTAINER_CREATE			1000
#define		VS_TPM_CONTAINER_OPEN			2000

#define		VS_TPM_UUID_ZEROS				"00000000-0000-0000-0000-000000000000"

#endif