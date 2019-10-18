//=================================================================
//
// Instance.h - Definition of CInstance class
//
// Copyright 1997, 1998 Microsoft Corporation
//
//=================================================================

#if _MSC_VER > 1000
#pragma once
#endif

#ifndef _INSTANCE_H_
#define _INSTANCE_H_

#include "FWcommon.h"
#include "ThreadBase.h"
#include <chstring.h>
#include <wbemtypes.h>
#include <wbemtime.h>
#include "MethodContext.h"


///////////////////////////////////////////
//
// CLASS CInstance
//
// base instance class
// encapsulation of IWbemClassObject 
///////////////////////////////////////////
class POLARITY CInstance
{
	public:
		CInstance(IWbemClassObject* piClassObject, MethodContext*  pMethodContext);
		virtual ~CInstance();

		// AddRef/Release
		ULONG	AddRef( void );
		ULONG	Release( void );

		// get and set for various data types
		bool SetCHString(const CHString& name,  const CHString& str);
		bool SetDWORD(const CHString& name,  DWORD d);
		bool Setbool(const CHString& name,  bool  b);
		bool SetVariant( const CHString& name,  const VARIANT& variant );
		bool SetCharSplat( const CHString& name,  const char* pStr);
		bool SetWCHARSplat( const CHString& name,  const WCHAR* pStr);
		bool SetDateTime( const CHString& name,  const WBEMTime& wbemtime );
		bool SetTimeSpan( const CHString& name,  const WBEMTimeSpan& wbemtimespan );
		bool SetWBEMINT64( const CHString& name, const WBEMINT64& wbemint64 );
		bool SetWBEMINT64( const CHString& name, const __int64 i64Value ) { char szBuff[22]; _i64toa(i64Value, szBuff, 10); return SetWBEMINT64(name, szBuff); }
		bool SetWBEMINT16( const CHString& name, const WBEMINT16& wbemint16 );
		bool SetByte( const CHString& name, BYTE b );

		bool GetCHString(const CHString& name,  CHString& str)     const; 
        bool GetWCHAR(const CHString& name,  WCHAR **pW) const;
		bool GetDWORD(const CHString& name,  DWORD& d)          const;
		bool Getbool(const CHString& name,  bool&  b)          const;
		bool GetVariant( const CHString& name, VARIANT& variant ) const;
		bool GetDateTime( const CHString& name,  WBEMTime& wbemtime ) const;
		bool GetTimeSpan( const CHString& name,  WBEMTimeSpan& wbemtimespan ) const;
		bool GetWBEMINT64( const CHString& name, WBEMINT64& wbemint64 ) const;
		bool GetWBEMINT64( const CHString& name, __int64& i64Value ) { CHString s; bool b = GetWBEMINT64(name, s); i64Value = _atoi64(s); return b; }
		bool GetWBEMINT16( const CHString& name, WBEMINT16& wbemint16 ) const;
		bool GetByte( const CHString& name, BYTE& b ) const;

		HRESULT Commit(void);
      bool CInstance::IsNull(const CHString& name) const;
		
		IWbemClassObject* GetClassObjectInterface();
		MethodContext*	  GetMethodContext() const;

	protected:
		void LogError(const char* errorStr, const char *pFunctionName, const char* pArgs = NULL, HRESULT hError = -1) const;

		IWbemClassObject*	m_piClassObject;
		MethodContext*		m_pMethodContext;
		ULONG				m_nRefCount;
};

#endif