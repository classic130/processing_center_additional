#include "stdafx.h"
#include "..\include\csputil.h"

BOOL	_decode(short input, DWORD *output);

void _Base64Encode(PCHAR pInput, DWORD dwInputSize, PCHAR pOutput, DWORD * dwOutputSize)
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
		DWORD		remainingSize, seventySixCount ;
		PCHAR		inputPtr, outputPtr ;

		remainingSize = dwInputSize ;
		inputPtr = pInput ;
		outputPtr = pOutput ;
		*dwOutputSize = 0 ;
		seventySixCount = 0 ;

		while((int)remainingSize > 0)
		{
			if (remainingSize == 1)
			{
				DWORD tmp ;
				tmp = 0x000000FF & inputPtr[0] ;
				tmp = tmp << 16 ;

				outputPtr[0] = _encode[((tmp & 0x00FC0000) >> 18)] ;
				outputPtr[1] = _encode[((tmp & 0x0003F000) >> 12)] ;
				outputPtr[2] = '=' ;
				outputPtr[3] = '=' ;
			}
			else if(remainingSize == 2)
			{
				DWORD tmp ;
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
				DWORD tmp ;
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

		EraseMemory ( (unsigned int) dwInputSize, (unsigned char*) filteredInputPtr );
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

		EraseMemory ( (unsigned int) dwInputSize, (unsigned char*) filteredInputPtr );
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
