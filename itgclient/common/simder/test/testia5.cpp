#include "PrintableString.h"
#include "UniversalInteger.h"
#include "BaseDERCollection.h"
#include <stdio.h>
#include <string.h>

int main()
{
  _DWORD i, length ;
  char		string[] = {"This is fun!!"} ;

  CPrintableString	cps1(strlen(const char *)string, (_PBYTE)string) ;

  printf("cps1.BaseDERBlob.cbdata : %d\n", cps1.BaseDERBlob->cbData) ;
  printf("cps1.BaseDERBlob.pbData :\n") ;
  for ( i = 0 ; i < cps1.BaseDERBlob->cbData ; i++ )
    printf("0x%02x ", cps1.BaseDERBlob->pbData[i]) ;
  printf("\n") ;
  for ( i = 0 ; i < cps1.BaseDERBlob->cbData ; i++ )
    printf("%c    ", cps1.BaseDERBlob->pbData[i]) ;
  printf("\n\n") ;

  printf("cps1.BaseDERBlob.cbdata : %d\n", cps1.BaseDERBlob->cbData) ;
  printf("cps1.BaseDERBlob.pbData :\n") ;
  for ( i = 0 ; i < cps1.BaseDERBlob->cbData ; i++ )
    printf("0x%02x ", cps1.BaseDERBlob->pbData[i]) ;
  printf("\n") ;
  for ( i = 0 ; i < cps1.BaseDERBlob->cbData ; i++ )
    printf("%c    ", cps1.BaseDERBlob->pbData[i]) ;
  printf("\n\n") ;

  CPrintableString		cps2(4, (_PBYTE)string) ;

  printf("cps2.BaseDERBlob.cbdata : %d\n", cps2.BaseDERBlob->cbData) ;
  printf("cps2.BaseDERBlob.pbData :\n") ;
  for ( i = 0 ; i < cps2.BaseDERBlob->cbData ; i++ )
    printf("0x%02x ", cps2.BaseDERBlob->pbData[i]) ;
  printf("\n") ;
  for ( i = 0 ; i < cps2.BaseDERBlob->cbData ; i++ )
    printf("%c    ", cps2.BaseDERBlob->pbData[i]) ;
  printf("\n\n") ;

  cps1 = cps2 ;

  printf("cp1 = cps2 :\ncps1.BaseDERBlob.cbdata : %d\n", cps1.BaseDERBlob->cbData) ;
  printf("cps1.BaseDERBlob.pbData :\n") ;
  for ( i = 0 ; i < cps1.BaseDERBlob->cbData ; i++ )
    printf("0x%02x ", cps1.BaseDERBlob->pbData[i]) ;
  printf("\n") ;
  for ( i = 0 ; i < cps1.BaseDERBlob->cbData ; i++ )
    printf("%c    ", cps1.BaseDERBlob->pbData[i]) ;
  printf("\n\n") ;

  CPrintableString		cps3(3, (_PBYTE)string) ;
 
  printf("cps3.BaseDERBlob.cbdata : %d\n", cps3.BaseDERBlob->cbData) ;
  printf("cps3.BaseDERBlob.pbData :\n") ;
  for ( i = 0 ; i < cps3.BaseDERBlob->cbData ; i++ )
    printf("0x%02x ", cps3.BaseDERBlob->pbData[i]) ;
  printf("\n") ;
  for ( i = 0 ; i < cps3.BaseDERBlob->cbData ; i++ )
    printf("%c    ", cps3.BaseDERBlob->pbData[i]) ;
  printf("\n\n") ;

  CPrintableString		cps4(cps3) ;

  printf("cps4(cps3) : \ncps4.BaseDERBlob.cbdata : %d\n", cps4.BaseDERBlob->cbData) ;
  printf("cps4.BaseDERBlob.pbData :\n") ;
  for ( i = 0 ; i < cps4.BaseDERBlob->cbData ; i++ )
    printf("0x%02x ", cps4.BaseDERBlob->pbData[i]) ;
  printf("\n") ;
  for ( i = 0 ; i < cps4.BaseDERBlob->cbData ; i++ )
    printf("%c    ", cps4.BaseDERBlob->pbData[i]) ;
  printf("\n\n") ;
  
  CBaseDERCollection	cbdc ;

  cbdc = cps1 + cps4 ;

  printf("cbdc = cps1 + cps4 : \ncbdc.BaseDERBlob.cbdata : %d\n", cbdc.BaseDERBlob->cbData) ;
  printf("cbdc.BaseDERBlob.pbData :\n") ;
  for ( i = 0 ; i < cbdc.BaseDERBlob->cbData ; i++ )
    printf("0x%02x ", cbdc.BaseDERBlob->pbData[i]) ;
  printf("\n") ;
  for ( i = 0 ; i < cbdc.BaseDERBlob->cbData ; i++ )
    printf("%c    ", cbdc.BaseDERBlob->pbData[i]) ;
  printf("\n\n") ;

  _DWORD	tmp = 0x12345678 ;
  CUniversalInteger	cui1(4, (_PCHAR)&tmp) ;

  printf("cui1.BaseDERBlob.cbdata : %d\n", cui1.BaseDERBlob->cbData) ;
  printf("cui1.BaseDERBlob.pbData :\n") ;
  for ( i = 0 ; i < cui1.BaseDERBlob->cbData ; i++ )
    printf("0x%02x ", cui1.BaseDERBlob->pbData[i]) ;
  printf("\n\n") ;
  
  cbdc = cps1 + cui1 + cps4 ;

  printf("cbdc = cps1 + cui1 + cps4 : \ncbdc.BaseDERBlob.cbdata : %d\n", cbdc.BaseDERBlob->cbData) ;
  printf("cbdc.BaseDERBlob.pbData :\n") ;
  for ( i = 0 ; i < cbdc.BaseDERBlob->cbData ; i++ )
    printf("0x%02x ", cbdc.BaseDERBlob->pbData[i]) ;
  printf("\n") ;
  for ( i = 0 ; i < cbdc.BaseDERBlob->cbData ; i++ )
    printf("%c    ", cbdc.BaseDERBlob->pbData[i]) ;
  printf("\n\n") ;
#endif

  return(1) ;
}
