// This is the CGI that will decode
// the SMIME Message using Proxy Recipients's
// Certificate.

///////////////////////////////////////////////////////////////////////////////
//																			 //
//	File Name		:	sgmspr.cpp											 //
//																			 //
//	Description		:	This is the CGI that will decode the SMIME Message	 //
//						using Proxy Recipients's Certificate.				 //
//																			 //
//	Date			:	???													 //
//																			 //
//	Author			:	Isaac Liu											 //
//																			 //
//  Change Log		:   ???? - Initial revisions    						 //
//						28 Sep 2001 - Ramakant								 //
//							- Added logging capability to the CGI			 //
//						    - Added a try catch block to trap exceptions     //
//							  and post an error if an exception occurs		 //	
//																			 //
//					    11/01/2001 - Ramakant								 //
//						Incorporated changes for VSSC. It now returns an	 //		
//						appStatus variable that provides further information //
//						if errors occurs.									 //
///////////////////////////////////////////////////////////////////////////////

#include<atlbase.h>

#include "sgmsprs.h"
#include "ptaerrs.h"
#include "Http.h"
#include <fstream.h>
#include <strstrea.h>
#include <iostream.h>
#include <sys/types.h>
#include <sys/stat.h>      
#include <process.h>

// global variables
bool		debugMode;
VSString	debugSMIMEFile;


static char *URLEncode(const char *str);
static char *URLEncode(unsigned char * str, int len);
void URLEncodeAndWrite(const unsigned char* buffer, long n);

class DuplicateProfile
{

public: 
	

	DuplicateProfile()
	{
		_newProfileName = "";
		_newProfilePath = "";
	}

	HRESULT CreateDuplicateProfile(const char* path, const char* profileName, const char * appName)
	{

		  VSString vsExistingFileName = path;
		  vsExistingFileName = vsExistingFileName + "\\" + profileName + "'s " + appName + " Profile.pta";	
	 
		  /*LARGE_INTEGER e;				
		  QueryPerformanceCounter(&e);  

		  srand(e.LowPart);
		
		  char randbuffer[20];
		  int i = rand();
		  _itoa( i, randbuffer, 10 );

		  char ticksbuffer[20];
		  QueryPerformanceCounter(&e);
		  _ultoa( e.LowPart,ticksbuffer, 10 );	
		  
		  _newProfileName = randbuffer;
		  _newProfileName = _newProfileName + ticksbuffer;	*/

		  int pid = _getpid();
		  char pidbuf[15];
		  _newProfileName = _itoa(pid,pidbuf,10);	


		  _newProfilePath = path;
		  _newProfilePath = _newProfilePath	+ "\\";
		  _newProfilePath = _newProfilePath + _newProfileName;
		  
		  
		  _newProfilePath = _newProfilePath + "'s " + appName + " Profile.pta";	

		  // now create a copy of the existing profile
		  BOOL bSuccess =  CopyFile(vsExistingFileName,_newProfilePath,true);
		
		  if ( bSuccess )
			return S_OK;
		  else
			  return E_FAIL;
	}	

	~DuplicateProfile()
	{
		if ( _newProfilePath != "" )
		{
			// delete file here 
			 DeleteFile(_newProfilePath);

		}
	}

public:	
	
	VSString _newProfileName;
	
	VSString _newProfilePath;
};


