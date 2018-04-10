
#include <stdio.h>
//#include "c:\temp\generic.h"


#include <stdlib.h>


#include "bsafelite.h"
#include "bsafe.h"
#include "integrate.h"

main()
{
	POINTER randomBuffer;

	HashBegin(0, NULL);

	randomBuffer = (POINTER)T_malloc(128);

	GenerateRandomBlock(randomBuffer, 128);
	
}