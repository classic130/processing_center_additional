#include "vsscenum.h"

int VSSCSubtypeStrToEnum(const VSSCString& vsscStr)
{
    if (vsscStr == "")
	{
        return VSSCEnumMime::eSubtypeNull;
    }

    int type = VSSCEnumMime::eSubtypeUnknown;
    int ch = vsscStr[0];
    switch (ch)
	{
    case 'A':
    case 'a':
        if (VSSCStrcasecmp(vsscStr, "alternative") == 0)
		{
            type = VSSCEnumMime::eSubtypeAlternative;
        }
        if (VSSCStrcasecmp(vsscStr, "appledouble") == 0)
		{
            type = VSSCEnumMime::eSubtypeAppledouble;
        }
        if (VSSCStrcasecmp(vsscStr, "applefile") == 0)
		{
            type = VSSCEnumMime::eSubtypeApplefile;
        }
        break;
    case 'B':
    case 'b':
        if (VSSCStrcasecmp(vsscStr, "basic") == 0)
		{
            type = VSSCEnumMime::eSubtypeBasic;
        }
        break;
    case 'D':
    case 'd':
        if (VSSCStrcasecmp(vsscStr, "delivery-status") == 0)
		{
            type = VSSCEnumMime::eSubtypeDeliveryStatus;
        }
        else if (VSSCStrcasecmp(vsscStr, "digest") == 0)
		{
            type = VSSCEnumMime::eSubtypeDigest;
        }
        break;
    case 'E':
    case 'e':
        if (VSSCStrcasecmp(vsscStr, "encrypted") == 0)
		{
            type = VSSCEnumMime::eSubtypeEncrypted;
        }
        else if (VSSCStrcasecmp(vsscStr, "enriched") == 0)
		{
            type = VSSCEnumMime::eSubtypeEnriched;
        }
        else if (VSSCStrcasecmp(vsscStr, "external-body") == 0)
		{
            type = VSSCEnumMime::eSubtypeExternalBody;
        }
        break;
    case 'G':
    case 'g':
        if (VSSCStrcasecmp(vsscStr, "gif") == 0)
		{
            type = VSSCEnumMime::eSubtypeGif;
        }
        break;
    case 'H':
    case 'h':
        if (VSSCStrcasecmp(vsscStr, "html") == 0)
		{
            type = VSSCEnumMime::eSubtypeHtml;
        }
        break;
    case 'J':
    case 'j':
        if (VSSCStrcasecmp(vsscStr, "jpeg") == 0)
		{
            type = VSSCEnumMime::eSubtypeJpeg;
        }
        break;
    case 'M':
    case 'm':
        if (VSSCStrcasecmp(vsscStr, "mixed") == 0)
		{
            type = VSSCEnumMime::eSubtypeMixed;
        }
        else if (VSSCStrcasecmp(vsscStr, "mpeg") == 0)
		{
            type = VSSCEnumMime::eSubtypeMpeg;
        }
        break;
    case 'O':
    case 'o':
        if (VSSCStrcasecmp(vsscStr, "octet-stream") == 0)
		{
            type = VSSCEnumMime::eSubtypeOctetStream;
        }
        break;
    case 'P':
    case 'p':
        if (VSSCStrcasecmp(vsscStr, "plain") == 0)
		{
            type = VSSCEnumMime::eSubtypePlain;
        }
        else if (VSSCStrcasecmp(vsscStr, "parallel") == 0)
		{
            type = VSSCEnumMime::eSubtypeParallel;
        }
        else if (VSSCStrcasecmp(vsscStr, "partial") == 0)
		{
            type = VSSCEnumMime::eSubtypePartial;
        }
        else if (VSSCStrcasecmp(vsscStr, "postscript") == 0)
		{
            type = VSSCEnumMime::eSubtypePostscript;
        }
        break;
    case 'R':
    case 'r':
        if (VSSCStrcasecmp(vsscStr, "report") == 0)
		{
            type = VSSCEnumMime::eSubtypeReport;
        }
        else if (VSSCStrcasecmp(vsscStr, "related") == 0)
		{
            type = VSSCEnumMime::eSubtypeRelated;
        }
        else if (VSSCStrcasecmp(vsscStr, "richtext") == 0)
		{
            type = VSSCEnumMime::eSubtypeRichtext;
        }
        else if (VSSCStrcasecmp(vsscStr, "rfc822") == 0)
		{
            type = VSSCEnumMime::eSubtypeRfc822;
        }
        else if (VSSCStrcasecmp(vsscStr, "rfc822-headers") == 0)
		{
            type = VSSCEnumMime::eSubtypeRfc822Headers;
        }
        break;
    case 'S':
    case 's':
        if (VSSCStrcasecmp(vsscStr, "signed") == 0)
		{
            type = VSSCEnumMime::eSubtypeSigned;
        }
    }
    return type;
}


