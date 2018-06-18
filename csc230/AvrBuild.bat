@ECHO OFF
"C:\Program Files (x86)\Atmel\AVR Tools\AvrAssembler2\avrasm2.exe" -S "C:\School\Csc 230\labels.tmp" -fI -W+ie -C V3 -o "C:\School\Csc 230\test.hex" -d "C:\School\Csc 230\test.obj" -e "C:\School\Csc 230\test.eep" -m "C:\School\Csc 230\test.map" "C:\School\Csc 230\test.asm"
