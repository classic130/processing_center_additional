///////////////misc.cpp

#include "vssc_global.h"

#define PESTUBCFG             "pestub.cfg"

PESTUBINFO    g_pInfo;

 bool PestubInit()
{
	FILE *stream=NULL;
	char szName[1024],szValue[1024];

	if((stream = fopen(PESTUBCFG, "r")) != NULL)
	{	
		while(!feof(stream))
		{
			fscanf(stream, "%s	%s\n", szName, szValue);
			if(strcmp(szName,"END") == 0)
				break;
			InitiliazeInfo(szName, szValue);

		}
	}
	else
	{
		return false;
	}

	if(stream!=NULL)
		fclose(stream);
	
	return true;

}

void InitiliazeInfo(char *szName,
					  char *szValue)
{

	if(strcmp(szName,"SMTPSERVER") == 0)
	{
		strcpy(g_pInfo.szSMTPServerName,szValue);
	}
	else if(strcmp(szName, "USERSMIMECERT") == 0)
	{
		
		g_pInfo.UserSMIMECert=atoi(szValue);
	}
	else if(strcmp(szName, "REVOCATIONTYPE") == 0)
	{
		g_pInfo.RevocationType=atoi(szValue);
	}
	else if(strcmp(szName, "REVOCATIONSTATUS") == 0)
	{
		g_pInfo.RevocationStatus=atoi(szValue);
	}
	else if(strcmp(szName, "CHAINVALIDATETYPE") == 0)
	{
		g_pInfo.ChainValidateType=atoi(szValue);
	}
	else if(strcmp(szName, "CHAINVALIDATESTATUS") == 0)
	{
		g_pInfo.ChainValidateStatus=atoi(szValue);
	}
	
		
}

/*****************************************************************************/
// _Base64Decode() : Decodes a message that is in Base64 format. 
//
//				    Implements RFC 1521 - 5.2 Base64 Content-Transfer Decoding.
//
//  Input :
//	  pInput : PCHAR
//                Contains the input message that is the be decoded.
//	  dwInputSize : DWORD
//				  Specifies the size of the input message.
//  Input/Output :
//	  pOutput : PCHAR
//                Specifies the address where the decoded message is to be copied.
//
//				  If it is specified as NULL, then the output formal parameter, dwOutputSize,
//				  specifies the size of the decoded message, corresponding to the 
//				  input message specified through the formal parameter pInput.
//  Input/Output :
//	  dwOutputSize : DWORD *
//				  Specifies the size of the output decoded message.
//  Returns :
//    NONE
/*****************************************************************************/

