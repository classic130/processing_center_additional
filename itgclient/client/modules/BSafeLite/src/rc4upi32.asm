; Copyright (C) 1994 RSA Data Security, Inc. Created 1994
; This is an unpublished work protected as such under copyright law.
; This work contains proprietary, confidential, and trade secret information
; of RSA Data Security, Inc.  Use, disclosure, or reproduction without the
; express written authorization of RSA Data Security, Inc., is prohibited.
;
	.386P
	.MODEL	FLAT
; _TEXT is the name of a segment, the type of segement is CODE, PARA means
; paragraph aligned, any starting segment address will be 16-byte aligned.
; USE32 means addresses and data are 32-bit by default, so assembler will
; put a override prefix in front of any 16-bit instruction. PUBLIC means
; you can combine it with other segments, and will get combined if they use
; the same class ('CODE').
;

; DATA: data segment begins on DWORD (4-byte) boundary
;
_DATA	SEGMENT DWORD USE32 PUBLIC 'DATA'
_DATA	ENDS

; _BSS: where it puts changeable variables
;
_BSS	SEGMENT DWORD USE32 PUBLIC 'BSS'
_BSS	ENDS

; _TLS ??????????????
;
_TLS	SEGMENT DWORD USE32 PUBLIC 'TLS'
_TLS	ENDS

DGROUP	GROUP _DATA, _BSS

; ASSUME hints when the assembler needs to put override prefixes on
; instructions so that they use non-default segments.
;
	ASSUME	CS: FLAT, DS: FLAT, SS: FLAT

_TEXT	SEGMENT        ; announces the beginning of the _TEXT segment
                       ; it ends with the _TEXT ENDS line
; int A_RC4Update
;   (A_RC4_CTX *context,
;    unsigned char *output,
;    unsigned int *outputLen,
;    unsigned int maxOutputLen,
;    unsigned char *input,
;    unsigned int inputLen)
;
; Create a struct containing a list of all the things we will need to store
; on the stack. The last item in this struct will be moreStackSpace, the
; number of bytes needed to store all the previous items. For the arguments
; of this routine (passed on the stack, C calling convention), begin counting
; their offsets at moreStackSpace.
;
RC4UpdateStruct struc
saveEBX            dd   ?
saveESI            dd   ?
saveEDI            dd   ?
saveEBP            dd   ?
moreStackSpace     dd   ?
RC4UpdateStruct    ends

RETURN_ADDRESS     EQU  RC4UpdateStruct.moreStackSpace + 0
CONTEXT            EQU  RC4UpdateStruct.moreStackSpace + 4
OUTPUT             EQU  RC4UpdateStruct.moreStackSpace + 8
OUTPUT_LEN         EQU  RC4UpdateStruct.moreStackSpace + 12
MAX_OUTPUT_LEN     EQU  RC4UpdateStruct.moreStackSpace + 16
INPUT              EQU  RC4UpdateStruct.moreStackSpace + 20
INPUT_LEN          EQU  RC4UpdateStruct.moreStackSpace + 24

RC4_UPDATE_SAVE_EBX  EQU  RC4UpdateStruct.saveEBX
RC4_UPDATE_SAVE_ESI  EQU  RC4UpdateStruct.saveESI
RC4_UPDATE_SAVE_EDI  EQU  RC4UpdateStruct.saveEDI
RC4_UPDATE_SAVE_EBP  EQU  RC4UpdateStruct.saveEBP

; This is the RC4 key context struct
; typedef struct {
;   int initialized;
;   unsigned int i;
;   unsigned int j;
;   unsigned char table[256];
; } A_RC4_CTX;
;
RC4_CTX_INIT_FLAG  EQU  0
RC4_CTX_I          EQU  4
RC4_CTX_J          EQU  8
RC4_CTX_TABLE      EQU  12

; Return values
;
AE_OUTPUT_LEN          EQU     10
AE_NOT_INITIALIZED     EQU     11

; Entry point, it's public so other modules can access it by name.
;
public _A_RC4UpdateI32

; PROC means beginning of precedure and allows you to give it the property
; of being NEAR (in 32-bit always use NEAR -- never FAR)
;
_A_RC4UpdateI32 PROC NEAR
        sub     esp,RC4UpdateStruct.moreStackSpace  ; Set aside stack space
        mov     [esp+RC4_UPDATE_SAVE_EBX],ebx   ; Save the contents of
        mov     [esp+RC4_UPDATE_SAVE_ESI],esi   ;  these registers
        mov     [esp+RC4_UPDATE_SAVE_EDI],edi   ;  ..
        mov     [esp+RC4_UPDATE_SAVE_EBP],ebp   ;  ..

; if (inputLen > maxOutputLen)
;   return (AE_OUTPUT_LEN);
;
        mov     ecx,[esp+INPUT_LEN]       ; get inputLen
        mov     eax,[esp+MAX_OUTPUT_LEN]  ; get maxOutputLen
        mov     edx,[esp+CONTEXT]         ; get context
        cmp     ecx,eax                   ; compare inputLen to maxOutputLen
        ja      ErrOutputLen              ;  ..

        mov     edi,[edx+RC4_CTX_INIT_FLAG] ; get the initFlag

