;************************************
;** Файл резервирования переменных в ОЗУ и констант
;**
;**
;************************************

;************************************
;выбор сегмента EEPROM
.eseg
.org	0x10

;eepromTu:	.BYTE 1

;************************************
.dseg
.org 0x100

DataByte1r:	.BYTE 1
DataByte2r:	.BYTE 1
DataByte3r:	.BYTE 1

;************************************


;************************************
.cseg
;запишем необходимые константы
;.equ END_DATA = '+'
;.equ START_DATA = ':'

//константы предустановок  МК
;.equ T0PRE=-5	
;.equ T2PRE=-150;-125;2	


;************************************
; инициализируем необходимые названия для выводов

; канал Tx/Rx
;.set PortX = PD2
;.set KeyTRIAC = PD2

; кнопкa 
;.set tempKey1 = PD3


.equ a = 1		; Bit 0 - a, вес разряда 1
.equ b = 2		; Bit 1 - b, вес разряда 2
.equ c = 4		; Bit 2 - c, вес разряда 4
.equ d = 8		; Bit 3 - d, вес разряда 8
.equ e = 16		; Bit 4 - e, вес разряда 16
.equ f = 32		; Bit 5 - f, вес разряда 32
.equ g = 64		; Bit 6 - g, вес разряда 64
.equ DP = 128	; Bit 7 - DP, вес разряда 128

.equ Num0 = a+b+c+d+e+f	; цифра 0
.equ Num1 = b+c			; цифра 1
.equ Num2 = a+b+d+e+g	; цифра 2
.equ Num3 = a+b+c+d+g	; цифра 3
.equ Num4 = b+c+f+g		; цифра 4
.equ Num5 = a+c+d+f+g	; цифра 5
.equ Num6 = a+c+d+e+f+g	; цифра 6
.equ Num7 = a+b+c		; цифра 7
.equ Num8 = a+b+c+d+e+f+g	; цифра 8
.equ Num9 = a+b+c+d+f+g; цифра 9

;************************************
;************************************
;Таблица констант для вывода цифр на семисегментный индикатор
; 0 1 2 3 4 5 6 7 8 9
TableIndicator:
.db Num0,Num1	;.db	0b00111111, 0b00000110
.db Num2,Num3	;.db	0b01011011, 0b01001111
.db Num4,Num5	;.db	0b01100110, 0b01101101
.db Num6,Num7	;.db	0b01111101, 0b00000111
.db Num8,Num9	;.db	0b01111111, 0b01101111


.cseg			; выбор сегмента памяти программ
;dataRX: .db ':','R','S','-','4','8','5','+'
;dataTX: .db ':','P','C','-','A','V','R','+'


;TableCHxx: 20mksec
.equ f01 =  31;1620Hz
.equ f02 =  33;1512Hz
.equ f03 =  39;1296Hz
.equ f04 =  42;1188Hz
.equ f05 =  51; 972Hz
.equ f06 =  58; 864Hz
.equ f07 =  66; 756Hz
.equ f08 =  77; 648Hz
.equ f09 =  93; 540Hz
.equ f10 = 116; 432Hz
.equ f11 = 154; 324Hz
.equ f12 = 231; 216Hz

.equ f01s =  925;54Hz
.equ f02s = 1111;45Hz
.equ f03s = 1389;36Hz
.equ f04s = 1852;27Hz
.equ f05s = 2778;18Hz
.equ f06s = 5555; 9Hz

.equ f01m = 116; 432Hz 
.equ f02m =  77; 648Hz
.equ f03m =  58; 864Hz
.equ f04m =  42;1188Hz
.equ f05m =  39;1296Hz
.equ f06m =  29;1728Hz


.equ timeLeft = 25000
.equ timeRight = 35000
.equ timeCenter = 40000
.equ timeModula = 15000


TableCHxx:
;00..20
.dw f01, f02, f03, f04, f05, f06, f07, f08, f09, f10, f11
;22..42
.dw f12, f11, f10, f09, f08, f07, f06, f05, f04, f03, f02
;44..64
.dw f01, f02, f03, f04, f05, f06, f07, f08, f09, f10, f11
;66..86
.dw f01s, f02s, f03s, f04s, f05s, f06s, f05s, f04s, f03s, f02s
;88..104
.dw f01m, f02m, f03m, f04m, f05m, f06m, f05m, f04m, f03m, f02m

