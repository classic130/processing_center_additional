#ifndef SAFEDEL_H
#define SAFEDEL_H

VOID OverwriteFileName(PTCHAR FileName, PTCHAR LastFileName);
BOOL SecureOverwrite(HANDLE FileHandle, DWORD Length);
VOID SecureDelete(PTCHAR FileName);

#endif
