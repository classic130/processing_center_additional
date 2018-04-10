//+---------------------------------------------------------------------------
//
//  Microsoft Windows
//  Copyright (C) Microsoft Corporation, 1992-1997.
//
//  File:       CertSrv.h
//  Contents:   Main Certificate Server header
//              Also includes .h files for the COM interfaces
//
//----------------------------------------------------------------------------

#if !defined( _CERTSRV_H_ )
#define _CERTSRV_H_

#include <certadm.h>
#include <certcli.h>
#include <certdb.h>
#include <certenc.h>
#include <certexit.h>
#include <certif.h>
#include <certpol.h>
#include <certview.h>

#ifndef DBG_CERTSRV
# if defined(_DEBUG)
#  define DBG_CERTSRV     1
# elif defined(DBG)
#  define DBG_CERTSRV     DBG
# else
#  define DBG_CERTSRV     0
# endif
#endif

#define wszSERVICE_NAME		TEXT("CertSvc")

#define wszREGKEYBASE		TEXT("SYSTEM\\CurrentControlSet\\Services\\") \
				wszSERVICE_NAME

//======================================================================
// Full path to "CertSvc\Configuration\":
#define wszREGKEYCONFIGCANAME	wszREGKEYBASE TEXT("\\") \
				wszREGKEYCONFIG TEXT("\\")

//======================================================================
// Key Under "CertSvc":
#define wszREGKEYCONFIG		TEXT("Configuration")

//======================================================================
// Values Under "CertSvc\Configuration":
#define wszREGDIRECTORY		TEXT("ConfigurationDirectory")
#define wszREGACTIVE		TEXT("Active")
#define wszREGRESTORE		TEXT("Restore")

//======================================================================
// Keys Under "CertSvc\Configuration":
#define wszREGKEYEXITMODULES	TEXT("ExitModules")
#define wszREGKEYPOLICYMODULES	TEXT("PolicyModules")

//======================================================================
// Values Under "CertSvc\Configuration\{UUID}":
#define wszREGMANAGECSMODULE    TEXT("ICertManageModule")
#define wszREGCSMODULENAME      TEXT("Name")

//======================================================================
// Values Under "CertSvc\Configuration\<CAName>":
#define wszREGCASERIALNUMBER	   TEXT("CACertSerialNumber")
#define wszREGCATYPE		   TEXT("CAType")
#define wszREGCERTENROLLCOMPATIBLE TEXT("CertEnrollCompatible")
#define wszREGCOMMONNAME	   TEXT("CommonName")
#define wszREGCLOCKSKEWMINUTES	   TEXT("ClockSkewMinutes")
#define wszREGCRLLASTISSUED	   TEXT("CRLLastIssued")
#define wszREGCRLPERIOD		   TEXT("CRLPeriod")
#define wszREGCRLUNITS		   TEXT("CRLPeriodUnits")
#define wszREGENABLED		   TEXT("Enabled")
#define wszREGFORCETELETEX         TEXT("ForceTeletex")
#define wszREGLOGLEVEL	   	   TEXT("LogLevel")
#define wszREGPOLICYFLAGS	   TEXT("PolicyFlags")
#define wszREGNAMESEPARATOR        TEXT("SubjectNameSeparator")
#define wszREGSUBJECTTEMPLATE	   TEXT("SubjectTemplate")
#define wszREGCAUSEDS		   TEXT("UseDS")
#define wszREGDURATIONPERIOD	   TEXT("ValidityPeriod")
#define wszREGDURATIONUNITS	   TEXT("ValidityPeriodUnits")

#define wszREGDBDIRECTORY          TEXT("DBDirectory")
#define wszREGDBLOGDIRECTORY       TEXT("DBLogDirectory")
#define wszREGDBSYSDIRECTORY       TEXT("DBSystemDirectory")
#define wszREGDBTEMPDIRECTORY      TEXT("DBTempDirectory")
#define wszREGDBRESTOREDIRECTORY   TEXT("DBRestoreDirectory")
#define wszREGINSTALLER            TEXT("Installer")
#define wszREGSETUPSTATUS          TEXT("SetupStatus")

