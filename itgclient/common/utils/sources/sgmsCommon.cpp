#include "sgmsCommon.h"
#include <stdio.h>

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

			
			/*
			// Check if '\n' \r' sequence is necessary.
			if ( seventySixCount >= 76 )
			{
				seventySixCount = 0 ;
				*dwOutputSize += 2 ;
				outputPtr[0] = '\n' ;
				outputPtr[1] = '\r' ;
				outputPtr += 2 ;
			}
			*/
			
			
			
			// Ajay made changes 
			// Check if '\r' \n' sequence is necessary.
			if ( seventySixCount >= 76 )
			{
				seventySixCount = 0 ;
				*dwOutputSize += 2 ;
				outputPtr[0] = '\r' ;
				outputPtr[1] = '\n' ;
				outputPtr += 2 ;
			}
			
			

		}
	}

}

void _Base64EncodeCRLF(char* pInput,
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
		*dwOutputSize += (*dwOutputSize / 76)*2 ; // Includes '\r' '\n' after 76 chars in encoded output.
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

			
			// Check if '\r' \n' sequence is necessary.
			if ( seventySixCount >= 76 )
			{
				seventySixCount = 0 ;
				*dwOutputSize += 2 ;
				outputPtr[0] = '\r' ;
				outputPtr[1] = '\n' ;
				outputPtr += 2 ;
			}
			

		}
	}

}

void _Base64EncodeLF(char* pInput,
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
		*dwOutputSize += (*dwOutputSize / 76)*1 ; // Includes  '\n' after 76 chars in encoded output.
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

			
			// Check if  \n' sequence is necessary.
			if ( seventySixCount >= 76 )
			{
				seventySixCount = 0 ;
				*dwOutputSize += 1 ;
				outputPtr[0] = '\n' ;
				outputPtr += 1 ;
			}
			

		}
	}

}

void _Base64EncodeCR(char* pInput,
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
		*dwOutputSize += (*dwOutputSize / 76)*1 ; // Includes  '\r' after 76 chars in encoded output.
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

			
			// Check if  \r' sequence is necessary.
			if ( seventySixCount >= 76 )
			{
				seventySixCount = 0 ;
				*dwOutputSize += 1 ;
				outputPtr[0] = '\r' ;
				outputPtr += 1 ;
			}
			

		}
	}

}

void _Base64EncodeNOLF(char* pInput,
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
		//*dwOutputSize += (*dwOutputSize / 76)*1 ; // Includes  '\n' after 76 chars in encoded output.
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

			/*
			// Check if  \n' sequence is necessary.
			if ( seventySixCount >= 76 )
			{
				seventySixCount = 0 ;
				*dwOutputSize += 1 ;
				outputPtr[0] = '\n' ;
				outputPtr += 1 ;
			}
			*/
			

		}
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

void _Base64Decode(PCHAR pInput,
				   DWORD dwInputSize,
				   PCHAR pOutput,
				   DWORD * dwOutputSize)
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

BOOL _decode(short input,
			 DWORD *output)
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

void reverse(unsigned int size,
			 unsigned char *input)
{
  unsigned int	sizeby2 = size/2 ;
  char		tmpchar ;

  for (unsigned int i = 0 ; i < sizeby2 ; i++ )
  {
	  tmpchar = input[i] ;
	  input[i] = input[size-1-i] ;
	  input[size-1-i] = tmpchar ;
  }
}



///// BSAFE CRYPTO
int VSBSafeGenSessionKey(int nKeySize,
						 ITEM *i_pRCKey )
{
	int nRet;

	i_pRCKey->data = (unsigned char*)malloc(nKeySize);;
	i_pRCKey->len = nKeySize;
	nRet = GenerateRandomBlock(i_pRCKey->data, i_pRCKey->len);
	return nRet;

}

