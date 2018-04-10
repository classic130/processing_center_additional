/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Fri Dec 29 16:04:40 2006
 */
/* Compiler settings for .\ConfigChk.idl:
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

const IID IID_IConfigChkr = {0x08F04138,0x8DFC,0x11D2,{0x80,0xE9,0x00,0x60,0x08,0xB0,0x66,0xEE}};


const IID LIBID_CONFIGCHKLib = {0x08F0412C,0x8DFC,0x11D2,{0x80,0xE9,0x00,0x60,0x08,0xB0,0x66,0xEE}};


const CLSID CLSID_ConfigChkr = {0x08F04139,0x8DFC,0x11D2,{0x80,0xE9,0x00,0x60,0x08,0xB0,0x66,0xEE}};


#ifdef __cplusplus
}
#endif

