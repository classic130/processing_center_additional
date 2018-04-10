/*****************************************************************************
*
* Copyright (c) 1998  Microsoft Corporation
*
* Module Name:
*
*    tapi3err.h
*
* Abstract:
*
*    Error Notifications for TAPI 3.0
*
*****************************************************************************/

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __TAPI3ERR_H__
#define __TAPI3ERR_H__

//
//  Values are 32 bit values layed out as follows:
//
//   3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
//   1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
//  +---+-+-+-----------------------+-------------------------------+
//  |Sev|C|R|     Facility          |               Code            |
//  +---+-+-+-----------------------+-------------------------------+
//
//  where
//
//      Sev - is the severity code
//
//          00 - Success
//          01 - Informational
//          10 - Warning
//          11 - Error
//
//      C - is the Customer code flag
//
//      R - is a reserved bit
//
//      Facility - is the facility code
//
//      Code - is the facility's status code
//
//
// Define the facility codes
//


//
// Define the severity codes
//


//
// MessageId: T3_NOERROR
//
// MessageText:
//
//  The call was successfull.
//
#define T3_NOERROR                       ((HRESULT)0x00040000L)

//--------------------------------------------------------------------------
//     Core TAPI Error messages
//--------------------------------------------------------------------------

//--------------------------------------------------------------------------
//     Call Center Error messages
//--------------------------------------------------------------------------

//
// MessageId: TAPI_E_CALLCENTER_GROUP_REMOVED
//
// MessageText:
//
//  The ACD Proxy has removed this Group. Operations on this object are invalid.
//
#define TAPI_E_CALLCENTER_GROUP_REMOVED  ((HRESULT)0x80040001L)

//
// MessageId: TAPI_E_CALLCENTER_QUEUE_REMOVED
//
// MessageText:
//
//  The ACD Proxy has removed this Queue. Operations on this object are invalid.
//
#define TAPI_E_CALLCENTER_QUEUE_REMOVED  ((HRESULT)0x80040002L)

//
// MessageId: TAPI_E_CALLCENTER_NO_AGENT_ID
//
// MessageText:
//
//  The Agent object was created with CreateAgent. It does not have an ID, use CreateAgentWithID.
//
#define TAPI_E_CALLCENTER_NO_AGENT_ID    ((HRESULT)0x80040003L)

//--------------------------------------------------------------------------
//     Terminal Specific Error messages
//--------------------------------------------------------------------------

//
// MessageId: T3_E_TERMINAL_PEER
//
// MessageText:
//
//  The peer for one of these bridge terminals has already been assigned.
//
#define T3_E_TERMINAL_PEER               ((HRESULT)0x80040004L)

//
// MessageId: T3_E_PEER_NOT_SET
//
// MessageText:
//
//  The peer for this bridge terminal must be set to complete this operation.
//
#define T3_E_PEER_NOT_SET                ((HRESULT)0x80040005L)


//--------------------------------------------------------------------------
//     Media Service Provider Error messages
//--------------------------------------------------------------------------
#endif // #ifndef __TAPI3ERR_H__