#define wszDBFILENAME		   TEXT("certsrv.edb")
#define wszLOGPATH		   TEXT("CertLog")

#define CERTLOG_MINIMAL		(DWORD) 0
#define CERTLOG_TERSE		(DWORD) 1
#define CERTLOG_ERROR		(DWORD) 2
#define CERTLOG_VERBOSE		(DWORD) 3


//======================================================================
// Keys Under "CertSvc\Configuration\<CAName>":
#define wszREGKEYCSP			TEXT("CSP")
//#define wszREGKEYEXITMODULES		TEXT("ExitModules")
//#define wszREGKEYPOLICYMODULES	TEXT("PolicyModules")

//======================================================================
// Values Under "CertSvc\Configuration\<CAName>\CSP":
#define wszREGPROVIDERTYPE    TEXT("ProviderType")
#define wszREGPROVIDER        TEXT("Provider")
#define wszHASHALGORITHM      TEXT("HashAlgorithm")
#define wszMACHINEKEYSET      TEXT("MachineKeyset")


//======================================================================
// Value strings for "CertSvc\Configuration\<CAName>\SubjectNameSeparator":
#define szNAMESEPARATORDEFAULT   "\n"
#define wszNAMESEPARATORDEFAULT   TEXT(szNAMESEPARATORDEFAULT)


//======================================================================
// Value strings for "CertSvc\Configuration\<CAName>\RevocationType":
#define wszREVTYPE_CRL		TEXT("CRL")
#define wszREVTYPE_NETSCAPE	TEXT("Netscape")


//======================================================================
// Value strings for "CertSvc\Configuration\<CAName>\ValidityPeriod":
#define wszDURATIONUNITSYEARS	TEXT("Years")
#define wszDURATIONUNITSMONTHS	TEXT("Months")
#define wszDURATIONUNITSWEEKS	TEXT("Weeks")
#define wszDURATIONUNITSDAYS	TEXT("Days")
#define wszDURATIONUNITSHOURS	TEXT("Hours")
#define wszDURATIONUNITSMINUTES	TEXT("Minutes")
#define wszDURATIONUNITSSECONDS	TEXT("Seconds")

//======================================================================
// Values Under "CertSvc\Configuration\<CAName>\PolicyModules\<{CLSID}>":
#define wszREGSUBJECTALTNAME	   TEXT("SubjectAltName")
#define wszREGSUBJECTALTNAME2	   TEXT("SubjectAltName2")
#define wszREGREVOCATIONCRLURL	   TEXT("RevocationCRLURL")
#define wszREGREVOCATIONTYPE	   TEXT("RevocationType")
#define wszREGREVOCATIONURL	   TEXT("RevocationURL")
#define wszREGISSUERCERTURL        TEXT("IssuerCertURL")
#define wszREGNETSCAPECERTTYPE     TEXT("NetscapeCertType")



#define wszCLASS_CERTADMIN	  TEXT("CertificateAuthority.Admin")
#define wszCLASS_CERTCONFIG	  TEXT("CertificateAuthority.Config")
#define wszCLASS_CERTGETCONFIG	  TEXT("CertificateAuthority.GetConfig")
#define wszCLASS_CERTENCODE	  TEXT("CertificateAuthority.Encode")
#define wszCLASS_CERTEXIT	  TEXT("CertificateAuthority.Exit")
#define wszCLASS_CERTPOLICY	  TEXT("CertificateAuthority.Policy")
#define wszCLASS_CERTREQUEST	  TEXT("CertificateAuthority.Request")
#define wszCLASS_CERTSERVEREXIT	  TEXT("CertificateAuthority.ServerExit")
#define wszCLASS_CERTSERVERPOLICY TEXT("CertificateAuthority.ServerPolicy")
#define wszCLASS_CERTVIEW	  TEXT("CertificateAuthority.View")
#define wszCLASS_CERTMANAGEEXITMODULE TEXT("CertificateAuthority.ManageExitModule")
#define wszCLASS_CERTMANAGEPOLICYMODULE TEXT("CertificateAuthority.ManagePolicyModule")


