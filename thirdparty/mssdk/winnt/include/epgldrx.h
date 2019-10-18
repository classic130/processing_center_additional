// tssldrx.h : external interface definition for
// epg loader .dlls main entry point
//
// Copyright(c) 1996 Microsoft Corp.

#ifndef _EPGLDRX_H_
#define _EPGLDRX_H_

extern "C"
{

// this list defines the exit codes used by the standard loader stub and
// the sample loader.
// any codes <= EXIT_LDR_DEF_SUCCESS or >= EXIT_LDR_DEF_ERROR
// will be passed straight through in order to implement extensible loader
// defined errors.  it is up to an individual loader to add the appropriate
// section to sage registry entries for these additional codes.
// each loader should check to make sure that extended error codes are not
// colliding with codes already present.
enum ExitCodeList
{
 	// common loader codes
	EXIT_OK = 0,             // success
	EXIT_FIRST_CODE = EXIT_OK,
	EXIT_INCOMPLETE = 1,     // success, but not all guide info added
 	EXIT_LAST_LOADER_SUCCESS = 1,
	EXIT_ABORT = 2,
	// 3 is the value returned by VC's ASSERT mechanism
	EXIT_FAIL = 4,           // unknown failure
 	
	// loadstub codes
    EXIT_MISSINGDLL = 5,
    EXIT_DB = 6,				// can't open database
    EXIT_USAGE = 7,				// missing command line argument
    EXIT_BUSY = 0xF9,			// magic sage retry code

	// more common loader codes
	EXIT_COMPACT = 300,
	EXIT_REPAIR = 301,
	EXIT_FAIL_CEXCEPTION = 302,
	EXIT_FAIL_DBEXCEPTION = 303,
	EXIT_FAIL_GETTIMEZONE = 304,
	EXIT_FAIL_GETTUNINGSPACE = 305,
	EXIT_FAIL_BADTUNINGSPACE = 306,
	EXIT_FAIL_BADSTARTTIME = 307,
	EXIT_FAIL_BADENDTIME = 308,
	EXIT_FAIL_GETLOADERREADFILE = 309,
	EXIT_FAIL_LOADERREADFILE = 310,

	// StarSight specific
	EXIT_FAIL_GETREGIONID = 400,
    EXIT_FIRST_LOADER_DEF = EXIT_FAIL_GETREGIONID,

	// DTV specific
	EXIT_FAIL_NULLPGDR = 500,
	EXIT_FAIL_NULLPGM = 501,
	EXIT_FAIL_PGMHEADER = 502,
	EXIT_FAIL_PGMSIZE = 503,
	EXIT_FAIL_PIVHEADER = 504,
	EXIT_FAIL_PIVSPGNUM = 505,
	EXIT_FAIL_VIEWLISTSPRINTF = 506,
	EXIT_FAIL_VIEWLISTMASK = 507,
	EXIT_FAIL_NULLAPGD = 508,
	EXIT_FAIL_APGDSYNC = 509,
	EXIT_FAIL_APGDHEADER = 510,
	EXIT_FAIL_APGDCHECKSUM = 511,
	EXIT_FAIL_SPIGTV = 512,
	EXIT_FAIL_SPILTV = 513,
	EXIT_FAIL_SPIGTV_CD = 514,
	EXIT_FAIL_SPILTV_CD = 515,
	EXIT_FAIL_SPIGTV_SD = 516,
	EXIT_FAIL_SPILTV_SD = 517,
	EXIT_FAIL_SPIGTV_DAVIS = 518,
	EXIT_FAIL_SPIGTV_R9_DAVIS = 519,
	EXIT_FAIL_SPIGTV_R9 = 520,
	EXIT_FAIL_SPILTV_R9 = 521,
	EXIT_FAIL_SPILTV_DAVIS = 522,
	EXIT_FAIL_SPIGA = 523,
	EXIT_FAIL_SPICD = 524,
	EXIT_FAIL_SPISD = 525,
	EXIT_FAIL_SPIHSD = 526,
	EXIT_FAIL_EXPLICITSCID = 527,
	EXIT_FAIL_SPI = 528,
	EXIT_FAIL_EXPLICITHEAP = 529,
	EXIT_FAIL_SCIDSIZE = 530,
	EXIT_FAIL_DIPXSPONDER = 531,
	EXIT_FAIL_DIPFLAG = 532,
	EXIT_FAIL_LABELEN = 533,
	EXIT_FAIL_NOLABEL = 534,
	EXIT_FAIL_PIPXSPONDER = 535,
	EXIT_FAIL_CSSMNULL = 536,
	EXIT_FAIL_CSSMSYNC = 537,
	EXIT_FAIL_CSSMHEADER = 538,
	EXIT_FAIL_CSSMCHECKSUM = 539,
	EXIT_FAIL_SEGMENTNUM = 540,
	EXIT_FAIL_CIREC = 541,
	EXIT_FAIL_DIPPROCESSBUFFER = 542,
	EXIT_FAIL_DSSDATE = 543,
	EXIT_FAIL_APPLIEDTIME = 544,
	EXIT_FAIL_NULLSEGM = 545,
	EXIT_FAIL_SEGMSYNC = 546,
	EXIT_FAIL_SEGMHEADER = 547,
	EXIT_FAIL_SEGMCHECKSUM = 548,
	EXIT_FAIL_SEGMSEGMENTS = 549,
	EXIT_FAIL_SEGMPACKETSIZE = 550,
	EXIT_FAIL_STARTDAY = 551,
	EXIT_FAIL_STARTINFO = 552,
	EXIT_FAIL_STARTTIME = 553,
	EXIT_FAIL_RATING = 554,
	EXIT_FAIL_PI2CHAN = 555,
	EXIT_FAIL_CHAN2PIP = 556,
	EXIT_FAIL_CHAN2DIP = 557,
	EXIT_FAIL_CHAN2NUM = 558,
	EXIT_FAIL_PIAHEADER = 559,
	EXIT_FAIL_STARTSLOT = 560,
	EXIT_FAIL_ENDTIME = 561,
	EXIT_FAIL_NULLPISM = 562,
	EXIT_FAIL_PISMSYNC = 563,
	EXIT_FAIL_PISMHEADER = 564,
	EXIT_FAIL_PISMCHECKSUM = 565,
	EXIT_FAIL_LISTGUIDESLOTS = 566,
	EXIT_FAIL_ES = 567,
	EXIT_FAIL_ARRIVALTIME = 568,
	EXIT_FAIL_MPGPROCESSBUFFER = 569,
	EXIT_FAIL_SPGPROCESSBUFFER = 570,
	EXIT_FAIL_PIPFLAG = 571,
	EXIT_FAIL_CHAN2PIPMSGNUM = 572,
	EXIT_FAIL_PARSE = 573,
	EXIT_FAIL_LOADERREADNET = 574,
	EXIT_FAIL_DBE_INIT = 575,
	EXIT_FAIL_ENHANCEMENTS = 576,
	EXIT_LAST_CODE = EXIT_FAIL_ENHANCEMENTS
};

#ifdef _DBDAO_H_
typedef BOOL (*PFNFORCEQUIT)(VOID);
ExitCodeList APIENTRY EPG_DBLoad(int &argc, _TCHAR **argv, CdbDBEngine &db, PFNFORCEQUIT pfnForceQuit);
typedef ExitCodeList (APIENTRY *PFNDBLOAD)(int &argc, _TCHAR **argv, CdbDBEngine &db, PFNFORCEQUIT pfnForceQuit);
#endif
};

