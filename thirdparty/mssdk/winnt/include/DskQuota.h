/************************************************************************
*                                                                       *
*   dskquota.h --  public header for Windows NT disk quota interfaces.  *
*                                                                       *
*   Copyright (c) 1991-1998, Microsoft Corp. All rights reserved.       *
*                                                                       *
************************************************************************/
#ifndef __DSKQUOTA_H
#define __DSKQUOTA_H

//
// This is the public header for the Windows NT disk quota control 
// COM library.  The interfaces are implemented in DSKQUOTA.DLL.
//
// Define the INITGUIDS macros in one source module (and only one source
// module) before including this header.  This will generate a single 
// definition for the GUIDs used by the library.
//
// DSKQUOTA.DLL is self-registering using REGSVR32.
//
// Functions listing Win32 error codes as a return value,
// (i.e. ERROR_ACCESS_DENIED), actually return the value as the "code" part
// of an HRESULT created using HRESULT_FROM_WIN32(code).  Use the
// HRESULT_CODE(hr) macro to extract the error code from the HRESULT.
//
//
// Interfaces -----------------------------------------------------------------
//
//      IDiskQuotaControl
//
//          Represents an NTFS volume for purposes of managing disk quota.
//          Instantiate this interface for each volume to be controlled.
//          Through it you can:
//              * Enable/Disable disk quotas.
//              * Obtain status of quota system on the volume.
//              * Deny disk space to users exceding their quota limit.
//              * Assign default warning threshold and quota limit values
//                to be used for new volume users.
//              * Locate a single user quota entry.
//              * Mark a user quota entry for deletion.
//              * Create an enumeration object for enumerating user quota
//                entries.
//              * Create a batch object for updating multiple user quota
//                entries efficiently.
//
//      IDiskQuotaUser
//
//          Represents a user quota entry on the volume.
//          Instantiated through IEnumDiskQuotaUsers, 
//              IDiskQuotaControl::FindUserSid or 
//              IDiskQuotaControl::FindUserName or
//              IDiskQuotaControl::AddUserName or
//              IDiskQuotaControl::AddUserSid
//
//          Through it you can:
//              * Set/Retrieve the user's quota warning threshold and quota
//                limit.
//              * Retrieve the user's quota amount "used" value.
//              * Retrieve the user's account name information.
//                   - Account container name
//                   - Logon name
//                   - Display name
//              * Retrieve the user's security ID (SID).
//
//      IEnumDiskQuotaUsers
//
//          Enumerates user quota entries on the volume.  Implements the
//          standard OLE IEnumXXXX interface.
//          Instantiated through IDiskQuotaControl::CreateEnumUsers.
//
//      IDiskQuotaUserBatch
//
//          Coordinates the update of multiple user quota entries into
//          a single call to NTFS.  Improves update efficiency when 
//          multiple entries must be updated.
//          Instantiated through IDiskQuotaControl::CreateUserBatch.
//
//      IDiskQuotaEvents
//
//          The DiskQuotaControl object services this interface as
//          an OLE connection point.  The connection point is used to
//          notify client code when a significant event has occured in
//          the quota system.  Currently, the only event supported is
//          the asynchronous update of a quota user object's name 
//          information.
//
// Interfaces [end] -----------------------------------------------------------
//          
//
#ifndef _WINDOWS_
#include <windows.h>
#endif

#ifndef _OLE2_H_
#include <ole2.h>
#endif

#ifndef _OLECTL_H_
#include <olectl.h>
#endif

#ifdef INITGUIDS
#include <initguid.h>
#endif


//
// Class IDs
//
// {7988B571-EC89-11cf-9C00-00AA00A14F56}
DEFINE_GUID(CLSID_DiskQuotaControl, 
0x7988b571, 0xec89, 0x11cf, 0x9c, 0x0, 0x0, 0xaa, 0x0, 0xa1, 0x4f, 0x56);

//
// Interface IDs
//
// {7988B572-EC89-11cf-9C00-00AA00A14F56}
DEFINE_GUID(IID_IDiskQuotaControl, 
0x7988b572, 0xec89, 0x11cf, 0x9c, 0x0, 0x0, 0xaa, 0x0, 0xa1, 0x4f, 0x56);

// {7988B574-EC89-11cf-9C00-00AA00A14F56}
DEFINE_GUID(IID_IDiskQuotaUser, 
0x7988b574, 0xec89, 0x11cf, 0x9c, 0x0, 0x0, 0xaa, 0x0, 0xa1, 0x4f, 0x56);

// {7988B576-EC89-11cf-9C00-00AA00A14F56}
DEFINE_GUID(IID_IDiskQuotaUserBatch, 
0x7988b576, 0xec89, 0x11cf, 0x9c, 0x0, 0x0, 0xaa, 0x0, 0xa1, 0x4f, 0x56);

// {7988B577-EC89-11cf-9C00-00AA00A14F56}
DEFINE_GUID(IID_IEnumDiskQuotaUsers, 
0x7988b577, 0xec89, 0x11cf, 0x9c, 0x0, 0x0, 0xaa, 0x0, 0xa1, 0x4f, 0x56);

// {7988B579-EC89-11cf-9C00-00AA00A14F56}
DEFINE_GUID(IID_IDiskQuotaEvents, 
0x7988b579, 0xec89, 0x11cf, 0x9c, 0x0, 0x0, 0xaa, 0x0, 0xa1, 0x4f, 0x56);


//
// Definitions for value and bits in DWORD returned by GetQuotaState().
//
#define DISKQUOTA_STATE_DISABLED            0x00000000
#define DISKQUOTA_STATE_TRACK               0x00000001
#define DISKQUOTA_STATE_ENFORCE             0x00000002
#define DISKQUOTA_STATE_MASK                0x00000003
#define DISKQUOTA_FILESTATE_INCOMPLETE      0x00000100
#define DISKQUOTA_FILESTATE_REBUILDING      0x00000200
#define DISKQUOTA_FILESTATE_MASK            0x00000300

//
// Helper macros for setting and testing state value.
//
#define DISKQUOTA_SET_DISABLED(s) \
            ((s) &= ~DISKQUOTA_STATE_MASK)

#define DISKQUOTA_SET_TRACKED(s) \
            ((s) |= (DISKQUOTA_STATE_MASK & DISKQUOTA_STATE_TRACK))

#define DISKQUOTA_SET_ENFORCED(s) \
            ((s) |= (DISKQUOTA_STATE_ENFORCE & DISKQUOTA_STATE_ENFORCE))

#define DISKQUOTA_IS_DISABLED(s) \
            (DISKQUOTA_STATE_DISABLED == ((s) & DISKQUOTA_STATE_MASK))

#define DISKQUOTA_IS_TRACKED(s) \
            (DISKQUOTA_STATE_TRACK == ((s) & DISKQUOTA_STATE_MASK))

#define DISKQUOTA_IS_ENFORCED(s) \
            (DISKQUOTA_STATE_ENFORCE == ((s) & DISKQUOTA_STATE_MASK))
//
// These file state flags are read-only.
//
#define DISKQUOTA_FILE_INCOMPLETE(s) \
            (0 != ((s) & DISKQUOTA_FILESTATE_INCOMPLETE))

#define DISKQUOTA_FILE_REBUILDING(s) \
            (0 != ((s) & DISKQUOTA_FILESTATE_REBUILDING))


//
// Definitions for bits in DWORD returned by GetQuotaLogFlags().
//
#define DISKQUOTA_LOGFLAG_USER_THRESHOLD    0x00000001
#define DISKQUOTA_LOGFLAG_USER_LIMIT        0x00000002

//
// Helper macros to interrogate a log flags DWORD.
//
#define DISKQUOTA_IS_LOGGED_USER_THRESHOLD(f) \
            (0 != ((f) & DISKQUOTA_LOGFLAG_USER_THRESHOLD))

#define DISKQUOTA_IS_LOGGED_USER_LIMIT(f) \
            (0 != ((f) & DISKQUOTA_LOGFLAG_USER_LIMIT))

//
// Helper macros to set/clear bits in a log flags DWORD.
//
#define DISKQUOTA_SET_LOG_USER_THRESHOLD(f,yn) \
              ((f &= ~DISKQUOTA_LOGFLAG_USER_THRESHOLD) |= ((yn) ? DISKQUOTA_LOGFLAG_USER_THRESHOLD : 0))

#define DISKQUOTA_SET_LOG_USER_LIMIT(f,yn) \
              ((f &= ~DISKQUOTA_LOGFLAG_USER_LIMIT) |= ((yn) ? DISKQUOTA_LOGFLAG_USER_LIMIT : 0))

//
// Per-user quota information.
//
typedef struct DiskQuotaUserInformation {    
    LONGLONG QuotaUsed;
    LONGLONG QuotaThreshold;
    LONGLONG QuotaLimit;
} DISKQUOTA_USER_INFORMATION, *PDISKQUOTA_USER_INFORMATION;


//
// Values for fNameResolution argument to:
//
//      IDiskQuotaControl::AddUserSid
//      IDiskQuotaControl::AddUserName
//      IDiskQuotaControl::FindUserSid
//      IDiskQuotaControl::CreateEnumUsers
//
#define DISKQUOTA_USERNAME_RESOLVE_NONE     0
#define DISKQUOTA_USERNAME_RESOLVE_SYNC     1
#define DISKQUOTA_USERNAME_RESOLVE_ASYNC    2

