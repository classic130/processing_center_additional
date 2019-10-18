// CCharFlipper.h

#ifndef CCHARFLIPPER_H
#define CCHARFLIPPER_H

#ifndef _NPAPI_H_
#include "npapi.h"
#endif

#include "CNetscapePlugin.h"

class CPluginView;

class CCharFlipper : public CNetscapePlugin {
	public:
			static NPError		Initialize( void );
		static NPError		Shutdown( void );
		
							CCharFlipper( NPP instance, uint16 mode, CPluginArguments* adoptedArgs );
		virtual				~CCharFlipper();

		virtual NPError		SaveData( NPSavedData** );
		
		virtual NPBool				Handle_Event( void* event );
		virtual CNetscapeStream*	CreateStream( NPMIMEType type, NPStream *stream, NPBool seekable, uint16 stype );
		virtual CPluginView* 		CreatePluginView( ) ;

		int32				GetSpeed( );
		void				SetSpeed( int32 inSpeed );
		NPBool				GetRunning( );
		void				SetRunning( NPBool inRunning );
		NPBool				GetLooping( );
		void				SetLooping( NPBool inLooping );

		void				StartAtFrame( int32 inFrame = 0 );
		
		void				SetText( char* inText, int32 inTextLength );
	
		//		Message handlers (called by event pump.)
		void				HandleTimePassed();
		void				HandleMouseClick();

	protected:
		char				GetNextChar();
		unsigned long		GetNormalSysTime();

		virtual void		PrintEmbeded( NPEmbedPrint& embedPrintInfo );

		static const char* 	kCharFlipperArgs_Speed;
		static const char* 	kCharFlipperArgs_Autostart;
		static const char* 	kCharFlipperArgs_Looping;

		static const int32			kDefaultSpeed;
		static const NPBool 		kDefaultAutostart;
		static const NPBool 		kDefaultLooping;
		
		NPBool				mRunning;
		NPBool				mLooping;
		int32				mSpeed;
	
		char* 				mText;			// The text
		long				mTextLength;	// How much text do we have
		long				mTextIndex;		// The part we are displaying
		
		char				mCurrentChar;
		unsigned long		mTimeLastFlipped;
};

#endif /* CCHARFLIPPER_H */