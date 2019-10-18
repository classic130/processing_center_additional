#ifndef __NZDEFINES_
#define __NZDEFINES_

#define		ERR_STRING_LEN							12*1024
#define		MAX_FILE_PATH							4*MAX_PATH
#define		MAX_READ_SIZE							1024
#define		MAX_STRING_LEN							1024
#define		MAX_HASH_LEN							20

// Log file that will hold error information, created only for debug builds
#define		VS_NZLOGFILE							"c:\\vsdnotz.log"

// File that will hold the crl
#define		DEF_CRLFILE								"c:\\tempcrl.crl"

#define		HASH_SHA1_LENGTH						20
#define		HASH_MD5_LENGTH							16
#define		HASH_MD2_LENGTH							16
#define		HASH_MD4_LENGTH							16


// Values similar to those required by the PTA, needed when signing transaction
#define		SCRIPT_HASH_MD2							2
#define		SCRIPT_HASH_MD5							3
#define		SCRIPT_HASH_SHA1						4


#define		CAPI									1
#define		NON_CAPI								0


// Maximum response data that can be returned by the notarization server 
#define		MAX_NZ_RESPONZE							8*1024


// Maximum size of the record(receipt) file
//#define		MAX_RECORD_FILE_SIZE					12*1024


// This corresponds to the OPENPROF_OPEN_ONLY flag of the PTA
#define		PROF_OPEN_FLAG							529

// This corresponds to the EXP_DATE_GREATER_THAN flag of the PTA
#define		EXP_DATE_FLAG							0x20


/****** MAXIMUM SIZES ***/
#define MAX_ERR_DESC_SIZE		1024
#define MAX_RES_STRING_SIZE		1024

/********************** START OF UI RELATED DEFINES **********************/
/***** WIZARD AND UI CONSTANTS ****/ 
//Masks
#define WIZARD_BITS 0x00F00000
#define OPERATION_BITS 0x000FFF00
#define FLAG_BITS 0x000000FF

//Operations
#define SELFILE_BASE 0x00000100
#define PROGRESS_BASE 0x00000200
#define VERIFYRCPT_BASE	0x00000400
#define ERROR_BASE 0x00000800

//Wizards
#define NO_WIZARD_BASE 0x00000000
#define DIGNOTREQ_WIZARD_BASE 0x00100000
#define VERIFYRCPT_WIZARD_BASE 0x00200000

//Operation Flags

/****** UI Messages ***/

/****** POSITION OF UI IN WIZARD ***/
#define POS_FIRST 1
#define POS_MIDDLE 2
#define POS_LAST 3
#define POS_SOLO 4
#define POS_UNKNOWN 16


/***** FONTS IDENTIFIER ****/
#define FONTS_CUSTOM 0x01
#define FONTS_DEFAULT 0x02


/****** DIALOG BOX DEFINES ****/
#define DLGSIZE_CX ((int)(360.0*lXMult))
#define DLGSIZE_SMALL_CX ((int)(360.0*lXMult))
#define DLGSIZE_SMALL_CY ((int)(320.0*lYMult))
#define DLGSIZE_LARGE_CX ((int)(360.0*lXMult))
#define DLGSIZE_LARGE_CY ((int)(420.0*lYMult))
#define DLG_HEADER_SIZE ((int)(34.0*lYMult))
#define DLG_FOOTER_SIZE ((int)(52.0*lYMult))

#define WIZARD_TITLE_FONT_SIZE 20
#define UI_TITLE_FONT_SIZE 13
#define UI_TEXT_FONT_SIZE 13
#define UI_BTN_FONT_SIZE 14

#define HEADER_RIGHT_MARGIN ((int)(10.0*lXMult))
#define HEADER_LEFT_MARGIN ((int)(10.0*lXMult))
#define HEADER_TOPBTM_MARGIN ((int)(2.0*lXMult))
#define BITMAP_MAX_CX ((int)(200.0*lXMult))
#define BITMAP_MAX_CY ((int)(42.0*lXMult))

#define MAX_CLASSNAME 16

#define BTN_RIGHT_MARGIN ((int)(3.0*lXMult))
#define BTN_LEFT_MARGIN ((int)(2.0*lXMult))
#define BTN1_RGN_X ((int)(120.0*lXMult))
#define BTN_MIN_CX ((int)(65.0*lXMult))
#define BTN_MIN_CY ((int)(22.0*lYMult))
#define BTN_MAX_CX ((int)(100.0*lXMult))
#define BTN_MAX_CY ((int)(32.0*lYMult))
#define BTN_LEFTRIGHTMARGINS ((int)(10.0*lXMult))
#define BTN_TOPBTMMARGINS ((int)(6.0*lYMult))