// the tuning space value must be the 0th parameter
// of all of the delete queries
const int giTuningSpacePos = 0;

// wparam for broadcast event messages
enum EpgldrEventList
{
    EPGLDR_STARTING = 1,
    EPGLDR_ACTIVE_COMMIT_STARTING = 2,
    EPGLDR_ACTIVE_COMMIT_ENDING = 3,
    EPGLDR_PASSIVE_COMMIT_STARTING = 4,
    EPGLDR_PASSIVE_COMMIT_ENDING = 5,
    EPGLDR_ENDING = 6,
    EPGLDR_EXCLUSIVE_STARTING = 7,
    EPGLDR_EXCLUSIVE_ENDING = 8,
    EPGLDR_ACTIVE_COMMIT_EPIENHANCE_STARTING = 9,
    EPGLDR_ACTIVE_COMMIT_EPIENHANCE_ENDING = 10
};

#define SZLOADERSTUBGUID _T("{27DB71E0-776C-11cf-B8E8-0020AFDFD047}")
#define GUIDLOADERSTUB ({ 0x27db71e0, 0x776c, 0x11cf, { 0xb8, 0xe8, 0x0, 0x20, 0xaf, 0xdf, 0xd0, 0x47 } })

#define SZDTVLOADGUID _T("{7B501360-8D71-11cf-A88F-444553540000}")
#define GUIDDTVLOAD ({ 0x7b501360, 0x8d71, 0x11cf, { 0xa8, 0x8f, 0x44, 0x45, 0x53, 0x54, 0x0, 0x0 } })

#define SZSSLOADGUID _T("{C94D1940-9F69-11d0-BDB8-0000F8027346}")
#define GUIDSSLOAD ({ 0xc94d1940, 0x9f69, 0x11d0, { 0xbd, 0xb8, 0x0, 0x0, 0xf8, 0x2, 0x73, 0x46 } })

#define SZCDFLOADGUID _T("{45CD64E2-D2D5-11d0-AB57-00AA00C23166}")
#define GUIDCDFLOAD ({ 0x45CD64E2, 0xD2D5, 0x11d0, { 0xAB, 0x57, 0x0, 0xAA, 0x0, 0xC2, 0x31, 0x66 } })

#define SZDOWNLOADGUID _T("{62765981-333D-11d1-883A-3C8B00C10000}")
#define GUIDDOWNLOAD ({ 0x62765981, 0x333d, 0x11d1, { 0x88, 0x3a, 0x3c, 0x8b, 0x0, 0xc1, 0x0, 0x0 } })

#define SSSCAN		_T("{C94D1940-9F69-11d0-BDB8-0000F8027346}-Scan")
#define SSSCANEND	_T("{C94D1940-9F69-11d0-BDB8-0000F8027346}-ScanEnded")
#define SSHEAR		_T("{C94D1940-9F69-11d0-BDB8-0000F8027346}-Listen")
#define SSHEAREND	_T("{C94D1940-9F69-11d0-BDB8-0000F8027346}-ListenEnded")


enum SSExitCodeList
{
	SUCCESS,
	ALREADY_RUNNING,
	INCOMPLETE_SCAN,
	NO_CHANNELS_FOUND,
	NO_VBI_DATA_FOUND,
	NO_SS_DATA_FOUND,
	NO_GOOD_SS_DATA_FOUND,
	NO_REGION_FOUND,
	INCOMPLETE_DATA
};


#endif
