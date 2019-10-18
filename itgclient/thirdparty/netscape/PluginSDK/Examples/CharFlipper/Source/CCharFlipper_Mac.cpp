#include "CCharFlipper.h"
#include "CMacFlipView.h"

//------------------------------------------------------------------------------------
// CCharFlipper::Handle_Event
//------------------------------------------------------------------------------------
NPBool 
CCharFlipper::Handle_Event( void* event)
{
	Boolean eventHandled = false;

	if (event != NULL)
	{
		EventRecord* ev = (EventRecord*) event;
		switch (ev->what)
		{
			//
			// Draw ourselves on update events
			//
			case updateEvt: {
				((CFlipView*)mView)->Paint();
				break;
			}

			// On a mouse-click, toggle the current running-state
			case mouseDown: {
				HandleMouseClick();
				eventHandled = true;
				break;
			}
				
			case nullEvent: {
				HandleTimePassed();
				eventHandled = true;
				break;
			}
				
			default: {
				break;
			}
		}
	}
	return eventHandled;
}



//------------------------------------------------------------------------------------
// CCharFlipper::CreatePluginView
//------------------------------------------------------------------------------------
CPluginView*
CCharFlipper::CreatePluginView( )
{
	return new CMacFlipView( this );
}

//------------------------------------------------------------------------------------
// CCharFlipper::PrintEmbeded
//------------------------------------------------------------------------------------
void
CCharFlipper::PrintEmbeded( NPEmbedPrint& embedPrintInfo )
{
	NPWindow* printWindow = &(embedPrintInfo.window);
	CMacFlipView* macView = (CMacFlipView*) mView;

	NPWindow* oldWindow = macView->GetWindow();
	macView->SetWindow( printWindow );
	macView->Paint();
	macView->SetWindow( oldWindow );
}

unsigned long 
CCharFlipper::GetNormalSysTime( )
{
	unsigned long macTime = TickCount();
	return macTime;
}
