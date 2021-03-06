/*++

Copyright (c) 1992-1998  Microsoft Corporation

Module Name:

    wdbgexts.h

Abstract:

    This file contains the necessary prototypes and data types for a user
    to write a debugger extension DLL.  This header file is also included
    by the NT debuggers (WINDBG & KD).

    This header file must be included after "windows.h" and "imagehlp.h".

    Please see the NT DDK documentation for specific information about
    how to write your own debugger extension DLL.

Environment:

    Win32 only.

Revision History:

--*/

#ifndef _WDBGEXTS_
#define _WDBGEXTS_

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(WDBGAPI)
#define WDBGAPI __stdcall
#endif

#if !defined(WDBGAPIV)
#define WDBGAPIV __cdecl
#endif

#ifndef _WINDEF_
typedef CONST void far *LPCVOID;
#endif

typedef
VOID
(WDBGAPIV*PWINDBG_OUTPUT_ROUTINE)(
    PCSTR lpFormat,
    ...
    );

typedef
ULONG_PTR
(WDBGAPI*PWINDBG_GET_EXPRESSION)(
    PCSTR lpExpression
    );

typedef
VOID
(WDBGAPI*PWINDBG_GET_SYMBOL)(
    PVOID   offset,
    PUCHAR  pchBuffer,
    PULONG  pDisplacement
    );

typedef
ULONG
(WDBGAPI*PWINDBG_DISASM)(
    ULONG_PTR *lpOffset,
    PCSTR      lpBuffer,
    ULONG      fShowEffectiveAddress
    );

typedef
ULONG
(WDBGAPI*PWINDBG_CHECK_CONTROL_C)(
    VOID
    );

typedef
ULONG
(WDBGAPI*PWINDBG_READ_PROCESS_MEMORY_ROUTINE)(
    ULONG_PTR  offset,
    PVOID      lpBuffer,
    ULONG      cb,
    PULONG     lpcbBytesRead
    );

typedef
ULONG
(WDBGAPI*PWINDBG_WRITE_PROCESS_MEMORY_ROUTINE)(
    ULONG_PTR  offset,
    LPCVOID    lpBuffer,
    ULONG      cb,
    PULONG     lpcbBytesWritten
    );

typedef
ULONG
(WDBGAPI*PWINDBG_GET_THREAD_CONTEXT_ROUTINE)(
    ULONG       Processor,
    PCONTEXT    lpContext,
    ULONG       cbSizeOfContext
    );

typedef
ULONG
(WDBGAPI*PWINDBG_SET_THREAD_CONTEXT_ROUTINE)(
    ULONG       Processor,
    PCONTEXT    lpContext,
    ULONG       cbSizeOfContext
    );

typedef
ULONG
(WDBGAPI*PWINDBG_IOCTL_ROUTINE)(
    USHORT   IoctlType,
    PVOID    lpvData,
    ULONG    cbSize
    );

typedef
ULONG
(WDBGAPI*PWINDBG_OLDKD_READ_PHYSICAL_MEMORY)(
    LARGE_INTEGER    address,
    PVOID            buffer,
    ULONG            count,
    PULONG           bytesread
    );

typedef
ULONG
(WDBGAPI*PWINDBG_OLDKD_WRITE_PHYSICAL_MEMORY)(
    LARGE_INTEGER    address,
    PVOID            buffer,
    ULONG            length,
    PULONG           byteswritten
    );


typedef struct _tagEXTSTACKTRACE {
    ULONG       FramePointer;
    ULONG       ProgramCounter;
    ULONG       ReturnAddress;
    ULONG       Args[4];
} EXTSTACKTRACE, *PEXTSTACKTRACE;


typedef
ULONG
(*PWINDBG_STACKTRACE_ROUTINE)(
    ULONG             FramePointer,
    ULONG             StackPointer,
    ULONG             ProgramCounter,
    PEXTSTACKTRACE    StackFrames,
    ULONG             Frames
    );

