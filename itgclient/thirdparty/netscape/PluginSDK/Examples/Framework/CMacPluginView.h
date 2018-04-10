#pragma once#include "Events.h"#include "Quickdraw.h"#ifndef _NPAPI_H_#include "npapi.h"#endif#include "CPluginView.h"#include <LGrafPortView.h>class CMacPluginView :	public CPluginView,	public LGrafPortView {	public:		static NPError		Initialize();									CMacPluginView( CNetscapePlugin* controller, Int16 inFrameThickness = 2 );		virtual				~CMacPluginView();// CPluginView methods		virtual NPError		SetWindow( NPWindow* window );		virtual void		Paint();// CMacPluginView-specific methods		virtual NPBool		Handle_Event( EventRecord& event );			protected:		virtual NPError 	Handle_SetWindow() { return NPERR_NO_ERROR; };		virtual LPane*		CreateContentPane( );				void				RecalcFrameLayout();		virtual void		UpdatePort();				virtual void		DrawSelf();		virtual void		ActivateSelf();		virtual void		DeactivateSelf();		CGrafPtr			GetNetscapeGrafPort() { return ((NP_Port*)(mNetscapeWindow->window))->port; };				short				mFramePenThickness;		NPWindow*			mNetscapeWindow;		LPane*				mContentPane;};