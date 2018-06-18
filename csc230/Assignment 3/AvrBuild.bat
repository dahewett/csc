@ECHO OFF
"C:\Program Files (x86)\Atmel\AVR Tools\AvrAssembler2\avrasm2.exe" -S "C:\School\Csc 230\Assignment 3\labels.tmp" -fI -W+ie -C V3 -o "C:\School\Csc 230\Assignment 3\display.hex" -d "C:\School\Csc 230\Assignment 3\display.obj" -e "C:\School\Csc 230\Assignment 3\display.eep" -m "C:\School\Csc 230\Assignment 3\display.map" "C:\School\Csc 230\Assignment 3\display.asm"
