;
; screen handling primitives
;
; by: jim nutt
;

.model large

.data

vseg    dw      0b000h
vmode   db      ?
x       dw      0
y       dw      0
color   db      07h
ofs     dw      0
xhite   db      8

; video information block

VIOinfo struc
	level   db      ?
		db      ?
		dw      ?
	flags   dw      ?
	mode    db      ?
		db      ?
	colors  dw      ?
	pixcol  dw      ?
	pixrow  dw      ?
	txtcol  dw      ?
	txtrow  dw      ?
VIOinfo ends

info    VIOinfo <0,0,14,1,0,0,2,0,0,80,25>

.code

public _VIOopen, _VIOclose, _VIOcolumns, _VIOrows, _VIOmode
public _VIOscrollright, _VIOscrollleft, _VIOscrollup, _VIOscrolldown
public _VIOclear, _VIOputc, _VIOputs, _VIOgetca, _VIOgetra, _VIOheight,
public _VIOsetfore, _VIOsetback, _VIOgetfore, _VIOgetback
public _VIOgotoxy, _VIOupdate, _VIOwherex, _VIOwherey, _VIOputr
public _VIOcursor, _VIOsegment, _VIOsetSegment, _VIOsetRows, _VIOsetCols

;int  _far _pascal VIOheight(void)

_VIOheight proc

	mov al, xhite;
	xor ah,ah;
	ret

_VIOheight endp

;int  _far _pascal VIOopen(void);

_VIOopen proc

	push ds

	mov ax,3000h            ; get dos version, v4 can do this from dos
	int 21h

	cmp al,4
	je odos4

	mov ax,0f00h            ; get screen mode and width
	int 10h

	mov vmode, al

	cmp al,7
	je mono

	xor al,al
	xchg al,ah
	mov info.txtcol,ax
	mov vseg,0b800h

	push di
	mov ax,0fe00h
	mov es,vseg
	mov di,0
	int 10h
	pop di
	mov vseg,es

	push bp                 ; how many rows
	mov ax,1130h
	mov bh,1h
	xor dx,dx
	int 10h
	pop bp

	cmp dl,0
	je cga

	mov xhite,cl
	inc dl
	xor dh,dh
	mov info.txtrow,dx

mono:   mov ax,0
	pop ds
	ret

odos4:  mov ax,440ch
	mov bx,0
	mov cx,037fh
	mov dx,offset info
	int 21h
	jnc l1
	pop ds
	ret

cga:    mov info.txtrow,25

l1:     mov ax,0
	pop ds
	ret

_VIOopen endp

;void _far _pascal VIOclose(void);

_VIOclose proc

	mov ax,3000h
	int 21h

	cmp al,4
	jne l2

	mov ax,440ch
	mov bx,0
	mov cx,035fh
	mov dx,offset info
	int 21h

l2:     ret

_VIOclose endp

;int  _far VIOcolumns(void);

_VIOcolumns proc

	mov ax,info.txtcol
	ret

_VIOcolumns endp

;int  _far VIOrows(void);

_VIOrows proc

	mov ax,info.txtrow
	ret

_VIOrows endp

;int  _far VIOmode(void);

_VIOmode proc

	mov al,vmode
	xor ah,ah
	ret

_VIOmode endp

;int  _far VIOwherex(void);

_VIOwherex proc

	mov ax,x
	ret

_VIOwherex endp

;int  _far VIOwherey(void);

_VIOwherey proc

	mov ax,y
	ret

_VIOwherey endp

;void _far VIOscrollright(int x1, int y1, int x2, int y2, int count);

_VIOscrollright proc

	push bp
	mov bp,sp
	pushf

	std

	push di
	push si

	mov ax,[bp+8]
	mov bx,[bp+12]
	sub bx,ax
	mov cx,info.txtcol
	mul cl
	mov dx,[bp+10]
	add dx,ax
	shl dx,1
	mov cx,[bp+10]
	sub cx,[bp+6]

	add bx,2
	mov [bp+6],cx
	mov [bp+8],bx

	mov es,vseg

sr1:    dec word ptr [bp+8]
	jz sr3
	mov bx,[bp+14]

	push ds
	mov ah,color
	mov al,20h

	push es
	pop ds

sr2:    mov di,dx
	mov si,di
	dec si
	dec si
	mov cx,[bp+6]
	rep movsw
	stosw
	dec bx
	jnz sr2

	pop ds
	mov ax,info.txtcol
	shl ax,1
	add dx,ax
	jmp sr1

sr3:    pop si
	pop di

	popf
	pop bp
	ret

_VIOscrollright endp

;void _far VIOscrollleft(int x1, int y1, int x2, int y2, int count);

_VIOscrollleft proc

	push bp
	mov bp,sp
	pushf

	push di
	push si

	mov ax,[bp+8]
	mov bx,[bp+12]
	sub bx,ax
	mov cx,info.txtcol
	mul cl
	mov dx,[bp+6]
	add dx,ax
	shl dx,1
	mov cx,[bp+10]
	sub cx,[bp+6]

	add bx,2
	mov [bp+6],cx
	mov [bp+8],bx

	mov es,vseg

