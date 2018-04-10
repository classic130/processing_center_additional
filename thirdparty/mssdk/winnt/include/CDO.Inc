<%
'<!--CDOSYS.DLL Constants-->
'<!--cdo.inc : Application constants-->
'<!--Copyright (c) Microsoft Corporation 1993-1998. All rights reserved.-->
'
' Constants.inc contains constant declarations used with Microsoft CDO 2.0.
'

'  ----------------------------------------
'  CdoDataSource Values
'  ----------------------------------------

Const 	CdoDataSourceEmpty = 0
Const 	CdoDataSourceStream = 1
Const 	CdoDataSourceBodyPart = 2

'  ----------------------------------------
'   MHTMLFlags Values
'  ----------------------------------------

Const 		SuppressNone	= 0
Const 		SuppressSrc		= 256
Const 		SuppressCode	= 512
Const 		SuppressAll		= 768

'  ----------------------------------------
'  EncodingType Constants
'  ----------------------------------------

Const EncodingType_UsAscii			 = "us-ascii"
Const EncodingType_Enc7bit			 = "7bit"
Const EncodingType_QuotedPrintable	 = "quoted-printable"
Const EncodingType_Base64			 = "base64"
Const EncodingType_Enc8bit			 = "8bit"
Const EncodingType_Binary			 = "binary"
Const EncodingType_Uuencode			 = "UUENCODE"

'  ----------------------------------------
'  ContentMediaType Constants
'  ----------------------------------------

Const ContentMediaType_TextPlain		 = "text/plain"
Const ContentMediaType_TextHtml			 = "text/html"
Const ContentMediaType_MultipartAlt		 = "multipart/alternative"
Const ContentMediaType_MultipartRelated	 = "multipart/related"
Const ContentMediaType_MultipartMixed	 = "multipart/mixed"
Const ContentMediaType_Message			 = "message/rfc822"
Const ContentMediaType_MultipartDigest	 = "multipart/digest"
Const ContentMediaType_MessagePartial	 = "message/partial"
Const ContentMediaType_MessageExternal	 = "message/external-body"
Const ContentMediaType_ImageGif			 = "image/gif"
Const ContentMediaType_ImageJpeg		 = "image/jpeg"

'  ----------------------------------------
'  ConfigProperties Constants
'  ----------------------------------------

Const ConfigProperties_NNTPServer					 = "NNTPServer"
Const ConfigProperties_NNTPServerPickupDirectory	 = "NNTPServerPickupDirectory"
Const ConfigProperties_NNTPServerPort				 = "NNTPServerPort"
Const ConfigProperties_NNTPUserDisplayName			 = "NNTPUserDisplayName"
Const ConfigProperties_NNTPUserEmailAddress			 = "NNTPUserEmailAddress"
Const ConfigProperties_NNTPUserReplyEmailAddress	 = "NNTPUserReplyEmailAddress"
Const ConfigProperties_SMTPServer					 = "SMTPServer"
Const ConfigProperties_SMTPServerPickupDirectory	 = "SMTPServerPickupDirectory"
Const ConfigProperties_SMTPServerPort				 = "SMTPServerPort"
Const ConfigProperties_SMTPUserDisplayName			 = "SMTPUserDisplayName"
Const ConfigProperties_SMTPUserEmailAddress			 = "SMTPUserEmailAddress"
Const ConfigProperties_SMTPUserReplyEmailAddress	 = "SMTPUserReplyEmailAddress"

'  ----------------------------------------
'  Namespace Constants
'  ----------------------------------------

Const Namespace_Messaging	 = "http://www.iana.org/standards/rfc822/"
Const Namespace_Mime			 = "http://www.iana.org/standards/mime/"

'  ----------------------------------------
'  MimeProperties Constants
'  ----------------------------------------

Const MimeProperties_ContentBase				 = "http://www.iana.org/standards/mime/Content-Base"
Const MimeProperties_ContentDescription		 = "http://www.iana.org/standards/mime/Content-Description"
Const MimeProperties_ContentDisposition		 = "http://www.iana.org/standards/mime/Content-Disposition"
Const MimeProperties_ContentId				 = "http://www.iana.org/standards/mime/Content-ID"
Const MimeProperties_ContentLanguage			 = "http://www.iana.org/standards/mime/Content-Language"
Const MimeProperties_ContentMediaType			 = "http://www.iana.org/standards/mime/Content-Media-Type"
Const MimeProperties_ContentTransferEncoding	 = "http://www.iana.org/standards/mime/Content-Transfer-Encoding"
Const MimeProperties_ContentType				 = "http://www.iana.org/standards/mime/Content-Type"

