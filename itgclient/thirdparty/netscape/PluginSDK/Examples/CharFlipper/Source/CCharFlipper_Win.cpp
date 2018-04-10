// CCharFlipper_Win


#include "StdAfx.h"
#include "CCharFlipper.h"
#include "WinFlipView.h"

//------------------------------------------------------------------------------------
// CCharFlipper::Handle_Event
//------------------------------------------------------------------------------------
NPBool 
CCharFlipper::Handle_Event( void* event)
{
	return FALSE;
}

//------------------------------------------------------------------------------------
// CCharFlipper::CreatePluginView
//------------------------------------------------------------------------------------
CPluginView*
CCharFlipper::CreatePluginView( )
{
	return new CWinFlipView( this );
}

//------------------------------------------------------------------------------------
// CCharFlipper::PrintEmbeded
//------------------------------------------------------------------------------------
void
CCharFlipper::PrintEmbeded( NPEmbedPrint& embedPrintInfo )
{

}

unsigned long 
CCharFlipper::GetNormalSysTime( )
{
	unsigned long winTime = GetTickCount();
			// turn the windows time into 60ths of a second
	double normalTime = ( winTime / 1000.0 ) * 60.0;
	return normalTime;
}