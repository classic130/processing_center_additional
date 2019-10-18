#include "base/pblock.h"
#include "base/session.h"
#include "frame/req.h"
#include "frame/protocol.h"  /* protocol_start_response */
#include "frame/http.h"       /* log_error */
#include "frame/log.h"       /* log_error */

#include "cdr.h"

int VSSampleCDRNsapi ( pblock *pb, Session *sn, Request *rq)
{
  int i;                   /* miscellaneous counter/index */
  char *cn = NULL, *email = NULL, *ou0 = NULL, *keyusage = NULL, *eku = NULL;
	int status = 0;       /* generally usefull for checking return conditions */

#ifdef DEBUG
	log_error (LOG_WARN, "VSSampleCDRNsapi", sn, rq,
						 "hey -- that tickles");
#endif


/* find the values I want */
	cn = pblock_findval ("VSCERT_CN", sn->client);
	email = pblock_findval ("VSCERT_EMAIL", sn->client);
	ou0 = pblock_findval ("VSCERT_OU1", sn->client);
	keyusage = pblock_findval ("VSCERT_EX_KEYUSAGE", sn->client);
	eku = pblock_findval ("VSCERT_EX_EKU", sn->client);

	/* set the outbound content type */
	param_free (pblock_remove ("content-type", rq->srvhdrs));
	pblock_nvinsert ("content-type", "text/html", rq->srvhdrs);
	protocol_status (sn, rq, PROTOCOL_OK, NULL);
	protocol_start_response (sn, rq);
#define TITLE "<TITLE>This is a rather simple example of using \
libcdrNSAPI.so</TITLE>"
#define PRECN "The cn was "
#define POSTANY ":.<BR>"
#define PREEMAIL "Email was :"
#define PREOU0 "ou1 was :"
#define PREKEYUSAGE "key usage was :"
#define PRE_EKU	"EKU was :"
#define CYA "Sample this."
	net_write (sn->csd, TITLE, strlen(TITLE));
	if (cn) {
		net_write (sn->csd, PRECN, strlen(PRECN));
		net_write (sn->csd, cn, strlen(cn));
		net_write (sn->csd, POSTANY, strlen (POSTANY));
	}
	if (email) {
		net_write (sn->csd, PREEMAIL, strlen(PREEMAIL));
		net_write (sn->csd, email, strlen(email));
		net_write (sn->csd, POSTANY, strlen (POSTANY));
	}
	if (ou0) {
		net_write (sn->csd, PREOU0, strlen(PREOU0));
		net_write (sn->csd, ou0, strlen(ou0));
		net_write (sn->csd, POSTANY, strlen (POSTANY));
	}
	if (keyusage) {
		net_write (sn->csd, PREKEYUSAGE, strlen(PREKEYUSAGE));
		net_write (sn->csd, keyusage, strlen(keyusage));
		net_write (sn->csd, POSTANY, strlen (POSTANY));
	}
	if (eku) {
		net_write (sn->csd, PRE_EKU, strlen(PRE_EKU));
		net_write (sn->csd, eku, strlen(eku));
		net_write (sn->csd, POSTANY, strlen (POSTANY));
	}

	net_write (sn->csd, CYA, strlen(CYA));

#ifdef DEBUG
	log_error (LOG_WARN, "VSSampleCDRNsapi", sn, rq,
						 "cn:%s:email:%s:", cn, email);
#endif

	FREE (cn);
	FREE (email);
	FREE (ou0);
	FREE (keyusage);
	FREE (eku);
}