// No Support for FINAL flag - hence can't be decrypted in chunks of data.
int VSBSafeEncrypt(int i_nAlgId,
				   ITEM* i_pRCKey,
				   int i_nEffectiveKeyLen,
				   unsigned char *initVector, 
				   unsigned char *pbData,
				   unsigned int *dwDataLen,
				   unsigned int dwBufLen
				   )
{
	int nRet;
	void *o_ppvoidContext;
	unsigned int toPad ;
	unsigned int outDataSize = dwBufLen;
	unsigned char *outData;

	switch(i_nAlgId)
	{
		case SYM_RC2_CBC:
		case SYM_3DES:
			toPad = 1;
			outData = (unsigned char*)malloc(dwBufLen);

			nRet = SymEncryptDataBegin (i_nAlgId,
										i_pRCKey,
										i_nEffectiveKeyLen,
										&o_ppvoidContext,
										initVector,
										toPad);
			if(nRet != 0)
			{
				return nRet;
			}


			nRet = SymEncryptDataUpdate 
			(
			o_ppvoidContext,
			pbData, 
			*dwDataLen, 
			outData, 
			&outDataSize
			);

			if(nRet != 0)
			{
				return nRet;
			}

			memcpy(pbData, outData, outDataSize);

			*dwDataLen = outDataSize;

			nRet = SymEncryptDataEnd (o_ppvoidContext,
									outData,
									&outDataSize);

			if(nRet != 0)
			{
				return nRet;
			}

			memcpy(pbData + (*dwDataLen), outData, outDataSize);
			*dwDataLen += outDataSize;

		break;

		case SYM_RC4:
			// BUGBUG - not tested. 
			// for RC4 dwDataLen and dwBufLen is the same.
			toPad = 0;
			outData = (unsigned char*)malloc(dwBufLen);

			nRet = SymEncryptDataBegin (i_nAlgId,
										i_pRCKey,
										i_nEffectiveKeyLen,
										&o_ppvoidContext,
										initVector,
										toPad);
			if(nRet != 0)
			{
				return nRet;
			}


			nRet = SymEncryptDataUpdate 
			(
			o_ppvoidContext,
			pbData, 
			*dwDataLen, 
			outData, 
			&outDataSize
			);

			if(nRet != 0)
			{
				return nRet;
			}

			memcpy(pbData, outData, outDataSize);

			*dwDataLen = outDataSize;

			nRet = SymEncryptDataEnd (o_ppvoidContext,
									outData,
									&outDataSize);

			if(nRet != 0)
			{
				return nRet;
			}
			
			break;

		default:
			break;

	}
	if(outData)
		free(outData);

	return nRet;
		
}

int VSBSafePublicKeyEncrypt(CERT_PUBLIC_KEY_INFO *i_CertPublicKeyInfo,
							unsigned char *pbSymKey,
							unsigned int dwSymKey,
							unsigned char **pbEncData,
							unsigned int *dwEncData
							)
{
	int nRet = 0;
	A_RSA_KEY			RSA_Enc_PublicKey;
	void*				pContext;

	RSA_Enc_PublicKey.modulus.data=NULL;
	RSA_Enc_PublicKey.exponent.data=NULL;


	unsigned char *pbEncKey = NULL;
	unsigned int   dwEncKey = 0;

	nRet = GetRSAKeyFromKeyInfo(i_CertPublicKeyInfo, &RSA_Enc_PublicKey);
	if(nRet != 0)
	{
		return -1;
	}

	nRet = RSADataBegin(&RSA_Enc_PublicKey,(void**) &pContext);
	if(nRet!=0)
	{
		return -1;
	}

	unsigned char* pbPaddedData = NULL;
	unsigned long dwPaddedData;

	nRet =	PadDataForEncryption
					(
						RSA_Enc_PublicKey,
						pbSymKey,
						dwSymKey,
						&pbPaddedData,
						&dwPaddedData
					);


	
	*pbEncData = (BYTE*)malloc(dwPaddedData);
	*dwEncData =  dwPaddedData;

	
	nRet= RSADataUpdate(pContext, pbPaddedData, dwPaddedData, *pbEncData, 
					dwEncData);

	reverse(*dwEncData, *pbEncData);

	if(nRet!=0)
	{
		return -1;
	}
	nRet =	RSADataEnd(pContext);
	if(nRet!=0)
	{
		return -1;
	}

	if(pbPaddedData)
		delete(pbPaddedData);

	if(RSA_Enc_PublicKey.modulus.data)
		delete RSA_Enc_PublicKey.modulus.data;

	if(RSA_Enc_PublicKey.exponent.data)
		delete RSA_Enc_PublicKey.exponent.data;


	return nRet;
}

