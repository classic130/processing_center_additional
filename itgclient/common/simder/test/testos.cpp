#include "OctetString.h"
#include "UniversalInteger.h"
#include "BaseDERCollection.h"
#include <stdio.h>
#include <string.h>

int main()
{
  _DWORD i, length ;
  _BYTE		string[1024] ;

  length = 6 ;
  for ( i = 0 ; i < length ; i++ )
    string[i] = i+1 ;

  COctetString		cos1(length, (_PBYTE)string) ;

  printf("cos1.BaseDERBlob.cbdata : %d\n", cos1.BaseDERBlob->cbData) ;
  printf("cos1.BaseDERBlob.pbData :\n") ;
  for ( i = 0 ; i < cos1.BaseDERBlob->cbData ; i++ )
    printf("0x%02x ", cos1.BaseDERBlob->pbData[i]) ;
  printf("\n\n") ;

  cos1.decode() ;

  printf("Decoded Octet String for cos1 is :\n") ;
  for ( i = 0 ; i < cos1.cbData ; i++ )
    printf("0x%02x ", cos1.pbData[i]) ;
  printf("\n\n") ;

  COctetString		cos2(4, (_PBYTE)&string) ;

  printf("cos2.BaseDERBlob.cbdata : %d\n", cos2.BaseDERBlob->cbData) ;
  printf("cos2.BaseDERBlob.pbData :\n") ;
  for ( i = 0 ; i < cos2.BaseDERBlob->cbData ; i++ )
    printf("0x%02x ", cos2.BaseDERBlob->pbData[i]) ;
  printf("\n\n") ;

  cos1 = cos2 ;

  printf("cos1 = cos2 : \ncos1.BaseDERBlob.cbdata : %d\n", cos1.BaseDERBlob->cbData) ;
  printf("cos1.BaseDERBlob.pbData :\n") ;
  for ( i = 0 ; i < cos1.BaseDERBlob->cbData ; i++ )
    printf("0x%02x ", cos1.BaseDERBlob->pbData[i]) ;
  printf("\n\n") ;

  COctetString		cos3(3, (_PBYTE)&string) ;
 
  printf("cos3.BaseDERBlob.cbdata : %d\n", cos3.BaseDERBlob->cbData) ;
  printf("cos3.BaseDERBlob.pbData :\n") ;
  for ( i = 0 ; i < cos3.BaseDERBlob->cbData ; i++ )
    printf("0x%02x ", cos3.BaseDERBlob->pbData[i]) ;
  printf("\n\n") ;

  COctetString		cos4(cos3) ;

  printf("cos4(cos3) : \ncos4.BaseDERBlob.cbdata : %d\n", cos4.BaseDERBlob->cbData) ;
  printf("cos4.BaseDERBlob.pbData :\n") ;
  for ( i = 0 ; i < cos4.BaseDERBlob->cbData ; i++ )
    printf("0x%02x ", cos4.BaseDERBlob->pbData[i]) ;
  printf("\n\n") ;
  
  CBaseDERCollection	cbdc ;

  cbdc = cos1 + cos4 ;

  printf("cbdc = cos1 + cos4 : \ncbdc.BaseDERBlob.cbdata : %d\n", cbdc.BaseDERBlob->cbData) ;
  printf("cbdc.BaseDERBlob.pbData :\n") ;
  for ( i = 0 ; i < cbdc.BaseDERBlob->cbData ; i++ )
    printf("0x%02x ", cbdc.BaseDERBlob->pbData[i]) ;
  printf("\n\n") ;

  CBaseDERCollection	cbdc2 ;

  _DWORD	tmp = 0x12345678 ;
  CUniversalInteger	cui1(2, (_PCHAR)&tmp) ;

  printf("cui1.BaseDERBlob.cbdata : %d\n", cui1.BaseDERBlob->cbData) ;
  printf("cui1.BaseDERBlob.pbData :\n") ;
  for ( i = 0 ; i < cui1.BaseDERBlob->cbData ; i++ )
    printf("0x%02x ", cui1.BaseDERBlob->pbData[i]) ;
  printf("\n\n") ;
  
  cbdc2 = cui1 + cos2 ;

  printf("cbdc2 = cui1 + cos2 : \ncbdc.BaseDERBlob.cbdata : %d\n", cbdc2.BaseDERBlob->cbData) ;
  printf("cbdc2.BaseDERBlob.pbData :\n") ;
  for ( i = 0 ; i < cbdc2.BaseDERBlob->cbData ; i++ )
    printf("0x%02x ", cbdc2.BaseDERBlob->pbData[i]) ;
  printf("\n\n") ;

  return(1) ;
}

