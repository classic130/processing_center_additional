// CPluginArgs.cpp

#include "CPluginArgs.h"


#include "npapi.h"

#include <string.h>
//#include <stdlib.h>

void NormalizeString( char* theString );
const char* gTrueString = "true";

extern void* NPN_MemAlloc(uint32 size);
extern void NPN_MemFree(void* ptr);

//======================================================================
//
//		CArgumentNode::CArgumentNode
//
//======================================================================

CArgumentNode::CArgumentNode( char* adoptArgumentName, char* adoptArgumentValue )
:	fArgumentName( adoptArgumentName ),
	fArgumentValue( adoptArgumentValue ),
	fLesserChild( 0 ),
	fGreaterChild( 0 )
{
}

//======================================================================
//
//		CArgumentNode::~CArgumentNode
//
//======================================================================

CArgumentNode::~CArgumentNode()
{
	delete fLesserChild;
	delete fGreaterChild;
	NPN_MemFree( fArgumentName );
	NPN_MemFree( fArgumentValue );	
}

//======================================================================
//
//		CArgumentNode::FindArgumentByName
//
//======================================================================

const CArgumentNode*
CArgumentNode::FindArgumentByName( const char* normalArgName ) const
{
	CArgumentNode* resultNode = 0;
	
	int result = strcmp( normalArgName, fArgumentName );
	if ( result == 0 ) {
		return this;
	}
	else if( result < 0 ) {
		if ( fLesserChild )
			return fLesserChild->FindArgumentByName( normalArgName );
	}
	else if( result > 0 ) {
		if( fGreaterChild )
			return fGreaterChild->FindArgumentByName( normalArgName );
	}
	return resultNode;
}

//======================================================================
//
//		CArgumentNode::GetArgumentName
//
//======================================================================

const char*
CArgumentNode::GetArgumentName() const
{
	return fArgumentName;
}

//======================================================================
//
//		CArgumentNode::GetArgumentValue
//
//======================================================================

const char*
CArgumentNode::GetArgumentValue() const
{
	return fArgumentValue;
}

//======================================================================
//
//		CArgumentNode::AdoptChildArgument
//
//======================================================================

void
CArgumentNode::AdoptChildArgument( CArgumentNode* adoptedArg )
{
	
	int result = strcmp( adoptedArg->fArgumentName, fArgumentName );
	if ( result == 0 ) {
		delete adoptedArg;					// Tried to adopt an argument with the
											// same name as this one. Kill it.
	}
	else if( result < 0 ) {
		if ( fLesserChild ) {
			fLesserChild->AdoptChildArgument( adoptedArg );
		}
		else {
			fLesserChild = adoptedArg;
		}
	}
	else if( result > 0 ) {
		if( fGreaterChild ) {
			fGreaterChild->AdoptChildArgument( adoptedArg );
		}
		else {
			fGreaterChild = adoptedArg;
		}
	}
}

//======================================================================
//
//		NormalizeString
//
//======================================================================
void
NormalizeString( char* theString )
{
	int stringIndex = 0;
	char curChar = theString[stringIndex];
	
	while( curChar != '\0' ) {
		if( (curChar>='A') && (curChar<='Z') ) {
			theString[stringIndex] = curChar - ('A'-'a');
		}
		stringIndex++;
		curChar = theString[stringIndex];
	}
}

//======================================================================
//
//		CPluginArguments::CPluginArguments
//
//======================================================================

CPluginArguments::CPluginArguments( short argc, const char* argn[], const char* argv[] )
{
	CArgumentNode* newArg;
	
	for( int index = 0; index < argc; index++ ) {
		char* newName = (char*) NPN_MemAlloc( strlen( argn[index] ) +1 );
		char* newValue = (char*) NPN_MemAlloc( strlen( argv[index] ) +1 );
		
		strcpy( newName, argn[index] );
		strcpy( newValue, argv[index] );
		
		NormalizeString( newName );

		newArg = new CArgumentNode( newName, newValue );
		
		if( index == 0 ) {
			fTopArgument = newArg;
		}
		else {
			fTopArgument->AdoptChildArgument( newArg );
		}
	}
	
	if( fTopArgument == 0 ) {
		char* emptyName = (char*) NPN_MemAlloc( 1 );
		emptyName[0] = '\0';
		
		char* emptyValue = (char*) NPN_MemAlloc( 1 );
		emptyValue[0] = '\0';
		
		fTopArgument = new CArgumentNode( emptyName, emptyValue );
	}
	fEmptyString[0] = '\0';
}

//======================================================================
//
//		CPluginArguments::~CPluginArguments
//
//======================================================================

CPluginArguments::~CPluginArguments()
{
	delete fTopArgument;
}

//======================================================================
//
//		CPluginArguments::ArgumentValueAsString
//
//======================================================================

const char*
CPluginArguments::ArgumentValueAsString( const char* argumentName )
{
	char normalName[256];		
	strcpy( normalName, argumentName );
	NormalizeString( normalName );
	
	const CArgumentNode* foundNode = fTopArgument->FindArgumentByName( normalName );
	if( foundNode ) {
		return foundNode->GetArgumentValue();
	}
	else {
		return fEmptyString;
	}
}

//======================================================================
//
//		CPluginArguments::ArgumentValueAsInt
//
//======================================================================

long
CPluginArguments::ArgumentValueAsInt( const char* argumentName, long defaultValue )
{
	long theNumber = defaultValue;
	
	char normalName[256];		
	strcpy( normalName, argumentName );
	NormalizeString( normalName );

	const CArgumentNode* foundNode = fTopArgument->FindArgumentByName( normalName );
	if( foundNode ) {
		const char* value = foundNode->GetArgumentValue();

		theNumber = atol( value );		
	}
	
	return theNumber;
}

//======================================================================
//
//		CPluginArguments::ArgumentValueAsBool
//
//======================================================================

NPBool
CPluginArguments::ArgumentValueAsBool( const char* argumentName , NPBool defaultValue)
{
	NPBool isTrue = defaultValue;

	char normalName[256];		
	strcpy( normalName, argumentName );
	NormalizeString( normalName );

	const CArgumentNode* foundNode = fTopArgument->FindArgumentByName( normalName );
	if( foundNode ) {
		int cmpResult = strcmp( gTrueString, foundNode->GetArgumentValue() );
		if( cmpResult == 0 ) {
			isTrue = TRUE;
		}
		else
			isTrue = FALSE;
	}
	
	return isTrue;
}
