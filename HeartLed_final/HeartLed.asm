;**************************************
;** ������������ ����� FLASH
;** ������������ ������� � ���������
;** �. ��������, ���. ������, 2
;**
;**(������ ��� "�����" - ������ ������� ����, ����� ������, �� �7, "����")
;**
;** �������� �� ������ � ��������� �����
;**
;** mob: 095-725-20-14
;**
;** mob: 099-490-69-45
;**
;** mail: info@imkoteh.com
;**************************************
;**************************************
;**	��������-������� "�������"
;** ������������ ������� � ���������
;** �. ��������, ���. ������, 2
;**
;**(������ ��� "�����" - ������ ������� ����, ����� ������, �� �7, "����")
;**
;** �������� �� ������ � ��������� ���������
;**
;** mob: 066-817-76-78
;**
;** mob: 050-044-79-69
;**
;** icq: 419-543-015
;**
;** mail: info@imkoteh.com
;**************************************


;**************************************
;**	Test Programm Version 001
;**	17 Aug 2013
;** Generator Logic
;**	Mega48	1MHz
;** Blackveolet
;** Ukraine, Donetsk region, Khartsyzsk
;** blackveolet@mail.ru
;**************************************

;**************************************
; HeartLed
;**************************************
.listmac
.nolist
; ����������� ������������ ������
#include"m48def.inc"
.list
; ��������� DEVICE ��������� ������� ��� ������ ���������� ������������� ���������.
; ��� ������������� ������ ��������� ���������� ������ ��������������, ���� ����� 
; ������� ����������, ������� �� ������������ ������ ���������������. ����� ����� ������
; ��������������, ���� ����������� �������, ���� ������� EEPROM �������� ������ ����������� �����������. 
; ���� �� ��������� �� ������������ �� ��� ���������� ��������� �����������, � ����������� ����������� �� ������ ���������.
.device ATmega48


; �������� ������� ����������

; ����� �������� ������ ��������
.cseg

;ATmega48
.org 0x0000 rjmp RESET ; Reset Handler
.org 0x0001 reti;rjmp EXT_INT0 ; IRQ0 Handler
.org 0x0002 reti;rjmp EXT_INT1 ; IRQ1 Handler
.org 0x0003 reti;rjmp PCINT0 ; PCINT0 Handler
.org 0x0004 reti;rjmp PCINT1 ; PCINT1 Handler
.org 0x0005 reti;rjmp PCINT2 ; PCINT2 Handler
.org 0x0006 reti;rjmp WDT ; Watchdog Timer Handler
.org 0x0007 reti;rjmp TIM2_COMPA ; Timer2 Compare A Handler
.org 0x0008 reti;rjmp TIM2_COMPB ; Timer2 Compare B Handler
.org 0x0009 reti;rjmp TIM2_OVF ; Timer2 Overflow Handler
.org 0x000A reti;rjmp TIM1_CAPT ; Timer1 Capture Handler
.org 0x000B reti;rjmp TIM1_COMPA ; Timer1 Compare A Handler
.org 0x000C reti;rjmp TIM1_COMPB ; Timer1 Compare B Handler
.org 0x000D reti;rjmp TIM1_OVF ; Timer1 Overflow Handler
.org 0x000E reti;rjmp TIM0_COMPA ; Timer0 Compare A Handler
.org 0x000F reti;rjmp TIM0_COMPB ; Timer0 Compare B Handler
.org 0x0010 rjmp TIM0_OVF ; Timer0 Overflow Handler
.org 0x0011 reti;rjmp SPI_STC ; SPI Transfer Complete Handler
.org 0x0012 reti;rjmp USART_RXC ; USART, RX Complete Handler
.org 0x0013 reti;rjmp USART_UDRE ; USART, UDR Empty Handler
.org 0x0014 reti;rjmp USART_TXC ; USART, TX Complete Handler
.org 0x0015 reti;rjmp ADC ; ADC Conversion Complete Handler
.org 0x0016 reti;rjmp EE_RDY ; EEPROM Ready Handler
.org 0x0017 reti;rjmp ANA_COMP ; Analog Comparator Handler
.org 0x0018 reti;rjmp TWI ; 2-wire Serial Interface Handler
.org 0x0019 reti;rjmp SPM_RDY ; Store Program Memory Ready Handler

