#define LCD_LIBONLY
.include "lcd.asm"

.cseg

	call lcd_init
	call lcd_clr
	call init_strings

	push r20
	ldi r20, 0x03
loop:
	dec r20
	cpi r20, 0 
	call disp_str
	call delay_sec

	call lcd_clr
	;call disp_rev

	brne loop
	pop r20


lp: jmp lp

init_strings:
	push r16
	ldi r16, high(msg1)
	push r16
	ldi r16, low(msg1)
	push r16

	ldi r16, high(msg1_p << 1)
	push r16
	ldi r16, low(msg1_p << 1) 
	push r16
	call str_init ;copy into data memory
	pop r16
	pop r16
	pop r16
	pop r16
	
	ldi r16, high(msg2)
	push r16
	ldi r16, low(msg2)
	push r16
	ldi r16, high(msg2_p << 1)
	push r16
	ldi r16, low(msg2_p << 1)
	push r16
	call str_init ;copy into data memory
	pop r16
	pop r16
	pop r16
	pop r16

	pop r16
	ret

disp_str:
	push r16
	call lcd_clr

	;set XY to the first line
	ldi r16, 0x00
	push r16
	ldi r16, 0x00
	push r16
	call lcd_gotoxy
	pop r16
	pop r16

	;Display msg1 on first line
	ldi r16, high(msg1)
	push r16
	ldi r16, low(msg1)
	push r16
	call lcd_puts
	pop r16
	pop r16

	;Move XY cursor to the second line
	ldi r16, 0x01
	push r16
	ldi r16, 0x00
	push r16
	call lcd_gotoxy
	pop r16
	pop r16

	;Display msg2 on the second line
	ldi r16, high(msg2)
	push r16
	ldi r16, low(msg2)
	push r16
	call lcd_puts
	pop r16
	pop r16
	
	pop r16
	ret

;disp_rev:
;	ldi        ZH,high(msg1_p<<1)    ;Set Z pointer to message
 ;   ldi        ZL,low(msg1_p<<1)    
  ;  rcall    get_length        ;call subroutine to get length
   ; ldi        XH,high(msg1)    ;Set X pointer to destination in
    ;ldi        XL,low(msg1)    ; data memory.
    ;add        XL,r17            ;Add count to X pointer,
;lop:
;	lpm
;get_length:
 ;   push    ZH
  ;  push    ZL
   ; ldi        r17,0
;subrutine that delays for one second on a 16MHz microcontroller
delay_sec:
	ret

; sample strings
; These are in program memory
msg1_p: .db "Devin Hewett", 0
msg2_p: .db "UVIC: Computer Sci", 0
.dseg
;
; The program copies the strings from program memory
; into data memory.
;
msg1: .byte 200
msg2: .byte 200
; These strings contain the 18 characters to be displayed on the LCD
; Each time through, the 18 characters are copied into these memory locations
line1: .byte 19
line2: .byte 19
line3: .byte 19
line4: .byte 19
