//
// cregcls.h -- registry wrapper class
//
// Copyright 1998 Microsoft Corporation
//
//
//=================================================================

#if _MSC_VER > 1000
#pragma once
#endif

#ifndef _CREGCLS_H_
#define _CREGCLS_H_

#include <Polarity.h>
#include <CHString.h>
#include <chstrarr.h>
#include <chptrarr.h>

#define MAX_VALUE_NAME (1024)
#define NULL_DWORD ((DWORD)0L)
#define MAX_SUBKEY_BUFFERSIZE (MAX_PATH+1)      // Per spec
#define QUOTE ("\"")
#define CSTRING_PTR (1)



class POLARITY CRegistry {
 public:
  CRegistry();	// Constructor
  ~CRegistry();  // Destructor

  // Opens the key and subkey using the desired access mask
  LONG Open( HKEY  hRootKey,	// handle of open key 
            LPCTSTR  lpszSubKey,	// address of name of subkey to open 
            REGSAM  samDesired);	// Access mask

  // Opens the key but forces the enumation of subkeys flag
  //=======================================================
  LONG OpenAndEnumerateSubKeys(HKEY hInRootKey, LPCTSTR lpszSubKey, REGSAM samDesired);
  LONG EnumerateAndGetValues( DWORD & dwIndexOfValue,
							   char *& pValueName,
							   unsigned char *& pValueData);

  void Close(void);
 


  // Information Functions

 // Having a key, but no class name is legal so just return a null string
 // if there has been no class name set
 //======================================================================
  HKEY GethKey(void) { return hKey; }
  
  char* GetClassName(void) { return(ClassName); }
  DWORD GetCurrentSubKeyCount(void) { return(dwcSubKeys); }
  DWORD GetLongestSubKeySize(void) { return(dwcMaxSubKey); }
  DWORD GetLongestClassStringSize(void) { return (dwcMaxClass); }
  DWORD GetValueCount(void) { return(dwcValues); }
  DWORD GetLongestValueName(void) { return(dwcMaxValueName); }
  DWORD GetLongestValueData(void) { return(dwcMaxValueData); }

  DWORD GetCurrentKeyValue(LPCSTR pValueName, CHString &DestValue);
  DWORD GetCurrentKeyValue(LPCSTR pValueName, DWORD &DestValue);
  DWORD GetCurrentKeyValue(LPCSTR pValueName, CHStringArray &DestValue);

  DWORD SetCurrentKeyValue(LPCSTR pValueName, CHString &DestValue);
  DWORD SetCurrentKeyValue(LPCSTR pValueName, DWORD &DestValue);
  DWORD SetCurrentKeyValue(LPCSTR pValueName, CHStringArray &DestValue);

  DWORD GetCurrentBinaryKeyValue(LPCSTR pValueName, CHString &chsDest );
  DWORD GetCurrentBinaryKeyValue(LPCSTR pValueName, LPBYTE pbDest) ;
  DWORD GetCurrentBinaryKeyValue(LPCSTR pValueName, LPBYTE pbDest, LPDWORD pSizeOfDestValue ) ;

  DWORD GetCurrentKeyValue(HKEY UseKey, LPCSTR pValueName, CHString &DestValue);
  DWORD GetCurrentKeyValue(HKEY UseKey, LPCSTR pValueName, DWORD &DestValue);
  DWORD GetCurrentKeyValue(HKEY UseKey, LPCSTR pValueName, CHStringArray &DestValue);

  DWORD SetCurrentKeyValue(HKEY UseKey, LPCSTR pValueName, CHString &DestValue);
  DWORD SetCurrentKeyValue(HKEY UseKey, LPCSTR pValueName, DWORD &DestValue);
  DWORD SetCurrentKeyValue(HKEY UseKey, LPCSTR pValueName, CHStringArray &DestValue);

  DWORD DeleteCurrentKeyValue (LPCSTR pValueName);
  DWORD DeleteCurrentKeyValue (HKEY UseKey, LPCSTR pValueName);
 
  // Subkey functions
  //=================
  void  RewindSubKeys(void);
  DWORD GetCurrentSubKeyName(CHString &DestSubKeyName);

  DWORD GetCurrentSubKeyValue(LPCSTR pValueName, void* pDestValue,LPDWORD pSizeOfDestValue);
  DWORD GetCurrentSubKeyValue(LPCSTR pValueName, CHString &DestValue);
  DWORD GetCurrentSubKeyValue(LPCSTR pValueName, DWORD &DestValue);

  
  DWORD NextSubKey(void); 
  DWORD GetCurrentSubKeyPath(CHString &DestSubKeyPath); 
  LONG  OpenLocalMachineKeyAndReadValue( LPCTSTR lpszSubKey, 
                                  LPCSTR pValueName, 
                                  CHString &DestValue );
 private:

 // Private functions
 //==================