void VSSCSubtypeEnumToStr(int nEnum, VSSCString& vsscStr)
{
    switch (nEnum) {
    case VSSCEnumMime::eSubtypeNull:
        vsscStr = "";
        break;
    case VSSCEnumMime::eSubtypeUnknown:
    default:
        vsscStr = "Unknown";
        break;
    case VSSCEnumMime::eSubtypePlain:
        vsscStr = "Plain";
        break;
    case VSSCEnumMime::eSubtypeRichtext:
        vsscStr = "Richtext";
        break;
    case VSSCEnumMime::eSubtypeEnriched:
        vsscStr = "Enriched";
        break;
    case VSSCEnumMime::eSubtypeHtml:
        vsscStr = "HTML";
        break;
    case VSSCEnumMime::eSubtypeMixed:
        vsscStr = "Mixed";
        break;
    case VSSCEnumMime::eSubtypeAlternative:
        vsscStr = "Alternative";
        break;
    case VSSCEnumMime::eSubtypeDigest:
        vsscStr = "Digest";
        break;
    case VSSCEnumMime::eSubtypeParallel:
        vsscStr = "Parallel";
        break;
    case VSSCEnumMime::eSubtypeRfc822:
        vsscStr = "Rfc822";
        break;
    case VSSCEnumMime::eSubtypePartial:
        vsscStr = "Partial";
        break;
    case VSSCEnumMime::eSubtypeExternalBody:
        vsscStr = "External-body";
        break;
    case VSSCEnumMime::eSubtypePostscript:
        vsscStr = "Postscript";
        break;
    case VSSCEnumMime::eSubtypeOctetStream:
        vsscStr = "Octet-stream";
        break;
    case VSSCEnumMime::eSubtypeJpeg:
        vsscStr = "jpeg";
        break;
    case VSSCEnumMime::eSubtypeGif:
        vsscStr = "gif";
        break;
    case VSSCEnumMime::eSubtypeBasic:
        vsscStr = "basic";
        break;
    case VSSCEnumMime::eSubtypeMpeg:
        vsscStr = "mpeg";
        break;
    case VSSCEnumMime::eSubtypeSigned:
        vsscStr = "signed";
        break;
    case VSSCEnumMime::eSubtypeEncrypted:
        vsscStr = "encrypted";
        break;
    case VSSCEnumMime::eSubtypeRfc822Headers:
        vsscStr = "rfc822-headers";
        break;
    case VSSCEnumMime::eSubtypeReport:
        vsscStr = "report";
        break;
    case VSSCEnumMime::eSubtypeDeliveryStatus:
        vsscStr = "delivery-status";
        break;
    case VSSCEnumMime::eSubtypeRelated:
        vsscStr = "related";
        break;
    case VSSCEnumMime::eSubtypeAppledouble:
        vsscStr = "appledouble";
        break;
    case VSSCEnumMime::eSubtypeApplefile:
        vsscStr = "applefile";
        break;
    }
}


int VSSCTypeStrToEnum(const VSSCString& vsscStr)
{
    int type = VSSCEnumMime::eTypeUnknown;
    int ch = vsscStr[0];
    switch (ch)
	{
    case 'A':
    case 'a':
        if (VSSCStrcasecmp(vsscStr, "application") == 0)
		{
            type = VSSCEnumMime::eTypeApplication;
        }
        else if (VSSCStrcasecmp(vsscStr, "audio") == 0)
		{
            type = VSSCEnumMime::eTypeAudio;
        }
        break;
    case 'I':
    case 'i':
        if (VSSCStrcasecmp(vsscStr, "image") == 0)
		{
            type = VSSCEnumMime::eTypeImage;
        }
        break;
    case 'M':
    case 'm':
        if (VSSCStrcasecmp(vsscStr, "message") == 0)
		{
            type = VSSCEnumMime::eTypeMessage;
        }
        else if (VSSCStrcasecmp(vsscStr, "model") == 0)
		{
            type = VSSCEnumMime::eTypeModel;
        }
        else if (VSSCStrcasecmp(vsscStr, "multipart") == 0)
		{
            type = VSSCEnumMime::eTypeMultipart;
        }
        break;
    case 'T':
    case 't':
        if (VSSCStrcasecmp(vsscStr, "text") == 0)
		{
            type = VSSCEnumMime::eTypeText;
        }
        break;
    case 'V':
    case 'v':
        if (VSSCStrcasecmp(vsscStr, "video") == 0)
		{
            type = VSSCEnumMime::eTypeVideo;
        }
        break;
    case 0:
        type = VSSCEnumMime::eTypeNull;
        break;
    }
    return type;
}


void VSSCTypeEnumToStr(int nEnum, VSSCString& vsscStr)
{
    switch (nEnum)
	{
    case VSSCEnumMime::eTypeNull:
        vsscStr = "";
        break;
    case VSSCEnumMime::eTypeUnknown:
    default:
        vsscStr = "Unknown";
        break;
    case VSSCEnumMime::eTypeText:
        vsscStr = "Text";
        break;
    case VSSCEnumMime::eTypeMultipart:
        vsscStr = "Multipart";
        break;
    case VSSCEnumMime::eTypeMessage:
        vsscStr = "Message";
        break;
    case VSSCEnumMime::eTypeApplication:
        vsscStr = "Application";
        break;
    case VSSCEnumMime::eTypeImage:
        vsscStr = "Image";
        break;
    case VSSCEnumMime::eTypeAudio:
        vsscStr = "Audio";
        break;
    case VSSCEnumMime::eTypeVideo:
        vsscStr = "Video";
        break;
    case VSSCEnumMime::eTypeModel:
        vsscStr = "Model";
        break;
    }
}