//
// Values for status returned by IDiskQuotaUser::GetAccountStatus.
//
#define DISKQUOTA_USER_ACCOUNT_RESOLVED     0
#define DISKQUOTA_USER_ACCOUNT_UNAVAILABLE  1
#define DISKQUOTA_USER_ACCOUNT_DELETED      2
#define DISKQUOTA_USER_ACCOUNT_INVALID      3
#define DISKQUOTA_USER_ACCOUNT_UNKNOWN      4
#define DISKQUOTA_USER_ACCOUNT_UNRESOLVED   5


///////////////////////////////////////////////////////////////////////////////
// IDiskQuotaUser interface
//
// This interface represents a single user entry in the volume's quota
// information file.  Through this interface, you can query and modify
// user-specific quota information on an NTFS volume.  An IDiskQuotaUser 
// interface is instantiated through IEnumDiskQuotaUsers, 
//      IDiskQuotaControl::FindUserSid
//      IDiskQuotaControl::FindUserName
//      IDiskQuotaControl::AddUserSid
//      IDiskQuotaControl::AddUserName
//
// IDiskQuotaUser::GetID ------------------------------------------------------
//
//      Retrieves a unique ID number for the DiskQuotaUser object.  This ID 
//      is unique on a per-process basis only.  This is useful for identifying
//      a user object in a set of user objects when the language used doesn't
//      support pointers (i.e. Visual Basic and VBScript).
//
//      Arguments:
//
//          pulID - Address of unsigned long variable to receive the ID number.
//
//      Returns:
//          NOERROR
//
//
// IDiskQuotaUser::GetName ----------------------------------------------------
//
//      Retrieves the various name strings associated with a disk quota user.
//
//      Arguments:
//
//          pszContainer - Address of buffer to receive the name of the user's 
//              account container.  May be NULL.  For NT4 accounts or for NT5
//              accounts without directory service informaiton available, this string
//              is simply the domain name.  For NT5 accounts with directory service
//              information available, this is the canonical name with the terminating
//              object name removed.
//
//              ex:  NT4 & NT5 w/o DS info:
//                      "THEDOMAIN"
//
//                   NT5 with DS info:
//                      "usa.acme.com/toys/engineering"
//
//          cchContainer - Size of container name buffer in characters.  Ignored if
//              pszContainer is NULL.
//
//          pszLogonName - Address of buffer to receive the name the user uses
//              to logon to the machine.  As with the container name, this name
//              is different for NT4 and NT5 accounts.  May be NULL.
//
//              ex:  NT4 & NT5 w/o DS info:
//                      "THEDOMAIN\jqpublic"
//
//                   NT5 with DS info:
//                      "jqpublic@acme.com"
//
//          cchLogonName - Size of the logon name buffer in characters.  
//              Ignored if pszLogonName is NULL.
//
//          pszDisplayName - Address of buffer to receive the displayable name for
//              the quota user.  May be NULL.  If the account does not contain
//              this information, a text string of length 0 is returned.
//
//              ex:  "John Q. Public"
//
//          cchDisplayName - Size of the display buffer in characters.  Ignored
//              if pszDisplayName is NULL.
//
//      Returns:
//          NOERROR           - Success.
//          ERROR_LOCK_FAILED - Could not gain exclusive lock on user object.
//
//
// IDiskQuotaUser::GetSidLength -----------------------------------------------
//
//      Retrieves the length of the user's security ID (SID) in bytes.  The
//      return value is used to size the destination buffer passed to
//      IDiskQuotaUser::GetSid.
//
//      Arguments:
//
//          pdwLength - Address of DWORD variable to receive SID length.
//
//      Returns:
//
//          NOERROR           - Success.
//          E_INVALIDARG      - pdwLength argument is NULL.
//          ERROR_INVALID_SID - User's SID is invalid.
//          ERROR_LOCK_FAILED - Could not gain exclusive lock on user object.
//          
//
// IDiskQuotaUser::GetSid -----------------------------------------------------
//
//      Retrieves the user's security ID (SID).
//
//      Arguments:
//
//          pbSidBuffer - Address of destination buffer to receive SID.
//
//          cbSidBuffer - Size of destination buffer in bytes.
//
//      Returns:
//
//          NOERROR                   - Success.
//          E_INVALIDARG              - pbSidBuffer is NULL.
//          ERROR_INVALID_SID         - Quota entry SID is invalid.
//          ERROR_INSUFFICIENT_BUFFER - Insufficient destination buffer size.
//          ERROR_LOCK_FAILED         - Couldn't lock user object.
//          
//
// IDiskQuotaUser::GetQuotaThreshold ------------------------------------------
//
//      Retrieves the user's quota "threshold" value on the volume.  The
//      threshold is an arbitrary value set by the volume's quota 
//      administrator.  It may be used to identify users who are approaching
//      their quota limit.
//
//      Arguments:
//
//          pllThreshold - Address of LONGLONG variable to receive the 
//              threshold value.
//
//      Returns:
//
//          NOERROR             - Success.
//          ERROR_ACCESS_DENIED - No READ access to quota information.
//          ERROR_LOCK_FAILED   - Couldn't lock user object.
//          E_INVALIDARG        - pllThreshold is NULL.
//          E_OUTOFMEMORY       - Insufficient memory.
//          E_FAIL              - Unexpected filesystem error.
//          E_UNEXPECTED        - Unexpected exception.
//          
//          This function may return other errors expressed as HResults
//          returned from the filesystem.  
//
// IDiskQuotaUser::GetQuotaThresholdText --------------------------------------
//
//      Retrieves the user's quota "threshold" value expressed as a text
//      string (i.e. "10.5 MB").  If the user's threshold is unlimited,
//      the string "No Limit" is returned (localized).  If the destination
//      buffer is too small, the string is automatically truncated to fit.
//
//      Arguments:
//
//          pszText - Address of character buffer to receive text.
//
//          cchText - Size of destination buffer in bytes.
//
//      Returns:
//
//          NOERROR             - Success.
//          ERROR_ACCESS_DENIED - No READ access to quota information.
//          ERROR_LOCK_FAILED   - Couldn't lock user object.
//          E_INVALIDARG        - pszText is NULL.
//          E_OUTOFMEMORY       - Insufficient memory.
//          E_FAIL              - Unexpected filesystem error.
//          E_UNEXPECTED        - Unexpected exception.
//
//          This function may return other errors expressed as HResults
//          returned from the filesystem.  
//
// IDiskQuotaUser::GetQuotaLimit ----------------------------------------------
//
//      Retrieves the user's quota "limit" value on the volume.  The
//      limit is set as the maximum amount of disk space available to the
//      volume user.  There are two special-case values associated with the
//      quota limit.
//
//          -1 = User has unlimited quota on the volume.
//          -2 = User's quota entry is marked for deletion.  If the entry's
//               value for quota "used" is 0, the record will be deleted by
//               NTFS at some future time.
//
//      Arguments:
//
//          pllLimit - Address of LONGLONG variable to receive the limit value.
//
//      Returns:
//
//          NOERROR             - Success.
//          ERROR_ACCESS_DENIED - No READ access to quota information.
//          ERROR_LOCK_FAILED   - Couldn't lock user object.
//          E_INVALIDARG        - pllLimit is NULL.
//          E_OUTOFMEMORY       - Insufficient memory.
//          E_FAIL              - Unexpected filesystem error.
//          E_UNEXPECTED        - Unexpected exception.
//          
//          This function may return other errors expressed as HResults
//          returned from the filesystem.  
//
// IDiskQuotaUser::GetQuotaLimitText ------------------------------------------
//
//      Retrieves the user's quota "limit" value expressed as a text
//      string (i.e. "10.5 MB").  If the user's limit is unlimited,
//      the string "No Limit" is returned (localized).  If the destination
//      buffer is too small, the string is automatically truncated to fit.
//
//      Arguments:
//
//          pszText - Address of character buffer to receive text.
//
//          cchText - Size of destination buffer in bytes.
//
//      Returns:
//
//          NOERROR             - Success.
//          ERROR_ACCESS_DENIED - No READ access to quota information.
//          ERROR_LOCK_FAILED   - Couldn't lock user object.
//          E_INVALIDARG        - pszText is NULL.
//          E_OUTOFMEMORY       - Insufficient memory.
//          E_FAIL              - Unexpected filesystem error.
//          E_UNEXPECTED        - Unexpected exception.
//
//          This function may return other errors expressed as HResults
//          returned from the filesystem.  
//
// IDiskQuotaUser::GetQuotaUsed -----------------------------------------------
//
//      Retrieves the user's quota "used" value on the volume.  This is the
//      amount of information stored on the volume by the user.  Note that
//      this is the amount of uncompressed information.  Therefore, the 
//      use of NTFS compression does not affect this value.
//
//      Arguments:
//
//          pllUsed - Address of LONGLONG variable to receive the 
//              quota used value.
//
//      Returns:
//
//          NOERROR             - Success.
//          ERROR_ACCESS_DENIED - No READ access to quota information.
//          ERROR_LOCK_FAILED   - Couldn't lock user object.
//          E_INVALIDARG        - pllUsed is NULL.
//          E_OUTOFMEMORY       - Insufficient memory.
//          E_FAIL              - Unexpected filesystem error.
//          E_UNEXPECTED        - Unexpected exception.
//          
//          This function may return other errors expressed as HResults
//          returned from the filesystem.  
//
// IDiskQuotaUser::GetQuotaUsedText -------------------------------------------
//
//      Retrieves the user's quota "used" value expressed as a text
//      string (i.e. "10.5 MB").    If the destination buffer is too small, 
//      the string is automatically truncated to fit.
//
//      Arguments:
//
//          pszText - Address of character buffer to receive text.
//
//          cchText - Size of destination buffer in bytes.
//
//      Returns:
//
//          NOERROR             - Success.
//          ERROR_ACCESS_DENIED - No READ access to quota information.
//          ERROR_LOCK_FAILED   - Couldn't lock user object.
//          E_INVALIDARG        - pszText is NULL.
//          E_OUTOFMEMORY       - Insufficient memory.
//          E_FAIL              - Unexpected filesystem error.
//          E_UNEXPECTED        - Unexpected exception.
//          
//          This function may return other errors expressed as HResults
//          returned from the filesystem.  
//
// IDiskQuotaUser::GetQuotaInformation ----------------------------------------
//
//      Retrieves the user's quota "threshold", "used" and "limit" values in 
//      a single function call.
//
//      Arguments:
//
//          pQuotaInfo - Address of DISKQUOTA_USER_INFORMATION structure to 
//              receive the quota information.
//
//          cbQuotaInfo - Size of the desination buffer in bytes.
//
//      Returns:
//
//          NOERROR             - Success.
//          ERROR_ACCESS_DENIED - No READ access to quota information.
//          ERROR_LOCK_FAILED   - Couldn't lock user object.
//          E_INVALIDARG        - pQuotaInfo is NULL.
//          E_OUTOFMEMORY       - Insufficient memory.
//          E_FAIL              - Unexpected filesystem error.
//          E_UNEXPECTED        - Unexpected exception.
//          
//          This function may return other errors expressed as HResults
//          returned from the filesystem.  
//          
//
// IDiskQuotaUser::SetQuotaThreshold ------------------------------------------
//
//      Sets the user's quota "threshold" value on the volume.  The
//      threshold is an arbitrary value set by the volume's quota 
//      administrator.  It may be used to identify users who are approaching
//      their quota limit.
//
//      Arguments:
//
//          llThreshold - Threshold value.
//
//          fWriteThrough - Set this to TRUE if you want to immediately write
//              the value to the volume's quota file.  Otherwise, the value
//              is only written to the quota user object's local memory.
//              This value should normally be set to TRUE.  Set it to FALSE 
//              when using the IDiskQuotaUserBatch interface to modify 
//              multiple user quota entries at once.
//
//      Returns:
//
//          NOERROR             - Success.
//          ERROR_ACCESS_DENIED - No WRITE access to quota information.
//          ERROR_LOCK_FAILED   - Couldn't lock user object.
//          E_FAIL              - Unexpected filesystem error.
//
//          This function may return other errors expressed as HResults
//          returned from the filesystem.  
//
// IDiskQuotaUser::SetQuotaLimit ----------------------------------------------
//
//      Sets the user's quota "limit" value on the volume.  The
//      limit is set as the maximum amount of disk space available to the
//      volume user.  
//
//      Arguments:
//
//          llLimit - Limit value (bytes).  -1 = Unlimitd quota.
//
//          fWriteThrough - Set this to TRUE if you want to immediately write
//              the value to the volume's quota file.  Otherwise, the value
//              is only written to the quota user object's local memory.
//              This value should normally be set to TRUE.  Set it to FALSE 
//              when using the IDiskQuotaUserBatch interface to modify 
//              multiple user quota entries at once.
//
//      Returns:
//
//          NOERROR             - Success.
//          ERROR_ACCESS_DENIED - No WRITE access to quota information.
//          ERROR_LOCK_FAILED   - Couldn't lock user object.
//          E_FAIL              - Unexpected filesystem error.
//
//          This function may return other errors expressed as HResults
//          returned from the filesystem.  
//          
//
// IDiskQuotaUser::Invalidate -------------------------------------------------
//
//      Invalidates the quota information stored in the quota user object.
//      The next time information is requested, it is refreshed from disk.
//
//      Arguments: None.
//
//      Returns:   NOERROR.
//          
//
// IDiskQuotaUser::GetAccountStatus -------------------------------------------
//
//      Retrieves the status of the user object's account.  User information
//      is identified in the quota system by user security ID (SID).  This
//      SID must be resolved to a user account for the user's account name
//      information to be retrieved.  This status information may be used 
//      to determine why a user's name string(s) are not available.
//
//      Arguments:
//
//          pdwStatus - Address of DWORD variable to receive user's account
//              status.  The status value may be one of the following:
//
//              DISKQUOTA_USER_ACCOUNT_RESOLVED - SID has been resolved to
//                  a user account.  Names are available through GetName().
//
//              DISKQUOTA_USER_ACCOUNT_UNAVAILABLE - User's account is 
//                  unavailable at this time.  Network domain controller
//                  may not be available.  Name information will not be
//                  available.
//
//              DISKQUOTA_USER_ACCOUNT_DELETED - User's account has been
//                  deleted from the domain.  Name information will not be
//                  available.
//
//              DISKQUOTA_USER_ACCOUNT_INVALID - User's account is invalid.
//                  Name information will not be available.
//
//              DISKQUOTA_USER_ACCOUNT_UNKNOWN - User's account is unknown.
//                  Name information will not be available.
//
//              DISKQUOTA_USER_ACCOUNT_UNRESOLVED - SID has yet to be resolved
//                  to a user account.  
//
//
//      Returns:   NOERROR      - Success.
//                 E_INVALIDARG - pdwStatus argument is NULL.
//
///////////////////////////////////////////////////////////////////////////////
#undef  INTERFACE
#define INTERFACE IDiskQuotaUser

