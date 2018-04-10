#include "vssc_util.h"

#define EMAILRES_CONFIGFILE	"EmailRes.config"


typedef struct
{
	VS_PROTOCOL	eProtocol;
	char		*szServerName;
	char		*szEmailBaseDn;
	char		*szEmailAttribute;
}EMAILDIRINFO;

void InitiliazeEmailConfigInfo(char *szName,
					  char *szValue);

bool EmailResolutionInit();

unsigned long EmailResolution(char *szSearchName,
							 char **szEmailAddress);

/*
unsigned long MyCertResolution(char *szEmailAddress,
							  char **szMyUserCertificate);

unsigned long UserCertResolution(char *szEmailAddress,
							  char **szUserCertificate);
*/