; if (inputLen == 0)
;   return (0);
;
        test    ecx,ecx                   ; check for inputLen == 0
        je      ZeroInput                 ;  ..

; if (! context->initialized)
;   return (AE_NOT_INITIALIZED);
;
        test    edi,edi                   ; check for initFlag == 0
        je      ErrNotInitialized         ;  ..

        mov     edi,[esp+OUTPUT]          ; get the outputBuffer
        mov     esi,[esp+INPUT]           ; get the inputBuffer

; Check to see if the outputBuffer is the same as the inputBuffer
; if (input == output)
;   goto LoopSetup
;
        cmp     esi,edi                   ; are the buffers the same
        je      LoopSetup                 ;  address?

; The registers currently look like this
; eax | -                        esi | inputBuffer
; ebx | -                        edi | outputBuffer
; ecx | inputLen                 ebp | -
; edx | context
; Copy input to output buffer four bytes at a time.
;
        mov     ebx,edi                   ; copy addr(output)
        shr     ecx,2                     ; inputLen / 4 = num (4 byte blocks)
        test    ecx,ecx                   ; any 4 byte blocks?
        je      Copy4Done                 ;  ..

; Copy input bytes to the output buffer 4 at a time.
;
Copy4Top:
        mov     eax,[esi]                 ; get 4 bytes of input
        add     esi,4                     ; advance the input buffer
        mov     [edi],eax                 ; move input bytes into output
        add     edi,4                     ; advance the output buffer
        dec     ecx                       ; decrement (inputLen / 4)
        je      Copy4Done                 ; any bytes left?

; Unroll loop once to avoid stalling pipeline for small blocks.
;
        mov     eax,[esi]                 ; get 4 bytes of input
        add     esi,4                     ; advance the input buffer
        mov     [edi],eax                 ; move input bytes into output
        add     edi,4                     ; advance the output buffer
        dec     ecx                       ; decrement (inputLen / 4)
        jne     Copy4Top                  ; more bytes?

; Copied all the four-byte blocks, do remaining bytes
;
Copy4Done:
        mov     ecx,[esp+INPUT_LEN]       ; get inputLen again
        and     ecx,3                     ; find number of leftover bytes

; At most 3 bytes left to copy, so unroll the loop to avoid branch
; prediction stalls of the pipeline.
;
        test    ecx,ecx                   ; any bytes left?
        je      Copy1Done                 ;  ..

        mov     al,[esi]                  ; get leftover byte 1 of input
        inc     esi                       ; advance input buffer
        mov     [edi],al                  ; store leftover byte 1
        inc     edi                       ; advance output buffer
        dec     ecx                       ; decrement inputLen
        je      Copy1Done                 ; only 1 leftover byte?

        mov     al,[esi]                  ; get leftover byte 2 of input
        inc     esi                       ; advance input buffer
        mov     [edi],al                  ; store leftover byte 2
        inc     edi                       ; advance output buffer
        dec     ecx                       ; decrement inputLen
        je      Copy1Done                 ; only 2 leftover bytes?

        mov     al,[esi]                  ; get leftover byte 3 of input
        mov     [edi],al                  ; store leftover byte 3

Copy1Done:
        mov     edi,ebx                   ; Restore output pointer

; The registers currently look like this
; eax | -                        esi | -
; ebx | -                        edi | outputBuffer
; ecx | -                        ebp | -
; edx | context
;
LoopSetup:
        mov     esi,[esp+INPUT_LEN]       ; get inputLen again
        mov     eax,[edx+RC4_CTX_I]       ; get i
        mov     ecx,[edx+RC4_CTX_J]       ; get j
        lea     ebp,[edx+RC4_CTX_TABLE]   ; get table
        inc     al                        ; i = i + 1
        xor     edx,edx                   ; initialize ti to 0
        xor     ebx,ebx                   ; initialize tj to 0

; First do multiple of 4 input bytes
;
        shr     esi,2                      ; inputLen / 4
        test    esi,esi                    ; any 4 byte blocks to do?
        je      Loop1Setup                 ;  ..