int GetRSAKeyFromKeyInfo(CERT_PUBLIC_KEY_INFO *i_CertPublicKeyInfo,
						 A_RSA_KEY* o_pTheKey)
{
	int retVal = 0;

	o_pTheKey->modulus.data = o_pTheKey->exponent.data = NULL;
	
	CBaseDERCollection cbdcTheKeySeq(i_CertPublicKeyInfo->PublicKey.cbData, i_CertPublicKeyInfo->PublicKey.pbData);
	CBaseDERHierarchy cbdhTheKeySeq(cbdcTheKeySeq);
	DERTree* pdtTheKeySeq = &cbdhTheKeySeq.m_DERTree;
	if(!pdtTheKeySeq && pdtTheKeySeq->currentBaseDER->Type != SEQUENCE)
	{
		retVal = -1;
	}
	else
	{
		/*Get the modulus*/
		DERTree* pdtTheMod = pdtTheKeySeq->rightDERTree;
		if(!pdtTheMod && pdtTheMod->currentBaseDER->Type != UNIVERSAL_INTEGER)
		{
			retVal = -1;
		}
		else
		{
			unsigned char* pbyteRawData;

			o_pTheKey->modulus.len = pdtTheMod->currentBaseDER->cbData;
			o_pTheKey->modulus.data = new BYTE[o_pTheKey->modulus.len];

			pbyteRawData = pdtTheMod->currentBaseDER->BaseDERBlob->pbData + 
									(pdtTheMod->currentBaseDER->BaseDERBlob->cbData - pdtTheMod->currentBaseDER->cbData);

			if(*pbyteRawData)
				memcpy(o_pTheKey->modulus.data, pbyteRawData,o_pTheKey->modulus.len);
			else if(o_pTheKey->modulus.len > 1)
			{
				o_pTheKey->modulus.len --;
				memcpy(o_pTheKey->modulus.data, pbyteRawData+1,o_pTheKey->modulus.len);
			}
			else
				retVal = -1;

		}

		/*Get the exponent*/
		DERTree* pdtTheExp;
		if(retVal == 0)
		{
			pdtTheExp = pdtTheMod->nextDERTree;
			if(!pdtTheExp && pdtTheExp->currentBaseDER->Type != UNIVERSAL_INTEGER)
			{
				retVal = -1;
			}
			else
			{
				unsigned char* pbyteRawData;

				o_pTheKey->exponent.len = pdtTheExp->currentBaseDER->cbData;
				o_pTheKey->exponent.data = new BYTE[o_pTheKey->exponent.len];

				pbyteRawData = pdtTheExp->currentBaseDER->BaseDERBlob->pbData + 
									(pdtTheExp->currentBaseDER->BaseDERBlob->cbData - pdtTheExp->currentBaseDER->cbData);
				if(*pbyteRawData)
					memcpy(o_pTheKey->exponent.data, pbyteRawData,o_pTheKey->exponent.len);
				else if(o_pTheKey->exponent.len > 1)
				{
					o_pTheKey->exponent.len --;
					memcpy(o_pTheKey->exponent.data, pbyteRawData+1,o_pTheKey->exponent.len);
				}
				else
					retVal = -1;
			}

		}
	}

	return retVal;
}


