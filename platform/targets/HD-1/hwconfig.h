/***************************************************************************
 *   Copyright (C) 2022 by Federico Amedeo Izzo IU2NUO,                    *
 *                         Niccolò Izzo IU2KIN                             *
 *                         Frederik Saraci IU2NRO                          *
 *                         Silvano Seva IU2KWO                             *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 3 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, see <http://www.gnu.org/licenses/>   *
 ***************************************************************************/

#ifndef HWCONFIG_H
#define HWCONFIG_H

#include "MK22F51212.h"

/* Screen dimensions */
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

/* Screen pixel format */
#define PIX_FMT_BW

/* Battery type */
#define BAT_LIPO_2S

/* Serial port, UART0 */
#define UART_RX  GPIOA,1
#define UART_TX  GPIOA,2

/* Display */
#define LCD_D0      GPIOD,0
#define LCD_D1      GPIOD,1
#define LCD_D2      GPIOD,2
#define LCD_D3      GPIOD,3
#define LCD_D4      GPIOD,4
#define LCD_D5      GPIOD,5
#define LCD_D6      GPIOD,6
#define LCD_D7      GPIOD,7
#define LCD_RD      GPIOC,14
#define LCD_RS      GPIOC,13
#define LCD_RST     GPIOC,12
#define LCD_WR      GPIOC,11
#define LCD_CS      GPIOC,10
#define LCD_BKLIGHT GPIOB,1

/* Signalling LEDs */
#define GREEN_LED  GPIOB,18
#define RED_LED    GPIOB,19

/* Keyboard */
#define KB_ROW0 LCD_D4
#define KB_ROW1 LCD_D5
#define KB_ROW2 LCD_D6
#define KB_ROW3 LCD_D7

#define KB_COL0 LCD_D0
#define KB_COL1 LCD_D1
#define KB_COL2 LCD_D2
#define KB_COL3 LCD_D3

#define PTT_SW   GPIOE,2

#endif
