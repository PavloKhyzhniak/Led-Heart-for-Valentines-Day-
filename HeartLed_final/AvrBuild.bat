@ECHO OFF
"C:\Program Files\Atmel\AVR Tools\AvrAssembler2\avrasm2.exe" -S "C:\AVR_USB_Work\HeartLed\labels.tmp" -fI -W+ie -C V2E -o "C:\AVR_USB_Work\HeartLed\HeartLed.hex" -d "C:\AVR_USB_Work\HeartLed\HeartLed.obj" -e "C:\AVR_USB_Work\HeartLed\HeartLed.eep" -m "C:\AVR_USB_Work\HeartLed\HeartLed.map" "C:\AVR_USB_Work\HeartLed\HeartLed.asm"
