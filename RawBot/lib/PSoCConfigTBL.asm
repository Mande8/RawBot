;  Generated by PSoC Designer 5.4.2946
;
; =============================================================================
; FILENAME: PSoCConfigTBL.asm
;  
; Copyright (c) Cypress Semiconductor 2013. All Rights Reserved.
;  
; NOTES:
; Do not modify this file. It is generated by PSoC Designer each time the
; generate application function is run. The values of the parameters in this
; file can be modified by changing the values of the global parameters in the
; device editor.
;  
; =============================================================================
 
include "m8c.inc"
;  Personalization tables 
export LoadConfigTBL_rawbot_Bank1
export LoadConfigTBL_rawbot_Bank0
export LoadConfigTBL_rawbot_Ordered
AREA lit(rom, rel)
LoadConfigTBL_rawbot_Bank0:
;  Instance name LCD, User Module LCD
;  Instance name ServoPWM, User Module PWM16
;       Instance name ServoPWM, Block Name PWM16_LSB(DBB10)
	db		33h, 00h		;ServoPWM_CONTROL_LSB_REG(DBB10CR0)
	db		31h, 9fh		;ServoPWM_PERIOD_LSB_REG(DBB10DR1)
	db		32h, 2ch		;ServoPWM_COMPARE_LSB_REG(DBB10DR2)
;       Instance name ServoPWM, Block Name PWM16_MSB(DBB11)
	db		37h, 00h		;ServoPWM_CONTROL_MSB_REG(DBB11CR0)
	db		35h, 0fh		;ServoPWM_PERIOD_MSB_REG(DBB11DR1)
	db		36h, 01h		;ServoPWM_COMPARE_MSB_REG(DBB11DR2)
;  Instance name Timer16UsEcho, User Module Timer16
;       Instance name Timer16UsEcho, Block Name TIMER16_LSB(DCB02)
	db		2bh, 00h		;Timer16UsEcho_CONTROL_LSB_REG(DCB02CR0)
	db		29h, 40h		;Timer16UsEcho_PERIOD_LSB_REG(DCB02DR1)
	db		2ah, 00h		;Timer16UsEcho_COMPARE_LSB_REG(DCB02DR2)
;       Instance name Timer16UsEcho, Block Name TIMER16_MSB(DCB03)
	db		2fh, 04h		;Timer16UsEcho_CONTROL_MSB_REG(DCB03CR0)
	db		2dh, b5h		;Timer16UsEcho_PERIOD_MSB_REG(DCB03DR1)
	db		2eh, 00h		;Timer16UsEcho_COMPARE_MSB_REG(DCB03DR2)
;  Instance name Timer8Main, User Module Timer8
;       Instance name Timer8Main, Block Name TIMER8(DBB00)
	db		23h, 04h		;Timer8Main_CONTROL_REG(DBB00CR0)
	db		21h, c7h		;Timer8Main_PERIOD_REG(DBB00DR1)
	db		22h, 00h		;Timer8Main_COMPARE_REG(DBB00DR2)
;  Instance name Timer8UsTrig, User Module Timer8
;       Instance name Timer8UsTrig, Block Name TIMER8(DBB01)
	db		27h, 04h		;Timer8UsTrig_CONTROL_REG(DBB01CR0)
	db		25h, 0ah		;Timer8UsTrig_PERIOD_REG(DBB01DR1)
	db		26h, 00h		;Timer8UsTrig_COMPARE_REG(DBB01DR2)
;  Global Register values Bank 0
	db		60h, 28h		; AnalogColumnInputSelect register (AMX_IN)
	db		66h, 00h		; AnalogComparatorControl1 register (CMP_CR1)
	db		63h, 05h		; AnalogReferenceControl register (ARF_CR)
	db		65h, 00h		; AnalogSyncControl register (ASY_CR)
	db		e6h, 00h		; DecimatorControl_0 register (DEC_CR0)
	db		e7h, 00h		; DecimatorControl_1 register (DEC_CR1)
	db		d6h, 00h		; I2CConfig register (I2CCFG)
	db		b0h, 00h		; Row_0_InputMux register (RDI0RI)
	db		b1h, 00h		; Row_0_InputSync register (RDI0SYN)
	db		b2h, 00h		; Row_0_LogicInputAMux register (RDI0IS)
	db		b3h, 33h		; Row_0_LogicSelect_0 register (RDI0LT0)
	db		b4h, 33h		; Row_0_LogicSelect_1 register (RDI0LT1)
	db		b5h, 00h		; Row_0_OutputDrive_0 register (RDI0SRO0)
	db		b6h, 00h		; Row_0_OutputDrive_1 register (RDI0SRO1)
	db		b8h, 55h		; Row_1_InputMux register (RDI1RI)
	db		b9h, 00h		; Row_1_InputSync register (RDI1SYN)
	db		bah, 10h		; Row_1_LogicInputAMux register (RDI1IS)
	db		bbh, 33h		; Row_1_LogicSelect_0 register (RDI1LT0)
	db		bch, 33h		; Row_1_LogicSelect_1 register (RDI1LT1)
	db		bdh, 00h		; Row_1_OutputDrive_0 register (RDI1SRO0)
	db		beh, 20h		; Row_1_OutputDrive_1 register (RDI1SRO1)
	db		ffh
