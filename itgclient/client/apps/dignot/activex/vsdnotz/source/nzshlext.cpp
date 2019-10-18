// Implements the ShellExtInit interface

#include "stdafx.h"
#include <comutil.h>
#include "ptav3.h"
#include "vsdnotz.h"
#include "nzuser.h"
#include "notarize.h"
#include "nzutils.h"
#include "nzmacros.h"
#include "VSNZ.h"

/*
Working -	This function sets the 'm_pSelItems' member variable. This is used to query 
			for the files which have been selected.
			For more information regarding this function refer to the Windows documentation of 
			the IShellExtInit interface.
*/
STDMETHODIMP CVSNZ::Initialize(LPCITEMIDLIST pIDFolder, LPDATAOBJECT pDataObj, HKEY hKeyID)
{
	// Initialize can be called more than once
	RELEASE_INTERFACE_PTR(m_pSelItems)

	// Duplicate the data object
	if(pDataObj)
    {
    	m_pSelItems = pDataObj;
    	m_pSelItems->AddRef();
    }

	return NOERROR;
}