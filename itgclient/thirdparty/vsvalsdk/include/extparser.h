#ifndef _EXTPARSER_H_
#define _EXTPARSER_H_ 



#ifdef __cplusplus
extern "C" {
  /* This allows for C++ inclusion/use of this header file */
#endif

#define MAX_SUPPORTED	10


typedef struct _ITEM_MV
{
	unsigned char *data;
	unsigned int len;

}ITEM_MV;



typedef struct _VSKeyUsage_MV
{
	int nCritical;
	char* szKeyUsage; /* Comma separted list */

} VSKeyUsage_MV;

typedef struct _VSExtendedKeyUsage_MV
{
	int nCritical;
	char *szExtendedKeyUsage; /* Comma separted list */

} VSExtendedKeyUsage_MV;


typedef struct _VSGeneralNames_MV
{
	int nRFC822NameCount;
	char **szRFC822Name;
	int nDNSNameCount;
	char **szDNSName;
	int  nUniformResourceIdentifierCount;
	char **szUniformResourceIdentifier;
	int nOtherNameUPNCount;
	char** szOtherNameUPN;
	int nOtherNameGUIDCount;
	char** szOtherNameGUID; /* hex string format (half ASCII) */
	int nDirectoryNameCount;
	char **szDirectoryName; /* ex: "O = \"VeriSign, Inc.\", C = US" */
}VSGeneralNames_MV;

typedef struct _VSSubjectAltName_MV
{
	int nCritical;
	VSGeneralNames_MV GeneralNames;

}VSSubjectAltName_MV;

typedef struct _VSDispPointName
{
	VSGeneralNames_MV GeneralNames;

}VSDispPointName;

typedef struct _VSCRLIssuerName
{
	VSGeneralNames_MV GeneralNames;

}VSCRLIssuerName;

typedef	struct _VSCRLDistributionpPoint_MV
{
	int nCritical;
	int nDPNamePresent;
	int nCRLIssuerPresent;
	VSGeneralNames_MV	distributionPointName; /* We support only fullName */
	VSGeneralNames_MV	cRLIssuerName;
	char* szReasonFlags;
}VSCRLDistributionPoint_MV;

typedef struct _VSCertV3Extensions_MV
{
	VSKeyUsage_MV					vsKeyUsage;
	VSSubjectAltName_MV				vsSubjectAltName;
	VSCRLDistributionPoint_MV		vsCDP;
	VSExtendedKeyUsage_MV			vsExtendedKeyUsage;

}VSCertV3Extensions_MV;




#ifdef __cplusplus
     }
#endif

#endif /* _EXTPARSER_H_ */
