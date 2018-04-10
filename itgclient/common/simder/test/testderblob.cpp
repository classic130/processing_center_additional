#include <DERBlob.h>
#include <string.h>
#include <stdio.h>

int main()
{
  char		string[] = {"This is fun!!"} ;
  int		i = 0 ;

  CDERBlob	derblob1 ;

  printf("\n\n") ;

  CDERBlob	derblob2(121) ;

  printf("derblob2(121):\nderblob2.cbData : %d\n\n", derblob2.cbData) ;

  CDERBlob	derblob3((_DWORD)strlen(string), (_PBYTE)string) ;

  printf("derblob3.cbData : %d\n", derblob3.cbData) ;
  printf("derblob3.pbData : ") ;
  for( i = 0 ; i < derblob3.cbData ; i++ )
    printf("%c", derblob3.pbData[i]) ;
  printf("\n\n") ;

  CDERBlob	derblob4(derblob3) ;

  printf("derblob4(derblob3):\nderblob4.cbData : %d\n", derblob4.cbData) ;
  printf("derblob4.pbData : ") ;
  for( i = 0 ; i < derblob4.cbData ; i++ )
    printf("%c", derblob4.pbData[i]) ;
  printf("\n\n") ;

  derblob2 = derblob4 ;

  printf("derblob2 = derblob4 :\nderblob2.cbData : %d\n", derblob2.cbData) ;
  printf("derblob2.pbData : ") ;
  for( i = 0 ; i < derblob2.cbData ; i++ )
    printf("%c", derblob2.pbData[i]) ;
  printf("\n\n") ;

  derblob2 = derblob4 + derblob4 ;
  printf("derblob2 = derblob4 + derblob4 :\nderblob2.cbData : %d\n", derblob2.cbData) ;
  printf("derblob2.pbData : ") ;
  for( i = 0 ; i < derblob2.cbData ; i++ )
    printf("%c", derblob2.pbData[i]) ;
  printf("\n\n") ;

  CDERBlob 	derblob5, derblob6 ;

  derblob6 = derblob4 + derblob5 ;
  printf("derblob6 = derblob4 + derblob5(empty) :\nderblob6.cbData : %d\n", derblob6.cbData) ;
  printf("derblob6.pbData : ") ;
  for( i = 0 ; i < derblob6.cbData ; i++ )
    printf("%c", derblob6.pbData[i]) ;
  printf("\n\n") ;

  return(1) ;

}

