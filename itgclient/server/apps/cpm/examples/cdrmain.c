#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include "cdr.h"
/* To use the embedded cert below #define TEST 1 */
/* To use a cert from cgi, do not #define TEST */
#define TEST
#ifdef TEST
static char certB64_1[] = "\
MIIJTDCCCPagAwIBAgIQNgizAL1+67QS1iiVShEemTANBgkqhkiG9w0BAQQFADBi\n\
MREwDwYDVQQHEwhJbnRlcm5ldDEXMBUGA1UEChMOVmVyaVNpZ24sIEluYy4xNDAy\n\
BgNVBAsTK1ZlcmlTaWduIENsYXNzIDEgQ0EgLSBJbmRpdmlkdWFsIFN1YnNjcmli\n\
ZXIwHhcNOTYwODI4MDAwMDAwWhcNOTYwODMxMjM1OTU5WjCCAZcxETAPBgNVBAcT\n\
CEludGVybmV0MRcwFQYDVQQKEw5WZXJpU2lnbiwgSW5jLjE0MDIGA1UECxMrVmVy\n\
aVNpZ24gQ2xhc3MgMSBDQSAtIEluZGl2aWR1YWwgU3Vic2NyaWJlcjFHMEUGA1UE\n\
CxM+d3d3LnZlcmlzaWduLmNvbS9yZXBvc2l0b3J5L0NQUy0xLjAgSW5jLiBieSBS\n\
ZWYuLExJQUIuTFREKGMpOTYxKzApBgNVBAsTIkRpZ2l0YWwgSUQgQ2xhc3MgMSAt\n\
IE5ldHNjYXBlIEJldGExGDAWBgNVBAMTD05lb3BoeXRlIFN1cmZlcjEfMB0GCSqG\n\
SIb3DQEJARYQcmFtQHZlcmlzaWduLmNvbTGBgTB/BgkqhkiG9w0BCQITcmQ0NjUy\n\
YmQ2M2YyMDQ3MDI5Mjk4NzYzYzlkMmYyNzUwNjljNzM1OWJlZDFiMDU5ZGE3NWJj\n\
NGJjOTcwMTc0N2NhNWQzZjIxNDFiZWFkYjJiZDJlODkyMWZhOTZiZjVkNzExNDk5\n\
Y2ExYjk0YmZkZjNlYTBcMA0GCSqGSIb3DQEBAQUAA0sAMEgCQQDipF9VTI/sT7Ur\n\
cze27qDyDgpE2ZQHZzWoFyWaDFUfnZVwqtBZ0mcx7sDRKp11qkEDq1mk25rh8xmt\n\
9cpEY5yPAgMBAAGjggZPMIIGSzAJBgNVHRMEAjAAMIICJgYDVR0DBIICHTCCAhkw\n\
ggIVMIICEQYLYIZIAYb4RQEHAQEwggIAFoIBq1RoaXMgY2VydGlmaWNhdGUgaW5j\n\
b3Jwb3JhdGVzIGJ5IHJlZmVyZW5jZSwgYW5kIGl0cyB1c2UgaXMgc3RyaWN0bHkg\n\
c3ViamVjdCB0bywgdGhlIFZlcmlTaWduIENlcnRpZmljYXRpb24gUHJhY3RpY2Ug\n\
U3RhdGVtZW50IChDUFMpLCBhdmFpbGFibGUgYXQ6IGh0dHBzOi8vd3d3LnZlcmlz\n\
aWduLmNvbS9DUFMtMS4wOyBieSBFLW1haWwgYXQgQ1BTLXJlcXVlc3RzQHZlcmlz\n\
aWduLmNvbTsgb3IgYnkgbWFpbCBhdCBWZXJpU2lnbiwgSW5jLiwgMjU5MyBDb2Fz\n\
dCBBdmUuLCBNb3VudGFpbiBWaWV3LCBDQSA5NDA0MyBVU0EgVGVsLiArMSAoNDE1\n\
KSA5NjEtODgzMCBDb3B5cmlnaHQgKGMpIDE5OTYgVmVyaVNpZ24sIEluYy4gIEFs\n\
bCBSaWdodHMgUmVzZXJ2ZWQuIENFUlRBSU4gV0FSUkFOVElFUyBESVNDTEFJTUVE\n\
IGFuZCBMSUFCSUxJVFkgTElNSVRFRC6gDgYMYIZIAYb4RQEHAQEBoQ4GDGCGSAGG\n\
+EUBBwEBAjAvMC0WK2h0dHBzOi8vd3d3LnZlcmlzaWduLmNvbS9yZXBvc2l0b3J5\n\
L0NQUy0xLgMwEQYJYIZIAYb4QgEBBAQDAgeAMDYGCWCGSAGG+EIBCAQpFidodHRw\n\
czovL3d3dy52ZXJpc2lnbi5jb20vcmVwb3NpdG9yeS9DUFMwggPHBglghkgBhvhC\n\
AQ0EggO4FoIDtFRoaXMgY2VydGlmaWNhdGUgaW5jb3Jwb3JhdGVzIGJ5IHJlZmVy\n\
ZW5jZSwgYW5kIGl0cyB1c2UgaXMgc3RyaWN0bHkKc3ViamVjdCB0bywgdGhlIFZl\n\
cmlTaWduIENlcnRpZmljYXRpb24gUHJhY3RpY2UgU3RhdGVtZW50IChDUFMpCnZl\n";

