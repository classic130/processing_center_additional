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

; int CMP_MontProduct
;   (multiplicand, multiplier, modulus, n0Prime, montProduct)
; CMPInt *multiplicand;
; CMPInt *multiplier;
; CMPInt *modulus;
; CMPWord n0Prime;
; CMPInt *montProduct;
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
montProdStruct struc
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
multiplicand       dd   ?
multiplier         dd   ?
modulus            dd   ?
n0Prime            dd   ?
montProduct        dd   ?
montProdStruct    ends

; Borland does not always recognize structures in instructions (and yet
; claims to be superior to Microsoft even though it screws up something
; this basic), so rename the structrue values.
;
MONT_PROD_ARG_1     EQU  montProdStruct.argument_1
MONT_PROD_ARG_2     EQU  montProdStruct.argument_2
MONT_PROD_ARG_3     EQU  montProdStruct.argument_3
MONT_PROD_ARG_4     EQU  montProdStruct.argument_4
MONT_PROD_ARG_5     EQU  montProdStruct.argument_5
MONT_PROD_ARG_6     EQU  montProdStruct.argument_6
MONT_PROD_MLENGTH   EQU  montProdStruct.mlength
MONT_PROD_MLENGTH2  EQU  montProdStruct.mlength2
MONT_PROD_SAVE_EBX  EQU  montProdStruct.saveEBX
MONT_PROD_SAVE_ESI  EQU  montProdStruct.saveESI
MONT_PROD_SAVE_EDI  EQU  montProdStruct.saveEDI
MONT_PROD_SAVE_EBP  EQU  montProdStruct.saveEBP
MONT_PROD_MULTIPLICAND  EQU  montProdStruct.multiplicand
MONT_PROD_MULTIPLIER    EQU  montProdStruct.multiplier
MONT_PROD_MODULUS       EQU  montProdStruct.modulus
MONT_PROD_N0_PRIME      EQU  montProdStruct.n0Prime
MONT_PROD_MONT_PRODUCT  EQU  montProdStruct.montProduct

; Upon entering this routine, the return address will be at [esp + 0]. So
; whatever amount we give to MORE_STACK_SPACE -- the amount to subtract off
; the stack to make room for saving information -- that is the amount offset
; from the stack pointer where we will find the return address, namely,
; [esp + MORE_STACK_SPACE]. To guarantee montProdStruct.returnAddress equals
; MORE_STACK_SPACE, simply set MORE_STACK_SPACE to
; montProdStruct.returnAddress.
;
MORE_STACK_SPACE   EQU  montProdStruct.returnAddress

; This is the
; typedef struct {
;   int space;
;   int length;
;   unsigned char *value;
; } CMPInt
;
CMP_INT_SPACE  EQU 0
CMP_INT_LENGTH EQU 4
CMP_INT_PVALUE EQU 8

; These are the subroutines we will be calling.
;
extrn _CMP_VectorMultiplyI32:near
extrn _VS_CMP_RecomputeLength:near
extrn _VS_CMP_ShiftRightByCMPWords:near
extrn _VS_CMP_Compare:near
extrn _VS_CMP_SubtractInPlace:near
extrn _CMP_reallocNoCopy:near

; entry point, it's public so other modules can access it by name, adds
; it to the symbol table
;
        public _CMP_MontProductI32
_CMP_MontProductI32 PROC NEAR
        sub     esp,MORE_STACK_SPACE          ; Set aside stack space
        mov     [esp+MONT_PROD_SAVE_EBX],ebx  ; Save the contents of
        mov     [esp+MONT_PROD_SAVE_ESI],esi  ;  these registers
        mov     [esp+MONT_PROD_SAVE_EDI],edi  ;  ..
        mov     [esp+MONT_PROD_SAVE_EBP],ebp  ;  ..

        mov     esi,[esp+MONT_PROD_MODULUS]      ; get modulus    
        mov     ebx,[esp+MONT_PROD_MONT_PRODUCT] ; get MontProduct
        mov     eax,[esi+CMP_INT_LENGTH]         ; mlength = len (modulus)
        mov     [esp+MONT_PROD_MLENGTH],eax      ; save mlength
        add     eax,eax                          ; mlength2 = mlength * 2
        mov     [esp+MONT_PROD_MLENGTH2],eax     ; save mlength2

        lea     ebp,[eax+3]              ; mlength2 + 3
        cmp     ebp,[ebx+CMP_INT_SPACE]  ; see if montProduct is big enough
        ja      ReallocMontProduct       ; jump if need more space for value

