/* this ALWAYS GENERATED file contains the proxy stub code */


/* File created by MIDL compiler version 5.01.0164 */
/* at Fri Dec 29 16:04:40 2006
 */
/* Compiler settings for .\ConfigChk.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )

#define USE_STUBLESS_PROXY


/* verify that the <rpcproxy.h> version is high enough to compile this file*/
#ifndef __REDQ_RPCPROXY_H_VERSION__
#define __REQUIRED_RPCPROXY_H_VERSION__ 440
#endif


#include "rpcproxy.h"
#ifndef __RPCPROXY_H_VERSION__
#error this stub requires an updated version of <rpcproxy.h>
#endif // __RPCPROXY_H_VERSION__


#include "ConfigChk.h"

#define TYPE_FORMAT_STRING_SIZE   1033                              
#define PROC_FORMAT_STRING_SIZE   211                               

typedef struct _MIDL_TYPE_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ TYPE_FORMAT_STRING_SIZE ];
    } MIDL_TYPE_FORMAT_STRING;

typedef struct _MIDL_PROC_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ PROC_FORMAT_STRING_SIZE ];
    } MIDL_PROC_FORMAT_STRING;


extern const MIDL_TYPE_FORMAT_STRING __MIDL_TypeFormatString;
extern const MIDL_PROC_FORMAT_STRING __MIDL_ProcFormatString;


/* Object interface: IUnknown, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}} */


/* Object interface: IDispatch, ver. 0.0,
   GUID={0x00020400,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}} */


/* Object interface: IConfigChkr, ver. 0.0,
   GUID={0x08F04138,0x8DFC,0x11D2,{0x80,0xE9,0x00,0x60,0x08,0xB0,0x66,0xEE}} */


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IConfigChkr_ServerInfo;

#pragma code_seg(".orpc")
extern const USER_MARSHAL_ROUTINE_QUADRUPLE UserMarshalRoutines[1];

static const MIDL_STUB_DESC Object_StubDesc = 
    {
    0,
    NdrOleAllocate,
    NdrOleFree,
    0,
    0,
    0,
    0,
    0,
    __MIDL_TypeFormatString.Format,
    1, /* -error bounds_check flag */
    0x20000, /* Ndr library version */
    0,
    0x50100a4, /* MIDL Version 5.1.164 */
    0,
    UserMarshalRoutines,
    0,  /* notify & notify_flag routine table */
    1,  /* Flags */
    0,  /* Reserved3 */
    0,  /* Reserved4 */
    0   /* Reserved5 */
    };

static const unsigned short IConfigChkr_FormatStringOffsetTable[] = 
    {
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    0,
    40,
    80,
    108,
    142,
    170
    };

static const MIDL_SERVER_INFO IConfigChkr_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IConfigChkr_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0
    };

static const MIDL_STUBLESS_PROXY_INFO IConfigChkr_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IConfigChkr_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };

CINTERFACE_PROXY_VTABLE(13) _IConfigChkrProxyVtbl = 
{
    &IConfigChkr_ProxyInfo,
    &IID_IConfigChkr,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* (void *)-1 /* IDispatch::GetTypeInfoCount */ ,
    0 /* (void *)-1 /* IDispatch::GetTypeInfo */ ,
    0 /* (void *)-1 /* IDispatch::GetIDsOfNames */ ,
    0 /* IDispatch_Invoke_Proxy */ ,
    (void *)-1 /* IConfigChkr::GetVersion */ ,
    (void *)-1 /* IConfigChkr::VerCompare */ ,
    (void *)-1 /* IConfigChkr::CheckMSEnhCSP */ ,
    (void *)-1 /* IConfigChkr::FixEnhCSP */ ,
    (void *)-1 /* IConfigChkr::ChkWindowsLogin */ ,
    (void *)-1 /* IConfigChkr::CheckKeyGen */
};


static const PRPC_STUB_FUNCTION IConfigChkr_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2
};

CInterfaceStubVtbl _IConfigChkrStubVtbl =
{
    &IID_IConfigChkr,
    &IConfigChkr_ServerInfo,
    13,
    &IConfigChkr_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};

#pragma data_seg(".rdata")

static const USER_MARSHAL_ROUTINE_QUADRUPLE UserMarshalRoutines[1] = 
        {
            
            {
            VARIANT_UserSize
            ,VARIANT_UserMarshal
            ,VARIANT_UserUnmarshal
            ,VARIANT_UserFree
            }

        };


#if !defined(__RPC_WIN32__)
#error  Invalid build platform for this stub.
#endif

#if !(TARGET_IS_NT40_OR_LATER)
#error You need a Windows NT 4.0 or later to run this stub because it uses these features:
#error   -Oif or -Oicf, [wire_marshal] or [user_marshal] attribute, more than 32 methods in the interface.
#error However, your C/C++ compilation flags indicate you intend to run this app on earlier systems.
#error This app will die there with the RPC_X_WRONG_STUB_VERSION error.
#endif


