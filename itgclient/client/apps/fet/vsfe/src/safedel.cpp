// This file implements secure deletion of a file. Secure deletion is needed in case of
// File Encryption because deleting a plaintext file does not cause the disk sectors to be 
// overwritten, so a disk utility can recover the plaintextdata.

#include "stdafx.h"

#include <shlobj.h>

#include "resource.h"
#include "slist.h"
#include "cryptsup.h"

#include "ptav3.h"

#include "util.h"
#include "vspmspP.h"
#include "vspmutil.h"
#include "vspmsp.h"
#include "policysup.h"

extern PolicyVars g_LocalPolicy;
extern DWORD g_dwProgressRange;

/* Securely deletes a file's original name by renaming it several
   times. This works by changing each non-'.' character in the file's
   name to successive alphabetic characters, thus overwriting the
   name 26 times.

   'FileName' (IN)   - file name to overwrite
   'LastName' (OUT)  - overwritten name

*/


VOID OverwriteFileName(PTCHAR FileName, PTCHAR LastFileName)
{
	TCHAR	newName[MAX_PATH];
	PTCHAR	lastSlash;
	DWORD	index;

	strcpy(LastFileName, FileName);
	lastSlash = strrchr(LastFileName, '\\');
	index = lastSlash - LastFileName;

	// Loop through each letter in the English alphabet
	strcpy(newName, FileName);

	for(int i = 0; i < 26; i++) 
	{
		// Replace each non-'.' character with the same letter
		for(int j = index + 1 ; j < lstrlen(FileName); j++) 
			if(FileName[j] != '.')
				newName[j] = (TCHAR) i + 'A';
	
			
		// Got a new name so rename
		if(!MoveFile(LastFileName, newName)) 
		{
			// error
			return;
		}

		lstrcpy(LastFileName, newName);
	}
} // OverwriteFileName()




// This function implements a secure santize of rigid (removable 
// and fixed) disk media as per the Department of Defense clearing 
// and sanitizing standard: DOD 5220.22-M
// The standard states that hard disk media is sanatized by 
// overwriting with a character, then the character's complement,
// and then a random character. 
BOOL SecureOverwrite(HANDLE FileHandle, DWORD Length)
{
	DWORD	bytesWritten, bytesToWrite, totalWritten;
	LONG	seekLength;
	BOOLEAN	status;

	seekLength = (LONG) Length;

	for(int i = 0; i < 3; i++) 
	{
		// Move back to the start of where we're overwriting. This is done bcos 
		// different patterns have to be written on the file
		if(i != 0)
			SetFilePointer(FileHandle, -seekLength, NULL, FILE_CURRENT);
		
		bytesToWrite = Length;
		totalWritten = 0;
		while(totalWritten < Length) 
		{
			bytesToWrite = Length - totalWritten;
			if(bytesToWrite > CLEANBUFSIZE) 
				bytesToWrite = CLEANBUFSIZE;

			status = WriteFile(FileHandle, Buffers[i], bytesToWrite, &bytesWritten, NULL);

			if(!status) 
			{
				LogErrorMessage("SecureOverwrite:WriteFile() failed.", GetLastError());
				return FALSE;
			}

			totalWritten += bytesWritten;
		}
	}

	return TRUE;
}	// SecureOverwrite()