typedef struct _WINDBG_EXTENSION_APIS {
    ULONG                                  nSize;
    PWINDBG_OUTPUT_ROUTINE                 lpOutputRoutine;
    PWINDBG_GET_EXPRESSION                 lpGetExpressionRoutine;
    PWINDBG_GET_SYMBOL                     lpGetSymbolRoutine;
    PWINDBG_DISASM                         lpDisasmRoutine;
    PWINDBG_CHECK_CONTROL_C                lpCheckControlCRoutine;
    PWINDBG_READ_PROCESS_MEMORY_ROUTINE    lpReadProcessMemoryRoutine;
    PWINDBG_WRITE_PROCESS_MEMORY_ROUTINE   lpWriteProcessMemoryRoutine;
    PWINDBG_GET_THREAD_CONTEXT_ROUTINE     lpGetThreadContextRoutine;
    PWINDBG_SET_THREAD_CONTEXT_ROUTINE     lpSetThreadContextRoutine;
    PWINDBG_IOCTL_ROUTINE                  lpIoctlRoutine;
    PWINDBG_STACKTRACE_ROUTINE             lpStackTraceRoutine;
} WINDBG_EXTENSION_APIS, *PWINDBG_EXTENSION_APIS;

typedef struct _WINDBG_OLD_EXTENSION_APIS {
    ULONG                                  nSize;
    PWINDBG_OUTPUT_ROUTINE                 lpOutputRoutine;
    PWINDBG_GET_EXPRESSION                 lpGetExpressionRoutine;
    PWINDBG_GET_SYMBOL                     lpGetSymbolRoutine;
    PWINDBG_DISASM                         lpDisasmRoutine;
    PWINDBG_CHECK_CONTROL_C                lpCheckControlCRoutine;
} WINDBG_OLD_EXTENSION_APIS, *PWINDBG_OLD_EXTENSION_APIS;

typedef struct _WINDBG_OLDKD_EXTENSION_APIS {
    ULONG                                  nSize;
    PWINDBG_OUTPUT_ROUTINE                 lpOutputRoutine;
    PWINDBG_GET_EXPRESSION                 lpGetExpressionRoutine;
    PWINDBG_GET_SYMBOL                     lpGetSymbolRoutine;
    PWINDBG_DISASM                         lpDisasmRoutine;
    PWINDBG_CHECK_CONTROL_C                lpCheckControlCRoutine;
    PWINDBG_READ_PROCESS_MEMORY_ROUTINE    lpReadVirtualMemRoutine;
    PWINDBG_WRITE_PROCESS_MEMORY_ROUTINE   lpWriteVirtualMemRoutine;
    PWINDBG_OLDKD_READ_PHYSICAL_MEMORY     lpReadPhysicalMemRoutine;
    PWINDBG_OLDKD_WRITE_PHYSICAL_MEMORY    lpWritePhysicalMemRoutine;
} WINDBG_OLDKD_EXTENSION_APIS, *PWINDBG_OLDKD_EXTENSION_APIS;

typedef
VOID
(WDBGAPI*PWINDBG_OLD_EXTENSION_ROUTINE)(
    HANDLE                  hCurrentProcess,
    HANDLE                  hCurrentThread,
    ULONG                   dwCurrentPc,
    PWINDBG_EXTENSION_APIS  lpExtensionApis,
    PCSTR                   lpArgumentString
    );

typedef
VOID
(WDBGAPI*PWINDBG_EXTENSION_ROUTINE)(
    HANDLE                  hCurrentProcess,
    HANDLE                  hCurrentThread,
    ULONG                   dwCurrentPc,
    ULONG                   dwProcessor,
    PCSTR                   lpArgumentString
    );

typedef
VOID
(WDBGAPI*PWINDBG_OLDKD_EXTENSION_ROUTINE)(
    ULONG                        dwCurrentPc,
    PWINDBG_OLDKD_EXTENSION_APIS lpExtensionApis,
    PCSTR                        lpArgumentString
    );