INT _CRTAPI1 main(int argc, char* argv[])
{
	
	HRESULT		 rc = S_OK;
	int          breakPoint = FALSE;
	char         pathName[64];     
	HRESULT		 appErrorStatus = PRS_CONFIGURATION_ERROR;

	// CGI debug capability. 
	// The 'debugMode' is available
	// for stepping thru the code using inputs from the policy file.
	// But if CGI inputs need to be examined, you must use this
	// debugging method.  Follow the directions below.
	//
	// How to debug:
	// 1. Put a file named: DEBUGWAIT.lock in the
	// same directory where this program is running.
	// 2. Start you client program to hit the CGI.
	// 3. Use Visual C++ to 'attach process'.  You will find
	// sgmsprs.exe in the 'system process' window.
	// 4. Once Visual C++ debug is in sesssion, do a 'break'
	// to go to the 'Main' part of the source code.
	// 5. Set the variable, 'breakPoint' to '0'
	// 6. Step thru the code.
	struct stat  statbuf;

	// Create the log file class, do not initialize it to anything
	CLogWrapper objLogger;
	
	try
	{
		strcpy(pathName, "DEBUGWAIT.lock");

		if (stat(pathName,&statbuf) == 0) {
			breakPoint = TRUE;
			while(breakPoint);
		}         
		do {

		
		   CProxyRecipients	myCPR;
		   VSPRSInfo			proxyInfo;
			
		  // Step 1.  Get the configuration from sgmsprs.policy
		  // sgmsprs.policy must be in same directory as the sgmsprs.exe
		  // sgmsprs.policy can be any OnSite Policy file with PTA
		  // enabled.  Basically info such as password timeout, PTA app, etc
		  // is required to open the PTA.
		  // Get config will also log the message	
		  if ((rc = GetConfiguration(&proxyInfo,objLogger)) != S_OK) {
			  long retCode = rc & 0x0000FFFF;
			  retCode = retCode | 0x80090000;
			  PostError(retCode,PRS_CONFIGURATION_ERROR);
			  break;
		  }

		  
		  


		  objLogger.LogMessage(CLogWrapper::LOG_INFO, __LINE__, __FILE__,
								"Got the config information and starting the execution.", 0);
		  
		  objLogger.LogMessage(CLogWrapper::LOG_DEBUG, __LINE__, __FILE__,
								"Before GetSMIMEMessage.", 0);

		  // Step 2.  Get the SMIME Message from web server.
		  if ((rc = GetSMIMEMessage(&proxyInfo,objLogger)) != S_OK) {
			  objLogger.LogMessage(CLogWrapper::LOG_ERROR, __LINE__, __FILE__,
									"Getting the s-mime message failed.", rc);
			  long retCode = rc & 0x0000FFFF;
			  retCode = retCode | 0x80090000;
			  PostError(retCode,PRS_GETSMIME_ERROR);
			  break;
		  }

		  objLogger.LogMessage(CLogWrapper::LOG_DEBUG, __LINE__, __FILE__,
				"Before VSPRS_Initialize.", 0);
		
		  // this variable is used to get the app status from the component	
		  VARIANT varAppStatus;

		  DuplicateProfile objDupProfile;
		  
		  rc = objDupProfile.CreateDuplicateProfile(
										proxyInfo.PTAProfilePath,
										proxyInfo.PTAProfile,
										proxyInfo.PTAApplication
										);

		  if ( E_FAIL == rc )
		  {
			   objLogger.LogMessage(CLogWrapper::LOG_CRITICAL, __LINE__, __FILE__,
									"Create dup profile failed.", rc);
			   
			   // we will ignore this error
			   // PostError(rc,PRS_DUPPROFILE_ERROR);
			   // break;
			  
			   rc=S_OK;				
		  }

		  // set the profile name to the this new name now
		  proxyInfo.PTAProfile = objDupProfile._newProfileName;
		   	
		  // Step 3.  Initialize the CProxyRecipient class with
		  // info we fetched from the conf file.
		  if ((rc = myCPR.VSPRS_Initialize(&proxyInfo,&varAppStatus)) != S_OK) {
			  objLogger.LogMessage(CLogWrapper::LOG_ERROR, __LINE__, __FILE__,
									"VSPRS_Initialize failed.", rc);
			  objLogger.LogMessage(CLogWrapper::LOG_ERROR, __LINE__, __FILE__,
									"VSPRS_Initialize AppStatus.", varAppStatus.lVal);
			  
			  long retCode = rc & 0x0000FFFF;
			  retCode = retCode | 0x80090000;
			  
			  PostError(retCode,PRS_INITVSSC_ERROR);
			  
			  break;
		  }

		  objLogger.LogMessage(CLogWrapper::LOG_DEBUG, __LINE__, __FILE__,
								"Before VSPRS_DecryptVerifySMIMEMessage.", 0);
				
		  // Step 4.  Call the decrypt function to decrypt the SMIME message.
		  if ((rc = myCPR.VSPRS_DecryptVerifySMIMEMessage(&varAppStatus)) != S_OK) {
				objLogger.LogMessage(CLogWrapper::LOG_ERROR, __LINE__, __FILE__,
							"VSPRS_DecryptVerifySMIMEMessage failed.", rc);
				
				if ( S_OK == varAppStatus.lVal )
				{
					objLogger.LogMessage(CLogWrapper::LOG_ERROR, __LINE__, __FILE__,
							"VSPRS_DecryptVerifySMIMEMessage AppStatus.", varAppStatus.lVal);
				}
				else
				{
					objLogger.LogMessage(CLogWrapper::LOG_ERROR, __LINE__, __FILE__,
							"VSPRS_DecryptVerifySMIMEMessage AppStatus.", PRS_DECRYPTVERIFY_ERROR);
				}
				
				// check to see if it is a config error in the pTA username and password
				if ( E_USERCANCELLED == rc )
				{
					objLogger.LogMessage(CLogWrapper::LOG_CRITICAL, __LINE__, __FILE__,
							"Please check the PRC username and password, the service is unable to login.", PRS_PASSWORDFAILED_ERROR);
					rc = PRS_PASSWORDFAILED_ERROR;
							
				}
				
				long retCode = rc & 0x0000FFFF;
				retCode = retCode | 0x80090000;

				PostError(retCode,PRS_DECRYPTVERIFY_ERROR);
				break;	  
		  } 
		
		  objLogger.LogMessage(CLogWrapper::LOG_DEBUG, __LINE__, __FILE__,
						"Before HandleOutput.", 0);
		  
		  // Step 5:  Write the output to STDOUT.
		  HandleOutput(myCPR, &proxyInfo,objLogger);			
	  
		  
		} while (0);

	}
	catch(...)
	{
		objLogger.LogMessage(CLogWrapper::LOG_CRITICAL, __LINE__, __FILE__,"Exception thrown",E_UNEXPECTED);
		long retCode = E_UNEXPECTED & 0x0000FFFF;
		retCode = retCode | 0x80090000;

		PostError(retCode,PRS_EXCEPTION_ERROR);				
	}
	
	objLogger.LogMessage(CLogWrapper::LOG_INFO, __LINE__, __FILE__,
								"Done processing.", 0);

	return 0;
}



