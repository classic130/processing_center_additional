//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//
// PluginFactoryStubs.cpp
//
// These functions create, initialize, and shutdown a plugin. Remove this file and implement
// these functions yourself in order to make sure that the correct subclass of CNetscapePlugin
// gets used.
//
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

#ifndef _NPAPI_H_
#include "npapi.h"
#endif

#include "CCharFlipper.h"


CNetscapePlugin* CreateNetscapePlugin( NPP instance, uint16 mode, CPluginArguments* adoptedArgs, NPSavedData* saved )
{
	return new CCharFlipper( instance, mode, adoptedArgs );
}

NPError InitializeNetscapePlugin( void )
{
	return CCharFlipper::Initialize();
}

void ShutdownNetscapePlugin( void )
{
	CCharFlipper::Shutdown();
}
