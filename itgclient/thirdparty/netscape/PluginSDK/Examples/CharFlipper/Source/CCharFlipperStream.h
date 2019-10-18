#ifndef CCHARFLIPPERSTREAM_H
#define CCHARFLIPPERSTREAM_H

#ifndef _NPAPI_H_
#include "npapi.h"
#endif

#include "CNetscapeStream.h"
#include "CCharFlipper.h"

class CCharFlipperStream : public CNetscapeStream {
	public:
							CCharFlipperStream( 	NPMIMEType type, 
												NPStream* stream, 
												NPBool seekable, 
												uint16 stype,
												CCharFlipper* inController);
		virtual				~CCharFlipperStream();
		
		// We just use the default behavior for writeready: send as much data
		// as is available.
		
		virtual long		Write( int32 offset, int32 len, void *buffer );

		virtual NPError		Finish( NPError reason );

		static NPBool		IsCharFlipperStream( NPStream* stream );
		
	protected:
		virtual int32		ChangeBufferSize( int32 inNewSize );
		virtual int32		AppendData( int32 inLength, void* inBuffer );
	
		static const char*	kCharFlipperType;
		CCharFlipper*		mController;
		
		char*				mBuffer;
		int32				mAllocatedSize;
		int32				mEndOfData;
};

#endif