@ECHO OFF
"C:\Program Files (x86)\Atmel\AVR Tools\AvrAssembler2\avrasm2.exe" -S "C:\School\Csc 230\Lab 7\labels.tmp" -fI -W+ie -C V3 -o "C:\School\Csc 230\Lab 7\numDisplay.hex" -d "C:\School\Csc 230\Lab 7\numDisplay.obj" -e "C:\School\Csc 230\Lab 7\numDisplay.eep" -m "C:\School\Csc 230\Lab 7\numDisplay.map" "C:\School\Csc 230\Lab 7\numDisplay.asm"
