;************************************
;** Файл работы с энергонезависимой памятью
;**
;**
;************************************

;************************************
; запись данных в EEPROM
EEPROM_write:
	; Wait for completion of previous write
	sbic EECR,EEPE
	rjmp EEPROM_write 
	; Set up address (r18:r17) in address register
	out EEARH, r18
	out EEARL, r17
	; Write data (r16) to Data Register
	out EEDR,r16
	; Write logical one to EEMPE
	sbi EECR,EEMPE
	; Start eeprom write by setting EEPE
	sbi EECR,EEPE
ret
;************************************

;************************************
;чтение данных из EEPROM
EEPROM_read:
	; Wait for completion of previous write
	sbic EECR,EEPE
	rjmp EEPROM_read
	; Set up address (r18:r17) in address register
	out EEARH, r18
	out EEARL, r17
	; Start eeprom read by writing EERE
	sbi EECR,EERE
	; Read data from Data Register
	in r16,EEDR
ret
;************************************
