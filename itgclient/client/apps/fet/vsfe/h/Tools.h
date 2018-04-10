/**************************************************************************
   #include statements
**************************************************************************/

#include "resource.h"

typedef struct
   {
   UINT  uImageSet;
   UINT  idCommand;
   int   iImage;
   int   idString;
   BYTE  bState;
   BYTE  bStyle;
   }MYTOOLINFO, *LPMYTOOLINFO;

extern MYTOOLINFO g_Tools[];
