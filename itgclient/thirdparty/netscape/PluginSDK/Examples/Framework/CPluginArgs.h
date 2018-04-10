// CPluginArgs.h

#ifndef CPLUGINARGS_H
#define CPLUGINARGS_H

#include "CNetscapeMemObject.h"

class CArgumentNode : public CNetscapeMemObject {
	public:
							CArgumentNode( char* adoptArgumentName, char* adoptArgumentValue );
		virtual				~CArgumentNode();
	
		const CArgumentNode*	FindArgumentByName( const char* normalArgName ) const;
		const char*			GetArgumentName() const;
		const char*			GetArgumentValue() const;
		void				AdoptChildArgument( CArgumentNode* adoptedArg );

	private:
		char*				fArgumentName;
		char*				fArgumentValue;
		
		CArgumentNode*		fLesserChild;
		CArgumentNode*		fGreaterChild;
};


class CPluginArguments : public CNetscapeMemObject {
	public:
							CPluginArguments( short argc, const char* argn[], const char* argv[] );
		virtual				~CPluginArguments();
		
		const char*			ArgumentValueAsString( const char* argumentName );
		long				ArgumentValueAsInt( const char* argumentName, long defaultValue = 0 );
		NPBool				ArgumentValueAsBool( const char* argumentName, NPBool defaultValue=FALSE );
		
	private:
		CArgumentNode*		fTopArgument;
		char				fEmptyString[1];		
			
};

#endif /* CPLUGINARGS_H */