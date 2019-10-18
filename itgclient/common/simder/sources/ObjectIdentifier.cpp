// ObjectIdentifier.cpp: implementation of the CObjectIdentifier class.
//
//////////////////////////////////////////////////////////////////////

#include "ObjectIdentifier.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CObjectIdentifier::CObjectIdentifier()
{
	cbData = 0x00000000 ;
	pbData = _NULL ;
	NumberOfLengthBytes = 0x00000000 ;
	Type = INVALID_DER_TYPE ;
}

CObjectIdentifier::~CObjectIdentifier()
{
	if ( pbData )
		(*SIMDER_MemErase)(cbData, pbData) ;

	if ( pbData )
	{
		free (pbData) ;
		cbData = 0x00000000 ;
		pbData = _NULL;
	}
	NumberOfLengthBytes = 0x00000000 ;
	Type = INVALID_DER_TYPE ;
}

CObjectIdentifier::CObjectIdentifier(CObjectIdentifier &cobjectidentifier)
{
	copyinfo(OBJECT_IDENTIFIER, cobjectidentifier) ;
}

_BOOL	valid(_DWORD i_cbData, _PBYTE i_pbData)
{
  for ( _DWORD i = 0 ; i < i_cbData ; i++ )
  {
	  if ( i_pbData[i] >= '0' && i_pbData[i] <= '9' )
		  continue ;
	  else if ( i_pbData[i] == '.' )
		  continue ;
	  else
		  return _FALSE ;
  }

  return _TRUE ;
}

#define	MAX_OBJ_IDS				100
#define	MAX_OBJ_ID_COMP_LENGTH	100

_DWORD	getObjIdComp(_PCHAR input, _PCHAR output)
{
	_DWORD i = 0 ; 
	while(i < MAX_OBJ_ID_COMP_LENGTH)
	{
		if ( input[i] >= '0' && input[i] <= '9' )
			output[i] = input[i] ;
		else if ( input[i] == '.' || input[i] == '\0' )
			return i ;
		else
			return 0 ;
		i++ ;
	}

	return 0 ;
}

_DWORD	CObjectIdentifier::EncodeSubId(_DWORD dwSubId, _PBYTE pbSubEncodedSubId)
{
	_BYTE	bFlag = _FALSE ;
	_BYTE	byteSubIdChunk = 0 ;
	_BYTE	i = 0 ;
	_BYTE	tmpSubEncodedSubId[4] ;

	while(i < 4)
	{
		byteSubIdChunk = dwSubId & 0x0000007F ;
		if ( bFlag == _FALSE )
		{
			tmpSubEncodedSubId[i] = byteSubIdChunk ;
			bFlag = _TRUE ;
		}
		else
			tmpSubEncodedSubId[i] = 0x80 | byteSubIdChunk ;
		dwSubId = dwSubId >> 7 ;			
		i++ ;
		if ( dwSubId == 0 )
			break ;
	}

	memcpy(pbSubEncodedSubId, tmpSubEncodedSubId, i) ;

	return i ;
}

_DWORD	CObjectIdentifier::getSubId(_PCHAR szObjIdComp, _PBYTE subid)
{
	_DWORD	dwSubId = 0, dwEncodedSubId = 0, dwSubIdBytes = 0 ;
	_DWORD	i, dwObjIdComp = strlen((const char *)szObjIdComp) ;

	for ( i = 0 ; i < dwObjIdComp ; i++ )
		dwSubId += (_DWORD)(szObjIdComp[dwObjIdComp-1-i] - '0') * (_DWORD)ceil((pow(10.0, (double)i))) ;

	dwSubIdBytes = EncodeSubId(dwSubId, (_PCHAR)&dwEncodedSubId) ;

	memcpy(subid, &dwEncodedSubId, dwSubIdBytes) ;

	return dwSubIdBytes ;
}

_DWORD	CObjectIdentifier::getSubId1(_PCHAR szObjIdComp, _PBYTE subid)
{
	_DWORD	dwSubId = 0, dwEncodedSubId = 0, dwSubIdBytes = 0 ;
	_DWORD	i, dwObjIdComp = strlen((const char *)szObjIdComp) ;

	for ( i = 0 ; i < dwObjIdComp ; i++ )
		dwSubId += (_DWORD)(szObjIdComp[dwObjIdComp-1-i] - '0') * (_DWORD)ceil((pow(10.0, (double)i))) ;

	dwSubId *= 40 ;
	dwSubIdBytes = EncodeSubId(dwSubId, (_PCHAR)&dwEncodedSubId) ;

	memcpy(subid, &dwEncodedSubId, dwSubIdBytes) ;

	return dwSubIdBytes ;
}

