; by: David Nugent via ECPROG echo
;
; works VERY reliably under all the protected mode environments I've
; tried (namely DV and PC-MOS). Haven't tried VM386 or NX386 yet, but
; I'm hopeful.... ;-)
 
 
BIOS_POST  equ    0472H        ; POST (warm boot) flag
 
 
        xor BX,BX               ; AL=1 for warm boot, 0 for cold
        mov ES,BX
        cmp AL,1
        jnz @NcB
        mov AX,1234H            ; Avoid POST
@NcB:
        mov ES:[BIOS_POST],AX   ; Install flag
 
        cli                     ; Reboot
        xor AX,AX
        mov DS,AX
        mov ES,AX
        mov SS,AX
        mov SP,AX
@cP:
        in AL,64H               ; Wait on AT keyboard controller
        test AL,2
        jne @cP
 
        xor AL,AL               ; Try reset lines
        out 64H,AL
        iodelay
        mov AL,0FEh
        out 64H,AL
        iodelay
        mov AX,0002H            ; Jump to reset vector
        push AX                 ; via IRET
        mov AX,0F000H
        push AX
        mov AX,0FFF0H
        push AX
        iret
