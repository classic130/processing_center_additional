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

; int CMP_MontSquare
;   (operand, modulus, n0Prime, montSquare)
; CMPInt *operand;
; CMPInt *modulus;
; CMPWord n0Prime;
; CMPInt *montSquare;
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
; If this routine calls other routines, pass the arguments on the stack
; following the C calling convention. That means immediately before the call,
; the first argument will be at [esp + 0], the second at [esp + 4], and so on.
; The call instruction will push the return address onto the stack.
;
montSquareStruct struc
argument_1         dd   ?
argument_2         dd   ?
argument_3         dd   ?
argument_4         dd   ?
argument_5         dd   ?
argument_6         dd   ?
mlength            dd   ?
mlength2           dd   ?
saveEBX            dd   ?
saveESI            dd   ?
saveEDI            dd   ?
saveEBP            dd   ?
returnAddress      dd   ?
operand            dd   ?
modulus            dd   ?
n0Prime            dd   ?
montSquare         dd   ?
montSquareStruct    ends

; Borland does not always recognize structures in instructions (and yet
; claims to be superior to Microsoft even though it screws up something
; this basic), so rename the structrue values.
;
MONT_SQUARE_ARG_1     EQU  montSquareStruct.argument_1
MONT_SQUARE_ARG_2     EQU  montSquareStruct.argument_2
MONT_SQUARE_ARG_3     EQU  montSquareStruct.argument_3
MONT_SQUARE_ARG_4     EQU  montSquareStruct.argument_4
MONT_SQUARE_ARG_5     EQU  montSquareStruct.argument_5
MONT_SQUARE_ARG_6     EQU  montSquareStruct.argument_6
MONT_SQUARE_MLENGTH   EQU  montSquareStruct.mlength
MONT_SQUARE_MLENGTH2  EQU  montSquareStruct.mlength2
MONT_SQUARE_SAVE_EBX  EQU  montSquareStruct.saveEBX
MONT_SQUARE_SAVE_ESI  EQU  montSquareStruct.saveESI
MONT_SQUARE_SAVE_EDI  EQU  montSquareStruct.saveEDI
MONT_SQUARE_SAVE_EBP  EQU  montSquareStruct.saveEBP
MONT_SQUARE_OPERAND   EQU  montSquareStruct.operand
MONT_SQUARE_MODULUS       EQU  montSquareStruct.modulus
MONT_SQUARE_N0_PRIME      EQU  montSquareStruct.n0Prime
MONT_SQUARE_MONT_SQUARE   EQU  montSquareStruct.montSquare

; Upon entering this routine, the return address will be at [esp + 0]. So
; whatever amount we give to MORE_STACK_SPACE -- the amount to subtract off
; the stack to make room for saving information -- that is the amount offset
; from the stack pointer where we will find the return address, namely,
; [esp + MORE_STACK_SPACE]. To guarantee montSquareStruct.returnAddress equals
; MORE_STACK_SPACE, simply set MORE_STACK_SPACE to
; montSquareStruct.returnAddress.
;
MORE_STACK_SPACE   EQU  montSquareStruct.returnAddress

; This is the
; typedef struct {
;   int space;
;   int length;
;   unsigned char *value;
; } CMPInt
;
CMP_INT_SPACE  EQU 0
CMP_INT_LENGTH EQU 4
CMP_INT_VALUE  EQU 8

; These are the subroutines we will be calling.
;
extrn _CMP_VectorMultiplyI32:near
extrn _VS_CMP_RecomputeLength:near
extrn _VS_CMP_ShiftRightByCMPWords:near
extrn _VS_CMP_ShiftLeftByBits:near
extrn _VS_CMP_Compare:near
extrn _VS_CMP_SubtractInPlace:near
extrn _CMP_reallocNoCopy:near

; entry point, it's public so other modules can access it by name, adds
; it to the symbol table
;
        public _CMP_MontSquareI32