void _Base64Decode(PCHAR pInput, DWORD dwInputSize, PCHAR pOutput, DWORD * dwOutputSize)
{
	if ( pOutput == NULL )
	{
		PCHAR	filteredInputPtr ;
		int		i, filteredCounter = 0 ;

		filteredInputPtr = (PCHAR) malloc(dwInputSize) ;
		for ( i = 0 ; i < (int)dwInputSize ; i++ )
		{
			DWORD	tmp ;
			if (_decode(pInput[i], &tmp))
			{
				filteredInputPtr[filteredCounter] = pInput[i] ;
				filteredCounter++ ;
			}
		}

		*dwOutputSize = filteredCounter ;
		*dwOutputSize = (*dwOutputSize/4)*3 ;

		free(filteredInputPtr) ;
	}
	else
	{
		DWORD		remainingSize ;
		PCHAR		inputPtr, outputPtr, filteredInputPtr ;
		int			i, filteredCounter = 0 ;

		filteredInputPtr = (PCHAR) malloc(dwInputSize) ;
		for ( i = 0 ; i < (int)dwInputSize ; i++ )
		{
			DWORD	tmp ;
			if (_decode(pInput[i], &tmp))
			{
				filteredInputPtr[filteredCounter] = pInput[i] ;
				filteredCounter++ ;
			}
		}

		// remainingSize = dwInputSize ;
		remainingSize = filteredCounter ;
		inputPtr = filteredInputPtr ;
		outputPtr = pOutput ;
		*dwOutputSize = 0 ;

		while((int)remainingSize > 0)
		{
			DWORD tmp, tmpout ;

			_decode(inputPtr[0], &tmpout) ;
			tmp = tmpout ;

			_decode(inputPtr[1], &tmpout) ;
			tmp = tmp << 6 ;
			tmp |= tmpout ;

			_decode(inputPtr[2], &tmpout) ;
			tmp = tmp << 6 ;
			tmp |= tmpout ;
				
			_decode(inputPtr[3], &tmpout) ;
			tmp = tmp << 6 ;
			tmp |= tmpout ;

			if ( inputPtr[2] == '=' && inputPtr[3] == '=' )
			{
				outputPtr[0] = (char)((tmp & 0x00FF0000) >> 16) ;
				*dwOutputSize += 1 ;
			}
			else if ( inputPtr[3] == '=' )
			{
				outputPtr[0] = (char)((tmp & 0x00FF0000) >> 16) ;
				outputPtr[1] = (char)((tmp & 0x0000FF00) >> 8) ;
				*dwOutputSize += 2 ;
			}
			else
			{
				outputPtr[0] = (char)((tmp & 0x00FF0000) >> 16) ;
				outputPtr[1] = (char)((tmp & 0x0000FF00) >> 8) ;
				outputPtr[2] = (char)((tmp & 0x000000FF)) ;
				*dwOutputSize += 3 ;
			}

			remainingSize -= 4 ;
			inputPtr += 4 ;
			outputPtr += 3 ;
		}

		free(filteredInputPtr) ;
	}
}


BOOL	_decode(short input, DWORD *output)
{
	if ( input >= 'A' && input <= 'Z' )
	{
		*output = input - 'A' ;
		return TRUE ;
	}
	else if ( input >= 'a' && input <= 'z' )
	{
		*output = input - 'a' + 26 ;
		return TRUE ;
	}
	else if ( input >= '1' && input <= '9' )
	{
		*output = input - '1' + 26 + 27 ;
		return TRUE ;
	}
	else if ( input == '0' )
	{
		*output = 26 + 26 ;
		return TRUE ;
	}
	else if ( input == '+' )
	{
		*output = 62 ;
		return TRUE ;
	}
	else if (input == '/' )
	{
		*output = 63 ;
		return TRUE ;
	}
	else if (input == '=' )
	{
		*output = 0 ;
		return TRUE ;
	}
	else
	{
		*output = 0 ;
		return FALSE ;
	}
}




void _Base64Encode(char* pInput,
				   unsigned int dwInputSize,
				   char* pOutput,
				   unsigned int * dwOutputSize)
{
	char _encode[64] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
					'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
				    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
				    'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/'} ;


	if ( pOutput == NULL )
	{
		*dwOutputSize = !(dwInputSize % 3) ? (dwInputSize/3)*4 : ((dwInputSize/3)*4) + 4 ;
		*dwOutputSize += (*dwOutputSize / 76)*2 ; // Includes '\n' '\r' after 76 chars in encoded output.
	}
	else
	{
		unsigned int		remainingSize, seventySixCount ;
		char		*inputPtr, *outputPtr ;

		remainingSize = dwInputSize ;
		inputPtr = pInput ;
		outputPtr = pOutput ;
		*dwOutputSize = 0 ;
		seventySixCount = 0 ;

		while((int)remainingSize > 0)
		{
			if (remainingSize == 1)
			{
				unsigned int tmp ;
				tmp = 0x000000FF & inputPtr[0] ;
				tmp = tmp << 16 ;

				outputPtr[0] = _encode[((tmp & 0x00FC0000) >> 18)] ;
				outputPtr[1] = _encode[((tmp & 0x0003F000) >> 12)] ;
				outputPtr[2] = '=' ;
				outputPtr[3] = '=' ;
			}
			else if(remainingSize == 2)
			{
				unsigned int tmp ;
				tmp = 0x000000FF & inputPtr[0] ;
				tmp = tmp << 8 ;
				tmp |= 0x000000FF & inputPtr[1] ;
				tmp = tmp << 8 ;

				outputPtr[0] = _encode[((tmp & 0x00FC0000) >> 18)] ;
				outputPtr[1] = _encode[((tmp & 0x0003F000) >> 12)] ;
				outputPtr[2] = _encode[((tmp & 0x00000FC0) >> 6)] ;
				outputPtr[3] = '=' ;
			}
			else
			{
				unsigned int tmp ;
				tmp = 0x000000FF & inputPtr[0] ;
				tmp = tmp << 8 ;
				tmp |= 0x000000FF & inputPtr[1] ;
				tmp = tmp << 8 ;
				tmp |= 0x000000FF & inputPtr[2] ;

				outputPtr[0] = _encode[((tmp & 0x00FC0000) >> 18)] ;
				outputPtr[1] = _encode[((tmp & 0x0003F000) >> 12)] ;
				outputPtr[2] = _encode[((tmp & 0x00000FC0) >> 6)] ;
				outputPtr[3] = _encode[(tmp & 0x0000003F)] ;
			}
			*dwOutputSize += 4 ;
			seventySixCount += 4 ;
			remainingSize -= 3 ;
			inputPtr += 3 ;
			outputPtr += 4 ;

			// Check if '\n' \r' sequence is necessary.
			if ( seventySixCount >= 76 )
			{
				seventySixCount = 0 ;
				*dwOutputSize += 2 ;
				outputPtr[0] = '\n' ;
				outputPtr[1] = '\r' ;
				outputPtr += 2 ;
			}
		}
	}

}





