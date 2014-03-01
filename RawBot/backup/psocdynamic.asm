;  Generated by PSoC Designer 5.4.2946
;
;
;  rawbotDynamic.asm
;
;  Data: 11 June, 2004
;  Copyright (c) Cypress Semiconductor 2013. All Rights Reserved.
;
;  This file is generated by the Device Editor on Application Generation.
;  It contains functions that can be used to test the state of the 
;  currently active configuration.
;  
;  DO NOT EDIT THIS FILE MANUALLY, AS IT IS OVERWRITTEN!!!
;  Edits to this file will not be preserved.
;
include "m8c.inc"
include "memory.inc"
include "PSoCDynamic.inc"
export IsrawbotLoaded
export _IsrawbotLoaded
export IsConfig1Loaded
export _IsConfig1Loaded
IsrawbotLoaded:
_IsrawbotLoaded:
	RAM_SETPAGE_CUR >ACTIVE_CONFIG_STATUS
	mov		a, 0
	tst		[ACTIVE_CONFIG_STATUS+rawbot_ADDR_OFF], rawbot_BIT
	jz		rawbotIsNotLoaded
	mov		a, 1
rawbotIsNotLoaded:
	ret

IsConfig1Loaded:
_IsConfig1Loaded:
	RAM_SETPAGE_CUR >ACTIVE_CONFIG_STATUS
	mov		a, 0
	tst		[ACTIVE_CONFIG_STATUS+Config1_ADDR_OFF], Config1_BIT
	jz		Config1IsNotLoaded
	mov		a, 1
Config1IsNotLoaded:
	ret

