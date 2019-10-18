//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//
// CNetscapeStream.h
//
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

#ifndef CNETSCAPESTREAM_H
#define CNETSCAPESTREAM_H

#ifndef _NPAPI_H_
#include "npapi.h"
#endif

#include "CNetscapeMemObject.h"

class CNetscapeStream : public CNetscapeMemObject {
	public:
							CNetscapeStream( NPMIMEType type, NPStream* stream, NPBool seekable, uint16 stype );
		virtual				~CNetscapeStream();
		
		virtual int32		WriteReady();
		virtual int32		Write( int32 offset, int32 len, void *buffer );
		virtual NPError		Finish( NPError reason );
		virtual void		StreamAsFile( const char* fname ); 
									
		unsigned short		GetStreamType() const { return mStreamType; };
		const char*			GetURL() const;
		
		static CNetscapeStream*	EvolveStream( NPStream* npStream );
	
	protected:
		static const long	kMaxBufSize;
		
		NPStream*			mSourceStream;
		char*				mMIMEType;
		NPBool				mSeekable;
		unsigned short		mStreamType;
};

#endif