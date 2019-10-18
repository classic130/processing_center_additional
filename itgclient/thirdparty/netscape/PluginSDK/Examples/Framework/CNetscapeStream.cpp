//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//
// CNetscapeStream.cpp
//
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
#include "CNetscapeStream.h"

#include <string.h>

const long CNetscapeStream::kMaxBufSize = 0X0FFFFFFF;

//======================================================================
//		CNetscapeStream::CNetscapeStream
//======================================================================

CNetscapeStream::CNetscapeStream( NPMIMEType type, NPStream* stream, NPBool seekable, uint16 stype )
:	mSourceStream( stream ),
	mMIMEType( 0 ),
	mSeekable( seekable ),
	mStreamType( stype )
{
	mSourceStream->pdata = (void*) this;
	
	short mimeLength = strlen( type );
	mMIMEType = (char*) NPN_MemAlloc( mimeLength + 1 );
	strcpy( mMIMEType, type );
}

//======================================================================
//		CNetscapeStream::~CNetscapeStream
//======================================================================

CNetscapeStream::~CNetscapeStream()
{
	mSourceStream->pdata = 0;
	NPN_MemFree( mMIMEType );
}

//======================================================================
//		CNetscapeStream::WriteReady
//======================================================================
int32
CNetscapeStream::WriteReady() 
{
	return kMaxBufSize; 
}

//======================================================================
//		CNetscapeStream::Write
//======================================================================
int32
CNetscapeStream::Write( int32 offset, int32 len, void *buffer ) 
{
	return len;
}

//======================================================================
//		CNetscapeStream::Finish
//======================================================================
NPError
CNetscapeStream::Finish( NPError reason ) 
{
	return NPERR_NO_ERROR;
}

//======================================================================
//		CNetscapeStream::CNetscapeStream
//======================================================================
void
CNetscapeStream::StreamAsFile( const char* fname ) 
{ 
}


//======================================================================
//		CNetscapeStream::GetURL
//======================================================================

const char*
CNetscapeStream::GetURL() const 
{ 
	if( mSourceStream ) 
		return mSourceStream->url; 
	return 0;
}

//======================================================================
//		CNetscapeStream::EvolveStream - static
//======================================================================

CNetscapeStream*
CNetscapeStream::EvolveStream( NPStream* npStream )
{
	return (CNetscapeStream*) npStream->pdata;
}

