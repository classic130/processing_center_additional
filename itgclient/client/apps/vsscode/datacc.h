#ifndef __DATACCESS_
#define __DATACCESS_

enum AccessMode
{
	ACCESS_READ,
	ACCESS_WRITE,
	ACCESS_OVERWRITE,
	ACCESS_READWRITE
};

class CDataAccess
{
public:
	CDataAccess();
	~CDataAccess();

public:
	HRESULT Open(const _bstr_t& i_bstrDocument, const AccessMode i_aMode = ACCESS_READ);
	HRESULT Read(LPBYTE o_pbBytesRead, DWORD* io_dwBytesRead);
	HRESULT Write(const LPBYTE i_pbData, const DWORD i_dwDataLen, LPDWORD o_pdwBytesWritten = NULL);
	HRESULT GetSize(LPDWORD o_pdwSize);
	VOID Close();

private:
	_bstr_t m_bstrProtocol;	// Currently we support 'file:' and 'http:'

	// Handle used when protocol is 'file:'
	HANDLE	m_hFile;	

	// Handles used when protocol is 'http:'
	HANDLE m_hOpen;
	HANDLE m_hConnect;
	HANDLE m_hRequest;
};

#endif // __DATACCESS_