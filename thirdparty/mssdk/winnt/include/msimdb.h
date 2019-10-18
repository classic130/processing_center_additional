//--------------------------------------------------------------------
//
// Microsoft In-Memory Database 
// (C) Copyright 1998 By Microsoft Corporation.
//
//
//--------------------------------------------------------------------

#ifndef  _MSIMDB_H_
	#define  _MSIMDB_H_

	//
	// MSIMDB property specific definitions
	//
	// The GUID for the MSIMDB specific property set on the session
	//
	// {AFE68CE9-C367-11d1-AC4F-0000F8758E41}
	_declspec(selectany) extern const GUID DBPROPSET_IMDBSESSION = 
			{ 0xafe68ce9, 0xc367, 0x11d1, { 0xac, 0x4f, 0x0, 0x0, 0xf8, 0x75, 0x8e, 0x41 } };


	//----------------------------------------------------------------------------
	// Props for DBPROPSET_IMDBSESSION
	//
	#define IMDBPROP_SESS_ISOLEVEL				0x01	// I4 
														//		DBPROPVAL_TI_READCOMMITTED (Default), 
														//		DBPROPVAL_TI_REPEATABLEREAD, 
														//		DBPROPVAL_TI_SERIALIZABLE

	#define IMDBPROP_SESS_OPENROWSET_TIMEOUT	0x02	// I2 0 (30s wait, Default) 
	#define IMDBPROP_SESS_SMALL_TABLES			0x03	// BOOL VARIANT_FALSE (Default)
	#define IMDBPROP_SESS_PESSIMISTIC_LOCKING	0x04	// BOOL VARIANT_FALSE (Default)
	#define IMDBPROP_SESS_WRITE_THROUGH			0x05	// BOOL VARIANT_FALSE (Default)


	#define IMDBPROP_SESS_OPENROWSET_TIMEOUT_DEFAULT_VALUE  30
	#define IMDBPROP_SESS_OPENROWSET_TIMEOUT_MIN_VALUE      0
	#define IMDBPROP_SESS_OPENROWSET_TIMEOUT_MAX_VALUE      0xffff

#endif // _MSIMDB_H_

//
// End Of File
//



