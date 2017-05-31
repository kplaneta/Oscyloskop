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
/* Include core modules */
#include "stm32f4xx.h"
/* Include my libraries here */
#include "defines.h"
#include "tm_stm32f4_ili9341.h"
#include "tm_stm32f4_stmpe811.h"
#include "tm_stm32f4_adc.h"
#include <stdio.h>

void PrintSquareWave(uint16_t posy);
void ClearScreen(void);
void PrintADCResult(uint16_t result,uint16_t posy);

int main(void) {
	char str[30];
	/* Create TouchData struct */
	TM_STMPE811_TouchData touchData;

	
	/* Initialize system */
	SystemInit();
	
	/* Initialize LCD */
	TM_ILI9341_Init();
	
	/* Initialize touchscreen */
	if (TM_STMPE811_Init() != TM_STMPE811_State_Ok) {
		TM_ILI9341_Puts(20, 20, "STMPE811 Error", &TM_Font_11x18, ILI9341_COLOR_ORANGE, ILI9341_COLOR_BLACK);
	}
	
	/* Initialize ADC */
	TM_ADC_Init(ADC1, ADC_Channel_0);
	
	/* Rotate LCD */
	TM_ILI9341_Rotate(TM_ILI9341_Orientation_Landscape_2);
	
	touchData.orientation = TM_STMPE811_Orientation_Landscape_2;
	
	ClearScreen();
	PrintSquareWave(0);


	/* Print triangular wave*/
	/*	for(int i = 0; i < 7; i++)
	{
		TM_ILI9341_DrawLine(20 + i*40, 160, 40 + i*40, 180, ILI9341_COLOR_GREEN);
		TM_ILI9341_DrawLine(40 + i*40, 180, 60 + i*40, 160, ILI9341_COLOR_GREEN);
		TM_ILI9341_DrawLine(60 + i*40, 160, 60 + i*40, 180, ILI9341_COLOR_GREEN);
		TM_ILI9341_DrawLine(40 + i*40, 160, 40 + i*40, 180, ILI9341_COLOR_GREEN);
	}*/

		
		while (1) {
						
			uint16_t res;
			res = TM_ADC_Read(ADC1, ADC_Channel_0);
			sprintf(str, "%dl",res);
			TM_ILI9341_Puts(100, 80, "Odczyt ADC:", &TM_Font_11x18, ILI9341_COLOR_ORANGE, ILI9341_COLOR_BLACK);
			TM_ILI9341_Puts(140, 100, "      ", &TM_Font_11x18, ILI9341_COLOR_ORANGE, ILI9341_COLOR_BLACK);
			TM_ILI9341_Puts(140, 100, str, &TM_Font_11x18, ILI9341_COLOR_ORANGE, ILI9341_COLOR_BLACK);
			
			if(TM_STMPE811_ReadTouch(&touchData) == TM_STMPE811_State_Pressed)
			{
	
				if(TM_STMPE811_TouchInRectangle(&touchData, 20, 20, 280, 185))
				{
					ClearScreen();
					PrintSquareWave(touchData.y - 60);						
				}
			}
			else
			{


			}
						PrintADCResult(res,140);

	}
}

void ClearScreen(void)
{
		/* Fill with black color */
	TM_ILI9341_Fill(ILI9341_COLOR_BLACK);
	
	/* Draw a frame */
	TM_ILI9341_DrawRectangle(20, 20, 300, 225, ILI9341_COLOR_YELLOW);
	
	/* Write mode and scale */
	TM_ILI9341_Puts(100, 5, "Prototyp oscyloskopu", &TM_Font_7x10, ILI9341_COLOR_ORANGE, ILI9341_COLOR_BLACK);
	//TM_ILI9341_Puts(50, 230, "CH1: 500 mV", &TM_Font_7x10, ILI9341_COLOR_BLUE, ILI9341_COLOR_BLACK);
	
	/* Print grid */
	
	for(int i=0; i<14; i++)
	{
		for(int j=0; j<19; j++)
		{
			TM_ILI9341_DrawLine(20+j*15, 20+ i*15, 20+j*15, 20+i*15, ILI9341_COLOR_GRAY);
		}
	}
}

void PrintSquareWave(uint16_t posy)
{
		/* Print square wave */	
	for(int i = 0; i < 7; i++)
	{
		TM_ILI9341_DrawLine(20 + i*40, 60+posy, 40 + i*40, 60+posy, ILI9341_COLOR_BLUE);
		TM_ILI9341_DrawLine(40 + i*40, 80+posy, 60 + i*40, 80+posy, ILI9341_COLOR_BLUE);
		TM_ILI9341_DrawLine(60 + i*40, 60+posy, 60 + i*40, 80+posy, ILI9341_COLOR_BLUE);
		TM_ILI9341_DrawLine(40 + i*40, 60+posy, 40 + i*40, 80+posy, ILI9341_COLOR_BLUE);
	}
}

void PrintADCResult(uint16_t result, uint16_t posy)
{
		uint16_t ADCresult[420];
		static int i=20;								//Begin of the frame

				if( i<300)
				{
					TM_ILI9341_DrawPixel(i, ADCresult[i-20], ILI9341_COLOR_BLACK);
					ADCresult[i-20] =((posy - result/10));
					TM_ILI9341_DrawPixel(i, ADCresult[i-20], ILI9341_COLOR_GREEN);
					i++;
				}
			else
				{
					i = 20;
				}
}