DECLARE_INTERFACE_(IDiskQuotaUser, IUnknown)
{
    STDMETHOD(GetID)(THIS_
        ULONG *pulID) PURE;

    STDMETHOD(GetName)(THIS_ 
        LPWSTR pszAccountContainer, 
        DWORD cchAccountContainer, 
        LPWSTR pszLogonName, 
        DWORD cchLogonName, 
        LPWSTR pszDisplayName, 
        DWORD cchDisplayName) PURE;

    STDMETHOD(GetSidLength)(THIS_ 
        LPDWORD pdwLength) PURE;

    STDMETHOD(GetSid)(THIS_ 
        LPBYTE pbSidBuffer, 
        DWORD cbSidBuffer) PURE;

    STDMETHOD(GetQuotaThreshold)(THIS_ 
        PLONGLONG pllThreshold) PURE;

    STDMETHOD(GetQuotaThresholdText)(THIS_
        LPWSTR pszText,
        DWORD cchText) PURE;

    STDMETHOD(GetQuotaLimit)(THIS_ 
        PLONGLONG pllLimit) PURE;

    STDMETHOD(GetQuotaLimitText)(THIS_
        LPWSTR pszText,
        DWORD cchText) PURE;

    STDMETHOD(GetQuotaUsed)(THIS_ 
        PLONGLONG pllUsed) PURE;

    STDMETHOD(GetQuotaUsedText)(THIS_
        LPWSTR pszText,
        DWORD cchText) PURE;

    STDMETHOD(GetQuotaInformation)(THIS_ 
        LPVOID pbQuotaInfo, 
        DWORD cbQuotaInfo) PURE;

    STDMETHOD(SetQuotaThreshold)(THIS_ 
        LONGLONG llThreshold,
        BOOL fWriteThrough) PURE;

    STDMETHOD(SetQuotaLimit)(THIS_ 
        LONGLONG llLimit,
        BOOL fWriteThrough) PURE;

    STDMETHOD(Invalidate)(THIS) PURE;

    STDMETHOD(GetAccountStatus)(THIS_ 
        LPDWORD pdwStatus) PURE;
};

typedef IDiskQuotaUser DISKQUOTA_USER, *PDISKQUOTA_USER;


///////////////////////////////////////////////////////////////////////////////
// IEnumDiskQuotaUsers interface
//
// Implementation of a standard OLE IEnumXXXX interface for enumerating 
// IDiskQuotaUser objects.  IEnumDiskQuotaUsers is instantiated 
// with IDiskQuotaControl::CreateEnumUsers.
//
// For a description of argument and return values, see the OLE documentation 
// for IEnumXXXX.
//
///////////////////////////////////////////////////////////////////////////////
#undef  INTERFACE
#define INTERFACE IEnumDiskQuotaUsers

DECLARE_INTERFACE_(IEnumDiskQuotaUsers, IUnknown)
{
    STDMETHOD(Next)(THIS_ 
        DWORD cUsers, 
        PDISKQUOTA_USER *rgUsers, 
        LPDWORD pcUsersFetched) PURE;

    STDMETHOD(Skip)(THIS_ 
        DWORD cUsers) PURE;

    STDMETHOD(Reset)(THIS) PURE;

    STDMETHOD(Clone)(THIS_ 
        IEnumDiskQuotaUsers **ppEnum) PURE;
};

typedef IEnumDiskQuotaUsers ENUM_DISKQUOTA_USERS, *PENUM_DISKQUOTA_USERS;



