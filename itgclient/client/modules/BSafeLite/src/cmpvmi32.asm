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

; /* vectorB = (scaler * vectorA) + vectorB
;  */
; int CMP_VectorMultiply
;   (scaler, vectorA, indexA, lengthA, vectorB, indexB)
; CMPWord scaler;
; CMPInt *vectorA;
; int indexA;
; int lengthA;
; CMPInt *vectorB;
; int indexB;
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
vectorMultStruct struc
saveEBX            dd   ?
saveESI            dd   ?
saveEDI            dd   ?
saveEBP            dd   ?
returnAddress      dd   ?
scaler             dd   ?
vectorA            dd   ?
indexA             dd   ?
lengthA            dd   ?
vectorB            dd   ?
indexB             dd   ?
vectorMultStruct ends

; Borland does not always recognize structures in instructions (and yet
; claims to be superior to Microsoft even though it screws up something
; this basic), so rename the structrue values.
;
VECTOR_MULT_SAVE_EBX  EQU  vectorMultStruct.saveEBX
VECTOR_MULT_SAVE_ESI  EQU  vectorMultStruct.saveESI
VECTOR_MULT_SAVE_EDI  EQU  vectorMultStruct.saveEDI
VECTOR_MULT_SAVE_EBP  EQU  vectorMultStruct.saveEBP
VECTOR_MULT_SCALER    EQU  vectorMultStruct.scaler
VECTOR_MULT_VECTOR_A  EQU  vectorMultStruct.vectorA
VECTOR_MULT_INDEX_A   EQU  vectorMultStruct.indexA
VECTOR_MULT_LENGTH_A  EQU  vectorMultStruct.lengthA
VECTOR_MULT_VECTOR_B  EQU  vectorMultStruct.vectorB
VECTOR_MULT_INDEX_B   EQU  vectorMultStruct.indexB

; Upon entering this routine, the return address will be at [esp + 0]. So
; whatever amount we give to MORE_STACK_SPACE -- the amount to subtract off
; the stack to make room for saving information -- that is the amount offset
; from the stack pointer where we will find the return address, namely,
; [esp + MORE_STACK_SPACE]. To guarantee vectorMultStruct.returnAddress equals
; MORE_STACK_SPACE, simply set MORE_STACK_SPACE to
; vectorMultStruct.returnAddress.
;
MORE_STACK_SPACE   EQU  vectorMultStruct.returnAddress

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
public _CMP_VectorMultiplyI32

; PROC means beginning of precedure and allows you to give it the property
; of being NEAR (in 32-bit always use NEAR -- never FAR)
;
_CMP_VectorMultiplyI32 PROC NEAR

; ebx, ebp, esi and edi are temp registers, they must be saved before using
; and restored before returning. There are other temp registers, but they're
; the ones that hold segments, and we're not going to change them, so don't
; worry about them.
;
        sub     esp,MORE_STACK_SPACE           ; Set aside stack space
        mov     [esp+VECTOR_MULT_SAVE_EBX],ebx ; Save the contents of
        mov     [esp+VECTOR_MULT_SAVE_ESI],esi ;  these registers
        mov     [esp+VECTOR_MULT_SAVE_EDI],edi ;  ..
        mov     [esp+VECTOR_MULT_SAVE_EBP],ebp ;  ..

        mov     edi,[esp+VECTOR_MULT_VECTOR_A] ; get vectorA
        mov     ebx,[esp+VECTOR_MULT_INDEX_A]  ; get indexA
        mov     esi,[esp+VECTOR_MULT_VECTOR_B] ; get vectorB
        mov     eax,[esp+VECTOR_MULT_INDEX_B]  ; get indexB
        mov     edi,[edi+CMP_INT_VALUE]        ; vectorA.value
        mov     ecx,[esp+VECTOR_MULT_SCALER]   ; get scaler
        mov     esi,[esi+CMP_INT_VALUE]        ; vectorB.value
        mov     ebp,[esp+VECTOR_MULT_LENGTH_A] ; get lengthA
        lea     esi,[esi+eax*4]                ; &vectorB.value[indexB]
        lea     edi,[edi+ebx*4]                ; &vectorA.value[indexA]

