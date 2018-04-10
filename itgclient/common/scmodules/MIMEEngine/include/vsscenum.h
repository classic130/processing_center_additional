#ifndef _VSSCENUM
#define _VSSCENUM

#include "vsscstring.h"

struct VSSCEnumMime
{
	// Content-Transfer-Encoding
	enum
	{
		eCteNull,
		eCteUnknown,
		eCte7bit,
		eCte8bit,
		eCteBinary,
		eCteQuotedPrintable,
		eCteBase64,
		eCteLast
	};

	// Content-Disposition
	enum {
		eDispTypeNull,
		eDispTypeUnknown,
		eDispTypeInline,
		eDispTypeAttachment
	};

	// Types
	enum
	{
		eTypeNull,
		eTypeUnknown,
		eTypeText,
		eTypeMultipart,
		eTypeMessage,
		eTypeApplication,
		eTypeImage,
		eTypeAudio,
		eTypeVideo,
		eTypeModel,
		eTypeLast
	};
	// SubTypes
	enum
	{
		eSubtypeNull,
		eSubtypeUnknown,
		// Text
		eSubtypePlain,           // text/plain
		eSubtypeRichtext,        // text/richtext (RFC-1341)
		eSubtypeEnriched,        // text/enriched
		eSubtypeHtml,            // text/html
		// Multipart
		eSubtypeMixed,           // multipart/mixed
		eSubtypeAlternative,     // multipart/alternative
		eSubtypeDigest,          // multipart/digest
		eSubtypeParallel,        // multipart/parallel
		// Message
		eSubtypeRfc822,          // message/rfc822
		eSubtypePartial,         // message/partial
		eSubtypeExternalBody,    // message/external-body
		// Application
		eSubtypePostscript,      // application/postscript
		eSubtypeOctetStream,     // application/octet-stream
		// Image
		eSubtypeJpeg,            // image/jpeg
		eSubtypeGif,             // image/gif
		// Audio
		eSubtypeBasic,           // audio/basic
		// Video
		eSubtypeMpeg,            // video/mpeg
		// RFC 1847
		eSubtypeSigned,          // multipart/signed
		eSubtypeEncrypted,       // multipart/encrypted
		eSubtypeRfc822Headers,   // text/rfc822-headers
		// RFC-1892
		eSubtypeReport,          // multipart/report
		// RFC-1894
		eSubtypeDeliveryStatus,  // message/delivery-status
		// RFC-2112
		eSubtypeRelated,         // multipart/related
		// RFC-1740
		eSubtypeAppledouble,     // multipart/appledouble
		eSubtypeApplefile,       // application/applefile
		// Last
		eSubtypeLast
	};

};


int VSSCSubtypeStrToEnum(const VSSCString& vsscStr);
void VSSCSubtypeEnumToStr(int nEnum, VSSCString& vsscStr);
int VSSCTypeStrToEnum(const VSSCString& vsscStr);
void VSSCTypeEnumToStr(int nEnum, VSSCString& vsscStr);

#endif // _VSSCENUM