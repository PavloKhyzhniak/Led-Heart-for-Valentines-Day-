;************************************
;**
;**
;**
;************************************

; �������������� �����
RESET:
; ��������� ����������
	cli
;************************************
;---����������� ���������� ���������
;		ldi r16, 0x48
;		sts OSCCAL, r16
;************************************

;************************************
;	������������� �����
		ldi r16,high(RAMEND)	
		out SPH,r16			 	; Set Stack Pointer to top of RAM
		ldi r16,low(RAMEND)
		out SPL,r16
;************************************

;************************************

	;Port Pin Configurations
	;DDxn     PORTxn	PUD (in 
	;					MCUCR2)         I/O        Pull-up     	Comment
	;0 			0 		X 				Input      No        	Tri-state (Hi-Z)
	;0 			1 		0 				Input      Yes			Pxn will source current if ext. pulled low.
	;0 			1 		1 				Input      No        	Tri-state (Hi-Z)
	;1 			0 		X 				Output     No	        Output Low (Sink)
	;1 			1 		X 				Output     No        	Output High (Source)
	
;-------------------------- ����������� ������������� ����������
;		lds		r16, SFIOR
;		ori		r16, 0<<PUD	
;		out		SFIOR, r16	

;DDxn PORTxn PUD(in MCUCR)	I/O 	Pull-up Comment
; 0		 0		X Input 	No 		Tri-state (Hi-Z)
; 0		 1		0 Input 	Yes		Pxn will source current if ext. pulled low
; 0		 1		1 Input 	No 		Tri-state (Hi-Z)
; 1		 0		X Output 	No 		Output low (sink)
; 1		 1		X Output 	No 		Output high (source)

;-------------------------- ������������� ����� �����/������ B

		ldi		r16, 0xFF	; ���������� ����� $00 � ������� temp
		out		DDRB, r16	; ���������� ��� ����� � DDR�
		ldi		r16, 0x00	; ���������� ����� $00 � ������� temp
		out		PORTB, r16	; ���������� ��  �� ����� � PORT�

;-------------------------- ������������� ����� �����/������ �

		ldi		r16, 0xFF	; ���������� ����� $00 � ������� temp
		out		DDRC, r16	; ���������� ��� ����� � DDR�
		ldi		r16, 0x00	; ���������� ����� $00 � ������� temp
		out		PORTC, r16	; ���������� ��  �� ����� � PORT�

;-------------------------- ������������� ����� �����/������ D

		ldi		r16, 0xFF	; ���������� ����� $00 � ������� temp
		out		DDRD, r16	; ���������� ��� ����� � DDR�
		ldi		r16, 0x00	; ���������� ����� $00 � ������� temp
		out		PORTD, r16	; ���������� ��  �� ����� � PORT�

;************************************

;************************************
; �������� ������������� ������������� ���� ����������� �� ������ ����
;������� ADCSRB
;Bit 	7	 6 	5 	4 	3	 	2 			1 			0
;		� ACME	 �	 �	 �	 ADTS2        ADTS1        ADTS0        
;ldi temp, (1<<ACME)
;sts ADCSRB, temp 
; ������ ������� ������� ���� �������������
; �� ���� ������� ��� �� ���� REF ����� �����������
;������� ADMUX
;Bit 	7		 6			 5 		4 		3 			2 			1 			0
;	REFS1       REFS0      ADLAR	 �	 MUX3        MUX2        MUX1        MUX0        
;ldi temp, 0xC7
;sts ADMUX, temp

	; ������� ACSR
	;7		6		5		4		3		2		1		0
	;ACD    ACBG    ACO 	ACI 	ACIE    ACIC    ACIS1   ACIS0  
	;7-ACD: ��������� (1) ���������(0) ����������
	;6-ACBG:(1) ����������� � ���������������� ����� ����������� ����������� ���, (0) �� ���������
	;5-ACO:��������� ���������
	;4-ACI:���� ����������
	;3-ACIE:���������� ���������� (1)
	;2-ACIC:(1) ����������� ����������� � ����� ������� ������� �1
	;1-ACIS1:������� ������������ ����������
	;0-ACIS0:
	;00 ����� ��������� 
	;10 � 1 �� 0
	;11 � 0 �� 1
	;ldi temp, (1<<ACD)		; ���������� �����������
