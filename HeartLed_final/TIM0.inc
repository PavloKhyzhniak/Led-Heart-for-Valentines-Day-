;************************************
;**
;**
;**
;************************************

/*
у меня есть 22 светика которыми я могу управлять
против часовой стрелке от 12 --

		PD0 PD1 PD2 PD3 PD4 PB6 PB7 PD5
		PD6 PD7 PB0 PB1 PB2 PB3 PB4 PB5
		PC0 PC1 PC2 PC3 PC4 PC5
Bit 01 .... Bit 22
сделаем промежуточные байты хранящие эффекты 
и обработчик этих байтов на пины

DataByte1 PD5 PB7 PB6 PD4 PD3 PD2 PD1 PD0
DataByte2 PB5 PB4 PB3 PB2 PB1 PB0 PD7 PD6
DataByte3 --  --  PC5 PC4 PC3 PC2 PC1 PC0



1) эффект одиночного светика по кругу влево\вправо
2) эффект двоичного счета да максимума\ до минимума
3) зажигаем через один, вращение то вправо\то влево
4) бегаем цепочкой от 1 до 5 светиков 
*/

HeaterEffects_n:

	ldi zl,low(End_Step_n)
	ldi zh,high(End_Step_n)
	dec time	//проверяем время отработки шага,пока время не прошло ничего не меняем
	breq PC+2
	ijmp

	cpi Step,120
	brne Run
	
	clr Step
Run:
	//программа прохода шагоф - эффектов
	ldi zl,low(Step_n)
	ldi zh,high(Step_n)
push TempH2
	clr TempH2
	add zl,Step
	adc zh,TempH2
pop TempH2	
	ijmp

Step_n:
// заполнение сердечка звего к звену
	rjmp Step_n00i
	rjmp Step_n00
	rjmp Step_n01i
	rjmp Step_n01
// змейка по часовой
	rjmp Step_n02i
	rjmp Step_n02
// цепочка против часовой
	rjmp Step_n03i
	rjmp Step_n03
//быстрый эффект заполнения сердечка
	rjmp Step_n04i
	rjmp Step_n04
	rjmp Step_n05i
	rjmp Step_n05
// рисуем сердечко по часовой и против часовой стрелки
	rjmp Step_n06i
	rjmp Step_n06
	rjmp Step_n07i
	rjmp Step_n07
//бег точек по часовой стрелки
	rjmp Step_n08i	
	rjmp Step_n08	
//рисуем сердечко снизу вверх
	rjmp Step_n09i
	rjmp Step_n09
// дмагональный бег четвертинок
	rjmp Step_n10i
	rjmp Step_n10
//сердечко рисуем сверху вниз
	rjmp Step_n11i
	rjmp Step_n11
//ассиметричное сердечко
	rjmp Step_n12i
	rjmp Step_n12
//загорание звездочек
	rjmp Step_n13i
	rjmp Step_n13
//загорание всего сердечка
	rjmp Step_n14i
	rjmp Step_n14
//
	rjmp Step_n15i
	rjmp Step_n15
	rjmp Step_n16i
	rjmp Step_n16
	rjmp Step_n17i
	rjmp Step_n17
	rjmp Step_n18i
	rjmp Step_n18
	rjmp Step_n19i
	rjmp Step_n19
	rjmp Step_n20i	
	rjmp Step_n20	
	rjmp Step_n21i
	rjmp Step_n21
	rjmp Step_n22i
	rjmp Step_n22
	rjmp Step_n23i
	rjmp Step_n23
	rjmp Step_n24i
	rjmp Step_n24
	rjmp Step_n25i
	rjmp Step_n25
	rjmp Step_n26i
	rjmp Step_n26
	rjmp Step_n27i	
	rjmp Step_n27	
	rjmp Step_n28i
	rjmp Step_n28
	rjmp Step_n29i
	rjmp Step_n29
	rjmp Step_n30i
	rjmp Step_n30
	rjmp Step_n31i
	rjmp Step_n31
	rjmp Step_n32i
	rjmp Step_n32


Step_n00i:
//инициализация первого шага
	ldi temp1,0x01
	sts DataByte1r,temp1
	ldi temp1,0x00	
	sts DataByte2r,temp1
	ldi temp1,0x00
	sts DataByte3r,temp1

	ldi DataByte1,0b00000001
	clr DataByte2
	clr DataByte3

	inc Step

	ldi Repeat,22	// сколько раз повторить цепочку шагов для достижения эффекта
Step_n00:
	ldi Time,1//2	// сколько времени стоим на этом шаге(прерывания по таймеру)

	clc	// организуем сдвиг вправо
	bst DataByte1,0
	ror DataByte3
	ror DataByte2
	ror DataByte1
	bld DataByte3,5

	dec Repeat
	brne ex00//End_Step_n	//уходим на вывод результатов

	lds temp1, DataByte1r
	lds temp2, DataByte2r
	lds tempL2, DataByte3r

	sec	// организуем сдвиг влево
	rol temp1	//DataByte1r
	rol temp2	//DataByte2r
	rol tempL2	//DataByte3r

	sts DataByte1r,temp1
	sts DataByte2r,temp2
	sts DataByte3r,tempL2

	ldi Repeat,22	// сколько раз повторить цепочку шагов для достижения эффекта

	cpi tempL2,	0b00111111