///////////////////////////////////////////////////////////////////////////////
// IDiskQuotaUserBatch interface
//
// This interface provides a mechanism for optimizing updates of quota
// information on multiple users.  Through this interface, you can add quota
// user objects to a container that is then submitted for update in a single
// call.  This reduces the number of calls to the underlying file system
// providing optimal performance when large numbers of user objects must
// be updated.
//
// IDiskQuotaUserBatch::Add ---------------------------------------------------
//
//      Adds an IDiskQuotaUser pointer to the batch list.  When setting values
//      on a quota user object in preparation for batch processing, specify
//      FALSE for the fWriteThrough flag in the SetQuotaLimit and
//      SetQuotaThreshold functions.  This will store the values in memory
//      without writing through to disk.  Calling FlushToDisk will write the
//      changes to disk.
//      This function calls AddRef() on the pUser interface pointer.
//      Release() is automatically called on each contained IDiskQuotaUser 
//      interface pointer when the batch object is destroyed.
//
//      Arguments:
//
//          pUser - Address of quota user object's IDiskQuotaUser interface.
//
//      Returns:
//
//          NOERROR        - Success.
//          E_INVALIDARG   - pUser arg is NULL. 
//          E_OUTOFMEMORY  - Insufficient memory.
//          E_UNEXPECTED   - Unexpected exception occured.
//          
//
// IDiskQuotaUserBatch::Remove ------------------------------------------------
//
//      Removes an IDiskQuotaUser pointer from the batch list.
//
//      Arguments:
//
//          pUser - Address of quota user object's IDiskQuotaUser interface.
//
//      Returns:
//
//          S_OK          - Success.
//          S_FALSE       - Quota user object not found in batch.
//          E_INVALIDARG  - pUser arg is NULL. 
//          E_UNEXPECTED  - An unexpected exception occured.
//
//
// IDiskQuotaUserBatch::RemoveAll ---------------------------------------------
//
//      Removes all IDiskQuotaUser pointers from the batch list.
//
//      Arguments: None.
//
//      Returns:
//
//          NOERROR      - Success.
//          E_UNEXPECTED - An unexpected exception occured.
//
//
// IDiskQuotaUserBatch::FlushToDisk -------------------------------------------
//
//      Writes user object changes to disk in a single call to the filesystem.
//
//      Note that there are limitations as to how much information can be
//      written to disk in a single call to the file system.  The flush 
//      operation may require multiple calls to NTFS.  Nonetheless, it will
//      be much more efficient than a single call for each user object.
//
//      Arguments: None.
//
//      Returns:
//
//          NOERROR             - Success.
//          ERROR_ACCESS_DENIED - No WRITE access to quota information.
//          E_OUTOFMEMORY       - Insufficient memory.
//          E_UNEXPECTED        - An unexpected exception occured.
//          E_FAIL              - Unexpected filesystem error.
//
//          This function may return other errors expressed as HResults
//          returned from the filesystem.  
//
///////////////////////////////////////////////////////////////////////////////
#undef  INTERFACE
#define INTERFACE IDiskQuotaUserBatch

DECLARE_INTERFACE_(IDiskQuotaUserBatch, IUnknown)
{
    STDMETHOD(Add)(THIS_ 
        PDISKQUOTA_USER pUser) PURE;

    STDMETHOD(Remove)(THIS_ 
        PDISKQUOTA_USER pUser) PURE;

    STDMETHOD(RemoveAll)(THIS) PURE;

    STDMETHOD(FlushToDisk)(THIS) PURE;
};


typedef IDiskQuotaUserBatch DISKQUOTA_USER_BATCH, *PDISKQUOTA_USER_BATCH;


