#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <OctetString.h>
#include <TaggedValue.h>
#include <ObjectIdentifier.h>
#include <BaseDERCollection.h>
#include <BaseDERHierarchy.h>
#include <Sequence.h>
#include <DataTypes.h>

int main()
{
	_DWORD			i = 0 ;
	_CHAR			szInput1[] = {"Abhay"} ;
	COctetString	cos1(strlen((const char *)szInput1), szInput1) ;

	_CHAR			szInput2[] = {"Ranade"} ;
	COctetString	cos2(strlen((const char *)szInput2), szInput2) ;

	CBaseDERCollection	cbdc1 ;
	cbdc1 = cos1 + cos2 ;

	CTaggedValue	ctv1(UNIVERSAL, CONSTRUCTED, OCTET_STRING, _TRUE, cbdc1) ;
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

	CTaggedValue	ctv2(CONTEXT_SPECIFIC, CONSTRUCTED, 0, _FALSE, _TRUE, ctv1) ;
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

	_CHAR			szOID[] = {"1.56.2.3.4"} ;
	CObjectIdentifier	coi(strlen((const char *)szOID), szOID) ;

	CBaseDERCollection	cbdc ;
	cbdc = coi + ctv2 ;

	CSequence		cseq(cbdc, _TRUE) ;

	printf("cseq.BaseDERBlob.cbdata : %d\n", cseq.BaseDERBlob->cbData) ;
	printf("cseq.BaseDERBlob.pbData :\n") ;
	for ( i = 0 ; i < cseq.BaseDERBlob->cbData ; i++ )
		printf("0x%02x ", cseq.BaseDERBlob->pbData[i]) ;
	printf("\n") ;
	for ( i = 0 ; i < cseq.BaseDERBlob->cbData ; i++ )
		printf("%c    ", cseq.BaseDERBlob->pbData[i]) ;
	printf("\n\n") ;

	CBaseDERCollection	cbdc3 ;
	cbdc3 = cseq + cos1 ;

	printf("cbdc3.BaseDERBlob.cbdata : %d\n", cbdc3.BaseDERBlob->cbData) ;
	printf("cbdc3.BaseDERBlob.pbData :\n") ;
	for ( i = 0 ; i < cbdc3.BaseDERBlob->cbData ; i++ )
		printf("0x%02x ", cbdc3.BaseDERBlob->pbData[i]) ;
	printf("\n") ;
	for ( i = 0 ; i < cbdc3.BaseDERBlob->cbData ; i++ )
		printf("%c    ", cbdc3.BaseDERBlob->pbData[i]) ;
	printf("\n\n") ;

	CBaseDERHierarchy	cbdh(cbdc3) ;
	
	
	return 1 ;
}

