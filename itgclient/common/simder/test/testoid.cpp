#include "ObjectIdentifier.h"
#include "BaseDERCollection.h"
#include "PrintableString.h"
#include <string.h>
#include <stdio.h>

int main()
{
  _DWORD	i = 0 ;
  _CHAR		string1[] = {"1.2.840.113549.1.1.4"} ;

  CObjectIdentifier	coid1(strlen((const char *)string1), (_PCHAR)string1) ;

  printf("coid1.BaseDERBlob.cbdata : %d\n", coid1.BaseDERBlob->cbData) ;
  printf("coid1.BaseDERBlob.pbData :\n") ;
  for ( i = 0 ; i < coid1.BaseDERBlob->cbData ; i++ )
    printf("0x%02x ", coid1.BaseDERBlob->pbData[i]) ;
  printf("\n\n") ;

  coid1.decode() ;
  printf("Decoded coid1 is : %s\n", coid1.pbData) ;
  printf("Decoded coid1 length is : %d\n", coid1.cbData) ;

  _CHAR		string2[] = {"1840.19.1.3451.43"} ;
  CObjectIdentifier	coid2(strlen((const char *)string2), (_PCHAR)string2) ;

  printf("coid2.BaseDERBlob.cbdata : %d\n", coid2.BaseDERBlob->cbData) ;
  printf("coid2.BaseDERBlob.pbData :\n") ;
  for ( i = 0 ; i < coid2.BaseDERBlob->cbData ; i++ )
    printf("0x%02x ", coid2.BaseDERBlob->pbData[i]) ;
  printf("\n\n") ;

  coid2.decode() ;
  printf("Decoded coid2 is : %s\n", coid2.pbData) ;
  printf("Decoded coid2 length is : %d\n", coid2.cbData) ;

  coid2 = coid1 ;

  printf("coid2 = coid1 :\ncoid2.BaseDERBlob.cbdata : %d\n", coid2.BaseDERBlob->cbData) ;
  printf("coid2.BaseDERBlob.pbData :\n") ;
  for ( i = 0 ; i < coid2.BaseDERBlob->cbData ; i++ )
    printf("0x%02x ", coid2.BaseDERBlob->pbData[i]) ;
  printf("\n\n") ;

  CObjectIdentifier	coid4(coid2) ;

  printf("coid4(coid2) :\ncoid4.BaseDERBlob.cbdata : %d\n", coid4.BaseDERBlob->cbData) ;
  printf("coid4.BaseDERBlob.pbData :\n") ;
  for ( i = 0 ; i < coid4.BaseDERBlob->cbData ; i++ )
    printf("0x%02x ", coid4.BaseDERBlob->pbData[i]) ;
  printf("\n\n") ;

  _CHAR		string5[] = {"14.3452.1135.461.1.4"} ;
  CObjectIdentifier	coid5(strlen((const char *)string5), (_PCHAR)string5) ;

  printf("coid5(coid2) :\ncoid5.BaseDERBlob.cbdata : %d\n", coid5.BaseDERBlob->cbData) ;
  printf("coid5.BaseDERBlob.pbData :\n") ;
  for ( i = 0 ; i < coid5.BaseDERBlob->cbData ; i++ )
    printf("0x%02x ", coid5.BaseDERBlob->pbData[i]) ;
  printf("\n\n") ;

  CBaseDERCollection	cbdc ;

  cbdc = coid1 + coid5 ;

  printf("cbdc = coid1 + coid5 : \ncbdc.BaseDERBlob.cbdata : %d\n", cbdc.BaseDERBlob->cbData) ;
  printf("cbdc.BaseDERBlob.pbData :\n") ;
  for ( i = 0 ; i < cbdc.BaseDERBlob->cbData ; i++ )
    printf("0x%02x ", cbdc.BaseDERBlob->pbData[i]) ;
  printf("\n\n") ;

  char	string[] = {"This is real fun!!"} ;
  CPrintableString		cps1(strlen((const char *)string), (_PBYTE)string) ;

  printf("cps1.BaseDERBlob.cbdata : %d\n", cps1.BaseDERBlob->cbData) ;
  printf("cps1.BaseDERBlob.pbData :\n") ;
  for ( i = 0 ; i < cps1.BaseDERBlob->cbData ; i++ )
    printf("0x%02x ", cps1.BaseDERBlob->pbData[i]) ;
  printf("\n") ;
  for ( i = 0 ; i < cps1.BaseDERBlob->cbData ; i++ )
    printf("%c    ", cps1.BaseDERBlob->pbData[i]) ;
  printf("\n\n") ;

  CBaseDERCollection	cbdc2 ;

  cbdc2 = coid1 + coid5 + cps1 ;

  printf("cbdc = coid1 + coid5 + cps1 : \ncbdc2.BaseDERBlob.cbdata : %d\n", cbdc2.BaseDERBlob->cbData) ;
  printf("cbdc2.BaseDERBlob.pbData :\n") ;
  for ( i = 0 ; i < cbdc2.BaseDERBlob->cbData ; i++ )
    printf("0x%02x ", cbdc2.BaseDERBlob->pbData[i]) ;
  printf("\n\n") ;

  return 1 ;
}