typedef
VOID
(WDBGAPI*PWINDBG_EXTENSION_DLL_INIT)(
    PWINDBG_EXTENSION_APIS lpExtensionApis,
    USHORT                 MajorVersion,
    USHORT                 MinorVersion
    );

typedef
ULONG
(WDBGAPI*PWINDBG_CHECK_VERSION)(
    VOID
    );

#define EXT_API_VERSION_NUMBER 5

typedef struct EXT_API_VERSION {
    USHORT  MajorVersion;
    USHORT  MinorVersion;
    USHORT  Revision;
    USHORT  Reserved;
} EXT_API_VERSION, *LPEXT_API_VERSION;

typedef
LPEXT_API_VERSION
(WDBGAPI*PWINDBG_EXTENSION_API_VERSION)(
    VOID
    );

#define IG_KD_CONTEXT               1
#define IG_READ_CONTROL_SPACE       2
#define IG_WRITE_CONTROL_SPACE      3
#define IG_READ_IO_SPACE            4
#define IG_WRITE_IO_SPACE           5
#define IG_READ_PHYSICAL            6
#define IG_WRITE_PHYSICAL           7
#define IG_READ_IO_SPACE_EX         8
#define IG_WRITE_IO_SPACE_EX        9
#define IG_KSTACK_HELP             10   // obsolete
#define IG_SET_THREAD              11
#define IG_READ_MSR                12
#define IG_WRITE_MSR               13
#define IG_GET_DEBUGGER_DATA       14
#define IG_GET_KERNEL_VERSION      15
#define IG_RELOAD_SYMBOLS          16
#define IG_GET_SET_SYMPATH         17
#define IG_GET_EXCEPTION_RECORD    18

typedef struct _tagPROCESSORINFO {
    USHORT      Processor;                // current processor
    USHORT      NumberProcessors;         // total number of processors
} PROCESSORINFO, *PPROCESSORINFO;

typedef struct _tagREADCONTROLSPACE {
    USHORT      Processor;
    ULONG       Address;
    ULONG       BufLen;
    UCHAR       Buf[1];
} READCONTROLSPACE, *PREADCONTROLSPACE;

typedef struct _tagIOSPACE {
    ULONG       Address;
    ULONG       Length;                   // 1, 2, or 4 bytes
    ULONG       Data;
} IOSPACE, *PIOSPACE;

typedef struct _tagIOSPACE_EX {
    ULONG       Address;
    ULONG       Length;                   // 1, 2, or 4 bytes
    ULONG       Data;
    ULONG       InterfaceType;
    ULONG       BusNumber;
    ULONG       AddressSpace;
} IOSPACE_EX, *PIOSPACE_EX;

typedef struct _tagPHYSICAL {
    LARGE_INTEGER          Address;
    ULONG                  BufLen;
    UCHAR                  Buf[1];
} PHYSICAL, *PPHYSICAL;

typedef struct _tagREAD_WRITE_MSR {
    ULONG       Msr;
    LONGLONG    Value;
} READ_WRITE_MSR, *PREAD_WRITE_MSR;

typedef struct _tagGET_SET_SYMPATH {
    PCSTR       Args;       // args to !reload command
    PSTR        Result;     // returns new path
    int         Length;     // Length of result buffer
} GET_SET_SYMPATH, *PGET_SET_SYMPATH;

#ifdef __cplusplus
#define CPPMOD extern "C"
#else
#define CPPMOD
#endif


#define DECLARE_API(s)                             \
    CPPMOD VOID                                    \
    s(                                             \
        HANDLE                 hCurrentProcess,    \
        HANDLE                 hCurrentThread,     \
        ULONG                  dwCurrentPc,        \
        ULONG                  dwProcessor,        \
        PCSTR                  args                \
     )

#ifndef NOEXTAPI