ex00:	brne ex01//End_Step_n

	inc Step	// переход на новый шаг
Step_n01i:
//инициализация следующего шага
	ldi temp1,0x00
	sts DataByte1r,temp1
	ldi temp1,0x00	
	sts DataByte2r,temp1
	ldi temp1,0x20
	sts DataByte3r,temp1

	ldi DataByte1,0b00000001
	clr DataByte2
	clr DataByte3

	inc Step	// переход на новый шаг
	ldi Repeat,22	// сколько раз повторить цепочку шагов для достижения эффекта
Step_n01:
	ldi Time,1	// сколько времени стоим на этом шаге(прерывания по таймеру)

	clc	// организуем сдвиг влево
	rol DataByte1
	rol DataByte2
	rol DataByte3
	bst DataByte3,6
	bld DataByte1,0

	dec Repeat
ex01:	brne ex02//End_Step_n

	lds temp1, DataByte1r
	lds temp2, DataByte2r
	lds tempL2, DataByte3r

	sec	// организуем сдвиг влево
	ror tempL2	//DataByte3r
	ori tempL2,0x20
	ror temp2	//DataByte2r
	ror temp1	//DataByte1r

	sts DataByte1r,temp1
	sts DataByte2r,temp2
	sts DataByte3r,tempL2

	ldi Repeat,22	// сколько раз повторить цепочку шагов для достижения эффекта

	cpi temp1,	0b11111111
	brne ex02//End_Step_n

	inc Step	// переход на новый шаг

Step_n02i:
//инициализация следующего шага
	clr temp1
	sts DataByte1r,temp1
	sts DataByte2r,temp1
	sts DataByte3r,temp1

	ldi DataByte1,0b00000111
	clr DataByte2
	clr DataByte3

	inc Step	// переход на новый шаг
	ldi Repeat,88//128	// сколько раз повторить цепочку шагов для достижения эффекта
Step_n02:
	ldi Time,2	// сколько времени стоим на этом шаге(прерывания по таймеру)

	clc	// организуем сдвиг вправо
	bst DataByte1,0
	ror DataByte3
	ror DataByte2
	ror DataByte1
	bld DataByte3,5

	dec Repeat
ex02:	brne ex03//End_Step_n

	inc Step	// переход на новый шаг
Step_n03i:
//инициализация первого шага
	clr temp1
	sts DataByte1r,temp1
	sts DataByte2r,temp1
	sts DataByte3r,temp1

	ldi DataByte1,0b11111000
	ldi DataByte2,0xFF
	ldi DataByte3,0x3F

	inc Step	// переход на новый шаг
	ldi Repeat,88	// сколько раз повторить цепочку шагов для достижения эффекта
Step_n03:
	ldi Time,2	// сколько времени стоим на этом шаге(прерывания по таймеру)

	clc	// организуем сдвиг влево
	rol DataByte1
	rol DataByte2
	rol DataByte3
	bst DataByte3,6
	bld DataByte1,0
	
	dec Repeat
ex03:	brne ex04//End_Step_n

	inc Step	// переход на новый шаг

Step_n04i:
//инициализация первого шага
	ldi temp1,0x01
	sts DataByte1r,temp1
	ldi temp1,0x00	
	sts DataByte2r,temp1
	ldi temp1,0x00
	sts DataByte3r,temp1

	ldi DataByte1,0b00000001
	clr DataByte2
	clr DataByte3

	ldi TempH2,6
	inc Step
	ldi Repeat,2;22	// сколько раз повторить цепочку шагов для достижения эффекта
Step_n04:
	ldi Time,1//2	// сколько времени стоим на этом шаге(прерывания по таймеру)

	clc	// организуем сдвиг вправо
	bst DataByte1,0
	ror DataByte3
	ror DataByte2
	ror DataByte1
	bld DataByte3,5

	dec Repeat
	brne ex04//End_Step_n	//уходим на вывод результатов

	lds temp1, DataByte1r
	lds temp2, DataByte2r
	lds tempL2, DataByte3r

	sec	// организуем сдвиг влево
	rol temp1	//DataByte1r
	rol temp2	//DataByte2r
	rol tempL2	//DataByte3r

	sts DataByte1r,temp1
	sts DataByte2r,temp2
	sts DataByte3r,tempL2

	ldi Repeat,2;22	// сколько раз повторить цепочку шагов для достижения эффекта

	cpi tempL2,	0b00111111
ex04:	brne ex05//End_Step_n


	inc Step	// переход на новый шаг
Step_n05i:
//инициализация следующего шага
	ldi temp1,0x00
	sts DataByte1r,temp1
	ldi temp1,0x00	
	sts DataByte2r,temp1
	ldi temp1,0x20
	sts DataByte3r,temp1

	ldi DataByte1,0b00000001
	clr DataByte2
	clr DataByte3

	inc Step	// переход на новый шаг
	ldi Repeat,2;22	// сколько раз повторить цепочку шагов для достижения эффекта
Step_n05:

	ldi Time,1	// сколько времени стоим на этом шаге(прерывания по таймеру)

	clc	// организуем сдвиг влево
	rol DataByte1
	rol DataByte2
	rol DataByte3
	bst DataByte3,6
	bld DataByte1,0

	dec Repeat
