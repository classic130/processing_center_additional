/*
$Revision: 1.2.96.2 $
$Header: /cvs/itgclient/server/apps/pta/source/nsapiCDR.c,v 1.2.96.2 2003/07/30 02:34:20 sgoginen Exp $
*/
#ifdef NSAPI3_0
#include "nsapi.h"
#else
#include "base/pblock.h"
#include "base/session.h"
#include "frame/req.h"
#include "frame/protocol.h"  /* protocol_start_response */
#include "frame/http.h"       /* log_error */
#include "frame/log.h"       /* log_error */
#endif

#include "vsvalsdk.h"

#include <stdio.h>
#include <string.h>


int VSUnwrapCertificate ( pblock *pb, Session *sn, Request *rq)
{
	int i;                   /* miscellaneous counter/index */
	int status = 0;

	VSVAL_SDK *cpmValSDK;
	VSVAL_UserCtx ctx={0};
	VSVAL_CertFields *certDetails=0;

	char *certB64 = NULL;
	char buff[1000], buff2[1000], buff3[1000], *someP = 0;

	certB64 = pblock_findval ("auth-cert", rq->vars);
	if (!certB64) {
#ifdef DEBUG
		log_error (LOG_WARN, "VSUnwrapCertificate", sn, rq,
							 "Client certificate not found");
#endif
		return REQ_ABORTED;
	}

#ifdef DEBUG
	log_error (LOG_WARN, "VSUnwrapCertificate", sn, rq, "got here ");
#endif


	do 
	{
		if ((status = VSVAL_Init(&cpmValSDK, &ctx, VAL_SDK_CURRENT_VERSION))) {
#ifdef DEBUG
			log_error (LOG_WARN, "VSUnwrapCertificate", sn, rq,
								"VSVAL_Init returned non-zero %d", status);
#endif
			break;
		}	

		if ((status = VSVAL_ParseB64Cert(cpmValSDK, &ctx, &certDetails, certB64))) {
#ifdef DEBUG
			log_error (LOG_WARN, "VSUnwrapCertificate", sn, rq,
								"VSVAL_ParseB64Cert returned non-zero %d", status);
#endif
			break;	
		}

			/* for all non null values, throw into name values in pb */
		if (certDetails->issuerOrganization) { 
			pblock_nvinsert ("VSCERT_ISSUER_ORGANIZATION", certDetails->issuerOrganization, sn->client);
			pblock_nvinsert ("VSCERT_ISSUER_ORGANIZATION", certDetails->issuerOrganization, rq->headers);
		}

		if (certDetails->issuerLocality) { 
			pblock_nvinsert ("VSCERT_ISSUER_LOCALITY", certDetails->issuerLocality, sn->client);
			pblock_nvinsert ("VSCERT_ISSUER_LOCALITY", certDetails->issuerLocality, rq->headers);
		}
		if (certDetails->issuerCountry) { 
			pblock_nvinsert ("VSCERT_ISSUER_COUNTRY", certDetails->issuerCountry, sn->client);
			pblock_nvinsert ("VSCERT_ISSUER_COUNTRY", certDetails->issuerCountry, rq->headers);
		}	
		if (certDetails->issuerCommonName) { 
			pblock_nvinsert ("VSCERT_ISSUER_CN", certDetails->issuerCommonName, sn->client);
			pblock_nvinsert ("VSCERT_ISSUER_CN", certDetails->issuerCommonName, rq->headers);
		}
		pblock_nninsert ("VSCERT_ISSUER_OUCOUNT", certDetails->issuerOrgUnitCount, sn->client);
		pblock_nninsert ("VSCERT_ISSUER_OUCOUNT", certDetails->issuerOrgUnitCount, rq->headers);

		if (certDetails->issuerOrgUnitCount && certDetails->issuerOrganizationUnits) {
		  /* VSCERT_ISS_OUn, issouN */
		  strcpy(buff2, "VSCERT_ISSUER_OU");
		  buff2[16] = 0; buff2[17] = 0;

			buff[0] = 'i'; buff[1] = 's';  buff[2] = 's'; buff[3] = 'o'; buff[4] = 'u';
			buff[5] = 0; buff[6] = 0;
			
			/* for each of them, create name = ouN, value = value */
			for (i = 0 ; i < certDetails->issuerOrgUnitCount; i++) {
				buff[5] = (i + '1');
				buff2[16] = (i + '1');
				pblock_nvinsert (buff, certDetails->issuerOrganizationUnits[i], sn->client);
				pblock_nvinsert (buff2, certDetails->issuerOrganizationUnits[i], rq->headers);
			}
		}

		if (certDetails->emailAddress) { 
			pblock_nvinsert ("VSCERT_EMAIL", certDetails->emailAddress, sn->client);
			pblock_nvinsert ("VSCERT_EMAIL", certDetails->emailAddress, rq->headers);
		}
		if (certDetails->commonName) {
			pblock_nvinsert( "VSCERT_CN", certDetails->commonName, sn->client);
			pblock_nvinsert( "VSCERT_CN", certDetails->commonName, rq->headers);
		}
		if (certDetails->organization) {
			pblock_nvinsert( "VSCERT_ORGANIZATION", certDetails->organization, sn->client);
			pblock_nvinsert( "VSCERT_ORGANIZATION", certDetails->organization, rq->headers);
		}
		if (certDetails->title) {
			pblock_nvinsert( "VSCERT_TITLE", certDetails->title, sn->client);
			pblock_nvinsert( "VSCERT_TITLE", certDetails->title, rq->headers);
		}

		if (certDetails->notBefore) {
			pblock_nvinsert( "VSCERT_NOTBEFORE", certDetails->notBefore, sn->client);
			pblock_nvinsert( "VSCERT_NOTBEFORE", certDetails->notBefore, rq->headers);
		}
		if (certDetails->notAfter) {
			pblock_nvinsert( "VSCERT_NOTAFTER", certDetails->notAfter, sn->client);
			pblock_nvinsert( "VSCERT_NOTAFTER", certDetails->notAfter, rq->headers);
		}
		if (certDetails->uniqueID) {
			pblock_nvinsert ("VSCERT_UNIQUE", certDetails->uniqueID, sn->client);
			pblock_nvinsert ("VSCERT_UNIQUE", certDetails->uniqueID, rq->headers);
		}
		if (certDetails->address) {
			pblock_nvinsert ("VSCERT_ADDRESS", certDetails->address, sn->client);
			pblock_nvinsert ("VSCERT_ADDRESS", certDetails->address, rq->headers);
		}
		pblock_nninsert ("VSCERT_OUCOUNT", certDetails->orgUnitCount, sn->client);
		pblock_nninsert ("VSCERT_OUCOUNT", certDetails->orgUnitCount, rq->headers);



#ifdef DEBUG
		log_error (LOG_WARN, "VSUnwrapCertificate", sn, rq,"about to OUs");
#endif
		if (certDetails->orgUnitCount && certDetails->organizationUnits) {
			buff2[0] = 'V'; buff2[1] = 'S'; buff2[2] = 'C'; buff2[3] = 'E';
			buff2[4] = 'R'; buff2[5] = 'T'; buff2[6] = '_'; buff2[7] = 'O';
			buff2[8] = 'U'; buff2[9] = 0; buff2[10] = 0;
			buff[0] = 'o'; buff[1] = 'u'; buff[2] = 0; buff[3] = 0;
			/* for each of them, create name = ouN, value = value */
			for (i = 0 ; i < certDetails->orgUnitCount; i++) {
				buff[2] = (i + '1');
				buff2[9] = (i + '1');
				pblock_nvinsert (buff, certDetails->organizationUnits[i], sn->client);
				pblock_nvinsert (buff2, certDetails->organizationUnits[i], rq->headers);
			}
		}

#ifdef DEBUG
		if (certDetails->commonName)
			log_error (LOG_WARN, "VSUnwrapCertificate", sn, rq,"CN :%s:", certDetails->commonName);
		if (certDetails->emailAddress)
			log_error (LOG_WARN, "VSUnwrapCertificate", sn, rq, "email :%s", certDetails->emailAddress);
#endif

#ifdef DEBUG
		log_error (LOG_WARN, "VSUnwrapCertificate", sn, rq,
							 "about to Extensions");

		/* KeyUsage Extension */
		if (certDetails->v3Extensions.vsKeyUsage.szKeyUsage)
			log_error (LOG_WARN, "VSUnwrapCertificate", sn, rq,
								 "KeyUsage :%s", certDetails->v3Extensions.vsKeyUsage.szKeyUsage);
#endif

		if(certDetails->v3Extensions.vsKeyUsage.szKeyUsage)
		{
			pblock_nvinsert ("VSCERT_EX_KEYUSAGE", certDetails->v3Extensions.vsKeyUsage.szKeyUsage, sn->client);
			pblock_nvinsert ("VSCERT_EX_KEYUSAGE", certDetails->v3Extensions.vsKeyUsage.szKeyUsage, rq->headers);
		}

		/* Extended Key Usage Extension */
		if(certDetails->v3Extensions.vsExtendedKeyUsage.szExtendedKeyUsage)
		{
			pblock_nvinsert ("VSCERT_EX_EKU", certDetails->v3Extensions.vsExtendedKeyUsage.szExtendedKeyUsage, sn->client);
			pblock_nvinsert ("VSCERT_EX_EKU", certDetails->v3Extensions.vsExtendedKeyUsage.szExtendedKeyUsage, rq->headers);

		}

		/* SubjectAltNames */

		pblock_nninsert ("VSCERT_EX_SAN_DIRNAMECOUNT", certDetails->v3Extensions.vsSubjectAltName.GeneralNames.nDirectoryNameCount, sn->client);
		pblock_nninsert ("VSCERT_EX_SAN_DIRNAMECOUNT", certDetails->v3Extensions.vsSubjectAltName.GeneralNames.nDirectoryNameCount, rq->headers);
		if(certDetails->v3Extensions.vsSubjectAltName.GeneralNames.nDirectoryNameCount && 
			certDetails->v3Extensions.vsSubjectAltName.GeneralNames.szDirectoryName)
		{
			/* VSCERT_EX_SAN_DIRNAMEn */
			strcpy(buff3, "VSCERT_EX_SAN_DIRNAME");
			buff3[21] = 0; buff3[22] = 0;


			/* for each of them, create name = VSCERT_EX_SAN_DIRNAMEn, value = value */
			for (i = 0 ; i < certDetails->v3Extensions.vsSubjectAltName.GeneralNames.nDirectoryNameCount; i++) {
				buff3[21] = (i + '1');
				pblock_nvinsert (buff3, certDetails->v3Extensions.vsSubjectAltName.GeneralNames.szDirectoryName[i], sn->client);
				pblock_nvinsert (buff3, certDetails->v3Extensions.vsSubjectAltName.GeneralNames.szDirectoryName[i], rq->headers);
			}
		}

		pblock_nninsert ("VSCERT_EX_SAN_RFC822COUNT", certDetails->v3Extensions.vsSubjectAltName.GeneralNames.nRFC822NameCount, sn->client);
		pblock_nninsert ("VSCERT_EX_SAN_RFC822COUNT", certDetails->v3Extensions.vsSubjectAltName.GeneralNames.nRFC822NameCount, rq->headers);
		if(certDetails->v3Extensions.vsSubjectAltName.GeneralNames.nRFC822NameCount && 
			certDetails->v3Extensions.vsSubjectAltName.GeneralNames.szRFC822Name)
		{
			/* VSCERT_EX_SAN_RFC822n */
			strcpy(buff3, "VSCERT_EX_SAN_RFC822");
			buff3[20] = 0; buff3[21] = 0;


			/* for each of them, create name = VSCERT_EX_SAN_RFC822n, value = value */
			for (i = 0 ; i < certDetails->v3Extensions.vsSubjectAltName.GeneralNames.nRFC822NameCount; i++) {
				buff3[20] = (i + '1');
				pblock_nvinsert (buff3, certDetails->v3Extensions.vsSubjectAltName.GeneralNames.szRFC822Name[i], sn->client);
				pblock_nvinsert (buff3, certDetails->v3Extensions.vsSubjectAltName.GeneralNames.szRFC822Name[i], rq->headers);
			}
		}

		pblock_nninsert ("VSCERT_EX_SAN_DNSNAMECOUNT", certDetails->v3Extensions.vsSubjectAltName.GeneralNames.nDNSNameCount, sn->client);
		pblock_nninsert ("VSCERT_EX_SAN_DNSNAMECOUNT", certDetails->v3Extensions.vsSubjectAltName.GeneralNames.nDNSNameCount, rq->headers);
		if(certDetails->v3Extensions.vsSubjectAltName.GeneralNames.nDNSNameCount && 
			certDetails->v3Extensions.vsSubjectAltName.GeneralNames.szDNSName)
		{
			/* VSCERT_EX_SAN_DNSNAMEn */
			strcpy(buff3, "VSCERT_EX_SAN_DNSNAME");
			buff3[21] = 0; buff3[22] = 0;


			/* for each of them, create name = VSCERT_EX_SAN_DNSNAMEn, value = value */
			for (i = 0 ; i < certDetails->v3Extensions.vsSubjectAltName.GeneralNames.nDNSNameCount; i++) {
				buff3[21] = (i + '1');
				pblock_nvinsert (buff3, certDetails->v3Extensions.vsSubjectAltName.GeneralNames.szDNSName[i], sn->client);
				pblock_nvinsert (buff3, certDetails->v3Extensions.vsSubjectAltName.GeneralNames.szDNSName[i], rq->headers);
			}
		}

		pblock_nninsert ("VSCERT_EX_SAN_URICOUNT", certDetails->v3Extensions.vsSubjectAltName.GeneralNames.nUniformResourceIdentifierCount, sn->client);
		pblock_nninsert ("VSCERT_EX_SAN_URICOUNT", certDetails->v3Extensions.vsSubjectAltName.GeneralNames.nUniformResourceIdentifierCount, rq->headers);
		if(certDetails->v3Extensions.vsSubjectAltName.GeneralNames.nUniformResourceIdentifierCount && 
			certDetails->v3Extensions.vsSubjectAltName.GeneralNames.szUniformResourceIdentifier)
		{
			/* VSCERT_EX_SAN_URIn */
			strcpy(buff3, "VSCERT_EX_SAN_URI");
			buff3[17] = 0; buff3[18] = 0;


			/* for each of them, create name = VSCERT_EX_SAN_URIn, value = value */
			for (i = 0 ; i < certDetails->v3Extensions.vsSubjectAltName.GeneralNames.nUniformResourceIdentifierCount; i++) {
				buff3[17] = (i + '1');
				pblock_nvinsert (buff3, certDetails->v3Extensions.vsSubjectAltName.GeneralNames.szUniformResourceIdentifier[i], sn->client);
				pblock_nvinsert (buff3, certDetails->v3Extensions.vsSubjectAltName.GeneralNames.szUniformResourceIdentifier[i], rq->headers);
			}
		}

		pblock_nninsert ("VSCERT_EX_SAN_UPNCOUNT", certDetails->v3Extensions.vsSubjectAltName.GeneralNames.nOtherNameUPNCount, sn->client);
		pblock_nninsert ("VSCERT_EX_SAN_UPNCOUNT", certDetails->v3Extensions.vsSubjectAltName.GeneralNames.nOtherNameUPNCount, rq->headers);
		if(certDetails->v3Extensions.vsSubjectAltName.GeneralNames.nOtherNameUPNCount && 
			certDetails->v3Extensions.vsSubjectAltName.GeneralNames.szOtherNameUPN)
		{
			/* VSCERT_EX_SAN_UPNn */
			strcpy(buff3, "VSCERT_EX_SAN_UPN");
			buff3[17] = 0; buff3[18] = 0;


			/* for each of them, create name = VSCERT_EX_SAN_UPNn, value = value */
			for (i = 0 ; i < certDetails->v3Extensions.vsSubjectAltName.GeneralNames.nOtherNameUPNCount; i++) {
				buff3[17] = (i + '1');
				pblock_nvinsert (buff3, certDetails->v3Extensions.vsSubjectAltName.GeneralNames.szOtherNameUPN[i], sn->client);
				pblock_nvinsert (buff3, certDetails->v3Extensions.vsSubjectAltName.GeneralNames.szOtherNameUPN[i], rq->headers);
			}
		}

		pblock_nninsert ("VSCERT_EX_SAN_GUIDCOUNT", certDetails->v3Extensions.vsSubjectAltName.GeneralNames.nOtherNameGUIDCount, sn->client);
		pblock_nninsert ("VSCERT_EX_SAN_GUIDCOUNT", certDetails->v3Extensions.vsSubjectAltName.GeneralNames.nOtherNameGUIDCount, rq->headers);
		if(certDetails->v3Extensions.vsSubjectAltName.GeneralNames.nOtherNameGUIDCount && 
			certDetails->v3Extensions.vsSubjectAltName.GeneralNames.szOtherNameGUID)
		{
			/* VSCERT_EX_SAN_GUIDn */
			strcpy(buff3, "VSCERT_EX_SAN_GUID");
			buff3[18] = 0; buff3[19] = 0;


			/* for each of them, create name = VSCERT_EX_SAN_GUIDn, value = value */
			for (i = 0 ; i < certDetails->v3Extensions.vsSubjectAltName.GeneralNames.nOtherNameGUIDCount; i++) {
				buff3[18] = (i + '1');
				pblock_nvinsert (buff3, certDetails->v3Extensions.vsSubjectAltName.GeneralNames.szOtherNameGUID[i], sn->client);
				pblock_nvinsert (buff3, certDetails->v3Extensions.vsSubjectAltName.GeneralNames.szOtherNameGUID[i], rq->headers);
			}
		}


		/* CDP Extension: FullName */
		if(certDetails->v3Extensions.vsCDP.nDPNamePresent)
		{
			pblock_nninsert ("VSCERT_EX_CDP_DPN_DIRNAMECOUNT", certDetails->v3Extensions.vsCDP.distributionPointName.nDirectoryNameCount, sn->client);
			pblock_nninsert ("VSCERT_EX_CDP_DPN_DIRNAMECOUNT", certDetails->v3Extensions.vsCDP.distributionPointName.nDirectoryNameCount, rq->headers);
			if(certDetails->v3Extensions.vsCDP.distributionPointName.nDirectoryNameCount && 
				certDetails->v3Extensions.vsCDP.distributionPointName.szDirectoryName)
			{
				/* VSCERT_EX_CDP_DPN_DIRNAMEn */
				strcpy(buff3, "VSCERT_EX_CDP_DPN_DIRNAME");
				buff3[25] = 0; buff3[26] = 0;

				/* for each of them, create name = VSCERT_EX_CDP_DPN_DIRNAMEn, value = value */
				for (i = 0 ; i < certDetails->v3Extensions.vsCDP.distributionPointName.nDirectoryNameCount; i++) {
					buff3[25] = (i + '1');
					pblock_nvinsert (buff3, certDetails->v3Extensions.vsCDP.distributionPointName.szDirectoryName[i], sn->client);
					pblock_nvinsert (buff3, certDetails->v3Extensions.vsCDP.distributionPointName.szDirectoryName[i], rq->headers);
				}
			}

			pblock_nninsert ("VSCERT_EX_CDP_DPN_RFC822COUNT", certDetails->v3Extensions.vsCDP.distributionPointName.nRFC822NameCount, sn->client);
			pblock_nninsert ("VSCERT_EX_CDP_DPN_RFC822COUNT", certDetails->v3Extensions.vsCDP.distributionPointName.nRFC822NameCount, rq->headers);
			if(certDetails->v3Extensions.vsCDP.distributionPointName.nRFC822NameCount && 
				certDetails->v3Extensions.vsCDP.distributionPointName.szRFC822Name)
			{
				/* VSCERT_EX_CDP_DPN_RFC822n */
				strcpy(buff3, "VSCERT_EX_CDP_DPN_RFC822");
				buff3[24] = 0; buff3[25] = 0;

				/* for each of them, create name = VSCERT_EX_CDP_DPN_RFC822n, value = value */
				for (i = 0 ; i < certDetails->v3Extensions.vsCDP.distributionPointName.nRFC822NameCount; i++) {
					buff3[24] = (i + '1');
					pblock_nvinsert (buff3, certDetails->v3Extensions.vsCDP.distributionPointName.szRFC822Name[i], sn->client);
					pblock_nvinsert (buff3, certDetails->v3Extensions.vsCDP.distributionPointName.szRFC822Name[i], rq->headers);
				}
			}

			pblock_nninsert ("VSCERT_EX_CDP_DPN_DNSNAMECOUNT", certDetails->v3Extensions.vsCDP.distributionPointName.nDNSNameCount, sn->client);
			pblock_nninsert ("VSCERT_EX_CDP_DPN_DNSNAMECOUNT", certDetails->v3Extensions.vsCDP.distributionPointName.nDNSNameCount, rq->headers);
			if(certDetails->v3Extensions.vsCDP.distributionPointName.nDNSNameCount && 
				certDetails->v3Extensions.vsCDP.distributionPointName.szDNSName)
			{
				/* VSCERT_EX_CDP_DPN_DNSNAMEn */
				strcpy(buff3, "VSCERT_EX_CDP_DPN_DNSNAME");
				buff3[25] = 0; buff3[26] = 0;

				/* for each of them, create name = VSCERT_EX_CDP_DPN_DNSNAMEn, value = value */
				for (i = 0 ; i < certDetails->v3Extensions.vsCDP.distributionPointName.nDNSNameCount; i++) {
					buff3[25] = (i + '1');
					pblock_nvinsert (buff3, certDetails->v3Extensions.vsCDP.distributionPointName.szDNSName[i], sn->client);
					pblock_nvinsert (buff3, certDetails->v3Extensions.vsCDP.distributionPointName.szDNSName[i], rq->headers);
				}
			}

			pblock_nninsert ("VSCERT_EX_CDP_DPN_URICOUNT", certDetails->v3Extensions.vsCDP.distributionPointName.nUniformResourceIdentifierCount, sn->client);
			pblock_nninsert ("VSCERT_EX_CDP_DPN_URICOUNT", certDetails->v3Extensions.vsCDP.distributionPointName.nUniformResourceIdentifierCount, rq->headers);
			if(certDetails->v3Extensions.vsCDP.distributionPointName.nUniformResourceIdentifierCount && 
				certDetails->v3Extensions.vsCDP.distributionPointName.szUniformResourceIdentifier)
			{
				/* VSCERT_EX_CDP_DPN_URIn */
				strcpy(buff3, "VSCERT_EX_CDP_DPN_URI");
				buff3[21] = 0; buff3[22] = 0;

				/* for each of them, create name = VSCERT_EX_CDP_DPN_URIn, value = value */
				for (i = 0 ; i < certDetails->v3Extensions.vsCDP.distributionPointName.nUniformResourceIdentifierCount; i++) {
					buff3[21] = (i + '1');
					pblock_nvinsert (buff3, certDetails->v3Extensions.vsCDP.distributionPointName.szUniformResourceIdentifier[i], sn->client);
					pblock_nvinsert (buff3, certDetails->v3Extensions.vsCDP.distributionPointName.szUniformResourceIdentifier[i], rq->headers);
				}
			}

			pblock_nninsert ("VSCERT_EX_CDP_DPN_UPNCOUNT", certDetails->v3Extensions.vsCDP.distributionPointName.nOtherNameUPNCount, sn->client);
			pblock_nninsert ("VSCERT_EX_CDP_DPN_UPNCOUNT", certDetails->v3Extensions.vsCDP.distributionPointName.nOtherNameUPNCount, rq->headers);
			if(certDetails->v3Extensions.vsCDP.distributionPointName.nOtherNameUPNCount && 
				certDetails->v3Extensions.vsCDP.distributionPointName.szOtherNameUPN)
			{
				/* VSCERT_EX_CDP_DPN_UPNn */
				strcpy(buff3, "VSCERT_EX_CDP_DPN_UPN");
				buff3[21] = 0; buff3[22] = 0;

				/* for each of them, create name = VSCERT_EX_CDP_DPN_UPNn, value = value */
				for (i = 0 ; i < certDetails->v3Extensions.vsCDP.distributionPointName.nOtherNameUPNCount; i++) {
					buff3[21] = (i + '1');
					pblock_nvinsert (buff3, certDetails->v3Extensions.vsCDP.distributionPointName.szOtherNameUPN[i], sn->client);
					pblock_nvinsert (buff3, certDetails->v3Extensions.vsCDP.distributionPointName.szOtherNameUPN[i], rq->headers);
				}
			}

			pblock_nninsert ("VSCERT_EX_CDP_DPN_GUIDCOUNT", certDetails->v3Extensions.vsCDP.distributionPointName.nOtherNameGUIDCount, sn->client);
			pblock_nninsert ("VSCERT_EX_CDP_DPN_GUIDCOUNT", certDetails->v3Extensions.vsCDP.distributionPointName.nOtherNameGUIDCount, rq->headers);
			if(certDetails->v3Extensions.vsCDP.distributionPointName.nOtherNameGUIDCount && 
				certDetails->v3Extensions.vsCDP.distributionPointName.szOtherNameGUID)
			{
				/* VSCERT_EX_CDP_DPN_GUIDn */
				strcpy(buff3, "VSCERT_EX_CDP_DPN_GUID");
				buff3[22] = 0; buff3[23] = 0;

				/* for each of them, create name = VSCERT_EX_CDP_DPN_GUIDn, value = value */
				for (i = 0 ; i < certDetails->v3Extensions.vsCDP.distributionPointName.nOtherNameGUIDCount; i++) {
					buff3[22] = (i + '1');
					pblock_nvinsert (buff3, certDetails->v3Extensions.vsCDP.distributionPointName.szOtherNameGUID[i], sn->client);
					pblock_nvinsert (buff3, certDetails->v3Extensions.vsCDP.distributionPointName.szOtherNameGUID[i], rq->headers);
				}
			}
		}
		
		/* CDP Extension: ReasonFlags */
/*
		if(certDetails->v3Extensions.vsCDP.szReasonFlags)
		{
			pblock_nvinsert ("VSCERT_EX_CDP_REASONS", certDetails->v3Extensions.vsCDP.szReasonFlags, sn->client);
			pblock_nvinsert ("VSCERT_EX_CDP_REASONS", certDetails->v3Extensions.vsCDP.szReasonFlags, rq->headers);
		}
*/		
		/* CDP Extension: cRLIssuer */
		if(certDetails->v3Extensions.vsCDP.nCRLIssuerPresent)
		{
			pblock_nninsert ("VSCERT_EX_CDP_CRL_DIRNAMECOUNT", certDetails->v3Extensions.vsCDP.cRLIssuerName.nDirectoryNameCount, sn->client);
			pblock_nninsert ("VSCERT_EX_CDP_CRL_DIRNAMECOUNT", certDetails->v3Extensions.vsCDP.cRLIssuerName.nDirectoryNameCount, rq->headers);
			if(certDetails->v3Extensions.vsCDP.cRLIssuerName.nDirectoryNameCount && 
				certDetails->v3Extensions.vsCDP.cRLIssuerName.szDirectoryName)
			{
				/* VSCERT_EX_CDP_CRL_DIRNAMEn */
				strcpy(buff3, "VSCERT_EX_CDP_CRL_DIRNAME");
				buff3[25] = 0; buff3[26] = 0;

				/* for each of them, create name = VSCERT_EX_CDP_CRL_DIRNAMEn, value = value */
				for (i = 0 ; i < certDetails->v3Extensions.vsCDP.cRLIssuerName.nDirectoryNameCount; i++) {
					buff3[25] = (i + '1');
					pblock_nvinsert (buff3, certDetails->v3Extensions.vsCDP.cRLIssuerName.szDirectoryName[i], sn->client);
					pblock_nvinsert (buff3, certDetails->v3Extensions.vsCDP.cRLIssuerName.szDirectoryName[i], rq->headers);
				}
			}

			pblock_nninsert ("VSCERT_EX_CDP_CRL_RFC822COUNT", certDetails->v3Extensions.vsCDP.cRLIssuerName.nRFC822NameCount, sn->client);
			pblock_nninsert ("VSCERT_EX_CDP_CRL_RFC822COUNT", certDetails->v3Extensions.vsCDP.cRLIssuerName.nRFC822NameCount, rq->headers);
			if(certDetails->v3Extensions.vsCDP.cRLIssuerName.nRFC822NameCount && 
				certDetails->v3Extensions.vsCDP.cRLIssuerName.szRFC822Name)
			{
				/* VSCERT_EX_CDP_CRL_RFC822n */
				strcpy(buff3, "VSCERT_EX_CDP_CRL_RFC822");
				buff3[24] = 0; buff3[25] = 0;

				/* for each of them, create name = VSCERT_EX_CDP_CRL_RFC822n, value = value */
				for (i = 0 ; i < certDetails->v3Extensions.vsCDP.cRLIssuerName.nRFC822NameCount; i++) {
					buff3[24] = (i + '1');
					pblock_nvinsert (buff3, certDetails->v3Extensions.vsCDP.cRLIssuerName.szRFC822Name[i], sn->client);
					pblock_nvinsert (buff3, certDetails->v3Extensions.vsCDP.cRLIssuerName.szRFC822Name[i], rq->headers);
				}
			}

			pblock_nninsert ("VSCERT_EX_CDP_CRL_DNSNAMECOUNT", certDetails->v3Extensions.vsCDP.cRLIssuerName.nDNSNameCount, sn->client);
			pblock_nninsert ("VSCERT_EX_CDP_CRL_DNSNAMECOUNT", certDetails->v3Extensions.vsCDP.cRLIssuerName.nDNSNameCount, rq->headers);
			if(certDetails->v3Extensions.vsCDP.cRLIssuerName.nDNSNameCount && 
				certDetails->v3Extensions.vsCDP.cRLIssuerName.szDNSName)
			{
				/* VSCERT_EX_CDP_CRL_DNSNAMEn */
				strcpy(buff3, "VSCERT_EX_CDP_CRL_DNSNAME");
				buff3[25] = 0; buff3[26] = 0;

				/* for each of them, create name = VSCERT_EX_CDP_CRL_DNSNAMEn, value = value */
				for (i = 0 ; i < certDetails->v3Extensions.vsCDP.cRLIssuerName.nDNSNameCount; i++) {
					buff3[25] = (i + '1');
					pblock_nvinsert (buff3, certDetails->v3Extensions.vsCDP.cRLIssuerName.szDNSName[i], sn->client);
					pblock_nvinsert (buff3, certDetails->v3Extensions.vsCDP.cRLIssuerName.szDNSName[i], rq->headers);
				}

			}

			pblock_nninsert ("VSCERT_EX_CDP_CRL_URICOUNT", certDetails->v3Extensions.vsCDP.cRLIssuerName.nUniformResourceIdentifierCount, sn->client);
			pblock_nninsert ("VSCERT_EX_CDP_CRL_URICOUNT", certDetails->v3Extensions.vsCDP.cRLIssuerName.nUniformResourceIdentifierCount, rq->headers);
			if(certDetails->v3Extensions.vsCDP.cRLIssuerName.nUniformResourceIdentifierCount && 
				certDetails->v3Extensions.vsCDP.cRLIssuerName.szUniformResourceIdentifier)
			{
				/* VSCERT_EX_CDP_CRL_URIn */
				strcpy(buff3, "VSCERT_EX_CDP_CRL_URI");
				buff3[21] = 0; buff3[22] = 0;

				/* for each of them, create name = VSCERT_EX_CDP_CRL_URIn, value = value */
				for (i = 0 ; i < certDetails->v3Extensions.vsCDP.cRLIssuerName.nUniformResourceIdentifierCount; i++) {
					buff3[21] = (i + '1');
					pblock_nvinsert (buff3, certDetails->v3Extensions.vsCDP.cRLIssuerName.szUniformResourceIdentifier[i], sn->client);
					pblock_nvinsert (buff3, certDetails->v3Extensions.vsCDP.cRLIssuerName.szUniformResourceIdentifier[i], rq->headers);
				}
			}

			pblock_nninsert ("VSCERT_EX_CDP_CRL_UPNCOUNT", certDetails->v3Extensions.vsCDP.cRLIssuerName.nOtherNameUPNCount, sn->client);
			pblock_nninsert ("VSCERT_EX_CDP_CRL_UPNCOUNT", certDetails->v3Extensions.vsCDP.cRLIssuerName.nOtherNameUPNCount, rq->headers);
			if(certDetails->v3Extensions.vsCDP.cRLIssuerName.nOtherNameUPNCount && 
				certDetails->v3Extensions.vsCDP.cRLIssuerName.szOtherNameUPN)
			{
				/* VSCERT_EX_CDP_CRL_UPNn */
				strcpy(buff3, "VSCERT_EX_CDP_CRL_UPN");
				buff3[21] = 0; buff3[22] = 0;

				/* for each of them, create name = VSCERT_EX_CDP_CRL_UPNn, value = value */
				for (i = 0 ; i < certDetails->v3Extensions.vsCDP.cRLIssuerName.nOtherNameUPNCount; i++) {
					buff3[21] = (i + '1');
					pblock_nvinsert (buff3, certDetails->v3Extensions.vsCDP.cRLIssuerName.szOtherNameUPN[i], sn->client);
					pblock_nvinsert (buff3, certDetails->v3Extensions.vsCDP.cRLIssuerName.szOtherNameUPN[i], rq->headers);
				}
			}

			pblock_nninsert ("VSCERT_EX_CDP_CRL_GUIDCOUNT", certDetails->v3Extensions.vsCDP.cRLIssuerName.nOtherNameGUIDCount, sn->client);
			pblock_nninsert ("VSCERT_EX_CDP_CRL_GUIDCOUNT", certDetails->v3Extensions.vsCDP.cRLIssuerName.nOtherNameGUIDCount, rq->headers);
			if(certDetails->v3Extensions.vsCDP.cRLIssuerName.nOtherNameGUIDCount && 
				certDetails->v3Extensions.vsCDP.cRLIssuerName.szOtherNameGUID)
			{
				/* VSCERT_EX_CDP_CRL_GUIDn */
				strcpy(buff3, "VSCERT_EX_CDP_CRL_GUID");
				buff3[22] = 0; buff3[23] = 0;

				/* for each of them, create name = VSCERT_EX_CDP_CRL_GUIDn, value = value */
				for (i = 0 ; i < certDetails->v3Extensions.vsCDP.cRLIssuerName.nOtherNameGUIDCount; i++) {
					buff3[22] = (i + '1');
					pblock_nvinsert (buff3, certDetails->v3Extensions.vsCDP.cRLIssuerName.szOtherNameGUID[i], sn->client);
					pblock_nvinsert (buff3, certDetails->v3Extensions.vsCDP.cRLIssuerName.szOtherNameGUID[i], rq->headers);
				}
			}
		}


	} while (0);/* end while */



	/* clean up */
	VSVAL_FreeCertFields (cpmValSDK, certDetails);
	VSVAL_Final ( cpmValSDK );


	return REQ_PROCEED;
}
