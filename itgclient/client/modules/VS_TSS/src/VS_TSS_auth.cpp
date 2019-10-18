#include <stdio.h>
#include <windows.h>

#include "tcpa_types.h"
#include "tcpa_literals.h"
#include "spi_literals.h"
#include "spi_exports.h"

TSS_RESULT CallbackHMACAuth(PVOID			lpAppData,			// in
							TSS_HOBJECT		hAuthorizedObject,	// in
							BOOL			CalculateHMACData,	// in
							BOOL			ContinueUse,		// in
							BOOL			UseOSAP	,			// in
							UINT32			ulSizeNonces,		// in
							BYTE*			rgbNonceEven,		// in
							BYTE*			rgbNonceOdd,		// in
							BYTE*			rgbNonceEvenOSAP,	// in
							BYTE*			rgbNonceOddOSAP,	// in
							UINT32			ulSizeDigestHmac,	// in
							BYTE*			rgbParamDigest,		// in
							BYTE*			rgbHmacData)		// in, out
{
	return(0);
}

TSS_RESULT CallbackTakeOwnership(PVOID			lpAppData,		 // in
								 TSS_HOBJECT	hObject,		 // in
								 TSS_HKEY		hObjectPubKey,	 // in
								 UINT32		    ulSizeEncAuth,	 // in
								 BYTE*			rgbEncAuthOwner, // out
								 BYTE*			rgbEncAuthSrk) 	 // out
{
	return(0);
}


TSS_RESULT CallbackXorEnc(PVOID				lpAppData,	         // in
						  TSS_HOBJECT		hOSAPObject, 	     // in
						  TSS_HOBJECT		hObject, 	         // in
						  TSS_FLAGS		    PurposeSecret,	     // in 
						  UINT32			ulSizeNonces,	     // in
						  BYTE*				rgbNonceEven, 	     // in
						  BYTE*				rgbNonceOdd, 	     // in
						  BYTE*				rgbNonceEvenOSAP, 	 // in
						  BYTE*				rgbNonceOddOSAP, 	 // in
						  UINT32			ulSizeEncAuth,	     // in 
						  BYTE*				rgbEncAuthUsage,	 // out
						  BYTE*				rgbEncAuthMigration) // out
{
	return(0);
}