HRESULT GetSMIMEMessage(VSPRSInfo *pInfo, CLogWrapper& logWrapper)
{
	HRESULT rc = S_OK;

	do {
		//1.  Check if debug mode, and if smime file exists. If not, report error.
		if (debugMode) {
			struct stat statbuf;
			
			logWrapper.LogMessage(CLogWrapper::LOG_DEBUG, __LINE__, __FILE__,
					"GetSMIMEMessage::Trying to get the debug s-mime file", rc);
			
			if (stat((const char *)debugSMIMEFile, &statbuf) != 0) {
				rc = PRS_SMIME_FILE_NOT_FOUND;
				logWrapper.LogMessage(CLogWrapper::LOG_DEBUG, __LINE__, __FILE__,
						"GetSMIMEMessage::Debug s-mime file not found", rc);
				break;
			}
			// if file has size == 0 then report error too.
			if (statbuf.st_size == 0) {
				rc = PRS_SMIME_FILE_NOT_FOUND;
				logWrapper.LogMessage(CLogWrapper::LOG_DEBUG, __LINE__, __FILE__,
					"GetSMIMEMessage::Debug s-mime file size is zero", rc);
				break;
			}
			// open the test file and red it into memory.
			FILE *fp =NULL;
			fp = fopen((const char *)debugSMIMEFile, "rb");
			fseek(fp, 0, SEEK_END);
			int nFileSize = ftell(fp);
			rewind(fp);
			char *szFileCont = (char*)malloc(nFileSize + 1);
			fread(szFileCont, 1, nFileSize, fp);
			szFileCont[nFileSize] = '\0';
			fclose(fp);


			pInfo->EncryptedMIMEMessage = (const char*)szFileCont;
			/*
			printf("DebugMode:\n %sinput file: %s\n%smesage size=%d\n", 
				DEBUGLINE, (const char *)debugSMIMEFile, DEBUGLINE, 

  pInfo->EncryptedMIMEMessage.Length());
			*/
			if (szFileCont != NULL) free(szFileCont);

		} // end debugMode.
		else { // get the smime blob from the POST.
			// sgmsprx.exe is runnign as a cgo here.
			// See if we have a debugfile.  If so, hang the process.
			struct stat  statbuf;
			bool breakPoint = FALSE;

			if (stat("DEBUGWAIT.lock",&statbuf) == 0) {
				breakPoint = TRUE;
				while(breakPoint);
			} 

			logWrapper.LogMessage(CLogWrapper::LOG_DEBUG, __LINE__, __FILE__,
				"GetSMIMEMessage::Before the HTTP object creation", rc);
			
			CHttp myHttp;
			
			logWrapper.LogMessage(CLogWrapper::LOG_DEBUG, __LINE__, __FILE__,
				"GetSMIMEMessage::Before getting the s-mime message from the HTTP class", rc);
			
			pInfo->EncryptedMIMEMessage = (const char *)myHttp.getVar(SMIMEMESSAGE);
			
			logWrapper.LogMessage(CLogWrapper::LOG_DEBUG, __LINE__, __FILE__,
				"GetSMIMEMessage::Before getting the useenccert flag", rc);

			pInfo->UseEncCert = (const char *)myHttp.getVar(USEENCCERT);

			logWrapper.LogMessage(CLogWrapper::LOG_DEBUG, __LINE__, __FILE__,
				"GetSMIMEMessage::Before getting the REENCRYPTEMAIL flag", rc);
			
			pInfo->ReEncryptEmail = (const char *)myHttp.getVar(REENCRYPTEMAIL);
			
			logWrapper.LogMessage(CLogWrapper::LOG_DEBUG, __LINE__, __FILE__,
				"GetSMIMEMessage::Before getting the Base64Attachment flag", rc);

			pInfo->Base64Attachment = (const char *)myHttp.getVar(BASE64ATTACHMENT);	
		}
	} while (0);
    
	
	return rc;
}

