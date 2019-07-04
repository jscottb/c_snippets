        page    55, 132

;  FUNCTION:  cpu_check
;
;  Attempt to discover the type of CPU. Use MASM 5.1 or greater.
;  Returns 86 for 8088/8086, 286 for 80286, 386 for 80386/80486.
;
;  Requires MASM 5.1 or later or equivalent
;
;  Assemble with:       MASM /Mx /z ...
;                       TASM /jMASM /mx /z ...
;

%       .MODEL  memodel,C               ;Add model support via
                                        ;command line macros, e.g.
                                        ;MASM /Dmemodel=LARGE

        .CODE
;
; int cpu_check(void) - returns 86, 186, 286, 386
;

        PUBLIC  cpu_check

cpu_check       PROC    USES BX
        pushf
        xor     ax,ax                   ; zero ax
        push    ax
        popf                            ; try to put 0 into flags
        pushf
        pop     ax                      ; see what went in flags
        and     ax,0f000h               ; mask off high flag bits
        cmp     ax,0f000h               ; was high nibble ones
        je      _86                     ; is 8086 or 8088
        push    sp                      ; see if sp is updated
        pop     bx                      ; before or after it is
        cmp     bx,sp                   ; pushed
        jne     _186
        mov     ax,0f000h               ; try to set high bits
        push    ax
        popf                            ; in the flags
        pushf
        pop     ax                      ; look at actual flags
        and     ax,0f000h               ; any high bits set?
        je      _286                    ; is 80286
_386:
        .386                            ; enable 386 instructions

        pushfd                          ; save extended flags
        mov     eax,040000h
        push    eax                     ; push 40000h onto stack
        popfd                           ; pop extended flags
        pushfd                          ; push extended flags
        pop     eax                     ; put in eax
        and     eax,040000h             ; is bit 18 set?
        jne     _486                    ; yes, it's a 486
        mov     ax,386                  ; no, it's a 386
        jmp     _386x
_486:
        mov     ax,486
_386x:
        popfd                           ; clean the stack
        jmp     ccexit
_286:
        mov     ax,286                  ; is an 80286
        jmp     ccexit
_186:
        mov     ax,186                  ; is an 80188/80186
        jmp     ccexit
_86:
        mov     ax,86                   ; is an 8088/8086
ccexit:
        popf                            ; restore original flags
        ret                             ; return

cpu_check       ENDP    

        end
