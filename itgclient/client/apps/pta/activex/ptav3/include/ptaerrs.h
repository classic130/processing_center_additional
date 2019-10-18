#ifndef _VS_PTA_ERRS_
#define _VS_PTA_ERRS_

/******** Generic return codes ***/
#define VS_OK		1
#define VS_ERROR	0

/******** HRESULTS *******/
#define E_INITIALIZED 0x80001001
#define E_EMPTYARGS	  0x80001002
#define E_INVALIDARGS 0x80001003
#define E_HOSTBAD	  0x80001004
#define E_APPCTXTBAD  0x80001005
#define E_NOTINITIALIZED 0x80001006
#define E_CARDNOTOPEN 0x80001008
#define E_CAPIMODEONLY 0x80001009
#define E_LANGNOTSUPPORTED 0x8000100A
#define E_BUFFTOSMALL 0x8000100C
#define E_NOFONT	0x8000100D
#define E_FONTNOTAVAILABLE 0x8000100E
#define E_FONTDOESNOTSUPPORTLANG 0x8000100F
#define E_INVALIDVALUE 0x80001020
#define E_IDNOTSELECTED 0x80001021
#define E_CARDOPEN	  0x80001022
#define E_CANNOTLOADMSCAPI 0x80001023
#define E_CANNOTLOADVSCAPI 0x80001024
#define E_CANNOTFINDWINDOWSDIR 0x80001025
#define E_PATHNOTFOUND 0x80001026
#define E_FILENOTFOUND 0x80001027
#define E_NONCAPIMODEONLY 0x80001028
#define E_INVALIDFLAGS 0x80001029
#define E_PROFDOESNOTEXIST 0x8000102B
#define E_PASSWDREQD 0x8000102C
#define E_PROFEXISTS 0x8000102D
#define E_OPERATIONPOSUNKNOWN 0x8000102E
#define E_CARDALREADYOPEN 0x8000102F
#define E_INVALIDWIZARDFLAG 0x80001030
#define E_INVALIDUIFLAG 0x80001031
#define E_PROFCREATED 0x80001032
#define E_SEP_SETPOSFAILED 0x80001033
#define E_DEFWIZTITLEFONTFAIL 0x80001034
#define E_DEFUITITLEFONTFAIL 0x80001035
#define E_DEFUITEXTFONTFAIL 0x80001036
#define E_DEFBTNFONTFAIL 0x80001037
#define E_CUSTWIZTITLEFONTFAIL 0x80001035
#define E_CUSTUITITLEFONTFAIL 0x80001036
#define E_CUSTUITEXTFONTFAIL 0x80001037
#define E_CUSTBTNFONTFAIL 0x80001038
#define E_INTERNETOPENERR 0x80001039
#define E_INTERNETOPENURLERR 0x80001040
#define E_COULDNOTGETTEMPPATH 0x80001041
#define E_COULDNOTGETTEMPFILENAME 0x80001042
#define E_COULDNOTCREATETEMPFILE 0x80001043
#define E_INTERNETREADERR 0x80001043
#define E_FILEWRITEERR 0x80001044
#define E_INTERNETATTEMPTERR 0x80001045
#define E_COULDNOTGETBMPDIMS 0x80001046
#define E_FIELD_SELOBJFAILED 0x80001047
#define E_FIELD_SETTEXTFAILED 0x80001048
#define E_DLG_SETDIMSFAILED 0x80001049
#define E_HEADERLOGO_SHOWFAILED 0x8000104B
#define E_FIELD_SETPOSFAILED 0x8000104C
#define E_FIELD_GETTEXTEXTENTFAILED 0x8000104D
#define E_FIELD_GETCLIENTRECTFAILED 0x8000104E
#define E_FIELD_SETDIMSFAILED 0x8000104F
#define E_FIELD_GETDLGITEMFAILED 0x80001050
#define E_FIELD_GETDCFAILED 0x80001051
#define E_DLG_GETDCFAILED 0x80001052
#define E_CREATEPATTERNBRUSH_FAILED 0x80001053
#define E_CREATESOLIDBRUSH_FAILED 0x80001054
#define E_CERT_SELECTBLACKBRUSH_FAILED 0x80001055
#define E_CERT_ROUNDRECTFAILED 0x80001056
#define E_CERTINFOFONTFAIL 0x80001057
#define E_CERTVALIDLITYLBLFONTFAIL 0x80001058
#define E_NOCNFOUND 0x80001059
#define E_GETLOCALEINFOFAILED 0x8000105A
#define E_VARTIMETOSYSTIMEFAILED 0x8000105B
#define E_GETDATEFORMATFAILED 0x8000105C
#define E_GETDATEFORMATSIZEFAILED 0x8000105C
#define E_CERT_SELECTTEXTUREBRUSH_FAILED 0x8000105D
#define E_DPTOLPFAILED 0x8000105E
#define E_INSERTCOLFAILED 0x8000105F
#define E_INSERTITEMFAILED 0x80001060
#define E_SETITEMFAILED 0x80001061
#define E_GETCLASSNAMEFAILED 0x80001062
#define E_GETCLASSINFOFAILED 0x80001063
#define E_GETDLGITEMTEXTFAILED 0x80001064
#define E_DLGBTNCHECKEDFAILED 0x80001065
#define E_INVALIDATERECTFAILED 0x80001066
#define E_USERCANCELLED 0x80001067
#define E_CONFIRMPASSWORDNOMATCH 0x80001068
#define E_GETSTRINGTYPEFAILED 0x80001069
#define E_SAFEARRAYGETUBOUNDFAILED 0x80001070
#define E_INVALIDKEYTYPE 0x80001071
#define E_DNPARSEERR 0x80001072
#define E_SUBJECTDNINVALID 0x80001073
#define E_ASCHEXTTOBYTESFAILED 0x80001074
#define E_HASHBEGINERR 0x80001075
#define E_HASHDATAERR 0x80001076
#define E_HASHENDERR 0x80001077
#define E_VSCNOTINIT 0x80001078
#define E_REGCREATEKEYFAILED 0x80001079
#define E_REGSETVALUEFAILED 0x80001080
#define E_REGOPENKEYFAILED 0x80001081
#define E_REGQUERYVALFAILED 0x80001082
#define E_REGDELVALUEFAILED 0x80001083
#define E_INVALIDPKCS7 0x80001084
#define E_SAFEARRAYACCDATAFAILED 0x80001085
#define E_SAFEARRAYCREATEVECTFAILED 0x80001086
#define E_CERTOPENSYSSTOREFAILED 0x80001087
#define E_ADDCERTTOSTOREFAILED 0x80001088
#define E_CERTEXISTS 0x80001089
#define E_SETPROPFAILED 0x8000108A
#define E_INVALIDASNKEYENC 0x8000108B
#define E_NOT_GMT 0x8000108C
#define E_SYSTOFT_ERR 0x8000108D
#define E_PROFLOCKEDOUT 0x8000108E
#define E_PATHNAMEPARSEERR 0x8000108F
#define E_EXPENVSTRFAILED 0x80001090
#define E_CERTNOTFOUND 0x80001091
#define E_CERTNAMETOSTRFAILED 0x80001092
#define E_FILETIMETOSYSTIMEFAILED 0x80001093
#define E_SYSTIMETOVARTIMEFAILED 0x80001094
#define E_CERTNOMATCHCRIT 0x80001095
#define E_CERTMATCHBUTEXP 0x80001096
#define E_KEYDOESNOTEXIST 0x80001097
#define E_HTTPSREQD 0x80001098
#define E_CERTPREFNOTFOUND 0x80001099
#define	E_ROAMING_START_SESSION_FAILED 0x8000109A
#define	E_ROAMING_STORE_DATA_FAILED 0x8000109B
#define	E_ROAMING_UPDATE_FAILED 0x8000109C
#define E_ROAMING_RECDATA_FAILED 0x8000109D
#define E_SAFEARRAYCREATEFAILED 0x8000109E
#define E_INSTALLCERTWRONGPROFILE 0x8000109F
#define E_AUTHDLLNOTPRESENT 0x800010A0
#define E_GETPROCADDRFAILED 0x800010A1
#define E_AUTHDLL_INVALIDDIMS 0x800010A2
#define E_CRYPT32LOADFAILED 0x800010A3
#define E_CERTFREECERTCTXTLOADFAILED 0x800010A4
#define E_CERTCLOSESTORELOADFAILED 0x800010A5
#define E_CERTADDENCERTTOSTORELOADFAILED 0x800010A6
#define E_CERTSETCERTCTXTPROPLOADFAILED 0x800010A7
#define E_CERTENUMCERTINSTORELOADFAILED 0x800010A8
#define E_CRYPTSIGNMSGFAILED 0x800010A9
#define E_ADVAPI32LOADFAILED 0x800010AA
#define E_INVALIDPKCS8 0x800010AB
#define E_NOPRIVKEYBLOB 0x800010AC
#define E_PASSWORDPROVIDED 0x800010AD
#define E_CERTSERIALIZEFAILED 0x800010AE
#define E_ROAM_REQDNOPASSWD_INVALID 0x800010AF
#define	E_OPT_FAILED_DUE_TO_TIMEOUT	0x800010B0
#define	E_ROAM_RESERVE_FAILED		0x800010B1
#define E_INVALIDCERTSIZE	0x800010B2
#define E_DELETECERTFROMSTOREFAILED 0x800010B3
#define E_CERTSERCERTSTORELEMFAILED 0x800010B4
#define E_CERTDELCERTFAILED 0x800010B5