; Do 4 bytes at a time
;
Loop4Top:
        mov     dl,[ebp+eax]               ; ti = table[i]
        add     cl,dl                      ; j = j + ti
        inc     edi                        ; advance outputBuffer
        mov     bl,[ebp+ecx]               ; tj = table[j]
        mov     [ebp+eax],bl               ; table[i] = tj
        mov     [ebp+ecx],dl               ; table[j] = ti
        add     dl,bl                      ; ti + tj
        mov     bl,[edi-1]                 ; input byte
        inc     al                         ; increment i
        xor     bl,[ebp+edx]               ; input ^ table[ti + tj]

        mov     dl,[ebp+eax]               ; ti = table[i]
        mov     [edi-1],bl                 ; output byte

        add     cl,dl                      ; j = j + ti
        inc     edi                        ; advance outputBuffer
        mov     bl,[ebp+ecx]               ; tj = table[j]
        mov     [ebp+eax],bl               ; table[i] = tj
        mov     [ebp+ecx],dl               ; table[j] = ti
        add     dl,bl                      ; ti + tj
        mov     bl,[edi-1]                 ; input byte
        inc     al                         ; increment i
        xor     bl,[ebp+edx]               ; input ^ table[ti + tj]

        mov     dl,[ebp+eax]               ; ti = table[i]
        mov     [edi-1],bl                 ; output byte

        add     cl,dl                      ; j = j + ti
        inc     edi                        ; advance outputBuffer
        mov     bl,[ebp+ecx]               ; tj = table[j]
        mov     [ebp+eax],bl               ; table[i] = tj
        mov     [ebp+ecx],dl               ; table[j] = ti
        add     dl,bl                      ; ti + tj
        mov     bl,[edi-1]                 ; input byte
        inc     al                         ; increment i
        xor     bl,[ebp+edx]               ; input ^ table[ti + tj]

        mov     dl,[ebp+eax]               ; ti = table[i]
        mov     [edi-1],bl                 ; output byte

        add     cl,dl                      ; j = j + ti
        inc     edi                        ; advance outputBuffer
        mov     bl,[ebp+ecx]               ; tj = table[j]
        mov     [ebp+eax],bl               ; table[i] = tj
        mov     [ebp+ecx],dl               ; table[j] = ti
        add     dl,bl                      ; ti + tj
        mov     bl,[edi-1]                 ; input byte
        inc     al                         ; increment i
        xor     bl,[ebp+edx]               ; input ^ table[ti + tj]

        mov     [edi-1],bl                 ; output byte
        dec     esi                        ; decrement inputLen / 4
        jne     Loop4Top                   ; more 4 byte blocks?

; Do the leftover bytes one at a time.
;
Loop1Setup:
        mov     esi,[esp+INPUT_LEN]        ; get inputLen again
        and     esi,3                      ; isolate leftover count
        je      Loop1End                   ; any leftovers?

Loop1Top:
; Cycle 1
        mov     dl,[ebp+eax]               ; ti = table[i]

; Cycle 2
        add     cl,dl                      ; j = (j + ti) & 255
        inc     edi                        ; advance output buffer

; Cycle 3
; AGI on ecx

; Cycle 4
        mov     bl,[ebp+ecx]               ; tj = table[j]

; Cycle 5
        mov     [ebp+eax],bl               ; table[i] = tj
        mov     [ebp+ecx],dl               ; table[j] = ti

; Cycle 6
        add     dl,bl                      ; ti + tj

; Cycle 7
        mov     bl,[edi-1]                 ; input byte
        inc     al                         ; increment i

; Cycle 8
; ???

; Cycle 9   Two cycle instruction
; Cycle 10
        xor     bl,[ebp+edx]               ; input ^ table[ti + tj]

; Cycle 11
        mov     [edi-1],bl                 ; output byte

; Cycle 12	
        dec     esi                        ; decrement inputLen
        jne     Loop1Top                   ; any more bytes?

; No more leftover bytes
;   *outputLen = inputLen;
;   returnValue = 0;
;
Loop1End:
        mov     ebp,[esp+OUTPUT_LEN]       ; get addr (outputLen)
        mov     ebx,[esp+INPUT_LEN]        ; get inputLen
        mov     edx,[esp+CONTEXT]          ; get context
        dec     al                         ; had incremented i
        mov     [ebp],ebx                  ; set outputLen to inputLen

        mov     [edx+RC4_CTX_I],eax        ;  context->i = i;
        mov     [edx+RC4_CTX_J],ecx        ;  context->j = j;
        xor     eax,eax                    ; set return value to 0

Done:
        mov     ebx,[esp+RC4_UPDATE_SAVE_EBX]  ; Restore the contents
        mov     esi,[esp+RC4_UPDATE_SAVE_ESI]  ;  of these registers
        mov     edi,[esp+RC4_UPDATE_SAVE_EDI]  ;  ..
        mov     ebp,[esp+RC4_UPDATE_SAVE_EBP]  ;  ..
        add     esp,RC4UpdateStruct.moreStackSpace ; Restore the stack
        ret

; No input, do nothing, just return 0
;
ZeroInput:
        xor     eax,eax              ; set return register to 0
        jmp     Done                 ; jump to exit code

; Algorithm not initialized, do nothing, just return the proper error code
;
ErrNotInitialized:
        mov     eax,AE_NOT_INITIALIZED ; set return register to error code
        jmp     Done                   ; jump to exit code

ErrOutputLen:
        mov     eax,AE_OUTPUT_LEN    ; set return register to error code
        jmp     Done                 ; jump to exit code

_A_RC4UpdateI32 ENDP
_TEXT	ENDS
END