; eax | -                         esi | modulus
; ebx | montProduct               edi | -
; ecx | -                         ebp | mlength2 + 3
; edx | -
;
PointToMontProductValue:
        mov     edi,[ebx+CMP_INT_PVALUE] ; montProduct.value

; Set the mlength2 + 3 CMPWords of montProduct.value to 0 using rep stosd
;
        mov     ecx,ebp                  ; ecx contains number of words to set
        xor     eax,eax                  ; eax contains 0, the fill value
        rep stosd                        ; fills all ecx (mlength+3) WORDS at
                                         ;  address in edi with value in eax
                                         ; edi now points past end of value
        mov     dword ptr [ebx+CMP_INT_LENGTH],1 ; set length of montProduct

; Prepare for call to
;  CMP_VectorMultiply
;    (multiplicand->value[i], multiplier, 0, multiplier->length,
;     montProduct, i)
;
        mov     [esp+MONT_PROD_ARG_5],ebx         ; montProduct to stack
        mov     ebx,[ebx+CMP_INT_PVALUE]         ; montProduct.value   
        xor     edi,edi                          ; initialize i to 0
        mov     esi,[esp+MONT_PROD_MULTIPLICAND] ; get multiplicand
        mov     [esp+MONT_PROD_ARG_6],edi        ; i to stack
        mov     [esp+MONT_PROD_ARG_3],edi        ; indexA (0) to stack
        mov     ebp,[esi+CMP_INT_LENGTH]         ; multiplicand.length
                                                 ;  loop counter
        mov     esi,[esi+CMP_INT_PVALUE]         ; mulutiplicand.value

; Stack now looks like this
;   arg_1 | (blank) space for scalar
;   arg_2 | (blank) space for CMPInt
;   arg_3 | indexA = 0
;   arg_4 | (blank) space for arg_2's length
;   arg_5 | montProduct
;   arg_6 | i
;
; Registers now look like this
;   eax | -                       esi | multiplicand.value
;   ebx | montProduct.value       edi | i
;   ecx | -                       ebp | multiplicand.length
;   edx | -
;
NextMulitiplicandLengthLoop:
        mov     eax,[esi]                 ; multiplicand.value[i], the scaler
        mov     ecx,[esp+MONT_PROD_MULTIPLIER] ; get multiplier
        mov     [esp+MONT_PROD_ARG_1],eax ; scalar to stack
        mov     edx,[ecx+CMP_INT_LENGTH]  ; multiplier.length
        mov     [esp+MONT_PROD_ARG_2],ecx ; multiplier to stack
        mov     [esp+MONT_PROD_ARG_4],edx ; length to stack
        call    _CMP_VectorMultiplyI32

; Prepare for call to
;  CMP_VectorMultiply
;    (montProduct->value[i] * n0Prime, modulus, 0, modulus->length,
;     montProduct, i)
;
        mov     eax,[ebx]                ; get resulting montProduct.value[i]
        mov     ecx,[esp+MONT_PROD_MODULUS]       ; get modulus
        mul     dword ptr[esp+MONT_PROD_N0_PRIME] ; montProduct.value[i]
                                                  ;              * n0Prime
        mov     [esp+MONT_PROD_ARG_2],ecx         ; modulus to stack
        mov     [esp+MONT_PROD_ARG_1],eax         ; low (value[i] * n0Prime)
                                                  ;  to stack
        mov     ecx,[esp+MONT_PROD_MLENGTH]       ; recall modulus length
        mov     [esp+MONT_PROD_ARG_4],ecx         ; length to stack
        call    _CMP_VectorMultiplyI32
        inc     edi                              ; advance i
        lea     ebx,[ebx+4]                      ; advance montProduct.value
        lea     esi,[esi+4]                      ; advance multiplicand.value
        mov     [esp+MONT_PROD_ARG_6],edi ; i to stack
        cmp     edi,ebp                          ; compare i to
        jb      NextMulitiplicandLengthLoop      ; multiplicand.length to see
                                                 ;  if we are done
; Done processing multiplicand.length CMPWords, are there more values from
; the modulus?
;
        mov     ebp,[esp+MONT_PROD_MLENGTH]      ; recall modulus length
        cmp     edi,ebp                          ; more than
        jb      HandleModulusLoop                ;  multiplicand.length?