_DWORD	CObjectIdentifier::getSubId2(_PCHAR szObjIdComp1, _PCHAR szObjIdComp2, _PBYTE subid)
{
	_DWORD	dwSubId = 0, dwSubId1 = 0,dwSubId2 = 0 ;
	_DWORD  dwEncodedSubId = 0, dwSubIdBytes = 0, i ;
	_DWORD	dwObjIdComp1 = strlen((const char *)szObjIdComp1) ;
	_DWORD	dwObjIdComp2 = strlen((const char *)szObjIdComp2) ;

	for ( i = 0 ; i < dwObjIdComp1 ; i++ )
		dwSubId1 += (_DWORD)(szObjIdComp1[dwObjIdComp1-1-i] - '0') * (_DWORD)ceil((pow(10.0, (double)i))) ;

	for ( i = 0 ; i < dwObjIdComp2 ; i++ )
		dwSubId2 += (_DWORD)(szObjIdComp2[dwObjIdComp2-1-i] - '0') * (_DWORD)ceil((pow(10.0, (double)i))) ;

	dwSubId = dwSubId1*40 + dwSubId2 ;
	dwSubIdBytes = EncodeSubId(dwSubId, (_PCHAR)&dwEncodedSubId) ;

	memcpy(subid, &dwEncodedSubId, dwSubIdBytes) ;

	return dwSubIdBytes ;
}

CObjectIdentifier::CObjectIdentifier(_DWORD i_cbData, _PBYTE i_pbNoNULLData)
{
	_CHAR		obj_id_comp[MAX_OBJ_IDS][MAX_OBJ_ID_COMP_LENGTH] ;
	_PCHAR		i_pbData = NULL ;

	i_pbData = (_PBYTE) malloc(i_cbData+1) ;
	memcpy(i_pbData, i_pbNoNULLData, i_cbData) ;
	i_pbData[i_cbData] = '\0' ;

	if ( !valid(i_cbData, i_pbData) )
		return ;

	_DWORD i = 0, obj_id_comp_index = 0, obj_id_comp_length = 0 ;
	_DWORD		dwObjIdComp = 0 ;
	while(i < i_cbData)
	{
		if ( (obj_id_comp_length = getObjIdComp(i_pbData+i, &obj_id_comp[obj_id_comp_index][0])) == 0 )
			return ;
		if ( obj_id_comp_length > MAX_OBJ_ID_COMP_LENGTH )
			return ;
		obj_id_comp[obj_id_comp_index][obj_id_comp_length] = '\0' ;
		i += obj_id_comp_length + 1 ;
		obj_id_comp_index++ ;
		if ( obj_id_comp_index > MAX_OBJ_IDS )
			return ;
	} ;
	dwObjIdComp = obj_id_comp_index ;

	_BYTE		pbSubIds[1024], *pbPtrSubIds ;
	_DWORD		cbSubIds = 0, cbSubId = 0 ;

	pbPtrSubIds = pbSubIds ;
	obj_id_comp_index = 0 ;

	if ( dwObjIdComp == 0 )
		return ;
	else if ( dwObjIdComp == 1 )
	{
		if ( (cbSubId = getSubId1(obj_id_comp[0], pbPtrSubIds)) == 0 )
			return ;
		cbSubIds += cbSubId ;
		obj_id_comp_index++ ;
	}
	else
	{
		while( obj_id_comp_index < (dwObjIdComp-2) )
		{
			if ( (cbSubId = getSubId(obj_id_comp[dwObjIdComp - 1 - obj_id_comp_index], pbPtrSubIds)) == 0 )
				return ;
			pbPtrSubIds += cbSubId ;
			cbSubIds += cbSubId ;
			obj_id_comp_index++ ;
		}

		if ( (cbSubId = getSubId2(obj_id_comp[0], obj_id_comp[1], pbPtrSubIds)) == 0 )
			return ;
		pbPtrSubIds += cbSubId ;
		cbSubIds += cbSubId ;
		obj_id_comp_index += 2 ;
	}

	this->fillit(OBJECT_IDENTIFIER, cbSubIds, pbSubIds) ;
	this->encode() ;
}

