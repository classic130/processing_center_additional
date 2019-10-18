//#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <sys/types.h>
//#include <sys/stat.h>
//#include <fcntl.h>
#include <locale.h>
#include "vspmc.h"


int main(int argc, char *argv[])
{
	VSPM_STATUS status = VSPM_STATUS_NO_ERROR;
	VSPM_Descriptor fd = NULL;
	VSPM_PARAMETER param = NULL;
	char * locale = NULL;
	char * errmsg = NULL;
	const char * value = NULL;
	const char *protocol = NULL;
	const char *hostname = NULL;
	const char *port = NULL;
	const char *cgiUri = NULL;

	/* This is required to allow proper I18N message handling */
	locale = setlocale(LC_ALL, "");

	if (!locale)
		printf("Cannot operate in the requested locale.\nContinuing in the C locale.\n");


	if (argc < 2) {
		printf("Usage: %s policy_file_name \n\n", argv[0]);
		exit(1);
	}

	do {

		fd = VSPM_Open(argv[1], &status);
		if (status != VSPM_STATUS_NO_ERROR) {

			errmsg = (char *) VSPM_DescribeStatus(fd, status);
			printf("Error %s\n", errmsg);
			break;
		}

		unsigned int paramCount = VSPM_GetParameterCount(fd, VSPM_END_USER, &status);
		if (status != VSPM_STATUS_NO_ERROR) {
	
			errmsg = (char *) VSPM_DescribeStatus(fd, status);
			printf("Error %s\n", errmsg);
			break;
		}

		int i = 0;
		for (i = 0; i < paramCount; i++) {
			
			param = VSPM_GetParameter(fd, VSPM_END_USER, i, &status);
			if (status != VSPM_STATUS_NO_ERROR) {
	
				errmsg = (char *) VSPM_DescribeStatus(fd, status);
				printf("Error %s\n", errmsg);
				break;
			}

			value = VSPM_GetDisplayName(param, &status);
			if (status != VSPM_STATUS_NO_ERROR) {
	
				errmsg = (char *) VSPM_DescribeStatus(fd, status);
				printf("Error %s\n", errmsg);
				break;
			}

			printf("Parameter %s\n", value);
			VSPM_FreeString((char *)value, &status);
			value = NULL;

			value = VSPM_GetInternalName(param, &status);
			if (status != VSPM_STATUS_NO_ERROR) {
	
				errmsg = (char *) VSPM_DescribeStatus(fd, status);
				printf("Error %s\n", errmsg);
				break;
			}

			printf("\tInternal Name : %s\n", value);
			VSPM_FreeString((char *)value, &status);
			value = NULL;

			VSPM_FIELD_PROCESSING_TYPE fieldType = VSPM_GetFieldProcessingType(param, &status);
			if (status != VSPM_STATUS_NO_ERROR) {
	
				errmsg = (char *) VSPM_DescribeStatus(fd, status);
				printf("Error %s\n", errmsg);
				break;
			}

			switch (fieldType) {
			case VSPM_USER_INPUT_FIELD:
				printf("\tProcessing Type : User Input\n");
				break;
			case VSPM_USER_SELECTABLE_FIELD:
				printf("\tProcessing Type : User Selectable\n");
				break;
			case VSPM_HARD_CODED_FIELD:
				printf("\tProcessing Type : Hard Coded\n");
				break;
			case VSPM_SOFTWARE_CONFIG_FIELD:
				printf("\tProcessing Type : Software Config\n");
				break;
			case VSPM_DISPLAY_ONLY_FIELD:
				printf("\tProcessing Type : Display Only\n");
				break;
			}

			VSPM_VALUE_TAG valueTag = VSPM_GetValueTag(param, &status);
			if (status != VSPM_STATUS_NO_ERROR) {
	
				errmsg = (char *) VSPM_DescribeStatus(fd, status);
				printf("Error %s\n", errmsg);
				break;
			}

			switch (valueTag) {
			case VSPM_VALUE_TEXT:
				printf("\tValue Type : TEXT\n");
				break;
			case VSPM_VALUE_T61:
				printf("\tValue Type : T61\n");
				break;
			case VSPM_VALUE_NUMBER:
				printf("\tValue Type : NUMBER\n");
				break;
			case VSPM_VALUE_BASE64:
				printf("\tValue Type : BASE64\n");
				break;
			case VSPM_VALUE_EMAIL:
				printf("\tValue Type : EMAIL\n");
				break;
			case VSPM_VALUE_PHONE:
				printf("\tValue Type : PHONE\n");
				break;
			case VSPM_VALUE_DATE:
				printf("\tValue Type : DATE\n");
				break;
			case VSPM_VALUE_CLEAR:
				printf("\tValue Type : CLEAR\n");
				break;
			case VSPM_VALUE_PASSCODE:
				printf("\tValue Type : PASSCODE\n");
				break;
			}

			VSPM_REQUIREMENT req = VSPM_GetRequirement(param, &status);
			if (status != VSPM_STATUS_NO_ERROR) {
	
				errmsg = (char *) VSPM_DescribeStatus(fd, status);
				printf("Error %s\n", errmsg);
				break;
			}

			if (req == VSPM_REQ_OPTIONAL) {
				printf("\tRequirement : Optional\n");
			}
			else {
				printf("\tRequirement : Mandatory\n");
			}


			unsigned short minLen = VSPM_GetMinLen(param, &status);
			if (status != VSPM_STATUS_NO_ERROR) {
	
				errmsg = (char *) VSPM_DescribeStatus(fd, status);
				printf("Error %s\n", errmsg);
				break;
			}

			printf("\tMinimum Length : %d\n", minLen);


			unsigned short maxLen = VSPM_GetMaxLen(param, &status);
			if (status != VSPM_STATUS_NO_ERROR) {
	
				errmsg = (char *) VSPM_DescribeStatus(fd, status);
				printf("Error %s\n", errmsg);
				break;
			}

			printf("\tMaximum Length : %d\n", maxLen);


			VSPM_FreeParam(param, &status);
			param = NULL;


		} /* for */

		if (status != VSPM_STATUS_NO_ERROR)
			break;


		value = VSPM_GetCertIssuerDN(fd, VSPM_END_USER, &status);
		if (status != VSPM_STATUS_NO_ERROR) {
	
			errmsg = (char *) VSPM_DescribeStatus(fd, status);
			printf("Error %s\n", errmsg);
			break;
		}

		printf("\nIssuer Cert DN : %s\n\n", value);

		VSPM_FreeString((char *)value, &status);
		value = NULL;

		value = VSPM_GetCertSubjectDNTemplate(fd, VSPM_END_USER, &status);
		if (status != VSPM_STATUS_NO_ERROR) {
	
			errmsg = (char *) VSPM_DescribeStatus(fd, status);
			printf("Error %s\n", errmsg);
			break;
		}

		printf("\nSubject Cert DN Template : %s\n\n", value);

		VSPM_FreeString((char *)value, &status);
		value = NULL;

		VSPM_AUTH_SCHEME_TAG authTag = VSPM_GetAuthSchemeTag (fd, &status);
		if (status != VSPM_STATUS_NO_ERROR) {
	
			errmsg = (char *) VSPM_DescribeStatus(fd, status);
			printf("Error %s\n", errmsg);
			break;
		}

		if (authTag == VSPM_MANUAL_AUTH)
			printf("\nAuthentication Scheme : Manual Auth\n\n");
		else
			printf("\nAuthentication Scheme : Auto Auth\n\n");


		VSPM_KEY_MANAGER_TAG kmTag = VSPM_GetKeyManagerTag (fd, &status);
		if (status != VSPM_STATUS_NO_ERROR) {
	
			errmsg = (char *) VSPM_DescribeStatus(fd, status);
			printf("Error %s\n", errmsg);
			break;
		}

		if (kmTag == VSPM_NO_KEY_MANAGER)
			printf("\nKey Manager : No Key Manager\n\n");
		else if (kmTag == VSPM_SINGLE_KEY)
			printf("\nKey Manager : Single Key\n\n");
		else
			printf("\nKey Manager : Dual Key\n\n");


		VSPM_GetEnrollmentURL(fd, &protocol, &hostname, &port, &cgiUri, &status);
		if (status != VSPM_STATUS_NO_ERROR) {
	
			errmsg = (char *) VSPM_DescribeStatus(fd, status);
			printf("Error %s\n", errmsg);
			break;
		}

		printf("\nEnrollment URL : %s://%s:%s%s\n\n", protocol, hostname, port, cgiUri);

		VSPM_FreeString((char *)protocol, &status);
		protocol = NULL;
		VSPM_FreeString((char *)hostname, &status);
		hostname = NULL;
		VSPM_FreeString((char *)port, &status);
		port = NULL;
		VSPM_FreeString((char *)cgiUri, &status);
		cgiUri = NULL;

		VSPM_GetCRSEnrollmentURL(fd, &protocol, &hostname, &port, &cgiUri, &status);
		if (status != VSPM_STATUS_NO_ERROR) {
	
			errmsg = (char *) VSPM_DescribeStatus(fd, status);
			printf("Error %s\n", errmsg);
			break;
		}

		printf("\nCRS Enrollment URL : %s://%s:%s%s\n\n", protocol, hostname, port, cgiUri);

		VSPM_FreeString((char *)protocol, &status);
		protocol = NULL;
		VSPM_FreeString((char *)hostname, &status);
		hostname = NULL;
		VSPM_FreeString((char *)port, &status);
		port = NULL;
		VSPM_FreeString((char *)cgiUri, &status);
		cgiUri = NULL;

		unsigned int bufSize = 0;
		VSPM_GetCertIssuerChain(fd, VSPM_END_USER, 0, (char **) &value, &bufSize, &status);
		if (status != VSPM_STATUS_NO_ERROR) {
	
			errmsg = (char *) VSPM_DescribeStatus(fd, status);
			printf("Error %s\n", errmsg);
			break;
		}

		FILE* ofd = fopen("cacert.X509", "w");
		if (ofd != NULL) {

			fwrite(value, bufSize, 1, ofd); 
			fclose(ofd);

		}

		VSPM_FreeCertBuf((char *)value, &status);
		value = NULL;

	} while (0);

	if (errmsg)
		VSPM_FreeString((char *)errmsg, &status);

	if (param)
		VSPM_FreeParam(param, &status);

	if (value)
		VSPM_FreeString((char *)value, &status);

	if (fd)
		VSPM_Close(fd);

	return (int)status;
}
