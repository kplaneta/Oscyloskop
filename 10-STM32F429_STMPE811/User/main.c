/**
 *	Keil project for STMPE811 touch driver controller
 *	
 *	Works on STM32F429 Discovery board by default
 *
 *	Before you start, select your target, on the right of the "Load" button
 *
 *	@author		Tilen Majerle
 *	@email		tilen@majerle.eu
 *	@website	http://stm32f4-discovery.com
 *	@ide		Keil uVision 5
 *	@packs		STM32F4xx Keil packs version 2.2.0 or greater required
 *	@stdperiph	STM32F4xx Standard peripheral drivers version 1.4.0 or greater required
 */

//#include "tm_stm32f4_ili9341.h"
//#include "tm_stm32f4_stmpe811.h"

/* Include core modules */
#include "stm32f4xx.h"
/* Include my libraries here */
#include "defines.h"
#include "tm_stm32f4_delay.h"
#include "tm_stm32f4_lcd.h"
#include "tm_stm32f4_i2c.h"
#include "tm_stm32f4_usart.h"
#include "stdio.h"
#include "tm_stm32f4_dma2d_graphic.h"

#include "lcd.h"



#define ILI9341_PIXEL				76800
/* Starting buffer address in RAM */
/* Offset for Layer 1 = SDRAM START ADDRESS + FRAME_BUFFER */
#define ILI9341_FRAME_BUFFER		SDRAM_START_ADR
/* Offset for Layer 2 */
#define ILI9341_FRAME_OFFSET		(uint32_t)ILI9341_PIXEL * 2


int main(void) {

	/* Create TouchData struct */

	
	/* Initialize system */
	SystemInit();
	
	/* Initialize LCD */
	
	/* Initialize touchscreen */
		/* Initialize delay */
	TM_DELAY_Init();
	/* Initialize ADC */
	TM_ADC_Init(ADC1, ADC_Channel_0);
		/* Init EMWIN */
	TM_EMWIN_Init();
			/* Rotate LCD */
	TM_EMWIN_Rotate(TM_EMWIN_Rotate_270);
		/* Init DMA2D graphic acceleration */
	TM_DMA2DGRAPHIC_Init();
		/* 
	   Enable memory for EMWIN 
	   This features allows you to update screen very fast without flickering, because EMWIN draws on LCD layer 1 (LTDC) 
	   but layer 2 (LTDC) is shown on LCD. After all drawings from EMWIN are done, layer 1 is copied to layer 2 
	   and everything is shown to user at same time, without flickering.
	   You have to use @ref TM_EMWIN_Exec() to execute all EMWIN pending tasks in future or memory does not have effect here
	*/
	TM_EMWIN_MemoryEnable();
	
	CreateGraph();
	TouchInit();
	
	while(1){
				if (TM_EMWIN_Exec()) {
			/* Toggle RED led if non-zero value is returned from GUI_Exec() */
			TM_DISCO_LedToggle(LED_RED);
		}
		
		ShowResult();
		//TouchDetected();
	}
}