'  ----------------------------------------
'  MessageProperties Constants
'  ----------------------------------------

Const MessageProperties_Comments							 = "http://www.iana.org/standards/rfc822/Comments"
Const MessageProperties_Approved							 = "http://www.iana.org/standards/rfc822/Approved"
Const MessageProperties_BodyStructure					 = "http://www.iana.org/standards/rfc822/BodyStructure"
Const MessageProperties_BCC								 = "http://www.iana.org/standards/rfc822/Bcc"
Const MessageProperties_CC								 = "http://www.iana.org/standards/rfc822/CC"
Const MessageProperties_Date								 = "http://www.iana.org/standards/rfc822/Date"
Const MessageProperties_DateReceived						 = "http://www.iana.org/standards/rfc822/DateReceived"
Const MessageProperties_DispositionNotificationOption	 = "http://www.iana.org/standards/rfc822/Disposition-Notification-Option"
Const MessageProperties_DispositionNotificationTo		 = "http://www.iana.org/standards/rfc822/Disposition-Notification-To"
Const MessageProperties_Distribution						 = "http://www.iana.org/standards/rfc822/Distribution"
Const MessageProperties_Expires							 = "http://www.iana.org/standards/rfc822/Expires"
Const MessageProperties_FollowupTo						 = "http://www.iana.org/standards/rfc822/Followup-To"
Const MessageProperties_From								 = "http://www.iana.org/standards/rfc822/From"
Const MessageProperties_HasAttachment					 = "http://www.iana.org/standards/rfc822/HasAttachment"
Const MessageProperties_HTMLDescription					 = "http://www.iana.org/standards/rfc822/HTMLDescription"
Const MessageProperties_Importance						 = "http://www.iana.org/standards/rfc822/Importance"
Const MessageProperties_InReplyTo						 = "http://www.iana.org/standards/rfc822/In-Reply-To"
Const MessageProperties_Keywords							 = "http://www.iana.org/standards/rfc822/Keywords"
Const MessageProperties_Lines							 = "http://www.iana.org/standards/rfc822/Lines"
Const MessageProperties_MessageId						 = "http://www.iana.org/standards/rfc822/Message-ID"
Const MessageProperties_MimeVersion						 = "http://www.iana.org/standards/rfc822/MIME-Version"
Const MessageProperties_Newsgroups						 = "http://www.iana.org/standards/rfc822/Newsgroups"
Const MessageProperties_NNTPPostingHost					 = "http://www.iana.org/standards/rfc822/NNTP-Posting-Host"
Const MessageProperties_NNTPPostingUser					 = "http://www.iana.org/standards/rfc822/NNTP-Posting-User"
Const MessageProperties_Path								 = "http://www.iana.org/standards/rfc822/Path"
Const MessageProperties_Priority							 = "http://www.iana.org/standards/rfc822/Priority"
Const MessageProperties_References						 = "http://www.iana.org/standards/rfc822/References"
Const MessageProperties_RelayVersion						 = "http://www.iana.org/standards/rfc822/Relay-Version"
Const MessageProperties_ReplyTo							 = "http://www.iana.org/standards/rfc822/Reply-To"
Const MessageProperties_ReturnPath						 = "http://www.iana.org/standards/rfc822/Return-Path"
Const MessageProperties_Sender							 = "http://www.iana.org/standards/rfc822/Sender"
Const MessageProperties_Sensitivity						 = "http://www.iana.org/standards/rfc822/Sensitivity"
Const MessageProperties_Subject							 = "http://www.iana.org/standards/rfc822/Subject"
Const MessageProperties_Submitted						 = "http://www.iana.org/standards/rfc822/Submitted"
Const MessageProperties_Summary							 = "http://www.iana.org/standards/rfc822/Summary"
Const MessageProperties_TextDescription					 = "http://www.iana.org/standards/rfc822/TextDescription"
Const MessageProperties_To								 = "http://www.iana.org/standards/rfc822/To"
Const MessageProperties_XMailer							 = "http://www.iana.org/standards/rfc822/X-Mailer"
Const MessageProperties_Xref								 = "http://www.iana.org/standards/rfc822/Xref"
%>