;-------------------------- ������������� �����������
; ��������� ���������� ���������� ��� ������ ����������
		ldi r16, 0x80		; ���������� �����������
		out ACSR, r16

;		in r16,ACSR
;		sbr r16, (1<<ACIE)
;		out ACSR, r16
;************************************
; �������� ����������� ���������� �� ������� ���������
; Pin Change Interrupt Control Register - PCICR
; ������� PCICR
;	Bit 7 6 5 4 3 	2 		1 		0
;		� � � � � PCIE2    PCIE1    PCIE0          
;	ldi r16, (1<<PCIE0)|(1<<PCIE1)|(1<<PCIE2)
;	sts PCICR, r16

;!!! ������� ��� ���������� ���������� ����� � � ��� ������
; ���� ���� ��������� �� �����)))
; ������� ����� �� ����������� ���� �� ������ ��� ��
;Pin Change Mask Register 2 � PCMSK2
; ������� PCMSK2
;Bit 	7 		6 		5		 4		 3		 2		 1		 0
;	PCINT23   PCINT22   PCINT21  PCINT20 PCINT19 PCINT18 PCINT17 PCINT16        
;	ldi r16, (1<<PCINT21)|(1<<PCINT22)
;	sts PCMSK2, r16

;Pin Change Mask Register 1 � PCMSK1
; ������� PCMSK1
;   Bit 7 6 	   5		4 		3		 2		 1		 0
;		� PCINT14  PCINT13  PCINT12 PCINT11  PCINT10 PCINT9  PCINT8 
;	ldi r16, (1<<PCINT8)|(1<<PCINT9);|(1<<PCINT13)
;	sts PCMSK1, r16

; Pin Change Mask Register 0 � PCMSK0
; ������� PCMSK0
; Bit 		7 	6		5		4		3		2		1		0
;		PCINT7  PCINT6  PCINT5  PCINT4  PCINT3  PCINT2  PCINT1  PCINT0  
;	ldi r16, (1<<PCINT6)|(1<<PCINT7)
;	sts PCMSK0, r16
;-------------------------- ������������� ���������� ������� INT0/INT1
		
		;ldi r16, 0b00001000
		;out MCUCR, r16
		;ldi r16,0b10000000
		;out GIMSK, r16

;************************************

;************************************
;-------------------------- ��������� ���
;		ldi r16, 0x21			; ����� ������� ������������������� ���	�		
;		sts ADMUX, r16			; �� 1-� ����� (�� 0 �� 7 � ��� 8 �������)
		; ��������� ������ ���, ������� ������� +5� �� ����!!!
;-----------
;		ldi r16, 0xDE			; ����� ������������ ��������������
;		sts ADCSRA, r16
;************************************

