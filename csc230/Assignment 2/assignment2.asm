.cseg

	;ldi 	R20, 33
	;subi	R20, 033
here:	NOP
		RJMP here

done: jmp done

.dseg
.org 0x200