; Register use in the loop that follows:
; eax,edx - Used in multiply instruction 
;           eax holds factor, and edx:eax the product
; ebx     - holds carry from the last multiplication plus the carry from
;           the last column add.
; ecx     - holds the scalar to multiply by
; edi     - points to consecutive WORDS of vectorA starting at the
;           indexA-th WORD 
; esi     - points to consecutive WORDS of vectorB starting at the
;           indexB-th WORD 

        mov     ebx,0           ; the carry from the previous column
                                ;  initialize to zero for the first column
        cmp     ebp,0           ; if lengthA = 0, just skip this routine
        jbe     VectorMultiplyDone

NextColumn:
        mov     eax,[edi]       ; get next WORD from vectorA
        mul     ecx             ; product goes into edx:eax
                                ;  eax is low 32 bits, edx is high 32 bits
                                ;  so edx has the multiplicative carry
        add     eax,[esi]       ; add in vectorB's WORD to the low product
        adc     edx,0           ; add sum of column's carry to multiplicative
                                ;  carry
        add     eax,ebx         ; add in the last columns carry
        adc     edx,0           ; add sum of column's carry to the next
                                ;  column's carry
        mov     [esi],eax       ; save column result into vectorB
        mov     ebx,edx         ; save next column's carry in ebx
        add     edi,4           ; point to next vectorA WORD
        add     esi,4           ; point to next vectorB WORD

; * Note: Never use the LOOP instruction in 386+ code because it is slower
; *  than DEC followed by a conditional branch
;
        dec     ebp             ; decrement lengthA
        jne     NextColumn      ; if this is 0, done with vectorA

        mov     eax,[esi]       ; next vectorB WORD
        add     eax,ebx         ; add in last column's carry
        mov     [esi],eax       ; store result back into vectorB WORD
        jc      PropagateCarry  ; if there is a carry out then propagate

VectorMultiplyDone:
        mov     ebx,[esp+VECTOR_MULT_SAVE_EBX] ; Restore the contents of
        mov     esi,[esp+VECTOR_MULT_SAVE_ESI] ;  these registers
        mov     edi,[esp+VECTOR_MULT_SAVE_EDI] ;  ..
        mov     ebp,[esp+VECTOR_MULT_SAVE_EBP] ;  ..
        add     esp,MORE_STACK_SPACE           ; Restore the stack
        ret

; * The destination for jumps and calls should be dword aligned (386)
; * The destination for jumps and calls should be 16 byte aligned 
; *  on a 486, but you can't link ALIGN 16 assembly code with most 
; *  C compiler generated code.  So we settle for ALIGN 4 
;
        align 4
PropagateCarry:
        lea     esi,[esi+4]     ; point to next WORD of vectorB

; * Note: we could ADD [esi],1, but can't INC [esi] because INC doesn't
; *  set the carry flag needed for the test that follows.
;
        adc     dword ptr [esi],0 ; add carry from last into next vectorB WORD.
        jc      PropagateCarry    ; if the dword overflowed then contine on to
                                  ;  next dword of vectorB.

        mov     ebx,[esp+VECTOR_MULT_SAVE_EBX] ; Restore the contents of
        mov     esi,[esp+VECTOR_MULT_SAVE_ESI] ;  these registers
        mov     edi,[esp+VECTOR_MULT_SAVE_EDI] ;  ..
        mov     ebp,[esp+VECTOR_MULT_SAVE_EBP] ;  ..
        add     esp,MORE_STACK_SPACE           ; Restore the stack
        ret

_CMP_VectorMultiplyI32 ENDP
_TEXT	ENDS
END
