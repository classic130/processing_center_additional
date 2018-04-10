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

; int CMP_AddInTrace
;   (vectorA, vectorB)
; CMPInt *vectorA;
; CMPInt *vectorB;
;
; Upon entry, the return address is at [esp + 0], the first argument is at
; [esp + 4] and so on. The first thing to do is subtract enough space off
; the stack to hold anything we will ever need to save on the stack. Once
; we do that, however, the return address is at [esp + subtractedAmount].
;
; Create a struct containing a list of all the things we will need to store
; on the stack. Following all those items, list the return address and passed
; arguments. Whatever number returnAddress turns out to be, that will be the
; amount necessary for the opening subtract.
;
addInTraceStruct struc
saveESI            dd   ?
saveEDI            dd   ?
returnAddress      dd   ?
vectorA            dd   ?
vectorB            dd   ?
addInTraceStruct ends

; Borland does not always recognize structures in instructions (and yet
; claims to be superior to Microsoft even though it screws up something
; this basic), so rename the structrue values.
;
ADD_IN_TRACE_SAVE_ESI  EQU  addInTraceStruct.saveESI
ADD_IN_TRACE_SAVE_EDI  EQU  addInTraceStruct.saveEDI
ADD_IN_TRACE_VECTOR_A  EQU  addInTraceStruct.vectorA
ADD_IN_TRACE_VECTOR_B  EQU  addInTraceStruct.vectorB

; Upon entering this routine, the return address will be at [esp + 0]. So
; whatever amount we give to MORE_STACK_SPACE -- the amount to subtract off
; the stack to make room for saving information -- that is the amount offset
; from the stack pointer where we will find the return address, namely,
; [esp + MORE_STACK_SPACE]. To guarantee addInTraceStruct.returnAddress equals
; MORE_STACK_SPACE, simply set MORE_STACK_SPACE to
; addInTraceStruct.returnAddress.
;
MORE_STACK_SPACE   EQU  addInTraceStruct.returnAddress

; The following definitions are for the CMPInt struct
; typedef struct {
;   int space;
;   int length;
;   unsigned char *value;
; }
;
CMP_INT_SPACE   EQU  0
CMP_INT_LENGTH  EQU  4
CMP_INT_VALUE   EQU  8

; entry point, it's public so other modules can access it by name, adds
; it to the symbol table
;
public _CMP_AddInTraceI32

; PROC means beginning of precedure and allows you to give it the property
; of being NEAR (in 32-bit always use NEAR -- never FAR)
;
_CMP_AddInTraceI32 PROC NEAR

; esi and edi are temp registers, they must be saved before using and
; restored before returning. There are other temp registers, but we're
; not going to change them, so don't worry about them.
;
        sub     esp,MORE_STACK_SPACE            ; Set aside stack space
        mov     [esp+ADD_IN_TRACE_SAVE_ESI],esi ;  Save the contents of
        mov     [esp+ADD_IN_TRACE_SAVE_EDI],edi ;  these registers

        mov     edi,[esp+ADD_IN_TRACE_VECTOR_A] ; get vectorA
        mov     esi,[esp+ADD_IN_TRACE_VECTOR_B] ; get vectorB
        mov     ecx,[edi+CMP_INT_LENGTH]        ; get lengthA
        mov     edi,[edi+CMP_INT_VALUE]         ; vectorA.value
        mov     esi,[esi+CMP_INT_VALUE]         ; vectorB.value

; Register use in the loop that follows:
; eax,edx - Used in multiply instruction 
;           eax holds factor, and edx:eax the product
; ecx     - length of vectorA, the loop count
; edi     - points to consecutive WORDS of vectorA
; esi     - points to consecutive WORDS of vectorB

NextColumn:
        mov     eax,[edi]       ; get next WORD from vectorA
        mul     eax             ; product goes into edx:eax
                                ;  eax is low 32 bits, edx is high 32 bits
        add     [esi],eax       ; add low WORD of square to vectorB
        adc     [esi+4],edx     ; add high WORD of square to vectorB
        jc      PropagateCarry  ; Is there still a carry?

UpdatePointers:
        lea     edi,[edi+4]     ; point to next vectorA WORD
        lea     esi,[esi+8]     ; point to next vectorB WORD
        dec     ecx             ; decrement counter, length of vectorA
        jne     NextColumn

        mov     esi,[esp+ADD_IN_TRACE_SAVE_ESI] ; Restore the contents of
        mov     edi,[esp+ADD_IN_TRACE_SAVE_EDI] ;  these registers
        add     esp,MORE_STACK_SPACE            ; Restore the stack
        ret

; * The destination for jumps and calls should be dword aligned (386)
; * The destination for jumps and calls should be 16 byte aligned 
; *  on a 486, but you can't link ALIGN 16 assembly code with most 
; *  C compiler generated code.  So we settle for ALIGN 4 
;
        align 4
PropagateCarry:
        lea     edx,[esi+8]     ; point to next WORD of vectorB
NextCarry:
        add     dword ptr [edx],1 ; add in the carry
        jnc     UpdatePointers    ; if no carry out this time contine
        lea     edx,[edx+4]       ; if there is another carry generated
        jmp short NextCarry       ;  add it in too.

_CMP_AddInTraceI32 ENDP
_TEXT	ENDS
END
