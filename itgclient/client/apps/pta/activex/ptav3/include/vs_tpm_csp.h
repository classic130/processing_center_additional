#ifndef	__VS_TPM_CSP_H__
#define	__VS_TPM_CSP_H__


BOOL WINAPI VSTPM_CPAcquireContext
(
	OUT HCRYPTPROV *phProv,
	OUT CHAR *pszIdentity,
	IN DWORD dwFlags,
	IN PVTableProvStruc pVTable
);

#endif