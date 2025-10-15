void ssd1306_clear(void){
    memset(ssd1306_buffer,0,sizeof(ssd1306_buffer));
}
xóa toàn bộ buffer dạng ram của màn
ssd1306_bufer là mảng lưu trạng thái pixel trong ram của mcu, với màn 128x64 thì buffer có kích thước 128x64/8 = 1024byte
memset(): đặt tất cả các byte bằng 0
*************************************
*************************************
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
gửi toàn bộ buffer ra màn theo page, màn 128*64 được chia làm 8 page, mỗi page cao 8px
gửi lệnh chọn page 0xB0 -> 0xB7, lệnh 0x00 và 0x10 đặt cột bắt đầu từ 0
data[129], data[0] = 0x40 tạo buffer dài 129byte có byte đầu nhận vào i2c là lệnh hiển thị, các byte sau là dữ liệu hiển thị
memcpy() copy 128byte từ page i vào data[1..128] rồi gửi qua i2c 
***********************************
***********************************
void ssd1306_drawPixel(uint8_t x, uint8_t y, uint8_t color){
    if (x >=128 || y >= 64) return; // nằm ngoài màn hình thì bỏ
    if (color)
        ssd1306_buffer[x + (y/8)*128] |= 1 << (y % 8);
    else
        ssd1306_buffer[x + (y/8)*128] &= ~(1 << (y % 8));
}
bật tắt 1px tọa độ (x,y) trong buffer: cột x(0-127), hàng y(0-63), color = 1(px sáng) | =0(px tắt)
cách tính: index = x + (y / 8) * 128;
y/8 : xác định page 0 -> 7
y%8 : xác định vị trí bit trong byte
x : xác định cột
1 << (y % 8): lấy vị trí bit trong byte rồi dịch bit 1 sang vị trí đó
|= : or rồi gán
&= : and rồi gán
***********************************
***********************************
uint8_t ssd1306_writeChar(char ch, uint8_t x, uint8_t y, FontDef font) {
    if (ch < 32 || ch > 126) return 0;
    uint16_t charIndex = (ch - 32) * font.width;
    for (uint8_t i = 0; i < font.width; i++) {
        uint8_t line = font.data[charIndex + i];
        for (uint8_t j = 0; j < font.height; j++) {
            if (line & (1 << j)) {
                ssd1306_drawPixel(x + i, y + j, 1);
            }
        }
    }
    return font.width + 1; // thêm 1 pixel trống giữa các ký tự
}
vẽ kí tự ascii lên buffer tại tọa độ (x,y) bằng font5x7
font.data chứa bitmap của các kí tự, mỗi kí tự có font.width cột
vị trí của kí tự trong mảng char=(ch-32)*font.width
duyệt từng cột i và hàng j kí tự, nếu bit tại (i,j) = 1, px sáng
***********************************
***********************************
void ssd1306_writeString(char* str, uint8_t x, uint8_t y, FontDef font) {
    while (*str) {
        x += ssd1306_writeChar(*str, x, y, font);
        str++;
    }
}
in chuỗi kí tự ra màn hình bắt đầu từ vị trí (x,y)
duyệt qua từng kí tự trong chuỗi, gọi hàm writechar để vẽ, sau mỗi kí tự tăng x lên để viết tiếp