LoadConfigTBL_rawbot_Bank1:
;  Instance name LCD, User Module LCD
;  Instance name ServoPWM, User Module PWM16
;       Instance name ServoPWM, Block Name PWM16_LSB(DBB10)
	db		30h, 01h		;ServoPWM_FUNC_LSB_REG(DBB10FN)
	db		31h, 16h		;ServoPWM_INPUT_LSB_REG(DBB10IN)
	db		32h, 40h		;ServoPWM_OUTPUT_LSB_REG(DBB10OU)
;       Instance name ServoPWM, Block Name PWM16_MSB(DBB11)
	db		34h, 21h		;ServoPWM_FUNC_MSB_REG(DBB11FN)
	db		35h, 36h		;ServoPWM_INPUT_MSB_REG(DBB11IN)
	db		36h, 47h		;ServoPWM_OUTPUT_MSB_REG(DBB11OU)
;  Instance name Timer16UsEcho, User Module Timer16
;       Instance name Timer16UsEcho, Block Name TIMER16_LSB(DCB02)
	db		28h, 00h		;Timer16UsEcho_FUNC_LSB_REG(DCB02FN)
	db		29h, 05h		;Timer16UsEcho_INPUT_LSB_REG(DCB02IN)
	db		2ah, 40h		;Timer16UsEcho_OUTPUT_LSB_REG(DCB02OU)
;       Instance name Timer16UsEcho, Block Name TIMER16_MSB(DCB03)
	db		2ch, 20h		;Timer16UsEcho_FUNC_MSB_REG(DCB03FN)
	db		2dh, 35h		;Timer16UsEcho_INPUT_MSB_REG(DCB03IN)
	db		2eh, 40h		;Timer16UsEcho_OUTPUT_MSB_REG(DCB03OU)
;  Instance name Timer8Main, User Module Timer8
;       Instance name Timer8Main, Block Name TIMER8(DBB00)
	db		20h, 20h		;Timer8Main_FUNC_REG(DBB00FN)
	db		21h, 06h		;Timer8Main_INPUT_REG(DBB00IN)
	db		22h, 40h		;Timer8Main_OUTPUT_REG(DBB00OU)
;  Instance name Timer8UsTrig, User Module Timer8
;       Instance name Timer8UsTrig, Block Name TIMER8(DBB01)
	db		24h, 20h		;Timer8UsTrig_FUNC_REG(DBB01FN)
	db		25h, 05h		;Timer8UsTrig_INPUT_REG(DBB01IN)
	db		26h, 40h		;Timer8UsTrig_OUTPUT_REG(DBB01OU)
;  Global Register values Bank 1
	db		61h, 00h		; AnalogClockSelect1 register (CLK_CR1)
	db		69h, 00h		; AnalogClockSelect2 register (CLK_CR2)
	db		60h, 00h		; AnalogColumnClockSelect register (CLK_CR0)
	db		62h, 00h		; AnalogIOControl_0 register (ABF_CR0)
	db		67h, 33h		; AnalogLUTControl0 register (ALT_CR0)
	db		68h, 33h		; AnalogLUTControl1 register (ALT_CR1)
	db		63h, 00h		; AnalogModulatorControl_0 register (AMD_CR0)
	db		66h, 00h		; AnalogModulatorControl_1 register (AMD_CR1)
	db		d1h, 00h		; GlobalDigitalInterconnect_Drive_Even_Input register (GDI_E_IN)
	db		d3h, 00h		; GlobalDigitalInterconnect_Drive_Even_Output register (GDI_E_OU)
	db		d0h, 00h		; GlobalDigitalInterconnect_Drive_Odd_Input register (GDI_O_IN)
	db		d2h, 00h		; GlobalDigitalInterconnect_Drive_Odd_Output register (GDI_O_OU)
	db		e1h, b9h		; OscillatorControl_1 register (OSC_CR1)
	db		e2h, 00h		; OscillatorControl_2 register (OSC_CR2)
	db		dfh, c7h		; OscillatorControl_3 register (OSC_CR3)
	db		deh, 02h		; OscillatorControl_4 register (OSC_CR4)
	db		ddh, 00h		; OscillatorGlobalBusEnableControl register (OSC_GO_EN)
	db		ffh
