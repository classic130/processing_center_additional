///////////////////////////////////////////////////////////////////////////////
//																			 //
//	File Name		:	LogWrapper.cpp										 //
//																			 //
//	Description		:	Implementation of the CLogWrapper class				 //
//																			 //
//	Date			:	Sep 28, 2001										 //
//																			 //
//	Author			:	Ramakant Pandrangi									 //
//																			 //
//  Change Log		:   Sep 28 2001 - Initial revisions    					 //
//																			 //
///////////////////////////////////////////////////////////////////////////////
#include <Windows.h>
#include "LogWrapper.h"


///////////////////////////////////////////////////////////////////////////////
///	Function Name	:	CLogWrapper
///
///	Parameters		:	None
///
///	Return Values	:	None
///	
///	Description		:	Constructor
///////////////////////////////////////////////////////////////////////////////
CLogWrapper::CLogWrapper()
{
	_eLogLevel = LOG_CRITICAL;
		
	_bInitialized = false;
}

///////////////////////////////////////////////////////////////////////////////
///	Function Name	:	~CLogWrapper
///
///	Parameters		:	None
///
///	Return Values	:	None
///	
///	Description		:	Destructor
///////////////////////////////////////////////////////////////////////////////
CLogWrapper::~CLogWrapper()
{
	if ( _bInitialized )
		VS_CloseLogFile(); 
}

///////////////////////////////////////////////////////////////////////////////
//	Function Name	:	setLogFile
//
//	Parameters		:	const char* strLogFileName
//
//	Return Values	:	VS_STATUS
//	
//	Description		:	sets the file to which all log messages need to be written to
//
///////////////////////////////////////////////////////////////////////////////
VS_STATUS CLogWrapper::setLogFile(const char* strLogFileName)
{
	VS_STATUS rc= eERR_CANT_OPEN_LOG;
	
	_strLogFileName = strLogFileName;

	// if it has already been opened before close it as it may be 
	// some other log file that we are trying to open now
	if ( _bInitialized )
		VS_CloseLogFile();
	
	// now open the file
	rc = VS_OpenLogFile (_strLogFileName);

	if ( eERR_NO_ERROR == rc )
		_bInitialized = true;

	return rc;
}

///////////////////////////////////////////////////////////////////////////////
///	Function Name	:	setLogLevel
///
///	Parameters		:	LOG_TYPE& elevel: the level that determines what kind of messages
//						need to be logged
///
///	Return Values	:	None
///	
///	Description		:	sets the level that determines what kind of messages need to be
//						written
///////////////////////////////////////////////////////////////////////////////
VS_STATUS CLogWrapper::setLogLevel(const LOG_TYPE& elevel)
{
	_eLogLevel = elevel;
	
	const char* pstrLevel;
	VS_STATUS rc= eERR_CANT_OPEN_LOG;
	
	// set the log level here
	switch ( _eLogLevel )
	{
		case LOG_CRITICAL:
			 pstrLevel = "VS_LOG_CRITICAL";
			 break;
																		
		case LOG_ERROR:
			 pstrLevel = "VS_LOG_ERROR";
			 break;
																		
		case LOG_WARNING:
			 pstrLevel = "VS_LOG_WARNING";
			 break;
																		
		case LOG_INFO:
			 pstrLevel = "VS_LOG_INFO";
			 break;
																		
		case LOG_DEBUG:
			 pstrLevel = "VS_LOG_DEBUG";
			 break;
																		
		default:
			 pstrLevel = "VS_LOG_EMERGENCY";
			 break;
	}

	// set the log level now
	rc = VS_SetLogLevel (pstrLevel);

	return rc;
}

///////////////////////////////////////////////////////////////////////////////
///	Function Name	:	setLogLevel
///
///	Parameters		:	int level 0 to 5 are valid values
///
///	Return Values	:	true: if the integer specified corresponds to a valid
//							  log level
//						false: if the integer value is outside the range of valid
//						values
///	
///	Description		:	sets the level that determines what kind of messages need to be
//						written
///////////////////////////////////////////////////////////////////////////////
bool CLogWrapper::setLogLevel(int level)
{

	LOG_TYPE eLogLevel = LOG_NOLOG;

	switch ( level )
	{
		case 0:
			 eLogLevel = LOG_NOLOG;
			 break;

		case 1:
			 eLogLevel = LOG_CRITICAL;
			 break;
				
		case 2:
			 eLogLevel = LOG_ERROR;
			 break;
				
		case 3:
			 eLogLevel = LOG_WARNING;
			 break;
				
		case 4:
			 eLogLevel = LOG_INFO;
			 break;
				
		case 5:
			 eLogLevel = LOG_DEBUG;
			 break;
				
		default:
			 return false;
			 break;
	}

	// set the log level
	VS_STATUS rc = setLogLevel(eLogLevel);

	if ( eERR_NO_ERROR == rc )
		return true;
	else
		return false;

}

///////////////////////////////////////////////////////////////////////////////
//	Function Name	:	LogMessage
//
//	Parameters		:	const LOG_TYPE& level,
//						const int& iLine,
//						const char *strFileName,
//						const char *strMessage,
//						const long& lErrorCode
//
//	Return Values	:	VS_STATUS indicates if there was an error while writing the log
//						message
//	
//	Description		:	Write a message to the log file if the level specified
//						is equal to or less than the level of logging required
///////////////////////////////////////////////////////////////////////////////

VS_STATUS CLogWrapper::LogMessage(
								const LOG_TYPE& level,
								const int& iLine,
								const char *strFileName,
								const char *strMessage,
								const long& lErrorCode
								)
{
	VS_STATUS rc= eERR_CANT_OPEN_LOG;

	// check the level and return if the current level is lower
	if ( level > _eLogLevel )
		return eERR_NO_ERROR;
		
	// we will do a late initialization depending on when it is called
	do
	{
		if ( !_bInitialized )
		{
			// if not initialized dont do anything at all
			break;
		}
			
		VS_LOG_TYPE vsLevel;

		switch ( level )
		{
			case LOG_NOLOG:
				 vsLevel = VS_LOG_CRITICAL;
				 break;

			case LOG_CRITICAL:
				 vsLevel = VS_LOG_CRITICAL;
				 break;
				
			case LOG_ERROR:
				 vsLevel = VS_LOG_ERROR;
				 break;
				
			case LOG_WARNING:
				 vsLevel = VS_LOG_WARNING;
				 break;
				
			case LOG_INFO:
				 vsLevel = VS_LOG_INFO;
				 break;
				
			case LOG_DEBUG:
				 vsLevel = VS_LOG_DEBUG;
				 break;
				
			default:
				 vsLevel = VS_LOG_CRITICAL;
				 break;
		}
			

		rc = VS_Log (
					 vsLevel, iLine, strFileName,
					"Message: %s Status Code: 0x%x",
					 strMessage, lErrorCode
					);
	}
	while(0);
		
	return rc;
}	


