#include "BitString.h"
#include "BaseDERCollection.h"
#include <stdio.h>
#include <memory.h>

int main()
{
  _DWORD	tmp = 0x12345678, i ;
  _DWORD	dwDecoded = 0 ;

  CBitString	cbs1(5, 4, (_PBYTE)&tmp) ;

  printf("cbs1.BaseDERBlob.cbdata : %d\n", cbs1.BaseDERBlob->cbData) ;
  printf("cbs1.BaseDERBlob.pbData : ") ;
  for ( i = 0 ; i < cbs1.BaseDERBlob->cbData ; i++ )
    printf("0x%02x ", cbs1.BaseDERBlob->pbData[i]) ;
  printf("\n\n") ;

  cbs1.decode() ;

  memcpy(&dwDecoded, cbs1.pbData, cbs1.cbData) ;
  printf("Decoded BitString for cbs1 is : 0x%08x\n", dwDecoded) ;
  printf("Unused Bits for cbs1 is : %2x\n\n", cbs1.cbUnusedBits) ;

  CBitString	cbs2(6, 3, (_PBYTE)&tmp) ;

  printf("cbs2.BaseDERBlob.cbdata : %d\n", cbs2.BaseDERBlob->cbData) ;
  printf("cbs2.BaseDERBlob.pbData : ") ;
  for ( i = 0 ; i < cbs2.BaseDERBlob->cbData ; i++ )
    printf("0x%02x ", cbs2.BaseDERBlob->pbData[i]) ;
  printf("\n\n") ;

  cbs2.decode() ;

  memcpy(&dwDecoded, cbs2.pbData, cbs2.cbData) ;
  printf("Decoded BitString for cbs2 is : 0x%08x\n", dwDecoded) ;
  printf("Unused Bits for cbs2 is : %2x\n\n", cbs2.cbUnusedBits) ;

  cbs2 = cbs1 ;

  printf("cbs2 = cbs1 :\ncbs2.BaseDERBlob.cbdata : %d\n", cbs2.BaseDERBlob->cbData) ;
  printf("cbs2.BaseDERBlob.pbData : ") ;
  for ( i = 0 ; i < cbs2.BaseDERBlob->cbData ; i++ )
    printf("0x%02x ", cbs2.BaseDERBlob->pbData[i]) ;
  printf("\n\n") ;

  CBitString	cbs3(cbs2) ;

  printf("cbs3(cbs2) :\ncbs3.BaseDERBlob.cbdata : %d\n", cbs3.BaseDERBlob->cbData) ;
  printf("cbs3.BaseDERBlob.pbData : ") ;
  for ( i = 0 ; i < cbs3.BaseDERBlob->cbData ; i++ )
    printf("0x%02x ", cbs3.BaseDERBlob->pbData[i]) ;
  printf("\n\n") ;

  return(1) ;
}

