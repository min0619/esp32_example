#include <LiquidCrystal.h>

//                RS  E   D4  D5  D6  D7
LiquidCrystal lcd(13, 12, 14, 27, 26, 25);

void setup() {
    lcd.begin(16, 2);                  // 16칸 · 2줄
    lcd.print("Hello ESP32");          // 커서 (0, 0) 부터
    lcd.setCursor(0, 1);               // (열, 행) — 0부터
    lcd.print("Day 3 LCD 1602A");
}

void loop() { }
// → 윗줄 Hello ESP32, 아랫줄 Day 3 LCD 1602A