;ATmega168
;.org 0x0000 rjmp RESET ; Reset Handler
;.org 0x0002 reti; jmp EXT_INT0 ; IRQ0 Handler
;.org 0x0004 reti; jmp EXT_INT1 ; IRQ1 Handler
;.org 0x0006 reti; jmp PCINT0 ; PCINT0 Handler
;.org 0x0008 reti; jmp PCINT1 ; PCINT1 Handler
;.org 0x000A reti; jmp PCINT2 ; PCINT2 Handler
;.org 0x000C reti; jmp WDT ; Watchdog Timer Handler
;.org 0x000E reti; jmp TIM2_COMPA ; Timer2 Compare A Handler
;.org 0x0010 reti; jmp TIM2_COMPB ; Timer2 Compare B Handler
;.org 0x0012 rjmp TIM2_OVF ; Timer2 Overflow Handler
;.org 0x0014 reti; jmp TIM1_CAPT ; Timer1 Capture Handler
;.org 0x0016 reti; jmp TIM1_COMPA ; Timer1 Compare A Handler
;.org 0x0018 reti; jmp TIM1_COMPB ; Timer1 Compare B Handler
;.org 0x001A rjmp TIM1_OVF ; Timer1 Overflow Handler
;.org 0x001C reti; jmp TIM0_COMPA ; Timer0 Compare A Handler
;.org 0x001E reti; jmp TIM0_COMPB ; Timer0 Compare B Handler
;.org 0x0020 rjmp TIM0_OVF ; Timer0 Overflow Handler
;.org 0x0022 reti; jmp SPI_STC ; SPI Transfer Complete Handler
;.org 0x0024 reti; jmp USART_RXC ; USART, RX Complete Handler
;.org 0x0026 reti; jmp USART_UDRE ; USART, UDR Empty Handler
;.org 0x0028 reti; jmp USART_TXC ; USART, TX Complete Handler
;.org 0x002A reti; jmp ADC ; ADC Conversion Complete Handler
;.org 0x002C reti; jmp EE_RDY ; EEPROM Ready Handler
;.org 0x002E reti; jmp ANA_COMP ; Analog Comparator Handler
;.org 0x0030 reti; jmp TWI ; 2-wire Serial Interface Handler
;.org 0x0032 reti; jmp SPM_RDY ; Store Program Memory Ready Handler
;

;�������� ���� �����
.def temp1	= r16	;������� ������� �������(�������)
.def temp2	= r17	;������� ������� �������(�������)
.def tempL2	= r18	;��������������� ������� �������(�������)
.def tempH2	= r19	;��������������� ������� �������(�������)
.def DataByte1	= r20	;���������������� 1 �������
.def DataByte2	= r21	;���������������� 1 �������
.def DataByte3	= r22	;���������������� 1 �������
.def Time	= r23	;������� ������(�������)
.def Repeat	= r24	;������� ������(�������)
.def Step	= r25	;������� ������� �������

// ���������� ����������� ���� ������ �������
#include"DSEG.inc"		;���� �������������� ���������� � ��� � ������������� �������� � ������
;#include"EEPROM.inc"	;���� ������ � ����������������� �������
#include"RESET.inc" 	;���� �������������(������)
#include"TIM0.inc"		;���� ������ � ��������0
;#include"TIM1.inc"		;���� ������ � ��������1
;#include"TIM2.inc"		;���� ������ � ��������2
;#include"Delay.inc"		;���� ����������� ��������
;#include"SubRouters.inc"

//���������� ����������� ����
main:
; ��� ����������� ��� ������� ����� ���������	

cbi PORTB,PB0
nop
nop
sbi PORTB,PB0
nop
;rjmp main


//������������� ���������� ����
	ldi DataByte1,0b00000001
	clr DataByte2
	clr DataByte3

	clr Step
ldi Time,1
ldi Repeat,1
ldi Step,26;3
ldi TempL2,3

	rcall TIM0_Init

	rjmp HeaterEffects_n
//	rjmp HeaterEffects

rjmp main

main0:

	sleep
	nop
	rjmp PC-1

rjmp main0
