;function.asm
.cseg
.org 0

	ldi r16, 0x00
	call delay
	inc r16

done: jmp done

delay:
	inc r16
	ret
