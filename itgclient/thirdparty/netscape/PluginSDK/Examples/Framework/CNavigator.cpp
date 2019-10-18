//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//
// NetscapePlugin.cpp
//
//
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
#include "CNavigator.h"

static const int kVersionSupportsNotify = 7;

//======================================================================
//		CNavigator::CNavigator()
//======================================================================

CNavigator::CNavigator( NPP inInstanceRef )
:	mInstance( inInstanceRef )
{
	int pluginMajor, pluginMinor, navMajor, navMinor;
	NPN_Version( &pluginMajor, &pluginMinor, &navMajor, &navMinor );
	
	mNavMinorVersion = navMinor;
}

//======================================================================
//		CNavigator::~CNavigator()
//======================================================================

CNavigator::~CNavigator()
{
}

//------------------------------------------------------------------------------------
// CNavigator::GetURL
//------------------------------------------------------------------------------------
NPError
CNavigator::GetURL(const char* url, const char* target, void* notifyData)
{
	if( notifyData && (mNavMinorVersion >= kVersionSupportsNotify ) ) {
		return NPN_GetURLNotify( mInstance, url, target, notifyData );
	}
	return NPN_GetURL( mInstance, url, target );
}

//------------------------------------------------------------------------------------
// CNavigator::PostURL
//------------------------------------------------------------------------------------
NPError
CNavigator::PostURL(const char* url, const char* target, 
								uint32 len, const char* buf,
								NPBool file, void* notifyData)
{
	if( notifyData && (mNavMinorVersion >= kVersionSupportsNotify ) ) {
		return NPN_PostURLNotify( mInstance, url, target, len, buf, file, notifyData );
	}
	return NPN_PostURL( mInstance, url, target, len, buf, file );

}

								
//------------------------------------------------------------------------------------
// CNavigator::NewStream
//------------------------------------------------------------------------------------
NPError
CNavigator::NewStream( NPMIMEType type, const char* target, NPStream** stream)
{
	return NPN_NewStream( mInstance, type, target, stream );
}

//------------------------------------------------------------------------------------
// CNavigator::NavWrite
//------------------------------------------------------------------------------------
int32
CNavigator::Write(NPStream* stream, int32 len, void* buffer)
{
	return NPN_Write( mInstance, stream, len, buffer );
}

//------------------------------------------------------------------------------------
// CNavigator::NavDestroyStream
//------------------------------------------------------------------------------------
NPError
CNavigator::DestroyStream(NPStream* stream, NPReason reason)
{
	return NPN_DestroyStream( mInstance, stream, reason );
}

		
//------------------------------------------------------------------------------------
// CNavigator::NavStatus
//------------------------------------------------------------------------------------
void
CNavigator::Status(const char* message)
{
	NPN_Status( mInstance, message );
}

//------------------------------------------------------------------------------------
// CNavigator::NavUserAgent
//------------------------------------------------------------------------------------
const char*
CNavigator::UserAgent()
{
	return NPN_UserAgent( mInstance );
}


//------------------------------------------------------------------------------------
// CNavigator::NavGetJavaPeer
//------------------------------------------------------------------------------------
jref
CNavigator::GetJavaPeer()
{
	return NPN_GetJavaPeer( mInstance );
}


