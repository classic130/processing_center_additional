------------------------------------------------------------------------
(C)Copyright VeriSign Inc. 1998.
Author          : Abhay Ranade
eMail           : aranade@verisign.com 
                  (Send questions/comments to this email address)
ActiveX Control : ImportPKCS12
Version         : v1.5.0.1
File            : vsimport.dll
------------------------------------------------------------------------

Description: 
-----------
It imports a PKCS#8 and an associated Certificate (chain) through a browser on a clients machine.
IT DOES NOT like a PKCS#12 at present. Although, we would eventually support a PKCS#12 import, which has
both the private key related information as well as the associated Certificate(s).

The v1.5.0.1 version of vsimport.dll imports a PKCS#8 instead of the PRIVATEKEYBLOB that it 
imported in v1.0.0.1 Both the PKCS#8 and PRIVATEKEYBLOB formats essentially store the
private key information of the end-entity certificate. Additionally, it recognizes the size
of the private/public key to use, based on the size information present in the PKCS#8 itself.
The size of the private/public key determines the Cryptographic Provider to be set for the
certificate being imported. If the bit-length of the private/public key is 512 or less, then 
the "Microsoft Base Cryptographic Provider v1.0" is used. If it is more than 512, then
then "Microsoft Base Cryptographic Provider v1.0" is used.

Version 1.5.0.1 of vsimport.dll also takes additional formal parameters through the Import method.
If the Import method fails, it now returns the error code and the corresponding error code string,
through it's formal parameters.

Assumptions :
-----------
Use IE 4.0x+ verision. It DOES NOT work with IE 3.02 at present.

ImportPKCS12 Control Properties :
-------------------------------

-------------------------------------------------------------------------
VBScript Name : KeyExportable(BOOL) 
VC++ Name : put_KeyExportable(BOOL newVal)
-------------------------------------------------------------------------
Input Parameters :
    newVal : BOOL in VB
    newVal : BOOL - in VC++
           This formal parameter can be either TRUE or FALSE
Output Parameter : 
    NONE

Returned Value :
	NONE

- This property sets the Key Exportable flag associated with the Private Key.
  If you do not want this private key to be exportable, call this property
  with "newVal" = FALSE

-------------------------------------------------------------------------
VBScript Name : BOOL KeyExportable
VC++ Name : get_KeyExportable(BOOL *pVal)
-------------------------------------------------------------------------
Input Parameters : 
    NONE

Returned Value : 
	bVal : BOOL in VB
Output Parameters :
    pVal : BOOL * - in VC++
           If the Private key is exportable, this contains TRUE, otherwise
           it contains FALSE. 
           NOTE : You MUST set this flag before you read it's value.

- This property gets the Key Exportable flag associated with the Private Key.

ImportPKCS12 Control Methods :
----------------------------

-------------------------------------------------------------------------
VBScript Name : Import(BSTR pkcs12, BSTR pkcs7, Integer status, 
					   Interger ErrorCode, BSTR ErrorCodeString)
VC++ Name : Import(VARIANT *i_pvarPKCS12, VARIANT *i_pvarPKCS7, VARIANT *o_pvarStatus, 
				   VARIANT *o_pvarErrorCode, VARIANT *o_pvarErrorCodeString)
-------------------------------------------------------------------------
Input Parameters :
    pkcs12 : BSTR - in VB
    i_pvarPKCS12 : VARIANT * - in VC++ (vt = VT_BSTR)
           This contains the Base64 Encoded PKCS#8 for the end-entity certificate.
           It essentially contains the Private Key information corresponding to the
           end-entity certificate present in the PKCS#7 chain.
           NOTE : This SHOULD NOT be PKCS12 as of now. Support for PKCS12 will be
                  added in the future.

    pkcs7 : in VB 
    i_pvarPKCS7 : VARIANT * - in VC++ (vt = VT_BSTR)
           This contains the Base64 Encoded Signed PKCS#7. The PKCS#7 is assumed
           to have been digitally signed by the CA who is issuing the certificate.
           Moreover, it can contain ALL the certificates of the higher CA, which
           chain up to the top level ROOT CA. 
           NOTE : The order of certificates in the PKCS#7 is assumed to be such that
		  the first certificate in the PKCS#7 is the end-entity certificate.
		  This end-entity certificate is assumed to be followed by the
		  intermediate certificate(s) that lead to the Top Level ROOT CA.
		  The Root CA certificate need not be there in this PKCS#7 chain.

Outout Parameters :
	fStatus : BOOL in VB
	o_pvarStatus : VARIANT * - in VC++ (vt = VT_BOOL)
		   This returns the success status of the Import method. If the Import method
		   succeeds without any errors, then it contains TRUE, otherwise, it contains
		   FALSE.

	ErrorCode : Integer in VB
	o_pvarErrorCode : VARIANT * - in VC++ (vt = VT_I4)
		   If fStatus/o_pvarStatus->boolVal is TRUE, then ErrorCode/o_pvarErrorCode->lVal
		   value is indeterminate.
		   If fStatus/o_pvarStatus->boolVal is FALSE, then ErrorCode/o_pvarErrorCode->lVal
		   value contains the error code

	ErrorCodeString : String in VB
	o_pvarErrorCode : VARIANT * - in VC++ (vt = VT_BSTR)
		   If fStatus/o_pvarStatus->boolVal is TRUE, then ErrorCodeString/o_pvarErrorCode->bstrVal
		   value is indeterminate.
		   If fStatus/o_pvarStatus->boolVal is FALSE, then ErrorCodeString/o_pvarErrorCode->bstrVal
		   value contains the string representation of the error code

Returned value : 
	NONE
                                      
- This method actually performs the job of importing a PKCS#8 and it's associated
  signed PKCS#7. The PKCS#8 is first converted to a PRIVATEKEYBLOB format.
  The PRIVATEKEYBLOB is then stored in a NEW Key Container. The end-entity certificate
  is added in the MY certificate store (that is visible to IE and OutLook). The intermediate
  CA certificates are stored in the CA Certificate store. When you SIGN a message using the
  end-entity certificate, ALL the intermediate CA certificates associated with the end-entity
  certificate are sent (ROOT CA Cert is NOT sent).

  NOTE : The exact format of PKCS#8 is available on www.rsa.com.
         The exact format of PRIVATEKEYBLOB is specified on MSDN online.

Examples : 
--------
The file testImportPKCS12.html can be used to import a TEST Key container and an associated
certificate chain. It also contains the VBScript calls to complete the import operation.
NOTE : The KeyBlob variable in the VBScript example contains a LIVE PRIVATE KEY BLOB kept in 
       PKCS#8 format.
       DO NOT DISTIBUTE THIS HTML FILE TO ANYONE WHOM YOU DON'T TRUST !!!!

Enjoy !

In case of any problems, send email to aranade@verisign.com
