/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Mon Aug 17 12:07:42 1998
 */
/* Compiler settings for SCardSrv.Idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )
#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

const IID IID_ISCardISO7816 = {0x53B6AA68,0x3F56,0x11D0,{0x91,0x6B,0x00,0xAA,0x00,0xC1,0x80,0x68}};


const IID LIBID_SCardSrvLib = {0x53B6AA61,0x3F56,0x11D0,{0x91,0x6B,0x00,0xAA,0x00,0xC1,0x80,0x68}};


const CLSID CLSID_CSCardISO7816 = {0x53B6AA6C,0x3F56,0x11D0,{0x91,0x6B,0x00,0xAA,0x00,0xC1,0x80,0x68}};


#ifdef __cplusplus
}
#endif