///////////////////////////////////////////////////////////////////////////////
// IDiskQuotaControl interface
//
// This interface is the principle point of control for the disk quota control
// library.  A client instantiates this interface through CoCreateInstance
// using the the class ID CLSID_DiskQuotaControl.  The resulting quota control 
// object provides a layer of abstraction around the disk quota facilities of 
// a single NTFS volume.  Through the IDiskQuotaControl interface, the client
// may query and set volume-specific quota attributes as well as enumerate
// all quota user entries on the volume.
//
// The DiskQuotaControl object also implements IConnectionPointContainer
// to service the IDiskQuotaEvents connection point interface.
//
//
// IDiskQuotaControl::Initialize ----------------------------------------------
//
//      Initializes a new QuotaControl object by opening the NTFS volume
//      with the requested access rights.  The return value indicates
//      if the volume does not support NTFS disk quotas or if the caller
//      does not have sufficient access rights.  
//
//                        >>>>>>  NOTE  <<<<<<<
//
//          Accessing quota information on remote volumes is not 
//          supported for NT5 Beta 1.  Remote volume support will be
//          added after Beta 1.
//
//      Arguments:
//
//          pszPath - Path to the volume root.
//
//                      ex:  "C:\"
//
//          bReadWrite - TRUE  = Open for read/write.
//                       FALSE = Open for read only
//
//      Returns:
//
//        NOERROR               - Success.
//        ERROR_INITIALIZED     - Controller object already initialized.
//        ERROR_ACCESS_DENIED   - Caller has insufficient access rights.
//        ERROR_INVALID_NAME    - Invalid path string at pszPath.
//        ERROR_FILE_NOT_FOUND  - Specified path doesn't exist.
//        ERROR_PATH_NOT_FOUND  - Specified path doesn't exist.
//        ERROR_BAD_PATHNAME    - Specified path name is invalid.
//        ERROR_NOTSUPPORTED    - File system doesn't support NTFS quotas.
//          
//              
// IDiskQuotaControl::SetQuotaState -------------------------------------------
//
//      Sets the state of the quota system.  Note that not all state attributes
//      can be modified.  The enable/disable and track/enforce attributes can
//      be modified.
//
//      Arguments:
//
//          dwState - DWORD containing the state to be applied to the volume.
//              Use the following macros to set the proper bits in the dwState
//              argument:
//
//                                       Enable?   Track?  Enforce?
//                                       --------- ------- --------
//              DISKQUOTA_SET_DISABLED -   No        No       No
//              DISKQUOTA_SET_TRACKED  -   Yes       Yes      No
//              DISKQUOTA_SET_ENFORCED -   Yes       Yes      Yes
//
//      Returns:
//
//          NOERROR             - Success.
//          ERROR_NOT_READY     - DiskQuotaControl object not initialized.
//          ERROR_ACCESS_DENIED - No WRITE access to quota information.
//          E_INVALIDARG        - dwState value is incorrect.
//          E_OUTOFMEMORY       - Insufficient memory.
//          E_UNEXPECTED        - Unexpected exception.
//          E_FAIL              - Unexpected filesystem error.
//
//          This function may return other errors expressed as HResults
//          returned from the filesystem.  
//
// IDiskQuotaControl::GetQuotaState -------------------------------------------
//
//      Retrieves a set of flags describing the state of the quota system.
//
//      Arguments:
//
//          pdwState - Address of DWORD to receive the state flags.  The flag
//              bits are defined as follows:
//
//              DISKQUOTA_STATE_DISABLED - Quotas are not enabled on the volume.
//
//              DISKQUOTA_STATE_TRACK - Quotas are enabled but the limit value
//                  is not being enforced.  Users may exceed their quota limit.
//
//              DISKQUOTA_STATE_ENFORCE - Quotas are enabled and the limit 
//                  value is enforced.  Users cannot exceed their quota limit.
//
//              DISKQUOTA_FILESTATE_INCOMPLETE - The volume's quota information
//                  is out of date.  Quotas are probably disabled.
//
//              DISKQUOTA_FILESTATE_REBUILDING - The volume is rebuilding it's
//                  quota information.
//
//      Returns:
//
//          NOERROR             - Success.
//          ERROR_NOT_READY     - DiskQuotaControl object not initialized.
//          ERROR_ACCESS_DENIED - No READ access to quota information.
//          E_INVALIDARG        - pdwState argument is NULL.
//          E_OUTOFMEMORY       - Insufficient memory.
//          E_UNEXPECTED        - Unexpected exception.
//          E_FAIL              - Unexpected filesystem error.
//          
//          This function may return other errors expressed as HResults
//          returned from the filesystem.  
//          
// IDiskQuotaControl::SetQuotaLogFlags ----------------------------------------
//
//      Controls the logging of user-related quota events on the volume. 
//      Logging consists of an entry in the volume server system's event log.
//
//      Arguments:
//
//          dwFlags - DWORD containing the flags to be applied to the volume.
//              Use the following macros to set the proper bits in the dwFlags
//              argument:
//
//              DISKQUOTA_SET_LOG_USER_THRESHOLD - Turn on/off logging of 
//                  user quota threshold violations.  If set, an event log
//                  entry will be created when the user exceeds their assigned
//                  quota warning threshold.
//
//              DISKQUOTA_SET_LOG_USER_LIMIT - Turn on/off logging of user
//                  quota limit violations.  If set, an event log entry will
//                  be created when the user exceeds their assigned quota 
//                  limit.
//
//      Returns:
//
//          NOERROR             - Success.
//          ERROR_NOT_READY     - DiskQuotaControl object not initialized.
//          ERROR_ACCESS_DENIED - No WRITE access to quota information.
//          E_OUTOFMEMORY       - Insufficient memory.
//          E_UNEXPECTED        - Unexpected exception.
//          E_FAIL              - Unexpected filesystem error.
//          
//          This function may return other errors expressed as HResults
//          returned from the filesystem.  
//
// IDiskQuotaControl::GetQuotaLogFlags ----------------------------------------
//
//      Retrieves the flags that control the logging of user-related quota 
//      events on the volume. Logging consists of an entry in the volume 
//      server's event log.
//
//      Arguments:
//
//          pdwFlags - Address of DWORD variable to receive the volume's
//              quota logging flags.  Use the following macros to 
//              interrogate the contents of the flag value:
//
//              DISKQUOTA_IS_LOGGED_USER_THRESHOLD
//              DISKQUOTA_IS_LOGGED_USER_LIMIT
//
//      Returns:
//
//          NOERROR             - Success.
//          ERROR_NOT_READY     - DiskQuotaControl object not initialized.
//          ERROR_ACCESS_DENIED - No READ access to quota information.
//          E_INVALIDARG        - pdwFlags argument is NULL.
//          E_OUTOFMEMORY       - Insufficient memory.
//          E_UNEXPECTED        - Unexpected exception.
//          E_FAIL              - Unexpected filesystem error.
//          
//          This function may return other errors expressed as HResults
//          returned from the filesystem.  
//          
// IDiskQuotaControl::SetDefaultQuotaLimit ------------------------------------
//
//      Modifies the default quota limit applied automatically to new users
//      of the volume.
//
//      Arguments:
//
//          llLimit - Default quota limit value.
//
//      Returns:
//
//          NOERROR             - Success.
//          ERROR_NOT_READY     - DiskQuotaControl object not initialized.
//          ERROR_ACCESS_DENIED - No WRITE access to quota information.
//          E_OUTOFMEMORY       - Insufficient memory.
//          E_UNEXPECTED        - Unexpected exception.
//          E_FAIL              - Unexpected filesystem error.
//          
//          This function may return other errors expressed as HResults
//          returned from the filesystem.  
//
// IDiskQuotaControl::GetDefaultQuotaLimit ------------------------------------
//
//      Retrieves the default quota limit applied automatically to new users
//      of the volume.
//
//      Arguments:
//
//          pllLimit - Address of LONGLONG variable to receive the limit value.
//
//      Returns:
//
//          NOERROR             - Success.
//          ERROR_NOT_READY     - DiskQuotaControl object not initialized.
//          ERROR_ACCESS_DENIED - No READ access to quota information.
//          E_INVALIDARG        - pllLimit argument is NULL.
//          E_OUTOFMEMORY       - Insufficient memory.
//          E_UNEXPECTED        - Unexpected exception.
//          E_FAIL              - Unexpected filesystem error.
//          
//          This function may return other errors expressed as HResults
//          returned from the filesystem.  
//          
// IDiskQuotaControl::GetDefaultQuotaLimitText --------------------------------
//
//      Retrieves the volume's default quota "limit" expressed as a text
//      string (i.e. "10.5 MB"). If the volume's limit is unlimited,
//      the string "No Limit" is returned (localized).  The text string
//      is automatically truncated to fit the buffer.
//
//      Arguments:
//
//          pszText - Address of character buffer to receive text.
//
//          cchText - Size of destination buffer in bytes.
//
//      Returns:
//          NOERROR             - Success.
//          ERROR_NOT_READY     - DiskQuotaControl object not initialized.
//          ERROR_ACCESS_DENIED - No READ access to quota information.
//          E_INVALIDARG        - pszText is NULL.
//          E_OUTOFMEMORY       - Insufficient memory.
//          E_UNEXPECTED        - Unexpected exception.
//          E_FAIL              - Unexpected filesystem error.
//          
//          This function may return other errors expressed as HResults
//          returned from the filesystem.  
//
// IDiskQuotaControl::SetDefaultQuotaThreshold --------------------------------
//
//      Modifies the default quota warning threshold applied automatically to 
//      new users of the volume.
//
//      Arguments:
//
//          llThreshold - Default quota threshold value.
//
//      Returns:
//
//          NOERROR             - Success.
//          ERROR_NOT_READY     - DiskQuotaControl object not initialized.
//          ERROR_ACCESS_DENIED - No WRITE access to quota information.
//          E_OUTOFMEMORY       - Insufficient memory.
//          E_UNEXPECTED        - Unexpected exception.
//          E_FAIL              - Unexpected filesystem error.
//          
//          This function may return other errors expressed as HResults
//          returned from the filesystem.  
//
// IDiskQuotaControl::GetDefaultQuotaThreshold --------------------------------
//
//      Retrieves the default quota warning threshold applied automatically to 
//      new users of the volume.
//
//      Arguments:
//
//          pllThreshold - Address of LONGLONG variable to receive the 
//              warning threshold value.
//
//      Returns:
//
//          NOERROR             - Success.
//          ERROR_NOT_READY     - DiskQuotaControl object not initialized.
//          ERROR_ACCESS_DENIED - No READ access to quota information.
//          E_INVALIDARG        - pllThreshold argument is NULL.
//          E_OUTOFMEMORY       - Insufficient memory.
//          E_UNEXPECTED        - Unexpected exception.
//          E_FAIL              - Unexpected filesystem error.
//          
//          This function may return other errors expressed as HResults
//          returned from the filesystem.  
//          
//
// IDiskQuotaControl::GetDefaultQuotaThresholdText ----------------------------
//
//      Retrieves the volume's default quota "threshold" expressed as a text
//      string (i.e. "10.5 MB"). If the volume's threshold is unlimited,
//      the string "No Limit" is returned (localized).  The text string
//      is automatically truncated to fit the buffer.
//
//      Arguments:
//
//          pszText - Address of character buffer to receive text.
//
//          cchText - Size of destination buffer in bytes.
//
//      Returns:
//          NOERROR             - Success.
//          ERROR_NOT_READY     - DiskQuotaControl object not initialized.
//          ERROR_ACCESS_DENIED - No READ access to quota information.
//          E_INVALIDARG        - pszText is NULL.
//          E_OUTOFMEMORY       - Insufficient memory.
//          E_UNEXPECTED        - Unexpected exception.
//          E_FAIL              - Unexpected filesystem error.
//          
//          This function may return other errors expressed as HResults
//          returned from the filesystem.  
//
//
// IDiskQuotaControl::AddUserSid ----------------------------------------------
// IDiskQuotaControl::AddUserName ---------------------------------------------
//
//      Adds a new quota entry on the volume for a given user.  Note that 
//      NTFS automatically creates a user quota entry when a user first writes
//      to the volume.  Automatically created user entries are assigned the
//      volume's default threshold and limit values.  This function allows
//      you to create a user quota entry before a user has written information
//      to the volume.  One reason for doing this might be to pre-assign
//      a threshold or limit value different than the volume defaults.
//
//      Arguments:
//
//          pUserSid - Address of buffer containing user's security ID (SID).
//
//          pszLogonName - Address of user's account logon name string.
//
//          fNameResolution - Flag indicating how the user's account information
//              is to be obtained.  The volume's quota information contains
//              only security IDs for identifying users.  The user's account 
//              information such as container, logon and display name 
//              must be obtained from the network domain controller, or 
//              the local machine if the machine is not networked.  This 
//              information may be obtained synchronously, asynchronously or 
//              not at all.
//              Specify one of the following values in this argument:
//
//              DISKQUOTA_USERNAME_RESOLVE_NONE - Do not resolve user account
//                  information.
//
//              DISKQUOTA_USERNAME_RESOLVE_SYNC - Resolve user account 
//                  information synchronously.  Function will not return until 
//                  the information has been resolved.  If the information
//                  is present in the disk quota SID cache, the return of
//                  information will be immediate.  If not cached, the
//                  function can take a considerable amount of time to 
//                  locate the user's information.  This period is dependent
//                  upon many network-related factors.  It can be on the
//                  order of several seconds.
//
//              DISKQUOTA_USERNAME_RESOLVE_ASYNC - Resolve user account 
//                  information asynchronously.  AddUser will return 
//                  immediately.  The caller must implement 
//                  IDiskQuotaUserEvents to receive notification when the 
//                  account information is available.  This option causes
//                  the user object to be placed on a queue.  This queue
//                  is serviced by a thread dedicated to obtaining account
//                  information for disk quota users on the volume. If the 
//                  information has been cached from a previous request,
//                  the notification occurs as soon as the object is serviced.
//                  If the information is not cached, the thread obtains
//                  the information from the network domain controller and
//                  then notifies IDiskQuotaUserEvents that the operation
//                  is complete.
//
//          ppUser - Address of IDiskQuotaUser pointer variable to receive
//              the interface pointer of the newly created quota user object.
//
//
//      Returns:
//
//          S_OK               - Success.
//          S_FALSE            - User already exists.  Not added.
//          ERROR_NOT_READY    - DiskQuotaControl object not initialized.
//          ERROR_USER_UNKNOWN - User name provided is unknown.
//          E_INVALIDARG       - A pointer argument was NULL.
//          E_OUTOFMEMORY      - Insufficient memory.
//          E_UNEXPECTED       - Unexpected exception.
//          E_FAIL             - Unexpected filesystem error.
//          
//          This function may return other errors expressed as HResults
//          returned from the filesystem.  
//
//
// IDiskQuotaControl::FindUserSid ---------------------------------------------
//
//      Locates a specific user entry in the volume's quota information.
//      The user's security ID (SID) is used as the search key.
//
//      Arguments:
//
//          pUserSid - Address of buffer containing user's security ID (SID).
//
//          fNameResolution - Flag indicating how the user's account information
//              is to be resolved.  See description in AddUser for details.
//
//          ppUser - Address of IDiskQuotaUser pointer variable to receive
//              the interface pointer of the quota user object for the user.
//
//      Returns:
//          NOERROR             - Success.
//          ERROR_NOT_READY     - DiskQuotaControl object not initialized.
//          ERROR_INVALID_SID   - SID pointed to by pUserSid is invalid.
//          ERROR_ACCESS_DENIED - No READ access to quota information.
//          E_INVALIDARG        - Either pUserSid or ppUser was NULL.
//          E_OUTOFMEMORY       - Insufficient memory.
//          E_UNEXPECTED        - Unexpected exception.
//          E_FAIL              - Unexpected filesystem error.
//          
//          This function may return other errors expressed as HResults
//          returned from the filesystem.  
//
//                   >>>>>>>>> IMPORTANT NOTE <<<<<<<<<
//
//        This method will return a user object even if there is no quota
//        record for the user in the quota file.  While that may sound
//        strange, it is consistent with the idea of automatic user addition
//        and default quota settings.  If there is currently no quota entry
//        for the requested user, and the user would be added to the quota
//        file if they were to request disk space, the returned user object
//        will have a quota threshold and limit equal to the volume defaults.
//
//
// IDiskQuotaControl::FindUserName --------------------------------------------
//
//      Locates a specific entry in the volume's quota information.
//      The user's domain and account name are used as the search key.  
//      This method can take some time as it may need to resolve the name to 
//      a security ID.  See note for FindUserSid (above) concerning behavior
//      when an entry for the user does not exist.
//
//      Arguments:
//
//          pszLogonName - Address of buffer containing user's account 
//              logon name.
//
//          ppUser - Address of IDiskQuotaUser pointer variable to receive
//              the interface pointer of the quota user object for the user.
//
//          fNameResolution - Flag indicating how the user's account information
//              is to be resolved.  See description in AddUser for details.
//
//      Returns:
//          NOERROR             - Success.
//          ERROR_NOT_READY     - DiskQuotaControl object not initialized.
//          ERROR_INVALID_SID   - SID pointed to by pUserSid is invalid.
//          ERROR_ACCESS_DENIED - No READ access to quota information.
//          ERROR_NONE_MAPPED   - Could not map account name to a security ID.
//          E_INVALIDARG        - Either pUserSid or ppUser was NULL.
//          E_OUTOFMEMORY       - Insufficient memory.
//          E_UNEXPECTED        - Unexpected exception.
//          E_FAIL              - Unexpected filesystem error.
//          
//          This function may return other errors expressed as HResults
//          returned from the filesystem.  
//
//
// IDiskQuotaControl::DeleteUser ----------------------------------------------
//
//      Removes a user entry from the volume's quota information file if the 
//      user's charged quota amount is 0 bytes.  This function doesn't actually
//      remove the quota entry from the volume.  It marks the entry for 
//      deletion.  NTFS performs the actual deletion at a later point in time.
//      Following a call to DeleteUser, the IDiskQuotaUser interface is still
//      active.  This function does not delete the user object from memory.
//      You must still call IUnknown::Release() on the user object to
//      release it.
//
//      Arguments:
//
//          pUser - Pointer to IDiskQuotaUser interface of quota user who's
//              quota record is marked for deletion.
//
//      Returns:
//      
//          NOERROR              - Success.
//          ERROR_NOT_READY      - DiskQuotaControl object not initialized.
//          ERROR_ACCESS_DENIED  - Insufficient access.
//          ERROR_FILE_EXISTS    - Couldn't delete.  User still has file(s) on
//                                 the volume.
//          E_INVALIDARG         - pUser argument was NULL.
//          E_OUTOFMEMORY       - Insufficient memory.
//          E_UNEXPECTED        - Unexpected exception.
//          E_FAIL              - Unexpected filesystem error.
//          
//          This function may return other errors expressed as HResults
//          returned from the filesystem.  
//
//
// IDiskQuotaControl::CreateEnumUsers -----------------------------------------
//
//      Creates an enumerator object for enumerating quota users on the volume.
//      The object created implements the IEnumDiskQuotaUsers interface.  
//      The object created supports the standard OLE IEnumXXXX functions.
//
//      Arguments:
//
//          rgpUserSids - Array of security ID (SID) pointers representing the
//              user objects to be included in the enumeration.  If this 
//              value is NULL, all user entries are enumerated.
//
//          cpSids - Number of items in the rgpUserSids array.  Ignored if 
//              rgpUserSids is NULL.
//
//
//          ppEnum - Address of IEnumDiskQuotaUsers pointer variable to receive
//              the address of the new enumerator.
//
//          fNameResolution - Flag indicating how the account information for
//              enumerated users is to be resolved.  See description in
//              AddUser for details.
//
//      Returns:
//          NOERROR             - Success.
//          ERROR_NOT_READY     - DiskQuotaControl object not initialized.
//          ERROR_ACCESS_DENIED - Insufficient access rights.
//          E_INVALIDARG        - ppEnum argument is NULL.
//          E_OUTOFMEMORY       - Insufficient memory.
//          E_UNEXPECTED        - Unexpected exception.
//
//
// IDiskQuotaControl::CreateUserBatch -----------------------------------------
//
//      Creates a batching object for optimizing updates to the quota settings
//      of multiple users simultaneously. See IDiskQuotaUserBatch for details.
//
//      Arguments:
//
//          ppBatch - Address of IDiskQuotaUserBatch pointer variable to 
//              receive the IDiskQuotaUserBatch interface pointer.
//
//      Returns:
//
//        NOERROR             - Success.
//        ERROR_NOT_READY     - DiskQuotaControl object not initialized.
//        ERROR_ACCESS_DENIED - Insufficient access rights.
//        E_INVALIDARG        - ppBatch argument is NULL.
//        E_OUTOFMEMORY       - Insufficient memory.
//        E_UNEXPECTED        - Unexpected exception.
//
//
// IDiskQuotaControl::InvalidateSidNameCache ----------------------------------
//
//      Invalidates the contents of the system's SID-Name cache so that 
//      subsequent requests for new user objects (IEnumDiskQuotaUsers::Next,
//      IDiskQuotaControl::FindUserSid and IDiskQuotaControl::FindUserName) 
//      must obtain user names from the network domain controller.  As names 
//      are obtained, they are again cached.
//
//      In general there is no reason to call this method.  It is included to 
//      provide a method for programmatically refreshing the entire SID-name
//      cache.
//
//      Arguments: None.
//
//      Returns:
//
//          NOERROR          - Success.
//          ERROR_NOT_READY  - DiskQuotaControl object not initialized.
//          E_FAIL           - SID/Name cache not available or couldn't obtain 
//                             exclusive lock on cache.
//          E_OUTOFMEMORY    - Insufficient memory.
//          E_UNEXPECTED     - Unexpected exception.
//
//
// IDiskQuotaControl::GiveUserNameResolutionPriority --------------------------
//
//      By default, quota user objects are serviced in the resolution queue in 
//      the order they were placed into the queue.  This function will promote
//      a specified user object to the head of the queue so that it is next in 
//      line for resolution.
//
//      Arguments:
//
//          pUser - Address of user object's IDiskQuotaUser interface.
//
//      Returns:
//
//        NOERROR         - Success.
//        ERROR_NOT_READY - DiskQuotaControl object not initialized.
//        S_FALSE         - Quota user object not in resolver queue.
//        E_UNEXPECTED    - Unexpected error.  Caught an exception or the 
//                          Sid-Name resolver hasn't been created.
//
//
// IDiskQuotaControl::ShutdownNameResolution ----------------------------------
//
//      The SID-Name resolver runs on a background thread to translate
//      user security IDs to user names.  When a quota control object is 
//      destroyed, this thread automatically terminates.  If you have a
//      situation where you're finished with the quota control object and
//      it is not be ready to be destroyed (other open ref counts),
//      this method may be called to shut down the background thread before
//      the object is destroyed.  Note that asynchronous name resolution will 
//      also cease once the thread terminates.  A subsequent call to 
//      CreateEnumUsers, AddUserSid, AddUserName, FindUserSid or FindUserName 
//      may re-create the resolver thread.
//      
//      Arguments: None.
//
//      Returns : Only returns NOERROR.
//
///////////////////////////////////////////////////////////////////////////////
#undef INTERFACE
#define INTERFACE IDiskQuotaControl

