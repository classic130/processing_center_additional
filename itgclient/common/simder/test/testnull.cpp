#include "Null.h"
#include "BaseDERCollection.h"
#include "UniversalInteger.h"
#include <stdio.h>

int main()
{
  _DWORD	i = 0 ;
  CNull 	cnull1 ;
  
  printf("cnull1.BaseDERBlob.cbdata : %d\n", cnull1.BaseDERBlob->cbData) ;
  printf("cnull1.BaseDERBlob.pbData :\n") ;
  for ( i = 0 ; i < cnull1.BaseDERBlob->cbData ; i++ )
    printf("0x%02x ", cnull1.BaseDERBlob->pbData[i]) ;
  printf("\n\n") ;

  CNull 	cnull2 ;
  
  printf("cnull2.BaseDERBlob.cbdata : %d\n", cnull2.BaseDERBlob->cbData) ;
  printf("cnull2.BaseDERBlob.pbData :\n") ;
  for ( i = 0 ; i < cnull2.BaseDERBlob->cbData ; i++ )
    printf("0x%02x ", cnull2.BaseDERBlob->pbData[i]) ;
  printf("\n\n") ;

  cnull1 = cnull2 ;

  printf("cnull1 = cnull2 :\ncnull2.BaseDERBlob.cbdata : %d\n", cnull2.BaseDERBlob->cbData) ;
  printf("cnull2.BaseDERBlob.pbData :\n") ;
  for ( i = 0 ; i < cnull2.BaseDERBlob->cbData ; i++ )
    printf("0x%02x ", cnull2.BaseDERBlob->pbData[i]) ;
  printf("\n\n") ;

  CNull		cnull3(cnull2) ;

  printf("cnull3(cnull2) :\ncnull3.BaseDERBlob.cbdata : %d\n", cnull3.BaseDERBlob->cbData) ;
  printf("cnull3.BaseDERBlob.pbData :\n") ;
  for ( i = 0 ; i < cnull3.BaseDERBlob->cbData ; i++ )
    printf("0x%02x ", cnull3.BaseDERBlob->pbData[i]) ;
  printf("\n\n") ;

  _DWORD	tmp = 0x12345678 ;
  CUniversalInteger	cui1(4, (_PCHAR)&tmp) ;

  printf("cui1.BaseDERBlob.cbdata : %d\n", cui1.BaseDERBlob->cbData) ;
  printf("cui1.BaseDERBlob.pbData :\n") ;
  for ( i = 0 ; i < cui1.BaseDERBlob->cbData ; i++ )
    printf("0x%02x ", cui1.BaseDERBlob->pbData[i]) ;
  printf("\n\n") ;
  
  CBaseDERCollection	cbdc ;

  cbdc = cui1 + cnull2 + cnull3 ;

  printf("cbdc = cui1 + cnull2 + cnull3 : \ncbdc.BaseDERBlob.cbdata : %d\n", cbdc.BaseDERBlob->cbData) ;
  printf("cbdc.BaseDERBlob.pbData :\n") ;
  for ( i = 0 ; i < cbdc.BaseDERBlob->cbData ; i++ )
    printf("0x%02x ", cbdc.BaseDERBlob->pbData[i]) ;
  printf("\n\n") ;

  return(1) ;
}

