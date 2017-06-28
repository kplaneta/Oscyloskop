#ifndef _LCD_H
#define _LCD_H

#include "PROGBAR.h"
#include "BUTTON.h"
#include "GRAPH.h"
#include "DIALOG.h"
#include "math.h"
#include "tm_stm32f4_emwin.h"
#include "GUI.h"
#include "tm_stm32f4_adc.h"
#include "tm_stm32f4_disco.h"
#include "tm_stm32f4_stmpe811.h"
#include <stdbool.h>


void CreateGraph(void);
void ShowResult(void);
void CreateButtons(void);
void TouchInit(void);
bool TouchDetected(void);

#endif