int PadDataForEncryption
(
	A_RSA_KEY			RSA_Enc_PublicKey,
	const BYTE*			i_cpbyteData,
	const DWORD			i_cdwDataLen,
	BYTE**				o_ppbytePaddedData,
	DWORD*				o_pdwPaddedDataLen
)
{
	int nRet;

	DWORD						dwBlockLength				=	0;
	DWORD						dwLengthOfPaddingRequired	=	0;
	DWORD						dwNumOfRandomBytes			=	0;

	DWORD						i, j;

	BYTE*						pbyteRandomData				=	NULL;
	DWORD						dwRandomDataLen				=	0;

	*o_ppbytePaddedData	=	NULL;

	while (1)
	{
					//	the block lenght in case of the assymetric key
					//	is basically the length of the modulus
		dwBlockLength =	(RSA_Enc_PublicKey.modulus).len;

					//	the padding required is the block length - the data length
		dwLengthOfPaddingRequired =	dwBlockLength - i_cdwDataLen;

					//	the minimum required padding is 11 bytes.
					//	so if the required padding length is less than 11 then return error
		if ( RSA_MIN_PAD_LEN > dwLengthOfPaddingRequired )
		{
			nRet = -1;
			break;
		}

			//	the padding is of the form 0x00 0x02 ... Random Data Bytes (non 0x00) ... 0x00
			//	so the number of Random bytes is required padding - 3
		dwNumOfRandomBytes =	dwLengthOfPaddingRequired - 3;

				//	 allocate memory for the padded input data
		*o_pdwPaddedDataLen =	dwBlockLength;
		*o_ppbytePaddedData =	new BYTE [*o_pdwPaddedDataLen];
		

			//	the length of the required random data is dwNumOfRandomBytes.
			//	but 0x00 is cannot be used for padding
			//	so to be on a safe side the random block generated is twice
			//	the length of dwNumOfRandomBytes and the 0x00s and the remaining block
			//	will be discarded
			//
			//	The assumption is that if more than half the bytes of an allocated random block
			//	have the value 0x00 then the random function is not exactly random.
		dwRandomDataLen =	dwNumOfRandomBytes * 2;
		pbyteRandomData =	new BYTE [dwRandomDataLen];
		
					//	generate the random block
		nRet =	GenerateRandomBlock
					(
						pbyteRandomData,
						dwRandomDataLen
					);
		if(nRet != 0)
		{
			nRet = -1;
			break;
		}

				//	0x00 0x02
		(*o_ppbytePaddedData) [0] =	0x00;
		(*o_ppbytePaddedData) [1] =	0x02;

		for ( i = 0, j = 0; i < dwNumOfRandomBytes; i++, j++ )
		{
					//	discard all the 0x00s from the random block
			while ( 0x00 == pbyteRandomData [j] )
			{
				j++;
			}

					//	copy the random data as padding
			(*o_ppbytePaddedData) [2 + i] = pbyteRandomData [j];
		}

		(*o_ppbytePaddedData) [2 + i] =	0x00;

					//	copy the original (input) data after the padding bytes
		memcpy
		(
			&((*o_ppbytePaddedData) [dwLengthOfPaddingRequired]),
			i_cpbyteData,
			i_cdwDataLen
		);

		nRet = 0;
		break;
	}	//	end		while (1)
	

	if(pbyteRandomData)
		delete pbyteRandomData;

	return	nRet;
}	



BSTR  _MultiToWideString(LPSTR szInputString)
{
	BSTR	szwcOutputString = NULL ;
	DWORD	dwSize = 0 ;

	if (szInputString == NULL)
		return NULL ;

	// Obtain size of the wide char UNICODE string.
	dwSize = MultiByteToWideChar(CP_ACP, 
								MB_COMPOSITE, 
								szInputString, 
								-1,
								NULL,
								0) ;

	// Allocate memory for the BSTR (UNICODE string).
	if ( (szwcOutputString = SysAllocStringLen(NULL, dwSize)) == NULL )
	{
		return(NULL) ;
	}

	// Copy from (and convert) Multi Byte string to Wide Char string.
	dwSize = MultiByteToWideChar(CP_ACP, 
								MB_COMPOSITE, 
								szInputString, 
								-1,
								szwcOutputString,
								dwSize) ;
	if (!dwSize)
	{
		return(NULL) ;
	}

	return szwcOutputString ;
}



/*****************************************************************************/
// _WideToMultiString() : Converts a Wide Character String to Multi Byte String.
//
//  Input :
//	  szwcInputString : BSTR
//                Contains the Wide Character string
//  Output :
//	  NONE
//  Returns : LPSTR
//				  Returns the Multi Byte String representation of the
//				  input Wide Character String.
/*****************************************************************************/

LPSTR  _WideToMultiString(BSTR szwcInputString)
{
	LPSTR	szmbOutputString = NULL ;
	DWORD	dwSize = 0 ;

	if (szwcInputString == NULL)
		return NULL ;

	// Obtain the size of the Multi Byte string representing szwcInputString.
	dwSize = WideCharToMultiByte(CP_ACP,
								WC_COMPOSITECHECK | WC_DEFAULTCHAR,
								szwcInputString,
								-1,
								NULL,
								0,
								NULL,
								NULL) ;

	// Allocate memory for the Multi Byte String.
	if ( (szmbOutputString = (LPSTR)malloc(dwSize)) == NULL )
	{
		return(NULL) ;
	}

	//memset(szmbOutputString,0,dwSize);

	// Copy from a Wide Char string to Multi Byte string.
	dwSize = WideCharToMultiByte(CP_ACP,
								WC_COMPOSITECHECK | WC_DEFAULTCHAR,
								szwcInputString,
								-1,
								szmbOutputString,
								dwSize,
								NULL,
								NULL) ;
	if (!dwSize)
	{
		return(NULL) ;
	}

	return szmbOutputString ;
}