//	added by anand for P12 Export
#define	E_P8_INVALID_PARAMS 0x800010B6
#define	E_P8_ERROR_FINDING_PRIMES	0x800010B7
#define	E_P8_ERROR_ENCODING	0x800010B8

#define	E_P12E_WRONG_TYPE 0x800010B9
#define E_P12E_ZERO_CERTS_NOT_ALLOWED 0x800010BA
#define	E_P12E_CANNOT_SET_CERT 0x800010BB
#define	E_P12E_CERT_LEN_ZERO 0x800010BC
#define	E_P12E_KEY_LEN_ZERO 0x800010BD
#define	E_P12E_INIT_PARAM 0x800010BE
#define E_P12E_KEY_GEN 0x800010BF
#define E_P12E_IV_GEN 0x800010C0
#define	E_P12E_ENCRYPTION 0x800010C1
#define E_P12E_KEY_NULL 0x800010C2
#define	E_P12E_KEYNOTEXPORTABLE 0x800010C3

// added by sameer for aff logo url support
#define E_INVALIDURL 0x800010C4

#define	E_UPGRADE 0x800010C5
#define	E_USERENV_DLL_MISSING 0x800010C6
#define E_GETPROC 0x800010C7
#define	E_GETUSERNAME 0x800010C8

// Wasim: getting open/save file name from Windows
#define	E_GETOPENFILERR	0x800010C9
#define	E_GETSAVEFILERR	0x800010CA