static const MIDL_PROC_FORMAT_STRING __MIDL_ProcFormatString =
    {
        0,
        {

	/* Procedure GetVersion */

			0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/*  2 */	NdrFcLong( 0x0 ),	/* 0 */
/*  6 */	NdrFcShort( 0x7 ),	/* 7 */
#ifndef _ALPHA_
/*  8 */	NdrFcShort( 0x14 ),	/* x86, MIPS, PPC Stack size/offset = 20 */
#else
			NdrFcShort( 0x28 ),	/* Alpha Stack size/offset = 40 */
#endif
/* 10 */	NdrFcShort( 0x0 ),	/* 0 */
/* 12 */	NdrFcShort( 0x10 ),	/* 16 */
/* 14 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x4,		/* 4 */

	/* Parameter i_pvarFile */

/* 16 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
#ifndef _ALPHA_
/* 18 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 20 */	NdrFcShort( 0x3e8 ),	/* Type Offset=1000 */

	/* Parameter o_pvarVersion */

/* 22 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
#ifndef _ALPHA_
/* 24 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 26 */	NdrFcShort( 0x3e8 ),	/* Type Offset=1000 */

	/* Parameter o_lResult */

/* 28 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
#ifndef _ALPHA_
/* 30 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 32 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 34 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 36 */	NdrFcShort( 0x10 ),	/* x86, MIPS, PPC Stack size/offset = 16 */
#else
			NdrFcShort( 0x20 ),	/* Alpha Stack size/offset = 32 */
#endif
/* 38 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure VerCompare */

/* 40 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 42 */	NdrFcLong( 0x0 ),	/* 0 */
/* 46 */	NdrFcShort( 0x8 ),	/* 8 */
#ifndef _ALPHA_
/* 48 */	NdrFcShort( 0x14 ),	/* x86, MIPS, PPC Stack size/offset = 20 */
#else
			NdrFcShort( 0x28 ),	/* Alpha Stack size/offset = 40 */
#endif
/* 50 */	NdrFcShort( 0x0 ),	/* 0 */
/* 52 */	NdrFcShort( 0x10 ),	/* 16 */
/* 54 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x4,		/* 4 */

	/* Parameter i_pvarVer1 */

/* 56 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
#ifndef _ALPHA_
/* 58 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 60 */	NdrFcShort( 0x3e8 ),	/* Type Offset=1000 */

	/* Parameter i_pvarVer2 */

/* 62 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
#ifndef _ALPHA_
/* 64 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 66 */	NdrFcShort( 0x3e8 ),	/* Type Offset=1000 */

	/* Parameter o_plResult */

/* 68 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
#ifndef _ALPHA_
/* 70 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 72 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 74 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 76 */	NdrFcShort( 0x10 ),	/* x86, MIPS, PPC Stack size/offset = 16 */
#else
			NdrFcShort( 0x20 ),	/* Alpha Stack size/offset = 32 */
#endif
/* 78 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure CheckMSEnhCSP */

/* 80 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 82 */	NdrFcLong( 0x0 ),	/* 0 */
/* 86 */	NdrFcShort( 0x9 ),	/* 9 */
#ifndef _ALPHA_
/* 88 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 90 */	NdrFcShort( 0x0 ),	/* 0 */
/* 92 */	NdrFcShort( 0x10 ),	/* 16 */
/* 94 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter o_lRetVal */

/* 96 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
#ifndef _ALPHA_
/* 98 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 100 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 102 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 104 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 106 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure FixEnhCSP */

/* 108 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 110 */	NdrFcLong( 0x0 ),	/* 0 */
/* 114 */	NdrFcShort( 0xa ),	/* 10 */
#ifndef _ALPHA_
/* 116 */	NdrFcShort( 0x10 ),	/* x86, MIPS, PPC Stack size/offset = 16 */
#else
			NdrFcShort( 0x20 ),	/* Alpha Stack size/offset = 32 */
#endif
/* 118 */	NdrFcShort( 0x0 ),	/* 0 */
/* 120 */	NdrFcShort( 0x10 ),	/* 16 */
/* 122 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x3,		/* 3 */

	/* Parameter i_pvarEnhCSPVer */

/* 124 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
#ifndef _ALPHA_
/* 126 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 128 */	NdrFcShort( 0x3e8 ),	/* Type Offset=1000 */

	/* Parameter o_plRetVal */

/* 130 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
#ifndef _ALPHA_
/* 132 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 134 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 136 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 138 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 140 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure ChkWindowsLogin */

/* 142 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 144 */	NdrFcLong( 0x0 ),	/* 0 */
/* 148 */	NdrFcShort( 0xb ),	/* 11 */
#ifndef _ALPHA_
/* 150 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 152 */	NdrFcShort( 0x0 ),	/* 0 */
/* 154 */	NdrFcShort( 0x10 ),	/* 16 */
/* 156 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter o_lResult */

/* 158 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
#ifndef _ALPHA_
/* 160 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 162 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 164 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 166 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 168 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure CheckKeyGen */

/* 170 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 172 */	NdrFcLong( 0x0 ),	/* 0 */
/* 176 */	NdrFcShort( 0xc ),	/* 12 */
#ifndef _ALPHA_
/* 178 */	NdrFcShort( 0x14 ),	/* x86, MIPS, PPC Stack size/offset = 20 */
#else
			NdrFcShort( 0x28 ),	/* Alpha Stack size/offset = 40 */
#endif
/* 180 */	NdrFcShort( 0x0 ),	/* 0 */
/* 182 */	NdrFcShort( 0x8 ),	/* 8 */
/* 184 */	0x7,		/* Oi2 Flags:  srv must size, clt must size, has return, */
			0x4,		/* 4 */

	/* Parameter i_pvarProvName */

/* 186 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
#ifndef _ALPHA_
/* 188 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 190 */	NdrFcShort( 0x3e8 ),	/* Type Offset=1000 */

	/* Parameter i_pvarKeyFlags */

/* 192 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
#ifndef _ALPHA_
/* 194 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 196 */	NdrFcShort( 0x3e8 ),	/* Type Offset=1000 */

	/* Parameter o_pvarResult */

/* 198 */	NdrFcShort( 0x4113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=16 */
#ifndef _ALPHA_
/* 200 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 202 */	NdrFcShort( 0x3fe ),	/* Type Offset=1022 */

	/* Return value */

/* 204 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 206 */	NdrFcShort( 0x10 ),	/* x86, MIPS, PPC Stack size/offset = 16 */
#else
			NdrFcShort( 0x20 ),	/* Alpha Stack size/offset = 32 */
#endif
/* 208 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

			0x0
        }
    };

static const MIDL_TYPE_FORMAT_STRING __MIDL_TypeFormatString =
    {
        0,
        {
			NdrFcShort( 0x0 ),	/* 0 */
/*  2 */	
			0x11, 0x0,	/* FC_RP */
/*  4 */	NdrFcShort( 0x3e4 ),	/* Offset= 996 (1000) */
/*  6 */	
			0x12, 0x0,	/* FC_UP */
/*  8 */	NdrFcShort( 0x3cc ),	/* Offset= 972 (980) */
/* 10 */	
			0x2b,		/* FC_NON_ENCAPSULATED_UNION */
			0x9,		/* FC_ULONG */
/* 12 */	0x7,		/* Corr desc: FC_USHORT */
			0x0,		/*  */
/* 14 */	NdrFcShort( 0xfff8 ),	/* -8 */
/* 16 */	NdrFcShort( 0x2 ),	/* Offset= 2 (18) */
/* 18 */	NdrFcShort( 0x10 ),	/* 16 */
/* 20 */	NdrFcShort( 0x2f ),	/* 47 */
/* 22 */	NdrFcLong( 0x14 ),	/* 20 */
/* 26 */	NdrFcShort( 0x800b ),	/* Simple arm type: FC_HYPER */
/* 28 */	NdrFcLong( 0x3 ),	/* 3 */
/* 32 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 34 */	NdrFcLong( 0x11 ),	/* 17 */
/* 38 */	NdrFcShort( 0x8001 ),	/* Simple arm type: FC_BYTE */
/* 40 */	NdrFcLong( 0x2 ),	/* 2 */
/* 44 */	NdrFcShort( 0x8006 ),	/* Simple arm type: FC_SHORT */
/* 46 */	NdrFcLong( 0x4 ),	/* 4 */
/* 50 */	NdrFcShort( 0x800a ),	/* Simple arm type: FC_FLOAT */
/* 52 */	NdrFcLong( 0x5 ),	/* 5 */
/* 56 */	NdrFcShort( 0x800c ),	/* Simple arm type: FC_DOUBLE */
/* 58 */	NdrFcLong( 0xb ),	/* 11 */
/* 62 */	NdrFcShort( 0x8006 ),	/* Simple arm type: FC_SHORT */
/* 64 */	NdrFcLong( 0xa ),	/* 10 */
/* 68 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 70 */	NdrFcLong( 0x6 ),	/* 6 */
/* 74 */	NdrFcShort( 0xe8 ),	/* Offset= 232 (306) */
/* 76 */	NdrFcLong( 0x7 ),	/* 7 */
/* 80 */	NdrFcShort( 0x800c ),	/* Simple arm type: FC_DOUBLE */
/* 82 */	NdrFcLong( 0x8 ),	/* 8 */
/* 86 */	NdrFcShort( 0xe2 ),	/* Offset= 226 (312) */
/* 88 */	NdrFcLong( 0xd ),	/* 13 */
/* 92 */	NdrFcShort( 0xf4 ),	/* Offset= 244 (336) */
/* 94 */	NdrFcLong( 0x9 ),	/* 9 */
/* 98 */	NdrFcShort( 0x100 ),	/* Offset= 256 (354) */
/* 100 */	NdrFcLong( 0x2000 ),	/* 8192 */
/* 104 */	NdrFcShort( 0x10c ),	/* Offset= 268 (372) */
/* 106 */	NdrFcLong( 0x24 ),	/* 36 */
/* 110 */	NdrFcShort( 0x31a ),	/* Offset= 794 (904) */
/* 112 */	NdrFcLong( 0x4024 ),	/* 16420 */
/* 116 */	NdrFcShort( 0x314 ),	/* Offset= 788 (904) */
/* 118 */	NdrFcLong( 0x4011 ),	/* 16401 */
/* 122 */	NdrFcShort( 0x312 ),	/* Offset= 786 (908) */
/* 124 */	NdrFcLong( 0x4002 ),	/* 16386 */
/* 128 */	NdrFcShort( 0x310 ),	/* Offset= 784 (912) */
/* 130 */	NdrFcLong( 0x4003 ),	/* 16387 */
/* 134 */	NdrFcShort( 0x30e ),	/* Offset= 782 (916) */
/* 136 */	NdrFcLong( 0x4014 ),	/* 16404 */
/* 140 */	NdrFcShort( 0x30c ),	/* Offset= 780 (920) */
/* 142 */	NdrFcLong( 0x4004 ),	/* 16388 */
/* 146 */	NdrFcShort( 0x30a ),	/* Offset= 778 (924) */
/* 148 */	NdrFcLong( 0x4005 ),	/* 16389 */
/* 152 */	NdrFcShort( 0x308 ),	/* Offset= 776 (928) */
/* 154 */	NdrFcLong( 0x400b ),	/* 16395 */
/* 158 */	NdrFcShort( 0x2f2 ),	/* Offset= 754 (912) */
/* 160 */	NdrFcLong( 0x400a ),	/* 16394 */
/* 164 */	NdrFcShort( 0x2f0 ),	/* Offset= 752 (916) */
/* 166 */	NdrFcLong( 0x4006 ),	/* 16390 */
/* 170 */	NdrFcShort( 0x2fa ),	/* Offset= 762 (932) */
/* 172 */	NdrFcLong( 0x4007 ),	/* 16391 */
/* 176 */	NdrFcShort( 0x2f0 ),	/* Offset= 752 (928) */
/* 178 */	NdrFcLong( 0x4008 ),	/* 16392 */
/* 182 */	NdrFcShort( 0x2f2 ),	/* Offset= 754 (936) */
/* 184 */	NdrFcLong( 0x400d ),	/* 16397 */
/* 188 */	NdrFcShort( 0x2f0 ),	/* Offset= 752 (940) */
/* 190 */	NdrFcLong( 0x4009 ),	/* 16393 */
/* 194 */	NdrFcShort( 0x2ee ),	/* Offset= 750 (944) */
/* 196 */	NdrFcLong( 0x6000 ),	/* 24576 */
/* 200 */	NdrFcShort( 0x2ec ),	/* Offset= 748 (948) */
/* 202 */	NdrFcLong( 0x400c ),	/* 16396 */
/* 206 */	NdrFcShort( 0x2ea ),	/* Offset= 746 (952) */
/* 208 */	NdrFcLong( 0x10 ),	/* 16 */
/* 212 */	NdrFcShort( 0x8002 ),	/* Simple arm type: FC_CHAR */
/* 214 */	NdrFcLong( 0x12 ),	/* 18 */
/* 218 */	NdrFcShort( 0x8006 ),	/* Simple arm type: FC_SHORT */
/* 220 */	NdrFcLong( 0x13 ),	/* 19 */
/* 224 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 226 */	NdrFcLong( 0x15 ),	/* 21 */
/* 230 */	NdrFcShort( 0x800b ),	/* Simple arm type: FC_HYPER */
/* 232 */	NdrFcLong( 0x16 ),	/* 22 */
/* 236 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 238 */	NdrFcLong( 0x17 ),	/* 23 */
/* 242 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 244 */	NdrFcLong( 0xe ),	/* 14 */
/* 248 */	NdrFcShort( 0x2c8 ),	/* Offset= 712 (960) */
/* 250 */	NdrFcLong( 0x400e ),	/* 16398 */
/* 254 */	NdrFcShort( 0x2ce ),	/* Offset= 718 (972) */
/* 256 */	NdrFcLong( 0x4010 ),	/* 16400 */
/* 260 */	NdrFcShort( 0x2cc ),	/* Offset= 716 (976) */
/* 262 */	NdrFcLong( 0x4012 ),	/* 16402 */
/* 266 */	NdrFcShort( 0x286 ),	/* Offset= 646 (912) */
/* 268 */	NdrFcLong( 0x4013 ),	/* 16403 */
/* 272 */	NdrFcShort( 0x284 ),	/* Offset= 644 (916) */
/* 274 */	NdrFcLong( 0x4015 ),	/* 16405 */
/* 278 */	NdrFcShort( 0x282 ),	/* Offset= 642 (920) */
/* 280 */	NdrFcLong( 0x4016 ),	/* 16406 */
/* 284 */	NdrFcShort( 0x278 ),	/* Offset= 632 (916) */
/* 286 */	NdrFcLong( 0x4017 ),	/* 16407 */
/* 290 */	NdrFcShort( 0x272 ),	/* Offset= 626 (916) */
/* 292 */	NdrFcLong( 0x0 ),	/* 0 */
/* 296 */	NdrFcShort( 0x0 ),	/* Offset= 0 (296) */
/* 298 */	NdrFcLong( 0x1 ),	/* 1 */
/* 302 */	NdrFcShort( 0x0 ),	/* Offset= 0 (302) */
/* 304 */	NdrFcShort( 0xffffffff ),	/* Offset= -1 (303) */
/* 306 */	
			0x15,		/* FC_STRUCT */
			0x7,		/* 7 */
/* 308 */	NdrFcShort( 0x8 ),	/* 8 */
/* 310 */	0xb,		/* FC_HYPER */
			0x5b,		/* FC_END */
/* 312 */	
			0x12, 0x0,	/* FC_UP */
/* 314 */	NdrFcShort( 0xc ),	/* Offset= 12 (326) */
/* 316 */	
			0x1b,		/* FC_CARRAY */
			0x1,		/* 1 */
/* 318 */	NdrFcShort( 0x2 ),	/* 2 */
/* 320 */	0x9,		/* Corr desc: FC_ULONG */
			0x0,		/*  */
/* 322 */	NdrFcShort( 0xfffc ),	/* -4 */
/* 324 */	0x6,		/* FC_SHORT */
			0x5b,		/* FC_END */
/* 326 */	
			0x17,		/* FC_CSTRUCT */
			0x3,		/* 3 */
/* 328 */	NdrFcShort( 0x8 ),	/* 8 */
/* 330 */	NdrFcShort( 0xfffffff2 ),	/* Offset= -14 (316) */
/* 332 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 334 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 336 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 338 */	NdrFcLong( 0x0 ),	/* 0 */
/* 342 */	NdrFcShort( 0x0 ),	/* 0 */
/* 344 */	NdrFcShort( 0x0 ),	/* 0 */
/* 346 */	0xc0,		/* 192 */
			0x0,		/* 0 */
/* 348 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 350 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 352 */	0x0,		/* 0 */
			0x46,		/* 70 */
/* 354 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 356 */	NdrFcLong( 0x20400 ),	/* 132096 */
/* 360 */	NdrFcShort( 0x0 ),	/* 0 */
/* 362 */	NdrFcShort( 0x0 ),	/* 0 */
/* 364 */	0xc0,		/* 192 */
			0x0,		/* 0 */
/* 366 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 368 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 370 */	0x0,		/* 0 */
			0x46,		/* 70 */
/* 372 */	
			0x12, 0x10,	/* FC_UP */
/* 374 */	NdrFcShort( 0x2 ),	/* Offset= 2 (376) */
/* 376 */	
			0x12, 0x0,	/* FC_UP */
/* 378 */	NdrFcShort( 0x1fc ),	/* Offset= 508 (886) */
/* 380 */	
			0x2a,		/* FC_ENCAPSULATED_UNION */
			0x49,		/* 73 */
/* 382 */	NdrFcShort( 0x18 ),	/* 24 */
/* 384 */	NdrFcShort( 0xa ),	/* 10 */
/* 386 */	NdrFcLong( 0x8 ),	/* 8 */
/* 390 */	NdrFcShort( 0x58 ),	/* Offset= 88 (478) */
/* 392 */	NdrFcLong( 0xd ),	/* 13 */
/* 396 */	NdrFcShort( 0x78 ),	/* Offset= 120 (516) */
/* 398 */	NdrFcLong( 0x9 ),	/* 9 */
/* 402 */	NdrFcShort( 0x94 ),	/* Offset= 148 (550) */
/* 404 */	NdrFcLong( 0xc ),	/* 12 */
/* 408 */	NdrFcShort( 0xbc ),	/* Offset= 188 (596) */
/* 410 */	NdrFcLong( 0x24 ),	/* 36 */
/* 414 */	NdrFcShort( 0x114 ),	/* Offset= 276 (690) */
/* 416 */	NdrFcLong( 0x800d ),	/* 32781 */
/* 420 */	NdrFcShort( 0x130 ),	/* Offset= 304 (724) */
/* 422 */	NdrFcLong( 0x10 ),	/* 16 */
/* 426 */	NdrFcShort( 0x148 ),	/* Offset= 328 (754) */
/* 428 */	NdrFcLong( 0x2 ),	/* 2 */
/* 432 */	NdrFcShort( 0x160 ),	/* Offset= 352 (784) */
/* 434 */	NdrFcLong( 0x3 ),	/* 3 */
/* 438 */	NdrFcShort( 0x178 ),	/* Offset= 376 (814) */
/* 440 */	NdrFcLong( 0x14 ),	/* 20 */
/* 444 */	NdrFcShort( 0x190 ),	/* Offset= 400 (844) */
/* 446 */	NdrFcShort( 0xffffffff ),	/* Offset= -1 (445) */
/* 448 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 450 */	NdrFcShort( 0x4 ),	/* 4 */
/* 452 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 454 */	NdrFcShort( 0x0 ),	/* 0 */
/* 456 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 458 */	
			0x48,		/* FC_VARIABLE_REPEAT */
			0x49,		/* FC_FIXED_OFFSET */
/* 460 */	NdrFcShort( 0x4 ),	/* 4 */
/* 462 */	NdrFcShort( 0x0 ),	/* 0 */
/* 464 */	NdrFcShort( 0x1 ),	/* 1 */
/* 466 */	NdrFcShort( 0x0 ),	/* 0 */
/* 468 */	NdrFcShort( 0x0 ),	/* 0 */
/* 470 */	0x12, 0x0,	/* FC_UP */
/* 472 */	NdrFcShort( 0xffffff6e ),	/* Offset= -146 (326) */
/* 474 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 476 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 478 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 480 */	NdrFcShort( 0x8 ),	/* 8 */
/* 482 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 484 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 486 */	NdrFcShort( 0x4 ),	/* 4 */
/* 488 */	NdrFcShort( 0x4 ),	/* 4 */
/* 490 */	0x11, 0x0,	/* FC_RP */
/* 492 */	NdrFcShort( 0xffffffd4 ),	/* Offset= -44 (448) */
/* 494 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 496 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 498 */	
			0x21,		/* FC_BOGUS_ARRAY */
			0x3,		/* 3 */
/* 500 */	NdrFcShort( 0x0 ),	/* 0 */
/* 502 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 504 */	NdrFcShort( 0x0 ),	/* 0 */
/* 506 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 510 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 512 */	NdrFcShort( 0xffffff50 ),	/* Offset= -176 (336) */
/* 514 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 516 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 518 */	NdrFcShort( 0x8 ),	/* 8 */
/* 520 */	NdrFcShort( 0x0 ),	/* 0 */
/* 522 */	NdrFcShort( 0x6 ),	/* Offset= 6 (528) */
/* 524 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 526 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 528 */	
			0x11, 0x0,	/* FC_RP */
/* 530 */	NdrFcShort( 0xffffffe0 ),	/* Offset= -32 (498) */
/* 532 */	
			0x21,		/* FC_BOGUS_ARRAY */
			0x3,		/* 3 */
/* 534 */	NdrFcShort( 0x0 ),	/* 0 */
/* 536 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 538 */	NdrFcShort( 0x0 ),	/* 0 */
/* 540 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 544 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 546 */	NdrFcShort( 0xffffff40 ),	/* Offset= -192 (354) */
/* 548 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 550 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 552 */	NdrFcShort( 0x8 ),	/* 8 */
/* 554 */	NdrFcShort( 0x0 ),	/* 0 */
/* 556 */	NdrFcShort( 0x6 ),	/* Offset= 6 (562) */
/* 558 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 560 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 562 */	
			0x11, 0x0,	/* FC_RP */
/* 564 */	NdrFcShort( 0xffffffe0 ),	/* Offset= -32 (532) */
/* 566 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 568 */	NdrFcShort( 0x4 ),	/* 4 */
/* 570 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 572 */	NdrFcShort( 0x0 ),	/* 0 */
/* 574 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 576 */	
			0x48,		/* FC_VARIABLE_REPEAT */
			0x49,		/* FC_FIXED_OFFSET */
/* 578 */	NdrFcShort( 0x4 ),	/* 4 */
/* 580 */	NdrFcShort( 0x0 ),	/* 0 */
/* 582 */	NdrFcShort( 0x1 ),	/* 1 */
/* 584 */	NdrFcShort( 0x0 ),	/* 0 */
/* 586 */	NdrFcShort( 0x0 ),	/* 0 */
/* 588 */	0x12, 0x0,	/* FC_UP */
/* 590 */	NdrFcShort( 0xfffffdb2 ),	/* Offset= -590 (0) */
/* 592 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 594 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 596 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 598 */	NdrFcShort( 0x8 ),	/* 8 */
/* 600 */	NdrFcShort( 0x0 ),	/* 0 */
/* 602 */	NdrFcShort( 0x6 ),	/* Offset= 6 (608) */
/* 604 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 606 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 608 */	
			0x11, 0x0,	/* FC_RP */
/* 610 */	NdrFcShort( 0xffffffd4 ),	/* Offset= -44 (566) */
/* 612 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 614 */	NdrFcLong( 0x2f ),	/* 47 */
/* 618 */	NdrFcShort( 0x0 ),	/* 0 */
/* 620 */	NdrFcShort( 0x0 ),	/* 0 */
/* 622 */	0xc0,		/* 192 */
			0x0,		/* 0 */
/* 624 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 626 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 628 */	0x0,		/* 0 */
			0x46,		/* 70 */
/* 630 */	
			0x1b,		/* FC_CARRAY */
			0x0,		/* 0 */
/* 632 */	NdrFcShort( 0x1 ),	/* 1 */
/* 634 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 636 */	NdrFcShort( 0x4 ),	/* 4 */
/* 638 */	0x1,		/* FC_BYTE */
			0x5b,		/* FC_END */
/* 640 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 642 */	NdrFcShort( 0x10 ),	/* 16 */
/* 644 */	NdrFcShort( 0x0 ),	/* 0 */
/* 646 */	NdrFcShort( 0xa ),	/* Offset= 10 (656) */
/* 648 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 650 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 652 */	NdrFcShort( 0xffffffd8 ),	/* Offset= -40 (612) */
/* 654 */	0x36,		/* FC_POINTER */
			0x5b,		/* FC_END */
/* 656 */	
			0x12, 0x0,	/* FC_UP */
/* 658 */	NdrFcShort( 0xffffffe4 ),	/* Offset= -28 (630) */
/* 660 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 662 */	NdrFcShort( 0x4 ),	/* 4 */
/* 664 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 666 */	NdrFcShort( 0x0 ),	/* 0 */
/* 668 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 670 */	
			0x48,		/* FC_VARIABLE_REPEAT */
			0x49,		/* FC_FIXED_OFFSET */
/* 672 */	NdrFcShort( 0x4 ),	/* 4 */
/* 674 */	NdrFcShort( 0x0 ),	/* 0 */
/* 676 */	NdrFcShort( 0x1 ),	/* 1 */
/* 678 */	NdrFcShort( 0x0 ),	/* 0 */
/* 680 */	NdrFcShort( 0x0 ),	/* 0 */
/* 682 */	0x12, 0x0,	/* FC_UP */
/* 684 */	NdrFcShort( 0xffffffd4 ),	/* Offset= -44 (640) */
/* 686 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 688 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 690 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 692 */	NdrFcShort( 0x8 ),	/* 8 */
/* 694 */	NdrFcShort( 0x0 ),	/* 0 */
/* 696 */	NdrFcShort( 0x6 ),	/* Offset= 6 (702) */
/* 698 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 700 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 702 */	
			0x11, 0x0,	/* FC_RP */
/* 704 */	NdrFcShort( 0xffffffd4 ),	/* Offset= -44 (660) */
/* 706 */	
			0x1d,		/* FC_SMFARRAY */
			0x0,		/* 0 */
/* 708 */	NdrFcShort( 0x8 ),	/* 8 */
/* 710 */	0x1,		/* FC_BYTE */
			0x5b,		/* FC_END */
/* 712 */	
			0x15,		/* FC_STRUCT */
			0x3,		/* 3 */
/* 714 */	NdrFcShort( 0x10 ),	/* 16 */
/* 716 */	0x8,		/* FC_LONG */
			0x6,		/* FC_SHORT */
/* 718 */	0x6,		/* FC_SHORT */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 720 */	0x0,		/* 0 */
			NdrFcShort( 0xfffffff1 ),	/* Offset= -15 (706) */
			0x5b,		/* FC_END */
/* 724 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 726 */	NdrFcShort( 0x18 ),	/* 24 */
/* 728 */	NdrFcShort( 0x0 ),	/* 0 */
/* 730 */	NdrFcShort( 0xa ),	/* Offset= 10 (740) */
/* 732 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 734 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 736 */	NdrFcShort( 0xffffffe8 ),	/* Offset= -24 (712) */
/* 738 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 740 */	
			0x11, 0x0,	/* FC_RP */
/* 742 */	NdrFcShort( 0xffffff0c ),	/* Offset= -244 (498) */
/* 744 */	
			0x1b,		/* FC_CARRAY */
			0x0,		/* 0 */
/* 746 */	NdrFcShort( 0x1 ),	/* 1 */
/* 748 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 750 */	NdrFcShort( 0x0 ),	/* 0 */
/* 752 */	0x1,		/* FC_BYTE */
			0x5b,		/* FC_END */
/* 754 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 756 */	NdrFcShort( 0x8 ),	/* 8 */
/* 758 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 760 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 762 */	NdrFcShort( 0x4 ),	/* 4 */
/* 764 */	NdrFcShort( 0x4 ),	/* 4 */
/* 766 */	0x12, 0x0,	/* FC_UP */
/* 768 */	NdrFcShort( 0xffffffe8 ),	/* Offset= -24 (744) */
/* 770 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 772 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 774 */	
			0x1b,		/* FC_CARRAY */
			0x1,		/* 1 */
/* 776 */	NdrFcShort( 0x2 ),	/* 2 */
/* 778 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 780 */	NdrFcShort( 0x0 ),	/* 0 */
/* 782 */	0x6,		/* FC_SHORT */
			0x5b,		/* FC_END */
/* 784 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 786 */	NdrFcShort( 0x8 ),	/* 8 */
/* 788 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 790 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 792 */	NdrFcShort( 0x4 ),	/* 4 */
/* 794 */	NdrFcShort( 0x4 ),	/* 4 */
/* 796 */	0x12, 0x0,	/* FC_UP */
/* 798 */	NdrFcShort( 0xffffffe8 ),	/* Offset= -24 (774) */
/* 800 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 802 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 804 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 806 */	NdrFcShort( 0x4 ),	/* 4 */
/* 808 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 810 */	NdrFcShort( 0x0 ),	/* 0 */
/* 812 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 814 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 816 */	NdrFcShort( 0x8 ),	/* 8 */
/* 818 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 820 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 822 */	NdrFcShort( 0x4 ),	/* 4 */
/* 824 */	NdrFcShort( 0x4 ),	/* 4 */
/* 826 */	0x12, 0x0,	/* FC_UP */
/* 828 */	NdrFcShort( 0xffffffe8 ),	/* Offset= -24 (804) */
/* 830 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 832 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 834 */	
			0x1b,		/* FC_CARRAY */
			0x7,		/* 7 */
/* 836 */	NdrFcShort( 0x8 ),	/* 8 */
/* 838 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 840 */	NdrFcShort( 0x0 ),	/* 0 */
/* 842 */	0xb,		/* FC_HYPER */
			0x5b,		/* FC_END */
/* 844 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 846 */	NdrFcShort( 0x8 ),	/* 8 */
/* 848 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 850 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 852 */	NdrFcShort( 0x4 ),	/* 4 */
/* 854 */	NdrFcShort( 0x4 ),	/* 4 */
/* 856 */	0x12, 0x0,	/* FC_UP */
/* 858 */	NdrFcShort( 0xffffffe8 ),	/* Offset= -24 (834) */
/* 860 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 862 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 864 */	
			0x15,		/* FC_STRUCT */
			0x3,		/* 3 */
/* 866 */	NdrFcShort( 0x8 ),	/* 8 */
/* 868 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 870 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 872 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 874 */	NdrFcShort( 0x8 ),	/* 8 */
/* 876 */	0x7,		/* Corr desc: FC_USHORT */
			0x0,		/*  */
/* 878 */	NdrFcShort( 0xffd8 ),	/* -40 */
/* 880 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 882 */	NdrFcShort( 0xffffffee ),	/* Offset= -18 (864) */
/* 884 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 886 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 888 */	NdrFcShort( 0x28 ),	/* 40 */
/* 890 */	NdrFcShort( 0xffffffee ),	/* Offset= -18 (872) */
/* 892 */	NdrFcShort( 0x0 ),	/* Offset= 0 (892) */
/* 894 */	0x6,		/* FC_SHORT */
			0x6,		/* FC_SHORT */
/* 896 */	0x38,		/* FC_ALIGNM4 */
			0x8,		/* FC_LONG */
/* 898 */	0x8,		/* FC_LONG */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 900 */	0x0,		/* 0 */
			NdrFcShort( 0xfffffdf7 ),	/* Offset= -521 (380) */
			0x5b,		/* FC_END */
/* 904 */	
			0x12, 0x0,	/* FC_UP */
/* 906 */	NdrFcShort( 0xfffffef6 ),	/* Offset= -266 (640) */
/* 908 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 910 */	0x1,		/* FC_BYTE */
			0x5c,		/* FC_PAD */
/* 912 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 914 */	0x6,		/* FC_SHORT */
			0x5c,		/* FC_PAD */
/* 916 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 918 */	0x8,		/* FC_LONG */
			0x5c,		/* FC_PAD */
/* 920 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 922 */	0xb,		/* FC_HYPER */
			0x5c,		/* FC_PAD */
/* 924 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 926 */	0xa,		/* FC_FLOAT */
			0x5c,		/* FC_PAD */
/* 928 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 930 */	0xc,		/* FC_DOUBLE */
			0x5c,		/* FC_PAD */
/* 932 */	
			0x12, 0x0,	/* FC_UP */
/* 934 */	NdrFcShort( 0xfffffd8c ),	/* Offset= -628 (306) */
/* 936 */	
			0x12, 0x10,	/* FC_UP */
/* 938 */	NdrFcShort( 0xfffffd8e ),	/* Offset= -626 (312) */
/* 940 */	
			0x12, 0x10,	/* FC_UP */
/* 942 */	NdrFcShort( 0xfffffda2 ),	/* Offset= -606 (336) */
/* 944 */	
			0x12, 0x10,	/* FC_UP */
/* 946 */	NdrFcShort( 0xfffffdb0 ),	/* Offset= -592 (354) */
/* 948 */	
			0x12, 0x10,	/* FC_UP */
/* 950 */	NdrFcShort( 0xfffffdbe ),	/* Offset= -578 (372) */
/* 952 */	
			0x12, 0x10,	/* FC_UP */
/* 954 */	NdrFcShort( 0x2 ),	/* Offset= 2 (956) */
/* 956 */	
			0x12, 0x0,	/* FC_UP */
/* 958 */	NdrFcShort( 0xfffffc42 ),	/* Offset= -958 (0) */
/* 960 */	
			0x15,		/* FC_STRUCT */
			0x7,		/* 7 */
/* 962 */	NdrFcShort( 0x10 ),	/* 16 */
/* 964 */	0x6,		/* FC_SHORT */
			0x1,		/* FC_BYTE */
/* 966 */	0x1,		/* FC_BYTE */
			0x38,		/* FC_ALIGNM4 */
/* 968 */	0x8,		/* FC_LONG */
			0x39,		/* FC_ALIGNM8 */
/* 970 */	0xb,		/* FC_HYPER */
			0x5b,		/* FC_END */
/* 972 */	
			0x12, 0x0,	/* FC_UP */
/* 974 */	NdrFcShort( 0xfffffff2 ),	/* Offset= -14 (960) */
/* 976 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 978 */	0x2,		/* FC_CHAR */
			0x5c,		/* FC_PAD */
/* 980 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x7,		/* 7 */
/* 982 */	NdrFcShort( 0x20 ),	/* 32 */
/* 984 */	NdrFcShort( 0x0 ),	/* 0 */
/* 986 */	NdrFcShort( 0x0 ),	/* Offset= 0 (986) */
/* 988 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 990 */	0x6,		/* FC_SHORT */
			0x6,		/* FC_SHORT */
/* 992 */	0x6,		/* FC_SHORT */
			0x6,		/* FC_SHORT */
/* 994 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 996 */	NdrFcShort( 0xfffffc26 ),	/* Offset= -986 (10) */
/* 998 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 1000 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 1002 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1004 */	NdrFcShort( 0x10 ),	/* 16 */
/* 1006 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1008 */	NdrFcShort( 0xfffffc16 ),	/* Offset= -1002 (6) */
/* 1010 */	
			0x11, 0xc,	/* FC_RP [alloced_on_stack] [simple_pointer] */
/* 1012 */	0x8,		/* FC_LONG */
			0x5c,		/* FC_PAD */
/* 1014 */	
			0x11, 0x4,	/* FC_RP [alloced_on_stack] */
/* 1016 */	NdrFcShort( 0x6 ),	/* Offset= 6 (1022) */
/* 1018 */	
			0x13, 0x0,	/* FC_OP */
/* 1020 */	NdrFcShort( 0xffffffd8 ),	/* Offset= -40 (980) */
/* 1022 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 1024 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1026 */	NdrFcShort( 0x10 ),	/* 16 */
/* 1028 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1030 */	NdrFcShort( 0xfffffff4 ),	/* Offset= -12 (1018) */

			0x0
        }
    };

const CInterfaceProxyVtbl * _ConfigChk_ProxyVtblList[] = 
{
    ( CInterfaceProxyVtbl *) &_IConfigChkrProxyVtbl,
    0
};

const CInterfaceStubVtbl * _ConfigChk_StubVtblList[] = 
{
    ( CInterfaceStubVtbl *) &_IConfigChkrStubVtbl,
    0
};

PCInterfaceName const _ConfigChk_InterfaceNamesList[] = 
{
    "IConfigChkr",
    0
};

const IID *  _ConfigChk_BaseIIDList[] = 
{
    &IID_IDispatch,
    0
};


#define _ConfigChk_CHECK_IID(n)	IID_GENERIC_CHECK_IID( _ConfigChk, pIID, n)

int __stdcall _ConfigChk_IID_Lookup( const IID * pIID, int * pIndex )
{
    
    if(!_ConfigChk_CHECK_IID(0))
        {
        *pIndex = 0;
        return 1;
        }

    return 0;
}

const ExtendedProxyFileInfo ConfigChk_ProxyFileInfo = 
{
    (PCInterfaceProxyVtblList *) & _ConfigChk_ProxyVtblList,
    (PCInterfaceStubVtblList *) & _ConfigChk_StubVtblList,
    (const PCInterfaceName * ) & _ConfigChk_InterfaceNamesList,
    (const IID ** ) & _ConfigChk_BaseIIDList,
    & _ConfigChk_IID_Lookup, 
    1,
    2,
    0, /* table of [async_uuid] interfaces */
    0, /* Filler1 */
    0, /* Filler2 */
    0  /* Filler3 */
};