ex05:	brne ex06

	lds temp1, DataByte1r
	lds temp2, DataByte2r
	lds tempL2, DataByte3r

	sec	// организуем сдвиг влево
	ror tempL2	//DataByte3r
	ori tempL2,0x20
	ror temp2	//DataByte2r
	ror temp1	//DataByte1r

	sts DataByte1r,temp1
	sts DataByte2r,temp2
	sts DataByte3r,tempL2

	ldi Repeat,2;22	// сколько раз повторить цепочку шагов для достижения эффекта

	cpi temp1,	0b11111111
	brne ex05//End_Step_n


//инициализация первого шага
	ldi temp1,0x01
	sts DataByte1r,temp1
	ldi temp1,0x00	
	sts DataByte2r,temp1
	ldi temp1,0x00
	sts DataByte3r,temp1

	ldi DataByte1,0b00000001
	clr DataByte2
	clr DataByte3

	ldi Repeat,2;22	// сколько раз повторить цепочку шагов для достижения эффекта

	dec Step
	dec Step
	dec TempH2
	brne ex05
	inc Step
	inc Step


	inc Step	// переход на новый шаг
Step_n06i:
//инициализация следующего шага
	clr temp1
	sts DataByte1r,temp1
	sts DataByte2r,temp1
	sts DataByte3r,temp1

	ldi DataByte1,0b00000001
	clr DataByte2
	clr DataByte3

	ldi TempL2,2;4;10

	inc Step	// переход на новый шаг
	ldi Repeat,23	// сколько раз повторить цепочку шагов для достижения эффекта
Step_n06:
	ldi Time,4	// сколько времени стоим на этом шаге(прерывания по таймеру)

	sec
	rol DataByte1
	rol DataByte2
	rol DataByte3

	dec Repeat
ex06:	brne ex07

	inc Step
Step_n07i:
//инициализация следующего шага
	clr temp1
	sts DataByte1r,temp1
	sts DataByte2r,temp1
	sts DataByte3r,temp1

	ldi DataByte3,0b00111111
	ser DataByte2
	ser DataByte1

	inc Step	// переход на новый шаг
	ldi Repeat,23	// сколько раз повторить цепочку шагов для достижения эффекта
Step_n07:
	sbrs TempL2,0
	rjmp RightLed_n
	rjmp LeftLed_n

RightLed_n:
	ldi Time,5	// сколько времени стоим на этом шаге(прерывания по таймеру)

	clc
	ror DataByte3
	ror DataByte2
	ror DataByte1
	rjmp EndLed_n

LeftLed_n:
	ldi Time,7	// сколько времени стоим на этом шаге(прерывания по таймеру)

	clc
	rol DataByte1
	rol DataByte2
	rol DataByte3
	rjmp EndLed_n

EndLed_n:
	dec Repeat
ex07:	brne ex08//End_Step_n

//инициализация следующего шага
	ldi DataByte1,0b00000001
	clr DataByte2
	clr DataByte3

	ldi Repeat,23
	dec Step
	dec Step
	dec TempL2
	brne ex08

	inc Step
	inc Step
	inc Step


Step_n08i:	
//инициализация следующего шага
	clr temp1
	sts DataByte1r,temp1
	sts DataByte2r,temp1
	sts DataByte3r,temp1

	ldi DataByte1,~0b01001001
	ldi DataByte2,~0b10010010
	ldi DataByte3,~0b00000100

	inc Step	// переход на новый шаг
	ldi Repeat,128	// сколько раз повторить цепочку шагов для достижения эффекта
Step_n08:	
	ldi Time,2	// сколько времени стоим на этом шаге(прерывания по таймеру)

	clc	// организуем сдвиг вправо
	bst DataByte1,0
	ror DataByte3
	ror DataByte2
	ror DataByte1
	bld DataByte3,5

	dec Repeat
ex08:	brne ex10;End_Step_n
	
	inc Step	// переход на новый шаг
Step_n09i:
//инициализация следующего шага
	clr temp1
	sts DataByte1r,temp1
	sts DataByte2r,temp1
	sts DataByte3r,temp1

	clr TempL2
	inc Step	// переход на новый шаг
	ldi Repeat,255	// сколько раз повторить цепочку шагов для достижения эффекта
Step_n09:
	ldi Time,3;150	// сколько времени стоим на этом шаге(прерывания по таймеру)

	//рисуем сердечко
	ldi zl,low(St0)
	ldi zh,high(St0)
	inc TempL2
	clr TempH2
	add zl,TempL2
	adc zh,TempH2
	ijmp
	

Step_n10i:
//инициализация следующего шага
	clr temp1
	sts DataByte1r,temp1
	sts DataByte2r,temp1
	sts DataByte3r,temp1

	ldi DataByte1,~0b00011111
	ldi DataByte2,~0b11111000
	ldi DataByte3,~0b00000000

	inc Step	// переход на новый шаг
	ldi Repeat,64	// сколько раз повторить цепочку шагов для достижения эффекта
Step_n10:	
	ldi Time,2	// сколько времени стоим на этом шаге(прерывания по таймеру)

	clc	// организуем сдвиг вправо
	bst DataByte1,0
	ror DataByte3
	ror DataByte2
	ror DataByte1
	bld DataByte3,5

	dec Repeat
