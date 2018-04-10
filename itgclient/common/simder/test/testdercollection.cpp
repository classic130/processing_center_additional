#include "UniversalInteger.h"
#include "BaseDERCollection.h"
#include <stdio.h>

int main()
{
  _DWORD	tmp = 0x12345678, i ;

  CUniversalInteger	cui1(3, (_PBYTE)&tmp) ;

  printf("cui1.BaseDERBlob.cbdata : %d\n", cui1.BaseDERBlob->cbData) ;
  printf("cui1.BaseDERBlob.pbData : ") ;
  for ( i = 0 ; i < cui1.BaseDERBlob->cbData ; i++ )
    printf("0x%02x ", cui1.BaseDERBlob->pbData[i]) ;
  printf("\n\n") ;

  CUniversalInteger	cui2(4, (_PBYTE)&tmp) ;
 
  printf("cui2 :\ncui2.BaseDERBlob.cbdata : %d\n", cui2.BaseDERBlob->cbData) ;
  printf("cui2.BaseDERBlob.pbData : ") ;
  for ( i = 0 ; i < cui2.BaseDERBlob->cbData ; i++ )
    printf("0x%02x ", cui2.BaseDERBlob->pbData[i]) ;
  printf("\n\n") ;

  CBaseDERCollection	cbdc1 ;

  cbdc1 = cui1 + cui2 ;

  printf("cbdc1 = cui1 + cui2 :\ncbdc1.BaseDERBlob.cbdata : %d\n", cbdc1.BaseDERBlob->cbData) ;
  printf("cbdc1.BaseDERBlob.pbData : ") ;
  for ( i = 0 ; i < cbdc1.BaseDERBlob->cbData ; i++ )
    printf("0x%02x ", cbdc1.BaseDERBlob->pbData[i]) ;
  printf("\n\n") ;

  CBaseDERCollection	cbdc2 ;

  cbdc2 = cui2 ;

  printf("cbd2 = cui2 :\ncbdc2.BaseDERBlob.cbdata : %d\n", cbdc2.BaseDERBlob->cbData) ;
  printf("cbdc2.BaseDERBlob.pbData : ") ;
  for ( i = 0 ; i < cbdc2.BaseDERBlob->cbData ; i++ )
    printf("0x%02x ", cbdc2.BaseDERBlob->pbData[i]) ;
  printf("\n\n") ;

  cbdc2 = cbdc1 + cbdc1 ;

  printf("cbdc2 = cbdc1 + cbdc1 :\ncbdc2.BaseDERBlob.cbdata : %d\n", cbdc2.BaseDERBlob->cbData) ;
  printf("cbdc2.BaseDERBlob.pbData : ") ;
  for ( i = 0 ; i < cbdc2.BaseDERBlob->cbData ; i++ )
    printf("0x%02x ", cbdc2.BaseDERBlob->pbData[i]) ;
  printf("\n\n") ;

  return (1) ;
}