sl1:    dec word ptr [bp+8]
	jz sl3
	mov bx,[bp+14]

	push ds
	mov ah,color
	mov al,20h

	push es
	pop ds

sl2:    mov di,dx
	mov si,di
	inc si
	inc si
	mov cx,[bp+6]
	rep movsw
	stosw
	dec bx
	jnz sl2

	pop ds
	mov ax,info.txtcol
	shl ax,1
	add dx,ax
	jmp sl1

sl3:    pop si
	pop di

	popf
	pop bp
	ret

_VIOscrollleft endp

;void _far VIOscrollup(int x1, int y1, int x2, int y2, int count);

_VIOscrollup proc

	push bp
	mov bp,sp
	push di
	push si

	mov es,vseg

	mov bx,[bp+6]
	mov ax,[bp+8]
	mov dx,info.txtcol
	mul dl
	add ax,bx
	shl ax,1
	shl dx,1

	push ax
	push ds
	push ax

	mov cx,[bp+10]
	sub cx,bx
	mov bx,cx

	mov ax,[bp+12]
	sub ax,[bp+8]
	mov [bp+12],ax

	push es
	pop ds
	inc word ptr [bp+14]

l9:     dec word ptr [bp+14]
	jz l11
	mov ax,[bp+12]

l10:    pop di
	mov si,di
	add si,dx
	push si
	mov cx,bx
	rep movsw
	dec ax
	jne l10

	pop di
	pop ds
	mov al,20h
	mov ah,color
	mov cx,bx
	rep stosw

	pop di
	push di
	push ds
	push di

	push es
	pop ds
	jmp l9

l11:    pop ax
	pop ds
	pop ax
	pop si
	pop di

	pop bp
	ret

_VIOscrollup endp

;void _far VIOscrolldown(int x1, int y1, int x2, int y2, int count);

_VIOscrolldown proc

	push bp
	mov bp,sp
	push di
	push si

	mov es,vseg

	mov bx,[bp+6]
	mov ax,[bp+12]
	mov dx,info.txtcol
	mul dl
	add ax,bx
	shl ax,1
	shl dx,1

	push ax
	push ds
	push ax

	mov cx,[bp+10]
	sub cx,bx
	mov bx,cx

	mov ax,[bp+12]
	sub ax,[bp+8]
	mov [bp+12],ax

	push es
	pop ds
	inc word ptr [bp+14]

l6:     dec word ptr [bp+14]
	jz l7
	mov ax,[bp+12]

l8:     pop di
	mov si,di
	sub si,dx
	push si
	mov cx,bx
	rep movsw
	dec ax
	jne l8

	pop di
	pop ds
	mov al,20h
	mov ah,color
	mov cx,bx
	rep stosw

	pop di
	push di
	push ds
	push di

	push es
	pop ds
	jmp l6

l7:     pop ax
	pop ds
	pop ax
	pop si
	pop di
	pop bp
	ret

_VIOscrolldown endp

;void _far VIOclear(int x1, int y1, int x2, int y2);

_VIOclear proc

	push bp
	mov bp,sp
	push di
	push si

	mov es,vseg

	mov ax,[bp+8]
	mov bx,[bp+6]
	mov cx,info.txtcol
	mul cl
	add ax,bx
	shl ax,1
	mov si,ax
	mov bx,[bp+10]
	sub bx,[bp+6]
	inc bx
	mov dx,[bp+12]
	sub dx,[bp+8]
	inc dx
	mov al,20h
	mov ah,color

l5:     mov di,si
	mov cx,bx
	rep stosw
	mov cx,info.txtcol
	shl cx,1
	add si,cx
	dec dx
	jne l5

	pop si
	pop di
	pop bp
	ret

_VIOclear endp

;void _far VIOputc(const char c);

_VIOputc proc

	push bp
	mov bp,sp
	push di

	mov es,vseg
	mov di,ofs

	mov ax,[bp+6]
	mov ah,color

	stosw

	mov ofs,di
	pop di

	mov ax,x
	inc ax
	cmp ax,info.txtcol
	jge cwrap

	mov x,ax

	pop bp
	ret

cwrap:  inc y
	sub ax,info.txtcol
	mov x,ax

	pop bp
	ret

_VIOputc endp

;void _far VIOputs(const char far * s);

_VIOputs proc

	push bp
	mov bp,sp
	push di
        push si
	push ds

	mov es,vseg
	mov di,ofs

	mov ah,color
	lds si,[bp+6]
	mov bx,x

l3:     lodsb
	cmp al,0
	je l4
	stosw
	inc bx

	jmp l3

l4:     mov ofs,di
	pop ds
        pop si
	pop di

	cmp bx,info.txtcol
	jge swrap

	mov x,bx

	pop bp
	ret

swrap:  inc y
	sub bx,info.txtcol
	mov x,bx

	pop bp
	ret