BYTE* _WideToMultiByte(BSTR szwcInputString, DWORD *dwLength)
{
	LPSTR szmbOutputString = NULL;
	DWORD dwSize = 0;

	if(szwcInputString == NULL)
		return NULL;

	// Obtain the size of the Multi Byte string representing szwcInputString.
	dwSize = WideCharToMultiByte(CP_ACP, WC_COMPOSITECHECK | WC_DEFAULTCHAR,
								 szwcInputString, -1, NULL, 0, NULL, NULL);

	// Allocate memory for the Multi Byte String.
	if((szmbOutputString = (LPSTR)malloc(dwSize)) == NULL)
	{
		
		return NULL;
	}

	// Copy from a Wide Char string to Multi Byte string.
	dwSize = WideCharToMultiByte(CP_ACP, WC_COMPOSITECHECK | WC_DEFAULTCHAR,
								szwcInputString, -1, szmbOutputString,
								dwSize, NULL, NULL);
	if(!dwSize)
	{
		
		return NULL;
	}

	*dwLength = dwSize;

	return (BYTE*)szmbOutputString;
}

BOOL	URLEncode(PCHAR szInput, PCHAR szOutput)
{
	DWORD	dwInput = strlen(szInput) ;
	DWORD	i, j ;

	for ( j = 0, i = 0 ; i < dwInput ; i++ )
	{
		if ( szInput[i] == '\n' ||
			 szInput[i] == '\r' ||
			 szInput[i] == '\t' ||
			 szInput[i] == '\"' ||
			 szInput[i] == '\'' ||

			 //szInput[i] == ' ' ||

			 szInput[i] == ',' ||
			 szInput[i] == ';' ||
			 szInput[i] == ':' ||
			 szInput[i] == '@' ||
			 szInput[i] == '.' ||
			 szInput[i] == '\\' ||
			 szInput[i] == '|' ||
			 szInput[i] == '<' ||
			 szInput[i] == '>' ||
			 szInput[i] == '{' ||
			 szInput[i] == '}' ||
			 szInput[i] == '(' ||
			 szInput[i] == ')' ||
			 szInput[i] == '[' ||
			 szInput[i] == ']' ||
			 szInput[i] == '-' ||
			 szInput[i] == '_' ||
			 szInput[i] == '=' ||
			 szInput[i] == '+' ||
			 szInput[i] == '/' ||
			 szInput[i] == '$' ||
			 szInput[i] == '#' ||
			 szInput[i] == '`' ||
			 szInput[i] == '~' ||
			 szInput[i] == '!' ||
			 szInput[i] == '*' )
		{
			CHAR	tmp[4] ;
			itoa((int)szInput[i], tmp, 16) ;

			szOutput[j] = '%' ;

			if( strlen(tmp) == 1 )
			{
				szOutput[j+1] = '0' ;
				szOutput[j+2] = tmp[0] ;
			}
			else
			{
				memcpy(szOutput+j+1, tmp, 2) ;
			} 

			j += 3 ;
		}
		else
		{
			if(szInput[i] == ' ')
			{
				szOutput[j]='+';
			}
			else
			{
				szOutput[j] = szInput[i] ;
			}
			j++ ;

		}
	}

	szOutput[j] = '\0' ;

	return TRUE ;
}

PCHAR	URLDecode(PCHAR input)
{
	PCHAR	szDecodedString = NULL ;
	DWORD	inputIndex = 0, outputIndex = 0 ;

	szDecodedString = (PCHAR) malloc(strlen(input)+1) ;
	

	while(input[inputIndex] != NULL )
	{
		if ( input[inputIndex] != '%' )
		{
			if(input[inputIndex]=='+')
			{
				szDecodedString[outputIndex++] = ' ';
				inputIndex++;
			}
			else
			{
				szDecodedString[outputIndex++] = input[inputIndex++] ;
			}
			
		}
		else
		{

			inputIndex++ ;
			CHAR	szTmp[4], tmpChar ;
			szTmp[0] = input[inputIndex++] ;
			szTmp[1] = input[inputIndex++] ;
			szTmp[2] = '\0' ;
			sscanf(szTmp, "%x", &tmpChar) ;
			szDecodedString[outputIndex++] = tmpChar ;
		}
	}
	szDecodedString[outputIndex] = '\0' ;

/*
	if ( input )
		free (input) ;
*/
	return(szDecodedString) ;
}

