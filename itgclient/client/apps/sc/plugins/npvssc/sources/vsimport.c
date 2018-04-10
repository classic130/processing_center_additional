/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Fri Jun 18 10:26:58 1999
 */
/* Compiler settings for ImportPKCS12.idl:
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

const IID IID_IImpPKCS12 = {0xB1D475FD,0x75CD,0x11D2,{0x83,0x01,0x00,0x60,0xB0,0xB3,0x2E,0x16}};


const IID LIBID_IMPORTPKCS12Lib = {0xB1D475F0,0x75CD,0x11D2,{0x83,0x01,0x00,0x60,0xB0,0xB3,0x2E,0x16}};


const CLSID CLSID_ImpPKCS12 = {0xB1D475FE,0x75CD,0x11D2,{0x83,0x01,0x00,0x60,0xB0,0xB3,0x2E,0x16}};


#ifdef __cplusplus
}
#endif