#define dprintf          (ExtensionApis.lpOutputRoutine)
#define GetExpression    (ExtensionApis.lpGetExpressionRoutine)
#define GetSymbol        (ExtensionApis.lpGetSymbolRoutine)
#define Disassm          (ExtensionApis.lpDisasmRoutine)
#define CheckControlC    (ExtensionApis.lpCheckControlCRoutine)
#define ReadMemory       (ExtensionApis.lpReadProcessMemoryRoutine)
#define WriteMemory      (ExtensionApis.lpWriteProcessMemoryRoutine)
#define GetContext       (ExtensionApis.lpGetThreadContextRoutine)
#define SetContext       (ExtensionApis.lpSetThreadContextRoutine)
#define Ioctl            (ExtensionApis.lpIoctlRoutine)
#define StackTrace       (ExtensionApis.lpStackTraceRoutine)


#define GetKdContext(ppi) \
    Ioctl( IG_KD_CONTEXT, (PVOID)ppi, sizeof(*ppi) )

//
// BOOL
// GetDebuggerData(
//     ULONG Tag,
//     PVOID Buf,
//     ULONG Size
//     )
//
/*++

Routine Description:



Arguments:



Return Value:



--*/

#define GetDebuggerData(TAG, BUF, SIZE)                             \
      ( (((PDBGKD_DEBUG_DATA_HEADER)(BUF))->OwnerTag = (TAG)),      \
        (((PDBGKD_DEBUG_DATA_HEADER)(BUF))->Size = (SIZE)),         \
        Ioctl( IG_GET_DEBUGGER_DATA, (PVOID)(BUF), (SIZE) ) )

extern WINDBG_EXTENSION_APIS ExtensionApis;

__inline VOID
ReadControlSpace(
    USHORT  processor,
    ULONG   address,
    PVOID   buf,
    ULONG   size
    )
{
    PREADCONTROLSPACE prc;
    prc = (PREADCONTROLSPACE)LocalAlloc(LPTR, sizeof(*prc) + size );
    ZeroMemory( prc->Buf, size );
    prc->Processor = processor;
    prc->Address = (ULONG)address;
    prc->BufLen = size;
    Ioctl( IG_READ_CONTROL_SPACE, (PVOID)prc, sizeof(*prc) + size );
    CopyMemory( buf, prc->Buf, size );
    LocalFree( prc );
}

__inline VOID
ReadIoSpace(
    ULONG   address,
    PULONG  data,
    PULONG  size
    )
{
    IOSPACE is;
    is.Address = (ULONG)address;
    is.Length = *size;
    Ioctl( IG_READ_IO_SPACE, (PVOID)&is, sizeof(is) );
    memcpy(data, &is.Data, is.Length);
    *size = is.Length;
}

__inline VOID
WriteIoSpace(
    ULONG   address,
    ULONG   data,
    PULONG  size
    )
{
    IOSPACE is;
    is.Address = (ULONG)address;
    is.Length = *size;
    is.Data = data;
    Ioctl( IG_WRITE_IO_SPACE, (PVOID)&is, sizeof(is) );
    *size = is.Length;
}

__inline VOID
ReadIoSpaceEx(
    ULONG   address,
    PULONG  data,
    PULONG  size,
    ULONG   interfacetype,
    ULONG   busnumber,
    ULONG   addressspace
    )
{
    IOSPACE_EX is;
    is.Address = (ULONG)address;
    is.Length = *size;
    is.Data = 0;
    is.InterfaceType = interfacetype;
    is.BusNumber = busnumber;
    is.AddressSpace = addressspace;
    Ioctl( IG_READ_IO_SPACE_EX, (PVOID)&is, sizeof(is) );
    *data = is.Data;
    *size = is.Length;
}

__inline VOID
WriteIoSpaceEx(
    ULONG   address,
    ULONG   data,
    PULONG  size,
    ULONG   interfacetype,
    ULONG   busnumber,
    ULONG   addressspace
    )
{
    IOSPACE_EX is;
    is.Address = (ULONG)address;
    is.Length = *size;
    is.Data = data;
    is.InterfaceType = interfacetype;
    is.BusNumber = busnumber;
    is.AddressSpace = addressspace;
    Ioctl( IG_WRITE_IO_SPACE_EX, (PVOID)&is, sizeof(is) );
    *size = is.Length;
}

