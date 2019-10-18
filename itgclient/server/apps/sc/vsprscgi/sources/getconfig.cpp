///////////////////////////////////////////////////////////////////////////////
//																			 //
//	File Name		:	getconfig.cpp										 //
//																			 //
//	Description		:	Implementation of the GetConfiguration function		 //
//						Gets the config info from the policy file			 //
//																			 //
//	Date			:	???													 //
//																			 //
//	Author			:	Isaac Liu											 //
//																			 //
//  Change Log		:   ???? - Initial revisions    						 //
//						28 Sep 2001 - Ramakant								 //
//							- Added logging capability to the function		 //
///////////////////////////////////////////////////////////////////////////////

#include "sgmsprs.h"
#include "vslog.h"

//Use policy module API to fetch the configuration.
HRESULT GetConfiguration(VSPRSInfo *pInfo, CLogWrapper& logWrapper)
{
	HRESULT rc = S_OK;
	
	// Use Policy Module API to get the policy contents.
	VSPM_STATUS status;
	VSPM_Descriptor pmd = (VSPM_Descriptor) NULL;
	VSPM_Container ptaContainer = (VSPM_Container) NULL;
	VSPM_Container sgmsprsContainer = (VSPM_Container) NULL;
	VSPM_Item pmItem = (VSPM_Item) NULL;
	 
	do {
		
		// 1.  Open the policy file.
		if ((pmd=VSPM_Open(POLICYFILE, &status)) == NULL) {
			rc = (HRESULT)status;
			break;
		}
		
		// 2. Get the PTA container index by name.
		if ((ptaContainer = VSPM_GetContainerByNameFromDescriptor(
			pmd, PTACONTAINER, &status)) == NULL) {
			rc = (HRESULT) status;
			break;
		}

		// 3. Get the SGMSPRS Container index by name
		if ((sgmsprsContainer = VSPM_GetContainerByNameFromDescriptor(
			pmd, SGMSPRSCONTAINER, &status)) == NULL) {
			rc = (HRESULT) status;
			break;
		}

		// Get the logLevel first.
		// now try and get the log level
		// Get the Log level from the file
		if ((pmItem = VSPM_GetItemByName (
			sgmsprsContainer, LOGLEVEL, &status )) == NULL) {
			rc = (HRESULT) status;
			
			// we are going to ignore the error here and continue
			rc = S_OK;

			// we will set the log level to INFO and continue
			logWrapper.setLogLevel(CLogWrapper::LOG_INFO);
		}
		else
		{
			// set the log level after i get it
			const char* logLevel = (const char*)VSPM_GetValue(pmItem, &status);
			
			int level = atoi(logLevel);
			
			logWrapper.setLogLevel(level);
			
			// need to re-use this pmItem. Free it now.
			VSPM_FreeItem(pmItem, &status);
		}

		// Get the LogFile name from the file
		if ((pmItem = VSPM_GetItemByName (
			sgmsprsContainer, LOGFILE, &status )) == NULL) {
			rc = (HRESULT) status;
			// we are going to ignore the error. we will not have any logging in this
			// case
			rc = S_OK;
		}
		else
		{
			VSString strLogFileName = (const char*)VSPM_GetValue(pmItem, &status);
		
			// need to re-use this pmItem. Free it now.
			VSPM_FreeItem(pmItem, &status);

			// now try and create the log file
			// only if this call succeeds will further messages be logged
			logWrapper.setLogFile(strLogFileName);	//set the log file name			
			
		}
		
		logWrapper.LogMessage(CLogWrapper::LOG_DEBUG, __LINE__, __FILE__,
						"GetConfiguration::Getting the PTAAPPNAME.", 0);

		// 4. Get PTA application name
		if ((pmItem = VSPM_GetItemByName (
			ptaContainer, PTAAPPNAME, &status )) == NULL) {
			rc = (HRESULT) status;
			logWrapper.LogMessage(CLogWrapper::LOG_CRITICAL, __LINE__, __FILE__,
				"GetConfiguration::Getting the PTA name failed.", rc);
			break;
		}
		pInfo->PTAApplication = (const char*)VSPM_GetValue(pmItem, &status);
		// need to re-use this pmItem. Free it now.
		VSPM_FreeItem(pmItem, &status);
		
		logWrapper.LogMessage(CLogWrapper::LOG_DEBUG, __LINE__, __FILE__,
					"GetConfiguration::Getting the PTAFILE.", 0);
		// 6. Get PTA profile 
		if ((pmItem = VSPM_GetItemByName (
			sgmsprsContainer, PTAFILE, &status )) == NULL) {
			rc = (HRESULT) status;
			logWrapper.LogMessage(CLogWrapper::LOG_CRITICAL, __LINE__, __FILE__,
					"GetConfiguration::Getting the PTAFILE failed.", rc);
			break;
		}
		pInfo->PTAProfile = (const char*)VSPM_GetValue(pmItem, &status);
		// need to re-use this pmItem. Free it now.
		VSPM_FreeItem(pmItem, &status);

		logWrapper.LogMessage(CLogWrapper::LOG_DEBUG, __LINE__, __FILE__,
					"GetConfiguration::Getting the PTAPASSWORD.", 0);
		// 7. Get PTA password 
		if ((pmItem = VSPM_GetItemByName (
			sgmsprsContainer, PTAPASSWORD, &status )) == NULL) {
			rc = (HRESULT) status;
			logWrapper.LogMessage(CLogWrapper::LOG_CRITICAL, __LINE__, __FILE__,
				"GetConfiguration::Getting the PTA password failed.", rc);
			break;
		}
		pInfo->PTAPassword = (const char*)VSPM_GetValue(pmItem, &status);
		// need to re-use this pmItem. Free it now.
		VSPM_FreeItem(pmItem, &status);

		logWrapper.LogMessage(CLogWrapper::LOG_DEBUG, __LINE__, __FILE__,
						"GetConfiguration::Getting the DEBUGMODE.", 0);
		// 8. Get DebugMode
		if ((pmItem = VSPM_GetItemByName (
			sgmsprsContainer, DEBUGMODE, &status )) == NULL) {
			rc = (HRESULT) status;
			logWrapper.LogMessage(CLogWrapper::LOG_CRITICAL, __LINE__, __FILE__,
					"GetConfiguration::Getting the debug mode failed.", rc);
			break;
		}
		if ((VSString((const char*)VSPM_GetValue(pmItem, &status))) == "1")
			debugMode = TRUE; // global var

		// need to re-use this pmItem. Free it now.
		VSPM_FreeItem(pmItem, &status);

		// 9. Get SMIME Debug file if debugMode = true
		if (debugMode) {
			logWrapper.LogMessage(CLogWrapper::LOG_DEBUG, __LINE__, __FILE__,
						"GetConfiguration::Getting the DEBUGSMIMEFILE.", 0);
			if ((pmItem = VSPM_GetItemByName (
				sgmsprsContainer, DEBUGSMIMEFILE, &status )) == NULL) {
				rc = (HRESULT) status;
				logWrapper.LogMessage(CLogWrapper::LOG_CRITICAL, __LINE__, __FILE__,
						"GetConfiguration::Getting the debug s-mime file failed.", rc);
				break;
			}
			debugSMIMEFile = (const char*)VSPM_GetValue(pmItem, &status);

			// need to re-use this pmItem. Free it now.
			VSPM_FreeItem(pmItem, &status);
		} // end debugMode

		logWrapper.LogMessage(CLogWrapper::LOG_DEBUG, __LINE__, __FILE__,
					"GetConfiguration::Getting the AUTHDLL.", 0);
		// 10. Get Auth DLL for PTA to bypass UI
		if ((pmItem = VSPM_GetItemByName (
			sgmsprsContainer, AUTHDLL, &status )) == NULL) {
			rc = (HRESULT) status;
			logWrapper.LogMessage(CLogWrapper::LOG_CRITICAL, __LINE__, __FILE__,
				"GetConfiguration::Getting the Auth DLL failed.", rc);
			break;
		}
		pInfo->AuthDLL = (const char*)VSPM_GetValue(pmItem, &status);
		// need to re-use this pmItem. Free it now.
		VSPM_FreeItem(pmItem, &status);

		logWrapper.LogMessage(CLogWrapper::LOG_DEBUG, __LINE__, __FILE__,
					"GetConfiguration::Getting the USEENCCERT.", 0);
		// 11. Get useEncCert Flag
		if ((pmItem = VSPM_GetItemByName (
			sgmsprsContainer, USEENCCERT, &status )) == NULL) {
			rc = (HRESULT) status;
			logWrapper.LogMessage(CLogWrapper::LOG_CRITICAL, __LINE__, __FILE__,
					"GetConfiguration::Getting the useEncCert failed.", rc);
			break;
		}
		pInfo->UseEncCert = (const char*)VSPM_GetValue(pmItem, &status);
		// need to re-use this pmItem. Free it now.
		VSPM_FreeItem(pmItem, &status);

		logWrapper.LogMessage(CLogWrapper::LOG_DEBUG, __LINE__, __FILE__,
				"GetConfiguration::Getting the REENCRYPTEMAIL.", 0);
		// 12. Get REENCRYPTEMAIL
		if ((pmItem = VSPM_GetItemByName (
			sgmsprsContainer, REENCRYPTEMAIL, &status )) == NULL) {
			rc = (HRESULT) status;
			logWrapper.LogMessage(CLogWrapper::LOG_CRITICAL, __LINE__, __FILE__,
				"GetConfiguration::Getting reEncryptEmail failed.", rc);
			break;
		}
		pInfo->ReEncryptEmail = (const char*)VSPM_GetValue(pmItem, &status);
		// need to re-use this pmItem. Free it now.
		VSPM_FreeItem(pmItem, &status);

		logWrapper.LogMessage(CLogWrapper::LOG_DEBUG, __LINE__, __FILE__,
							 "GetConfiguration::Getting the BASE64ATTACHMENT.", 0);
		// 13. Get Base64Attachment
		if ((pmItem = VSPM_GetItemByName (
			sgmsprsContainer, BASE64ATTACHMENT, &status )) == NULL) {
			rc = (HRESULT) status;
			logWrapper.LogMessage(CLogWrapper::LOG_CRITICAL, __LINE__, __FILE__,
				"GetConfiguration::Getting Base64Attachment failed.", rc);
			break;
		}
		pInfo->Base64Attachment = (const char*)VSPM_GetValue(pmItem, &status);
		// need to re-use this pmItem. Free it now.
		VSPM_FreeItem(pmItem, &status);

		logWrapper.LogMessage(CLogWrapper::LOG_DEBUG, __LINE__, __FILE__,
			"GetConfiguration::Getting the CERTRESSOURCE.", 0);
		// 14. Get CertResolutionSource
		if ((pmItem = VSPM_GetItemByName (
			sgmsprsContainer, CERTRESSOURCE, &status )) == NULL) {
			rc = (HRESULT) status;
			logWrapper.LogMessage(CLogWrapper::LOG_CRITICAL, __LINE__, __FILE__,
				"GetConfiguration::Getting CertResolutionSource failed.", rc);
			break;
		}
		pInfo->CertResSource = (const char*)VSPM_GetValue(pmItem, &status);
		// need to re-use this pmItem. Free it now.
		VSPM_FreeItem(pmItem, &status);

		logWrapper.LogMessage(CLogWrapper::LOG_DEBUG, __LINE__, __FILE__,
			"GetConfiguration::Before Getting ROAMING.", 0);
		// 15. Get Roaming
		if ((pmItem = VSPM_GetItemByName (
			sgmsprsContainer, ROAMING, &status )) == NULL) {
			rc = (HRESULT) status;
			logWrapper.LogMessage(CLogWrapper::LOG_CRITICAL, __LINE__, __FILE__,
				"GetConfiguration::Getting Roaming failed.", rc);
			break;
		}
		pInfo->Roaming = (const char*)VSPM_GetValue(pmItem, &status);
		// need to re-use this pmItem. Free it now.
		VSPM_FreeItem(pmItem, &status);

		logWrapper.LogMessage(CLogWrapper::LOG_DEBUG, __LINE__, __FILE__,
				"GetConfiguration::Getting CLIENTINFO.", 0);
		// 16. Get ClientInfo
		if ((pmItem = VSPM_GetItemByName (
			sgmsprsContainer, CLIENTINFO, &status )) == NULL) {
			rc = (HRESULT) status;
			logWrapper.LogMessage(CLogWrapper::LOG_CRITICAL, __LINE__, __FILE__,
				"GetConfiguration::Getting ClientInfo failed.", rc);
			break;
		}
		pInfo->ClientInfo = (const char*)VSPM_GetValue(pmItem, &status);
		// need to re-use this pmItem. Free it now.
		VSPM_FreeItem(pmItem, &status);

		logWrapper.LogMessage(CLogWrapper::LOG_DEBUG, __LINE__, __FILE__,
				"GetConfiguration::Before Getting CLIENTINFOSIG.", 0);
		// 17. Get ClientInfoSig
		if ((pmItem = VSPM_GetItemByName (
			sgmsprsContainer, CLIENTINFOSIG, &status )) == NULL) {
			rc = (HRESULT) status;
			logWrapper.LogMessage(CLogWrapper::LOG_CRITICAL, __LINE__, __FILE__,
				"GetConfiguration::Getting ClientInfoSig failed.", rc);
			break;
		}
		pInfo->ClientInfoSig = (const char*)VSPM_GetValue(pmItem, &status);
		// need to re-use this pmItem. Free it now.
		VSPM_FreeItem(pmItem, &status);

		logWrapper.LogMessage(CLogWrapper::LOG_DEBUG, __LINE__, __FILE__,
			"GetConfiguration::Before Getting CERTRESOLUTEURL.", 0);
		// 18. Get CertResolutionUrl
		if ((pmItem = VSPM_GetItemByName (
			sgmsprsContainer, CERTRESOLUTEURL, &status )) == NULL) {
			rc = (HRESULT) status;
			logWrapper.LogMessage(CLogWrapper::LOG_CRITICAL, __LINE__, __FILE__,
				"GetConfiguration::Getting CertResolutionUrl failed.", rc);
			break;
		}
		pInfo->CertResolutionURL = (const char*)VSPM_GetValue(pmItem, &status);
		// need to re-use this pmItem. Free it now.
		VSPM_FreeItem(pmItem, &status);
		
		logWrapper.LogMessage(CLogWrapper::LOG_DEBUG, __LINE__, __FILE__,
					"GetConfiguration::Before Getting SSCEMAIL.", 0);
		// 19. Get SSC Email
		if ((pmItem = VSPM_GetItemByName (
			sgmsprsContainer, SSCEMAIL, &status )) == NULL) {
			rc = (HRESULT) status;
			logWrapper.LogMessage(CLogWrapper::LOG_CRITICAL, __LINE__, __FILE__,
				"GetConfiguration::Getting SSC Email failed.", rc);
			break;
		}
		pInfo->SSCEmail = (const char*)VSPM_GetValue(pmItem, &status);
		// need to re-use this pmItem. Free it now.
		VSPM_FreeItem(pmItem, &status);

		logWrapper.LogMessage(CLogWrapper::LOG_DEBUG, __LINE__, __FILE__,
			"GetConfiguration::Before Getting SSCSUBJECT.", 0);
		// 20. Get SSC Subject
		if ((pmItem = VSPM_GetItemByName (
			sgmsprsContainer, SSCSUBJECT, &status )) == NULL) {
			rc = (HRESULT) status;
			logWrapper.LogMessage(CLogWrapper::LOG_CRITICAL, __LINE__, __FILE__,
					"GetConfiguration::Getting SSC Subject failed.", rc);
			break;
		}
		pInfo->SSCSubject = (const char*)VSPM_GetValue(pmItem, &status);
		// need to re-use this pmItem. Free it now.
		VSPM_FreeItem(pmItem, &status);


		
		logWrapper.LogMessage(CLogWrapper::LOG_DEBUG, __LINE__, __FILE__,
			"GetConfiguration::Before Getting SCType.", 0);
		// 21. Get SCTYPE
		if ((pmItem = VSPM_GetItemByName (
			sgmsprsContainer, SCTYPE, &status )) == NULL) {
			rc = (HRESULT) status;
			logWrapper.LogMessage(CLogWrapper::LOG_CRITICAL, __LINE__, __FILE__,
					"GetConfiguration::Getting SSC Subject failed.", rc);
			break;
		}
		pInfo->SCType = (const char*)VSPM_GetValue(pmItem, &status);
		// need to re-use this pmItem. Free it now.
		VSPM_FreeItem(pmItem, &status);


		logWrapper.LogMessage(CLogWrapper::LOG_DEBUG, __LINE__, __FILE__,
			"GetConfiguration::Before Getting supportedPTAVersions.", 0);
		// 21. Get SCTYPE
		if ((pmItem = VSPM_GetItemByName (
			sgmsprsContainer, SUPPORTED_PTA_VERSIONS, &status )) == NULL) {
			rc = (HRESULT) status;
			logWrapper.LogMessage(CLogWrapper::LOG_CRITICAL, __LINE__, __FILE__,
					"GetConfiguration::Getting supportedPTAVersions failed.", rc);
			break;
		}
		pInfo->SupportedPTAVersions = (const char*)VSPM_GetValue(pmItem, &status);
		// need to re-use this pmItem. Free it now.
		VSPM_FreeItem(pmItem, &status);

		// 21. Get PTA Path
		if ((pmItem = VSPM_GetItemByName (
			sgmsprsContainer, PTAPATH, &status )) == NULL) {
			rc = (HRESULT) status;
			logWrapper.LogMessage(CLogWrapper::LOG_CRITICAL, __LINE__, __FILE__,
					"GetConfiguration::Getting pta path failed.", rc);
			break;
		}
		pInfo->PTAProfilePath = (const char*)VSPM_GetValue(pmItem, &status);
		// need to re-use this pmItem. Free it now.
		VSPM_FreeItem(pmItem, &status);

/*
		printf("%sPTA Application = %s\nPTA Profile = %s\nPTA Password = %s\nPTA TimeOut = %s\nDebugMode = %d\nDebugSMIMEFile = %s\nAuth DLL= %s\n", 
				DEBUGLINE, (const char *)pInfo->PTAApplication,
				(const char *)pInfo->PTAProfile,
				(const char *)pInfo->PTAPassword,
				(const char *)pInfo->PassWordTimeOut, debugMode,
				(const char *)debugSMIMEFile,
				(const char *)pInfo->AuthDLL);
				/*/


	} while (0);
	
	logWrapper.LogMessage(CLogWrapper::LOG_DEBUG, __LINE__, __FILE__,
			"GetConfiguration::Before VSPM_FreeContainer for ptaContainer .", 0);

	if (ptaContainer != NULL) VSPM_FreeContainer(ptaContainer, &status);

	logWrapper.LogMessage(CLogWrapper::LOG_DEBUG, __LINE__, __FILE__,
		"GetConfiguration::Before VSPM_FreeContainer for sgmsprsContainer.", 0);

	if (sgmsprsContainer != NULL) VSPM_FreeContainer(sgmsprsContainer, &status);
	
	logWrapper.LogMessage(CLogWrapper::LOG_DEBUG, __LINE__, __FILE__,
		"GetConfiguration::Before VSPM_Close.", 0);

	if (pmd != NULL) VSPM_Close(pmd);
	

	return rc;
}