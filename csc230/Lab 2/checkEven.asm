.cseg
.org 0

	ldi		r18,0x09		;set r18 to a number
	andi	r18,0x01		;mask and rempboes 7 bits
	cpi		r18,0x00		;compare r 18 with 0x00
	ldi		r19,0x00		;set r19 to 0x00
	brne	done			;if r18 doesnt equal 0x00, do not change r19

	ldi		r19,0x01		;if r18 did equal 0x00 set r19 to 0x01

done:	jmp done
