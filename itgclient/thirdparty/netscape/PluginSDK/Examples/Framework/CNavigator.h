// CNavigator.h

#ifndef CNAVIGATOR_H
#define CNAVIGATOR_H

#ifndef _NPAPI_H_
#include "npapi.h"
#endif

#include "CNetscapeMemObject.h"

class CNavigator : public CNetscapeMemObject {
	public:
						CNavigator( NPP inInstanceRef );
		virtual			~CNavigator();
	
	// Netscape call-backs.
		NPError     	GetURL(const char* url, const char* target, void* notifyData = 0);
		NPError    		PostURL(const char* url, const char* target, 
								uint32 len, const char* buf,
								NPBool file, void* notifyData = 0);
								
		NPError     	NewStream( NPMIMEType type, const char* target, NPStream** stream);
		int32       	Write(NPStream* stream, int32 len, void* buffer);
		NPError    		DestroyStream(NPStream* stream, NPReason reason);
		
		void        	Status(const char* message);
		const char* 	UserAgent();

		jref		    GetJavaPeer();

		int32			GetVersion() // returns the navigator minor version.
									{ return mNavMinorVersion; };
									
	// These functions don't really need to be called through the plugin class, but they
	// are here for completeness.
		static	void*       	MemAlloc(uint32 size)
									{ return NPN_MemAlloc( size ); };
		static	void       		MemFree(void* ptr)
									{ NPN_MemFree( ptr ); };
		static	uint32      	MemFlush(uint32 size)
									{ return NPN_MemFlush( size ); };
		static	void			ReloadPlugins(NPBool reloadPages)
									{ NPN_ReloadPlugins( reloadPages ); };
		static	JRIEnv*	    	GetJavaEnv(void)
									{ return NPN_GetJavaEnv( ); };
		
	protected:
		NPP				mInstance;
		int32			mNavMinorVersion;
};

#endif /* CNAVIGATOR_H */