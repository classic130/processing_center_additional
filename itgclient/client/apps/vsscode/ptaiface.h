#ifndef __VS_PTAIFACE_
#define __VS_PTAIFACE_

// This corresponds to the OPENPROF_OPEN_ONLY flag of the PTA
#define		PROF_OPEN				529

// This corresponds to the  flag of the PTA
#define		PROF_OPEN_OR_CREATE		547


// This corresponds to the EXP_DATE_GREATER_THAN flag of the PTA
#define		EXP_DATE_FLAG			0x20

// This corresponds to the PASSWDQUAL_ANYPASSWDOK flag of the PTA
#define		ANYPASSWDOK				0x2000

// Values similar to those required by the PTA, needed when signing transaction
#define		SCRIPT_HASH_MD2					2
#define		SCRIPT_HASH_MD5					3
#define		SCRIPT_HASH_SHA1				4
#define		SCRIPT_HASH_MD2_WITHAUTHATTR	5
#define		SCRIPT_HASH_MD5_WITHAUTHATTR	6
#define		SCRIPT_HASH_SHA1_WITHAUTHATTR	7


#define		CAPI_MODE				1
#define		NON_CAPI_MODE			0

HRESULT InitializePTA(CRegSettings& i_usrSettings, IVSPTA** o_pVSPTA);
HRESULT UnInitializePTA(IVSPTA* i_pVSPTA);

#endif	//	__VS_PTAIFACE_