DetermineProperLength:
        mov     eax,[esp+MONT_PROD_MONT_PRODUCT] ; recall montProduct
        mov     edx,[esp+MONT_PROD_MLENGTH2]     ; recall mlength2
        mov     [esp+MONT_PROD_ARG_1],ebp        ; modulus length to stack
        mov     [esp+MONT_PROD_ARG_2],eax        ; montProduct to stack
        inc     edx                              ; mlength2 + 1
        mov     [eax+CMP_INT_LENGTH],edx ; montProduct.len = mlength2 + 1

; Stack now looks like this:
;   arg_1 | mlength
;   arg_2 | montProduct
;
        call    _VS_CMP_ShiftRightByCMPWords
        call    _VS_CMP_RecomputeLength         ; parameters still on stack

        mov     eax,[esp+MONT_PROD_MODULUS]  ; recall modulus
        mov     [esp+MONT_PROD_ARG_1],eax    ; modulus to stack
        call    _VS_CMP_Compare                 ; montProduct still arg_2

        or      eax,eax              ; test return value
        je      ReturnAnswerOfZero   ; if equal, answer is 0
        jns     ReturnWithZeroStatus ; if strictly positive then
                                     ;  modulus > montProduct, we have answer

; montProduct > modulus, find montProduct -= modulus
; the arguments are ready on the stack.
;
        call    _VS_CMP_SubtractInPlace ; return value in eax from this call is
                                     ;  same as that for this function
RestoreStackAndReturnTheValueInEAX:
        mov     ebx,[esp+MONT_PROD_SAVE_EBX]  ; Restore the contents of
        mov     esi,[esp+MONT_PROD_SAVE_ESI]  ;  these registers
        mov     edi,[esp+MONT_PROD_SAVE_EDI]  ;  ..
        mov     ebp,[esp+MONT_PROD_SAVE_EBP]  ;  ..
        add     esp,MORE_STACK_SPACE          ; Restore the stack
        ret

; if modulusLength > multiplicandLength
; Stack now looks like this
;   arg_1 | (blank) space for scalar
;   arg_2 | modulus
;   arg_3 | indexA = 0
;   arg_4 | modulus length
;   arg_5 | montProduct
;   arg_6 | i
;
; Registers now look like this
;   eax | -                       esi | multiplicand.value
;   ebx | montProduct.value       edi | i
;   ecx | -                       ebp | modulusLen
;   edx | -
;
HandleModulusLoop:
        mov     eax,[ebx]                           ; montProduct.value[i]
        mul     dword ptr[esp+MONT_PROD_N0_PRIME]   ; multiply by n0Prime
        mov     [esp+MONT_PROD_ARG_1],eax           ; scalar to stack
        call    _CMP_VectorMultiplyI32
        inc     edi                                 ; advance i
        lea     ebx,[ebx+4]                         ; advance montProduct.value
        mov     [esp+MONT_PROD_ARG_6],edi ; i to stack
        cmp     edi,ebp                             ; done?
        jb      HandleModulusLoop                   ;  (compare to modulusLen)
        jmp short DetermineProperLength             ; finished with loop

ReturnWithZeroStatus:
        xor     eax,eax              ; return value should be 0   
        jmp short RestoreStackAndReturnTheValueInEAX

ReturnAnswerOfZero:
        mov     esi,[esp+MONT_PROD_MONT_PRODUCT]     ; recall montProduct
        mov     dword ptr [esi+CMP_INT_LENGTH],1     ; montProduct.length = 1
        mov     esi,[esi+CMP_INT_PVALUE]             ; montProduct.value[0]
        xor     eax,eax                              ;  = 0
        mov     [esi],eax                            ;  ..
        jmp short RestoreStackAndReturnTheValueInEAX

; Allocate enough space for montProduct
;   ebp contains size, arg_1
;   ebx contains montProduct, arg_2
;
ReallocMontProduct:
        mov     [esp+MONT_PROD_ARG_1],ebp      ; 1st arg is size
        mov     [esp+MONT_PROD_ARG_2],ebx      ; 2nd arg is montProduct
        call    _CMP_reallocNoCopy             ; return value in eax

        test    eax,eax                        ; test return value
        je      PointToMontProductValue        ; if zero was able to realloc
        jmp short RestoreStackAndReturnTheValueInEAX

_CMP_MontProductI32 ENDP

_TEXT	ENDS
END