// Wasim: moved these error codes from above and assigned new values to them so that they do no
// correspond to those defined in pkcs12errs.h
#define E_INVALIDPASSWD 0x800010CB
#define E_INVALIDPASSWD_NOPASSWDREQD 0x800010CC
#define E_INVALIDPASSWD_LESSTHANMINLENGTH 0x800010CD
#define E_INVALIDPASSWD_NOTNUMERICONLY 0x800010CE
#define E_INVALIDPASSWD_INVALIDCHARS 0x800010CF
#define E_INVALIDPASSWD_LESSTHANMINNOOFNUM 0x800010D0
#define E_INVALIDPASSWD_NONUMATBEGIN 0x800010D1
#define E_INVALIDPASSWD_NONUMATEND 0x800010D2
#define E_INVALIDPASSWD_PASSWDREQD 0x800010D3

// Wasim: error while encrypting/decrypting
#define E_ENCRYPTFAIL 0x800010D4
#define E_DECRYPTFAIL 0x800010D5

// Wasim: error while decoding the profile
#define E_INVALIDPROFILE 0x800010D6

// Wasim: version of profile not supported
#define E_INVALIDVERSION 0x800010D7

// Wasim : added to support variable width transaction signing dialog
#define	E_INVALID_HEIGHT 0x800010D8
#define	E_INVALID_WIDTH	0x800010D9
#define E_SYSPARAMSERR 0x800010DA

// Sasi: Added error code for app context errors
#define E_APPCTXTFAILED 0x800010DB

// Sasi: Added error code for thread creation errors
#define E_CREATETHREADFAILED 0x800010DC

// Ajay: Added error for loading the VS_XXXTSS library
#define E_TSSLIBLOADFAILED 0x800010DE


// Sasi 05/02/2003
// Added error codes for roaming password reset errors
#define E_CREATESECRET 0x800010DF
#define E_ROAMING_QUERYRESETPASSWORD_FAILED 0x800010E0
#define E_RESETFEATURE_NOT_SUPPORTED 0x800010E1
#define E_GETSECRET_PROFILEREQD 0x800010E2
#define E_GETSECRET_PROFDOESNOTEXIST 0x800010E3
#define E_RESETPASSWD_ANSWERPASSWDREQD 0x800010E4
#define E_RESETPASSWD_WRONGANSWER 0x800010E5
#define E_RESETPASSWD_PROFLOCKOUT 0x800010E6
#define E_RESETPASSWD_FAILED 0x800010E7
#define E_CREATESECRET_SECRETREQD 0x800010E8
#define E_ROAMING_GETUSERQUESTION_FAILED 0x800010E9


#define E_UTF8_ENCODING_FAILED 0x800010EA

// Added by Ryan for HTML signing validation
#define	E_HTMLMSG_LOAD					0x80001101
#define	E_HTMLMSG_COLORDIFF				0x80001102
#define	E_HTMLMSG_SCRIPTS				0x80001103
#define	E_HTMLMSG_EMBEDS				0x80001104
#define	E_HTMLMSG_FORMS					0x80001105
#define	E_HTMLMSG_FRAMES				0x80001106
#define	E_HTMLMSG_IMAGES				0x80001107
#define	E_HTMLMSG_APPLETS				0x80001108
#define	E_HTMLMSG_PLUGINS				0x80001109
#define	E_HTMLMSG_STYLESHEETS			0x8000110A
#define	E_HTMLMSG_BADTAG				0x8000110B
#define	E_HTMLMSG_DEFAULTCOLORDIFF		0x8000110C
#define	E_HTMLMSG_LAST					0x800011OD



#endif