ldi r20, 0x01
del1: nop
ldi r21, 0x01
del2: nop
ldi r22, 0xFF
del3: nop
dec r22
brne del3
dec r21
brne del2
dec r20
brne del1