_CMP_MontSquareI32 PROC NEAR
        sub     esp,MORE_STACK_SPACE              ; Set aside stack space
        mov     [esp+MONT_SQUARE_SAVE_EBX],ebx    ; Save the contents of
        mov     [esp+MONT_SQUARE_SAVE_ESI],esi    ;  these registers
        mov     [esp+MONT_SQUARE_SAVE_EDI],edi    ;  ..
        mov     [esp+MONT_SQUARE_SAVE_EBP],ebp    ;  ..

        mov     esi,[esp+MONT_SQUARE_MODULUS]     ; get modulus    
        mov     ebx,[esp+MONT_SQUARE_MONT_SQUARE] ; get MontSquare
        mov     eax,[esi+CMP_INT_LENGTH]          ; modulus length
        mov     [esp+MONT_SQUARE_MLENGTH],eax     ; save modulus length 
        add     eax,eax                           ; mlength * 2
        mov     [esp+MONT_SQUARE_MLENGTH2],eax    ; save mlength * 2

        lea     eax,[eax+3]              ; (mlength * 2) + 3
        cmp     eax,[ebx+CMP_INT_SPACE]  ; see if montSquare is big enough
        ja      ReallocMontSquare        ; jump if need more space for value

PointToMontSquareValue:
        mov     edi,[ebx+CMP_INT_VALUE]  ; montSquare.value

; set the montSquare value to zero
;
        mov     eax,[esp+MONT_SQUARE_MLENGTH2] ; recall mlength2
        lea     ecx,[eax+3]              ; ecx holds the count of dwords
        xor     eax,eax                  ; eax holds the value to fill with
        rep stosd                        ; zeroes all ecx (mlength+3) WORDS
                                         ; edi now points past end of value
        mov     dword ptr [ebx+CMP_INT_LENGTH],1 ; length of montSquare made 1

; Prepare for call to
;  CMP_VectorMultiply
;    (operand->value[i], operand, i + 1, operand->length - (i + 1),
;     montSquare, (2 * i) + 1)
;
        mov     [esp+MONT_SQUARE_ARG_5],ebx   ; montSquare to stack
        mov     ebx,[ebx+CMP_INT_VALUE]       ; montSquare.value   
        xor     edi,edi                       ; initialize i to 0
        mov     esi,[esp+MONT_SQUARE_OPERAND] ; get operand
        mov     ebp,[esi+CMP_INT_LENGTH]      ; operand.length, for
                                              ;  finding loop end
        mov     [esp+MONT_SQUARE_ARG_2],esi   ; operand to stack
        mov     esi,[esi+CMP_INT_VALUE]       ; operand.value
        dec     ebp                           ; operand.length - 1
        jz      AddInTrace   ; if operand 1 CMPWord long, skip ShiftSquareAdd

; Stack now looks like this
;   arg_1 | (blank) space for operand->value[i]
;   arg_2 | operand
;   arg_3 | (blank) space for i + 1
;   arg_4 | (blank) space for operand->length - (i + 1)
;   arg_5 | montSquare
;   arg_6 | (blank) space for (2 * i) + 1
;
; Registers now look like this
;   eax | -                       esi | operand.value
;   ebx | montSquare.value        edi | i
;   ecx | -                       ebp | operand.length - 1
;   edx | -
;
NextOperandLengthLoop:
        mov     eax,esi                     ; copy operand.value
        lea     esi,[esi+edi*4]             ; &operand.value[i]
        mov     edx,edi                     ; copy i
        mov     ecx,[esi]                   ; operand.value[i]
        mov     esi,eax                     ; restore operand.value
        mov     eax,edi                     ; copy i
        shl     edx,1                       ; i * 2
        mov     [esp+MONT_SQUARE_ARG_1],ecx ; scaler to stack
        inc     eax                         ; i + 1
        inc     edx                         ; (i * 2) + 1
        mov     ecx,ebp                     ; copy operand.length - 1
        mov     [esp+MONT_SQUARE_ARG_3],eax ; i + 1 to stack
        sub     ecx,edi                     ; operand.length - 1 - i
        mov     [esp+MONT_SQUARE_ARG_6],edx ; (2 * i) + 1 to stack
        mov     [esp+MONT_SQUARE_ARG_4],ecx ; length - (i + 1) to stack
        call    _CMP_VectorMultiplyI32
        inc     edi                         ; advance i
        cmp     edi,ebp                     ; compare i to operandLength - 1 to
                                            ;  see if we are done
        jb      NextOperandLengthLoop       ; if not call ShiftSquareAdd again

        mov     eax,[esp+MONT_SQUARE_MONT_SQUARE] ; get montSquare
        mov     ecx,[esp+MONT_SQUARE_MLENGTH2]    ; get mlength2
        mov     [esp+MONT_SQUARE_ARG_2],eax       ; montSquare to stack
        mov     [esp+MONT_SQUARE_ARG_1],ecx       ; mlength2 to stack
        call    _VS_CMP_RecomputeLength

