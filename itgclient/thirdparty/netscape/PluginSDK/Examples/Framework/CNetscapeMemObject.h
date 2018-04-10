// CNetscapeMemObject.h
#ifndef CNETSCAPEMEMOBJECT_H
#define CNETSCAPEMEMOBJECT_H


#ifndef _NPAPI_H_
#include "npapi.h"
#endif

#ifdef XP_MAC
#include <defines.h>
#endif

class CNetscapeMemObject {
	public:
		void*				operator new(size_t size)
								{ return NPN_MemAlloc( size ); }; 
		void				operator delete( void* theThing, size_t size )
								{ NPN_MemFree( theThing ); };
};

#endif /* CNETSCAPEMEMOBJECT_H */