@ECHO OFF
"C:\Program Files (x86)\Atmel\AVR Tools\AvrAssembler2\avrasm2.exe" -S "C:\School\Csc 230\Assignment 2\labels.tmp" -fI -W+ie -C V3 -o "C:\School\Csc 230\Assignment 2\A2_Factorial.hex" -d "C:\School\Csc 230\Assignment 2\A2_Factorial.obj" -e "C:\School\Csc 230\Assignment 2\A2_Factorial.eep" -m "C:\School\Csc 230\Assignment 2\A2_Factorial.map" "C:\School\Csc 230\Assignment 2\A2_Factorial.asm"