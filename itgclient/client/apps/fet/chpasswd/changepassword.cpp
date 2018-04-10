// changepassword.cpp : Defines the entry point for the console application.
//



#include "stdafx.h"

#ifndef _WIN32_WINNT
#define _WIN32_WINNT  0x0400
#endif

#include <stdio.h>
#include <windows.h>
#include <wincrypt.h>
#include "cryptsup.h"

#define MAX_READ_SIZE 1024

BOOL DecryptFile(LPCTSTR);

int main(int argc, char* argv[])
{
	if(argc < 3)
		printf("Usage : chpasswd inputtokenfile outputtokenfile");

	DWORD dwErr;
	// Decrypt the password file
	if(DecryptFile(argv[1]))
	{
		// Get signature from "decrypted file", verify hash, get hash,
		// Sign hash using public key
		HANDLE hReadFile = CreateFile("passwddecr", GENERIC_READ, 0, NULL, 
								OPEN_EXISTING, FILE_ATTRIBUTE_ARCHIVE, NULL);
		if(hReadFile == INVALID_HANDLE_VALUE)
		{
			dwErr = GetLastError();
			printf("Could not open password file %s, error : %d", 
				   "passwddecr", dwErr);
			return FALSE;
		}

		// 1st DWORD contains the length of hash
		DWORD dwBytesRead, dwHashLen, dwFileSize;
		dwFileSize = GetFileSize(hReadFile,  NULL);

		ReadFile(hReadFile, (LPVOID)&dwHashLen, sizeof(DWORD), &dwBytesRead,
				 NULL);

		if(dwHashLen > dwFileSize)
			printf("Invalid password file, hash length is greater than file size");
		else
		{
			PBYTE pbHash = (PBYTE)malloc(dwHashLen);

			ReadFile(hReadFile, (LPVOID)pbHash, dwHashLen, &dwBytesRead,
					 NULL);

			DWORD dwSigLen = dwFileSize - sizeof(DWORD) - dwHashLen;

			PBYTE pbSig = (PBYTE)malloc(dwSigLen);

			ReadFile(hReadFile, (LPVOID)pbSig, dwSigLen, &dwBytesRead,
					 NULL);

			PBYTE pbEncodedBlob = NULL;
			DWORD dwEncodedBlob;
			if(!VerifySignatureAndEncryptHash(pbHash, dwHashLen, pbSig, dwSigLen,
						&pbEncodedBlob, &dwEncodedBlob))
				printf("Signature verification failed");
			else
			{
				// Write the encrypted hash to a file
				HANDLE hWriteFile = CreateFile(argv[2], GENERIC_WRITE, 0, NULL, 
										CREATE_ALWAYS, FILE_ATTRIBUTE_ARCHIVE, NULL);
				if(hWriteFile == INVALID_HANDLE_VALUE)
				{
					dwErr = GetLastError();
					printf("Could not create output file %s, error : %d",
						   argv[2], dwErr);
				}
				else
				{
					DWORD dwBytesWritten;
					WriteFile(hWriteFile, pbEncodedBlob, dwEncodedBlob, &dwBytesWritten, NULL);
					CloseHandle(hWriteFile);
				}

			}

			free(pbEncodedBlob);
			free(pbSig);
			free(pbHash);
		}

		CloseHandle(hReadFile);

	}

	DeleteFile("passwddecr");

	return 0;
}



BOOL DecryptFile(LPCTSTR lpPasswdFile)
{
	if(!lpPasswdFile)
		return FALSE;

	DWORD dwErr;
	HANDLE hReadFile = CreateFile(lpPasswdFile, GENERIC_READ, 0, NULL, 
							OPEN_EXISTING, FILE_ATTRIBUTE_ARCHIVE, NULL);
	if(hReadFile == INVALID_HANDLE_VALUE)
	{
		dwErr = GetLastError();
		printf("Could not open password file %s, error : %d", 
			   lpPasswdFile, dwErr);
		return FALSE;
	}

	TCHAR szDecrFile[MAX_PATH] = {"passwddecr"};
	
	HANDLE hWriteFile = CreateFile(szDecrFile, GENERIC_WRITE, 0, NULL, 
							CREATE_ALWAYS, FILE_ATTRIBUTE_ARCHIVE, NULL);
	if(hWriteFile == INVALID_HANDLE_VALUE)
	{
		dwErr = GetLastError();
		printf("Could not create temporary file %s because user may not have write permissions, error : %d",
			   szDecrFile, dwErr);
		CloseHandle(hReadFile);
		return FALSE;
	}

	CMSG_STREAM_INFO StreamInfo;
	memset(&StreamInfo, 0, sizeof(CMSG_STREAM_INFO));

	StreamInfo.cbContent		= GetFileSize(hReadFile, NULL);
	StreamInfo.pfnStreamOutput	= StreamOutputCallback;
	StreamInfo.pvArg			= hWriteFile;

	DWORD dwBytesRead;
	ULONG ulCryptoError, ulDecryptContext;
	TCHAR cReadBuf[MAX_READ_SIZE];
	BOOL bSuccess = FALSE;

	if(DecryptStart(NULL, &ulDecryptContext, &StreamInfo, &ulCryptoError) == S_OK)
	{
		while(ReadFile(hReadFile, cReadBuf, MAX_READ_SIZE, &dwBytesRead, NULL))
		{
			if(dwBytesRead == MAX_READ_SIZE)
			{
				if(DecryptUpdate(ulDecryptContext, (BYTE *)cReadBuf, 
								 dwBytesRead, &ulCryptoError) != S_OK)
					break;
			}
			else
			{
				if(DecryptEnd(ulDecryptContext, (BYTE *)cReadBuf, dwBytesRead,
							  &ulCryptoError) == S_OK)
					bSuccess = TRUE;

				break;
			}
		}
	}

	if(!bSuccess)					// This handle was not closed by the
	{								// stream callback
		CloseHandle(hWriteFile);	
		return FALSE;
	}

	CloseHandle(hReadFile);

	return TRUE;
}