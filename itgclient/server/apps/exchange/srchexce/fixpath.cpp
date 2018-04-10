#include <string.h>
#include <stdlib.h>

#include "vsstring.h"
#include "ntfuncs.h"

void FixPath(VSString& szFile, VSString documentRoot)
{
/*----------- Make sure file access is restricted to document root ----------*/
  VSString fix = "..\\";
  documentRoot = fix + documentRoot + "\\";
  if( strncmp(szFile, documentRoot, documentRoot.Length()) != 0 )
  {
    // path doesn't begin with documentRoot, so prefix it.
    szFile = documentRoot + szFile ;
  }
/*---- Now make sure the full path doesn't contain a relative component. ----*/

  if( strstr(((const char *)szFile)+2, "..") )
  {
    char *ptr = szFile.GetBuffer() ;
    ptr = basename(ptr) ;
    szFile = documentRoot + VSString(ptr);
  }
}
