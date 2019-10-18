#include "UTCTime.h"
#include "UniversalInteger.h"
#include "BaseDERCollection.h"
#include <stdio.h>
#include <string.h>

int main()
{
  _DWORD i, length ;
  char		utctime[] = {"990820183456Z"} ;

  CUTCTime		cutct1(strlen((const char *)utctime), (_PBYTE)utctime) ;

  printf("cutct1.BaseDERBlob.cbdata : %d\n", cutct1.BaseDERBlob->cbData) ;
  printf("cutct1.BaseDERBlob.pbData :\n") ;
  for ( i = 0 ; i < cutct1.BaseDERBlob->cbData ; i++ )
    printf("0x%02x ", cutct1.BaseDERBlob->pbData[i]) ;
  printf("\n") ;
  for ( i = 0 ; i < cutct1.BaseDERBlob->cbData ; i++ )
    printf("%c    ", cutct1.BaseDERBlob->pbData[i]) ;
  printf("\n\n") ;

  cutct1.decode() ;

  char	szDecodedString[1000] ;
  strcpy(szDecodedString, (const char *)cutct1.pbData) ;
  printf("Decoded String from cutct1 is : \n%s\n", szDecodedString) ;
  printf("Decoded String Length from cutct1 is : %d\n\n", cutct1.cbData) ;

  return(1) ;
}

