/*
 * font5x7.h
 *
 *  Created on: Sep 14, 2025
 *      Author: khanh
 */

#ifndef INC_FONT5X7_H_
#define INC_FONT5X7_H_
#include <stdint.h>

/*
 * Font 5x7 cho SSD1306
 * Mỗi ký tự có 5 cột, cao 7 pixel
 * Dữ liệu lấy từ font chuẩn Adafruit GFX
 */

typedef struct {
    uint8_t width;
    uint8_t height;
    const uint8_t *data;
} FontDef;

// Font 5x7 (ASCII 32-127)
extern const FontDef Font_5x7;

#endif /* INC_FONT5X7_H_ */