void PostError(HRESULT rc, HRESULT appErrorCode)
{
	printf ("Content-Type: text/plain\n") ;
	printf ("Pragma: no cache\n") ;
	printf ("Expires: -1\n") ;
	printf ("Cache-control: no cache\n\n\n") ;
	printf("errorCode=%x&", rc) ;
	printf("appErrorCode=%x", appErrorCode) ;
}

void HandleOutput(CProxyRecipients & myCPR, VSPRSInfo *infoPtr, CLogWrapper& logWrapper)
{
	logWrapper.LogMessage(CLogWrapper::LOG_DEBUG, __LINE__, __FILE__,
				"HandleOutput::In handle output", 0);

	printf ("Content-Type: text/plain\n") ;
	printf ("Pragma: no cache\n") ;
	printf ("Expires: -1\n") ;
	printf ("Cache-control: no cache\n\n\n") ;

	printf("status=%d&", (int)myCPR.VSPRS_GetStatus());
	printf("messageType=%d&", (int)myCPR.VSPRS_GetMsgType());

	if (infoPtr->UseEncCert == YES) {

		logWrapper.LogMessage(CLogWrapper::LOG_DEBUG, __LINE__, __FILE__,
				"HandleOutput::UseEncCert == YES", 0);
		
		printf("ReEncryptedContent=%s&",URLEncode(myCPR.VSPRS_GeReEncryptedContent()));
			/******* DEBUG
					FILE *fp = NULL;
					
					
					fp = fopen("D:\\SecureMsg\\ReEncrypt.eml", "wb+");

					if(fp == NULL)
					{
							printf("invalid path name");
							
					}
					else {

						fwrite((PCHAR)(const char *)myCPR.VSPRS_GeReEncryptedContent(),1, 
							VSString(myCPR.VSPRS_GeReEncryptedContent()).Length(), fp);
					}

					fclose(fp);
					*********** ---- DEBUG END ********/		
	}

	else { 
		if (infoPtr != NULL) {
		
			logWrapper.LogMessage(CLogWrapper::LOG_DEBUG, __LINE__, __FILE__,
				"HandleOutput::infoPtr != NULL", 0);
		
			char *bodyType = URLEncode("body-content-type");
			char *bodyEnc = URLEncode("body-content-transfer-encoding");
			char *bodyDisp = URLEncode("body-content-disposition");

			printf("From=%s&",URLEncode(myCPR.VSPRS_GetFrom()));
			printf("To=%s&", URLEncode(myCPR.VSPRS_GetTo()));
			if (VSString(myCPR.VSPRS_GetCC()).Length() == 0)
				printf("CC=&");
			else
				printf("CC=%s&", URLEncode(myCPR.VSPRS_GetCC()));

			if (VSString(myCPR.VSPRS_GetBCC()).Length() == 0)
				printf("BCC=&");
			else
				printf("BCC=%s&", URLEncode(myCPR.VSPRS_GetBCC()));

			printf("Date=%s&", URLEncode(myCPR.VSPRS_GetDate()));

			if (VSString( myCPR.VSPRS_GetSubject()).Length() == 0)
				printf("Subject=&");
			else
				printf("Subject=%s&", URLEncode(myCPR.VSPRS_GetSubject()));
			
			//printf("%s=%s&", bodyType,URLEncode(myCPR.VSPRS_GetBodyContent(BD_CONTENT_TYPE)));
			//printf("%s=%s&", bodyEnc,URLEncode(myCPR.VSPRS_GetBodyContent(BD_CONTENT_XSFER_ENCODING)));
		
			//if (VSString(myCPR.VSPRS_GetBodyContent(BD_CONTENT_DISP)).Length() == 0)
			//	printf("%s=&", bodyDisp);
			//else
			//	printf("%s=%s&", bodyDisp,URLEncode(myCPR.VSPRS_GetBodyContent(BD_CONTENT_DISP)));
		
			/*if (VSString(myCPR.VSPRS_GetBody()).Length() == 0)
				printf("Body=");
			else
				printf("Body=%s", URLEncode(myCPR.VSPRS_GetBody()));*/
			
			VSString temp = myCPR.VSPRS_GetBody();

			if (temp.Length() == 0)
				printf("Body=");
			else
			{
				printf("Body=");
				URLEncodeAndWrite((const unsigned char*)((const char*)temp),temp.Length());
			}

			logWrapper.LogMessage(CLogWrapper::LOG_DEBUG, __LINE__, __FILE__,
				"HandleOutput::Before calling Handle attachments", 0);
				
			// handle attachments, if any.
			HandleAttachments(myCPR, infoPtr->Base64Attachment,logWrapper);

			logWrapper.LogMessage(CLogWrapper::LOG_DEBUG, __LINE__, __FILE__,
				"HandleOutput::After calling Handle attachments", 0);
			
		}
	} // end else
}




