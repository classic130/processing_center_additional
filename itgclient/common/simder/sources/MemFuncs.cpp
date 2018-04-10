/******************************************************************
	This file provides functionality to support special memory 
	related handling. The functionality includes two components,viz.,
	a data structure that holds a function pointer and the other is
	the default implementation of that function. The formal
	parameters taken by this function are quite generic and 
	have been defined in this file.

	The function pointer is invoked by all SimDer Class destructors
	to erase memory. The memory erase operation could be something
	that does a so called "safe" erase of memory allocated while
	using SimDer objects.

    An outside application can change the function pointer contents
	and provide it's own implementation that erases memory.
******************************************************************/

#include <DataTypes.h>

_DWORD SimDerMemErase(_DWORD cbData, _PBYTE pbData)
{
	return 0 ;
}

_DWORD		(*SIMDER_MemErase) (_DWORD cbData, _PBYTE pbData) = &SimDerMemErase ;
