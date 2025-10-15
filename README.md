datasheet: https://www.alldatasheet.com/datasheet-pdf/view/1179026/ETC2/SSD1306.html

địa chỉ oled ssd1306 (xem mục 9 datasheet)

0xAE / 0xAF : tắt bật màn hình
0x20 : chọn chế độ địa chỉ
0x00 : ghi dữ liệu theo hàng ngang(hết dòng tự xuống dòng mới)
0x01 : chế độ hàng dọc
0x02 : chế độ trang(mỗi dòng là 1 trang, không tự xuống dòng, tràn là mất)
0xB0 - 0xB7 : chọn page(hàng)
0xC0 / 0xC8 : chọn hướng hiển thị xuôi / ngược
0x00 : đặt 4 bit thấp địa chỉ cột về 0  |
0x10 : đặt 4 bit cao địa chỉ cột về 0   |=> bắt đầu viết từ cột 0
0x40 : bắt đầu hiển thị từ dòng đầu tiên
0x81 : lệnh chỉnh độ tương phản (0x00 -> 0xFF)
0xA0 / 0xA1 : chọn hướng cột xuôi, ngược 
0xA6 / 0xA7 : chọn chế độ hiển thị (A6: 1 = sáng, 0 = tối | A7 ngược lại)
0xA8 : đặt chiều cao(có bao nhiêu dòng) ở đây ssd1306 có 64 dòng nên gửi lệnh 0x3F = 63
0xA4 / 0xA5 : chọn chế độ hiển thị RAM (A4 : chỉ nội dung trong RAM | A5 : toàn bộ màn hình sáng)
0xD3 : lệnh dịch màn hình theo chiều dọc + giá trị (top_displayed_line = (display_start_line + display_offset) % (MUX + 1))
0xD5 : lệnh đặt tốc độ quét + giá trị (bit(7-4) : điều chỉnh tốc độ dao động nội| bit(3-0) : hệ số chia)
0xD9 : lệnh đặt thời gian sạc xả + giá trị (bit(3-0) : phase 1: sạc | bit(7-4): phase 2: xả)
    thời gian t = (phase+1)*(tốc độ dao động nội) | 0xF1 là giá trị ổn định
0xDA : cấu hình chân COM + giá trị
  bit(7-6) = 0
  bit 5 = 0 : 32 hàng | = 1: 64 hàng
  bit 4 = 0 : COM0 ở trên cùng | = 1 : COM0 ở dưới cùng 
  bit(3-0) = 0
  => ssd1306 128x64 đặt giá trị 0x10
0xDB : chọn điện áp nền + giá trị(đặt điện áp chân COM khi không hoạt động)
  bit(7-6) không dùng
  bit(5-0) : chọn mức điện áp so với Vcc (Vcom = bit(5-0)xVcc)
  0x00 = 0,43 | 0x20 = 0x77 | 0x40 = 0,83 | 0x60 = 0,86
0x8D : cấu hình điện áp (xem datasheet trang 62)


  
