
//=============================================================================
//  userenv.h   -   Header file for user environment API.
//                  User Profiles, environment variables, and policy.
//
//  Copyright (c) Microsoft Corporation 1995-1998
//  All rights reserved
//
//=============================================================================


#ifndef _INC_USERENV
#define _INC_USERENV

//
// Define API decoration for direct importing of DLL references.
//

#if !defined(_USERENV_)
#define USERENVAPI DECLSPEC_IMPORT
#else
#define USERENVAPI
#endif


#ifdef __cplusplus
extern "C" {
#endif

//=============================================================================
//
// LoadUserProfile
//
// Loads the specified user's profile.
//
// Most applications should not need to use this function.  It's used primarily
// when a user has logged onto the system or a service starts in a named
// user account.
//
// hToken        - Token for the user, returned from LogonUser()
// lpProfileInfo - Address of a PROFILEINFO structure
//
// Returns:  TRUE if successful
//           FALSE if not.  Call GetLastError() for more details
//
// Note:  The caller of this function must have admin privileges on the machine.
//
//        Upon successful return, the hProfile member of the PROFILEINFO
//        structure is a registry key handle opened to the root
//        of the user's hive.  It has been opened with full access. If
//        you need to read or write to the user's registry file, use
//        this key instead of HKEY_CURRENT_USER.  Do not close this
//        handle.  Instead pass it to UnloadUserProfile to close
//        the handle.
//
//=============================================================================

//
// Flags that can be set in the dwFlags field
//

#define PI_NOUI         0x00000001      // Prevents displaying of messages
#define PI_APPLYPOLICY  0x00000002      // Apply NT4 style policy

typedef struct _PROFILEINFOA {
    DWORD       dwSize;                 // Set to sizeof(PROFILEINFO) before calling
    DWORD       dwFlags;                // See flags above
    LPSTR       lpUserName;             // User name (required)
    LPSTR       lpProfilePath;          // Roaming profile path (optional, can be NULL)
    LPSTR       lpDefaultPath;          // Default user profile path (optional, can be NULL)
    LPSTR       lpServerName;           // Validating domain controller name in netbios format (optional, can be NULL but group NT4 style policy won't be applied)
    LPSTR       lpPolicyPath;           // Path to the NT4 style policy file (optional, can be NULL)
    HANDLE      hProfile;               // Filled in by the function.  Registry key handle open to the root.
} PROFILEINFOA, FAR * LPPROFILEINFOA;
typedef struct _PROFILEINFOW {
    DWORD       dwSize;                 // Set to sizeof(PROFILEINFO) before calling
    DWORD       dwFlags;                // See flags above
    LPWSTR      lpUserName;             // User name (required)
    LPWSTR      lpProfilePath;          // Roaming profile path (optional, can be NULL)
    LPWSTR      lpDefaultPath;          // Default user profile path (optional, can be NULL)
    LPWSTR      lpServerName;           // Validating domain controller name in netbios format (optional, can be NULL but group NT4 style policy won't be applied)
    LPWSTR      lpPolicyPath;           // Path to the NT4 style policy file (optional, can be NULL)
    HANDLE      hProfile;               // Filled in by the function.  Registry key handle open to the root.
} PROFILEINFOW, FAR * LPPROFILEINFOW;
#ifdef UNICODE
typedef PROFILEINFOW PROFILEINFO;
typedef LPPROFILEINFOW LPPROFILEINFO;
#else
typedef PROFILEINFOA PROFILEINFO;
typedef LPPROFILEINFOA LPPROFILEINFO;
#endif // UNICODE



USERENVAPI
BOOL
WINAPI
LoadUserProfileA(
    IN HANDLE hToken,
    IN OUT LPPROFILEINFOA lpProfileInfo);
USERENVAPI
BOOL
WINAPI
LoadUserProfileW(
    IN HANDLE hToken,
    IN OUT LPPROFILEINFOW lpProfileInfo);
#ifdef UNICODE
#define LoadUserProfile  LoadUserProfileW
#else
#define LoadUserProfile  LoadUserProfileA
#endif // !UNICODE


//=============================================================================
//
// UnloadUserProfile
//
// Unloads a user's profile that was loaded by LoadUserProfile()
//
// hToken        -  Token for the user, returned from LogonUser()
// hProfile      -  hProfile member of the PROFILEINFO structure
//
// Returns:  TRUE if successful
//           FALSE if not.  Call GetLastError() for more details
//
// Note:     The caller of this function must have admin privileges on the machine.
//
//=============================================================================

USERENVAPI
BOOL
WINAPI
UnloadUserProfile(
    IN HANDLE hToken,
    IN HANDLE hProfile);


//=============================================================================
//
// GetProfilesDirectory
//
// Returns the path to the root of where all user profiles are stored.
//
// lpProfilesDir  -  Receives the path
// lpcchSize      -  Size of lpProfilesDir
//
// Returns:  TRUE if successful
//           FALSE if not.  Call GetLastError() for more details
//
// Note:     If lpProfilesDir is not large enough, the function will fail,
//           and lpcchSize will contain the necessary buffer size.
//
// Example return value: C:\Winnt\Profiles
//
//=============================================================================

USERENVAPI
BOOL
WINAPI
GetProfilesDirectoryA(
    OUT LPSTR lpProfilesDir,
    IN OUT LPDWORD lpcchSize);
USERENVAPI
BOOL
WINAPI
GetProfilesDirectoryW(
    OUT LPWSTR lpProfilesDir,
    IN OUT LPDWORD lpcchSize);
#ifdef UNICODE
#define GetProfilesDirectory  GetProfilesDirectoryW
#else
#define GetProfilesDirectory  GetProfilesDirectoryA
#endif // !UNICODE


//=============================================================================
//
// GetDefaultUserProfilesDirectory
//
// Returns the path to the root of the default user profile
//
// lpProfileDir   -  Receives the path
// lpcchSize      -  Size of lpProfileDir
//
// Returns:  TRUE if successful
//           FALSE if not.  Call GetLastError() for more details
//
// Note:     If lpProfileDir is not large enough, the function will fail,
//           and lpcchSize will contain the necessary buffer size.
//
// Example return value: C:\Winnt\Profiles\Default User
//
//=============================================================================

USERENVAPI
BOOL
WINAPI
GetDefaultUserProfileDirectoryA(
    IN LPSTR lpProfileDir,
    IN OUT LPDWORD lpcchSize);
USERENVAPI
BOOL
WINAPI
GetDefaultUserProfileDirectoryW(
    IN LPWSTR lpProfileDir,
    IN OUT LPDWORD lpcchSize);
#ifdef UNICODE
#define GetDefaultUserProfileDirectory  GetDefaultUserProfileDirectoryW
#else
#define GetDefaultUserProfileDirectory  GetDefaultUserProfileDirectoryA
#endif // !UNICODE


//=============================================================================
//
// GetAllUsersProfilesDirectory
//
// Returns the path to the root of the All Users profile
//
// lpProfileDir   -  Receives the path
// lpcchSize      -  Size of lpProfileDir
//
// Returns:  TRUE if successful
//           FALSE if not.  Call GetLastError() for more details
//
// Note:     If lpProfileDir is not large enough, the function will fail,
//           and lpcchSize will contain the necessary buffer size.
//
// Example return value: C:\Winnt\Profiles\All Users
//
//=============================================================================

USERENVAPI
BOOL
WINAPI
GetAllUsersProfileDirectoryA(
    IN LPSTR lpProfileDir,
    IN OUT LPDWORD lpcchSize);
USERENVAPI
BOOL
WINAPI
GetAllUsersProfileDirectoryW(
    IN LPWSTR lpProfileDir,
    IN OUT LPDWORD lpcchSize);
#ifdef UNICODE
#define GetAllUsersProfileDirectory  GetAllUsersProfileDirectoryW
#else
#define GetAllUsersProfileDirectory  GetAllUsersProfileDirectoryA
#endif // !UNICODE


//=============================================================================
//
// GetUserProfileDirectory
//
// Returns the path to the root of the requested user's profile
//
// hToken         -  User's token returned from LogonUser()
// lpProfileDir   -  Receives the path
// lpcchSize      -  Size of lpProfileDir
//
// Returns:  TRUE if successful
//           FALSE if not.  Call GetLastError() for more details
//
// Note:     If lpProfileDir is not large enough, the function will fail,
//           and lpcchSize will contain the necessary buffer size.
//
// Example return value: C:\Winnt\Profiles\Joe
//
//=============================================================================

USERENVAPI
BOOL
WINAPI
GetUserProfileDirectoryA(
    IN HANDLE  hToken,
    OUT LPSTR lpProfileDir,
    IN OUT LPDWORD lpcchSize);
USERENVAPI
BOOL
WINAPI
GetUserProfileDirectoryW(
    IN HANDLE  hToken,
    OUT LPWSTR lpProfileDir,
    IN OUT LPDWORD lpcchSize);
#ifdef UNICODE
#define GetUserProfileDirectory  GetUserProfileDirectoryW
#else
#define GetUserProfileDirectory  GetUserProfileDirectoryA
#endif // !UNICODE


//=============================================================================
//
// CreateEnvironmentBlock
//
// Returns the environment variables for the specified user.  This block
// can then be passed to CreateProcessAsUser().
//
// lpEnvironment  -  Receives a pointer to the new environment block
// hToken         -  User's token returned from LogonUser() (optional, can be NULL)
// bInherit       -  Inherit from the current process's environment block
//                   or start from a clean state.
//
// Returns:  TRUE if successful
//           FALSE if not.  Call GetLastError() for more details
//
// Note:     If hToken is NULL, the returned environment block will contain
//           system variables only.
//
//           Call DestroyEnvironmentBlock to free the buffer when finished.
//
//           If this block is passed to CreateProcessAsUser, the
//           CREATE_UNICODE_ENVIRONMENT flag must also be set.
//
//=============================================================================

USERENVAPI
BOOL
WINAPI
CreateEnvironmentBlock(
    OUT LPVOID *lpEnvironment,
    IN HANDLE  hToken,
    IN BOOL    bInherit);


//=============================================================================
//
// DestroyEnvironmentBlock
//
// Frees environment variables created by CreateEnvironmentBlock
//
// lpEnvironment  -  A pointer to the environment block
//
// Returns:  TRUE if successful
//           FALSE if not.  Call GetLastError() for more details
//
//=============================================================================

USERENVAPI
BOOL
WINAPI
DestroyEnvironmentBlock(
    IN LPVOID  lpEnvironment);


//=============================================================================
//
// ExpandEnvironmentStringsForUser
//
// Expands the source string using the environment block for the
// specified user.  If hToken is null, the system environment block
// will be used (no user environment variables).
//
// hToken         -  User's token returned from LogonUser() (optional, can be NULL)
// lpSrc          -  Pointer to the string with environment variables
// lpDest         -  Buffer that receives the expanded string
// dwSize         -  Size of lpDest in characters (max chars)
//
// Returns:  TRUE if successful
//           FALSE if not.  Call GetLastError() for more details
//
// Note:     If the user profile for hToken is not loaded, this api will fail.
//
//=============================================================================

USERENVAPI
BOOL
WINAPI
ExpandEnvironmentStringsForUserA(
    IN HANDLE hToken,
    IN LPCSTR lpSrc,
    OUT LPSTR lpDest,
    IN DWORD dwSize);
USERENVAPI
BOOL
WINAPI
ExpandEnvironmentStringsForUserW(
    IN HANDLE hToken,
    IN LPCWSTR lpSrc,
    OUT LPWSTR lpDest,
    IN DWORD dwSize);
#ifdef UNICODE
#define ExpandEnvironmentStringsForUser  ExpandEnvironmentStringsForUserW
#else
#define ExpandEnvironmentStringsForUser  ExpandEnvironmentStringsForUserA
#endif // !UNICODE


//=============================================================================
//
// RefreshPolicy()
//
// Causes group policy to be applied immediately on the client machine
//
// bMachine  -  Refresh machine or user policy
//
// Returns:  TRUE if successful
//           FALSE if not.  Call GetLastError() for more details
//
//=============================================================================

USERENVAPI
BOOL
WINAPI
RefreshPolicy(
    IN BOOL bMachine);


//=============================================================================
//
// EnterCriticalPolicySection
//
// Pauses the background application of group policy to allow safe
// reading of the registry.  Applications that need to read multiple
// policy entries and ensure that the values are not changed while reading
// them should use this function.
//
// The maximum amount of time an application can hold a critical section
// is 10 minutes.  After 10 minutes, policy can be applied again.
//
// bMachine -  Pause machine or user policy
//
// Returns:  Handle if successful
//           NULL if not.  Call GetLastError() for more details
//
// Note:  The handle returned should be passed to LeaveCriticalPolicySection
// when finished.  Do not close this handle, LeaveCriticalPolicySection
// will do that.
//
//=============================================================================

USERENVAPI
HANDLE
WINAPI
EnterCriticalPolicySection(
    IN BOOL bMachine);


//=============================================================================
//
// LeaveCriticalPolicySection
//
// Resumes the background application of group policy.  See
// EnterCriticalPolicySection for more details.
//
// hSection - Handle returned from EnterCriticalPolicySection
//
// Returns:  TRUE if successful
//           FALSE if not.  Call GetLastError() for more details
//
// Note:  This function will close the handle.
//
//=============================================================================

USERENVAPI
BOOL
WINAPI
LeaveCriticalPolicySection(
    IN HANDLE hSection);


//=============================================================================
//
// GPOptions flags
//
// These are the flags found in the GPOptions property of a DS object
//
// For a given DS object (Site, Domain, OU), the GPOptions property
// contains options that effect all the GPOs link to this SDOU.
//
// This is a DWORD type
//
//=============================================================================

#define GPC_BLOCK_POLICY        0x00000001  // Block all non-forced policy from above


//=============================================================================
//
// GPLink flags
//
// These are the flags found on the GPLink property of a DS object after
// the GPO path.
//
// For a given DS object (Site, Domain, OU), the GPLink property will
// be in this text format
//
// [LDAP://CN={E615A0E3-C4F1-11D1-A3A7-00AA00615092},CN=Policies,CN=System,DC=ntdev,DC=Microsoft,DC=Com;1]
//
// The GUID is the GPO name, and the number following the LDAP path are the options
// for that link from this DS object.  Note, there can be multiple GPOs
// each in their own square brackets in a prioritized list.
//
//=============================================================================

//
// Options for a GPO link
//

#define GPO_FLAG_DISABLE        0x00000001  // This GPO is disabled
#define GPO_FLAG_FORCE          0x00000002  // Don't override the settings in
                                            // this GPO with settings from
                                            // a GPO below it.


//=============================================================================
//
// GetGPOList
//
//
// Queries for the list of Group Policy Objects for the specified
// user or machine.  This function will return a link list
// of Group Policy Objects.  Call FreeGPOList to free the list.
//
// Note, most applications will not need to call this function.
// This will primarily be used by services acting on behalf of
// another user or machine.  The caller of this function will
// need to look in each GPO for their specific policy
//
// This function can be called two different ways.  Either the hToken for
// a user or machine can be supplied and the correct name and domain
// controller name will be generated, or hToken is NULL and the caller
// must supply the name and the domain controller name.
//
// Calling this function with an hToken ensures the list of Group Policy
// Objects is correct for the user or machine since security access checking
// can be perfomed.  If hToken is not supplied, the security of the caller
// is used instead which means that list may or may not be 100% correct
// for the intended user / machine.  However, this is the fastest way
// to call this function.
//
// hToken           - User or machine token, if NULL, lpName and lpDCName must be supplied
// lpName           - User or machine name in DN format, if hToken is supplied, this must be NULL
// lpDCName         - Domain controller name, if hToken is supplied, this must be NULL
// dwFlags          - Flags field.  See flags definition below
// pGPOList         - Address of a pointer which receives the link list of GPOs
//
//
// Returns:  TRUE if successful
//           FALSE if not.  Use GetLastError() for more details.
//
// Examples:
//
// Here's how this function will typically be called for
// looking up the list of GPOs for a user:
//
//      LPGROUP_POLICY_OBJECT  pGPOList
//
//      if (GetGPOList (hToken, NULL, NULL, 0, &pGPOList))
//      {
//          // do processing here...
//          FreeGPOList (pGPOList)
//      }
//
//
// Here's how this function will typically be called for
// looking up the list of GPOs for a machine:
//
//      LPGROUP_POLICY_OBJECT  pGPOList
//
//      if (GetGPOList (NULL, lpMachineName, lpDCName, 0, &pGPOList))
//      {
//          // do processing here...
//          FreeGPOList (pGPOList)
//      }
//
//=============================================================================

//
// Each Group Policy Object is associated (linked) with a site, domain,
// organizational unit, or machine.
//

typedef enum _GPO_LINK {
    GPLinkUnknown = 0,                     // No link information available
    GPLinkMachine,                         // GPO linked to a machine (local or remote)
    GPLinkSite,                            // GPO linked to a site
    GPLinkDomain,                          // GPO linked to a domain
    GPLinkOrganizationalUnit               // GPO linked to a organizational unit
} GPO_LINK, *PGPO_LINK;

typedef struct _GROUP_POLICY_OBJECTA {
    DWORD       dwOptions;                  // See GPLink option flags above
    DWORD       dwVersion;                  // Revision number of the GPO
    LPSTR       lpDSPath;                   // Path to the Active Directory portion of the GPO
    LPSTR       lpFileSysPath;              // Path to the file system portion of the GPO
    LPSTR       lpDisplayName;              // Friendly display name
    CHAR        szGPOName[50];              // Unique name
    GPO_LINK    GPOLink;                    // Link information
    LPARAM      lParam;                     // Free space for the caller to store GPO specific information
    struct _GROUP_POLICY_OBJECTA * pNext;   // Next GPO in the list
    struct _GROUP_POLICY_OBJECTA * pPrev;   // Previous GPO in the list
} GROUP_POLICY_OBJECTA, *PGROUP_POLICY_OBJECTA;
typedef struct _GROUP_POLICY_OBJECTW {
    DWORD       dwOptions;                  // See GPLink option flags above
    DWORD       dwVersion;                  // Revision number of the GPO
    LPWSTR      lpDSPath;                   // Path to the Active Directory portion of the GPO
    LPWSTR      lpFileSysPath;              // Path to the file system portion of the GPO
    LPWSTR      lpDisplayName;              // Friendly display name
    WCHAR       szGPOName[50];              // Unique name
    GPO_LINK    GPOLink;                    // Link information
    LPARAM      lParam;                     // Free space for the caller to store GPO specific information
    struct _GROUP_POLICY_OBJECTW * pNext;   // Next GPO in the list
    struct _GROUP_POLICY_OBJECTW * pPrev;   // Previous GPO in the list
} GROUP_POLICY_OBJECTW, *PGROUP_POLICY_OBJECTW;
#ifdef UNICODE
typedef GROUP_POLICY_OBJECTW GROUP_POLICY_OBJECT;
typedef PGROUP_POLICY_OBJECTW PGROUP_POLICY_OBJECT;
#else
typedef GROUP_POLICY_OBJECTA GROUP_POLICY_OBJECT;
typedef PGROUP_POLICY_OBJECTA PGROUP_POLICY_OBJECT;
#endif // UNICODE


//
// dwFlags for GetGPOList()
//

#define GPO_LIST_FLAG_SITEONLY  0x00000001  // Return site policy information only


USERENVAPI
BOOL
WINAPI
GetGPOListA (
    IN HANDLE hToken,
    IN LPCSTR lpName,
    IN LPCSTR lpDCName,
    IN DWORD dwFlags,
    OUT PGROUP_POLICY_OBJECTA *pGPOList);
USERENVAPI
BOOL
WINAPI
GetGPOListW (
    IN HANDLE hToken,
    IN LPCWSTR lpName,
    IN LPCWSTR lpDCName,
    IN DWORD dwFlags,
    OUT PGROUP_POLICY_OBJECTW *pGPOList);
#ifdef UNICODE
#define GetGPOList  GetGPOListW
#else
#define GetGPOList  GetGPOListA
#endif // !UNICODE


//=============================================================================
//
// FreeGPOList
//
//
// Frees the link list returned from GetGPOList
//
// pGPOList - Pointer to the link list of GPOs
//
//
// Returns:  TRUE if successful
//           FALSE if not
//
//=============================================================================

USERENVAPI
BOOL
WINAPI
FreeGPOListA (
    IN PGROUP_POLICY_OBJECTA pGPOList);
USERENVAPI
BOOL
WINAPI
FreeGPOListW (
    IN PGROUP_POLICY_OBJECTW pGPOList);
#ifdef UNICODE
#define FreeGPOList  FreeGPOListW
#else
#define FreeGPOList  FreeGPOListA
#endif // !UNICODE


//=============================================================================
//
// Group Policy Object client side extension support
//
// Flags, data structures and function prototype
//
// To register your extension, create a subkey under this key
//
// Software\Microsoft\Windows NT\CurrentVersion\Winlogon\GPOExtensions
//
// The subkey needs to be unique (eg: your DLL name, company name, etc)
// Then add these values:
//
//     DllName      REG_EXPAND_SZ   Path to your DLL
//     ProcessGPO   REG_SZ          Function name (see PFNPROCESSGPO prototype)
//
//=============================================================================

#define GPO_INFO_FLAG_MACHINE     0x00000001  // Apply machine policy rather than user policy
#define GPO_INFO_FLAG_DELETE      0x00000002  // Delete policy rather than apply
#define GPO_INFO_FLAG_FIRSTGPO    0x00000004  // First GPO in the sequence
#define GPO_INFO_FLAG_LASTGPO     0x00000008  // Last GPO in the sequence
#define GPO_INFO_FLAG_BACKGROUND  0x00000010  // Background refresh of policy (ok to do slow stuff)
#define GPO_INFO_FLAG_SLOWLINK    0x00000020  // Policy is being applied across a slow link
#define GPO_INFO_FLAG_VERBOSE     0x00000040  // Verbose output to the eventlog
#define GPO_INFO_FLAG_NOCHANGES   0x00000080  // No changes were detected to the Group Policy Objects


typedef struct _GPO_INFO
{
   DWORD    dwSize;               // Size of this structure
   DWORD    dwFlags;              // Flags
   HANDLE   hUserToken;           // User's token
   HKEY     hKeyRoot;             // HKLM or HKCU registry key
   LPCWSTR  lpGPOName;            // Unique GPO name (usually a GUID)
   LPCWSTR  lpFileSysPath;        // Path to the file system part of the GPO
   LPCWSTR  lpDSPath;             // Path to the DS part of the GPO
   LPCWSTR  lpDisplayName;        // Friendly display name of GPO

}  GPO_INFO, *PGPO_INFO;

typedef BOOL (*PFNPROCESSGPO)(PGPO_INFO pGPOInfo);


//=============================================================================
//
// Group Policy Notifications
//
// Some applications need to know when group policy is applied so
// they can adjust according.  There are 2 ways an application can
// be notify of this.
//
// 1)  A WM_WININICHANGE message is broadcast to all desktops.
//        wParam - 1 if machine policy was applied, 0 if user policy was applied.
//        lParam - Points to the string "Policy"
//
// 2)  An event is signaled.  There are 2 events (one for machine policy and
//     one for user policy), after policy is set, the appropriate event is
//     signaled.  An application can call OpenEvent() with one the names below and
//     then call WaitForSingleObject().
//
//=============================================================================

#define GROUP_POLICY_USER_EVENTA       "UserGroupPolicyApplied"
#define GROUP_POLICY_USER_EVENTW      L"UserGroupPolicyApplied"
#define GROUP_POLICY_MACHINE_EVENTA    "MachineGroupPolicyApplied"
#define GROUP_POLICY_MACHINE_EVENTW   L"MachineGroupPolicyApplied"

#ifdef UNICODE
#define GROUP_POLICY_USER_EVENT     GROUP_POLICY_USER_EVENTW
#define GROUP_POLICY_MACHINE_EVENT  GROUP_POLICY_MACHINE_EVENTW
#else
#define GROUP_POLICY_USER_EVENT     GROUP_POLICY_USER_EVENTA
#define GROUP_POLICY_MACHINE_EVENT  GROUP_POLICY_MACHINE_EVENTA
#endif


#ifdef __cplusplus
}
#endif


#endif // _INC_USERENV
