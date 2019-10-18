#include "import.h"
#include "export.h"
#include "ptav3.h"

EXTERN_C IVSP12Import*	P12Import_GetInstance (IVSPTA* pPTA);
EXTERN_C unsigned int	P12Import_ImportP12 (IVSP12Import* pP12Import, int nType, wchar_t* pwstrP12, int nLen, wchar_t** pwstrSerNum, wchar_t** pwstrIssDN);

EXTERN_C IVSP12Export*	P12Export_GetInstance (IVSPTA* pPTA);
EXTERN_C unsigned int	P12Export_ExportP12(IVSP12Export* pP12Export, int nOutputType, int nFlags, wchar_t* pwstrFile, int nLen);
EXTERN_C int	P12Export_get_PasswdQuality(IVSP12Export* pP12Export);
EXTERN_C unsigned int	P12Export_set_PasswdQuality(IVSP12Export* pP12Export, int newVal);
EXTERN_C int	P12Export_get_PasswdLength(IVSP12Export* pP12Export);
EXTERN_C unsigned int	P12Export_set_PasswdLength(IVSP12Export* pP12Export, int newVal);
