#ifndef _VS_DNZ_UI_DATASTRUCTS_
#define _VS_DNZ_UI_DATASTRUCTS_

#include <comdef.h>

//Forward declaration
typedef struct _OPCTXT* POPCTXT;
typedef struct _UICTXT* PUICTXT;

typedef HRESULT (*LPFNBtnFn) (POPCTXT pOpCtxt);


typedef struct _OPARAMS
{
	_bstr_t	tbstrNotResponse;	//Response of the notarization request
	int nVerificationResult;	//Result of verifying a notarization response	
	_bstr_t tbstrSelFile;		//The selected document that should be notarized
} OPARAMS, *POPARAMS;

typedef struct _OPCTXT
{
	int nWizardAndUIs;	  //contains a bit field indicating the wizard and UIs to show.
	POPARAMS pOParams;  	  //Pointer to the output params object.
	void* pvTheVNZObj;	  //Pointer to the CVSNZ object
	void* pvTheNotUIObj;	  //Pointer to the CNotarizationUI object 
} OPCTXT, *POPCTXT;


//This structure contains the fonts to be used
typedef struct _FONTSINFO
{
	DWORD dwCharset;	 //The character set representing the Language to be used
  	_bstr_t tbstrTitleFont;  //The title font
  	_bstr_t tbstrTextFont;	 //The text font
	_bstr_t tbstrBtnFont;	 //The button font
} FONTSINFO, *PFONTSINFO;

//This function contains the text of the buttons
typedef struct _BTNFNS
{
	LPFNBtnFn lpfnBtn1Fn;
	LPFNBtnFn lpfnBtn2Fn;
	LPFNBtnFn lpfnBtn3Fn;
	LPFNBtnFn lpfnAutoFn;
} BTNFNS, *PBTNFNS;

//This function contains the text of the buttons
typedef struct _BTNELEMS
{
	_bstr_t tbstrBtn1Text;
	_bstr_t tbstrBtn2Text;
	_bstr_t tbstrBtn3Text;
} BTNELEMS, *PBTNELEMS;


//This structure contains the UI Context. The UI Context provides
//information about the state in which the UI should be in, information
//required to render the UI for that state and the functions it needs
//to call when the buttons are clicked.
typedef struct _UICTXT
{
	void* pvReserved; //pointer to the CVSNZ Object

	PFONTSINFO pfontInfoCustomFonts;	//Object containing information about the fonts set by the app
	PFONTSINFO pfontInfoDefaultFonts;	//Object containing information about the default fonts

	PBTNFNS pbtnFns;		//Object containing the callback functions
	PBTNELEMS pbtnElems;		//Object containing the labels of the buttons
	
	_bstr_t tbstrDefLogoUrl;	//The default logo to be displayed on the dialog box
	_bstr_t tbstrCustLogoUrl;	//The app specified logo to be displayed on the dialog box

	int nWhichWizardAndUI;		//Bit Flag specifying which UI and Wizard should be shown
	int nDefLangId;			//The default language to be used

	void* pvWizardElems;		//Information required to render the current wizard
	void* pvUIElements;		//Information required to render the current ui

	
} UICTXT, *PUICTXT;


typedef struct _WIZARDELEMENTS
{
	_bstr_t tbstrWizTitle; 		//Title of the wizard
}WIZARDELEMENTS, *PWIZARDELEMENTS;


//This structure contains the elements of the
//login wizard
typedef struct _ALLWIZARDELEMENTS
{
	WIZARDELEMENTS theDefWizardElems;	//The default wizard elements
	WIZARDELEMENTS theCustWizardElems;	//The app supplied wizard elements
}ALLWIZARDELEMENTS, *PALLWIZARDELEMENTS;

//This structure contains information required to render the 
//Notarize Document/Transaction Wizard
typedef ALLWIZARDELEMENTS ALL_CREATENOTREQ_WIZARDELEMENTS ;
typedef PALLWIZARDELEMENTS PALL_CREATENOTREQ_WIZARDELEMENTS ;