void HandleAttachments(CProxyRecipients &myCPR, VSString &flag, CLogWrapper& logWrapper)
{

	logWrapper.LogMessage(CLogWrapper::LOG_DEBUG, __LINE__, __FILE__,
				"HandleAttachments::In Handle attachments", 0);
	
	CComVariant pvarAppStatus;
	VSPRSAttachment *myAtt = myCPR.VSPRS_GetAttachmentObj(&pvarAppStatus);
	VSString j;

	do {

		if (myAtt == NULL) {
			
			logWrapper.LogMessage(CLogWrapper::LOG_DEBUG, __LINE__, __FILE__,
				"HandleAttachments::No attachments", 0);
	
			printf("#");  // THIS IS ONLY a TEMPORARY for SLAMDUNK
						// to figure out how to get # of bytes
						// from stream.
			break; // nothing to do. no attachments.
		}
	
		// Print a '&' to deliminate the attachments.
		printf("&");

		// First, determine if attachment needs to be base64rized.

		if (flag == YES) 
		{
			logWrapper.LogMessage(CLogWrapper::LOG_DEBUG, __LINE__, __FILE__,
				"HandleAttachments::Attachments need to be base64rized", 0);
	
			myAtt->VSPRSAT_Base64Attachments();
		}


		logWrapper.LogMessage(CLogWrapper::LOG_DEBUG, __LINE__, __FILE__,
				"HandleAttachments::Writing the attachments", 0);


		// now, loop thru each one.
		char *name = NULL;
		char *value = NULL;

		for (int i = 1; myAtt->VSPRSAT_HasElements(); i++,myAtt->VSPRSAT_Next())
		{
			j.IntToString(i);
			
						
			printf("attachmentName%s=%s&", (const char *)j, URLEncode(myAtt->VSPRSAT_GetName()));
					
			printf("attachmentContent%s=",(const char *)j);
			
			logWrapper.LogMessage(CLogWrapper::LOG_DEBUG, __LINE__, __FILE__,
				"HandleAttachments::Before URLEncoding", 0);
		
			//VSString UrlEncode = URLEncode(myAtt->VSPRSAT_GetData(), myAtt->VSPRSAT_GetSize());
			
			logWrapper.LogMessage(CLogWrapper::LOG_DEBUG, __LINE__, __FILE__,
				"HandleAttachments::Before writing the data", 0);
		
			//fwrite((const char*)UrlEncode, 1, UrlEncode.Length(), stdout);
			URLEncodeAndWrite(myAtt->VSPRSAT_GetData(),myAtt->VSPRSAT_GetSize());

			printf("&");
		
			logWrapper.LogMessage(CLogWrapper::LOG_DEBUG, __LINE__, __FILE__,
				"HandleAttachments::After writing the data", 0);
		
		}
		
		logWrapper.LogMessage(CLogWrapper::LOG_DEBUG, __LINE__, __FILE__,
				"HandleAttachments::Number of Attachments", i-1);


		printf("attachmentCount=%d", i-1);
		printf("#");  // THIS IS ONLY a TEMPORARY for SLAMDUNK
						// to figure out how to get # of bytes
						// from stream.
	} while (0);

	return;
}


