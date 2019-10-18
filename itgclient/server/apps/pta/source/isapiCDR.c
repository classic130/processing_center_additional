
#include <stdio.h>
#include <string.h>

#include "vsvalsdk.h"

#define WIN32_LEAN_AN_MEAN
#include <windows.h>
#include <httpfilt.h>

/* From ISAPI/NSAPI book. */
#include <debug.h> /* debug macro */

/* Add cert fields to the request as http headers. */
/* Returns 0 or -1. */
int VSUnwrapCertificate(HTTP_FILTER_CONTEXT *pFC, 
                        PHTTP_FILTER_PREPROC_HEADERS pPreProcData, char *certB64) { 

  int i;                   /* miscellaneous counter/index */
  int status = 0;
  VSVAL_SDK *cpmValSDK;
  VSVAL_UserCtx ctx={0};
  VSVAL_CertFields *certDetails=0;

  char buff[1000], buff2[1000], buff3[1000];
 
  if (!certB64) { return -1; }

#ifdef DEBUGMSG
  Debug((DEST, "VSUnwrapCertificate: got here"));
#endif

  do {
	if ((status = VSVAL_Init(&cpmValSDK, &ctx, VAL_SDK_CURRENT_VERSION))) {
#ifdef DEBUGMSG
		Debug((DEST, "VSUnwrapCertificate: VSVAL_Init returned %d", status));
#endif
      break;
    }

    if ((status = VSVAL_ParseB64Cert(cpmValSDK, &ctx, &certDetails, certB64))) {
#ifdef DEBUGMSG
		Debug((DEST, "VSUnwrapCertificate: VSVAL_ParseB64Cert returned %d", status));
#endif
	  break;
	}


	if (certDetails->issuerOrganization) { 
		pPreProcData->AddHeader(pFC, "VSCERT-ISSUER-ORGANIZATION:", certDetails->issuerOrganization);
	}

	if (certDetails->issuerLocality) { 
		pPreProcData->AddHeader(pFC, "VSCERT-ISSUER-LOCALITY:", certDetails->issuerLocality);
	}
  
	if (certDetails->issuerCountry) { 
		pPreProcData->AddHeader(pFC, "VSCERT-ISSUER-COUNTRY:", certDetails->issuerCountry);
	}

	if (certDetails->issuerCommonName) { 
		pPreProcData->AddHeader(pFC, "VSCERT-ISSUER-CN:", certDetails->issuerCommonName);
	}
	sprintf(buff, "%d", certDetails->issuerOrgUnitCount);
	pPreProcData->AddHeader(pFC, "VSCERT-ISSUER-OUCOUNT:", buff);
  
    if (certDetails->issuerOrgUnitCount && certDetails->issuerOrganizationUnits) {
		/* VSCERT_ISS_OUn: */
		strcpy(buff2, "VSCERT-ISSUER-OU :");
		buff2[16] = 0; buff2[18] = 0;

		/* for each of them, create name = ouN, value = value */
		for (i = 0 ; i < certDetails->issuerOrgUnitCount; i++) {
			buff2[16] = (i + '1');
			pPreProcData->AddHeader(pFC, buff2, certDetails->issuerOrganizationUnits[i]);	
		}
	}

	if (certDetails->emailAddress) { 
		pPreProcData->AddHeader(pFC, "VSCERT-EMAIL:", certDetails->emailAddress);
	}
	if (certDetails->commonName) {
		pPreProcData->AddHeader(pFC, "VSCERT-CN:", certDetails->commonName);
	}
	if (certDetails->organization) {
		pPreProcData->AddHeader(pFC, "VSCERT-ORGANIZATION:", certDetails->organization);
	}
	if (certDetails->title) {
		pPreProcData->AddHeader(pFC, "VSCERT-TITLE:", certDetails->title);
	}	
	if (certDetails->notBefore) {
		pPreProcData->AddHeader(pFC, "VSCERT-NOTBEFORE:", certDetails->notBefore);
	}
	if (certDetails->notAfter) {
		pPreProcData->AddHeader(pFC, "VSCERT-NOTAFTER:", certDetails->notAfter);
	}	
	if (certDetails->uniqueID) {
		pPreProcData->AddHeader(pFC, "VSCERT-UNIQUE:", certDetails->uniqueID);
	}
	if (certDetails->address) {
		pPreProcData->AddHeader(pFC, "VSCERT-ADDRESS:", certDetails->address);
	}

	sprintf(buff, "%d", certDetails->orgUnitCount);
	pPreProcData->AddHeader(pFC, "VSCERT-OUCOUNT:", buff);

#ifdef DEBUGMSG
	Debug((DEST, "VSUnwrapCertificate: about to OUs"));	
#endif

	if (certDetails->orgUnitCount && certDetails->organizationUnits) {
		buff2[0] = 'V'; buff2[1] = 'S'; buff2[2] = 'C'; buff2[3] = 'E';
		buff2[4] = 'R'; buff2[5] = 'T'; buff2[6] = '-'; buff2[7] = 'O';
		buff2[8] = 'U'; buff2[9] = 0; buff2[10] = ':'; buff2[11] = 0;

		// for each of them, create name = ouN, value = value 
		for (i = 0 ; i < certDetails->orgUnitCount; i++) {	
			buff2[9] = (i + '1');
			pPreProcData->AddHeader(pFC, buff2, certDetails->organizationUnits[i]);
		}	
	}

#ifdef DEBUGMSG
	if (certDetails->commonName)
		Debug((DEST, "VSUnwrapCertificate: CN :%s:", certDetails->commonName));
	if (certDetails->emailAddress)
		Debug((DEST, "VSUnwrapCertificate: email :%s", certDetails->emailAddress));
#endif


#ifdef DEBUGMSG
		Debug((DEST, "VSUnwrapCertificate: about to Extensions"));	
#endif

		if(certDetails->v3Extensions.vsKeyUsage.szKeyUsage)
		{
			pPreProcData->AddHeader(pFC, "VSCERT-EX-KEYUSAGE:", certDetails->v3Extensions.vsKeyUsage.szKeyUsage);
		}

		/* Extended Key Usage Extension */
		if(certDetails->v3Extensions.vsExtendedKeyUsage.szExtendedKeyUsage)
		{
			pPreProcData->AddHeader(pFC, "VSCERT-EX-EKU:", certDetails->v3Extensions.vsExtendedKeyUsage.szExtendedKeyUsage);

		}

		/* SubjectAltNames */

		sprintf(buff, "%d", certDetails->v3Extensions.vsSubjectAltName.GeneralNames.nDirectoryNameCount);
		pPreProcData->AddHeader(pFC, "VSCERT-EX-SAN-DIRNAMECOUNT:", buff);
		if(certDetails->v3Extensions.vsSubjectAltName.GeneralNames.nDirectoryNameCount && 
			certDetails->v3Extensions.vsSubjectAltName.GeneralNames.szDirectoryName)
		{
			/* VSCERT_EX_SAN_DIRNAMEn */
			strcpy(buff3, "VSCERT-EX-SAN-DIRNAME :");
			buff3[21] = 0; buff3[23] = 0;


			/* for each of them, create name = VSCERT_EX_SAN_DIRNAMEn, value = value */
			for (i = 0 ; i < certDetails->v3Extensions.vsSubjectAltName.GeneralNames.nDirectoryNameCount; i++) {
				buff3[21] = (i + '1');
				pPreProcData->AddHeader(pFC, buff3, certDetails->v3Extensions.vsSubjectAltName.GeneralNames.szDirectoryName[i]);
			}
		}

		sprintf(buff, "%d", certDetails->v3Extensions.vsSubjectAltName.GeneralNames.nRFC822NameCount);
		pPreProcData->AddHeader(pFC, "VSCERT-EX-SAN-RFC822COUNT:", buff);
		if(certDetails->v3Extensions.vsSubjectAltName.GeneralNames.nRFC822NameCount && 
			certDetails->v3Extensions.vsSubjectAltName.GeneralNames.szRFC822Name)
		{
			/* VSCERT_EX_SAN_RFC822n */
			strcpy(buff3, "VSCERT-EX-SAN-RFC822 :");
			buff3[20] = 0; buff3[22] = 0;


			/* for each of them, create name = VSCERT_EX_SAN_RFC822n, value = value */
			for (i = 0 ; i < certDetails->v3Extensions.vsSubjectAltName.GeneralNames.nRFC822NameCount; i++) {
				buff3[20] = (i + '1');
				pPreProcData->AddHeader(pFC, buff3, certDetails->v3Extensions.vsSubjectAltName.GeneralNames.szRFC822Name[i]);
			}
		}

		sprintf(buff, "%d", certDetails->v3Extensions.vsSubjectAltName.GeneralNames.nDNSNameCount);
		pPreProcData->AddHeader(pFC, "VSCERT-EX-SAN-DNSNAMECOUNT:", buff);
		if(certDetails->v3Extensions.vsSubjectAltName.GeneralNames.nDNSNameCount && 
			certDetails->v3Extensions.vsSubjectAltName.GeneralNames.szDNSName)
		{
			/* VSCERT_EX_SAN_DNSNAMEn */
			strcpy(buff3, "VSCERT-EX-SAN-DNSNAME :");
			buff3[21] = 0; buff3[23] = 0;


			/* for each of them, create name = VSCERT_EX_SAN_DNSNAMEn, value = value */
			for (i = 0 ; i < certDetails->v3Extensions.vsSubjectAltName.GeneralNames.nDNSNameCount; i++) {
				buff3[21] = (i + '1');
				pPreProcData->AddHeader(pFC, buff3, certDetails->v3Extensions.vsSubjectAltName.GeneralNames.szDNSName[i]);
			}
		}

		sprintf(buff, "%d", certDetails->v3Extensions.vsSubjectAltName.GeneralNames.nUniformResourceIdentifierCount);
		pPreProcData->AddHeader(pFC, "VSCERT-EX-SAN-URICOUNT:", buff);
		if(certDetails->v3Extensions.vsSubjectAltName.GeneralNames.nUniformResourceIdentifierCount && 
			certDetails->v3Extensions.vsSubjectAltName.GeneralNames.szUniformResourceIdentifier)
		{
			/* VSCERT_EX_SAN_URIn */
			strcpy(buff3, "VSCERT-EX-SAN-URI :");
			buff3[17] = 0; buff3[19] = 0;


			/* for each of them, create name = VSCERT-EX-SAN-URIn, value = value */
			for (i = 0 ; i < certDetails->v3Extensions.vsSubjectAltName.GeneralNames.nUniformResourceIdentifierCount; i++) {
				buff3[17] = (i + '1');
				pPreProcData->AddHeader(pFC, buff3, certDetails->v3Extensions.vsSubjectAltName.GeneralNames.szUniformResourceIdentifier[i]);
			}
		}

		sprintf(buff, "%d", certDetails->v3Extensions.vsSubjectAltName.GeneralNames.nOtherNameUPNCount);
		pPreProcData->AddHeader(pFC, "VSCERT-EX-SAN-UPNCOUNT:", buff);
		if(certDetails->v3Extensions.vsSubjectAltName.GeneralNames.nOtherNameUPNCount && 
			certDetails->v3Extensions.vsSubjectAltName.GeneralNames.szOtherNameUPN)
		{
			/* VSCERT_EX_SAN_UPNn */
			strcpy(buff3, "VSCERT-EX-SAN-UPN :");
			buff3[17] = 0; buff3[19] = 0;


			/* for each of them, create name = VSCERT_EX_SAN_UPNn, value = value */
			for (i = 0 ; i < certDetails->v3Extensions.vsSubjectAltName.GeneralNames.nOtherNameUPNCount; i++) {
				buff3[17] = (i + '1');
				pPreProcData->AddHeader(pFC, buff3, certDetails->v3Extensions.vsSubjectAltName.GeneralNames.szOtherNameUPN[i]);
			}
		}

		sprintf(buff, "%d", certDetails->v3Extensions.vsSubjectAltName.GeneralNames.nOtherNameGUIDCount);
		pPreProcData->AddHeader(pFC, "VSCERT-EX-SAN-GUIDCOUNT:", buff);
		if(certDetails->v3Extensions.vsSubjectAltName.GeneralNames.nOtherNameGUIDCount && 
			certDetails->v3Extensions.vsSubjectAltName.GeneralNames.szOtherNameGUID)
		{
			/* VSCERT_EX_SAN_GUIDn */
			strcpy(buff3, "VSCERT-EX-SAN-GUID :");
			buff3[18] = 0; buff3[20] = 0;


			/* for each of them, create name = VSCERT-EX-SAN-GUIDn, value = value */
			for (i = 0 ; i < certDetails->v3Extensions.vsSubjectAltName.GeneralNames.nOtherNameGUIDCount; i++) {
				buff3[18] = (i + '1');
				pPreProcData->AddHeader(pFC, buff3, certDetails->v3Extensions.vsSubjectAltName.GeneralNames.szOtherNameGUID[i]);
			}
		}


		/* CDP Extension: FullName */
		if(certDetails->v3Extensions.vsCDP.nDPNamePresent)
		{
			sprintf(buff, "%d", certDetails->v3Extensions.vsCDP.distributionPointName.nDirectoryNameCount);
			pPreProcData->AddHeader(pFC, "VSCERT-EX-CDP-DPN-DIRNAMECOUNT:", buff);
			if(certDetails->v3Extensions.vsCDP.distributionPointName.nDirectoryNameCount && 
				certDetails->v3Extensions.vsCDP.distributionPointName.szDirectoryName)
			{
				/* VSCERT_EX_CDP_DPN_DIRNAMEn */
				strcpy(buff3, "VSCERT-EX-CDP-DPN-DIRNAME :");
				buff3[25] = 0; buff3[27] = 0;

				/* for each of them, create name = VSCERT_EX_CDP_DPN_DIRNAMEn, value = value */
				for (i = 0 ; i < certDetails->v3Extensions.vsCDP.distributionPointName.nDirectoryNameCount; i++) {
					buff3[25] = (i + '1');
					pPreProcData->AddHeader(pFC, buff3, certDetails->v3Extensions.vsCDP.distributionPointName.szDirectoryName[i]);
				}
			}

			sprintf(buff, "%d", certDetails->v3Extensions.vsCDP.distributionPointName.nRFC822NameCount);
			pPreProcData->AddHeader(pFC, "VSCERT-EX-CDP-DPN-RFC822COUNT:", buff);
			if(certDetails->v3Extensions.vsCDP.distributionPointName.nRFC822NameCount && 
				certDetails->v3Extensions.vsCDP.distributionPointName.szRFC822Name)
			{
				/* VSCERT_EX_CDP_DPN_RFC822n */
				strcpy(buff3, "VSCERT-EX-CDP-DPN-RFC822 :");
				buff3[24] = 0; buff3[26] = 0;

				/* for each of them, create name = VSCERT_EX_CDP_DPN_RFC822n, value = value */
				for (i = 0 ; i < certDetails->v3Extensions.vsCDP.distributionPointName.nRFC822NameCount; i++) {
					buff3[24] = (i + '1');
					pPreProcData->AddHeader(pFC, buff3, certDetails->v3Extensions.vsCDP.distributionPointName.szRFC822Name[i]);
				}
			}

			sprintf(buff, "%d", certDetails->v3Extensions.vsCDP.distributionPointName.nDNSNameCount);
			pPreProcData->AddHeader(pFC, "VSCERT-EX-CDP-DPN-DNSNAMECOUNT:", buff);
			if(certDetails->v3Extensions.vsCDP.distributionPointName.nDNSNameCount && 
				certDetails->v3Extensions.vsCDP.distributionPointName.szDNSName)
			{
				/* VSCERT_EX_CDP_DPN_DNSNAMEn */
				strcpy(buff3, "VSCERT-EX-CDP-DPN-DNSNAME :");
				buff3[25] = 0; buff3[27] = 0;

				/* for each of them, create name = VSCERT_EX_CDP_DPN_DNSNAMEn, value = value */
				for (i = 0 ; i < certDetails->v3Extensions.vsCDP.distributionPointName.nDNSNameCount; i++) {
					buff3[25] = (i + '1');
					pPreProcData->AddHeader(pFC, buff3, certDetails->v3Extensions.vsCDP.distributionPointName.szDNSName[i]);
				}
			}

			sprintf(buff, "%d", certDetails->v3Extensions.vsCDP.distributionPointName.nUniformResourceIdentifierCount);
			pPreProcData->AddHeader(pFC, "VSCERT-EX-CDP-DPN-URICOUNT:", buff);
			if(certDetails->v3Extensions.vsCDP.distributionPointName.nUniformResourceIdentifierCount && 
				certDetails->v3Extensions.vsCDP.distributionPointName.szUniformResourceIdentifier)
			{
				/* VSCERT_EX_CDP_DPN_URIn */
				strcpy(buff3, "VSCERT-EX-CDP-DPN-URI :");
				buff3[21] = 0; buff3[23] = 0;

				/* for each of them, create name = VSCERT_EX_CDP_DPN_URIn, value = value */
				for (i = 0 ; i < certDetails->v3Extensions.vsCDP.distributionPointName.nUniformResourceIdentifierCount; i++) {
					buff3[21] = (i + '1');
					pPreProcData->AddHeader(pFC, buff3, certDetails->v3Extensions.vsCDP.distributionPointName.szUniformResourceIdentifier[i]);
				}
			}

			sprintf(buff, "%d", certDetails->v3Extensions.vsCDP.distributionPointName.nOtherNameUPNCount);
			pPreProcData->AddHeader(pFC, "VSCERT-EX-CDP-DPN-UPNCOUNT:", buff);
			if(certDetails->v3Extensions.vsCDP.distributionPointName.nOtherNameUPNCount && 
				certDetails->v3Extensions.vsCDP.distributionPointName.szOtherNameUPN)
			{
				/* VSCERT_EX_CDP_DPN_UPNn */
				strcpy(buff3, "VSCERT-EX-CDP-DPN-UPN :");
				buff3[21] = 0; buff3[23] = 0;

				/* for each of them, create name = VSCERT_EX_CDP_DPN_UPNn, value = value */
				for (i = 0 ; i < certDetails->v3Extensions.vsCDP.distributionPointName.nOtherNameUPNCount; i++) {
					buff3[21] = (i + '1');
					pPreProcData->AddHeader(pFC, buff3, certDetails->v3Extensions.vsCDP.distributionPointName.szOtherNameUPN[i]);
				}
			}

			sprintf(buff, "%d", certDetails->v3Extensions.vsCDP.distributionPointName.nOtherNameGUIDCount);
			pPreProcData->AddHeader(pFC, "VSCERT-EX-CDP-DPN-GUIDCOUNT:", buff);
			if(certDetails->v3Extensions.vsCDP.distributionPointName.nOtherNameGUIDCount && 
				certDetails->v3Extensions.vsCDP.distributionPointName.szOtherNameGUID)
			{
				/* VSCERT_EX_CDP_DPN_GUIDn */
				strcpy(buff3, "VSCERT-EX-CDP-DPN-GUID :");
				buff3[22] = 0; buff3[24] = 0;

				/* for each of them, create name = VSCERT_EX_CDP_DPN_GUIDn, value = value */
				for (i = 0 ; i < certDetails->v3Extensions.vsCDP.distributionPointName.nOtherNameGUIDCount; i++) {
					buff3[22] = (i + '1');
					pPreProcData->AddHeader(pFC, buff3, certDetails->v3Extensions.vsCDP.distributionPointName.szOtherNameGUID[i]);
				}
			}
		}
		
		/* CDP Extension: ReasonFlags */
/*
		if(certDetails->v3Extensions.vsCDP.szReasonFlags)
		{
			pPreProcData->AddHeader(pFC, "VSCERT-EX-CDP-REASONS:", certDetails->v3Extensions.vsCDP.szReasonFlags);
		}
*/		
		/* CDP Extension: cRLIssuer */
		if(certDetails->v3Extensions.vsCDP.nCRLIssuerPresent)
		{
			sprintf(buff, "%d", certDetails->v3Extensions.vsCDP.cRLIssuerName.nDirectoryNameCount);
			pPreProcData->AddHeader(pFC, "VSCERT-EX-CDP-CRL-DIRNAMECOUNT:", buff);
			if(certDetails->v3Extensions.vsCDP.cRLIssuerName.nDirectoryNameCount && 
				certDetails->v3Extensions.vsCDP.cRLIssuerName.szDirectoryName)
			{
				/* VSCERT_EX_CDP_CRL_DIRNAMEn */
				strcpy(buff3, "VSCERT-EX-CDP-CRL-DIRNAME :");
				buff3[25] = 0; buff3[27] = 0;

				/* for each of them, create name = VSCERT_EX_CDP_CRL_DIRNAMEn, value = value */
				for (i = 0 ; i < certDetails->v3Extensions.vsCDP.cRLIssuerName.nDirectoryNameCount; i++) {
					buff3[25] = (i + '1');
					pPreProcData->AddHeader(pFC, buff3, certDetails->v3Extensions.vsCDP.cRLIssuerName.szDirectoryName[i]);
				}
			}

			sprintf(buff, "%d", certDetails->v3Extensions.vsCDP.cRLIssuerName.nRFC822NameCount);
			pPreProcData->AddHeader(pFC, "VSCERT-EX-CDP-CRL-RFC822COUNT:", buff);
			if(certDetails->v3Extensions.vsCDP.cRLIssuerName.nRFC822NameCount && 
				certDetails->v3Extensions.vsCDP.cRLIssuerName.szRFC822Name)
			{
				/* VSCERT_EX_CDP_CRL_RFC822n */
				strcpy(buff3, "VSCERT-EX-CDP-CRL-RFC822 :");
				buff3[24] = 0; buff3[26] = 0;

				/* for each of them, create name = VSCERT_EX_CDP_CRL_RFC822n, value = value */
				for (i = 0 ; i < certDetails->v3Extensions.vsCDP.cRLIssuerName.nRFC822NameCount; i++) {
					buff3[24] = (i + '1');
					pPreProcData->AddHeader(pFC, buff3, certDetails->v3Extensions.vsCDP.cRLIssuerName.szRFC822Name[i]);
				}
			}

			sprintf(buff, "%d", certDetails->v3Extensions.vsCDP.cRLIssuerName.nDNSNameCount);
			pPreProcData->AddHeader(pFC, "VSCERT-EX-CDP-CRL-DNSNAMECOUNT:", buff);
			if(certDetails->v3Extensions.vsCDP.cRLIssuerName.nDNSNameCount && 
				certDetails->v3Extensions.vsCDP.cRLIssuerName.szDNSName)
			{
				/* VSCERT_EX_CDP_CRL_DNSNAMEn */
				strcpy(buff3, "VSCERT-EX-CDP-CRL-DNSNAME :");
				buff3[25] = 0; buff3[27] = 0;

				/* for each of them, create name = VSCERT_EX_CDP_CRL_DNSNAMEn, value = value */
				for (i = 0 ; i < certDetails->v3Extensions.vsCDP.cRLIssuerName.nDNSNameCount; i++) {
					buff3[25] = (i + '1');
					pPreProcData->AddHeader(pFC, buff3, certDetails->v3Extensions.vsCDP.cRLIssuerName.szDNSName[i]);
				}

			}

			sprintf(buff, "%d", certDetails->v3Extensions.vsCDP.cRLIssuerName.nUniformResourceIdentifierCount);
			pPreProcData->AddHeader(pFC, "VSCERT-EX-CDP-CRL-URICOUNT:", buff);
			if(certDetails->v3Extensions.vsCDP.cRLIssuerName.nUniformResourceIdentifierCount && 
				certDetails->v3Extensions.vsCDP.cRLIssuerName.szUniformResourceIdentifier)
			{
				/* VSCERT_EX_CDP_CRL_URIn */
				strcpy(buff3, "VSCERT-EX-CDP-CRL-URI :");
				buff3[21] = 0; buff3[23] = 0;

				/* for each of them, create name = VSCERT_EX_CDP_CRL_URIn, value = value */
				for (i = 0 ; i < certDetails->v3Extensions.vsCDP.cRLIssuerName.nUniformResourceIdentifierCount; i++) {
					buff3[21] = (i + '1');
					pPreProcData->AddHeader(pFC, buff3, certDetails->v3Extensions.vsCDP.cRLIssuerName.szUniformResourceIdentifier[i]);
				}
			}

			sprintf(buff, "%d", certDetails->v3Extensions.vsCDP.cRLIssuerName.nOtherNameUPNCount);
			pPreProcData->AddHeader(pFC, "VSCERT-EX-CDP-CRL-UPNCOUNT:", buff);
			if(certDetails->v3Extensions.vsCDP.cRLIssuerName.nOtherNameUPNCount && 
				certDetails->v3Extensions.vsCDP.cRLIssuerName.szOtherNameUPN)
			{
				/* VSCERT_EX_CDP_CRL_UPNn */
				strcpy(buff3, "VSCERT-EX-CDP-CRL-UPN :");
				buff3[21] = 0; buff3[23] = 0;

				/* for each of them, create name = VSCERT_EX_CDP_CRL_UPNn, value = value */
				for (i = 0 ; i < certDetails->v3Extensions.vsCDP.cRLIssuerName.nOtherNameUPNCount; i++) {
					buff3[21] = (i + '1');
					pPreProcData->AddHeader(pFC, buff3, certDetails->v3Extensions.vsCDP.cRLIssuerName.szOtherNameUPN[i]);
				}
			}

			sprintf(buff, "%d", certDetails->v3Extensions.vsCDP.cRLIssuerName.nOtherNameGUIDCount);
			pPreProcData->AddHeader(pFC, "VSCERT-EX-CDP-CRL-GUIDCOUNT:", buff);
			if(certDetails->v3Extensions.vsCDP.cRLIssuerName.nOtherNameGUIDCount && 
				certDetails->v3Extensions.vsCDP.cRLIssuerName.szOtherNameGUID)
			{
				/* VSCERT_EX_CDP_CRL_GUIDn */
				strcpy(buff3, "VSCERT-EX-CDP-CRL-GUID :");
				buff3[22] = 0; buff3[24] = 0;

				/* for each of them, create name = VSCERT_EX_CDP_CRL_GUIDn, value = value */
				for (i = 0 ; i < certDetails->v3Extensions.vsCDP.cRLIssuerName.nOtherNameGUIDCount; i++) {
					buff3[22] = (i + '1');
					pPreProcData->AddHeader(pFC, buff3, certDetails->v3Extensions.vsCDP.cRLIssuerName.szOtherNameGUID[i]);
				}
			}
		}


  }while (0);

	VSVAL_FreeCertFields (cpmValSDK, certDetails);
	VSVAL_Final ( cpmValSDK );


  return 0;
}
