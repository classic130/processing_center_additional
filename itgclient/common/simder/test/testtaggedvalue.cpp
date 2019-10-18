#include "VisibleString.h"
#include "TaggedValue.h"
#include <string.h>
#include <stdio.h>

int main()
{
  _DWORD		i ;
//  _CHAR			string[] = {"Jones"} ;
  _CHAR			string[] = {"JonesJonesJonesJonesJonesJoneJonesJonessJonesJonesJonesJonesJonesJonesJonesJonesJonesJonesJonesJonesJonesJonesJonesJoneJonessJoneJoneJoneJoneJoneJoneJoneJoneJoneJonessssssssss"} ;
  CVisibleString 	cvs1(strlen((const char *)string), (_PBYTE)string) ;

  printf("cvs1.BaseDERBlob.cbdata : %d\n", cvs1.BaseDERBlob->cbData) ;
  printf("cvs1.BaseDERBlob.pbData :\n") ;
  for ( i = 0 ; i < cvs1.BaseDERBlob->cbData ; i++ )
    printf("0x%02x ", cvs1.BaseDERBlob->pbData[i]) ;
  printf("\n") ;
  for ( i = 0 ; i < cvs1.BaseDERBlob->cbData ; i++ )
    printf("%c    ", cvs1.BaseDERBlob->pbData[i]) ;
  printf("\n\n") ;

  CTaggedValue ctv1(CONTEXT_SPECIFIC, CONSTRUCTED, 0, _FALSE, _FALSE, cvs1) ;
  ctv1.decode() ;
  printf("Class for ctv1 is : %x\n", ctv1.Class) ;
  printf("Encoding for ctv1 is : %x\n", ctv1.Encoding) ;
  printf("TagNumber for ctv1 is : %x\n", ctv1.TagNumber) ;
  printf("Value represented by ctv11 is : ") ;
  for ( i = 0 ; i < ctv1.cbData ; i++ )
    printf("%c", ctv1.pbData[i]) ;
  printf("\n\n") ;

  printf("ctv1.BaseDERBlob.cbdata : %d\n", ctv1.BaseDERBlob->cbData) ;
  printf("ctv1.BaseDERBlob.pbData :\n") ;
  for ( i = 0 ; i < ctv1.BaseDERBlob->cbData ; i++ )
    printf("0x%02x ", ctv1.BaseDERBlob->pbData[i]) ;
  printf("\n") ;
  for ( i = 0 ; i < ctv1.BaseDERBlob->cbData ; i++ )
    printf("%c    ", ctv1.BaseDERBlob->pbData[i]) ;
  printf("\n\n") ;


  CTaggedValue ctv2(CONTEXT_SPECIFIC, CONSTRUCTED, 0, _FALSE, _TRUE, cvs1) ;
  ctv2.decode() ;
  printf("Class for ctv2 is : %x\n", ctv2.Class) ;
  printf("Encoding for ctv2 is : %x\n", ctv2.Encoding) ;
  printf("TagNumber for ctv2 is : %x\n", ctv2.TagNumber) ;
  printf("Value represented by ctv21 is : ") ;
  for ( i = 0 ; i < ctv2.cbData ; i++ )
    printf("%c", ctv2.pbData[i]) ;
  printf("\n\n") ;

  printf("ctv2.BaseDERBlob.cbdata : %d\n", ctv2.BaseDERBlob->cbData) ;
  printf("ctv2.BaseDERBlob.pbData :\n") ;
  for ( i = 0 ; i < ctv2.BaseDERBlob->cbData ; i++ )
    printf("0x%02x ", ctv2.BaseDERBlob->pbData[i]) ;
  printf("\n") ;
  for ( i = 0 ; i < ctv2.BaseDERBlob->cbData ; i++ )
    printf("%c    ", ctv2.BaseDERBlob->pbData[i]) ;
  printf("\n\n") ;




/*
  CTaggedValue ctv1(APPLICATION, PRIMITIVE, 3, _TRUE, cvs1) ;

  ctv1.decode() ;
  printf("Class for ctv1 is : %x\n", ctv1.Class) ;
  printf("Encoding for ctv1 is : %x\n", ctv1.Encoding) ;
  printf("TagNumber for ctv1 is : %x\n", ctv1.TagNumber) ;
  printf("Value represented by ctv11 is : ") ;
  for ( i = 0 ; i < ctv1.cbData ; i++ )
    printf("%c", ctv1.pbData[i]) ;
  printf("\n\n") ;

  printf("ctv1.BaseDERBlob.cbdata : %d\n", ctv1.BaseDERBlob->cbData) ;
  printf("ctv1.BaseDERBlob.pbData :\n") ;
  for ( i = 0 ; i < ctv1.BaseDERBlob->cbData ; i++ )
    printf("0x%02x ", ctv1.BaseDERBlob->pbData[i]) ;
  printf("\n") ;
  for ( i = 0 ; i < ctv1.BaseDERBlob->cbData ; i++ )
    printf("%c    ", ctv1.BaseDERBlob->pbData[i]) ;
  printf("\n\n") ;

  CTaggedValue ctv2(CONTEXT_SPECIFIC, CONSTRUCTED, 2, _FALSE, ctv1) ;

  ctv2.decode() ;
  printf("Class for ctv2 is : %x\n", ctv2.Class) ;
  printf("Encoding for ctv2 is : %x\n", ctv2.Encoding) ;
  printf("TagNumber for ctv2 is : %x\n", ctv2.TagNumber) ;
  printf("Value represented by ctv21 is : ") ;
  for ( i = 0 ; i < ctv2.cbData ; i++ )
    printf("%c", ctv2.pbData[i]) ;
  printf("\n\n") ;

  printf("ctv2.BaseDERBlob.cbdata : %d\n", ctv2.BaseDERBlob->cbData) ;
  printf("ctv2.BaseDERBlob.pbData :\n") ;
  for ( i = 0 ; i < ctv2.BaseDERBlob->cbData ; i++ )
    printf("0x%02x ", ctv2.BaseDERBlob->pbData[i]) ;
  printf("\n") ;
  for ( i = 0 ; i < ctv2.BaseDERBlob->cbData ; i++ )
    printf("%c    ", ctv2.BaseDERBlob->pbData[i]) ;
  printf("\n\n") ;

  CTaggedValue ctv3(APPLICATION, CONSTRUCTED, 7, _TRUE, ctv2) ;

  ctv3.decode() ;
  printf("Class for ctv3 is : %x\n", ctv3.Class) ;
  printf("Encoding for ctv3 is : %x\n", ctv3.Encoding) ;
  printf("TagNumber for ctv3 is : %x\n", ctv3.TagNumber) ;
  printf("Value represented by ctv31 is : ") ;
  for ( i = 0 ; i < ctv3.cbData ; i++ )
    printf("%c", ctv3.pbData[i]) ;
  printf("\n\n") ;

  printf("ctv3.BaseDERBlob.cbdata : %d\n", ctv3.BaseDERBlob->cbData) ;
  printf("ctv3.BaseDERBlob.pbData :\n") ;
  for ( i = 0 ; i < ctv3.BaseDERBlob->cbData ; i++ )
    printf("0x%02x ", ctv3.BaseDERBlob->pbData[i]) ;
  printf("\n") ;
  for ( i = 0 ; i < ctv3.BaseDERBlob->cbData ; i++ )
    printf("%c    ", ctv3.BaseDERBlob->pbData[i]) ;
  printf("\n\n") ;

  CTaggedValue ctv4(CONTEXT_SPECIFIC, PRIMITIVE, 2, _TRUE, ctv1) ;

  ctv4.decode() ;
  printf("Class for ctv4 is : %x\n", ctv4.Class) ;
  printf("Encoding for ctv4 is : %x\n", ctv4.Encoding) ;
  printf("TagNumber for ctv4 is : %x\n", ctv4.TagNumber) ;
  printf("Value represented by ctv41 is : ") ;
  for ( i = 0 ; i < ctv4.cbData ; i++ )
    printf("%c", ctv4.pbData[i]) ;
  printf("\n\n") ;

  printf("ctv4.BaseDERBlob.cbdata : %d\n", ctv4.BaseDERBlob->cbData) ;
  printf("ctv4.BaseDERBlob.pbData :\n") ;
  for ( i = 0 ; i < ctv4.BaseDERBlob->cbData ; i++ )
    printf("0x%02x ", ctv4.BaseDERBlob->pbData[i]) ;
  printf("\n") ;
  for ( i = 0 ; i < ctv4.BaseDERBlob->cbData ; i++ )
    printf("%c    ", ctv4.BaseDERBlob->pbData[i]) ;
  printf("\n\n") ;
*/

  return(1) ;
}