ex10:	brne ex12;End_Step_n
	
	inc Step	// переход на новый шаг
Step_n11i:
//инициализация следующего шага
	clr temp1
	sts DataByte1r,temp1
	sts DataByte2r,temp1
	sts DataByte3r,temp1

	clr TempL2
	inc Step	// переход на новый шаг
	ldi Repeat,255	// сколько раз повторить цепочку шагов для достижения эффекта
Step_n11:
	ldi Time,3;150	// сколько времени стоим на этом шаге(прерывания по таймеру)

	//рисуем сердечко
	ldi zl,low(St0+24)
	ldi zh,high(St0+24)
	inc TempL2
	clr TempH2
	sub zl,TempL2
	sbc zh,TempH2
	ijmp

Step_n12i:
//инициализация следующего шага
	clr temp1
	ldi temp1,0b11111111
	sts DataByte1r,temp1
	ldi temp1,0b00000111
	sts DataByte2r,temp1
	clr temp1
	sts DataByte3r,temp1

	clr TempL2
	inc Step	// переход на новый шаг
	ldi Repeat,110	// сколько раз повторить цепочку шагов для достижения эффекта
Step_n12:
	ldi Time,2;150	// сколько времени стоим на этом шаге(прерывания по таймеру)

	//рисуем сердечко
	ldi zl,low(St0)
	ldi zh,high(St0)
	inc TempL2
	clr TempH2
	add zl,TempL2
	adc zh,TempH2
	ijmp
ex12: rjmp ex13
Step_n13i:
//инициализация следующего шага
	clr temp1
	sts DataByte1r,temp1
	sts DataByte2r,temp1
	sts DataByte3r,temp1

	ldi DataByte1,~0x00
	ldi DataByte2,~0x02
	ldi DataByte3,~0x00

	inc Step	// переход на новый шаг
	ldi Repeat,16	// сколько раз повторить цепочку шагов для достижения эффекта
Step_n13:
	ldi Time,20	// сколько времени стоим на этом шаге(прерывания по таймеру)

	sbrs Repeat,0
	rjmp OnLed_n
	rjmp OffLed_n
OnLed_n:
	sec
	ror DataByte3
	ror DataByte1
	ror DataByte2
	ror DataByte3
	ror DataByte1
	ror DataByte2
	ror DataByte3
	ror DataByte2
	ror DataByte1
 
OffLed_n:
	ror DataByte3
	ror DataByte1
	ror DataByte2
	ror DataByte3
	ror DataByte1
	ror DataByte2



	rjmp OnOff
OnOff:
	dec Repeat
ex13:	brne End_Step_n
	
	inc Step	// переход на новый шаг
Step_n14i:
//инициализация следующего шага
	clr temp1
	sts DataByte1r,temp1
	sts DataByte2r,temp1
	sts DataByte3r,temp1

	ldi DataByte1,0x00
	ldi DataByte2,0x00
	ldi DataByte3,0x00

	inc Step	// переход на новый шаг
	ldi Repeat,64	// сколько раз повторить цепочку шагов для достижения эффекта
Step_n14:
	ldi Time,12	// сколько времени стоим на этом шаге(прерывания по таймеру)

	ldi temp1,0b11111111
	eor DataByte1, temp1
	ldi temp1,0b11111111
	eor DataByte2, temp1
	ldi temp1,0b00111111
	eor DataByte3, temp1

	dec Repeat
ex14:	brne End_Step_n
	
	inc Step	// переход на новый шаг
Step_n15i:
Step_n15:
Step_n16i:
Step_n16:
Step_n17i:
Step_n17:
Step_n18i:
Step_n18:
Step_n19i:
Step_n19:
clr Step
rjmp Run
Step_n20i:	
Step_n20:	
Step_n21i:
Step_n21:
Step_n22i:
Step_n22:
Step_n23i:
Step_n23:
Step_n24i:
Step_n24:
Step_n25i:
Step_n25:
Step_n26i:
Step_n26:
Step_n27i:	
Step_n27:	
Step_n28i:
Step_n28:
Step_n29i:
Step_n29:
Step_n30i:
Step_n30:
Step_n31i:
Step_n31:
Step_n32i:
Step_n32:



	rjmp End_Step_n


//*******************
// обработчик на вывод 
//DataByte1 PD5 PB7 PB6 PD4 PD3 PD2 PD1 PD0
//DataByte2 PB5 PB4 PB3 PB2 PB1 PB0 PD7 PD6
//DataByte3 --  --  PC5 PC4 PC3 PC2 PC1 PC0
End_Step_n:

push DataByte1
push DataByte2
push DataByte3

push temp1
push temp2
push tempL2

	lds temp1, DataByte1r
	lds temp2, DataByte2r
	lds tempL2, DataByte3r

//ldi temp1,0xFF
eor DataByte1, temp1
eor DataByte2, temp2
eor DataByte3, tempL2