// Performs a secure delete on the specified file.
VOID SecureDelete(PTCHAR FileName) 
{
	HANDLE	hFile;
	ULONGLONG bytesToWrite, bytesWritten;
	ULARGE_INTEGER fileLength;
	TCHAR lastFileName[MAX_PATH], szFmt[MAX_PATH], szMsg[MAX_PATH];
	DWORD FileLengthHi, FileLengthLo, dwErr;

	if(!g_LocalPolicy.bSecureDelete)
	{
		// Do a normal deletion
		DeleteFile(FileName);
		return;
	}
	
	// First, open the file in overwrite mode
	hFile = CreateFile(FileName, GENERIC_WRITE, 
						FILE_SHARE_READ|FILE_SHARE_WRITE,
						NULL, OPEN_EXISTING, FILE_FLAG_WRITE_THROUGH, NULL );

	if( hFile == INVALID_HANDLE_VALUE ) 
	{
		dwErr = GetLastError();
		LoadString(g_hInst, IDS_WRITE_FILE_ERR, szMsg, MAX_PATH);
		wsprintf(szFmt, szMsg, FileName);
		MessageBox(GetFocus(), szFmt, "Safe", MB_OK | MB_ICONERROR);
		wsprintf(szMsg, "SecureDelete:CreateFile() for file \'%s\' failed.", FileName);
		LogErrorMessage(szMsg, dwErr);
		return;
	}

	BY_HANDLE_FILE_INFORMATION fad;
	GetFileInformationByHandle(hFile, &fad);
	FileLengthHi = fad.nFileSizeHigh; 
	FileLengthLo = fad.nFileSizeLow;

	// If the file has a non-zero length, fill it with 0's first in order
	// to preserve is cluster allocation.
	if(FileLengthLo || FileLengthHi) 
	{
		// Seek to the last byte of the file
		FileLengthLo--;
		if(FileLengthLo == (DWORD) -1 && FileLengthHi) 
			FileLengthHi--;

		SetFilePointer(hFile, FileLengthLo, (long *)&FileLengthHi, FILE_BEGIN);

		// Write one zero byte, which causes the file system to fill the entire
		// file's on-disk contents with 0.
		if(!SecureOverwrite( hFile, 1 )) 
		{
			CloseHandle( hFile );
			return;
		}

		HWND hWndBar;
		if(!g_LogOn_Off)
			hWndBar = GetDlgItem(g_hAnimateDlg, IDC_PROGRESS);

		// Now go back to the start of the file and overwrite the rest of the
		// file.
		SetFilePointer( hFile, 0, NULL, FILE_BEGIN );
		fileLength.LowPart = FileLengthLo;
		fileLength.HighPart = FileLengthHi;
		bytesWritten = 0;
		DWORD dwCurrProgressPos = 0;
		while(bytesWritten < fileLength.QuadPart) 
		{
			bytesToWrite = min(fileLength.QuadPart - bytesWritten, CLEANBUFSIZE);

			if(!g_LogOn_Off)
			{
				if(dwCurrProgressPos < g_dwProgressRange)
				{
					for(int i = 0; i < bytesToWrite/MAX_READ_SIZE; i++)
					{
						if(dwCurrProgressPos >= g_dwProgressRange)
							break;

						SendMessage(hWndBar, PBM_STEPIT, 0, 0);
						dwCurrProgressPos++;
					}
				}

				// Even if user presses cancel cannot cancel the operation
				// now as we are in the middle of deletion
				ScanUserInput();
			}

			if(!SecureOverwrite(hFile, (DWORD) bytesToWrite)) 
			{
				CloseHandle( hFile );
				return;
			}

			bytesWritten += bytesToWrite;
		}

		if(!g_LogOn_Off)
		{
			while(dwCurrProgressPos < g_dwProgressRange)
			{
				SendMessage(hWndBar, PBM_STEPIT, 0, 0);
				dwCurrProgressPos++;
			}
		}
	}

	CloseHandle(hFile);
	
	// Rename the file a few times
	OverwriteFileName(FileName, lastFileName);

	// Now we can delete the file
	if(!DeleteFile(lastFileName)) 
	{
		TCHAR szMsg[MAX_PATH];
		dwErr = GetLastError();
		wsprintf(szMsg, "SecureDelete:DeleteFile() for file \'%s\' failed", lastFileName);
		LogErrorMessage(szMsg,  dwErr);
		
		// Rename back to original name so as not to confuse the user
		if(!MoveFile(lastFileName, FileName)) 
		{
			dwErr = GetLastError();
			wsprintf(szMsg, "SecureDelete:MoveFile() for file \'%s\' to \'%s\' failed", lastFileName, FileName);
			LogErrorMessage(szMsg,  dwErr);
			return;
		}

	}
} // SecureDelete()

