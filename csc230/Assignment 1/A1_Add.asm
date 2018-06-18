;
; CSc 230 Assignment 1 Part 2 Programming
; Programming Problem #1: Adding
;  
; YOUR NAME GOES HERE:  Devin Hewett	V00821219
;	Date: Due : Jan 28, 2017
;
.include "m2560def.inc"
; This program should sum 3 numbers together: 27, 41 and 15 (all decimal).  
;
; The result should be stored in (result).
;
; Where:
;
;   (result) refers to the byte memory location where the result is stored
;
.cseg

;***
; YOUR CODE GOES HERE:
;
	
	ldi r16, 27
	ldi r17, 41
	ldi r18, 15

	CLR r0
	ADD r0, r16
	ADD	r0, r17
	ADD	r0, r18
	
	STS result, r0










;
; YOUR CODE FINISHES HERE
;****

done:	jmp done

; This is in the data segment (ie. SRAM)
; The first real memory location in SRAM starts at location 0x200 on
; the ATMega 2560 processor.  Locations less than 0x200 are special
; and will be discussed later
;
.dseg
.org 0x200

result:	.byte 1
