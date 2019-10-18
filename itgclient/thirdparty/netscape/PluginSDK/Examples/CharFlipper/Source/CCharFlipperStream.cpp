// CCharFlipperStream.cpp

#include "CCharFlipperStream.h"

#include <string.h>

const char*	CCharFlipperStream::kCharFlipperType = "application/x-charflipper";

CCharFlipperStream::CCharFlipperStream( NPMIMEType type, NPStream* stream, NPBool seekable, uint16 stype, CCharFlipper* inController)
:	CNetscapeStream( type, stream, seekable, stype ),
	mController( inController ),
	mBuffer( 0 ),
	mAllocatedSize( 0 ),
	mEndOfData( 0 )
{
}

CCharFlipperStream::~CCharFlipperStream()
{
}

//======================================================================
//		CCharFlipperStream::Write()
//======================================================================
long		
CCharFlipperStream::Write( int32 offset, int32 len, void *buffer )
{
	if( mSourceStream->end < ( offset + len ) ) {	// Navigator screwed something up, and
		return -1;									// we are getting out of here
	}
	int32 result;
	
	if( mSourceStream->end > mAllocatedSize ) {			// We don't have enough space in the buffer,
		result = ChangeBufferSize( mSourceStream->end );// so we need to expand it.
		if( result < 0 ) {
			return result;
		}
	}
	
	result = AppendData( len, buffer );	

	return result;
}

//======================================================================
//		CCharFlipperStream::ChangeBufferSize()
//
// Returns the new size of the data buffer. Currently will not shrink
// the buffer.
//======================================================================
int32		
CCharFlipperStream::ChangeBufferSize( int32 inNewSize )
{
	if( inNewSize <= mAllocatedSize ) {
		// we don't shrink the buffer
		return mAllocatedSize;
	}
	
	char* newBuffer = (char*) NPN_MemAlloc( inNewSize );
	if( newBuffer == 0 ) {			// Couldn't Allocate the space.
		return -1;					// Return -1 as an error.
	}
	
	::memcpy( (void*) newBuffer, (void*) mBuffer, mAllocatedSize );
	NPN_MemFree( mBuffer );
	mBuffer = newBuffer;
	mAllocatedSize = inNewSize;
	
	return inNewSize;
}

//======================================================================
//		CCharFlipperStream::AppendData()
//
// Returns the number of bytes appended (which at this time will be all
// of the bytes sent, unless an error occurs.)
//======================================================================
int32		
CCharFlipperStream::AppendData( int32 inLength, void* inBuffer )
{
	// We expect that there will be enough room in mBuffer to append all of the data.
	// If not, we will return an error.
	if( ( mEndOfData + inLength ) > mAllocatedSize ) {
		return -1;
	}
	
	::memcpy( (void*) (mBuffer + mEndOfData ), inBuffer, inLength );
	mEndOfData += inLength;
	
	return inLength;
}


//======================================================================
//		CCharFlipperStream::Finish()
//======================================================================
NPError		
CCharFlipperStream::Finish( NPError reason )
{
	if( !mController ) {
		return NPERR_GENERIC_ERROR;
	}
	mController->SetText( mBuffer, mEndOfData );
	return NPERR_NO_ERROR;
}


//======================================================================
//		CCharFlipperStream::Finish()
//======================================================================
NPBool
CCharFlipperStream::IsCharFlipperStream( NPStream* stream )
{
	if( strcmp( stream->url, kCharFlipperType ) == 0 )
		return TRUE;
	return FALSE;
}
