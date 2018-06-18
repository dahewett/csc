;
; CSc 230 Assignment 2 Part 2 Programming
; Question 2  Factorial
;  
; YOUR NAME GOES HERE:  Devin Hewett V00821219
;	Date: Feb 08, 2016
;
.include "m2560def.inc"
; This program . . . (edit this line)

;
; Where:
;
;   (result) . . . (edit this line) 
 
;
.cseg
.;org 0x0000
;  Obtain the constant from location init
	ldi zH, High(init<<1)
	ldi zL, low(init<<1)
	lpm r16, Z

;***
; YOUR CODE GOES HERE:
;
;main:	ldi r16, zL (RAMEND)
;		out	SPL, r16
;		ldi r16, zH (RAMEND)
;		out SPH, r16
.def	al = r25
.def	ah = r24
.def	bl = r22
.def	bh = r23
.def	byte_a = r20
.def	c = r21

;question 1
addTwo:	ldi al, zL 
		ldi	ah, zH
		ldi bl, zL
		ldi bh, zH
		add ah, bh
		add al, bl

;question 2

		ldi al, zL
		ldi ah, zH
		ldi byte_a, init
		ldi c, init
		rcall mult
		sts result+1, r25
		sts result, r24

mult:	clr bl
		clr bh
loop:	lsr ah
		ror al
		brcc skip
		add bl, al
		add bh, ah
skip:	ror bl
		ror bh
		dec c
		brne loop
		 

















; YOUR CODE FINISHES HERE
;****

done:	jmp done

; The constant, named init, holds the starting number.  
init:	.db 0x03, 0x00

; This is in the data segment (ie. SRAM)
; The first real memory location in SRAM starts at location 0x200 on
; the ATMega 2560 processor.  
;
.dseg
.org 0x200

result:	.byte 2

