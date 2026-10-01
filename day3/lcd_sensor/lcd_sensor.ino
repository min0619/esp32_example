#include <LiquidCrystal.h>
LiquidCrystal lcd(13, 12, 14, 27, 26, 25);
const int PIN_LIGHT = 33;

byte BAR[8] = {0b11111, 0b11111, 0b11111, 0b11111,
               0b11111, 0b11111, 0b11111, 0b11111};   // 꽉 찬 칸 (5×8)

void setup() {
    lcd.begin(16, 2);
    lcd.createChar(0, BAR);                // 사용자 문자 0번
}

void loop() {
    int raw = analogRead(PIN_LIGHT);
    int pct = raw * 100 / 4095;
    char line[17];
    snprintf(line, sizeof(line), "light:%4d %3d%%", raw, pct);
    lcd.setCursor(0, 0);
    lcd.print(line);

    int bars = pct * 16 / 100;             // 0 ~ 16 칸 막대 그래프
    lcd.setCursor(0, 1);
    for (int i = 0; i < 16; i++) {
        if (i < bars) lcd.write((uint8_t)0);
        else lcd.print(' ');
    }
    delay(200);
}