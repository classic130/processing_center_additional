/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Fri Jun 06 15:51:25 2003
 */
/* Compiler settings for F:\gswa_v6_0\itgclient\client\apps\pta\activex\ptav3\Source\seldigid.idl:
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

const IID IID_IVSSelectedDigID = {0xd962f4c3,0xddb0,0x11d3,{0xa4,0x28,0xd1,0xa3,0x69,0xca,0x48,0x4f}};


#ifdef __cplusplus
}
#endif

