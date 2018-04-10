#include "stdafx.h"
#include "..\Include\MyUniversalInteger.h"

CMyUniversalInteger::CMyUniversalInteger(_DWORD i_cbData, _PBYTE i_pbData)
{
	_DWORD i_cbTmpData;
	_PBYTE i_pbTmpData;
	bool boolAddPad = false;

	
	if(i_pbData[0] & 0x80)
	{
		i_cbTmpData = i_cbData +1;
		i_pbTmpData = (_PBYTE)malloc(sizeof(_BYTE) * (i_cbTmpData));
		i_pbTmpData[0] = 0x00;
		memcpy(i_pbTmpData+1,i_pbData,i_cbTmpData-1);
		boolAddPad = true;
	}
	else
	{
		i_pbTmpData = i_pbData;
		i_cbTmpData = i_cbData;
	}

	this->fillit(UNIVERSAL_INTEGER, i_cbTmpData, i_pbTmpData) ;
	this->encode2() ;
	if(boolAddPad)
		free(i_pbTmpData);
}


CMyUniversalInteger::CMyUniversalInteger(_DWORD i_dwData)
{
	_DWORD i_cbData;
	_PBYTE i_pbData;
	_DWORD i_cbTmpData;
	_PBYTE i_pbTmpData;
	bool boolAddPad = false;


	BYTE	byteData[4];

	i_pbData = (BYTE*) &i_dwData;
	i_cbData = 4;

	for (int i = 0; i < 4; i++ )
	{
		if (0x00 == i_pbData[3-i])
		{
			i_cbData --;
		}
		else
		{
			break;
		}
	}

	for (int j = 0; j < i_cbData; j++)
	{
		byteData[j] = i_pbData [i_cbData - 1 - j];
	}

	if ( 0 == i_cbData )
	{
		i_cbData ++;
		byteData [0] = 0x00;
	}

	if(byteData[0] & 0x80)
	{
		i_cbTmpData = i_cbData +1;
		i_pbTmpData = (_PBYTE)malloc(sizeof(_BYTE) * (i_cbTmpData));
		i_pbTmpData[0] = 0x00;
		memcpy(i_pbTmpData+1,byteData,i_cbTmpData-1);
		boolAddPad = true;
	}
	else
	{
		i_pbTmpData = byteData;
		i_cbTmpData = i_cbData;
	}

	this->fillit(UNIVERSAL_INTEGER, i_cbTmpData, i_pbTmpData) ;
	this->encode2() ;
	if(boolAddPad)
		free(i_pbTmpData);
}
