/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0158 */
/* at Mon Jul 20 08:51:29 1998
 */
/* Compiler settings for certbase.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data , no_format_optimization
*/
//@@MIDL_FILE_HEADING(  )


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__


#ifndef __certbase_h__
#define __certbase_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

/* header files for imported files */
#include "wtypes.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_certbase_0000 */
/* [local] */ 

typedef struct  _CERTTRANSBLOB
    {
    unsigned long cb;
    /* [unique][size_is] */ BYTE __RPC_FAR *pb;
    }	CERTTRANSBLOB;

typedef struct  _CERTVIEWRESTRICTION
    {
    DWORD ColumnIndex;
    LONG SeekOperator;
    LONG SortOrder;
    /* [unique][size_is] */ BYTE __RPC_FAR *pbValue;
    DWORD cbValue;
    }	CERTVIEWRESTRICTION;

#define	CVR_SEEK_NONE	( 0 )

#define	CVR_SEEK_EQ	( 0x1 )

#define	CVR_SEEK_LT	( 0x2 )

#define	CVR_SEEK_LE	( 0x4 )

#define	CVR_SEEK_GE	( 0x8 )

#define	CVR_SEEK_GT	( 0x10 )

#define	CVR_SEEK_MASK	( 0xff )

#define	CVR_SEEK_NODELTA	( 0x1000 )

#define	CVR_SORT_NONE	( 0 )

#define	CVR_SORT_ASCEND	( 0x1 )

#define	CVR_SORT_DESCEND	( 0x2 )



extern RPC_IF_HANDLE __MIDL_itf_certbase_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_certbase_0000_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
