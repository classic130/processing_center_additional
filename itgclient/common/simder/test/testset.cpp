#include <stdio.h>
#include "Set.h"
#include "BaseDERCollection.h"
#include "UniversalInteger.h"

int main()
{
  _DWORD	tmp = 0x12345678, i ;

  CUniversalInteger	cui1(3, (_PBYTE)&tmp) ;

  printf("cui1.BaseDERBlob.cbdata : %d\n", cui1.BaseDERBlob->cbData) ;
  printf("cui1.BaseDERBlob.pbData : ") ;
  for ( i = 0 ; i < cui1.BaseDERBlob->cbData ; i++ )
    printf("0x%02x ", cui1.BaseDERBlob->pbData[i]) ;
  printf("\n\n") ;

  CSet cset1(cui1) ;

  printf("cset1(cui1) :\ncset1.BaseDERBlob.cbdata : %d\n", cset1.BaseDERBlob->cbData) ;
  printf("cset1.BaseDERBlob.pbData : ") ;
  for ( i = 0 ; i < cset1.BaseDERBlob->cbData ; i++ )
    printf("0x%02x ", cset1.BaseDERBlob->pbData[i]) ;
  printf("\n\n") ;

  CSet cset2(cset1) ;

  printf("cset2(cset1) :\ncset2.BaseDERBlob.cbdata : %d\n", cset2.BaseDERBlob->cbData) ;
  printf("cset2.BaseDERBlob.pbData : ") ;
  for ( i = 0 ; i < cset2.BaseDERBlob->cbData ; i++ )
    printf("0x%02x ", cset2.BaseDERBlob->pbData[i]) ;
  printf("\n\n") ;

  CSet cset3((CBaseDER)cset1) ;

  printf("cset3((CBaseDER)cset1) :\ncset3.BaseDERBlob.cbdata : %d\n", cset3.BaseDERBlob->cbData) ;
  printf("cset3.BaseDERBlob.pbData : ") ;
  for ( i = 0 ; i < cset3.BaseDERBlob->cbData ; i++ )
    printf("0x%02x ", cset3.BaseDERBlob->pbData[i]) ;
  printf("\n\n") ;

  CUniversalInteger	cui2(4, (_PBYTE)&tmp) ;

  printf("cui2.BaseDERBlob.cbdata : %d\n", cui2.BaseDERBlob->cbData) ;
  printf("cui2.BaseDERBlob.pbData : ") ;
  for ( i = 0 ; i < cui2.BaseDERBlob->cbData ; i++ )
    printf("0x%02x ", cui2.BaseDERBlob->pbData[i]) ;
  printf("\n\n") ;

  CBaseDERCollection	cbdc ;

  cbdc = cui2 ;

  printf("cbdc = cui2 :\ncbdc.BaseDERBlob.cbdata : %d\n", cbdc.BaseDERBlob->cbData) ;
  printf("cbdc.BaseDERBlob.pbData : ") ;
  for ( i = 0 ; i < cbdc.BaseDERBlob->cbData ; i++ )
    printf("0x%02x ", cbdc.BaseDERBlob->pbData[i]) ;
  printf("\n\n") ;

  CSet cset4(cbdc+cset1) ;

  printf("cset4(cbdc+cset1) :\ncset4.BaseDERBlob.cbdata : %d\n", cset4.BaseDERBlob->cbData) ;
  printf("cset4.BaseDERBlob.pbData : ") ;
  for ( i = 0 ; i < cset4.BaseDERBlob->cbData ; i++ )
    printf("0x%02x ", cset4.BaseDERBlob->pbData[i]) ;
  printf("\n\n") ;

  return(1) ;
}