static char *URLEncode(const char * str)
{
	return (CHttp::URLEncodeAlloc((const unsigned char *)str, strlen(str)));
}

static char *URLEncode(unsigned char * str, int len)
{
	return (CHttp::URLEncodeAlloc((const unsigned char *)str, len));
}

void URLEncodeAndWrite(const unsigned char* buffer, long n)
{
  long           length = 0;
  long			traverseCounter = 0;
  const long	MAX_TRAVERSESIZE = 340000;

  char escaped[MAX_TRAVERSESIZE*3 + 1];

  const char*         hex = "0123456789ABCDEF";

  long iCountTraversed = 0;
  
  *escaped = NULL;

  while( iCountTraversed < n)
  {
    if ((*buffer >= 'a' && *buffer <= 'z') ||
        (*buffer >= 'A' && *buffer <= 'Z') ||
        (*buffer >= '0' && *buffer <= '9'))
    {
      escaped[length++] = *buffer;
    }
    else if (*buffer == ' ')
    {
      escaped[length++] = '+';
    }
    else
    {
      escaped[length++] = '%';
      escaped[length++] = hex[((unsigned char)*buffer) >> 4];
      escaped[length++] = hex[((unsigned char)*buffer) & 15];
    }
    escaped[length] = NULL;
    ++buffer;
	
	iCountTraversed++;

	traverseCounter++;

	if ( traverseCounter >= MAX_TRAVERSESIZE )
	{
		fwrite((const char*)escaped, 1, length, stdout);
		
		//reset length
		length=0;
		traverseCounter = 0;
	}
  }

  if ( length )
	 // write the last remaining buffer and quit
	 fwrite((const char*)escaped, 1, length, stdout);

}