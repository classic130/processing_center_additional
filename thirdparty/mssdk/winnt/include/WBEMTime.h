//***************************************************************************
//
//  wbemtime.h
//
//  Purpose: declares the WBEMTime and WBEMTimeSpan objects which are 
//  similar to the MFC CTime and CTimeSpan objects.  The WBEM versions
//  are capable of storing down to the nsec and also have functions for
//  Creating from and getting BSTRs.
//
//  Note; The current implementation of WBEMTime does not support datas 
//  before 1970;
//
// Copyright 1998 Microsoft Corporation
//
//***************************************************************************
#if _MSC_VER > 1000
#pragma once
#endif

#ifndef WBEMTIME_HEADERFILE_IS_INCLUDED
#define WBEMTIME_HEADERFILE_IS_INCLUDED

#define INVALID_TIME 0xffffffffffffffff
#define DECPOS 14

#ifdef USE_POLARITY
#include <polarity.h>
#else
#define POLARITY
#endif

#include <time.h>

///////////////////////////////////////////////////////////////////////////
// WBEMTimeSpan - This class holds time span values. 

class POLARITY WBEMTimeSpan 
{
public:
    WBEMTimeSpan(){m_Time = INVALID_TIME;};
    WBEMTimeSpan(BSTR bstrWbemFormat){*this = bstrWbemFormat;};
    WBEMTimeSpan(int iDays, int iHours, int iMinutes, int iSeconds, 
                    int iMSec=0, int iUSec=0, int iNSec=0);
    WBEMTimeSpan(const FILETIME &ft){*this = ft;};
    WBEMTimeSpan(const time_t & t){*this = t;};
    const WBEMTimeSpan &  operator=(BSTR pWbemFormat); 
    const WBEMTimeSpan &  operator=(const FILETIME &ft);
    const WBEMTimeSpan &  operator=(const time_t & t);
    WBEMTimeSpan operator+(const WBEMTimeSpan &uAdd);
    const WBEMTimeSpan &  operator+=(const WBEMTimeSpan &uAdd){m_Time += uAdd.m_Time;return *this;};
    BOOL operator==(const WBEMTimeSpan & a){return m_Time == a.m_Time;}; 
    BOOL operator < (const WBEMTimeSpan & a){return m_Time < a.m_Time;}; 
    BOOL operator <= (const WBEMTimeSpan & a){return m_Time <= a.m_Time;}; 
    BOOL operator >(const WBEMTimeSpan & a){return m_Time > a.m_Time;}; 
    BOOL operator >=(const WBEMTimeSpan & a){return m_Time >= a.m_Time;}; 


    BSTR GetBSTR(void);
    BOOL Gettime_t(time_t * ptime_t);
    BOOL GetFILETIME(FILETIME * pst);

private:
    __int64 m_Time;
    friend class WBEMTime;
};

///////////////////////////////////////////////////////////////////////////
// WBEMTime - This class holds time values. 

class POLARITY WBEMTime 
{
public:
    WBEMTime(){m_uTime = INVALID_TIME;};
    WBEMTime(BSTR bstrHMMSFormat){*this = bstrHMMSFormat;};
    WBEMTime(const SYSTEMTIME &st){*this = st;};
    WBEMTime(const FILETIME &ft){*this = ft;};
    WBEMTime(const struct tm tmin){*this = tmin;};
    WBEMTime(const time_t & t){*this = t;};
    const WBEMTime & operator=(BSTR bstrHMMSFormat); 
    const WBEMTime & operator=(const SYSTEMTIME &st);
    const WBEMTime & operator=(const FILETIME &ft);
    const WBEMTime & operator=(struct tm tmin);
    const WBEMTime & operator=(const time_t & t);
    WBEMTime operator+(const WBEMTime &uAdd);
    const WBEMTime & operator+=(const WBEMTime &uAdd){m_uTime += uAdd.m_uTime;return *this;};
    const WBEMTime & operator+=(const WBEMTimeSpan &ts){m_uTime += ts.m_Time;return *this;};
    WBEMTimeSpan operator-(const WBEMTime & sub);
    BOOL operator==(const WBEMTime & a){return m_uTime == a.m_uTime;}; 
    BOOL operator < (const WBEMTime & a){return m_uTime < a.m_uTime;}; 
    BOOL operator <= (const WBEMTime & a){return m_uTime <= a.m_uTime;}; 
    BOOL operator >(const WBEMTime & a){return m_uTime > a.m_uTime;}; 
    BOOL operator >=(const WBEMTime & a){return m_uTime >= a.m_uTime;}; 

    BSTR GetBSTR(void);
    BOOL GetStructtm(struct tm * ptm);
    BOOL Gettime_t(time_t * ptime_t);
    BOOL GetSYSTEMTIME(SYSTEMTIME * pst);
    BOOL GetFILETIME(FILETIME * pst);

    BOOL SetDMTF(BSTR wszText);
    BSTR GetDMTF(BOOL bLocal = FALSE);

    void Clear( void ){m_uTime = INVALID_TIME;};

private:
    unsigned __int64 m_uTime;
};


#endif
