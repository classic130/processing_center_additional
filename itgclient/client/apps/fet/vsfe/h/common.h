#ifndef COMMON_H
#define COMMON_H


#ifndef _WIN32_WINNT
#define _WIN32_WINNT  0x0400
#endif

#include <stdio.h>
#include <windows.h>
#include <windowsx.h>
#include <windef.h>
#include <wincrypt.h>
#include <olectl.h>
#include <shlobj.h>
#include <ole2.h>
#include <objbase.h>
#include <shlobj.h>
#include <ServProv.h>
#include <DocObj.h>
#include <Regstr.h>

#include "resource.h"		// resource defns
#include "Commands.h"		// private commands for this project
#include "slist.h"
#include "cryptsup.h"		// the encryption routines
#include "util.h"			// utility fns
#include "dlgprocs.h"		// callbacks for all the dialogs
#include "safedel.h"		// fns for secure delete

#endif // COMMON_H 