static char certB64_2[] = "\
cnNpb24gMS4wLCBhdmFpbGFibGUgaW4gdGhlIFZlcmlTaWduIHJlcG9zaXRvcnkg\n\
YXQ6Cmh0dHBzOi8vd3d3LnZlcmlzaWduLmNvbTsgYnkgRS1tYWlsIGF0IENQUy1y\n\
ZXF1ZXN0c0B2ZXJpc2lnbi5jb207IG9yCmJ5IG1haWwgYXQgVmVyaVNpZ24sIElu\n\
Yy4sIDI1OTMgQ29hc3QgQXZlLiwgTW91bnRhaW4gVmlldywgQ0EgOTQwNDMKVVNB\n\
IENvcHlyaWdodCAoYykxOTk2IFZlcmlTaWduLCBJbmMuICBBbGwgUmlnaHRzIFJl\n\
c2VydmVkLiBDRVJUQUlOCldBUlJBTlRJRVMgRElTQ0xBSU1FRCBBTkQgTElBQklM\n\
SVRZIExJTUlURUQuCgpXQVJOSU5HOiBUSEUgVVNFIE9GIFRISVMgQ0VSVElGSUNB\n\
VEUgSVMgU1RSSUNUTFkgU1VCSkVDVCBUTyBUSEUKVkVSSVNJR04gQ0VSVElGSUNB\n\
VElPTiBQUkFDVElDRSBTVEFURU1FTlQuICBUSEUgSVNTVUlORyBBVVRIT1JJVFkK\n\
RElTQ0xBSU1TIENFUlRBSU4gSU1QTElFRCBBTkQgRVhQUkVTUyBXQVJSQU5USUVT\n\
LCBJTkNMVURJTkcgV0FSUkFOVElFUwpPRiBNRVJDSEFOVEFCSUxJVFkgT1IgRklU\n\
TkVTUyBGT1IgQSBQQVJUSUNVTEFSIFBVUlBPU0UsIEFORCBXSUxMIE5PVApCRSBM\n\
SUFCTEUgRk9SIENPTlNFUVVFTlRJQUwsIFBVTklUSVZFLCBBTkQgQ0VSVEFJTiBP\n\
VEhFUiBEQU1BR0VTLiBTRUUKVEhFIENQUyBGT1IgREVUQUlMUy4KCkNvbnRlbnRz\n\
IG9mIHRoZSBWZXJpU2lnbiByZWdpc3RlcmVkIG5vbnZlcmlmaWVkU3ViamVjdEF0\n\
dHJpYnV0ZXMKZXh0ZW5zaW9uIHZhbHVlIHNoYWxsIG5vdCBiZSBjb25zaWRlcmVk\n\
IGFzIGFjY3VyYXRlIGluZm9ybWF0aW9uCnZhbGlkYXRlZCBieSB0aGUgSUEuCjAN\n\
BgkqhkiG9w0BAQQFAANBADeLA2cj9p8L3RpaKl2L50JYF/jvVF4sa06AMJZqJLyi\n\
JFGJNFnXKMCELjj5pLeUTCK5h9mcZTkCqd+Z0PVhQYA=\n\
";
#endif