//+--------------------------------------------------------------------------
// Name properties:

#define wszPROPDISTINGUISHEDNAME TEXT("DistinguishedName")
#define wszPROPRAWNAME           TEXT("RawName")
#define wszPROPNAMETYPE          TEXT("NameType")
#define wszPROPCOUNTRY           TEXT("Country")
#define wszPROPORGANIZATION      TEXT("Organization")
#define wszPROPORGUNIT           TEXT("OrgUnit")
#define wszPROPCOMMONNAME        TEXT("CommonName")
#define wszPROPLOCALITY          TEXT("Locality")
#define wszPROPSTATE             TEXT("State")
#define wszPROPTITLE             TEXT("Title")
#define wszPROPGIVENNAME         TEXT("GivenName")
#define wszPROPINITIALS          TEXT("Initials")
#define wszPROPSURNAME           TEXT("SurName")
#define wszPROPDOMAINCOMPONENT   TEXT("DomainComponent")
#define wszPROPEMAIL             TEXT("EMail")
#define wszPROPSTREETADDRESS     TEXT("StreetAddress")

//+--------------------------------------------------------------------------
// Subject Name properties:

#define wszPROPSUBJECTDOT	    TEXT("Subject.")
#define wszPROPSUBJECTDISTINGUISHEDNAME \
				    wszPROPSUBJECTDOT wszPROPDISTINGUISHEDNAME
#define wszPROPSUBJECTRAWNAME       wszPROPSUBJECTDOT wszPROPRAWNAME
#define wszPROPSUBJECTNAMETYPE      wszPROPSUBJECTDOT wszPROPNAMETYPE

#define wszPROPSUBJECTCOUNTRY       wszPROPSUBJECTDOT wszPROPCOUNTRY
#define wszPROPSUBJECTORGANIZATION  wszPROPSUBJECTDOT wszPROPORGANIZATION
#define wszPROPSUBJECTORGUNIT       wszPROPSUBJECTDOT wszPROPORGUNIT
#define wszPROPSUBJECTCOMMONNAME    wszPROPSUBJECTDOT wszPROPCOMMONNAME
#define wszPROPSUBJECTLOCALITY      wszPROPSUBJECTDOT wszPROPLOCALITY
#define wszPROPSUBJECTSTATE         wszPROPSUBJECTDOT wszPROPSTATE
#define wszPROPSUBJECTTITLE	    wszPROPSUBJECTDOT wszPROPTITLE
#define wszPROPSUBJECTGIVENNAME	    wszPROPSUBJECTDOT wszPROPGIVENNAME
#define wszPROPSUBJECTINITIALS	    wszPROPSUBJECTDOT wszPROPINITIALS
#define wszPROPSUBJECTSURNAME	    wszPROPSUBJECTDOT wszPROPSURNAME
#define wszPROPSUBJECTDOMAINCOMPONENT wszPROPSUBJECTDOT wszPROPDOMAINCOMPONENT
#define wszPROPSUBJECTEMAIL	    wszPROPSUBJECTDOT wszPROPEMAIL
#define wszPROPSUBJECTSTREETADDRESS wszPROPSUBJECTDOT wszPROPSTREETADDRESS

#define wszPROPSUBJECTCOUNTRYOBJID \
    wszPROPSUBJECTDOT TEXT(szOID_COUNTRY_NAME)

#define wszPROPSUBJECTORGANIZATIONOBJID \
    wszPROPSUBJECTDOT TEXT(szOID_ORGANIZATION_NAME)

#define wszPROPSUBJECTORGUNITOBJID \
    wszPROPSUBJECTDOT TEXT(szOID_ORGANIZATIONAL_UNIT_NAME)

#define wszPROPSUBJECTCOMMONNAMEOBJID \
    wszPROPSUBJECTDOT TEXT(szOID_COMMON_NAME)

#define wszPROPSUBJECTLOCALITYOBJID \
    wszPROPSUBJECTDOT TEXT(szOID_LOCALITY_NAME)

#define wszPROPSUBJECTSTATEOBJID \
    wszPROPSUBJECTDOT TEXT(szOID_STATE_OR_PROVINCE_NAME)

