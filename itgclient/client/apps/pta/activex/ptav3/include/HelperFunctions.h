#ifndef		__VS_CSP_HELPER_FUNCTIONS__
#define		__VS_CSP_HELPER_FUNCTIONS__

#include "cspincludes.h"
#include "cspstructures.h"
#include "vs_csp.h"
//#include "globals.h"


/*
HRESULT		GetLastNode
(
	CSP_State**						o_ppCS
);
*/

HRESULT		CheckProv
(
	CSP_State*						i_pCSP
);

HRESULT		AddHashNode
(
	CSP_State*						i_pCSP,
	CSP_HashParam*					i_pHash
);

HRESULT		CheckHashNode
(
	const	CSP_State*				i_cpCSP,
	const	CSP_HashParam*			i_cpHash
);

HRESULT		DeleteHashNode
(
	CSP_State*						i_cpCSP,
	CSP_HashParam*					i_cpHash
);

void	DeleteHashChain
(
	CSP_State*						i_pCSP
);

HRESULT		AddKeyNode
(
	CSP_State*						i_pCSP,
	CSP_KeyParam*					i_pKey
);

HRESULT		CheckKeyNode
(
	const	CSP_State*				i_cpCSP,
	const	CSP_KeyParam*			i_cpKey
);

HRESULT		DeleteKeyNode
(
	CSP_State*						i_pCSP,
	CSP_KeyParam*					i_pKey
);

void	DeleteKeyChain
(
	CSP_State*						i_pCSP
);

HRESULT		CheckIfKeyExists
(
	CSP_State*			i_pCSP,
	CVirtualSmartCard*	i_pVSmartCard,
	const DWORD			i_cdwAlgID,
	CSP_Key_Container*	o_pstructContainer
);

HRESULT		CheckIfContainerExists
(
	CSP_State*			i_pCSP,
	CVirtualSmartCard*	i_pVSmartCard
);

HRESULT		ExportSessionKey
(
	CSP_State*						i_cpCSP,
	const CSP_KeyParam*				i_cpKey,
	CSP_KeyParam*					i_pPubKey,
	BYTE**							o_ppbyteKey,
	DWORD*							o_pdwKeyLen
);

HRESULT		ExportPublicKey
(
	CSP_State*						i_cpCSP,
	const CSP_KeyParam*				i_cpKey,
	BYTE**							o_ppbyteKey,
	DWORD*							o_pdwKeyLen
);

HRESULT		ImportSessionKey
(
	CSP_State*						i_cpCSP,
	CSP_KeyParam*					i_pPubKey,
	const BYTE*						i_cpbyteKey,
	const DWORD						i_cdwKeyLen,
	CSP_KeyParam**					o_ppKey
);

HRESULT		ImportPublicKey
(
	CSP_State*						i_cpCSP,
	const BYTE*						i_cpbyteKey,
	const DWORD						i_cdwKeyLen,
	const DWORD						i_cdwFlags,
	CSP_KeyParam**					o_ppKey
);

HRESULT		GetVSC
(
	CSP_State*						i_pCSP,
	CVirtualSmartCard**				o_pVSC
);

#endif