#define UITITLE_LEFT_MARGIN (HEADER_LEFT_MARGIN + ((int)(5.0*lXMult)))
#define UITITLE_RIGHT_MARGIN HEADER_RIGHT_MARGIN
#define UITITLE_MAX_X (DLGSIZE_CX-UITITLE_LEFT_MARGIN-UITITLE_RIGHT_MARGIN)
#define UILABEL_SPACE ((int)(105.0*lXMult))
#define SELFILE_UILABEL_SPACE ((int)(65.0*lXMult))
#define SELFILE_EDIT_SPACE ((int)(10.0*lXMult))

#define UITEXT_LEFT_MARGIN UITITLE_LEFT_MARGIN
#define UITEXT_RIGHT_MARGIN UITITLE_RIGHT_MARGIN
#define UITEXT_MAX_X (DLGSIZE_CX-UITEXT_LEFT_MARGIN-UITEXT_RIGHT_MARGIN)
#define ERROR_TEXT_MAX_X (UITEXT_MAX_X * 0.85)

#define SELFILE_FILENAME_EDIT_SIZE ((int)(170.0*lXMult))
#define EDIT_TOPBTM_MARGINS ((int)(9.0*lYMult))
#define EDIT_MIN_CY ((int)(22.0*lYMult))
#define EDIT_MAX_CY ((int)(32.0*lYMult))
#define UI_LEFT_MARGIN ((int)(35.0*lXMult))
#define EDIT_RDONLY_MAX_CY ((int)(355.0*lYMult))
#define EDIT_RDONLY_TOPBTM_MARGINS ((int)(13.0*lYMult))

#define UIPROG_MAX_X (DLGSIZE_CX-UIPROG_LEFT_MARGIN-UIPROG_RIGHT_MARGIN)
#define UIPROG_LEFT_MARGIN UITITLE_LEFT_MARGIN
#define UIPROG_RIGHT_MARGIN ((int)(25.0*lXMult))
#define ERROR_TEXT_X (UITEXT_MAX_X * 0.15)

#define VRSNLOGO_X ((int)(90.0*lXMult))
#define VRSNLOGO_Y ((int)(38.0*lYMult))
#define VRSNLOGO_RGN_X ((int)(5.0*lXMult))
#define RBSLOGO_X ((int)(90.0*lXMult))
#define RBSLOGO_Y ((int)(87.0*lYMult))
#define DIGRCPT_X ((int)(332.0*lXMult)) //321
#define DIGRCPT_Y ((int)(226.0*lYMult)) // 224
#define ERROR_X ((int)(332.0*lXMult))
#define ERROR_Y ((int)(226.0*lYMult))


/***** ANCHOR DEFINES ***/
#define RGN_ANCH_TOPLEFT 1
#define RGN_ANCH_TOPRIGHT 2
#define RGN_ANCH_BOTTOMLEFT 3
#define RGN_ANCH_BOTTOMRIGHT 4
#define FLD_XANCH_LEFT 5
#define FLD_XANCH_RIGHT 6
#define FLD_XANCH_MIDDLE 7
#define FLD_YANCH_TOP 8
#define FLD_YANCH_BOTTOM 9
#define FLD_YANCH_MIDDLE 10
/********************** END OF UI RELATED DEFINES **********************/

//Defines for verification and integrity result
#define VERIFY_CORRECT	1
#define VERIFY_INCORRECT 2
#define INTEGRITY_CORRECT 1
#define INTEGRITY_INCORRECT 2


// Language identifiers
#define LANG_ENGLISH_US 0x0409

//Maximum file path size
#define MAX_FILE_SIZE 512

//Netscape and IE HTTP Headers



#define	IE_USERAGENT	"MSIE"
#define	NS_USERAGENT	"Mozilla"

#define	NS_HTTP_HEADERS	"Accept:image/gif,image/x-xbitmap,\
image/jpeg,image/pjpeg,image/png,*\/*\r\n\
Accept-Encoding:gzip\r\nAccept-Language:en\r\n\
Accept-Charset:iso-8859-1,*,utf-8"

#define	IE_HTTP_HEADERS	"Accept:*\/*\r\n\
Accept-Encoding:gzip, deflate\r\n\
Accept-Language:en-us"


#define	SELECT_OPEN		1
#define SELECT_SAVE		2

#endif	// __NZDEFINES_