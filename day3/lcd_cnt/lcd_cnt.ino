#include <LiquidCrystal.h>
LiquidCrystal lcd(13, 12, 14, 27, 26, 25);

void setup() {
    lcd.begin(16, 2);
    lcd.print("count:");
}

void loop() {
    static int n = 1200;
    n = (n > 0) ? n - 7 : 1200;            // 1200 → 0 으로 줄어드는 값
    char buf[17];                          // 16글자 + '\0'
    lcd.setCursor(6, 0);
    snprintf(buf, sizeof(buf), "%4d", n);  // 항상 4칸 — 남는 글자가 없다
    lcd.print(buf);
    lcd.setCursor(0, 1);
    lcd.printf("%3lus", (millis() / 1000) % 1000);
    delay(200);
}