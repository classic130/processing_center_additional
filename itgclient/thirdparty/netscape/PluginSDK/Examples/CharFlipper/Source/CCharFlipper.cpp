//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//
// charflipper.cp
//
// About this example:
//
// MIME type: application/x-charflipper
// File extention: flip
//
// This example plugin accepts the stream of characters
// and displays them one by one.  Once it¹s read all
// characters from the file, it redraws itself on null
// events, cycling through the characters over and over.
//
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

#ifndef _NPAPI_H_
#include "npapi.h"
#endif

#include "CCharFlipper.h"
#include "CCharFlipperStream.h"

#include "CFlipView.h"


const char* 	CCharFlipper::kCharFlipperArgs_Speed = "speed";
const char* 	CCharFlipper::kCharFlipperArgs_Autostart = "autostart";
const char*		CCharFlipper::kCharFlipperArgs_Looping = "loop";

const int32		CCharFlipper::kDefaultSpeed = 60;
const NPBool 	CCharFlipper::kDefaultAutostart = TRUE;
const NPBool 	CCharFlipper::kDefaultLooping = FALSE;


#define IMPLEMENT_TimeMediaPlugin

#include "TimeMediaPlugin.h"


//------------------------------------------------------------------------------------
// CCharFlipper::Initialize
//------------------------------------------------------------------------------------
NPError
CCharFlipper::Initialize( void )
{
	return CNetscapePlugin::Initialize();
}


//------------------------------------------------------------------------------------
// CCharFlipper::Shutdown:
//------------------------------------------------------------------------------------
NPError
CCharFlipper::Shutdown( void )
{
#ifndef __MC68K__
	JRIEnv* env = NPN_GetJavaEnv();

	netscape_plugin_Plugin::_unuse( env );
	TimeMediaPlugin::_unuse(env);
#endif /* !__MC68K__ */

	return CNetscapePlugin::Shutdown();
}


//------------------------------------------------------------------------------------
// CCharFlipper::CCharFlipper
//------------------------------------------------------------------------------------
CCharFlipper::CCharFlipper( NPP instance, uint16 mode, CPluginArguments* adoptedArgs )
:	CNetscapePlugin( instance, mode, adoptedArgs ),
	mCurrentChar(' '),
	mText( 0 ),
	mTextLength( 0 ),
	mTextIndex( 0 ),
	mTimeLastFlipped( 0 )
{
	SetSpeed( mArgs->ArgumentValueAsInt( kCharFlipperArgs_Speed, kDefaultSpeed ) );
	SetRunning( mArgs->ArgumentValueAsBool( kCharFlipperArgs_Autostart, kDefaultAutostart ));
	SetLooping( mArgs->ArgumentValueAsBool( kCharFlipperArgs_Looping, kDefaultLooping ));
}


//------------------------------------------------------------------------------------
//		CCharFlipper::~CCharFlipper()
//------------------------------------------------------------------------------------
CCharFlipper::~CCharFlipper()
{
	if( mText ) {
		NPN_MemFree( mText );
	}
}

//------------------------------------------------------------------------------------
//		CCharFlipper::SaveData()
//------------------------------------------------------------------------------------
NPError
CCharFlipper::SaveData( NPSavedData** ) 
{ 
	return NPERR_NO_ERROR;
}


//------------------------------------------------------------------------------------
// CCharFlipper::CreateStream
//------------------------------------------------------------------------------------
CNetscapeStream*
CCharFlipper::CreateStream( NPMIMEType type, NPStream *stream, NPBool seekable, uint16 stype )
{
	return new CCharFlipperStream( type, stream, seekable, stype, this );
}

//------------------------------------------------------------------------------------
// CharFlipper::GetNextChar
//------------------------------------------------------------------------------------
char
CCharFlipper::GetNextChar( )
{

	if( mText ) {
		mTextIndex++;
		if( mTextIndex >= mTextLength ) {
			NPBool isLooping = GetLooping();
			if( isLooping ) {
				mTextIndex = 0;
			}
			else {
				mTextIndex = mTextLength;
			}
		}
		return mText[mTextIndex];

	}

	return ' ';
}

//------------------------------------------------------------------------------------
// CharFlipper::GetSpeed:
//------------------------------------------------------------------------------------
int32
CCharFlipper::GetSpeed( )
{
	return mSpeed;
}

//------------------------------------------------------------------------------------
// CharFlipper::SetSpeed:
//------------------------------------------------------------------------------------
void
CCharFlipper::SetSpeed( int32 inSpeed )
{
	mSpeed = inSpeed;
}

//------------------------------------------------------------------------------------
// CharFlipper::GetRunning:
//------------------------------------------------------------------------------------
NPBool
CCharFlipper::GetRunning( )
{
	return mRunning;
}

//------------------------------------------------------------------------------------
// CharFlipper::SetRunning:
//------------------------------------------------------------------------------------
void
CCharFlipper::SetRunning( NPBool inRunning )
{
	mRunning = inRunning;
}

//------------------------------------------------------------------------------------
// CharFlipper::GetLooping:
//------------------------------------------------------------------------------------
NPBool
CCharFlipper::GetLooping( )
{
	return mLooping;
}

//------------------------------------------------------------------------------------
// CharFlipper::SetLooping:
//------------------------------------------------------------------------------------
void
CCharFlipper::SetLooping( NPBool inLooping )
{
	mLooping = inLooping;
}

//------------------------------------------------------------------------------------
// CharFlipper::SetText
//------------------------------------------------------------------------------------
void
CCharFlipper::SetText( char* inText, int32 inTextLength )
{
	if( mText ) {
		NPN_MemFree( mText );
	}
	mText = inText;
	mTextLength = inTextLength;
	mTextIndex = 0;
}

void
CCharFlipper::StartAtFrame( int32 inFrame )
{
	int32 startFrame = inFrame;
	if( startFrame > mTextLength ) {
		startFrame = 0;
	}
	mTextIndex = startFrame;
	SetRunning( TRUE );
}



void

CCharFlipper::HandleTimePassed()

{

	NPBool isRunning = GetRunning( );

	if( isRunning ) {

		unsigned long currentTicks = GetNormalSysTime();

		long speed = GetSpeed();

		if( mTimeLastFlipped <= ( currentTicks - speed ) ) {

			mTimeLastFlipped = currentTicks;

			mCurrentChar = GetNextChar();

			((CFlipView*)mView)->SetChar( mCurrentChar );

			mView->Paint();

		}

	}	

}



void

CCharFlipper::HandleMouseClick()

{

	NPBool isRunning = GetRunning();

	SetRunning( ! isRunning );

}