PCHAR	StripSpace(PCHAR input)
{
	PCHAR	szString = NULL ;
	DWORD	inputIndex = 0, outputIndex = 0 ;

	szString = (PCHAR) malloc(strlen(input)+1) ;

	while(input[inputIndex] != NULL )
	{
		if(input[inputIndex]==' ')
		{
			inputIndex++;
		}
		else
		{
			szString[outputIndex++] = input[inputIndex++] ;
		}
		
	}
	szString[outputIndex] = '\0' ;

	return(szString) ;
}

int
AnsiToUnicodeString(
    LPSTR pAnsi,
    LPWSTR pUnicode,
    DWORD StringLength
    )
{
    int iReturn;

    if( StringLength == 0 )
        StringLength = strlen( pAnsi );

    iReturn = MultiByteToWideChar(CP_ACP,
                                  MB_PRECOMPOSED,
                                  pAnsi,
                                  StringLength + 1,
                                  pUnicode,
                                  StringLength + 1 );

    //
    // Ensure NULL termination.
    //
    pUnicode[StringLength] = 0;

    return iReturn;
}


int
UnicodeToAnsiString(
    LPWSTR pUnicode,
    LPSTR pAnsi,
    DWORD StringLength
    )
{
    LPSTR pTempBuf = NULL;
    INT   rc = 0;

    if( StringLength == 0 ) {

        //
        // StringLength is just the
        // number of characters in the string
        //
        StringLength = wcslen( pUnicode );
    }

    //
    // WideCharToMultiByte doesn't NULL terminate if we're copying
    // just part of the string, so terminate here.
    //

    pUnicode[StringLength] = 0;

    //
    // Include one for the NULL
    //
    StringLength++;

    //
    // Unfortunately, WideCharToMultiByte doesn't do conversion in place,
    // so allocate a temporary buffer, which we can then copy:
    //

    if( pAnsi == (LPSTR)pUnicode )
    {
        pTempBuf = (LPSTR)LocalAlloc( LPTR, StringLength );
        pAnsi = pTempBuf;
    }

    if( pAnsi )
    {
        rc = WideCharToMultiByte( CP_ACP,
                                  0,
                                  pUnicode,
                                  StringLength,
                                  pAnsi,
                                  StringLength,
                                  NULL,
                                  NULL );
    }

    /* If pTempBuf is non-null, we must copy the resulting string
     * so that it looks as if we did it in place:
     */
    if( pTempBuf && ( rc > 0 ) )
    {
        pAnsi = (LPSTR)pUnicode;
        strcpy( pAnsi, pTempBuf );
        LocalFree( pTempBuf );
    }

    return rc;
}


LPWSTR
AllocateUnicodeString(
    LPSTR  pAnsiString
    )
{
    LPWSTR  pUnicodeString = NULL;

    if (!pAnsiString)
        return NULL;

    pUnicodeString = (LPWSTR)LocalAlloc(
                        LPTR,
                        strlen(pAnsiString)*sizeof(WCHAR) +sizeof(WCHAR)
                        );

    if (pUnicodeString) {

        AnsiToUnicodeString(
            pAnsiString,
            pUnicodeString,
            0
            );
    }

    return pUnicodeString;
}


void
FreeUnicodeString(
    LPWSTR  pUnicodeString
    )
{
    if (!pUnicodeString)
        return;

    LocalFree(pUnicodeString);

    return;
}


void getRandomString(BYTE *pbData, int len)
{
	DWORD dwRand;
	CHAR szRand[256];
	int i = 0;
	int count = 0;
	srand( (unsigned)time( NULL ) + GetTickCount() );

	while(1)
	{
		dwRand = rand();
		itoa(dwRand,szRand,10);

		while(szRand[i])
		{
			if(count == len)
			{
				pbData[len] = '\0';
				return;
			}
			pbData[count] = szRand[i];
			i ++;
			count ++;

		}
		i = 0;
	}

}



int Hascii2Bin(PCHAR hasc, PCHAR *OutBuf, int *OutLen)
{
	int status = 0;
	PCHAR data;
	unsigned int i = 0;
	int binNum;

	do {
		*OutLen = (unsigned int)(strlen(hasc)+1)/2;
		if (*OutLen > 0) {
			data = (char *) malloc (*OutLen);
			memset(data, 0, *OutLen);
			if (data != NULL) {
				while ((int)i < *OutLen) {
					status = sscanf (&hasc[2 * i], "%2x", &binNum);
					data[i] = (char)binNum;
					i++;
				}

			} else {
				*OutLen = 0;
			}
		} else {
				*OutBuf = NULL;
		}

	} while (0);
  *OutBuf = data;
  return(status);
}