int main (int argc, char *argv[], char *envp[])
{
  char *certB64 = (char *)0;
  char *emailAddress, *commonName, *uniqueID, *address;
  char **organizationUnits, *title, *notBefore, *notAfter;
  int status = 0, organizationUnitCount = 0, loop = 0;
  size_t length = 0;
  FILE *fH = NULL;
  char *issuerOrganization, *issuerLocality,  *issuerCountry, *issuerCommonName;
  char **issuerOrganizationUnits;
  int issuerOrganizationUnitCount = 0;

  /* this structure contains the V3 extensions, defined in extparser.h */
  VSCertV3Extensions_MV v3Extensions; 

  issuerOrganization = issuerLocality = issuerCountry = issuerCommonName = (char *)0; 
  issuerOrganizationUnits = (char **)0;


  emailAddress = commonName = uniqueID = address  = (char *)0;
  title = notBefore = notAfter = (char *)0;
		organizationUnits = (char **)0;

  printf ("Content-Type:  text/html\n\n\n");
#ifndef TEST
  certB64 = getenv ("CLIENT_CERT");
  if (!certB64) {
    printf ("Sample ERROR: <BR>\n client certificate not found in ");
    printf ("CLIENT_CERT environment variable. <BR>\nCheck to see if ");
    printf ("server configured correctly.<BR>\n");
    return -1;
  }

#else
  if (argc == 1) {
    certB64 = (char *)malloc (strlen(certB64_1) + strlen(certB64_2) + 1);
    if (certB64) {
      strcpy (certB64, certB64_1);
      strcat (certB64, certB64_2);
    }
    else 
      {
        return (-1); /* couldn't alloc memory */
      }
  }
  else  /* take it from a file */
    {
      if (argc != 2)
        return (-1);
      if (!(fH = fopen (argv[1], "r")))
        return -1;
      if (!(certB64 = (char *)malloc (4096)))
        return -1;
      length = fread (certB64, 1, 4096, fH);
      certB64[length] = 0;
    }
#endif

  do {
    if (status = GetAllFieldsAlloc 
        (&emailAddress, 0, &uniqueID, &address, 
         &organizationUnits, &organizationUnitCount, certB64))
      break;
		if (status = VSGetAllFieldsAlloc (0, 0, &title, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                          &notBefore, &notAfter, 0, certB64))
			break;
    if (status = GetCommonNameStringAlloc (&commonName, certB64))
      break;

    if (status = VSGetAllFieldsAlloc (0, 0, 0, 0, 0, 0, 0, 0, 
                                      &issuerOrganization,
                                      &issuerLocality, &issuerCountry, &issuerCommonName,
                                      &issuerOrganizationUnits,
                                      &issuerOrganizationUnitCount,
                                      0, 0, &v3Extensions, certB64))
      break;


    if (issuerLocality)
      printf("Issuer Locality:%s:<BR>\n", issuerLocality);

    if (issuerCountry)
      printf("Issuer Country:%s:<BR>\n", issuerCountry);

    if (issuerCommonName)
      printf("Issuer Common Name:%s:<BR>\n", issuerCommonName);

    if (issuerOrganization)
      printf("Issuer Organization:%s:<BR>\n", issuerOrganization);

    if (issuerOrganizationUnitCount) {
      printf ("Issuer Organization unit(s)<BR>\n");
      for (loop = issuerOrganizationUnitCount ; loop > 0; loop--)
        printf (":%s:<BR>\n", issuerOrganizationUnits[loop - 1]);
    }


    if (emailAddress)
      printf("email:%s:<BR>\n", emailAddress);
		if (title)
			printf ("title :%s:<BR>\n", title);
		if (notBefore)
			printf ("not before :%s:<BR>\n", notBefore);
		if (notAfter)
			printf ("not after :%s:<BR>\n", notAfter);
    if (commonName)
      printf ("common name :%s:<BR>\n", commonName);
    if (uniqueID)
      printf ("unique ID :%s:<BR>\n", uniqueID);
    if (organizationUnitCount) {
      printf ("organization unit(s)<BR>\n");
      for (loop = organizationUnitCount ; loop > 0; loop--)
        printf (":%s:<BR>\n", organizationUnits[loop - 1]);
    }
    if (address)
      printf ("address :%s:<BR>\n", address);
	if (v3Extensions.vsKeyUsage.szKeyUsage)
		printf ("key usage:%s:<BR>\n", v3Extensions.vsKeyUsage.szKeyUsage);

	if (v3Extensions.vsExtendedKeyUsage.szExtendedKeyUsage)
		printf("EKU:%s:<BR>\n", v3Extensions.vsExtendedKeyUsage.szExtendedKeyUsage);

	if (v3Extensions.vsCDP.distributionPointName.nUniformResourceIdentifierCount) {
		printf ("CDP URI(s)<BR>\n");
		for (loop = v3Extensions.vsCDP.distributionPointName.nUniformResourceIdentifierCount; loop > 0; loop--)
			printf (":%s:<BR>\n", v3Extensions.vsCDP.distributionPointName.szUniformResourceIdentifier[loop - 1]);
	}

  } while (0);
  CDR_Free (uniqueID);
  CDR_Free (title);
  CDR_Free (notBefore);
  CDR_Free (notAfter);
  CDR_Free (emailAddress);
  CDR_Free (commonName);
  CDR_Free (address);
  if (organizationUnitCount) {
    for (loop = organizationUnitCount ; loop > 0; loop --)
      CDR_Free (organizationUnits[loop - 1]);
    CDR_Free ((char *)organizationUnits);
  }

  CDR_Free(issuerOrganization);
  CDR_Free(issuerLocality);
  CDR_Free(issuerCountry);
  CDR_Free(issuerCommonName);
  if (issuerOrganizationUnits) {
    for (loop = issuerOrganizationUnitCount; loop > 0; loop--) {
      CDR_Free (issuerOrganizationUnits[loop-1]);
      issuerOrganizationUnits[loop-1] = 0;
    }
    CDR_Free ((char *)issuerOrganizationUnits);
    issuerOrganizationUnits = 0;
  }

#ifdef TEST
  free (certB64);
#endif
  if (status)
    printf ("status:  %d\n", status);
  return status;
}
