#include "UniversalInteger.h"
#include "BaseDERCollection.h"
#include <stdio.h>
#include <memory.h>

int main()
{
  _DWORD	tmp = 0x12345678, i ;
  _DWORD	theUI = 0 ;

  CUniversalInteger	cui1(3, (_PBYTE)&tmp) ;

  printf("cui1.BaseDERBlob.cbdata : %d\n", cui1.BaseDERBlob->cbData) ;
  printf("cui1.BaseDERBlob.pbData : ") ;
  for ( i = 0 ; i < cui1.BaseDERBlob->cbData ; i++ )
    printf("0x%02x ", cui1.BaseDERBlob->pbData[i]) ;
  printf("\n\n") ;

  // Deliberately destroy the data
  for ( i = 0 ; i < 3 ; i++ )
    cui1.pbData[i] = 0x00 ;
  cui1.cbData = 0 ;

  cui1.decode() ;

  memcpy(&theUI, cui1.pbData, cui1.cbData) ;
  printf("UI for cui1 is : 0x%08x\n\n", theUI) ;

  CUniversalInteger	cui2(4, (_PBYTE)&tmp) ;

  printf("cui2.BaseDERBlob.cbdata : %d\n", cui2.BaseDERBlob->cbData) ;
  printf("cui2.BaseDERBlob.pbData : ") ;
  for ( i = 0 ; i < cui2.BaseDERBlob->cbData ; i++ )
    printf("0x%02x ", cui2.BaseDERBlob->pbData[i]) ;
  printf("\n\n") ;

  // Deliberately destroy the data
  for ( i = 0 ; i < 3 ; i++ )
    cui2.pbData[i] = 0x00 ;
  cui2.cbData = 0 ;

  cui2.decode() ;

  memcpy(&theUI, cui2.pbData, cui2.cbData) ;
  printf("UI for cui2 is : 0x%08x\n\n", theUI) ;

  cui1 = cui2 ;

  printf("cui1 = cui2 : cui1.BaseDERBlob.cbdata : %d\n", cui1.BaseDERBlob->cbData) ;
  printf("              cui1.BaseDERBlob.pbData :") ;
  for ( i = 0 ; i < cui1.BaseDERBlob->cbData ; i++ )
    printf("0x%02x ", cui1.BaseDERBlob->pbData[i]) ;
  printf("\n\n") ;

  CUniversalInteger	cui3(3, (_PBYTE)&tmp) ;
 
  cui1 = cui3 ;
 
  printf("cui1 = cui3 :\ncui3.BaseDERBlob.cbdata : %d\n", cui3.BaseDERBlob->cbData) ;
  printf("cui3.BaseDERBlob.pbData : ") ;
  for ( i = 0 ; i < cui3.BaseDERBlob->cbData ; i++ )
    printf("0x%02x ", cui3.BaseDERBlob->pbData[i]) ;
  printf("\n\n") ;

  CUniversalInteger	cui4(cui3) ;

  printf("cui4(cui3) : cui4.BaseDERBlob.cbdata : %d\n", cui4.BaseDERBlob->cbData) ;
  printf("             cui4.BaseDERBlob.pbData : ") ;
  for ( i = 0 ; i < cui4.BaseDERBlob->cbData ; i++ )
    printf("0x%02x ", cui4.BaseDERBlob->pbData[i]) ;
  printf("\n\n") ;
  
  CBaseDERCollection	cbdc ;

  cbdc = cui1 + cui2 ;

  printf("cbdc = cui1 + cui2 : cbdc.BaseDERBlob.cbdata : %d\n", cbdc.BaseDERBlob->cbData) ;
  printf("                     cbdc.BaseDERBlob.pbData : ") ;
  for ( i = 0 ; i < cbdc.BaseDERBlob->cbData ; i++ )
    printf("0x%02x ", cbdc.BaseDERBlob->pbData[i]) ;
  printf("\n\n") ;

  return(1) ;
}