DECLARE_INTERFACE_(IDiskQuotaControl, IConnectionPointContainer)
{
    STDMETHOD(Initialize)(THIS_ 
        LPCWSTR pszPath, 
        BOOL bReadWrite) PURE;

    STDMETHOD(SetQuotaState)(THIS_ 
        DWORD dwState) PURE;

    STDMETHOD(GetQuotaState)(THIS_ 
        LPDWORD pdwState) PURE;

    STDMETHOD(SetQuotaLogFlags)(THIS_ 
        DWORD dwFlags) PURE;

    STDMETHOD(GetQuotaLogFlags)(THIS_ 
        LPDWORD pdwFlags) PURE;

    STDMETHOD(SetDefaultQuotaThreshold)(THIS_ 
        LONGLONG llThreshold) PURE;

    STDMETHOD(GetDefaultQuotaThreshold)(THIS_ 
        PLONGLONG pllThreshold) PURE;

    STDMETHOD(GetDefaultQuotaThresholdText)(THIS_
        LPWSTR pszText,
        DWORD cchText) PURE;

    STDMETHOD(SetDefaultQuotaLimit)(THIS_ 
        LONGLONG llLimit) PURE;

    STDMETHOD(GetDefaultQuotaLimit)(THIS_ 
        PLONGLONG pllLimit) PURE;

    STDMETHOD(GetDefaultQuotaLimitText)(THIS_
        LPWSTR pszText,
        DWORD cchText) PURE;

    STDMETHOD(AddUserSid)(THIS_ 
        PSID pUserSid, 
        DWORD fNameResolution,
        PDISKQUOTA_USER *ppUser) PURE; 

    STDMETHOD(AddUserName)(THIS_ 
        LPWSTR pszLogonName,
        DWORD fNameResolution,
        PDISKQUOTA_USER *ppUser) PURE; 

    STDMETHOD(DeleteUser)(THIS_ 
        PDISKQUOTA_USER pUser) PURE;

    STDMETHOD(FindUserSid)(THIS_ 
        PSID pUserSid, 
        DWORD fNameResolution,
        PDISKQUOTA_USER *ppUser) PURE;

    STDMETHOD(FindUserName)(THIS_ 
        LPCWSTR pszLogonName, 
        PDISKQUOTA_USER *ppUser) PURE;

    STDMETHOD(CreateEnumUsers)(THIS_ 
        PSID *rgpUserSids, 
        DWORD cpSids, 
        DWORD fNameResolution,
        PENUM_DISKQUOTA_USERS *ppEnum) PURE;

    STDMETHOD(CreateUserBatch)(THIS_ 
        PDISKQUOTA_USER_BATCH *ppBatch) PURE;

    STDMETHOD(InvalidateSidNameCache)(THIS) PURE;

    STDMETHOD(GiveUserNameResolutionPriority)(THIS_ 
        PDISKQUOTA_USER pUser) PURE;

    STDMETHOD(ShutdownNameResolution)(THIS_
        VOID) PURE;
};

