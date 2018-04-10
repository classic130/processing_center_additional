#include <stdio.h>
#include "Sequence.h"
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

  CSequence csq1(cui1) ;

  printf("csq1(cui1) :\ncsq1.BaseDERBlob.cbdata : %d\n", csq1.BaseDERBlob->cbData) ;
  printf("csq1.BaseDERBlob.pbData : ") ;
  for ( i = 0 ; i < csq1.BaseDERBlob->cbData ; i++ )
    printf("0x%02x ", csq1.BaseDERBlob->pbData[i]) ;
  printf("\n\n") ;

  CSequence csq2(csq1) ;

  printf("csq2(csq1) :\ncsq2.BaseDERBlob.cbdata : %d\n", csq2.BaseDERBlob->cbData) ;
  printf("csq2.BaseDERBlob.pbData : ") ;
  for ( i = 0 ; i < csq2.BaseDERBlob->cbData ; i++ )
    printf("0x%02x ", csq2.BaseDERBlob->pbData[i]) ;
  printf("\n\n") ;

  CSequence csq3((CBaseDER)csq1) ;

  printf("csq3((CBaseDER)csq1) :\ncsq3.BaseDERBlob.cbdata : %d\n", csq3.BaseDERBlob->cbData) ;
  printf("csq3.BaseDERBlob.pbData : ") ;
  for ( i = 0 ; i < csq3.BaseDERBlob->cbData ; i++ )
    printf("0x%02x ", csq3.BaseDERBlob->pbData[i]) ;
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

  CSequence csq4(cbdc+csq1) ;

  printf("csq4(cbdc+csq1) :\ncsq4.BaseDERBlob.cbdata : %d\n", csq4.BaseDERBlob->cbData) ;
  printf("csq4.BaseDERBlob.pbData : ") ;
  for ( i = 0 ; i < csq4.BaseDERBlob->cbData ; i++ )
    printf("0x%02x ", csq4.BaseDERBlob->pbData[i]) ;
  printf("\n\n") ;


  CSequence csq5 ;

  csq5 = csq4 ;

  csq5 += cui1 ;
  printf("csq5 = csq4 ;\ncsq5 += cui1 ;\n\ncsq5.BaseDERBlob.cbdata : %d\n", csq5.BaseDERBlob->cbData) ;
  printf("csq5.BaseDERBlob.pbData : ") ;
  for ( i = 0 ; i < csq5.BaseDERBlob->cbData ; i++ )
    printf("0x%02x ", csq5.BaseDERBlob->pbData[i]) ;
  printf("\n\n") ;

  return(1) ;
}