CObjectIdentifier CObjectIdentifier::operator=(CObjectIdentifier &cobjectidentifier)
{
	if (BaseDERBlob)
		if (BaseDERBlob->cbData != 0x00000000)
			delete (BaseDERBlob) ;
	if ( pbData )
		free(pbData) ;
	cbData = 0 ;

	copyinfo(OBJECT_IDENTIFIER, cobjectidentifier) ;

	return *this ;
}

void CObjectIdentifier::decode()
{
	_DWORD		dwInsideDERBlobLength, dwContentLengthBytes ;

	if ( BaseDERBlob != _NULL )
	{
		Type = BaseDERBlob->pbData[0] ;
		if ( (Type & 0x1F) == OBJECT_IDENTIFIER )
		{
			GetLengthInfo(BaseDERBlob, &dwInsideDERBlobLength, &dwContentLengthBytes) ;

			if ( dwInsideDERBlobLength == 0 || ((dwInsideDERBlobLength+1+dwContentLengthBytes) > BaseDERBlob->cbData) )
			{
				// You have got invalid InsideDERBlob length. So don't bother to decode.
				dwErrorCode = 0xFFFFFFFF ;
				return ;
			}

			NumberOfLengthBytes = dwContentLengthBytes ;

			if (pbData)
				free(pbData) ;

			_PCHAR	EncodedBlobPtr ;
			_DWORD	dwEncodedBlobIndex ;
			_BOOL	bFirstTime = _TRUE ;

			EncodedBlobPtr = BaseDERBlob->pbData + 1+dwContentLengthBytes ;
			dwEncodedBlobIndex = 0 ;
			while ( dwEncodedBlobIndex < dwInsideDERBlobLength )
			{
				_DWORD	dwBytesInSubID = 1 ;
				while ( EncodedBlobPtr[dwBytesInSubID-1] & 0x80 )
					dwBytesInSubID++ ;
				if ( bFirstTime )
				{
					_DWORD	dwBothSubID = 0, dwFirstSubID = 0, dwSecondSubID = 0 ;
					for ( _DWORD i = 0 ; i < dwBytesInSubID ; i++ )
					{
						dwBothSubID = dwBothSubID << 7 ;
						dwBothSubID |= EncodedBlobPtr[i] & 0x7F ;
					}

					dwFirstSubID = dwBothSubID/40 ;
					dwSecondSubID = dwBothSubID - (dwFirstSubID*40) ;

					_CHAR	temp[200], *tmpData ;
					_DWORD	dwLength = 0 ;
					_itoa(dwFirstSubID, (char *)temp, 10) ;
					dwLength = strlen((char *)temp) ;
					dwLength++ ;
					tmpData = (_PBYTE) malloc(dwLength+1) ;
					strcpy((char *)tmpData, (char *)temp) ;
					strcat((char *)tmpData, (char *)".") ;
					_itoa(dwSecondSubID, (char *)temp, 10) ;
					dwLength += strlen((char *)temp) ;
					dwLength++ ;
					pbData = (_PBYTE) malloc(dwLength+1) ;
					strcpy((char *)pbData, (char *)tmpData) ;
					free(tmpData) ;
					strcat((char *)pbData, (char *)temp) ;
					strcat((char *)pbData, (char *)".") ;

					bFirstTime = _FALSE ;
				}
				else
				{
					_DWORD	dwSubID = 0 ;
					for ( _DWORD i = 0 ; i < dwBytesInSubID ; i++ )
					{
						dwSubID = dwSubID << 7 ;
						dwSubID |= EncodedBlobPtr[i] & 0x7F ;
					}

					_PCHAR	temp ;
					_CHAR	temp1[200] ;
					_itoa(dwSubID, (char *)temp1, 10) ;
					temp = (_PCHAR) malloc(strlen((char *)pbData) + strlen((char *)temp1) + 1 + 1) ;
					strcpy((char *)temp, (char *)pbData) ;
					strcat((char *)temp, (char *)temp1) ;
					strcat((char *)temp, (char *)".") ;
					free(pbData) ;
					pbData = temp ;
				}

				dwEncodedBlobIndex += dwBytesInSubID ;
				EncodedBlobPtr += dwBytesInSubID ;
			}

			pbData[strlen((char *)pbData)-1] = '\0' ;
			cbData = strlen((char *)pbData) ;
			if ( Type & 0x20 )
				Encoding = CONSTRUCTED ;
			Type = Type & 0x1F ;

			return ;
		}
	}

	NumberOfLengthBytes = 0 ;
	cbData = 0 ;
	pbData = _NULL ;
	Type = INVALID_DER_TYPE ;

	return ;
}