 // Set the member variables to their default state
 //================================================
 void SetDefaultValues(void);

 // Open and close the subkey
 // =========================
 DWORD OpenSubKey(void);
 void  CloseSubKey(void);

 // Given a good key gets the value
 // ===============================
 DWORD GetCurrentRawKeyValue(HKEY UseKey, LPCSTR pValueName, void* pDestValue,LPDWORD pValueType, LPDWORD pSizeOfDestValue);
 DWORD GetCurrentRawSubKeyValue(LPCSTR pValueName, void* pDestValue,LPDWORD pValueType, LPDWORD pSizeOfDestValue);


 // In the event the caller is REUSING this instance,
 // close the existing key and reset values to the default
 // in preparation to REOPEN this instance
 //=======================================================
 void PrepareToReOpen(void);


 // Private data
 //=============
 HKEY hRootKey;             // Current root key for cla
 HKEY hKey;				   // Current active key
 HKEY hSubKey;             // Current active subkey
  
 CHString RootKeyPath;      // Current path to root assigned by open
 
 DWORD CurrentSubKeyIndex; // Current subkey being indexed
 // Information about this class
 //=============================
 CHAR ClassName[MAX_PATH];       // Buffer for class name.
 DWORD dwcClassLen;              // Length of class string.
 DWORD dwcSubKeys;               // Number of sub keys.
 DWORD dwcMaxSubKey;             // Longest sub key size.
 DWORD dwcMaxClass;              // Longest class string.
 DWORD dwcValues;                // Number of values for this key.
 DWORD dwcMaxValueName;          // Longest Value name.
 DWORD dwcMaxValueData;          // Longest Value data.
 DWORD dwcSecDesc;               // Security descriptor.
 FILETIME ftLastWriteTime;       // Last write time.
}; 

//*********************************************************************
//
//   CLASS:         CRegistrySearch
//
//   Description:   This class uses the CRegistry Class to search
//                  through the registry to build a list of keys
//                  for the requested value, or requested full key
//                  name, or requested partial key name.  This class
//                  allocates CHString objects and puts them in the
//                  users CHPtrArray.  The user is responsible for
//                  deleting the memory allocated, the FreeSearchList
//                  function can accomplish this, or the user must
//                  remember to delete every object in the array
//                  before deallocating the array.
//
//
//=====================================================================
//
//  Note:  Private functions are documented in the .CPP file
//
//=====================================================================
//
//  Public functions
//
//=====================================================================
//
//  BOOL SearchAndBuildList( CHString chsRootKey, 
//                           CHPtrArray & cpaList,
//                           CHString chsSearchString,
//                           CHString chsValueString,
//                           int nSearchType );
//
//  Parameters:
//      chsRootKey          - The root key to start the search from.
//                            Note:  At this point in time, we just
//                            search thru HKEY_LOCAL_MACHINE, this
//                            can be changed when needed. 
//      cpaList             - The reference to the CHPtrArray to put
//                            the list of keys that matched the search
//                            criteria.
//      chsSearchString     - The string to search for
//      chsValueString      - The value to open and see if it matches what is 
//                            chsSearchString
//      nSearchType         - The type of search, the following are
//                            supported:
//                            KEY_FULL_MATCH_SEARCH      
//                               Only keys that match the chsSearchString
//                            KEY_PARTIAL_MATCH_SEARCH   
//                               Keys that have chsSearchString anywhere in them
//                            VALUE_SEARCH               
//                               Values that match chsSearchString
//*********************************************************************
#define KEY_FULL_MATCH_SEARCH      1
#define KEY_PARTIAL_MATCH_SEARCH   2
#define VALUE_SEARCH               3

class POLARITY CRegistrySearch{

    private:
        void CheckAndAddToList( CRegistry * pReg, 
                                CHString chsSubKey, 
                                CHString chsFullKey,
                                CHPtrArray & chpaList,
                                CHString chsSearchString,
                                CHString chsValueString,
                                int nSearchType);
        int         m_nSearchType;
        CHString     m_chsSearchString;
        CHPtrArray   m_cpaList;

    
    public:
        CRegistrySearch();
        ~CRegistrySearch();
        BOOL SearchAndBuildList( CHString chsRootKey, 
                                 CHPtrArray & cpaList,
                                 CHString chsSearchString,
                                 CHString chsValueString,
                                 int nSearchType,HKEY hkDefault = HKEY_LOCAL_MACHINE );
        BOOL FreeSearchList( int nType, CHPtrArray & cpaList );

		BOOL LocateKeyByNameOrValueName(HKEY		hKeyParent,
										LPCTSTR		pszKeyName,
										LPCTSTR		pszSubKeyName,
										LPCTSTR*	ppszValueNames,
										DWORD		dwNumValueNames,
										CHString&	strFoundKeyName,
										CHString&	strFoundKeyPath  );

};

#endif