#define wszPROPSUBJECTTITLEOBJID \
    wszPROPSUBJECTDOT TEXT(szOID_TITLE)

#define wszPROPSUBJECTGIVENNAMEOBJID \
    wszPROPSUBJECTDOT TEXT(szOID_GIVEN_NAME)

#define wszPROPSUBJECTINITIALSOBJID \
    wszPROPSUBJECTDOT TEXT(szOID_INITIALS)

#define wszPROPSUBJECTSURNAMEOBJID \
    wszPROPSUBJECTDOT TEXT(szOID_SUR_NAME)

#define wszPROPSUBJECTDOMAINCOMPONENTOBJID \
    wszPROPSUBJECTDOT TEXT(szOID_DOMAIN_COMPONENT)

#define wszPROPSUBJECTEMAILOBJID \
    wszPROPSUBJECTDOT TEXT(szOID_RSA_emailAddr)

#define wszPROPSUBJECTSTREETADDRESSOBJID \
    wszPROPSUBJECTDOT TEXT(szOID_STREET_ADDRESS)



//+--------------------------------------------------------------------------
// Request properties:
#define wszPROPREQUESTDOT	            TEXT("Request.")

#define wszPROPREQUESTREQUESTID		    TEXT("RequestID")
#define wszPROPREQUESTRAWREQUEST	    TEXT("RawRequest")
#define wszPROPREQUESTRAWOLDCERTIFICATE	    TEXT("RawOldCertificate")
#define wszPROPREQUESTATTRIBUTES	    TEXT("RequestAttributes")
#define wszPROPREQUESTTYPE		    TEXT("RequestType")
#define wszPROPREQUESTFLAGS		    TEXT("RequestFlags")
#define wszPROPREQUESTSTATUSCODE	    TEXT("StatusCode")
#define wszPROPREQUESTDISPOSITION	    TEXT("Disposition")
#define wszPROPREQUESTDISPOSITIONMESSAGE    TEXT("DispositionMessage")
#define wszPROPREQUESTSUBMITTEDWHEN	    TEXT("SubmittedWhen")
#define wszPROPREQUESTRESOLVEDWHEN	    TEXT("ResolvedWhen")
#define wszPROPREQUESTREVOKEDWHEN	    TEXT("RevokedWhen")
#define wszPROPREQUESTREVOKEDEFFECTIVEWHEN  TEXT("RevokedEffectiveWhen")
#define wszPROPREQUESTREVOKEDREASON	    TEXT("RevokedReason")
#define wszPROPREQUESTERNAME		    TEXT("RequesterName")
#define wszPROPREQUESTERTOKEN		    TEXT("RequesterToken")

//+--------------------------------------------------------------------------
// Request attribute properties:

#define wszPROPCHALLENGE		TEXT("Challenge")
#define wszPROPEXPECTEDCHALLENGE	TEXT("ExpectedChallenge")

#define wszPROPDISPOSITION		TEXT("Disposition")
#define wszPROPDISPOSITIONDENY		TEXT("Deny")
#define wszPROPDISPOSITIONPENDING	TEXT("Pending")

#define wszPROPVALIDITYPERIOD		TEXT("ValidityPeriod")
#define wszPROPVALIDITYPERIODUNITS	TEXT("ValidityPeriodUnits")


//+--------------------------------------------------------------------------
// Certificate properties:

#define wszPROPCERTIFICATEREQUESTID	    TEXT("RequestID")
#define wszPROPRAWCERTIFICATE		    TEXT("RawCertificate")
#define wszPROPCERTIFICATEHASH		    TEXT("CertificateHash")
#define wszPROPCERTIFICATETYPE		    TEXT("CertificateType")
#define wszPROPCERTIFICATESERIALNUMBER	    TEXT("SerialNumber")
#define wszPROPCERTIFICATENOTBEFOREDATE	    TEXT("NotBefore")
#define wszPROPCERTIFICATENOTAFTERDATE	    TEXT("NotAfter")
#define wszPROPCERTIFICATERAWPUBLICKEY	    TEXT("RawPublicKey")
#define wszPROPCERTIFICATEPUBLICKEYALGORITHM TEXT("PublicKeyAlgorithm")
#define wszPROPCERTIFICATERAWPUBLICKEYALGORITHMPARAMETERS \
    TEXT("RawPublicKeyAlgorithmParameters")