; Take the result and find montSquare * 2 by shifting left one bit
;
        mov     eax,1                       ; shift count
        mov     [esp+MONT_SQUARE_ARG_1],eax ; to stack
        call    _VS_CMP_ShiftLeftByBits        ; montSquare already on the stack

; Now do "AddInTrace" functionality
;
AddInTrace:
        mov     esi,[esp+MONT_SQUARE_OPERAND]     ; get operand again
        mov     ebx,[esp+MONT_SQUARE_MONT_SQUARE] ; get montSquare again
        mov     ecx,[esi+CMP_INT_LENGTH]          ; operand.length
        mov     esi,[esi+CMP_INT_VALUE]           ; operand.value
        mov     edi,[ebx+CMP_INT_VALUE]           ; montSquare.value

NextOperandWord:
        mov     eax,[esi]       ; operand.value[i]
        mul     eax             ; square the value, result is in edx:eax
        add     [edi],eax       ; add to low WORD of montSquare
        adc     [edi+4],edx     ; add with carry high WORDS
        jc      PropagateCarry  ; jump if need to propagate the carry

UpdatePointers:
        lea     esi,[esi+4]     ; advance operand.value
        lea     edi,[edi+8]     ; advance montSquare.value
        dec     ecx             ; decrement counter (operand.length)
        jne     NextOperandWord ; do it again if haven't processed all of
                                ;  operand's WORDs

; Prepare for next loop
; Registers now look like this
;   eax | -                       esi | -
;   ebx | montSquare              edi | -
;   ecx | -                       ebp | -
;   edx | -
;
        mov     [esp+MONT_SQUARE_ARG_5],ebx ; montSquare to stack
        mov     ecx,[esp+MONT_SQUARE_MODULUS]    ; get modulus
        mov     ebp,[esp+MONT_SQUARE_MLENGTH]    ; get modulusLen
        mov     ebx,[ebx+CMP_INT_VALUE]               ; montSquare.value
        xor     edi,edi                               ; initialize i to 0
        mov     [esp+MONT_SQUARE_ARG_2],ecx ; modulus to stack
        mov     [esp+MONT_SQUARE_ARG_3],edi ; indexA (0) to stack
        mov     [esp+MONT_SQUARE_ARG_4],ebp ; mlength to stack
        mov     [esp+MONT_SQUARE_ARG_6],edi ; i to stack

