/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Fri Mar 12 11:41:50 1999
 */
/* Compiler settings for xenroll.idl:
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

const IID LIBID_XENROLLLib = {0x43F8F27B,0x7A20,0x11D0,{0x8F,0x06,0x00,0xC0,0x4F,0xC2,0x95,0xE1}};


const IID IID_ICEnroll = {0x43F8F288,0x7A20,0x11D0,{0x8F,0x06,0x00,0xC0,0x4F,0xC2,0x95,0xE1}};


const IID IID_ICEnroll2 = {0x704CA730,0xC90B,0x11D1,{0x9B,0xEC,0x00,0xC0,0x4F,0xC2,0x95,0xE1}};


const CLSID CLSID_CEnroll = {0x43F8F289,0x7A20,0x11D0,{0x8F,0x06,0x00,0xC0,0x4F,0xC2,0x95,0xE1}};


#ifdef __cplusplus
}
#endif