//+--------------------------------------------------------------------------
// Certificate extension properties:

#define EXTENSION_CRITICAL_FLAG	     0x00000001
#define EXTENSION_DISABLE_FLAG	     0x00000002
#define EXTENSION_POLICY_MASK	     0x0000ffff	// Settable by admin+policy

#define EXTENSION_ORIGIN_REQUEST     0x00010000
#define EXTENSION_ORIGIN_POLICY	     0x00020000
#define EXTENSION_ORIGIN_ADMIN	     0x00030000
#define EXTENSION_ORIGIN_SERVER	     0x00040000
#define EXTENSION_ORIGIN_RENEWALCERT 0x00050000
#define EXTENSION_ORIGIN_MASK	     0x000f0000

//+--------------------------------------------------------------------------
// GetProperty/SetProperty Flags:
//
// Choose one Type

#define PROPTYPE_LONG		 0x00000001	// Signed long
#define PROPTYPE_DATE		 0x00000002	// Date+Time
#define PROPTYPE_BINARY		 0x00000003	// Binary data
#define PROPTYPE_STRING		 0x00000004	// Unicode String
#define PROPTYPE_MASK		 0x000000ff

// Choose one Caller:

#define PROPCALLER_SERVER	 0x00000100
#define PROPCALLER_POLICY	 0x00000200
#define PROPCALLER_EXIT		 0x00000300
#define PROPCALLER_ADMIN	 0x00000400
#define PROPCALLER_REQUEST	 0x00000500
#define PROPCALLER_MASK		 0x00000f00

// RequestFlags definitions:

#define CR_FLG_FORCETELETEX	0x00000001
#define CR_FLG_RENEWAL		0x00000002

// Disposition property values:

// Disposition values for requests in the queue:
#define DB_DISP_ACTIVE	        8	// being processed
#define DB_DISP_PENDING		9	// taken under submission
#define DB_DISP_QUEUE_MAX	9	// max disposition value for queue view

// Disposition values for requests in the log:
#define DB_DISP_LOG_MIN		20	// min disposition value for log view
#define DB_DISP_ISSUED		20	// cert issued
#define DB_DISP_REVOKED	        21	// issued and revoked

// Disposition values for failed requests in the log:
#define DB_DISP_LOG_FAILED_MIN	30	// min disposition value for log view
#define DB_DISP_ERROR		30	// request failed
#define DB_DISP_DENIED		31	// request denied


// VerifyRequest() return values

#define VR_PENDING	0	 // request will be accepted or denied later
#define VR_INSTANT_OK	1	 // request was accepted
#define VR_INSTANT_BAD	2	 // request was rejected


//+--------------------------------------------------------------------------
// Known request Attribute names and Value strings

// RequestType attribute name:
#define wszCERT_TYPE		L"RequestType"	// attribute name

// RequestType attribute values:
// Not specified: 				// Non-specific certificate
#define wszCERT_TYPE_CLIENT	L"Client"	// Client authentication cert
#define wszCERT_TYPE_SERVER	L"Server"	// Server authentication cert
#define wszCERT_TYPE_CODESIGN	L"CodeSign"	// Code signing certificate
#define wszCERT_TYPE_CUSTOMER	L"SetCustomer"	// SET Customer certificate
#define wszCERT_TYPE_MERCHANT	L"SetMerchant"	// SET Merchant certificate
#define wszCERT_TYPE_PAYMENT	L"SetPayment"	// SET Payment certificate


// Version attribute name:
#define wszCERT_VERSION		L"Version"	// attribute name

// Version attribute values:
// Not specified: 				// Whetever is current
#define wszCERT_VERSION_1	L"1"		// Version one certificate
#define wszCERT_VERSION_2	L"2"		// Version two certificate
#define wszCERT_VERSION_3	L"3"		// Version three certificate

#endif // _CERTSRV_H_