typedef IDiskQuotaControl DISKQUOTA_CONTROL, *PDISKQUOTA_CONTROL;



///////////////////////////////////////////////////////////////////////////////
// IDiskQuotaEvents interface
//
// A client must implement this interface as a COM event sink in order to
// receive quota-related event notifications such as asynchronous account
// name resolution.  The interface functions are called by the quota
// control implementation whenever important quota events occur.  Currently,
// the only event supported is the asynchronous resolution of a user account's
// name information.
//
// IDiskQuotaEvents::OnUserNameChanged ----------------------------------------
//
//      Notifies client's connection sink whenever a user's SID has been 
//      asynchronously resolved so that the user's account container name, 
//      logon name and display name strings are available in the quota user 
//      object.
//
//      Arguments:
//
//          pUser - Address of IDiskQuotaUser interface for quota user object.
//                  It is not necessary to call Release() on this pointer.
//                  The DiskQuotaControl object controls the lifetime of the
//                  user object.
//
//      Returns:  Return value is ignored.
//  
///////////////////////////////////////////////////////////////////////////////
#undef  INTERFACE
#define INTERFACE IDiskQuotaEvents

DECLARE_INTERFACE_(IDiskQuotaEvents, IUnknown)
{
    STDMETHOD(OnUserNameChanged)(THIS_ 
        PDISKQUOTA_USER pUser) PURE;
};

typedef IDiskQuotaEvents DISKQUOTA_EVENTS, *PDISKQUOTA_EVENTS;


///////////////////////////////////////////////////////////////////////////////
// DiskQuotaEventSink
//
// Declaration for a class that implements IDiskQuotaEvents.  A client may
// implement this class as it is declared or create their own class.  The only
// requirement is that it implement IDiskQuotaEvents as a COM connection
// point.  See the COM documentation for details on connection points and
// connection point containers.
//
///////////////////////////////////////////////////////////////////////////////
class DiskQuotaEventSink : public IDiskQuotaEvents
{
    private:
        LONG  m_cRef;       // Interface reference count.

    public:
        DWORD m_dwCookie;   // Connection point cookie.

        DiskQuotaEventSink(VOID);
        ~DiskQuotaEventSink(VOID);

        //
        // IUnknown methods.
        //
        STDMETHODIMP QueryInterface(REFIID, LPVOID *);
        STDMETHODIMP_(ULONG) AddRef(VOID);
        STDMETHODIMP_(ULONG) Release(VOID);

        //
        // IDiskQuotaEvents
        //
        STDMETHODIMP OnUserNameChanged(PDISKQUOTA_USER pUser);
};