; Stack now looks like this
;   arg_1 | (blank) space for scalar
;   arg_2 | modulus
;   arg_3 | indexA (0)
;   arg_4 | modulus->length
;   arg_5 | montSquare
;   arg_6 | i
;
; Registers now look like this
;   eax | -                       esi | -
;   ebx | montSquare.value        edi | i
;   ecx | -                       ebp | modulusLen
;   edx | -
;
HandleModulusLoop:
        mov     eax,[ebx]                           ; get montSquare.value[i]
        mul     dword ptr[esp+MONT_SQUARE_N0_PRIME] ; multiply by n0Prime
        mov     [esp+MONT_SQUARE_ARG_1],eax         ; scalar to stack
        call    _CMP_VectorMultiplyI32
        inc     edi                          ; advance i
        mov     [esp+MONT_SQUARE_ARG_6],edi  ; i to stack
        lea     ebx,[ebx+4]                  ; advance montSquare.value
        cmp     edi,ebp                      ; done? (compare to modulusLen)
        jb      HandleModulusLoop            ; if not process another
                                             ;  montSquare WORD

        mov     eax,[esp+MONT_SQUARE_MONT_SQUARE] ; get montSquare
        mov     edx,[esp+MONT_SQUARE_MLENGTH2]   ; get mlength2
        mov     [esp+MONT_SQUARE_ARG_1],ebp ; modulus length to stack
        mov     [esp+MONT_SQUARE_ARG_2],eax ; montSquare to stack
        inc     edx                                   ; mlength2 + 1
        mov     [eax+CMP_INT_LENGTH],edx ; montSquare.length = mlength2 + 1

; Stack now looks like this:
;   arg_1 | mlength
;   arg_2 | montSquare
;
        call    _VS_CMP_ShiftRightByCMPWords
        call    _VS_CMP_RecomputeLength      ; parameters still on stack

        mov     eax,[esp+MONT_SQUARE_MODULUS]    ; get modulus
        mov     [esp+MONT_SQUARE_ARG_1],eax ; modulus to stack
        call    _VS_CMP_Compare              ; montSquare is still arg_2

        or      eax,eax              ; test return value
        je      ReturnAnswerOfZero   ; if equal, answer is 0
        jns     ReturnWithZeroStatus ; if strictly positive then
                                     ;  modulus > montSquare, we have answer

; montSquare > modulus, find montSquare -= modulus
; the arguments are ready on the stack.
;
        call    _VS_CMP_SubtractInPlace ; return value in EAX from this call is
                                     ;  same as that for this function

RestoreStackAndReturnTheValueInEAX:
        mov     ebx,[esp+MONT_SQUARE_SAVE_EBX] ; Restore the contents of
        mov     esi,[esp+MONT_SQUARE_SAVE_ESI] ;  these registers
        mov     edi,[esp+MONT_SQUARE_SAVE_EDI] ;  ..
        mov     ebp,[esp+MONT_SQUARE_SAVE_EBP] ;  ..
        add     esp,MORE_STACK_SPACE           ; Restore the stack
        ret

ReturnWithZeroStatus:
        xor     eax,eax              ; return value should be 0   
        jmp short RestoreStackAndReturnTheValueInEAX

ReturnAnswerOfZero:
        mov     esi,[esp+MONT_SQUARE_MONT_SQUARE] ; get montSquare
        mov     dword ptr [esi+CMP_INT_LENGTH],1  ; set montSquare.length to 1
        mov     esi,[esi+CMP_INT_VALUE]           ; &montSquare.value[0]
        xor     eax,eax                           ; eax = 0
        mov     [esi],eax                         ; montSquare.value[0] = 0
        jmp short RestoreStackAndReturnTheValueInEAX

PropagateCarry:
        lea     edx,[edi+8]       ; point to next montSquare WORD
NextCarry:
        adc     dword ptr [edx],0 ; add in the carry
        jnc     UpdatePointers    ; if no carry out this time contine
        lea     edx,[edx+4]       ; if there is another carry generated
        jmp short NextCarry       ;  add it in too.

; Allocate enough space for montSquare
;   eax contains size, arg_1
;   ebx contains montSquare, arg_2
;
ReallocMontSquare:
        mov     [esp+MONT_SQUARE_ARG_1],eax ; 1st arg is size
        mov     [esp+MONT_SQUARE_ARG_2],ebx ; 2nd arg is montSquare
        call    _CMP_reallocNoCopy          ; return value comes back in EAX

        test    eax,eax                     ; test return value
        je      PointToMontSquareValue      ; if zero was able to realloc
        jmp short RestoreStackAndReturnTheValueInEAX

_CMP_MontSquareI32 ENDP

_TEXT	ENDS
END