_VIOputs endp

;int  _far VIOgetca(const int x, const int y);

_VIOgetca proc

	push bp
	mov bp,sp

	mov es,vseg
	mov ax,[bp+8]
	mov bx,[bp+6]
	mov cx,info.txtcol
	mul cl
	add ax,bx
	shl ax,1

	xchg ax,bx
	mov ax,es:[bx]

	pop bp
	ret

_VIOgetca endp

;int *_far VIOgetra(int x1, int y1, int x2, int y2, int * b);

_VIOgetra proc

	push bp
	mov bp,sp
	push di
	push si
	push ds

	mov ax,[bp+8]           ; y1
	mov bx,info.txtcol
	mul bl                  ; y1 * width of screen
	add ax,[bp+6]
	shl ax,1                ; x1 * 2
	shl bx,1                ; width * 2
	mov cx,[bp+10]
	sub cx,[bp+6]           ; x2 - x1
	mov dx,[bp+12]
	sub dx,[bp+8]           ; y2 - y1
	inc dx
	inc cx
	les di,[bp+14]
	mov ds,vseg
	push cx

gr1:    pop cx
	push cx
	mov si,ax
	rep movsw
	add ax,bx
	dec dx
	jnz gr1

	pop cx

	pop ds
	pop si
	pop di
	pop bp
	ret

_VIOgetra endp

;void _far VIOputr(int x, int y, int w, int h, int far * b);

_VIOputr proc

	push bp
	mov bp,sp

	push ds
	push si
	push di

	mov ax,[bp+8]
	mov bx,info.txtcol
	mul bl                ; y * width
	add ax,[bp+6]
	shl ax,1
	shl bx,1

	mov es,vseg

	lds si,[bp+14]
	mov dx,[bp+10]

pr1:    mov cx,dx
	mov di,ax
	rep movsw
	add ax,bx
	dec word ptr [bp+12]
	jnz pr1

	pop di
	pop si
	pop ds

	pop bp
	ret

_VIOputr endp

;void _far VIOsetfore(const int c);

_VIOsetfore proc

	push bp
	mov bp,sp

	mov bl,color
	and bx,00f0h
	mov ax,[bp+6]
	and ax,000fh
	or  ax,bx
	mov color,al

	pop bp
	ret

_VIOsetfore endp

;void _far VIOsetback(const int c);

_VIOsetback proc

	push bp
	mov bp,sp

	mov bl,color
	and bx,000fh
	mov ax,[bp+6]
	and ax,000fh
	shl ax,1
	shl ax,1
	shl ax,1
	shl ax,1
	or  ax,bx
	mov color,al

	pop bp
	ret

_VIOsetback endp

;int  _far VIOgetfore(void);

_VIOgetfore proc

	mov al,color
	and ax,000fh
	ret

_VIOgetfore endp

;int  _far VIOgetback(void);

_VIOgetback proc

	mov al,color
	and ax,00f0h
	shr al,1
	shr al,1
	shr al,1
	shr al,1
	ret

_VIOgetback endp

;void _far VIOgotoxy(int x, int y);

_VIOgotoxy proc

	push bp
	mov bp,sp

	mov bx,[bp + 6]
	mov ax,[bp + 8]

	mov x,bx
	mov y,ax

	mov cx,info.txtcol
	mul cl

	add ax,bx
	shl ax,1

	mov ofs,ax

	pop bp
	ret

_VIOgotoxy endp

;void _far VIOupdate(int x1, int y1, int x2, int y2);

_VIOupdate proc

	mov ah,2
	mov bh,0
	mov cx,y
	mov dx,x
	mov dh,cl
	int 10h

	ret

_VIOupdate endp

;void _far VIOcursor(int _far * x, int _far * y, int _far * shape);

_VIOcursor proc

	push bp
	mov bp,sp
	push ds

	mov ah,3
	mov bh,0
	int 10h

	mov al,dl
	cbw
	lds bx,[bp + 6]
	mov [bx],ax

	mov al,dh
	cbw
	lds bx,[bp + 10]
	mov [bx],ax

	lds bx,[bp + 14]
	mov [bx],cx

	pop ds
	pop bp
	ret

_VIOcursor endp

;unsigned int  _far VIOsegment(void);

_VIOsegment proc

	mov ax, vseg
	ret

_VIOsegment endp

;void _far VIOsetSegment(unsigned int s);

_VIOsetSegment proc

	push bp
	mov bp,sp

	mov ax, [bp + 6]
	mov vseg,ax

	pop bp
	ret

_VIOsetSegment endp

;void _far VIOsetRows(int r);

_VIOsetRows proc

	push bp
	mov bp,sp

	mov ax,[bp + 6]
	mov info.txtrow,ax

	pop bp
	ret

_VIOsetRows endp

;void _far VIOsetCols(int c);

_VIOsetCols proc

	push bp
	mov bp,sp

	mov ax,[bp + 6]
	mov info.txtcol, ax

	pop bp
	ret

_VIOsetCols endp

end
