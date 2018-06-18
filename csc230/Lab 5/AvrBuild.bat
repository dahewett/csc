@ECHO OFF
"C:\Program Files (x86)\Atmel\AVR Tools\AvrAssembler2\avrasm2.exe" -S "H:\Csc 230\Lab 5\labels.tmp" -fI -W+ie -C V3 -o "H:\Csc 230\Lab 5\Lab5.hex" -d "H:\Csc 230\Lab 5\Lab5.obj" -e "H:\Csc 230\Lab 5\Lab5.eep" -m "H:\Csc 230\Lab 5\Lab5.map" "H:\Csc 230\Lab 5\lab5.asm"
