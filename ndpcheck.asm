        page    55, 132

;
;  FUNCTION:  ndp_check
;
;  Require MASM 5.1 or later, or equivalent
;
;  Assemble with:       MASM /Mx /z ...
;                       TASM /jMASM /mx /z ...
;

%       .MODEL  memodel,C               ;Add model support via
                                        ;command line macros, e.g.
                                        ;MASM /Mx /Dmemodel=LARGE

        .CODE

control dw      0

;---------------------------------------------------------------
;
; Check for an NDP.
;
;  Returns 0 if no coprocessor
;  Returns 1 if coprocessor present

        PUBLIC  ndp_check

ndp_check       PROC    USES BX
        xor     BX,BX                    ; set up zero return
        fninit                           ; try to initialize the NDP
        mov     byte ptr control+1,0     ; clear memory byte
        fnstcw  control                  ; put control word in memory
        mov     AH,byte ptr control+1    ; if AH is 03h, you got
        cmp     AH,03h                   ;   an NDP on board !!
        jne     SHORT NDPbye
        inc     BX
NDPbye:
        mov     AX,BX
        ret

ndp_check       ENDP

        end