;************************************
 	;Timer/Counter Control Register A � TCCR0A
	;7		6		5		4		3		2		1		0
	;COM0A1 COM0A0  COM0B1  COM0B0 	� 		� 		WGM01   WGM00
	; Bits 7:6 � COM0A1:0: Compare Match Output A Mode
	; Bits 5:4 � COM0B1:0: Compare Match Output B Mode
	; Bits 1:0 � WGM01:0: Waveform Generation Mode
	; Compare Output Mode, non-PWM Mode
	;COM0A1 COM0A0  Description
	;0 		0 		Normal port operation, OC0A disconnected.
	;0 		1 		������������� OC0A on Compare Match
	;1 		0 		��������� OC0A on Compare Match
	;1 		1 		��������������� OC0A on Compare Match
	; Compare Output Mode, Fast PWM Mode(1)
	;COM0A1 COM0A0  Description
	;0 		0 		Normal port operation, OC0A disconnected.
	;0 		1 		WGM02 = 0: Normal Port Operation, OC0A Disconnected.
	;				WGM02 = 1: ������������� OC0A on Compare Match.
	;1 		0 		��������� OC0A on Compare Match, set OC0A at TOP
	;1 		1 		��������������� OC0A on Compare Match, clear OC0A at TOP
	; Compare Output Mode, Phase Correct PWM Mode(1)
	;COM0A1 COM0A0  Description
	;0 		0 		Normal port operation, OC0A disconnected.
	;0 		1 		WGM02 = 0: Normal Port Operation, OC0A Disconnected.
	;				WGM02 = 1: ������������� OC0A on Compare Match.
	;1 		0 		Clear OC0A on Compare Match when up-counting. 
	;				Set OC0A on Compare Match when down-counting.
	;1 		1 		Set OC0A on Compare Match when up-counting. 
	;				Clear OC0A on Compare Match when down-counting.
	; ��� COMOBx - ���� �����
	;Waveform Generation Mode Bit Description (WGM2 in TCCR0B)
	;Mode     WGM2     WGM1     WGM0 	Timer/Counter 	TOP		Update of	TOV Flag
	;									Mode of 				OCRx at		Set on
	;									Operation 
	;0 			0 		0 		0       Normal 			0xFF    Immediate   MAX
	;1 			0 		0 		1       PWM, Phase 		0xFF    TOP 		BOTTOM
	;									Correct
	;2 			0 		1 		0       CTC 			OCRA    Immediate   MAX
	;									����� ��� ����������
	;3 			0 		1 		1       Fast PWM 		0xFF    TOP 		MAX
	;4 			1 		0 		0       Reserved 		� 		� 			�
	;5 			1 		0 		1       PWM, Phase 		OCRA    TOP 		BOTTOM
	;									Correct
	;6 			1 		1 		0       Reserved 		� 		� 			�
	;7 			1 		1 		1       Fast PWM 		OCRA    TOP 		TOP
	; MAX        = 0xFF,  BOTTOM = 0x00

	;Timer/Counter Control Register B � TCCR0B
	;7		6		5		4		3		2		1		0
	; FOC0A FOC0B 	� 		� 		WGM02   CS02    CS01    CS00  
	; Bit 7 � FOC0A: Force Output Compare A
	; Bit 6 � FOC0B: Force Output Compare B
	; Bits 5:4 � Res: Reserved Bits
	; Bit 3 � WGM02: Waveform Generation Mode
	; Bits 2:0 � CS02:0: Clock Select
	; Clock Select Bit Description 
	;CS02     CS01     CS00     Description
	;0 			0 		0        No clock source (Timer/Counter stopped)
	;0 			0 		1        clk/(No prescaling)
	;0 			1 		0        clk/8 (From prescaler)
	;0 			1 		1        clk/64 (From prescaler)
	;1 			0 		0        clk/256 (From prescaler)
	;1 			0 		1        clk/1024 (From prescaler)
	;1 			1 		0        External clock source on T0 pin. Clock on falling edge.
	;1 			1 		1        External clock source on T0 pin. Clock on rising edge.


	;Timer/Counter Interrupt Mask Register � TIMSK0
	;7		6		5		4		3		2		1		0
	;-      -       -    	- 		-      OCIE0B  OCIE0A  TOIE0
	; Bit 2 � OCIE0B: Timer/Counter0 Output Compare Match B Interrupt Enable
	; Bit 1 � OCIE0A: Timer/Counter0 Output Compare Match A Interrupt Enable
	; Bit 0 � TOIE0: Timer/Counter0 Overflow Interrupt Enable

; General Timer/Counter Control Register � GTCCR
; ������� TCCR
;Bit 7  6 5 4 3 2 	1 		0
;	TSM � � � � � PSRASY   SRSYNC       
;-------------------------- ������������� ������� 0	

;		ldi		r16, 0x05	; ���������� ������������ �������0 � 1024,
;		out		TCCR0, r16	; ������ ������ ����� ������� � 1024 ��� ��������� ��� �������� ������� ��
;		; ��� ���������� ����� � 8���, ������� ����� 0,0078 ���!!!
;		ldi		r16, T0PRE	; �������� ��������� �������� �������0
;		out		TCNT0, r16	; ������ ���� 8-�� ������� ������� � ����� 255-32
;							; ���������� ���������� ��� ������������, �.�. ���������� ����� 255
;
;		ldi		r16, 0x01	; ��������� ���������� �� ������������ �������0 � �������2
;		sts		TIMSK, r16	; 
;************************************

;************************************
;-------------------------- ������������� ������� 2	

