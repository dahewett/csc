.cseg

	;ldi 	R20, 33
	;subi	R20, 033

	RJMP here
	NOP

here: NOP	
		

done: jmp done

.dseg
.org 0x200