VSAA_STATUS Test(VSAA_NAME anInput[], VSAA_NAME **panOutput)
{
	int     	fh;
	char		buffer[8026];


    strcpy(buffer,"");
	
	fh = _open("c:\\postVar.txt", _O_RDWR | _O_CREAT,_S_IREAD | _S_IWRITE ); 
	
	sprintf(buffer,"Name=%s   Value=%s\n",anInput[0].pszName,anInput[0].pszValue);
    _write(fh,buffer,strlen(buffer));

	sprintf(buffer,"Name=%s   Value=%s\n",anInput[1].pszName,anInput[1].pszValue);
    _write(fh,buffer,strlen(buffer));
	
	sprintf(buffer,"Name=%s   Value=%s\n",anInput[2].pszName,anInput[2].pszValue);
    _write(fh,buffer,strlen(buffer));
	
	sprintf(buffer,"Name=%s   Value=%s\n",anInput[3].pszName,anInput[3].pszValue);
    _write(fh,buffer,strlen(buffer));
	
	_close(fh);
/*	
	if (*panOutput == NULL)
	{
		*panOutput = (VSAA_NAME *)calloc(5, sizeof(VSAA_NAME));
	}

	(*panOutput)[0].pszName = (char *)calloc(1, 15 + 1);
	(*panOutput)[0].pszValue = (char *)calloc(1, 15 + 1);

	memcpy((*panOutput)[0].pszName, "FirstName", strlen("FirstName"));
	memcpy((*panOutput)[0].pszValue, "Narinder", strlen("Narinder"));

	(*panOutput)[1].pszName = (char *)calloc(1, 15 + 1);
	(*panOutput)[1].pszValue = (char *)calloc(1, 15 + 1);

	memcpy((*panOutput)[1].pszName, "LastName", strlen("LastName"));
	memcpy((*panOutput)[1].pszValue, "Paul", strlen("Paul"));

	(*panOutput)[2].pszName = (char *)calloc(1, 15 + 1);
	(*panOutput)[2].pszValue = (char *)calloc(1, 25 + 1);

	memcpy((*panOutput)[2].pszName, "Email", strlen("Email"));
	memcpy((*panOutput)[2].pszValue, "npaul@verisign.com", strlen("npaul@verisign.com"));

  */

	(*panOutput)[3].pszName = NULL;
	(*panOutput)[3].pszValue =NULL;

	return VSAA_SUCCESS;

}

void debugInfo(char * buf)
{
	FILE   * fp;

	fp=fopen("debug.txt","a+");
	fwrite(buf,strlen(buf),1,fp);
	fclose(fp);

}