;		ldi		r16, 0x05	; ���������� ������������ �������0 � 1024,
;		sts		TCCR2, r16	; ������ ������ ����� ������� � 1024 ��� ��������� ��� �������� ������� ��
;		; ��� ���������� ����� � 8���, ������� ����� 0,0078 ���!!!
;		ldi		r16, T2PRE	; �������� ��������� �������� �������0
;		sts		TCNT2, r16	; ������ ���� 8-�� ������� ������� � ����� 255-32
;							; ���������� ���������� ��� ������������, �.�. ���������� ����� 255
;
;		ldi		r16, TIMSK	; ��������� ���������� �� ������������ �������0 � �������2
;		ori		r16, TOIE2<<1
;		sts		TIMSK, r16	; 
;************************************

;************************************
; �������� ����� ���
; MCU Control Register � MCUCR	
; ������� MCUCR
;	Bit 7 6 5 4  3   2   1  0
;		SE SM2 SM1 SM0 ISC11 ISC10 ISC01 ISC00 	
	ldi r16, (1<<SE)	
	out SMCR, r16
;************************************

;************************************
	;Watchdog Timer Control Register - WDTCSR
	;7		6		5		4		3		2		1		0
	;WDIF   WDIE    WDP3    WDCE    WDE     WDP2    WDP1    WDP0  
	; Bit 7 - WDIF: Watchdog Interrupt Flag
	; Bit 6 - WDIE: Watchdog Interrupt Enable
	; Bit 4 - WDCE: Watchdog Change Enable
	; Bit 3 - WDE: Watchdog System Reset Enable
	; Bit 5, 2..0 - WDP3..0: Watchdog Timer Prescaler 3, 2, 1 and 0
	;WDTON(1)	WDE WDIE    Mode 					Action on Time-out
	;	1 		0 	0 		Stopped 				None
	;	1 		0 	1 		Interrupt Mode 			Interrupt
	;	1 		1 	0 		System Reset Mode 		Reset
	;	1 		1 	1		Interrupt and System 	Interrupt, then go to
	;						Reset Mode				System Reset Mode
	;	0 		x 	x 		System Reset Mode 		Reset
	;Note:      1.  WDTON Fuse set to �0� means programmed and �1� means unprogrammed.
	;WDP3     WDP2     WDP1     WDP0	Number of WDT Oscillator 	Typical Time-out at
	;									Cycles						VCC = 5.0V
	;	0 		0 		0 		0 		2K (2048) cycles 			16 ms
	;	0 		0 		0 		1 		4K (4096) cycles 			32 ms
	;	0 		0 		1 		0 		8K (8192) cycles 			64 ms
	;	0 		0 		1 		1 		16K (16384) cycles 			0.125 s
	;	0 		1 		0 		0 		32K (32768) cycles 			0.25 s
	;	0 		1 		0	 	1 		64K (65536) cycles 			0.5 s
	;	0 		1 		1 		0 		128K (131072) cycles 		1.0 s
	;	0 		1 		1 		1 		256K (262144) cycles 		2.0 s
	;	1 		0 		0 		0 		512K (524288) cycles 		4.0 s
	;	1 		0 		0 		1 		1024K (1048576) cycles 		8.0 s
;--------------------------- ���������� ����������� �������
WDT_off:
; Turn off global interrupt
cli
; Reset Watchdog Timer
wdr
; Clear WDRF in MCUSR
in r16, MCUSR
andi r16, (0xff & (0<<WDRF))
out MCUSR, r16
; Write logical one to WDCE and WDE
; Keep old prescaler setting to prevent unintentional time-out
lds r16, WDTCSR
ori r16, (1<<WDCE) | (1<<WDE)
sts WDTCSR, r16
; Turn off WDT
ldi r16, (0<<WDE)
sts WDTCSR, r16
; Turn on global interrupt
sei
;ret
;************************************

;************************************
; ������� ���� ������� ���������

	clr R16
	clr R17
	clr R18
	clr R19
	clr R20
	clr ZL
	clr ZH

; ������� ��������� ������� ���� ����������������� �������
;	ldi r16,2
;	sts Power, r16



; ���������� ����������
	sei ; Enable interrupts

// ������� � ������� ������� ���������
	rjmp main
;************************************
