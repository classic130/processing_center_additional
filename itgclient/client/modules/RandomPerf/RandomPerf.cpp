// RandomPerf.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
//#include "stdlibrf.h"
#include <stdlib.h>
#include <time.h>

#include "malloc.h"
#include "bsafelite.h"
#include "integrate.h"


int BytesToAscHex
(
	unsigned char* byteRandom,
	int nRandomLen, 
	char*	szHalfAsc
);

int main(int argc, char* argv[])
{
	
    struct tm *newtime;
    time_t long_time;
	unsigned char randomData1[128];
	unsigned int nIndx;
	unsigned int nSample;
	unsigned int nTime;
	char szRandomHalfAscii [1000];

//	printf("Hello World!\n");

    time( &long_time );                /* Get time as long integer. */
    newtime = localtime( &long_time ); /* Convert to local time. */
//    printf( "%.19s \n", asctime( newtime ) );

    nSample = 0;
    for (nIndx = 0; nIndx < 100; ++nIndx)
	{
		nSample++;
		if ( GenerateRandomBlock(randomData1, 128) == -1)
			printf ("\n error in generating random no.");
		else
		{
			BytesToAscHex (randomData1, 128, szRandomHalfAscii);
//			randomData1[127] = '\0';
			//if (nIndx % 8 == 0)
//				printf("\nRandom no. %d is %s", nIndx, szRandomHalfAscii);
				printf("%s", szRandomHalfAscii);
		}
	}

    time( &long_time );                /* Get time as long integer. */
    newtime = localtime( &long_time ); /* Convert to local time. */
//    printf( "%.19s \n", asctime( newtime ) );
//	printf("No. of samples = %d", nSample);

	return 0;
}


int BytesToAscHex
(
	unsigned char* byteRandom,
	int nRandomLen, 
	char*	szHalfAsc
)
{
	::strcpy (szHalfAsc, "");
	char szDigitAscVal[] = "0123456789ABCDEF";
	char szDigit[2];

	szDigit[1] = '\0';
	for(int i=0;i<nRandomLen;++i)
	{
		szDigit[0] = szDigitAscVal[((byteRandom[i] & 0xF0)>>4)];
		::strcat (szHalfAsc, szDigit);
		szDigit[0] = szDigitAscVal[(byteRandom[i] & 0x0F)];
		::strcat (szHalfAsc, szDigit);
	}

	return 1;
}