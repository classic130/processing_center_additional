// ErrCppD.h--------------------------------------------------------------------
// This defines an array of mapi error codes.
// Include this file only once in your code for the entire project.
//
// Copyright 1986 - 1998 Microsoft Corporation.  All Rights Reserved.
// -----------------------------------------------------------------------------

#ifndef _ERRCPPD_H_
#define _ERRCPPD_H_

// -----------------------------------------------------------------------------

static IDList MAPIErrors[] = 
{
    (ULONG) SUCCESS_SUCCESS,    "SUCCESS_SUCCESS",
    (ULONG) MAPI_E_CALL_FAILED, "MAPI_E_CALL_FAILED",
    (ULONG) MAPI_E_NOT_ENOUGH_MEMORY,   "MAPI_E_NOT_ENOUGH_MEMORY",
    (ULONG) MAPI_E_INVALID_PARAMETER,   "MAPI_E_INVALID_PARAMETER",
    (ULONG) MAPI_E_INTERFACE_NOT_SUPPORTED, "MAPI_E_INTERFACE_NOT_SUPPORTED",
    (ULONG) MAPI_E_NO_ACCESS,   "MAPI_E_NO_ACCESS",
    (ULONG) MAPI_E_NO_SUPPORT,  "MAPI_E_NO_SUPPORT",
    (ULONG) MAPI_E_BAD_CHARWIDTH,   "MAPI_E_BAD_CHARWIDTH",
    (ULONG) MAPI_E_STRING_TOO_LONG, "MAPI_E_STRING_TOO_LONG",
    (ULONG) MAPI_E_UNKNOWN_FLAGS,   "MAPI_E_UNKNOWN_FLAGS",
    (ULONG) MAPI_E_INVALID_ENTRYID, "MAPI_E_INVALID_ENTRYID",
    (ULONG) MAPI_E_INVALID_OBJECT,  "MAPI_E_INVALID_OBJECT",
    (ULONG) MAPI_E_OBJECT_CHANGED,  "MAPI_E_OBJECT_CHANGED",
    (ULONG) MAPI_E_OBJECT_DELETED,  "MAPI_E_OBJECT_DELETED",
    (ULONG) MAPI_E_BUSY,    "MAPI_E_BUSY",
    (ULONG) MAPI_E_NOT_ENOUGH_DISK, "MAPI_E_NOT_ENOUGH_DISK",
    (ULONG) MAPI_E_NOT_ENOUGH_RESOURCES,    "MAPI_E_NOT_ENOUGH_RESOURCES",
    (ULONG) MAPI_E_NOT_FOUND,   "MAPI_E_NOT_FOUND",
    (ULONG) MAPI_E_VERSION, "MAPI_E_VERSION",
    (ULONG) MAPI_E_LOGON_FAILED,    "MAPI_E_LOGON_FAILED",
    (ULONG) MAPI_E_SESSION_LIMIT,   "MAPI_E_SESSION_LIMIT",
    (ULONG) MAPI_E_USER_CANCEL, "MAPI_E_USER_CANCEL",
    (ULONG) MAPI_E_UNABLE_TO_ABORT, "MAPI_E_UNABLE_TO_ABORT",
    (ULONG) MAPI_E_NETWORK_ERROR,   "MAPI_E_NETWORK_ERROR",
    (ULONG) MAPI_E_DISK_ERROR,  "MAPI_E_DISK_ERROR",
    (ULONG) MAPI_E_TOO_COMPLEX, "MAPI_E_TOO_COMPLEX",
    (ULONG) MAPI_E_BAD_COLUMN,  "MAPI_E_BAD_COLUMN",
    (ULONG) MAPI_E_EXTENDED_ERROR,  "MAPI_E_EXTENDED_ERROR",
    (ULONG) MAPI_E_COMPUTED,    "MAPI_E_COMPUTED",
    (ULONG) MAPI_E_END_OF_SESSION,  "MAPI_E_END_OF_SESSION",
    (ULONG) MAPI_E_UNKNOWN_ENTRYID, "MAPI_E_UNKNOWN_ENTRYID",
    (ULONG) MAPI_E_MISSING_REQUIRED_COLUMN, "MAPI_E_MISSING_REQUIRED_COLUMN",
    (ULONG) MAPI_W_NO_SERVICE,  "MAPI_W_NO_SERVICE",
    (ULONG) MAPI_E_BAD_VALUE,   "MAPI_E_BAD_VALUE",
    (ULONG) MAPI_E_INVALID_TYPE,    "MAPI_E_INVALID_TYPE",
    (ULONG) MAPI_E_TYPE_NO_SUPPORT, "MAPI_E_TYPE_NO_SUPPORT",
    (ULONG) MAPI_E_UNEXPECTED_TYPE, "MAPI_E_UNEXPECTED_TYPE",
    (ULONG) MAPI_E_TOO_BIG, "MAPI_E_TOO_BIG",
    (ULONG) MAPI_W_ERRORS_RETURNED, "MAPI_W_ERRORS_RETURNED",
    (ULONG) MAPI_E_UNABLE_TO_COMPLETE,  "MAPI_E_UNABLE_TO_COMPLETE",
    (ULONG) MAPI_E_TABLE_EMPTY, "MAPI_E_TABLE_EMPTY",
    (ULONG) MAPI_E_TABLE_TOO_BIG,   "MAPI_E_TABLE_TOO_BIG",
    (ULONG) MAPI_E_INVALID_BOOKMARK,    "MAPI_E_INVALID_BOOKMARK",
    (ULONG) MAPI_W_POSITION_CHANGED,    "MAPI_W_POSITION_CHANGED",
    (ULONG) MAPI_W_APPROX_COUNT,    "MAPI_W_APPROX_COUNT",
    (ULONG) MAPI_E_WAIT,    "MAPI_E_WAIT",
    (ULONG) MAPI_E_CANCEL,  "MAPI_E_CANCEL",
    (ULONG) MAPI_E_NOT_ME,  "MAPI_E_NOT_ME",
    (ULONG) MAPI_W_CANCEL_MESSAGE,  "MAPI_W_CANCEL_MESSAGE",
    (ULONG) MAPI_E_CORRUPT_STORE,   "MAPI_E_CORRUPT_STORE",
    (ULONG) MAPI_E_NOT_IN_QUEUE,    "MAPI_E_NOT_IN_QUEUE",
    (ULONG) MAPI_E_NO_SUPPRESS, "MAPI_E_NO_SUPPRESS",
    (ULONG) MAPI_E_COLLISION,   "MAPI_E_COLLISION",
    (ULONG) MAPI_E_NOT_INITIALIZED, "MAPI_E_NOT_INITIALIZED",
    (ULONG) MAPI_E_NON_STANDARD,    "MAPI_E_NON_STANDARD",
    (ULONG) MAPI_E_NO_RECIPIENTS,   "MAPI_E_NO_RECIPIENTS",
    (ULONG) MAPI_E_SUBMITTED,   "MAPI_E_SUBMITTED",
    (ULONG) MAPI_E_HAS_FOLDERS, "MAPI_E_HAS_FOLDERS",
    (ULONG) MAPI_E_HAS_MESSAGES,    "MAPI_E_HAS_MESSAGES",
    (ULONG) MAPI_E_FOLDER_CYCLE,    "MAPI_E_FOLDER_CYCLE",
    (ULONG) MAPI_W_PARTIAL_COMPLETION,  "MAPI_W_PARTIAL_COMPLETION",
    (ULONG) MAPI_E_AMBIGUOUS_RECIP, "MAPI_E_AMBIGUOUS_RECIP",
    (ULONG) E_NOTIMPL,      "E_NOTIMPL",
    (ULONG) E_UNEXPECTED,   "E_UNEXPECTED",
    (ULONG) E_OUTOFMEMORY,  "E_OUTOFMEMORY",
    (ULONG) E_INVALIDARG,   "E_INVALIDARG",
    (ULONG) E_NOINTERFACE,  "E_NOINTERFACE",
    (ULONG) E_POINTER,      "E_POINTER",
    (ULONG) E_HANDLE,       "E_HANDLE",
    (ULONG) E_ABORT,        "E_ABORT",
    (ULONG) E_FAIL,         "E_FAIL",
    (ULONG) E_ACCESSDENIED, "E_ACCESSDENIED",
};

// -----------------------------------------------------------------------------

#endif  //_ERRCPPD_H_