push temp1
push temp2

	mov		temp1,DataByte1
	andi	temp1,0b10000000
	lsr 	temp1
	lsr 	temp1
	mov 	temp2,DataByte1
	andi 	temp2,0b00011111
	or 		temp1,temp2
	mov 	temp2,DataByte2
	andi 	temp2,0b00000011
	clc
	ror 	temp2
	ror 	temp2
	ror 	temp2
	or 		temp1,temp2
	out 	PORTD,temp1

	mov 	temp1,DataByte1
	andi 	temp1,0b01100000
	lsl 	temp1
	mov 	temp2,DataByte2
	andi 	temp2,0b11111100
	lsr 	temp2
	lsr 	temp2
	or	 	temp1,temp2
	out 	PORTB,temp1

	andi 	DataByte3,0b00111111
	out		PORTC, DataByte3

pop temp2
pop temp1

pop tempL2
pop temp2
pop temp1

pop DataByte3
pop DataByte2
pop DataByte1


	sleep
	nop
	rjmp HeaterEffects_n
//*******************
/*

*/
rjmp End_Step_n
St0:
rjmp St1
rjmp St2
rjmp St3
rjmp St4
rjmp St5
rjmp St6
rjmp St7
rjmp St8
rjmp St9
rjmp St10
rjmp St11
rjmp St12
rjmp St13
rjmp St14
rjmp St15
rjmp St16
rjmp St17
rjmp St18
rjmp St19
rjmp St20
rjmp St21
rjmp St22
rjmp St23
ex_St:

	cpi TempL2,22
	brne PC+2
	clr TempL2




	dec Repeat
	brne St0-1
	
	inc Step
	rjmp St0-1

St1:
ldi DataByte1,0b00000000
ldi DataByte2,0b00000000
ldi DataByte3,0b00000000
rjmp ex_St

St2:
ldi DataByte1,0b00000000
ldi DataByte2,0b00001100
ldi DataByte3,0b00000000
rjmp ex_St

St3:
ldi DataByte1,0b00000000
ldi DataByte2,0b00011110
ldi DataByte3,0b00000000
rjmp ex_St

St4:
ldi DataByte1,0b00000000
ldi DataByte2,0b00111111
ldi DataByte3,0b00000000
rjmp ex_St

St5:
ldi DataByte1,0b10000000
ldi DataByte2,0b01111111
ldi DataByte3,0b00000000
rjmp ex_St

St6:
ldi DataByte1,0b11000000
ldi DataByte2,0b11111111
ldi DataByte3,0b00000000
rjmp ex_St

St7:
ldi DataByte1,0b11100000
ldi DataByte2,0b11111111
ldi DataByte3,0b00000001
rjmp ex_St

St8:
ldi DataByte1,0b11110000
ldi DataByte2,0b11111111
ldi DataByte3,0b00000011
rjmp ex_St

St9:
ldi DataByte1,0b11111000
ldi DataByte2,0b11111111
ldi DataByte3,0b00000111
rjmp ex_St

St10:
ldi DataByte1,0b11111100
ldi DataByte2,0b11111111
ldi DataByte3,0b00001111
rjmp ex_St

St11:
ldi DataByte1,0b11111110
ldi DataByte2,0b11111111
ldi DataByte3,0b00011111
rjmp ex_St

St12:
ldi DataByte1,0b11111111
ldi DataByte2,0b11111111
ldi DataByte3,0b00111111
rjmp ex_St

St13:
ldi DataByte1,0b11111111
ldi DataByte2,0b11110011
ldi DataByte3,0b00111111
rjmp ex_St

St14:
ldi DataByte1,0b11111111
ldi DataByte2,0b11100001
ldi DataByte3,0b00111111
rjmp ex_St

St15:
ldi DataByte1,0b11111111
ldi DataByte2,0b11000000
ldi DataByte3,0b00111111
rjmp ex_St

St16:
ldi DataByte1,0b01111111
ldi DataByte2,0b10000000
ldi DataByte3,0b00111111
rjmp ex_St

St17:
ldi DataByte1,0b00111111
ldi DataByte2,0b00000000
ldi DataByte3,0b00111111
rjmp ex_St

St18:
ldi DataByte1,0b00011111
ldi DataByte2,0b00000000
ldi DataByte3,0b00111110
rjmp ex_St

St19:
ldi DataByte1,0b00001111
ldi DataByte2,0b00000000
ldi DataByte3,0b00111100
rjmp ex_St

St20:
ldi DataByte1,0b00000111
ldi DataByte2,0b00000000
ldi DataByte3,0b00111000
rjmp ex_St

St21:
ldi DataByte1,0b00000011
ldi DataByte2,0b00000000
ldi DataByte3,0b00110000
rjmp ex_St

St22:
ldi DataByte1,0b00000001
ldi DataByte2,0b00000000
ldi DataByte3,0b00100000
rjmp ex_St

St23:
ldi DataByte1,0b00000000
ldi DataByte2,0b00000000
ldi DataByte3,0b00000000
rjmp ex_St