//=============================================================================
//=============================================================================
// ActiveX Control Description
//=============================================================================
//=============================================================================
//
// DSKQUOTA.DLL also provides an ActiveX control that performs much of the
// functionality found in the vtable interfaces IDiskQuotaControl, 
// IDiskQuotaUser and IDiskQuotaEvents.  The control is available through
// Visual Basic, VBScript and scripting hosts such as cscript and wscript.
//
// The following section describes the properties and methods for each
// OLE automation interface supported.
//
// ActiveX object ProgID = "Microsoft.DiskQuota.1"
// ActiveX object CLSID  = {7988B571-EC89-11cf-9C00-00AA00A14F56}
// Type library CLSID    = {7988B57C-EC89-11cf-9C00-00AA00A14F56}
// 
// The object supports 3 automation-compatible interfaces:
//
//      IID_DIDiskQuotaControl          [default]
//      IID_DIDiskQuotaUser
//      IID_DIDiskQuotaControlEvents    [default, source]
// 
//
// ----------------------------------------------------------------------------
// IID_DIDiskQuotaControl - Disk Quota Controller
//
// This interface is the default controlling interface for the DiskQuota
// ActiveX component.  It implements much the same functionality as 
// the vtable interface IDiskQuotaControl.
//
// Properties:
//
//      QuotaState
//
//          Desc:   The "state" of NTFS disk quotas on the volume.
//                  The state can be either "disabled", "tracking quota usage"
//                  or "enforcing quota limits".  Enforcement implies
//                  tracking.
//
//          Type:   QuotaStateConstants (enumeration)
//
//          Domain: dqStateDisable   (0)
//                  qsStateTrack     (1)
//                  qsStateEnforce   (2)
//
//      QuotaFileIncomplete (read only)
//
//          Desc:   Determines if the quota file on the volume is marked
//                  as "incomplete".  An incomplete volume is usually the
//                  result of a disabled quota system.
//
//          Type:   VARIANT_BOOL
//
//          Domain: True/False
//
//      QuotaFileRebuilding (read only)
//
//          Desc:   Determines if the quota file on the volume is being
//                  rebuilt.  Rebuilding automatically occurs whenever
//                  quotas are enabled on the system or when one or more
//                  user entries are marked for deletion.
//
//          Type:   VARIANT_BOOL
//
//          Domain: True/False
//
//      LogQuotaThreshold
//
//          Desc:   Indicates if a system event log entry should be created
//                  whenever a user exceeds their assigned quota warning
//                  threshold.
//
//          Type:   VARIANT_BOOL
//
//          Domain: True/False
//
//      LogQuotaLimit
//
//          Desc:   Indicates if a system event log entry should be created
//                  whenever a user exceeds their assigned quota limit.
//
//          Type:   VARIANT_BOOL
//
//          Domain: True/False
//
//      DefaultQuotaThreshold
//
//          Desc:   The default warning threshold value assigned to new users
//                  of the volume.
//
//          Type:   double
//
//          Domain: Value is expressed in bytes.
//
//      DefaultQuotaThresholdText (read only)
//
//          Desc:   The default threshold value expressed as a text
//                  string suitable for display.  The recipient of
//                  the string is responsible for deleting the string
//                  using SysFreeString().
//
//          Type:   BSTR
//
//          Domain: Threshold value formatted as a decimal number
//                  and appended with a units suffix.
//
//                  i.e.:  "10.5 MB"
//                         "No Limit" if unlimited.
//
//      DefaultQuotaLimit
//
//          Desc:   The default quota limit value assigned to new users
//                  of the volume.
//
//          Type:   double
//
//          Domain: Value is expressed in bytes.
//                  -1 is special case meaning "no limit".
//
//      DefaultQuotaLimitText (read only)
//
//          Desc:   The default quota limit value expressed as a text
//                  string suitable for display.  The recipient of
//                  the string is responsible for deleting the string
//                  using SysFreeString().
//
//          Type:   BSTR
//
//          Domain: Limit value formatted as a decimal number
//                  and appended with a units suffix.
//
//                  i.e.:  "10.5 MB"
//                         "No Limit" if unlimited.
//
//      UserNameResolution
//
//          Desc:   Controls the behavior of the security ID-to-Name
//                  resolution processing.  The process may be bypassed,
//                  performed synchronously or performed asynchronously.
//                  If Asynchronous name resolution is chosen, the caller
//                  must implement the DIDiskQuotaControlEvents dispatch 
//                  interface to receive notification when the name has
//                  been resolved.
//
//          Type:   UserNameResolutionConstants (enumeration)
//
//          Domain: dqResolveNone      (0) - No name information
//                  dqResolveSync      (1) - Resolve synchronously
//                  dqResolveAsync     (2) - Resolve asynchronously
//
// Methods:
//
//      Initialize
//
//          Desc:   Initializes a DiskQuota object for a given NTFS volume.
//                  This method must be called before any other methods.
//                  If unsuccessful, any other method calls will return
//                  ERROR_NOT_READY as an HResult.
//
//                        >>>>>>  NOTE  <<<<<<<
//
//          Accessing quota information on remote volumes is not 
//          supported for NT5 Beta 1.  Remote volume support will be
//          added after Beta 1.
//
//
//          Arguments:
//              pPath [in] - Contains path of volume to initialize.
//
//                  Type:   BSTR
//
//                  Domain: Volume root name. i.e. "C:\"
//
//              bReadWrite [in] - Indicates if "write" access is desired.  
//
//                  Type:   VARIANT_BOOL
//
//                  Domain: False = Read-only
//                          True  = Read-Write
//
//          Returns: Nothing.
//
//          Errors:  See IDiskQuotaControl::Initialize.
//
//
//      AddUser
//
//          Desc:   Add a new user entry to the volume's quota file.
//                  If the user already exists, the object for the existing
//                  user is returned.
//
//          Arguments:
//              pLogonName [in] - User's account logon name.
//
//                  Type:   BSTR
//
//                  Domain: Windows NT account logon names.
//
//                          ex:  "THEDOMAIN\jqpublic" (NT4 & NT5 w/o DS info)
//                               "jqpublic@acme.com"  (NT5 with DS info)
//
//          Returns:
//              Reference to newly added user object (DIDiskQuotaUser).
//
//          Errors:  See IDiskQuotaControl::AddUserName
//
//
//      DeleteUser
//
//          Arguments:
//              pUser [in] - Reference to user object to be marked for deletion.
//
//                  Type:   DIDiskQuotaUser
//
//                  Domain: Pointer to DIDiskQuotaUser interface.
//
//          Returns: Nothing
//
//          Errors:  See IDiskQuotaControl::DeleteUser
//
//
//      FindUser
//
//          Desc:   Locate user entry in the volume's quota file.
//
//          Arguments:
//              pLogonName [in] - User's account logon name.
//
//                  Type:   BSTR
//
//                  Domain: Windows NT account logon names.
//
//                          ex:  "THEDOMAIN\jqpublic" (NT4 & NT5 w/o DS info)
//                               "jqpublic@acme.com"  (NT5 with DS info)
//
//          Returns:
//              Reference to located user object (DIDiskQuotaUser).
//
//          Errors:  See IDiskQuotaControl::FindUserName
//
//
//      InvalidateSidNameCache
//
//          Desc:   Invalidates the contents of the Security ID-User name
//                  cache.  Following cache invalidation, subsequent 
//                  creations of user objects will need to resolve and
//                  re-cache account information.
//      
//          Arguments: None
//
//          Returns:  Nothing
//
//          Errors:  See IDiskQuotaControl::InvalidateSidNameCache
//
//
//      GiveUserNameResolutionPriority
//
//          Desc:   When UserNameResolution is dqResolveAsync, 
//                  user entry objects with unresolved security IDs are
//                  automatically placed on a queue, waiting to be
//                  resolved.  The resolution process occurs on a background
//                  thread.  Normally objects are processed on a FIFO
//                  basis (queue).  This method moves the specified user
//                  object to the front of the line so to speak.  This
//                  can be helpful when a user interface is being
//                  updated dynamically through IDiskQuotaControlEvent
//                  notifications.
//
//          Arguments:
//              pUser - Reference to user object to be promoted.
//
//          Returns: Nothing.
//
//          Errors:  See IDiskQuotaControl::GiveUserNameResolutionPriority
//
//
//      ShutdownNameResolution
//
//          Desc:   The SID-Name resolver runs on a background thread to 
//                  translate user security IDs to user names.  When a quota 
//                  control object is destroyed, this thread automatically 
//                  terminates.  In situations where you're finished 
//                  with the quota control object and it is not be ready to be 
//                  destroyed (i.e. other open ref counts), this method may be 
//                  called to shut down the background thread before the object
//                  is destroyed.  Note that asynchronous name resolution will 
//                  also cease once the thread terminates.  A subsequent call
//                  to CreateEnumUsers, AddUserSid, AddUserName, FindUserSid or
//                  FindUserName may re-create the resolver thread.
//      
//          Arguments: None.
//
//          Returns : Nothing.
//
//          Errors: None.
//
//
// ----------------------------------------------------------------------------
// IID_DIDiskQuotaUser - Disk Quota user entry object.
//
// This interface represents a user entry in a volume's quota information.
// It implements much the same functionality as the vtable interface 
// IDiskQuotaUser.  Disk Quota user objects can only be created through
// a Disk Quota controller object (enumeration, AddUser, FindUser etc).
//
// Properties:
//
//      ID (read only)
//
//          Desc:   A unique integer identifier for the user object.
//                  ID's are unique only to the dskquota module instance
//                  within a given process.  They are intended to be used
//                  with languages that don't support pointers.  For instance,
//                  in Visual Basic you might want to visually represent a set 
//                  of disk quota users in a listview.  One possibility is to 
//                  keep an array of DIDiskQuotaUser pointers and store the 
//                  object IDs in the userdata (LPARAM) of each listview item.
//
//          Type:   long
//
//          Domain: 0 through MAXLONG
//
//
//      AccountContainerName (read only)
//
//          Desc:   The account container name for the user's account.
//
//          Type:   BSTR
//
//          Domain: Windows NT network domain names.
//
//                    ex:  NT4 & NT5 w/o DS info:
//                            "THEDOMAIN"
//      
//                         NT5 with DS info:
//                            "usa.acme.com/toys/engineering"
//
//
//      LogonName (read only)
//
//          Desc:   The account logon name for the user's account.
//
//          Type:   BSTR
//
//          Domain: Windows NT network account logon names.
//
//                    ex:  NT4 & NT5 w/o DS info:
//                            "THEDOMAIN\jqpublic"
//      
//                         NT5 with DS info:
//                            "jqpublic@acme.com"
//
//      DisplayName (read only)
//
//          Desc:   The "friendly" name for the user's account.
//
//          Type:   BSTR
//
//          Domain: Whatever string is assigned to the account.
//                  May not exist.
//
//                    ex:  "John Q. Public"
//
//      QuotaThreshold
//
//          Desc:   The user's quota warning threshold.
//
//          Type:   double
//
//          Domain: Value expressed in bytes.
//
//      QuotaThresholdText (read only)
//
//          Desc:   User's threshold value formatted as a decimal number
//                  and appended with a units suffix.
//
//          Type:   BSTR
//
//          Domain: i.e. "10.5 MB"
//                       "No Limit" if unlimited.
//
//      QuotaLimit
//
//          Desc:   The user's quota limit.
//
//          Type:   double
//
//          Domain: Value expressed in bytes.
//
//      QuotaLimitText (read only)
//
//          Desc:   User's limit value formatted as a decimal number
//                  and appended with a units suffix.
//
//          Type:   BSTR
//
//          Domain: i.e. "10.5 MB"
//                       "No Limit" if unlimited.
//
//      QuotaUsed (read only)
//
//          Desc:   The user's quota "used" value.
//
//          Type:   double
//
//          Domain: Value expressed in bytes.
//
//      QuotaUsedText (read only)
//
//          Desc:   User's quota "used" value formatted as a decimal number
//                  and appended with a units suffix.
//
//          Type:   BSTR
//
//          Domain: i.e. "10.5 MB"
//                       "No Limit" if unlimited.
//
//      AccountStatus (read only)
//
//          Desc:   Status of the user's account information.
//
//          Type:   AccountStatusConstants (enumeration)
//
//          Domain: dqAcctResolved    (0) - Name information available
//                  dqAcctUnavailable (1) - Can't get name information
//                  dqAcctDeleted     (2) - Account has been deleted
//                  dqAcctInvalid     (3) - Account is invalid
//                  dqAcctUnknown     (4) - Account is not known
//                  dqAcctUnresolved  (5) - Name information not yet resolved
//
// Methods:
//
//      Invalidate
//
//          Desc:   Invalidates the information cached in the user object.
//                  Following a call to Invalidate, the next call for 
//                  a quota-related property refreshes the information from
//                  the NTFS volume.
//
//          Arguments: None.
//
//          Returns: Nothing.
//
//          Errors: None. Always returns S_OK.
//
//
// ----------------------------------------------------------------------------
// IID_DIDiskQuotaControlEvents - Disk Quota Controller Events source.
//
// This interface is the default source interface for the DiskQuota
// ActiveX component.  It is not implemented in the DiskQuota object.  It
// merely describes the interface that must be implemented by clients if they
// are to receive user-name-update notifications for asynchronous resolution
// of user object name information.
//
// Properties:  None.
//
// Methods:
//
//      OnUserNameChanged
//
//          Desc:   Called by the DiskQuota object whenever an asynchronous
//                  name resolution operation has completed for a single user
//                  object.  This notification indicates that the user's
//                  DomainName, AccountName and Name properties contain
//                  valid information.
//                  It is not necessary to call Release() on this pointer.
//                  The DiskQuotaControl object controls the lifetime of the
//                  user object.
//
//          Arguments:
//              pUser - Reference to the user object associated with the event.
//
//          Returns: Ignored by DiskQuota object.
//
//          Errors:  Ignored by DiskQuota object.
//
//

#endif // __DSKQUOTA_H
