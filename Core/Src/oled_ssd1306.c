/*
 * oled_ssd1306.c
 *
 *  Created on: Sep 13, 2025
 *      Author: khanh
 */
#include "oled_ssd1306.h"
#include "font5x7.h"
#include "string.h"

static uint8_t ssd1306_buffer[128 * 64 / 8];

void ssd1306_sendCmd(uint8_t cmd){
	uint8_t d[2] = {0x00,cmd};
	HAL_I2C_Master_Transmit(&hi2c1, SSD1306_I2C_ADDR, d, 2, 10);
}

void ssd1306_init(void){
    HAL_Delay(100);
    ssd1306_sendCmd(0xAE); // display off
    ssd1306_sendCmd(0x20); ssd1306_sendCmd(0x02); // horizontal addressing
    ssd1306_sendCmd(0xB0);
    ssd1306_sendCmd(0xC8);
    ssd1306_sendCmd(0x00);
    ssd1306_sendCmd(0x10);
    ssd1306_sendCmd(0x40);
    ssd1306_sendCmd(0x81); ssd1306_sendCmd(0x7F);
    ssd1306_sendCmd(0xA1);
    ssd1306_sendCmd(0xA6);
    ssd1306_sendCmd(0xA8); ssd1306_sendCmd(0x3F);
    //ssd1306_sendCmd(0xA4);
    ssd1306_sendCmd(0xD3); ssd1306_sendCmd(0x00);
    ssd1306_sendCmd(0xD5); ssd1306_sendCmd(0x80);
    ssd1306_sendCmd(0xD9); ssd1306_sendCmd(0xF1);
    ssd1306_sendCmd(0xDA); ssd1306_sendCmd(0x12);
    ssd1306_sendCmd(0xDB); ssd1306_sendCmd(0x40);
    ssd1306_sendCmd(0x8D); ssd1306_sendCmd(0x14);
    ssd1306_sendCmd(0xAF); // display ON
    ssd1306_clear();
    ssd1306_updateScreen();

}

void ssd1306_clear(void){
	memset(ssd1306_buffer,0,sizeof(ssd1306_buffer));
}

void ssd1306_updateScreen(void){
	for (uint8_t i = 0;i < 8; i++) {
		ssd1306_sendCmd(0xB0 + i);
		ssd1306_sendCmd(0x00);
		ssd1306_sendCmd(0x10);
		uint8_t data[129];
		data[0]=0x40;
		memcpy(&data[1], &ssd1306_buffer[128*i],128);
		HAL_I2C_Master_Transmit(&hi2c1, SSD1306_I2C_ADDR, data, 129, 100);

	}
}

void ssd1306_drawPixel(uint8_t x, uint8_t y, uint8_t color){
	if (x >=128 || y >= 64) {
		return;
	}
	if(color){
		ssd1306_buffer[x + (y/8)*128] |= 1<< (y % 8);
	}
	else {
		ssd1306_buffer[x + (y/8)*128] &= ~(1 <<(y%8));\
	}
}


uint8_t ssd1306_writeChar(char ch, uint8_t x, uint8_t y, FontDef font) {
    if (ch < 32 || ch > 126) return 0;
    uint16_t charIndex = (ch - 32) * font.width;

    for (uint8_t i = 0; i < font.width; i++) {
        uint8_t line = font.data[charIndex + i];
        for (uint8_t j = 0; j < font.height; j++) {
            if (line & (1 << j)) {
                ssd1306_drawPixel(x + i, y + j, 1);
            } /*else {
                ssd1306_drawPixel(x + i, y + j, 0);
            }*/
        }
    }
    return font.width + 1; // khoảng trắng 1 pixel
}

void ssd1306_writeString(char* str, uint8_t x, uint8_t y, FontDef font) {
    while (*str) {
        x += ssd1306_writeChar(*str, x, y, font);
        str++;
    }
}















