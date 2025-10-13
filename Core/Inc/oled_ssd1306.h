/*
 * oled_ssd1306.h
 *
 *  Created on: Sep 13, 2025
 *      Author: khanh
 */

#ifndef INC_OLED_SSD1306_H_
#define INC_OLED_SSD1306_H_

#include "stm32f1xx_hal.h"
#include "font5x7.h"

#define SSD1306_I2C_ADDR   0x78
extern I2C_HandleTypeDef hi2c1;


void ssd1306_init(void);
void ssd1306_clear(void);
void ssd1306_updateScreen(void);
void ssd1306_drawPixel(uint8_t x, uint8_t y, uint8_t color);
void ssd1306_writeString(char *str, uint8_t x, uint8_t y, FontDef font);

#endif /* INC_OLED_SSD1306_H_ */