/*
HeaterEffects:
Step_init:
;ldi time,1
	dec time	//проверяем время отработки шага,пока время не прошло ничего не меняем
	brne EndStep00

	ldi temp1,0	// смотрим на каком шаге находимся(перебор всех шагов)
	tst Step
	brne Step_00

//инициализация первого шага
	ldi DataByte1,0b00000001
	clr DataByte2
	clr DataByte3

	ldi Step,1

;	ldi Step,13

	ldi Repeat,128	// сколько раз повторить цепочку шагов для достижения эффекта
Step_00:
	ldi temp1,1
	cpse Step,temp1
	rjmp Step_01

	ldi Time,6;100	// сколько времени стоим на этом шаге(прерывания по таймеру)

	clc	// организуем сдвиг вправо
	bst DataByte1,0
	ror DataByte3
	ror DataByte2
	ror DataByte1
	bld DataByte3,5

	dec Repeat
	brne EndStep00	//уходим на вывод результатов


//инициализация следующего шага
;	ldi DataByte1,0b00000001
;	clr DataByte2
;	clr DataByte3

	inc Step	// переход на новый шаг
	ldi Repeat,128;255	// сколько раз повторить цепочку шагов для достижения эффекта
Step_01:
	ldi temp1,2
	cpse Step,temp1
	rjmp Step_02

	ldi Time,6;15;50	// сколько времени стоим на этом шаге(прерывания по таймеру)

	clc	// организуем сдвиг влево
	rol DataByte1
	rol DataByte2
	rol DataByte3
	bst DataByte3,6
	bld DataByte1,0

	dec Repeat
	brne EndStep00


//инициализация следующего шага
	ldi DataByte1,0b00000001
	clr DataByte2
	clr DataByte3

	ldi TempL2,5

	inc Step	// переход на новый шаг
	ldi Repeat,22;128;255	// сколько раз повторить цепочку шагов для достижения эффекта
Step_02:
	ldi temp1,3
	cpse Step,temp1
	rjmp Step_03

	ldi Time,5;10;50	// сколько времени стоим на этом шаге(прерывания по таймеру)

	sec
	rol DataByte1
	rol DataByte2
	rol DataByte3

	dec Repeat
	brne EndStep00


//инициализация следующего шага
	ldi DataByte3,0b00111111
	ser DataByte2
	ser DataByte1

	inc Step	// переход на новый шаг
	ldi Repeat,22;225	// сколько раз повторить цепочку шагов для достижения эффекта
	

EndStep00:	//промежуточная метка
	rjmp EndStep

Step_03:
	ldi temp1,4
	cpse Step,temp1
	rjmp Step_04

	sbrs TempL2,0
	rjmp RightLed
	rjmp LeftLed

RightLed:
	ldi Time,10;100	// сколько времени стоим на этом шаге(прерывания по таймеру)

	clc
	ror DataByte3
	ror DataByte2
	ror DataByte1
	rjmp EndLed

LeftLed:
	ldi Time,7;100	// сколько времени стоим на этом шаге(прерывания по таймеру)

	clc
	rol DataByte1
	rol DataByte2
	rol DataByte3
	rjmp EndLed

EndLed:
	dec Repeat
	brne EndStep00


//инициализация следующего шага
	ldi DataByte1,0b00000001
	clr DataByte2
	clr DataByte3

	ldi Repeat,22
	ldi Step,3
	dec TempL2
	brne EndStep00

	ldi Step,4
//инициализация следующего шага
	ldi DataByte1,0b01010101
	ldi DataByte2,0b01010101
	ldi DataByte3,0b00010101

	inc Step	// переход на новый шаг
	ldi Repeat,128	// сколько раз повторить цепочку шагов для достижения эффекта
Step_04:
	ldi temp1,5
	cpse Step,temp1
	rjmp Step_05

	ldi Time,6;150	// сколько времени стоим на этом шаге(прерывания по таймеру)

	ldi temp1,3;50	// создадим эффект догонялок в одну из сторон
	sbrc Repeat,0
	add Time,temp1

	ldi temp1,0xFF
	eor DataByte1,temp1
	eor DataByte2,temp1
	eor DataByte3,temp1

	dec Repeat
	brne EndStep00


//инициализация следующего шага
;	ldi DataByte1,0b01010101
;	ldi DataByte2,0b01010101
;	ldi DataByte3,0b00010101

	inc Step	// переход на новый шаг
	ldi Repeat,128	// сколько раз повторить цепочку шагов для достижения эффекта
Step_05:
	ldi temp1,6
	cpse Step,temp1
	rjmp Step_06
	ldi Time,7;150	// сколько времени стоим на этом шаге(прерывания по таймеру)

	ldi temp1,3;50	// создадим эффект догонялок в одну из сторон
	sbrc Repeat,0
	sub Time,temp1

	ldi temp1,0xFF
	eor DataByte1,temp1
	eor DataByte2,temp1
	eor DataByte3,temp1

	dec Repeat
	brne EndStep00


//инициализация следующего шага
	ldi DataByte1,0b00011111	//цепочка из 5ти светодиодов
	clr DataByte2
	clr DataByte3

	inc Step	// переход на новый шаг
	ldi Repeat,128	// сколько раз повторить цепочку шагов для достижения эффекта
Step_06:
	ldi temp1,7
	cpse Step,temp1
	rjmp Step_07

	ldi Time,5;150	// сколько времени стоим на этом шаге(прерывания по таймеру)

	clc	// организуем сдвиг влево
	rol DataByte1
	rol DataByte2
	rol DataByte3
	bst DataByte3,6
	bld DataByte1,0

	dec Repeat
	brne EndStep01


//инициализация следующего шага
	ldi DataByte1,0b00001111	//цепочка из 5ти светодиодов
	clr DataByte2
	clr DataByte3

	inc Step	// переход на новый шаг
	ldi Repeat,128	// сколько раз повторить цепочку шагов для достижения эффекта
Step_07:
	ldi temp1,8
	cpse Step,temp1
	rjmp Step_08

	ldi Time,8;150	// сколько времени стоим на этом шаге(прерывания по таймеру)


	clc	// организуем сдвиг вправо
	bst DataByte1,0
	ror DataByte3
	ror DataByte2
	ror DataByte1
	bld DataByte3,5

	dec Repeat
	brne EndStep01


//инициализация следующего шага
	ldi DataByte1,0b00000111	//цепочка из 5ти светодиодов
	clr DataByte2
	clr DataByte3

	inc Step	// переход на новый шаг
	ldi Repeat,128	// сколько раз повторить цепочку шагов для достижения эффекта

EndStep01:	//промежуточная метка
	rjmp EndStep

Step_08:
	ldi temp1,9
	cpse Step,temp1
	rjmp Step_09

	ldi Time,5;150	// сколько времени стоим на этом шаге(прерывания по таймеру)

	clc	// организуем сдвиг влево
	rol DataByte1
	rol DataByte2
	rol DataByte3
	bst DataByte3,6
	bld DataByte1,0

	dec Repeat
	brne EndStep01


//инициализация следующего шага
	ldi DataByte1,0b00000011	//цепочка из 5ти светодиодов
	clr DataByte2
	clr DataByte3

	inc Step	// переход на новый шаг
	ldi Repeat,128	// сколько раз повторить цепочку шагов для достижения эффекта
Step_09:
	ldi temp1,10
	cpse Step,temp1
	rjmp Step_10

	ldi Time,5;150	// сколько времени стоим на этом шаге(прерывания по таймеру)


	clc	// организуем сдвиг вправо
	bst DataByte1,0
	ror DataByte3
	ror DataByte2
	ror DataByte1
	bld DataByte3,5

	dec Repeat
	brne EndStep01

//инициализация следующего шага
	ldi DataByte1,0b00000001	//цепочка из 5ти светодиодов
	clr DataByte2
	clr DataByte3

	inc Step	// переход на новый шаг
	ldi Repeat,128	// сколько раз повторить цепочку шагов для достижения эффекта
Step_10:
	ldi temp1,11
	cpse Step,temp1
	rjmp Step_11

	ldi Time,7;150	// сколько времени стоим на этом шаге(прерывания по таймеру)

	clc	// организуем сдвиг влево
	rol DataByte1
	rol DataByte2
	rol DataByte3
	bst DataByte3,6
	bld DataByte1,0

	dec Repeat
	brne EndStep01


//инициализация следующего шага
	ldi DataByte1,0b01100110	//цепочка из 5ти светодиодов
	clr DataByte2
	clr DataByte3

	inc Step	// переход на новый шаг
	ldi Repeat,128	// сколько раз повторить цепочку шагов для достижения эффекта
Step_11:
	ldi temp1,12
	cpse Step,temp1
	rjmp Step_12

	ldi Time,5;150	// сколько времени стоим на этом шаге(прерывания по таймеру)


	clc	// организуем сдвиг вправо
	bst DataByte1,0
	ror DataByte3
	ror DataByte2
	ror DataByte1
	bld DataByte3,5

	dec Repeat
	brne EndStep01


//инициализация следующего шага
	clr TempL2
	clr TempH2

	inc Step	// переход на новый шаг
	ldi Repeat,255	// сколько раз повторить цепочку шагов для достижения эффекта
Step_12:
	ldi temp1,13
	cpse Step,temp1
	rjmp Step_00

	ldi Time,4;150	// сколько времени стоим на этом шаге(прерывания по таймеру)


	//рисуем сердечко
	ldi zl,low(St0)
	ldi zh,high(St0)
	inc TempL2
	clr TempH2
	add zl,TempL2
	adc zh,TempH2
	ijmp
St0:
rjmp St1
rjmp St2
rjmp St3
rjmp St4
rjmp St5
rjmp St6
rjmp St7
rjmp St8
rjmp St9
rjmp St10
rjmp St11
rjmp St12
rjmp St13
rjmp St14
rjmp St15
rjmp St16
rjmp St17
rjmp St18
rjmp St19
rjmp St20
rjmp St21
rjmp St22
rjmp St23


St1:
ldi DataByte1,0b00000000
ldi DataByte2,0b00000000
ldi DataByte3,0b00000000
rjmp ex_St

St2:
ldi DataByte1,0b00000000
ldi DataByte2,0b00001100
ldi DataByte3,0b00000000
rjmp ex_St

St3:
ldi DataByte1,0b00000000
ldi DataByte2,0b00011110
ldi DataByte3,0b00000000
rjmp ex_St

St4:
ldi DataByte1,0b00000000
ldi DataByte2,0b00111111
ldi DataByte3,0b00000000
rjmp ex_St

St5:
ldi DataByte1,0b10000000
ldi DataByte2,0b01111111
ldi DataByte3,0b00000000
rjmp ex_St

St6:
ldi DataByte1,0b11000000
ldi DataByte2,0b11111111
ldi DataByte3,0b00000000
rjmp ex_St

St7:
ldi DataByte1,0b11100000
ldi DataByte2,0b11111111
ldi DataByte3,0b00000001
rjmp ex_St

St8:
ldi DataByte1,0b11110000
ldi DataByte2,0b11111111
ldi DataByte3,0b00000011
rjmp ex_St

St9:
ldi DataByte1,0b11111000
ldi DataByte2,0b11111111
ldi DataByte3,0b00000111
rjmp ex_St

St10:
ldi DataByte1,0b11111100
ldi DataByte2,0b11111111
ldi DataByte3,0b00001111
rjmp ex_St

St11:
ldi DataByte1,0b11111110
ldi DataByte2,0b11111111
ldi DataByte3,0b00011111
rjmp ex_St

St12:
ldi DataByte1,0b11111111
ldi DataByte2,0b11111111
ldi DataByte3,0b00111111
rjmp ex_St

St13:
ldi DataByte1,0b11111111
ldi DataByte2,0b11110011
ldi DataByte3,0b00111111
rjmp ex_St

St14:
ldi DataByte1,0b11111111
ldi DataByte2,0b11100001
ldi DataByte3,0b00111111
rjmp ex_St

St15:
ldi DataByte1,0b11111111
ldi DataByte2,0b11000000
ldi DataByte3,0b00111111
rjmp ex_St

St16:
ldi DataByte1,0b01111111
ldi DataByte2,0b10000000
ldi DataByte3,0b00111111
rjmp ex_St

St17:
ldi DataByte1,0b00111111
ldi DataByte2,0b00000000
ldi DataByte3,0b00111111
rjmp ex_St

St18:
ldi DataByte1,0b00011111
ldi DataByte2,0b00000000
ldi DataByte3,0b00111110
rjmp ex_St

St19:
ldi DataByte1,0b00001111
ldi DataByte2,0b00000000
ldi DataByte3,0b00111100
rjmp ex_St

St20:
ldi DataByte1,0b00000111
ldi DataByte2,0b00000000
ldi DataByte3,0b00111000
rjmp ex_St

St21:
ldi DataByte1,0b00000011
ldi DataByte2,0b00000000
ldi DataByte3,0b00110000
rjmp ex_St

St22:
ldi DataByte1,0b00000001
ldi DataByte2,0b00000000
ldi DataByte3,0b00100000
rjmp ex_St

St23:
ldi DataByte1,0b00000000
ldi DataByte2,0b00000000
ldi DataByte3,0b00000000
rjmp ex_St

ex_St:

	cpi TempL2,24
	brne PC+2
	clr TempL2




	dec Repeat
	brne EndStep

	clr Step
	rjmp EndStep


Step_13:
Step_14:
Step_15:
Step_17:
Step_18:
Step_19:
Step_20:
Step_21:
Step_22:
Step_23:
Step_24:
Step_25:


//*******************
// обработчик на вывод 
//DataByte1 PD5 PB7 PB6 PD4 PD3 PD2 PD1 PD0
//DataByte2 PB5 PB4 PB3 PB2 PB1 PB0 PD7 PD6
//DataByte3 --  --  PC5 PC4 PC3 PC2 PC1 PC0
EndStep:

push DataByte1
push DataByte2
push DataByte3

ldi temp1,0xFF
eor DataByte1, temp1
eor DataByte2, temp1
eor DataByte3, temp1

push temp1
push temp2

	mov		temp1,DataByte1
	andi	temp1,0b10000000
	lsr 	temp1
	lsr 	temp1
	mov 	temp2,DataByte1
	andi 	temp2,0b00011111
	or 		temp1,temp2
	mov 	temp2,DataByte2
	andi 	temp2,0b00000011
	clc
	ror 	temp2
	ror 	temp2
	ror 	temp2
	or 		temp1,temp2
	out 	PORTD,temp1

	mov 	temp1,DataByte1
	andi 	temp1,0b01100000
	lsl 	temp1
	mov 	temp2,DataByte2
	andi 	temp2,0b11111100
	lsr 	temp2
	lsr 	temp2
	or	 	temp1,temp2
	out 	PORTB,temp1

	andi 	DataByte3,0b00111111
	out		PORTC, DataByte3

pop temp2
pop temp1

pop DataByte3
pop DataByte2
pop DataByte1


	sleep
	nop
	rjmp Step_Init 
//*******************
/*

*/
//*/



//Обработка прерывания для формирования импульса по таймеру 0
TIM0_OVF:

; переинициализация таймера
	nop
	ldi r16,-124
	out TCNT0,r16

	reti


;Подпрограмма инициализации Таймера0
TIM0_Init:
; настроим предделитель таймера 0 /256
	clr r16
	out TCCR0A,r16
	ldi r16,(0<<CS00)|(0<<CS01)|(1<<CS02)
	out TCCR0B,r16
; запишем начальное значение в таймер0 
; будем вызывать прерывание через 100 тиков по 256 тика
; работаем на внутреннем генераторе в 1 МГц
	ldi r16,-125
	out TCNT0,r16
; разрешим прерывание от Таймера 0 по переполнению
	ldi r16,(1<<TOIE0)
	sts TIMSK0,r16

	ret
