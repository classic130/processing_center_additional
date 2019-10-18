#ifndef _VS_VSSC_ERRS_
#define _VS_VSSC_ERRS_

//
// VSSC APP error returns
//
#define E_VSSC_INITIALIZED				0x80003001
#define E_VSSC_EMPTYARGS				0x80003002
#define E_VSSC_INVALIDARGS				0x80003003
#define E_VSSC_INVALIDNODE				0x80003004
#define E_VSSC_INVALID_MODE				0x80003005 


#define E_DIFERENT_PTAVER				0x80003006
#define E_NOSUPPORTED_PTAVER			0x80003007


#define E_REGOPEN_KEY					0x80003008 
#define E_REGQUERY_KEY					0x80003009 

#define E_WININET_ERR					0x8000300A

#define E_INETOPEN_ERR					0x8000300B
#define E_INETCONNECT_ERR				0x8000300C
#define E_INETOPENREQ_ERR				0x8000300D
#define E_INETCERT_CN_INVALID			0x8000300E
#define E_INETINVALID_CA				0x8000300F
#define E_INETCERT_DATE_INVALID			0x80003010
#define E_INETQUERY_DATA_ERR			0x80003011
#define E_INETREAD_DATA_ERR				0x80003012

#define E_INETSTATUS_PROXY_AUTH_REQ		0x80003013
#define E_INETSTATUS_SERVER_AUTH_REQ	0x80003014
#define E_INETSTATUS_BAD_REQUEST		0x80003015 //400 The request could not be processed by
												   //the server due to invalid syntax.

#define E_INETSTATUS_NOT_FOUND			0x80003016 //404 The server has not found anything matching 
												   //the requested URI (Uniform Resource Identifier).

#define E_INETSTATUS_SERVER_ERROR       0x80003017  //500 The server encountered an unexpected 
												   //condition that prevented it from fulfilling the request    

#define E_NETSTATUS_STATUS_BAD_METHOD   0x80003018  //405 The method used is not allowed.


#define E_CERTRESOLVEURL_NOTFOUND		0x80003019
#define E_SCTYPE_NOTFOUND				0x8000301A 
#define E_INVALID_CERTREQDATA			0x8000301B
#define E_INVALID_CERTRESPONSEDATA		0x8000301C

	
#define E_FIRSTNOT_CALLED			 	0x8000301D
#define E_EMPTYEMAILLIST 				0x8000301E


#define E_SIGNER_CERTNOTFOUND			0x8000301F
#define E_ENCRYPT_CERTNOTFOUND			0x80003020
#define E_SENDERINFO_NOTFOUND			0x80003021 



#define E_SIGNER_CERT_REVOKED			0x80003022   
#define E_SIGNER_CERT_EXPIRED			0x80003023   
#define E_ENCRYPT_CERT_EXPIRED			0x80003024   
#define E_ENCRYPT_CERT_REVOKED			0x80003025  


#define E_FILE_EXIST					0x80003026  

#define E_BSAFE_KEYGEN_FAILED			0x80003027   
#define E_BSAFE_ENCRYPT_FAILED			0x80003028   
#define E_BSAFE_PUB_ENCRYPT_FAILED		0x80003029 
  
#define E_HASH_BEGIN_FAILED				0x8000302A   
#define E_HASH_DATA_FAILED				0x8000302B   
#define E_HASH_END_FAILED				0x8000302C   

#define E_PKCS_AA_ERR					0x8000302D
#define E_CREATE_PKCS7_FAILED			0x8000302E 
#define E_CREATE_ENVELOP_DATA_FAILED	0x8000302F




/////decompose
#define E_PARSEMIME_FAILED				0x80003031   
#define E_INVALID_MIME                  0x80003032   
#define E_PARSE_SIGNEDMSG_FAILED		0x80003033   
#define E_PARSEPKCS7_FAILED				0x80003034   
#define E_INVALID_PKCS7					0x80003035   

#define E_NO_HASH_ALGID					0x80003036   
#define E_NO_ENCRYPT_ALGID              0x80003037   
#define E_DECRYPTION_NOT_ALLOWED        0x80003038   

#define E_SYM_DECRYPT_BEGIN_FAILED		0x80003039   
#define E_SYM_DECRYPT_DATA_FAILED		0x8000303A   
#define E_SYM_DECRYPT_END_FAILED		0x8000303B   

#define E_RSA_DATA_BEGIN_FAILED			0x8000303C   
#define E_RSA_DATA_UPDATE_FAILED		0x8000303D   
#define E_RSA_DATA_END_FAILED			0x8000303E   


#define E_AUTH_MSG_DIGEST_FAILED        0x8000303F   
#define E_HASHNOT_MATCHED				0x80003040   

#define E_CERT_PARSEING_FAILED			0x80003041   
#define E_UNKNOWN_PKCS7_TYPE			0x80003042  
#define E_CERT_NOT_MATCH				0x80003043   
 

#define E_BASE64_DECODE_FAILED          0x80003044
   


#define E_PRC_CERTNOTFOUND				0x80003045
#define E_PRC_REVOKED					0x80003046
#define E_PRC_EXPIRED					0x80003047 
#define E_PRC_NOTALLOWED				0x80003048

////APP Related ERROR
#define E_UNABLE_TOFIND_PTAVER			0x80003049
#define E_REVOKED_OR_EXPIED_CERT		0x8000304A

#define E_UNABLE_TODO_CERTRESOLVE		0x8000304B
#define E_UNABLE_RESOLVE_PRC		    0x8000304C

#define E_UNABLE_TODO_SIGN_ERR			0x8000304D 
#define E_UNABLE_TO_CONSTRUCT_MSG		0x8000304E

#define E_UNABLE_TODO_VERIFICATION_ERR	0x8000304F
#define E_UNABLE_TO_SELECT_CERT			0x80003050
#define E_UNABLE_TODO_DECRYPTION_ERR	0x80003051
#define E_UNABLE_VIEW_ERR				0x80003052
#define E_UNABLE_TO_INIT				0x80003054
#define E_UNABLE_TO_ATTACH				0x80003055



#define E_HOST_NOT_MATCH				0x80003056

  

#endif