__inline VOID
ReadPhysical(
    LARGE_INTEGER       address,
    PVOID               buf,
    ULONG               size,
    PULONG              sizer
    )
{
    PPHYSICAL phy;
    phy = (PPHYSICAL)LocalAlloc(LPTR,  sizeof(*phy) + size );
    ZeroMemory( phy->Buf, size );
    phy->Address = address;
    phy->BufLen = size;
    Ioctl( IG_READ_PHYSICAL, (PVOID)phy, sizeof(*phy) + size );
    *sizer = phy->BufLen;
    CopyMemory( buf, phy->Buf, *sizer );
    LocalFree( phy );
}

__inline VOID
WritePhysical(
    LARGE_INTEGER       address,
    PVOID               buf,
    ULONG               size,
    PULONG              sizew
    )
{
    PPHYSICAL phy;
    phy = (PPHYSICAL)LocalAlloc(LPTR, sizeof(*phy) + size );
    ZeroMemory( phy->Buf, size );
    phy->Address = address;
    phy->BufLen = size;
    CopyMemory( phy->Buf, buf, size );
    Ioctl( IG_WRITE_PHYSICAL, (PVOID)phy, sizeof(*phy) + size );
    *sizew = phy->BufLen;
    LocalFree( phy );
}

__inline VOID
SetThreadForOperation(
    PULONG Thread
    )
{
    Ioctl(IG_SET_THREAD, (PVOID)Thread, sizeof(ULONG));
}

__inline VOID
ReadMsr(
    ULONG       MsrReg,
    ULONGLONG   *MsrValue
    )
{
    PREAD_WRITE_MSR msr;

    msr = (PREAD_WRITE_MSR)LocalAlloc(LPTR,  sizeof(*msr));
    msr->Msr = MsrReg;
    Ioctl( IG_READ_MSR, (PVOID)msr, sizeof(*msr) );

    *MsrValue = msr->Value;
    LocalFree( msr );
}

__inline VOID
WriteMsr(
    ULONG       MsrReg,
    ULONGLONG   MsrValue
    )
{
    PREAD_WRITE_MSR msr;

    msr = (PREAD_WRITE_MSR)LocalAlloc(LPTR,  sizeof(*msr));
    msr->Msr = MsrReg;
    msr->Value = MsrValue;
    Ioctl( IG_WRITE_MSR, (PVOID)msr, sizeof(*msr) );
    LocalFree( msr );
}

__inline VOID
ReloadSymbols(
    IN PSTR Arg OPTIONAL
    )
/*++

Routine Description:

    Calls the debugger to reload symbols.

Arguments:

    Args - Supplies the tail of a !reload command string.

        !reload [flags] [module[=address]]
        flags:   /n  do not load from usermode list
                 /u  unload symbols, no reload
                 /v  verbose

        A value of NULL is equivalent to an empty string

Return Value:

    None

--*/
{
    Ioctl(IG_RELOAD_SYMBOLS, (PVOID)Arg, Arg?(strlen(Arg)+1):0);
}

__inline VOID
GetSetSympath(
    IN PSTR Arg,
    OUT PSTR Result OPTIONAL,
    IN int Length
    )
/*++

Routine Description:

    Calls the debugger to set or retrieve symbol search path.

Arguments:

    Arg - Supplies new search path.  If Arg is NULL or string is empty,
            the search path is not changed and the current setting is
            returned in Result.  When the symbol search path is changed,
            a call to ReloadSymbols is made implicitly.

    Result - OPTIONAL Returns the symbol search path setting.

    Length - Supplies the size of the buffer supplied by Result.

Return Value:

    None

--*/
{
    GET_SET_SYMPATH gss;
    gss.Args = Arg;
    gss.Result = Result;
    gss.Length = Length;
    Ioctl(IG_GET_SET_SYMPATH, (PVOID)&gss, sizeof(gss));
}


#endif


#ifdef __cplusplus
}
#endif

#endif // _WDBGEXTS_