//This structure contains information required to render the 
//Verify Receipt Wizard
typedef ALLWIZARDELEMENTS ALL_VERIFYRCPT_WIZARDELEMENTS ;
typedef PALLWIZARDELEMENTS PALL_VERIFYRCPT_WIZARDELEMENTS ;

//This structure contains the information required to render the 
//title and text of a dialog box.
typedef struct _UIELEMENTS
{
	_bstr_t tbstrTitle;	//Title of the dialog box
	_bstr_t tbstrText;	//Text of the dialog box
}UIELEMENTS, *PUIELEMENTS;


//This structure contains the information required to render the 
//Error handler dialog box
typedef UIELEMENTS ERROR_UIELEMENTS;
typedef PUIELEMENTS PERROR_UIELEMENTS;

typedef struct _ALL_ERROR_UIELEMENTS
{
	ERROR_UIELEMENTS theUIElements;
}ALL_ERROR_UIELEMENTS, *PALL_ERROR_UIELEMENTS;

//This structure contains the information required to render the 
//Select File dialog box
typedef UIELEMENTS SELFILE_UIELEMENTS;
typedef PUIELEMENTS PSELFILE_UIELEMENTS;

typedef struct _ALL_SELFILE_UIELEMENTS
{
	_bstr_t tbstrSelectedFile;		//The selected file
	SELFILE_UIELEMENTS theDefUIElements;	//The default UI elements
	SELFILE_UIELEMENTS theCustUIElements;	//The app specified UI elements
}ALL_SELFILE_UIELEMENTS, *PALL_SELFILE_UIELEMENTS ;

//This structure contains the information required to render the 
//Progress dialog box.
typedef UIELEMENTS PROGRESS_UIELEMENTS;
typedef PUIELEMENTS PPROGRESS_UIELEMENTS;

typedef struct _ALL_PROGRESS_UIELEMENTS
{
	int nCompletedPercent;			//The percentage of operation completed
	PROGRESS_UIELEMENTS theDefUIElements;	//The default UI elements
	PROGRESS_UIELEMENTS theCustUIElements; 	//The app specified UI elements
}ALL_PROGRESS_UIELEMENTS, *PALL_PROGRESS_UIELEMENTS;

//This structure contains the information required to render the 
//Verify Receipt dialog box.
typedef UIELEMENTS VERIFYRCPT_UIELEMENTS;
typedef PUIELEMENTS PVERIFYRCPT_UIELEMENTS;

typedef struct _ALL_VERIFYRCPT_UIELEMENTS
{
	_bstr_t tbstrWhoNotarized;		//Name of the requestor of the notarization
	//_bstr_t	tbstrNotarizedMsg;		//The message that was notarized if it is textual
	int nNotarizedDocumentType;		//The type of data (document or transaction) that was notarized
	_bstr_t tbstrNotarizedDocument;	//Name and location of the url that was notarized
	_bstr_t tbstrNotarizedDocumentTitle; // Name of the document.
	BOOL	boolShowViewDocumentLink;
	BYTE*	pbRecordData;
	DWORD	dwRecordDataLen;
	_bstr_t tbstrUserAgent;
	_bstr_t	tbstrNotary;			//The notary that created the notarization
	int nRcptVerificationResult;	//The result of verifying the receipt
	int nDocumentIntegrityResult;	//The result of checking the integrity of the notarized document
	_bstr_t tbstrDateCreated;		//The date when the notarization was created.
	_bstr_t tbstrTimeCreated;		//The time when the notarization was created.
	_bstr_t tbstrTmpHtmlFile;		//File containing data to be posted to the notarization server
	VERIFYRCPT_UIELEMENTS theDefUIElements;	//The default UI elements
	VERIFYRCPT_UIELEMENTS theCustUIElements; //The app specified UI elements
}ALL_VERIFYRCPT_UIELEMENTS, *PALL_VERIFYRCPT_UIELEMENTS;

#endif