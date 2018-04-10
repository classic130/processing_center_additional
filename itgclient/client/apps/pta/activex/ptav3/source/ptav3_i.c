/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Wed Jul 02 10:36:21 2003
 */
/* Compiler settings for F:\sasi_063003\itgclient\client\apps\pta\activex\ptav3\source\Ptav3.idl:
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

const IID IID_IVSPTA = {0x6F7864F8,0xDB33,0x11D3,{0x81,0x66,0x00,0x60,0xB0,0xF8,0x85,0xE6}};


const IID IID_IVSRootsUpdate = {0x50E71FEA,0x2234,0x11d4,{0x8D,0x73,0x00,0x60,0xB0,0xFC,0x06,0x37}};


const IID LIBID_PTAV3Lib = {0x6F7864EC,0xDB33,0x11D3,{0x81,0x66,0x00,0x60,0xB0,0xF8,0x85,0xE6}};


const CLSID CLSID_VSPTA = {0x6F7864F9,0xDB33,0x11D3,{0x81,0x66,0x00,0x60,0xB0,0xF8,0x85,0xE6}};


const CLSID CLSID_VSROOTS = {0x50E71FEB,0x2234,0x11d4,{0x8D,0x73,0x00,0x60,0xB0,0xFC,0x06,0x37}};


#ifdef __cplusplus
}
#endif

