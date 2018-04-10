///////////////////////////////////////////////////////////////////////////////
//																			 //
//	File Name		:	LogWrapper.h										 //
//																			 //
//	Description		:	Class for wrapping the log functionality available   //
//                      in the vslog.h.										 //
//																			 //
//	Date			:	Sep 28, 2001										 //
//																			 //
//	Author			:	Ramakant Pandrangi									 //
//																			 //
//  Change Log		:   Sep 28 2001 - Initial revisions    					 //
//																			 //
///////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include "vsstring.h"
#include "vslog.h"

#define LOGDEBUG(msg,erCode) LogMessage(CLogWrapper::LOG_DEBUG, __LINE__, __FILE__, msg, erCode)


class CLogWrapper
{
	
public:

	// constructor to create a log wrapper object without specifying a file
	CLogWrapper();

	enum LOG_TYPE {
		 LOG_NOLOG = 0,
		 LOG_CRITICAL,     // Emergency condition
		 LOG_ERROR,         // Errors 
		 LOG_WARNING,       // Warning messages 
		 LOG_INFO,        //  Informational messages
		 LOG_DEBUG          // Debugging messages
	};

	// destructor 
	~CLogWrapper();
			
public:
	
	// allows you to change the log file that was specified earlier. 
	VS_STATUS setLogFile(const char* strLogFileName);
	
	// set the log level by specifying an integer. will return an error if an
	// int with an invlaid range is passed in
	bool setLogLevel(int level);
	
	// set the log type use the enum defined by this class
	VS_STATUS setLogLevel(const LOG_TYPE& elevel);
	
	// This function actually logs the message
	VS_STATUS LogMessage(
							const LOG_TYPE& level,
							const int& iLine,
							const char *strFileName,
							const char *strMessage,
							const long& lErrorCode
						);
	
private:
	
	bool	_bInitialized;
	
	VSString _strLogFileName;

	LOG_TYPE		_eLogLevel;	

};