AREA psoc_config(rom, rel)
LoadConfigTBL_rawbot_Ordered:
;  Ordered Global Register values
	M8C_SetBank0
	mov	reg[00h], 00h		; Port_0_Data register (PRT0DR)
	M8C_SetBank1
	mov	reg[00h], ffh		; Port_0_DriveMode_0 register (PRT0DM0)
	mov	reg[01h], 00h		; Port_0_DriveMode_1 register (PRT0DM1)
	M8C_SetBank0
	mov	reg[03h], 00h		; Port_0_DriveMode_2 register (PRT0DM2)
	mov	reg[02h], 80h		; Port_0_GlobalSelect register (PRT0GS)
	M8C_SetBank1
	mov	reg[02h], 00h		; Port_0_IntCtrl_0 register (PRT0IC0)
	mov	reg[03h], 00h		; Port_0_IntCtrl_1 register (PRT0IC1)
	M8C_SetBank0
	mov	reg[01h], 00h		; Port_0_IntEn register (PRT0IE)
	mov	reg[04h], 00h		; Port_1_Data register (PRT1DR)
	M8C_SetBank1
	mov	reg[04h], 00h		; Port_1_DriveMode_0 register (PRT1DM0)
	mov	reg[05h], 00h		; Port_1_DriveMode_1 register (PRT1DM1)
	M8C_SetBank0
	mov	reg[07h], 00h		; Port_1_DriveMode_2 register (PRT1DM2)
	mov	reg[06h], 00h		; Port_1_GlobalSelect register (PRT1GS)
	M8C_SetBank1
	mov	reg[06h], 80h		; Port_1_IntCtrl_0 register (PRT1IC0)
	mov	reg[07h], 80h		; Port_1_IntCtrl_1 register (PRT1IC1)
	M8C_SetBank0
	mov	reg[05h], 80h		; Port_1_IntEn register (PRT1IE)
	mov	reg[08h], 00h		; Port_2_Data register (PRT2DR)
	M8C_SetBank1
	mov	reg[08h], 7fh		; Port_2_DriveMode_0 register (PRT2DM0)
	mov	reg[09h], 80h		; Port_2_DriveMode_1 register (PRT2DM1)
	M8C_SetBank0
	mov	reg[0bh], 80h		; Port_2_DriveMode_2 register (PRT2DM2)
	mov	reg[0ah], 00h		; Port_2_GlobalSelect register (PRT2GS)
	M8C_SetBank1
	mov	reg[0ah], 00h		; Port_2_IntCtrl_0 register (PRT2IC0)
	mov	reg[0bh], 00h		; Port_2_IntCtrl_1 register (PRT2IC1)
	M8C_SetBank0
	mov	reg[09h], 00h		; Port_2_IntEn register (PRT2IE)
	mov	reg[0ch], 00h		; Port_3_Data register (PRT3DR)
	M8C_SetBank1
	mov	reg[0ch], 00h		; Port_3_DriveMode_0 register (PRT3DM0)
	mov	reg[0dh], 00h		; Port_3_DriveMode_1 register (PRT3DM1)
	M8C_SetBank0
	mov	reg[0fh], 00h		; Port_3_DriveMode_2 register (PRT3DM2)
	mov	reg[0eh], 00h		; Port_3_GlobalSelect register (PRT3GS)
	M8C_SetBank1
	mov	reg[0eh], 00h		; Port_3_IntCtrl_0 register (PRT3IC0)
	mov	reg[0fh], 00h		; Port_3_IntCtrl_1 register (PRT3IC1)
	M8C_SetBank0
	mov	reg[0dh], 00h		; Port_3_IntEn register (PRT3IE)
	mov	reg[10h], 00h		; Port_4_Data register (PRT4DR)
	M8C_SetBank1
	mov	reg[10h], 00h		; Port_4_DriveMode_0 register (PRT4DM0)
	mov	reg[11h], 00h		; Port_4_DriveMode_1 register (PRT4DM1)
	M8C_SetBank0
	mov	reg[13h], 00h		; Port_4_DriveMode_2 register (PRT4DM2)
	mov	reg[12h], 00h		; Port_4_GlobalSelect register (PRT4GS)
	M8C_SetBank1
	mov	reg[12h], 00h		; Port_4_IntCtrl_0 register (PRT4IC0)
	mov	reg[13h], 00h		; Port_4_IntCtrl_1 register (PRT4IC1)
	M8C_SetBank0
	mov	reg[11h], 00h		; Port_4_IntEn register (PRT4IE)
	mov	reg[14h], 00h		; Port_5_Data register (PRT5DR)
	M8C_SetBank1
	mov	reg[14h], 00h		; Port_5_DriveMode_0 register (PRT5DM0)
	mov	reg[15h], 00h		; Port_5_DriveMode_1 register (PRT5DM1)
	M8C_SetBank0
	mov	reg[17h], 00h		; Port_5_DriveMode_2 register (PRT5DM2)
	mov	reg[16h], 00h		; Port_5_GlobalSelect register (PRT5GS)
	M8C_SetBank1
	mov	reg[16h], 00h		; Port_5_IntCtrl_0 register (PRT5IC0)
	mov	reg[17h], 00h		; Port_5_IntCtrl_1 register (PRT5IC1)
	M8C_SetBank0
	mov	reg[15h], 00h		; Port_5_IntEn register (PRT5IE)
	M8C_SetBank0
	ret


; PSoC Configuration file trailer PsocConfig.asm
