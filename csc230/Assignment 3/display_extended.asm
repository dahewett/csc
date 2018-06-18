;Devin Hewett Csc 230 V00821219
;Assignment 3 (EXTENDED)
#define LCD_LIBONLY
.include "lcd.asm"

.cseg

;intilize stack pointer
ldi r16, 0xFF
out SPL, r16
ldi r16, 0x21
out SPH, r16


;initialize the Analog to Digital conversion
push r16
ldi r16, 0x87
sts ADCSRA, r16
ldi r16, 0x40
sts ADMUX, r16
pop r16

;marco which initilizes the line (line, msg)
.MACRO init_l

	push r17
	
	ldi r17, high(@0)		
	push r17
	ldi r17, low(@0)
	push r17
	ldi r17, high(@1 << 1) 
	push r17
	ldi r17, low(@1 << 1)
	push r17
	call str_init			
	pop r17					
	pop r17
	pop r17
	pop r17

	pop r17
	
.ENDMACRO
;Macro which takes line and displays it on the lcd (line)
.MACRO disp
	
		
	push r18

	ldi r18, high(@0)	
	push r18
	ldi r18, low(@0)
	push r18
	call lcd_puts
	pop r18
	pop r18
	
	pop r18

.ENDMACRO

	;start of main method
main:
	
	call lcd_init ;initilize lcd display
	call lcd_clr	;clear lcd display
	call init_all_lines	;initlize all lines 
	
	;start of loop that will go through 3 times
	push r21
	ldi r21, 0x03

	loop:
		cpi r21, 0x00
		breq lpp
		dec r21
		;display line1 and line2
		call lcd_clr	;clear lcd
		call set_curs_r0_c0	;set curser on line 1
		disp line1		;display line1
		call set_curs_r1_c0	;set curser on line 2
		disp line2		;display line2
		call delay_sec	;delay 1 second
		
		;display line2 and line3
		call lcd_clr
		call set_curs_r0_c1
		disp line2
		call set_curs_r1_c1
		disp line3
		call delay_sec
		jmp loop2
		
		;Handle brne loop out of range
		lpp: jmp lp
		
	;second loop
	loop2:	
		;display line3 and line4
		call lcd_clr
		call set_curs_r0_c0
		disp line3
		call set_curs_r1_c0
		disp line4
		call delay_sec
		;display line4 and line1
		call lcd_clr	
		call set_curs_r0_c1
		disp line4
		call set_curs_r1_c1
		disp line1
		call delay_sec
		call delay_sec ;delay 2 seconds

	
		jmp loop

		pop r21

	;infite star and dot loop
	lp: 
		call lcd_clr
		call set_curs_r0_c0
		disp lineS
		call set_curs_r1_c0
		disp lineS
		call delay_sec

		call set_curs_r0_c0
		disp lineD
		call set_curs_r1_c0
		disp lineD
		call delay_sec
	
	jmp lp

call lcd_clr

; initlizes all the lines using macro and rev method
init_all_lines:
	
	init_l line1, msg1_p
	init_l line2, msg2_p
	call init_rev
	init_l lineS, msg3_p
	init_l lineD, msg4_p

	ret


;set XY to the first line r0
set_curs_r0_c0:
	push r16
	
	ldi r16, 0x00
	push r16
	ldi r16, 0x00
	push r16
	call lcd_gotoxy
	pop r16
	pop r16
	pop r16
	ret

;Move XY cursor to the second line r0
set_curs_r1_c0:
	push r16

	ldi r16, 0x01
	push r16
	ldi r16, 0x00
	push r16
	call lcd_gotoxy
	pop r16
	pop r16
	pop r16
	ret

;set XY to the first line r1
set_curs_r0_c1:
	push r16
	
	ldi r16, 0x00
	push r16
	ldi r16, 0x01
	push r16
	call lcd_gotoxy
	pop r16
	pop r16
	pop r16
	ret

;Move XY cursor to the second line r1
set_curs_r1_c1:
	push r16

	ldi r16, 0x01
	push r16
	ldi r16, 0x01
	push r16
	call lcd_gotoxy
	pop r16
	pop r16
	pop r16
	ret

;reverse line 1 and line 2 and stores into line 3 and line 4
init_rev:
	.def tmp = r17

	push tmp 			 
	push ZH
	push ZL
	ldi tmp, 0x00		
	push tmp
	ldi ZH, high(line1)	
	ldi ZL, low(line1)

	rev:			
		ld tmp, Z+
		cpi tmp, 0x00
		push tmp
		brne rev
	ldi ZH, high(line3)	
	ldi ZL, low(line3)
	pop tmp	
		
	lp1:				
		pop tmp
		st Z+, tmp
		cpi tmp, 0x00
		brne lp1
	ldi tmp, 0x00		
	push tmp
	ldi ZH, high(line2)	
	ldi ZL, low(line2)

	rev2:			
		ld tmp, Z+
		cpi tmp, 0x00
		push tmp
		brne rev2
	ldi ZH, high(line4)	
	ldi ZL, low(line4)
	pop tmp	
		
	lp2:			
		pop tmp
		st Z+, tmp
		cpi tmp, 0x00
		brne lp2
	pop ZL
	pop ZH
	pop tmp
	.undef tmp
		
	ret

;subrutine that delays for one second on a 16MHz microcontroller
delay_sec:
	push r22
	push r21
	push r20
	push r24
	;button checker
	call check_button
	cpi r24, 0x14
	breq up
	cpi r24, 1
	breq down

del1:	nop
	ldi r21,0x8F
del2:	nop
	ldi r22, 0x8F
del3:	nop
	dec r22
	brne del3
	dec r21
	brne del2
	dec r20
	brne del1
	jmp done
up:
 	call up_disp
	jmp done
down:
	call down_disp
done:
	pop r24
	pop r20
	pop r21
	pop r22
	ret
;display line 1 and 2
up_disp:
	call lcd_clr	
	call set_curs_r0_c0	
	disp line1		
	call set_curs_r1_c0	
	disp line2		
	call delay_sec
	ret
;display line 3 and 4
down_disp:
	call lcd_clr
	call set_curs_r0_c0
	disp line3
	call set_curs_r1_c0
	disp line4
	call delay_sec

;check if button was pushed
check_button:
		; start a2d
		push r16
		push r17
		lds	r16, ADCSRA	
		ori r16, 0x40
		sts	ADCSRA, r16

		; wait for it to complete
wait:	lds r16, ADCSRA
		andi r16, 0x40
		brne wait

		; read the value
		lds r16, ADCL
		lds r17, ADCH

		clr r24
		cpi r17, 2
		brge skip ;if not pressed
		cpi r17, 1
		brne  a ;if down
		ldi r24,1
		jmp skip
	
a:		cpi r16, 0xC2 
		brge skip
		ldi r24, 20 ;if up

skip:	
		pop r17
		pop r16
		ret
	
; These are in program memory
msg1_p: .db "Devin Hewett", 0
msg2_p: .db "UVIC: Comp Sci", 0
msg3_p: .db "****************", 0
msg4_p: .db "................", 0

.dseg
;
; The program copies the strings from program memory
; into data memory.

.org 0x200
msg1: .byte 200
msg2: .byte 200
msg3: .byte 200
msg4: .byte 200
; These strings contain the 18 characters to be displayed on the LCD
; Each time through, the 18 characters are copied into these memory locations
line1: .byte 19
line2: .byte 19
line3: .byte 19
line4: .byte 19
lineS: .byte 19
lineD: .byte 19
